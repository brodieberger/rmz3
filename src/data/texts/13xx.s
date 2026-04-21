.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_Others:: @ 0x083836cc
	.2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
	.2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
	.2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
	.2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start), (Text29-Start), (Text30-Start), (Text31-Start)
	.2byte (Text32-Start), (Text33-Start), (Text34-Start), (Text35-Start), (Text36-Start), (Text37-Start), (Text38-Start), (Text39-Start)
	.2byte (Text40-Start), (Text41-Start), (Text42-Start), (Text43-Start), (Text44-Start), (Text45-Start), (Text46-Start), (Text47-Start)
	.2byte (Text48-Start), (Text49-Start), (Text50-Start), (Text51-Start), (Text52-Start), (Text53-Start), (Text54-Start), (Text55-Start)
	.2byte (Text56-Start), (Text57-Start), (Text58-Start), (Text59-Start), (Text60-Start), (Text61-Start), (Text62-Start), (Text63-Start)
	.2byte (Text64-Start), (Text65-Start), (Text66-Start), (Text67-Start), (Text68-Start), (Text69-Start), (Text70-Start), (Text71-Start)
	.2byte (Text72-Start), (Text73-Start), (Text74-Start), (Text75-Start), (Text76-Start), (Text77-Start), (Text78-Start), (Text79-Start)
	.2byte (Text80-Start), (Text81-Start), (Text82-Start), (Text83-Start), (Text84-Start), (Text85-Start), (Text86-Start), (Text87-Start)
	.2byte (Text88-Start), (Text89-Start), (Text90-Start), (Text91-Start), (Text92-Start), (Text93-Start), (Text94-Start), (Text95-Start)
	.2byte (Text96-Start), (Text97-Start), (Text98-Start), (Text99-Start)

Text_Others:: @ 0x08383794
Start:

Text0: @ 0x08383794
	.string "{WINDOW 0x6C}"
		.string "シエルさん、ゲンキ出してください▼"
		.string "今までだって、\n"
		.string "なんとかなったじゃないですか！▼"
	.string "{WINDOW 0x6D}"
		.string "そうですよ…▼"
		.string "ボクたち\n"
		.string "シエルさんや ゼロさんのこと\n"
		.string "シンライしてますから！▼"
	.string "{WINDOW 0x40}"
		.string "あ…ありがとう、みんな………$"

Text1: @ 0x083837FB
	.string "{WINDOW 0x40}"
		.string "シミュレーションの\n"
		.string "ケッカが出るまで\n"
		.string "まだ時間がかかるみたい…▼"
		.string "またゼロに…\n"
		.string "色々おねがいしなければ\n"
		.string "いけなくなると思うの……▼"
		.string "それまで…少しだけでも\n"
		.string "カラダをやすめて…もらえるかしら▼"
		.string "とりあえず……$"

Text2: @ 0x08383869
		.string "今までのことをキロクしておくわね…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text3: @ 0x08383887
	.string "{WINDOW 0x40}"
		.string "データのカンリは、\n"
		.string "いつものように\n"
		.string "わたしがするわね▼"
		.string "何かあったら\n"
		.string "いつでも声をかけて…▼"
		.string "あっそうだ…\n"
		.string "セルヴォのところへ\n"
		.string "かおを出してあげて▼"
		.string "シークレットディスクの\n"
		.string "カイセキそうちが\n"
		.string "カンセイしたみたいなの▼"
		.string "ゼロじゃカイセキできない\n"
		.string "シークレットディスクは\n"
		.string "セルヴォに おねがいするといいわ$"

Text4: @ 0x0838391F
	.string "{WINDOW 0x40}"
		.string "やすまなくてヘイキ？\n"
		.string "無理はしないでね▼"
		.string "データのカンリは、\n"
		.string "いつものようにわたしがするわね\n"
		.string "何かあったらいつでも声をかけて▼"
		.string "あっそうだ…\n"
		.string "セルヴォのところへ\n"
		.string "かおを出してあげて▼"
		.string "シークレットディスクの\n"
		.string "カイセキそうちが\n"
		.string "カンセイしたみたいなの▼"
		.string "ゼロじゃカイセキできない\n"
		.string "シークレットディスクは\n"
		.string "セルヴォに おねがいするといいわ$"

Text5: @ 0x083839CA
	.string "{WINDOW 0x40}"
		.string "セルヴォには、もう会ったの？▼"
		.string "セルヴォったら、\n"
		.string "ディスクのカイセキそうちを\n"
		.string "はやく ためしてみたいそうよ$"

Text6: @ 0x08383A02
	.string "{WINDOW 0x6C}"
		.string "セルヴォのへやですか？▼"
		.string "シレイシツを 右へぬけて、\n"
		.string "手前のへやですよ▼"
		.string "ベースがベンリになるのは\n"
		.string "うれしいですけど…\n"
		.string "こうひろいと まよっちゃいますよね$"

Text7: @ 0x08383A53
	.string "{WINDOW 0x43}"
		.string "おお！ ゼロ！ 無事だったか！！▼"
		.string "話は聞いたぞ▼"
		.string "せっかく新エネルギーが\n"
		.string "カンセイしたというのに\n"
		.string "和平どころじゃなくなったな…▼"
		.string "もっとも、\n"
		.string "そうかんたんに平和がくるとも…\n"
		.string "考えていなかったがな▼"
		.string "………▼"
		.string "それはそうと\n"
		.string "新しいブキについてなんだが\n"
		.string "たった今、カンセイしたところだ▼"
		.string "それにシールドブーメランも\n"
		.string "シュウリしておいたぞ！▼"
		.string "もっていきなさい！$"

Text8: @ 0x08383B0E
	.string "{WINDOW 0x43}"
		.string "あっ、そうそう\n"
		.string "シークレットディスクに\n"
		.string "ついてなのだが…▼"
		.string "シークレットディスクの中に\n"
		.string "ゼロじゃカイセキできない\n"
		.string "ものがあるだろ？▼"
		.string "そんな時は、\n"
		.string "わたしがカイセキするので\n"
		.string "えんりょなく、話しかけてくれ▼"
		.string "いちどカイセキしたディスクでも\n"
		.string "ナイヨウをカクニンしたい時は\n"
		.string "わたしのところに来なさい$"

Text9: @ 0x08383BA5
	.string "{WINDOW 0x00}"
		.string "オペレーター「ゼロさん、ゼロさん…▼"
		.string "シキュウ、シレイシツまでおこしください…$"

Text10: @ 0x08383BCE
	.string "{WINDOW 0x43}"
		.string "ん？ ゼロ…呼んどるようだぞ$"

Text11: @ 0x08383BE0
	.string "{WINDOW 0x04}"
		.string "リコイルロッド……使いやすそうだ\n"
		.string "カンシャする…$"

Text12: @ 0x08383BFC
	.string "{WINDOW 0x43}"
		.string "シエルにはまだ……\n"
		.string "世界は、おも過ぎる……▼"
		.string "ささえてやってくれ\n"
		.string "ゼロ……$"

Text13: @ 0x08383C26
	.string "{WINDOW 0x40}"
		.string "またせちゃったわね\n"
		.string "ゼロ…\n"
		.string "ジュンビはいい？▼"
		.string "わたしたちに できることを\n"
		.string "色々なジョウホウをもとに\n"
		.string "シミュレートして…▼"
		.string "そのケッカを\n"
		.string "ミッションのカタチで\n"
		.string "テイアンしてもらったの…▼"
		.string "まず2つは…▼"
		.string "ダークエルフを\n"
		.string "ネオ・アルカディアに\n"
		.string "わたさないためのミッション…▼"
		.string "のこり2つは…▼"
		.string "ネオ・アルカディアから\n"
		.string "みんなを守るためにおこなう▼"
		.string "ネオ・アルカディアへの\n"
		.string "ゲリラこうげきミッション…▼"
		.string "………▼"
		.string "……▼"
		.string "ゼロ…わたしたち……\n"
		.string "戦うしかないのかな……▼"
		.string "せっかく、\n"
		.string "新エネルギーが開発できて……▼"
		.string "これでようやく……\n"
		.string "世界が平和になると思ったのに……▼"
		.string "まだ…戦い続けるしか\n"
		.string "ないっていうの………▼"
	.string "{WINDOW 0x05}"
		.string "シエル……▼"
		.string "オマエにできることは、\n"
		.string "もうジュウブンやっている……▼"
		.string "オマエは、ひとりじゃない▼"
		.string "あとは、オレたちにまかせろ▼"
	.string "{WINDOW 0x40}"
		.string "ゼ…ゼロ……▼"
	.string "{WINDOW 0x62}"
		.string "ゼロさん\n"
		.string "いつでも行けます……$"

Text14: @ 0x08383DB4
	.string "{WINDOW 0x62}"
		.string "ミッションをセンタクしますか？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text15: @ 0x08383DD1
	.string "{WINDOW 0x62}"
		.string "{TOP}では、ジュンビができましたら\n"
		.string "いつでも声をおかけください…$"

Text16: @ 0x08383DF3
	.string "{WINDOW 0x61}"
		.string "これですべてのミッションが\n"
		.string "シュウリョウしました▼"
		.string "今回のミッションで\n"
		.string "新たに発見されたミサイル工場を\n"
		.string "どうするか…▼"
		.string "現在、\n"
		.string "ダークエルフのタンサクと同時に…▼"
		.string "このモンダイへの\n"
		.string "タイオウをケントウ中です$"

Text17: @ 0x08383E65
	.string "{WINDOW 0x40}"
		.string "イッコクもはやく\n"
		.string "あのミサイルをなんとか\n"
		.string "したいんだけど…▼"
		.string "ミサイル工場への転送ザヒョウは、\n"
		.string "古いエイセイしゃしんをもとに\n"
		.string "ケイサンしただけだから……▼"
		.string "転送ルートとして使うには、\n"
		.string "あまりにキケンすぎるの▼"
	.string "{WINDOW 0x62}"
		.string "ミサイル工場への地上ルートは、\n"
		.string "テイサツ部隊がソウサク中ですが\n"
		.string "ナンコウしてます▼"
		.string "ダークエルフの方も、\n"
		.string "スキャニングを続けていますが\n"
		.string "まだハンノウがありません▼"
	.string "{WINDOW 0x04}"
		.string "わかった…▼"
		.string "ジョウキョウがかわったら\n"
		.string "おしえてくれ…$"

Text18: @ 0x08383F4B
	.string "{WINDOW 0x40}"
		.string "わかったわ…▼"
		.string "あっ、そうだ…$"

Text19: @ 0x08383F5C
	.string "{WINDOW 0x40}"
		.string "何か わかったら、\n"
		.string "すぐにレンラクするから…\n"
		.string "それまで、ゆっくりやすんで…ね$"

Text20: @ 0x08383F86
	.string "{WINDOW 0x40}"
		.string "そう…でも無理はしないでね▼"
		.string "すぐにレンラクするから…\n"
		.string "それまで、ゆっくりやすんで…ね$"

Text21: @ 0x08383FB5
	.string "{WINDOW 0x2C}"
		.string "エックスさま……▼"
		.string "まだ、あのオトコ…バイルを\n"
		.string "信用されているのですか……？▼"
	.string "{WINDOW 0x37}"
		.string "かレの ツイほウは、\n"
		.string "セイシキな テつヅキをとらず\n"
		.string "実行された…▼"
		.string "カレが おこなったコとが\n"
		.string "ケッカとして、おおキなヒゲキを\n"
		.string "ひきおこしたからといって…▼"
		.string "ホウリツをムシして…\n"
		.string "カレを ツイホウしたことは、\n"
		.string "アヤまりだト おもわないかい？▼"
		.string "今回かレは、ゴウホウ的にこの\n"
		.string "ネオ・アルかでィアにフッキした▼"
		.string "カレをハイジョするリユウが\n"
		.string "ドコニあるんダ▼"
		.string "シンパイいらないよ\n"
		.string "カレも過去のアヤマチから…\n"
		.string "多くのものをマナんだ…▼"
		.string "今度こそウマくやるに\n"
		.string "チガいなイ……$"

Text22: @ 0x083840CD
	.string "{WINDOW 0x2C}"
		.string "ですが…！▼"
	.string "{WINDOW 0x3B}"
		.string "クックック…\n"
		.string "さすがは、エックスさま$"

Text23: @ 0x083840EA
	.string "{WINDOW 0x3B}"
		.string "このバイル、\n"
		.string "同じアヤマチは、\n"
		.string "にどとおかしません▼"
		.string "そう…にどと……ね\n"
		.string "クックック…$"

Text24: @ 0x08384118
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}しかし…\n"
		.string "ワシのいないところで\n"
		.string "かげぐちとは…▼"
		.string "かつての四天王も\n"
		.string "おちたものですな▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}なんだと……バイル…！$"

Text25: @ 0x08384157
	.string "{WINDOW 0x3B}"
		.string "ところでエックスさま▼"
		.string "ダークエルフが\n"
		.string "ネオ・アルカディアに\n"
		.string "現れたもようです▼"
		.string "エリアZ-3079…\n"
		.string "ここから、もっともはなれた\n"
		.string "人間の きょじゅうくなんですが…$"

Text26: @ 0x083841AD
	.string "{WINDOW 0x2C}"
		.string "われわれが行きます▼"
		.string "レヴィアタンとファーブニルは、\n"
		.string "まだメンテナンス中ですが…\n"
		.string "いそがせれば…▼"
	.string "{WINDOW 0x37}"
		.string "いツまで カンブきどりダ\n"
		.string "ハルピュイア……▼"
		.string "たびかサなる レジスタンスの\n"
		.string "はんらんヲ ゆるし…▼"
		.string "ついには ダークエルフまデも…\n"
		.string "にがした…▼"
		.string "おマエたちノヨうな ノウナシには\n"
		.string "もウ、あキアきした▼"
		.string "キみたち四天王は…\n"
		.string "カンブから オリてもらウよ…▼"
	.string "{WINDOW 0x2C}"
		.string "なっ…エックスさま…！？▼"
	.string "{WINDOW 0x37}"
		.string "ドクター・バイル…▼"
		.string "全軍のシキは…\n"
		.string "キミにまカせる▼"
		.string "やっテクれる…ナ$"

Text27: @ 0x08384296
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…\n"
		.string "リョウカイいたしました…▼"
		.string "かならずやダークエルフを\n"
		.string "手に入れましょう▼"
		.string "レジスタンスの手にわたり…\n"
		.string "この世界のキョウイとならぬよう…\n"
		.string "クーックックッ$"

Text28: @ 0x083842F2
	.string "{WINDOW 0x61}"
		.string "巨大ミサイルが\n"
		.string "ハッシャじゅんびに入りました▼"
		.string "モクヒョウとされるエリアは不明\n"
		.string "現在ハッキングにてチョウサ中▼"
	.string "{WINDOW 0x62}"
		.string "ミサイルに\n"
		.string "強力なエネルギーはんのう▼"
		.string "ミサイルには、\n"
		.string "オメガがつまれているもようです▼"
	.string "{WINDOW 0x40}"
		.string "オメガ！？▼"
		.string "あのオメガがミサイルに！！▼"
	.string "{WINDOW 0x04}"
		.string "………$"

Text29: @ 0x0838437D
	.string "{WINDOW 0x04}"
		.string "シエル…▼"
		.string "オマエがカイセキした\n"
		.string "ザヒョウを入力させろ$"

Text30: @ 0x0838439C
	.string "{WINDOW 0x40}"
		.string "そんな…キケンだわ！$"

Text31: @ 0x083843A9
	.string "{WINDOW 0x04}"
		.string "オペレーター▼"
		.string "転送ジュンビいそげ$"

Text32: @ 0x083843BE
	.string "{WINDOW 0x40}"
		.string "ゼロ……自信がない！！▼"
	.string "{WINDOW 0x04}"
		.string "オレは、オマエを信じている$"

Text33: @ 0x083843DF
	.string "{WINDOW 0x40}"
		.string "………………$"

Text34: @ 0x083843E8
	.string "{WINDOW 0x40}"
		.string "わかった……\n"
		.string "………\n"
		.string "データを…入力して………▼"
		.string "転送……おねがい！▼"
	.string "{WINDOW 0x61}"
		.string "リョウカイ\n"
		.string "転送ジュンビかいし…$"

Text35: @ 0x08384425
	.string "{WINDOW 0x40}"
		.string "ゼロ………$"

Text36: @ 0x0838442D
	.string "{WINDOW 0x40}"
		.string "ゼロ………▼"
		.string "ほんとに…無事でよかった……▼"
		.string "もう……にどと………\n"
		.string "あんなむちゃ……しないでね\n"
		.string "おねがいよ………▼"
	.string "{WINDOW 0x05}"
		.string "………\n"
		.string "考えておこう……▼"
		.string "ところで……\n"
		.string "ハルピュイアは…？$"

Text37: @ 0x08384489
	.string "{WINDOW 0x40}"
		.string "セルヴォがメンテナンス・ルームに\n"
		.string "つれていったわ▼"
		.string "キズは、それほど\n"
		.string "深くないみたいだけど……▼"
		.string "しばらく あんせいにしないと\n"
		.string "だめみたい………▼"
		.string "…………▼"
		.string "ほんとに………\n"
		.string "タイヘンなことに\n"
		.string "なってしまったわね……▼"
		.string "今、オペレーターさんたちに\n"
		.string "カノウなかぎり ジョウホウを\n"
		.string "集めてもらってるわ▼"
		.string "ブンセキには、時間がかかりそうなの\n"
		.string "それまで、少しやすんでいて…▼"
	.string "{WINDOW 0x05}"
		.string "だいじょうぶだ$"

Text38: @ 0x0838454C
	.string "{WINDOW 0x40}"
		.string "じゃあ、せめて……$"

Text39: @ 0x08384558
	.string "{WINDOW 0x40}"
		.string "…それにしても、\n"
		.string "ダークエルフのためとは言え…▼"
		.string "ネオ・アルカディアが\n"
		.string "人間たちのいるエリアに\n"
		.string "ミサイルを おとすなんて…$"

Text40: @ 0x0838459A
	.string "{WINDOW 0x40}"
		.string "そう…わかったわ……▼"
		.string "…それにしても、\n"
		.string "ダークエルフのためとは言え…▼"
		.string "ネオ・アルカディアが\n"
		.string "人間たちのいるエリアに\n"
		.string "ミサイルを おとすなんて…$"

Text41: @ 0x083845E7
	.string "{WINDOW 0x61}"
		.string "ツウシンかいせんに\n"
		.string "キョウセイわりこみ……！▼"
		.string "ネオ・アルカディアからです！$"

Text42: @ 0x0838460F
	.string "{WINDOW 0x05}"
		.string "つなげろ！$"

Text43: @ 0x08384617
	.string "{WINDOW 0x36}"
		.string "{BOTTOM}ギ…ギギッ…きコえるカい…\n"
		.string "レジスタンスのショクん…▼"
		.string "ソして…ドクター・シエル…▼"
	.string "{WINDOW 0x41}"
		.string "コピー…エックス……！▼"
	.string "{WINDOW 0x36}"
		.string "ダークエルフは、ついに\n"
		.string "われワれの もノと ナっタ…▼"
		.string "くダらない アラソいは、\n"
		.string "オわリに しタい…▼"
		.string "キミたちに コウフクを\n"
		.string "よびカけるこトに したよ$"

Text44: @ 0x0838469E
	.string "{WINDOW 0x40}"
		.string "コウフクですって…？▼"
	.string "{WINDOW 0x3B}"
		.string "キミの発明した新エネルギー\n"
		.string "システマ・シエルを\n"
		.string "われわれに わたしてほしい▼"
		.string "そうすれば、\n"
		.string "キミたちイレギュラーの\n"
		.string "安全は、ホショウしよう…▼"
	.string "{WINDOW 0x40}"
		.string "そんな……▼"
	.string "{WINDOW 0x3B}"
		.string "キミが送ってくれた\n"
		.string "システマ・シエルのジョウホウを\n"
		.string "カイセキしたケッカ…▼"
		.string "ダークエルフと\n"
		.string "くみあわせることにより……▼"
		.string "バクダイなエネルギーを\n"
		.string "生み出すカノウセイが\n"
		.string "あることがわかったのだよ▼"
		.string "これでエネルギー不足は、\n"
		.string "いっきょにカイケツ▼"
		.string "もう、オマエたちを\n"
		.string "ショブンするヒツヨウもない……▼"
	.string "{WINDOW 0x37}"
		.string "シエル…▼"
		.string "キみのコタエひとつで\n"
		.string "世界は、平和になルんだよ…$"

Text45: @ 0x083847BB
	.string "{WINDOW 0x40}"
		.string "……………▼"
		.string "あなたたちは……▼"
		.string "信用……できません………▼"
	.string "{WINDOW 0x37}"
		.string "…なんだっテ？$"

Text46: @ 0x083847E5
	.string "{WINDOW 0x40}"
		.string "ダークエルフを手に入れるために\n"
		.string "人間をぎせいにするような……▼"
		.string "そんな…あなたたちは……\n"
		.string "信用できません！▼"
		.string "システマ・シエルは、わたさない▼"
		.string "これは、人とレプリロイドが\n"
		.string "平和にくらすためのものだから！$"

Text47: @ 0x08384853
	.string "{WINDOW 0x37}"
		.string "{BOTTOM}…そレが…こたえか…▼"
		.string "いいだろウ…▼"
		.string "エネルギーしげんを\n"
		.string "ドクセンし……▼"
		.string "ゼロという、\n"
		.string "おそロシい戦闘力をモつ\n"
		.string "レプリロイドを ホユウしていル……▼"
		.string "おまエタちなど、もハヤ\n"
		.string "たダノ うすヨごれた テロリストだ▼"
		.string "シエル…\n"
		.string "人間のおまエガ いたかラ\n"
		.string "いマまで、テカゲンしてイタが…▼"
		.string "イレギュラー ともドモ\n"
		.string "ショブンしてヤる！$"

Text48: @ 0x083848FA
	.string "{WINDOW 0x61}"
		.string "ツウシンとだえました$"

Text49: @ 0x08384907
	.string "{WINDOW 0x62}"
		.string "ネオ・アルカディア軍が\n"
		.string "かくエリアから べースへ向けて\n"
		.string "シンコウを カイシしました▼"
		.string "ソウコウゲキを\n"
		.string "しかけてくるもようです$"

Text50: @ 0x08384949
	.string "{WINDOW 0x40}"
		.string "ゼロ……わたし………▼"
	.string "{WINDOW 0x05}"
		.string "オマエは自分を信じて戦った▼"
		.string "ここからは…\n"
		.string "オレのシゴトだ…▼"
		.string "ヤツらのいるエリアをおしえろ\n"
		.string "ゲイゲキする▼"
	.string "{WINDOW 0x40}"
		.string "ゼ…ゼロ…………▼"
	.string "{WINDOW 0x61}"
		.string "ネオ・アルカディアの\n"
		.string "しんこうルートを\n"
		.string "モニターにヒョウジします$"

Text51: @ 0x083849BE
	.string "{WINDOW 0x00}"
		.string "メンテナンス・ルーム 使用中…$"

Text52: @ 0x083849D3
	.string "{WINDOW 0x40}"
		.string "とうとう\n"
		.string "ドクター・バイルが……▼"
		.string "ネオ・アルカディアの\n"
		.string "シハイシャに\n"
		.string "なってしまったわね………▼"
	.string "{WINDOW 0x05}"
		.string "何も知らされていない\n"
		.string "人間たち…▼"
		.string "いや…\n"
		.string "何も知ろうとしない\n"
		.string "人間たち…か$"

Text53: @ 0x08384A35
	.string "{WINDOW 0x40}"
		.string "たべものにも、\n"
		.string "すむバショにも不自由しない\n"
		.string "セイカツ……▼"
		.string "人々は、だんだん…\n"
		.string "自分のアタマで\n"
		.string "考えようとしなくなった……▼"
		.string "でも…中には、\n"
		.string "何とかしたいと思っている人が\n"
		.string "いるかもしれない▼"
		.string "ドクター・バイルが\n"
		.string "何を考えているのか…▼"
		.string "そんな人たちに\n"
		.string "伝えることができたら……▼"
		.string "ネオ・アルカディアを\n"
		.string "かえることができるかもしれない…▼"
	.string "{WINDOW 0x61}"
		.string "ドクター・バイルは\n"
		.string "いったい何者なのか……▼"
		.string "この世界に再び現れてから\n"
		.string "今まで何をやっていたのか……▼"
	.string "{WINDOW 0x62}"
		.string "ジョウホウを\n"
		.string "集めていただければ……▼"
		.string "カレが今どこにいるか…\n"
		.string "何をしようとしているのか…\n"
		.string "ブンセキできるかもしれません▼"
	.string "{WINDOW 0x05}"
		.string "わかった▼"
		.string "どこへ行けばいいか\n"
		.string "おしえてくれ…$"

Text54: @ 0x08384B81
	.string "{WINDOW 0x40}"
		.string "ええ、でも その前に…$"

Text55: @ 0x08384B90
	.string "{WINDOW 0x61}"
		.string "ジョウホウが\n"
		.string "入手できそうなバショを\n"
		.string "ピックアップしてみました$"

Text56: @ 0x08384BB4
	.string "{WINDOW 0x61}"
		.string "ゼロさんが今までカイシュウされた\n"
		.string "データの入力……▼"
		.string "今、終わりました▼"
	.string "{WINDOW 0x62}"
		.string "カイセキにうつります$"

Text57: @ 0x08384BEB
	.string "{WINDOW 0x40}"
		.string "ゼロのおかげで、\n"
		.string "いろいろなジョウホウが\n"
		.string "集まったわ……▼"
		.string "カイセキが終わるまで\n"
		.string "少し時間がかかりそうだから\n"
		.string "今のうちに……$"

Text58: @ 0x08384C31
	.string "{WINDOW 0x40}"
		.string "あっ、そうだ\n"
		.string "そういえばセルヴォが……▼"
		.string "ハルピュイアのカラダ……\n"
		.string "だいぶん よくなったって\n"
		.string "言ってたわ…▼"
		.string "おみまいに……\n"
		.string "行ってあげたら…どうかしら？$"

Text59: @ 0x08384C81
	.string "{WINDOW 0x40}"
		.string "わかったわ…\n"
		.string "でも……無理…しないでね……▼"
		.string "あっ、そうだ\n"
		.string "そういえばセルヴォが……▼"
		.string "ハルピュイアのカラダ……\n"
		.string "だいぶん よくなったって\n"
		.string "言ってたわ…▼"
		.string "おみまいに……\n"
		.string "行ってあげたら…どうかしら？$"

Text60: @ 0x08384CE9
	.string "{WINDOW 0x04}"
		.string "もう…たてるのか▼"
		.string "さすがだな\n"
		.string "ハルピュイア……$"

Text61: @ 0x08384D03
	.string "{WINDOW 0x2D}"
		.string "どういうつもりだ？\n"
		.string "なぜ助けた？▼"
		.string "かりはかえすとでも言いたいのか！？▼"
	.string "{WINDOW 0x04}"
		.string "さあな$"

Text62: @ 0x08384D30
	.string "{WINDOW 0x42}"
		.string "おお、気がついたか▼"
		.string "気分はどうだね？▼"
	.string "{WINDOW 0x2D}"
		.string "…サイアクだな▼"
		.string "キサマらに助けられたかと思うと\n"
		.string "ハキケがする▼"
		.string "カンブを おろされ…\n"
		.string "ネオ・アルカディアを おわれ\n"
		.string "オレもおちたものだ…▼"
	.string "{WINDOW 0x42}"
		.string "そんなことは ないよ▼"
		.string "キミは自分の考えを\n"
		.string "つらぬいただけだ…\n"
		.string "わたしたちと同じようにね▼"
		.string "何も まちがっては\n"
		.string "いないさ▼"
	.string "{WINDOW 0x2D}"
		.string "自分の考え…か…▼"
		.string "もうこれ以上\n"
		.string "ねてなどいられない……▼"
		.string "バイルから…\n"
		.string "人間たちを守ってやらねば\n"
		.string "ならんのだ………▼"
		.string "はやくアイツを止めなければ……\n"
		.string "アイツは……アイツは…！$"

Text63: @ 0x08384E33
	.string "{WINDOW 0x42}"
		.string "まちたまえ！▼"
		.string "キミのキズはまだカンゼンには\n"
		.string "なおっていないんだ！▼"
	.string "{WINDOW 0x2D}"
		.string "オレは……\n"
		.string "人間を守るために生まれた戦士…▼"
		.string "ほこりたかき\n"
		.string "ネオ・アルカディアの戦士だ！\n"
		.string "キサマらの 助けなどいらない！▼"
		.string "たとえこのカラダが\n"
		.string "くちはてようとも……▼"
		.string "人間のためなら\n"
		.string "よろこんで戦おう！$"

Text64: @ 0x08384EC7
	.string "{WINDOW 0x42}"
		.string "やはり…われわれとは▼"
		.string "いっしょに\n"
		.string "行けないというのか…▼"
	.string "{WINDOW 0x04}"
		.string "………$"

Text65: @ 0x08384EEC
	.string "{WINDOW 0x00}"
		.string "オペレーター「ゼロさん、ゼロさん…▼"
		.string "シキュウ、シレイシツまでおこしください…$"

Text66: @ 0x08384F15
	.string "{WINDOW 0x42}"
		.string "いきつくひまもないな…\n"
		.string "ゼロ……▼"
	.string "{WINDOW 0x04}"
		.string "…行ってくる$"

Text67: @ 0x08384F32
	.string "{WINDOW 0x42}"
		.string "ゼロ……▼"
		.string "ハルピュイア……▼"
		.string "みんな…死ぬんじゃないぞ……$"

Text68: @ 0x08384F52
	.string "{WINDOW 0x61}"
		.string "データのカイセキ中です\n"
		.string "しばらく おまちください$"

Text69: @ 0x08384F6E
	.string "{WINDOW 0x61}"
		.string "ジョウホウのカイセキ…\n"
		.string "カンリョウしました▼"
		.string "シエルさんから\n"
		.string "ホウコクしていただきます……$"

Text70: @ 0x08384F9D
	.string "{WINDOW 0x40}"
		.string "ゼロ…ごめんなさい▼"
		.string "せっかくゼロにいろいろな\n"
		.string "ジョウホウを\n"
		.string "集めてもらったのに……▼"
		.string "バイルがどこにいるかまでは、\n"
		.string "わからなかったわ▼"
		.string "でも…バイルが\n"
		.string "何をしようとしているのか……\n"
		.string "それは少し わかったかもしれないの▼"
		.string "バイルの話をする前に\n"
		.string "まず……▼"
		.string "ゼロが見つけてくれた\n"
		.string "ヨウセイ戦争の\n"
		.string "データファイルをひらくわね$"

Text71: @ 0x08385043
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ファイルナンバー945388\n"
		.string "--ヨウセイ戦争--$"

Text72: @ 0x08385062
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}イレギュラー戦争の終わりごろ、\n"
		.string "サイバーエルフがタイリョウに\n"
		.string "使用されたことから……▼"
		.string "これ以後、戦争が終わるまでを\n"
		.string "ヨウセイ戦争と呼ぶ▼"
		.string "とくにダークエルフと呼ばれる\n"
		.string "ちょう大型ヨウセイと…▼"
		.string "そのコピーであるベビーエルフの\n"
		.string "使用により……▼"
		.string "レプリロイドのチカラを\n"
		.string "ゾウフクさせ……▼"
		.string "同時に思いどおりに\n"
		.string "コントロールすることが\n"
		.string "カノウになってからは……▼"
		.string "かつてないほどの……\n"
		.string "最悪の戦争となった……▼"
		.string "戦争は、ダークエルフ使用により\n"
		.string "4年でシュウケツするが……▼"
		.string "レプリロイドのほぼ90%……▼"
		.string "人間の60%がシメツした……$"

Text73: @ 0x08385187
	.string "{WINDOW 0x40}"
		.string "この時、使用したギジュツ……▼"
		.string "ベビーエルフを使って\n"
		.string "レプリロイドを思いどおりに\n"
		.string "コントロールするギジュツを▼"
		.string "バイルは、再び\n"
		.string "使用しようと\n"
		.string "してるんじゃないかしら……▼"
		.string "ゼロが\n"
		.string "ダークエルフのコピー工場で\n"
		.string "見たものは▼"
		.string "きっと、そのために 用意した\n"
		.string "モノだと思うんだけど……$"

Text74: @ 0x0838521D
	.string "{WINDOW 0x62}"
		.string "………▼"
		.string "クックックック……▼"
		.string "よくしらべたな\n"
		.string "ドクター・シエル……$"

Text75: @ 0x08385240
	.string "{WINDOW 0x40}"
		.string "な？▼"
	.string "{WINDOW 0x61}"
		.string "だが少し………▼"
		.string "おそすぎたんじゃないかね$"

Text76: @ 0x0838525D
	.string "{WINDOW 0x04}"
		.string "ドクター・バイルか！？$"

Text77: @ 0x0838526B
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}クーックックッ…▼"
		.string "今度のオメガは、まさに\n"
		.string "カンペキだ……▼"
		.string "もう、ベビーエルフなど\n"
		.string "使わなくとも…▼"
		.string "この世界…\n"
		.string "すべてのレプリロイドを▼"
		.string "思うがままに\n"
		.string "あやつれるようになったのだ！！▼"
		.string "クーックックックッ…\n"
		.string "さあ…はじめるとするか…\n"
		.string "オメガよ…$"

Text78: @ 0x083852EC
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}今こそ思い知れ…▼"
		.string "ワシをツイホウした\n"
		.string "人間どもよ！$"

Text79: @ 0x0838530E
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}キョウフしろ…▼"
		.string "ワシをツイホウした\n"
		.string "レプリロイドどもよ！$"

Text80: @ 0x0838532E
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}きざみこむのだ\n"
		.string "この世界に…▼"
		.string "シハイシャたるワシの名を！$"

Text81: @ 0x08385351
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}わが名はドクター・バイル▼"
		.string "世界は、わが手の中にある…\n"
		.string "この手をにぎりしめるだけで……▼"
		.string "この世界を終わらすことが\n"
		.string "できるのだ！！$"

Text82: @ 0x0838539D
	.string "{WINDOW 0x61}"
		.string "クーックックックッ…▼"
		.string "クヒャーッハッハッハッハッ！$"

Text83: @ 0x083853B9
	.string "{WINDOW 0x40}"
		.string "まっ、まさか！？$"

Text84: @ 0x083853C4
	.string "{WINDOW 0x5F}"
		.string "う…うう…$"

Text85: @ 0x083853CC
	.string "{WINDOW 0x40}"
		.string "そ、そんな……！$"

Text86: @ 0x083853D7
	.string "{WINDOW 0x5E}"
		.string "新たなる世界…\n"
		.string "新たなるチツジョ…▼"
		.string "とじられたレキシが…\n"
		.string "再び 動きはじめる…$"

Text87: @ 0x08385407
	.string "{WINDOW 0x05}"
		.string "さがれ！ シエル！$"

Text88: @ 0x08385413
	.string "{WINDOW 0x40}"
		.string "ゼロ！？▼"
	.string "{WINDOW 0x5E}"
		.string "世界にきざめ…\n"
		.string "われらのシハイシャの名は…▼"
		.string "バイル！ バイル！ バイル！\n"
		.string "バイル！ バイル！ バイル！\n"
		.string "バイル！ バイル！ バイル！$"

Text89: @ 0x08385462
	.string "{WINDOW 0x34}"
		.string "ふたりとも、動かないで！$"

Text90: @ 0x08385472
	.string "{WINDOW 0x40}"
		.string "あ…！▼"
	.string "{WINDOW 0x34}"
		.string "だいじょうぶ…\n"
		.string "気をうしなっているだけだよ▼"
		.string "ダークエルフのチカラを\n"
		.string "とりのぞいたんだ▼"
		.string "今のボクのチカラじゃ…\n"
		.string "このベースの中のみんなを守るので\n"
		.string "せいいっぱいだけど…$"

Text91: @ 0x083854D1
	.string "{WINDOW 0x05}"
		.string "おそいぞエックス……▼"
		.string "バイルはどこだ▼"
	.string "{WINDOW 0x34}"
		.string "ネオ・アルカディアの\n"
		.string "地下動力部……▼"
		.string "アンダー・アルカディア…だよ▼"
		.string "オメガはそこから\n"
		.string "世界中にダークエルフのチカラを\n"
		.string "おくっているんだ▼"
	.string "{WINDOW 0x05}"
		.string "どうやら…▼"
		.string "まともに動けるのは、\n"
		.string "オレとエックスだけのようだな▼"
		.string "エックス▼"
		.string "アンダー・アルカディアの\n"
		.string "ザヒョウをおしえろ▼"
	.string "{WINDOW 0x34}"
		.string "オメガと…戦うんだね？▼"
	.string "{WINDOW 0x05}"
		.string "ああ……▼"
		.string "それが…なんだ？▼"
	.string "{WINDOW 0x34}"
		.string "いや、キミならだいじょうぶだ…▼"
		.string "気をつけて………ゼロ$"

Text92: @ 0x083855B0
	.string "{WINDOW 0x61}"
		.string "て…▼"
		.string "転送ソウチに…\n"
		.string "アンダー・アルカディアの\n"
		.string "ザヒョウ入力をカクニン…▼"
	.string "{WINDOW 0x04}"
		.string "転送をたのむ$"

Text93: @ 0x083855E6
	.string "{WINDOW 0x61}"
		.string "リョウカイ…\n"
		.string "カクイン…転送じゅんびにかかれ$"

Text94: @ 0x08385601
	.string "{WINDOW 0x62}"
		.string "転送じゅんびカンリョウ…$"

Text95: @ 0x08385612
	.string "{WINDOW 0x61}"
		.string "転送…$"

Text96: @ 0x0838561A
	.string "{WINDOW 0x61}"
		.string "オリジナルエックスより\n"
		.string "入手しました ざひょうデータ…▼"
		.string "入力…カンリョウしました$"

Text97: @ 0x08385649
	.string "{WINDOW 0x40}"
		.string "ザヒョウがしめすバショは\n"
		.string "ハイキされた\n"
		.string "古いケンキュウジョなの……▼"
		.string "キロクによると\n"
		.string "ここは、むかしバイルが\n"
		.string "ケンキュウをしていたバショで…▼"
		.string "ゼロがねむっていた…\n"
		.string "あのバショの…すぐ近くだわ……▼"
	.string "{WINDOW 0x05}"
		.string "そこに…\n"
		.string "バイルとオメガがいるんだな$"

Text98: @ 0x083856C3
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "気をつけてね………▼"
	.string "{WINDOW 0x05}"
		.string "あぁ……▼"
		.string "オペレーター…\n"
		.string "行けるか？$"

Text99: @ 0x083856EB
	.string "{WINDOW 0x61}"
		.string "いつでも行けます$"

.balign 4, 0
