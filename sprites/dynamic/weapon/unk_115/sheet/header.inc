.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_115
gGraphicHeader_Sprite_weapon_unk_115:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_115_0-. @ src
	.4byte 1152 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_115_1-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_115_2-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_115_3-. @ src
	.4byte 192 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_115_4-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_115_0:
	.incbin "sprites/dynamic/weapon/unk_115/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_115_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_115_1:
	.incbin "sprites/dynamic/weapon/unk_115/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_115_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_115_2:
	.incbin "sprites/dynamic/weapon/unk_115/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_115_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_115_3:
	.incbin "sprites/dynamic/weapon/unk_115/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_115_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_115_4:
	.incbin "sprites/dynamic/weapon/unk_115/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_115_4_Palettes:
