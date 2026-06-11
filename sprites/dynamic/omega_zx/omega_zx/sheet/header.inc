.balign 4, 0

.global gGraphicHeader_Sprite_omega_zx_omega_zx
gGraphicHeader_Sprite_omega_zx_omega_zx:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_omega_zx_omega_zx_0-. @ src
	.4byte 6048 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1512, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_omega_zx_omega_zx_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_omega_zx_omega_zx_0:
	.incbin "sprites/dynamic/omega_zx/omega_zx/sheet/0.4bpp"
	gGraphicHeader_Sprite_omega_zx_omega_zx_0_Palettes:
	.incbin "sprites/dynamic/omega_zx/omega_zx/sheet/0.gbapal"
