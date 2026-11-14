@ Zero 2's Bear, dynamic motion 160, Zero 3's DM207_Z2_BEAR

.balign 4, 0

.global gGraphicHeader_Sprite_z2_bear
gGraphicHeader_Sprite_z2_bear:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_bear_0-. @ src
	.4byte 2624 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 656, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_bear_1-. @ src
	.4byte 4736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_bear_2-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_bear_3-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_bear_4-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_bear_5-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_bear_6-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_bear_7-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_bear_8-. @ src
	.4byte 3488 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 872, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_bear_9-. @ src
	.4byte 4480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_bear_10-. @ src
	.4byte 4928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_bear_11-. @ src
	.4byte 4448 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1112, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_bear_12-. @ src
	.4byte 3296 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 824, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_bear_13-. @ src
	.4byte 4512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_bear_14-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_bear_15-. @ src
	.4byte 4032 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1008, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_bear_16-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_bear_17-. @ src
	.4byte 5312 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1328, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_bear_18-. @ src
	.4byte 4064 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1016, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_bear_19-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_bear_20-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_bear_21-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_bear_22-. @ src
	.4byte 4320 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1080, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_bear_23-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_bear_24-. @ src
	.4byte 4000 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1000, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_bear_25-. @ src
	.4byte 5120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_bear_26-. @ src
	.4byte 4256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1064, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_bear_27-. @ src
	.4byte 4320 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1080, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_bear_28-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_bear_29-. @ src
	.4byte 4480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_bear_30-. @ src
	.4byte 4416 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1104, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_bear_31-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_bear_32-. @ src
	.4byte 3040 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_bear_33-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_bear_34-. @ src
	.4byte 4896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_bear_35-. @ src
	.4byte 4480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_bear_36-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_bear_37-. @ src
	.4byte 4960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_bear_38-. @ src
	.4byte 5440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_bear_39-. @ src
	.4byte 4384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1096, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_bear_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_bear_0:
	.incbin "sprites/dynamic/z2_bear/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_bear_0_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_bear_1:
	.incbin "sprites/dynamic/z2_bear/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_bear_1_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_bear_2:
	.incbin "sprites/dynamic/z2_bear/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_bear_2_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_bear_3:
	.incbin "sprites/dynamic/z2_bear/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_bear_3_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_bear_4:
	.incbin "sprites/dynamic/z2_bear/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_bear_4_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_bear_5:
	.incbin "sprites/dynamic/z2_bear/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_bear_5_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_bear_6:
	.incbin "sprites/dynamic/z2_bear/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_bear_6_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_bear_7:
	.incbin "sprites/dynamic/z2_bear/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_bear_7_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_bear_8:
	.incbin "sprites/dynamic/z2_bear/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_bear_8_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_bear_9:
	.incbin "sprites/dynamic/z2_bear/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_bear_9_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_bear_10:
	.incbin "sprites/dynamic/z2_bear/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_bear_10_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_bear_11:
	.incbin "sprites/dynamic/z2_bear/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_bear_11_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_bear_12:
	.incbin "sprites/dynamic/z2_bear/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_bear_12_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_bear_13:
	.incbin "sprites/dynamic/z2_bear/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_bear_13_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_bear_14:
	.incbin "sprites/dynamic/z2_bear/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_bear_14_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_bear_15:
	.incbin "sprites/dynamic/z2_bear/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_bear_15_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_bear_16:
	.incbin "sprites/dynamic/z2_bear/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_bear_16_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_bear_17:
	.incbin "sprites/dynamic/z2_bear/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_bear_17_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_bear_18:
	.incbin "sprites/dynamic/z2_bear/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_bear_18_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_bear_19:
	.incbin "sprites/dynamic/z2_bear/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_bear_19_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_bear_20:
	.incbin "sprites/dynamic/z2_bear/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_bear_20_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_bear_21:
	.incbin "sprites/dynamic/z2_bear/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_bear_21_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_bear_22:
	.incbin "sprites/dynamic/z2_bear/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_bear_22_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_bear_23:
	.incbin "sprites/dynamic/z2_bear/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_bear_23_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_bear_24:
	.incbin "sprites/dynamic/z2_bear/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_bear_24_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_bear_25:
	.incbin "sprites/dynamic/z2_bear/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_bear_25_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_bear_26:
	.incbin "sprites/dynamic/z2_bear/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_bear_26_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_bear_27:
	.incbin "sprites/dynamic/z2_bear/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_bear_27_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_bear_28:
	.incbin "sprites/dynamic/z2_bear/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_bear_28_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_bear_29:
	.incbin "sprites/dynamic/z2_bear/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_bear_29_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_bear_30:
	.incbin "sprites/dynamic/z2_bear/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_bear_30_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_bear_31:
	.incbin "sprites/dynamic/z2_bear/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_bear_31_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_bear_32:
	.incbin "sprites/dynamic/z2_bear/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_bear_32_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_bear_33:
	.incbin "sprites/dynamic/z2_bear/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_bear_33_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_bear_34:
	.incbin "sprites/dynamic/z2_bear/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_bear_34_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_bear_35:
	.incbin "sprites/dynamic/z2_bear/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_bear_35_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_bear_36:
	.incbin "sprites/dynamic/z2_bear/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_bear_36_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_bear_37:
	.incbin "sprites/dynamic/z2_bear/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_bear_37_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_bear_38:
	.incbin "sprites/dynamic/z2_bear/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_bear_38_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_bear_39:
	.incbin "sprites/dynamic/z2_bear/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_bear_39_Palettes:
	.incbin "sprites/dynamic/z2_bear/sheet/39.gbapal"

.global gGraphicHeader_Sprite_z2_bear_End
gGraphicHeader_Sprite_z2_bear_End:
