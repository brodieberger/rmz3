.balign 4, 0

.global gGraphicHeader_Sprite_zero_teleport_start
gGraphicHeader_Sprite_zero_teleport_start:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_teleport_start_0-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_teleport_start_1-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_teleport_start_2-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_teleport_start_3-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_teleport_start_4-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_teleport_start_5-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_teleport_start_0:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_0_Palettes:

gGraphicHeader_Sprite_zero_teleport_start_1:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_1_Palettes:

gGraphicHeader_Sprite_zero_teleport_start_2:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_2_Palettes:

gGraphicHeader_Sprite_zero_teleport_start_3:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_3_Palettes:

gGraphicHeader_Sprite_zero_teleport_start_4:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_4_Palettes:

gGraphicHeader_Sprite_zero_teleport_start_5:
	.incbin "sprites/dynamic/zero/teleport/start/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_teleport_start_5_Palettes:
