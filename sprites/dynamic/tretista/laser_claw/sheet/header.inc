.balign 4, 0

.global gGraphicHeader_Sprite_tretista_laser_claw
gGraphicHeader_Sprite_tretista_laser_claw:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_tretista_laser_claw_0-. @ src
	.4byte 3456 | (912 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 864, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_tretista_laser_claw_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_tretista_laser_claw_0:
	.incbin "sprites/dynamic/tretista/laser_claw/sheet/0.4bpp"
	gGraphicHeader_Sprite_tretista_laser_claw_0_Palettes:
	.incbin "sprites/dynamic/tretista/laser_claw/sheet/0.gbapal"
