.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_gale
gGraphicHeader_Sprite_zero_saber_gale:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_gale_0-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_gale_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_gale_2-. @ src
	.4byte 544 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_gale_0:
	.incbin "sprites/dynamic/zero/saber/gale/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_gale_0_Palettes:

gGraphicHeader_Sprite_zero_saber_gale_1:
	.incbin "sprites/dynamic/zero/saber/gale/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_gale_1_Palettes:

gGraphicHeader_Sprite_zero_saber_gale_2:
	.incbin "sprites/dynamic/zero/saber/gale/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_gale_2_Palettes:
