@ Zero 2's Frog, dynamic motion 166, Zero 3's DM212_Z2_FROG

.balign 4, 0

.global gGraphicHeader_Sprite_z2_frog
gGraphicHeader_Sprite_z2_frog:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_frog_0-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_frog_1-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_frog_2-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_frog_3-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_frog_4-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_frog_5-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_frog_6-. @ src
	.4byte 480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_frog_7-. @ src
	.4byte 480 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_frog_8-. @ src
	.4byte 384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_frog_9-. @ src
	.4byte 416 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 104, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_frog_10-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_frog_11-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_frog_12-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_frog_13-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_frog_14-. @ src
	.4byte 448 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_frog_15-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_frog_16-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_frog_17-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_frog_18-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_frog_19-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_frog_20-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_frog_21-. @ src
	.4byte 608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gGraphicHeader_Sprite_z2_frog_22-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gGraphicHeader_Sprite_z2_frog_23-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gGraphicHeader_Sprite_z2_frog_24-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gGraphicHeader_Sprite_z2_frog_25-. @ src
	.4byte 704 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gGraphicHeader_Sprite_z2_frog_26-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gGraphicHeader_Sprite_z2_frog_27-. @ src
	.4byte 608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gGraphicHeader_Sprite_z2_frog_28-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gGraphicHeader_Sprite_z2_frog_29-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gGraphicHeader_Sprite_z2_frog_30-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gGraphicHeader_Sprite_z2_frog_31-. @ src
	.4byte 2176 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 544, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gGraphicHeader_Sprite_z2_frog_32-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gGraphicHeader_Sprite_z2_frog_33-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gGraphicHeader_Sprite_z2_frog_34-. @ src
	.4byte 544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gGraphicHeader_Sprite_z2_frog_35-. @ src
	.4byte 1344 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gGraphicHeader_Sprite_z2_frog_36-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gGraphicHeader_Sprite_z2_frog_37-. @ src
	.4byte 1056 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gGraphicHeader_Sprite_z2_frog_38-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gGraphicHeader_Sprite_z2_frog_39-. @ src
	.4byte 1184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gGraphicHeader_Sprite_z2_frog_40-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gGraphicHeader_Sprite_z2_frog_41-. @ src
	.4byte 1472 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gGraphicHeader_Sprite_z2_frog_42-. @ src
	.4byte 1696 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 424, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gGraphicHeader_Sprite_z2_frog_43-. @ src
	.4byte 1984 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 496, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gGraphicHeader_Sprite_z2_frog_44-. @ src
	.4byte 1440 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gGraphicHeader_Sprite_z2_frog_45-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gGraphicHeader_Sprite_z2_frog_46-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gGraphicHeader_Sprite_z2_frog_47-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gGraphicHeader_Sprite_z2_frog_48-. @ src
	.4byte 2176 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 544, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_frog_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_frog_0:
	.incbin "sprites/dynamic/z2_frog/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_frog_0_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_frog_1:
	.incbin "sprites/dynamic/z2_frog/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_frog_1_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_frog_2:
	.incbin "sprites/dynamic/z2_frog/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_frog_2_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_frog_3:
	.incbin "sprites/dynamic/z2_frog/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_frog_3_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_frog_4:
	.incbin "sprites/dynamic/z2_frog/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_frog_4_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_frog_5:
	.incbin "sprites/dynamic/z2_frog/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_frog_5_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_frog_6:
	.incbin "sprites/dynamic/z2_frog/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_frog_6_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_frog_7:
	.incbin "sprites/dynamic/z2_frog/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_frog_7_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_frog_8:
	.incbin "sprites/dynamic/z2_frog/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_frog_8_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_frog_9:
	.incbin "sprites/dynamic/z2_frog/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_frog_9_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_frog_10:
	.incbin "sprites/dynamic/z2_frog/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_frog_10_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_frog_11:
	.incbin "sprites/dynamic/z2_frog/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_frog_11_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_frog_12:
	.incbin "sprites/dynamic/z2_frog/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_frog_12_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_frog_13:
	.incbin "sprites/dynamic/z2_frog/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_frog_13_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_frog_14:
	.incbin "sprites/dynamic/z2_frog/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_frog_14_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_frog_15:
	.incbin "sprites/dynamic/z2_frog/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_frog_15_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_frog_16:
	.incbin "sprites/dynamic/z2_frog/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_frog_16_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_frog_17:
	.incbin "sprites/dynamic/z2_frog/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_frog_17_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_frog_18:
	.incbin "sprites/dynamic/z2_frog/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_frog_18_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_frog_19:
	.incbin "sprites/dynamic/z2_frog/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_frog_19_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_frog_20:
	.incbin "sprites/dynamic/z2_frog/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_frog_20_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_frog_21:
	.incbin "sprites/dynamic/z2_frog/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_frog_21_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/21.gbapal"

gGraphicHeader_Sprite_z2_frog_22:
	.incbin "sprites/dynamic/z2_frog/sheet/22.4bpp"
	gGraphicHeader_Sprite_z2_frog_22_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/22.gbapal"

gGraphicHeader_Sprite_z2_frog_23:
	.incbin "sprites/dynamic/z2_frog/sheet/23.4bpp"
	gGraphicHeader_Sprite_z2_frog_23_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/23.gbapal"

gGraphicHeader_Sprite_z2_frog_24:
	.incbin "sprites/dynamic/z2_frog/sheet/24.4bpp"
	gGraphicHeader_Sprite_z2_frog_24_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/24.gbapal"

gGraphicHeader_Sprite_z2_frog_25:
	.incbin "sprites/dynamic/z2_frog/sheet/25.4bpp"
	gGraphicHeader_Sprite_z2_frog_25_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/25.gbapal"

gGraphicHeader_Sprite_z2_frog_26:
	.incbin "sprites/dynamic/z2_frog/sheet/26.4bpp"
	gGraphicHeader_Sprite_z2_frog_26_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/26.gbapal"

gGraphicHeader_Sprite_z2_frog_27:
	.incbin "sprites/dynamic/z2_frog/sheet/27.4bpp"
	gGraphicHeader_Sprite_z2_frog_27_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/27.gbapal"

gGraphicHeader_Sprite_z2_frog_28:
	.incbin "sprites/dynamic/z2_frog/sheet/28.4bpp"
	gGraphicHeader_Sprite_z2_frog_28_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/28.gbapal"

gGraphicHeader_Sprite_z2_frog_29:
	.incbin "sprites/dynamic/z2_frog/sheet/29.4bpp"
	gGraphicHeader_Sprite_z2_frog_29_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/29.gbapal"

gGraphicHeader_Sprite_z2_frog_30:
	.incbin "sprites/dynamic/z2_frog/sheet/30.4bpp"
	gGraphicHeader_Sprite_z2_frog_30_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/30.gbapal"

gGraphicHeader_Sprite_z2_frog_31:
	.incbin "sprites/dynamic/z2_frog/sheet/31.4bpp"
	gGraphicHeader_Sprite_z2_frog_31_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/31.gbapal"

gGraphicHeader_Sprite_z2_frog_32:
	.incbin "sprites/dynamic/z2_frog/sheet/32.4bpp"
	gGraphicHeader_Sprite_z2_frog_32_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/32.gbapal"

gGraphicHeader_Sprite_z2_frog_33:
	.incbin "sprites/dynamic/z2_frog/sheet/33.4bpp"
	gGraphicHeader_Sprite_z2_frog_33_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/33.gbapal"

gGraphicHeader_Sprite_z2_frog_34:
	.incbin "sprites/dynamic/z2_frog/sheet/34.4bpp"
	gGraphicHeader_Sprite_z2_frog_34_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/34.gbapal"

gGraphicHeader_Sprite_z2_frog_35:
	.incbin "sprites/dynamic/z2_frog/sheet/35.4bpp"
	gGraphicHeader_Sprite_z2_frog_35_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/35.gbapal"

gGraphicHeader_Sprite_z2_frog_36:
	.incbin "sprites/dynamic/z2_frog/sheet/36.4bpp"
	gGraphicHeader_Sprite_z2_frog_36_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/36.gbapal"

gGraphicHeader_Sprite_z2_frog_37:
	.incbin "sprites/dynamic/z2_frog/sheet/37.4bpp"
	gGraphicHeader_Sprite_z2_frog_37_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/37.gbapal"

gGraphicHeader_Sprite_z2_frog_38:
	.incbin "sprites/dynamic/z2_frog/sheet/38.4bpp"
	gGraphicHeader_Sprite_z2_frog_38_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/38.gbapal"

gGraphicHeader_Sprite_z2_frog_39:
	.incbin "sprites/dynamic/z2_frog/sheet/39.4bpp"
	gGraphicHeader_Sprite_z2_frog_39_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/39.gbapal"

gGraphicHeader_Sprite_z2_frog_40:
	.incbin "sprites/dynamic/z2_frog/sheet/40.4bpp"
	gGraphicHeader_Sprite_z2_frog_40_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/40.gbapal"

gGraphicHeader_Sprite_z2_frog_41:
	.incbin "sprites/dynamic/z2_frog/sheet/41.4bpp"
	gGraphicHeader_Sprite_z2_frog_41_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/41.gbapal"

gGraphicHeader_Sprite_z2_frog_42:
	.incbin "sprites/dynamic/z2_frog/sheet/42.4bpp"
	gGraphicHeader_Sprite_z2_frog_42_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/42.gbapal"

gGraphicHeader_Sprite_z2_frog_43:
	.incbin "sprites/dynamic/z2_frog/sheet/43.4bpp"
	gGraphicHeader_Sprite_z2_frog_43_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/43.gbapal"

gGraphicHeader_Sprite_z2_frog_44:
	.incbin "sprites/dynamic/z2_frog/sheet/44.4bpp"
	gGraphicHeader_Sprite_z2_frog_44_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/44.gbapal"

gGraphicHeader_Sprite_z2_frog_45:
	.incbin "sprites/dynamic/z2_frog/sheet/45.4bpp"
	gGraphicHeader_Sprite_z2_frog_45_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/45.gbapal"

gGraphicHeader_Sprite_z2_frog_46:
	.incbin "sprites/dynamic/z2_frog/sheet/46.4bpp"
	gGraphicHeader_Sprite_z2_frog_46_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/46.gbapal"

gGraphicHeader_Sprite_z2_frog_47:
	.incbin "sprites/dynamic/z2_frog/sheet/47.4bpp"
	gGraphicHeader_Sprite_z2_frog_47_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/47.gbapal"

gGraphicHeader_Sprite_z2_frog_48:
	.incbin "sprites/dynamic/z2_frog/sheet/48.4bpp"
	gGraphicHeader_Sprite_z2_frog_48_Palettes:
	.incbin "sprites/dynamic/z2_frog/sheet/48.gbapal"

.global gGraphicHeader_Sprite_z2_frog_End
gGraphicHeader_Sprite_z2_frog_End:
