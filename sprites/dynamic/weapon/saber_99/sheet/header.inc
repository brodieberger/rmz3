.balign 4, 0

.global gGraphicHeader_Sprite_weapon_saber_99
gGraphicHeader_Sprite_weapon_saber_99:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_saber_99_0-. @ src
	.4byte 800 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_saber_99_1-. @ src
	.4byte 960 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_saber_99_2-. @ src
	.4byte 1024 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_saber_99_3-. @ src
	.4byte 960 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_saber_99_4-. @ src
	.4byte 1024 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_saber_99_5-. @ src
	.4byte 992 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_saber_99_0:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_0_Palettes:

gGraphicHeader_Sprite_weapon_saber_99_1:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_1_Palettes:

gGraphicHeader_Sprite_weapon_saber_99_2:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_2_Palettes:

gGraphicHeader_Sprite_weapon_saber_99_3:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_3_Palettes:

gGraphicHeader_Sprite_weapon_saber_99_4:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_4_Palettes:

gGraphicHeader_Sprite_weapon_saber_99_5:
	.incbin "sprites/dynamic/weapon/saber_99/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_saber_99_5_Palettes:
