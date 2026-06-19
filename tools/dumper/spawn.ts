#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { BASE, BitField, dumpBitField, getEntityKind, ROM_PATH } from '../common/index.ts';

// spawn.h
const Spawn = {
  // SpawnTemplate.flag, SpawnedEntity.flag
  flag: {
    0: 'SF_RESPAWN',
    1: 'SF_FLAG_1',
    2: 'SF_NO_CULLING',
    3: 'SF_FLAG_3',
    4: 'SF_ZOMBIE',
  } as BitField,
  // SpawnTemplate.attr
  attr: {
    0: 'SA_KNIGHT',
    1: 'SA_STORY_ONLY',
  } as BitField,
  // SpawnTemplate.virusID
  virus: ['VIRUS_NONE', 'VIRUS_BEETANK', 'VIRUS_SWORDY', 'VIRUS_PUFFY'],
};

const Subcommands = {
  // e.g. ./tools/dumper/spawn.ts entity 0x08347dcc 51 > tmp/spawn.txt
  'entity': new Command().name('entity')
    .description(`Print SpawnTemplate array as C initializer list.`)
    .argument('<start_addr:string>', '開始アドレス')
    .argument('<length:number>', 'エントリ数')
    .usage('0x08347dcc 51 > output.bin')
    .action((_, start_addr: string, length: number) => {
      const rom = Deno.readFileSync(ROM_PATH);
      const start = Number(start_addr) - BASE;
      for (let i = 0; i < length; i++) {
        if (i === 0) { // [0] はダミーエントリなのでスキップ
          console.log(`[${i}] = {0},`);
          continue;
        }
        const offset = start + (8 * i);
        const kind = getEntityKind(rom[offset + 1], rom[offset + 2], rom[offset + 3], rom[offset + 4]);
        let result = `[${i}] = {
\t.flag      = ${((i === (length - 1)) && (rom[offset] == 0xF)) ? '0xF' : dumpBitField(rom[offset], Spawn.flag)},
\t.kind      = SpawnEntity(${kind.join(',')}),\n`;
        const attr = rom[offset + 5];
        if (attr !== 0) {
          result += `\t.attr      = ${dumpBitField(rom[offset + 5], Spawn.attr)},\n`;
        }
        const mettaurID = rom[offset + 6];
        if (mettaurID !== 0) {
          result += `\t.mettaurID = ${mettaurID},\n`;
        }
        const virusID = rom[offset + 7];
        if (virusID !== 0) {
          result += `\t.virusID   = ${Spawn.virus[virusID]},\n`;
        }
        result += '},';
        console.log(result);
      }
    }),

  // e.g. ./tools/dumper/spawn.ts point 0x08348004 69 > tmp/spawn_point.txt
  'point': new Command().name('point')
    .description(`Print SpawnPoint array as C initializer list.`)
    .argument('<start_addr:string>', '開始アドレス')
    .argument('<length:number>', 'エントリ数')
    .usage('0x08348004 69')
    .action((_, start_addr: string, length: number) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const start = Number(start_addr) - BASE;
      if (length >= 2) {
        console.log('\t[0] = { -0x80000000, -0x8000, 0 },'); // [0] はダミーエントリなのでスキップ
        for (let i = 1; i < length - 1; i++) {
          const offset = start + (8 * i);
          const x16 = view.getInt32(offset, true);
          const y16 = view.getInt16(offset + 4, true);
          const eid = view.getUint16(offset + 6, true);
          console.log(`\t[${i}] = { SpawnPixelCoords(${x16 * 16}, ${y16 * 16}), ${eid} },`);
        }
        console.log(`\t[${length - 1}] = { 0x7FFFFFFF, 0x7FFF, 0 },`);
      }
    }),

  // e.g. ./tools/dumper/spawn.ts graphic 0x08347f64 20 > tmp/spawn_graphic.txt
  'graphic': new Command().name('graphic')
    .description(`Print PreloadEntity array as C initializer list.`)
    .argument('<start_addr:string>', '開始アドレス')
    .argument('<length:number>', 'エントリ数')
    .usage('0x08347f64 20')
    .action((_, start_addr: string, length: number) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const start = Number(start_addr) - BASE;
      // TODO: implement
    }),
};

const main = async () => {
  await new Command()
    .name('spawn.ts')
    .version('1.0.0')
    .command('entity', Subcommands['entity'])
    .command('point', Subcommands['point'])
    .command('graphic', Subcommands['graphic'])
    .parse(Deno.args);
};

main();
