.section .rodata
.balign 4, 0

.global gAntarcticTilesetGraphics
gAntarcticTilesetGraphics:
	@ Graphic 0
	.4byte gAntarcticTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 5736 	@ size(bit0..21): 5736 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAntarcticTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gAntarcticTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 11696 	@ size(bit0..21): 11696 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAntarcticTilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gAntarcticTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 9444 	@ size(bit0..21): 9444 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAntarcticTilesetGraphics_2_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gAntarcticTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 6868 	@ size(bit0..21): 6868 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAntarcticTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gAntarcticTilesetGraphics_4-. @ src offset
	.4byte (0 << 22) | 8792 	@ size(bit0..21): 8792 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAntarcticTilesetGraphics_4_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gAntarcticTilesetGraphics_0:
	.incbin "data/tilesets/antarctic/0/tiles.4bpp.lz"
	gAntarcticTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/antarctic/0/02.pal"
	.incbin "data/tilesets/antarctic/0/03.pal"
	.incbin "data/tilesets/antarctic/0/04.pal"
	.incbin "data/tilesets/antarctic/0/05.pal"
	.incbin "data/tilesets/antarctic/0/06.pal"
	.incbin "data/tilesets/antarctic/0/07.pal"
	.incbin "data/tilesets/antarctic/0/08.pal"

gAntarcticTilesetGraphics_1:
	.incbin "data/tilesets/antarctic/1/tiles.4bpp.lz"
	gAntarcticTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/antarctic/1/09.pal"
	.incbin "data/tilesets/antarctic/1/10.pal"
	.incbin "data/tilesets/antarctic/1/11.pal"
	.incbin "data/tilesets/antarctic/1/12.pal"
	.incbin "data/tilesets/antarctic/1/13.pal"
	.incbin "data/tilesets/antarctic/1/14.pal"
	.incbin "data/tilesets/antarctic/1/15.pal"

gAntarcticTilesetGraphics_2:
	.incbin "data/tilesets/antarctic/2/tiles.4bpp.lz"
	gAntarcticTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/antarctic/2/09.pal"
	.incbin "data/tilesets/antarctic/2/10.pal"
	.incbin "data/tilesets/antarctic/2/11.pal"
	.incbin "data/tilesets/antarctic/2/12.pal"
	.incbin "data/tilesets/antarctic/2/13.pal"
	.incbin "data/tilesets/antarctic/2/14.pal"
	.incbin "data/tilesets/antarctic/2/15.pal"

gAntarcticTilesetGraphics_3:
	.incbin "data/tilesets/antarctic/3/tiles.4bpp.lz"
	gAntarcticTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/antarctic/3/09.pal"
	.incbin "data/tilesets/antarctic/3/10.pal"
	.incbin "data/tilesets/antarctic/3/11.pal"
	.incbin "data/tilesets/antarctic/3/12.pal"
	.incbin "data/tilesets/antarctic/3/13.pal"
	.incbin "data/tilesets/antarctic/3/14.pal"
	.incbin "data/tilesets/antarctic/3/15.pal"

gAntarcticTilesetGraphics_4:
	.incbin "data/tilesets/antarctic/4/tiles.4bpp.lz"
	gAntarcticTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/antarctic/4/02.pal"
	.incbin "data/tilesets/antarctic/4/03.pal"
	.incbin "data/tilesets/antarctic/4/04.pal"
	.incbin "data/tilesets/antarctic/4/05.pal"
	.incbin "data/tilesets/antarctic/4/06.pal"
	.incbin "data/tilesets/antarctic/4/07.pal"

