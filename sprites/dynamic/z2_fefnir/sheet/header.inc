@ Zero 2's Fefnir, dynamic motion 169, Zero 3's DM201_Z2_FEFNIR

.balign 4, 0

.global gGraphicHeader_Sprite_z2_fefnir
gGraphicHeader_Sprite_z2_fefnir:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_fefnir_0-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_fefnir_1-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_fefnir_2-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_fefnir_3-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_fefnir_4-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_fefnir_5-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_fefnir_6-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_fefnir_7-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_fefnir_8-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_fefnir_9-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_fefnir_10-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_fefnir_11-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_fefnir_12-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_fefnir_13-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_fefnir_14-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_fefnir_15-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_fefnir_16-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_fefnir_17-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_fefnir_18-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_fefnir_19-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_fefnir_20-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_fefnir_21-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_fefnir_22-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_fefnir_23-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_fefnir_24-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_fefnir_25-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_fefnir_26-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_fefnir_27-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_fefnir_28-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_fefnir_29-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_fefnir_30-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_fefnir_31-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_fefnir_32-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_fefnir_33-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_fefnir_34-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_fefnir_35-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_fefnir_36-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_fefnir_37-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_fefnir_38-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_fefnir_39-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_fefnir_40-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_fefnir_41-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_fefnir_42-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_fefnir_43-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_fefnir_44-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_fefnir_45-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_fefnir_46-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_fefnir_47-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_fefnir_48-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gGraphicHeader_Sprite_z2_fefnir_49-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gGraphicHeader_Sprite_z2_fefnir_50-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gGraphicHeader_Sprite_z2_fefnir_51-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gGraphicHeader_Sprite_z2_fefnir_52-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gGraphicHeader_Sprite_z2_fefnir_53-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_53_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gGraphicHeader_Sprite_z2_fefnir_54-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gGraphicHeader_Sprite_z2_fefnir_55-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gGraphicHeader_Sprite_z2_fefnir_56-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gGraphicHeader_Sprite_z2_fefnir_57-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gGraphicHeader_Sprite_z2_fefnir_58-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gGraphicHeader_Sprite_z2_fefnir_59-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gGraphicHeader_Sprite_z2_fefnir_60-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gGraphicHeader_Sprite_z2_fefnir_61-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gGraphicHeader_Sprite_z2_fefnir_62-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gGraphicHeader_Sprite_z2_fefnir_63-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gGraphicHeader_Sprite_z2_fefnir_64-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gGraphicHeader_Sprite_z2_fefnir_65-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 66
	.4byte gGraphicHeader_Sprite_z2_fefnir_66-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_66_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 67
	.4byte gGraphicHeader_Sprite_z2_fefnir_67-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_67_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 68
	.4byte gGraphicHeader_Sprite_z2_fefnir_68-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_68_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 69
	.4byte gGraphicHeader_Sprite_z2_fefnir_69-. @ src
	.4byte 1504 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_69_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 70
	.4byte gGraphicHeader_Sprite_z2_fefnir_70-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_70_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 71
	.4byte gGraphicHeader_Sprite_z2_fefnir_71-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_71_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_fefnir_0:
	.incbin "sprites/dynamic/z2_fefnir/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_0_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_fefnir_1:
	.incbin "sprites/dynamic/z2_fefnir/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_1_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_fefnir_2:
	.incbin "sprites/dynamic/z2_fefnir/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_2_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_fefnir_3:
	.incbin "sprites/dynamic/z2_fefnir/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_3_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_fefnir_4:
	.incbin "sprites/dynamic/z2_fefnir/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_4_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_fefnir_5:
	.incbin "sprites/dynamic/z2_fefnir/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_5_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_fefnir_6:
	.incbin "sprites/dynamic/z2_fefnir/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_6_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_fefnir_7:
	.incbin "sprites/dynamic/z2_fefnir/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_7_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_fefnir_8:
	.incbin "sprites/dynamic/z2_fefnir/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_8_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_fefnir_9:
	.incbin "sprites/dynamic/z2_fefnir/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_9_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_fefnir_10:
	.incbin "sprites/dynamic/z2_fefnir/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_10_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_fefnir_11:
	.incbin "sprites/dynamic/z2_fefnir/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_11_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_fefnir_12:
	.incbin "sprites/dynamic/z2_fefnir/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_12_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_fefnir_13:
	.incbin "sprites/dynamic/z2_fefnir/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_13_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_fefnir_14:
	.incbin "sprites/dynamic/z2_fefnir/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_14_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_fefnir_15:
	.incbin "sprites/dynamic/z2_fefnir/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_15_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_fefnir_16:
	.incbin "sprites/dynamic/z2_fefnir/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_16_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_fefnir_17:
	.incbin "sprites/dynamic/z2_fefnir/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_17_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_fefnir_18:
	.incbin "sprites/dynamic/z2_fefnir/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_18_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_fefnir_19:
	.incbin "sprites/dynamic/z2_fefnir/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_19_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_fefnir_20:
	.incbin "sprites/dynamic/z2_fefnir/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_20_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_fefnir_21:
	.incbin "sprites/dynamic/z2_fefnir/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_21_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_fefnir_22:
	.incbin "sprites/dynamic/z2_fefnir/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_22_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_fefnir_23:
	.incbin "sprites/dynamic/z2_fefnir/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_23_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_fefnir_24:
	.incbin "sprites/dynamic/z2_fefnir/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_24_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_fefnir_25:
	.incbin "sprites/dynamic/z2_fefnir/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_25_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_fefnir_26:
	.incbin "sprites/dynamic/z2_fefnir/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_26_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_fefnir_27:
	.incbin "sprites/dynamic/z2_fefnir/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_27_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_fefnir_28:
	.incbin "sprites/dynamic/z2_fefnir/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_28_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_fefnir_29:
	.incbin "sprites/dynamic/z2_fefnir/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_29_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_fefnir_30:
	.incbin "sprites/dynamic/z2_fefnir/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_30_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_fefnir_31:
	.incbin "sprites/dynamic/z2_fefnir/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_31_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_fefnir_32:
	.incbin "sprites/dynamic/z2_fefnir/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_32_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_fefnir_33:
	.incbin "sprites/dynamic/z2_fefnir/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_33_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_fefnir_34:
	.incbin "sprites/dynamic/z2_fefnir/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_34_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_fefnir_35:
	.incbin "sprites/dynamic/z2_fefnir/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_35_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_fefnir_36:
	.incbin "sprites/dynamic/z2_fefnir/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_36_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_fefnir_37:
	.incbin "sprites/dynamic/z2_fefnir/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_37_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_fefnir_38:
	.incbin "sprites/dynamic/z2_fefnir/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_38_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_fefnir_39:
	.incbin "sprites/dynamic/z2_fefnir/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_39_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_fefnir_40:
	.incbin "sprites/dynamic/z2_fefnir/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_40_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_fefnir_41:
	.incbin "sprites/dynamic/z2_fefnir/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_41_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_fefnir_42:
	.incbin "sprites/dynamic/z2_fefnir/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_42_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_fefnir_43:
	.incbin "sprites/dynamic/z2_fefnir/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_43_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_fefnir_44:
	.incbin "sprites/dynamic/z2_fefnir/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_44_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_fefnir_45:
	.incbin "sprites/dynamic/z2_fefnir/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_45_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_fefnir_46:
	.incbin "sprites/dynamic/z2_fefnir/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_46_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_fefnir_47:
	.incbin "sprites/dynamic/z2_fefnir/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_47_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_fefnir_48:
	.incbin "sprites/dynamic/z2_fefnir/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_48_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/48.gbapal"

gGraphicHeader_Sprite_z2_fefnir_49:
	.incbin "sprites/dynamic/z2_fefnir/sheet/49.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_49_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/49.gbapal"

gGraphicHeader_Sprite_z2_fefnir_50:
	.incbin "sprites/dynamic/z2_fefnir/sheet/50.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_50_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/50.gbapal"

gGraphicHeader_Sprite_z2_fefnir_51:
	.incbin "sprites/dynamic/z2_fefnir/sheet/51.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_51_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/51.gbapal"

gGraphicHeader_Sprite_z2_fefnir_52:
	.incbin "sprites/dynamic/z2_fefnir/sheet/52.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_52_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/52.gbapal"

gGraphicHeader_Sprite_z2_fefnir_53:
	.incbin "sprites/dynamic/z2_fefnir/sheet/53.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_53_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/53.gbapal"

gGraphicHeader_Sprite_z2_fefnir_54:
	.incbin "sprites/dynamic/z2_fefnir/sheet/54.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_54_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/54.gbapal"

gGraphicHeader_Sprite_z2_fefnir_55:
	.incbin "sprites/dynamic/z2_fefnir/sheet/55.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_55_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/55.gbapal"

gGraphicHeader_Sprite_z2_fefnir_56:
	.incbin "sprites/dynamic/z2_fefnir/sheet/56.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_56_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/56.gbapal"

gGraphicHeader_Sprite_z2_fefnir_57:
	.incbin "sprites/dynamic/z2_fefnir/sheet/57.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_57_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/57.gbapal"

gGraphicHeader_Sprite_z2_fefnir_58:
	.incbin "sprites/dynamic/z2_fefnir/sheet/58.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_58_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/58.gbapal"

gGraphicHeader_Sprite_z2_fefnir_59:
	.incbin "sprites/dynamic/z2_fefnir/sheet/59.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_59_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/59.gbapal"

gGraphicHeader_Sprite_z2_fefnir_60:
	.incbin "sprites/dynamic/z2_fefnir/sheet/60.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_60_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/60.gbapal"

gGraphicHeader_Sprite_z2_fefnir_61:
	.incbin "sprites/dynamic/z2_fefnir/sheet/61.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_61_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/61.gbapal"

gGraphicHeader_Sprite_z2_fefnir_62:
	.incbin "sprites/dynamic/z2_fefnir/sheet/62.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_62_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/62.gbapal"

gGraphicHeader_Sprite_z2_fefnir_63:
	.incbin "sprites/dynamic/z2_fefnir/sheet/63.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_63_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/63.gbapal"

gGraphicHeader_Sprite_z2_fefnir_64:
	.incbin "sprites/dynamic/z2_fefnir/sheet/64.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_64_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/64.gbapal"

gGraphicHeader_Sprite_z2_fefnir_65:
	.incbin "sprites/dynamic/z2_fefnir/sheet/65.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_65_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/65.gbapal"

gGraphicHeader_Sprite_z2_fefnir_66:
	.incbin "sprites/dynamic/z2_fefnir/sheet/66.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_66_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/66.gbapal"

gGraphicHeader_Sprite_z2_fefnir_67:
	.incbin "sprites/dynamic/z2_fefnir/sheet/67.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_67_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/67.gbapal"

gGraphicHeader_Sprite_z2_fefnir_68:
	.incbin "sprites/dynamic/z2_fefnir/sheet/68.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_68_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/68.gbapal"

gGraphicHeader_Sprite_z2_fefnir_69:
	.incbin "sprites/dynamic/z2_fefnir/sheet/69.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_69_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/69.gbapal"

gGraphicHeader_Sprite_z2_fefnir_70:
	.incbin "sprites/dynamic/z2_fefnir/sheet/70.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_70_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/70.gbapal"

gGraphicHeader_Sprite_z2_fefnir_71:
	.incbin "sprites/dynamic/z2_fefnir/sheet/71.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_71_Palettes:
	.incbin "sprites/dynamic/z2_fefnir/sheet/71.gbapal"

.global gGraphicHeader_Sprite_z2_fefnir_End
gGraphicHeader_Sprite_z2_fefnir_End:
