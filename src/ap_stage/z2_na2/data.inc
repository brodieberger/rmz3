@ Zero 2's NA-2 AKA Temple of Ice

.balign 4

.global gApZ2Na2_Terrain
gApZ2Na2_Terrain:
	.4byte gApZ2Na2_Metatiles-.
	.4byte gApZ2Na2_Attrs-(.-4)
	.4byte gApZ2Na2_Chunks-(.-8)

.global gApZ2Na2_Tilesets
gApZ2Na2_Tilesets: @ ColorGraphic[6]

gApZ2Na2_Ts0:
	.4byte gApZ2Na2_Ts0_Tiles-.
	.4byte 7616 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na2_Ts0_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na2_Ts1:
	.4byte gApZ2Na2_Ts1_Tiles-.
	.4byte 4800 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na2_Ts1_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na2_Ts2:
	.4byte gApZ2Na2_Ts2_Tiles-.
	.4byte 7368 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na2_Ts2_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Na2_Ts3:
	.4byte gApZ2Na2_Ts3_Tiles-.
	.4byte 6100 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na2_Ts3_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Na2_Ts4:
	.4byte gApZ2Na2_Ts4_Tiles-.
	.4byte 5876 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na2_Ts4_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Na2_Ts5:
	.4byte gApZ2Na2_Ts5_Tiles-.
	.4byte 5040 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na2_Ts5_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Na2_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1264*PX
	.4byte DIR_RIGHT

gApZ2Na2_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na2_Script
gApZ2Na2_Script:
	spawn 0, gApZ2Na2_Zero
	reset_camera gApZ2Na2_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_ICE_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na2_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1264*PX
	.4byte DIR_RIGHT

gApZ2Na2_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na2_AgainScript
gApZ2Na2_AgainScript:
	spawn 0, gApZ2Na2_AgainZero
	reset_camera gApZ2Na2_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_ICE_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na2_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5392*PX, 576*PX
	.4byte DIR_RIGHT

gApZ2Na2_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 592*PX

.global gApZ2Na2_CheckpointScript
gApZ2Na2_CheckpointScript:
	spawn 0, gApZ2Na2_CheckpointZero
	reset_camera gApZ2Na2_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na2_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5392*PX, 576*PX
	.4byte DIR_RIGHT

gApZ2Na2_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 592*PX

.global gApZ2Na2_BossRestartScript
gApZ2Na2_BossRestartScript:
	spawn 0, gApZ2Na2_BossRestartZero
	reset_camera gApZ2Na2_BossRestartCamera
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
.global gApZ2Na2_ResultScript
gApZ2Na2_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Na2_Boss:
	.byte ENTITY_BOSS, BOSS_Z2_LEVIATHAN, 0, 0
	.4byte 5840*PX, 496*PX
	.4byte DIR_LEFT

gApZ2Na2_BossCamera: @ Zero 2's, 0x0832e82c
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 5520*PX, 6128*PX, 320*PX, 592*PX

gApZ2Na2_ClearCamera: @ Zero 2's, 0x0832e858
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 5648*PX, 5888*PX, 320*PX, 592*PX

gApZ2Na2_ClearZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5696*PX, 576*PX
	.4byte DIR_RIGHT

gApZ2Na2_BeatenLeviathan:
	.byte ENTITY_SOLID, SOLID_Z2_BEATEN_FEFNIR, 37, 1
	.4byte 5840*PX, 544*PX
	.4byte DIR_LEFT

@ Zero 2's script 3
.global gApZ2Na2_BossScript
gApZ2Na2_BossScript:
	spawn 1, gApZ2Na2_Boss
	reset_camera gApZ2Na2_BossCamera
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	walkto 5728*PX
	play_bgm BGM_X
	lock
	cutscene_start CS_UNK_48
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 5792*PX
	wait 90
	message 1, 0, 0x1426
	wait_msgbox_end
	wait 60
	cutscene_end
	stop_bgm
	entityflag 1, 0, TRUE
	wait 220
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 100
	warning_indicator
	reset_camera gApZ2Na2_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 4
.global gApZ2Na2_BossReturnScript
gApZ2Na2_BossReturnScript:
	spawn 1, gApZ2Na2_Boss
	reset_camera gApZ2Na2_BossCamera
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	walkto 5728*PX
	play_bgm BGM_X
	lock
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 5792*PX
	wait 30
	stop_bgm
	entityflag 1, 0, TRUE
	wait 220
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 100
	warning_indicator
	reset_camera gApZ2Na2_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 5
.global gApZ2Na2_ClearScript
gApZ2Na2_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	time 0
	destroy 0
	lockmenu
	stop_camera
	backdrop_color 0xFFFF
	start_transition 5
	wait 90
	load_graphic_primitive
	spawn 0, gApZ2Na2_ClearZero
	spawn 3, gApZ2Na2_BeatenLeviathan
	reset_camera gApZ2Na2_ClearCamera
	start_transition 1
	wait_transition_end
	play_bgm BGM_Z2_GUARDIAN_RETREAT
	entityflag 3, 0, TRUE
	wait 30
	message 1, 0, 0x1427
	wait_msgbox_end
	wait 30
	entityflag 3, 1, TRUE
	wait 120
	message 1, 0, 0x1428
	wait_msgbox_end
	wait 60
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	stop_bgm
	wait 60
	start_transition 6
	wait_transition_end
	wait 30
	destroy 3
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

.global gApZ2Na2_PlttAnim126
gApZ2Na2_PlttAnim126: @ Zero 2's palette animation 126
	.byte 4, 47, 47, 0
	.2byte 0x5AC0
	.2byte 0x5B20
	.2byte 0x5B80
	.2byte 0x5BE0
	.balign 4, 0
.global gApZ2Na2_PlttAnimScript126
gApZ2Na2_PlttAnimScript126:
	.4byte gApZ2Na2_PlttAnimScript126_0
gApZ2Na2_PlttAnimScript126_0:
	.byte 0, 40
	.byte 1, 6
	.byte 2, 3
	.byte 3, 1
	.byte 2, 3
	.byte 1, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na2_PlttAnim127
gApZ2Na2_PlttAnim127: @ Zero 2's palette animation 127
	.byte 4, 49, 75, 0
	.2byte 0x6780, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x5280, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7FA0
	.2byte 0x6340, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4A40, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B40
	.2byte 0x4E80, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4200, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x72E0
	.2byte 0x39C0, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x39C0, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B00
	.balign 4, 0
.global gApZ2Na2_PlttAnimScript127
gApZ2Na2_PlttAnimScript127:
	.4byte gApZ2Na2_PlttAnimScript127_0
gApZ2Na2_PlttAnimScript127_0:
	.byte 0, 12
	.byte 1, 12
	.byte 2, 12
	.byte 3, 12
	.byte 2, 12
	.byte 1, 12
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na2_PlttAnim128
gApZ2Na2_PlttAnim128: @ Zero 2's palette animation 128
	.byte 4, 97, 102, 0
	.2byte 0x1C1F, 0x0220, 0x7E80, 0x6A20, 0x5DE0, 0x55A0
	.2byte 0x1C18, 0x2300, 0x55A0, 0x7E80, 0x6A20, 0x5DE0
	.2byte 0x1810, 0x43E0, 0x5DE0, 0x55A0, 0x7E80, 0x6A20
	.2byte 0x1C18, 0x2300, 0x6A20, 0x5DE0, 0x55A0, 0x7E80
	.balign 4, 0
.global gApZ2Na2_PlttAnimScript128
gApZ2Na2_PlttAnimScript128:
	.4byte gApZ2Na2_PlttAnimScript128_0
gApZ2Na2_PlttAnimScript128_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na2_PlttAnim140
gApZ2Na2_PlttAnim140: @ Zero 2's palette animation 140
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x3CC0, 0x30E4, 0x4D00, 0x6160, 0x381A, 0x61E0, 0x4989, 0x6660, 0x11D9, 0x5A2E, 0x7347, 0x66F6, 0x5F3F, 0x7FF6, 0x7FFF
	.2byte 0x0000, 0x51EA, 0x49ED, 0x5E0A, 0x6E2A, 0x515C, 0x6E8A, 0x5A50, 0x6EEA, 0x369B, 0x66B4, 0x778F, 0x6F59, 0x6B7F, 0x7FF9, 0x7FFF
	.2byte 0x0000, 0x6AF5, 0x66F6, 0x6F15, 0x7715, 0x6ABD, 0x7755, 0x6F38, 0x7775, 0x5B5D, 0x735A, 0x7BD7, 0x77BC, 0x77BF, 0x7FFC, 0x7FFF
	.2byte 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Na2_PlttAnimScript140
gApZ2Na2_PlttAnimScript140:
	.4byte gApZ2Na2_PlttAnimScript140_0
gApZ2Na2_PlttAnimScript140_0:
	.byte 3, 60
	.byte 2, 8
	.byte 1, 8
	.byte 0, 60
	.byte 0, 255
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Na2_Metatiles
gApZ2Na2_Metatiles:
	.incbin "data/ap/z2_na2/metatile.bin"
	.balign 4, 0

.global gApZ2Na2_Attrs
gApZ2Na2_Attrs:
	.incbin "data/ap/z2_na2/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Na2_Chunks
gApZ2Na2_Chunks:
	.incbin "data/ap/z2_na2/screen.bin"
	.balign 4, 0

.global gApZ2Na2_WaterMap
gApZ2Na2_WaterMap:
	.incbin "data/ap/z2_na2/water_map.bin"

gApZ2Na2_Ts0_Tiles:
	.incbin "data/ap/z2_na2/tileset0.4bpp"
	.balign 4, 0
gApZ2Na2_Ts0_Pal:
	.incbin "data/ap/z2_na2/tileset0.gbapal"
	.balign 4, 0

gApZ2Na2_Ts1_Tiles:
	.incbin "data/ap/z2_na2/tileset1.4bpp"
	.balign 4, 0
gApZ2Na2_Ts1_Pal:
	.incbin "data/ap/z2_na2/tileset1.gbapal"
	.balign 4, 0

gApZ2Na2_Ts2_Tiles:
	.incbin "data/ap/z2_na2/tileset2.4bpp.lz"
	.balign 4, 0
gApZ2Na2_Ts2_Pal:
	.incbin "data/ap/z2_na2/tileset2.gbapal"
	.balign 4, 0

gApZ2Na2_Ts3_Tiles:
	.incbin "data/ap/z2_na2/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Na2_Ts3_Pal:
	.incbin "data/ap/z2_na2/tileset3.gbapal"
	.balign 4, 0

gApZ2Na2_Ts4_Tiles:
	.incbin "data/ap/z2_na2/tileset4.4bpp.lz"
	.balign 4, 0
gApZ2Na2_Ts4_Pal:
	.incbin "data/ap/z2_na2/tileset4.gbapal"
	.balign 4, 0

gApZ2Na2_Ts5_Tiles:
	.incbin "data/ap/z2_na2/tileset5.4bpp.lz"
	.balign 4, 0
gApZ2Na2_Ts5_Pal:
	.incbin "data/ap/z2_na2/tileset5.gbapal"
	.balign 4, 0
