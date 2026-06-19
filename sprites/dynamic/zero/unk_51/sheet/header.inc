.balign 4, 0

.global gGraphicHeader_Sprite_zero_unk_51
gGraphicHeader_Sprite_zero_unk_51:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_unk_51_0-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_unk_51_1-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_unk_51_2-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_unk_51_0:
	.incbin "sprites/dynamic/zero/unk_51/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_unk_51_0_Palettes:

gGraphicHeader_Sprite_zero_unk_51_1:
	.incbin "sprites/dynamic/zero/unk_51/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_unk_51_1_Palettes:

gGraphicHeader_Sprite_zero_unk_51_2:
	.incbin "sprites/dynamic/zero/unk_51/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_unk_51_2_Palettes:
