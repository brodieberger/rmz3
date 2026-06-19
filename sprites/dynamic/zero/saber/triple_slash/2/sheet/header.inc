.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_triple_slash_2
gGraphicHeader_Sprite_zero_saber_triple_slash_2:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_0-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_1-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_2-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_3-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_4-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_5-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_2_6-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_triple_slash_2_0:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_0_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_1:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_1_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_2:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_2_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_3:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_3_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_4:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_4_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_5:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_5_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_2_6:
	.incbin "sprites/dynamic/zero/saber/triple_slash/2/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_2_6_Palettes:
