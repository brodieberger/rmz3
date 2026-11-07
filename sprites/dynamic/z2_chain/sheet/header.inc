@ Zero 2's Chain, dynamic motion 103, Zero 3's DM065_Z2_CHAIN

.balign 4, 0

.global gGraphicHeader_Sprite_z2_chain
gGraphicHeader_Sprite_z2_chain:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_chain_0-. @ src
	.4byte 1056 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_chain_1-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_chain_2-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_chain_3-. @ src
	.4byte 544 | (48 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 136, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_chain_0:
	.incbin "sprites/dynamic/z2_chain/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_chain_1:
	.incbin "sprites/dynamic/z2_chain/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_chain_2:
	.incbin "sprites/dynamic/z2_chain/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_chain_3:
	.incbin "sprites/dynamic/z2_chain/sheet/3.4bpp"

.global gGraphicHeader_Sprite_z2_chain_End
gGraphicHeader_Sprite_z2_chain_End:
