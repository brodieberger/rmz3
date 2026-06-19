.balign 4, 0

.global gGraphicHeader_Sprite_ciel
gGraphicHeader_Sprite_ciel:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_ciel_0-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_ciel_1-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_ciel_2-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_ciel_3-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_ciel_4-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_ciel_5-. @ src
	.4byte 608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_ciel_6-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_ciel_7-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_ciel_8-. @ src
	.4byte 704 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_ciel_9-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_ciel_10-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_ciel_11-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_ciel_12-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_ciel_13-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_ciel_14-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_ciel_15-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_ciel_16-. @ src
	.4byte 448 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_ciel_17-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_ciel_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_ciel_0:
	.incbin "sprites/dynamic/ciel/sheet/0.4bpp"
	gGraphicHeader_Sprite_ciel_0_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/0.gbapal"

gGraphicHeader_Sprite_ciel_1:
	.incbin "sprites/dynamic/ciel/sheet/1.4bpp"
	gGraphicHeader_Sprite_ciel_1_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/1.gbapal"

gGraphicHeader_Sprite_ciel_2:
	.incbin "sprites/dynamic/ciel/sheet/2.4bpp"
	gGraphicHeader_Sprite_ciel_2_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/2.gbapal"

gGraphicHeader_Sprite_ciel_3:
	.incbin "sprites/dynamic/ciel/sheet/3.4bpp"
	gGraphicHeader_Sprite_ciel_3_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/3.gbapal"

gGraphicHeader_Sprite_ciel_4:
	.incbin "sprites/dynamic/ciel/sheet/4.4bpp"
	gGraphicHeader_Sprite_ciel_4_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/4.gbapal"

gGraphicHeader_Sprite_ciel_5:
	.incbin "sprites/dynamic/ciel/sheet/5.4bpp"
	gGraphicHeader_Sprite_ciel_5_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/5.gbapal"

gGraphicHeader_Sprite_ciel_6:
	.incbin "sprites/dynamic/ciel/sheet/6.4bpp"
	gGraphicHeader_Sprite_ciel_6_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/6.gbapal"

gGraphicHeader_Sprite_ciel_7:
	.incbin "sprites/dynamic/ciel/sheet/7.4bpp"
	gGraphicHeader_Sprite_ciel_7_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/7.gbapal"

gGraphicHeader_Sprite_ciel_8:
	.incbin "sprites/dynamic/ciel/sheet/8.4bpp"
	gGraphicHeader_Sprite_ciel_8_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/8.gbapal"

gGraphicHeader_Sprite_ciel_9:
	.incbin "sprites/dynamic/ciel/sheet/9.4bpp"
	gGraphicHeader_Sprite_ciel_9_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/9.gbapal"

gGraphicHeader_Sprite_ciel_10:
	.incbin "sprites/dynamic/ciel/sheet/10.4bpp"
	gGraphicHeader_Sprite_ciel_10_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/10.gbapal"

gGraphicHeader_Sprite_ciel_11:
	.incbin "sprites/dynamic/ciel/sheet/11.4bpp"
	gGraphicHeader_Sprite_ciel_11_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/11.gbapal"

gGraphicHeader_Sprite_ciel_12:
	.incbin "sprites/dynamic/ciel/sheet/12.4bpp"
	gGraphicHeader_Sprite_ciel_12_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/12.gbapal"

gGraphicHeader_Sprite_ciel_13:
	.incbin "sprites/dynamic/ciel/sheet/13.4bpp"
	gGraphicHeader_Sprite_ciel_13_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/13.gbapal"

gGraphicHeader_Sprite_ciel_14:
	.incbin "sprites/dynamic/ciel/sheet/14.4bpp"
	gGraphicHeader_Sprite_ciel_14_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/14.gbapal"

gGraphicHeader_Sprite_ciel_15:
	.incbin "sprites/dynamic/ciel/sheet/15.4bpp"
	gGraphicHeader_Sprite_ciel_15_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/15.gbapal"

gGraphicHeader_Sprite_ciel_16:
	.incbin "sprites/dynamic/ciel/sheet/16.4bpp"
	gGraphicHeader_Sprite_ciel_16_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/16.gbapal"

gGraphicHeader_Sprite_ciel_17:
	.incbin "sprites/dynamic/ciel/sheet/17.4bpp"
	gGraphicHeader_Sprite_ciel_17_Palettes:
	.incbin "sprites/dynamic/ciel/sheet/17.gbapal"
