.section .rodata
.balign 4, 0

@ US leaves 0x14800 bytes
.if REGION_US
.global gUsGapImage
gUsGapImage:
  .incbin "src/data/us_gap.bin"
.endif
