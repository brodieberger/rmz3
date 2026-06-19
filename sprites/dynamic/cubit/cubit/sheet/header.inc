.balign 4, 0

.global gGraphicHeader_Sprite_cubit_cubit
gGraphicHeader_Sprite_cubit_cubit:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cubit_cubit_0-. @ src
	.4byte 3040 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cubit_cubit_1-. @ src
	.4byte 3136 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 784, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cubit_cubit_2-. @ src
	.4byte 2848 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 712, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_cubit_cubit_3-. @ src
	.4byte 2912 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 728, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_cubit_cubit_4-. @ src
	.4byte 2368 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 592, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_cubit_cubit_5-. @ src
	.4byte 3264 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 816, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_cubit_cubit_6-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_cubit_cubit_7-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_cubit_cubit_8-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_cubit_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cubit_cubit_0:
	.incbin "sprites/dynamic/cubit/cubit/sheet/0.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_0_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/0.gbapal"

gGraphicHeader_Sprite_cubit_cubit_1:
	.incbin "sprites/dynamic/cubit/cubit/sheet/1.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_1_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/1.gbapal"

gGraphicHeader_Sprite_cubit_cubit_2:
	.incbin "sprites/dynamic/cubit/cubit/sheet/2.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_2_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/2.gbapal"

gGraphicHeader_Sprite_cubit_cubit_3:
	.incbin "sprites/dynamic/cubit/cubit/sheet/3.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_3_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/3.gbapal"

gGraphicHeader_Sprite_cubit_cubit_4:
	.incbin "sprites/dynamic/cubit/cubit/sheet/4.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_4_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/4.gbapal"

gGraphicHeader_Sprite_cubit_cubit_5:
	.incbin "sprites/dynamic/cubit/cubit/sheet/5.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_5_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/5.gbapal"

gGraphicHeader_Sprite_cubit_cubit_6:
	.incbin "sprites/dynamic/cubit/cubit/sheet/6.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_6_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/6.gbapal"

gGraphicHeader_Sprite_cubit_cubit_7:
	.incbin "sprites/dynamic/cubit/cubit/sheet/7.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_7_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/7.gbapal"

gGraphicHeader_Sprite_cubit_cubit_8:
	.incbin "sprites/dynamic/cubit/cubit/sheet/8.4bpp"
	gGraphicHeader_Sprite_cubit_cubit_8_Palettes:
	.incbin "sprites/dynamic/cubit/cubit/sheet/8.gbapal"
