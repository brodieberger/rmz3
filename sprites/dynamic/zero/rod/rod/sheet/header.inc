.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_rod
gGraphicHeader_Sprite_zero_rod_rod:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_rod_0-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_rod_1-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_rod_2-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_rod_3-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_rod_4-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_rod_rod_5-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_rod_0:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_0_Palettes:

gGraphicHeader_Sprite_zero_rod_rod_1:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_1_Palettes:

gGraphicHeader_Sprite_zero_rod_rod_2:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_2_Palettes:

gGraphicHeader_Sprite_zero_rod_rod_3:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_3_Palettes:

gGraphicHeader_Sprite_zero_rod_rod_4:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_4_Palettes:

gGraphicHeader_Sprite_zero_rod_rod_5:
	.incbin "sprites/dynamic/zero/rod/rod/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_rod_rod_5_Palettes:
