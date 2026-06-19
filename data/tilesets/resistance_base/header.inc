.section .rodata
.balign 4, 0

.global gResistanceBaseTilesetGraphics
gResistanceBaseTilesetGraphics:
	@ Graphic 0
	.4byte gResistanceBaseTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 6148 	@ size(bit0..21): 6148 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gResistanceBaseTilesetGraphics_1-. @ src offset
	.4byte (0 << 22) | 6892 	@ size(bit0..21): 6892 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gResistanceBaseTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_2_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gResistanceBaseTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gResistanceBaseTilesetGraphics_4-. @ src offset
	.4byte (0 << 22) | 8160 	@ size(bit0..21): 8160 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_4_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gResistanceBaseTilesetGraphics_5-. @ src offset
	.4byte (0 << 22) | 4788 	@ size(bit0..21): 4788 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gResistanceBaseTilesetGraphics_5_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gResistanceBaseTilesetGraphics_0:
	.incbin "data/tilesets/resistance_base/0/tiles.4bpp.lz"
	gResistanceBaseTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/resistance_base/0/02.pal"
	.incbin "data/tilesets/resistance_base/0/03.pal"
	.incbin "data/tilesets/resistance_base/0/04.pal"
	.incbin "data/tilesets/resistance_base/0/05.pal"
	.incbin "data/tilesets/resistance_base/0/06.pal"
	.incbin "data/tilesets/resistance_base/0/07.pal"
	.incbin "data/tilesets/resistance_base/0/08.pal"

gResistanceBaseTilesetGraphics_1:
	.incbin "data/tilesets/resistance_base/1/tiles.4bpp.lz"
	gResistanceBaseTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/resistance_base/1/02.pal"
	.incbin "data/tilesets/resistance_base/1/03.pal"
	.incbin "data/tilesets/resistance_base/1/04.pal"
	.incbin "data/tilesets/resistance_base/1/05.pal"
	.incbin "data/tilesets/resistance_base/1/06.pal"
	.incbin "data/tilesets/resistance_base/1/07.pal"
	.incbin "data/tilesets/resistance_base/1/08.pal"

gResistanceBaseTilesetGraphics_2:
	.incbin "data/tilesets/resistance_base/2/tiles.4bpp"
	gResistanceBaseTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/resistance_base/2/09.pal"
	.incbin "data/tilesets/resistance_base/2/10.pal"
	.incbin "data/tilesets/resistance_base/2/11.pal"
	.incbin "data/tilesets/resistance_base/2/12.pal"
	.incbin "data/tilesets/resistance_base/2/13.pal"
	.incbin "data/tilesets/resistance_base/2/14.pal"
	.incbin "data/tilesets/resistance_base/2/15.pal"

gResistanceBaseTilesetGraphics_3:
	.incbin "data/tilesets/resistance_base/3/tiles.4bpp"
	gResistanceBaseTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/resistance_base/3/09.pal"
	.incbin "data/tilesets/resistance_base/3/10.pal"
	.incbin "data/tilesets/resistance_base/3/11.pal"
	.incbin "data/tilesets/resistance_base/3/12.pal"
	.incbin "data/tilesets/resistance_base/3/13.pal"
	.incbin "data/tilesets/resistance_base/3/14.pal"
	.incbin "data/tilesets/resistance_base/3/15.pal"

gResistanceBaseTilesetGraphics_4:
	.incbin "data/tilesets/resistance_base/4/tiles.4bpp.lz"
	gResistanceBaseTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/resistance_base/4/02.pal"
	.incbin "data/tilesets/resistance_base/4/03.pal"
	.incbin "data/tilesets/resistance_base/4/04.pal"
	.incbin "data/tilesets/resistance_base/4/05.pal"
	.incbin "data/tilesets/resistance_base/4/06.pal"
	.incbin "data/tilesets/resistance_base/4/07.pal"
	.incbin "data/tilesets/resistance_base/4/08.pal"

gResistanceBaseTilesetGraphics_5:
	.incbin "data/tilesets/resistance_base/5/tiles.4bpp.lz"
	gResistanceBaseTilesetGraphics_5_Palettes:
	.incbin "data/tilesets/resistance_base/5/02.pal"
	.incbin "data/tilesets/resistance_base/5/03.pal"
	.incbin "data/tilesets/resistance_base/5/04.pal"
	.incbin "data/tilesets/resistance_base/5/05.pal"
	.incbin "data/tilesets/resistance_base/5/06.pal"

