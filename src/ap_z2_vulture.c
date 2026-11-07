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
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's robot vultures, enemy 48.
  work0:
    0: perch with one vulture, on the side work1 says
    1: perch with two vultures
    2: vulture, made by its perch
  Init then sets work0 to PERCH or VULTURE.
*/

struct Perch {
  OBJECT_HDR;
  struct Entity* vultures[2];    // 0xB4
  u32 _bc;                       // 0xBC
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Perch) == sizeof(struct Enemy));

struct Vulture {
  OBJECT_HDR;
  u8 alarm;                      // 0xB4, bit 0: perch gone, bit 1: startled
  u8 coll;                       // 0xB5
  u8 angle;                      // 0xB6, position in loop
  u8 high;                       // 0xB7, turn timer, then dive depth
  s32 homeX;                     // 0xB8
  s32 homeY;                     // 0xBC
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Vulture) == sizeof(struct Enemy));

#define ALARM_PERCH_GONE 1
#define ALARM_STARTLED 2

enum {
  PERCH,
  VULTURE,
};

enum {
  VULTURE_PERCHED,
  VULTURE_TAKE_OFF,
  VULTURE_LOOP,
  VULTURE_RETURN,
  VULTURE_LANDED,
  VULTURE_DIVE,
  VULTURE_KNOCKED,
  VULTURE_LANDING,
  VULTURE_PREEN,
  VULTURE_LEAVE,
  VULTURE_PULLED,
  VULTURE_ELEMENT,
  VULTURE_RECOIL,
};

// Deaths, by mode[1]
enum {
  VULTURE_BURST,
  VULTURE_CUT,
  VULTURE_CUT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_VULTURE, (n))
#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

static const struct Collision sVulture[3][2];
static const struct Collision sHarmless[3][2];
static const struct Collision sPerch[2];
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sHardGibs[2];
static const struct SlashedEnemy sHalfGibs[2];
static const Coords32 sElementCoord = {0, -PIXEL(12)};

static u16 Vulture_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Vulture_Init(struct Vulture* p);
static void Vulture_Update(struct Vulture* p);
static void Vulture_Die(struct Vulture* p);
static void Vulture_Disappear(struct Perch* p);
static void createHalf(struct Vulture* vulture, u8 kind);

// clang-format off
const EnemyRoutine gApZ2VultureRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Vulture_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Vulture_Update,
    [ENTITY_DIE] =       (EnemyFunc)Vulture_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)Vulture_Disappear,
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
static bool8 zeroNear(struct Entity* s) { return abs32((pZero2->s).coord.x - s->coord.x) <= PIXEL(96); }
static bool8 gone(struct Entity* s) { return s == NULL || s->mode[0] > ENTITY_UPDATE; }

static void disappear(struct Entity* s) {
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(s);
  SET_ENEMY_ROUTINE(s, ENTITY_DISAPPEAR);
}

// 0x080801dc
static void setColl(struct Vulture* p, u8 n) {
  SetDDP(&p->body, sVulture[n]);
  p->coll = n;
}

// 0x08080205
static void Vulture_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* s = body->parent;
    s->work[3] = s->coord.x < (pZero2->s).coord.x;
  }
}

// 0x0807e910
static struct Entity* createVulture(struct Perch* perch, s32 x, s32 y, u8 side) {
  struct Entity* s = AllocEntityLast(gEnemyHeaderPtr);
  if (s != NULL) {
    INIT_ENEMY_ROUTINE(s, ENEMY_Z2_VULTURE);
    s->unk_28 = &perch->s;
    s->coord.x = x;
    s->coord.y = y;
    s->work[0] = 2;
    s->work[1] = side;
  }
  return s;
}

// 0x0807e978
static void Vulture_Init(struct Vulture* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, 0);
  InitNonAffineMotion(s);
  useApSheets(p);
  if (s->work[0] != 2) {
    struct Perch* perch = (struct Perch*)p;
    s32 floor;
    face(p, FALSE);
    SetMotion(s, ANIM(17));
    INIT_BODY(p, sPerch, 3, NULL);
    floor = FUN_08009f6c(s->coord.x, s->coord.y);
    s->coord.y = floor;
    if (s->work[0] == 0) {
      perch->vultures[0] = createVulture(perch, s->coord.x + s->work[1] * PIXEL(32) - PIXEL(16), floor, s->work[1]);
      perch->vultures[1] = NULL;
    } else {
      perch->vultures[0] = createVulture(perch, s->coord.x - PIXEL(16), floor, 0);
      perch->vultures[1] = createVulture(perch, s->coord.x + PIXEL(16), floor, 1);
      if (perch->vultures[0] != NULL) {
        perch->vultures[0]->unk_2c = perch->vultures[1];
        if (perch->vultures[1] != NULL) perch->vultures[1]->unk_2c = perch->vultures[0];
      }
    }
    s->work[0] = PERCH;
    perch->elementEffect = NULL;
  } else {
    s->work[0] = VULTURE;
    face(p, !s->work[1]);
    SetMotion(s, ANIM(8));
    p->coll = 0;
    INIT_BODY(p, sVulture[0], 4, Vulture_OnCollision);
    (p->body).unk_28 = (u32)Vulture_Pull;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    p->homeX = s->coord.x;
    p->homeY = s->coord.y;
    p->alarm = 0;
    p->elementEffect = NULL;
  }
  s->flags |= DISPLAY | FLIPABLE;
  UpdateEntityAnim(s);
  Vulture_Update(p);
}

// --------------------------------------------
// Perch

static void Perch_Update(struct Perch* p);
static void Perch_Die(struct Perch* p);

// 0x0807ed54
static void Perch_Update(struct Perch* p) {
  struct Entity* s = &p->s;
  bool8 preening;
  s32 i;
  for (i = 0; i < 2; i++) {
    if (p->vultures[i] != NULL && gone(p->vultures[i])) p->vultures[i] = NULL;
  }
  if ((p->body).status & BODY_STATUS_DEAD) {
    for (i = 0; i < 2; i++) {
      if (p->vultures[i] != NULL) ((struct Vulture*)p->vultures[i])->alarm |= ALARM_STARTLED;
    }
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Perch_Die(p);
    return;
  }
  if (IsFrozen(p)) {
    p->elementEffect = NULL;
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) {
    if (p->elementEffect == NULL) p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
  }
  if (p->elementEffect != NULL && IsDead(p->elementEffect)) p->elementEffect = NULL;

  preening = FALSE;
  for (i = 0; i < 2; i++) {
    if (p->vultures[i] != NULL && p->vultures[i]->mode[1] == VULTURE_PREEN) preening = TRUE;
  }
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(s->mode[1] == 0 ? 17 : 18));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 0 && preening) {
    setMode(s, 1);
  } else if (s->mode[1] == 1 && !preening) {
    setMode(s, 0);
  }
}

// 0x0807ebcc
static void Perch_Die(struct Perch* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  PlaySound(SE_ZAKO_EXPLODE);
  c.x = s->coord.x + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1);
  c.y = s->coord.y - PIXEL(12) + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1);
  CreateSmoke(1, &c);
  c.x = s->coord.x + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1);
  c.y = s->coord.y - PIXEL(12) + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1);
  CreateSmoke(2, &c);
  TryDropItem(0, (struct Coord*)&s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0807ed0c: perch gone, vultures leave
static void Vulture_Disappear(struct Perch* p) {
  s32 i;
  if ((p->s).work[0] == PERCH) {
    for (i = 0; i < 2; i++) {
      if (p->vultures[i] != NULL && !gone(p->vultures[i])) ((struct Vulture*)p->vultures[i])->alarm |= ALARM_PERCH_GONE;
    }
  }
  DeleteEnemy((struct Entity*)p);
}

// --------------------------------------------
// Vulture

static void Vulture_Perched(struct Vulture* p);
static void Vulture_TakeOff(struct Vulture* p);
static void Vulture_Loop(struct Vulture* p);
static void Vulture_Return(struct Vulture* p);
static void Vulture_Landed(struct Vulture* p);
static void Vulture_Dive(struct Vulture* p);
static void Vulture_Knocked(struct Vulture* p);
static void Vulture_Landing(struct Vulture* p);
static void Vulture_Preen(struct Vulture* p);
static void Vulture_Leave(struct Vulture* p);
static void Vulture_Element(struct Vulture* p);

static void startle(struct Entity* partner) {
  if (partner != NULL) ((struct Vulture*)partner)->alarm |= ALARM_STARTLED;
}

// 0x0807ef30
// 0x0807f9f0
static void Vulture_Pulled(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    face(p, !s->work[1]);
    SetMotion(s, ANIM(9));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
}

// 0x08080230
static u16 Vulture_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  if (s->mode[1] != VULTURE_PULLED) {
    s->mode[1] = VULTURE_PULLED;
    s->mode[2] = 0;
  }
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  s->mode[1] = VULTURE_TAKE_OFF;
  s->mode[2] = 0;
  return 0;
}

static void Vulture_Update(struct Vulture* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  u8 mode;

  if (s->work[0] == PERCH) {
    Perch_Update((struct Perch*)p);
    return;
  }

  if (ApRecoilHit((Object*)p) && s->mode[1] != VULTURE_RECOIL) setMode(s, VULTURE_RECOIL);
  if (s->mode[1] == VULTURE_RECOIL) {
    if (ApRecoilFly((Object*)p)) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      setMode(s, VULTURE_BURST);
      EXIT_BODY(p);
      Vulture_Die(p);
    }
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 kind = VULTURE_BURST;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? VULTURE_CUT_HARD : VULTURE_CUT;
    mode = s->mode[1];
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[3] = mode;
    s->mode[1] = kind;
    EXIT_BODY(p);
    Vulture_Die(p);
    return;
  }

  if (s->unk_2c != NULL && gone(s->unk_2c)) s->unk_2c = NULL;
  p->alarm &= ALARM_PERCH_GONE;
  if (p->alarm) {
    mode = s->mode[1];
    if (mode == VULTURE_PERCHED || mode == VULTURE_LOOP || mode == VULTURE_LANDING || mode == VULTURE_PREEN) setMode(s, VULTURE_LEAVE);
  }
  if (s->unk_28 != NULL) {
    if (gone(s->unk_28)) s->unk_28 = NULL;
  } else {
    if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x4FFF) {
      disappear(s);
      return;
    }
    if (s->mode[1] == VULTURE_LOOP && abs32(p->homeX - (pZero2->s).coord.x) > PIXEL(240)) setMode(s, VULTURE_LEAVE);
  }

  if (IsFrozen(p)) {
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      SetDDP(&p->body, sVulture[p->coll]);
    }
    return;
  }
  if (status & BODY_STATUS_WHITE) {
    mode = s->mode[1];
    if (mode == VULTURE_PERCHED || mode == VULTURE_LANDING || mode == VULTURE_PREEN) {
      startle(s->unk_2c);
      setMode(s, VULTURE_KNOCKED);
    }
    if (p->elementEffect == NULL) {
      p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
      if (p->elementEffect != NULL) setMode(s, VULTURE_ELEMENT);
    }
  }
  if (p->elementEffect != NULL && IsDead(p->elementEffect)) p->elementEffect = NULL;

  switch (s->mode[1]) {
    case VULTURE_PERCHED: Vulture_Perched(p); break;
    case VULTURE_TAKE_OFF: Vulture_TakeOff(p); break;
    case VULTURE_LOOP: Vulture_Loop(p); break;
    case VULTURE_RETURN: Vulture_Return(p); break;
    case VULTURE_LANDED: Vulture_Landed(p); break;
    case VULTURE_DIVE: Vulture_Dive(p); break;
    case VULTURE_KNOCKED: Vulture_Knocked(p); break;
    case VULTURE_LANDING: Vulture_Landing(p); break;
    case VULTURE_PREEN: Vulture_Preen(p); break;
    case VULTURE_LEAVE: Vulture_Leave(p); break;
    case VULTURE_PULLED: Vulture_Pulled(p); break;
    case VULTURE_ELEMENT: Vulture_Element(p); break;
  }
}

// 0x0807f198: every 24 frames, takes off or preens
static void Vulture_Perched(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    face(p, !s->work[1]);
    SetMotion(s, ANIM(8));
    setColl(p, 0);
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (p->alarm & ALARM_STARTLED) {
    p->alarm = 0;
    setMode(s, VULTURE_TAKE_OFF);
  } else if (zeroNear(s)) {
    startle(s->unk_2c);
    setMode(s, VULTURE_TAKE_OFF);
  } else if (s->unk_28 != NULL && s->unk_28->mode[1] == 2) {
    setMode(s, VULTURE_TAKE_OFF);
  } else if (RANDOM(RNG_0202f388) & 3) {
    setMode(s, VULTURE_PREEN);
  } else {
    face(p, !s->work[1]);
    s->work[2] = 24;
  }
}

// 0x0807f2d8: flies up 80 px, or to near top of screen
static void Vulture_TakeOff(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    u8 a = 192 + (2 * s->work[1] - 1) * (15 + (RANDOM(RNG_0202f388) & 7));
    SetMotion(s, ANIM(10));
    setColl(p, 2);
    s->d.x = COS(a) * 896 / 256;
    s->d.y = SIN(a) * 896 / 256;
    face(p, s->d.x > 0);
    s->work[2] = abs32(112 / (s->d.y >> 8));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->coord.y < p->homeY - PIXEL(80)) {
    if (s->coord.y <= gStageRun.vm.camera.viewport.y - PIXEL(64) || s->work[2] == 0) setMode(s, VULTURE_LOOP);
  }
}

static void target(struct Vulture* p, Coords32* c);

// 0x0807f414: circles beside perch, or dives at Zero once perch is gone
static void Vulture_Loop(struct Vulture* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  switch (s->mode[2]) {
    case 0:
      face(p, !s->work[1]);
      SetMotion(s, ANIM(0));
      setColl(p, 1);
      s->unk_coord.x = s->coord.x + (1 - 2 * s->work[1]) * PIXEL(72);
      s->unk_coord.y = s->coord.y;
      p->angle = s->work[1] * 128 - 64;
      s->work[2] = 8;
      s->mode[2] = 1;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (s->motion.state == ANIM_END || s->motion.state == ANIM_NEXT_GOTO) {
        s->mode[2]++;
        s->mode[3] = 0;
      }
      break;
    case 2:
      if (s->mode[3] == 0) {
        SetMotion(s, ANIM(0));
        s->mode[3]++;
      }
      UpdateEntityAnim(s);
      if (p->angle == 48 || p->angle == 176) {
        s->mode[2]++;
        s->mode[3] = 0;
      }
      break;
    case 3:
      if (s->mode[3] == 0) {
        SetMotion(s, ANIM(2));
        s->mode[3]++;
      }
      UpdateEntityAnim(s);
      if (s->motion.state != ANIM_END) break;
      if (s->unk_28 != NULL) {
        if (--s->work[2] == 0) {
          setMode(s, VULTURE_RETURN);
          return;
        }
      } else {
        target(p, &c);
        if (abs32(c.x - p->homeX) <= PIXEL(240) && zeroNear(s) && c.y > s->coord.y) {
          setMode(s, VULTURE_DIVE);
          return;
        }
      }
      s->mode[2]++;
      s->mode[3] = 0;
      break;
    case 4:
      if (s->mode[3] == 0) {
        face(p, !FACING_RIGHT(p));
        SetMotion(s, ANIM(3));
        p->high = 8;
        s->mode[3]++;
      }
      UpdateEntityAnim(s);
      if (--p->high == 0) {
        SetMotion(s, ANIM(1));
        s->mode[2] = 1;
      }
      break;
  }
  p->angle += 2;
  s->coord.x = s->unk_coord.x + SIN(p->angle) * 72;
  s->coord.y = s->unk_coord.y + SIN(2 * (p->angle + 64)) * 9 + abs32(SIN(p->angle + 64) * 72) / 8;
}

