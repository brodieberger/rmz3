.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_AnatreForest:: @ 0x08380bf4
  .2byte (Text0-Start), (Text1-Start), (Text2-Start)

Texts_AnatreForest:: @ 0x08380bfa
Start:

Text0: @ 0x08380BFA
	.string "{WINDOW 0x29}"
		.string "いちどは くちた このカラダ…▼"
		.string "イノチをあたえて下さった\n"
		.string "バイルさまのため…▼"
		.string "今再び！\n"
		.string "あなたのミシルシ\n"
		.string "いただきにまいりました！▼"
		.string "いざ…ジンジョウに▼"
		.string "ショウブ！$"

Text1: @ 0x08380C51
	.string "{WINDOW 0x28}"
		.string "セイギは、われら\n"
		.string "ネオ・アルカディアにあり！$"

Text2: @ 0x08380C6A
	.string "{WINDOW 0x28}"
		.string "お…おみごと…！\n"
		.string "ですが…▼"
		.string "最後に悪がほろびるは\n"
		.string "世のつね…！▼"
		.string "真のショウシャは…\n"
		.string "レキシがきめること……！▼"
		.string "ほろびよ…古きハカイ神…！$"

.balign 4, 0
