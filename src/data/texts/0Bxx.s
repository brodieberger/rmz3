.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_IceBase:: @ 0x08380cb8
  .2byte (Text0-Start), (Text1-Start), (Text2-Start)

Texts_IceBase:: @ 0x08380cbe
Start:

Text0: @ 0x08380CBE
	.string "{WINDOW 0x2B}"
		.string "むふー\n"
		.string "よくこの基地まで\n"
		.string "たどりついたなー▼"
		.string "しかし…▼"
		.string "オレをよみがえらせてくれた\n"
		.string "バイルさまのカオに\n"
		.string "ドロをぬらせるわけには、いかねー▼"
		.string "ここでオマエを\n"
		.string "コオリづけにしてやるー\n"
		.string "むふー$"

Text1: @ 0x08380D1E
	.string "{WINDOW 0x2A}"
		.string "むふー▼"
		.string "100年と言わず▼"
		.string "そのままずっとねむってろー$"

Text2: @ 0x08380D3D
	.string "{WINDOW 0x2A}"
		.string "ぐ…お…おゆるしを…\n"
		.string "バイルさま…▼"
		.string "む…っはーーーーーー！$"

.balign 4, 0
