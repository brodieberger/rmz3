.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SubArcadia:: @ 0x083820fc
	.2byte (Text_SubArcadia_Empty-Start),  (Text_SubArcadia_DrWeil-Start), (Text_SubArcadia_HeheheheheeeHowGallantYouAre-Start), (Text_SubArcadia_CreaPrea-Start), (Text_SubArcadia_HeSBack-Start), (Text_SubArcadia_HeSBack_2-Start), (Text_SubArcadia_ILlRipYouTo-Start), (Text_SubArcadia_ILlTearYouTo-Start)
	.2byte (Text_SubArcadia_Ahahahahahahaa-Start),  (Text_SubArcadia_PreaThereS-Start), (Text_SubArcadia_YesCreaThereS-Start), (Text_SubArcadia_IFeelLikeIM-Start), (Text_SubArcadia_IFeelLikeIM_2-Start), (Text_SubArcadia_CielZeroAreYouAllright-Start), (Text_SubArcadia_Understood-Start), (Text_SubArcadia_INeverThoughtI-Start)
	.2byte (Text_SubArcadia_AllLegendsAre-Start), (Text_SubArcadia_GaspYouTrulyDid-Start)

Text_SubArcadia:: @ 0x08382120
Start:

Text_SubArcadia_Empty: @ 0x08382120
		.if ENGLISH
		.string "$"
		.else
		.string "$"
		.endif

Text_SubArcadia_DrWeil: @ 0x08382121
	@ EN: Dr. Weil!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Dr. Weil!$"
	.else
	.string "{WINDOW 0x04}"
		.string "ドクター・バイル…！$"
	.endif

Text_SubArcadia_HeheheheheeeHowGallantYouAre: @ 0x0838212E
	@ EN: Heheheheheee... / How gallant you are, / Zero. To play hero, / all by yourself! / All the Reploids in / the entire world are / now under my power. / Humans are like / pigs, dependent upon / the Reploids for / their very / existence... / You do realize, / don't you, that if I / felt like it, / I could wipe all / humans out in the / blink of an eye?
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "Heheheheheee...▼"
		.string "How gallant you are,\n"
		.string "Zero. To play hero,\n"
		.string "all by yourself!▼"
		.string "All the Reploids in\n"
		.string "the entire world are\n"
		.string "now under my power.▼"
		.string "Humans are like\n"
		.string "pigs, dependent upon\n"
		.string "the Reploids for▼"
		.string "their very\n"
		.string "existence...▼"
		.string "You do realize,\n"
		.string "don't you, that if I\n"
		.string "felt like it,▼"
		.string "I could wipe all\n"
		.string "humans out in the\n"
		.string "blink of an eye?$"
	.else
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
	.endif

Text_SubArcadia_CreaPrea: @ 0x083821BD
	@ EN: Crea! Prea! / Do with this one as / you please! / I've got some pig / squeals to enjoy. / The squeals of / indolent pigs, / wasting their / pitiful lives on / idle pursuits. / Would you like to / know who rules this / world?! / Heheheheheee... / Bwahahahahah!
	.if ENGLISH
	.string "{WINDOW 0x53}"
		.string "Crea! Prea!\n"
		.string "Do with this one as\n"
		.string "you please!▼"
		.string "I've got some pig\n"
		.string "squeals to enjoy.▼"
		.string "The squeals of\n"
		.string "indolent pigs,\n"
		.string "wasting their▼"
		.string "pitiful lives on\n"
		.string "idle pursuits.▼"
		.string "Would you like to\n"
		.string "know who rules this\n"
		.string "world?!▼"
		.string "Heheheheheee...▼"
		.string "Bwahahahahah!$"
	.else
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
	.endif

Text_SubArcadia_HeSBack: @ 0x08382248
	@ EN: He's back! / The bad Reploid!
	.if ENGLISH
	.string "{WINDOW 0x66}"
		.string "He's back!\n"
		.string "The bad Reploid!$"
	.else
	.string "{WINDOW 0x66}"
		.string "またきたー！\n"
		.string "わるいレプリロイドー！$"
	.endif

Text_SubArcadia_HeSBack_2: @ 0x0838225D
	@ EN: He's back! / The fake Reploid!
	.if ENGLISH
	.string "{WINDOW 0x69}"
		.string "He's back!\n"
		.string "The fake Reploid!$"
	.else
	.string "{WINDOW 0x69}"
		.string "またきたー！\n"
		.string "ニセモノレプリロイドー！$"
	.endif

Text_SubArcadia_ILlRipYouTo: @ 0x08382273
	@ EN: I'll rip you to / pieces!
	.if ENGLISH
	.string "{WINDOW 0x66}"
		.string "I'll rip you to\n"
		.string "pieces!$"
	.else
	.string "{WINDOW 0x66}"
		.string "おまえなんか\n"
		.string "バラバラにしてやるー！$"
	.endif

Text_SubArcadia_ILlTearYouTo: @ 0x08382288
	@ EN: I'll tear you to / shreds!
	.if ENGLISH
	.string "{WINDOW 0x69}"
		.string "I'll tear you to\n"
		.string "shreds!$"
	.else
	.string "{WINDOW 0x69}"
		.string "おまえなんか\n"
		.string "ズタズタにしてやるー！$"
	.endif

Text_SubArcadia_Ahahahahahahaa: @ 0x0838229D
	@ EN: Ahahahahahahaa! / He's all ripped to / pieces! / Teheheheeehee! / He's all torn to / shreds!
	.if ENGLISH
	.string "{WINDOW 0x66}"
		.string "Ahahahahahahaa!\n"
		.string "He's all ripped to\n"
		.string "pieces!▼"
	.string "{WINDOW 0x69}"
		.string "Teheheheeehee!\n"
		.string "He's all torn to\n"
		.string "shreds!$"
	.else
	.string "{WINDOW 0x66}"
		.string "あははははははっ！\n"
		.string "バラバラになったー！▼"
	.string "{WINDOW 0x69}"
		.string "うふふふふふふっ！\n"
		.string "ズタズタになったー！$"
	.endif

Text_SubArcadia_PreaThereS: @ 0x083822CB
	@ EN: Prea, there's / something wrong...
	.if ENGLISH
	.string "{WINDOW 0x66}"
		.string "Prea, there's\n"
		.string "something wrong...$"
	.else
	.string "{WINDOW 0x66}"
		.string "あれ…プリエ…\n"
		.string "なんだかへんだよ…$"
	.endif

Text_SubArcadia_YesCreaThereS: @ 0x083822DF
	@ EN: Yes Crea, there's / something wrong...
	.if ENGLISH
	.string "{WINDOW 0x69}"
		.string "Yes Crea, there's\n"
		.string "something wrong...$"
	.else
	.string "{WINDOW 0x69}"
		.string "うん…クリエ…\n"
		.string "なんだかへんだよ…$"
	.endif

Text_SubArcadia_IFeelLikeIM: @ 0x083822F3
	@ EN: I feel like I'm / being stabbed with / pins and needles...
	.if ENGLISH
	.string "{WINDOW 0x66}"
		.string "I feel like I'm\n"
		.string "being stabbed with\n"
		.string "pins and needles...$"
	.else
	.string "{WINDOW 0x66}"
		.string "からだが…いっぱ…い\n"
		.string "チクチク…す…るよ…$"
	.endif

Text_SubArcadia_IFeelLikeIM_2: @ 0x0838230B
	@ EN: I feel like I'm / being smashed with / clubs and hammers... / Mi...meeeeeee!
	.if ENGLISH
	.string "{WINDOW 0x69}"
		.string "I feel like I'm\n"
		.string "being smashed with\n"
		.string "clubs and hammers...▼"
		.string "Mi...meeeeeee!$"
	.else
	.string "{WINDOW 0x69}"
		.string "か…らだが…いっぱ…い\n"
		.string "ズキ…ズキ…す…る…▼"
		.string "ミ…ミーーーーーーーッ！$"
	.endif

Text_SubArcadia_CielZeroAreYouAllright: @ 0x08382331
	@ EN: Ciel: Zero, are you all / right? I just received / some new information / from X. Come back to the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Zero, are you all▼"
		.string "right? I just received▼"
		.string "some new information▼"
		.string "from X. Come back to the▼"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ、だいじょうぶ？▼"
		.string "エックスから、新しいジョウホウをもらったわ▼"
		.string "…いちどレジスタンスベースにもどってきて…$"
	.endif

