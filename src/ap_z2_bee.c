#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's bee, enemy 8. Bee carrier is enemy 10.
  work0:
    0: circles a point
    1: circles its carrier
*/

struct Bee {
  OBJECT_HDR;
  u16 timer;       // 0xB4
  u8 phase;        // 0xB6, position around centre
  bool8 attached;  // 0xB7, circling carrier
  s32 centreX;     // 0xB8
  s32 centreY;     // 0xBC
  u8 _[4];
};
static_assert(sizeof(struct Bee) == sizeof(struct Enemy));

struct Carrier {
  OBJECT_HDR;
  bool8 gone;                    // 0xB4, read by its bees
  u8 _b5[3];
  s32 baseY;                     // 0xB8
  struct Entity* elementEffect;  // 0xBC
  u8 _[4];
};
static_assert(sizeof(struct Carrier) == sizeof(struct Enemy));

struct Bomb {
  OBJECT_HDR;
  bool8 released;  // 0xB4
  bool8 open;      // 0xB5, carrier may leave
  u8 _[14];
};
static_assert(sizeof(struct Bomb) == sizeof(struct Projectile));

enum {
  BEE_CIRCLE,
  BEE_DIVE,
  BEE_ELEMENT_HIT,
  BEE_RECOIL,
  BEE_DECIDE = 255,
};

enum {
  BEE_EXPLODE,
  BEE_CUT,
  BEE_CUT_HARD,
};

enum {
  CARRIER_HOVER,
  CARRIER_DROP,
  CARRIER_LEAVE,
  CARRIER_ELEMENT_HIT,
  CARRIER_RECOIL,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_BEE, (n))
#define CARRIER_ANIM(n) MOTION(AP_SHEET_Z2_BEE_CARRIER, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

static const struct Collision sCollisions[2];
static const struct Collision sHarmless;
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sHeadGib;
static const struct Collision sCarrierCollisions[2];
static const struct Collision sCarrierHarmless;
static const Coords32 sElementCoord = {0, 0};

static void Bee_Init(struct Bee* p);
static void Bee_Update(struct Bee* p);
static void Bee_Die(struct Bee* p);
static void Carrier_Init(struct Carrier* p);
static void Carrier_Update(struct Carrier* p);
static void Carrier_Die(struct Carrier* p);
static void Carrier_Disappear(struct Carrier* p);
static struct Entity* createBomb(struct Carrier* carrier);
static void createHead(struct Bee* bee, bool8 hard);

// clang-format off
const EnemyRoutine gApZ2BeeRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Bee_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Bee_Update,
    [ENTITY_DIE] =       (EnemyFunc)Bee_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

const EnemyRoutine gApZ2BeeCarrierRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Carrier_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Carrier_Update,
    [ENTITY_DIE] =       (EnemyFunc)Carrier_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)Carrier_Disappear,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(void* p, u8 mode) {
  ((struct Entity*)p)->mode[1] = mode;
  ((struct Entity*)p)->mode[2] = 0;
}

static void disappear(struct Entity* p) {
  p->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

static bool8 offScreen(struct Entity* p) {
  return Camera_GetDistance(&gStageRun.vm.camera, &p->coord) > PIXEL(32);
}

static void fall(struct Entity* p) {
  p->d.y += 0x40;
  if (p->d.y > 0x700) p->d.y = 0x700;
}

static void countKill(struct Entity* p, u8 dropTable) {
  TryDropItem(dropTable, (struct Coord*)&p->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &p->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Bee

// Motion table at 0x0833e364, a row of five per facing
static void gotoAnim(struct Bee* p, u8 n) {
  struct Entity* s = &p->s;
  GotoMotion(s, ANIM(FACING_RIGHT(p) ? n + 10 : n), (s->motion).cmdIdx, (s->motion).duration);
}

static void faceZero(struct Bee* p, u8 n) {
  bool8 right = (p->s).coord.x < (pZero2->s).coord.x;
  if (right != FACING_RIGHT(p)) {
    SET_XFLIP(p, right);
    gotoAnim(p, n);
  }
}

// Current position becomes top of circle
static void topOfCircle(struct Bee* p) {
  p->phase = 192;
  p->centreX = (p->s).coord.x;
  p->centreY = (p->s).coord.y + PIXEL(16);
}

static void circle(struct Bee* p, s32 radius) {
  (p->s).coord.x = p->centreX + COS(p->phase) * radius;
  (p->s).coord.y = p->centreY + SIN(p->phase) * radius;
}

static void Bee_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = p->coord.x < (pZero2->s).coord.x;
  }
}

// 0x0806a290
static void Bee_Init(struct Bee* p) {
  struct Entity* s = &p->s;
  bool8 right = s->coord.x < (pZero2->s).coord.x;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, sCollisions, 2, Bee_OnCollision);
  SET_XFLIP(p, right);
  SetMotion(s, ANIM(right ? 10 : 0));
  UpdateEntityAnim(s);
  p->attached = TRUE;
  if (s->work[0] == 0) {
    topOfCircle(p);
  } else {
    p->centreX = s->unk_28->coord.x;
    p->centreY = s->unk_28->coord.y;
    circle(p, 24);
  }
  s->unk_2c = NULL;
  Bee_Update(p);
}

static void Bee_Recoil(struct Bee* p);
static void Bee_Circle(struct Bee* p);
static void Bee_Dive(struct Bee* p);
static void Bee_ElementHit(struct Bee* p);

// 0x0806b0fc: dives 9 times in 16 with Zero close. Bee on carrier waits out the drop.
static void decide(struct Bee* p) {
  struct Entity* s = &p->s;
  s32 dx = s->coord.x - (pZero2->s).coord.x;
  s32 dy = s->coord.y - (pZero2->s).coord.y;
  bool8 waiting = s->work[0] == 1 && p->attached && s->unk_28->mode[1] != CARRIER_HOVER;
  if (!waiting && (u32)(dx + PIXEL(112)) < PIXEL(224) && (u32)(dy + PIXEL(160)) < PIXEL(320) &&
      (RANDOM(RNG_0202f388) & 15) <= 8) {
    setMode(p, BEE_DIVE);
  } else {
    setMode(p, BEE_CIRCLE);
  }
}

// 0x0806a4a4, and 0x0806a530 for a bee that came with a carrier
static void Bee_Update(struct Bee* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != BEE_RECOIL) setMode(p, BEE_RECOIL);
  if (s->mode[1] == BEE_RECOIL) {
    Bee_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = BEE_EXPLODE;
    if (status & BODY_STATUS_SLASHED) s->mode[1] = (status & BODY_STATUS_B15) ? BEE_CUT_HARD : BEE_CUT;
    EXIT_BODY(p);
    Bee_Die(p);
    return;
  }

  if (s->work[0] == 1 && s->mode[1] == BEE_CIRCLE) {
    struct Carrier* carrier = (struct Carrier*)s->unk_28;
    if (!p->attached) {
      if (offScreen(s)) {
        disappear(s);
        return;
      }
    } else if (carrier == NULL || (carrier->s).mode[0] > ENTITY_UPDATE) {
      p->attached = FALSE;
    } else if (carrier->gone) {
      disappear(s);
      return;
    } else {
      p->centreX = (carrier->s).coord.x;
      p->centreY = (carrier->s).coord.y;
    }
  }

  if (IsFrozen(p)) {
    if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) setMode(p, BEE_ELEMENT_HIT);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;

  if (s->mode[1] == BEE_DECIDE) decide(p);
  switch (s->mode[1]) {
    case BEE_CIRCLE: Bee_Circle(p); break;
    case BEE_DIVE: Bee_Dive(p); break;
    case BEE_ELEMENT_HIT: Bee_ElementHit(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Bee_Recoil(struct Bee* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = BEE_EXPLODE;
    EXIT_BODY(p);
    Bee_Die(p);
  }
}

// 0x0806a710, and 0x0806a850 around a carrier
static void Bee_Circle(struct Bee* p) {
  struct Entity* s = &p->s;
  bool8 onCarrier = s->work[0] == 1;
  if (s->mode[2] == 0) {
    gotoAnim(p, 0);
    SetDDP(&p->body, sCollisions);
    p->timer = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  p->timer++;
  circle(p, onCarrier ? 24 : 16);
  p->phase += onCarrier ? 3 : 4;
  faceZero(p, 0);
  if (p->timer > (onCarrier ? 63 : 31)) s->mode[1] = BEE_DECIDE;
}

// 0x0806a998: aims 16 px above Zero's feet
static void Bee_Dive(struct Bee* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0: {
      s32 dx = (pZero2->s).coord.x - s->coord.x;
      s32 dy = (pZero2->s).coord.y - PIXEL(16) - s->coord.y;
      u16 frames;
      SetDDP(&p->body, sCollisions);
      frames = Sqrt((dx * dx / 256 + dy * dy / 256) >> 8) >> 2;
      if (frames == 0) {
        setMode(p, BEE_CIRCLE);
        return;
      }
      s->d.x = dx / frames;
      s->d.y = dy / frames;
      // Zero 2 sets left-facing row here, only changes it on a turn
      GotoMotion(s, ANIM(4), (s->motion).cmdIdx, (s->motion).duration);
      faceZero(p, 1);
      p->timer = 0;
      s->mode[2]++;
    }
    // fallthrough
    case 1:
      UpdateEntityAnim(s);
      if (++p->timer > 2) {
        gotoAnim(p, 2);
        p->timer = 0;
        s->mode[2]++;
      }
      return;
    case 2:
      UpdateEntityAnim(s);
      if (++p->timer > 14) {
        gotoAnim(p, 3);
        p->timer = 0;
        s->mode[2]++;
      }
      return;
    case 3:
      UpdateEntityAnim(s);
      if (++p->timer > 2) {
        PlaySound(SE_UNK_108);
        gotoAnim(p, 4);
        s->mode[2]++;
      }
      return;
    case 4:
      UpdateEntityAnim(s);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (offScreen(s)) {
        disappear(s);
      } else if ((u32)(s->coord.x - p->centreX + PIXEL(240)) > PIXEL(480)) {
        s->d.y = -PIXEL(2);
        s->mode[2]++;
      }
      return;
    default:
      UpdateEntityAnim(s);
      s->coord.y += s->d.y;
      if (offScreen(s)) disappear(s);
      return;
  }
}

// 0x0806acbc: drops to floor, then circles where it lies
static void Bee_ElementHit(struct Bee* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sHarmless);
    s->d.y = 0;
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    s->coord.y += s->d.y;
    fall(s);
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2]++;
    }
  }
  if (s->unk_2c == NULL) {
    topOfCircle(p);
    setMode(p, BEE_CIRCLE);
    p->attached = FALSE;
  }
}

static s32 jitter(void) { return ((RANDOM(RNG_0202f388) & 15) - 7) << 8; }

// 0x0806ad88: three pieces, flung away from Zero
static void explode(struct Bee* p) {
  struct Entity* s = &p->s;
  u8 flip = s->work[3] * 0x11;
  Coords32 c;
  s32 i;
  for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[i], 0, flip));
  c.x = s->coord.x + jitter();
  c.y = s->coord.y + jitter();
  CreateSmoke(1, &c);
  c.x = s->coord.x + jitter();
  c.y = s->coord.y + jitter();
  CreateSmoke(2, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  countKill(s, 3);
}

// 0x0806aeb4, and 0x0806af9c cut hard: head flies off, body falls then bursts
static void fallHeadless(struct Bee* p, bool8 hard) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    createHead(p, hard);
    SetMotion(s, ANIM(6));
    if (hard) {
      u16 r = RANDOM(RNG_0202f388) & 0x1FF;
      s->d.x = s->work[3] == 0 ? r + 1 : -r - 1;
      s->d.y = -0x300 - (RANDOM(RNG_0202f388) & 0xFF);
    } else {
      s->d.y = 0;
    }
    s->work[2] = 128;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (hard) s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0 && --s->work[2] != 0) {
    fall(s);
    return;
  }
  PlaySound(SE_ZAKO_EXPLODE);
  CreateSmoke(1, &s->coord);
  useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[0], 0, FACING_RIGHT(p) * 0x11));
  useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[1], 0, FACING_RIGHT(p) * 0x11));
  countKill(s, 3);
}

// 0x0806a6a8
static void Bee_Die(struct Bee* p) {
  switch ((p->s).mode[1]) {
    case BEE_EXPLODE: explode(p); break;
    case BEE_CUT: fallHeadless(p, FALSE); break;
    case BEE_CUT_HARD: fallHeadless(p, TRUE); break;
  }
}

// --------------------------------------------
// Carrier

// 0x0806a1ac
static void createBees(struct Carrier* carrier) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct Bee* p = (struct Bee*)AllocEntityLast(gEnemyHeaderPtr);
    if (p != NULL) {
      INIT_ENEMY_ROUTINE(p, ENEMY_Z2_BEE);
      (p->s).unk_28 = &carrier->s;
      (p->s).coord = (carrier->s).coord;
      (p->s).work[0] = 1;
      p->phase = i * 85;
    }
  }
}

// 0x0806c338
static void Carrier_Init(struct Carrier* p) {
  struct Entity* s = &p->s;
  s->unk_2c = createBomb(p);
  if (s->unk_2c == NULL) {
    disappear(s);
    return;
  }
  createBees(p);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, CARRIER_ANIM(3));
  UpdateEntityAnim(s);
  INIT_BODY(p, sCarrierCollisions, 2, NULL);
  s->d.x = s->d.y = 0;
  SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
  p->gone = FALSE;
  p->baseY = s->coord.y;
  p->elementEffect = NULL;
  Carrier_Update(p);
}

static void Carrier_Recoil(struct Carrier* p);
static void Carrier_Hover(struct Carrier* p);
static void Carrier_Drop(struct Carrier* p);
static void Carrier_Leave(struct Carrier* p);
static void Carrier_ElementHit(struct Carrier* p);

// 0x0806c440
static void Carrier_Update(struct Carrier* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != CARRIER_RECOIL) setMode(p, CARRIER_RECOIL);
  if (s->mode[1] == CARRIER_RECOIL) {
    Carrier_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    if (s->unk_2c != NULL) ((struct Bomb*)s->unk_2c)->released = TRUE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Carrier_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      SetDDP(&p->body, sCarrierCollisions);
    }
    return;
  }

  if ((status & BODY_STATUS_WHITE) && p->elementEffect == NULL) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->elementEffect != NULL) setMode(p, CARRIER_ELEMENT_HIT);
  }
  if (p->elementEffect != NULL && IsDead(p->elementEffect)) p->elementEffect = NULL;

  switch (s->mode[1]) {
    case CARRIER_HOVER: Carrier_Hover(p); break;
    case CARRIER_DROP: Carrier_Drop(p); break;
    case CARRIER_LEAVE: Carrier_Leave(p); break;
    case CARRIER_ELEMENT_HIT: Carrier_ElementHit(p); break;
  }
}

static void Carrier_Recoil(struct Carrier* p) {
  if (ApRecoilFly((Object*)p)) {
    struct Entity* s = &p->s;
    if (s->unk_2c != NULL) ((struct Bomb*)s->unk_2c)->released = TRUE;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Carrier_Die(p);
  }
}

// 0x0806c60c: bobs until Zero is under it
static void Carrier_Hover(struct Carrier* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sCarrierCollisions);
    SetMotion(s, CARRIER_ANIM(3));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y = p->baseY + SIN(s->work[2]) * 16;
  s->work[2]++;
  if (s->coord.y > gStageRun.vm.camera.viewport.y - PIXEL(80) && s->coord.y < (z->s).coord.y &&
      (u32)(s->coord.x - (z->s).coord.x + PIXEL(24)) < PIXEL(48)) {
    setMode(p, CARRIER_DROP);
  }
}

// 0x0806c6a4: lets go of bomb when it opens
static void Carrier_Drop(struct Carrier* p) {
  struct Entity* s = &p->s;
  struct Bomb* bomb = (struct Bomb*)s->unk_2c;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sCarrierCollisions);
      if (bomb != NULL) bomb->released = TRUE;
      SetMotion(s, CARRIER_ANIM(3));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateEntityAnim(s);
      if (bomb == NULL || bomb->open) {
        s->unk_2c = NULL;
        s->work[2] = 0;
        s->mode[2]++;
      }
      return;
    case 2:
      UpdateEntityAnim(s);
      if (++s->work[2] > 2) {
        SetMotion(s, CARRIER_ANIM(0));
        s->work[2] = 0;
        s->mode[2]++;
      }
      return;
    case 3:
      UpdateEntityAnim(s);
      if (++s->work[2] > 2) {
        SetMotion(s, CARRIER_ANIM(1));
        s->work[2] = 0;
        s->mode[2]++;
      }
      return;
    case 4:
      UpdateEntityAnim(s);
      if (++s->work[2] > 14) {
        SetMotion(s, CARRIER_ANIM(2));
        s->work[2] = 0;
        s->mode[2]++;
      }
      return;
    default:
      UpdateEntityAnim(s);
      if (++s->work[2] > 2) setMode(p, CARRIER_LEAVE);
      return;
  }
}

// 0x0806c7c4
static void Carrier_Leave(struct Carrier* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_UNK_108);
    SetDDP(&p->body, sCarrierCollisions);
    SetMotion(s, CARRIER_ANIM(3));
    s->d.x = FACING_RIGHT(p) ? PIXEL(2) : -PIXEL(2);
    s->d.y = PIXEL(1);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y -= 32;
  if (s->coord.y <= gStageRun.vm.camera.viewport.y - PIXEL(176)) disappear(s);
}

// 0x0806c890: same as bee, then bobs where it landed
static void Carrier_ElementHit(struct Carrier* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sCarrierHarmless);
    s->d.y = 0;
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    s->coord.y += s->d.y;
    fall(s);
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2]++;
    }
  }
  if (p->elementEffect == NULL) {
    p->baseY = s->coord.y;
    setMode(p, CARRIER_HOVER);
  }
}

static s32 carrierJitter(void) { return ((RANDOM(RNG_0202f388) & 31) - 15) << 8; }

// 0x0806c518
static void Carrier_Die(struct Carrier* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  c.x = s->coord.x + carrierJitter();
  c.y = s->coord.y + carrierJitter();
  CreateSmoke(1, &c);
  c.x = s->coord.x + carrierJitter();
  c.y = s->coord.y + carrierJitter();
  CreateSmoke(2, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  countKill(s, 0);
}

// 0x0806c5f8
static void Carrier_Disappear(struct Carrier* p) {
  p->gone = TRUE;
  DeleteEnemy(&p->s);
}

// --------------------------------------------
// Bomb, Zero 2's projectile 6

static const struct Collision sBomb[2];

static void Bomb_Init(struct Bomb* p);
static void Bomb_Update(struct Bomb* p);
static void Bomb_Die(struct Bomb* p);
static void createBlast(Coords32* c, u8 angle);

// clang-format off
const ProjectileRoutine gApZ2BeeBombRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Bomb_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Bomb_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Bomb_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x08099564
static struct Entity* createBomb(struct Carrier* carrier) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BEE_BOMB);
    p->unk_28 = &carrier->s;
    p->coord.x = (carrier->s).coord.x;
    p->coord.y = (carrier->s).coord.y + PIXEL(8);
  }
  return p;
}

// 0x080995b8
static void Bomb_Init(struct Bomb* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  (s->spr).oam.priority = 2;
  INIT_BODY(p, sBomb, 1, NULL);
  SET_XFLIP(p, FACING_RIGHT(s->unk_28));
  SetMotion(s, CARRIER_ANIM(4));
  UpdateEntityAnim(s);
  s->d.y = 0;
  p->released = FALSE;
  p->open = FALSE;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Bomb_Update(p);
}

static void explodeBomb(struct Bomb* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  (p->s).mode[1] = 0;
  Bomb_Die(p);
}

// 0x08099688
static void Bomb_Update(struct Bomb* p) {
  struct Entity* s = &p->s;
  struct Entity* carrier = s->unk_28;
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    explodeBomb(p);
    return;
  }
  if (!p->released) {
    if (carrier->mode[0] > ENTITY_UPDATE) {
      s->flags &= ~(DISPLAY | FLIPABLE);
      EXIT_BODY(p);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    s->coord.x = carrier->coord.x;
    s->coord.y = carrier->coord.y + PIXEL(8);
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) explodeBomb(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      SetMotion(s, CARRIER_ANIM(5));
      s->mode[1]++;
      // fallthrough
    case 1:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) {
        p->open = TRUE;
        s->work[2] = 128;
        s->mode[1]++;
      }
      return;
    default:
      s->coord.y += s->d.y;
      if (((p->body).status & BODY_STATUS_B2) || FUN_080098a4(s->coord.x, s->coord.y) != 0 ||
          --s->work[2] == 0) {
        explodeBomb(p);
        return;
      }
      fall(s);
      return;
  }
}

// 0x08099834: nine blasts in a turning ring, each shaking screen
static void Bomb_Die(struct Bomb* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    if (!p->released && s->unk_28->mode[0] <= ENTITY_UPDATE) s->unk_28->unk_2c = NULL;
    EXIT_BODY(p);
    s->flags &= ~DISPLAY;
    s->work[2] = 0;
    PlaySound(SE_UNK_35);
    s->mode[1]++;
  }
  if ((s->work[2] & 1) == 0) {
    createBlast(&s->coord, ((s->work[2] >> 1) & 7) << 5);
    AppendQuake(4, &s->coord);
    if (s->work[2] == 16) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
      return;
    }
  }
  s->work[2]++;
}

// --------------------------------------------
// Blast, Zero 2's projectile 7

static const struct Collision sBlast;

static void Blast_Init(struct Entity* p);
static void Blast_Update(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2BeeBlastRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Blast_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Blast_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x08099900
static void createBlast(Coords32* c, u8 angle) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BEE_BLAST);
    p->coord = *c;
    p->work[0] = angle;
  }
}

// 0x08099950
static void Blast_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  p->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, &sBlast, 0, NULL);
  p->d.x = SIN(p->work[0]) * 2;
  p->d.y = COS(p->work[0]) * 2;
  SetMotion(p, MOTION(SM000_BATTLE_EFFECT, 1));
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Blast_Update(p);
}

// 0x080999d8
static void Blast_Update(struct Entity* p) {
  UpdateEntityAnim(p);
  p->coord.x += p->d.x;
  p->coord.y += p->d.y;
  if (IsSpriteAnimEnd(p)) {
    EXIT_BODY(p);
    p->flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
  }
}

// --------------------------------------------
// Cut bee's head, Zero 2's VFX 20. Facing passed in work[3].

static void Head_Init(struct VFX* p);
static void Head_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2BeeHeadRoutine = {
    [ENTITY_INIT] =      Head_Init,
    [ENTITY_UPDATE] =    Head_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b188c
static void createHead(struct Bee* bee, bool8 hard) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_BEE_HEAD);
    (p->s).coord = (bee->s).coord;
    (p->s).work[0] = hard;
    (p->s).work[1] = (bee->s).work[3];
    (p->s).work[3] = FACING_RIGHT(bee);
  }
}

// 0x080b18e8
static void Head_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, s->work[3]);
  s->flags |= DISPLAY | FLIPABLE;
  s->renderPrio = 25;
  SetMotion(s, ANIM(5));
  if (s->work[0]) {
    s->d.x = (s->work[1] * 2 - 1) * ((RANDOM(RNG_0202f388) & 0xFF) + 0x100);
    s->d.y = -0x400 - (RANDOM(RNG_0202f388) & 0xFF);
  } else {
    s->d.x = 0;
    s->d.y = -0x180;
  }
  s->work[2] = 255;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Head_Update(p);
}

// 0x080b19d4
static void Head_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->work[2]--;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0 && s->work[2] != 0) {
    fall(s);
    return;
  }
  useApSheets(CreateSlashedEnemy(&s->coord, &sHeadGib, 0, FACING_RIGHT(p) * 0x11));
  CreateSmoke(2, &s->coord);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}};

static const struct Collision sCarrierCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x1800}},
};

static const struct Collision sCarrierHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x1800}};

static const struct Collision sBomb[2] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x03, 0, 0, 1, 0x00000001, {0x0, 0x200, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x03, 0, 0, 0, 0x00000000, {0x0, 0x200, 0x1000, 0x1000}},
};

static const struct Collision sBlast =
    {DDP, FACTION_NEUTRAL, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x2000, 0x2000}};

static const struct SlashedEnemy sGibs[3] = {
    {MOTION(AP_SHEET_Z2_BEE, 7), {0xff, 0x11}, {0, 0}, {96, -768}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_BEE, 8), {0xff, 0x11}, {0, 0}, {128, -1024}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_BEE, 9), {0xff, 0x11}, {0, 0}, {256, -1280}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sHeadGib =
    {MOTION(AP_SHEET_Z2_BEE, 9), {0xff, 0x11}, {0, 0}, {96, -768}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}};
// clang-format on

#endif  // AP
