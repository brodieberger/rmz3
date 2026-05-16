#include "collision.h"
#include "global.h"
#include "metatile.h"
#include "projectile.h"

static void Projectile25_Init(struct Entity* p);
static void Projectile25_Update(struct Entity* p);
static void Projectile25_Die(Object* p);

// clang-format off
const ProjectileRoutine gProjectile25Routine = {
    [ENTITY_INIT] =      (void*)Projectile25_Init,
    [ENTITY_UPDATE] =    (void*)Projectile25_Update,
    [ENTITY_DIE] =       (void*)Projectile25_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteProjectile,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

void FUN_080a83e4(struct Entity* e, u8 param_2, u8 param_3) {
  struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    p->taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 25);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = param_2, p->work[1] = param_3;
    p->unk_28 = (void*)e;
    (p->coord) = e->coord;
  }
}

// --------------------------------------------

void FUN_080a84c4(struct Projectile* p);
void FUN_080a85a0(struct Projectile* p);
void FUN_080a8684(struct Projectile* p);
void FUN_080a8794(struct Projectile* p);

static void Projectile25_Init(struct Entity* p) {
  static const ProjectileFunc sInitializers[4] = {
      (void*)FUN_080a84c4,
      (void*)FUN_080a85a0,
      (void*)FUN_080a8684,
      (void*)FUN_080a8794,
  };  // 0x0836bf68
  (sInitializers[p->work[0]])((void*)p);
}

static void Projectile25_Update(struct Entity* p) {
  UpdateMotionGraphic(p);
  (p->coord).x += (p->d).x;
  (p->coord).y += (p->d).y;
  if (FUN_080098a4((p->coord).x, (p->coord).y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

static void Projectile25_Die(Object* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

INCASM("asm/projectile/unk_25.inc");

// --------------------------------------------

// 0x0836BF78
static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 6,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
