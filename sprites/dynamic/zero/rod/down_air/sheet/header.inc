.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_down_air
gGraphicHeader_Sprite_zero_rod_down_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_down_air_0-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_down_air_1-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_down_air_0:
	.incbin "sprites/dynamic/zero/rod/down_air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_air_0_Palettes:

gGraphicHeader_Sprite_zero_rod_down_air_1:
	.incbin "sprites/dynamic/zero/rod/down_air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_air_1_Palettes:
