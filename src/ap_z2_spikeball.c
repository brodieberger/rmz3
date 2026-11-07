#include "ap.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's spiked ball, enemy 2.
  work0:
    0: sits
    1: rolls towards Zero
*/

struct Ball {
  OBJECT_HDR;
  u8 lastMove;      // 0xB4
  u8 repeats;       // 0xB5
  u8 scriptStep;    // 0xB6
  s8 halfHeight;    // 0xB7, middle to floor
  bool8 pulled;     // 0xB8
  u8 _b9[3];
  u16 turned;       // 0xBC, roll's progress through one turn, 0x4000
  u16 peak;         // 0xBE, how far it had turned at full speed
  u16 speed;        // 0xC0
  s8 dir;           // 0xC2
  bool8 throwing;   // 0xC3
};
static_assert(sizeof(struct Ball) == sizeof(struct Enemy));

// Split in two, reuses first three for its roll
#define rollAngle lastMove
#define rollStep repeats
#define airborne scriptStep

enum {
  BALL_FALL,
  BALL_SIT,
  BALL_ROLL,
  BALL_THROW,
  BALL_RECOIL,
  BALL_DECIDE = 255,
};

enum {
  BALL_BURST,
  BALL_BURST_OPEN,
  BALL_SPLIT,
  BALL_SPLIT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_SPIKEBALL, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

// Animation script: (motion, frames) pairs ending in a pair with no frames
struct ScriptStep {
  motion_t motion;
  u16 frames;
};

static const struct ScriptStep sRollStart[4] = {{ANIM(1), 1}, {ANIM(2), 4}, {ANIM(0), 4}, {0, 0}};
static const struct ScriptStep sRollEnd[4] = {{ANIM(0), 4}, {ANIM(3), 4}, {ANIM(1), 16}, {0, 0}};
static const struct ScriptStep sThrow[5] = {{ANIM(1), 4}, {ANIM(4), 16}, {ANIM(7), 32}, {ANIM(5), 16}, {0, 0}};

static const struct Collision sCollisions[2];
static const struct Collision sHarmless;
static const struct SlashedEnemy sGibs[5];
static const struct SlashedEnemy sOpenGibs[5];
static const struct SlashedEnemy sHalfGibs[2];
static const Coords32 sElementCoord = {0, 0};

static u16 Ball_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Ball_Init(struct Ball* p);
static void Ball_Update(struct Ball* p);
static void Ball_Die(struct Ball* p);
static void createRocks(struct Ball* ball, Coords32* c, s32 speed);
static void createHalf(struct Ball* ball, s32 x, u8 kind);

// clang-format off
const EnemyRoutine gApZ2SpikeballRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Ball_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Ball_Update,
    [ENTITY_DIE] =       (EnemyFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Ball* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static bool8 solid(s32 x, s32 y) { return FUN_080098a4(x, y) != 0; }

// 0x08068800: lands on a floor or under a ceiling. Returns TRUE when standing or it hit its
// head.
static bool8 stepVertical(struct Entity* s, s32 half) {
  s32 x = s->coord.x;
  s32 y = s->coord.y + s->d.y;
  half <<= 8;
  if (s->d.y > 0 && solid(x, y + half)) {
    s->coord.y = FUN_08009f6c(x, y + half) - half;
    s->d.y = 0;
    return TRUE;
  }
  if (s->d.y < 0 && solid(x, y - half)) {
    s->coord.y = FUN_0800a134(x, y - half) + half;
    s->d.y = 0;
    return TRUE;
  }
  if (s->d.y == 0) {
    if (solid(x, y + half + PIXEL(1))) {
      s->coord.y = FUN_08009f6c(x, y + half + PIXEL(1)) - half;
      return TRUE;
    }
  } else {
    s->coord.y = y;
  }
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  return FALSE;
}

// 0x080688b4: stops half px short of a wall. Returns TRUE when it hit one.
static bool8 stepHorizontal(struct Entity* s, s32 half) {
  s32 x = s->coord.x + s->d.x;
  s32 y = s->coord.y;
  half <<= 8;
  if (s->d.x < 0 && solid(x - half, y)) {
    s->coord.x = FUN_0800a31c(x - half, y) + half;
    return TRUE;
  }
  if (s->d.x > 0 && solid(x + half, y)) {
    s->coord.x = FUN_0800a22c(x + half, y) - half;
    return TRUE;
  }
  s->coord.x = x;
  return FALSE;
}

static bool8 onGround(struct Ball* p) {
  return solid((p->s).coord.x, (p->s).coord.y + ((p->halfHeight + 1) << 8));
}

static void Ball_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = p->coord.x >= (pZero2->s).coord.x;
  }
}

// 0x0806773c
static void Ball_Init(struct Ball* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(p, s->work[0] ? BALL_ROLL : BALL_SIT);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(1));
  UpdateEntityAnim(s);
  INIT_BODY(p, sCollisions, 6, Ball_OnCollision);
  (p->body).unk_28 = (u32)Ball_Pull;
  p->pulled = FALSE;
  SET_XFLIP(p, FALSE);
  s->d.x = s->d.y = 0;
  p->halfHeight = 8;
  p->throwing = FALSE;
  p->lastMove = 0xFF;
  s->unk_2c = NULL;
  Ball_Update(p);
}

static void Ball_Recoil(struct Ball* p);
static void Ball_Fall(struct Ball* p);
static void Ball_Sit(struct Ball* p);
static void Ball_Roll(struct Ball* p);
static void Ball_Throw(struct Ball* p);

// 0x080679cc and 0x08067a84: never the same move three times running
static void decide(struct Ball* p) {
  u8 own = (p->s).work[0] ? BALL_ROLL : BALL_SIT;
  u8 next;
  if (!onGround(p)) {
    setMode(p, BALL_FALL);
    return;
  }
  next = (RANDOM(RNG_0202f388) & 15) <= 7 ? BALL_THROW : own;
  if (next == p->lastMove && ++p->repeats > 1) {
    next = next == own ? BALL_THROW : own;
    p->repeats = 0;
  }
  p->lastMove = next;
  setMode(p, next);
}

// 0x08067808. Open, a hit bursts it. Shut, a cut splits it.
// 0x0806894c
static u16 Ball_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  struct Ball* p = (struct Ball*)s;
  p->pulled = TRUE;
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  if (FUN_080098a4(s->coord.x, s->coord.y + (p->halfHeight << 8) + PIXEL(8)) == 0) {
    s->mode[1] = BALL_FALL;
    s->mode[2] = 0;
  } else {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - (p->halfHeight << 8);
  }
  p->pulled = FALSE;
  return 0;
}

static void Ball_Update(struct Ball* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != BALL_RECOIL) setMode(p, BALL_RECOIL);
  if (s->mode[1] == BALL_RECOIL) {
    Ball_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 death = BALL_BURST;
    if (p->throwing) {
      if (status & BODY_STATUS_B15) death = BALL_BURST_OPEN;
    } else if (status & BODY_STATUS_SLASHED) {
      if (s->mode[1] == BALL_ROLL) {
        p->halfHeight = 8;
        if (solid(s->coord.x, s->coord.y + PIXEL(13))) {
          s->d.x = 0;
          s->d.y = 0x500;
          stepVertical(s, p->halfHeight);
        }
      }
      death = (status & BODY_STATUS_B15) ? BALL_SPLIT_HARD : BALL_SPLIT;
    }
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    setMode(p, death);
    EXIT_BODY(p);
    Ball_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  // Burning or frozen, holds still and harmless
  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) SetDDP(&p->body, &sHarmless);
  }
  if (s->unk_2c != NULL) {
    if (!IsDead(s->unk_2c)) return;
    SetDDP(&p->body, sCollisions);
    s->unk_2c = NULL;
  }

  if (p->pulled) {
    UpdateEntityAnim(s);
    return;
  }
  if (s->mode[1] == BALL_DECIDE) decide(p);
  switch (s->mode[1]) {
    case BALL_FALL: Ball_Fall(p); break;
    case BALL_SIT: Ball_Sit(p); break;
    case BALL_ROLL: Ball_Roll(p); break;
    case BALL_THROW: Ball_Throw(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Ball_Recoil(struct Ball* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    setMode(p, BALL_BURST);
    EXIT_BODY(p);
    Ball_Die(p);
  }
}

// 0x08067b3c
static void Ball_Fall(struct Ball* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    bool8 right = FACING_RIGHT(p);
    InitNonAffineMotion(s);
    s->flags |= DISPLAY;
    SET_XFLIP(p, right);
    SetMotion(s, ANIM(1));
    p->halfHeight = 8;
    p->throwing = FALSE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (stepVertical(s, p->halfHeight)) s->mode[1] = BALL_DECIDE;
}

// 0x08067bcc: 90 frames
static void Ball_Sit(struct Ball* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(1));
    s->work[2] = 0;
    p->throwing = FALSE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 89) {
    s->mode[1] = BALL_DECIDE;
  } else if (!onGround(p)) {
    setMode(p, BALL_FALL);
  }
}

// Plays one script step each time the last one's frames are up. Returns FALSE when ended.
static bool8 playScript(struct Ball* p, const struct ScriptStep* script) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (++s->work[2] != script[p->scriptStep].frames) return TRUE;
  if (script[p->scriptStep + 1].frames == 0) return FALSE;
  s->work[2] = 0;
  p->scriptStep++;
  SetMotion(s, script[p->scriptStep].motion);
  return TRUE;
}

// 0x08067c30
static void Ball_Roll(struct Ball* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      p->scriptStep = 0;
      SetMotion(s, sRollStart[0].motion);
      p->halfHeight = 12;
      p->throwing = FALSE;
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (playScript(p, sRollStart)) break;
      InitRotatableMotion(s);
      SetMotion(s, ANIM(0));
      s->angle = 0;
      p->speed = 48;
      s->d.y = -0x300;
      p->dir = (pZero2->s).coord.x >= s->coord.x ? 1 : -1;
      p->turned = 0;
      p->peak = 0;
      s->work[2] = 0;
      s->mode[2]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      s->d.x = p->dir * p->speed;
      p->turned += p->speed;
      s->angle = p->dir * (p->turned >> 6);
      if (p->speed <= 0x17F && p->turned <= 0x1FFF) {
        p->speed += 48;
        p->peak = p->turned;
      } else if (0x4000 - p->turned <= p->peak) {
        p->speed -= 48;
      }
      if (p->turned > 0x3FFF) {
        InitNonAffineMotion(s);
        p->scriptStep = 0;
        SetMotion(s, ANIM(0));
        p->halfHeight = 8;
        s->work[2] = 0;
        s->d.x = 0;
        s->mode[2]++;
      }
      break;
    default:
      if (!playScript(p, sRollEnd)) s->mode[1] = BALL_DECIDE;
      break;
  }
  stepHorizontal(s, 12);
  stepVertical(s, p->halfHeight);
}

// 0x08067e2c: two rocks aimed at where Zero stood when it began
static void Ball_Throw(struct Ball* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->scriptStep = 0;
    SetMotion(s, sThrow[0].motion);
    PlaySound(SE_Z2_SPIKEBALL_OPEN);
    s->unk_coord.x = (pZero2->s).coord.x;
    p->throwing = TRUE;
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (!playScript(p, sThrow)) {
    s->mode[1] = BALL_DECIDE;
    return;
  }
  if (p->scriptStep == 2 && s->work[2] == 3) {
    s32 dx = s->unk_coord.x - s->coord.x;
    s32 far = (dx < 0 ? -dx : dx) / PIXEL(44);
    Coords32 c;
    c.x = s->coord.x;
    c.y = s->coord.y - PIXEL(18);
    PlaySound(SE_ENEMY_BOMB);
    createRocks(p, &c, far == 0 ? 0x2000 : far == 1 ? 0x4000 : 0x6000);
  }
  if (!onGround(p)) setMode(p, BALL_FALL);
}

// --------------------------------------------
// Deaths

static s32 jitter(void) { return ((RANDOM(RNG_0202f388) & 31) - 15) << 8; }

static void smokes(struct Entity* s) {
  Coords32 c;
  c.x = s->coord.x + jitter();
  c.y = s->coord.y + jitter();
  CreateSmoke(1, &c);
  c.x = s->coord.x + jitter();
  c.y = s->coord.y + jitter();
  CreateSmoke(2, &c);
}

// 0x08068638 / 0x0806871c: three of the five pieces
static void burstInThree(struct Entity* s, const struct SlashedEnemy* gibs, bool8 right) {
  u8 flip = right * 0x11;
  useApSheets(CreateSlashedEnemy(&s->coord, &gibs[0], 0, flip));
  useApSheets(CreateSlashedEnemy(&s->coord, &gibs[2], 0, flip));
  useApSheets(CreateSlashedEnemy(&s->coord, &gibs[4], 0, flip));
  smokes(s);
}

static void countKill(struct Entity* s, bool8 drop) {
  if (drop) TryDropItem(3, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  ApImportSpikeballKilled();
  TryDropZakoDisk((struct Enemy*)s, &s->coord);
  SET_ENEMY_ROUTINE(s, ENTITY_EXIT);
}

// 0x08067f4c / 0x0806806c: all five pieces
static void burst(struct Ball* p, const struct SlashedEnemy* gibs) {
  struct Entity* s = &p->s;
  u8 flip = FACING_RIGHT(p) * 0x11;
  s32 i;
  for (i = 0; i < 5; i++) useApSheets(CreateSlashedEnemy(&s->coord, &gibs[i], 0, flip));
  smokes(s);
  PlaySound(SE_ZAKO_EXPLODE);
  countKill(s, TRUE);
}

// 0x08068188 and 0x080683cc: other half flies off, this one rolls away from it
static void split(struct Ball* p, bool8 hard) {
  struct Entity* s = &p->s;
  const struct SlashedEnemy* gibs = hard ? sOpenGibs : sGibs;
  bool8 right;
  s16 v;
  if (s->mode[2] == 0) {
    InitRotatableMotion(s);
    useApSheets(p);
    SetMotion(s, ANIM(10));
    SET_XFLIP(p, s->work[3]);
    s->angle = 0;
    createHalf(p, s->coord.x + (s->work[3] ? PIXEL(2) : -PIXEL(2)), hard);
    s->work[2] = 0;
    p->rollAngle = 0;
    p->rollStep = 1;
    p->airborne = FALSE;
    s->d.x = 0;
    s->d.y = 0x100;
    s->mode[2]++;
  }
  right = FACING_RIGHT(p);
  if (++s->work[2] == (hard ? 160 : 64)) {
    PlaySound(SE_ZAKO_EXPLODE);
    burstInThree(s, gibs, right);
    countKill(s, !hard);
    return;
  }
  UpdateEntityAnim(s);
  if (!stepVertical(s, p->halfHeight)) {
    p->airborne = TRUE;
    return;
  }
  if (!p->airborne) {
    if (s->work[2] <= 47) return;
    p->rollStep += (s8)p->rollAngle >> 5;
    v = (SIN(p->rollAngle + p->rollStep + 64) - SIN(p->rollAngle + 64)) << 4;
    s->d.x = right ? v : -v;
    if (!stepHorizontal(s, 12)) {
      s->angle = p->rollAngle;
      p->rollAngle += p->rollStep;
      if ((s8)p->rollAngle <= (hard ? 32 : 24)) return;
    }
  }
  PlaySound(SE_ZAKO_EXPLODE);
  burstInThree(s, gibs, right);
  countKill(s, TRUE);
}

// 0x08067964
static void Ball_Die(struct Ball* p) {
  switch ((p->s).mode[1]) {
    case BALL_BURST: burst(p, sGibs); break;
    case BALL_BURST_OPEN: burst(p, sOpenGibs); break;
    case BALL_SPLIT: split(p, FALSE); break;
    case BALL_SPLIT_HARD: split(p, TRUE); break;
  }
}

// --------------------------------------------
// Rocks, Zero 2's projectile 2

static const struct Collision sRock;

static void Rock_Init(struct Entity* p);
static void Rock_Update(struct Entity* p);
static void Rock_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2SpikeballRockRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Rock_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Rock_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Rock_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809892c: one each way
static void createRocks(struct Ball* ball, Coords32* c, s32 speed) {
  s32 i;
  for (i = 0; i < 2; i++) {
    struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
    if (p != NULL) {
      INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_SPIKEBALL_ROCK);
      p->unk_28 = &ball->s;
      p->coord = *c;
      p->d.x = (speed << 8) / 0x376C;
      if (i != 0) p->d.x = -p->d.x;
      p->d.y = -0x700;
    }
  }
}

// 0x080989b4
static void Rock_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, &sRock, 0, NULL);
  SetMotion(p, ANIM(8));
  p->work[2] = 128;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Rock_Update(p);
}

// 0x08098a18
static void Rock_Update(struct Entity* p) {
  UpdateEntityAnim(p);
  p->coord.x += p->d.x;
  p->coord.y += p->d.y;
  if ((((Object*)p)->body.status & BODY_STATUS_B2) || solid(p->coord.x, p->coord.y) || --p->work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Rock_Die(p);
    return;
  }
  p->d.y += 0x40;
  if (p->d.y > 0x700) p->d.y = 0x700;
}

// 0x08098adc
static void Rock_Die(struct Entity* p) {
  CreateSmoke(2, &p->coord);
  EXIT_BODY(p);
  p->flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Other half, Zero 2's VFX 17

struct Half {
  struct Entity s;
  u8 angle;        // 0x74
  u8 step;         // 0x75
  bool8 airborne;  // 0x76
  u8 _[13];
};
static_assert(sizeof(struct Half) == sizeof(struct VFX));

static void Half_Init(struct Half* p);
static void Half_Update(struct Half* p);

// clang-format off
const VFXRoutine gApZ2SpikeballHalfRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Half_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Half_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b0e7c. Facing passed in work[3].
static void createHalf(struct Ball* ball, s32 x, u8 kind) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_SPIKEBALL_HALF);
    (p->s).coord.x = x;
    (p->s).coord.y = (ball->s).coord.y;
    (p->s).work[0] = kind;
    (p->s).work[3] = FACING_RIGHT(ball);
  }
}

// 0x080b1228
static void burstHalf(struct Half* p, bool8 right) {
  struct Entity* s = &p->s;
  useApSheets(CreateSlashedEnemy(&s->coord, &sHalfGibs[0], 0, right * 0x11));
  useApSheets(CreateSlashedEnemy(&s->coord, &sHalfGibs[1], 0, right * 0x11));
  smokes(s);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080b0ed0
static void Half_Init(struct Half* p) {
  struct Entity* s = &p->s;
  InitRotatableMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(9));
  s->renderPrio = 26;
  SET_XFLIP(p, s->work[3]);
  if (solid(s->coord.x, s->coord.y)) {
    burstHalf(p, FACING_RIGHT(p));
    return;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Half_Update(p);
}

// 0x080b1004: half from a cut
static void rollAway(struct Half* p) {
  struct Entity* s = &p->s;
  bool8 right = FACING_RIGHT(p);
  s16 v;
  if (s->mode[1] == 0) {
    p->angle = 0;
    p->step = 1;
    s->d.x = s->d.y = 0;
    s->work[2] = 0;
    p->airborne = FALSE;
    s->mode[1]++;
  }
  if (++s->work[2] == 128) {
    burstHalf(p, right);
    return;
  }
  if (!stepVertical(s, 8)) {
    p->airborne = TRUE;
    return;
  }
  if (p->airborne) {
    burstHalf(p, right);
    return;
  }
  if (s->work[2] <= 31) return;
  p->step += p->angle >> 5;
  v = (SIN(p->angle + p->step + 64) - SIN(p->angle + 64)) << 4;
  s->d.x = right ? -v : v;
  if (stepHorizontal(s, 12)) {
    burstHalf(p, right);
    return;
  }
  s->angle = ~p->angle;
  p->angle += p->step;
  if (p->angle > 96) burstHalf(p, right);
}

// 0x080b1178: half from a hard cut
static void thrownOff(struct Half* p) {
  struct Entity* s = &p->s;
  bool8 right = FACING_RIGHT(p);
  if (s->mode[1] == 0) {
    s->d.x = right ? 0x500 : -0x500;
    s->d.y = -0x340;
    s->work[2] = 0;
    s->mode[1]++;
  }
  if (++s->work[2] == 48) {
    burstHalf(p, right);
    return;
  }
  UpdateEntityAnim(s);
  if (stepHorizontal(s, 8)) {
    burstHalf(p, right);
    return;
  }
  if (right) {
    s->d.x -= 24;
    if (s->d.x < 0) s->d.x = 0;
  } else {
    s->d.x += 24;
    if (s->d.x > 0) s->d.x = 0;
  }
  stepVertical(s, 8);
}

static void Half_Update(struct Half* p) {
  if ((p->s).work[0] == 0) {
    rollAway(p);
  } else {
    thrownOff(p);
  }
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x1800}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x1800}};

static const struct Collision sRock =
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}};

static const struct SlashedEnemy sGibs[5] = {
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 11), {0xff, 0x11}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 12), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 13), {0xff, 0x11}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 14), {0xff, 0x11}, {0, 0}, {128, -768}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 15), {0xff, 0x11}, {0, 0}, {-512, -768}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sOpenGibs[5] = {
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 11), {0xff, 0x11}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 12), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 13), {0xff, 0x11}, {0, 0}, {192, -768}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 14), {0xff, 0x11}, {0, 0}, {192, -1152}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 15), {0xff, 0x11}, {0, 0}, {-768, -1152}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sHalfGibs[2] = {
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 13), {0xff, 0x11}, {0, 0}, {-384, -1280}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_SPIKEBALL, 15), {0xff, 0x11}, {0, 0}, {-512, -1280}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
