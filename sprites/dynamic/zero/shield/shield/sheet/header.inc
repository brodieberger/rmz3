.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_shield
gGraphicHeader_Sprite_zero_shield_shield:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_shield_0-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_shield_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_shield_2-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_shield_0:
	.incbin "sprites/dynamic/zero/shield/shield/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_shield_0_Palettes:

gGraphicHeader_Sprite_zero_shield_shield_1:
	.incbin "sprites/dynamic/zero/shield/shield/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_shield_1_Palettes:

gGraphicHeader_Sprite_zero_shield_shield_2:
	.incbin "sprites/dynamic/zero/shield/shield/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_shield_2_Palettes:
