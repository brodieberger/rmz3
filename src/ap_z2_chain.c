#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "overworld.h"
#include "player/zero.h"
#include "string_ids.h"
#include "text.h"
#include "score.h"
#include "sound.h"
#include "trig.h"
#include "weapon.h"
#include "zero.h"

#include "gba/syscall.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"
#include "constants/weapon.h"

#if AP

/*
  Zero 2's Chain Rod. Row with hardness 8 latches, body's unk_28 moves it.
*/

enum { CHAIN_START, CHAIN_WIND, CHAIN_FIRE, CHAIN_HOLD, CHAIN_REEL, CHAIN_END, CHAIN_LATCH, CHAIN_PULL, CHAIN_SPIN_WIND, CHAIN_SPIN, CHAIN_SPIN_END };
enum { AIM_NONE, AIM_FORWARD, AIM_UP_FORWARD, AIM_DOWN_FORWARD, AIM_UP, AIM_DOWN };

#define FACING_RIGHT(p) (((p)->s.flags & X_FLIP) != 0)
#define LINKS 8
#define REACH PIXEL(64)
#define FIRE_FRAMES 8
#define HOLD_FRAMES 6
#define PULL_SPEED 0x500
#define TIP(n) MOTION(DM065_Z2_CHAIN, (n))

static EWRAM_DATA struct {
  Coords32 tip;
  Coords32 hand;
  motion_t pose;
  u8 stance;
  u8 aim;
  u8 timer;
  bool8 hit;
  bool8 out;
  struct Entity* target;
  ApChainHook hook;
  u8 targetId;
  s16 angle;  // swing, 0 straight down, 0x2000 45 degrees
  s16 from;
  s16 reach;
  s16 speed;
  u16 length;
  s8 dir;
  u8 row;
  s8 intoX;  // side tip hit
  s8 intoY;
  s32 block;  // id of solid entity tip hit, -1 terrain
} sChain = {0};

// 0x08334566
static const u8 sAngle[5] = {0, 0, 224, 32, 192};
// 0x0802b29e, 0x0802e68e, 0x0802f766, 0x080309cc
static const motion_t sSpinPose[4][2] = {
    [ZERO_GROUND] = {MOTION(DM069_Z2_ZERO_CHAIN_CHARGE, 0), MOTION(DM069_Z2_ZERO_CHAIN_CHARGE, 1)},
    [ZERO_AIR] = {MOTION(DM071_Z2_ZERO_CHAIN_CHARGE_AIR, 0), MOTION(DM071_Z2_ZERO_CHAIN_CHARGE_AIR, 1)},
    [ZERO_WALL] = {MOTION(DM072_Z2_ZERO_CHAIN_CHARGE_WALL, 0), MOTION(DM072_Z2_ZERO_CHAIN_CHARGE_WALL, 1)},
    [ZERO_LADDER] = {MOTION(DM073_Z2_ZERO_CHAIN_CHARGE_LADDER, 0), MOTION(DM073_Z2_ZERO_CHAIN_CHARGE_LADDER, 1)},
};
// 0x08338d4c..0x08338d58
static const u8 sSpinMotion[4] = {
    [ZERO_GROUND] = DM070_Z2_CHAIN_SPIN,
    [ZERO_AIR] = DM074_Z2_CHAIN_SPIN_AIR,
    [ZERO_WALL] = DM075_Z2_CHAIN_SPIN_WALL,
    [ZERO_LADDER] = DM076_Z2_CHAIN_SPIN_LADDER,
};
// 0x08335d44, 0x08335d58, 0x08335d70, 0x08335d78
static const struct Coord sHand[4][6] = {
    [ZERO_GROUND] = {{-2048, -4608}, {-8704, -4608}, {-6656, -9216}, {-7168, -256}, {0, -13056}},
    [ZERO_AIR] = {{-512, -5888}, {-7424, -5888}, {-5376, -10496}, {-5888, -1536}, {256, -13568}, {0, 256}},
    [ZERO_WALL] = {{1280, -4096}, {6656, -4096}},
    [ZERO_LADDER] = {{-512, -4352}, {-6912, -4352}},
};
// 0x08335c94, 0x08335c9a, 0x08335ca1, 0x08335ca7, through Zero's motion table
static const motion_t sPose[4][6] = {
    [ZERO_GROUND] = {0, MOTION(DM038_Z2_ZERO_CHAIN, 2), MOTION(DM038_Z2_ZERO_CHAIN, 1), MOTION(DM038_Z2_ZERO_CHAIN, 3), MOTION(DM038_Z2_ZERO_CHAIN, 0)},
    [ZERO_AIR] = {0, MOTION(DM039_Z2_ZERO_CHAIN_AIR, 2), MOTION(DM039_Z2_ZERO_CHAIN_AIR, 1), MOTION(DM039_Z2_ZERO_CHAIN_AIR, 3), MOTION(DM039_Z2_ZERO_CHAIN_AIR, 0),
                  MOTION(DM039_Z2_ZERO_CHAIN_AIR, 4)},
    [ZERO_WALL] = {0, MOTION(DM066_Z2_ZERO_CHAIN_WALL, 0)},
    [ZERO_LADDER] = {0, MOTION(DM067_Z2_ZERO_CHAIN_LADDER, 0)},
};
// 0x0802acb4, 0x0802e538, 0x0802f650, 0x080308b0
static const motion_t sEndPose[4] = {
    [ZERO_GROUND] = MOTION(DM038_Z2_ZERO_CHAIN, 5),
    [ZERO_AIR] = MOTION(DM039_Z2_ZERO_CHAIN_AIR, 6),
    [ZERO_WALL] = MOTION(DM066_Z2_ZERO_CHAIN_WALL, 2),
    [ZERO_LADDER] = MOTION(DM067_Z2_ZERO_CHAIN_LADDER, 2),
};
// 0x0802affa
#define PULL_POSE MOTION(DM038_Z2_ZERO_CHAIN, 4)
// 0x083363d4
static const u8 sTipAnim[5] = {2, 2, 1, 3, 0};

static const struct Collision sCollisions[5][2];

extern const char_t gApChainName[];

static void setPose(struct Zero* z, motion_t m) {
  sChain.pose = m;
  SetSpriteAnimation(z, m);
}

static void updateHand(struct Zero* z) {
  s32 x = sHand[sChain.stance][sChain.aim].x;
  sChain.hand.x = (z->s).coord.x + (FACING_RIGHT(z) ? -x : x);
  sChain.hand.y = (z->s).coord.y + sHand[sChain.stance][sChain.aim].y;
}

// 0x0803609c
static void follow(struct Zero* z) {
  Coords32 from = sChain.hand;
  updateHand(z);
  sChain.tip.x += sChain.hand.x - from.x;
  sChain.tip.y += sChain.hand.y - from.y;
}

// 0x08035fb4
static void placeTip(struct Zero* z, u8 done) {
  u8 angle = sAngle[sChain.aim];
  if (FACING_RIGHT(z) == (sChain.stance == ZERO_WALL)) angle = 128 - angle;
  sChain.tip.x = sChain.hand.x + (((COS(angle) * REACH) >> 8) * done) / FIRE_FRAMES;
  sChain.tip.y = sChain.hand.y + (((SIN(angle) * REACH) >> 8) * done) / FIRE_FRAMES;
}

// 0x08039ddc
static bool8 createLinks(struct Zero* z) {
  u8 slot = (z->unk_b4).mainCopy == WEAPON_CHAIN ? 0 : 1;
  u8 i;
  KillAllWeapons(DeleteSaber);
  SetWeaponElement(slot, WEAPON_COLOR_NORMAL);
  for (i = 0; i < LINKS; i++) {
    struct Entity* p = AllocEntityLast(gWeaponHeaderPtr);
    if (p == NULL) return i != 0;
    INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_Z2_CHAIN);
    p->flags2 &= ~ENTITY_FLAGS2_B6;
    p->renderPrio = 16;
    p->tileNum = gWeaponTileNum[slot];
    p->palID = gWeaponPalIDs[slot];
    p->work[1] = i;
    p->unk_28 = (struct Entity*)z;
  }
  return TRUE;
}

// Button as CountRodButton reads it: type B's sub weapon has its own, else main
static bool8 isHeld(struct Zero* z) {
  KEY_INPUT key = (z->input).mapping.main;
  if ((z->unk_b4).mainCopy != WEAPON_CHAIN && (z->unk_b4).status.keyMap.attackMode == 1) key = (z->input).mapping.sub;
  return ((z->input).raw & key) != 0;
}

// Holding on doesn't charge
static void noCharge(struct Zero* z) {
  if ((z->unk_b4).mainCopy == WEAPON_CHAIN) {
    (z->unk_b4).status.charge[0] = 0;
    z->mainChargeFrame = 0;
  } else {
    (z->unk_b4).status.charge[1] = 0;
    z->subChargeFrame = 0;
  }
}

// 0x08036b0c
static u16 callHook(u16 pulling, s32 dx, s32 dy) {
  if (sChain.target == NULL || sChain.hook == NULL || sChain.target->mode[0] > ENTITY_UPDATE || sChain.target->id != sChain.targetId) return 0;
  return sChain.hook(sChain.target, pulling, dx, dy);
}

static void letGo(void) {
  callHook(0, 0, 0);
  sChain.target = NULL;
  sChain.hook = NULL;
}

// 0x08036a0c
static void startReel(struct Zero* z) {
  s32 dx = sChain.tip.x - sChain.hand.x;
  s32 dy = sChain.tip.y - sChain.hand.y;
  letGo();
  sChain.timer = (Sqrt(dx * dx + dy * dy) * FIRE_FRAMES) / REACH;
  if (sChain.timer == 0) sChain.timer = 1;
  if (sChain.pose != sPose[sChain.stance][sChain.aim]) setPose(z, sPose[sChain.stance][sChain.aim]);
  (z->unk_b4).attackState8[1] = CHAIN_REEL;
}

// 0x0802b0a0
static void pull(struct Zero* z) {
  s32 dx = sChain.tip.x - sChain.hand.x;
  s32 dy = sChain.tip.y - sChain.hand.y;
  s32 len = Sqrt(dx * dx + dy * dy);
  s32 left = len - PULL_SPEED;
  s32 x, y;
  u16 held;
  if (left < 0 || len == 0) left = 0;
  x = len != 0 ? sChain.hand.x + left * dx / len : sChain.hand.x;
  y = len != 0 ? sChain.hand.y + left * dy / len : sChain.hand.y;
  held = callHook(left > 0, x - sChain.tip.x, y - sChain.tip.y);
  sChain.tip.x = x;
  sChain.tip.y = y;
  if (left <= 0 || held == 0) startReel(z);
}

// 0x0803d46c
static void createSpin(struct Zero* z) {
  u8 slot = (z->unk_b4).mainCopy == WEAPON_CHAIN ? 0 : 1;
  struct Entity* p;
  KillAllWeapons(DeleteSaber);
  SetWeaponElement(slot, (z->unk_b4).status.element);
  p = AllocEntityFirst(gWeaponHeaderPtr);
  if (p == NULL) return;
  INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_Z2_CHAIN_SPIN);
  p->flags2 &= ~ENTITY_FLAGS2_B6;
  p->renderPrio = 16;
  p->tileNum = gWeaponTileNum[slot];
  p->palID = gWeaponPalIDs[slot];
  p->work[0] = sChain.stance;
  p->unk_28 = (struct Entity*)z;
}

// Solid entity under point
static s32 blockAt(s32 x, s32 y) {
  u8 i;
  for (i = 0; i < gOverworld.terrain.objectLen; i++) {
    struct Hazard* h = HAZARD(i);
    if ((u32)(x - h->center.x) + h->hw < (u32)h->hw * 2 && (u32)(y - h->center.y) + h->hh < (u32)h->hh * 2) return i;
  }
  return -1;
}

// 0x0801f3d0
static s32 slotOf(s32 id) {
  u8 i;
  for (i = 0; i < gOverworld.terrain.objectLen; i++) {
    if (HAZARD(i)->id == id) return i;
  }
  return -1;
}

static bool8 solidAt(s32 x, s32 y) { return (GetGroundMetatileAttr(x, y) & 15) || blockAt(x, y) >= 0; }

// 0x08036878, 0x080369cc
static bool8 hookable(void) {
  s32 slot = slotOf(sChain.block);
  metatile_attr_t attr = slot >= 0 ? HAZARD(slot)->attr : GetGroundMetatileAttr(sChain.tip.x + sChain.intoX * 0x100, sChain.tip.y + sChain.intoY * 0x100);
  return (attr & 15) && !(attr & 0x400) && (attr & ~0x80) != 15 && (attr & ~0x80) != 14;
}

// 0x08032f24, tip level or above
static bool8 hangs(u8 angle) {
  u8 side = angle + 128;
  if ((u8)(angle + 64) <= 127) side = 128 - side;
  return side <= 96;
}

static s32 stepTo(s32 at, s32 to) { return to > at + 0x100 ? at + 0x100 : (to < at - 0x100 ? at - 0x100 : to); }

// 0x080361a8: back to surface, x then y. Started inside or behind it, Zero too close: no hit
static bool8 snapTip(Coords32 from) {
  s32 n, slot, edge;
  if (solidAt(from.x, from.y)) return FALSE;
  sChain.intoX = 0;
  sChain.intoY = 0;
  sChain.block = -1;
  while (from.x != sChain.tip.x) {
    n = stepTo(from.x, sChain.tip.x);
    slot = blockAt(n, from.y);
    if (slot >= 0) {
      edge = HAZARD(slot)->center.x + (n > from.x ? -HAZARD(slot)->hw - 1 : HAZARD(slot)->hw);
    } else if (GetGroundMetatileAttr(n, from.y) & 15) {
      edge = n > from.x ? (n & ~0xFFF) - 1 : (n | 0xFFF) + 1;
    } else {
      from.x = n;
      continue;
    }
    if ((edge - from.x) * (n - from.x) < 0) break;
    sChain.intoX = n > from.x ? 1 : -1;
    sChain.block = slot >= 0 ? HAZARD(slot)->id : -1;
    sChain.tip.x = edge;
    return TRUE;
  }
  while (from.y != sChain.tip.y) {
    n = stepTo(from.y, sChain.tip.y);
    slot = blockAt(sChain.tip.x, n);
    if (slot >= 0) {
      edge = HAZARD(slot)->center.y + (n > from.y ? -HAZARD(slot)->hh - 1 : HAZARD(slot)->hh);
    } else if (GetGroundMetatileAttr(sChain.tip.x, n) & 15) {
      edge = n > from.y ? (n & ~0xFFF) - 1 : (n | 0xFFF) + 1;
    } else {
      from.y = n;
      continue;
    }
    if ((edge - from.y) * (n - from.y) < 0) return FALSE;
    sChain.intoY = n > from.y ? 1 : -1;
    sChain.block = slot >= 0 ? HAZARD(slot)->id : -1;
    sChain.tip.y = edge;
    return TRUE;
  }
  return FALSE;
}

static void startSwing(struct Zero* z) {
  (z->s).mode[1] = ZERO_CHAIN_SWING;
  (z->s).mode[2] = 0;
  (z->s).mode[3] = 0;
  (z->unk_b4).attackState8[0] = 0;
  PlaySound(SE_Z2_CHAIN_LATCH);
}

static void finish(struct Zero* z) {
  sChain.out = FALSE;
  (z->unk_b4).attackState8[0] = 0;
  if (sChain.stance == ZERO_AIR) {
    GotoMotion(&z->s, (z->s).mode[2] == 1 ? MOTION(DM004_ZERO_AIR, 3) : MOTION(DM004_ZERO_AIR, 4), 2, 1);
  } else if (sChain.stance == ZERO_WALL) {
    GotoMotion(&z->s, MOTION(DM005_ZERO_WALL, 0), 4, 1);
  } else if (sChain.stance == ZERO_LADDER) {
    GotoMotion(&z->s, MOTION(DM007_ZERO_LADDER, 0), 0, 1);
  } else {
    SetSpriteAnimation(z, GetDefaultMotion(z));
  }
}

// 0x0802a774, 0x0802a7ec, then fire, hold, reel, end
void ApChainAttack(struct Zero* z) {
  u8* state = &(z->unk_b4).attackState8[1];
  zero_input_t input = (z->input).val;
  Coords32 from;

  (z->restriction).move = (z->s).mode[1] != ZERO_AIR;
  if ((z->unk_b4).status.weapons[0] == WEAPON_CHAIN) {
    (z->restriction).mainCharge = TRUE;
  } else {
    (z->restriction).subCharge = TRUE;
  }

  if (*state != CHAIN_START && sChain.stance != (z->s).mode[1]) {
    if (sChain.stance == ZERO_WALL) SET_PLAYER_XFLIP(z, !FACING_RIGHT(z));
    sChain.stance = (z->s).mode[1];
    if (sChain.stance >= ZERO_WALL) sChain.aim = AIM_FORWARD;
    if (*state >= CHAIN_SPIN_WIND) {
      sChain.pose = sSpinPose[sChain.stance][*state == CHAIN_SPIN_END];
    } else {
      sChain.pose = *state == CHAIN_PULL ? PULL_POSE : (*state == CHAIN_END ? sEndPose[sChain.stance] : sPose[sChain.stance][sChain.aim]);
    }
    GotoMotion(&z->s, sChain.pose, z->motionCmdIdx, z->motionDuration);
  } else if (*state != CHAIN_START) {
    KeepMotion(z, sChain.pose);
  }

  switch (*state) {
    case CHAIN_START:
      sChain.stance = (z->s).mode[1];
      if (GetWeaponCharge(z, (z->unk_b4).mainCopy != WEAPON_CHAIN) == FULL_CHARGE) {
        sChain.timer = 5;
        setPose(z, sSpinPose[sChain.stance][0]);
        *state = CHAIN_SPIN_WIND;
        break;
      }
      if (sChain.stance >= ZERO_WALL) {
        sChain.aim = AIM_FORWARD;
      } else if (input & DPAD_UP) {
        sChain.aim = (input & (DPAD_LEFT | DPAD_RIGHT)) ? AIM_UP_FORWARD : AIM_UP;
      } else if (input & DPAD_DOWN) {
        sChain.aim = AIM_DOWN_FORWARD;
      } else {
        sChain.aim = AIM_FORWARD;
      }
      sChain.hit = FALSE;
      sChain.target = NULL;
      sChain.hook = NULL;
      setPose(z, sPose[sChain.stance][sChain.aim]);
      (*state)++;
      FALLTHROUGH;
    case CHAIN_WIND:
      if ((z->s).motion.cmdIdx != 1 || (z->s).motion.duration > 1) break;
      updateHand(z);
      placeTip(z, 0);
      from.x = (z->s).coord.x;
      from.y = sChain.hand.y;
      sChain.hit = snapTip(from);
      if (!createLinks(z)) {
        finish(z);
        break;
      }
      sChain.out = TRUE;
      sChain.timer = FIRE_FRAMES;
      IncWeaponUseCount(WEAPON_ROD);
      PlaySound(SE_Z2_CHAIN_FIRE);
      *state = CHAIN_FIRE;
      break;
    case CHAIN_FIRE:
      if (sChain.target != NULL && isHeld(z) && sChain.stance == ZERO_GROUND) {
        PlaySound(SE_Z2_CHAIN_LATCH);
        *state = CHAIN_LATCH;
        break;
      }
      if (sChain.hit || sChain.timer == 0) {
        sChain.timer = HOLD_FRAMES;
        *state = CHAIN_HOLD;
        break;
      }
      sChain.timer--;
      from = sChain.tip;
      updateHand(z);
      placeTip(z, FIRE_FRAMES - sChain.timer);
      if (solidAt(sChain.tip.x, sChain.tip.y) && snapTip(from)) {
        sChain.hit = TRUE;
        // 0x0802e30a
        if (sChain.stance == ZERO_AIR && isHeld(z) && hookable()) startSwing(z);
      }
      break;
    case CHAIN_HOLD:
      follow(z);
      if (--sChain.timer != 0) break;
      startReel(z);
      break;
    case CHAIN_LATCH:
      updateHand(z);
      noCharge(z);
      if (!isHeld(z) || callHook(1, 0, 0) == 0) {
        startReel(z);
      } else if (input & (FACING_RIGHT(z) ? DPAD_LEFT : DPAD_RIGHT)) {
        setPose(z, PULL_POSE);
        *state = CHAIN_PULL;
      }
      break;
    case CHAIN_PULL:
      updateHand(z);
      noCharge(z);
      if (isHeld(z)) {
        pull(z);
      } else {
        startReel(z);
      }
      break;
    case CHAIN_REEL:
      follow(z);
      sChain.tip.x = sChain.hand.x + (sChain.tip.x - sChain.hand.x) * (sChain.timer - 1) / sChain.timer;
      sChain.tip.y = sChain.hand.y + (sChain.tip.y - sChain.hand.y) * (sChain.timer - 1) / sChain.timer;
      if (--sChain.timer != 0) break;
      sChain.out = FALSE;
      setPose(z, sEndPose[sChain.stance]);
      *state = CHAIN_END;
      break;
    case CHAIN_END:
    case CHAIN_SPIN_END:
      if ((z->s).motion.state == ANIM_END) finish(z);
      break;
    // 0x0802b264
    case CHAIN_SPIN_WIND:
      if ((z->s).motion.duration > 1) break;
      createSpin(z);
      IncWeaponUseCount(WEAPON_ROD);
      *state = CHAIN_SPIN;
      break;
    case CHAIN_SPIN:
      if ((z->s).motion.state != 4 || --sChain.timer != 0) break;
      setPose(z, sSpinPose[sChain.stance][1]);
      *state = CHAIN_SPIN_END;
      break;
  }
}

// --------------------------------------------
// Zero 2's mode 4, hanging from tip
enum { ROPE_START, ROPE_FALL, ROPE_SWING };
enum { SWING_INIT, SWING_IN, SWING_OUT, SWING_TURN, SWING_IDLE };

// 0x08335d18
#define SWING_REST_Y -5888
#define SWING_AIM 8  // air aim pose past 45 degrees
// 0x08335d1c..0x08335d30, rows 0..7 of Zero's swing motion
static const struct Coord sSwingHand[8] = {
    {-1536, -11264}, {-1024, -11776}, {0, -12032}, {1280, -12032},
    {1792, -11776},  {0, -12032},     {2304, -11776}, {-1280, -11264},
};

static s32 sqrtOr1(s32 n) {
  s32 r = Sqrt(n);
  return r != 0 ? r : 1;
}

// 0x08033154
static s16 reachOf(s16 angle) { return (u16)(angle + 0x2000) <= 0x4000 ? (angle < 0 ? -angle : angle) : 0x2000; }

// 0x08033184
static void pump(struct Zero* z, zero_input_t key) {
  if (!((z->input).val & key)) return;
  sChain.reach += ((z->input).val & (key == DPAD_LEFT ? ZERO_INPUT_PRESS_DPAD_LEFT : ZERO_INPUT_PRESS_DPAD_RIGHT)) ? 0x800 : 0x100;
  if (sChain.reach > 0x2000) sChain.reach = 0x2000;
}

// 0x080331e8
static s16 brake(struct Zero* z, zero_input_t key) {
  s16 floor = sChain.angle < 0 ? -sChain.angle : sChain.angle;
  if (!((z->input).val & key)) return sChain.reach;
  sChain.reach -= ((z->input).val & (key == DPAD_LEFT ? ZERO_INPUT_PRESS_DPAD_LEFT : ZERO_INPUT_PRESS_DPAD_RIGHT)) ? 0x800 : 0x100;
  if (sChain.reach < floor) sChain.reach = floor;
  return sChain.reach;
}

static void swingRow(struct Zero* z, u8 row) {
  if (row == sChain.row) return;
  if (row < 5 && sChain.row < 5) {
    GotoMotion(&z->s, MOTION(DM068_Z2_ZERO_CHAIN_SWING, row), (z->s).motion.cmdIdx, (z->s).motion.duration);
  } else {
    SetSpriteAnimation(z, MOTION(DM068_Z2_ZERO_CHAIN_SWING, row));
  }
  sChain.row = row;
}

static void handOffset(struct Zero* z, s32* x, s32* y) {
  if (sChain.row == SWING_AIM) {
    *x = FACING_RIGHT(z) ? -sHand[ZERO_AIR][sChain.aim].x : sHand[ZERO_AIR][sChain.aim].x;
    *y = sHand[ZERO_AIR][sChain.aim].y;
    return;
  }
  *x = sSwingHand[sChain.row].x;
  *y = sSwingHand[sChain.row].y;
  if ((z->s).motion.cmdIdx == 1) {
    if (sChain.row == 6) *x = 2048;
    if (sChain.row == 7) {
      *x = 2304;
      *y = -11776;
    }
  }
  if (FACING_RIGHT(z)) *x = -*x;
}

// 0x08027c14
static void swingInit(struct Zero* z) {
  u8 angle = CalcAngle(sChain.tip.x - sChain.hand.x, sChain.tip.y - sChain.hand.y);
  u8 side = angle + 128;
  s32 dx = sChain.tip.x - (z->s).coord.x;
  s32 dy = sChain.tip.y - ((z->s).coord.y + SWING_REST_Y);
  s32 length = Sqrt(dx * dx + dy * dy) - 0x1800;
  bool8 back = side == 64 ? FACING_RIGHT(z) : (u8)(angle + 64) <= 127;

  sChain.dir = back ? -1 : 1;
  sChain.angle = (s16)((side << 8) - 0x4000);
  sChain.from = sChain.angle;
  sChain.reach = reachOf(sChain.angle);
  if (length < 0x400) length = 0x400;
  if (length > REACH) length = REACH;
  sChain.length = length;
  sChain.speed = 0;
  sChain.row = 0xFF;
  if ((z->s).d.y >= 0 && ((z->s).d.x != 0 || (z->s).d.y != 0)) {
    s32 v = (Sqrt((z->s).d.x * (z->s).d.x + (z->s).d.y * (z->s).d.y) * 255) >> 8;
    if (v > 0) {
      s32 a = length - ((length * 255) >> 8);
      s32 b = (length * 6) >> 8;
      s32 cap = sqrtOr1(sChain.reach << 5);
      v = (v << 8) / sqrtOr1(a * a + b * b);
      sChain.speed = v > cap ? cap : v;
    }
  }
  (z->s).mode[3] = sChain.reach <= 0x667 ? SWING_IDLE : SWING_IN;
}

// 0x08027316: wall where swing heads
static bool8 wallAhead(struct Zero* z, const struct Rect* range) {
  Coords32 at = (z->s).coord;
  bool8 hit;
  (z->s).coord.x -= sChain.dir * 0x100;
  PushoutWallX(z, range, 0);
  PushoutWallX(z, range, 1);
  hit = (z->s).coord.x != at.x - sChain.dir * 0x100;
  (z->s).coord = at;
  return hit;
}

static s32 clampStep(s32 from, s32 to) {
  if (to > from + PIXEL(15)) return from + PIXEL(15);
  if (to < from - PIXEL(15)) return from - PIXEL(15);
  return to;
}

// 0x08032f48
static void swingPoint(s32 r, Coords32* out) {
  u16 turned = (u16)(sChain.angle + 0x4000);
  u8 a = turned >> 8;
  u8 frac = turned & 0xFF;
  s32 x = (COS(a) * r) >> 8;
  s32 y = (SIN(a) * r) >> 8;
  out->x = x + ((((COS(a + 1) * r) >> 8) - x) * frac >> 8);
  out->y = y + ((((SIN(a + 1) * r) >> 8) - y) * frac >> 8);
}

static u8 restAngle(struct Zero* z) { return CalcAngle(sChain.tip.x - (z->s).coord.x, sChain.tip.y - ((z->s).coord.y + SWING_REST_Y)); }

// 0x08335c84
static const u8 sFallAim[5] = {AIM_UP, AIM_UP_FORWARD, AIM_FORWARD, AIM_DOWN_FORWARD, AIM_DOWN};

// 0x08036ad0
static u8 fallAim(struct Zero* z, u8 angle) {
  u8 a = angle + 64;
  if (!FACING_RIGHT(z)) a = -a;
  a += 16;
  return a <= 159 ? sFallAim[a >> 5] : AIM_NONE;
}

// 0x08026e38, 0x08026ea8: tip below, falls on rope until it hangs
static void ropeFall(struct Zero* z) {
  const struct Rect* range = &gZeroRanges[z->posture];
  zero_input_t input = (z->input).val;
  bool8 right = FACING_RIGHT(z);
  s32 x = (z->s).coord.x, y, dx, dy, r;
  u8 angle, aim;
  bool8 landed;

  if ((z->s).mode[3] == 0) {
    (z->s).mode[3] = 1;
    if ((z->s).d.y < 0) (z->s).d.y = 0;
  }
  if (input & DPAD_LEFT) {
    x -= CalcDx(z);
  } else if (input & DPAD_RIGHT) {
    x += CalcDx(z);
  }
  y = (z->s).coord.y + (z->s).d.y;
  (z->s).d.y += getFallAcceleration(z);
  if ((z->s).d.y > calcMaxFallSpeed(z)) (z->s).d.y = calcMaxFallSpeed(z);

  dx = x - sChain.tip.x;
  dy = y + SWING_REST_Y - sChain.tip.y;
  r = (REACH + 0x1800) * (REACH + 0x1800) - dy * dy;
  if (dx * dx > r) {
    r = Sqrt(r);
    x = sChain.tip.x + (dx < 0 ? -r : r);
  }
  (z->s).d.x = x > (z->s).coord.x ? x - (z->s).coord.x : (z->s).coord.x - x;
  if ((z->s).d.x != 0) {
    (z->s).coord.x = x;
    PushoutWallX(z, range, 0);
    PushoutWallX(z, range, 1);
  }
  (z->s).coord.y = y;
  PushoutByCeiling(z, range, 0);
  landed = PushoutByFloor1(z, range, 1) != 0;

  if (sChain.tip.x != (z->s).coord.x) SET_PLAYER_XFLIP(z, sChain.tip.x > (z->s).coord.x);
  angle = restAngle(z);
  aim = fallAim(z, angle);
  if (aim == AIM_NONE || aim == AIM_UP || aim == AIM_DOWN) SET_PLAYER_XFLIP(z, right);
  if (aim != AIM_NONE) {
    sChain.aim = aim;
    if (sChain.pose != sPose[ZERO_AIR][aim]) setPose(z, sPose[ZERO_AIR][aim]);
  }
  updateHand(z);

  if (hangs(angle)) {
    (z->s).mode[2] = ROPE_SWING;
    (z->s).mode[3] = SWING_INIT;
  } else if (landed) {
    (z->s).mode[1] = ZERO_GROUND;
    (z->s).mode[2] = 0;
    (z->s).mode[3] = 0;
    PlaySound(SE_WALK);
  }
}

// 0x08026dc0, 0x080271b4, 0x08027e68..0x08027fbc
void ApChainSwing(struct Zero* z) {
  const struct Rect* range = &gZeroRanges[z->posture];
  zero_input_t input = (z->input).val;
  Coords32 at, oldAt = (z->s).coord;
  s32 handX, handY, pd, blendX, blendY, x, pushedX;
  metatile_attr_t floor, pushedY;
  u16 oldLength;
  u8 state, was, turned, side;

  if ((z->s).mode[2] == ROPE_START) (z->s).mode[2] = hangs(restAngle(z)) ? ROPE_SWING : ROPE_FALL;
  if ((z->s).mode[2] == ROPE_FALL) {
    ropeFall(z);
    return;
  }
  if ((z->s).mode[3] == SWING_INIT) swingInit(z);
  was = (z->s).mode[3];
  pd = sChain.angle * sChain.dir;

  // steering
  state = was == SWING_TURN ? (pd > 0 ? SWING_OUT : SWING_IN) : was;
  if (state == SWING_IN) {
    pump(z, sChain.dir < 0 ? DPAD_RIGHT : DPAD_LEFT);
  } else if (state == SWING_OUT) {
    brake(z, sChain.dir < 0 ? DPAD_LEFT : DPAD_RIGHT);
  } else if (FACING_RIGHT(z) == (sChain.dir < 0)) {
    // 0x08027f68: idle, pumps toward facing, brakes away from it
    pump(z, FACING_RIGHT(z) ? DPAD_RIGHT : DPAD_LEFT);
  } else if (brake(z, FACING_RIGHT(z) ? DPAD_LEFT : DPAD_RIGHT) <= 0) {
    sChain.dir = FACING_RIGHT(z) ? -1 : 1;
  }
  if (was == SWING_TURN) {
    if (sChain.row == 6) {
      if ((z->s).motion.state == ANIM_END) {
        swingRow(z, 7);
        SET_PLAYER_XFLIP(z, !FACING_RIGHT(z));
      }
    } else if (sChain.row == 7) {
      if ((z->s).motion.state == ANIM_END) (z->s).mode[3] = state;
    } else {
      swingRow(z, 6);
    }
  }

  oldLength = sChain.length;
  if (input & DPAD_UP) {
    s32 length = (s32)sChain.length - 0x180;
    sChain.length = length < 0x400 ? 0x400 : length;
  } else if (input & DPAD_DOWN) {
    s32 length = (s32)sChain.length + 0x180;
    sChain.length = length > REACH ? REACH : length;
  }

  if ((z->s).mode[3] != SWING_TURN) {
    if (sChain.reach <= 0x667) {
      (z->s).mode[3] = SWING_IDLE;
    } else {
      (z->s).mode[3] = pd < 0 ? SWING_IN : SWING_OUT;
    }
  }

  if ((sChain.reach != 0 || sChain.angle != 0) && (sChain.length != oldLength || pd >= 0 || !wallAhead(z, range))) {
    s32 speed;
    if (pd < 0) {
      s32 cap = sqrtOr1(sChain.reach << 5);
      speed = sqrtOr1(((sChain.angle - sChain.from) * sChain.dir) << 5);
      if (speed < sChain.speed) speed = sChain.speed;
      if (speed > cap) speed = cap;
    } else {
      s32 left = sChain.reach - pd;
      speed = sqrtOr1((left > 0 ? left : 0) << 5);
    }
    sChain.speed = speed;
    sChain.angle += speed * sChain.dir;
  }

  // end of swing
  pd = sChain.angle * sChain.dir;
  turned = FALSE;
  if (pd > 0 && pd >= sChain.reach) {
    if ((z->s).mode[3] != SWING_IDLE) {
      (z->s).mode[3] = SWING_TURN;
      was = SWING_OUT;
      turned = TRUE;
    }
    sChain.angle = sChain.reach * sChain.dir;
    sChain.dir = -sChain.dir;
    sChain.from = sChain.angle;
    sChain.speed = 0;
  }

  // Zero's pose
  state = (z->s).mode[3];
  side = (u16)(sChain.angle + 0x4000) >> 8;
  if (state == SWING_IDLE) {
    swingRow(z, 5);
  } else if (state == SWING_TURN) {
    if (was != SWING_TURN || turned) {
      SET_PLAYER_XFLIP(z, sChain.dir > 0);
      swingRow(z, 6);
    }
  } else if ((u16)(sChain.angle + 0x2000) <= 0x4000) {
    s32 row = ((sChain.dir > 0 ? side - 32 : 96 - side) * 5) >> 6;
    if (row < 0) row = 0;
    swingRow(z, row > 4 ? 4 : row);
  } else {
    // 0x080275e4
    u8 aim = fallAim(z, side + 128);
    if (aim != AIM_NONE && (sChain.row != SWING_AIM || sChain.aim != aim)) {
      sChain.aim = aim;
      sChain.row = SWING_AIM;
      SetSpriteAnimation(z, sPose[ZERO_AIR][aim]);
    }
  }

  // 0x08027600: from tip, out by length, past hand as it lengthens
  swingPoint(sChain.length + ((0x1800 * (s32)sChain.length) >> 14), &at);
  handOffset(z, &handX, &handY);
  blendX = ((0 - handX) * (s32)sChain.length >> 14) + handX;
  blendY = ((SWING_REST_Y - handY) * (s32)sChain.length >> 14) + handY;
  x = clampStep(oldAt.x, sChain.tip.x + at.x - blendX);
  (z->s).d.x = x > oldAt.x ? x - oldAt.x : oldAt.x - x;
  (z->s).coord.y = clampStep(oldAt.y, sChain.tip.y + at.y - blendY);
  (z->s).d.y = (z->s).coord.y - oldAt.y;

  // 0x080276ee: y then x pushed by terrain, lands only with hand up by tip
  floor = PushoutByFloor1(z, range, 1);
  pushedY = (z->s).d.y < 0 ? PushoutByCeiling(z, range, 0) : floor;
  if (!floor || (z->s).coord.y + sSwingHand[5].y > sChain.tip.y + 0x400) {
    (z->s).coord.x = x;
    PushoutWallX(z, range, 0);
    PushoutWallX(z, range, 1);
    floor = PushoutByFloor1(z, range, 1);
  }
  if (floor && (z->s).coord.y + sSwingHand[5].y <= sChain.tip.y + 0x400) {
    (z->s).mode[1] = ZERO_GROUND;
    (z->s).mode[2] = 0;
    (z->s).mode[3] = 0;
    PlaySound(SE_WALK);
    return;
  }

  // 0x08027940: swing carries on from where Zero ends up
  pushedX = ((z->s).coord.x - x) * sChain.dir;
  if (pushedY || pushedX != 0) {
    s32 restY = (z->s).coord.y + SWING_REST_Y;
    s32 length, qx, qy;
    u8 a;
    bool8 apart;
    handOffset(z, &handX, &handY);
    handX += (z->s).coord.x;
    handY += (z->s).coord.y;
    a = CalcAngle(sChain.tip.x - (z->s).coord.x, sChain.tip.y - restY);
    apart = (u8)((s8)(CalcAngle(sChain.tip.x - handX, sChain.tip.y - handY) - a) + 8) > 16;
    length = sqrtOr1((sChain.tip.x - (z->s).coord.x) * (sChain.tip.x - (z->s).coord.x) + (sChain.tip.y - restY) * (sChain.tip.y - restY)) - 0x1800;
    if (!apart) length = (length + Sqrt((sChain.tip.x - handX) * (sChain.tip.x - handX) + (sChain.tip.y - handY) * (sChain.tip.y - handY))) / 2;
    sChain.length = length > REACH ? REACH : (length < 0x400 ? 0x400 : length);
    // Pushed from behind on way down changes nothing
    if (pushedX > 0 || (pushedX < 0 && sChain.angle * sChain.dir >= 0)) {
      qx = apart ? (z->s).coord.x : handX + ((z->s).coord.x - handX) * (s32)sChain.length / 0x4000;
      qy = apart ? restY : handY + (restY - handY) * (s32)sChain.length / 0x4000;
      sChain.angle = (s16)((CalcAngle(qx - sChain.tip.x, qy - sChain.tip.y) << 8) - 0x4000);
      if (sChain.reach == 0) {
        sChain.dir = sChain.angle < 0 ? 1 : -1;
        SET_PLAYER_XFLIP(z, sChain.dir < 0);
      }
      if (sChain.reach == 0 || sChain.angle * sChain.dir <= 0) {
        sChain.from = sChain.angle;
        sChain.speed = 0;
      }
      sChain.reach = reachOf(sChain.angle);
    }
  }

  handOffset(z, &handX, &handY);
  sChain.hand.x = (z->s).coord.x + handX;
  sChain.hand.y = (z->s).coord.y + handY;
}

// 0x08024ac8
void ApChainSwingInput(struct Zero* z) {
  s32 slot = slotOf(sChain.block);
  // 0x08036878: tip rides solid entity
  if (slot >= 0) {
    sChain.tip.x += HAZARD(slot)->center.x - HAZARD(slot)->unk_10.x;
    sChain.tip.y += HAZARD(slot)->center.y - HAZARD(slot)->unk_10.y;
  }
  noCharge(z);
  if (isHeld(z) && sChain.out && hookable()) return;
  // Falls keeping swing's d.y, Zero 2's hop off an upswing
  (z->s).mode[1] = ZERO_AIR;
  (z->s).mode[2] = 2;
  (z->s).mode[3] = 1;
  (z->s).d.x = CalcDx(z);
  SetSpriteAnimation(z, MOTION(DM004_ZERO_AIR, 4));
}

// --------------------------------------------
// Zero 2's weapon 2. work1: 0 tip, rest links, 8 px apart
static void Chain_Init(struct Weapon* p);
static void Chain_Update(struct Weapon* p);

// clang-format off
const WeaponRoutine gApZ2ChainRoutine = {
    [ENTITY_INIT] =      (WeaponFunc)Chain_Init,
    [ENTITY_UPDATE] =    (WeaponFunc)Chain_Update,
    [ENTITY_DIE] =       (WeaponFunc)DeleteWeapon,
    [ENTITY_DISAPPEAR] = (WeaponFunc)DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,
};
// clang-format on

static void Dragged_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (sChain.target == s && !((p->body).status & BODY_STATUS_DEAD)) return;
  s->onUpdate = (*gEnemyFnTable[s->id])[ENTITY_UPDATE];
  ((EnemyFunc)s->onUpdate)(p);
}

// 0x080667b4, 0x080676b8, minus state changes
static u16 dragNative(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  // Shield side, tug turns it round as Recoil Rod does
  if (s->id == ENEMY_LAMPLORT && (dx != 0 || dy != 0) && ((*pZero2).s.coord.x > s->coord.x) == ((s->flags & X_FLIP) != 0)) {
    if (s->mode[1] != 5 && s->mode[1] != 6) {
      s->mode[1] = 5;
      s->mode[2] = 0;
    }
    return 0;
  }
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling && FUN_080098a4(s->coord.x, s->coord.y) == 0) {
    s->onUpdate = Dragged_Update;
    return 1;
  }
  return 0;
}

static bool8 isNativePullable(struct Entity* s) {
  if ((u32)s < (u32)gEnemies || (u32)s >= (u32)(gEnemies + ARRAY_COUNT(gEnemies))) return FALSE;
  switch (s->id) {
    case ENEMY_P_GUARDIAN:
    case ENEMY_P_HUNTER:
    case ENEMY_P_ZOMBIE:
    case ENEMY_P_FIST:
    case ENEMY_CARRY_ARM:
    case ENEMY_MELLNET:
    case ENEMY_SHARKSEAL_X:
    case ENEMY_BEETANK:
    case ENEMY_SWORDY:
    case ENEMY_PUFFY:
    case ENEMY_CANNON_HOPPER:
    case ENEMY_SHOTCOUNTER:
    case ENEMY_BATRING:
    case ENEMY_LAMPLORT:
    case ENEMY_CLAVEKER:
    case ENEMY_PETATRIA:
    case ENEMY_MOTHJIRO:
    case ENEMY_SHELLUNO:
      return TRUE;
    case ENEMY_GYRO_CANNON:   // Not propeller
    case ENEMY_SHOTLOID:      // Not gun
    case ENEMY_PURPLE_NERPLE:
      return s->work[0] == 0;
    case ENEMY_DEATHLOCK:
      return s->work[0] != 9;
    case ENEMY_SHELLCRAWLER:  // Not shell
      return s->work[0] != 4;
    case ENEMY_VOLCAIRE:
      return s->work[0] == 2;  // Crawlers
    case ENEMY_SNAKECORD:
      return s->work[0] == 0 && s->mode[1] >= 3 && s->mode[1] <= 8;  // Off ceiling
  }
  return FALSE;
}

// 0x08039ff4
static void onHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Body* e = body->enemy;
  if (!(body->status & (BODY_STATUS_B2 | BODY_STATUS_B5))) return;
  if (body->status & BODY_STATUS_B2) {
    if (e->status & BODY_STATUS_BLOCKED) return;
  } else {
    sChain.hit = TRUE;
  }
  if (sChain.target == NULL && ((e->processing->hardness & HARDNESS_B3) || isNativePullable(e->parent))) {
    sChain.target = e->parent;
    sChain.targetId = e->parent->id;
    sChain.hook = (ApChainHook)e->unk_28;
    // Zero 3's own, asm has no hook
    if (sChain.hook == NULL && isNativePullable(sChain.target)) sChain.hook = dragNative;
  }
}

// 0x080399f0, 0x08039b08
static void Chain_Init(struct Weapon* p) {
  struct Entity* s = &p->s;
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[1] == 0) {
    SetSpriteAnimation(p, TIP(sTipAnim[sChain.aim]));
    s->flags |= COLLIDABLE;
    INIT_BODY(p, sCollisions[sChain.aim], 1, onHit);
    (p->body).atk += ApChainBonus((struct Zero*)s->unk_28);
  } else {
    SetSpriteAnimation(p, TIP((s->work[1] & 1) ? 8 : 7));
  }
  Chain_Update(p);
}

// 0x08039b7c, 0x08039cc8
static void Chain_Update(struct Weapon* p) {
  struct Entity* s = &p->s;
  struct Zero* z = (struct Zero*)s->unk_28;
  if (sChain.out && (z->s).mode[1] != ZERO_CHAIN_SWING && ((z->unk_b4).attackState8[0] != 3 || z->usingWeapon != WEAPON_CHAIN)) {
    letGo();
    sChain.out = FALSE;
  }
  if (!sChain.out) {
    if (s->work[1] == 0) EXIT_BODY(p);
    s->flags &= ~DISPLAY;
    SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  s->coord.x = sChain.tip.x + (sChain.hand.x - sChain.tip.x) * s->work[1] / LINKS;
  s->coord.y = sChain.tip.y + (sChain.hand.y - sChain.tip.y) * s->work[1] / LINKS;
  SET_XFLIP(p, FACING_RIGHT(z) != (sChain.stance == ZERO_WALL));
  UpdateSpriteAnimation(p);
}

// Zero 2's, in its own palette 9 order
static const u32 sMenuIcon[4][8] = {
    {0xDDDFFFF0, 0x2222222F, 0xBBBBB62F, 0x9FFB632F, 0x9FB6332F, 0x7B63332F, 0x6633332D, 0x3333332D},
    {0x09DDDDDD, 0x99222222, 0x93333336, 0x93333333, 0x9333369F, 0x9336FB77, 0x93796333, 0x939F3333},
    {0x3333332D, 0xBF33332D, 0x66B3332D, 0x3993332D, 0xF773332D, 0x6333332D, 0x33333259, 0x99999990},
    {0x9379BF99, 0x93376677, 0x93333333, 0x93333333, 0x939BF99B, 0x73766776, 0x73333333, 0x27799999}
};

static const u32 sHudIcon[6][8] = {
    {0xFF110000, 0x33F10000, 0x66310000, 0x6E310000, 0xEE310000, 0xEE310000, 0xEE310000, 0xEE310000},
    {0x11FFFFFF, 0x1F333333, 0x13EE7666, 0x1EEEF919, 0x1EE7FF66, 0x1EE66E6E, 0x1EF1EEEE, 0x1EFF1F1E},
    {0x7E310000, 0x6E310000, 0xEE310000, 0xE3110000, 0x111F0000, 0x11F00000, 0xFFF00000, 0x111F0000},
    {0x1EE76FF6, 0x1EEEEEE1, 0x1EEEEEF1, 0x11EEEEFF, 0xF1111111, 0x0FFFFFF1, 0x0F111FFF, 0xF1111111},
    {0x7E310000, 0x6E310000, 0xEE310000, 0xE31F0000, 0x11F00000, 0xFF000000, 0x00000000, 0x00000000},
    {0x1EE76FF6, 0x1EEEEEE1, 0x1EEEEEF1, 0xF1EEEEFF, 0x0F111111, 0x00FFFFFF, 0x00000000, 0x00000000}
};

#define HUD_TILE 0xD6
#define HUD_MAP(n) (u16)(0x1000 | (0x200 + HUD_TILE + (n)))

// Zero 2's palette 9 to chip_icon's
static const u8 sMenuColors[16] = {0, 0, 1, 11, 7, 2, 8, 3, 12, 4, 13, 9, 14, 5, 10, 6};

void ApLoadChainMenuIcon(u32 tile) {
  u32* dst = (u32*)(VRAM + 0x10000 + (tile + 20) * 32);
  u32 w, out;
  u8 i, k;
  for (i = 0; i < 32; i++) {
    w = sMenuIcon[i / 8][i % 8];
    out = 0;
    for (k = 0; k < 32; k += 4) out |= (u32)sMenuColors[(w >> k) & 15] << k;
    dst[i] = out;
  }
}

void ApLoadChainHudIcon(void) { MemCopy32(sHudIcon, (void*)(VRAM + 0xC000 + HUD_TILE * 32), sizeof(sHudIcon)); }

void ApDrawChainHudIcon(u16* bg0, struct Zero* z) {
  struct ZeroStatus* status = &(z->unk_b4).status;
  if (status->weapons[0] == WEAPON_CHAIN) {
    bg0[0x180] = HUD_MAP(0);
    bg0[0x181] = HUD_MAP(1);
    bg0[0x1A0] = HUD_MAP(2);
    bg0[0x1A1] = HUD_MAP(3);
  }
  if (status->weapons[1] == WEAPON_CHAIN) {
    bg0[0x1C0] = HUD_MAP(0);
    bg0[0x1C1] = HUD_MAP(1);
    bg0[0x1E0] = HUD_MAP(4);
    bg0[0x1E1] = HUD_MAP(5);
  }
}

u8 ApChainBonus(struct Zero* z) {
  u8 bonus = isElfUsed_2(z, ELF_RODERAS) != 0;
  return gApSavedata.chainLevel > 2 ? bonus + gApSavedata.chainLevel - 2 : bonus;
}

const char_t* ApWeaponName(u8 weapon) { return weapon == WEAPON_CHAIN ? gApChainName : STRING(STR_MAINMENU_WEAPON + weapon); }

// --------------------------------------------
// Zero 2's weapon 11, charged rod. work0: stance, work1: row
#include "ap_z2_chain_hit.inc"

static void Spin_Init(struct Weapon* p);
static void Spin_Update(struct Weapon* p);

// clang-format off
const WeaponRoutine gApZ2ChainSpinRoutine = {
    [ENTITY_INIT] =      (WeaponFunc)Spin_Init,
    [ENTITY_UPDATE] =    (WeaponFunc)Spin_Update,
    [ENTITY_DIE] =       (WeaponFunc)DeleteWeapon,
    [ENTITY_DISAPPEAR] = (WeaponFunc)DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,
};
// clang-format on

static void Spin_SetHit(struct Weapon* p) {
  struct Entity* s = &p->s;
  struct Zero* z = (struct Zero*)s->unk_28;
  s8 cmd = (s->motion).cmdIdx;
  if (s->work[1] != 0 || cmd < 1 || cmd > 4) {
    s->flags &= ~COLLIDABLE;
    return;
  }
  s->flags |= COLLIDABLE;
  InitWeaponBody(&p->body, sChainSpinHits[s->work[0]][cmd - 1], 4 + ApChainBonus(z), (z->unk_b4).status.element, -1, -1);
}

// 0x0803d28c
static void Spin_Init(struct Weapon* p) {
  struct Entity* s = &p->s;
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(sSpinMotion[s->work[0]], 0));
  INIT_BODY(p, sChainSpinHits[s->work[0]][0], 1, NULL);
  PlaySound(SE_Z2_CHAIN_SPIN);
  Spin_Update(p);
}

// 0x0803d318
static void Spin_Update(struct Weapon* p) {
  struct Entity* s = &p->s;
  struct Zero* z = (struct Zero*)s->unk_28;
  s8 cmd = (s->motion).cmdIdx;
  if ((z->unk_b4).attackState8[0] != 3 || z->usingWeapon != WEAPON_CHAIN || (z->unk_b4).attackState8[1] < CHAIN_SPIN) {
    EXIT_BODY(p);
    s->flags &= ~DISPLAY;
    SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->work[0] != (z->s).mode[1] && (z->s).mode[1] < 4) {
    s->work[0] = (z->s).mode[1];
    GotoMotion(s, MOTION(sSpinMotion[s->work[0]], s->work[1]), (s->motion).cmdIdx, (s->motion).duration);
  }
  if (s->work[1] == 0 && (z->unk_b4).attackState8[1] == CHAIN_SPIN_END) {
    s->work[1] = 1;
    SetSpriteAnimation(p, MOTION(sSpinMotion[s->work[0]], 1));
  }
  s->coord = (z->s).coord;
  SET_XFLIP(p, FACING_RIGHT(z));
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx != cmd || (s->flags & COLLIDABLE) == 0) Spin_SetHit(p);
}

#define HITBOX(x, y) \
  { \
    {DDP, FACTION_ALLY, 1, 4, ATK_ROD, 0x00, 0x10, 0x00, 0xFF, 0x00, 0x00, 1, 0x00000400, {(x), (y), 2048, 2048}}, \
    {DRP, FACTION_ALLY, 1, 4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0, 0x00000000, {(x), (y), 2048, 2048}}, \
  }

// 0x08336414..0x083364d4
static const struct Collision sCollisions[5][2] = {
    HITBOX(-768, 0),
    HITBOX(-768, 0),
    HITBOX(-512, -512),
    HITBOX(-512, 512),
    HITBOX(0, -768),
};

#endif  // AP
