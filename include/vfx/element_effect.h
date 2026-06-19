#ifndef __INCLUDE_VFX_ELEMENT_EFFECT_H__
#define __INCLUDE_VFX_ELEMENT_EFFECT_H__

#include "entity/entity.h"
#include "gba/gba.h"

struct ElementEffect {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  Coords32 c;
  u8 unk_8[8];
};  // 132 bytes
static_assert(sizeof(struct ElementEffect) == sizeof(struct VFX));

#endif  // __INCLUDE_VFX_ELEMENT_EFFECT_H__
