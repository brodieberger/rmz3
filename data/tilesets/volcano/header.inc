.section .rodata
.balign 4, 0

.global gVolcanoTilesetGraphics
gVolcanoTilesetGraphics:
	@ Graphic 0
	.4byte gVolcanoTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_0_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gVolcanoTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 15360 	@ size(bit0..21): 15360 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_1_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gVolcanoTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 14784 	@ size(bit0..21): 14784 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_2_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gVolcanoTilesetGraphics_3-. @ src offset
	.4byte (0 << 22) | 16256 	@ size(bit0..21): 16256 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gVolcanoTilesetGraphics_4-. @ src offset
	.4byte (512 << 22) | 7980 	@ size(bit0..21): 7980 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_4_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 5
	.4byte gVolcanoTilesetGraphics_5-. @ src offset
	.4byte (0 << 22) | 7892 	@ size(bit0..21): 7892 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_5_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 6
	.4byte gVolcanoTilesetGraphics_6-. @ src offset
	.4byte (0 << 22) | 5380 	@ size(bit0..21): 5380 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gVolcanoTilesetGraphics_6_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gVolcanoTilesetGraphics_0:
	.incbin "data/tilesets/volcano/0/tiles.4bpp"
	gVolcanoTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/volcano/0/02.pal"
	.incbin "data/tilesets/volcano/0/03.pal"
	.incbin "data/tilesets/volcano/0/04.pal"
	.incbin "data/tilesets/volcano/0/05.pal"
	.incbin "data/tilesets/volcano/0/06.pal"
	.incbin "data/tilesets/volcano/0/07.pal"

gVolcanoTilesetGraphics_1:
	.incbin "data/tilesets/volcano/1/tiles.4bpp"
	gVolcanoTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/volcano/1/09.pal"
	.incbin "data/tilesets/volcano/1/10.pal"
	.incbin "data/tilesets/volcano/1/11.pal"
	.incbin "data/tilesets/volcano/1/12.pal"
	.incbin "data/tilesets/volcano/1/13.pal"
	.incbin "data/tilesets/volcano/1/14.pal"

gVolcanoTilesetGraphics_2:
	.incbin "data/tilesets/volcano/2/tiles.4bpp"
	gVolcanoTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/volcano/2/09.pal"
	.incbin "data/tilesets/volcano/2/10.pal"
	.incbin "data/tilesets/volcano/2/11.pal"
	.incbin "data/tilesets/volcano/2/12.pal"
	.incbin "data/tilesets/volcano/2/13.pal"
	.incbin "data/tilesets/volcano/2/14.pal"

gVolcanoTilesetGraphics_3:
	.incbin "data/tilesets/volcano/3/tiles.4bpp"
	gVolcanoTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/volcano/3/02.pal"
	.incbin "data/tilesets/volcano/3/03.pal"
	.incbin "data/tilesets/volcano/3/04.pal"
	.incbin "data/tilesets/volcano/3/05.pal"
	.incbin "data/tilesets/volcano/3/06.pal"
	.incbin "data/tilesets/volcano/3/07.pal"
	.incbin "data/tilesets/volcano/3/08.pal"

gVolcanoTilesetGraphics_4:
	.incbin "data/tilesets/volcano/4/tiles.4bpp.lz"
	gVolcanoTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/volcano/4/09.pal"
	.incbin "data/tilesets/volcano/4/10.pal"
	.incbin "data/tilesets/volcano/4/11.pal"
	.incbin "data/tilesets/volcano/4/12.pal"
	.incbin "data/tilesets/volcano/4/13.pal"
	.incbin "data/tilesets/volcano/4/14.pal"

gVolcanoTilesetGraphics_5:
	.incbin "data/tilesets/volcano/5/tiles.4bpp.lz"
	gVolcanoTilesetGraphics_5_Palettes:
	.incbin "data/tilesets/volcano/5/02.pal"
	.incbin "data/tilesets/volcano/5/03.pal"
	.incbin "data/tilesets/volcano/5/04.pal"
	.incbin "data/tilesets/volcano/5/05.pal"
	.incbin "data/tilesets/volcano/5/06.pal"
	.incbin "data/tilesets/volcano/5/07.pal"

gVolcanoTilesetGraphics_6:
	.incbin "data/tilesets/volcano/6/tiles.4bpp.lz"
	gVolcanoTilesetGraphics_6_Palettes:
	.incbin "data/tilesets/volcano/6/02.pal"
	.incbin "data/tilesets/volcano/6/03.pal"
	.incbin "data/tilesets/volcano/6/04.pal"

