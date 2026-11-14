#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's Leviathan, boss 16. Computer Zone 2, under water.
*/

struct LeviathanFirst {
  OBJECT_HDR;
  u8 _b4[9];
  u8 pattern;             // 0xBD, next attack
  bool8 sinking;          // 0xBE, to mid height from above
  u8 sinceStrike;         // 0xBF, picks since close strike
  s32 left;               // 0xC0, arena
  s32 right;              // 0xC4
  s32 ceiling;            // 0xC8
  s32 floor;              // 0xCC
  u8 dashes;              // 0xD0, left after this one
  u8 _d1;
  s16 slow;               // 0xD2, turn's braking
  s32 target;             // 0xD4, dash's end
  u8 dive;                // 0xD8, may dive at Zero below
  u8 _d9[3];
  struct Entity* struck;  // 0xDC, player her lance touched
  s16 current;            // 0xE0, EX's looped sound
  u8 _e2[2];
};
static_assert(sizeof(struct LeviathanFirst) == sizeof(struct Boss));

enum {
  LEV_INTRO,
  LEV_WAIT,
  LEV_NOP,
  LEV_DECIDE,
  LEV_PAUSE,
  LEV_HOP,
  LEV_SWIM,
  LEV_TURN,
  LEV_TURNED,
  LEV_LEVEL,
  LEV_LANCE_WIND,
  LEV_LANCE1,
  LEV_LANCE2,
  LEV_LANCE3,
  LEV_LANCE_END,
  LEV_WHIRL,
  LEV_WHIRL_END,
  LEV_BACK_OFF,
  LEV_DASH,
  LEV_DASH_END,
  LEV_STRIKE,
  LEV_NOP2,
  LEV_EX,
  LEV_CURRENT,
  LEV_PLUNGE,
  LEV_LAND,
  LEV_DIVE_WIND,
  LEV_DIVE,
  LEV_REBOUND,
};

#define LEV(n) MOTION(DM202_Z2_LEVIATHAN, (n))
#define LANCE(n) MOTION(AP_SHEET_Z2_LEVIATHAN_LANCE, (n))
#define WATER(n) MOTION(AP_SHEET_Z2_LEVIATHAN_WATER, (n))

// clang-format off
// 0x0833cedc
static const struct Collision sBody[20] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 5, 0x00000001, {-0xc00, -0x200, 0x1800, 0x4400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 4, 0x00000001, {0x200, -0x2a00, 0x2c00, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 3, 0x00000001, {-0xc00, -0x200, 0x1800, 0x4400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {-0x1c00, -0x400, 0x800, 0x3800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xe00, 0x1800, 0x1c00, 0x1000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 5, 0x00000001, {0x200, 0x2000, 0x3000, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 4, 0x00000001, {0x200, -0x2800, 0x3000, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 3, 0x00000001, {0x200, -0x400, 0x3e00, 0x4400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {-0x2000, -0x400, 0x800, 0x3600}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x2500, -0x400, 0x800, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 3, 0x00000001, {0x100, 0x1f00, 0x3500, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {-0x2500, -0x400, 0x800, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x200, 0x1000, 0x4800, 0x1600}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x1000, 0x2400}},
};
// clang-format on

#define NORMAL_BODY (&sBody[0])
#define EX_BODY (&sBody[2])

// 0x0833d0c0: close strike's hitboxes by frame
static const u8 sStrikeBody[9] = {0, 0, 0, 6, 4, 11, 10, 16, 0};

static const struct PreloadEntity sLanceSheet = {AP_SHEET_Z2_LEVIATHAN_LANCE, 0, 592, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWaterSheet = {AP_SHEET_Z2_LEVIATHAN_WATER, 0, 647, 6, 0, AP_PRELOAD_SHEET, 0};

static void Leviathan_Init(struct LeviathanFirst* p);
static void Leviathan_Update(struct LeviathanFirst* p);
static void Leviathan_Die(struct LeviathanFirst* p);

// clang-format off
const BossRoutine gApZ2LeviathanFirstRoutine = {
    [ENTITY_INIT] =      (BossFunc)Leviathan_Init,
    [ENTITY_UPDATE] =    (BossFunc)Leviathan_Update,
    [ENTITY_DIE] =       (BossFunc)Leviathan_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void createLance(struct Entity* parent, u8 kind, u8 n);
static void createIceMine(struct Entity* parent, u8 kind, u8 n);
static void createWhirlPiece(struct Entity* boss, u8 n, u8 phase);
static void createLanceTip(struct Entity* parent, u8 kind, u8 n);
void CreateBubble(s32 x, s32 y, u8 kind);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void faceZero(struct LeviathanFirst* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static bool8 alive(struct Zero* z) { return !((z->body).status & BODY_STATUS_DEAD) && (z->body).hp != 0; }

static bool8 countDown(struct Entity* s) { return --s->work[2] == 0xFF; }

static void move(struct Entity* s) {
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// Knocked back, away from where she faces
static void recoil(struct Entity* s) {
  s->d.x = facingRight(s) ? -PIXEL(2) : PIXEL(2);
  s->unk_coord.x = facingRight(s) ? 16 : -16;
  s->d.y = -PIXEL(1);
}

static void backOff(struct Entity* s) {
  s->d.x += s->unk_coord.x;
  move(s);
}

static void bubbles(struct Entity* s) {
  s32 x, y;
  if ((s->work[2] & 1) || !(RANDOM(RNG_0202f388) & 1)) return;
  x = s->coord.x + PIXEL(4 - (RANDOM(RNG_0202f388) & 7));
  y = s->coord.y - PIXEL(RANDOM(RNG_0202f388) & 7);
  CreateBubble(x, y, 0);
}

static void clampX(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->coord.x < p->left + PIXEL(16)) {
    s->coord.x = p->left + PIXEL(16);
  } else if (s->coord.x > p->right - PIXEL(16)) {
    s->coord.x = p->right - PIXEL(16);
  }
}

static void clampY(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->coord.y < p->ceiling + PIXEL(32)) {
    s->coord.y = p->ceiling + PIXEL(32);
  } else if (s->coord.y > p->floor - PIXEL(24)) {
    s->coord.y = p->floor - PIXEL(24);
  }
}

// Zero below and within 10 pixels of x
static bool8 canDive(struct LeviathanFirst* p, s32 x) {
  struct Entity* s = &p->s;
  s32 dx = s->coord.x - x;
  if (p->dive == 0 || s->coord.y >= (pZero2->s).coord.y - PIXEL(32)) return FALSE;
  return (dx < 0 ? -dx : dx) <= 0x9FF;
}

// Stands in for Zero 2's thrown state, 0x08022ea8
static void throwZero(struct Zero* z, s32 dx, s32 dy) {
  GotoMotion(&z->s, MOTION(DM004_ZERO_AIR, 4), 2, 1);
  (z->s).mode[1] = ZERO_AIR, (z->s).mode[2] = 2, (z->s).mode[3] = 1;
  (z->unk_b4).blownSpeed = dx;
  (z->s).d.y = dy;
}

// 0x0805f200
static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct LeviathanFirst* p = (struct LeviathanFirst*)body->parent;
  struct Entity* other = (body->enemy)->parent;
  if ((body->hitboxFlags & 4) && other->kind == ENTITY_PLAYER) p->struck = other;
}

// 0x0805d678
static void Leviathan_Init(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sLanceSheet);
  ApLoadSheet(&sWaterSheet);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, LEV(4));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, NORMAL_BODY, 64);
  (p->body).fn = onHit;
  (s->spr).oam.priority = 3;
  p->pattern = 0;
  p->sinceStrike = 2;
  p->dive = 1;
  s->coord.x += PIXEL(64);
  p->left = FUN_0800a31c(s->coord.x, s->coord.y);
  p->right = FUN_0800a22c(s->coord.x, s->coord.y);
  p->ceiling = FUN_0800a134(s->coord.x, s->coord.y);
  p->floor = FUN_08009f6c(s->coord.x, s->coord.y);
  s->coord.x = p->left + PIXEL(176);
  s->coord.y = p->ceiling;
  p->struck = NULL;
  s->unk_2c = NULL;
  p->current = -1;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Leviathan_Update(p);
}

typedef void (*StateFunc)(struct LeviathanFirst*);
static const StateFunc sStates[29];

// 0x0805d838
static void Leviathan_Update(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Leviathan_Die(p);
    return;
  }
  // 0x0805dc14
  if (((p->body).status & BODY_STATUS_WHITE) && (p->body).elemented == ELEMENT_FLAME) setMode(s, LEV_HOP);
  sStates[s->mode[1]](p);
  if (s->mode[1] > LEV_WAIT) {
    clampX(p);
    clampY(p);
  }
}

// 0x0805d8f8: knocked back, then beams out on script's flag 7
static void Leviathan_Die(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  bool8 right;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(16));
    EXIT_BODY(p);
    recoil(s);
    s->work[2] = 28;
    PlaySound(SE_Z2_LEVIATHAN_HURT);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    CreateBubble(s->coord.x, s->coord.y, 1);
    StopSound(p->current);
    p->current = -1;
    s->mode[2]++;
  }
  if (s->d.x != 0) backOff(s);
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      bubbles(s);
      if (countDown(s)) s->mode[1]++;
      break;
    case 1:
      SetMotion(s, LEV(18));
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) s->mode[1]++;
      break;
    case 3:
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 0x80) s->mode[1]++;
      break;
    case 4:
      right = facingRight(s);
      InitScalerotMotion1(s);
      ResetDynamicMotion(s);
      SetMotion(s, LEV(18));
      SET_XFLIP(p, right);
      PaintEntityWhite(s);
      (s->spr).mag.x = (s->spr).mag.y = 256;
      PlaySound(SE_TENSOU_BACK);
      s->mode[1]++;
      FALLTHROUGH;
    case 5:
      UpdateEntityAnim(s);
      (s->spr).mag.x -= 64;
      if ((u16)(s->spr).mag.x > 63) break;
      (s->spr).mag.x = 4;
      s->mode[1]++;
      break;
    case 6:
      UpdateEntityAnim(s);
      (s->spr).mag.y -= 16;
      if ((u16)(s->spr).mag.y > 128) break;
      s->mode[1]++;
      break;
    case 7:
      UpdateEntityAnim(s);
      s->coord.y -= PIXEL(8);
      if ((u16)(s->spr).mag.y <= 0x1FF) (s->spr).mag.y += 32;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= PIXEL(8)) break;
      s->flags &= ~DISPLAY;
      gStageRun.vm.active |= VM_FLAG1;
      break;
  }
  clampX(p);
  if (s->mode[1] <= 6) clampY(p);
}

// 0x0805dc40: sinks out of sight, swims in from right, waits for script's go
static void Leviathan_Intro(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 32;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      UpdateEntityAnim(s);
      s->coord.y += PIXEL(2);
      if (s->coord.y > p->floor) s->mode[3]++;
      break;
    case 1:
      SetMotion(s, LEV(2));
      (s->spr).oam.priority = 2;
      PlaySound(SE_Z2_LEVIATHAN_SUMMON);
      s->coord.x = p->right + PIXEL(80);
      s->coord.y = p->floor - PIXEL(32);
      s->d.x = -PIXEL(4);
      s->unk_coord.x = 8;
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x > -128) s->mode[3]++;
      break;
    case 3:
      SetMotion(s, LEV(1));
      s->mode[3]++;
      break;
    case 4:
      UpdateEntityAnim(s);
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[3]++;
      break;
    case 5:
      SetMotion(s, LEV(4));
      s->mode[3]++;
      FALLTHROUGH;
    case 6:
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 1) setMode(s, LEV_WAIT);
      break;
  }
}

// 0x0805dd7c: until script lets go
static void Leviathan_Wait(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(15));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, LEV_DECIDE);
}

// 0x0805ddbc
static void Leviathan_Nop(struct LeviathanFirst* p UNUSED) {}

// 0x0805ddc0: dives if Zero is below, strikes if he's close, else next of the pattern
static void Leviathan_Decide(struct LeviathanFirst* p) {
  static const u8 sPattern[12] = {LEV_SWIM, LEV_LEVEL, LEV_LANCE_WIND, LEV_SWIM, LEV_LEVEL, LEV_WHIRL,
                                  LEV_SWIM, LEV_LEVEL, LEV_DASH,       LEV_SWIM, LEV_LEVEL, LEV_EX};
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  UpdateEntityAnim(s);
  faceZero(p);
  if (canDive(p, z->coord.x)) {
    setMode(s, LEV_DIVE_WIND);
    return;
  }
  if (p->sinceStrike > 1 && (u32)(z->coord.x - s->coord.x + PIXEL(64)) <= PIXEL(128) &&
      (u32)(z->coord.y - s->coord.y + PIXEL(64)) <= PIXEL(128)) {
    p->sinceStrike = 0;
    setMode(s, LEV_STRIKE);
    return;
  }
  s->mode[1] = sPattern[p->pattern];
  if (p->pattern == 8) {
    p->dashes = (RANDOM(RNG_0202f388) & 1) + 2;
    RANDOM(RNG_0202f388);  // 0xD1's, never read
  }
  p->pattern = (p->pattern + 1) % (gScore.total->rank > 4 ? 12 : 9);
  p->sinceStrike++;
  s->mode[2] = 0;
}

// 0x0805dfb4
static void Leviathan_Pause(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(0));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, LEV_DECIDE);
}

// 0x0805dff4: hit by fire
static void Leviathan_Hop(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(16));
    SetDDP(&p->body, NORMAL_BODY);
    PlaySound(SE_Z2_LEVIATHAN_HURT);
    recoil(s);
    s->work[2] = 28;
    CreateBubble(s->coord.x, s->coord.y, 1);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->d.x != 0) backOff(s);
  switch (s->mode[3]) {
    case 0:
      UpdateEntityAnim(s);
      bubbles(s);
      if (countDown(s)) s->mode[3]++;
      break;
    case 1:
      SetMotion(s, LEV(17));
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if (s->d.x == 0) s->mode[3]++;
      break;
    case 3:
      setMode(s, LEV_DECIDE);
      break;
  }
}

// 0x0805e150: speeds toward Zero, glides to a stop, turns if she passes him
static void Leviathan_Swim(struct LeviathanFirst* p) {
  static const s16 sPush[2] = {-16, 16};
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  s32 h;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(1));
    faceZero(p);
    s->d.x = facingRight(s) ? PIXEL(1) : -PIXEL(1);
    // Zero 2 measures Zero's height, not the gap
    h = z->coord.y - PIXEL(48);
    if (h > s->coord.y) {
      s->d.y = (h < 0 ? -h : h) > PIXEL(64) ? PIXEL(1) : 128;
    } else {
      s->d.y = (h < 0 ? -h : h) > PIXEL(64) ? -PIXEL(1) : -128;
    }
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (canDive(p, z->coord.x + (s->d.x > 0 ? -PIXEL(10) : PIXEL(10)))) {
    setMode(s, LEV_DIVE_WIND);
    return;
  }
  switch (s->mode[3]) {
    case 0:
      s->d.x += sPush[facingRight(s)];
      if ((s->d.x < 0 ? -s->d.x : s->d.x) > 0x180) {
        SetMotion(s, LEV(2));
        s->mode[3]++;
      }
      break;
    case 1:
      s->d.x += sPush[facingRight(s)];
      if ((s->d.x < 0 ? -s->d.x : s->d.x) > PIXEL(4)) {
        s->unk_coord.x = s->d.x / 48;
        s->work[2] = 48;
        s->mode[3]++;
      }
      break;
    case 2:
      s->d.x -= s->unk_coord.x;
      if (--s->work[2] == 15) {
        SetMotion(s, LEV(1));
        s->mode[3]++;
      }
      break;
    case 3:
      s->d.x -= s->unk_coord.x;
      if (countDown(s)) {
        s->d.x = 0;
        p->dive++;
        setMode(s, LEV_DECIDE);
      }
      break;
  }
  if (s->mode[3] != 0 && (z->coord.x > s->coord.x) != facingRight(s)) {
    p->dive++;
    setMode(s, LEV_TURN);
    s->mode[3] = LEV_DECIDE;
  }
  move(s);
  UpdateEntityAnim(s);
}

// 0x0805e3dc: brakes into a turn, then the state in mode[3]
static void Leviathan_Turn(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(3));
    p->slow = s->d.x >> 5;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.x -= p->slow;
  move(s);
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_TURNED);
}

// 0x0805e43c
static void Leviathan_Turned(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(19));
    SET_XFLIP(p, !facingRight(s));
    s->work[2] = 24;
    s->mode[2]++;
  }
  if (s->work[2] == 8) SetMotion(s, LEV(0));
  UpdateEntityAnim(s);
  s->d.x -= p->slow;
  move(s);
  if (countDown(s)) setMode(s, s->mode[3]);
}

// 0x0805e4ec: to the room's mid height
static void Leviathan_Level(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  s32 mid = p->ceiling + (p->floor - p->ceiling) / 2 + PIXEL(16);
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(4));
    faceZero(p);
    p->sinking = s->coord.y < mid;
    s->d.y = p->sinking ? 128 : -128;
    s->work[2] = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0) {
    s->work[2]++;
    if (p->sinking) {
      s->d.y += 8;
      s->coord.y += s->d.y;
      if (s->work[2] > 64 || s->coord.y > mid) {
        s->work[2] >>= 2;
        s->mode[3]++;
      }
    } else {
      s->d.y -= 8;
      s->coord.y += s->d.y;
      if (s->work[2] > 64 || s->coord.y < mid) {
        s->work[2] >>= 2;
        s->mode[3]++;
      }
    }
  } else {
    s->d.y += p->sinking ? -32 : 32;
    s->coord.y += s->d.y;
    if (countDown(s)) {
      setMode(s, LEV_DECIDE);
      return;
    }
  }
  if (p->sinking && s->coord.y > p->floor) setMode(s, LEV_DECIDE);
}

// 0x0805e648
static void Leviathan_LanceWind(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(5));
    faceZero(p);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_LANCE1);
}

// 0x0805e6d8, 0x0805e788, 0x0805e838: three lance shots, ahead, up, down
static void Leviathan_Lance(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  u8 n = s->mode[1] - LEV_LANCE1;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(6 + n));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) s->mode[3]++;
      break;
    case 1:
      SetMotion(s, LEV(9 + n));
      createLance(s, 0, n);
      PlaySound(SE_Z2_LEVIATHAN_THRUST);
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) {
        s->mode[3]++;
        s->work[2] = 4;
      }
      break;
    case 3:
      UpdateEntityAnim(s);
      if (countDown(s)) setMode(s, s->mode[1] + 1);
      break;
  }
}

// 0x0805e8e8
static void Leviathan_LanceEnd(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(12));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0) {
    if (IsSpriteAnimEnd(s)) {
      s->work[2] = 4;
      s->mode[3]++;
    }
  } else if (countDown(s)) {
    setMode(s, LEV_DECIDE);
  }
}

// 0x0805e940
static void Leviathan_Whirl(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(13));
    s->mode[2]++;
    s->work[2] = 96;
    createIceMine(s, 1, 0);
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, LEV_WHIRL_END);
}

// 0x0805e98c
static void Leviathan_WhirlEnd(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(14));
    s->work[2] = 4;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, LEV_BACK_OFF);
}

// 0x0805e9d0
static void Leviathan_BackOff(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(17));
    PlaySound(SE_Z2_LEVIATHAN_BACK);
    recoil(s);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  backOff(s);
  if (countDown(s)) setMode(s, LEV_DECIDE);
}

// 0x0805ea5c: dashes past or at Zero, dropping ice mines
static void Leviathan_Dash(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  s32 zx = (pZero2->s).coord.x;
  bool8 there;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(2));
    s->mode[2]++;
    if (facingRight(s) == (s->coord.x < zx)) {
      if (s->coord.x > zx) {
        s->d.x = -PIXEL(4);
        p->target = zx - PIXEL(64);
        if (p->target < p->left + PIXEL(48)) p->target = p->left + PIXEL(48);
      } else {
        s->d.x = PIXEL(4);
        p->target = zx + PIXEL(64);
        if (p->target > p->right - PIXEL(48)) p->target = p->right - PIXEL(48);
      }
    } else if (facingRight(s)) {
      s->d.x = PIXEL(4);
      p->target = s->coord.x + PIXEL(240);
      if (p->target < p->left + PIXEL(48)) p->target = p->left + PIXEL(48);
    } else {
      s->d.x = -PIXEL(4);
      p->target = zx - PIXEL(64);
      if (p->target > p->right - PIXEL(48)) p->target = p->right - PIXEL(48);
    }
    if (s->coord.y < p->ceiling + PIXEL(48)) {
      s->d.y = (RANDOM(RNG_0202f388) & 127) + 128;
    } else {
      s->d.y = -((RANDOM(RNG_0202f388) & 127) + 128);
    }
    s->work[2] = 64;
    s->work[3] = 16;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 15) == 0) createIceMine(s, 0, 0);
  move(s);
  there = facingRight(s) ? s->coord.x > p->target : s->coord.x < p->target;
  if (!there && !countDown(s)) return;
  setMode(s, LEV_TURN);
  s->mode[3] = --p->dashes == 0xFF ? LEV_DASH_END : LEV_DASH;
}

// 0x0805ec28: the mines fall
static void Leviathan_DashEnd(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(0));
    s->work[2] = 8;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      UpdateEntityAnim(s);
      if (countDown(s)) s->mode[3]++;
      break;
    case 1:
      SetMotion(s, LEV(1));
      PlaySound(SE_Z2_LEVIATHAN_SHARDS);
      s->work[2] = 32;
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      if (countDown(s)) setMode(s, LEV_DECIDE);
      break;
  }
}

// 0x0805ecb0: lance spun at Zero up close, throws him off it
static void Leviathan_Strike(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  struct Zero* struck = (struct Zero*)p->struck;
  s8 frame;
  u8 a;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(20));
    s->work[2] = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  frame = (s->motion).cmdIdx;
  SetDDP(&p->body, &sBody[sStrikeBody[frame]]);
  if (s->work[2] == 0 && frame == 3) {
    PlaySound(SE_Z2_LEVIATHAN_THRUST);
    s->work[2]++;
  }
  if (s->mode[3] == 0 && sStrikeBody[frame] != 0 && ((p->body).status & BODY_STATUS_B2) && struck != NULL &&
      alive(struck)) {
    a = ((ArcTan2(((z->s).coord.x - s->coord.x) >> 12, ((z->s).coord.y - (s->coord.y + PIXEL(16))) >> 12) + 0x4000) >>
         8) - 64;
    throwZero(struck, COS(a) * 7, SIN(a) * 7);
    s->mode[3]++;
  }
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_DECIDE);
}

// 0x0805ee14
static void Leviathan_Nop2(struct LeviathanFirst* p) { UpdateEntityAnim(&p->s); }

// 0x0805ee20
static void Leviathan_Ex(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(21));
    SetDDP(&p->body, EX_BODY);
    s->unk_28 = ApZ2CreateEx(s, 2);
    PlaySound(SE_Z2_HARPUIA_EX);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_CURRENT);
}

// 0x0805ee88: whirlpool and a current pulling Zero in
static void Leviathan_Current(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(22));
    p->current = PlaySound(SE_Z2_WATER);
    for (i = 0; i < 4; i++) createWhirlPiece(s, i, 0);
    for (i = 0; i < 4; i++) createWhirlPiece(s, i, 2);
    s->d.x = PIXEL(1);
    s->work[2] = 192;
    s->work[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 31) == 0) {
    PlaySound(SE_Z2_LEVIATHAN_THRUST);
    createLance(s, 0, 0x20 | (s->work[3] & 1) << 4);
    s->work[3]++;
  }
  if (z != NULL && alive(z)) {
    if (s->d.x <= 0x2BF) s->d.x += 16;
    ApZ2PushZero(s->coord.x < (z->s).coord.x ? -s->d.x : s->d.x);
  }
  if (countDown(s)) setMode(s, LEV_PLUNGE);
}

// 0x0805efb4: current eases, lance plunged to the floor
static void Leviathan_Plunge(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(23));
    s->d.y = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (z != NULL) {
    if (s->d.x > 0) s->d.x -= 32;
    if (s->coord.x < (z->s).coord.x) {
      (z->s).coord.x -= s->d.x;
    } else {
      (z->s).coord.x += s->d.x;
    }
  }
  if (s->mode[3] != 0) {
    s->coord.y += s->d.y;
    s->d.y += 128;
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(32)) != 0) setMode(s, LEV_LAND);
  } else if (IsSpriteAnimEnd(s)) {
    PlaySound(SE_Z2_LEVIATHAN_THRUST);
    createLanceTip(s, 0, 0);
    s->mode[3]++;
  }
}

// 0x0805f05c
static void Leviathan_Land(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(24));
    SetDDP(&p->body, NORMAL_BODY);
    if (s->unk_28 != NULL) (s->unk_28)->work[1] = 1;
    StopSound(p->current);
    p->current = -1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_DECIDE);
}

// 0x0805f0bc
static void Leviathan_DiveWind(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(26));
    p->dive = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, LEV_DIVE);
}

// 0x0805f0fc: lance first onto Zero
static void Leviathan_Dive(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  s32 zx = (pZero2->s).coord.x;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(25));
    s->d.y = 0;
    PlaySound(SE_Z2_LEVIATHAN_THRUST);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 128;
  if (facingRight(s)) {
    if (s->coord.x < zx) s->coord.x += 128;
  } else if (s->coord.x > zx) {
    s->coord.x -= 128;
  }
  if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(32)) != 0) {
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
    setMode(s, LEV_REBOUND);
  }
}

// 0x0805f190
static void Leviathan_Rebound(struct LeviathanFirst* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, LEV(24));
    s->d.x = facingRight(s) ? -PIXEL(3) : PIXEL(3);
    s->unk_coord.x = facingRight(s) ? 24 : -24;
    s->d.y = -128;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  move(s);
  s->d.x += s->unk_coord.x;
  if (s->d.x == 0) setMode(s, LEV_DECIDE);
}

// 0x0833ce68
static const StateFunc sStates[29] = {
    Leviathan_Intro,     Leviathan_Wait,      Leviathan_Nop,       Leviathan_Decide,   Leviathan_Pause,
    Leviathan_Hop,       Leviathan_Swim,      Leviathan_Turn,      Leviathan_Turned,   Leviathan_Level,
    Leviathan_LanceWind, Leviathan_Lance,     Leviathan_Lance,     Leviathan_Lance,    Leviathan_LanceEnd,
    Leviathan_Whirl,     Leviathan_WhirlEnd,  Leviathan_BackOff,   Leviathan_Dash,     Leviathan_DashEnd,
    Leviathan_Strike,    Leviathan_Nop2,      Leviathan_Ex,        Leviathan_Current,  Leviathan_Plunge,
    Leviathan_Land,      Leviathan_DiveWind,  Leviathan_Dive,      Leviathan_Rebound,
};

// --------------------------------------------
/*
  Zero 2's projectile 40.
  0: lance's flash, fires an ice lance
     work1: 0 ahead, 1 up, 2 down. 0x20 the EX's, bit 4 to the right
  1: ice lance, turns once toward Zero
  2: its trail
*/

struct Lance {
  OBJECT_HDR;
  u8 _b4[12];
  s16 speed;  // 0xC0
  s16 aim;    // 0xC2
};
static_assert(sizeof(struct Lance) == sizeof(struct Projectile));

static void Lance_Init(struct Lance* p);
static void Lance_Update(struct Lance* p);
static void Lance_Die(struct Lance* p);

// clang-format off
const ProjectileRoutine gApZ2LeviathanLanceRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Lance_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Lance_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Lance_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344e18, 0x08344e48
static const struct Collision sLance[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

// 0x08344e78: ice lance's heading by work1, facing left then right
static const u8 sLanceAims[6] = {0, 32, 223, 128, 95, 160};

// 0x080a4e3c
static void createLance(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_LEVIATHAN_LANCE);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080a4f04, 0x080a50dc, 0x080a51e8
static void Lance_Init(struct Lance* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  switch (s->work[0]) {
    case 0:
      InitNonAffineMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, LANCE((s->work[1] & 15) ? 1 : 0));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, facingRight(parent));
      INIT_BODY(p, &sLance[0], 1, NULL);
      s->coord = parent->coord;
      if (s->work[1] & 15) {
        s->coord.x += facingRight(s) ? 0x1B00 : -0x1B00;
        if (s->work[1] == 1) {
          s->coord.y -= 0x2000;
        } else {
          SET_YFLIP(p, TRUE);
          s->coord.y += 0x1400;
        }
      } else if (s->work[1] & 0xF0) {
        SET_XFLIP(p, (s->work[1] & 0x10) != 0);
        s->coord.x += facingRight(s) ? 0x2200 : -0x2200;
        s->coord.y -= 0x1600;
      } else {
        s->coord.y -= 0x600;
        s->coord.x += facingRight(s) ? 0x2900 : -0x2900;
      }
      s->work[2] = 0;
      break;
    case 1:
      InitRotatableMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, LANCE(2));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      INIT_BODY(p, &sLance[1], 1, NULL);
      s->work[3] = sLanceAims[s->work[1] + (facingRight(parent) ? 3 : 0)];
      s->angle = s->work[3];
      p->speed = 256;
      p->aim = 0;
      s->coord = parent->coord;
      s->d.x = COS(s->work[3] + 128);
      s->d.y = SIN(s->work[3] + 128);
      s->work[2] = 8;
      createLance(s, 2, 0);
      break;
    case 2:
      InitRotatableMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, LANCE(3));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      s->angle = parent->work[3];
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Lance_Update(p);
}

// 0x080a4ea4
static void Lance_Update(struct Lance* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  struct Entity* z = &pZero2->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    Lance_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->work[0]) {
    case 0:
      if (++s->work[2] == 5) createLance(s, 1, s->work[1] & 1);
      if (IsSpriteAnimEnd(s)) Lance_Die(p);
      return;
    case 2:
      s->angle = parent->work[3];
      s->coord.x = parent->coord.x + COS(parent->work[3]) * 14;
      s->coord.y = parent->coord.y + SIN(parent->work[3]) * 14;
      if (parent->mode[0] > ENTITY_UPDATE) Lance_Die(p);
      return;
  }
  switch (s->mode[1]) {
    case 0:
      if (!countDown(s)) break;
      s->mode[1]++;
      p->aim = (ArcTan2((z->coord.x - s->coord.x - PIXEL(16)) >> 12, (z->coord.y - s->coord.y) >> 12) + 0x8000) >> 8;
      if (p->aim > s->work[3]) {
        s->work[2] = p->aim - s->work[3];
        s->mode[3] = s->work[2] <= 126;
      } else {
        s->work[2] = s->work[3] - p->aim;
        s->mode[3] = s->work[2] >> 7;
      }
      if ((s8)s->work[2] < 0) s->work[2] = ~s->work[2];
      s->work[2] = s->work[2] / 3 + 3;
      break;
    case 1:
      if (countDown(s)) {
        s->mode[1]++;
      } else {
        s->work[3] += s->mode[3] ? 3 : -3;
      }
      break;
    case 2:
      s->work[2] = 0xFF;
      s->mode[1]++;
      break;
    case 3:
      if (countDown(s)) {
        Lance_Die(p);
        return;
      }
      break;
  }
  p->speed += 16;
  if (p->speed > 1024) p->speed = 1024;
  s->d.x = Cos(s->work[3] + 128, p->speed);
  s->d.y = Sin(s->work[3] + 128, p->speed);
  move(s);
  s->angle = s->work[3];
}

// 0x080a54a8
static void Lance_Die(struct Lance* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 41.
  0: ice mine, sways until her dashes end, then sinks
  1: whirl, unseen center of 2s. Spins out its ice, then is thrown at Zero
  2: whirl's ice
     work1: angle
*/

struct IceMine {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  u8 _b8[4];
  s8 spin;    // 0xBC
  u8 _bd[3];
  u16 timer;  // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct IceMine) == sizeof(struct Projectile));

static void IceMine_Init(struct IceMine* p);
static void IceMine_Update(struct IceMine* p);
static void IceMine_Die(struct IceMine* p);

// clang-format off
const ProjectileRoutine gApZ2IceMineRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)IceMine_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)IceMine_Update,
    [ENTITY_DIE] =       (ProjectileFunc)IceMine_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344eac: harmless until formed
static const struct Collision sMine[3] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

// 0x08344f0c
static const struct Collision sWhirl[3] = {
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {0x0, 0x0, 0x2000, 0x3800}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 1, 0x00000000, {0x0, 0x0, 0x2000, 0x3800}},
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, METAL, 0, 0, 0x00000000, {0x0, 0x0, 0x2000, 0x3800}},
};

// 0x08344ef4
static const struct Collision sWhirlIce = {
    DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800},
};
// clang-format on

// 0x080a54f0
static void createIceMine(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ICE_MINE);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080a55a0, 0x080a5670, 0x080a5754
static void IceMine_Init(struct IceMine* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  switch (s->work[0]) {
    case 0:
      InitNonAffineMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, WATER(0));
      UpdateSpriteAnimation(p);
      INIT_BODY(p, &sMine[0], 2, NULL);
      SET_XFLIP(p, facingRight(parent));
      s->coord = parent->coord;
      p->homeX = s->coord.x;
      s->work[2] = 0;
      break;
    case 1:
      s->flags |= FLIPABLE;
      SET_XFLIP(p, facingRight(parent));
      INIT_BODY(p, sWhirl, 1, NULL);
      s->coord = parent->coord;
      s->coord.x += facingRight(s) ? 0x1200 : -0x1200;
      p->spin = facingRight(s) ? 4 : -4;
      s->coord.y -= 0x300;
      s->work[2] = 0;
      s->work[3] = 9;
      break;
    case 2:
      InitNonAffineMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, WATER(1));
      UpdateSpriteAnimation(p);
      INIT_BODY(p, &sWhirlIce, 1, NULL);
      SET_XFLIP(p, facingRight(parent));
      s->coord = parent->coord;
      s->work[3] = 0;
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  IceMine_Update(p);
}

// 0x080a5818
static void updateMine(struct IceMine* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (s->mode[1] != 0 && ((p->body).status & BODY_STATUS_DEAD)) {
    ApZ2CreateIceBurst(s, 2, 0);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    IceMine_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (IsSpriteAnimEnd(s)) {
        SetDDP(&p->body, &sMine[1]);
        s->mode[1]++;
      }
      break;
    case 1:
      s->coord.x = p->homeX + SIN(s->work[2]) * 4;
      s->work[2] += 4;
      if (boss->mode[1] == LEV_HOP || boss->mode[1] == LEV_DASH_END) {
        s->mode[1]++;
        s->work[3] = 0;
      }
      break;
    case 2:
      s->coord.y += PIXEL(1);
      s->coord.x = p->homeX + SIN(s->work[2]) * 4;
      s->work[2] += 4;
      if ((s->work[3]++ & 15) == 0) ApZ2CreateIceBurst(s, 0, 0);
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        CreateSmoke(3, &s->coord);
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// Gone, and its ice with a splash
static void burst(struct IceMine* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  (p->s).work[1] = 1;
}

// 0x080a5948
static void updateWhirl(struct IceMine* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  struct Entity* z = &pZero2->s;
  bool8 spinning = s->mode[1] < 2;
  u8 aim;
  if (((p->body).status & BODY_STATUS_WHITE) && facingRight(boss) == (boss->coord.x < z->coord.x) &&
      !isSoundPlaying(SE_Z2_LEVIATHAN_WHIRL)) {
    PlaySound(SE_Z2_LEVIATHAN_WHIRL);
  }
  s->work[2] += p->spin;
  switch (s->mode[1]) {
    case 0:
      if ((s->work[2] & 31) == 0) createIceMine(s, 2, s->work[2]);
      if (s->work[2] == 0) {
        s->mode[1]++;
        p->timer = 32;
      }
      break;
    case 1:
      if (--p->timer != 0xFFFF) break;
      s->mode[1]++;
      aim = ArcTan2((z->coord.x - s->coord.x - PIXEL(16)) >> 12, (z->coord.y - s->coord.y) >> 12) >> 8;
      s->d.x = Cos(aim, 384);
      s->d.y = Sin(aim, 384);
      EXIT_BODY(p);
      break;
    case 2:
      s->work[3]++;
      move(s);
      if (s->work[3] == 20) {
        s->mode[1]++;
        p->timer = 512;
      }
      break;
    case 3:
      s->work[3]++;
      move(s);
      if (--p->timer == 0xFFFF) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        return;
      }
      break;
  }
  if (boss->mode[0] > ENTITY_UPDATE || (spinning && boss->mode[1] == LEV_HOP)) burst(p);
}

// 0x080a5b6c: squashed ring while it spins, then spreads
static void updateWhirlIce(struct IceMine* p) {
  struct Entity* s = &p->s;
  struct Entity* whirl = s->unk_28;
  u8 a = whirl->work[2] + s->work[1];
  u8 r = whirl->work[3];
  UpdateSpriteAnimation(p);
  if (whirl->mode[1] > 1 && (s->work[3]++ & 15) == 0) ApZ2CreateIceBurst(s, 0, 0);
  s->coord.x = whirl->coord.x + COS(a) * r;
  s->coord.y = whirl->coord.y + SIN(a) * (r <= 19 ? 20 : r);
  if (whirl->mode[0] > ENTITY_UPDATE) {
    if (whirl->work[1] != 0) ApZ2CreateIceBurst(s, 2, 0);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    CreateSmoke(3, &s->coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

// 0x080a5558
static void IceMine_Update(struct IceMine* p) {
  switch ((p->s).work[0]) {
    case 0:
      updateMine(p);
      break;
    case 1:
      updateWhirl(p);
      break;
    case 2:
      updateWhirlIce(p);
      break;
  }
}

// 0x080a5570
static void IceMine_Die(struct IceMine* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's enemy 58, her whirlpool through the EX.
  work0: height, 64 pixels a step up from floor
  work1: 0 or 2, half a turn apart
*/

struct WhirlPiece {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  u8 _b8[12];
};
static_assert(sizeof(struct WhirlPiece) == sizeof(struct Enemy));

static void WhirlPiece_Init(struct WhirlPiece* p);
static void WhirlPiece_Update(struct WhirlPiece* p);
static void WhirlPiece_Die(struct WhirlPiece* p);

// clang-format off
const EnemyRoutine gApZ2WhirlPieceRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)WhirlPiece_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)WhirlPiece_Update,
    [ENTITY_DIE] =       (EnemyFunc)WhirlPiece_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080872a0
static void createWhirlPiece(struct Entity* boss, u8 n, u8 phase) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_WHIRL_PIECE);
    p->unk_28 = boss;
    p->work[0] = n;
    p->work[1] = phase;
  }
}

// Behind her for the far half of a turn
static void circle(struct WhirlPiece* p) {
  struct Entity* s = &p->s;
  u8 a = s->work[2];
  s->renderPrio = a > 128 ? 25 : 23;
  s->coord.x = p->homeX + SIN((s->work[3]++ & 1) ? a : a + 64) * s->d.x;
  s->work[2] = a + 3;
}

// 0x080872fc
static void WhirlPiece_Init(struct WhirlPiece* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, WATER((s->work[0] & 1) ? 6 : 5));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  s->coord.x = boss->coord.x;
  s->coord.y = FUN_08009f6c(boss->coord.x, boss->coord.y) - (s->work[0] << 14);
  p->homeX = s->coord.x;
  s->d.x = 0;
  s->work[3] = 0;
  s->work[2] = s->work[1] << 6;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  WhirlPiece_Update(p);
}

// 0x080873ac: widens, until she plunges or is hit by fire
static void WhirlPiece_Update(struct WhirlPiece* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  UpdateSpriteAnimation(p);
  if (s->d.x < 32) s->d.x++;
  circle(p);
  if (boss->mode[1] == LEV_PLUNGE || boss->mode[1] == LEV_HOP) SET_ENEMY_ROUTINE(p, ENTITY_DIE);
}

// 0x0808743c: narrows to nothing
static void WhirlPiece_Die(struct WhirlPiece* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  circle(p);
  if (s->d.x > 0) {
    s->d.x--;
  } else {
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  }
}

// --------------------------------------------
/*
  Zero 2's enemy 59.
  0: splash at her lance's tip, nine shards on the floor
  1: shard
     work1: angle
*/

static void LanceTip_Init(struct Enemy* p);
static void LanceTip_Update(struct Enemy* p);
static void LanceTip_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2LanceTipRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)LanceTip_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)LanceTip_Update,
    [ENTITY_DIE] =       (EnemyFunc)LanceTip_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x083415c0, 0x083415f0
static const struct Collision sLanceTip[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1200, 0x1800}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

// 0x080874c4
static void createLanceTip(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_LANCE_TIP);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x08087574, 0x08087614
static void LanceTip_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 0) {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, WATER(7));
    SET_XFLIP(p, facingRight(parent));
    INIT_BODY(p, &sLanceTip[0], 1, NULL);
  } else {
    InitRotatableMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, WATER(8));
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, &sLanceTip[1], 1, NULL);
    s->angle = s->work[1] + 192;
    s->coord.x = parent->coord.x;
    s->coord.y = FUN_08009f6c(parent->coord.x, parent->coord.y);
    s->d.x = -(COS(s->work[1]) * 4);
    s->d.y = -(SIN(s->work[1]) * 4);
    s->work[2] = 128;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  LanceTip_Update(p);
}

// 0x080876f4, 0x080877b4
static void LanceTip_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 i;
  UpdateSpriteAnimation(p);
  if (s->work[0] == 0) {
    s->coord.x = boss->coord.x + (facingRight(s) ? PIXEL(10) : -PIXEL(10));
    s->coord.y = boss->coord.y + PIXEL(32);
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    PlaySound(SE_Z2_ICE_BREAK);
    for (i = 0; i < 9; i++) createLanceTip(s, 1, i * 16);
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    return;
  }
  move(s);
  if (s->work[2] < 32) s->flags = (s->work[2] & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  if (countDown(s) || FUN_080098a4(s->coord.x, s->coord.y) != 0) SET_ENEMY_ROUTINE(p, ENTITY_DIE);
}

// 0x08087828, 0x08087840
static void LanceTip_Die(struct Enemy* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }

#endif  // AP
