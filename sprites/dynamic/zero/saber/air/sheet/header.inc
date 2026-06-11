.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_air
gGraphicHeader_Sprite_zero_saber_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_air_0-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_air_1-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_air_2-. @ src
	.4byte 992 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_air_3-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_air_4-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_air_0:
	.incbin "sprites/dynamic/zero/saber/air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_0_Palettes:

gGraphicHeader_Sprite_zero_saber_air_1:
	.incbin "sprites/dynamic/zero/saber/air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_1_Palettes:

gGraphicHeader_Sprite_zero_saber_air_2:
	.incbin "sprites/dynamic/zero/saber/air/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_2_Palettes:

gGraphicHeader_Sprite_zero_saber_air_3:
	.incbin "sprites/dynamic/zero/saber/air/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_3_Palettes:

gGraphicHeader_Sprite_zero_saber_air_4:
	.incbin "sprites/dynamic/zero/saber/air/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_air_4_Palettes:
