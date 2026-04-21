#include "entity.h"
#include "global.h"
#include "vfx.h"

// Cattatank の残骸?

static void Ghost75_Init(struct Entity* p);
static void Ghost75_Update(struct Entity* p);
static void Ghost75_Die(struct Entity* p);

// clang-format off
const VFXRoutine gGhost75Routine = {
    [ENTITY_INIT] =      (void*)Ghost75_Init,
    [ENTITY_UPDATE] =    (void*)Ghost75_Update,
    [ENTITY_DIE] =       (void*)Ghost75_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Entity* FUN_080c7518(struct Coord* c, u8 n) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_075);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = n, p->work[1] = 0;
    p->coord.x = c->x, p->coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080c7570(struct Coord* c, u8 n, u16 r2, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_075);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = n, (p->s).work[1] = 1;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->props).unk28.unk_0 = r2;
    (p->props).unk28.unk_4 = y;
  }
  return p;
}

// --------------------------------------------

static void Ghost75_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  p->flags |= DISPLAY;
  p->flags |= FLIPABLE;
  if (p->work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }

  if (p->work[0] == 0) {
    (p->d).x = -PIXEL(1) / 2;
  } else {
    (p->d).x = PIXEL(1) / 2;
  }
  (p->d).y = 0;

  if (p->work[1] == 0) {
    p->work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    p->mode[1] = 1, p->mode[2] = 0, p->mode[3] = 0;
  } else {
    RNG_0202f388 = LCG(RNG_0202f388);
    p->work[2] = 96 + ((RNG_0202f388 >> 16) & 7);
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    p->mode[1] = 2, p->mode[2] = 0, p->mode[3] = 0;
  }
  Ghost75_Update((void*)p);
}

static void nop_080c76fc(void* _ UNUSED);
void FUN_080c7700(struct VFX* p);
void FUN_080c77f0(struct VFX* p);

static void Ghost75_Update(struct Entity* p) {
  static const VFXFunc sUpdates[3] = {
      (void*)nop_080c76fc,
      (void*)FUN_080c7700,
      (void*)FUN_080c77f0,
  };
  (sUpdates[(p->mode)[1]])((void*)p);
}

static void Ghost75_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080c76fc(void* _) {}

INCASM("asm/vfx/unk_75.inc");

// --------------------------------------------

const s32 s32_ARRAY_0836f8c0[24] = {
    0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160,
};

const s32* const PTR_ARRAY_0836f920[3] = {
    &s32_ARRAY_0836f8c0[0],
    &s32_ARRAY_0836f8c0[8],
    &s32_ARRAY_0836f8c0[16],
};
