.balign 4, 0

.global gGraphicHeader_Sprite_hanumachine
gGraphicHeader_Sprite_hanumachine:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_hanumachine_0-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_hanumachine_1-. @ src
	.4byte 2656 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 664, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_hanumachine_2-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_hanumachine_3-. @ src
	.4byte 2080 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 520, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_hanumachine_4-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_hanumachine_5-. @ src
	.4byte 2880 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 720, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_hanumachine_6-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_hanumachine_7-. @ src
	.4byte 3360 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 840, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_hanumachine_8-. @ src
	.4byte 2816 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 704, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_hanumachine_9-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_hanumachine_10-. @ src
	.4byte 3168 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 792, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_hanumachine_11-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_hanumachine_12-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_hanumachine_13-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_hanumachine_14-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_hanumachine_15-. @ src
	.4byte 3200 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 800, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_hanumachine_16-. @ src
	.4byte 3616 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 904, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_hanumachine_17-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_hanumachine_18-. @ src
	.4byte 2656 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 664, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_hanumachine_19-. @ src
	.4byte 3008 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 752, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hanumachine_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_hanumachine_0:
	.incbin "sprites/dynamic/hanumachine/sheet/0.4bpp"
	gGraphicHeader_Sprite_hanumachine_0_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/0.gbapal"

gGraphicHeader_Sprite_hanumachine_1:
	.incbin "sprites/dynamic/hanumachine/sheet/1.4bpp"
	gGraphicHeader_Sprite_hanumachine_1_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/1.gbapal"

gGraphicHeader_Sprite_hanumachine_2:
	.incbin "sprites/dynamic/hanumachine/sheet/2.4bpp"
	gGraphicHeader_Sprite_hanumachine_2_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/2.gbapal"

gGraphicHeader_Sprite_hanumachine_3:
	.incbin "sprites/dynamic/hanumachine/sheet/3.4bpp"
	gGraphicHeader_Sprite_hanumachine_3_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/3.gbapal"

gGraphicHeader_Sprite_hanumachine_4:
	.incbin "sprites/dynamic/hanumachine/sheet/4.4bpp"
	gGraphicHeader_Sprite_hanumachine_4_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/4.gbapal"

gGraphicHeader_Sprite_hanumachine_5:
	.incbin "sprites/dynamic/hanumachine/sheet/5.4bpp"
	gGraphicHeader_Sprite_hanumachine_5_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/5.gbapal"

gGraphicHeader_Sprite_hanumachine_6:
	.incbin "sprites/dynamic/hanumachine/sheet/6.4bpp"
	gGraphicHeader_Sprite_hanumachine_6_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/6.gbapal"

gGraphicHeader_Sprite_hanumachine_7:
	.incbin "sprites/dynamic/hanumachine/sheet/7.4bpp"
	gGraphicHeader_Sprite_hanumachine_7_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/7.gbapal"

gGraphicHeader_Sprite_hanumachine_8:
	.incbin "sprites/dynamic/hanumachine/sheet/8.4bpp"
	gGraphicHeader_Sprite_hanumachine_8_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/8.gbapal"

gGraphicHeader_Sprite_hanumachine_9:
	.incbin "sprites/dynamic/hanumachine/sheet/9.4bpp"
	gGraphicHeader_Sprite_hanumachine_9_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/9.gbapal"

gGraphicHeader_Sprite_hanumachine_10:
	.incbin "sprites/dynamic/hanumachine/sheet/10.4bpp"
	gGraphicHeader_Sprite_hanumachine_10_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/10.gbapal"

gGraphicHeader_Sprite_hanumachine_11:
	.incbin "sprites/dynamic/hanumachine/sheet/11.4bpp"
	gGraphicHeader_Sprite_hanumachine_11_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/11.gbapal"

gGraphicHeader_Sprite_hanumachine_12:
	.incbin "sprites/dynamic/hanumachine/sheet/12.4bpp"
	gGraphicHeader_Sprite_hanumachine_12_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/12.gbapal"

gGraphicHeader_Sprite_hanumachine_13:
	.incbin "sprites/dynamic/hanumachine/sheet/13.4bpp"
	gGraphicHeader_Sprite_hanumachine_13_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/13.gbapal"

gGraphicHeader_Sprite_hanumachine_14:
	.incbin "sprites/dynamic/hanumachine/sheet/14.4bpp"
	gGraphicHeader_Sprite_hanumachine_14_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/14.gbapal"

gGraphicHeader_Sprite_hanumachine_15:
	.incbin "sprites/dynamic/hanumachine/sheet/15.4bpp"
	gGraphicHeader_Sprite_hanumachine_15_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/15.gbapal"

gGraphicHeader_Sprite_hanumachine_16:
	.incbin "sprites/dynamic/hanumachine/sheet/16.4bpp"
	gGraphicHeader_Sprite_hanumachine_16_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/16.gbapal"

gGraphicHeader_Sprite_hanumachine_17:
	.incbin "sprites/dynamic/hanumachine/sheet/17.4bpp"
	gGraphicHeader_Sprite_hanumachine_17_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/17.gbapal"

gGraphicHeader_Sprite_hanumachine_18:
	.incbin "sprites/dynamic/hanumachine/sheet/18.4bpp"
	gGraphicHeader_Sprite_hanumachine_18_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/18.gbapal"

gGraphicHeader_Sprite_hanumachine_19:
	.incbin "sprites/dynamic/hanumachine/sheet/19.4bpp"
	gGraphicHeader_Sprite_hanumachine_19_Palettes:
	.incbin "sprites/dynamic/hanumachine/sheet/19.gbapal"
