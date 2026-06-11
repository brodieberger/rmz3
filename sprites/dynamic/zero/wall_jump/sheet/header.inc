.balign 4, 0

.global gGraphicHeader_Sprite_zero_wall_jump
gGraphicHeader_Sprite_zero_wall_jump:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_wall_jump_0-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_wall_jump_1-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_wall_jump_2-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_wall_jump_3-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_wall_jump_4-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_wall_jump_5-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_wall_jump_0:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_0_Palettes:

gGraphicHeader_Sprite_zero_wall_jump_1:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_1_Palettes:

gGraphicHeader_Sprite_zero_wall_jump_2:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_2_Palettes:

gGraphicHeader_Sprite_zero_wall_jump_3:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_3_Palettes:

gGraphicHeader_Sprite_zero_wall_jump_4:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_4_Palettes:

gGraphicHeader_Sprite_zero_wall_jump_5:
	.incbin "sprites/dynamic/zero/wall_jump/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_wall_jump_5_Palettes:
