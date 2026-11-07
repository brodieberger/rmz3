@ Zero 2's Blob, dynamic motion 164, Zero 3's DM204_Z2_BLOB

.balign 4, 0

.global gGraphicHeader_Sprite_z2_blob
gGraphicHeader_Sprite_z2_blob:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_blob_0-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_blob_1-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_blob_2-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_blob_3-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_blob_4-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_blob_5-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_blob_6-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_blob_7-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_blob_8-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_blob_9-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_blob_10-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_blob_11-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_blob_12-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_blob_13-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_blob_14-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_blob_15-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_blob_16-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_blob_17-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_blob_18-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_blob_19-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_blob_20-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_blob_21-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_blob_22-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_blob_23-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_blob_24-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_blob_25-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_blob_26-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_blob_27-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_blob_28-. @ src
	.4byte 1312 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_blob_29-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_blob_30-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_blob_31-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_blob_32-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_blob_33-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_blob_34-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_blob_35-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_blob_36-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_blob_37-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_blob_38-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_blob_39-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_blob_40-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_blob_41-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_blob_42-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_blob_43-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_blob_44-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_blob_45-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_blob_46-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_blob_47-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_blob_48-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gGraphicHeader_Sprite_z2_blob_49-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gGraphicHeader_Sprite_z2_blob_50-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gGraphicHeader_Sprite_z2_blob_51-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gGraphicHeader_Sprite_z2_blob_52-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gGraphicHeader_Sprite_z2_blob_53-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_53_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gGraphicHeader_Sprite_z2_blob_54-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gGraphicHeader_Sprite_z2_blob_55-. @ src
	.4byte 2272 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 568, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gGraphicHeader_Sprite_z2_blob_56-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gGraphicHeader_Sprite_z2_blob_57-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gGraphicHeader_Sprite_z2_blob_58-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gGraphicHeader_Sprite_z2_blob_59-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gGraphicHeader_Sprite_z2_blob_60-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gGraphicHeader_Sprite_z2_blob_61-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gGraphicHeader_Sprite_z2_blob_62-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gGraphicHeader_Sprite_z2_blob_63-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gGraphicHeader_Sprite_z2_blob_64-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gGraphicHeader_Sprite_z2_blob_65-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 66
	.4byte gGraphicHeader_Sprite_z2_blob_66-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_66_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 67
	.4byte gGraphicHeader_Sprite_z2_blob_67-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_67_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 68
	.4byte gGraphicHeader_Sprite_z2_blob_68-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_68_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 69
	.4byte gGraphicHeader_Sprite_z2_blob_69-. @ src
	.4byte 896 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_69_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 70
	.4byte gGraphicHeader_Sprite_z2_blob_70-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_70_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 71
	.4byte gGraphicHeader_Sprite_z2_blob_71-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_71_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 72
	.4byte gGraphicHeader_Sprite_z2_blob_72-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_72_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 73
	.4byte gGraphicHeader_Sprite_z2_blob_73-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_73_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 74
	.4byte gGraphicHeader_Sprite_z2_blob_74-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_74_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 75
	.4byte gGraphicHeader_Sprite_z2_blob_75-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_75_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 76
	.4byte gGraphicHeader_Sprite_z2_blob_76-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_76_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 77
	.4byte gGraphicHeader_Sprite_z2_blob_77-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_77_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 78
	.4byte gGraphicHeader_Sprite_z2_blob_78-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_78_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 79
	.4byte gGraphicHeader_Sprite_z2_blob_79-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_79_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 80
	.4byte gGraphicHeader_Sprite_z2_blob_80-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_80_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 81
	.4byte gGraphicHeader_Sprite_z2_blob_81-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_81_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 82
	.4byte gGraphicHeader_Sprite_z2_blob_82-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_82_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 83
	.4byte gGraphicHeader_Sprite_z2_blob_83-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_83_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 84
	.4byte gGraphicHeader_Sprite_z2_blob_84-. @ src
	.4byte 2240 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 560, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_84_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 85
	.4byte gGraphicHeader_Sprite_z2_blob_85-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_85_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 86
	.4byte gGraphicHeader_Sprite_z2_blob_86-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_86_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 87
	.4byte gGraphicHeader_Sprite_z2_blob_87-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_87_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 88
	.4byte gGraphicHeader_Sprite_z2_blob_88-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_88_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 89
	.4byte gGraphicHeader_Sprite_z2_blob_89-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_89_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 90
	.4byte gGraphicHeader_Sprite_z2_blob_90-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_90_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 91
	.4byte gGraphicHeader_Sprite_z2_blob_91-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_91_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 92
	.4byte gGraphicHeader_Sprite_z2_blob_92-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_92_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 93
	.4byte gGraphicHeader_Sprite_z2_blob_93-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_93_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 94
	.4byte gGraphicHeader_Sprite_z2_blob_94-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_94_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 95
	.4byte gGraphicHeader_Sprite_z2_blob_95-. @ src
	.4byte 1504 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_95_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 96
	.4byte gGraphicHeader_Sprite_z2_blob_96-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_96_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 97
	.4byte gGraphicHeader_Sprite_z2_blob_97-. @ src
	.4byte 1248 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_97_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 98
	.4byte gGraphicHeader_Sprite_z2_blob_98-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_98_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 99
	.4byte gGraphicHeader_Sprite_z2_blob_99-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_99_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 100
	.4byte gGraphicHeader_Sprite_z2_blob_100-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_100_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 101
	.4byte gGraphicHeader_Sprite_z2_blob_101-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_101_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 102
	.4byte gGraphicHeader_Sprite_z2_blob_102-. @ src
	.4byte 1376 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_102_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 103
	.4byte gGraphicHeader_Sprite_z2_blob_103-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_103_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 104
	.4byte gGraphicHeader_Sprite_z2_blob_104-. @ src
	.4byte 480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_104_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 105
	.4byte gGraphicHeader_Sprite_z2_blob_105-. @ src
	.4byte 480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_105_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 106
	.4byte gGraphicHeader_Sprite_z2_blob_106-. @ src
	.4byte 544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_106_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 107
	.4byte gGraphicHeader_Sprite_z2_blob_107-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_107_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 108
	.4byte gGraphicHeader_Sprite_z2_blob_108-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_108_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 109
	.4byte gGraphicHeader_Sprite_z2_blob_109-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_109_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 110
	.4byte gGraphicHeader_Sprite_z2_blob_110-. @ src
	.4byte 2304 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 576, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_110_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 111
	.4byte gGraphicHeader_Sprite_z2_blob_111-. @ src
	.4byte 1824 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 456, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_111_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 112
	.4byte gGraphicHeader_Sprite_z2_blob_112-. @ src
	.4byte 2208 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_112_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 113
	.4byte gGraphicHeader_Sprite_z2_blob_113-. @ src
	.4byte 2176 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 544, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_113_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 114
	.4byte gGraphicHeader_Sprite_z2_blob_114-. @ src
	.4byte 2176 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 544, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_114_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 115
	.4byte gGraphicHeader_Sprite_z2_blob_115-. @ src
	.4byte 1952 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 488, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_115_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 116
	.4byte gGraphicHeader_Sprite_z2_blob_116-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_116_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 117
	.4byte gGraphicHeader_Sprite_z2_blob_117-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_117_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 118
	.4byte gGraphicHeader_Sprite_z2_blob_118-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_118_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 119
	.4byte gGraphicHeader_Sprite_z2_blob_119-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_119_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 120
	.4byte gGraphicHeader_Sprite_z2_blob_120-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_120_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 121
	.4byte gGraphicHeader_Sprite_z2_blob_121-. @ src
	.4byte 1312 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_121_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 122
	.4byte gGraphicHeader_Sprite_z2_blob_122-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_blob_122_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_blob_0:
	.incbin "sprites/dynamic/z2_blob/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_blob_0_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_blob_1:
	.incbin "sprites/dynamic/z2_blob/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_blob_1_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_blob_2:
	.incbin "sprites/dynamic/z2_blob/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_blob_2_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_blob_3:
	.incbin "sprites/dynamic/z2_blob/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_blob_3_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_blob_4:
	.incbin "sprites/dynamic/z2_blob/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_blob_4_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_blob_5:
	.incbin "sprites/dynamic/z2_blob/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_blob_5_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_blob_6:
	.incbin "sprites/dynamic/z2_blob/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_blob_6_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_blob_7:
	.incbin "sprites/dynamic/z2_blob/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_blob_7_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_blob_8:
	.incbin "sprites/dynamic/z2_blob/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_blob_8_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_blob_9:
	.incbin "sprites/dynamic/z2_blob/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_blob_9_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_blob_10:
	.incbin "sprites/dynamic/z2_blob/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_blob_10_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_blob_11:
	.incbin "sprites/dynamic/z2_blob/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_blob_11_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_blob_12:
	.incbin "sprites/dynamic/z2_blob/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_blob_12_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_blob_13:
	.incbin "sprites/dynamic/z2_blob/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_blob_13_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_blob_14:
	.incbin "sprites/dynamic/z2_blob/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_blob_14_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_blob_15:
	.incbin "sprites/dynamic/z2_blob/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_blob_15_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_blob_16:
	.incbin "sprites/dynamic/z2_blob/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_blob_16_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_blob_17:
	.incbin "sprites/dynamic/z2_blob/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_blob_17_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_blob_18:
	.incbin "sprites/dynamic/z2_blob/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_blob_18_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_blob_19:
	.incbin "sprites/dynamic/z2_blob/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_blob_19_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_blob_20:
	.incbin "sprites/dynamic/z2_blob/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_blob_20_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_blob_21:
	.incbin "sprites/dynamic/z2_blob/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_blob_21_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_blob_22:
	.incbin "sprites/dynamic/z2_blob/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_blob_22_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_blob_23:
	.incbin "sprites/dynamic/z2_blob/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_blob_23_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_blob_24:
	.incbin "sprites/dynamic/z2_blob/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_blob_24_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_blob_25:
	.incbin "sprites/dynamic/z2_blob/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_blob_25_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_blob_26:
	.incbin "sprites/dynamic/z2_blob/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_blob_26_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_blob_27:
	.incbin "sprites/dynamic/z2_blob/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_blob_27_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_blob_28:
	.incbin "sprites/dynamic/z2_blob/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_blob_28_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_blob_29:
	.incbin "sprites/dynamic/z2_blob/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_blob_29_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_blob_30:
	.incbin "sprites/dynamic/z2_blob/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_blob_30_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_blob_31:
	.incbin "sprites/dynamic/z2_blob/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_blob_31_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_blob_32:
	.incbin "sprites/dynamic/z2_blob/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_blob_32_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_blob_33:
	.incbin "sprites/dynamic/z2_blob/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_blob_33_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_blob_34:
	.incbin "sprites/dynamic/z2_blob/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_blob_34_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_blob_35:
	.incbin "sprites/dynamic/z2_blob/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_blob_35_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_blob_36:
	.incbin "sprites/dynamic/z2_blob/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_blob_36_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_blob_37:
	.incbin "sprites/dynamic/z2_blob/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_blob_37_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_blob_38:
	.incbin "sprites/dynamic/z2_blob/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_blob_38_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_blob_39:
	.incbin "sprites/dynamic/z2_blob/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_blob_39_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_blob_40:
	.incbin "sprites/dynamic/z2_blob/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_blob_40_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_blob_41:
	.incbin "sprites/dynamic/z2_blob/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_blob_41_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_blob_42:
	.incbin "sprites/dynamic/z2_blob/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_blob_42_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_blob_43:
	.incbin "sprites/dynamic/z2_blob/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_blob_43_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_blob_44:
	.incbin "sprites/dynamic/z2_blob/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_blob_44_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_blob_45:
	.incbin "sprites/dynamic/z2_blob/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_blob_45_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_blob_46:
	.incbin "sprites/dynamic/z2_blob/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_blob_46_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_blob_47:
	.incbin "sprites/dynamic/z2_blob/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_blob_47_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_blob_48:
	.incbin "sprites/dynamic/z2_blob/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_blob_48_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/48.gbapal"

gGraphicHeader_Sprite_z2_blob_49:
	.incbin "sprites/dynamic/z2_blob/sheet/49.4bpp"
	gGraphicHeader_Sprite_z2_blob_49_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/49.gbapal"

gGraphicHeader_Sprite_z2_blob_50:
	.incbin "sprites/dynamic/z2_blob/sheet/50.4bpp"
	gGraphicHeader_Sprite_z2_blob_50_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/50.gbapal"

gGraphicHeader_Sprite_z2_blob_51:
	.incbin "sprites/dynamic/z2_blob/sheet/51.4bpp"
	gGraphicHeader_Sprite_z2_blob_51_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/51.gbapal"

gGraphicHeader_Sprite_z2_blob_52:
	.incbin "sprites/dynamic/z2_blob/sheet/52.4bpp"
	gGraphicHeader_Sprite_z2_blob_52_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/52.gbapal"

gGraphicHeader_Sprite_z2_blob_53:
	.incbin "sprites/dynamic/z2_blob/sheet/53.4bpp"
	gGraphicHeader_Sprite_z2_blob_53_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/53.gbapal"

gGraphicHeader_Sprite_z2_blob_54:
	.incbin "sprites/dynamic/z2_blob/sheet/54.4bpp"
	gGraphicHeader_Sprite_z2_blob_54_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/54.gbapal"

gGraphicHeader_Sprite_z2_blob_55:
	.incbin "sprites/dynamic/z2_blob/sheet/55.4bpp"
	gGraphicHeader_Sprite_z2_blob_55_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/55.gbapal"

gGraphicHeader_Sprite_z2_blob_56:
	.incbin "sprites/dynamic/z2_blob/sheet/56.4bpp"
	gGraphicHeader_Sprite_z2_blob_56_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/56.gbapal"

gGraphicHeader_Sprite_z2_blob_57:
	.incbin "sprites/dynamic/z2_blob/sheet/57.4bpp"
	gGraphicHeader_Sprite_z2_blob_57_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/57.gbapal"

gGraphicHeader_Sprite_z2_blob_58:
	.incbin "sprites/dynamic/z2_blob/sheet/58.4bpp"
	gGraphicHeader_Sprite_z2_blob_58_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/58.gbapal"

gGraphicHeader_Sprite_z2_blob_59:
	.incbin "sprites/dynamic/z2_blob/sheet/59.4bpp"
	gGraphicHeader_Sprite_z2_blob_59_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/59.gbapal"

gGraphicHeader_Sprite_z2_blob_60:
	.incbin "sprites/dynamic/z2_blob/sheet/60.4bpp"
	gGraphicHeader_Sprite_z2_blob_60_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/60.gbapal"

gGraphicHeader_Sprite_z2_blob_61:
	.incbin "sprites/dynamic/z2_blob/sheet/61.4bpp"
	gGraphicHeader_Sprite_z2_blob_61_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/61.gbapal"

gGraphicHeader_Sprite_z2_blob_62:
	.incbin "sprites/dynamic/z2_blob/sheet/62.4bpp"
	gGraphicHeader_Sprite_z2_blob_62_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/62.gbapal"

gGraphicHeader_Sprite_z2_blob_63:
	.incbin "sprites/dynamic/z2_blob/sheet/63.4bpp"
	gGraphicHeader_Sprite_z2_blob_63_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/63.gbapal"

gGraphicHeader_Sprite_z2_blob_64:
	.incbin "sprites/dynamic/z2_blob/sheet/64.4bpp"
	gGraphicHeader_Sprite_z2_blob_64_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/64.gbapal"

gGraphicHeader_Sprite_z2_blob_65:
	.incbin "sprites/dynamic/z2_blob/sheet/65.4bpp"
	gGraphicHeader_Sprite_z2_blob_65_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/65.gbapal"

gGraphicHeader_Sprite_z2_blob_66:
	.incbin "sprites/dynamic/z2_blob/sheet/66.4bpp"
	gGraphicHeader_Sprite_z2_blob_66_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/66.gbapal"

gGraphicHeader_Sprite_z2_blob_67:
	.incbin "sprites/dynamic/z2_blob/sheet/67.4bpp"
	gGraphicHeader_Sprite_z2_blob_67_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/67.gbapal"

gGraphicHeader_Sprite_z2_blob_68:
	.incbin "sprites/dynamic/z2_blob/sheet/68.4bpp"
	gGraphicHeader_Sprite_z2_blob_68_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/68.gbapal"

gGraphicHeader_Sprite_z2_blob_69:
	.incbin "sprites/dynamic/z2_blob/sheet/69.4bpp"
	gGraphicHeader_Sprite_z2_blob_69_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/69.gbapal"

gGraphicHeader_Sprite_z2_blob_70:
	.incbin "sprites/dynamic/z2_blob/sheet/70.4bpp"
	gGraphicHeader_Sprite_z2_blob_70_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/70.gbapal"

gGraphicHeader_Sprite_z2_blob_71:
	.incbin "sprites/dynamic/z2_blob/sheet/71.4bpp"
	gGraphicHeader_Sprite_z2_blob_71_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/71.gbapal"

gGraphicHeader_Sprite_z2_blob_72:
	.incbin "sprites/dynamic/z2_blob/sheet/72.4bpp"
	gGraphicHeader_Sprite_z2_blob_72_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/72.gbapal"

gGraphicHeader_Sprite_z2_blob_73:
	.incbin "sprites/dynamic/z2_blob/sheet/73.4bpp"
	gGraphicHeader_Sprite_z2_blob_73_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/73.gbapal"

gGraphicHeader_Sprite_z2_blob_74:
	.incbin "sprites/dynamic/z2_blob/sheet/74.4bpp"
	gGraphicHeader_Sprite_z2_blob_74_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/74.gbapal"

gGraphicHeader_Sprite_z2_blob_75:
	.incbin "sprites/dynamic/z2_blob/sheet/75.4bpp"
	gGraphicHeader_Sprite_z2_blob_75_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/75.gbapal"

gGraphicHeader_Sprite_z2_blob_76:
	.incbin "sprites/dynamic/z2_blob/sheet/76.4bpp"
	gGraphicHeader_Sprite_z2_blob_76_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/76.gbapal"

gGraphicHeader_Sprite_z2_blob_77:
	.incbin "sprites/dynamic/z2_blob/sheet/77.4bpp"
	gGraphicHeader_Sprite_z2_blob_77_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/77.gbapal"

gGraphicHeader_Sprite_z2_blob_78:
	.incbin "sprites/dynamic/z2_blob/sheet/78.4bpp"
	gGraphicHeader_Sprite_z2_blob_78_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/78.gbapal"

gGraphicHeader_Sprite_z2_blob_79:
	.incbin "sprites/dynamic/z2_blob/sheet/79.4bpp"
	gGraphicHeader_Sprite_z2_blob_79_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/79.gbapal"

gGraphicHeader_Sprite_z2_blob_80:
	.incbin "sprites/dynamic/z2_blob/sheet/80.4bpp"
	gGraphicHeader_Sprite_z2_blob_80_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/80.gbapal"

gGraphicHeader_Sprite_z2_blob_81:
	.incbin "sprites/dynamic/z2_blob/sheet/81.4bpp"
	gGraphicHeader_Sprite_z2_blob_81_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/81.gbapal"

gGraphicHeader_Sprite_z2_blob_82:
	.incbin "sprites/dynamic/z2_blob/sheet/82.4bpp"
	gGraphicHeader_Sprite_z2_blob_82_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/82.gbapal"

gGraphicHeader_Sprite_z2_blob_83:
	.incbin "sprites/dynamic/z2_blob/sheet/83.4bpp"
	gGraphicHeader_Sprite_z2_blob_83_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/83.gbapal"

gGraphicHeader_Sprite_z2_blob_84:
	.incbin "sprites/dynamic/z2_blob/sheet/84.4bpp"
	gGraphicHeader_Sprite_z2_blob_84_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/84.gbapal"

gGraphicHeader_Sprite_z2_blob_85:
	.incbin "sprites/dynamic/z2_blob/sheet/85.4bpp"
	gGraphicHeader_Sprite_z2_blob_85_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/85.gbapal"

gGraphicHeader_Sprite_z2_blob_86:
	.incbin "sprites/dynamic/z2_blob/sheet/86.4bpp"
	gGraphicHeader_Sprite_z2_blob_86_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/86.gbapal"

gGraphicHeader_Sprite_z2_blob_87:
	.incbin "sprites/dynamic/z2_blob/sheet/87.4bpp"
	gGraphicHeader_Sprite_z2_blob_87_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/87.gbapal"

gGraphicHeader_Sprite_z2_blob_88:
	.incbin "sprites/dynamic/z2_blob/sheet/88.4bpp"
	gGraphicHeader_Sprite_z2_blob_88_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/88.gbapal"

gGraphicHeader_Sprite_z2_blob_89:
	.incbin "sprites/dynamic/z2_blob/sheet/89.4bpp"
	gGraphicHeader_Sprite_z2_blob_89_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/89.gbapal"

gGraphicHeader_Sprite_z2_blob_90:
	.incbin "sprites/dynamic/z2_blob/sheet/90.4bpp"
	gGraphicHeader_Sprite_z2_blob_90_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/90.gbapal"

gGraphicHeader_Sprite_z2_blob_91:
	.incbin "sprites/dynamic/z2_blob/sheet/91.4bpp"
	gGraphicHeader_Sprite_z2_blob_91_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/91.gbapal"

gGraphicHeader_Sprite_z2_blob_92:
	.incbin "sprites/dynamic/z2_blob/sheet/92.4bpp"
	gGraphicHeader_Sprite_z2_blob_92_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/92.gbapal"

gGraphicHeader_Sprite_z2_blob_93:
	.incbin "sprites/dynamic/z2_blob/sheet/93.4bpp"
	gGraphicHeader_Sprite_z2_blob_93_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/93.gbapal"

gGraphicHeader_Sprite_z2_blob_94:
	.incbin "sprites/dynamic/z2_blob/sheet/94.4bpp"
	gGraphicHeader_Sprite_z2_blob_94_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/94.gbapal"

gGraphicHeader_Sprite_z2_blob_95:
	.incbin "sprites/dynamic/z2_blob/sheet/95.4bpp"
	gGraphicHeader_Sprite_z2_blob_95_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/95.gbapal"

gGraphicHeader_Sprite_z2_blob_96:
	.incbin "sprites/dynamic/z2_blob/sheet/96.4bpp"
	gGraphicHeader_Sprite_z2_blob_96_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/96.gbapal"

gGraphicHeader_Sprite_z2_blob_97:
	.incbin "sprites/dynamic/z2_blob/sheet/97.4bpp"
	gGraphicHeader_Sprite_z2_blob_97_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/97.gbapal"

gGraphicHeader_Sprite_z2_blob_98:
	.incbin "sprites/dynamic/z2_blob/sheet/98.4bpp"
	gGraphicHeader_Sprite_z2_blob_98_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/98.gbapal"

gGraphicHeader_Sprite_z2_blob_99:
	.incbin "sprites/dynamic/z2_blob/sheet/99.4bpp"
	gGraphicHeader_Sprite_z2_blob_99_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/99.gbapal"

gGraphicHeader_Sprite_z2_blob_100:
	.incbin "sprites/dynamic/z2_blob/sheet/100.4bpp"
	gGraphicHeader_Sprite_z2_blob_100_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/100.gbapal"

gGraphicHeader_Sprite_z2_blob_101:
	.incbin "sprites/dynamic/z2_blob/sheet/101.4bpp"
	gGraphicHeader_Sprite_z2_blob_101_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/101.gbapal"

gGraphicHeader_Sprite_z2_blob_102:
	.incbin "sprites/dynamic/z2_blob/sheet/102.4bpp"
	gGraphicHeader_Sprite_z2_blob_102_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/102.gbapal"

gGraphicHeader_Sprite_z2_blob_103:
	.incbin "sprites/dynamic/z2_blob/sheet/103.4bpp"
	gGraphicHeader_Sprite_z2_blob_103_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/103.gbapal"

gGraphicHeader_Sprite_z2_blob_104:
	.incbin "sprites/dynamic/z2_blob/sheet/104.4bpp"
	gGraphicHeader_Sprite_z2_blob_104_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/104.gbapal"

gGraphicHeader_Sprite_z2_blob_105:
	.incbin "sprites/dynamic/z2_blob/sheet/105.4bpp"
	gGraphicHeader_Sprite_z2_blob_105_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/105.gbapal"

gGraphicHeader_Sprite_z2_blob_106:
	.incbin "sprites/dynamic/z2_blob/sheet/106.4bpp"
	gGraphicHeader_Sprite_z2_blob_106_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/106.gbapal"

gGraphicHeader_Sprite_z2_blob_107:
	.incbin "sprites/dynamic/z2_blob/sheet/107.4bpp"
	gGraphicHeader_Sprite_z2_blob_107_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/107.gbapal"

gGraphicHeader_Sprite_z2_blob_108:
	.incbin "sprites/dynamic/z2_blob/sheet/108.4bpp"
	gGraphicHeader_Sprite_z2_blob_108_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/108.gbapal"

gGraphicHeader_Sprite_z2_blob_109:
	.incbin "sprites/dynamic/z2_blob/sheet/109.4bpp"
	gGraphicHeader_Sprite_z2_blob_109_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/109.gbapal"

gGraphicHeader_Sprite_z2_blob_110:
	.incbin "sprites/dynamic/z2_blob/sheet/110.4bpp"
	gGraphicHeader_Sprite_z2_blob_110_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/110.gbapal"

gGraphicHeader_Sprite_z2_blob_111:
	.incbin "sprites/dynamic/z2_blob/sheet/111.4bpp"
	gGraphicHeader_Sprite_z2_blob_111_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/111.gbapal"

gGraphicHeader_Sprite_z2_blob_112:
	.incbin "sprites/dynamic/z2_blob/sheet/112.4bpp"
	gGraphicHeader_Sprite_z2_blob_112_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/112.gbapal"

gGraphicHeader_Sprite_z2_blob_113:
	.incbin "sprites/dynamic/z2_blob/sheet/113.4bpp"
	gGraphicHeader_Sprite_z2_blob_113_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/113.gbapal"

gGraphicHeader_Sprite_z2_blob_114:
	.incbin "sprites/dynamic/z2_blob/sheet/114.4bpp"
	gGraphicHeader_Sprite_z2_blob_114_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/114.gbapal"

gGraphicHeader_Sprite_z2_blob_115:
	.incbin "sprites/dynamic/z2_blob/sheet/115.4bpp"
	gGraphicHeader_Sprite_z2_blob_115_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/115.gbapal"

gGraphicHeader_Sprite_z2_blob_116:
	.incbin "sprites/dynamic/z2_blob/sheet/116.4bpp"
	gGraphicHeader_Sprite_z2_blob_116_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/116.gbapal"

gGraphicHeader_Sprite_z2_blob_117:
	.incbin "sprites/dynamic/z2_blob/sheet/117.4bpp"
	gGraphicHeader_Sprite_z2_blob_117_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/117.gbapal"

gGraphicHeader_Sprite_z2_blob_118:
	.incbin "sprites/dynamic/z2_blob/sheet/118.4bpp"
	gGraphicHeader_Sprite_z2_blob_118_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/118.gbapal"

gGraphicHeader_Sprite_z2_blob_119:
	.incbin "sprites/dynamic/z2_blob/sheet/119.4bpp"
	gGraphicHeader_Sprite_z2_blob_119_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/119.gbapal"

gGraphicHeader_Sprite_z2_blob_120:
	.incbin "sprites/dynamic/z2_blob/sheet/120.4bpp"
	gGraphicHeader_Sprite_z2_blob_120_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/120.gbapal"

gGraphicHeader_Sprite_z2_blob_121:
	.incbin "sprites/dynamic/z2_blob/sheet/121.4bpp"
	gGraphicHeader_Sprite_z2_blob_121_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/121.gbapal"

gGraphicHeader_Sprite_z2_blob_122:
	.incbin "sprites/dynamic/z2_blob/sheet/122.4bpp"
	gGraphicHeader_Sprite_z2_blob_122_Palettes:
	.incbin "sprites/dynamic/z2_blob/sheet/122.gbapal"

.global gGraphicHeader_Sprite_z2_blob_End
gGraphicHeader_Sprite_z2_blob_End:
