.balign 4, 0

.global gGraphicHeader_Sprite_weapon_semi_buster
gGraphicHeader_Sprite_weapon_semi_buster:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_semi_buster_0-. @ src
	.4byte 576 | (65 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_semi_buster_0:
	.incbin "sprites/dynamic/weapon/semi_buster/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_semi_buster_0_Palettes:
