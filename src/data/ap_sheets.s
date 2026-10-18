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

.endif
