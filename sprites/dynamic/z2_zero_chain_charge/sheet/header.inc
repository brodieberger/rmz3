@ Zero 2's Zero_chain_charge, dynamic motion 32, Zero 3's DM069_Z2_ZERO_CHAIN_CHARGE

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_charge
gGraphicHeader_Sprite_z2_zero_chain_charge:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_0-. @ src
	.4byte 1088 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 272, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_1-. @ src
	.4byte 896 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_2-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_3-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_4-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_charge_5-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_charge_0:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_1:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_2:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_3:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_4:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_charge_5:
	.incbin "sprites/dynamic/z2_zero_chain_charge/sheet/5.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_charge_End
gGraphicHeader_Sprite_z2_zero_chain_charge_End:
