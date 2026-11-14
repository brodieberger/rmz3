@ Zero 2's PLANT2 AKA Shuttle Factory

.balign 4

.global gApZ2Plant2_Terrain
gApZ2Plant2_Terrain:
	.4byte gApZ2Plant2_Metatiles-.
	.4byte gApZ2Plant2_Attrs-(.-4)
	.4byte gApZ2Plant2_Chunks-(.-8)

.global gApZ2Plant2_Tilesets
gApZ2Plant2_Tilesets: @ ColorGraphic[8]

gApZ2Plant2_Ts0:
	.4byte gApZ2Plant2_Ts0_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts0_Pal-.
		.2byte 192
		.byte 0, 2

gApZ2Plant2_Ts1:
	.4byte gApZ2Plant2_Ts1_Tiles-.
	.4byte 10688 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts1_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Plant2_Ts2:
	.4byte gApZ2Plant2_Ts2_Tiles-.
	.4byte 16192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts2_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Plant2_Ts3:
	.4byte gApZ2Plant2_Ts3_Tiles-.
	.4byte 16320 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts3_Pal-.
		.2byte 192
		.byte 0, 2

gApZ2Plant2_Ts4:
	.4byte gApZ2Plant2_Ts4_Tiles-.
	.4byte 12288 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts4_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Plant2_Ts5:
	.4byte gApZ2Plant2_Ts5_Tiles-.
	.4byte 16384 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts5_Pal-.
		.2byte 224
		.byte 0, 9

gApZ2Plant2_Ts6:
	.4byte gApZ2Plant2_Ts6_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts6_Pal-.
		.2byte 160
		.byte 0, 2

gApZ2Plant2_Ts7:
	.4byte gApZ2Plant2_Ts7_Tiles-.
	.4byte 9664 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Ts7_Pal-.
		.2byte 192
		.byte 0, 9

.global gApZ2Plant2_TileAnim
gApZ2Plant2_TileAnim: @ ColorGraphic[10]

gApZ2Plant2_Anim0:
	.4byte gApZ2Plant2_Anim0_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim0_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim1:
	.4byte gApZ2Plant2_Anim1_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim1_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim2:
	.4byte gApZ2Plant2_Anim2_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim2_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim3:
	.4byte gApZ2Plant2_Anim3_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim3_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim4:
	.4byte gApZ2Plant2_Anim4_Tiles-.
	.4byte 384 | (497 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim4_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim5:
	.4byte gApZ2Plant2_Anim5_Tiles-.
	.4byte 128 | (960 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim5_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim6:
	.4byte gApZ2Plant2_Anim6_Tiles-.
	.4byte 128 | (960 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim6_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim7:
	.4byte gApZ2Plant2_Anim7_Tiles-.
	.4byte 128 | (960 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim7_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim8:
	.4byte gApZ2Plant2_Anim8_Tiles-.
	.4byte 128 | (960 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim8_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Anim9:
	.4byte gApZ2Plant2_Anim9_Tiles-.
	.4byte 128 | (960 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Plant2_Anim9_Pal-.
		.2byte 0
		.byte 0, 0

gApZ2Plant2_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 768*PX
	.4byte DIR_RIGHT

gApZ2Plant2_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant2_Script
gApZ2Plant2_Script:
	spawn 0, gApZ2Plant2_Zero
	reset_camera gApZ2Plant2_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_SHUTTLE_FACTORY
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x144a
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant2_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 768*PX
	.4byte DIR_RIGHT

gApZ2Plant2_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant2_AgainScript
gApZ2Plant2_AgainScript:
	spawn 0, gApZ2Plant2_AgainZero
	reset_camera gApZ2Plant2_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_SHUTTLE_FACTORY
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant2_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 6352*PX, 608*PX
	.4byte DIR_RIGHT

gApZ2Plant2_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant2_CheckpointScript
gApZ2Plant2_CheckpointScript:
	spawn 0, gApZ2Plant2_CheckpointZero
	reset_camera gApZ2Plant2_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_GUARDER_ROOM
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Plant2_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 6352*PX, 608*PX
	.4byte DIR_RIGHT

gApZ2Plant2_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Plant2_BossRestartScript
gApZ2Plant2_BossRestartScript:
	spawn 0, gApZ2Plant2_BossRestartZero
	reset_camera gApZ2Plant2_BossRestartCamera
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
.global gApZ2Plant2_ResultScript
gApZ2Plant2_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Plant2_Fefnir:
	.byte ENTITY_BOSS, BOSS_Z2_FEFNIR_FOOT, 0, 0
	.4byte 6512*PX, 480*PX
	.4byte DIR_LEFT

gApZ2Plant2_BossCamera: @ Zero 2's, 0x0832cf20
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 6512*PX, 15360*PX, 0*PX, 10240*PX

@ Zero 2's script 3, the line once a visit
.global gApZ2Plant2_BossScript
gApZ2Plant2_BossScript:
	spawn 1, gApZ2Plant2_Fefnir
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	wait 20
	play_bgm BGM_X
	lock
	reset_camera gApZ2Plant2_BossCamera
	wait 60
	cutscene_start CS_UNK_48
	message 1, 0, 0x144b
	wait_msgbox_end
	cutscene_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Plant2_BossReturnScript
gApZ2Plant2_BossReturnScript:
	spawn 1, gApZ2Plant2_Fefnir
	stop_bgm
	forcekeyinput DPAD_RIGHT
	pause
	wait 20
	play_bgm BGM_X
	lock
	reset_camera gApZ2Plant2_BossCamera
	wait 60
	entityflag 1, 0, TRUE
	stop_bgm
	wait 60
	warning_indicator
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 4
.global gApZ2Plant2_ClearScript
gApZ2Plant2_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	wait 30
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 2
	adjust_camera 2, 0, 1
	wait 90
	play_bgm BGM_Z2_GUARDIAN_RETREAT
	wait 60
	adjust_camera 0, 0, 1
	message 1, 0, 0x144c
	wait_msgbox_end
	entityflag 1, 7, TRUE
	cmd08_wait_set 1
	adjust_camera 0, 0, 4
	adjust_camera 1, 0, 4
	adjust_camera 2, 0, 0
	wait 60
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
	cutscene_end
	start_result_screen
	wait_for_result_screen_end
	load_graphic_primitive
	destroy 0
	wait 2
	end

.global gApZ2Plant2_PlttAnim91
gApZ2Plant2_PlttAnim91: @ Zero 2's palette animation 91
	.byte 1, 0, 15, 0
	.2byte 0x0000, 0x017F, 0x22BF, 0x47FE, 0x63FE, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	.balign 4, 0
.global gApZ2Plant2_PlttAnimScript91
gApZ2Plant2_PlttAnimScript91:
	.4byte gApZ2Plant2_PlttAnimScript91_0
gApZ2Plant2_PlttAnimScript91_0:
	.byte 0, 1
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Plant2_Metatiles
gApZ2Plant2_Metatiles:
	.incbin "data/ap/z2_plant2/metatile.bin"
	.balign 4, 0

.global gApZ2Plant2_Attrs
gApZ2Plant2_Attrs:
	.incbin "data/ap/z2_plant2/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Plant2_Chunks
gApZ2Plant2_Chunks:
	.incbin "data/ap/z2_plant2/screen.bin"
	.balign 4, 0

gApZ2Plant2_Ts0_Tiles:
	.incbin "data/ap/z2_plant2/tileset0.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts0_Pal:
	.incbin "data/ap/z2_plant2/tileset0.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts1_Tiles:
	.incbin "data/ap/z2_plant2/tileset1.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts1_Pal:
	.incbin "data/ap/z2_plant2/tileset1.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts2_Tiles:
	.incbin "data/ap/z2_plant2/tileset2.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts2_Pal:
	.incbin "data/ap/z2_plant2/tileset2.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts3_Tiles:
	.incbin "data/ap/z2_plant2/tileset3.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts3_Pal:
	.incbin "data/ap/z2_plant2/tileset3.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts4_Tiles:
	.incbin "data/ap/z2_plant2/tileset4.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts4_Pal:
	.incbin "data/ap/z2_plant2/tileset4.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts5_Tiles:
	.incbin "data/ap/z2_plant2/tileset5.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts5_Pal:
	.incbin "data/ap/z2_plant2/tileset5.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts6_Tiles:
	.incbin "data/ap/z2_plant2/tileset6.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts6_Pal:
	.incbin "data/ap/z2_plant2/tileset6.gbapal"
	.balign 4, 0

gApZ2Plant2_Ts7_Tiles:
	.incbin "data/ap/z2_plant2/tileset7.4bpp"
	.balign 4, 0
gApZ2Plant2_Ts7_Pal:
	.incbin "data/ap/z2_plant2/tileset7.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim0_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim0.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim0_Pal:
	.incbin "data/ap/z2_plant2/tile_anim0.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim1_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim1.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim1_Pal:
	.incbin "data/ap/z2_plant2/tile_anim1.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim2_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim2.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim2_Pal:
	.incbin "data/ap/z2_plant2/tile_anim2.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim3_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim3.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim3_Pal:
	.incbin "data/ap/z2_plant2/tile_anim3.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim4_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim4.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim4_Pal:
	.incbin "data/ap/z2_plant2/tile_anim4.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim5_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim5.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim5_Pal:
	.incbin "data/ap/z2_plant2/tile_anim5.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim6_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim6.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim6_Pal:
	.incbin "data/ap/z2_plant2/tile_anim6.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim7_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim7.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim7_Pal:
	.incbin "data/ap/z2_plant2/tile_anim7.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim8_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim8.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim8_Pal:
	.incbin "data/ap/z2_plant2/tile_anim8.gbapal"
	.balign 4, 0

gApZ2Plant2_Anim9_Tiles:
	.incbin "data/ap/z2_plant2/tile_anim9.4bpp"
	.balign 4, 0
gApZ2Plant2_Anim9_Pal:
	.incbin "data/ap/z2_plant2/tile_anim9.gbapal"
	.balign 4, 0
