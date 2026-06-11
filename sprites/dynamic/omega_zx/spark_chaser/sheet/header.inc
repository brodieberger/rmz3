.balign 4, 0

.global gGraphicHeader_Sprite_omega_zx_spark_chaser
gGraphicHeader_Sprite_omega_zx_spark_chaser:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_omega_zx_spark_chaser_0-. @ src
	.4byte 480 | (729 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_omega_zx_spark_chaser_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_omega_zx_spark_chaser_0:
	.incbin "sprites/dynamic/omega_zx/spark_chaser/sheet/0.4bpp"
	gGraphicHeader_Sprite_omega_zx_spark_chaser_0_Palettes:
	.incbin "sprites/dynamic/omega_zx/spark_chaser/sheet/0.gbapal"
