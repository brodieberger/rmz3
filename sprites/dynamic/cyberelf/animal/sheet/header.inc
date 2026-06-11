.balign 4, 0

.global gGraphicHeader_Sprite_cyberelf_animal
gGraphicHeader_Sprite_cyberelf_animal:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cyberelf_animal_0-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cyberelf_animal_1-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cyberelf_animal_2-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_cyberelf_animal_3-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_cyberelf_animal_4-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_cyberelf_animal_5-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_cyberelf_animal_6-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_cyberelf_animal_7-. @ src
	.4byte 128 | (148 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_animal_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cyberelf_animal_0:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/0.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_0_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/0.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_1:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/1.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_1_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/1.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_2:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/2.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_2_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/2.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_3:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/3.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_3_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/3.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_4:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/4.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_4_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/4.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_5:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/5.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_5_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/5.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_6:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/6.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_6_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/6.gbapal"

gGraphicHeader_Sprite_cyberelf_animal_7:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/7.4bpp"
	gGraphicHeader_Sprite_cyberelf_animal_7_Palettes:
	.incbin "sprites/dynamic/cyberelf/animal/sheet/7.gbapal"
