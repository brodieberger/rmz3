.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_117
gGraphicHeader_Sprite_weapon_unk_117:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_117_0-. @ src
	.4byte 608 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_117_1-. @ src
	.4byte 608 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_117_2-. @ src
	.4byte 448 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_117_3-. @ src
	.4byte 640 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_117_4-. @ src
	.4byte 320 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 80, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_unk_117_5-. @ src
	.4byte 384 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_unk_117_6-. @ src
	.4byte 448 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_unk_117_7-. @ src
	.4byte 416 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 104, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_117_0:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_1:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_2:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_3:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_4:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_4_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_5:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_5_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_6:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_6_Palettes:

gGraphicHeader_Sprite_weapon_unk_117_7:
	.incbin "sprites/dynamic/weapon/unk_117/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_unk_117_7_Palettes:
