@ Zero 2's Chain_spin, dynamic motion 104, Zero 3's DM070_Z2_CHAIN_SPIN

.balign 4, 0

.global gGraphicHeader_Sprite_z2_chain_spin
gGraphicHeader_Sprite_z2_chain_spin:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_chain_spin_0-. @ src
	.4byte 704 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_chain_spin_1-. @ src
	.4byte 800 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_chain_spin_2-. @ src
	.4byte 608 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_chain_spin_3-. @ src
	.4byte 608 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 152, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_chain_spin_4-. @ src
	.4byte 992 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 248, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_chain_spin_0:
	.incbin "sprites/dynamic/z2_chain_spin/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_1:
	.incbin "sprites/dynamic/z2_chain_spin/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_2:
	.incbin "sprites/dynamic/z2_chain_spin/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_3:
	.incbin "sprites/dynamic/z2_chain_spin/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_chain_spin_4:
	.incbin "sprites/dynamic/z2_chain_spin/sheet/4.4bpp"

.global gGraphicHeader_Sprite_z2_chain_spin_End
gGraphicHeader_Sprite_z2_chain_spin_End:
