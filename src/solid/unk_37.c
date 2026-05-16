#include "collision.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"
#include "vfx.h"

// 改造カードでベースに出現するトビウオ

static const struct Collision sCollisions[2];

static void Solid37_Init(struct Solid* p);
static void Solid37_Update(struct Solid* p);
static void Solid37_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid37Routine = {
    [ENTITY_INIT] =      (void*)Solid37_Init,
    [ENTITY_UPDATE] =    (void*)Solid37_Update,
    [ENTITY_DIE] =       (void*)Solid37_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

void CreateSolid37(struct Entity* e) {
  struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_037);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = e;
    p->coord = e->coord;
    p->work[0] = 1, p->work[1] = 0;
  }
}

void FUN_080dc81c(struct Solid* p);
void FUN_080dc900(struct Solid* p);

static void Solid37_Init(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc81c(p);
  } else {
    FUN_080dc900(p);
  }
}

void FUN_080dc898(struct Solid* p);
void FUN_080dca60(struct Solid* p);

static void Solid37_Update(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc898(p);
  } else {
    FUN_080dca60(p);
  }
}

void FUN_080dc8e8(struct Solid* p);
static void FUN_080dcb80(struct Solid* p);

static void Solid37_Die(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc8e8(p);
  } else {
    FUN_080dcb80(p);
  }
}

// --------------------------------------------

INCASM("asm/solid/unk_37.inc");

// 0x080dcb80
static void FUN_080dcb80(struct Solid* p) {
  struct Camera* cam;
  if ((p->s).mode[1] == 0) {
    struct Entity* q;
    SetMotion(&p->s, MOTION(SM230_FLYING_FISH, 0));
    (p->s).d.x = PIXEL(7) / 4;
    (p->s).d.y = -PIXEL(4);
    (p->s).work[2] = 0;
    q = (p->s).unk_28;
    q->work[2]++;
    EXIT_BODY(p);
    (p->s).mode[1]++;
  }
  UpdateMotionGraphic(&p->s);
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
      range : {0x0000, 0x0000, 0x0E00, 0x0E00},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x02,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0E00, 0x0E00},
    },
};
