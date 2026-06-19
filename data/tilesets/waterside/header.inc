.section .rodata
.balign 4, 0

.global gWatersideTilesetGraphics
gWatersideTilesetGraphics:
	@ Graphic 0
	.4byte gWatersideTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 11952 	@ size(bit0..21): 11952 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_0_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gWatersideTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 8032 	@ size(bit0..21): 8032 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gWatersideTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 10172 	@ size(bit0..21): 10172 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_2_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gWatersideTilesetGraphics_3-. @ src offset
	.4byte (0 << 22) | 6664 	@ size(bit0..21): 6664 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_3_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gWatersideTilesetGraphics_4-. @ src offset
	.4byte (0 << 22) | 6940 	@ size(bit0..21): 6940 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_4_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gWatersideTilesetGraphics_5-. @ src offset
	.4byte (512 << 22) | 6456 	@ size(bit0..21): 6456 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_5_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gWatersideTilesetGraphics_6-. @ src offset
	.4byte (0 << 22) | 7304 	@ size(bit0..21): 7304 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWatersideTilesetGraphics_6_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gWatersideTilesetGraphics_0:
	.incbin "data/tilesets/waterside/0/tiles.4bpp.lz"
	gWatersideTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/waterside/0/02.pal"
	.incbin "data/tilesets/waterside/0/03.pal"
	.incbin "data/tilesets/waterside/0/04.pal"
	.incbin "data/tilesets/waterside/0/05.pal"
	.incbin "data/tilesets/waterside/0/06.pal"
	.incbin "data/tilesets/waterside/0/07.pal"

gWatersideTilesetGraphics_1:
	.incbin "data/tilesets/waterside/1/tiles.4bpp.lz"
	gWatersideTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/waterside/1/09.pal"
	.incbin "data/tilesets/waterside/1/10.pal"
	.incbin "data/tilesets/waterside/1/11.pal"
	.incbin "data/tilesets/waterside/1/12.pal"
	.incbin "data/tilesets/waterside/1/13.pal"
	.incbin "data/tilesets/waterside/1/14.pal"
	.incbin "data/tilesets/waterside/1/15.pal"

gWatersideTilesetGraphics_2:
	.incbin "data/tilesets/waterside/2/tiles.4bpp.lz"
	gWatersideTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/waterside/2/02.pal"
	.incbin "data/tilesets/waterside/2/03.pal"
	.incbin "data/tilesets/waterside/2/04.pal"
	.incbin "data/tilesets/waterside/2/05.pal"
	.incbin "data/tilesets/waterside/2/06.pal"
	.incbin "data/tilesets/waterside/2/07.pal"
	.incbin "data/tilesets/waterside/2/08.pal"

gWatersideTilesetGraphics_3:
	.incbin "data/tilesets/waterside/3/tiles.4bpp.lz"
	gWatersideTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/waterside/3/02.pal"
	.incbin "data/tilesets/waterside/3/03.pal"
	.incbin "data/tilesets/waterside/3/04.pal"
	.incbin "data/tilesets/waterside/3/05.pal"
	.incbin "data/tilesets/waterside/3/06.pal"

gWatersideTilesetGraphics_4:
	.incbin "data/tilesets/waterside/4/tiles.4bpp.lz"
	gWatersideTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/waterside/4/02.pal"
	.incbin "data/tilesets/waterside/4/03.pal"
	.incbin "data/tilesets/waterside/4/04.pal"
	.incbin "data/tilesets/waterside/4/05.pal"
	.incbin "data/tilesets/waterside/4/06.pal"
	.incbin "data/tilesets/waterside/4/07.pal"
	.incbin "data/tilesets/waterside/4/08.pal"

gWatersideTilesetGraphics_5:
	.incbin "data/tilesets/waterside/5/tiles.4bpp.lz"
	gWatersideTilesetGraphics_5_Palettes:
	.incbin "data/tilesets/waterside/5/09.pal"
	.incbin "data/tilesets/waterside/5/10.pal"
	.incbin "data/tilesets/waterside/5/11.pal"
	.incbin "data/tilesets/waterside/5/12.pal"
	.incbin "data/tilesets/waterside/5/13.pal"
	.incbin "data/tilesets/waterside/5/14.pal"
	.incbin "data/tilesets/waterside/5/15.pal"

gWatersideTilesetGraphics_6:
	.incbin "data/tilesets/waterside/6/tiles.4bpp.lz"
	gWatersideTilesetGraphics_6_Palettes:
	.incbin "data/tilesets/waterside/6/02.pal"
	.incbin "data/tilesets/waterside/6/03.pal"
	.incbin "data/tilesets/waterside/6/04.pal"
	.incbin "data/tilesets/waterside/6/05.pal"
	.incbin "data/tilesets/waterside/6/06.pal"
	.incbin "data/tilesets/waterside/6/07.pal"
	.incbin "data/tilesets/waterside/6/08.pal"

