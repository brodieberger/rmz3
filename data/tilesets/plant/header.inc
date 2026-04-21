.section .rodata
.balign 4, 0

.global gPlantTilesetGraphics
gPlantTilesetGraphics:
	@ Graphic 0
	.4byte gPlantTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gPlantTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gPlantTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 13440 	@ size(bit0..21): 13440 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gPlantTilesetGraphics_1_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gPlantTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 13888 	@ size(bit0..21): 13888 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gPlantTilesetGraphics_2_Palettes-. @ src offset
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gPlantTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 10944 	@ size(bit0..21): 10944 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gPlantTilesetGraphics_3_Palettes-. @ src offset
		.2byte 128 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gPlantTilesetGraphics_4-. @ src offset
	.4byte (512 << 22) | 16384 	@ size(bit0..21): 16384 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gPlantTilesetGraphics_4_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gPlantTilesetGraphics_0:
	.incbin "data/tilesets/plant/0/tiles.4bpp"
	gPlantTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/plant/0/02.pal"
	.incbin "data/tilesets/plant/0/03.pal"
	.incbin "data/tilesets/plant/0/04.pal"
	.incbin "data/tilesets/plant/0/05.pal"
	.incbin "data/tilesets/plant/0/06.pal"
	.incbin "data/tilesets/plant/0/07.pal"
	.incbin "data/tilesets/plant/0/08.pal"

gPlantTilesetGraphics_1:
	.incbin "data/tilesets/plant/1/tiles.4bpp"
	gPlantTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/plant/1/09.pal"
	.incbin "data/tilesets/plant/1/10.pal"
	.incbin "data/tilesets/plant/1/11.pal"
	.incbin "data/tilesets/plant/1/12.pal"
	.incbin "data/tilesets/plant/1/13.pal"
	.incbin "data/tilesets/plant/1/14.pal"
	.incbin "data/tilesets/plant/1/15.pal"

gPlantTilesetGraphics_2:
	.incbin "data/tilesets/plant/2/tiles.4bpp"
	gPlantTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/plant/2/02.pal"
	.incbin "data/tilesets/plant/2/03.pal"
	.incbin "data/tilesets/plant/2/04.pal"
	.incbin "data/tilesets/plant/2/05.pal"
	.incbin "data/tilesets/plant/2/06.pal"
	.incbin "data/tilesets/plant/2/07.pal"

gPlantTilesetGraphics_3:
	.incbin "data/tilesets/plant/3/tiles.4bpp"
	gPlantTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/plant/3/09.pal"
	.incbin "data/tilesets/plant/3/10.pal"
	.incbin "data/tilesets/plant/3/11.pal"
	.incbin "data/tilesets/plant/3/12.pal"

gPlantTilesetGraphics_4:
	.incbin "data/tilesets/plant/4/tiles.4bpp"
	gPlantTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/plant/4/09.pal"
	.incbin "data/tilesets/plant/4/10.pal"
	.incbin "data/tilesets/plant/4/11.pal"
	.incbin "data/tilesets/plant/4/12.pal"
	.incbin "data/tilesets/plant/4/13.pal"
	.incbin "data/tilesets/plant/4/14.pal"
	.incbin "data/tilesets/plant/4/15.pal"

