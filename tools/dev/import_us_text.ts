#!/usr/bin/env -S deno run --allow-read --allow-write
// Import the official English script from the US ROM (BZ3E) into the
// `.if ENGLISH` branches of src/data/texts/*.s.
//
// The US ROM uses the same text engine and charmap as the JP ROM, with one
// difference: lowercase a-z occupies 0x25-0x3E (the JP hiragana range).
// Its bank/offset tables live at fixed ROM offsets (found by scanning):
//   gTextOffsetTable @ 0x373644 (20 pointers to u16 offset tables)
//   gTextTable       @ 0x373694 (20 pointers to text banks)
// Bank n corresponds to src/data/texts/<n as %02X>xx.s; entry i of a bank is
// the label at index i of the file's TextOfs .2byte table.
//
// Usage:
//   ./tools/dev/import_us_text.ts <us-rom> [files...] [--write]
// Dry-run by default; --write rewrites the English branches in place.
// The Japanese `.else` sides are never touched.

const US_OFS_TABLE = 0x373644;
const US_BANK_TABLE = 0x373694;
const ROM_BASE = 0x08000000;

// ---- charmap ---------------------------------------------------------------

type DecodeMaps = { single: Map<number, string>; double: Map<number, string> };

const parseCharmap = (path: string): DecodeMaps => {
  const single = new Map<number, string>();
  const double = new Map<number, string>();
  for (const raw of Deno.readTextFileSync(path).split("\n")) {
    if (raw.includes("English build aliases")) break; // additive aliases: encode-only
    const line = raw.trim();
    const m = line.match(/^'(\\?.|..)' = ([0-9A-F]{2})( [0-9A-F]{2})?$/);
    if (!m) continue;
    let ch = m[1];
    if (ch === "\\'") ch = "'";
    else if (ch === "\\n") ch = "\n";
    else if (ch === "\\\\") ch = "\\";
    if (m[3]) {
      const key = (parseInt(m[2], 16) << 8) | parseInt(m[3].trim(), 16);
      if (!double.has(key)) double.set(key, ch);
    } else {
      const b = parseInt(m[2], 16);
      if (!single.has(b)) single.set(b, ch);
    }
  }
  // US override: lowercase in the hiragana range.
  for (let i = 0; i < 26; i++) single.set(0x25 + i, String.fromCharCode(97 + i));
  // US comma glyph; the JP charmap never mapped 0xE8 (JP text uses '、'=D5).
  single.set(0xE8, ",");
  // Prefer the ASCII spellings for source readability; the charmap's English
  // alias block encodes them back to the same bytes.
  single.set(0xCA, "!");
  single.set(0xDD, "?");
  // US redraws the '↾' tile (0xCC) as a number sign ("File #650326").
  single.set(0xCC, "#");
  return { single, double };
};

// ---- US ROM decode ---------------------------------------------------------

type Tok =
  | { t: "char"; c: string }
  | { t: "ctrl"; s: string } // inline control token, e.g. {RED}
  | { t: "window"; n: number }
  | { t: "nl" }
  | { t: "page" }
  | { t: "end" };

const ARG1: Record<number, string> = { 0xF4: "ANSWER", 0xF5: "F5", 0xF6: "F6" };
const PLAIN: Record<number, string> = {
  0xF1: "{RED_END}", 0xF2: "{RED}", 0xF9: "{VARIABLE}",
  0xFA: "{TOP}", 0xFB: "{BOTTOM}", 0xFE: "{RETURN}",
};

const decodeEntry = (
  rom: Uint8Array, start: number, maps: DecodeMaps, warn: (s: string) => void,
): Tok[] => {
  const toks: Tok[] = [];
  let i = start;
  for (;;) {
    const b = rom[i];
    if (b === 0xFF) { toks.push({ t: "end" }); break; }
    else if (b === 0xFC) toks.push({ t: "nl" });
    else if (b === 0xFD) toks.push({ t: "page" });
    else if (b === 0xF3) toks.push({ t: "window", n: rom[++i] });
    else if (b in ARG1) {
      const hex = rom[++i].toString(16).toUpperCase().padStart(2, "0");
      toks.push({ t: "ctrl", s: `{${ARG1[b]} 0x${hex}}` });
    } else if (b in PLAIN) toks.push({ t: "ctrl", s: PLAIN[b] });
    else if (b === 0xF0 || b === 0xDA) {
      const key = (b << 8) | rom[i + 1];
      const ch = maps.double.get(key);
      if (ch !== undefined) { toks.push({ t: "char", c: ch }); i++; }
      else warn(`unmapped 2-byte 0x${key.toString(16)} @ 0x${i.toString(16)}`);
    } else if (b >= 0xF0) {
      warn(`unexpected control 0x${b.toString(16)} @ 0x${i.toString(16)}`);
      toks.push({ t: "ctrl", s: `{0x${b.toString(16).toUpperCase().padStart(2, "0")}}` });
    } else {
      const ch = maps.single.get(b);
      if (ch !== undefined) toks.push({ t: "char", c: ch });
      else {
        warn(`unmapped byte 0x${b.toString(16)} @ 0x${i.toString(16)}`);
        toks.push({ t: "ctrl", s: `{0x${b.toString(16).toUpperCase().padStart(2, "0")}}` });
      }
    }
    i++;
  }
  return toks;
};

// ---- source-line formatting ------------------------------------------------

// preproc cannot take a literal '"' inside .string; the charmap's '"' glyph
// byte is injected via numeric syntax instead.
const escChar = (c: string) => (c === '"' ? "{0xE9}" : c);

const formatEntry = (toks: Tok[]): string[] => {
  const out: string[] = [];
  let cur = "";
  const flush = () => { if (cur.length) out.push(`\t\t.string "${cur}"`); cur = ""; };
  for (const tok of toks) {
    if (tok.t === "window") {
      flush();
      out.push(`\t.string "{WINDOW 0x${tok.n.toString(16).toUpperCase().padStart(2, "0")}}"`);
    } else if (tok.t === "char") cur += escChar(tok.c);
    else if (tok.t === "ctrl") cur += tok.s;
    else if (tok.t === "nl") { cur += "\\n"; flush(); }
    else if (tok.t === "page") { cur += "▼"; flush(); }
    else if (tok.t === "end") { cur += "$"; flush(); }
  }
  return out;
};

// ---- .s file parsing / rewriting -------------------------------------------

const rewriteFile = (
  path: string, bank: number, rom: Uint8Array, dv: DataView, maps: DecodeMaps,
  write: boolean,
): { entries: number; replaced: number; warns: string[] } => {
  const warns: string[] = [];
  const src = Deno.readTextFileSync(path);
  const lines = src.split("\n");

  // Ordered ID list from the TextOfs .2byte table.
  const ofsLabels: string[] = [];
  for (const line of lines) {
    if (/^\s*\.2byte\b/.test(line)) {
      for (const m of line.matchAll(/\(?\s*([A-Za-z0-9_]+)\s*-\s*Start\s*\)?/g)) ofsLabels.push(m[1]);
    }
  }

  const bankAddr = dv.getUint32(US_BANK_TABLE + bank * 4, true) - ROM_BASE;
  const ofsAddr = dv.getUint32(US_OFS_TABLE + bank * 4, true) - ROM_BASE;
  const usCount = (bankAddr - ofsAddr) / 2;
  if (usCount !== ofsLabels.length) {
    warns.push(`ID count differs: JP table ${ofsLabels.length}, US table ${usCount}`);
  }

  const out: string[] = [];
  let pendingLabels: string[] = [];
  let replaced = 0;
  let i = 0;
  while (i < lines.length) {
    const line = lines[i];
    const lm = line.match(/^([A-Za-z0-9_]+):{1,2}(\s|$|@)/);
    if (lm && ofsLabels.includes(lm[1])) pendingLabels.push(lm[1]);
    if (/^\s*\.if ENGLISH\s*$/.test(line)) {
      // Find matching .else
      let j = i + 1;
      while (j < lines.length && !/^\s*\.else\s*$/.test(lines[j])) j++;
      if (j === lines.length) { warns.push(`no .else after line ${i + 1}`); out.push(line); i++; continue; }
      const idx = Math.min(...pendingLabels.map((l) => ofsLabels.indexOf(l)).filter((x) => x >= 0));
      if (!isFinite(idx)) {
        warns.push(`no table index for block at line ${i + 1} (labels: ${pendingLabels.join(",")})`);
        for (; i <= j - 1; i++) out.push(lines[i]);
        continue;
      }
      const start = bankAddr + dv.getUint16(ofsAddr + idx * 2, true);
      const toks = decodeEntry(rom, start, maps, (w) => warns.push(`${pendingLabels[0]}: ${w}`));
      out.push(line, ...formatEntry(toks));
      replaced++;
      pendingLabels = [];
      i = j; // continue at .else
      continue;
    }
    out.push(line);
    i++;
  }

  if (write) Deno.writeTextFileSync(path, out.join("\n"));
  return { entries: ofsLabels.length, replaced, warns };
};

// ---- main ------------------------------------------------------------------

const main = () => {
  const args = Deno.args.filter((a) => a !== "--write");
  const write = Deno.args.includes("--write");
  const romPath = args[0];
  if (!romPath) { console.error("usage: import_us_text.ts <us-rom> [files...] [--write]"); Deno.exit(1); }
  const rom = Deno.readFileSync(romPath);
  const dv = new DataView(rom.buffer);
  const maps = parseCharmap("charmap.txt");

  const files = args.length > 1
    ? args.slice(1)
    : [...Deno.readDirSync("src/data/texts")].filter((e) => e.name.endsWith(".s"))
        .map((e) => "src/data/texts/" + e.name).sort();

  let totalReplaced = 0, totalWarns = 0;
  for (const f of files) {
    const bank = parseInt(f.match(/([0-9A-F]{2})xx\.s$/)![1], 16);
    const r = rewriteFile(f, bank, rom, dv, maps, write);
    totalReplaced += r.replaced;
    totalWarns += r.warns.length;
    console.log(`${f}  bank=${bank}  ids=${r.entries}  blocks-replaced=${r.replaced}  warns=${r.warns.length}`);
    for (const w of r.warns) console.log(`  ! ${w}`);
  }
  console.log(`\nTOTAL: ${totalReplaced} blocks ${write ? "rewritten" : "(dry-run)"} , ${totalWarns} warnings`);
};

main();
