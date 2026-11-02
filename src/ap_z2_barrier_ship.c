#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's barrier ship, enemy 86.
  work0: unused
*/

struct Ship {
  OBJECT_HDR;
  s32 postX;                     // 0xB4
  s32 postY;                     // 0xB8
  u8 hitFromRight;               // 0xBC
  u8 blocked;                    // 0xBD, blocked hits since last firing
  bool8 scorched;                // element effect ran out
  u8 _bf;
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Ship) == sizeof(struct Enemy));

enum {
  SHIP_PULLED = 3,
  SHIP_RECOVER = 5,
  SHIP_PATROL,
  SHIP_BRAKE,
  SHIP_TURN,
  SHIP_FIRE,
  SHIP_RECOIL,
};

enum {
  SHIP_EXPLODE,
  SHIP_CUT,
  SHIP_CUT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_BARRIER_SHIP, n)
#define ANIM_BRAKE ANIM(0)
#define ANIM_CUT ANIM(2)
#define ANIM_BARRIER ANIM(5)
#define ANIM_CHARGE ANIM(6)
#define ANIM_RING ANIM(7)
#define ANIM_FLY ANIM(8)
#define ANIM_BARRIER_TURN ANIM(9)
#define ANIM_BARRIER_HIT ANIM(10)
#define ANIM_TURN ANIM(11)
#define ANIM_BARRIER_TURNED ANIM(12)

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define attachment unk_28

static const struct Collision sCollisions[3];
static const Coords32 sElementCoord = {0, 0};

static void Ship_Init(struct Ship* p);
static void Ship_Update(struct Ship* p);
static void Ship_Die(struct Ship* p);
static struct Entity* createBarrier(struct Ship* p, motion_t m);
static void createWreck(struct Entity* parent, u8 kind, u8 n);

// clang-format off
const EnemyRoutine gApZ2BarrierShipRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Ship_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Ship_Update,
    [ENTITY_DIE] =       (EnemyFunc)Ship_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Ship* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

// Replace barrier
static void swapBarrier(struct Ship* p, motion_t m) {
  if ((p->s).attachment != NULL) (p->s).attachment->work[1] = TRUE;
  (p->s).attachment = createBarrier(p, m);
}

static void dropBarrier(struct Ship* p) {
  if ((p->s).attachment != NULL) {
    (p->s).attachment->work[1] = TRUE;
    (p->s).attachment = NULL;
  }
}

static void Ship_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Ship* p = (struct Ship*)body->parent;
    p->hitFromRight = (body->enemy->parent->coord).x > (p->s).coord.x;
  }
}

// 0x08096f64: starts 64 px behind post, away from Zero
static void Ship_Init(struct Ship* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM_FLY);
  UpdateEntityAnim(s);
  SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
  INIT_BODY(p, sCollisions, 8, Ship_OnCollision);
  p->postX = s->coord.x;
  p->postY = s->coord.y;
  s->coord.x += FACING_RIGHT(p) ? -PIXEL(64) : PIXEL(64);
  p->elementEffect = NULL;
  p->scorched = FALSE;
  s->attachment = NULL;
  p->blocked = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = SHIP_PATROL;
  Ship_Update(p);
}

static void Ship_Recoil(struct Ship* p);
static void Ship_Pulled(struct Ship* p);
static void Ship_Recover(struct Ship* p);
static void Ship_Patrol(struct Ship* p);
static void Ship_Brake(struct Ship* p);
static void Ship_Turn(struct Ship* p);
static void Ship_Fire(struct Ship* p);

// 0x08097060
static void Ship_Update(struct Ship* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != SHIP_RECOIL) {
    dropBarrier(p);
    setMode(p, SHIP_RECOIL);
  }
  if (s->mode[1] == SHIP_RECOIL) {
    Ship_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 kind = SHIP_EXPLODE;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? SHIP_CUT_HARD : SHIP_CUT;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    s->mode[2] = 0;
    s->mode[3] = 0;
    EXIT_BODY(p);
    Ship_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    SetDDP(&p->body, &sCollisions[1]);
    dropBarrier(p);
    p->elementEffect = NULL;
    p->scorched = FALSE;
    return;
  }

  // Burned or frozen, loses barrier permanently.
  if (p->elementEffect == NULL && !p->scorched && (status & BODY_STATUS_WHITE)) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
  }
  if (p->elementEffect != NULL) {
    if (!IsDead(p->elementEffect)) {
      SetDDP(&p->body, &sCollisions[2]);
      dropBarrier(p);
      return;
    }
    p->elementEffect = NULL;
    p->scorched = TRUE;
  }
  if (p->scorched) SetDDP(&p->body, &sCollisions[1]);

  if (status & BODY_STATUS_B6) {  // shot hit barrier
    if (s->mode[1] == SHIP_PATROL) swapBarrier(p, ANIM_BARRIER_HIT);
    PlaySound(SE_Z2_SHIP_BLOCK);
    p->blocked++;
  }

  switch (s->mode[1]) {
    case SHIP_PULLED: Ship_Pulled(p); break;
    case SHIP_RECOVER: Ship_Recover(p); break;
    case SHIP_PATROL: Ship_Patrol(p); break;
    case SHIP_BRAKE: Ship_Brake(p); break;
    case SHIP_TURN: Ship_Turn(p); break;
    case SHIP_FIRE: Ship_Fire(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Ship_Recoil(struct Ship* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = SHIP_EXPLODE;
    EXIT_BODY(p);
    Ship_Die(p);
  }
}

// 0x08097240
static void Ship_Pulled(struct Ship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    SetDDP(&p->body, sCollisions);
    swapBarrier(p, ANIM_BARRIER);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
}

// 0x08097294: 33 frames without barrier after firing
static void Ship_Recover(struct Ship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    SetDDP(&p->body, &sCollisions[1]);
    s->work[2] = 32;
    p->blocked = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, SHIP_PATROL);
}

// 0x080972e8: patrols 64 px either side of post
static void Ship_Patrol(struct Ship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    SetDDP(&p->body, sCollisions);
    s->d.x = FACING_RIGHT(p) ? 0x180 : -0x180;
    swapBarrier(p, ANIM_BARRIER);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  if (p->blocked > 3) {
    setMode(p, SHIP_FIRE);
  } else if (s->d.x > 0 ? s->coord.x > p->postX + PIXEL(64) : s->coord.x < p->postX - PIXEL(64)) {
    setMode(p, SHIP_BRAKE);
  }
}

// 0x0809739c
static void Ship_Brake(struct Ship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_BRAKE);
    swapBarrier(p, ANIM_BARRIER_TURN);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.x += FACING_RIGHT(p) ? -16 : 16;
  s->coord.x += s->d.x;
  if (s->d.x == 0) setMode(p, SHIP_TURN);
}

// 0x08097408
static void Ship_Turn(struct Ship* p) {
  struct Entity* s = &p->s;
  s32 speed;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_TURN);
    SET_XFLIP(p, !FACING_RIGHT(p));
    swapBarrier(p, ANIM_BARRIER_TURNED);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.x += FACING_RIGHT(p) ? 16 : -16;
  s->coord.x += s->d.x;
  speed = s->d.x < 0 ? -s->d.x : s->d.x;
  if (speed > 0x17F) setMode(p, SHIP_PATROL);
}

// 0x080974b0
static void Ship_Fire(struct Ship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    swapBarrier(p, ANIM_CHARGE);
    PlaySound(SE_Z2_SHIP_CHARGE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->attachment == NULL || s->attachment->mode[0] > ENTITY_UPDATE) {
    s->attachment = NULL;
    setMode(p, SHIP_RECOVER);
  }
}

// --------------------------------------------

static void finish(struct Ship* p) {
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(0, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// Zero 2 draws two unused random numbers before each smoke
static void wasteRandom(void) {
  RANDOM(RNG_0202f388);
  RANDOM(RNG_0202f388);
}

static void smokes(struct Ship* p) {
  wasteRandom();
  CreateSmoke(2, &(p->s).coord);
  wasteRandom();
  CreateSmoke(2, &(p->s).coord);
  CreateSmoke(1, &(p->s).coord);
}

// 0x0809750c / 0x080975d4 / 0x08097694
static void Ship_Die(struct Ship* p) {
  struct Entity* s = &p->s;
  dropBarrier(p);
  switch (s->mode[1]) {
    case SHIP_EXPLODE:
      createWreck(s, 3, 0);
      createWreck(s, 3, 0);
      createWreck(s, 3, 1);
      smokes(p);
      finish(p);
      return;

    case SHIP_CUT:
      // Hull drops away, rest falls until it lands
      if (s->mode[3] == 0) {
        SetMotion(s, ANIM_CUT);
        s->d.x >>= 2;
        s->d.y = 0;
        createWreck(s, 0, 0);
        s->mode[3]++;
      }
      UpdateEntityAnim(s);
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(16)) == 0) return;
      CreateSmoke(1, &s->coord);
      createWreck(s, 3, 1);
      finish(p);
      return;

    case SHIP_CUT_HARD:
      createWreck(s, 1, 0);
      createWreck(s, 2, 0);
      smokes(p);
      finish(p);
      return;
  }
}

// --------------------------------------------
// Barrier and ring, Zero 2's projectile 62

enum {
  BARRIER,
  RING,
};

static const struct Collision sRing;

static void Barrier_Init(struct Entity* p);
static void Barrier_Update(struct Entity* p);
static void Barrier_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2BarrierShipShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Barrier_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Barrier_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Barrier_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

#define barrierMotion unk_coord.x

// 0x080abe84
static struct Entity* createShot(struct Entity* parent, u8 kind) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BARRIER_SHIP_SHOT);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = FALSE;
  }
  return p;
}

static struct Entity* createBarrier(struct Ship* ship, motion_t m) {
  struct Entity* p = createShot(&ship->s, BARRIER);
  if (p != NULL) p->barrierMotion = m;
  return p;
}

// Ring copies barrier's position and facing
static void createRing(struct Entity* barrier) {
  struct Entity* p = createShot(barrier, RING);
  if (p != NULL) {
    p->coord = barrier->coord;
    p->flags = barrier->flags & X_FLIP;
  }
}

// 0x080abf54 / 0x080abfa4
static void Barrier_Init(struct Entity* p) {
  bool8 right = FACING_RIGHT(p);
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  if (p->work[0] == BARRIER) {
    SetMotion(p, p->barrierMotion);
    UpdateEntityAnim(p);
    p->renderPrio = 23;
  } else {
    SetMotion(p, ANIM_RING);
    UpdateEntityAnim(p);
    INIT_BODY(p, &sRing, 1, NULL);
    SET_XFLIP(p, right);
    p->d.x = right ? 0x300 : -0x300;
    p->coord.x += right ? PIXEL(16) : -PIXEL(16);
    p->work[2] = 64;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Barrier_Update(p);
}

static void Barrier_End(struct Entity* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Barrier_Die(p);
}

// 0x080ac08c: rides on ship until told to go
static void BarrierOnShip_Update(struct Entity* p) {
  struct Entity* ship = p->unk_28;
  if (p->work[1] || ship->mode[0] > ENTITY_UPDATE) {
    Barrier_End(p);
    return;
  }
  UpdateEntityAnim(p);
  SET_XFLIP(p, FACING_RIGHT(ship));
  p->coord = ship->coord;
  if (p->barrierMotion == ANIM_CHARGE) {
    if (IsSpriteAnimEnd(p)) {
      createRing(p);
      Barrier_End(p);
    }
  } else if (p->barrierMotion == ANIM_BARRIER_HIT && IsSpriteAnimEnd(p)) {
    SetMotion(p, ANIM_BARRIER);
    UpdateEntityAnim(p);
    p->barrierMotion = ANIM_BARRIER;
  }
}

// 0x080ac1a0: blinks for last 16 frames
static void Ring_Update(struct Entity* p) {
  UpdateEntityAnim(p);
  p->coord.x += p->d.x;
  if (p->work[2] < 16) {
    if (p->work[2] & 1) {
      p->flags |= DISPLAY;
    } else {
      p->flags &= ~DISPLAY;
    }
  }
  if (--p->work[2] == 0xFF || FUN_080098a4(p->coord.x, p->coord.y) != 0) Barrier_End(p);
}

static void Barrier_Update(struct Entity* p) {
  if (p->work[0] == BARRIER) {
    BarrierOnShip_Update(p);
  } else {
    Ring_Update(p);
  }
}

static void Barrier_Die(struct Entity* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
// Wreckage, Zero 2's VFX 68: hull (0), halves (1, 2), small pieces (3)

static const motion_t sPieces[2] = {ANIM(3), ANIM(4)};

static void Wreck_Init(struct VFX* p);
static void Wreck_Update(struct VFX* p);
static void Wreck_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2BarrierShipWreckRoutine = {
    [ENTITY_INIT] =      Wreck_Init,
    [ENTITY_UPDATE] =    Wreck_Update,
    [ENTITY_DIE] =       Wreck_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080be1ac. Copies what it needs from parent.
static void createWreck(struct Entity* parent, u8 kind, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_BARRIER_SHIP_WRECK);
    (p->s).work[0] = kind;
    (p->s).work[1] = n;
    (p->s).flags = parent->flags & X_FLIP;
    (p->s).coord = parent->coord;
    (p->s).d.x = parent->d.x;
  }
}

static s32 spinUp(void) { return -(((RANDOM(RNG_0202f388) & 7) + 16) << 6); }

// 0x080be280 / 0x080be318 / 0x080be43c / 0x080be544
static void Wreck_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  bool8 right = (s->flags & X_FLIP) != 0;
  s->flags = 0;
  if (s->work[0] == 1 || s->work[0] == 2) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case 0:
      SetMotion(s, ANIM(1));
      s->d.x <<= 2;
      s->d.y = 0;
      break;
    case 1:
      SetMotion(s, ANIM(1));
      s->d.x = (RANDOM(RNG_0202f388) & 0xFF) + PIXEL(1);
      if (!right) s->d.x = -s->d.x;
      s->d.y = spinUp();
      s->work[3] = -3;
      s->work[2] = RANDOM(RNG_0202f388);
      s->angle = s->work[2];
      break;
    case 2:
      SetMotion(s, ANIM_CUT);
      s->d.x = right ? 0 : (RANDOM(RNG_0202f388) & 0xFF) + PIXEL(1);
      s->d.y = spinUp();
      s->work[3] = 3;
      s->work[2] = RANDOM(RNG_0202f388);
      s->angle = s->work[2];
      break;
    case 3:
      SetMotion(s, sPieces[s->work[1]]);
      s->d.x = PIXEL(2) - (RANDOM(RNG_0202f388) & 0x3FF);
      s->d.y = -(((RANDOM(RNG_0202f388) & 3) + 8) << 6);
      break;
  }
  UpdateEntityAnim(s);
  SET_XFLIP(p, right);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Wreck_Update(p);
}

static void Wreck_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->work[0] == 1 || s->work[0] == 2) {
    s->work[2] += s->work[3];
    s->angle = s->work[2];
  }
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  switch (s->work[0]) {
    case 0:
      createWreck(s, 3, 0);
      CreateSmoke(1, &s->coord);
      PlaySound(SE_ZAKO_EXPLODE);
      break;
    case 1:
    case 2:
      createWreck(s, 3, RANDOM(RNG_0202f388) & 1);
      CreateSmoke(1, &s->coord);
      break;
    case 3:
      CreateSmoke(3, &s->coord);
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_DIE);
}

static void Wreck_Die(struct VFX* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[3] = {
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, METAL, 0, 2, 0xffffffff, {-0xd00, 0x0, 0xc00, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x400, 0x0, 0x1600, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x400, 0x0, 0x1600, 0x1400}},
};

static const struct Collision sRing =
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}};
// clang-format on

#endif  // AP
