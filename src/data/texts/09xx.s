.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_TwilightDesert:: @ 0x08380b24
  .2byte (Text_TwilightDesert_IHaveBeenSummoned-Start), (Text_TwilightDesert_ThereIsNoEternity-Start), (Text_TwilightDesert_YouOfTheAncient-Start)

Text_TwilightDesert:: @ 0x08380b2a
Start:

Text_TwilightDesert_IHaveBeenSummoned: @ 0x08380B2A
	@ EN: I have been summoned / by Lord Weil back / from the netherworld / to continue my reign / of terror. / Ancient One, it is / now your turn to lie / beneath the soil... / Back to the earth / with you!
	.if ENGLISH
	.string "{WINDOW 0x27}"
		.string "I have been summoned\n"
		.string "by Lord Weil back\n"
		.string "from the netherworld▼"
		.string "to continue my reign\n"
		.string "of terror.▼"
		.string "Ancient One, it is\n"
		.string "now your turn to lie\n"
		.string "beneath the soil...▼"
		.string "Back to the earth\n"
		.string "with you!$"
	.else
	.string "{WINDOW 0x27}"
		.string "われ…バイルさまの手により\n"
		.string "メイフより\n"
		.string "まいもどりたり…▼"
		.string "古き者よ…\n"
		.string "つぎは おぬしが地のそこを\n"
		.string "はうバンだ…▼"
		.string "ツチへとかえるがよい…！$"
	.endif

Text_TwilightDesert_ThereIsNoEternity: @ 0x08380B75
	@ EN: There is no eternity / in this world. / Even your life must / come to an end!
	.if ENGLISH
	.string "{WINDOW 0x26}"
		.string "There is no eternity\n"
		.string "in this world.▼"
		.string "Even your life must\n"
		.string "come to an end!$"
	.else
	.string "{WINDOW 0x26}"
		.string "この世に永遠などありえん▼"
		.string "おぬしのイノチもしかりだ…！$"
	.endif

Text_TwilightDesert_YouOfTheAncient: @ 0x08380B96
	@ EN: You, of the ancient / soul. / You have no place in / the new world Lord / Weil is creating. / I will enjoy viewing / your torment from / my grave below... / Hahahahaa!
	.if ENGLISH
	.string "{WINDOW 0x26}"
		.string "You, of the ancient\n"
		.string "soul.▼"
		.string "You have no place in\n"
		.string "the new world Lord\n"
		.string "Weil is creating.▼"
		.string "I will enjoy viewing\n"
		.string "your torment from\n"
		.string "my grave below...▼"
		.string "Hahahahaa!$"
	.else
	.string "{WINDOW 0x26}"
		.string "古きタマシイをひきずる者よ…▼"
		.string "バイルさまの作る新しき世界に\n"
		.string "おぬしのイバショはない…▼"
		.string "もがきくるしむ おぬしのすがた…\n"
		.string "地のそこより見ておるぞ…▼"
		.string "フ…フフフフッ……！$"
	.endif

.balign 4, 0
