.balign 4, 0

.global gGraphicHeader_Sprite_weapon_burst_shot_bullet
gGraphicHeader_Sprite_weapon_burst_shot_bullet:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_burst_shot_bullet_0-. @ src
	.4byte 416 | (65 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 104, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_weapon_burst_shot_bullet_1-. @ src
	.4byte 384 | (65 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 96, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_burst_shot_bullet_0:
	.incbin "sprites/dynamic/weapon/burst_shot/bullet/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_burst_shot_bullet_0_Palettes:

gGraphicHeader_Sprite_weapon_burst_shot_bullet_1:
	.incbin "sprites/dynamic/weapon/burst_shot/bullet/sheet/1.4bpp"
	gGraphicHeader_Sprite_weapon_burst_shot_bullet_1_Palettes:
