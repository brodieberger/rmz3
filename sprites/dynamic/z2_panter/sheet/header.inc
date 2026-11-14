@ Zero 2's Panter, dynamic motion 163, Zero 3's DM208_Z2_PANTER

.balign 4, 0

.global gGraphicHeader_Sprite_z2_panter
gGraphicHeader_Sprite_z2_panter:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_panter_0-. @ src
	.4byte 3328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_panter_1-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_panter_2-. @ src
	.4byte 3296 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 824, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_panter_3-. @ src
	.4byte 2880 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 720, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_panter_4-. @ src
	.4byte 3296 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 824, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_panter_5-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_panter_6-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_panter_7-. @ src
	.4byte 3616 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 904, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_panter_8-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_panter_9-. @ src
	.4byte 2720 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 680, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_panter_10-. @ src
	.4byte 3456 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 864, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_panter_11-. @ src
	.4byte 2336 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 584, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_panter_12-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_panter_13-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_panter_14-. @ src
	.4byte 2944 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 736, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_panter_15-. @ src
	.4byte 2752 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 688, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_panter_16-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_panter_17-. @ src
	.4byte 3616 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 904, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_panter_18-. @ src
	.4byte 2368 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 592, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_panter_19-. @ src
	.4byte 2592 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 648, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_panter_20-. @ src
	.4byte 2816 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 704, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_panter_21-. @ src
	.4byte 2496 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 624, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_panter_22-. @ src
	.4byte 2560 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 640, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_panter_23-. @ src
	.4byte 2624 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 656, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_panter_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_panter_0:
	.incbin "sprites/dynamic/z2_panter/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_panter_0_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_panter_1:
	.incbin "sprites/dynamic/z2_panter/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_panter_1_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_panter_2:
	.incbin "sprites/dynamic/z2_panter/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_panter_2_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_panter_3:
	.incbin "sprites/dynamic/z2_panter/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_panter_3_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_panter_4:
	.incbin "sprites/dynamic/z2_panter/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_panter_4_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_panter_5:
	.incbin "sprites/dynamic/z2_panter/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_panter_5_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_panter_6:
	.incbin "sprites/dynamic/z2_panter/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_panter_6_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_panter_7:
	.incbin "sprites/dynamic/z2_panter/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_panter_7_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_panter_8:
	.incbin "sprites/dynamic/z2_panter/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_panter_8_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_panter_9:
	.incbin "sprites/dynamic/z2_panter/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_panter_9_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_panter_10:
	.incbin "sprites/dynamic/z2_panter/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_panter_10_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_panter_11:
	.incbin "sprites/dynamic/z2_panter/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_panter_11_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_panter_12:
	.incbin "sprites/dynamic/z2_panter/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_panter_12_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_panter_13:
	.incbin "sprites/dynamic/z2_panter/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_panter_13_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_panter_14:
	.incbin "sprites/dynamic/z2_panter/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_panter_14_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_panter_15:
	.incbin "sprites/dynamic/z2_panter/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_panter_15_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_panter_16:
	.incbin "sprites/dynamic/z2_panter/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_panter_16_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_panter_17:
	.incbin "sprites/dynamic/z2_panter/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_panter_17_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_panter_18:
	.incbin "sprites/dynamic/z2_panter/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_panter_18_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_panter_19:
	.incbin "sprites/dynamic/z2_panter/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_panter_19_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_panter_20:
	.incbin "sprites/dynamic/z2_panter/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_panter_20_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_panter_21:
	.incbin "sprites/dynamic/z2_panter/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_panter_21_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_panter_22:
	.incbin "sprites/dynamic/z2_panter/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_panter_22_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_panter_23:
	.incbin "sprites/dynamic/z2_panter/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_panter_23_Palettes:
	.incbin "sprites/dynamic/z2_panter/sheet/23.gbapal"

.global gGraphicHeader_Sprite_z2_panter_End
gGraphicHeader_Sprite_z2_panter_End:
