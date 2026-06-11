.balign 4, 0

.global gGraphicHeader_Sprite_weapon_saber_dash
gGraphicHeader_Sprite_weapon_saber_dash:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_saber_dash_0-. @ src
	.4byte 960 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_saber_dash_1-. @ src
	.4byte 960 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_saber_dash_2-. @ src
	.4byte 928 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_saber_dash_0:
	.incbin "sprites/dynamic/weapon/saber_dash/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_saber_dash_0_Palettes:

gGraphicHeader_Sprite_weapon_saber_dash_1:
	.incbin "sprites/dynamic/weapon/saber_dash/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_saber_dash_1_Palettes:

gGraphicHeader_Sprite_weapon_saber_dash_2:
	.incbin "sprites/dynamic/weapon/saber_dash/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_saber_dash_2_Palettes:
