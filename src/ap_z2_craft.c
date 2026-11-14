#include "ap.h"
#include "ap_import.h"
#include "camera.h"
#include "entity.h"
#include "entity_manager.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "projectile.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"

#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's solid 2, the Bombardment Aircraft's flying craft. Zero rides them over the clouds.
  Fires a shot forward and back by turns, every 64 frames while near.
  work0: path, 0 hovers in place
*/
struct Craft {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  u8 _bc[8];
};
static_assert(sizeof(struct Craft) == sizeof(struct Solid));

static void Craft_Init(struct Solid* p);
static void Craft_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2CraftRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Craft_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Craft_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08348864
static const struct Rect sSize = {0, 8192, 24576, 16384};

// 0x08348874: shot's muzzle, forward then back
static const Coords32 sMuzzles[2] = {{9472, 5376}, {-9472, 5376}};

// 0x08348884: path's reach, by work0
static const Coords32 sReach[8] = {
    {0, 0}, {8192, -4096}, {0, 10240}, {0, 6144}, {24576, 0}, {18432, 2048}, {4096, 0}, {0, 2048},
};

// 0x080c177c
struct Solid* ApZ2CreateCraft(const Coords32* at, u8 kind) {
  struct Solid* p = (struct Solid*)AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_Z2_CRAFT);
    (p->s).coord = *at;
    (p->s).work[0] = kind;
  }
  return p;
}

// 0x0800d06c
void ApZ2DeleteCraft(struct Solid* p) { DeleteSolid((Object*)p); }

static void ride(struct Entity* s) {
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x4000) {
    s->flags2 &= ~ENTI_PHYSICS;
    return;
  }
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sSize;
  s->physicsAttr = MTATTR_CONVEYOR1 | MTATTR_B11 | SHAPE_BLOCK;
}

// 0x080c17d8
static void Craft_Init(struct Solid* p) {
  struct Craft* c = (struct Craft*)p;
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, MOTION(AP_SHEET_Z2_CRAFT, 0));
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = s->d.y = 0;
  s->coord.x -= PIXEL(8);
  s->coord.y -= PIXEL(8);
  c->home = s->coord;
  ride(s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Craft_Update(p);
}

static void shoot(struct Entity* s, u8 n) {
  Coords32 at;
  struct Projectile* shot;
  at.x = s->coord.x + sMuzzles[n].x;
  at.y = s->coord.y + sMuzzles[n].y;
  shot = CreateLemon(&at, 0x400, n == 0 ? 0x80 : 0);
  if (shot == NULL) return;
  (shot->s).work[0] = 0;
  PlaySound(SE_ENEMY_BOMB);
}

// 0x080c1874, 0x080c1964, 0x080c19b0
static void Craft_Update(struct Solid* p) {
  struct Craft* c = (struct Craft*)p;
  struct Entity* s = &p->s;
  u32 time = gOverworld.work.apZ2Bomber.time;
  u32 turn;
  s16 sine;

  if (s->work[0] == 0) {
    s->coord.x = c->home.x + SIN((c->home.y >> 8) + time) * 8;
    s->coord.y = c->home.y + COS((c->home.x >> 7) + time) * 8;
  } else {
    sine = SIN(time >> 1);
    s->coord.x = c->home.x + sine * sReach[s->work[0]].x / 256;
    s->coord.y = c->home.y + sine * sReach[s->work[0]].y / 256;
  }
  ride(s);
  UpdateEntityAnim(s);

  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x3FFF) return;
  turn = (c->home.x >> 7) + time;
  if ((turn & 127) == 0) {
    shoot(s, 0);
  } else if ((turn & 63) == 0) {
    shoot(s, 1);
  }
}

#endif  // AP
