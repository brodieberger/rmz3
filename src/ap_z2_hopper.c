#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "vfx.h"
#include "zero.h"

#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

struct Hopper {
  OBJECT_HDR;
  s32 targetX;  // 0xB4, where Zero was
  u8 prevMode;  // 0xB8, mode[1] before the last decision
  u8 hitbox;
  u8 _[10];
};
static_assert(sizeof(struct Hopper) == sizeof(struct Enemy));

enum {
  HOPPER_IDLE,
  HOPPER_CRAWL,
  HOPPER_LEAP,
  HOPPER_FALL,
  HOPPER_HIT,
  HOPPER_TURN,
  HOPPER_ELEMENT_HIT,
};

static const struct Collision sCollisions[8];
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sGibsHard[3];
static const Coords32 sElementCoord = {0, -PIXEL(12)};

static void Hopper_Init(struct Hopper* p);
static void Hopper_Update(struct Hopper* p);
static void Hopper_Die(struct Hopper* p);
static void Hopper_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED);
static void createUpperHalf(struct Hopper* p, Coords32* c, u8 kind);

// clang-format off
const EnemyRoutine gApZ2HopperRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Hopper_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Hopper_Update,
    [ENTITY_DIE] =       (EnemyFunc)Hopper_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

#define FACING_RIGHT(p) (((p)->s.flags & X_FLIP) != 0)

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static bool8 isLadder(s32 x, s32 y) { return GetMetatileAttr(x, y) == 0x800F; }

static bool8 isWall(s32 x, s32 y) { return FUN_080098a4(x, y) != 0 && !isLadder(x, y); }

static void stopAtWall(struct Hopper* p) {
  if ((p->s).d.x < 0) {
    (p->s).coord.x = FUN_0800a31c((p->s).coord.x, (p->s).coord.y);
  } else {
    (p->s).coord.x = FUN_0800a22c((p->s).coord.x, (p->s).coord.y);
  }
}

static void fall(struct Hopper* p) {
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) (p->s).d.y = 0x700;
}

static void setMode(struct Hopper* p, u8 mode) {
  p->prevMode = (p->s).mode[1];
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

// 0x08076e8c
static void Hopper_Decide(struct Hopper* p) {
  u8 m = (p->s).mode[1];
  p->targetX = (pZero2->s).coord.x;
  if (FACING_RIGHT(p) != ((p->s).coord.x < p->targetX)) {
    setMode(p, HOPPER_TURN);
  } else if (m == HOPPER_CRAWL && p->prevMode == HOPPER_CRAWL) {
    setMode(p, HOPPER_IDLE);
  } else if (m == HOPPER_IDLE && p->prevMode == HOPPER_IDLE) {
    setMode(p, HOPPER_CRAWL);
  } else if (m == HOPPER_LEAP && p->prevMode == HOPPER_LEAP) {
    setMode(p, (RANDOM(RNG_0202f388) & 1) ? HOPPER_IDLE : HOPPER_CRAWL);
  } else if ((u32)(p->targetX - (p->s).coord.x + PIXEL(96)) <= PIXEL(192)) {
    switch (RANDOM(RNG_0202f388) & 3) {
      case 0: setMode(p, HOPPER_CRAWL); break;
      case 1: setMode(p, HOPPER_IDLE); break;
      default: setMode(p, HOPPER_LEAP); break;
    }
  } else {
    setMode(p, (RANDOM(RNG_0202f388) & 1) ? HOPPER_CRAWL : HOPPER_IDLE);
  }
}

static void Hopper_Init(struct Hopper* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x);
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 0));
  UpdateSpriteAnimation(p);
  (p->s).flags |= DISPLAY | FLIPABLE;
  (p->s).unk_2c = NULL;
  p->hitbox = 0;
  (p->s).d.x = (p->s).d.y = 0;
  INIT_BODY(p, sCollisions, 6, Hopper_OnCollision);
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  Hopper_Update(p);
}

static void Hopper_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = (p->coord).x < (pZero2->s).coord.x;
  }
}

static const EnemyFunc sUpdates[7];

// 0x080760f4
static void Hopper_Update(struct Hopper* p) {
  u32 status = (p->body).status;

  if (status & BODY_STATUS_DEAD) {
    u8 kind = 0;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? 2 : 1;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = kind;
    EXIT_BODY(p);
    Hopper_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if ((p->s).unk_2c != NULL) {
      (p->s).unk_2c = NULL;
      SetDDP(&p->body, &sCollisions[p->hitbox * 2]);
    }
    return;
  }

  if ((status & BODY_STATUS_WHITE) && (p->s).unk_2c == NULL) {
    (p->s).unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    (p->s).mode[1] = ((p->s).unk_2c != NULL) ? HOPPER_ELEMENT_HIT : HOPPER_HIT;
    (p->s).mode[2] = 0;
  }

  if ((p->s).unk_2c != NULL) {
    if (IsDead((p->s).unk_2c)) (p->s).unk_2c = NULL;
  } else if (GetMetatileAttr((p->s).coord.x, (p->s).coord.y + PIXEL(1)) & MTATTR_SPIKE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Hopper_Die(p);
    return;
  } else {
    u8 m = (p->s).mode[1];
    if ((m < HOPPER_LEAP || m > HOPPER_HIT) && FUN_080098a4((p->s).coord.x, (p->s).coord.y + PIXEL(8)) == 0) {
      (p->s).mode[1] = HOPPER_FALL, (p->s).mode[2] = 0;
    }
  }

  (sUpdates[(p->s).mode[1]])((void*)p);
}

// 0x080762cc
static void Hopper_Idle(struct Hopper* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 0));
    SetDDP(&p->body, &sCollisions[0]);
    p->hitbox = 0;
    (p->s).work[2] = 32;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--(p->s).work[2] == 0) Hopper_Decide(p);
}

// 0x0807631c
static void Hopper_Crawl(struct Hopper* p) {
  s32 x;
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 1));
    SetDDP(&p->body, &sCollisions[0]);
    p->hitbox = 0;
    (p->s).d.x = FACING_RIGHT(p) ? 0x20 : -0x20;
    (p->s).work[2] = 128;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  x = (p->s).coord.x + (p->s).d.x;
  if (FUN_080098a4(x, (p->s).coord.y - PIXEL(12)) != 0 || FUN_080098a4(x, (p->s).coord.y + PIXEL(8)) == 0) {
    p->targetX = (p->s).coord.x + (FACING_RIGHT(p) ? PIXEL(64) : -PIXEL(64));
    setMode(p, HOPPER_LEAP);
    return;
  }
  (p->s).coord.x = x;
  (p->s).coord.y = FUN_08009f6c(x, (p->s).coord.y);
  if (--(p->s).work[2] == 0) Hopper_Decide(p);
}

// 0x080763f8
static void Hopper_Leap(struct Hopper* p) {
  struct Entity* s = &p->s;
  s32 x, y;
  if (s->mode[2] == 0) {
    s32 dx = p->targetX - s->coord.x;
    s32 adx = dx < 0 ? -dx : dx;
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 2));
    SetDDP(&p->body, &sCollisions[2]);
    p->hitbox = 1;
    if (adx <= 0x1FFF) {
      dx = FACING_RIGHT(p) ? PIXEL(32) : -PIXEL(32);
    } else if (adx > PIXEL(96)) {
      dx = FACING_RIGHT(p) ? PIXEL(96) : -PIXEL(96);
    }
    s->d.y = -(u16)Sqrt(0x280000);
    s->d.x = dx / (u16)(-(s->d.y >> 5));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);

  switch (s->mode[2]) {
    case 1:
      s->coord.x += s->d.x;
      if (isWall(s->coord.x, s->coord.y - PIXEL(12))) {
        if (s->d.x < 0) {
          s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y - PIXEL(12));
        } else if (s->d.x > 0) {
          s->coord.x = FUN_0800a22c(s->coord.x, s->coord.y - PIXEL(12));
        }
      }
      fall(p);
      if (s->d.y < 0) {
        x = s->coord.x, y = s->coord.y - PIXEL(12);
        if (isWall(x, y)) {
          s->coord.y = FUN_0800a134(x, y) + PIXEL(12);
          s->d.y = 0;
        }
      } else if (isWall(s->coord.x, s->coord.y + PIXEL(32))) {
        SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 3));
        UpdateSpriteAnimation(p);
        s->mode[2]++;
      }
      break;

    case 2:
      s->coord.x += s->d.x;
      if (isWall(s->coord.x, s->coord.y) && s->d.x != 0) {
        stopAtWall(p);
        s->d.x = 0;
      }
      fall(p);
      if (isWall(s->coord.x, s->coord.y)) {
        if (s->d.y < 0) {
          s->coord.y = FUN_0800a134(s->coord.x, s->coord.y);
          s->d.y = 0;
        } else {
          SetDDP(&p->body, &sCollisions[0]);
          s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
          s->mode[2]++;
        }
      }
      break;

    default:
      if (IsSpriteAnimEnd(p)) Hopper_Decide(p);
      break;
  }
}

// 0x080766e4
static void Hopper_Fall(struct Hopper* p) {
  if ((p->s).mode[2] == 0) {
    if ((p->s).unk_2c == NULL) {
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 0));
      SetDDP(&p->body, &sCollisions[0]);
      p->hitbox = 0;
    }
    (p->s).d.y = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((p->s).mode[2] == 1) {
    fall(p);
    if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) == 0) return;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[2]++;
  }
  if ((p->s).unk_2c == NULL) Hopper_Decide(p);
}

static void knockBack(struct Hopper* p, const struct Collision* collisions) {
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 4));
  SetDDP(&p->body, collisions);
  p->hitbox = 1;
  (p->s).d.x = ((p->s).coord.x < (pZero2->s).coord.x) ? -0x180 : 0x180;
  (p->s).d.y = -0x280;
  (p->s).mode[2]++;
}

// 0x08076770
static void Hopper_Hit(struct Hopper* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) knockBack(p, &sCollisions[2]);
  UpdateSpriteAnimation(p);
  s->coord.x += s->d.x;
  if (isWall(s->coord.x, s->coord.y)) {
    stopAtWall(p);
    s->d.x = 0;
  }
  fall(p);
  if (isWall(s->coord.x, s->coord.y)) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    Hopper_Decide(p);
  }
}

// 0x0807685c
static void Hopper_Turn(struct Hopper* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 0));
    SetDDP(&p->body, &sCollisions[0]);
    p->hitbox = 0;
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (p->s).work[2]++;
  if ((p->s).work[2] == 16) {
    SET_XFLIP(p, (p->s).coord.x < p->targetX);
  } else if ((p->s).work[2] == 24) {
    Hopper_Decide(p);
  }
}

// 0x08076918
static void Hopper_ElementHit(struct Hopper* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) knockBack(p, &sCollisions[6]);
  UpdateSpriteAnimation(p);
  if (s->mode[2] == 1) {
    s->coord.x += s->d.x;
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      stopAtWall(p);
      s->d.x = 0;
    }
    fall(p);
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    s->mode[2]++;
  }
  if (s->unk_2c == NULL) Hopper_Decide(p);
}

static const EnemyFunc sUpdates[7] = {
    [HOPPER_IDLE] = (EnemyFunc)Hopper_Idle,
    [HOPPER_CRAWL] = (EnemyFunc)Hopper_Crawl,
    [HOPPER_LEAP] = (EnemyFunc)Hopper_Leap,
    [HOPPER_FALL] = (EnemyFunc)Hopper_Fall,
    [HOPPER_HIT] = (EnemyFunc)Hopper_Hit,
    [HOPPER_TURN] = (EnemyFunc)Hopper_Turn,
    [HOPPER_ELEMENT_HIT] = (EnemyFunc)Hopper_ElementHit,
};

// --------------------------------------------

static Coords32 smokeNearby(Coords32 c) {
  c.x += ((RANDOM(RNG_0202f388) & 15) - 8) << 8;
  c.y += ((RANDOM(RNG_0202f388) & 15) - 8) << 8;
  return c;
}

// 0x08077028 / 0x080770d4, 0x080769fc
static Coords32 explode(struct Hopper* p, const struct SlashedEnemy* gibs) {
  u8 flip = (p->s).work[3] | (FACING_RIGHT(p) << 4);
  Coords32 c;
  c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(12);
  PlaySound(SE_ZAKO_EXPLODE);
  useApSheets(CreateSlashedEnemy(&c, &gibs[0], 0, flip));
  useApSheets(CreateSlashedEnemy(&c, &gibs[1], 0, flip));
  useApSheets(CreateSlashedEnemy(&c, &gibs[2], 0, flip));
  c = smokeNearby(c);
  CreateSmoke(1, &c);
  return c;
}

static void finish(struct Hopper* p) {
  TryDropItem(1, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x080769fc
static void Hopper_Explode(struct Hopper* p) {
  if ((p->s).mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 4));
    (p->s).work[2] = 0;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++(p->s).work[2] > 1) {
    Coords32 c = smokeNearby(explode(p, sGibs));
    CreateSmoke(2, &c);
    finish(p);
  }
}

static void Hopper_CutInHalf(struct Hopper* p) {
  struct Entity* s = &p->s;
  bool8 hard = s->mode[1] == 2;
  if (s->mode[2] == 0) {
    u8 xflip = FACING_RIGHT(p);
    s32 k = 1 - 2 * xflip;
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 5));
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) {
      if (hard) {
        s->d.y += 0x300;
        if (s->d.y > 0x700) s->d.y = 0x700;
        createUpperHalf(p, &s->coord, 1);
      } else {
        Coords32 c = s->coord;
        s->d.y = (s->d.y < -0x200) ? s->d.y + 0x200 : 0;
        createUpperHalf(p, &c, 0);
      }
      s->mode[2] = 3;
    } else {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->d.y = 0;
      if (hard) {
        s->d.x = -k * 0x300, s->unk_coord.x = k * 0x40;
        createUpperHalf(p, &s->coord, 1);
      } else {
        Coords32 c;
        s->d.x = -k * 0x60, s->unk_coord.x = k * 4;
        c.x = s->coord.x + k * 0x200, c.y = s->coord.y + 0x300;
        createUpperHalf(p, &c, 0);
      }
      s->mode[2] = 1;
    }
    s->work[2] = 0;
  }

  if (s->work[2] != 0xFF) {
    UpdateSpriteAnimation(p);
    s->work[2]++;
    switch (s->mode[2]) {
      case 1: 
        if (hard && FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) goto airborne;
        s->coord.x += s->d.x;
        s->d.x += s->unk_coord.x;
        if (!hard && FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) goto airborne;
        if (s->d.x == 0) s->mode[2]++;
        return;
      case 2: 
        if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) goto airborne;
        if (s->work[2] <= (hard ? 11 : 15)) return;
        break;
      case 3: 
        s->coord.x += s->d.x;
        fall(p);
        if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(4)) == 0) return;
        break;
      default:
        return;
    }
  }
  explode(p, hard ? sGibsHard : sGibs);
  finish(p);
  return;

airborne:
  s->d.x = s->d.y = 0;
  s->mode[2] = 3;
}

static const EnemyFunc sDies[3] = {
    (EnemyFunc)Hopper_Explode,
    (EnemyFunc)Hopper_CutInHalf,
    (EnemyFunc)Hopper_CutInHalf,
};

// 0x08076264
static void Hopper_Die(struct Hopper* p) { (sDies[(p->s).mode[1]])((void*)p); }

static const struct SlashedEnemy sTopGibs[2];

static void UpperHalf_Init(struct Entity* p);
static void UpperHalf_Update(struct Entity* p);
static void UpperHalf_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2HopperTopRoutine = {
    [ENTITY_INIT] =      (void*)UpperHalf_Init,
    [ENTITY_UPDATE] =    (void*)UpperHalf_Update,
    [ENTITY_DIE] =       (void*)UpperHalf_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

static void createUpperHalf(struct Hopper* legs, Coords32* c, u8 kind) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_HOPPER_TOP);
    p->unk_28 = &legs->s;
    p->coord = *c;
    p->work[0] = kind;
  }
}

static void UpperHalf_Init(struct Entity* p) {
  struct Entity* legs = p->unk_28;
  bool8 xflip = (legs->flags & X_FLIP) != 0;
  s32 k = 1 - 2 * xflip;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(p);
  useApSheets(p);
  SET_XFLIP(p, xflip);
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_HOPPER, 6));
  p->flags |= DISPLAY | FLIPABLE;
  p->work[2] = 0;
  if (FUN_080098a4((p->coord).x, (p->coord).y + PIXEL(8)) == 0) {
    (p->d).x = (legs->d).x + k * (p->work[0] ? 0x100 : 0x90);
    (p->d).y = (legs->d).y;
    p->mode[1] = 2;
  } else {
    (p->d).x = k * (p->work[0] ? 0x300 : 0x60);
    p->unk_coord.x = -k * (p->work[0] ? 0x40 : 4);
    (p->d).y = 0;
    p->mode[1] = 0;
  }
  UpperHalf_Update(p);
}

static void UpperHalf_Burst(struct Entity* p) {
  Coords32 c;
  bool8 xflip = (p->flags & X_FLIP) != 0;
  c.x = (p->coord).x, c.y = (p->coord).y - PIXEL(12);
  useApSheets(CreateSlashedEnemy(&c, &sTopGibs[p->work[0]], 0, xflip | (xflip << 4)));
  c = smokeNearby(c);
  CreateSmoke(1, &c);
  SET_VFX_ROUTINE(p, ENTITY_DIE);
  UpperHalf_Die(p);
}

static void UpperHalf_Update(struct Entity* p) {
  s32 front;
  if (p->work[2] == 0xFF) {
    UpperHalf_Burst(p);
    return;
  }
  UpdateSpriteAnimation(p);
  p->work[2]++;
  switch (p->mode[1]) {
    case 0:
      (p->coord).x += (p->d).x;
      (p->d).x += p->unk_coord.x;
      front = (p->coord).x + ((p->flags & X_FLIP) ? PIXEL(12) : -PIXEL(12));
      if (FUN_080098a4(front, (p->coord).y + PIXEL(8)) == 0) {
        (p->d).x = (p->d).y = 0;
        p->mode[1] = 2;
      } else if ((p->d).x == 0) {
        p->mode[1]++;
      }
      break;
    case 1:
      front = (p->coord).x + ((p->flags & X_FLIP) ? PIXEL(12) : -PIXEL(12));
      if (FUN_080098a4(front, (p->coord).y + PIXEL(8)) == 0) {
        (p->d).x = (p->d).y = 0;
        p->mode[1] = 2;
      } else if (p->work[2] > (p->work[0] ? 11 : 15)) {
        UpperHalf_Burst(p);
      }
      break;
    case 2:  // falling
      (p->coord).x += (p->d).x;
      (p->coord).y += (p->d).y;
      (p->d).y += 0x40;
      if ((p->d).y > 0x700) (p->d).y = 0x700;
      front = (p->coord).x + ((p->flags & X_FLIP) ? PIXEL(12) : -PIXEL(12));
      if (FUN_080098a4(front, (p->coord).y - PIXEL(4)) != 0) UpperHalf_Burst(p);
      break;
  }
}

// 0x080b5814
static void UpperHalf_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2 data.

// clang-format off
static const struct Collision sCollisions[8] = {
    // standing
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0, 1, 0x00000001, {0x0, -0x400, 0x1800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0x400, 0x1800, 0x800}},
    // leaping and knocked back
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0, 1, 0x00000001, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
    // harmless
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0x400, 0x1800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0x400, 0x1800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x08, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
};

static const struct SlashedEnemy sGibs[3] = {
    {MOTION(AP_SHEET_Z2_HOPPER, 7), {0xff, 0x11}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_HOPPER, 8), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_HOPPER, 9), {0xff, 0x11}, {0, 0}, {128, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sGibsHard[3] = {
    {MOTION(AP_SHEET_Z2_HOPPER, 7), {0xff, 0x11}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_HOPPER, 8), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_HOPPER, 9), {0xff, 0x11}, {0, 0}, {192, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sTopGibs[2] = {
    {MOTION(AP_SHEET_Z2_HOPPER, 8), {0xff, 0x11}, {0, 0}, {16, -768}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_HOPPER, 8), {0xff, 0x11}, {0, 0}, {64, -1536}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
