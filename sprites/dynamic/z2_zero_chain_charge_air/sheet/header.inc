@ Zero 2's Zero_chain_charge_air, dynamic motion 34, Zero 3's DM071_Z2_ZERO_CHAIN_CHARGE_AIR

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_charge_air
gGraphicHeader_Sprite_z2_zero_chain_charge_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_0-. @ src
	.4byte 1440 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 360, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_1-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_2-. @ src
	.4byte 864 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 216, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_3-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_4-. @ src
	.4byte 832 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_air_5-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_charge_air_0:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_air_1:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_air_2:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_air_3:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_air_4:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_air_5:
	.incbin "sprites/dynamic/z2_zero_chain_charge_air/sheet/5.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_charge_air_End
gGraphicHeader_Sprite_z2_zero_chain_charge_air_End:
