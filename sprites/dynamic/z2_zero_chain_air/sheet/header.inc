@ Zero 2's Zero_chain_air, dynamic motion 33, Zero 3's DM039_Z2_ZERO_CHAIN_AIR

.balign 4, 0

.global gGraphicHeader_Sprite_z2_zero_chain_air
gGraphicHeader_Sprite_z2_zero_chain_air:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_0-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_1-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_2-. @ src
	.4byte 1280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 320, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_3-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_4-. @ src
	.4byte 1152 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_5-. @ src
	.4byte 1472 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 368, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_6-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_7-. @ src
	.4byte 1344 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 336, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_8-. @ src
	.4byte 1216 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 304, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_9-. @ src
	.4byte 1536 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_10-. @ src
	.4byte 1248 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 312, BPP4 	@ rowsize(unused), props

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_11-. @ src
	.4byte 1312 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 328, BPP4 	@ rowsize(unused), props

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_12-. @ src
	.4byte 1120 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 280, BPP4 	@ rowsize(unused), props

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_zero_chain_air_13-. @ src
	.4byte 1504 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 376, BPP4 	@ rowsize(unused), props

gGraphicHeader_Sprite_z2_zero_chain_air_0:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/0.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_1:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/1.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_2:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/2.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_3:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/3.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_4:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/4.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_5:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/5.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_6:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/6.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_7:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/7.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_8:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/8.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_9:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/9.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_10:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/10.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_11:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/11.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_12:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/12.4bpp"

gGraphicHeader_Sprite_z2_zero_chain_air_13:
	.incbin "sprites/dynamic/z2_zero_chain_air/sheet/13.4bpp"

.global gGraphicHeader_Sprite_z2_zero_chain_air_End
gGraphicHeader_Sprite_z2_zero_chain_air_End:
