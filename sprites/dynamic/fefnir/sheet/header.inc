.balign 4, 0

.global gGraphicHeader_Sprite_fefnir
gGraphicHeader_Sprite_fefnir:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_fefnir_0-. @ src
	.4byte 1952 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 488, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_fefnir_1-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_fefnir_2-. @ src
	.4byte 3680 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 920, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_fefnir_3-. @ src
	.4byte 3968 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_fefnir_4-. @ src
	.4byte 4032 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1008, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_fefnir_5-. @ src
	.4byte 2880 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 720, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_fefnir_6-. @ src
	.4byte 2848 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 712, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_fefnir_7-. @ src
	.4byte 3328 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_fefnir_8-. @ src
	.4byte 2464 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 616, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_fefnir_9-. @ src
	.4byte 4032 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1008, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_fefnir_10-. @ src
	.4byte 3648 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_fefnir_11-. @ src
	.4byte 3616 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 904, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_fefnir_12-. @ src
	.4byte 2560 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 640, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_fefnir_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_fefnir_0:
	.incbin "sprites/dynamic/fefnir/sheet/0.4bpp"
	gGraphicHeader_Sprite_fefnir_0_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/0.gbapal"

gGraphicHeader_Sprite_fefnir_1:
	.incbin "sprites/dynamic/fefnir/sheet/1.4bpp"
	gGraphicHeader_Sprite_fefnir_1_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/1.gbapal"

gGraphicHeader_Sprite_fefnir_2:
	.incbin "sprites/dynamic/fefnir/sheet/2.4bpp"
	gGraphicHeader_Sprite_fefnir_2_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/2.gbapal"

gGraphicHeader_Sprite_fefnir_3:
	.incbin "sprites/dynamic/fefnir/sheet/3.4bpp"
	gGraphicHeader_Sprite_fefnir_3_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/3.gbapal"

gGraphicHeader_Sprite_fefnir_4:
	.incbin "sprites/dynamic/fefnir/sheet/4.4bpp"
	gGraphicHeader_Sprite_fefnir_4_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/4.gbapal"

gGraphicHeader_Sprite_fefnir_5:
	.incbin "sprites/dynamic/fefnir/sheet/5.4bpp"
	gGraphicHeader_Sprite_fefnir_5_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/5.gbapal"

gGraphicHeader_Sprite_fefnir_6:
	.incbin "sprites/dynamic/fefnir/sheet/6.4bpp"
	gGraphicHeader_Sprite_fefnir_6_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/6.gbapal"

gGraphicHeader_Sprite_fefnir_7:
	.incbin "sprites/dynamic/fefnir/sheet/7.4bpp"
	gGraphicHeader_Sprite_fefnir_7_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/7.gbapal"

gGraphicHeader_Sprite_fefnir_8:
	.incbin "sprites/dynamic/fefnir/sheet/8.4bpp"
	gGraphicHeader_Sprite_fefnir_8_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/8.gbapal"

gGraphicHeader_Sprite_fefnir_9:
	.incbin "sprites/dynamic/fefnir/sheet/9.4bpp"
	gGraphicHeader_Sprite_fefnir_9_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/9.gbapal"

gGraphicHeader_Sprite_fefnir_10:
	.incbin "sprites/dynamic/fefnir/sheet/10.4bpp"
	gGraphicHeader_Sprite_fefnir_10_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/10.gbapal"

gGraphicHeader_Sprite_fefnir_11:
	.incbin "sprites/dynamic/fefnir/sheet/11.4bpp"
	gGraphicHeader_Sprite_fefnir_11_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/11.gbapal"

gGraphicHeader_Sprite_fefnir_12:
	.incbin "sprites/dynamic/fefnir/sheet/12.4bpp"
	gGraphicHeader_Sprite_fefnir_12_Palettes:
	.incbin "sprites/dynamic/fefnir/sheet/12.gbapal"
