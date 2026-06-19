.balign 4, 0

.global gGraphicHeader_Sprite_weapon_blizz_arrow
gGraphicHeader_Sprite_weapon_blizz_arrow:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_blizz_arrow_0-. @ src
	.4byte 800 | (65 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_blizz_arrow_0:
	.incbin "sprites/dynamic/weapon/blizz_arrow/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_blizz_arrow_0_Palettes:
