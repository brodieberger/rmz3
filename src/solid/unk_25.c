#include "collision.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"

// AreaX2 と WeilLabo の動く足場
// TODO: "./platform_weil_labo.c" が 本当に WeilLabo の足場かチェックする

static void Solid25_Init(struct Solid* p);
static void Solid25_Update(Object* p);
static void Solid25_Die(void* _ UNUSED);

// clang-format off
const SolidRoutine gSolid25Routine = {
    [ENTITY_INIT] =      (void*)Solid25_Init,
    [ENTITY_UPDATE] =    (void*)Solid25_Update,
    [ENTITY_DIE] =       (void*)Solid25_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

static void Solid25_Init(struct Solid* p) {
  static const struct Rect size = {PIXEL(0), PIXEL(24), PIXEL(32), PIXEL(48)};

  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = (struct Rect*)&size;
  (p->s).hazardAttr = 0x2001;
  (p->s).coord.x += PIXEL(8);
  (p->s).unk_coord.y = (p->s).coord.y - PIXEL(8);
  if ((p->s).work[1] == 0) {
    SetMotion(&p->s, MOTION(SM124_AREA_X2_PLATFORM, 1));
  } else {
    SetMotion(&p->s, MOTION(SM125_WEILLABO_PLATFORM, 0));
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid25_Update((void*)p);
}

static void Solid25_Update(Object* p) {
  u16 val;
  u32 tmp = (p->s).work[0] * 64;
  if (((gOverworld.terrain.id & 0x7F) == STAGE_AREA_X2) || ((gOverworld.terrain.id & 0x7F) == STAGE_WEILS_LABO)) {
    tmp += gOverworld.work.areaX2.unk_008;
  }

  // 足場を上下に動かす
  val = tmp;
  val &= 0xFF;
  if (val < 0x80) {
    s32 y = (val * 0xC0) - PIXEL(48);
    (p->s).coord.y = (p->s).unk_coord.y + y;
  } else {
    s32 y = ((val - 0x80) * 0xC0) - PIXEL(48);
    (p->s).coord.y = (p->s).unk_coord.y - y;
  }
  UpdateMotionGraphic(&p->s);
}

static void Solid25_Die(void* _) {}
