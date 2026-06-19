.balign 4, 0

.global gGraphicHeader_Sprite_weil
gGraphicHeader_Sprite_weil:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weil_0-. @ src
	.4byte 1984 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 496, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_weil_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weil_1-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_weil_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weil_2-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_weil_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weil_3-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_weil_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weil_0:
	.incbin "sprites/dynamic/weil/sheet/0.4bpp"
	gGraphicHeader_Sprite_weil_0_Palettes:
	.incbin "sprites/dynamic/weil/sheet/0.gbapal"

gGraphicHeader_Sprite_weil_1:
	.incbin "sprites/dynamic/weil/sheet/1.4bpp"
	gGraphicHeader_Sprite_weil_1_Palettes:
	.incbin "sprites/dynamic/weil/sheet/1.gbapal"

gGraphicHeader_Sprite_weil_2:
	.incbin "sprites/dynamic/weil/sheet/2.4bpp"
	gGraphicHeader_Sprite_weil_2_Palettes:
	.incbin "sprites/dynamic/weil/sheet/2.gbapal"

gGraphicHeader_Sprite_weil_3:
	.incbin "sprites/dynamic/weil/sheet/3.4bpp"
	gGraphicHeader_Sprite_weil_3_Palettes:
	.incbin "sprites/dynamic/weil/sheet/3.gbapal"
