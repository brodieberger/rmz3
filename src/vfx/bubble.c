#include "global.h"
#include "vfx.h"

// Bubble in the water
struct BubbleVFX {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u8 unk_0[4];  // 0x74
  s32 unk_78;   // 0x78
  u8 unk_8[8];  // 0x7C
};
static_assert(sizeof(struct BubbleVFX) == sizeof(struct VFX));

static void Bubble_Init(struct VFX* p);
static void Bubble_Update(struct BubbleVFX* p);
static void Bubble_Die(struct Entity* p);

// clang-format off
const VFXRoutine gBubbleRoutine = {
    [ENTITY_INIT] =      (void*)Bubble_Init,
    [ENTITY_UPDATE] =    (void*)Bubble_Update,
    [ENTITY_DIE] =       (void*)Bubble_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

void CreateBubble(s32 x, s32 y, u8 kind) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_BUBBLE);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind;
    (p->coord).x = x, (p->coord).y = y;
  }
}

// --------------------------------------------

void FUN_080b2e50(struct VFX* p);
void FUN_080b2ef0(struct VFX* p);
void FUN_080b2f7c(struct VFX* p);
void FUN_080b3024(struct VFX* p);

static void Bubble_Init(struct VFX* p) {
  static const VFXFunc sInitializers[] = {
      FUN_080b2e50,
      FUN_080b2ef0,
      FUN_080b2f7c,
      FUN_080b3024,
  };
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

void FUN_080b30b4(struct VFX* p);
void FUN_080b3144(struct VFX* p);
void FUN_080b31d8(struct VFX* p);
void FUN_080b3278(struct VFX* p);

static void Bubble_Update(struct BubbleVFX* p) {
  static const VFXFunc sUpdates[] = {
      (void*)FUN_080b30b4,
      (void*)FUN_080b3144,
      (void*)FUN_080b31d8,
      (void*)FUN_080b3278,
  };
  if (p->unk_78 != 0) {
    if (p->unk_78-- < 32) {
      if (p->unk_78 & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
    }
  } else {
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).work[0]])((void*)p);
}

static void Bubble_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/bubble.inc");
