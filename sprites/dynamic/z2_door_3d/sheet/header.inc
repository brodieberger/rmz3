@ Zero 2's Door_3d, dynamic motion 200, Zero 3's DM210_Z2_DOOR_3D

.balign 4, 0

.global gGraphicHeader_Sprite_z2_door_3d
gGraphicHeader_Sprite_z2_door_3d:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_door_3d_0-. @ src
	.4byte 960 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_door_3d_1-. @ src
	.4byte 1024 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_door_3d_2-. @ src
	.4byte 896 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 224, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_door_3d_3-. @ src
	.4byte 960 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_door_3d_4-. @ src
	.4byte 832 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 208, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_door_3d_5-. @ src
	.4byte 576 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 144, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_door_3d_6-. @ src
	.4byte 320 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 80, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_door_3d_7-. @ src
	.4byte 256 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 64, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_door_3d_8-. @ src
	.4byte 32 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 8, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_door_3d_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_door_3d_0:
	.incbin "sprites/dynamic/z2_door_3d/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_0_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_door_3d_1:
	.incbin "sprites/dynamic/z2_door_3d/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_1_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_door_3d_2:
	.incbin "sprites/dynamic/z2_door_3d/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_2_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_door_3d_3:
	.incbin "sprites/dynamic/z2_door_3d/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_3_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_door_3d_4:
	.incbin "sprites/dynamic/z2_door_3d/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_4_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_door_3d_5:
	.incbin "sprites/dynamic/z2_door_3d/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_5_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_door_3d_6:
	.incbin "sprites/dynamic/z2_door_3d/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_6_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_door_3d_7:
	.incbin "sprites/dynamic/z2_door_3d/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_7_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_door_3d_8:
	.incbin "sprites/dynamic/z2_door_3d/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_door_3d_8_Palettes:
	.incbin "sprites/dynamic/z2_door_3d/sheet/8.gbapal"

.global gGraphicHeader_Sprite_z2_door_3d_End
gGraphicHeader_Sprite_z2_door_3d_End:
