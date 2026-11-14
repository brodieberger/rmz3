#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
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
  Zero 2's snowball thrower, enemy 75.
  work0:
    0: thrower
    1: snowball
  work1:
    0: throws left
    1: throws right
*/

struct Snowball {
  OBJECT_HDR;
  u16 scale;     // 0xB4, 0x100 is full size
  u16 spin;      // 0xB6
  s8 dir;        // 0xB8, -1 or 1
  u8 size;       // 0xB9, 1..6, hitbox
  u8 _ba[2];
  s32 rolled;    // 0xBC, distance since last rolling sound
  u8 _[4];
};
static_assert(sizeof(struct Snowball) == sizeof(struct Enemy));

enum {
  THROWER,
  SNOWBALL,
};

enum {
  THROWER_WAIT,
  THROWER_WAITING,
  THROWER_WIND_UP,
  THROWER_WINDING_UP,
  THROWER_THROW,
  THROWER_THROWING,
};

enum {
  SNOWBALL_ROLL,
  SNOWBALL_FALL,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_SNOWBALLER, n)

static const struct Collision sCollisions[16];
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sGibsCut[3];
static const struct SlashedEnemy sChunks[4];
static const struct SlashedEnemy sChunksCut[4];
static const Coords32 sElementCoord = {0, -PIXEL(16)};

#define HARMLESS (&sCollisions[14])

static void Snowballer_Init(struct Snowball* p);
static void Snowballer_Update(struct Snowball* p);
static void Snowballer_Die(struct Snowball* p);

// clang-format off
const EnemyRoutine gApZ2SnowballerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Snowballer_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Snowballer_Update,
    [ENTITY_DIE] =       (EnemyFunc)Snowballer_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

// 0x08090830
static void throwSnowball(struct Snowball* thrower) {
  struct Entity* s = &thrower->s;
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_SNOWBALLER);
    p->coord.x = s->coord.x + (s->work[1] << 13) - PIXEL(16);
    p->coord.y = s->coord.y - PIXEL(32);
    p->work[0] = SNOWBALL;
    p->work[1] = s->work[1];
  }
}

static void Snowballer_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = (p->coord).x < (pZero2->s).coord.x;
  }
}

// 0x08090894
static void Snowballer_Init(struct Snowball* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == THROWER) {
    s->mode[1] = THROWER_WIND_UP;
    InitNonAffineMotion(s);
    useApSheets(p);
    SET_XFLIP(p, s->work[1]);
    SetMotion(s, ANIM(2));
    UpdateEntityAnim(s);
    INIT_BODY(p, sCollisions, 12, Snowballer_OnCollision);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    s->work[2] = 0;
    s->unk_2c = NULL;
  } else {
    InitScalerotMotion1(s);
    useApSheets(p);
    s->angle = 0;
    (s->spr).mag.x = (s->spr).mag.y = 0x80;
    SET_XFLIP(p, FALSE);
    SetMotion(s, ANIM(3));
    UpdateEntityAnim(s);
    INIT_BODY(p, &sCollisions[2], 16, NULL);
    s->d.x = PIXEL(2);
    s->d.y = -0x280;
    p->scale = 0x80;
    p->dir = s->work[1] * 2 - 1;
    p->spin = 0;
    p->size = 1;
    s->work[2] = 8;
    p->rolled = 0;
  }
  s->flags |= DISPLAY | FLIPABLE;
  Snowballer_Update(p);
}

static void Thrower_Update(struct Snowball* p);
static void Snowball_Update(struct Snowball* p);

// 0x08090a20
static void Snowballer_Update(struct Snowball* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = (status & BODY_STATUS_SLASHED) ? (status & BODY_STATUS_B15) != 0 : 0;
    EXIT_BODY(p);
    Snowballer_Die(p);
    return;
  }
  if (s->work[0] == THROWER) {
    Thrower_Update(p);
  } else {
    Snowball_Update(p);
  }
}

static void Thrower_Update(struct Snowball* p) {
  struct Entity* s = &p->s;

  if (IsFrozen(p)) {
    if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) SetDDP(&p->body, HARMLESS);
  }
  if (s->unk_2c != NULL) {
    if (!IsDead(s->unk_2c)) return;  // held on frame while burning or thawing
    s->unk_2c = NULL;
    SetDDP(&p->body, sCollisions);
  }

  switch (s->mode[1]) {
    case THROWER_WAIT:
      SetMotion(s, ANIM(2));
      s->work[2] = 128;
      s->mode[1]++;
      FALLTHROUGH;
    case THROWER_WAITING:
      UpdateEntityAnim(s);
      if (s->work[2] != 0 && --s->work[2] != 0) return;
      if ((s->motion).state == ANIM_NEXT_GOTO) s->mode[1]++;  // end of loop
      return;

    case THROWER_WIND_UP:
      SetMotion(s, ANIM(0));
      s->mode[1]++;
      FALLTHROUGH;
    case THROWER_WINDING_UP:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) s->mode[1]++;
      return;

    case THROWER_THROW:
      throwSnowball(p);
      SetMotion(s, ANIM(1));
      s->mode[1]++;
      FALLTHROUGH;
    case THROWER_THROWING:
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) s->mode[1] = THROWER_WAIT;
      return;
  }
}

static void Snowball_Burst(struct Snowball* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  (p->s).mode[1] = 0;
  EXIT_BODY(p);
  Snowballer_Die(p);
}

// 0x08090c20
static void Snowball_Update(struct Snowball* p) {
  struct Entity* s = &p->s;
  s32 oldX = s->coord.x;
  s32 radius, below;

  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x1DFFF) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (gStageRun.vm.unk_004 & 1) {
    Snowball_Burst(p);
    return;
  }

  UpdateEntityAnim(s);
  radius = (u16)((p->scale * 2304) >> 8);  // 9 px at full size

  if (s->mode[1] == SNOWBALL_ROLL) {
    s->coord.x += p->dir * s->d.x;
    if (p->size > 1) {
      p->rolled += s->d.x;
      if (p->rolled > 0x77FF) {
        PlaySound(SE_Z2_SNOWBALL_ROLL);
        p->rolled = 0;
      }
    }
    if (FUN_080098a4(s->coord.x + p->dir * radius, s->coord.y) != 0) {
      Snowball_Burst(p);
      return;
    }
    below = s->coord.y + radius + PIXEL(8);
    if (FUN_080098a4(s->coord.x, below) == 0) {
      s->d.y = 0;
      s->mode[1] = SNOWBALL_FALL;
    } else {
      s32 aheadX, aheadY;
      s->coord.y = FUN_08009f6c(s->coord.x, below) - radius;
      // Step it can't climb turns it back, slower
      aheadX = s->coord.x + (p->dir << 11);
      aheadY = s->coord.y + radius - PIXEL(1);
      if (FUN_080098a4(aheadX, aheadY) != 0 && FUN_080098a4(aheadX, aheadY - PIXEL(8)) == 0) {
        p->dir = -p->dir;
        s->d.x = -(s->d.x >> 2);
      }
      // Speeds up downhill
      if (s->d.x <= 0x2FF &&
          FUN_080098a4(s->coord.x + p->dir * radius, s->coord.y + radius + 1) == 0) {
        s->d.x += (s->d.x < 0) ? 20 : 8;
      }
      // Grows while rolling forward, to twice its size
      if (s->d.x > 0 && p->scale <= 0x1FF && --s->work[2] == 0) {
        p->scale += 8;
        (s->spr).mag.x = (s->spr).mag.y = p->scale;
        s->work[2] = 8;
        if (p->size <= 5 && ((p->size + 1) << 11) < p->scale * 24) {
          p->size++;
          SetDDP(&p->body, &sCollisions[p->size * 2]);
        }
      }
    }
  } else {
    s->coord.x += p->dir * s->d.x;
    if (FUN_080098a4(s->coord.x + p->dir * radius, s->coord.y) != 0) {
      Snowball_Burst(p);
      return;
    }
    s->coord.y += s->d.y;
    below = s->coord.y + radius + 1;
    if (FUN_080098a4(s->coord.x, below) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, below) - radius;
      s->mode[1] = SNOWBALL_ROLL;
    } else {
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
    }
  }

  // Turns as far as it rolled
  p->spin += ((0x1000000 / ((radius * 2 * 804) >> 8)) * (s->coord.x - oldX)) / 256;
  s->angle = p->spin >> 8;
}

// --------------------------------------------

static void finish(struct Snowball* p, u8 dropTable) {
  TryDropItem(dropTable, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  if ((p->s).work[0] == 0) ApImportSnowballerKilled();
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void smokeNear(struct Snowball* p, u8 kind) {
  Coords32 c;
  c.x = (p->s).coord.x + (((RANDOM(RNG_0202f388) & 15) - 8) << 8);
  c.y = (p->s).coord.y + (((RANDOM(RNG_0202f388) & 15) - 8) << 8) - PIXEL(24);
  CreateSmoke(kind, &c);
}

// 0x08090fec, and 0x080911a0 for a hard cut
static void Snowballer_Die(struct Snowball* p) {
  struct Entity* s = &p->s;
  bool8 cut = s->mode[1];
  u8 flip = (s->work[3]) | (((s->flags & X_FLIP) != 0) << 4);
  s32 i;
  if (s->work[0] == THROWER) {
    const struct SlashedEnemy* gibs = cut ? sGibsCut : sGibs;
    Coords32 c;
    c.x = s->coord.x;
    c.y = s->coord.y - PIXEL(24);
    PlaySound(SE_ZAKO_EXPLODE);
    for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&c, &gibs[i], 0, flip));
    smokeNear(p, 1);
    smokeNear(p, 2);
    finish(p, 2);
  } else {
    const struct SlashedEnemy* chunks = cut ? sChunksCut : sChunks;
    if (p->size > 1) PlaySound(SE_Z2_SNOWBALL_BURST);
    for (i = p->size * 2; i != 0; i--) useApSheets(CreateSlashedEnemy(&s->coord, &chunks[i & 3], 0, flip));
    finish(p, 0);
  }
}

// -------------------------------------------
// clang-format off
// Thrower, then snowball's six sizes, then thrower while an element holds it
static const struct Collision sCollisions[16] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, -0x1000, 0x1000, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, -0x1000, 0x1000, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x1800}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x2000, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x2800, 0x2800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x2800, 0x2800}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x3000, 0x3000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x3000, 0x3000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, -0x1000, 0x1000, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0, 0, 0, 0x00000000, {0x0, -0x1000, 0x1000, 0x2000}},
};

static const struct SlashedEnemy sGibs[3] = {
    {ANIM(8), {0xff, 0x11}, {0, 0}, {32, -1280}, {31, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(9), {0xff, 0x11}, {0, 0}, {-256, -1024}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(10), {0xff, 0x11}, {0, 0}, {128, -1408}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sGibsCut[3] = {
    {ANIM(8), {0xff, 0x11}, {0, 0}, {32, -1536}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(9), {0xff, 0x11}, {0, 0}, {-256, -1408}, {511, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(10), {0xff, 0x11}, {0, 0}, {128, -1536}, {255, 63}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sChunks[4] = {
    {ANIM(4), {0xff, 0x11}, {0, 0}, {256, -1280}, {31, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {128, -1024}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(6), {0xff, 0x11}, {0, 0}, {-128, -1152}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(7), {0xff, 0x11}, {0, 0}, {-256, -1280}, {127, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sChunksCut[4] = {
    {ANIM(4), {0xff, 0x11}, {0, 0}, {512, -1920}, {31, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {256, -1536}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(6), {0xff, 0x11}, {0, 0}, {-256, -1280}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(7), {0xff, 0x11}, {0, 0}, {-384, -1536}, {127, 511}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
