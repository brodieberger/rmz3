#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's man-eating flower, enemy 51.
  work0: unused
*/

struct Flower {
  OBJECT_HDR;
  u8 coll;                       // 0xB4, which pair of sCollisions
  u8 caught;                     // 0xB5, Zero in mouth: sCollisions[15], which binds
  u8 hitStun;                    // 0xB6
  u8 stunTimer;                  // 0xB7
  struct Entity* elementEffect;  // 0xB8
  u8 depth;                      // 0xBC, how far down its throat Zero is, 8 px a step
  u8 dying;                      // 0xBD
  u8 zeroFacing;                 // 0xBE
  u8 throwRight;                 // 0xBF
  s32 lastZeroX;                 // 0xC0
};
static_assert(sizeof(struct Flower) == sizeof(struct Enemy));

enum {
  FLOWER_IDLE,
  FLOWER_BITE,
  FLOWER_CHOMP,
  FLOWER_SWALLOW,
  FLOWER_CHEW,
  FLOWER_SPIT,
  FLOWER_CLOSE,
  FLOWER_RECOVER,
  FLOWER_REST,
  FLOWER_CAUGHT,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_FLOWER, (n))
#define CAUGHT_COLL 15

static const struct Collision sCollisions[17][2];
static const Coords32 sElementCoord = {0, -PIXEL(16)};

static void Flower_Init(struct Flower* p);
static void Flower_Update(struct Flower* p);
static void Flower_Die(struct Flower* p);

// clang-format off
const EnemyRoutine gApZ2FlowerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Flower_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Flower_Update,
    [ENTITY_DIE] =       (EnemyFunc)Flower_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Flower* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

// 0x08081f98
static void setColl(struct Flower* p, u8 n) {
  p->coll = n;
  SetDDP(&p->body, sCollisions[p->caught ? CAUGHT_COLL : n]);
}

static bool8 holding(struct Flower* p) { return ((p->body).status & BODY_STATUS_BINDING) && pZero2 != NULL; }

// Zero, held in its mouth
static void placeZero(struct Flower* p, s32 lower) {
  (pZero2->s).coord.x = (p->s).coord.x - (p->s).unk_coord.x;
  (pZero2->s).coord.y = (p->s).coord.y - (p->s).unk_coord.y - PIXEL(13) - lower;
}

// Moves hitbox with frame. Returns TRUE when frame changed.
static bool8 animate(struct Flower* p) {
  s8 was = (p->s).motion.cmdIdx;
  UpdateEntityAnim(&p->s);
  return (p->s).motion.cmdIdx != was;
}

static bool8 animEnded(struct Flower* p) { return (p->s).motion.state == ANIM_END; }
static bool8 loopEnded(struct Flower* p) { return (p->s).motion.state == ANIM_NEXT_GOTO; }

// Throw is a blownSpeed like Pantheon Fist, so the air state doesn't take Zero's x from the
// d-pad
static void throwZero(struct Flower* p) {
  struct Zero* z = pZero2;
  GotoMotion(&z->s, MOTION(DM004_ZERO_AIR, 4), 2, 1);
  (z->s).mode[1] = ZERO_AIR, (z->s).mode[2] = 2, (z->s).mode[3] = 1;
  (z->unk_b4).blownSpeed = p->throwRight ? PIXEL(2) : -PIXEL(2);
  (z->s).d.y = -0x580;
}

// --------------------------------------------

static void Flower_Kill(struct Flower* p);

// 0x08081fd8. Hurtboxes are priority layers, only flame kills it.
static void Flower_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Flower* p = (struct Flower*)body->parent;
  if ((body->hitboxFlags & BODY_STATUS_B3) && (body->enemy->element & 0xF) == ELEMENT_FLAME) {
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Flower_Kill(p);
  }
}

// 0x08081634
static void Flower_Init(struct Flower* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(p, FLOWER_IDLE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->renderPrio = 24;
  SET_XFLIP(p, FALSE);
  SetMotion(s, ANIM(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->coll = 0;
  p->caught = 0;
  p->elementEffect = NULL;
  p->hitStun = 0;
  p->dying = 0;
  INIT_BODY(p, sCollisions[0], 4, Flower_OnCollision);
  Flower_Update(p);
}

static void Flower_Idle(struct Flower* p);
static void Flower_Bite(struct Flower* p);
static void Flower_Chomp(struct Flower* p);
static void Flower_Swallow(struct Flower* p);
static void Flower_Chew(struct Flower* p);
static void Flower_Spit(struct Flower* p);
static void Flower_Close(struct Flower* p);
static void Flower_Recover(struct Flower* p);
static void Flower_Rest(struct Flower* p);
static void Flower_Caught(struct Flower* p);

// 0x080816f0. Hit stops it for 32 frames.
static void Flower_Update(struct Flower* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (status & BODY_STATUS_WHITE) {
    if (p->elementEffect == NULL) {
      p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    }
    p->hitStun = 1;
    p->stunTimer = 32;
  }
  if (status & BODY_STATUS_DEAD) {
    EXIT_BODY(p);
    p->dying = 1;
  }
  if (p->dying) {
    if (--p->stunTimer == 0) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      Flower_Kill(p);
    }
    return;
  }

  if (p->lastZeroX != (pZero2->s).coord.x) p->lastZeroX = (pZero2->s).coord.x;

  if (IsFrozen(p)) {
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      setColl(p, p->coll);
    }
    if (p->caught) {
      p->caught = 0;
      s->renderPrio = 24;
      setColl(p, p->coll);
    }
    return;
  }
  if (p->elementEffect != NULL && IsDead(p->elementEffect)) p->elementEffect = NULL;
  if (p->hitStun) {
    if (--p->stunTimer != 0) return;
    p->hitStun = 0;
  }

  switch (s->mode[1]) {
    case FLOWER_IDLE: Flower_Idle(p); break;
    case FLOWER_BITE: Flower_Bite(p); break;
    case FLOWER_CHOMP: Flower_Chomp(p); break;
    case FLOWER_SWALLOW: Flower_Swallow(p); break;
    case FLOWER_CHEW: Flower_Chew(p); break;
    case FLOWER_SPIT: Flower_Spit(p); break;
    case FLOWER_CLOSE: Flower_Close(p); break;
    case FLOWER_RECOVER: Flower_Recover(p); break;
    case FLOWER_REST: Flower_Rest(p); break;
    case FLOWER_CAUGHT: Flower_Caught(p); break;
  }
}

// 0x08081900: shut until Zero is within 48 px across, feet between 96 px above and 16 px below
static void Flower_Idle(struct Flower* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    setColl(p, 0);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->coord.y >= z->coord.y - PIXEL(16) && z->coord.y >= s->coord.y - PIXEL(96) &&
      (u32)(z->coord.x - s->coord.x + PIXEL(48)) <= PIXEL(96)) {
    setMode(p, FLOWER_BITE);
  }
}

// 0x08081974
static void Flower_Bite(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(1));
    setColl(p, 0);
    s->mode[2]++;
  }
  if (animate(p)) setColl(p, s->motion.cmdIdx);
  if (((p->body).status & BODY_STATUS_B2) && pZero2 != NULL) {
    struct Entity* z = &pZero2->s;
    p->caught = 1;
    setColl(p, p->coll);
    p->zeroFacing = (z->flags & X_FLIP) != 0;
    if (z->coord.x < p->lastZeroX) {
      p->throwRight = TRUE;
    } else if (z->coord.x > p->lastZeroX) {
      p->throwRight = FALSE;
    } else {
      p->throwRight = !p->zeroFacing;
    }
    p->depth = 3;
    s->unk_coord.x = s->coord.x - z->coord.x;
    if (s->unk_coord.x > PIXEL(4)) s->unk_coord.x = PIXEL(4);
    if (s->unk_coord.x < -PIXEL(4)) s->unk_coord.x = -PIXEL(4);
    s->unk_coord.y = s->coord.y - PIXEL(13) - p->depth * PIXEL(8) - z->coord.y;
    if (s->unk_coord.y > PIXEL(4)) s->unk_coord.y = PIXEL(4);
    if (s->unk_coord.y < -PIXEL(6)) s->unk_coord.y = -PIXEL(6);
    placeZero(p, p->depth * PIXEL(8));
    setMode(p, FLOWER_CAUGHT);
    return;
  }
  if (animEnded(p)) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    setMode(p, FLOWER_CHOMP);
  }
}

// 0x08081ba4: missed
static void Flower_Chomp(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2));
    setColl(p, 10);
    s->work[2] = 12;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  if (s->work[2] % 12 == 0) PlaySound(SE_Z2_FLOWER_CHOMP);
  if (s->work[2] == 0 && loopEnded(p)) setMode(p, FLOWER_CLOSE);
}

// 0x08081ae0: last frames of bite, Zero in mouth
static void Flower_Caught(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (holding(p)) s->renderPrio = 8;
    s->mode[2]++;
  }
  if (animate(p)) setColl(p, s->motion.cmdIdx);
  if (holding(p)) {
    placeZero(p, p->depth * PIXEL(8));
    if (animEnded(p)) {
      PlaySound(SE_Z2_FLOWER_CHOMP);
      setMode(p, FLOWER_SWALLOW);
    }
  } else if (animEnded(p)) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    p->caught = 0;
    setMode(p, FLOWER_CHOMP);
  }
}

// 0x08081c10
static void Flower_Swallow(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    setColl(p, 11);
    s->mode[2]++;
  }
  if (holding(p)) {
    if (animate(p)) {
      if (p->depth != 0) p->depth--;
      setColl(p, s->motion.cmdIdx + 10);
    }
    placeZero(p, p->depth * PIXEL(8));
    if (animEnded(p)) setMode(p, FLOWER_CHEW);
  } else {
    UpdateEntityAnim(s);
    if (animEnded(p)) {
      p->caught = 0;
      setMode(p, FLOWER_RECOVER);
    }
  }
}

// 0x08081cd0
static void Flower_Chew(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    setColl(p, 16);
    SetMotion(s, ANIM(4));
    s->work[2] = 24;
    s->mode[2]++;
  }
  if (s->work[2] % 12 == 0) PlaySound(SE_Z2_FLOWER_CHOMP);
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  if (holding(p)) {
    placeZero(p, s->motion.cmdIdx == 1 ? PIXEL(2) : 0);
  } else if (s->work[2] == 0 && loopEnded(p)) {
    p->caught = 0;
  }
  if (s->work[2] == 0 && loopEnded(p)) setMode(p, FLOWER_SPIT);
}

// 0x08081da0: lets go on second frame, throws him once binding ends
static void Flower_Spit(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    setColl(p, 16);
    SetMotion(s, ANIM(5));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((p->body).status & BODY_STATUS_BINDING) {
    if (pZero2 != NULL) {
      placeZero(p, 0);
      if (s->motion.cmdIdx == 1) {
        p->caught = 0;
        setColl(p, 0);
        s->work[2]++;
      }
    }
  } else if (s->work[2] != 0 && pZero2 != NULL) {
    throwZero(p);
    s->work[2] = 0;
  }
  if (animEnded(p)) {
    p->caught = 0;
    setMode(p, FLOWER_RECOVER);
  }
}

// 0x08081e80
static void Flower_Close(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(6));
    setColl(p, 5);
    s->mode[2]++;
  }
  if (animate(p)) setColl(p, s->motion.cmdIdx / 2 + 5);
  if (animEnded(p)) setMode(p, FLOWER_REST);
}

// 0x08081ee4
static void Flower_Recover(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->renderPrio = 24;
    setColl(p, 0);
    s->work[2] = 60;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[2] == 1) {
    if (--s->work[2] == 0) {
      SetMotion(s, ANIM(0));
      s->work[2] = 33;
      s->mode[2]++;
    }
  } else if (s->mode[2] == 2) {
    if (--s->work[2] == 0) setMode(p, FLOWER_IDLE);
  }
}

// 0x08081f54
static void Flower_Rest(struct Flower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    setColl(p, 0);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) setMode(p, FLOWER_IDLE);
}

// --------------------------------------------

// 0x0808184c
static void Flower_Kill(struct Flower* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  PlaySound(SE_ZAKO_EXPLODE);
  c.x = s->coord.x + ((RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  c.y = s->coord.y - PIXEL(12) + ((RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  CreateSmoke(1, &c);
  TryDropItem(4, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void Flower_Die(struct Flower* p) { Flower_Kill(p); }

// clang-format off
// 0x08340d08: a pair per pose. 15 is open mouth with Zero in it.
static const struct Collision sCollisions[17][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x600, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x600, 0x1400, 0xc00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x600, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x600, 0x1400, 0xc00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x1400, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0xd00, 0x1000, 0x1a00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2400, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1500, 0x1000, 0x2a00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x3000, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1b00, 0x1000, 0x3600}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2c00, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1900, 0x1000, 0x3100}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2800, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1700, 0x1000, 0x2d00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2400, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1500, 0x1000, 0x2900}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2000, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1300, 0x1000, 0x2500}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x1800, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0xf00, 0x1000, 0x1d00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x3000, 0x1400, 0xc00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1b00, 0x1000, 0x3600}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2a00, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1800, 0x1000, 0x2f00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x2200, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1400, 0x1000, 0x2700}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x1a00, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0x1000, 0x1000, 0x1f00}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x1200, 0xa00, 0xa00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0xc00, 0x1000, 0x1700}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 33, 1, 0x00000001, {0x0, -0x2000, 0x4000, 0x4000}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 33, 0, 0xdfbbdef7, {0x0, -0x2000, 0x4000, 0x4000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 0x00000001, {0x0, -0x1200, 0xe00, 0xe00}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0, 0, 0xdfbbdef7, {0x0, -0xd00, 0x1000, 0x1900}},
    },
};
// clang-format on

#endif  // AP
