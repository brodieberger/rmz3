.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_throw_wall
gGraphicHeader_Sprite_zero_shield_throw_wall:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_0-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_1-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_2-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_3-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_4-. @ src
	.4byte 992 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_5-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_shield_throw_wall_6-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_throw_wall_0:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_0_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_1:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_1_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_2:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_2_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_3:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_3_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_4:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_4_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_5:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_5_Palettes:

gGraphicHeader_Sprite_zero_shield_throw_wall_6:
	.incbin "sprites/dynamic/zero/shield/throw_wall/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_shield_throw_wall_6_Palettes:
