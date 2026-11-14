#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
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
  Zero 2's pyramid-shelled crab, enemy 55.
  work0:
    0: floor
    1: ceiling, drops when Zero is near
  work1:
    0: safe on spikes
    1: dies on spikes
*/

struct Crab {
  OBJECT_HDR;
  u8 shell;          // 0xB4
  u8 hops;           // 0xB5
  u8 shots;          // 0xB6
  u8 faceRight;      // 0xB7, side to face for the next hop
  u8 hardHit;        // 0xB8, shell came off to a hard (B15) hit
  u8 airborne;       // 0xB9, no snapping to the floor
  u8 flash;          // 0xBA
  u8 _bb[9];         // 0xBB
};
static_assert(sizeof(struct Crab) == sizeof(struct Enemy));

enum {
  CRAB_SHUT,
  CRAB_CEILING,
  CRAB_WATCH,
  CRAB_DROP,
  CRAB_BOUNCE,
  CRAB_OPEN,
  CRAB_CLOSE,
  CRAB_CROUCH,
  CRAB_HOP,
  CRAB_HOP_LAND,
  CRAB_SETTLE,
  CRAB_RAISE,
  CRAB_SHOOT_UP,
  CRAB_LOWER,
  CRAB_LOWERED,
  CRAB_SHOOT,
  CRAB_SHOT,
  CRAB_SHELL_OFF,
  CRAB_TURN,
  BARE_WAIT,
  BARE_CROUCH,
  BARE_HOP,
  BARE_HOP_LAND,
  BARE_SETTLE,
  BARE_SHOOT,
  BARE_TURN,
  BARE_FALL,
  CRAB_PULLED,
  CRAB_ELEMENT,
  CRAB_RECOIL,
};

// Deaths, by mode[1]
enum {
  CRAB_BURST,
  CRAB_CUT,
  CRAB_CUT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_CRAB, (n))
#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define UPSIDE_DOWN(p) ((((struct Entity*)(p))->flags & Y_FLIP) != 0)
#define SPIKE 0x11  // Zero 2's spike row (0xF), as stage import writes it

void CreateBubble(s32 x, s32 y, u8 kind);

static const struct Collision sShelled[2];
static const struct Collision sCrouched[2];
static const struct Collision sBare[2];
static const struct Collision sShellOff[2];
static const struct Collision sElement[2];
static const struct SlashedEnemy sGibs[6];
static const struct SlashedEnemy sWallGibs[3];
static const struct SlashedEnemy sHalfGibs[3];
static const struct SlashedEnemy sHalfWallGibs[3];
static const Coords32 sElementCoord = {0, -PIXEL(8)};

static u16 Crab_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Crab_Init(struct Crab* p);
static void Crab_Update(struct Crab* p);
static void Crab_Die(struct Crab* p);
static void createShellPart(struct Crab* crab, u8 kind, u8 part);

// clang-format off
const EnemyRoutine gApZ2CrabRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Crab_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Crab_Update,
    [ENTITY_DIE] =       (EnemyFunc)Crab_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void face(void* p, bool8 right) { SET_XFLIP(p, right); }
static s32 abs32(s32 v) { return v < 0 ? -v : v; }
static bool8 zeroIsRight(struct Entity* s) { return s->coord.x < (pZero2->s).coord.x; }
static bool8 zeroBehind(struct Entity* s) { return FACING_RIGHT(s) != zeroIsRight(s); }

static bool8 zeroNear(struct Entity* s) {
  return abs32((pZero2->s).coord.x - s->coord.x) <= PIXEL(104) && abs32((pZero2->s).coord.y - s->coord.y) <= PIXEL(160);
}

static bool8 solid(s32 x, s32 y) { return FUN_080098a4(x, y) != 0; }

// 0x080862f8
static bool8 inWater(s32 x, s32 y) { return GetMetatileAttr(x, y) == 0x8000 || y > gOverworld.sea; }

// 0x08086228: min..max - 1 bubbles within spread of c
static void bubbles(s32 x, s32 y, s32 spread, u8 min, u8 max) {
  u8 n;
  if (!inWater(x, y)) return;
  for (n = min + RANDOM(RNG_0202f388) % (max - min); n != 0; n--) {
    CreateBubble(x + RANDOM(RNG_0202f388) % spread - spread / 2, y + RANDOM(RNG_0202f388) % spread - spread / 2 - PIXEL(8), 0);
  }
}

// Bubbles from its back, now and then
static void idleBubbles(struct Crab* p, u8 max) {
  struct Entity* s = &p->s;
  if ((s->work[2] & 63) == 0 && (RANDOM(RNG_0202f388) & 1) == 0) bubbles(s->coord.x - PIXEL(16), s->coord.y, 0x200, 1, max);
}

static void fall(struct Entity* s) {
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

// Same as bee, 16 px above Zero's feet
static u8 aimAt(Coords32* c) {
  return CalcAngle(c->x - (pZero2->s).coord.x, c->y - ((pZero2->s).coord.y - PIXEL(16)));
}

static void shoot(Coords32* c, u8 a) {
  CreateLemon(c, 0x180, a);
  PlaySound(SE_ENEMY_SHOT);
}

// 0x0808632c
static void Crab_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Crab* p = (struct Crab*)body->parent;
  if (body->hitboxFlags & (p->shell ? BODY_STATUS_B3 : BODY_STATUS_WHITE)) (p->s).work[3] = zeroIsRight(&p->s);
}

// 0x08084370
static void Crab_Init(struct Crab* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  face(p, zeroIsRight(s));
  s->flags |= DISPLAY | FLIPABLE;
  p->shell = 1;
  s->d.x = s->d.y = 0;
  p->hardHit = 0;
  s->unk_2c = NULL;
  p->airborne = 0;
  p->flash = 0;
  INIT_BODY(p, sShelled, 10, Crab_OnCollision);
  (p->body).unk_28 = (u32)Crab_Pull;
  SetMotion(s, ANIM(0));
  if (s->work[0] == 0) {
    setMode(s, CRAB_SHUT);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  } else {
    SET_YFLIP(p, TRUE);
    setMode(s, CRAB_CEILING);
    s->coord.y = FUN_0800a134(s->coord.x, s->coord.y);
    p->airborne = 1;
  }
  UpdateEntityAnim(s);
  Crab_Update(p);
}

static void Crab_ShellOff(struct Crab* p);
static void Crab_State(struct Crab* p);

// 0x080844d4
// 0x08086368
static u16 Crab_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  if (s->mode[1] != CRAB_PULLED) setMode(s, CRAB_PULLED);
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  setMode(s, s->unk_2c != NULL ? CRAB_ELEMENT : BARE_FALL);
  return 0;
}

static void Crab_Update(struct Crab* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != CRAB_RECOIL) setMode(s, CRAB_RECOIL);
  if (s->mode[1] == CRAB_RECOIL) {
    if (ApRecoilFly((Object*)p)) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      EXIT_BODY(p);
      Crab_Die(p);
    }
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 kind = CRAB_BURST;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? CRAB_CUT_HARD : CRAB_CUT;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    Crab_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (p->shell) {
      if (solid(s->coord.x, s->coord.y)) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      if (status & BODY_STATUS_WHITE) {
        if (status & BODY_STATUS_B15) p->hardHit = 1;
        setMode(s, CRAB_SHELL_OFF);
        p->shell = 0;
        Crab_ShellOff(p);
      }
      return;
    }
    if (solid(s->coord.x, s->coord.y)) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y - PIXEL(4));
    if (p->flash != 0) {
      if (--p->flash != 0) return;
    } else if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
    } else {
      return;
    }
    SetDDP(&p->body, sBare);
    return;
  }

  if (p->shell) {
    if (status & BODY_STATUS_WHITE) {
      if (status & BODY_STATUS_B15) p->hardHit = 1;
      setMode(s, CRAB_SHELL_OFF);
      p->shell = 0;
    }
  } else if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    if (inWater(s->coord.x, s->coord.y) && (p->body).elemented == ELEMENT_FLAME) {
      bubbles(s->coord.x, s->coord.y - PIXEL(8), 0x1C00, 10, 12);  // fire under water is steam
    } else {
      s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
      if (s->unk_2c != NULL) setMode(s, CRAB_ELEMENT);
    }
  }

  if (s->work[1] != 0 && GetMetatileAttr(s->coord.x, s->coord.y + 0x80) == SPIKE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Crab_Die(p);
    return;
  }
  if (!p->airborne) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y - PIXEL(4));
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  Crab_State(p);
}

// --------------------------------------------
// In its shell

static bool8 enter(struct Entity* s, u8 anim) {
  if (s->mode[2] != 0) return FALSE;
  SetMotion(s, ANIM(anim));
  s->mode[2]++;
  return TRUE;
}

static bool8 animEnded(struct Entity* s) { return s->motion.state == ANIM_END; }

// 0x08084728 / 0x080847f4
static void Crab_Shut(struct Crab* p) {
  struct Entity* s = &p->s;
  if (enter(s, 0)) {
    SetDDP(&p->body, sShelled);
    p->airborne = s->mode[1] == CRAB_CEILING;
    if (p->airborne) SET_YFLIP(p, TRUE);
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  if (s->mode[1] == CRAB_SHUT) idleBubbles(p, 2);
  if (zeroNear(s)) setMode(s, s->mode[1] == CRAB_SHUT ? CRAB_OPEN : CRAB_DROP);
}

// 0x08084888: hops at Zero three times while he is near
static void Crab_Watch(struct Crab* p) {
  struct Entity* s = &p->s;
  if (enter(s, 3)) {
    SetDDP(&p->body, sCrouched);
    s->work[2] = 32;
    p->airborne = 0;
  }
  UpdateEntityAnim(s);
  idleBubbles(p, 2);
  if (--s->work[2] != 0) return;
  if (zeroNear(s)) {
    setMode(s, CRAB_CROUCH);
    p->faceRight = zeroIsRight(s);
    p->hops = 3;
  } else {
    setMode(s, CRAB_CLOSE);
  }
}

// 0x08084980 (ceiling crab lets go) and 0x08084a68 (bounces where it lands)
static void Crab_Drop(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->mode[1] == CRAB_DROP) {
      if (inWater(s->coord.x, s->coord.y)) {
        s32 n;
        for (n = (RANDOM(RNG_0202f388) & 3) + 2; n != 0; n--) {
          CreateBubble(s->coord.x + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1), s->coord.y, 0);
        }
      }
      s->d.y = 0;
    } else {
      SET_YFLIP(p, FALSE);
      s->d.y = -0x300;
    }
    SetMotion(s, ANIM(0));
    p->airborne = 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  fall(s);
  if (solid(s->coord.x, s->coord.y)) {
    if (s->mode[1] == CRAB_BOUNCE) PlaySound(SE_Z2_CRAB_LAND);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(s, s->mode[1] == CRAB_DROP ? CRAB_BOUNCE : CRAB_OPEN);
  }
}

// 0x08084af8, 0x08084b9c
static void Crab_OpenClose(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->mode[1] == CRAB_OPEN) {
      bubbles(s->coord.x, s->coord.y, 0x1800, 4, 6);
      face(p, zeroIsRight(s));
    }
    SetMotion(s, ANIM(s->mode[1] == CRAB_OPEN ? 1 : 2));
    SetDDP(&p->body, sShelled);
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, s->mode[1] == CRAB_OPEN ? CRAB_WATCH : CRAB_SHUT);
}

// 0x08084be8
static void Crab_Crouch(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    face(p, p->faceRight);
    SetMotion(s, ANIM(s->mode[1] == CRAB_CROUCH ? 4 : 15));
    SetDDP(&p->body, s->mode[1] == CRAB_CROUCH ? sCrouched : sBare);
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, s->mode[1] == CRAB_CROUCH ? CRAB_HOP : BARE_HOP);
}

// 0x08084c6c (at Zero) and 0x080856a4 (bare, away from him)
static void Crab_Hop(struct Crab* p) {
  struct Entity* s = &p->s;
  bool8 bare = s->mode[1] == BARE_HOP;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(bare ? 16 : 5));
    if (bare) {
      s->d.x = FACING_RIGHT(p) ? -0x300 : 0x300;
      s->d.y = -0x500;
    } else {
      s->d.x = FACING_RIGHT(p) ? PIXEL(1) : -PIXEL(1);
      s->d.y = -0x280;
    }
    p->airborne = 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  if (solid(s->coord.x, s->coord.y - (bare ? 0 : PIXEL(8)))) {
    s32 y = s->coord.y - (bare ? 0 : PIXEL(8));
    s->coord.x = s->d.x < 0 ? FUN_0800a31c(s->coord.x, y) : FUN_0800a22c(s->coord.x, y);
    if (bare) s->d.x = FACING_RIGHT(p) ? -0x100 : 0x100;
  }
  fall(s);
  if (s->d.y <= 0) {
    if (solid(s->coord.x, s->coord.y - PIXEL(8))) {
      s->coord.y = FUN_0800a134(s->coord.x, s->coord.y) + PIXEL(8);
      s->d.y = 0;
    }
  } else if (solid(s->coord.x, s->coord.y)) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(s, bare ? BARE_HOP_LAND : CRAB_HOP_LAND);
  }
}

// 0x08084d60 / 0x080857a0
static void Crab_HopLand(struct Crab* p) {
  struct Entity* s = &p->s;
  bool8 bare = s->mode[1] == BARE_HOP_LAND;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_CRAB_LAND);
    if (RANDOM(RNG_0202f388) & 1) bubbles(s->coord.x, s->coord.y, 0x1000, 1, bare ? 3 : 2);
    SetMotion(s, ANIM(bare ? 17 : 6));
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  if (bare && abs32(gStageRun.vm.camera.viewport.x - s->coord.x) > PIXEL(104)) {
    setMode(s, BARE_SETTLE);
  } else if (p->hops == 0 || --p->hops == 0) {
    setMode(s, bare ? BARE_SETTLE : CRAB_SETTLE);
  } else {
    setMode(s, bare ? BARE_CROUCH : CRAB_CROUCH);
  }
}

// 0x08084df8: turns first if Zero is behind
static void Crab_Settle(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    s->work[2] = 8;
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  setMode(s, zeroBehind(s) ? CRAB_TURN : CRAB_SHOOT);
  p->shots = 3;
}

// 0x08084e6c, 0x08084fa0, 0x08084fe4
static void Crab_Raise(struct Crab* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case CRAB_RAISE:
      if (s->mode[2] == 0) bubbles(s->coord.x, s->coord.y, 0x1800, 4, 6);
      enter(s, 7);
      UpdateEntityAnim(s);
      if (animEnded(s)) setMode(s, CRAB_SHOOT_UP);
      break;
    case CRAB_LOWER:
      if (enter(s, 8)) s->work[2] = 8;
      UpdateEntityAnim(s);
      if (--s->work[2] == 0) setMode(s, CRAB_LOWERED);
      break;
    default:
      enter(s, 10);
      UpdateEntityAnim(s);
      if (animEnded(s)) setMode(s, p->shots == 0 ? CRAB_WATCH : CRAB_SHOOT);
      break;
  }
  p->airborne = 0;
}

// 0x08084ebc
static void Crab_ShootUp(struct Crab* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (enter(s, 9)) {
    s->work[2] = 24;
    p->airborne = 0;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(10);
  shoot(&c, aimAt(&c));
  if (p->shots != 0 && --p->shots != 0 && (RANDOM(RNG_0202f388) & 1)) {
    setMode(s, CRAB_SHOOT_UP);
  } else {
    setMode(s, CRAB_LOWER);
  }
}

// 0x08085034
static void Crab_Shoot(struct Crab* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  u8 a;
  if (enter(s, 12)) {
    s->work[2] = 16;
    p->airborne = 0;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  c.x = s->coord.x + (FACING_RIGHT(p) ? PIXEL(14) : -PIXEL(14));
  c.y = s->coord.y;
  a = aimAt(&c);
  if (!FACING_RIGHT(p)) {
    if (a > 16 && a < 128) a = 16;
    if (a >= 128 && a < 240) a = 240;
  } else {
    if (a < 112) a = 112;
    if (a > 144) a = 144;
  }
  shoot(&c, a);
  setMode(s, CRAB_SHOT);
}

// 0x0808511c
static void Crab_Shot(struct Crab* p) {
  struct Entity* s = &p->s;
  if (enter(s, 11)) s->work[2] = 8;
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (p->shots == 0 || --p->shots == 0) {
    setMode(s, CRAB_WATCH);
  } else {
    setMode(s, (RANDOM(RNG_0202f388) & 1) ? CRAB_RAISE : CRAB_SHOOT);
  }
}

// 0x080854a0, 0x08085998
static void Crab_Turn(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    face(p, !FACING_RIGHT(p));
    SetMotion(s, ANIM(s->mode[1] == CRAB_TURN ? 3 : 13));
    s->work[2] = 8;
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) setMode(s, s->mode[1] == CRAB_TURN ? CRAB_SHOOT : BARE_SHOOT);
}

// 0x080851ac
static void Crab_ShellOff(struct Crab* p) {
  struct Entity* s = &p->s;
  bool8 upsideDown = UPSIDE_DOWN(p);
  if (s->mode[2] == 0) {
    bubbles(s->coord.x, s->coord.y, 0x1800, 6, 8);
    SetDDP(&p->body, sShellOff);
    createShellPart(p, p->hardHit, 0);
    createShellPart(p, p->hardHit, 1);
    SetMotion(s, ANIM(13));
    face(p, zeroIsRight(s));
    s->d.x = (1 - 2 * s->work[3]) * 0x180;
    s->d.y = 0;
    if (solid(s->coord.x, s->coord.y + PIXEL(2))) {
      SET_YFLIP(p, FALSE);
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->d.y = -0x280;
    }
    p->flash = 32;
    p->airborne = 1;
    s->mode[2]++;
    if (IsFrozen(p)) {
      UpdateEntityAnim(s);
      return;
    }
  }
  UpdateEntityAnim(s);
  if (p->flash != 0) p->flash--;
  if (s->mode[2] == 1) {
    s32 head = s->coord.y - (upsideDown ? 0 : PIXEL(8));
    s->coord.x += s->d.x;
    if (solid(s->coord.x, head)) s->coord.x = s->d.x < 0 ? FUN_0800a31c(s->coord.x, head) : FUN_0800a22c(s->coord.x, head);
    s->coord.y += s->d.y;
    if (s->d.y > 0 && solid(s->coord.x, s->coord.y + (upsideDown ? PIXEL(8) : 0))) {
      SET_YFLIP(p, FALSE);
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      p->airborne = 0;
      s->d.x = FACING_RIGHT(p) ? -32 : 32;
      s->d.y = 0;
      s->mode[2]++;
    } else {
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
    }
    return;
  }
  if (s->d.x != 0) {
    s->coord.x += s->d.x;
    if (solid(s->coord.x, s->coord.y - PIXEL(8))) {
      s->coord.x = s->d.x < 0 ? FUN_0800a31c(s->coord.x, s->coord.y - PIXEL(8)) : FUN_0800a22c(s->coord.x, s->coord.y - PIXEL(8));
      s->d.x = 0;
    }
  }
  if (p->flash == 0) {
    SetDDP(&p->body, sBare);
    setMode(s, BARE_CROUCH);
    p->hops = 3;
    p->faceRight = zeroIsRight(s);
  }
}

// --------------------------------------------
// Bare

// 0x08085518
static void Bare_Wait(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SET_YFLIP(p, FALSE);
    SetMotion(s, ANIM(13));
    SetDDP(&p->body, sBare);
    s->work[2] = 32;
    p->airborne = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  idleBubbles(p, 2);
  if (--s->work[2] != 0) return;
  if (zeroNear(s)) {
    setMode(s, BARE_CROUCH);
    p->faceRight = zeroIsRight(s);
    p->hops = 3;
  } else {
    setMode(s, BARE_WAIT);
  }
}

// 0x08085858
static void Bare_Settle(struct Crab* p) {
  struct Entity* s = &p->s;
  if (enter(s, 14)) {
    s->work[2] = 8;
    p->airborne = 0;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) {
    setMode(s, BARE_WAIT);
  } else {
    setMode(s, zeroBehind(s) ? BARE_TURN : BARE_SHOOT);
  }
}

// 0x080858e4
static void Bare_Shoot(struct Crab* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (enter(s, 28)) {
    s->work[2] = 0;
    p->airborne = 0;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  if (s->work[2] == 16 || s->work[2] == 32 || s->work[2] == 48) {
    c.x = s->coord.x;
    c.y = s->coord.y - PIXEL(10);
    shoot(&c, aimAt(&c));
  } else if (s->work[2] == 64) {
    setMode(s, BARE_WAIT);
  }
}

// 0x08085a10
static void Bare_Fall(struct Crab* p) {
  struct Entity* s = &p->s;
  if (enter(s, 14)) {
    SetDDP(&p->body, sBare);
    s->d.y = 0;
    p->airborne = 1;
  }
  UpdateEntityAnim(s);
  fall(s);
  if (solid(s->coord.x, s->coord.y)) {
    PlaySound(SE_Z2_CRAB_LAND);
    SET_YFLIP(p, FALSE);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(s, BARE_WAIT);
  }
}

// 0x08085ba0: burning or frozen, drops and waits
static void Crab_Element(struct Crab* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sElement);
    s->d.y = 0;
    p->airborne = 1;
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    fall(s);
    if (solid(s->coord.x, s->coord.y)) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      p->airborne = 0;
      s->mode[2]++;
    }
  }
  if (s->unk_2c == NULL) setMode(s, s->mode[2] == 2 ? BARE_WAIT : BARE_FALL);
}

static void Crab_State(struct Crab* p) {
  switch ((p->s).mode[1]) {
    case CRAB_SHUT:
    case CRAB_CEILING: Crab_Shut(p); break;
    case CRAB_WATCH: Crab_Watch(p); break;
    case CRAB_DROP:
    case CRAB_BOUNCE: Crab_Drop(p); break;
    case CRAB_OPEN:
    case CRAB_CLOSE: Crab_OpenClose(p); break;
    case CRAB_CROUCH:
    case BARE_CROUCH: Crab_Crouch(p); break;
    case CRAB_HOP:
    case BARE_HOP: Crab_Hop(p); break;
    case CRAB_HOP_LAND:
    case BARE_HOP_LAND: Crab_HopLand(p); break;
    case CRAB_SETTLE: Crab_Settle(p); break;
    case CRAB_RAISE:
    case CRAB_LOWER:
    case CRAB_LOWERED: Crab_Raise(p); break;
    case CRAB_SHOOT_UP: Crab_ShootUp(p); break;
    case CRAB_SHOOT: Crab_Shoot(p); break;
    case CRAB_SHOT: Crab_Shot(p); break;
    case CRAB_SHELL_OFF: Crab_ShellOff(p); break;
    case CRAB_TURN:
    case BARE_TURN: Crab_Turn(p); break;
    case BARE_WAIT: Bare_Wait(p); break;
    case BARE_SETTLE: Bare_Settle(p); break;
    case BARE_SHOOT: Bare_Shoot(p); break;
    case BARE_FALL: Bare_Fall(p); break;
    case CRAB_PULLED:
      if ((p->s).mode[2] == 0) {
        SetMotion(&p->s, ANIM(13));
        p->airborne = TRUE;
        (p->s).mode[2]++;
      }
      UpdateEntityAnim(&p->s);
      break;
    case CRAB_ELEMENT: Crab_Element(p); break;
  }
}

// --------------------------------------------
// Deaths

static void countKill(struct Crab* p) {
  struct Entity* s = &p->s;
  TryDropItem(1, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  ApImportCrabKilled();
}

static void burstSound(struct Entity* s) {
  if (inWater(s->coord.x, s->coord.y - PIXEL(20))) {
    PlaySound(49);
    bubbles(s->coord.x, s->coord.y - PIXEL(8), 0x1000, 6, 8);
  } else {
    PlaySound(SE_ZAKO_EXPLODE);
  }
}

static void smokes(struct Entity* s, s32 spread, bool8 two) {
  Coords32 c;
  c.x = s->coord.x + ((RANDOM(RNG_0202f388) % spread) - spread / 2) * PIXEL(1);
  c.y = s->coord.y + ((RANDOM(RNG_0202f388) % spread) - spread / 2) * PIXEL(1);
  CreateSmoke(1, &c);
  if (!two) return;
  c.x = s->coord.x + ((RANDOM(RNG_0202f388) % spread) - spread / 2) * PIXEL(1);
  c.y = s->coord.y + ((RANDOM(RNG_0202f388) % spread) - spread / 2) * PIXEL(1);
  CreateSmoke(2, &c);
}

static void gib(struct Entity* s, const struct SlashedEnemy* g, u8 flags) {
  Coords32 c;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(20);
  useApSheets(CreateSlashedEnemy(&c, g, 0, flags));
}

// 0x0808604c, 0x08086134
static void cutBurst(struct Crab* p, bool8 atWall) {
  struct Entity* s = &p->s;
  u8 flags = FACING_RIGHT(p) << 4 | (atWall ? s->d.x >= 0 : s->work[3]);
  burstSound(s);
  if (atWall) {
    gib(s, &sWallGibs[0], flags);
    gib(s, &sWallGibs[1], flags);
    gib(s, &sWallGibs[2], flags);
  } else {
    gib(s, &sGibs[1], flags);
    gib(s, &sGibs[2], flags);
    gib(s, &sGibs[4], flags);
  }
  smokes(s, 7, FALSE);
  countKill(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void Crab_Die(struct Crab* p) {
  struct Entity* s = &p->s;
  bool8 hard = s->mode[1] == CRAB_CUT_HARD;
  s32 i;
  if (s->mode[1] == CRAB_BURST) {  // 0x08085c30
    burstSound(s);
    for (i = 0; i < 6; i++) gib(s, &sGibs[i], FACING_RIGHT(p) << 4 | s->work[3]);
    smokes(s, 16, TRUE);
    countKill(p);
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  // 0x08085d8c, 0x08085ec8: one half slides or falls apart, other goes the other way
  if (s->mode[2] == 0) {
    s32 side = 2 * FACING_RIGHT(p) - 1;
    SetMotion(s, ANIM(18));
    if (solid(s->coord.x, s->coord.y + PIXEL(2))) {
      s->mode[2] = 1;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->d.x = side * (hard ? 0x400 : 0x40);
      s->unk_coord.x = -side * (hard ? 0x40 : 4);
    } else {
      s->mode[2] = 2;
      if (hard) {
        s->d.x = side * 0x100;
        s->d.y = UPSIDE_DOWN(p) ? 0 : 0x80;
      } else {
        s->d.y = UPSIDE_DOWN(p) ? 0 : 0x100;
      }
    }
    createShellPart(p, hard ? 3 : 2, 0);
  }
  UpdateEntityAnim(s);
  if (s->mode[2] == 1) {
    s->coord.x += s->d.x;
    s->d.x += s->unk_coord.x;
    if (s->d.x == 0) {
      cutBurst(p, FALSE);
      return;
    }
    if (hard && solid(s->coord.x, s->coord.y)) {
      s->coord.x = s->d.x < 0 ? FUN_0800a31c(s->coord.x, s->coord.y) : FUN_0800a22c(s->coord.x, s->coord.y);
      cutBurst(p, TRUE);
      return;
    }
    if (!solid(s->coord.x, s->coord.y + PIXEL(hard ? 2 : 8))) {
      s->mode[2] = 2;
      s->d.y = 0x80;
    }
    return;
  }
  if (hard) s->coord.x += s->d.x;
  fall(s);
  if (solid(s->coord.x, s->coord.y)) cutBurst(p, FALSE);
}

// --------------------------------------------
// Shell halves and cut crab's other half, Zero 2's VFX 53

static void Part_Init(struct VFX* p);
static void Part_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2CrabPartRoutine = {
    [ENTITY_INIT] =      Part_Init,
    [ENTITY_UPDATE] =    Part_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080babac: work0 is the kind, work1 the half, work3 bit 0 facing and bit 1 Y_FLIP
static void createShellPart(struct Crab* crab, u8 kind, u8 part) {
  struct Entity* s = AllocEntityLast(gVFXHeaderPtr);
  if (s != NULL) {
    INIT_VFX_ROUTINE(s, VFX_Z2_CRAB_PART);
    s->coord = (crab->s).coord;
    s->work[0] = kind;
    s->work[1] = part;
    s->work[3] = FACING_RIGHT(crab) | UPSIDE_DOWN(crab) << 1;
  }
}

// 0x080bac0c
static void Part_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3] & 1;
  bool8 upsideDown = (s->work[3] >> 1) & 1;
  s32 side = 2 * right - 1;
  InitNonAffineMotion(s);
  useApSheets(p);
  face(p, right);
  SET_YFLIP(p, upsideDown);
  s->flags |= DISPLAY | FLIPABLE;
  s->mode[1] = 0;
  switch (s->work[0]) {
    case 0:
    case 1:
      SetMotion(s, ANIM(s->work[1] ? 27 : 26));
      s->d.x = (s->work[1] ? -side : side) * (s->work[0] ? 0x1C0 : 0x40);
      s->d.y = upsideDown ? 0 : (s->work[0] ? -0x500 : -0x300);
      s->work[2] = s->work[0] ? 90 : 60;
      break;
    default:
      SetMotion(s, ANIM(19));
      if (solid(s->coord.x, s->coord.y + PIXEL(2))) {
        s->d.x = -side * (s->work[0] == 3 ? 0x400 : 0x60);
        s->unk_coord.x = side * (s->work[0] == 3 ? 0x40 : 4);
      } else {
        s->mode[1] = 1;
        s->d.x = -side * (s->work[0] == 3 ? 0x100 : 0x40);
        s->d.y = upsideDown ? 0 : (s->work[0] == 3 ? 0x380 : 0x100);
      }
      s->work[2] = 64;
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

static void partBurst(struct VFX* p, bool8 atWall) {
  struct Entity* s = &p->s;
  const struct SlashedEnemy* g = atWall ? sHalfWallGibs : sHalfGibs;
  s32 i;
  u8 flags = FACING_RIGHT(p) << 4 | 1;
  for (i = 0; i < 3; i++) gib(s, &g[i], flags);
  smokes(s, 7, FALSE);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080bae94, 0x080baf8c, 0x080baff8, 0x080bb0bc
static void Part_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if (s->work[2] == 0) {
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  s->work[2]--;
  if (s->work[0] <= 1) {
    // Shell half blinks out
    bool8 shown = s->work[0] == 1 || s->work[2] > 29 || (s->work[2] > 14 ? (s->work[2] & 3) != 0 : (s->work[2] & 1) != 0);
    if (shown) {
      s->flags |= DISPLAY;
    } else {
      s->flags &= ~DISPLAY;
    }
  }
  UpdateEntityAnim(s);
  if (s->work[0] == 0 && s->mode[1] == 0) {
    s->coord.x += s->d.x;
    if (solid(s->coord.x, s->coord.y)) s->d.x = 0;
    s->coord.y += s->d.y;
    s->d.y += 0x40;
    if (s->d.y > 0x700) s->d.y = 0x700;
    if (s->d.y < 0) {
      if (solid(s->coord.x, s->coord.y)) s->d.y = 0;
    } else if (s->d.y > 0 && solid(s->coord.x, s->coord.y)) {
      s->d.y = -0x200;
      s->mode[1]++;
    }
    return;
  }
  if (s->work[0] >= 2 && s->mode[1] == 0) {
    s->coord.x += s->d.x;
    s->d.x += s->unk_coord.x;
    if (s->d.x == 0) {
      partBurst(p, FALSE);
      return;
    }
    if (s->work[0] == 3 && solid(s->coord.x, s->coord.y)) {
      s->coord.x = s->d.x < 0 ? FUN_0800a31c(s->coord.x, s->coord.y) : FUN_0800a22c(s->coord.x, s->coord.y);
      partBurst(p, TRUE);
      return;
    }
    if (!solid(s->coord.x, s->coord.y + PIXEL(8))) {
      s->mode[1]++;
      s->d.y = 0x80;
    }
    return;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (s->work[0] >= 2 && solid(s->coord.x, s->coord.y)) partBurst(p, FALSE);
}

// -------------------------------------------
// clang-format off
// Shell is a priority layer, most hits do no damage
static const struct Collision sShelled[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x01, 0x02, 0, 1, 0x00000001, {0x0, -0xa00, 0x1200, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0x02, 0, 0, 0x80ff041f, {0x0, -0xa00, 0x1200, 0x1400}},
};

static const struct Collision sCrouched[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x01, 0x02, 0, 1, 0x00000001, {0x0, -0xc00, 0xc00, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0x02, 0, 0, 0x80ff041f, {0x0, -0xc00, 0xc00, 0x1800}},
};

static const struct Collision sBare[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0x900, 0x1600, 0x1200}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x900, 0x1000, 0x1200}},
};

static const struct Collision sShellOff[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x900, 0x1600, 0x1200}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sElement[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x900, 0x1000, 0x1200}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x900, 0x1000, 0x1200}},
};

// 0x083413c0
static const struct SlashedEnemy sGibs[6] = {
    {MOTION(AP_SHEET_Z2_CRAB, 20), {0xff, 0x11}, {0, 0}, {256, -960}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 21), {0xff, 0x11}, {0, 0}, {-128, -1152}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 22), {0xff, 0x11}, {0, 0}, {-128, -832}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 23), {0xff, 0x11}, {0, 0}, {256, -1024}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 24), {0xff, 0x11}, {0, 0}, {128, -1152}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 25), {0xff, 0x11}, {0, 0}, {-128, -1280}, {127, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x08341468
static const struct SlashedEnemy sWallGibs[3] = {
    {MOTION(AP_SHEET_Z2_CRAB, 21), {0xff, 0x11}, {0, 0}, {128, -1664}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 22), {0xff, 0x11}, {0, 0}, {128, -1408}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 24), {0xff, 0x11}, {0, 0}, {112, -1536}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
};

// 0x083471f8
static const struct SlashedEnemy sHalfGibs[3] = {
    {MOTION(AP_SHEET_Z2_CRAB, 20), {0xff, 0x11}, {0, 0}, {256, -960}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 23), {0xff, 0x11}, {0, 0}, {256, -1024}, {31, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 25), {0xff, 0x11}, {0, 0}, {-128, -1280}, {127, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x0834724c
static const struct SlashedEnemy sHalfWallGibs[3] = {
    {MOTION(AP_SHEET_Z2_CRAB, 20), {0xff, 0x11}, {0, 0}, {128, -1536}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 23), {0xff, 0x11}, {0, 0}, {128, -1664}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
    {MOTION(AP_SHEET_Z2_CRAB, 25), {0xff, 0x11}, {0, 0}, {64, -1408}, {31, 255}, {0, 64}, {0x0, 0x0}, {0}},
};
// clang-format on

#endif  // AP
