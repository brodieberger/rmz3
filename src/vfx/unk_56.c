#include "global.h"
#include "vfx.h"

static void VFX56_Init(struct Entity* p);
static void VFX56_Update(struct Entity* p);
static void VFX56_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX56Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX56_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX56_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX56_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void CreateVFX56(struct Entity* e, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_056);
    p->tileNum = 0, p->palID = 0;
    p->unk_28 = (void*)e;
    p->work[0] = kind1;
    p->work[1] = kind2;
  }
}

// --------------------------------------------

void FUN_080c15d4(struct VFX* vfx);
void FUN_080c161c(struct VFX* vfx);
void FUN_080c16fc(struct VFX* vfx);

static void VFX56_Init(struct Entity* p) {
  static const VFXFunc sInitializers[3] = {
      (VFXFunc)FUN_080c15d4,
      (VFXFunc)FUN_080c161c,
      (VFXFunc)FUN_080c16fc,
  };  // 0x0836f22c

  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(p);
  p->flags |= DISPLAY;
  p->flags |= FLIPABLE;
  SetMotion(p, MOTION(SM096_COPYX_REFLECT_LASER, 1));
  (sInitializers[p->work[0]])((void*)p);
}

void FUN_080c17e8(struct VFX* vfx);
void FUN_080c182c(struct VFX* vfx);
void FUN_080c188c(struct VFX* vfx);

static void VFX56_Update(struct Entity* p) {
  static const VFXFunc sUpdates[3] = {
      (VFXFunc)FUN_080c17e8,
      (VFXFunc)FUN_080c182c,
      (VFXFunc)FUN_080c188c,
  };  // 0x0836f238
  (sUpdates[p->work[0]])((void*)p);
}

static void VFX56_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

INCASM("asm/vfx/unk_56.inc");
