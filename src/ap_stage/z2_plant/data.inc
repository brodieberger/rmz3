@ Zero 2's PLANT AKA Power Room

.balign 4

.global gApZ2Plant_Terrain
gApZ2Plant_Terrain:
	.4byte gApZ2Plant_Metatiles-.
	.4byte gApZ2Plant_Attrs-(.-4)
	.4byte gApZ2Plant_Chunks-(.-8)

.global gApZ2Plant_Tilesets
gApZ2Plant_Tilesets: @ ColorGraphic[6]

gApZ2Plant_Ts0:
	.4byte gApZ2Plant_Ts0_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts0_Pal-.
		.2byte 192
		.byte 0, 2

gApZ2Plant_Ts1:
	.4byte gApZ2Plant_Ts1_Tiles-.
	.4byte 10688 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts1_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Plant_Ts2:
	.4byte gApZ2Plant_Ts2_Tiles-.
	.4byte 16192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts2_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Plant_Ts3:
	.4byte gApZ2Plant_Ts3_Tiles-.
	.4byte 16320 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts3_Pal-.
		.2byte 192
		.byte 0, 2

gApZ2Plant_Ts4:
	.4byte gApZ2Plant_Ts4_Tiles-.
	.4byte 12288 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts4_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Plant_Ts5:
	.4byte gApZ2Plant_Ts5_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Ts5_Pal-.
		.2byte 224
		.byte 0, 9

.global gApZ2Plant_TileAnim
gApZ2Plant_TileAnim: @ ColorGraphic[5]

gApZ2Plant_Anim0:
	.4byte gApZ2Plant_Anim0_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Anim0_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant_Anim1:
	.4byte gApZ2Plant_Anim1_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Anim1_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant_Anim2:
	.4byte gApZ2Plant_Anim2_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Anim2_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant_Anim3:
	.4byte gApZ2Plant_Anim3_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Anim3_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant_Anim4:
	.4byte gApZ2Plant_Anim4_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant_Anim4_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1088*PX
	.4byte DIR_RIGHT

gApZ2Plant_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant_Script
gApZ2Plant_Script:
	spawn 0, gApZ2Plant_Zero
	reset_camera gApZ2Plant_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x140e
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1088*PX
	.4byte DIR_RIGHT

gApZ2Plant_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant_AgainScript
gApZ2Plant_AgainScript:
	spawn 0, gApZ2Plant_AgainZero
	reset_camera gApZ2Plant_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1088*PX
	.4byte DIR_RIGHT

gApZ2Plant_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant_CheckpointScript
gApZ2Plant_CheckpointScript:
	spawn 0, gApZ2Plant_CheckpointZero
	reset_camera gApZ2Plant_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3712*PX, 1408*PX
	.4byte DIR_RIGHT

gApZ2Plant_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant_BossRestartScript
gApZ2Plant_BossRestartScript:
	spawn 0, gApZ2Plant_BossRestartZero
	reset_camera gApZ2Plant_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Plant_ResultScript
gApZ2Plant_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Plant_MiniBoss0:
	.byte ENTITY_BOSS, BOSS_Z2_FORTRESS, 1, 0
	.4byte 3904*PX, 592*PX
	.4byte DIR_LEFT

gApZ2Plant_MiniBoss1:
	.byte ENTITY_BOSS, BOSS_Z2_FORTRESS, 1, 0
	.4byte 7504*PX, 912*PX
	.4byte DIR_LEFT

gApZ2Plant_MiniBoss0Camera:
	.byte 6, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 3840*PX, 4080*PX, 512*PX, 960*PX

gApZ2Plant_MiniBoss1Camera:
	.byte 6, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 7440*PX, 7680*PX, 832*PX, 1280*PX

gApZ2Plant_Golem:
	.byte ENTITY_BOSS, BOSS_Z2_FLAME_GOLEM, 0, 0
	.4byte 6408*PX, 1744*PX
	.4byte DIR_LEFT

gApZ2Plant_GolemElf:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 53, 1
	.4byte 6408*PX, 1680*PX
	.4byte DIR_RIGHT

.global gApZ2Plant_Generator
gApZ2Plant_Generator:
	.byte ENTITY_ENEMY, ENEMY_Z2_GENERATOR, 0, 0
	.4byte 6232*PX, 808*PX
	.4byte DIR_LEFT

.global gApZ2Plant_MagmaDropper
gApZ2Plant_MagmaDropper:
	.byte ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 0
	.4byte 6088*PX, 1104*PX
	.4byte DIR_LEFT

.global gApZ2Plant_MiniBoss0Script
gApZ2Plant_MiniBoss0Script:
	spawn 1, gApZ2Plant_MiniBoss0
	entityflag 1, 0, TRUE
	reset_camera gApZ2Plant_MiniBoss0Camera
	end

.global gApZ2Plant_MiniBoss1Script
gApZ2Plant_MiniBoss1Script:
	spawn 1, gApZ2Plant_MiniBoss1
	entityflag 1, 0, TRUE
	reset_camera gApZ2Plant_MiniBoss1Camera
	end

@ Zero 2's scripts 2 and 3: the Flame Golem, its elf
.global gApZ2Plant_GolemScript
gApZ2Plant_GolemScript:
	spawn 1, gApZ2Plant_Golem
	pause
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Plant_GolemClearScript
gApZ2Plant_GolemClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	lockmenu
	spawn 9, gApZ2Plant_GolemElf
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

gApZ2Plant_Reactor0:
	.byte ENTITY_BOSS, BOSS_Z2_REACTOR, 0, 0
	.4byte 3840*PX, 1312*PX
	.4byte DIR_LEFT

gApZ2Plant_ReactorElf0:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 54, 1
	.4byte 3840*PX, 1248*PX
	.4byte DIR_RIGHT

gApZ2Plant_Magnion0:
	.byte ENTITY_BOSS, BOSS_Z2_MAGNION, 0, 0
	.4byte 3792*PX, 1360*PX
	.4byte DIR_LEFT

@ Zero 2's scripts 4, then 8: reactor 0, its elf
.global gApZ2Plant_Reactor0Script
gApZ2Plant_Reactor0Script:
	pause
	sweep 1, 0, 0
	spawn 1, gApZ2Plant_Reactor0
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Plant_Reactor0ClearScript
gApZ2Plant_Reactor0ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	spawn 9, gApZ2Plant_ReactorElf0
	destroy 1
	lockmenu
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

@ Zero 2's script 9: Phoenix Magnion in room 0, the line once a visit
.global gApZ2Plant_Magnion0Script
gApZ2Plant_Magnion0Script:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0xf0000
	adjust_camera 4, 0, 0x55000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0xeb000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion0
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x4e000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x54000
	wait 180
	message 1, 0, 0x140f
	wait_msgbox_end
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x46000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 9: Phoenix Magnion in room 0, the line once a visit
.global gApZ2Plant_Magnion0ReturnScript
gApZ2Plant_Magnion0ReturnScript:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0xf0000
	adjust_camera 4, 0, 0x55000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0xeb000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion0
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x4e000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x54000
	wait 180
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x46000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

gApZ2Plant_Room0Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3712*PX, 1408*PX
	.4byte DIR_RIGHT

@ Zero 2's script 14: restart in room 0
.global gApZ2Plant_Room0Script
gApZ2Plant_Room0Script:
	spawn 0, gApZ2Plant_Room0Zero
	reset_camera gApZ2Plant_RoomCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_Reactor1:
	.byte ENTITY_BOSS, BOSS_Z2_REACTOR, 3, 0
	.4byte 4800*PX, 512*PX
	.4byte DIR_LEFT

gApZ2Plant_ReactorElf1:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 54, 1
	.4byte 4800*PX, 448*PX
	.4byte DIR_RIGHT

gApZ2Plant_Magnion1:
	.byte ENTITY_BOSS, BOSS_Z2_MAGNION, 0, 3
	.4byte 4752*PX, 560*PX
	.4byte DIR_LEFT

@ Zero 2's scripts 5, then 8: reactor 3, its elf
.global gApZ2Plant_Reactor1Script
gApZ2Plant_Reactor1Script:
	pause
	sweep 1, 0, 0
	spawn 1, gApZ2Plant_Reactor1
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Plant_Reactor1ClearScript
gApZ2Plant_Reactor1ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	spawn 9, gApZ2Plant_ReactorElf1
	destroy 1
	lockmenu
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

@ Zero 2's script 10: Phoenix Magnion in room 1, the line once a visit
.global gApZ2Plant_Magnion1Script
gApZ2Plant_Magnion1Script:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x12c000
	adjust_camera 4, 0, 0x23000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x127000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion1
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x1c000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x22000
	wait 180
	message 1, 0, 0x140f
	wait_msgbox_end
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x14000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 10: Phoenix Magnion in room 1, the line once a visit
.global gApZ2Plant_Magnion1ReturnScript
gApZ2Plant_Magnion1ReturnScript:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x12c000
	adjust_camera 4, 0, 0x23000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x127000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion1
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x1c000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x22000
	wait 180
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x14000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

