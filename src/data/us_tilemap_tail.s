.section .rodata
.balign 4, 0

@ US carries 0x40 bytes here
.if REGION_US
.global gUsTilemapTail
gUsTilemapTail:
  .incbin "src/data/us_tilemap_tail.bin"
.endif
