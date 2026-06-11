.balign 4, 0

.global gGraphicHeader_Sprite_aztec_falcon
gGraphicHeader_Sprite_aztec_falcon:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_aztec_falcon_0-. @ src
	.4byte 2848 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 712, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_aztec_falcon_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 6 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_aztec_falcon_0:
	.incbin "sprites/dynamic/aztec_falcon/sheet/0.4bpp"
	gGraphicHeader_Sprite_aztec_falcon_0_Palettes:
	.incbin "sprites/dynamic/aztec_falcon/sheet/0.gbapal"
