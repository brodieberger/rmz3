#include "collision.h"
#include "global.h"
#include "projectile.h"

static void FUN_080b22c8(struct Entity* p);
static void FUN_080b22e0(struct Entity* p);
static void FUN_080b22f8(struct Entity* p);

// clang-format off
const ProjectileRoutine gProjectile46Routine = {
    [ENTITY_INIT] =      (void*)FUN_080b22c8,
    [ENTITY_UPDATE] =    (void*)FUN_080b22e0,
    [ENTITY_DIE] =       (void*)FUN_080b22f8,
    [ENTITY_DISAPPEAR] = (void*)DeleteProjectile,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// 0x080B221C
struct Entity* FUN_080b221c(void* g, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, 46);
    p->unk_28 = g;
    p->work[0] = kind1, p->work[1] = kind2;
  }
  return p;
}

// 0x080B2270
struct Entity* FUN_080b2270(void* g, struct Entity* q, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, 46);
    p->unk_28 = g;
    p->unk_2c = q;
    p->work[0] = kind1, p->work[1] = kind2;
  }
  return p;
}

// --------------------------------------------

void FUN_080b2310(struct Projectile* p);
void FUN_080b2384(struct Projectile* p);
void FUN_080b2428(struct Projectile* p);

static void FUN_080b22c8(struct Entity* p) {
  static const EntityFunc sInitializers[3] = {
      (void*)FUN_080b2310,
      (void*)FUN_080b2384,
      (void*)FUN_080b2428,
  };  // 0x0836d8b0
  (sInitializers[p->work[0]])(p);
}

void FUN_080b24c8(struct Projectile* p);
void FUN_080b258c(struct Projectile* p);
void FUN_080b2654(struct Projectile* p);

static void FUN_080b22e0(struct Entity* p) {
  static const EntityFunc sUpdates[3] = {
      (void*)FUN_080b24c8,
      (void*)FUN_080b258c,
      (void*)FUN_080b2654,
  };  // 0x0836d8bc
  (sUpdates[p->work[0]])(p);
}

void FUN_080b274c(struct Projectile* p);
void FUN_080b2764(struct Projectile* p);
void FUN_080b277c(struct Projectile* p);

static void FUN_080b22f8(struct Entity* p) {
  static const EntityFunc PTR_ARRAY_0836d8c8[3] = {
      (void*)FUN_080b274c,
      (void*)FUN_080b2764,
      (void*)FUN_080b277c,
  };  // 0x0836d8c8
  (PTR_ARRAY_0836d8c8[p->work[0]])(p);
}

// --------------------------------------------

INCASM("asm/projectile/unk_46.inc");
