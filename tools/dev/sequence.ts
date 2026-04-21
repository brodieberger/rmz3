#!/usr/bin/env -S deno run --allow-read

import { Command } from '@cliffy/command';

type JsonData = {
  label?: string;
  data: Sequence[];
};

type Sequence = MotionCmd[];

type MotionCmd = {
  frameIdx: number;
  duration: number;
};

// sequence.json (スプライトのアニメーション を記述したもの) から sequence.inc (アセンブリファイル) を生成するスクリプト
// 結果は標準出力に出るので、ファイルに保存したい場合は、リダイレクトしてください
// e.g. ./tools/dev/sequence.ts sprites/dynamic/zero/dash/sequence.json > tmp/sequence.inc
const main = async () => {
  const { args, options } = await new Command()
    .name('sequence.ts')
    .version('1.0.0')
    .description('sequence.json (スプライトのアニメーション を記述したもの) から sequence.inc (アセンブリファイル) を生成するスクリプト')
    .argument('<json:string>', 'sequence.json のファイルパス')
    .option('--verbose', 'verbose')
    .option('-l, --label=[val:string]', 'Force label', { default: '' })
    .usage('sprites/dynamic/zero/dash/sequence.json')
    .parse(Deno.args);

  const json = JSON.parse(Deno.readTextFileSync(args[0])) as JsonData;
  const sequences = json.data;
  if (options.verbose) {
    console.error(json); // stderr
  }

  const sizes = sequences.map((seq) => (seq.length * 2));

  const headers: string[] = [];
  for (let i = 0; i < sequences.length; i++) {
    let ofs = 4 * (sequences.length - i);
    if (i > 0) {
      ofs += sum(sizes.slice(0, i));
    }
    const header = `\t.4byte .+${ofs}`;
    headers.push(header);
  }

  const label = options.label || json.label;

  let result = '';
  /**
   * .section .rodata
   * .balign 4, 0
   * .global [label]
   * [label]:
   */
  result += `.section .rodata\n.balign 4, 0\n\n.global ${label}\n${label}:\n`;

  /**
   * .4byte .+8
   * .4byte .+18
   * ...
   */
  result += headers.join('\n') + '\n';

  /**
   * .byte 0, 2
   * .byte 1, 2
   * .byte 2, 4
   * .byte 3, 4
   * .byte 4, 4
   * .byte 5, 4
   * .byte 2, 254
   * .byte 6, 2
   * .byte 7, 4
   * .byte 0, 255
   */
  sequences.forEach((seq) => {
    seq.forEach((cmd) => {
      result += `\t.byte ${cmd.frameIdx}, ${cmd.duration}\n`;
    });
  });

  result += '\n.balign 4, 0\n';

  console.log(result);
};

const sum = (numbers: number[]) => {
  return numbers.reduce((accumulator, current) => accumulator + current, 0);
};

main();
