#include "enemy.h"

#include "entity.h"
#include "global.h"
#include "story.h"

void InitEnemyHeader(struct EntityHeader* h, struct Enemy* p, s16 len) {
  s16 i;

  InitEntityHeader(h, ENTITY_ENEMY, &p->s, sizeof(struct Enemy), len);
  for (i = 0; i < len; i++) {
    p[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gEnemyHeaderPtr = h;
}

void DeleteEnemy(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0806364c, 本当は引数の型は (struct Enemy*) だけど cast面倒くさいから void* で
bool32 IsFrozen(void* enemy_entity) {
  bool32 result = FALSE;
  if (FLAG(gCurStory.s.gameflags, TIME_ELF_ENABLED) || (((struct Entity*)enemy_entity)->flags2 & STOPPED)) {
    result = TRUE;
  }
  return result;
}

static struct Enemy* unused_08063674(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)GetNearestEntity(gZeroHeaderPtr, &e->coord);
  if (p == NULL) {
    return NULL;
  }
  return p;
}

static struct Entity* Unused_08063690(u8 n) {
  struct EntityHeader* h = gZeroHeaderPtr;
  struct Entity* p = GetEntityList(h);

  while (p != (struct Entity*)(&h->tail)) {
    if (p->work[0] == n) return p;
    p = GetNextEntity(h);
  }
  return NULL;
}

static struct Weapon* unused_080636d4(struct Entity* e) {
  struct Weapon* p = (struct Weapon*)GetNearestEntity(gWeaponHeaderPtr, &e->coord);
  if (p == NULL) {
    return NULL;
  }
  return p;
}

static Coords32* unused_080636f0(struct Entity* p) {
  struct Entity* w = GetNearestEntity(gWeaponHeaderPtr, &p->coord);
  if (w != NULL) return &w->coord;
  return NULL;
}

static u16 unused_CountSpecificZako(void* _ UNUSED, u8 id) { return countSpecificEntities1(gEnemyHeaderPtr, id); }

static u16 unused_CountSpecificProjectile(void* _ UNUSED, u8 id, u8 r2, u8 r3) { return countSpecificEntities2(gProjectileHeaderPtr, id, r2, r3); }

// ------------------------------------------------------------------------------------------------------------------------------------

extern const EnemyRoutine gPantheonGuardianRoutine;
extern const EnemyRoutine gPantheonHunterRoutine;
extern const EnemyRoutine gMegamilpaNodeRoutine;
extern const EnemyRoutine gShotcounterRoutine;
extern const EnemyRoutine gBatringRoutine;
extern const EnemyRoutine gPillerCannonRoutine;
extern const EnemyRoutine gGrandCannonRoutine;
extern const EnemyRoutine gShrimporinRoutine;
extern const EnemyRoutine gOmegaWhiteHandRoutine;
extern const EnemyRoutine gFlopperRoutine;
extern const EnemyRoutine gLamplortRoutine;
extern const EnemyRoutine gGyroCannonRoutine;
extern const EnemyRoutine gLemminglesNestRoutine;
extern const EnemyRoutine gLemminglesRoutine;
extern const EnemyRoutine gTopGabyoallRoutine;
extern const EnemyRoutine gSharksealXRoutine;
extern const EnemyRoutine gVolcanoBombRoutine;
extern const EnemyRoutine gCarryArmRoutine;
extern const EnemyRoutine gPantheonAquaRoutine;
extern const EnemyRoutine gChildreObjRoutine;
extern const EnemyRoutine gSnakecordRoutine;
extern const EnemyRoutine gHammerRoutine;
extern const EnemyRoutine gPurpleNerpleRoutine;
extern const EnemyRoutine gWormerRockDroneRoutine;
extern const EnemyRoutine gVolcaireRoutine;
extern const EnemyRoutine gTileCannonRoutine;
extern const EnemyRoutine gShellunoRoutine;
extern const EnemyRoutine gDeathtanzRockRoutine;
extern const EnemyRoutine gHeavyCannonBallRoutine;
extern const EnemyRoutine gWormerSnowBallRoutine;
extern const EnemyRoutine gBeetankRoutine;
extern const EnemyRoutine gSwordyRoutine;
extern const EnemyRoutine gPuffyRoutine;
extern const EnemyRoutine gCrossbyneRoutine;
extern const EnemyRoutine gBurnableWoodRoutine;
extern const EnemyRoutine gMellnetRoutine;
extern const EnemyRoutine gHellBouncerRoutine;
extern const EnemyRoutine gPantheonZombieRoutine;
extern const EnemyRoutine gPantheonAquaModObjRoutine;
extern const EnemyRoutine gGlacierleAtkArmRoutine;
extern const EnemyRoutine gOmegaGoldHandRoutine;
extern const EnemyRoutine gEyeCannonRoutine;
extern const EnemyRoutine gEnemy42Routine;
extern const EnemyRoutine gCapsuleCannonRoutine;
extern const EnemyRoutine gPantheonBomberRoutine;
extern const EnemyRoutine gHanumachineObjRoutine;
extern const EnemyRoutine gGallisniRoutine;
extern const EnemyRoutine gMothjiroRoutine;
extern const EnemyRoutine gMettaurRoutine;
extern const EnemyRoutine gPantheonBaseRoutine;
extern const EnemyRoutine gHanumachineNecroRoutine;
extern const EnemyRoutine gCarrybeeGRoutine;
extern const EnemyRoutine gOmegaZeroRockRoutine;
extern const EnemyRoutine gOmegaGoldSwordRoutine;
extern const EnemyRoutine gGeneratorCannonRoutine;
extern const EnemyRoutine gDeathlockRoutine;
extern const EnemyRoutine gClavekerRoutine;
extern const EnemyRoutine gSeimeranRoutine;
extern const EnemyRoutine gPetatriaRoutine;
extern const EnemyRoutine gEnemy59Routine;
extern const EnemyRoutine gEnemy60Routine;
extern const EnemyRoutine gEnemy61Routine;
extern const EnemyRoutine gShotloidRoutine;
extern const EnemyRoutine gEnemy63Routine;
extern const EnemyRoutine gPantheonFistRoutine;
extern const EnemyRoutine gShellcrawlerRoutine;
extern const EnemyRoutine gCannonHopperRoutine;
extern const EnemyRoutine gCattatankRoutine;
extern const EnemyRoutine gLeviathanMinigameEnemyRoutine;
extern const EnemyRoutine gHarpuiaMinigameEnemyRoutine;
extern const EnemyRoutine gCielMinigameEnemy1Routine;
extern const EnemyRoutine gCielMinigameEnemy2Routine;
extern const EnemyRoutine gEnemy72Routine;
#if AP
extern const EnemyRoutine gApZ2HopperRoutine;
extern const EnemyRoutine gApZ2HiveRoutine;
extern const EnemyRoutine gApZ2HottalookRoutine;
extern const EnemyRoutine gApZ2SoldierRoutine;
extern const EnemyRoutine gApZ2CarryarmRoutine, gApZ2CrateCarrierRoutine, gApZ2PanterHalfRoutine;
extern const EnemyRoutine gApZ2FortressArmRoutine, gApZ2GeneratorRoutine, gApZ2DroneRoutine, gApZ2FefnirBombRoutine;
extern const EnemyRoutine gApZ2WhirlPieceRoutine, gApZ2LanceTipRoutine, gApZ2TreeFrogRoutine, gApZ2FrogTongueRoutine;
extern const EnemyRoutine gApZ2SignaloidRoutine;
extern const EnemyRoutine gApZ2GolemArmRoutine;
extern const EnemyRoutine gApZ2HarpuiaBladeRoutine;
extern const EnemyRoutine gApZ2CopterRoutine;
extern const EnemyRoutine gApZ2EyeRoutine;
extern const EnemyRoutine gApZ2LeaperRoutine;
extern const EnemyRoutine gApZ2BarrierShipRoutine;
extern const EnemyRoutine gApZ2SnowballerRoutine;
extern const EnemyRoutine gApZ2RingCannonRoutine;
extern const EnemyRoutine gApZ2ShieldGuardRoutine;
extern const EnemyRoutine gApZ2BeeRoutine;
extern const EnemyRoutine gApZ2BeeCarrierRoutine;
extern const EnemyRoutine gApZ2MoleRoutine;
extern const EnemyRoutine gApZ2TowerRoutine;
extern const EnemyRoutine gApZ2SpikeballRoutine;
extern const EnemyRoutine gApZ2ShellRoutine;
extern const EnemyRoutine gApZ2WolfRoutine;
extern const EnemyRoutine gApZ2FlowerRoutine;
extern const EnemyRoutine gApZ2SpiderRoutine;
extern const EnemyRoutine gApZ2VultureRoutine;
extern const EnemyRoutine gApZ2CrabRoutine;
extern const EnemyRoutine gApZ2DesertPartRoutine;
extern const EnemyRoutine gApZ2DesertJawRoutine;
extern const EnemyRoutine gApZ2DesertTailRoutine;
extern const EnemyRoutine gApZ2FefnirPartRoutine;
extern const EnemyRoutine gApZ2FefnirWheelsRoutine;
extern const EnemyRoutine gApZ2FefnirBallRoutine;
extern const EnemyRoutine gApZ2MineSpawnerRoutine;
extern const EnemyRoutine gApZ2MineRoutine;
extern const EnemyRoutine gApZ2PylonRoutine;
extern const EnemyRoutine gApZ2DozerRoutine;
extern const EnemyRoutine gApZ2IceBlockRoutine;
extern const EnemyRoutine gApZ2FishRoutine;
extern const EnemyRoutine gApZ2IceDragonRoutine;
extern const EnemyRoutine gApZ2IceCrawlerRoutine;
extern const EnemyRoutine gApZ2SnowflakeRoutine;
extern const EnemyRoutine gApZ2IcicleRoutine;
extern const EnemyRoutine gApZ2IceCellEnemyRoutine;
extern const EnemyRoutine gApZ2WallFrogRoutine, gApZ2WallEyeRoutine;
extern const EnemyRoutine gApZ2SnakeArmRoutine, gApZ2SnakeSpringRoutine;
extern const EnemyRoutine gApZ2RaptorDroneRoutine, gApZ2VortexRoutine;
extern const EnemyRoutine gApZ2CrawlerRoutine, gApZ2BearPartRoutine, gApZ2IcePillarRoutine, gApZ2IceCapRoutine;
extern const EnemyRoutine gApZ2FlameArmRoutine, gApZ2FrostArmRoutine, gApZ2FrostBallRoutine, gApZ2FrostShardRoutine;
extern const EnemyRoutine gApZ2FishSpawnerRoutine;
#endif

// clang-format off
const EnemyRoutine* const gEnemyFnTable[ENEMY_COUNT] = {
  [ENEMY_P_GUARDIAN] =  &gPantheonGuardianRoutine,
  [ENEMY_P_HUNTER] =  &gPantheonHunterRoutine,
  [ENEMY_MEGAMILPA_NODE] =  &gMegamilpaNodeRoutine,
  [ENEMY_SHOTCOUNTER] =  &gShotcounterRoutine,
  [ENEMY_BATRING] =  &gBatringRoutine,
  [ENEMY_PILLER_CANNON] =  &gPillerCannonRoutine,
  [ENEMY_GRAND_CANNON] =  &gGrandCannonRoutine,
  [ENEMY_SHRIMPORIN] =  &gShrimporinRoutine,
  [ENEMY_OMEGA1W_HAND] =  &gOmegaWhiteHandRoutine,
  [ENEMY_FLOPPER] =  &gFlopperRoutine,
  [ENEMY_LAMPLORT] = &gLamplortRoutine,
  [ENEMY_GYRO_CANNON] = &gGyroCannonRoutine,
  [ENEMY_LEMMINGLES_NEST] = &gLemminglesNestRoutine,
  [ENEMY_LEMMINGLES] = &gLemminglesRoutine,
  [ENEMY_TOP_GABYOALL] = &gTopGabyoallRoutine,
  [ENEMY_SHARKSEAL_X] = &gSharksealXRoutine,
  [ENEMY_VOLCANO_BOMB] = &gVolcanoBombRoutine,
  [ENEMY_CARRY_ARM] = &gCarryArmRoutine,
  [ENEMY_P_AQUA] = &gPantheonAquaRoutine,
  [ENEMY_CHILDRE_OBJ] = &gChildreObjRoutine,
  [ENEMY_SNAKECORD] = &gSnakecordRoutine,
  [ENEMY_HAMMER] = &gHammerRoutine,
  [ENEMY_PURPLE_NERPLE] = &gPurpleNerpleRoutine,
  [ENEMY_WORMER_ROCK_DRONE] = &gWormerRockDroneRoutine,
  [ENEMY_VOLCAIRE] = &gVolcaireRoutine,
  [ENEMY_TILE_CANNON] = &gTileCannonRoutine,
  [ENEMY_SHELLUNO] = &gShellunoRoutine,
  [ENEMY_DEATHTANZ_ROCK] = &gDeathtanzRockRoutine,
  [ENEMY_HEAVY_CANNON_BALL] = &gHeavyCannonBallRoutine,
  [ENEMY_WORMER_SNOW_BALL] = &gWormerSnowBallRoutine,
  [ENEMY_BEETANK] = &gBeetankRoutine,
  [ENEMY_SWORDY] = &gSwordyRoutine,
  [ENEMY_PUFFY] = &gPuffyRoutine,
  [ENEMY_CROSSBYNE] = &gCrossbyneRoutine,
  [ENEMY_BURNABLE_WOOD] = &gBurnableWoodRoutine,
  [ENEMY_MELLNET] = &gMellnetRoutine,
  [ENEMY_HELL_BOUNCER] = &gHellBouncerRoutine,
  [ENEMY_P_ZOMBIE] = &gPantheonZombieRoutine,
  [ENEMY_P_AQUA_MOD_OBJ] = &gPantheonAquaModObjRoutine,
  [ENEMY_GLACIERLE_ARM] = &gGlacierleAtkArmRoutine,
  [ENEMY_OMEGA1G_HAND] = &gOmegaGoldHandRoutine,
  [ENEMY_EYE_CANNON] = &gEyeCannonRoutine,
  [ENEMY_42] = &gEnemy42Routine,
  [ENEMY_CAPSULE_CANNON] = &gCapsuleCannonRoutine,
  [ENEMY_P_BOMBER] = &gPantheonBomberRoutine,
  [ENEMY_HANUMACHINE_OBJ] = &gHanumachineObjRoutine,
  [ENEMY_GALLISNI] = &gGallisniRoutine,
  [ENEMY_MOTHJIRO] = &gMothjiroRoutine,
  [ENEMY_METTAUR] = &gMettaurRoutine,
  [ENEMY_P_BASE] = &gPantheonBaseRoutine,
  [ENEMY_HANUMACHINE_NECRO] = &gHanumachineNecroRoutine,
  [ENEMY_CARRYBEE_G] = &gCarrybeeGRoutine,
  [ENEMY_OZ_ROCK] = &gOmegaZeroRockRoutine,
  [ENEMY_OMEGA1G_SWORD] = &gOmegaGoldSwordRoutine,
  [ENEMY_GENERATOR_CANNON] = &gGeneratorCannonRoutine,
  [ENEMY_DEATHLOCK] = &gDeathlockRoutine,
  [ENEMY_CLAVEKER] = &gClavekerRoutine,
  [ENEMY_SEIMERAN] = &gSeimeranRoutine,
  [ENEMY_PETATRIA] = &gPetatriaRoutine,
  [ENEMY_59] = &gEnemy59Routine,
  [ENEMY_OMEGA_ZX_X] = &gEnemy60Routine,
  [ENEMY_61] = &gEnemy61Routine,
  [ENEMY_SHOTLOID] = &gShotloidRoutine,
  [ENEMY_63] = &gEnemy63Routine,
  [ENEMY_P_FIST] = &gPantheonFistRoutine,
  [ENEMY_SHELLCRAWLER] = &gShellcrawlerRoutine,
  [ENEMY_CANNON_HOPPER] = &gCannonHopperRoutine,
  [ENEMY_CATTATANK] = &gCattatankRoutine,
  [ENEMY_LEVIATHAN_MG] = &gLeviathanMinigameEnemyRoutine,
  [ENEMY_HARPUIA_MG] = &gHarpuiaMinigameEnemyRoutine,
  [ENEMY_CIEL_MG_1] = &gCielMinigameEnemy1Routine,
  [ENEMY_CIEL_MG_2] = &gCielMinigameEnemy2Routine,
  [ENEMY_72] = &gEnemy72Routine,
#if AP
  [ENEMY_Z2_HOPPER] = &gApZ2HopperRoutine,
  [ENEMY_Z2_HIVE] = &gApZ2HiveRoutine,
  [ENEMY_Z2_HOTTALOOK] = &gApZ2HottalookRoutine,
  [ENEMY_Z2_SOLDIER] = &gApZ2SoldierRoutine,
  [ENEMY_Z2_CARRYARM] = &gApZ2CarryarmRoutine,
  [ENEMY_Z2_CRATE_CARRIER] = &gApZ2CrateCarrierRoutine,
  [ENEMY_Z2_PANTER_HALF] = &gApZ2PanterHalfRoutine,
  [ENEMY_Z2_FORTRESS_ARM] = &gApZ2FortressArmRoutine,
  [ENEMY_Z2_GENERATOR] = &gApZ2GeneratorRoutine,
  [ENEMY_Z2_DRONE] = &gApZ2DroneRoutine,
  [ENEMY_Z2_FEFNIR_BOMB] = &gApZ2FefnirBombRoutine,
  [ENEMY_Z2_WHIRL_PIECE] = &gApZ2WhirlPieceRoutine,
  [ENEMY_Z2_LANCE_TIP] = &gApZ2LanceTipRoutine,
  [ENEMY_Z2_TREE_FROG] = &gApZ2TreeFrogRoutine,
  [ENEMY_Z2_FROG_TONGUE] = &gApZ2FrogTongueRoutine,
  [ENEMY_Z2_SIGNALOID] = &gApZ2SignaloidRoutine,
  [ENEMY_Z2_GOLEM_ARM] = &gApZ2GolemArmRoutine,
  [ENEMY_Z2_HARPUIA_BLADE] = &gApZ2HarpuiaBladeRoutine,
  [ENEMY_Z2_COPTER] = &gApZ2CopterRoutine,
  [ENEMY_Z2_EYE] = &gApZ2EyeRoutine,
  [ENEMY_Z2_LEAPER] = &gApZ2LeaperRoutine,
  [ENEMY_Z2_BARRIER_SHIP] = &gApZ2BarrierShipRoutine,
  [ENEMY_Z2_SNOWBALLER] = &gApZ2SnowballerRoutine,
  [ENEMY_Z2_RING_CANNON] = &gApZ2RingCannonRoutine,
  [ENEMY_Z2_SHIELD_GUARD] = &gApZ2ShieldGuardRoutine,
  [ENEMY_Z2_BEE] = &gApZ2BeeRoutine,
  [ENEMY_Z2_BEE_CARRIER] = &gApZ2BeeCarrierRoutine,
  [ENEMY_Z2_MOLE] = &gApZ2MoleRoutine,
  [ENEMY_Z2_TOWER] = &gApZ2TowerRoutine,
  [ENEMY_Z2_SPIKEBALL] = &gApZ2SpikeballRoutine,
  [ENEMY_Z2_SHELL] = &gApZ2ShellRoutine,
  [ENEMY_Z2_WOLF] = &gApZ2WolfRoutine,
  [ENEMY_Z2_FLOWER] = &gApZ2FlowerRoutine,
  [ENEMY_Z2_SPIDER] = &gApZ2SpiderRoutine,
  [ENEMY_Z2_VULTURE] = &gApZ2VultureRoutine,
  [ENEMY_Z2_CRAB] = &gApZ2CrabRoutine,
  [ENEMY_Z2_DESERT_PART] = &gApZ2DesertPartRoutine,
  [ENEMY_Z2_DESERT_JAW] = &gApZ2DesertJawRoutine,
  [ENEMY_Z2_DESERT_TAIL] = &gApZ2DesertTailRoutine,
  [ENEMY_Z2_FEFNIR_PART] = &gApZ2FefnirPartRoutine,
  [ENEMY_Z2_FEFNIR_WHEELS] = &gApZ2FefnirWheelsRoutine,
  [ENEMY_Z2_FEFNIR_BALL] = &gApZ2FefnirBallRoutine,
  [ENEMY_Z2_MINE_SPAWNER] = &gApZ2MineSpawnerRoutine,
  [ENEMY_Z2_MINE] = &gApZ2MineRoutine,
  [ENEMY_Z2_PYLON] = &gApZ2PylonRoutine,
  [ENEMY_Z2_DOZER] = &gApZ2DozerRoutine,
  [ENEMY_Z2_ICE_BLOCK] = &gApZ2IceBlockRoutine,
  [ENEMY_Z2_FISH] = &gApZ2FishRoutine,
  [ENEMY_Z2_FISH_SPAWNER] = &gApZ2FishSpawnerRoutine,
  [ENEMY_Z2_ICE_DRAGON] = &gApZ2IceDragonRoutine,
  [ENEMY_Z2_ICE_CRAWLER] = &gApZ2IceCrawlerRoutine,
  [ENEMY_Z2_SNOWFLAKE] = &gApZ2SnowflakeRoutine,
  [ENEMY_Z2_ICICLE] = &gApZ2IcicleRoutine,
  [ENEMY_Z2_ICE_CELL] = &gApZ2IceCellEnemyRoutine,
  [ENEMY_Z2_WALL_FROG] = &gApZ2WallFrogRoutine,
  [ENEMY_Z2_WALL_EYE] = &gApZ2WallEyeRoutine,
  [ENEMY_Z2_SNAKE_ARM] = &gApZ2SnakeArmRoutine,
  [ENEMY_Z2_SNAKE_SPRING] = &gApZ2SnakeSpringRoutine,
  [ENEMY_Z2_RAPTOR_DRONE] = &gApZ2RaptorDroneRoutine,
  [ENEMY_Z2_VORTEX] = &gApZ2VortexRoutine,
  [ENEMY_Z2_CRAWLER] = &gApZ2CrawlerRoutine,
  [ENEMY_Z2_BEAR_PART] = &gApZ2BearPartRoutine,
  [ENEMY_Z2_ICE_PILLAR] = &gApZ2IcePillarRoutine,
  [ENEMY_Z2_ICE_CAP] = &gApZ2IceCapRoutine,
  [ENEMY_Z2_FLAME_ARM] = &gApZ2FlameArmRoutine,
  [ENEMY_Z2_FROST_ARM] = &gApZ2FrostArmRoutine,
  [ENEMY_Z2_FROST_BALL] = &gApZ2FrostBallRoutine,
  [ENEMY_Z2_FROST_SHARD] = &gApZ2FrostShardRoutine,
#endif
};
// clang-format on
