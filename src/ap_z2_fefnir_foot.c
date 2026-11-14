#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "palette_animation.h"
#include "projectile.h"
#include "quake.h"
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
  Zero 2's Fefnir on foot, boss 14. Shuttle Factory.
  Powered up by his aura, his next attack is the big one and spends it.
*/

struct FefnirFoot {
  OBJECT_HDR;
  s32 homeX;               // 0xB4
  s32 homeY;               // 0xB8
  bool8 hitFromRight;      // 0xBC
  u8 _bd;
  bool8 powered;           // 0xBE
  u8 last;                 // 0xBF, attack picked last
  s32 left;                // 0xC0, arena
  s32 right;               // 0xC4
  struct Entity* aura;     // 0xC8
  u8 exUsed;               // 0xCC
  u8 _cd[3];
  struct Zero* zero;       // 0xD0, held
  u8 _d4[16];
};
static_assert(sizeof(struct FefnirFoot) == sizeof(struct Boss));

enum {
  FEF_WAIT,
  FEF_INTRO,
  FEF_IDLE,
  FEF_DECIDE,
  FEF_PAUSE,
  FEF_HOP,
  FEF_POWER_UP,
  FEF_CROUCH,
  FEF_FALL,
  FEF_LAND,
  FEF_JUMP_BACK,
  FEF_JUMP_PUNCH,
  FEF_DIVE,
  FEF_PUNCH_LAND,
  FEF_RISE,
  FEF_HANG,
  FEF_AIR_SHOT,
  FEF_AIR_BIG_SHOT,
  FEF_LEAP,
  FEF_LEAP_UP,
  FEF_LEAP_TOP,
  FEF_DOWN_SHOT,
  FEF_DOWN_BIG_SHOT,
  FEF_STAND,
  FEF_SHOT,
  FEF_BIG_SHOT,
  FEF_DASH,
  FEF_DASH_STOP,
  FEF_GRAB,
  FEF_LIFT,
  FEF_SWING,
  FEF_SLAM,
  FEF_CHASE,
  FEF_CHASE_FALL,
  FEF_CHASE_LAND,
  FEF_SLAM_END,
  FEF_HOP_TOWARD,
  FEF_HOP_FALL,
  FEF_HOP_SHOT,
  FEF_HOP_BIG_SHOT,
  FEF_BOMB_WIND,
  FEF_BOMB,
  FEF_BIG_BOMB,
  FEF_BOMB_END,
  FEF_EX,
  FEF_EX_RAISE,
  FEF_EX_PILLARS,
  FEF_EX_END,
};

#define FEF(n) MOTION(DM201_Z2_FEFNIR, (n))
#define SHOT(n) MOTION(AP_SHEET_Z2_FEFNIR_SHOT, (n))
#define PILLAR(n) MOTION(AP_SHEET_Z2_FEFNIR_PILLAR, (n))
#define JUMP_FIRE(n) MOTION(AP_SHEET_Z2_FEFNIR_JUMP_FIRE, (n))

// clang-format off
// 0x0833ccf4
static const struct Collision sBody[7] = {
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 2, 0x00000001, {-0x1600, -0x1900, 0x1600, 0x1600}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x200, -0x1400, 0x1a00, 0x2800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x07, 0, 0, 0, 0x00000000, {0x200, -0x1400, 0x1a00, 0x2800}},
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 0, 0x00000001, {0x0, -0x2a00, 0x5600, 0x5600}},
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x2a00, 0x5600, 0x5600}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x07, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x1000, 0x2400}},
};
// clang-format on

#define DASH_BODY (&sBody[0])
#define NORMAL_BODY (&sBody[1])
#define HOLD_BODY (&sBody[3])
#define SLAM_BODY (&sBody[4])
#define EX_BODY (&sBody[5])

// 0x0833cd9c
static const Coords32 sElementCoord = {0, -PIXEL(20)};

static const struct PreloadEntity sShotSheet = {AP_SHEET_Z2_FEFNIR_SHOT, 0, 576, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sJumpFireSheet = {AP_SHEET_Z2_FEFNIR_JUMP_FIRE, 0, 765, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sPillarSheet = {AP_SHEET_Z2_FEFNIR_PILLAR, 0, 765, 9, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWaveSheet = {AP_SHEET_Z2_FEFNIR_WAVE, 0, 885, 7, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sBigWaveSheet = {AP_SHEET_Z2_FEFNIR_BIG_WAVE, 0, 928, 8, 0, AP_PRELOAD_SHEET, 0};

static void FefnirFoot_Init(struct FefnirFoot* p);
static void FefnirFoot_Update(struct FefnirFoot* p);
static void FefnirFoot_Die(struct FefnirFoot* p);

// clang-format off
const BossRoutine gApZ2FefnirFootRoutine = {
    [ENTITY_INIT] =      (BossFunc)FefnirFoot_Init,
    [ENTITY_UPDATE] =    (BossFunc)FefnirFoot_Update,
    [ENTITY_DIE] =       (BossFunc)FefnirFoot_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void createShot(const Coords32* at, u8 kind, bool8 big, bool8 right);
static void createWave(const Coords32* at, bool8 big, bool8 right, u8 left);
static void createJumpFire(struct FefnirFoot* boss);
static void createPillar(const Coords32* at, bool8 low);
static void createBomb(struct FefnirFoot* boss, bool8 big);
static struct Entity* createAura(struct FefnirFoot* boss);
void CreateDashDust(Coords32* c, bool8 isRight);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void faceZero(struct FefnirFoot* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static bool8 alive(struct Zero* z) { return !((z->body).status & BODY_STATUS_DEAD) && (z->body).hp != 0; }

// Stands in for Zero 2's thrown state, 0x08022ea8
static void throwZero(struct Zero* z, s32 dx, s32 dy) {
  GotoMotion(&z->s, MOTION(DM004_ZERO_AIR, 4), 2, 1);
  (z->s).mode[1] = ZERO_AIR, (z->s).mode[2] = 2, (z->s).mode[3] = 1;
  (z->unk_b4).blownSpeed = dx;
  (z->s).d.y = dy;
}

// Zero caught by his hold box, or NULL
static struct Zero* caught(struct FefnirFoot* p) {
  struct Zero* z;
  if (!((p->body).status & BODY_STATUS_BINDING)) return NULL;
  z = (struct Zero*)((p->body).enemy)->parent;
  if ((z->s).kind != ENTITY_PLAYER || !alive(z)) return NULL;
  return z;
}

static void dropAura(struct FefnirFoot* p) {
  if (p->aura != NULL) (p->aura)->work[1] = 1;
  p->aura = NULL;
}

// Moves, then gravity, then the floor
static bool8 tumble(struct Entity* s) {
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  return TRUE;
}

// One frame of flight, then the floor
static bool8 fall(struct Entity* s) {
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  return TRUE;
}

static void fly(struct Entity* s) {
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

static bool8 countDown(struct Entity* s) { return --s->work[2] == 0xFF; }

static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct FefnirFoot* p = (struct FefnirFoot*)body->parent;
  p->hitFromRight = (p->s).coord.x < ((body->enemy)->parent)->coord.x;
}

// 0x0805a404
static void FefnirFoot_Init(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sShotSheet);
  ApLoadSheet(&sJumpFireSheet);
  ApLoadSheet(&sWaveSheet);
  ApLoadSheet(&sBigWaveSheet);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, FEF(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, NORMAL_BODY, 64);
  (p->body).fn = onHit;
  p->powered = FALSE;
  p->last = 0;
  p->left = s->coord.x;
  p->right = s->coord.x + PIXEL(448);
  s->coord.x += PIXEL(208);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  p->aura = NULL;
  p->exUsed = 0;
  s->unk_2c = NULL;
  p->zero = NULL;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, FEF_WAIT);
  FefnirFoot_Update(p);
}

typedef void (*StateFunc)(struct FefnirFoot*);
static const StateFunc sStates[48];

// 0x0805a4dc
static void FefnirFoot_Update(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    FefnirFoot_Die(p);
    return;
  }
  // 0x0805a7f4
  if (((p->body).status & BODY_STATUS_WHITE) &&
      (s->unk_2c != NULL || (s->unk_2c = ApplyElementEffect(9, (Object*)p, &sElementCoord)) != NULL)) {
    setMode(s, FEF_HOP);
  }
  sStates[s->mode[1]](p);
  if (s->coord.x < p->left + PIXEL(32)) {
    s->coord.x = p->left + PIXEL(32);
  } else if (s->coord.x > p->right - PIXEL(32)) {
    s->coord.x = p->right - PIXEL(32);
  }
}

// 0x0805a570: knocked back, kneels, beams out on script's flag 7
static void FefnirFoot_Die(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  bool8 right;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(20));
    faceZero(p);
    s->d.x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    s->d.y = -PIXEL(3);
    s->unk_28 = NULL;
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
      UpdateEntityAnim(s);
      if (tumble(s)) s->mode[1]++;
      break;
    case 1:
      SetMotion(s, FEF(23));
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
      SetMotion(s, FEF(23));
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
}

// 0x0805a82c: waits for script's go
static void Fefnir_Wait(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 16;
    s->mode[2]++;
    s->mode[3] = 0;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0 && (s->scriptEntity->flags & 1)) setMode(s, FEF_INTRO);
}

// 0x0805a868: roars until script lets go
static void Fefnir_Intro(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(22));
    PlaySound(SE_Z2_FEFNIR_SUMMON);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!(gStageRun.vm.active & VM_ACTIVE)) {
    setMode(s, FEF_CROUCH);
    s->mode[3] = FEF_JUMP_BACK;
  }
}

// 0x0805a8b4
static void Fefnir_Idle(struct FefnirFoot* p UNUSED) {}

// 0x0805a8b8: never the same attack twice running. EX at rank A, under 32 HP and 16 HP
static void Fefnir_Decide(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  s32 dist;
  u8 r;
  UpdateEntityAnim(s);
  if (!p->powered) {
    if (gScore.total->rank > 4 && ((p->exUsed == 0 && (p->body).hp <= 31) || (p->exUsed == 1 && (p->body).hp <= 15))) {
      p->exUsed++;
      setMode(s, FEF_EX);
      return;
    }
    if (RANDOM(RNG_0202f388) & 1) {
      setMode(s, FEF_POWER_UP);
      return;
    }
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) != 0) {
    if (!(RANDOM(RNG_0202f388) & 1) && !p->powered) {
      s->mode[1] = FEF_POWER_UP;
    } else {
      s->mode[1] = FEF_LEAP;
    }
    s->mode[2] = 0;
    return;
  }
  do {
    dist = (pZero2->s).coord.x - s->coord.x;
    if (dist < 0) dist = -dist;
    r = RANDOM(RNG_0202f388) & 15;
    if (dist <= PIXEL(32) - 1) {
      if (r <= 7) {
        s->mode[1] = FEF_DASH;
      } else if (r <= 11) {
        s->mode[1] = FEF_JUMP_PUNCH;
      } else {
        s->mode[1] = FEF_CROUCH;
        s->mode[3] = FEF_JUMP_BACK;
      }
    } else if (dist <= PIXEL(64) - 1) {
      if (r <= 3) {
        s->mode[1] = FEF_DASH;
      } else if (r <= 7) {
        s->mode[1] = FEF_JUMP_PUNCH;
      } else if (r <= 11) {
        s->mode[1] = FEF_CROUCH;
        s->mode[3] = FEF_RISE;
      } else {
        s->mode[1] = FEF_BOMB_WIND;
      }
    } else if (dist <= PIXEL(96) - 1) {
      if (r <= 5) {
        s->mode[1] = FEF_JUMP_PUNCH;
      } else if (r <= 8) {
        s->mode[1] = FEF_HOP_TOWARD;
      } else if (r <= 10) {
        s->mode[1] = FEF_CROUCH;
        s->mode[3] = FEF_RISE;
      } else {
        s->mode[1] = FEF_BOMB_WIND;
      }
    } else {
      if (r <= 3) {
        s->mode[1] = FEF_STAND;
      } else if (r <= 7) {
        s->mode[1] = FEF_LEAP;
      } else if (r <= 11) {
        s->mode[1] = FEF_HOP_TOWARD;
      } else {
        s->mode[1] = FEF_BOMB_WIND;
      }
    }
  } while (p->last == s->mode[1]);
  p->last = s->mode[1];
  s->mode[2] = 0;
}

// 0x0805aa7c
static void Fefnir_Pause(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(0));
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, FEF_DECIDE);
}

// 0x0805aabc: element hit, hops back until it wears off
static void Fefnir_Hop(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(20));
    SetDDP(&p->body, NORMAL_BODY);
    faceZero(p);
    s->d.x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    s->d.y = -PIXEL(3);
    PlaySound(SE_Z2_FEFNIR_HURT);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  switch (s->mode[3]) {
    case 0:
      UpdateEntityAnim(s);
      if (tumble(s)) s->mode[3]++;
      break;
    case 1:
      SetMotion(s, FEF(21));
      s->mode[3]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (s->unk_2c == NULL) setMode(s, FEF_DECIDE);
      break;
  }
}

// 0x0805abe8
static void Fefnir_PowerUp(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(22));
    dropAura(p);
    p->aura = createAura(p);
    if (p->aura != NULL) p->powered = TRUE;
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, FEF_DECIDE);
}

// 0x0805ac50: then mode[3]'s
static void Fefnir_Crouch(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(1));
    faceZero(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, s->mode[3]);
}

// 0x0805acdc
static void Fefnir_Fall(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(3));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fall(s)) setMode(s, FEF_LAND);
}

// 0x0805ad34
static void Fefnir_Land(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(1));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) {
    s->mode[1] = FEF_PAUSE;
    s->mode[2] = 1;
    s->work[2] = 1;
  }
}

// 0x0805ad70
static void Fefnir_JumpBack(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(3));
    s->d.x = facingRight(s) ? -PIXEL(2) : PIXEL(2);
    s->d.y = -PIXEL(4);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fall(s)) setMode(s, FEF_LAND);
}

// 0x0805ade8: rising with his fists aflame
static void Fefnir_JumpPunch(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(17));
    faceZero(p);
    s->d.x = facingRight(s) ? 0x240 : -0x240;
    s->d.y = -0x500;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] == 13) {
    ApLoadSheet(&sJumpFireSheet);
    createJumpFire(p);
  }
  if ((s->motion).cmdIdx > 3) fly(s);
  if (s->d.y > 0) setMode(s, FEF_DIVE);
}

// 0x0805af14
static void Fefnir_Dive(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(18));
    s->d.x = facingRight(s) ? 0x180 : -0x180;
    s->d.y = PIXEL(1);
    PlaySound(SE_Z2_FEFNIR_DIVE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fall(s)) setMode(s, FEF_PUNCH_LAND);
}

// 0x0805af94: fist into floor, flames run along it
static void Fefnir_PunchLand(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(19));
    at.x = s->coord.x + (facingRight(s) ? PIXEL(24) : -PIXEL(24));
    at.y = s->coord.y;
    if (p->powered) {
      createWave(&at, TRUE, facingRight(s), 6);
    } else {
      createWave(&at, FALSE, facingRight(s), 9);
    }
    s->work[2] = 0;
    dropAura(p);
    p->powered = FALSE;
    AppendQuake(4, &s->coord);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_PAUSE);
}

// 0x0805b0e8
static void Fefnir_Rise(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(2));
    s->d.x = 0;
    s->d.y = -0x580;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (s->d.y + 64 > 0) setMode(s, FEF_HANG);
}

// 0x0805b13c
static void Fefnir_Hang(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(3));
    s->work[2] = 6;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (!countDown(s)) return;
  if (p->powered) {
    s->mode[1] = FEF_AIR_BIG_SHOT;
  } else {
    s->mode[1] = FEF_AIR_SHOT;
    s->work[3] = 3;
  }
  s->mode[2] = 0;
}

static void airShotAt(struct Entity* s, Coords32* at) {
  at->x = s->coord.x + (facingRight(s) ? PIXEL(29) : -PIXEL(29));
  at->y = s->coord.y - PIXEL(10);
}

// 0x0805b1a8, 0x0805c47c: three shots down at an angle, each kicking him back up
static void Fefnir_AirShot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(4));
    s->d.x = facingRight(s) ? -PIXEL(1) : PIXEL(1);
    airShotAt(s, &at);
    createShot(&at, 2, FALSE, facingRight(s));
    s->d.y = -PIXEL(3);
    s->work[2] = 10;
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (!countDown(s)) return;
  if (--s->work[3] == 0) s->mode[1] = FEF_FALL;
  s->mode[2] = 0;
}

// 0x0805b2b8, 0x0805c58c
static void Fefnir_AirBigShot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(5));
    s->d.x = facingRight(s) ? -PIXEL(2) : PIXEL(2);
    airShotAt(s, &at);
    createShot(&at, 2, TRUE, facingRight(s));
    s->d.y = -PIXEL(3);
    if (s->mode[1] == FEF_HOP_BIG_SHOT) {
      p->powered = FALSE;
      dropAura(p);
    }
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_FALL);
}

// 0x0805b3b0: a leap at Zero
static void Fefnir_Leap(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(1));
    faceZero(p);
    s->d.x = ((pZero2->s).coord.x - s->coord.x) >> 5;
    s->d.y = -PIXEL(6);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_LEAP_UP);
}

// 0x0805b458
static void Fefnir_LeapUp(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(2));
    s->work[2] = 12;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (countDown(s)) setMode(s, FEF_LEAP_TOP);
}

// 0x0805b4b0
static void Fefnir_LeapTop(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(6));
    s->work[2] = 12;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (!countDown(s)) return;
  if (p->powered) {
    s->mode[1] = FEF_DOWN_BIG_SHOT;
  } else {
    s->mode[1] = FEF_DOWN_SHOT;
    s->work[3] = 3;
  }
  s->mode[2] = 0;
}

static void downShotAt(struct Entity* s, Coords32* at) {
  at->x = s->coord.x + (facingRight(s) ? PIXEL(11) : -PIXEL(11));
  at->y = s->coord.y + PIXEL(20);
}

// 0x0805b51c: three shots straight down
static void Fefnir_DownShot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(7));
    s->d.x = facingRight(s) ? PIXEL(2) : -PIXEL(2);
    downShotAt(s, &at);
    createShot(&at, 1, FALSE, facingRight(s));
    s->d.y = -0x280;
    s->work[2] = 12;
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (!countDown(s)) return;
  if (--s->work[3] == 0) {
    faceZero(p);
    s->mode[1] = FEF_FALL;
  }
  s->mode[2] = 0;
}

// 0x0805b674
static void Fefnir_DownBigShot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(8));
    s->d.x = facingRight(s) ? PIXEL(2) : -PIXEL(2);
    downShotAt(s, &at);
    createShot(&at, 1, TRUE, facingRight(s));
    s->d.y -= PIXEL(4);
    p->powered = FALSE;
    dropAura(p);
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (IsSpriteAnimEnd(s)) {
    faceZero(p);
    setMode(s, FEF_FALL);
  }
}

// 0x0805b7d0
static void Fefnir_Stand(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  u8 r;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(9));
    faceZero(p);
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (p->powered) {
    s->mode[1] = FEF_BIG_SHOT;
  } else {
    s->mode[1] = FEF_SHOT;
    r = RANDOM(RNG_0202f388) % 3;
    s->work[3] = r + 1;
    s->mode[3] = r;
  }
  s->mode[2] = 0;
}

static void standShotAt(struct Entity* s, Coords32* at) {
  at->x = s->coord.x + (facingRight(s) ? PIXEL(44) : -PIXEL(44));
  at->y = s->coord.y - PIXEL(30);
}

// 0x0805b8a0: one, two or three shots ahead
static void Fefnir_Shot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  // 0x0833cda4
  static const u8 sGap[3] = {17, 28, 8};
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(10));
    standShotAt(s, &at);
    createShot(&at, 0, FALSE, facingRight(s));
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->work[2] = sGap[s->mode[3]];
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (--s->work[3] == 0) s->mode[1] = FEF_PAUSE;
  s->mode[2] = 0;
}

// 0x0805b990
static void Fefnir_BigShot(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(11));
    standShotAt(s, &at);
    createShot(&at, 0, TRUE, facingRight(s));
    p->powered = FALSE;
    dropAura(p);
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_PAUSE);
}

// 0x0805ba74: a dash that catches Zero
static void Fefnir_Dash(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  s32 dx;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(12));
    faceZero(p);
    if (facingRight(s)) {
      s->d.x = 0x380;
      s->unk_coord.x = -24;
    } else {
      s->d.x = -0x380;
      s->unk_coord.x = 24;
    }
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).cmdIdx <= 2) return;
  if (s->mode[3] == 0) {
    CreateParticle(&s->coord, 0, facingRight(s));
    SetDDP(&p->body, DASH_BODY);
    s->work[2] = 0;
    s->mode[3]++;
  }
  if (s->work[2]++ % 3 == 0) CreateDashDust(&s->coord, facingRight(s));
  dx = s->d.x;
  s->coord.x += dx;
  if (dx < 0) dx = -dx;
  if (dx > 128) {
    s->d.x += s->unk_coord.x;
  } else {
    setMode(s, FEF_DASH_STOP);
  }
  if ((p->body).status & BODY_STATUS_B2) setMode(s, FEF_GRAB);
}

static void slowDown(struct Entity* s, s32 by) {
  if (facingRight(s)) {
    s->d.x -= by;
    if (s->d.x < 0) s->d.x = 0;
  } else {
    s->d.x += by;
    if (s->d.x > 0) s->d.x = 0;
  }
  s->coord.x += s->d.x;
}

// 0x0805bbb8
static void Fefnir_DashStop(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(0));
    s->mode[2]++;
    SetDDP(&p->body, NORMAL_BODY);
  }
  UpdateEntityAnim(s);
  slowDown(s, 16);
  if (s->d.x == 0) setMode(s, FEF_PAUSE);
}

static void hold(struct FefnirFoot* p, s32 dx, s32 dy) {
  struct Zero* z = caught(p);
  if (z == NULL) return;
  p->zero = z;
  (z->s).coord.x = (p->s).coord.x + (facingRight(&p->s) ? dx : -dx);
  (z->s).coord.y = (p->s).coord.y + dy;
}

// 0x0805bc28
static void Fefnir_Grab(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, HOLD_BODY);
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  slowDown(s, 32);
  hold(p, PIXEL(32), -PIXEL(6));
  if (s->d.x == 0) setMode(s, FEF_LIFT);
}

// 0x0805bd0c
static void Fefnir_Lift(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  // 0x0833cda8, 0x0833cdb8
  static const s32 sX[4] = {0x1E00, 0x1800, 0x1200, 0x1200};
  static const s32 sY[4] = {-0x400, -0xA00, -0x1200, -0x1200};
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(13));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  hold(p, sX[(s->motion).cmdIdx], sY[(s->motion).cmdIdx]);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_SWING);
}

// 0x0805bdec
static void Fefnir_Swing(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  // 0x0833cdc8, 0x0833cdd4
  static const s32 sX[3] = {0xF00, 0x600, -0x100};
  static const s32 sY[3] = {-0x2000, -0x2700, -0x2900};
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(14));
    s->mode[2]++;
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  hold(p, sX[(s->motion).cmdIdx], sY[(s->motion).cmdIdx]);
  if (IsSpriteAnimEnd(s)) {
    SetDDP(&p->body, SLAM_BODY);
    setMode(s, FEF_SLAM);
  }
}

// 0x0805bee0: Zero flung straight up
static void Fefnir_Slam(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(15));
    PlaySound(SE_Z2_FEFNIR_SLAM);
    at.x = s->coord.x + (facingRight(s) ? -PIXEL(1) : PIXEL(1));
    at.y = s->coord.y - PIXEL(64);
    CreateSmoke(1, &at);
    if (p->zero != NULL && alive(p->zero)) throwZero(p->zero, 0, -0xB00);
    AppendQuake(8, &s->coord);
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (!(gStageRun.vm.active & VM_ACTIVE) && p->powered) {
    s->mode[1] = FEF_CHASE;
  } else {
    s->mode[1] = FEF_SLAM_END;
  }
  s->mode[2] = 0;
}

// 0x0805bfc4: leaps after him
static void Fefnir_Chase(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  u8 left;
  if (s->mode[2] == 0) {
    GotoMotion(s, FEF(17), 3, 0);
    UpdateEntityAnim(s);
    SetDDP(&p->body, HOLD_BODY);
    s->d.y = -0xDC0;
    SET_XFLIP(p, p->left + PIXEL(224) > (pZero2->s).coord.x);
    s->work[2] = 40;
    s->mode[2]++;
  }
  left = s->work[2];
  if (left > 24) {
    s->work[2]--;
    return;
  }
  s->d.x = left == 0 ? 0 : ((pZero2->s).coord.x + (facingRight(s) ? -PIXEL(16) : PIXEL(16)) - s->coord.x) / left;
  fly(s);
  if (countDown(s)) setMode(s, FEF_CHASE_FALL);
}

// 0x0805c120
static void Fefnir_ChaseFall(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    s->d.x = facingRight(s) ? PIXEL(2) : -PIXEL(2);
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  hold(p, -PIXEL(4), -PIXEL(10));
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  SetDDP(&p->body, SLAM_BODY);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  at.x = s->coord.x + (facingRight(s) ? PIXEL(24) : -PIXEL(24));
  at.y = s->coord.y;
  createShot(&at, 3, FALSE, FALSE);
  setMode(s, FEF_CHASE_LAND);
}

// 0x0805c24c
static void Fefnir_ChaseLand(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(19));
    s->mode[2]++;
    SetDDP(&p->body, NORMAL_BODY);
    p->powered = FALSE;
    dropAura(p);
    if (p->zero != NULL && alive(p->zero)) throwZero(p->zero, facingRight(s) ? PIXEL(4) : -PIXEL(4), -PIXEL(4));
    AppendQuake(8, &s->coord);
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_JUMP_BACK);
}

// 0x0805c304
static void Fefnir_SlamEnd(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[2]++;
    SetDDP(&p->body, NORMAL_BODY);
    s->work[2] = 60;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, FEF_JUMP_BACK);
}

// 0x0805c348: hops to 64 px short of Zero, shooting from the top
static void Fefnir_HopToward(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(1));
    faceZero(p);
    s->d.x = ((pZero2->s).coord.x - s->coord.x + (facingRight(s) ? -PIXEL(64) : PIXEL(64))) / 48;
    s->d.y = -PIXEL(6);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_HOP_FALL);
}

// 0x0805c418
static void Fefnir_HopFall(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(3));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fly(s);
  if (s->d.y <= PIXEL(3)) return;
  if (p->powered) {
    s->mode[1] = FEF_HOP_BIG_SHOT;
  } else {
    s->mode[1] = FEF_HOP_SHOT;
    s->work[3] = 3;
  }
  s->mode[2] = 0;
}

// 0x0805c69c
static void Fefnir_BombWind(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(27));
    faceZero(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_BOMB);
}

// 0x0805c770, 0x0805c7cc
static void Fefnir_Bomb(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  bool8 big = s->mode[1] == FEF_BIG_BOMB;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(28));
    createBomb(p, big);
    if (big) {
      p->powered = FALSE;
      dropAura(p);
    }
    PlaySound(SE_Z2_FEFNIR_LOB);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!IsSpriteAnimEnd(s)) return;
  setMode(s, !big && p->powered ? FEF_BIG_BOMB : FEF_BOMB_END);
}

// 0x0805c82c
static void Fefnir_BombEnd(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(29));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_PAUSE);
}

// 0x0805c868: gathers his flames
static void Fefnir_Ex(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(22));
    SetDDP(&p->body, EX_BODY);
    p->powered = FALSE;
    dropAura(p);
    s->unk_28 = ApZ2CreateEx(s, 1);
    s->work[2] = 64;
    PlaySound(SE_Z2_HARPUIA_EX);
    PlaySound(SE_Z2_FEFNIR_SUMMON);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, FEF_EX_RAISE);
}

// 0x0805c8f4
static void Fefnir_ExRaise(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(24));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!IsSpriteAnimEnd(s)) return;
  setMode(s, FEF_EX_PILLARS);
  ApLoadSheet(&sPillarSheet);
  s->work[3] = 0;
}

// 0x0805c980: nine rounds of pillars about where Zero was
static void Fefnir_ExPillars(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(25));
    at.y = (pZero2->s).coord.y;
    switch (s->work[3] % 3) {
      case 0:
        s->unk_coord.x = (pZero2->s).coord.x;
        at.x = s->unk_coord.x + PIXEL(64);
        createPillar(&at, FALSE);
        at.x = s->unk_coord.x - PIXEL(64);
        createPillar(&at, FALSE);
        s->work[2] = 32;
        break;
      case 1:
        at.x = s->unk_coord.x + PIXEL(32);
        createPillar(&at, TRUE);
        at.x = s->unk_coord.x - PIXEL(32);
        createPillar(&at, TRUE);
        at.x = s->unk_coord.x + PIXEL(96);
        createPillar(&at, TRUE);
        at.x = s->unk_coord.x - PIXEL(96);
        createPillar(&at, TRUE);
        s->work[2] = 32;
        break;
      default:
        at.x = s->unk_coord.x;
        createPillar(&at, FALSE);
        at.x = s->unk_coord.x + PIXEL(128);
        createPillar(&at, FALSE);
        at.x = s->unk_coord.x - PIXEL(128);
        createPillar(&at, FALSE);
        s->work[2] = 72;
        break;
    }
    PlaySound(SE_Z2_FEFNIR_SLAM);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (++s->work[3] > 8) s->mode[1] = FEF_EX_END;
  s->mode[2] = 0;
}

// 0x0805cac0
static void Fefnir_ExEnd(struct FefnirFoot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FEF(26));
    SetDDP(&p->body, NORMAL_BODY);
    if (s->unk_28 != NULL) (s->unk_28)->work[1] = 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, FEF_PAUSE);
}

// 0x0833cc34
static const StateFunc sStates[48] = {
    [FEF_WAIT] = Fefnir_Wait,
    [FEF_INTRO] = Fefnir_Intro,
    [FEF_IDLE] = Fefnir_Idle,
    [FEF_DECIDE] = Fefnir_Decide,
    [FEF_PAUSE] = Fefnir_Pause,
    [FEF_HOP] = Fefnir_Hop,
    [FEF_POWER_UP] = Fefnir_PowerUp,
    [FEF_CROUCH] = Fefnir_Crouch,
    [FEF_FALL] = Fefnir_Fall,
    [FEF_LAND] = Fefnir_Land,
    [FEF_JUMP_BACK] = Fefnir_JumpBack,
    [FEF_JUMP_PUNCH] = Fefnir_JumpPunch,
    [FEF_DIVE] = Fefnir_Dive,
    [FEF_PUNCH_LAND] = Fefnir_PunchLand,
    [FEF_RISE] = Fefnir_Rise,
    [FEF_HANG] = Fefnir_Hang,
    [FEF_AIR_SHOT] = Fefnir_AirShot,
    [FEF_AIR_BIG_SHOT] = Fefnir_AirBigShot,
    [FEF_LEAP] = Fefnir_Leap,
    [FEF_LEAP_UP] = Fefnir_LeapUp,
    [FEF_LEAP_TOP] = Fefnir_LeapTop,
    [FEF_DOWN_SHOT] = Fefnir_DownShot,
    [FEF_DOWN_BIG_SHOT] = Fefnir_DownBigShot,
    [FEF_STAND] = Fefnir_Stand,
    [FEF_SHOT] = Fefnir_Shot,
    [FEF_BIG_SHOT] = Fefnir_BigShot,
    [FEF_DASH] = Fefnir_Dash,
    [FEF_DASH_STOP] = Fefnir_DashStop,
    [FEF_GRAB] = Fefnir_Grab,
    [FEF_LIFT] = Fefnir_Lift,
    [FEF_SWING] = Fefnir_Swing,
    [FEF_SLAM] = Fefnir_Slam,
    [FEF_CHASE] = Fefnir_Chase,
    [FEF_CHASE_FALL] = Fefnir_ChaseFall,
    [FEF_CHASE_LAND] = Fefnir_ChaseLand,
    [FEF_SLAM_END] = Fefnir_SlamEnd,
    [FEF_HOP_TOWARD] = Fefnir_HopToward,
    [FEF_HOP_FALL] = Fefnir_HopFall,
    [FEF_HOP_SHOT] = Fefnir_AirShot,
    [FEF_HOP_BIG_SHOT] = Fefnir_AirBigShot,
    [FEF_BOMB_WIND] = Fefnir_BombWind,
    [FEF_BOMB] = Fefnir_Bomb,
    [FEF_BIG_BOMB] = Fefnir_Bomb,
    [FEF_BOMB_END] = Fefnir_BombEnd,
    [FEF_EX] = Fefnir_Ex,
    [FEF_EX_RAISE] = Fefnir_ExRaise,
    [FEF_EX_PILLARS] = Fefnir_ExPillars,
    [FEF_EX_END] = Fefnir_ExEnd,
};

// --------------------------------------------
/*
  Zero 2's projectile 34, his shots.
  work0:
    0: ahead
    1: straight down
    2: down at an angle
    3: fire where a big one hit floor
  work1: big, 2 once a big one hits floor
*/

struct Shot {
  OBJECT_HDR;
  u8 _b4[9];
  bool8 right;  // 0xBD
  u8 _be[6];
};
static_assert(sizeof(struct Shot) == sizeof(struct Projectile));

static void Shot_Init(struct Shot* p);
static void Shot_Update(struct Shot* p);
static void Shot_Die(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2FefnirShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Shot_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Shot_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Shot_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083448d4: by kind, small then big
static const struct Collision sShot[14] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1a00, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1a00}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1a00}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x700, 0x1500, 0x1300}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

#define BODY_HIT 0x400104

// 0x080a35fc
static void createShot(const Coords32* at, u8 kind, bool8 big, bool8 right) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FEFNIR_SHOT);
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = big;
    ((struct Shot*)p)->right = right;
  }
}

// Small ones are a big one at half size
static void initShotMotion(struct Shot* p, u8 kind, bool8 rotate) {
  struct Entity* s = &p->s;
  if (s->work[1]) {
    if (rotate) {
      InitRotatableMotion(s);
    } else {
      InitNonAffineMotion(s);
    }
    INIT_BODY(p, &sShot[kind * 4 + 2], 0, NULL);
  } else {
    InitScalerotMotion2(s);
    INIT_BODY(p, &sShot[kind * 4], 0, NULL);
    (s->spr).mag.x = (s->spr).mag.y = 128;
  }
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, SHOT(1));
}

// 0x080a36d4, 0x080a37d0, 0x080a38d8, 0x080a3a00
static void Shot_Init(struct Shot* p) {
  struct Entity* s = &p->s;
  switch (s->work[0]) {
    case 0:
      initShotMotion(p, 0, TRUE);
      s->angle = 192;
      SET_XFLIP(p, p->right);
      s->d.x = p->right ? 0x380 : -0x380;
      break;
    case 1:
      initShotMotion(p, 1, FALSE);
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, p->right);
      SET_YFLIP(p, TRUE);
      s->d.y = 0x380;
      break;
    case 2:
      initShotMotion(p, 2, TRUE);
      s->angle = 160;
      SET_XFLIP(p, p->right);
      s->d.x = SIN(96) * 7 * 128 / 256;
      s->d.y = SIN(32) * 7 * 128 / 256;
      if (!p->right) s->d.x = -s->d.x;
      break;
    case 3:
      InitNonAffineMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, SHOT(0));
      SET_XFLIP(p, p->right);
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      PlaySound(SE_Z2_SIGNALOID_FLAME);
      break;
  }
  s->work[2] = 0xFF;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Shot_Update(p);
}

static void burst(struct Shot* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Shot_Die(p);
}

// 0x080a3a88, 0x080a3ae8, 0x080a3b74, 0x080a3c08
static void Shot_Update(struct Shot* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    burst(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->work[0] == 3) {
    if (s->mode[1] != 0) {
      if ((s->motion).cmdIdx <= 4) return;
      EXIT_BODY(p);
      burst(p);
    } else if ((s->motion).cmdIdx != 0) {
      INIT_BODY(p, &sShot[12], 1, NULL);
      s->mode[1]++;
    }
    return;
  }
  if (s->work[0] != 1) s->coord.x += s->d.x;
  if (s->work[0] != 0) s->coord.y += s->d.y;
  if (--s->work[2] == 0xFF || ((p->body).status & BODY_HIT)) {
    burst(p);
    return;
  }
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  if (s->work[0] != 0 && s->work[1]) s->work[1] = 2;
  burst(p);
}

// 0x080a3c98, 0x080a3cd4, 0x080a3d2c, 0x080a3d84
static void Shot_Die(struct Shot* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 3) {
    UpdateSpriteAnimation(p);
    if (IsSpriteAnimEnd(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->work[1] == 2) {
    createShot(&s->coord, 3, FALSE, p->right);
  } else {
    CreateSmoke(s->work[1] ? 1 : 2, &s->coord);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 35, flames up from the floor where he punched.
  Small ones run along in a line, a big one is one wave.
  work3: flames still to come
*/

static void Wave_Init(struct Shot* p);
static void Wave_Update(struct Shot* p);
static void Wave_Die(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2FefnirWaveRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Wave_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Wave_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Wave_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344a38: small, then a big one's by frame
static const struct Collision sWave[9] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xc00, 0xa00, 0x2200}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0x800, -0x600, 0xa00, 0xe00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0xc00, -0x1000, 0xa00, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x1000, 0x2400, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1e00, 0xc00, 0x3e00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xa00, 0x2400, 0x1600}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x1600, 0xc00, 0x3000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xc00, 0xc00, 0x2200}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x200, 0xc00, 0x800}},
};
// clang-format on

// 0x08344b10
static const u8 sBigWaveBody[8] = {1, 2, 3, 4, 6, 7, 8, 0};

// 0x080a3db4
static void createWave(const Coords32* at, bool8 big, bool8 right, u8 left) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FEFNIR_WAVE);
    p->coord = *at;
    p->work[0] = big;
    p->work[1] = 0;
    ((struct Shot*)p)->right = right;
    p->work[3] = left;
  }
}

// 0x080a3e1c
static void Wave_Init(struct Shot* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(s->work[0] ? AP_SHEET_Z2_FEFNIR_BIG_WAVE : AP_SHEET_Z2_FEFNIR_WAVE, 0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, p->right);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->work[0]) INIT_BODY(p, &sWave[1], 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Wave_Update(p);
}

// 0x080a3edc
static void Wave_Update(struct Shot* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  UpdateSpriteAnimation(p);
  if (s->work[0]) {
    SetDDP(&p->body, &sWave[sBigWaveBody[(s->motion).cmdIdx]]);
    if (s->mode[1] != 0) {
      if ((s->motion).cmdIdx > 5) s->mode[1]++;
    } else if ((s->motion).cmdIdx > 3) {
      if (s->work[3] != 0) s->work[3]--;
      s->mode[1]++;
    }
  } else if (s->mode[1] != 0) {
    if ((s->motion).cmdIdx > 3) s->mode[1]++;
  } else if ((s->motion).cmdIdx != 0) {
    INIT_BODY(p, &sWave[0], 1, NULL);
    at.x = s->coord.x + (p->right ? PIXEL(8) : -PIXEL(8));
    at.y = s->coord.y;
    if (s->work[3] != 0) {
      s->work[3]--;
      createWave(&at, s->work[0], p->right, s->work[3]);
    }
    s->mode[1]++;
  }
  if (s->mode[1] <= 1) return;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Wave_Die(p);
}

// 0x080a4014
static void Wave_Die(struct Shot* p) {
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(&p->s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 36, fire about him through the jump punch. Harmless.
*/

static void JumpFire_Init(struct Entity* p);
static void JumpFire_Update(struct Entity* p);
static void JumpFire_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2FefnirJumpFireRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)JumpFire_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)JumpFire_Update,
    [ENTITY_DIE] =       (ProjectileFunc)JumpFire_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a4044
static void createJumpFire(struct FefnirFoot* boss) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FEFNIR_JUMP_FIRE);
    p->unk_28 = &boss->s;
    p->work[0] = p->work[1] = 0;
  }
}

// 0x080a408c
static void JumpFire_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  p->texture = TEXTURE_AP_SHEET;
  p->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, JUMP_FIRE(0));
  UpdateSpriteAnimation(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  JumpFire_Update(p);
}

// 0x080a40d4: rising, falling, then out with his landing
static void JumpFire_Update(struct Entity* p) {
  struct Entity* boss = p->unk_28;
  p->coord = boss->coord;
  SET_XFLIP(p, facingRight(boss));
  switch (p->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (boss->mode[1] == FEF_DIVE) p->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, JUMP_FIRE(1));
      p->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if (boss->mode[1] == FEF_PUNCH_LAND) p->mode[1]++;
      break;
    case 3:
      SetSpriteAnimation(p, JUMP_FIRE(2));
      p->mode[1]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) p->mode[1]++;
      break;
  }
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == FEF_HOP || p->mode[1] > 4) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    JumpFire_Die(p);
  }
}

static void JumpFire_Die(struct Entity* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 37, the EX's pillars.
  work0: 0 its mark on the floor, 1 the pillar
  work1: low
*/

static void Pillar_Init(struct Entity* p);
static void Pillar_Update(struct Entity* p);
static void Pillar_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2FefnirPillarRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Pillar_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Pillar_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Pillar_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344b64: tall, low
static const struct Collision sPillar[4] = {
    {DDP, FACTION_ENEMY, 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x1e00, 0x800, 0x3e00}},
    {DRP, FACTION_ENEMY, 0, 5, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xe00, 0x800, 0x1c00}},
    {DRP, FACTION_ENEMY, 0, 5, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

static struct Entity* newPillar(u8 kind, bool8 low) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FEFNIR_PILLAR);
    p->work[0] = kind;
    p->work[1] = low;
  }
  return p;
}

// 0x080a41e4
static void createPillar(const Coords32* at, bool8 low) {
  struct Entity* p = newPillar(0, low);
  if (p != NULL) p->coord = *at;
}

// 0x080a42d8, 0x080a4344
static void Pillar_Init(struct Entity* p) {
  if (p->work[0] == 0) {
    InitNonAffineMotion(p);
    p->texture = TEXTURE_AP_SHEET;
    p->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, PILLAR(0));
    SET_XFLIP(p, FALSE);
    p->coord.y = FUN_08009f6c(p->coord.x, p->coord.y);
  } else {
    if (p->work[1]) {
      InitScalerotMotion2(p);
      (p->spr).mag.x = 256;
      (p->spr).mag.y = 128;
      p->work[2] = 64;
    } else {
      InitNonAffineMotion(p);
      p->work[2] = 48;
    }
    p->texture = TEXTURE_AP_SHEET;
    p->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, PILLAR(2));
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, &sPillar[p->work[1] * 2], 0, NULL);
    (p->spr).oam.priority = 3;
    p->coord = (p->unk_28)->coord;
    PlaySound(SE_Z2_SIGNALOID_FLAME);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Pillar_Update(p);
}

static void Pillar_Die(struct Entity* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// 0x080a441c, 0x080a44d4
static void Pillar_Update(struct Entity* p) {
  if (p->work[0] == 1) {
    UpdateSpriteAnimation(p);
    if (--p->work[2] == 0xFF) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Pillar_Die(p);
    }
    return;
  }
  switch (p->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) p->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, PILLAR(1));
      p->unk_28 = newPillar(1, p->work[1]);
      if (p->unk_28 != NULL) (p->unk_28)->unk_28 = p;
      p->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if (p->unk_28 == NULL || (p->unk_28)->mode[0] > ENTITY_UPDATE) p->mode[1]++;
      break;
    case 3:
      SetSpriteAnimation(p, PILLAR(3));
      p->mode[1]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      if ((p->motion).state != 4) break;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Pillar_Die(p);
      break;
  }
}

// --------------------------------------------
/*
  Zero 2's enemy 38, his fire bomb.
  work0: 0 the bomb, 1 one of its seven shards
  work1: bomb, big: bursts on the floor upward, else in the air downward. Shard, its angle
*/

struct Bomb {
  OBJECT_HDR;
  u8 _b4[16];
};
static_assert(sizeof(struct Bomb) == sizeof(struct Enemy));

static void Bomb_Init(struct Bomb* p);
static void Bomb_Update(struct Bomb* p);
static void Bomb_Die(struct Bomb* p);

// clang-format off
const EnemyRoutine gApZ2FefnirBombRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Bomb_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Bomb_Update,
    [ENTITY_DIE] =       (EnemyFunc)Bomb_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x08340134, 0x0834014c
static const struct Collision sBomb[2] = {
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

static struct Entity* newBomb(struct Entity* parent, u8 kind, u8 work1) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FEFNIR_BOMB);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = work1;
  }
  return p;
}

// 0x0807ae7c
static void createBomb(struct FefnirFoot* boss, bool8 big) { newBomb(&boss->s, 0, big); }

static void burstInto(struct Entity* s, u8 first) {
  u8 i;
  for (i = 0; i < 7; i++) newBomb(s, 1, first + i * 16);
}

// 0x0807af2c, 0x0807affc
static void Bomb_Init(struct Bomb* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SET_XFLIP(p, FALSE);
  if (s->work[0] == 0) {
    SetSpriteAnimation(p, SHOT(2));
    UpdateSpriteAnimation(p);
    INIT_BODY(p, &sBomb[0], 1, NULL);
    s->coord.x = parent->coord.x + (facingRight(parent) ? PIXEL(21) : -PIXEL(21));
    s->d.x = facingRight(parent) ? PIXEL(1) : -PIXEL(1);
    s->coord.y = parent->coord.y - PIXEL(46);
    s->d.y = -0x580;
    s->work[2] = 30;
  } else {
    SetSpriteAnimation(p, SHOT(4));
    UpdateSpriteAnimation(p);
    INIT_BODY(p, &sBomb[1], 1, NULL);
    s->coord = parent->coord;
    s->d.x = -(COS(s->work[1]) * 3);
    s->d.y = -(SIN(s->work[1]) * 3);
    s->work[2] = 96;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Bomb_Update(p);
}

// 0x0807b0d8, 0x0807b1c4
static void Bomb_Update(struct Bomb* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->work[0] == 1) {
    if (--s->work[2] == 0xFF || ((p->body).status & 0x400100) || FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      Bomb_Die(p);
    }
    return;
  }
  s->d.y += 64;
  if (s->work[1]) {
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    burstInto(s, 16);
  } else {
    if (--s->work[2] != 0xFF) return;
    burstInto(s, 144);
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
}

// 0x0807b22c, 0x0807b274
static void Bomb_Die(struct Bomb* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SHOT(3));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(s)) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's VFX 38, his aura: his own frame behind him, pulsing, all one color.
*/

static void Aura_Init(struct Entity* p);
static void Aura_Update(struct Entity* p);
static void Aura_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2FefnirAuraRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Aura_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Aura_Update,
    [ENTITY_DIE] =       (VFXFunc)Aura_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b6780
static struct Entity* createAura(struct FefnirFoot* boss) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_AURA);
    p->unk_28 = &boss->s;
    p->work[0] = p->work[1] = 0;
  }
  return p;
}

// 0x080b67d4
static void Aura_Init(struct Entity* p) {
  InitScalerotMotion1(p);
  p->renderPrio = 25;
  ForceEntityPalette(p, 13);
  p->flags |= DISPLAY;
  p->work[3] = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Aura_Update(p);
}

// 0x080b681c
static void Aura_Update(struct Entity* p) {
  struct Entity* boss = p->unk_28;
  p->coord = boss->coord;
  p->work[3] += 4;
  (p->spr).mag.x = (p->spr).mag.y = ((SIN(p->work[3]) + 256) >> 4) + 256;
  (p->spr).oam.tileNum = (boss->spr).oam.tileNum;
  (p->spr).sprites = (boss->spr).sprites;
  (p->spr).spriteIdx = (boss->spr).spriteIdx;
  SET_XFLIP(p, facingRight(boss));
  if (boss->mode[0] > ENTITY_UPDATE || p->work[1] != 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Aura_Die(p);
  }
}

// 0x080b68f0
static void Aura_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's VFX 65, flames about him through his EX.
  work0: 1 Fefnir's, 2 Leviathan's
*/

static void Ex_Init(struct Entity* p);
static void Ex_Update(struct Entity* p);
static void Ex_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2FefnirExRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Ex_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Ex_Update,
    [ENTITY_DIE] =       (VFXFunc)Ex_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

extern const PlttAnimData gApZ2Plant2_PlttAnim91, gApZ2Ice2_PlttAnim92;
extern const AnimCmd* const gApZ2Plant2_PlttAnimScript91[];
extern const AnimCmd* const gApZ2Ice2_PlttAnimScript92[];

#define EX_PLTT_ANIM(p) (0x8000 | (90 + (p)->work[0]))

// 0x080bd70c
struct Entity* ApZ2CreateEx(struct Entity* boss, u8 kind) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_EX);
    p->unk_28 = boss;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

// 0x080bd760
static void Ex_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  p->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(p);
  SetMotion(p, MOTION(DM211_Z2_FEFNIR_EX, 0));
  SET_XFLIP(p, FALSE);
  if (p->work[0] == 2) {
    ApStartPaletteAnimation(EX_PLTT_ANIM(p), &gApZ2Ice2_PlttAnim92, gApZ2Ice2_PlttAnimScript92, 0x340);
  } else {
    ApStartPaletteAnimation(EX_PLTT_ANIM(p), &gApZ2Plant2_PlttAnim91, gApZ2Plant2_PlttAnimScript91, 0x340);
  }
  p->renderPrio = 25;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ex_Update(p);
}

// 0x080bd7dc: flare up, then burn until he's done
static void Ex_Update(struct Entity* p) {
  p->coord = (p->unk_28)->coord;
  if (p->work[0] == 2) p->coord.y += 0x1600;
  if (p->mode[1] == 0) {
    UpdateEntityAnim(p);
    if (IsSpriteAnimEnd(p)) setMode(p, 1);
  } else {
    if (p->mode[2] == 0) {
      SetMotion(p, MOTION(DM211_Z2_FEFNIR_EX, 1));
      p->mode[2]++;
    }
    UpdateEntityAnim(p);
    if (p->work[1] != 0) SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
  StepPaletteAnimation(EX_PLTT_ANIM(p));
}

// 0x080bd820
static void Ex_Die(struct Entity* p) {
  if (p->mode[2] == 0) {
    SetMotion(p, MOTION(DM211_Z2_FEFNIR_EX, 2));
    p->mode[2]++;
  }
  UpdateEntityAnim(p);
  if (!IsSpriteAnimEnd(p)) return;
  RemovePaletteAnimation(EX_PLTT_ANIM(p));
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

#endif  // AP
