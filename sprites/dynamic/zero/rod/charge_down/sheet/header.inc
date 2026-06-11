.balign 4, 0

.global gGraphicHeader_Sprite_zero_rod_charge_down
gGraphicHeader_Sprite_zero_rod_charge_down:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_0-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_1-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_2-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_3-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_4-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_5-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_rod_charge_down_6-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_rod_charge_down_0:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_0_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_1:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_1_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_2:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_2_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_3:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_3_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_4:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_4_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_5:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_5_Palettes:

gGraphicHeader_Sprite_zero_rod_charge_down_6:
	.incbin "sprites/dynamic/zero/rod/charge_down/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_rod_charge_down_6_Palettes:
