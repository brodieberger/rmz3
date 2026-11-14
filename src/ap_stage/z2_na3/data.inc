@ Zero 2's NA-3 AKA Temple of Wind

.balign 4

.global gApZ2Na3_Terrain
gApZ2Na3_Terrain:
	.4byte gApZ2Na3_Metatiles-.
	.4byte gApZ2Na3_Attrs-(.-4)
	.4byte gApZ2Na3_Chunks-(.-8)

.global gApZ2Na3_Tilesets
gApZ2Na3_Tilesets: @ ColorGraphic[4]

gApZ2Na3_Ts0:
	.4byte gApZ2Na3_Ts0_Tiles-.
	.4byte 7616 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Ts0_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na3_Ts1:
	.4byte gApZ2Na3_Ts1_Tiles-.
	.4byte 4800 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Ts1_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na3_Ts2:
	.4byte gApZ2Na3_Ts2_Tiles-.
	.4byte 7368 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na3_Ts2_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Na3_Ts3:
	.4byte gApZ2Na3_Ts3_Tiles-.
	.4byte 6100 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na3_Ts3_Pal-.
		.2byte 192
		.byte 0, 9

.global gApZ2Na3_TileAnim
gApZ2Na3_TileAnim: @ ColorGraphic[9]

gApZ2Na3_Anim0:
	.4byte gApZ2Na3_Anim0_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim0_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim1:
	.4byte gApZ2Na3_Anim1_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim1_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim2:
	.4byte gApZ2Na3_Anim2_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim2_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim3:
	.4byte gApZ2Na3_Anim3_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim3_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim4:
	.4byte gApZ2Na3_Anim4_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim4_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim5:
	.4byte gApZ2Na3_Anim5_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim5_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim6:
	.4byte gApZ2Na3_Anim6_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim6_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim7:
	.4byte gApZ2Na3_Anim7_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim7_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Anim8:
	.4byte gApZ2Na3_Anim8_Tiles-.
	.4byte 640 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na3_Anim8_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Na3_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1888*PX
	.4byte DIR_RIGHT

gApZ2Na3_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na3_Script
gApZ2Na3_Script:
	spawn 0, gApZ2Na3_Zero
	reset_camera gApZ2Na3_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_WIND_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na3_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1888*PX
	.4byte DIR_RIGHT

gApZ2Na3_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na3_AgainScript
gApZ2Na3_AgainScript:
	spawn 0, gApZ2Na3_AgainZero
	reset_camera gApZ2Na3_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_WIND_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na3_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 2272*PX, 400*PX
	.4byte DIR_RIGHT

gApZ2Na3_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 432*PX

.global gApZ2Na3_CheckpointScript
gApZ2Na3_CheckpointScript:
	spawn 0, gApZ2Na3_CheckpointZero
	reset_camera gApZ2Na3_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na3_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 2272*PX, 400*PX
	.4byte DIR_RIGHT

gApZ2Na3_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, 432*PX

.global gApZ2Na3_BossRestartScript
gApZ2Na3_BossRestartScript:
	spawn 0, gApZ2Na3_BossRestartZero
	reset_camera gApZ2Na3_BossRestartCamera
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
.global gApZ2Na3_ResultScript
gApZ2Na3_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Na3_Boss:
	.byte ENTITY_BOSS, BOSS_Z2_RAPTOR, 0, 0
	.4byte 2640*PX, 240*PX
	.4byte DIR_LEFT

gApZ2Na3_BossCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 2608*PX, 3040*PX, 0*PX, 432*PX

gApZ2Na3_ClearCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 2704*PX, 2944*PX, 0*PX, 432*PX

gApZ2Na3_Harpuia:
	.byte ENTITY_SOLID, SOLID_Z2_WIND_HARPUIA, 0, 0
	.4byte 2896*PX, 400*PX
	.4byte DIR_RIGHT

gApZ2Na3_Elpizo:
	.byte ENTITY_SOLID, SOLID_Z2_ELPIZO, 0, 0
	.4byte 2944*PX, 400*PX
	.4byte DIR_LEFT

gApZ2Na3_DarkElf:
	.byte ENTITY_SOLID, SOLID_Z2_DARK_ELF, 0, 1
	.4byte 2960*PX, 400*PX
	.4byte DIR_LEFT

gApZ2Na3_Bolt:
	.byte ENTITY_SOLID, SOLID_Z2_DARK_BOLT, 0, 0
	.4byte 2960*PX, 400*PX
	.4byte DIR_LEFT

gApZ2Na3_ElfLeft:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELVES, 0, 0
	.4byte 2960*PX, 352*PX
	.4byte DIR_LEFT

gApZ2Na3_ElfRight:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELVES, 0, 1
	.4byte 2960*PX, 352*PX
	.4byte DIR_LEFT

gApZ2Na3_ClearZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 2768*PX, 400*PX
	.4byte DIR_RIGHT

gApZ2Na3_BeatenHarpuia:
	.byte ENTITY_SOLID, SOLID_Z2_BEATEN_FEFNIR, 37, 2
	.4byte 2880*PX, 400*PX
	.4byte DIR_LEFT

@ Zero 2's script 3
.global gApZ2Na3_BossScript
gApZ2Na3_BossScript:
	spawn 3, gApZ2Na3_Harpuia
	spawn 4, gApZ2Na3_Elpizo
	spawn 5, gApZ2Na3_DarkElf
	cmd0f 5, 4, 0
	spawn 7, gApZ2Na3_ElfLeft
	spawn 8, gApZ2Na3_ElfRight
	cmd0f 7, 4, 0
	cmd0f 8, 4, 0
	forcekeyinput DPAD_RIGHT
	pause
	wait 75
	forcekeyinput 0x2010
	wait 60
	walkto 2768*PX
	emotion_bubble 0, 16, -40, 0
	stop_bgm
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 2880*PX
	wait 60
	play_bgm BGM_Z2_ELPIZO
	wait 30
	cutscene_start CS_UNK_48
	message 1, 0, 0x1454
	wait_msgbox_end
	wait 15
	blackout_screen
	wait_transition_end
	stop_camera
	normal_screen
	cmd06 134, 0, 0
	wait_transition_end
	wait 60
	message 1, 0, 0x1455
	wait_msgbox_end
	wait 15
	blackout_screen
	wait_transition_end
	cmd06 0, 1, 0
	resume_camera
	change_camera_mode 1
	normal_screen
	wait_transition_end
	wait 60
	entityflag 4, 0, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x1456
	wait_msgbox_end
	wait 15
	walkto 2800*PX
	wait 45
	message 1, 0, 0x1457
	wait_msgbox_end
	wait 15
	entityflag 3, 0, TRUE
	wait 30
	message 1, 0, 0x1458
	wait_msgbox_end
	wait 15
	emotion_bubble 4, -12, -44, 0
	wait 60
	message 1, 0, 0x1459
	wait_msgbox_end
	wait 15
	entityflag 4, 1, TRUE
	wait 60
	start_transition 5
	play_se SE_Z2_DARK_BOLT
	spawn 6, gApZ2Na3_Bolt
	cmd0f 6, 3, 0
	entityflag 3, 1, TRUE
	wait 120
	entityflag 4, 2, TRUE
	wait 60
	message 1, 0, 0x145a
	wait_msgbox_end
	wait 15
	entityflag 4, 0, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x145b
	wait_msgbox_end
	wait 30
	cmd0f 7, 3, 0
	cmd0f 8, 3, 0
	wait 180
	message 1, 0, 0x145c
	wait_msgbox_end
	wait 15
	entityflag 4, 3, TRUE
	stop_bgm
	wait 120
	play_bgm BGM_Z2_BABY_ELVES
	entityflag 7, 0, TRUE
	entityflag 8, 0, TRUE
	wait 400
	set_chase_mode 2
	set_camera_target_x 2824*PX
	turn_left 3
	wait 15
	entityflag 3, 2, TRUE
	entityflag 3, 3, TRUE
	wait 30
	message 1, 0, 0x145d
	wait_msgbox_end
	cutscene_end
	destroy 8
	destroy 7
	destroy 6
	destroy 5
	destroy 4
	wait 2
	destroy 3
	spawn 1, gApZ2Na3_Boss
	wait 15
	stop_bgm
	entityflag 1, 0, TRUE
	time 0
	wait 16
	walkto 2768*PX
	turn_right 0
	waitabs 200
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 210
	warning_indicator
	reset_camera gApZ2Na3_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 4
.global gApZ2Na3_BossReturnScript
gApZ2Na3_BossReturnScript:
	spawn 1, gApZ2Na3_Boss
	forcekeyinput DPAD_RIGHT
	pause
	wait 75
	forcekeyinput 0x2010
	stop_bgm
	wait 60
	walkto 2768*PX
	play_bgm BGM_X
	lock
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 2824*PX
	wait 30
	stop_bgm
	entityflag 1, 0, TRUE
	wait 200
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 210
	warning_indicator
	reset_camera gApZ2Na3_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 5
