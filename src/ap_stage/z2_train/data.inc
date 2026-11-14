@ Zero 2's TRAIN AKA Train

.balign 4

.global gApZ2Train_Terrain
gApZ2Train_Terrain:
	.4byte gApZ2Train_Metatiles-.
	.4byte gApZ2Train_Attrs-(.-4)
	.4byte gApZ2Train_Chunks-(.-8)

.global gApZ2Train_Tilesets
gApZ2Train_Tilesets: @ ColorGraphic[4]

gApZ2Train_Ts0:
	.4byte gApZ2Train_Ts0_Tiles-.
	.4byte 6216 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Train_Ts0_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Train_Ts1:
	.4byte gApZ2Train_Ts1_Tiles-.
	.4byte 9264 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Train_Ts1_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Train_Ts2:
	.4byte gApZ2Train_Ts2_Tiles-.
	.4byte 11796 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Train_Ts2_Pal-.
		.2byte 128
		.byte 0, 2

gApZ2Train_Ts3:
	.4byte gApZ2Train_Ts3_Tiles-.
	.4byte 7020 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Train_Ts3_Pal-.
		.2byte 160
		.byte 0, 9

.global gApZ2Train_TileAnim
gApZ2Train_TileAnim: @ ColorGraphic[4]

gApZ2Train_Anim0:
	.4byte gApZ2Train_Anim0_Tiles-.
	.4byte 128 | (909 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Train_Anim0_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Train_Anim1:
	.4byte gApZ2Train_Anim1_Tiles-.
	.4byte 128 | (909 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Train_Anim1_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Train_Anim2:
	.4byte gApZ2Train_Anim2_Tiles-.
	.4byte 128 | (909 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Train_Anim2_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Train_Anim3:
	.4byte gApZ2Train_Anim3_Tiles-.
	.4byte 128 | (909 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Train_Anim3_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Train_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 1072*PX, 368*PX
	.4byte DIR_RIGHT

gApZ2Train_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 960*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Train_Script
gApZ2Train_Script:
	spawn 0, gApZ2Train_Zero
	reset_camera gApZ2Train_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_TRAIN
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x140a
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Train_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 1072*PX, 368*PX
	.4byte DIR_RIGHT

gApZ2Train_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 960*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Train_AgainScript
gApZ2Train_AgainScript:
	spawn 0, gApZ2Train_AgainZero
	reset_camera gApZ2Train_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_TRAIN
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Train_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 8272*PX, 320*PX
	.4byte DIR_RIGHT

gApZ2Train_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 8160*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Train_CheckpointScript
gApZ2Train_CheckpointScript:
	spawn 0, gApZ2Train_CheckpointZero
	reset_camera gApZ2Train_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_TRAIN
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Train_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 9600*PX, 320*PX
	.4byte DIR_RIGHT

gApZ2Train_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 9408*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Train_BossRestartScript
gApZ2Train_BossRestartScript:
	spawn 0, gApZ2Train_BossRestartZero
	reset_camera gApZ2Train_BossRestartCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_TRAIN
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

@ Clear scene skip lands here
.global gApZ2Train_ResultScript
gApZ2Train_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Train_Supplies:
	.byte ENTITY_SOLID, SOLID_Z2_SUPPLIES, 0, 0
	.4byte 7952*PX, 448*PX
	.4byte DIR_LEFT

gApZ2Train_SuppliesCamera:
	.byte 6, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 7824*PX, 8064*PX, 0*PX, 10240*PX

@ Zero 2's scripts 2 and 3
.global gApZ2Train_MidBoss0Script
gApZ2Train_MidBoss0Script:
	spawn 1, gApZ2Train_Supplies
	lock
	force 0, 0, 0
	turn_right 0
	reset_camera gApZ2Train_SuppliesCamera
	wait 60
	emotion_bubble 0, 16, -40, 0
	message 1, 0, 0x140d
	wait_msgbox_end
	play_bgm BGM_Z2_OPENING_BOSS
	entityflag 1, 0, TRUE
	force 1, 0, 0
	release
	resume 1
	end

.global gApZ2Train_MidBoss0ClearScript
gApZ2Train_MidBoss0ClearScript:
	detach_entity 1
	adjust_camera 0, 0, 6
	adjust_camera 12, 0, 0x3C0000
	adjust_camera 1, 0, 4
	play_bgm BGM_Z2_TRAIN
	end

gApZ2Train_RoomZero:
	.4byte 336*PX, 380*PX

gApZ2Train_PanterCamera:
	.byte 1, 8, 0, 0
	.4byte 420*PX, 336*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 240*PX, 592*PX, 256*PX, 640*PX

gApZ2Train_FrontCar:
	.byte ENTITY_SOLID, SOLID_Z2_CAR_FRONT, 55, 0
	.4byte 0*PX, 0*PX
	.4byte DIR_LEFT

gApZ2Train_RearCar:
	.byte ENTITY_SOLID, SOLID_Z2_CAR_FRONT, 55, 1
	.4byte 0*PX, 0*PX
	.4byte DIR_LEFT

gApZ2Train_Panter:
	.byte ENTITY_BOSS, BOSS_Z2_PANTER, 0, 0
	.4byte 504*PX, 392*PX
	.4byte DIR_LEFT

@ Zero 2's script 6, the line once a visit
.global gApZ2Train_BossScript
gApZ2Train_BossScript:
	stop_bgm
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 60
	start_transition 2
	wait_transition_end
	force 1, 0, 0
	play_bgm BGM_GUARDER_ROOM
	wait 58
	change_entity_val 0, 0, gApZ2Train_RoomZero
	reset_camera gApZ2Train_PanterCamera
	wait 2
	spawn 3, gApZ2Train_FrontCar
	spawn 4, gApZ2Train_RearCar
	wait 1
	spawn 1, gApZ2Train_Panter
	wait 1
	play_se SE_Z2_RAPTOR_SWOOP
	start_transition 1
	wait_transition_end
	message 1, 0, 0x140b
	wait_msgbox_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	adjust_camera 2, 0, 0
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Train_BossReturnScript
gApZ2Train_BossReturnScript:
	stop_bgm
	lock
	force 0, 0, 0
	change_entity_val 0, 2, 1
	emotion_bubble 0, 16, -40, 0
	wait 60
	start_transition 2
	wait_transition_end
	force 1, 0, 0
	play_bgm BGM_GUARDER_ROOM
	wait 58
	change_entity_val 0, 0, gApZ2Train_RoomZero
	reset_camera gApZ2Train_PanterCamera
	wait 2
	spawn 3, gApZ2Train_FrontCar
	spawn 4, gApZ2Train_RearCar
	wait 1
	spawn 1, gApZ2Train_Panter
	wait 1
	play_se SE_Z2_RAPTOR_SWOOP
	start_transition 1
	wait_transition_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	adjust_camera 2, 0, 0
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 7
.global gApZ2Train_ClearScript
gApZ2Train_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	force 8, 0, 0
	message 1, 0, 0x140c
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	play_se SE_UNK_c8
	fadeout_se 90, SE_Z2_TRAIN_RUMBLE
	force 4, 0, 0
	wait 8
	force 5, 0, 0
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	destroy 3
	destroy 4
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

.global gApZ2Train_PlttAnim62
gApZ2Train_PlttAnim62: @ Zero 2's palette animation 62
	.byte 8, 183, 191, 0
	.2byte 0x2190, 0x73FF, 0x5F7B, 0x6F11, 0x637C, 0x6FFF, 0x5B5A, 0x5B5A, 0x2E73
	.2byte 0x2DF3, 0x5739, 0x5FFD, 0x628E, 0x5719, 0x67BD, 0x6FFF, 0x6FFF, 0x15AD
	.2byte 0x3635, 0x3A53, 0x5F7B, 0x6F11, 0x46B5, 0x5B5A, 0x5B5A, 0x3E55, 0x2E73
	.2byte 0x3E77, 0x5739, 0x5319, 0x7794, 0x5719, 0x5318, 0x46B5, 0x5B5A, 0x19CE
	.2byte 0x3E77, 0x73FF, 0x46B6, 0x7FF7, 0x637C, 0x46B5, 0x5B5A, 0x6FFF, 0x2E73
	.2byte 0x3E77, 0x5739, 0x3A53, 0x7FF7, 0x6FDF, 0x5318, 0x6FFF, 0x5B5A, 0x19CE
	.2byte 0x3635, 0x3A53, 0x46B6, 0x7FF7, 0x6FDF, 0x5B5A, 0x5B5A, 0x46B5, 0x2E73
	.2byte 0x2DF3, 0x5739, 0x5319, 0x7794, 0x6FDF, 0x67BD, 0x46B5, 0x5B5A, 0x19CE
	.balign 4, 0
.global gApZ2Train_PlttAnimScript62
gApZ2Train_PlttAnimScript62:
	.4byte gApZ2Train_PlttAnimScript62_0
gApZ2Train_PlttAnimScript62_0:
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

.global gApZ2Train_PlttAnim63
gApZ2Train_PlttAnim63: @ Zero 2's palette animation 63
	.byte 8, 215, 223, 0
	.2byte 0x2190, 0x73FF, 0x5F7B, 0x6F11, 0x637C, 0x6FFF, 0x5B5A, 0x5B5A, 0x2E73
	.2byte 0x2DF3, 0x5739, 0x5FFD, 0x628E, 0x5719, 0x67BD, 0x6FFF, 0x6FFF, 0x15AD
	.2byte 0x3635, 0x3A53, 0x5F7B, 0x6F11, 0x46B5, 0x5B5A, 0x5B5A, 0x3E55, 0x2E73
	.2byte 0x3E77, 0x5739, 0x5319, 0x7794, 0x5719, 0x5318, 0x46B5, 0x5B5A, 0x19CE
	.2byte 0x3E77, 0x73FF, 0x46B6, 0x7FF7, 0x637C, 0x46B5, 0x5B5A, 0x6FFF, 0x2E73
	.2byte 0x3E77, 0x5739, 0x3A53, 0x7FF7, 0x6FDF, 0x5318, 0x6FFF, 0x5B5A, 0x19CE
	.2byte 0x3635, 0x3A53, 0x46B6, 0x7FF7, 0x6FDF, 0x5B5A, 0x5B5A, 0x46B5, 0x2E73
	.2byte 0x2DF3, 0x5739, 0x5319, 0x7794, 0x6FDF, 0x67BD, 0x46B5, 0x5B5A, 0x19CE
	.balign 4, 0
.global gApZ2Train_PlttAnimScript63
gApZ2Train_PlttAnimScript63:
	.4byte gApZ2Train_PlttAnimScript63_0
gApZ2Train_PlttAnimScript63_0:
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

.global gApZ2Train_PlttAnim64
gApZ2Train_PlttAnim64: @ Zero 2's palette animation 64
	.byte 3, 206, 207, 0
	.2byte 0x3718, 0x3673
	.2byte 0x2EB5, 0x4F39
	.2byte 0x2231, 0x67FF
	.balign 4, 0
.global gApZ2Train_PlttAnimScript64
gApZ2Train_PlttAnimScript64:
	.4byte gApZ2Train_PlttAnimScript64_0
gApZ2Train_PlttAnimScript64_0:
	.byte 0, 4
	.byte 1, 4
	.byte 2, 4
	.byte 1, 4
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Train_Metatiles
gApZ2Train_Metatiles:
	.incbin "data/ap/z2_train/metatile.bin"
	.balign 4, 0

.global gApZ2Train_Attrs
gApZ2Train_Attrs:
	.incbin "data/ap/z2_train/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Train_Chunks
gApZ2Train_Chunks:
	.incbin "data/ap/z2_train/screen.bin"
	.balign 4, 0

.global gApZ2MugshotPanter
gApZ2MugshotPanter:
	.incbin "data/ap/z2_train/mugshot_panter.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotPanter_Pal
gApZ2MugshotPanter_Pal:
	.incbin "data/ap/z2_train/mugshot_panter.gbapal"
	.balign 4, 0

.global gApZ2Train_FrontCarMap
gApZ2Train_FrontCarMap:
	.incbin "data/ap/z2_train/frontcar_map.bin"

.global gApZ2Train_RearCarMap
gApZ2Train_RearCarMap:
	.incbin "data/ap/z2_train/rearcar_map.bin"

.global gApZ2Train_Sky0Map
gApZ2Train_Sky0Map:
	.incbin "data/ap/z2_train/sky0_map.bin"

.global gApZ2Train_Sky1Map
gApZ2Train_Sky1Map:
	.incbin "data/ap/z2_train/sky1_map.bin"

.global gApZ2Train_Near0Map
gApZ2Train_Near0Map:
	.incbin "data/ap/z2_train/near0_map.bin"

.global gApZ2Train_Near1Map
gApZ2Train_Near1Map:
	.incbin "data/ap/z2_train/near1_map.bin"

.global gApZ2Train_NightMap
gApZ2Train_NightMap:
	.incbin "data/ap/z2_train/night_map.bin"

gApZ2Train_Ts0_Tiles:
	.incbin "data/ap/z2_train/tileset0.4bpp.lz"
	.balign 4, 0
gApZ2Train_Ts0_Pal:
	.incbin "data/ap/z2_train/tileset0.gbapal"
	.balign 4, 0

gApZ2Train_Ts1_Tiles:
	.incbin "data/ap/z2_train/tileset1.4bpp.lz"
	.balign 4, 0
gApZ2Train_Ts1_Pal:
	.incbin "data/ap/z2_train/tileset1.gbapal"
	.balign 4, 0

gApZ2Train_Ts2_Tiles:
	.incbin "data/ap/z2_train/tileset2.4bpp.lz"
	.balign 4, 0
gApZ2Train_Ts2_Pal:
	.incbin "data/ap/z2_train/tileset2.gbapal"
	.balign 4, 0

gApZ2Train_Ts3_Tiles:
	.incbin "data/ap/z2_train/tileset3.4bpp.lz"
	.balign 4, 0
gApZ2Train_Ts3_Pal:
	.incbin "data/ap/z2_train/tileset3.gbapal"
	.balign 4, 0

gApZ2Train_Anim0_Tiles:
	.incbin "data/ap/z2_train/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Train_Anim0_Pal:
	.incbin "data/ap/z2_train/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Train_Anim1_Tiles:
	.incbin "data/ap/z2_train/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Train_Anim1_Pal:
	.incbin "data/ap/z2_train/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Train_Anim2_Tiles:
	.incbin "data/ap/z2_train/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Train_Anim2_Pal:
	.incbin "data/ap/z2_train/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Train_Anim3_Tiles:
	.incbin "data/ap/z2_train/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Train_Anim3_Pal:
	.incbin "data/ap/z2_train/tile_anim3.gbapal"
	.balign 4, 0
