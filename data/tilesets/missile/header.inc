.section .rodata
.balign 4, 0

.global gMissileTilesetGraphics
gMissileTilesetGraphics:
	@ Graphic 0
	.4byte gMissileTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 7284 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_0_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gMissileTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 7404 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_1_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gMissileTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 5784 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_2_Palettes-. @ src offset
		.2byte 64 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gMissileTilesetGraphics_3-. @ src offset
	.4byte (0 << 22) | 5680 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gMissileTilesetGraphics_4-. @ src offset
	.4byte (512 << 22) | 5636 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_4_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gMissileTilesetGraphics_5-. @ src offset
	.4byte (0 << 22) | 11028 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_5_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gMissileTilesetGraphics_6-. @ src offset
	.4byte (512 << 22) | 4724 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ colsize(unused), props
		@ Palette
		.4byte gMissileTilesetGraphics_6_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gMissileTilesetGraphics_0:
	.incbin "data/tilesets/missile/0/tiles.4bpp.lz"
	gMissileTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/missile/0/02.pal"
	.incbin "data/tilesets/missile/0/03.pal"
	.incbin "data/tilesets/missile/0/04.pal"
	.incbin "data/tilesets/missile/0/05.pal"
	.incbin "data/tilesets/missile/0/06.pal"
	.incbin "data/tilesets/missile/0/07.pal"

gMissileTilesetGraphics_1:
	.incbin "data/tilesets/missile/1/tiles.4bpp.lz"
	gMissileTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/missile/1/09.pal"
	.incbin "data/tilesets/missile/1/10.pal"
	.incbin "data/tilesets/missile/1/11.pal"
	.incbin "data/tilesets/missile/1/12.pal"
	.incbin "data/tilesets/missile/1/13.pal"
	.incbin "data/tilesets/missile/1/14.pal"

gMissileTilesetGraphics_2:
	.incbin "data/tilesets/missile/2/tiles.4bpp.lz"
	gMissileTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/missile/2/02.pal"
	.incbin "data/tilesets/missile/2/03.pal"

gMissileTilesetGraphics_3:
	.incbin "data/tilesets/missile/3/tiles.4bpp.lz"
	gMissileTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/missile/3/02.pal"
	.incbin "data/tilesets/missile/3/03.pal"
	.incbin "data/tilesets/missile/3/04.pal"
	.incbin "data/tilesets/missile/3/05.pal"
	.incbin "data/tilesets/missile/3/06.pal"
	.incbin "data/tilesets/missile/3/07.pal"
	.incbin "data/tilesets/missile/3/08.pal"

gMissileTilesetGraphics_4:
	.incbin "data/tilesets/missile/4/tiles.4bpp.lz"
	gMissileTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/missile/4/09.pal"
	.incbin "data/tilesets/missile/4/10.pal"
	.incbin "data/tilesets/missile/4/11.pal"
	.incbin "data/tilesets/missile/4/12.pal"
	.incbin "data/tilesets/missile/4/13.pal"
	.incbin "data/tilesets/missile/4/14.pal"
	.incbin "data/tilesets/missile/4/15.pal"

gMissileTilesetGraphics_5:
	.incbin "data/tilesets/missile/5/tiles.4bpp.lz"
	gMissileTilesetGraphics_5_Palettes:
	.incbin "data/tilesets/missile/5/02.pal"
	.incbin "data/tilesets/missile/5/03.pal"
	.incbin "data/tilesets/missile/5/04.pal"
	.incbin "data/tilesets/missile/5/05.pal"
	.incbin "data/tilesets/missile/5/06.pal"
	.incbin "data/tilesets/missile/5/07.pal"

gMissileTilesetGraphics_6:
	.incbin "data/tilesets/missile/6/tiles.4bpp.lz"
	gMissileTilesetGraphics_6_Palettes:
	.incbin "data/tilesets/missile/6/09.pal"
	.incbin "data/tilesets/missile/6/10.pal"
	.incbin "data/tilesets/missile/6/11.pal"
	.incbin "data/tilesets/missile/6/12.pal"
	.incbin "data/tilesets/missile/6/13.pal"
	.incbin "data/tilesets/missile/6/14.pal"
	.incbin "data/tilesets/missile/6/15.pal"

