.section .rodata
.balign 4, 0

.global gFactoryTilesetGraphics
gFactoryTilesetGraphics:
	@ Graphic 0
	.4byte gFactoryTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 10124 	@ size(bit0..21): 10124 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gFactoryTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gFactoryTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 16128 	@ size(bit0..21): 16128 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gFactoryTilesetGraphics_1_Palettes-. @ src offset
		.2byte 128 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gFactoryTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 13888 	@ size(bit0..21): 13888 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gFactoryTilesetGraphics_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gFactoryTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gFactoryTilesetGraphics_3_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gFactoryTilesetGraphics_4-. @ src offset
	.4byte (512 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gFactoryTilesetGraphics_4_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gFactoryTilesetGraphics_0:
	.incbin "data/tilesets/factory/0/tiles.4bpp.lz"
	gFactoryTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/factory/0/02.pal"
	.incbin "data/tilesets/factory/0/03.pal"
	.incbin "data/tilesets/factory/0/04.pal"
	.incbin "data/tilesets/factory/0/05.pal"
	.incbin "data/tilesets/factory/0/06.pal"
	.incbin "data/tilesets/factory/0/07.pal"
	.incbin "data/tilesets/factory/0/08.pal"

gFactoryTilesetGraphics_1:
	.incbin "data/tilesets/factory/1/tiles.4bpp"
	gFactoryTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/factory/1/09.pal"
	.incbin "data/tilesets/factory/1/10.pal"
	.incbin "data/tilesets/factory/1/11.pal"
	.incbin "data/tilesets/factory/1/12.pal"

gFactoryTilesetGraphics_2:
	.incbin "data/tilesets/factory/2/tiles.4bpp"
	gFactoryTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/factory/2/09.pal"

gFactoryTilesetGraphics_3:
	.incbin "data/tilesets/factory/3/tiles.4bpp"
	gFactoryTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/factory/3/09.pal"
	.incbin "data/tilesets/factory/3/10.pal"
	.incbin "data/tilesets/factory/3/11.pal"
	.incbin "data/tilesets/factory/3/12.pal"
	.incbin "data/tilesets/factory/3/13.pal"
	.incbin "data/tilesets/factory/3/14.pal"

gFactoryTilesetGraphics_4:
	.incbin "data/tilesets/factory/4/tiles.4bpp"
	gFactoryTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/factory/4/09.pal"
	.incbin "data/tilesets/factory/4/10.pal"
	.incbin "data/tilesets/factory/4/11.pal"
	.incbin "data/tilesets/factory/4/12.pal"
	.incbin "data/tilesets/factory/4/13.pal"
	.incbin "data/tilesets/factory/4/14.pal"
	.incbin "data/tilesets/factory/4/15.pal"

