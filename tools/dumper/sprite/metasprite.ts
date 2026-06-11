#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { Parser } from '@binary-parser';
import { BASE, ROM_PATH } from '../../common/index.ts';

const SIZE = 4; // MetaspriteHeader　構造体　のサイズ

const Hdr = new Parser().endianness('little')
  .uint16('ofs')
  .uint8('len')
  .uint8('sheetIdx');

const Subsprite = new Parser().endianness('little')
  .uint16('props')
  .int8('x')
  .int8('y');

const SUPRITE_SIZE: [number, number][] = [
  [8, 8],
  [16, 16],
  [32, 32],
  [64, 64],

  [16, 8],
  [32, 8],
  [32, 16],
  [64, 32],

  [8, 16],
  [8, 32],
  [16, 32],
  [32, 64],
];

type MetaspriteHdrResult = {
  ofs: number;
  len: number;
  sheetIdx: number;
};

type ParseResult = {
  props: number;
  x: number;
  y: number;
};

type Metasprite = {
  sheetIdx: number;
  subsprites: Subsprite[];
};

type Subsprite = {
  tileNum: number;
  xflip: boolean;
  yflip: boolean;
  size: [number, number];
  x: number;
  y: number;
};

const main = async () => {
  const { args } = await new Command()
    .name('metasprite.ts')
    .version('1.0.0')
    .description('開始アドレス(start) から metasprite.json を標準出力に表示')
    .argument('<start:string>', '開始アドレス')
    .usage('0x083a0ee0')
    .parse(Deno.args);

  const start = Number(args[0]);

  console.log(dump(start));
};

const dump = (start: number): string => {
  const rom = Deno.readFileSync(ROM_PATH);
  const view = new DataView(rom.buffer);

  // MetaspriteHeader0 (最初の2バイトが Metasprite0 へのオフセット つまり, MetaspriteHeader[] のバイト数)
  // MetaspriteHeader1
  // ...
  // Metasprite0
  // Metasprite1
  // ...
  const length = view.getUint16(start - BASE, true) / SIZE;

  const metasprites: Metasprite[] = [];
  for (let i = 0; i < length; i++) {
    const addr = start + (i * SIZE) - BASE;
    const hdr = Hdr.parse(rom.slice(addr, addr + SIZE)) as MetaspriteHdrResult;

    const subsprites: Subsprite[] = [];
    for (let j = 0; j < hdr.len; j++) {
      const addr = start + hdr.ofs + (j * SIZE) - BASE;
      const result = Subsprite.parse(rom.slice(addr, addr + SIZE)) as ParseResult;
      const tileNum = result.props & 0x3ff;
      const xflip = ((result.props & 0x400) >> 10) != 0;
      const yflip = ((result.props & 0x800) >> 11) != 0;
      const size = SUPRITE_SIZE[(result.props >> 12) & 0xF];

      subsprites.push({
        tileNum,
        xflip,
        yflip,
        size,
        x: result.x,
        y: result.y,
      });
    }

    metasprites.push({
      sheetIdx: hdr.sheetIdx,
      subsprites,
    });
  }

  return dumpJson(metasprites);
};

const dumpJson = (metasprites: Metasprite[]): string => {
  // xflip と yflip が false のときは JSON に出力しないようにするための replacer
  const replacer = (key: string, value: unknown) => {
    if (key === 'xflip' || key === 'yflip') {
      return value ? true : undefined;
    }
    return value;
  };

  let output: string = JSON.stringify({ data: metasprites }, replacer, '\t');

  /*
  "size": [
    16,
    32
  ],
  を
  "size": [16, 32],
  のように1行で出力するための正規表現置換
  */
  output = output.replace(
    /"size":\s*\[\s*(-?\d+),\s*(-?\d+)\s*\]/g,
    '"size": [$1, $2]',
  );

  return output;
};

main();
