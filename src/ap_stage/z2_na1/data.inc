@ Zero 2's NA-1 AKA Temple of Flame

.balign 4

.global gApZ2Na1_Terrain
gApZ2Na1_Terrain:
	.4byte gApZ2Na1_Metatiles-.
	.4byte gApZ2Na1_Attrs-(.-4)
	.4byte gApZ2Na1_Chunks-(.-8)

.global gApZ2Na1_Tilesets
gApZ2Na1_Tilesets: @ ColorGraphic[5]

gApZ2Na1_Ts0:
	.4byte gApZ2Na1_Ts0_Tiles-.
	.4byte 7616 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Ts0_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na1_Ts1:
	.4byte gApZ2Na1_Ts1_Tiles-.
	.4byte 4800 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Ts1_Pal-.
		.2byte 32
		.byte 0, 2

gApZ2Na1_Ts2:
	.4byte gApZ2Na1_Ts2_Tiles-.
	.4byte 7368 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na1_Ts2_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Na1_Ts3:
	.4byte gApZ2Na1_Ts3_Tiles-.
	.4byte 6100 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na1_Ts3_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Na1_Ts4:
	.4byte gApZ2Na1_Ts4_Tiles-.
	.4byte 5876 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Na1_Ts4_Pal-.
		.2byte 224
		.byte 0, 9

.global gApZ2Na1_TileAnim
gApZ2Na1_TileAnim: @ ColorGraphic[5]

gApZ2Na1_Anim0:
	.4byte gApZ2Na1_Anim0_Tiles-.
	.4byte 384 | (593 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Anim0_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Na1_Anim1:
	.4byte gApZ2Na1_Anim1_Tiles-.
	.4byte 384 | (593 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Anim1_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Na1_Anim2:
	.4byte gApZ2Na1_Anim2_Tiles-.
	.4byte 384 | (593 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Anim2_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Na1_Anim3:
	.4byte gApZ2Na1_Anim3_Tiles-.
	.4byte 384 | (593 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Anim3_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Na1_Anim4:
	.4byte gApZ2Na1_Anim4_Tiles-.
	.4byte 384 | (593 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Na1_Anim4_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Na1_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 784*PX
	.4byte DIR_RIGHT

gApZ2Na1_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na1_Script
gApZ2Na1_Script:
	spawn 0, gApZ2Na1_Zero
	reset_camera gApZ2Na1_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_LAVA_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na1_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 784*PX
	.4byte DIR_RIGHT

gApZ2Na1_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na1_AgainScript
gApZ2Na1_AgainScript:
	spawn 0, gApZ2Na1_AgainZero
	reset_camera gApZ2Na1_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_LAVA_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na1_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3936*PX, 1264*PX
	.4byte DIR_RIGHT

gApZ2Na1_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na1_CheckpointScript
gApZ2Na1_CheckpointScript:
	spawn 0, gApZ2Na1_CheckpointZero
	reset_camera gApZ2Na1_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_LAVA_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Na1_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 3936*PX, 1264*PX
	.4byte DIR_RIGHT

gApZ2Na1_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Na1_BossRestartScript
gApZ2Na1_BossRestartScript:
	spawn 0, gApZ2Na1_BossRestartZero
	reset_camera gApZ2Na1_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_LAVA_SHRINE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Na1_ResultScript
gApZ2Na1_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

@ Zero 2's script 2
.global gApZ2Na1_LavaScript
gApZ2Na1_LavaScript:
	lock
	pause
	emotion_bubble 0, 24, -40, 0
	quake 0, 0, 2
	wait 60
	gimmick 1, 0, 1
	change_camera_mode 1
	set_chase_mode 4
	set_camera_target_y 1120*PX
	wait 30
	quake 0, 0, 0
	gimmick 1, 0, 1
	wait 45
	change_camera_mode 3
	set_chase_mode 4
	wait 15
	release
	end

gApZ2Na1_Boss:
	.byte ENTITY_BOSS, BOSS_Z2_FEFNIR, 0, 0
	.4byte 3840*PX, 1440*PX
	.4byte DIR_LEFT

gApZ2Na1_BossCamera: @ Zero 2's, 0x0832e114
	.byte 4, 4, 1, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0xB800, 0x0, 0x0, 0x0
	.4byte 0*PX, 15360*PX, 0*PX, 10240*PX

gApZ2Na1_ClearZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 288*PX, 1584*PX
	.4byte DIR_RIGHT

gApZ2Na1_BeatenFefnir:
	.byte ENTITY_SOLID, SOLID_Z2_BEATEN_FEFNIR, 0, 0
	.4byte 432*PX, 1584*PX
	.4byte DIR_LEFT

@ Zero 2's script 4
.global gApZ2Na1_BossScript
gApZ2Na1_BossScript:
	stop_bgm
	lock
	pause
	cutscene_start CS_UNK_48
	change_entity_val 0, 2, 1
	wait 30
	play_bgm BGM_X
	spawn 1, gApZ2Na1_Boss
	wait 15
	emotion_bubble 0, 24, -40, 0
	wait 30
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 3960*PX
	wait 90
	message 1, 0, 0x144e
	wait_msgbox_end
	wait 60
	cutscene_end
	stop_bgm
	entityflag 1, 0, TRUE
	wait 140
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 100
	warning_indicator
	reset_camera gApZ2Na1_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 5
.global gApZ2Na1_BossReturnScript
gApZ2Na1_BossReturnScript:
	stop_bgm
	lock
	pause
	change_entity_val 0, 2, 1
	wait 30
	play_bgm BGM_X
	spawn 1, gApZ2Na1_Boss
	wait 15
	wait 45
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 3960*PX
	wait 30
	stop_bgm
	entityflag 1, 0, TRUE
	wait 140
	start_transition 6
	wait_transition_end
	wait 16
	start_transition 5
	wait_transition_end
	wait 100
	warning_indicator
	reset_camera gApZ2Na1_BossCamera
	wait_indicator_end
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 6: Fefnir's and Ciel's lines, room at bottom left
.global gApZ2Na1_ClearScript
gApZ2Na1_ClearScript:
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
	spawn 0, gApZ2Na1_ClearZero
	spawn 3, gApZ2Na1_BeatenFefnir
	reset_camera gApZ2Na1_Camera
	start_transition 1
	wait_transition_end
	play_bgm BGM_Z2_GUARDIAN_RETREAT
	entityflag 3, 0, TRUE
	wait 30
	message 1, 0, 0x144f
	wait_msgbox_end
	wait 60
	entityflag 3, 1, TRUE
	wait 120
	message 1, 0, 0x1450
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

.global gApZ2Na1_PlttAnim126
gApZ2Na1_PlttAnim126: @ Zero 2's palette animation 126
	.byte 4, 47, 47, 0
	.2byte 0x5AC0
	.2byte 0x5B20
	.2byte 0x5B80
	.2byte 0x5BE0
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript126
gApZ2Na1_PlttAnimScript126:
	.4byte gApZ2Na1_PlttAnimScript126_0
gApZ2Na1_PlttAnimScript126_0:
	.byte 0, 40
	.byte 1, 6
	.byte 2, 3
	.byte 3, 1
	.byte 2, 3
	.byte 1, 6
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na1_PlttAnim127
gApZ2Na1_PlttAnim127: @ Zero 2's palette animation 127
	.byte 4, 49, 75, 0
	.2byte 0x6780, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x5280, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7FA0
	.2byte 0x6340, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4A40, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B40
	.2byte 0x4E80, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x4200, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x72E0
	.2byte 0x39C0, 0x2909, 0x2D09, 0x3109, 0x310A, 0x312A, 0x352A, 0x352A, 0x352A, 0x352A, 0x394C, 0x3D8D, 0x41AD, 0x4610, 0x39C0, 0x03E0, 0x2D09, 0x2D09, 0x2D09, 0x4160, 0x2929, 0x314A, 0x396C, 0x3D8D, 0x41AE, 0x45CF, 0x7B00
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript127
gApZ2Na1_PlttAnimScript127:
	.4byte gApZ2Na1_PlttAnimScript127_0
gApZ2Na1_PlttAnimScript127_0:
	.byte 0, 12
	.byte 1, 12
	.byte 2, 12
	.byte 3, 12
	.byte 2, 12
	.byte 1, 12
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na1_PlttAnim128
gApZ2Na1_PlttAnim128: @ Zero 2's palette animation 128
	.byte 4, 97, 102, 0
	.2byte 0x1C1F, 0x0220, 0x7E80, 0x6A20, 0x5DE0, 0x55A0
	.2byte 0x1C18, 0x2300, 0x55A0, 0x7E80, 0x6A20, 0x5DE0
	.2byte 0x1810, 0x43E0, 0x5DE0, 0x55A0, 0x7E80, 0x6A20
	.2byte 0x1C18, 0x2300, 0x6A20, 0x5DE0, 0x55A0, 0x7E80
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript128
gApZ2Na1_PlttAnimScript128:
	.4byte gApZ2Na1_PlttAnimScript128_0
gApZ2Na1_PlttAnimScript128_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Na1_PlttAnim129
gApZ2Na1_PlttAnim129: @ Zero 2's palette animation 129
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x1CEB, 0x2531, 0x0539, 0x0DDE, 0x26BF, 0x537F, 0x3967, 0x4E09, 0x6AAE, 0x7F54, 0x7FD9, 0x69F6, 0x7EFE, 0x267A, 0x7FFF
	.2byte 0x0000, 0x3DF2, 0x4216, 0x2E3B, 0x329E, 0x431F, 0x63BF, 0x524F, 0x5EB0, 0x7314, 0x7F98, 0x7FDB, 0x72B9, 0x7F5E, 0x42FC, 0x7FFF
	.2byte 0x0000, 0x5EF9, 0x631B, 0x571D, 0x5B3F, 0x639F, 0x73DF, 0x6B37, 0x6F58, 0x7B9A, 0x7FDC, 0x7FFD, 0x7B5C, 0x7FBF, 0x637E, 0x7FFF
	.2byte 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript129
gApZ2Na1_PlttAnimScript129:
	.4byte gApZ2Na1_PlttAnimScript129_0
gApZ2Na1_PlttAnimScript129_0:
	.byte 3, 60
	.byte 2, 8
	.byte 1, 8
	.byte 0, 60
	.byte 0, 255
	.balign 4, 0

.global gApZ2Na1_PlttAnim130
gApZ2Na1_PlttAnim130: @ Zero 2's palette animation 130
	.byte 4, 0, 15, 0
	.2byte 0x0000, 0x537F, 0x1CEB, 0x2531, 0x0539, 0x0DDE, 0x26BF, 0x18E7, 0x3967, 0x4E09, 0x6AAE, 0x7F54, 0x296E, 0x29D4, 0x3A9A, 0x6F7B
	.2byte 0x0000, 0x63BF, 0x3DF2, 0x4216, 0x2E3B, 0x329E, 0x431F, 0x3DEF, 0x524F, 0x5EB0, 0x7314, 0x7F98, 0x4654, 0x4698, 0x531C, 0x739C
	.2byte 0x0000, 0x73DF, 0x5EF9, 0x631B, 0x571D, 0x5B3F, 0x639F, 0x5EF7, 0x6B37, 0x6F58, 0x7B9A, 0x7FDC, 0x631A, 0x635C, 0x6B9E, 0x7BDE
	.2byte 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript130
gApZ2Na1_PlttAnimScript130:
	.4byte gApZ2Na1_PlttAnimScript130_0
gApZ2Na1_PlttAnimScript130_0:
	.byte 3, 60
	.byte 2, 8
	.byte 1, 8
	.byte 0, 60
	.byte 0, 255
	.balign 4, 0

.global gApZ2Na1_PlttAnim131
gApZ2Na1_PlttAnim131: @ Zero 2's palette animation 131
	.byte 4, 144, 159, 0
	.2byte 0x0000, 0x1CEB, 0x2531, 0x0539, 0x0DDE, 0x537F, 0x18E7, 0x3967, 0x4E09, 0x6AAE, 0x7F54, 0x7FD9, 0x296E, 0x29D4, 0x3A9A, 0x7FFF
	.2byte 0x0000, 0x3DF2, 0x4636, 0x2E3B, 0x369F, 0x63BF, 0x3DEF, 0x524F, 0x5EB1, 0x7334, 0x7F98, 0x7FFB, 0x4654, 0x4698, 0x531C, 0x7FFF
	.2byte 0x0000, 0x5EF9, 0x631B, 0x571D, 0x5B5F, 0x73DF, 0x5EF7, 0x6B37, 0x6F58, 0x7B9A, 0x7FDC, 0x7FFD, 0x633A, 0x635C, 0x6B9E, 0x7FFF
	.2byte 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF
	.balign 4, 0
.global gApZ2Na1_PlttAnimScript131
gApZ2Na1_PlttAnimScript131:
	.4byte gApZ2Na1_PlttAnimScript131_0
gApZ2Na1_PlttAnimScript131_0:
	.byte 3, 60
	.byte 2, 8
	.byte 1, 8
	.byte 0, 60
	.byte 0, 255
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Na1_Metatiles
gApZ2Na1_Metatiles:
	.incbin "data/ap/z2_na1/metatile.bin"
	.balign 4, 0

.global gApZ2Na1_Attrs
gApZ2Na1_Attrs:
	.incbin "data/ap/z2_na1/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Na1_Chunks
gApZ2Na1_Chunks:
	.incbin "data/ap/z2_na1/screen.bin"
	.balign 4, 0

.global gApZ2Na1_TankMap
gApZ2Na1_TankMap:
	.incbin "data/ap/z2_na1/tank_map.bin"

.global gApZ2Na1_LavaMap
gApZ2Na1_LavaMap:
	.incbin "data/ap/z2_na1/lava_map.bin"

gApZ2Na1_Ts0_Tiles:
	.incbin "data/ap/z2_na1/tileset0.4bpp"
	.balign 4, 0
gApZ2Na1_Ts0_Pal:
	.incbin "data/ap/z2_na1/tileset0.gbapal"
	.balign 4, 0

gApZ2Na1_Ts1_Tiles:
	.incbin "data/ap/z2_na1/tileset1.4bpp"
	.balign 4, 0
gApZ2Na1_Ts1_Pal:
	.incbin "data/ap/z2_na1/tileset1.gbapal"
	.balign 4, 0

gApZ2Na1_Ts2_Tiles:
	.incbin "data/ap/z2_na1/tileset2.4bpp.lz"
	.balign 4, 0
gApZ2Na1_Ts2_Pal:
	.incbin "data/ap/z2_na1/tileset2.gbapal"
	.balign 4, 0

gApZ2Na1_Ts3_Tiles:
	.incbin "data/ap/z2_na1/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Na1_Ts3_Pal:
	.incbin "data/ap/z2_na1/tileset3.gbapal"
	.balign 4, 0

gApZ2Na1_Ts4_Tiles:
	.incbin "data/ap/z2_na1/tileset4.4bpp.lz"
	.balign 4, 0
gApZ2Na1_Ts4_Pal:
	.incbin "data/ap/z2_na1/tileset4.gbapal"
	.balign 4, 0

gApZ2Na1_Anim0_Tiles:
	.incbin "data/ap/z2_na1/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Na1_Anim0_Pal:
	.incbin "data/ap/z2_na1/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Na1_Anim1_Tiles:
	.incbin "data/ap/z2_na1/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Na1_Anim1_Pal:
	.incbin "data/ap/z2_na1/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Na1_Anim2_Tiles:
	.incbin "data/ap/z2_na1/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Na1_Anim2_Pal:
	.incbin "data/ap/z2_na1/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Na1_Anim3_Tiles:
	.incbin "data/ap/z2_na1/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Na1_Anim3_Pal:
	.incbin "data/ap/z2_na1/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Na1_Anim4_Tiles:
	.incbin "data/ap/z2_na1/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Na1_Anim4_Pal:
	.incbin "data/ap/z2_na1/tile_anim4.gbapal"
	.balign 4, 0
