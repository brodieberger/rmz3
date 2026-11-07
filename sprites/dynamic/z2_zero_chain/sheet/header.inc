@ Zero 2's Zero_chain, dynamic motion 30, Zero 3's DM038_Z2_ZERO_CHAIN

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain
gGraphicHeader_Sprite_z2_zero_chain:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_0-. @ src
	.4byte 1376 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 344, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_1-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_2-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_3-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_4-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_5-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_zero_chain_6-. @ src
	.4byte 1056 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 264, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_zero_chain_7-. @ src
	.4byte 1408 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 352, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_zero_chain_8-. @ src
	.4byte 960 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_zero_chain_9-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_zero_chain_10-. @ src
	.4byte 1024 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_0:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_1:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_2:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_3:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_4:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_5:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/5.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_6:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/6.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_7:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/7.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_8:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/8.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_9:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/9.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_10:
	.incbin "sprites/dynamic/z2_zero_chain/sheet/10.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_End
gGraphicHeader_Sprite_z2_zero_chain_End:
