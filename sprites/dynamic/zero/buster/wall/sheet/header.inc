.balign 4, 0

.global gGraphicHeader_Sprite_zero_buster_wall
gGraphicHeader_Sprite_zero_buster_wall:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_buster_wall_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_buster_wall_1-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_buster_wall_2-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_buster_wall_3-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_buster_wall_4-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_buster_wall_0:
	.incbin "sprites/dynamic/zero/buster/wall/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_buster_wall_0_Palettes:

gGraphicHeader_Sprite_zero_buster_wall_1:
	.incbin "sprites/dynamic/zero/buster/wall/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_buster_wall_1_Palettes:

gGraphicHeader_Sprite_zero_buster_wall_2:
	.incbin "sprites/dynamic/zero/buster/wall/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_buster_wall_2_Palettes:

gGraphicHeader_Sprite_zero_buster_wall_3:
	.incbin "sprites/dynamic/zero/buster/wall/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_buster_wall_3_Palettes:

gGraphicHeader_Sprite_zero_buster_wall_4:
	.incbin "sprites/dynamic/zero/buster/wall/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_buster_wall_4_Palettes:
