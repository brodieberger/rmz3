#include "global.h"
#include "vfx.h"

// コピーエックスが変身する際のエフェクト?

static void VFX55_Init(struct VFX* vfx);
static void VFX55_Update(struct VFX* vfx);
static void VFX55_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX55Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX55_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX55_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX55_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateVFX55(struct Boss* e, u8 r1, u8 r2) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_055);
    p->tileNum = 0, p->palID = 0;
    p->unk_28 = (void*)e;
    p->work[0] = r1, p->work[1] = r2;
  }
  return p;
}

// --------------------------------------------

static void FUN_080c11e0(struct VFX* vfx);
void FUN_080c123c(struct VFX* vfx);
void FUN_080c12b0(struct VFX* vfx);

static void VFX55_Init(struct VFX* vfx) {
  static const VFXFunc sInitializers[3] = {
      FUN_080c11e0,
      FUN_080c123c,
      FUN_080c12b0,
  };

  SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
  InitNonAffineMotion(&vfx->s);
  (vfx->s).flags |= DISPLAY;
  (vfx->s).flags |= FLIPABLE;
  (sInitializers[(vfx->s).work[0]])(vfx);
  VFX55_Update(vfx);
}

// --------------------------------------------

void FUN_080c1328(struct VFX* vfx);
void FUN_080c13c8(struct VFX* vfx);
void FUN_080c143c(struct VFX* vfx);

static void VFX55_Update(struct VFX* vfx) {
  static const VFXFunc sUpdates[3] = {
      FUN_080c1328,
      FUN_080c13c8,
      FUN_080c143c,
  };
  (sUpdates[(vfx->s).work[0]])(vfx);
}

// --------------------------------------------

static void VFX55_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// --------------------------------------------

static void FUN_080c11e0(struct VFX* vfx) {
  struct Entity* copyx = (vfx->s).unk_28;
  (vfx->s).flags &= ~DISPLAY;
  SetMotion(&vfx->s, MOTION(SM097_COPYX_UNK, 2));
  UpdateMotionGraphic(&vfx->s);
  SET_XFLIP(vfx, FALSE);
  (vfx->s).spr.oam.priority = 3;
  (vfx->s).coord = copyx->coord;
  (vfx->s).work[2] = 42;
}

INCASM("asm/vfx/unk_55.inc");
