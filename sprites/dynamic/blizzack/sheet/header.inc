.balign 4, 0

.global gGraphicHeader_Sprite_blizzack
gGraphicHeader_Sprite_blizzack:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_blizzack_0-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_blizzack_1-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_blizzack_2-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_blizzack_3-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_blizzack_4-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_blizzack_5-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_blizzack_6-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_blizzack_7-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_blizzack_8-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_blizzack_9-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_blizzack_10-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_blizzack_11-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_blizzack_12-. @ src
	.4byte 1504 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_blizzack_13-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_blizzack_14-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_blizzack_15-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_blizzack_16-. @ src
	.4byte 1856 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_blizzack_17-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_blizzack_18-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_blizzack_19-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_blizzack_20-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_blizzack_21-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_blizzack_22-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_blizzack_23-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_blizzack_24-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_blizzack_25-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_blizzack_26-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_blizzack_27-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_blizzack_28-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blizzack_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_blizzack_0:
	.incbin "sprites/dynamic/blizzack/sheet/0.4bpp"
	gGraphicHeader_Sprite_blizzack_0_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/0.gbapal"

gGraphicHeader_Sprite_blizzack_1:
	.incbin "sprites/dynamic/blizzack/sheet/1.4bpp"
	gGraphicHeader_Sprite_blizzack_1_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/1.gbapal"

gGraphicHeader_Sprite_blizzack_2:
	.incbin "sprites/dynamic/blizzack/sheet/2.4bpp"
	gGraphicHeader_Sprite_blizzack_2_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/2.gbapal"

gGraphicHeader_Sprite_blizzack_3:
	.incbin "sprites/dynamic/blizzack/sheet/3.4bpp"
	gGraphicHeader_Sprite_blizzack_3_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/3.gbapal"

gGraphicHeader_Sprite_blizzack_4:
	.incbin "sprites/dynamic/blizzack/sheet/4.4bpp"
	gGraphicHeader_Sprite_blizzack_4_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/4.gbapal"

gGraphicHeader_Sprite_blizzack_5:
	.incbin "sprites/dynamic/blizzack/sheet/5.4bpp"
	gGraphicHeader_Sprite_blizzack_5_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/5.gbapal"

gGraphicHeader_Sprite_blizzack_6:
	.incbin "sprites/dynamic/blizzack/sheet/6.4bpp"
	gGraphicHeader_Sprite_blizzack_6_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/6.gbapal"

gGraphicHeader_Sprite_blizzack_7:
	.incbin "sprites/dynamic/blizzack/sheet/7.4bpp"
	gGraphicHeader_Sprite_blizzack_7_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/7.gbapal"

gGraphicHeader_Sprite_blizzack_8:
	.incbin "sprites/dynamic/blizzack/sheet/8.4bpp"
	gGraphicHeader_Sprite_blizzack_8_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/8.gbapal"

gGraphicHeader_Sprite_blizzack_9:
	.incbin "sprites/dynamic/blizzack/sheet/9.4bpp"
	gGraphicHeader_Sprite_blizzack_9_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/9.gbapal"

gGraphicHeader_Sprite_blizzack_10:
	.incbin "sprites/dynamic/blizzack/sheet/10.4bpp"
	gGraphicHeader_Sprite_blizzack_10_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/10.gbapal"

gGraphicHeader_Sprite_blizzack_11:
	.incbin "sprites/dynamic/blizzack/sheet/11.4bpp"
	gGraphicHeader_Sprite_blizzack_11_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/11.gbapal"

gGraphicHeader_Sprite_blizzack_12:
	.incbin "sprites/dynamic/blizzack/sheet/12.4bpp"
	gGraphicHeader_Sprite_blizzack_12_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/12.gbapal"

gGraphicHeader_Sprite_blizzack_13:
	.incbin "sprites/dynamic/blizzack/sheet/13.4bpp"
	gGraphicHeader_Sprite_blizzack_13_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/13.gbapal"

gGraphicHeader_Sprite_blizzack_14:
	.incbin "sprites/dynamic/blizzack/sheet/14.4bpp"
	gGraphicHeader_Sprite_blizzack_14_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/14.gbapal"

gGraphicHeader_Sprite_blizzack_15:
	.incbin "sprites/dynamic/blizzack/sheet/15.4bpp"
	gGraphicHeader_Sprite_blizzack_15_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/15.gbapal"

gGraphicHeader_Sprite_blizzack_16:
	.incbin "sprites/dynamic/blizzack/sheet/16.4bpp"
	gGraphicHeader_Sprite_blizzack_16_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/16.gbapal"

gGraphicHeader_Sprite_blizzack_17:
	.incbin "sprites/dynamic/blizzack/sheet/17.4bpp"
	gGraphicHeader_Sprite_blizzack_17_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/17.gbapal"

gGraphicHeader_Sprite_blizzack_18:
	.incbin "sprites/dynamic/blizzack/sheet/18.4bpp"
	gGraphicHeader_Sprite_blizzack_18_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/18.gbapal"

gGraphicHeader_Sprite_blizzack_19:
	.incbin "sprites/dynamic/blizzack/sheet/19.4bpp"
	gGraphicHeader_Sprite_blizzack_19_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/19.gbapal"

gGraphicHeader_Sprite_blizzack_20:
	.incbin "sprites/dynamic/blizzack/sheet/20.4bpp"
	gGraphicHeader_Sprite_blizzack_20_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/20.gbapal"

gGraphicHeader_Sprite_blizzack_21:
	.incbin "sprites/dynamic/blizzack/sheet/21.4bpp"
	gGraphicHeader_Sprite_blizzack_21_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/21.gbapal"

gGraphicHeader_Sprite_blizzack_22:
	.incbin "sprites/dynamic/blizzack/sheet/22.4bpp"
	gGraphicHeader_Sprite_blizzack_22_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/22.gbapal"

gGraphicHeader_Sprite_blizzack_23:
	.incbin "sprites/dynamic/blizzack/sheet/23.4bpp"
	gGraphicHeader_Sprite_blizzack_23_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/23.gbapal"

gGraphicHeader_Sprite_blizzack_24:
	.incbin "sprites/dynamic/blizzack/sheet/24.4bpp"
	gGraphicHeader_Sprite_blizzack_24_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/24.gbapal"

gGraphicHeader_Sprite_blizzack_25:
	.incbin "sprites/dynamic/blizzack/sheet/25.4bpp"
	gGraphicHeader_Sprite_blizzack_25_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/25.gbapal"

gGraphicHeader_Sprite_blizzack_26:
	.incbin "sprites/dynamic/blizzack/sheet/26.4bpp"
	gGraphicHeader_Sprite_blizzack_26_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/26.gbapal"

gGraphicHeader_Sprite_blizzack_27:
	.incbin "sprites/dynamic/blizzack/sheet/27.4bpp"
	gGraphicHeader_Sprite_blizzack_27_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/27.gbapal"

gGraphicHeader_Sprite_blizzack_28:
	.incbin "sprites/dynamic/blizzack/sheet/28.4bpp"
	gGraphicHeader_Sprite_blizzack_28_Palettes:
	.incbin "sprites/dynamic/blizzack/sheet/28.gbapal"
