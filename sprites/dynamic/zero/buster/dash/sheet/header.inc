.balign 4, 0

.global gGraphicHeader_Sprite_zero_buster_dash
gGraphicHeader_Sprite_zero_buster_dash:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_buster_dash_0-. @ src
	.4byte 576 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_buster_dash_1-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_buster_dash_2-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_buster_dash_3-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_buster_dash_0:
	.incbin "sprites/dynamic/zero/buster/dash/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_buster_dash_0_Palettes:

gGraphicHeader_Sprite_zero_buster_dash_1:
	.incbin "sprites/dynamic/zero/buster/dash/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_buster_dash_1_Palettes:

gGraphicHeader_Sprite_zero_buster_dash_2:
	.incbin "sprites/dynamic/zero/buster/dash/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_buster_dash_2_Palettes:

gGraphicHeader_Sprite_zero_buster_dash_3:
	.incbin "sprites/dynamic/zero/buster/dash/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_buster_dash_3_Palettes:
