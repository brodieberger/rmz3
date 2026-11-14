@ Zero 2's ICE AKA Computer Zone

.balign 4

.global gApZ2Ice_Terrain
gApZ2Ice_Terrain:
	.4byte gApZ2Ice_Metatiles-.
	.4byte gApZ2Ice_Attrs-(.-4)
	.4byte gApZ2Ice_Chunks-(.-8)

.global gApZ2Ice_Tilesets
gApZ2Ice_Tilesets: @ ColorGraphic[6]

gApZ2Ice_Ts0:
	.4byte gApZ2Ice_Ts0_Tiles-.
	.4byte 16320 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice_Ts0_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice_Ts1:
	.4byte gApZ2Ice_Ts1_Tiles-.
	.4byte 14208 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice_Ts1_Pal-.
		.2byte 64
		.byte 0, 9

gApZ2Ice_Ts2:
	.4byte gApZ2Ice_Ts2_Tiles-.
	.4byte 16384 | (0 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice_Ts2_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice_Ts3:
	.4byte gApZ2Ice_Ts3_Tiles-.
	.4byte 8192 | (512 << 22)
	.2byte 256, BPP4
		.4byte gApZ2Ice_Ts3_Pal-.
		.2byte 160
		.byte 0, 9

gApZ2Ice_Ts4:
	.4byte gApZ2Ice_Ts4_Tiles-.
	.4byte 6912 | (512 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice_Ts4_Pal-.
		.2byte 192
		.byte 0, 9

gApZ2Ice_Ts5:
	.4byte gApZ2Ice_Ts5_Tiles-.
	.4byte 6104 | (0 << 22)
	.2byte 256, (LZ77 | BPP4)
		.4byte gApZ2Ice_Ts5_Pal-.
		.2byte 224
		.byte 0, 2

gApZ2Ice_Zero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1248*PX
	.4byte DIR_RIGHT

gApZ2Ice_Camera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice_Script
gApZ2Ice_Script:
	spawn 0, gApZ2Ice_Zero
	reset_camera gApZ2Ice_Camera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_COMPUTER_ZONE
	cutscene_start CS_UNK_48
	wait 90
	message 1, 0, 0x1403
	wait_msgbox_end
	cutscene_end
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice_AgainZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 352*PX, 1248*PX
	.4byte DIR_RIGHT

gApZ2Ice_AgainCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice_AgainScript
gApZ2Ice_AgainScript:
	spawn 0, gApZ2Ice_AgainZero
	reset_camera gApZ2Ice_AgainCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_COMPUTER_ZONE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice_CheckpointZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 7312*PX, 1376*PX
	.4byte DIR_RIGHT

gApZ2Ice_CheckpointCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice_CheckpointScript
gApZ2Ice_CheckpointScript:
	spawn 0, gApZ2Ice_CheckpointZero
	reset_camera gApZ2Ice_CheckpointCamera
	lock
	start_transition 9
	wait_transition_end
	play_bgm BGM_Z2_COMPUTER_ZONE
	indicator 1, 0, 0
	wait_indicator_end
	release
	resume 0
	end

gApZ2Ice_BossRestartZero:
	.byte PLAYER, ZERO, 0, 0
	.4byte 9232*PX, 464*PX
	.4byte DIR_RIGHT

gApZ2Ice_BossRestartCamera:
	.byte 6, 8, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, MAX_X, 0*PX, MAX_Y

.global gApZ2Ice_BossRestartScript
gApZ2Ice_BossRestartScript:
	spawn 0, gApZ2Ice_BossRestartZero
	reset_camera gApZ2Ice_BossRestartCamera
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
.global gApZ2Ice_ResultScript
gApZ2Ice_ResultScript:
	backdrop_color 0xFFFF
	start_result_screen
	wait_for_result_screen_end
	lockmenu
	end

gApZ2Ice_Frost:
	.byte ENTITY_BOSS, BOSS_Z2_FROST_GOLEM, 0, 0
	.4byte 6360*PX, 1248*PX
	.4byte DIR_LEFT

gApZ2Ice_FrostCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 6360*PX, 6720*PX, 0*PX, 1328*PX

gApZ2Ice_GolemElf:
	.byte ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 19, 0
	.4byte 6608*PX, 1248*PX
	.4byte DIR_RIGHT

@ Zero 2's scripts 2 and 3
.global gApZ2Ice_MidBoss0Script
gApZ2Ice_MidBoss0Script:
	lock
	pause
	spawn 1, gApZ2Ice_Frost
	gameflag FLAG_2, TRUE
	forcekeyinput DPAD_RIGHT
	wait 112
	lock
	emotion_bubble 0, 16, -40, 0
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 6540*PX
	set_camera_target_y 1248*PX
	entityflag 1, 0, TRUE
	wait 90
	force 1, 0, 0
	release
	reset_camera gApZ2Ice_FrostCamera
	resume 1
	end

.global gApZ2Ice_MidBoss0ClearScript
gApZ2Ice_MidBoss0ClearScript:
	cmd08_wait_set 1
	play_se SE_UNK_c8
	start_transition 6
	wait_transition_end
	wait 32
	destroy 1
	adjust_camera 0, 0, 3
	adjust_camera 1, 0, 4
	spawn 9, gApZ2Ice_GolemElf
	start_transition 5
	wait_transition_end
	gameflag FLAG_2, FALSE
	end

gApZ2Ice_Bear:
	.byte ENTITY_BOSS, BOSS_Z2_BEAR, 0, 0
	.4byte 9584*PX, 480*PX
	.4byte DIR_LEFT

gApZ2Ice_BearCamera:
	.byte 4, 4, 0, 0
	.4byte 0*PX, 0*PX
	.4byte 0*PX, 0*PX
	.2byte 0x0, 0x0, 0x0, 0x0
	.4byte 0*PX, 9712*PX, 0*PX, 10240*PX

@ Zero 2's script 6, the line once a visit
.global gApZ2Ice_BossScript
gApZ2Ice_BossScript:
	spawn 1, gApZ2Ice_Bear
	lock
	pause
	forcekeyinput DPAD_RIGHT
	wait 32
	force 0, 0, 0
	lock
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 9520*PX
	wait 120
	message 1, 0, 0x1404
	wait_msgbox_end
	entityflag 1, 0, TRUE
	stop_bgm
	wait 120
	warning_indicator
	reset_camera gApZ2Ice_BearCamera
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

.global gApZ2Ice_BossReturnScript
gApZ2Ice_BossReturnScript:
	spawn 1, gApZ2Ice_Bear
	lock
	pause
	forcekeyinput DPAD_RIGHT
	wait 32
	force 0, 0, 0
	lock
	change_camera_mode 1
	set_chase_mode 2
	set_camera_target_x 9520*PX
	wait 120
	entityflag 1, 0, TRUE
	stop_bgm
	wait 120
	warning_indicator
	reset_camera gApZ2Ice_BearCamera
	wait_indicator_end
	force 1, 0, 0
	release
	play_bgm BGM_Z2_HARPUIA
	resume 1
	end

@ Zero 2's script 7
.global gApZ2Ice_ClearScript
gApZ2Ice_ClearScript:
	forcekeyinput 0xFFFF
	stop_bgm
	wait 1
	lock
	cutscene_start CS_UNK_48
	message 1, 0, 0x1405
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

.global gApZ2Ice_PlttAnim85
gApZ2Ice_PlttAnim85: @ Zero 2's palette animation 85
	.byte 8, 182, 191, 0
	.2byte 0x1144, 0x19A5, 0x1E27, 0x26A8, 0x332B, 0x3BCD, 0x6BF7, 0x4B77, 0x2AAD, 0x1E27
	.2byte 0x1124, 0x1585, 0x1E06, 0x2688, 0x2F2B, 0x3BCD, 0x67F7, 0x3B10, 0x3714, 0x224C
	.2byte 0x0D03, 0x1584, 0x19E6, 0x2287, 0x2F0B, 0x37AC, 0x67D6, 0x26A8, 0x2AAD, 0x2290
	.2byte 0x0D03, 0x1164, 0x19C5, 0x2267, 0x2F0B, 0x37AC, 0x63D6, 0x3710, 0x2267, 0x224C
	.2byte 0x08E2, 0x1143, 0x15C5, 0x1E46, 0x2EEB, 0x33AB, 0x63B5, 0x4B77, 0x2AAD, 0x1E27
	.2byte 0x0D03, 0x1164, 0x19C5, 0x2267, 0x2F0B, 0x37AC, 0x63D6, 0x3710, 0x3714, 0x224C
	.2byte 0x0D03, 0x1584, 0x19E6, 0x2287, 0x2F0B, 0x37AC, 0x67D6, 0x26A8, 0x2AAD, 0x2290
	.2byte 0x1124, 0x1585, 0x1E06, 0x2688, 0x2F2B, 0x3BCD, 0x67F7, 0x3710, 0x2267, 0x224C
	.balign 4, 0
.global gApZ2Ice_PlttAnimScript85
gApZ2Ice_PlttAnimScript85:
	.4byte gApZ2Ice_PlttAnimScript85_0
gApZ2Ice_PlttAnimScript85_0:
	.byte 0, 12
	.byte 1, 12
	.byte 2, 12
	.byte 3, 12
	.byte 4, 12
	.byte 5, 12
	.byte 6, 12
	.byte 7, 12
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice_PlttAnim86
gApZ2Ice_PlttAnim86: @ Zero 2's palette animation 86
	.byte 10, 58, 63, 0
	.2byte 0x18E4, 0x18E4, 0x18E4, 0x20E3, 0x7FFF, 0x18E4
	.2byte 0x18E4, 0x18E4, 0x20E3, 0x7FFF, 0x7779, 0x14C8
	.2byte 0x18E4, 0x20E3, 0x7FFF, 0x737A, 0x66D3, 0x10AC
	.2byte 0x20E3, 0x7FFF, 0x737A, 0x66D4, 0x562E, 0x0C71
	.2byte 0x7FFF, 0x737A, 0x66D4, 0x562E, 0x4988, 0x0855
	.2byte 0x737A, 0x66D4, 0x562E, 0x4988, 0x20E3, 0x0439
	.2byte 0x66D4, 0x562E, 0x4988, 0x20E3, 0x18E4, 0x0855
	.2byte 0x562E, 0x4988, 0x20E3, 0x18E4, 0x18E4, 0x0C71
	.2byte 0x4988, 0x20E3, 0x18E4, 0x18E4, 0x18E4, 0x10AC
	.2byte 0x20E3, 0x18E4, 0x18E4, 0x18E4, 0x18E4, 0x14C8
	.balign 4, 0
.global gApZ2Ice_PlttAnimScript86
gApZ2Ice_PlttAnimScript86:
	.4byte gApZ2Ice_PlttAnimScript86_0
gApZ2Ice_PlttAnimScript86_0:
	.byte 0, 3
	.byte 1, 4
	.byte 2, 5
	.byte 3, 6
	.byte 4, 7
	.byte 5, 8
	.byte 6, 9
	.byte 7, 10
	.byte 8, 11
	.byte 9, 20
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice_PlttAnim87
gApZ2Ice_PlttAnim87: @ Zero 2's palette animation 87
	.byte 6, 221, 223, 0
	.2byte 0x53D9, 0x37D8, 0x1FB3
	.2byte 0x3BD5, 0x4FDE, 0x3B99
	.2byte 0x1FD0, 0x37D8, 0x537F
	.2byte 0x03CC, 0x1BD2, 0x3B99
	.2byte 0x1FD0, 0x03CC, 0x1FB3
	.2byte 0x3BD5, 0x1BD2, 0x03CC
	.balign 4, 0
.global gApZ2Ice_PlttAnimScript87
gApZ2Ice_PlttAnimScript87:
	.4byte gApZ2Ice_PlttAnimScript87_0
gApZ2Ice_PlttAnimScript87_0:
	.byte 0, 14
	.byte 1, 14
	.byte 2, 14
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice_PlttAnim88
gApZ2Ice_PlttAnim88: @ Zero 2's palette animation 88
	.byte 10, 215, 239, 0
	.2byte 0x21A2, 0x2E02, 0x32A3, 0x21A2, 0x21A2, 0x21A2, 0x21A2, 0x21A2, 0x21A2, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3222, 0x3AE3, 0x3222, 0x3222, 0x4746, 0x0000, 0x21A2, 0x21A2, 0x21A2, 0x21A2, 0x21A2
	.2byte 0x21A2, 0x3263, 0x3F04, 0x21A2, 0x21A2, 0x21A2, 0x21A2, 0x25E3, 0x25C2, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x4746, 0x3EE5, 0x0000, 0x3263, 0x21A2, 0x21A2, 0x21A2, 0x21A2
	.2byte 0x21A2, 0x2E02, 0x32A3, 0x21A2, 0x21A2, 0x2A03, 0x3263, 0x2A23, 0x25E3, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3222, 0x3AE3, 0x4746, 0x4746, 0x3684, 0x0000, 0x3F04, 0x3263, 0x21A2, 0x21A2, 0x21A2
	.2byte 0x21A2, 0x3263, 0x3F04, 0x21A2, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x2A03, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x4746, 0x2E23, 0x0000, 0x3F04, 0x3F04, 0x3263, 0x21A2, 0x21A2
	.2byte 0x21A2, 0x2E02, 0x32A3, 0x21A2, 0x21A2, 0x3263, 0x3F04, 0x3683, 0x2A03, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3222, 0x3AE3, 0x3222, 0x3222, 0x21A2, 0x0000, 0x3F04, 0x3F04, 0x3F04, 0x21A2, 0x21A2
	.2byte 0x21A2, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3AC3, 0x2E23, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x4746, 0x4746, 0x0000, 0x3F04, 0x3F04, 0x3F04, 0x3263, 0x21A2
	.2byte 0x21A2, 0x2E02, 0x32A3, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3F04, 0x2E43, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3222, 0x3AE3, 0x4746, 0x4746, 0x3EE5, 0x0000, 0x3F04, 0x3F04, 0x3F04, 0x3F04, 0x21A2
	.2byte 0x21A2, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3F04, 0x3263, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x4746, 0x3684, 0x0000, 0x3F04, 0x3F04, 0x3F04, 0x3F04, 0x3263
	.2byte 0x21A2, 0x2E02, 0x32A3, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3F04, 0x3263, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3222, 0x3AE3, 0x3222, 0x3222, 0x2E23, 0x0000, 0x3F04, 0x3F04, 0x3F04, 0x3F04, 0x3F04
	.2byte 0x21A2, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3263, 0x3F04, 0x3F04, 0x3263, 0x7E1F, 0x18A5, 0x2908, 0x3DCE, 0x21A2, 0x3263, 0x3F04, 0x3263, 0x4746, 0x21A2, 0x0000, 0x3263, 0x3263, 0x3263, 0x3263, 0x3263
	.balign 4, 0
.global gApZ2Ice_PlttAnimScript88
gApZ2Ice_PlttAnimScript88:
	.4byte gApZ2Ice_PlttAnimScript88_0
gApZ2Ice_PlttAnimScript88_0:
	.byte 0, 8
	.byte 1, 8
	.byte 2, 8
	.byte 3, 8
	.byte 4, 8
	.byte 5, 8
	.byte 6, 8
	.byte 7, 8
	.byte 8, 8
	.byte 9, 8
	.byte 0, 254
	.balign 4, 0

.global gApZ2Ice_PlttAnim89
gApZ2Ice_PlttAnim89: @ Zero 2's palette animation 89
	.byte 10, 63, 63, 0
	.2byte 0x18E4
	.2byte 0x14C8
	.2byte 0x10AC
	.2byte 0x0C71
	.2byte 0x0855
	.2byte 0x0439
	.2byte 0x0855
	.2byte 0x0C71
	.2byte 0x10AC
	.2byte 0x14C8
	.balign 4, 0
.global gApZ2Ice_PlttAnimScript89
gApZ2Ice_PlttAnimScript89:
	.4byte gApZ2Ice_PlttAnimScript89_0
gApZ2Ice_PlttAnimScript89_0:
	.byte 0, 3
	.byte 1, 4
	.byte 2, 5
	.byte 3, 6
	.byte 4, 7
	.byte 5, 8
	.byte 6, 9
	.byte 7, 10
	.byte 8, 11
	.byte 9, 20
	.byte 0, 254
	.balign 4, 0

@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global gApZ2Ice_Metatiles
gApZ2Ice_Metatiles:
	.incbin "data/ap/z2_ice/metatile.bin"
	.balign 4, 0

.global gApZ2Ice_Attrs
gApZ2Ice_Attrs:
	.incbin "data/ap/z2_ice/metatile_attr.bin"
	.balign 4, 0

.global gApZ2Ice_Chunks
gApZ2Ice_Chunks:
	.incbin "data/ap/z2_ice/screen.bin"
	.balign 4, 0

.global gApZ2MugshotBear
gApZ2MugshotBear:
	.incbin "data/ap/z2_ice/mugshot_bear.4bpp.lz"
	.balign 4, 0
.global gApZ2MugshotBear_Pal
gApZ2MugshotBear_Pal:
	.incbin "data/ap/z2_ice/mugshot_bear.gbapal"
	.balign 4, 0

gApZ2Ice_Ts0_Tiles:
	.incbin "data/ap/z2_ice/tileset0.4bpp"
	.balign 4, 0
gApZ2Ice_Ts0_Pal:
	.incbin "data/ap/z2_ice/tileset0.gbapal"
	.balign 4, 0

gApZ2Ice_Ts1_Tiles:
	.incbin "data/ap/z2_ice/tileset1.4bpp"
	.balign 4, 0
gApZ2Ice_Ts1_Pal:
	.incbin "data/ap/z2_ice/tileset1.gbapal"
	.balign 4, 0

gApZ2Ice_Ts2_Tiles:
	.incbin "data/ap/z2_ice/tileset2.4bpp"
	.balign 4, 0
gApZ2Ice_Ts2_Pal:
	.incbin "data/ap/z2_ice/tileset2.gbapal"
	.balign 4, 0

gApZ2Ice_Ts3_Tiles:
	.incbin "data/ap/z2_ice/tileset3.4bpp"
	.balign 4, 0
gApZ2Ice_Ts3_Pal:
	.incbin "data/ap/z2_ice/tileset3.gbapal"
	.balign 4, 0

gApZ2Ice_Ts4_Tiles:
	.incbin "data/ap/z2_ice/tileset4.4bpp.lz"
	.balign 4, 0
gApZ2Ice_Ts4_Pal:
	.incbin "data/ap/z2_ice/tileset4.gbapal"
	.balign 4, 0

gApZ2Ice_Ts5_Tiles:
	.incbin "data/ap/z2_ice/tileset5.4bpp.lz"
	.balign 4, 0
gApZ2Ice_Ts5_Pal:
	.incbin "data/ap/z2_ice/tileset5.gbapal"
	.balign 4, 0
