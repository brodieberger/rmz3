#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "random.h"
#include "score.h"
#include "solid.h"
#include "sound.h"
#include "vfx.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's solid 30, the Bombardment Aircraft's cargo. Stands on and breaks.
  work0:
    0 crate, its broken base left a while
    1 stack of eight boxes, dropping an item per column
*/

enum { CRATE_BURST, CRATE_CUT, STACK_BURST, STACK_CUT };

#define CARGO(n) MOTION(AP_SHEET_Z2_CARGO, (n))

// clang-format off
// 0x08349ba8
static const struct Collision sBody[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x1600, 0x3000, 0x2c00}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0xe00, 0x4000, 0x1c00}},
};
// 0x08349e58
static const struct Rect sSize[2] = {{0, -0x1600, 0x3000, 0x2c00}, {0, -0xe00, 0x4000, 0x1c00}};

// 0x08349bf0
static const struct SlashedEnemy sCrateGibs[4] = {
    {CARGO(1), {0xff, 0x51}, {0, 0}, {-320, -640}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(2), {0xff, 0x51}, {0, 0}, {64, -640}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(1), {0xff, 0x51}, {0, 0}, {-384, -1664}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(2), {0xff, 0x51}, {0, 0}, {128, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// 0x08349c60, 0x08349d5c
static const struct SlashedEnemy sStackGibs[9] = {
    {CARGO(5), {0x10, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x14, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x18, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x1c, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x12, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x16, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x1a, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(5), {0x1e, 0x42}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}},
    {CARGO(6), {0x30, 0x50}, {0, 0}, {-384, -896}, {63, 255}, {0, 32}, {0x200, 0x200}, {0}},
};
static const struct SlashedEnemy sStackCutGibs[9] = {
    {CARGO(5), {0xff, 0x51}, {0, 0}, {-256, -1280}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {-128, -1664}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {128, -1664}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {256, -1280}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {-256, -768}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {-128, -832}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {128, -832}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(5), {0xff, 0x51}, {0, 0}, {256, -768}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {CARGO(6), {0x20, 0x50}, {0, 0}, {-384, -1280}, {63, 255}, {0, 32}, {0x200, 0x200}, {0}},
};
// clang-format on

static void Cargo_Init(struct Solid* p);
static void Cargo_Update(struct Solid* p);
static void Cargo_Die(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2CargoRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Cargo_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Cargo_Update,
    [ENTITY_DIE] =       (SolidFunc)Cargo_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static u8 gibFlip(struct Entity* s) { return ((s->flags & X_FLIP) != 0) << 4; }

// 0x080d1c78
static void Cargo_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  u8 n = s->work[0];
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->mode[2] = 0;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SET_XFLIP(p, FALSE);
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (n == 1) s->coord.x += PIXEL(8);
  SetMotion(s, n == 0 ? CARGO(0) : CARGO(4));
  INIT_BODY(p, &sBody[n], 24, NULL);
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sSize[n];
  s->physicsAttr = 0x801;
  Cargo_Update(p);
}

// 0x080d1df4
static void Cargo_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  bool8 hardCut;
  if (!(status & BODY_STATUS_DEAD)) {
    UpdateEntityAnim(s);
    return;
  }
  hardCut = (status & BODY_STATUS_SLASHED) && (status & BODY_STATUS_B15);
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  if (s->work[0] == 0) {
    s->mode[1] = hardCut ? CRATE_CUT : CRATE_BURST;
  } else {
    s->mode[1] = hardCut ? STACK_CUT : STACK_BURST;
  }
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  Cargo_Die(p);
}

static s32 jitter(u8 mask, s32 below) { return PIXEL((s32)(RANDOM(RNG_0202f388) & mask) - below); }

static void smokeAround(struct Entity* s, u8 kind, u8 mask, s32 below) {
  Coords32 c;
  c.x = s->coord.x + jitter(mask, below);
  c.y = s->coord.y + jitter(mask, below) - PIXEL(12);
  CreateSmoke(kind, &c);
}

static void finish(struct Solid* p) {
  struct Entity* s = &p->s;
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// 0x080d1ea8, 0x080d211c: bursts, its base a while, then smoke and an item
static void crate(struct Solid* p, const struct SlashedEnemy* gibs, u8 time) {
  struct Entity* s = &p->s;
  s32 dir = (s->flags & X_FLIP) ? 1 : -1;
  Coords32 c;
  if (s->mode[2] == 0) {
    PlaySound(SE_ZAKO_EXPLODE);
    SetMotion(s, CARGO(3));
    c.x = s->coord.x + dir * PIXEL(6);
    c.y = s->coord.y - PIXEL(30);
    useApSheets(CreateSlashedEnemy(&c, &gibs[0], 0, gibFlip(s)));
    c.x = s->coord.x - dir * PIXEL(14);
    c.y = s->coord.y - PIXEL(34);
    useApSheets(CreateSlashedEnemy(&c, &gibs[1], 0, gibFlip(s)));
    smokeAround(s, 1, 15, 8);
    smokeAround(s, 2, 15, 8);
    s->work[2] = time;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  PlaySound(SE_ZAKO_EXPLODE);
  smokeAround(s, 1, 31, 15);
  smokeAround(s, 2, 31, 15);
  smokeAround(s, 2, 31, 15);
  TryDropItem(5, (struct Coord*)&s->coord);
  s->flags &= ~DISPLAY;
  finish(p);
}

// Eight boxes, two rows of four, and the lid
static void scatter(struct Entity* s, const struct SlashedEnemy* gibs) {
  Coords32 c;
  u8 i;
  for (i = 0; i < 8; i++) {
    c.x = s->coord.x - PIXEL(24) + PIXEL(16) * (i & 3);
    c.y = s->coord.y - PIXEL(20) + PIXEL(16) * ((i >> 2) & 1);
    useApSheets(CreateSlashedEnemy(&c, &gibs[i], 0, gibFlip(s)));
  }
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(32);
  useApSheets(CreateSlashedEnemy(&c, &gibs[8], 0, gibFlip(s)));
}

// 0x080d2390: an item per column, 8 frames apart
static void stack(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    scatter(s, sStackGibs);
    s->unk_coord.x = s->coord.x - PIXEL(24);
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->work[2]--;
  if ((s->work[2] & 7) != 0 || s->work[2] > 32) return;
  if (s->work[2] == 0) {
    finish(p);
    return;
  }
  PlaySound(SE_ZAKO_EXPLODE);
  c.x = s->unk_coord.x;
  c.y = s->coord.y - PIXEL(20);
  TryDropItem(5, (struct Coord*)&c);
  s->unk_coord.x += PIXEL(16);
}

// 0x080d24e0
static void stackCut(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  PlaySound(SE_ZAKO_EXPLODE);
  scatter(s, sStackCutGibs);
  c.x = s->coord.x + PIXEL(RANDOM(RNG_0202f388) & 15) - PIXEL(20);
  c.y = s->coord.y + PIXEL(RANDOM(RNG_0202f388) & 15) - PIXEL(24);
  CreateSmoke(1, &c);
  c.x = s->coord.x + PIXEL(RANDOM(RNG_0202f388) & 15) + PIXEL(4);
  c.y = s->coord.y + jitter(15, 8) - PIXEL(24);
  CreateSmoke(1, &c);
  c.x = s->coord.x + jitter(63, 31);
  c.y = s->coord.y + jitter(15, 8) - PIXEL(24);
  CreateSmoke(2, &c);
  TryDropItem(5, (struct Coord*)&s->coord);
  s->flags &= ~DISPLAY;
  finish(p);
}

// 0x08349b98
static void Cargo_Die(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case CRATE_BURST:
      crate(p, &sCrateGibs[0], 32);
      break;
    case CRATE_CUT:
      crate(p, &sCrateGibs[2], 56);
      break;
    case STACK_BURST:
      stack(p);
      break;
    case STACK_CUT:
      stackCut(p);
      break;
  }
}

#endif
