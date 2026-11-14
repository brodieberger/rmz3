#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's pipe crawler, enemy 22. Walks a pipe's top or underside, rolls round it, shoots in threes.
  orient: 0 on top, 3 underneath, 1, 2, 4, 5 rolling round
*/

struct Crawler {
  OBJECT_HDR;
  u8 _b4;
  u8 hitbox;        // 0xB5, orient its hitboxes are for
  u8 orient;        // 0xB6
  bool8 zeroRight;  // 0xB7, when it took aim
  u8 elementTime;   // 0xB8
  s8 dir;           // 0xB9
  u8 last;          // 0xBA, mode[1] chosen last
  u8 before;        // 0xBB, and before that
  u8 period;        // 0xBC, frames a roll step
  u8 _bd[7];
};
static_assert(sizeof(struct Crawler) == sizeof(struct Enemy));

// Zero 2's 2 rolls round, but nothing reaches it
enum {
  CRAWLER_IDLE = 0,
  CRAWLER_WALK = 1,
  CRAWLER_SHOOT = 3,
  CRAWLER_DASH = 4,
  CRAWLER_RECOIL = 5,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_CRAWLER, (n))

static const struct Collision sCollisions[6][2];
static const struct Collision sElemented[6][2];
static const struct SlashedEnemy sGibs[4];
static const Coords32 sElementCoord[6];

static void Crawler_Init(struct Crawler* p);
static void Crawler_Update(struct Crawler* p);
static void Crawler_Die(struct Crawler* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static void createBit(Coords32* at, u8 kind, u8 dir, bool8 yflip);

// clang-format off
const EnemyRoutine gApZ2CrawlerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Crawler_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Crawler_Update,
    [ENTITY_DIE] =       (EnemyFunc)Crawler_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheet(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Crawler* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
}

static bool8 yflipped(struct Crawler* p) { return ((p->s).flags & Y_FLIP) != 0; }

// 0x080725b0
static void Crawler_Init(struct Crawler* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->mode[2] = 0;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SET_XFLIP(p, FALSE);
  SET_YFLIP(p, FALSE);
  SetMotion(s, ANIM(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = 0x100;
  s->d.y = 0;
  p->hitbox = 0;
  p->orient = 0;
  p->dir = 1;
  p->last = p->before = 0xFF;
  s->unk_2c = NULL;
  p->elementTime = 0;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + PIXEL(8);
  INIT_BODY(p, &sCollisions[0][0], 16, onCollision);
  Crawler_Update(p);
}

static void setHitbox(struct Crawler* p, u8 orient) {
  p->hitbox = orient;
  SetDDP(&p->body, &sCollisions[orient][0]);
}

// Underneath, it stands as on top, flipped
static void stand(struct Crawler* p) {
  if (p->orient == 3) {
    SET_YFLIP(p, TRUE);
    setHitbox(p, 0);
  }
}

static void unstand(struct Crawler* p) {
  if (p->orient == 3) {
    SET_YFLIP(p, FALSE);
    setHitbox(p, 3);
  }
}

// 0x08073758: Zero within w either side of its middle, h up or down
static bool8 zeroNear(struct Crawler* p, s32 w, s32 h) {
  struct Entity* s = &p->s;
  s32 y = yflipped(p) ? s->coord.y + h : s->coord.y - h;
  return (u32)((pZero2->s).coord.x - s->coord.x + w) <= (u32)(2 * w) &&
         (u32)((pZero2->s).coord.y - y + h) <= (u32)(2 * h);
}

// 0x080736cc: walking, close it shoots or dashes, alternating
static void decide(struct Crawler* p) {
  u8 next;
  if ((p->s).mode[1] != CRAWLER_WALK) return;
  if (zeroNear(p, PIXEL(56), PIXEL(96))) {
    next = p->last == CRAWLER_DASH ? CRAWLER_SHOOT : CRAWLER_DASH;
  } else if (zeroNear(p, PIXEL(112), PIXEL(96))) {
    next = p->last == CRAWLER_SHOOT && p->before == CRAWLER_SHOOT ? CRAWLER_DASH : CRAWLER_SHOOT;
  } else {
    next = CRAWLER_WALK;
  }
  setMode(p, next);
  p->before = p->last;
  p->last = next;
}

static void Crawler_Idle(struct Crawler* p);
static void Crawler_Walk(struct Crawler* p);
static void Crawler_Shoot(struct Crawler* p);
static void Crawler_Dash(struct Crawler* p);
static void Crawler_Recoil(struct Crawler* p);
static void Crawler_Elemented(struct Crawler* p);

// 0x08072694
static void Crawler_Update(struct Crawler* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (ApRecoilHit((Object*)p) && s->mode[1] != CRAWLER_RECOIL) setMode(p, CRAWLER_RECOIL);
  if (s->mode[1] == CRAWLER_RECOIL) {
    Crawler_Recoil(p);
    return;
  }
  if (status & BODY_STATUS_DEAD) {
    u8 kind = 0;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? 2 : 1;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    s->mode[2] = 0;
    EXIT_BODY(p);
    Crawler_Die(p);
    return;
  }
  if (IsFrozen(p)) {
    if (p->elementTime != 0) {
      s->unk_2c = NULL;
      p->elementTime = 0;
      SetDDP(&p->body, &sCollisions[p->hitbox][0]);
    }
    return;
  }
  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL && p->elementTime == 0) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord[p->hitbox]);
    if (s->unk_2c != NULL || (p->body).elemented == 2) p->elementTime = 88;
  }
  if (p->elementTime != 0) {
    Crawler_Elemented(p);
    return;
  }
  decide(p);
  switch (s->mode[1]) {
    case CRAWLER_IDLE: Crawler_Idle(p); break;
    case CRAWLER_WALK: Crawler_Walk(p); break;
    case CRAWLER_SHOOT: Crawler_Shoot(p); break;
    case CRAWLER_DASH: Crawler_Dash(p); break;
  }
}

// 0x08072858
static void Crawler_Idle(struct Crawler* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 15) setMode(p, CRAWLER_WALK);
}

/*
  0x080728b4, 0x08072e88: a step along the pipe. Its feet are 8 px into it.
  At its end or a wall, snaps to the edge and turns. Returns whether it turned.
*/
static bool8 step(struct Crawler* p) {
  struct Entity* s = &p->s;
  s32 ahead = s->coord.x + (s->d.x + PIXEL(12)) * p->dir;
  s32 y = s->coord.y;
  if (FUN_080098a4(ahead, y) == 0) {
    s->coord.x = p->dir < 0 ? FUN_0800a22c(s->coord.x, y) + PIXEL(12) : FUN_0800a31c(s->coord.x, y) - PIXEL(12);
  } else if (FUN_080098a4(ahead, y - PIXEL(16)) != 0) {
    y -= PIXEL(16);
    s->coord.x = p->dir < 0 ? FUN_0800a31c(s->coord.x, y) + PIXEL(12) : FUN_0800a22c(s->coord.x, y) - PIXEL(12);
  } else if (FUN_080098a4(ahead, y + PIXEL(16)) != 0) {
    y += PIXEL(16);
    s->coord.x = p->dir < 0 ? FUN_0800a31c(s->coord.x, y) + PIXEL(12) : FUN_0800a22c(s->coord.x, y) - PIXEL(12);
  } else {
    s->coord.x += p->dir * s->d.x;
    return FALSE;
  }
  p->dir = -p->dir;
  return TRUE;
}

// 0x080728b4: decide() restarts it every frame, so it never tires
static void Crawler_Walk(struct Crawler* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    stand(p);
    SetMotion(s, ANIM(0));
    s->d.x = 0x100;
    s->work[2] = 0;
    s->mode[3]++;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  step(p);
}

static const motion_t sRollMotions[6] = {ANIM(11), ANIM(6), ANIM(7), ANIM(8), ANIM(9), ANIM(10)};

static bool8 rollStep(struct Crawler* p) {
  if (++p->orient > 5) p->orient = 0;
  SetMotion(&p->s, sRollMotions[p->orient]);
  setHitbox(p, p->orient);
  return p->orient == 0 || p->orient == 3;
}

// 0x08072dac: rolls round the pipe, a step every 4 frames
static bool8 roll(struct Crawler* p) {
  struct Entity* s = &p->s;
  bool8 done = FALSE;
  if (s->mode[3] == 0) {
    unstand(p);
    SetMotion(s, sRollMotions[p->orient]);
    s->work[2] = 1;
    s->mode[3]++;
  }
  if ((s->work[2] & 3) == 0) done = rollStep(p);
  UpdateEntityAnim(s);
  s->work[2]++;
  return done;
}

// 0x08072afc, 0x08072b94: aims 32 frames, then three shots
static void Crawler_Shoot(struct Crawler* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 up = yflipped(p) ? PIXEL(32) : -PIXEL(32);
  if (s->mode[2] == 0) {
    if (s->mode[3] == 0) {
      stand(p);
      SetMotion(s, ANIM(5));
      p->zeroRight = s->coord.x < (pZero2->s).coord.x;
      s->work[2] = 0;
      s->mode[3]++;
    }
    UpdateEntityAnim(s);
    if (++s->work[2] > 31) {
      s->mode[2]++;
      s->mode[3] = 0;
    }
    return;
  }
  if (s->mode[3] == 0) {
    SetMotion(s, ANIM(0));
    s->work[2] = 0;
    s->mode[3]++;
  }
  switch (s->work[2]) {
    case 4:
    case 10:
    case 16:
      SetMotion(s, p->zeroRight ? ANIM(2) : ANIM(1));
      at.x = s->coord.x + (p->zeroRight ? -PIXEL(4) : PIXEL(4));
      at.y = s->coord.y + up;
      createBit(&at, 0, !p->zeroRight, yflipped(p));
      break;
    case 8:
    case 14:
    case 20:
      at.x = s->coord.x + (p->zeroRight ? PIXEL(16) : -PIXEL(16));
      at.y = s->coord.y + up;
      CreateLemon(&at, 0x280, p->zeroRight ? 128 : 0);
      PlaySound(SE_ENEMY_SHOT);
      break;
    case 38:
      setMode(p, CRAWLER_WALK);
      return;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
}

/*
  0x08072dac, 0x08072e88, 0x08073044: rolls to the other side, dashes at 3 px until under Zero
  or 48 frames, then rolls back, slowing
*/
static void Crawler_Dash(struct Crawler* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      if (roll(p)) {
        s->mode[2]++;
        s->mode[3] = 0;
      }
      break;
    case 1:
      if (s->mode[3] == 0) {
        stand(p);
        SetMotion(s, ANIM(0));
        s->d.x = 0x300;
        s->work[2] = 0;
        s->mode[3]++;
      }
      UpdateEntityAnim(s);
      s->work[2]++;
      if (step(p) || (u32)((pZero2->s).coord.x - s->coord.x + PIXEL(4)) <= PIXEL(8) || s->work[2] > 47) {
        s->mode[2]++;
        s->mode[3] = 0;
      }
      break;
    case 2:
      if (s->mode[3] == 0) {
        unstand(p);
        SetMotion(s, sRollMotions[p->orient]);
        p->period = 12;
        s->work[2] = 1;
        s->mode[3]++;
      }
      if (s->work[2] % p->period == 0) {
        if (rollStep(p)) setMode(p, CRAWLER_WALK);
        p->period >>= 1;
      }
      UpdateEntityAnim(s);
      s->work[2]++;
      break;
  }
}

// Same as the Pantheon Hunter's, 0x08064cac
static void Crawler_Recoil(struct Crawler* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Crawler_Die(p);
  }
}

// 0x080732f4: burning or frozen 88 frames, harmless
static void Crawler_Elemented(struct Crawler* p) {
  struct Entity* s = &p->s;
  if (p->elementTime == 88) {
    SetDDP(&p->body, &sElemented[p->hitbox][0]);
    if (s->mode[1] == CRAWLER_SHOOT && (s->motion.id == 1 || s->motion.id == 2)) SetMotion(s, ANIM(0));
  }
  if (--p->elementTime == 0) {
    s->unk_2c = NULL;
    SetDDP(&p->body, &sCollisions[p->hitbox][0]);
  }
}

// 0x080739e0
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) s->work[3] = s->coord.x < (pZero2->s).coord.x;
}

// --------------------------------------------

static Coords32 nearby(Coords32 c) {
  c.x += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 7);
  c.y += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 7);
  return c;
}

// 0x080737c8: falls apart, top half 22 px from its feet
static void burst(struct Crawler* p, bool8 bits) {
  struct Entity* s = &p->s;
  u8 flip = s->work[3] | (((s->flags & X_FLIP) ? 1 : 0) << 4);
  Coords32 top, c;
  top.x = s->coord.x;
  top.y = s->coord.y + (yflipped(p) ? PIXEL(22) : -PIXEL(22));
  useApSheet(CreateSlashedEnemy(&s->coord, &sGibs[0], 0, flip));
  useApSheet(CreateSlashedEnemy(&s->coord, &sGibs[1], 0, flip));
  useApSheet(CreateSlashedEnemy(&top, &sGibs[2], 0, flip));
  useApSheet(CreateSlashedEnemy(&top, &sGibs[3], 0, flip));
  if (bits) createBit(&top, 3, 0, yflipped(p));
  c = nearby(s->coord);
  CreateSmoke(1, &c);
  c = nearby(s->coord);
  CreateSmoke(2, &c);
  PlaySound(SE_ZAKO_EXPLODE);
}

static void finish(struct Crawler* p) {
  TryDropItem(2, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  ApImportCrawlerKilled();
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

/*
  0x08073384, 0x080734e4, 0x080735d8
  mode[1]: 0 bursts, 1 cut, 2 cut by an element, its top flies off and it bursts 32 frames on
*/
static void Crawler_Die(struct Crawler* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    burst(p, TRUE);
    finish(p);
    return;
  }
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    if (p->orient >= 2 && p->orient <= 4) SET_YFLIP(p, TRUE);
    createBit(&s->coord, s->mode[1], s->work[3] ^ 1, yflipped(p));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] < 32) return;
  burst(p, FALSE);
  finish(p);
}

// --------------------------------------------
/*
  Zero 2's VFX 27, the crawler's bits.
  work0:
    0: spent shell, bounces once
    1: its top, cut off, flies up and bursts where it lands
    2: same, cut by an element, slides and bursts
    3: debris
  work1: 0 thrown left, 1 right
*/

struct Bit {
  struct Entity s;
  bool8 yflip;    // 0x74
  bool8 bounced;  // 0x75
  u8 landed;      // 0x76, frames since
  u8 _[13];
};
static_assert(sizeof(struct Bit) == sizeof(struct VFX));

static void Bit_Init(struct Bit* p);
static void Bit_Update(struct Bit* p);

// clang-format off
const VFXRoutine gApZ2CrawlerBitRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Bit_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Bit_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x08346c20, 0x08346c28, 0x08346c30: x, y, w, h
static const s16 sShellBox[4] = {0, 0, 512, 512};
static const s16 sTopBoxes[2][4] = {{0, -PIXEL(24), PIXEL(16), PIXEL(16)}, {0, PIXEL(24), PIXEL(16), PIXEL(16)}};

// 0x080b3fb4
static void createBit(Coords32* at, u8 kind, u8 dir, bool8 yflip) {
  struct Bit* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_CRAWLER_BIT);
  (p->s).coord = *at;
  (p->s).work[0] = kind;
  (p->s).work[1] = dir;
  p->yflip = yflip;
}

// 0x080b4014
static void Bit_Init(struct Bit* p) {
  struct Entity* s = &p->s;
  s8 sign = s->work[1] * 2 - 1;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  s->work[2] = 0;
  switch (s->work[0]) {
    case 0:
      SetMotion(s, ANIM(12));
      s->d.x = sign * 320;
      s->d.y = p->yflip ? 768 : -768;
      p->bounced = FALSE;
      break;
    case 1:
      SetMotion(s, ANIM(4));
      SET_YFLIP(p, p->yflip);
      s->d.x = 0;
      s->d.y = -0x180;
      break;
    case 2:
      SetMotion(s, ANIM(4));
      SET_YFLIP(p, p->yflip);
      s->d.x = sign * 128;
      s->d.y = 0x980;
      break;
    case 3:
      SetMotion(s, ANIM(16));
      SET_YFLIP(p, p->yflip);
      SET_XFLIP(p, RANDOM(RNG_0202f388) & 1);
      sign = (s->flags & X_FLIP) ? 1 : -1;
      if (s->work[1] == 0) {
        s->d.x = sign * ((s32)(RANDOM(RNG_0202f388) & 0x1FF) - 255);
        s->d.y = (RANDOM(RNG_0202f388) & 0x1FF) - 0x400;
      } else {
        s->d.x = sign * (255 - (s32)(RANDOM(RNG_0202f388) & 0x1FF));
        s->d.y = (RANDOM(RNG_0202f388) & 0x1FF) - 0x740;
      }
      break;
  }
  Bit_Update(p);
}

static void fall(struct Entity* s) {
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

// 0x080b47a8: moves dy, stopping on a ceiling or floor
static bool8 moveY(struct Entity* s, s32 dy, const s16* box) {
  s32 x = s->coord.x + box[0];
  s32 y = s->coord.y + box[1] + dy;
  if (dy < 0) {
    y -= box[3] / 2;
    if (FUN_080098a4(x, y) != 0) {
      s->coord.y = FUN_0800a134(x, y) + box[3] / 2 - box[1];
      return TRUE;
    }
  } else if (dy > 0) {
    y += box[3] / 2;
    if (FUN_080098a4(x, y) != 0) {
      s->coord.y = FUN_08009f6c(x, y) - box[3] / 2 - box[1];
      return TRUE;
    }
  } else {
    return FALSE;
  }
  s->coord.y += dy;
  return FALSE;
}

// 0x080b4838: moves dx, stopping on a wall
static bool8 moveX(struct Entity* s, s32 dx, const s16* box) {
  s32 x = s->coord.x + box[0] + dx;
  s32 y = s->coord.y + box[1];
  if (dx < 0) {
    x -= box[2] / 2;
    if (FUN_080098a4(x, y) != 0) {
      s->coord.x = FUN_0800a31c(x, y) + box[2] / 2 - box[0];
      return TRUE;
    }
  } else if (dx > 0) {
    x += box[2] / 2;
    if (FUN_080098a4(x, y) != 0) {
      s->coord.x = FUN_0800a22c(x, y) - box[2] / 2 - box[0];
      return TRUE;
    }
  } else {
    return FALSE;
  }
  s->coord.x += dx;
  return FALSE;
}

// 0x080b471c: falls, true once on the ground
static bool8 land(struct Entity* s, const s16* box) {
  s32 feet = box[1] + box[3] / 2;
  if (s->d.y == 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y + feet + PIXEL(1)) != 0) return TRUE;
    if (FUN_080098a4(s->coord.x, s->coord.y + feet + PIXEL(8)) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + box[1];
      return TRUE;
    }
  } else if (moveY(s, s->d.y, box)) {
    s->d.y = 0;
    return TRUE;
  }
  fall(s);
  return FALSE;
}

// 0x080b461c, 0x080b469c
static void bitBurst(struct Bit* p, const s16* box, u8 dir) {
  Coords32 at;
  at.x = (p->s).coord.x + box[0];
  at.y = (p->s).coord.y + box[1];
  createBit(&at, 3, dir, ((p->s).flags & Y_FLIP) != 0);
  at.x += PIXEL((s32)(RANDOM(RNG_0202f388) & 31) - 15);
  at.y += PIXEL((s32)(RANDOM(RNG_0202f388) & 31) - 15);
  CreateSmoke(1, &at);
}

static void vanish(struct Bit* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080b429c
static void Bit_Update(struct Bit* p) {
  struct Entity* s = &p->s;
  const s16* box = sTopBoxes[(s->flags & Y_FLIP) ? 1 : 0];
  UpdateEntityAnim(s);
  s->work[2]++;
  switch (s->work[0]) {
    case 0:  // 0x080b430c
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) {
        vanish(p);
        return;
      }
      s->coord.x += s->d.x;
      if (p->bounced) {
        s->coord.y += s->d.y;
        fall(s);
      } else {
        s8 down = s->d.y >= 0 ? 1 : -1;
        if (land(s, sShellBox)) {
          s32 v = (4 - s->work[2] / 4) * 256;
          if (v < 0) v = 0;
          s->d.x /= 2;
          s->d.y = -(down * v);
          p->bounced = TRUE;
        }
      }
      break;
    case 1:  // 0x080b43c4
      if (s->work[2] == 255 || land(s, box)) {
        bitBurst(p, box, 0);
        vanish(p);
      }
      break;
    case 2:  // 0x080b4460
      if (s->work[2] == 255) {
        bitBurst(p, box, 0);
        vanish(p);
      } else if (s->mode[1] == 0) {
        if (moveX(s, s->d.x, box) || land(s, box)) {
          s->mode[1]++;
          p->landed = 0;
        }
      } else if (++p->landed == 1) {
        s->coord.y += PIXEL(1);
      } else if (p->landed == 3) {
        bitBurst(p, box, 1);
        vanish(p);
      }
      break;
    case 3:  // 0x080b4570
      if (s->work[2] == 255) {
        CreateSmoke(3, &s->coord);
        vanish(p);
        return;
      }
      if (s->work[2] & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        CreateSmoke(3, &s->coord);
        vanish(p);
        return;
      }
      fall(s);
      break;
  }
}

// --------------------------------------------
// clang-format off
// 0x0833f0c4: by orient, a damaging box and a hurtbox
static const struct Collision sCollisions[6][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, -0x1600, 0x1000, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1600, 0x1000, 0x1800}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, -0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, 0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, 0x1600, 0x1000, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1600, 0x1000, 0x1800}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, 0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0x00000001, {0, -0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
    },
};

// 0x0833f1e4: hurtboxes only
static const struct Collision sElemented[6][2] = {
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1600, 0x1000, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1600, 0x1000, 0x1800}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1600, 0x1000, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1600, 0x1000, 0x1800}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, 0x1000, 0x1000, 0xc00}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 1, 0, 0, 0, 0x00000000, {0, -0x1000, 0x1000, 0xc00}},
    },
};

// 0x0833f094
static const Coords32 sElementCoord[6] = {
    {0, -PIXEL(24)}, {0, -PIXEL(12)}, {0, PIXEL(12)}, {0, PIXEL(24)}, {0, PIXEL(12)}, {0, -PIXEL(12)},
};

// 0x0833f304
static const struct SlashedEnemy sGibs[4] = {
    {ANIM(13), {0xff, 0x11}, {0, 0}, {128, -1280}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(13), {0xff, 0x11}, {0, 0}, {-128, -1280}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(14), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(15), {0xff, 0x11}, {0, 0}, {128, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
