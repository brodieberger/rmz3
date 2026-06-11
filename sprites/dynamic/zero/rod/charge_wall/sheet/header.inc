.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_charge_wall
gGraphicHeader_Sprite_zero_rod_charge_wall:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_charge_wall_0-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_charge_wall_1-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_charge_wall_2-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_charge_wall_3-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_charge_wall_0:
	.incbin "sprites/dynamic/zero/rod/charge_wall/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_wall_0_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_wall_1:
	.incbin "sprites/dynamic/zero/rod/charge_wall/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_wall_1_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_wall_2:
	.incbin "sprites/dynamic/zero/rod/charge_wall/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_wall_2_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_wall_3:
	.incbin "sprites/dynamic/zero/rod/charge_wall/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_wall_3_Palettes:
