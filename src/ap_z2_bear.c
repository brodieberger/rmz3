#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Zero 2's bear, boss 4.
*/

struct Bear {
  OBJECT_HDR;
  s32 homeX;              // 0xB4
  s32 homeY;              // 0xB8
  u8 _bc[2];
  u8 last;                // 0xBE, attack chosen last
  u8 sinceCharge;         // 0xBF
  struct Entity* part;    // 0xC0, enemy 21 over it
  struct Entity* pillar;  // 0xC4
  struct Entity* explosion;  // 0xC8
  s16 sound;              // 0xCC
  u8 _ce[14];
  s32 left;               // 0xDC
  s32 right;              // 0xE0
};
static_assert(sizeof(struct Bear) == sizeof(struct Boss));

struct Pillar {
  OBJECT_HDR;
  u8 _b4[9];
  u8 pieces;       // 0xBD
  u16 scale;       // 0xBE
  bool8 breakTop;  // 0xC0, set by bear
  bool8 smash;     // 0xC1, set by bear
  u8 _c2[2];
};
static_assert(sizeof(struct Pillar) == sizeof(struct Enemy));

enum {
  BEAR_WAIT = 0,
  BEAR_INTRO = 1,
  BEAR_DECIDE = 3,
  BEAR_PAUSE = 4,
  BEAR_SWIPE_WIND = 5,
  BEAR_SWIPE = 6,
  BEAR_BALL_WIND = 8,
  BEAR_BALL_BREATH = 9,
  BEAR_BALL_THROW = 10,
  BEAR_BALL_END = 11,
  BEAR_BLOCK_WIND = 12,
  BEAR_BLOCK_BREATH = 13,
  BEAR_BLOCK_END = 14,
  BEAR_CHARGE_WIND = 16,
  BEAR_CHARGE = 17,
  BEAR_PILLAR_WIND = 19,
  BEAR_PILLAR = 20,
  BEAR_PILLAR_END = 21,
  BEAR_PILLAR_BREAK = 22,
  BEAR_PILLAR_SMASH = 23,
  BEAR_TURN = 24,
  BEAR_TURNED = 25,
  BEAR_DASH_WIND = 26,
  BEAR_STUNNED = 29,
};

#define BEAR(n) MOTION(DM207_Z2_BEAR, (n))
#define ICE(n) MOTION(AP_SHEET_Z2_BEAR_ICE, (n))

#define BOSS(p) ((struct Bear*)(p)->s.unk_28)

static const struct Collision sCollisions[5];
static const struct Collision* const sBig = &sCollisions[0];
static const struct Collision* const sNormal = &sCollisions[1];
static const struct Coord sElementCoord = {0, -PIXEL(43)};
static const s32 sPillarBreathY[5] = {-PIXEL(42), -PIXEL(65), -PIXEL(75), -PIXEL(88), -PIXEL(100)};

static const struct PreloadEntity sIceSheet = {AP_SHEET_Z2_BEAR_ICE, 0, 682, 5, 0, AP_PRELOAD_SHEET, 0};

static void Bear_Init(struct Bear* p);
static void Bear_Update(struct Bear* p);
static void Bear_Die(struct Bear* p);
static struct Entity* createPart(struct Bear* boss, u8 kind);
static struct Entity* createPillar(struct Bear* boss, bool8 right);
static void createBall(struct Bear* boss, bool8 high);
static void createBlock(struct Bear* boss, bool8 right);
static void createIce(Coords32* at, u8 kind, u8 work1);

// clang-format off
const BossRoutine gApZ2BearRoutine = {
    [ENTITY_INIT] =      (BossFunc)Bear_Init,
    [ENTITY_UPDATE] =    (BossFunc)Bear_Update,
    [ENTITY_DIE] =       (BossFunc)Bear_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void useSheet(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static bool8 animDone(struct Entity* s) { return (s->motion).state == ANIM_END; }

static void stopSound(struct Bear* p) {
  if (p->sound != -1) StopSound(p->sound);
  p->sound = -1;
}

// Tells its part to go
static void dropPart(struct Bear* p) {
  if (p->part != NULL) (p->part)->work[3] = 1;
  p->part = NULL;
}

static bool8 bossDown(struct Bear* p) {
  return ((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0 && !(gStageRun.missionStatus & MISSION_PLAYER_DEAD));
}

// 0x08045064
static void Bear_Init(struct Bear* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sIceSheet);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, BEAR(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sNormal, 64);
  (s->spr).oam.priority = 3;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  p->left = FUN_0800a31c(s->coord.x, FUN_0800a134(s->coord.x, s->coord.y) + PIXEL(16));
  p->right = FUN_0800a22c(s->coord.x, FUN_0800a134(s->coord.x, s->coord.y) + PIXEL(16));
  p->part = p->pillar = NULL;
  p->sound = -1;
  s->unk_2c = NULL;
  p->last = 0;
  p->sinceCharge = 0;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, BEAR_WAIT);
  Bear_Update(p);
}

static void Bear_Dispatch(struct Bear* p);

// 0x080451a4
static void Bear_Update(struct Bear* p) {
  struct Entity* s = &p->s;
  if (bossDown(p)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Bear_Die(p);
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) {
    if (s->unk_2c == NULL) s->unk_2c = ApplyElementEffect(10, (Object*)p, &sElementCoord);
    if ((p->body).elemented == 2) setMode(s, BEAR_STUNNED);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  Bear_Dispatch(p);
}

// 0x08045224: cut, slides back, then waits for script and explodes
static void Bear_Die(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    dropPart(p);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      SetMotion(s, BEAR(12));
      s->d.x = facingRight(s) ? 64 : -64;
      s->unk_coord.x = facingRight(s) ? -1 : 1;
      p->part = createPart(p, 4);
      PlaySound(SE_LIGHT);
      s->mode[1] = 0;
    } else {
      SetMotion(s, BEAR(11));
      s->mode[1] = 1;
      s->work[2] = 64;
    }
    stopSound(p);
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[1] = 1;
      break;
    case 1:
      if (s->scriptEntity->flags & 0x80) s->mode[1] = 2;
      break;
    case 2:
      if (s->mode[3] == 0) {
        Coords32 at = {0, -PIXEL(56)};
        p->explosion = CreateBossExplosion(s, &at);
        s->mode[3]++;
      }
      if ((p->explosion)->mode[0] > ENTITY_UPDATE) gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// 0x080453dc: waits for script's go
static void Bear_Wait(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(0));
    s->mode[2]++;
  } else if (s->scriptEntity->flags & 1) {
    setMode(s, BEAR_INTRO);
  }
  UpdateEntityAnim(s);
}

// 0x0804541c: roars, frost flying off both sides
static void Bear_Intro(struct Bear* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 reach;
  switch (s->mode[2]) {
    case 0:
      SetMotion(s, BEAR(14));
      s->mode[2]++;
      break;
    case 1:
      if (!animDone(s)) break;
      SetMotion(s, BEAR(18));
      p->sound = PlaySound(SE_Z2_FROST_BREATH);
      s->work[2] = 64;
      s->mode[2]++;
      break;
    case 2:
      reach = s->motion.cmdIdx == 0 ? PIXEL(44) : PIXEL(42);
      at.x = (s->work[2] & 1) ? s->coord.x + reach : s->coord.x - reach;
      at.y = s->coord.y - PIXEL(40);
      createIce(&at, (s->work[2] >> 1) & 1, s->work[2] & 1);
      if (--s->work[2] == 0xFF) {
        stopSound(p);
        s->work[2] = 40;
        s->mode[2]++;
      }
      break;
    case 3:
      if (--s->work[2] == 0xFF) {
        SetMotion(s, BEAR(15));
        s->mode[2]++;
      }
      return;
    case 4:
      if (!animDone(s)) break;
      SetMotion(s, BEAR(0));
      s->mode[2]++;
      break;
    case 5:
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, BEAR_DECIDE);
      break;
  }
  UpdateEntityAnim(s);
}

static s32 zeroDistance(struct Entity* s) {
  s32 d = s->coord.x - (pZero2->s).coord.x;
  return d < 0 ? -d : d;
}

// 0x08045560: turns to face Zero, else never the same attack twice; charges if far and 3 since
static void Bear_Decide(struct Bear* p) {
  struct Entity* s = &p->s;
  u8 next, r;
  s32 d;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(0));
    SetDDP(&p->body, sNormal);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (gStageRun.vm.active & VM_ACTIVE) return;
  if (p->last != BEAR_CHARGE_WIND && zeroDistance(s) > PIXEL(48) && p->sinceCharge > 2) {
    setMode(s, BEAR_CHARGE_WIND);
    p->last = BEAR_CHARGE_WIND;
    p->sinceCharge = 0;
    return;
  }
  if ((s->coord.x < (pZero2->s).coord.x) != facingRight(s)) {
    next = BEAR_TURN;
  } else {
    do {
      d = zeroDistance(s);
      r = RANDOM(RNG_0202f388) & 15;
      if (d < PIXEL(48)) {
        next = r <= 7 ? BEAR_SWIPE_WIND : BEAR_BALL_WIND;
      } else if (d < PIXEL(96)) {
        next = r <= 5 ? BEAR_DASH_WIND : r <= 9 ? BEAR_BALL_WIND : r <= 13 ? BEAR_BLOCK_WIND : BEAR_CHARGE_WIND;
      } else if ((gScore.total)->rank > 4) {
        next = r <= 6 ? BEAR_PILLAR_WIND : r <= 13 ? BEAR_BLOCK_WIND : BEAR_CHARGE_WIND;
      } else {
        next = r <= 6 ? BEAR_BALL_WIND : r <= 13 ? BEAR_BLOCK_WIND : BEAR_CHARGE_WIND;
      }
    } while (p->last == next);
  }
  if (next == BEAR_CHARGE_WIND) {
    p->sinceCharge = 0;
  } else {
    p->sinceCharge++;
  }
  p->last = next;
  setMode(s, next);
}

// 0x080456dc
static void Bear_Pause(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(0));
    SetDDP(&p->body, sNormal);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(s, BEAR_DECIDE);
}

// 0x08045728
static void Bear_SwipeWind(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(16));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(s, BEAR_SWIPE);
}

static void pause(struct Entity* s, u8 frames) {
  setMode(s, BEAR_PAUSE);
  s->work[2] = frames;
}

// 0x0804576c
static void Bear_Swipe(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(17));
    PlaySound(SE_Z2_BEAR_ROAR);
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if ((u8)(s->motion.cmdIdx - 1) <= 2) SetDDP(&p->body, sBig);
  if (animDone(s)) pause(s, 60);
}

// Wind-up for a breath, frost blown from mouth after
static void Bear_BreathWind(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(5));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animDone(s)) return;
  if (s->mode[1] == BEAR_BALL_WIND) {
    p->part = createPart(p, 0);
    setMode(s, BEAR_BALL_BREATH);
  } else {
    setMode(s, BEAR_BLOCK_BREATH);
  }
}

// 0x08045820..: frost from mouth, every other frame
static void breath(struct Bear* p, s32 dx, s32 y) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (facingRight(s)) {
    at.x = s->coord.x + dx;
    s->work[3] += 9;
  } else {
    at.x = s->coord.x - dx;
    s->work[3] -= 9;
  }
  at.y = s->coord.y + y;
  if ((s->work[2] & 3) == 2) createIce(&at, 2, s->work[3]);
  createIce(&at, 2, (u8)RANDOM(RNG_0202f388));
}

// 0x08045820, 0x08045a74: a ball, or a block, grows in its mouth
static void Bear_Breath(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    if (s->mode[1] == BEAR_BALL_BREATH) {
      createBall(p, (pZero2->s).coord.y < s->coord.y - PIXEL(72));
    } else {
      p->part = createPart(p, 0);
      createBlock(p, facingRight(s));
    }
    s->work[2] = 64;
    s->work[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] > 24 && (s->work[2] & 1)) breath(p, PIXEL(41), -PIXEL(42));
  if (--s->work[2] == 0xFF) {
    stopSound(p);
    setMode(s, s->mode[1] == BEAR_BALL_BREATH ? BEAR_BALL_THROW : BEAR_BLOCK_END);
  }
}

// 0x08045960
static void Bear_BallThrow(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(6));
    if (p->part != NULL) {
      (p->part)->work[3] = 1;
      p->part = createPart(p, 1);
    }
    PlaySound(SE_Z2_BEAR_ROAR);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->motion.cmdIdx == 1 || s->motion.cmdIdx == 4) {
    dropPart(p);
  } else if (s->motion.cmdIdx == 3 && p->part == NULL) {
    p->part = createPart(p, 2);
  }
  if (animDone(s)) setMode(s, BEAR_BALL_END);
}

// 0x080459f8
static void Bear_BallEnd(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(4));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) pause(s, 52);
}

// 0x08045ba0
static void Bear_BlockEnd(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(7));
    dropPart(p);
    PlaySound(SE_Z2_BEAR_ROAR);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) pause(s, 60);
}

// 0x08045bf8, 0x080461c8
static void Bear_ChargeWind(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(15));
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(s, BEAR_CHARGE);
}

// 0x08045c3c: stomps across, shaking the room each step, until near a wall
static void Bear_Charge(struct Bear* p) {
  struct Entity* s = &p->s;
  s8 step;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(8));
    s->d.x = facingRight(s) ? 0x180 : -0x180;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  step = s->motion.cmdIdx;
  SetDDP(&p->body, (step == 3 || step == 7) ? sNormal : sBig);
  if (step == 1 || step == 5) {
    if (s->mode[3] == 0) {
      PlaySound(SE_Z2_BEAR_STOMP);
      s->mode[3]++;
    }
    AppendQuake(1, &s->coord);
  } else {
    s->coord.x += s->d.x;
    s->mode[3] = 0;
  }
  if (facingRight(s) ? s->coord.x > p->right - PIXEL(48) : s->coord.x < p->left + PIXEL(48)) {
    SetDDP(&p->body, sNormal);
    setMode(s, BEAR_TURN);
  }
}

// 0x08045d50: breathes frost low, then raises an ice pillar
static void Bear_PillarWind(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(2));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] != 0) {
    if (s->work[2] & 1) breath(p, PIXEL(37), -PIXEL(23));
    if (--s->work[2] == 0xFF) setMode(s, BEAR_PILLAR);
  } else if (animDone(s)) {
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    p->part = createPart(p, 1);
    s->work[2] = 24;
    s->mode[3] = 1;
  }
}

// 0x08045e90
static void Bear_Pillar(struct Bear* p) {
  struct Entity* s = &p->s;
  u8 frame;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(3));
    p->pillar = createPillar(p, facingRight(s));
    if (p->part != NULL) {
      (p->part)->work[3] = 1;
      p->part = createPart(p, 3);
    }
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 2) {
    if (--s->work[2] == 0xFF) setMode(s, BEAR_PILLAR_END);
    return;
  }
  if (s->mode[3] == 0) {
    frame = s->motion.cmdIdx;
    if (animDone(s)) {
      s->work[2] = 10;
      s->mode[3] = 1;
    }
  } else {
    frame = 4;
    if (--s->work[2] == 0xFF) {
      stopSound(p);
      s->work[2] = 36;
      s->mode[3] = 2;
    }
  }
  if (s->work[2] & 1) breath(p, PIXEL(37), sPillarBreathY[frame]);
}

// 0x08046008
static void Bear_PillarEnd(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(4));
    dropPart(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) setMode(s, BEAR_PILLAR_BREAK);
}

// 0x08046054
static void Bear_PillarBreak(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(1));
    s->work[2] = 64;
    PlaySound(SE_Z2_BEAR_ROAR);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] == 48 && p->pillar != NULL) ((struct Pillar*)p->pillar)->breakTop = TRUE;
  if (--s->work[2] == 0xFF) setMode(s, BEAR_PILLAR_SMASH);
}

// 0x080460b0
static void Bear_PillarSmash(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(17));
    s->work[2] = 0;
    PlaySound(SE_Z2_BEAR_ROAR);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2]++ > 4 && p->pillar != NULL) ((struct Pillar*)p->pillar)->smash = TRUE;
  if (animDone(s)) pause(s, 60);
}

// 0x08046110, 0x0804614c
static void Bear_Turn(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->mode[1] == BEAR_TURN) {
      SetMotion(s, BEAR(14));
    } else {
      SetMotion(s, BEAR(15));
      SET_XFLIP(p, !facingRight(s));
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) setMode(s, s->mode[1] == BEAR_TURN ? BEAR_TURNED : BEAR_DECIDE);
}

// 0x080462c4: shocked, a minute's breather and its charge count reset
static void Bear_Stunned(struct Bear* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BEAR(11));
    SetDDP(&p->body, sNormal);
    s->work[2] = 60;
    stopSound(p);
    p->last = BEAR_STUNNED;
    p->sinceCharge = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) pause(s, 1);
}

static void Bear_Dispatch(struct Bear* p) {
  switch ((p->s).mode[1]) {
    case BEAR_WAIT: Bear_Wait(p); break;
    case BEAR_INTRO: Bear_Intro(p); break;
    case BEAR_DECIDE: Bear_Decide(p); break;
    case BEAR_PAUSE: Bear_Pause(p); break;
    case BEAR_SWIPE_WIND: Bear_SwipeWind(p); break;
    case BEAR_SWIPE: Bear_Swipe(p); break;
    case BEAR_BALL_WIND:
    case BEAR_BLOCK_WIND: Bear_BreathWind(p); break;
    case BEAR_BALL_BREATH:
    case BEAR_BLOCK_BREATH: Bear_Breath(p); break;
    case BEAR_BALL_THROW: Bear_BallThrow(p); break;
    case BEAR_BALL_END: Bear_BallEnd(p); break;
    case BEAR_BLOCK_END: Bear_BlockEnd(p); break;
    case BEAR_CHARGE_WIND:
    case BEAR_DASH_WIND: Bear_ChargeWind(p); break;
    case BEAR_CHARGE: Bear_Charge(p); break;
    case BEAR_PILLAR_WIND: Bear_PillarWind(p); break;
    case BEAR_PILLAR: Bear_Pillar(p); break;
    case BEAR_PILLAR_END: Bear_PillarEnd(p); break;
    case BEAR_PILLAR_BREAK: Bear_PillarBreak(p); break;
    case BEAR_PILLAR_SMASH: Bear_PillarSmash(p); break;
    case BEAR_TURN:
    case BEAR_TURNED: Bear_Turn(p); break;
    case BEAR_STUNNED: Bear_Stunned(p); break;
  }
}

// --------------------------------------------
/*
  Zero 2's enemy 21, a piece of the bear drawn over it.
  work0: its motion, 4 the top it's cut to
  work3: set by bear to go
*/

static void Part_Init(struct Enemy* p);
static void Part_Update(struct Enemy* p);
static void Part_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2BearPartRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Part_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Part_Update,
    [ENTITY_DIE] =       (EnemyFunc)Part_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const motion_t sPartMotions[5] = {BEAR(20), BEAR(9), BEAR(19), BEAR(10), BEAR(13)};

// 0x08072398
static struct Entity* createPart(struct Bear* boss, u8 kind) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p == NULL) return NULL;
  INIT_ENEMY_ROUTINE(p, ENEMY_Z2_BEAR_PART);
  p->unk_28 = &boss->s;
  p->work[0] = kind;
  return p;
}

// 0x080723f0
static void Part_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  // Own textures in doors' window, 1 and 4 draw from bear's
  if (s->work[0] != 1 && s->work[0] != 4) s->tileNum = (u16)(380 - 512);
  SetMotion(s, sPartMotions[s->work[0]]);
  s->work[3] = 0;
  if (s->work[0] == 4) {
    SET_XFLIP(p, facingRight(boss));
    s->coord = boss->coord;
    s->d.x = facingRight(boss) ? -64 : 64;
    s->unk_coord.x = facingRight(boss) ? 1 : -1;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

// 0x080724bc
static void Part_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Bear* boss = BOSS(p);
  UpdateEntityAnim(s);
  if (s->work[0] == 4) {
    if (s->mode[1] == 0) {
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[1] = 1;
      return;
    }
    if ((boss->s).mode[0] != ENTITY_EXIT) return;
  } else if (s->work[3] == 0 && (boss->s).mode[1] != BEAR_STUNNED && !bossDown(boss)) {
    SET_XFLIP(p, facingRight(&boss->s));
    s->coord = (boss->s).coord;
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Part_Die(p);
}

// 0x08072590
static void Part_Die(struct Enemy* p) {
  if (BOSS(p)->part == &p->s) BOSS(p)->part = NULL;
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's enemy 20, ice pillar raised in front of the bear in four steps.

static const struct Collision sPillarCollisions[4][2];
static const struct Rect sPillarSizes[4];
static const struct SlashedEnemy sChips[4];

static void Pillar_Init(struct Pillar* p);
static void Pillar_Update(struct Pillar* p);
static void Pillar_Die(struct Pillar* p);
static void pillarHit(struct Body* body, Coords32* r1, Coords32* r2);

// clang-format off
const EnemyRoutine gApZ2IcePillarRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Pillar_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Pillar_Update,
    [ENTITY_DIE] =       (EnemyFunc)Pillar_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08071bdc
static struct Entity* createPillar(struct Bear* boss, bool8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p == NULL) return NULL;
  INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_PILLAR);
  p->unk_28 = &boss->s;
  p->work[1] = right;
  return p;
}

static void setScale(struct Entity* s, u16 scale) {
  (s->spr).mag.x = (s->spr).mag.y = scale;
}

// 0x08071c34
static void Pillar_Init(struct Pillar* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitRotatableMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ICE(3));
  UpdateEntityAnim(s);
  SET_XFLIP(p, facingRight(boss));
  INIT_BODY(p, &sPillarCollisions[0][0], 64, pillarHit);
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sPillarSizes[0];
  s->physicsAttr = 0x801;
  (s->spr).oam.priority = 3;
  p->breakTop = p->smash = FALSE;
  p->pieces = 0;
  p->scale = 0;
  s->coord.x = boss->coord.x + (s->work[1] ? PIXEL(42) : -PIXEL(42));
  s->coord.y = FUN_08009f6c(s->coord.x, boss->coord.y);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Pillar_Update(p);
}

static void dust(struct Entity* s, s32 up) {
  Coords32 at;
  at.x = s->coord.x;
  at.y = FUN_08009f6c(s->coord.x, s->coord.y) - up;
  createIce(&at, 3, 0);
}

// 0x08071f0c..0x08072034: a step taller
static void grow(struct Pillar* p, u8 step) {
  struct Entity* s = &p->s;
  SetMotion(s, ICE(3 + step));
  SetDDP(&p->body, &sPillarCollisions[step][0]);
  s->size = &sPillarSizes[step];
  s->physicsAttr = 0x801;
  dust(s, PIXEL(16) + PIXEL(32) * step);
  p->pieces = 4 + 4 * step;
}

// Chips flying up the pillar, 8 px apart
static void chips(struct Pillar* p, s32 up, u8 angleRight, u8 angleLeft) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i, flip;
  RANDOM(RNG_0202f388);
  at.x = s->coord.x;
  at.y = s->coord.y - up;
  for (i = 0; i < 8; i++) {
    flip = (!(RANDOM(RNG_0202f388) & 1)) << 4;
    if (facingRight(s)) flip |= 1;
    useSheet(CreateSlashedEnemy(&at, &sChips[i & 3], 0, flip));
    createIce(&at, 2, facingRight(s) ? angleRight - 5 * i : angleLeft + 5 * i);
    at.y -= PIXEL(8);
  }
  PlaySound(SE_Z2_ICE_BREAK);
}

// 0x08071d48
static void Pillar_Update(struct Pillar* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (((p->body).status & BODY_STATUS_DEAD) || boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == BEAR_STUNNED) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Pillar_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:  // 0x08071e94
      if (s->mode[2] == 0) {
        SetMotion(s, ICE(3));
        dust(s, PIXEL(16));
        p->pieces = 4;
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      p->scale += 16;
      setScale(s, p->scale);
      if (p->scale > 255) setMode(s, 1);
      return;
    case 1:
    case 2:
    case 3:  // 0x08071f0c, 0x08071fa0, 0x08072034
      if (s->mode[2] == 0) {
        grow(p, s->mode[1]);
        s->work[2] = s->mode[1] == 1 ? 13 : s->mode[1] == 2 ? 11 : 8;
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      if (--s->work[2] == 0xFF) setMode(s, s->mode[1] + 1);
      return;
    case 4:  // 0x080720c8: top breaks off
      if (p->breakTop) {
        chips(p, PIXEL(64), 35, 93);
        SetMotion(s, ICE(4));
        SetDDP(&p->body, &sPillarCollisions[1][0]);
        s->size = &sPillarSizes[1];
        s->physicsAttr = 0x801;
        p->pieces = 8;
        s->mode[1]++;
      }
      UpdateEntityAnim(s);
      return;
    case 5:  // 0x08072210: smashed
      if (!p->smash) return;
      chips(p, 0, (u8)-16, (u8)-112);
      p->pieces = 0;
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      Pillar_Die(p);
      return;
  }
}

// 0x08071da0
static void Pillar_Die(struct Pillar* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i, flip;
  if (BOSS(p)->pillar == s) BOSS(p)->pillar = NULL;
  RANDOM(RNG_0202f388);
  at = s->coord;
  for (i = 0; i < p->pieces; i++) {
    flip = (RANDOM(RNG_0202f388) & 1) << 4;
    if (facingRight(s)) flip |= 1;
    useSheet(CreateSlashedEnemy(&at, &sChips[i & 3], 0, flip));
    at.y -= PIXEL(8);
  }
  s->flags2 &= ~ENTI_PHYSICS;
  EXIT_BODY(p);
  s->flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0807232c: a chip where it's hit
static void pillarHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  u8 r;
  if (!(body->hitboxFlags & BODY_STATUS_WHITE) || !((body->parent)->flags & DISPLAY)) return;
  r = RANDOM(RNG_0202f388) & 3;
  useSheet(CreateSlashedEnemy(&(body->enemy->parent)->coord, &sChips[r], 0, (r & 1) | ((r & 1) << 4)));
}

// --------------------------------------------
/*
  Zero 2's projectile 18 work0 0, ice ball grown in the bear's mouth and lobbed at Zero.
  work1: thrown high
*/

struct Ball {
  OBJECT_HDR;
  u8 _b4[12];
  u16 scale;  // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Ball) == sizeof(struct Projectile));

static const struct Collision sBallCollision;

static void Ball_Init(struct Ball* p);
static void Ball_Update(struct Ball* p);
static void Ball_Die(struct Ball* p);

// clang-format off
const ProjectileRoutine gApZ2IceBallRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Ball_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Ball_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809cdb4
static void createBall(struct Bear* boss, bool8 high) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p == NULL) return;
  INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ICE_BALL);
  p->unk_28 = &boss->s;
  p->work[1] = high;
}

// 0x0809cea0
static void Ball_Init(struct Ball* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitRotatableMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ICE(7));
  UpdateEntityAnim(s);
  SET_XFLIP(p, facingRight(boss));
  INIT_BODY(p, &sBallCollision, 1, NULL);
  (s->spr).oam.priority = 3;
  s->work[2] = 0;
  s->work[3] = (u8)-7;
  p->scale = 0;
  s->coord.x = boss->coord.x + (facingRight(boss) ? PIXEL(41) : -PIXEL(41));
  s->coord.y = boss->coord.y - PIXEL(42);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Ball_Update(p);
}

// 0x0809d18c
static void Ball_Update(struct Ball* p) {
  struct Entity* s = &p->s;
  struct Bear* boss = BOSS(p);
  s32 frames, zx;
  u8 i;
  Coords32 at;
  if (bossDown(boss) || (boss->s).mode[1] == BEAR_STUNNED) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Ball_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[2]) {
    case 0:  // grows until thrown
      if (p->scale <= 255) {
        p->scale += 16;
        setScale(s, p->scale);
      }
      if ((boss->s).mode[1] == BEAR_BALL_THROW) s->mode[2]++;
      break;
    case 1:
      s->coord.x = (boss->s).coord.x + (facingRight(s) ? PIXEL(40) : -PIXEL(40));
      s->coord.y = (boss->s).coord.y - PIXEL(24);
      s->work[2] = 15;
      s->mode[2]++;
      break;
    case 2:
      if (--s->work[2] != 0xFF) break;
      frames = s->work[1] ? 30 : 24;
      (s->spr).oam.priority = 2;
      zx = (pZero2->s).coord.x;
      if (facingRight(s) ? zx > s->coord.x : zx < s->coord.x) {
        s->d.x = (zx - s->coord.x) / (frames * 2);
      } else {
        s->d.x = facingRight(s) ? 0x100 : -0x100;
      }
      s->d.y = -(frames * 3 * 32);
      s->mode[2]++;
      break;
    case 3:  // spins, falls, shatters on landing
      s->work[2] += s->work[3];
      s->angle = s->work[2];
      s->d.y += 96;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(14)) == 0) break;
      at = s->coord;
      for (i = 0; i < 4; i++) createIce(&at, 1, i);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Ball_Die(p);
      break;
  }
}

// 0x0809d41c
static void Ball_Die(struct Ball* p) {
  PlaySound(SE_Z2_ICE_BREAK);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's solid 3, ice block grown in the bear's mouth and slid across the floor.
  work1: slid right
  Its top is enemy 19, which can be broken.
*/

struct Block {
  OBJECT_HDR;
  u8 _b4[9];
  bool8 whole;   // 0xBD, not yet cracked
  u8 landed;     // 0xBE, 1 when it stops, 2 once its top knows
  u8 _bf;
  u16 scale;     // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Block) == sizeof(struct Solid));

static const struct Collision sBlockCollisions[2][2];
static const struct Collision sShatterCollision;
static const struct Rect sBlockSize = {0, -0x1800, 0x2000, 0x3000};

static void Block_Init(struct Block* p);
static void Block_Update(struct Block* p);
static void Block_Die(struct Block* p);
static void blockHit(struct Body* body, Coords32* r1, Coords32* r2);
static void createCap(struct Block* block);

// clang-format off
const SolidRoutine gApZ2BearBlockRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Block_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Block_Update,
    [ENTITY_DIE] =       (SolidFunc)Block_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c1ad0
static void createBlock(struct Bear* boss, bool8 right) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p == NULL) return;
  INIT_SOLID_ROUTINE(p, SOLID_Z2_BEAR_BLOCK);
  p->unk_28 = &boss->s;
  p->work[1] = right;
}

// 0x080c1b28
static void Block_Init(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitRotatableMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ICE(1));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sBlockCollisions[0][0], 32, blockHit);
  (s->spr).oam.priority = 3;
  p->scale = 0;
  s->coord.x = boss->coord.x + (s->work[1] ? PIXEL(34) : -PIXEL(34));
  s->coord.y = boss->coord.y - PIXEL(32);
  p->whole = TRUE;
  p->landed = 0;
  createCap(p);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Block_Update(p);
}

static void blockAt(struct Entity* s, struct Entity* boss, s32 right, s32 left, s32 y) {
  s->coord.x = boss->coord.x + (s->work[1] ? right : left);
  s->coord.y = boss->coord.y + y;
}

// 0x080c1c00
static void Block_Update(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  Coords32 at;
  u16 r;
  s32 ahead;
  if (((p->body).status & BODY_STATUS_DEAD) ||
      (s->mode[1] <= 3 && (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == BEAR_STUNNED))) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Block_Die(p);
    return;
  }
  if (s->mode[1] == 7) {
    SetDDP(&p->body, &sShatterCollision);
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Block_Die(p);
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) {
    r = RANDOM(RNG_0202f388);
    at.x = s->coord.x + (r & 0xFFF) - PIXEL(8);
    at.y = s->coord.y - PIXEL(24);
    useSheet(CreateSlashedEnemy(&at, &sChips[(r >> 1) & 1], 0, (r & 1) | ((r & 1) << 4)));
    if (p->whole && (p->body).hp <= 15) {
      SetMotion(s, ICE(2));
      UpdateEntityAnim(s);
      p->whole = FALSE;
    }
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:  // 0x080c1e18: grows in mouth
      p->scale += 16;
      setScale(s, p->scale);
      s->coord.y += PIXEL(1);
      if (p->scale <= 255) break;
      InitNonAffineMotion(s);
      SetMotion(s, ICE(1));
      UpdateEntityAnim(s);
      (s->spr).oam.priority = 3;
      SET_XFLIP(p, FALSE);
      s->mode[1]++;
      break;
    case 1:  // 0x080c1e94
      if (boss->mode[1] != BEAR_BLOCK_END) break;
      (s->spr).oam.priority = 2;
      blockAt(s, boss, PIXEL(27), -PIXEL(27), -PIXEL(16));
      s->work[2] = 6;
      s->mode[1]++;
      break;
    case 2:  // 0x080c1eec: solid now
      if (--s->work[2] != 0xFF) break;
      s->flags2 |= ENTI_PHYSICS;
      s->size = &sBlockSize;
      s->physicsAttr = 0x2C01;
      blockAt(s, boss, -PIXEL(7), PIXEL(7), -PIXEL(12));
      s->work[2] = 15;
      s->mode[1]++;
      break;
    case 3:  // 0x080c1f54: pushed off
      if (--s->work[2] != 0xFF) break;
      blockAt(s, boss, PIXEL(56), -PIXEL(56), -PIXEL(14));
      s->d.x = s->work[1] ? 0x380 : -0x380;
      s->d.y = 0;
      s->mode[1]++;
      break;
    case 4:  // 0x080c1fb4: slides to wall
      if (FUN_080098a4(s->coord.x, s->coord.y) == 0) {
        s->d.y += 64;
        s->coord.y += s->d.y;
        if (FUN_080098a4(s->coord.x, s->coord.y) == 0) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      }
      s->coord.x += s->d.x;
      ahead = s->work[1] ? s->coord.x + PIXEL(16) : s->coord.x - PIXEL(16);
      if (FUN_080098a4(ahead, s->coord.y - PIXEL(8)) == 0) break;
      PlaySound(SE_Z2_BOX_LAND);
      if (s->work[1]) {
        s->coord.x = FUN_0800a22c(s->coord.x, s->coord.y - PIXEL(8)) - PIXEL(16);
      } else {
        s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y - PIXEL(8)) + PIXEL(16);
      }
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->work[2] = 2;
      setMode(s, 5);
      break;
    case 5:  // 0x080c2098: judders
      if (s->mode[2] == 0) {
        SetDDP(&p->body, &sBlockCollisions[1][0]);
        p->landed = 1;
        s->mode[2]++;
      }
      if (s->work[2] != 0) s->coord.x += (s->work[2] & 1) ? PIXEL(2) : -PIXEL(1);
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;
  }
}

// 0x080c1d1c: four pieces, its top half up from its middle
static void Block_Die(struct Block* p) {
  struct Entity* s = &p->s;
  u16 r = RANDOM(RNG_0202f388);
  s32 off = r & 0xFFF;
  u8 b = r & 1;
  u8 flipA = (b << 4) | (b ^ 1), flipB = ((b ^ 1) << 4) | b;
  Coords32 at;
  at.x = s->coord.x + off - PIXEL(16);
  at.y = s->coord.y - (off + PIXEL(26));
  useSheet(CreateSlashedEnemy(&at, &sChips[0], 0, flipA));
  at.x = s->coord.x + off;
  useSheet(CreateSlashedEnemy(&at, &sChips[1], 0, flipB));
  at.x = s->coord.x + off - PIXEL(16);
  at.y = s->coord.y - off;
  useSheet(CreateSlashedEnemy(&at, &sChips[2], 0, flipA));
  at.x = s->coord.x + off;
  useSheet(CreateSlashedEnemy(&at, &sChips[3], 0, flipB));
  PlaySound(SE_Z2_ICE_BREAK);
  s->flags2 &= ~ENTI_PHYSICS;
  EXIT_BODY(p);
  s->flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// 0x080c216c: shatters rather than crush Zero against a wall
static void blockHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* q;
  if (!(body->hitboxFlags & BODY_STATUS_B2)) return;
  q = body->enemy->parent;
  if (q->kind != ENTITY_PLAYER) return;
  if (FUN_080098a4(q->coord.x - PIXEL(9), q->coord.y) != 0 && FUN_080098a4(q->coord.x + PIXEL(9), q->coord.y) != 0) {
    (body->parent)->mode[1] = 7;
  }
}

// --------------------------------------------
/*
  Zero 2's enemy 19, a block's top, rides 48 px above it.
*/

struct Cap {
  OBJECT_HDR;
  u8 _b4[12];
  u16 scale;  // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Cap) == sizeof(struct Enemy));

static const struct Collision sCapCollisions[2][2];

static void Cap_Init(struct Cap* p);
static void Cap_Update(struct Cap* p);
static void Cap_Die(struct Cap* p);

// clang-format off
const EnemyRoutine gApZ2IceCapRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Cap_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Cap_Update,
    [ENTITY_DIE] =       (EnemyFunc)Cap_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080718bc
static void createCap(struct Block* block) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p == NULL) return;
  INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_CAP);
  p->unk_28 = &block->s;
}

// 0x08071910
static void Cap_Init(struct Cap* p) {
  struct Entity* s = &p->s;
  InitRotatableMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ICE(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  p->scale = 0;
  s->work[2] = 16;
  INIT_BODY(p, &sCapCollisions[0][0], 8, NULL);
  (s->spr).oam.priority = 3;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Cap_Update(p);
}

// 0x080719b4
static void Cap_Update(struct Cap* p) {
  struct Entity* s = &p->s;
  struct Block* block = (struct Block*)s->unk_28;
  u16 r;
  if ((block->s).mode[0] > ENTITY_UPDATE || ((p->body).status & BODY_STATUS_DEAD)) {
    if ((block->s).mode[0] <= ENTITY_UPDATE) PlaySound(SE_Z2_ICE_BREAK);
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Cap_Die(p);
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) {
    r = RANDOM(RNG_0202f388) & 1;
    useSheet(CreateSlashedEnemy(&s->coord, &sChips[2 + r], 0, r | (r << 4)));
  }
  s->coord.x = (block->s).coord.x;
  s->coord.y = (block->s).coord.y - PIXEL(48);
  if (s->mode[1] == 0) {
    p->scale += 16;
    setScale(s, p->scale);
    s->coord.y += s->work[2] << 9;
    if (--s->work[2] != 0xFF) return;
    InitNonAffineMotion(s);
    SetMotion(s, ICE(0));
    UpdateEntityAnim(s);
    SET_XFLIP(p, FALSE);
    (s->spr).oam.priority = 3;
    s->mode[1]++;
    return;
  }
  if (block->landed == 1) {
    SetDDP(&p->body, &sCapCollisions[1][0]);
    block->landed = 2;
  }
  if (s->mode[1] == 1 && (block->s).mode[1] == 2) {
    (s->spr).oam.priority = 2;
    s->mode[1]++;
  }
}

// 0x08071b08
static void Cap_Die(struct Cap* p) {
  struct Entity* s = &p->s;
  u8 b = RANDOM(RNG_0202f388) & 1;
  u8 flipA = (b << 4) | (b ^ 1), flipB = ((b ^ 1) << 4) | b;
  useSheet(CreateSlashedEnemy(&s->coord, &sChips[0], 0, flipA));
  useSheet(CreateSlashedEnemy(&s->coord, &sChips[1], 0, flipB));
  useSheet(CreateSlashedEnemy(&s->coord, &sChips[2], 0, flipA));
  useSheet(CreateSlashedEnemy(&s->coord, &sChips[3], 0, flipB));
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's VFX 26, the bear's frost.
  work0:
    0: chunk thrown off, falls
    1: bit of a shattered ball
    2: frost blown at angle work1
    3: dust at a pillar's foot
*/

static void Ice_Init(struct VFX* p);
static void Ice_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2BearIceRoutine = {
    [ENTITY_INIT] =      Ice_Init,
    [ENTITY_UPDATE] =    Ice_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b3ad8
static void createIce(Coords32* at, u8 kind, u8 work1) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_BEAR_ICE);
  p->coord = *at;
  p->work[0] = kind;
  p->work[1] = work1;
}

// 0x080b3b74, 0x080b3c48, 0x080b3d2c, 0x080b3ddc
static void Ice_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  s32 v;
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = s->d.y = 0;
  SetMotion(s, s->work[0] == 0 ? ICE(13) : ICE(14));
  UpdateEntityAnim(s);
  SET_XFLIP(p, s->work[0] == 0 && s->work[1] != 0);
  if (s->work[0] >= 2) (s->spr).oam.priority = 3;
  switch (s->work[0]) {
    case 0:
      v = (RANDOM(RNG_0202f388) & 0x1FF) + 128;
      s->d.x = s->work[1] ? -v : v;
      break;
    case 1:
      v = (RANDOM(RNG_0202f388) & 0x7FFF) % 384 + 128;
      s->d.x = s->work[1] ? -v : v;
      s->d.y = -((RANDOM(RNG_0202f388) & 0xFF) + 256);
      break;
    case 2:
      s->d.x = COS(s->work[1]) * 192 / 256;
      s->d.y = SIN(s->work[1]) * 192 / 256;
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ice_Update(p);
}

// 0x080b3e4c, 0x080b3e94, 0x080b3edc, 0x080b3f20
static void Ice_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (s->work[0] == 0) s->d.y += 64;
  if (s->work[0] == 1) s->d.y += 24;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (animDone(s)) SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// clang-format off
// 0x0833a968: a swipe's or charge's reach, body, two hurtboxes. Normal from body on
static const struct Collision sCollisions[5] = {
    {DDP, FACTION_ENEMY, 2, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0x00000001, {-0x2c00, -0x2800, 0x2400, 0x1e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0x00000001, {-0xc00, -0x4a00, 0x3400, 0x1600}},
    {DDP, FACTION_ENEMY, 2, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0x00000001, {0x600, -0x1f00, 0x4500, 0x4200}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 8, 0, 0, 1, 0x00000000, {-0xc00, -0x4a00, 0x3400, 0x1600}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 8, 0, 0, 0, 0x00000000, {0x600, -0x1f00, 0x4500, 0x4200}},
};

// 0x0833ef48..: by height, a shot-bouncing face and a hurtbox
static const struct Collision sPillarCollisions[4][2] = {
    {
        {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 1, 0x00000000, {0, -0x1000, 0x1800, 0x2000}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1a00, 0x2000}},
    },
    {
        {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 1, 0x00000000, {0, -0x2000, 0x1800, 0x4000}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0, 0, 0, 0x00000000, {0, -0x2000, 0x1a00, 0x4000}},
    },
    {
        {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 1, 0x00000000, {0, -0x3000, 0x1800, 0x6000}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0, 0, 0, 0x00000000, {0, -0x3000, 0x1a00, 0x6000}},
    },
    {
        {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 1, 0x00000000, {0, -0x3c00, 0x1800, 0x7800}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0, 0, 0, 0x00000000, {0, -0x3c00, 0x1a00, 0x7800}},
    },
};

// 0x0833f008..
static const struct Rect sPillarSizes[4] = {
    {0, -0x1000, 0x1800, 0x2000}, {0, -0x2000, 0x1800, 0x4000}, {0, -0x3000, 0x1800, 0x6000}, {0, -0x3c00, 0x1800, 0x7800},
};

// 0x083439bc
static const struct Collision sBallCollision =
    {DDP, FACTION_ENEMY, 2, 4, 13, 0, 0, 0, 0, 0, 0, 0, 0x00008000, {0, 0x100, 0x1400, 0x1a00}};

// 0x083488f8, 0x08348928: sliding, then landed, its hurtbox neutral
static const struct Collision sBlockCollisions[2][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0x80, 0, 0, 0, 0, 1, 0x00000001, {0, -0x1600, 0x2200, 0x2c00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0xc0, 0, 0, 0x00000000, {0, -0x1600, 0x2000, 0x2c00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0x80, 0, 0, 0, 0, 1, 0x00000001, {0, -0x1600, 0x2200, 0x2c00}},
        {DRP, FACTION_NEUTRAL, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0xc0, 0, 0, 0x00000000, {0, -0x1600, 0x2000, 0x2c00}},
    },
};

// 0x08348958
static const struct Collision sShatterCollision =
    {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0x80, 0, 0, 0, 0, 0, 0x00000001, {0, -0x2000, 0x4000, 0x4000}};

// 0x0833eebc, 0x0833eeec
static const struct Collision sCapCollisions[2][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0x00000001, {0, -0xb00, 0x1200, 0x1c00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0x80, 0, 0, 0x00000000, {0, -0xb00, 0x1c00, 0x1d00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0x00000001, {0, -0xb00, 0x1200, 0x1c00}},
        {DRP, FACTION_NEUTRAL, 0, 0, 0xff, 0xff, 0xff, 0xff, 2, 0x80, 0, 0, 0x00000000, {0, -0xb00, 0x1c00, 0x1d00}},
    },
};

// 0x08343a04
static const struct SlashedEnemy sChips[4] = {
    {ICE(10), {47, 112}, {0, 0}, {0, -1024}, {1023, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ICE(12), {47, 112}, {0, 0}, {192, -1024}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ICE(9), {48, 112}, {0, 0}, {0, -1024}, {1023, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ICE(11), {48, 112}, {0, 0}, {192, -1024}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

// clang-format on

#endif  // AP
