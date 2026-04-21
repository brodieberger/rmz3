.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_OceanHighwayRuins:: @ 0x0837fd54
  .2byte (Text0-Start),  (Text1-Start),  (Text2-Start),  (Text3-Start)
  .2byte (Text4-Start),  (Text5-Start),  (Text6-Start),  (Text7-Start)
  .2byte (Text8-Start),  (Text9-Start),  (Text10-Start), (Text11-Start)
  .2byte (Text12-Start), (Text13-Start), (Text14-Start)

Text_OceanHighwayRuins:: @ 0x0837fd72
Start:

Text0: @ 0x0837FD72
	.string "{WINDOW 0x64}"
		.string "シエル:\n"
		.string "「ゼロ！ 今のハンノウは…！▼"
	.string "{WINDOW 0x04}"
		.string "ダークエルフをカクニンした\n"
		.string "ツイセキをカイシする$"

Text1: @ 0x0837FDA4
Text2:
Text3:
	.string "{WINDOW 0x09}"
		.string "なんだ、オマエは？▼"
		.string "はは〜ん…\n"
		.string "さては、オマエも さっきの\n"
		.string "ダークエルフをねらってるんだな？▼"
		.string "そうはさせるか！$"

Text4: @ 0x0837FDDE
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ…！ 聞こえる？▼"
		.string "「このさきにウミのスイイを下げるスイッチがあるから▼"
		.string "「それをおして、そのメカのシンコウをおくらせて！$"

Text5: @ 0x0837FE24
Text6:
Text7:
Text8:
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}ゼ………ロ…………▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}ダークエルフ…！$"

Text9: @ 0x0837FE3D
	.string "{WINDOW 0x39}"
		.string "{BOTTOM}……ヤメ……テ……！$"

Text10: @ 0x0837FE4B
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}……！$"

Text11: @ 0x0837FE52
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}コイツをかたづけるのが\n"
		.string "さき…か$"

Text12: @ 0x0837FE66
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

Text13: @ 0x0837FEDB
	.string "{WINDOW 0x08}"
		.string "そこでサメのエサにでもなってな！▼"
		.string "さーて、ダークエルフを\n"
		.string "おっかけるとするか！！$"

Text14: @ 0x0837FF06
	.string "{WINDOW 0x08}"
		.string "ふざ…けんな…▼"
		.string "オイラが…なんでこんな目に…\n"
		.string "ち…ちくしょおーーーーっ！$"

.balign 4, 0
