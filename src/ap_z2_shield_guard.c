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

#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's shield guard, enemy 9.
  work0:
    0: charges when Zero is close, fires its mace farther out
    1: only fires its mace, also set when it lands on a new post
  work1:
    0: shield
    1: no shield
*/

struct Guard {
  OBJECT_HDR;
  s32 postX;          // 0xB4
  s32 postY;          // 0xB8
  u8 hitFromRight;    // 0xBC
  bool8 shielded;     // 0xBD
  u8 aim;             // 0xBE
  bool8 goHome;       // 0xBF
  u8 _c0;
  bool8 alive;        // 0xC1, read by mace
  bool8 recallMace;   // 0xC2, read by mace
  u8 _c3;
};
static_assert(sizeof(struct Guard) == sizeof(struct Enemy));

enum {
  GUARD_FALL,
  GUARD_ELEMENT_HIT,
  GUARD_PULLED = 3,
  GUARD_DECIDE = 4,
  GUARD_WAIT,
  GUARD_AIM,
  GUARD_FIRE,
  GUARD_RETRACT,
  GUARD_CROUCH,
  GUARD_CHARGE,
  GUARD_RECOVER,
  GUARD_HOP_HOME,
  GUARD_LAND,
  GUARD_RECOIL,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_SHIELD_GUARD, n)

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define gravity unk_coord.y
#define mace unk_28
#define dashBrake unk_coord.x

// Shielded and bare versions of each animation
static motion_t pick(struct Guard* p, u8 shielded, u8 bare) { return p->shielded ? ANIM(shielded) : ANIM(bare); }

static const struct Collision sShielded[3];
static const struct Collision sCollisions[2];
static const struct Collision sHarmless;
static const struct Collision sCharge[3];
static const struct SlashedEnemy sGibs[5];
static const struct SlashedEnemy sShieldOff;
static const Coords32 sElementCoord = {0, -PIXEL(16)};

static void Guard_Pulled(struct Guard* p);
static u8 gibFlip(struct Guard* p);
static u16 Guard_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Guard_Init(struct Guard* p);
static void Guard_Update(struct Guard* p);
static void Guard_Die(struct Guard* p);
static struct Entity* createMace(struct Guard* guard, u8 aim);
static void createTopHalf(Coords32* c, bool8 right, u8 hitFromRight);

// clang-format off
const EnemyRoutine gApZ2ShieldGuardRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Guard_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Guard_Update,
    [ENTITY_DIE] =       (EnemyFunc)Guard_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Guard* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void setStance(struct Guard* p) { SetDDP(&p->body, p->shielded ? sShielded : sCollisions); }

static void faceZero(struct Guard* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static bool8 onSpikes(struct Guard* p) {
  return (GetMetatileAttr((p->s).coord.x, (p->s).coord.y + PIXEL(8)) & MTATTR_SPIKE) != 0;
}

static void Guard_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Guard* p = (struct Guard*)body->parent;
    p->hitFromRight = (body->enemy->parent->coord).x > (p->s).coord.x;
  }
}

// 0x0806b1c0
static void Guard_Init(struct Guard* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, s->work[1] == 0 ? ANIM(0) : ANIM(8));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sShielded, 16, Guard_OnCollision);
  (p->body).unk_28 = (u32)Guard_Pull;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->postX = s->coord.x;
  p->postY = s->coord.y;
  s->gravity = 0;
  p->goHome = FALSE;
  p->shielded = s->work[1] == 0;
  p->alive = TRUE;
  p->recallMace = FALSE;
  s->unk_2c = NULL;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = GUARD_DECIDE;
  Guard_Update(p);
}

static void Guard_Recoil(struct Guard* p);
static void Guard_Fall(struct Guard* p);
static void Guard_ElementHit(struct Guard* p);
static void Guard_Decide(struct Guard* p);
static void Guard_Wait(struct Guard* p);
static void Guard_Aim(struct Guard* p);
static void Guard_Fire(struct Guard* p);
static void Guard_Retract(struct Guard* p);
static void Guard_Crouch(struct Guard* p);
static void Guard_Charge(struct Guard* p);
static void Guard_Recover(struct Guard* p);
static void Guard_HopHome(struct Guard* p);
static void Guard_Land(struct Guard* p);

// 0x0806b2e0
static void Guard_Update(struct Guard* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != GUARD_RECOIL) {
    p->recallMace = TRUE;
    setMode(p, GUARD_RECOIL);
  }
  if (s->mode[1] == GUARD_RECOIL) {
    Guard_Recoil(p);
    return;
  }

  if ((status & BODY_STATUS_DEAD) || onSpikes(p)) {
    if (status & BODY_STATUS_DEAD) {
      p->alive = FALSE;  // mace flies off instead of vanishing
    } else {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    }
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Guard_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    SetMotion(s, pick(p, 0, 8));
    setStance(p);
    UpdateEntityAnim(s);
    s->unk_2c = NULL;
    setMode(p, GUARD_DECIDE);
    return;
  }

  // 0x0806b4b8: falls when off the ground
  if (s->mode[1] > 2 && s->gravity == 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    } else {
      setMode(p, GUARD_FALL);
    }
  }

  // 0x0806b4f4
  if (s->mode[1] != GUARD_ELEMENT_HIT && (status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) setMode(p, GUARD_ELEMENT_HIT);
  }

  switch (s->mode[1]) {
    case GUARD_FALL: Guard_Fall(p); break;
    case GUARD_ELEMENT_HIT: Guard_ElementHit(p); break;
    case GUARD_PULLED: Guard_Pulled(p); break;
    case GUARD_DECIDE: Guard_Decide(p); break;
    case GUARD_WAIT: Guard_Wait(p); break;
    case GUARD_AIM: Guard_Aim(p); break;
    case GUARD_FIRE: Guard_Fire(p); break;
    case GUARD_RETRACT: Guard_Retract(p); break;
    case GUARD_CROUCH: Guard_Crouch(p); break;
    case GUARD_CHARGE: Guard_Charge(p); break;
    case GUARD_RECOVER: Guard_Recover(p); break;
    case GUARD_HOP_HOME: Guard_HopHome(p); break;
    case GUARD_LAND: Guard_Land(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Guard_Recoil(struct Guard* p) {
  if (ApRecoilFly((Object*)p)) {
    p->alive = FALSE;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    EXIT_BODY(p);
    Guard_Die(p);
  }
}

static void fall(struct Entity* s) {
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  s->coord.y += s->d.y;
}

// 0x0806b6c8
static void Guard_Pulled(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, p->shielded ? ANIM(0) : ANIM(8));
    p->recallMace = TRUE;
    s->mode[2]++;
  } else if (s->mode[2] == 2) {
    if (s->unk_2c != NULL) s->mode[1] = GUARD_ELEMENT_HIT;
    useApSheets(CreateSlashedEnemy(&s->coord, &sShieldOff, 0, gibFlip(p)));
    setStance(p);
    s->mode[2] = 0;
  }
  UpdateEntityAnim(s);
}

// 0x0806c2c4: first tug takes shield off, then dragged
static u16 Guard_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  struct Guard* p = (struct Guard*)s;
  p->recallMace = TRUE;
  s->mode[1] = GUARD_PULLED;
  s->mode[2] = 0;
  if (p->shielded) {
    if (dx == 0 && dy == 0) return 1;
    p->shielded = FALSE;
    s->mode[2] = 2;
    return 0;
  }
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling && FUN_080098a4(s->coord.x, s->coord.y) == 0) return 1;
  s->mode[1] = s->unk_2c != NULL ? GUARD_ELEMENT_HIT : GUARD_FALL;
  return 0;
}

// 0x0806b530: where it lands becomes its post
static void Guard_Fall(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 29, 32));
    setStance(p);
    s->d.x = s->d.y = 0;
    p->recallMace = TRUE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fall(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (p->postX != s->coord.x) {
    p->postX = s->coord.x;
    s->work[0] = 1;
  }
  p->postY = s->coord.y;
  setMode(p, GUARD_LAND);
  s->work[2] = 32;
}

// 0x0806b5ec: harmless while burning or thawing
static void Guard_ElementHit(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 0, 8));
    SetDDP(&p->body, &sHarmless);
    s->d.x = s->d.y = 0;
    p->recallMace = TRUE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (FUN_080098a4(s->coord.x, s->coord.y + 1) == 0) {
    fall(s);
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  }
  if (IsDead(s->unk_2c)) {
    s->unk_2c = NULL;
    setStance(p);
    s->mode[1] = GUARD_FALL;
    s->mode[2] = 1;
  }
}

// 0x0806b750: back to post first if it strayed 80 px or charged into something
static void Guard_Decide(struct Guard* p) {
  struct Entity* s = &p->s;
  s32 dx, dy, fromPost;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 0, 8));
    setStance(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  faceZero(p);
  dx = (pZero2->s).coord.x - s->coord.x;
  if (dx < 0) dx = -dx;
  dy = (pZero2->s).coord.y - s->coord.y;
  if (dy < 0) dy = -dy;
  fromPost = p->postX - s->coord.x;
  if (fromPost < 0) fromPost = -fromPost;
  if (p->goHome || fromPost > PIXEL(80)) {
    p->goHome = FALSE;
    setMode(p, GUARD_HOP_HOME);
    return;
  }
  if (s->work[0] == 1) {
    if (dx <= 0x8FFF && dy <= 0x5FFF) setMode(p, GUARD_AIM);
  } else if (dx <= 0x4FFF && dy <= 0x3FFF) {
    setMode(p, GUARD_CROUCH);
  } else if (dx <= 0x63FF && dy <= 0x47FF) {
    setMode(p, (RANDOM(RNG_0202f388) & 1) ? GUARD_CROUCH : GUARD_AIM);
  } else if (dx <= 0x8FFF && dy <= 0x5FFF) {
    setMode(p, GUARD_AIM);
  }
}

// 0x0806b8d4
static void Guard_Wait(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 0, 8));
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, GUARD_DECIDE);
}

// 0x0806b92c
static void Guard_Aim(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    faceZero(p);
    p->aim = ArcTan2((s->coord.x - (pZero2->s).coord.x) >> 8, (s->coord.y - (pZero2->s).coord.y) >> 8) >> 8;
    SetMotion(s, pick(p, 1, 9));
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, GUARD_FIRE);
}

// 0x0806b9fc
static void Guard_Fire(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 2, 10));
    SetDDP(&p->body, sCollisions);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] != 0) {
    if (s->mace == NULL || s->mace->mode[0] > ENTITY_UPDATE) setMode(p, GUARD_RETRACT);
  } else if ((s->motion).state == ANIM_NEXT_GOTO) {
    s->mace = createMace(p, p->aim);
    p->recallMace = FALSE;
    s->work[2] = 48;
    s->mode[3]++;
  }
}

// 0x0806ba94
static void Guard_Retract(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 3, 11));
    setStance(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(p, GUARD_WAIT);
}

// 0x0806bb04
static void Guard_Crouch(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 4, 12));
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, GUARD_CHARGE);
}

// 0x0806bb60. Zero 2 only brakes a rightward charge, a leftward one keeps going.
static void Guard_Charge(struct Guard* p) {
  struct Entity* s = &p->s;
  s32 ahead;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 5, 13));
    s->d.x = FACING_RIGHT(p) ? PIXEL(4) : -PIXEL(4);
    s->dashBrake = 32;
    SetDDP(&p->body, sCharge);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  ahead = s->coord.x + (s->d.x > 0 ? PIXEL(12) : -PIXEL(12));
  if (FUN_080098a4(ahead, s->coord.y - PIXEL(8)) != 0 || FUN_080098a4(ahead, s->coord.y + PIXEL(10)) == 0) {
    p->goHome = TRUE;
    s->d.x = 0;
  }
  s->coord.x += s->d.x;
  s->work[2] = (s->work[2] + 1) % 6;
  if (s->work[2] == 0) {
    Coords32 c;
    c.x = s->coord.x + (FACING_RIGHT(p) ? -PIXEL(12) : PIXEL(12));
    c.y = s->coord.y;
    CreateSmoke(3, &c);
  }
  if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) {
    setMode(p, GUARD_FALL);
    return;
  }
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->d.x != 0) {
    s->d.x -= s->dashBrake;
  } else {
    setMode(p, GUARD_RECOVER);
  }
}

// 0x0806bca4
static void Guard_Recover(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, pick(p, 26, 27));
    SetDDP(&p->body, sShielded);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(p, GUARD_WAIT);
}

// 0x0806bd08: one hop back to post
static void Guard_HopHome(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.x = (p->postX - s->coord.x) / 36;
    if (s->d.x > PIXEL(8)) s->d.x = PIXEL(8);
    if (s->d.x < -PIXEL(8)) s->d.x = -PIXEL(8);
    s->d.y = -PIXEL(4);
    s->gravity = 0x40;
    if (FACING_RIGHT(p) && s->d.x < 0) {
      SetMotion(s, pick(p, 6, 14));  // backwards
    } else {
      SetMotion(s, pick(p, 28, 31));
    }
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0) {
    if (IsSpriteAnimEnd(s)) s->mode[3]++;
    return;
  }
  if (FUN_080098a4(s->coord.x + (s->d.x > 0 ? PIXEL(12) : -PIXEL(12)), s->coord.y) != 0) s->d.x = 0;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += s->gravity;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (s->d.y > 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->gravity = 0;
      setMode(p, GUARD_LAND);
    }
  } else if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(32)) != 0) {
    s->d.y = -s->d.y;
  }
}

// 0x0806be5c
static void Guard_Land(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (FACING_RIGHT(p) && s->d.x < 0) {
      SetMotion(s, pick(p, 7, 15));
    } else {
      SetMotion(s, pick(p, 30, 33));
    }
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2]++ <= 9 && s->d.x != 0) {
    if (FUN_080098a4(s->coord.x + (s->d.x > 0 ? PIXEL(12) : -PIXEL(12)), s->coord.y) != 0) s->d.x = 0;
    s->coord.x += s->d.x >> 2;
  }
  if (IsSpriteAnimEnd(s)) setMode(p, GUARD_WAIT);
}

// --------------------------------------------

static u8 gibFlip(struct Guard* p) { return p->hitFromRight | (FACING_RIGHT(p) << 4); }

static void finish(struct Guard* p) {
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(4, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0806bf20
static void Guard_Explode(struct Guard* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s32 i;
  s->flags &= ~DISPLAY;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(16);
  for (i = 0; i < 5; i++) useApSheets(CreateSlashedEnemy(&c, &sGibs[i], 0, gibFlip(p)));
  CreateSmoke(1, &c);
  finish(p);
}

// 0x0806c064: legs slide on and burst
static void Guard_Cut(struct Guard* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (s->mode[3] == 0) {
    bool8 right = FACING_RIGHT(p);
    SetMotion(s, ANIM(24));
    if (right == p->hitFromRight) {
      s->d.x = 64, s->unk_coord.x = -4;
    } else {
      s->d.x = -192, s->unk_coord.x = 8;
    }
    if (right) s->d.x = -s->d.x, s->unk_coord.x = -s->unk_coord.x;
    s->d.y = 0;
    s->work[2] = 23;
    createTopHalf(&s->coord, right, p->hitFromRight);
    s->mode[3]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->d.x += s->unk_coord.x;
  if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(4)) == 0) {
    s->d.y += 0x40;
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(4)) != 0) s->work[2] = 0;
  }
  if (--s->work[2] != 0xFF) return;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(16);
  useApSheets(CreateSlashedEnemy(&c, &sGibs[0], 0, gibFlip(p)));
  useApSheets(CreateSlashedEnemy(&c, &sGibs[4], 0, gibFlip(p)));
  c.x += FACING_RIGHT(p) ? -PIXEL(8) : PIXEL(8);
  CreateSmoke(1, &c);
  c.x += PIXEL(16) - (RANDOM(RNG_0202f388) & 0x1FFF);
  c.y += PIXEL(16) - (RANDOM(RNG_0202f388) & 0x1FFF);
  CreateSmoke(2, &c);
  finish(p);
}

// 0x0806b3f0
static void Guard_Die(struct Guard* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[1] = (!onSpikes(p) && ((p->body).status & BODY_STATUS_SLASHED)) ? 1 : 0;
    EXIT_BODY(p);
    s->mode[2]++;
  }
  if (s->mode[1] == 0) {
    Guard_Explode(p);
  } else {
    Guard_Cut(p);
  }
}

// --------------------------------------------
// Mace and chain, Zero 2's projectile 5. Four links each drawn in two places on alternate
// frames, so eight show.

struct Mace {
  OBJECT_HDR;
  s32 x;          // 0xB4, from hand
  s32 y;          // 0xB8
  struct Mace* head;  // 0xBC, a link's mace
  u8 aim;         // 0xC0
  u8 divisions;   // 0xC1, a link's: chain's eighths
  u8 slot;        // 0xC2, a link's: which eighth
  bool8 returning;  // 0xC3
};
static_assert(sizeof(struct Mace) == sizeof(struct Projectile));

enum {
  MACE,
  LINK,
};

#define decel unk_coord

static const struct Collision sMace;

static void Mace_Init(struct Mace* p);
static void Mace_Update(struct Mace* p);
static void Mace_Die(struct Mace* p);

// clang-format off
const ProjectileRoutine gApZ2ShieldGuardMaceRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Mace_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Mace_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Mace_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static struct Mace* allocMace(struct Guard* guard, u8 kind) {
  struct Mace* p = (struct Mace*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_SHIELD_GUARD_MACE);
    (p->s).unk_28 = (struct Entity*)guard;
    (p->s).work[0] = kind;
  }
  return p;
}

// 0x08098e80
static struct Entity* createMace(struct Guard* guard, u8 aim) {
  struct Mace* p = allocMace(guard, MACE);
  if (p != NULL) p->aim = aim;
  return (struct Entity*)p;
}

// 0x08098ed4
static void createLink(struct Mace* head, u8 slot) {
  struct Mace* p = allocMace((struct Guard*)(head->s).unk_28, LINK);
  if (p != NULL) {
    p->head = head;
    p->divisions = 8;
    p->slot = slot;
  }
}

static Coords32 hand(struct Guard* guard) {
  Coords32 c;
  c.x = (guard->s).coord.x + (FACING_RIGHT(guard) ? PIXEL(24) : -PIXEL(24));
  c.y = (guard->s).coord.y - PIXEL(17);
  return c;
}

// 0x08099118 / 0x08099258
static void Mace_Init(struct Mace* p) {
  struct Entity* s = &p->s;
  struct Entity* guard = s->unk_28;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SET_XFLIP(p, FACING_RIGHT(guard));
  if (s->work[0] == MACE) {
    u8 a = p->aim + 128;
    SetMotion(s, ANIM(18));
    UpdateEntityAnim(s);
    INIT_BODY(p, &sMace, 1, NULL);
    s->d.x = COS(a) * 3;
    s->d.y = SIN(a) * 3;
    s->decel.x = -s->d.x / 4;
    s->decel.y = -s->d.y / 4;
    s->work[2] = 18;
    p->x = p->y = 0;
    p->returning = FALSE;
    p->slot = 0;
    createLink(p, 1);
    createLink(p, 3);
    createLink(p, 5);
    createLink(p, 7);
  } else {
    SetMotion(s, ANIM(17));
    UpdateEntityAnim(s);
    s->renderPrio = 25;
    s->d.x = s->d.y = 0;
    p->returning = FALSE;
    s->work[2] = 0;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Mace_Update(p);
}

static void place(struct Mace* p, Coords32 from) {
  (p->s).coord.x = from.x + p->x;
  (p->s).coord.y = from.y + p->y;
}

// 0x080992f4
static void Mace_Fly(struct Mace* p) {
  struct Entity* s = &p->s;
  Coords32 from = hand((struct Guard*)s->unk_28);
  if (((p->body).status & BODY_STATUS_B2) && !((p->body).prevStatus & BODY_STATUS_B2)) {
    PlaySound(SE_Z2_SHIELD_GUARD_MACE_HIT);
  }
  switch (s->mode[2]) {
    case 0:  // full speed for 19 frames
      p->x += s->d.x;
      p->y += s->d.y;
      place(p, from);
      if (--s->work[2] == 0xFF) {
        s->work[2] = 0;
        s->mode[2]++;
      }
      return;
    case 1:  // slowing, for 3
      p->x += s->d.x + s->decel.x * s->work[2];
      p->y += s->d.y + s->decel.y * s->work[2];
      place(p, from);
      if (s->work[2]++ > 2) {
        s->work[2] = 32;
        s->mode[2]++;
      }
      return;
    case 2:  // held out for 33
      place(p, from);
      if (--s->work[2] == 0xFF) {
        p->returning = TRUE;
        s->d.x = s->decel.x * 4;
        s->d.y = s->decel.y * 4;
        s->mode[2]++;
      }
      return;
    case 3: {  // back until it passes the hand both ways
      bool8 pastX, pastY;
      p->x += s->d.x;
      p->y += s->d.y;
      place(p, from);
      pastX = s->d.x < 0 ? s->coord.x <= from.x : s->coord.x >= from.x;
      pastY = s->d.y < 0 ? s->coord.y <= from.y : s->coord.y >= from.y;
      if (pastX && pastY) SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
}

// 0x08099490: on the line from mace to hand, in eighths
static void Link_Update(struct Mace* p) {
  struct Entity* s = &p->s;
  struct Mace* head = p->head;
  Coords32 from;
  s32 stepX, stepY;
  u8 n;
  if ((head->s).mode[0] > ENTITY_UPDATE) {
    s->flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  from = hand((struct Guard*)s->unk_28);
  stepX = (from.x - (head->s).coord.x) / p->divisions;
  stepY = (from.y - (head->s).coord.y) / p->divisions;
  n = (s->work[2]++ & 1) ? p->slot : p->slot + 1;
  s->coord.x = (head->s).coord.x + stepX * n;
  s->coord.y = (head->s).coord.y + stepY * n;
  s->d = (head->s).d;
  p->returning = head->returning;
}

// 0x08098f50: flies off when guard dies
static void Mace_Update(struct Mace* p) {
  struct Entity* s = &p->s;
  struct Guard* guard = (struct Guard*)s->unk_28;
  if ((guard->s).mode[0] > ENTITY_UPDATE) {
    if (!guard->alive) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Mace_Die(p);
    } else {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
    return;
  }
  if (IsFrozen(guard) || guard->recallMace) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->work[0] == MACE) {
    Mace_Fly(p);
  } else {
    Link_Update(p);
  }
}

// 0x08099004
static void Mace_Die(struct Mace* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    if (p->returning) {
      s->d.x = ((p->slot + 1) * 32 * s->d.x) / 256;
    } else {
      s->d.x = ((9 - p->slot) * 32 * s->d.x) / 256;
    }
    s->d.y = s->d.y - PIXEL(2) - (RANDOM(RNG_0202f388) & 0x1FF);
    s->work[2] = (p->slot & 1) + 32;
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  if (--s->work[2] == 0xFF) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Upper half thrown off by a cut, Zero 2's VFX 21

static void TopHalf_Init(struct Entity* p);
static void TopHalf_Update(struct Entity* p);
static void TopHalf_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2ShieldGuardTopRoutine = {
    [ENTITY_INIT] =      (VFXFunc)TopHalf_Init,
    [ENTITY_UPDATE] =    (VFXFunc)TopHalf_Update,
    [ENTITY_DIE] =       (VFXFunc)TopHalf_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b1ab0
static void createTopHalf(Coords32* c, bool8 right, u8 hitFromRight) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_SHIELD_GUARD_TOP);
    p->coord = *c;
    p->work[0] = right;
    p->work[1] = hitFromRight;
  }
}

// 0x080b1b04
static void TopHalf_Init(struct Entity* p) {
  bool8 right = p->work[0];
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  SetMotion(p, ANIM(25));
  UpdateEntityAnim(p);
  SET_XFLIP(p, right);
  if (right == p->work[1]) {
    p->d.x = 192, p->unk_coord.x = -8;
  } else {
    p->d.x = -96, p->unk_coord.x = 4;
  }
  if (right) p->d.x = -p->d.x, p->unk_coord.x = -p->unk_coord.x;
  p->work[2] = 23;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  TopHalf_Update(p);
}

// 0x080b1bc0
static void TopHalf_Update(struct Entity* p) {
  UpdateEntityAnim(p);
  p->coord.x += p->d.x;
  p->d.x += p->unk_coord.x;
  if (FUN_080098a4(p->coord.x, p->coord.y + PIXEL(4)) == 0) {
    p->d.y += 0x40;
    p->coord.y += p->d.y;
    if (FUN_080098a4(p->coord.x, p->coord.y + PIXEL(4)) != 0) p->work[2] = 0;
  }
  if (--p->work[2] == 0xFF) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    TopHalf_Die(p);
  }
}

// 0x080b1c70
static void TopHalf_Die(struct Entity* p) {
  bool8 right = FACING_RIGHT(p);
  u8 flip = p->work[1] | (right << 4);
  Coords32 c, d;
  s32 i;
  c.x = p->coord.x;
  c.y = p->coord.y - PIXEL(16);
  for (i = 1; i <= 3; i++) useApSheets(CreateSlashedEnemy(&c, &sGibs[i], 0, flip));
  c.x = p->coord.x + (right ? PIXEL(16) : -PIXEL(16));
  c.y = p->coord.y - PIXEL(8);
  d.x = p->coord.x + (right ? -PIXEL(16) : PIXEL(16));
  d.y = p->coord.y - PIXEL(24);
  CreateSmoke(2, &c);
  CreateSmoke(2, &d);
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sShielded[3] = {
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, METAL | HARDNESS_B3, 0, 2, 0x00000000, {-0x1200, -0xe00, 0x1000, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0xe00, 0x1a00, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xe00, 0x1a00, 0x2000}},
};

static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0xe00, 0x1a00, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xe00, 0x1a00, 0x2000}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xe00, 0x1a00, 0x2000}};

static const struct Collision sCharge[3] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {-0x1a00, -0x1000, 0x1e00, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0xe00, 0x1a00, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xe00, 0x1a00, 0x2000}},
};

static const struct Collision sMace =
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}};

// 0x0833e4ec
static const struct SlashedEnemy sShieldOff =
    {ANIM(16), {0x40, 0x10}, {-5120, -3328}, {-512, -1536}, {0, 0}, {0, 64}, {0, 0}, {0}};
static const struct SlashedEnemy sGibs[5] = {
    {ANIM(19), {0xff, 0x11}, {0, -3840}, {128, -1024}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(20), {0xfe, 0x11}, {0, -2048}, {512, -512}, {255, 127}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(21), {0xff, 0x11}, {1024, -1024}, {640, -256}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(22), {0xfe, 0x11}, {2048, -3840}, {128, -512}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(23), {0xff, 0x11}, {-1024, -2048}, {0, -512}, {0, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
