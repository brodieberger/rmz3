.section .rodata
.balign 4, 0

.global gForestTilesetGraphics
gForestTilesetGraphics:
	@ Graphic 0
	.4byte gForestTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 10524 	@ size(bit0..21): 10524 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gForestTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gForestTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 12880 	@ size(bit0..21): 12880 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gForestTilesetGraphics_1_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gForestTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 6672 	@ size(bit0..21): 6672 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gForestTilesetGraphics_2_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gForestTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 7516 	@ size(bit0..21): 7516 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gForestTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gForestTilesetGraphics_0:
	.incbin "data/tilesets/forest/0/tiles.4bpp.lz"
	gForestTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/forest/0/02.pal"
	.incbin "data/tilesets/forest/0/03.pal"
	.incbin "data/tilesets/forest/0/04.pal"
	.incbin "data/tilesets/forest/0/05.pal"
	.incbin "data/tilesets/forest/0/06.pal"
	.incbin "data/tilesets/forest/0/07.pal"
	.incbin "data/tilesets/forest/0/08.pal"

gForestTilesetGraphics_1:
	.incbin "data/tilesets/forest/1/tiles.4bpp.lz"
	gForestTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/forest/1/09.pal"
	.incbin "data/tilesets/forest/1/10.pal"
	.incbin "data/tilesets/forest/1/11.pal"
	.incbin "data/tilesets/forest/1/12.pal"
	.incbin "data/tilesets/forest/1/13.pal"
	.incbin "data/tilesets/forest/1/14.pal"

gForestTilesetGraphics_2:
	.incbin "data/tilesets/forest/2/tiles.4bpp.lz"
	gForestTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/forest/2/02.pal"
	.incbin "data/tilesets/forest/2/03.pal"
	.incbin "data/tilesets/forest/2/04.pal"
	.incbin "data/tilesets/forest/2/05.pal"
	.incbin "data/tilesets/forest/2/06.pal"
	.incbin "data/tilesets/forest/2/07.pal"
	.incbin "data/tilesets/forest/2/08.pal"

gForestTilesetGraphics_3:
	.incbin "data/tilesets/forest/3/tiles.4bpp.lz"
	gForestTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/forest/3/09.pal"
	.incbin "data/tilesets/forest/3/10.pal"
	.incbin "data/tilesets/forest/3/11.pal"
	.incbin "data/tilesets/forest/3/12.pal"
	.incbin "data/tilesets/forest/3/13.pal"
	.incbin "data/tilesets/forest/3/14.pal"
	.incbin "data/tilesets/forest/3/15.pal"

