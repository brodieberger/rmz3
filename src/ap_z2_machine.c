#include "ap.h"
#include "ap_import.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

#define GENERATOR(n) MOTION(AP_SHEET_Z2_GENERATOR, (n))
#define DRONE(n) MOTION(AP_SHEET_Z2_DRONE, (n))
#define MAGMA(n) MOTION(AP_SHEET_Z2_MAGMA, (n))

static void useApSheets(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void createBit(struct Entity* parent, u8 kind, u8 piece, bool8 right);

// --------------------------------------------
/*
  Zero 2's drone generator, enemy 71, Power Room's machine room.
  Core shows only if all three waves are shot down.
*/

struct Generator {
  OBJECT_HDR;
  s32 left;     // 0xB4
  s32 top;      // 0xB8
  u8 spared;    // 0xBC, drones of this wave not shot down
  u8 flying;    // 0xBD, drones of this wave not yet gone
  u8 _be[2];
  s16 sound;    // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Generator) == sizeof(struct Enemy));

enum { GEN_WAIT, GEN_WAVE0, GEN_WAVE1, GEN_WAVE2, GEN_CORE, GEN_SHUT };

static void Generator_Init(struct Generator* p);
static void Generator_Update(struct Generator* p);
static void Generator_Die(struct Generator* p);
static void createDrone(struct Generator* parent, u8 kind, u8 n);

// clang-format off
const EnemyRoutine gApZ2GeneratorRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Generator_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Generator_Update,
    [ENTITY_DIE] =       (EnemyFunc)Generator_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x083421b4
static const struct Collision sCore[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1e00, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1e00, 0x1000}},
};
// clang-format on

// 0x0808f7a0
static void Generator_Init(struct Generator* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, GENERATOR(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  p->left = s->coord.x - PIXEL(40);
  p->top = s->coord.y - PIXEL(160);
  s->coord.x += PIXEL(32);
  s->coord.y += PIXEL(128);
  p->sound = -1;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Generator_Update(p);
}

// 0x0808f8fc
static void Generator_Wait(struct Generator* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->work[2]-- == 0) setMode(s, GEN_WAVE0);
}

// 0x0808f930, 0x0808f9a4, 0x0808fa18
static void Generator_Wave(struct Generator* p) {
  static const u8 sGaps[3] = {32, 24, 16};
  struct Entity* s = &p->s;
  u8 kind = s->mode[1] - GEN_WAVE0;
  if (s->mode[2] == 0) {
    p->spared = p->flying = 12;
    s->work[3] = s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->work[2] < 12 && s->work[3]++ > sGaps[kind]) {
    createDrone(p, kind, s->work[2]);
    s->work[2]++;
    s->work[3] = 0;
  }
  if (p->flying != 0) return;
  setMode(s, p->spared != 0 ? GEN_SHUT : s->mode[1] + 1);
}

// 0x0808fa8c
static void Generator_Core(struct Generator* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Generator_Die(p);
    return;
  }
  switch (s->mode[3]) {
    case 0:
      if (s->work[2]-- != 0) return;
      INIT_BODY(p, sCore, 4, NULL);
      p->sound = PlaySound(SE_Z2_GENERATOR_CORE);
      s->mode[3]++;
      break;
    case 1:
      s->coord.x -= 0x300;
      if (s->coord.x >= p->left + PIXEL(32)) return;
      s->coord.x = p->left + PIXEL(32);
      s->mode[3]++;
      break;
    default:
      s->coord.y -= 0x300;
      if (s->coord.y < p->top - PIXEL(8)) setMode(s, GEN_SHUT);
  }
}

// 0x0808fb78
static void Generator_Shut(struct Generator* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] != 0) return;
  StopSound(p->sound);
  EXIT_BODY(p);
  s->flags &= ~DISPLAY;
  s->mode[2]++;
}

static void (*const sGeneratorStates[])(struct Generator*) = {
    Generator_Wait, Generator_Wave, Generator_Wave, Generator_Wave, Generator_Core, Generator_Shut,
};

// 0x0808f844
static void Generator_Update(struct Generator* p) { sGeneratorStates[(p->s).mode[1]](p); }

// 0x0808f85c
static void Generator_Die(struct Generator* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] != 0) return;
  CreateSmoke(1, &s->coord);
  StopSound(p->sound);
  PlaySound(SE_Z2_GENERATOR_BLAST);
  TryDropItem(0, (struct Coord*)&s->coord);
  EXIT_BODY(p);
  s->flags &= ~DISPLAY;
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  ApImportGeneratorKilled();
  s->mode[2]++;
}

// --------------------------------------------
/*
  Zero 2's drone, enemy 72.
  work0: wave, 0..2
  work1: order in wave
*/

struct Drone {
  OBJECT_HDR;
  s32 homeX;           // 0xB4
  s32 homeY;           // 0xB8
  bool8 hitFromRight;  // 0xBC
  u8 _bd[7];
};
static_assert(sizeof(struct Drone) == sizeof(struct Enemy));

#define DRONE_PARENT(s) ((struct Generator*)(s)->unk_28)

static void Drone_Init(struct Drone* p);
static void Drone_Update(struct Drone* p);
static void Drone_Die(struct Drone* p);
static void createShot(struct Entity* drone);

// clang-format off
const EnemyRoutine gApZ2DroneRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Drone_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Drone_Update,
    [ENTITY_DIE] =       (EnemyFunc)Drone_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x083421f8
static const struct Collision sDrone[2] = {
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

// 0x08342228
static const s16 sDroneSpeeds[3] = {0x100, 0x180, 0x200};

// 0x0808fbb4
static void createDrone(struct Generator* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_DRONE);
    p->unk_28 = (struct Entity*)parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x0808fef0
static void Drone_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Drone* p = (struct Drone*)body->parent;
    p->hitFromRight = (body->enemy->parent->coord).x > (p->s).coord.x;
  }
}

// 0x0808fc14
static void Drone_Init(struct Drone* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  s->palID = s->work[0];
  SetSpriteAnimation(p, DRONE(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sDrone, 1, Drone_OnCollision);
  s->coord.x = p->homeX = DRONE_PARENT(s)->left;
  s->coord.y = p->homeY = DRONE_PARENT(s)->top;
  s->work[2] = 24;
  s->work[3] = 16;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Drone_Update(p);
}

// 0x0808fccc: down, left, up, left, down, left, up out
static void Drone_Update(struct Drone* p) {
  struct Entity* s = &p->s;
  s16 speed = sDroneSpeeds[s->work[0]];
  if ((DRONE_PARENT(s)->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Drone_Die(p);
    return;
  }
  if (s->work[3]-- == 0) {
    PlaySound(SE_ENEMY_SHOT);
    createShot(s);
    s->work[3] = 92;
  }
  switch (s->mode[1]) {
    case 0:
    case 4:
      s->coord.y += speed;
      if (s->coord.y < p->homeY + PIXEL(288)) break;
      s->coord.y = p->homeY + PIXEL(288);
      s->mode[1]++;
      break;
    case 1:
    case 3:
    case 5:
      s->coord.x -= speed;
      if (s->coord.x > p->homeX - PIXEL(s->work[2])) break;
      s->coord.x = p->homeX - PIXEL(s->work[2]);
      s->work[2] += 24;
      s->mode[1]++;
      break;
    case 2:
      s->coord.y -= speed;
      if (s->coord.y > p->homeY + PIXEL(32)) break;
      s->coord.y = p->homeY + PIXEL(32);
      s->mode[1]++;
      break;
    case 6:
      s->coord.y -= speed;
      if (s->coord.y > p->homeY) break;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      DRONE_PARENT(s)->flying--;
      break;
  }
}

// 0x0808fe44
static void Drone_Die(struct Drone* p) {
  struct Entity* s = &p->s;
  u8 i;
  DRONE_PARENT(s)->spared--;
  DRONE_PARENT(s)->flying--;
  for (i = 0; i < 3; i++) createBit(s, 0, i, p->hitFromRight);
  CreateSmoke(2, &s->coord);
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(0, (struct Coord*)&s->coord);
  EXIT_BODY(p);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's drone shot, projectile 50.
*/

enum { SHOT_WAIT, SHOT_CHARGE, SHOT_CHARGING, SHOT_FIRE, SHOT_FLY };

static void Shot_Init(struct Projectile* p);
static void Shot_Update(struct Projectile* p);
static void Shot_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2DroneShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Shot_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Shot_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Shot_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08345468
static const struct Collision sShot = {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x800}};
// clang-format on

// 0x080a9494
static void createShot(struct Entity* drone) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_DRONE_SHOT);
    p->unk_28 = drone;
  }
}

static bool8 inTerrain(s32 x, s32 y) {
  metatile_attr_t attr = FUN_080098a4(x, y);
  return attr != 0 && attr != MT_LADDER;
}

// 0x080a94e4
static void Shot_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, DRONE(1));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  s->work[2] = 32;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Shot_Update(p);
}

// 0x080a9550
static void Shot_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* drone = s->unk_28;
  if (s->mode[1] < SHOT_FLY) {
    s->coord.x = drone->coord.x - PIXEL(24);
    s->coord.y = drone->coord.y;
    if (drone->mode[0] > ENTITY_UPDATE) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
  if ((p->body).status & (BODY_STATUS_B8 | BODY_STATUS_B22)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Shot_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case SHOT_WAIT:
      UpdateSpriteAnimation(p);
      if (s->work[2]-- == 0) s->mode[1]++;
      break;
    case SHOT_CHARGE:
      SetSpriteAnimation(p, DRONE(2));
      s->mode[1]++;
    case SHOT_CHARGING:
      UpdateSpriteAnimation(p);
      if (s->motion.state == ANIM_END) s->mode[1]++;
      break;
    case SHOT_FIRE:
      SetSpriteAnimation(p, DRONE(3));
      INIT_BODY(p, &sShot, 1, NULL);
      s->mode[1]++;
    case SHOT_FLY:
      UpdateSpriteAnimation(p);
      s->coord.x -= PIXEL(2);
      break;
  }
  if (inTerrain(s->coord.x - PIXEL(8), s->coord.y) && inTerrain(s->coord.x, s->coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Shot_Die(p);
  }
}

// 0x080a96d8
static void Shot_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, DRONE(4));
    EXIT_BODY(p);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->motion.state == ANIM_END) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's VFX 58.
  work0:
    0: drone's wreck, flung
    1: frost off frozen magma
  work1: piece
*/

static void Bit_Init(struct Entity* p);
static void Bit_Update(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2MachineBitRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Bit_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Bit_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bc2e0
static void createBit(struct Entity* parent, u8 kind, u8 piece, bool8 right) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_MACHINE_BIT);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = piece;
    p->work[3] = right;
  }
}

// 0x080bc384, 0x080bc448
static void Bit_Init(struct Entity* p) {
  struct Entity* parent = p->unk_28;
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  if (p->work[0] == 0) {
    p->palID = parent->work[0];
    SetSpriteAnimation(p, DRONE(5 + p->work[1]));
  } else {
    SetSpriteAnimation(p, MAGMA(3 + p->work[1]));
  }
  SET_XFLIP(p, FALSE);
  p->coord = parent->coord;
  if (p->work[0] == 0) {
    p->d.x = RANDOM(RNG_0202f388) & 0x1FF;
    p->d.y = -(RANDOM(RNG_0202f388) & 0x3FF);
    if (p->work[3]) p->d.x = -p->d.x;
    p->work[2] = p->work[1] + 64;
  } else {
    p->coord.x += PIXEL(8 - (RANDOM(RNG_0202f388) & 15));
    p->coord.y += PIXEL(8 - (RANDOM(RNG_0202f388) & 15));
    p->work[2] = 96;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Bit_Update(p);
}

// 0x080bc524, 0x080bc58c
static void Bit_Update(struct Entity* p) {
  UpdateSpriteAnimation(p);
  if (p->work[0] == 0) {
    p->d.y += 64;
    p->coord.x += p->d.x;
    p->coord.y += p->d.y;
  } else {
    p->coord.y += 0x180;
  }
  if (p->work[0] == 0 || p->work[2] < 32) {
    p->flags = (p->work[2] & 1) ? (p->flags | DISPLAY) : (p->flags & ~DISPLAY);
  }
  if (p->work[2]-- == 0) SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's magma, solid 19. Rises or falls, ice chip freezes it.
  Solid to Zero only within 72 px.
*/

struct Magma {
  OBJECT_HDR;
  bool8 far;  // 0xB4
  bool8 out;  // 0xB5, has left terrain it started in
  u8 _b6[14];
};
static_assert(sizeof(struct Magma) == sizeof(struct Solid));

enum { MAGMA_MOLTEN, MAGMA_FREEZE, MAGMA_FROZEN };

static void Magma_Init(struct Magma* p);
static void Magma_Update(struct Magma* p);

// clang-format off
const SolidRoutine gApZ2MagmaRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Magma_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Magma_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};

// 0x0834986c
static const struct Collision sMagma[2] = {
    {DDP, FACTION_NEUTRAL, 0, 4, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00008000, {0x0, 0x0, 0x1800, 0x2400}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x02, NO_DAMAGE, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1800, 0x2400}},
};
// clang-format on

// 0x08349864
static const struct Rect sMagmaSize = {0, 0, 0x1400, 0x2000};

// 0x080cdd64
static void createMagma(struct Entity* dropper, const Coords32* at, bool8 falling) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_Z2_MAGMA);
    p->unk_28 = dropper;
    p->coord = *at;
    p->work[0] = falling;
  }
}

static void becomeSolid(struct Entity* s) {
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sMagmaSize;
  s->physicsAttr = s->mode[1] != MAGMA_MOLTEN ? MTATTR_B11 | SHAPE_BLOCK : SHAPE_14;
}

// 0x080cddc8
static void Magma_Init(struct Magma* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MAGMA(0));
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sMagma, 1, NULL);
  s->d.y = s->work[0] ? PIXEL(1) : -PIXEL(1);
  p->far = TRUE;
  p->out = FALSE;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Magma_Update(p);
}

// 0x080cde60
static void Magma_Update(struct Magma* p) {
  struct Entity* s = &p->s;
  bool8 near;
  s32 edge;
  if (s->unk_28->mode[0] > ENTITY_UPDATE) {
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  s->coord.y += s->d.y;
  edge = s->coord.y + (s->work[0] ? -PIXEL(16) : PIXEL(16));
  near = (u32)((pZero2->s).coord.x - s->coord.x + PIXEL(72)) <= PIXEL(144) &&
         (u32)((pZero2->s).coord.y - s->coord.y + PIXEL(72)) <= PIXEL(144);
  if (!p->far && !near) {
    s->flags2 &= ~ENTI_PHYSICS;
    p->far = TRUE;
  } else if (p->far && near) {
    becomeSolid(s);
    p->far = FALSE;
  }
  switch (s->mode[1]) {
    case MAGMA_MOLTEN:
      UpdateSpriteAnimation(p);
      if (((p->body).status & BODY_STATUS_WHITE) && (p->body).elemented == ELEMENT_ICE) s->mode[1]++;
      break;
    case MAGMA_FREEZE:
      SetSpriteAnimation(p, MAGMA(1));
      EXIT_BODY(p);
      becomeSolid(s);
      PlaySound(SE_ICE_40);
      p->far = TRUE;
      s->work[2] = 0;
      s->mode[1]++;
    case MAGMA_FROZEN:
      UpdateSpriteAnimation(p);
      if ((s->work[2]++ & 15) == 0 && FUN_080098a4(s->coord.x, s->coord.y) == 0) {
        createBit(s, 1, RANDOM(RNG_0202f388) % 3, FALSE);
      }
      break;
  }
  if (!p->out) {
    if (FUN_080098a4(s->coord.x, edge) == 0) p->out = TRUE;
    return;
  }
  if (FUN_080098a4(s->coord.x, edge) != 0 ||
      (s->work[0] ? edge >= gStageRun.vm.camera.viewport.y + PIXEL(80)
                  : edge < gStageRun.vm.camera.viewport.y - PIXEL(80))) {
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
  }
}

// --------------------------------------------
/*
  Zero 2's magma dropper, solid 27, unseen.
  work0: 0 lets it rise, 1 fall
  work1: frames into Shuttle Factory's 96
*/

static void Dropper_Init(struct Solid* p);
static void Dropper_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2MagmaDropperRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Dropper_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Dropper_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

extern const StageFunc gApZ2Plant2_StageRoutines[4];

// Shuttle Factory's droppers keep one clock and start with their column full
static bool8 inFactory(void) { return gApImportedStages[gApImportSelected].fns == gApZ2Plant2_StageRoutines; }

// 0x080d1644
static void Dropper_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  u16 t = gOverworld.work.apZ2Plant2.clock;
  Coords32 at;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if (!inFactory()) {
    s->work[2] = 0;
    Dropper_Update(p);
    return;
  }
  at.x = s->coord.x;
  if (s->work[0] == 0) {
    at.y = s->coord.y + PIXEL(16) - PIXEL((t - (s->work[1] - 96)) % 96);
    for (; at.y > gStageRun.vm.camera.viewport.y - PIXEL(80); at.y -= PIXEL(96)) createMagma(s, &at, FALSE);
  } else {
    at.y = s->coord.y - PIXEL(16) + PIXEL((t + s->work[1]) % 96);
    for (; at.y < gStageRun.vm.camera.viewport.y + PIXEL(80) - 1; at.y += PIXEL(96)) createMagma(s, &at, TRUE);
  }
}

// 0x080d1764
static void Dropper_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u16 t;
  if (inFactory()) {
    t = gOverworld.work.apZ2Plant2.clock;
  } else {
    if (++s->work[2] > 95) s->work[2] = 0;
    t = s->work[2];
  }
  at.x = s->coord.x;
  if (s->work[0] == 0 && (t - (s->work[1] - 96)) % 96 == 0) {
    at.y = s->coord.y + PIXEL(16);
    createMagma(s, &at, FALSE);
  } else if (s->work[0] == 1 && (t + s->work[1]) % 96 == 0) {
    at.y = s->coord.y - PIXEL(16);
    createMagma(s, &at, TRUE);
  }
}

#endif  // AP
