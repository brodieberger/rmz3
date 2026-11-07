@ Zero 2's Chain_spin_ladder, dynamic motion 107, Zero 3's DM076_Z2_CHAIN_SPIN_LADDER

.balign 4, 0

.global gGraphicHeader_Sprite_z2_chain_spin_ladder
gGraphicHeader_Sprite_z2_chain_spin_ladder:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_chain_spin_ladder_0-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_chain_spin_ladder_1-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_chain_spin_ladder_2-. @ src
	.4byte 736 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_chain_spin_ladder_3-. @ src
	.4byte 448 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 112, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_chain_spin_ladder_4-. @ src
	.4byte 896 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_chain_spin_ladder_0:
	.incbin "sprites/dynamic/z2_chain_spin_ladder/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_ladder_1:
	.incbin "sprites/dynamic/z2_chain_spin_ladder/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_ladder_2:
	.incbin "sprites/dynamic/z2_chain_spin_ladder/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_ladder_3:
	.incbin "sprites/dynamic/z2_chain_spin_ladder/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_ladder_4:
	.incbin "sprites/dynamic/z2_chain_spin_ladder/sheet/4.4bpp"

.global gGraphicHeader_Sprite_z2_chain_spin_ladder_End
gGraphicHeader_Sprite_z2_chain_spin_ladder_End:
