.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_charge
gGraphicHeader_Sprite_zero_rod_charge:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_charge_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_charge_1-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_charge_2-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_charge_3-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_charge_4-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_charge_0:
	.incbin "sprites/dynamic/zero/rod/charge/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_0_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_1:
	.incbin "sprites/dynamic/zero/rod/charge/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_1_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_2:
	.incbin "sprites/dynamic/zero/rod/charge/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_2_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_3:
	.incbin "sprites/dynamic/zero/rod/charge/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_3_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_4:
	.incbin "sprites/dynamic/zero/rod/charge/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_4_Palettes:
