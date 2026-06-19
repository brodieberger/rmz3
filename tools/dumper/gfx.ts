#!/usr/bin/env -S deno run --allow-read --allow-write --allow-run

import { Command } from '@cliffy/command';
import { BASE, ROM_PATH } from '../common/index.ts';

/*
  xxx.lz.png:        LZ77 compressed image
  xxx.lz.8bpp.png:   LZ77 compressed image(8bpp)
  xxx.notrim.png:    If the last tile in the data is a transparent tile, that tile is normally removed, but `.notrim` prevents that.
  xxx.notrim.lz.png: LZ77 compressed image version for `.notrim.png`
*/

const GBAGFX = './tools/gbagfx/gbagfx';

// e.g. ./tools/dumper/gfx.ts -w=9 0x08547514 tmp/output.png
// 処理の流れ
// 1. 引数で渡したアドレスの指すGraphic構造体を読み取って、グラフィックデータ(.bpp) と パレットデータ(.gbapal) をダンプ
// 2. それを使って、GBAGFXを呼び出して、pngを作成
// 3. GBAGFX に渡すために用意した グラフィックデータ(.bpp) と パレットデータ(.gbapal) を削除
const main = async () => {
  const { args, options } = await new Command()
    .name('gfx.ts')
    .version('1.0.0')
    .description(
      `Graphic構造体 のアドレスを与えると、それの指すグラフィックデータ と パレットデータ を ダンプし、それを使って、GBAGFXで利用可能なpngを作成します。
LZ77圧縮されている場合は、output に .lz   をつけてください e.g. output.lz.png
8BPPフォーマットの場合は、output に .8bpp をつけてください e.g. output.lz.8bpp.png`,
    )
    .option('-w, --width=[n]', 'image width(not px but tile)', { default: 1 })
    .option('--nodiscard', '中間生成物(.bpp, .gbapal)を削除しない', { default: false })
    .option('-p, --pal=[s:string]', 'use specified gbapal')
    .option('-g, --grayscale', 'use grayscale palettes')
    .option('-z, --zero', 'use zero palettes')
    .option('-W, --weapon', 'use weapon palettes')
    .argument('<addr:string>', 'Graphic or ColorGraphic 構造体のアドレス')
    .argument('<output:string>', '出力先のpngファイルパス')
    .usage('0x08547550 output.png')
    .parse(Deno.args);

  const rom = Deno.readFileSync(ROM_PATH);
  const view = new DataView(rom.buffer);

  const addr = Number(args[0]);
  const offset = addr - BASE;

  const gfx = {
    src: view.getUint32(offset, true) + addr,
    size: view.getUint16(offset + 4, true),
    pal: view.getUint32(offset + 12, true) + (addr + 12),
    palSize: view.getUint16(offset + 16, true),
  };

  const outputPath = args[1];
  const isLz77 = outputPath.includes('.lz.'); // e.g. ".lz.png"
  const bpp = outputPath.includes('.8bpp.') ? 8 : 4; // e.g. ".lz.8bpp.png"
  const bppPath = args[1].replaceAll('.png', `.${bpp}bpp`);

  // GBAGFX に必要な パレットデータ をROMから取り出す
  let pal: Uint8Array;
  let palPath: string;
  let usePredefPalettes = false;
  if (options.grayscale) {
    palPath = './tools/dumper/grayscale.gbapal';
    usePredefPalettes = true;
  } else if (options.zero) {
    palPath = './tools/dumper/zero.gbapal';
    usePredefPalettes = true;
  } else if (options.weapon) {
    palPath = './tools/dumper/weapon.gbapal';
    usePredefPalettes = true;
  } else if (options.pal) {
    palPath = options.pal as string;
    usePredefPalettes = true;
  } else {
    palPath = args[1].replaceAll('.png', '.gbapal');
    pal = rom.slice(gfx.pal - BASE, gfx.pal - BASE + gfx.palSize);
    switch (bpp) {
      case 4: {
        if (pal.byteLength > 16 * 2) {
          // deno-fmt-ignore
          const dst = palPath.replaceAll(isLz77 ? ".lz.gbapal" : ".gbapal", "_2.pal");
          Deno.writeFileSync(dst, pal.slice(32));
          pal = pal.slice(0, 32);
        }
        break;
      }
      case 8: {
        if (pal.byteLength < (256 * 2)) {
          // deno-fmt-ignore
          const dst = palPath.replaceAll(isLz77 ? ".lz.gbapal" : ".gbapal", "_2.pal");
          Deno.writeFileSync(dst, pal.slice(512));
          const old = [...pal];
          pal = new Uint8Array(512);
          pal.set(old, 0);
        }
        break;
      }
    }
    Deno.writeFileSync(palPath, pal);
  }

  if (isLz77) {
    // dump as LZ77
    const lz77Path = args[1].replaceAll('.png', '.lz');
    const lz77 = rom.slice(gfx.src - BASE, gfx.src - BASE + gfx.size);
    Deno.writeFileSync(lz77Path, lz77);

    // decompress LZ77 into 4bpp
    const cmd = new Deno.Command(GBAGFX, { args: [lz77Path, bppPath] }); // $ gbagfx xxx.lz xxx.4bpp
    await cmd.output();
    Deno.removeSync(lz77Path);
  } else {
    // dump as 4BPP
    const data = rom.slice(gfx.src - BASE, gfx.src - BASE + gfx.size);
    Deno.writeFileSync(bppPath, data);
  }

  // create png
  const cmd = new Deno.Command(GBAGFX, { args: [bppPath, args[1], `-width ${options.width}`, `-palette ${palPath}`] }); // $ gbagfx xxx.4bpp xxx.png -width 6 -palette xxx.gbapal
  await cmd.output();

  // 中間ファイルの削除
  if (!options.nodiscard) {
    Deno.removeSync(bppPath); // .bpp ファイルは GBAGFXでpngを作成した後は不要
    if (!usePredefPalettes) {
      Deno.removeSync(palPath);
    }
  }
};

main();
