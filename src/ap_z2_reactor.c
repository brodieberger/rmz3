#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "projectile.h"
#include "quake.h"
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
  Zero 2's boss 24, a Power Room reactor's core.
  work0: which reactor, and its shots
    0: Zero 3's lemons
    1: energy balls
    2: faster energy balls
    3: faster energy balls that split on the floor
*/

struct Reactor {
  OBJECT_HDR;
  u8 _b4[12];
  u16 dying;  // 0xC0
  u8 _c2[34];
};
static_assert(sizeof(struct Reactor) == sizeof(struct Boss));

enum { REACTOR_START, REACTOR_WAIT, REACTOR_NOP, REACTOR_FIRE };

static const struct Collision sBody[4];
static const struct PreloadEntity sSheet = {AP_SHEET_Z2_REACTOR, 0, 960, 4, 0, AP_PRELOAD_SHEET, 0};

static void Reactor_Init(struct Reactor* p);
static void Reactor_Update(struct Reactor* p);
static void Reactor_Die(struct Reactor* p);
static void Reactor_Disappear(struct Reactor* p);
struct Entity* ApZ2CreateEnergyBall(const Coords32* at, s32 speed, u8 angle, u8 kind);

// clang-format off
const BossRoutine gApZ2ReactorRoutine = {
    [ENTITY_INIT] =      (BossFunc)Reactor_Init,
    [ENTITY_UPDATE] =    (BossFunc)Reactor_Update,
    [ENTITY_DIE] =       (BossFunc)Reactor_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Reactor_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// 0x08065554
static void Reactor_Init(struct Reactor* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sSheet);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_REACTOR, 0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sBody, 48);
  s->work[3] = 0;
  s->work[2] = 0;
  PlaySound(SE_Z2_REACTOR_HUM);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Reactor_Update(p);
}

// 0x0833d960, 0x0833d974, 0x0833d988: a fan of five
static const s32 sShotX[5] = {-PIXEL(49), -PIXEL(27), 0, PIXEL(27), PIXEL(49)};
static const s32 sShotY[5] = {PIXEL(24), PIXEL(25), PIXEL(24), PIXEL(25), PIXEL(24)};
static const u8 sShotAngle[5] = {227, 222, 192, 162, 157};

// 0x080658a4: two fans 40 frames apart, every 105 frames
static void fire(struct Reactor* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i;
  UpdateSpriteAnimation(p);
  if (s->work[2] == 104) {
    s->work[2] = 0;
    return;
  }
  if (s->work[2] == 0 || s->work[2] == 40) {
    for (i = 0; i < 5; i++) {
      at.x = s->coord.x + sShotX[i];
      at.y = s->coord.y + sShotY[i];
      switch (s->work[0]) {
        case 0: CreateLemon(&at, 0x400, sShotAngle[i]); break;
        case 1: ApZ2CreateEnergyBall(&at, 0x400, sShotAngle[i], 0); break;
        case 2: ApZ2CreateEnergyBall(&at, 0x600, sShotAngle[i], 0); break;
        default: ApZ2CreateEnergyBall(&at, 0x600, sShotAngle[i], 1); break;
      }
      PlaySound(SE_ENEMY_BOMB);
    }
  }
  s->work[2]++;
}

// 0x08065624
static void Reactor_Update(struct Reactor* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Reactor_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case REACTOR_START:
      UpdateSpriteAnimation(p);
      s->mode[1] = REACTOR_WAIT;
      s->mode[2] = 0;
      break;
    case REACTOR_WAIT:
      if (s->mode[2] == 0) {
        s->work[2] = 64;
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) {
        s->mode[1] = REACTOR_FIRE;
        s->mode[2] = 0;
      }
      break;
    case REACTOR_FIRE:
      fire(p);
      break;
  }
}

// 0x08065688: explodes, flashes faster and faster, then VM_FLAG1
static void Reactor_Die(struct Reactor* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u16 t;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    p->dying = 0;
    s->work[2] = 24;
    s->work[3] = 12;
    StopSound(SE_Z2_REACTOR_HUM);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  t = p->dying++;
  if (t > 64) {
    if ((p->dying & 3) == 0) {
      at.x = s->coord.x + PIXEL(32 - (RANDOM(RNG_0202f388) & 63));
      at.y = s->coord.y + PIXEL(32 - (RANDOM(RNG_0202f388) & 63));
      ApZ2CreateExplosion(s, &at, 2, RANDOM(RNG_0202f388));
    }
    if ((p->dying & 15) == 0) {
      AppendQuake(8, &s->coord);
      PlaySound(SE_UNK_35);
    }
  }
  if (s->mode[1] != 0) {
    if (p->dying & 1) {
      PaintEntityWhite(s);
    } else {
      UpdateEntityPaletteID(s);
    }
    return;
  }
  if (--s->work[3] != 0xFF) {
    UpdateEntityPaletteID(s);
    return;
  }
  PaintEntityWhite(s);
  if (--s->work[2] == 0xFF) {
    gStageRun.vm.active |= VM_FLAG1;
    s->mode[1]++;
  }
  s->work[3] = s->work[2] >> 1;
}

// 0x0806583c
static void Reactor_Disappear(struct Reactor* p) {
  ApZ2PlantBreakReactor((p->s).work[0]);
  DeleteBoss(&p->s);
}

// clang-format off
// 0x0833d8f8
static const struct Collision sBody[4] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 3, 0x00000000, {0x0, 0x0, 0x4c00, 0x4000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 2, 0x00000000, {0x0, 0x0, 0x6400, 0x3400}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 1, 0x00000000, {0x0, 0x0, 0x7000, 0x2800}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x7e00, 0x1c00}},
};
// clang-format on

// --------------------------------------------

/*
  Zero 2's projectile 63, a reactor's energy ball. Bounces once, a saber sends it back.
  work0: 1 splits into two lemons when it lands falling straight
*/

static void Ball_Init(struct Entity* s);
static void Ball_Update(struct Entity* s);
static void Ball_Die(struct Entity* s);

// clang-format off
const ProjectileRoutine gApZ2EnergyBallRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Ball_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Ball_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08345938, 0x08345968
static const struct Collision sBall[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x600, 0x600}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x600, 0x600}},
};
static const struct Collision sSentBack[2] = {
    {DDP, FACTION_ALLY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x600, 0x600}},
    {DRP, FACTION_ALLY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x600, 0x600}},
};
// clang-format on

// 0x080ac238
struct Entity* ApZ2CreateEnergyBall(const Coords32* at, s32 speed, u8 angle, u8 kind) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ENERGY_BALL);
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = 0;
    p->d.x = SIN(angle + 192) * speed / 256;
    p->d.y = SIN(angle + 128) * speed / 256;
  }
  return p;
}

// 0x080ac2e4
static void Ball_Init(struct Entity* s) {
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE | COLLIDABLE;
  INIT_BODY(s, sBall, 0, NULL);
  SetSpriteAnimation(s, MOTION(SM002_LEMON, 0));
  s->work[2] = 0xFF;
  s->work[3] = 0;
  SET_PROJECTILE_ROUTINE(s, ENTITY_UPDATE);
  Ball_Update(s);
}

static void die(struct Entity* s) {
  SET_PROJECTILE_ROUTINE(s, ENTITY_DIE);
  Ball_Die(s);
}

// 0x080ac348
static void Ball_Update(struct Entity* s) {
  Object* p = (Object*)s;
  UpdateSpriteAnimation(s);
  if ((p->body).status & BODY_STATUS_BLOCKED) {
    if (s->mode[1] == 0) {
      INIT_BODY(s, sSentBack, 0, NULL);
      s->d.x = -s->d.x * 3 / 2;
      s->d.y = -s->d.y * 3 / 2;
      s->mode[1] = 1;
    } else if (s->d.y < 0) {
      PlaySound(SE_BLOCKED);
      s->d.x = -s->d.x;
    } else {
      PlaySound(SE_BLOCKED);
      s->d.y = -s->d.y;
    }
  }
  if ((p->body).status & (BODY_STATUS_B22 | BODY_STATUS_B8)) {
    EXIT_BODY(s);
    CreateSmoke(3, &s->coord);
    die(s);
    return;
  }
  if ((p->body).status & BODY_STATUS_B2) {
    EXIT_BODY(s);
    CreateSmoke(2, &s->coord);
    die(s);
    return;
  }
  if (--s->work[2] == 0) {
    CreateSmoke(3, &s->coord);
    die(s);
    return;
  }
  if (FUN_080098a4(s->coord.x, s->coord.y)) {
    if (s->work[3] != 0) {
      die(s);
      return;
    }
    if (s->d.x == 0 && s->work[0] == 1) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      CreateLemon(&s->coord, s->d.y, 0);
      CreateLemon(&s->coord, s->d.y, 128);
      EXIT_BODY(s);
      SET_PROJECTILE_ROUTINE(s, ENTITY_DIE);
    } else {
      s->d.y = -s->d.y;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->work[3]++;
    }
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// 0x080ac4f8
static void Ball_Die(struct Entity* s) {
  s->flags &= ~DISPLAY;
  EXIT_BODY(s);
  SET_PROJECTILE_ROUTINE(s, ENTITY_EXIT);
}

#endif
