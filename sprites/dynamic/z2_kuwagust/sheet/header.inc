@ Zero 2's Kuwagust, dynamic motion 165, Zero 3's DM213_Z2_KUWAGUST

.balign 4, 0

.global gGraphicHeader_Sprite_z2_kuwagust
gGraphicHeader_Sprite_z2_kuwagust:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_kuwagust_0-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_kuwagust_1-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_kuwagust_2-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_kuwagust_3-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_kuwagust_4-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_kuwagust_5-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_kuwagust_6-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_kuwagust_7-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_kuwagust_8-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_kuwagust_9-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_kuwagust_10-. @ src
	.4byte 1856 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_kuwagust_11-. @ src
	.4byte 1856 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 464, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_kuwagust_12-. @ src
	.4byte 1952 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 488, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_kuwagust_13-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_kuwagust_14-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_kuwagust_15-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_kuwagust_16-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_kuwagust_17-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_kuwagust_18-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_kuwagust_19-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_kuwagust_20-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_kuwagust_21-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_kuwagust_22-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_kuwagust_23-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_kuwagust_24-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_kuwagust_25-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_kuwagust_26-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_kuwagust_27-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_kuwagust_28-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_kuwagust_29-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_kuwagust_30-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_kuwagust_31-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_kuwagust_32-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_kuwagust_33-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_kuwagust_34-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_kuwagust_35-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_kuwagust_36-. @ src
	.4byte 1952 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 488, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_kuwagust_37-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_kuwagust_38-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_kuwagust_39-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_kuwagust_40-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_kuwagust_41-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_kuwagust_42-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_kuwagust_43-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_kuwagust_44-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_kuwagust_45-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_kuwagust_46-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_kuwagust_47-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_kuwagust_48-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gGraphicHeader_Sprite_z2_kuwagust_49-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gGraphicHeader_Sprite_z2_kuwagust_50-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gGraphicHeader_Sprite_z2_kuwagust_51-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gGraphicHeader_Sprite_z2_kuwagust_52-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gGraphicHeader_Sprite_z2_kuwagust_53-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_53_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gGraphicHeader_Sprite_z2_kuwagust_54-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gGraphicHeader_Sprite_z2_kuwagust_55-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gGraphicHeader_Sprite_z2_kuwagust_56-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gGraphicHeader_Sprite_z2_kuwagust_57-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gGraphicHeader_Sprite_z2_kuwagust_58-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gGraphicHeader_Sprite_z2_kuwagust_59-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gGraphicHeader_Sprite_z2_kuwagust_60-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gGraphicHeader_Sprite_z2_kuwagust_61-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gGraphicHeader_Sprite_z2_kuwagust_62-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gGraphicHeader_Sprite_z2_kuwagust_63-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gGraphicHeader_Sprite_z2_kuwagust_64-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gGraphicHeader_Sprite_z2_kuwagust_65-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 66
	.4byte gGraphicHeader_Sprite_z2_kuwagust_66-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_66_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 67
	.4byte gGraphicHeader_Sprite_z2_kuwagust_67-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_67_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 68
	.4byte gGraphicHeader_Sprite_z2_kuwagust_68-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_68_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 69
	.4byte gGraphicHeader_Sprite_z2_kuwagust_69-. @ src
	.4byte 1312 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_69_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 70
	.4byte gGraphicHeader_Sprite_z2_kuwagust_70-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_70_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 71
	.4byte gGraphicHeader_Sprite_z2_kuwagust_71-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_71_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 72
	.4byte gGraphicHeader_Sprite_z2_kuwagust_72-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_72_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 73
	.4byte gGraphicHeader_Sprite_z2_kuwagust_73-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_73_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 74
	.4byte gGraphicHeader_Sprite_z2_kuwagust_74-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_74_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 75
	.4byte gGraphicHeader_Sprite_z2_kuwagust_75-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_75_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 76
	.4byte gGraphicHeader_Sprite_z2_kuwagust_76-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_76_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 77
	.4byte gGraphicHeader_Sprite_z2_kuwagust_77-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_77_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 78
	.4byte gGraphicHeader_Sprite_z2_kuwagust_78-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_78_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 79
	.4byte gGraphicHeader_Sprite_z2_kuwagust_79-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_79_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 80
	.4byte gGraphicHeader_Sprite_z2_kuwagust_80-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_80_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 81
	.4byte gGraphicHeader_Sprite_z2_kuwagust_81-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_81_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 82
	.4byte gGraphicHeader_Sprite_z2_kuwagust_82-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_82_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 83
	.4byte gGraphicHeader_Sprite_z2_kuwagust_83-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_83_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 84
	.4byte gGraphicHeader_Sprite_z2_kuwagust_84-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_84_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 85
	.4byte gGraphicHeader_Sprite_z2_kuwagust_85-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_85_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 86
	.4byte gGraphicHeader_Sprite_z2_kuwagust_86-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_86_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 87
	.4byte gGraphicHeader_Sprite_z2_kuwagust_87-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_87_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 88
	.4byte gGraphicHeader_Sprite_z2_kuwagust_88-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_88_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 89
	.4byte gGraphicHeader_Sprite_z2_kuwagust_89-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_89_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 90
	.4byte gGraphicHeader_Sprite_z2_kuwagust_90-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_90_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 91
	.4byte gGraphicHeader_Sprite_z2_kuwagust_91-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_91_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 92
	.4byte gGraphicHeader_Sprite_z2_kuwagust_92-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_92_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 93
	.4byte gGraphicHeader_Sprite_z2_kuwagust_93-. @ src
	.4byte 256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_93_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 94
	.4byte gGraphicHeader_Sprite_z2_kuwagust_94-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_94_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 95
	.4byte gGraphicHeader_Sprite_z2_kuwagust_95-. @ src
	.4byte 416 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 104, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_95_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 96
	.4byte gGraphicHeader_Sprite_z2_kuwagust_96-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_96_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 97
	.4byte gGraphicHeader_Sprite_z2_kuwagust_97-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_97_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 98
	.4byte gGraphicHeader_Sprite_z2_kuwagust_98-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_98_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 99
	.4byte gGraphicHeader_Sprite_z2_kuwagust_99-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_99_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 100
	.4byte gGraphicHeader_Sprite_z2_kuwagust_100-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_100_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 101
	.4byte gGraphicHeader_Sprite_z2_kuwagust_101-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_101_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 102
	.4byte gGraphicHeader_Sprite_z2_kuwagust_102-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_102_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 103
	.4byte gGraphicHeader_Sprite_z2_kuwagust_103-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_103_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 104
	.4byte gGraphicHeader_Sprite_z2_kuwagust_104-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_104_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 105
	.4byte gGraphicHeader_Sprite_z2_kuwagust_105-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_105_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 106
	.4byte gGraphicHeader_Sprite_z2_kuwagust_106-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_kuwagust_106_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_kuwagust_0:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_0_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_1:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_1_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_2:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_2_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_3:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_3_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_4:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_4_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_5:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_5_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_6:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_6_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_7:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_7_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_8:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_8_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_9:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_9_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_10:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_10_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_11:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_11_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_12:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_12_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_13:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_13_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_14:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_14_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_15:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_15_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_16:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_16_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_17:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_17_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_18:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_18_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_19:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_19_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_20:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_20_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_21:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_21_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_22:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_22_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_23:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_23_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_24:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_24_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_25:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_25_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_26:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_26_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_27:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_27_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_28:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_28_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_29:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_29_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_30:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_30_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_31:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_31_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_32:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_32_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_33:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_33_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_34:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_34_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_35:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_35_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_36:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_36_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_37:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_37_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_38:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_38_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_39:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_39_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_40:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_40_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_41:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_41_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_42:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_42_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_43:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_43_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_44:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_44_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_45:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_45_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_46:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_46_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_47:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_47_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_48:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_48_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/48.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_49:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/49.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_49_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/49.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_50:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/50.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_50_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/50.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_51:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/51.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_51_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/51.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_52:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/52.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_52_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/52.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_53:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/53.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_53_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/53.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_54:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/54.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_54_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/54.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_55:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/55.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_55_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/55.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_56:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/56.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_56_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/56.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_57:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/57.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_57_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/57.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_58:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/58.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_58_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/58.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_59:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/59.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_59_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/59.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_60:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/60.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_60_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/60.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_61:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/61.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_61_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/61.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_62:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/62.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_62_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/62.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_63:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/63.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_63_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/63.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_64:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/64.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_64_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/64.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_65:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/65.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_65_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/65.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_66:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/66.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_66_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/66.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_67:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/67.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_67_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/67.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_68:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/68.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_68_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/68.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_69:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/69.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_69_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/69.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_70:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/70.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_70_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/70.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_71:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/71.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_71_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/71.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_72:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/72.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_72_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/72.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_73:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/73.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_73_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/73.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_74:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/74.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_74_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/74.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_75:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/75.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_75_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/75.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_76:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/76.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_76_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/76.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_77:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/77.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_77_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/77.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_78:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/78.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_78_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/78.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_79:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/79.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_79_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/79.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_80:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/80.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_80_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/80.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_81:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/81.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_81_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/81.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_82:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/82.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_82_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/82.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_83:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/83.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_83_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/83.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_84:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/84.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_84_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/84.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_85:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/85.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_85_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/85.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_86:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/86.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_86_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/86.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_87:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/87.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_87_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/87.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_88:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/88.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_88_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/88.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_89:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/89.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_89_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/89.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_90:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/90.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_90_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/90.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_91:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/91.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_91_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/91.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_92:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/92.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_92_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/92.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_93:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/93.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_93_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/93.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_94:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/94.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_94_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/94.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_95:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/95.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_95_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/95.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_96:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/96.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_96_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/96.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_97:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/97.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_97_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/97.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_98:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/98.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_98_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/98.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_99:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/99.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_99_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/99.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_100:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/100.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_100_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/100.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_101:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/101.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_101_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/101.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_102:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/102.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_102_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/102.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_103:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/103.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_103_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/103.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_104:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/104.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_104_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/104.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_105:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/105.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_105_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/105.gbapal"

gGraphicHeader_Sprite_z2_kuwagust_106:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/106.4bpp"
	gGraphicHeader_Sprite_z2_kuwagust_106_Palettes:
	.incbin "sprites/dynamic/z2_kuwagust/sheet/106.gbapal"

.global gGraphicHeader_Sprite_z2_kuwagust_End
gGraphicHeader_Sprite_z2_kuwagust_End:
