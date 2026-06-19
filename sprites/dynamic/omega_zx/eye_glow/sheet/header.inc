.balign 4, 0

.global gGraphicHeader_Sprite_omega_zx_eye_glow
gGraphicHeader_Sprite_omega_zx_eye_glow:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_omega_zx_eye_glow_0-. @ src
	.4byte 736 | (701 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_omega_zx_eye_glow_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_omega_zx_eye_glow_0:
	.incbin "sprites/dynamic/omega_zx/eye_glow/sheet/0.4bpp"
	gGraphicHeader_Sprite_omega_zx_eye_glow_0_Palettes:
	.incbin "sprites/dynamic/omega_zx/eye_glow/sheet/0.gbapal"