gApZ2Plant_Room1Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 4672*PX, 608*PX
	.4byte DIR_RIGHT

@ Zero 2's script 15: restart in room 1
.global gApZ2Plant_Room1Script
gApZ2Plant_Room1Script:
	spawn 0, gApZ2Plant_Room1Zero
	reset_camera gApZ2Plant_RoomCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_Reactor2:
	.byte ENTITY_BOSS, BOSS_Z2_REACTOR, 1, 0
	.4byte 5760*PX, 1152*PX
	.4byte DIR_LEFT

gApZ2Plant_ReactorElf2:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 54, 1
	.4byte 5760*PX, 1088*PX
	.4byte DIR_RIGHT

gApZ2Plant_Magnion2:
	.byte ENTITY_BOSS, BOSS_Z2_MAGNION, 0, 1
	.4byte 5712*PX, 1200*PX
	.4byte DIR_LEFT

@ Zero 2's scripts 6, then 8: reactor 1, its elf
.global gApZ2Plant_Reactor2Script
gApZ2Plant_Reactor2Script:
	pause
	sweep 1, 0, 0
	spawn 1, gApZ2Plant_Reactor2
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Plant_Reactor2ClearScript
gApZ2Plant_Reactor2ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	spawn 9, gApZ2Plant_ReactorElf2
	destroy 1
	lockmenu
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

@ Zero 2's script 11: Phoenix Magnion in room 2, the line once a visit
.global gApZ2Plant_Magnion2Script
gApZ2Plant_Magnion2Script:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x168000
	adjust_camera 4, 0, 0x4b000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x163000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion2
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x44000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x4a000
	wait 180
	message 1, 0, 0x140f
	wait_msgbox_end
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x3c000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 11: Phoenix Magnion in room 2, the line once a visit
.global gApZ2Plant_Magnion2ReturnScript
gApZ2Plant_Magnion2ReturnScript:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x168000
	adjust_camera 4, 0, 0x4b000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x163000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion2
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x44000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x4a000
	wait 180
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x3c000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

gApZ2Plant_Room2Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 5632*PX, 1248*PX
	.4byte DIR_RIGHT

@ Zero 2's script 16: restart in room 2
.global gApZ2Plant_Room2Script
gApZ2Plant_Room2Script:
	spawn 0, gApZ2Plant_Room2Zero
	reset_camera gApZ2Plant_RoomCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_Reactor3:
	.byte ENTITY_BOSS, BOSS_Z2_REACTOR, 2, 0
	.4byte 6720*PX, 512*PX
	.4byte DIR_LEFT

gApZ2Plant_ReactorElf3:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 54, 1
	.4byte 6720*PX, 448*PX
	.4byte DIR_RIGHT

gApZ2Plant_Magnion3:
	.byte ENTITY_BOSS, BOSS_Z2_MAGNION, 0, 2
	.4byte 6672*PX, 560*PX
	.4byte DIR_LEFT

@ Zero 2's scripts 7, then 8: reactor 2, its elf
.global gApZ2Plant_Reactor3Script
gApZ2Plant_Reactor3Script:
	pause
	sweep 1, 0, 0
	spawn 1, gApZ2Plant_Reactor3
	entityflag 1, 0, TRUE
	gameflag FLAG_2, TRUE
	resume 1
	end

.global gApZ2Plant_Reactor3ClearScript
gApZ2Plant_Reactor3ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	spawn 9, gApZ2Plant_ReactorElf3
	destroy 1
	lockmenu
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

@ Zero 2's script 12: Phoenix Magnion in room 3, the line once a visit
.global gApZ2Plant_Magnion3Script
gApZ2Plant_Magnion3Script:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x1a4000
	adjust_camera 4, 0, 0x23000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x19f000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion3
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x1c000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x22000
	wait 180
	message 1, 0, 0x140f
	wait_msgbox_end
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x14000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 12: Phoenix Magnion in room 3, the line once a visit
.global gApZ2Plant_Magnion3ReturnScript
gApZ2Plant_Magnion3ReturnScript:
	forcekeyinput 0xFFFF
	stop_bgm
	gameflag FLAG_2, TRUE
	wait 15
	emotion_bubble 0, 16, -40, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x1a4000
	adjust_camera 4, 0, 0x23000
	wait 45
	play_bgm BGM_GUARDER_ROOM
	wait 15
	force 9, 0, 0x19f000
	change_entity_val 0, 2, 1
	wait 15
	spawn 1, gApZ2Plant_Magnion3
	wait 120
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x1c000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x22000
	wait 180
	stop_bgm
	wait 30
	warning_indicator
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	adjust_camera 11, 0, 0
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 13, 0, 0x14000
	adjust_camera 14, 0, 0x280000
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

gApZ2Plant_Room3Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 6592*PX, 608*PX
	.4byte DIR_RIGHT

@ Zero 2's script 17: restart in room 3
.global gApZ2Plant_Room3Script
gApZ2Plant_Room3Script:
	spawn 0, gApZ2Plant_Room3Zero
	reset_camera gApZ2Plant_RoomCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_POWER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant_RoomCamera:
	.byte 3, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant_BossScript
gApZ2Plant_BossScript:
.global gApZ2Plant_BossReturnScript
gApZ2Plant_BossReturnScript:
	end

@ Zero 2's script 13
.global gApZ2Plant_ClearScript
gApZ2Plant_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	message 1, 0, 0x1410
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
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

.global gApZ2Plant_PlttAnim59
gApZ2Plant_PlttAnim59: @ Zero 2's palette animation 59
	.byte 3, 45, 47, 0
	.2byte 0x19D1, 0x2A75, 0x4B1A
	.2byte 0x4B1A, 0x19D1, 0x2A75
	.2byte 0x2A75, 0x4B1A, 0x19D1
	.balign 4, 0
.global gApZ2Plant_PlttAnimScript59
gApZ2Plant_PlttAnimScript59:
	.4byte gApZ2Plant_PlttAnimScript59_0
gApZ2Plant_PlttAnimScript59_0:
	.byte 0, 9
	.byte 1, 9
	.byte 2, 9
	.byte 0, 254
	.balign 4, 0

.global gApZ2Plant_PlttAnim60
gApZ2Plant_PlttAnim60: @ Zero 2's palette animation 60
	.byte 3, 77, 79, 0
	.2byte 0x66D4, 0x62B3, 0x5A51
	.2byte 0x5A51, 0x66D4, 0x62B3
	.2byte 0x62B3, 0x5A51, 0x66D4
	.balign 4, 0
.global gApZ2Plant_PlttAnimScript60
gApZ2Plant_PlttAnimScript60:
	.4byte gApZ2Plant_PlttAnimScript60_0
gApZ2Plant_PlttAnimScript60_0:
	.byte 0, 15
	.byte 1, 15
	.byte 2, 15
	.byte 0, 254
	.balign 4, 0

.global gApZ2Plant_PlttAnim61
gApZ2Plant_PlttAnim61: @ Zero 2's palette animation 61
	.byte 5, 43, 47, 0
	.2byte 0x013F, 0x027F, 0x035F, 0x1FFF, 0x5FFF
	.2byte 0x01FB, 0x02DB, 0x137B, 0x4B9D, 0x01DF
	.2byte 0x031C, 0x139D, 0x035F, 0x05DF, 0x025D
	.2byte 0x1FFF, 0x4FDF, 0x013F, 0x027F, 0x035F
	.2byte 0x035F, 0x013F, 0x027F, 0x035F, 0x1FFF
	.balign 4, 0
.global gApZ2Plant_PlttAnimScript61
gApZ2Plant_PlttAnimScript61:
	.4byte gApZ2Plant_PlttAnimScript61_0
gApZ2Plant_PlttAnimScript61_0:
	.byte 0, 11
	.byte 1, 12
	.byte 2, 13
	.byte 3, 15
	.byte 4, 17
	.byte 0, 254
	.balign 4, 0

.global gApZ2Plant_PlttAnim132
gApZ2Plant_PlttAnim132: @ Zero 2's palette animation 132
	.byte 3, 92, 94, 0
	.2byte 0x027F, 0x035F, 0x1FFF
	.2byte 0x035F, 0x1FFF, 0x027F
	.2byte 0x1FFF, 0x027F, 0x035F
	.balign 4, 0
.global gApZ2Plant_PlttAnimScript132
gApZ2Plant_PlttAnimScript132:
	.4byte gApZ2Plant_PlttAnimScript132_0
gApZ2Plant_PlttAnimScript132_0:
	.byte 0, 10
	.byte 1, 10
	.byte 2, 10
	.byte 0, 254
	.balign 4, 0

.global gApZ2Plant_PlttAnim58
gApZ2Plant_PlttAnim58: @ Zero 2's palette animation 58
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x001D, 0x013F, 0x777F, 0x7FFF, 0x7FFF, 0x1CE7, 0x2DED, 0x3EB1, 0x4757, 0x63B8, 0x77FD, 0x7FFF, 0x5D37, 0x7EBF, 0x7F7F
	.2byte 0x0000, 0x0856, 0x0938, 0x677D, 0x77FD, 0x7FFF, 0x1CE7, 0x2DED, 0x3EB1, 0x4757, 0x63B8, 0x77FD, 0x7FFF, 0x5D37, 0x7EBF, 0x7F7F
	.2byte 0x0000, 0x14AF, 0x1530, 0x577A, 0x6FDB, 0x7BFE, 0x1CE7, 0x2DED, 0x3EB1, 0x4757, 0x63B8, 0x77FD, 0x7FFF, 0x5D37, 0x7EBF, 0x7F7F
	.2byte 0x0000, 0x1CE7, 0x254B, 0x4757, 0x63B8, 0x77FD, 0x1CE7, 0x2DED, 0x3EB1, 0x4757, 0x63B8, 0x77FD, 0x7FFF, 0x5D37, 0x7EBF, 0x7F7F
	.balign 4, 0
.global gApZ2Plant_PlttAnimScript58
gApZ2Plant_PlttAnimScript58:
	.4byte gApZ2Plant_PlttAnimScript58_0
gApZ2Plant_PlttAnimScript58_0:
	.byte 3, 30
	.byte 2, 5
	.byte 1, 5
	.byte 0, 30
	.byte 1, 5
	.byte 2, 5
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Plant_Metatiles
gApZ2Plant_Metatiles:
	.incbin "data/ap/z2_plant/metatile.bin"
	.balign 4, 0

.global gApZ2Plant_Attrs
gApZ2Plant_Attrs:
	.incbin "data/ap/z2_plant/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Plant_Chunks
gApZ2Plant_Chunks:
	.incbin "data/ap/z2_plant/screen.bin"
	.balign 4, 0

.global gApZ2MugshotMagnion
gApZ2MugshotMagnion:
	.incbin "data/ap/z2_plant/mugshot_magnion.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotMagnion_Pal
gApZ2MugshotMagnion_Pal:
	.incbin "data/ap/z2_plant/mugshot_magnion.gbapal"
	.balign 4, 0

gApZ2Plant_Ts0_Tiles:
	.incbin "data/ap/z2_plant/tileset0.4bpp"
	.balign 4, 0
gApZ2Plant_Ts0_Pal:
	.incbin "data/ap/z2_plant/tileset0.gbapal"
	.balign 4, 0

gApZ2Plant_Ts1_Tiles:
	.incbin "data/ap/z2_plant/tileset1.4bpp"
	.balign 4, 0
gApZ2Plant_Ts1_Pal:
	.incbin "data/ap/z2_plant/tileset1.gbapal"
	.balign 4, 0

gApZ2Plant_Ts2_Tiles:
	.incbin "data/ap/z2_plant/tileset2.4bpp"
	.balign 4, 0
gApZ2Plant_Ts2_Pal:
	.incbin "data/ap/z2_plant/tileset2.gbapal"
	.balign 4, 0

gApZ2Plant_Ts3_Tiles:
	.incbin "data/ap/z2_plant/tileset3.4bpp"
	.balign 4, 0
gApZ2Plant_Ts3_Pal:
	.incbin "data/ap/z2_plant/tileset3.gbapal"
	.balign 4, 0

gApZ2Plant_Ts4_Tiles:
	.incbin "data/ap/z2_plant/tileset4.4bpp"
	.balign 4, 0
gApZ2Plant_Ts4_Pal:
	.incbin "data/ap/z2_plant/tileset4.gbapal"
	.balign 4, 0

gApZ2Plant_Ts5_Tiles:
	.incbin "data/ap/z2_plant/tileset5.4bpp"
	.balign 4, 0
gApZ2Plant_Ts5_Pal:
	.incbin "data/ap/z2_plant/tileset5.gbapal"
	.balign 4, 0

gApZ2Plant_Anim0_Tiles:
	.incbin "data/ap/z2_plant/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Plant_Anim0_Pal:
	.incbin "data/ap/z2_plant/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Plant_Anim1_Tiles:
	.incbin "data/ap/z2_plant/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Plant_Anim1_Pal:
	.incbin "data/ap/z2_plant/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Plant_Anim2_Tiles:
	.incbin "data/ap/z2_plant/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Plant_Anim2_Pal:
	.incbin "data/ap/z2_plant/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Plant_Anim3_Tiles:
	.incbin "data/ap/z2_plant/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Plant_Anim3_Pal:
	.incbin "data/ap/z2_plant/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Plant_Anim4_Tiles:
	.incbin "data/ap/z2_plant/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Plant_Anim4_Pal:
	.incbin "data/ap/z2_plant/tile_anim4.gbapal"
	.balign 4, 0
