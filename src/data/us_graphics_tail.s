.section .rodata
.balign 4, 0

@ US keeps 0x420 bytes between the BG graphics and the dialog graphic table
@ where JP has nothing. Same species as us_gap and us_tilemap_tail: nothing
@ references it and it is absent from the JP ROM, but it is what puts
@ gDialogGraphics at 0x085a7ec4 in both regions.
.if REGION_US
.global gUsGraphicsTail
gUsGraphicsTail:
  .incbin "src/data/us_graphics_tail.bin"
.endif
