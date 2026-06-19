.section .rodata
.balign 4, 0

.global gElevatorTilesetGraphics
gElevatorTilesetGraphics:
	@ Graphic 0
	.4byte gElevatorTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 9316 	@ size(bit0..21): 9316 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gElevatorTilesetGraphics_0_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gElevatorTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 8800 	@ size(bit0..21): 8800 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gElevatorTilesetGraphics_1_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gElevatorTilesetGraphics_2-. @ src offset
	.4byte (512 << 22) | 10928 	@ size(bit0..21): 10928 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gElevatorTilesetGraphics_2_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gElevatorTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 9036 	@ size(bit0..21): 9036 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gElevatorTilesetGraphics_3_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 4
	.4byte gElevatorTilesetGraphics_4-. @ src offset
	.4byte (0 << 22) | 11380 	@ size(bit0..21): 11380 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gElevatorTilesetGraphics_4_Palettes-. @ src offset
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gElevatorTilesetGraphics_0:
	.incbin "data/tilesets/giant_elevator/0/tiles.4bpp.lz"
	gElevatorTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/giant_elevator/0/02.pal"
	.incbin "data/tilesets/giant_elevator/0/03.pal"
	.incbin "data/tilesets/giant_elevator/0/04.pal"
	.incbin "data/tilesets/giant_elevator/0/05.pal"
	.incbin "data/tilesets/giant_elevator/0/06.pal"

gElevatorTilesetGraphics_1:
	.incbin "data/tilesets/giant_elevator/1/tiles.4bpp.lz"
	gElevatorTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/giant_elevator/1/09.pal"
	.incbin "data/tilesets/giant_elevator/1/10.pal"
	.incbin "data/tilesets/giant_elevator/1/11.pal"

gElevatorTilesetGraphics_2:
	.incbin "data/tilesets/giant_elevator/2/tiles.4bpp.lz"
	gElevatorTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/giant_elevator/2/09.pal"
	.incbin "data/tilesets/giant_elevator/2/10.pal"
	.incbin "data/tilesets/giant_elevator/2/11.pal"

gElevatorTilesetGraphics_3:
	.incbin "data/tilesets/giant_elevator/3/tiles.4bpp.lz"
	gElevatorTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/giant_elevator/3/09.pal"
	.incbin "data/tilesets/giant_elevator/3/10.pal"
	.incbin "data/tilesets/giant_elevator/3/11.pal"

gElevatorTilesetGraphics_4:
	.incbin "data/tilesets/giant_elevator/4/tiles.4bpp.lz"
	gElevatorTilesetGraphics_4_Palettes:
	.incbin "data/tilesets/giant_elevator/4/02.pal"
	.incbin "data/tilesets/giant_elevator/4/03.pal"
	.incbin "data/tilesets/giant_elevator/4/04.pal"

