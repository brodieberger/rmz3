.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_throw_blade
gGraphicHeader_Sprite_zero_saber_throw_blade:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_throw_blade_0-. @ src
	.4byte 1344 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_throw_blade_1-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_throw_blade_2-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_throw_blade_3-. @ src
	.4byte 608 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_throw_blade_0:
	.incbin "sprites/dynamic/zero/saber/throw_blade/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_throw_blade_0_Palettes:

gGraphicHeader_Sprite_zero_saber_throw_blade_1:
	.incbin "sprites/dynamic/zero/saber/throw_blade/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_throw_blade_1_Palettes:

gGraphicHeader_Sprite_zero_saber_throw_blade_2:
	.incbin "sprites/dynamic/zero/saber/throw_blade/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_throw_blade_2_Palettes:

gGraphicHeader_Sprite_zero_saber_throw_blade_3:
	.incbin "sprites/dynamic/zero/saber/throw_blade/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_throw_blade_3_Palettes:
