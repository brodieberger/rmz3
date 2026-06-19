.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_charge
gGraphicHeader_Sprite_zero_saber_charge:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_charge_0-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_charge_1-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_charge_2-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_charge_3-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_charge_4-. @ src
	.4byte 1344 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_charge_5-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_charge_0:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_0_Palettes:

gGraphicHeader_Sprite_zero_saber_charge_1:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_1_Palettes:

gGraphicHeader_Sprite_zero_saber_charge_2:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_2_Palettes:

gGraphicHeader_Sprite_zero_saber_charge_3:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_3_Palettes:

gGraphicHeader_Sprite_zero_saber_charge_4:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_4_Palettes:

gGraphicHeader_Sprite_zero_saber_charge_5:
	.incbin "sprites/dynamic/zero/saber/charge/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_charge_5_Palettes:
