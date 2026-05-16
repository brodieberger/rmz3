#!/usr/bin/env -S deno run --allow-read --allow-write

import { Command } from '@cliffy/command';

const OUTPUT = 'tmp/hardcode.s';

type JsonData = {
  [key: string]: {
    addr: string;
    size: number; // バイト数
    length: number; // 要素数
  };
};

const Subcommands = {
  // e.g. ./tools/misc/hardcode.ts collision asm/boss/volteel.inc 0x08362330 24
  'collision': new Command().name('collision')
    .argument('<srcPath:string>', 'アセンブリファイル')
    .argument('<collisions:string>', 'sCollisions のアドレス')
    .argument('<length:number>', 'sCollisions の要素数')
    .action((_, srcPath: string, collisions: string, length: number) => {
      if (srcPath === '') {
        console.error('asmファイルのパスを指定してください。');
        Deno.exit(1);
      }

      const src = Deno.readTextFileSync(srcPath);
      const lines = src.split('\n');

      const start = Number(collisions);
      const SIZE = 24; // sizeof(struct Collision)
      const end = start + SIZE * length;

      let isModified = false;
      const pattern = /^(\w+):\s+\.4byte\s+(0x08[0-9A-Fa-f]+)$/;
      for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        const match = line.match(pattern);
        if (match) {
          const address = parseInt(match[2], 16);
          if (address >= start && address < end) {
            const offset = address - start;
            const index = Math.floor(offset / SIZE);
            // console.log(`symbol: ${match[1]}, address: ${match[2]}, after: sCollisions+(${index}*24)`);
            // replace the line
            const newLine = `${match[1]}: .4byte sCollisions${index > 0 ? `+(${index}*${SIZE})` : ''}`;
            lines[i] = newLine;
            isModified = true;
          }
        }
      }

      if (isModified) {
        const newSrc = lines.join('\n');
        Deno.writeTextFileSync(OUTPUT, newSrc);
      }
    }),

  // ./tools/misc/hardcode.ts all tmp/hardcode/hardcode.json asm/enemy/seimeran.inc
  'all': new Command().name('all')
    .argument('<jsonPath:string>', 'json のアドレス')
    .argument('<srcPath:string>', 'アセンブリファイル')
    .action((_, jsonPath: string, srcPath: string) => {
      if (srcPath === '') {
        console.error('asmファイルのパスを指定してください。');
        Deno.exit(1);
      }
      if (jsonPath === '') {
        console.error('JSONファイルのパスを指定してください。');
        Deno.exit(1);
      }

      const src = Deno.readTextFileSync(srcPath);
      const lines = src.split('\n');

      const jsondata = JSON.parse(Deno.readTextFileSync(jsonPath)) as JsonData;

      let isModified = false;
      const pattern = /^(\w+):\s+\.4byte\s+(0x08[0-9A-Fa-f]+)$/;
      for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        const match = line.match(pattern);
        if (match) {
          const address = parseInt(match[2], 16);

          for (const key in jsondata) {
            const start = Number(jsondata[key].addr);
            const size = jsondata[key].size;
            const length = jsondata[key].length;
            const end = start + (size * length);
            if (address >= start && address < end) {
              const offset = address - start;
              const index = Math.floor(offset / size);
              const newLine = `${match[1]}: .4byte ${key}${index > 0 ? `+(${index}*${size})` : ''}`;
              lines[i] = newLine;
              isModified = true;
              break;
            }
          }
        }
      }

      if (isModified) {
        const newSrc = lines.join('\n');
        Deno.writeTextFileSync(OUTPUT, newSrc);
      }
    }),
};

const main = async () => {
  await new Command()
    .name('dump.ts')
    .version('1.0.0')
    .command('collision', Subcommands['collision'])
    .command('all', Subcommands['all'])
    .parse(Deno.args);
};

main();
