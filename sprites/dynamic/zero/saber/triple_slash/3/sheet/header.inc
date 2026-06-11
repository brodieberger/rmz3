.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_triple_slash_3
gGraphicHeader_Sprite_zero_saber_triple_slash_3:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_0-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_1-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_2-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_3-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_4-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_5-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_6-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_7-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_8-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_zero_saber_triple_slash_3_9-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_triple_slash_3_0:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_0_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_1:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_1_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_2:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_2_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_3:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_3_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_4:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_4_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_5:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_5_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_6:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_6_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_7:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_7_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_8:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_8_Palettes:

gGraphicHeader_Sprite_zero_saber_triple_slash_3_9:
	.incbin "sprites/dynamic/zero/saber/triple_slash/3/sheet/9.4bpp"
	gGraphicHeader_Sprite_zero_saber_triple_slash_3_9_Palettes:
