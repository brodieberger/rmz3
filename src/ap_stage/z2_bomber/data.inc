@ Zero 2's BOMBER AKA Bombardment Aircraft

.balign 4

.global gApZ2Bomber_Terrain
gApZ2Bomber_Terrain:
	.4byte gApZ2Bomber_Metatiles-.
	.4byte gApZ2Bomber_Attrs-(.-4)
	.4byte gApZ2Bomber_Chunks-(.-8)

.global gApZ2Bomber_Tilesets
gApZ2Bomber_Tilesets: @ ColorGraphic[8]

gApZ2Bomber_Ts0:
	.4byte gApZ2Bomber_Ts0_Tiles-.
	.4byte 0 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts0_Pal-.
		.2byte 0
		.byte 0, 2

gApZ2Bomber_Ts1:
	.4byte gApZ2Bomber_Ts1_Tiles-.
	.4byte 12928 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts1_Pal-.
		.2byte 128
		.byte 0, 2

gApZ2Bomber_Ts2:
	.4byte gApZ2Bomber_Ts2_Tiles-.
	.4byte 16192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts2_Pal-.
		.2byte 96
		.byte 0, 9

gApZ2Bomber_Ts3:
	.4byte gApZ2Bomber_Ts3_Tiles-.
	.4byte 15744 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts3_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Bomber_Ts4:
	.4byte gApZ2Bomber_Ts4_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts4_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Bomber_Ts5:
	.4byte gApZ2Bomber_Ts5_Tiles-.
	.4byte 15744 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts5_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Bomber_Ts6:
	.4byte gApZ2Bomber_Ts6_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts6_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Bomber_Ts7:
	.4byte gApZ2Bomber_Ts7_Tiles-.
	.4byte 14144 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Ts7_Pal-.
		.2byte 160
		.byte 0, 9

.global gApZ2Bomber_TileAnim
gApZ2Bomber_TileAnim: @ ColorGraphic[9]

gApZ2Bomber_Anim0:
	.4byte gApZ2Bomber_Anim0_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim0_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim1:
	.4byte gApZ2Bomber_Anim1_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim1_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim2:
	.4byte gApZ2Bomber_Anim2_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim2_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim3:
	.4byte gApZ2Bomber_Anim3_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim3_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim4:
	.4byte gApZ2Bomber_Anim4_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim4_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim5:
	.4byte gApZ2Bomber_Anim5_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim5_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim6:
	.4byte gApZ2Bomber_Anim6_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim6_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim7:
	.4byte gApZ2Bomber_Anim7_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim7_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Anim8:
	.4byte gApZ2Bomber_Anim8_Tiles-.
	.4byte 640 | (448 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Bomber_Anim8_Pal-.
		.2byte 32
		.byte 0, 7

gApZ2Bomber_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 592*PX, 288*PX
	.4byte DIR_RIGHT

gApZ2Bomber_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Bomber_Script
gApZ2Bomber_Script:
	spawn 0, gApZ2Bomber_Zero
	reset_camera gApZ2Bomber_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x142a
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Bomber_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 592*PX, 288*PX
	.4byte DIR_RIGHT

gApZ2Bomber_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Bomber_AgainScript
gApZ2Bomber_AgainScript:
	spawn 0, gApZ2Bomber_AgainZero
	reset_camera gApZ2Bomber_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Bomber_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1568*PX
	.4byte DIR_RIGHT

gApZ2Bomber_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Bomber_CheckpointScript
gApZ2Bomber_CheckpointScript:
	spawn 0, gApZ2Bomber_CheckpointZero
	reset_camera gApZ2Bomber_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Bomber_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3712*PX, 4128*PX
	.4byte DIR_RIGHT

gApZ2Bomber_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Bomber_BossRestartScript
gApZ2Bomber_BossRestartScript:
	spawn 0, gApZ2Bomber_BossRestartZero
	reset_camera gApZ2Bomber_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Bomber_ResultScript
gApZ2Bomber_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Bomber_DropZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 592*PX, 288*PX
	.4byte DIR_RIGHT

gApZ2Bomber_CraftZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1568*PX
	.4byte DIR_RIGHT

gApZ2Bomber_MidBossZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3232*PX, 1568*PX
	.4byte DIR_RIGHT

gApZ2Bomber_DefenceZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 4680*PX, 2864*PX
	.4byte DIR_RIGHT

gApZ2Bomber_DescentZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 4680*PX, 2864*PX
	.4byte DIR_LEFT

gApZ2Bomber_FightZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3712*PX, 4128*PX
	.4byte DIR_RIGHT

gApZ2Bomber_MidBoss:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 1, 0
	.4byte 3120*PX, 1440*PX
	.4byte DIR_LEFT

gApZ2Bomber_Golem:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 1, 0
	.4byte 2952*PX, 1904*PX
	.4byte DIR_RIGHT

gApZ2Bomber_Boss:
	.byte ENTITY_BOSS, BOSS_Z2_GOLEM, 1, 0
	.4byte 3648*PX, 4000*PX
	.4byte DIR_LEFT

.global gApZ2Bomber_Doors0
gApZ2Bomber_Doors0:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0
	.4byte 4552*PX, 2832*PX
	.4byte DIR_LEFT

.global gApZ2Bomber_Doors1
gApZ2Bomber_Doors1:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0
	.4byte 4792*PX, 2832*PX
	.4byte DIR_LEFT

gApZ2Bomber_OpenDoors0:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0
	.4byte 4552*PX, 2832*PX
	.4byte DIR_LEFT

gApZ2Bomber_OpenDoors1:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0
	.4byte 4792*PX, 2832*PX
	.4byte DIR_LEFT

gApZ2Bomber_DefenceHopper:
	.byte ENTITY_ENEMY, ENEMY_Z2_HOPPER, 2, 0
	.4byte 5024*PX, 2848*PX
	.4byte DIR_RIGHT

gApZ2Bomber_DropCamera:
	.byte 1, 8, 0, 0
	.4byte 960*PX, 480*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, 15360*PX, 0*PX, 10240*PX

gApZ2Bomber_FreeCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, 15360*PX, 0*PX, 10240*PX

gApZ2Bomber_MidBossCamera:
	.byte 4, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 3120*PX, 3360*PX, 1440*PX, 1600*PX

gApZ2Bomber_BossCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 3648*PX, 4032*PX, 4000*PX, 4160*PX

@ Zero 2's script 0: Zero jumps off the transport
.global gApZ2Bomber_OpeningScript
gApZ2Bomber_OpeningScript:
	wait 30
	spawn 0, gApZ2Bomber_DropZero
	reset_camera gApZ2Bomber_DropCamera
	lock
	quake 0, 0, 1
	start_transition 1
	wait 2
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x34800
	adjust_camera 4, 0, 0x16000
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	wait 60
	cutscene_start CS_UNK_48
	message 1, 0, 0x142a
	wait_msgbox_end
	cutscene_end
	adjust_camera 0, 0, 6
	adjust_camera 2, 0, 0
	adjust_camera 1, 0, 2
	wait 120
	forcekeyinput 0x20
	wait 15
	forcekeyinput 0x4020
	wait 15
	forcekeyinput 0x6020
	wait 45
	stop_quake
	lock
	wait 100
	change_entity_val 0, 2, 1
	wait 140
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 7, 0, 0x3C00
	indicator 1, 2, 0
	wait_indicator_end
	release
	end

@ Zero 2's script 1: restart on the first craft, the camera scrolling
.global gApZ2Bomber_CraftScript
gApZ2Bomber_CraftScript:
	spawn 0, gApZ2Bomber_CraftZero
	reset_camera gApZ2Bomber_FreeCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 7, 0, 0x3C00
	indicator 1, 0, 0
	wait_indicator_end
	release
	end

@ Zero 2's script 2: the mid-boss on the hull
.global gApZ2Bomber_MidBossScript
gApZ2Bomber_MidBossScript:
	spawn 1, gApZ2Bomber_MidBoss
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 4
	adjust_camera 3, 0, 0xCA800
	adjust_camera 4, 0, 0x5F000
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 290
	force 1, 0, 0
	release
	reset_camera gApZ2Bomber_MidBossCamera
	resume 1
	end

@ Zero 2's script 3
.global gApZ2Bomber_MidBossClearScript
gApZ2Bomber_MidBossClearScript:
	forcekeyinput 0xFFFF
	wait 1
	lock
	cmd08_wait_set 1
	destroy 1
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0
	adjust_camera 14, 0, 0x280000
	release
	end

.global gApZ2Bomber_MidBossRestartScript
gApZ2Bomber_MidBossRestartScript:
	spawn 0, gApZ2Bomber_MidBossZero
	reset_camera gApZ2Bomber_FreeCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Zero 2's scripts 5 and 6: the Golem
.global gApZ2Bomber_GolemScript
gApZ2Bomber_GolemScript:
	spawn 1, gApZ2Bomber_Golem
	entityflag 1, 0, TRUE
	pause
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Bomber_GolemClearScript
gApZ2Bomber_GolemClearScript:
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

.global gApZ2Bomber_DefenceRestartScript
gApZ2Bomber_DefenceRestartScript:
	spawn 3, gApZ2Bomber_Doors0
	spawn 4, gApZ2Bomber_Doors1
	spawn 0, gApZ2Bomber_DefenceZero
	reset_camera gApZ2Bomber_FreeCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Zero 2's script 8: the defence starts
.global gApZ2Bomber_DefenceScript
gApZ2Bomber_DefenceScript:
	lock
	killtimeelf
	pause
	forcekeyinput 0x4010
	wait 28
	forcekeyinput 0x10
	wait 8
	forcekeyinput 0x4010
	wait 28
	force 9, 0, 0x141000
	lock
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 4
	adjust_camera 3, 0, 0x142800
	wait 60
	force 2, 0, 0
	wait 60
	message 1, 0, 0x142d
	wait_msgbox_end
	wait 60
	wait 120
	message 1, 0, 0x142e
	wait_msgbox_end
	wait 15
	wait 90
	message 1, 0, 0x142f
	wait_msgbox_end
	wait 60
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	emotion_bubble 0, 8, -40, 0
	spawn 6, gApZ2Bomber_DefenceHopper
	stop_bgm
	wait 60
	change_entity_val 0, 2, 0
	wait 15
	play_bgm BGM_Z2_RUIN_ESCAPE
	force 3, 0, 0
	release
	end

@ Zero 2's script 9: the defence held, the doors open
.global gApZ2Bomber_DefenceClearScript
gApZ2Bomber_DefenceClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	change_entity_val 6, 7, 0
	wait 60
	play_bgm BGM_Z2_BOMBER
	message 1, 0, 0x1432
	wait_msgbox_end
	wait 15
	force 9, 0, 0x141000
	change_entity_val 0, 2, 1
	wait 15
	wait 60
	message 1, 0, 0x1431
	wait_msgbox_end
	wait 15
	wait 90
	quake 0, 0, 5
	emotion_bubble 0, 16, -40, 0
	wait 120
	message 1, 0, 0x1433
	wait_msgbox_end
	wait 16
	destroy 1
	destroy 3
	destroy 4
	spawn 3, gApZ2Bomber_OpenDoors0
	spawn 4, gApZ2Bomber_OpenDoors1
	release
	end

.global gApZ2Bomber_DescentRestartScript
gApZ2Bomber_DescentRestartScript:
	spawn 3, gApZ2Bomber_OpenDoors0
	spawn 4, gApZ2Bomber_OpenDoors1
	quake 0, 0, 5
	spawn 0, gApZ2Bomber_DescentZero
	reset_camera gApZ2Bomber_FreeCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_BOMBER
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Zero 2's script 11: down the shaft
.global gApZ2Bomber_DescentScript
gApZ2Bomber_DescentScript:
	forcekeyinput 0xFFFF
	force 0, 0, 0
	change_entity_val 0, 2, 0
	wait 1
	lock
	message 1, 0, 0x1434
	wait_msgbox_end
	wait 15
	force 1, 0, 0
	forcekeyinput 0x2020
	wait 10
	forcekeyinput 0x20
	wait 10
	lock
	change_entity_val 0, 2, 1
	wait 30
	release
	end

.global gApZ2Bomber_FightRestartScript
gApZ2Bomber_FightRestartScript:
	message 6, 1, 0
	spawn 0, gApZ2Bomber_FightZero
	reset_camera gApZ2Bomber_FreeCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Zero 2's script 13: the boss
.global gApZ2Bomber_FightScript
gApZ2Bomber_FightScript:
	destroy 3
	destroy 4
	lock
	force 0, 0, 0
	force 8, 0, 0
	force 1, 0, 0
	spawn 1, gApZ2Bomber_Boss
	forcekeyinput 0x10
	wait 8
	lock
	force 0, 0, 0
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0xF5000
	wait 120
	message 5, 1, 0
	wait_msgbox_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	reset_camera gApZ2Bomber_BossCamera
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Bomber_BossScript
gApZ2Bomber_BossScript:
.global gApZ2Bomber_BossReturnScript
gApZ2Bomber_BossReturnScript:
	end

@ Zero 2's script 14
.global gApZ2Bomber_ClearScript
gApZ2Bomber_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	message 1, 0, 0x142c
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	stop_camera
	backdrop_color 0xFFFF
	start_transition 5
	wait 90
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Bomber_Texts
gApZ2Bomber_Texts:
	.2byte 0x142b
	.2byte 0x1435
	.2byte 0x1436
	.2byte 0x1430
	.balign 4, 0

.global gApZ2Bomber_PlttAnim17
gApZ2Bomber_PlttAnim17: @ Zero 2's palette animation 17
	.byte 8, 88, 88, 0
	.2byte 0x01BF
	.2byte 0x017B
	.2byte 0x0136
	.2byte 0x00F2
	.2byte 0x00AD
	.2byte 0x0069
	.2byte 0x0024
	.2byte 0x0000
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript17
gApZ2Bomber_PlttAnimScript17:
	.4byte gApZ2Bomber_PlttAnimScript17_0
gApZ2Bomber_PlttAnimScript17_0:
	.byte 0, 8
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 2
	.byte 5, 2
	.byte 6, 2
	.byte 7, 16
	.byte 6, 2
	.byte 5, 2
	.byte 4, 2
	.byte 3, 2
	.byte 2, 2
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim18
gApZ2Bomber_PlttAnim18: @ Zero 2's palette animation 18
	.byte 5, 43, 47, 0
	.2byte 0x3969, 0x41CD, 0x4E12, 0x5676, 0x62BA
	.2byte 0x3969, 0x41AC, 0x4DF0, 0x5254, 0x5E97
	.2byte 0x3949, 0x418B, 0x49CE, 0x4E11, 0x5654
	.2byte 0x3948, 0x416A, 0x45AC, 0x49CE, 0x5210
	.2byte 0x3928, 0x3D49, 0x418A, 0x45AB, 0x49CD
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript18
gApZ2Bomber_PlttAnimScript18:
	.4byte gApZ2Bomber_PlttAnimScript18_0
gApZ2Bomber_PlttAnimScript18_0:
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 2, 1
	.byte 3, 1
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 2, 1
	.byte 3, 1
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim19
gApZ2Bomber_PlttAnim19: @ Zero 2's palette animation 19
	.byte 5, 107, 111, 0
	.2byte 0x3969, 0x45CD, 0x4E32, 0x5A96, 0x62DA
	.2byte 0x3969, 0x41AC, 0x4A10, 0x5253, 0x5E97
	.2byte 0x3949, 0x418B, 0x49CE, 0x4E11, 0x5653
	.2byte 0x3948, 0x416A, 0x45AC, 0x49CE, 0x5210
	.2byte 0x3928, 0x3D49, 0x418A, 0x45AB, 0x49CD
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript19
gApZ2Bomber_PlttAnimScript19:
	.4byte gApZ2Bomber_PlttAnimScript19_0
gApZ2Bomber_PlttAnimScript19_0:
	.byte 2, 1
	.byte 3, 1
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 2, 1
	.byte 3, 1
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim20
gApZ2Bomber_PlttAnim20: @ Zero 2's palette animation 20
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
.global gApZ2Bomber_PlttAnimScript20
gApZ2Bomber_PlttAnimScript20:
	.4byte gApZ2Bomber_PlttAnimScript20_0
gApZ2Bomber_PlttAnimScript20_0:
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

.global gApZ2Bomber_PlttAnim21
gApZ2Bomber_PlttAnim21: @ Zero 2's palette animation 21
	.byte 4, 91, 94, 0
	.2byte 0x0260, 0x03E0, 0x0160, 0x00C0
	.2byte 0x00C0, 0x0260, 0x03E0, 0x0160
	.2byte 0x0160, 0x00C0, 0x0260, 0x03E0
	.2byte 0x03E0, 0x0160, 0x00C0, 0x0260
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript21
gApZ2Bomber_PlttAnimScript21:
	.4byte gApZ2Bomber_PlttAnimScript21_0
gApZ2Bomber_PlttAnimScript21_0:
	.byte 0, 3
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim22
gApZ2Bomber_PlttAnim22: @ Zero 2's palette animation 22
	.byte 2, 62, 63, 0
	.2byte 0x1E46, 0x1B66
	.2byte 0x1D66, 0x1E46
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript22
gApZ2Bomber_PlttAnimScript22:
	.4byte gApZ2Bomber_PlttAnimScript22_0
gApZ2Bomber_PlttAnimScript22_0:
	.byte 0, 2
	.byte 1, 2
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim23
gApZ2Bomber_PlttAnim23: @ Zero 2's palette animation 23
	.byte 8, 93, 94, 0
	.2byte 0x0060, 0x001F
	.2byte 0x0140, 0x001C
	.2byte 0x0220, 0x0018
	.2byte 0x0300, 0x0014
	.2byte 0x03E0, 0x0011
	.2byte 0x0300, 0x000D
	.2byte 0x0220, 0x0009
	.2byte 0x0140, 0x0006
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript23
gApZ2Bomber_PlttAnimScript23:
	.4byte gApZ2Bomber_PlttAnimScript23_0
gApZ2Bomber_PlttAnimScript23_0:
	.byte 0, 6
	.byte 1, 6
	.byte 2, 6
	.byte 3, 6
	.byte 4, 6
	.byte 5, 6
	.byte 6, 6
	.byte 7, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim24
gApZ2Bomber_PlttAnim24: @ Zero 2's palette animation 24
	.byte 8, 93, 94, 0
	.2byte 0x03E0, 0x001F
	.2byte 0x0380, 0x001C
	.2byte 0x0300, 0x0018
	.2byte 0x0280, 0x0014
	.2byte 0x0200, 0x0011
	.2byte 0x01A0, 0x000D
	.2byte 0x0120, 0x0009
	.2byte 0x00A0, 0x0008
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript24
gApZ2Bomber_PlttAnimScript24:
	.4byte gApZ2Bomber_PlttAnimScript24_0
gApZ2Bomber_PlttAnimScript24_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 9
	.byte 3, 9
	.byte 4, 10
	.byte 5, 10
	.byte 6, 12
	.byte 7, 12
	.byte 0, 255
	.balign 4, 0

.global gApZ2Bomber_PlttAnim25
gApZ2Bomber_PlttAnim25: @ Zero 2's palette animation 25
	.byte 8, 206, 207, 0
	.2byte 0x376C, 0x0048
	.2byte 0x2AA9, 0x00AF
	.2byte 0x1DC6, 0x0117
	.2byte 0x0CE3, 0x017F
	.2byte 0x0000, 0x0117
	.2byte 0x0CE3, 0x00AF
	.2byte 0x1DC6, 0x0048
	.2byte 0x2AA9, 0x0000
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript25
gApZ2Bomber_PlttAnimScript25:
	.4byte gApZ2Bomber_PlttAnimScript25_0
gApZ2Bomber_PlttAnimScript25_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 4, 8
	.byte 5, 8
	.byte 6, 8
	.byte 7, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim26
gApZ2Bomber_PlttAnim26: @ Zero 2's palette animation 26
	.byte 5, 187, 191, 0
	.2byte 0x3969, 0x45CE, 0x4E32, 0x5A76, 0x62DA
	.2byte 0x3969, 0x45AD, 0x4DF0, 0x5654, 0x5E97
	.2byte 0x3949, 0x418B, 0x49CE, 0x5211, 0x5654
	.2byte 0x3948, 0x416A, 0x45AC, 0x49CE, 0x5210
	.2byte 0x3928, 0x3D49, 0x418A, 0x45AB, 0x49CD
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript26
gApZ2Bomber_PlttAnimScript26:
	.4byte gApZ2Bomber_PlttAnimScript26_0
gApZ2Bomber_PlttAnimScript26_0:
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 2, 1
	.byte 3, 1
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 127
	.byte 0, 254
	.balign 4, 0

.global gApZ2Bomber_PlttAnim27
gApZ2Bomber_PlttAnim27: @ Zero 2's palette animation 27
	.byte 5, 219, 223, 0
	.2byte 0x3969, 0x41CD, 0x4E12, 0x5676, 0x62DA
	.2byte 0x3969, 0x41AC, 0x4DF0, 0x5254, 0x5E97
	.2byte 0x3949, 0x418B, 0x49CE, 0x4E11, 0x5653
	.2byte 0x3948, 0x416A, 0x45AC, 0x49CE, 0x5210
	.2byte 0x3928, 0x3D49, 0x418A, 0x45AB, 0x49CD
	.balign 4, 0
.global gApZ2Bomber_PlttAnimScript27
gApZ2Bomber_PlttAnimScript27:
	.4byte gApZ2Bomber_PlttAnimScript27_0
gApZ2Bomber_PlttAnimScript27_0:
	.byte 4, 127
	.byte 0, 1
	.byte 1, 1
	.byte 2, 1
	.byte 3, 1
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 127
	.byte 0, 1
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Bomber_Metatiles
gApZ2Bomber_Metatiles:
	.incbin "data/ap/z2_bomber/metatile.bin"
	.balign 4, 0

.global gApZ2Bomber_Attrs
gApZ2Bomber_Attrs:
	.incbin "data/ap/z2_bomber/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Bomber_Chunks
gApZ2Bomber_Chunks:
	.incbin "data/ap/z2_bomber/screen.bin"
	.balign 4, 0

.global gApZ2MugshotKuwagust
gApZ2MugshotKuwagust:
	.incbin "data/ap/z2_bomber/mugshot_kuwagust.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotKuwagust_Pal
gApZ2MugshotKuwagust_Pal:
	.incbin "data/ap/z2_bomber/mugshot_kuwagust.gbapal"
	.balign 4, 0

.global gApZ2Bomber_Layer3Map
gApZ2Bomber_Layer3Map:
	.incbin "data/ap/z2_bomber/layer3_map.bin"

.global gApZ2Bomber_Layer4Map
gApZ2Bomber_Layer4Map:
	.incbin "data/ap/z2_bomber/layer4_map.bin"

.global gApZ2Bomber_Layer5Map
gApZ2Bomber_Layer5Map:
	.incbin "data/ap/z2_bomber/layer5_map.bin"

.global gApZ2Bomber_Layer6Map
gApZ2Bomber_Layer6Map:
	.incbin "data/ap/z2_bomber/layer6_map.bin"

.global gApZ2Bomber_Layer11Map
gApZ2Bomber_Layer11Map:
	.incbin "data/ap/z2_bomber/layer11_map.bin"

gApZ2Bomber_Ts0_Tiles:
	.incbin "data/ap/z2_bomber/tileset0.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts0_Pal:
	.incbin "data/ap/z2_bomber/tileset0.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts1_Tiles:
	.incbin "data/ap/z2_bomber/tileset1.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts1_Pal:
	.incbin "data/ap/z2_bomber/tileset1.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts2_Tiles:
	.incbin "data/ap/z2_bomber/tileset2.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts2_Pal:
	.incbin "data/ap/z2_bomber/tileset2.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts3_Tiles:
	.incbin "data/ap/z2_bomber/tileset3.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts3_Pal:
	.incbin "data/ap/z2_bomber/tileset3.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts4_Tiles:
	.incbin "data/ap/z2_bomber/tileset4.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts4_Pal:
	.incbin "data/ap/z2_bomber/tileset4.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts5_Tiles:
	.incbin "data/ap/z2_bomber/tileset5.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts5_Pal:
	.incbin "data/ap/z2_bomber/tileset5.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts6_Tiles:
	.incbin "data/ap/z2_bomber/tileset6.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts6_Pal:
	.incbin "data/ap/z2_bomber/tileset6.gbapal"
	.balign 4, 0

gApZ2Bomber_Ts7_Tiles:
	.incbin "data/ap/z2_bomber/tileset7.4bpp"
	.balign 4, 0
gApZ2Bomber_Ts7_Pal:
	.incbin "data/ap/z2_bomber/tileset7.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim0_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim0_Pal:
	.incbin "data/ap/z2_bomber/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim1_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim1_Pal:
	.incbin "data/ap/z2_bomber/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim2_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim2_Pal:
	.incbin "data/ap/z2_bomber/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim3_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim3_Pal:
	.incbin "data/ap/z2_bomber/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim4_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim4_Pal:
	.incbin "data/ap/z2_bomber/tile_anim4.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim5_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim5.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim5_Pal:
	.incbin "data/ap/z2_bomber/tile_anim5.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim6_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim6.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim6_Pal:
	.incbin "data/ap/z2_bomber/tile_anim6.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim7_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim7.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim7_Pal:
	.incbin "data/ap/z2_bomber/tile_anim7.gbapal"
	.balign 4, 0

gApZ2Bomber_Anim8_Tiles:
	.incbin "data/ap/z2_bomber/tile_anim8.4bpp"
	.balign 4, 0
gApZ2Bomber_Anim8_Pal:
	.incbin "data/ap/z2_bomber/tile_anim8.gbapal"
	.balign 4, 0
