.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_triple_slash_1
gGraphicHeader_Sprite_zero_saber_triple_slash_1:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_1-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_2-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_3-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_4-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_5-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_6-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_1_7-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_triple_slash_1_0:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_0_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_1:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_1_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_2:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_2_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_3:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_3_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_4:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_4_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_5:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_5_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_6:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_6_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_1_7:
	.incbin "sprites/dynamic/zero/saber/triple_slash/1/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_1_7_Palettes:
