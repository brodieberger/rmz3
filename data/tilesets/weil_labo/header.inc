.section .rodata
.balign 4, 0

.global gWeilLaboTilesetGraphics
gWeilLaboTilesetGraphics:
	@ Graphic 0
	.4byte gWeilLaboTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 8484 	@ size(bit0..21): 8484 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gWeilLaboTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 11160 	@ size(bit0..21): 11160 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_1_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gWeilLaboTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 3900 	@ size(bit0..21): 3900 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_2_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gWeilLaboTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 10268 	@ size(bit0..21): 10268 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gWeilLaboTilesetGraphics_4-. @ src offset
	.4byte (0 << 22) | 7652 	@ size(bit0..21): 7652 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_4_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gWeilLaboTilesetGraphics_5-. @ src offset
	.4byte (512 << 22) | 7368 	@ size(bit0..21): 7368 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_5_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gWeilLaboTilesetGraphics_6-. @ src offset
	.4byte (0 << 22) | 13224 	@ size(bit0..21): 13224 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gWeilLaboTilesetGraphics_6_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gWeilLaboTilesetGraphics_0:
	.incbin "data/tilesets/weil_labo/0/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/weil_labo/0/02.pal"
	.incbin "data/tilesets/weil_labo/0/03.pal"
	.incbin "data/tilesets/weil_labo/0/04.pal"
	.incbin "data/tilesets/weil_labo/0/05.pal"
	.incbin "data/tilesets/weil_labo/0/06.pal"
	.incbin "data/tilesets/weil_labo/0/07.pal"
	.incbin "data/tilesets/weil_labo/0/08.pal"

gWeilLaboTilesetGraphics_1:
	.incbin "data/tilesets/weil_labo/1/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/weil_labo/1/09.pal"
	.incbin "data/tilesets/weil_labo/1/10.pal"
	.incbin "data/tilesets/weil_labo/1/11.pal"
	.incbin "data/tilesets/weil_labo/1/12.pal"
	.incbin "data/tilesets/weil_labo/1/13.pal"
	.incbin "data/tilesets/weil_labo/1/14.pal"

gWeilLaboTilesetGraphics_2:
	.incbin "data/tilesets/weil_labo/2/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/weil_labo/2/02.pal"
	.incbin "data/tilesets/weil_labo/2/03.pal"
	.incbin "data/tilesets/weil_labo/2/04.pal"
	.incbin "data/tilesets/weil_labo/2/05.pal"
	.incbin "data/tilesets/weil_labo/2/06.pal"

gWeilLaboTilesetGraphics_3:
	.incbin "data/tilesets/weil_labo/3/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/weil_labo/3/09.pal"
	.incbin "data/tilesets/weil_labo/3/10.pal"
	.incbin "data/tilesets/weil_labo/3/11.pal"
	.incbin "data/tilesets/weil_labo/3/12.pal"
	.incbin "data/tilesets/weil_labo/3/13.pal"
	.incbin "data/tilesets/weil_labo/3/14.pal"
	.incbin "data/tilesets/weil_labo/3/15.pal"

gWeilLaboTilesetGraphics_4:
	.incbin "data/tilesets/weil_labo/4/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/weil_labo/4/02.pal"
	.incbin "data/tilesets/weil_labo/4/03.pal"
	.incbin "data/tilesets/weil_labo/4/04.pal"

gWeilLaboTilesetGraphics_5:
	.incbin "data/tilesets/weil_labo/5/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_5_Palettes:
	.incbin "data/tilesets/weil_labo/5/09.pal"
	.incbin "data/tilesets/weil_labo/5/10.pal"
	.incbin "data/tilesets/weil_labo/5/11.pal"
	.incbin "data/tilesets/weil_labo/5/12.pal"
	.incbin "data/tilesets/weil_labo/5/13.pal"
	.incbin "data/tilesets/weil_labo/5/14.pal"

gWeilLaboTilesetGraphics_6:
	.incbin "data/tilesets/weil_labo/6/tiles.4bpp.lz"
	gWeilLaboTilesetGraphics_6_Palettes:
	.incbin "data/tilesets/weil_labo/6/02.pal"
	.incbin "data/tilesets/weil_labo/6/03.pal"
	.incbin "data/tilesets/weil_labo/6/04.pal"
	.incbin "data/tilesets/weil_labo/6/05.pal"
	.incbin "data/tilesets/weil_labo/6/06.pal"
	.incbin "data/tilesets/weil_labo/6/07.pal"
	.incbin "data/tilesets/weil_labo/6/08.pal"

