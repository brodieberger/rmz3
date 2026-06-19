.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_up
gGraphicHeader_Sprite_zero_rod_up:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_up_0-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_up_1-. @ src
	.4byte 1376 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_up_2-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_up_3-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_up_4-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_rod_up_5-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_up_0:
	.incbin "sprites/dynamic/zero/rod/up/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_0_Palettes:

gGraphicHeader_Sprite_zero_rod_up_1:
	.incbin "sprites/dynamic/zero/rod/up/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_1_Palettes:

gGraphicHeader_Sprite_zero_rod_up_2:
	.incbin "sprites/dynamic/zero/rod/up/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_2_Palettes:

gGraphicHeader_Sprite_zero_rod_up_3:
	.incbin "sprites/dynamic/zero/rod/up/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_3_Palettes:

gGraphicHeader_Sprite_zero_rod_up_4:
	.incbin "sprites/dynamic/zero/rod/up/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_4_Palettes:

gGraphicHeader_Sprite_zero_rod_up_5:
	.incbin "sprites/dynamic/zero/rod/up/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_rod_up_5_Palettes:
