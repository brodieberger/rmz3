@ Zero 2's Zero_chain_swing, dynamic motion 39, Zero 3's DM068_Z2_ZERO_CHAIN_SWING

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_swing
gGraphicHeader_Sprite_z2_zero_chain_swing:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_0-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_1-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_2-. @ src
	.4byte 1376 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_3-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_4-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_5-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_zero_chain_swing_6-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_swing_0:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_1:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_2:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_3:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_4:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_5:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/5.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_swing_6:
	.incbin "sprites/dynamic/z2_zero_chain_swing/sheet/6.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_swing_End
gGraphicHeader_Sprite_z2_zero_chain_swing_End:
