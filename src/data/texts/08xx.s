.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_MissileFactory:: @ 0x08380724
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
  .2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
  .2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
  .2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start)

Text_MissileFactory:: @ 0x0838075e
Start:

Text0: @ 0x0838075E
	.string "{WINDOW 0x64}"
		.string "シエル:\n"
		.string "「よかった！ 無事だったのね！！▼"
	.string "{WINDOW 0x04}"
		.string "ミサイルのモクヒョウは、\n"
		.string "わかったか？▼"
	.string "{WINDOW 0x64}"
		.string "シエル:\n"
		.string "「あっ…えっと今……\n"
		.string " モクヒョウ…エリアZ…3079▼"
		.string "「なんてこと…！\n"
		.string " 人間の……きょじゅうくだわ！！▼"
		.string "「まって、それだけじゃない……\n"
		.string " その きょじゅうくに、\n"
		.string " ダークエルフがいるらしいわ！！▼"
	.string "{WINDOW 0x04}"
		.string "チョクセツのりこんで\n"
		.string "ダークエルフをとらえる気か…▼"
		.string "りょうかいした$"

Text1: @ 0x08380821
	.string "{WINDOW 0x04}"
		.string "ちっ…！$"

Text2: @ 0x08380828
	.string "{WINDOW 0x00}"
		.string "シエル「ハッシャされたのね！！▼"
		.string "ゼロ！ これ以上はキケンだわ！$"

Text3: @ 0x0838084C
	.string "{WINDOW 0x05}"
		.string "今ならオメガは動けない……▼"
		.string "後方からシンニュウして、\n"
		.string "ヤツごとミサイルをしとめる$"

Text4: @ 0x0838087B
	.string "{WINDOW 0x00}"
		.string "シエル「ゼローーー！！$"

Text5: @ 0x08380889
	.string "{WINDOW 0x04}"
		.string "ベビーエルフ…！？$"

Text6: @ 0x08380895
	.string "{WINDOW 0x66}"
		.string "やっぱりきたよ！\n"
		.string "わるいレプリロイドだ！$"

Text7: @ 0x083808AC
	.string "{WINDOW 0x69}"
		.string "やっぱりきたね！\n"
		.string "わるいレプリロイドめ！$"

Text8: @ 0x083808C3
	.string "{WINDOW 0x66}"
		.string "オメガにーちゃんは\n"
		.string "おかーさんを\n"
		.string "たすけにいくんだ！▼"
		.string "じゃまするな！\n"
		.string "あっちいけぇー！$"

Text9: @ 0x083808F1
	.string "{WINDOW 0x69}"
		.string "オメガにーちゃんを\n"
		.string "オマエから\n"
		.string "まもるんだ！▼"
		.string "じゃまするな！\n"
		.string "あっちいけぇー！！$"

Text10: @ 0x0838091C
	.string "{WINDOW 0x66}"
		.string "あはははっ！ おじーちゃん\n"
		.string "ほめてくれるかなぁ？▼"
	.string "{WINDOW 0x69}"
		.string "うふふふっ！ おじーちゃん\n"
		.string "きっと ほめてくれるよー$"

Text11: @ 0x08380954
	.string "{WINDOW 0x66}"
		.string "うわぁぁんっ！\n"
		.string "ひどいよー！$"

Text12: @ 0x08380965
	.string "{WINDOW 0x69}"
		.string "やあぁぁんっ！\n"
		.string "いたいよー！$"

Text13: @ 0x08380976
	.string "{WINDOW 0x66}"
		.string "まけちゃったけど\n"
		.string "もうすぐミサイル おちちゃうよ！\n"
		.string "さくせんセイコウだね！$"

Text14: @ 0x0838099E
	.string "{WINDOW 0x69}"
		.string "まけちゃったけど\n"
		.string "もうすぐ おかーさんにあえるよ！\n"
		.string "さくせんセイコウだね！▼"
	.string "{WINDOW 0x04}"
		.string "くっ…！$"

Text15: @ 0x083809CD
	.string "{WINDOW 0x3C}"
		.string "グ…オオ…！$"

Text16: @ 0x083809D6
	.string "{WINDOW 0x66}"
		.string "わーい！\n"
		.string "おかーさん！ おかーさん！$"

Text17: @ 0x083809EB
	.string "{WINDOW 0x69}"
		.string "わーい！\n"
		.string "おかーさん！ おかーさん！$"

Text18: @ 0x08380A00
	.string "{WINDOW 0x3D}"
		.string "グ…オオオオオオオオッ！$"

Text19: @ 0x08380A0F
	.string "{WINDOW 0x3F}"
		.string "グ…オオオオオオオオッ！$"

Text20: @ 0x08380A1E
	.string "{WINDOW 0x66}"
		.string "ついでに わるいレプリロイドも\n"
		.string "やっつけちゃえー$"

Text21: @ 0x08380A39
	.string "{WINDOW 0x69}"
		.string "ついでに ニセモノレプリロイドも\n"
		.string "やっつけちゃえー$"

Text22: @ 0x08380A55
	.string "{WINDOW 0x2C}"
		.string "……………▼"
		.string "われらネオ・アルカディアの\n"
		.string "レプリロイドは…▼"
		.string "人間を守る……\n"
		.string "この地上のユイイツのセイギ▼"
		.string "これが…\n"
		.string "このハイキョが…\n"
		.string "キサマらの セイギかーっ！▼"
		.string "バイルーーーッ！$"

Text23: @ 0x08380AB4
	.string "{WINDOW 0x2C}"
		.string "ぐあああああっ…！▼"
		.string "くっ…オレは…オレは…っ！$"

Text24: @ 0x08380ACE
	.string "{WINDOW 0x04}"
		.string "ハルピュイア！$"

Text25: @ 0x08380AD8
	.string "{WINDOW 0x66}"
		.string "いいぞいいぞー！$"

Text26: @ 0x08380AE3
	.string "{WINDOW 0x69}"
		.string "やっちゃえやっちゃえー！$"

Text27: @ 0x08380AF2
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ、動かないで！▼"
		.string "今ベースへ転送するわ！！$"

Text28: @ 0x08380B13
	.string "{WINDOW 0x00}"
		.string "オペレーター「転送！$"

.balign 4, 0
