.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_123
gGraphicHeader_Sprite_weapon_unk_123:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_123_0-. @ src
	.4byte 576 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_123_1-. @ src
	.4byte 224 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 56, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_123_0:
	.incbin "sprites/dynamic/weapon/unk_123/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_123_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_123_1:
	.incbin "sprites/dynamic/weapon/unk_123/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_123_1_Palettes:
