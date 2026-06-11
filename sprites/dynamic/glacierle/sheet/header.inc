.balign 4, 0

.global gGraphicHeader_Sprite_glacierle
gGraphicHeader_Sprite_glacierle:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_glacierle_0-. @ src
	.4byte 2816 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 704, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_glacierle_1-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_glacierle_2-. @ src
	.4byte 2464 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 616, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_glacierle_3-. @ src
	.4byte 3232 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 808, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_glacierle_4-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_glacierle_5-. @ src
	.4byte 4352 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1088, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_glacierle_6-. @ src
	.4byte 3552 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 888, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_glacierle_7-. @ src
	.4byte 5408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_glacierle_8-. @ src
	.4byte 4288 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1072, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_glacierle_9-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_glacierle_10-. @ src
	.4byte 5440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_glacierle_11-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_glacierle_12-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_glacierle_13-. @ src
	.4byte 5888 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1472, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_glacierle_14-. @ src
	.4byte 4288 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1072, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_glacierle_15-. @ src
	.4byte 4800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_glacierle_16-. @ src
	.4byte 3584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_glacierle_17-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_glacierle_18-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_glacierle_19-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_glacierle_20-. @ src
	.4byte 3104 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 776, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_glacierle_21-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_glacierle_22-. @ src
	.4byte 3136 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 784, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_glacierle_23-. @ src
	.4byte 4128 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1032, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_glacierle_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_glacierle_0:
	.incbin "sprites/dynamic/glacierle/sheet/0.4bpp"
	gGraphicHeader_Sprite_glacierle_0_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/0.gbapal"

gGraphicHeader_Sprite_glacierle_1:
	.incbin "sprites/dynamic/glacierle/sheet/1.4bpp"
	gGraphicHeader_Sprite_glacierle_1_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/1.gbapal"

gGraphicHeader_Sprite_glacierle_2:
	.incbin "sprites/dynamic/glacierle/sheet/2.4bpp"
	gGraphicHeader_Sprite_glacierle_2_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/2.gbapal"

gGraphicHeader_Sprite_glacierle_3:
	.incbin "sprites/dynamic/glacierle/sheet/3.4bpp"
	gGraphicHeader_Sprite_glacierle_3_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/3.gbapal"

gGraphicHeader_Sprite_glacierle_4:
	.incbin "sprites/dynamic/glacierle/sheet/4.4bpp"
	gGraphicHeader_Sprite_glacierle_4_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/4.gbapal"

gGraphicHeader_Sprite_glacierle_5:
	.incbin "sprites/dynamic/glacierle/sheet/5.4bpp"
	gGraphicHeader_Sprite_glacierle_5_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/5.gbapal"

gGraphicHeader_Sprite_glacierle_6:
	.incbin "sprites/dynamic/glacierle/sheet/6.4bpp"
	gGraphicHeader_Sprite_glacierle_6_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/6.gbapal"

gGraphicHeader_Sprite_glacierle_7:
	.incbin "sprites/dynamic/glacierle/sheet/7.4bpp"
	gGraphicHeader_Sprite_glacierle_7_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/7.gbapal"

gGraphicHeader_Sprite_glacierle_8:
	.incbin "sprites/dynamic/glacierle/sheet/8.4bpp"
	gGraphicHeader_Sprite_glacierle_8_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/8.gbapal"

gGraphicHeader_Sprite_glacierle_9:
	.incbin "sprites/dynamic/glacierle/sheet/9.4bpp"
	gGraphicHeader_Sprite_glacierle_9_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/9.gbapal"

gGraphicHeader_Sprite_glacierle_10:
	.incbin "sprites/dynamic/glacierle/sheet/10.4bpp"
	gGraphicHeader_Sprite_glacierle_10_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/10.gbapal"

gGraphicHeader_Sprite_glacierle_11:
	.incbin "sprites/dynamic/glacierle/sheet/11.4bpp"
	gGraphicHeader_Sprite_glacierle_11_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/11.gbapal"

gGraphicHeader_Sprite_glacierle_12:
	.incbin "sprites/dynamic/glacierle/sheet/12.4bpp"
	gGraphicHeader_Sprite_glacierle_12_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/12.gbapal"

gGraphicHeader_Sprite_glacierle_13:
	.incbin "sprites/dynamic/glacierle/sheet/13.4bpp"
	gGraphicHeader_Sprite_glacierle_13_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/13.gbapal"

gGraphicHeader_Sprite_glacierle_14:
	.incbin "sprites/dynamic/glacierle/sheet/14.4bpp"
	gGraphicHeader_Sprite_glacierle_14_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/14.gbapal"

gGraphicHeader_Sprite_glacierle_15:
	.incbin "sprites/dynamic/glacierle/sheet/15.4bpp"
	gGraphicHeader_Sprite_glacierle_15_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/15.gbapal"

gGraphicHeader_Sprite_glacierle_16:
	.incbin "sprites/dynamic/glacierle/sheet/16.4bpp"
	gGraphicHeader_Sprite_glacierle_16_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/16.gbapal"

gGraphicHeader_Sprite_glacierle_17:
	.incbin "sprites/dynamic/glacierle/sheet/17.4bpp"
	gGraphicHeader_Sprite_glacierle_17_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/17.gbapal"

gGraphicHeader_Sprite_glacierle_18:
	.incbin "sprites/dynamic/glacierle/sheet/18.4bpp"
	gGraphicHeader_Sprite_glacierle_18_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/18.gbapal"

gGraphicHeader_Sprite_glacierle_19:
	.incbin "sprites/dynamic/glacierle/sheet/19.4bpp"
	gGraphicHeader_Sprite_glacierle_19_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/19.gbapal"

gGraphicHeader_Sprite_glacierle_20:
	.incbin "sprites/dynamic/glacierle/sheet/20.4bpp"
	gGraphicHeader_Sprite_glacierle_20_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/20.gbapal"

gGraphicHeader_Sprite_glacierle_21:
	.incbin "sprites/dynamic/glacierle/sheet/21.4bpp"
	gGraphicHeader_Sprite_glacierle_21_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/21.gbapal"

gGraphicHeader_Sprite_glacierle_22:
	.incbin "sprites/dynamic/glacierle/sheet/22.4bpp"
	gGraphicHeader_Sprite_glacierle_22_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/22.gbapal"

gGraphicHeader_Sprite_glacierle_23:
	.incbin "sprites/dynamic/glacierle/sheet/23.4bpp"
	gGraphicHeader_Sprite_glacierle_23_Palettes:
	.incbin "sprites/dynamic/glacierle/sheet/23.gbapal"
