.balign 4, 0

.global gGraphicHeader_Sprite_weapon_unk_116
gGraphicHeader_Sprite_weapon_unk_116:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_unk_116_0-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_unk_116_1-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_unk_116_2-. @ src
	.4byte 288 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 72, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_unk_116_3-. @ src
	.4byte 768 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_unk_116_4-. @ src
	.4byte 928 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_unk_116_0:
	.incbin "sprites/dynamic/weapon/unk_116/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_unk_116_0_Palettes:

gGraphicHeader_Sprite_weapon_unk_116_1:
	.incbin "sprites/dynamic/weapon/unk_116/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_unk_116_1_Palettes:

gGraphicHeader_Sprite_weapon_unk_116_2:
	.incbin "sprites/dynamic/weapon/unk_116/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_unk_116_2_Palettes:

gGraphicHeader_Sprite_weapon_unk_116_3:
	.incbin "sprites/dynamic/weapon/unk_116/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_unk_116_3_Palettes:

gGraphicHeader_Sprite_weapon_unk_116_4:
	.incbin "sprites/dynamic/weapon/unk_116/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_unk_116_4_Palettes:
