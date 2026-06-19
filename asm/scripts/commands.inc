
	.macro goto dst
  .byte 0x00
	.byte 0
  .2byte 0x00
  .4byte \dst
	.endm

  .macro cmd01 subcommand arg
  .byte 0x01
  .byte \subcommand
  .2byte 0
  .4byte \arg
  .endm

	.macro pause
  cmd01 0, 0
	.endm

	.macro wait frame
  cmd01 1, \frame
	.endm

	.macro waitabs absolute_time
  cmd01 2, \absolute_time
	.endm

	.macro time t
  .byte 0x02
	.byte 0x00
  .2byte 0x00
  .4byte \t
	.endm

	.macro do_nothing
  .byte 0x03
	.byte 0x00
  .2byte 0x00
  .4byte 0x00
	.endm

	.macro reset_camera template
  .byte 0x04
	.byte 0x00, 0x00, 0x00
  .4byte \template
	.endm
  
	.macro adjust_camera a b c
  .byte 0x05
	.byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro change_camera_mode mode
  adjust_camera 0, 0, \mode
	.endm

	.macro set_chase_mode mode
  adjust_camera 1, 0, \mode
	.endm

	.macro set_camera_target_x x_coord
  adjust_camera 3, 0, \x_coord
	.endm

	.macro set_camera_target_y y_coord
  adjust_camera 4, 0, \y_coord
	.endm

	.macro scroll_speed_x speed
  adjust_camera 5, 0, \speed
	.endm

	.macro scroll_speed_y speed
  adjust_camera 6, 0, \speed
	.endm

	.macro stop_camera
  adjust_camera 16, 0, 0
	.endm

	.macro resume_camera
  adjust_camera 17, 0, 0
	.endm

	.macro cmd06 a b c
  .byte 0x06
	.byte \a
  .2byte \b
  .4byte \c
	.endm

  .macro backdrop_color color
  cmd06 0, 5, \color
	.endm

	.macro resume a
  .byte 0x07
	.byte \a
  .2byte 0
  .4byte 0
	.endm

	.macro cmd08 a c
  .byte 0x08
	.byte \a
  .2byte 0x00
  .4byte \c
	.endm

  @ VM.active の bitidx がセットされるまで待機する
	.macro cmd08_wait_set bitidx
  cmd08 1, (1 << \bitidx)
	.endm

  @ VM.active の bitidx がクリアされるまで待機する
	.macro cmd08_wait_clear bitidx
  cmd08 0, (1 << \bitidx)
	.endm

  .macro lock
  .byte 0x09
	.byte 0
  .2byte 0
  .4byte 0
	.endm

  .macro release
  .byte 0x09
	.byte 1
  .2byte 0
  .4byte 0
	.endm

  .macro forcekeyinput input
  .byte 0x09
	.byte 2
  .2byte 0
  .4byte \input
	.endm

  .macro spawn slot addr b=0
  .byte 0x0b
	.byte \slot @ gStageRun.vm.entities の idx
  .2byte \b
  .4byte \addr
	.endm

  .macro change_entity_val slot targetattr val
  .byte 0x0c
	.byte \slot
  .2byte \targetattr
  .4byte \val
	.endm

  .macro set_entity_coords slot coords
  change_entity_val \slot, 0x0, \coords
	.endm

	.macro turn_left slot
  change_entity_val \slot, 0x2, 0
	.endm

	.macro turn_right slot
  change_entity_val \slot, 0x2, 1
	.endm

	.macro visible slot val
  change_entity_val \slot, 0x4+\val, 0
	.endm

  .macro destroy slot
  change_entity_val \slot, 0x6, 0
	.endm

	.macro detach_entity slot
  change_entity_val \slot, 0x7, 0x0
	.endm

	.macro entityflag slot bit bool
  .byte 0x0D
	.byte \slot
  .2byte (1 << \bit)
  .4byte \bool
	.endm

  .macro gameflag n val
  .byte 0x0D, 0x00
  .2byte \n
  .4byte 0x02 + \val
	.endm

  .macro cmd0f a b c
  .byte 0x0F
  .byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro set_emergency on_off
  .byte 0x10, \on_off
  .2byte 0, 0, 0
	.endm

	.macro emergency_on
  set_emergency 0
	.endm

	.macro emergency_off
  set_emergency 1
	.endm

	.macro quake a b c
  .byte 0x11
	.byte \a
  .2byte \b
  .4byte \c
	.endm

  .macro stop_quake
  .byte 0x11
	.byte 1
  .2byte 0
  .4byte 0
	.endm

  .macro emotion_bubble target_entity_idx pixel_x pixel_y emotion_kind
  .byte 0x12
  .byte \target_entity_idx
  .2byte \pixel_x
  .2byte \emotion_kind
  .2byte \pixel_y
  .endm

	.macro scroll a string_id duration
  .byte 0x13
	.byte \a
  .2byte \string_id
  .4byte \duration
	.endm

	.macro start_transition vmtransition
	.byte 0x14, \vmtransition
  .2byte 0, 0, 0
	.endm

  .macro wait_transition_end
	start_transition 0
	.endm

  .macro normal_screen
	start_transition (1 << 0)
	.endm

  .macro blackout_screen
	start_transition (1 << 1)
	.endm

  .macro whiteout_screen
	start_transition (1 << 2)
	.endm

  @ string_id で指定した文字列(string.s) を描画させる (print_string_end を呼ぶまで表示し続ける)
	.macro print_string x y string_id
  .byte 0x15
	.byte \x
  .2byte \y
  .2byte \string_id
  .2byte 0x00
	.endm

  @ print_string で表示した文字列　はこのコマンドを呼ぶまで消えない
  .macro print_string_end
  .byte 0x15, 0x00
  .2byte 0x00, 0x00, 0x00
  .endm

	.macro indicator a b c
  .byte 0x16
	.byte \a
  .2byte \b
  .4byte \c
	.endm

  .macro wait_indicator_end
  indicator 0, 0, 0
	.endm

  .macro failed_or_gameover_indicator
  indicator 2, 0, 0
	.endm

  .macro warning_indicator
  indicator 4, 0, 0
	.endm

	.macro message a b c
  .byte 0x17
	.byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro print_message msgtype textid
  message 0, \msgtype, \textid
	.endm

	.macro wait_msgbox_end
  message 2, 0, 0
	.endm

	.macro triumphant_message slot textid
  message 3, \slot, \textid
	.endm

  .macro kill_message
  message 7, 0, 0
  .endm

  .macro play_bgm song
  .byte 0x18
  .byte 0x00
  .2byte 0
  .4byte \song
  .endm

  .macro stop_bgm
  .byte 0x18
  .byte 0x01
  .2byte 0
  .4byte 0
  .endm

  .macro wait_bgm_end
  .byte 0x18
  .byte 0x02
  .2byte 0
  .4byte 0
  .endm

	.macro play_se se
  .byte 0x19
	.byte 0
  .2byte 0
  .4byte \se
	.endm

	.macro stop_se se
  .byte 0x19
	.byte 1
  .2byte 0
  .4byte \se
	.endm

	.macro fadeout_se duration se
  .byte 0x19
	.byte 2
  .2byte \duration
  .4byte \se
	.endm

	.macro force a b c
  .byte 0x1a
	.byte \a
  .2byte \b
  .4byte \c
	.endm

  .macro clear_force_coord
  force 1, 0, 0
	.endm

  .macro start_talk
  force 2, 0, 0
	.endm

  .macro end_talk
  force 3, 0, 0
	.endm

  .macro walkto dst
  force 9, 0, \dst
	.endm

	.macro gimmick a b c
  .byte 0x1b
	.byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro cmd1c a b c
  .byte 0x1c
	.byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro sweep a b c
  .byte 0x1d
	.byte \a
  .2byte \b
  .4byte \c
	.endm

	.macro lockmenu
  .byte 0x1e
	.byte 0
  .2byte 0
  .4byte 0
	.endm

	.macro unlockmenu
  .byte 0x1e
	.byte 1
  .2byte 0
  .4byte 0
	.endm

	.macro cutscene_flag a b
  .byte 0x1F
	.byte \a
  .2byte \b
  .4byte 0
	.endm

  @ ここから cutscene_end までのコマンドがカットシーンであることを示すコマンド
	.macro cutscene_start cutscene_id
  cutscene_flag 0, \cutscene_id
	.endm

  @ カットシーンの終了を示す (初見のイベントだったらここで見たことをあらわすフラグが立つ)
	.macro cutscene_end
  cutscene_flag 1, 0
	.endm

  @ 汎用的なグラフィックデータ (戦闘エフェクト、吹き出し、数字、エレメントエフェクト) の読み込み
	.macro load_graphic_primitive
  .byte 0x20, 0x0
	.2byte 0x00, 0x00, 0x00
	.endm

	.macro result_screen init_or_update
  .byte 0x22, \init_or_update
  .2byte 0x00, 0x00, 0x00
	.endm

	.macro start_result_screen
  result_screen 0
	.endm

	.macro wait_for_result_screen_end
  result_screen 1
	.endm

	.macro goodluck val
  .byte 0x23
	.byte \val
  .2byte 0
  .4byte 0
	.endm

	.macro killtimeelf
  .byte 0x24
	.byte 0
  .2byte 0
  .4byte 0
	.endm

  @ 大きな一枚絵を使って(静止したものではない)ムービーシーンを再生する
	.macro play_movie id
  .byte 0x25
	.byte \id
  .2byte 0
  .4byte 0
	.endm

  @ プロローグで落ちてきた宇宙船を発見したときのムービー
  .macro play_find_spacecraft_movie step
  play_movie (0 + \step)
  .endm

  @ オリジナルゼロが出てきたときのムービー
  .macro play_omega_zero_appear_movie step
  play_movie (3 + \step)
  .endm

  @ 後半の4ミッションを終えた後にオメガによる洗脳が始まるときのムービー
  .macro play_brain_control_movie step
  play_movie (6 + \step)
  .endm

	.macro end
  .byte 0xFF
	.byte 0
  .2byte 0
  .4byte 0
	.endm
