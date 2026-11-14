#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "entity.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "script.h"
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
  Zero 2's boss 13, Phoenix Magnion. Boss of the Power Room, in the room of the last reactor.
  work0:
    0 Magnion
    2 copy of him in the four-way attack
    3 his shadow in the dash
    4 his top half once cut
  work1: room, how many lava columns erupt
*/

struct Magnion {
  OBJECT_HDR;
  u8 next;           // 0xB4
  u8 spot;           // 0xB5
  u16 nearTime;      // 0xB6
  u16 idleTime;      // 0xB8
  u8 lastAttack;     // 0xBA
  u8 _bb;
  u32 signal;        // 0xBC, read by his afterimages and rings
  s32 centerX;       // 0xC0
  u8 arrival;        // 0xC4
  u8 slot;           // 0xC5
  bool8 hit;         // 0xC6
  u8 blink;          // 0xC7
  struct Zero* zero;    // 0xC8
  struct Zero* struck;  // 0xCC
  s32 groundY;       // 0xD0
  u8 hitFromRight;   // 0xD4
  bool8 stunned;     // 0xD5
  s16 eruptTime;     // 0xD6
  u8 eruptGap;       // 0xD8
  u8 erupted;        // 0xD9
  u8 rand;           // 0xDA
  u8 attack;         // 0xDB
  s32 homeX;         // 0xDC
  s32 homeY;         // 0xE0
};
static_assert(sizeof(struct Magnion) == sizeof(struct Boss));

#define TRAIL (1 << 0)
#define VANISH (1 << 1)
#define RINGS_FLASH (1 << 3)
#define RINGS_HIDDEN (1 << 4)
#define CUT (1 << 5)
#define RINGS_LOW (1 << 6)
#define PILLAR_UP (1 << 2)

#define MAG(n) MOTION(DM209_Z2_MAGNION, (n))
#define SPARK(n) MOTION(AP_SHEET_Z2_MAGNION_SPARK, (n))
#define FACING_RIGHT(s) (((s)->flags & X_FLIP) != 0)

enum {
  MAGNION_INTRO,
  MAGNION_IDLE,
  MAGNION_VANISH,
  MAGNION_APPEAR,
  MAGNION_SHOOT,
  MAGNION_LAND,
  MAGNION_CROUCH,
  MAGNION_POUNCE,
  MAGNION_RISE,
  MAGNION_RECOVER,
  MAGNION_CARRY,
  MAGNION_BLAST,
  MAGNION_FLY_OFF,
  MAGNION_FOUR_WAY,
  MAGNION_BACK_OFF,
  MAGNION_DASH,
  MAGNION_SHADOW,
  MAGNION_TAUNT,
  MAGNION_BEHIND,
  MAGNION_LUNGE,
  MAGNION_FOLLOW_UP,
  MAGNION_PILLAR,
  MAGNION_TOSS,
  MAGNION_FLINCH,
  MAGNION_HALF,
};

static const struct Collision sStand[1], sBody[1], sShoot[2], sPounce[2], sCrouch[2], sPounceSide[2],
    sCrouchSide[2], sCarry[2], sFourWay[2], sDash[2], sLunge[1], sPillar[1], sToss[1], sHidden[1];
static const Coords32 sElementCoord = {0, -PIXEL(24)};

// After his window, 512 on palette 4. Blast loads over the sparks
static const struct PreloadEntity sFireSheet = {AP_SHEET_Z2_MAGNION_FIRE, 0, 664, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSparkSheet = {AP_SHEET_Z2_MAGNION_SPARK, 0, 728, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sBlastSheet = {AP_SHEET_Z2_MAGNION_BLAST, 0, 728, 7, 0, AP_PRELOAD_SHEET, 0};

static void Magnion_Init(struct Magnion* p);
static void Magnion_Update(struct Magnion* p);
static void Magnion_Die(struct Magnion* p);
static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED);
static void createAfterimages(struct Entity* boss, const Coords32* at);
static void createRings(struct Entity* boss);
static struct Entity* createColumn(struct Entity* below, const Coords32* at, u8 part);
static void createSpreadShot(struct Entity* boss, const Coords32* at, u8 angle, u8 n);
static void createOrbit(const Coords32* at, u8 n);
static void createFireball(struct Entity* boss, const Coords32* at, bool8 right, u8 angle);

// clang-format off
const BossRoutine gApZ2MagnionRoutine = {
    [ENTITY_INIT] =      (BossFunc)Magnion_Init,
    [ENTITY_UPDATE] =    (BossFunc)Magnion_Update,
    [ENTITY_DIE] =       (BossFunc)Magnion_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 animEnded(struct Entity* s) { return s->motion.state == ANIM_END; }
static bool8 loopEnded(struct Entity* s) { return (u8)(s->motion.state - ANIM_END) <= 1; }

static void faceZero(struct Magnion* p) { SET_XFLIP(p, (pZero2->s).coord.x - (p->s).coord.x > 0); }

// A copy or his shadow leaves at once
static void disappear(struct Magnion* p) {
  struct Entity* s = &p->s;
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
}

static void reappear(struct Magnion* p) {
  setMode(&p->s, MAGNION_APPEAR);
  p->arrival = 4;
}

static void draw(struct Magnion* p) {
  if ((p->s).work[0] == 2) {
    FUN_0801779c(&p->s);
  } else {
    UpdateSpriteAnimation(p);
  }
}

// Stands in for Zero 2's thrown state, 0x08022ea8
static void throwZero(struct Zero* z, s32 dx, s32 dy) {
  GotoMotion(&z->s, MOTION(DM004_ZERO_AIR, 4), 2, 1);
  (z->s).mode[1] = ZERO_AIR, (z->s).mode[2] = 2, (z->s).mode[3] = 1;
  (z->unk_b4).blownSpeed = dx;
  (z->s).d.y = dy;
}

static bool8 alive(struct Zero* z) { return z != NULL && !((z->body).status & BODY_STATUS_DEAD) && (z->body).hp != 0; }

// 0x08057cf4
static void Magnion_Init(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u8 sFirstMode[5] = {MAGNION_INTRO, MAGNION_INTRO, MAGNION_FOUR_WAY, MAGNION_SHADOW, MAGNION_HALF};
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sFirstMode[s->work[0]];
  s->flags |= FLIPABLE;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->flags |= DISPLAY;
  ResetBossBody((struct Boss*)p, sBody, 64);
  (p->body).fn = onHit;
  p->signal = 0;
  p->idleTime = 0;
  p->lastAttack = 0xFF;
  p->_bb = 0;
  p->arrival = 0;
  p->eruptTime = 1800;
  if (s->work[0] == 2) {
    p->arrival = 3;
  } else {
    ApLoadSheet(&sFireSheet);
    ApLoadSheet(&sSparkSheet);
  }
  p->groundY = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->work[0] != 4) s->coord.y = p->groundY;
  p->centerX = (FUN_0800a31c(s->coord.x, s->coord.y) + FUN_0800a22c(s->coord.x, s->coord.y)) >> 1;
  s->unk_2c = NULL;
  Magnion_Update(p);
}

// 0x08057f88
static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Magnion* p = (struct Magnion*)body->parent;
  struct Entity* other = (body->enemy)->parent;
  if (body->hitboxFlags & BODY_STATUS_BINDING) p->zero = (struct Zero*)other;
  if (body->hitboxFlags & BODY_STATUS_B2) p->struck = (struct Zero*)other;
  if (!(body->hitboxFlags & BODY_STATUS_WHITE)) return;
  if (body->elemented == 1) (p->s).unk_2c = ApplyElementEffect(9, (Object*)p, &sElementCoord);
  p->hitFromRight = (p->s).coord.x < other->coord.x;
  if (body->hitboxFlags & BODY_STATUS_SLASHED) {
    p->signal |= CUT;
  } else {
    p->signal &= ~CUT;
  }
}

// 0x08057ab0
static void cry(struct Magnion* p) {
  static const u8 sCries[4][4] = {
      {140, 141, 142, 142}, {138, 138, 139, 139}, {136, 137, 138, 139}, {136, 136, 137, 137}};
  u8 level = (p->body).hp * 6 / 64;
  if (level > 3) level = 3;
  PlaySound(SE_Z2_MAGNION_CRY + sCries[level][RANDOM(RNG_0202f388) & 3] - 136);
}

// 0x08057bec: every 1800 frames, sooner while Zero keeps off the middle
static void erupt(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const s16 sColumns[4] = {2, 4, 7, 9};
  static const s16 sColumnX[4][9] = {
      {16, 400}, {16, 112, 304, 400}, {16, 80, 144, 208, 272, 336, 400}, {16, 64, 112, 160, 208, 256, 304, 352, 400}};
  Coords32 at;
  struct Entity* part;
  if (p->eruptTime > 0) {
    p->eruptGap = 0;
    p->erupted = 0;
    if (--p->eruptTime < 180) {
      AppendQuake(3, &s->coord);
    } else if ((u32)((pZero2->s).coord.x - p->centerX + PIXEL(192)) > PIXEL(384) - 1) {
      p->eruptTime -= 7;
    }
    return;
  }
  if (p->eruptGap != 0) {
    p->eruptGap--;
    return;
  }
  at.x = p->centerX - PIXEL(208) + PIXEL(sColumnX[s->work[1]][p->erupted]);
  at.y = p->groundY + PIXEL(32);
  PlaySound(SE_Z2_MAGNION_ERUPT);
  part = createColumn(NULL, &at, 0);
  part = createColumn(part, NULL, 1);
  part = createColumn(part, NULL, 2);
  createColumn(part, NULL, 3);
  p->eruptGap = 16;
  if (++p->erupted >= sColumns[s->work[1]]) p->eruptTime = 1800;
}

static const BossFunc sTriggers[25], sStates[25];

// 0x08057e68
static void Magnion_Update(struct Magnion* p) {
  struct Entity* s = &p->s;
  p->rand = RANDOM(RNG_0202f388);
  if ((u8)(s->work[0] - 2) > 2) {
    if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
        !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
      SET_BOSS_ROUTINE(p, ENTITY_DIE);
      s->mode[1] = (p->signal & CUT) ? 1 : 0;
      s->mode[2] = 0;
      Magnion_Die(p);
      return;
    }
    if (!(gStageRun.vm.active & VM_ACTIVE)) erupt(p);
  }
  if (s->mode[1] != MAGNION_INTRO && p->idleTime <= 5399) p->idleTime++;
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  sTriggers[s->mode[1]]((struct Boss*)p);
  sStates[s->mode[1]]((struct Boss*)p);
}

static void nothing(struct Magnion* p UNUSED) {}

// 0x08058490: never the same attack twice running
static void pickAttack(struct Magnion* p) {
  static const u8 sAttacks[6] = {MAGNION_SHOOT, MAGNION_CROUCH, MAGNION_FOUR_WAY, MAGNION_IDLE, MAGNION_BACK_OFF, MAGNION_TAUNT};
  static const u8 sFirst[6] = {MAGNION_VANISH, MAGNION_VANISH, MAGNION_VANISH, MAGNION_VANISH, MAGNION_BACK_OFF, MAGNION_TAUNT};
  u8 n = (gScore.total->rank > 4 && (p->body).hp < 32) ? 6 : 5;
  u8 r;
  do {
    r = RANDOM(RNG_0202f388) % n;
    if (r == 3) r = 4;
    p->attack = sAttacks[r];
    (p->s).mode[1] = sFirst[r];
  } while (p->lastAttack == p->attack);
  p->lastAttack = p->attack;
  (p->s).mode[2] = 0;
}

// 0x08058518: Zero near, a shot close, or 90 seconds
static void idleTrigger(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  struct Entity* shot;
  if ((u32)(z->coord.x - s->coord.x + PIXEL(64)) <= PIXEL(128) - 1 &&
      (u32)(z->coord.y - s->coord.y + PIXEL(64)) <= PIXEL(128) - 1) {
    if (++p->nearTime > 30) {
      pickAttack(p);
      p->nearTime = 0;
      return;
    }
  } else {
    p->nearTime = 0;
  }
  shot = GetNearestEntity(gWeaponHeaderPtr, &s->coord);
  if (shot != NULL && (u32)(shot->coord.x - s->coord.x + PIXEL(96)) <= PIXEL(192) - 1 &&
      (u32)(shot->coord.y - s->coord.y + PIXEL(96)) <= PIXEL(192) - 1) {
    pickAttack(p);
  } else if (p->idleTime == 5400) {
    pickAttack(p);
  }
}

// 0x08058020
static void Magnion_Intro(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const s16 sPath[10][2] = {{-238, -75}, {-225, -159}, {-186, -204}, {-99, -155}, {-90, -67},
                                   {-161, 0},   {-209, -72},  {-174, -190}, {-80, -160}, {-80, -140}};
  static const u16 sRise[4][2] = {{MAG(0x29), 8}, {MAG(0x2A), 1}, {MAG(0x35), 1}, {MAG(0x36), 3}};
  static const u16 sLand[3] = {MAG(0x37), MAG(0x2B), MAG(0x00)};
  struct Camera* cam = &gStageRun.vm.camera;
  Coords32 to;
  s32 dx, dy, ux, uy;
  u32 len;
  s32 pushout;
  switch (s->mode[2]) {
    case 0:
      s->spr.oam.priority = 1;
      s->flags &= ~DISPLAY;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(24);
      if (s->work[0] == 0 || s->work[0] == 5) {
        SET_XFLIP(p, FALSE);
        s->coord.x = cam->viewport.x + 0x97FF;
      } else {
        SET_XFLIP(p, TRUE);
        s->coord.x = cam->viewport.x - PIXEL(152);
      }
      p->homeX = s->coord.x;
      p->homeY = s->coord.y;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (!(s->scriptEntity->flags & 1)) break;
      if (s->work[0] <= 1) {
        s->mode[2]++;
        break;
      }
      s->flags |= DISPLAY;
      s->work[2] = 1;
      createRings(s);
      s->coord.x = p->homeX + (s->work[0] == 5 ? PIXEL(sPath[9][0]) : -PIXEL(sPath[9][0]));
      s->coord.y = p->homeY + PIXEL(sPath[9][1]);
      s->mode[2] = 5;
      break;
    case 2:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, MAG(0x27));
      s->d.x = s->d.y = 0;
      s->work[2] = s->work[3] = 0;
      createAfterimages(s, &s->coord);
      createRings(s);
      s->mode[2]++;
      // fallthrough
    case 3:
      to.x = p->homeX + (s->work[0] == 0 ? PIXEL(sPath[s->work[2]][0]) : -PIXEL(sPath[s->work[2]][0]));
      to.y = p->homeY + PIXEL(sPath[s->work[2]][1]);
      dx = to.x - s->coord.x;
      dy = to.y - s->coord.y;
      len = (u16)Sqrt((u32)(dx * dx + dy * dy));
      ux = len ? (dx << 8) / (s32)len : 0;
      uy = len ? (dy << 8) / (s32)len : 0;
      s->unk_coord.x = ux;
      s->unk_coord.y = uy;
      if (len > 0x400) len = 0x400;
      s->d.x += (ux - s->d.x) / 16;
      s->d.y += (uy - s->d.y) / 16;
      s->coord.x += s->d.x * (s32)len / 256;
      s->coord.y += s->d.y * (s32)len / 256;
      s->work[3] += 8;
      if (s->work[3] == 0) {
        s->work[2]++;
        if (s->work[2] == 1 || s->work[2] == 6) PlaySound(SE_Z2_FEFNIR_BUBBLE_GROW);
        if (s->work[2] == 10) s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      break;
    case 4:
      p->signal |= TRAIL;
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 5:
      if (s->work[2] == 2) {
        PlaySound(SE_Z2_MAGNION_FLARE);
        p->signal |= RINGS_FLASH;
      }
      if (s->work[2] == 1) {
        p->signal |= RINGS_HIDDEN;
      } else {
        p->signal &= ~RINGS_HIDDEN;
      }
      SetSpriteAnimation(p, sRise[s->work[2]][0]);
      s->work[3] = sRise[s->work[2]][1];
      s->mode[2]++;
      // fallthrough
    case 6:
      UpdateSpriteAnimation(p);
      if (loopEnded(s) && --s->work[3] == 0) {
        if (++s->work[2] == 4) {
          s->mode[2]++;
        } else {
          s->mode[2] = 5;
        }
      }
      break;
    case 7:
      s->d.y = 0;
      s->mode[2]++;
      // fallthrough
    case 8:
      s->d.y += 8;
      if (s->d.y > 0x180) s->d.y = 0x180;
      s->coord.y += s->d.y;
      pushout = PushoutToUp1(s->coord.x, s->coord.y + PIXEL(80));
      if (pushout < 0) {
        s->mode[2]++;
        s->coord.y += pushout;
      }
      UpdateSpriteAnimation(p);
      break;
    case 9:
      s->d.y -= 8;
      if (s->d.y == 0) s->mode[2]++;
      s->coord.y += s->d.y;
      UpdateSpriteAnimation(p);
      break;
    case 10:
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 11:
      SetSpriteAnimation(p, sLand[s->work[2]]);
      if (s->work[2] == 1) {
        p->signal |= VANISH;
        s->coord.y += PIXEL(36);
      }
      s->mode[2]++;
      // fallthrough
    case 12:
      UpdateSpriteAnimation(p);
      if (s->work[2] > 1 && !(gStageRun.vm.active & VM_ACTIVE)) {
        s->spr.oam.priority = 2;
        s->mode[1] = MAGNION_IDLE;
        s->mode[2] = 1;
      }
      if (loopEnded(s)) {
        if (++s->work[2] > 2) {
          s->work[2] = 2;
        } else {
          s->mode[2] = 11;
        }
      }
      break;
  }
}

// 0x080585c8
static void Magnion_Idle(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, MAG(0));
      s->mode[2]++;
      // fallthrough
    case 1:
      SetDDP(&p->body, sStand);
      p->nearTime = 0;
      s->mode[2]++;
      // fallthrough
    case 2:
      faceZero(p);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08058678
static void Magnion_Vanish(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      if (p->arrival != 4) cry(p);
      SetDDP(&p->body, sBody);
      SetSpriteAnimation(p, MAG(9));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (!animEnded(s)) break;
      if (s->work[0] == 2) {
        disappear(p);
      } else {
        setMode(s, MAGNION_APPEAR);
      }
      break;
  }
}

static void createCopy(struct Entity* boss, u8 slot);

// 0x08058714
static void Magnion_Appear(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u8 sNext[4] = {MAGNION_SHOOT, MAGNION_CROUCH, MAGNION_FOUR_WAY, MAGNION_IDLE};
  static const s32 sCopySpots[4][2] = {{96, 48}, {-96, 48}, {48, -16}, {-48, -16}};
  struct Camera* cam = &gStageRun.vm.camera;
  s32 spots[3];
  u8 kind, i, tries, slot = 0;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_MAGNION_APPEAR);
      s->flags |= DISPLAY;
      SetDDP(&p->body, sBody);
      if (p->arrival != 0) {
        kind = p->arrival - 1;
        if (kind == 2) slot = p->slot;
        p->arrival = 0;
      } else {
        kind = 0;
        if (p->attack == MAGNION_CROUCH) kind = 1;
        if (p->attack == MAGNION_FOUR_WAY) kind = 2;
        if (p->attack == MAGNION_IDLE) kind = 3;
        if (kind == 2) {
          slot = RANDOM(RNG_0202f388) & 3;
          for (i = 0; i <= 3; i++) {
            if (i != slot) createCopy(s, i);
          }
        }
      }
      p->next = sNext[kind];
      switch (kind) {
        case 0:
          s->coord.x = p->centerX;
          s->coord.y = p->groundY - PIXEL(48);
          break;
        case 1:
          s->coord.y = p->groundY - PIXEL(64);
          spots[0] = (pZero2->s).coord.x;
          spots[1] = spots[0] + PIXEL(88);
          spots[2] = spots[0] - PIXEL(88);
          i = RANDOM(RNG_0202f388) % 3;
          s->coord.x = spots[i];
          for (tries = 0; (u32)(s->coord.x - p->centerX + PIXEL(208)) > 0x19FFF;) {
            i = (i + 1) % 3;
            s->coord.x = spots[i];
            if (++tries > 2) break;
          }
          p->spot = i;
          break;
        case 2:
          SET_XFLIP(p, slot & 1);
          s->coord.x = cam->viewport.x + PIXEL(sCopySpots[slot][0]);
          s->coord.y = cam->viewport.y + PIXEL(sCopySpots[slot][1]);
          p->slot = slot;
          break;
        case 3:
          s->coord.x = p->centerX;
          s->coord.y = p->groundY - PIXEL(8);
          break;
      }
      SetDDP(&p->body, sBody);
      SetSpriteAnimation(p, MAG(0x0A));
      s->mode[2]++;
      // fallthrough
    case 1:
      draw(p);
      if (animEnded(s)) setMode(s, p->next);
      break;
  }
}

static void flinchOnHit(struct Magnion* p) {
  if (!((p->body).status & BODY_STATUS_WHITE)) return;
  p->stunned = FALSE;
  setMode(&p->s, MAGNION_FLINCH);
}

// 0x080589ec: three volleys of six shots
static void Magnion_Shoot(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u16 sAnims[6] = {MAG(0x04), MAG(0x05), MAG(0x06), MAG(0x07), MAG(0x08), MAG(0x03)};
  static const s16 sAt[18][2] = {{-22, -58}, {22, -58}, {-17, -46}, {17, -46}, {-22, -46}, {22, -46},
                                 {-39, -35}, {38, -35}, {-31, -36}, {30, -36}, {-20, -36}, {19, -36},
                                 {-14, -64}, {13, -64}, {-20, -57}, {19, -57}, {-20, -44}, {19, -44}};
  static const u8 sAngles[18] = {120, 8, 108, 20, 90, 38, 108, 20, 90, 38, 70, 58, 148, 236, 128, 0, 96, 32};
  static const u8 sVolleyFrame[4] = {6, 7, 0, 6};
  Coords32 at;
  u8 i, first;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sShoot);
      s->work[2] = 0;
      s->unk_coord.x = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      SetSpriteAnimation(p, sAnims[s->work[2]]);
      s->work[3] = 0;
      s->mode[2]++;
      // fallthrough
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->work[2] == 0 || s->work[2] == 1 || s->work[2] == 3) && s->motion.cmdIdx == sVolleyFrame[s->work[2]] &&
          !s->work[3]) {
        s->work[3] = 1;
        first = s->work[2] == 0 ? 0 : (s->work[2] == 1 ? 6 : 12);
        for (i = 0; i < 6; i++) {
          at.x = s->coord.x + PIXEL(sAt[first + i][0]);
          at.y = s->coord.y + PIXEL(sAt[first + i][1]);
          createSpreadShot(s, &at, sAngles[first + i], i);
        }
      }
      if (!loopEnded(s)) break;
      if (s->work[2] == 0 && s->unk_coord.x <= 29) {
        s->unk_coord.x++;
      } else if (++s->work[2] == 6) {
        setMode(s, MAGNION_LAND);
      } else {
        s->mode[2] = 1;
      }
      break;
  }
}

// 0x08058be0
static void Magnion_Land(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, MAG(0));
      s->d.y = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      faceZero(p);
      s->d.y += 16;
      if (s->d.y > 0x100) s->d.y = 0x100;
      s->coord.y += s->d.y;
      if (PushoutToUp1(s->coord.x, s->coord.y + PIXEL(16)) < 0) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      faceZero(p);
      s->d.y -= 16;
      if (s->d.y == 0) setMode(s, MAGNION_IDLE);
      s->coord.y += s->d.y;
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08058d0c
static void Magnion_Crouch(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u16 sAnims[3] = {MAG(0x0B), MAG(0x10), MAG(0x10)};
  switch (s->mode[2]) {
    case 0:
      if (p->spot != 0) {
        SET_XFLIP(p, p->spot - 1);
        SetDDP(&p->body, sCrouchSide);
      } else {
        SetDDP(&p->body, sCrouch);
      }
      SetSpriteAnimation(p, sAnims[p->spot]);
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (animEnded(s)) setMode(s, MAGNION_POUNCE);
      break;
  }
}

// 0x08058dbc: a hold catches Zero
static void pounceTrigger(struct Magnion* p) {
  if ((p->body).status & BODY_STATUS_WHITE) {
    p->stunned = FALSE;
    setMode(&p->s, MAGNION_FLINCH);
  } else if ((p->body).status & BODY_STATUS_BINDING) {
    setMode(&p->s, MAGNION_CARRY);
  }
}

// 0x08058df0
static void Magnion_Pounce(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u16 sAnims[3] = {MAG(0x0C), MAG(0x11), MAG(0x11)};
  static const s16 sDx[3] = {0, -0x500, 0x500};
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, p->spot == 0 ? sPounce : sPounceSide);
      SetSpriteAnimation(p, sAnims[p->spot]);
      s->d.x = sDx[p->spot];
      s->d.y = 0x500;
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      s->coord.x += s->d.x;
      s->d.y -= 48;
      if (s->d.y < 0) s->d.y = 0;
      s->coord.y += s->d.y;
      if (p->groundY - 8 - s->coord.y < 0) setMode(s, MAGNION_RISE);
      break;
  }
}

// 0x08058e9c
static void Magnion_Rise(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Camera* cam = &gStageRun.vm.camera;
  static const u16 sAnims[3] = {MAG(0x0D), MAG(0x12), MAG(0x12)};
  static const u16 sAirAnims[3] = {MAG(0x0E), MAG(0x13), MAG(0x13)};
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, p->spot == 0 ? sCrouch : sPounceSide);
      SetSpriteAnimation(p, sAnims[p->spot]);
      s->d.y = 0;
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      UpdateSpriteAnimation(p);
      if (animEnded(s)) {
        s->work[2] = 1;
        SetSpriteAnimation(p, sAirAnims[p->spot]);
        UpdateSpriteAnimation(p);
      }
      if (p->spot == 0) {
        if (p->groundY - s->coord.y > PIXEL(32)) s->mode[2]++;
        if (s->work[2]) {
          s->d.y -= 32;
          s->coord.y += s->d.y;
        }
      } else {
        if (Camera_GetDistance(cam, &s->coord) > PIXEL(96)) reappear(p);
        if (s->work[2]) {
          s->d.y -= 16;
          s->coord.y += s->d.y;
        }
      }
      break;
    case 2:
      s->d.y += 64;
      if (s->d.y > 0) {
        s->d.y = 0;
        setMode(s, MAGNION_RECOVER);
      }
      s->coord.y += s->d.y;
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08058fd0
static void Magnion_Recover(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, MAG(0x0F));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (animEnded(s)) {
        setMode(s, MAGNION_VANISH);
        p->arrival = 4;
      }
      break;
  }
}

// 0x08059018: carries Zero to the middle of the room
static void Magnion_Carry(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Zero* z = p->zero;
  s32 tx, ty, ux, uy;
  u32 len;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_CARRIER_GRAB);
      SetDDP(&p->body, sCarry);
      SetSpriteAnimation(p, MAG(0x38));
      s->d.x = s->d.y = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      (z->s).coord.x = s->coord.x;
      if ((z->s).coord.y - s->coord.y > PIXEL(28)) (z->s).coord.y = s->coord.y + PIXEL(28);
      tx = p->centerX - s->coord.x;
      ty = p->groundY - PIXEL(96) - s->coord.y;
      len = (u16)Sqrt((u32)(tx * tx + ty * ty));
      ux = len ? (tx << 8) / (s32)len : 0;
      uy = len ? (ty << 8) / (s32)len : 0;
      s->d.x += (ux - s->d.x) / 16;
      s->d.y += (uy - s->d.y) / 16;
      if (len > 0x300) len = 0x300;
      if (len < 64) setMode(s, MAGNION_BLAST);
      s->coord.x += s->d.x * (s32)len / 256;
      s->coord.y += s->d.y * (s32)len / 256;
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08059158: four orbits, then Zero thrown clear
static void Magnion_Blast(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Zero* z = p->zero;
  switch (s->mode[2]) {
    case 0:
      ApLoadSheet(&sBlastSheet);
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      createOrbit(&s->coord, s->work[2]);
      s->work[3] = ++s->work[2] == 4 ? 90 : 30;
      s->mode[2]++;
      // fallthrough
    case 2:
      s->work[3]--;
      if (s->work[2] == 4) {
        if (s->work[3] == 15) SetDDP(&p->body, sBody);
        if (s->work[3] == 14 && alive(z)) throwZero(z, -0x300, -0x300);
      }
      if (s->work[3] == 0) {
        if (s->work[2] == 4) {
          setMode(s, MAGNION_FLY_OFF);
        } else {
          s->mode[2] = 1;
        }
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0805927c
static void Magnion_FlyOff(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sBody);
      s->d.y = 0;
      SetSpriteAnimation(p, MAG(0x0E));
      s->mode[2]++;
      // fallthrough
    case 1:
      s->d.y -= 48;
      if (s->d.y < -0x200) s->d.y = -0x200;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(96)) {
        ApLoadSheet(&sSparkSheet);
        setMode(s, MAGNION_VANISH);
        p->arrival = 4;
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08059348
static void fourWayTrigger(struct Magnion* p) {
  struct Entity* s = &p->s;
  if (!((p->body).status & BODY_STATUS_WHITE)) return;
  if (s->work[0] == 2) {
    p->hit = TRUE;
  } else if (s->work[2] <= 2) {
    s->flags |= DISPLAY;
    setMode(s, MAGNION_FLINCH);
    p->stunned = FALSE;
  }
}

// 0x08059388: he and three copies, only he takes hits
static void Magnion_FourWay(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  static const u16 sAnims[4] = {MAG(0x14), MAG(0x15), MAG(0x16), MAG(0x17)};
  static const u8 sAngles[2] = {55, 18};
  bool8 copy = s->work[0] == 2;
  if (copy && (boss->mode[0] > ENTITY_UPDATE || *(u16*)boss->mode == ((MAGNION_FLINCH << 8) | ENTITY_UPDATE))) {
    disappear(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      if (copy) {
        EXIT_BODY(p);
      } else {
        SetDDP(&p->body, sFourWay);
      }
      s->work[2] = 0;
      p->hit = FALSE;
      p->blink = p->slot;
      s->mode[2]++;
      // fallthrough
    case 1:
      SetSpriteAnimation(p, sAnims[s->work[2]]);
      s->mode[2]++;
      // fallthrough
    case 2:
      p->blink++;
      draw(p);
      if (!animEnded(s)) break;
      s->work[2]++;
      if (s->work[2] == 3) {
        if (copy) {
          createFireball(boss, &s->coord, FACING_RIGHT(s), sAngles[p->slot > 1]);
        } else {
          PlaySound(SE_Z2_MAGNION_FIREBALL);
          createFireball(s, &s->coord, FACING_RIGHT(s), sAngles[p->slot > 1]);
        }
        s->work[3] = 38;
        s->mode[2]++;
        return;
      }
      if (s->work[2] == 4) {
        if (copy) {
          disappear(p);
          break;
        }
        PlaySound(SE_Z2_MAGNION_APPEAR);
        setMode(s, MAGNION_VANISH);
        p->arrival = 4;
        s->flags |= DISPLAY;
        return;
      }
      s->mode[2] = 1;
      break;
    case 3:
      p->blink++;
      if (--s->work[3] == 0) s->mode[2] = 1;
      draw(p);
      break;
  }
  if (p->blink & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  if (p->blink - p->slot <= 5 && !copy) s->flags &= ~DISPLAY;
}

// 0x08057b90
static void createCopy(struct Entity* boss, u8 slot) {
  struct Entity* p = AllocEntityLast(gBossHeaderPtr);
  if (p != NULL) {
    INIT_BOSS_ROUTINE(p, BOSS_Z2_MAGNION);
    p->work[0] = 2;
    p->unk_28 = boss;
    ((struct Magnion*)p)->slot = slot;
  }
}

// 0x08059620: backs off the screen
static void Magnion_BackOff(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      cry(p);
      SetDDP(&p->body, sStand);
      faceZero(p);
      SetSpriteAnimation(p, MAG(0x1A));
      s->d.x = FACING_RIGHT(s) ? -0x500 : 0x500;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      s->flags &= ~DISPLAY;
      SetDDP(&p->body, sHidden);
      s->work[2] = 30;
      s->mode[2]++;
      // fallthrough
    case 3:
      if (--s->work[2] == 0) setMode(s, MAGNION_DASH);
      break;
  }
}

// 0x080595e0: thunder stops him mid-dash
static void dashTrigger(struct Magnion* p) {
  if (((p->body).status & BODY_STATUS_WHITE) && (p->body).elemented == 1) {
    p->signal |= VANISH;
    p->stunned = TRUE;
    setMode(&p->s, MAGNION_FLINCH);
  }
}

static void createShadow(struct Entity* boss);

// 0x0805973c: across the screen at Zero's height
static void Magnion_Dash(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Camera* cam = &gStageRun.vm.camera;
  s32 top;
  switch (s->mode[2]) {
    case 0:
      s->work[0] = 7;
      PlaySound(SE_Z2_SIGNALOID_FLAME);
      SetDDP(&p->body, sDash);
      createRings(s);
      p->signal = (p->signal & ~(RINGS_LOW | VANISH)) | RINGS_FLASH;
      createShadow(s);
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, MAG(0x1B));
      s->d.x = FACING_RIGHT(s) ? 0x600 : -0x600;
      s->coord.x = FACING_RIGHT(s) ? cam->viewport.x - PIXEL(184) : cam->viewport.x + 0xB7FF;
      s->d.y = 0;
      top = s->coord.y - PIXEL(16);
      s->coord.y = (pZero2->s).coord.y;
      if (s->coord.y > top) s->coord.y = top;
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (s->work[2] <= 9) {
        s->work[2]++;
      } else {
        s->d.y -= 4;
        if (Camera_GetDistance(cam, &s->coord) > PIXEL(64)) {
          s->work[0] = 0;
          p->signal |= VANISH;
          reappear(p);
        }
      }
      s->coord.y += s->d.y;
      s->coord.x += s->d.x;
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08057b34
static void createShadow(struct Entity* boss) {
  struct Entity* p = AllocEntityLast(gBossHeaderPtr);
  if (p != NULL) {
    INIT_BOSS_ROUTINE(p, BOSS_Z2_MAGNION);
    p->work[0] = 3;
    p->unk_28 = boss;
    p->coord = boss->coord;
  }
}

// 0x08059870
static void Magnion_Shadow(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (boss->mode[0] > ENTITY_UPDATE) disappear(p);
  switch (s->mode[2]) {
    case 0:
      s->flags2 |= WHITE_PAINTABLE;
      s->invincibleID = boss->uniqueID;
      EXIT_BODY(p);
      InitNonAffineMotion(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, MAG(0x1C));
      SET_XFLIP(p, FACING_RIGHT(boss));
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord = boss->coord;
      if (*(u16*)boss->mode != ((MAGNION_DASH << 8) | ENTITY_UPDATE)) disappear(p);
      break;
  }
  FUN_0801779c(s);
}

// 0x08059a10
static void Magnion_Taunt(struct Magnion* p) {
  struct Entity* s = &p->s;
  static const u8 sRounds[16] = {3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6};
  switch (s->mode[2]) {
    case 0:
      SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
      s->work[2] = sRounds[RANDOM(RNG_0202f388) & 15];
      s->mode[2]++;
      // fallthrough
    case 1:
      SetDDP(&p->body, sBody);
      SetSpriteAnimation(p, MAG(0x1F));
      s->mode[2]++;
      // fallthrough
    case 2:
      UpdateSpriteAnimation(p);
      if (!animEnded(s)) break;
      if (--s->work[2] == 0) {
        reappear(p);
      } else {
        setMode(s, MAGNION_BEHIND);
      }
      break;
  }
}

// 0x08059b1c
static void Magnion_Behind(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sBody);
      s->flags &= ~DISPLAY;
      s->work[3] = 20;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (--s->work[3] == 0) s->mode[2]++;
      break;
    case 2:
      s->flags |= DISPLAY;
      if (z->flags & X_FLIP) {
        s->coord.x = z->coord.x - PIXEL(64);
        SET_XFLIP(p, TRUE);
      } else {
        s->coord.x = z->coord.x + PIXEL(64);
        SET_XFLIP(p, FALSE);
      }
      s->coord.y = z->coord.y - PIXEL(8);
      SetSpriteAnimation(p, MAG(0x1D));
      s->mode[2]++;
      // fallthrough
    case 3:
      UpdateSpriteAnimation(p);
      if (animEnded(s)) setMode(s, MAGNION_LUNGE);
      break;
  }
}

// 0x0805999c: a claw that lands knocks Zero up
static void lungeTrigger(struct Magnion* p) {
  struct Zero* z = p->struck;
  if (!((p->body).status & BODY_STATUS_B2)) return;
  if (alive(z)) throwZero(z, FACING_RIGHT(&p->s) ? 0x1E0 : -0x1E0, -0x600);
  setMode(&p->s, MAGNION_FOLLOW_UP);
}

// 0x08059c18
static void Magnion_Lunge(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sLunge);
      SetSpriteAnimation(p, MAG(0x1E));
      s->unk_coord.y = 0;
      s->unk_coord.x = FACING_RIGHT(s) ? 48 : -48;
      s->d.x = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->d.x += s->unk_coord.x;
      if (s->d.x > 0x3A0) s->d.x = 0x3A0;
      if (s->d.x < -0x3A0) s->d.x = -0x3A0;
      s->unk_coord.y += s->d.x < 0 ? -s->d.x : s->d.x;
      if (s->unk_coord.y > PIXEL(192)) {
        s->mode[1] = MAGNION_TAUNT;
        s->mode[2] = 1;
      }
      s->coord.x += s->d.x;
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08059cb4
static void Magnion_FollowUp(struct Magnion* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, MAG(0x1F));
      SetDDP(&p->body, sBody);
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (animEnded(s)) s->flags &= ~DISPLAY;
      if (p->groundY - (pZero2->s).coord.y <= 0xAFFF && (p->struck->s).d.y > 0) setMode(s, MAGNION_PILLAR);
      break;
  }
}

// 0x08059d68: a pillar of fire under the falling Zero
static void Magnion_Pillar(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  switch (s->mode[2]) {
    case 0:
      s->coord.x = FACING_RIGHT(s) ? z->coord.x + PIXEL(63) : z->coord.x - PIXEL(63);
      if (s->coord.x < p->centerX - PIXEL(192)) {
        s->coord.x = p->centerX - PIXEL(192);
      } else if (s->coord.x > p->centerX + PIXEL(192)) {
        s->coord.x = p->centerX + PIXEL(192);
      }
      s->coord.y = p->groundY;
      s->flags |= DISPLAY;
      SetDDP(&p->body, sBody);
      SetSpriteAnimation(p, MAG(0x20));
      s->mode[2]++;
      // fallthrough
    case 1:
      cry(p);
      UpdateSpriteAnimation(p);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 2:
      createRings(s);
      p->signal = ((p->signal | RINGS_LOW) & ~VANISH) | PILLAR_UP;
      SetDDP(&p->body, sPillar);
      s->work[2] = 60;
      SetSpriteAnimation(p, MAG(0x21));
      s->mode[2]++;
      // fallthrough
    case 3:
      if (--s->work[2] == 0) {
        p->signal |= VANISH;
        setMode(s, MAGNION_TOSS);
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08059e88
static void Magnion_Toss(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Zero* z = p->zero;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_SIGNALOID_FLAME);
      SetSpriteAnimation(p, MAG(0x22));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (animEnded(s)) {
        SetDDP(&p->body, sToss);
        s->mode[2]++;
      }
      break;
    case 2:
      if (alive(z)) throwZero(z, 0, -0x600);
      SetSpriteAnimation(p, MAG(0x23));
      s->d.y = -0x600;
      s->mode[2]++;
      // fallthrough
    case 3:
      s->coord.y += s->d.y;
      UpdateSpriteAnimation(p);
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) reappear(p);
      break;
  }
}

// 0x08059f74: knocked back, or falls stunned while the thunder lasts
static void Magnion_Flinch(struct Magnion* p) {
  struct Entity* s = &p->s;
  bool8 done;
  switch (s->mode[2]) {
    case 0:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, MAG(0x24));
      SET_XFLIP(p, p->hitFromRight);
      SetDDP(&p->body, sStand);
      s->d.x = 0x300 - p->hitFromRight * 0x600;
      s->d.y = p->stunned ? -0x500 : 0;
      s->work[2] = 20;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (p->stunned) {
        s->d.y += 64;
        if (s->d.y > 0x700) s->d.y = 0x700;
        done = s->unk_2c == NULL;
      } else {
        s->d.x = s->d.x * 232 / 256;
        done = --s->work[2] == 0;
      }
      if (done) {
        setMode(s, MAGNION_VANISH);
        p->arrival = 4;
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0805a098: the top half slides off
static void Magnion_Half(struct Magnion* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  switch (s->mode[2]) {
    case 0:
      s->flags2 |= WHITE_PAINTABLE;
      s->invincibleID = boss->uniqueID;
      EXIT_BODY(p);
      SET_XFLIP(p, FACING_RIGHT(boss));
      SetSpriteAnimation(p, MAG(0x26));
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      s->d.x = s->d.x * (s->work[3] ? 246 : 250) / 256;
      FUN_0801779c(s);
      if (boss->mode[0] == ENTITY_EXIT) disappear(p);
      break;
  }
}

// clang-format off
static const BossFunc sTriggers[25] = {
    (BossFunc)nothing, (BossFunc)idleTrigger, (BossFunc)nothing, (BossFunc)nothing,
    (BossFunc)flinchOnHit, (BossFunc)nothing, (BossFunc)flinchOnHit, (BossFunc)pounceTrigger,
    (BossFunc)pounceTrigger, (BossFunc)flinchOnHit, (BossFunc)nothing, (BossFunc)nothing,
    (BossFunc)nothing, (BossFunc)fourWayTrigger, (BossFunc)nothing, (BossFunc)dashTrigger,
    (BossFunc)nothing, (BossFunc)nothing, (BossFunc)nothing, (BossFunc)lungeTrigger,
    (BossFunc)nothing, (BossFunc)nothing, (BossFunc)nothing, (BossFunc)nothing,
    (BossFunc)nothing,
};

static const BossFunc sStates[25] = {
    (BossFunc)Magnion_Intro, (BossFunc)Magnion_Idle, (BossFunc)Magnion_Vanish, (BossFunc)Magnion_Appear,
    (BossFunc)Magnion_Shoot, (BossFunc)Magnion_Land, (BossFunc)Magnion_Crouch, (BossFunc)Magnion_Pounce,
    (BossFunc)Magnion_Rise, (BossFunc)Magnion_Recover, (BossFunc)Magnion_Carry, (BossFunc)Magnion_Blast,
    (BossFunc)Magnion_FlyOff, (BossFunc)Magnion_FourWay, (BossFunc)Magnion_BackOff, (BossFunc)Magnion_Dash,
    (BossFunc)Magnion_Shadow, (BossFunc)Magnion_Taunt, (BossFunc)Magnion_Behind, (BossFunc)Magnion_Lunge,
    (BossFunc)Magnion_FollowUp, (BossFunc)Magnion_Pillar, (BossFunc)Magnion_Toss, (BossFunc)Magnion_Flinch,
    (BossFunc)Magnion_Half,
};
// clang-format on

// 0x0805a18c, 0x0805a26c: waits for the clear scene's flag 7, then bursts
static void Magnion_Die(struct Magnion* p) {
  struct Entity* s = &p->s;
  Coords32 blastAt = {0, -PIXEL(32)};
  struct Entity* half;
  bool8 cut = s->mode[1] != 0;
  u8 side;
  switch (s->mode[2]) {
    case 0:
      s->flags |= DISPLAY;
      side = p->hitFromRight;
      if (cut) {
        PlaySound(SE_LIGHT);
        half = AllocEntityLast(gBossHeaderPtr);
        if (half != NULL) {
          INIT_BOSS_ROUTINE(half, BOSS_Z2_MAGNION);
          half->coord = s->coord;
          half->d.x = 0x100 - side * 0x200;
          half->unk_28 = s;
          half->work[0] = 4;
          half->work[3] = FACING_RIGHT(s) ^ side;
        }
        SetSpriteAnimation(p, MAG(0x25));
      } else {
        SetSpriteAnimation(p, MAG(0x24));
      }
      EXIT_BODY(p);
      if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
        gStageRun.missionStatus &= ~MISSION_STAY;
        gStageRun.missionStatus |= MISSION_SUCCESS;
      }
      s->d.x = cut ? 0x100 - side * 0x200 : s->d.x;
      s->work[2] = cut ? 50 : 80;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (cut) {
        s->coord.x += s->d.x;
        s->d.x = s->d.x * (FACING_RIGHT(s) == p->hitFromRight ? 246 : 250) / 256;
      }
      s->work[2]--;
      if (s->scriptEntity->flags & 0x80) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      s->unk_2c = CreateBossExplosion(s, &blastAt);
      s->mode[2]++;
      // fallthrough
    case 3:
      if (s->unk_2c->mode[0] > ENTITY_UPDATE) {
        gStageRun.vm.active |= VM_FLAG1;
        s->mode[2]++;
      }
      break;
  }
}

// clang-format off
// 0x0833c7c8 .. 0x0833ca68
static const struct Collision sStand[1] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x1d00, 0x1700, 0x3c00}},
};
static const struct Collision sBody[1] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
};
static const struct Collision sShoot[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1d00, 0x1700, 0x3c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1d00, 0x1700, 0x3c00}},
};
static const struct Collision sPounce[2] = {
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x23, 1, 0x00000001, {0x0, -0x400, 0x1400, 0xa00}},
    {DRP, FACTION_ENEMY, 2, 255, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x23, 0, 0x00000000, {0x0, -0x1a00, 0x1400, 0x3400}},
};
static const struct Collision sCrouch[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1a00, 0x1400, 0x3400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1a00, 0x1400, 0x3400}},
};
static const struct Collision sPounceSide[2] = {
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x23, 1, 0x00000001, {-0x400, -0x1000, 0x1400, 0x2200}},
    {DRP, FACTION_ENEMY, 2, 255, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x23, 0, 0x00000000, {-0x400, -0x1700, 0x1200, 0x2f00}},
};
static const struct Collision sCrouchSide[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {-0x400, -0x1700, 0x1200, 0x2f00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {-0x400, -0x1700, 0x1200, 0x2f00}},
};
static const struct Collision sCarry[2] = {
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x23, 1, 0x00000001, {0x0, -0x400, 0x6000, 0x6000}},
    {DRP, FACTION_ENEMY, 2, 255, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x23, 0, 0x00000000, {0x0, -0x1a00, 0x1400, 0x3400}},
};
static const struct Collision sFourWay[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1d00, 0x1700, 0x3c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1d00, 0x1700, 0x3c00}},
};
static const struct Collision sDash[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {-0x200, -0x200, 0x4400, 0x1a00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x200, 0x4400, 0x1a00}},
};
static const struct Collision sLunge[1] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x600, -0x1a00, 0x2000, 0x2400}},
};
static const struct Collision sPillar[1] = {
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0, 0x00000001, {0x0, -0x1e00, 0x4200, 0x3c00}},
};
static const struct Collision sToss[1] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x1d00, 0x1700, 0x3c00}},
};
static const struct Collision sHidden[1] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
};
// clang-format on

// --------------------------------------------

/*
  Zero 2's VFX 33, Magnion's afterimages and rings.
  work0:
    0 afterimage, his own frame
    1 ring
  work1: ring, how fast it closes in
*/

static void Fx_Init(struct VFX* p);
static void Fx_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2MagnionFxRoutine = {
    [ENTITY_INIT] =      Fx_Init,
    [ENTITY_UPDATE] =    Fx_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

#define FX_BOSS(s) ((struct Magnion*)(s)->unk_28)

// 0x080b5bd4: each held behind the one before
static void createAfterimages(struct Entity* boss, const Coords32* at) {
  struct Entity* lead = boss;
  struct Entity* p;
  s32 gap = PIXEL(16);
  s8 i;
  for (i = 3; i >= 0; i--) {
    p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_MAGNION_FX);
      p->work[0] = 0;
      p->coord = *at;
      p->unk_2c = lead;
      p->unk_28 = boss;
      p->unk_coord.x = gap;
      gap = PIXEL(12);
      lead = p;
    }
  }
}

// 0x080b5c58
static void createRings(struct Entity* boss) {
  struct Entity* p;
  u8 i;
  for (i = 0; i <= 9; i++) {
    p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_MAGNION_FX);
      p->work[0] = 1;
      p->work[1] = i;
      p->unk_28 = boss;
    }
  }
}

// 0x080b5cb0
static void Fx_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->work[0];
  s->flags |= FLIPABLE | DISPLAY;
  InitNonAffineMotion(s);
  if (s->work[0] == 1) s->texture = TEXTURE_AP_SHEET;
  Fx_Update(p);
}

static void keepBehind(struct Entity* s, s32 gap) {
  struct Entity* lead = s->unk_2c;
  s32 dx = s->coord.x - (lead->coord).x;
  s32 dy = s->coord.y - (lead->coord).y;
  u32 len = (u16)Sqrt((u32)(dx * dx + dy * dy));
  s32 ux, uy;
  if ((s32)len <= gap) return;
  ux = (dx << 8) / (s32)len;
  uy = (dy << 8) / (s32)len;
  s->coord.x = (lead->coord).x + gap * ux / 256;
  s->coord.y = (lead->coord).y + gap * uy / 256;
}

// 0x080b5d1c
static void Afterimage(struct Entity* s) {
  switch (s->mode[2]) {
    case 0:
      ResetDynamicMotion(s);
      SetSpriteAnimation(s, MAG(0x28));
      s->spr.oam.priority = 3;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (FX_BOSS(s)->signal & TRAIL) s->mode[2]++;
      keepBehind(s, s->unk_coord.x);
      break;
    case 2:
      s->unk_coord.x = s->unk_coord.x * 224 / 256;
      if (s->unk_coord.x <= 255) {
        s->flags &= ~(DISPLAY | FLIPABLE);
        SET_VFX_ROUTINE(s, ENTITY_DISAPPEAR);
        return;
      }
      keepBehind(s, s->unk_coord.x);
      break;
  }
  FUN_0801779c(s);
}

// 0x080b5ec8
static void Ring(struct Entity* s) {
  static const s32 sSpeed[10] = {70, 88, 119, 128, 154, 187, 210, 230, 248, 256};
  struct Magnion* boss = FX_BOSS(s);
  struct Camera* cam = &gStageRun.vm.camera;
  s32 to;
  if ((boss->s).mode[0] > ENTITY_UPDATE) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    SET_VFX_ROUTINE(s, ENTITY_DISAPPEAR);
  }
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(s, SPARK(6 + s->work[1]));
      s->spr.oam.priority = 1;
      s->work[2] = s->work[1];
      s->mode[2]++;
      // fallthrough
    case 1:
      if (boss->signal & RINGS_FLASH) {
        s->palID = 1;
        SetSpriteAnimation(s, SPARK(6 + s->work[1]));
        if (s->work[1] == 0) boss->signal &= ~RINGS_FLASH;
      }
      if (boss->signal & VANISH) {
        s->flags &= ~(DISPLAY | FLIPABLE);
        SET_VFX_ROUTINE(s, ENTITY_DISAPPEAR);
        return;
      }
      if ((++s->work[2] & 1) && Camera_GetDistance(cam, &(boss->s).coord) <= 0x1FFF &&
          !(boss->signal & RINGS_HIDDEN)) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      to = cam->viewport.x - 1;
      s->coord.x += (to - s->coord.x) * 2 * sSpeed[s->work[1]] / 256;
      to = cam->viewport.y - 1;
      if (boss->signal & RINGS_LOW) {
        s->coord.y += (to + PIXEL(28) - s->coord.y) * 2 * sSpeed[s->work[1]] / 256 - PIXEL(28);
      } else {
        s->coord.y += (to - s->coord.y) * 2 * sSpeed[s->work[1]] / 256;
      }
      UpdateSpriteAnimation(s);
      break;
  }
}

// 0x080b5d00
static void Fx_Update(struct VFX* p) {
  if ((p->s).mode[1] == 0) {
    Afterimage(&p->s);
  } else {
    Ring(&p->s);
  }
}

// --------------------------------------------

/*
  Zero 2's projectile 28, Magnion's attacks.
  work0:
    0 spread shot
    1 orbit while he holds Zero, then a shot at him
    2 fireball of the four-way attack, back where it came from
    3 its tail, his own frame
    4 part of a lava column
    5 spark an orbit's shot leaves
*/

struct Shot {
  OBJECT_HDR;
  u8 angle;   // 0xB4
  u8 right;   // 0xB5
  u8 part;    // 0xB6
  u8 _b7;
  s32 speed;  // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct Shot) == sizeof(struct Projectile));

enum { SPREAD_GATHER, SPREAD, ORBIT, ORBIT_SHOT, FIREBALL, TAIL, COLUMN, SPARK_FALL };
enum { SPREAD_WAIT, SPREAD_FLY, SPREAD_BURST };

static void Shot_Init(struct Shot* p);
static void Shot_Update(struct Shot* p);
static void Shot_Die(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2MagnionShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Shot_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Shot_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Shot_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083444d4, 0x08344504, 0x08344534, 0x08344564
static const struct Collision sSpread = {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}};
static const struct Collision sOrbitShot = {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}};
static const struct Collision sFireball = {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0xa00, 0xa00}};
static const struct Collision sColumn = {DDP, FACTION_ENEMY, 0, 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}};
// clang-format on

#define FIRE(n) MOTION(AP_SHEET_Z2_MAGNION_FIRE, (n))
#define BLAST(n) MOTION(AP_SHEET_Z2_MAGNION_BLAST, (n))

static struct Shot* newShot(bool8 first, u8 kind) {
  struct Entity* p = first ? AllocEntityFirst(gProjectileHeaderPtr) : AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_MAGNION_SHOT);
    p->work[0] = kind;
  }
  return (struct Shot*)p;
}

// 0x080a0e70: below the part before it, or at the floor
static struct Entity* createColumn(struct Entity* below, const Coords32* at, u8 part) {
  struct Shot* p = newShot(TRUE, 4);
  if (p != NULL) {
    if (below == NULL) {
      (p->s).coord = *at;
    } else {
      (p->s).coord.x = below->coord.x;
      (p->s).coord.y = below->coord.y + PIXEL(16);
    }
    p->part = part;
  }
  return &p->s;
}

// 0x080a0edc
static void createSpreadShot(struct Entity* boss, const Coords32* at, u8 angle, u8 n) {
  struct Shot* p = newShot(TRUE, 0);
  if (p != NULL) {
    (p->s).work[1] = n;
    (p->s).coord = *at;
    p->angle = angle;
    (p->s).unk_28 = boss;
  }
}

// 0x080a0f44
static void createOrbit(const Coords32* at, u8 n) {
  static const s16 sAt[4][2] = {{80, 50}, {-80, 50}, {-80, -50}, {80, -50}};
  struct Shot* p = newShot(TRUE, 1);
  if (p != NULL) {
    (p->s).coord.x = at->x + PIXEL(sAt[n][0]);
    (p->s).coord.y = at->y + PIXEL(sAt[n][1]);
    (p->s).work[1] = n;
  }
}

// 0x080a1028: four tail parts trail it
static void createFireball(struct Entity* boss, const Coords32* at, bool8 right, u8 angle) {
  struct Shot* p = newShot(FALSE, 2);
  struct Shot* tail;
  u8 a, i;
  if (p == NULL) return;
  (p->s).unk_28 = boss;
  (p->s).coord.x = at->x - PIXEL(6 - right * 12);
  (p->s).unk_coord.x = (p->s).coord.x;
  (p->s).coord.y = at->y - PIXEL(20);
  (p->s).unk_coord.y = (p->s).coord.y;
  p->angle = angle;
  p->right = right;
  a = angle + 64;
  if (right) a = 128 - a;
  (p->s).d.x = COS(a);
  (p->s).d.y = SIN(a);
  p->speed = PIXEL(8);
  for (i = 1; i <= 4; i++) {
    tail = newShot(FALSE, 3);
    if (tail != NULL) {
      (tail->s).unk_coord = (p->s).coord;
      tail->angle = p->angle;
      tail->right = p->right;
      tail->part = (p->s).work[2];
      (tail->s).work[2] = i;
      (tail->s).unk_28 = &p->s;
    }
  }
}

// 0x080a0e1c
static void createSpark(const Coords32* at, u8 n) {
  struct Shot* p = newShot(TRUE, 5);
  if (p != NULL) {
    (p->s).work[1] = n;
    (p->s).coord = *at;
  }
}

// 0x080a1104
static void Shot_Init(struct Shot* p) {
  struct Entity* s = &p->s;
  static const u8 sFirst[6] = {SPREAD_GATHER, ORBIT, FIREBALL, TAIL, COLUMN, SPARK_FALL};
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sFirst[s->work[0]];
  s->flags |= FLIPABLE | DISPLAY;
  if (s->work[0] == 3) {
    InitRotatableMotion(s);
    ResetDynamicMotion(s);
    GotoMotion(s, MAG(0x18), p->part & 1, 2);
    SET_XFLIP(p, p->right);
    s->angle = p->angle;
  } else {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
  }
  Shot_Update(p);
}

static void Shot_Die(struct Shot* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

static void vanish(struct Shot* p) {
  (p->s).flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

static void setStep(struct Entity* s, u8 step) {
  s->mode[2] = step;
  s->mode[3] = 0;
}

// 0x080a1208: three sparks gather
static void Spread_Gather(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->work[3] = 1;
      SetSpriteAnimation(p, SPARK(s->work[2]));
      s->mode[2]++;
      // fallthrough
    case 2:
      UpdateSpriteAnimation(p);
      if (loopEnded(s) && --s->work[3] == 0) {
        if (++s->work[2] == 3) {
          s->mode[1] = SPREAD;
          setStep(s, SPREAD_WAIT);
        } else {
          s->mode[2] = 1;
        }
      }
      break;
  }
}

// 0x080a1298, 0x080a12bc
static void Spread(struct Shot* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (s->mode[2] == SPREAD_FLY && ((p->body).status & BODY_STATUS_B2)) setStep(s, SPREAD_BURST);
  switch (s->mode[2]) {
    case SPREAD_WAIT:  // 0x080a12d4: until he dies or flinches
      if (s->mode[3] == 0) {
        SetSpriteAnimation(p, SPARK(3));
        s->mode[3]++;
      }
      UpdateSpriteAnimation(p);
      if (animEnded(s)) setStep(s, SPREAD_FLY);
      if (boss->mode[0] > ENTITY_UPDATE || *(u16*)boss->mode == ((MAGNION_FLINCH << 8) | ENTITY_UPDATE)) {
        setStep(s, SPREAD_BURST);
      }
      break;
    case SPREAD_FLY:  // 0x080a1330
      if (s->mode[3] == 0) {
        if (s->work[1] == 0) PlaySound(SE_Z2_LEVIATHAN_SHOT);
        InitRotatableMotion(s);
        SetSpriteAnimation(p, SPARK(4));
        s->d.x = COS(p->angle) * 5;
        s->d.y = SIN(p->angle) * 5;
        s->angle = p->angle + 192;
        INIT_BODY(p, &sSpread, 0, NULL);
        s->mode[3]++;
      }
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if ((u16)FUN_080098a4(s->coord.x, s->coord.y)) setStep(s, SPREAD_BURST);
      UpdateSpriteAnimation(p);
      break;
    case SPREAD_BURST:  // 0x080a13f4
      if (s->mode[3] == 0) {
        InitNonAffineMotion(s);
        SetSpriteAnimation(p, SPARK(5));
        EXIT_BODY(p);
        s->mode[3]++;
      }
      UpdateSpriteAnimation(p);
      if (animEnded(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// 0x080a1464: swells, throbs twice, shrinks
static void Orbit(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      EXIT_BODY(p);
      InitRotatableMotion(s);
      SetSpriteAnimation(p, BLAST(0));
      s->spr.mag.x = s->spr.mag.y = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->spr.mag.x += 32;
      if (s->spr.mag.x > 0x1C0) {
        s->spr.mag.x = 0x1C0;
        s->mode[2]++;
      }
      s->spr.mag.y = s->spr.mag.x;
      break;
    case 2:
      s->work[2] = s->work[3] = 0;
      s->mode[2]++;
      // fallthrough
    case 3:
      s->work[2] += 16;
      if (s->work[2] == 0 && ++s->work[3] == 2) s->mode[2]++;
      s->spr.mag.x = SIN(s->work[2]) / 4 + 0x1C0;
      s->spr.mag.y = SIN(s->work[2]) / 4 + 0x1C0;
      break;
    case 4:
      s->spr.mag.x = s->spr.mag.y = 0x1C0;
      s->mode[2]++;
      // fallthrough
    case 5:
      s->spr.mag.x -= 32;
      if (s->spr.mag.x <= 255) {
        s->spr.mag.x = 0x100;
        s->mode[1] = ORBIT_SHOT;
        s->mode[2] = 0;
      }
      s->spr.mag.y = s->spr.mag.x;
      break;
  }
  UpdateSpriteAnimation(p);
}

// 0x080a15b0
static void Orbit_Shot(struct Shot* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  static const u16 sAnims[4] = {BLAST(1), BLAST(2), BLAST(3), BLAST(4)};
  s32 dx, dy;
  u32 len;
  switch (s->mode[2]) {
    case 0:
      s->spr.oam.priority = 1;
      INIT_BODY(p, &sOrbitShot, 0, NULL);
      SetSpriteAnimation(p, sAnims[s->work[1]]);
      dx = z->coord.x - s->coord.x;
      dy = z->coord.y - (s->coord.y + PIXEL(16));
      len = (u16)Sqrt((u32)(dx * dx + dy * dy));
      s->d.x = len ? (dx << 8) / (s32)len * 6 : 0;
      s->d.y = len ? (dy << 8) / (s32)len * 6 : 0;
      s->work[2] = 30;
      s->work[3] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if ((u32)(s->coord.x - z->coord.x + 0x380) <= 0x6FF) {
        if (s->work[2] == 30) PlaySound(SE_Z2_DESERT_TAIL_HIT);
        if (s->work[2] != 0) {
          s->work[2]--;
          break;
        }
      }
      if ((++s->work[3] & 3) == 0) createSpark(&s->coord, s->work[1]);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// 0x080a17a0: flies out, slows and comes back
static void Fireball(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->spr.oam.priority = 1;
      INIT_BODY(p, &sFireball, 0, NULL);
      InitRotatableMotion(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, MAG(0x19));
      SET_XFLIP(p, p->right);
      s->angle = p->angle;
      s->work[2] = 38;
      s->work[3] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (++s->work[3] & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (--s->work[2] == 0 || (s->unk_28)->mode[0] > ENTITY_UPDATE) SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      s->coord.x += p->speed * s->d.x / 256;
      s->coord.y += p->speed * s->d.y / 256;
      p->speed -= 112;
      FUN_0801779c(s);
      break;
  }
}

// 0x080a18d8
static void Tail(struct Shot* p) {
  struct Entity* s = &p->s;
  struct Entity* ball = s->unk_28;
  if (++s->work[3] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  s->spr.oam.priority = 1;
  s->coord.x = s->unk_coord.x + (ball->coord.x - s->unk_coord.x) * s->work[2] / 5;
  s->coord.y = s->unk_coord.y + (ball->coord.y - s->unk_coord.y) * s->work[2] / 5;
  if (ball->mode[0] > ENTITY_UPDATE) vanish(p);
  FUN_0801779c(s);
}

// 0x080a1984
static void Column(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      INIT_BODY(p, &sColumn, 0, NULL);
      GotoMotion(s, FIRE(0), p->part, 1);
      s->d.y = -PIXEL(8);
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.y += s->d.y;
      UpdateSpriteAnimation(p);
      if (s->coord.y < gStageRun.vm.camera.viewport.y - PIXEL(144)) SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// 0x080a1700
static void Spark_Fall(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      EXIT_BODY(p);
      SetSpriteAnimation(p, BLAST(5));
      s->d.y = 0;
      s->work[2] = 60;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.y += s->d.y;
      s->d.y += 32;
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) vanish(p);
      break;
  }
}

// 0x080a11b8
static void Shot_Update(struct Shot* p) {
  switch ((p->s).mode[1]) {
    case SPREAD_GATHER: Spread_Gather(p); break;
    case SPREAD: Spread(p); break;
    case ORBIT: Orbit(p); break;
    case ORBIT_SHOT: Orbit_Shot(p); break;
    case FIREBALL: Fireball(p); break;
    case TAIL: Tail(p); break;
    case COLUMN: Column(p); break;
    case SPARK_FALL: Spark_Fall(p); break;
  }
}

#endif
