#ifndef __INCLUDE_BOSS_OMEGA1_H__
#define __INCLUDE_BOSS_OMEGA1_H__

#include "entity/entity.h"
#include "gba/gba.h"

struct Omega1 {
  OBJECT_HDR;
  // props (48bytes, offset: 0xB4..)
  u8 unk_b4[4];
  s32 unk_y;
  struct Entity* unk_bc;  // omegaWhite_080b91d4
  u16 unk_c0;
  u8 unk_c2[18];
  u32 unk_d4;
  u8 unk_d8[12];
};
static_assert(sizeof(struct Omega1) == sizeof(struct Boss));

#endif  // __INCLUDE_BOSS_OMEGA1_H__
