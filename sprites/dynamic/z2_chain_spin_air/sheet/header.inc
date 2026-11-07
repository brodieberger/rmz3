@ Zero 2's Chain_spin_air, dynamic motion 105, Zero 3's DM074_Z2_CHAIN_SPIN_AIR

.balign 4, 0

.global gGraphicHeader_Sprite_z2_chain_spin_air
gGraphicHeader_Sprite_z2_chain_spin_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_chain_spin_air_0-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_chain_spin_air_1-. @ src
	.4byte 640 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 160, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_chain_spin_air_2-. @ src
	.4byte 704 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_chain_spin_air_3-. @ src
	.4byte 480 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 120, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_chain_spin_air_4-. @ src
	.4byte 896 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_chain_spin_air_0:
	.incbin "sprites/dynamic/z2_chain_spin_air/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_air_1:
	.incbin "sprites/dynamic/z2_chain_spin_air/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_air_2:
	.incbin "sprites/dynamic/z2_chain_spin_air/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_air_3:
	.incbin "sprites/dynamic/z2_chain_spin_air/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_air_4:
	.incbin "sprites/dynamic/z2_chain_spin_air/sheet/4.4bpp"

.global gGraphicHeader_Sprite_z2_chain_spin_air_End
gGraphicHeader_Sprite_z2_chain_spin_air_End:
