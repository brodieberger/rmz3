.balign 4, 0

.global gGraphicHeader_Sprite_weapon_gale_attack
gGraphicHeader_Sprite_weapon_gale_attack:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_gale_attack_0-. @ src
	.4byte 736 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_gale_attack_0:
	.incbin "sprites/dynamic/weapon/gale_attack/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_gale_attack_0_Palettes:
