.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_charge_down_air
gGraphicHeader_Sprite_zero_rod_charge_down_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_0-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_1-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_2-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_3-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_4-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_5-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_air_6-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_charge_down_air_0:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_0_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_1:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_1_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_2:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_2_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_3:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_3_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_4:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_4_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_5:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_5_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_air_6:
	.incbin "sprites/dynamic/zero/rod/charge_down_air/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_air_6_Palettes:
