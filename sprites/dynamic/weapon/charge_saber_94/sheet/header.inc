.balign 4, 0

.global gGraphicHeader_Sprite_weapon_charge_saber_94
gGraphicHeader_Sprite_weapon_charge_saber_94:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_0-. @ src
	.4byte 224 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 56, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_1-. @ src
	.4byte 1440 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_2-. @ src
	.4byte 1120 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_3-. @ src
	.4byte 1152 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_4-. @ src
	.4byte 1344 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_5-. @ src
	.4byte 1216 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_charge_saber_94_6-. @ src
	.4byte 1024 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_charge_saber_94_0:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_0_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_1:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_1_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_2:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_2_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_3:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_3_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_4:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_4_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_5:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_5_Palettes:

gGraphicHeader_Sprite_weapon_charge_saber_94_6:
	.incbin "sprites/dynamic/weapon/charge_saber_94/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_charge_saber_94_6_Palettes:
