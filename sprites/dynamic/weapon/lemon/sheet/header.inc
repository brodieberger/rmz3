.balign 4, 0

.global gGraphicHeader_Sprite_weapon_lemon
gGraphicHeader_Sprite_weapon_lemon:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_lemon_0-. @ src
	.4byte 64 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 16, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_lemon_1-. @ src
	.4byte 64 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 16, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_weapon_lemon_2-. @ src
	.4byte 64 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 16, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_lemon_0:
	.incbin "sprites/dynamic/weapon/lemon/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_lemon_0_Palettes:

gGraphicHeader_Sprite_weapon_lemon_1:
	.incbin "sprites/dynamic/weapon/lemon/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_lemon_1_Palettes:

gGraphicHeader_Sprite_weapon_lemon_2:
	.incbin "sprites/dynamic/weapon/lemon/sheet/2.4bpp"
	gGraphicHeader_Sprite_weapon_lemon_2_Palettes:
