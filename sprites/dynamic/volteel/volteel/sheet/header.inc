.balign 4, 0

.global gGraphicHeader_Sprite_volteel_volteel
gGraphicHeader_Sprite_volteel_volteel:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_volteel_volteel_0-. @ src
	.4byte 5088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_volteel_volteel_1-. @ src
	.4byte 4800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_volteel_volteel_2-. @ src
	.4byte 2976 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 744, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_volteel_volteel_3-. @ src
	.4byte 2528 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 632, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_volteel_volteel_4-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_volteel_volteel_5-. @ src
	.4byte 4064 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1016, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_volteel_volteel_6-. @ src
	.4byte 4256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1064, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_volteel_volteel_7-. @ src
	.4byte 3712 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 928, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_volteel_volteel_8-. @ src
	.4byte 4736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_volteel_volteel_9-. @ src
	.4byte 3136 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 784, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_volteel_volteel_10-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_volteel_volteel_11-. @ src
	.4byte 4640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_volteel_volteel_12-. @ src
	.4byte 5024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_volteel_volteel_13-. @ src
	.4byte 3264 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 816, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_volteel_volteel_14-. @ src
	.4byte 4896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_volteel_volteel_15-. @ src
	.4byte 3136 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 784, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_volteel_volteel_16-. @ src
	.4byte 4448 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1112, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_volteel_volteel_17-. @ src
	.4byte 3008 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 752, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_volteel_volteel_18-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_volteel_volteel_19-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_volteel_volteel_20-. @ src
	.4byte 1856 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_volteel_volteel_21-. @ src
	.4byte 4928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_volteel_volteel_22-. @ src
	.4byte 3456 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 864, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_volteel_volteel_23-. @ src
	.4byte 2752 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 688, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_volteel_volteel_24-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_volteel_volteel_25-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_volteel_volteel_26-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_volteel_volteel_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_volteel_volteel_0:
	.incbin "sprites/dynamic/volteel/volteel/sheet/0.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_0_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/0.gbapal"

gGraphicHeader_Sprite_volteel_volteel_1:
	.incbin "sprites/dynamic/volteel/volteel/sheet/1.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_1_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/1.gbapal"

gGraphicHeader_Sprite_volteel_volteel_2:
	.incbin "sprites/dynamic/volteel/volteel/sheet/2.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_2_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/2.gbapal"

gGraphicHeader_Sprite_volteel_volteel_3:
	.incbin "sprites/dynamic/volteel/volteel/sheet/3.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_3_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/3.gbapal"

gGraphicHeader_Sprite_volteel_volteel_4:
	.incbin "sprites/dynamic/volteel/volteel/sheet/4.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_4_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/4.gbapal"

gGraphicHeader_Sprite_volteel_volteel_5:
	.incbin "sprites/dynamic/volteel/volteel/sheet/5.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_5_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/5.gbapal"

gGraphicHeader_Sprite_volteel_volteel_6:
	.incbin "sprites/dynamic/volteel/volteel/sheet/6.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_6_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/6.gbapal"

gGraphicHeader_Sprite_volteel_volteel_7:
	.incbin "sprites/dynamic/volteel/volteel/sheet/7.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_7_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/7.gbapal"

gGraphicHeader_Sprite_volteel_volteel_8:
	.incbin "sprites/dynamic/volteel/volteel/sheet/8.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_8_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/8.gbapal"

gGraphicHeader_Sprite_volteel_volteel_9:
	.incbin "sprites/dynamic/volteel/volteel/sheet/9.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_9_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/9.gbapal"

gGraphicHeader_Sprite_volteel_volteel_10:
	.incbin "sprites/dynamic/volteel/volteel/sheet/10.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_10_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/10.gbapal"

gGraphicHeader_Sprite_volteel_volteel_11:
	.incbin "sprites/dynamic/volteel/volteel/sheet/11.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_11_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/11.gbapal"

gGraphicHeader_Sprite_volteel_volteel_12:
	.incbin "sprites/dynamic/volteel/volteel/sheet/12.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_12_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/12.gbapal"

gGraphicHeader_Sprite_volteel_volteel_13:
	.incbin "sprites/dynamic/volteel/volteel/sheet/13.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_13_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/13.gbapal"

gGraphicHeader_Sprite_volteel_volteel_14:
	.incbin "sprites/dynamic/volteel/volteel/sheet/14.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_14_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/14.gbapal"

gGraphicHeader_Sprite_volteel_volteel_15:
	.incbin "sprites/dynamic/volteel/volteel/sheet/15.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_15_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/15.gbapal"

gGraphicHeader_Sprite_volteel_volteel_16:
	.incbin "sprites/dynamic/volteel/volteel/sheet/16.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_16_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/16.gbapal"

gGraphicHeader_Sprite_volteel_volteel_17:
	.incbin "sprites/dynamic/volteel/volteel/sheet/17.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_17_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/17.gbapal"

gGraphicHeader_Sprite_volteel_volteel_18:
	.incbin "sprites/dynamic/volteel/volteel/sheet/18.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_18_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/18.gbapal"

gGraphicHeader_Sprite_volteel_volteel_19:
	.incbin "sprites/dynamic/volteel/volteel/sheet/19.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_19_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/19.gbapal"

gGraphicHeader_Sprite_volteel_volteel_20:
	.incbin "sprites/dynamic/volteel/volteel/sheet/20.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_20_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/20.gbapal"

gGraphicHeader_Sprite_volteel_volteel_21:
	.incbin "sprites/dynamic/volteel/volteel/sheet/21.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_21_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/21.gbapal"

gGraphicHeader_Sprite_volteel_volteel_22:
	.incbin "sprites/dynamic/volteel/volteel/sheet/22.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_22_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/22.gbapal"

gGraphicHeader_Sprite_volteel_volteel_23:
	.incbin "sprites/dynamic/volteel/volteel/sheet/23.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_23_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/23.gbapal"

gGraphicHeader_Sprite_volteel_volteel_24:
	.incbin "sprites/dynamic/volteel/volteel/sheet/24.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_24_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/24.gbapal"

gGraphicHeader_Sprite_volteel_volteel_25:
	.incbin "sprites/dynamic/volteel/volteel/sheet/25.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_25_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/25.gbapal"

gGraphicHeader_Sprite_volteel_volteel_26:
	.incbin "sprites/dynamic/volteel/volteel/sheet/26.4bpp"
	gGraphicHeader_Sprite_volteel_volteel_26_Palettes:
	.incbin "sprites/dynamic/volteel/volteel/sheet/26.gbapal"
