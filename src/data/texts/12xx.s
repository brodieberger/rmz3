.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_WeilLabo:: @ 0x083825bc
	.2byte (Text_WeilLabo_Empty-Start), (Text_WeilLabo_YaaaaahILoveLordWeil-Start), (Text_WeilLabo_YaaaaaaahInscribeHisName-Start), (Text_WeilLabo_YaahHotSoHotI-Start), (Text_WeilLabo_YouDunderheadLordWeilS-Start), (Text_WeilLabo_YouSureAreSlow-Start), (Text_WeilLabo_OophYouCanHurryAs-Start), (Text_WeilLabo_YouSureAreA-Start)
	.2byte (Text_WeilLabo_GoBackHomeBackTo-Start), (Text_WeilLabo_KekekeYouSilly-Start), (Text_WeilLabo_WhatSTheUseOf-Start), (Text_WeilLabo_ChikaChikachikaWatchAsI-Start), (Text_WeilLabo_HowCouldIThe-Start), (Text_WeilLabo_WhatAreYouDoing-Start), (Text_WeilLabo_GoodNightLittle-Start), (Text_WeilLabo_Arrgh-Start)
	.2byte (Text_WeilLabo_HahFirstThieveryAnd-Start), (Text_WeilLabo_HahThoseWhoDisrupt-Start), (Text_WeilLabo_WhatIsThisYou-Start), (Text_WeilLabo_HeheheheSoYouReBack-Start), (Text_WeilLabo_HeheheheheheLookAtYou-Start), (Text_WeilLabo_HeheHe-Start), (Text_WeilLabo_IAmTheGuardDog-Start), (Text_WeilLabo_GrrarwooorrrThereSNotEnough-Start)
	.2byte (Text_WeilLabo_HHowDidThis-Start), (Text_WeilLabo_HeheheheHavingFunPlaying-Start), (Text_WeilLabo_ThatSRight-Start), (Text_WeilLabo_IBetMostDecent-Start), (Text_WeilLabo_OhOhHoZeeerrooYou-Start), (Text_WeilLabo_GrrrRarwrarrHehehe-Start), (Text_WeilLabo_Grrrrrrrrrrraawrr-Start), (Text_WeilLabo_WhatIsThisPlace-Start)
	.2byte (Text_WeilLabo_ThisIsWhereIWas-Start), (Text_WeilLabo_Hehehehehe-Start), (Text_WeilLabo_Hehehehe-Start), (Text_WeilLabo_HeheheheYouThoughtYouWere-Start), (Text_WeilLabo_YouPlanTo-Start), (Text_WeilLabo_GulpHehehe-Start), (Text_WeilLabo_HurryStandUp-Start), (Text_WeilLabo_HeyIMHereTo-Start)
	.2byte (Text_WeilLabo_TimeToStraighten-Start), (Text_WeilLabo_YouGuysWeilIsTrying-Start), (Text_WeilLabo_ZeeeerrooooWhatIsItDark-Start), (Text_WeilLabo_HerTheDarkElfS-Start), (Text_WeilLabo_ZeroDonTDoIt-Start), (Text_WeilLabo_ZeRo-Start), (Text_WeilLabo_CanYouHearMe-Start), (Text_WeilLabo_ZeroWakeUp-Start)
	.2byte (Text_WeilLabo_ZeroAhWhatARelief-Start), (Text_WeilLabo_HeyEveryoneMrZeroIs-Start), (Text_WeilLabo_WhereIsThisThe-Start), (Text_WeilLabo_Zerrroooo-Start), (Text_WeilLabo_DarkElfWaitNoYou-Start), (Text_WeilLabo_ShouldnTWeFollow-Start), (Text_WeilLabo_XToldMeAboutYou-Start), (Text_WeilLabo_CielThankYouZeZero-Start)
	.2byte (Text_WeilLabo_ItSJustMeI-Start)

Text_WeilLabo:: @ 0x0838262e
Start:

Text_WeilLabo_Empty: @ 0x0838262E
		.if ENGLISH
		.string "$"
		.else
		.string "$"
		.endif

Text_WeilLabo_YaaaaahILoveLordWeil: @ 0x0838262F
	@ EN: Yaaaaah! / I love Lord Weil's / new world! So hot! / I won't let you get / in the way! I'll / turn you to ashes!
	.if ENGLISH
	.string "{WINDOW 0x17}"
		.string "Yaaaaah!▼"
		.string "I love Lord Weil's\n"
		.string "new world! So hot!▼"
		.string "I won't let you get\n"
		.string "in the way! I'll\n"
		.string "turn you to ashes!$"
	.else
	.string "{WINDOW 0x17}"
		.string "シャハアアッ！▼"
		.string "バイルさまの作る新しい世界！\n"
		.string "いいねぇ！ あつくなってきたぜ！▼"
		.string "ジャマはさせねえぜ！\n"
		.string "ここでオマエをケシズミに\n"
		.string "してやるよ！$"
	.endif

Text_WeilLabo_YaaaaaaahInscribeHisName: @ 0x0838267C
	@ EN: Yaaaaaaah! / Inscribe his name / on the world! Our / ruler, Dr. Weeeeiil!
	.if ENGLISH
	.string "{WINDOW 0x06}"
		.string "Yaaaaaaah!▼"
		.string "Inscribe his name\n"
		.string "on the world! Our\n"
		.string "ruler, Dr. Weeeeiil!$"
	.else
	.string "{WINDOW 0x06}"
		.string "シャハアアアァッ！\n"
		.string "世界にきざめ！ しはいしゃの名！\n"
		.string "ドクターァァッバイルッ！$"
	.endif

Text_WeilLabo_YaahHotSoHotI: @ 0x083826A9
	@ EN: Yaah...hot...so hot! / I hope you writhe in / pain, alone in the / new world! / Yaahaaah!
	.if ENGLISH
	.string "{WINDOW 0x06}"
		.string "Yaah...hot...so hot!▼"
		.string "I hope you writhe in\n"
		.string "pain, alone in the\n"
		.string "new world!▼"
		.string "Yaahaaah!$"
	.else
	.string "{WINDOW 0x06}"
		.string "シャ…ハッ…あつい…あついぜ…！▼"
		.string "新しい世界で…ひとりで\n"
		.string "もがきくるしめ…！▼"
		.string "シャギャハアアアアッ！$"
	.endif

Text_WeilLabo_YouDunderheadLordWeilS: @ 0x083826E1
	@ EN: You dunderhead! / Lord Weil's ideals / were set in motion a / century ago! / Who are you to / complain now! Get / with the times! / Do you wanna get left / behind?
	.if ENGLISH
	.string "{WINDOW 0x19}"
		.string "You dunderhead!▼"
		.string "Lord Weil's ideals\n"
		.string "were set in motion a\n"
		.string "century ago!▼"
		.string "Who are you to\n"
		.string "complain now! Get\n"
		.string "with the times!▼"
		.string "Do you wanna get left\n"
		.string "behind?$"
	.else
	.string "{WINDOW 0x19}"
		.string "このノロマーッ！▼"
		.string "バイルさまの理想は100年前に\n"
		.string "できあがっていたんだーっ！▼"
		.string "今さらモンク言うなよなーっ！\n"
		.string "ジダイおくれのポンコツがーっ！\n"
		.string "ひとりで とりのこされてろーっ！$"
	.endif

Text_WeilLabo_YouSureAreSlow: @ 0x08382740
	@ EN: You sure are slow- / witted! / The times have past / you by!
	.if ENGLISH
	.string "{WINDOW 0x08}"
		.string "You sure are slow-\n"
		.string "witted!▼"
		.string "The times have past\n"
		.string "you by!$"
	.else
	.string "{WINDOW 0x08}"
		.string "ほんっとノロイなーっ！▼"
		.string "ジダイにまで\n"
		.string "のりおくれてるんじゃねーよっ！$"
	.endif

Text_WeilLabo_OophYouCanHurryAs: @ 0x08382765
	@ EN: *ooph!* / You can hurry as / fast as you want... / But you'll never / catch up with a / history that has / already passed you / by... / You'll be trailing / behind Lord Weil / forever! / *grimace* Arrrggh!
	.if ENGLISH
	.string "{WINDOW 0x08}"
		.string "*ooph!*▼"
		.string "You can hurry as\n"
		.string "fast as you want...▼"
		.string "But you'll never\n"
		.string "catch up with a\n"
		.string "history that has▼"
		.string "already passed you\n"
		.string "by...▼"
		.string "You'll be trailing\n"
		.string "behind Lord Weil\n"
		.string "forever!▼"
		.string "*grimace* Arrrggh!$"
	.else
	.string "{WINDOW 0x08}"
		.string "う…ぐっ…！▼"
		.string "オマエが\n"
		.string "いくらいそいだところで…▼"
		.string "動き出したレキシには\n"
		.string "おいつけねー…▼"
		.string "オマエはずっと…\n"
		.string "バイルさまに おいつけねーよ…！▼"
		.string "うっ…あああああああっ！$"
	.endif

Text_WeilLabo_YouSureAreA: @ 0x083827BC
	@ EN: You sure are a / boisterous lout. / Knock quietly next / time. Where are your / manners? / You have no right / to live in this new / world. / So I'll see that / you don't!
	.if ENGLISH
	.string "{WINDOW 0x1B}"
		.string "You sure are a\n"
		.string "boisterous lout.▼"
		.string "Knock quietly next\n"
		.string "time. Where are your\n"
		.string "manners?▼"
		.string "You have no right\n"
		.string "to live in this new\n"
		.string "world.▼"
		.string "So I'll see that\n"
		.string "you don't!$"
	.else
	.string "{WINDOW 0x1B}"
		.string "さわがしいですね▼"
		.string "ノックはしずかにするものですよ\n"
		.string "そんなマナーも知らないとは…▼"
		.string "この新しい世界で生きるシカクは\n"
		.string "…あなたには、ありませんっ！\n"
		.string "消えてもらいましょう！$"
	.endif

Text_WeilLabo_GoBackHomeBackTo: @ 0x08382817
	@ EN: Go back home. / Back to the depths, / where you slept all / those years away!
	.if ENGLISH
	.string "{WINDOW 0x0A}"
		.string "Go back home.▼"
		.string "Back to the depths,\n"
		.string "where you slept all\n"
		.string "those years away!$"
	.else
	.string "{WINDOW 0x0A}"
		.string "おかえりねがいましょうか▼"
		.string "あなたがねむっていた\n"
		.string "くらく…深い地のそこにね！$"
	.endif

Text_WeilLabo_KekekeYouSilly: @ 0x08382841
	@ EN: Kekeke... / You silly... / ...inconsiderate.. / barbarian! / Your type won't / survive in the new / world that's coming! / Kekeke...kekeeee!
	.if ENGLISH
	.string "{WINDOW 0x0A}"
		.string "Kekeke...▼"
		.string "You silly...\n"
		.string "...inconsiderate..\n"
		.string "barbarian!▼"
		.string "Your type won't\n"
		.string "survive in the new\n"
		.string "world that's coming!▼"
		.string "Kekeke...kekeeee!$"
	.else
	.string "{WINDOW 0x0A}"
		.string "キキッ…キ…▼"
		.string "なんと…おろかな…\n"
		.string "なんと…やばんな…！▼"
		.string "あなたのようなものが…\n"
		.string "新しい世界に生きのこるなど…！▼"
		.string "キキッ…キキキキーーッ！$"
	.endif

Text_WeilLabo_WhatSTheUseOf: @ 0x0838288C
	@ EN: What's the use of / century-old junk / in this new world? / I'll cut you down / and send you off to / the deadlands! / Chikachikachika!
	.if ENGLISH
	.string "{WINDOW 0x1D}"
		.string "What's the use of\n"
		.string "century-old junk\n"
		.string "in this new world?▼"
		.string "I'll cut you down\n"
		.string "and send you off to\n"
		.string "the deadlands!▼"
		.string "Chikachikachika!$"
	.else
	.string "{WINDOW 0x1D}"
		.string "100年前のガラクタなど\n"
		.string "この新しい世界には\n"
		.string "ヒツヨウない…！▼"
		.string "ここできりきざんで…\n"
		.string "すててきてやる…！ 死の世界になぁ！▼"
		.string "ギチギチギチギチィッ！$"
	.endif

Text_WeilLabo_ChikaChikachikaWatchAsI: @ 0x083828E0
	@ EN: Chika! Chikachika! / Watch as I slice / your old world and / all your friends to / ribbons! Chikaka!
	.if ENGLISH
	.string "{WINDOW 0x0C}"
		.string "Chika! Chikachika!▼"
		.string "Watch as I slice\n"
		.string "your old world and\n"
		.string "all your friends to▼"
		.string "ribbons! Chikaka!$"
	.else
	.string "{WINDOW 0x0C}"
		.string "ギチッ！ ギチチッ！▼"
		.string "そこで見てな…！\n"
		.string "古き世界と…テメエの仲間が\n"
		.string "きりきざまれる ところをな…！$"
	.endif

Text_WeilLabo_HowCouldIThe: @ 0x0838291A
	@ EN: How could I, the / newest and greatest, / lose to a century- / old piece of junk?! / Impossible... No, / I don't want to die. / I don't want to die! / Chikachikaaaaa!
	.if ENGLISH
	.string "{WINDOW 0x0C}"
		.string "How could I, the\n"
		.string "newest and greatest,\n"
		.string "lose to a century-▼"
		.string "old piece of junk?!▼"
		.string "Impossible... No,\n"
		.string "I don't want to die.\n"
		.string "I don't want to die!▼"
		.string "Chikachikaaaaa!$"
	.else
	.string "{WINDOW 0x0C}"
		.string "最新最強の このオレが…\n"
		.string "100年前のガラクタに\n"
		.string "まけるのか…！？▼"
		.string "ありえない…イヤ…だ…\n"
		.string "死にたくない…\n"
		.string "死にたくないぃぃ…！▼"
		.string "ギチッ…ギギギギギギーーーーッ！$"
	.endif

Text_WeilLabo_WhatAreYouDoing: @ 0x08382976
	@ EN: What are you doing / in a place like / this, little boy? / It's your bedtime... / You mustn't see the / world that lies / ahead, little boy. / You mustn't survive / to see it!
	.if ENGLISH
	.string "{WINDOW 0x1F}"
		.string "What are you doing\n"
		.string "in a place like\n"
		.string "this, little boy?▼"
		.string "It's your bedtime...▼"
		.string "You mustn't see the\n"
		.string "world that lies\n"
		.string "ahead, little boy.▼"
		.string "You mustn't survive\n"
		.string "to see it!$"
	.else
	.string "{WINDOW 0x1F}"
		.string "あらあら…こんなところまで\n"
		.string "来ちゃったのねぇ…ボウヤ▼"
		.string "おねむりなさい…▼"
		.string "ここからさきは、\n"
		.string "ボウヤの見ちゃいけない世界…▼"
		.string "オマエがいちゃいけない世界なの…！$"
	.endif

Text_WeilLabo_GoodNightLittle: @ 0x083829CC
	@ EN: Good night, little / boy. / I don't expect / you'll wake again! / Teeheehee!
	.if ENGLISH
	.string "{WINDOW 0x0E}"
		.string "Good night, little\n"
		.string "boy.▼"
		.string "I don't expect\n"
		.string "you'll wake again!▼"
		.string "Teeheehee!$"
	.else
	.string "{WINDOW 0x0E}"
		.string "ゆっくりとおやすみなさい▼"
		.string "もう、おきることも\n"
		.string "ないでしょうけどね！▼"
		.string "オーッホッホッホッホッ！$"
	.endif

Text_WeilLabo_Arrgh: @ 0x083829FD
	@ EN: Arrgh... / No need to throw / a temper tantrum... / All your struggles / will be in vain. / That's right. / You're no hero. And / you're no God of / Destruction, either. / There's...nothing... / you...can...do... / Arrrrrgh!
	.if ENGLISH
	.string "{WINDOW 0x0E}"
		.string "Arrgh...\n"
		.string "No need to throw\n"
		.string "a temper tantrum...▼"
		.string "All your struggles\n"
		.string "will be in vain.▼"
		.string "That's right.▼"
		.string "You're no hero. And\n"
		.string "you're no God of\n"
		.string "Destruction, either.▼"
		.string "There's...nothing...\n"
		.string "you...can...do...\n"
		.string "Arrrrrgh!$"
	.else
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
	.endif

Text_WeilLabo_HahFirstThieveryAnd: @ 0x08382A63
	@ EN: Hah! / First thievery, and / now unlawful entry! / How outrageous! / There is no mercy / for those who / disrupt the order! / I sentence you... / to death!
	.if ENGLISH
	.string "{WINDOW 0x21}"
		.string "Hah!▼"
		.string "First thievery, and\n"
		.string "now unlawful entry!\n"
		.string "How outrageous!▼"
		.string "There is no mercy\n"
		.string "for those who\n"
		.string "disrupt the order!▼"
		.string "I sentence you...\n"
		.string "to death!$"
	.else
	.string "{WINDOW 0x21}"
		.string "んんーっ！▼"
		.string "ドロボウにつづき、\n"
		.string "ふほうしんにゅうまでするとは…\n"
		.string "なんとふとどきなヤツであるか！▼"
		.string "チツジョをみだすことは\n"
		.string "ゆるされざることであーる！\n"
		.string "よって死けいであーる！$"
	.endif

Text_WeilLabo_HahThoseWhoDisrupt: @ 0x08382ABC
	@ EN: Hah! / Those who disrupt / Lord Weil's world / must face my wrath!
	.if ENGLISH
	.string "{WINDOW 0x10}"
		.string "Hah!▼"
		.string "Those who disrupt\n"
		.string "Lord Weil's world\n"
		.string "must face my wrath!$"
	.else
	.string "{WINDOW 0x10}"
		.string "んんーっ！▼"
		.string "バイルさまの世界をみだすものは\n"
		.string "ワシがゆるさんのであーる！$"
	.endif

Text_WeilLabo_WhatIsThisYou: @ 0x08382AE4
	@ EN: What is this? You / dare to defy my / judgment?! / Lord Weil...strike / down this foolish / one! / Ugghhh!!!
	.if ENGLISH
	.string "{WINDOW 0x10}"
		.string "What is this? You\n"
		.string "dare to defy my\n"
		.string "judgment?!▼"
		.string "Lord Weil...strike\n"
		.string "down this foolish\n"
		.string "one!▼"
		.string "Ugghhh!!!$"
	.else
	.string "{WINDOW 0x10}"
		.string "ワシのさばきにすら…\n"
		.string "したがわぬと言うであるか…！▼"
		.string "バイルさま…このおろかものに…\n"
		.string "て…てんばつを…！▼"
		.string "ぬおおおおおおおおっ！$"
	.endif

Text_WeilLabo_HeheheheSoYouReBack: @ 0x08382B27
	@ EN: Hehehehe! / So you're back! / Back again, ready to / be broken! / Hehehe! I'll do it, / I don't mind!
	.if ENGLISH
	.string "{WINDOW 0x23}"
		.string "Hehehehe!▼"
		.string "So you're back!\n"
		.string "Back again, ready to\n"
		.string "be broken!▼"
		.string "Hehehe! I'll do it,\n"
		.string "I don't mind!$"
	.else
	.string "{WINDOW 0x23}"
		.string "ひ…ひひひっ…▼"
		.string "またきた…きやがった…！\n"
		.string "こわされに…きやがった…！▼"
		.string "ひひひっ…こわして…やる…！\n"
		.string "オマエなんか…こわしてやるぅ…！$"
	.endif

Text_WeilLabo_HeheheheheheLookAtYou: @ 0x08382B6C
	@ EN: Hehehehehehe! / Look at you! / You're broken now! / hehehe!
	.if ENGLISH
	.string "{WINDOW 0x12}"
		.string "Hehehehehehe!▼"
		.string "Look at you!\n"
		.string "You're broken now!\n"
		.string "hehehe!$"
	.else
	.string "{WINDOW 0x12}"
		.string "ひひひひひひひっ！▼"
		.string "コイツめ！ コイツめ！\n"
		.string "こわれろ！ こわれろ！$"
	.endif

Text_WeilLabo_HeheHe: @ 0x08382B90
	@ EN: Hehe...he... / You broke me! / But you won't be / able to break Omega! / I guarantee that! / Heheheheheheeee! / *groan*
	.if ENGLISH
	.string "{WINDOW 0x12}"
		.string "Hehe...he...\n"
		.string "You broke me!▼"
		.string "But you won't be\n"
		.string "able to break Omega!\n"
		.string "I guarantee that!▼"
		.string "Heheheheheheeee!\n"
		.string "*groan*$"
	.else
	.string "{WINDOW 0x12}"
		.string "ひひ…ひ…こわしやがった…\n"
		.string "オレを…こわしやがった…！▼"
		.string "でも…オマエにはオメガは\n"
		.string "こわせない…ざ…ざまあみろーっ！▼"
		.string "ひひひひひゃはああああーーっ！$"
	.endif

Text_WeilLabo_IAmTheGuardDog: @ 0x08382BDC
	@ EN: I am the guard dog / of Hades! / Lord Weil instructed / me not to let you / in. / I'll bite you to / chunks! Come and get / it!
	.if ENGLISH
	.string "{WINDOW 0x25}"
		.string "I am the guard dog\n"
		.string "of Hades!▼"
		.string "Lord Weil instructed\n"
		.string "me not to let you\n"
		.string "in.▼"
		.string "I'll bite you to\n"
		.string "chunks! Come and get\n"
		.string "it!$"
	.else
	.string "{WINDOW 0x25}"
		.string "オレさまはジゴクのバンケンよぉ！▼"
		.string "テメエを入れるなと\n"
		.string "バイルさまに 言われてんだぁ！▼"
		.string "バラッバラにかみくだいてやるぜぇ！\n"
		.string "かくごしなぁ！$"
	.endif

Text_WeilLabo_GrrarwooorrrThereSNotEnough: @ 0x08382C25
	@ EN: Grrarwooorrr! / There's not enough / meat on your bones! / I'm still hungry!
	.if ENGLISH
	.string "{WINDOW 0x14}"
		.string "Grrarwooorrr!▼"
		.string "There's not enough\n"
		.string "meat on your bones!\n"
		.string "I'm still hungry!$"
	.else
	.string "{WINDOW 0x14}"
		.string "ゴルルルルルウゥ！▼"
		.string "かみごたえねえなぁ！\n"
		.string "オレさまにゃあ\n"
		.string "ものたりねえぜぇ！$"
	.endif

Text_WeilLabo_HHowDidThis: @ 0x08382C4E
	@ EN: H-how did this / happen? Why can't I / bite you to chunks? / Why do I hurt all / over again? Ouch. / Ouch. Ouuuuuch!!! / Grrauwruurrrr!
	.if ENGLISH
	.string "{WINDOW 0x14}"
		.string "H-how did this\n"
		.string "happen? Why can't I\n"
		.string "bite you to chunks?▼"
		.string "Why do I hurt all\n"
		.string "over again? Ouch.\n"
		.string "Ouch. Ouuuuuch!!!▼"
		.string "Grrauwruurrrr!$"
	.else
	.string "{WINDOW 0x14}"
		.string "な…なんでだぁ…\n"
		.string "なんで…かみちぎれねえんだぁ…▼"
		.string "なんでまた…カラダがいてえんだぁ…\n"
		.string "いてえ…またいてえぞおおおおっ！▼"
		.string "ゴルルアアアアアアアアッ！$"
	.endif

Text_WeilLabo_HeheheheHavingFunPlaying: @ 0x08382C9A
	@ EN: Hehehehe... / Having fun playing / the hero, Zero? / Hmmm? / You do understand, / don't you, that I / have no time for / your petty games? / So let's finish this / for once and for / all, shall we? / Hehehehe... / How pitiful. / Of course, a Reploid / like you would never / understand. / The joy of ruling / all that you see... / Only a human could / possibly understand! / A...human?
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Hehehehe...▼"
		.string "Having fun playing\n"
		.string "the hero, Zero?\n"
		.string "Hmmm?▼"
	.string "{WINDOW 0x04}"
		.string "You do understand,\n"
		.string "don't you, that I\n"
		.string "have no time for▼"
		.string "your petty games?▼"
		.string "So let's finish this\n"
		.string "for once and for\n"
		.string "all, shall we?▼"
	.string "{WINDOW 0x53}"
		.string "Hehehehe...\n"
		.string "How pitiful.▼"
		.string "Of course, a Reploid\n"
		.string "like you would never\n"
		.string "understand.▼"
		.string "The joy of ruling\n"
		.string "all that you see...▼"
		.string "Only a human could\n"
		.string "possibly understand!▼"
	.string "{WINDOW 0x04}"
		.string "A...human?$"
	.else
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
	.endif

Text_WeilLabo_ThatSRight: @ 0x08382D51
	@ EN: That's right! / I'm a bona fide / human. / The creator of / Reploids... / A human being! / ... / The desire for / power. The joy of / making everything / work for you. / You have no way of / experiencing this / without a human / brain. It's the / ultimate joy! / No mere Reploid / could ever / understand!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "{BOTTOM}That's right!\n"
		.string "I'm a bona fide\n"
		.string "human.▼"
		.string "The creator of\n"
		.string "Reploids...▼"
		.string "A human being!▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}...▼"
	.string "{WINDOW 0x53}"
		.string "{BOTTOM}The desire for\n"
		.string "power. The joy of\n"
		.string "making everything▼"
		.string "work for you.\n"
		.string "You have no way of\n"
		.string "experiencing this▼"
		.string "without a human\n"
		.string "brain. It's the\n"
		.string "ultimate joy!▼"
		.string "No mere Reploid\n"
		.string "could ever\n"
		.string "understand!$"
	.else
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
	.endif

Text_WeilLabo_IBetMostDecent: @ 0x08382E0B
	@ EN: I bet most decent / humans wouldn't / understand, either. / You look like just / another Maverick, / to me. / All I gotta do is / dispose of you like / any other Maverick. / Hehehehe... / Good, good! / An excellent speech, / Zero! You must feel / great, right?!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "I bet most decent\n"
		.string "humans wouldn't\n"
		.string "understand, either.▼"
		.string "You look like just\n"
		.string "another Maverick,\n"
		.string "to me.▼"
		.string "All I gotta do is\n"
		.string "dispose of you like\n"
		.string "any other Maverick.▼"
	.string "{WINDOW 0x53}"
		.string "Hehehehe...▼"
		.string "Good, good!▼"
		.string "An excellent speech,\n"
		.string "Zero! You must feel\n"
		.string "great, right?!$"
	.else
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
	.endif

Text_WeilLabo_OhOhHoZeeerrooYou: @ 0x08382E7D
	@ EN: Oh, oh ho, Zeeerroo! / You were a fun guy, / Zero! / I'd like to play / some more, but it's / time we parted. / I have some more fun / surprises left in / store for you... / Enjoy them to the / last, Zero!
	.if ENGLISH
	.string "{WINDOW 0x3F}"
		.string "Oh, oh ho, Zeeerroo!▼"
	.string "{WINDOW 0x53}"
		.string "You were a fun guy,\n"
		.string "Zero!▼"
		.string "I'd like to play\n"
		.string "some more, but it's\n"
		.string "time we parted.▼"
		.string "I have some more fun\n"
		.string "surprises left in\n"
		.string "store for you...▼"
		.string "Enjoy them to the\n"
		.string "last, Zero!$"
	.else
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
	.endif

Text_WeilLabo_GrrrRarwrarrHehehe: @ 0x08382EEC
	@ EN: Grrr... Rarwrarr! / Hehehe... / Not bad, Zero. / But Omega's true / power is much / greater than you've / been led to expect. / Go get him, Omega! / Release the power of / the Dark Elf!!!
	.if ENGLISH
	.string "{WINDOW 0x3F}"
		.string "Grrr... Rarwrarr!▼"
	.string "{WINDOW 0x53}"
		.string "Hehehe...\n"
		.string "Not bad, Zero.▼"
		.string "But Omega's true\n"
		.string "power is much\n"
		.string "greater than you've▼"
		.string "been led to expect.▼"
		.string "Go get him, Omega!▼"
		.string "Release the power of\n"
		.string "the Dark Elf!!!$"
	.else
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
	.endif

Text_WeilLabo_Grrrrrrrrrrraawrr: @ 0x08382F4E
	@ EN: GrrrrrrRRRRRAAWRR!!!
	.if ENGLISH
	.string "{WINDOW 0x3F}"
		.string "GrrrrrrRRRRRAAWRR!!!$"
	.else
	.string "{WINDOW 0x3F}"
		.string "オ…ウオオオオオオオッ！$"
	.endif

Text_WeilLabo_WhatIsThisPlace: @ 0x08382F5D
	@ EN: What is this place?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "What is this place?$"
	.else
	.string "{WINDOW 0x04}"
		.string "ここは……$"
	.endif

Text_WeilLabo_ThisIsWhereIWas: @ 0x08382F65
	@ EN: This is where I was / sleeping...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "This is where I was\n"
		.string "sleeping...$"
	.else
	.string "{WINDOW 0x04}"
		.string "オレがねむっていた場所……$"
	.endif

Text_WeilLabo_Hehehehehe: @ 0x08382F75
	@ EN: Hehehehehe! / Excellent, Zero! / Your power is extra- / ordinary, for a / mere fake. / Fake?!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Hehehehehe!\n"
		.string "Excellent, Zero!▼"
		.string "Your power is extra-\n"
		.string "ordinary, for a\n"
		.string "mere fake.▼"
	.string "{WINDOW 0x04}"
		.string "Fake?!$"
	.else
	.string "{WINDOW 0x53}"
		.string "クククククーッ！\n"
		.string "みごとだぞ！ ゼロ！▼"
		.string "とてもニセモノとは\n"
		.string "思えんパワーだ▼"
	.string "{WINDOW 0x04}"
		.string "ニセモノだと！？$"
	.endif

Text_WeilLabo_Hehehehe: @ 0x08382FA9
	@ EN: Hehehehe... / You, the legendary / Reploid? You fool! / Those Resistance / losers just decided / to call the Reploid / they found here / "Zero" for some / reason... / You may be Zero, in / a way, but you are / still merely a copy. / You're no legendary / hero at all. You're / just a reproduction!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Hehehehe...\n"
		.string "You, the legendary\n"
		.string "Reploid? You fool!▼"
		.string "Those Resistance\n"
		.string "losers just decided\n"
		.string "to call the Reploid▼"
		.string "they found here\n"
		.string "{0xE9}Zero{0xE9} for some\n"
		.string "reason...▼"
		.string "You may be Zero, in\n"
		.string "a way, but you are\n"
		.string "still merely a copy.▼"
		.string "You're no legendary\n"
		.string "hero at all. You're\n"
		.string "just a reproduction!$"
	.else
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
	.endif

Text_WeilLabo_HeheheheYouThoughtYouWere: @ 0x0838303A
	@ EN: Hehehehe... / You thought you were / a hero all along, / didn't you! Never / suspecting that you / were a mere copy. / What a joke! / Omega himself is the / one and only, / original Zero! / You're just a copy / of him! / The original Zero... / Why is he your / slave, then? / Hmph! / He's a bloodthirsty / God of Destruction, / All I did was / upgrade him to draw / out all his power! / All right, Omega... / ...or should I say / "Original Zero"! / Time to wake this / pitiful fake from a / century-long dream!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Hehehehe...▼"
		.string "You thought you were\n"
		.string "a hero all along,\n"
		.string "didn't you! Never▼"
		.string "suspecting that you\n"
		.string "were a mere copy.\n"
		.string "What a joke!▼"
		.string "Omega himself is the\n"
		.string "one and only,\n"
		.string "original Zero!▼"
		.string "You're just a copy\n"
		.string "of him!▼"
	.string "{WINDOW 0x04}"
		.string "The original Zero...▼"
		.string "Why is he your\n"
		.string "slave, then?▼"
	.string "{WINDOW 0x53}"
		.string "Hmph!\n"
		.string "He's a bloodthirsty\n"
		.string "God of Destruction,▼"
		.string "All I did was\n"
		.string "upgrade him to draw\n"
		.string "out all his power!▼"
		.string "All right, Omega...\n"
		.string "...or should I say\n"
		.string "{0xE9}Original Zero{0xE9}!▼"
		.string "Time to wake this\n"
		.string "pitiful fake from a\n"
		.string "century-long dream!$"
	.else
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
	.endif

Text_WeilLabo_YouPlanTo: @ 0x08383138
	@ EN: You plan to... / reactivate Omega?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "You plan to...\n"
		.string "reactivate Omega?$"
	.else
	.string "{WINDOW 0x04}"
		.string "オメガを……\n"
		.string "フッカツさせる…気か！？$"
	.endif

Text_WeilLabo_GulpHehehe: @ 0x0838314F
	@ EN: *gulp!* / Hehehe... / Watch, but don't / interfere. / Don't forget... / I hold the lives of / all humans and / Reploids in my hand! / Erk!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "*gulp!*▼"
	.string "{WINDOW 0x53}"
		.string "Hehehe...\n"
		.string "Watch, but don't\n"
		.string "interfere.▼"
		.string "Don't forget...▼"
		.string "I hold the lives of\n"
		.string "all humans and\n"
		.string "Reploids in my hand!▼"
	.string "{WINDOW 0x04}"
		.string "Erk!$"
	.else
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
	.endif

Text_WeilLabo_HurryStandUp: @ 0x083831A5
	@ EN: Zero! / What are you doing?! / Hurry, stand up!!!
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "Zero!\n"
		.string "What are you doing?!\n"
		.string "Hurry, stand up!!!$"
	.else
	.string "{WINDOW 0x2C}"
		.string "ゼロ！\n"
		.string "何をしている！\n"
		.string "はやくたて！！$"
	.endif

Text_WeilLabo_HeyIMHereTo: @ 0x083831BC
	@ EN: Hey! / I'm here to get a / little payback, / Omega!
	.if ENGLISH
	.string "{WINDOW 0x30}"
		.string "Hey!▼"
		.string "I'm here to get a\n"
		.string "little payback,\n"
		.string "Omega!$"
	.else
	.string "{WINDOW 0x30}"
		.string "オラァ！▼"
		.string "かりをかえしにきたぜ！\n"
		.string "オメガァ！$"
	.endif

Text_WeilLabo_TimeToStraighten: @ 0x083831D5
	@ EN: Time to straighten / the record!
	.if ENGLISH
	.string "{WINDOW 0x2E}"
		.string "Time to straighten\n"
		.string "the record!$"
	.else
	.string "{WINDOW 0x2E}"
		.string "やられっぱなしって\n"
		.string "しょうにあわないのよね！$"
	.endif

Text_WeilLabo_YouGuysWeilIsTrying: @ 0x083831EE
	@ EN: You guys! / Weil is trying to / bluff you... / He can't do anything / in his current / state. / Argh! / Dark Elf! / Shut them up!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "You guys!▼"
	.string "{WINDOW 0x2C}"
		.string "Weil is trying to\n"
		.string "bluff you...▼"
		.string "He can't do anything\n"
		.string "in his current\n"
		.string "state.▼"
	.string "{WINDOW 0x53}"
		.string "Argh!\n"
		.string "Dark Elf!▼"
		.string "Shut them up!$"
	.else
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
	.endif

Text_WeilLabo_ZeeeerrooooWhatIsItDark: @ 0x0838323E
	@ EN: Zeeeerroooo! / What is it, Dark / Elf?!
	.if ENGLISH
	.string "{WINDOW 0x39}"
		.string "Zeeeerroooo!▼"
	.string "{WINDOW 0x73}"
		.string "What is it, Dark\n"
		.string "Elf?!$"
	.else
	.string "{WINDOW 0x39}"
		.string "ゼ……ロ………！▼"
	.string "{WINDOW 0x73}"
		.string "どうした…ダークエルフ…！？$"
	.endif

Text_WeilLabo_HerTheDarkElfS: @ 0x0838325A
	@ EN: Her... / The Dark Elf's / curse is fading... / Who's that! X?! / That's right, Weil. / Just like a century / ago... / I worked with Zero / to defeat this / Omega then... / And we saved the / world from your / greedy clutches. / Just like...a / century ago? / The defeated Omega / is using your / original body. / That's all... / Your current body / may be a copy... / But your heart is / the real thing. / All right, now's the / time. While the Dark / Elf's power is weak. / Time to finish what / you started a / century ago, Zero!
	.if ENGLISH
	.string "{WINDOW 0x34}"
		.string "Her...▼"
		.string "The Dark Elf's\n"
		.string "curse is fading...▼"
	.string "{WINDOW 0x53}"
		.string "Who's that! X?!▼"
	.string "{WINDOW 0x34}"
		.string "That's right, Weil.\n"
		.string "Just like a century\n"
		.string "ago...▼"
		.string "I worked with Zero\n"
		.string "to defeat this\n"
		.string "Omega then...▼"
		.string "And we saved the\n"
		.string "world from your\n"
		.string "greedy clutches.▼"
	.string "{WINDOW 0x04}"
		.string "Just like...a\n"
		.string "century ago?▼"
	.string "{WINDOW 0x34}"
		.string "The defeated Omega\n"
		.string "is using your\n"
		.string "original body.▼"
		.string "That's all...▼"
		.string "Your current body\n"
		.string "may be a copy...▼"
		.string "But your heart is\n"
		.string "the real thing.▼"
		.string "All right, now's the\n"
		.string "time. While the Dark\n"
		.string "Elf's power is weak.▼"
		.string "Time to finish what\n"
		.string "you started a\n"
		.string "century ago, Zero!$"
	.else
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
	.endif

Text_WeilLabo_ZeroDonTDoIt: @ 0x08383374
	@ EN: Zero, don't do it!!! / That's your original / body! Don't you feel / any attachment?! / Are you really / prepared to spend / the rest of your / life in that cheap / fake?! / You can do it. / You know what's / truly important. / Go on, Zero!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Zero, don't do it!!!▼"
		.string "That's your original\n"
		.string "body! Don't you feel\n"
		.string "any attachment?!▼"
		.string "Are you really\n"
		.string "prepared to spend\n"
		.string "the rest of your▼"
		.string "life in that cheap\n"
		.string "fake?!▼"
	.string "{WINDOW 0x34}"
		.string "You can do it.▼"
		.string "You know what's\n"
		.string "truly important.▼"
		.string "Go on, Zero!$"
	.else
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
	.endif

Text_WeilLabo_ZeRo: @ 0x083833F8
	@ EN: Ze...ro... / Zero... / Wake up... / Zero...
	.if ENGLISH
	.string "{WINDOW 0x70}"
		.string "Ze...ro...\n"
		.string "Zero...▼"
		.string "Wake up...\n"
		.string "Zero...$"
	.else
	.string "{WINDOW 0x70}"
		.string "ゼ…ロ……\n"
		.string "ゼロ…▼"
		.string "目をさまして…\n"
		.string "ゼロ…$"
	.endif

Text_WeilLabo_CanYouHearMe: @ 0x08383411
	@ EN: Can you hear me, / Zero? / My energy is almost / all spent. / I can't...stay in / this world...much / longer. / Zero... / I want to leave this / world in your care. / The threat Weil / represents has not / left this world. / I want you...to / protect humans and / Reploids. / Ze...ro... / You can do it... / You...can...
	.if ENGLISH
	.string "{WINDOW 0x34}"
		.string "Can you hear me,\n"
		.string "Zero?▼"
		.string "My energy is almost\n"
		.string "all spent.▼"
		.string "I can't...stay in\n"
		.string "this world...much\n"
		.string "longer.▼"
		.string "Zero...▼"
		.string "I want to leave this\n"
		.string "world in your care.▼"
		.string "The threat Weil\n"
		.string "represents has not\n"
		.string "left this world.▼"
		.string "I want you...to\n"
		.string "protect humans and\n"
		.string "Reploids.▼"
		.string "Ze...ro...\n"
		.string "You can do it...\n"
		.string "You...can...$"
	.else
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
	.endif

Text_WeilLabo_ZeroWakeUp: @ 0x083834C4
	@ EN: Zero, wake up!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero, wake up!$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…目をさまして…！$"
	.endif

Text_WeilLabo_ZeroAhWhatARelief: @ 0x083834D3
	@ EN: Zero! / Ah, what a relief! / I was so worried / about you... / Mr. Zero! You've / regained / consciousness! / What a relief...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero!▼"
		.string "Ah, what a relief!\n"
		.string "I was so worried\n"
		.string "about you...▼"
	.string "{WINDOW 0x6C}"
		.string "Mr. Zero! You've\n"
		.string "regained\n"
		.string "consciousness!▼"
		.string "What a relief...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…！\n"
		.string "よかった…本当によかった…▼"
	.string "{WINDOW 0x6C}"
		.string "ゼロさん！\n"
		.string "気がついたんですね！！▼"
		.string "よかったー$"
	.endif

Text_WeilLabo_HeyEveryoneMrZeroIs: @ 0x08383505
	@ EN: Hey! Everyone! / Mr. Zero is awake! / He's all right! / Yahooo!!!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Hey! Everyone!▼"
		.string "Mr. Zero is awake!\n"
		.string "He's all right!\n"
		.string "Yahooo!!!$"
	.else
	.string "{WINDOW 0x6C}"
		.string "おーい！ みんなー！▼"
		.string "ゼロさんがおきたぞ！\n"
		.string "無事だったぞー！ やったー！$"
	.endif

Text_WeilLabo_WhereIsThisThe: @ 0x0838352E
	@ EN: Where is this...the / Resistance Base? / Who could have...?
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Where is this...the\n"
		.string "Resistance Base?▼"
		.string "Who could have...?$"
	.else
	.string "{WINDOW 0x05}"
		.string "ここは……\n"
		.string "レジスタンスベース……か▼"
		.string "いったい…だれが……$"
	.endif

Text_WeilLabo_Zerrroooo: @ 0x0838354E
	@ EN: Zerrroooo...
	.if ENGLISH
	.string "{WINDOW 0x38}"
		.string "Zerrroooo...$"
	.else
	.string "{WINDOW 0x38}"
		.string "ゼ…ロ…$"
	.endif

Text_WeilLabo_DarkElfWaitNoYou: @ 0x08383555
	@ EN: Dark Elf? / Wait, no. You are... / She brought you back / here. / Ze...ro... / What a warm, gentle / light... / Mother Elf... / Has Weil's curse / been broken?
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "{BOTTOM}Dark Elf?▼"
		.string "Wait, no. You are...▼"
	.string "{WINDOW 0x43}"
		.string "She brought you back\n"
		.string "here.▼"
	.string "{WINDOW 0x38}"
		.string "Ze...ro...▼"
	.string "{WINDOW 0x40}"
		.string "What a warm, gentle\n"
		.string "light...▼"
	.string "{WINDOW 0x05}"
		.string "Mother Elf...▼"
		.string "Has Weil's curse\n"
		.string "been broken?$"
	.else
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
	.endif

Text_WeilLabo_ShouldnTWeFollow: @ 0x083835C0
	@ EN: Shouldn't we follow / her? / She's finally free. / There's still Weil, / but let's let her go / in peace for now.
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "{BOTTOM}Shouldn't we follow\n"
		.string "her?▼"
	.string "{WINDOW 0x40}"
		.string "She's finally free.▼"
		.string "There's still Weil,\n"
		.string "but let's let her go\n"
		.string "in peace for now.$"
	.else
	.string "{WINDOW 0x05}"
		.string "{BOTTOM}…おわなくて いいのか……▼"
	.string "{WINDOW 0x40}"
		.string "やっと自由になれたんだもの…▼"
		.string "バイルのこともあるけど…\n"
		.string "今はそっとしておいて\n"
		.string "あげましょう…$"
	.endif

Text_WeilLabo_XToldMeAboutYou: @ 0x08383605
	@ EN: X told me about you, / Zero. / Really... / I know you're not / worried about a / thing, but... / ? / Even if your body is / a copy... / As long as your / heart is your own, / you are Zero. / The one and only, / Zero...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "X told me about you,\n"
		.string "Zero.▼"
	.string "{WINDOW 0x05}"
		.string "Really...▼"
	.string "{WINDOW 0x40}"
		.string "I know you're not\n"
		.string "worried about a\n"
		.string "thing, but...▼"
	.string "{WINDOW 0x05}"
		.string "?▼"
	.string "{WINDOW 0x40}"
		.string "Even if your body is\n"
		.string "a copy...▼"
		.string "As long as your\n"
		.string "heart is your own,\n"
		.string "you are Zero.▼"
		.string "The one and only,\n"
		.string "Zero...$"
	.else
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
	.endif

Text_WeilLabo_CielThankYouZeZero: @ 0x08383696
	@ EN: Ciel... / Thank you. / Ze-Zero!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Ciel...▼"
		.string "Thank you.▼"
	.string "{WINDOW 0x41}"
		.string "Ze-Zero!$"
	.else
	.string "{WINDOW 0x04}"
		.string "シエル………▼"
		.string "ありがとう…▼"
	.string "{WINDOW 0x41}"
		.string "ゼ、ゼロ……！$"
	.endif

Text_WeilLabo_ItSJustMeI: @ 0x083836B0
	@ EN: It's just me... / I am... / ...Zero.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}It's just me...▼"
		.string "I am...▼"
		.string "...Zero.$"
	.else
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}オレは、オレでしかない……▼"
		.string "オレは…▼"
		.string "……ゼロだ$"
	.endif

.balign 4, 0
