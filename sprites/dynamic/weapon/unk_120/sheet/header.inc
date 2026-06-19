.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_120
gGraphicHeader_Sprite_weapon_unk_120:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_120_0-. @ src
	.4byte 512 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_120_1-. @ src
	.4byte 320 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 80, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_120_0:
	.incbin "sprites/dynamic/weapon/unk_120/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_120_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_120_1:
	.incbin "sprites/dynamic/weapon/unk_120/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_120_1_Palettes:
