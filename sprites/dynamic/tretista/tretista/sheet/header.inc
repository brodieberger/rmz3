.balign 4, 0

.global gGraphicHeader_Sprite_tretista_tretista
gGraphicHeader_Sprite_tretista_tretista:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_tretista_tretista_0-. @ src
	.4byte 8160 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 2040, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_tretista_tretista_1-. @ src
	.4byte 5184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_tretista_tretista_2-. @ src
	.4byte 7264 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1816, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_tretista_tretista_3-. @ src
	.4byte 6944 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1736, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_tretista_tretista_4-. @ src
	.4byte 7072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_tretista_tretista_5-. @ src
	.4byte 7584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_tretista_tretista_6-. @ src
	.4byte 7680 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1920, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_tretista_tretista_7-. @ src
	.4byte 7552 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1888, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_tretista_tretista_8-. @ src
	.4byte 8160 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 2040, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_tretista_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_tretista_tretista_0:
	.incbin "sprites/dynamic/tretista/tretista/sheet/0.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_0_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/0.gbapal"

gGraphicHeader_Sprite_tretista_tretista_1:
	.incbin "sprites/dynamic/tretista/tretista/sheet/1.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_1_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/1.gbapal"

gGraphicHeader_Sprite_tretista_tretista_2:
	.incbin "sprites/dynamic/tretista/tretista/sheet/2.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_2_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/2.gbapal"

gGraphicHeader_Sprite_tretista_tretista_3:
	.incbin "sprites/dynamic/tretista/tretista/sheet/3.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_3_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/3.gbapal"

gGraphicHeader_Sprite_tretista_tretista_4:
	.incbin "sprites/dynamic/tretista/tretista/sheet/4.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_4_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/4.gbapal"

gGraphicHeader_Sprite_tretista_tretista_5:
	.incbin "sprites/dynamic/tretista/tretista/sheet/5.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_5_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/5.gbapal"

gGraphicHeader_Sprite_tretista_tretista_6:
	.incbin "sprites/dynamic/tretista/tretista/sheet/6.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_6_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/6.gbapal"

gGraphicHeader_Sprite_tretista_tretista_7:
	.incbin "sprites/dynamic/tretista/tretista/sheet/7.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_7_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/7.gbapal"

gGraphicHeader_Sprite_tretista_tretista_8:
	.incbin "sprites/dynamic/tretista/tretista/sheet/8.4bpp"
	gGraphicHeader_Sprite_tretista_tretista_8_Palettes:
	.incbin "sprites/dynamic/tretista/tretista/sheet/8.gbapal"
