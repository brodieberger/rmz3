.section .rodata
.balign 4, 0

.global gGraphicHeader_Sprite_zero_run
gGraphicHeader_Sprite_zero_run:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_run_0-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_run_1-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_run_2-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_run_3-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_run_4-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_run_5-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_run_6-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_run_7-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_run_8-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_zero_run_9-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_zero_run_10-. @ src
	.4byte 704 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 176, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_run_0:
	.incbin "sprites/dynamic/zero/run/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_run_0_Palettes:

gGraphicHeader_Sprite_zero_run_1:
	.incbin "sprites/dynamic/zero/run/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_run_1_Palettes:

gGraphicHeader_Sprite_zero_run_2:
	.incbin "sprites/dynamic/zero/run/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_run_2_Palettes:

gGraphicHeader_Sprite_zero_run_3:
	.incbin "sprites/dynamic/zero/run/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_run_3_Palettes:

gGraphicHeader_Sprite_zero_run_4:
	.incbin "sprites/dynamic/zero/run/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_run_4_Palettes:

gGraphicHeader_Sprite_zero_run_5:
	.incbin "sprites/dynamic/zero/run/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_run_5_Palettes:

gGraphicHeader_Sprite_zero_run_6:
	.incbin "sprites/dynamic/zero/run/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_run_6_Palettes:

gGraphicHeader_Sprite_zero_run_7:
	.incbin "sprites/dynamic/zero/run/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_run_7_Palettes:

gGraphicHeader_Sprite_zero_run_8:
	.incbin "sprites/dynamic/zero/run/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_run_8_Palettes:

gGraphicHeader_Sprite_zero_run_9:
	.incbin "sprites/dynamic/zero/run/sheet/9.4bpp"
	gGraphicHeader_Sprite_zero_run_9_Palettes:

gGraphicHeader_Sprite_zero_run_10:
	.incbin "sprites/dynamic/zero/run/sheet/10.4bpp"
	gGraphicHeader_Sprite_zero_run_10_Palettes:

