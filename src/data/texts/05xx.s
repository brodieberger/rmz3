.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_OceanHighwayRuins:: @ 0x0837fd54
  .2byte (Text_OceanHighwayRuins_GotAReading-Start),  (Text_OceanHighwayRuins_WhoTheHeckReYou-Start),  (Text_OceanHighwayRuins_WhoTheHeckReYou_2-Start),  (Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias1-Start)
  .2byte (Text_OceanHighwayRuins_CielCanYouHearMe-Start),  (Text_OceanHighwayRuins_ZeeeeeeerrooooodarkElf-Start),  (Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias2-Start),  (Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias3-Start)
  .2byte (Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias4-Start),  (Text_OceanHighwayRuins_StoooooopIiiiiit-Start),  (Text_OceanHighwayRuins_Empty-Start), (Text_OceanHighwayRuins_ILlHaveToTake-Start)
  .2byte (Text_OceanHighwayRuins_WhatAPainYouAre-Start), (Text_OceanHighwayRuins_YouReSharkFood-Start), (Text_OceanHighwayRuins_YouReKiddingMeWhy-Start)

Text_OceanHighwayRuins:: @ 0x0837fd72
Start:

Text_OceanHighwayRuins_GotAReading: @ 0x0837FD72
	@ EN: Ciel: / Zero! We've just / got a reading! / Dark Elf detected. / Beginning pursuit.
	.if ENGLISH
	.string "{WINDOW 0x64}"
		.string "Ciel:\n"
		.string "Zero! We've just\n"
		.string "got a reading!▼"
	.string "{WINDOW 0x04}"
		.string "Dark Elf detected.\n"
		.string "Beginning pursuit.$"
	.else
	.string "{WINDOW 0x64}"
		.string "シエル:\n"
		.string "「ゼロ！ 今のハンノウは…！▼"
	.string "{WINDOW 0x04}"
		.string "ダークエルフをカクニンした\n"
		.string "ツイセキをカイシする$"
	.endif

Text_OceanHighwayRuins_WhoTheHeckReYou: @ 0x0837FDA4
Text_OceanHighwayRuins_WhoTheHeckReYou_2:
Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias1:
	@ EN: Who the heck're you? / Heh, you must be / after that Dark Elf, / too. Am I right? / You'll have to get / past me, first!
	.if ENGLISH
	.string "{WINDOW 0x09}"
		.string "Who the heck're you?▼"
		.string "Heh, you must be\n"
		.string "after that Dark Elf,\n"
		.string "too. Am I right?▼"
		.string "You'll have to get\n"
		.string "past me, first!$"
	.else
	.string "{WINDOW 0x09}"
		.string "なんだ、オマエは？▼"
		.string "はは〜ん…\n"
		.string "さては、オマエも さっきの\n"
		.string "ダークエルフをねらってるんだな？▼"
		.string "そうはさせるか！$"
	.endif

Text_OceanHighwayRuins_CielCanYouHearMe: @ 0x0837FDDE
	@ EN: Ciel: Can you hear me, / Zero?! There's a switch / up ahead that lowers the / ocean's water level. Hit / it and slow the mech down!
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Can you hear me,▼"
		.string "Zero?! There's a switch▼"
		.string "up ahead that lowers the▼"
		.string "ocean's water level. Hit▼"
		.string "it and slow the mech down!$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ…！ 聞こえる？▼"
		.string "「このさきにウミのスイイを下げるスイッチがあるから▼"
		.string "「それをおして、そのメカのシンコウをおくらせて！$"
	.endif

Text_OceanHighwayRuins_ZeeeeeeerrooooodarkElf: @ 0x0837FE24
Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias2:
Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias3:
Text_OceanHighwayRuins_WhoTheHeckReYou_2_Alias4:
	@ EN: Zeeeeeeerrooooo / Dark Elf!
	.if ENGLISH
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}Zeeeeeeerrooooo▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}Dark Elf!$"
	.else
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}ゼ………ロ…………▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}ダークエルフ…！$"
	.endif

Text_OceanHighwayRuins_StoooooopIiiiiit: @ 0x0837FE3D
	@ EN: Stoooooop iiiiiit!
	.if ENGLISH
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}Stoooooop iiiiiit!$"
	.else
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}……ヤメ……テ……！$"
	.endif

Text_OceanHighwayRuins_Empty: @ 0x0837FE4B
	@ EN: !!!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}!!!$"
	.else
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}……！$"
	.endif

Text_OceanHighwayRuins_ILlHaveToTake: @ 0x0837FE52
	@ EN: I'll have to take / care of this guy / first...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}I'll have to take\n"
		.string "care of this guy\n"
		.string "first...$"
	.else
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}コイツをかたづけるのが\n"
		.string "さき…か$"
	.endif

Text_OceanHighwayRuins_WhatAPainYouAre: @ 0x0837FE66
	@ EN: What a pain you are! / I thought you'd be / easier to scare off / than that! / No more games. I'm / Childre Inarabitta, / of Weil's Numbers! / I'll see that smug / face of yours / frozen with fear!
	.if ENGLISH
	.string "{WINDOW 0x09}"
		.string "What a pain you are!▼"
		.string "I thought you'd be\n"
		.string "easier to scare off\n"
		.string "than that!▼"
		.string "No more games. I'm\n"
		.string "Childre Inarabitta,\n"
		.string "of Weil's Numbers!▼"
		.string "I'll see that smug\n"
		.string "face of yours\n"
		.string "frozen with fear!$"
	.else
	.string "{WINDOW 0x09}"
		.string "うっとおしいヤツだなー！▼"
		.string "ちょっとビビらせてやれば\n"
		.string "にげかえると思ったのにーッ！▼"
		.string "もう手かげんすんのヤーメたっ！\n"
		.string "オイラはバイル・ナンバーズ\n"
		.string "チルドレ・イナラビッタ！▼"
		.string "そのすかしたツラ、\n"
		.string "キョウフで\n"
		.string "コオリつかせてやるよっ！$"
	.endif

Text_OceanHighwayRuins_YouReSharkFood: @ 0x0837FEDB
	@ EN: You're shark food, / now! / Now, time to go / after that Dark Elf!
	.if ENGLISH
	.string "{WINDOW 0x08}"
		.string "You're shark food,\n"
		.string "now!▼"
		.string "Now, time to go\n"
		.string "after that Dark Elf!$"
	.else
	.string "{WINDOW 0x08}"
		.string "そこでサメのエサにでもなってな！▼"
		.string "さーて、ダークエルフを\n"
		.string "おっかけるとするか！！$"
	.endif

Text_OceanHighwayRuins_YouReKiddingMeWhy: @ 0x0837FF06
	@ EN: You're kidding me... / Why is this... / happening...to me?!
	.if ENGLISH
	.string "{WINDOW 0x08}"
		.string "You're kidding me...▼"
		.string "Why is this...\n"
		.string "happening...to me?!$"
	.else
	.string "{WINDOW 0x08}"
		.string "ふざ…けんな…▼"
		.string "オイラが…なんでこんな目に…\n"
		.string "ち…ちくしょおーーーーっ！$"
	.endif

.balign 4, 0
