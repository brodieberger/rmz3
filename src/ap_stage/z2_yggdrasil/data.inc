@ Zero 2's YGGR-DRASILL AKA Yggdrasil

.balign 4

.global gApZ2Yggdrasil_Terrain
gApZ2Yggdrasil_Terrain:
	.4byte gApZ2Yggdrasil_Metatiles-.
	.4byte gApZ2Yggdrasil_Attrs-(.-4)
	.4byte gApZ2Yggdrasil_Chunks-(.-8)

.global gApZ2Yggdrasil_Tilesets
gApZ2Yggdrasil_Tilesets: @ ColorGraphic[4]

gApZ2Yggdrasil_Ts0:
	.4byte gApZ2Yggdrasil_Ts0_Tiles-.
	.4byte 16128 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Ts0_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Yggdrasil_Ts1:
	.4byte gApZ2Yggdrasil_Ts1_Tiles-.
	.4byte 13952 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Ts1_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Yggdrasil_Ts2:
	.4byte gApZ2Yggdrasil_Ts2_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Ts2_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Yggdrasil_Ts3:
	.4byte gApZ2Yggdrasil_Ts3_Tiles-.
	.4byte 9912 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Yggdrasil_Ts3_Pal-.
		.2byte 128
		.byte 0, 2

.global gApZ2Yggdrasil_TileAnim
gApZ2Yggdrasil_TileAnim: @ ColorGraphic[5]

gApZ2Yggdrasil_Anim0:
	.4byte gApZ2Yggdrasil_Anim0_Tiles-.
	.4byte 384 | (851 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Anim0_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Yggdrasil_Anim1:
	.4byte gApZ2Yggdrasil_Anim1_Tiles-.
	.4byte 384 | (851 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Anim1_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Yggdrasil_Anim2:
	.4byte gApZ2Yggdrasil_Anim2_Tiles-.
	.4byte 384 | (851 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Anim2_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Yggdrasil_Anim3:
	.4byte gApZ2Yggdrasil_Anim3_Tiles-.
	.4byte 384 | (851 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Anim3_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Yggdrasil_Anim4:
	.4byte gApZ2Yggdrasil_Anim4_Tiles-.
	.4byte 384 | (851 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Yggdrasil_Anim4_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Yggdrasil_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 832*PX, 4304*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Yggdrasil_Script
gApZ2Yggdrasil_Script:
	spawn 0, gApZ2Yggdrasil_Zero
	reset_camera gApZ2Yggdrasil_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Yggdrasil_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 832*PX, 4304*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Yggdrasil_AgainScript
gApZ2Yggdrasil_AgainScript:
	spawn 0, gApZ2Yggdrasil_AgainZero
	reset_camera gApZ2Yggdrasil_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Yggdrasil_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 848*PX, 3184*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Yggdrasil_CheckpointScript
gApZ2Yggdrasil_CheckpointScript:
	spawn 0, gApZ2Yggdrasil_CheckpointZero
	reset_camera gApZ2Yggdrasil_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Yggdrasil_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 608*PX, 624*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Yggdrasil_BossRestartScript
gApZ2Yggdrasil_BossRestartScript:
	spawn 0, gApZ2Yggdrasil_BossRestartZero
	reset_camera gApZ2Yggdrasil_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Yggdrasil_ResultScript
gApZ2Yggdrasil_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Yggdrasil_StartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 832*PX, 4304*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_LowDoor:
	.byte ENTITY_SOLID, SOLID_Z2_HATCH, 0, 0
	.4byte 488*PX, 3032*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub1RestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 848*PX, 3184*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Snake:
	.byte ENTITY_BOSS, BOSS_Z2_SNAKE, 1, 0
	.4byte 1920*PX, 1760*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Bear:
	.byte ENTITY_BOSS, BOSS_Z2_BEAR, 0, 0
	.4byte 1984*PX, 3184*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Magnion:
	.byte ENTITY_BOSS, BOSS_Z2_MAGNION, 0, 3
	.4byte 1872*PX, 2512*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub1Life:
	.byte ENTITY_ITEM, ITEM_GENERAL, 0, 2
	.4byte 640*PX, 3152*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub1Energy:
	.byte ENTITY_ITEM, ITEM_GENERAL, 1, 2
	.4byte 544*PX, 3152*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_LowDoorOpen:
	.byte ENTITY_SOLID, SOLID_Z2_HATCH, 1, 0
	.4byte 488*PX, 3032*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_HighDoor:
	.byte ENTITY_SOLID, SOLID_Z2_HATCH, 0, 0
	.4byte 488*PX, 1592*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub1DoneZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 928*PX, 3024*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_Hub2RestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 848*PX, 1744*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Panter:
	.byte ENTITY_BOSS, BOSS_Z2_PANTER, 1, 0
	.4byte 1944*PX, 392*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Kuwagust:
	.byte ENTITY_BOSS, BOSS_Z2_KUWAGUST2, 0, 0
	.4byte 2640*PX, 320*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Frog:
	.byte ENTITY_BOSS, BOSS_Z2_FROG, 0, 0
	.4byte 1872*PX, 1088*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub2Life:
	.byte ENTITY_ITEM, ITEM_GENERAL, 0, 2
	.4byte 640*PX, 1712*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Hub2Energy:
	.byte ENTITY_ITEM, ITEM_GENERAL, 1, 2
	.4byte 544*PX, 1712*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_HighDoorOpen:
	.byte ENTITY_SOLID, SOLID_Z2_HATCH, 1, 0
	.4byte 488*PX, 1592*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_ClimbZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 576*PX, 1552*PX
	.4byte DIR_RIGHT

gApZ2Yggdrasil_TopZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 608*PX, 624*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Elpizo:
	.byte ENTITY_BOSS, BOSS_Z2_ELPIZO, 0, 0
	.4byte 800*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Final:
	.byte ENTITY_BOSS, BOSS_Z2_ELPIZO_FINAL, 0, 0
	.4byte 720*PX, 384*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_SealElpizo:
	.byte ENTITY_SOLID, SOLID_Z2_YGG_ELPIZO, 0, 0
	.4byte 800*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_DarkElf:
	.byte ENTITY_SOLID, SOLID_Z2_DARK_ELF, 0, 0
	.4byte 800*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_Seal:
	.byte ENTITY_SOLID, SOLID_Z2_YGG_SEAL, 0, 0
	.4byte 720*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_FreedElf:
	.byte ENTITY_SOLID, SOLID_Z2_DARK_ELF_TWIN, 0, 0
	.4byte 720*PX, 352*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_EndSoul:
	.byte ENTITY_SOLID, SOLID_Z2_YGG_SOUL, 0, 0
	.4byte 752*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_EndRubble:
	.byte ENTITY_SOLID, SOLID_Z2_YGG_RUBBLE, 0, 0
	.4byte 752*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_EndElf:
	.byte ENTITY_SOLID, SOLID_Z2_DARK_ELF_END, 2, 0
	.4byte 752*PX, 464*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_EndX:
	.byte ENTITY_SOLID, SOLID_Z2_X, 0, 0
	.4byte 752*PX, 444*PX
	.4byte DIR_LEFT

gApZ2Yggdrasil_EndZeroAt:
	.4byte 688*PX, 464*PX - 1

gApZ2Yggdrasil_FreeCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, 15360*PX, 0*PX, 10240*PX

gApZ2Yggdrasil_Camera0832f974:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 464*PX, 976*PX, 0*PX, 10240*PX

gApZ2Yggdrasil_Camera0832f948:
	.byte 6, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 464*PX, 976*PX, 0*PX, 10240*PX

gApZ2Yggdrasil_Camera0832f9a0:
	.byte 1, 8, 0, 0
	.4byte 720*PX, 400*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 464*PX, 976*PX, 0*PX, 10240*PX

.global gApZ2Yggdrasil_OpeningScript
gApZ2Yggdrasil_OpeningScript:
	spawn 0, gApZ2Yggdrasil_StartZero
	reset_camera gApZ2Yggdrasil_FreeCamera
	lock
	start_transition 1
	wait 1
	change_entity_val 0, 4, 0
	spawn 3, gApZ2Yggdrasil_LowDoor
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	wait 15
	force 6, 0, 0
	wait 90
	indicator 1, 2, 0
	wait_indicator_end
	release
	resume 0
	end

.global gApZ2Yggdrasil_StartRestartScript
gApZ2Yggdrasil_StartRestartScript:
	spawn 0, gApZ2Yggdrasil_Hub1RestartZero
	reset_camera gApZ2Yggdrasil_FreeCamera
	lock
	start_transition 9
	wait 1
	spawn 3, gApZ2Yggdrasil_LowDoor
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

.global gApZ2Yggdrasil_SnakeScript
gApZ2Yggdrasil_SnakeScript:
	stop_bgm
	lock
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x7f000
	adjust_camera 4, 0, 0x71000
	adjust_camera 15, 0, 0
	wait 1
	spawn 1, gApZ2Yggdrasil_Snake
	play_bgm BGM_GUARDER_ROOM
	wait 119
	message 3, 0, 0x1461
	message 3, 1, 0x1462
	message 1, 0, 0x1460
	wait_msgbox_end
	entityflag 1, 0, TRUE
	wait 60
	warning_indicator
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_BearScript
gApZ2Yggdrasil_BearScript:
	stop_bgm
	lock
	force 0, 0, 0
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x78000
	adjust_camera 15, 0, 0
	wait 1
	spawn 1, gApZ2Yggdrasil_Bear
	play_bgm BGM_GUARDER_ROOM
	wait 119
	message 3, 0, 0x1464
	message 3, 1, 0x1465
	message 1, 0, 0x1463
	wait_msgbox_end
	entityflag 1, 0, TRUE
	wait 60
	warning_indicator
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_MagnionScript
gApZ2Yggdrasil_MagnionScript:
	stop_bgm
	lock
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x78000
	adjust_camera 4, 0, 0x9b000
	adjust_camera 15, 0, 0
	wait 1
	spawn 1, gApZ2Yggdrasil_Magnion
	play_bgm BGM_GUARDER_ROOM
	entityflag 1, 0, TRUE
	wait 240
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x94000
	wait 260
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 4, 0, 0x9a000
	wait 180
	message 3, 0, 0x1467
	message 3, 1, 0x1468
	message 1, 0, 0x1466
	wait_msgbox_end
	warning_indicator
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_Hub1ClearScript
gApZ2Yggdrasil_Hub1ClearScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	force 8, 0, 0
	message 6, 0, 0
	message 5, 1, 0
	wait_msgbox_end
	message 6, 1, 0
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	load_graphic_primitive
	stop_camera
	backdrop_color 0xffff
	start_transition 2
	wait_transition_end
	backdrop_color 0x0000
	change_entity_val 0, 0, gApZ2Yggdrasil_Hub1Return
	change_entity_val 0, 2, 0
	resume_camera
	adjust_camera 0, 0, 6
	adjust_camera 15, 0, 0
	start_transition 1
	wait 1
	force 6, 0, 0
	wait 1
	spawn 6, gApZ2Yggdrasil_Hub1Life
	change_entity_val 6, 7, 0
	spawn 6, gApZ2Yggdrasil_Hub1Energy
	change_entity_val 6, 7, 0
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	release
	end

.global gApZ2Yggdrasil_Hub1DoneScript
gApZ2Yggdrasil_Hub1DoneScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	force 8, 0, 0
	message 6, 0, 0
	message 5, 1, 0
	wait_msgbox_end
	message 6, 1, 0
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	load_graphic_primitive
	stop_camera
	backdrop_color 0xffff
	start_transition 2
	wait_transition_end
	backdrop_color 0x0000
	change_entity_val 0, 0, gApZ2Yggdrasil_Hub1Return
	change_entity_val 0, 2, 0
	resume_camera
	adjust_camera 0, 0, 6
	adjust_camera 15, 0, 0
	start_transition 1
	wait 1
	force 6, 0, 0
	wait 1
	spawn 6, gApZ2Yggdrasil_Hub1Life
	change_entity_val 6, 7, 0
	spawn 6, gApZ2Yggdrasil_Hub1Energy
	change_entity_val 6, 7, 0
	destroy 3
	spawn 3, gApZ2Yggdrasil_LowDoorOpen
	spawn 4, gApZ2Yggdrasil_HighDoor
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	release
	end

.global gApZ2Yggdrasil_Hub1RestartScript
gApZ2Yggdrasil_Hub1RestartScript:
	spawn 0, gApZ2Yggdrasil_Hub1DoneZero
	reset_camera gApZ2Yggdrasil_FreeCamera
	lock
	start_transition 9
	wait 1
	spawn 3, gApZ2Yggdrasil_LowDoorOpen
	spawn 4, gApZ2Yggdrasil_HighDoor
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

.global gApZ2Yggdrasil_Hub2RestartScript
gApZ2Yggdrasil_Hub2RestartScript:
	spawn 0, gApZ2Yggdrasil_Hub2RestartZero
	reset_camera gApZ2Yggdrasil_FreeCamera
	lock
	start_transition 9
	wait 1
	spawn 4, gApZ2Yggdrasil_HighDoor
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

.global gApZ2Yggdrasil_PanterScript
gApZ2Yggdrasil_PanterScript:
	destroy 3
	stop_bgm
	lock
	force 0, 0, 0
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x74000
	adjust_camera 4, 0, 0x15000
	adjust_camera 15, 0, 0
	wait 1
	spawn 1, gApZ2Yggdrasil_Panter
	play_bgm BGM_GUARDER_ROOM
	wait 119
	message 3, 0, 0x146a
	message 3, 1, 0x146b
	message 1, 0, 0x1469
	wait_msgbox_end
	entityflag 1, 0, TRUE
	wait 60
	warning_indicator
	adjust_camera 13, 0, 0x10000
	adjust_camera 12, 0, 0x7f000
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_KuwagustScript
gApZ2Yggdrasil_KuwagustScript:
	destroy 3
	stop_bgm
	lock
	force 0, 0, 0
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0xac800
	adjust_camera 15, 0, 0
	wait 1
	play_bgm BGM_GUARDER_ROOM
	wait 59
	spawn 1, gApZ2Yggdrasil_Kuwagust
	wait 120
	message 3, 0, 0x146d
	message 3, 1, 0x146e
	message 1, 0, 0x146c
	wait_msgbox_end
	entityflag 1, 0, TRUE
	wait 60
	warning_indicator
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_FrogScript
gApZ2Yggdrasil_FrogScript:
	destroy 3
	stop_bgm
	lock
	force 0, 0, 0
	pause
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x70800
	adjust_camera 15, 0, 0
	wait 1
	spawn 1, gApZ2Yggdrasil_Frog
	play_bgm BGM_GUARDER_ROOM
	wait 119
	message 3, 0, 0x1470
	message 3, 1, 0x1471
	message 1, 0, 0x146f
	wait_msgbox_end
	entityflag 1, 0, TRUE
	wait 60
	warning_indicator
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Yggdrasil_Hub2ClearScript
gApZ2Yggdrasil_Hub2ClearScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	force 8, 0, 0
	message 6, 0, 0
	message 5, 1, 0
	wait_msgbox_end
	message 6, 1, 0
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
	adjust_camera 13, 0, 0
	adjust_camera 12, 0, 0x3c0000
	destroy 1
	load_graphic_primitive
	stop_camera
	backdrop_color 0xffff
	start_transition 2
	wait_transition_end
	backdrop_color 0x0000
	change_entity_val 0, 0, gApZ2Yggdrasil_Hub2Return
	change_entity_val 0, 2, 0
	resume_camera
	adjust_camera 0, 0, 6
	adjust_camera 15, 0, 0
	start_transition 1
	wait 1
	force 6, 0, 0
	wait 1
	spawn 6, gApZ2Yggdrasil_Hub2Life
	change_entity_val 6, 7, 0
	spawn 6, gApZ2Yggdrasil_Hub2Energy
	change_entity_val 6, 7, 0
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	release
	end

.global gApZ2Yggdrasil_Hub2DoneScript
gApZ2Yggdrasil_Hub2DoneScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	force 8, 0, 0
	message 6, 0, 0
	message 5, 1, 0
	wait_msgbox_end
	message 6, 1, 0
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
	adjust_camera 13, 0, 0
	adjust_camera 12, 0, 0x3c0000
	destroy 1
	load_graphic_primitive
	stop_camera
	backdrop_color 0xffff
	start_transition 2
	wait_transition_end
	backdrop_color 0x0000
	change_entity_val 0, 0, gApZ2Yggdrasil_Hub2Return
	change_entity_val 0, 2, 0
	resume_camera
	adjust_camera 0, 0, 6
	adjust_camera 15, 0, 0
	start_transition 1
	wait 1
	force 6, 0, 0
	wait 1
	spawn 6, gApZ2Yggdrasil_Hub2Life
	change_entity_val 6, 7, 0
	spawn 6, gApZ2Yggdrasil_Hub2Energy
	change_entity_val 6, 7, 0
	destroy 4
	spawn 4, gApZ2Yggdrasil_HighDoorOpen
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	release
	end

.global gApZ2Yggdrasil_ClimbRestartScript
gApZ2Yggdrasil_ClimbRestartScript:
	spawn 0, gApZ2Yggdrasil_ClimbZero
	reset_camera gApZ2Yggdrasil_FreeCamera
	lock
	start_transition 9
	wait 1
	spawn 4, gApZ2Yggdrasil_HighDoorOpen
	wait_transition_end
	play_bgm BGM_Z2_YGGDRASIL
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

.global gApZ2Yggdrasil_TopRestartScript
gApZ2Yggdrasil_TopRestartScript:
	spawn 0, gApZ2Yggdrasil_TopZero
	reset_camera gApZ2Yggdrasil_Camera0832f974
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Yggdrasil_Hub1Return:
	.4byte 592*PX, 3232*PX

gApZ2Yggdrasil_Hub2Return:
	.4byte 592*PX, 1792*PX

.global gApZ2Yggdrasil_BossScript
gApZ2Yggdrasil_BossScript:
	destroy 3
	destroy 4
	change_entity_val 0, 2, 1
	lock
	killtimeelf
	stop_bgm
	pause
	emotion_bubble 0, 16, -40, 0
	wait 60
	spawn 3, gApZ2Yggdrasil_SealElpizo
	spawn 4, gApZ2Yggdrasil_DarkElf
	spawn 5, gApZ2Yggdrasil_Seal
	cmd0f 4, 3, 0
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x2d000
	forcekeyinput 0x10
	wait 60
	lock
	wait 60
	adjust_camera 15, 0, 0
	play_bgm BGM_Z2_ELPIZO
	wait 60
	entityflag 3, 0, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x1474
	wait_msgbox_end
	wait 15
	entityflag 3, 0, TRUE
	wait 60
	message 1, 0, 0x1475
	wait_msgbox_end
	forcekeyinput 0x4010
	play_se SE_Z2_DARK_BOLT
	entityflag 3, 2, TRUE
	wait 15
	forcekeyinput 0xffff
	wait 120
	message 1, 0, 0x1476
	wait_msgbox_end
	wait 15
	entityflag 3, 1, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	message 1, 0, 0x1477
	wait_msgbox_end
	wait 15
	entityflag 3, 3, TRUE
	wait 30
	message 1, 0, 0x1478
	wait_msgbox_end
	wait 60
	entityflag 3, 4, TRUE
	play_se SE_UNK_101
	wait 20
	stop_camera
	wait 1
	cmd06 135, 0, 0
	wait 1
	play_se SE_Z2_SEAL_STRIKE
	wait 120
	start_transition 6
	wait_transition_end
	cmd06 0, 1, 0
	resume_camera
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x2d000
	adjust_camera 15, 0, 0
	start_transition 5
	wait_transition_end
	wait 90
	entityflag 5, 0, TRUE
	play_se SE_Z2_FEFNIR_BUBBLE_GROW
	wait 90
	gimmick 1, 0, 1
	wait 300
	start_transition 6
	wait 16
	entityflag 3, 5, TRUE
	wait_transition_end
	destroy 5
	stop_camera
	wait 1
	play_se SE_Z2_SEAL_WHITEOUT
	backdrop_color 0xffff
	cmd06 136, 0, 0
	start_transition 5
	wait_transition_end
	stop_bgm
	wait 90
	spawn 6, gApZ2Yggdrasil_FreedElf
	cmd0f 6, 4, 0
	start_transition 6
	wait_transition_end
	backdrop_color 0x0000
	cmd06 0, 1, 0
	resume_camera
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x2d000
	adjust_camera 15, 0, 0
	entityflag 3, 6, TRUE
	wait 90
	play_bgm BGM_Z2_SEAL
	start_transition 5
	wait_transition_end
	wait 90
	entityflag 3, 1, TRUE
	play_se SE_Z2_ELPIZO_LAUGH
	wait 90
	entityflag 6, 0, TRUE
	wait 300
	message 1, 0, 0x1479
	wait_msgbox_end
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x2f800
	wait 15
	entityflag 3, 1, TRUE
	wait 90
	message 1, 0, 0x147a
	wait_msgbox_end
	wait 30
	entityflag 6, 1, TRUE
	wait 240
	destroy 6
	entityflag 4, 2, TRUE
	start_transition 5
	play_se SE_Z2_DARK_ELF_WAKE
	wait_transition_end
	wait 210
	entityflag 4, 0, TRUE
	wait 180
	adjust_camera 15, 0, 0
	entityflag 4, 1, TRUE
	wait 600
	entityflag 3, 4, TRUE
	wait 480
	message 1, 0, 0x147b
	wait_msgbox_end
	wait 15
	entityflag 3, 0, TRUE
	destroy 4
	stop_bgm
	wait 90
	entityflag 3, 5, TRUE
	wait 300
	start_transition 2
	wait_transition_end
	entityflag 3, 6, TRUE
	stop_camera
	wait 1
	quake 0, 0, 8
	wait 90
	cmd06 137, 0, 0
	play_se SE_Z2_DARK_MERGE
	start_transition 1
	wait_transition_end
	wait 60
	start_transition 2
	wait_transition_end
	quake 0, 0, 8
	wait 90
	cmd06 138, 0, 0
	play_se SE_Z2_DARK_MERGE
	start_transition 1
	wait_transition_end
	wait 60
	start_transition 2
	wait_transition_end
	quake 0, 0, 8
	wait 90
	cmd06 139, 0, 0
	play_se SE_Z2_DARK_MERGE
	start_transition 1
	wait_transition_end
	wait 60
	start_transition 2
	wait_transition_end
	quake 0, 0, 4
	wait 90
	cmd06 140, 0, 0
	play_se SE_Z2_DARK_MERGE
	start_transition 1
	wait_transition_end
	wait 60
	start_transition 2
	wait_transition_end
	stop_quake
	wait 120
	play_bgm BGM_Z2_ELPIZO_BATTLE
	cmd06 141, 3, 0
	start_transition 1
	cmd06 141, 4, 0
	message 1, 0, 0x147c
	wait_msgbox_end
	start_transition 2
	wait_transition_end
	cmd06 0, 1, 0
	spawn 1, gApZ2Yggdrasil_Elpizo
	resume_camera
	adjust_camera 0, 0, 1
	adjust_camera 3, 0, 0x2f800
	adjust_camera 15, 0, 0
	start_transition 1
	wait_transition_end
	wait 15
	entityflag 3, 7, TRUE
	wait 20
	entityflag 1, 0, TRUE
	adjust_camera 3, 0, 0x2e000
	adjust_camera 1, 0, 2
	wait 60
	destroy 3
	warning_indicator
	reset_camera gApZ2Yggdrasil_Camera0832f948
	wait_indicator_end
	force 1, 0, 0
	release
	resume 1
	end

.global gApZ2Yggdrasil_BossReturnScript
gApZ2Yggdrasil_BossReturnScript:
	change_entity_val 0, 2, 1
	forcekeyinput 0xffff
	pause
	emotion_bubble 0, 16, -40, 0
	wait 60
	spawn 1, gApZ2Yggdrasil_Elpizo
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x2e000
	force 9, 0, 0x2a000
	wait 30
	adjust_camera 15, 0, 0
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	reset_camera gApZ2Yggdrasil_Camera0832f948
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_ELPIZO_BATTLE
	resume 1
	end

.global gApZ2Yggdrasil_ElpizoDownScript
gApZ2Yggdrasil_ElpizoDownScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	wait 30
	adjust_camera 0, 0, 6
	adjust_camera 1, 0, 2
	adjust_camera 2, 0, 1
	wait 90
	play_bgm BGM_Z2_SEAL
	sweep 1, 0, 0
	message 1, 0, 0x147d
	wait_msgbox_end
	wait 15
	entityflag 1, 1, TRUE
	wait 30
	message 1, 0, 0x147e
	wait_msgbox_end
	wait 60
	entityflag 1, 7, TRUE
	wait 180
	adjust_camera 0, 0, 1
	adjust_camera 1, 0, 2
	adjust_camera 3, 0, 0x2d000
	stop_bgm
	wait 120
	adjust_camera 15, 0, 0
	cmd08_wait_set 1
	change_entity_val 1, 7, 0
	spawn 1, gApZ2Yggdrasil_Final
	entityflag 1, 0, TRUE
	play_bgm BGM_Z2_ELPIZO_FINAL
	time 0
	force 9, 0, 0x2d000
	change_entity_val 0, 2, 1
	waitabs 450
	warning_indicator
	reset_camera gApZ2Yggdrasil_Camera0832f948
	wait_indicator_end
	release
	resume 1
	end

.global gApZ2Yggdrasil_FinalDownScript
gApZ2Yggdrasil_FinalDownScript:
	forcekeyinput 0xffff
	stop_bgm
	wait 1
	lock
	wait 240
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	backdrop_color 0xFFFF
	wait 30
	destroy 1
	stop_camera
	wait 60
	play_bgm BGM_Z2_ENDING
	wait 60
	spawn 3, gApZ2Yggdrasil_EndSoul
	spawn 5, gApZ2Yggdrasil_EndRubble
	spawn 6, gApZ2Yggdrasil_EndElf
	cmd0f 3, 0, 0
	cmd0f 6, 3, 0
	reset_camera gApZ2Yggdrasil_Camera0832f9a0
	set_entity_coords 0, gApZ2Yggdrasil_EndZeroAt
	turn_right 0
	force 2, 0, 0
	backdrop_color 0x0000
	start_transition 5
	wait_transition_end
	wait 60
	message 1, 0, 0x147f
	wait_msgbox_end
	start_transition 2
	wait_transition_end
	stop_camera
	wait 1
	cmd06 142, 0, 0
	start_transition 1
	wait_transition_end
	wait 60
	message 1, 0, 0x1480
	wait_msgbox_end
	wait 15
	start_transition 2
	wait_transition_end
	cmd06 0, 1, 0
	reset_camera gApZ2Yggdrasil_Camera0832f9a0
	start_transition 1
	wait_transition_end
	wait 60
	entityflag 6, 5, TRUE
	wait 240
	message 1, 0, 0x1481
	wait_msgbox_end
	wait 30
	entityflag 6, 6, TRUE
	wait 300
	entityflag 3, 0, TRUE
	wait 60
	message 1, 0, 0x1482
	wait_msgbox_end
	wait 15
	entityflag 3, 1, TRUE
	entityflag 6, 0, TRUE
	wait 420
	entityflag 3, 2, TRUE
	wait 180
	message 1, 0, 0x1483
	wait_msgbox_end
	wait 60
	entityflag 3, 3, TRUE
	wait 240
	entityflag 6, 1, TRUE
	wait 60
	emotion_bubble 0, 8, -40, 0
	wait 120
	start_transition 2
	wait_transition_end
	stop_camera
	wait 1
	cmd06 143, 0, 0
	start_transition 1
	wait_transition_end
	wait 60
	message 1, 0, 0x1484
	wait_msgbox_end
	wait 15
	start_transition 2
	wait_transition_end
	cmd06 0, 1, 0
	reset_camera gApZ2Yggdrasil_Camera0832f9a0
	start_transition 1
	wait_transition_end
	wait 180
	entityflag 6, 2, TRUE
	wait 30
	message 1, 0, 0x1485
	wait_msgbox_end
	wait 60
	entityflag 6, 3, TRUE
	wait 180
	entityflag 6, 4, TRUE
	wait 900
	destroy 6
	wait 60
	spawn 6, gApZ2Yggdrasil_EndX
	wait 60
	emotion_bubble 0, 8, -40, 0
	wait 240
	message 1, 0, 0x1486
	wait_msgbox_end
	wait 150
	message 1, 0, 0x1487
	wait_msgbox_end
	wait 30
	start_transition 2
	wait_transition_end
	stop_camera
	wait 1
	cmd06 144, 2, 0
	start_transition 1
	cmd06 144, 4, 0
	wait_transition_end
	wait 90
	message 1, 0, 0x1488
	wait_msgbox_end
	wait 15
	start_transition 6
	wait_transition_end
	backdrop_color 0xFFFF
	cmd06 0, 1, 0
	wait 240
	stop_bgm
	destroy 3
	destroy 5
	destroy 6
	start_transition 5
	wait 150
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Yggdrasil_ClearScript
gApZ2Yggdrasil_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
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

.global gApZ2Yggdrasil_PlttAnim65
gApZ2Yggdrasil_PlttAnim65: @ Zero 2's palette animation 65
	.byte 12, 72, 79, 0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x56E0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x77E0, 0x56E0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x56E0, 0x77E0, 0x56E0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x35C0, 0x56E0, 0x77E0, 0x56E0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x35C0, 0x56E0, 0x77E0, 0x56E0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x35C0, 0x56E0, 0x77E0, 0x56E0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x35C0, 0x56E0, 0x77E0, 0x56E0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x35C0, 0x56E0, 0x77E0, 0x56E0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x35C0, 0x56E0, 0x77E0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x35C0, 0x56E0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x35C0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript65
gApZ2Yggdrasil_PlttAnimScript65:
	.4byte gApZ2Yggdrasil_PlttAnimScript65_0
gApZ2Yggdrasil_PlttAnimScript65_0:
	.byte 0, 60
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
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim66
gApZ2Yggdrasil_PlttAnim66: @ Zero 2's palette animation 66
	.byte 12, 56, 63, 0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x52C0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x73E0, 0x52C0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x52C0, 0x73E0, 0x52C0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x31A0, 0x52C0, 0x73E0, 0x52C0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x31A0, 0x52C0, 0x73E0, 0x52C0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x31A0, 0x52C0, 0x73E0, 0x52C0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x31A0, 0x52C0, 0x73E0, 0x52C0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x31A0, 0x52C0, 0x73E0, 0x52C0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x31A0, 0x52C0, 0x73E0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x31A0, 0x52C0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x31A0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript66
gApZ2Yggdrasil_PlttAnimScript66:
	.4byte gApZ2Yggdrasil_PlttAnimScript66_0
gApZ2Yggdrasil_PlttAnimScript66_0:
	.byte 0, 60
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
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim67
gApZ2Yggdrasil_PlttAnim67: @ Zero 2's palette animation 67
	.byte 12, 40, 47, 0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x4680, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x5B60, 0x4680, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x4680, 0x5B60, 0x4680, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x2DA0, 0x4680, 0x5B60, 0x4680, 0x14A0, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x2DA0, 0x4680, 0x5B60, 0x4680, 0x14A0, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x2DA0, 0x4680, 0x5B60, 0x4680, 0x14A0, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x2DA0, 0x4680, 0x5B60, 0x4680, 0x14A0
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x2DA0, 0x4680, 0x5B60, 0x4680
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x2DA0, 0x4680, 0x5B60
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x2DA0, 0x4680
	.2byte 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x14A0, 0x2DA0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript67
gApZ2Yggdrasil_PlttAnimScript67:
	.4byte gApZ2Yggdrasil_PlttAnimScript67_0
gApZ2Yggdrasil_PlttAnimScript67_0:
	.byte 0, 60
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
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim68
gApZ2Yggdrasil_PlttAnim68: @ Zero 2's palette animation 68
	.byte 5, 92, 95, 0
	.2byte 0x0011, 0x0006, 0x0006, 0x0006
	.2byte 0x001F, 0x0011, 0x0006, 0x0006
	.2byte 0x0017, 0x001F, 0x0011, 0x0006
	.2byte 0x000E, 0x0017, 0x001F, 0x0011
	.2byte 0x0006, 0x000E, 0x0017, 0x001F
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript68
gApZ2Yggdrasil_PlttAnimScript68:
	.4byte gApZ2Yggdrasil_PlttAnimScript68_0
gApZ2Yggdrasil_PlttAnimScript68_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 4, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim69
gApZ2Yggdrasil_PlttAnim69: @ Zero 2's palette animation 69
	.byte 8, 158, 159, 0
	.2byte 0x14A5, 0x14A5
	.2byte 0x14C5, 0x1D04
	.2byte 0x18E4, 0x2964
	.2byte 0x1D04, 0x35C4
	.2byte 0x2124, 0x4224
	.2byte 0x2544, 0x4E83
	.2byte 0x2964, 0x5B03
	.2byte 0x2D84, 0x6763
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript69
gApZ2Yggdrasil_PlttAnimScript69:
	.4byte gApZ2Yggdrasil_PlttAnimScript69_0
gApZ2Yggdrasil_PlttAnimScript69_0:
	.byte 0, 15
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 15
	.byte 6, 3
	.byte 5, 3
	.byte 4, 3
	.byte 3, 3
	.byte 2, 3
	.byte 1, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim70
gApZ2Yggdrasil_PlttAnim70: @ Zero 2's palette animation 70
	.byte 10, 186, 191, 0
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x1D88, 0x0461, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x4FB4, 0x1D88, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x36AE, 0x4FB4, 0x1D88, 0x0461, 0x0461, 0x0461
	.2byte 0x1D88, 0x36AE, 0x4FB4, 0x1D88, 0x0461, 0x0461
	.2byte 0x0461, 0x1D88, 0x36AE, 0x4FB4, 0x1D88, 0x0461
	.2byte 0x0461, 0x0461, 0x1D88, 0x36AE, 0x4FB4, 0x1D88
	.2byte 0x0461, 0x0461, 0x0461, 0x1D88, 0x36AE, 0x4FB4
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x1D88, 0x36AE
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x0461, 0x1D88
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript70
gApZ2Yggdrasil_PlttAnimScript70:
	.4byte gApZ2Yggdrasil_PlttAnimScript70_0
gApZ2Yggdrasil_PlttAnimScript70_0:
	.byte 0, 30
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 3
	.byte 8, 3
	.byte 9, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim71
gApZ2Yggdrasil_PlttAnim71: @ Zero 2's palette animation 71
	.byte 8, 239, 239, 0
	.2byte 0x14A5
	.2byte 0x1D07
	.2byte 0x2589
	.2byte 0x2DEB
	.2byte 0x366E
	.2byte 0x3ED0
	.2byte 0x4752
	.2byte 0x4FB4
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript71
gApZ2Yggdrasil_PlttAnimScript71:
	.4byte gApZ2Yggdrasil_PlttAnimScript71_0
gApZ2Yggdrasil_PlttAnimScript71_0:
	.byte 0, 15
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 15
	.byte 6, 3
	.byte 5, 3
	.byte 4, 3
	.byte 3, 3
	.byte 2, 3
	.byte 1, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim72
gApZ2Yggdrasil_PlttAnim72: @ Zero 2's palette animation 72
	.byte 10, 58, 63, 0
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x1D88, 0x0461, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x4FB4, 0x1D88, 0x0461, 0x0461, 0x0461, 0x0461
	.2byte 0x36AE, 0x4FB4, 0x1D88, 0x0461, 0x0461, 0x0461
	.2byte 0x1D88, 0x36AE, 0x4FB4, 0x1D88, 0x0461, 0x0461
	.2byte 0x0461, 0x1D88, 0x36AE, 0x4FB4, 0x1D88, 0x0461
	.2byte 0x0461, 0x0461, 0x1D88, 0x36AE, 0x4FB4, 0x1D88
	.2byte 0x0461, 0x0461, 0x0461, 0x1D88, 0x36AE, 0x4FB4
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x1D88, 0x36AE
	.2byte 0x0461, 0x0461, 0x0461, 0x0461, 0x0461, 0x1D88
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript72
gApZ2Yggdrasil_PlttAnimScript72:
	.4byte gApZ2Yggdrasil_PlttAnimScript72_0
gApZ2Yggdrasil_PlttAnimScript72_0:
	.byte 0, 30
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 3
	.byte 8, 3
	.byte 9, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim73
gApZ2Yggdrasil_PlttAnim73: @ Zero 2's palette animation 73
	.byte 8, 95, 95, 0
	.2byte 0x14A5
	.2byte 0x1D07
	.2byte 0x2589
	.2byte 0x2DEB
	.2byte 0x366E
	.2byte 0x3ED0
	.2byte 0x4752
	.2byte 0x4FB4
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript73
gApZ2Yggdrasil_PlttAnimScript73:
	.4byte gApZ2Yggdrasil_PlttAnimScript73_0
gApZ2Yggdrasil_PlttAnimScript73_0:
	.byte 0, 15
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 15
	.byte 6, 3
	.byte 5, 3
	.byte 4, 3
	.byte 3, 3
	.byte 2, 3
	.byte 1, 3
	.byte 0, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim74
gApZ2Yggdrasil_PlttAnim74: @ Zero 2's palette animation 74
	.byte 8, 222, 223, 0
	.2byte 0x14A5, 0x14A5
	.2byte 0x1CE4, 0x2104
	.2byte 0x2944, 0x3184
	.2byte 0x3184, 0x3E04
	.2byte 0x3DE3, 0x4E83
	.2byte 0x4623, 0x5B03
	.2byte 0x5283, 0x6B83
	.2byte 0x5AC2, 0x77E2
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript74
gApZ2Yggdrasil_PlttAnimScript74:
	.4byte gApZ2Yggdrasil_PlttAnimScript74_0
gApZ2Yggdrasil_PlttAnimScript74_0:
	.byte 0, 15
	.byte 1, 3
	.byte 2, 3
	.byte 3, 3
	.byte 4, 3
	.byte 5, 3
	.byte 6, 3
	.byte 7, 15
	.byte 6, 3
	.byte 5, 3
	.byte 4, 3
	.byte 3, 3
	.byte 2, 3
	.byte 1, 3
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim93
gApZ2Yggdrasil_PlttAnim93: @ Zero 2's palette animation 93
	.byte 1, 0, 15, 0
	.2byte 0x0000, 0x5904, 0x6CEC, 0x7CD3, 0x7E79, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript93
gApZ2Yggdrasil_PlttAnimScript93:
	.4byte gApZ2Yggdrasil_PlttAnimScript93_0
gApZ2Yggdrasil_PlttAnimScript93_0:
	.byte 0, 1
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim139
gApZ2Yggdrasil_PlttAnim139: @ Zero 2's palette animation 139
	.byte 1, 0, 15, 0
	.2byte 0x0000, 0x341A, 0x381A, 0x381B, 0x3C1B, 0x401B, 0x441C, 0x441C, 0x481C, 0x4C1D, 0x501D, 0x541E, 0x541E, 0x581E, 0x5C1F, 0x601F
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript139
gApZ2Yggdrasil_PlttAnimScript139:
	.4byte gApZ2Yggdrasil_PlttAnimScript139_0
gApZ2Yggdrasil_PlttAnimScript139_0:
	.byte 0, 1
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim51
gApZ2Yggdrasil_PlttAnim51: @ Zero 2's palette animation 51
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0015, 0x0015, 0x0015, 0x0015, 0x0000, 0x0000, 0x0000, 0x0000
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000A, 0x000A, 0x000A, 0x000A, 0x0000, 0x0000, 0x0000, 0x0000
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript51
gApZ2Yggdrasil_PlttAnimScript51:
	.4byte gApZ2Yggdrasil_PlttAnimScript51_0
gApZ2Yggdrasil_PlttAnimScript51_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 2, 8
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim52
gApZ2Yggdrasil_PlttAnim52: @ Zero 2's palette animation 52
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000
	.2byte 0x0000, 0x0465, 0x00C6, 0x1129, 0x0420, 0x1800, 0x1C80, 0x24E0, 0x001B, 0x005F, 0x0CDF, 0x213F, 0x294A, 0x0C42, 0x1484, 0x20E7
	.2byte 0x0000, 0x08EA, 0x058D, 0x2253, 0x0841, 0x3020, 0x3D00, 0x49C0, 0x0016, 0x009F, 0x19BF, 0x467F, 0x56B5, 0x1CA5, 0x2928, 0x45CE
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript52
gApZ2Yggdrasil_PlttAnimScript52:
	.4byte gApZ2Yggdrasil_PlttAnimScript52_0
gApZ2Yggdrasil_PlttAnimScript52_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 60
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim53
gApZ2Yggdrasil_PlttAnim53: @ Zero 2's palette animation 53
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.2byte 0x0000, 0x364A, 0x32CD, 0x4FB3, 0x3582, 0x5D80, 0x6A60, 0x7300, 0x294B, 0x29F5, 0x46F5, 0x6FB5, 0x7FF5, 0x4A05, 0x5268, 0x6F2E
	.2byte 0x0000, 0x5B25, 0x5B66, 0x67CA, 0x5AC1, 0x6EC0, 0x7720, 0x7B80, 0x56A6, 0x56EA, 0x636A, 0x77CA, 0x7FEA, 0x6302, 0x6B24, 0x7787
	.2byte 0x0000, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript53
gApZ2Yggdrasil_PlttAnimScript53:
	.4byte gApZ2Yggdrasil_PlttAnimScript53_0
gApZ2Yggdrasil_PlttAnimScript53_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 4
	.byte 3, 4
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim54
gApZ2Yggdrasil_PlttAnim54: @ Zero 2's palette animation 54
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.2byte 0x0000, 0x364A, 0x32CD, 0x4FB3, 0x3582, 0x5D80, 0x6A60, 0x7300, 0x294B, 0x29F5, 0x46F5, 0x6FB5, 0x7FF5, 0x4A05, 0x5268, 0x6F2E
	.2byte 0x0000, 0x5B25, 0x5B66, 0x67CA, 0x5AC1, 0x6EC0, 0x7720, 0x7B80, 0x56A6, 0x56EA, 0x636A, 0x77CA, 0x7FEA, 0x6302, 0x6B24, 0x7787
	.2byte 0x0000, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript54
gApZ2Yggdrasil_PlttAnimScript54:
	.4byte gApZ2Yggdrasil_PlttAnimScript54_0
gApZ2Yggdrasil_PlttAnimScript54_0:
	.byte 3, 4
	.byte 2, 4
	.byte 1, 4
	.byte 0, 4
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim55
gApZ2Yggdrasil_PlttAnim55: @ Zero 2's palette animation 55
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000
	.2byte 0x0000, 0x0465, 0x00C6, 0x1129, 0x0420, 0x1800, 0x1C80, 0x24E0, 0x001B, 0x005F, 0x0CDF, 0x213F, 0x294A, 0x0C42, 0x1484, 0x20E7
	.2byte 0x0000, 0x08EA, 0x058D, 0x2253, 0x0841, 0x3020, 0x3D00, 0x49C0, 0x0016, 0x009F, 0x19BF, 0x467F, 0x56B5, 0x1CA5, 0x2928, 0x45CE
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript55
gApZ2Yggdrasil_PlttAnimScript55:
	.4byte gApZ2Yggdrasil_PlttAnimScript55_0
gApZ2Yggdrasil_PlttAnimScript55_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 60
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim56
gApZ2Yggdrasil_PlttAnim56: @ Zero 2's palette animation 56
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.2byte 0x0000, 0x364A, 0x32CD, 0x4FB3, 0x3582, 0x5D80, 0x6A60, 0x7300, 0x294B, 0x29F5, 0x46F5, 0x6FB5, 0x7FF5, 0x4A05, 0x5268, 0x6F2E
	.2byte 0x0000, 0x5B25, 0x5B66, 0x67CA, 0x5AC1, 0x6EC0, 0x7720, 0x7B80, 0x56A6, 0x56EA, 0x636A, 0x77CA, 0x7FEA, 0x6302, 0x6B24, 0x7787
	.2byte 0x0000, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript56
gApZ2Yggdrasil_PlttAnimScript56:
	.4byte gApZ2Yggdrasil_PlttAnimScript56_0
gApZ2Yggdrasil_PlttAnimScript56_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 4
	.byte 3, 4
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim57
gApZ2Yggdrasil_PlttAnim57: @ Zero 2's palette animation 57
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x116F, 0x0A53, 0x337D, 0x1062, 0x4C40, 0x5D80, 0x6EA0, 0x0011, 0x00DF, 0x267F, 0x679F, 0x7FFF, 0x2D07, 0x3DAD, 0x66D5
	.2byte 0x0000, 0x364A, 0x32CD, 0x4FB3, 0x3582, 0x5D80, 0x6A60, 0x7300, 0x294B, 0x29F5, 0x46F5, 0x6FB5, 0x7FF5, 0x4A05, 0x5268, 0x6F2E
	.2byte 0x0000, 0x5B25, 0x5B66, 0x67CA, 0x5AC1, 0x6EC0, 0x7720, 0x7B80, 0x56A6, 0x56EA, 0x636A, 0x77CA, 0x7FEA, 0x6302, 0x6B24, 0x7787
	.2byte 0x0000, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0, 0x7FE0
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript57
gApZ2Yggdrasil_PlttAnimScript57:
	.4byte gApZ2Yggdrasil_PlttAnimScript57_0
gApZ2Yggdrasil_PlttAnimScript57_0:
	.byte 3, 4
	.byte 2, 4
	.byte 1, 4
	.byte 0, 4
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim76
gApZ2Yggdrasil_PlttAnim76: @ Zero 2's palette animation 76
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x45F2, 0x4215, 0x3A39, 0x367C, 0x329F, 0x46FF, 0x5B5F, 0x6B9F, 0x7FFF, 0x7FFF, 0x7FFF, 0x02BF, 0x03BF, 0x2FFF, 0x7FFF
	.2byte 0x0000, 0x41F2, 0x4235, 0x3A79, 0x36BC, 0x32FF, 0x473F, 0x5B7F, 0x6BBF, 0x7FFF, 0x7FFF, 0x7FFF, 0x0319, 0x03BF, 0x3BFD, 0x7FFF
	.2byte 0x0000, 0x41F2, 0x4255, 0x3A99, 0x36FC, 0x333F, 0x477F, 0x5B9F, 0x6BDF, 0x7FFF, 0x7FFF, 0x7FFF, 0x0373, 0x03BF, 0x47FB, 0x7FFF
	.2byte 0x0000, 0x41F2, 0x4275, 0x3AD9, 0x373C, 0x339F, 0x47BF, 0x5BDF, 0x6BFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x03CD, 0x2BF3, 0x57F9, 0x7FFF
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript76
gApZ2Yggdrasil_PlttAnimScript76:
	.4byte gApZ2Yggdrasil_PlttAnimScript76_0
gApZ2Yggdrasil_PlttAnimScript76_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 2, 8
	.byte 1, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim77
gApZ2Yggdrasil_PlttAnim77: @ Zero 2's palette animation 77
	.byte 6, 0, 15, 0
	.2byte 0x0000, 0x30EE, 0x40F2, 0x4C97, 0x545B, 0x601F, 0x501A, 0x3C35, 0x2C4F, 0x1C4A, 0x498C, 0x5E73, 0x601F, 0x7E3F, 0x7F5F, 0x7FFF
	.2byte 0x0000, 0x352F, 0x4133, 0x48F7, 0x50BB, 0x589F, 0x4CBB, 0x44D7, 0x38F2, 0x2D0E, 0x5610, 0x66D5, 0x4C9F, 0x669F, 0x6F7F, 0x7FFF
	.2byte 0x0000, 0x3950, 0x4153, 0x4557, 0x493B, 0x4D1F, 0x4D3C, 0x4979, 0x4596, 0x41D2, 0x5E94, 0x6B18, 0x391F, 0x4EDF, 0x5F9F, 0x7FFF
	.2byte 0x0000, 0x3D90, 0x4194, 0x4198, 0x419B, 0x459F, 0x49DD, 0x4E1B, 0x5259, 0x5697, 0x6B18, 0x737A, 0x259F, 0x331F, 0x4FBF, 0x7FFF
	.2byte 0x0000, 0x41D1, 0x41D4, 0x3DF8, 0x3DFC, 0x3A1F, 0x465E, 0x52BD, 0x5EFC, 0x6B5B, 0x779B, 0x7BBD, 0x121F, 0x1B7F, 0x3FDF, 0x7FFF
	.2byte 0x0000, 0x45F2, 0x4215, 0x3A39, 0x367C, 0x329F, 0x46FF, 0x5B5F, 0x6B9F, 0x7FFF, 0x7FFF, 0x7FFF, 0x02BF, 0x03BF, 0x2FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript77
gApZ2Yggdrasil_PlttAnimScript77:
	.4byte gApZ2Yggdrasil_PlttAnimScript77_0
gApZ2Yggdrasil_PlttAnimScript77_0:
	.byte 0, 6
	.byte 1, 6
	.byte 2, 6
	.byte 3, 6
	.byte 4, 6
	.byte 5, 6
	.byte 0, 255
	.balign 4, 0

.global gApZ2Yggdrasil_PlttAnim78
gApZ2Yggdrasil_PlttAnim78: @ Zero 2's palette animation 78
	.byte 6, 0, 15, 0
	.2byte 0x0000, 0x30EE, 0x40F2, 0x4C97, 0x545B, 0x601F, 0x501A, 0x3C35, 0x2C4F, 0x1C4A, 0x498C, 0x5E73, 0x601F, 0x7E3F, 0x7F5F, 0x7FFF
	.2byte 0x0000, 0x352F, 0x4133, 0x48F7, 0x50BB, 0x589F, 0x4CBB, 0x44D7, 0x38F2, 0x2D0E, 0x5610, 0x66D5, 0x4C9F, 0x669F, 0x6F7F, 0x7FFF
	.2byte 0x0000, 0x3950, 0x4153, 0x4557, 0x493B, 0x4D1F, 0x4D3C, 0x4979, 0x4596, 0x41D2, 0x5E94, 0x6B18, 0x391F, 0x4EDF, 0x5F9F, 0x7FFF
	.2byte 0x0000, 0x3D90, 0x4194, 0x4198, 0x419B, 0x459F, 0x49DD, 0x4E1B, 0x5259, 0x5697, 0x6B18, 0x737A, 0x259F, 0x331F, 0x4FBF, 0x7FFF
	.2byte 0x0000, 0x41D1, 0x41D4, 0x3DF8, 0x3DFC, 0x3A1F, 0x465E, 0x52BD, 0x5EFC, 0x6B5B, 0x779B, 0x7BBD, 0x121F, 0x1B7F, 0x3FDF, 0x7FFF
	.2byte 0x0000, 0x45F2, 0x4215, 0x3A39, 0x367C, 0x329F, 0x46FF, 0x5B5F, 0x6B9F, 0x7FFF, 0x7FFF, 0x7FFF, 0x02BF, 0x03BF, 0x2FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Yggdrasil_PlttAnimScript78
gApZ2Yggdrasil_PlttAnimScript78:
	.4byte gApZ2Yggdrasil_PlttAnimScript78_0
gApZ2Yggdrasil_PlttAnimScript78_0:
	.byte 5, 6
	.byte 4, 6
	.byte 3, 6
	.byte 2, 6
	.byte 1, 6
	.byte 0, 6
	.byte 0, 255
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Yggdrasil_Metatiles
gApZ2Yggdrasil_Metatiles:
	.incbin "data/ap/z2_yggdrasil/metatile.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_Attrs
gApZ2Yggdrasil_Attrs:
	.incbin "data/ap/z2_yggdrasil/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_Chunks
gApZ2Yggdrasil_Chunks:
	.incbin "data/ap/z2_yggdrasil/screen.bin"
	.balign 4, 0

.global gApZ2MugshotAnchus
gApZ2MugshotAnchus:
	.incbin "data/ap/z2_yggdrasil/mugshot_anchus.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotAnchus_Pal
gApZ2MugshotAnchus_Pal:
	.incbin "data/ap/z2_yggdrasil/mugshot_anchus.gbapal"
	.balign 4, 0

.global gApZ2MugshotDarkElpizo
gApZ2MugshotDarkElpizo:
	.incbin "data/ap/z2_yggdrasil/mugshot_darkelpizo.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotDarkElpizo_Pal
gApZ2MugshotDarkElpizo_Pal:
	.incbin "data/ap/z2_yggdrasil/mugshot_darkelpizo.gbapal"
	.balign 4, 0

.global gApZ2MugshotElpizoSorry
gApZ2MugshotElpizoSorry:
	.incbin "data/ap/z2_yggdrasil/mugshot_elpizosorry.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotElpizoSorry_Pal
gApZ2MugshotElpizoSorry_Pal:
	.incbin "data/ap/z2_yggdrasil/mugshot_elpizosorry.gbapal"
	.balign 4, 0

.global gApZ2MugshotDarkElfFace
gApZ2MugshotDarkElfFace:
	.incbin "data/ap/z2_yggdrasil/mugshot_darkelfface.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotDarkElfFace_Pal
gApZ2MugshotDarkElfFace_Pal:
	.incbin "data/ap/z2_yggdrasil/mugshot_darkelfface.gbapal"
	.balign 4, 0

.global gApZ2MugshotElpizoFallen
gApZ2MugshotElpizoFallen:
	.incbin "data/ap/z2_yggdrasil/mugshot_elpizofallen.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotElpizoFallen_Pal
gApZ2MugshotElpizoFallen_Pal:
	.incbin "data/ap/z2_yggdrasil/mugshot_elpizofallen.gbapal"
	.balign 4, 0

.global gApZ2Yggdrasil_Portrait
gApZ2Yggdrasil_Portrait:
	.incbin "data/ap/z2_yggdrasil/portrait.4bpp.lz"
	.balign 4, 0
.global gApZ2Yggdrasil_PortraitPal
gApZ2Yggdrasil_PortraitPal:
	.incbin "data/ap/z2_yggdrasil/portrait.gbapal"
	.balign 4, 0

.global gApZ2PictureSealBreak
gApZ2PictureSealBreak:
	.incbin "data/ap/z2_yggdrasil/picture_sealbreak.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureSealBreak_Pal
gApZ2PictureSealBreak_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_sealbreak.gbapal"
	.balign 4, 0
.global gApZ2PictureSealBreak_Map
gApZ2PictureSealBreak_Map:
	.incbin "data/ap/z2_yggdrasil/picture_sealbreak_map.bin"
	.balign 4, 0

.global gApZ2PictureZeroRage
gApZ2PictureZeroRage:
	.incbin "data/ap/z2_yggdrasil/picture_zerorage.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureZeroRage_Pal
gApZ2PictureZeroRage_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_zerorage.gbapal"
	.balign 4, 0
.global gApZ2PictureZeroRage_Map
gApZ2PictureZeroRage_Map:
	.incbin "data/ap/z2_yggdrasil/picture_zerorage_map.bin"
	.balign 4, 0

.global gApZ2PictureMerge0
gApZ2PictureMerge0:
	.incbin "data/ap/z2_yggdrasil/picture_merge0.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureMerge0_Pal
gApZ2PictureMerge0_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_merge0.gbapal"
	.balign 4, 0
.global gApZ2PictureMerge0_Map
gApZ2PictureMerge0_Map:
	.incbin "data/ap/z2_yggdrasil/picture_merge0_map.bin"
	.balign 4, 0

.global gApZ2PictureMerge1
gApZ2PictureMerge1:
	.incbin "data/ap/z2_yggdrasil/picture_merge1.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureMerge1_Pal
gApZ2PictureMerge1_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_merge1.gbapal"
	.balign 4, 0
.global gApZ2PictureMerge1_Map
gApZ2PictureMerge1_Map:
	.incbin "data/ap/z2_yggdrasil/picture_merge1_map.bin"
	.balign 4, 0

.global gApZ2PictureMerge2
gApZ2PictureMerge2:
	.incbin "data/ap/z2_yggdrasil/picture_merge2.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureMerge2_Pal
gApZ2PictureMerge2_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_merge2.gbapal"
	.balign 4, 0
.global gApZ2PictureMerge2_Map
gApZ2PictureMerge2_Map:
	.incbin "data/ap/z2_yggdrasil/picture_merge2_map.bin"
	.balign 4, 0

.global gApZ2PictureMerge3
gApZ2PictureMerge3:
	.incbin "data/ap/z2_yggdrasil/picture_merge3.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureMerge3_Pal
gApZ2PictureMerge3_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_merge3.gbapal"
	.balign 4, 0
.global gApZ2PictureMerge3_Map
gApZ2PictureMerge3_Map:
	.incbin "data/ap/z2_yggdrasil/picture_merge3_map.bin"
	.balign 4, 0

.global gApZ2PictureElpizoReborn
gApZ2PictureElpizoReborn:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoreborn.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureElpizoReborn_Pal
gApZ2PictureElpizoReborn_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoreborn.gbapal"
	.balign 4, 0
.global gApZ2PictureElpizoReborn_Map
gApZ2PictureElpizoReborn_Map:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoreborn_map.bin"
	.balign 4, 0

.global gApZ2PictureElpizoRegret
gApZ2PictureElpizoRegret:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoregret.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureElpizoRegret_Pal
gApZ2PictureElpizoRegret_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoregret.gbapal"
	.balign 4, 0
.global gApZ2PictureElpizoRegret_Map
gApZ2PictureElpizoRegret_Map:
	.incbin "data/ap/z2_yggdrasil/picture_elpizoregret_map.bin"
	.balign 4, 0

.global gApZ2PictureDarkElfCalm
gApZ2PictureDarkElfCalm:
	.incbin "data/ap/z2_yggdrasil/picture_darkelfcalm.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureDarkElfCalm_Pal
gApZ2PictureDarkElfCalm_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_darkelfcalm.gbapal"
	.balign 4, 0
.global gApZ2PictureDarkElfCalm_Map
gApZ2PictureDarkElfCalm_Map:
	.incbin "data/ap/z2_yggdrasil/picture_darkelfcalm_map.bin"
	.balign 4, 0

.global gApZ2PictureZeroSky
gApZ2PictureZeroSky:
	.incbin "data/ap/z2_yggdrasil/picture_zerosky.8bpp.lz"
	.balign 4, 0
.global gApZ2PictureZeroSky_Pal
gApZ2PictureZeroSky_Pal:
	.incbin "data/ap/z2_yggdrasil/picture_zerosky.gbapal"
	.balign 4, 0
.global gApZ2PictureZeroSky_Map
gApZ2PictureZeroSky_Map:
	.incbin "data/ap/z2_yggdrasil/picture_zerosky_map.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_Layer3Map
gApZ2Yggdrasil_Layer3Map:
	.incbin "data/ap/z2_yggdrasil/layer3_map.bin"

.global gApZ2Yggdrasil_PlatformMap
gApZ2Yggdrasil_PlatformMap:
	.incbin "data/ap/z2_yggdrasil/platform_map.bin"

.global gApZ2Yggdrasil_SkyMap
gApZ2Yggdrasil_SkyMap:
	.incbin "data/ap/z2_yggdrasil/sky_map.bin"

.global gApZ2Yggdrasil_ZeroSkyLowMap
gApZ2Yggdrasil_ZeroSkyLowMap:
	.incbin "data/ap/z2_yggdrasil/zeroskylow_map.bin"

.global gApZ2Yggdrasil_SkyTiles
gApZ2Yggdrasil_SkyTiles:
	.incbin "data/ap/z2_yggdrasil/skytiles.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_SkyPal
gApZ2Yggdrasil_SkyPal:
	.incbin "data/ap/z2_yggdrasil/skypal.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_BlastTiles
gApZ2Yggdrasil_BlastTiles:
	.incbin "data/ap/z2_yggdrasil/blasttiles.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_BlastPal
gApZ2Yggdrasil_BlastPal:
	.incbin "data/ap/z2_yggdrasil/blastpal.bin"
	.balign 4, 0

.global gApZ2Yggdrasil_BlastShades
gApZ2Yggdrasil_BlastShades:
	.incbin "data/ap/z2_yggdrasil/blastshades.bin"
	.balign 4, 0

gApZ2Yggdrasil_Ts0_Tiles:
	.incbin "data/ap/z2_yggdrasil/tileset0.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Ts0_Pal:
	.incbin "data/ap/z2_yggdrasil/tileset0.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Ts1_Tiles:
	.incbin "data/ap/z2_yggdrasil/tileset1.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Ts1_Pal:
	.incbin "data/ap/z2_yggdrasil/tileset1.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Ts2_Tiles:
	.incbin "data/ap/z2_yggdrasil/tileset2.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Ts2_Pal:
	.incbin "data/ap/z2_yggdrasil/tileset2.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Ts3_Tiles:
	.incbin "data/ap/z2_yggdrasil/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Yggdrasil_Ts3_Pal:
	.incbin "data/ap/z2_yggdrasil/tileset3.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Anim0_Tiles:
	.incbin "data/ap/z2_yggdrasil/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Anim0_Pal:
	.incbin "data/ap/z2_yggdrasil/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Anim1_Tiles:
	.incbin "data/ap/z2_yggdrasil/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Anim1_Pal:
	.incbin "data/ap/z2_yggdrasil/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Anim2_Tiles:
	.incbin "data/ap/z2_yggdrasil/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Anim2_Pal:
	.incbin "data/ap/z2_yggdrasil/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Anim3_Tiles:
	.incbin "data/ap/z2_yggdrasil/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Anim3_Pal:
	.incbin "data/ap/z2_yggdrasil/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Yggdrasil_Anim4_Tiles:
	.incbin "data/ap/z2_yggdrasil/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Yggdrasil_Anim4_Pal:
	.incbin "data/ap/z2_yggdrasil/tile_anim4.gbapal"
	.balign 4, 0
