.balign 4, 0

.global gGraphicHeader_Sprite_weapon_triple_slash_1
gGraphicHeader_Sprite_weapon_triple_slash_1:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_triple_slash_1_0-. @ src
	.4byte 864 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_triple_slash_1_1-. @ src
	.4byte 864 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_triple_slash_1_2-. @ src
	.4byte 384 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_weapon_triple_slash_1_3-. @ src
	.4byte 128 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 32, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_weapon_triple_slash_1_4-. @ src
	.4byte 256 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_triple_slash_1_0:
	.incbin "sprites/dynamic/weapon/triple_slash_1/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_triple_slash_1_0_Palettes:

gGraphicHeader_Sprite_weapon_triple_slash_1_1:
	.incbin "sprites/dynamic/weapon/triple_slash_1/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_triple_slash_1_1_Palettes:

gGraphicHeader_Sprite_weapon_triple_slash_1_2:
	.incbin "sprites/dynamic/weapon/triple_slash_1/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_triple_slash_1_2_Palettes:

gGraphicHeader_Sprite_weapon_triple_slash_1_3:
	.incbin "sprites/dynamic/weapon/triple_slash_1/sheet/3.4bpp"
	gGraphicHeader_Sprite_weapon_triple_slash_1_3_Palettes:

gGraphicHeader_Sprite_weapon_triple_slash_1_4:
	.incbin "sprites/dynamic/weapon/triple_slash_1/sheet/4.4bpp"
	gGraphicHeader_Sprite_weapon_triple_slash_1_4_Palettes:
