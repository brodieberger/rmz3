.balign 4, 0

.global gGraphicHeader_Sprite_zero_buster_air
gGraphicHeader_Sprite_zero_buster_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_buster_air_0-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_buster_air_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_buster_air_2-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_buster_air_3-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_buster_air_4-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_buster_air_5-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_buster_air_0:
	.incbin "sprites/dynamic/zero/buster/air/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_0_Palettes:

gGraphicHeader_Sprite_zero_buster_air_1:
	.incbin "sprites/dynamic/zero/buster/air/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_1_Palettes:

gGraphicHeader_Sprite_zero_buster_air_2:
	.incbin "sprites/dynamic/zero/buster/air/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_2_Palettes:

gGraphicHeader_Sprite_zero_buster_air_3:
	.incbin "sprites/dynamic/zero/buster/air/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_3_Palettes:

gGraphicHeader_Sprite_zero_buster_air_4:
	.incbin "sprites/dynamic/zero/buster/air/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_4_Palettes:

gGraphicHeader_Sprite_zero_buster_air_5:
	.incbin "sprites/dynamic/zero/buster/air/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_buster_air_5_Palettes:
