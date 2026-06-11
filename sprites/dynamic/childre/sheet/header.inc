.balign 4, 0

.global gGraphicHeader_Sprite_childre
gGraphicHeader_Sprite_childre:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_childre_0-. @ src
	.4byte 3744 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 936, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_childre_1-. @ src
	.4byte 2400 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 600, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_childre_2-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_childre_3-. @ src
	.4byte 3584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_childre_4-. @ src
	.4byte 4000 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1000, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_childre_5-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_childre_6-. @ src
	.4byte 3872 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 968, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_childre_7-. @ src
	.4byte 3968 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 992, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_childre_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_childre_0:
	.incbin "sprites/dynamic/childre/sheet/0.4bpp"
	gGraphicHeader_Sprite_childre_0_Palettes:
	.incbin "sprites/dynamic/childre/sheet/0.gbapal"

gGraphicHeader_Sprite_childre_1:
	.incbin "sprites/dynamic/childre/sheet/1.4bpp"
	gGraphicHeader_Sprite_childre_1_Palettes:
	.incbin "sprites/dynamic/childre/sheet/1.gbapal"

gGraphicHeader_Sprite_childre_2:
	.incbin "sprites/dynamic/childre/sheet/2.4bpp"
	gGraphicHeader_Sprite_childre_2_Palettes:
	.incbin "sprites/dynamic/childre/sheet/2.gbapal"

gGraphicHeader_Sprite_childre_3:
	.incbin "sprites/dynamic/childre/sheet/3.4bpp"
	gGraphicHeader_Sprite_childre_3_Palettes:
	.incbin "sprites/dynamic/childre/sheet/3.gbapal"

gGraphicHeader_Sprite_childre_4:
	.incbin "sprites/dynamic/childre/sheet/4.4bpp"
	gGraphicHeader_Sprite_childre_4_Palettes:
	.incbin "sprites/dynamic/childre/sheet/4.gbapal"

gGraphicHeader_Sprite_childre_5:
	.incbin "sprites/dynamic/childre/sheet/5.4bpp"
	gGraphicHeader_Sprite_childre_5_Palettes:
	.incbin "sprites/dynamic/childre/sheet/5.gbapal"

gGraphicHeader_Sprite_childre_6:
	.incbin "sprites/dynamic/childre/sheet/6.4bpp"
	gGraphicHeader_Sprite_childre_6_Palettes:
	.incbin "sprites/dynamic/childre/sheet/6.gbapal"

gGraphicHeader_Sprite_childre_7:
	.incbin "sprites/dynamic/childre/sheet/7.4bpp"
	gGraphicHeader_Sprite_childre_7_Palettes:
	.incbin "sprites/dynamic/childre/sheet/7.gbapal"
