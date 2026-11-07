@ Zero 2's Zero_chain_charge_wall, dynamic motion 36, Zero 3's DM072_Z2_ZERO_CHAIN_CHARGE_WALL

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_charge_wall
gGraphicHeader_Sprite_z2_zero_chain_charge_wall:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_0-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_1-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_2-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_3-. @ src
	.4byte 928 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 232, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_4-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_wall_5-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_0:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_1:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_2:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_3:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_4:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_wall_5:
	.incbin "sprites/dynamic/z2_zero_chain_charge_wall/sheet/5.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_charge_wall_End
gGraphicHeader_Sprite_z2_zero_chain_charge_wall_End:
