.section .rodata
.balign 4, 0

.global gGraphicHeader_Sprite_zero_idle
gGraphicHeader_Sprite_zero_idle:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_idle_0-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_idle_1-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_idle_2-. @ src
	.4byte 992 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_idle_3-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_idle_0:
	.incbin "sprites/dynamic/zero/idle/sheet/0.4bpp"

gGraphicHeader_Sprite_zero_idle_1:
	.incbin "sprites/dynamic/zero/idle/sheet/1.4bpp"

gGraphicHeader_Sprite_zero_idle_2:
	.incbin "sprites/dynamic/zero/idle/sheet/2.4bpp"

gGraphicHeader_Sprite_zero_idle_3:
	.incbin "sprites/dynamic/zero/idle/sheet/3.4bpp"
