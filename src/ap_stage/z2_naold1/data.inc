@ Zero 2's NA-OLD1 AKA Residential Area

.balign 4

.global gApZ2Naold1_Terrain
gApZ2Naold1_Terrain:
	.4byte gApZ2Naold1_Metatiles-.
	.4byte gApZ2Naold1_Attrs-(.-4)
	.4byte gApZ2Naold1_Chunks-(.-8)

.global gApZ2Naold1_Tilesets
gApZ2Naold1_Tilesets: @ ColorGraphic[4]

gApZ2Naold1_Ts0:
	.4byte gApZ2Naold1_Ts0_Tiles-.
	.4byte 8628 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Naold1_Ts0_Pal-.
		.2byte 128
		.byte 0, 2

gApZ2Naold1_Ts1:
	.4byte gApZ2Naold1_Ts1_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Naold1_Ts1_Pal-.
		.2byte 128
		.byte 0, 9

gApZ2Naold1_Ts2:
	.4byte gApZ2Naold1_Ts2_Tiles-.
	.4byte 14976 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Naold1_Ts2_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Naold1_Ts3:
	.4byte gApZ2Naold1_Ts3_Tiles-.
	.4byte 8012 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Naold1_Ts3_Pal-.
		.2byte 96
		.byte 0, 2

gApZ2Naold1_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Naold1_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Naold1_Script
gApZ2Naold1_Script:
	spawn 0, gApZ2Naold1_Zero
	reset_camera gApZ2Naold1_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_CIRCUIT_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Naold1_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Naold1_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Naold1_AgainScript
gApZ2Naold1_AgainScript:
	spawn 0, gApZ2Naold1_AgainZero
	reset_camera gApZ2Naold1_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_CIRCUIT_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Naold1_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5632*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Naold1_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Naold1_CheckpointScript
gApZ2Naold1_CheckpointScript:
	spawn 0, gApZ2Naold1_CheckpointZero
	reset_camera gApZ2Naold1_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Naold1_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5632*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Naold1_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Naold1_BossRestartScript
gApZ2Naold1_BossRestartScript:
	spawn 0, gApZ2Naold1_BossRestartZero
	reset_camera gApZ2Naold1_BossRestartCamera
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
.global gApZ2Naold1_ResultScript
gApZ2Naold1_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Naold1_Golem:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 1, 1
	.4byte 5928*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Naold1_Flame:
	.byte ENTITY_BOSS, BOSS_Z2_FLAME_GOLEM, 1, 1
	.4byte 6168*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Naold1_Frost:
	.byte ENTITY_BOSS, BOSS_Z2_FROST_GOLEM, 1, 1
	.4byte 6304*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Door0Shut:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0
	.4byte 5992*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Door0Open:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0
	.4byte 5992*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Door1Shut:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0
	.4byte 6232*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Door1Open:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0
	.4byte 6232*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_FrostCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 6304*PX, 6656*PX, 320*PX, 800*PX

@ Zero 2's scripts 3 and 4
.global gApZ2Naold1_MidBoss0Script
gApZ2Naold1_MidBoss0Script:
	stop_bgm
	spawn 1, gApZ2Naold1_Golem
	spawn 3, gApZ2Naold1_Door0Shut
	entityflag 1, 0, TRUE
	forcekeyinput DPAD_RIGHT
	pause
	wait 8
	lock
	warning_indicator
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Naold1_MidBoss0ClearScript
gApZ2Naold1_MidBoss0ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 3
	spawn 3, gApZ2Naold1_Door0Open
	start_transition 5
	wait_transition_end
	end

@ Zero 2's scripts 5 and 6
.global gApZ2Naold1_MidBoss1Script
gApZ2Naold1_MidBoss1Script:
	spawn 4, gApZ2Naold1_Door1Shut
	wait 1
	spawn 1, gApZ2Naold1_Flame
	entityflag 1, 0, TRUE
	forcekeyinput DPAD_RIGHT
	pause
	wait 8
	lock
	warning_indicator
	wait_indicator_end
	release
	resume 1
	end

.global gApZ2Naold1_MidBoss1ClearScript
gApZ2Naold1_MidBoss1ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 4
	spawn 4, gApZ2Naold1_Door1Open
	start_transition 5
	wait_transition_end
	end

@ Zero 2's scripts 7 and 8
.global gApZ2Naold1_MidBoss2Script
gApZ2Naold1_MidBoss2Script:
	spawn 1, gApZ2Naold1_Frost
	lock
	pause
	destroy 3
	forcekeyinput DPAD_RIGHT
	wait 75
	lock
	emotion_bubble 0, 16, -40, 0
	wait 5
	entityflag 1, 0, TRUE
	wait 90
	warning_indicator
	reset_camera gApZ2Naold1_FrostCamera
	wait_indicator_end
	release
	resume 1
	end

.global gApZ2Naold1_MidBoss2ClearScript
gApZ2Naold1_MidBoss2ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 4
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0
	change_camera_mode 6
	set_chase_mode 4
	start_transition 5
	wait 90
	start_transition 1
	wait_transition_end
	play_bgm BGM_Z2_CIRCUIT_SHRINE
	release
	end

.global gApZ2Naold1_BossScript
gApZ2Naold1_BossScript:
.global gApZ2Naold1_BossReturnScript
gApZ2Naold1_BossReturnScript:
	end

gApZ2Naold1_Captive:
	.byte ENTITY_SOLID, SOLID_Z2_BEATEN_FEFNIR, 42, 2
	.4byte 7040*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Harpuia:
	.byte ENTITY_SOLID, SOLID_Z2_CAST, 43, 0
	.4byte 7088*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Fefnir:
	.byte ENTITY_SOLID, SOLID_Z2_CAST, 43, 1
	.4byte 7168*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Naold1_Leviathan:
	.byte ENTITY_SOLID, SOLID_Z2_CAST, 43, 2
	.4byte 7136*PX, 448*PX
	.4byte DIR_LEFT

@ Zero 2's script 9
.global gApZ2Naold1_ClearScript
gApZ2Naold1_ClearScript:
	stop_bgm
	lock
	cutscene_start CS_UNK_48
	spawn 5, gApZ2Naold1_Captive
	wait 1
	spawn 6, gApZ2Naold1_Harpuia
	wait 1
	spawn 7, gApZ2Naold1_Fefnir
	wait 1
	spawn 8, gApZ2Naold1_Leviathan
	pause
	play_bgm BGM_X
	play_se SE_Z2_RUIN_ALARM
	emotion_bubble 0, 16, -40, 0
	wait 90
	entityflag 8, 0, TRUE
	wait 60
	message 1, 0, 0x1411
	wait_msgbox_end
	wait 15
	entityflag 7, 0, TRUE
	wait 45
	message 1, 0, 0x1412
	wait_msgbox_end
	wait 15
	entityflag 6, 0, TRUE
	wait 30
	message 1, 0, 0x1413
	wait_msgbox_end
	wait 15
	entityflag 7, 1, TRUE
	wait 30
	message 1, 0, 0x1414
	wait_msgbox_end
	wait 15
	entityflag 6, 1, TRUE
	wait 30
	message 1, 0, 0x1415
	wait_msgbox_end
	wait 15
	force 2, 0, 0
	wait 90
	message 1, 0, 0x1416
	wait_msgbox_end
	wait 15
	stop_bgm
	play_se SE_Z2_RUIN_CALL
	message 1, 0, 0x1417
	wait_msgbox_end
	wait 15
	force 3, 0, 0
	wait 60
	entityflag 8, 1, TRUE
	wait 60
	message 1, 0, 0x1418
	wait_msgbox_end
	emotion_bubble 0, 16, -40, 0
	play_bgm BGM_Z2_RUIN_ESCAPE
	wait 60
	message 1, 0, 0x1419
	wait_msgbox_end
	wait 15
	message 1, 0, 0x141a
	wait_msgbox_end
	wait 30
	force 4, 0, 0
	wait 10
	entityflag 5, 0, TRUE
	wait 20
	force 5, 0, 0
	wait 120
	message 1, 0, 0x141b
	wait_msgbox_end
	wait 60
	stop_bgm
	wait 30
	start_transition 2
	wait_transition_end
	destroy 5
	destroy 6
	destroy 7
	destroy 8
	wait 60
	stop_camera
	backdrop_color 0xFFFF
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Naold1_PlttAnim35
gApZ2Naold1_PlttAnim35: @ Zero 2's palette animation 35
	.byte 4, 47, 47, 0
	.2byte 0x001F
	.2byte 0x0019
	.2byte 0x0013
	.2byte 0x000C
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript35
gApZ2Naold1_PlttAnimScript35:
	.4byte gApZ2Naold1_PlttAnimScript35_0
gApZ2Naold1_PlttAnimScript35_0:
	.byte 0, 30
	.byte 1, 10
	.byte 2, 10
	.byte 3, 10
	.byte 2, 10
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim36
gApZ2Naold1_PlttAnim36: @ Zero 2's palette animation 36
	.byte 4, 79, 79, 0
	.2byte 0x43E0
	.2byte 0x2F20
	.2byte 0x1660
	.2byte 0x0140
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript36
gApZ2Naold1_PlttAnimScript36:
	.4byte gApZ2Naold1_PlttAnimScript36_0
gApZ2Naold1_PlttAnimScript36_0:
	.byte 0, 30
	.byte 1, 10
	.byte 2, 10
	.byte 3, 10
	.byte 2, 10
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim37
gApZ2Naold1_PlttAnim37: @ Zero 2's palette animation 37
	.byte 4, 165, 165, 0
	.2byte 0x001F
	.2byte 0x0019
	.2byte 0x0013
	.2byte 0x000C
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript37
gApZ2Naold1_PlttAnimScript37:
	.4byte gApZ2Naold1_PlttAnimScript37_0
gApZ2Naold1_PlttAnimScript37_0:
	.byte 0, 30
	.byte 1, 10
	.byte 2, 10
	.byte 3, 10
	.byte 2, 10
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim38
gApZ2Naold1_PlttAnim38: @ Zero 2's palette animation 38
	.byte 4, 219, 219, 0
	.2byte 0x011F
	.2byte 0x00D9
	.2byte 0x0073
	.2byte 0x000C
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript38
gApZ2Naold1_PlttAnimScript38:
	.4byte gApZ2Naold1_PlttAnimScript38_0
gApZ2Naold1_PlttAnimScript38_0:
	.byte 0, 30
	.byte 1, 10
	.byte 2, 10
	.byte 3, 10
	.byte 2, 10
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim39
gApZ2Naold1_PlttAnim39: @ Zero 2's palette animation 39
	.byte 4, 228, 228, 0
	.2byte 0x001F
	.2byte 0x0019
	.2byte 0x0013
	.2byte 0x000C
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript39
gApZ2Naold1_PlttAnimScript39:
	.4byte gApZ2Naold1_PlttAnimScript39_0
gApZ2Naold1_PlttAnimScript39_0:
	.byte 0, 30
	.byte 1, 10
	.byte 2, 10
	.byte 3, 10
	.byte 2, 10
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim40
gApZ2Naold1_PlttAnim40: @ Zero 2's palette animation 40
	.byte 31, 194, 206, 0
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript40
gApZ2Naold1_PlttAnimScript40:
	.4byte gApZ2Naold1_PlttAnimScript40_0
gApZ2Naold1_PlttAnimScript40_0:
	.byte 0, 3
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
	.byte 15, 15
	.byte 16, 3
	.byte 17, 3
	.byte 18, 3
	.byte 19, 3
	.byte 20, 3
	.byte 21, 3
	.byte 22, 3
	.byte 23, 3
	.byte 24, 3
	.byte 25, 3
	.byte 26, 3
	.byte 27, 3
	.byte 28, 3
	.byte 29, 3
	.byte 30, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Naold1_PlttAnim41
gApZ2Naold1_PlttAnim41: @ Zero 2's palette animation 41
	.byte 18, 41, 47, 0
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E, 0x0006
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017, 0x000E
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0017
	.2byte 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017, 0x001F
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E, 0x0017
	.2byte 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x000E
	.balign 4, 0
.global gApZ2Naold1_PlttAnimScript41
gApZ2Naold1_PlttAnimScript41:
	.4byte gApZ2Naold1_PlttAnimScript41_0
gApZ2Naold1_PlttAnimScript41_0:
	.byte 0, 3
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 3
	.byte 8, 3
	.byte 9, 15
	.byte 10, 3
	.byte 11, 3
	.byte 12, 3
	.byte 13, 3
	.byte 14, 3
	.byte 15, 3
	.byte 16, 3
	.byte 17, 3
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Naold1_Metatiles
gApZ2Naold1_Metatiles:
	.incbin "data/ap/z2_naold1/metatile.bin"
	.balign 4, 0

.global gApZ2Naold1_Attrs
gApZ2Naold1_Attrs:
	.incbin "data/ap/z2_naold1/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Naold1_Chunks
gApZ2Naold1_Chunks:
	.incbin "data/ap/z2_naold1/screen.bin"
	.balign 4, 0

gApZ2Naold1_Ts0_Tiles:
	.incbin "data/ap/z2_naold1/tileset0.4bpp.lz"
	.balign 4, 0
gApZ2Naold1_Ts0_Pal:
	.incbin "data/ap/z2_naold1/tileset0.gbapal"
	.balign 4, 0

gApZ2Naold1_Ts1_Tiles:
	.incbin "data/ap/z2_naold1/tileset1.4bpp"
	.balign 4, 0
gApZ2Naold1_Ts1_Pal:
	.incbin "data/ap/z2_naold1/tileset1.gbapal"
	.balign 4, 0

gApZ2Naold1_Ts2_Tiles:
	.incbin "data/ap/z2_naold1/tileset2.4bpp"
	.balign 4, 0
gApZ2Naold1_Ts2_Pal:
	.incbin "data/ap/z2_naold1/tileset2.gbapal"
	.balign 4, 0

gApZ2Naold1_Ts3_Tiles:
	.incbin "data/ap/z2_naold1/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Naold1_Ts3_Pal:
	.incbin "data/ap/z2_naold1/tileset3.gbapal"
	.balign 4, 0
