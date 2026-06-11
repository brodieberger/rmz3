.balign 4, 0

.global gGraphicHeader_Sprite_zero_air
gGraphicHeader_Sprite_zero_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_air_0-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_air_1-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_air_2-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_air_3-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_air_4-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_air_5-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_air_6-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_air_7-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_air_8-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_zero_air_9-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_air_0:
	.incbin "sprites/dynamic/zero/air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_air_0_Palettes:

gGraphicHeader_Sprite_zero_air_1:
	.incbin "sprites/dynamic/zero/air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_air_1_Palettes:

gGraphicHeader_Sprite_zero_air_2:
	.incbin "sprites/dynamic/zero/air/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_air_2_Palettes:

gGraphicHeader_Sprite_zero_air_3:
	.incbin "sprites/dynamic/zero/air/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_air_3_Palettes:

gGraphicHeader_Sprite_zero_air_4:
	.incbin "sprites/dynamic/zero/air/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_air_4_Palettes:

gGraphicHeader_Sprite_zero_air_5:
	.incbin "sprites/dynamic/zero/air/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_air_5_Palettes:

gGraphicHeader_Sprite_zero_air_6:
	.incbin "sprites/dynamic/zero/air/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_air_6_Palettes:

gGraphicHeader_Sprite_zero_air_7:
	.incbin "sprites/dynamic/zero/air/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_air_7_Palettes:

gGraphicHeader_Sprite_zero_air_8:
	.incbin "sprites/dynamic/zero/air/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_air_8_Palettes:

gGraphicHeader_Sprite_zero_air_9:
	.incbin "sprites/dynamic/zero/air/sheet/9.4bpp"
	gGraphicHeader_Sprite_zero_air_9_Palettes:
