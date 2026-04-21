  .include "asm/macros.inc"

.section .rodata
.balign 4, 0

.global gDialogGraphics
gDialogGraphics:
	@ Graphic 0
	.4byte gDialogGraphics_0-. @ src
	.4byte 156 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gDialogGraphics_1-. @ src
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, LZ77 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_1_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gDialogGraphics_2-. @ src
	.4byte 868 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gDialogGraphics_3-. @ src
	.4byte 868 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gDialogGraphics_4-. @ src
	.4byte 904 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gDialogGraphics_5-. @ src
	.4byte 936 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gDialogGraphics_6-. @ src
	.4byte 760 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gDialogGraphics_7-. @ src
	.4byte 988 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gDialogGraphics_8-. @ src
	.4byte 756 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gDialogGraphics_9-. @ src
	.4byte 808 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gDialogGraphics_10-. @ src
	.4byte 876 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gDialogGraphics_11-. @ src
	.4byte 1096 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gDialogGraphics_12-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gDialogGraphics_13-. @ src
	.4byte 872 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gDialogGraphics_14-. @ src
	.4byte 940 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gDialogGraphics_15-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gDialogGraphics_16-. @ src
	.4byte 1020 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gDialogGraphics_17-. @ src
	.4byte 1144 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gDialogGraphics_18-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gDialogGraphics_19-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gDialogGraphics_20-. @ src
	.4byte 956 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gDialogGraphics_21-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 22
	.4byte gDialogGraphics_22-. @ src
	.4byte 940 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 23
	.4byte gDialogGraphics_23-. @ src
	.4byte 952 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 24
	.4byte gDialogGraphics_24-. @ src
	.4byte 1040 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 25
	.4byte gDialogGraphics_25-. @ src
	.4byte 968 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 26
	.4byte gDialogGraphics_26-. @ src
	.4byte 748 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 27
	.4byte gDialogGraphics_27-. @ src
	.4byte 900 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 28
	.4byte gDialogGraphics_28-. @ src
	.4byte 1136 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 29
	.4byte gDialogGraphics_29-. @ src
	.4byte 1164 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 30
	.4byte gDialogGraphics_30-. @ src
	.4byte 1008 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 31
	.4byte gDialogGraphics_31-. @ src
	.4byte 912 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 32
	.4byte gDialogGraphics_32-. @ src
	.4byte 936 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 33
	.4byte gDialogGraphics_33-. @ src
	.4byte 936 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 34
	.4byte gDialogGraphics_34-. @ src
	.4byte 836 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 35
	.4byte gDialogGraphics_35-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 36
	.4byte gDialogGraphics_36-. @ src
	.4byte 944 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 37
	.4byte gDialogGraphics_37-. @ src
	.4byte 876 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 38
	.4byte gDialogGraphics_38-. @ src
	.4byte 912 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 39
	.4byte gDialogGraphics_39-. @ src
	.4byte 772 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 40
	.4byte gDialogGraphics_40-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 41
	.4byte gDialogGraphics_41-. @ src
	.4byte 1112 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 42
	.4byte gDialogGraphics_42-. @ src
	.4byte 900 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 43
	.4byte gDialogGraphics_43-. @ src
	.4byte 796 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 44
	.4byte gDialogGraphics_44-. @ src
	.4byte 772 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 45
	.4byte gDialogGraphics_45-. @ src
	.4byte 856 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 46
	.4byte gDialogGraphics_46-. @ src
	.4byte 848 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 47
	.4byte gDialogGraphics_47-. @ src
	.4byte 884 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 48
	.4byte gDialogGraphics_48-. @ src
	.4byte 952 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 49
	.4byte gDialogGraphics_49-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 50
	.4byte gDialogGraphics_50-. @ src
	.4byte 564 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 51
	.4byte gDialogGraphics_51-. @ src
	.4byte 1112 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 52
	.4byte gDialogGraphics_52-. @ src
	.4byte 1136 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 53
	.4byte gDialogGraphics_53-. @ src
	.4byte 648 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_53_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 54
	.4byte gDialogGraphics_54-. @ src
	.4byte 820 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 55
	.4byte gDialogGraphics_55-. @ src
	.4byte 860 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 56
	.4byte gDialogGraphics_56-. @ src
	.4byte 920 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 57
	.4byte gDialogGraphics_57-. @ src
	.4byte 868 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 58
	.4byte gDialogGraphics_58-. @ src
	.4byte 148 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 59
	.4byte gDialogGraphics_59-. @ src
	.4byte 204 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 60
	.4byte gDialogGraphics_60-. @ src
	.4byte 216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 61
	.4byte gDialogGraphics_61-. @ src
	.4byte 228 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 62
	.4byte gDialogGraphics_62-. @ src
	.4byte 244 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 63
	.4byte gDialogGraphics_63-. @ src
	.4byte 268 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 64
	.4byte gDialogGraphics_64-. @ src
	.4byte 228 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 65
	.4byte gDialogGraphics_65-. @ src
	.4byte 220 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte gDialogGraphics_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gDialogGraphics_0:
	.incbin "graphics/dialog/msgbox/0.lz"
	gDialogGraphics_0_Palettes:
	.incbin "graphics/dialog/msgbox/0.lz.gbapal"

gDialogGraphics_1:
	gDialogGraphics_1_Palettes:

gDialogGraphics_2:
	.incbin "graphics/dialog/mugshot/zero.lz"
	gDialogGraphics_2_Palettes:
	.incbin "graphics/dialog/mugshot/zero.lz.gbapal"

gDialogGraphics_3:
	.incbin "graphics/dialog/mugshot/blazin.lz"
	gDialogGraphics_3_Palettes:
	.incbin "graphics/dialog/mugshot/blazin.lz.gbapal"

gDialogGraphics_4:
	.incbin "graphics/dialog/mugshot/childre.lz"
	gDialogGraphics_4_Palettes:
	.incbin "graphics/dialog/mugshot/childre.lz.gbapal"

gDialogGraphics_5:
	.incbin "graphics/dialog/mugshot/hellbat.lz"
	gDialogGraphics_5_Palettes:
	.incbin "graphics/dialog/mugshot/hellbat.lz.gbapal"

gDialogGraphics_6:
	.incbin "graphics/dialog/mugshot/deathtanz.lz"
	gDialogGraphics_6_Palettes:
	.incbin "graphics/dialog/mugshot/deathtanz.lz.gbapal"

gDialogGraphics_7:
	.incbin "graphics/dialog/mugshot/cubit.lz"
	gDialogGraphics_7_Palettes:
	.incbin "graphics/dialog/mugshot/cubit.lz.gbapal"

gDialogGraphics_8:
	.incbin "graphics/dialog/mugshot/glacierle.lz"
	gDialogGraphics_8_Palettes:
	.incbin "graphics/dialog/mugshot/glacierle.lz.gbapal"

gDialogGraphics_9:
	.incbin "graphics/dialog/mugshot/volteel.lz"
	gDialogGraphics_9_Palettes:
	.incbin "graphics/dialog/mugshot/volteel.lz.gbapal"

gDialogGraphics_10:
	.incbin "graphics/dialog/mugshot/tretista.lz"
	gDialogGraphics_10_Palettes:
	.incbin "graphics/dialog/mugshot/tretista.lz.gbapal"

gDialogGraphics_11:
	.incbin "graphics/dialog/mugshot/blazin_human.lz"
	gDialogGraphics_11_Palettes:
	.incbin "graphics/dialog/mugshot/blazin_human.lz.gbapal"

gDialogGraphics_12:
	.incbin "graphics/dialog/mugshot/childre_human.lz"
	gDialogGraphics_12_Palettes:
	.incbin "graphics/dialog/mugshot/childre_human.lz.gbapal"

gDialogGraphics_13:
	.incbin "graphics/dialog/mugshot/hellbat_human.lz"
	gDialogGraphics_13_Palettes:
	.incbin "graphics/dialog/mugshot/hellbat_human.lz.gbapal"

gDialogGraphics_14:
	.incbin "graphics/dialog/mugshot/deathtanz_human.lz"
	gDialogGraphics_14_Palettes:
	.incbin "graphics/dialog/mugshot/deathtanz_human.lz.gbapal"

gDialogGraphics_15:
	.incbin "graphics/dialog/mugshot/cubit_human.lz"
	gDialogGraphics_15_Palettes:
	.incbin "graphics/dialog/mugshot/cubit_human.lz.gbapal"

gDialogGraphics_16:
	.incbin "graphics/dialog/mugshot/glacierle_human.lz"
	gDialogGraphics_16_Palettes:
	.incbin "graphics/dialog/mugshot/glacierle_human.lz.gbapal"

gDialogGraphics_17:
	.incbin "graphics/dialog/mugshot/volteel_human.lz"
	gDialogGraphics_17_Palettes:
	.incbin "graphics/dialog/mugshot/volteel_human.lz.gbapal"

gDialogGraphics_18:
	.incbin "graphics/dialog/mugshot/tretista_human.lz"
	gDialogGraphics_18_Palettes:
	.incbin "graphics/dialog/mugshot/tretista_human.lz.gbapal"

gDialogGraphics_19:
	.incbin "graphics/dialog/mugshot/anubis.lz"
	gDialogGraphics_19_Palettes:
	.incbin "graphics/dialog/mugshot/anubis.lz.gbapal"

gDialogGraphics_20:
	.incbin "graphics/dialog/mugshot/hanumachine.lz"
	gDialogGraphics_20_Palettes:
	.incbin "graphics/dialog/mugshot/hanumachine.lz.gbapal"

gDialogGraphics_21:
	.incbin "graphics/dialog/mugshot/blizzack.lz"
	gDialogGraphics_21_Palettes:
	.incbin "graphics/dialog/mugshot/blizzack.lz.gbapal"

gDialogGraphics_22:
	.incbin "graphics/dialog/mugshot/harpuia.lz"
	gDialogGraphics_22_Palettes:
	.incbin "graphics/dialog/mugshot/harpuia.lz.gbapal"

gDialogGraphics_23:
	.incbin "graphics/dialog/mugshot/leviathan.lz"
	gDialogGraphics_23_Palettes:
	.incbin "graphics/dialog/mugshot/leviathan.lz.gbapal"

gDialogGraphics_24:
	.incbin "graphics/dialog/mugshot/fefnir.lz"
	gDialogGraphics_24_Palettes:
	.incbin "graphics/dialog/mugshot/fefnir.lz.gbapal"

gDialogGraphics_25:
	.incbin "graphics/dialog/mugshot/phantom.lz"
	gDialogGraphics_25_Palettes:
	.incbin "graphics/dialog/mugshot/phantom.lz.gbapal"

gDialogGraphics_26:
	.incbin "graphics/dialog/mugshot/x.lz"
	gDialogGraphics_26_Palettes:
	.incbin "graphics/dialog/mugshot/x.lz.gbapal"

gDialogGraphics_27:
	.incbin "graphics/dialog/mugshot/copy_x.lz"
	gDialogGraphics_27_Palettes:
	.incbin "graphics/dialog/mugshot/copy_x.lz.gbapal"

gDialogGraphics_28:
	.incbin "graphics/dialog/mugshot/mother_elf.lz"
	gDialogGraphics_28_Palettes:
	.incbin "graphics/dialog/mugshot/mother_elf.lz.gbapal"

gDialogGraphics_29:
	.incbin "graphics/dialog/mugshot/weil.lz"
	gDialogGraphics_29_Palettes:
	.incbin "graphics/dialog/mugshot/weil.lz.gbapal"

gDialogGraphics_30:
	.incbin "graphics/dialog/mugshot/omega_white.lz"
	gDialogGraphics_30_Palettes:
	.incbin "graphics/dialog/mugshot/omega_white.lz.gbapal"

gDialogGraphics_31:
	.incbin "graphics/dialog/mugshot/omega_gold.lz"
	gDialogGraphics_31_Palettes:
	.incbin "graphics/dialog/mugshot/omega_gold.lz.gbapal"

gDialogGraphics_32:
	.incbin "graphics/dialog/mugshot/ciel.lz"
	gDialogGraphics_32_Palettes:
	.incbin "graphics/dialog/mugshot/ciel.lz.gbapal"

gDialogGraphics_33:
	.incbin "graphics/dialog/mugshot/cerveau.lz"
	gDialogGraphics_33_Palettes:
	.incbin "graphics/dialog/mugshot/cerveau.lz.gbapal"

gDialogGraphics_34:
	.incbin "graphics/dialog/mugshot/alouette.lz"
	gDialogGraphics_34_Palettes:
	.incbin "graphics/dialog/mugshot/alouette.lz.gbapal"

gDialogGraphics_35:
	.incbin "graphics/dialog/mugshot/andrew.lz"
	gDialogGraphics_35_Palettes:
	.incbin "graphics/dialog/mugshot/andrew.lz.gbapal"

gDialogGraphics_36:
	.incbin "graphics/dialog/mugshot/hibou.lz"
	gDialogGraphics_36_Palettes:
	.incbin "graphics/dialog/mugshot/hibou.lz.gbapal"

gDialogGraphics_37:
	.incbin "graphics/dialog/mugshot/rocinolle.lz"
	gDialogGraphics_37_Palettes:
	.incbin "graphics/dialog/mugshot/rocinolle.lz.gbapal"

gDialogGraphics_38:
	.incbin "graphics/dialog/mugshot/perroquiet.lz"
	gDialogGraphics_38_Palettes:
	.incbin "graphics/dialog/mugshot/perroquiet.lz.gbapal"

gDialogGraphics_39:
	.incbin "graphics/dialog/mugshot/menart.lz"
	gDialogGraphics_39_Palettes:
	.incbin "graphics/dialog/mugshot/menart.lz.gbapal"

gDialogGraphics_40:
	.incbin "graphics/dialog/mugshot/doigt.lz"
	gDialogGraphics_40_Palettes:
	.incbin "graphics/dialog/mugshot/doigt.lz.gbapal"

gDialogGraphics_41:
	.incbin "graphics/dialog/mugshot/weil_monitor.lz"
	gDialogGraphics_41_Palettes:
	.incbin "graphics/dialog/mugshot/weil_monitor.lz.gbapal"

gDialogGraphics_42:
	.incbin "graphics/dialog/mugshot/autruche.lz"
	gDialogGraphics_42_Palettes:
	.incbin "graphics/dialog/mugshot/autruche.lz.gbapal"

gDialogGraphics_43:
	.incbin "graphics/dialog/mugshot/pic.lz"
	gDialogGraphics_43_Palettes:
	.incbin "graphics/dialog/mugshot/pic.lz.gbapal"

gDialogGraphics_44:
	.incbin "graphics/dialog/mugshot/hirondelle.lz"
	gDialogGraphics_44_Palettes:
	.incbin "graphics/dialog/mugshot/hirondelle.lz.gbapal"

gDialogGraphics_45:
	.incbin "graphics/dialog/mugshot/faucon.lz"
	gDialogGraphics_45_Palettes:
	.incbin "graphics/dialog/mugshot/faucon.lz.gbapal"

gDialogGraphics_46:
	.incbin "graphics/dialog/mugshot/kiss.lz"
	gDialogGraphics_46_Palettes:
	.incbin "graphics/dialog/mugshot/kiss.lz.gbapal"

gDialogGraphics_47:
	.incbin "graphics/dialog/mugshot/brain.lz"
	gDialogGraphics_47_Palettes:
	.incbin "graphics/dialog/mugshot/brain.lz.gbapal"

gDialogGraphics_48:
	.incbin "graphics/dialog/mugshot/joan.lz"
	gDialogGraphics_48_Palettes:
	.incbin "graphics/dialog/mugshot/joan.lz.gbapal"

gDialogGraphics_49:
	.incbin "graphics/dialog/mugshot/rouge.lz"
	gDialogGraphics_49_Palettes:
	.incbin "graphics/dialog/mugshot/rouge.lz.gbapal"

gDialogGraphics_50:
	.incbin "graphics/dialog/mugshot/sound_only.lz"
	gDialogGraphics_50_Palettes:
	.incbin "graphics/dialog/mugshot/sound_only.lz.gbapal"

gDialogGraphics_51:
	.incbin "graphics/dialog/mugshot/crea.lz"
	gDialogGraphics_51_Palettes:
	.incbin "graphics/dialog/mugshot/crea.lz.gbapal"

gDialogGraphics_52:
	.incbin "graphics/dialog/mugshot/prea.lz"
	gDialogGraphics_52_Palettes:
	.incbin "graphics/dialog/mugshot/prea.lz.gbapal"

gDialogGraphics_53:
	.incbin "graphics/dialog/mugshot/sound_only2.lz"
	gDialogGraphics_53_Palettes:
	.incbin "graphics/dialog/mugshot/sound_only2.lz.gbapal"

gDialogGraphics_54:
	.incbin "graphics/dialog/mugshot/colbor.lz"
	gDialogGraphics_54_Palettes:
	.incbin "graphics/dialog/mugshot/colbor.lz.gbapal"

gDialogGraphics_55:
	.incbin "graphics/dialog/mugshot/copy_x_armor.lz"
	gDialogGraphics_55_Palettes:
	.incbin "graphics/dialog/mugshot/copy_x_armor.lz.gbapal"

gDialogGraphics_56:
	.incbin "graphics/dialog/mugshot/ciel_blur.lz"
	gDialogGraphics_56_Palettes:
	.incbin "graphics/dialog/mugshot/ciel_blur.lz.gbapal"

gDialogGraphics_57:
	.incbin "graphics/dialog/mugshot/omega_zero.lz"
	gDialogGraphics_57_Palettes:
	.incbin "graphics/dialog/mugshot/omega_zero.lz.gbapal"

gDialogGraphics_58:
	.incbin "graphics/dialog/msgbox/1.lz"
	gDialogGraphics_58_Palettes:
	.incbin "graphics/dialog/msgbox/1.lz.gbapal"

gDialogGraphics_59:
	.incbin "graphics/dialog/msgbox/2.lz"
	gDialogGraphics_59_Palettes:
	.incbin "graphics/dialog/msgbox/2.lz.gbapal"

gDialogGraphics_60:
	.incbin "graphics/dialog/msgbox/3.lz"
	gDialogGraphics_60_Palettes:
	.incbin "graphics/dialog/msgbox/3.lz.gbapal"

gDialogGraphics_61:
	.incbin "graphics/dialog/msgbox/4.lz"
	gDialogGraphics_61_Palettes:
	.incbin "graphics/dialog/msgbox/4.lz.gbapal"

gDialogGraphics_62:
	.incbin "graphics/dialog/msgbox/5.lz"
	gDialogGraphics_62_Palettes:
	.incbin "graphics/dialog/msgbox/5.lz.gbapal"

gDialogGraphics_63:
	.incbin "graphics/dialog/msgbox/6.lz"
	gDialogGraphics_63_Palettes:
	.incbin "graphics/dialog/msgbox/6.lz.gbapal"

gDialogGraphics_64:
	.incbin "graphics/dialog/msgbox/7.lz"
	gDialogGraphics_64_Palettes:
	.incbin "graphics/dialog/msgbox/7.lz.gbapal"

gDialogGraphics_65:
	.incbin "graphics/dialog/msgbox/8.lz"
	gDialogGraphics_65_Palettes:
	.incbin "graphics/dialog/msgbox/8.lz.gbapal"

