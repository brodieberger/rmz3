.balign 4, 0

.global gGraphicHeader_Sprite_weapon_throw_blade
gGraphicHeader_Sprite_weapon_throw_blade:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_throw_blade_0-. @ src
	.4byte 736 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_throw_blade_1-. @ src
	.4byte 1536 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_throw_blade_0:
	.incbin "sprites/dynamic/weapon/throw_blade/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_throw_blade_0_Palettes:

gGraphicHeader_Sprite_weapon_throw_blade_1:
	.incbin "sprites/dynamic/weapon/throw_blade/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_throw_blade_1_Palettes:
