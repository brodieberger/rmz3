#!/usr/bin/env -S deno run --allow-read --allow-run

import { Command } from '@cliffy/command';

// src/data/texts/*.s の日英デュアル (.if ENGLISH) テキストを検証するツール。
//
// 2 つのチェックを行う:
//
// 1. 制御コードスケルトン照合 (ツールチェイン不要, デフォルト):
//    各エントリの英語ペイロードと日本語ペイロードから、制御コード列
//    ({WINDOW xx}, {TOP}, {BOTTOM}, {RED}, {RED_END}, {VARIABLE}, {ANSWER xx},
//    {RETURN}, {F5 xx}, {F6 xx}) と ▼ ページ送りの数、$ 終端を取り出して比較する。
//    (改行 \n は英語では折り返しが変わるので除外)。
//    英語側が日本語側と同じスケルトンを持てば「整合」、違えば「要校正」。
//    text_lang.ts が自動生成した直後は、複数ウィンドウ/ページ送り/{RED} 等を
//    持つエントリがすべて mismatch として出る (= @ TODO(en) の集合)。人手で
//    英語ペイロードに制御コードを戻すと mismatch が消えるので、進捗の目安になる。
//
// 2. アセンブル確認 (--assemble, preproc と arm-none-eabi-as が必要):
//    preproc | as --defsym ENGLISH=1 と =0 の両方が通ることを確認する。
//    構文ミスや charmap 未対応文字を検出できる。
//
// e.g. ./tools/dev/verify_text_lang.ts                       # 全 texts を照合
//      ./tools/dev/verify_text_lang.ts src/data/texts/00xx.s # 1 ファイル
//      ./tools/dev/verify_text_lang.ts --assemble            # アセンブルも確認
//      ./tools/dev/verify_text_lang.ts --list-mismatch       # 未整合エントリ名を列挙

const STRING_RE = /^\s*\.string\s+"(.*)"\s*$/;
const LABEL_RE = /^([A-Za-z_][A-Za-z0-9_]*):\s*(@.*)?$/;

// 意味のある制御コードだけを取り出す (\n は折り返し差を許すため無視)。
const skeletonOf = (chunks: string[]): string => {
  const joined = chunks.join('');
  const tokens: string[] = [];
  const re = /\{[^}]*\}|▼|\$/g;
  let m: RegExpExecArray | null;
  while ((m = re.exec(joined)) !== null) tokens.push(m[0]);
  return tokens.join(' ');
};

type Entry = { label: string; en: string[]; jp: string[]; hasTodo: boolean };

const parseEntries = (text: string): Entry[] => {
  const lines = text.split('\n');
  const entries: Entry[] = [];
  let lastLabel = '(top)';
  for (let i = 0; i < lines.length; i++) {
    const lab = lines[i].match(LABEL_RE);
    if (lab) lastLabel = lab[1];
    if (/^\s*\.if ENGLISH\s*$/.test(lines[i])) {
      const en: string[] = [];
      const jp: string[] = [];
      let hasTodo = false;
      let side: 'en' | 'jp' = 'en';
      i++;
      while (i < lines.length && !/^\s*\.endif\s*$/.test(lines[i])) {
        if (/^\s*\.else\s*$/.test(lines[i])) side = 'jp';
        else if (/TODO\(en\)/.test(lines[i])) hasTodo = true;
        else {
          const s = lines[i].match(STRING_RE);
          if (s) (side === 'en' ? en : jp).push(s[1]);
        }
        i++;
      }
      entries.push({ label: lastLabel, en, jp, hasTodo });
    }
  }
  return entries;
};

const run = async (cmd: string[], input: string): Promise<number> => {
  const p = new Deno.Command(cmd[0], { args: cmd.slice(1), stdin: 'piped', stdout: 'piped', stderr: 'piped' }).spawn();
  const w = p.stdin.getWriter();
  await w.write(new TextEncoder().encode(input));
  await w.close();
  const { code } = await p.output();
  return code;
};

const assembleFile = async (path: string): Promise<{ en: boolean; jp: boolean; err: string }> => {
  const preproc = 'tools/preproc/preproc';
  const as = (Deno.env.get('DEVKITARM') ? Deno.env.get('DEVKITARM') + '/bin/' : '') + 'arm-none-eabi-as';
  try {
    const pre = await new Deno.Command(preproc, { args: [path, 'charmap.txt'], stdout: 'piped', stderr: 'piped' }).output();
    if (pre.code !== 0) return { en: false, jp: false, err: 'preproc: ' + new TextDecoder().decode(pre.stderr).trim() };
    const src = new TextDecoder().decode(pre.stdout);
    const en = await run([as, '--defsym', 'ENGLISH=1', '-o', '/dev/null', '-'], src);
    const jp = await run([as, '--defsym', 'ENGLISH=0', '-o', '/dev/null', '-'], src);
    return { en: en === 0, jp: jp === 0, err: '' };
  } catch (e) {
    return { en: false, jp: false, err: `toolchain not found (${(e as Error).message}); run 'make -C tools/preproc' and ensure arm-none-eabi-as is on PATH` };
  }
};

const main = async () => {
  const { args, options } = await new Command()
    .name('verify_text_lang.ts')
    .version('1.0.0')
    .description('日英デュアルテキストの制御コード整合と (任意で) アセンブルを検証する')
    .arguments('[files...:string]')
    .option('--assemble', 'preproc | arm-none-eabi-as で両ブランチがアセンブルできるか確認する')
    .option('--list-mismatch', '未整合 (要校正) エントリのラベルを列挙する')
    .parse(Deno.args);

  const files = (args[0] as string[] | undefined)?.length
    ? (args[0] as unknown as string[])
    : [...Deno.readDirSync('src/data/texts')].filter((e) => e.name.endsWith('.s')).map((e) => 'src/data/texts/' + e.name).sort();

  let totalEntries = 0, totalMismatch = 0, anyFail = false;
  for (const f of files) {
    const entries = parseEntries(Deno.readTextFileSync(f));
    const mismatches = entries.filter((e) => skeletonOf(e.en) !== skeletonOf(e.jp));
    totalEntries += entries.length;
    totalMismatch += mismatches.length;

    let asmNote = '';
    if (options.assemble) {
      const r = await assembleFile(f);
      if (r.err) { asmNote = `  asm: SKIP (${r.err})`; }
      else {
        asmNote = `  asm: EN=${r.en ? 'ok' : 'FAIL'} JP=${r.jp ? 'ok' : 'FAIL'}`;
        if (!r.en || !r.jp) anyFail = true;
      }
    }
    console.log(`${f.padEnd(24)} entries=${String(entries.length).padStart(3)} aligned=${String(entries.length - mismatches.length).padStart(3)} needs-proof=${String(mismatches.length).padStart(3)}${asmNote}`);
    if (options.listMismatch) for (const m of mismatches) console.log(`    - ${m.label}`);
  }
  console.log(`\nTOTAL: ${totalEntries} entries, ${totalEntries - totalMismatch} aligned, ${totalMismatch} need proofing`);
  if (anyFail) { console.error('\nAssembly FAILED for one or more files.'); Deno.exit(1); }
};

main();
