.section .rodata
.balign 4, 0

.global gRuinTilesetGraphics
gRuinTilesetGraphics:
	@ Graphic 0
	.4byte gRuinTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 11872 	@ size(bit0..21): 11872 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gRuinTilesetGraphics_0_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gRuinTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 10356 	@ size(bit0..21): 10356 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gRuinTilesetGraphics_1_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gRuinTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 11388 	@ size(bit0..21): 11388 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gRuinTilesetGraphics_2_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gRuinTilesetGraphics_3-. @ src offset
	.4byte (0 << 22) | 9492 	@ size(bit0..21): 9492 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gRuinTilesetGraphics_3_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gRuinTilesetGraphics_0:
	.incbin "data/tilesets/ruin/0/tiles.4bpp.lz"
	gRuinTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/ruin/0/02.pal"
	.incbin "data/tilesets/ruin/0/03.pal"
	.incbin "data/tilesets/ruin/0/04.pal"
	.incbin "data/tilesets/ruin/0/05.pal"
	.incbin "data/tilesets/ruin/0/06.pal"

gRuinTilesetGraphics_1:
	.incbin "data/tilesets/ruin/1/tiles.4bpp.lz"
	gRuinTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/ruin/1/09.pal"
	.incbin "data/tilesets/ruin/1/10.pal"
	.incbin "data/tilesets/ruin/1/11.pal"
	.incbin "data/tilesets/ruin/1/12.pal"
	.incbin "data/tilesets/ruin/1/13.pal"
	.incbin "data/tilesets/ruin/1/14.pal"

gRuinTilesetGraphics_2:
	.incbin "data/tilesets/ruin/2/tiles.4bpp.lz"
	gRuinTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/ruin/2/09.pal"
	.incbin "data/tilesets/ruin/2/10.pal"
	.incbin "data/tilesets/ruin/2/11.pal"
	.incbin "data/tilesets/ruin/2/12.pal"
	.incbin "data/tilesets/ruin/2/13.pal"

gRuinTilesetGraphics_3:
	.incbin "data/tilesets/ruin/3/tiles.4bpp.lz"
	gRuinTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/ruin/3/02.pal"
	.incbin "data/tilesets/ruin/3/03.pal"
	.incbin "data/tilesets/ruin/3/04.pal"

