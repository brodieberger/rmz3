.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_86
gGraphicHeader_Sprite_weapon_unk_86:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_86_0-. @ src
	.4byte 288 | (50 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 72, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_86_0:
	.incbin "sprites/dynamic/weapon/unk_86/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_86_0_Palettes:
