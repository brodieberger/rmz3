#ifndef GUARD_RMZ3_ENTITY_SOLID_H
#define GUARD_RMZ3_ENTITY_SOLID_H

#include "entity/entity.h"

struct Solid {
  struct Entity s;
  struct Body body;  // 0x74
  // 0xB4..
  union {
    u8 raw[16];
  } props;
};  // 196 bytes

typedef void (*SolidFunc)(struct Solid*);

#endif  // GUARD_RMZ3_ENTITY_SOLID_H
