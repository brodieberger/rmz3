#ifndef GUARD_RMZ3_OW_QUAKE_H
#define GUARD_RMZ3_OW_QUAKE_H

#include "common.h"
#include "gba/gba.h"

typedef struct {
  u32 power;
  Coords32 c;
} Quake;
static_assert(sizeof(Quake) == 12);

// 020300f0
struct QuakeManager {
  u32 rng;
  Quake quakes[17];
  Quake unk_0d0[17];
  u16 length;  // 020300f4 の有効な配列の長さ
  u16 frame;   // 揺れ始めから経過したフレーム
  s32 power;
  u16 unk_1a4;
  u16 unk_1a6;
};  // 424 bytes
static_assert(sizeof(struct QuakeManager) == 424);

extern struct QuakeManager gQuakeManager;

void ClearQuakeManager(void);
void AppendQuake(u8 power, Coords32* c);
void CalcQuake(Coords32* _, Coords32* ofs);
s32 quake_0801acdc(Coords32* _);

#endif  // GUARD_RMZ3_OW_QUAKE_H
