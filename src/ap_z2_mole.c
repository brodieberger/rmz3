#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's drilling mole, enemy 41.
  work0: unused
*/

struct Mole {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  s32 homeY;  // 0xB8
  s8 side;    // 0xBC, smoke side on death: 0 floor, +-1 wall
  u8 pose;    // 0xBD
  u8 _[6];
};
static_assert(sizeof(struct Mole) == sizeof(struct Enemy));

enum {
  MOLE_SEARCH,
  MOLE_HIDE,
  MOLE_FLOOR_PEEK,
  MOLE_FLOOR_EMERGE,
  MOLE_FLOOR_SINK,
  MOLE_FLOOR_OUT,
  MOLE_FLOOR_SHOOT,
  MOLE_WALL_PEEK,
  MOLE_WALL_EMERGE,
  MOLE_WALL_SINK,
  MOLE_WALL_OUT,
  MOLE_WALL_SHOOT,
  MOLE_RECOIL,
};

// Each pose has own hitbox and element point
enum {
  POSE_FLOOR,
  POSE_FLOOR_MOVING,
  POSE_WALL,
  POSE_WALL_MOVING,
  POSE_HIDDEN,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_MOLE, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

static const struct Collision sCollisions[5][2];
static const struct Collision sHarmless[5][2];
static const Coords32 sElementCoords[5];
static const struct SlashedEnemy sFloorDirt;
static const struct SlashedEnemy sWallDirt;

static void Mole_Init(struct Mole* p);
static void Mole_Update(struct Mole* p);
static void Mole_Die(struct Mole* p);
static void createDrill(Coords32* c, bool8 right);

// clang-format off
const EnemyRoutine gApZ2MoleRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Mole_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Mole_Update,
    [ENTITY_DIE] =       (EnemyFunc)Mole_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Mole* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void setPose(struct Mole* p, u8 pose) {
  p->pose = pose;
  SetDDP(&p->body, sCollisions[pose]);
}

static void faceZero(struct Mole* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

// 0x0807c060: mole spawning in stopped time is not there
static void Mole_Init(struct Mole* p) {
  struct Entity* s = &p->s;
  if (IsFrozen(p)) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  faceZero(p);
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  p->side = 0;
  p->pose = POSE_HIDDEN;
  s->unk_2c = NULL;
  INIT_BODY(p, sCollisions[POSE_HIDDEN], 4, NULL);
  Mole_Update(p);
}

static void Mole_Recoil(struct Mole* p);
static void Mole_Search(struct Mole* p);
static void Mole_Hide(struct Mole* p);
static void Mole_FloorPeek(struct Mole* p);
static void Mole_FloorEmerge(struct Mole* p);
static void Mole_FloorSink(struct Mole* p);
static void Mole_FloorOut(struct Mole* p);
static void Mole_FloorShoot(struct Mole* p);
static void Mole_WallPeek(struct Mole* p);
static void Mole_WallEmerge(struct Mole* p);
static void Mole_WallSink(struct Mole* p);
static void Mole_WallOut(struct Mole* p);
static void Mole_WallShoot(struct Mole* p);

// 0x0807c1d0
static void Mole_Update(struct Mole* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != MOLE_RECOIL) setMode(p, MOLE_RECOIL);
  if (s->mode[1] == MOLE_RECOIL) {
    Mole_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Mole_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    if (s->unk_2c != NULL) {
      s->unk_2c = NULL;
      SetDDP(&p->body, sCollisions[p->pose]);
    }
    return;
  }

  if ((status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoords[p->pose]);
    if (s->unk_2c != NULL) s->mode[3] = 0;
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) {
    s->unk_2c = NULL;
    SetDDP(&p->body, sCollisions[p->pose]);
  }

  // 0x0807cd80: harmless and still while burning or thawing
  if (s->unk_2c != NULL) {
    if (s->mode[3] == 0) {
      SetDDP(&p->body, sHarmless[p->pose]);
      s->mode[3]++;
    }
    return;
  }

  switch (s->mode[1]) {
    case MOLE_SEARCH: Mole_Search(p); break;
    case MOLE_HIDE: Mole_Hide(p); break;
    case MOLE_FLOOR_PEEK: Mole_FloorPeek(p); break;
    case MOLE_FLOOR_EMERGE: Mole_FloorEmerge(p); break;
    case MOLE_FLOOR_SINK: Mole_FloorSink(p); break;
    case MOLE_FLOOR_OUT: Mole_FloorOut(p); break;
    case MOLE_FLOOR_SHOOT: Mole_FloorShoot(p); break;
    case MOLE_WALL_PEEK: Mole_WallPeek(p); break;
    case MOLE_WALL_EMERGE: Mole_WallEmerge(p); break;
    case MOLE_WALL_SINK: Mole_WallSink(p); break;
    case MOLE_WALL_OUT: Mole_WallOut(p); break;
    case MOLE_WALL_SHOOT: Mole_WallShoot(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Mole_Recoil(struct Mole* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Mole_Die(p);
  }
}

static bool8 nearHome(struct Mole* p, s32 x, s32 y) {
  return (u32)(x - p->homeX + PIXEL(128)) <= PIXEL(256) && (u32)(y - p->homeY + PIXEL(48)) <= PIXEL(96);
}

static bool8 solid(s32 x, s32 y) { return FUN_080098a4(x, y) != 0; }

// Wall face at x, back to Zero (dir +1: wall to his right). Hole nudged up or down once if wall
// doesn't cover 16 px above and below.
static bool8 tryWall(struct Mole* p, s32 x, s32 y, s32 dir) {
  struct Entity* s = &p->s;
  u8 moved = 0;
  s->coord.x = x;
  s->coord.y = y;
  if (!solid(x + dir * PIXEL(8), y - PIXEL(16))) {
    s->coord.y = FUN_08009f6c(x + dir * PIXEL(8), y - PIXEL(16)) + PIXEL(16);
    moved = 1;
  }
  if (!solid(s->coord.x + dir * PIXEL(8), s->coord.y + PIXEL(16))) {
    s->coord.y = FUN_0800a134(s->coord.x + dir * PIXEL(8), s->coord.y + PIXEL(16)) - PIXEL(16);
    moved++;
  }
  return moved != 2;
}

// Floor spot, needs floor and no wall 16 px either side. Nudged sideways once if not.
static bool8 tryFloor(struct Mole* p, s32 x, s32 y) {
  struct Entity* s = &p->s;
  u8 moved = 0;
  s->coord.x = x;
  s->coord.y = y;
  if (!solid(x - PIXEL(16), y + PIXEL(8))) {
    s->coord.x = FUN_0800a22c(x - PIXEL(16), y + PIXEL(8)) + PIXEL(16);
    moved = 1;
  } else if (solid(x - PIXEL(16), y - PIXEL(8))) {
    s->coord.x = FUN_0800a31c(x - PIXEL(16), y - PIXEL(8)) + PIXEL(16);
    moved = 1;
  }
  if (!solid(s->coord.x + PIXEL(16), s->coord.y + PIXEL(8))) {
    s->coord.x = FUN_0800a31c(s->coord.x + PIXEL(16), s->coord.y + PIXEL(8)) - PIXEL(16);
    moved++;
  } else if (solid(s->coord.x + PIXEL(16), s->coord.y - PIXEL(8))) {
    s->coord.x = FUN_0800a22c(s->coord.x + PIXEL(16), s->coord.y - PIXEL(8)) - PIXEL(16);
    moved++;
  }
  return moved != 2;
}

// Floor near home, level with Zero within 16 px
static bool8 floorFits(struct Mole* p, s32 x, s32 y, s32 zeroY) {
  return nearHome(p, x, y) && (u32)(y - (zeroY + PIXEL(10)) + PIXEL(16)) <= PIXEL(32);
}

// 0x0807c390: measures from 16 px above Zero's feet
static void Mole_Search(struct Mole* p) {
  struct Entity* s = &p->s;
  s32 zx = (pZero2->s).coord.x;
  s32 zy = (pZero2->s).coord.y - PIXEL(16);
  s32 x, y, ahead;

  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    setPose(p, POSE_HIDDEN);
    s->mode[2]++;
  }
  if (!nearHome(p, zx, zy)) return;

  x = FUN_0800a22c(zx, zy);
  if (nearHome(p, x, zy) && (u32)(x - zx + PIXEL(32)) > PIXEL(64) && (u32)(x - zx + PIXEL(64)) <= PIXEL(128) &&
      zx < x && tryWall(p, x, zy, 1)) {
    SET_XFLIP(p, FALSE);
    setMode(p, MOLE_WALL_PEEK);
    return;
  }
  x = FUN_0800a31c(zx, zy);
  if (nearHome(p, x, zy) && (u32)(x - zx + PIXEL(32)) > PIXEL(64) && (u32)(x - zx + PIXEL(64)) <= PIXEL(128) &&
      x < zx && tryWall(p, x, zy, -1)) {
    SET_XFLIP(p, TRUE);
    setMode(p, MOLE_WALL_PEEK);
    return;
  }

  ahead = ((RANDOM(RNG_0202f388) & 7) << 11) + PIXEL(32);
  y = FUN_08009f6c(zx + ahead, zy);
  if (!(floorFits(p, zx + ahead, y, zy) && tryFloor(p, zx + ahead, y))) {
    y = FUN_08009f6c(zx - ahead, zy);
    if (!(floorFits(p, zx - ahead, y, zy) && tryFloor(p, zx - ahead, y))) return;
  }
  faceZero(p);
  setMode(p, MOLE_FLOOR_PEEK);
}

// 0x0807c8fc: hidden until work[2] passes 63, counting on from previous state
static void Mole_Hide(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    setPose(p, POSE_HIDDEN);
    s->mode[2]++;
  }
  if (++s->work[2] > 63) setMode(p, MOLE_SEARCH);
}

// 0x0807c944: drill pokes out of floor for 32 frames
static void Mole_FloorPeek(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= DISPLAY;
    SetMotion(s, ANIM(8));
    p->side = 0;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_FLOOR_EMERGE);
}

// 0x0807c994
static void Mole_FloorEmerge(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_MOLE_DRILL);
    SetMotion(s, ANIM(0));
    setPose(p, POSE_FLOOR_MOVING);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).cmdIdx == 1 && s->work[2] == 0) {
    s32 i;
    for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&s->coord, &sFloorDirt, 0, i & 1));
    s->work[2]++;
  }
  if (IsSpriteAnimEnd(s)) setMode(p, MOLE_FLOOR_OUT);
}

// 0x0807ca28
static void Mole_FloorSink(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(1));
    setPose(p, POSE_FLOOR_MOVING);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(p, MOLE_HIDE);
}

// 0x0807ca78
static void Mole_FloorOut(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(4));
    setPose(p, POSE_FLOOR);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_FLOOR_SHOOT);
}

// 0x0807cacc
static void Mole_FloorShoot(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    Coords32 c;
    SetMotion(s, ANIM(5));
    c.x = s->coord.x + (FACING_RIGHT(p) ? PIXEL(14) : -PIXEL(14));
    c.y = s->coord.y - PIXEL(10);
    createDrill(&c, FACING_RIGHT(p));
    PlaySound(SE_ENEMY_BOMB);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_FLOOR_SINK);
}

// 0x0807cb54: wall versions, same turned sideways
static void Mole_WallPeek(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= DISPLAY;
    SetMotion(s, ANIM(9));
    p->side = FACING_RIGHT(p) ? 1 : -1;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_WALL_EMERGE);
}

// 0x0807cbb8
static void Mole_WallEmerge(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_MOLE_DRILL);
    SetMotion(s, ANIM(2));
    setPose(p, POSE_WALL_MOVING);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).cmdIdx == 1 && s->work[2] == 0) {
    s32 i;
    for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&s->coord, &sWallDirt, 0, !FACING_RIGHT(p)));
    s->work[2]++;
  }
  if (IsSpriteAnimEnd(s)) setMode(p, MOLE_WALL_OUT);
}

// 0x0807cc5c
static void Mole_WallSink(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(3));
    setPose(p, POSE_WALL_MOVING);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(p, MOLE_HIDE);
}

// 0x0807ccac
static void Mole_WallOut(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(6));
    setPose(p, POSE_WALL);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_WALL_SHOOT);
}

// 0x0807cd00
static void Mole_WallShoot(struct Mole* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    Coords32 c;
    SetMotion(s, ANIM(7));
    c.x = s->coord.x + (FACING_RIGHT(p) ? PIXEL(22) : -PIXEL(22));
    c.y = s->coord.y;
    createDrill(&c, FACING_RIGHT(p));
    PlaySound(SE_ENEMY_BOMB);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 31) setMode(p, MOLE_WALL_SINK);
}

// 0x0807c2d4
static void Mole_Die(struct Mole* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  c.x = s->coord.x + (p->side << 11) + (((RANDOM(RNG_0202f388) & 7) - 3) << 8);
  c.y = s->coord.y - PIXEL(15) + ((RANDOM(RNG_0202f388) & 7) << 8);
  CreateSmoke(1, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(3, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Drill bit, Zero 2's projectile 39

static const struct Collision sDrill[2];

static void Drill_Init(struct Entity* p);
static void Drill_Update(struct Entity* p);
static void Drill_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2MoleDrillRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Drill_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Drill_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Drill_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a4b98
static void createDrill(Coords32* c, bool8 right) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_MOLE_DRILL);
    p->coord = *c;
    p->work[1] = right;
  }
}

// 0x080a4bec
static void Drill_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  useApSheets(p);
  SET_XFLIP(p, p->work[1]);
  SetMotion(p, ANIM(10));
  p->flags |= DISPLAY | FLIPABLE;
  p->d.x = (p->work[1] * 2 - 1) * 0x280;
  p->work[2] = 128;
  INIT_BODY(p, sDrill, 3, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Drill_Update(p);
}

static void explode(struct Entity* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Drill_Die(p);
}

// 0x080a4c98
static void Drill_Update(struct Entity* p) {
  u32 status = ((Object*)p)->body.status;
  if (status & BODY_STATUS_DEAD) {
    explode(p);
    return;
  }
  UpdateEntityAnim(p);
  if (--p->work[2] == 0) {
    explode(p);
    return;
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &p->coord) > PIXEL(32)) {
    p->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (status & BODY_STATUS_B2) {
    explode(p);
    return;
  }
  p->coord.x += p->d.x;
  if (FUN_080098a4(p->coord.x, p->coord.y) != 0) explode(p);
}

// 0x080a4d9c
static void Drill_Die(struct Entity* p) {
  PlaySound(SE_UNK_35);
  CreateSmoke(2, &p->coord);
  p->flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[5][2] = {
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, -0x800, 0x1400, 0x1000}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x800, 0x1400, 0x1000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, -0x400, 0x1400, 0x800}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x400, 0x1400, 0x800}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {-0x800, 0x0, 0x1000, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x800, 0x0, 0x1000, 0x1400}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {-0x400, 0x0, 0x800, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x400, 0x0, 0x800, 0x1400}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    },
};

static const struct Collision sHarmless[5][2] = {
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x800, 0x1400, 0x1000}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x800, 0x1400, 0x1000}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x400, 0x1400, 0x800}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x400, 0x1400, 0x800}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x800, 0x0, 0x1000, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x800, 0x0, 0x1000, 0x1400}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x400, 0x0, 0x800, 0x1400}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {-0x400, 0x0, 0x800, 0x1400}},
    },
    {
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
        {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    },
};

static const Coords32 sElementCoords[5] = {
    {0, -0x800},
    {0, -0x400},
    {-0x800, 0},
    {-0x400, 0},
    {0, 0},
};

static const struct Collision sDrill[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};

static const struct SlashedEnemy sFloorDirt =
    {MOTION(AP_SHEET_Z2_MOLE, 11), {0x60, 0x20}, {0, 0}, {0, -1280}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}};

static const struct SlashedEnemy sWallDirt =
    {MOTION(AP_SHEET_Z2_MOLE, 11), {0x60, 0x20}, {0, 0}, {64, -128}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}};
// clang-format on

#endif  // AP
