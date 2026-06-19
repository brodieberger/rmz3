#include "collision.h"
#include "entity.h"
#include "global.h"
#include "mod.h"
#include "overworld.h"
#include "solid.h"
#include "vfx.h"

// 改造カードでベースに出現するトビウオ

// Entity.work[0]
#define FLYING_FISH_MANAGER 0
#define FLYING_FISH_MAIN 1

static const struct Collision sCollisions[2];

static void Solid37_Init(struct Solid* p);
static void Solid37_Update(struct Solid* p);
static void Solid37_Die(struct Solid* p);

// clang-format off
const SolidRoutine gFlyingFishRoutine = {
    [ENTITY_INIT] =      (void*)Solid37_Init,
    [ENTITY_UPDATE] =    (void*)Solid37_Update,
    [ENTITY_DIE] =       (void*)Solid37_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// 0x080dc768
static void CreateFlyingFish(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_FLYING_FISH);
    p->unk_28 = e;
    p->coord = e->coord;
    p->work[0] = FLYING_FISH_MAIN, p->work[1] = 0;
  }
}

static void FUN_080dc81c(struct Solid* p);
void FUN_080dc900(struct Solid* p);

static void Solid37_Init(struct Solid* p) {
  if ((p->s).work[0] == FLYING_FISH_MANAGER) {
    FUN_080dc81c(p);  // spawner
  } else {
    FUN_080dc900(p);  // spawned fish
  }
}

static void FUN_080dc898(struct Solid* p);
void FUN_080dca60(struct Solid* p);

static void Solid37_Update(struct Solid* p) {
  if ((p->s).work[0] == FLYING_FISH_MANAGER) {
    FUN_080dc898(p);
  } else {
    FUN_080dca60(p);
  }
}

static void FUN_080dc8e8(struct Entity* p);
static void FUN_080dcb80(struct Solid* p);

static void Solid37_Die(struct Solid* p) {
  if ((p->s).work[0] == FLYING_FISH_MANAGER) {
    FUN_080dc8e8((void*)p);
  } else {
    FUN_080dcb80(p);
  }
}

// --------------------------------------------

// 0x080dc81c
static void FUN_080dc81c(struct Solid* p) {
  if (!FLAG(gSystemSavedata.flags, MOD_FLYING_FISH)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (p->s).work[2] = 0, (p->s).work[3] = 30;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid37_Update(p);
}

static void FUN_080dc898(struct Solid* p) {
  if ((--(p->s).work[3]) == 0xFF) {
    CreateFlyingFish((void*)p);
    (p->s).work[3] = (RANDOM(RNG_0202f388) & 0x1F) + 8;
  }
  if ((p->s).work[2] > 30) (p->s).work[2] = 0;
}

static void FUN_080dc8e8(struct Entity* p) { SET_SOLID_ROUTINE(p, ENTITY_EXIT); }

INCASM("asm/solid/flying_fish.inc");

// 0x080dcb80
static void FUN_080dcb80(struct Solid* p) {
  struct Camera* cam;
  if ((p->s).mode[1] == 0) {
    struct Entity* q;
    SetSpriteAnimation(p, MOTION(SM230_FLYING_FISH, 0));
    (p->s).d.x = PIXEL(7) / 4;
    (p->s).d.y = -PIXEL(4);
    (p->s).work[2] = 0;
    q = (p->s).unk_28;
    q->work[2]++;
    EXIT_BODY(p);
    (p->s).mode[1]++;
  }
  UpdateSpriteAnimation(p);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += PIXEL(1) / 4;
  (p->s).work[2]++;
  if ((p->s).work[2] & 1) {
    (p->s).flags &= ~DISPLAY;
  } else {
    (p->s).flags |= DISPLAY;
  }
  cam = &gStageRun.vm.camera;
  if ((p->s).coord.x > ((cam->viewport).x + PIXEL(136) - 1)) {
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
  }
}

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x02,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x02,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
};
