@ Zero 2's Captive, dynamic motion 195, Zero 3's DM205_Z2_CAPTIVE

.balign 4, 0

.global gGraphicHeader_Sprite_z2_captive
gGraphicHeader_Sprite_z2_captive:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_captive_0-. @ src
	.4byte 384 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_captive_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_captive_0:
	.incbin "sprites/dynamic/z2_captive/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_captive_0_Palettes:
	.incbin "sprites/dynamic/z2_captive/sheet/0.gbapal"

.global gGraphicHeader_Sprite_z2_captive_End
gGraphicHeader_Sprite_z2_captive_End:
