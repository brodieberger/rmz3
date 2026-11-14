@ Zero 2's ICE2 AKA Computer Zone 2

.balign 4

.global gApZ2Ice2_Terrain
gApZ2Ice2_Terrain:
	.4byte gApZ2Ice2_Metatiles-.
	.4byte gApZ2Ice2_Attrs-(.-4)
	.4byte gApZ2Ice2_Chunks-(.-8)

.global gApZ2Ice2_Tilesets
gApZ2Ice2_Tilesets: @ ColorGraphic[9]

gApZ2Ice2_Ts0:
	.4byte gApZ2Ice2_Ts0_Tiles-.
	.4byte 16320 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice2_Ts0_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice2_Ts1:
	.4byte gApZ2Ice2_Ts1_Tiles-.
	.4byte 14208 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice2_Ts1_Pal-.
		.2byte 64
		.byte 0, 9

gApZ2Ice2_Ts2:
	.4byte gApZ2Ice2_Ts2_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice2_Ts2_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice2_Ts3:
	.4byte gApZ2Ice2_Ts3_Tiles-.
	.4byte 8192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice2_Ts3_Pal-.
		.2byte 160
		.byte 0, 9

gApZ2Ice2_Ts4:
	.4byte gApZ2Ice2_Ts4_Tiles-.
	.4byte 6912 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice2_Ts4_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Ice2_Ts5:
	.4byte gApZ2Ice2_Ts5_Tiles-.
	.4byte 6104 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice2_Ts5_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice2_Ts6:
	.4byte gApZ2Ice2_Ts6_Tiles-.
	.4byte 6492 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice2_Ts6_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice2_Ts7:
	.4byte gApZ2Ice2_Ts7_Tiles-.
	.4byte 4924 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice2_Ts7_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Ice2_Ts8:
	.4byte gApZ2Ice2_Ts8_Tiles-.
	.4byte 3700 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice2_Ts8_Pal-.
		.2byte 64
		.byte 0, 9

gApZ2Ice2_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 480*PX, 1184*PX
	.4byte DIR_RIGHT

gApZ2Ice2_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice2_Script
gApZ2Ice2_Script:
	spawn 0, gApZ2Ice2_Zero
	reset_camera gApZ2Ice2_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_COMPUTER_ZONE_2
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x1441
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice2_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 480*PX, 1184*PX
	.4byte DIR_RIGHT

gApZ2Ice2_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice2_AgainScript
gApZ2Ice2_AgainScript:
	spawn 0, gApZ2Ice2_AgainZero
	reset_camera gApZ2Ice2_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_COMPUTER_ZONE_2
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice2_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 8272*PX, 2000*PX
	.4byte DIR_RIGHT

gApZ2Ice2_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 2016*PX

.global gApZ2Ice2_CheckpointScript
gApZ2Ice2_CheckpointScript:
	spawn 0, gApZ2Ice2_CheckpointZero
	reset_camera gApZ2Ice2_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice2_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 8272*PX, 2000*PX
	.4byte DIR_RIGHT

gApZ2Ice2_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 2016*PX

.global gApZ2Ice2_BossRestartScript
gApZ2Ice2_BossRestartScript:
	spawn 0, gApZ2Ice2_BossRestartZero
	reset_camera gApZ2Ice2_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Ice2_ResultScript
gApZ2Ice2_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Ice2_Leviathan:
	.byte ENTITY_BOSS, BOSS_Z2_LEVIATHAN_FIRST, 0, 0
	.4byte 8400*PX, 1920*PX
	.4byte DIR_LEFT

gApZ2Ice2_BossCamera: @ Zero 2's, 0x0832bf80
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 8400*PX, 8784*PX, 1840*PX, 2128*PX

@ Zero 2's script 3, the line once a visit
.global gApZ2Ice2_BossScript
gApZ2Ice2_BossScript:
	reset_camera gApZ2Ice2_BossCamera
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	wait 20
	play_bgm BGM_X
	force 0, 0, 0
	lock
	spawn 1, gApZ2Ice2_Leviathan
	wait 60
	play_se SE_Z2_WATER
	gimmick 1, 0, 1
	wait 240
	stop_se SE_Z2_WATER
	wait 16
	cutscene_start CS_UNK_48
	message 1, 0, 0x1442
	wait_msgbox_end
	cutscene_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Ice2_BossReturnScript
gApZ2Ice2_BossReturnScript:
	reset_camera gApZ2Ice2_BossCamera
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	wait 20
	play_bgm BGM_X
	force 0, 0, 0
	lock
	spawn 1, gApZ2Ice2_Leviathan
	wait 60
	play_se SE_Z2_WATER
	gimmick 1, 0, 1
	wait 240
	stop_se SE_Z2_WATER
	wait 16
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 4
.global gApZ2Ice2_ClearScript
gApZ2Ice2_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	wait 30
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 2
	adjust_camera 2, 0, 1
	wait 90
	play_bgm BGM_Z2_GUARDIAN_RETREAT
	wait 60
	adjust_camera 0, 0, 1
	message 1, 0, 0x1443
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	adjust_camera 2, 0, 0
	wait 60
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	stop_bgm
	wait 60
	start_transition 6
	wait_transition_end
	wait 30
	destroy 1
	stop_camera
	backdrop_color 0xFFFF
	start_transition 5
	wait 60
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Ice2_PlttAnim83
gApZ2Ice2_PlttAnim83: @ Zero 2's palette animation 83
	.byte 12, 75, 95, 0
	.2byte 0x20D8, 0x1072, 0x0C4B, 0x0C4B, 0x1072, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0437, 0x0832, 0x0C4C, 0x1066
	.2byte 0x20D9, 0x1074, 0x0C4B, 0x106F, 0x1495, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0832, 0x0C4C, 0x1066, 0x0437
	.2byte 0x1CDB, 0x1075, 0x0C4C, 0x1493, 0x14B8, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0C4C, 0x1066, 0x0437, 0x0832
	.2byte 0x1CDC, 0x0C77, 0x0C4C, 0x18B7, 0x18DA, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x1066, 0x0437, 0x0832, 0x0C4C
	.2byte 0x1CBE, 0x0C79, 0x0C4D, 0x1CDB, 0x1CDD, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0437, 0x0832, 0x0C4C, 0x1066
	.2byte 0x18BF, 0x0C5A, 0x0C4D, 0x211F, 0x20FF, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0832, 0x0C4C, 0x1066, 0x0437
	.2byte 0x18DF, 0x0C5A, 0x0C4E, 0x295F, 0x251F, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0C4C, 0x1066, 0x0437, 0x0832
	.2byte 0x18BF, 0x0C5A, 0x0C4D, 0x211F, 0x20FF, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x1066, 0x0437, 0x0832, 0x0C4C
	.2byte 0x18BE, 0x0C59, 0x0C4D, 0x1CDB, 0x1CFD, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0437, 0x0832, 0x0C4C, 0x1066
	.2byte 0x1CBC, 0x0C77, 0x0C4C, 0x18B7, 0x18DA, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0832, 0x0C4C, 0x1066, 0x0437
	.2byte 0x1CDB, 0x1075, 0x0C4C, 0x1493, 0x14B7, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x0C4C, 0x1066, 0x0437, 0x0832
	.2byte 0x20D9, 0x1074, 0x0C4B, 0x0C6E, 0x1494, 0x4811, 0x1864, 0x492B, 0x6211, 0x7693, 0x4188, 0x5A4F, 0x6ED3, 0x7F59, 0x7FFF, 0x2D6A, 0x4E52, 0x1066, 0x0437, 0x0832, 0x0C4C
	.balign 4, 0
.global gApZ2Ice2_PlttAnimScript83
gApZ2Ice2_PlttAnimScript83:
	.4byte gApZ2Ice2_PlttAnimScript83_0
gApZ2Ice2_PlttAnimScript83_0:
	.byte 0, 14
	.byte 1, 14
	.byte 2, 14
	.byte 3, 14
	.byte 4, 14
	.byte 5, 14
	.byte 6, 14
	.byte 7, 14
	.byte 8, 14
	.byte 9, 14
	.byte 10, 14
	.byte 11, 14
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice2_PlttAnim84
gApZ2Ice2_PlttAnim84: @ Zero 2's palette animation 84
	.byte 8, 172, 175, 0
	.2byte 0x0C40, 0x0C40, 0x0C40, 0x0C40
	.2byte 0x0C40, 0x0C40, 0x0C40, 0x043F
	.2byte 0x0C40, 0x0C40, 0x043F, 0x0435
	.2byte 0x0C40, 0x043F, 0x0435, 0x084A
	.2byte 0x043F, 0x0435, 0x084A, 0x0C40
	.2byte 0x0435, 0x084A, 0x0C40, 0x0C40
	.2byte 0x084A, 0x0C40, 0x0C40, 0x0C40
	.2byte 0x0C40, 0x0C40, 0x0C40, 0x0C40
	.balign 4, 0
.global gApZ2Ice2_PlttAnimScript84
gApZ2Ice2_PlttAnimScript84:
	.4byte gApZ2Ice2_PlttAnimScript84_0
gApZ2Ice2_PlttAnimScript84_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 4, 8
	.byte 5, 8
	.byte 6, 8
	.byte 7, 30
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice2_PlttAnim92
gApZ2Ice2_PlttAnim92: @ Zero 2's palette animation 92
	.byte 1, 0, 15, 0
	.2byte 0x0000, 0x7E6A, 0x7B2E, 0x73F3, 0x7BF9, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	.balign 4, 0
.global gApZ2Ice2_PlttAnimScript92
gApZ2Ice2_PlttAnimScript92:
	.4byte gApZ2Ice2_PlttAnimScript92_0
gApZ2Ice2_PlttAnimScript92_0:
	.byte 0, 1
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Ice2_Metatiles
gApZ2Ice2_Metatiles:
	.incbin "data/ap/z2_ice2/metatile.bin"
	.balign 4, 0

.global gApZ2Ice2_Attrs
gApZ2Ice2_Attrs:
	.incbin "data/ap/z2_ice2/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Ice2_Chunks
gApZ2Ice2_Chunks:
	.incbin "data/ap/z2_ice2/screen.bin"
	.balign 4, 0

gApZ2Ice2_Ts0_Tiles:
	.incbin "data/ap/z2_ice2/tileset0.4bpp"
	.balign 4, 0
gApZ2Ice2_Ts0_Pal:
	.incbin "data/ap/z2_ice2/tileset0.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts1_Tiles:
	.incbin "data/ap/z2_ice2/tileset1.4bpp"
	.balign 4, 0
gApZ2Ice2_Ts1_Pal:
	.incbin "data/ap/z2_ice2/tileset1.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts2_Tiles:
	.incbin "data/ap/z2_ice2/tileset2.4bpp"
	.balign 4, 0
gApZ2Ice2_Ts2_Pal:
	.incbin "data/ap/z2_ice2/tileset2.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts3_Tiles:
	.incbin "data/ap/z2_ice2/tileset3.4bpp"
	.balign 4, 0
gApZ2Ice2_Ts3_Pal:
	.incbin "data/ap/z2_ice2/tileset3.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts4_Tiles:
	.incbin "data/ap/z2_ice2/tileset4.4bpp.lz"
	.balign 4, 0
gApZ2Ice2_Ts4_Pal:
	.incbin "data/ap/z2_ice2/tileset4.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts5_Tiles:
	.incbin "data/ap/z2_ice2/tileset5.4bpp.lz"
	.balign 4, 0
gApZ2Ice2_Ts5_Pal:
	.incbin "data/ap/z2_ice2/tileset5.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts6_Tiles:
	.incbin "data/ap/z2_ice2/tileset6.4bpp.lz"
	.balign 4, 0
gApZ2Ice2_Ts6_Pal:
	.incbin "data/ap/z2_ice2/tileset6.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts7_Tiles:
	.incbin "data/ap/z2_ice2/tileset7.4bpp.lz"
	.balign 4, 0
gApZ2Ice2_Ts7_Pal:
	.incbin "data/ap/z2_ice2/tileset7.gbapal"
	.balign 4, 0

gApZ2Ice2_Ts8_Tiles:
	.incbin "data/ap/z2_ice2/tileset8.4bpp.lz"
	.balign 4, 0
gApZ2Ice2_Ts8_Pal:
	.incbin "data/ap/z2_ice2/tileset8.gbapal"
	.balign 4, 0
