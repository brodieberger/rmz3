.balign 4, 0

.global gGraphicHeader_Sprite_harpuia
gGraphicHeader_Sprite_harpuia:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_harpuia_0-. @ src
	.4byte 1248 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_harpuia_1-. @ src
	.4byte 1568 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_harpuia_2-. @ src
	.4byte 1536 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_harpuia_3-. @ src
	.4byte 1696 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 424, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_harpuia_4-. @ src
	.4byte 832 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_harpuia_5-. @ src
	.4byte 1536 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_harpuia_6-. @ src
	.4byte 1984 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 496, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_harpuia_7-. @ src
	.4byte 1248 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_harpuia_8-. @ src
	.4byte 960 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_harpuia_9-. @ src
	.4byte 1920 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_harpuia_10-. @ src
	.4byte 1152 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_harpuia_11-. @ src
	.4byte 1312 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_harpuia_12-. @ src
	.4byte 1920 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_harpuia_13-. @ src
	.4byte 1600 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_harpuia_14-. @ src
	.4byte 1792 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_harpuia_15-. @ src
	.4byte 800 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_harpuia_16-. @ src
	.4byte 1728 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_harpuia_17-. @ src
	.4byte 1376 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_harpuia_18-. @ src
	.4byte 960 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_harpuia_19-. @ src
	.4byte 1600 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_harpuia_20-. @ src
	.4byte 1760 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 440, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_harpuia_21-. @ src
	.4byte 800 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_harpuia_22-. @ src
	.4byte 1664 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_harpuia_23-. @ src
	.4byte 992 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_harpuia_24-. @ src
	.4byte 1920 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_harpuia_25-. @ src
	.4byte 1600 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_harpuia_26-. @ src
	.4byte 1216 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_harpuia_27-. @ src
	.4byte 864 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_harpuia_28-. @ src
	.4byte 832 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_harpuia_29-. @ src
	.4byte 1408 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_harpuia_30-. @ src
	.4byte 800 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_harpuia_31-. @ src
	.4byte 928 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_harpuia_32-. @ src
	.4byte 928 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_harpuia_33-. @ src
	.4byte 1632 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_harpuia_34-. @ src
	.4byte 800 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_harpuia_35-. @ src
	.4byte 1408 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_harpuia_36-. @ src
	.4byte 2048 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_harpuia_37-. @ src
	.4byte 1920 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_harpuia_38-. @ src
	.4byte 2048 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_harpuia_39-. @ src
	.4byte 1984 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 496, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_harpuia_40-. @ src
	.4byte 1856 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_harpuia_41-. @ src
	.4byte 1952 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 488, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_harpuia_42-. @ src
	.4byte 1600 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_harpuia_43-. @ src
	.4byte 1632 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_harpuia_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_harpuia_0:
	.incbin "sprites/dynamic/harpuia/sheet/0.4bpp"
	gGraphicHeader_Sprite_harpuia_0_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/0.gbapal"

gGraphicHeader_Sprite_harpuia_1:
	.incbin "sprites/dynamic/harpuia/sheet/1.4bpp"
	gGraphicHeader_Sprite_harpuia_1_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/1.gbapal"

gGraphicHeader_Sprite_harpuia_2:
	.incbin "sprites/dynamic/harpuia/sheet/2.4bpp"
	gGraphicHeader_Sprite_harpuia_2_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/2.gbapal"

gGraphicHeader_Sprite_harpuia_3:
	.incbin "sprites/dynamic/harpuia/sheet/3.4bpp"
	gGraphicHeader_Sprite_harpuia_3_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/3.gbapal"

gGraphicHeader_Sprite_harpuia_4:
	.incbin "sprites/dynamic/harpuia/sheet/4.4bpp"
	gGraphicHeader_Sprite_harpuia_4_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/4.gbapal"

gGraphicHeader_Sprite_harpuia_5:
	.incbin "sprites/dynamic/harpuia/sheet/5.4bpp"
	gGraphicHeader_Sprite_harpuia_5_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/5.gbapal"

gGraphicHeader_Sprite_harpuia_6:
	.incbin "sprites/dynamic/harpuia/sheet/6.4bpp"
	gGraphicHeader_Sprite_harpuia_6_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/6.gbapal"

gGraphicHeader_Sprite_harpuia_7:
	.incbin "sprites/dynamic/harpuia/sheet/7.4bpp"
	gGraphicHeader_Sprite_harpuia_7_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/7.gbapal"

gGraphicHeader_Sprite_harpuia_8:
	.incbin "sprites/dynamic/harpuia/sheet/8.4bpp"
	gGraphicHeader_Sprite_harpuia_8_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/8.gbapal"

gGraphicHeader_Sprite_harpuia_9:
	.incbin "sprites/dynamic/harpuia/sheet/9.4bpp"
	gGraphicHeader_Sprite_harpuia_9_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/9.gbapal"

gGraphicHeader_Sprite_harpuia_10:
	.incbin "sprites/dynamic/harpuia/sheet/10.4bpp"
	gGraphicHeader_Sprite_harpuia_10_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/10.gbapal"

gGraphicHeader_Sprite_harpuia_11:
	.incbin "sprites/dynamic/harpuia/sheet/11.4bpp"
	gGraphicHeader_Sprite_harpuia_11_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/11.gbapal"

gGraphicHeader_Sprite_harpuia_12:
	.incbin "sprites/dynamic/harpuia/sheet/12.4bpp"
	gGraphicHeader_Sprite_harpuia_12_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/12.gbapal"

gGraphicHeader_Sprite_harpuia_13:
	.incbin "sprites/dynamic/harpuia/sheet/13.4bpp"
	gGraphicHeader_Sprite_harpuia_13_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/13.gbapal"

gGraphicHeader_Sprite_harpuia_14:
	.incbin "sprites/dynamic/harpuia/sheet/14.4bpp"
	gGraphicHeader_Sprite_harpuia_14_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/14.gbapal"

gGraphicHeader_Sprite_harpuia_15:
	.incbin "sprites/dynamic/harpuia/sheet/15.4bpp"
	gGraphicHeader_Sprite_harpuia_15_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/15.gbapal"

gGraphicHeader_Sprite_harpuia_16:
	.incbin "sprites/dynamic/harpuia/sheet/16.4bpp"
	gGraphicHeader_Sprite_harpuia_16_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/16.gbapal"

gGraphicHeader_Sprite_harpuia_17:
	.incbin "sprites/dynamic/harpuia/sheet/17.4bpp"
	gGraphicHeader_Sprite_harpuia_17_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/17.gbapal"

gGraphicHeader_Sprite_harpuia_18:
	.incbin "sprites/dynamic/harpuia/sheet/18.4bpp"
	gGraphicHeader_Sprite_harpuia_18_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/18.gbapal"

gGraphicHeader_Sprite_harpuia_19:
	.incbin "sprites/dynamic/harpuia/sheet/19.4bpp"
	gGraphicHeader_Sprite_harpuia_19_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/19.gbapal"

gGraphicHeader_Sprite_harpuia_20:
	.incbin "sprites/dynamic/harpuia/sheet/20.4bpp"
	gGraphicHeader_Sprite_harpuia_20_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/20.gbapal"

gGraphicHeader_Sprite_harpuia_21:
	.incbin "sprites/dynamic/harpuia/sheet/21.4bpp"
	gGraphicHeader_Sprite_harpuia_21_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/21.gbapal"

gGraphicHeader_Sprite_harpuia_22:
	.incbin "sprites/dynamic/harpuia/sheet/22.4bpp"
	gGraphicHeader_Sprite_harpuia_22_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/22.gbapal"

gGraphicHeader_Sprite_harpuia_23:
	.incbin "sprites/dynamic/harpuia/sheet/23.4bpp"
	gGraphicHeader_Sprite_harpuia_23_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/23.gbapal"

gGraphicHeader_Sprite_harpuia_24:
	.incbin "sprites/dynamic/harpuia/sheet/24.4bpp"
	gGraphicHeader_Sprite_harpuia_24_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/24.gbapal"

gGraphicHeader_Sprite_harpuia_25:
	.incbin "sprites/dynamic/harpuia/sheet/25.4bpp"
	gGraphicHeader_Sprite_harpuia_25_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/25.gbapal"

gGraphicHeader_Sprite_harpuia_26:
	.incbin "sprites/dynamic/harpuia/sheet/26.4bpp"
	gGraphicHeader_Sprite_harpuia_26_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/26.gbapal"

gGraphicHeader_Sprite_harpuia_27:
	.incbin "sprites/dynamic/harpuia/sheet/27.4bpp"
	gGraphicHeader_Sprite_harpuia_27_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/27.gbapal"

gGraphicHeader_Sprite_harpuia_28:
	.incbin "sprites/dynamic/harpuia/sheet/28.4bpp"
	gGraphicHeader_Sprite_harpuia_28_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/28.gbapal"

gGraphicHeader_Sprite_harpuia_29:
	.incbin "sprites/dynamic/harpuia/sheet/29.4bpp"
	gGraphicHeader_Sprite_harpuia_29_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/29.gbapal"

gGraphicHeader_Sprite_harpuia_30:
	.incbin "sprites/dynamic/harpuia/sheet/30.4bpp"
	gGraphicHeader_Sprite_harpuia_30_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/30.gbapal"

gGraphicHeader_Sprite_harpuia_31:
	.incbin "sprites/dynamic/harpuia/sheet/31.4bpp"
	gGraphicHeader_Sprite_harpuia_31_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/31.gbapal"

gGraphicHeader_Sprite_harpuia_32:
	.incbin "sprites/dynamic/harpuia/sheet/32.4bpp"
	gGraphicHeader_Sprite_harpuia_32_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/32.gbapal"

gGraphicHeader_Sprite_harpuia_33:
	.incbin "sprites/dynamic/harpuia/sheet/33.4bpp"
	gGraphicHeader_Sprite_harpuia_33_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/33.gbapal"

gGraphicHeader_Sprite_harpuia_34:
	.incbin "sprites/dynamic/harpuia/sheet/34.4bpp"
	gGraphicHeader_Sprite_harpuia_34_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/34.gbapal"

gGraphicHeader_Sprite_harpuia_35:
	.incbin "sprites/dynamic/harpuia/sheet/35.4bpp"
	gGraphicHeader_Sprite_harpuia_35_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/35.gbapal"

gGraphicHeader_Sprite_harpuia_36:
	.incbin "sprites/dynamic/harpuia/sheet/36.4bpp"
	gGraphicHeader_Sprite_harpuia_36_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/36.gbapal"

gGraphicHeader_Sprite_harpuia_37:
	.incbin "sprites/dynamic/harpuia/sheet/37.4bpp"
	gGraphicHeader_Sprite_harpuia_37_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/37.gbapal"

gGraphicHeader_Sprite_harpuia_38:
	.incbin "sprites/dynamic/harpuia/sheet/38.4bpp"
	gGraphicHeader_Sprite_harpuia_38_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/38.gbapal"

gGraphicHeader_Sprite_harpuia_39:
	.incbin "sprites/dynamic/harpuia/sheet/39.4bpp"
	gGraphicHeader_Sprite_harpuia_39_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/39.gbapal"

gGraphicHeader_Sprite_harpuia_40:
	.incbin "sprites/dynamic/harpuia/sheet/40.4bpp"
	gGraphicHeader_Sprite_harpuia_40_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/40.gbapal"

gGraphicHeader_Sprite_harpuia_41:
	.incbin "sprites/dynamic/harpuia/sheet/41.4bpp"
	gGraphicHeader_Sprite_harpuia_41_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/41.gbapal"

gGraphicHeader_Sprite_harpuia_42:
	.incbin "sprites/dynamic/harpuia/sheet/42.4bpp"
	gGraphicHeader_Sprite_harpuia_42_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/42.gbapal"

gGraphicHeader_Sprite_harpuia_43:
	.incbin "sprites/dynamic/harpuia/sheet/43.4bpp"
	gGraphicHeader_Sprite_harpuia_43_Palettes:
	.incbin "sprites/dynamic/harpuia/sheet/43.gbapal"
