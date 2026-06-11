.balign 4, 0

.global gGraphicHeader_Sprite_zero_shield_walk
gGraphicHeader_Sprite_zero_shield_walk:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_shield_walk_0-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_shield_walk_1-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_shield_walk_2-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_shield_walk_3-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_shield_walk_4-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_shield_walk_5-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_shield_walk_6-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_shield_walk_7-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_shield_walk_8-. @ src
	.4byte 992 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_zero_shield_walk_9-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_zero_shield_walk_10-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_shield_walk_0:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_0_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_1:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_1_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_2:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_2_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_3:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_3_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_4:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_4_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_5:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_5_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_6:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_6_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_7:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_7_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_8:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_8_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_9:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/9.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_9_Palettes:

gGraphicHeader_Sprite_zero_shield_walk_10:
	.incbin "sprites/dynamic/zero/shield/walk/sheet/10.4bpp"
	gGraphicHeader_Sprite_zero_shield_walk_10_Palettes:
