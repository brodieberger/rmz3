.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_dash
gGraphicHeader_Sprite_zero_saber_dash:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_dash_0-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_dash_1-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_dash_2-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_dash_3-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_dash_4-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_dash_0:
	.incbin "sprites/dynamic/zero/saber/dash/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_dash_0_Palettes:

gGraphicHeader_Sprite_zero_saber_dash_1:
	.incbin "sprites/dynamic/zero/saber/dash/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_dash_1_Palettes:

gGraphicHeader_Sprite_zero_saber_dash_2:
	.incbin "sprites/dynamic/zero/saber/dash/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_dash_2_Palettes:

gGraphicHeader_Sprite_zero_saber_dash_3:
	.incbin "sprites/dynamic/zero/saber/dash/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_dash_3_Palettes:

gGraphicHeader_Sprite_zero_saber_dash_4:
	.incbin "sprites/dynamic/zero/saber/dash/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_dash_4_Palettes:
