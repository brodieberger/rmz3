#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's robot wolf, enemy 66.
  work0:
    0: paces near home
    1: same, but goes when 96 px off screen
    2: invisible bite
    3: invisible jaws, used while running or pouncing
*/

struct Wolf {
  OBJECT_HDR;
  s32 hitFromX;                  // 0xB4, Zero's x minus its own at last hit
  struct Entity* elementEffect;  // 0xB8
  u8 _bc;
  u8 homing;                     // 0xBD, 1: heading home, 2: turned back at edge of range
  u16 pounceAngle;               // 0xBE
  s32 homeX;                     // 0xC0
};
static_assert(sizeof(struct Wolf) == sizeof(struct Enemy));

enum {
  WOLF_IDLE,
  WOLF_FALL,
  WOLF_RUN,
  WOLF_POUNCE,
  WOLF_LAND,
  WOLF_LATCHED,
  WOLF_LEAP_OFF,
  WOLF_BITE,   // bite part
  WOLF_FLINCH,
  WOLF_NONE,
  WOLF_JAWS,   // jaws part
  WOLF_RECOIL,
  WOLF_PULLED,
};

enum {
  WOLF_BURST,
  WOLF_CUT,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_WOLF, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define IS_PART(s) ((s)->work[0] >= 2)

static const struct Collision sBody[2];
static const struct Collision sRunning[2];
static const struct Collision sLatched[2];
static const struct Collision sPouncing[2];
static const struct Collision sLeaping[2];
static const struct Collision sBite[2];
static const struct Collision sJaws[2];
static const struct Collision sHarmless;
static const Coords32 sElementCoord = {0, -PIXEL(6)};
static const u8 sStartModes[4] = {WOLF_IDLE, WOLF_IDLE, WOLF_BITE, WOLF_JAWS};

static u16 Wolf_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Wolf_Init(struct Wolf* p);
static void Wolf_Update(struct Wolf* p);
static void Wolf_Die(struct Wolf* p);
static void createPieces(struct Wolf* wolf, Coords32* c);
static void createHalf(struct Wolf* wolf);

// clang-format off
const EnemyRoutine gApZ2WolfRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Wolf_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Wolf_Update,
    [ENTITY_DIE] =       (EnemyFunc)Wolf_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Wolf* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void disappear(struct Entity* s) {
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(s);
  SET_ENEMY_ROUTINE(s, ENTITY_DISAPPEAR);
}

static void face(struct Wolf* p, bool8 right) { SET_XFLIP(p, right); }
static void turnRound(struct Wolf* p) { face(p, !FACING_RIGHT(p)); }
static void setPriority(struct Wolf* p, u8 n) { ((p->s).spr).oam.priority = n; }
static s32 abs32(s32 v) { return v < 0 ? -v : v; }
// 0x0808c348
static u16 Wolf_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  s->mode[1] = WOLF_PULLED;
  s->mode[2] = 0;
  s->d.x = dx;
  s->d.y = dy;
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling && FUN_080098a4(s->coord.x, s->coord.y) == 0) return 1;
  s->mode[1] = WOLF_FALL;
  return 0;
}

static bool8 zeroInFront(struct Wolf* p) { return FACING_RIGHT(p) == ((pZero2->s).coord.x > (p->s).coord.x); }
static bool8 facingAwayFromHome(struct Wolf* p) { return FACING_RIGHT(p) == ((p->s).coord.x >= p->homeX); }

static void fall(struct Entity* s) {
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

static struct Entity* createPart(struct Wolf* wolf, u8 kind, u8 which) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_WOLF);
    p->coord = (wolf->s).coord;
    p->work[0] = kind;
    p->work[1] = which;
    p->unk_28 = &wolf->s;
  }
  return p;
}

// --------------------------------------------
// Zero 2's ground helpers, shared with enemy 65 (0x0808bacc..0x0808bd9c)

// 0x0808bacc: turns back if over 256 px from home and still going
static bool8 decide(struct Wolf* p) {
  struct Entity* s = &p->s;
  s->mode[1] = WOLF_IDLE;
  if ((zeroInFront(p) && p->homing != 1) || abs32(s->coord.x - p->homeX) <= PIXEL(256) || !facingAwayFromHome(p)) {
    s->mode[2] = 2;
    return FALSE;
  }
  s->mode[2] = 4;
  p->homing = 2;
  return TRUE;
}

// 0x0808bb60: highest floor under front, middle and back is at its feet or above
static bool8 standing(struct Entity* s) {
  s32 back = FUN_08009f6c(s->coord.x - PIXEL(8), s->coord.y);
  s32 mid = FUN_08009f6c(s->coord.x, s->coord.y);
  s32 front = FUN_08009f6c(s->coord.x + PIXEL(8), s->coord.y);
  s32 top = back;
  if (mid < top) top = mid;
  if (front < top) top = front;
  return top - s->coord.y <= 0;
}

// 0x0808bbe0
static void snapToFloor(struct Entity* s) {
  s32 f = FUN_08009f6c(s->coord.x, s->coord.y);
  if (f - s->coord.y <= PIXEL(5)) s->coord.y = f;
}

// Floor rule of both followers. Returns TRUE when it moved.
static bool8 followFloor(struct Entity* s, bool8 rising) {
  s32 f;
  if (rising) {
    s32 head = FUN_0800a134(s->coord.x, s->coord.y - PIXEL(20));
    if (s->coord.y - PIXEL(20) < head) {
      s->coord.y = head + PIXEL(20);
      return TRUE;
    }
    return FALSE;
  }
  f = FUN_08009f6c(s->coord.x, s->coord.y);
  if (FUN_080098a4(s->coord.x, s->coord.y) & MTATTR_SOFT_PLATFORM) {
    if (abs32(f - s->coord.y) <= 0x3FF || s->d.y > 0x400) {
      s->coord.y = f;
      return TRUE;
    }
  } else if (f - s->coord.y <= 0x43F) {
    s->coord.y = f;
    return TRUE;
  }
  return FALSE;
}

// 0x0808bc04: floor rule, then walls 10 px ahead and behind. Returns TRUE when a wall pushed
// it back.
static bool8 followGround(struct Wolf* p) {
  struct Entity* s = &p->s;
  u16 below;
  s32 r;
  followFloor(s, (s->mode[1] == WOLF_POUNCE || s->mode[1] == WOLF_LEAP_OFF) && s->d.y < 0);
  below = GetMetatileAttr(s->coord.x, s->coord.y + PIXEL(1));
  if ((below & 1) || below == 0) {
    if ((FUN_080098a4(s->coord.x + PIXEL(10), s->coord.y - PIXEL(4)) & 1) &&
        (r = PushoutToLeft1(s->coord.x + PIXEL(10), s->coord.y - PIXEL(4))) < 0) {
      s->coord.x += r;
      return TRUE;
    }
    if ((FUN_080098a4(s->coord.x - PIXEL(10), s->coord.y - PIXEL(4)) & 1) &&
        (r = PushoutToRight1(s->coord.x - PIXEL(10), s->coord.y - PIXEL(4))) > 0) {
      s->coord.x += r;
      return TRUE;
    }
    return FALSE;
  }
  // On a slope, only the wall 16 px up counts
  if ((r = PushoutToLeft1(s->coord.x + PIXEL(10), s->coord.y - PIXEL(16))) < 0 ||
      (r = PushoutToRight1(s->coord.x - PIXEL(10), s->coord.y - PIXEL(16))) > 0) {
    s->coord.x += r;
    return TRUE;
  }
  return FALSE;
}

// 0x0808bd9c: dying wolf's step. Only lands or slides, returned flags go unread.
static void followGroundFalling(struct Entity* s) {
  s32 r;
  if (s->d.y != 0) followFloor(s, s->d.y < 0);
  if (s->d.x > 0 && (r = PushoutToLeft1(s->coord.x + PIXEL(10), s->coord.y - PIXEL(4))) < 0) s->coord.x += r;
  if (s->d.x < 0 && (r = PushoutToRight1(s->coord.x - PIXEL(10), s->coord.y - PIXEL(4))) > 0) s->coord.x += r;
}

// --------------------------------------------

static void Wolf_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Wolf* p = (struct Wolf*)body->parent;
  p->hitFromX = (pZero2->s).coord.x - (p->s).coord.x;
}

// 0x0808beb8
static void Wolf_Init(struct Wolf* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(p, sStartModes[s->work[0]]);
  s->flags |= FLIPABLE;
  if (!IS_PART(s)) {
    s32 back, front;
    if (PushoutToUp1(s->coord.x, s->coord.y) < -PIXEL(64)) {
      disappear(s);
      return;
    }
    InitNonAffineMotion(s);
    useApSheets(p);
    s->flags |= DISPLAY;
    INIT_BODY(p, sBody, 12, Wolf_OnCollision);
    (p->body).unk_28 = (u32)Wolf_Pull;
    back = FUN_08009f6c(s->coord.x - PIXEL(10), s->coord.y);
    front = FUN_08009f6c(s->coord.x + PIXEL(10), s->coord.y);
    s->coord.y = front < back ? front : back;
    SetMotion(s, ANIM(1));
  } else {
    INIT_BODY(p, s->work[0] == 2 ? sBite : sJaws, 12, Wolf_OnCollision);
  }
  p->homeX = s->coord.x;
  face(p, (pZero2->s).coord.x > s->coord.x);
  p->elementEffect = NULL;
  p->homing = 0;
  Wolf_Update(p);
}

static void offScreenCheck(struct Wolf* p);
static void groundCheck(struct Wolf* p);
static void airCheck(struct Wolf* p);
static void latchedCheck(struct Wolf* p);
static void Wolf_Recoil(struct Wolf* p);
static void Wolf_Idle(struct Wolf* p);
static void Wolf_Fall(struct Wolf* p);
static void Wolf_Run(struct Wolf* p);
static void Wolf_Pounce(struct Wolf* p);
static void Wolf_Land(struct Wolf* p);
static void Wolf_Latched(struct Wolf* p);
static void Wolf_LeapOff(struct Wolf* p);
static void Wolf_Bite(struct Wolf* p);
static void Wolf_Flinch(struct Wolf* p);
static void Wolf_Jaws(struct Wolf* p);

// Time stopped, holds still. mode[3]: 1 on first stopped frame, 2 after
static bool8 stopped(struct Wolf* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0 && IsFrozen(p)) s->mode[3] = 1;
  if (s->mode[3] == 0) return FALSE;
  if (s->mode[1] == WOLF_LATCHED) {
    setPriority(p, 2);
    (p->body).unk_21 = 0;
    SetDDP(&p->body, sBody);
  }
  if (s->mode[3] == 1) {
    UpdateEntityAnim(s);
    s->mode[3] = 2;
    p->elementEffect = NULL;
    SetDDP(&p->body, sBody);
  }
  if (!IsFrozen(p)) s->mode[3] = 0;
  return TRUE;
}

// 0x0808c06c. Each state has a check (0x8341e70) then its step (0x8341ea0).
static void Wolf_Update(struct Wolf* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (!IS_PART(s)) {
    if (ApRecoilHit((Object*)p) && s->mode[1] != WOLF_RECOIL) setMode(p, WOLF_RECOIL);
    if (s->mode[1] == WOLF_RECOIL) {
      Wolf_Recoil(p);
      return;
    }
  }

  if (status & BODY_STATUS_DEAD) {
    u8 was = s->mode[1];
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[3] = was;
    s->mode[1] = WOLF_BURST;
    if ((status & (BODY_STATUS_SLASHED | BODY_STATUS_B15)) == BODY_STATUS_SLASHED) {
      if (was != WOLF_FALL && was != WOLF_POUNCE && was != WOLF_LEAP_OFF) {
        s->d.y = 0;
        if (was != WOLF_RUN && was != WOLF_FLINCH) s->d.x = 0;
      }
      s->mode[1] = WOLF_CUT;
    }
    EXIT_BODY(p);
    Wolf_Die(p);
    return;
  }

  if (IS_PART(s) && s->unk_28 != NULL && s->unk_28->mode[0] > ENTITY_UPDATE) {
    disappear(s);
    return;
  }

  if (stopped(p)) return;

  // Burning or frozen, drops to ground and waits
  if (p->elementEffect != NULL) {
    s32 r;
    if (IsDead(p->elementEffect)) {
      SetDDP(&p->body, sBody);
      p->elementEffect = NULL;
      s->d.y = s->unk_coord.y;
      return;
    }
    if (PushoutToUp1(s->coord.x - PIXEL(10), s->coord.y) < 0 || PushoutToUp1(s->coord.x + PIXEL(10), s->coord.y) < 0) return;
    fall(s);
    s->coord.y += s->d.y;
    if ((r = PushoutToUp1(s->coord.x - PIXEL(10), s->coord.y)) < 0) s->coord.y += r;
    if ((r = PushoutToUp1(s->coord.x + PIXEL(10), s->coord.y)) < 0) s->coord.y += r;
    return;
  }

  switch (s->mode[1]) {
    case WOLF_IDLE:
    case WOLF_RUN:
    case WOLF_LAND:
    case WOLF_FLINCH:
    case WOLF_NONE: groundCheck(p); break;
    case WOLF_POUNCE:
    case WOLF_LEAP_OFF: airCheck(p); break;
    case WOLF_LATCHED: latchedCheck(p); break;
    default: offScreenCheck(p); break;
  }
  if (s->mode[0] != ENTITY_UPDATE) return;
  switch (s->mode[1]) {
    case WOLF_IDLE: Wolf_Idle(p); break;
    case WOLF_FALL: Wolf_Fall(p); break;
    case WOLF_RUN: Wolf_Run(p); break;
    case WOLF_POUNCE: Wolf_Pounce(p); break;
    case WOLF_LAND: Wolf_Land(p); break;
    case WOLF_LATCHED: Wolf_Latched(p); break;
    case WOLF_LEAP_OFF: Wolf_LeapOff(p); break;
    case WOLF_BITE: Wolf_Bite(p); break;
    case WOLF_FLINCH: Wolf_Flinch(p); break;
    case WOLF_JAWS: Wolf_Jaws(p); break;
  }

  if (status & BODY_STATUS_WHITE) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->elementEffect != NULL) {
      SetDDP(&p->body, &sHarmless);
      s->unk_coord.y = s->d.y;
      s->d.y = 0;
      SetMotion(s, ANIM(5));
      UpdateEntityAnim(s);
      s->angle = 0;
      setPriority(p, 2);
      setMode(p, WOLF_IDLE);
    }
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Wolf_Recoil(struct Wolf* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    setMode(p, WOLF_BURST);
    EXIT_BODY(p);
    Wolf_Die(p);
  }
}

// 0x0808c508: wolf placed with work0 1 goes when 96 px off screen
static void offScreenCheck(struct Wolf* p) {
  if ((p->s).work[0] == 1 && Camera_GetDistance(&gStageRun.vm.camera, &(p->s).coord) > PIXEL(96)) disappear(&p->s);
}

// Caught Zero, moves onto him 8 px back from jaws
static void latchOn(struct Wolf* p) {
  struct Entity* s = &p->s;
  struct Entity* zero = (struct Entity*)((p->body).bindPair->parent);
  s->coord.x = zero->coord.x + (FACING_RIGHT(p) ? -PIXEL(8) : PIXEL(8));
  s->coord.y = zero->coord.y;
  followGround(p);
  setMode(p, WOLF_LATCHED);
}

// 0x0808c398
static void groundCheck(struct Wolf* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (p->homing == 0 && abs32(s->coord.x - p->homeX) > PIXEL(256)) {
    if (s->mode[1] != WOLF_RUN) {
      setMode(p, WOLF_RUN);
      face(p, s->coord.x < p->homeX);
      p->homing = 1;
    } else if (facingAwayFromHome(p)) {
      p->homing = 1;
    }
    return;
  }
  offScreenCheck(p);
  if (s->mode[0] != ENTITY_UPDATE) return;
  if (!standing(s)) {
    setMode(p, WOLF_FALL);
  } else if (status & BODY_STATUS_WHITE) {
    setMode(p, WOLF_FLINCH);
  } else if (status & BODY_STATUS_BINDING) {
    latchOn(p);
  }
}

// 0x0808c568
static void airCheck(struct Wolf* p) {
  struct Entity* s = &p->s;
  offScreenCheck(p);
  if (s->mode[0] != ENTITY_UPDATE || !((p->body).status & BODY_STATUS_BINDING)) return;
  latchOn(p);
  InitNonAffineMotion(s);
  s->angle = 0;
  setPriority(p, 1);
  SetMotion(s, ANIM(3));
  UpdateEntityAnim(s);
}

// 0x0808c640
static void latchedCheck(struct Wolf* p) {
  offScreenCheck(p);
  if ((p->s).mode[0] == ENTITY_UPDATE && !((p->body).status & BODY_STATUS_BINDING)) setMode(p, WOLF_LEAP_OFF);
}

// 0x0808c718: runs (3 in 4) when Zero is level, otherwise pounces (3 in 4)
static void Wolf_Idle(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setPriority(p, 2);
      face(p, (pZero2->s).coord.x > s->coord.x);
      // fallthrough
    case 1:
      turnRound(p);
      // fallthrough
    case 2:
      SetDDP(&p->body, sBody);
      SetMotion(s, ANIM(1));
      setPriority(p, 2);
      s->work[2] = 80;
      s->mode[2]++;
      // fallthrough
    case 3:
      s->d.y = 0;
      if (abs32((pZero2->s).coord.x - s->coord.x) <= 0x7FFF && zeroInFront(p)) {
        bool8 likely = (RANDOM(RNG_0202f388) & 15) <= 11;
        bool8 level = abs32((pZero2->s).coord.y - s->coord.y) <= PIXEL(32);
        setMode(p, likely == level ? WOLF_RUN : WOLF_POUNCE);
        return;
      }
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 4:
      SetDDP(&p->body, sBody);
      SetMotion(s, ANIM(2));
      s->mode[2]++;
      // fallthrough
    default:
      UpdateEntityAnim(s);
      if (!IsSpriteAnimEnd(s)) return;
      if (p->homing == 2) {
        setMode(p, WOLF_RUN);
        turnRound(p);
        Wolf_Run(p);
      } else {
        s->mode[2] = 1;
      }
      return;
  }
}

// 0x0808c94c
static void Wolf_Fall(struct Wolf* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    InitNonAffineMotion(s);
    setPriority(p, 2);
    SetDDP(&p->body, sBody);
    SetMotion(s, ANIM(1));
    s->d.y = 0;
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  fall(s);
  followGround(p);
  if (standing(s)) {
    snapToFloor(s);
    p->homing = 0;
    s->mode[1] = WOLF_IDLE;
    s->mode[2] = 2;
  }
  UpdateEntityAnim(s);
}

// 0x0808c9e0: brakes once Zero is behind it
static void Wolf_Run(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0: {
      s32 x = s->coord.x;
      setPriority(p, 2);
      s->d.x = FACING_RIGHT(p) ? 0x180 : -0x180;
      s->coord.x += s->d.x;
      if (followGround(p)) {
        s->coord.x = x;
        SetMotion(s, ANIM(1));
        UpdateEntityAnim(s);
        s->mode[1] = WOLF_IDLE;
        s->mode[2] = 2;
        return;
      }
      snapToFloor(s);
      PlaySound(SE_Z2_WOLF_GROWL);
      SetDDP(&p->body, sRunning);
      createPart(p, 3, 0);
      SetMotion(s, ANIM(0));
      UpdateEntityAnim(s);
      s->mode[2]++;
    }
      // fallthrough
    case 1:
      s->d.y = 0;
      s->coord.x += s->d.x;
      if (followGround(p)) {
        decide(p);
        p->homing = 0;
        return;
      }
      snapToFloor(s);
      if (p->homing != 2 && (!zeroInFront(p) || p->homing == 1)) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 2:
      s->mode[2] = 3;
      // fallthrough
    default:
      s->d.y = 0;
      s->coord.x += s->d.x;
      s->d.x += s->d.x > 0 ? -16 : 16;
      if (followGround(p) || abs32(s->d.x) <= 47) decide(p);
      snapToFloor(s);
      UpdateEntityAnim(s);
      return;
  }
}

// 0x0808cba4
static void Wolf_Pounce(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setPriority(p, 2);
      SetDDP(&p->body, sRunning);
      createPart(p, 3, 1);
      SetDDP(&p->body, sPouncing);
      SetMotion(s, ANIM(10));
      s->mode[2]++;
      s->work[2] = 2;
      // fallthrough
    case 1:
      s->d.y = 0;
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 2:
      InitRotatableMotion(s);
      setPriority(p, 2);
      SetMotion(s, ANIM(9));
      s->d.x = FACING_RIGHT(p) ? 0xC0 : -0xC0;
      s->d.y = -0x400;
      s->coord.y -= PIXEL(1);
      p->pounceAngle = 0x2000;
      s->mode[2]++;
      // fallthrough
    default: {
      u16 was = p->pounceAngle;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 32;
      if (s->d.y > 0x700) s->d.y = 0x700;
      p->pounceAngle = was - 0xC0;
      if ((u16)(was + 0x7F3F) <= 0x5FFE) p->pounceAngle = 0xE000;
      s->angle = p->pounceAngle >> 8;
      followGround(p);
      if (standing(s) && s->d.y > 0) {
        snapToFloor(s);
        InitNonAffineMotion(s);
        s->angle = 0;
        setPriority(p, 1);
        SetMotion(s, ANIM(10));
        setMode(p, WOLF_LAND);
      }
      UpdateEntityAnim(s);
      return;
    }
  }
}

// 0x0808cd80
static void Wolf_Land(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setPriority(p, 2);
      SetDDP(&p->body, sBody);
      SetMotion(s, ANIM(10));
      s->work[2] = 2;
      p->homing = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->d.y = 0;
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 2:
      SetDDP(&p->body, sBody);
      SetMotion(s, ANIM(1));
      s->work[2] = 48;
      s->mode[2]++;
      // fallthrough
    default:
      if (--s->work[2] == 0) decide(p);
      UpdateEntityAnim(s);
      return;
  }
}

// 0x0808ce3c: hangs on to Zero for 255 frames, carries him as it falls
static void Wolf_Latched(struct Wolf* p) {
  struct Entity* s = &p->s;
  s32 oldY, r;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sLatched);
    PlaySound(SE_Z2_WOLF_GROWL);
    SetMotion(s, ANIM(3));
    s->work[2] = 255;
    s->work[3] = 40;
    s->d.y = 0;
    setPriority(p, 1);
    s->mode[2]++;
  }
  if (--s->work[2] == 0) {
    SetDDP(&p->body, sLeaping);
    setMode(p, WOLF_LEAP_OFF);
    return;
  }
  if (--s->work[3] == 0) {
    s->work[3] = 40;
    createPart(p, 2, 0);
  }
  oldY = s->coord.y;
  s->coord.y += s->d.y;
  fall(s);
  r = PushoutToUp1(s->coord.x, s->coord.y);
  if (FUN_080098a4(s->coord.x, s->coord.y) & 0x80) {
    if (r < 0 && s->coord.y + r <= oldY) {
      s->coord.y += r;
      s->d.y = 0;
    }
  } else if (r < 0) {
    if (r > -PIXEL(16)) s->coord.y += r;
    s->d.y = 0;
  }
  if ((p->body).status & BODY_STATUS_BINDING) {
    struct Entity* zero = (struct Entity*)((p->body).bindPair->parent);
    if ((r = PushoutToRight1(s->coord.x - PIXEL(28), s->coord.y - PIXEL(16))) > 0) s->coord.x += r;
    if ((r = PushoutToLeft1(s->coord.x + PIXEL(28), s->coord.y - PIXEL(16))) < 0) s->coord.x += r;
    zero->coord = s->coord;
  }
  UpdateEntityAnim(s);
}

// 0x0808cfdc: leaps back towards home
static void Wolf_LeapOff(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setPriority(p, 2);
      SetDDP(&p->body, sLeaping);
      SetMotion(s, ANIM(10));
      s->mode[2]++;
      s->work[2] = 2;
      // fallthrough
    case 1:
      s->d.y = 0;
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 2:
      if (abs32(s->coord.x - p->homeX) > PIXEL(256) && !facingAwayFromHome(p)) turnRound(p);
      InitRotatableMotion(s);
      setPriority(p, 2);
      SetMotion(s, ANIM(4));
      s->d.x = FACING_RIGHT(p) ? -0x180 : 0x180;
      s->d.y = -0x400;
      s->coord.y -= PIXEL(6);
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    default:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      fall(s);
      s->work[2] += 10;
      s->angle = s->work[2];
      followGround(p);
      if (standing(s) && s->d.y > 0) {
        snapToFloor(s);
        p->homing = 0;
        InitNonAffineMotion(s);
        setPriority(p, 1);
        s->angle = 0;
        SetMotion(s, ANIM(10));
        setMode(p, WOLF_LAND);
      }
      UpdateEntityAnim(s);
      return;
  }
}

// 0x0808d1a4: one hit over two frames
static void Wolf_Bite(struct Wolf* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 2;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) disappear(s);
}

// 0x0808d224
static void Wolf_Flinch(struct Wolf* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    setPriority(p, 2);
    p->homing = 0;
    SetDDP(&p->body, sBody);
    SetMotion(s, ANIM(5));
    s->d.x = p->hitFromX > 0 ? -PIXEL(1) : PIXEL(1);
    s->work[2] = 8;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) decide(p);
  s->coord.x += s->d.x;
  s->d.x = s->d.x * 230 / 256;
  followGround(p);
  UpdateEntityAnim(s);
}

// 0x0808d2c4: rides on wolf while it runs (work1 0) or pounces (work1 1)
static void Wolf_Jaws(struct Wolf* p) {
  struct Entity* s = &p->s;
  struct Entity* wolf = s->unk_28;
  s->coord = wolf->coord;
  if ((wolf->mode[1] != WOLF_RUN && s->work[1] == 0) || (wolf->mode[1] != WOLF_POUNCE && s->work[1] == 1)) disappear(s);
}

// --------------------------------------------
// Deaths

static void countKill(struct Wolf* p) {
  struct Entity* s = &p->s;
  TryDropItem(1, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  ApImportWolfKilled();
}

// 0x0808d370: three pieces
static void burst(struct Wolf* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s->flags &= ~DISPLAY;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  createPieces(p, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  countKill(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0808d414: back half slides on, front flies off
static void cut(struct Wolf* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0: {
      bool8 right = FACING_RIGHT(p);
      InitNonAffineMotion(s);
      face(p, right);
      setPriority(p, 2);
      SetMotion(s, ANIM(6));
      s->d.x += 128 - (p->hitFromX > 0 ? 256 : 0);
      createHalf(p);
      s->work[2] = 20;
      s->mode[2]++;
    }
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      followGroundFalling(s);
      s->d.x = s->d.x * 245 / 256;
      fall(s);
      if (--s->work[2] == 0) {
        Coords32 c;
        c.x = s->coord.x;
        c.y = s->coord.y - PIXEL(16);
        CreateSmoke(1, &c);
        PlaySound(SE_ZAKO_EXPLODE);
        countKill(p);
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      return;
    default:
      s->flags &= ~DISPLAY;
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      return;
  }
}

static void Wolf_Die(struct Wolf* p) {
  if ((p->s).mode[1] == WOLF_CUT) {
    cut(p);
  } else {
    burst(p);
  }
}

// --------------------------------------------
// Pieces, Zero 2's VFX 55: cut-off half (work0 0) and three small pieces (work0 1). work[3] is
// the facing, d the speed, work[1] whether it was in the air.

static void Piece_Init(struct VFX* p);
static void Piece_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2WolfPieceRoutine = {
    [ENTITY_INIT] =      Piece_Init,
    [ENTITY_UPDATE] =    Piece_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

static void createPiecesAt(Coords32* c, bool8 right) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_WOLF_PIECE);
      (p->s).work[0] = 1;
      (p->s).work[1] = i;
      (p->s).work[3] = right;
      (p->s).coord = *c;
    }
  }
}

// 0x080bb5e0
static void createPieces(struct Wolf* wolf, Coords32* c) { createPiecesAt(c, FACING_RIGHT(wolf)); }

// 0x080bb598
static void createHalf(struct Wolf* wolf) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  u8 was = (wolf->s).mode[3];
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_WOLF_PIECE);
    (p->s).work[0] = 0;
    (p->s).work[1] = was == WOLF_FALL || was == WOLF_POUNCE || was == WOLF_LEAP_OFF;
    (p->s).work[3] = FACING_RIGHT(wolf);
    (p->s).coord = (wolf->s).coord;
    (p->s).d.x = (wolf->s).d.x * 100 / 256;
    (p->s).d.y = (wolf->s).d.y;
  }
}

// 0x080bb6d4 and 0x080bb838
static void Piece_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3];
  s->flags |= DISPLAY;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, right);
  if (s->work[0] == 0) {
    SetMotion(s, ANIM(7));
    s->work[2] = 22;
  } else {
    u8 n = s->work[1];
    SetMotion(s, ANIM(11 + n));
    if (right) n = 2 - n;
    s->d.x = ((n - 1) << 8) + (RANDOM(RNG_0202f388) & 0x1FF) - PIXEL(1);
    s->d.y = -PIXEL(2) - (RANDOM(RNG_0202f388) & 0x1FF);
    s->work[2] = 0;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Piece_Update(p);
}

static void Piece_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080bb78c (half) and 0x080bb91c (piece)
static void Piece_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    bool8 airborne = s->work[1];
    s->coord.x += s->d.x;
    s->d.x = s->d.x * 250 / 256;
    s->coord.y += s->d.y;
    if (airborne) {
      s->d.y += 32;
      if (s->d.y > 0x700) s->d.y = 0x700;
    }
    UpdateEntityAnim(s);
    s->work[2]--;
    if (airborne) {
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) s->work[2] = 0;
    } else {
      s32 f = FUN_08009f6c(s->coord.x, s->coord.y);
      if (s->coord.y > f) s->coord.y = f;
    }
    if (s->work[2] == 0) {
      createPiecesAt(&s->coord, s->work[3]);
      CreateSmoke(1, &s->coord);
      Piece_Die(p);
    }
    return;
  }
  if (++s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  UpdateEntityAnim(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    CreateSmoke(3, &s->coord);
    Piece_Die(p);
  }
}

// -------------------------------------------
// clang-format off
// unk_0a 0x81 on running, pouncing and latched hitboxes lets them bind Zero
static const struct Collision sBody[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0x800, 0x1800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
};

static const struct Collision sRunning[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x04, HARDNESS_B3, 129, 1, 0x00000001, {-0x800, -0x1000, 0xa00, 0xa00}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x04, HARDNESS_B3, 129, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
};

static const struct Collision sLatched[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 129, 1, 0x00000001, {-0x800, -0x1000, 0x800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 129, 0, 0x00000000, {0x0, -0xe00, 0x1400, 0x1c00}},
};

static const struct Collision sPouncing[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, HARDNESS_B3, 129, 1, 0x00000001, {-0x800, -0x1000, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, HARDNESS_B3, 129, 0, 0x00000000, {0x0, -0xa00, 0x1400, 0x1400}},
};

static const struct Collision sLeaping[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sBite[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, HARDNESS_B3, 0, 0, 0x00000001, {0x0, -0xa00, 0x1000, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sJaws[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, HARDNESS_B3, 0, 0, 0x00000001, {0x0, -0x800, 0x1800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xc00, 0x1800, 0x1800}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}};
// clang-format on

#endif  // AP
