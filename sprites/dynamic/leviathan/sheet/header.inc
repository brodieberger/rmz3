.balign 4, 0

.global gGraphicHeader_Sprite_leviathan
gGraphicHeader_Sprite_leviathan:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_leviathan_0-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_leviathan_1-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_leviathan_2-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_leviathan_3-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_leviathan_4-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_leviathan_5-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_leviathan_6-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_leviathan_7-. @ src
	.4byte 1856 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_leviathan_8-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_leviathan_9-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_leviathan_10-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_leviathan_11-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_leviathan_12-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_leviathan_13-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_leviathan_14-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_leviathan_15-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_leviathan_16-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_leviathan_17-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_leviathan_18-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_leviathan_19-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_leviathan_20-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_leviathan_21-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_leviathan_22-. @ src
	.4byte 2272 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 568, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_leviathan_23-. @ src
	.4byte 2528 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 632, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_leviathan_24-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_leviathan_25-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_leviathan_26-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_leviathan_27-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_leviathan_28-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_leviathan_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_leviathan_0:
	.incbin "sprites/dynamic/leviathan/sheet/0.4bpp"
	gGraphicHeader_Sprite_leviathan_0_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/0.gbapal"

gGraphicHeader_Sprite_leviathan_1:
	.incbin "sprites/dynamic/leviathan/sheet/1.4bpp"
	gGraphicHeader_Sprite_leviathan_1_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/1.gbapal"

gGraphicHeader_Sprite_leviathan_2:
	.incbin "sprites/dynamic/leviathan/sheet/2.4bpp"
	gGraphicHeader_Sprite_leviathan_2_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/2.gbapal"

gGraphicHeader_Sprite_leviathan_3:
	.incbin "sprites/dynamic/leviathan/sheet/3.4bpp"
	gGraphicHeader_Sprite_leviathan_3_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/3.gbapal"

gGraphicHeader_Sprite_leviathan_4:
	.incbin "sprites/dynamic/leviathan/sheet/4.4bpp"
	gGraphicHeader_Sprite_leviathan_4_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/4.gbapal"

gGraphicHeader_Sprite_leviathan_5:
	.incbin "sprites/dynamic/leviathan/sheet/5.4bpp"
	gGraphicHeader_Sprite_leviathan_5_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/5.gbapal"

gGraphicHeader_Sprite_leviathan_6:
	.incbin "sprites/dynamic/leviathan/sheet/6.4bpp"
	gGraphicHeader_Sprite_leviathan_6_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/6.gbapal"

gGraphicHeader_Sprite_leviathan_7:
	.incbin "sprites/dynamic/leviathan/sheet/7.4bpp"
	gGraphicHeader_Sprite_leviathan_7_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/7.gbapal"

gGraphicHeader_Sprite_leviathan_8:
	.incbin "sprites/dynamic/leviathan/sheet/8.4bpp"
	gGraphicHeader_Sprite_leviathan_8_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/8.gbapal"

gGraphicHeader_Sprite_leviathan_9:
	.incbin "sprites/dynamic/leviathan/sheet/9.4bpp"
	gGraphicHeader_Sprite_leviathan_9_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/9.gbapal"

gGraphicHeader_Sprite_leviathan_10:
	.incbin "sprites/dynamic/leviathan/sheet/10.4bpp"
	gGraphicHeader_Sprite_leviathan_10_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/10.gbapal"

gGraphicHeader_Sprite_leviathan_11:
	.incbin "sprites/dynamic/leviathan/sheet/11.4bpp"
	gGraphicHeader_Sprite_leviathan_11_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/11.gbapal"

gGraphicHeader_Sprite_leviathan_12:
	.incbin "sprites/dynamic/leviathan/sheet/12.4bpp"
	gGraphicHeader_Sprite_leviathan_12_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/12.gbapal"

gGraphicHeader_Sprite_leviathan_13:
	.incbin "sprites/dynamic/leviathan/sheet/13.4bpp"
	gGraphicHeader_Sprite_leviathan_13_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/13.gbapal"

gGraphicHeader_Sprite_leviathan_14:
	.incbin "sprites/dynamic/leviathan/sheet/14.4bpp"
	gGraphicHeader_Sprite_leviathan_14_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/14.gbapal"

gGraphicHeader_Sprite_leviathan_15:
	.incbin "sprites/dynamic/leviathan/sheet/15.4bpp"
	gGraphicHeader_Sprite_leviathan_15_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/15.gbapal"

gGraphicHeader_Sprite_leviathan_16:
	.incbin "sprites/dynamic/leviathan/sheet/16.4bpp"
	gGraphicHeader_Sprite_leviathan_16_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/16.gbapal"

gGraphicHeader_Sprite_leviathan_17:
	.incbin "sprites/dynamic/leviathan/sheet/17.4bpp"
	gGraphicHeader_Sprite_leviathan_17_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/17.gbapal"

gGraphicHeader_Sprite_leviathan_18:
	.incbin "sprites/dynamic/leviathan/sheet/18.4bpp"
	gGraphicHeader_Sprite_leviathan_18_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/18.gbapal"

gGraphicHeader_Sprite_leviathan_19:
	.incbin "sprites/dynamic/leviathan/sheet/19.4bpp"
	gGraphicHeader_Sprite_leviathan_19_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/19.gbapal"

gGraphicHeader_Sprite_leviathan_20:
	.incbin "sprites/dynamic/leviathan/sheet/20.4bpp"
	gGraphicHeader_Sprite_leviathan_20_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/20.gbapal"

gGraphicHeader_Sprite_leviathan_21:
	.incbin "sprites/dynamic/leviathan/sheet/21.4bpp"
	gGraphicHeader_Sprite_leviathan_21_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/21.gbapal"

gGraphicHeader_Sprite_leviathan_22:
	.incbin "sprites/dynamic/leviathan/sheet/22.4bpp"
	gGraphicHeader_Sprite_leviathan_22_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/22.gbapal"

gGraphicHeader_Sprite_leviathan_23:
	.incbin "sprites/dynamic/leviathan/sheet/23.4bpp"
	gGraphicHeader_Sprite_leviathan_23_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/23.gbapal"

gGraphicHeader_Sprite_leviathan_24:
	.incbin "sprites/dynamic/leviathan/sheet/24.4bpp"
	gGraphicHeader_Sprite_leviathan_24_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/24.gbapal"

gGraphicHeader_Sprite_leviathan_25:
	.incbin "sprites/dynamic/leviathan/sheet/25.4bpp"
	gGraphicHeader_Sprite_leviathan_25_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/25.gbapal"

gGraphicHeader_Sprite_leviathan_26:
	.incbin "sprites/dynamic/leviathan/sheet/26.4bpp"
	gGraphicHeader_Sprite_leviathan_26_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/26.gbapal"

gGraphicHeader_Sprite_leviathan_27:
	.incbin "sprites/dynamic/leviathan/sheet/27.4bpp"
	gGraphicHeader_Sprite_leviathan_27_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/27.gbapal"

gGraphicHeader_Sprite_leviathan_28:
	.incbin "sprites/dynamic/leviathan/sheet/28.4bpp"
	gGraphicHeader_Sprite_leviathan_28_Palettes:
	.incbin "sprites/dynamic/leviathan/sheet/28.gbapal"
