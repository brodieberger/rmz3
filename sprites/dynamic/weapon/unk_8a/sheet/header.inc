.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_8a
gGraphicHeader_Sprite_weapon_unk_8a:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_8a_0-. @ src
	.4byte 384 | (80 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_8a_1-. @ src
	.4byte 384 | (80 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_8a_2-. @ src
	.4byte 384 | (80 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_8a_3-. @ src
	.4byte 384 | (80 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_8a_0:
	.incbin "sprites/dynamic/weapon/unk_8a/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_8a_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_8a_1:
	.incbin "sprites/dynamic/weapon/unk_8a/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_8a_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_8a_2:
	.incbin "sprites/dynamic/weapon/unk_8a/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_8a_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_8a_3:
	.incbin "sprites/dynamic/weapon/unk_8a/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_8a_3_Palettes:
