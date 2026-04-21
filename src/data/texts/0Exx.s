.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SnowyPlains:: @ 0x083815dc
    .2byte Text0-Start, Text1-Start, Text2-Start, Text3-Start
    .2byte Text4-Start, Text5-Start, Text6-Start, Text7-Start

Texts_SnowyPlains:: @ 0x083815ec
Start:

Text0: @ 0x083815ec
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

Text1: @ 0x0838164B
	.string "{WINDOW 0x04}"
		.string "…あれか$"

Text2: @ 0x08381652
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

Text3: @ 0x083816CD
	.string "{WINDOW 0x11}"
		.string "けだかきバイル・ナンバーズ\n"
		.string "グラチャー・レ・カクタンクの\n"
		.string "名において…はんけつをくだす▼"
		.string "ドロボウのつみは…\n"
		.string "死けいであーる！$"

Text4: @ 0x08381710
	.string "{WINDOW 0x10}"
		.string "んんーっ！▼"
		.string "ユキの下で深くしずかに\n"
		.string "ハンセイするのであーる！$"

Text5: @ 0x08381733
	.string "{WINDOW 0x10}"
		.string "お…おお…▼"
		.string "ドロボウだけにあきたらず…\n"
		.string "バイルさまへのテイコウまでも…！▼"
		.string "さばかれるがいいであーる…\n"
		.string "バイルさまの\n"
		.string "新しきチツジョのもとに…！▼"
		.string "グッ…オオオオッ！$"

Text6: @ 0x08381788
	.string "{WINDOW 0x6D}"
		.string "コンテナの中からデータを発見！▼"
		.string "ゼロさん！\n"
		.string "データのカイシュウ…\n"
		.string "カンリョウしました！！▼"
		.string "わたしは ひきつづき\n"
		.string "データをさがします$"

Text7: @ 0x083817cf
	.string "{WINDOW 0x00}"
		.string "オペレーター「ミッションしゅうりょう▼"
		.string "転送をカイシします$"

.balign 4, 0
