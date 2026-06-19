.balign 4, 0

.global gGraphicHeader_Sprite_zero_stun_50
gGraphicHeader_Sprite_zero_stun_50:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_stun_50_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_stun_50_1-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_stun_50_0:
	.incbin "sprites/dynamic/zero/stun/50/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_stun_50_0_Palettes:

gGraphicHeader_Sprite_zero_stun_50_1:
	.incbin "sprites/dynamic/zero/stun/50/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_stun_50_1_Palettes:
