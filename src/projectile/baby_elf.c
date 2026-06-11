#include "collision.h"
#include "global.h"
#include "projectile.h"

// Baby Elf's projectile

void Projectile13_Init(struct Projectile* p);
void Projectile13_Update(struct Projectile* p);
void Projectile13_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile13Routine = {
    [ENTITY_INIT] =      (void*)Projectile13_Init,
    [ENTITY_UPDATE] =    (void*)Projectile13_Update,
    [ENTITY_DIE] =       (void*)Projectile13_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteProjectile,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

void FUN_0809f8ac(struct Entity* q) {
  s32 i;
  for (i = 0; i < 4; i++) {
    struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
    if (p != NULL) {
      INIT_PROJECTILE_ROUTINE(p, 13);
      p->work[0] = 5, p->work[2] = i;
      p->unk_28 = q;
    }
  }
}

INCASM("asm/projectile/baby_elf.inc");

// --------------------------------------------

void nop_0809fbd8(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[7] = {
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
};
// clang-format on

// --------------------------------------------

void FUN_0809fbdc(struct Projectile* p);
void FUN_0809fcfc(struct Projectile* p);
void FUN_0809ff74(struct Projectile* p);
void FUN_080a025c(struct Projectile* p);
void FUN_080a03ac(struct Projectile* p);
void FUN_080a04d4(struct Projectile* p);
void FUN_080a06c0(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[7] = {
    FUN_0809fbdc,
    FUN_0809fcfc,
    FUN_0809ff74,
    FUN_080a025c,
    FUN_080a03ac,
    FUN_080a04d4,
    FUN_080a06c0,
};
// clang-format on

// --------------------------------------------

// 0x0836B050
static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};

static const u8 u8_0836b0c8[6] = {0, 1, 2, 3, 4, 5};

// 0x0836B0CE
static const s16 sUnkDeltaX[4] = {PIXEL(48), PIXEL(32), -PIXEL(32), -PIXEL(48)};

static const s16 s16_ARRAY_0836b0d6[4] = {
    0x30,
    0x90,
    0xC0,
    0x60,
};
