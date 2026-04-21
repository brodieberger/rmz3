.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_WeilLabo:: @ 0x083825bc
	.2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
	.2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
	.2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
	.2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start), (Text29-Start), (Text30-Start), (Text31-Start)
	.2byte (Text32-Start), (Text33-Start), (Text34-Start), (Text35-Start), (Text36-Start), (Text37-Start), (Text38-Start), (Text39-Start)
	.2byte (Text40-Start), (Text41-Start), (Text42-Start), (Text43-Start), (Text44-Start), (Text45-Start), (Text46-Start), (Text47-Start)
	.2byte (Text48-Start), (Text49-Start), (Text50-Start), (Text51-Start), (Text52-Start), (Text53-Start), (Text54-Start), (Text55-Start)
	.2byte (Text56-Start)

Text_WeilLabo:: @ 0x0838262e
Start:

Text0: @ 0x0838262E
		.string "$"

Text1: @ 0x0838262F
	.string "{WINDOW 0x17}"
		.string "シャハアアッ！▼"
		.string "バイルさまの作る新しい世界！\n"
		.string "いいねぇ！ あつくなってきたぜ！▼"
		.string "ジャマはさせねえぜ！\n"
		.string "ここでオマエをケシズミに\n"
		.string "してやるよ！$"

Text2: @ 0x0838267C
	.string "{WINDOW 0x06}"
		.string "シャハアアアァッ！\n"
		.string "世界にきざめ！ しはいしゃの名！\n"
		.string "ドクターァァッバイルッ！$"

Text3: @ 0x083826A9
	.string "{WINDOW 0x06}"
		.string "シャ…ハッ…あつい…あついぜ…！▼"
		.string "新しい世界で…ひとりで\n"
		.string "もがきくるしめ…！▼"
		.string "シャギャハアアアアッ！$"

Text4: @ 0x083826E1
	.string "{WINDOW 0x19}"
		.string "このノロマーッ！▼"
		.string "バイルさまの理想は100年前に\n"
		.string "できあがっていたんだーっ！▼"
		.string "今さらモンク言うなよなーっ！\n"
		.string "ジダイおくれのポンコツがーっ！\n"
		.string "ひとりで とりのこされてろーっ！$"

Text5: @ 0x08382740
	.string "{WINDOW 0x08}"
		.string "ほんっとノロイなーっ！▼"
		.string "ジダイにまで\n"
		.string "のりおくれてるんじゃねーよっ！$"

Text6: @ 0x08382765
	.string "{WINDOW 0x08}"
		.string "う…ぐっ…！▼"
		.string "オマエが\n"
		.string "いくらいそいだところで…▼"
		.string "動き出したレキシには\n"
		.string "おいつけねー…▼"
		.string "オマエはずっと…\n"
		.string "バイルさまに おいつけねーよ…！▼"
		.string "うっ…あああああああっ！$"

Text7: @ 0x083827BC
	.string "{WINDOW 0x1B}"
		.string "さわがしいですね▼"
		.string "ノックはしずかにするものですよ\n"
		.string "そんなマナーも知らないとは…▼"
		.string "この新しい世界で生きるシカクは\n"
		.string "…あなたには、ありませんっ！\n"
		.string "消えてもらいましょう！$"

Text8: @ 0x08382817
	.string "{WINDOW 0x0A}"
		.string "おかえりねがいましょうか▼"
		.string "あなたがねむっていた\n"
		.string "くらく…深い地のそこにね！$"

Text9: @ 0x08382841
	.string "{WINDOW 0x0A}"
		.string "キキッ…キ…▼"
		.string "なんと…おろかな…\n"
		.string "なんと…やばんな…！▼"
		.string "あなたのようなものが…\n"
		.string "新しい世界に生きのこるなど…！▼"
		.string "キキッ…キキキキーーッ！$"

Text10: @ 0x0838288C
	.string "{WINDOW 0x1D}"
		.string "100年前のガラクタなど\n"
		.string "この新しい世界には\n"
		.string "ヒツヨウない…！▼"
		.string "ここできりきざんで…\n"
		.string "すててきてやる…！ 死の世界になぁ！▼"
		.string "ギチギチギチギチィッ！$"

Text11: @ 0x083828E0
	.string "{WINDOW 0x0C}"
		.string "ギチッ！ ギチチッ！▼"
		.string "そこで見てな…！\n"
		.string "古き世界と…テメエの仲間が\n"
		.string "きりきざまれる ところをな…！$"

Text12: @ 0x0838291A
	.string "{WINDOW 0x0C}"
		.string "最新最強の このオレが…\n"
		.string "100年前のガラクタに\n"
		.string "まけるのか…！？▼"
		.string "ありえない…イヤ…だ…\n"
		.string "死にたくない…\n"
		.string "死にたくないぃぃ…！▼"
		.string "ギチッ…ギギギギギギーーーーッ！$"

Text13: @ 0x08382976
	.string "{WINDOW 0x1F}"
		.string "あらあら…こんなところまで\n"
		.string "来ちゃったのねぇ…ボウヤ▼"
		.string "おねむりなさい…▼"
		.string "ここからさきは、\n"
		.string "ボウヤの見ちゃいけない世界…▼"
		.string "オマエがいちゃいけない世界なの…！$"

Text14: @ 0x083829CC
	.string "{WINDOW 0x0E}"
		.string "ゆっくりとおやすみなさい▼"
		.string "もう、おきることも\n"
		.string "ないでしょうけどね！▼"
		.string "オーッホッホッホッホッ！$"

Text15: @ 0x083829FD
	.string "{WINDOW 0x0E}"
		.string "あ…ああっ…\n"
		.string "ダダをこねても…ムダよ…▼"
		.string "あがいたところで…\n"
		.string "オマエなんかじゃ\n"
		.string "どうにもならないの…▼"
		.string "そう……▼"
		.string "エイユウでも…ハカイ神でもない\n"
		.string "オマエには…▼"
		.string "どうにも…できな…\n"
		.string "あっ…ああーーーっ！$"

Text16: @ 0x08382A63
	.string "{WINDOW 0x21}"
		.string "んんーっ！▼"
		.string "ドロボウにつづき、\n"
		.string "ふほうしんにゅうまでするとは…\n"
		.string "なんとふとどきなヤツであるか！▼"
		.string "チツジョをみだすことは\n"
		.string "ゆるされざることであーる！\n"
		.string "よって死けいであーる！$"

Text17: @ 0x08382ABC
	.string "{WINDOW 0x10}"
		.string "んんーっ！▼"
		.string "バイルさまの世界をみだすものは\n"
		.string "ワシがゆるさんのであーる！$"

Text18: @ 0x08382AE4
	.string "{WINDOW 0x10}"
		.string "ワシのさばきにすら…\n"
		.string "したがわぬと言うであるか…！▼"
		.string "バイルさま…このおろかものに…\n"
		.string "て…てんばつを…！▼"
		.string "ぬおおおおおおおおっ！$"

Text19: @ 0x08382B27
	.string "{WINDOW 0x23}"
		.string "ひ…ひひひっ…▼"
		.string "またきた…きやがった…！\n"
		.string "こわされに…きやがった…！▼"
		.string "ひひひっ…こわして…やる…！\n"
		.string "オマエなんか…こわしてやるぅ…！$"

Text20: @ 0x08382B6C
	.string "{WINDOW 0x12}"
		.string "ひひひひひひひっ！▼"
		.string "コイツめ！ コイツめ！\n"
		.string "こわれろ！ こわれろ！$"

Text21: @ 0x08382B90
	.string "{WINDOW 0x12}"
		.string "ひひ…ひ…こわしやがった…\n"
		.string "オレを…こわしやがった…！▼"
		.string "でも…オマエにはオメガは\n"
		.string "こわせない…ざ…ざまあみろーっ！▼"
		.string "ひひひひひゃはああああーーっ！$"

Text22: @ 0x08382BDC
	.string "{WINDOW 0x25}"
		.string "オレさまはジゴクのバンケンよぉ！▼"
		.string "テメエを入れるなと\n"
		.string "バイルさまに 言われてんだぁ！▼"
		.string "バラッバラにかみくだいてやるぜぇ！\n"
		.string "かくごしなぁ！$"

Text23: @ 0x08382C25
	.string "{WINDOW 0x14}"
		.string "ゴルルルルルウゥ！▼"
		.string "かみごたえねえなぁ！\n"
		.string "オレさまにゃあ\n"
		.string "ものたりねえぜぇ！$"

Text24: @ 0x08382C4E
	.string "{WINDOW 0x14}"
		.string "な…なんでだぁ…\n"
		.string "なんで…かみちぎれねえんだぁ…▼"
		.string "なんでまた…カラダがいてえんだぁ…\n"
		.string "いてえ…またいてえぞおおおおっ！▼"
		.string "ゴルルアアアアアアアアッ！$"

Text25: @ 0x08382C9A
	.string "{WINDOW 0x53}"
		.string "クーックックックッ……▼"
		.string "どうだ、ゼロ\n"
		.string "エイユウごっこは\n"
		.string "たのしいか…？ ん？▼"
	.string "{WINDOW 0x04}"
		.string "オマエのくだらんあそびには\n"
		.string "つきあいきれん……▼"
		.string "そろそろ終わりに\n"
		.string "させてもらうぞ…！▼"
	.string "{WINDOW 0x53}"
		.string "クーックックックッ……\n"
		.string "くだらんか……▼"
		.string "そうだろうとも\n"
		.string "レプリロイドには、\n"
		.string "リカイできまい▼"
		.string "すべてのものをシハイする\n"
		.string "このヨロコビは…▼"
		.string "人間にしか わからぬよ▼"
	.string "{WINDOW 0x04}"
		.string "人間……だと？$"

Text26: @ 0x08382D51
	.string "{WINDOW 0x53}"
		.string "{BOTTOM}そうとも！\n"
		.string "ワシは、れっきとした人間だ▼"
		.string "キサマらレプリロイドを\n"
		.string "生み出した…\n"
		.string "キサマらのソウゾウシュ…▼"
		.string "人間さまなのだよ！▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}………▼"
	.string "{WINDOW 0x53}"
		.string "{BOTTOM}シハイヨクとでも言おうか…\n"
		.string "すべてのものを\n"
		.string "いのままに動かすカイカン……▼"
		.string "これだけは、人間さまのズノウが\n"
		.string "なければあじわえん…\n"
		.string "キュウキョクのカイラクだよ……▼"
		.string "キサマらレプリロイドには\n"
		.string "わかるまい…！$"

Text27: @ 0x08382E0B
	.string "{WINDOW 0x04}"
		.string "まともな人間にも\n"
		.string "リカイできるとは、思えんな…▼"
		.string "オレにはオマエが\n"
		.string "ただのイレギュラーにしか見えん▼"
		.string "イレギュラーならば、かるまで…だ▼"
	.string "{WINDOW 0x53}"
		.string "クーックックックッ…▼"
		.string "いいぞ！▼"
		.string "いいセリフだ…ゼロ！\n"
		.string "さぞ、きもちよかろう！？$"

Text28: @ 0x08382E7D
	.string "{WINDOW 0x3F}"
		.string "オ…オオ…ゼ…ロ…！▼"
	.string "{WINDOW 0x53}"
		.string "オマエは、たのしいヤツだったよ▼"
		.string "いつまでも、いっしょに\n"
		.string "あそんでいたいが……\n"
		.string "そろそろ消えてもらうとするか▼"
		.string "まだまだ、おたのしみも\n"
		.string "ヨウイしてある…▼"
		.string "最後まで たのしんでくれよ\n"
		.string "ゼロ！$"

Text29: @ 0x08382EEC
	.string "{WINDOW 0x3F}"
		.string "グ…オオ…ゼェ…ロォ…！▼"
	.string "{WINDOW 0x53}"
		.string "クックック\n"
		.string "なかなかやるのう、ゼロ▼"
		.string "だが、オメガの本当のチカラは\n"
		.string "こんなもんではないぞ…▼"
		.string "さあ、ゆけい！ オメガ！▼"
		.string "ダークエルフのチカラを\n"
		.string "カイホウしろ！！$"

Text30: @ 0x08382F4E
	.string "{WINDOW 0x3F}"
		.string "オ…ウオオオオオオオッ！$"

Text31: @ 0x08382F5D
	.string "{WINDOW 0x04}"
		.string "ここは……$"

Text32: @ 0x08382F65
	.string "{WINDOW 0x04}"
		.string "オレがねむっていた場所……$"

Text33: @ 0x08382F75
	.string "{WINDOW 0x53}"
		.string "クククククーッ！\n"
		.string "みごとだぞ！ ゼロ！▼"
		.string "とてもニセモノとは\n"
		.string "思えんパワーだ▼"
	.string "{WINDOW 0x04}"
		.string "ニセモノだと！？$"

Text34: @ 0x08382FA9
	.string "{WINDOW 0x53}"
		.string "クックックッ…\n"
		.string "キサマが伝説のレプリロイド？\n"
		.string "おめでたいヤツよの…▼"
		.string "ここで見つけたレプリロイドを\n"
		.string "レジスタンスのばかどもが\n"
		.string "かってにゼロと呼んだだけだ…▼"
		.string "オマエも…\n"
		.string "たしかにゼロではあるが\n"
		.string "たんなるコピーだ▼"
		.string "伝説のエイユウでも\n"
		.string "なーんでもない\n"
		.string "たーだーのコピー…なのだよ！$"

Text35: @ 0x0838303A
	.string "{WINDOW 0x53}"
		.string "クックックッ…▼"
		.string "自分がコピーだと知らず\n"
		.string "エイユウをきどりおって…\n"
		.string "本当にわらわせるじゃないか▼"
		.string "オメガこそ\n"
		.string "ショウシンショウメイ…\n"
		.string "ホンモノのオリジナルゼロだ！▼"
		.string "オマエは\n"
		.string "そのコピーに過ぎん！！▼"
	.string "{WINDOW 0x04}"
		.string "オリジナルゼロが…▼"
		.string "なぜ、オマエの\n"
		.string "いいなりになっている…▼"
	.string "{WINDOW 0x53}"
		.string "ふん…！\n"
		.string "ヤツはチにうえたハカイ神…▼"
		.string "そのチカラを\n"
		.string "ゲンカイまでひきだせるよう\n"
		.string "改造してやっただけだ！！▼"
		.string "さぁオメガ…\n"
		.string "いや、オリジナルゼロよ！▼"
		.string "あわれなニセモノが\n"
		.string "100年見つづけたユメを…\n"
		.string "そろそろさましてやれ！！$"

Text36: @ 0x08383138
	.string "{WINDOW 0x04}"
		.string "オメガを……\n"
		.string "フッカツさせる…気か！？$"

Text37: @ 0x0838314F
	.string "{WINDOW 0x04}"
		.string "くっ…！▼"
	.string "{WINDOW 0x53}"
		.string "クックックッ…\n"
		.string "じゃませず見ておけ▼"
		.string "全ての人間……▼"
		.string "全てのレプリロイドのイノチは\n"
		.string "このワシが にぎっていることを\n"
		.string "わすれるな！！▼"
	.string "{WINDOW 0x04}"
		.string "ちっ……$"

Text38: @ 0x083831A5
	.string "{WINDOW 0x2C}"
		.string "ゼロ！\n"
		.string "何をしている！\n"
		.string "はやくたて！！$"

Text39: @ 0x083831BC
	.string "{WINDOW 0x30}"
		.string "オラァ！▼"
		.string "かりをかえしにきたぜ！\n"
		.string "オメガァ！$"

Text40: @ 0x083831D5
	.string "{WINDOW 0x2E}"
		.string "やられっぱなしって\n"
		.string "しょうにあわないのよね！$"

Text41: @ 0x083831EE
	.string "{WINDOW 0x04}"
		.string "オマエたち…！▼"
	.string "{WINDOW 0x2C}"
		.string "バイルが言うことは\n"
		.string "ハッタリだ…▼"
		.string "今のジョウタイでは\n"
		.string "ヤツは、何もできん▼"
	.string "{WINDOW 0x53}"
		.string "くっ……\n"
		.string "ダークエルフ！▼"
		.string "コイツらを…だまらせろ！$"

Text42: @ 0x0838323E
	.string "{WINDOW 0x39}"
		.string "ゼ……ロ………！▼"
	.string "{WINDOW 0x73}"
		.string "どうした…ダークエルフ…！？$"

Text43: @ 0x0838325A
	.string "{WINDOW 0x34}"
		.string "カノジョの…▼"
		.string "ダークエルフのノロイが\n"
		.string "とけかけている…▼"
	.string "{WINDOW 0x53}"
		.string "キサマッ…エックスかぁっ…！▼"
	.string "{WINDOW 0x34}"
		.string "そうだよバイル\n"
		.string "100年前と同じだね…▼"
		.string "あの時も、ボクは…\n"
		.string "ゼロとともに\n"
		.string "このオメガをたおし……▼"
		.string "あなたのヤボウから\n"
		.string "世界を守ったんだ…▼"
	.string "{WINDOW 0x04}"
		.string "100年前と…同じ……\n"
		.string "だと？▼"
	.string "{WINDOW 0x34}"
		.string "たしかにオメガは\n"
		.string "キミのオリジナル・ボディを\n"
		.string "使っている▼"
		.string "ただ、それだけだ…▼"
		.string "キミのカラダは\n"
		.string "たしかにコピーだけど……▼"
		.string "心は…まぎれもなくホンモノだよ……▼"
		.string "さぁ、ダークエルフの\n"
		.string "チカラが弱まってる今のうちに…▼"
		.string "100年前の\n"
		.string "ケッチャクをつけるんだ…ゼロ！$"

Text44: @ 0x08383374
	.string "{WINDOW 0x53}"
		.string "やめろゼロ！！▼"
		.string "オマエのオリジナル・ボディだぞ\n"
		.string "おしくはないのか！！▼"
		.string "いっしょう、そんな安っぽい\n"
		.string "ニセモノのカラダで生きていくと\n"
		.string "いうのか！！！▼"
	.string "{WINDOW 0x34}"
		.string "キミならできるさ▼"
		.string "本当にタイセツなものが何なのか\n"
		.string "キミには、わかっているはずだから…▼"
		.string "さあ…ゼロ！$"

Text45: @ 0x083833F8
	.string "{WINDOW 0x70}"
		.string "ゼ…ロ……\n"
		.string "ゼロ…▼"
		.string "目をさまして…\n"
		.string "ゼロ…$"

Text46: @ 0x08383411
	.string "{WINDOW 0x34}"
		.string "聞こえるかい…ゼロ▼"
		.string "ボクにはもう…ほとんどチカラが\n"
		.string "のこっていない…▼"
		.string "この世界に…長くいることも…\n"
		.string "むずかしくなってきたよ…▼"
		.string "ゼロ……▼"
		.string "キミに…\n"
		.string "この世界をまかせたい……▼"
		.string "まだこの世界から…\n"
		.string "バイルのキョウイは\n"
		.string "去っていない……▼"
		.string "人間と…レプリロイドを…\n"
		.string "守ってあげてほしい…▼"
		.string "ゼ…ロ……\n"
		.string "キミ…なら…できる\n"
		.string "キミ…な…ら………$"

Text47: @ 0x083834C4
	.string "{WINDOW 0x40}"
		.string "ゼロ…目をさまして…！$"

Text48: @ 0x083834D3
	.string "{WINDOW 0x40}"
		.string "ゼロ…！\n"
		.string "よかった…本当によかった…▼"
	.string "{WINDOW 0x6C}"
		.string "ゼロさん！\n"
		.string "気がついたんですね！！▼"
		.string "よかったー$"

Text49: @ 0x08383505
	.string "{WINDOW 0x6C}"
		.string "おーい！ みんなー！▼"
		.string "ゼロさんがおきたぞ！\n"
		.string "無事だったぞー！ やったー！$"

Text50: @ 0x0838352E
	.string "{WINDOW 0x05}"
		.string "ここは……\n"
		.string "レジスタンスベース……か▼"
		.string "いったい…だれが……$"

Text51: @ 0x0838354E
	.string "{WINDOW 0x38}"
		.string "ゼ…ロ…$"

Text52: @ 0x08383555
	.string "{WINDOW 0x05}"
		.string "{BOTTOM}ダークエルフ…？▼"
		.string "いや…オマエは……▼"
	.string "{WINDOW 0x43}"
		.string "カノジョがキミを\n"
		.string "ここまで、はこんでくれたんだ▼"
	.string "{WINDOW 0x38}"
		.string "…ゼ…ロ…▼"
	.string "{WINDOW 0x40}"
		.string "なんてやさしくて…\n"
		.string "あたたかなヒカリ……▼"
	.string "{WINDOW 0x05}"
		.string "マザーエルフ…▼"
		.string "バイルのノロイが…\n"
		.string "とけた……か…$"

Text53: @ 0x083835C0
	.string "{WINDOW 0x05}"
		.string "{BOTTOM}…おわなくて いいのか……▼"
	.string "{WINDOW 0x40}"
		.string "やっと自由になれたんだもの…▼"
		.string "バイルのこともあるけど…\n"
		.string "今はそっとしておいて\n"
		.string "あげましょう…$"

Text54: @ 0x08383605
	.string "{WINDOW 0x40}"
		.string "ゼロのこと…\n"
		.string "エックスから聞いたわ…▼"
	.string "{WINDOW 0x05}"
		.string "…そうか▼"
	.string "{WINDOW 0x40}"
		.string "あなたが\n"
		.string "何も気にしてないって\n"
		.string "わたし…知っているけど……▼"
	.string "{WINDOW 0x05}"
		.string "……？▼"
	.string "{WINDOW 0x40}"
		.string "あなたのカラダが\n"
		.string "たとえ…\n"
		.string "コピーであったとしても……▼"
		.string "あなたの心が あなたであるかぎり\n"
		.string "あなたは、ゼロ…▼"
		.string "ゼロ以外…何者でもないわ…$"

Text55: @ 0x08383696
	.string "{WINDOW 0x04}"
		.string "シエル………▼"
		.string "ありがとう…▼"
	.string "{WINDOW 0x41}"
		.string "ゼ、ゼロ……！$"

Text56: @ 0x083836B0
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}オレは、オレでしかない……▼"
		.string "オレは…▼"
		.string "……ゼロだ$"

.balign 4, 0
