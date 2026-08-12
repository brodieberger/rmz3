.section .rodata
.balign 4, 0

@ US leaves 0x14800 bytes of an earlier build image in the gap the JP linker
@ simply pads. It is not referenced by anything — the tail of it is a verbatim
@ copy of JP graphics data at a constant offset — but it is in the ROM, so it
@ has to be reproduced. JP keeps the plain FILL(0xFF) padding instead.
.if REGION_US
.global gUsGapImage
gUsGapImage:
  .incbin "src/data/us_gap.bin"
.endif
