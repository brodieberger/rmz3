@ Zero 2's Elpizo_boss, dynamic motion 173, Zero 3's DM216_Z2_ELPIZO_BOSS

.balign 4, 0

.global gGraphicHeader_Sprite_z2_elpizo_boss
gGraphicHeader_Sprite_z2_elpizo_boss:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_0-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_1-. @ src
	.4byte 800 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_2-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_3-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_4-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_5-. @ src
	.4byte 608 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_6-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_7-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_8-. @ src
	.4byte 640 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_9-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_10-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_11-. @ src
	.4byte 576 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_12-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_13-. @ src
	.4byte 768 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_14-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_15-. @ src
	.4byte 768 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_16-. @ src
	.4byte 864 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_17-. @ src
	.4byte 768 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_18-. @ src
	.4byte 800 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_19-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_20-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_21-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_22-. @ src
	.4byte 896 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_23-. @ src
	.4byte 992 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_24-. @ src
	.4byte 768 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_25-. @ src
	.4byte 832 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_26-. @ src
	.4byte 832 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_27-. @ src
	.4byte 896 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_28-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_29-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_30-. @ src
	.4byte 640 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_31-. @ src
	.4byte 576 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_32-. @ src
	.4byte 640 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_33-. @ src
	.4byte 576 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_34-. @ src
	.4byte 608 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_35-. @ src
	.4byte 1344 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_36-. @ src
	.4byte 992 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_37-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_38-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_39-. @ src
	.4byte 800 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_40-. @ src
	.4byte 832 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_41-. @ src
	.4byte 768 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_42-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_43-. @ src
	.4byte 736 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_44-. @ src
	.4byte 704 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_45-. @ src
	.4byte 992 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_46-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_47-. @ src
	.4byte 512 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_48-. @ src
	.4byte 544 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_49-. @ src
	.4byte 544 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gGraphicHeader_Sprite_z2_elpizo_boss_50-. @ src
	.4byte 672 | (776 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_boss_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_elpizo_boss_0:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_0_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_1:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_1_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_2:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_2_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_3:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_3_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_4:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_4_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_5:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_5_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_6:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_6_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_7:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_7_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_8:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_8_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_9:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_9_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_10:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_10_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_11:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_11_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_12:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_12_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_13:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_13_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_14:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_14_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_15:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_15_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_16:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_16_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_17:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_17_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_18:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_18_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_19:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_19_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_20:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_20_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_21:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_21_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_22:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_22_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_23:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_23_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_24:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_24_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_25:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_25_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_26:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_26_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_27:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_27_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_28:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_28_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_29:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_29_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_30:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_30_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_31:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_31_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_32:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_32_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_33:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_33_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_34:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_34_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_35:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_35_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_36:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_36_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_37:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_37_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_38:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_38_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_39:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_39_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_40:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_40_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_41:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_41_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_42:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_42_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_43:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_43_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_44:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_44_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_45:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_45_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_46:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_46_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_47:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_47_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_48:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_48_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/48.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_49:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/49.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_49_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/49.gbapal"

gGraphicHeader_Sprite_z2_elpizo_boss_50:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/50.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_boss_50_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_boss/sheet/50.gbapal"

.global gGraphicHeader_Sprite_z2_elpizo_boss_End
gGraphicHeader_Sprite_z2_elpizo_boss_End:
