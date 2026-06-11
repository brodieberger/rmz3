.balign 4, 0

.global gGraphicHeader_Sprite_cubit_flame
gGraphicHeader_Sprite_cubit_flame:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cubit_flame_0-. @ src
	.4byte 7552 | (618 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1888, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_flame_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cubit_flame_1-. @ src
	.4byte 7488 | (618 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1872, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_flame_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cubit_flame_2-. @ src
	.4byte 2464 | (618 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 616, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cubit_flame_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cubit_flame_0:
	.incbin "sprites/dynamic/cubit/flame/sheet/0.4bpp"
	gGraphicHeader_Sprite_cubit_flame_0_Palettes:
	.incbin "sprites/dynamic/cubit/flame/sheet/0.gbapal"

gGraphicHeader_Sprite_cubit_flame_1:
	.incbin "sprites/dynamic/cubit/flame/sheet/1.4bpp"
	gGraphicHeader_Sprite_cubit_flame_1_Palettes:
	.incbin "sprites/dynamic/cubit/flame/sheet/1.gbapal"

gGraphicHeader_Sprite_cubit_flame_2:
	.incbin "sprites/dynamic/cubit/flame/sheet/2.4bpp"
	gGraphicHeader_Sprite_cubit_flame_2_Palettes:
	.incbin "sprites/dynamic/cubit/flame/sheet/2.gbapal"
