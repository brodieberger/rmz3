@ Zero 2's Elpizo_final, dynamic motion 172, Zero 3's DM217_Z2_ELPIZO_FINAL

.balign 4, 0

.global gGraphicHeader_Sprite_z2_elpizo_final
gGraphicHeader_Sprite_z2_elpizo_final:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_z2_elpizo_final_0-. @ src
	.4byte 3040 | (832 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 760, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_final_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_z2_elpizo_final_1-. @ src
	.4byte 3936 | (832 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 984, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_z2_elpizo_final_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 4 @ lz77(bool8), dst = PaletteID

gGraphicHeader_Sprite_z2_elpizo_final_0:
	.incbin "sprites/dynamic/z2_elpizo_final/sheet/0.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_final_0_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_final/sheet/0.gbapal"

gGraphicHeader_Sprite_z2_elpizo_final_1:
	.incbin "sprites/dynamic/z2_elpizo_final/sheet/1.4bpp"
	gGraphicHeader_Sprite_z2_elpizo_final_1_Palettes:
	.incbin "sprites/dynamic/z2_elpizo_final/sheet/1.gbapal"

.global gGraphicHeader_Sprite_z2_elpizo_final_End
gGraphicHeader_Sprite_z2_elpizo_final_End:
