#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { BASE, ROM_PATH } from '../common/index.ts';
import { GraphicHeader, GraphicProp } from '../common/index.ts';

/**
 * JSONの配列要素は、
 * "xxx": [
 *  ???,
 *  ???,
 *  ...
 *  ???
 * ]
 * と出力されるが、要素が全て 数値や文字列 で構成されている場合は、
 * "xxx": [???, ???, ... ???]
 * と1行で出力されるようにするための関数
 */
const collapseSimpleArrays = (json: string): string => {
  const element = String.raw`(?:"(?:[^"\\]|\\.)*"|-?\d+(?:\.\d+)?)`;
  const array = new RegExp(
    String.raw`\[\s*(${element}(?:,\s*${element})*)\s*\]`,
    'g',
  );
  return json.replace(array, (_, inner) => `[${inner.replace(/\s+/g, ' ').trim()}]`);
};

const printGraphicHeader = (
  rom: DataView,
  addr: number,
  nopal: boolean,
): GraphicHeader => {
  const getProps = (props: number): GraphicProp[] => {
    if (props === 0x22) return ['lz77', '4bpp'];
    if (props === 0x26) return ['lz77', '4bpp', 'no_pal'];
    if (props === 0x24) return ['4bpp', 'no_pal'];
    if (props === 0x25) return ['4bpp', 'no_pal', 'chunked'];
    if (props === 0x20) return ['4bpp'];
    if (props === 0x00) return [];
    throw new Error(`Unknown props: ${props}`);
  };

  const offset = addr - BASE;
  const gfx = {
    ofs: rom.getUint16(offset + 6, true) >> 6,
    chunk: rom.getUint16(offset + 8, true),
    props: rom.getUint16(offset + 10, true),
    palLength: rom.getUint16(offset + 16, true) / 2,
    dst: rom.getUint8(offset + 19),
  };

  const data: GraphicHeader = {
    name: '',
    ofs: gfx.ofs,
    chunkSize: gfx.chunk,
    props: getProps(gfx.props),
  };

  if (nopal) {
    return data;
  }

  data.palette = {
    color: gfx.palLength,
    id: gfx.dst,
  };
  return data;
};

// ROMから、 (struct Graphic または struct ColorGraphic) を JSON形式(header.json)で出力するツール
// あくまで struct Graphic または struct ColorGraphic のみを出力するツールであって、これらの指す、グラフィックデータやパレットデータは出力しないことに注意 (グラフィックデータやパレットデータは gfx.ts でダンプします)
// また、依存ファイル (.files[]) は自分で書き込んであげる必要があることに注意
// e.g.
//  ./tools/dumper/graphic_header_json.ts --nopal 0x083b8fac 4 > tmp/header.json
const command = new Command().name('graphic_header_json')
  .description(`Graphic構造体 の配列の先頭アドレスと、配列の長さを与えると JSONを標準出力に表示します`)
  .argument('<start_addr:string>', '開始アドレス')
  .argument('<length:number>', 'エントリ数')
  .option('--nopal', '対象が、 "struct ColorGraphic" ではなく "struct Graphic" の場合には、有効にする必要がある')
  .usage('0x085197C4 4')
  .action((options, start_addr: string, length: number) => {
    const rom = new DataView(Deno.readFileSync(ROM_PATH).buffer);
    const start = Number(start_addr);

    const headers: GraphicHeader[] = [];

    for (let i = 0; i < length; i++) {
      const addr = start + (i * (options.nopal ? 12 : (12 + 8))); // 12: sizeof(struct Graphic), 20: sizeof(struct ColorGraphic)
      const hdr = printGraphicHeader(rom, addr, options.nopal ?? false);
      hdr.name = `${i}.png`;
      headers.push(hdr);
    }

    const output = JSON.stringify({ data: headers }, null, '\t');
    console.log(collapseSimpleArrays(output));
  });

const main = async () => {
  await command.parse(Deno.args);
};

main();
