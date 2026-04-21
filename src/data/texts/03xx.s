.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SpaceCraft:: @ 0x0837f00c
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
  .2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
  .2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
  .2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start), (Text29-Start), (Text30-Start), (Text31-Start)
  .2byte (Text32-Start), (Text33-Start), (Text34-Start), (Text35-Start), (Text36-Start), (Text37-Start), (Text38-Start), (Text39-Start)
  .2byte (Text40-Start), (Text41-Start), (Text42-Start), (Text43-Start), (Text44-Start), (Text45-Start), (Text46-Start), (Text47-Start)
  .2byte (Text48-Start), (Text49-Start), (Text50-Start)

Text_SpaceCraft:: @ 0x0837f072
Start:

Text0: @ 0x0837F072
	.string "{WINDOW 0x6C}"
		.string "しずかだな…▼"
		.string "最近…\n"
		.string "ネオ・アルカディアのコウゲキも\n"
		.string "ほとんどないし…▼"
		.string "まったく…\n"
		.string "平和になったもんだ▼"
	.string "{WINDOW 0x6D}"
		.string "シエルさんがケンキュウしていた\n"
		.string "新エネルギーも\n"
		.string "ついにカンセイしたし…▼"
		.string "これでエネルギー不足が\n"
		.string "カイショウしたら…▼"
		.string "ネオ・アルカディアも\n"
		.string "オレたちと戦う理由がなくなる…\n"
		.string "ってもんだよな ▼"
	.string "{WINDOW 0x40}"
		.string "じつはね……▼"
		.string "新エネルギー…\n"
		.string "システマ・シエルのこと▼"
		.string "ネオ・アルカディアに\n"
		.string "伝えてみたのよ…▼"
		.string "ヘンジは…▼"
		.string "まだ、だけど…ね▼"
	.string "{WINDOW 0x6C}"
		.string "だいじょうぶですって！\n"
		.string "もうすぐヘンジがきますよ！！▼"
		.string "もう、戦う理由がなくなった\n"
		.string "これからは、ともに生きよう……▼"
		.string "ってね！▼"
	.string "{WINDOW 0x05}"
		.string "作戦行動中だ……▼"
		.string "だまって…あるけ……▼"
	.string "{WINDOW 0x40}"
		.string "ご、ごめんなさい$"

Text1: @ 0x0837F1BE
	.string "{WINDOW 0x40}"
		.string "ハンノウが強くなってきたわ\n"
		.string "このあたりのはずなんだけど…$"

Text2: @ 0x0837F1DE
	.string "{WINDOW 0x6D}"
		.string "ユキがはれてきたな…$"

Text3: @ 0x0837F1EB
	.string "{WINDOW 0x6C}"
		.string "お、おい…！▼"
		.string "あれを見ろ！！$"

Text4: @ 0x0837F1FD
	.string "{WINDOW 0x05}"
		.string "これは…フネ…か？$"

Text5: @ 0x0837F209
	.string "{WINDOW 0x6C}"
		.string "シエルさん…▼"
		.string "あんな…ばかでかいものが……\n"
		.string "ウチュウから\n"
		.string "おちてきたのですか！？▼"
	.string "{WINDOW 0x41}"
		.string "ええ…それも…▼"
		.string "この世界に \n"
		.string "たったひとりしかいないはずの\n"
		.string "ダークエルフと…▼"
		.string "同じエネルギーはんのうを\n"
		.string "出しながら…ね……▼"
		.string "ゼロには、ハンタイされたけど…\n"
		.string "どうしても \n"
		.string "この目で たしかめてみたかったの…▼"
		.string "この世界に……いったい…\n"
		.string "何がおきようとしているのか$"

Text6: @ 0x0837F2C0
	.string "{WINDOW 0x05}"
		.string "ここからさきに\n"
		.string "ネオ・アルカディアの\n"
		.string "ケイカイセンがはってある……▼"
	.string "{WINDOW 0x40}"
		.string "なんですって！？▼"
	.string "{WINDOW 0x05}"
		.string "オレがルートをカクホするまで\n"
		.string "オマエたちは、\n"
		.string "ここでタイキしろ……▼"
	.string "{WINDOW 0x40}"
		.string "わかったわ……\n"
		.string "気をつけてね…ゼロ……$"

Text7: @ 0x0837F32A
	.string "{WINDOW 0x04}"
		.string "このおく……か、▼"
		.string "ダークエルフのハンノウが\n"
		.string "あったのは……$"

Text8: @ 0x0837F34A
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}アイツは…\n"
		.string "オレのことを 知っていた…▼"
		.string "世界をほろぼしかけたエルフが\n"
		.string "なぜオレのことを…$"

Text9: @ 0x0837F37D
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ？ 聞こえる？$"

Text10: @ 0x0837F38E
	.string "{WINDOW 0x04}"
		.string "つうしんヘイサだ！▼"
		.string "テキが近い……$"

Text11: @ 0x0837F3A3
	.string "{WINDOW 0x41}"
		.string "えっ、ご、ごめんなさい……$"

Text12: @ 0x0837F3B3
	.string "{WINDOW 0x6C}"
		.string "ふせて！！$"

Text13: @ 0x0837F3BB
Text14: @ 0x0837F3BB
	.string "{WINDOW 0x6C}"
		.string "ネオ・アルカディアか！▼"
	.string "{WINDOW 0x6D}"
		.string "シエルさん！ さがって！$"

Text15: @ 0x0837F3D8
	.string "{WINDOW 0x04}"
		.string "ちっ…$"

Text16: @ 0x0837F3DE
	.string "{WINDOW 0x2D}"
		.string "安心しろ\n"
		.string "イノチまではとらん▼"
	.string "{WINDOW 0x04}"
		.string "ハルピュイア…！▼"
	.string "{WINDOW 0x2D}"
		.string "今回は見のがしてやる▼"
		.string "レジスタンスともども…\n"
		.string "今すぐここから たち去れ！▼"
	.string "{WINDOW 0x04}"
		.string "見のがす…だと？$"

Text17: @ 0x0837F434
	.string "{WINDOW 0x2D}"
		.string "さっさと消えろ▼"
		.string "今は、オマエたちに\n"
		.string "かまっているバアイじゃないんだ…$"

Text18: @ 0x0837F45B
	.string "{WINDOW 0x04}"
		.string "………$"

Text19: @ 0x0837F461
	.string "{WINDOW 0x00}"
		.string "シエル「ゼ…ゼロ▼"
		.string "聞こえる…かしら……？$"

Text20: @ 0x0837F479
	.string "{WINDOW 0x04}"
		.string "無事だったようだな…▼"
		.string "ここからさきは…\n"
		.string "オレだけでやらせてもらう▼"
		.string "オマエたちは、\n"
		.string "レジスタンスベースにもどれ$"

Text21: @ 0x0837F4B4
	.string "{WINDOW 0x00}"
		.string "シエル「で、でも……$"

Text22: @ 0x0837F4C1
	.string "{WINDOW 0x04}"
		.string "この声…\n"
		.string "前にも どこかで………$"

Text23: @ 0x0837F4D6
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}オレを…\n"
		.string "呼んでいるのか…？$"

Text24: @ 0x0837F4E9
	.string "{WINDOW 0x2F}"
		.string "きゃああああっ…！$"

Text25: @ 0x0837F4F5
	.string "{WINDOW 0x31}"
		.string "やりやがったな！$"

Text26: @ 0x0837F500
	.string "{WINDOW 0x31}"
		.string "ふっとびやがれえっ！$"

Text27: @ 0x0837F50D
	.string "{WINDOW 0x31}"
		.string "グオオオオッ！$"

Text28: @ 0x0837F517
	.string "{WINDOW 0x2F}"
		.string "{BOTTOM}はあ…はあ…▼"
		.string "生きてる…？\n"
		.string "ファーブニル…▼"
	.string "{WINDOW 0x30}"
		.string "{BOTTOM}まったくバケモンだぜ…▼"
		.string "オレたちふたりがかりで\n"
		.string "キズひとつ\n"
		.string "つかねえなんて…な…▼"
	.string "{WINDOW 0x2F}"
		.string "{BOTTOM}ネオ・アルカディアをツイホウされた\n"
		.string "アクマのレプリロイド…オメガ…▼"
		.string "ケッコウやるわね…$"

Text29: @ 0x0837F58C
	.string "{WINDOW 0x30}"
		.string "…ゼロ！？▼"
		.string "なんでテメーがここに…！？▼"
	.string "{WINDOW 0x05}"
		.string "ヤツは何者だ？$"

Text30: @ 0x0837F5AE
	.string "{WINDOW 0x2E}"
		.string "アイツは、オメガ……\n"
		.string "そんざいジタイが\n"
		.string "デタラメなヤツ………▼"
		.string "強いんだけど…▼"
		.string "戦ってもなんだか もえないのよね\n"
		.string "あなたとちがって…ふふ……▼"
		.string "気がのらないから\n"
		.string "あとは…あなたにまかせるわ……▼"
		.string "またね…ゼロ……$"

Text31: @ 0x0837F61B
	.string "{WINDOW 0x30}"
		.string "ちっ、レヴィアタンめ…▼"
		.string "くそっ、体がいうことをきかねえ…\n"
		.string "今日のところは出なおしだ…！▼"
		.string "おい…ゼロ！▼"
		.string "テメエもオメガも…\n"
		.string "いつかかならず…ぶっころす！▼"
		.string "それまで死ぬんじゃねーぞ…\n"
		.string "ゼロ……！$"

Text32: @ 0x0837F682
	.string "{WINDOW 0x04}"
		.string "オメガとか言ったな…▼"
		.string "オマエか…\n"
		.string "オレを呼んでいたのは…$"

Text33: @ 0x0837F6A3
	.string "{WINDOW 0x3D}"
		.string "グ…オオ……！$"

Text34: @ 0x0837F6AD
	.string "{WINDOW 0x04}"
		.string "ちっ…\n"
		.string "しぶといヤツだ$"

Text35: @ 0x0837F6BB
	.string "{WINDOW 0x2C}"
		.string "オマエがオメガ…か…▼"
		.string "オマエのようなものを\n"
		.string "ここから出すわけにはいかん▼"
		.string "ここで…ハカイする！！$"

Text36: @ 0x0837F6EE
	.string "{WINDOW 0x3D}"
		.string "グオオオオオッ！$"

Text37: @ 0x0837F6F9
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…▼"
		.string "オメガよ…\n"
		.string "そのくらいにしておけ$"

Text38: @ 0x0837F717
	.string "{WINDOW 0x3B}"
		.string "オマエは今日から…▼"
		.string "ネオ・アルカディアの\n"
		.string "メンバーとして\n"
		.string "この方と ともに戦うのだ…▼"
		.string "仲間になる者を\n"
		.string "ころしてしまっては、\n"
		.string "いごこちも悪かろう…$"

Text39: @ 0x0837F76A
	.string "{WINDOW 0x3D}"
		.string "グ…オオ…\n"
		.string "バイル…サマ…▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}ネオ・アルカディアの…\n"
		.string "メンバーだと！？▼"
		.string "何者だ！？$"

Text40: @ 0x0837F79A
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}クーックックックッ…▼"
		.string "わが名はバイル…\n"
		.string "ドクター・バイルだ…▼"
		.string "名前くらいは聞いたことがあろう？\n"
		.string "四天王ハルピュイア▼"
		.string "そして…伝説のエイユウ▼"
		.string "ゼロ……▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}ドクター・バイル…だと！？▼"
		.string "バカな！ ありえん！▼"
		.string "100年前にネオ・アルカディアを\n"
		.string "ツイホウされたはずのオマエが\n"
		.string "なぜオメガを！？▼"
	.string "{WINDOW 0x37}"
		.string "{BOTTOM}ボくが…▼"
		.string "よンだのサ…$"

Text41: @ 0x0837F847
	.string "{WINDOW 0x2C}"
		.string "エ…\n"
		.string "エックス…さま！？$"

Text42: @ 0x0837F856
	.string "{WINDOW 0x37}"
		.string "ギギッ…ハルピュイアか\n"
		.string "フフ…かわりない…な▼"
		.string "そしテ……▼"
		.string "会いタかッたよ……ゼロ$"

Text43: @ 0x0837F882
	.string "{WINDOW 0x04}"
		.string "オマエ……\n"
		.string "コピーだな……▼"
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}クックックッ……▼"
		.string "かつてオマエに\n"
		.string "たおされたエックスさまを\n"
		.string "このワシが よみがえらせた…▼"
		.string "コントンとした この世界から\n"
		.string "人間を守るためにな！▼"
	.string "{WINDOW 0x37}"
		.string "{TOP}バイルは…\n"
		.string "ぼクの いのチのおんじンなのサ…▼"
		.string "オメガは、かいしゅうスる…▼"
		.string "ハルピュイア\n"
		.string "おマえはひき続き\n"
		.string "ダークエルフのそうさくにアたレ▼"
		.string "オメガとダークエルフ…▼"
		.string "ふたつとも、\n"
		.string "これカらのボくたちに\n"
		.string "ひつヨウなものだからネ…$"

Text44: @ 0x0837F955
	.string "{WINDOW 0x2C}"
		.string "し…しかし！ エックスさま！▼"
		.string "このオトコが作った\n"
		.string "ダークエルフとオメガのせいで…\n"
		.string "どれだけ多くの人間が死んだか…▼"
		.string "新エネルギーがカンセイし\n"
		.string "エネルギーもんだいが\n"
		.string "カイケツするかもしれない時に…▼"
		.string "人間をキケンにさらすようなことは、\n"
		.string "おやめください！▼"
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}エックスさまにイケンをするのか？\n"
		.string "ハルピュイア…▼"
		.string "いつからそんなに、\n"
		.string "えらくなった$"

Text45: @ 0x0837FA09
	.string "{WINDOW 0x2C}"
		.string "{TOP}くっ…バイル……▼"
	.string "{WINDOW 0x37}"
		.string "サて…ゼロ▼"
		.string "キミたちも…ダークエルフを\n"
		.string "サがしてイるんだろウ？\n"
		.string "きょうそうと いコウじゃないか！▼"
		.string "ギッ…ギギギッ…！\n"
		.string "こんどは まケないヨ…！▼"
		.string "ボクこそガ…\n"
		.string "本当のエイユウなんダからネ！$"

Text46: @ 0x0837FA77
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}クーックックックッ…\n"
		.string "たのしくなってきたな、ゼロ！▼"
		.string "そのカラダでどこまでできるか…\n"
		.string "見せてもらうとしよう！\n"
		.string "クックックッ…$"

Text47: @ 0x0837FAB9
	.string "{WINDOW 0x04}"
		.string "そのカラダ…だと…？▼"
		.string "………$"

Text48: @ 0x0837FACA
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ……▼"
		.string "タイヘンなことになったわね……$"

Text49: @ 0x0837FAE5
	.string "{WINDOW 0x04}"
		.string "モニターしていたのか……$"

Text50: @ 0x0837FAF4
	.string "{WINDOW 0x00}"
		.string "シエル「すぐにベースへもどってきて……▼"
		.string "オペレーターさん…おねがい▼"
	.string "{WINDOW 0x00}"
		.string "オペレーター「転送をカイシします$"

.balign 4, 0
