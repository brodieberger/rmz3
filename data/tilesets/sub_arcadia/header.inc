.section .rodata
.balign 4, 0

.global gSubArcadiaTilesetGraphics
gSubArcadiaTilesetGraphics:
	@ Graphic 0
	.4byte gSubArcadiaTilesetGraphics_0-. @ src offset
	.4byte (0 << 22) | 8756 	@ size(bit0..21): 8756 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gSubArcadiaTilesetGraphics_0_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gSubArcadiaTilesetGraphics_1-. @ src offset
	.4byte (512 << 22) | 8636 	@ size(bit0..21): 8636 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gSubArcadiaTilesetGraphics_1_Palettes-. @ src offset
		.2byte 160 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gSubArcadiaTilesetGraphics_2-. @ src offset
	.4byte (0 << 22) | 5840 	@ size(bit0..21): 5840 Bytes, dst(bit22..) = VRAM+0
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gSubArcadiaTilesetGraphics_2_Palettes-. @ src offset
		.2byte 128 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 3
	.4byte gSubArcadiaTilesetGraphics_3-. @ src offset
	.4byte (512 << 22) | 10056 	@ size(bit0..21): 10056 Bytes, dst(bit22..) = VRAM+512
	.2byte 256, (LZ77 | BPP4) 	@ chunk size, props
		@ Palette
		.4byte gSubArcadiaTilesetGraphics_3_Palettes-. @ src offset
		.2byte 224 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gSubArcadiaTilesetGraphics_0:
	.incbin "data/tilesets/sub_arcadia/0/tiles.4bpp.lz"
	gSubArcadiaTilesetGraphics_0_Palettes:
	.incbin "data/tilesets/sub_arcadia/0/02.pal"
	.incbin "data/tilesets/sub_arcadia/0/03.pal"
	.incbin "data/tilesets/sub_arcadia/0/04.pal"
	.incbin "data/tilesets/sub_arcadia/0/05.pal"
	.incbin "data/tilesets/sub_arcadia/0/06.pal"
	.incbin "data/tilesets/sub_arcadia/0/07.pal"
	.incbin "data/tilesets/sub_arcadia/0/08.pal"

gSubArcadiaTilesetGraphics_1:
	.incbin "data/tilesets/sub_arcadia/1/tiles.4bpp.lz"
	gSubArcadiaTilesetGraphics_1_Palettes:
	.incbin "data/tilesets/sub_arcadia/1/09.pal"
	.incbin "data/tilesets/sub_arcadia/1/10.pal"
	.incbin "data/tilesets/sub_arcadia/1/11.pal"
	.incbin "data/tilesets/sub_arcadia/1/12.pal"
	.incbin "data/tilesets/sub_arcadia/1/13.pal"

gSubArcadiaTilesetGraphics_2:
	.incbin "data/tilesets/sub_arcadia/2/tiles.4bpp.lz"
	gSubArcadiaTilesetGraphics_2_Palettes:
	.incbin "data/tilesets/sub_arcadia/2/02.pal"
	.incbin "data/tilesets/sub_arcadia/2/03.pal"
	.incbin "data/tilesets/sub_arcadia/2/04.pal"
	.incbin "data/tilesets/sub_arcadia/2/05.pal"

gSubArcadiaTilesetGraphics_3:
	.incbin "data/tilesets/sub_arcadia/3/tiles.4bpp.lz"
	gSubArcadiaTilesetGraphics_3_Palettes:
	.incbin "data/tilesets/sub_arcadia/3/09.pal"
	.incbin "data/tilesets/sub_arcadia/3/10.pal"
	.incbin "data/tilesets/sub_arcadia/3/11.pal"
	.incbin "data/tilesets/sub_arcadia/3/12.pal"
	.incbin "data/tilesets/sub_arcadia/3/13.pal"
	.incbin "data/tilesets/sub_arcadia/3/14.pal"
	.incbin "data/tilesets/sub_arcadia/3/15.pal"

