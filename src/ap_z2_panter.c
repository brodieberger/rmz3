#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "overworld.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Zero 2's boss 3, Panter Flauclaws, on the Train's two cars.
  work0: 0 Train, 1 Yggdrasil's refight, not ported
  Stands on fourteen spots, 0..6 back from the right car's edge, 7..13 the left's.
*/

struct Panter {
  OBJECT_HDR;
  u8 lastState;                 // 0xB4
  u8 spot;                      // 0xB5, where the move goes
  bool8 airborne;               // 0xB6, ground not followed
  u8 _b7;
  struct Entity* element;       // 0xB8
  s32 floorGap;                 // 0xBC, pounce's spring
  u8 back;                      // 0xC0, thrown claws back
  bool8 recall;                 // 0xC1
  u8 _c2[2];
  struct Entity* claws[2];      // 0xC4
  s32 rightEdge;                // 0xCC
  s32 leftEdge;                 // 0xD0
  s32 slide;                    // 0xD4, car's push this frame
  s32 fall;                     // 0xD8
  struct Entity* explosion;     // 0xDC
  u16 _e0;
  u8 _e2[2];
};
static_assert(sizeof(struct Panter) == sizeof(struct Boss));

typedef void (*PanterFunc)(struct Panter*);

enum {
  PANTER_WAIT,
  PANTER_ROAR,
  PANTER_IDLE,
  PANTER_LEAP,
  PANTER_CLAWS,
  PANTER_JUMP_THROW,
  PANTER_6,
  PANTER_7,
  PANTER_8,
  PANTER_9,
  PANTER_STUNNED,
};

#define PANTER(n) MOTION(DM208_Z2_PANTER, (n))
#define SHEET(n) MOTION(AP_SHEET_Z2_PANTER, (n))
#define HOME_X unk_coord.x
#define HOME_Y unk_coord.y
#define SPOT_Y PIXEL(416)

static const struct Collision sBody[16];
static const struct Coord sElementCoord = {PIXEL(12), 0};
static const s32 sSpots[14] = {PIXEL(0), PIXEL(16), PIXEL(32), PIXEL(48), PIXEL(64), PIXEL(80), PIXEL(96),
                               PIXEL(0), PIXEL(16), PIXEL(32), PIXEL(48), PIXEL(64), PIXEL(80), PIXEL(96)};
// Move, what it rules out, weight near, mid, far
static const u16 sMoves[8][5] = {
    {PANTER_IDLE, 1, 0, 0, 0}, {PANTER_LEAP, 2, 0, 0, 4}, {PANTER_CLAWS, 4, 4, 0, 0}, {PANTER_JUMP_THROW, 8, 0, 4, 4},
    {PANTER_6, 16, 4, 4, 4},   {PANTER_7, 32, 4, 4, 0},   {PANTER_8, 64, 8, 0, 0},   {PANTER_9, 128, 4, 4, 4},
};

static const struct PreloadEntity sSheet = {AP_SHEET_Z2_PANTER, 0, 640, 5, 0, AP_PRELOAD_SHEET, 0};

static void Panter_Init(struct Panter* p);
static void Panter_Update(struct Panter* p);
static void Panter_Die(struct Panter* p);
struct Entity* ApZ2CreatePanterClaw(struct Entity* boss, const Coords32* at, u8 kind, u8 n);
struct Entity* ApZ2CreatePanterHeld(struct Entity* boss, const Coords32* at, u8 kind, u8 n);
struct Entity* ApZ2CreatePanterSlash(struct Entity* boss, const Coords32* at, u8 kind, u8 n);
s32 CalcAngleBetweenCoords(Coords32* c1, Coords32* c2);

// clang-format off
const BossRoutine gApZ2PanterRoutine = {
    [ENTITY_INIT] =      (BossFunc)Panter_Init,
    [ENTITY_UPDATE] =    (BossFunc)Panter_Update,
    [ENTITY_DIE] =       (BossFunc)Panter_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteEntity,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
  s->mode[3] = 0;
}

static void nextStep(struct Entity* s) {
  s->mode[2]++;
  s->mode[3] = 0;
}

static bool8 animDone(struct Entity* s) { return (s->motion).state == ANIM_END; }

static void face(struct Panter* p, bool8 right) { SET_XFLIP(p, right); }

static void faceZero(struct Panter* p) { face(p, (p->s).coord.x < (pZero2->s).coord.x); }

// 0x08044d54, 0x08044d80
static s32 spotX(struct Panter* p, u8 n) {
  s32 edge = n <= 6 ? p->rightEdge : p->leftEdge;
  if (n > 13) n = 13;
  return edge - sSpots[n];
}

static s32 spotFloor(struct Panter* p, u8 n) { return FUN_08009f6c(spotX(p, n), SPOT_Y); }

// 0x08044cd4: right car past home
static u8 spotAt(struct Panter* p, s32 x) {
  u8 n;
  x += PIXEL(8);
  if (x > (p->s).HOME_X) {
    for (n = 0; n < 7 && x < p->rightEdge - sSpots[n]; n++) {}
    return n < 7 ? n : 6;
  }
  for (n = 7; n < 14 && x < p->leftEdge - sSpots[n]; n++) {}
  return n < 14 ? n : 13;
}

// 0x08044dac
static bool8 onRightCar(struct Panter* p, s32 x) { return (p->s).HOME_X < x; }

static u8 mySpot(struct Panter* p) { return spotAt(p, (p->s).coord.x); }

static u8 zeroSpot(struct Panter* p) { return spotAt(p, (pZero2->s).coord.x); }

// 0x08044de8
static u8 spotBesideZero(struct Panter* p) {
  s32 x = (pZero2->s).coord.x;
  return spotAt(p, mySpot(p) < zeroSpot(p) ? x + PIXEL(64) : x - PIXEL(64));
}

// 0x08044e34
static u8 farEnd(struct Panter* p) { return mySpot(p) <= 6 ? 13 : 0; }

// 0x08044e5c
static u8 spotAhead(struct Panter* p) {
  return spotAt(p, (p->s).coord.x + (((p->s).flags & X_FLIP) ? -PIXEL(96) : PIXEL(96)));
}

// 0x08044e8c
static u8 middleOfCar(struct Panter* p) { return onRightCar(p, (p->s).coord.x) ? 3 : 10; }

// 0x08044f20: off is half its height
static bool8 hitFloorOrCeiling(struct Entity* s, u16 off) {
  s32 x = s->coord.x, y = s->coord.y;
  if (s->d.y > 0) {
    if (!FUN_080098a4(x, y + off)) return FALSE;
    s->coord.y = FUN_08009f6c(x, y + off) - off;
    return TRUE;
  }
  if (s->d.y < 0) {
    if (!FUN_080098a4(x, y - off)) return FALSE;
    s->coord.y = FUN_0800a134(x, y - off) + off;
    return TRUE;
  }
  return FUN_080098a4(x, y - off) || FUN_080098a4(x, y + off);
}

// 0x08044ea4: falls, TRUE once landed
static bool8 land(struct Panter* p, u16 off) {
  struct Entity* s = &p->s;
  if (s->d.y == 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y + off + PIXEL(1))) return TRUE;
    if (FUN_080098a4(s->coord.x, s->coord.y + off + PIXEL(8))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - off;
      return TRUE;
    }
  }
  if (hitFloorOrCeiling(s, off)) {
    s->d.y = 0;
    return TRUE;
  }
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
  return FALSE;
}

// 0x08044fac
static bool8 hitWall(struct Entity* s, u16 off) {
  s32 x = s->coord.x, y = s->coord.y;
  if (s->d.x < 0) {
    if (!FUN_080098a4(x - off, y)) return FALSE;
    s->coord.x = FUN_0800a31c(x - off, y) + off;
    return TRUE;
  }
  if (s->d.x > 0) {
    if (!FUN_080098a4(x + off, y)) return FALSE;
    s->coord.x = FUN_0800a22c(x + off, y) - off;
    return TRUE;
  }
  return FUN_080098a4(x - off, y) || FUN_080098a4(x + off, y);
}

/*
  0x08044a4c: next move by weight, near, mid or far from Zero.
  Not the last one twice, not a leap to where it stands, the run only at mid range,
  move 8 only at rank A or S on Zero's car
*/
static void pick(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 zx = (pZero2->s).coord.x;
  u16 ruled = 0, total, r;
  u8 here = mySpot(p), zero = zeroSpot(p), beside, band, i;
  s32 d;

  if (p->lastState == s->mode[1]) {
    for (i = 0; i < 8; i++) {
      if (sMoves[i][0] == s->mode[1]) ruled |= sMoves[i][1];
    }
  }
  beside = spotBesideZero(p);
  if (here == beside) {
    ruled |= 2;
  } else if (s->coord.x >= zx ? beside - zero >= -1 : beside - zero <= 1) {
    ruled |= 2;
  }
  d = s->coord.x - zx;
  if ((u32)(d + PIXEL(64)) <= PIXEL(128) || (u32)(d + PIXEL(128)) > PIXEL(256)) ruled |= 128;
  if (gScore.total->rank <= 4 || onRightCar(p, s->coord.x) != onRightCar(p, zx)) ruled |= 64;
  d = zx - s->coord.x;
  if ((u32)(d + PIXEL(96)) <= PIXEL(192)) {
    band = 2;
  } else if ((u32)(d + PIXEL(128)) > PIXEL(256)) {
    band = 4;
  } else {
    band = 3;
  }
  p->lastState = s->mode[1];

  for (i = total = 0; i < 8; i++) {
    if (!(sMoves[i][1] & ruled)) total += sMoves[i][band];
  }
  if (total == 0) {
    setMode(s, PANTER_IDLE);
    return;
  }
  r = (RANDOM(RNG_0202f388) & 0x7FFF) % total;
  for (i = total = 0; i < 8; i++) {
    if (sMoves[i][1] & ruled) continue;
    total += sMoves[i][band];
    if (r < total) {
      s->mode[1] = sMoves[i][0];
      break;
    }
  }
  switch (s->mode[1]) {
    case PANTER_LEAP:
      p->spot = spotBesideZero(p);
      break;
    case PANTER_JUMP_THROW:
      p->spot = mySpot(p);
      break;
    case PANTER_6:
      p->spot = farEnd(p);
      break;
    case PANTER_8:
      p->spot = middleOfCar(p);
      break;
    case PANTER_9:
      p->spot = zeroSpot(p);
      break;
  }
  s->mode[2] = 0;
  s->mode[3] = 0;
}

// 0x08045038
static void onHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = body->parent;
  if (body->hitboxFlags & 1) s->work[3] = (pZero2->s).coord.x > s->coord.x;
}

static void findEdges(struct Panter* p, s32 inset) {
  struct Entity* s = &p->s;
  p->rightEdge = FUN_0800a31c(s->HOME_X + PIXEL(160), s->HOME_Y) - inset;
  p->leftEdge = FUN_0800a31c(s->HOME_X - PIXEL(32), s->HOME_Y) - inset;
}

// 0x080421e8
static void Panter_Init(struct Panter* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sSheet);
  s->mode[2] = 0;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  face(p, s->coord.x < (pZero2->s).coord.x);
  SetSpriteAnimation(p, PANTER(8));
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  s->d.x = s->d.y = 0;
  p->spot = 0;
  p->lastState = PANTER_IDLE;
  p->airborne = FALSE;
  p->_e0 = 0;
  p->element = NULL;
  s->HOME_X = PIXEL(416);
  s->HOME_Y = PIXEL(416);
  findEdges(p, PIXEL(32));
  ResetBossBody((struct Boss*)p, sBody, 64);
  (p->body).fn = onHit;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, PANTER_WAIT);
  Panter_Update(p);
}

static const PanterFunc sStates[11];

// 0x0804235c
static void Panter_Update(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 y;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = ((p->body).status & BODY_STATUS_SLASHED) != 0;
    s->mode[2] = 0;
    Panter_Die(p);
    return;
  }
  findEdges(p, PIXEL(16));
  if (!p->airborne) {
    y = s->coord.y;
    s->coord.y = FUN_08009f6c(s->coord.x, y);
    p->fall = s->coord.y - y;
    p->slide = FUN_0800a40c(s->coord.x, s->coord.y + PIXEL(8));
    s->coord.x += p->slide;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && p->element == NULL && (p->body).elemented == 3) {
    p->element = ApplyElementEffect(13, (Object*)p, &sElementCoord);
    if (p->element != NULL && !p->airborne) setMode(s, PANTER_STUNNED);
  }
  if (p->element != NULL && IsDead(p->element)) p->element = NULL;
  sStates[s->mode[1]](p);
}

// 0x080424e8: until script's flag
static void Panter_Wait(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, PANTER(8));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) setMode(s, PANTER_ROAR);
}

// 0x08042524: until warning is done
static void Panter_Roar(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, PANTER(9));
    s->work[2] = 0;
    s->mode[2]++;
    PlaySound(SE_Z2_PANTER_ROAR);
  }
  UpdateSpriteAnimation(p);
  if (s->mode[2] == 1) {
    if (!animDone(s)) return;
    SetSpriteAnimation(p, PANTER(0));
    s->mode[2]++;
  } else if (!(gStageRun.vm.active & VM_ACTIVE)) {
    setMode(s, PANTER_IDLE);
  }
}

// 0x08042590
static void Panter_Idle(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] > 95) pick(p);
}

// --------------------------------------------
// 0x080425d8: leap to beside Zero

static void Leap_Crouch(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    face(p, mySpot(p) > p->spot);
    SetSpriteAnimation(p, PANTER(1));
    SetDDP(&p->body, sBody);
    PlaySound(SE_Z2_PANTER_LEAP);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

// Arc over 24 frames, 44 a frame squared down
static void Leap_Fly(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 x = spotX(p, p->spot), y = spotFloor(p, p->spot);
  u8 t;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(4));
    s->d.x = (x - s->coord.x) / 24;
    s->d.y = -0x420;
    s->work[2] = 24;
    SetDDP(&p->body, &sBody[12]);
    p->airborne = TRUE;
    s->mode[3]++;
  }
  if ((s->motion).cmdIdx <= 1) UpdateSpriteAnimation(p);
  t = 24 - --s->work[2];
  s->coord.x = x - s->d.x * s->work[2];
  s->coord.y = y + s->d.y * t + 44 * t * t;
  if (s->work[2] != 0) return;
  p->airborne = FALSE;
  SetDDP(&p->body, &sBody[10]);
  nextStep(s);
}

static void Leap_Land(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) s->mode[3]++;
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx == 5) nextStep(s);
}

static void Leap_Rise(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(14));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Leap_End(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    SetDDP(&p->body, sBody);
    s->work[2] = 8;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) pick(p);
}

static const PanterFunc sLeap[5] = {Leap_Crouch, Leap_Fly, Leap_Land, Leap_Rise, Leap_End};

static void Panter_Leap(struct Panter* p) { sLeap[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08042808: throws both claws, which come back

static void Claws_Face(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    faceZero(p);
    SetSpriteAnimation(p, PANTER(18));
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void throwClaw(struct Panter* p, motion_t m, s32 dx, u8 n, u8 lasts) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, m);
    s->work[2] = 0;
    PlaySound(SE_Z2_PANTER_THROW);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] == 1) {
    at.x = s->coord.x + ((s->flags & X_FLIP) ? dx : -dx);
    at.y = s->coord.y - PIXEL(18);
    p->claws[n] = ApZ2CreatePanterClaw(s, &at, 0, n);
  } else if (s->work[2] >= lasts && animDone(s)) {
    nextStep(s);
  }
}

static void Claws_ThrowFirst(struct Panter* p) { throwClaw(p, PANTER(19), -PIXEL(15), 0, 20); }

static void Claws_ThrowSecond(struct Panter* p) { throwClaw(p, PANTER(20), PIXEL(20), 1, 8); }

// Both back, gone in a burst
static void Claws_Catch(struct Panter* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(21));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] == 1) {
    if (!animDone(s)) return;
    SetSpriteAnimation(p, PANTER(0));
    s->mode[3]++;
    return;
  }
  if (p->claws[0]->mode[1] != 2 || p->claws[1]->mode[1] != 2) return;
  for (i = 0; i < 2; i++) {
    struct Entity* c = p->claws[i];
    c->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(c);
    c->flags &= ~COLLIDABLE;
    SET_PROJECTILE_ROUTINE(c, ENTITY_DISAPPEAR);
  }
  ApZ2CreatePanterHeld(s, &s->coord, 3, 0);
  ApZ2CreatePanterHeld(s, &s->coord, 3, 1);
  nextStep(s);
}

static void Claws_End(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    s->work[2] = 12;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) pick(p);
}

static const PanterFunc sClaws[5] = {Claws_Face, Claws_ThrowFirst, Claws_ThrowSecond, Claws_Catch, Claws_End};

static void Panter_Claws(struct Panter* p) { sClaws[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08042b14: jumps, throws three claws that circle back

static void Jump_Face(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    faceZero(p);
    SetSpriteAnimation(p, PANTER(1));
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void jumpUp(struct Panter* p, s32 dy) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(2));
    s->d.x = 0;
    s->d.y = dy;
    p->airborne = TRUE;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]++;
  s->coord.x = spotX(p, p->spot);
  s->coord.y += s->d.y;
  land(p, 0);
  if (s->d.y >= 0) nextStep(s);
}

static void Jump_Up(struct Panter* p) { jumpUp(p, -0x700); }

static void holdPose(struct Panter* p, motion_t m) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, m);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = spotX(p, p->spot);
  if (animDone(s)) nextStep(s);
}

static void Jump_Top(struct Panter* p) { holdPose(p, PANTER(15)); }

static void Jump_Throw(struct Panter* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(16));
    at.x = s->coord.x + ((s->flags & X_FLIP) ? PIXEL(16) : -PIXEL(16));
    at.y = s->coord.y;
    for (i = 0; i < 3; i++) ApZ2CreatePanterClaw(s, &at, 1, i);
    SetSpriteAnimation(p, PANTER(16));
    p->back = 0;
    p->recall = FALSE;
    PlaySound(SE_Z2_PANTER_THROW);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = spotX(p, p->spot);
  if (animDone(s)) nextStep(s);
}

static void Jump_After(struct Panter* p) { holdPose(p, PANTER(17)); }

static void Jump_Fall(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(3));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = spotX(p, p->spot);
  if (s->mode[3] == 1) {
    s->coord.y += s->d.y;
    if (!land(p, 0)) return;
    SetSpriteAnimation(p, PANTER(14));
    p->airborne = FALSE;
    s->mode[3]++;
  } else if (animDone(s)) {
    nextStep(s);
  }
}

// Claws all out, skips to waiting
static void Jump_Landed(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 16;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] != 0) return;
  p->recall = TRUE;
  s->mode[2] += 4;
  s->mode[3] = 0;
}

static void Jump_Again(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(1));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Jump_UpAgain(struct Panter* p) {
  p->recall = TRUE;
  jumpUp(p, -0x500);
}

static void Jump_Wait(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 0;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] > 55 && p->back == 3) pick(p);
}

static const PanterFunc sJump[11] = {Jump_Face,   Jump_Up,    Jump_Top,     Jump_Throw,   Jump_After, Jump_Fall,
                                   Jump_Landed, Jump_Again, Jump_UpAgain, Jump_Fall,    Jump_Wait};

static void Panter_JumpThrow(struct Panter* p) { sJump[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08042f18: leaps to the car's far end, throwing three claws down from the top

static void arc(struct Panter* p, u8 frames) {
  struct Entity* s = &p->s;
  u8 t = frames - --s->work[2];
  s->coord.x = spotX(p, p->spot) - s->d.x * s->work[2];
  s->coord.y = spotFloor(p, p->spot) + s->d.y * t + 44 * t * t;
}

static void Far_Face(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    face(p, mySpot(p) > p->spot);
    SetSpriteAnimation(p, PANTER(1));
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Far_Rise(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(2));
    s->d.x = (spotX(p, p->spot) - s->coord.x) / 50;
    s->d.y = -0x898;
    s->work[2] = 50;
    p->airborne = TRUE;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  arc(p, 50);
  if (s->work[2] == 25) nextStep(s);
}

static void playThrough(struct Panter* p, motion_t m) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, m);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Far_Top(struct Panter* p) { playThrough(p, PANTER(15)); }

static void aimClaw(struct Panter* p, u8 spot, s32 y) {
  struct Entity* s = &p->s;
  ApZ2CreatePanterClaw(s, &s->coord, 2, CalcAngle(spotX(p, spot) - s->coord.x, y - s->coord.y));
}

static void Far_Throw(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 y = s->coord.y + PIXEL(96);
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(16));
    if (s->flags & X_FLIP) {
      aimClaw(p, 2, y);
      aimClaw(p, 8, y);
      aimClaw(p, 13, y);
    } else {
      aimClaw(p, 11, y);
      aimClaw(p, 5, y);
      aimClaw(p, 0, y);
    }
    PlaySound(SE_Z2_PANTER_THROW);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Far_After(struct Panter* p) { playThrough(p, PANTER(17)); }

static void Far_Fall(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(3));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  arc(p, 50);
  if (s->work[2] != 0) return;
  p->airborne = FALSE;
  nextStep(s);
}

static void Far_Land(struct Panter* p) { playThrough(p, PANTER(14)); }

static void Far_TurnRound(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 32;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (s->work[2] == 28) face(p, !(s->flags & X_FLIP));
  if (--s->work[2] == 0) pick(p);
}

static const PanterFunc sFar[8] = {Far_Face, Far_Rise, Far_Top, Far_Throw, Far_After, Far_Fall, Far_Land, Far_TurnRound};

static void Panter_FarLeap(struct Panter* p) { sFar[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08043354: two slashes, a claw in each hand let go as a wave

static void place(struct Entity* e, struct Entity* s, s32 dx, s32 dy) {
  e->coord.x = s->coord.x + ((s->flags & X_FLIP) ? dx : -dx);
  e->coord.y = s->coord.y + dy;
}

static void letGo(struct Entity* claw, struct Entity* s, s32 dx, s32 dy) {
  Coords32 at;
  claw->flags &= ~(DISPLAY | FLIPABLE);
  SET_VFX_ROUTINE(claw, ENTITY_DISAPPEAR);
  at.x = s->coord.x + ((s->flags & X_FLIP) ? dx : -dx);
  at.y = s->coord.y + dy;
  ApZ2CreatePanterSlash(s, &at, 0, 0);
}

static void Combo_Face(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    faceZero(p);
    SetSpriteAnimation(p, PANTER(22));
    SetDDP(&p->body, sBody);
    s->work[2] = 8;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) nextStep(s);
}

static void Combo_Draw(struct Panter* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[3] == 0) {
    at.y = s->coord.y - PIXEL(20);
    at.x = s->coord.x + ((s->flags & X_FLIP) ? -PIXEL(21) : PIXEL(21));
    p->claws[0] = ApZ2CreatePanterHeld(s, &at, 0, 0);
    at.x = s->coord.x + ((s->flags & X_FLIP) ? PIXEL(22) : -PIXEL(22));
    p->claws[1] = ApZ2CreatePanterHeld(s, &at, 0, 1);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
    s->work[2] = 32;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) nextStep(s);
}

// Front claw by frame, let go on the third
static void Combo_First(struct Panter* p) {
  struct Entity* s = &p->s;
  struct Entity** c = p->claws;
  s8 frame;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(19));
    c[0]->mode[1]++;
    c[1]->mode[1]++;
    (c[1]->spr).oam.priority = 3;
    PlaySound(SE_Z2_PANTER_THROW);
    s->mode[3]++;
  }
  frame = (s->motion).cmdIdx;
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx != frame && ++s->mode[3] == 3) letGo(c[0], s, PIXEL(16), -PIXEL(20));
  switch (s->mode[3]) {
    case 1:
      place(c[0], s, -PIXEL(20), -PIXEL(8));
      place(c[1], s, -PIXEL(8), -PIXEL(22));
      break;
    case 2:
      place(c[0], s, PIXEL(16), -PIXEL(16));
      place(c[1], s, -PIXEL(14), -PIXEL(22));
      break;
    case 3:
      place(c[0], s, PIXEL(24), -PIXEL(32));
      place(c[1], s, -PIXEL(18), -PIXEL(24));
      break;
    case 4:
      place(c[1], s, -PIXEL(20), -PIXEL(26));
      break;
    default:
      if (animDone(s)) nextStep(s);
      break;
  }
}

// Back claw by frame, let go on the second
static void Combo_Second(struct Panter* p) {
  struct Entity* s = &p->s;
  struct Entity* c = p->claws[1];
  s8 frame;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(20));
    PlaySound(SE_Z2_PANTER_THROW);
    s->work[2] = 0;
    s->mode[3]++;
  }
  frame = (s->motion).cmdIdx;
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx != frame && ++s->work[2] == 1) letGo(c, s, PIXEL(8), -PIXEL(28));
  switch (s->work[2]) {
    case 0:
      place(c, s, -PIXEL(24), -PIXEL(24));
      break;
    case 1:
      place(c, s, PIXEL(6), -PIXEL(14));
      break;
    case 2:
      place(c, s, PIXEL(12), -PIXEL(16));
      (c->spr).oam.priority = 2;
      break;
    default:
      if (animDone(s)) nextStep(s);
      break;
  }
}

static void Combo_End(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(21));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] == 1) {
    if (!animDone(s)) return;
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 32;
    s->mode[3]++;
  } else if (--s->work[2] == 0) {
    pick(p);
  }
}

static const PanterFunc sCombo[5] = {Combo_Face, Combo_Draw, Combo_First, Combo_Second, Combo_End};

static void Panter_Combo(struct Panter* p) { sCombo[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08043850: rank A and S, hops to the car's middle and spins, waves both ways

static void Spin_Hop(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 x;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(4));
    SetDDP(&p->body, &sBody[12]);
    if (p->spot > mySpot(p)) {
      s->d.x = -0x400;
      face(p, FALSE);
    } else {
      s->d.x = 0x400;
      face(p, TRUE);
    }
    s->mode[3]++;
  }
  x = spotX(p, p->spot);
  if (s->d.x < 0 ? s->coord.x <= x : s->coord.x >= x) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    nextStep(s);
    return;
  }
  UpdateSpriteAnimation(p);
  switch ((s->motion).cmdIdx) {
    case 0:
      s->coord.x += s->d.x / 2;
      s->coord.y -= 170;
      break;
    case 1:
      s->coord.x += s->d.x;
      s->coord.y -= 42;
      break;
    case 2:
      s->coord.x += s->d.x / 2;
      s->coord.y += 42;
      break;
    case 3:
      s->coord.y += 170;
      break;
    default:
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      break;
  }
}

static void Spin_Draw(struct Panter* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[3] == 0) {
    faceZero(p);
    SetSpriteAnimation(p, PANTER(22));
    at.y = s->coord.y - PIXEL(20);
    at.x = s->coord.x + ((s->flags & X_FLIP) ? -PIXEL(21) : PIXEL(21));
    p->claws[0] = ApZ2CreatePanterHeld(s, &at, 1, 0);
    at.x = s->coord.x + ((s->flags & X_FLIP) ? PIXEL(22) : -PIXEL(22));
    p->claws[1] = ApZ2CreatePanterHeld(s, &at, 1, 1);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
    SetDDP(&p->body, sBody);
    s->work[2] = 20;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) nextStep(s);
}

static void Spin_Raise(struct Panter* p) {
  struct Entity* s = &p->s;
  struct Entity** c = p->claws;
  s8 frame;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(23));
    c[0]->mode[1]++;
    c[1]->mode[1]++;
    s->work[2] = 36;
    s->mode[3]++;
  }
  frame = (s->motion).cmdIdx;
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx != frame && ++s->mode[3] == 3) {
    SetDDP(&p->body, &sBody[10]);
    (c[1]->spr).oam.priority = 3;
  }
  switch (s->mode[3]) {
    case 1:
      place(c[0], s, -PIXEL(26), -PIXEL(32));
      place(c[1], s, PIXEL(20), -PIXEL(34));
      break;
    case 2:
      place(c[0], s, -PIXEL(28), -PIXEL(36));
      place(c[1], s, PIXEL(20), -PIXEL(39));
      break;
    case 3:
      place(c[0], s, PIXEL(2), -PIXEL(4));
      place(c[1], s, PIXEL(18), -PIXEL(8));
      break;
    case 4:
      place(c[0], s, PIXEL(12), PIXEL(4));
      place(c[1], s, PIXEL(24), PIXEL(8));
      if (--s->work[2] == 0) nextStep(s);
      break;
  }
}

static void Spin_Spin(struct Panter* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(24));
    SetDDP(&p->body, &sBody[8]);
    s->work[2] = 0;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] <= 3) return;
  if (s->work[2] == 4) {
    for (i = 0; i < 2; i++) {
      p->claws[i]->flags &= ~(DISPLAY | FLIPABLE);
      SET_VFX_ROUTINE(p->claws[i], ENTITY_DISAPPEAR);
    }
    s->unk_2c = ApZ2CreatePanterHeld(s, &s->coord, 2, 0);
    PlaySound(SE_Z2_PANTER_SPIN);
  }
  s->unk_2c->coord = s->coord;
  if ((s->work[2] & 7) == 0) {
    ApZ2CreatePanterSlash(s, &s->coord, 1, 0);
    ApZ2CreatePanterSlash(s, &s->coord, 1, 1);
  }
  if (s->work[2] <= 99) return;
  StopSound(SE_Z2_PANTER_SPIN);
  nextStep(s);
}

static void Spin_Stop(struct Panter* p) { playThrough(p, PANTER(14)); }

static void Spin_End(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetDDP(&p->body, sBody);
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 16;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) pick(p);
}

static const PanterFunc sSpin[6] = {Spin_Hop, Spin_Draw, Spin_Raise, Spin_Spin, Spin_Stop, Spin_End};

static void Panter_Spin(struct Panter* p) { sSpin[(p->s).mode[2]](p); }

// --------------------------------------------
// 0x08043e20: hops back, spins up and dives at Zero's spot, springs off him if it hits

static void Pounce_Face(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    face(p, p->spot < mySpot(p));
    SetSpriteAnimation(p, PANTER(1));
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void backHop(struct Panter* p) {
  struct Entity* s = &p->s;
  s->coord.x += s->d.x;
  hitWall(s, PIXEL(16));
  s->coord.y += s->d.y;
  land(p, 0);
}

static void Pounce_Hop(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(2));
    s->d.x = (s->flags & X_FLIP) ? -0x80 : 0x80;
    s->d.y = -0x680;
    p->airborne = TRUE;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  backHop(p);
  if (s->d.y >= -0x400) nextStep(s);
}

static void Pounce_Tuck(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(10));
    PlaySound(SE_Z2_PANTER_LEAP);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  backHop(p);
  if (animDone(s)) nextStep(s);
}

static void rotate(struct Panter* p, bool8 on) {
  struct Entity* s = &p->s;
  bool8 right = (s->flags & X_FLIP) != 0;
  if (on) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  ResetDynamicMotion(s);
  face(p, right);
}

static void Pounce_Spin(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    rotate(p, TRUE);
    s->angle = 0;
    SetSpriteAnimation(p, PANTER(11));
    SetDDP(&p->body, &sBody[2]);
    s->coord.y -= PIXEL(22);
    s->work[2] = 0;
    s->mode[3]++;
  }
  if (s->mode[3] == 1) {
    s->angle += 24;
    if (s->work[2] == 8) {
      rotate(p, FALSE);
      SetSpriteAnimation(p, PANTER(12));
      SetDDP(&p->body, &sBody[4]);
      s->coord.y += PIXEL(22);
      s->work[2] = 0;
      s->mode[3]++;
    }
  } else if (animDone(s)) {
    nextStep(s);
  }
  UpdateSpriteAnimation(p);
  s->work[2]++;
}

// Ten frames to the spot. Hitting Zero lands it on him
static void Pounce_Dive(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 x = spotX(p, p->spot), y = spotFloor(p, p->spot), dx, dy;
  if (s->mode[3] == 0) {
    (s->spr).oam.priority = 1;
    s->d.x = (x - s->coord.x) / 10;
    s->d.y = (y - s->coord.y) / 10;
    s->work[2] = 10;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]--;
  s->coord.x = x - s->d.x * s->work[2];
  s->coord.y = y - s->d.y * s->work[2];
  if ((p->body).status & BODY_STATUS_B2) {
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
    dx = (pZero2->s).coord.x - (s->coord.x + ((s->flags & X_FLIP) ? PIXEL(24) : -PIXEL(24)));
    dy = (dx << 8) / s->d.x * s->d.y / 256;
    s->coord.x += dx;
    s->coord.y -= dy < 0 ? -dy : dy;
    nextStep(s);
    return;
  }
  if (s->work[2] != 0) return;
  p->airborne = FALSE;
  (s->spr).oam.priority = 2;
  s->mode[2] += 6;
  s->mode[3] = 0;
}

// Eases back off what it hit
static void Pounce_Recoil(struct Panter* p) {
  struct Entity* s = &p->s;
  u8 n;
  if (s->mode[3] == 0) {
    s->work[2] = 0;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] == 1) {
    if (++s->work[2] == 5) {
      s->work[2] = 6;
      s->mode[3]++;
    }
    return;
  }
  n = s->work[2]--;
  s->coord.x -= s->d.x / (s->work[2] + 2);
  s->coord.y -= s->d.y / (s->work[2] + 2);
  s->work[2] = n - 2;
  if (s->work[2] == 0) nextStep(s);
}

// Springs off to the spot ahead
static void Pounce_Spring(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 x, y;
  u8 t;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(10));
    s->coord.x += (s->flags & X_FLIP) ? -PIXEL(10) : PIXEL(10);
    p->floorGap = spotFloor(p, p->spot) - s->coord.y - PIXEL(20);
    p->spot = spotAhead(p);
    s->d.x = (spotX(p, p->spot) - s->coord.x) / 28;
    s->d.y = -0x380;
    s->work[2] = 28;
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  x = spotX(p, p->spot);
  y = spotFloor(p, p->spot) - PIXEL(22) - p->floorGap;
  UpdateSpriteAnimation(p);
  t = 28 - --s->work[2];
  s->coord.x = x - s->d.x * s->work[2];
  s->coord.y = y + s->d.y * t + 32 * t * t;
  if (!animDone(s)) return;
  p->floorGap += PIXEL(23);
  nextStep(s);
}

static void Pounce_Roll(struct Panter* p) {
  struct Entity* s = &p->s;
  s32 x = spotX(p, p->spot), y = spotFloor(p, p->spot) - PIXEL(22) - p->floorGap;
  u8 t;
  if (s->mode[3] == 0) {
    rotate(p, TRUE);
    s->angle = 0;
    (s->spr).oam.priority = 2;
    SetSpriteAnimation(p, PANTER(11));
    SetDDP(&p->body, &sBody[2]);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]--;
  s->angle += 24;
  t = 28 - s->work[2];
  s->coord.x = x - s->d.x * s->work[2];
  s->coord.y = y + s->d.y * t + 32 * t * t;
  if (--s->work[2] == 0) nextStep(s);
}

static void Pounce_Drop(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    s->d.y = 0x440;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  s->angle += 24;
  s->coord.x = spotX(p, p->spot);
  s->coord.y += s->d.y;
  if (!land(p, PIXEL(22))) return;
  p->airborne = FALSE;
  nextStep(s);
}

static void Pounce_RollEnd(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    rotate(p, FALSE);
    SetSpriteAnimation(p, PANTER(13));
    SetDDP(&p->body, &sBody[6]);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (!animDone(s)) return;
  s->mode[2] += 2;
  s->mode[3] = 0;
}

static void Pounce_Landed(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(25));
    SetDDP(&p->body, &sBody[6]);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Pounce_Rise(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(14));
    SetDDP(&p->body, sBody);
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (animDone(s)) nextStep(s);
}

static void Pounce_End(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetSpriteAnimation(p, PANTER(0));
    s->work[2] = 16;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) pick(p);
}

static const PanterFunc sPounce[13] = {Pounce_Face,   Pounce_Hop,  Pounce_Tuck,    Pounce_Spin,   Pounce_Dive,
                                     Pounce_Recoil, Pounce_Spring, Pounce_Roll,  Pounce_Drop,   Pounce_RollEnd,
                                     Pounce_Landed, Pounce_Rise, Pounce_End};

static void Panter_Pounce(struct Panter* p) { sPounce[(p->s).mode[2]](p); }

// 0x08044678: thunder, until the effect is gone
static void Panter_Stunned(struct Panter* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    rotate(p, FALSE);
    SetSpriteAnimation(p, PANTER(5));
    (s->spr).oam.priority = 2;
    SetDDP(&p->body, &sBody[14]);
    StopSound(SE_Z2_PANTER_SPIN);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (p->element == NULL) pick(p);
}

// clang-format off
static const PanterFunc sStates[11] = {
    [PANTER_WAIT] =       Panter_Wait,
    [PANTER_ROAR] =       Panter_Roar,
    [PANTER_IDLE] =       Panter_Idle,
    [PANTER_LEAP] =       Panter_Leap,
    [PANTER_CLAWS] =      Panter_Claws,
    [PANTER_JUMP_THROW] = Panter_JumpThrow,
    [PANTER_6] =          Panter_FarLeap,
    [PANTER_7] =          Panter_Combo,
    [PANTER_8] =          Panter_Spin,
    [PANTER_9] =          Panter_Pounce,
    [PANTER_STUNNED] =    Panter_Stunned,
};
// clang-format on

// --------------------------------------------
// 0x08044728, 0x08044884: kneels, or is cut and its top slides off, then explodes on script's flag 0x80

struct Entity* ApZ2CreatePanterHalf(struct Entity* boss, const Coords32* at, u8 right);

static void Panter_Die(struct Panter* p) {
  struct Entity* s = &p->s;
  bool8 right = (s->flags & X_FLIP) != 0;
  Coords32 at;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    rotate(p, FALSE);
    StopSound(SE_Z2_PANTER_SPIN);
    if (s->mode[1] == 0) {
      SetSpriteAnimation(p, PANTER(5));
      s->work[2] = 32;
    } else {
      PlaySound(SE_LIGHT);
      SetSpriteAnimation(p, PANTER(6));
      s->unk_2c = ApZ2CreatePanterHalf(s, &s->coord, right);
      s->d.x = 72;
    }
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[2]) {
    case 1:
      if (s->mode[1] == 0) {
        if (--s->work[2] == 0) s->mode[2]++;
      } else {
        s->coord.x += (right ? 1 : -1) * s->d.x;
        s->d.x -= 2;
        if (s->d.x < 0) s->mode[2]++;
      }
      break;
    case 2:
      if (!(s->scriptEntity->flags & 0x80)) break;
      at.x = s->mode[1] == 0 ? (right ? -PIXEL(10) : PIXEL(10)) : (right ? -PIXEL(16) : PIXEL(16));
      at.y = -PIXEL(28);
      p->explosion = CreateBossExplosion(s, &at);
      s->mode[2]++;
      break;
    case 3:
      if (p->explosion->mode[0] <= ENTITY_UPDATE) break;
      if (s->mode[1] != 0 && s->unk_2c != NULL) {
        s->unk_2c->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(s->unk_2c);
        s->unk_2c->flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(s->unk_2c, ENTITY_DISAPPEAR);
      }
      s->flags &= ~DISPLAY;
      gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// clang-format off
static const struct Collision sBody[16] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1200, 0x1800, 0x2000}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1800, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x2000}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x2000, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {-0xe00, -0xe00, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1800, 0x1800, 0x1800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {-0x400, -0xc00, 0x2600, 0x1c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x400, -0xc00, 0x2600, 0x1c00}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {-0x400, -0x800, 0x2600, 0x1000}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0xffffffff, {-0x400, -0x800, 0x2600, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {0x0, -0x800, 0x2a00, 0x1000}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x800, 0x2000, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1000, 0x2a00, 0x1800}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x1800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1800, 0x2000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1800, 0x2000}},
};
// clang-format on

// --------------------------------------------

/*
  Zero 2's projectile 16, his thrown claws.
  work0:
    0: Claws, swings out and back on an ellipse, work1 which
    1: Jump-throw, flies out, waits for recall, comes home
    2: Far leap's, straight on, work1 angle
*/

struct Claw {
  OBJECT_HDR;
  s8 dir;          // 0xB4
  u8 blink;        // 0xB5
  u16 swing;       // 0xB6
  u16 spin;        // 0xB8, or ellipse's width
  u16 height;      // 0xBA
  Coords32 center; // 0xBC
};
static_assert(sizeof(struct Claw) == sizeof(struct Projectile));

static void Claw_Init(struct Claw* p);
static void Claw_Update(struct Claw* p);
static void Claw_Die(struct Claw* p);

// clang-format off
const ProjectileRoutine gApZ2PanterClawRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Claw_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Claw_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Claw_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

static const struct Collision sClaw[3][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1800, 0x400}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x400}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    },
};
// clang-format on

static const u8 sThrowAngle[3] = {32, 40, 48};

// 0x0809bd14
struct Entity* ApZ2CreatePanterClaw(struct Entity* boss, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_PANTER_CLAW);
    p->unk_28 = boss;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

static void hide(struct Entity* s, u8 routine) {
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(s);
  s->mode[0] = routine;
}

// 0x0809bd74
static void Claw_Init(struct Claw* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  bool8 right = (boss->flags & X_FLIP) != 0;
  u8 ang;
  p->dir = right ? 1 : -1;
  s->texture = TEXTURE_AP_SHEET;
  switch (s->work[0]) {
    case 0:
      s->palID = 1;
      InitNonAffineMotion(s);
      SET_XFLIP(p, right);
      SetMotion(s, SHEET(2));
      if (s->work[1] == 0) {
        p->spin = 0x1C00;
        p->height = 0xC00;
        p->center.x = boss->coord.x + p->dir * PIXEL(13);
        p->swing = 0x780;
      } else {
        p->spin = 0x2000;
        p->height = 0xC00;
        p->center.x = boss->coord.x + p->dir * PIXEL(52);
        p->swing = 0x400;
      }
      p->center.y = boss->coord.y - PIXEL(18);
      break;
    case 1:
      s->palID = 1;
      InitScalerotMotion2(s);
      SET_XFLIP(p, right);
      SetMotion(s, SHEET(1));
      ang = 64 - p->dir * sThrowAngle[s->work[1]];
      s->d.x = SIN(ang + 64) * 9 * 128 / 256;
      s->d.y = SIN(ang) * 9 * 128 / 256;
      s->angle = ang - 96;
      p->spin = 0;
      break;
    case 2:
      InitScalerotMotion2(s);
      s->angle = 0;
      SET_XFLIP(p, right);
      SetMotion(s, SHEET(1));
      s->d.x = SIN(s->work[1] + 64) * 4;
      s->d.y = SIN(s->work[1]) * 4;
      p->spin = 0x1000;
      break;
  }
  s->flags |= DISPLAY | FLIPABLE | COLLIDABLE;
  s->work[2] = 0;
  INIT_BODY(p, sClaw[s->work[0]], 4, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Claw_Update(p);
}

static void spin(struct Claw* p, u16 most) {
  p->spin += 128;
  if (p->spin > most) p->spin = most;
  (p->s).angle += p->spin >> 8;
}

// 0x0809c0f8, 0x0809c240
static void Claw_Swing(struct Claw* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 a;
  if (boss->mode[1] == PANTER_STUNNED) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Claw_Die(p);
    return;
  }
  p->center.x = boss->coord.x + p->dir * (s->work[1] ? PIXEL(52) : PIXEL(13));
  p->center.y = boss->coord.y - PIXEL(18);
  switch (s->mode[1]) {
    case 0:
      if ((s16)p->swing < 0) {
        if (s->work[1]) p->swing = 0x8000;
        s->mode[1]++;
      }
      s->work[2]++;
      break;
    case 1:
      if ((s16)p->swing >= 0) {
        if (s->work[1]) p->swing = 0;
        s->mode[1]++;
      }
      if (--s->work[2] == 0) s->work[2] = 1;
      break;
    case 2:
      s->coord.x = boss->coord.x - p->dir * (s->work[1] ? -PIXEL(20) : PIXEL(15));
      s->coord.y = boss->coord.y - PIXEL(18);
      UpdateSpriteAnimation(p);
      return;
  }
  a = p->swing >> 8;
  s->coord.x = p->center.x - (SIN(a + 64) * p->spin / 256) * p->dir;
  s->coord.y = p->center.y + SIN(a) * p->height / 256;
  p->swing += s->work[1] ? s->work[2] << 7 : s->work[2] * 192;
  UpdateSpriteAnimation(p);
}

static void homeAt(struct Claw* p, Coords32* at) {
  struct Entity* boss = (p->s).unk_28;
  at->x = boss->coord.x + p->dir * ((p->s).work[1] == 1 ? PIXEL(22) : -PIXEL(21));
  at->y = boss->coord.y - PIXEL(20);
}

static const u8 sHomeTime[3] = {16, 20, 24};

// 0x0809c39c: out, recalled, back past him, home
static void Claw_Thrown(struct Claw* p) {
  struct Entity* s = &p->s;
  struct Panter* boss = (struct Panter*)s->unk_28;
  Coords32 at;
  u8 a;
  UpdateSpriteAnimation(p);
  if ((boss->s).mode[1] == PANTER_STUNNED) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Claw_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      spin(p, 0x4000);
      s->work[2]++;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (hitFloorOrCeiling(s, PIXEL(8)) || hitWall(s, PIXEL(8)) || s->work[2] > 24) s->mode[1]++;
      break;
    case 1:
      spin(p, 0x4000);
      if (!boss->recall) break;
      homeAt(p, &at);
      a = CalcAngleBetweenCoords(&at, &s->coord);
      s->d.x = SIN(a + 64) * 5 * 64 / 256;
      s->d.y = SIN(a) * 5 * 64 / 256;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 2:
      spin(p, 0x8000);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (--s->work[2] != 0) break;
      homeAt(p, &at);
      s->work[2] = sHomeTime[s->work[1]];
      s->d.x = (at.x - s->coord.x) / s->work[2];
      s->d.y = (at.y - s->coord.y) / s->work[2];
      s->mode[1]++;
      break;
    case 3:
      spin(p, 0x8000);
      s->work[2]--;
      homeAt(p, &at);
      s->coord.x = at.x - s->d.x * s->work[2];
      s->coord.y = at.y - s->d.y * s->work[2];
      if (s->work[2] != 0) break;
      ApZ2CreatePanterHeld(&boss->s, &(boss->s).coord, 3, s->work[1] == 1);
      boss->back++;
      hide(s, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x0809c77c
static void Claw_Flying(struct Claw* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x6000) {
    hide(s, ENTITY_DISAPPEAR);
    return;
  }
  spin(p, 0x2000);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// 0x0809c07c
static void Claw_Update(struct Claw* p) {
  struct Entity* s = &p->s;
  if (s->unk_28->mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Claw_Die(p);
    return;
  }
  switch (s->work[0]) {
    case 0:
      Claw_Swing(p);
      break;
    case 1:
      Claw_Thrown(p);
      break;
    case 2:
      Claw_Flying(p);
      break;
  }
}

// 0x0809c814, 0x0809c8ac: blinks out, slower each time
static void Claw_Die(struct Claw* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 2) {
    hide(s, ENTITY_EXIT);
    return;
  }
  if (s->mode[1] != 0xFF) {
    EXIT_BODY(p);
    s->work[2] = 0;
    p->blink = 1;
    s->mode[1] = 0xFF;
  }
  if (s->work[0] == 1) {
    if (p->spin <= 0x2FF + 0x200) {
      p->spin = 0x300;
    } else {
      p->spin -= 0x200;
    }
    s->angle += p->spin >> 8;
  }
  if (++s->work[2] > p->blink >> 2) {
    s->flags |= DISPLAY;
    if (p->blink < 255) p->blink++;
    if (p->blink == (s->work[0] ? 12 : 8)) {
      hide(s, ENTITY_EXIT);
    } else {
      s->work[2] = 0;
    }
  } else {
    s->flags &= ~DISPLAY;
  }
}

// --------------------------------------------

/*
  Zero 2's projectile 17, his slashes.
  work0:
    0: Combo's, flies straight on
    1: Spin's, runs along the car either way, work1 which, falls off its end
*/

static void Slash_Init(struct Entity* s);
static void Slash_Update(struct Entity* s);

// clang-format off
const ProjectileRoutine gApZ2PanterSlashRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Slash_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Slash_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

static const struct Collision sSlash[2][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
        {DRP, FACTION_ENEMY, 0, 5, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    },
};
// clang-format on

// 0x0809cad0
struct Entity* ApZ2CreatePanterSlash(struct Entity* boss, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_PANTER_SLASH);
    p->unk_28 = boss;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x0809cb2c
static void Slash_Init(struct Entity* s) {
  bool8 right = (s->unk_28->flags & X_FLIP) != 0;
  s->texture = TEXTURE_AP_SHEET;
  InitNonAffineMotion(s);
  if (s->work[0] == 0) {
    s->palID = 1;
    SetMotion(s, SHEET(0));
    s->d.x = right ? 0x400 : -0x400;
  } else {
    SetMotion(s, SHEET(5));
    s->d.x = s->work[1] ? 0x800 : -0x800;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  }
  s->d.y = 0;
  s->flags |= DISPLAY | FLIPABLE | COLLIDABLE;
  s->work[2] = 0;
  INIT_BODY(s, sSlash[s->work[0]], 4, NULL);
  SET_PROJECTILE_ROUTINE(s, ENTITY_UPDATE);
  Slash_Update(s);
}

// 0x0809cbfc, 0x0809cc80, 0x0809ccec
static void Slash_Update(struct Entity* s) {
  struct Panter* boss = (struct Panter*)s->unk_28;
  if ((boss->s).mode[0] > ENTITY_UPDATE) {
    s->flags &= ~DISPLAY;
    EXIT_BODY(s);
    s->mode[0] = ENTITY_EXIT;
    return;
  }
  if (s->work[0] == 0) {
    if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0xF000) {
      hide(s, ENTITY_DISAPPEAR);
      return;
    }
    UpdateSpriteAnimation(s);
    s->coord.x += s->d.x;
    return;
  }
  UpdateSpriteAnimation(s);
  if (++s->work[2] > 23) {
    hide(s, ENTITY_DISAPPEAR);
    return;
  }
  s->coord.x += boss->slide;
  if (s->mode[1] == 0) {
    s->coord.x += s->d.x;
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8))) return;
    if (s->d.x < 0) {
      s->coord.x = FUN_0800a22c(s->coord.x, s->coord.y + PIXEL(8));
    } else {
      s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y + PIXEL(8));
    }
    s->d.y = 0x800;
    s->mode[1]++;
  } else {
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y)) hide(s, ENTITY_DISAPPEAR);
  }
}

// --------------------------------------------

/*
  Zero 2's VFX 29, claws in his hands.
  work0:
    0: Combo's, work1 which hand
    1: Spin's
    2: Spin's whirl
    3: Back from a throw, shrinks away, work1 which hand
*/

struct Held {
  struct Entity s;
  u8 blink;  // 0x74
  u8 _75[15];
};
static_assert(sizeof(struct Held) == sizeof(struct VFX));

static void Held_Init(struct Held* p);
static void Held_Update(struct Held* p);
static void Held_Die(struct Held* p);

// clang-format off
const VFXRoutine gApZ2PanterHeldRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Held_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Held_Update,
    [ENTITY_DIE] =       (VFXFunc)Held_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b4a68
struct Entity* ApZ2CreatePanterHeld(struct Entity* boss, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_PANTER_HELD);
    p->unk_28 = boss;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x080b4ac4
static void Held_Init(struct Held* p) {
  struct Entity* s = &p->s;
  bool8 right = (s->unk_28->flags & X_FLIP) != 0;
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 3) {
    s->palID = 1;
    InitScalerotMotion1(s);
  } else {
    if (s->work[0] == 0) s->palID = 1;
    InitNonAffineMotion(s);
  }
  SET_XFLIP(p, right);
  switch (s->work[0]) {
    case 0:
    case 1:
      SetMotion(s, SHEET(0));
      break;
    case 2:
      (s->spr).oam.priority = 1;
      SetMotion(s, SHEET(3));
      break;
    case 3:
      (s->spr).oam.priority = 1;
      SetMotion(s, SHEET(2));
      p->blink = 1;
      break;
  }
  s->work[2] = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Held_Update(p);
}

static bool8 letGoOf(struct Entity* boss) { return boss->mode[1] == PANTER_STUNNED || boss->mode[0] > ENTITY_UPDATE; }

// 0x080b4ca0
static void Held_InHand(struct Held* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s8 dir = (s->flags & X_FLIP) ? 1 : -1;
  if (letGoOf(boss)) {
    CreateSmoke(2, &s->coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Held_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] != 0) return;
  s->coord.x = boss->coord.x + dir * (s->work[1] ? PIXEL(22) : -PIXEL(21));
  s->coord.y = boss->coord.y - PIXEL(20);
}

// 0x080b4d3c
static void Held_Whirl(struct Held* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (letGoOf(boss)) {
        SetMotion(s, SHEET(4));
        s->mode[1] = 2;
      } else if ((s8)(s->motion).cmdIdx == 4) {
        s->mode[1]++;
      }
      break;
    case 1:
      if (letGoOf(boss) || ++s->work[2] > 95) {
        SetMotion(s, SHEET(4));
        s->mode[1]++;
      }
      break;
    default:
      if ((s->motion).state != ANIM_END) break;
      SET_VFX_ROUTINE(p, ENTITY_DIE);
      Held_Die(p);
      break;
  }
}

// 0x080b4de4
static void Held_Back(struct Held* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s8 dir = (s->flags & X_FLIP) ? 1 : -1;
  s32 mag;
  if (letGoOf(boss)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Held_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  s->work[2]++;
  s->coord.x = boss->coord.x + dir * (s->work[1] ? PIXEL(20) : -PIXEL(15));
  s->coord.y = boss->coord.y - PIXEL(18);
  if ((s16)(s->spr).mag.x == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Held_Die(p);
    return;
  }
  mag = (s16)(s->spr).mag.x - 10;
  if (mag < 0) mag = 0;
  (s->spr).mag.x = (s->spr).mag.y = mag;
  if (s->work[2] > p->blink >> 2) {
    s->flags |= DISPLAY;
    if (p->blink < 255) {
      p->blink++;
      s->work[2] = 0;
    }
  } else {
    s->flags &= ~DISPLAY;
  }
}

static void Held_Update(struct Held* p) {
  switch ((p->s).work[0]) {
    case 0:
    case 1:
      Held_InHand(p);
      break;
    case 2:
      Held_Whirl(p);
      break;
    case 3:
      Held_Back(p);
      break;
  }
}

// 0x080b4c80
static void Held_Die(struct Held* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

/*
  Zero 2's enemy 74, his top half once cut.
  work0: slides off right
*/

static void Half_Init(struct Enemy* p);
static void Half_Update(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2PanterHalfRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Half_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Half_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEntity,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080906b0
struct Entity* ApZ2CreatePanterHalf(struct Entity* boss, const Coords32* at, u8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_PANTER_HALF);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = boss->uniqueID;
    p->unk_28 = boss;
    p->coord = *at;
    p->work[0] = right;
  }
  return p;
}

// 0x0809071c
static void Half_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  SET_XFLIP(p, s->work[0]);
  SetMotion(s, PANTER(7));
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = 72;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Half_Update(p);
}

// 0x080907b8
static void Half_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (s->mode[1] != 0) return;
  s->coord.x += ((s->flags & X_FLIP) ? -1 : 1) * s->d.x;
  s->d.x -= 2;
  if (s->d.x < 0) s->mode[1]++;
}

#endif
