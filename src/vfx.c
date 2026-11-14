#include "vfx.h"

#include "entity.h"
#include "global.h"

void InitVFXHeader(struct EntityHeader* h, struct VFX* p, s16 len) {
  s16 i;

  InitEntityHeader(h, ENTITY_VFX, &p->s, sizeof(struct VFX), len);
  for (i = 0; i < len; i++) {
    p[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gVFXHeaderPtr = h;
}

void UpdateVFXs(void) {
  struct EntityHeader* h = gVFXHeaderPtr;
  struct Entity* p = StartEntityListIteration(h);

  while (p != ((void*)&h->tail)) {
    if (gPause) {
      if (p->id == VFX_ELF_PARTICLE) ((EntityFunc)(p->onUpdate))(p);
    } else {
      ((EntityFunc)(p->onUpdate))(p);
    }
    p = GetNextEntity(h);
  }
}

void DeleteVFX(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

extern const VFXRoutine gSmokeRoutine;
extern const VFXRoutine gBubbleRoutine;
extern const VFXRoutine gChargeEffectRoutine;
extern const VFXRoutine gZeroDeathEffectRoutine;
extern const VFXRoutine gParticleRoutine;
extern const VFXRoutine gDashAfterImageRoutine;
extern const VFXRoutine gGhost7Routine;
extern const VFXRoutine gGhost8Routine;
extern const VFXRoutine gThunderEffectRoutine;
extern const VFXRoutine gFlameEffectRoutine;
extern const VFXRoutine gIceEffectRoutine;
extern const VFXRoutine gRippleRoutine;
extern const VFXRoutine gMissionAlertRoutine;
extern const VFXRoutine gEmotionBubbleRoutine;
extern const VFXRoutine gSlashedEnemyRoutine;
extern const VFXRoutine gGhost17Routine;
extern const VFXRoutine gGhost18Routine;
extern const VFXRoutine gMegamilpaDeadRoutine;
extern const VFXRoutine gGhost20Routine;
extern const VFXRoutine gBatringNecroRoutine;
extern const VFXRoutine gGhost22Routine;
extern const VFXRoutine gNecroRoutine;
extern const VFXRoutine gShrimporinVFXRoutine;
extern const VFXRoutine gVFX25Routine;
extern const VFXRoutine gIcebonIcedustRoutine;
extern const VFXRoutine gGhost27Routine;
extern const VFXRoutine gGhost28Routine;
extern const VFXRoutine gBurningFlameFXRoutine;
extern const VFXRoutine gGhost30Routine;
extern const VFXRoutine gGhost31Routine;
extern const VFXRoutine gGhost32Routine;
extern const VFXRoutine gGhost33Routine;
extern const VFXRoutine gBallChainRoutine;
extern const VFXRoutine gOrWormerDustCloudRoutine;
extern const VFXRoutine gVFX36Routine;
extern const VFXRoutine gVFX37Routine;
extern const VFXRoutine gVFX38Routine;
extern const VFXRoutine gVFX39Routine;
extern const VFXRoutine gVFX40Routine;
extern const VFXRoutine gVFX41Routine;
extern const VFXRoutine gExlifeIndicatorRoutine;
extern const VFXRoutine gVFX43Routine;
extern const VFXRoutine gVFX44Routine;
extern const VFXRoutine gIceballParticleRoutine;
extern const VFXRoutine gVFX46Routine;
extern const VFXRoutine gVFX47Routine;
extern const VFXRoutine gElfParticleRoutine;
extern const VFXRoutine gVFX49Routine;
extern const VFXRoutine gVFX50Routine;
extern const VFXRoutine gVFX51Routine;
extern const VFXRoutine gVFX52Routine;
extern const VFXRoutine gVFX53Routine;
extern const VFXRoutine gIcicleParticleRoutine;
extern const VFXRoutine gVFX55Routine;
extern const VFXRoutine gVFX56Routine;
extern const VFXRoutine gVFX57Routine;
extern const VFXRoutine gVFX58Routine;
extern const VFXRoutine gVFX59Routine;
extern const VFXRoutine gVFX60Routine;
extern const VFXRoutine gVFX61Routine;
extern const VFXRoutine gVFX62Routine;
extern const VFXRoutine gVFX63Routine;
extern const VFXRoutine gGhost64Routine;
extern const VFXRoutine gGhost65Routine;
extern const VFXRoutine gGhost66Routine;
extern const VFXRoutine gGhost67Routine;
extern const VFXRoutine gGhost68Routine;
extern const VFXRoutine gGhost69Routine;
extern const VFXRoutine gGhost70Routine;
extern const VFXRoutine gGhost71Routine;
extern const VFXRoutine gGhost72Routine;
extern const VFXRoutine gGhost73Routine;
extern const VFXRoutine gCyberSpaceElfRoutine;
extern const VFXRoutine gGhost75Routine;
extern const VFXRoutine gBossExplosionRoutine;
extern const VFXRoutine gMinigameIconRoutine;
extern const VFXRoutine gGhost78Routine;
extern const VFXRoutine gGhost79Routine;
extern const VFXRoutine gSnowRoutine;
extern const VFXRoutine gSmallNumberRoutine;
extern const VFXRoutine gGhost82Routine;
extern const VFXRoutine gGhost83Routine;
extern const VFXRoutine gGhost84Routine;
#if AP
extern const VFXRoutine gApZ2HopperTopRoutine;
extern const VFXRoutine gApZ2HottalookShardRoutine;
extern const VFXRoutine gApZ2CarryarmDebrisRoutine;
extern const VFXRoutine gApZ2SignaloidEffectRoutine;
extern const VFXRoutine gApZ2GolemFootRoutine;
extern const VFXRoutine gApZ2EyeDebrisRoutine;
extern const VFXRoutine gApZ2BarrierShipWreckRoutine;
extern const VFXRoutine gApZ2RingCannonSparksRoutine;
extern const VFXRoutine gApZ2ShieldGuardTopRoutine;
extern const VFXRoutine gApZ2BeeHeadRoutine;
extern const VFXRoutine gApZ2TowerPieceRoutine;
extern const VFXRoutine gApZ2SpikeballHalfRoutine;
extern const VFXRoutine gApZ2ShellPieceRoutine;
extern const VFXRoutine gApZ2WolfPieceRoutine;
extern const VFXRoutine gApZ2SpiderPieceRoutine;
extern const VFXRoutine gApZ2VultureHalfRoutine;
extern const VFXRoutine gApZ2CrabPartRoutine;
extern const VFXRoutine gApZ2RockRoutine;
extern const VFXRoutine gApZ2FefnirBubbleRoutine;
extern const VFXRoutine gApZ2FefnirExplosionRoutine;
extern const VFXRoutine gApZ2FefnirSmokeRoutine;
extern const VFXRoutine gApZ2FefnirSparkRoutine;
extern const VFXRoutine gApZ2MineBlastRoutine;
extern const VFXRoutine gApZ2IcePuffRoutine;
extern const VFXRoutine gApZ2WaterSplashRoutine;
extern const VFXRoutine gApZ2StreakRoutine, gApZ2RaptorTrailRoutine;
extern const VFXRoutine gApZ2FrostCloudRoutine, gApZ2CrawlerBitRoutine, gApZ2BearIceRoutine;
extern const VFXRoutine gApZ2ElfSparkleRoutine, gApZ2PanterHeldRoutine, gApZ2FortressJetRoutine;
extern const VFXRoutine gApZ2MagnionFxRoutine, gApZ2MachineBitRoutine, gApZ2FefnirAuraRoutine, gApZ2FefnirExRoutine,
    gApZ2LeafRoutine, gApZ2FrogDustRoutine;
extern const VFXRoutine gApZ2IceBurstRoutine;
extern const VFXRoutine gApZ2DozerTopRoutine;
extern const VFXRoutine gApZ2FishBitRoutine;
extern const VFXRoutine gApZ2FrostBreathRoutine;
#endif

// clang-format off
const VFXRoutine* const gVFXFnTable[VFX_COUNT] = {
    [VFX_SMOKE] =  &gSmokeRoutine,
    [VFX_BUBBLE] = &gBubbleRoutine,
    [VFX_CHARGE_EFFECT] =  &gChargeEffectRoutine,
    [VFX_UNK_003] =  &gSmokeRoutine,
    [VFX_DEATH_EFFECT] =  &gZeroDeathEffectRoutine,
    [VFX_PARTICLE] =  &gParticleRoutine,
    [VFX_AFTER_IMAGE] =  &gDashAfterImageRoutine,
    [VFX_UNK_007] =  &gGhost7Routine,
    [VFX_UNK_008] =  &gGhost8Routine,
    [VFX_THUNDER_EFFECT] =  &gThunderEffectRoutine,
    [VFX_FLAME_EFFECT] = &gFlameEffectRoutine,
    [VFX_ICE_EFFECT] = &gIceEffectRoutine,
    [VFX_RIPPLE] = &gRippleRoutine,
    [VFX_UNK_013] = &gSmokeRoutine,
    [VFX_MISSION_ALERT] = &gMissionAlertRoutine,
    [VFX_EMOTION_BUBBLE] = &gEmotionBubbleRoutine,
    [VFX_SLASHED_ENEMY] = &gSlashedEnemyRoutine,
    [VFX_UNK_017] = &gGhost17Routine,
    [VFX_UNK_018] = &gGhost18Routine,
    [VFX_MEGAMILPA_DEAD] = &gMegamilpaDeadRoutine,
    [VFX_UNK_020] = &gGhost20Routine,
    [VFX_BATRING_NECRO] = &gBatringNecroRoutine,
    [VFX_UNK_022] = &gGhost22Routine,
    [VFX_NECRO] = &gNecroRoutine,
    [VFX_SHRIMPORIN] = &gShrimporinVFXRoutine,
    [VFX_UNK_025] = &gVFX25Routine,
    [VFX_UNK_026] = &gIcebonIcedustRoutine,
    [VFX_UNK_027] = &gGhost27Routine,
    [VFX_UNK_028] = &gGhost28Routine,
    [VFX_BURNING_FLAME_FX] = &gBurningFlameFXRoutine,
    [VFX_UNK_030] = &gGhost30Routine,
    [VFX_UNK_031] = &gGhost31Routine,
    [VFX_P_AQUA] = &gGhost32Routine,
    [VFX_UNK_033] = &gGhost33Routine,
    [VFX_BALLCHAIN] = &gBallChainRoutine,
    [VFX_ORWORMER_DUST_CLOUD] = &gOrWormerDustCloudRoutine,
    [VFX_UNK_036] = &gVFX36Routine,
    [VFX_UNK_037] = &gVFX37Routine,
    [VFX_UNK_038] = &gVFX38Routine,
    [VFX_UNK_039] = &gVFX39Routine,
    [VFX_UNK_040] = &gVFX40Routine,
    [VFX_UNK_041] = &gVFX41Routine,
    [VFX_EXLIFE_INDICATOR] = &gExlifeIndicatorRoutine,
    [VFX_UNK_043] = &gVFX43Routine,
    [VFX_UNK_MMBN4_044] = &gVFX44Routine,
    [VFX_ICEBALL_PARTICLE] = &gIceballParticleRoutine,
    [VFX_UNK_046] = &gVFX46Routine,
    [VFX_UNK_047] = &gVFX47Routine,
    [VFX_ELF_PARTICLE] = &gElfParticleRoutine,
    [VFX_UNK_049] = &gVFX49Routine,
    [VFX_UNK_050] = &gVFX50Routine,
    [VFX_UNK_051] = &gVFX51Routine,
    [VFX_UNK_052] = &gVFX52Routine,
    [VFX_UNK_053] = &gVFX53Routine,
    [VFX_ICICLE_PARTICLE] = &gIcicleParticleRoutine,
    [VFX_UNK_055] = &gVFX55Routine,
    [VFX_COPYX_REFLECTLASER] = &gVFX56Routine,
    [VFX_UNK_057] = &gVFX57Routine,
    [VFX_UNK_058] = &gVFX58Routine,
    [VFX_UNK_059] = &gVFX59Routine,
    [VFX_UNK_060] = &gVFX60Routine,
    [VFX_UNK_061] = &gVFX61Routine,
    [VFX_UNK_062] = &gVFX62Routine,
    [VFX_UNK_063] = &gVFX63Routine,
    [VFX_UNK_064] = &gGhost64Routine,
    [VFX_UNK_065] = &gGhost65Routine,
    [VFX_UNK_066] = &gGhost66Routine,
    [VFX_UNK_067] = &gGhost67Routine,
    [VFX_UNK_068] = &gGhost68Routine,
    [VFX_UNK_069] = &gGhost69Routine,
    [VFX_UNK_070] = &gGhost70Routine,
    [VFX_MISSION_INFO] = &gGhost71Routine,
    [VFX_UNK_072] = &gGhost72Routine,
    [VFX_UNK_073] = &gGhost73Routine,
    [VFX_CS_ELF] = &gCyberSpaceElfRoutine,
    [VFX_UNK_075] = &gGhost75Routine,
    [VFX_BOSS_EXPLOSION] = &gBossExplosionRoutine,
    [VFX_MINIGAME_ICON] = &gMinigameIconRoutine,
    [VFX_UNK_078] = &gGhost78Routine,
    [VFX_UNK_079] = &gGhost79Routine,
    [VFX_UNK_080] = &gSnowRoutine,
    [VFX_SMALL_NUMBER] = &gSmallNumberRoutine,
    [VFX_UNK_082] = &gGhost82Routine,
    [VFX_UNK_083] = &gGhost83Routine,
    [VFX_UNK_084] = &gGhost84Routine,
#if AP
    [VFX_Z2_HOPPER_TOP] = &gApZ2HopperTopRoutine,
    [VFX_Z2_HOTTALOOK_SHARD] = &gApZ2HottalookShardRoutine,
    [VFX_Z2_CARRYARM_DEBRIS] = &gApZ2CarryarmDebrisRoutine,
    [VFX_Z2_SIGNALOID] = &gApZ2SignaloidEffectRoutine,
    [VFX_Z2_GOLEM_FOOT] = &gApZ2GolemFootRoutine,
    [VFX_Z2_EYE_DEBRIS] = &gApZ2EyeDebrisRoutine,
    [VFX_Z2_BARRIER_SHIP_WRECK] = &gApZ2BarrierShipWreckRoutine,
    [VFX_Z2_RING_CANNON_SPARKS] = &gApZ2RingCannonSparksRoutine,
    [VFX_Z2_SHIELD_GUARD_TOP] = &gApZ2ShieldGuardTopRoutine,
    [VFX_Z2_BEE_HEAD] = &gApZ2BeeHeadRoutine,
    [VFX_Z2_TOWER_PIECE] = &gApZ2TowerPieceRoutine,
    [VFX_Z2_SPIKEBALL_HALF] = &gApZ2SpikeballHalfRoutine,
    [VFX_Z2_SHELL_PIECE] = &gApZ2ShellPieceRoutine,
    [VFX_Z2_WOLF_PIECE] = &gApZ2WolfPieceRoutine,
    [VFX_Z2_SPIDER_PIECE] = &gApZ2SpiderPieceRoutine,
    [VFX_Z2_VULTURE_HALF] = &gApZ2VultureHalfRoutine,
    [VFX_Z2_CRAB_PART] = &gApZ2CrabPartRoutine,
    [VFX_Z2_ROCK] = &gApZ2RockRoutine,
    [VFX_Z2_FEFNIR_BUBBLE] = &gApZ2FefnirBubbleRoutine,
    [VFX_Z2_FEFNIR_EXPLOSION] = &gApZ2FefnirExplosionRoutine,
    [VFX_Z2_FEFNIR_SMOKE] = &gApZ2FefnirSmokeRoutine,
    [VFX_Z2_FEFNIR_SPARK] = &gApZ2FefnirSparkRoutine,
    [VFX_Z2_MINE_BLAST] = &gApZ2MineBlastRoutine,
    [VFX_Z2_ICE_PUFF] = &gApZ2IcePuffRoutine,
    [VFX_Z2_WATER_SPLASH] = &gApZ2WaterSplashRoutine,
    [VFX_Z2_STREAK] = &gApZ2StreakRoutine,
    [VFX_Z2_RAPTOR_TRAIL] = &gApZ2RaptorTrailRoutine,
    [VFX_Z2_FROST_CLOUD] = &gApZ2FrostCloudRoutine,
    [VFX_Z2_CRAWLER_BIT] = &gApZ2CrawlerBitRoutine,
    [VFX_Z2_BEAR_ICE] = &gApZ2BearIceRoutine,
    [VFX_Z2_ELF_SPARKLE] = &gApZ2ElfSparkleRoutine,
    [VFX_Z2_PANTER_HELD] = &gApZ2PanterHeldRoutine,
    [VFX_Z2_FORTRESS_JET] = &gApZ2FortressJetRoutine,
    [VFX_Z2_MAGNION_FX] = &gApZ2MagnionFxRoutine,
    [VFX_Z2_MACHINE_BIT] = &gApZ2MachineBitRoutine,
    [VFX_Z2_FEFNIR_AURA] = &gApZ2FefnirAuraRoutine,
    [VFX_Z2_FEFNIR_EX] = &gApZ2FefnirExRoutine,
    [VFX_Z2_LEAF] = &gApZ2LeafRoutine,
    [VFX_Z2_FROG_DUST] = &gApZ2FrogDustRoutine,
    [VFX_Z2_ICE_BURST] = &gApZ2IceBurstRoutine,
    [VFX_Z2_DOZER_TOP] = &gApZ2DozerTopRoutine,
    [VFX_Z2_FISH_BIT] = &gApZ2FishBitRoutine,
    [VFX_Z2_FROST_BREATH] = &gApZ2FrostBreathRoutine,
#endif
};
// clang-format on
