.balign 4, 0

.global gGraphicHeader_Sprite_anubis
gGraphicHeader_Sprite_anubis:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_anubis_0-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_anubis_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_anubis_1-. @ src
	.4byte 3264 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 816, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_anubis_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_anubis_2-. @ src
	.4byte 4000 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1000, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_anubis_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_anubis_3-. @ src
	.4byte 2976 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 744, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_anubis_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_anubis_4-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_anubis_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_anubis_0:
	.incbin "sprites/dynamic/anubis/sheet/0.4bpp"
	gGraphicHeader_Sprite_anubis_0_Palettes:
	.incbin "sprites/dynamic/anubis/sheet/0.gbapal"

gGraphicHeader_Sprite_anubis_1:
	.incbin "sprites/dynamic/anubis/sheet/1.4bpp"
	gGraphicHeader_Sprite_anubis_1_Palettes:
	.incbin "sprites/dynamic/anubis/sheet/1.gbapal"

gGraphicHeader_Sprite_anubis_2:
	.incbin "sprites/dynamic/anubis/sheet/2.4bpp"
	gGraphicHeader_Sprite_anubis_2_Palettes:
	.incbin "sprites/dynamic/anubis/sheet/2.gbapal"

gGraphicHeader_Sprite_anubis_3:
	.incbin "sprites/dynamic/anubis/sheet/3.4bpp"
	gGraphicHeader_Sprite_anubis_3_Palettes:
	.incbin "sprites/dynamic/anubis/sheet/3.gbapal"

gGraphicHeader_Sprite_anubis_4:
	.incbin "sprites/dynamic/anubis/sheet/4.4bpp"
	gGraphicHeader_Sprite_anubis_4_Palettes:
	.incbin "sprites/dynamic/anubis/sheet/4.gbapal"
