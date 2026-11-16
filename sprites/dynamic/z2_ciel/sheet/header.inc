@ Zero 2's Ciel, dynamic motion 196, Zero 3's DM214_Z2_CIEL

.balign 4, 0

.global gGraphicHeader_Sprite_z2_ciel
gGraphicHeader_Sprite_z2_ciel:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_ciel_0-. @ src
	.4byte 832 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_ciel_1-. @ src
	.4byte 992 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_ciel_2-. @ src
	.4byte 960 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_ciel_3-. @ src
	.4byte 960 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_ciel_4-. @ src
	.4byte 1024 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_ciel_5-. @ src
	.4byte 608 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_ciel_6-. @ src
	.4byte 960 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_ciel_7-. @ src
	.4byte 832 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_ciel_8-. @ src
	.4byte 704 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_ciel_9-. @ src
	.4byte 800 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_ciel_10-. @ src
	.4byte 576 | (520 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_ciel_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_ciel_0:
	.incbin "sprites/dynamic/z2_ciel/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_ciel_0_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_ciel_1:
	.incbin "sprites/dynamic/z2_ciel/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_ciel_1_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_ciel_2:
	.incbin "sprites/dynamic/z2_ciel/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_ciel_2_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_ciel_3:
	.incbin "sprites/dynamic/z2_ciel/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_ciel_3_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_ciel_4:
	.incbin "sprites/dynamic/z2_ciel/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_ciel_4_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_ciel_5:
	.incbin "sprites/dynamic/z2_ciel/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_ciel_5_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_ciel_6:
	.incbin "sprites/dynamic/z2_ciel/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_ciel_6_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_ciel_7:
	.incbin "sprites/dynamic/z2_ciel/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_ciel_7_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_ciel_8:
	.incbin "sprites/dynamic/z2_ciel/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_ciel_8_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_ciel_9:
	.incbin "sprites/dynamic/z2_ciel/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_ciel_9_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_ciel_10:
	.incbin "sprites/dynamic/z2_ciel/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_ciel_10_Palettes:
	.incbin "sprites/dynamic/z2_ciel/sheet/10.gbapal"

.global gGraphicHeader_Sprite_z2_ciel_End
gGraphicHeader_Sprite_z2_ciel_End:
