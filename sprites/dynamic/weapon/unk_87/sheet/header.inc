.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_87
gGraphicHeader_Sprite_weapon_unk_87:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_87_0-. @ src
	.4byte 192 | (59 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_87_1-. @ src
	.4byte 192 | (59 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_87_2-. @ src
	.4byte 192 | (59 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_87_3-. @ src
	.4byte 192 | (59 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_87_0:
	.incbin "sprites/dynamic/weapon/unk_87/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_87_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_87_1:
	.incbin "sprites/dynamic/weapon/unk_87/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_87_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_87_2:
	.incbin "sprites/dynamic/weapon/unk_87/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_87_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_87_3:
	.incbin "sprites/dynamic/weapon/unk_87/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_87_3_Palettes:
