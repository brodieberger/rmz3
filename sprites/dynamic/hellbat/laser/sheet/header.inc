.balign 4, 0

.global gGraphicHeader_Sprite_hellbat_laser
gGraphicHeader_Sprite_hellbat_laser:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_hellbat_laser_0-. @ src
	.4byte 2688 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 672, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_laser_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_hellbat_laser_1-. @ src
	.4byte 2688 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 672, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_laser_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_hellbat_laser_0:
	.incbin "sprites/dynamic/hellbat/laser/sheet/0.4bpp"
	gGraphicHeader_Sprite_hellbat_laser_0_Palettes:
	.incbin "sprites/dynamic/hellbat/laser/sheet/0.gbapal"

gGraphicHeader_Sprite_hellbat_laser_1:
	.incbin "sprites/dynamic/hellbat/laser/sheet/1.4bpp"
	gGraphicHeader_Sprite_hellbat_laser_1_Palettes:
	.incbin "sprites/dynamic/hellbat/laser/sheet/1.gbapal"
