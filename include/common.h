#ifndef GUARD_RMZ3_COMMON_H
#define GUARD_RMZ3_COMMON_H

#include "gba/types.h"

typedef struct {
  s8_8 x;
  s8_8 y;
} Coords16;

// 32bitの座標　
// Overworld では (0, 0) が現在のマップの左上
typedef struct Coord {
  s32 x;
  s32 y;  // y が大きくなると、　画面の下の方を指す
} Coords32;

// ピクセル単位の座標
typedef struct Coord PixelCoords;

struct DrawPivot {
  Coords32 coord;       // = pivot.coord, 描画の基準点の座標(ゲーム中は &Camera.viewport (現在の画面中心の座標))
  PixelCoords lefttop;  // 画面の座標(ピクセル単位)
  Coords32 offset;      // = pivot.offset, 振動エフェクトなどで coord からずれるオフセット
};

struct Pivot {
  Coords32* coord;   // Pivotの座標 (Camera.pivot の場合は、 ResetPivot で &Camera.viewport がセットされる)
  Coords32* offset;  // Pivotのオフセット(基本的に (0, 0) だが、 Camera.pivot の場合は ResetPivot で &Camera.base がセットされ、これは振動で変化する)
  void* _;           // Unused
};

struct BgMapHeader {
  u32 unk_00;
  u16 w;
  u16 h;
};

/*
  (x, y )------------(x+w, y  )
  |                           |
  |                           |
  (x,y+h)------------(x+w, y+h)
*/
struct Rect {
  s8_8 x;  // 0x00
  s8_8 y;  // 0x02
  s8_8 w;  // 0x04
  s8_8 h;  // 0x06
};  // 8 bytes

#endif  // GUARD_RMZ3_COMMON_H
