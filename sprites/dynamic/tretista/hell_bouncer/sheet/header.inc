.balign 4, 0

.global gGraphicHeader_Sprite_tretista_hell_bouncer
gGraphicHeader_Sprite_tretista_hell_bouncer:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_tretista_hell_bouncer_0-. @ src
	.4byte 8160 | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 2040, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_hell_bouncer_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 5 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_tretista_hell_bouncer_0:
	.incbin "sprites/dynamic/tretista/hell_bouncer/sheet/0.4bpp"
	gGraphicHeader_Sprite_tretista_hell_bouncer_0_Palettes:
	.incbin "sprites/dynamic/tretista/hell_bouncer/sheet/0.gbapal"
