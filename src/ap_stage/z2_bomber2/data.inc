@ Zero 2's BOMBER2 AKA Crystal Cave

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
	.4byte 352*PX, 768*PX
	.4byte DIR_RIGHT

.global gApImp0_Script
gApImp0_Script:
	spawn 0, gApImp0_Zero
	reset_camera gApImp0_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm 176
	wait 90
	message 1, 0, 0x1400
	wait_msgbox_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApImp0_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 832*PX, 2496*PX
	.4byte DIR_RIGHT

.global gApImp0_CheckpointScript
gApImp0_CheckpointScript:
	spawn 0, gApImp0_CheckpointZero
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

gApImp0_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 7152*PX, 1568*PX
	.4byte DIR_RIGHT

.global gApImp0_BossRestartScript
gApImp0_BossRestartScript:
	spawn 0, gApImp0_BossRestartZero
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

@ Zero 2's script 14, command for command
.global gApImp0_WarningScript
gApImp0_WarningScript:
	lock
	force 0, 0, 0
	turn_right 0
	emotion_bubble 0, 16, -40, 0
	wait 60
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 3696*PX
	set_camera_target_y 1760*PX
	wait 90
	message 1, 0, 0x1401
	wait_msgbox_end
	change_camera_mode 3
	set_chase_mode 4
	wait 45
	clear_force_coord
	release
	end

gApImp0_Harpuia:
	.byte ENTITY_BOSS, BOSS_Z2_HARPUIA, 0, 0
	.4byte 7440*PX, 1440*PX
	.4byte DIR_LEFT

gApImp0_BossCamera: @ Zero 2's, 0x0832c4b0
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 7440*PX, 7680*PX, 0*PX, 1584*PX

.global gApImp0_BossScript
gApImp0_BossScript:
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	play_bgm BGM_X
	spawn 1, gApImp0_Harpuia
	change_camera_mode 1
	set_chase_mode 2
	adjust_camera 3, 0, 7560*PX
	wait 60
	clear_force_coord
	forcekeyinput DPAD_RIGHT
	wait 80
	lock
	message 1, 0, 0x1402
	wait_msgbox_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	reset_camera gApImp0_BossCamera
	wait_indicator_end
	release
	triumphant_message 0, 0x1403
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApImp0_ClearScript
gApImp0_ClearScript:
	message 6, 0, 0
	lockmenu
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	force 8, 0, 0
	time 0
	wait 120
	play_bgm BGM_X
	wait 60
	message 1, 0, 0x1404
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	wait 120
	message 1, 0, 0x1405
	wait_msgbox_end
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
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

gApImp0_Golem:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 1, 0
	.4byte 1128*PX, 2224*PX
	.4byte DIR_LEFT

.global gApImp0_MidBossScript
gApImp0_MidBossScript:
	spawn 1, gApImp0_Golem
	entityflag 1, 0, TRUE
	pause
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApImp0_MidBossClearScript
gApImp0_MidBossClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

.global gApImp0_PlttAnim133
gApImp0_PlttAnim133: @ Zero 2's palette animation 133
	.byte 8, 47, 47, 0
	.2byte 0x03E0
	.2byte 0x0360
	.2byte 0x02C0
	.2byte 0x0240
	.2byte 0x01A0
	.2byte 0x0120
	.2byte 0x0080
	.2byte 0x0000
	.balign 4, 0
.global gApImp0_PlttAnimScript133
gApImp0_PlttAnimScript133:
	.4byte gApImp0_PlttAnimScript133_0
gApImp0_PlttAnimScript133_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 4
	.byte 3, 4
	.byte 4, 4
	.byte 5, 4
	.byte 6, 4
	.byte 7, 4
	.byte 6, 4
	.byte 5, 4
	.byte 4, 4
	.byte 3, 4
	.byte 2, 4
	.byte 1, 4
	.byte 0, 254
	.balign 4, 0

.global gApImp0_PlttAnim134
gApImp0_PlttAnim134: @ Zero 2's palette animation 134
	.byte 5, 163, 173, 0
	.2byte 0x30A6, 0x34E8, 0x414B, 0x596D, 0x59F0, 0x6E33, 0x7697, 0x76F9, 0x7F3C, 0x7F9E, 0x7FFF
	.2byte 0x30A6, 0x34E8, 0x414B, 0x554C, 0x55CF, 0x6612, 0x6E55, 0x6EB7, 0x76F9, 0x773B, 0x779C
	.2byte 0x30A6, 0x34E8, 0x3D2A, 0x512B, 0x51AE, 0x5DD0, 0x6613, 0x6654, 0x6A96, 0x6AD8, 0x6B18
	.2byte 0x30A6, 0x34E8, 0x3D09, 0x492A, 0x496C, 0x558E, 0x59D0, 0x5A11, 0x5E33, 0x5E74, 0x5E95
	.2byte 0x30A6, 0x34C7, 0x3909, 0x4509, 0x454B, 0x4D6C, 0x518E, 0x51AF, 0x55D0, 0x55F1, 0x5631
	.balign 4, 0
.global gApImp0_PlttAnimScript134
gApImp0_PlttAnimScript134:
	.4byte gApImp0_PlttAnimScript134_0
gApImp0_PlttAnimScript134_0:
	.byte 0, 20
	.byte 1, 6
	.byte 2, 4
	.byte 3, 4
	.byte 4, 2
	.byte 3, 4
	.byte 2, 4
	.byte 1, 6
	.byte 0, 254
	.balign 4, 0

.global gApImp0_PlttAnim135
gApImp0_PlttAnim135: @ Zero 2's palette animation 135
	.byte 8, 162, 169, 0
	.2byte 0x0000, 0x0428, 0x0C50, 0x1098, 0x317F, 0x1098, 0x0C50, 0x0428
	.2byte 0x0428, 0x0C50, 0x1098, 0x317F, 0x1098, 0x0C50, 0x0428, 0x0000
	.2byte 0x0C50, 0x1098, 0x317F, 0x1098, 0x0C50, 0x0428, 0x0000, 0x0428
	.2byte 0x1098, 0x317F, 0x1098, 0x0C50, 0x0428, 0x0000, 0x0428, 0x0C50
	.2byte 0x317F, 0x1098, 0x0C50, 0x0428, 0x0000, 0x0428, 0x0C50, 0x1098
	.2byte 0x1098, 0x0C50, 0x0428, 0x0000, 0x0428, 0x0C50, 0x1098, 0x317F
	.2byte 0x0C50, 0x0428, 0x0000, 0x0428, 0x0C50, 0x1098, 0x317F, 0x1098
	.2byte 0x0428, 0x0000, 0x0428, 0x0C50, 0x1098, 0x317F, 0x1098, 0x0C50
	.balign 4, 0
.global gApImp0_PlttAnimScript135
gApImp0_PlttAnimScript135:
	.4byte gApImp0_PlttAnimScript135_0
gApImp0_PlttAnimScript135_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 4
	.byte 3, 4
	.byte 4, 4
	.byte 5, 4
	.byte 6, 4
	.byte 7, 4
	.byte 0, 254
	.balign 4, 0

.global gApImp0_PlttAnim138
gApImp0_PlttAnim138: @ Zero 2's palette animation 138
	.byte 8, 57, 63, 0
	.2byte 0x2D45, 0x3165, 0x3586, 0x39A6, 0x1082, 0x1082, 0x1082
	.2byte 0x2D45, 0x3186, 0x35C7, 0x39E9, 0x7FFF, 0x1082, 0x1082
	.2byte 0x2D45, 0x3186, 0x35A7, 0x39C7, 0x5AD6, 0x1082, 0x1082
	.2byte 0x2D45, 0x3165, 0x3586, 0x39A6, 0x35AC, 0x1082, 0x1082
	.2byte 0x2D45, 0x3186, 0x35A7, 0x39C8, 0x1082, 0x4318, 0x1082
	.2byte 0x2D45, 0x3186, 0x35A7, 0x39C8, 0x1082, 0x3231, 0x0211
	.2byte 0x2D45, 0x3166, 0x3586, 0x39A7, 0x1082, 0x2149, 0x058C
	.2byte 0x2D45, 0x3165, 0x3586, 0x39A6, 0x1082, 0x1082, 0x0907
	.balign 4, 0
.global gApImp0_PlttAnimScript138
gApImp0_PlttAnimScript138:
	.4byte gApImp0_PlttAnimScript138_0
gApImp0_PlttAnimScript138_0:
	.byte 0, 120
	.byte 1, 2
	.byte 2, 6
	.byte 3, 6
	.byte 0, 90
	.byte 4, 2
	.byte 5, 2
	.byte 6, 6
	.byte 7, 6
	.byte 0, 254
	.balign 4, 0

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
