.balign 4, 0

.global gGraphicHeader_Sprite_cyberelf_nurse
gGraphicHeader_Sprite_cyberelf_nurse:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_0-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_1-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_2-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_3-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_4-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_5-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_6-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_cyberelf_nurse_7-. @ src
	.4byte 128 | (144 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_nurse_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cyberelf_nurse_0:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/0.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_0_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/0.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_1:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/1.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_1_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/1.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_2:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/2.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_2_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/2.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_3:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/3.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_3_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/3.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_4:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/4.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_4_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/4.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_5:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/5.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_5_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/5.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_6:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/6.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_6_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/6.gbapal"

gGraphicHeader_Sprite_cyberelf_nurse_7:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/7.4bpp"
	gGraphicHeader_Sprite_cyberelf_nurse_7_Palettes:
	.incbin "sprites/dynamic/cyberelf/nurse/sheet/7.gbapal"
