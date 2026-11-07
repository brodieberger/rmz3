@ Zero 2's Leviathan, dynamic motion 170, Zero 3's DM202_Z2_LEVIATHAN

.balign 4, 0

.global gGraphicHeader_Sprite_z2_leviathan
gGraphicHeader_Sprite_z2_leviathan:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_leviathan_0-. @ src
	.4byte 1632 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 408, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_leviathan_1-. @ src
	.4byte 768 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_leviathan_2-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_leviathan_3-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_leviathan_4-. @ src
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_leviathan_5-. @ src
	.4byte 1568 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_leviathan_6-. @ src
	.4byte 672 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_leviathan_7-. @ src
	.4byte 1664 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 416, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_leviathan_8-. @ src
	.4byte 1120 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_leviathan_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_leviathan_0:
	.incbin "sprites/dynamic/z2_leviathan/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_0_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_leviathan_1:
	.incbin "sprites/dynamic/z2_leviathan/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_1_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_leviathan_2:
	.incbin "sprites/dynamic/z2_leviathan/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_2_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_leviathan_3:
	.incbin "sprites/dynamic/z2_leviathan/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_3_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_leviathan_4:
	.incbin "sprites/dynamic/z2_leviathan/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_4_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_leviathan_5:
	.incbin "sprites/dynamic/z2_leviathan/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_5_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_leviathan_6:
	.incbin "sprites/dynamic/z2_leviathan/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_6_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_leviathan_7:
	.incbin "sprites/dynamic/z2_leviathan/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_7_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_leviathan_8:
	.incbin "sprites/dynamic/z2_leviathan/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_leviathan_8_Palettes:
	.incbin "sprites/dynamic/z2_leviathan/sheet/8.gbapal"

.global gGraphicHeader_Sprite_z2_leviathan_End
gGraphicHeader_Sprite_z2_leviathan_End:
