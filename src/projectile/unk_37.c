#include "collision.h"
#include "global.h"
#include "projectile.h"

void Projectile37_Init(struct Projectile* p);
void Projectile37_Update(struct Projectile* p);
void Projectile37_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile37Routine = {
    [ENTITY_INIT] =      (void*)Projectile37_Init,
    [ENTITY_UPDATE] =    (void*)Projectile37_Update,
    [ENTITY_DIE] =       (void*)Projectile37_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteProjectile,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

static struct Entity* unused_FUN_080ada80(void* e, u8 kind) {
  struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    p->taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 37);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind, p->work[1] = 1;
    p->unk_28 = e;
  }
  return p;
}

struct Entity* FUN_080adad0(struct Coord* c, u8 kind) {
  struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    p->taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 37);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind, p->work[1] = 0;
    (p->coord).x = c->x, (p->coord).y = c->y;
  }
  return p;
}

INCASM("asm/projectile/unk_37.inc");

// --------------------------------------------

void FUN_080adc84(struct Projectile* p);
void FUN_080ae140(struct Projectile* p);

static const ProjectileFunc sUpdates[2] = {
    FUN_080adc84,
    FUN_080ae140,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};
