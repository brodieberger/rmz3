#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';
import { BASE, ROM_PATH, toHex } from '../../common/index.ts';
import { StringBuilder } from './string.ts';

const Subcommands = {
  // e.g. ./tools/dumper/text/text.ts string 0x08374f40 > tmp/output.txt
  'string': new Command().name('string')
    .description(`Dump RMZ3 string`)
    .argument('<start_addr:string>', '開始アドレス')
    .action((_, start_addr: string) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const sb = new StringBuilder(view);

      const [result] = sb.decode(Number(start_addr) - BASE);
      console.log(sb.format(result));
    }),

  // e.g. ./tools/dumper/text/text.ts batch 0x08373e06 Text_NurseV2_ 20 > tmp/strings.inc
  'batch': new Command().name('batch')
    .description(`Dump RMZ3 string`)
    .argument('<start_addr:string>', '開始アドレス')
    .argument('<prefix:string>', 'ラベルのプレフィックス')
    .argument('<length:number>', 'ダンプする文字列の数')
    .action((_, start_addr: string, prefix: string, length: number) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const sb = new StringBuilder(view);

      let addr = Number(start_addr);
      for (let i = 0; i < length; i++) {
        const [result, length] = sb.decode(addr - BASE);
        if (length === -1) {
          console.warn(`Failed to parse string at 0x${toHex(addr, 8)}`);
          break;
        }
        console.log(`${prefix}${toHex(i, 2)}:: @ 0x${toHex(addr, 8)}`);
        console.log(sb.format(result) + '\n');
        addr += length;
      }
    }),

  // e.g. ./tools/dumper/text/text.ts window 0x083856eb > tmp/window.inc
  'window': new Command().name('window')
    .argument('<start_addr:string>', '開始アドレス')
    .action((_, start_addr: string) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const sb = new StringBuilder(view);
      const [result] = sb.decode(Number(start_addr) - BASE);
      console.log(sb.formatWindow(result));
    }),

  // e.g. ./tools/dumper/text/text.ts table 0x08376920 219 > tmp/00xx.inc
  'table': new Command().name('table')
    .description(`batch for window`)
    .argument('<start_addr:string>', 'TextOfs_XXX の開始アドレス')
    .argument('<length:number>', 'TextOfs_XXX のエントリ数')
    .action((_, start_addr: string, length: number) => {
      const view = new DataView(Deno.readFileSync(ROM_PATH).buffer);
      const sb = new StringBuilder(view);

      const base = Number(start_addr) - BASE;
      const start = base + (length * 2); // e.g. 0x08376ad6 - BASE

      const text = {
        offset: -1,
        text: '',
        ids: [] as number[],
      };

      let offset_table_string = '';
      for (let i = 0; i < length; i++) {
        if ((i & 7) === 0) offset_table_string += `\t.2byte `;
        offset_table_string += `(Text${i}-Start), `;
        if ((i & 7) === 7) offset_table_string = offset_table_string.slice(0, -2) + '\n';
      }
      console.log(offset_table_string);
      console.log('');

      for (let i = 0; i < length; i++) {
        const offset = start + view.getUint16(base + (i * 2), true);

        let newText = false;
        if (text.offset === -1) {
          newText = true;
        } else if (offset === text.offset) {
          text.ids.push(i);
        } else {
          const addr_str = `0x${toHex(text.offset + BASE, 8)}`;
          text.ids.forEach((id) => {
            console.log(`Text${id}: @ ${addr_str}`);
          });
          console.log(sb.formatWindow(text.text) + '\n');
          newText = true;
        }

        if (newText) {
          const [result, length] = sb.decode(offset);
          if (length === -1) {
            console.warn(`Failed to parse text${i} at 0x${toHex(offset, 8)}`);
            break;
          }

          text.offset = offset;
          text.text = result;
          text.ids = [i];
        }
      }

      // 最後のテキスト
      if (text.offset !== -1) {
        const addr_str = `0x${toHex(text.offset + BASE, 8)}`;
        text.ids.forEach((id) => {
          console.log(`Text${id}: @ ${addr_str}`);
        });
        console.log(sb.formatWindow(text.text) + '\n');
      }
    }),
};

const main = async () => {
  const { args, cmd } = await new Command()
    .name('text.ts')
    .version('1.0.0')
    .command('string', Subcommands['string'])
    .command('batch', Subcommands['batch'])
    .command('window', Subcommands['window'])
    .command('table', Subcommands['table'])
    .parse(Deno.args);
  if (cmd.getParent()) return;

  // default command
  console.log('default');
};

main();
