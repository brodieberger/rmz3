#ifndef __INCLUDE_BOSS_COPY_X_H__
#define __INCLUDE_BOSS_COPY_X_H__

#include "entity/entity.h"
#include "gba/gba.h"

struct BossCopyX {
  OBJECT_HDR;
  // props (48bytes, offset: 0xB4..)
  u8 unk_b4[16];
  u8 unk_c4;
  u8 unk_c5;
  u8 unk_c6;  // 0xC6, FUN_080a9dcc で使用
  u8 unk_c7;
  u8 unk_c8[20];
  u8 unk_dc;
  s8 unk_dd;
  u8 unk_de[6];
};
static_assert(sizeof(struct BossCopyX) == sizeof(struct Boss));

#endif  // __INCLUDE_BOSS_COPY_X_H__
