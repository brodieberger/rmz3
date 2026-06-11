.balign 4, 0

.global gGraphicHeader_Sprite_weapon_burst_shot_firework
gGraphicHeader_Sprite_weapon_burst_shot_firework:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_weapon_burst_shot_firework_0-. @ src
	.4byte 448 | (79 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_weapon_burst_shot_firework_0:
	.incbin "sprites/dynamic/weapon/burst_shot/firework/sheet/0.4bpp"
	gGraphicHeader_Sprite_weapon_burst_shot_firework_0_Palettes:
