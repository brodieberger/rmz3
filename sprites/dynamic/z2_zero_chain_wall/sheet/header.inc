@ Zero 2's Zero_chain_wall, dynamic motion 35, Zero 3's DM066_Z2_ZERO_CHAIN_WALL

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_wall
gGraphicHeader_Sprite_z2_zero_chain_wall:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_wall_0-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_wall_1-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_wall_2-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_wall_3-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_wall_4-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_wall_0:
	.incbin "sprites/dynamic/z2_zero_chain_wall/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_wall_1:
	.incbin "sprites/dynamic/z2_zero_chain_wall/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_wall_2:
	.incbin "sprites/dynamic/z2_zero_chain_wall/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_wall_3:
	.incbin "sprites/dynamic/z2_zero_chain_wall/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_wall_4:
	.incbin "sprites/dynamic/z2_zero_chain_wall/sheet/4.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_wall_End
gGraphicHeader_Sprite_z2_zero_chain_wall_End:
