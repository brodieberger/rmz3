.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SnowyPlains:: @ 0x083815dc
    .2byte Text_SnowyPlains_AhMrZeroTheEnemy-Start, Text_SnowyPlains_IsThatIt-Start, Text_SnowyPlains_HahThatContainerWas-Start, Text_SnowyPlains_IGlacierLe-Start
    .2byte Text_SnowyPlains_HahConsiderYourSins-Start, Text_SnowyPlains_OhMyNotStoppingAt-Start, Text_SnowyPlains_WeVeDiscovered-Start, Text_SnowyPlains_OperatorMissionCompletedCommencingTransfer-Start

Texts_SnowyPlains:: @ 0x083815ec
Start:

Text_SnowyPlains_AhMrZeroTheEnemy: @ 0x083815ec
	@ EN: Ah, Mr. Zero! / The enemy is / waiting in ambush up / ahead... / There's no way we / can break through. / Mr. Zero, if you can / make an opening, / we'll follow you.
	.if ENGLISH
	.string "{WINDOW 0x6D}"
		.string "Ah, Mr. Zero!▼"
		.string "The enemy is\n"
		.string "waiting in ambush up\n"
		.string "ahead...▼"
		.string "There's no way we\n"
		.string "can break through.▼"
		.string "Mr. Zero, if you can\n"
		.string "make an opening,\n"
		.string "we'll follow you.$"
	.else
	.string "{WINDOW 0x6D}"
		.string "あ！ ゼロさん！▼"
		.string "このさきにテキが、\n"
		.string "マチブセしていて…▼"
		.string "わたしたちでは、\n"
		.string "とてもトッパできそうも\n"
		.string "ありません…▼"
		.string "ゼロさんが\n"
		.string "トッパコウを開いてくだされば\n"
		.string "ワレワレも後につづきます$"
	.endif

Text_SnowyPlains_IsThatIt: @ 0x0838164B
	@ EN: Is that it?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Is that it?$"
	.else
	.string "{WINDOW 0x04}"
		.string "…あれか$"
	.endif

Text_SnowyPlains_HahThatContainerWas: @ 0x08381652
	@ EN: Hah! / That container was / on Omega's ship. So / you see, it's ours. / Has the legendary / hero stooped to / thievery? / How deplorable. / As king of the Snow / Plains, I do hereby / judge your crime.
	.if ENGLISH
	.string "{WINDOW 0x21}"
		.string "Hah!▼"
		.string "That container was\n"
		.string "on Omega's ship. So\n"
		.string "you see, it's ours.▼"
		.string "Has the legendary\n"
		.string "hero stooped to\n"
		.string "thievery?▼"
		.string "How deplorable.▼"
		.string "As king of the Snow\n"
		.string "Plains, I do hereby\n"
		.string "judge your crime.$"
	.else
	.string "{WINDOW 0x21}"
		.string "んんーっ▼"
		.string "このコンテナは\n"
		.string "オメガのフネにつんであった…\n"
		.string "いわばわれわれのモノであーる▼"
		.string "伝説のエイユウも、\n"
		.string "ドロボウになりさがったであるか？▼"
		.string "なげかわしいことであーる…▼"
		.string "セツゲンの王たるこのワシが\n"
		.string "オマエのつみを\n"
		.string "さばいてやるのであーる$"
	.endif

Text_SnowyPlains_IGlacierLe: @ 0x083816CD
	@ EN: I, Glacier Le / Cactank, of / Weil's Numbers, / have reached a / verdict. / The punishment for / thievery is death!
	.if ENGLISH
	.string "{WINDOW 0x11}"
		.string "I, Glacier Le\n"
		.string "Cactank, of\n"
		.string "Weil's Numbers,▼"
		.string "have reached a\n"
		.string "verdict.▼"
		.string "The punishment for\n"
		.string "thievery is death!$"
	.else
	.string "{WINDOW 0x11}"
		.string "けだかきバイル・ナンバーズ\n"
		.string "グラチャー・レ・カクタンクの\n"
		.string "名において…はんけつをくだす▼"
		.string "ドロボウのつみは…\n"
		.string "死けいであーる！$"
	.endif

Text_SnowyPlains_HahConsiderYourSins: @ 0x08381710
	@ EN: Hah! / Consider your sins / from deep beneath / the silent snow!
	.if ENGLISH
	.string "{WINDOW 0x10}"
		.string "Hah!▼"
		.string "Consider your sins\n"
		.string "from deep beneath\n"
		.string "the silent snow!$"
	.else
	.string "{WINDOW 0x10}"
		.string "んんーっ！▼"
		.string "ユキの下で深くしずかに\n"
		.string "ハンセイするのであーる！$"
	.endif

Text_SnowyPlains_OhMyNotStoppingAt: @ 0x08381733
	@ EN: Oh...my... / Not stopping at / thievery, you also / defy Lord Weil!? / Lord Weil's new / order will issue / judgment upon you! / Arrrrgh!
	.if ENGLISH
	.string "{WINDOW 0x10}"
		.string "Oh...my...▼"
		.string "Not stopping at\n"
		.string "thievery, you also\n"
		.string "defy Lord Weil!?▼"
		.string "Lord Weil's new\n"
		.string "order will issue\n"
		.string "judgment upon you!▼"
		.string "Arrrrgh!$"
	.else
	.string "{WINDOW 0x10}"
		.string "お…おお…▼"
		.string "ドロボウだけにあきたらず…\n"
		.string "バイルさまへのテイコウまでも…！▼"
		.string "さばかれるがいいであーる…\n"
		.string "バイルさまの\n"
		.string "新しきチツジョのもとに…！▼"
		.string "グッ…オオオオッ！$"
	.endif

Text_SnowyPlains_WeVeDiscovered: @ 0x08381788
	@ EN: We've discovered / data inside the / container! / Mr. Zero! / We've recovered all / of the data! / I will continue / searching for more / data.
	.if ENGLISH
	.string "{WINDOW 0x6D}"
		.string "We've discovered\n"
		.string "data inside the\n"
		.string "container!▼"
		.string "Mr. Zero!\n"
		.string "We've recovered all\n"
		.string "of the data!▼"
		.string "I will continue\n"
		.string "searching for more\n"
		.string "data.$"
	.else
	.string "{WINDOW 0x6D}"
		.string "コンテナの中からデータを発見！▼"
		.string "ゼロさん！\n"
		.string "データのカイシュウ…\n"
		.string "カンリョウしました！！▼"
		.string "わたしは ひきつづき\n"
		.string "データをさがします$"
	.endif

Text_SnowyPlains_OperatorMissionCompletedCommencingTransfer: @ 0x083817cf
	@ EN: Operator: Mission completed. / Commencing transfer.
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Operator: Mission completed.▼"
		.string "Commencing transfer.$"
	.else
	.string "{WINDOW 0x00}"
		.string "オペレーター「ミッションしゅうりょう▼"
		.string "転送をカイシします$"
	.endif

.balign 4, 0
