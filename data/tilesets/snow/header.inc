.section .rodata
.balign 4, 0

.global gSnowTilesetGraphics
gSnowTilesetGraphics:
	@ Graphic 0
	.4byte gSnowTilesetGraphic0-. @ src
	.4byte 15424 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic0_Palettes-. @ src
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77, palette_ID
	@ Graphic 1
	.4byte gSnowTilesetGraphic1-. @ src
	.4byte 2147494656 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic1_Palettes-. @ src
		.2byte 128 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 2
	.4byte gSnowTilesetGraphic2-. @ src
	.4byte 2147498560 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic2_Palettes-. @ src
		.2byte 192 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 3
	.4byte gSnowTilesetGraphic3-. @ src
	.4byte 10944 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic3_Palettes-. @ src
		.2byte 192 @ bytesize
		.byte 0, 2 @ lz77, palette_ID
	@ Graphic 4
	.4byte gSnowTilesetGraphic4-. @ src
	.4byte 2147492052 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic4_Palettes-. @ src
		.2byte 128 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 5
	.4byte gSnowTilesetGraphic5-. @ src
	.4byte 2147499968 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic5_Palettes-. @ src
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 6
	.4byte gSnowTilesetGraphic6-. @ src
	.4byte 2147498112 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic6_Palettes-. @ src
		.2byte 64 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 7
	.4byte gSnowTilesetGraphic7-. @ src
	.4byte 2147499008 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, BPP4 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic7_Palettes-. @ src
		.2byte 160 @ bytesize
		.byte 0, 9 @ lz77, palette_ID
	@ Graphic 8
	.4byte gSnowTilesetGraphic8-. @ src
	.4byte 11268 	@ bits 0..21: bytesize, 22..: dst offset in VRAM
	.2byte 256, (BPP4 | LZ77) 	@ chunk size, props
		@ Palette
		.4byte gSnowTilesetGraphic8_Palettes-. @ src
		.2byte 64 @ bytesize
		.byte 0, 2 @ lz77, palette_ID

	@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ GraphicData:
gSnowTilesetGraphic0:
	.incbin "data/tilesets/snow/0/tiles.4bpp"
gSnowTilesetGraphic0_Palettes:
	.incbin "data/tilesets/snow/0/02.pal"
	.incbin "data/tilesets/snow/0/03.pal"
	.incbin "data/tilesets/snow/0/04.pal"

gSnowTilesetGraphic1:
	.incbin "data/tilesets/snow/1/tiles.4bpp"
gSnowTilesetGraphic1_Palettes:
	.incbin "data/tilesets/snow/1/09.pal"
	.incbin "data/tilesets/snow/1/10.pal"
	.incbin "data/tilesets/snow/1/11.pal"
	.incbin "data/tilesets/snow/1/12.pal"

gSnowTilesetGraphic2:
	.incbin "data/tilesets/snow/2/tiles.4bpp"
gSnowTilesetGraphic2_Palettes:
	.incbin "data/tilesets/snow/2/09.pal"
	.incbin "data/tilesets/snow/2/10.pal"
	.incbin "data/tilesets/snow/2/11.pal"
	.incbin "data/tilesets/snow/2/12.pal"
	.incbin "data/tilesets/snow/2/13.pal"
	.incbin "data/tilesets/snow/2/14.pal"

gSnowTilesetGraphic3:
	.incbin "data/tilesets/snow/3/tiles.4bpp"
gSnowTilesetGraphic3_Palettes:
	.incbin "data/tilesets/snow/3/02.pal"
	.incbin "data/tilesets/snow/3/03.pal"
	.incbin "data/tilesets/snow/3/04.pal"
	.incbin "data/tilesets/snow/3/05.pal"
	.incbin "data/tilesets/snow/3/06.pal"
	.incbin "data/tilesets/snow/3/07.pal"

gSnowTilesetGraphic4:
	.incbin "data/tilesets/snow/4/tiles.4bpp.lz"
gSnowTilesetGraphic4_Palettes:
	.incbin "data/tilesets/snow/4/09.pal"
	.incbin "data/tilesets/snow/4/10.pal"
	.incbin "data/tilesets/snow/4/11.pal"
	.incbin "data/tilesets/snow/4/12.pal"

gSnowTilesetGraphic5:
	.incbin "data/tilesets/snow/5/tiles.4bpp"
gSnowTilesetGraphic5_Palettes:
	.incbin "data/tilesets/snow/5/09.pal"
	.incbin "data/tilesets/snow/5/10.pal"
	.incbin "data/tilesets/snow/5/11.pal"

gSnowTilesetGraphic6:
	.incbin "data/tilesets/snow/6/tiles.4bpp"
gSnowTilesetGraphic6_Palettes:
	.incbin "data/tilesets/snow/6/09.pal"
	.incbin "data/tilesets/snow/6/10.pal"

gSnowTilesetGraphic7:
	.incbin "data/tilesets/snow/7/tiles.4bpp"
gSnowTilesetGraphic7_Palettes:
	.incbin "data/tilesets/snow/7/09.pal"
	.incbin "data/tilesets/snow/7/10.pal"
	.incbin "data/tilesets/snow/7/11.pal"
	.incbin "data/tilesets/snow/7/12.pal"
	.incbin "data/tilesets/snow/7/13.pal"

gSnowTilesetGraphic8:
	.incbin "data/tilesets/snow/8/tiles.4bpp.lz"
gSnowTilesetGraphic8_Palettes:
	.incbin "data/tilesets/snow/8/02.pal"
	.incbin "data/tilesets/snow/8/03.pal"
