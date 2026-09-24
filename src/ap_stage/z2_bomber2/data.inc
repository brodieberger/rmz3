@ Zero 2's BOMBER2: the desert surface, the crystal cave beneath it, the plant to the east

.balign 4

.global gApImp0_Terrain
gApImp0_Terrain:
	.4byte gApImp0_Metatiles-.
	.4byte gApImp0_Attrs-(.-4)
	.4byte gApImp0_Chunks-(.-8)

.global gApImp0_Tilesets
gApImp0_Tilesets: @ ColorGraphic[13]

gApImp0_Ts0:
	.4byte gApImp0_Ts0_Tiles-.
	.4byte 0 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts0_Pal-.
		.2byte 0
		.byte 0, 2

gApImp0_Ts1:
	.4byte gApImp0_Ts1_Tiles-.
	.4byte 12928 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts1_Pal-.
		.2byte 128
		.byte 0, 2

gApImp0_Ts2:
	.4byte gApImp0_Ts2_Tiles-.
	.4byte 16192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts2_Pal-.
		.2byte 96
		.byte 0, 9

gApImp0_Ts3:
	.4byte gApImp0_Ts3_Tiles-.
	.4byte 15744 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts3_Pal-.
		.2byte 224
		.byte 0, 2

gApImp0_Ts4:
	.4byte gApImp0_Ts4_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts4_Pal-.
		.2byte 224
		.byte 0, 9

gApImp0_Ts5:
	.4byte gApImp0_Ts5_Tiles-.
	.4byte 15744 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts5_Pal-.
		.2byte 224
		.byte 0, 2

gApImp0_Ts6:
	.4byte gApImp0_Ts6_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts6_Pal-.
		.2byte 224
		.byte 0, 2

gApImp0_Ts7:
	.4byte gApImp0_Ts7_Tiles-.
	.4byte 14144 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts7_Pal-.
		.2byte 160
		.byte 0, 9

gApImp0_Ts8:
	.4byte gApImp0_Ts8_Tiles-.
	.4byte 16320 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts8_Pal-.
		.2byte 224
		.byte 0, 2

gApImp0_Ts9:
	.4byte gApImp0_Ts9_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts9_Pal-.
		.2byte 96
		.byte 0, 9

gApImp0_Ts10:
	.4byte gApImp0_Ts10_Tiles-.
	.4byte 16320 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts10_Pal-.
		.2byte 192
		.byte 0, 9

gApImp0_Ts11:
	.4byte gApImp0_Ts11_Tiles-.
	.4byte 15296 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts11_Pal-.
		.2byte 96
		.byte 0, 2

gApImp0_Ts12:
	.4byte gApImp0_Ts12_Tiles-.
	.4byte 15168 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApImp0_Ts12_Pal-.
		.2byte 128
		.byte 0, 9

gApImp0_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

gApImp0_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 280*PX, 736*PX
	.4byte DIR_RIGHT

.global gApImp0_Script
gApImp0_Script:
	spawn 0, gApImp0_Zero
	reset_camera gApImp0_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm 176
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApImp0_Metatiles
gApImp0_Metatiles:
	.incbin "data/ap/z2_bomber2/metatile.bin"
	.balign 4, 0

.global gApImp0_Attrs
gApImp0_Attrs:
	.incbin "data/ap/z2_bomber2/metatile_attr.bin"
	.balign 4, 0

.global gApImp0_Chunks
gApImp0_Chunks:
	.incbin "data/ap/z2_bomber2/screen.bin"
	.balign 4, 0

gApImp0_Ts0_Tiles:
	.incbin "data/ap/z2_bomber2/tileset0.4bpp"
	.balign 4, 0
gApImp0_Ts0_Pal:
	.incbin "data/ap/z2_bomber2/tileset0.gbapal"
	.balign 4, 0

gApImp0_Ts1_Tiles:
	.incbin "data/ap/z2_bomber2/tileset1.4bpp"
	.balign 4, 0
gApImp0_Ts1_Pal:
	.incbin "data/ap/z2_bomber2/tileset1.gbapal"
	.balign 4, 0

gApImp0_Ts2_Tiles:
	.incbin "data/ap/z2_bomber2/tileset2.4bpp"
	.balign 4, 0
gApImp0_Ts2_Pal:
	.incbin "data/ap/z2_bomber2/tileset2.gbapal"
	.balign 4, 0

gApImp0_Ts3_Tiles:
	.incbin "data/ap/z2_bomber2/tileset3.4bpp"
	.balign 4, 0
gApImp0_Ts3_Pal:
	.incbin "data/ap/z2_bomber2/tileset3.gbapal"
	.balign 4, 0

gApImp0_Ts4_Tiles:
	.incbin "data/ap/z2_bomber2/tileset4.4bpp"
	.balign 4, 0
gApImp0_Ts4_Pal:
	.incbin "data/ap/z2_bomber2/tileset4.gbapal"
	.balign 4, 0

gApImp0_Ts5_Tiles:
	.incbin "data/ap/z2_bomber2/tileset5.4bpp"
	.balign 4, 0
gApImp0_Ts5_Pal:
	.incbin "data/ap/z2_bomber2/tileset5.gbapal"
	.balign 4, 0

gApImp0_Ts6_Tiles:
	.incbin "data/ap/z2_bomber2/tileset6.4bpp"
	.balign 4, 0
gApImp0_Ts6_Pal:
	.incbin "data/ap/z2_bomber2/tileset6.gbapal"
	.balign 4, 0

gApImp0_Ts7_Tiles:
	.incbin "data/ap/z2_bomber2/tileset7.4bpp"
	.balign 4, 0
gApImp0_Ts7_Pal:
	.incbin "data/ap/z2_bomber2/tileset7.gbapal"
	.balign 4, 0

gApImp0_Ts8_Tiles:
	.incbin "data/ap/z2_bomber2/tileset8.4bpp"
	.balign 4, 0
gApImp0_Ts8_Pal:
	.incbin "data/ap/z2_bomber2/tileset8.gbapal"
	.balign 4, 0

gApImp0_Ts9_Tiles:
	.incbin "data/ap/z2_bomber2/tileset9.4bpp"
	.balign 4, 0
gApImp0_Ts9_Pal:
	.incbin "data/ap/z2_bomber2/tileset9.gbapal"
	.balign 4, 0

gApImp0_Ts10_Tiles:
	.incbin "data/ap/z2_bomber2/tileset10.4bpp"
	.balign 4, 0
gApImp0_Ts10_Pal:
	.incbin "data/ap/z2_bomber2/tileset10.gbapal"
	.balign 4, 0

gApImp0_Ts11_Tiles:
	.incbin "data/ap/z2_bomber2/tileset11.4bpp"
	.balign 4, 0
gApImp0_Ts11_Pal:
	.incbin "data/ap/z2_bomber2/tileset11.gbapal"
	.balign 4, 0

gApImp0_Ts12_Tiles:
	.incbin "data/ap/z2_bomber2/tileset12.4bpp"
	.balign 4, 0
gApImp0_Ts12_Pal:
	.incbin "data/ap/z2_bomber2/tileset12.gbapal"
	.balign 4, 0
