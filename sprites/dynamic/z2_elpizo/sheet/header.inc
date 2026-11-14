@ Zero 2's Elpizo, dynamic motion 195, Zero 3's DM205_Z2_ELPIZO

.balign 4, 0

.global gGraphicHeader_Sprite_z2_elpizo
gGraphicHeader_Sprite_z2_elpizo:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_elpizo_0-. @ src
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_elpizo_1-. @ src
	.4byte 384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_elpizo_2-. @ src
	.4byte 800 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_elpizo_3-. @ src
	.4byte 928 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_elpizo_4-. @ src
	.4byte 672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_elpizo_5-. @ src
	.4byte 384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_elpizo_6-. @ src
	.4byte 704 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_elpizo_0:
	.incbin "sprites/dynamic/z2_elpizo/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_0_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_elpizo_1:
	.incbin "sprites/dynamic/z2_elpizo/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_1_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_elpizo_2:
	.incbin "sprites/dynamic/z2_elpizo/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_2_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_elpizo_3:
	.incbin "sprites/dynamic/z2_elpizo/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_3_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_elpizo_4:
	.incbin "sprites/dynamic/z2_elpizo/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_4_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_elpizo_5:
	.incbin "sprites/dynamic/z2_elpizo/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_5_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_elpizo_6:
	.incbin "sprites/dynamic/z2_elpizo/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_6_Palettes:
	.incbin "sprites/dynamic/z2_elpizo/sheet/6.gbapal"

.global gGraphicHeader_Sprite_z2_elpizo_End
gGraphicHeader_Sprite_z2_elpizo_End:
