.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_88
gGraphicHeader_Sprite_weapon_unk_88:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_88_0-. @ src
	.4byte 480 | (65 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_88_0:
	.incbin "sprites/dynamic/weapon/unk_88/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_88_0_Palettes:
