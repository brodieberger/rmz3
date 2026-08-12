#!/usr/bin/env -S deno run --allow-read --allow-write

import { Command } from '@cliffy/command';

// src/data/texts/*.s の各テキストエントリを、日本語と英語の両方を持つ形に変換するスクリプト。
//
// 各エントリの連続した `.string` 行を、以下のように `.if ENGLISH` で囲む:
//
//     .if ENGLISH
//         <英語ペイロード (@ EN: グロスから機械生成)>
//     .else
//         <元の日本語ペイロード (そのまま)>
//     .endif
//
// 英語ペイロードは `@ EN:` コメント (` / ` を改行区切りとして持つ) から生成する。
// フォントは大文字のみなので、小文字は charmap で大文字グリフにエイリアスされる
// 前提 (charmap.txt の「English build aliases」を参照)。
//
// 元のペイロードが平坦なグロスでは表現できない構造 (複数の {WINDOW} 切り替え、
// `▼` のページ送り、インラインの {RED}/{VARIABLE}) を含む場合は、同じように
// 変換しつつ `@ TODO(en):` マーカーを付けて、人手での改行・ページ送りの校正を
// 促す。
//
// ビルド側は makefile の TEXTLANG=en (=> as --defsym ENGLISH=1) で英語を選ぶ。
//
// e.g. ./tools/dev/text_lang.ts src/data/texts/00xx.s --in-place

const STRING_RE = /^(\s*)\.string\s+"(.*)"\s*$/;
const GLOSS_RE = /^\s*@ EN:\s?(.*)$/;
const WINDOW_RE = /\{WINDOW [^}]*\}/;
const WINDOW_RE_G = /\{WINDOW [^}]*\}/g;
const CTRL_RE_G = /\{[^}]*\}/g;

const leadingWindow = (chunks: string[]): string | null => {
  for (const c of chunks) {
    const m = c.match(WINDOW_RE);
    if (m) return m[0];
  }
  return null;
};

const positionalPrefix = (chunks: string[]): string | null => {
  for (const c of chunks) {
    const stripped = c.replace(CTRL_RE_G, '');
    if (stripped.trim() === '') {
      if (c.includes('{TOP}')) return '{TOP}';
      if (c.includes('{BOTTOM}')) return '{BOTTOM}';
      continue;
    }
    if (c.startsWith('{TOP}')) return '{TOP}';
    if (c.startsWith('{BOTTOM}')) return '{BOTTOM}';
    return null;
  }
  return null;
};

// メニュー選択肢の行は、日本語では先頭に半角スペース2つを付けてインデントされる。
const countMenuChunks = (chunks: string[]): number =>
  chunks.filter((c) => c.replace(CTRL_RE_G, '').startsWith('  ')).length;

const complexReasons = (chunks: string[]): string[] => {
  const joined = chunks.join('');
  const reasons: string[] = [];
  if ((joined.match(WINDOW_RE_G) ?? []).length > 1) reasons.push('multi-window');
  if (joined.includes('▼')) reasons.push('page-breaks');
  if (joined.includes('{RED}')) reasons.push('red-text');
  if (joined.includes('{VARIABLE}')) reasons.push('variable');
  if (joined.includes('{ANSWER}')) reasons.push('answer');
  return reasons;
};

const buildEnglish = (gloss: string, chunks: string[], indent: string): string[] => {
  const win = leadingWindow(chunks);
  const pos = positionalPrefix(chunks);
  const nMenu = countMenuChunks(chunks);

  let lines = gloss.split(' / ').map((s) => s.trim()).filter((s) => s !== '');
  if (lines.length === 0) lines = [''];

  // 末尾のメニュー選択肢行を日本語のレイアウトに合わせてインデントする。
  lines = lines.map((l, i) => (nMenu > 0 && i >= lines.length - nMenu ? '  ' + l : l));

  const out: string[] = [];
  if (win) out.push(`${indent}.string "${win}"`);

  for (let i = 0; i < lines.length; i++) {
    const prefix = i === 0 && pos ? pos : '';
    const term = i === lines.length - 1 ? '$' : '\\n';
    // preproc は .string 内に生の ASCII ダブルクォートを置けない (リテラルを
    // 終端し、エスケープも禁止されている。ゲーム本体は「」で引用する)。
    // グロスの引用符はアポストロフィにする。大文字テキストでも読みやすい。
    const line = lines[i].replaceAll('"', "'");
    out.push(`${indent}.string "${prefix}${line}${term}"`);
  }
  return out;
};

const process = (text: string): string => {
  const lines = text.split('\n');
  const out: string[] = [];
  let i = 0;
  const n = lines.length;

  while (i < n) {
    const m = lines[i].match(STRING_RE);
    if (!m) {
      out.push(lines[i]);
      i++;
      continue;
    }

    // `.string` の連続を集める。
    const run: Array<[string, string]> = [];
    const runIndent = m[1];
    let j = i;
    while (j < n) {
      const mm = lines[j].match(STRING_RE);
      if (!mm) break;
      run.push([mm[1], mm[2]]);
      j++;
    }
    const chunks = run.map(([, c]) => c);

    // グロスを探す: 直前の `@ EN:` 行 (このエントリを導入するラベル/コメントを
    // さかのぼる。空行や別の .string / .endif で打ち切る)。
    let gloss: string | null = null;
    for (let k = out.length - 1; k >= 0; k--) {
      const g = out[k].match(GLOSS_RE);
      if (g) {
        gloss = g[1];
        break;
      }
      if (out[k].trim() === '' || out[k].includes('.string') || out[k].includes('.endif')) break;
    }

    out.push(`${runIndent}.if ENGLISH`);
    if (gloss !== null) {
      const reasons = complexReasons(chunks);
      if (reasons.length > 0) {
        out.push(`${runIndent}\t@ TODO(en): ${reasons.join(', ')} - proof line/page breaks against JP`);
      }
      out.push(...buildEnglish(gloss, chunks, runIndent + '\t'));
    } else {
      // 翻訳するグロスがない場合は日本語をそのまま使い、ビルドは通るようにする。
      for (const [ind, c] of run) out.push(`${ind}.string "${c}"`);
    }
    out.push(`${runIndent}.else`);
    for (const [ind, c] of run) out.push(`${ind}.string "${c}"`);
    out.push(`${runIndent}.endif`);

    i = j;
  }
  return out.join('\n');
};

const main = async () => {
  const { args, options } = await new Command()
    .name('text_lang.ts')
    .version('1.0.0')
    .description('src/data/texts/*.s のテキストエントリを日英デュアル (.if ENGLISH) 形式に変換する')
    .argument('<src:string>', 'texts/*.s のファイルパス')
    .option('-i, --in-place', '入力ファイルを上書きする (指定しなければ標準出力)')
    .usage('src/data/texts/00xx.s --in-place')
    .parse(Deno.args);

  const result = process(Deno.readTextFileSync(args[0]));
  if (options.inPlace) {
    Deno.writeTextFileSync(args[0], result);
  } else {
    console.log(result);
  }
};

main();
