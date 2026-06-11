.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_split_heaven
gGraphicHeader_Sprite_zero_saber_split_heaven:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_split_heaven_0-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_split_heaven_1-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_split_heaven_2-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_split_heaven_3-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_split_heaven_0:
	.incbin "sprites/dynamic/zero/saber/split_heaven/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_split_heaven_0_Palettes:

gGraphicHeader_Sprite_zero_saber_split_heaven_1:
	.incbin "sprites/dynamic/zero/saber/split_heaven/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_split_heaven_1_Palettes:

gGraphicHeader_Sprite_zero_saber_split_heaven_2:
	.incbin "sprites/dynamic/zero/saber/split_heaven/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_split_heaven_2_Palettes:

gGraphicHeader_Sprite_zero_saber_split_heaven_3:
	.incbin "sprites/dynamic/zero/saber/split_heaven/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_split_heaven_3_Palettes:
