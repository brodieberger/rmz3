import { BASE, Nullable, toHex } from '../../common/index.ts';
import { charmap, charmapF0 } from './charmap.ts';

export class StringBuilder {
  #buf: DataView;
  #maxLength = 0x1000; // 終端文字が見つからなくて無限ループするのを防止するための最大長

  // Context
  #start = 0;
  #length = 0;

  constructor(buf: DataView) {
    this.#buf = buf;
  }

  // start is ROM offset (= GBA_address - BASE)
  decode(start: number, terminate: number = 0xFF): [string, number] {
    const err = this.#read(start, terminate);
    if (err) {
      console.warn(`Failed to decode string: ${err}`);
      return ['', -1];
    }
    return [this.#decode(), this.#length];
  }

  #read(start: number, terminate: number = 0xFF): Nullable<string> {
    if (start >= BASE) {
      return `Expected ROM offset, but got GBA address: 0x${toHex(start, 8)}`;
    }

    this.#start = start;
    for (let i = 0; i < this.#maxLength; i++) {
      const byte = this.#buf.getUint8(start + i);
      if (byte === terminate) {
        this.#length = i + 1;
        return null;
      }
    }

    return `Failed to find terminate character 0x${toHex(terminate, 2)} within max length ${this.#maxLength}`;
  }

  #decode(): string {
    let result = '';

    let isF0 = false;
    let isF3 = false;
    let isF4 = false;
    let isF5 = false;
    let isF6 = false;

    let offset = this.#start;
    const end = this.#start + this.#length;

    while (offset < end) {
      const byte = this.#buf.getUint8(offset);
      offset++;

      if (byte === 0xF0) {
        if (isF3) {
          console.warn(`Unexpected F0 after F3 at 0x${toHex(offset, 8)}`);
        }
        isF0 = true;
        continue;
      }
      if (byte === 0xF3) {
        if (isF0) {
          console.warn(`Unexpected F3 after F0 at 0x${toHex(offset, 8)}`);
        }
        isF3 = true;
        continue;
      }
      if (byte === 0xF4) {
        isF4 = true;
        continue;
      }
      if (byte === 0xF5) {
        isF5 = true;
        continue;
      }
      if (byte === 0xF6) {
        if (isF0 || isF3) {
          console.warn(`Unexpected F6 after F0 or F3 at 0x${toHex(offset, 8)}`);
        }
        isF6 = true;
        continue;
      }

      if (byte === 0xDA) {
        const next = this.#buf.getUint8(offset);
        if (next === 0xDC) {
          result += '✚';
          offset++;
          continue;
        }
      }

      let char: string;
      if (isF0) {
        char = Object.entries(charmapF0).find(([_, v]) => v === byte)?.[0] || '';
        isF0 = false;
      } else if (isF3) {
        char = `{WINDOW 0x${toHex(byte, 2)}}`;
        isF3 = false;
      } else if (isF4) {
        char = `{ANSWER 0x${toHex(byte, 2)}}`;
        isF4 = false;
      } else if (isF5) {
        char = `{F5 0x${toHex(byte, 2)}}`;
        isF5 = false;
      } else if (isF6) {
        char = `{F6 0x${toHex(byte, 2)}}`;
        isF6 = false;
      } else {
        char = Object.entries(charmap).find(([_, v]) => v === byte)?.[0] || '';
      }

      if (!char) {
        console.warn(`Unknown char: 0x${toHex(byte, 2)} at 0x${toHex(BASE + offset - 1, 8)}`);
        return '';
      }
      result += char;
    }

    return result;
  }

  format(s: string): string {
    let result = '';

    s.split('\n').forEach((line) => {
      if (!line.endsWith('$')) {
        result += `\t.string "${line}\\n"\n`;
      } else {
        result += `\t.string "${line}"`;
      }
    });

    return result;
  }

  formatWindow(s: string): string {
    let result = '';

    let line = '';

    const chars = [...s];

    let i = 0;
    while (i < chars.length) {
      const char = chars[i];
      i++;

      if (char === '{' && chars.slice(i, i + 7).join('') === 'WINDOW ') {
        const endIndex = chars.indexOf('}', i);
        if (endIndex === -1) {
          console.warn(`Failed to parse {WINDOW ...}: missing closing }`);
          return '';
        }
        const content = chars.slice(i, endIndex).join('');
        result += `\t.string "{${content}}"\n`;
        i = endIndex + 1;
        continue;
      }

      if (char === '\n') {
        result += `\t\t.string "${line}\\n"\n`;
        line = '';
      } else if (char === '▼') {
        result += `\t\t.string "${line}▼"\n`;
        line = '';
      } else {
        line += char;
      }
    }

    if (line) {
      result += `\t\t.string "${line}"`;
    }
    return result;
  }
}
