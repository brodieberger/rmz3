#include "projectile.h"

#include "entity.h"
#include "global.h"
#include "overworld.h"

void InitProjectileHeader(struct EntityHeader* h, struct Projectile* p, s16 len) {
  s16 i;

  InitEntityHeader(h, ENTITY_PROJECTILE, &p->s, sizeof(struct Projectile), len);
  for (i = 0; i < len; i++) {
    p[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gProjectileHeaderPtr = h;
}

void UpdateProjectiles(void) {
  struct Entity* p;
  struct EntityHeader* h = gProjectileHeaderPtr;
  if ((gStageRun.id != STAGE_SPACE_CRAFT) && (((!(gStageRun.missionStatus & MISSION_STAY)) || (gStageRun.vm.active & VM_ACTIVE) || (gStageRun.vm.unk_004 & 1)) || gInChat || gIsUsingDoor3D)) {
    gIsLemonCollisionRemoved = TRUE;
  } else {
    gIsLemonCollisionRemoved = FALSE;
  }

  p = StartEntityListIteration(h);

  while (p != (struct Entity*)&h->tail) {
    ((EntityFunc)p->onUpdate)(p);
    p = GetNextEntity(h);
  }
}

void DeleteProjectile(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

static Coords32* unused_0809c978(struct Entity* q) {
  struct Entity* p = GetNearestEntity(gWeaponHeaderPtr, &q->coord);
  if (p != NULL) return &p->coord;
  return NULL;
}

// -----------------------------------------------------------------------------

extern const ProjectileRoutine gLemonRoutine;
extern const ProjectileRoutine gShotcounterBulletRoutine;
extern const ProjectileRoutine gProjectile2Routine;
extern const ProjectileRoutine gGrandCannonBombRoutine;
extern const ProjectileRoutine gOmegaWhiteProjectileRoutine;
extern const ProjectileRoutine gProjectile5Routine;
extern const ProjectileRoutine gProjectile6Routine;
extern const ProjectileRoutine gProjectile7Routine;
extern const ProjectileRoutine gProjectile8Routine;
extern const ProjectileRoutine gBlazinProjectileRoutine;
extern const ProjectileRoutine gBlazinTailRoutine;
extern const ProjectileRoutine gEarShotRoutine;
extern const ProjectileRoutine gProjectile12Routine;
extern const ProjectileRoutine gProjectile13Routine;
extern const ProjectileRoutine gProjectile14Routine;
extern const ProjectileRoutine gHellbatProjectileRoutine;
extern const ProjectileRoutine gProjectile16Routine;
extern const ProjectileRoutine gProjectile17Routine;
extern const ProjectileRoutine gProjectile18Routine;
extern const ProjectileRoutine gTretistaProjectileRoutine;
extern const ProjectileRoutine gProjectile20Routine;
extern const ProjectileRoutine gPantheonAquaModProjectileRoutine;
extern const ProjectileRoutine gCubitProjectileRoutine;
extern const ProjectileRoutine gProjectile23Routine;
extern const ProjectileRoutine gCopyXTackleProjectileRoutine;
extern const ProjectileRoutine gProjectile25Routine;
extern const ProjectileRoutine gProjectile26Routine;
extern const ProjectileRoutine gProjectile27Routine;
extern const ProjectileRoutine gProjectile28Routine;
extern const ProjectileRoutine gProjectile29Routine;
extern const ProjectileRoutine gProjectile30Routine;
extern const ProjectileRoutine gProjectile31Routine;
extern const ProjectileRoutine gProjectile32Routine;
extern const ProjectileRoutine gOmegaGoldProjectileRoutine;
extern const ProjectileRoutine gProjectile34Routine;
extern const ProjectileRoutine gPantheonBombProjectileRoutine;
extern const ProjectileRoutine gProjectile36Routine;
extern const ProjectileRoutine gProjectile37Routine;
extern const ProjectileRoutine gOmegaZeroProjectileRoutine;
extern const ProjectileRoutine gClavekerYellowBallsRoutine;
extern const ProjectileRoutine gPhantomProjectileRoutine;
extern const ProjectileRoutine gOmegaZXProjectileRoutine;
extern const ProjectileRoutine gShotloidProjectileRoutine;
extern const ProjectileRoutine gShellcrawlerProjectileRoutine;
extern const ProjectileRoutine gProjectile44Routine;
extern const ProjectileRoutine gProjectile45Routine;
extern const ProjectileRoutine gProjectile46Routine;
extern const ProjectileRoutine gProjectile47Routine;
#if AP
extern const ProjectileRoutine gApZ2SignaloidBoltRoutine;
extern const ProjectileRoutine gApZ2SignaloidFlakeRoutine;
extern const ProjectileRoutine gApZ2SignaloidFireRoutine;
extern const ProjectileRoutine gApZ2GolemLaserRoutine;
extern const ProjectileRoutine gApZ2HarpuiaWaveRoutine;
extern const ProjectileRoutine gApZ2HarpuiaThunderRoutine;
extern const ProjectileRoutine gApZ2CopterGunRoutine;
extern const ProjectileRoutine gApZ2BarrierShipShotRoutine;
extern const ProjectileRoutine gApZ2RingCannonShotRoutine;
extern const ProjectileRoutine gApZ2ShieldGuardMaceRoutine;
extern const ProjectileRoutine gApZ2BeeBombRoutine;
extern const ProjectileRoutine gApZ2BeeBlastRoutine;
extern const ProjectileRoutine gApZ2MoleDrillRoutine;
extern const ProjectileRoutine gApZ2TowerArmRoutine;
extern const ProjectileRoutine gApZ2TowerSpikeRoutine;
extern const ProjectileRoutine gApZ2SpikeballRockRoutine;
extern const ProjectileRoutine gApZ2SpiderWebRoutine;
extern const ProjectileRoutine gApZ2DesertLinkRoutine;
extern const ProjectileRoutine gApZ2FefnirFireRoutine;
extern const ProjectileRoutine gApZ2LeviathanShotRoutine;
extern const ProjectileRoutine gApZ2BlobDropRoutine, gApZ2BlobSplatRoutine;
extern const ProjectileRoutine gApZ2GolemFireRoutine, gApZ2GolemJetRoutine;
extern const ProjectileRoutine gApZ2DragonTailRoutine;
extern const ProjectileRoutine gApZ2WallRingRoutine;
extern const ProjectileRoutine gApZ2PylonHazardRoutine;
#endif

// clang-format off
const ProjectileRoutine *const gProjectileFnTable[PROJECTILE_ENTITY_COUNT] = {
    [0]  = &gLemonRoutine,
    [1]  = &gShotcounterBulletRoutine,
    [2]  = &gProjectile2Routine,
    [3]  = &gGrandCannonBombRoutine,
    [4]  = &gOmegaWhiteProjectileRoutine,
    [5]  = &gProjectile5Routine,
    [6]  = &gProjectile6Routine,
    [7]  = &gProjectile7Routine,
    [8]  = &gProjectile8Routine,
    [9]  = &gBlazinProjectileRoutine,
    [10] = &gBlazinTailRoutine,
    [11] = &gEarShotRoutine,
    [12] = &gProjectile12Routine,
    [13] = &gProjectile13Routine,
    [14] = &gProjectile14Routine,
    [15] = &gHellbatProjectileRoutine,
    [16] = &gProjectile16Routine,
    [17] = &gProjectile17Routine,
    [18] = &gProjectile18Routine,
    [19] = &gTretistaProjectileRoutine,
    [20] = &gProjectile20Routine,
    [21] = &gPantheonAquaModProjectileRoutine,
    [22] = &gCubitProjectileRoutine,
    [23] = &gProjectile23Routine,
    [24] = &gCopyXTackleProjectileRoutine,
    [25] = &gProjectile25Routine,
    [26] = &gProjectile26Routine,
    [27] = &gProjectile27Routine,
    [28] = &gProjectile28Routine,
    [29] = &gProjectile29Routine,
    [30] = &gProjectile30Routine,
    [31] = &gProjectile31Routine,
    [32] = &gProjectile32Routine,
    [33] = &gOmegaGoldProjectileRoutine,
    [34] = &gProjectile34Routine,
    [35] = &gPantheonBombProjectileRoutine,
    [36] = &gProjectile36Routine,
    [37] = &gProjectile37Routine,
    [38] = &gOmegaZeroProjectileRoutine,
    [39] = &gClavekerYellowBallsRoutine,
    [40] = &gPhantomProjectileRoutine,
    [41] = &gOmegaZXProjectileRoutine,
    [42] = &gShotloidProjectileRoutine,
    [43] = &gShellcrawlerProjectileRoutine,
    [44] = &gProjectile44Routine,
    [45] = &gProjectile45Routine,
    [46] = &gProjectile46Routine,
    [47] = &gProjectile47Routine,
#if AP
    [PROJECTILE_Z2_SIGNALOID_BOLT] = &gApZ2SignaloidBoltRoutine,
    [PROJECTILE_Z2_SIGNALOID_FLAKE] = &gApZ2SignaloidFlakeRoutine,
    [PROJECTILE_Z2_SIGNALOID_FIRE] = &gApZ2SignaloidFireRoutine,
    [PROJECTILE_Z2_GOLEM_LASER] = &gApZ2GolemLaserRoutine,
    [PROJECTILE_Z2_HARPUIA_WAVE] = &gApZ2HarpuiaWaveRoutine,
    [PROJECTILE_Z2_HARPUIA_THUNDER] = &gApZ2HarpuiaThunderRoutine,
    [PROJECTILE_Z2_COPTER_GUN] = &gApZ2CopterGunRoutine,
    [PROJECTILE_Z2_BARRIER_SHIP_SHOT] = &gApZ2BarrierShipShotRoutine,
    [PROJECTILE_Z2_RING_CANNON_SHOT] = &gApZ2RingCannonShotRoutine,
    [PROJECTILE_Z2_SHIELD_GUARD_MACE] = &gApZ2ShieldGuardMaceRoutine,
    [PROJECTILE_Z2_BEE_BOMB] = &gApZ2BeeBombRoutine,
    [PROJECTILE_Z2_BEE_BLAST] = &gApZ2BeeBlastRoutine,
    [PROJECTILE_Z2_MOLE_DRILL] = &gApZ2MoleDrillRoutine,
    [PROJECTILE_Z2_TOWER_ARM] = &gApZ2TowerArmRoutine,
    [PROJECTILE_Z2_TOWER_SPIKE] = &gApZ2TowerSpikeRoutine,
    [PROJECTILE_Z2_SPIKEBALL_ROCK] = &gApZ2SpikeballRockRoutine,
    [PROJECTILE_Z2_SPIDER_WEB] = &gApZ2SpiderWebRoutine,
    [PROJECTILE_Z2_DESERT_LINK] = &gApZ2DesertLinkRoutine,
    [PROJECTILE_Z2_FEFNIR_FIRE] = &gApZ2FefnirFireRoutine,
    [PROJECTILE_Z2_LEVIATHAN_SHOT] = &gApZ2LeviathanShotRoutine,
    [PROJECTILE_Z2_BLOB_DROP] =     &gApZ2BlobDropRoutine,
    [PROJECTILE_Z2_BLOB_SPLAT] =    &gApZ2BlobSplatRoutine,
    [PROJECTILE_Z2_GOLEM_FIRE] =    &gApZ2GolemFireRoutine,
    [PROJECTILE_Z2_GOLEM_JET] =     &gApZ2GolemJetRoutine,
    [PROJECTILE_Z2_DRAGON_TAIL] = &gApZ2DragonTailRoutine,
    [PROJECTILE_Z2_WALL_RING] = &gApZ2WallRingRoutine,
    [PROJECTILE_Z2_PYLON_HAZARD] = &gApZ2PylonHazardRoutine,
#endif
};
// clang-format on
