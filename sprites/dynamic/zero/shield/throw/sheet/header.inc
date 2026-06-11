.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_throw
gGraphicHeader_Sprite_zero_shield_throw:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_throw_0-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_throw_1-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_throw_2-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_shield_throw_3-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_shield_throw_4-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_shield_throw_5-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_shield_throw_6-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_shield_throw_7-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_shield_throw_8-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_throw_0:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_0_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_1:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_1_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_2:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_2_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_3:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_3_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_4:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_4_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_5:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_5_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_6:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_6_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_7:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_7_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_8:
	.incbin "sprites/dynamic/zero/shield/throw/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_8_Palettes:
