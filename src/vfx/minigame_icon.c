#include "entity.h"
#include "global.h"
#include "vfx.h"

void Ghost77_Init(struct VFX* p);
void Ghost77_Update(struct VFX* p);
void Ghost77_Die(struct VFX* p);

// clang-format off
const VFXRoutine gMinigameIconRoutine = {
    [ENTITY_INIT] =      Ghost77_Init,
    [ENTITY_UPDATE] =    Ghost77_Update,
    [ENTITY_DIE] =       Ghost77_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* CreateMinigameIcon_1(Coords32* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).work[0] = 0;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

INCASM("asm/vfx/minigame_icon.inc");

// --------------------------------------------

void FUN_080c843c(struct VFX* p);
void FUN_080c8488(struct VFX* p);
void FUN_080c8628(struct VFX* p);
void FUN_080c8684(struct VFX* p);
void FUN_080c8744(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[5] = {
    FUN_080c843c,
    FUN_080c8488,
    FUN_080c8628,
    FUN_080c8684,
    FUN_080c8744,
};
// clang-format on

// --------------------------------------------

// 0x0836f998
const motion_t motion_t_ARRAY_0836f998[3] = {
    MOTION(SM014_CHIPICON, 8),
    MOTION(SM014_CHIPICON, 7),
    MOTION(SM014_CHIPICON, 9),
};
