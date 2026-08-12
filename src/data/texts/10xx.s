.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

.global TextOfs_GiantElevator
TextOfs_GiantElevator: @ 0x08382008
  .2byte (Text_GiantElevator_Empty - Start), (Text_GiantElevator_GrrrSoYouRe - Start), (Text_GiantElevator_WhatSThisAhhI - Start), (Text_GiantElevator_Huh - Start)

Texts_GiantElevator:: @ 0x08382010
Start:

Text_GiantElevator_Empty: @ 0x08382010
  .if ENGLISH
		.string "$"
  .else
  .string "$"
  .endif

Text_GiantElevator_GrrrSoYouRe: @ 0x08382011
	@ EN: Grrr... So you're / Zerrooo? / You're so tiny, I / almost stepped on / yah! / My name is Tretista / Kelverian, of Weil's / Numbers. / Your neck is so / tiny... I'll snap it / with one chomp! / Grrrrrrr!
	.if ENGLISH
	.string "{WINDOW 0x15}"
		.string "Grrr... So you're\n"
		.string "Zerrooo?▼"
		.string "You're so tiny, I\n"
		.string "almost stepped on\n"
		.string "yah!▼"
		.string "My name is Tretista\n"
		.string "Kelverian, of Weil's\n"
		.string "Numbers.▼"
		.string "Your neck is so\n"
		.string "tiny... I'll snap it\n"
		.string "with one chomp!▼"
		.string "Grrrrrrr!$"
	.else
	.string "{WINDOW 0x15}"
		.string "ゴルルルゥ…テメエがゼロかぁ…？▼"
		.string "小さすぎてぇ\n"
		.string "ふんづけちまうところだったぜぇ…！▼"
		.string "オレの名はバイル・ナンバーズ\n"
		.string "トレテスタ・ケルベリアン▼"
		.string "そのほそいくび…\n"
		.string "ひとくちでぇ\n"
		.string "かみちぎってやるぜぇ！▼"
		.string "ゴルルルルルルァ！$"
	.endif

Text_GiantElevator_WhatSThisAhhI: @ 0x08382081
	@ EN: What's this? / Ahh, I must've / stepped on you. / You're so tiny, I / didn't even realize / it!
	.if ENGLISH
	.string "{WINDOW 0x14}"
		.string "What's this?▼"
		.string "Ahh, I must've\n"
		.string "stepped on you.▼"
		.string "You're so tiny, I\n"
		.string "didn't even realize\n"
		.string "it!$"
	.else
	.string "{WINDOW 0x14}"
		.string "ああーん？▼"
		.string "いつのまにかぁ\n"
		.string "ふみつぶしちまったかぁ？▼"
		.string "小さすぎて気づかなかったぜぇ！$"
	.endif

Text_GiantElevator_Huh: @ 0x083820b0
	@ EN: Huh? / Zero... Where did / you go? I don't / see you... / And my whole body / hurts... Ouch... / Oouuuch! / Gaarrrwwwrrr!
	.if ENGLISH
	.string "{WINDOW 0x14}"
		.string "Huh?\n"
		.string "Zero... Where did\n"
		.string "you go? I don't▼"
		.string "see you...▼"
		.string "And my whole body\n"
		.string "hurts... Ouch...\n"
		.string "Oouuuch!▼"
		.string "Gaarrrwwwrrr!$"
	.else
	.string "{WINDOW 0x14}"
		.string "あ…れぇ…？\n"
		.string "ゼロォ…どこ行きやがったぁ…？\n"
		.string "見えねえぞぉ…？▼"
		.string "それに…カラダもいてえ…\n"
		.string "いてえ…いてえぞおおおっ！▼"
		.string "ゴアアアアアアッ！$"
	.endif

.balign 4, 0
