.balign 4, 0

.global gGraphicHeader_Sprite_zero_buster_buster
gGraphicHeader_Sprite_zero_buster_buster:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_buster_buster_0-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_buster_buster_1-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_buster_buster_2-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_buster_buster_3-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_buster_buster_4-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_buster_buster_5-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_buster_buster_0:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_0_Palettes:

gGraphicHeader_Sprite_zero_buster_buster_1:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_1_Palettes:

gGraphicHeader_Sprite_zero_buster_buster_2:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_2_Palettes:

gGraphicHeader_Sprite_zero_buster_buster_3:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_3_Palettes:

gGraphicHeader_Sprite_zero_buster_buster_4:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_4_Palettes:

gGraphicHeader_Sprite_zero_buster_buster_5:
	.incbin "sprites/dynamic/zero/buster/buster/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_buster_buster_5_Palettes:
