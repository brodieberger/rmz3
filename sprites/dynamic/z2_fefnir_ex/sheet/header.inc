@ Zero 2's Fefnir_ex, dynamic motion 199, Zero 3's DM211_Z2_FEFNIR_EX

.balign 4, 0

.global gGraphicHeader_Sprite_z2_fefnir_ex
gGraphicHeader_Sprite_z2_fefnir_ex:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_0-. @ src
	.4byte 1792 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 448, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_1-. @ src
	.4byte 1664 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_2-. @ src
	.4byte 1696 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 424, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_3-. @ src
	.4byte 1696 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 424, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_4-. @ src
	.4byte 1216 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_fefnir_ex_5-. @ src
	.4byte 2048 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_fefnir_ex_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_fefnir_ex_0:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_0_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_fefnir_ex_1:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_1_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_fefnir_ex_2:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_2_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_fefnir_ex_3:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_3_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_fefnir_ex_4:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_4_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_fefnir_ex_5:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_fefnir_ex_5_Palettes:
	.incbin "sprites/dynamic/z2_fefnir_ex/sheet/5.gbapal"

.global gGraphicHeader_Sprite_z2_fefnir_ex_End
gGraphicHeader_Sprite_z2_fefnir_ex_End:
