.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_IceBase:: @ 0x08380cb8
  .2byte (Text_IceBase_HmphIAmImpressed-Start), (Text_IceBase_HmphACenturyIsNot-Start), (Text_IceBase_Groan-Start)

Texts_IceBase:: @ 0x08380cbe
Start:

Text_IceBase_HmphIAmImpressed: @ 0x08380CBE
	@ EN: Hmph. I am impressed / you made it to this / base. / Still... / I cannot dishonor / Lord Weil, the man / who brought me back. / I'll just have to / freeze you, now. / Hmph.
	.if ENGLISH
	.string "{WINDOW 0x2B}"
		.string "Hmph. I am impressed\n"
		.string "you made it to this\n"
		.string "base.▼"
		.string "Still...▼"
		.string "I cannot dishonor\n"
		.string "Lord Weil, the man\n"
		.string "who brought me back.▼"
		.string "I'll just have to\n"
		.string "freeze you, now.\n"
		.string "Hmph.$"
	.else
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
	.endif

Text_IceBase_HmphACenturyIsNot: @ 0x08380D1E
	@ EN: Hmph. / A century is not / enough. This time, / sleep forever!
	.if ENGLISH
	.string "{WINDOW 0x2A}"
		.string "Hmph.▼"
		.string "A century is not\n"
		.string "enough. This time,\n"
		.string "sleep forever!$"
	.else
	.string "{WINDOW 0x2A}"
		.string "むふー▼"
		.string "100年と言わず▼"
		.string "そのままずっとねむってろー$"
	.endif

Text_IceBase_Groan: @ 0x08380D3D
	@ EN: *groan* / Forgive me... / Lord Weil... / Hm...phahh!
	.if ENGLISH
	.string "{WINDOW 0x2A}"
		.string "*groan*\n"
		.string "Forgive me...\n"
		.string "Lord Weil...▼"
		.string "Hm...phahh!$"
	.else
	.string "{WINDOW 0x2A}"
		.string "ぐ…お…おゆるしを…\n"
		.string "バイルさま…▼"
		.string "む…っはーーーーーー！$"
	.endif

.balign 4, 0
