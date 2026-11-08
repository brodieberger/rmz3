@ The AP sprite sheet table

.include "asm/macros.inc"

.if AP

.section .rodata
.balign 4, 0

.global gApSheetGraphics
gApSheetGraphics:
	@ Sheet 0: enemy/z2_hopper, Zero 2 SM20
	.4byte gApSheet_0-. @ src
	.4byte 2624 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 656, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 1: enemy/z2_hive, Zero 2 SM94
	.4byte gApSheet_1-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 2: enemy/z2_hottalook, Zero 2 SM93
	.4byte gApSheet_2-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 3: enemy/z2_soldier, Zero 2 SM88
	.4byte gApSheet_3-. @ src
	.4byte 2144 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 536, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 4: enemy/z2_carryarm, Zero 2 SM118
	.4byte gApSheet_4-. @ src
	.4byte 3840 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 960, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 5: enemy/z2_signaloid, Zero 2 SM21
	.4byte gApSheet_5-. @ src
	.4byte 5504 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1376, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_5_Palettes-. @ src offset
		.2byte 64 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 6: boss/z2_golem, Zero 2 SM30
	.4byte gApSheet_6-. @ src
	.4byte 5760 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1440, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 7: boss/z2_golem/arm, Zero 2 SM31
	.4byte gApSheet_7-. @ src
	.4byte 7168 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1792, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 8: boss/z2_golem/laser, Zero 2 SM32
	.4byte gApSheet_8-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_8_Palettes-. @ src offset
		.2byte 64 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 9: boss/z2_golem/foot, Zero 2 SM33
	.4byte gApSheet_9-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 10: boss/z2_harpuia/shots, Zero 2 SM41
	.4byte gApSheet_10-. @ src
	.4byte 4672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 11: boss/z2_harpuia/blade, Zero 2 SM42
	.4byte gApSheet_11-. @ src
	.4byte 256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 12: enemy/z2_copter, Zero 2 SM13
	.4byte gApSheet_12-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 13: enemy/z2_eye, Zero 2 SM144
	.4byte gApSheet_13-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 14: enemy/z2_leaper, Zero 2 SM119
	.4byte gApSheet_14-. @ src
	.4byte 576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 15: enemy/z2_barrier_ship, Zero 2 SM156
	.4byte gApSheet_15-. @ src
	.4byte 3200 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 800, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 16: enemy/z2_snowballer, Zero 2 SM142
	.4byte gApSheet_16-. @ src
	.4byte 4352 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1088, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 17: enemy/z2_ring_cannon, Zero 2 SM23
	.4byte gApSheet_17-. @ src
	.4byte 3776 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 944, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 18: enemy/z2_shield_guard, Zero 2 SM8
	.4byte gApSheet_18-. @ src
	.4byte 4576 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 19: enemy/z2_bee, Zero 2 SM10
	.4byte gApSheet_19-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 20: enemy/z2_bee_carrier, Zero 2 SM11
	.4byte gApSheet_20-. @ src
	.4byte 736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 21: enemy/z2_mole, Zero 2 SM84
	.4byte gApSheet_21-. @ src
	.4byte 2208 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 22: enemy/z2_tower, Zero 2 SM7
	.4byte gApSheet_22-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_22_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 23: enemy/z2_spikeball, Zero 2 SM6
	.4byte gApSheet_23-. @ src
	.4byte 2304 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 576, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_23_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 24: enemy/z2_shell, Zero 2 SM157
	.4byte gApSheet_24-. @ src
	.4byte 2016 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 504, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_24_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 25: enemy/z2_wolf, Zero 2 SM117
	.4byte gApSheet_25-. @ src
	.4byte 4800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_25_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 26: enemy/z2_flower, Zero 2 SM102
	.4byte gApSheet_26-. @ src
	.4byte 960 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_26_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 27: enemy/z2_spider, Zero 2 SM116
	.4byte gApSheet_27-. @ src
	.4byte 4160 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1040, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_27_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 28: enemy/z2_vulture, Zero 2 SM95
	.4byte gApSheet_28-. @ src
	.4byte 5184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1296, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_28_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 29: enemy/z2_crab, Zero 2 SM114
	.4byte gApSheet_29-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_29_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 30: boss/z2_boss0, Zero 2 SM4
	.4byte gApSheet_30-. @ src
	.4byte 6880 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1720, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_30_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 31: boss/z2_boss0/b, Zero 2 SM5
	.4byte gApSheet_31-. @ src
	.4byte 6848 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1712, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_31_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 32: solid/z2_sand_block, Zero 2 SM12
	.4byte gApSheet_32-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_32_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 33: vfx/z2_rocks, Zero 2 SM62
	.4byte gApSheet_33-. @ src
	.4byte 544 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_33_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 34: solid/z2_slab, Zero 2 SM151
	.4byte gApSheet_34-. @ src
	.4byte 256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_34_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 35: solid/z2_gate, Zero 2 SM150
	.4byte gApSheet_35-. @ src
	.4byte 704 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_35_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 36: enemy/z2_pylon, Zero 2 SM17
	.4byte gApSheet_36-. @ src
	.4byte 864 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_36_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 37: enemy/z2_dozer, Zero 2 SM24
	.4byte gApSheet_37-. @ src
	.4byte 2208 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_37_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 38: enemy/z2_ice_block, Zero 2 SM25
	.4byte gApSheet_38-. @ src
	.4byte 2048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_38_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 39: enemy/z2_fish, Zero 2 SM110
	.4byte gApSheet_39-. @ src
	.4byte 3552 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 888, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_39_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 40: enemy/z2_mine, Zero 2 SM73
	.4byte gApSheet_40-. @ src
	.4byte 2208 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_40_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 41: boss/z2_fefnir/tank, Zero 2 SM80
	.4byte gApSheet_41-. @ src
	.4byte 8608 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 2152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_41_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 42: boss/z2_fefnir/wheels, Zero 2 SM81
	.4byte gApSheet_42-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_42_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 43: boss/z2_fefnir/ball, Zero 2 SM81
	.4byte gApSheet_43-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_43_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 44: boss/z2_fefnir/flash, Zero 2 SM82
	.4byte gApSheet_44-. @ src
	.4byte 256 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_44_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 45: boss/z2_fefnir/fire, Zero 2 SM82
	.4byte gApSheet_45-. @ src
	.4byte 6176 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1544, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_45_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 46: boss/z2_fefnir/summon, Zero 2 SM155
	.4byte gApSheet_46-. @ src
	.4byte 672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_46_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 47: solid/z2_floe, Zero 2 SM112
	.4byte gApSheet_47-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_47_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 48: boss/z2_leviathan/ice, Zero 2 SM92
	.4byte gApSheet_48-. @ src
	.4byte 7136 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1784, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_48_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 49: boss/z2_blob/drop, Zero 2 SM53
	.4byte gApSheet_49-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_49_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 50: boss/z2_blob/splat, Zero 2 SM54
	.4byte gApSheet_50-. @ src
	.4byte 2784 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 696, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_50_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 51: boss/z2_blob/rock, Zero 2 SM83
	.4byte gApSheet_51-. @ src
	.4byte 288 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 72, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_51_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 52: boss/z2_flame_golem, Zero 2 SM34
	.4byte gApSheet_52-. @ src
	.4byte 7328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_52_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 53: boss/z2_flame_golem/fire, Zero 2 SM35
	.4byte gApSheet_53-. @ src
	.4byte 8064 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 2016, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_53_Palettes-. @ src offset
		.2byte 64 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 54: boss/z2_flame_golem/foot, Zero 2 SM36
	.4byte gApSheet_54-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_54_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 55: boss/z2_frost_golem, Zero 2 SM37
	.4byte gApSheet_55-. @ src
	.4byte 7200 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1800, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_55_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 56: boss/z2_frost_golem/ice, Zero 2 SM38
	.4byte gApSheet_56-. @ src
	.4byte 7680 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1920, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_56_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 57: boss/z2_frost_golem/foot, Zero 2 SM39
	.4byte gApSheet_57-. @ src
	.4byte 512 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_57_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 58: solid/z2_door, Zero 2 SM103
	.4byte gApSheet_58-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_58_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 59: solid/z2_door/open, Zero 2 SM103
	.4byte gApSheet_59-. @ src
	.4byte 1216 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_59_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 60: solid/z2_fallen, Zero 2 SM226
	.4byte gApSheet_60-. @ src
	.4byte 1024 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_60_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 61: solid/z2_pad, Zero 2 SM135
	.4byte gApSheet_61-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_61_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 62: solid/z2_lift, Zero 2 SM111
	.4byte gApSheet_62-. @ src
	.4byte 992 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_62_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 63: solid/z2_box, Zero 2 SM108
	.4byte gApSheet_63-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_63_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 64: solid/z2_rescue, Zero 2 SM159
	.4byte gApSheet_64-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_64_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 65: solid/z2_rescue/run, Zero 2 SM158
	.4byte gApSheet_65-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_65_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 66: solid/z2_baby_elf, Zero 2 SM133
	.4byte gApSheet_66-. @ src
	.4byte 640 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_66_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 67: solid/z2_x, Zero 2 SM141
	.4byte gApSheet_67-. @ src
	.4byte 4000 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1000, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_67_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 68: boss/z2_wall/splash, Zero 2 SM96
	.4byte gApSheet_68-. @ src
	.4byte 5632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_68_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 69: boss/z2_wall/part, Zero 2 SM98
	.4byte gApSheet_69-. @ src
	.4byte 1280 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_69_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 70: boss/z2_wall/arm, Zero 2 SM98
	.4byte gApSheet_70-. @ src
	.4byte 1728 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_70_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 71: boss/z2_wall, Zero 2 SM99
	.4byte gApSheet_71-. @ src
	.4byte 1792 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_71_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 72: boss/z2_wall/spike, Zero 2 SM100
	.4byte gApSheet_72-. @ src
	.4byte 3072 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 768, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_72_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 73: boss/z2_wall/shot, Zero 2 SM97
	.4byte gApSheet_73-. @ src
	.4byte 2208 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_73_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 74: boss/z2_wall/shelf, Zero 2 SM101
	.4byte gApSheet_74-. @ src
	.4byte 1088 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_74_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 75: solid/z2_cast/harpuia, Zero 2 SM220
	.4byte gApSheet_75-. @ src
	.4byte 2016 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 504, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_75_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 76: solid/z2_cast/fefnir, Zero 2 SM221
	.4byte gApSheet_76-. @ src
	.4byte 4736 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_76_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Sheet 77: solid/z2_cast/leviathan, Zero 2 SM222
	.4byte gApSheet_77-. @ src
	.4byte 1152 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gApSheet_77_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

.global gApSheetMetaspriteTable
gApSheetMetaspriteTable:
  .word gStaticMetaSprite_enemy_z2_hopper
  .word gStaticMetaSprite_enemy_z2_hive
  .word gStaticMetaSprite_enemy_z2_hottalook
  .word gStaticMetaSprite_enemy_z2_soldier
  .word gStaticMetaSprite_enemy_z2_carryarm
  .word gStaticMetaSprite_enemy_z2_signaloid
  .word gStaticMetaSprite_boss_z2_golem
  .word gStaticMetaSprite_boss_z2_golem_arm
  .word gStaticMetaSprite_boss_z2_golem_laser
  .word gStaticMetaSprite_boss_z2_golem_foot
  .word gStaticMetaSprite_boss_z2_harpuia_shots
  .word gStaticMetaSprite_boss_z2_harpuia_blade
  .word gStaticMetaSprite_enemy_z2_copter
  .word gStaticMetaSprite_enemy_z2_eye
  .word gStaticMetaSprite_enemy_z2_leaper
  .word gStaticMetaSprite_enemy_z2_barrier_ship
  .word gStaticMetaSprite_enemy_z2_snowballer
  .word gStaticMetaSprite_enemy_z2_ring_cannon
  .word gStaticMetaSprite_enemy_z2_shield_guard
  .word gStaticMetaSprite_enemy_z2_bee
  .word gStaticMetaSprite_enemy_z2_bee_carrier
  .word gStaticMetaSprite_enemy_z2_mole
  .word gStaticMetaSprite_enemy_z2_tower
  .word gStaticMetaSprite_enemy_z2_spikeball
  .word gStaticMetaSprite_enemy_z2_shell
  .word gStaticMetaSprite_enemy_z2_wolf
  .word gStaticMetaSprite_enemy_z2_flower
  .word gStaticMetaSprite_enemy_z2_spider
  .word gStaticMetaSprite_enemy_z2_vulture
  .word gStaticMetaSprite_enemy_z2_crab
  .word gStaticMetaSprite_boss_z2_boss0
  .word gStaticMetaSprite_boss_z2_boss0_b
  .word gStaticMetaSprite_solid_z2_sand_block
  .word gStaticMetaSprite_vfx_z2_rocks
  .word gStaticMetaSprite_solid_z2_slab
  .word gStaticMetaSprite_solid_z2_gate
  .word gStaticMetaSprite_enemy_z2_pylon
  .word gStaticMetaSprite_enemy_z2_dozer
  .word gStaticMetaSprite_enemy_z2_ice_block
  .word gStaticMetaSprite_enemy_z2_fish
  .word gStaticMetaSprite_enemy_z2_mine
  .word gStaticMetaSprite_boss_z2_fefnir_tank
  .word gStaticMetaSprite_boss_z2_fefnir_wheels
  .word gStaticMetaSprite_boss_z2_fefnir_ball
  .word gStaticMetaSprite_boss_z2_fefnir_flash
  .word gStaticMetaSprite_boss_z2_fefnir_fire
  .word gStaticMetaSprite_boss_z2_fefnir_summon
  .word gStaticMetaSprite_solid_z2_floe
  .word gStaticMetaSprite_boss_z2_leviathan_ice
  .word gStaticMetaSprite_boss_z2_blob_drop
  .word gStaticMetaSprite_boss_z2_blob_splat
  .word gStaticMetaSprite_boss_z2_blob_rock
  .word gStaticMetaSprite_boss_z2_flame_golem
  .word gStaticMetaSprite_boss_z2_flame_golem_fire
  .word gStaticMetaSprite_boss_z2_flame_golem_foot
  .word gStaticMetaSprite_boss_z2_frost_golem
  .word gStaticMetaSprite_boss_z2_frost_golem_ice
  .word gStaticMetaSprite_boss_z2_frost_golem_foot
  .word gStaticMetaSprite_solid_z2_door
  .word gStaticMetaSprite_solid_z2_door_open
  .word gStaticMetaSprite_solid_z2_fallen
  .word gStaticMetaSprite_solid_z2_pad
  .word gStaticMetaSprite_solid_z2_lift
  .word gStaticMetaSprite_solid_z2_box
  .word gStaticMetaSprite_solid_z2_rescue
  .word gStaticMetaSprite_solid_z2_rescue_run
  .word gStaticMetaSprite_solid_z2_baby_elf
  .word gStaticMetaSprite_solid_z2_x
  .word gStaticMetaSprite_boss_z2_wall_splash
  .word gStaticMetaSprite_boss_z2_wall_part
  .word gStaticMetaSprite_boss_z2_wall_arm
  .word gStaticMetaSprite_boss_z2_wall
  .word gStaticMetaSprite_boss_z2_wall_spike
  .word gStaticMetaSprite_boss_z2_wall_shot
  .word gStaticMetaSprite_boss_z2_wall_shelf
  .word gStaticMetaSprite_solid_z2_cast_harpuia
  .word gStaticMetaSprite_solid_z2_cast_fefnir
  .word gStaticMetaSprite_solid_z2_cast_leviathan

.global gApSheetCmdTable
gApSheetCmdTable:
  .word gStaticAnimationSequence_enemy_z2_hopper
  .word gStaticAnimationSequence_enemy_z2_hive
  .word gStaticAnimationSequence_enemy_z2_hottalook
  .word gStaticAnimationSequence_enemy_z2_soldier
  .word gStaticAnimationSequence_enemy_z2_carryarm
  .word gStaticAnimationSequence_enemy_z2_signaloid
  .word gStaticAnimationSequence_boss_z2_golem
  .word gStaticAnimationSequence_boss_z2_golem_arm
  .word gStaticAnimationSequence_boss_z2_golem_laser
  .word gStaticAnimationSequence_boss_z2_golem_foot
  .word gStaticAnimationSequence_boss_z2_harpuia_shots
  .word gStaticAnimationSequence_boss_z2_harpuia_blade
  .word gStaticAnimationSequence_enemy_z2_copter
  .word gStaticAnimationSequence_enemy_z2_eye
  .word gStaticAnimationSequence_enemy_z2_leaper
  .word gStaticAnimationSequence_enemy_z2_barrier_ship
  .word gStaticAnimationSequence_enemy_z2_snowballer
  .word gStaticAnimationSequence_enemy_z2_ring_cannon
  .word gStaticAnimationSequence_enemy_z2_shield_guard
  .word gStaticAnimationSequence_enemy_z2_bee
  .word gStaticAnimationSequence_enemy_z2_bee_carrier
  .word gStaticAnimationSequence_enemy_z2_mole
  .word gStaticAnimationSequence_enemy_z2_tower
  .word gStaticAnimationSequence_enemy_z2_spikeball
  .word gStaticAnimationSequence_enemy_z2_shell
  .word gStaticAnimationSequence_enemy_z2_wolf
  .word gStaticAnimationSequence_enemy_z2_flower
  .word gStaticAnimationSequence_enemy_z2_spider
  .word gStaticAnimationSequence_enemy_z2_vulture
  .word gStaticAnimationSequence_enemy_z2_crab
  .word gStaticAnimationSequence_boss_z2_boss0
  .word gStaticAnimationSequence_boss_z2_boss0_b
  .word gStaticAnimationSequence_solid_z2_sand_block
  .word gStaticAnimationSequence_vfx_z2_rocks
  .word gStaticAnimationSequence_solid_z2_slab
  .word gStaticAnimationSequence_solid_z2_gate
  .word gStaticAnimationSequence_enemy_z2_pylon
  .word gStaticAnimationSequence_enemy_z2_dozer
  .word gStaticAnimationSequence_enemy_z2_ice_block
  .word gStaticAnimationSequence_enemy_z2_fish
  .word gStaticAnimationSequence_enemy_z2_mine
  .word gStaticAnimationSequence_boss_z2_fefnir_tank
  .word gStaticAnimationSequence_boss_z2_fefnir_wheels
  .word gStaticAnimationSequence_boss_z2_fefnir_ball
  .word gStaticAnimationSequence_boss_z2_fefnir_flash
  .word gStaticAnimationSequence_boss_z2_fefnir_fire
  .word gStaticAnimationSequence_boss_z2_fefnir_summon
  .word gStaticAnimationSequence_solid_z2_floe
  .word gStaticAnimationSequence_boss_z2_leviathan_ice
  .word gStaticAnimationSequence_boss_z2_blob_drop
  .word gStaticAnimationSequence_boss_z2_blob_splat
  .word gStaticAnimationSequence_boss_z2_blob_rock
  .word gStaticAnimationSequence_boss_z2_flame_golem
  .word gStaticAnimationSequence_boss_z2_flame_golem_fire
  .word gStaticAnimationSequence_boss_z2_flame_golem_foot
  .word gStaticAnimationSequence_boss_z2_frost_golem
  .word gStaticAnimationSequence_boss_z2_frost_golem_ice
  .word gStaticAnimationSequence_boss_z2_frost_golem_foot
  .word gStaticAnimationSequence_solid_z2_door
  .word gStaticAnimationSequence_solid_z2_door_open
  .word gStaticAnimationSequence_solid_z2_fallen
  .word gStaticAnimationSequence_solid_z2_pad
  .word gStaticAnimationSequence_solid_z2_lift
  .word gStaticAnimationSequence_solid_z2_box
  .word gStaticAnimationSequence_solid_z2_rescue
  .word gStaticAnimationSequence_solid_z2_rescue_run
  .word gStaticAnimationSequence_solid_z2_baby_elf
  .word gStaticAnimationSequence_solid_z2_x
  .word gStaticAnimationSequence_boss_z2_wall_splash
  .word gStaticAnimationSequence_boss_z2_wall_part
  .word gStaticAnimationSequence_boss_z2_wall_arm
  .word gStaticAnimationSequence_boss_z2_wall
  .word gStaticAnimationSequence_boss_z2_wall_spike
  .word gStaticAnimationSequence_boss_z2_wall_shot
  .word gStaticAnimationSequence_boss_z2_wall_shelf
  .word gStaticAnimationSequence_solid_z2_cast_harpuia
  .word gStaticAnimationSequence_solid_z2_cast_fefnir
  .word gStaticAnimationSequence_solid_z2_cast_leviathan

.include "sprites/static/enemy/z2_hopper/metasprite.inc"
.include "sprites/static/enemy/z2_hopper/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_0:
	.incbin "sprites/static/enemy/z2_hopper/sheet.4bpp"
gApSheet_0_Palettes:
	.incbin "sprites/static/enemy/z2_hopper/sheet.gbapal"

.include "sprites/static/enemy/z2_hive/metasprite.inc"
.include "sprites/static/enemy/z2_hive/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_1:
	.incbin "sprites/static/enemy/z2_hive/sheet.4bpp"
gApSheet_1_Palettes:
	.incbin "sprites/static/enemy/z2_hive/sheet.gbapal"

.include "sprites/static/enemy/z2_hottalook/metasprite.inc"
.include "sprites/static/enemy/z2_hottalook/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_2:
	.incbin "sprites/static/enemy/z2_hottalook/sheet.4bpp"
gApSheet_2_Palettes:
	.incbin "sprites/static/enemy/z2_hottalook/sheet.gbapal"

.include "sprites/static/enemy/z2_soldier/metasprite.inc"
.include "sprites/static/enemy/z2_soldier/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_3:
	.incbin "sprites/static/enemy/z2_soldier/sheet.4bpp"
gApSheet_3_Palettes:
	.incbin "sprites/static/enemy/z2_soldier/sheet.gbapal"

.include "sprites/static/enemy/z2_carryarm/metasprite.inc"
.include "sprites/static/enemy/z2_carryarm/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_4:
	.incbin "sprites/static/enemy/z2_carryarm/sheet.4bpp"
gApSheet_4_Palettes:
	.incbin "sprites/static/enemy/z2_carryarm/sheet.gbapal"

.include "sprites/static/enemy/z2_signaloid/metasprite.inc"
.include "sprites/static/enemy/z2_signaloid/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_5:
	.incbin "sprites/static/enemy/z2_signaloid/sheet.4bpp"
gApSheet_5_Palettes:
	.incbin "sprites/static/enemy/z2_signaloid/palettes.bin"

.include "sprites/static/boss/z2_golem/metasprite.inc"
.include "sprites/static/boss/z2_golem/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_6:
	.incbin "sprites/static/boss/z2_golem/sheet.4bpp"
gApSheet_6_Palettes:
	.incbin "sprites/static/boss/z2_golem/sheet.gbapal"

.include "sprites/static/boss/z2_golem/arm/metasprite.inc"
.include "sprites/static/boss/z2_golem/arm/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_7:
	.incbin "sprites/static/boss/z2_golem/arm/sheet.4bpp"
gApSheet_7_Palettes:
	.incbin "sprites/static/boss/z2_golem/arm/sheet.gbapal"

.include "sprites/static/boss/z2_golem/laser/metasprite.inc"
.include "sprites/static/boss/z2_golem/laser/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_8:
	.incbin "sprites/static/boss/z2_golem/laser/sheet.4bpp"
gApSheet_8_Palettes:
	.incbin "sprites/static/boss/z2_golem/laser/palettes.bin"

.include "sprites/static/boss/z2_golem/foot/metasprite.inc"
.include "sprites/static/boss/z2_golem/foot/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_9:
	.incbin "sprites/static/boss/z2_golem/foot/sheet.4bpp"
gApSheet_9_Palettes:
	.incbin "sprites/static/boss/z2_golem/foot/sheet.gbapal"

.include "sprites/static/boss/z2_harpuia/shots/metasprite.inc"
.include "sprites/static/boss/z2_harpuia/shots/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_10:
	.incbin "sprites/static/boss/z2_harpuia/shots/sheet.4bpp"
gApSheet_10_Palettes:
	.incbin "sprites/static/boss/z2_harpuia/shots/sheet.gbapal"

.include "sprites/static/boss/z2_harpuia/blade/metasprite.inc"
.include "sprites/static/boss/z2_harpuia/blade/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_11:
	.incbin "sprites/static/boss/z2_harpuia/blade/sheet.4bpp"
gApSheet_11_Palettes:
	.incbin "sprites/static/boss/z2_harpuia/blade/sheet.gbapal"

.include "sprites/static/enemy/z2_copter/metasprite.inc"
.include "sprites/static/enemy/z2_copter/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_12:
	.incbin "sprites/static/enemy/z2_copter/sheet.4bpp"
gApSheet_12_Palettes:
	.incbin "sprites/static/enemy/z2_copter/sheet.gbapal"

.include "sprites/static/enemy/z2_eye/metasprite.inc"
.include "sprites/static/enemy/z2_eye/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_13:
	.incbin "sprites/static/enemy/z2_eye/sheet.4bpp"
gApSheet_13_Palettes:
	.incbin "sprites/static/enemy/z2_eye/sheet.gbapal"

.include "sprites/static/enemy/z2_leaper/metasprite.inc"
.include "sprites/static/enemy/z2_leaper/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_14:
	.incbin "sprites/static/enemy/z2_leaper/sheet.4bpp"
gApSheet_14_Palettes:
	.incbin "sprites/static/enemy/z2_leaper/sheet.gbapal"

.include "sprites/static/enemy/z2_barrier_ship/metasprite.inc"
.include "sprites/static/enemy/z2_barrier_ship/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_15:
	.incbin "sprites/static/enemy/z2_barrier_ship/sheet.4bpp"
gApSheet_15_Palettes:
	.incbin "sprites/static/enemy/z2_barrier_ship/sheet.gbapal"

.include "sprites/static/enemy/z2_snowballer/metasprite.inc"
.include "sprites/static/enemy/z2_snowballer/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_16:
	.incbin "sprites/static/enemy/z2_snowballer/sheet.4bpp"
gApSheet_16_Palettes:
	.incbin "sprites/static/enemy/z2_snowballer/sheet.gbapal"

.include "sprites/static/enemy/z2_ring_cannon/metasprite.inc"
.include "sprites/static/enemy/z2_ring_cannon/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_17:
	.incbin "sprites/static/enemy/z2_ring_cannon/sheet.4bpp"
gApSheet_17_Palettes:
	.incbin "sprites/static/enemy/z2_ring_cannon/sheet.gbapal"

.include "sprites/static/enemy/z2_shield_guard/metasprite.inc"
.include "sprites/static/enemy/z2_shield_guard/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_18:
	.incbin "sprites/static/enemy/z2_shield_guard/sheet.4bpp"
gApSheet_18_Palettes:
	.incbin "sprites/static/enemy/z2_shield_guard/sheet.gbapal"

.include "sprites/static/enemy/z2_bee/metasprite.inc"
.include "sprites/static/enemy/z2_bee/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_19:
	.incbin "sprites/static/enemy/z2_bee/sheet.4bpp"
gApSheet_19_Palettes:
	.incbin "sprites/static/enemy/z2_bee/sheet.gbapal"

.include "sprites/static/enemy/z2_bee_carrier/metasprite.inc"
.include "sprites/static/enemy/z2_bee_carrier/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_20:
	.incbin "sprites/static/enemy/z2_bee_carrier/sheet.4bpp"
gApSheet_20_Palettes:
	.incbin "sprites/static/enemy/z2_bee_carrier/sheet.gbapal"

.include "sprites/static/enemy/z2_mole/metasprite.inc"
.include "sprites/static/enemy/z2_mole/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_21:
	.incbin "sprites/static/enemy/z2_mole/sheet.4bpp"
gApSheet_21_Palettes:
	.incbin "sprites/static/enemy/z2_mole/sheet.gbapal"

.include "sprites/static/enemy/z2_tower/metasprite.inc"
.include "sprites/static/enemy/z2_tower/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_22:
	.incbin "sprites/static/enemy/z2_tower/sheet.4bpp"
gApSheet_22_Palettes:
	.incbin "sprites/static/enemy/z2_tower/sheet.gbapal"

.include "sprites/static/enemy/z2_spikeball/metasprite.inc"
.include "sprites/static/enemy/z2_spikeball/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_23:
	.incbin "sprites/static/enemy/z2_spikeball/sheet.4bpp"
gApSheet_23_Palettes:
	.incbin "sprites/static/enemy/z2_spikeball/sheet.gbapal"

.include "sprites/static/enemy/z2_shell/metasprite.inc"
.include "sprites/static/enemy/z2_shell/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_24:
	.incbin "sprites/static/enemy/z2_shell/sheet.4bpp"
gApSheet_24_Palettes:
	.incbin "sprites/static/enemy/z2_shell/sheet.gbapal"

.include "sprites/static/enemy/z2_wolf/metasprite.inc"
.include "sprites/static/enemy/z2_wolf/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_25:
	.incbin "sprites/static/enemy/z2_wolf/sheet.4bpp"
gApSheet_25_Palettes:
	.incbin "sprites/static/enemy/z2_wolf/sheet.gbapal"

.include "sprites/static/enemy/z2_flower/metasprite.inc"
.include "sprites/static/enemy/z2_flower/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_26:
	.incbin "sprites/static/enemy/z2_flower/sheet.4bpp"
gApSheet_26_Palettes:
	.incbin "sprites/static/enemy/z2_flower/sheet.gbapal"

.include "sprites/static/enemy/z2_spider/metasprite.inc"
.include "sprites/static/enemy/z2_spider/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_27:
	.incbin "sprites/static/enemy/z2_spider/sheet.4bpp"
gApSheet_27_Palettes:
	.incbin "sprites/static/enemy/z2_spider/sheet.gbapal"

.include "sprites/static/enemy/z2_vulture/metasprite.inc"
.include "sprites/static/enemy/z2_vulture/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_28:
	.incbin "sprites/static/enemy/z2_vulture/sheet.4bpp"
gApSheet_28_Palettes:
	.incbin "sprites/static/enemy/z2_vulture/sheet.gbapal"

.include "sprites/static/enemy/z2_crab/metasprite.inc"
.include "sprites/static/enemy/z2_crab/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_29:
	.incbin "sprites/static/enemy/z2_crab/sheet.4bpp"
gApSheet_29_Palettes:
	.incbin "sprites/static/enemy/z2_crab/sheet.gbapal"

.include "sprites/static/boss/z2_boss0/metasprite.inc"
.include "sprites/static/boss/z2_boss0/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_30:
	.incbin "sprites/static/boss/z2_boss0/sheet.4bpp"
gApSheet_30_Palettes:
	.incbin "sprites/static/boss/z2_boss0/sheet.gbapal"

.include "sprites/static/boss/z2_boss0/b/metasprite.inc"
.include "sprites/static/boss/z2_boss0/b/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_31:
	.incbin "sprites/static/boss/z2_boss0/b/sheet.4bpp"
gApSheet_31_Palettes:
	.incbin "sprites/static/boss/z2_boss0/b/sheet.gbapal"

.include "sprites/static/solid/z2_sand_block/metasprite.inc"
.include "sprites/static/solid/z2_sand_block/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_32:
	.incbin "sprites/static/solid/z2_sand_block/sheet.4bpp"
gApSheet_32_Palettes:
	.incbin "sprites/static/solid/z2_sand_block/sheet.gbapal"

.include "sprites/static/vfx/z2_rocks/metasprite.inc"
.include "sprites/static/vfx/z2_rocks/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_33:
	.incbin "sprites/static/vfx/z2_rocks/sheet.4bpp"
gApSheet_33_Palettes:
	.incbin "sprites/static/vfx/z2_rocks/sheet.gbapal"

.include "sprites/static/solid/z2_slab/metasprite.inc"
.include "sprites/static/solid/z2_slab/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_34:
	.incbin "sprites/static/solid/z2_slab/sheet.4bpp"
gApSheet_34_Palettes:
	.incbin "sprites/static/solid/z2_slab/sheet.gbapal"

.include "sprites/static/solid/z2_gate/metasprite.inc"
.include "sprites/static/solid/z2_gate/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_35:
	.incbin "sprites/static/solid/z2_gate/sheet.4bpp"
gApSheet_35_Palettes:
	.incbin "sprites/static/solid/z2_gate/sheet.gbapal"

.include "sprites/static/enemy/z2_pylon/metasprite.inc"
.include "sprites/static/enemy/z2_pylon/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_36:
	.incbin "sprites/static/enemy/z2_pylon/sheet.4bpp"
gApSheet_36_Palettes:
	.incbin "sprites/static/enemy/z2_pylon/sheet.gbapal"

.include "sprites/static/enemy/z2_dozer/metasprite.inc"
.include "sprites/static/enemy/z2_dozer/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_37:
	.incbin "sprites/static/enemy/z2_dozer/sheet.4bpp"
gApSheet_37_Palettes:
	.incbin "sprites/static/enemy/z2_dozer/sheet.gbapal"

.include "sprites/static/enemy/z2_ice_block/metasprite.inc"
.include "sprites/static/enemy/z2_ice_block/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_38:
	.incbin "sprites/static/enemy/z2_ice_block/sheet.4bpp"
gApSheet_38_Palettes:
	.incbin "sprites/static/enemy/z2_ice_block/sheet.gbapal"

.include "sprites/static/enemy/z2_fish/metasprite.inc"
.include "sprites/static/enemy/z2_fish/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_39:
	.incbin "sprites/static/enemy/z2_fish/sheet.4bpp"
gApSheet_39_Palettes:
	.incbin "sprites/static/enemy/z2_fish/sheet.gbapal"

.include "sprites/static/enemy/z2_mine/metasprite.inc"
.include "sprites/static/enemy/z2_mine/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_40:
	.incbin "sprites/static/enemy/z2_mine/sheet.4bpp"
gApSheet_40_Palettes:
	.incbin "sprites/static/enemy/z2_mine/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/tank/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/tank/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_41:
	.incbin "sprites/static/boss/z2_fefnir/tank/sheet.4bpp"
gApSheet_41_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/tank/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/wheels/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/wheels/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_42:
	.incbin "sprites/static/boss/z2_fefnir/wheels/sheet.4bpp"
gApSheet_42_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/wheels/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/ball/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/ball/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_43:
	.incbin "sprites/static/boss/z2_fefnir/ball/sheet.4bpp"
gApSheet_43_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/ball/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/flash/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/flash/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_44:
	.incbin "sprites/static/boss/z2_fefnir/flash/sheet.4bpp"
gApSheet_44_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/flash/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/fire/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/fire/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_45:
	.incbin "sprites/static/boss/z2_fefnir/fire/sheet.4bpp"
gApSheet_45_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/fire/sheet.gbapal"

.include "sprites/static/boss/z2_fefnir/summon/metasprite.inc"
.include "sprites/static/boss/z2_fefnir/summon/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_46:
	.incbin "sprites/static/boss/z2_fefnir/summon/sheet.4bpp"
gApSheet_46_Palettes:
	.incbin "sprites/static/boss/z2_fefnir/summon/sheet.gbapal"

.include "sprites/static/solid/z2_floe/metasprite.inc"
.include "sprites/static/solid/z2_floe/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_47:
	.incbin "sprites/static/solid/z2_floe/sheet.4bpp"
gApSheet_47_Palettes:
	.incbin "sprites/static/solid/z2_floe/sheet.gbapal"

.include "sprites/static/boss/z2_leviathan/ice/metasprite.inc"
.include "sprites/static/boss/z2_leviathan/ice/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_48:
	.incbin "sprites/static/boss/z2_leviathan/ice/sheet.4bpp"
gApSheet_48_Palettes:
	.incbin "sprites/static/boss/z2_leviathan/ice/sheet.gbapal"

.include "sprites/static/boss/z2_blob/drop/metasprite.inc"
.include "sprites/static/boss/z2_blob/drop/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_49:
	.incbin "sprites/static/boss/z2_blob/drop/sheet.4bpp"
gApSheet_49_Palettes:
	.incbin "sprites/static/boss/z2_blob/drop/sheet.gbapal"

.include "sprites/static/boss/z2_blob/splat/metasprite.inc"
.include "sprites/static/boss/z2_blob/splat/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_50:
	.incbin "sprites/static/boss/z2_blob/splat/sheet.4bpp"
gApSheet_50_Palettes:
	.incbin "sprites/static/boss/z2_blob/splat/sheet.gbapal"

.include "sprites/static/boss/z2_blob/rock/metasprite.inc"
.include "sprites/static/boss/z2_blob/rock/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_51:
	.incbin "sprites/static/boss/z2_blob/rock/sheet.4bpp"
gApSheet_51_Palettes:
	.incbin "sprites/static/boss/z2_blob/rock/sheet.gbapal"

.include "sprites/static/boss/z2_flame_golem/metasprite.inc"
.include "sprites/static/boss/z2_flame_golem/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_52:
	.incbin "sprites/static/boss/z2_flame_golem/sheet.4bpp"
gApSheet_52_Palettes:
	.incbin "sprites/static/boss/z2_flame_golem/sheet.gbapal"

.include "sprites/static/boss/z2_flame_golem/fire/metasprite.inc"
.include "sprites/static/boss/z2_flame_golem/fire/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_53:
	.incbin "sprites/static/boss/z2_flame_golem/fire/sheet.4bpp"
gApSheet_53_Palettes:
	.incbin "sprites/static/boss/z2_flame_golem/fire/palettes.bin"

.include "sprites/static/boss/z2_flame_golem/foot/metasprite.inc"
.include "sprites/static/boss/z2_flame_golem/foot/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_54:
	.incbin "sprites/static/boss/z2_flame_golem/foot/sheet.4bpp"
gApSheet_54_Palettes:
	.incbin "sprites/static/boss/z2_flame_golem/foot/sheet.gbapal"

.include "sprites/static/boss/z2_frost_golem/metasprite.inc"
.include "sprites/static/boss/z2_frost_golem/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_55:
	.incbin "sprites/static/boss/z2_frost_golem/sheet.4bpp"
gApSheet_55_Palettes:
	.incbin "sprites/static/boss/z2_frost_golem/sheet.gbapal"

.include "sprites/static/boss/z2_frost_golem/ice/metasprite.inc"
.include "sprites/static/boss/z2_frost_golem/ice/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_56:
	.incbin "sprites/static/boss/z2_frost_golem/ice/sheet.4bpp"
gApSheet_56_Palettes:
	.incbin "sprites/static/boss/z2_frost_golem/ice/sheet.gbapal"

.include "sprites/static/boss/z2_frost_golem/foot/metasprite.inc"
.include "sprites/static/boss/z2_frost_golem/foot/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_57:
	.incbin "sprites/static/boss/z2_frost_golem/foot/sheet.4bpp"
gApSheet_57_Palettes:
	.incbin "sprites/static/boss/z2_frost_golem/foot/sheet.gbapal"

.include "sprites/static/solid/z2_door/metasprite.inc"
.include "sprites/static/solid/z2_door/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_58:
	.incbin "sprites/static/solid/z2_door/sheet.4bpp"
gApSheet_58_Palettes:
	.incbin "sprites/static/solid/z2_door/sheet.gbapal"

.include "sprites/static/solid/z2_door/open/metasprite.inc"
.include "sprites/static/solid/z2_door/open/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_59:
	.incbin "sprites/static/solid/z2_door/open/sheet.4bpp"
gApSheet_59_Palettes:
	.incbin "sprites/static/solid/z2_door/open/sheet.gbapal"

.include "sprites/static/solid/z2_fallen/metasprite.inc"
.include "sprites/static/solid/z2_fallen/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_60:
	.incbin "sprites/static/solid/z2_fallen/sheet.4bpp"
gApSheet_60_Palettes:
	.incbin "sprites/static/solid/z2_fallen/sheet.gbapal"

.include "sprites/static/solid/z2_pad/metasprite.inc"
.include "sprites/static/solid/z2_pad/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_61:
	.incbin "sprites/static/solid/z2_pad/sheet.4bpp"
gApSheet_61_Palettes:
	.incbin "sprites/static/solid/z2_pad/sheet.gbapal"

.include "sprites/static/solid/z2_lift/metasprite.inc"
.include "sprites/static/solid/z2_lift/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_62:
	.incbin "sprites/static/solid/z2_lift/sheet.4bpp"
gApSheet_62_Palettes:
	.incbin "sprites/static/solid/z2_lift/sheet.gbapal"

.include "sprites/static/solid/z2_box/metasprite.inc"
.include "sprites/static/solid/z2_box/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_63:
	.incbin "sprites/static/solid/z2_box/sheet.4bpp"
gApSheet_63_Palettes:
	.incbin "sprites/static/solid/z2_box/sheet.gbapal"

.include "sprites/static/solid/z2_rescue/metasprite.inc"
.include "sprites/static/solid/z2_rescue/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_64:
	.incbin "sprites/static/solid/z2_rescue/sheet.4bpp"
gApSheet_64_Palettes:
	.incbin "sprites/static/solid/z2_rescue/sheet.gbapal"

.include "sprites/static/solid/z2_rescue/run/metasprite.inc"
.include "sprites/static/solid/z2_rescue/run/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_65:
	.incbin "sprites/static/solid/z2_rescue/run/sheet.4bpp"
gApSheet_65_Palettes:
	.incbin "sprites/static/solid/z2_rescue/run/sheet.gbapal"

.include "sprites/static/solid/z2_baby_elf/metasprite.inc"
.include "sprites/static/solid/z2_baby_elf/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_66:
	.incbin "sprites/static/solid/z2_baby_elf/sheet.4bpp"
gApSheet_66_Palettes:
	.incbin "sprites/static/solid/z2_baby_elf/sheet.gbapal"

.include "sprites/static/solid/z2_x/metasprite.inc"
.include "sprites/static/solid/z2_x/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_67:
	.incbin "sprites/static/solid/z2_x/sheet.4bpp"
gApSheet_67_Palettes:
	.incbin "sprites/static/solid/z2_x/sheet.gbapal"

.include "sprites/static/boss/z2_wall/splash/metasprite.inc"
.include "sprites/static/boss/z2_wall/splash/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_68:
	.incbin "sprites/static/boss/z2_wall/splash/sheet.4bpp"
gApSheet_68_Palettes:
	.incbin "sprites/static/boss/z2_wall/splash/sheet.gbapal"

.include "sprites/static/boss/z2_wall/part/metasprite.inc"
.include "sprites/static/boss/z2_wall/part/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_69:
	.incbin "sprites/static/boss/z2_wall/part/sheet.4bpp"
gApSheet_69_Palettes:
	.incbin "sprites/static/boss/z2_wall/part/sheet.gbapal"

.include "sprites/static/boss/z2_wall/arm/metasprite.inc"
.include "sprites/static/boss/z2_wall/arm/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_70:
	.incbin "sprites/static/boss/z2_wall/arm/sheet.4bpp"
gApSheet_70_Palettes:
	.incbin "sprites/static/boss/z2_wall/arm/sheet.gbapal"

.include "sprites/static/boss/z2_wall/metasprite.inc"
.include "sprites/static/boss/z2_wall/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_71:
	.incbin "sprites/static/boss/z2_wall/sheet.4bpp"
gApSheet_71_Palettes:
	.incbin "sprites/static/boss/z2_wall/sheet.gbapal"

.include "sprites/static/boss/z2_wall/spike/metasprite.inc"
.include "sprites/static/boss/z2_wall/spike/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_72:
	.incbin "sprites/static/boss/z2_wall/spike/sheet.4bpp"
gApSheet_72_Palettes:
	.incbin "sprites/static/boss/z2_wall/spike/sheet.gbapal"

.include "sprites/static/boss/z2_wall/shot/metasprite.inc"
.include "sprites/static/boss/z2_wall/shot/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_73:
	.incbin "sprites/static/boss/z2_wall/shot/sheet.4bpp"
gApSheet_73_Palettes:
	.incbin "sprites/static/boss/z2_wall/shot/sheet.gbapal"

.include "sprites/static/boss/z2_wall/shelf/metasprite.inc"
.include "sprites/static/boss/z2_wall/shelf/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_74:
	.incbin "sprites/static/boss/z2_wall/shelf/sheet.4bpp"
gApSheet_74_Palettes:
	.incbin "sprites/static/boss/z2_wall/shelf/sheet.gbapal"

.include "sprites/static/solid/z2_cast/harpuia/metasprite.inc"
.include "sprites/static/solid/z2_cast/harpuia/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_75:
	.incbin "sprites/static/solid/z2_cast/harpuia/sheet.4bpp"
gApSheet_75_Palettes:
	.incbin "sprites/static/solid/z2_cast/harpuia/sheet.gbapal"

.include "sprites/static/solid/z2_cast/fefnir/metasprite.inc"
.include "sprites/static/solid/z2_cast/fefnir/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_76:
	.incbin "sprites/static/solid/z2_cast/fefnir/sheet.4bpp"
gApSheet_76_Palettes:
	.incbin "sprites/static/solid/z2_cast/fefnir/sheet.gbapal"

.include "sprites/static/solid/z2_cast/leviathan/metasprite.inc"
.include "sprites/static/solid/z2_cast/leviathan/sequence.inc"
.section .rodata
.balign 4, 0
gApSheet_77:
	.incbin "sprites/static/solid/z2_cast/leviathan/sheet.4bpp"
gApSheet_77_Palettes:
	.incbin "sprites/static/solid/z2_cast/leviathan/sheet.gbapal"

.endif
