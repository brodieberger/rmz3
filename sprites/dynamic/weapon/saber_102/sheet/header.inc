.balign 4, 0

.global gGraphicHeader_Sprite_weapon_saber_102
gGraphicHeader_Sprite_weapon_saber_102:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_saber_102_0-. @ src
	.4byte 64 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 16, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_saber_102_1-. @ src
	.4byte 64 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 16, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_saber_102_2-. @ src
	.4byte 1408 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_saber_102_3-. @ src
	.4byte 1344 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_saber_102_4-. @ src
	.4byte 1280 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_saber_102_5-. @ src
	.4byte 1312 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_saber_102_6-. @ src
	.4byte 992 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_saber_102_7-. @ src
	.4byte 832 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_weapon_saber_102_8-. @ src
	.4byte 512 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_weapon_saber_102_9-. @ src
	.4byte 512 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_weapon_saber_102_10-. @ src
	.4byte 576 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_saber_102_0:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_0_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_1:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_1_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_2:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_2_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_3:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_3_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_4:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_4_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_5:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_5_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_6:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_6_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_7:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_7_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_8:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/8.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_8_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_9:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/9.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_9_Palettes:

gGraphicHeader_Sprite_weapon_saber_102_10:
	.incbin "sprites/dynamic/weapon/saber_102/sheet/10.4bpp"
	gGraphicHeader_Sprite_weapon_saber_102_10_Palettes:
