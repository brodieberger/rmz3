// Frames drawn whole, and packed back into tiles and subsprites. Also loads in node, for tests.
const Core = (() => {
  const SIZES = [[8, 8], [16, 16], [32, 32], [64, 64], [16, 8], [32, 8], [32, 16], [64, 32],
    [8, 16], [8, 32], [16, 32], [32, 64]];
  const BY_AREA = SIZES.map((s, i) => [s, i]).sort((a, b) => b[0][0] * b[0][1] - a[0][0] * a[0][1] || a[1] - b[1]).map(e => e[0]);
  const MARGIN = 16, PAD = 64, MIN_REUSE = 16, SHEET_WIDTH = 32;

  // ---- PNG ------------------------------------------------------------------------------------

  const CRC_TABLE = (() => {
    const t = new Uint32Array(256);
    for (let n = 0; n < 256; n++) {
      let c = n;
      for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1;
      t[n] = c >>> 0;
    }
    return t;
  })();
  function crc32(bytes) {
    let c = 0xffffffff;
    for (let i = 0; i < bytes.length; i++) c = CRC_TABLE[(c ^ bytes[i]) & 0xff] ^ (c >>> 8);
    return (c ^ 0xffffffff) >>> 0;
  }

  // Indexed or RGB(A) PNG -> {width, height, indexed, palette: [[r,g,b]], alpha: Uint8Array per index, pixels}
  // pixels holds palette indices for indexed images, RGBA bytes otherwise.
  async function decodePNG(bytes, inflate) {
    const dv = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
    if (dv.getUint32(0) !== 0x89504e47) throw new Error('not a PNG file');
    let pos = 8, ihdr, palette = [], alpha = null, idat = [];
    while (pos < bytes.length) {
      const len = dv.getUint32(pos), type = String.fromCharCode(...bytes.subarray(pos + 4, pos + 8));
      const data = bytes.subarray(pos + 8, pos + 8 + len);
      if (type === 'IHDR') ihdr = {
        width: dv.getUint32(pos + 8), height: dv.getUint32(pos + 12),
        depth: data[8], color: data[9], interlace: data[12]
      };
      else if (type === 'PLTE') for (let i = 0; i < len; i += 3) palette.push([data[i], data[i + 1], data[i + 2]]);
      else if (type === 'tRNS') alpha = data.slice();
      else if (type === 'IDAT') idat.push(data);
      else if (type === 'IEND') break;
      pos += 12 + len;
    }
    if (ihdr.interlace) throw new Error('the PNG is interlaced. Save it again with interlacing off.');
    const channels = { 0: 1, 2: 3, 3: 1, 4: 2, 6: 4 }[ihdr.color];
    if (!channels) throw new Error('unsupported PNG colour type');
    if (ihdr.color !== 3 && ihdr.color !== 0 && ihdr.depth !== 8) throw new Error('only 8-bit RGB PNGs are supported');
    const total = idat.reduce((n, d) => n + d.length, 0), z = new Uint8Array(total);
    let o = 0;
    for (const d of idat) { z.set(d, o); o += d.length; }
    const raw = await inflate(z);
    const bitsPP = ihdr.depth * channels, stride = Math.ceil(ihdr.width * bitsPP / 8), bpp = Math.max(1, bitsPP >> 3);
    const rows = new Uint8Array(stride * ihdr.height);
    for (let y = 0; y < ihdr.height; y++) {
      const f = raw[y * (stride + 1)], src = raw.subarray(y * (stride + 1) + 1, (y + 1) * (stride + 1));
      const row = rows.subarray(y * stride, (y + 1) * stride), up = y ? rows.subarray((y - 1) * stride, y * stride) : null;
      for (let i = 0; i < stride; i++) {
        const a = i >= bpp ? row[i - bpp] : 0, b = up ? up[i] : 0, c = up && i >= bpp ? up[i - bpp] : 0;
        let v = src[i];
        if (f === 1) v += a;
        else if (f === 2) v += b;
        else if (f === 3) v += (a + b) >> 1;
        else if (f === 4) { const p = a + b - c, pa = Math.abs(p - a), pb = Math.abs(p - b), pc = Math.abs(p - c); v += pa <= pb && pa <= pc ? a : pb <= pc ? b : c; }
        row[i] = v & 0xff;
      }
    }
    const { width, height } = ihdr;
    if (ihdr.color === 3) {
      const pixels = new Uint8Array(width * height), per = 8 / ihdr.depth, mask = (1 << ihdr.depth) - 1;
      for (let y = 0; y < height; y++) for (let x = 0; x < width; x++) {
        const byte = rows[y * stride + Math.floor(x / per)];
        pixels[y * width + x] = (byte >> ((per - 1 - x % per) * ihdr.depth)) & mask;
      }
      return { width, height, indexed: true, palette, alpha, pixels };
    }
    const rgba = new Uint8Array(width * height * 4);
    for (let i = 0; i < width * height; i++) {
      const s = rows.subarray(Math.floor(i / width) * stride + (i % width) * channels);
      if (channels >= 3) { rgba[i * 4] = s[0]; rgba[i * 4 + 1] = s[1]; rgba[i * 4 + 2] = s[2]; }
      else { const g = ihdr.depth === 8 ? s[0] : 0; rgba[i * 4] = rgba[i * 4 + 1] = rgba[i * 4 + 2] = g; }
      rgba[i * 4 + 3] = channels === 4 ? s[3] : channels === 2 ? s[1] : 255;
    }
    return { width, height, indexed: false, palette, alpha, pixels: rgba };
  }

  // A 4-bit indexed PNG, the format the build's gbagfx reads. Stored (uncompressed) zlib blocks.
  function encodePNG(width, height, pixels, palette, transparentZero) {
    const stride = Math.ceil(width / 2), raw = new Uint8Array((stride + 1) * height);
    for (let y = 0; y < height; y++) for (let x = 0; x < width; x++)
      raw[y * (stride + 1) + 1 + (x >> 1)] |= (pixels[y * width + x] & 15) << (x & 1 ? 0 : 4);
    const blocks = Math.max(1, Math.ceil(raw.length / 65535)), z = new Uint8Array(2 + raw.length + blocks * 5 + 4);
    z[0] = 0x78; z[1] = 0x01;
    let o = 2;
    for (let b = 0; b < blocks; b++) {
      const chunk = raw.subarray(b * 65535, Math.min(raw.length, (b + 1) * 65535));
      z[o] = b === blocks - 1 ? 1 : 0; z[o + 1] = chunk.length & 0xff; z[o + 2] = chunk.length >> 8;
      z[o + 3] = ~chunk.length & 0xff; z[o + 4] = (~chunk.length >> 8) & 0xff;
      z.set(chunk, o + 5); o += 5 + chunk.length;
    }
    let s1 = 1, s2 = 0;
    for (const v of raw) { s1 = (s1 + v) % 65521; s2 = (s2 + s1) % 65521; }
    new DataView(z.buffer).setUint32(o, ((s2 << 16) | s1) >>> 0);
    const ihdr = new Uint8Array(13);
    new DataView(ihdr.buffer).setUint32(0, width); new DataView(ihdr.buffer).setUint32(4, height);
    ihdr[8] = 4; ihdr[9] = 3;
    const plte = new Uint8Array(48);
    palette.slice(0, 16).forEach((c, i) => plte.set(c, i * 3));
    const chunks = [['IHDR', ihdr], ['PLTE', plte]];
    if (transparentZero) chunks.push(['tRNS', new Uint8Array([0])]);
    chunks.push(['IDAT', z], ['IEND', new Uint8Array(0)]);
    const size = 8 + chunks.reduce((n, [, d]) => n + 12 + d.length, 0), out = new Uint8Array(size), dv = new DataView(out.buffer);
    out.set([0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a]);
    let p = 8;
    for (const [type, data] of chunks) {
      dv.setUint32(p, data.length);
      const body = new Uint8Array(4 + data.length);
      body.set([...type].map(ch => ch.charCodeAt(0))); body.set(data, 4);
      out.set(body, p + 4); dv.setUint32(p + 8 + data.length, crc32(body)); p += 12 + data.length;
    }
    return out;
  }

  // ---- The sprite ------------------------------------------------------------------------------

  // An indexed image: {w, h, px: Uint8Array of palette indices}.
  function img(w, h) { return { w, h, px: new Uint8Array(w * h) }; }

  function tileOf(sheet, n) {
    const per = sheet.w / 8, tx = (n % per) * 8, ty = Math.floor(n / per) * 8, t = img(8, 8);
    for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) t.px[y * 8 + x] = sheet.px[(ty + y) * sheet.w + tx + x] ?? 0;
    return t;
  }

  function pieceImage(sheet, s) {
    const [w, h] = s.size, cw = w / 8, p = img(w, h);
    for (let j = 0; j < cw * (h / 8); j++) {
      const t = tileOf(sheet, s.tileNum + j), bx = (j % cw) * 8, by = Math.floor(j / cw) * 8;
      for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) {
        const lx = s.xflip ? w - 1 - (bx + x) : bx + x, ly = s.yflip ? h - 1 - (by + y) : by + y;
        p.px[ly * w + lx] = t.px[y * 8 + x];
      }
    }
    return p;
  }

  // Every frame whole, on one canvas with room to grow. origin: the sprite's position on it.
  function unpack(meta, sheets, margin = MARGIN) {
    const boxes = meta.data.flatMap(f => f.subsprites.map(s => [s.x, s.y, s.x + s.size[0], s.y + s.size[1]]));
    const left = Math.min(...boxes.map(b => b[0])) - margin, top = Math.min(...boxes.map(b => b[1])) - margin;
    const width = Math.max(...boxes.map(b => b[2])) + margin - left, height = Math.max(...boxes.map(b => b[3])) + margin - top;
    const frames = meta.data.map(f => {
      const canvas = img(width, height), sheet = sheets[f.sheetIdx];
      for (const s of [...f.subsprites].reverse()) {
        const p = pieceImage(sheet, s);
        for (let y = 0; y < p.h; y++) for (let x = 0; x < p.w; x++) {
          const v = p.px[y * p.w + x], cx = s.x - left + x, cy = s.y - top + y;
          if (v && cx >= 0 && cy >= 0 && cx < width && cy < height) canvas.px[cy * width + cx] = v;
        }
      }
      return canvas;
    });
    return { frames, origin: [-left, -top], sheets: meta.data.map(f => f.sheetIdx) };
  }

  // An edited PNG -> palette indices. Throws a message saying what is wrong with it.
  function toIndices(png, palette, name) {
    const same = png.indexed && palette.slice(0, 16).every((c, i) => png.palette[i] && c.every((v, k) => v === png.palette[i][k]));
    if (same) return { w: png.width, h: png.height, px: png.pixels };
    const out = img(png.width, png.height), lookup = new Map();
    for (let i = 15; i >= 0; i--) lookup.set(palette[i].join(','), i);
    for (let i = 0; i < png.width * png.height; i++) {
      let r, g, b, a;
      if (png.indexed) {
        const k = png.pixels[i], c = png.palette[k] || [0, 0, 0];
        [r, g, b] = c; a = png.alpha && k < png.alpha.length ? png.alpha[k] : 255;
      } else [r, g, b, a] = png.pixels.subarray(i * 4, i * 4 + 4);
      if (a === 0) continue;
      const v = lookup.get(`${r},${g},${b}`);
      if (v === undefined) throw new Error(`${name}: the colour ${r},${g},${b} at x ${i % png.width}, y ${Math.floor(i / png.width)} is not in Zero's palette.`);
      out.px[i] = v;
    }
    return out;
  }

  // ---- Packing ---------------------------------------------------------------------------------

  function padded(frame) {
    const p = img(frame.w + 2 * PAD, frame.h + 2 * PAD);
    for (let y = 0; y < frame.h; y++) p.px.set(frame.px.subarray(y * frame.w, (y + 1) * frame.w), (y + PAD) * p.w + PAD);
    return p;
  }

  function slice(f, x, y, w, h) {
    const a = img(w, h);
    for (let j = 0; j < h; j++) for (let i = 0; i < w; i++) a.px[j * w + i] = f.px[(y + j) * f.w + x + i];
    return a;
  }

  function equal(a, b) {
    if (a.w !== b.w || a.h !== b.h) return false;
    for (let i = 0; i < a.px.length; i++) if (a.px[i] !== b.px[i]) return false;
    return true;
  }

  // The 8x8 cells, on a grid shifted by (gx, gy), holding any pixel still to draw. Keys are "cx,cy".
  function cells(todo, w, h, gx, gy) {
    const found = new Set();
    for (let y = 0; y < h; y++) for (let x = 0; x < w; x++)
      if (todo[y * w + x]) found.add(`${Math.floor((x - gx) / 8)},${Math.floor((y - gy) / 8)}`);
    return found;
  }

  // Split cells into GBA-sized rectangles, largest first, with no empty tiles.
  function cover(todo) {
    const pieces = [];
    for (const [w, h] of BY_AREA) {
      const cw = w / 8, ch = h / 8;
      const order = [...todo].map(k => k.split(',').map(Number)).sort((a, b) => a[1] - b[1] || a[0] - b[0]);
      for (const [cx, cy] of order) {
        let all = true;
        for (let j = 0; j < ch && all; j++) for (let i = 0; i < cw && all; i++) all = todo.has(`${cx + i},${cy + j}`);
        if (!all) continue;
        for (let j = 0; j < ch; j++) for (let i = 0; i < cw; i++) todo.delete(`${cx + i},${cy + j}`);
        pieces.push([cx, cy, w, h]);
      }
    }
    return pieces;
  }

  function flipped(a, xf, yf) {
    const out = img(a.w, a.h);
    for (let y = 0; y < a.h; y++) for (let x = 0; x < a.w; x++)
      out.px[y * a.w + x] = a.px[(yf ? a.h - 1 - y : y) * a.w + (xf ? a.w - 1 - x : x)];
    return out;
  }

  // Every (x, y) where art's opaque pixels are exactly the frame's, in row-major order.
  function matches(frame, art) {
    const solid = [];
    for (let y = 0; y < art.h; y++) for (let x = 0; x < art.w; x++) if (art.px[y * art.w + x]) solid.push(y * frame.w + x, art.px[y * art.w + x]);
    const found = [];
    for (let y = 0; y <= frame.h - art.h; y++) for (let x = 0; x <= frame.w - art.w; x++) {
      const base = y * frame.w + x;
      let ok = true;
      for (let k = 0; k < solid.length && ok; k += 2) ok = frame.px[base + solid[k]] === solid[k + 1];
      if (ok) found.push([x, y]);
    }
    return found;
  }

  // frames: indexed images, all one size. origin: [x, y]. sheetOf: sheet index per frame.
  // -> {data: metasprite frames, sheets: a list of 8x8 tiles per sheet}
  function pack(frames, origin, sheetOf, sheetCount) {
    const [ox, oy] = origin, data = new Array(frames.length), sheetTiles = [];
    for (let sheetIdx = 0; sheetIdx < sheetCount; sheetIdx++) {
      const members = sheetOf.map((s, i) => [s, i]).filter(([s]) => s === sheetIdx).map(([, i]) => i);
      const px = {};
      for (const i of members) px[i] = padded(frames[i]);
      const W = frames[0].w + 2 * PAD, H = frames[0].h + 2 * PAD;
      const solid = i => px[i].px.map(v => v ? 1 : 0);
      let best = null;
      for (let gy = 0; gy < 8; gy++) for (let gx = 0; gx < 8; gx++) {
        const n = members.reduce((t, i) => t + cells(solid(i), W, H, gx, gy).size, 0);
        if (!best || n < best[0]) best = [n, gx, gy];
      }
      const [, gx, gy] = best;
      const block = (i, cx, cy) => slice(px[i], cx * 8 + gx, cy * 8 + gy, 8, 8);
      let common = new Set();
      if (members.length > 1) {
        const sets = members.map(i => cells(solid(i), W, H, gx, gy));
        for (const c of sets[0]) {
          if (!sets.every(s => s.has(c))) continue;
          const [cx, cy] = c.split(',').map(Number), first = block(members[0], cx, cy);
          if (members.every(i => equal(block(i, cx, cy), first))) common.add(c);
        }
      }
      const shared = cover(common), tiles = [], pieces = [];
      const cut = (i, cx, cy, w, h) => {
        const x = cx * 8 + gx, y = cy * 8 + gy, art = slice(px[i], x, y, w, h);
        const same = pieces.find(p => p.size[0] === w && p.size[1] === h && equal(p.art, art));
        if (same) return [same, x, y];
        const piece = { tileNum: tiles.length, size: [w, h], art };
        for (let j = 0; j < h; j += 8) for (let k = 0; k < w; k += 8) tiles.push(slice(art, k, j, 8, 8));
        pieces.push(piece);
        return [piece, x, y];
      };
      for (const i of members) {
        const frame = px[i], todo = solid(i), subsprites = [];
        const draw = (p, xf, yf, x, y, mask) => {
          for (let j = 0; j < mask.h; j++) for (let k = 0; k < mask.w; k++) if (mask.px[j * mask.w + k]) todo[(y + j) * W + x + k] = 0;
          subsprites.push({ tileNum: p.tileNum, xflip: xf, yflip: yf, size: p.size, x: x - PAD - ox, y: y - PAD - oy });
        };
        for (const [cx, cy, w, h] of shared) { const [p, x, y] = cut(i, cx, cy, w, h); draw(p, false, false, x, y, p.art); }
        // Reuse pieces other frames cut, flipped or not, wherever they fit exactly.
        const options = [];
        for (const p of pieces) for (const xf of [false, true]) for (const yf of [false, true]) {
          const art = flipped(p.art, xf, yf), opaque = [];
          for (let j = 0; j < art.h; j++) for (let k = 0; k < art.w; k++) if (art.px[j * art.w + k]) opaque.push(j * W + k);
          for (const [x, y] of matches(frame, art)) options.push({ p, xf, yf, x, y, art, opaque });
        }
        const gain = o => { let n = 0; const base = o.y * W + o.x; for (const d of o.opaque) n += todo[base + d]; return n; };
        while (options.length) {
          let top = options[0], topGain = gain(top);
          for (const o of options) { const g = gain(o); if (g > topGain) { top = o; topGain = g; } }
          if (topGain < MIN_REUSE) break;
          draw(top.p, top.xf, top.yf, top.x, top.y, top.art);
        }
        for (const [cx, cy, w, h] of cover(cells(todo, W, H, gx, gy))) { const [p, x, y] = cut(i, cx, cy, w, h); draw(p, false, false, x, y, p.art); }
        data[i] = { sheetIdx, subsprites };
      }
      sheetTiles.push(tiles);
    }
    return { data, sheets: sheetTiles };
  }

  function sheetImage(tiles) {
    const rows = Math.max(1, Math.ceil(tiles.length / 4)), s = img(SHEET_WIDTH, rows * 8);
    tiles.forEach((t, k) => {
      for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) s.px[(Math.floor(k / 4) * 8 + y) * SHEET_WIDTH + (k % 4) * 8 + x] = t.px[y * 8 + x];
    });
    return s;
  }

  // ---- Text files ------------------------------------------------------------------------------

  function headerSizes(text) { return [...text.matchAll(/\.4byte (\d+) \|/g)].map(m => +m[1]); }

  function rewriteHeader(text, tileCounts) {
    const blocks = text.split(/(?=\t@ Graphic \d+\n)/);
    tileCounts.forEach((count, n) => {
      if (count == null) return;
      const i = blocks.findIndex(b => b.startsWith(`\t@ Graphic ${n}\n`));
      blocks[i] = blocks[i].replace(/\.4byte \d+ \|/, `.4byte ${count * 32} |`).replace(/\.2byte \d+, /, `.2byte ${count * 8}, `);
    });
    return blocks.join('');
  }

  // spritePath is relative to the sprites folder, e.g. "dynamic/zero/idle".
  function rewriteGfxOpts(text, spritePath, tileCounts) {
    const lines = text.replace(/\n$/, '').split('\n');
    tileCounts.forEach((count, n) => {
      if (count == null) return;
      const target = `$(SPRITE_GFX_DIR)/${spritePath}/sheet/${n}.4bpp:`, line = `${target} GFX_OPTS := -num_tiles ${count}`;
      const k = lines.findIndex(l => l.startsWith(target));
      if (k >= 0) lines[k] = line; else lines.push(line);
    });
    return lines.join('\n') + '\n';
  }

  // How many tiles of a sheet actually reach the game: the PNG, cut by any -num_tiles in sprites.mk.
  function builtTiles(mkText, spritePath, n, pngTiles) {
    const m = mkText.split('\n').find(l => l.startsWith(`$(SPRITE_GFX_DIR)/${spritePath}/sheet/${n}.4bpp:`));
    const k = m && m.match(/-num_tiles (\d+)/);
    return k ? Math.min(+k[1], pngTiles) : pngTiles;
  }

  return { SIZES, MARGIN, PAD, decodePNG, encodePNG, unpack, toIndices, pack, sheetImage, headerSizes, rewriteHeader, rewriteGfxOpts, builtTiles, pieceImage, img };
})();
if (typeof module !== 'undefined') module.exports = Core;
