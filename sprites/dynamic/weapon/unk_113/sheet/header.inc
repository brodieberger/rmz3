.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_113
gGraphicHeader_Sprite_weapon_unk_113:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_113_0-. @ src
	.4byte 1152 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_113_1-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_113_2-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_113_3-. @ src
	.4byte 192 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_113_4-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_113_0:
	.incbin "sprites/dynamic/weapon/unk_113/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_113_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_113_1:
	.incbin "sprites/dynamic/weapon/unk_113/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_113_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_113_2:
	.incbin "sprites/dynamic/weapon/unk_113/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_113_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_113_3:
	.incbin "sprites/dynamic/weapon/unk_113/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_113_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_113_4:
	.incbin "sprites/dynamic/weapon/unk_113/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_113_4_Palettes:
