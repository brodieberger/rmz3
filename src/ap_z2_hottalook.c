#include "ap.h"

#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Hive and Hottalooks for Zero 2's crystal cave.
  Illuminates the crystal platforms.
*/

#define CORRIDOR_LEFT 0x44800
#define CORRIDOR_RIGHT 0xcec00

#define MAX_HOTTALOOKS 6

struct Hive {
  OBJECT_HDR;
  s32 baseY;     // 0xB4, height it flies at
  s8 side;       // 0xB8, -1: leading left, 1: leading right
  bool8 shocked; // 0xB9, frozen by a elemental attack
  u16 swapTimer; // 0xBA
  u8 _[8];
};
static_assert(sizeof(struct Hive) == sizeof(struct Enemy));

struct Hottalook {
  OBJECT_HDR;
  u16 radius;     // 0xB4
  u8 phase;       // 0xB6, position around its circle or along its wave
  u8 heading;     // 0xB7, lap count while circling
  s32 travelled;  // 0xB8
  u16 timer;      // 0xBC
  u8 _[6];
};
static_assert(sizeof(struct Hottalook) == sizeof(struct Enemy));

enum {
  HIVE_ENTER,
  HIVE_LEAD,
  HIVE_SWAP,
  HIVE_HIT,
  HIVE_RELEASE,
  HIVE_CLOSE,
  HIVE_LEAVE,
};

enum {
  HOTTALOOK_HATCH,
  HOTTALOOK_CIRCLE,
  HOTTALOOK_FLY,
  HOTTALOOK_FALL,
  HOTTALOOK_RECOIL,
};

static const struct Collision sHiveCollisions[2];
static const struct Collision sHiveHarmless[2];
static const struct Collision sHiveHidden[2];
static const struct Collision sHottalookCollisions[2];
static const struct Collision sHottalookHarmless[2];
static const Coords32 sElementCoord = {0, 0};

static void Hive_Init(struct Hive* p);
static void Hive_Update(struct Hive* p);
static void Hive_Die(struct Hive* p);
static void Hottalook_Init(struct Hottalook* p);
static void Hottalook_Update(struct Hottalook* p);
static void Hottalook_Die(struct Hottalook* p);
static void createHottalook(struct Hive* hive, u8 phase, u8 color);
static void createShard(struct Entity* parent, u8 kind, u8 angle, u16 motion);

// clang-format off
const EnemyRoutine gApZ2HiveRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Hive_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Hive_Update,
    [ENTITY_DIE] =       (EnemyFunc)Hive_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

const EnemyRoutine gApZ2HottalookRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Hottalook_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Hottalook_Update,
    [ENTITY_DIE] =       (EnemyFunc)Hottalook_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

#define COLOR work[1]  // 0: red, 1: blue

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* p, u8 mode) {
  p->mode[1] = mode;
  p->mode[2] = 0;
}

static void disappear(struct Entity* p) {
  p->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = (p->coord).x < (pZero2->s).coord.x;
  }
}

static void approach(s32* v, s32 to) {
  s32 step;
  if (*v == to) return;
  step = (to - *v) / 8;
  if (step < 0) step = -step;
  if (step == 0) step = 1;
  if (step > PIXEL(3)) step = PIXEL(3);
  *v += (*v < to) ? step : -step;
}

// --------------------------------------------
// Hive, Zero 2 enemy 49.

static void Hive_Init(struct Hive* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, FALSE);
  (p->s).flags |= DISPLAY | FLIPABLE;
  p->side = (p->s).work[0] * 2 - 1;
  p->shocked = FALSE;
  (p->s).d.x = (p->s).d.y = 0;
  p->swapTimer = 128;
  p->baseY = (p->s).coord.y;
  (p->s).COLOR = 0;
  (p->s).unk_2c = NULL;
  (p->s).unk_coord.x = (p->s).coord.x;
  INIT_BODY(p, sHiveHidden, 64, onCollision);
  Hive_Update(p);
}

// 0x0808090c: stays 80 px ahead of Zero
static void Hive_Follow(struct Hive* p) {
  s32 x, home = (p->s).unk_coord.x;
  if ((p->s).unk_2c != NULL) return;
  x = (pZero2->s).coord.x + p->side * PIXEL(80);
  if ((p->s).work[0] == 0) {
    if (x > home) {
      x = home;
    } else if (x < CORRIDOR_LEFT) {
      x = CORRIDOR_LEFT;
    }
  } else {
    if (x < home) {
      x = home;
    } else if (x > CORRIDOR_RIGHT) {
      x = CORRIDOR_RIGHT;
    }
  }
  approach(&(p->s).coord.x, x);
  approach(&(p->s).coord.y, p->baseY);
}

static const EnemyFunc sHiveUpdates[7];

// 0x08080368
static void Hive_Update(struct Hive* p) {
  struct Entity* s = &p->s;
  if (((p->body).status & BODY_STATUS_WHITE) && (s->mode[1] == HIVE_LEAD || s->mode[1] == HIVE_SWAP)) {
    if (!p->shocked) {
      switch ((p->body).elemented) {
        case ELEMENT_THUNDER: p->shocked = TRUE; break;
        case ELEMENT_FLAME: s->COLOR = 0; setMode(s, HIVE_HIT); break;
        case ELEMENT_ICE: s->COLOR = 1; setMode(s, HIVE_HIT); break;
        default: setMode(s, HIVE_HIT); break;
      }
    }
    if (s->unk_2c == NULL) {
      s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
      SetDDP(&p->body, sHiveHarmless);
    }
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) {
    s->unk_2c = NULL;
    SetDDP(&p->body, sHiveCollisions);
  }

  if (s->mode[1] == HIVE_LEAD) {
    if (s->work[0] == 0 ? s->coord.x <= CORRIDOR_LEFT : s->coord.x >= CORRIDOR_RIGHT) setMode(s, HIVE_LEAVE);
  }

  if (p->shocked) {  // 0x080808f0
    UpdateSpriteAnimation(p);
    if (s->unk_2c == NULL) p->shocked = FALSE;
    return;
  }
  (sHiveUpdates[s->mode[1]])((void*)p);
}

// Hive animations: idle, swap, hit, open, close. One per color
static void setHiveAnim(struct Hive* p, u8 n) {
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HIVE, (n * 2 + 1 - (p->s).COLOR)));
}

// 0x080804d8: waits above the end of its corridor for Zero to walk in, then lowers 96 px
static void Hive_Enter(struct Hive* p) {
  struct Entity* s = &p->s;
  s32 zx = (pZero2->s).coord.x, home = s->unk_coord.x;
  if (s->mode[2] == 0) {
    setHiveAnim(p, 0);
    s->work[2] = 64;
    s->coord.y = p->baseY + SIN(191) * 96;  // 96 px up
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[2] == 1) {
    if (s->work[0] == 0 ? (zx >= home && zx <= home + PIXEL(80)) : (zx <= home && zx >= home - PIXEL(80))) {
      s->coord.x = home;
      s->mode[2]++;
    } else {
      if (s->work[0] == 0) {
        if (s->coord.x < home) s->coord.x = zx - PIXEL(80);
        if (s->coord.x <= CORRIDOR_LEFT) disappear(s);
      } else {
        if (s->coord.x > home) s->coord.x = zx + PIXEL(80);
        if (s->coord.x >= CORRIDOR_RIGHT) disappear(s);
      }
      return;
    }
  }
  s->work[2]--;
  s->coord.y = p->baseY + SIN(255 - s->work[2]) * 96;
  if (s->work[2] == 0) {
    SetDDP(&p->body, sHiveCollisions);
    setMode(s, HIVE_LEAD);
  }
}

// 0x08080654
static void Hive_Lead(struct Hive* p) {
  if ((p->s).mode[2] == 0) {
    setHiveAnim(p, 0);
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  Hive_Follow(p);
  if (--p->swapTimer == 0) {
    p->swapTimer = 128;
    setMode(&p->s, HIVE_SWAP);
  }
}

// 0x080806ac: turns to its other color
static void Hive_Swap(struct Hive* p) {
  if ((p->s).mode[2] == 0) {
    setHiveAnim(p, 1);
    (p->s).COLOR ^= 1;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  Hive_Follow(p);
  if (IsSpriteAnimEnd(p)) setMode(&p->s, HIVE_LEAD);
}

// 0x08080704
static void Hive_Hit(struct Hive* p) {
  if ((p->s).mode[2] == 0) {
    setHiveAnim(p, 2);
    (p->s).mode[2]++;
  }
  if ((p->s).unk_2c != NULL) return;  // Frozen while an element effect plays
  UpdateSpriteAnimation(p);
  Hive_Follow(p);
  if (IsSpriteAnimEnd(p)) setMode(&p->s, HIVE_RELEASE);
}

// 0x08080760: opens, and after 8 frames lets out up to 3 Hottalooks. At most 6 alive
static void Hive_Release(struct Hive* p) {
  struct Entity* s = &p->s;
  u8 n;
  if (s->mode[2] == 0) {
    setHiveAnim(p, 3);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]++;
  Hive_Follow(p);
  switch (s->work[2]) {
    case 8:
      n = countSpecificEntities1(gEnemyHeaderPtr, ENEMY_Z2_HOTTALOOK);
      if (n < MAX_HOTTALOOKS) {
        n = MAX_HOTTALOOKS - n;
        if (n > 3) n = 3;
        for (; n != 0; n--) createHottalook(p, n * 85, s->COLOR);
      }
      break;
    case 24:
      PlaySound(SE_Z2_HIVE);
      break;
    case 96:
      setMode(s, HIVE_CLOSE);
      break;
  }
}

// 0x08080814
static void Hive_Close(struct Hive* p) {
  if ((p->s).mode[2] == 0) {
    setHiveAnim(p, 4);
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  Hive_Follow(p);
  if (IsSpriteAnimEnd(p)) setMode(&p->s, HIVE_LEAD);
}

// 0x08080864: past the far end of its corridor, flies up out of view
static void Hive_Leave(struct Hive* p) {
  if ((p->s).mode[2] == 0) {
    setHiveAnim(p, 0);
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (p->s).coord.y -= 0x1C0;
  if (Camera_GetDistance(&gStageRun.vm.camera, &(p->s).coord) > 63) disappear(&p->s);
}

static const EnemyFunc sHiveUpdates[7] = {
    [HIVE_ENTER] = (EnemyFunc)Hive_Enter,
    [HIVE_LEAD] = (EnemyFunc)Hive_Lead,
    [HIVE_SWAP] = (EnemyFunc)Hive_Swap,
    [HIVE_HIT] = (EnemyFunc)Hive_Hit,
    [HIVE_RELEASE] = (EnemyFunc)Hive_Release,
    [HIVE_CLOSE] = (EnemyFunc)Hive_Close,
    [HIVE_LEAVE] = (EnemyFunc)Hive_Leave,
};

// 0x0808048c: never from damage, since it takes none
static void Hive_Die(struct Hive* p) {
  CreateSmoke(1, &(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Hottalook, Zero 2 enemy 50.

// 0x08080a6c
static void createHottalook(struct Hive* hive, u8 phase, u8 color) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_HOTTALOOK);
    p->unk_28 = &hive->s;
    p->coord = (hive->s).coord;
    p->work[0] = phase;
    p->COLOR = color;
  }
}

// 0x08080ad4
static void Hottalook_Init(struct Hottalook* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x);
  (p->s).flags |= DISPLAY | FLIPABLE;
  (p->s).unk_2c = NULL;
  INIT_BODY(p, sHottalookCollisions, 4, onCollision);
  Hottalook_Update(p);
}

// Hatching and flying animations
#define HATCH_ANIM(p) MOTION(AP_SHEET_Z2_HOTTALOOK, ((p)->s.COLOR))
#define FLY_ANIM(p) MOTION(AP_SHEET_Z2_HOTTALOOK, (2 + (p)->s.COLOR))

static bool8 hiveAlive(struct Entity* hive) { return hive != NULL && hive->mode[0] <= ENTITY_UPDATE; }

// 0x08080c7c: 
static void Hottalook_Hatch(struct Hottalook* p) {
  struct Entity* hive = (p->s).unk_28;
  if (hiveAlive(hive)) (p->s).coord = hive->coord;
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, HATCH_ANIM(p));
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(&p->s, HOTTALOOK_CIRCLE);
}

// 0x08080cd4:
static void Hottalook_Circle(struct Hottalook* p) {
  struct Entity* s = &p->s;
  Coords32 was;
  if (s->mode[2] == 0) {
    struct Entity* hive = s->unk_28;
    if (!hiveAlive(hive)) {
      setMode(s, HOTTALOOK_FLY);
      return;
    }
    SetSpriteAnimation(p, FLY_ANIM(p));
    p->radius = 0;
    p->phase = s->work[0];
    p->heading = 0;
    s->unk_coord = hive->coord;
    s->work[2] = 3;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  was = s->coord;
  p->radius += 64;
  if (p->radius > PIXEL(32)) p->radius = PIXEL(32);
  p->phase += 2;
  p->heading += 2;
  s->coord.y = s->unk_coord.y + Sin(p->phase, p->radius);
  s->coord.x = s->unk_coord.x + Cos(p->phase, p->radius);
  s->d.x = s->coord.x - was.x;
  s->d.y = s->coord.y - was.y;
  if ((p->heading & 127) == 0 && --s->work[2] == 0) setMode(s, HOTTALOOK_FLY);
}

// 0x08080de0: 
static void Hottalook_Fly(struct Hottalook* p) {
  struct Entity* s = &p->s;
  s32 wave;
  if (s->mode[2] == 0) {
    u8 angle;
    SetDDP(&p->body, sHottalookCollisions);
    SetSpriteAnimation(p, FLY_ANIM(p));
    angle = CalcAngle(s->d.x, s->d.y);
    angle += (RANDOM(RNG_0202f388) & 31) + 241;
    s->d.x = COS(angle);
    s->d.y = SIN(angle);
    s->unk_coord = s->coord;
    p->phase = 0;
    p->heading = angle;
    p->travelled = 0;
    p->timer = 320;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  p->phase += 2;
  p->travelled += 256;
  wave = SIN(p->phase) * 24;
  s->coord.y = s->unk_coord.y + Sin(p->heading, p->travelled) + Cos(p->heading, wave);
  s->coord.x = s->unk_coord.x + Cos(p->heading, p->travelled) - Sin(p->heading, wave);
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64) || --p->timer == 0) {
    disappear(s);
  } else if (p->timer < 64) {
    s->flags = (p->timer & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  } else if (p->timer < 128) {
    s->flags = (p->timer & 3) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  }
}

static void Hottalook_Die(struct Hottalook* p);

// 0x08081030: an element hit makes it fall. It shatters on the ground, or keeps flying if the effect ends
static void Hottalook_Fall(struct Hottalook* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sHottalookHarmless);
    s->d.y = 0;
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = 0;
    EXIT_BODY(p);
    Hottalook_Die(p);
  } else if (IsDead(s->unk_2c)) {
    s->unk_2c = NULL;
    setMode(s, HOTTALOOK_FLY);
  }
}

static void Hottalook_Recoil(struct Hottalook* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Hottalook_Die(p);
  }
}

static const EnemyFunc sHottalookUpdates[4] = {
    [HOTTALOOK_HATCH] = (EnemyFunc)Hottalook_Hatch,
    [HOTTALOOK_CIRCLE] = (EnemyFunc)Hottalook_Circle,
    [HOTTALOOK_FLY] = (EnemyFunc)Hottalook_Fly,
    [HOTTALOOK_FALL] = (EnemyFunc)Hottalook_Fall,
};

// 0x08080b8c
static void Hottalook_Update(struct Hottalook* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != HOTTALOOK_RECOIL) setMode(s, HOTTALOOK_RECOIL);
  if (s->mode[1] == HOTTALOOK_RECOIL) {
    Hottalook_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 kind = 0;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? 2 : 1;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    EXIT_BODY(p);
    Hottalook_Die(p);
    return;
  }

  gOverworld.work.apZ2Bomber2.lit[s->COLOR] = TRUE;

  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) setMode(s, HOTTALOOK_FALL);
  }
  (sHottalookUpdates[s->mode[1]])((void*)p);
}

// 0x080810cc, 0x08081250, 0x080813d4: 
static void Hottalook_Die(struct Hottalook* p) {
  struct Entity* s = &p->s;
  u8 kind = s->mode[1] == 2;
  u8 angle, n, i;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, FLY_ANIM(p));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] < 2) return;

  PlaySound(SE_ZAKO_EXPLODE);
  angle = (RANDOM(RNG_0202f388) & 31) - 15;
  if (!(s->flags & X_FLIP)) angle += 128;
  createShard(s, kind, angle, MOTION(AP_SHEET_Z2_HOTTALOOK, 4));
  angle = RANDOM(RNG_0202f388);
  n = (RANDOM(RNG_0202f388) & 1) + 4;
  for (i = 0; i < n; i++) {
    createShard(s, kind, angle, MOTION(AP_SHEET_Z2_HOTTALOOK, (5 + RANDOM(RNG_0202f388) % 3)));
    angle += 32 + (RANDOM(RNG_0202f388) & 15);
  }
  CreateSmoke(2, &s->coord);
  TryDropItem(2, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  ApImportHottalookKilled();
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void Shard_Init(struct Entity* p);
static void Shard_Update(struct Entity* p);
static void Shard_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2HottalookShardRoutine = {
    [ENTITY_INIT] =      (void*)Shard_Init,
    [ENTITY_UPDATE] =    (void*)Shard_Update,
    [ENTITY_DIE] =       (void*)Shard_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

#define SHARD_MOTION unk_coord.x
#define SHARD_SPEED unk_coord.y

// 0x080b98cc.
static void createShard(struct Entity* parent, u8 kind, u8 angle, u16 motion) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_HOTTALOOK_SHARD);
    p->coord = parent->coord;
    p->work[0] = kind;
    p->work[1] = angle;
    p->work[3] = (parent->flags & X_FLIP) != 0;
    p->SHARD_MOTION = motion;
  }
}

// 0x080b9930
static void Shard_Init(struct Entity* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(p);
  useApSheets(p);
  SET_XFLIP(p, p->work[3]);
  SetSpriteAnimation(p, p->SHARD_MOTION);
  p->flags |= DISPLAY | FLIPABLE;
  p->work[2] = 0;
  p->SHARD_SPEED = (RANDOM(RNG_0202f388) & 255) + (p->work[0] ? 576 : 384);
  Shard_Update(p);
}

// 0x080b9a14
static void Shard_Update(struct Entity* p) {
  UpdateSpriteAnimation(p);
  p->SHARD_SPEED -= 12;
  if (p->SHARD_SPEED < 0) {
    Shard_Die(p);
    return;
  }
  (p->d).x = Cos(p->work[1], p->SHARD_SPEED);
  (p->d).y = Sin(p->work[1], p->SHARD_SPEED);
  (p->coord).x += (p->d).x;
  (p->coord).y += (p->d).y;
  if (p->SHARD_SPEED <= 256) {
    p->flags = (++p->work[2] & 1) ? (p->flags | DISPLAY) : (p->flags & ~DISPLAY);
  }
}

// 0x080b9aa0
static void Shard_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2 data. 

// clang-format off
static const struct Collision sHiveCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x01, NO_DAMAGE | HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x01, NO_DAMAGE | HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHiveHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, NO_DAMAGE | HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, NO_DAMAGE | HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

// Until it swoops in
static const struct Collision sHiveHidden[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sHottalookCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x02, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0xc00, 0xc00}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x02, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0xc00, 0xc00}},
};

static const struct Collision sHottalookHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0xc00, 0xc00}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0xc00, 0xc00}},
};
// clang-format on

#endif  // AP
