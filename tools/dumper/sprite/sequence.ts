#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { BASE, ROM_PATH } from '../../common/index.ts';

const SIZE = 4;

type AnimCmd = {
  frameIdx: number;
  duration: number;
};

const main = async () => {
  const { args, options } = await new Command()
    .name('sequence.ts')
    .version('1.0.0')
    .description('開始アドレス(start) から 長さNだけ、 JSONのMotionCmd構造体として標準出力に表示します。')
    .arguments('<start>')
    .option('-l, --label=[s:string]', 'label name')
    .usage('0x083b5864')
    .parse(Deno.args);

  const rom = Deno.readFileSync(ROM_PATH);
  const view = new DataView(rom.buffer);
  const start = Number(args[0]);
  const length = (view.getUint32(start - BASE, true) - start) / SIZE;

  const result: AnimCmd[][] = [];
  for (let i = 0; i < length; i++) {
    let idx = 0;

    const arr = view.getUint32((start + (SIZE * i)) - BASE, true) - BASE;
    const seq: AnimCmd[] = [];
    for (;;) {
      const frameIdx = rom[arr + (idx * 2) + 0];
      const duration = rom[arr + (idx * 2) + 1];
      seq.push({ frameIdx, duration });
      if (duration === 254 || duration === 255) {
        break;
      }
      idx++;
    }
    result.push(seq);
  }

  if (options.label && options.label !== '') {
    console.log(JSON.stringify({ label: options.label, data: result }, null, 2));
  } else {
    console.log(JSON.stringify({ data: result }, null, 2));
  }
};

main();