.global gApZ2Na3_ClearScript
gApZ2Na3_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	force 8, 0, 0
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 0
	lockmenu
	stop_camera
	backdrop_color 0xFFFF
	start_transition 5
	wait 90
	load_graphic_primitive
	spawn 0, gApZ2Na3_ClearZero
	spawn 3, gApZ2Na3_BeatenHarpuia
	reset_camera gApZ2Na3_ClearCamera
	start_transition 1
	wait_transition_end
	play_bgm BGM_Z2_GUARDIAN_RETREAT
	wait 30
	spawn 7, gApZ2Na3_ElfLeft
	spawn 8, gApZ2Na3_ElfRight
	cmd0f 7, 3, 0
	cmd0f 8, 3, 0
	entityflag 7, 7, TRUE
	entityflag 8, 7, TRUE
	wait 360
	destroy 7
	destroy 8
	entityflag 3, 0, TRUE
	wait 120
	message 1, 0, 0x145e
	wait_msgbox_end
	wait 30
	entityflag 3, 1, TRUE
	wait 120
	message 1, 0, 0x145f
	wait_msgbox_end
	wait 60
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	stop_bgm
	wait 60
	blackout_screen
	wait_transition_end
	destroy 3
	stop_camera
	backdrop_color 0xFFFF
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Na3_PlttAnim126
gApZ2Na3_PlttAnim126: @ Zero 2's palette animation 126
	.byte 4, 47, 47, 0
	.2byte 0x5AC0
	.2byte 0x5B20
	.2byte 0x5B80
	.2byte 0x5BE0
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript126
gApZ2Na3_PlttAnimScript126:
	.4byte gApZ2Na3_PlttAnimScript126_0
gApZ2Na3_PlttAnimScript126_0:
	.byte 0, 40
	.byte 1, 6
	.byte 2, 3
	.byte 3, 1
	.byte 2, 3
	.byte 1, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na3_PlttAnim127
gApZ2Na3_PlttAnim127: @ Zero 2's palette animation 127
	.byte 4, 49, 75, 0
	.2byte 0x6780, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x5280, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7FA0
	.2byte 0x6340, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4A40, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B40
	.2byte 0x4E80, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4200, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x72E0
	.2byte 0x39C0, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x39C0, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B00
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript127
gApZ2Na3_PlttAnimScript127:
	.4byte gApZ2Na3_PlttAnimScript127_0
gApZ2Na3_PlttAnimScript127_0:
	.byte 0, 12
	.byte 1, 12
	.byte 2, 12
	.byte 3, 12
	.byte 2, 12
	.byte 1, 12
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na3_PlttAnim128
gApZ2Na3_PlttAnim128: @ Zero 2's palette animation 128
	.byte 4, 97, 102, 0
	.2byte 0x1C1F, 0x0220, 0x7E80, 0x6A20, 0x5DE0, 0x55A0
	.2byte 0x1C18, 0x2300, 0x55A0, 0x7E80, 0x6A20, 0x5DE0
	.2byte 0x1810, 0x43E0, 0x5DE0, 0x55A0, 0x7E80, 0x6A20
	.2byte 0x1C18, 0x2300, 0x6A20, 0x5DE0, 0x55A0, 0x7E80
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript128
gApZ2Na3_PlttAnimScript128:
	.4byte gApZ2Na3_PlttAnimScript128_0
gApZ2Na3_PlttAnimScript128_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na3_PlttAnim146
gApZ2Na3_PlttAnim146: @ Zero 2's palette animation 146
	.byte 8, 177, 191, 0
	.2byte 0x1060, 0x18C2, 0x2524, 0x3186, 0x39E8, 0x464A, 0x5AF0, 0x5F11, 0x6333, 0x6754, 0x6B76, 0x7397, 0x77B9, 0x7BDA, 0x7FFC
	.2byte 0x1060, 0x1CC2, 0x2524, 0x3186, 0x39E8, 0x464A, 0x52CE, 0x56F0, 0x5F11, 0x6332, 0x6754, 0x6B75, 0x6F96, 0x73B8, 0x7BD9
	.2byte 0x1080, 0x18C2, 0x2524, 0x2D86, 0x35C7, 0x3E29, 0x4EAD, 0x52CE, 0x56EF, 0x5B10, 0x5F31, 0x6353, 0x6774, 0x6F95, 0x73B7
	.2byte 0x1080, 0x18E2, 0x2123, 0x2965, 0x31A7, 0x3A08, 0x4A6B, 0x4A8C, 0x52AD, 0x56CE, 0x5AEF, 0x5F10, 0x6332, 0x6753, 0x6B74
	.2byte 0x10A1, 0x18E2, 0x2123, 0x2565, 0x2D86, 0x35C7, 0x424A, 0x466B, 0x4A8C, 0x4EAD, 0x52CE, 0x56EF, 0x5B10, 0x5F31, 0x6352
	.2byte 0x10A1, 0x18E2, 0x1D03, 0x2144, 0x2965, 0x2DA6, 0x3A08, 0x3E29, 0x424A, 0x4A8C, 0x4EAD, 0x52CE, 0x56EF, 0x5B10, 0x5F30
	.2byte 0x10C1, 0x14E2, 0x1D03, 0x2124, 0x2544, 0x2985, 0x31A7, 0x31C7, 0x35E8, 0x466B, 0x4A8C, 0x4EAD, 0x52EE, 0x56EE, 0x5B0F
	.2byte 0x10C1, 0x14E2, 0x1902, 0x1D23, 0x2124, 0x2144, 0x25A5, 0x2985, 0x2DC6, 0x35E8, 0x3E29, 0x424A, 0x4A8B, 0x4ECC, 0x56EE
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript146
gApZ2Na3_PlttAnimScript146:
	.4byte gApZ2Na3_PlttAnimScript146_0
gApZ2Na3_PlttAnimScript146_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 6
	.byte 3, 8
	.byte 4, 10
	.byte 5, 12
	.byte 6, 14
	.byte 7, 16
	.byte 6, 14
	.byte 5, 12
	.byte 4, 10
	.byte 3, 8
	.byte 2, 6
	.byte 1, 4
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na3_PlttAnim8
gApZ2Na3_PlttAnim8: @ Zero 2's palette animation 8
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x15A4, 0x1AA5, 0x436E, 0x63F6, 0x6AEC, 0x7FF0, 0x5F3F, 0x11D9, 0x1926, 0x4189, 0x5A2D, 0x5E70, 0x7B37, 0x7FFF, 0x391A
	.2byte 0x0000, 0x3A6D, 0x3F0D, 0x5794, 0x6FF9, 0x7352, 0x7FF5, 0x6B7F, 0x369B, 0x3E0F, 0x5651, 0x66D3, 0x6AF5, 0x7B7A, 0x7FFF, 0x521C
	.2byte 0x0000, 0x5F36, 0x5F96, 0x6BD9, 0x77FC, 0x7B99, 0x7FFA, 0x77BF, 0x5B5D, 0x5F17, 0x6B38, 0x7379, 0x737A, 0x7FBD, 0x7FFF, 0x6B1D
	.2byte 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript8
gApZ2Na3_PlttAnimScript8:
	.4byte gApZ2Na3_PlttAnimScript8_0
gApZ2Na3_PlttAnimScript8_0:
	.byte 3, 60
	.byte 2, 8
	.byte 1, 8
	.byte 0, 60
	.byte 0, 255
	.balign 4, 0

.global gApZ2Na3_PlttAnim75
gApZ2Na3_PlttAnim75: @ Zero 2's palette animation 75
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x30EE, 0x40F2, 0x4C97, 0x545B, 0x601F, 0x501A, 0x3C35, 0x2C4F, 0x1C4A, 0x498C, 0x5E73, 0x601F, 0x7E3F, 0x7F5F, 0x7FFF
	.2byte 0x0000, 0x34EE, 0x40F2, 0x5095, 0x5C59, 0x681D, 0x5818, 0x3C35, 0x304F, 0x1C4A, 0x498C, 0x5E93, 0x681D, 0x7E3F, 0x7F5F, 0x7FFF
	.2byte 0x0000, 0x38EE, 0x40F2, 0x5493, 0x6457, 0x741A, 0x6016, 0x3C35, 0x384E, 0x1C4A, 0x498C, 0x5EB3, 0x741A, 0x7E3F, 0x7F5F, 0x7FFF
	.2byte 0x0000, 0x38ED, 0x48EF, 0x5C92, 0x6C55, 0x7C18, 0x6814, 0x5431, 0x3C4D, 0x284A, 0x49EC, 0x5EB3, 0x7C18, 0x7E39, 0x7F5D, 0x7FFF
	.balign 4, 0
.global gApZ2Na3_PlttAnimScript75
gApZ2Na3_PlttAnimScript75:
	.4byte gApZ2Na3_PlttAnimScript75_0
gApZ2Na3_PlttAnimScript75_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 2, 8
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Na3_Metatiles
gApZ2Na3_Metatiles:
	.incbin "data/ap/z2_na3/metatile.bin"
	.balign 4, 0

.global gApZ2Na3_Attrs
gApZ2Na3_Attrs:
	.incbin "data/ap/z2_na3/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Na3_Chunks
gApZ2Na3_Chunks:
	.incbin "data/ap/z2_na3/screen.bin"
	.balign 4, 0

.global gApZ2MugshotElpizo
gApZ2MugshotElpizo:
	.incbin "data/ap/z2_na3/mugshot_elpizo.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotElpizo_Pal
gApZ2MugshotElpizo_Pal:
	.incbin "data/ap/z2_na3/mugshot_elpizo.gbapal"
	.balign 4, 0

.global gApZ2PictureDarkElf
gApZ2PictureDarkElf:
	.incbin "data/ap/z2_na3/picture_darkelf.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureDarkElf_Pal
gApZ2PictureDarkElf_Pal:
	.incbin "data/ap/z2_na3/picture_darkelf.gbapal"
	.balign 4, 0
.global gApZ2PictureDarkElf_Map
gApZ2PictureDarkElf_Map:
	.incbin "data/ap/z2_na3/picture_darkelf_map.bin"
	.balign 4, 0

.global gApZ2Na3_RaptorMap
gApZ2Na3_RaptorMap:
	.incbin "data/ap/z2_na3/raptor_map.bin"

.global gApZ2Na3_WingsMap
gApZ2Na3_WingsMap:
	.incbin "data/ap/z2_na3/wings_map.bin"

gApZ2Na3_Ts0_Tiles:
	.incbin "data/ap/z2_na3/tileset0.4bpp"
	.balign 4, 0
gApZ2Na3_Ts0_Pal:
	.incbin "data/ap/z2_na3/tileset0.gbapal"
	.balign 4, 0

gApZ2Na3_Ts1_Tiles:
	.incbin "data/ap/z2_na3/tileset1.4bpp"
	.balign 4, 0
gApZ2Na3_Ts1_Pal:
	.incbin "data/ap/z2_na3/tileset1.gbapal"
	.balign 4, 0

gApZ2Na3_Ts2_Tiles:
	.incbin "data/ap/z2_na3/tileset2.4bpp.lz"
	.balign 4, 0
gApZ2Na3_Ts2_Pal:
	.incbin "data/ap/z2_na3/tileset2.gbapal"
	.balign 4, 0

gApZ2Na3_Ts3_Tiles:
	.incbin "data/ap/z2_na3/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Na3_Ts3_Pal:
	.incbin "data/ap/z2_na3/tileset3.gbapal"
	.balign 4, 0

gApZ2Na3_Anim0_Tiles:
	.incbin "data/ap/z2_na3/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Na3_Anim0_Pal:
	.incbin "data/ap/z2_na3/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Na3_Anim1_Tiles:
	.incbin "data/ap/z2_na3/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Na3_Anim1_Pal:
	.incbin "data/ap/z2_na3/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Na3_Anim2_Tiles:
	.incbin "data/ap/z2_na3/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Na3_Anim2_Pal:
	.incbin "data/ap/z2_na3/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Na3_Anim3_Tiles:
	.incbin "data/ap/z2_na3/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Na3_Anim3_Pal:
	.incbin "data/ap/z2_na3/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Na3_Anim4_Tiles:
	.incbin "data/ap/z2_na3/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Na3_Anim4_Pal:
	.incbin "data/ap/z2_na3/tile_anim4.gbapal"
	.balign 4, 0

gApZ2Na3_Anim5_Tiles:
	.incbin "data/ap/z2_na3/tile_anim5.4bpp"
	.balign 4, 0
gApZ2Na3_Anim5_Pal:
	.incbin "data/ap/z2_na3/tile_anim5.gbapal"
	.balign 4, 0

gApZ2Na3_Anim6_Tiles:
	.incbin "data/ap/z2_na3/tile_anim6.4bpp"
	.balign 4, 0
gApZ2Na3_Anim6_Pal:
	.incbin "data/ap/z2_na3/tile_anim6.gbapal"
	.balign 4, 0

gApZ2Na3_Anim7_Tiles:
	.incbin "data/ap/z2_na3/tile_anim7.4bpp"
	.balign 4, 0
gApZ2Na3_Anim7_Pal:
	.incbin "data/ap/z2_na3/tile_anim7.gbapal"
	.balign 4, 0

gApZ2Na3_Anim8_Tiles:
	.incbin "data/ap/z2_na3/tile_anim8.4bpp"
	.balign 4, 0
gApZ2Na3_Anim8_Pal:
	.incbin "data/ap/z2_na3/tile_anim8.gbapal"
	.balign 4, 0
