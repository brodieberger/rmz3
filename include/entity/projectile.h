#ifndef GUARD_RMZ3_ENTITY_PROJECTILE_H
#define GUARD_RMZ3_ENTITY_PROJECTILE_H

#include "entity/entity.h"

// TODO: Solid などの Object と 16バイトのバッファ をもつ 196バイトの 構造体　として共通化する

// 飛び道具だと思ってたけど、特定のエンティティに従属しているエンティティのことを指すかも？
struct Projectile {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 work[4];  // general purpose buffer
  struct Coord prevCoord;
  u32 unk_c0;
};  // 196 bytes

typedef void (*ProjectileFunc)(struct Projectile*);

#endif  // GUARD_RMZ3_ENTITY_PROJECTILE_H
