  .include "asm/macros.inc"

.section .rodata
.balign 4, 0

# 現在のアドレスから gXXXTilesetGraphics までのオフセットを格納している . は現在のアドレス
.global gStageTilesetOffsets
gStageTilesetOffsets:
  .word gSnowTilesetGraphics-.
  .word gSnowTilesetGraphics-.
  .word gVolcanoTilesetGraphics-.
  .word gWatersideTilesetGraphics-.
  .word gFactoryTilesetGraphics-.
  .word gRuinTilesetGraphics-.
  .word gMissileTilesetGraphics-.
  .word gDesertTilesetGraphics-.
  .word gForestTilesetGraphics-.
  .word gAntarcticTilesetGraphics-.
  .word gAreaX2TilesetGraphics-.
  .word gPlantTilesetGraphics-.
  .word gSnowTilesetGraphics-.
  .word gWatersideTilesetGraphics-.
  .word gElevatorTilesetGraphics-.
  .word gSubArcadiaTilesetGraphics-.
  .word gWeilLaboTilesetGraphics-.
  .word gResistanceBaseTilesetGraphics-.
  .word gMiscTilesetGraphics-.

.include "data/tilesets/snow/header.inc"
.include "data/tilesets/volcano/header.inc"
.include "data/tilesets/waterside/header.inc"
.include "data/tilesets/factory/header.inc"
.include "data/tilesets/ruin/header.inc"
.include "data/tilesets/missile/header.inc"
.include "data/tilesets/desert/header.inc"
.include "data/tilesets/forest/header.inc"
.include "data/tilesets/antarctic/header.inc"
.include "data/tilesets/area_x2/header.inc"
.include "data/tilesets/plant/header.inc"
.include "data/tilesets/giant_elevator/header.inc"
.include "data/tilesets/sub_arcadia/header.inc"
.include "data/tilesets/weil_labo/header.inc"
.include "data/tilesets/resistance_base/header.inc"
.include "data/tilesets/misc/header.inc"
