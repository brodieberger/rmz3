#ifndef GUARD_RMZ3_ELEMENT_H
#define GUARD_RMZ3_ELEMENT_H

#include "gba/types.h"

struct VFX;
struct CollidableEntity;
struct Coord;

enum ElemFX {
  ELFX_NONE = 0,
  ELFX_THUNDER = 1,
  ELFX_FIRE = 2,
  ELFX_ICE = 3,
};

// ElFx = Element Effect
struct ElFxManager {
  u8 current;    // 現在VRAMにロードされているエレメントエフェクトのID (ElemFX)
  u8 requested;  // 次にVRAMにロードするエレメントエフェクトのID (ElemFX)
  u8 delay;
};

extern struct ElFxManager gElFxManager;

void RequestElementEffectGraphic(enum ElemFX elem_fx);
struct VFX* ApplyElementEffect(u8 idx, struct CollidableEntity* p, const struct Coord* c);

#endif  // GUARD_RMZ3_ELEMENT_H
