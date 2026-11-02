#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
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
  Zero 2's wall shell, enemy 87.
  work0:
    0: wall on its left
    1: wall on its right
    2: gun head, made by the shell
*/

struct Shell {
  OBJECT_HDR;
  u8 _b4[4];
  struct Entity* elementEffect;  // 0xB8
  s32 homeY;                     // 0xBC
  u8 headFlags;                  // 0xC0, set by head: HOLD_POSE, KNOCKBACK
  u8 flash;                      // 0xC1, head's white flash
  s16 knockback;                 // 0xC2, speed along wall when head fires
};
static_assert(sizeof(struct Shell) == sizeof(struct Enemy));

#define HOLD_POSE (1 << 0)
#define KNOCKBACK (1 << 1)

enum {
  SHELL_PATROL,
  SHELL_TURN,
  SHELL_TRACK,
  SHELL_RETURN,
  SHELL_HEAD,
  SHELL_KNOCKBACK,
  SHELL_RECOIL,
};

// What crawl() met
enum {
  CRAWL_OK,
  CRAWL_BLOCKED,   // floor or ceiling
  CRAWL_WALL_ENDS,
  CRAWL_TOO_FAR,   // more than 48 px from home and still going
};

#define ANIM(n) MOTION(AP_SHEET_Z2_SHELL, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define UPSIDE_DOWN(p) ((((struct Entity*)(p))->flags & Y_FLIP) != 0)

static const struct Collision sCollisions[2];
static const struct Collision sHarmless;
static const Coords32 sElementCoord = {PIXEL(8), 0};
static const u8 sHeadPhases[3] = {96, 4, 4};

static void Shell_Init(struct Shell* p);
static void Shell_Update(struct Shell* p);
static void Shell_Die(struct Shell* p);
static void createPieces(struct Shell* shell, Coords32* c);
static void Shell_Head(struct Shell* p);

// clang-format off
const EnemyRoutine gApZ2ShellRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Shell_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Shell_Update,
    [ENTITY_DIE] =       (EnemyFunc)Shell_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Shell* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static s32 wallFace(bool8 right, s32 x, s32 y) { return right ? FUN_0800a22c(x, y) : FUN_0800a31c(x, y); }

static s32 abs32(s32 v) { return v < 0 ? -v : v; }

// 0x080977c8: moves along wall by dy, keeping to its face
static u8 crawl(struct Shell* p, s32 dy) {
  struct Entity* s = &p->s;
  bool8 right = FACING_RIGHT(p);
  s32 oldY = s->coord.y;
  s32 r, d;
  s->coord.y += dy;
  if (s->coord.x != wallFace(right, s->coord.x, s->coord.y + (dy > 0 ? PIXEL(16) : -PIXEL(16)))) {
    s->coord.y = oldY;
    return CRAWL_WALL_ENDS;
  }
  s->coord.x = wallFace(right, s->coord.x, s->coord.y);
  r = dy > 0 ? PushoutToUp1(s->coord.x, s->coord.y + PIXEL(16)) : PushoutToDown1(s->coord.x, s->coord.y - PIXEL(16));
  if (r < 0) {
    s->coord.y += r;
    return CRAWL_BLOCKED;
  }
  d = s->coord.y - p->homeY;
  if (abs32(d) > PIXEL(48) && (dy > 0) == (d >= 0)) return CRAWL_TOO_FAR;
  return CRAWL_OK;
}

// 0x080978a0
static void crawlPose(struct Shell* p) { (p->s).work[2] = ((p->s).work[2] - 1) & 15; }

static void faceAlong(struct Shell* p, s32 dy) { SET_YFLIP(p, dy > 0); }

// 0x080978ac
static void Shell_Init(struct Shell* p) {
  struct Entity* s = &p->s;
  bool8 head = s->work[0] == 2;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(p, head ? SHELL_HEAD : SHELL_PATROL);
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.x = wallFace(s->work[0] != 0, s->coord.x, s->coord.y);
  p->homeY = s->coord.y;
  if (head) {
    InitRotatableMotion(s);
    useApSheets(p);
    (s->spr).oam.priority = 3;
  } else {
    struct Shell* h = (struct Shell*)AllocEntityLast(gEnemyHeaderPtr);
    if (h != NULL) {
      INIT_ENEMY_ROUTINE(h, ENEMY_Z2_SHELL);
      (h->s).coord.x = s->coord.x + PIXEL(16) - s->work[0] * PIXEL(32);
      (h->s).coord.y = s->coord.y;
      (h->s).work[0] = 2;
      (h->s).unk_28 = s;
    }
    INIT_BODY(p, sCollisions, 8, NULL);
    InitNonAffineMotion(s);
    useApSheets(p);
    s->work[3] = 15;
    p->headFlags = 0;
    SET_XFLIP(p, s->work[0]);
    p->elementEffect = NULL;
  }
  SET_YFLIP(p, (pZero2->s).coord.y > s->coord.y);
  SetMotion(s, ANIM(head ? 7 : 0));
  if (head) Shell_Head(p);
  Shell_Update(p);
}

static void Shell_Recoil(struct Shell* p);
static void Shell_Patrol(struct Shell* p);
static void Shell_Turn(struct Shell* p);
static void Shell_Track(struct Shell* p);
static void Shell_Return(struct Shell* p);
static void Shell_Knockback(struct Shell* p);

// Time stopped, holds still. mode[3]: 1 on first stopped frame, 2 after
static bool8 stopped(struct Shell* p, void* clock) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0 && IsFrozen(clock)) s->mode[3] = 1;
  if (s->mode[3] == 0) return FALSE;
  if (s->mode[3] == 1) {
    UpdateEntityAnim(s);
    s->mode[3] = 2;
  }
  if (!IsFrozen(clock)) s->mode[3] = 0;
  return TRUE;
}

// 0x08097a68
static void Shell_Update(struct Shell* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (s->mode[1] == SHELL_HEAD) {
    struct Shell* shell = (struct Shell*)s->unk_28;
    if ((shell->s).mode[0] > ENTITY_UPDATE) {
      s->flags &= ~(DISPLAY | FLIPABLE);
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    if (stopped(p, shell)) return;
    if (shell->elementEffect == NULL) Shell_Head(p);
    return;
  }

  if (ApRecoilHit((Object*)p) && s->mode[1] != SHELL_RECOIL) setMode(p, SHELL_RECOIL);
  if (s->mode[1] == SHELL_RECOIL) {
    Shell_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Shell_Die(p);
    return;
  }

  if (stopped(p, p)) {
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  // Burning or frozen, stops and keeps its speed for after
  if (p->elementEffect != NULL) {
    if (IsDead(p->elementEffect)) {
      SetDDP(&p->body, sCollisions);
      p->elementEffect = NULL;
      s->d.y = s->unk_coord.y;
    }
    return;
  }

  if (p->headFlags & KNOCKBACK) {
    p->headFlags &= ~KNOCKBACK;
    setMode(p, SHELL_KNOCKBACK);
  }
  if (p->headFlags & HOLD_POSE) {
    s->work[2] = 4;
  } else {
    SetMotion(s, ANIM(s->work[2] >> 2));
  }
  switch (s->mode[1]) {
    case SHELL_PATROL: Shell_Patrol(p); break;
    case SHELL_TURN: Shell_Turn(p); break;
    case SHELL_TRACK: Shell_Track(p); break;
    case SHELL_RETURN: Shell_Return(p); break;
    case SHELL_KNOCKBACK: Shell_Knockback(p); break;
  }
  if (status & BODY_STATUS_WHITE) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->elementEffect != NULL) {
      SetDDP(&p->body, &sHarmless);
      s->unk_coord.y = s->d.y;
      s->d.y = 0;
    }
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Shell_Recoil(struct Shell* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Shell_Die(p);
  }
}

// 0x08097cbc: turns when it can go no farther
static void Shell_Patrol(struct Shell* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = UPSIDE_DOWN(p) ? 0xC0 : -0xC0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (abs32((pZero2->s).coord.y - s->coord.y) <= 0x1FFF) {
    setMode(p, SHELL_TRACK);
  } else if (crawl(p, s->d.y) != CRAWL_OK) {
    setMode(p, SHELL_TURN);
  } else {
    crawlPose(p);
  }
}

// 0x08097d44
static void Shell_Turn(struct Shell* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[3] = 16;
    s->mode[2]++;
  }
  if (--s->work[3] == 0) {
    SET_YFLIP(p, !UPSIDE_DOWN(p));
    setMode(p, SHELL_PATROL);
  }
  UpdateEntityAnim(s);
}

// 0x08097db0: keeps 32 px above or below Zero, until he is 48 px away
static void Shell_Track(struct Shell* p) {
  struct Entity* s = &p->s;
  s32 zy = (pZero2->s).coord.y;
  s32 target;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateEntityAnim(s);
  if (abs32(zy - s->coord.y) > PIXEL(48)) {
    setMode(p, SHELL_RETURN);
    return;
  }
  target = zy + PIXEL(32) - (zy - s->coord.y > 0 ? PIXEL(64) : 0);
  s->d.y = 0;
  if (abs32(s->coord.y - target) > PIXEL(2)) s->d.y = s->coord.y > target ? -PIXEL(1) : PIXEL(1);
  faceAlong(p, s->d.y);
  if (crawl(p, s->d.y) == CRAWL_OK && s->d.y != 0) crawlPose(p);
}

// 0x08097ea8
static void Shell_Return(struct Shell* p) {
  struct Entity* s = &p->s;
  s32 d = p->homeY - s->coord.y;
  u8 r;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateEntityAnim(s);
  if (abs32(d) <= PIXEL(2)) {
    setMode(p, SHELL_PATROL);
    return;
  }
  s->d.y = d < 0 ? -PIXEL(1) : PIXEL(1);
  faceAlong(p, s->d.y);
  r = crawl(p, s->d.y);
  if (r == CRAWL_OK || r == CRAWL_TOO_FAR) crawlPose(p);
}

// 0x08098174: pushed back along wall by its own shot
static void Shell_Knockback(struct Shell* p) {
  struct Entity* s = &p->s;
  u8 r;
  if (s->mode[2] == 0) {
    s->d.y = p->knockback;
    s->work[3] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[3] == 0) {
    setMode(p, SHELL_PATROL);
    return;
  }
  faceAlong(p, s->d.y);
  r = crawl(p, s->d.y);
  if (r == CRAWL_WALL_ENDS) {
    s->coord.y -= s->d.y;
  } else if (r != CRAWL_BLOCKED) {
    crawlPose(p);
  }
  s->d.y /= 2;
}

// 0x08097f54: head. Only counts down to firing while on screen.
static void Shell_Head(struct Shell* p) {
  struct Entity* s = &p->s;
  struct Shell* shell = (struct Shell*)s->unk_28;
  bool8 right;
  u8 a;
  if ((shell->body).status & BODY_STATUS_WHITE) {
    p->flash = 3;
    PaintEntityWhite(s);
  }
  if (p->flash != 0 && --p->flash == 0) UpdateEntityPaletteID(s);
  if (s->mode[2] == 0) {
    s->work[2] = 85;
    s->work[3] = 0;
    p->headFlags = 0;
    SetMotion(s, ANIM(7));
    SET_XFLIP(p, FALSE);
    SET_YFLIP(p, FALSE);
    s->mode[2]++;
  }
  right = FACING_RIGHT(shell);
  s->coord.x = (shell->s).coord.x + PIXEL(16) - (right ? PIXEL(32) : 0x20);
  s->coord.y = (shell->s).coord.y;
  a = ArcTan2(((pZero2->s).coord.x - s->coord.x) >> 8, ((pZero2->s).coord.y - s->coord.y - PIXEL(24)) >> 8) >> 8;
  if (right) {
    if (a > 176) a = 176;
    if (a < 80) a = 80;
  } else {
    if ((u8)(a + 127) <= 78) a = 208;
    if ((u8)(a - 49) <= 79) a = 48;
  }
  s->angle = a;
  if (s->work[3] == 1) {
    if (s->work[2] == 0) {
      Coords32 c;
      s16 up = SIN(a) * 16;
      c.x = s->coord.x + COS(a) * 16;
      c.y = s->coord.y + up;
      PlaySound(SE_ENEMY_SHOT);
      CreateLemon(&c, 0x1C0, a + 128);
      SetMotion(&shell->s, ANIM(4));
      shell->headFlags |= KNOCKBACK;
      shell->knockback = -up >> 2;
    }
    shell->headFlags |= HOLD_POSE;
  } else {
    shell->headFlags &= ~HOLD_POSE;
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) == 0 || s->work[3] != 0) {
    if (++s->work[2] > sHeadPhases[s->work[3]]) {
      s->work[2] = 0;
      if (++s->work[3] == 3) s->work[3] = 0;
      SetMotion(s, ANIM(7 + s->work[3]));
    }
  }
  UpdateEntityAnim(s);
}

// 0x0809821c
static void Shell_Die(struct Shell* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  c.x = s->coord.x + (FACING_RIGHT(p) ? -PIXEL(8) : PIXEL(8));
  c.y = s->coord.y;
  createPieces(p, &c);
  CreateSmoke(1, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(3, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Pieces, Zero 2's VFX 69. Facing passed in work[3].

static void Piece_Init(struct VFX* p);
static void Piece_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2ShellPieceRoutine = {
    [ENTITY_INIT] =      Piece_Init,
    [ENTITY_UPDATE] =    Piece_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080be7b8
static void createPieces(struct Shell* shell, Coords32* c) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_SHELL_PIECE);
      (p->s).work[1] = i;
      (p->s).work[3] = FACING_RIGHT(shell);
      (p->s).coord = *c;
    }
  }
}

// 0x080be8a4
static void Piece_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3];
  s->flags |= DISPLAY;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, right);
  SetMotion(s, ANIM(10 + s->work[1]));
  s->d.x = (1 - right * 2) * (s32)(RANDOM(RNG_0202f388) & 0x1FF);
  s->d.y = RANDOM(RNG_0202f388) & 0x1FF;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Piece_Update(p);
}

// 0x080be974
static void Piece_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  UpdateEntityAnim(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    CreateSmoke(3, &s->coord);
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
  }
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x03, 0, 0, 1, 0x00000001, {0xa00, 0x0, 0x1400, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x03, 0, 0, 0, 0x00000000, {0xa00, 0x0, 0x1400, 0x1800}},
};

static const struct Collision sHarmless =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0, 0, 0, 0x00000000, {0xa00, 0x0, 0x1400, 0x1800}};
// clang-format on

#endif  // AP
