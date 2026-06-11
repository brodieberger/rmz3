#include "global.h"
#include "vfx.h"

// 旧居住区などの蔦の燃える炎のエフェクト
// メインは solid/burning_flame.c だが、 Solid のスロットに余裕がないときはこの VFX を代わりに生成する

s16 FUN_080cb528(struct Entity* p);
void FUN_080cb4c0(struct Entity* p);

static void Ghost29_Init(struct Entity* p);
static void Ghost29_Update(struct Entity* p);
static void Ghost29_Die(void* _ UNUSED);

// clang-format off
const VFXRoutine gBurningFlameFXRoutine = {
    [ENTITY_INIT] =      (void*)Ghost29_Init,
    [ENTITY_UPDATE] =    (void*)Ghost29_Update,
    [ENTITY_DIE] =       (void*)Ghost29_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
}; // 0x0836ebb8
// clang-format on

static void Ghost29_Init(struct Entity* p) {
  p->flags |= FLIPABLE;
  FUN_080cb4c0(p);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost29_Update(p);
}

static void Ghost29_Update(struct Entity* p) {
  if (!FUN_080cb528(p)) {
    p->flags &= ~DISPLAY;
    p->flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

static void Ghost29_Die(void* _) {}
