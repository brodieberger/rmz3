.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_109
gGraphicHeader_Sprite_weapon_unk_109:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_109_0-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_109_1-. @ src
	.4byte 192 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_109_2-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_109_3-. @ src
	.4byte 1152 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_109_4-. @ src
	.4byte 320 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 80, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_weapon_unk_109_5-. @ src
	.4byte 320 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 80, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_weapon_unk_109_6-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_weapon_unk_109_7-. @ src
	.4byte 864 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_109_0:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_1:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_2:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_3:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_4:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_4_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_5:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/5.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_5_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_6:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/6.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_6_Palettes:

gGraphicHeader_Sprite_weapon_unk_109_7:
	.incbin "sprites/dynamic/weapon/unk_109/sheet/7.4bpp"
	gGraphicHeader_Sprite_weapon_unk_109_7_Palettes:
