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
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's mind-controlled Resistance soldier, enemy 43.
*/

enum {
  SOLDIER_IDLE,
  SOLDIER_SHOOT,
  SOLDIER_TURN,
  SOLDIER_KNEEL,
  SOLDIER_STAND,
  SOLDIER_HIT,
  SOLDIER_RECOIL,
};

// Animations in the sheet
#define ANIM(n) MOTION(AP_SHEET_Z2_SOLDIER, n)
#define ANIM_IDLE ANIM(0)
#define ANIM_SHOOT ANIM(1)
#define ANIM_HIT ANIM(2)
#define ANIM_KNEEL ANIM(3)
#define ANIM_STAND ANIM(4)

// The sheet faces right
#define FACING_LEFT(p) (((p)->s.flags & X_FLIP) != 0)

static const struct Collision sCollisions[2];
static const struct Collision sKneeling[2];
static const struct Collision sHarmless[2];
static const Coords32 sElementCoord = {0, -PIXEL(24)};

static void Soldier_Init(struct Enemy* p);
static void Soldier_Update(struct Enemy* p);
static void Soldier_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2SoldierRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Soldier_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Soldier_Update,
    [ENTITY_DIE] =       (EnemyFunc)Soldier_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Enemy* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static bool8 facingZero(struct Enemy* p) { return FACING_LEFT(p) != ((p->s).coord.x < (pZero2->s).coord.x); }

// 0x0807cf48
static void Soldier_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x);  // Back turned to Zero
  SetSpriteAnimation(p, ANIM_IDLE);
  UpdateSpriteAnimation(p);
  (p->s).flags |= DISPLAY | FLIPABLE;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  (p->s).unk_2c = NULL;
  INIT_BODY(p, sCollisions, 6, NULL);
  Soldier_Update(p);
}

// 0x0807d7e0:
static void Soldier_Decide(struct Enemy* p) {
  s32 dx = (pZero2->s).coord.x - (p->s).coord.x;
  s32 dy = (pZero2->s).coord.y - (p->s).coord.y;
  if ((u32)(dx + PIXEL(104)) > PIXEL(208) || (u32)(dy + PIXEL(64)) > PIXEL(128)) {
    if (facingZero(p) || (RANDOM(RNG_0202f388) & 15) <= 3) {
      setMode(p, SOLDIER_TURN);
    } else {
      setMode(p, SOLDIER_IDLE);
    }
  } else {
    setMode(p, facingZero(p) ? SOLDIER_SHOOT : SOLDIER_TURN);
  }
}

static const EnemyFunc sUpdates[6];
static void Soldier_Recoil(struct Enemy* p);

// 0x0807d078
static void Soldier_Update(struct Enemy* p) {
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && (p->s).mode[1] != SOLDIER_RECOIL) setMode(p, SOLDIER_RECOIL);
  if ((p->s).mode[1] == SOLDIER_RECOIL) {
    Soldier_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Soldier_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if ((p->s).unk_2c != NULL) {
      (p->s).unk_2c = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  if (status & BODY_STATUS_WHITE) {
    PlaySound(SE_Z2_SOLDIER_HURT);
    if ((p->s).unk_2c == NULL) {
      (p->s).unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    }
    setMode(p, SOLDIER_HIT);
  }
  if ((p->s).unk_2c != NULL && IsDead((p->s).unk_2c)) (p->s).unk_2c = NULL;

  (sUpdates[(p->s).mode[1]])((void*)p);
}

// 0x0807d184
static void Soldier_Idle(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_IDLE);
    SetDDP(&p->body, sCollisions);
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++(p->s).work[2] > 63) Soldier_Decide(p);
}

static void shoot(struct Enemy* p) {
  bool8 left = FACING_LEFT(p);
  Coords32 c;
  SetSpriteAnimation(p, ANIM_SHOOT);
  c.x = (p->s).coord.x + (left ? -PIXEL(22) : PIXEL(22));
  c.y = (p->s).coord.y - PIXEL(18);
  if (CreateLemon(&c, 0x240, left ? 0 : 128) != NULL) PlaySound(SE_Z2_SOLDIER_SHOT);
}

// 0x0807d1cc: 
static void Soldier_Shoot(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_IDLE);
    SetDDP(&p->body, sCollisions);
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  switch ((p->s).work[2]) {
    case 0:
    case 5:
    case 10:
      shoot(p);
      break;
    case 4:
    case 9:
    case 14:
      SetSpriteAnimation(p, ANIM_IDLE);
      break;
    case 128:
      Soldier_Decide(p);
      return;
  }
  UpdateSpriteAnimation(p);
  (p->s).work[2]++;
}

// 0x0807d2a4
static void Soldier_Turn(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SET_XFLIP(p, !FACING_LEFT(p));
    SetSpriteAnimation(p, ANIM_IDLE);
    SetDDP(&p->body, sCollisions);
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++(p->s).work[2] > 23) Soldier_Decide(p);
}

// 0x0807d324: on one knee for at least 96 frames, and harmless
static void Soldier_Kneel(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_KNEEL);
    SetDDP(&p->body, sKneeling);
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (p->s).work[2]++;
  if (IsSpriteAnimEnd(p) && (p->s).work[2] > 95) setMode(p, SOLDIER_STAND);
}

// 0x0807d37c
static void Soldier_Stand(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_STAND);
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(p, SOLDIER_IDLE);
}

// 0x0807d3b4:
static void Soldier_Hit(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_HIT);
    SetDDP(&p->body, s->unk_2c != NULL ? sHarmless : sCollisions);
    s->d.y = 0;
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    s->coord.y += s->d.y;
    s->d.y += 0x40;
    if (s->d.y > 0x700) s->d.y = 0x700;
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2]++;
    }
  }
  if (s->unk_2c != NULL) return;
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(p, SOLDIER_KNEEL);
}

// Same as the Pantheon Hunter's, 0x08064cac
static void Soldier_Recoil(struct Enemy* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Soldier_Die(p);
  }
}

static const EnemyFunc sUpdates[6] = {
    [SOLDIER_IDLE] = (EnemyFunc)Soldier_Idle,
    [SOLDIER_SHOOT] = (EnemyFunc)Soldier_Shoot,
    [SOLDIER_TURN] = (EnemyFunc)Soldier_Turn,
    [SOLDIER_KNEEL] = (EnemyFunc)Soldier_Kneel,
    [SOLDIER_STAND] = (EnemyFunc)Soldier_Stand,
    [SOLDIER_HIT] = (EnemyFunc)Soldier_Hit,
};

static void smokeNearby(struct Enemy* p, u8 kind) {
  Coords32 c;
  c.x = (p->s).coord.x + (((RANDOM(RNG_0202f388) & 15) - 8) << 8);
  c.y = (p->s).coord.y + (((RANDOM(RNG_0202f388) & 15) - 8) << 8) - PIXEL(16);
  CreateSmoke(kind, &c);
}

// 0x0807d4fc, 0x0807d670 costs the mission 2 points
static void Soldier_Die(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    PlaySound(SE_Z2_SOLDIER_HURT);
    SetSpriteAnimation(p, ANIM_HIT);
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++(p->s).work[2] < 8) return;

  PlaySound(SE_ZAKO_EXPLODE);
  smokeNearby(p, 1);
  smokeNearby(p, 2);
  TryDropItem(1, &(p->s).coord);
  gScore.missionPoint = (gScore.missionPoint > 2) ? gScore.missionPoint - 2 : 0;
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0x1500, 0x1000, 0x2a00}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1500, 0x1000, 0x2a00}},
};

static const struct Collision sKneeling[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x400, -0x900, 0x1800, 0x1200}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x400, -0x900, 0x1800, 0x1200}},
};

static const struct Collision sHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1500, 0x1000, 0x2a00}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1500, 0x1000, 0x2a00}},
};
// clang-format on

#endif  // AP
