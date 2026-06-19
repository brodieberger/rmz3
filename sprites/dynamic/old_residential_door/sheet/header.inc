.balign 4, 0

.global gGraphicHeader_Sprite_old_residential_door
gGraphicHeader_Sprite_old_residential_door:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_old_residential_door_0-. @ src
	.4byte 768 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 192, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_old_residential_door_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_old_residential_door_0:
	.incbin "sprites/dynamic/old_residential_door/sheet/0.4bpp"
	gGraphicHeader_Sprite_old_residential_door_0_Palettes:
	.incbin "sprites/dynamic/old_residential_door/sheet/0.gbapal"
