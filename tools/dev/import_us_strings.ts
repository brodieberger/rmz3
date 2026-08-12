#!/usr/bin/env -S deno run --allow-read --allow-write
// Convert src/data/strings/strings.s (+ its .inc files) to dual-language and
// import the official English strings from the US ROM (BZ3E).
//
// The JP StringOfsTable is a hardcoded .hword table of offsets into
// gStringData. This tool:
//   1. walks the JP ROM's string data ({FF}-terminated chunks) and the source
//      items (a .string run ending in `$`, a .byte line, or a .include) in
//      lockstep, so each source item gets its JP offset;
//   2. inserts a `Str_<jpofs>` label before every chunk the table references,
//      and regenerates the table as label-relative `.2byte (Str_x-gStringData)`
//      — identical bytes for JP (verified by `make compare`), self-recomputing
//      for EN;
//   3. wraps each referenced chunk in `.if ENGLISH` with the official English
//      string decoded from the US ROM at the same table index (JP and US
//      tables are parallel: 1096 entries, verified same alias structure).
//
// Usage: ./tools/dev/import_us_strings.ts <us-rom> [--write]

const JP_ROM = "rmz3.gba";
const JP_TABLE = 0x372210, JP_DATA = 0x372aa0;
const US_TABLE = 0x36e9d8, US_DATA = 0x36f268;
const N_ENTRIES = 1096;
const JP_DATA_END = 0x3767a8; // end of strings.o rodata in the ROM

// ---- charmap (decode maps, same approach as import_us_text.ts) -------------

const parseCharmap = () => {
  const single = new Map<number, string>();
  const double = new Map<number, string>();
  for (const raw of Deno.readTextFileSync("charmap.txt").split("\n")) {
    if (raw.includes("English build aliases")) break;
    const line = raw.trim();
    const m = line.match(/^'(\\?.|..)' = ([0-9A-F]{2})( [0-9A-F]{2})?/);
    if (!m) continue;
    let ch = m[1];
    if (ch === "\\'") ch = "'";
    else if (ch === "\\n") ch = "\n";
    else if (ch === "\\\\") ch = "\\";
    if (m[3]) {
      const key = (parseInt(m[2], 16) << 8) | parseInt(m[3].trim(), 16);
      if (!double.has(key)) double.set(key, ch);
    } else if (!single.has(parseInt(m[2], 16))) single.set(parseInt(m[2], 16), ch);
  }
  for (let i = 0; i < 26; i++) single.set(0x25 + i, String.fromCharCode(97 + i));
  single.set(0xE8, ","); single.set(0xCA, "!"); single.set(0xDD, "?"); single.set(0xCC, "#");
  return { single, double };
};

// ---- US string decode -> .string source lines ------------------------------

const ARG1: Record<number, string> = { 0xF4: "ANSWER", 0xF5: "F5", 0xF6: "F6", 0xF7: "F7" };
const PLAIN: Record<number, string> = {
  0xF1: "{RED_END}", 0xF2: "{RED}", 0xF9: "{VARIABLE}",
  0xFA: "{TOP}", 0xFB: "{BOTTOM}", 0xFE: "{RETURN}",
};

const decodeUS = (
  rom: Uint8Array, start: number, maps: ReturnType<typeof parseCharmap>,
  warn: (s: string) => void,
): string[] => {
  // returns .string source lines (without indent)
  const out: string[] = [];
  let cur = "";
  const flush = () => { if (cur.length) out.push(`.string "${cur}"`); cur = ""; };
  for (let i = start; ; i++) {
    const b = rom[i];
    if (b === 0xFF) { cur += "$"; flush(); break; }
    else if (b === 0xFC) { cur += "\\n"; flush(); }
    else if (b === 0xFD) { cur += "▼"; flush(); }
    else if (b === 0xF3) cur += `{WINDOW 0x${rom[++i].toString(16).toUpperCase().padStart(2, "0")}}`;
    else if (b in ARG1) cur += `{${ARG1[b]} 0x${rom[++i].toString(16).toUpperCase().padStart(2, "0")}}`;
    else if (b in PLAIN) cur += PLAIN[b];
    else if (b === 0xF0 || b === 0xDA) {
      const ch = maps.double.get((b << 8) | rom[i + 1]);
      if (ch !== undefined) { cur += ch; i++; }
      else { warn(`unmapped 2-byte 0x${b.toString(16)}${rom[i+1].toString(16)} @ 0x${i.toString(16)}`); cur += `{0x${b.toString(16).toUpperCase()}}`; }
    } else if (b >= 0xF0) { warn(`control 0x${b.toString(16)} @ 0x${i.toString(16)}`); cur += `{0x${b.toString(16).toUpperCase()}}`; }
    else {
      const ch = maps.single.get(b);
      if (ch === undefined) { cur += `{0x${b.toString(16).toUpperCase().padStart(2, "0")}}`; }
      else cur += ch === '"' ? "{0xE9}" : ch;
    }
  }
  return out;
};

// ---- main ------------------------------------------------------------------

const write = Deno.args.includes("--write");
const usPath = Deno.args.filter((a) => a !== "--write")[0];
if (!usPath) { console.error("usage: import_us_strings.ts <us-rom> [--write]"); Deno.exit(1); }
const jp = Deno.readFileSync(JP_ROM);
const us = Deno.readFileSync(usPath);
const dvJ = new DataView(jp.buffer), dvU = new DataView(us.buffer);
const maps = parseCharmap();
const warns: string[] = [];
const warn = (s: string) => warns.push(s);

// Tables
const jpOfs: number[] = [], usOfs: number[] = [];
for (let i = 0; i < N_ENTRIES; i++) {
  jpOfs.push(dvJ.getUint16(JP_TABLE + i * 2, true));
  usOfs.push(dvU.getUint16(US_TABLE + i * 2, true));
}
// Alias-structure check: same-offset classes must match between regions.
const firstIdxByJpOfs = new Map<number, number>();
for (let i = 0; i < N_ENTRIES; i++) {
  const o = jpOfs[i];
  if (!firstIdxByJpOfs.has(o)) firstIdxByJpOfs.set(o, i);
  else if (usOfs[i] !== usOfs[firstIdxByJpOfs.get(o)!]) {
    warn(`alias mismatch at index ${i}: JP ofs 0x${o.toString(16)} but US ofs differs from index ${firstIdxByJpOfs.get(o)}`);
  }
}

// JP chunk walk (0xFF-terminated) over the whole data region.
const chunkStarts: number[] = [];
{
  let pos = 0;
  const size = JP_DATA_END - JP_DATA;
  while (pos < size) {
    // stop at trailing zero padding
    if (jp[JP_DATA + pos] === 0x00 && !firstIdxByJpOfs.has(pos)) {
      // could still be a real string starting with a space; only treat as
      // padding at the very end (no more FF ahead)
      let hasFF = false;
      for (let k = JP_DATA + pos; k < JP_DATA + size; k++) if (jp[k] === 0xFF) { hasFF = true; break; }
      if (!hasFF) break;
    }
    chunkStarts.push(pos);
    while (jp[JP_DATA + pos] !== 0xFF) pos++;
    pos++; // past FF
  }
}
const chunkSet = new Set(chunkStarts);
for (const o of firstIdxByJpOfs.keys()) {
  if (!chunkSet.has(o)) warn(`table offset 0x${o.toString(16)} is not a chunk start`);
}

// ---- source rewriting ------------------------------------------------------

let chunkCursor = 0;
const label = (o: number) => `Str_${o.toString(16).toUpperCase().padStart(4, "0")}`;

// Process one file's lines; returns rewritten lines. `top` = strings.s itself.
const processFile = (path: string, presetLines?: string[]): string[] => {
  const lines = presetLines ?? Deno.readTextFileSync(path).split("\n");
  const out: string[] = [];
  let i = 0;
  const emitChunk = (srcLines: string[]) => {
    const ofs = chunkStarts[chunkCursor++];
    if (ofs === undefined) { warn(`${path}: ran out of ROM chunks`); out.push(...srcLines); return; }
    const referenced = firstIdxByJpOfs.has(ofs);
    if (!referenced) { out.push(...srcLines); return; }
    const idx = firstIdxByJpOfs.get(ofs)!;
    const enLines = decodeUS(us, US_DATA + usOfs[idx], maps, (w) => warn(`${label(ofs)} (idx ${idx}): ${w}`));
    const indent = srcLines[0].match(/^\s*/)![0] || "  ";
    out.push(`${label(ofs)}:`);
    // identical content on both sides -> no need for a language switch
    const enPayload = enLines.map((l) => `${indent}${l}`);
    const jpPayload = srcLines;
    if (enPayload.join("\n") === jpPayload.join("\n")) { out.push(...srcLines); return; }
    out.push(".if ENGLISH");
    out.push(...enPayload);
    out.push(".else");
    out.push(...jpPayload);
    out.push(".endif");
  };
  while (i < lines.length) {
    const line = lines[i];
    const t = line.trim();
    if (t.startsWith(".string")) {
      // Gather a .string run until a `$"`-terminated line. A single line can
      // hold SEVERAL `$`-terminated chunks (e.g. "{F7 0x00}…${F7 0x01}…$"),
      // so split contents at `$` boundaries and emit chunk by chunk.
      const run = [line];
      let j = i;
      while (!/\$"\s*(@.*)?$/.test(lines[j])) {
        j++;
        if (j >= lines.length || !lines[j].trim().startsWith(".string")) { warn(`${path}:${i + 1}: unterminated .string run`); break; }
        run.push(lines[j]);
      }
      const indent = run[0].match(/^\s*/)![0];
      let chunkLines: string[] = [];
      for (const rl of run) {
        const cm = rl.match(/^\s*\.string "(.*)"\s*(@.*)?$/);
        if (!cm) { warn(`${path}: bad .string line: ${rl}`); continue; }
        const content = cm[1];
        // split into pieces, each `$`-terminated except possibly the last
        const pieces = content.split(/(?<=\$)/);
        for (const piece of pieces) {
          if (!piece.length) continue;
          chunkLines.push(`${indent}.string "${piece}"`);
          if (piece.endsWith("$")) { emitChunk(chunkLines); chunkLines = []; }
        }
      }
      if (chunkLines.length) { warn(`${path}:${i + 1}: run left unterminated content`); out.push(...chunkLines); }
      i = j + 1;
      continue;
    }
    if (t.startsWith(".byte") && /0xFF\b/i.test(t)) {
      // a raw chunk like `.byte 0xD0, 0xFF` (one FF per line in this file)
      emitChunk([line]);
      i++;
      continue;
    }
    const inc = t.match(/^\.include "([^"]+)"/);
    if (inc) {
      // recurse into the include; rewrite it in place
      const sub = processFile(inc[1]);
      rewritten.set(inc[1], sub);
      out.push(line);
      i++;
      continue;
    }
    out.push(line);
    i++;
  }
  return out;
};

const rewritten = new Map<string, string[]>();

// Pre-pass on strings.s: split into head (through the .hword table) and body.
const src = Deno.readTextFileSync("src/data/strings/strings.s").split("\n");
const dataMark = src.findIndex((l) => l.startsWith("gStringData::"));
if (dataMark < 0) { console.error("gStringData:: not found"); Deno.exit(1); }
if (src.some((l) => l.trim() === ".if ENGLISH")) {
  console.error("strings.s is already dual-language; this tool converts the original flat file only.");
  Deno.exit(1);
}
const firstHword = src.findIndex((l) => l.trim().startsWith(".hword"));
const lastHword = src.reduce((acc, l, n) => (l.trim().startsWith(".hword") ? n : acc), -1);

// Regenerate the table label-relative.
const tableLines: string[] = [];
for (let i = 0; i < N_ENTRIES; i += 8) {
  const row = [];
  for (let k = i; k < Math.min(i + 8, N_ENTRIES); k++) row.push(`(${label(jpOfs[k])}-gStringData)`);
  tableLines.push(`    .2byte ${row.join(", ")}`);
}

// Body: write to a temp representation then process chunk-wise.
const bodyPath = "src/data/strings/strings.s";
{
  const head = src.slice(0, firstHword);
  const newBody = processFile(bodyPath, src.slice(dataMark));
  const newFile = [
    ...head,
    ...tableLines,
    ...src.slice(lastHword + 1, dataMark),
    ...newBody,
  ];
  rewritten.set(bodyPath, newFile);
}

console.log(`chunks in ROM: ${chunkStarts.length}, consumed: ${chunkCursor}, referenced: ${firstIdxByJpOfs.size}`);
console.log(`${warns.length} warnings`);
for (const w of warns.slice(0, 30)) console.log(`  ! ${w}`);

if (write && warns.length === 0) {
  for (const [p, lines] of rewritten) Deno.writeTextFileSync(p, lines.join("\n"));
  console.log(`wrote ${[...rewritten.keys()].join(", ")}`);
} else if (write) {
  console.log("NOT writing due to warnings");
}
