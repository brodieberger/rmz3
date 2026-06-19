.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_throw_ladder
gGraphicHeader_Sprite_zero_shield_throw_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_0-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_1-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_2-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_3-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_4-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_5-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_shield_throw_ladder_6-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_throw_ladder_0:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_0_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_1:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_1_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_2:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_2_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_3:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_3_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_4:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_4_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_5:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_5_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_ladder_6:
	.incbin "sprites/dynamic/zero/shield/throw_ladder/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_ladder_6_Palettes:
