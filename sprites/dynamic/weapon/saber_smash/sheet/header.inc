.balign 4, 0

.global gGraphicHeader_Sprite_weapon_saber_smash
gGraphicHeader_Sprite_weapon_saber_smash:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_saber_smash_0-. @ src
	.4byte 1472 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_saber_smash_1-. @ src
	.4byte 1184 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_saber_smash_2-. @ src
	.4byte 704 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_saber_smash_3-. @ src
	.4byte 736 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_saber_smash_4-. @ src
	.4byte 1024 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_saber_smash_0:
	.incbin "sprites/dynamic/weapon/saber_smash/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_saber_smash_0_Palettes:

gGraphicHeader_Sprite_weapon_saber_smash_1:
	.incbin "sprites/dynamic/weapon/saber_smash/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_saber_smash_1_Palettes:

gGraphicHeader_Sprite_weapon_saber_smash_2:
	.incbin "sprites/dynamic/weapon/saber_smash/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_saber_smash_2_Palettes:

gGraphicHeader_Sprite_weapon_saber_smash_3:
	.incbin "sprites/dynamic/weapon/saber_smash/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_saber_smash_3_Palettes:

gGraphicHeader_Sprite_weapon_saber_smash_4:
	.incbin "sprites/dynamic/weapon/saber_smash/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_saber_smash_4_Palettes:
