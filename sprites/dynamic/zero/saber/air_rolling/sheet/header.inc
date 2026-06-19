.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_air_rolling
gGraphicHeader_Sprite_zero_saber_air_rolling:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_0-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_1-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_2-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_3-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_4-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_air_rolling_5-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_air_rolling_0:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_0_Palettes:

gGraphicHeader_Sprite_zero_saber_air_rolling_1:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_1_Palettes:

gGraphicHeader_Sprite_zero_saber_air_rolling_2:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_2_Palettes:

gGraphicHeader_Sprite_zero_saber_air_rolling_3:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_3_Palettes:

gGraphicHeader_Sprite_zero_saber_air_rolling_4:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_4_Palettes:

gGraphicHeader_Sprite_zero_saber_air_rolling_5:
	.incbin "sprites/dynamic/zero/saber/air_rolling/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_rolling_5_Palettes:
