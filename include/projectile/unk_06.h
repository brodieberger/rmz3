#ifndef __INCLUDE_PROJECTILE_UNK_06_H__
#define __INCLUDE_PROJECTILE_UNK_06_H__

#include "entity/entity.h"
#include "gba/gba.h"

struct LamplortFlame {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u32 unk_b4;
  u8 unk_b8[12];
};  // 132 bytes
static_assert(sizeof(struct LamplortFlame) == sizeof(Object) + 16);

#endif  // __INCLUDE_PROJECTILE_UNK_06_H__
