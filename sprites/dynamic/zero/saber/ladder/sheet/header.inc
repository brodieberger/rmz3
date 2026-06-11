.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_ladder
gGraphicHeader_Sprite_zero_saber_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_0-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_1-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_2-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_3-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_4-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_ladder_5-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_ladder_0:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_0_Palettes:

gGraphicHeader_Sprite_zero_saber_ladder_1:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_1_Palettes:

gGraphicHeader_Sprite_zero_saber_ladder_2:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_2_Palettes:

gGraphicHeader_Sprite_zero_saber_ladder_3:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_3_Palettes:

gGraphicHeader_Sprite_zero_saber_ladder_4:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_4_Palettes:

gGraphicHeader_Sprite_zero_saber_ladder_5:
	.incbin "sprites/dynamic/zero/saber/ladder/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_ladder_5_Palettes:
