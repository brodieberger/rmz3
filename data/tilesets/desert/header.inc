.section .rodata
.balign 4, 0

.global gDesertTilesetGraphics
gDesertTilesetGraphics:
	@ Graphic 0
	.4byte gDesertTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 9524 	@ size(bit0..21): 9524 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gDesertTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gDesertTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 15616 	@ size(bit0..21): 15616 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gDesertTilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gDesertTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 3648 	@ size(bit0..21): 3648 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gDesertTilesetGraphics_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gDesertTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 2712 	@ size(bit0..21): 2712 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gDesertTilesetGraphics_3_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gDesertTilesetGraphics_0:
	.incbin "data/tilesets/desert/0/tiles.4bpp.lz"
	gDesertTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/desert/0/02.pal"
	.incbin "data/tilesets/desert/0/03.pal"
	.incbin "data/tilesets/desert/0/04.pal"
	.incbin "data/tilesets/desert/0/05.pal"
	.incbin "data/tilesets/desert/0/06.pal"
	.incbin "data/tilesets/desert/0/07.pal"
	.incbin "data/tilesets/desert/0/08.pal"

gDesertTilesetGraphics_1:
	.incbin "data/tilesets/desert/1/tiles.4bpp"
	gDesertTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/desert/1/09.pal"
	.incbin "data/tilesets/desert/1/10.pal"
	.incbin "data/tilesets/desert/1/11.pal"
	.incbin "data/tilesets/desert/1/12.pal"
	.incbin "data/tilesets/desert/1/13.pal"
	.incbin "data/tilesets/desert/1/14.pal"
	.incbin "data/tilesets/desert/1/15.pal"

gDesertTilesetGraphics_2:
	.incbin "data/tilesets/desert/2/tiles.4bpp"
	gDesertTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/desert/2/09.pal"

gDesertTilesetGraphics_3:
	.incbin "data/tilesets/desert/3/tiles.4bpp.lz"
	gDesertTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/desert/3/09.pal"

