.balign 4, 0

.global gGraphicHeader_Sprite_deathtanz
gGraphicHeader_Sprite_deathtanz:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_deathtanz_0-. @ src
	.4byte 4896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_deathtanz_1-. @ src
	.4byte 7584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_deathtanz_2-. @ src
	.4byte 7104 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1776, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_deathtanz_3-. @ src
	.4byte 5600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_deathtanz_4-. @ src
	.4byte 4928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_deathtanz_5-. @ src
	.4byte 3168 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 792, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_deathtanz_6-. @ src
	.4byte 6720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_deathtanz_7-. @ src
	.4byte 2240 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 560, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_deathtanz_8-. @ src
	.4byte 3328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_deathtanz_9-. @ src
	.4byte 6144 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1536, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_deathtanz_10-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_deathtanz_11-. @ src
	.4byte 6336 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1584, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_deathtanz_12-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_deathtanz_13-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_deathtanz_14-. @ src
	.4byte 4768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_deathtanz_15-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_deathtanz_16-. @ src
	.4byte 4256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1064, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_deathtanz_17-. @ src
	.4byte 5344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_deathtanz_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_deathtanz_0:
	.incbin "sprites/dynamic/deathtanz/sheet/0.4bpp"
	gGraphicHeader_Sprite_deathtanz_0_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/0.gbapal"

gGraphicHeader_Sprite_deathtanz_1:
	.incbin "sprites/dynamic/deathtanz/sheet/1.4bpp"
	gGraphicHeader_Sprite_deathtanz_1_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/1.gbapal"

gGraphicHeader_Sprite_deathtanz_2:
	.incbin "sprites/dynamic/deathtanz/sheet/2.4bpp"
	gGraphicHeader_Sprite_deathtanz_2_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/2.gbapal"

gGraphicHeader_Sprite_deathtanz_3:
	.incbin "sprites/dynamic/deathtanz/sheet/3.4bpp"
	gGraphicHeader_Sprite_deathtanz_3_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/3.gbapal"

gGraphicHeader_Sprite_deathtanz_4:
	.incbin "sprites/dynamic/deathtanz/sheet/4.4bpp"
	gGraphicHeader_Sprite_deathtanz_4_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/4.gbapal"

gGraphicHeader_Sprite_deathtanz_5:
	.incbin "sprites/dynamic/deathtanz/sheet/5.4bpp"
	gGraphicHeader_Sprite_deathtanz_5_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/5.gbapal"

gGraphicHeader_Sprite_deathtanz_6:
	.incbin "sprites/dynamic/deathtanz/sheet/6.4bpp"
	gGraphicHeader_Sprite_deathtanz_6_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/6.gbapal"

gGraphicHeader_Sprite_deathtanz_7:
	.incbin "sprites/dynamic/deathtanz/sheet/7.4bpp"
	gGraphicHeader_Sprite_deathtanz_7_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/7.gbapal"

gGraphicHeader_Sprite_deathtanz_8:
	.incbin "sprites/dynamic/deathtanz/sheet/8.4bpp"
	gGraphicHeader_Sprite_deathtanz_8_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/8.gbapal"

gGraphicHeader_Sprite_deathtanz_9:
	.incbin "sprites/dynamic/deathtanz/sheet/9.4bpp"
	gGraphicHeader_Sprite_deathtanz_9_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/9.gbapal"

gGraphicHeader_Sprite_deathtanz_10:
	.incbin "sprites/dynamic/deathtanz/sheet/10.4bpp"
	gGraphicHeader_Sprite_deathtanz_10_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/10.gbapal"

gGraphicHeader_Sprite_deathtanz_11:
	.incbin "sprites/dynamic/deathtanz/sheet/11.4bpp"
	gGraphicHeader_Sprite_deathtanz_11_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/11.gbapal"

gGraphicHeader_Sprite_deathtanz_12:
	.incbin "sprites/dynamic/deathtanz/sheet/12.4bpp"
	gGraphicHeader_Sprite_deathtanz_12_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/12.gbapal"

gGraphicHeader_Sprite_deathtanz_13:
	.incbin "sprites/dynamic/deathtanz/sheet/13.4bpp"
	gGraphicHeader_Sprite_deathtanz_13_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/13.gbapal"

gGraphicHeader_Sprite_deathtanz_14:
	.incbin "sprites/dynamic/deathtanz/sheet/14.4bpp"
	gGraphicHeader_Sprite_deathtanz_14_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/14.gbapal"

gGraphicHeader_Sprite_deathtanz_15:
	.incbin "sprites/dynamic/deathtanz/sheet/15.4bpp"
	gGraphicHeader_Sprite_deathtanz_15_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/15.gbapal"

gGraphicHeader_Sprite_deathtanz_16:
	.incbin "sprites/dynamic/deathtanz/sheet/16.4bpp"
	gGraphicHeader_Sprite_deathtanz_16_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/16.gbapal"

gGraphicHeader_Sprite_deathtanz_17:
	.incbin "sprites/dynamic/deathtanz/sheet/17.4bpp"
	gGraphicHeader_Sprite_deathtanz_17_Palettes:
	.incbin "sprites/dynamic/deathtanz/sheet/17.gbapal"
