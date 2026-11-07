@ Zero 2's Zero_chain_charge_ladder, dynamic motion 38, Zero 3's DM073_Z2_ZERO_CHAIN_CHARGE_LADDER

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_charge_ladder
gGraphicHeader_Sprite_z2_zero_chain_charge_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_0-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_2-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_3-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_4-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_5-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_0:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_1:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_2:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_3:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_4:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_5:
	.incbin "sprites/dynamic/z2_zero_chain_charge_ladder/sheet/5.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_End
gGraphicHeader_Sprite_z2_zero_chain_charge_ladder_End:
