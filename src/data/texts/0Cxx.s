.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_AreaX2:: @ 0x08380d60
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start)
  .2byte (Text4-Start), 0x01d0, 0x029e, 0x02c4
  .2byte 0x02ed, 0x0339, 0x0377, 0x0384
  .2byte 0x041b, 0x04e9, 0x0593, 0x05d2

Texts_AreaX2:: @ 0x08380d80
Start:

Text0: @ 0x08380d80
	.string "$"

Text1: @ 0x08380D81
	.string "{WINDOW 0x37}"
		.string "きたネ…ゼロ▼"
		.string "キミは 自分が\n"
		.string "何を シていルか\n"
		.string "ワかってイるのかい？▼"
		.string "テロリストのミカタだよ…？▼"
		.string "伝説のエイユウが\n"
		.string "悪の軍団の手助けを\n"
		.string "していルんだヨ？▼"
	.string "{WINDOW 0x04}"
		.string "オレたちが\n"
		.string "悪の軍団で…▼"
		.string "オマエたちは、\n"
		.string "セイギのみかた…\n"
		.string "ということか……▼"
	.string "{WINDOW 0x37}"
		.string "そのとオり▼"
		.string "ボクたちは、\n"
		.string "人間たちのアットウ的なシジを\n"
		.string "うけている……▼"
		.string "テロリストを たおすことは、\n"
		.string "カレら人間…みんなのユメなんだよ▼"
	.string "{WINDOW 0x04}"
		.string "かいならされた人間たちが\n"
		.string "のぞむセイギに……▼"
		.string "いったい何のカチが\n"
		.string "あるっていうんだ▼"
	.string "{WINDOW 0x37}"
		.string "カチなんて どうでもイいんダよ…\n"
		.string "ネオ・アルカディアの\n"
		.string "やっテいることは たダしい…▼"
		.string "そのセイギの ショウメイになれば\n"
		.string "それで いイのさ！$"

Text2: @ 0x08380EC8
	.string "{WINDOW 0x6E}"
		.string "あは！ アはハはハは！▼"
		.string "見タか！やっぱりボクは\n"
		.string "本当のエイユウなんダ！$"

Text3: @ 0x08380EF1
	.string "{WINDOW 0x6F}"
		.string "くソっ…ナぜだ…！▼"
		.string "ボクは…ボクはセイギの\n"
		.string "エイユウなんダぞ…！▼"
		.string "バイル！\n"
		.string "ドクター・バイル！▼"
		.string "オメガを…オメガをだセ！\n"
		.string "コイツをひネりつぶセーッ！$"

Text4: @ 0x08380F3E
	.string "{WINDOW 0x34}"
		.string "カレはもう…▼"
		.string "ここにはいないよ$"

Text_0x08380F50: @ 0x08380F50
	.string "{WINDOW 0x6F}"
		.string "な…なンだ、オマエハ！？▼"
	.string "{WINDOW 0x04}"
		.string "エックス…！▼"
	.string "{WINDOW 0x6F}"
		.string "…エックスだと…！？▼"
		.string "オマエが…ボクのもとにナった\n"
		.string "オリジナルのエックス…！？▼"
	.string "{WINDOW 0x34}"
		.string "バイルは…\n"
		.string "この本部をすて\n"
		.string "べつのところにうつったよ▼"
		.string "オメガをつれてね……▼"
		.string "キミはバイルに\n"
		.string "利用されていただけなんだよ…▼"
	.string "{WINDOW 0x6F}"
		.string "ギ…ギギッ…▼"
		.string "どいツも…こイつも…\n"
		.string "ボクをバカにしやがッテ…！▼"
		.string "ゆるサナイ…ユルサないぞ…！\n"
		.string "ボクの…本当のチカラを…\n"
		.string "見せテやル…！$"

Text_0x0838101E: @ 0x0838101E
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}ハぁーーーーっ！！▼"
	.string "{WINDOW 0x34}"
		.string "いけない！▼"
		.string "バイルはキミのカラダに\n"
		.string "ワナを！$"

Text_0x08381044: @ 0x08381044
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}ギ…ガガ…！？▼"
		.string "カ…カラダが…しびれ…▼"
		.string "グガガッ…\n"
		.string "アアアアアアーーーッ！$"

Text_0x0838106D: @ 0x0838106D
	.string "{WINDOW 0x04}"
		.string "………！？▼"
	.string "{WINDOW 0x35}"
		.string "バイルは はじめから\n"
		.string "こうなることを 知っていて…\n"
		.string "カレにワナをしかけていたんだ▼"
		.string "カレの…本当のヤボウを\n"
		.string "かなえるために……$"

Text_0x083810B9: @ 0x083810B9
	.string "{WINDOW 0x52}"
		.string "…ネオ・アルカディアの\n"
		.string "すべてのゼンリョウなるシミンの\n"
		.string "みなさんに……▼"
		.string "かなしいお知らせをしなければ\n"
		.string "なりません……$"

Text_0x083810F7: @ 0x083810F7
	.string "{WINDOW 0x04}"
		.string "ドクター・バイル……$"

Text_0x08381104: @ 0x08381104
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}たった今…▼"
		.string "チにうえたテロリストの手にかかり\n"
		.string "ワレラがエイユウ…\n"
		.string "エックスさまが…………▼"
		.string "おナクなりに…\n"
		.string "なりました………▼"
		.string "今からジョウレイ8コウの\n"
		.string "テキヨウにより…▼"
		.string "フショウこのドクター・バイルが\n"
		.string "みなさんのシドウシャとなり…▼"
		.string "テロリストちんあつのシキを\n"
		.string "とりおこなうことになりました…$"

Text_0x0838119B: @ 0x0838119B
	.string "{WINDOW 0x52}"
		.string "………▼"
		.string "ありがとうございます\n"
		.string "今、みなさんのごショウニンを\n"
		.string "カクニンいたしました▼"
		.string "これから、みなさんにイロイロな\n"
		.string "オネガイをすることになるかも\n"
		.string "しれませんが……▼"
		.string "テロリストぼくめつまで……\n"
		.string "ネオ・アルカディアに\n"
		.string "真の平和は、おとずれません！▼"
		.string "ともにテロリストをねだやしに\n"
		.string "するまで、戦おうでは\n"
		.string "ありませんか！！▼"
		.string "……クッ………▼"
		.string "クックックッ……▼"
		.string "クーックックックッ…\n"
		.string "クヒャーッハッハッハッハッ！$"

Text_0x08381269: @ 0x08381269
	.string "{WINDOW 0x04}"
		.string "…………▼"
		.string "すべてヤツの\n"
		.string "スジガキどおり……か▼"
	.string "{WINDOW 0x35}"
		.string "ドクター・バイル……▼"
		.string "あなたは また\n"
		.string "100年前の戦争を…▼"
		.string "ヨウセイ戦争の ヒゲキを\n"
		.string "くりかえす つもりなのか…▼"
	.string "{WINDOW 0x04}"
		.string "オレはバイルの行方をおう▼"
		.string "チカラをかしてくれ▼"
	.string "{WINDOW 0x35}"
		.string "わかった……▼"
		.string "ボクもカレのイバショを\n"
		.string "さがそう……▼"
		.string "ところで……\n"
		.string "オメガのことなんだが……▼"
		.string "…………$"

Text_0x08381313: @ 0x08381313
	.string "{WINDOW 0x04}"
		.string "なんだ……？▼"
	.string "{WINDOW 0x35}"
		.string "いや……▼"
		.string "その時になったら\n"
		.string "あらためて言うよ……▼"
		.string "大事なのは、カラダではなく\n"
		.string "心なのだと……$"

Text_0x08381352: @ 0x08381352
	.string "{WINDOW 0x04}"
		.string "心……だと？▼"
		.string "…………$"

.balign 4, 0
