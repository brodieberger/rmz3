@ Zero 2's Zero_chain_ladder, dynamic motion 37, Zero 3's DM067_Z2_ZERO_CHAIN_LADDER

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_ladder
gGraphicHeader_Sprite_z2_zero_chain_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_ladder_0-. @ src
	.4byte 1184 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 296, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_ladder_1-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_ladder_2-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_ladder_3-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_ladder_4-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_ladder_0:
	.incbin "sprites/dynamic/z2_zero_chain_ladder/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_ladder_1:
	.incbin "sprites/dynamic/z2_zero_chain_ladder/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_ladder_2:
	.incbin "sprites/dynamic/z2_zero_chain_ladder/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_ladder_3:
	.incbin "sprites/dynamic/z2_zero_chain_ladder/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_ladder_4:
	.incbin "sprites/dynamic/z2_zero_chain_ladder/sheet/4.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_ladder_End
gGraphicHeader_Sprite_z2_zero_chain_ladder_End:
