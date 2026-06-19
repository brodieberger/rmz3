.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_down
gGraphicHeader_Sprite_zero_rod_down:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_down_0-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_down_1-. @ src
	.4byte 1376 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_down_2-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_down_3-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_down_4-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_rod_down_5-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_down_0:
	.incbin "sprites/dynamic/zero/rod/down/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_0_Palettes:

gGraphicHeader_Sprite_zero_rod_down_1:
	.incbin "sprites/dynamic/zero/rod/down/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_1_Palettes:

gGraphicHeader_Sprite_zero_rod_down_2:
	.incbin "sprites/dynamic/zero/rod/down/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_2_Palettes:

gGraphicHeader_Sprite_zero_rod_down_3:
	.incbin "sprites/dynamic/zero/rod/down/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_3_Palettes:

gGraphicHeader_Sprite_zero_rod_down_4:
	.incbin "sprites/dynamic/zero/rod/down/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_4_Palettes:

gGraphicHeader_Sprite_zero_rod_down_5:
	.incbin "sprites/dynamic/zero/rod/down/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_rod_down_5_Palettes:
