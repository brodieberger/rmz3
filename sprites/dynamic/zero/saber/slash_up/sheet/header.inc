.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_slash_up
gGraphicHeader_Sprite_zero_saber_slash_up:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_slash_up_0-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_slash_up_1-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_slash_up_2-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_slash_up_3-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_slash_up_0:
	.incbin "sprites/dynamic/zero/saber/slash_up/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_slash_up_0_Palettes:

gGraphicHeader_Sprite_zero_saber_slash_up_1:
	.incbin "sprites/dynamic/zero/saber/slash_up/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_slash_up_1_Palettes:

gGraphicHeader_Sprite_zero_saber_slash_up_2:
	.incbin "sprites/dynamic/zero/saber/slash_up/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_slash_up_2_Palettes:

gGraphicHeader_Sprite_zero_saber_slash_up_3:
	.incbin "sprites/dynamic/zero/saber/slash_up/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_slash_up_3_Palettes:
