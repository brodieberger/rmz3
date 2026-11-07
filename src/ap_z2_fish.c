#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "gba/syscall.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's mechanical fish, enemy 53.
  work0:
    0: swims wave, turns at walls
    1: swims straight out, leaps, dives back
    2: from spawner, rises from below screen, then as 1
  work1: faces right
*/

struct Fish {
  OBJECT_HDR;
  s32 anchorX;   // 0xB4
  s32 anchorY;   // 0xB8
  u8 phase;      // 0xBC
  u8 _bd;
  u8 tilt;       // 0xBE
  u8 nextMode;   // 0xBF
  u16 timer;     // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Fish) == sizeof(struct Enemy));

#define elementEffect unk_2c
#define prevX unk_coord.x
#define lastSea unk_coord.y

enum {
  FISH_IDLE,
  FISH_SWIM,
  FISH_WAVE,
  FISH_LEAP,
  FISH_DIVE,
  FISH_TURN,
  FISH_RISE,
  FISH_FALL,
  FISH_RETURN,
  FISH_ALIGN,
  FISH_FLOP,
  FISH_SINK,
  FISH_ELEMENT,
  FISH_HUNT,
  FISH_PULLED,
};

enum {
  FISH_DIE_BURST,
  FISH_DIE_CUT,
  FISH_DIE_CUT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_FISH, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

s32 CalcAngleBetweenPoints(s32 x1, s32 y1, s32 x2, s32 y2);
s32 CalcAngleBetweenCoords(Coords32* c1, Coords32* c2);
void CreateBubble(s32 x, s32 y, u8 kind);

static const struct Collision sBody[2];
static const struct Collision sLeaping[2];
static const struct Collision sHarmless;
static const struct SlashedEnemy sPieces[3];
static const struct SlashedEnemy sWetPieces[3];
static const Coords32 sElementCoord = {0, 0};

static u16 Fish_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Fish_Init(struct Fish* p);
static void Fish_Update(struct Fish* p);
static void Fish_Die(struct Fish* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static void createBit(struct Fish* fish, u8 kind, u8 work1, u8 angle);

// clang-format off
const EnemyRoutine gApZ2FishRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Fish_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Fish_Update,
    [ENTITY_DIE] =       (EnemyFunc)Fish_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Fish* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void turnThen(struct Fish* p, u8 next) {
  p->nextMode = next;
  setMode(p, FISH_TURN);
}

// Turns first if facing away from work1
static void faceThen(struct Fish* p, u8 next) {
  if ((p->s).work[1] == FACING_RIGHT(p)) {
    setMode(p, next);
  } else {
    turnThen(p, next);
  }
}

static void flatMotion(struct Fish* p, bool8 right, motion_t m) {
  InitNonAffineMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, right);
  SetMotion(&p->s, m);
}

static void tiltedMotion(struct Fish* p, bool8 right) {
  InitRotatableMotion(&p->s);
  useApSheets(p);
  SET_XFLIP(p, right);
  SetMotion(&p->s, ANIM(2));
  SetDDP(&p->body, sLeaping);
}

static bool8 solid(s32 x, s32 y) { return FUN_080098a4(x, y) != 0; }

// 0x08083fd8
static bool8 inWater(s32 x, s32 y) { return GetMetatileAttr(x, y) == 0x8000 || y > gOverworld.sea; }

static s32 abs32(s32 v) { return v < 0 ? -v : v; }

static void noseBubble(struct Fish* p, u32 t, u8 chance) {
  struct Entity* s = &p->s;
  if ((t & 7) == 0 && (RANDOM(RNG_0202f388) & chance) == 0) {
    CreateBubble(s->coord.x + (FACING_RIGHT(p) ? PIXEL(12) : -PIXEL(12)), s->coord.y, 0);
  }
}

// 0x0808400c
static void bubbles(Coords32* c, u32 width, u8 least, u8 most) {
  u32 n;
  if (!inWater(c->x, c->y)) return;
  n = least + (u16)RANDOM(RNG_0202f388) % (most - least);
  for (; n != 0; n--) {
    s32 x = c->x + (u16)RANDOM(RNG_0202f388) % (width + 1) - width / 2;
    s32 y = c->y + (u16)RANDOM(RNG_0202f388) % (width + 1) - width / 2 - PIXEL(8);
    CreateBubble(x, y, 0);
  }
}

// 0x08083ea0
static void nextSwim(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    setMode(p, FISH_WAVE);
  } else {
    setMode(p, s->mode[1] == FISH_IDLE ? FISH_SWIM : FISH_IDLE);
  }
}

// 0x0808238c
static void Fish_Init(struct Fish* p) {
  struct Entity* s = &p->s;
  flatMotion(p, s->work[1], ANIM(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  p->anchorX = s->coord.x;
  p->anchorY = s->coord.y;
  s->prevX = s->coord.x;
  p->phase = 0;
  p->tilt = 0;
  s->elementEffect = NULL;
  INIT_BODY(p, sBody, 6, onCollision);
  (p->body).unk_28 = (u32)Fish_Pull;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == 2) {
    setMode(p, FISH_RISE);
    s->lastSea = gOverworld.sea;
  } else {
    setMode(p, FISH_IDLE);
    s->unk_28 = NULL;
  }
  Fish_Update(p);
}

static void Fish_Idle(struct Fish* p);
static void Fish_Swim(struct Fish* p);
static void Fish_Wave(struct Fish* p);
static void Fish_Leap(struct Fish* p);
static void Fish_Dive(struct Fish* p);
static void Fish_Turn(struct Fish* p);
static void Fish_Rise(struct Fish* p);
static void Fish_Fall(struct Fish* p);
static void Fish_Return(struct Fish* p);
static void Fish_Align(struct Fish* p);
static void Fish_Flop(struct Fish* p);
static void Fish_Sink(struct Fish* p);
static void Fish_Element(struct Fish* p);
static void Fish_Hunt(struct Fish* p);

static void vanish(struct Fish* p) {
  (p->s).flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x080824d4
// 0x08083310
static void Fish_Pulled(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
}

// 0x08084110
static u16 Fish_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  struct Fish* p = (struct Fish*)s;
  if (s->mode[1] != FISH_PULLED) setMode(p, FISH_PULLED);
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  if (s->unk_2c != NULL) {
    setMode(p, FISH_ELEMENT);
  } else if (!inWater(s->coord.x, s->coord.y)) {
    setMode(p, FISH_FALL);
  } else if (s->work[0] == 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(32)) != 0 || FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) != 0) {
      setMode(p, FISH_ALIGN);
    } else {
      p->phase = 0;
      p->anchorX = s->coord.x;
      p->anchorY = s->coord.y;
      setMode(p, FISH_WAVE);
    }
  } else if ((s->coord.x >= p->anchorX) == FACING_RIGHT(p)) {
    turnThen(p, FISH_RETURN);
  } else {
    setMode(p, FISH_RETURN);
  }
  return 0;
}

static void Fish_Update(struct Fish* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (status & BODY_STATUS_DEAD) {
    u8 kind = FISH_DIE_BURST;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? FISH_DIE_CUT_HARD : FISH_DIE_CUT;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    EXIT_BODY(p);
    Fish_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (s->elementEffect != NULL) {
      s->elementEffect = NULL;
      SetDDP(&p->body, sLeaping);
    }
    return;
  }

  if (s->work[0] == 2) {
    s32 sea = gOverworld.sea;
    if (s->unk_28 == NULL || s->unk_28->mode[0] > ENTITY_UPDATE) {
      vanish(p);
      return;
    }
    if (sea < (pZero2->s).coord.y) {
      if (s->mode[1] == FISH_SWIM) setMode(p, FISH_HUNT);
    } else {
      p->anchorY = sea + PIXEL(16);
      if (!(status & BODY_STATUS_RECOILED)) s->coord.y += sea - s->lastSea;
      if (s->mode[1] == FISH_HUNT) {
        if (s->work[1] == FACING_RIGHT(p)) {
          turnThen(p, FISH_RETURN);
        } else {
          setMode(p, FISH_RETURN);
        }
      }
    }
    s->lastSea = sea;
  }

  if ((status & BODY_STATUS_WHITE) && s->elementEffect == NULL) {
    if (inWater(s->coord.x, s->coord.y) && (p->body).elemented == ELEMENT_FLAME) {
      bubbles(&s->coord, PIXEL(28), 10, 12);
    } else {
      s->elementEffect = ApplyElementEffect(0, (Object*)p, &sElementCoord);
      if (s->elementEffect != NULL) setMode(p, FISH_ELEMENT);
    }
  } else if (s->elementEffect != NULL && IsDead(s->elementEffect)) {
    s->elementEffect = NULL;
  }

  switch (s->mode[1]) {
    case FISH_IDLE: Fish_Idle(p); break;
    case FISH_SWIM: Fish_Swim(p); break;
    case FISH_WAVE: Fish_Wave(p); break;
    case FISH_PULLED: Fish_Pulled(p); break;
    case FISH_LEAP: Fish_Leap(p); break;
    case FISH_DIVE: Fish_Dive(p); break;
    case FISH_TURN: Fish_Turn(p); break;
    case FISH_RISE: Fish_Rise(p); break;
    case FISH_FALL: Fish_Fall(p); break;
    case FISH_RETURN: Fish_Return(p); break;
    case FISH_ALIGN: Fish_Align(p); break;
    case FISH_FLOP: Fish_Flop(p); break;
    case FISH_SINK: Fish_Sink(p); break;
    case FISH_ELEMENT: Fish_Element(p); break;
    case FISH_HUNT: Fish_Hunt(p); break;
  }
  s->prevX = s->coord.x;
}

// 0x08082748
static void Fish_Idle(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, s->work[2], 7);
  if (--s->work[2] == 0) nextSwim(p);
}

// 0x080827e8: out to 160 px from spot, drifts to height, leaps
static void Fish_Swim(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SET_XFLIP(p, s->work[1]);
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 80;
    s->d.x = FACING_RIGHT(p) ? 0x200 : -0x200;
    s->d.y = (p->anchorY - s->coord.y) / 80;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, --s->work[2], 3);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if ((u32)(p->anchorX - s->coord.x + PIXEL(160)) > PIXEL(320)) setMode(p, FISH_LEAP);
}

// 0x08082900: 24 px up and down along height
static void Fish_Wave(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 0;
    s->d.x = FACING_RIGHT(p) ? PIXEL(1) : -PIXEL(1);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, ++s->work[2], 7);
  p->phase += 2;
  s->coord.x += s->d.x;
  if (solid(s->coord.x, s->coord.y)) {
    s->coord.x = FACING_RIGHT(p) ? FUN_0800a22c(s->coord.x, s->coord.y) : FUN_0800a31c(s->coord.x, s->coord.y);
    turnThen(p, FISH_WAVE);
  }
  s->coord.y = p->anchorY + SIN(p->phase) * 24;
  if (solid(s->coord.x, s->coord.y)) {
    if (solid(s->coord.x, s->coord.y - PIXEL(8))) {
      s->coord.y = FUN_0800a134(s->coord.x, s->coord.y);
    } else if (solid(s->coord.x, s->coord.y + PIXEL(8))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    }
    p->phase = 128 - p->phase;
    turnThen(p, FISH_WAVE);
  }
  if ((u32)(p->anchorX - s->coord.x + PIXEL(160)) > PIXEL(320)) turnThen(p, FISH_WAVE);
}

static void surfaceBubbles(struct Fish* p) {
  struct Entity* s = &p->s;
  u32 n = (RANDOM(RNG_0202f388) & 1) + 4;
  createBit(p, 2, 0, 0);
  for (; n != 0; n--) {
    s32 x = s->coord.x + ((RANDOM(RNG_0202f388) & 7) - 3) * PIXEL(1);
    CreateBubble(x, gOverworld.sea + (RANDOM(RNG_0202f388) & 7) * PIXEL(1), 2);
  }
}

// 0x08082a9c: out of water at 45 degrees, lands back where it left
static void Fish_Leap(struct Fish* p) {
  struct Entity* s = &p->s;
  Coords32 old;
  if (s->mode[2] == 0) {
    s32 up;
    tiltedMotion(p, !s->work[1]);
    up = Sqrt(0x500000);
    s->d.y = -up;
    s->d.x = 0xA00000 / (up * 8);
    if (!FACING_RIGHT(p)) s->d.x = -s->d.x;
    s->mode[2]++;
  }
  switch (s->mode[2]) {
    case 1:
      if (s->coord.y <= gOverworld.sea) {
        surfaceBubbles(p);
        s->mode[2]++;
      }
      break;
    case 2:
      if (s->coord.y >= gOverworld.sea) {
        PlaySound(SE_Z2_SPLASH);
        surfaceBubbles(p);
        s->mode[2]++;
        s->work[2] = 0;
      }
      break;
    case 3:
      noseBubble(p, ++s->work[2], 7);
      break;
  }
  UpdateEntityAnim(s);
  old = s->coord;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  p->tilt = CalcAngleBetweenCoords(&s->coord, &old);
  if (FACING_RIGHT(p)) p->tilt = 128 - p->tilt;
  s->angle = p->tilt;
  if (s->coord.y > p->anchorY) {
    s->coord.y = p->anchorY;
    setMode(p, FISH_DIVE);
  }
}

// 0x08082dd4: levels out from dive, turns back at bottom
static void Fish_Dive(struct Fish* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sBody);
      s->d.x = s->coord.x - s->prevX;
      s->d.y = 0x280;
      s->work[2] = 0;
      s->mode[2]++;
    case 1:
      UpdateEntityAnim(s);
      noseBubble(p, ++s->work[2], 3);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->d.y > 0) s->d.y -= 16;
      p->tilt = p->tilt > 251 ? 0 : p->tilt + 4;
      s->angle = p->tilt;
      if (p->tilt == 0) s->mode[2]++;
      break;
    case 2:
      flatMotion(p, FACING_RIGHT(p), ANIM(1));
      s->mode[2]++;
    case 3:
      UpdateEntityAnim(s);
      noseBubble(p, ++s->work[2], 3);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->d.y > 0) s->d.y -= 12;
      if (s->motion.state == ANIM_END) s->mode[2]++;
      break;
    case 4:
      SET_XFLIP(p, s->work[1]);
      SetMotion(s, ANIM(0));
      s->mode[2]++;
    case 5:
      UpdateEntityAnim(s);
      noseBubble(p, ++s->work[2], 3);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y -= 6;
      if (s->d.y <= 0) setMode(p, FISH_SWIM);
      break;
  }
}

// 0x08083038
static void Fish_Turn(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    flatMotion(p, FACING_RIGHT(p), ANIM(1));
    SetDDP(&p->body, sBody);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, --s->work[2], 1);
  if (s->mode[2] == 1) {
    if (s->motion.state == ANIM_END) {
      s->mode[2]++;
      s->mode[3] = 0;
    }
    return;
  }
  if (s->mode[3] == 0) {
    SET_XFLIP(p, !FACING_RIGHT(p));
    SetMotion(s, ANIM(0));
    s->work[2] = 4;
    s->mode[3]++;
    UpdateEntityAnim(s);
  }
  if (s->work[2] == 0) setMode(p, p->nextMode);
}

// 0x08083184
static void Fish_Rise(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->d.y = -0x180;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, --s->work[2], 3);
  s->coord.y += s->d.y;
  if (s->coord.y <= gOverworld.sea + PIXEL(16)) {
    faceThen(p, FISH_SWIM);
  } else if (s->coord.y <= (pZero2->s).coord.y) {
    faceThen(p, FISH_HUNT);
  }
}

// 0x08083280: out of water, stranded or back in
static void Fish_Fall(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  s->angle--;
  if (solid(s->coord.x, s->coord.y) && !inWater(s->coord.x, s->coord.y + PIXEL(80))) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(p, FISH_FLOP);
  } else if (s->coord.y > p->anchorY) {
    s->coord.y = p->anchorY;
    setMode(p, FISH_SINK);
  }
}

// 0x08083338
static void Fish_Return(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    u16 dx = abs32(p->anchorX - s->coord.x);
    u16 dy = abs32(p->anchorY - s->coord.y);
    u8 a = CalcAngleBetweenPoints(s->coord.x, s->coord.y, p->anchorX, p->anchorY);
    flatMotion(p, FACING_RIGHT(p), ANIM(0));
    SetDDP(&p->body, sBody);
    s->d.x = COS(a) * 2;
    s->d.y = SIN(a) * 2;
    if (dy < dx) {
      p->timer = abs32(s->d.x != 0 ? dx / s->d.x : 0);
    } else {
      p->timer = abs32(s->d.y != 0 ? dy / s->d.y : 0);
    }
    if (p->timer == 0) {
      s->d.x = s->d.y = 0;
      p->timer = 1;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, p->timer, 3);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (--p->timer == 0) faceThen(p, FISH_SWIM);
}

static void startWave(struct Fish* p, u8 phase) {
  struct Entity* s = &p->s;
  setMode(p, FISH_WAVE);
  p->phase = phase;
  p->anchorX = s->coord.x;
  p->anchorY = s->coord.y;
}

// 0x080834d0: backs 32 px off floor or ceiling
static void Fish_Align(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s32 d;
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sBody);
    if (solid(s->coord.x, s->coord.y - PIXEL(32))) {
      s->d.y = 0x80;
      d = FUN_0800a134(s->coord.x, s->coord.y - PIXEL(32)) - s->coord.y + PIXEL(32);
    } else if (solid(s->coord.x, s->coord.y + PIXEL(32))) {
      s->d.y = -0x80;
      d = PIXEL(32) - (FUN_08009f6c(s->coord.x, s->coord.y + PIXEL(32)) - s->coord.y);
    } else {
      startWave(p, 0);
      return;
    }
    s->work[2] = abs32(d / s->d.y);
    if (s->work[2] == 0) {
      s->d.y = 0;
      s->work[2] = 1;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  noseBubble(p, s->work[2], 3);
  s->coord.y += s->d.y;
  if (--s->work[2] == 0) startWave(p, s->d.y < 0 ? 128 : 0);
}

// 0x0808361c: beached, wriggles 128 frames, blows
static void Fish_Flop(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    bool8 right = s->coord.x < p->anchorX;
    tiltedMotion(p, right);
    s->angle = 4;
    s->d.x = 64;
    s->work[2] = 128;
    s->mode[2]++;
  }
  if (--s->work[2] > 16) {
    UpdateEntityAnim(s);
    if ((s->work[2] & 3) == 0) s->angle = (s->work[2] & 4) ? 4 : -4;
  } else if (s->d.x > 0) {
    s->d.x -= 4;
  }
  s->coord.x += FACING_RIGHT(p) ? s->d.x : -s->d.x;
  if (!solid(s->coord.x, s->coord.y + PIXEL(8))) {
    setMode(p, FISH_FALL);
    return;
  }
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->work[2] == 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = FISH_DIE_BURST;
    EXIT_BODY(p);
    Fish_Die(p);
  }
}

// 0x0808378c: back in, slows, rights itself
static void Fish_Sink(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y /= 2;
    if (s->d.y > 0x280) s->d.y = 0x280;
    if (s->d.y < 0x80) s->d.y = 0x80;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[2] == 1) {
    s->coord.y += s->d.y;
    if (s->d.y > 80) s->d.y -= 16;
    if (solid(s->coord.x, s->coord.y) && !inWater(s->coord.x, s->coord.y + PIXEL(80))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2]++;
    }
  }
  if (s->angle == 0) {
    if (s->work[0] != 0) {
      if ((s->coord.x >= p->anchorX) != FACING_RIGHT(p)) {
        setMode(p, FISH_RETURN);
      } else {
        turnThen(p, FISH_RETURN);
      }
    } else if (solid(s->coord.x, s->coord.y - PIXEL(32)) || solid(s->coord.x, s->coord.y + PIXEL(32))) {
      setMode(p, FISH_ALIGN);
    } else {
      startWave(p, 0);
    }
  } else if (s->angle & 0x80) {
    s->angle = s->angle + 2 > 255 ? 0 : s->angle + 2;
  } else {
    s->angle = s->angle <= 2 ? 0 : s->angle - 2;
  }
}

// 0x080838c4: burning or frozen, sinks or falls
static void Fish_Element(struct Fish* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sHarmless);
    s->d.y = 0;
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    bool8 wet = inWater(s->coord.x, s->coord.y);
    s->coord.y += s->d.y;
    s->d.y += wet ? 32 : 0x40;
    if (s->d.y > (wet ? 0x380 : 0x700)) s->d.y = wet ? 0x380 : 0x700;
    if (solid(s->coord.x, s->coord.y) && solid(s->coord.x, s->coord.y + PIXEL(80))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[2]++;
    }
  }
  if (s->elementEffect != NULL) return;
  if (inWater(s->coord.x, s->coord.y)) {
    setMode(p, FISH_SINK);
  } else {
    setMode(p, solid(s->coord.x, s->coord.y + PIXEL(8)) ? FISH_FLOP : FISH_FALL);
  }
}

// 0x080839a0: Zero in water, levels with him, swims wave back and forth
static void Fish_Hunt(struct Fish* p) {
  struct Entity* s = &p->s;
  s32 zy = (pZero2->s).coord.y;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 0;
    p->anchorY = s->coord.y;
    p->phase = 0;
    s->d.x = FACING_RIGHT(p) ? PIXEL(1) : -PIXEL(1);
    if (zy + PIXEL(24) < s->coord.y) {
      s->mode[2] = 1;
    } else if (zy - PIXEL(24) > s->coord.y) {
      s->mode[2] = 3;
    } else {
      s->mode[2] = 2;
    }
  }
  UpdateEntityAnim(s);
  noseBubble(p, ++s->work[2], 7);
  switch (s->mode[2]) {
    case 1:
      s->coord.y -= 0x180;
      if (s->coord.y <= gOverworld.sea + PIXEL(40)) {
        s->coord.y = gOverworld.sea + PIXEL(40);
        p->anchorY = s->coord.y;
        p->phase = 0;
        s->mode[2]++;
      } else if (s->coord.y <= zy) {
        p->anchorY = s->coord.y;
        p->phase = 0;
        s->mode[2]++;
      }
      break;
    case 2: {
      s32 end = p->anchorX + (s->work[1] ? PIXEL(80) : -PIXEL(80));
      p->phase += 2;
      s->coord.x += s->d.x;
      s->coord.y = p->anchorY + SIN(p->phase) * 24;
      if ((u32)(end - s->coord.x + PIXEL(110)) > PIXEL(220)) turnThen(p, FISH_HUNT);
      break;
    }
    case 3:
      s->coord.y += 0x180;
      if (s->coord.y >= zy) {
        p->anchorY = s->coord.y;
        p->phase = 0;
        s->mode[2]--;
      }
      break;
  }
}

static void countKill(struct Fish* p) {
  struct Entity* s = &p->s;
  TryDropItem(3, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void burstPieces(struct Fish* p) {
  struct Entity* s = &p->s;
  const struct SlashedEnemy* pieces = sPieces;
  Coords32 c;
  u8 flip = (FACING_RIGHT(p) << 4) | s->work[3];
  s32 i;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(12);
  if (inWater(s->coord.x, s->coord.y)) {
    bubbles(&s->coord, PIXEL(24), 6, 8);
    PlaySound(SE_Z2_FISH_BURST);
    pieces = sWetPieces;
  } else {
    PlaySound(SE_ZAKO_EXPLODE);
  }
  for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&c, &pieces[i], 0, flip));
}

static void smoke(struct Entity* s, u8 kind) {
  Coords32 c;
  c.x = s->coord.x + ((s32)(RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  c.y = s->coord.y + ((s32)(RANDOM(RNG_0202f388) & 15) - 8) * PIXEL(1);
  CreateSmoke(kind, &c);
}

// 0x08083b88
static void Fish_Burst(struct Fish* p) {
  burstPieces(p);
  smoke(&p->s, 1);
  smoke(&p->s, 2);
  (p->s).flags &= ~DISPLAY;
  countKill(p);
}

// 0x08083d0c, 0x08083dd4: cut, tail flies off, rest sails after it
static void Fish_Cut(struct Fish* p, bool8 hard) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    createBit(p, 0, s->work[3], p->tilt);
    if (hard) {
      s->d.x = s->work[3] ? 0x180 : -0x180;
      s->d.y = -0x200;
    } else {
      s->d.x = s->work[3] * PIXEL(1) - 0x80;
      s->d.y = -0x1C0;
    }
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (s->work[2] < (hard ? 16 : 32)) {
    UpdateEntityAnim(s);
    s->work[2]++;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    s->d.y += hard ? 0x40 : 32;
    if (s->d.y > (hard ? 0x700 : 0x380)) s->d.y = hard ? 0x700 : 0x380;
    if (!solid(s->coord.x, s->coord.y)) return;
  }
  burstPieces(p);
  smoke(s, 1);
  s->flags &= ~DISPLAY;
  countKill(p);
}

// 0x080826e0
static void Fish_Die(struct Fish* p) {
  switch ((p->s).mode[1]) {
    case FISH_DIE_BURST: Fish_Burst(p); break;
    case FISH_DIE_CUT: Fish_Cut(p, FALSE); break;
    case FISH_DIE_CUT_HARD: Fish_Cut(p, TRUE); break;
  }
}

// 0x080840e4
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = (struct Entity*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) s->work[3] = s->coord.x < (pZero2->s).coord.x;
}

// --------------------------------------------
// Zero 2's enemy 61, unseen, keeps two fish coming from below screen

struct FishSpawner {
  OBJECT_HDR;
  struct Entity* left;   // 0xB4
  struct Entity* right;  // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct FishSpawner) == sizeof(struct Enemy));

static void Spawner_Init(struct FishSpawner* p);
static void Spawner_Update(struct FishSpawner* p);

// clang-format off
const EnemyRoutine gApZ2FishSpawnerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Spawner_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Spawner_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEnemy,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08088224
static void Spawner_Init(struct FishSpawner* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  p->left = p->right = NULL;
  s->work[2] = s->work[3] = 0;
  Spawner_Update(p);
}

// 0x0808841c
static struct Entity* createFish(struct Entity* spawner, s32 x, u8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FISH);
    p->renderPrio = 24;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = spawner;
    p->coord.x = x;
    p->coord.y = gStageRun.vm.camera.viewport.y + 0x8FFF;
    p->work[0] = 2;
    p->work[1] = right;
  }
  return p;
}

// 0x0808827c
static void Spawner_Update(struct FishSpawner* p) {
  struct Entity* s = &p->s;
  if (s->coord.x + 0x16700 < gStageRun.vm.camera.viewport.x + 0x77FF) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (p->left != NULL && p->left->mode[0] > ENTITY_UPDATE) p->left = NULL;
  if (p->right != NULL && p->right->mode[0] > ENTITY_UPDATE) p->right = NULL;
  if (p->left == NULL) {
    if (s->work[2] != 0) {
      s->work[2]--;
    } else {
      p->left = createFish(s, s->coord.x - PIXEL(80), 1);
      s->work[2] = 255;
    }
  }
  if (p->right == NULL) {
    if (s->work[3] != 0) {
      s->work[3]--;
    } else {
      p->right = createFish(s, s->coord.x + PIXEL(80), 0);
      s->work[3] = 255;
    }
  }
}

// --------------------------------------------
// Zero 2's VFX 49.
// work0:
//   0: cut tail
//   2: splash on surface

static void Bit_Init(struct VFX* p);
static void Bit_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FishBitRoutine = {
    [ENTITY_INIT] =      Bit_Init,
    [ENTITY_UPDATE] =    Bit_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b9e5c
static void createBit(struct Fish* fish, u8 kind, u8 work1, u8 angle) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FISH_BIT);
    p->renderPrio = 1;
    p->unk_28 = &fish->s;
    p->coord = (fish->s).coord;
    p->work[0] = kind;
    p->work[1] = work1;
    p->work[2] = 0;
    p->angle = angle;
  }
}

// 0x080b9ee4, 0x080ba044
static void Bit_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  if (s->work[0] == 2) {
    InitNonAffineMotion(s);
    useApSheets(p);
    SetMotion(s, ANIM(5));
  } else {
    u8 angle = s->angle;
    bool8 right = FACING_RIGHT(s->unk_28);
    if (angle != 0) {
      InitRotatableMotion(s);
      s->angle = angle;
    } else {
      InitNonAffineMotion(s);
    }
    useApSheets(p);
    SET_XFLIP(p, right);
    s->renderPrio = 28;
    SetMotion(s, ANIM(4));
    s->d.x = 0x40 - s->work[1] * 0x80;
    s->d.y = -0x180;
  }
  s->flags |= DISPLAY | FLIPABLE;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Bit_Update(p);
}

// 0x080ba110, 0x080ba230
static void Bit_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  if (s->work[0] == 2) {
    UpdateEntityAnim(s);
    s->coord.y = gOverworld.sea - PIXEL(4);
    if (s->motion.state == ANIM_END) SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  if (s->work[2] < 32) {
    UpdateEntityAnim(s);
    s->work[2]++;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    s->d.y += 32;
    if (s->d.y > 0x380) s->d.y = 0x380;
    if (!solid(s->coord.x, s->coord.y)) return;
  }
  CreateSmoke(1, &s->coord);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sBody[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0x00, 0, 0x00000000, {0x0, 0x0, 0x2000, 0x1000}},
};

static const struct Collision sLeaping[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}};

static const struct SlashedEnemy sPieces[3] = {
    {ANIM(6), {0x30, 0x30}, {0, 0}, {256, -768}, {31, 31}, {0, 64}, {512, 512}, {0}},
    {ANIM(7), {0x30, 0x30}, {0, 0}, {-128, -832}, {31, 31}, {0, 64}, {512, 512}, {0}},
    {ANIM(8), {0x30, 0x30}, {0, 0}, {-256, -800}, {31, 31}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sWetPieces[3] = {
    {ANIM(6), {0x30, 0x30}, {0, 0}, {256, -704}, {31, 31}, {0, 32}, {512, 512}, {0}},
    {ANIM(7), {0x30, 0x30}, {0, 0}, {-128, -640}, {31, 31}, {0, 32}, {512, 512}, {0}},
    {ANIM(8), {0x30, 0x30}, {0, 0}, {-256, -768}, {31, 31}, {0, 32}, {512, 512}, {0}},
};
// clang-format on

#endif  // AP
