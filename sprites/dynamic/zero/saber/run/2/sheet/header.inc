.balign 4, 0

.global gGraphicHeader_Sprite_zero_saber_run_2
gGraphicHeader_Sprite_zero_saber_run_2:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_0-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_1-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_2-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 3
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_3-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 4
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_4-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 5
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_5-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 6
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_6-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 7
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_7-. @ src
	.4byte 800 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 200, BPP4 	@ rowsize(unused), props

	@ Graphic 8
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_8-. @ src
	.4byte 736 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 184, BPP4 	@ rowsize(unused), props

	@ Graphic 9
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_9-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

	@ Graphic 10
	.4byte gGraphicHeader_Sprite_zero_saber_run_2_10-. @ src
	.4byte 768 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_zero_saber_run_2_0:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/0.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_0_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_1:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/1.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_1_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_2:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/2.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_2_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_3:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/3.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_3_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_4:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/4.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_4_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_5:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/5.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_5_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_6:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/6.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_6_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_7:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/7.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_7_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_8:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/8.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_8_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_9:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/9.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_9_Palettes:

gGraphicHeader_Sprite_zero_saber_run_2_10:
	.incbin "sprites/dynamic/zero/saber/run/2/sheet/10.4bpp"
	gGraphicHeader_Sprite_zero_saber_run_2_10_Palettes:
