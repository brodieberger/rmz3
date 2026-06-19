.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_TwilightDesert:: @ 0x08380b24
  .2byte (Text0-Start), (Text1-Start), (Text2-Start)

Text_TwilightDesert:: @ 0x08380b2a
Start:

Text0: @ 0x08380B2A
	.string "{WINDOW 0x27}"
		.string "われ…バイルさまの手により\n"
		.string "メイフより\n"
		.string "まいもどりたり…▼"
		.string "古き者よ…\n"
		.string "つぎは おぬしが地のそこを\n"
		.string "はうバンだ…▼"
		.string "ツチへとかえるがよい…！$"

Text1: @ 0x08380B75
	.string "{WINDOW 0x26}"
		.string "この世に永遠などありえん▼"
		.string "おぬしのイノチもしかりだ…！$"

Text2: @ 0x08380B96
	.string "{WINDOW 0x26}"
		.string "古きタマシイをひきずる者よ…▼"
		.string "バイルさまの作る新しき世界に\n"
		.string "おぬしのイバショはない…▼"
		.string "もがきくるしむ おぬしのすがた…\n"
		.string "地のそこより見ておるぞ…▼"
		.string "フ…フフフフッ……！$"

.balign 4, 0
