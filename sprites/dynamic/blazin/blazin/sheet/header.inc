.balign 4, 0

.global gGraphicHeader_Sprite_blazin_blazin
gGraphicHeader_Sprite_blazin_blazin:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_blazin_blazin_0-. @ src
	.4byte 2848 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 712, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_blazin_blazin_1-. @ src
	.4byte 2816 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 704, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_blazin_blazin_2-. @ src
	.4byte 3520 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 880, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_blazin_blazin_3-. @ src
	.4byte 2336 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 584, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_blazin_blazin_4-. @ src
	.4byte 3040 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_4_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_blazin_blazin_5-. @ src
	.4byte 2688 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 672, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_5_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_blazin_blazin_6-. @ src
	.4byte 3584 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 896, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_6_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_blazin_blazin_7-. @ src
	.4byte 3040 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_7_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_blazin_blazin_8-. @ src
	.4byte 1536 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 384, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_8_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_blazin_blazin_9-. @ src
	.4byte 3008 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 752, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_9_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_blazin_blazin_10-. @ src
	.4byte 3392 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 848, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_10_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 11
	.4byte gGraphicHeader_Sprite_blazin_blazin_11-. @ src
	.4byte 4064 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 1016, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_11_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 12
	.4byte gGraphicHeader_Sprite_blazin_blazin_12-. @ src
	.4byte 2144 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 536, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_blazin_blazin_12_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_blazin_blazin_0:
	.incbin "sprites/dynamic/blazin/blazin/sheet/0.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_0_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/0.gbapal"

gGraphicHeader_Sprite_blazin_blazin_1:
	.incbin "sprites/dynamic/blazin/blazin/sheet/1.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_1_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/1.gbapal"

gGraphicHeader_Sprite_blazin_blazin_2:
	.incbin "sprites/dynamic/blazin/blazin/sheet/2.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_2_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/2.gbapal"

gGraphicHeader_Sprite_blazin_blazin_3:
	.incbin "sprites/dynamic/blazin/blazin/sheet/3.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_3_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/3.gbapal"

gGraphicHeader_Sprite_blazin_blazin_4:
	.incbin "sprites/dynamic/blazin/blazin/sheet/4.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_4_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/4.gbapal"

gGraphicHeader_Sprite_blazin_blazin_5:
	.incbin "sprites/dynamic/blazin/blazin/sheet/5.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_5_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/5.gbapal"

gGraphicHeader_Sprite_blazin_blazin_6:
	.incbin "sprites/dynamic/blazin/blazin/sheet/6.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_6_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/6.gbapal"

gGraphicHeader_Sprite_blazin_blazin_7:
	.incbin "sprites/dynamic/blazin/blazin/sheet/7.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_7_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/7.gbapal"

gGraphicHeader_Sprite_blazin_blazin_8:
	.incbin "sprites/dynamic/blazin/blazin/sheet/8.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_8_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/8.gbapal"

gGraphicHeader_Sprite_blazin_blazin_9:
	.incbin "sprites/dynamic/blazin/blazin/sheet/9.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_9_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/9.gbapal"

gGraphicHeader_Sprite_blazin_blazin_10:
	.incbin "sprites/dynamic/blazin/blazin/sheet/10.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_10_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/10.gbapal"

gGraphicHeader_Sprite_blazin_blazin_11:
	.incbin "sprites/dynamic/blazin/blazin/sheet/11.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_11_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/11.gbapal"

gGraphicHeader_Sprite_blazin_blazin_12:
	.incbin "sprites/dynamic/blazin/blazin/sheet/12.4bpp"
	gGraphicHeader_Sprite_blazin_blazin_12_Palettes:
	.incbin "sprites/dynamic/blazin/blazin/sheet/12.gbapal"
