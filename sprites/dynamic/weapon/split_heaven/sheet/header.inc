.balign 4, 0

.global gGraphicHeader_Sprite_weapon_split_heaven
gGraphicHeader_Sprite_weapon_split_heaven:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_0-. @ src
	.4byte 480 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_1-. @ src
	.4byte 1184 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_2-. @ src
	.4byte 1056 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_3-. @ src
	.4byte 768 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_4-. @ src
	.4byte 480 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_5-. @ src
	.4byte 1184 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_6-. @ src
	.4byte 1056 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_7-. @ src
	.4byte 928 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_8-. @ src
	.4byte 1312 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_weapon_split_heaven_9-. @ src
	.4byte 608 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_split_heaven_0:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_0_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_1:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_1_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_2:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_2_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_3:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_3_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_4:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_4_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_5:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_5_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_6:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_6_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_7:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_7_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_8:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/8.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_8_Palettes:

gGraphicHeader_Sprite_weapon_split_heaven_9:
	.incbin "sprites/dynamic/weapon/split_heaven/sheet/9.4bpp"
	gGraphicHeader_Sprite_weapon_split_heaven_9_Palettes:
