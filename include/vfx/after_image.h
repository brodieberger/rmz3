#ifndef __INCLUDE_VFX_AFTER_IMAGE_H__
#define __INCLUDE_VFX_AFTER_IMAGE_H__

#include "entity/entity.h"
#include "gba/gba.h"

struct AfterImage {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  struct Coord c;
  u8 unk_8[8];
};  // 132 bytes
static_assert(sizeof(struct AfterImage) == sizeof(struct Entity) + 16);

struct Entity* CreateAfterImages(struct Entity* p);

#endif  // __INCLUDE_VFX_AFTER_IMAGE_H__
