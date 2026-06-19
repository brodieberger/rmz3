.balign 4, 0

.global gGraphicHeader_Sprite_weapon_soul_launchar_flame
gGraphicHeader_Sprite_weapon_soul_launchar_flame:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_soul_launchar_flame_0-. @ src
	.4byte 640 | (68 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_soul_launchar_flame_1-. @ src
	.4byte 192 | (68 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 48, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_soul_launchar_flame_0:
	.incbin "sprites/dynamic/weapon/soul_launchar_flame/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_soul_launchar_flame_0_Palettes:

gGraphicHeader_Sprite_weapon_soul_launchar_flame_1:
	.incbin "sprites/dynamic/weapon/soul_launchar_flame/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_soul_launchar_flame_1_Palettes:
