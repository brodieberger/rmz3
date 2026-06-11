.balign 4, 0

.global gGraphicHeader_Sprite_weapon_saber_98
gGraphicHeader_Sprite_weapon_saber_98:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_saber_98_0-. @ src
	.4byte 1120 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_saber_98_1-. @ src
	.4byte 1056 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_saber_98_2-. @ src
	.4byte 960 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_saber_98_3-. @ src
	.4byte 768 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_saber_98_4-. @ src
	.4byte 32 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_saber_98_5-. @ src
	.4byte 1472 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_saber_98_6-. @ src
	.4byte 1472 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_saber_98_7-. @ src
	.4byte 1472 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_weapon_saber_98_8-. @ src
	.4byte 1280 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_weapon_saber_98_9-. @ src
	.4byte 992 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_weapon_saber_98_10-. @ src
	.4byte 800 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_saber_98_0:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_0_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_1:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_1_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_2:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_2_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_3:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_3_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_4:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_4_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_5:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_5_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_6:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_6_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_7:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_7_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_8:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/8.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_8_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_9:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/9.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_9_Palettes:

gGraphicHeader_Sprite_weapon_saber_98_10:
	.incbin "sprites/dynamic/weapon/saber_98/sheet/10.4bpp"
	gGraphicHeader_Sprite_weapon_saber_98_10_Palettes:
