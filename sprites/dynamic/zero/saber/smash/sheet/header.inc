.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_smash
gGraphicHeader_Sprite_zero_saber_smash:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_smash_0-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_smash_1-. @ src
	.4byte 640 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_smash_2-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_smash_0:
	.incbin "sprites/dynamic/zero/saber/smash/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_smash_0_Palettes:

gGraphicHeader_Sprite_zero_saber_smash_1:
	.incbin "sprites/dynamic/zero/saber/smash/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_smash_1_Palettes:

gGraphicHeader_Sprite_zero_saber_smash_2:
	.incbin "sprites/dynamic/zero/saber/smash/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_smash_2_Palettes:
