#include "global.h"
#include "vfx.h"

// 砕け散る氷(大きめ)

static void VFX57_Init(struct Entity* p);
static void VFX57_Update(struct Entity* p);
static void VFX57_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX57Routine = {
    [ENTITY_INIT] =      (void*)VFX57_Init,
    [ENTITY_UPDATE] =    (void*)VFX57_Update,
    [ENTITY_DIE] =       (void*)VFX57_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void CreateVFX57(Coords32* c, u8 kind1, u8 kind2, s16 dx, s16 dy) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_UNK_057);
    p->work[0] = kind1, p->work[1] = kind2;
    (p->d).x = dx, (p->d).y = dy;
    p->coord = *c;
  }
}

// --------------------------------------------

void FUN_080c19b4(struct Entity* p);
void FUN_080c1a3c(struct Entity* p);

static void VFX57_Init(struct Entity* p) {
  if (p->work[0] == 0) {
    FUN_080c19b4(p);
  } else {
    FUN_080c1a3c(p);
  }
}

void FUN_080c1aec(struct Entity* p);
void FUN_080c1b34(struct Entity* p);

static void VFX57_Update(struct Entity* p) {
  if (p->work[0] == 0) {
    FUN_080c1aec(p);
  } else {
    FUN_080c1b34(p);
  }
}

static void VFX57_Die(struct Entity* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }

INCASM("asm/vfx/unk_57.inc");
