.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SubArcadia:: @ 0x083820fc
	.2byte (Text0-Start),  (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
	.2byte (Text8-Start),  (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
	.2byte (Text16-Start), (Text17-Start)

Text_SubArcadia:: @ 0x08382120
Start:

Text0: @ 0x08382120
		.string "$"

Text1: @ 0x08382121
	.string "{WINDOW 0x04}"
		.string "ドクター・バイル…！$"

Text2: @ 0x0838212E
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…▼"
		.string "いさましいな…ゼロ…\n"
		.string "キサマひとりでエイユウごっこか？▼"
		.string "いまや世界中のレプリロイドは\n"
		.string "ワシの手の中にある…▼"
		.string "レプリロイドにたよらねば\n"
		.string "生きていけぬ\n"
		.string "ブタのような人間たちなど………▼"
		.string "その気になれば、\n"
		.string "いつでもシマツできるのだ▼"
		.string "わかっているな？$"

Text3: @ 0x083821BD
	.string "{WINDOW 0x53}"
		.string "クリエ！ プリエ！\n"
		.string "ソイツをすきにしていいぞ！▼"
		.string "ワシは、今から\n"
		.string "ブタどものヒメイを聞きに行く▼"
		.string "ダミンをむさぼり\n"
		.string "タイダに…ただ生きているだけの\n"
		.string "ブタどもに……▼"
		.string "世界のシハイシャが\n"
		.string "だれなのか…\n"
		.string "おしえてやる！▼"
		.string "クーックックックッ…▼"
		.string "クヒャーッハッハッハッハッ！$"

Text4: @ 0x08382248
	.string "{WINDOW 0x66}"
		.string "またきたー！\n"
		.string "わるいレプリロイドー！$"

Text5: @ 0x0838225D
	.string "{WINDOW 0x69}"
		.string "またきたー！\n"
		.string "ニセモノレプリロイドー！$"

Text6: @ 0x08382273
	.string "{WINDOW 0x66}"
		.string "おまえなんか\n"
		.string "バラバラにしてやるー！$"

Text7: @ 0x08382288
	.string "{WINDOW 0x69}"
		.string "おまえなんか\n"
		.string "ズタズタにしてやるー！$"

Text8: @ 0x0838229D
	.string "{WINDOW 0x66}"
		.string "あははははははっ！\n"
		.string "バラバラになったー！▼"
	.string "{WINDOW 0x69}"
		.string "うふふふふふふっ！\n"
		.string "ズタズタになったー！$"

Text9: @ 0x083822CB
	.string "{WINDOW 0x66}"
		.string "あれ…プリエ…\n"
		.string "なんだかへんだよ…$"

Text10: @ 0x083822DF
	.string "{WINDOW 0x69}"
		.string "うん…クリエ…\n"
		.string "なんだかへんだよ…$"

Text11: @ 0x083822F3
	.string "{WINDOW 0x66}"
		.string "からだが…いっぱ…い\n"
		.string "チクチク…す…るよ…$"

Text12: @ 0x0838230B
	.string "{WINDOW 0x69}"
		.string "か…らだが…いっぱ…い\n"
		.string "ズキ…ズキ…す…る…▼"
		.string "ミ…ミーーーーーーーッ！$"

Text13: @ 0x08382331
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ、だいじょうぶ？▼"
		.string "エックスから、新しいジョウホウをもらったわ▼"
		.string "…いちどレジスタンスベースにもどってきて…$"

Text14: @ 0x0838236F
	.string "{WINDOW 0x04}"
		.string "わかった…転送しろ$"

Text15: @ 0x0838237D
	.string "{WINDOW 0x33}"
		.string "…かような地で\n"
		.string "キサマと再び\n"
		.string "あいまみえるとはな▼"
		.string "オメガとやらの せいで\n"
		.string "サイバーくうかんへの\n"
		.string "トビラが 開いたのならば▼"
		.string "ウンメイとは ヒニクなもので\n"
		.string "ござる…▼"
	.string "{WINDOW 0x04}"
		.string "…ネオ・アルカディア\n"
		.string "四天王…ファントム！▼"
		.string "オマエは\n"
		.string "オレが たおしたはず…▼"
	.string "{WINDOW 0x33}"
		.string "ここは レプリロイドのタマシイと\n"
		.string "サイバーエルフたちが すむ\n"
		.string "はざまの世界…▼"
		.string "キサマにたおされた せっしゃは\n"
		.string "タマシイのみとなり、\n"
		.string "サイバーくうかんに たどりついた▼"
		.string "ありとあらゆる データが\n"
		.string "ながれつく このくうかん…▼"
		.string "そこで せっしゃは全てを知った▼"
		.string "オメガのこと…\n"
		.string "ダークエルフのこと…\n"
		.string "そしてゼロ…キサマのこと…▼"
		.string "そう…全てを だ▼"
	.string "{WINDOW 0x04}"
		.string "…何が言いたい？▼"
	.string "{WINDOW 0x33}"
		.string "もじどおり キサマは\n"
		.string "エイユウのウツワ\n"
		.string "ではなかったのだ▼"
		.string "見るにたえぬ そのすがた、\n"
		.string "せめて せっしゃの手で\n"
		.string "消し去ってくれよう！$"

Text16: @ 0x08382503
	.string "{WINDOW 0x32}"
		.string "いかに伝説といえど、\n"
		.string "いつかは わすれさられる…\n"
		.string "さらばだ！ ゼロ！$"

Text17: @ 0x0838252A
	.string "{WINDOW 0x32}"
		.string "くっ…▼"
		.string "…エイユウのタマシイ\n"
		.string "そのものは…いつわりでは\n"
		.string "なかったということか…▼"
		.string "…行け…▼"
		.string "行って オメガと ヤイバをまじえ、\n"
		.string "そのカラダで たしかめるがいい…！▼"
		.string "真実を知ってなお、\n"
		.string "そのヤイバをふるえるのか…\n"
		.string "キサマが エイユウたりえるのか…▼"
		.string "おのが目で 見きわめよ！$"
