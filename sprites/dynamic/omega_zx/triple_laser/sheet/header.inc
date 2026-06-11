.balign 4, 0

.global gGraphicHeader_Sprite_omega_zx_triple_laser
gGraphicHeader_Sprite_omega_zx_triple_laser:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_omega_zx_triple_laser_0-. @ src
	.4byte 1568 | (729 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 392, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_omega_zx_triple_laser_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 8 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_omega_zx_triple_laser_0:
	.incbin "sprites/dynamic/omega_zx/triple_laser/sheet/0.4bpp"
	gGraphicHeader_Sprite_omega_zx_triple_laser_0_Palettes:
	.incbin "sprites/dynamic/omega_zx/triple_laser/sheet/0.gbapal"
