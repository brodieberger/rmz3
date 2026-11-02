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

.endif
