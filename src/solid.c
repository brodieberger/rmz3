#include "solid.h"

#include "entity.h"
#include "global.h"

void InitSolidHeader(struct EntityHeader* h, struct Solid* p, s16 len) {
  s16 i;

  InitEntityHeader(h, ENTITY_SOLID, &p->s, sizeof(struct Solid), len);
  for (i = 0; i < len; i++) {
    p[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gSolidHeaderPtr = h;
}

void DeleteSolid(Object* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  (p->s).flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

extern const SolidRoutine gIcebonRoutine;
extern const SolidRoutine gIcebonIceRoutine;
extern const SolidRoutine gDoor2DBlueRoutine;
extern const SolidRoutine gBurningFlameRoutine;
extern const SolidRoutine gIronStarRoutine;
extern const SolidRoutine gHeavyCannonRoutine;
extern const SolidRoutine gLavaGeyserPlatformRoutine;
extern const SolidRoutine gLavaGeyserRoutine;
extern const SolidRoutine gLavaRiverPlatformRoutine;
extern const SolidRoutine gDoor3DRoutine;
extern const SolidRoutine gSolid10Routine;
extern const SolidRoutine gSolid11Routine;
extern const SolidRoutine gAnubisCoffinRoutine;
extern const SolidRoutine gSolid13Routine;
extern const SolidRoutine gLocomoIFPlatformRoutine;
extern const SolidRoutine gGlacierleArmRoutine;
extern const SolidRoutine gSolid16Routine;
extern const SolidRoutine gSubArcadiaPlatformRoutine;
extern const SolidRoutine gSnowboardRoutine;
extern const SolidRoutine gBaseElevatorRoutine;
extern const SolidRoutine gDoor2DGrayVRoutine;
extern const SolidRoutine gScriptActorRoutine;
extern const SolidRoutine gDoor2DGrayHRoutine;
extern const SolidRoutine gTurtloidSRoutine;
extern const SolidRoutine gPhantomTeleporterRoutine;
extern const SolidRoutine gAreaX2WeilLaboPlatformRoutine;
extern const SolidRoutine gIceBlockRoutine;
extern const SolidRoutine gSolid27Routine;
extern const SolidRoutine gMinigameNinjaStarRoutine;
extern const SolidRoutine gMobNPCRoutine;
extern const SolidRoutine gMainNPCRoutine;
extern const SolidRoutine gCyberSpaceDoorRoutine;
extern const SolidRoutine gLightSwitchRoutine;
extern const SolidRoutine gSolid33Routine;
extern const SolidRoutine gToggleSwitchRedRoutine;
extern const SolidRoutine gContainerRoutine;
extern const SolidRoutine gSolid36Routine;
extern const SolidRoutine gFlyingFishRoutine;
extern const SolidRoutine gSeagullsRoutine;
extern const SolidRoutine gCatRoutine;
extern const SolidRoutine gModPlantRoutine;
extern const SolidRoutine gVolcanoCoffinRoutine;
extern const SolidRoutine gCielMinigameObjRoutine;
extern const SolidRoutine gSolid43Routine;
extern const SolidRoutine gSolid44Routine;
extern const SolidRoutine gGiantElevatorPierRoutine;
extern const SolidRoutine gGiantElevatorPlatformRoutine;
extern const SolidRoutine gAnatreCubeRoutine;
extern const SolidRoutine gCielComputerRoutine;
extern const SolidRoutine gGraffitiRoutine;
extern const SolidRoutine gStructuralSteelRoutine;
extern const SolidRoutine gModElfRoutine;
extern const SolidRoutine gToggleSwitchYellowRoutine;
extern const SolidRoutine gOceanRodWallRoutine;
extern const SolidRoutine gSeaLevelButtonRoutine;
extern const SolidRoutine gChildreShipRoutine;
#if AP
extern const SolidRoutine gApZ2SandBlockRoutine;
extern const SolidRoutine gApZ2IntroHunterRoutine;
extern const SolidRoutine gApZ2IntroJawRoutine;
extern const SolidRoutine gApZ2SlabRoutine;
extern const SolidRoutine gApZ2BeatenFefnirRoutine;
extern const SolidRoutine gApZ2GateRoutine;
extern const SolidRoutine gApZ2FloeRoutine;
extern const SolidRoutine gApZ2FallenRoutine, gApZ2CastRoutine, gApZ2DoorRoutine;
extern const SolidRoutine gApZ2RescueRoutine, gApZ2PadRoutine, gApZ2LiftRoutine, gApZ2ScoutRoutine, gApZ2ThiefRoutine,
    gApZ2BabyElfRoutine, gApZ2XRoutine, gApZ2WallShelfRoutine, gApZ2WallArmRoutine;
extern const SolidRoutine gApZ2IceCellRoutine;
extern const SolidRoutine gApZ2BoxRoutine;
#endif

// clang-format off
const SolidRoutine* const gSolidFnTable[SOLID_ENTITY_COUNT] = {
    [SOLID_ICEBON] =                    &gIcebonRoutine,
    [SOLID_ICEBON_ICE] =                &gIcebonIceRoutine,
    [SOLID_DOOR_2D_BLUE] =              &gDoor2DBlueRoutine,
    [SOLID_BURNING_FLAME] =             &gBurningFlameRoutine,
    [SOLID_UNK_004] =                   &gIronStarRoutine,
    [SOLID_HEAVY_CANNON] =              &gHeavyCannonRoutine,
    [SOLID_LAVA_GEYSER_PLATFORM] =      &gLavaGeyserPlatformRoutine,
    [SOLID_LAVA_GEYSER] =               &gLavaGeyserRoutine,
    [SOLID_LAVA_RIVER_PLATFORM] =       &gLavaRiverPlatformRoutine,
    [SOLID_DOOR_3D] =                   &gDoor3DRoutine,
    [SOLID_UNK_010] =                   &gSolid10Routine,
    [SOLID_UNK_011] =                   &gSolid11Routine,
    [SOLID_ANUBIS_COFFIN] =             &gAnubisCoffinRoutine,
    [SOLID_UNK_013] =                   &gSolid13Routine,
    [SOLID_LOCOMOIF_PLATFORM] =         &gLocomoIFPlatformRoutine,
    [SOLID_GLACIERLE_ARM] =             &gGlacierleArmRoutine,
    [SOLID_UNK_016] =                   &gSolid16Routine,
    [SOLID_PLATFORM_SUBARCADIA] =       &gSubArcadiaPlatformRoutine,
    [SOLID_SNOWBOARD] =                 &gSnowboardRoutine,
    [SOLID_BASE_ELEVATOR] =             &gBaseElevatorRoutine,
    [SOLID_DOOR_2D_GRAY_V] =            &gDoor2DGrayVRoutine,
    [SOLID_SCRIPT_ACTOR] =              &gScriptActorRoutine,
    [SOLID_DOOR_2D_GRAY_H] =            &gDoor2DGrayHRoutine,
    [SOLID_TURTLOID_S] =                &gTurtloidSRoutine,
    [SOLID_PHANTOM_TELEPORTER] =        &gPhantomTeleporterRoutine,
    [SOLID_PLATFORM_AREAX2_WEILLABO] =  &gAreaX2WeilLaboPlatformRoutine,
    [SOLID_ICE_BLOCK] =                 &gIceBlockRoutine,
    [SOLID_UNK_027] =                   &gSolid27Routine,
    [SOLID_MG_NINJASTAR] =              &gMinigameNinjaStarRoutine,
    [SOLID_MOB_NPC] =                   &gMobNPCRoutine,
    [SOLID_MAIN_NPC] =                  &gMainNPCRoutine,
    [SOLID_CYBERSPACE_DOOR] =           &gCyberSpaceDoorRoutine,
    [SOLID_LIGHT_SWITCH] =              &gLightSwitchRoutine,
    [SOLID_PLATFORM_33] =               &gSolid33Routine,
    [SOLID_TOGGLE_SWITCH_RED] =         &gToggleSwitchRedRoutine,
    [SOLID_CONTAINER] =                 &gContainerRoutine,
    [SOLID_PLATFORM_MISSILE] =          &gSolid36Routine,
    [SOLID_FLYING_FISH] =               &gFlyingFishRoutine,
    [SOLID_SEAGULLS] =                  &gSeagullsRoutine,
    [SOLID_CAT] =                       &gCatRoutine,
    [SOLID_MOD_PLANT] =                 &gModPlantRoutine,
    [SOLID_VOLCANO_COFFIN] =            &gVolcanoCoffinRoutine,
    [SOLID_UNK_042] =                   &gCielMinigameObjRoutine,
    [SOLID_UNK_043] =                   &gSolid43Routine,
    [SOLID_UNK_044] =                   &gSolid44Routine,
    [SOLID_GE_PIER] =                   &gGiantElevatorPierRoutine,
    [SOLID_GE_PLATFORM] =               &gGiantElevatorPlatformRoutine,
    [SOLID_ANATRE_CUBE] =               &gAnatreCubeRoutine,
    [SOLID_CIEL_COMPUTER] =             &gCielComputerRoutine,
    [SOLID_GRAFFITI] =                  &gGraffitiRoutine,
    [SOLID_STRUCTURAL_STEEL] =          &gStructuralSteelRoutine,
    [SOLID_MOD_ELF] =                   &gModElfRoutine,
    [SOLID_TOGGLE_SWITCH_YELLOW] =      &gToggleSwitchYellowRoutine,
    [SOLID_OCEAN_ROD_WALL] =            &gOceanRodWallRoutine,
    [SOLID_SEA_LV_BTN] =                &gSeaLevelButtonRoutine,
    [SOLID_CHILDRE_SHIP] =              &gChildreShipRoutine,
#if AP
    [SOLID_Z2_SAND_BLOCK] =             &gApZ2SandBlockRoutine,
    [SOLID_Z2_INTRO_HUNTER] =           &gApZ2IntroHunterRoutine,
    [SOLID_Z2_INTRO_JAW] =              &gApZ2IntroJawRoutine,
    [SOLID_Z2_SLAB] =                   &gApZ2SlabRoutine,
    [SOLID_Z2_BEATEN_FEFNIR] =          &gApZ2BeatenFefnirRoutine,
    [SOLID_Z2_GATE] =                   &gApZ2GateRoutine,
    [SOLID_Z2_FLOE] =                   &gApZ2FloeRoutine,
    [SOLID_Z2_FALLEN] =                 &gApZ2FallenRoutine,
    [SOLID_Z2_CAST] =                   &gApZ2CastRoutine,
    [SOLID_Z2_DOOR] =                   &gApZ2DoorRoutine,
    [SOLID_Z2_RESCUE] =                 &gApZ2RescueRoutine,
    [SOLID_Z2_PAD] =                    &gApZ2PadRoutine,
    [SOLID_Z2_LIFT] =                   &gApZ2LiftRoutine,
    [SOLID_Z2_SCOUT] =                  &gApZ2ScoutRoutine,
    [SOLID_Z2_RESCUE_THIEF] =           &gApZ2ThiefRoutine,
    [SOLID_Z2_BABY_ELF] =               &gApZ2BabyElfRoutine,
    [SOLID_Z2_X] =                      &gApZ2XRoutine,
    [SOLID_Z2_WALL_SHELF] =             &gApZ2WallShelfRoutine,
    [SOLID_Z2_WALL_ARM] =               &gApZ2WallArmRoutine,
    [SOLID_Z2_ICE_CELL] =               &gApZ2IceCellRoutine,
    [SOLID_Z2_BOX] =                    &gApZ2BoxRoutine,
#endif
};
// clang-format on
