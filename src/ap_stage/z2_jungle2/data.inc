@ Zero 2's JUNGLE2 AKA Forest of Notus

.balign 4

.global gApZ2Jungle2_Terrain
gApZ2Jungle2_Terrain:
	.4byte gApZ2Jungle2_Metatiles-.
	.4byte gApZ2Jungle2_Attrs-(.-4)
	.4byte gApZ2Jungle2_Chunks-(.-8)

.global gApZ2Jungle2_Tilesets
gApZ2Jungle2_Tilesets: @ ColorGraphic[5]

gApZ2Jungle2_Ts0:
	.4byte gApZ2Jungle2_Ts0_Tiles-.
	.4byte 13248 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Ts0_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Jungle2_Ts1:
	.4byte gApZ2Jungle2_Ts1_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Ts1_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Jungle2_Ts2:
	.4byte gApZ2Jungle2_Ts2_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Ts2_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Jungle2_Ts3:
	.4byte gApZ2Jungle2_Ts3_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Ts3_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Jungle2_Ts4:
	.4byte gApZ2Jungle2_Ts4_Tiles-.
	.4byte 8512 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Ts4_Pal-.
		.2byte 160
		.byte 0, 9

.global gApZ2Jungle2_TileAnim
gApZ2Jungle2_TileAnim: @ ColorGraphic[1]

gApZ2Jungle2_Anim0:
	.4byte gApZ2Jungle2_Anim0_Tiles-.
	.4byte 0 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Jungle2_Anim0_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Jungle2_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 768*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Jungle2_Script
gApZ2Jungle2_Script:
	spawn 0, gApZ2Jungle2_Zero
	reset_camera gApZ2Jungle2_Camera
	lock
	cutscene_start CS_UNK_48
	start_transition 1
	wait 1
	spawn 3, gApZ2Jungle2_OpeningElpizo
	spawn 4, gApZ2Jungle2_OpeningElfLeft
	spawn 5, gApZ2Jungle2_OpeningElfRight
	cmd0f 4, 3, 0
	cmd0f 5, 3, 0
	change_entity_val 0, 4, 0
	wait_transition_end
	play_bgm BGM_Z2_ELPIZO
	wait 30
	force 6, 0, 0
	wait 60
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 4
	adjust_camera 3, 0, 0x1A000
	wait 60
	entityflag 3, 0, TRUE
	wait 30
	message 1, 0, 0x143a
	wait_msgbox_end
	wait 15
	entityflag 3, 1, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x143b
	wait_msgbox_end
	wait 15
	entityflag 3, 1, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	entityflag 3, 2, TRUE
	wait 60
	stop_bgm
	wait 60
	play_bgm BGM_Z2_JUNGLE
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	message 1, 0, 0x1437
	wait_msgbox_end
	destroy 3
	destroy 4
	destroy 5
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Jungle2_OpeningElpizo:
	.byte ENTITY_SOLID, SOLID_Z2_FOREST_ELPIZO, 0, 0
	.4byte 480*PX, 768*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_OpeningElfLeft:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 0
	.4byte 480*PX, 768*PX
	.4byte DIR_LEFT

gApZ2Jungle2_OpeningElfRight:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 1
	.4byte 480*PX, 768*PX
	.4byte DIR_LEFT

gApZ2Jungle2_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 768*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Jungle2_AgainScript
gApZ2Jungle2_AgainScript:
	spawn 0, gApZ2Jungle2_AgainZero
	reset_camera gApZ2Jungle2_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_JUNGLE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Jungle2_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5152*PX, 608*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Jungle2_CheckpointScript
gApZ2Jungle2_CheckpointScript:
	spawn 0, gApZ2Jungle2_CheckpointZero
	reset_camera gApZ2Jungle2_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_JUNGLE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Jungle2_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 8032*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Jungle2_BossRestartScript
gApZ2Jungle2_BossRestartScript:
	spawn 0, gApZ2Jungle2_BossRestartZero
	reset_camera gApZ2Jungle2_BossRestartCamera
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
.global gApZ2Jungle2_ResultScript
gApZ2Jungle2_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Jungle2_Beast:
	.byte ENTITY_BOSS, BOSS_Z2_WALL, 0, 1
	.4byte 5040*PX, 320*PX
	.4byte DIR_LEFT

gApZ2Jungle2_BeastCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 4800*PX, 5040*PX, 320*PX, 480*PX

@ Zero 2's scripts 2 and 3
.global gApZ2Jungle2_MidBoss0Script
gApZ2Jungle2_MidBoss0Script:
	spawn 1, gApZ2Jungle2_Beast
	reset_camera gApZ2Jungle2_BeastCamera
	lock
	pause
	wait 30
	entityflag 1, 0, TRUE
	wait 180
	release
	resume 1
	end

.global gApZ2Jungle2_MidBoss0ClearScript
gApZ2Jungle2_MidBoss0ClearScript:
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	cmd08_wait_set 1
	destroy 1
	end

gApZ2Jungle2_Gate:
	.byte ENTITY_SOLID, SOLID_Z2_SCRIPT_DOOR, 0, 0
	.4byte 8400*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_Elpizo:
	.byte ENTITY_SOLID, SOLID_Z2_FOREST_ELPIZO, 0, 0
	.4byte 8352*PX, 448*PX
	.4byte DIR_RIGHT

gApZ2Jungle2_ElfLeft:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 0
	.4byte 8352*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_ElfRight:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 1
	.4byte 8352*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_Frog:
	.byte ENTITY_BOSS, BOSS_Z2_FROG, 0, 0
	.4byte 8352*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_DoorShut:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0
	.4byte 8392*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_DoorOpen:
	.byte ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0
	.4byte 8392*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_SealElpizo:
	.byte ENTITY_SOLID, SOLID_Z2_SEAL_ELPIZO, 0, 0
	.4byte 8592*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_X:
	.byte ENTITY_SOLID, SOLID_Z2_X_GLOW, 0, 1
	.4byte 8528*PX, 460*PX
	.4byte DIR_LEFT

gApZ2Jungle2_SealElfLeft:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 0
	.4byte 8528*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Jungle2_SealElfRight:
	.byte ENTITY_SOLID, SOLID_Z2_BABY_ELF, 0, 1
	.4byte 8528*PX, 448*PX
	.4byte DIR_LEFT

.global gApZ2Jungle2_BossScript
gApZ2Jungle2_BossScript:
.global gApZ2Jungle2_BossReturnScript
gApZ2Jungle2_BossReturnScript:
	end

@ Zero 2's script 6: Elpizo finds the key and goes through, the frog stops Zero
.global gApZ2Jungle2_FightScript
gApZ2Jungle2_FightScript:
	spawn 3, gApZ2Jungle2_Gate
	spawn 4, gApZ2Jungle2_Elpizo
	spawn 5, gApZ2Jungle2_ElfLeft
	spawn 6, gApZ2Jungle2_ElfRight
	cmd0f 5, 4, 0
	cmd0f 6, 4, 0
	entityflag 4, 0, TRUE
	stop_bgm
	lock
	cutscene_start CS_UNK_48
	killtimeelf
	pause
	emotion_bubble 0, 16, -40, 0
	wait 45
	play_bgm BGM_Z2_JUNGLE_SCENE
	wait 45
	entityflag 4, 1, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x143c
	wait_msgbox_end
	entityflag 3, 0, TRUE
	wait 30
	entityflag 4, 2, TRUE
	wait 60
	entityflag 3, 1, TRUE
	wait 44
	forcekeyinput DPAD_RIGHT
	wait 16
	destroy 4
	destroy 5
	destroy 6
	spawn 1, gApZ2Jungle2_Frog
	emotion_bubble 0, 16, -40, 0
	lock
	wait 90
	message 1, 0, 0x1438
	wait_msgbox_end
	destroy 3
	spawn 3, gApZ2Jungle2_DoorShut
	cutscene_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 7
.global gApZ2Jungle2_FightReturnScript
gApZ2Jungle2_FightReturnScript:
	spawn 3, gApZ2Jungle2_DoorShut
	lock
	pause
	forcekeyinput DPAD_RIGHT
	wait 16
	spawn 1, gApZ2Jungle2_Frog
	lock
	wait 90
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 8, its results moved after the clear scene
.global gApZ2Jungle2_ClearScript
gApZ2Jungle2_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	killtimeelf
	message 1, 0, 0x1439
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 3
	spawn 3, gApZ2Jungle2_DoorOpen
	load_graphic_primitive
	start_transition 1
	wait_transition_end
	release
	end

@ Zero 2's script 9: the seal broken, Elpizo gone, X
.global gApZ2Jungle2_SceneScript
gApZ2Jungle2_SceneScript:
	spawn 4, gApZ2Jungle2_SealElpizo
	spawn 5, gApZ2Jungle2_X
	spawn 6, gApZ2Jungle2_SealElfLeft
	spawn 7, gApZ2Jungle2_SealElfRight
	cmd0f 6, 5, 0
	cmd0f 7, 5, 0
	entityflag 6, 7, TRUE
	entityflag 7, 7, TRUE
	lock
	cutscene_start CS_UNK_48
	killtimeelf
	pause
	play_bgm BGM_Z2_SEAL
	emotion_bubble 0, 16, -40, 0
	wait 60
	entityflag 4, 0, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x143d
	wait_msgbox_end
	wait 16
	cmd0f 6, 4, 0
	cmd0f 7, 4, 0
	entityflag 6, 7, FALSE
	entityflag 7, 7, FALSE
	wait 30
	entityflag 4, 1, TRUE
	entityflag 6, 0, TRUE
	entityflag 7, 0, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	wait 15
	forcekeyinput DPAD_RIGHT
	wait 16
	lock
	entityflag 5, 0, TRUE
	wait 200
	message 1, 0, 0x143e
	wait_msgbox_end
	wait 15
	entityflag 5, 1, TRUE
	wait 180
	message 1, 0, 0x143f
	wait_msgbox_end
	wait 30
	message 1, 0, 0x1440
	wait_msgbox_end
	wait 90
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	stop_bgm
	wait 60
	start_transition 2
	wait_transition_end
	wait 30
	destroy 3
	destroy 4
	destroy 5
	destroy 6
	destroy 7
	backdrop_color 0xFFFF
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Jungle2_PlttAnim101
gApZ2Jungle2_PlttAnim101: @ Zero 2's palette animation 101
	.byte 7, 226, 232, 0
	.2byte 0x25C2, 0x2E05, 0x3647, 0x3E8A, 0x4B0F, 0x5796, 0x63FD
	.2byte 0x5796, 0x25C2, 0x2E05, 0x3647, 0x3E8A, 0x4B0F, 0x5796
	.2byte 0x4F53, 0x4B0F, 0x25C2, 0x3226, 0x3A69, 0x42CC, 0x4B0F
	.2byte 0x4710, 0x4B10, 0x3E8A, 0x25C2, 0x2E05, 0x3648, 0x3E8A
	.2byte 0x3EAC, 0x42CD, 0x46EE, 0x4B0F, 0x25C2, 0x2E05, 0x3647
	.2byte 0x3669, 0x3EAC, 0x4710, 0x4F53, 0x5796, 0x25C2, 0x2E05
	.2byte 0x2E05, 0x3A6A, 0x42CE, 0x4F32, 0x5796, 0x63FD, 0x25C2
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript101
gApZ2Jungle2_PlttAnimScript101:
	.4byte gApZ2Jungle2_PlttAnimScript101_0
gApZ2Jungle2_PlttAnimScript101_0:
	.byte 0, 5
	.byte 1, 4
	.byte 2, 4
	.byte 3, 5
	.byte 4, 5
	.byte 5, 5
	.byte 6, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim102
