.section .rodata
.balign 4, 0

@ US fills the 120-byte gap after the terrain data; JP just pads it.
.if REGION_US
.global gUsTerrainTail
gUsTerrainTail:
  .incbin "src/data/us_terrain_tail.bin"
.endif
