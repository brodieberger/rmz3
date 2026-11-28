#!/usr/bin/env -S deno run --allow-read --allow-write --allow-run

import { Command } from '@cliffy/command';
import { BASE, ROM_PATH, toHex } from '../common/index.ts';
import { join } from '@std/path';
import { existsSync } from '@std/fs';

const FRAME_TBL = 0x085c0874;
const SEQ_TBL = 0x085d2d48;

const main = async () => {
  const { args, options } = await new Command()
    .name('sprite.ts')
    .version('1.0.0')
    .description('static sprite の metasprite.json と sequence.json をダンプする')
    .argument('<id:number>', 'static sprite の id')
    .option('-o, --output <dir:string>', 'output dir')
    .usage('252 -o ./sprites/static/volteel_human')
    .parse(Deno.args);

  const rom = Deno.readFileSync(ROM_PATH);
  const view = new DataView(rom.buffer);
  const id = Number(args[0]);
  const dir = options.output ?? '';
  if (dir !== '' && !existsSync(dir)) {
    console.error(`output dir not found: ${dir}`);
    Deno.exit(1);
  }

  {
    const addr = view.getUint32(FRAME_TBL + (id * 4) - BASE, true);
    const cmd = new Deno.Command('tools/dumper/sprite/metasprite.ts', {
      args: [`0x${toHex(addr, 8)}`],
      stdout: 'piped',
    });
    const { stdout } = await cmd.output();
    const result = await (new TextDecoder().decode(stdout));
    if (dir.includes('sprites')) {
      const filepath = join(dir, 'metasprite.json');
      Deno.writeTextFileSync(filepath, result);
    } else {
      console.log(result);
    }
  }

  {
    const addr = view.getUint32(SEQ_TBL + (id * 4) - BASE, true);
    const cmd = new Deno.Command('tools/dumper/sprite/sequence.ts', {
      args: [`0x${toHex(addr, 8)}`, `-l=gMotionCmd_SM${id}`],
      stdout: 'piped',
    });
    const { stdout } = await cmd.output();
    const result = await (new TextDecoder().decode(stdout));
    if (dir.includes('sprites')) {
      const filepath = join(dir, 'sequence.json');
      Deno.writeTextFileSync(filepath, result);
    } else {
      console.log(result);
    }
  }
};

main();
