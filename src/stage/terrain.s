  .include "asm/macros.inc"

  .balign 4, 0
  .section .rodata

.global gStageTerrains
gStageTerrains: @ 0x0863c578
    @ struct TerrainHeader
    @ metatile.bin                  metatile_attr.bin                screen.bin
    .4byte gStage0_Tiles-.,         gStage0_TileAttrs-(.-4),         gStage0_Chunks-(.-8)
    .4byte gSpaceCraft_Tiles-.,     gSpaceCraft_TileAttrs-(.-4),     gSpaceCraft_Chunks-(.-8)
    .4byte gVolcano_Tiles-.,        gVolcano_TileAttrs-(.-4),        gVolcano_Chunks-(.-8)
    .4byte gOcean_Tiles-.,          gOcean_TileAttrs-(.-4),          gOcean_Chunks-(.-8)
    .4byte gRepairFactory_Tiles-.,  gRepairFactory_TileAttrs-(.-4),  gRepairFactory_Chunks-(.-8)
    .4byte gOldResidential_Tiles-., gOldResidential_TileAttrs-(.-4), gOldResidential_Chunks-(.-8)
    .4byte gMissileFactory_Tiles-., gMissileFactory_TileAttrs-(.-4), gMissileFactory_Chunks-(.-8)
    .4byte gTwilightDesert_Tiles-., gTwilightDesert_TileAttrs-(.-4), gTwilightDesert_Chunks-(.-8)
    .4byte gAnatreForest_Tiles-.,   gAnatreForest_TileAttrs-(.-4),   gAnatreForest_Chunks-(.-8)
    .4byte gFrostBaseLine_Tiles-.,  gFrostBaseLine_TileAttrs-(.-4),  gFrostBaseLine_Chunks-(.-8)
    .4byte gAreaX2_Tiles-.,         gAreaX2_TileAttrs-(.-4),         gAreaX2_Chunks-(.-8)
    .4byte gEnergyFacility_Tiles-., gEnergyFacility_TileAttrs-(.-4), gEnergyFacility_Chunks-(.-8)
    .4byte gSnowyPlains_Tiles-.,    gSnowyPlains_TileAttrs-(.-4),    gSnowyPlains_Chunks-(.-8)
    .4byte gSunkenLibrary_Tiles-.,  gSunkenLibrary_TileAttrs-(.-4),  gSunkenLibrary_Chunks-(.-8)
    .4byte gGiantElevator_Tiles-.,  gGiantElevator_TileAttrs-(.-4),  gGiantElevator_Chunks-(.-8)
    .4byte gSubArcadia_Tiles-.,     gSubArcadia_TileAttrs-(.-4),     gSubArcadia_Chunks-(.-8)
    .4byte gWeilLabo_Tiles-.,       gWeilLabo_TileAttrs-(.-4),       gWeilLabo_Chunks-(.-8)
    .4byte gResistanceBase_Tiles-., gResistanceBase_TileAttrs-(.-4), gResistanceBase_Chunks-(.-8)

StageTerrainsPadding:
    .4byte gTerrainsEnd-.

@ 0x0863c654
gStage0_Terrain:
  gStage0_Tiles: .incbin "data/stage/stage0/metatile.bin"
  gStage0_TileAttrs: .incbin "data/stage/stage0/metatile_attr.bin"
  gStage0_Chunks: .incbin "data/stage/stage0/screen.bin"

@ 0x0863c7a8
gSpaceCraft_Terrain:
  gSpaceCraft_Tiles: .incbin "data/stage/spacecraft/metatile.bin"
  gSpaceCraft_TileAttrs: .incbin "data/stage/spacecraft/metatile_attr.bin"
  gSpaceCraft_Chunks: .incbin "data/stage/spacecraft/screen.bin"

@ 0x08644cb4
gVolcano_Terrain:
  gVolcano_Tiles:     .incbin "data/stage/volcano/metatile.bin"
  gVolcano_TileAttrs: .incbin "data/stage/volcano/metatile_attr.bin"
  gVolcano_Chunks:    .incbin "data/stage/volcano/screen.bin"

@ 0x08653e30
gOcean_Terrain:
  gOcean_Tiles:     .incbin "data/stage/ocean/metatile.bin"
  gOcean_TileAttrs: .incbin "data/stage/ocean/metatile_attr.bin"
  gOcean_Chunks:    .incbin "data/stage/ocean/screen.bin"

@ 0x08662534
gRepairFactory_Terrain:
  gRepairFactory_Tiles:     .incbin "data/stage/repair_factory/metatile.bin"
  gRepairFactory_TileAttrs: .incbin "data/stage/repair_factory/metatile_attr.bin"
  gRepairFactory_Chunks:    .incbin "data/stage/repair_factory/screen.bin"

@ 0x0866f0cc
gOldResidential_Terrain:
  gOldResidential_Tiles:     .incbin "data/stage/old_residential/metatile.bin"
  gOldResidential_TileAttrs: .incbin "data/stage/old_residential/metatile_attr.bin"
  gOldResidential_Chunks:    .incbin "data/stage/old_residential/screen.bin"

@ 0x086807c8
gMissileFactory_Terrain:
  gMissileFactory_Tiles:     .incbin "data/stage/missile_factory/metatile.bin"
  gMissileFactory_TileAttrs: .incbin "data/stage/missile_factory/metatile_attr.bin"
  gMissileFactory_Chunks:    .incbin "data/stage/missile_factory/screen.bin"

@ 0x08690ec0
gTwilightDesert_Terrain:
  gTwilightDesert_Tiles:     .incbin "data/stage/twilight_desert/metatile.bin"
  gTwilightDesert_TileAttrs: .incbin "data/stage/twilight_desert/metatile_attr.bin"
  gTwilightDesert_Chunks:    .incbin "data/stage/twilight_desert/screen.bin"

@ 0x08698d8c
gAnatreForest_Terrain:
  gAnatreForest_Tiles:     .incbin "data/stage/anatre_forest/metatile.bin"
  gAnatreForest_TileAttrs: .incbin "data/stage/anatre_forest/metatile_attr.bin"
  gAnatreForest_Chunks:    .incbin "data/stage/anatre_forest/screen.bin"

@ 0x086a323c
gFrostBaseLine_Terrain:
  gFrostBaseLine_Tiles:     .incbin "data/stage/frostline_ice_base/metatile.bin"
  gFrostBaseLine_TileAttrs: .incbin "data/stage/frostline_ice_base/metatile_attr.bin"
  gFrostBaseLine_Chunks:    .incbin "data/stage/frostline_ice_base/screen.bin"

@ 0x086ae90c
gAreaX2_Terrain:
  gAreaX2_Tiles:     .incbin "data/stage/area_x2/metatile.bin"
  gAreaX2_TileAttrs: .incbin "data/stage/area_x2/metatile_attr.bin"
  gAreaX2_Chunks:    .incbin "data/stage/area_x2/screen.bin"

@ 0x086b6ff8
gEnergyFacility_Terrain:
  gEnergyFacility_Tiles:     .incbin "data/stage/energy_facility/metatile.bin"
  gEnergyFacility_TileAttrs: .incbin "data/stage/energy_facility/metatile_attr.bin"
  gEnergyFacility_Chunks:    .incbin "data/stage/energy_facility/screen.bin"

@ 0x086c3e60
gSnowyPlains_Terrain:
  gSnowyPlains_Tiles:     .incbin "data/stage/snowy_plains/metatile.bin"
  gSnowyPlains_TileAttrs: .incbin "data/stage/snowy_plains/metatile_attr.bin"
  gSnowyPlains_Chunks:    .incbin "data/stage/snowy_plains/screen.bin"

@ 0x086d2910
gSunkenLibrary_Terrain:
  gSunkenLibrary_Tiles:     .incbin "data/stage/sunken_library/metatile.bin"
  gSunkenLibrary_TileAttrs: .incbin "data/stage/sunken_library/metatile_attr.bin"
  gSunkenLibrary_Chunks:    .incbin "data/stage/sunken_library/screen.bin"

@ 0x086db010
gGiantElevator_Terrain:
  gGiantElevator_Tiles:     .incbin "data/stage/giant_elevator/metatile.bin"
  gGiantElevator_TileAttrs: .incbin "data/stage/giant_elevator/metatile_attr.bin"
  gGiantElevator_Chunks:    .incbin "data/stage/giant_elevator/screen.bin"

@ 0x086e2a2c
gSubArcadia_Terrain:
  gSubArcadia_Tiles:     .incbin "data/stage/sub_arcadia/metatile.bin"
  gSubArcadia_TileAttrs: .incbin "data/stage/sub_arcadia/metatile_attr.bin"
  gSubArcadia_Chunks:    .incbin "data/stage/sub_arcadia/screen.bin"

@ 0x086ee6b0
gWeilLabo_Terrain:
  gWeilLabo_Tiles:     .incbin "data/stage/weil_labo/metatile.bin"
  gWeilLabo_TileAttrs: .incbin "data/stage/weil_labo/metatile_attr.bin"
  gWeilLabo_Chunks:    .incbin "data/stage/weil_labo/screen.bin"

@ 0x086f9fec
gResistanceBase_Terrain:
  gResistanceBase_Tiles:     .incbin "data/stage/resistance_base/metatile.bin"
  gResistanceBase_TileAttrs: .incbin "data/stage/resistance_base/metatile_attr.bin"
  gResistanceBase_Chunks:    .incbin "data/stage/resistance_base/screen.bin"

gTerrainsEnd: @ 0x08704438
