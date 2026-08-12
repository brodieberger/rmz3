.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_AnatreForest:: @ 0x08380bf4
  .2byte (Text_AnatreForest_MyBodyHasReturned-Start), (Text_AnatreForest_JusticeIsOnThe-Start), (Text_AnatreForest_AnImpressiveFight-Start)

Texts_AnatreForest:: @ 0x08380bfa
Start:

Text_AnatreForest_MyBodyHasReturned: @ 0x08380BFA
	@ EN: My body has returned / from decay... / For Lord Weil, who / gave me life... / I have returned! / And now, I will take / your pitiful soul. / Let's see you fight / like a hero!
	.if ENGLISH
	.string "{WINDOW 0x29}"
		.string "My body has returned\n"
		.string "from decay...▼"
		.string "For Lord Weil, who\n"
		.string "gave me life...▼"
		.string "I have returned!\n"
		.string "And now, I will take\n"
		.string "your pitiful soul.▼"
		.string "Let's see you fight▼"
		.string "like a hero!$"
	.else
	.string "{WINDOW 0x29}"
		.string "いちどは くちた このカラダ…▼"
		.string "イノチをあたえて下さった\n"
		.string "バイルさまのため…▼"
		.string "今再び！\n"
		.string "あなたのミシルシ\n"
		.string "いただきにまいりました！▼"
		.string "いざ…ジンジョウに▼"
		.string "ショウブ！$"
	.endif

Text_AnatreForest_JusticeIsOnThe: @ 0x08380C51
	@ EN: Justice is on the / side of the Neo / Arcadians!
	.if ENGLISH
	.string "{WINDOW 0x28}"
		.string "Justice is on the\n"
		.string "side of the Neo\n"
		.string "Arcadians!$"
	.else
	.string "{WINDOW 0x28}"
		.string "セイギは、われら\n"
		.string "ネオ・アルカディアにあり！$"
	.endif

Text_AnatreForest_AnImpressiveFight: @ 0x08380C6A
	@ EN: An impressive fight! / However... / Evil must fail in / the end! / History will judge / who the true / winner was! / May you perish, / O Ancient God of / Destruction!
	.if ENGLISH
	.string "{WINDOW 0x28}"
		.string "An impressive fight!\n"
		.string "However...▼"
		.string "Evil must fail in\n"
		.string "the end!▼"
		.string "History will judge\n"
		.string "who the true\n"
		.string "winner was!▼"
		.string "May you perish,\n"
		.string "O Ancient God of\n"
		.string "Destruction!$"
	.else
	.string "{WINDOW 0x28}"
		.string "お…おみごと…！\n"
		.string "ですが…▼"
		.string "最後に悪がほろびるは\n"
		.string "世のつね…！▼"
		.string "真のショウシャは…\n"
		.string "レキシがきめること……！▼"
		.string "ほろびよ…古きハカイ神…！$"
	.endif

.balign 4, 0
