.balign 4, 0

.global gGraphicHeader_Sprite_hellbat_bat
gGraphicHeader_Sprite_hellbat_bat:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_hellbat_bat_0-. @ src
	.4byte 2144 | (896 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 536, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_hellbat_bat_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 6 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_hellbat_bat_0:
	.incbin "sprites/dynamic/hellbat/bat/sheet/0.4bpp"
	gGraphicHeader_Sprite_hellbat_bat_0_Palettes:
	.incbin "sprites/dynamic/hellbat/bat/sheet/0.gbapal"
