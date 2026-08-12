.section .rodata
.balign 4, 0

@ US fills the gap between the static graphic table and the cyber-elf table
@ with 0xb4 bytes of data; JP just pads it. Sixth block of this kind.
.if REGION_US
.global gUsSpriteStaticTail
gUsSpriteStaticTail:
  .incbin "sprites/static/us_sprite_static_tail.bin"
.endif