// 0x08080050: 16 px above Zero's feet
static void target(struct Vulture* p, Coords32* c) {
  struct Entity* s = &p->s;
  c->x = (pZero2->s).coord.x;
  c->y = (pZero2->s).coord.y - PIXEL(16);
  if ((u32)((pZero2->s).coord.x - s->coord.x + PIXEL(128)) > PIXEL(256) ||
      (u32)((pZero2->s).coord.y - s->coord.y + PIXEL(128)) > PIXEL(256)) {
    c->y = s->coord.y;
  }
}

// 0x0807f67c
static void Vulture_Return(struct Vulture* p) {
  struct Entity* s = &p->s;
  struct Entity* perch = s->unk_28;
  if (s->mode[2] == 0) {
    Coords32 c;
    u8 a;
    if (perch == NULL) {
      setMode(s, VULTURE_LOOP);
      return;
    }
    SetMotion(s, ANIM(4));
    setColl(p, 1);
    c.x = perch->coord.x + (2 * s->work[1] - 1) * (PIXEL(16) + (RANDOM(RNG_0202f388) & 7) * PIXEL(1));
    c.y = perch->coord.y;
    a = CalcAngle(c.x - s->coord.x, c.y - s->coord.y);
    s->d.x = COS(a) * 640 / 256;
    s->d.y = SIN(a) * 640 / 256;
    face(p, s->d.x > 0);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (perch != NULL && s->coord.y >= perch->coord.y - PIXEL(28)) setMode(s, VULTURE_LANDING);
}

// 0x0807fac0
static void Vulture_Landed(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(7));
    setColl(p, 0);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->motion.state == ANIM_END) setMode(s, VULTURE_PERCHED);
}

// 0x0807f868
static void Vulture_Dive(struct Vulture* p) {
  struct Entity* s = &p->s;
  u16 swoop;
  if (s->mode[2] == 0) {
    Coords32 c;
    target(p, &c);
    if (c.y < s->coord.y) {
      setMode(s, VULTURE_LOOP);
      return;
    }
    face(p, s->coord.x < (pZero2->s).coord.x);
    SetMotion(s, ANIM(4));
    setColl(p, 2);
    PlaySound(SE_Z2_VULTURE_DIVE);
    p->high = (c.y - s->coord.y) >> 8;
    p->angle = 0;
    s->unk_coord.y = s->coord.y;
    s->work[2] = 64;
    s->d.x = (c.x - s->coord.x) * 2 / 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->work[2]--;
  p->angle += 2;
  s->coord.x += s->d.x;
  swoop = p->high << 8 | p->angle;
  s->coord.y = s->unk_coord.y + abs32(SIN(p->angle) * swoop >> 8);
  if (s->work[2] == 56) SetMotion(s, ANIM(5));
  if (s->work[2] == 0) setMode(s, VULTURE_LOOP);
}

// 0x0807f980: hit while perched
static void Vulture_Knocked(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(11));
    setColl(p, 2);
    s->d.x = (1 - 2 * s->work[3]) * 0x180;
    s->d.y = 0xA0;
    s->work[2] = 12;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (--s->work[2] == 0) setMode(s, VULTURE_TAKE_OFF);
}

// 0x0807f7c8
static void Vulture_Landing(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(6));
    setColl(p, 2);
    s->d.x >>= 2;
    s->d.y >>= 2;
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (p->alarm & ALARM_STARTLED) {
    if (--s->work[2] == 0) {
      p->alarm &= ~ALARM_STARTLED;
      setMode(s, VULTURE_TAKE_OFF);
    }
  } else if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(s, VULTURE_LANDED);
  }
}

// 0x0807f9f0
static void Vulture_Preen(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    face(p, !s->work[1]);
    SetMotion(s, ANIM(9));
    setColl(p, 0);
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->alarm & ALARM_STARTLED) {
    if (--s->work[2] == 0) {
      p->alarm &= ~ALARM_STARTLED;
      setMode(s, VULTURE_TAKE_OFF);
    }
  } else if (s->unk_28 == NULL) {
    setMode(s, VULTURE_TAKE_OFF);
  } else if (zeroNear(s) || s->motion.state == ANIM_END) {
    setMode(s, VULTURE_PERCHED);
  }
}

// 0x0807fb00: perch gone
static void Vulture_Leave(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(1));
    setColl(p, 2);
    s->d.x = (2 * FACING_RIGHT(p) - 1) * PIXEL(1);
    s->d.y = -0x200;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// 0x0807fbf0: burning or frozen, drops to ground
static void Vulture_Element(struct Vulture* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sHarmless[p->coll]);
    s->mode[2]++;
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x4FFF) {
    disappear(s);
    return;
  }
  if (s->mode[2] == 1) {
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) {
      s->d.y = 0;
      s->mode[2]++;
    }
  } else {
    s->coord.y += s->d.y;
    s->d.y += 0x40;
    if (s->d.y > 0x700) s->d.y = 0x700;
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2] = 1;
    }
  }
  if (p->elementEffect == NULL) setMode(s, VULTURE_TAKE_OFF);
}

// --------------------------------------------
// Deaths

static void countKill(struct Vulture* p) {
  struct Entity* s = &p->s;
  TryDropItem(1, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  ApImportVultureKilled();
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
}

static void burstInto(struct Entity* s, const struct SlashedEnemy* gibs, s32 n, u8 side) {
  Coords32 c;
  s32 i;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(12);
  for (i = 0; i < n; i++) useApSheets(CreateSlashedEnemy(&c, &gibs[i], 0, (FACING_RIGHT(s) << 4) | side));
  c.x += ((RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  c.y += ((RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  CreateSmoke(1, &c);
}

static void Vulture_Die(struct Vulture* p) {
  struct Entity* s = &p->s;
  bool8 wasPerched;
  if (s->work[0] == PERCH) {
    Perch_Die((struct Perch*)p);
    return;
  }
  switch (s->mode[1]) {
    case VULTURE_BURST:  // 0x0807fce0
      if (s->mode[2] == 0) {
        SetMotion(s, ANIM(11));
        s->work[2] = 0;
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      if (++s->work[2] > 1) {
        PlaySound(SE_ZAKO_EXPLODE);
        burstInto(s, sGibs, 3, s->work[3]);
        countKill(p);
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      }
      return;
    case VULTURE_CUT:  // 0x0807fdfc
    case VULTURE_CUT_HARD:  // 0x0807ff4c
      if (s->mode[2] == 0) {
        SetMotion(s, ANIM(12));
        wasPerched = s->mode[3] == VULTURE_PERCHED || s->mode[3] == VULTURE_LANDED || s->mode[3] == VULTURE_PREEN;
        if (s->mode[1] == VULTURE_CUT) {
          s->d.x = (1 - 2 * s->work[3]) * (128 + (RANDOM(RNG_0202f388) >> 7 & 0x1FF));
          createHalf(p, wasPerched ? 0 : 1);
        } else {
          s->d.x = (1 - 2 * s->work[3]) * 0x100;
          createHalf(p, 0);
        }
        s->d.y = wasPerched ? -0x300 : -0x100;
        s->work[2] = 0;
        s->mode[2]++;
      }
      if (s->work[2] != 255) {
        UpdateEntityAnim(s);
        s->work[2]++;
        s->coord.x += s->d.x;
        s->coord.y += s->d.y;
        s->d.y += 0x40;
        if (s->d.y > 0x700) s->d.y = 0x700;
        if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(4)) == 0) return;
      }
      PlaySound(SE_ZAKO_EXPLODE);
      burstInto(s, s->mode[1] == VULTURE_CUT ? sGibs : sHardGibs, 2, s->work[3]);
      countKill(p);
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      return;
  }
}

// --------------------------------------------
// Cut-off half, Zero 2's VFX 40

static void Half_Init(struct VFX* p);
static void Half_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2VultureHalfRoutine = {
    [ENTITY_INIT] =      Half_Init,
    [ENTITY_UPDATE] =    Half_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b6eb4
static void createHalf(struct Vulture* vulture, u8 kind) {
  struct Entity* s = AllocEntityLast(gVFXHeaderPtr);
  if (s != NULL) {
    INIT_VFX_ROUTINE(s, VFX_Z2_VULTURE_HALF);
    s->unk_28 = &vulture->s;
    s->coord = (vulture->s).coord;
    s->work[0] = kind;
    s->work[1] = (vulture->s).work[3];
  }
}

// 0x080b6f10
static void Half_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  s32 sign = 1 - 2 * s->work[1];
  s32 speed = RANDOM(RNG_0202f388) >> 7 & 0x1FF;
  InitNonAffineMotion(s);
  useApSheets(p);
  face(p, FACING_RIGHT(s->unk_28));
  SetMotion(s, ANIM(13));
  s->flags |= DISPLAY | FLIPABLE;
  s->work[2] = 0;
  switch (s->work[0]) {
    case 0:
      s->d.x = sign * (128 + speed);
      s->d.y = -0x200;
      break;
    case 1:
      s->d.x = -sign * (128 + speed);
      s->d.y = -0x100;
      break;
    case 2:
      s->d.x = sign * (512 + speed);
      s->d.y = -0x400;
      break;
    default:
      s->d.x = -sign * (512 + speed);
      s->d.y = -0x200;
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Half_Update(p);
}

// 0x080b7100, 0x080b7190
static void Half_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if (s->work[2] != 255) {
    UpdateEntityAnim(s);
    s->work[2]++;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    s->d.y += 0x40;
    if (s->d.y > 0x700) s->d.y = 0x700;
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  }
  burstInto(s, &sHalfGibs[s->work[0] & 1], 1, s->work[1]);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sVulture[3][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {-0x200, -0xa00, 0x1800, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0xa00, 0x1800, 0x1400}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0x1000, 0x2000, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x1400}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {-0x200, -0x1200, 0x1800, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0x1200, 0x1800, 0x1800}},
    },
};

static const struct Collision sHarmless[3][2] = {
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0xa00, 0x1800, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0xa00, 0x1800, 0x1400}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x1400}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0x1200, 0x1800, 0x1800}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {-0x200, -0x1200, 0x1800, 0x1800}},
    },
};

static const struct Collision sPerch[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0xa00, 0x1000, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0xa00, 0x1000, 0x1400}},
};

// 0x08340a90
static const struct SlashedEnemy sGibs[3] = {
    {MOTION(AP_SHEET_Z2_VULTURE, 14), {0xff, 0x11}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_VULTURE, 15), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_VULTURE, 16), {0xff, 0x11}, {0, 0}, {128, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x08340ae4
static const struct SlashedEnemy sHardGibs[2] = {
    {MOTION(AP_SHEET_Z2_VULTURE, 14), {0xff, 0x11}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_VULTURE, 15), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x08346e58, 0x08346e74: by kind 0/2 and 1/3
static const struct SlashedEnemy sHalfGibs[2] = {
    {MOTION(AP_SHEET_Z2_VULTURE, 16), {0xff, 0x11}, {0, 0}, {-16, -768}, {15, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(AP_SHEET_Z2_VULTURE, 16), {0xff, 0x11}, {0, 0}, {-64, -1024}, {63, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
