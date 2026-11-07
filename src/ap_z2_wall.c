#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "palette_animation.h"
#include "projectile.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's boss 18, Jungle's mid-boss.
  Parts: solids 10 and 11, enemy 54
  Frogs: enemy 52
  Rings: projectile 44
*/

struct Wall {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  bool8 open;     // 0xBC
  u8 turn;        // 0xBD
  u8 _be[2];
  s32 flood;      // 0xC0, frames until the water falls
  u8 _c4[32];
};
static_assert(sizeof(struct Wall) == sizeof(struct Boss));

enum { WALL_WAIT, WALL_READY, WALL_NOP, WALL_OPEN, WALL_REST, WALL_FROG, WALL_AIM, WALL_RING, WALL_FLOOD };

#define BODY(n) MOTION(AP_SHEET_Z2_WALL, (n))
#define SHOT(n) MOTION(AP_SHEET_Z2_WALL_SHOT, (n))
#define PART(n) MOTION(AP_SHEET_Z2_WALL_PART, (n))
#define SPIKE(n) MOTION(AP_SHEET_Z2_WALL_SPIKE, (n))
#define SHELF(n) MOTION(AP_SHEET_Z2_WALL_SHELF, (n))

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define LENS_PALETTE 736

extern const PlttAnimData gApZ2Jungle_PlttAnim141, gApZ2Jungle_PlttAnim142, gApZ2Jungle_PlttAnim143;
extern const AnimCmd* const gApZ2Jungle_PlttAnimScript141[], *const gApZ2Jungle_PlttAnimScript142[],
    *const gApZ2Jungle_PlttAnimScript143[];

#define WALL_PARENT(s) ((struct Wall*)(s)->unk_28)
#define WALL_ALIVE(s) ((s)->unk_28->mode[0] < ENTITY_DIE)

static const struct Collision sCollisions[2];
static const struct Collision sOpenCollisions[2];
static const struct Collision sHurtCollisions[2];
static const struct Collision sShelfCollision;
static const struct Collision sFrogCollisions[2];
static const struct Collision sRingCollisions[2];
static const struct Rect sShelfSize = {0, 3072, 24576, 6144};
static const struct Rect sSpikeSize = {0, -3072, -24576, 6144};

#define ARM_TILE 512
#define PART_TILE (ARM_TILE + AP_SHEET_Z2_WALL_SPLASH_TILES)
#define BODY_TILE (PART_TILE + AP_SHEET_Z2_WALL_PART_TILES)
#define SPIKE_TILE (BODY_TILE + AP_SHEET_Z2_WALL_TILES)
#define SHOT_TILE (SPIKE_TILE + AP_SHEET_Z2_WALL_SPIKE_TILES)
#define SHELF_TILE (SHOT_TILE + AP_SHEET_Z2_WALL_SHOT_TILES)

static const struct PreloadEntity sSheets[6] = {
    {AP_SHEET_Z2_WALL_ARM, 0, ARM_TILE, 6, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_WALL_PART, 0, PART_TILE, 6, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_WALL, 0, BODY_TILE, 7, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_WALL_SPIKE, 0, SPIKE_TILE, 8, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_WALL_SHOT, 0, SHOT_TILE, 5, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_WALL_SHELF, 0, SHELF_TILE, 9, 0, AP_PRELOAD_SHEET, 0},
};
static const struct PreloadEntity sSplashSheet = {AP_SHEET_Z2_WALL_SPLASH, 0, ARM_TILE, 4, 0, AP_PRELOAD_SHEET, 0};
static_assert(SHELF_TILE + AP_SHEET_Z2_WALL_SHELF_TILES <= 1024);

static void Wall_Init(struct Wall* p);
static void Wall_Update(struct Wall* p);
static void Wall_Die(struct Wall* p);

// clang-format off
const BossRoutine gApZ2WallRoutine = {
    [ENTITY_INIT] =      (BossFunc)Wall_Init,
    [ENTITY_UPDATE] =    (BossFunc)Wall_Update,
    [ENTITY_DIE] =       (BossFunc)Wall_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setUp(struct Entity* s, motion_t m) {
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, m);
  UpdateEntityAnim(s);
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void createPart(u8 id, struct Entity* wall, u8 kind) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, id);
    p->unk_28 = wall;
    p->work[0] = kind;
  }
}

static void createEye(struct Entity* wall) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_WALL_EYE);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = wall;
  }
}

static void createFrog(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_WALL_FROG);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *at;
  }
}

static void createRing(struct Entity* parent, u8 kind, u8 dir) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_WALL_RING);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = dir;
  }
}

// 0x080608a8
static void Wall_Init(struct Wall* p) {
  struct Entity* s = &p->s;
  u8 i;
  for (i = 0; i < 6; i++) ApLoadSheet(&sSheets[i]);
  setUp(s, BODY(2));
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, 32);
  p->home = s->coord;
  p->open = FALSE;
  p->turn = 0;
  p->flood = 0;
  createPart(SOLID_Z2_WALL_SHELF, s, 0);
  createPart(SOLID_Z2_WALL_SHELF, s, 1);
  createPart(SOLID_Z2_WALL_ARM, s, 0);
  createEye(s);
  s->coord.x = p->home.x + 0x3700;
  s->coord.y = p->home.y + 0x3500;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Wall_Update(p);
}

static void Wall_Wait(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateEntityAnim(s);
  if (!(s->scriptEntity->flags & 1)) return;
  p->open = TRUE;
  setMode(s, WALL_READY);
}

static void Wall_Ready(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BODY(4));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (gStageRun.vm.active & VM_ACTIVE) return;
  s->mode[1] = WALL_REST;
  s->work[2] = 64;
}

static void Wall_Nop(struct Wall* p UNUSED) {}

// Body's palette, one frame: tells what's coming
static void tintLens(u8 attack) {
  if (attack == WALL_AIM) {
    ApStartPaletteAnimation(PLTT_ANIM_ID(141), &gApZ2Jungle_PlttAnim141, gApZ2Jungle_PlttAnimScript141, LENS_PALETTE);
    RemovePaletteAnimation(PLTT_ANIM_ID(141));
  } else if (attack == WALL_FROG) {
    ApStartPaletteAnimation(PLTT_ANIM_ID(142), &gApZ2Jungle_PlttAnim142, gApZ2Jungle_PlttAnimScript142, LENS_PALETTE);
    RemovePaletteAnimation(PLTT_ANIM_ID(142));
  } else {
    ApStartPaletteAnimation(PLTT_ANIM_ID(143), &gApZ2Jungle_PlttAnim143, gApZ2Jungle_PlttAnimScript143, LENS_PALETTE);
    RemovePaletteAnimation(PLTT_ANIM_ID(143));
  }
}

// 0x08060cf8
static void Wall_Open(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BODY(5));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).cmdIdx == 2) {
    SetDDP(&p->body, sHurtCollisions);
    if (s->mode[3] == 0) {
      static const u8 sNext[5] = {WALL_AIM, WALL_FROG, WALL_FLOOD, WALL_AIM, WALL_FROG};
      s->mode[3] = sNext[p->turn];
      tintLens(sNext[p->turn]);
    }
  } else {
    SetDDP(&p->body, sOpenCollisions);
  }
  if ((s->motion).state == ANIM_END) {
    SetDDP(&p->body, sCollisions);
    p->turn = (p->turn + 1) % 5;
    setMode(s, s->mode[3]);
  }
}

// 0x08060df4
static void Wall_Rest(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BODY(0));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (s->work[2]-- == 0) setMode(s, WALL_OPEN);
}

// 0x08060e34
static void Wall_Frog(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    Coords32 at;
    SetMotion(s, BODY(0));
    at.x = p->home.x + 0x3000;
    at.y = p->home.y + 0x7600;
    createFrog(&at);
    s->work[2] = 96;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2]-- == 0) setMode(s, WALL_REST);
}

// 0x08060eb8
static void Wall_Aim(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BODY(1));
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2]-- == 0) setMode(s, WALL_RING);
}

// 0x08060efc
static void Wall_Ring(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BODY(0));
    createRing(s, 0, RANDOM(RNG_0202f388) & 1);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2]-- == 0) setMode(s, WALL_REST);
}

// 0x08060f6c
static void Wall_Flood(struct Wall* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    gOverworld.state[0] = 1;
    s->mode[2]++;
  }
  if (gOverworld.sea >= s->coord.y - 0x1000) return;
  p->flood = RANDOM(RNG_0202f388) % 192 + 64;
  setMode(s, WALL_REST);
}

static void (*const sStates[9])(struct Wall*) = {Wall_Wait, Wall_Ready, Wall_Nop, Wall_Open, Wall_Rest,
                                                 Wall_Frog, Wall_Aim, Wall_Ring, Wall_Flood};

// 0x08060aec
static void Wall_Update(struct Wall* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Wall_Die(p);
    return;
  }
  if (p->flood != 0 && --p->flood == 0) gOverworld.state[0] = 0;
  sStates[s->mode[1]](p);
}

// 0x08060b74
static void Wall_Die(struct Wall* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (s->mode[2] == 0) {
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    s->flags &= ~COLLIDABLE;
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
      s->work[2] = 64;
      gOverworld.state[0] = 2;
      s->mode[2]++;
    }
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 3) == 0) {
    c.x = s->coord.x + ((8 - (RANDOM(RNG_0202f388) & 15)) << 8);
    c.y = s->coord.y + ((16 - (RANDOM(RNG_0202f388) & 31)) << 8);
    CreateSmoke(2, &c);
  }
  if ((s->work[2] & 15) == 0) PlaySound(SE_ZAKO_EXPLODE);
  if (s->work[2]-- == 0) gStageRun.vm.active |= VM_FLAG1;
}

// --------------------------------------------
/*
  Zero 2's solid 10.
  work0:
    0: shelf in room's floor, solid
    1: plate beside it
*/
struct ShelfSolid {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  u8 _b8[12];
};
static_assert(sizeof(struct ShelfSolid) == sizeof(struct Solid));

static void Shelf_Init(struct Solid* p);
static void Shelf_Update(struct Solid* p);
static void Shelf_Die(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2WallShelfRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Shelf_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Shelf_Update,
    [ENTITY_DIE] =       (SolidFunc)Shelf_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080cb1b0
static u16 Shelf_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy UNUSED) {
  struct ShelfSolid* f = (struct ShelfSolid*)s;
  bool8 stopped = FALSE;
  s->coord.x += dx;
  s->mode[1] = 1;
  s->work[2] = 64;
  if (s->coord.x > f->homeX + 0x3800) {
    s->coord.x = f->homeX + 0x3800;
    stopped = TRUE;
  }
  if (pulling == 0 || stopped) {
    s->mode[1] = 0;
    return 0;
  }
  return 1;
}

// 0x080cadec, 0x080caeec
static void Shelf_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Wall* wall = WALL_PARENT(s);
  if (s->work[0] == 0) {
    setUp(s, SHELF(0));
    s->flags |= COLLIDABLE;
    INIT_BODY(p, &sShelfCollision, 255, NULL);
    (p->body).unk_28 = (u32)Shelf_Pull;
    s->flags2 |= ENTI_PHYSICS;
    s->size = &sShelfSize;
    s->physicsAttr = 0x2401;
    s->coord.x = wall->home.x + 0x2000;
    s->coord.y = wall->home.y + 0x4F00;
    ((struct ShelfSolid*)p)->homeX = s->coord.x;
  } else {
    setUp(s, PART(3));
    s->coord.x = wall->home.x + 0x1000;
    s->coord.y = wall->home.y + 0x5C00;
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Shelf_Update(p);
}

// 0x080cad8c
static void Shelf_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  if (!WALL_ALIVE(s)) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Shelf_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->work[0] != 0 || s->mode[1] != 0) return;
  if (s->work[2] != 0) {
    s->work[2]--;
  } else if (s->coord.x > ((struct ShelfSolid*)p)->homeX) {
    s->coord.x -= 64;
  }
}

// 0x080caffc, 0x080cb174
static void Shelf_Die(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s32 i;
  if (s->mode[2] == 0) {
    s->work[2] = s->work[0] == 0 ? 96 : 144;
    s->mode[2]++;
  }
  if (s->work[2]-- != 0) return;
  if (s->work[0] == 0) {
    static const s16 sAlong[5] = {-0x2500, -0x1200, 0, 0x1200, 0x2500};
    for (i = 0; i < 5; i++) {
      c.x = s->coord.x + sAlong[i];
      c.y = s->coord.y + 0x600 + (RANDOM(RNG_0202f388) % 6 << 8);
      CreateSmoke(1, &c);
    }
    PlaySound(SE_ZAKO_EXPLODE);
  }
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's solid 11.
  work0:
    0: arm in floor
    1: spiked row under it
*/
struct Arm {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  u8 _bc[8];
};
static_assert(sizeof(struct Arm) == sizeof(struct Solid));

static void Arm_Init(struct Solid* p);
static void Arm_Update(struct Solid* p);
static void Arm_Die(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2WallArmRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Arm_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Arm_Update,
    [ENTITY_DIE] =       (SolidFunc)Arm_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080cb2e8, 0x080cb3ac
static void Arm_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Arm* a = (struct Arm*)p;
  struct Wall* wall = WALL_PARENT(s);
  if (s->work[0] == 0) {
    setUp(s, MOTION(AP_SHEET_Z2_WALL_ARM, 2));
    s->coord.x = wall->home.x + 0x3F00;
    s->coord.y = wall->home.y + 0x8B00;
    s->work[2] = 16;
  } else {
    setUp(s, SPIKE(0));
    s->renderPrio = 31;
    s->flags2 |= ENTI_PHYSICS;
    s->size = &sSpikeSize;
    s->physicsAttr = 15;
    s->coord.x = wall->home.x - 0x1800;
    s->coord.y = wall->home.y + 0xA000;
  }
  a->home = s->coord;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Arm_Update(p);
}

// 0x080cb488
static void armPart(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Arm* a = (struct Arm*)p;
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      if (!WALL_PARENT(s)->open) break;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    case 1:
      s->coord.y = (s->work[2] & 3) > 1 ? a->home.y : a->home.y - 0x200;
      if (s->work[2]-- != 0) break;
      PlaySound(SE_Z2_WALL_OPEN);
      s->mode[1]++;
      break;
    case 2:
      s->coord.y += 0x300;
      if (s->coord.y <= a->home.y + 0x1800) break;
      s->coord.y = a->home.y + 0x1800;
      s->work[2] = 32;
      s->mode[1]++;
      break;
    case 3:
      if (s->work[2]-- != 0) break;
      createPart(SOLID_Z2_WALL_ARM, s->unk_28, 1);
      s->mode[1]++;
      break;
    case 4:
      s->coord.x += 0x300;
      if (s->coord.x <= a->home.x + 0x9000) break;
      s->coord.x = a->home.x + 0x9000;
      s->mode[1]++;
      break;
  }
}

// 0x080cb594
static void armSpike(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Arm* a = (struct Arm*)p;
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      s->coord.x += 0x300;
      if (s->coord.x <= a->home.x + 0x7800) break;
      s->coord.x = a->home.x + 0x7800;
      s->mode[1]++;
      break;
    case 1:
      SetMotion(s, SPIKE(1));
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      break;
  }
}

// 0x080cb288
static void Arm_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  if (!WALL_ALIVE(s)) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Arm_Die(p);
    return;
  }
  if (s->work[0] == 0) {
    armPart(p);
  } else {
    armSpike(p);
  }
}

// 0x080cb624, 0x080cb63c
static void Arm_Die(struct Solid* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0 || s->mode[1] > 1) {
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's enemy 54, eye
static void Eye_Init(struct Enemy* p);
static void Eye_Update(struct Enemy* p);
static void Eye_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2WallEyeRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Eye_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Eye_Update,
    [ENTITY_DIE] =       (EnemyFunc)Eye_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08084250
static void Eye_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Wall* wall = WALL_PARENT(s);
  setUp(s, PART(1));
  s->coord.x = wall->home.x + 0xF00;
  s->coord.y = wall->home.y + 0x3200;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Eye_Update(p);
}

// 0x08084304
static void Eye_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (!WALL_ALIVE(s)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Eye_Die(p);
    return;
  }
  UpdateEntityAnim(s);
}

// 0x0808433c
static void Eye_Die(struct Enemy* p) {
  CreateSmoke(1, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's enemy 52, frog
struct Frog {
  OBJECT_HDR;
  u8 _[sizeof(struct Enemy) - sizeof(struct Solid) + 8];
};

static void Frog_Init(struct Enemy* p);
static void Frog_Update(struct Enemy* p);
static void Frog_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2WallFrogRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Frog_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Frog_Update,
    [ENTITY_DIE] =       (EnemyFunc)Frog_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08082094
static void Frog_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  setUp(s, SHOT(6));
  SET_XFLIP(p, FALSE);
  s->flags |= COLLIDABLE;
  INIT_BODY(p, sFrogCollisions, 4, NULL);
  s->d.x = 0x200;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Frog_Update(p);
}

// 0x08082204
static void Frog_Hop(struct Enemy* p) {
  struct Entity* s = &p->s;
  s32 cap;
  if (s->mode[2] == 0) {
    SetMotion(s, SHOT(6));
    s->d.y = -0x480;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  if (FUN_080098a4(s->coord.x + 0x800, s->coord.y) != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Frog_Die(p);
    return;
  }
  if (s->coord.y > gOverworld.sea) {
    s->d.y += 32;
    cap = 0x380;
  } else {
    s->d.y += 64;
    cap = 0x700;
  }
  if (s->d.y > cap) s->d.y = cap;
  s->coord.y += s->d.y;
  if (s->d.y > 0) {
    if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      setMode(s, 1);
    }
  } else if (FUN_080098a4(s->coord.x, s->coord.y - 0x1000) != 0) {
    s->d.y = -s->d.y;
  }
}

// 0x080822e4
static void Frog_Land(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, SHOT(7));
    PlaySound(SE_Z2_FROG_LAND);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_END) setMode(s, 0);
}

// 0x0808215c
static void Frog_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Frog_Die(p);
    return;
  }
  if (s->mode[1] == 0) {
    Frog_Hop(p);
  } else {
    Frog_Land(p);
  }
}

// 0x080821a4
static void Frog_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  c.x = s->coord.x;
  c.y = s->coord.y - 0x800;
  CreateSmoke(1, &c);
  PlaySound(s->coord.y > gOverworld.sea ? SE_UNK_31 : SE_ZAKO_EXPLODE);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 44, ring.
  work0:
    0: head
    1..4: rings behind, two frames apart
  work1:
    0: down
    1: up
*/
struct Ring {
  OBJECT_HDR;
  Coords32 last;     // 0xB4
  Coords32 earlier;  // 0xBC
};
static_assert(sizeof(struct Ring) <= sizeof(struct Projectile));

static void Ring_Init(struct Projectile* p);
static void Ring_Update(struct Projectile* p);
static void Ring_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2WallRingRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Ring_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Ring_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Ring_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a65a4, 0x080a668c
static void Ring_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Ring* r = (struct Ring*)p;
  setUp(s, SHOT(s->work[0]));
  SET_XFLIP(p, FALSE);
  s->flags |= COLLIDABLE;
  INIT_BODY(p, sRingCollisions, 1, NULL);
  s->coord = s->unk_28->coord;
  r->last.x = r->last.y = 0;
  r->earlier.x = r->earlier.y = 0;
  if (s->work[0] == 0) {
    s->d.x = 0x180;
    s->d.y = s->work[1] != 0 ? -0x180 : 0x180;
  }
  s->work[2] = 0;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Ring_Update(p);
}

static void ringRemember(struct Ring* r) {
  r->earlier = r->last;
  r->last = (r->s).coord;
}

// 0x080a6730
static void Ring_Head(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Ring* r = (struct Ring*)p;
  if (s->unk_28->mode[0] >= ENTITY_DIE || FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    s->mode[3] = 1;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Ring_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 0 && r->earlier.x != 0) {
    createRing(s, 1, 0);
    s->mode[1]++;
  }
  ringRemember(r);
  if (FUN_080098a4(s->coord.x + s->d.x, s->coord.y) != 0) {
    s->d.x = -s->d.x;
    s->work[2]++;
    PlaySound(SE_Z2_RING_BOUNCE);
  }
  s->coord.x += s->d.x;
  if (FUN_080098a4(s->coord.x, s->coord.y + s->d.y) != 0) {
    s->d.y = -s->d.y;
    s->work[2]++;
    PlaySound(SE_Z2_RING_BOUNCE);
  }
  s->coord.y += s->d.y;
  if (s->work[2] > 5) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Ring_Die(p);
  }
}

// 0x080a6834
static void Ring_Tail(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Ring* r = (struct Ring*)p;
  struct Ring* parent = (struct Ring*)s->unk_28;
  UpdateEntityAnim(s);
  if (s->mode[1] == 0 && s->work[0] <= 3 && r->earlier.x != 0) {
    createRing(s, s->work[0] + 1, 0);
    s->mode[1]++;
  }
  ringRemember(r);
  if (s->mode[2] == 0) {
    s->coord = parent->earlier;
    if ((parent->s).mode[0] < ENTITY_DIE) return;
    s->d.x = s->coord.x - r->last.x;
    s->d.y = s->coord.y - r->last.y;
    if ((parent->s).mode[3] != 0) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Ring_Die(p);
      return;
    }
    s->mode[2]++;
    return;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Ring_Die(p);
  }
}

static void Ring_Update(struct Projectile* p) {
  if ((p->s).work[0] == 0) {
    Ring_Head(p);
  } else {
    Ring_Tail(p);
  }
}

static void Ring_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR); }

// --------------------------------------------
// Zero 2's VFX 44, water coming in. work0: 1 room's left, 0 surface following sea
static void Splash_Init(struct VFX* p);
static void Splash_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2WaterSplashRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Splash_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Splash_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct Entity* ApZ2CreateSplash(const Coords32* at, u8 kind) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    ApLoadSheet(&sSplashSheet);
    INIT_VFX_ROUTINE(p, VFX_Z2_WATER_SPLASH);
    p->unk_28 = (void*)at;
    p->coord = *at;
    p->work[0] = kind;
  }
  return p;
}

static void Splash_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  setUp(s, MOTION(AP_SHEET_Z2_WALL_SPLASH, s->work[0]));
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
}

static void Splash_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateEntityAnim(s);
  if (s->work[0] == 0) s->coord = *(const Coords32*)s->unk_28;
}

// clang-format off
static const struct Collision sCollisions[2] = {
    /* 0x833d3c4 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0, 0, 0x800, 0x2000}},
    /* 0x833d3dc */ {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0, 0, 0x800, 0x2000}},
};
static const struct Collision sOpenCollisions[2] = {
    /* 0x833d3f4 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0, 0, 0x800, 0x1200}},
    /* 0x833d40c */ {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0, 0, 0x800, 0x2000}},
};
static const struct Collision sHurtCollisions[2] = {
    /* 0x833d424 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x02, 0x01, 0x00, 1, 0x00000001, {0, 0, 0x800, 0x1200}},
    /* 0x833d43c */ {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x01, 0x00, 0, 0xffffffff, {0, 0, 0x800, 0x2000}},
};
static const struct Collision sShelfCollision =
    /* 0x834911c */ {DRP, FACTION_ENEMY, 0, 0, 0x00, 0x04, 0x00, 0x00, 0x01, NO_DAMAGE | HARDNESS_B3, 0x00, 0, 0x00000000, {0, 3072, 24576, 6144}};
static const struct Collision sFrogCollisions[2] = {
    /* 0x8341054 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0, -2048, 4096, 4096}},
    /* 0x834106c */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0, -2048, 4096, 4096}},
};
static const struct Collision sRingCollisions[2] = {
    /* 0x834507c */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0, 0, 2048, 2048}},
    /* 0x8345094 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0, 0, 0, 0}},
};
// clang-format on

#endif  // AP
