.balign 4, 0

.global gGraphicHeader_Sprite_zero_stun_49
gGraphicHeader_Sprite_zero_stun_49:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_stun_49_0-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_stun_49_1-. @ src
	.4byte 672 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_stun_49_2-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_stun_49_0:
	.incbin "sprites/dynamic/zero/stun/49/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_stun_49_0_Palettes:

gGraphicHeader_Sprite_zero_stun_49_1:
	.incbin "sprites/dynamic/zero/stun/49/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_stun_49_1_Palettes:

gGraphicHeader_Sprite_zero_stun_49_2:
	.incbin "sprites/dynamic/zero/stun/49/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_stun_49_2_Palettes:
