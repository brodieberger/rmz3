.balign 4, 0

.global gGraphicHeader_Sprite_blazin_projectile
gGraphicHeader_Sprite_blazin_projectile:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_blazin_projectile_0-. @ src
	.4byte 6048 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_projectile_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_blazin_projectile_0:
	.incbin "sprites/dynamic/blazin/projectile/sheet/0.4bpp"
	gGraphicHeader_Sprite_blazin_projectile_0_Palettes:
	.incbin "sprites/dynamic/blazin/projectile/sheet/0.gbapal"
