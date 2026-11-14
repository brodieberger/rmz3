@ Zero 2's Snake, dynamic motion 162, Zero 3's DM206_Z2_SNAKE

.balign 4, 0

.global gGraphicHeader_Sprite_z2_snake
gGraphicHeader_Sprite_z2_snake:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_snake_0-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_snake_1-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_z2_snake_2-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_z2_snake_3-. @ src
	.4byte 3712 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 928, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_z2_snake_4-. @ src
	.4byte 3328 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 832, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_z2_snake_5-. @ src
	.4byte 2368 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 592, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_z2_snake_6-. @ src
	.4byte 3936 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 984, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_z2_snake_7-. @ src
	.4byte 3200 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 800, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_z2_snake_8-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_z2_snake_9-. @ src
	.4byte 3712 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 928, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_z2_snake_10-. @ src
	.4byte 1600 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 400, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_z2_snake_11-. @ src
	.4byte 1920 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 480, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_z2_snake_12-. @ src
	.4byte 3904 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 976, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 13
	.4byte gGraphicHeader_Sprite_z2_snake_13-. @ src
	.4byte 3648 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 912, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_13_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 14
	.4byte gGraphicHeader_Sprite_z2_snake_14-. @ src
	.4byte 3904 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 976, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_14_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 15
	.4byte gGraphicHeader_Sprite_z2_snake_15-. @ src
	.4byte 2688 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 672, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_15_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 16
	.4byte gGraphicHeader_Sprite_z2_snake_16-. @ src
	.4byte 3584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_16_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 17
	.4byte gGraphicHeader_Sprite_z2_snake_17-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_17_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 18
	.4byte gGraphicHeader_Sprite_z2_snake_18-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_18_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 19
	.4byte gGraphicHeader_Sprite_z2_snake_19-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_19_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 20
	.4byte gGraphicHeader_Sprite_z2_snake_20-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_20_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 21
	.4byte gGraphicHeader_Sprite_z2_snake_21-. @ src
	.4byte 4096 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1024, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_snake_21_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_snake_0:
	.incbin "sprites/dynamic/z2_snake/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_snake_0_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_snake_1:
	.incbin "sprites/dynamic/z2_snake/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_snake_1_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/1.gbapal"

gGraphicHeader_Sprite_z2_snake_2:
	.incbin "sprites/dynamic/z2_snake/sheet/2.4bpp"
	gGraphicHeader_Sprite_z2_snake_2_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/2.gbapal"

gGraphicHeader_Sprite_z2_snake_3:
	.incbin "sprites/dynamic/z2_snake/sheet/3.4bpp"
	gGraphicHeader_Sprite_z2_snake_3_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/3.gbapal"

gGraphicHeader_Sprite_z2_snake_4:
	.incbin "sprites/dynamic/z2_snake/sheet/4.4bpp"
	gGraphicHeader_Sprite_z2_snake_4_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/4.gbapal"

gGraphicHeader_Sprite_z2_snake_5:
	.incbin "sprites/dynamic/z2_snake/sheet/5.4bpp"
	gGraphicHeader_Sprite_z2_snake_5_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/5.gbapal"

gGraphicHeader_Sprite_z2_snake_6:
	.incbin "sprites/dynamic/z2_snake/sheet/6.4bpp"
	gGraphicHeader_Sprite_z2_snake_6_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/6.gbapal"

gGraphicHeader_Sprite_z2_snake_7:
	.incbin "sprites/dynamic/z2_snake/sheet/7.4bpp"
	gGraphicHeader_Sprite_z2_snake_7_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/7.gbapal"

gGraphicHeader_Sprite_z2_snake_8:
	.incbin "sprites/dynamic/z2_snake/sheet/8.4bpp"
	gGraphicHeader_Sprite_z2_snake_8_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/8.gbapal"

gGraphicHeader_Sprite_z2_snake_9:
	.incbin "sprites/dynamic/z2_snake/sheet/9.4bpp"
	gGraphicHeader_Sprite_z2_snake_9_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/9.gbapal"

gGraphicHeader_Sprite_z2_snake_10:
	.incbin "sprites/dynamic/z2_snake/sheet/10.4bpp"
	gGraphicHeader_Sprite_z2_snake_10_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/10.gbapal"

gGraphicHeader_Sprite_z2_snake_11:
	.incbin "sprites/dynamic/z2_snake/sheet/11.4bpp"
	gGraphicHeader_Sprite_z2_snake_11_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/11.gbapal"

gGraphicHeader_Sprite_z2_snake_12:
	.incbin "sprites/dynamic/z2_snake/sheet/12.4bpp"
	gGraphicHeader_Sprite_z2_snake_12_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/12.gbapal"

gGraphicHeader_Sprite_z2_snake_13:
	.incbin "sprites/dynamic/z2_snake/sheet/13.4bpp"
	gGraphicHeader_Sprite_z2_snake_13_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/13.gbapal"

gGraphicHeader_Sprite_z2_snake_14:
	.incbin "sprites/dynamic/z2_snake/sheet/14.4bpp"
	gGraphicHeader_Sprite_z2_snake_14_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/14.gbapal"

gGraphicHeader_Sprite_z2_snake_15:
	.incbin "sprites/dynamic/z2_snake/sheet/15.4bpp"
	gGraphicHeader_Sprite_z2_snake_15_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/15.gbapal"

gGraphicHeader_Sprite_z2_snake_16:
	.incbin "sprites/dynamic/z2_snake/sheet/16.4bpp"
	gGraphicHeader_Sprite_z2_snake_16_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/16.gbapal"

gGraphicHeader_Sprite_z2_snake_17:
	.incbin "sprites/dynamic/z2_snake/sheet/17.4bpp"
	gGraphicHeader_Sprite_z2_snake_17_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/17.gbapal"

gGraphicHeader_Sprite_z2_snake_18:
	.incbin "sprites/dynamic/z2_snake/sheet/18.4bpp"
	gGraphicHeader_Sprite_z2_snake_18_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/18.gbapal"

gGraphicHeader_Sprite_z2_snake_19:
	.incbin "sprites/dynamic/z2_snake/sheet/19.4bpp"
	gGraphicHeader_Sprite_z2_snake_19_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/19.gbapal"

gGraphicHeader_Sprite_z2_snake_20:
	.incbin "sprites/dynamic/z2_snake/sheet/20.4bpp"
	gGraphicHeader_Sprite_z2_snake_20_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/20.gbapal"

gGraphicHeader_Sprite_z2_snake_21:
	.incbin "sprites/dynamic/z2_snake/sheet/21.4bpp"
	gGraphicHeader_Sprite_z2_snake_21_Palettes:
	.incbin "sprites/dynamic/z2_snake/sheet/21.gbapal"

.global gGraphicHeader_Sprite_z2_snake_End
gGraphicHeader_Sprite_z2_snake_End:
