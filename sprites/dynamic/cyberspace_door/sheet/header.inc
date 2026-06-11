.balign 4, 0

.global gGraphicHeader_Sprite_cyberspace_door
gGraphicHeader_Sprite_cyberspace_door:
	@ Graphic 0
	.4byte gGraphicHeader_Sprite_cyberspace_door_0-. @ src
	.4byte 960 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberspace_door_0_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 1
	.4byte gGraphicHeader_Sprite_cyberspace_door_1-. @ src
	.4byte 960 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberspace_door_1_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Graphic 2
	.4byte gGraphicHeader_Sprite_cyberspace_door_2-. @ src
	.4byte 960 | (380 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 240, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte gGraphicHeader_Sprite_cyberspace_door_2_Palettes-. @ src offset
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

gGraphicHeader_Sprite_cyberspace_door_0:
	.incbin "sprites/dynamic/cyberspace_door/sheet/0.4bpp"
	gGraphicHeader_Sprite_cyberspace_door_0_Palettes:
	.incbin "sprites/dynamic/cyberspace_door/sheet/0.gbapal"

gGraphicHeader_Sprite_cyberspace_door_1:
	.incbin "sprites/dynamic/cyberspace_door/sheet/1.4bpp"
	gGraphicHeader_Sprite_cyberspace_door_1_Palettes:
	.incbin "sprites/dynamic/cyberspace_door/sheet/1.gbapal"

gGraphicHeader_Sprite_cyberspace_door_2:
	.incbin "sprites/dynamic/cyberspace_door/sheet/2.4bpp"
	gGraphicHeader_Sprite_cyberspace_door_2_Palettes:
	.incbin "sprites/dynamic/cyberspace_door/sheet/2.gbapal"
