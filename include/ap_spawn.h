#ifndef GUARD_RMZ3_AP_SPAWN_H
#define GUARD_RMZ3_AP_SPAWN_H

// The AP build's src/spawn.c
extern const struct SpawnTemplate gApSpaceCraftEntity[];
extern const struct PreloadEntity gApSpaceCraftStatic[];
extern const struct SpawnPoint gApSpaceCraftEntityCoord[];
extern const struct SpawnTemplate gApVolcanoEntity[];
extern const struct PreloadEntity gApVolcanoStatic[];
extern const struct SpawnPoint gApVolcanoEntityCoord[];
extern const struct SpawnTemplate gApOceanEntity[];
extern const struct PreloadEntity gApOceanStatic[];
extern const struct SpawnPoint gApOceanEntityCoord[];
extern const struct SpawnTemplate gApRepairFactoryEntity[];
extern const struct PreloadEntity gApRepairFactoryStatic[];
extern const struct SpawnPoint gApRepairFactoryEntityCoord[];
extern const struct SpawnTemplate gApOldResidentialEntity[];
extern const struct PreloadEntity gApOldResidentialStatic[];
extern const struct SpawnPoint gApOldResidentialEntityCoord[];
extern const struct SpawnTemplate gApMissileFactoryEntity[];
extern const struct PreloadEntity gApMissileFactoryStatic[];
extern const struct SpawnPoint gApMissileFactoryEntityCoord[];
extern const struct SpawnTemplate gApTwilightDesertEntity[];
extern const struct PreloadEntity gApTwilightDesertStatic[];
extern const struct SpawnPoint gApTwilightDesertEntityCoord[];
extern const struct SpawnTemplate gApAnatreForestEntity[];
extern const struct PreloadEntity gApAnatreForestStatic[];
extern const struct SpawnPoint gApAnatreForestEntityCoord[];
extern const struct SpawnTemplate gApIceBaseEntity[];
extern const struct PreloadEntity gApIceBaseStatic[];
extern const struct SpawnPoint gApIceBaseEntityCoord[];
extern const struct SpawnTemplate gApAreaX2Entity[];
extern const struct PreloadEntity gApAreaX2Static[];
extern const struct SpawnPoint gApAreaX2EntityCoord[];
extern const struct SpawnTemplate gApEnergyFacilityEntity[];
extern const struct PreloadEntity gApEnergyFacilityStatic[];
extern const struct SpawnPoint gApEnergyFacilityEntityCoord[];
extern const struct SpawnTemplate gApSnowyPlainsEntity[];
extern const struct PreloadEntity gApSnowyPlainsStatic[];
extern const struct SpawnPoint gApSnowyPlainsEntityCoord[];
extern const struct SpawnTemplate gApSunkenLibraryEntity[];
extern const struct PreloadEntity gApSunkenLibraryStatic[];
extern const struct SpawnPoint gApSunkenLibraryEntityCoord[];
extern const struct SpawnTemplate gApGiantElevatorEntity[];
extern const struct PreloadEntity gApGiantElevatorStatic[];
extern const struct SpawnPoint gApGiantElevatorEntityCoord[];
extern const struct SpawnTemplate gApSubArcadiaEntity[];
extern const struct PreloadEntity gApSubArcadiaStatic[];
extern const struct SpawnPoint gApSubArcadiaEntityCoord[];
extern const struct SpawnTemplate gApWeilLaboEntity[];
extern const struct PreloadEntity gApWeilLaboStatic[];
extern const struct SpawnPoint gApWeilLaboEntityCoord[];
extern const struct SpawnTemplate gApResistanceBaseEntity[];
extern const struct PreloadEntity gApResistanceBaseStatic[];
extern const struct SpawnPoint gApResistanceBaseEntityCoord[];

#define AP_STAGE_ENTITY_TEMPLATES \
  [STAGE_SPACE_CRAFT] = gApSpaceCraftEntity, \
  [STAGE_VOLCANO] = gApVolcanoEntity, \
  [STAGE_OCEAN] = gApOceanEntity, \
  [STAGE_REPAIR_FACTORY] = gApRepairFactoryEntity, \
  [STAGE_OLD_RESIDENTIAL] = gApOldResidentialEntity, \
  [STAGE_MISSILE_FACTORY] = gApMissileFactoryEntity, \
  [STAGE_TWILIGHT_DESERT] = gApTwilightDesertEntity, \
  [STAGE_ANATRE_FOREST] = gApAnatreForestEntity, \
  [STAGE_ICE_BASE] = gApIceBaseEntity, \
  [STAGE_AREA_X2] = gApAreaX2Entity, \
  [STAGE_E_FACILITY] = gApEnergyFacilityEntity, \
  [STAGE_SNOWY_PLAINS] = gApSnowyPlainsEntity, \
  [STAGE_SUNKEN_LIBRARY] = gApSunkenLibraryEntity, \
  [STAGE_GIANT_ELEVATOR] = gApGiantElevatorEntity, \
  [STAGE_SUB_ARCADIA] = gApSubArcadiaEntity, \
  [STAGE_WEILS_LABO] = gApWeilLaboEntity, \
  [STAGE_BASE] = gApResistanceBaseEntity,

#define AP_STAGE_PRELOAD_ENTITIES \
  [STAGE_SPACE_CRAFT] = gApSpaceCraftStatic, \
  [STAGE_VOLCANO] = gApVolcanoStatic, \
  [STAGE_OCEAN] = gApOceanStatic, \
  [STAGE_REPAIR_FACTORY] = gApRepairFactoryStatic, \
  [STAGE_OLD_RESIDENTIAL] = gApOldResidentialStatic, \
  [STAGE_MISSILE_FACTORY] = gApMissileFactoryStatic, \
  [STAGE_TWILIGHT_DESERT] = gApTwilightDesertStatic, \
  [STAGE_ANATRE_FOREST] = gApAnatreForestStatic, \
  [STAGE_ICE_BASE] = gApIceBaseStatic, \
  [STAGE_AREA_X2] = gApAreaX2Static, \
  [STAGE_E_FACILITY] = gApEnergyFacilityStatic, \
  [STAGE_SNOWY_PLAINS] = gApSnowyPlainsStatic, \
  [STAGE_SUNKEN_LIBRARY] = gApSunkenLibraryStatic, \
  [STAGE_GIANT_ELEVATOR] = gApGiantElevatorStatic, \
  [STAGE_SUB_ARCADIA] = gApSubArcadiaStatic, \
  [STAGE_WEILS_LABO] = gApWeilLaboStatic, \
  [STAGE_BASE] = gApResistanceBaseStatic,

#define AP_STAGE_SPAWN_POINTS \
  [STAGE_SPACE_CRAFT] = gApSpaceCraftEntityCoord, \
  [STAGE_VOLCANO] = gApVolcanoEntityCoord, \
  [STAGE_OCEAN] = gApOceanEntityCoord, \
  [STAGE_REPAIR_FACTORY] = gApRepairFactoryEntityCoord, \
  [STAGE_OLD_RESIDENTIAL] = gApOldResidentialEntityCoord, \
  [STAGE_MISSILE_FACTORY] = gApMissileFactoryEntityCoord, \
  [STAGE_TWILIGHT_DESERT] = gApTwilightDesertEntityCoord, \
  [STAGE_ANATRE_FOREST] = gApAnatreForestEntityCoord, \
  [STAGE_ICE_BASE] = gApIceBaseEntityCoord, \
  [STAGE_AREA_X2] = gApAreaX2EntityCoord, \
  [STAGE_E_FACILITY] = gApEnergyFacilityEntityCoord, \
  [STAGE_SNOWY_PLAINS] = gApSnowyPlainsEntityCoord, \
  [STAGE_SUNKEN_LIBRARY] = gApSunkenLibraryEntityCoord, \
  [STAGE_GIANT_ELEVATOR] = gApGiantElevatorEntityCoord, \
  [STAGE_SUB_ARCADIA] = gApSubArcadiaEntityCoord, \
  [STAGE_WEILS_LABO] = gApWeilLaboEntityCoord, \
  [STAGE_BASE] = gApResistanceBaseEntityCoord,

#endif  // GUARD_RMZ3_AP_SPAWN_H
