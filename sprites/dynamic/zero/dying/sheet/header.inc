.section .rodata
.balign 4, 0

.global gGraphicHeader_Sprite_zero_dying
gGraphicHeader_Sprite_zero_dying:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_dying_0-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_dying_1-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_dying_0:
	.incbin "sprites/dynamic/zero/dying/sheet/0.4bpp"

gGraphicHeader_Sprite_zero_dying_1:
	.incbin "sprites/dynamic/zero/dying/sheet/1.4bpp"