gApZ2Jungle2_PlttAnim102: @ Zero 2's palette animation 102
	.byte 4, 83, 86, 0
	.2byte 0x4DBC, 0x391A, 0x28D4, 0x1CAF
	.2byte 0x5D3D, 0x28DC, 0x1C97, 0x1491
	.2byte 0x6C9E, 0x147E, 0x0C5B, 0x0853
	.2byte 0x7C1F, 0x001F, 0x001E, 0x0014
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript102
gApZ2Jungle2_PlttAnimScript102:
	.4byte gApZ2Jungle2_PlttAnimScript102_0
gApZ2Jungle2_PlttAnimScript102_0:
	.byte 0, 64
	.byte 1, 16
	.byte 2, 16
	.byte 3, 10
	.byte 2, 16
	.byte 1, 16
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim103
gApZ2Jungle2_PlttAnim103: @ Zero 2's palette animation 103
	.byte 5, 189, 189, 0
	.2byte 0x0011
	.2byte 0x0015
	.2byte 0x0018
	.2byte 0x001C
	.2byte 0x001F
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript103
gApZ2Jungle2_PlttAnimScript103:
	.4byte gApZ2Jungle2_PlttAnimScript103_0
gApZ2Jungle2_PlttAnimScript103_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 4, 8
	.byte 3, 8
	.byte 2, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim104
gApZ2Jungle2_PlttAnim104: @ Zero 2's palette animation 104
	.byte 5, 113, 114, 0
	.2byte 0x4645, 0x3B3F
	.2byte 0x46C5, 0x3B7F
	.2byte 0x4725, 0x3B9F
	.2byte 0x4785, 0x3BDF
	.2byte 0x5FEE, 0x4FFF
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript104
gApZ2Jungle2_PlttAnimScript104:
	.4byte gApZ2Jungle2_PlttAnimScript104_0
gApZ2Jungle2_PlttAnimScript104_0:
	.byte 0, 16
	.byte 1, 16
	.byte 2, 16
	.byte 3, 16
	.byte 4, 16
	.byte 3, 16
	.byte 2, 16
	.byte 1, 16
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim105
gApZ2Jungle2_PlttAnim105: @ Zero 2's palette animation 105
	.byte 5, 75, 75, 0
	.2byte 0x001F
	.2byte 0x0C19
	.2byte 0x1813
	.2byte 0x240D
	.2byte 0x3007
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript105
gApZ2Jungle2_PlttAnimScript105:
	.4byte gApZ2Jungle2_PlttAnimScript105_0
gApZ2Jungle2_PlttAnimScript105_0:
	.byte 0, 16
	.byte 1, 16
	.byte 2, 16
	.byte 3, 16
	.byte 4, 16
	.byte 3, 16
	.byte 2, 16
	.byte 1, 16
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim106
gApZ2Jungle2_PlttAnim106: @ Zero 2's palette animation 106
	.byte 4, 249, 249, 0
	.2byte 0x53FF
	.2byte 0x47DC
	.2byte 0x3B99
	.2byte 0x2F55
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript106
gApZ2Jungle2_PlttAnimScript106:
	.4byte gApZ2Jungle2_PlttAnimScript106_0
gApZ2Jungle2_PlttAnimScript106_0:
	.byte 0, 16
	.byte 1, 16
	.byte 2, 16
	.byte 3, 16
	.byte 2, 16
	.byte 1, 16
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim107
gApZ2Jungle2_PlttAnim107: @ Zero 2's palette animation 107
	.byte 4, 252, 252, 0
	.2byte 0x09DF
	.2byte 0x0A7F
	.2byte 0x0B1F
	.2byte 0x0B5F
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript107
gApZ2Jungle2_PlttAnimScript107:
	.4byte gApZ2Jungle2_PlttAnimScript107_0
gApZ2Jungle2_PlttAnimScript107_0:
	.byte 0, 8
	.byte 1, 10
	.byte 2, 12
	.byte 3, 14
	.byte 2, 12
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim108
gApZ2Jungle2_PlttAnim108: @ Zero 2's palette animation 108
	.byte 5, 253, 253, 0
	.2byte 0x7F40
	.2byte 0x6EC0
	.2byte 0x6260
	.2byte 0x5600
	.2byte 0x49A0
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript108
gApZ2Jungle2_PlttAnimScript108:
	.4byte gApZ2Jungle2_PlttAnimScript108_0
gApZ2Jungle2_PlttAnimScript108_0:
	.byte 0, 6
	.byte 1, 8
	.byte 2, 10
	.byte 3, 12
	.byte 4, 16
	.byte 3, 12
	.byte 2, 10
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim109
gApZ2Jungle2_PlttAnim109: @ Zero 2's palette animation 109
	.byte 6, 255, 255, 0
	.2byte 0x4CB3
	.2byte 0x54D5
	.2byte 0x60F8
	.2byte 0x691A
	.2byte 0x757D
	.2byte 0x7DDF
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript109
gApZ2Jungle2_PlttAnimScript109:
	.4byte gApZ2Jungle2_PlttAnimScript109_0
gApZ2Jungle2_PlttAnimScript109_0:
	.byte 0, 2
	.byte 1, 2
	.byte 2, 2
	.byte 3, 2
	.byte 4, 2
	.byte 5, 2
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim110
gApZ2Jungle2_PlttAnim110: @ Zero 2's palette animation 110
	.byte 5, 217, 217, 0
	.2byte 0x023F
	.2byte 0x05FB
	.2byte 0x0DD6
	.2byte 0x1572
	.2byte 0x210E
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript110
gApZ2Jungle2_PlttAnimScript110:
	.4byte gApZ2Jungle2_PlttAnimScript110_0
gApZ2Jungle2_PlttAnimScript110_0:
	.byte 0, 16
	.byte 1, 6
	.byte 2, 8
	.byte 3, 10
	.byte 4, 32
	.byte 3, 6
	.byte 2, 8
	.byte 1, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim111
gApZ2Jungle2_PlttAnim111: @ Zero 2's palette animation 111
	.byte 4, 163, 167, 0
	.2byte 0x07FF, 0x73F1, 0x1F7F, 0x6AEF, 0x2EBC
	.2byte 0x079F, 0x73F1, 0x173F, 0x6AEF, 0x22BD
	.2byte 0x031F, 0x73F1, 0x0ADF, 0x6AEF, 0x129E
	.2byte 0x029F, 0x73F1, 0x029F, 0x6AEF, 0x029F
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript111
gApZ2Jungle2_PlttAnimScript111:
	.4byte gApZ2Jungle2_PlttAnimScript111_0
gApZ2Jungle2_PlttAnimScript111_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 2, 8
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim112
gApZ2Jungle2_PlttAnim112: @ Zero 2's palette animation 112
	.byte 4, 70, 70, 0
	.2byte 0x03FF
	.2byte 0x039F
	.2byte 0x031F
	.2byte 0x02BF
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript112
gApZ2Jungle2_PlttAnimScript112:
	.4byte gApZ2Jungle2_PlttAnimScript112_0
gApZ2Jungle2_PlttAnimScript112_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 2, 8
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim113
gApZ2Jungle2_PlttAnim113: @ Zero 2's palette animation 113
	.byte 3, 65, 65, 0
	.2byte 0x7FF1
	.2byte 0x4218
	.2byte 0x001F
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript113
gApZ2Jungle2_PlttAnimScript113:
	.4byte gApZ2Jungle2_PlttAnimScript113_0
gApZ2Jungle2_PlttAnimScript113_0:
	.byte 0, 2
	.byte 1, 2
	.byte 2, 2
	.byte 1, 2
	.byte 0, 254
	.balign 4, 0

.global gApZ2Jungle2_PlttAnim115
gApZ2Jungle2_PlttAnim115: @ Zero 2's palette animation 115
	.byte 4, 81, 90, 0
	.2byte 0x41EE, 0x3966, 0x3945, 0x3904, 0x34C2, 0x34A2, 0x44C3, 0x40C3, 0x38A3, 0x4A50
	.2byte 0x4A30, 0x49A6, 0x4166, 0x3D25, 0x3CE2, 0x34A2, 0x44C3, 0x40C3, 0x38A3, 0x4AF5
	.2byte 0x5672, 0x55E6, 0x4586, 0x3D45, 0x40E2, 0x34A2, 0x44C3, 0x40C3, 0x38A3, 0x4B7A
	.2byte 0x5EB4, 0x6606, 0x49A6, 0x4166, 0x44E2, 0x34A2, 0x44C3, 0x40C3, 0x38A3, 0x4BFF
	.balign 4, 0
.global gApZ2Jungle2_PlttAnimScript115
gApZ2Jungle2_PlttAnimScript115:
	.4byte gApZ2Jungle2_PlttAnimScript115_0
gApZ2Jungle2_PlttAnimScript115_0:
	.byte 0, 16
	.byte 1, 16
	.byte 2, 16
	.byte 3, 16
	.byte 2, 16
	.byte 1, 16
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Jungle2_Metatiles
gApZ2Jungle2_Metatiles:
	.incbin "data/ap/z2_jungle2/metatile.bin"
	.balign 4, 0

.global gApZ2Jungle2_Attrs
gApZ2Jungle2_Attrs:
	.incbin "data/ap/z2_jungle2/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Jungle2_Chunks
gApZ2Jungle2_Chunks:
	.incbin "data/ap/z2_jungle2/screen.bin"
	.balign 4, 0

.global gApZ2MugshotFrog
gApZ2MugshotFrog:
	.incbin "data/ap/z2_jungle2/mugshot_frog.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotFrog_Pal
gApZ2MugshotFrog_Pal:
	.incbin "data/ap/z2_jungle2/mugshot_frog.gbapal"
	.balign 4, 0

.global gApZ2MugshotBabyElves
gApZ2MugshotBabyElves:
	.incbin "data/ap/z2_jungle2/mugshot_babyelves.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotBabyElves_Pal
gApZ2MugshotBabyElves_Pal:
	.incbin "data/ap/z2_jungle2/mugshot_babyelves.gbapal"
	.balign 4, 0

gApZ2Jungle2_Ts0_Tiles:
	.incbin "data/ap/z2_jungle2/tileset0.4bpp"
	.balign 4, 0
gApZ2Jungle2_Ts0_Pal:
	.incbin "data/ap/z2_jungle2/tileset0.gbapal"
	.balign 4, 0

gApZ2Jungle2_Ts1_Tiles:
	.incbin "data/ap/z2_jungle2/tileset1.4bpp"
	.balign 4, 0
gApZ2Jungle2_Ts1_Pal:
	.incbin "data/ap/z2_jungle2/tileset1.gbapal"
	.balign 4, 0

gApZ2Jungle2_Ts2_Tiles:
	.incbin "data/ap/z2_jungle2/tileset2.4bpp"
	.balign 4, 0
gApZ2Jungle2_Ts2_Pal:
	.incbin "data/ap/z2_jungle2/tileset2.gbapal"
	.balign 4, 0

gApZ2Jungle2_Ts3_Tiles:
	.incbin "data/ap/z2_jungle2/tileset3.4bpp"
	.balign 4, 0
gApZ2Jungle2_Ts3_Pal:
	.incbin "data/ap/z2_jungle2/tileset3.gbapal"
	.balign 4, 0

gApZ2Jungle2_Ts4_Tiles:
	.incbin "data/ap/z2_jungle2/tileset4.4bpp"
	.balign 4, 0
gApZ2Jungle2_Ts4_Pal:
	.incbin "data/ap/z2_jungle2/tileset4.gbapal"
	.balign 4, 0

gApZ2Jungle2_Anim0_Tiles:
	.incbin "data/ap/z2_jungle2/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Jungle2_Anim0_Pal:
	.incbin "data/ap/z2_jungle2/tile_anim0.gbapal"
	.balign 4, 0
