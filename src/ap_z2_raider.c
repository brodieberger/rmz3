#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's enemy 31, the Bombardment Aircraft's defence raider. Appears, turns to its target firing
  shots both ways, dashes at it until a wall, then vanishes. Blows up on touch.
  work0:
    0 gone after one dash
    1 comes back near where it started
*/

struct Raider {
  OBJECT_HDR;
  u8 death;               // 0xB4
  u8 spin;                // 0xB5
  u8 aim;                 // 0xB6
  u8 beforePull;          // 0xB7
  Coords32 home;          // 0xB8
  struct Entity* target;  // 0xC0
};
static_assert(sizeof(struct Raider) == sizeof(struct Enemy));

enum {
  RAIDER_APPEAR,
  RAIDER_HOVER,
  RAIDER_TURN_LEFT,
  RAIDER_TURN_RIGHT,
  RAIDER_DASH,
  RAIDER_RIGHT_BACK,
  RAIDER_LEFT_BACK,
  RAIDER_VANISH,
  RAIDER_GONE,
  RAIDER_READY,
  RAIDER_PULLED,
  RAIDER_FALL,
  RAIDER_RECOIL,
};

enum { DEATH_BURST, DEATH_CUT, DEATH_TOUCH };

#define RAIDER(n) MOTION(AP_SHEET_Z2_RAIDER, (n))

// clang-format off
// 0x0833fc5c
static const struct Collision sBody[6] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

// 0x0833fcec, 0x0833fd40
static const struct SlashedEnemy sGibs[3] = {
    {RAIDER(4), {0xff, 0x11}, {0, 0}, {32, -832}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {RAIDER(5), {0xff, 0x11}, {0, 0}, {-384, -896}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {RAIDER(6), {0xff, 0x11}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
static const struct SlashedEnemy sCutGibs[3] = {
    {RAIDER(4), {0xff, 0x11}, {0, 0}, {48, -1664}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {RAIDER(5), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {RAIDER(6), {0xff, 0x11}, {0, 0}, {192, -1152}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

static const Coords32 sElementCoord = {0, 0};

static void Raider_Init(struct Raider* p);
static void Raider_Update(struct Raider* p);
static void Raider_Die(struct Raider* p);

// clang-format off
const EnemyRoutine gApZ2RaiderRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Raider_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Raider_Update,
    [ENTITY_DIE] =       (EnemyFunc)Raider_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static s32 scaleDown(s32 v) { return (v < 0 ? v + 255 : v) >> 8; }

// 0x08077468
struct Entity* ApZ2CreateRaider(struct Entity* target, const Coords32* at, u8 kind) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_RAIDER);
    ((struct Raider*)p)->target = target;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

// 0x08077f3c
static void onHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) s->work[3] = s->coord.x < (pZero2->s).coord.x;
}

// 0x08077f68: hangs where the rod pulls, then picks up where it was
static u16 pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  struct Raider* p = (struct Raider*)s;
  if (s->mode[1] != RAIDER_PULLED) {
    p->beforePull = s->mode[1];
    s->mode[1] = RAIDER_PULLED;
    s->mode[3] = 0;
  }
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  s->mode[1] = p->beforePull;
  return 0;
}

// 0x080774e0
static void Raider_Init(struct Raider* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->mode[2] = 0;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, FALSE);
  SetMotion(s, RAIDER(1));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->unk_2c = NULL;
  INIT_BODY(p, &sBody[2], 1, onHit);
  (p->body).unk_28 = (u32)pull;
  if (s->work[0] != 0) p->home = s->coord;
  Raider_Update(p);
}

static void burst(struct Raider* p, const struct SlashedEnemy* gibs) {
  struct Entity* s = &p->s;
  u8 flip = s->work[3] | (facingRight(s) << 4);
  Coords32 c;
  s32 i;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(12);
  for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&c, &gibs[i], 0, flip));
  c.x += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8);
  c.y += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8);
  CreateSmoke(1, &c);
  c.x += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8);
  c.y += PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8);
  CreateSmoke(2, &c);
}

// 0x0807767c
static void Raider_Die(struct Raider* p) {
  struct Entity* s = &p->s;
  PlaySound(SE_ZAKO_EXPLODE);
  switch (p->death) {
    case DEATH_BURST:
      burst(p, sGibs);
      TryDropItem(3, (struct Coord*)&s->coord);
      break;
    case DEATH_CUT:
      burst(p, sCutGibs);
      TryDropItem(3, (struct Coord*)&s->coord);
      break;
    case DEATH_TOUCH:
      burst(p, sGibs);
      break;
  }
  EXIT_BODY(p);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void die(struct Raider* p, u8 death) {
  p->death = death;
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  EXIT_BODY(p);
  Raider_Die(p);
}

typedef void (*RaiderFunc)(struct Raider*);
static const RaiderFunc sStates[12];

// 0x08077590
static void Raider_Update(struct Raider* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (ApRecoilHit((Object*)p) && s->mode[1] != RAIDER_RECOIL) s->mode[1] = RAIDER_RECOIL, s->mode[2] = 0;
  if (s->mode[1] == RAIDER_RECOIL) {
    if (ApRecoilFly((Object*)p)) die(p, DEATH_BURST);
    return;
  }
  if (status & BODY_STATUS_DEAD) {
    die(p, ((status & BODY_STATUS_SLASHED) && (status & BODY_STATUS_B15)) ? DEATH_CUT : DEATH_BURST);
    return;
  }
  if (IsFrozen(p)) return;
  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) s->mode[1] = RAIDER_FALL, s->mode[2] = 0;
  }
  if (status & BODY_STATUS_B2) {
    die(p, DEATH_TOUCH);
    return;
  }
  sStates[s->mode[1]](p);
}

// 0x08077d10: Ciel, now and then Zero
static u8 aim(struct Raider* p) {
  struct Entity* s = &p->s;
  struct Entity* t = &pZero2->s;
  if (s->work[0] == 0 && (RANDOM(RNG_0202f388) & 15) > 3) t = p->target;
  return CalcAngle(t->coord.x - s->coord.x, t->coord.y - PIXEL(8) - s->coord.y);
}

// 0x08077bb4
static void next(struct Raider* p) {
  struct Entity* s = &p->s;
  u8 turn;
  switch (s->mode[1]) {
    case RAIDER_APPEAR:
      s->mode[1] = RAIDER_HOVER;
      break;
    case RAIDER_HOVER:
      p->aim = aim(p);
      turn = p->aim + 64;
      s->mode[1] = turn < 128 ? RAIDER_TURN_LEFT : turn > 128 ? RAIDER_TURN_RIGHT : RAIDER_READY;
      break;
    case RAIDER_TURN_LEFT:
    case RAIDER_TURN_RIGHT:
      s->mode[1] = RAIDER_READY;
      break;
    case RAIDER_READY:
      s->mode[1] = RAIDER_DASH;
      break;
    case RAIDER_DASH:
      turn = p->aim + 64;
      s->mode[1] = turn < 128 ? RAIDER_LEFT_BACK : turn > 128 ? RAIDER_RIGHT_BACK : RAIDER_VANISH;
      break;
    case RAIDER_RIGHT_BACK:
    case RAIDER_LEFT_BACK:
      s->mode[1] = RAIDER_VANISH;
      break;
    case RAIDER_VANISH:
      if (s->work[0] == 0) {
        s->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      s->mode[1] = RAIDER_GONE;
      break;
    case RAIDER_GONE:
      s->coord.x = p->home.x + PIXEL((s32)((RANDOM(RNG_0202f388) & 0x7FFF) % 96) - 48);
      s->coord.y = p->home.y + PIXEL((s32)((RANDOM(RNG_0202f388) & 0x7FFF) % 96) - 48);
      s->mode[1] = RAIDER_APPEAR;
      break;
  }
  s->mode[2] = 0;
}

// 0x08077718
static void Raider_Appear(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= DISPLAY;
    SetMotion(s, RAIDER(0));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_END) next(p);
}

// 0x08077758
static void Raider_Hover(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, RAIDER(1));
    SetDDP(&p->body, sBody);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) next(p);
}

// Shots both ways every 16 frames of the turn
static void fire(struct Raider* p) {
  struct Entity* s = &p->s;
  if ((s->work[2] & 15) != 0) return;
  PlaySound(SE_ENEMY_SHOT);
  CreateLemon(&s->coord, PIXEL(2), p->spin);
  CreateLemon(&s->coord, PIXEL(2), p->spin + 128);
}

static void turn(struct Raider* p, s8 by) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (s->work[2] == 0) {
    next(p);
    return;
  }
  p->spin += by;
  s->angle = p->spin;
  s->work[2]--;
}

// 0x080777a4
static void Raider_TurnLeft(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    InitRotatableMotion(s);
    s->angle = 0;
    SetMotion(s, RAIDER(1));
    p->spin = 0;
    s->work[2] = (u8)(p->aim + 191) >> 1;
    s->mode[2]++;
  }
  fire(p);
  turn(p, 2);
}

// 0x08077844
static void Raider_TurnRight(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    InitRotatableMotion(s);
    s->angle = 0;
    SetMotion(s, RAIDER(1));
    p->spin = 0;
    s->work[2] = (u8)(0x13F - p->aim) >> 1;
    s->mode[2]++;
  }
  fire(p);
  turn(p, -2);
}

// 0x080778ec: straight on until a wall
static void Raider_Dash(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_ELECTRIC_PANTHEON);
    s->d.x = scaleDown(COS(p->aim) * 384);
    s->d.y = scaleDown(SIN(p->aim) * 384);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) next(p);
}

// 0x08077974
static void Raider_RightBack(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, RAIDER(1));
    s->work[2] = (u8)(p->aim - 64) >> 1;
    p->aim = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] == 0) {
    next(p);
    return;
  }
  s->work[2]--;
  p->spin -= 2;
  s->angle = p->spin;
}

// 0x080779cc
static void Raider_LeftBack(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, RAIDER(1));
    s->work[2] = (u8)(64 - p->aim) >> 1;
    p->aim = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] == 0) {
    next(p);
    return;
  }
  s->work[2]--;
  p->spin += 2;
  s->angle = p->spin;
}

// 0x08077a24
static void Raider_Vanish(struct Raider* p) {
  struct Entity* s = &p->s;
  bool8 right;
  if (s->mode[2] == 0) {
    right = facingRight(s);
    InitNonAffineMotion(s);
    SET_XFLIP(p, right);
    SetMotion(s, RAIDER(3));
    SetDDP(&p->body, &sBody[2]);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_END) next(p);
}

// 0x08077aa4
static void Raider_Gone(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (++s->work[2] > 31) next(p);
}

// 0x08077ad8
static void Raider_Ready(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, RAIDER(2));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 15) next(p);
}

// 0x08077b14
static void Raider_Pulled(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) s->mode[3]++;
  UpdateEntityAnim(s);
}

// 0x08077b2c: frozen, drops and bursts on the floor
static void Raider_Fall(struct Raider* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sBody[4]);
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) die(p, DEATH_BURST);
}

// 0x0833fc24
static const RaiderFunc sStates[12] = {
    Raider_Appear,    Raider_Hover,    Raider_TurnLeft, Raider_TurnRight, Raider_Dash,   Raider_RightBack,
    Raider_LeftBack,  Raider_Vanish,   Raider_Gone,     Raider_Ready,     Raider_Pulled, Raider_Fall,
};

#endif
