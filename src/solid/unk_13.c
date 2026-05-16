#include "collision.h"
#include "global.h"
#include "solid.h"

// Tretista

struct Solid13Object {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[12];
  u8 unk_c0;
};
static_assert(sizeof(struct Solid13Object) == sizeof(struct Solid));

static const struct Rect sSize;

static const struct Collision Collision_ARRAY_0837025c[2];
static const struct Collision Collision_ARRAY_0837028c[2];

static void Solid13_Init(struct Solid13Object* p);
static void Solid13_Update(struct Entity* p);
static void Solid13_Die(struct Entity* p);

// clang-format off
const SolidRoutine gSolid13Routine = {
    [ENTITY_INIT] =      (SolidFunc)Solid13_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Solid13_Update,
    [ENTITY_DIE] =       (SolidFunc)Solid13_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

struct Solid* CreateSolid13(struct Entity* e, struct Coord* c, struct Coord* d, u8 n) {
  struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_013);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = n;
    p->coord.x = c->x, p->coord.y = c->y;
    p->d.x = d->x, p->d.y = d->y;
    p->unk_28 = e;
  }
  return (void*)p;
}

static void Solid13_Init(struct Solid13Object* p) {
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = &sSize;
  (p->s).hazardAttr = METATILE_GROUND;
  (p->s).flags |= FLIPABLE;
  (p->s).flags &= ~DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &Collision_ARRAY_0837025c[0], 1, NULL);
  INIT_BODY(p, &Collision_ARRAY_0837028c[0], 1, NULL);
  p->unk_c0 = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  Solid13_Update((void*)p);
}

static void _Solid13_Update(Object* p);

static void Solid13_Update(struct Entity* p) {
  static const SolidFunc sUpdates[1] = {
      (SolidFunc)_Solid13_Update,
  };
  (sUpdates[p->mode[1]])((void*)p);
}

static void Solid13_Die(struct Entity* p) { SET_SOLID_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------

// 0x080ce438
static void _Solid13_Update(Object* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      struct Entity* e = (struct Entity*)(p->s).unk_28;
      (p->s).coord = e->coord;
      if (e->mode[0] >= ENTITY_DIE) {
        SET_SOLID_ROUTINE(p, ENTITY_DIE);
        EXIT_BODY(p);
        Solid13_Die((void*)p);
      }
      if ((p->body).status & BODY_STATUS_B2) {
        SET_SOLID_ROUTINE(p, ENTITY_DIE);
        EXIT_BODY(p);
        Solid13_Die((void*)p);
      }
      break;
    }
    default: {
      break;
    }
  }
}

// --------------------------------------------

static const struct Collision Collision_ARRAY_0837025c[2] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
};

static const struct Collision Collision_ARRAY_0837028c[2] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(28), PIXEL(76), PIXEL(76)},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(28), PIXEL(76), PIXEL(76)},
    },
};

static const struct Rect sSize = {PIXEL(0), -PIXEL(30), PIXEL(56), PIXEL(56)};
