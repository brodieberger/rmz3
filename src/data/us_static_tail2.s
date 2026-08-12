.section .rodata
.balign 4, 0

@ 0x18 bytes US keeps between the static sprite animations and the static
@ graphic table. Fifth block of this kind; unreferenced, absent from the JP ROM.
.if REGION_US
.global gUsStaticTail2
gUsStaticTail2:
  .incbin "src/data/us_static_tail2.bin"
.endif
