.balign 4, 0

.global gGraphicHeader_Sprite_cyberelf_particle
gGraphicHeader_Sprite_cyberelf_particle:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cyberelf_particle_0-. @ src
	.4byte 128 | (156 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_particle_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cyberelf_particle_1-. @ src
	.4byte 128 | (156 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_particle_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cyberelf_particle_2-. @ src
	.4byte 128 | (156 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_particle_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_cyberelf_particle_3-. @ src
	.4byte 128 | (156 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberelf_particle_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 3 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cyberelf_particle_0:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/0.4bpp"
	gGraphicHeader_Sprite_cyberelf_particle_0_Palettes:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/0.gbapal"

gGraphicHeader_Sprite_cyberelf_particle_1:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/1.4bpp"
	gGraphicHeader_Sprite_cyberelf_particle_1_Palettes:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/1.gbapal"

gGraphicHeader_Sprite_cyberelf_particle_2:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/2.4bpp"
	gGraphicHeader_Sprite_cyberelf_particle_2_Palettes:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/2.gbapal"

gGraphicHeader_Sprite_cyberelf_particle_3:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/3.4bpp"
	gGraphicHeader_Sprite_cyberelf_particle_3_Palettes:
	.incbin "sprites/dynamic/cyberelf/particle/sheet/3.gbapal"
