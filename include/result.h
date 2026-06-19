#ifndef GUARD_RMZ3_RESULT_H
#define GUARD_RMZ3_RESULT_H

#include "global.h"

struct Widget;

struct ResultState {
  u8 mode[4];  // 現在実行する処理を決める
  s16 frame;
  u16 unk_06;
  u16 unk_08;
  u16 unk_0a;
  u32 unk_0c;
  u32 rank;
  void* vfx;
  u8 codenamePrefix;
  u8 codenameSuffix;
  u16 unk_1a;
  u8 unk_1c[8];
  struct Widget* w;
  u8 unk_28[216];
};
static_assert(sizeof(struct ResultState) == 256);

// ------------------------------------------------------------------------------------------------------------------------------------

void ResultScreen_Init(struct ResultState* p);
bool32 ResultScreen_Update(struct ResultState* p);

#endif  // GUARD_RMZ3_RESULT_H
