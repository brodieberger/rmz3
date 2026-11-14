@ Zero 2's Magnion, dynamic motion 167, Zero 3's DM209_Z2_MAGNION

.balign 4, 0

.global gGraphicHeader_Sprite_z2_magnion
gGraphicHeader_Sprite_z2_magnion:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_magnion_0-. @ src
	.4byte 4608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_magnion_1-. @ src
	.4byte 4608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_magnion_2-. @ src
	.4byte 3392 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 848, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_magnion_3-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_magnion_4-. @ src
	.4byte 4704 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_magnion_5-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_magnion_6-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_magnion_7-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_magnion_8-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_magnion_9-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_magnion_10-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_magnion_11-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_magnion_12-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_magnion_13-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_magnion_14-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_magnion_15-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_magnion_16-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_magnion_17-. @ src
	.4byte 4064 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1016, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_magnion_18-. @ src
	.4byte 4544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_magnion_19-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_magnion_20-. @ src
	.4byte 4128 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1032, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_magnion_21-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_magnion_22-. @ src
	.4byte 3328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_magnion_23-. @ src
	.4byte 4480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_magnion_24-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_magnion_25-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_magnion_26-. @ src
	.4byte 4000 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1000, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_magnion_27-. @ src
	.4byte 2752 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 688, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_magnion_28-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_magnion_29-. @ src
	.4byte 4736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_magnion_30-. @ src
	.4byte 4864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_magnion_31-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_magnion_32-. @ src
	.4byte 4256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1064, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_magnion_33-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_magnion_34-. @ src
	.4byte 4224 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1056, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_magnion_35-. @ src
	.4byte 3424 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 856, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_magnion_36-. @ src
	.4byte 4608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_magnion_37-. @ src
	.4byte 4032 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1008, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_magnion_38-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_magnion_39-. @ src
	.4byte 4480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_magnion_40-. @ src
	.4byte 4640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_magnion_41-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_magnion_42-. @ src
	.4byte 2304 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 576, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_magnion_43-. @ src
	.4byte 2976 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 744, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_magnion_44-. @ src
	.4byte 2816 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 704, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_magnion_45-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_magnion_46-. @ src
	.4byte 4416 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1104, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_magnion_47-. @ src
	.4byte 3200 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 800, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_magnion_48-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gGraphicHeader_Sprite_z2_magnion_49-. @ src
	.4byte 4608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gGraphicHeader_Sprite_z2_magnion_50-. @ src
	.4byte 3584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gGraphicHeader_Sprite_z2_magnion_51-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gGraphicHeader_Sprite_z2_magnion_52-. @ src
	.4byte 4544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gGraphicHeader_Sprite_z2_magnion_53-. @ src
	.4byte 4192 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1048, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_53_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gGraphicHeader_Sprite_z2_magnion_54-. @ src
	.4byte 2880 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 720, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gGraphicHeader_Sprite_z2_magnion_55-. @ src
	.4byte 2464 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 616, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gGraphicHeader_Sprite_z2_magnion_56-. @ src
	.4byte 3488 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 872, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gGraphicHeader_Sprite_z2_magnion_57-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gGraphicHeader_Sprite_z2_magnion_58-. @ src
	.4byte 4608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gGraphicHeader_Sprite_z2_magnion_59-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gGraphicHeader_Sprite_z2_magnion_60-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gGraphicHeader_Sprite_z2_magnion_61-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gGraphicHeader_Sprite_z2_magnion_62-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gGraphicHeader_Sprite_z2_magnion_63-. @ src
	.4byte 4864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gGraphicHeader_Sprite_z2_magnion_64-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gGraphicHeader_Sprite_z2_magnion_65-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 66
	.4byte gGraphicHeader_Sprite_z2_magnion_66-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_66_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 67
	.4byte gGraphicHeader_Sprite_z2_magnion_67-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_67_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 68
	.4byte gGraphicHeader_Sprite_z2_magnion_68-. @ src
	.4byte 32 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_68_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 69
	.4byte gGraphicHeader_Sprite_z2_magnion_69-. @ src
	.4byte 4544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_69_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 70
	.4byte gGraphicHeader_Sprite_z2_magnion_70-. @ src
	.4byte 4736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_70_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 71
	.4byte gGraphicHeader_Sprite_z2_magnion_71-. @ src
	.4byte 4864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_magnion_71_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_magnion_0:
	.incbin "sprites/dynamic/z2_magnion/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_magnion_0_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_magnion_1:
	.incbin "sprites/dynamic/z2_magnion/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_magnion_1_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_magnion_2:
	.incbin "sprites/dynamic/z2_magnion/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_magnion_2_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_magnion_3:
	.incbin "sprites/dynamic/z2_magnion/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_magnion_3_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_magnion_4:
	.incbin "sprites/dynamic/z2_magnion/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_magnion_4_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_magnion_5:
	.incbin "sprites/dynamic/z2_magnion/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_magnion_5_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_magnion_6:
	.incbin "sprites/dynamic/z2_magnion/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_magnion_6_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_magnion_7:
	.incbin "sprites/dynamic/z2_magnion/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_magnion_7_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_magnion_8:
	.incbin "sprites/dynamic/z2_magnion/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_magnion_8_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_magnion_9:
	.incbin "sprites/dynamic/z2_magnion/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_magnion_9_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_magnion_10:
	.incbin "sprites/dynamic/z2_magnion/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_magnion_10_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_magnion_11:
	.incbin "sprites/dynamic/z2_magnion/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_magnion_11_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_magnion_12:
	.incbin "sprites/dynamic/z2_magnion/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_magnion_12_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_magnion_13:
	.incbin "sprites/dynamic/z2_magnion/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_magnion_13_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_magnion_14:
	.incbin "sprites/dynamic/z2_magnion/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_magnion_14_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_magnion_15:
	.incbin "sprites/dynamic/z2_magnion/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_magnion_15_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_magnion_16:
	.incbin "sprites/dynamic/z2_magnion/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_magnion_16_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_magnion_17:
	.incbin "sprites/dynamic/z2_magnion/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_magnion_17_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_magnion_18:
	.incbin "sprites/dynamic/z2_magnion/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_magnion_18_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_magnion_19:
	.incbin "sprites/dynamic/z2_magnion/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_magnion_19_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_magnion_20:
	.incbin "sprites/dynamic/z2_magnion/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_magnion_20_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_magnion_21:
	.incbin "sprites/dynamic/z2_magnion/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_magnion_21_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_magnion_22:
	.incbin "sprites/dynamic/z2_magnion/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_magnion_22_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_magnion_23:
	.incbin "sprites/dynamic/z2_magnion/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_magnion_23_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_magnion_24:
	.incbin "sprites/dynamic/z2_magnion/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_magnion_24_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_magnion_25:
	.incbin "sprites/dynamic/z2_magnion/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_magnion_25_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_magnion_26:
	.incbin "sprites/dynamic/z2_magnion/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_magnion_26_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_magnion_27:
	.incbin "sprites/dynamic/z2_magnion/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_magnion_27_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_magnion_28:
	.incbin "sprites/dynamic/z2_magnion/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_magnion_28_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_magnion_29:
	.incbin "sprites/dynamic/z2_magnion/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_magnion_29_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_magnion_30:
	.incbin "sprites/dynamic/z2_magnion/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_magnion_30_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_magnion_31:
	.incbin "sprites/dynamic/z2_magnion/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_magnion_31_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_magnion_32:
	.incbin "sprites/dynamic/z2_magnion/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_magnion_32_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_magnion_33:
	.incbin "sprites/dynamic/z2_magnion/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_magnion_33_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_magnion_34:
	.incbin "sprites/dynamic/z2_magnion/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_magnion_34_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_magnion_35:
	.incbin "sprites/dynamic/z2_magnion/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_magnion_35_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_magnion_36:
	.incbin "sprites/dynamic/z2_magnion/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_magnion_36_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_magnion_37:
	.incbin "sprites/dynamic/z2_magnion/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_magnion_37_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_magnion_38:
	.incbin "sprites/dynamic/z2_magnion/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_magnion_38_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_magnion_39:
	.incbin "sprites/dynamic/z2_magnion/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_magnion_39_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_magnion_40:
	.incbin "sprites/dynamic/z2_magnion/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_magnion_40_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_magnion_41:
	.incbin "sprites/dynamic/z2_magnion/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_magnion_41_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_magnion_42:
	.incbin "sprites/dynamic/z2_magnion/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_magnion_42_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_magnion_43:
	.incbin "sprites/dynamic/z2_magnion/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_magnion_43_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_magnion_44:
	.incbin "sprites/dynamic/z2_magnion/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_magnion_44_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_magnion_45:
	.incbin "sprites/dynamic/z2_magnion/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_magnion_45_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_magnion_46:
	.incbin "sprites/dynamic/z2_magnion/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_magnion_46_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_magnion_47:
	.incbin "sprites/dynamic/z2_magnion/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_magnion_47_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_magnion_48:
	.incbin "sprites/dynamic/z2_magnion/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_magnion_48_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/48.gbapal"

gGraphicHeader_Sprite_z2_magnion_49:
	.incbin "sprites/dynamic/z2_magnion/sheet/49.4bpp"
	gGraphicHeader_Sprite_z2_magnion_49_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/49.gbapal"

gGraphicHeader_Sprite_z2_magnion_50:
	.incbin "sprites/dynamic/z2_magnion/sheet/50.4bpp"
	gGraphicHeader_Sprite_z2_magnion_50_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/50.gbapal"

gGraphicHeader_Sprite_z2_magnion_51:
	.incbin "sprites/dynamic/z2_magnion/sheet/51.4bpp"
	gGraphicHeader_Sprite_z2_magnion_51_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/51.gbapal"

gGraphicHeader_Sprite_z2_magnion_52:
	.incbin "sprites/dynamic/z2_magnion/sheet/52.4bpp"
	gGraphicHeader_Sprite_z2_magnion_52_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/52.gbapal"

gGraphicHeader_Sprite_z2_magnion_53:
	.incbin "sprites/dynamic/z2_magnion/sheet/53.4bpp"
	gGraphicHeader_Sprite_z2_magnion_53_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/53.gbapal"

gGraphicHeader_Sprite_z2_magnion_54:
	.incbin "sprites/dynamic/z2_magnion/sheet/54.4bpp"
	gGraphicHeader_Sprite_z2_magnion_54_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/54.gbapal"

gGraphicHeader_Sprite_z2_magnion_55:
	.incbin "sprites/dynamic/z2_magnion/sheet/55.4bpp"
	gGraphicHeader_Sprite_z2_magnion_55_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/55.gbapal"

gGraphicHeader_Sprite_z2_magnion_56:
	.incbin "sprites/dynamic/z2_magnion/sheet/56.4bpp"
	gGraphicHeader_Sprite_z2_magnion_56_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/56.gbapal"

gGraphicHeader_Sprite_z2_magnion_57:
	.incbin "sprites/dynamic/z2_magnion/sheet/57.4bpp"
	gGraphicHeader_Sprite_z2_magnion_57_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/57.gbapal"

gGraphicHeader_Sprite_z2_magnion_58:
	.incbin "sprites/dynamic/z2_magnion/sheet/58.4bpp"
	gGraphicHeader_Sprite_z2_magnion_58_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/58.gbapal"

gGraphicHeader_Sprite_z2_magnion_59:
	.incbin "sprites/dynamic/z2_magnion/sheet/59.4bpp"
	gGraphicHeader_Sprite_z2_magnion_59_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/59.gbapal"

gGraphicHeader_Sprite_z2_magnion_60:
	.incbin "sprites/dynamic/z2_magnion/sheet/60.4bpp"
	gGraphicHeader_Sprite_z2_magnion_60_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/60.gbapal"

gGraphicHeader_Sprite_z2_magnion_61:
	.incbin "sprites/dynamic/z2_magnion/sheet/61.4bpp"
	gGraphicHeader_Sprite_z2_magnion_61_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/61.gbapal"

gGraphicHeader_Sprite_z2_magnion_62:
	.incbin "sprites/dynamic/z2_magnion/sheet/62.4bpp"
	gGraphicHeader_Sprite_z2_magnion_62_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/62.gbapal"

gGraphicHeader_Sprite_z2_magnion_63:
	.incbin "sprites/dynamic/z2_magnion/sheet/63.4bpp"
	gGraphicHeader_Sprite_z2_magnion_63_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/63.gbapal"

gGraphicHeader_Sprite_z2_magnion_64:
	.incbin "sprites/dynamic/z2_magnion/sheet/64.4bpp"
	gGraphicHeader_Sprite_z2_magnion_64_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/64.gbapal"

gGraphicHeader_Sprite_z2_magnion_65:
	.incbin "sprites/dynamic/z2_magnion/sheet/65.4bpp"
	gGraphicHeader_Sprite_z2_magnion_65_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/65.gbapal"

gGraphicHeader_Sprite_z2_magnion_66:
	.incbin "sprites/dynamic/z2_magnion/sheet/66.4bpp"
	gGraphicHeader_Sprite_z2_magnion_66_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/66.gbapal"

gGraphicHeader_Sprite_z2_magnion_67:
	.incbin "sprites/dynamic/z2_magnion/sheet/67.4bpp"
	gGraphicHeader_Sprite_z2_magnion_67_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/67.gbapal"

gGraphicHeader_Sprite_z2_magnion_68:
	.incbin "sprites/dynamic/z2_magnion/sheet/68.4bpp"
	gGraphicHeader_Sprite_z2_magnion_68_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/68.gbapal"

gGraphicHeader_Sprite_z2_magnion_69:
	.incbin "sprites/dynamic/z2_magnion/sheet/69.4bpp"
	gGraphicHeader_Sprite_z2_magnion_69_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/69.gbapal"

gGraphicHeader_Sprite_z2_magnion_70:
	.incbin "sprites/dynamic/z2_magnion/sheet/70.4bpp"
	gGraphicHeader_Sprite_z2_magnion_70_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/70.gbapal"

gGraphicHeader_Sprite_z2_magnion_71:
	.incbin "sprites/dynamic/z2_magnion/sheet/71.4bpp"
	gGraphicHeader_Sprite_z2_magnion_71_Palettes:
	.incbin "sprites/dynamic/z2_magnion/sheet/71.gbapal"

.global gGraphicHeader_Sprite_z2_magnion_End
gGraphicHeader_Sprite_z2_magnion_End:
