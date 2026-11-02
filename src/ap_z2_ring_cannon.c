#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's ring cannon, enemy 16.
  work0:
    0: rolls in from the left, faces right
    1, 2: faces Zero
*/

struct Cannon {
  OBJECT_HDR;
  s32 postX;                     // 0xB4
  s32 postY;                     // 0xB8
  u8 hitFromRight;               // 0xBC
  u8 fired;                      // 0xBD
  u8 _[2];
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Cannon) == sizeof(struct Enemy));

enum {
  CANNON_ELEMENT_HIT = 1,
  CANNON_REST = 4,
  CANNON_ROLL_IN,
  CANNON_CHARGE,
  CANNON_FIRE,
  CANNON_RECOIL,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_RING_CANNON, n)

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define nextMode mode[3]

static const struct Collision sCollisions[2];
static const struct Collision sHarmless;
static const struct SlashedEnemy sGibs[4];
static const struct SlashedEnemy sCutHalf;
static const Coords32 sElementCoord = {0, -PIXEL(16)};

static void Cannon_Init(struct Cannon* p);
static void Cannon_Update(struct Cannon* p);
static void Cannon_Die(struct Cannon* p);
static void createRing(Coords32* c, bool8 right);
static void createSparks(Coords32* c, bool8 right);

// clang-format off
const EnemyRoutine gApZ2RingCannonRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Cannon_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Cannon_Update,
    [ENTITY_DIE] =       (EnemyFunc)Cannon_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Cannon* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void Cannon_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Cannon* p = (struct Cannon*)body->parent;
    p->hitFromRight = (body->enemy->parent->coord).x > (p->s).coord.x;
  }
}

// 0x0806e9cc
static void Cannon_Init(struct Cannon* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetMotion(s, ANIM(0));
    UpdateEntityAnim(s);
    SET_XFLIP(p, TRUE);
    s->mode[1] = CANNON_ROLL_IN;
  } else {
    SetMotion(s, ANIM(5));
    UpdateEntityAnim(s);
    SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
    s->mode[1] = CANNON_CHARGE;
  }
  INIT_BODY(p, sCollisions, 12, Cannon_OnCollision);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->postX = s->coord.x;
  p->postY = s->coord.y;
  p->elementEffect = NULL;
  Cannon_Update(p);
}

static void Cannon_Recoil(struct Cannon* p);
static void Cannon_ElementHit(struct Cannon* p);
static void Cannon_Rest(struct Cannon* p);
static void Cannon_RollIn(struct Cannon* p);
static void Cannon_Charge(struct Cannon* p);
static void Cannon_Fire(struct Cannon* p);

// 0x0806eb58
static void Cannon_Update(struct Cannon* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != CANNON_RECOIL) setMode(p, CANNON_RECOIL);
  if (s->mode[1] == CANNON_RECOIL) {
    Cannon_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = (status & BODY_STATUS_SLASHED) ? 1 : 0;
    EXIT_BODY(p);
    Cannon_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    SetDDP(&p->body, sCollisions);
    p->elementEffect = NULL;
    return;
  }

  if (s->mode[1] != CANNON_ELEMENT_HIT && (status & BODY_STATUS_WHITE) && p->elementEffect == NULL) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->elementEffect != NULL) setMode(p, CANNON_ELEMENT_HIT);
  }

  switch (s->mode[1]) {
    case CANNON_ELEMENT_HIT: Cannon_ElementHit(p); break;
    case CANNON_REST: Cannon_Rest(p); break;
    case CANNON_ROLL_IN: Cannon_RollIn(p); break;
    case CANNON_CHARGE: Cannon_Charge(p); break;
    case CANNON_FIRE: Cannon_Fire(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Cannon_Recoil(struct Cannon* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    EXIT_BODY(p);
    Cannon_Die(p);
  }
}

// 0x0806ecd0: harmless while burning or thawing
static void Cannon_ElementHit(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2));
    SetDDP(&p->body, &sHarmless);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsDead(p->elementEffect)) {
    p->elementEffect = NULL;
    SetDDP(&p->body, sCollisions);
    setMode(p, CANNON_CHARGE);
  }
}

// 0x0806ed34: waits work[2] + 1 frames, then goes to nextMode
static void Cannon_Rest(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, s->nextMode);
}

// 0x0806ed74: rolls in 130 px from the left, drops 16 px onto post
static void Cannon_RollIn(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s32 i;
    SetMotion(s, ANIM(0));
    s->d.x = 0;
    for (i = 0; i < 64; i++) {
      s->d.x += 16;
      s->coord.x -= s->d.x;
    }
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(16);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  switch (s->mode[3]) {
    case 0:
      s->d.x -= 16;
      s->coord.x += s->d.x;
      if (s->d.x == 0) s->mode[3]++;
      return;
    case 1:
      s->coord.y += PIXEL(1);
      if (s->coord.y > p->postY) {
        SetMotion(s, ANIM(1));
        UpdateEntityAnim(s);
        s->coord.y = p->postY;
        s->mode[3]++;
      }
      return;
    default:
      if (IsSpriteAnimEnd(s)) {
        setMode(p, CANNON_REST);
        s->nextMode = CANNON_CHARGE;
        s->work[2] = 16;
      }
      return;
  }
}

// 0x0806ee30: sparks gather at muzzle for first half
static void Cannon_Charge(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(5));
    s->work[2] = 96;
    p->fired = 0;
    PlaySound(SE_Z2_RING_CANNON_CHARGE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 1) && s->work[2] > 48) createSparks(&s->coord, FACING_RIGHT(p));
  if (--s->work[2] == 0xFF) setMode(p, CANNON_FIRE);
}

// 0x0806ee9c: one ring each time firing animation plays
static void Cannon_Fire(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    createRing(&s->coord, FACING_RIGHT(p));
    PlaySound(SE_Z2_RING_CANNON_FIRE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!IsSpriteAnimEnd(s)) return;
  if (++p->fired > 7) {
    s->mode[1] = CANNON_REST;
    s->nextMode = CANNON_CHARGE;
    s->work[2] = 120;
  }
  s->mode[2] = 0;
}

// --------------------------------------------

static u8 gibFlip(struct Cannon* p) { return FACING_RIGHT(p) ? 0x11 : 0; }

static void smokeAt(struct Cannon* p, u8 kind, s32 forward, s32 up) {
  Coords32 c;
  c.x = (p->s).coord.x + (FACING_RIGHT(p) ? forward : -forward);
  c.y = (p->s).coord.y - up;
  CreateSmoke(kind, &c);
}

// One step of four-step breakup, Zero 2's 0x0806ef48 .. 0x0806f088. Returns TRUE when done.
static bool8 breakUp(struct Cannon* p, u8 step) {
  struct Entity* s = &p->s;
  switch (step) {
    case 0:
      useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[0], 0, gibFlip(p)));
      smokeAt(p, 1, PIXEL(23), PIXEL(19));
      PlaySound(SE_ZAKO_EXPLODE);
      break;
    case 4:
      useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[1], 0, gibFlip(p)));
      smokeAt(p, 2, PIXEL(9), PIXEL(4));
      break;
    case 8:
      useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[2], 0, gibFlip(p)));
      smokeAt(p, 1, -PIXEL(10), PIXEL(11));
      PlaySound(SE_ZAKO_EXPLODE);
      break;
    case 12:
      useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[3], 0, gibFlip(p)));
      smokeAt(p, 2, PIXEL(6), PIXEL(28));
      TryDropItem(4, (struct Coord*)&s->coord);
      if (gScore.enemyCount < 9999) gScore.enemyCount++;
      TryDropZakoDisk((struct Enemy*)p, &s->coord);
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      return TRUE;
  }
  return FALSE;
}

// 0x0806ef08, and 0x0806f140 when cut
static void Cannon_Die(struct Cannon* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetMotion(s, ANIM(8));
    s->work[2] = 0;
    if (s->mode[1] == 1) {
      useApSheets(CreateSlashedEnemy(&s->coord, &sCutHalf, 0, gibFlip(p)));
      s->d.x = FACING_RIGHT(p) ? -0x80 : 0x80;
      s->d.y = 0;
    }
    s->mode[3]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 1) {
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(1)) == 0) {
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 0x20;
      if (s->work[2] < 24) s->work[2] = 24;
    }
    if (s->work[2] >= 24 && breakUp(p, s->work[2] - 24)) return;
  } else if (breakUp(p, s->work[2])) {
    return;
  }
  s->work[2]++;
}

// --------------------------------------------
// Rings, Zero 2's projectile 15

static const struct Collision sRing;

static void Ring_Init(struct Entity* p);
static void Ring_Update(struct Entity* p);
static void Ring_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2RingCannonShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Ring_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Ring_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Ring_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809bae0
static void createRing(Coords32* c, bool8 right) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_RING_CANNON_SHOT);
    p->coord = *c;
    p->work[0] = right;
  }
}

// 0x0809bb30
static void Ring_Init(struct Entity* p) {
  bool8 right = p->work[0];
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  SetMotion(p, ANIM(4));
  UpdateEntityAnim(p);
  SET_XFLIP(p, right);
  INIT_BODY(p, &sRing, 1, NULL);
  p->d.x = right ? PIXEL(4) : -PIXEL(4);
  p->coord.x += right ? PIXEL(46) : -PIXEL(46);
  p->coord.y -= PIXEL(19);
  p->work[2] = 64;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Ring_Update(p);
}

// 0x0809bc0c
static void Ring_Update(struct Entity* p) {
  UpdateEntityAnim(p);
  p->coord.x += p->d.x;
  if (--p->work[2] == 0xFF || (((Object*)p)->body.status & BODY_STATUS_B2) ||
      FUN_080098a4(p->coord.x, p->coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Ring_Die(p);
  }
}

// 0x0809bcb8
static void Ring_Die(struct Entity* p) {
  if (p->mode[1] == 0) {
    SetMotion(p, ANIM(7));
    EXIT_BODY(p);
    p->mode[1]++;
  }
  UpdateEntityAnim(p);
  if (IsSpriteAnimEnd(p)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Charge sparks, Zero 2's VFX 24. Two at once, drawn on alternate frames.

struct Sparks {
  struct Entity s;
  s32 x[2];  // 0x74
  s32 y[2];  // 0x7C
};
static_assert(sizeof(struct Sparks) == sizeof(struct VFX));

static void Sparks_Init(struct Sparks* p);
static void Sparks_Update(struct Sparks* p);
static void Sparks_Die(struct Sparks* p);

// clang-format off
const VFXRoutine gApZ2RingCannonSparksRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Sparks_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Sparks_Update,
    [ENTITY_DIE] =       (VFXFunc)Sparks_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b3218
static void createSparks(Coords32* c, bool8 right) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_RING_CANNON_SPARKS);
    p->coord = *c;
    p->work[1] = right;
  }
}

// 0x080b32f0
static void Sparks_Init(struct Sparks* p) {
  struct Entity* s = &p->s;
  u8 a, b;
  s32 muzzleX, muzzleY;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(6));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  if (s->work[1]) {
    a = RANDOM(RNG_0202f388) % 52 + 128;
    b = 128 - RANDOM(RNG_0202f388) % 52;
    muzzleX = s->coord.x + PIXEL(31);
  } else {
    a = RANDOM(RNG_0202f388) % 52;
    b = 255 - RANDOM(RNG_0202f388) % 51;
    muzzleX = s->coord.x - PIXEL(31);
  }
  muzzleY = s->coord.y - PIXEL(19);
  s->d.x = COS(a) * 2;
  s->unk_coord.x = SIN(a) * 2;
  s->d.y = COS(b) * 2;
  s->unk_coord.y = SIN(b) * 2;
  p->x[0] = muzzleX - s->d.x * 20;
  p->y[0] = muzzleY - s->unk_coord.x * 20;
  p->x[1] = muzzleX - s->d.y * 20;
  p->y[1] = muzzleY - s->unk_coord.y * 20;
  s->work[2] = 16;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Sparks_Update(p);
}

// 0x080b3644
static void Sparks_Update(struct Sparks* p) {
  struct Entity* s = &p->s;
  u8 which = s->work[2] & 1;
  UpdateEntityAnim(s);
  p->x[0] += s->d.x;
  p->y[0] += s->unk_coord.x;
  p->x[1] += s->d.y;
  p->y[1] += s->unk_coord.y;
  s->coord.x = p->x[which];
  s->coord.y = p->y[which];
  if (--s->work[2] == 0xFF) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Sparks_Die(p);
  }
}

static void Sparks_Die(struct Sparks* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x500, -0xd00, 0x3800, 0x1a00}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, 0, 0, 0, 0x00000000, {-0x500, -0xd00, 0x3800, 0x1a00}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, 0, 0, 0, 0x00000000, {-0x500, -0xd00, 0x3800, 0x1a00}};

static const struct Collision sRing =
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xe00, 0xe00}};

static const struct SlashedEnemy sGibs[4] = {
    {ANIM(9), {0xff, 0x11}, {-5120, -4608}, {-512, -512}, {255, 511}, {0, 64}, {0x400, 0x400}, {0}},
    {ANIM(12), {0xfe, 0x11}, {-1792, -1536}, {512, -768}, {511, 511}, {0, 64}, {0x400, 0x400}, {0}},
    {ANIM(10), {0xff, 0x11}, {4352, -2304}, {256, -1280}, {255, 511}, {0, 64}, {0x400, 0x400}, {0}},
    {ANIM(11), {0xfe, 0x11}, {-1792, -2816}, {768, -768}, {511, 511}, {0, 64}, {0x400, 0x400}, {0}},
};

static const struct SlashedEnemy sCutHalf =
    {ANIM(9), {0xff, 0x04}, {-5120, -4608}, {-384, -512}, {0, 0}, {0, 64}, {0x0, 0x0}, {0}};
// clang-format on

#endif  // AP
