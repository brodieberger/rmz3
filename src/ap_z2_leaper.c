#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's leaper, enemy 56.
  work0:
    0: unseen launcher, sends a leaper whenever the last is gone
    1: leaper
  work1:
    0: jumps 112 px
    1: jumps 192 px
*/

struct Leaper {
  OBJECT_HDR;
  s32 startY;            // 0xB4
  struct Leaper* child;  // 0xB8, launcher's leaper
  bool8 landed;          // 0xBC
  u8 _[7];
};
static_assert(sizeof(struct Leaper) == sizeof(struct Enemy));

#define ANIM(n) MOTION(AP_SHEET_Z2_LEAPER, n)

static const struct Collision sCollisions[2];
static const struct Collision sHarmless[2];
static const Coords32 sElementCoord = {0, 0};

static void Leaper_Init(struct Leaper* p);
static void Leaper_Update(struct Leaper* p);
static void Leaper_Die(struct Leaper* p);

// clang-format off
const EnemyRoutine gApZ2LeaperRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Leaper_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Leaper_Update,
    [ENTITY_DIE] =       (EnemyFunc)Leaper_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

// 0x080863b4
static struct Leaper* launch(struct Leaper* launcher) {
  struct Leaper* p = (struct Leaper*)AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_LEAPER);
    (p->s).coord = (launcher->s).coord;
    (p->s).work[0] = 1;
    (p->s).work[1] = (launcher->s).work[1];
  }
  return p;
}

static void Leaper_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = (p->coord).x < (pZero2->s).coord.x;
  }
}

// 0x08086418
static void Leaper_Init(struct Leaper* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = 0;
  if (s->work[0] == 0) {
    p->child = launch(p);
    s->work[2] = 64;
    Leaper_Update(p);
    return;
  }
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
  SetMotion(s, ANIM(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  p->startY = s->coord.y;
  INIT_BODY(p, sCollisions, 4, Leaper_OnCollision);
  s->work[2] = 0;
  s->unk_2c = NULL;
  p->landed = FALSE;
  s->d.y = -(u16)Sqrt(s->work[1] == 0 ? 0x380000 : 0x600000);
  Leaper_Update(p);
}

// 0x080866f4
static void Launcher_Update(struct Leaper* p) {
  struct Entity* s = &p->s;
  if (s->work[2] != 0) s->work[2]--;
  if (p->child != NULL) {
    if ((p->child->s).mode[0] <= ENTITY_UPDATE) return;
    if (!p->child->landed) s->work[2] = 64;  // shot down, wait before next
    p->child = NULL;
    return;
  }
  if (s->work[2] == 0) {
    p->child = launch(p);
    s->work[2] = 64;
  }
}

// 0x08086568
static void Leaper_Update(struct Leaper* p) {
  struct Entity* s = &p->s;

  if (s->work[0] == 0) {
    Launcher_Update(p);
    return;
  }

  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Leaper_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) {
      SetMotion(s, ANIM(1));
      SetDDP(&p->body, sHarmless);
      s->d.y = 0;
      s->mode[1] = 1;  // holds frame from here on
    }
  }
  if (s->mode[1] == 0) UpdateEntityAnim(s);

  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (s->work[2] == 0 && s->d.y > 0xFF) {
    SetMotion(s, ANIM(1));
    s->work[2]++;
  }

  if (s->coord.y >= p->startY) {
    p->landed = TRUE;
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// 0x08086794
static void Leaper_Die(struct Leaper* p) {
  Coords32 c;
  PlaySound(SE_ZAKO_EXPLODE);
  c.x = (p->s).coord.x + (((RANDOM(RNG_0202f388) & 7) - 3) << 8);
  c.y = (p->s).coord.y + (((RANDOM(RNG_0202f388) & 7) - 3) << 8);
  CreateSmoke(1, &c);
  TryDropItem(0, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

#endif  // AP
