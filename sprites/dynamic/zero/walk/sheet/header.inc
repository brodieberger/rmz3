.balign 4, 0

.global gGraphicHeader_Sprite_zero_walk
gGraphicHeader_Sprite_zero_walk:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_walk_0-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_0_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_walk_1-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_1_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_walk_2-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_2_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_walk_3-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_3_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_walk_4-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_4_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_walk_5-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, (BPP4 | NO_PAL) 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_zero_walk_5_Palettes-. @ src offset
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_walk_0:
	.incbin "sprites/dynamic/zero/walk/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_walk_0_Palettes:

gGraphicHeader_Sprite_zero_walk_1:
	.incbin "sprites/dynamic/zero/walk/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_walk_1_Palettes:

gGraphicHeader_Sprite_zero_walk_2:
	.incbin "sprites/dynamic/zero/walk/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_walk_2_Palettes:

gGraphicHeader_Sprite_zero_walk_3:
	.incbin "sprites/dynamic/zero/walk/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_walk_3_Palettes:

gGraphicHeader_Sprite_zero_walk_4:
	.incbin "sprites/dynamic/zero/walk/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_walk_4_Palettes:

gGraphicHeader_Sprite_zero_walk_5:
	.incbin "sprites/dynamic/zero/walk/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_walk_5_Palettes:
