#include "ap.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
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
  Zero 2's robot spider, enemy 65.
  work0:
    0: ceiling
    1: wall on its right
    2: floor
    3: wall on its left
    4: thread, a second copy whose hitbox runs from the ceiling to the spider
    5: starts on ceiling, bobs on its thread above Zero
*/

struct Spider {
  OBJECT_HDR;
  s32 walked;    // 0xB4, distance since last pause (thread: hitbox x)
  s32 paidOut;   // 0xB8, thread let out (thread: hitbox y)
  s32 ceilingY;  // 0xBC, thread's
  s32 homeY;     // 0xC0, starting y, once dead whether it drops an item
};
static_assert(sizeof(struct Spider) == sizeof(struct Enemy));

enum {
  ON_CEILING,
  ON_RIGHT_WALL,
  ON_FLOOR,
  ON_LEFT_WALL,
  THREAD,
  BOBBER,  // starts as ON_CEILING with work1 5
};

// work0 ON_CEILING
enum {
  CEILING_WALK,
  CEILING_PAUSE,
  CEILING_HANG,
  CEILING_DESCEND,
  CEILING_BOTTOM,
  CEILING_SHOOT,
  CEILING_BOB,
  CEILING_BOB_PAUSE,
  CEILING_CORNER_LEFT,
  CEILING_CORNER_RIGHT,
  CEILING_AIM,
  CEILING_WEB,
  CEILING_WEB_END,
};

// work0 ON_RIGHT_WALL, ON_LEFT_WALL
enum {
  WALL_WALK,
  WALL_PAUSE,
  WALL_CORNER,
};

// work0 ON_FLOOR
enum {
  FLOOR_WALK,
  FLOOR_FALL,
  FLOOR_CLIMB_LEFT,
  FLOOR_CLIMB_RIGHT,
};

// Deaths, by mode[1]
enum {
  SPIDER_FALL,
  SPIDER_BURST,
  SPIDER_GONE,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_SPIDER, (n))
#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define UPSIDE_DOWN(p) ((((struct Entity*)(p))->flags & Y_FLIP) != 0)

static const struct Collision sBody[2];
static const struct Collision sHarmless;
static const struct Collision sThread[8];
static const struct Collision sWeb[2];
static const Coords32 sElementCoord = {0, PIXEL(16)};
static const Coords32 sCentre[4] = {{0, PIXEL(14)}, {-PIXEL(14), 0}, {0, 0}, {PIXEL(14), 0}};
static const u8 sSlopeAngles[16] = {0, 0, 233, 233, 246, 246, 246, 246, 23, 23, 10, 10, 10, 10, 0, 0};

static void Spider_Init(struct Spider* p);
static void Spider_Update(struct Spider* p);
static void Spider_Die(struct Spider* p);
static void createWeb(struct Spider* spider, Coords32* c, s32 speed, u8 angle);
static void createPieces(struct Spider* spider);

// clang-format off
const EnemyRoutine gApZ2SpiderRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Spider_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Spider_Update,
    [ENTITY_DIE] =       (EnemyFunc)Spider_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Spider* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void face(struct Spider* p, bool8 right) { SET_XFLIP(p, right); }
static s32 abs32(s32 v) { return v < 0 ? -v : v; }
static bool8 zeroIsLeft(struct Spider* p) { return (pZero2->s).coord.x < (p->s).coord.x; }

// Zero is 32 px or more below, on the side it faces
static bool8 zeroBelowInFront(struct Spider* p) {
  struct Entity* s = &p->s;
  if ((pZero2->s).coord.y - PIXEL(32) <= s->coord.y) return FALSE;
  return FACING_RIGHT(p) ? !zeroIsLeft(p) : zeroIsLeft(p);
}

// Full block or wall-like shape, not the 0x800f soft platform
static bool8 blocks(metatile_attr_t a) {
  u8 shape = a & 15;
  return (shape == 1 || shape > 13) && a != 0x800F;
}

static void disappear(struct Entity* s) {
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(s);
  SET_ENEMY_ROUTINE(s, ENTITY_DISAPPEAR);
}

static void cutThread(struct Spider* p) {
  if ((p->s).unk_2c != NULL) {
    disappear((p->s).unk_2c);
    (p->s).unk_2c = NULL;
  }
}

static void startArc(struct Spider* p, u8 a, s32 radius) {
  (p->s).work[2] = a;
  (p->s).d.x = COS(a) * radius;
  (p->s).d.y = -SIN(a) * radius;
}

// Round a corner: d holds last point on the 10 px circle, work[2] the angle
static void stepArc(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 x = COS(s->work[2]) * 10;
  s32 y = -SIN(s->work[2]) * 10;
  s->coord.x += x - s->d.x;
  s->coord.y += y - s->d.y;
  s->d.x = x;
  s->d.y = y;
}

// Dropped from ceiling or thread, walks the floor away from Zero
static void becomeWalker(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right = zeroIsLeft(p);
  s->work[0] = ON_FLOOR;
  setMode(p, FLOOR_FALL);
  InitRotatableMotion(s);
  SetMotion(s, ANIM(1));
  UpdateEntityAnim(s);
  s->d.x = right ? 0x240 : -0x240;
  face(p, right);
  SET_YFLIP(p, TRUE);
}

// --------------------------------------------

static void Thread_Update(struct Spider* p);
static void initFloor(struct Spider* p);

// 0x080895b4
static void Spider_Init(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitRotatableMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(1));
  INIT_BODY(p, sBody, 2, NULL);
  if (s->work[0] == ON_FLOOR) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  s->work[1] = 0;
  switch (s->work[0]) {
    case BOBBER:
    case ON_CEILING:
      s->work[2] = 0;
      p->walked = 0;
      right = RANDOM(RNG_0202f388) & 1;
      s->d.x = right ? 0x180 : -0x180;
      face(p, right);
      s->coord.y = FUN_0800a134(s->coord.x, s->coord.y);
      if (s->work[0] == BOBBER) {
        s->work[0] = ON_CEILING;
        s->work[1] = 5;
      }
      break;
    case ON_RIGHT_WALL:
      s->d.y = -0x180;
      face(p, TRUE);
      break;
    case ON_FLOOR: initFloor(p); break;
    case ON_LEFT_WALL:
      s->d.y = -0x180;
      face(p, FALSE);
      break;
    case THREAD:
      InitNonAffineMotion(s);
      p->ceilingY = FUN_0800a134(s->coord.x, s->coord.y);
      s->coord.y = p->ceilingY + PIXEL(16);
      p->walked = s->coord.x;
      s->work[2] = 0;
      s->flags &= ~DISPLAY;
      SetMotion(s, ANIM(13));
      INIT_BODY(p, &sThread[0], 1, NULL);
      (p->body).coord = (Coords32*)&p->walked;
      s->unk_2c = NULL;
      break;
  }
  s->mode[1] = 0;
  if (s->work[0] != THREAD) {
    s->unk_28 = NULL;
    p->homeY = s->coord.y;
  }
  Spider_Update(p);
}

static void ceilingCheck(struct Spider* p);
static void ceilingStep(struct Spider* p);
static void wallCheck(struct Spider* p);
static void rightWallStep(struct Spider* p);
static void leftWallStep(struct Spider* p);
static void floorCheck(struct Spider* p);
static void floorStep(struct Spider* p);
static void prepareDeath(struct Spider* p);
static void getOutOfTerrain(struct Spider* p);

// 0x0808966c
static void Spider_Update(struct Spider* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (s->mode[3] == 0 && IsFrozen(p)) s->mode[3] = 1;

  if (s->work[0] != THREAD) {
    if (status & BODY_STATUS_DEAD) {
      p->homeY = 1;
      prepareDeath(p);
      Spider_Die(p);
      return;
    }
  } else {
    struct Spider* spider = (struct Spider*)s->unk_28;
    if ((spider->s).mode[0] > ENTITY_UPDATE) {
      disappear(s);
      return;
    }
    // Thread cut, spider drops to floor
    if (status & BODY_STATUS_DEAD) {
      (spider->s).coord.y += PIXEL(20);
      SET_YFLIP(spider, TRUE);
      (spider->s).d.y = 0;
      cutThread(spider);
      (spider->s).work[0] = ON_FLOOR;
      (spider->s).mode[1] = FLOOR_FALL;
      InitRotatableMotion(&spider->s);
      SetMotion(&spider->s, ANIM(1));
      UpdateEntityAnim(&spider->s);
      (spider->s).d.x = zeroIsLeft(spider) ? 0x240 : -0x240;
      face(spider, zeroIsLeft(spider));
    }
  }

  // Time stopped, holds still, element effect gone
  if (s->mode[3] != 0) {
    if (s->mode[3] == 1) {
      UpdateEntityAnim(s);
      s->mode[3] = 2;
      s->unk_28 = NULL;
      SetDDP(&p->body, sBody);
    }
    if (!IsFrozen(p)) s->mode[3] = 0;
    return;
  }

  if (s->work[0] == THREAD) {
    UpdateEntityAnim(s);
    Thread_Update(p);
    return;
  }

  // Burning or frozen, drops to ground, walks once effect ends
  if (s->unk_28 != NULL) {
    s32 r;
    if (IsDead(s->unk_28)) {
      SetDDP(&p->body, sBody);
      s->unk_28 = NULL;
      s->work[0] = ON_FLOOR;
      s->mode[1] = 0;
      initFloor(p);
      return;
    }
    if (PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y) < 0 || PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y) < 0) return;
    s->d.y += 0x40;
    if (s->d.y > 0x6FF) s->d.y = 0x700;
    s->coord.y += s->d.y;
    if ((r = PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y)) < 0) s->coord.y += r;
    if ((r = PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y)) < 0) s->coord.y += r;
    return;
  }

  // Check that moves it on runs the new state's step at once, as in Zero 2
  UpdateEntityAnim(s);
  switch (s->work[0]) {
    case ON_CEILING: ceilingCheck(p); break;
    case ON_RIGHT_WALL:
    case ON_LEFT_WALL: wallCheck(p); break;
    case ON_FLOOR: floorCheck(p); break;
  }
  switch (s->work[0]) {
    case ON_CEILING: ceilingStep(p); break;
    case ON_RIGHT_WALL: rightWallStep(p); break;
    case ON_FLOOR: floorStep(p); break;
    case ON_LEFT_WALL: leftWallStep(p); break;
  }

  if (status & BODY_STATUS_WHITE) {
    s->unk_28 = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_28 != NULL) {
      SetDDP(&p->body, &sHarmless);
      s->d.y = 0;
      cutThread(p);
      s->angle = 0;
      SetMotion(s, ANIM(1));
      UpdateEntityAnim(s);
      SET_YFLIP(p, TRUE);
      getOutOfTerrain(p);
    }
  }
}

// --------------------------------------------
// Ceiling, work0 0

// 0x08089ede: wall ahead takes it round the inner corner, nothing overhead drops it
static void ceilingWalk(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right = FACING_RIGHT(p);
  s32 front = right ? PIXEL(14) : -PIXEL(14);
  s32 r;
  metatile_attr_t a;

  p->walked += abs32(s->d.x);
  s->coord.x += s->d.x;
  if (blocks(GetMetatileAttr(s->coord.x + front, s->coord.y + PIXEL(4))) &&
      blocks(GetMetatileAttr(s->coord.x + front, s->coord.y + PIXEL(16)))) {
    s->mode[1] = right ? CEILING_CORNER_RIGHT : CEILING_CORNER_LEFT;
    startArc(p, right ? 0x80 : 0xFF, 13);
  }
  if (right) {
    if ((r = PushoutToLeft1(s->coord.x + front, s->coord.y + PIXEL(4))) < 0) s->coord.x += r;
  } else {
    if ((r = PushoutToRight1(s->coord.x + front, s->coord.y + PIXEL(4))) > 0) s->coord.x += r;
  }

  a = GetMetatileAttr(s->coord.x + front, s->coord.y - PIXEL(4)) & 15;
  if (!(a == 1 || a > 13)) {
    face(p, !right);
    s->d.x = -s->d.x;
  }

  a = GetMetatileAttr(s->coord.x, s->coord.y - PIXEL(4)) & 15;
  if (a == 1) {
    s->coord.y = FUN_0800a134(s->coord.x, s->coord.y);
  } else if (a != 14) {
    // Stops here. Zero 2 carries on in ceiling modes and indexes past floor's state table.
    becomeWalker(p);
    s->coord.y += PIXEL(14);
    return;
  }

  if (s->work[1] == 5) {
    if (abs32(s->coord.x - (pZero2->s).coord.x) <= PIXEL(64) - 1) {
      s->d.y = 0x280;
      s->mode[1] = CEILING_HANG;
      p->walked = 0;
      p->paidOut = 0;
      SetMotion(s, ANIM(5));
    }
  } else if (abs32(s->coord.x - (pZero2->s).coord.x) <= PIXEL(80) - 1 && zeroBelowInFront(p)) {
    s->work[2] = 0;
    s->mode[1] = CEILING_AIM;
    SetMotion(s, ANIM(2));
  }
}

static void lowerThread(struct Spider* p) {
  struct Entity* s = &p->s;
  struct Entity* thread = AllocEntityFirst(gEnemyHeaderPtr);
  if (thread != NULL) {
    INIT_ENEMY_ROUTINE(thread, ENEMY_Z2_SPIDER);
    thread->coord.x = s->coord.x;
    thread->coord.y = s->coord.y + PIXEL(16);
    thread->work[0] = THREAD;
    thread->unk_28 = s;
  }
  s->unk_2c = thread;
}

// 0x0808a378: lets go near the ground (three frames running) or at 128 px of thread
static void ceilingDescendCheck(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 back, front;
  if (p->walked > PIXEL(48)) {
    s->work[2] = 0;
    s->mode[1] = CEILING_BOTTOM;
  }
  back = PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y + PIXEL(26));
  front = PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y + PIXEL(26));
  if (back < 0 || front < 0) {
    if (++s->work[3] == 3) {
      s->coord.y += back < front ? back : front;
      s->coord.y += PIXEL(26);
      cutThread(p);
      becomeWalker(p);
      s->work[2] = 0;
    } else {
      SetMotion(s, ANIM(7));
    }
  }
  if ((u32)p->paidOut > PIXEL(128) - 1) {
    s->coord.y += PIXEL(14);
    SET_YFLIP(p, TRUE);
    s->d.y = 0;
    cutThread(p);
    becomeWalker(p);
  }
}

// 0x0808a60c: down toward Zero and back up, shooting when he is below
static void ceilingBob(struct Spider* p) {
  struct Entity* s = &p->s;
  face(p, (pZero2->s).coord.x > s->coord.x);
  p->walked += s->d.y;
  p->paidOut += s->d.y;
  s->coord.y += s->d.y;
  s->d.x = 0;
  if (s->d.y > 0 || (u32)p->paidOut > PIXEL(128) - 1) {
    if (FUN_080098a4(s->coord.x - PIXEL(8), s->coord.y + PIXEL(48)) == 0 &&
        FUN_080098a4(s->coord.x + PIXEL(8), s->coord.y + PIXEL(48)) == 0 && abs32(p->homeY - s->coord.y) <= PIXEL(96)) {
      return;
    }
    s->work[2] = 0;
    s->mode[1] = CEILING_BOB_PAUSE;
    s->d.y = -s->d.y;
    return;
  }
  if (--s->work[2] == 0) {
    if (zeroBelowInFront(p)) {
      s->mode[1] = CEILING_SHOOT;
      SetMotion(s, ANIM(6));
    } else {
      s->mode[1] = CEILING_BOB_PAUSE;
    }
  }
  if (GetMetatileAttr(s->coord.x, s->coord.y - PIXEL(32)) != 0) {
    s->d.y = -s->d.y;
    s->work[2] = 0;
    if (zeroBelowInFront(p)) {
      s->mode[1] = CEILING_SHOOT;
      SetMotion(s, ANIM(6));
    } else {
      s->mode[1] = CEILING_BOB_PAUSE;
    }
  }
}

static void shootLemon(struct Spider* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  u8 a;
  c.x = s->coord.x + (FACING_RIGHT(p) ? PIXEL(6) : -PIXEL(6));
  c.y = s->coord.y + PIXEL(19);
  a = (ArcTan2(((pZero2->s).coord.x - c.x) >> 4, ((pZero2->s).coord.y - (s->coord.y + PIXEL(27))) >> 4) >> 8) + 128;
  CreateLemon(&c, 0x180, a);
  PlaySound(SE_ENEMY_SHOT);
}

static void shootWeb(struct Spider* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  u8 a;
  c.x = s->coord.x + (FACING_RIGHT(p) ? -PIXEL(4) : PIXEL(4));
  c.y = s->coord.y + PIXEL(19);
  a = (ArcTan2(((pZero2->s).coord.x - c.x) >> 8, ((pZero2->s).coord.y - (s->coord.y + PIXEL(27))) >> 8) >> 8) + 128;
  createWeb(p, &c, 0x280, a);
}

static void ceilingCheck(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right;
  switch (s->mode[1]) {
    case CEILING_WALK:  // 0x08089eb0
      if (p->walked > PIXEL(64) - 1) {
        s->work[2] = 0;
        s->mode[1] = CEILING_PAUSE;
        SetMotion(s, ANIM(0));
      }
      break;
    case CEILING_PAUSE:  // 0x0808a1f8: walks on in a random direction, or goes down thread
      if (s->work[2] > 15) {
        if ((RANDOM(RNG_0202f388) & 8) || s->work[1] == 5) {
          right = RANDOM(RNG_0202f388) & 1;
          s->d.x = right ? 0x180 : -0x180;
          face(p, right);
          s->mode[1] = CEILING_WALK;
          p->walked = 0;
          SetMotion(s, ANIM(1));
        } else {
          s->d.y = 0xCC;
          s->mode[1] = CEILING_HANG;
          p->walked = 0;
          p->paidOut = 0;
          SetMotion(s, ANIM(5));
        }
      }
      break;
    case CEILING_HANG:  // 0x0808a2dc
      if (s->motion.state == ANIM_END) {
        s->work[3] = 0;
        s->mode[1] = s->work[1] == 5 ? CEILING_BOB : CEILING_DESCEND;
        InitNonAffineMotion(s);
        SetMotion(s, ANIM(4));
        lowerThread(p);
      }
      break;
    case CEILING_DESCEND: ceilingDescendCheck(p); break;
    case CEILING_BOTTOM:  // 0x0808a7e4
      if (s->work[2] > 15) {
        p->walked = 0;
        if ((RANDOM(RNG_0202f388) & 1) && zeroBelowInFront(p)) {
          s->work[2] = 0;
          s->mode[1] = CEILING_SHOOT;
          SetMotion(s, ANIM(6));
        } else {
          s->work[3] = 0;
          s->mode[1] = CEILING_DESCEND;
          SetMotion(s, ANIM(4));
        }
      }
      break;
    case CEILING_SHOOT:  // 0x0808a9e4
      if (s->work[2] > 31) {
        s->work[2] = 0;
        s->mode[1] = s->work[1] == 5 ? CEILING_BOB_PAUSE : CEILING_BOTTOM;
        SetMotion(s, ANIM(4));
      }
      break;
    case CEILING_CORNER_LEFT:  // 0x0808a898: onto wall on its left
      if (s->work[2] <= 0xC0) {
        s->work[0] = ON_LEFT_WALL;
        s->mode[1] = WALL_WALK;
        s->d.y = 0x180;
        p->walked = 0;
        s->work[2] = 0;
        face(p, TRUE);
      }
      break;
    case CEILING_CORNER_RIGHT:  // 0x0808a940
      if (s->work[2] > 0xC0) {
        s->work[0] = ON_RIGHT_WALL;
        s->mode[1] = WALL_WALK;
        s->d.y = 0x180;
        p->walked = 0;
        s->work[2] = 0;
        face(p, FALSE);
      }
      break;
    case CEILING_WEB:  // 0x0808aaac
      if (s->work[2] > 63) {
        s->work[2] = 0;
        s->mode[1] = CEILING_WEB_END;
        SetMotion(s, ANIM(9));
      }
      break;
  }
}

static void ceilingStep(struct Spider* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case CEILING_WALK: ceilingWalk(p); break;
    case CEILING_PAUSE:
    case CEILING_BOTTOM:
      s->work[2]++;
      s->d.x = 0;
      break;
    case CEILING_BOB_PAUSE:  // 0x0808a7c0
      s->d.x = 0;
      if (++s->work[2] > 19) {
        s->mode[1] = CEILING_BOB;
        s->work[2] = 8;
      }
      break;
    case CEILING_HANG: s->d.x = 0; break;
    case CEILING_DESCEND:  // 0x0808a5d0
      p->walked += abs32(s->d.y);
      p->paidOut += abs32(s->d.y);
      s->coord.y += s->d.y;
      s->d.x = 0;
      break;
    case CEILING_SHOOT:  // 0x0808aa10
      if (s->work[2] == 16) shootLemon(p);
      s->work[2]++;
      break;
    case CEILING_BOB: ceilingBob(p); break;
    case CEILING_CORNER_LEFT:  // 0x0808a8e0
      s->work[2] -= 2;
      s->angle = s->work[2];
      stepArc(p);
      break;
    case CEILING_CORNER_RIGHT:  // 0x0808a980
      s->work[2] += 2;
      s->angle = 0x80 - s->work[2];
      stepArc(p);
      break;
    case CEILING_AIM:  // 0x0808aa90
      s->d.x = 0;
      if (s->motion.state == ANIM_END) {
        s->work[2] = 0;
        s->mode[1] = CEILING_WEB;
      }
      break;
    case CEILING_WEB:  // 0x0808aad0
      if (s->work[2] == 32) shootWeb(p);
      s->work[2]++;
      break;
    case CEILING_WEB_END:  // 0x0808ab54
      if (s->motion.state == ANIM_END) {
        s->work[2] = 0;
        s->mode[1] = CEILING_PAUSE;
      }
      break;
  }
}

// --------------------------------------------
// Wall, work0 1 and 3. Mirrors except for Zero 2's probe offsets, so each is written out.

static void turnOnWall(struct Spider* p) {
  face(p, !FACING_RIGHT(p));
  (p->s).d.y = -(p->s).d.y;
}

static void wallCheck(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right;
  switch (s->mode[1]) {
    case WALL_WALK:  // 0x0808ab9c, 0x0808b710
      if (p->walked > PIXEL(64) - 1) {
        s->work[2] = 0;
        s->mode[1] = WALL_PAUSE;
        SetMotion(s, ANIM(0));
      }
      break;
    case WALL_PAUSE:  // 0x0808adb0, 0x0808b924
      if (s->work[2] > 16) {
        right = RANDOM(RNG_0202f388) & 1;
        s->mode[1] = WALL_WALK;
        s->d.y = right == (s->work[0] == ON_LEFT_WALL) ? 0x180 : -0x180;
        face(p, right);
        p->walked = 0;
        SetMotion(s, ANIM(1));
      }
      break;
    case WALL_CORNER:  // round outer corner onto ceiling
      if (s->work[0] == ON_RIGHT_WALL ? (s8)s->work[2] >= 0 : s->work[2] <= 63) {  // 0x0808ae50, 0x0808b9c8
        right = s->work[0] == ON_LEFT_WALL;
        s->work[0] = ON_CEILING;
        s->mode[1] = CEILING_WALK;
        s->d.x = right ? 0x180 : -0x180;
        p->walked = 0;
        s->work[2] = 0;
        face(p, right);
        SET_YFLIP(p, FALSE);
        s->angle = 0;
      }
      break;
  }
}

// 0x0808abca
static void rightWallStep(struct Spider* p) {
  struct Entity* s = &p->s;
  metatile_attr_t a;
  switch (s->mode[1]) {
    case WALL_WALK:
      p->walked += abs32(s->d.y);
      s->coord.x = FUN_0800a22c(s->coord.x, s->coord.y);
      s->coord.y += s->d.y;
      s->d.x = 0;
      if (FACING_RIGHT(p)) {
        a = GetMetatileAttr(s->coord.x - PIXEL(4), s->coord.y - PIXEL(14));
        if (a == 0x8001) {
          turnOnWall(p);
        } else if ((a & 15) == 1) {
          s->mode[1] = WALL_CORNER;
          startArc(p, 0xC0, 10);
        } else if (FUN_080098a4(s->coord.x - PIXEL(4), s->coord.y - PIXEL(14)) != 0) {
          turnOnWall(p);
        }
      }
      if (GetMetatileAttr(s->coord.x + PIXEL(6), s->coord.y + (FACING_RIGHT(p) ? -PIXEL(14) : PIXEL(14))) != 1) {
        turnOnWall(p);
      } else if (GetMetatileAttr(s->coord.x - PIXEL(2), s->coord.y + PIXEL(14)) != 0 && !FACING_RIGHT(p)) {
        turnOnWall(p);
      }
      SET_YFLIP(p, TRUE);
      s->angle = FACING_RIGHT(p) ? 0xC0 : 0x40;
      break;
    case WALL_PAUSE:  // 0x0808ae44
      s->work[2]++;
      s->d.x = 0;
      break;
    case WALL_CORNER:  // 0x0808aeb8
      s->work[2] -= 2;
      SET_YFLIP(p, TRUE);
      s->angle = s->work[2];
      stepArc(p);
      break;
  }
}

// 0x0808b73c
static void leftWallStep(struct Spider* p) {
  struct Entity* s = &p->s;
  metatile_attr_t a;
  switch (s->mode[1]) {
    case WALL_WALK:
      s->d.x = 0;
      s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y);
      p->walked += abs32(s->d.y);
      s->coord.y += s->d.y;
      if (!FACING_RIGHT(p)) {
        a = GetMetatileAttr(s->coord.x + PIXEL(4), s->coord.y - PIXEL(14));
        if (a == 0x8001) {
          turnOnWall(p);
        } else if ((a & 15) == 1) {
          s->mode[1] = WALL_CORNER;
          startArc(p, 0xC0, 10);
        } else if (FUN_080098a4(s->coord.x + PIXEL(4), s->coord.y - PIXEL(14)) != 0) {
          turnOnWall(p);
        }
      }
      if (GetMetatileAttr(s->coord.x - PIXEL(4), s->coord.y + (FACING_RIGHT(p) ? PIXEL(14) : -PIXEL(14))) != 1) {
        turnOnWall(p);
      } else if (GetMetatileAttr(s->coord.x + PIXEL(2), s->coord.y + PIXEL(14)) != 0 && FACING_RIGHT(p)) {
        turnOnWall(p);
      }
      SET_YFLIP(p, TRUE);
      s->angle = FACING_RIGHT(p) ? 0x40 : 0xC0;
      break;
    case WALL_PAUSE:  // 0x0808b9bc
      s->work[2]++;
      s->d.x = 0;
      break;
    case WALL_CORNER:  // 0x0808ba38
      s->work[2] += 2;
      SET_YFLIP(p, TRUE);
      s->angle = -s->work[2];
      stepArc(p);
      break;
  }
}

// --------------------------------------------
// Floor, work0 2, art upside down

// 0x0808af48
static void initFloor(struct Spider* p) {
  struct Entity* s = &p->s;
  bool8 right = (pZero2->s).coord.x > s->coord.x;
  s->mode[1] = 0;
  s->mode[2] = 0;
  s->d.x = right ? 0x240 : -0x240;
  s->work[1] = 2;
  face(p, right);
  SET_YFLIP(p, TRUE);
}

static bool8 crushed(struct Spider* p);

// 0x0808aff0: walks away from Zero, or after him if it came in as a floor walker. Climbs a
// wall ahead, turns back at a low one.
static void floorWalk(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 dx, front, r, back;
  u8 shape;
  s8 turn;
  bool8 right;
  metatile_attr_t a;

  if (s->mode[2] == 0) {
    dx = (pZero2->s).coord.x - s->coord.x;
    right = (dx < 0) ^ (s->work[1] == 2);
    if (s->work[1] != 2) {
      s->d.x = right ? 0x240 : -0x240;
      face(p, right);
    } else if (abs32(dx) > PIXEL(32)) {
      s->d.x = right ? 0x180 : -0x180;
      face(p, right);
    }
    s->mode[2]++;
  }
  if (s->work[1] == 2) {
    dx = (pZero2->s).coord.x - s->coord.x;
    if (abs32(dx) > PIXEL(32)) {
      s->d.x = dx > 0 ? 0x180 : -0x180;
      face(p, dx > 0);
    }
  }
  SET_YFLIP(p, TRUE);

  right = FACING_RIGHT(p);
  front = right ? PIXEL(4) : -PIXEL(4);
  shape = GetMetatileAttr(s->coord.x + front, s->coord.y + PIXEL(4)) & 15;
  if (shape == 0 && FUN_080098a4(s->coord.x + front, s->coord.y + PIXEL(4)) != 0) shape = 1;
  if (shape == 1 || shape > 13) {
    // Shape is enough, Zero 2 indexes angles with the whole attribute
    shape = GetMetatileAttr(s->coord.x + front, s->coord.y - PIXEL(4)) & 15;
    if (shape == 0) shape = 1;
  }
  turn = sSlopeAngles[shape] - s->work[2];
  s->work[2] += turn >> 1;
  s->angle = right ? s->work[2] : -s->work[2];

  s->coord.x += s->d.x;
  if (shape > 1) {
    s32 floor = FUN_08009f6c(s->coord.x, s->coord.y);
    if (floor - s->coord.y > 0xA3F) {
      s->d.y = 0;
      s->mode[1] = FLOOR_FALL;
      return;
    }
    s->coord.y = floor;
  }

  front = right ? PIXEL(10) : -PIXEL(10);
  a = GetMetatileAttr(s->coord.x + front, s->coord.y - PIXEL(10));
  r = 0;
  if (blocks(a)) {
    if (blocks(GetMetatileAttr(s->coord.x + front, s->coord.y - PIXEL(32)))) {
      s->mode[1] = right ? FLOOR_CLIMB_RIGHT : FLOOR_CLIMB_LEFT;
      startArc(p, right ? 0x80 : 0, 10);
    } else {
      s->work[1] = 0;
      s->d.x = -s->d.x;
      face(p, s->d.x > 0);
    }
    r = right ? PushoutToLeft1(s->coord.x + front, s->coord.y - PIXEL(1)) : PushoutToRight1(s->coord.x + front, s->coord.y - PIXEL(1));
  } else if (FUN_080098a4(s->coord.x + front, s->coord.y - PIXEL(10)) != 0) {
    s->work[1] = 0;
    s->d.x = -s->d.x;
    face(p, s->d.x > 0);
    r = right ? PushoutToLeft1(s->coord.x + front, s->coord.y - PIXEL(10)) : PushoutToRight1(s->coord.x + front, s->coord.y - PIXEL(10));
  }
  if ((right && r < 0) || (!right && r > 0)) s->coord.x += r;

  if (shape > 1) return;
  back = PushoutToUp1(s->coord.x - PIXEL(10), s->coord.y);
  r = PushoutToUp1(s->coord.x + PIXEL(10), s->coord.y);
  if (back < 0 && r < 0) {
    s->coord.y += back < r ? back : r;
    return;
  }
  if (back < 0 || r < 0) {
    if ((r = PushoutToUp1(s->coord.x, s->coord.y)) < 0) s->coord.y += r;
  }
  if (PushoutToUp1(s->coord.x - PIXEL(10), s->coord.y + PIXEL(1)) >= 0 && PushoutToUp1(s->coord.x + PIXEL(10), s->coord.y + PIXEL(1)) >= 0) {
    s->d.y = 0;
    s->mode[1] = FLOOR_FALL;
  }
}

// 0x0808b4a8
static void floorFall(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 r, back;
  s->coord.x += s->d.x >> 1;
  if (FACING_RIGHT(p)) {
    if ((r = PushoutToLeft1(s->coord.x + PIXEL(8), s->coord.y)) < 0) {
      s->work[2] = 0;
      s->coord.x += r;
    }
  } else if ((r = PushoutToRight1(s->coord.x - PIXEL(8), s->coord.y)) > 0) {
    s->work[2] = 0;
    s->coord.x += r;
  }
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x6FF) s->d.y = 0x700;
  back = PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y + 0x40);
  r = PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y + 0x40);
  if (back < 0 || r < 0) {
    s->coord.y += back < r ? back : r;
    setMode(p, FLOOR_WALK);
  }
  SET_YFLIP(p, TRUE);
  if (crushed(p)) {
    p->homeY = 0;
    prepareDeath(p);
    Spider_Die(p);
  }
}

static void floorCheck(struct Spider* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == FLOOR_CLIMB_LEFT && s->work[2] > 63) {  // 0x0808b59c
    s->work[0] = ON_LEFT_WALL;
    s->mode[1] = WALL_WALK;
    s->d.y = -0x180;
    p->walked = 0;
    s->work[2] = 0;
    face(p, FALSE);
  } else if (s->mode[1] == FLOOR_CLIMB_RIGHT && s->work[2] <= 63) {  // 0x0808b640
    s->work[0] = ON_RIGHT_WALL;
    s->mode[1] = WALL_WALK;
    s->d.y = -0x180;
    p->walked = 0;
    s->work[2] = 0;
    face(p, TRUE);
  }
}

static void floorStep(struct Spider* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case FLOOR_WALK: floorWalk(p); break;
    case FLOOR_FALL: floorFall(p); break;
    case FLOOR_CLIMB_LEFT:  // 0x0808b5e0
      s->work[2] += 2;
      s->angle = -s->work[2];
      stepArc(p);
      break;
    case FLOOR_CLIMB_RIGHT:  // 0x0808b688
      s->work[2] -= 2;
      s->angle = s->work[2] + 127;
      stepArc(p);
      break;
  }
}

// --------------------------------------------

// 0x08089d74: glint slides down it
static void Thread_Update(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 spiderY = (s->unk_28)->coord.y;
  s32 length, n;
  s->coord.y += PIXEL(4);
  if (s->coord.y > spiderY) s->coord.y = p->ceilingY + PIXEL(16);
  length = spiderY - p->ceilingY;
  p->paidOut = p->ceilingY + length / 2;
  n = (length >> 12) - 1;
  if (n < 0) n = 0;
  if (n > 7) n = 7;
  SetDDP(&p->body, &sThread[n]);
  if (s->work[2] == 0) {
    s->work[2] = RANDOM(RNG_0202f388) % 24 + 16;
    s->flags |= DISPLAY;
    SetMotion(s, ANIM(13));
  }
  s->work[2]--;
  if (s->motion.state == ANIM_END) s->flags &= ~DISPLAY;
}

// 0x08089400: ground pressing from above and below at once
static bool8 crushed(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 head = s->coord.y + (UPSIDE_DOWN(p) ? -PIXEL(8) : PIXEL(8));
  s32 i;
  bool8 above = FALSE, below = FALSE;
  for (i = -1; i <= 1; i++) {
    if (PushoutToDown1(s->coord.x + i * PIXEL(8), head) > 0) above = TRUE;
    if (PushoutToUp1(s->coord.x + i * PIXEL(8), s->coord.y) < 0) below = TRUE;
  }
  return above && below;
}

// 0x080893b0: pushes body corners inside terrain back out
static void getOutOfTerrain(struct Spider* p) {
  static const Coords32 corners[4] = {{-PIXEL(9), 0}, {-PIXEL(9), -PIXEL(17)}, {PIXEL(9), -PIXEL(17)}, {PIXEL(9), 0}};
  struct Entity* s = &p->s;
  u8 mask = 0;
  s32 i, x, y;
  for (i = 0; i < 4; i++) {
    if (FUN_080098a4(s->coord.x + corners[i].x, s->coord.y + corners[i].y) != 0) mask |= 1 << i;
  }
#define CX(i) (s->coord.x + corners[i].x)
#define CY(i) (s->coord.y + corners[i].y)
  switch (mask) {
    case 1:
    case 2:
    case 4:
    case 8:
      i = mask == 1 ? 0 : mask == 2 ? 1 : mask == 4 ? 2 : 3;
      x = (i < 2) ? PushoutToRight1(CX(i), CY(i)) : PushoutToLeft1(CX(i), CY(i));
      y = (i == 0 || i == 3) ? PushoutToUp1(CX(i), CY(i)) : PushoutToDown1(CX(i), CY(i));
      if (abs32(x) < abs32(y)) {
        s->coord.x += x;
      } else {
        s->coord.y += y;
      }
      break;
    case 3: s->coord.x += PushoutToRight1(CX(0), CY(0)); break;
    case 6: s->coord.y += PushoutToDown1(CX(1), CY(1)); break;
    case 9: s->coord.y += PushoutToUp1(CX(0), CY(0)); break;
    case 12: s->coord.x += PushoutToLeft1(CX(2), CY(2)); break;
    case 7:
      s->coord.x += PushoutToRight1(CX(0), CY(0));
      s->coord.y += PushoutToDown1(CX(2), CY(2));
      break;
    case 11:
      s->coord.x += PushoutToRight1(CX(1), CY(1));
      s->coord.y += PushoutToUp1(CX(3), CY(3));
      break;
    case 13:
      s->coord.x += PushoutToLeft1(CX(2), CY(2));
      s->coord.y += PushoutToUp1(CX(0), CY(0));
      break;
    case 14:
      s->coord.x += PushoutToLeft1(CX(3), CY(3));
      s->coord.y += PushoutToDown1(CX(1), CY(1));
      break;
  }
#undef CX
#undef CY
}

// --------------------------------------------
// Death

// 0x080894cc: cut spider falls and flickers first, other deaths burst at once
static void prepareDeath(struct Spider* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == ON_CEILING) {
    s->d.x = 0;
    if (s->mode[1] >= CEILING_DESCEND && s->mode[1] <= CEILING_BOB_PAUSE) {
      s->coord.y += PIXEL(24);
      SET_YFLIP(p, TRUE);
      s->work[3] = 1;
    } else {
      s->work[3] = 0;
    }
  } else {
    s->work[3] = UPSIDE_DOWN(p);
  }
  s->d.y = 0;
  if ((s->work[0] == ON_RIGHT_WALL || s->work[0] == ON_FLOOR || s->work[0] == ON_LEFT_WALL) &&
      (s->mode[1] == 2 || (s->work[0] == ON_FLOOR && s->mode[1] == 3))) {
    s->d.x = 0;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  if ((p->body).status & BODY_STATUS_SLASHED) {
    s->mode[1] = SPIDER_FALL;
    SetMotion(s, ANIM(8));
  } else {
    s->mode[1] = SPIDER_BURST;
    SetMotion(s, ANIM(0));
  }
  s->work[2] = 0;
  EXIT_BODY(p);
}

static u8 land(struct Spider* p);

// 0x08089a40
static void Spider_Die(struct Spider* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case SPIDER_FALL:
      s->d.x = s->d.x * 230 / 256;
      s->d.y += 0x40;
      if (s->d.y > 0x6FF) s->d.y = 0x700;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->work[2] == 0 && land(p) == 2) s->work[2] = 24;
      if (s->work[2] & 2) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (s->work[2]++ > 23) s->mode[1] = SPIDER_BURST;
      return;
    case SPIDER_BURST:
      c.x = s->coord.x + sCentre[s->work[0] & 3].x;
      c.y = s->coord.y + sCentre[s->work[0] & 3].y - (s->work[3] << 12);
      CreateSmoke(1, &c);
      PlaySound(SE_ZAKO_EXPLODE);
      SET_YFLIP(p, s->work[3]);
      createPieces(p);
      s->work[2] = 4;
      if (p->homeY != 0) {
        TryDropItem(4, (struct Coord*)&s->coord);
        ApImportSpiderKilled();
        if (gScore.enemyCount < 9999) gScore.enemyCount++;
        TryDropZakoDisk((struct Enemy*)p, &s->coord);
      }
      s->mode[1]++;
      return;
    default:
      s->flags &= ~DISPLAY;
      if (--s->work[2] == 0) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      return;
  }
}

// 0x08089050: 2 when it lands on floor falling
static u8 land(struct Spider* p) {
  struct Entity* s = &p->s;
  s32 below = UPSIDE_DOWN(p) ? 0 : PIXEL(16);
  s32 floor = FUN_08009f6c(s->coord.x, s->coord.y);
  s32 r, y;
  u8 landed = 0;
  if (floor - (s->coord.y + below) <= 0x43F) {
    s->coord.y = floor - below;
    if (s->d.y > 64) landed = 2;
    s->d.y = 0;
  }
  if (s->work[0] == ON_CEILING || s->work[0] == ON_FLOOR) {
    y = s->coord.y - PIXEL(8) + below;
    if (FACING_RIGHT(p)) {
      if ((r = PushoutToLeft1(s->coord.x + PIXEL(8), y)) < 0) s->coord.x += r;
    } else if ((r = PushoutToRight1(s->coord.x - PIXEL(8), y)) > 0) {
      s->coord.x += r;
    }
  }
  return landed;
}

// --------------------------------------------
// Web, Zero 2's projectile 49. Binds Zero and drags him down.

static void Web_Init(struct Projectile* p);
static void Web_Update(struct Projectile* p);
static void Web_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2SpiderWebRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Web_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Web_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Web_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a91d8
static void createWeb(struct Spider* spider, Coords32* c, s32 speed, u8 angle) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p == NULL) return;
  INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_SPIDER_WEB);
  p->unk_28 = &spider->s;
  p->coord = *c;
  angle += 128;
  p->d.x = COS(angle) * speed / 256;
  p->d.y = SIN(angle) * speed / 256;
  PlaySound(SE_Z2_SPIDER_WEB);
}

// 0x080a9284
static void Web_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, sWeb, 0, NULL);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, ANIM(10));
  s->work[2] = 255;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Web_Update(p);
}

// 0x080a92ec
static void Web_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (s->mode[1] == 0 && (status & BODY_STATUS_BINDING)) {
    s->coord = ((p->body).bindPair)->parent->coord;
    s->d.x = 0;
    s->d.y = 0x40;
    SetMotion(s, ANIM(11));
    s->mode[1] = 1;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 0) {
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    if (--s->work[2] == 0 || FUN_080098a4(s->coord.x, s->coord.y) != 0 || (status & BODY_STATUS_B2)) {
      CreateSmoke(3, &s->coord);
      s->flags &= ~(DISPLAY | FLIPABLE);
      EXIT_BODY(p);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
    return;
  }
  if (!(status & BODY_STATUS_BINDING)) {
    SetMotion(s, ANIM(12));
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Web_Die(p);
    return;
  }
  {
    struct Entity* zero = ((p->body).bindPair)->parent;
    if (s->coord.y != zero->coord.y) {
      s->coord.y = zero->coord.y;
      s->d.y = 0x40;
    } else if (s->d.y <= 0x6FF) {
      s->d.y += 0x40;
    }
    if (FUN_080098a4(s->coord.x, s->coord.y + s->d.y) == 0) s->coord.y += s->d.y;
    zero->coord = s->coord;
  }
}

// 0x080a9464
static void Web_Die(struct Projectile* p) {
  UpdateEntityAnim(&p->s);
  if ((p->s).motion.state == ANIM_END) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Pieces, Zero 2's VFX 54

static void Piece_Init(struct VFX* p);
static void Piece_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2SpiderPieceRoutine = {
    [ENTITY_INIT] =      Piece_Init,
    [ENTITY_UPDATE] =    Piece_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bb30c
static void createPieces(struct Spider* spider) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_SPIDER_PIECE);
      p->work[1] = i;
      p->unk_28 = &spider->s;
      p->coord = (spider->s).coord;
    }
  }
}

// 0x080bb3f8
static void Piece_Init(struct VFX* p) {
  static const u8 anims[3] = {15, 14, 16};
  struct Entity* s = &p->s;
  bool8 right = FACING_RIGHT(s->unk_28);
  s32 k = right ? 2 - s->work[1] : s->work[1];
  s->flags |= DISPLAY;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SET_XFLIP(p, right);
  SET_YFLIP(p, UPSIDE_DOWN(s->unk_28));
  SetMotion(s, ANIM(anims[s->work[1]]));
  s->d.x = (k - 1) * 256 + (RANDOM(RNG_0202f388) & 0x1FF) - 256;
  s->d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x1FF);
  s->work[2] = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Piece_Update(p);
}

// 0x080bb524
static void Piece_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if (++s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  UpdateEntityAnim(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0 && s->d.y > 0) {
    CreateSmoke(3, &s->coord);
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
  }
}

// -------------------------------------------
// clang-format off
static const struct Collision sBody[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0xa00, 0x1400, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0xa00, 0x1400, 0x1400}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0xa00, 0x1400, 0x1400}};

// 0x08341aa0 holds these as identical pairs, one of each is enough
static const struct Collision sThread[8] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x3000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x4000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x5000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x6000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x7000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, -0x8000}},
};

// Damage 255 is no damage. unk_0a 0x21 binds for 16 frames.
static const struct Collision sWeb[2] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 33, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 33, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

#endif  // AP
