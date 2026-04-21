#ifndef GUARD_RMZ3_ENTITY_ENEMY_H
#define GUARD_RMZ3_ENTITY_ENEMY_H

#include "entity/entity.h"

// TODO: Solid などの "Object と 16バイトのバッファ" をもつ 196バイトの構造体　として共通化する

struct Enemy {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 props[16];
};  // 196 bytes

typedef void (*EnemyFunc)(struct Enemy*);

#endif  // GUARD_RMZ3_ENTITY_ENEMY_H