Text_SubArcadia_Understood: @ 0x0838236F
	@ EN: Understood. / Transfer me.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Understood.\n"
		.string "Transfer me.$"
	.else
	.string "{WINDOW 0x04}"
		.string "わかった…転送しろ$"
	.endif

Text_SubArcadia_INeverThoughtI: @ 0x0838237D
	@ EN: I never thought I / would meet you again / in this world. / If, thanks to Omega / and his ilk, the / portal to Cyberspace / has been opened, / then fate is truly / an ironic thing. / Phantom...one of the / Four Guardians of / Neo Arcadia! / But... / I defeated you... / This is a shadow / world, where both / Reploid souls and / Cyber-elves live. / After you defeated / me, I became a mere / soul, and somehow / drifted back to / Cyberspace. / This space, where / all data flows to / in the end... / And there I learned / all truths. / About Omega... / The Dark Elf... / And you, Zero... / That's right. / Everything. / So...what's your / point? / Exactly this. You / never had what it / takes to be a hero. / I can't stand to / look at you. Now it / is time for your / deletion, by my / hand!
	.if ENGLISH
	.string "{WINDOW 0x33}"
		.string "I never thought I\n"
		.string "would meet you again\n"
		.string "in this world.▼"
		.string "If, thanks to Omega\n"
		.string "and his ilk, the\n"
		.string "portal to Cyberspace▼"
		.string "has been opened,\n"
		.string "then fate is truly\n"
		.string "an ironic thing.▼"
	.string "{WINDOW 0x04}"
		.string "Phantom...one of the\n"
		.string "Four Guardians of\n"
		.string "Neo Arcadia!▼"
		.string "But...\n"
		.string "I defeated you...▼"
	.string "{WINDOW 0x33}"
		.string "This is a shadow\n"
		.string "world, where both\n"
		.string "Reploid souls and▼"
		.string "Cyber-elves live.\n"
		.string "After you defeated\n"
		.string "me, I became a mere▼"
		.string "soul, and somehow\n"
		.string "drifted back to\n"
		.string "Cyberspace.▼"
		.string "This space, where\n"
		.string "all data flows to\n"
		.string "in the end...▼"
		.string "And there I learned\n"
		.string "all truths.▼"
		.string "About Omega...\n"
		.string "The Dark Elf...\n"
		.string "And you, Zero...▼"
		.string "That's right.\n"
		.string "Everything.▼"
	.string "{WINDOW 0x04}"
		.string "So...what's your\n"
		.string "point?▼"
	.string "{WINDOW 0x33}"
		.string "Exactly this. You\n"
		.string "never had what it\n"
		.string "takes to be a hero.▼"
		.string "I can't stand to\n"
		.string "look at you. Now it\n"
		.string "is time for your▼"
		.string "deletion, by my\n"
		.string "hand!$"
	.else
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
	.endif

Text_SubArcadia_AllLegendsAre: @ 0x08382503
	@ EN: All legends are / forgotten in the / end. Goodbye, Zero!
	.if ENGLISH
	.string "{WINDOW 0x32}"
		.string "All legends are\n"
		.string "forgotten in the\n"
		.string "end. Goodbye, Zero!$"
	.else
	.string "{WINDOW 0x32}"
		.string "いかに伝説といえど、\n"
		.string "いつかは わすれさられる…\n"
		.string "さらばだ！ ゼロ！$"
	.endif

Text_SubArcadia_GaspYouTrulyDid: @ 0x0838252A
	@ EN: *gasp* / You truly did... / have the soul of a / hero... / Go... / Cross blades with / Omega, and show what / that body can do! / Will your blade / flinch after you / learn the truth? / Do you have what it / takes...to be a / hero? / You must be the / one to determine / that!
	.if ENGLISH
	.string "{WINDOW 0x32}"
		.string "*gasp*▼"
		.string "You truly did...\n"
		.string "have the soul of a\n"
		.string "hero...▼"
		.string "Go...▼"
		.string "Cross blades with\n"
		.string "Omega, and show what\n"
		.string "that body can do!▼"
		.string "Will your blade\n"
		.string "flinch after you\n"
		.string "learn the truth?▼"
		.string "Do you have what it\n"
		.string "takes...to be a\n"
		.string "hero?▼"
		.string "You must be the\n"
		.string "one to determine\n"
		.string "that!$"
	.else
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
	.endif
