.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_131
gGraphicHeader_Sprite_weapon_unk_131:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_131_0-. @ src
	.4byte 640 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_131_1-. @ src
	.4byte 576 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_131_2-. @ src
	.4byte 352 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 88, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_131_3-. @ src
	.4byte 512 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_131_4-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_131_0:
	.incbin "sprites/dynamic/weapon/unk_131/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_131_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_131_1:
	.incbin "sprites/dynamic/weapon/unk_131/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_131_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_131_2:
	.incbin "sprites/dynamic/weapon/unk_131/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_131_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_131_3:
	.incbin "sprites/dynamic/weapon/unk_131/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_131_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_131_4:
	.incbin "sprites/dynamic/weapon/unk_131/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_131_4_Palettes:
