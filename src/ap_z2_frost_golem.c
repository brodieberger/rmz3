#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "random.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's frost Golem, boss 21.
*/

struct FrostGolem {
  OBJECT_HDR;
  s32 homeX;        // 0xB4
  s32 homeY;        // 0xB8
  u8 _bc;
  u8 sway;          // 0xBD
  bool8 armsOut[2]; // 0xBE
  u16 dying;        // 0xC0
  u8 turn;          // 0xC2
  u8 armSway;       // 0xC3
  s32 left;         // 0xC4
  s32 right;        // 0xC8
  u8 _cc[3];
  u8 lastAttack;    // 0xCF
  s16 sound;        // 0xD0
  u8 _d2[18];
};
static_assert(sizeof(struct FrostGolem) == sizeof(struct Boss));

enum { FROST_WAIT, FROST_STIR, FROST_NOP, FROST_CHOOSE, FROST_PAUSE, FROST_WIND, FROST_BREATH, FROST_CLOSE,
       FROST_ARMS, FROST_LEAVE, FROST_RETURN };

#define BODY(n) MOTION(AP_SHEET_Z2_FROST_GOLEM, (n))
#define ICE(n) MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, (n))

#define BOSS(p) ((struct FrostGolem*)(p)->s.unk_28)

static const struct Collision sCollisions[2];
static const struct Collision sArmCollisions[4];
static const struct Collision sBallCollisions[2];
static const struct Collision sShardCollisions[2];
static const struct SlashedEnemy sBallGibs[4];
static const struct SlashedEnemy sShardGibs[2];
static const struct Coord sElementCoord = {0, -PIXEL(48)};

static const struct PreloadEntity sSheets[3] = {
    {AP_SHEET_Z2_FROST_GOLEM, 0, 512, 4, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_FROST_GOLEM_ICE, 0, 512 + AP_SHEET_Z2_FROST_GOLEM_TILES, 5, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_FROST_GOLEM_FOOT, 0, 512 + AP_SHEET_Z2_FROST_GOLEM_TILES + AP_SHEET_Z2_FROST_GOLEM_ICE_TILES, 7, 0, AP_PRELOAD_SHEET, 0},
};

static void Frost_Init(struct FrostGolem* p);
static void Frost_Update(struct FrostGolem* p);
static void Frost_Die(struct FrostGolem* p);
static void createEnemy(u8 id, struct Entity* boss, u8 work0, u8 work1);
static void createBreath(const Coords32* at, u8 xflip);

// clang-format off
const BossRoutine gApZ2FrostGolemRoutine = {
    [ENTITY_INIT] =      (BossFunc)Frost_Init,
    [ENTITY_UPDATE] =    (BossFunc)Frost_Update,
    [ENTITY_DIE] =       (BossFunc)Frost_Die,
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

static bool8 dying(struct Entity* e) { return e->mode[0] > ENTITY_UPDATE; }

static void slideBack(struct Entity* s) {
  u8 i;
  s->d.x = 0;
  for (i = 0; i < 64; i++) {
    s->d.x += s->unk_coord.x;
    s->coord.x += s->d.x;
  }
}

// 0x08062f78
static void Frost_Init(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  u8 i;
  for (i = 0; i < 3; i++) {
    ApLoadSheet(&sSheets[i]);
  }
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, BODY(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, s->work[1] != 0 ? 32 : 16);
  p->left = s->coord.x;
  p->right = s->coord.x + PIXEL(352);
  p->homeY = FUN_08009f6c(s->coord.x + PIXEL(160), s->coord.y) - PIXEL(16);
  s->coord.x += PIXEL(240);
  p->homeX = s->coord.x;
  p->sway = 0;
  p->armSway = 0;
  p->armsOut[0] = p->armsOut[1] = FALSE;
  p->turn = 0;
  p->lastAttack = 0;
  s->unk_2c = NULL;
  p->sound = -1;
  s->unk_coord.x = 8;
  slideBack(s);
  ApZ2CreateGolemFeet(s, 2);
  createEnemy(ENEMY_Z2_FROST_ARM, s, 0, 0);
  createEnemy(ENEMY_Z2_FROST_ARM, s, 1, 0);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Frost_Update(p);
}

static const BossFunc sStates[11];

// 0x08063170
static void Frost_Update(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Frost_Die(p);
    return;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(10, (Object*)p, &sElementCoord);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  (sStates[s->mode[1]])((struct Boss*)p);
  p->sway += 2;
  p->armSway += 2;
  s->coord.y = p->homeY - SIN(p->sway) * 2;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    p->sway = 0;
  }
}

// 0x08063258
static void Frost_Die(struct FrostGolem* p) {
  if ((p->s).mode[2] == 0 && p->sound != -1) {
    StopSound(p->sound);
    p->sound = -1;
  }
  ApZ2GolemDie(&p->s, BODY(0));
}

// 0x080633dc: slides in on script's flag
static void Frost_Wait(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[3]) {
    case 0:
      if (!(s->scriptEntity->flags & 1)) break;
      PlaySound(SE_Z2_GOLEM_SLIDE);
      s->mode[3]++;
      break;
    case 1:
      s->d.x -= s->unk_coord.x;
      s->coord.x -= s->d.x;
      if (s->d.x == 0) {
        s->coord.x = p->homeX;
        s->mode[3]++;
      }
      break;
    case 2:
      setMode(s, FROST_STIR);
      break;
  }
}

// 0x08063450
static void Frost_Stir(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, FROST_PAUSE);
}

static void Frost_Nop(struct FrostGolem* p UNUSED) {}

// 0x08063484
static void Frost_Choose(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  u8 attack;
  UpdateSpriteAnimation(p);
  if (p->turn > 1) {
    attack = FROST_LEAVE;
  } else if (p->turn == 1) {
    if (RANDOM(RNG_0202f388) & 1) {
      attack = FROST_LEAVE;
    } else {
      attack = p->lastAttack == FROST_ARMS ? FROST_WIND : FROST_ARMS;
    }
  } else {
    attack = (RANDOM(RNG_0202f388) & 1) ? FROST_ARMS : FROST_WIND;
    p->lastAttack = attack;
  }
  p->turn = (p->turn + 1) % 3;
  if (attack == FROST_LEAVE) p->turn = 0;
  setMode(s, attack);
}

// 0x0806353c
static void Frost_Pause(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FROST_CHOOSE);
}

// 0x0806357c
static void Frost_Wind(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(1));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, FROST_BREATH);
}

// 0x080635b8
static void Frost_Breath(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  bool8 flip = (s->flags & X_FLIP) != 0;
  Coords32 at;
  if (s->mode[2] == 0) {
    createEnemy(ENEMY_Z2_FROST_BALL, s, 0, flip);
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    s->work[2] = 0;
    s->work[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->work[2] & 3) == 0) {
    at.x = s->coord.x + (flip ? PIXEL(8) : -PIXEL(8));
    at.y = s->coord.y - PIXEL(94);
    createBreath(&at, flip);
  }
  if (s->work[2]++ > 48) setMode(s, FROST_CLOSE);
}

// 0x08063654
static void Frost_Close(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(3));
    StopSound(p->sound);
    p->sound = -1;
    s->work[2] = 96;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FROST_PAUSE);
}

// 0x080636ac
static void Frost_Arms(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    p->armsOut[0] = p->armsOut[1] = TRUE;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!p->armsOut[0] && !p->armsOut[1]) setMode(s, FROST_PAUSE);
}

// 0x080636f0
static void Frost_Leave(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    s->d.x = 0;
    PlaySound(SE_Z2_GOLEM_SLIDE);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->flags & X_FLIP) {
    if (s->d.x < 0x200) s->d.x += 8;
    s->coord.x += s->d.x;
    if (s->coord.x > p->right + PIXEL(64)) setMode(s, FROST_RETURN);
  } else {
    if (s->d.x > -0x200) s->d.x -= 8;
    s->coord.x += s->d.x;
    if (s->coord.x < p->left - PIXEL(64)) setMode(s, FROST_RETURN);
  }
}

// 0x08063790
static void Frost_Return(struct FrostGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    SET_XFLIP(p, !(s->flags & X_FLIP));
    if (s->flags & X_FLIP) {
      s->coord.x = p->left + PIXEL(48);
      s->unk_coord.x = -8;
    } else {
      s->coord.x = p->right - PIXEL(48);
      s->unk_coord.x = 8;
    }
    slideBack(s);
    p->sway = 0;
    p->armSway = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->d.x -= s->unk_coord.x;
  s->coord.x -= s->d.x;
  if (s->d.x == 0) setMode(s, FROST_CHOOSE);
}

// clang-format off
static const BossFunc sStates[11] = {
    (BossFunc)Frost_Wait, (BossFunc)Frost_Stir, (BossFunc)Frost_Nop, (BossFunc)Frost_Choose, (BossFunc)Frost_Pause,
    (BossFunc)Frost_Wind, (BossFunc)Frost_Breath, (BossFunc)Frost_Close, (BossFunc)Frost_Arms, (BossFunc)Frost_Leave,
    (BossFunc)Frost_Return,
};
// clang-format on

// 0x0808841c, 0x08088a1c, 0x08088de0
static void createEnemy(u8 id, struct Entity* boss, u8 work0, u8 work1) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, id);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = boss;
    p->work[0] = work0;
    p->work[1] = work1;
  }
}

// --------------------------------------------
// Zero 2's enemy 62

static void FArm_Init(struct Enemy* p);
static void FArm_Update(struct Enemy* p);
static void FArm_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2FrostArmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)FArm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)FArm_Update,
    [ENTITY_DIE] =       (EnemyFunc)FArm_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08088478
static void FArm_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] != 0) {
    SetSpriteAnimation(p, BODY(4));
    s->renderPrio = 25;
  } else {
    SetSpriteAnimation(p, BODY(5));
    (s->spr).oam.priority = 1;
  }
  UpdateSpriteAnimation(p);
  s->flags2 |= WHITE_PAINTABLE;
  s->invincibleID = boss->uniqueID;
  INIT_BODY(p, &sArmCollisions[s->work[0] * 2], 1, NULL);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  FArm_Update(p);
}

static u8 armBob(struct Enemy* p) {
  return BOSS(p)->armSway + ((p->s).work[0] != 0 ? 64 : 192);
}

static void followBoss(struct Enemy* p, s32 reach) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  SET_XFLIP(p, (boss->flags & X_FLIP) != 0);
  s->coord.x = boss->coord.x;
  s->coord.y = boss->coord.y - SIN(armBob(p)) * reach;
}

// 0x08088894
static void FArm_Idle(struct Enemy* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (BOSS(p)->armsOut[s->work[0] != 0 ? 0 : 1] && (armBob(p) & 127) == 0) {
    s->mode[1] = 1;
    s->mode[2] = 0;
  }
  followBoss(p, 2);
}

// 0x08088930
static void FArm_Throw(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->work[3] = s->work[0] * 32 + 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followBoss(p, 32);
  if (s->work[2] < 208 && --s->work[3] == 0xFF) {
    s->work[3] = 56;
    createEnemy(ENEMY_Z2_FROST_SHARD, s->unk_28, s->work[0], (s->flags & X_FLIP) != 0);
    PlaySound(SE_Z2_FROST_THROW);
  }
  if (++s->work[2] == 0) {
    BOSS(p)->armsOut[s->work[0] != 0 ? 0 : 1] = FALSE;
    s->mode[1] = 0;
    s->mode[2] = 0;
  }
}

// 0x0808852c
static void FArm_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (dying(s->unk_28)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    FArm_Die(p);
    return;
  }
  if (s->mode[1] == 0) {
    FArm_Idle(p);
  } else {
    FArm_Throw(p);
  }
}

// x from arm, by arm, as frosted side faces
static const s16 sArmSmoke[2][5] = {{0x200, 0x1600, 0x2800, 0x1000, 0x1A00}, {-0x2600, -0x1200, 0, -0x1800, -0xE00}};
static const s16 sArmSmokeUp[5] = {0x2800, 0x3200, 0x2800, 0x2000, 0x3200};

// 0x08088574: shakes, drops, bursts on floor
static void FArm_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  s8 side = (s->flags & X_FLIP) ? -1 : 1;
  Coords32 at;
  u8 i;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = s->work[0] != 0 ? 32 : 0;
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0) {
    s->coord.y += (s->work[2] & 3) == 0 ? 128 : -128;
    if (--s->work[2] == 0xFF) s->mode[1]++;
    return;
  }
  s->d.y += 64;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y - 0x2A00) == 0) return;
  for (i = 0; i < 5; i++) {
    at.x = s->coord.x + sArmSmoke[s->work[0] != 0 ? 1 : 0][i] * side;
    at.y = s->coord.y - ((RANDOM(RNG_0202f388) & 0x7FF) + sArmSmokeUp[i]);
    CreateSmoke(i < 3 ? 1 : 2, &at);
  }
  PlaySound(SE_Z2_ICICLE_BREAK);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's enemy 63, rolling snowball

static void Ball_Init(struct Enemy* p);
static void Ball_Update(struct Enemy* p);
static void Ball_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2FrostBallRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Ball_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Ball_Update,
    [ENTITY_DIE] =       (EnemyFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08088a78
static void Ball_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct FrostGolem* boss = (struct FrostGolem*)s->unk_28;
  bool8 right = ((boss->s).flags & X_FLIP) != 0;
  InitRotatableMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(2));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, right);
  INIT_BODY(p, sBallCollisions, 12, NULL);
  s->unk_coord.x = right ? boss->right + PIXEL(48) : boss->left - PIXEL(48);
  s->coord.x = (boss->s).coord.x + (right ? PIXEL(8) : -PIXEL(8));
  s->d.x = right ? 0x100 : -0x100;
  s->coord.y = (boss->s).coord.y - PIXEL(94);
  s->work[2] = 0;
  (s->spr).mag.x = 0;
  (s->spr).mag.y = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Ball_Update(p);
}

// 0x08088b8c
static void Ball_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  bool8 right = (s->flags & X_FLIP) != 0;
  s32 y, v;
  if (((p->body).status & BODY_STATUS_DEAD) || dying(s->unk_28)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Ball_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      if (s->work[2]++ & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      (s->spr).mag.x += 8;
      (s->spr).mag.y += 8;
      s->coord.x += s->d.x;
      if ((s->spr).mag.x > 255) {
        s->flags |= DISPLAY;
        s->d.x = 0;
        s->d.y = 0;
        s->mode[1]++;
      }
      break;
    case 1:
      s->d.y += 64;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y + 0x1B00) == 0) break;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - 0x1B00;
      s->d.x = right ? 0x200 : -0x200;
      s->unk_coord.y = right ? 8 : -8;
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 2:
      if ((s->work[2]++ & 63) == 0) PlaySound(SE_Z2_SNOWBALL_ROLL);
      y = s->coord.y;
      s->coord.y = FUN_08009f6c(s->coord.x, y) - 0x1B00;
      v = s->d.x < 0 ? -s->d.x : s->d.x;
      if (y < s->coord.y) {
        if (v < 0x300) s->d.x += s->unk_coord.y;
      } else if (y > s->coord.y && v > 0x100) {
        s->d.x -= s->unk_coord.y;
      }
      s->coord.x += s->d.x;
      s->angle -= (s->d.x < 0 ? -s->d.x : s->d.x) >> 8;
      if (right ? s->coord.x > s->unk_coord.x : s->coord.x < s->unk_coord.x) {
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

// 0x08088d4c
static void Ball_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  u8 flip = s->flags & X_FLIP;
  u8 i;
  PlaySound(SE_Z2_SNOWBALL_BURST);
  for (i = 0; i < 4; i++) {
    useSheet(CreateSlashedEnemy(&s->coord, &sBallGibs[i], 0, flip));
  }
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's enemy 64, thrown by arm.
// work0: arm
// work1: facing right

static void Shard_Init(struct Enemy* p);
static void Shard_Update(struct Enemy* p);
static void Shard_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2FrostShardRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Shard_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Shard_Update,
    [ENTITY_DIE] =       (EnemyFunc)Shard_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08088e38
static void Shard_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(3));
  SET_XFLIP(p, s->work[1]);
  INIT_BODY(p, sShardCollisions, 8, NULL);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Shard_Update(p);
}

// 0x08088ed8
static void Shard_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s32 v;
  if (((p->body).status & BODY_STATUS_DEAD) || dying(boss)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Shard_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0) {
    if (s->flags & X_FLIP) {
      s->coord.x = boss->coord.x + (s->work[0] != 0 ? 0x3400 : 0xA00);
    } else {
      s->coord.x = boss->coord.x + (s->work[0] != 0 ? -0x3400 : -0xA00);
    }
    s->coord.y = boss->coord.y - 0x2A00;
    if ((s->motion).state == ANIM_END) {
      s->unk_coord.x = (s->flags & X_FLIP) ? 16 : -16;
      s->d.x = 0;
      s->work[2] = 192;
      s->mode[1]++;
    }
    return;
  }
  v = s->d.x < 0 ? -s->d.x : s->d.x;
  if (v < 0x400) s->d.x += s->unk_coord.x;
  s->coord.x += s->d.x;
  if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x08088fe8
static void Shard_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  u8 flip = s->flags & X_FLIP;
  PlaySound(SE_Z2_ICE_BREAK);
  useSheet(CreateSlashedEnemy(&s->coord, &sShardGibs[0], 0, flip));
  useSheet(CreateSlashedEnemy(&s->coord, &sShardGibs[1], 0, flip));
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's VFX 39, breath

static void Breath_Init(struct Entity* p);
static void Breath_Update(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2FrostBreathRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Breath_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Breath_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080ba788
static void createBreath(const Coords32* at, u8 xflip) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FROST_BREATH);
    p->coord = *at;
    p->work[1] = xflip;
  }
}

// 0x080ba828
static void Breath_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  useSheet(p);
  p->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(5));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, p->work[1]);
  p->d.x = p->work[1] ? (s32)(RANDOM(RNG_0202f388) & 255) + 128 : -128 - (s32)(RANDOM(RNG_0202f388) & 255);
  p->d.y = 255 - (s32)(RANDOM(RNG_0202f388) & 511);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Breath_Update(p);
}

// 0x080ba924
static void Breath_Update(struct Entity* p) {
  UpdateSpriteAnimation(p);
  p->coord.x += p->d.x;
  p->coord.y += p->d.y;
  if ((p->motion).state == ANIM_END) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------

// clang-format off
static const struct Collision sCollisions[2] = {
    /* 0x833d5f0 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 1, 0x00000001, {0x200, -0x2000, 0x3200, 0x2c00}},
    /* 0x833d608 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 0, 0x00000000, {0x600, -0x4c00, 0x3400, 0x2c00}},
};

static const struct Collision sArmCollisions[4] = {
    /* 0x834177c */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x1500, -0x2b00, 0x3200, 0x1400}},
    /* 0x8341794 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    /* 0x83417ac */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x1300, -0x2c00, 0x3200, 0x1400}},
    /* 0x83417c4 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sBallCollisions[2] = {
    /* 0x83417f0 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2c00, 0x2c00}},
    /* 0x8341808 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x3600, 0x3600}},
};

static const struct Collision sShardCollisions[2] = {
    /* 0x83418a4 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 1, 0x00000001, {-0x800, 0x0, 0x2800, 0x800}},
    /* 0x83418bc */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {-0x800, 0x0, 0x3600, 0x1200}},
};

static const struct SlashedEnemy sBallGibs[4] = {
    /* 0x8341820 */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 6), {0x40, 0x70}, {-3072, -3072}, {-512, -1023}, {255, 255}, {0, 64}, {0x0, 0x0}, {0}},
    /* 0x834183c */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 7), {0x40, 0x70}, {3584, 3584}, {256, -1023}, {255, 255}, {0, 64}, {0x0, 0x0}, {0}},
    /* 0x8341858 */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 8), {0x40, 0x70}, {3584, 3584}, {-512, -1023}, {255, 255}, {0, 64}, {0x0, 0x0}, {0}},
    /* 0x8341874 */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 9), {0x40, 0x70}, {2048, -3584}, {256, -1023}, {255, 255}, {0, 64}, {0x0, 0x0}, {0}},
};

static const struct SlashedEnemy sShardGibs[2] = {
    /* 0x83418d4 */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 10), {0x40, 0x70}, {-5120, 0}, {256, -1024}, {255, 255}, {0, 64}, {0x0, 0x0}, {0}},
    /* 0x83418f0 */ {MOTION(AP_SHEET_Z2_FROST_GOLEM_ICE, 11), {0x41, 0x70}, {-512, 0}, {0, -1280}, {0, 255}, {0, 64}, {0x0, 0x0}, {0}},
};
// clang-format on

#endif
