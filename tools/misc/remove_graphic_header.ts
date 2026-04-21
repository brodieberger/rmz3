#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { dirname, extname, join } from '@std/path';
import { existsSync } from '@std/fs';
import { GraphicHeader, SEPARATOR, toHex, VRAM } from '../common/index.ts';

// 2026/04/18: header.json は元々、header.inc が TypeScript(mmz3e) で読み出すのが面倒だったので用意したものだったけど、
//              TypeScript で頑張って header.inc をパースした方がいいと判断して、 header.json を廃止することにした
// これは header.json を header.inc に変換するスクリプトだけど、 header.json を廃止するにあたって、このスクリプトで読みやすい header.inc を生成して、 すべて header.inc にしてから header.json を削除する予定

type JsonData = {
  label?: string;
  data: GraphicHeader[];
};

type GraphicInfo = {
  name: string;
  size: number;
  color: number;
  files: string[];
  hdrOnly: boolean;
  symbolData: string;
  symbolPalette: string;
};

// e.g.
// ./tools/dev/graphic_header.ts sprites/dynamic/zero/idle/sheet/header.json > tmp/header.inc
const main = async () => {
  const { args, options } = await new Command()
    .name('graphic_header.ts')
    .version('1.0.0')
    .description('Create a asm header file from a graphic json folder.')
    .argument('<json:string>', 'header.json のファイルパス')
    .option('--verbose', 'verbose')
    .option('-l, --label=[val:string]', 'Force label', { default: '' })
    .usage('sprites/dynamic/zero/idle/sheet/header.json')
    .parse(Deno.args);

  const source = args[0];
  const base = dirname(source); // e.g. sprites/dynamic/zero/idle/sheet/

  const json = JSON.parse(Deno.readTextFileSync(args[0])) as JsonData;
  const graphics = json.data;
  if (options.verbose) {
    console.error(source); // stderr
    console.error(json); // stderr
  }

  const infos: GraphicInfo[] = [];
  let headerSize = 12;

  const label = options.label || json.label;

  for (let i = 0; i < graphics.length; i++) {
    const g = graphics[i];

    let name: string;
    const ext = extname(g.name);
    switch (ext) {
      case '.4bpp': {
        name = g.name;
        break;
      }
      case '.lz': {
        name = g.name;
        break;
      }
      case '.png': {
        if (g.name.endsWith('.lz.png')) {
          name = g.name.replaceAll('.lz.png', '.lz');
        } else {
          name = g.name.replaceAll('.png', '.4bpp');
        }
        break;
      }
      default: {
        name = g.name;
        break;
      }
    }

    const path = join(base, name);
    if (!existsSync(path)) {
      throw new Error('File not found: ' + path);
    }

    const size = Deno.statSync(path).size;

    let color = 0;
    if (g.palette != null) {
      headerSize = 20;
      color = g.palette.color;
    }

    let files: string[] = [];
    if (g.files != null && g.files.length > 0) {
      files = g.files.map((f) => join(base, f));
    } else {
      files.push(path);
      if (g.palette != null) {
        if (g.palette.color > 0) {
          let palettePath = name.replaceAll('.4bpp.lz', '.gbapal');
          palettePath = palettePath.replaceAll('.4bpp', '.gbapal');
          palettePath = palettePath.replaceAll('.lz', '.lz.gbapal');
          files.push(join(base, palettePath));
        }
      }
    }

    const hdrOnly = g.hdrOnly ?? false;
    infos.push({
      name,
      size: hdrOnly ? 0 : size,
      color,
      files,
      hdrOnly,
      symbolData: `${label}_${i}`,
      symbolPalette: `${label}_${i}_Palettes`,
    });
  }

  const headers: string[] = [];
  for (let i = 0; i < graphics.length; i++) {
    const g = graphics[i];
    const info = infos[i];

    const map2d = g.props.includes('chunked');

    let header = `\t@ Graphic ${i}
\t.4byte ${info.symbolData}-. @ src
\t.4byte ${info.size} | (${g.ofs} << 22) \t@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
\t.2byte ${g.chunkSize}, ${getProps(g)} \t@ rowsize${map2d ? '' : '(unused)'}, props`;

    if (g.palette != null) {
      header += `
\t\t@ Palette
\t\t.4byte ${info.symbolPalette}-. @ src offset
\t\t.2byte ${info.color * 2} @ bytesize
\t\t.byte 0, ${g.palette.id} @ lz77(bool8), dst = PaletteID`;
    }

    headers.push(header);
  }

  let result = '';

  /**
   * .section .rodata
   * .balign 4, 0
   * .global [label]
   * [label]:
   */
  result += `.section .rodata\n.balign 4, 0\n\n.global ${label}\n${label}:\n`;

  result += headers.join('\n\n') + `\n\n${SEPARATOR}\n`;

  infos.forEach((info, i) => {
    result += `\n${info.symbolData}:\n`;
    if (!info.hdrOnly) {
      info.files.forEach((file, i) => {
        result += `\t.incbin "${file}"\n`;
        if (i === 0) {
          result += `\t${info.symbolPalette}:\n`;
        }
      });
    }
  });

  console.log(result);
};

// ['4bpp', 'lz77'] -> "(BPP4 | LZ77)"
const getProps = (g: GraphicHeader): string => {
  const len = g.props.length;
  if (len === 0) {
    return '0';
  }

  let props = 0;
  const labels: string[] = g.props.map((prop) => {
    switch (prop) {
      case '4bpp':
        props |= 0x20;
        return 'BPP4';
      case '8bpp':
        props |= 0x40;
        return 'BPP8';
      case 'lz77':
        props |= 0x02;
        return 'LZ77';
      case 'no_pal':
        props |= 0x04;
        return 'NO_PAL';
      case 'chunked':
        props |= 0x01;
        return 'MAP2D';
    }
  });

  if (len === 1) {
    return labels[0];
  }
  return `(${labels.join(' | ')})`;
};

const sum = (numbers: number[]) => {
  return numbers.reduce((accumulator, current) => accumulator + current, 0);
};

main();
