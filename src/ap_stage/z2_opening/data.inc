@ Zero 2's OPENING AKA Sand Wilderness

.balign 4

.global gApZ2Opening_Terrain
gApZ2Opening_Terrain:
	.4byte gApZ2Opening_Metatiles-.
	.4byte gApZ2Opening_Attrs-(.-4)
	.4byte gApZ2Opening_Chunks-(.-8)

.global gApZ2Opening_Tilesets
gApZ2Opening_Tilesets: @ ColorGraphic[6]

gApZ2Opening_Ts0:
	.4byte gApZ2Opening_Ts0_Tiles-.
	.4byte 11332 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Opening_Ts0_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Opening_Ts1:
	.4byte gApZ2Opening_Ts1_Tiles-.
	.4byte 14400 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Opening_Ts1_Pal-.
		.2byte 96
		.byte 0, 9

gApZ2Opening_Ts2:
	.4byte gApZ2Opening_Ts2_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Opening_Ts2_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Opening_Ts3:
	.4byte gApZ2Opening_Ts3_Tiles-.
	.4byte 13184 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Opening_Ts3_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Opening_Ts4:
	.4byte gApZ2Opening_Ts4_Tiles-.
	.4byte 13888 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Opening_Ts4_Pal-.
		.2byte 160
		.byte 0, 9

gApZ2Opening_Ts5:
	.4byte gApZ2Opening_Ts5_Tiles-.
	.4byte 14912 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Opening_Ts5_Pal-.
		.2byte 32
		.byte 0, 9

gApZ2Opening_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 1320*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Opening_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 1200*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Opening_Script
gApZ2Opening_Script:
	spawn 0, gApZ2Opening_Zero
	reset_camera gApZ2Opening_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_OPENING
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x1400
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Opening_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 1320*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Opening_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 1200*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Opening_AgainScript
gApZ2Opening_AgainScript:
	spawn 0, gApZ2Opening_AgainZero
	reset_camera gApZ2Opening_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_OPENING
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Opening_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 4192*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Opening_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 4080*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Opening_CheckpointScript
gApZ2Opening_CheckpointScript:
	spawn 0, gApZ2Opening_CheckpointZero
	reset_camera gApZ2Opening_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_OPENING
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Opening_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 7072*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Opening_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 6960*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Opening_BossRestartScript
gApZ2Opening_BossRestartScript:
	spawn 0, gApZ2Opening_BossRestartZero
	reset_camera gApZ2Opening_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_OPENING
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Opening_ResultScript
gApZ2Opening_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

@ Zero 2's script 2
.global gApZ2Opening_WaveScript
gApZ2Opening_WaveScript:
	lock
	force 0, 0, 0
	message 1, 0, 0x1401
	wait_msgbox_end
	force 1, 0, 0
	release
	end

gApZ2Opening_Boss:
	.byte ENTITY_BOSS, BOSS_Z2_DESERT, 0, 0
	.4byte 7088*PX, 320*PX
	.4byte DIR_LEFT

gApZ2Opening_IntroHunter6:
	.byte ENTITY_SOLID, SOLID_Z2_INTRO_HUNTER, 0, 0
	.4byte 7488*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Opening_IntroHunter4:
	.byte ENTITY_SOLID, SOLID_Z2_INTRO_HUNTER, 0, 0
	.4byte 7424*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Opening_IntroHunter5:
	.byte ENTITY_SOLID, SOLID_Z2_INTRO_HUNTER, 0, 0
	.4byte 7440*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Opening_IntroJaw:
	.byte ENTITY_SOLID, SOLID_Z2_INTRO_JAW, 0, 0
	.4byte 7328*PX, 320*PX
	.4byte DIR_LEFT

gApZ2Opening_BossCamera: @ Zero 2's, 0x08326fa4
	.byte 6, 4, 1, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x4000, 0x0, 0x0, 0x0
	.4byte 0*PX, 15360*PX, 0*PX, 10240*PX

@ Zero 2's script 9, minus rocks' load and end of Zero's jump
.global gApZ2Opening_BossScript
gApZ2Opening_BossScript:
	stop_bgm
	lock
	force 0, 0, 0
	cutscene_start CS_UNK_48
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 60
	spawn 6, gApZ2Opening_IntroHunter6
	spawn 4, gApZ2Opening_IntroHunter4
	spawn 5, gApZ2Opening_IntroHunter5
	play_bgm BGM_GUARDER_ROOM
	change_camera_mode 1
	set_chase_mode 4
	adjust_camera 3, 0, 7280*PX
	wait 90
	entityflag 5, 0, TRUE
	wait 60
	entityflag 4, 0, TRUE
	wait 90
	entityflag 6, 0, TRUE
	wait 30
	quake 0, 0, 8
	wait 30
	emotion_bubble 0, 16, -40, 1
	wait 60
	stop_quake
	change_entity_val 0, 2, 0
	wait 30
	spawn 3, gApZ2Opening_IntroJaw
	wait 15
	force 1, 0, 0
	forcekeyinput 0x2000
	wait 10
	forcekeyinput 0x2020
	wait 16
	forcekeyinput 0x2000
	wait 12
	forcekeyinput 0xFFFF
	wait 48
	lock
	destroy 4
	destroy 5
	destroy 6
	wait 60
	quake 0, 0, 2
	wait 60
	destroy 3
	cutscene_end
	spawn 1, gApZ2Opening_Boss
	change_camera_mode 1
	set_chase_mode 4
	adjust_camera 3, 0, 7120*PX
	wait 60
	gimmick 1, 1, 1
	play_se SE_Z2_DESERT_RUMBLE
	quake 0, 0, 4
	wait 120
	entityflag 1, 0, TRUE
	stop_quake
	wait 60
	stop_bgm
	wait 60
	reset_camera gApZ2Opening_BossCamera
	warning_indicator
	wait_indicator_end
	release
	play_bgm BGM_Z2_OPENING_BOSS
	resume 1
	end

@ Zero 2's script 16
.global gApZ2Opening_BossReturnScript
gApZ2Opening_BossReturnScript:
	stop_bgm
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 0
	wait 60
	quake 0, 0, 2
	wait 90
	spawn 1, gApZ2Opening_Boss
	change_camera_mode 1
	set_chase_mode 4
	adjust_camera 3, 0, 7120*PX
	wait 60
	gimmick 1, 1, 1
	play_se SE_Z2_DESERT_RUMBLE
	quake 0, 0, 4
	wait 120
	entityflag 1, 0, TRUE
	stop_quake
	wait 60
	stop_bgm
	wait 60
	reset_camera gApZ2Opening_BossCamera
	warning_indicator
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_OPENING_BOSS
	resume 1
	end

.global gApZ2Opening_ClearScript
gApZ2Opening_ClearScript:
	lockmenu
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	start_transition 5
	wait_transition_end
	force 8, 0, 0
	time 0
	wait 60
	play_bgm BGM_X
	wait 60
	message 1, 0, 0x1402
	wait_msgbox_end
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	stop_bgm
	wait 60
	start_transition 6
	wait_transition_end
	wait 30
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

gApZ2Opening_Golem0:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 0, 0
	.4byte 3312*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Opening_Golem0Camera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 3136*PX, 3376*PX, 320*PX, 800*PX

.global gApZ2Opening_MidBoss0Script
gApZ2Opening_MidBoss0Script:
	spawn 1, gApZ2Opening_Golem0
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	reset_camera gApZ2Opening_Golem0Camera
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 120
	force 1, 0, 0
	release
	resume 1
	end

.global gApZ2Opening_MidBoss0ClearScript
gApZ2Opening_MidBoss0ClearScript:
	lock
	force 0, 0, 0
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0
	change_camera_mode 6
	set_chase_mode 4
	start_transition 5
	wait_transition_end
	force 1, 0, 0
	release
	gameflag FLAG_2, FALSE
	end

gApZ2Opening_Golem1:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 0, 0
	.4byte 4256*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Opening_Golem1Camera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 4080*PX, 4320*PX, 320*PX, 800*PX

.global gApZ2Opening_MidBoss1Script
gApZ2Opening_MidBoss1Script:
	spawn 1, gApZ2Opening_Golem1
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	reset_camera gApZ2Opening_Golem1Camera
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 120
	force 1, 0, 0
	release
	resume 1
	end

.global gApZ2Opening_MidBoss1ClearScript
gApZ2Opening_MidBoss1ClearScript:
	lock
	force 0, 0, 0
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0
	change_camera_mode 6
	set_chase_mode 4
	start_transition 5
	wait_transition_end
	force 1, 0, 0
	release
	gameflag FLAG_2, FALSE
	end

.global gApZ2Opening_PlttAnim0
gApZ2Opening_PlttAnim0: @ Zero 2's palette animation 0
	.byte 16, 125, 125, 0
	.2byte 0x7BA4
	.2byte 0x7366
	.2byte 0x6B28
	.2byte 0x630A
	.2byte 0x5ACC
	.2byte 0x526E
	.2byte 0x4A2F
	.2byte 0x4211
	.2byte 0x39D2
	.2byte 0x3194
	.2byte 0x2D56
	.2byte 0x2538
	.2byte 0x1CF9
	.2byte 0x14BB
	.2byte 0x0C7D
	.2byte 0x043E
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript0
gApZ2Opening_PlttAnimScript0:
	.4byte gApZ2Opening_PlttAnimScript0_0
gApZ2Opening_PlttAnimScript0_0:
	.byte 0, 35
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 3
	.byte 8, 3
	.byte 9, 3
	.byte 10, 3
	.byte 11, 3
	.byte 12, 3
	.byte 13, 3
	.byte 14, 3
	.byte 15, 35
	.byte 14, 3
	.byte 13, 3
	.byte 12, 3
	.byte 11, 3
	.byte 10, 3
	.byte 9, 3
	.byte 8, 3
	.byte 7, 3
	.byte 6, 3
	.byte 5, 3
	.byte 4, 3
	.byte 3, 3
	.byte 2, 3
	.byte 1, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim1
gApZ2Opening_PlttAnim1: @ Zero 2's palette animation 1
	.byte 5, 174, 174, 0
	.2byte 0x7FC4
	.2byte 0x5EC3
	.2byte 0x4602
	.2byte 0x3140
	.2byte 0x1CC0
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript1
gApZ2Opening_PlttAnimScript1:
	.4byte gApZ2Opening_PlttAnimScript1_0
gApZ2Opening_PlttAnimScript1_0:
	.byte 0, 50
	.byte 1, 6
	.byte 2, 6
	.byte 3, 6
	.byte 4, 50
	.byte 3, 6
	.byte 2, 6
	.byte 1, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim2
gApZ2Opening_PlttAnim2: @ Zero 2's palette animation 2
	.byte 5, 150, 150, 0
	.2byte 0x001F
	.2byte 0x001B
	.2byte 0x0015
	.2byte 0x000F
	.2byte 0x000A
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript2
gApZ2Opening_PlttAnimScript2:
	.4byte gApZ2Opening_PlttAnimScript2_0
gApZ2Opening_PlttAnimScript2_0:
	.byte 0, 10
	.byte 1, 6
	.byte 2, 6
	.byte 3, 6
	.byte 4, 50
	.byte 3, 2
	.byte 2, 2
	.byte 1, 2
	.byte 0, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim3
gApZ2Opening_PlttAnim3: @ Zero 2's palette animation 3
	.byte 12, 167, 175, 0
	.2byte 0x0005, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0005, 0x0005, 0x0005, 0x0005
	.2byte 0x000C, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0005, 0x0005, 0x0005, 0x0005
	.2byte 0x0012, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0005, 0x0005, 0x000C, 0x0005
	.2byte 0x0019, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0005, 0x000C, 0x0012, 0x0005
	.2byte 0x001F, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0005, 0x0012, 0x0019, 0x000C
	.2byte 0x0019, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x000C, 0x0019, 0x001F, 0x0012
	.2byte 0x0012, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0012, 0x001F, 0x0019, 0x0019
	.2byte 0x000C, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0019, 0x0019, 0x0012, 0x001F
	.2byte 0x0005, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x001F, 0x0012, 0x000C, 0x0019
	.2byte 0x0005, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0019, 0x000C, 0x0005, 0x0012
	.2byte 0x0005, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x0012, 0x0005, 0x0005, 0x000C
	.2byte 0x0005, 0x3569, 0x316E, 0x41CB, 0x35F2, 0x000C, 0x0005, 0x0005, 0x0005
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript3
gApZ2Opening_PlttAnimScript3:
	.4byte gApZ2Opening_PlttAnimScript3_0
gApZ2Opening_PlttAnimScript3_0:
	.byte 0, 50
	.byte 1, 4
	.byte 2, 4
	.byte 3, 4
	.byte 4, 4
	.byte 5, 4
	.byte 6, 4
	.byte 7, 4
	.byte 8, 4
	.byte 9, 4
	.byte 10, 4
	.byte 11, 4
	.byte 0, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim28
gApZ2Opening_PlttAnim28: @ Zero 2's palette animation 28
	.byte 4, 97, 100, 0
	.2byte 0x2DF2, 0x3655, 0x3E97, 0x46D8
	.2byte 0x3655, 0x3E97, 0x46D8, 0x2DF2
	.2byte 0x3E97, 0x46D8, 0x2DF2, 0x3655
	.2byte 0x46D8, 0x2DF2, 0x3655, 0x3E97
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript28
gApZ2Opening_PlttAnimScript28:
	.4byte gApZ2Opening_PlttAnimScript28_0
gApZ2Opening_PlttAnimScript28_0:
	.byte 0, 9
	.byte 1, 9
	.byte 2, 9
	.byte 3, 9
	.byte 0, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim4
gApZ2Opening_PlttAnim4: @ Zero 2's palette animation 4
	.byte 6, 0, 15, 0
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x571F, 0x567A, 0x41F4, 0x2D4F, 0x18E7
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x2A1F, 0x29BB, 0x2176, 0x1511, 0x0CCB
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x011F, 0x00FC, 0x00D8, 0x00B4, 0x00B0
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x031F, 0x029F, 0x021F, 0x019F, 0x00FF
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502, 0x3584, 0x4605, 0x5A87, 0x630D, 0x6F72, 0x7FFF, 0x63FF, 0x43FF, 0x23FF, 0x03FF
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript4
gApZ2Opening_PlttAnimScript4:
	.4byte gApZ2Opening_PlttAnimScript4_0
gApZ2Opening_PlttAnimScript4_0:
	.byte 1, 4
	.byte 2, 4
	.byte 3, 2
	.byte 5, 2
	.byte 4, 2
	.byte 2, 254
	.balign 4, 0

.global gApZ2Opening_PlttAnim5
gApZ2Opening_PlttAnim5: @ Zero 2's palette animation 5
	.byte 1, 0, 15, 0
	.2byte 0x0000, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x6F72, 0x630D, 0x5689, 0x4A48, 0x3DE6, 0x3184, 0x7FFF, 0x7F5A, 0x6273, 0x458C, 0x2502
	.balign 4, 0
.global gApZ2Opening_PlttAnimScript5
gApZ2Opening_PlttAnimScript5:
	.4byte gApZ2Opening_PlttAnimScript5_0
gApZ2Opening_PlttAnimScript5_0:
	.byte 0, 1
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Opening_Metatiles
gApZ2Opening_Metatiles:
	.incbin "data/ap/z2_opening/metatile.bin"
	.balign 4, 0

.global gApZ2Opening_Attrs
gApZ2Opening_Attrs:
	.incbin "data/ap/z2_opening/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Opening_Chunks
gApZ2Opening_Chunks:
	.incbin "data/ap/z2_opening/screen.bin"
	.balign 4, 0

.global gApZ2Opening_SkyMap
gApZ2Opening_SkyMap:
	.incbin "data/ap/z2_opening/sky_map.bin"

.global gApZ2Opening_SandstormMap
gApZ2Opening_SandstormMap:
	.incbin "data/ap/z2_opening/sandstorm_map.bin"

gApZ2Opening_Ts0_Tiles:
	.incbin "data/ap/z2_opening/tileset0.4bpp.lz"
	.balign 4, 0
gApZ2Opening_Ts0_Pal:
	.incbin "data/ap/z2_opening/tileset0.gbapal"
	.balign 4, 0

gApZ2Opening_Ts1_Tiles:
	.incbin "data/ap/z2_opening/tileset1.4bpp"
	.balign 4, 0
gApZ2Opening_Ts1_Pal:
	.incbin "data/ap/z2_opening/tileset1.gbapal"
	.balign 4, 0

gApZ2Opening_Ts2_Tiles:
	.incbin "data/ap/z2_opening/tileset2.4bpp"
	.balign 4, 0
gApZ2Opening_Ts2_Pal:
	.incbin "data/ap/z2_opening/tileset2.gbapal"
	.balign 4, 0

gApZ2Opening_Ts3_Tiles:
	.incbin "data/ap/z2_opening/tileset3.4bpp"
	.balign 4, 0
gApZ2Opening_Ts3_Pal:
	.incbin "data/ap/z2_opening/tileset3.gbapal"
	.balign 4, 0

gApZ2Opening_Ts4_Tiles:
	.incbin "data/ap/z2_opening/tileset4.4bpp"
	.balign 4, 0
gApZ2Opening_Ts4_Pal:
	.incbin "data/ap/z2_opening/tileset4.gbapal"
	.balign 4, 0

gApZ2Opening_Ts5_Tiles:
	.incbin "data/ap/z2_opening/tileset5.4bpp"
	.balign 4, 0
gApZ2Opening_Ts5_Pal:
	.incbin "data/ap/z2_opening/tileset5.gbapal"
	.balign 4, 0
