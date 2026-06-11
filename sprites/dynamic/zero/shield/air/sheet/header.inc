.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_air
gGraphicHeader_Sprite_zero_shield_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_air_0-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_air_1-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_air_2-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_air_0:
	.incbin "sprites/dynamic/zero/shield/air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_air_0_Palettes:

gGraphicHeader_Sprite_zero_shield_air_1:
	.incbin "sprites/dynamic/zero/shield/air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_air_1_Palettes:

gGraphicHeader_Sprite_zero_shield_air_2:
	.incbin "sprites/dynamic/zero/shield/air/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_air_2_Palettes:
