#include "collision.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"
#include "zero.h"

// Weil Reserach Labo's platform

static const struct Collision sCollisions[2];
static const struct Rect sSize;

static void Solid33_Init(Object* p);
static void Solid33_Update(Object* p);
static void Solid33_Die(void* _ UNUSED);

// clang-format off
const SolidRoutine gSolid33Routine = {
    [ENTITY_INIT] =      (void*)Solid33_Init,
    [ENTITY_UPDATE] =    (void*)Solid33_Update,
    [ENTITY_DIE] =       (void*)Solid33_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

static void Solid33_Init(Object* p) {
  struct Coord* d;

  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SetMotion(&p->s, MOTION(SM125_WEILLABO_PLATFORM, 0));
  UpdateMotionGraphic(&p->s);
  INIT_BODY(p, &sCollisions[0], 0, NULL);
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = &sSize;
  (p->s).hazardAttr = (METATILE_CONVEYOR1 | METATILE_GROUND);

  d = &(p->s).d;
  d->y = 0;
  (p->s).d.x = 0;
  (p->s).coord.x += PIXEL(8);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid33_Update(p);
}

static void Solid33_Update(Object* p) {
  s32 y = SEA - PIXEL(10);
  if (((p->body).status & BODY_STATUS_B2) && ((p->s).coord.y + PIXEL(8) > (pZero2->s).coord.y)) {
    y = SEA - PIXEL(8);
  }
  (p->s).coord.y = (((p->s).coord.y * 7) + y) >> 3;
}

static void Solid33_Die(void* _) { return; }

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0800, 0x4200, 0x1200},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x2400, 0x3C00, 0x0800},
    },
};

static const struct Rect sSize = {PIXEL(0), PIXEL(8), PIXEL(64), PIXEL(16)};
