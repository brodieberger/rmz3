.section .rodata
.balign 4, 0

@ US carries 0x40 bytes here that JP does not, between the BG tilemaps and
@ gBgGraphics. Nothing references it and it appears in neither the JP ROM nor
@ anywhere else in the US one, so it reads as leftover — but it sets where
@ gBgGraphics starts, so it has to be reproduced.
.if REGION_US
.global gUsTilemapTail
gUsTilemapTail:
  .incbin "src/data/us_tilemap_tail.bin"
.endif
