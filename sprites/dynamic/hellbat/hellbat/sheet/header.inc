.balign 4, 0

.global gGraphicHeader_Sprite_hellbat_hellbat
gGraphicHeader_Sprite_hellbat_hellbat:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_0-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_1-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_2-. @ src
	.4byte 3264 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 816, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_3-. @ src
	.4byte 3872 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 968, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_4-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_5-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_6-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_7-. @ src
	.4byte 3328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_8-. @ src
	.4byte 3040 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_9-. @ src
	.4byte 3552 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 888, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_10-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_11-. @ src
	.4byte 2624 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 656, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_12-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_13-. @ src
	.4byte 3392 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 848, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_14-. @ src
	.4byte 3744 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 936, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_15-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_16-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_17-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_hellbat_hellbat_18-. @ src
	.4byte 4832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_hellbat_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_hellbat_hellbat_0:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/0.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_0_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/0.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_1:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/1.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_1_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/1.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_2:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/2.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_2_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/2.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_3:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/3.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_3_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/3.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_4:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/4.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_4_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/4.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_5:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/5.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_5_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/5.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_6:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/6.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_6_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/6.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_7:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/7.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_7_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/7.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_8:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/8.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_8_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/8.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_9:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/9.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_9_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/9.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_10:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/10.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_10_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/10.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_11:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/11.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_11_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/11.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_12:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/12.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_12_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/12.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_13:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/13.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_13_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/13.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_14:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/14.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_14_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/14.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_15:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/15.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_15_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/15.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_16:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/16.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_16_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/16.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_17:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/17.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_17_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/17.gbapal"

gGraphicHeader_Sprite_hellbat_hellbat_18:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/18.4bpp"
	gGraphicHeader_Sprite_hellbat_hellbat_18_Palettes:
	.incbin "sprites/dynamic/hellbat/hellbat/sheet/18.gbapal"
