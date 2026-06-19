.section .rodata
.balign 4, 0

.global gMiscTilesetGraphics
gMiscTilesetGraphics:
	@ Graphic 0
	.4byte gMiscTilesetGraphics_0-. @ src offset
	.4byte (302 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_0_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gMiscTilesetGraphics_1-. @ src offset
	.4byte (302 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_1_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gMiscTilesetGraphics_2-. @ src offset
	.4byte (302 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_2_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gMiscTilesetGraphics_3-. @ src offset
	.4byte (302 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_3_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gMiscTilesetGraphics_4-. @ src offset
	.4byte (302 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_4_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gMiscTilesetGraphics_5-. @ src offset
	.4byte (605 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_5_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gMiscTilesetGraphics_6-. @ src offset
	.4byte (605 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_6_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gMiscTilesetGraphics_7-. @ src offset
	.4byte (605 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_7_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gMiscTilesetGraphics_8-. @ src offset
	.4byte (605 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_8_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gMiscTilesetGraphics_9-. @ src offset
	.4byte (754 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_9_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gMiscTilesetGraphics_10-. @ src offset
	.4byte (754 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_10_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gMiscTilesetGraphics_11-. @ src offset
	.4byte (754 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_11_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gMiscTilesetGraphics_12-. @ src offset
	.4byte (754 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_12_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gMiscTilesetGraphics_13-. @ src offset
	.4byte (754 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_13_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gMiscTilesetGraphics_14-. @ src offset
	.4byte (624 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_14_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gMiscTilesetGraphics_15-. @ src offset
	.4byte (624 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_15_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gMiscTilesetGraphics_16-. @ src offset
	.4byte (624 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_16_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gMiscTilesetGraphics_17-. @ src offset
	.4byte (624 << 22) | 192 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (192 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_17_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gMiscTilesetGraphics_18-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_18_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gMiscTilesetGraphics_19-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_19_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gMiscTilesetGraphics_20-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_20_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gMiscTilesetGraphics_21-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_21_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gMiscTilesetGraphics_22-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_22_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gMiscTilesetGraphics_23-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_23_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gMiscTilesetGraphics_24-. @ src offset
	.4byte (704 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_24_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gMiscTilesetGraphics_25-. @ src offset
	.4byte (32 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_25_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gMiscTilesetGraphics_26-. @ src offset
	.4byte (32 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_26_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gMiscTilesetGraphics_27-. @ src offset
	.4byte (32 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_27_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gMiscTilesetGraphics_28-. @ src offset
	.4byte (32 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_28_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gMiscTilesetGraphics_29-. @ src offset
	.4byte (32 << 22) | 0 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, NO_PAL
		@ Palette
		.4byte gMiscTilesetGraphics_29_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gMiscTilesetGraphics_30-. @ src offset
	.4byte (32 << 22) | 0 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, NO_PAL
		@ Palette
		.4byte gMiscTilesetGraphics_30_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gMiscTilesetGraphics_31-. @ src offset
	.4byte (32 << 22) | 0 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, NO_PAL
		@ Palette
		.4byte gMiscTilesetGraphics_31_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gMiscTilesetGraphics_32-. @ src offset
	.4byte (32 << 22) | 0 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, NO_PAL
		@ Palette
		.4byte gMiscTilesetGraphics_32_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gMiscTilesetGraphics_33-. @ src offset
	.4byte (171 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_33_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gMiscTilesetGraphics_34-. @ src offset
	.4byte (171 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_34_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gMiscTilesetGraphics_35-. @ src offset
	.4byte (171 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_35_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gMiscTilesetGraphics_36-. @ src offset
	.4byte (171 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_36_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gMiscTilesetGraphics_37-. @ src offset
	.4byte (457 << 22) | 768 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (768 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_37_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gMiscTilesetGraphics_38-. @ src offset
	.4byte (457 << 22) | 768 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (768 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_38_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gMiscTilesetGraphics_39-. @ src offset
	.4byte (457 << 22) | 768 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (768 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_39_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gMiscTilesetGraphics_40-. @ src offset
	.4byte (457 << 22) | 768 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (768 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_40_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gMiscTilesetGraphics_41-. @ src offset
	.4byte (457 << 22) | 768 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (768 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_41_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gMiscTilesetGraphics_42-. @ src offset
	.4byte (66 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_42_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gMiscTilesetGraphics_43-. @ src offset
	.4byte (66 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_43_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gMiscTilesetGraphics_44-. @ src offset
	.4byte (66 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_44_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gMiscTilesetGraphics_45-. @ src offset
	.4byte (66 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_45_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gMiscTilesetGraphics_46-. @ src offset
	.4byte (66 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_46_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gMiscTilesetGraphics_47-. @ src offset
	.4byte (64 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_47_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gMiscTilesetGraphics_48-. @ src offset
	.4byte (64 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_48_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gMiscTilesetGraphics_49-. @ src offset
	.4byte (64 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_49_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gMiscTilesetGraphics_50-. @ src offset
	.4byte (64 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_50_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gMiscTilesetGraphics_51-. @ src offset
	.4byte (196 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_51_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gMiscTilesetGraphics_52-. @ src offset
	.4byte (196 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_52_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gMiscTilesetGraphics_53-. @ src offset
	.4byte (196 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_53_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gMiscTilesetGraphics_54-. @ src offset
	.4byte (196 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_54_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gMiscTilesetGraphics_55-. @ src offset
	.4byte (196 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_55_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gMiscTilesetGraphics_56-. @ src offset
	.4byte (320 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_56_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gMiscTilesetGraphics_57-. @ src offset
	.4byte (320 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_57_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gMiscTilesetGraphics_58-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_58_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gMiscTilesetGraphics_59-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_59_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gMiscTilesetGraphics_60-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_60_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gMiscTilesetGraphics_61-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_61_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gMiscTilesetGraphics_62-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_62_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gMiscTilesetGraphics_63-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_63_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gMiscTilesetGraphics_64-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_64_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gMiscTilesetGraphics_65-. @ src offset
	.4byte (192 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_65_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 66
	.4byte gMiscTilesetGraphics_66-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_66_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 67
	.4byte gMiscTilesetGraphics_67-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_67_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 68
	.4byte gMiscTilesetGraphics_68-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_68_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 69
	.4byte gMiscTilesetGraphics_69-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_69_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 70
	.4byte gMiscTilesetGraphics_70-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_70_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 71
	.4byte gMiscTilesetGraphics_71-. @ src offset
	.4byte (532 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 8), (BPP4 | NO_PAL | MAP2D)	 @ th=8, props
		@ Palette
		.4byte gMiscTilesetGraphics_71_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 72
	.4byte gMiscTilesetGraphics_72-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_72_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 73
	.4byte gMiscTilesetGraphics_73-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_73_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 74
	.4byte gMiscTilesetGraphics_74-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_74_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 75
	.4byte gMiscTilesetGraphics_75-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_75_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 76
	.4byte gMiscTilesetGraphics_76-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_76_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 77
	.4byte gMiscTilesetGraphics_77-. @ src offset
	.4byte (320 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_77_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 78
	.4byte gMiscTilesetGraphics_78-. @ src offset
	.4byte (334 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_78_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 79
	.4byte gMiscTilesetGraphics_79-. @ src offset
	.4byte (334 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_79_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 80
	.4byte gMiscTilesetGraphics_80-. @ src offset
	.4byte (334 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_80_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 81
	.4byte gMiscTilesetGraphics_81-. @ src offset
	.4byte (334 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_81_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 82
	.4byte gMiscTilesetGraphics_82-. @ src offset
	.4byte (334 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_82_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 83
	.4byte gMiscTilesetGraphics_83-. @ src offset
	.4byte (64 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_83_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 84
	.4byte gMiscTilesetGraphics_84-. @ src offset
	.4byte (64 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_84_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 85
	.4byte gMiscTilesetGraphics_85-. @ src offset
	.4byte (64 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_85_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 86
	.4byte gMiscTilesetGraphics_86-. @ src offset
	.4byte (64 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_86_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 87
	.4byte gMiscTilesetGraphics_87-. @ src offset
	.4byte (64 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_87_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 88
	.4byte gMiscTilesetGraphics_88-. @ src offset
	.4byte (528 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_88_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 89
	.4byte gMiscTilesetGraphics_89-. @ src offset
	.4byte (528 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_89_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 90
	.4byte gMiscTilesetGraphics_90-. @ src offset
	.4byte (528 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_90_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 91
	.4byte gMiscTilesetGraphics_91-. @ src offset
	.4byte (528 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_91_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 92
	.4byte gMiscTilesetGraphics_92-. @ src offset
	.4byte (1013 << 22) | 320 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (320 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_92_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 93
	.4byte gMiscTilesetGraphics_93-. @ src offset
	.4byte (588 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_93_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 94
	.4byte gMiscTilesetGraphics_94-. @ src offset
	.4byte (588 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_94_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 95
	.4byte gMiscTilesetGraphics_95-. @ src offset
	.4byte (588 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_95_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 96
	.4byte gMiscTilesetGraphics_96-. @ src offset
	.4byte (588 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_96_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 97
	.4byte gMiscTilesetGraphics_97-. @ src offset
	.4byte (588 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_97_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 98
	.4byte gMiscTilesetGraphics_98-. @ src offset
	.4byte (709 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_98_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 99
	.4byte gMiscTilesetGraphics_99-. @ src offset
	.4byte (709 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_99_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 100
	.4byte gMiscTilesetGraphics_100-. @ src offset
	.4byte (709 << 22) | 256 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (256 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_100_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 101
	.4byte gMiscTilesetGraphics_101-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_101_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 102
	.4byte gMiscTilesetGraphics_102-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_102_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 103
	.4byte gMiscTilesetGraphics_103-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_103_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 104
	.4byte gMiscTilesetGraphics_104-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_104_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 105
	.4byte gMiscTilesetGraphics_105-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_105_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 106
	.4byte gMiscTilesetGraphics_106-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_106_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 107
	.4byte gMiscTilesetGraphics_107-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_107_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 108
	.4byte gMiscTilesetGraphics_108-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_108_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 109
	.4byte gMiscTilesetGraphics_109-. @ src offset
	.4byte (991 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_109_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 110
	.4byte gMiscTilesetGraphics_110-. @ src offset
	.4byte (883 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_110_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 111
	.4byte gMiscTilesetGraphics_111-. @ src offset
	.4byte (883 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_111_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 112
	.4byte gMiscTilesetGraphics_112-. @ src offset
	.4byte (360 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_112_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 113
	.4byte gMiscTilesetGraphics_113-. @ src offset
	.4byte (360 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_113_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 114
	.4byte gMiscTilesetGraphics_114-. @ src offset
	.4byte (360 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_114_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 115
	.4byte gMiscTilesetGraphics_115-. @ src offset
	.4byte (360 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_115_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 116
	.4byte gMiscTilesetGraphics_116-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_116_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 117
	.4byte gMiscTilesetGraphics_117-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_117_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 118
	.4byte gMiscTilesetGraphics_118-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_118_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 119
	.4byte gMiscTilesetGraphics_119-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_119_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 120
	.4byte gMiscTilesetGraphics_120-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_120_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 121
	.4byte gMiscTilesetGraphics_121-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_121_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 122
	.4byte gMiscTilesetGraphics_122-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_122_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 123
	.4byte gMiscTilesetGraphics_123-. @ src offset
	.4byte (512 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_123_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 124
	.4byte gMiscTilesetGraphics_124-. @ src offset
	.4byte (855 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_124_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 125
	.4byte gMiscTilesetGraphics_125-. @ src offset
	.4byte (855 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_125_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 126
	.4byte gMiscTilesetGraphics_126-. @ src offset
	.4byte (855 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_126_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 127
	.4byte gMiscTilesetGraphics_127-. @ src offset
	.4byte (855 << 22) | 576 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (576 / 4), (BPP4 | NO_PAL)	 @ th=4(unused), props
		@ Palette
		.4byte gMiscTilesetGraphics_127_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 128
	.4byte gMiscTilesetGraphics_128-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_128_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 129
	.4byte gMiscTilesetGraphics_129-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_129_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 130
	.4byte gMiscTilesetGraphics_130-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_130_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 131
	.4byte gMiscTilesetGraphics_131-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_131_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 132
	.4byte gMiscTilesetGraphics_132-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_132_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 133
	.4byte gMiscTilesetGraphics_133-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_133_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 134
	.4byte gMiscTilesetGraphics_134-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_134_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 135
	.4byte gMiscTilesetGraphics_135-. @ src offset
	.4byte (832 << 22) | 1024 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1024 / 2), (BPP4 | NO_PAL | MAP2D)	 @ th=2, props
		@ Palette
		.4byte gMiscTilesetGraphics_135_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 136
	.4byte gMiscTilesetGraphics_136-. @ src offset
	.4byte (49 << 22) | 960 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (960 / 3), (BPP4 | NO_PAL | MAP2D)	 @ th=3, props
		@ Palette
		.4byte gMiscTilesetGraphics_136_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 137
	.4byte gMiscTilesetGraphics_137-. @ src offset
	.4byte (49 << 22) | 960 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (960 / 3), (BPP4 | NO_PAL | MAP2D)	 @ th=3, props
		@ Palette
		.4byte gMiscTilesetGraphics_137_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 138
	.4byte gMiscTilesetGraphics_138-. @ src offset
	.4byte (49 << 22) | 960 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (960 / 3), (BPP4 | NO_PAL | MAP2D)	 @ th=3, props
		@ Palette
		.4byte gMiscTilesetGraphics_138_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 139
	.4byte gMiscTilesetGraphics_139-. @ src offset
	.4byte (49 << 22) | 960 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (960 / 3), (BPP4 | NO_PAL | MAP2D)	 @ th=3, props
		@ Palette
		.4byte gMiscTilesetGraphics_139_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 140
	.4byte gMiscTilesetGraphics_140-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_140_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 141
	.4byte gMiscTilesetGraphics_141-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_141_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 142
	.4byte gMiscTilesetGraphics_142-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_142_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 143
	.4byte gMiscTilesetGraphics_143-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_143_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 144
	.4byte gMiscTilesetGraphics_144-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_144_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 145
	.4byte gMiscTilesetGraphics_145-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_145_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 146
	.4byte gMiscTilesetGraphics_146-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_146_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 147
	.4byte gMiscTilesetGraphics_147-. @ src offset
	.4byte (456 << 22) | 384 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (384 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_147_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 148
	.4byte gMiscTilesetGraphics_148-. @ src offset
	.4byte (736 << 22) | 7168 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (7168 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_148_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 149
	.4byte gMiscTilesetGraphics_149-. @ src offset
	.4byte (736 << 22) | 7168 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (7168 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_149_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 150
	.4byte gMiscTilesetGraphics_150-. @ src offset
	.4byte (736 << 22) | 7168 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (7168 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_150_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 151
	.4byte gMiscTilesetGraphics_151-. @ src offset
	.4byte (736 << 22) | 7168 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (7168 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_151_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 152
	.4byte gMiscTilesetGraphics_152-. @ src offset
	.4byte (736 << 22) | 7168 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (7168 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_152_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 153
	.4byte gMiscTilesetGraphics_153-. @ src offset
	.4byte (512 << 22) | 1920 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1920 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_153_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 154
	.4byte gMiscTilesetGraphics_154-. @ src offset
	.4byte (512 << 22) | 1920 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1920 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_154_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 155
	.4byte gMiscTilesetGraphics_155-. @ src offset
	.4byte (512 << 22) | 1920 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1920 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_155_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 156
	.4byte gMiscTilesetGraphics_156-. @ src offset
	.4byte (512 << 22) | 1920 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1920 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_156_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 157
	.4byte gMiscTilesetGraphics_157-. @ src offset
	.4byte (512 << 22) | 1920 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (1920 / 6), (BPP4 | NO_PAL | MAP2D)	 @ th=6, props
		@ Palette
		.4byte gMiscTilesetGraphics_157_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 158
	.4byte gMiscTilesetGraphics_158-. @ src offset
	.4byte (213 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_158_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 159
	.4byte gMiscTilesetGraphics_159-. @ src offset
	.4byte (213 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_159_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 160
	.4byte gMiscTilesetGraphics_160-. @ src offset
	.4byte (213 << 22) | 128 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (128 / 1), (BPP4 | NO_PAL | MAP2D)	 @ th=1, props
		@ Palette
		.4byte gMiscTilesetGraphics_160_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 161
	.4byte gMiscTilesetGraphics_161-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_161_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 162
	.4byte gMiscTilesetGraphics_162-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_162_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 163
	.4byte gMiscTilesetGraphics_163-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_163_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 164
	.4byte gMiscTilesetGraphics_164-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_164_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 165
	.4byte gMiscTilesetGraphics_165-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_165_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 166
	.4byte gMiscTilesetGraphics_166-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_166_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 167
	.4byte gMiscTilesetGraphics_167-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_167_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 168
	.4byte gMiscTilesetGraphics_168-. @ src offset
	.4byte (256 << 22) | 2688 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2688 / 7), (BPP4 | NO_PAL | MAP2D)	 @ th=7, props
		@ Palette
		.4byte gMiscTilesetGraphics_168_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 169
	.4byte gMiscTilesetGraphics_169-. @ src offset
	.4byte (128 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_169_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 170
	.4byte gMiscTilesetGraphics_170-. @ src offset
	.4byte (128 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_170_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 171
	.4byte gMiscTilesetGraphics_171-. @ src offset
	.4byte (128 << 22) | 512 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (512 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_171_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 172
	.4byte gMiscTilesetGraphics_172-. @ src offset
	.4byte (16 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_172_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 173
	.4byte gMiscTilesetGraphics_173-. @ src offset
	.4byte (16 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_173_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 174
	.4byte gMiscTilesetGraphics_174-. @ src offset
	.4byte (16 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_174_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 175
	.4byte gMiscTilesetGraphics_175-. @ src offset
	.4byte (16 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_175_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 176
	.4byte gMiscTilesetGraphics_176-. @ src offset
	.4byte (16 << 22) | 2048 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte (2048 / 4), (BPP4 | NO_PAL | MAP2D)	 @ th=4, props
		@ Palette
		.4byte gMiscTilesetGraphics_176_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gMiscTilesetGraphics_0:
	.incbin "data/tilesets/misc/0/tiles.4bpp"
	gMiscTilesetGraphics_0_Palettes:

gMiscTilesetGraphics_1:
	.incbin "data/tilesets/misc/1/tiles.4bpp"
	gMiscTilesetGraphics_1_Palettes:

gMiscTilesetGraphics_2:
	.incbin "data/tilesets/misc/2/tiles.4bpp"
	gMiscTilesetGraphics_2_Palettes:

gMiscTilesetGraphics_3:
	.incbin "data/tilesets/misc/3/tiles.4bpp"
	gMiscTilesetGraphics_3_Palettes:

gMiscTilesetGraphics_4:
	.incbin "data/tilesets/misc/4/tiles.4bpp"
	gMiscTilesetGraphics_4_Palettes:

gMiscTilesetGraphics_5:
	.incbin "data/tilesets/misc/5/tiles.4bpp"
	gMiscTilesetGraphics_5_Palettes:

gMiscTilesetGraphics_6:
	.incbin "data/tilesets/misc/6/tiles.4bpp"
	gMiscTilesetGraphics_6_Palettes:

gMiscTilesetGraphics_7:
	.incbin "data/tilesets/misc/7/tiles.4bpp"
	gMiscTilesetGraphics_7_Palettes:

gMiscTilesetGraphics_8:
	.incbin "data/tilesets/misc/8/tiles.4bpp"
	gMiscTilesetGraphics_8_Palettes:

gMiscTilesetGraphics_9:
	.incbin "data/tilesets/misc/9/tiles.4bpp"
	gMiscTilesetGraphics_9_Palettes:

gMiscTilesetGraphics_10:
	.incbin "data/tilesets/misc/10/tiles.4bpp"
	gMiscTilesetGraphics_10_Palettes:

gMiscTilesetGraphics_11:
	.incbin "data/tilesets/misc/11/tiles.4bpp"
	gMiscTilesetGraphics_11_Palettes:

gMiscTilesetGraphics_12:
	.incbin "data/tilesets/misc/12/tiles.4bpp"
	gMiscTilesetGraphics_12_Palettes:

gMiscTilesetGraphics_13:
	.incbin "data/tilesets/misc/13/tiles.4bpp"
	gMiscTilesetGraphics_13_Palettes:

gMiscTilesetGraphics_14:
	.incbin "data/tilesets/misc/14/tiles.4bpp"
	gMiscTilesetGraphics_14_Palettes:

gMiscTilesetGraphics_15:
	.incbin "data/tilesets/misc/15/tiles.4bpp"
	gMiscTilesetGraphics_15_Palettes:

gMiscTilesetGraphics_16:
	.incbin "data/tilesets/misc/16/tiles.4bpp"
	gMiscTilesetGraphics_16_Palettes:

gMiscTilesetGraphics_17:
	.incbin "data/tilesets/misc/17/tiles.4bpp"
	gMiscTilesetGraphics_17_Palettes:

gMiscTilesetGraphics_18:
	.incbin "data/tilesets/misc/18/tiles.4bpp"
	gMiscTilesetGraphics_18_Palettes:

gMiscTilesetGraphics_19:
	.incbin "data/tilesets/misc/19/tiles.4bpp"
	gMiscTilesetGraphics_19_Palettes:

gMiscTilesetGraphics_20:
	.incbin "data/tilesets/misc/20/tiles.4bpp"
	gMiscTilesetGraphics_20_Palettes:

gMiscTilesetGraphics_21:
	.incbin "data/tilesets/misc/21/tiles.4bpp"
	gMiscTilesetGraphics_21_Palettes:

gMiscTilesetGraphics_22:
	.incbin "data/tilesets/misc/22/tiles.4bpp"
	gMiscTilesetGraphics_22_Palettes:

gMiscTilesetGraphics_23:
	.incbin "data/tilesets/misc/23/tiles.4bpp"
	gMiscTilesetGraphics_23_Palettes:

gMiscTilesetGraphics_24:
	.incbin "data/tilesets/misc/24/tiles.4bpp"
	gMiscTilesetGraphics_24_Palettes:

gMiscTilesetGraphics_25:
	.incbin "data/tilesets/misc/25/tiles.4bpp"
	gMiscTilesetGraphics_25_Palettes:

gMiscTilesetGraphics_26:
	.incbin "data/tilesets/misc/26/tiles.4bpp"
	gMiscTilesetGraphics_26_Palettes:

gMiscTilesetGraphics_27:
	.incbin "data/tilesets/misc/27/tiles.4bpp"
	gMiscTilesetGraphics_27_Palettes:

gMiscTilesetGraphics_28:
	.incbin "data/tilesets/misc/28/tiles.4bpp"
	gMiscTilesetGraphics_28_Palettes:

gMiscTilesetGraphics_29:
	.incbin "data/tilesets/misc/29/tiles.4bpp"
	gMiscTilesetGraphics_29_Palettes:

gMiscTilesetGraphics_30:
	.incbin "data/tilesets/misc/30/tiles.4bpp"
	gMiscTilesetGraphics_30_Palettes:

gMiscTilesetGraphics_31:
	.incbin "data/tilesets/misc/31/tiles.4bpp"
	gMiscTilesetGraphics_31_Palettes:

gMiscTilesetGraphics_32:
	.incbin "data/tilesets/misc/32/tiles.4bpp"
	gMiscTilesetGraphics_32_Palettes:

gMiscTilesetGraphics_33:
	.incbin "data/tilesets/misc/33/tiles.4bpp"
	gMiscTilesetGraphics_33_Palettes:

gMiscTilesetGraphics_34:
	.incbin "data/tilesets/misc/34/tiles.4bpp"
	gMiscTilesetGraphics_34_Palettes:

gMiscTilesetGraphics_35:
	.incbin "data/tilesets/misc/35/tiles.4bpp"
	gMiscTilesetGraphics_35_Palettes:

gMiscTilesetGraphics_36:
	.incbin "data/tilesets/misc/36/tiles.4bpp"
	gMiscTilesetGraphics_36_Palettes:

gMiscTilesetGraphics_37:
	.incbin "data/tilesets/misc/37/tiles.4bpp"
	gMiscTilesetGraphics_37_Palettes:

gMiscTilesetGraphics_38:
	.incbin "data/tilesets/misc/38/tiles.4bpp"
	gMiscTilesetGraphics_38_Palettes:

gMiscTilesetGraphics_39:
	.incbin "data/tilesets/misc/39/tiles.4bpp"
	gMiscTilesetGraphics_39_Palettes:

gMiscTilesetGraphics_40:
	.incbin "data/tilesets/misc/40/tiles.4bpp"
	gMiscTilesetGraphics_40_Palettes:

gMiscTilesetGraphics_41:
	.incbin "data/tilesets/misc/41/tiles.4bpp"
	gMiscTilesetGraphics_41_Palettes:

gMiscTilesetGraphics_42:
	.incbin "data/tilesets/misc/42/tiles.4bpp"
	gMiscTilesetGraphics_42_Palettes:

gMiscTilesetGraphics_43:
	.incbin "data/tilesets/misc/43/tiles.4bpp"
	gMiscTilesetGraphics_43_Palettes:

gMiscTilesetGraphics_44:
	.incbin "data/tilesets/misc/44/tiles.4bpp"
	gMiscTilesetGraphics_44_Palettes:

gMiscTilesetGraphics_45:
	.incbin "data/tilesets/misc/45/tiles.4bpp"
	gMiscTilesetGraphics_45_Palettes:

gMiscTilesetGraphics_46:
	.incbin "data/tilesets/misc/46/tiles.4bpp"
	gMiscTilesetGraphics_46_Palettes:

gMiscTilesetGraphics_47:
	.incbin "data/tilesets/misc/47/tiles.4bpp"
	gMiscTilesetGraphics_47_Palettes:

gMiscTilesetGraphics_48:
	.incbin "data/tilesets/misc/48/tiles.4bpp"
	gMiscTilesetGraphics_48_Palettes:

gMiscTilesetGraphics_49:
	.incbin "data/tilesets/misc/49/tiles.4bpp"
	gMiscTilesetGraphics_49_Palettes:

gMiscTilesetGraphics_50:
	.incbin "data/tilesets/misc/50/tiles.4bpp"
	gMiscTilesetGraphics_50_Palettes:

gMiscTilesetGraphics_51:
	.incbin "data/tilesets/misc/51/tiles.4bpp"
	gMiscTilesetGraphics_51_Palettes:

gMiscTilesetGraphics_52:
	.incbin "data/tilesets/misc/52/tiles.4bpp"
	gMiscTilesetGraphics_52_Palettes:

gMiscTilesetGraphics_53:
	.incbin "data/tilesets/misc/53/tiles.4bpp"
	gMiscTilesetGraphics_53_Palettes:

gMiscTilesetGraphics_54:
	.incbin "data/tilesets/misc/54/tiles.4bpp"
	gMiscTilesetGraphics_54_Palettes:

gMiscTilesetGraphics_55:
	.incbin "data/tilesets/misc/55/tiles.4bpp"
	gMiscTilesetGraphics_55_Palettes:

gMiscTilesetGraphics_56:
	.incbin "data/tilesets/misc/56/tiles.4bpp"
	gMiscTilesetGraphics_56_Palettes:

gMiscTilesetGraphics_57:
	.incbin "data/tilesets/misc/57/tiles.4bpp"
	gMiscTilesetGraphics_57_Palettes:

gMiscTilesetGraphics_58:
	.incbin "data/tilesets/misc/58/tiles.4bpp"
	gMiscTilesetGraphics_58_Palettes:

gMiscTilesetGraphics_59:
	.incbin "data/tilesets/misc/59/tiles.4bpp"
	gMiscTilesetGraphics_59_Palettes:

gMiscTilesetGraphics_60:
	.incbin "data/tilesets/misc/60/tiles.4bpp"
	gMiscTilesetGraphics_60_Palettes:

gMiscTilesetGraphics_61:
	.incbin "data/tilesets/misc/61/tiles.4bpp"
	gMiscTilesetGraphics_61_Palettes:

gMiscTilesetGraphics_62:
	.incbin "data/tilesets/misc/62/tiles.4bpp"
	gMiscTilesetGraphics_62_Palettes:

gMiscTilesetGraphics_63:
	.incbin "data/tilesets/misc/63/tiles.4bpp"
	gMiscTilesetGraphics_63_Palettes:

gMiscTilesetGraphics_64:
	.incbin "data/tilesets/misc/64/tiles.4bpp"
	gMiscTilesetGraphics_64_Palettes:

gMiscTilesetGraphics_65:
	.incbin "data/tilesets/misc/65/tiles.4bpp"
	gMiscTilesetGraphics_65_Palettes:

gMiscTilesetGraphics_66:
	.incbin "data/tilesets/misc/66/tiles.4bpp"
	gMiscTilesetGraphics_66_Palettes:

gMiscTilesetGraphics_67:
	.incbin "data/tilesets/misc/67/tiles.4bpp"
	gMiscTilesetGraphics_67_Palettes:

gMiscTilesetGraphics_68:
	.incbin "data/tilesets/misc/68/tiles.4bpp"
	gMiscTilesetGraphics_68_Palettes:

gMiscTilesetGraphics_69:
	.incbin "data/tilesets/misc/69/tiles.4bpp"
	gMiscTilesetGraphics_69_Palettes:

gMiscTilesetGraphics_70:
	.incbin "data/tilesets/misc/70/tiles.4bpp"
	gMiscTilesetGraphics_70_Palettes:

gMiscTilesetGraphics_71:
	.incbin "data/tilesets/misc/71/tiles.4bpp"
	gMiscTilesetGraphics_71_Palettes:

gMiscTilesetGraphics_72:
	.incbin "data/tilesets/misc/72/tiles.4bpp"
	gMiscTilesetGraphics_72_Palettes:

gMiscTilesetGraphics_73:
	.incbin "data/tilesets/misc/73/tiles.4bpp"
	gMiscTilesetGraphics_73_Palettes:

gMiscTilesetGraphics_74:
	.incbin "data/tilesets/misc/74/tiles.4bpp"
	gMiscTilesetGraphics_74_Palettes:

gMiscTilesetGraphics_75:
	.incbin "data/tilesets/misc/75/tiles.4bpp"
	gMiscTilesetGraphics_75_Palettes:

gMiscTilesetGraphics_76:
	.incbin "data/tilesets/misc/76/tiles.4bpp"
	gMiscTilesetGraphics_76_Palettes:

gMiscTilesetGraphics_77:
	.incbin "data/tilesets/misc/77/tiles.4bpp"
	gMiscTilesetGraphics_77_Palettes:

gMiscTilesetGraphics_78:
	.incbin "data/tilesets/misc/78/tiles.4bpp"
	gMiscTilesetGraphics_78_Palettes:

gMiscTilesetGraphics_79:
	.incbin "data/tilesets/misc/79/tiles.4bpp"
	gMiscTilesetGraphics_79_Palettes:

gMiscTilesetGraphics_80:
	.incbin "data/tilesets/misc/80/tiles.4bpp"
	gMiscTilesetGraphics_80_Palettes:

gMiscTilesetGraphics_81:
	.incbin "data/tilesets/misc/81/tiles.4bpp"
	gMiscTilesetGraphics_81_Palettes:

gMiscTilesetGraphics_82:
	.incbin "data/tilesets/misc/82/tiles.4bpp"
	gMiscTilesetGraphics_82_Palettes:

gMiscTilesetGraphics_83:
	.incbin "data/tilesets/misc/83/tiles.4bpp"
	gMiscTilesetGraphics_83_Palettes:

gMiscTilesetGraphics_84:
	.incbin "data/tilesets/misc/84/tiles.4bpp"
	gMiscTilesetGraphics_84_Palettes:

gMiscTilesetGraphics_85:
	.incbin "data/tilesets/misc/85/tiles.4bpp"
	gMiscTilesetGraphics_85_Palettes:

gMiscTilesetGraphics_86:
	.incbin "data/tilesets/misc/86/tiles.4bpp"
	gMiscTilesetGraphics_86_Palettes:

gMiscTilesetGraphics_87:
	.incbin "data/tilesets/misc/87/tiles.4bpp"
	gMiscTilesetGraphics_87_Palettes:

gMiscTilesetGraphics_88:
	.incbin "data/tilesets/misc/88/tiles.4bpp"
	gMiscTilesetGraphics_88_Palettes:

gMiscTilesetGraphics_89:
	.incbin "data/tilesets/misc/89/tiles.4bpp"
	gMiscTilesetGraphics_89_Palettes:

gMiscTilesetGraphics_90:
	.incbin "data/tilesets/misc/90/tiles.4bpp"
	gMiscTilesetGraphics_90_Palettes:

gMiscTilesetGraphics_91:
	.incbin "data/tilesets/misc/91/tiles.4bpp"
	gMiscTilesetGraphics_91_Palettes:

gMiscTilesetGraphics_92:
	.incbin "data/tilesets/misc/92/tiles.4bpp"
	gMiscTilesetGraphics_92_Palettes:

gMiscTilesetGraphics_93:
	.incbin "data/tilesets/misc/93/tiles.4bpp"
	gMiscTilesetGraphics_93_Palettes:

gMiscTilesetGraphics_94:
	.incbin "data/tilesets/misc/94/tiles.4bpp"
	gMiscTilesetGraphics_94_Palettes:

gMiscTilesetGraphics_95:
	.incbin "data/tilesets/misc/95/tiles.4bpp"
	gMiscTilesetGraphics_95_Palettes:

gMiscTilesetGraphics_96:
	.incbin "data/tilesets/misc/96/tiles.4bpp"
	gMiscTilesetGraphics_96_Palettes:

gMiscTilesetGraphics_97:
	.incbin "data/tilesets/misc/97/tiles.4bpp"
	gMiscTilesetGraphics_97_Palettes:

gMiscTilesetGraphics_98:
	.incbin "data/tilesets/misc/98/tiles.4bpp"
	gMiscTilesetGraphics_98_Palettes:

gMiscTilesetGraphics_99:
	.incbin "data/tilesets/misc/99/tiles.4bpp"
	gMiscTilesetGraphics_99_Palettes:

gMiscTilesetGraphics_100:
	.incbin "data/tilesets/misc/100/tiles.4bpp"
	gMiscTilesetGraphics_100_Palettes:

gMiscTilesetGraphics_101:
	.incbin "data/tilesets/misc/101/tiles.4bpp"
	gMiscTilesetGraphics_101_Palettes:

gMiscTilesetGraphics_102:
	.incbin "data/tilesets/misc/102/tiles.4bpp"
	gMiscTilesetGraphics_102_Palettes:

gMiscTilesetGraphics_103:
	.incbin "data/tilesets/misc/103/tiles.4bpp"
	gMiscTilesetGraphics_103_Palettes:

gMiscTilesetGraphics_104:
	.incbin "data/tilesets/misc/104/tiles.4bpp"
	gMiscTilesetGraphics_104_Palettes:

gMiscTilesetGraphics_105:
	.incbin "data/tilesets/misc/105/tiles.4bpp"
	gMiscTilesetGraphics_105_Palettes:

gMiscTilesetGraphics_106:
	.incbin "data/tilesets/misc/106/tiles.4bpp"
	gMiscTilesetGraphics_106_Palettes:

gMiscTilesetGraphics_107:
	.incbin "data/tilesets/misc/107/tiles.4bpp"
	gMiscTilesetGraphics_107_Palettes:

gMiscTilesetGraphics_108:
	.incbin "data/tilesets/misc/108/tiles.4bpp"
	gMiscTilesetGraphics_108_Palettes:

gMiscTilesetGraphics_109:
	.incbin "data/tilesets/misc/109/tiles.4bpp"
	gMiscTilesetGraphics_109_Palettes:

gMiscTilesetGraphics_110:
	.incbin "data/tilesets/misc/110/tiles.4bpp"
	gMiscTilesetGraphics_110_Palettes:

gMiscTilesetGraphics_111:
	.incbin "data/tilesets/misc/111/tiles.4bpp"
	gMiscTilesetGraphics_111_Palettes:

gMiscTilesetGraphics_112:
	.incbin "data/tilesets/misc/112/tiles.4bpp"
	gMiscTilesetGraphics_112_Palettes:

gMiscTilesetGraphics_113:
	.incbin "data/tilesets/misc/113/tiles.4bpp"
	gMiscTilesetGraphics_113_Palettes:

gMiscTilesetGraphics_114:
	.incbin "data/tilesets/misc/114/tiles.4bpp"
	gMiscTilesetGraphics_114_Palettes:

gMiscTilesetGraphics_115:
	.incbin "data/tilesets/misc/115/tiles.4bpp"
	gMiscTilesetGraphics_115_Palettes:

gMiscTilesetGraphics_116:
	.incbin "data/tilesets/misc/116/tiles.4bpp"
	gMiscTilesetGraphics_116_Palettes:

gMiscTilesetGraphics_117:
	.incbin "data/tilesets/misc/117/tiles.4bpp"
	gMiscTilesetGraphics_117_Palettes:

gMiscTilesetGraphics_118:
	.incbin "data/tilesets/misc/118/tiles.4bpp"
	gMiscTilesetGraphics_118_Palettes:

gMiscTilesetGraphics_119:
	.incbin "data/tilesets/misc/119/tiles.4bpp"
	gMiscTilesetGraphics_119_Palettes:

gMiscTilesetGraphics_120:
	.incbin "data/tilesets/misc/120/tiles.4bpp"
	gMiscTilesetGraphics_120_Palettes:

gMiscTilesetGraphics_121:
	.incbin "data/tilesets/misc/121/tiles.4bpp"
	gMiscTilesetGraphics_121_Palettes:

gMiscTilesetGraphics_122:
	.incbin "data/tilesets/misc/122/tiles.4bpp"
	gMiscTilesetGraphics_122_Palettes:

gMiscTilesetGraphics_123:
	.incbin "data/tilesets/misc/123/tiles.4bpp"
	gMiscTilesetGraphics_123_Palettes:

gMiscTilesetGraphics_124:
	.incbin "data/tilesets/misc/124/tiles.4bpp"
	gMiscTilesetGraphics_124_Palettes:

gMiscTilesetGraphics_125:
	.incbin "data/tilesets/misc/125/tiles.4bpp"
	gMiscTilesetGraphics_125_Palettes:

gMiscTilesetGraphics_126:
	.incbin "data/tilesets/misc/126/tiles.4bpp"
	gMiscTilesetGraphics_126_Palettes:

gMiscTilesetGraphics_127:
	.incbin "data/tilesets/misc/127/tiles.4bpp"
	gMiscTilesetGraphics_127_Palettes:

gMiscTilesetGraphics_128:
	.incbin "data/tilesets/misc/128/tiles.4bpp"
	gMiscTilesetGraphics_128_Palettes:

gMiscTilesetGraphics_129:
	.incbin "data/tilesets/misc/129/tiles.4bpp"
	gMiscTilesetGraphics_129_Palettes:

gMiscTilesetGraphics_130:
	.incbin "data/tilesets/misc/130/tiles.4bpp"
	gMiscTilesetGraphics_130_Palettes:

gMiscTilesetGraphics_131:
	.incbin "data/tilesets/misc/131/tiles.4bpp"
	gMiscTilesetGraphics_131_Palettes:

gMiscTilesetGraphics_132:
	.incbin "data/tilesets/misc/132/tiles.4bpp"
	gMiscTilesetGraphics_132_Palettes:

gMiscTilesetGraphics_133:
	.incbin "data/tilesets/misc/133/tiles.4bpp"
	gMiscTilesetGraphics_133_Palettes:

gMiscTilesetGraphics_134:
	.incbin "data/tilesets/misc/134/tiles.4bpp"
	gMiscTilesetGraphics_134_Palettes:

gMiscTilesetGraphics_135:
	.incbin "data/tilesets/misc/135/tiles.4bpp"
	gMiscTilesetGraphics_135_Palettes:

gMiscTilesetGraphics_136:
	.incbin "data/tilesets/misc/136/tiles.4bpp"
	gMiscTilesetGraphics_136_Palettes:

gMiscTilesetGraphics_137:
	.incbin "data/tilesets/misc/137/tiles.4bpp"
	gMiscTilesetGraphics_137_Palettes:

gMiscTilesetGraphics_138:
	.incbin "data/tilesets/misc/138/tiles.4bpp"
	gMiscTilesetGraphics_138_Palettes:

gMiscTilesetGraphics_139:
	.incbin "data/tilesets/misc/139/tiles.4bpp"
	gMiscTilesetGraphics_139_Palettes:

gMiscTilesetGraphics_140:
	.incbin "data/tilesets/misc/140/tiles.4bpp"
	gMiscTilesetGraphics_140_Palettes:

gMiscTilesetGraphics_141:
	.incbin "data/tilesets/misc/141/tiles.4bpp"
	gMiscTilesetGraphics_141_Palettes:

gMiscTilesetGraphics_142:
	.incbin "data/tilesets/misc/142/tiles.4bpp"
	gMiscTilesetGraphics_142_Palettes:

gMiscTilesetGraphics_143:
	.incbin "data/tilesets/misc/143/tiles.4bpp"
	gMiscTilesetGraphics_143_Palettes:

gMiscTilesetGraphics_144:
	.incbin "data/tilesets/misc/144/tiles.4bpp"
	gMiscTilesetGraphics_144_Palettes:

gMiscTilesetGraphics_145:
	.incbin "data/tilesets/misc/145/tiles.4bpp"
	gMiscTilesetGraphics_145_Palettes:

gMiscTilesetGraphics_146:
	.incbin "data/tilesets/misc/146/tiles.4bpp"
	gMiscTilesetGraphics_146_Palettes:

gMiscTilesetGraphics_147:
	.incbin "data/tilesets/misc/147/tiles.4bpp"
	gMiscTilesetGraphics_147_Palettes:

gMiscTilesetGraphics_148:
	.incbin "data/tilesets/misc/148/tiles.4bpp"
	gMiscTilesetGraphics_148_Palettes:

gMiscTilesetGraphics_149:
	.incbin "data/tilesets/misc/149/tiles.4bpp"
	gMiscTilesetGraphics_149_Palettes:

gMiscTilesetGraphics_150:
	.incbin "data/tilesets/misc/150/tiles.4bpp"
	gMiscTilesetGraphics_150_Palettes:

gMiscTilesetGraphics_151:
	.incbin "data/tilesets/misc/151/tiles.4bpp"
	gMiscTilesetGraphics_151_Palettes:

gMiscTilesetGraphics_152:
	.incbin "data/tilesets/misc/152/tiles.4bpp"
	gMiscTilesetGraphics_152_Palettes:

gMiscTilesetGraphics_153:
	.incbin "data/tilesets/misc/153/tiles.4bpp"
	gMiscTilesetGraphics_153_Palettes:

gMiscTilesetGraphics_154:
	.incbin "data/tilesets/misc/154/tiles.4bpp"
	gMiscTilesetGraphics_154_Palettes:

gMiscTilesetGraphics_155:
	.incbin "data/tilesets/misc/155/tiles.4bpp"
	gMiscTilesetGraphics_155_Palettes:

gMiscTilesetGraphics_156:
	.incbin "data/tilesets/misc/156/tiles.4bpp"
	gMiscTilesetGraphics_156_Palettes:

gMiscTilesetGraphics_157:
	.incbin "data/tilesets/misc/157/tiles.4bpp"
	gMiscTilesetGraphics_157_Palettes:

gMiscTilesetGraphics_158:
	.incbin "data/tilesets/misc/158/tiles.4bpp"
	gMiscTilesetGraphics_158_Palettes:

gMiscTilesetGraphics_159:
	.incbin "data/tilesets/misc/159/tiles.4bpp"
	gMiscTilesetGraphics_159_Palettes:

gMiscTilesetGraphics_160:
	.incbin "data/tilesets/misc/160/tiles.4bpp"
	gMiscTilesetGraphics_160_Palettes:

gMiscTilesetGraphics_161:
	.incbin "data/tilesets/misc/161/tiles.4bpp"
	gMiscTilesetGraphics_161_Palettes:

gMiscTilesetGraphics_162:
	.incbin "data/tilesets/misc/162/tiles.4bpp"
	gMiscTilesetGraphics_162_Palettes:

gMiscTilesetGraphics_163:
	.incbin "data/tilesets/misc/163/tiles.4bpp"
	gMiscTilesetGraphics_163_Palettes:

gMiscTilesetGraphics_164:
	.incbin "data/tilesets/misc/164/tiles.4bpp"
	gMiscTilesetGraphics_164_Palettes:

gMiscTilesetGraphics_165:
	.incbin "data/tilesets/misc/165/tiles.4bpp"
	gMiscTilesetGraphics_165_Palettes:

gMiscTilesetGraphics_166:
	.incbin "data/tilesets/misc/166/tiles.4bpp"
	gMiscTilesetGraphics_166_Palettes:

gMiscTilesetGraphics_167:
	.incbin "data/tilesets/misc/167/tiles.4bpp"
	gMiscTilesetGraphics_167_Palettes:

gMiscTilesetGraphics_168:
	.incbin "data/tilesets/misc/168/tiles.4bpp"
	gMiscTilesetGraphics_168_Palettes:

gMiscTilesetGraphics_169:
	.incbin "data/tilesets/misc/169/tiles.4bpp"
	gMiscTilesetGraphics_169_Palettes:

gMiscTilesetGraphics_170:
	.incbin "data/tilesets/misc/170/tiles.4bpp"
	gMiscTilesetGraphics_170_Palettes:

gMiscTilesetGraphics_171:
	.incbin "data/tilesets/misc/171/tiles.4bpp"
	gMiscTilesetGraphics_171_Palettes:

gMiscTilesetGraphics_172:
	.incbin "data/tilesets/misc/172/tiles.4bpp"
	gMiscTilesetGraphics_172_Palettes:

gMiscTilesetGraphics_173:
	.incbin "data/tilesets/misc/173/tiles.4bpp"
	gMiscTilesetGraphics_173_Palettes:

gMiscTilesetGraphics_174:
	.incbin "data/tilesets/misc/174/tiles.4bpp"
	gMiscTilesetGraphics_174_Palettes:

gMiscTilesetGraphics_175:
	.incbin "data/tilesets/misc/175/tiles.4bpp"
	gMiscTilesetGraphics_175_Palettes:

gMiscTilesetGraphics_176:
	.incbin "data/tilesets/misc/176/tiles.4bpp"
	gMiscTilesetGraphics_176_Palettes:

