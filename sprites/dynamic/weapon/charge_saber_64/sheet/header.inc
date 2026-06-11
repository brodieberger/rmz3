.balign 4, 0

.global gGraphicHeader_Sprite_weapon_charge_saber_64
gGraphicHeader_Sprite_weapon_charge_saber_64:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_0-. @ src
	.4byte 192 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_1-. @ src
	.4byte 2624 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 656, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_2-. @ src
	.4byte 2304 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 576, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_3-. @ src
	.4byte 2144 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 536, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_4-. @ src
	.4byte 2208 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 552, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_5-. @ src
	.4byte 1728 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 432, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_6-. @ src
	.4byte 1280 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_64_7-. @ src
	.4byte 928 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_charge_saber_64_0:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_0_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_1:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_1_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_2:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_2_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_3:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_3_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_4:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_4_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_5:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_5_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_6:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_6_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_64_7:
	.incbin "sprites/dynamic/weapon/charge_saber_64/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_64_7_Palettes:
