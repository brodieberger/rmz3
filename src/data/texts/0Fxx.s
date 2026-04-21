.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SunkenLibrary:: @ 0x083817f0
	.2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
	.2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
	.2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
	.2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start)

Text_SunkenLibrary:: @ 0x0838182a
Start:

Text0: @ 0x0838182A
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「まずはデータルームへ\n"
		.string " 行ってください▼"
		.string "「バイルやオメガの\n"
		.string " ジョウホウがあるカノウセイは…\n"
		.string " そこがもっとも高そうです$"

Text1: @ 0x08381874
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「ここがデータルームです…▼"
		.string "「そこのコンソールで…\n"
		.string " バイルのことを\n"
		.string " ケンサクおねがいします▼"
		.string "「ケンサクすると…\n"
		.string " データがおさめられたエリアが\n"
		.string " ひょうじされるはずです▼"
		.string "「そのエリアへ行って\n"
		.string " データをカイシュウして\n"
		.string " いただけませんか？$"

Text2: @ 0x083818F9
	.string "{WINDOW 0x00}"
		.string "モニターの前で✚ボタンの上をおしてください$"

Text3: @ 0x08381914
	.string "{WINDOW 0x04}"
		.string "ガイトウするデータが4つ…▼"
		.string "バイル、オメガ、ダークエルフ\n"
		.string "ヨウセイ戦争……$"

Text4: @ 0x0838193E
	.string "{WINDOW 0x04}"
		.string "のこりのデータは3つ…$"

Text5: @ 0x0838194C
	.string "{WINDOW 0x04}"
		.string "のこりのデータは2つ…$"

Text6: @ 0x0838195A
	.string "{WINDOW 0x04}"
		.string "サイゴのデータか…$"

Text7: @ 0x08381966
	.string "{WINDOW 0x6A}"
		.string "ドノ データヲ サーチ シマスカ？$"

Text8: @ 0x0838197A
	.string "{WINDOW 0x6A}"
		.string "バイル ノ データガ アル\n"
		.string "エリアヲ サーチシマシタ▼"
		.string "サイド ジョウホウガ\n"
		.string "ヒツヨウナ トキハ\n"
		.string "コンソールヲ シラベテクダサイ$"

Text9: @ 0x083819BC
	.string "{WINDOW 0x6A}"
		.string "オメガ ノ データガ アル\n"
		.string "エリアヲ サーチシマシタ▼"
		.string "サイド ジョウホウガ\n"
		.string "ヒツヨウナ トキハ\n"
		.string "コンソールヲ シラベテクダサイ$"

Text10: @ 0x083819FE
	.string "{WINDOW 0x6A}"
		.string "ダークエルフ ノ データガ アル\n"
		.string "エリアヲ サーチシマシタ▼"
		.string "サイド ジョウホウガ\n"
		.string "ヒツヨウナ トキハ\n"
		.string "コンソールヲ シラベテクダサイ$"

Text11: @ 0x08381A43
	.string "{WINDOW 0x6A}"
		.string "ヨウセイ戦争 ノ データガ アル\n"
		.string "エリアヲ サーチシマシタ▼"
		.string "サイド ジョウホウガ\n"
		.string "ヒツヨウナ トキハ\n"
		.string "コンソールヲ シラベテクダサイ$"

Text12: @ 0x08381A8A
	.string "{WINDOW 0x23}"
		.string "…だ…だれだ…\n"
		.string "オレの…なわばりに\n"
		.string "……来たヤツは…▼"
		.string "…ゼ…ゼロ…！ひっ…ひひっ！\n"
		.string "そうか…オマエか…！\n"
		.string "ひひっ…！$"

Text13: @ 0x08381AC8
	.string "{WINDOW 0x13}"
		.string "オレは…バイル・ナンバーズ…\n"
		.string "ヴォルティール・ビブリーオ▼"
		.string "なんだ…その手にもっているのは…\n"
		.string "そのデータ…かえせ…\n"
		.string "かえせぇぇぇっ！$"

Text14: @ 0x08381B0D
	.string "{WINDOW 0x12}"
		.string "ひひひひひひっ！▼"
		.string "わたさないっ…このデータ…\n"
		.string "わたさないっ！ ひひっ！$"

Text15: @ 0x08381B33
	.string "{WINDOW 0x12}"
		.string "なんだ…なんなんだオマエ…！▼"
		.string "バイルさまにさからうのが…\n"
		.string "こわくないのか…！？▼"
		.string "い…いかれてる！▼"
		.string "ひゃあああああああっ！$"

Text16: @ 0x08381B72
	.string "{WINDOW 0x00}"
		.string "オペレーター「ミッションしゅうりょう▼"
		.string "転送をカイシします$"

Text17: @ 0x08381B93
	.string "{WINDOW 0x00}"
		.string "バイルのデータをゲットした！$"

Text18: @ 0x08381BA4
	.string "{WINDOW 0x00}"
		.string "オメガのデータをゲットした！$"

Text19: @ 0x08381BB5
	.string "{WINDOW 0x00}"
		.string "ダークエルフのデータをゲットした！$"

Text20: @ 0x08381BC9
	.string "{WINDOW 0x00}"
		.string "ヨウセイ戦争のデータをゲットした！$"

Text21: @ 0x08381BDF
	.string "{WINDOW 0x04}"
		.string "ファイルナンバー650326\n"
		.string "--ドクター・バイル--▼"
		.string "ネオ・アルカディアしょぞく……▼"
		.string "オメガのセイサクシャ…▼"
		.string "マザーエルフを改造し\n"
		.string "ヨウセイ戦争をひきおこす…▼"
		.string "ヨウセイ戦争でのセキニンをとわれ\n"
		.string "ネオ・アルカディアを\n"
		.string "ツイホウされる…$"

Text22: @ 0x08381C5D
	.string "{WINDOW 0x04}"
		.string "このデータをカイセキすれば、\n"
		.string "バイルについて さらにジョウホウが\n"
		.string "手に入るかもしれない………$"

Text23: @ 0x08381C90
	.string "{WINDOW 0x04}"
		.string "ファイルナンバー815156\n"
		.string "--オメガ--▼"
		.string "ドクター・バイルに作られた\n"
		.string "キュウキョクのレプリロイド…▼"
		.string "ダークエルフと\n"
		.string "くみあわせることにより\n"
		.string "おそろしいチカラをハッキする▼"
		.string "ヨウセイ戦争のヒゲキを\n"
		.string "くりかえさぬため…\n"
		.string "ウチュウへツイホウされる……$"

Text24: @ 0x08381D11
	.string "{WINDOW 0x04}"
		.string "このデータをカイセキすれば、\n"
		.string "オメガについて さらにジョウホウが\n"
		.string "手に入るかもしれない………$"

Text25: @ 0x08381D44
	.string "{WINDOW 0x04}"
		.string "ファイルナンバー351848\n"
		.string "--ダークエルフ--▼"
		.string "セイシキメイショウ マザーエルフ\n"
		.string "セイサクシャ不明▼"
		.string "もともと……\n"
		.string "イレギュラープログラムを\n"
		.string "もとにもどし………▼"
		.string "イレギュラーを\n"
		.string "すくうために作られた…\n"
		.string "サイバーエルフであったが……▼"
		.string "レプリロイドをあやつるため…\n"
		.string "プログラムを自由に\n"
		.string "かきかえることができるよう……▼"
		.string "ドクター・バイルによって\n"
		.string "改造された………▼"
		.string "改造されたマザーエルフに\n"
		.string "あやつられたレプリロイドが\n"
		.string "ソシキ的に戦うことにより…▼"
		.string "戦争は…\n"
		.string "シュウケツをむかえたが…▼"
		.string "その強大な力が\n"
		.string "悪用されることをおそれ\n"
		.string "ふういんされる$"

Text26: @ 0x08381E63
	.string "{WINDOW 0x04}"
		.string "ダークエルフ…か…\n"
		.string "アイツはいったい……▼"
		.string "……▼"
		.string "このデータをカイセキすれば、\n"
		.string "アイツについて 他にも何か\n"
		.string "わかるかもしれない………$"

Text27: @ 0x08381EA9
	.string "{WINDOW 0x04}"
		.string "ファイルナンバー945388\n"
		.string "--ヨウセイ戦争--▼"
		.string "………………戦争の終わり……\n"
		.string "サイバーエルフ………………\n"
		.string "使用され………………▼"
		.string "これ以後………………\n"
		.string "ヨウセイ戦争………………▼"
		.string "…………ダークエルフ…\n"
		.string "………………と…▼"
		.string "そのコピーである………………\n"
		.string "使用に………………▼"
		.string "………………チカラを\n"
		.string "ゾウフク……▼"
		.string "同時に………………\n"
		.string "………………することが\n"
		.string "カノウに………からは……▼"
		.string "………………の……\n"
		.string "最悪の………………▼"
		.string "戦争は、………………\n"
		.string "………シュウケツ……▼"
		.string "………………ほぼ90%……▼"
		.string "…………………した……$"

Text28: @ 0x08381FBF
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ…？▼"
		.string "どうやらデータがこわれているみたいね…▼"
		.string "多分、ベースでなら▼"
		.string "シュウフクできると…思うわ……▼"
		.string "ありがとう…ゼロ…$"

.balign 4, 0
