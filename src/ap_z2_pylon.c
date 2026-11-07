#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "physics.h"
#include "projectile.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's pylon, enemy 13.
  work0: slot
  work1:
    0: slots are u16s
    1: slots are bytes, in pairs 4 apart
*/

struct Pylon {
  OBJECT_HDR;
  u8 _b4[8];
  bool8 hitFromRight;            // 0xBC
  u8 _bd[3];
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Pylon) == sizeof(struct Enemy));

enum {
  PYLON_WHOLE,
  PYLON_BROKEN,
  PYLON_REGROW,
  PYLON_ELEMENT,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_PYLON, (n))

static const struct Collision sWhole;
static const struct Collision sRegrowing;
static const struct Collision sNone;
static const struct SlashedEnemy sGibs[3];
static const Coords32 sElementCoord = {0, -PIXEL(16)};

static void Pylon_Init(struct Pylon* p);
static void Pylon_Update(struct Pylon* p);
static void Pylon_Die(struct Pylon* p);
static void Pylon_Disappear(struct Pylon* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);

// clang-format off
const EnemyRoutine gApZ2PylonRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Pylon_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Pylon_Update,
    [ENTITY_DIE] =       (EnemyFunc)Pylon_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)Pylon_Disappear,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Pylon* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static u16 countdown(struct Pylon* p) {
  u8 n = (p->s).work[0];
  if ((p->s).work[1]) return gOverworld.work.raw[(n & 1) + (n >> 1) * 4];
  return ((u16*)gOverworld.work.raw)[n];
}

static void breakOff(struct Pylon* p) {
  u8 n = (p->s).work[0];
  if ((p->s).work[1]) {
    gOverworld.work.raw[(n & 1) + (n >> 1) * 4] = 190;
  } else {
    ((u16*)gOverworld.work.raw)[n] = 190;
  }
}

// 0x0806cdb8
static void Pylon_Init(struct Pylon* p) {
  struct Entity* s = &p->s;
  bool8 broken = countdown(p) != 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  if (broken) {
    SetMotion(s, ANIM(0));
    s->mode[1] = PYLON_BROKEN;
    s->mode[2] = 1;
    INIT_BODY(p, &sNone, 32, onCollision);
  } else {
    SetMotion(s, ANIM(10));
    setMode(p, PYLON_WHOLE);
    INIT_BODY(p, &sWhole, 32, onCollision);
  }
  UpdateEntityAnim(s);
  p->elementEffect = NULL;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  Pylon_Update(p);
}

static void Pylon_Whole(struct Pylon* p);
static void Pylon_Broken(struct Pylon* p);
static void Pylon_Regrow(struct Pylon* p);
static void Pylon_Element(struct Pylon* p);

// 0x0806cee0
static void Pylon_Update(struct Pylon* p) {
  switch ((p->s).mode[1]) {
    case PYLON_WHOLE: Pylon_Whole(p); break;
    case PYLON_BROKEN: Pylon_Broken(p); break;
    case PYLON_REGROW: Pylon_Regrow(p); break;
    case PYLON_ELEMENT: Pylon_Element(p); break;
  }
}

// 0x0806cef8
static void Pylon_Die(struct Pylon* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }

// 0x0806cf10: unloaded burning or frozen, counts as broken
static void Pylon_Disappear(struct Pylon* p) {
  if (p->elementEffect != NULL) breakOff(p);
  DeleteEnemy((struct Entity*)p);
}

// Burning or frozen first, unless fire made nothing
static void takeHit(struct Pylon* p) {
  if (p->elementEffect == NULL) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, &sElementCoord);
    if (p->elementEffect != NULL) {
      setMode(p, PYLON_ELEMENT);
      return;
    }
  }
  if ((p->body).elemented == ELEMENT_FLAME) return;
  breakOff(p);
  setMode(p, PYLON_BROKEN);
}

// 0x0806cf70
static void Pylon_Whole(struct Pylon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sWhole);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((p->body).status & BODY_STATUS_WHITE) takeHit(p);
}

// 0x0806d030
static void Pylon_Broken(struct Pylon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    u8 flip = p->hitFromRight | (s->flags & X_FLIP);
    s32 i;
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, &sNone);
    for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[i], 0, flip));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countdown(p) == 0) setMode(p, PYLON_REGROW);
}

// 0x0806d140: solid again 5 frames in
static void Pylon_Regrow(struct Pylon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(1));
    SetDDP(&p->body, &sRegrowing);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->motion.cmdIdx > 5) SetDDP(&p->body, &sWhole);
  if ((p->body).status & BODY_STATUS_WHITE) {
    takeHit(p);
  } else if (s->motion.state == ANIM_NEXT_GOTO) {
    setMode(p, PYLON_WHOLE);
  }
}

// 0x0806d238
static void Pylon_Element(struct Pylon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sNone);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (isKilled(p->elementEffect)) {
    p->elementEffect = NULL;
    breakOff(p);
    setMode(p, PYLON_BROKEN);
  }
}

// 0x0806d2c8
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Pylon* p = (struct Pylon*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) p->hitFromRight = body->enemy->parent->coord.x > (p->s).coord.x;
}

// --------------------------------------------
// Zero 2's projectile 10, unseen hazard, live while all pylons stand and Zero within 80 px
// work0: box

#define hazardOn (gOverworld.work.raw[0x10])

static const struct Collision sHazards[6];
static const s32 sHazardX[6] = {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(24), PIXEL(8), PIXEL(8)};

static void Hazard_Init(struct Projectile* p);
static void Hazard_Update(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2PylonHazardRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Hazard_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Hazard_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809a46c
static void Hazard_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->flags |= FLIPABLE;
  if (hazardOn) {
    s->mode[1] = 0;
    INIT_BODY(p, &sHazards[s->work[0]], 1, NULL);
  } else {
    s->mode[1] = 1;
    INIT_BODY(p, &sNone, 1, NULL);
  }
  s->coord.y += PIXEL(1);
  Hazard_Update(p);
}

// 0x0809a540, 0x0809a5d8
static void Hazard_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    u32 d = (pZero2->s).coord.x - (s->coord.x + sHazardX[s->work[0]]) + PIXEL(80);
    SetDDP(&p->body, d <= PIXEL(160) ? &sHazards[s->work[0]] : &sNone);
    if (!hazardOn) {
      s->mode[1] = 1;
      s->mode[2] = 0;
    }
  } else {
    SetDDP(&p->body, &sNone);
    if (hazardOn) {
      s->mode[1] = 0;
      s->mode[2] = 0;
    }
  }
}

// -------------------------------------------
// clang-format off
static const struct Collision sWhole =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, 0x02, 0x00, 0, 0x00000000, {0x0, -0xc00, 0xe00, 0x2300}};

static const struct Collision sRegrowing =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, 0x02, 0x00, 0, 0x00000000, {0x0, -0x600, 0xe00, 0x1500}};

static const struct Collision sNone =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}};

static const struct SlashedEnemy sGibs[3] = {
    {ANIM(2), {0xff, 0x51}, {0, -6144}, {128, -1280}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(4), {0xfe, 0x51}, {0, -4096}, {128, -512}, {127, 127}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(3), {0xff, 0x51}, {0, -1280}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};
static const struct Collision sHazards[6] = {
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x3000}},
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x800, 0x0, 0x2000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x1000, 0x0, 0x3000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x1800, 0x0, 0x4000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 7, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x1800, 0x1000, 0x4000}},
};
// clang-format on

#endif  // AP
