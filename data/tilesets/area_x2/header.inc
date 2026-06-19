.section .rodata
.balign 4, 0

.global gAreaX2TilesetGraphics
gAreaX2TilesetGraphics:
	@ Graphic 0
	.4byte gAreaX2TilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 8916 	@ size(bit0..21): 8916 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAreaX2TilesetGraphics_0_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gAreaX2TilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 7392 	@ size(bit0..21): 7392 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAreaX2TilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gAreaX2TilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 8456 	@ size(bit0..21): 8456 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAreaX2TilesetGraphics_2_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gAreaX2TilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 6932 	@ size(bit0..21): 6932 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gAreaX2TilesetGraphics_3_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gAreaX2TilesetGraphics_0:
	.incbin "data/tilesets/area_x2/0/tiles.4bpp.lz"
	gAreaX2TilesetGraphics_0_Palettes:
	.incbin "data/tilesets/area_x2/0/02.pal"
	.incbin "data/tilesets/area_x2/0/03.pal"
	.incbin "data/tilesets/area_x2/0/04.pal"
	.incbin "data/tilesets/area_x2/0/05.pal"
	.incbin "data/tilesets/area_x2/0/06.pal"
	.incbin "data/tilesets/area_x2/0/07.pal"

gAreaX2TilesetGraphics_1:
	.incbin "data/tilesets/area_x2/1/tiles.4bpp.lz"
	gAreaX2TilesetGraphics_1_Palettes:
	.incbin "data/tilesets/area_x2/1/09.pal"
	.incbin "data/tilesets/area_x2/1/10.pal"
	.incbin "data/tilesets/area_x2/1/11.pal"
	.incbin "data/tilesets/area_x2/1/12.pal"
	.incbin "data/tilesets/area_x2/1/13.pal"
	.incbin "data/tilesets/area_x2/1/14.pal"
	.incbin "data/tilesets/area_x2/1/15.pal"

gAreaX2TilesetGraphics_2:
	.incbin "data/tilesets/area_x2/2/tiles.4bpp.lz"
	gAreaX2TilesetGraphics_2_Palettes:
	.incbin "data/tilesets/area_x2/2/09.pal"
	.incbin "data/tilesets/area_x2/2/10.pal"
	.incbin "data/tilesets/area_x2/2/11.pal"
	.incbin "data/tilesets/area_x2/2/12.pal"
	.incbin "data/tilesets/area_x2/2/13.pal"

gAreaX2TilesetGraphics_3:
	.incbin "data/tilesets/area_x2/3/tiles.4bpp.lz"
	gAreaX2TilesetGraphics_3_Palettes:
	.incbin "data/tilesets/area_x2/3/09.pal"
	.incbin "data/tilesets/area_x2/3/10.pal"
	.incbin "data/tilesets/area_x2/3/11.pal"

