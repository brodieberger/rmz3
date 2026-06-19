.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_ladder
gGraphicHeader_Sprite_zero_shield_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_ladder_0-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_ladder_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_ladder_2-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_ladder_0:
	.incbin "sprites/dynamic/zero/shield/ladder/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_ladder_0_Palettes:

gGraphicHeader_Sprite_zero_shield_ladder_1:
	.incbin "sprites/dynamic/zero/shield/ladder/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_ladder_1_Palettes:

gGraphicHeader_Sprite_zero_shield_ladder_2:
	.incbin "sprites/dynamic/zero/shield/ladder/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_ladder_2_Palettes:
