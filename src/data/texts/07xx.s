.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_OldLifeSpace:: @ 0x08380114
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
  .2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
  .2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
  .2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start), (Text29-Start), (Text30-Start), (Text31-Start)
  .2byte (Text32-Start), (Text33-Start), (Text34-Start), (Text35-Start), (Text36-Start), (Text37-Start), (Text38-Start), (Text39-Start)
  .2byte (Text40-Start)

Text_OldLifeSpace:: @ 0x08380166
Start:

Text0: @ 0x08380166
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「ゼロさん！▼"
		.string "「ところどころにはえているツタは\n"
		.string " ホノオぞくせいのコウゲキで\n"
		.string " もやすことができます▼"
		.string "「また、リコイルロッドの\n"
		.string " チャージこうげきで\n"
		.string " こわせるところも あるようです▼"
		.string "「ちゅういしてください$"

Text1: @ 0x083801D8
	.string "{WINDOW 0x0D}"
		.string "このうつくしきカマに\n"
		.string "きれないものは ない…！▼"
		.string "ギチギチギチギチィィィッ！$"

Text2: @ 0x08380200
	.string "{WINDOW 0x0C}"
		.string "ギチギチッ…▼"
		.string "たとえオレが\n"
		.string "ここでたおれても…▼"
		.string "仲間が…必ず……\n"
		.string "世界をしばる…古き…くさりを…\n"
		.string "たちきってくれるはず……▼"
		.string "新しい世界を…\n"
		.string "新しいチツジョを…！\n"
		.string "バ…バイルさまーーーーーーっ！$"

Text3: @ 0x0838026D
Text4: @ 0x0838026D
	.string "{WINDOW 0x66}"
		.string "おかーさーん\n"
		.string "おかーさーん$"

Text5: @ 0x0838027D
	.string "{WINDOW 0x66}"
		.string "ねえ プリエ\n"
		.string "ここにも おかーさん いないね$"

Text6: @ 0x08380296
	.string "{WINDOW 0x69}"
		.string "そうだね クリエ\n"
		.string "ここにも おかーさん いないね$"

Text7: @ 0x083802B1
	.string "{WINDOW 0x66}"
		.string "ねえ プリエ\n"
		.string "もっとおくを さがしてみようか$"

Text8: @ 0x083802CA
	.string "{WINDOW 0x69}"
		.string "そうだね クリエ\n"
		.string "もっとおくをさがしてみようよ$"

Text9: @ 0x083802E4
	.string "{WINDOW 0x04}"
		.string "………▼"
		.string "あれは…たしか…$"

Text10: @ 0x083802F3
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ…！▼"
		.string "あなたにもっていってもらった▼"
		.string "ケイタイ用スキャンに… ベビーエルフのハンノウが！▼"
		.string "わたしが前に ケンキュウしていたベビーエルフと▼"
		.string "同じコかもしれないわ……$"

Text11: @ 0x0838034F
	.string "{WINDOW 0x04}"
		.string "ははおやを…▼"
		.string "ダークエルフを\n"
		.string "さがしているようだったな$"

Text12: @ 0x0838036D
	.string "{WINDOW 0x00}"
		.string "シエル「ねえ、ゼロ…▼"
		.string "あのコたちを ホゴできないかしら…$"

Text13: @ 0x0838038C
	.string "{WINDOW 0x04}"
		.string "わかった…▼"
		.string "あとをおう$"

Text14: @ 0x0838039A
	.string "{WINDOW 0x00}"
		.string "シエル「ありがとう…ゼロ$"

Text15: @ 0x083803A9
	.string "{WINDOW 0x66}"
		.string "あなたは だあれ？▼"
		.string "おかーさんと おなじニオイが\n"
		.string "するよ$"

Text16: @ 0x083803C8
	.string "{WINDOW 0x69}"
		.string "あなたは だあれ？▼"
		.string "わたしたちと おなじニオイが\n"
		.string "するよ$"

Text17: @ 0x083803E7
	.string "{WINDOW 0x1D}"
		.string "ギチギチギチ…▼"
		.string "コイツらがベビーエルフか…▼"
		.string "バイルさまのめいれいで\n"
		.string "コイツらを さがしにきたが…▼"
		.string "ホントにガキのエルフじゃねえか…\n"
		.string "こんなヤツら、やくにたつのか？$"

Text18: @ 0x0838043B
	.string "{WINDOW 0x04}"
		.string "…ベビーエルフを\n"
		.string "わたせ$"

Text19: @ 0x0838044A
	.string "{WINDOW 0x66}"
		.string "あ！ あいつ しってるよ！▼"
		.string "こないだ おかーさんを\n"
		.string "いじめた やつだ！$"

Text20: @ 0x08380470
	.string "{WINDOW 0x69}"
		.string "わたしも あいつ しってるよ！▼"
		.string "100ねんまえも おかーさんを\n"
		.string "いじめた やつだ！$"

Text21: @ 0x0838049C
	.string "{WINDOW 0x66}"
		.string "ニセモノのくせにー！$"

Text22: @ 0x083804A9
	.string "{WINDOW 0x69}"
		.string "ニセモノのくせにー！$"

Text23: @ 0x083804B6
	.string "{WINDOW 0x04}"
		.string "…？▼"
	.string "{WINDOW 0x1D}"
		.string "ギチギチッ…\n"
		.string "うるせえぞ\n"
		.string "ベビーエルフども！▼"
		.string "ブッたギられたくなかったら\n"
		.string "おくのへやに ひっこんでろ！！$"

Text24: @ 0x083804F2
	.string "{WINDOW 0x66}"
		.string "うわぁぁぁん$"

Text25: @ 0x083804FB
	.string "{WINDOW 0x69}"
		.string "うわぁぁぁん$"

Text26: @ 0x08380504
	.string "{WINDOW 0x1D}"
		.string "アイツらはバイルさまのもんだ…\n"
		.string "テメエなんかには\n"
		.string "わたさねえよ…！$"

Text27: @ 0x08380528
	.string "{WINDOW 0x0D}"
		.string "オレはバイル・ナンバーズがひとり\n"
		.string "デスタンツ・マンティスク▼"
		.string "テメエはオレが\n"
		.string "きりきざんでやるよ！$"

Text28: @ 0x0838055B
	.string "{WINDOW 0x66}"
		.string "おじちゃんは だあれ？▼"
		.string "みたこと あるような\n"
		.string "きがするよ$"

Text29: @ 0x0838057A
	.string "{WINDOW 0x69}"
		.string "おじちゃんは だあれ？▼"
		.string "わたしも みたことある\n"
		.string "きがするよ$"

Text30: @ 0x0838059A
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…\n"
		.string "ワシの名はバイル…▼"
		.string "オマエたちの ははおや\n"
		.string "ダークエルフを作ったのは\n"
		.string "このワシじゃ▼"
		.string "いわば オマエたちの\n"
		.string "おじいさん という\n"
		.string "ところじゃな$"

Text31: @ 0x083805EF
	.string "{WINDOW 0x66}"
		.string "きいた？ プリエ！▼"
		.string "わたしたちの おじーちゃん\n"
		.string "だって！$"

Text32: @ 0x0838060E
	.string "{WINDOW 0x69}"
		.string "きいた！ クリエ！▼"
		.string "わたしたちの おじーちゃん\n"
		.string "だって！$"

Text33: @ 0x0838062D
	.string "{WINDOW 0x3B}"
		.string "ワシも ダークエルフを\n"
		.string "さがしておる▼"
		.string "オマエたちの\n"
		.string "チカラをかしておくれ▼"
		.string "ワシといっしょに\n"
		.string "ネオ・アルカディアへ\n"
		.string "来るといい▼"
		.string "新しいチカラとカラダを…\n"
		.string "あたえてやろう$"

Text34: @ 0x08380685
	.string "{WINDOW 0x66}"
		.string "よし！ いこう！ プリエ！$"

Text35: @ 0x08380695
	.string "{WINDOW 0x69}"
		.string "うん！ いこう！ クリエ！$"

Text36: @ 0x083806A5
	.string "{WINDOW 0x04}"
		.string "まてっ！$"

Text37: @ 0x083806AC
	.string "{WINDOW 0x04}"
		.string "ちっ……▼"
		.string "シエル\n"
		.string "ヤツらのハンノウを\n"
		.string "おえるか？$"

Text38: @ 0x083806C7
	.string "{WINDOW 0x00}"
		.string "シエル「ごめんなさい…▼"
		.string "そのケイタイ用スキャンでは、ちょっと無理みたい…$"

Text39: @ 0x083806F1
	.string "{WINDOW 0x04}"
		.string "………$"

Text40: @ 0x083806F7
	.string "{WINDOW 0x00}"
		.string "オペレーター「ゼロさん… ベースへキカンしてください▼"
		.string "転送をカイシします…$"

.balign 4, 0
