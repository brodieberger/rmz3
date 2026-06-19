.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_ladder
gGraphicHeader_Sprite_zero_rod_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_ladder_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_ladder_1-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_ladder_2-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_ladder_0:
	.incbin "sprites/dynamic/zero/rod/ladder/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_ladder_0_Palettes:

gGraphicHeader_Sprite_zero_rod_ladder_1:
	.incbin "sprites/dynamic/zero/rod/ladder/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_ladder_1_Palettes:

gGraphicHeader_Sprite_zero_rod_ladder_2:
	.incbin "sprites/dynamic/zero/rod/ladder/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_ladder_2_Palettes:
