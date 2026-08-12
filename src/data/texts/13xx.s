.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_Others:: @ 0x083836cc
	.2byte (Text_Others_MsCielPlease-Start), (Text_Others_TheSimulationWill-Start), (Text_Others_ILlSaveOurData-Start), (Text_Others_ILlTakeCareOf-Start), (Text_Others_ShouldnTYouBe-Start), (Text_Others_HaveYouTalkedTo-Start), (Text_Others_CerveauSRoomGoThrough-Start), (Text_Others_HeyZeroYouRe-Start)
	.2byte (Text_Others_OhOneMoreThing-Start), (Text_Others_OperatorMrZeroPleaseCome-Start), (Text_Others_HmmZeroTheyRe-Start), (Text_Others_ThisRecoilRod-Start), (Text_Others_TheWorldIsToo-Start), (Text_Others_SorryThisTookSo-Start), (Text_Others_SelectAMission-Start), (Text_Others_WheneverYouRe-Start)
	.2byte (Text_Others_YouHaveCompleted-Start), (Text_Others_WeHaveToDo-Start), (Text_Others_AllRightOhYeah-Start), (Text_Others_WeLlContactYou-Start), (Text_Others_OkayButPlease-Start), (Text_Others_MasterXDoYouStill-Start), (Text_Others_ButHehehe-Start), (Text_Others_IDrWeilShall-Start)
	.2byte (Text_Others_StillToGossip-Start), (Text_Others_MasterXTheDarkElf-Start), (Text_Others_WeLlGoLeviathanAnd-Start), (Text_Others_Hehehehe-Start), (Text_Others_PreparationsHave-Start), (Text_Others_CielEnterTheCoordi-Start), (Text_Others_ThatSDangerous-Start), (Text_Others_OperatorHurryUpAndPrepare-Start)
	.2byte (Text_Others_ZeroIMNotSure-Start), (Text_Others_Empty-Start), (Text_Others_Okay-Start), (Text_Others_ZeroEllipsis-Start), (Text_Others_ZeroIMSoHappy-Start), (Text_Others_CerveauTookHimTo-Start), (Text_Others_ThenAtLeast-Start), (Text_Others_IStillDonTUnder-Start)
	.2byte (Text_Others_OkayIStillDonT-Start), (Text_Others_SomeoneHasBroken-Start), (Text_Others_PutThemThrough-Start), (Text_Others_CanYouHHHear-Start), (Text_Others_SurrenderHandOverTheNew-Start), (Text_Others_ICanTTrustYou-Start), (Text_Others_YouWerePreparedTo-Start), (Text_Others_IsThatYYour-Start)
	.2byte (Text_Others_TheTransmissionWas-Start), (Text_Others_TheNeoArcadian-Start), (Text_Others_ZeroIYouBelievedIn-Start), (Text_Others_MaintenanceRoomInUse-Start), (Text_Others_SoThisIsWhatIt-Start), (Text_Others_LivesWithPlenty-Start), (Text_Others_YesButFirst-Start), (Text_Others_WeVeIsolatedSome-Start)
	.2byte (Text_Others_AndThereWeVeJust-Start), (Text_Others_ThanksToZero-Start), (Text_Others_OhYesThatReminds-Start), (Text_Others_Okay_2-Start), (Text_Others_CanYouStandUp-Start), (Text_Others_WhatAreYouUpTo-Start), (Text_Others_OhYouReAwakeHow-Start), (Text_Others_WaitYourWoundsAreNot-Start)
	.2byte (Text_Others_SoHarpuiaRefuses-Start), (Text_Others_OperatorMrZeroComeTo-Start), (Text_Others_TheySureRunYou-Start), (Text_Others_ZeroHarpuiaDonTYou-Start), (Text_Others_WeAreAnalyzingThe-Start), (Text_Others_InformationAnalysis-Start), (Text_Others_ZeroIMSorryYou-Start), (Text_Others_File945388-Start)
	.2byte (Text_Others_NearTheEndOfThe-Start), (Text_Others_TheTechnologyUsed-Start), (Text_Others_HeheheheExcellentDetective-Start), (Text_Others_WhatUnfortunatelyYouWereA-Start), (Text_Others_IsThatDrWeil-Start), (Text_Others_HeheheThisTimeOmegaIs-Start), (Text_Others_NowYouWillSee-Start), (Text_Others_TasteTheFearFoolishReploids-Start)
	.2byte (Text_Others_InscribeMyName-Start), (Text_Others_ThatNameIs-Start), (Text_Others_HeheheheheeeBwahahahahah-Start), (Text_Others_No-Start), (Text_Others_RrrGrrph-Start), (Text_Others_ThisCanTBe-Start), (Text_Others_ANewWorld-Start), (Text_Others_CielBack-Start)
	.2byte (Text_Others_ZeroInscribeItUponThe-Start), (Text_Others_BothOfYouFreeze-Start), (Text_Others_ArghItSOkayThey-Start), (Text_Others_TookYouLong-Start), (Text_Others_IIVeVerifiedThe-Start), (Text_Others_RogerAll-Start), (Text_Others_PreparationsFor-Start), (Text_Others_Transfer-Start)
	.2byte (Text_Others_CoordinateData-Start), (Text_Others_TheCoordinates-Start), (Text_Others_ZeroBeCarefulIWill-Start), (Text_Others_YouCanGoAtAny-Start)

Text_Others:: @ 0x08383794
Start:

Text_Others_MsCielPlease: @ 0x08383794
	@ EN: Ms. Ciel, please / cheer up. / Everything's turned / out alright before, / hasn't it?! / That's right. / We believe in you, / Ms. Ciel. And in / Mr. Zero, too! / Thank you, everyone.
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Ms. Ciel, please\n"
		.string "cheer up.▼"
		.string "Everything's turned\n"
		.string "out alright before,\n"
		.string "hasn't it?!▼"
	.string "{WINDOW 0x6D}"
		.string "That's right.▼"
		.string "We believe in you,\n"
		.string "Ms. Ciel. And in\n"
		.string "Mr. Zero, too!▼"
	.string "{WINDOW 0x40}"
		.string "Thank you, everyone.$"
	.else
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
	.endif

Text_Others_TheSimulationWill: @ 0x083837FB
	@ EN: The simulation will / take a while longer / to finish... / I think we're going / to need your help / again, Zero... / But you should get a / little rest, first. / For now...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "The simulation will\n"
		.string "take a while longer\n"
		.string "to finish...▼"
		.string "I think we're going\n"
		.string "to need your help\n"
		.string "again, Zero...▼"
		.string "But you should get a\n"
		.string "little rest, first.▼"
		.string "For now...$"
	.else
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
	.endif

Text_Others_ILlSaveOurData: @ 0x08383869
	@ EN: I'll save our data. / YES / NO
		.if ENGLISH
		.string "I'll save our data.\n"
		.string "  YES\n"
		.string "  NO$"
		.else
		.string "今までのことをキロクしておくわね…\n"
		.string "  はい\n"
		.string "  いいえ$"
		.endif

Text_Others_ILlTakeCareOf: @ 0x08383887
	@ EN: I'll take care of / managing the data, / just like always. / If you need any- / thing, let me know. / One more thing... / You should go see / Cerveau. / I hear he's finished / his Secret Disk / analyzer. / If you find any / Secret Disks that / you can't analyze, / ask Cerveau to have / a look for you.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "I'll take care of\n"
		.string "managing the data,\n"
		.string "just like always.▼"
		.string "If you need any-\n"
		.string "thing, let me know.▼"
		.string "One more thing...\n"
		.string "You should go see\n"
		.string "Cerveau.▼"
		.string "I hear he's finished\n"
		.string "his Secret Disk\n"
		.string "analyzer.▼"
		.string "If you find any\n"
		.string "Secret Disks that\n"
		.string "you can't analyze,▼"
		.string "ask Cerveau to have\n"
		.string "a look for you.$"
	.else
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
	.endif

Text_Others_ShouldnTYouBe: @ 0x0838391F
	@ EN: Shouldn't you be / resting? Don't / overdo it. / I'll manage the / data. Tell me if / you need anything. / One more thing... / You should go see / Cerveau. / I hear he's finished / his Secret Disk / analyzer. / If you find any / Secret Disks that / you can't analyze, / ask Cerveau to have / a look for you.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Shouldn't you be\n"
		.string "resting? Don't\n"
		.string "overdo it.▼"
		.string "I'll manage the\n"
		.string "data. Tell me if\n"
		.string "you need anything.▼"
		.string "One more thing...\n"
		.string "You should go see\n"
		.string "Cerveau.▼"
		.string "I hear he's finished\n"
		.string "his Secret Disk\n"
		.string "analyzer.▼"
		.string "If you find any\n"
		.string "Secret Disks that\n"
		.string "you can't analyze,▼"
		.string "ask Cerveau to have\n"
		.string "a look for you.$"
	.else
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
	.endif

Text_Others_HaveYouTalkedTo: @ 0x083839CA
	@ EN: Have you talked to / Cerveau yet? / I hear he can't wait / to try out his / disk analyzer!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Have you talked to\n"
		.string "Cerveau yet?▼"
		.string "I hear he can't wait\n"
		.string "to try out his\n"
		.string "disk analyzer!$"
	.else
	.string "{WINDOW 0x40}"
		.string "セルヴォには、もう会ったの？▼"
		.string "セルヴォったら、\n"
		.string "ディスクのカイセキそうちを\n"
		.string "はやく ためしてみたいそうよ$"
	.endif

Text_Others_CerveauSRoomGoThrough: @ 0x08383A02
	@ EN: Cerveau's room? / Go through the / commander's room to / the right, and it's / the room right in / front of you. / It's convenient / that the base is so / big now, but it sure / is easy to get lost!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Cerveau's room?▼"
		.string "Go through the\n"
		.string "commander's room to\n"
		.string "the right, and it's▼"
		.string "the room right in\n"
		.string "front of you.▼"
		.string "It's convenient\n"
		.string "that the base is so\n"
		.string "big now, but it sure▼"
		.string "is easy to get lost!$"
	.else
	.string "{WINDOW 0x6C}"
		.string "セルヴォのへやですか？▼"
		.string "シレイシツを 右へぬけて、\n"
		.string "手前のへやですよ▼"
		.string "ベースがベンリになるのは\n"
		.string "うれしいですけど…\n"
		.string "こうひろいと まよっちゃいますよね$"
	.endif

Text_Others_HeyZeroYouRe: @ 0x08383A53
	@ EN: Hey, Zero! You're / all right! / I heard the news. / Despite the new / energy, the world is / still not at peace. / I never thought / peace would be easy, / but still... / ... / Anyway, I just / finished a new / weapon for you. / I also fixed your / S.Boomerang! / Here, take it!
	.if ENGLISH
	.string "{WINDOW 0x43}"
		.string "Hey, Zero! You're\n"
		.string "all right!▼"
		.string "I heard the news.▼"
		.string "Despite the new\n"
		.string "energy, the world is\n"
		.string "still not at peace.▼"
		.string "I never thought\n"
		.string "peace would be easy,\n"
		.string "but still...▼"
		.string "...▼"
		.string "Anyway, I just\n"
		.string "finished a new\n"
		.string "weapon for you.▼"
		.string "I also fixed your\n"
		.string "S.Boomerang!▼"
		.string "Here, take it!$"
	.else
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
	.endif

Text_Others_OhOneMoreThing: @ 0x08383B0E
	@ EN: Oh, one more thing. / About Secret Disks. / Secret Disks contain / things that you / can't decode, right? / Well, I can analyze / them for you, so / stop by anytime. / You can also talk to / me if you ever want / to look at the / contents of a disk / we've already / analyzed.
	.if ENGLISH
	.string "{WINDOW 0x43}"
		.string "Oh, one more thing.\n"
		.string "About Secret Disks.▼"
		.string "Secret Disks contain\n"
		.string "things that you\n"
		.string "can't decode, right?▼"
		.string "Well, I can analyze\n"
		.string "them for you, so\n"
		.string "stop by anytime.▼"
		.string "You can also talk to\n"
		.string "me if you ever want\n"
		.string "to look at the▼"
		.string "contents of a disk\n"
		.string "we've already\n"
		.string "analyzed.$"
	.else
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
	.endif

Text_Others_OperatorMrZeroPleaseCome: @ 0x08383BA5
	@ EN: Operator: Mr. Zero... / Please come to the / commander's room, / immediately.
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Operator: Mr. Zero...▼"
		.string "Please come to the▼"
		.string "commander's room,▼"
		.string "immediately.$"
	.else
	.string "{WINDOW 0x00}"
		.string "オペレーター「ゼロさん、ゼロさん…▼"
		.string "シキュウ、シレイシツまでおこしください…$"
	.endif

Text_Others_HmmZeroTheyRe: @ 0x08383BCE
	@ EN: Hmm? Zero, they're / asking for you.
	.if ENGLISH
	.string "{WINDOW 0x43}"
		.string "Hmm? Zero, they're\n"
		.string "asking for you.$"
	.else
	.string "{WINDOW 0x43}"
		.string "ん？ ゼロ…呼んどるようだぞ$"
	.endif

Text_Others_ThisRecoilRod: @ 0x08383BE0
	@ EN: This Recoil Rod / looks easy to use. / Thanks.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "This Recoil Rod\n"
		.string "looks easy to use.\n"
		.string "Thanks.$"
	.else
	.string "{WINDOW 0x04}"
		.string "リコイルロッド……使いやすそうだ\n"
		.string "カンシャする…$"
	.endif

Text_Others_TheWorldIsToo: @ 0x08383BFC
	@ EN: The world is too / much for Ciel to / bear alone... / Take good care of / her, Zero...
	.if ENGLISH
	.string "{WINDOW 0x43}"
		.string "The world is too\n"
		.string "much for Ciel to\n"
		.string "bear alone...▼"
		.string "Take good care of\n"
		.string "her, Zero...$"
	.else
	.string "{WINDOW 0x43}"
		.string "シエルにはまだ……\n"
		.string "世界は、おも過ぎる……▼"
		.string "ささえてやってくれ\n"
		.string "ゼロ……$"
	.endif

Text_Others_SorryThisTookSo: @ 0x08383C26
	@ EN: Sorry this took so / long, Zero. / Are you ready? / We've simulated our / options based on the / information at hand. / I've had the results / prepared in the form / of missions. / The first two are... / Missions to prevent / Neo Arcadia getting / the Dark Elf. / The other two are... / Guerilla attacks / on Neo Arcadia. / to protect everyone / from its threat. / ... / ... / Zero...is fighting / our only option? / I mean, we've / developed this new / energy... / I thought the world / would finally be at / peace... / Do we really have to / keep fighting? / Ciel... / You're already doing / the best you can. / And you're not / alone. / Leave the rest to / us. / Ze...Zero... / Mr. Zero, we're / ready. You can leave / at any time.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Sorry this took so\n"
		.string "long, Zero.\n"
		.string "Are you ready?▼"
		.string "We've simulated our\n"
		.string "options based on the\n"
		.string "information at hand.▼"
		.string "I've had the results\n"
		.string "prepared in the form\n"
		.string "of missions.▼"
		.string "The first two are...▼"
		.string "Missions to prevent\n"
		.string "Neo Arcadia getting\n"
		.string "the Dark Elf.▼"
		.string "The other two are...▼"
		.string "Guerilla attacks\n"
		.string "on Neo Arcadia.▼"
		.string "to protect everyone\n"
		.string "from its threat.▼"
		.string "...▼"
		.string "...▼"
		.string "Zero...is fighting\n"
		.string "our only option?▼"
		.string "I mean, we've\n"
		.string "developed this new\n"
		.string "energy...▼"
		.string "I thought the world\n"
		.string "would finally be at\n"
		.string "peace...▼"
		.string "Do we really have to\n"
		.string "keep fighting?▼"
	.string "{WINDOW 0x05}"
		.string "Ciel...▼"
		.string "You're already doing\n"
		.string "the best you can.▼"
		.string "And you're not\n"
		.string "alone.▼"
		.string "Leave the rest to\n"
		.string "us.▼"
	.string "{WINDOW 0x40}"
		.string "Ze...Zero...▼"
	.string "{WINDOW 0x62}"
		.string "Mr. Zero, we're\n"
		.string "ready. You can leave\n"
		.string "at any time.$"
	.else
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
	.endif

Text_Others_SelectAMission: @ 0x08383DB4
	@ EN: Select a mission? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Select a mission?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "ミッションをセンタクしますか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_Others_WheneverYouRe: @ 0x08383DD1
	@ EN: Whenever you're / ready, just let me / know.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{TOP}Whenever you're\n"
		.string "ready, just let me\n"
		.string "know.$"
	.else
	.string "{WINDOW 0x62}"
		.string "{TOP}では、ジュンビができましたら\n"
		.string "いつでも声をおかけください…$"
	.endif

Text_Others_YouHaveCompleted: @ 0x08383DF3
	@ EN: You have completed / all the missions. / This next mission / involves deciding / what to do with a / missile factory / that's been newly / discovered. / We are currently / also searching for / the Dark Elf, / while we look into / solutions for this / problem.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "You have completed\n"
		.string "all the missions.▼"
		.string "This next mission\n"
		.string "involves deciding\n"
		.string "what to do with a▼"
		.string "missile factory\n"
		.string "that's been newly\n"
		.string "discovered.▼"
		.string "We are currently\n"
		.string "also searching for\n"
		.string "the Dark Elf,▼"
		.string "while we look into\n"
		.string "solutions for this\n"
		.string "problem.$"
	.else
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
	.endif

Text_Others_WeHaveToDo: @ 0x08383E65
	@ EN: We have to do / something about that / missile right now. / We had to calculate / the transfer / coordinates for the / missile factory / based on old satel- / lite photographs... / ...so the coordi- / nates would be too / dangerous to use as / a direct transfer / route. / The land route to / the missile factory / is also dangerous, / due to the scout / patrols that are / searching the area. / We're scanning / for the Dark Elf, / but no luck yet. / Understood. / Let me know if / anything changes.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "We have to do\n"
		.string "something about that\n"
		.string "missile right now.▼"
		.string "We had to calculate\n"
		.string "the transfer\n"
		.string "coordinates for the▼"
		.string "missile factory\n"
		.string "based on old satel-\n"
		.string "lite photographs...▼"
		.string "...so the coordi-\n"
		.string "nates would be too\n"
		.string "dangerous to use as▼"
		.string "a direct transfer\n"
		.string "route.▼"
	.string "{WINDOW 0x62}"
		.string "The land route to\n"
		.string "the missile factory\n"
		.string "is also dangerous,▼"
		.string "due to the scout\n"
		.string "patrols that are\n"
		.string "searching the area.▼"
		.string "We're scanning\n"
		.string "for the Dark Elf,\n"
		.string "but no luck yet.▼"
	.string "{WINDOW 0x04}"
		.string "Understood.▼"
		.string "Let me know if\n"
		.string "anything changes.$"
	.else
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
	.endif

Text_Others_AllRightOhYeah: @ 0x08383F4B
	@ EN: All right. / Oh, yeah...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "All right.▼"
		.string "Oh, yeah...$"
	.else
	.string "{WINDOW 0x40}"
		.string "わかったわ…▼"
		.string "あっ、そうだ…$"
	.endif

Text_Others_WeLlContactYou: @ 0x08383F5C
	@ EN: We'll contact you / right away if we / learn anything new. / Please get some rest / until then.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "We'll contact you\n"
		.string "right away if we\n"
		.string "learn anything new.▼"
		.string "Please get some rest\n"
		.string "until then.$"
	.else
	.string "{WINDOW 0x40}"
		.string "何か わかったら、\n"
		.string "すぐにレンラクするから…\n"
		.string "それまで、ゆっくりやすんで…ね$"
	.endif

Text_Others_OkayButPlease: @ 0x08383F86
	@ EN: Okay...but please / try not to overdo / it. / We'll contact you / soon, so please get / some rest for now.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Okay...but please\n"
		.string "try not to overdo\n"
		.string "it.▼"
		.string "We'll contact you\n"
		.string "soon, so please get\n"
		.string "some rest for now.$"
	.else
	.string "{WINDOW 0x40}"
		.string "そう…でも無理はしないでね▼"
		.string "すぐにレンラクするから…\n"
		.string "それまで、ゆっくりやすんで…ね$"
	.endif

Text_Others_MasterXDoYouStill: @ 0x08383FB5
	@ EN: Master X... / Do you still trust / that man...Weil? / His banishment did / not follow official / ch-channels. / Just because what he / did resulted i-in a / terrible calamity... / Do-does not mean / that banishing him / was justified. / He has returned to / Neo Arcadia in a / legal manner. / What reason-n is / there to drive him / out? / Don't worr-rr-rry. / He learned many / things from his / mistakes of the / past. / He'll do things / right th-this time.
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "Master X...▼"
		.string "Do you still trust\n"
		.string "that man...Weil?▼"
	.string "{WINDOW 0x37}"
		.string "His banishment did\n"
		.string "not follow official\n"
		.string "ch-channels.▼"
		.string "Just because what he\n"
		.string "did resulted i-in a\n"
		.string "terrible calamity...▼"
		.string "Do-does not mean\n"
		.string "that banishing him\n"
		.string "was justified.▼"
		.string "He has returned to\n"
		.string "Neo Arcadia in a\n"
		.string "legal manner.▼"
		.string "What reason-n is\n"
		.string "there to drive him\n"
		.string "out?▼"
		.string "Don't worr-rr-rry.\n"
		.string "He learned many\n"
		.string "things from his▼"
		.string "mistakes of the\n"
		.string "past.▼"
		.string "He'll do things\n"
		.string "right th-this time.$"
	.else
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
	.endif

Text_Others_ButHehehe: @ 0x083840CD
	@ EN: But... / Hehehe... / Thank you, Master X.
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "But...▼"
	.string "{WINDOW 0x3B}"
		.string "Hehehe...\n"
		.string "Thank you, Master X.$"
	.else
	.string "{WINDOW 0x2C}"
		.string "ですが…！▼"
	.string "{WINDOW 0x3B}"
		.string "クックック…\n"
		.string "さすがは、エックスさま$"
	.endif

Text_Others_IDrWeilShall: @ 0x083840EA
	@ EN: I, Dr. Weil, shall / never repeat my / past mistakes. / Never again. Yes. / Hehehe...
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "I, Dr. Weil, shall\n"
		.string "never repeat my\n"
		.string "past mistakes.▼"
		.string "Never again. Yes.\n"
		.string "Hehehe...$"
	.else
	.string "{WINDOW 0x3B}"
		.string "このバイル、\n"
		.string "同じアヤマチは、\n"
		.string "にどとおかしません▼"
		.string "そう…にどと……ね\n"
		.string "クックック…$"
	.endif

Text_Others_StillToGossip: @ 0x08384118
	@ EN: Still, to gossip / about me behind my / back... / My, how the almighty / Four Guardians have / fallen! / What?! Weil!
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}Still, to gossip\n"
		.string "about me behind my\n"
		.string "back...▼"
		.string "My, how the almighty\n"
		.string "Four Guardians have\n"
		.string "fallen!▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}What?! Weil!$"
	.else
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}しかし…\n"
		.string "ワシのいないところで\n"
		.string "かげぐちとは…▼"
		.string "かつての四天王も\n"
		.string "おちたものですな▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}なんだと……バイル…！$"
	.endif

Text_Others_MasterXTheDarkElf: @ 0x08384157
	@ EN: Master X. / The Dark Elf has / appeared in Neo / Arcadia. / Area Z-3079... / It's the farthest / area from here. / A human / residential / district.
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "Master X.▼"
		.string "The Dark Elf has\n"
		.string "appeared in Neo\n"
		.string "Arcadia.▼"
		.string "Area Z-3079...\n"
		.string "It's the farthest\n"
		.string "area from here.▼"
		.string "A human\n"
		.string "residential\n"
		.string "district.$"
	.else
	.string "{WINDOW 0x3B}"
		.string "ところでエックスさま▼"
		.string "ダークエルフが\n"
		.string "ネオ・アルカディアに\n"
		.string "現れたもようです▼"
		.string "エリアZ-3079…\n"
		.string "ここから、もっともはなれた\n"
		.string "人間の きょじゅうくなんですが…$"
	.endif

Text_Others_WeLlGoLeviathanAnd: @ 0x083841AD
	@ EN: We'll go. / Leviathan and / Fefnir are still / undergoing / maintenance, but if / we hurry things / along a bit... / Harpuia, how long do / you plan to act like / you're in charge? / Letting th-the / Resistance get away / with countless / uprisings... / Even letting th-the / Dark Elf escape... / I'm tired of useless / p-people like you. / The Four Guardians / are going to be / stepped down. / But...Master X?! / Dr. Weil... / I'm entrusting you / with the leadership / of our ar-armies. / Will you accept?
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "We'll go.▼"
		.string "Leviathan and\n"
		.string "Fefnir are still\n"
		.string "undergoing▼"
		.string "maintenance, but if\n"
		.string "we hurry things\n"
		.string "along a bit...▼"
	.string "{WINDOW 0x37}"
		.string "Harpuia, how long do\n"
		.string "you plan to act like\n"
		.string "you're in charge?▼"
		.string "Letting th-the\n"
		.string "Resistance get away\n"
		.string "with countless▼"
		.string "uprisings...▼"
		.string "Even letting th-the\n"
		.string "Dark Elf escape...▼"
		.string "I'm tired of useless\n"
		.string "p-people like you.▼"
		.string "The Four Guardians\n"
		.string "are going to be\n"
		.string "stepped down.▼"
	.string "{WINDOW 0x2C}"
		.string "But...Master X?!▼"
	.string "{WINDOW 0x37}"
		.string "Dr. Weil...▼"
		.string "I'm entrusting you\n"
		.string "with the leadership\n"
		.string "of our ar-armies.▼"
		.string "Will you accept?$"
	.else
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
	.endif

Text_Others_Hehehehe: @ 0x08384296
	@ EN: Hehehehe... / Yes sir! / I will capture the / Dark Elf, without / fail... / ...Before she falls / into the hands of / the Resistance and / becomes a threat to / this world...
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "Hehehehe...\n"
		.string "Yes sir!▼"
		.string "I will capture the\n"
		.string "Dark Elf, without\n"
		.string "fail...▼"
		.string "...Before she falls\n"
		.string "into the hands of\n"
		.string "the Resistance and▼"
		.string "becomes a threat to\n"
		.string "this world...$"
	.else
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…\n"
		.string "リョウカイいたしました…▼"
		.string "かならずやダークエルフを\n"
		.string "手に入れましょう▼"
		.string "レジスタンスの手にわたり…\n"
		.string "この世界のキョウイとならぬよう…\n"
		.string "クーックックッ$"
	.endif

Text_Others_PreparationsHave: @ 0x083842F2
	@ EN: Preparations have / begun for the launch / of the missile. / We do not know the / target area, but we / are attempting to / hack our way in and / find out. / A tremendous energy / is emanating / from the missile. / It seems that Omega / is on board. / Omega?! / That Omega, on the / missile!? / ...
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Preparations have\n"
		.string "begun for the launch\n"
		.string "of the missile.▼"
		.string "We do not know the\n"
		.string "target area, but we\n"
		.string "are attempting to▼"
		.string "hack our way in and\n"
		.string "find out.▼"
	.string "{WINDOW 0x62}"
		.string "A tremendous energy\n"
		.string "is emanating\n"
		.string "from the missile.▼"
		.string "It seems that Omega\n"
		.string "is on board.▼"
	.string "{WINDOW 0x40}"
		.string "Omega?!▼"
		.string "That Omega, on the\n"
		.string "missile!?▼"
	.string "{WINDOW 0x04}"
		.string "...$"
	.else
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
	.endif

Text_Others_CielEnterTheCoordi: @ 0x0838437D
	@ EN: Ciel... / Enter the coordi- / nates you found.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Ciel...▼"
		.string "Enter the coordi-\n"
		.string "nates you found.$"
	.else
	.string "{WINDOW 0x04}"
		.string "シエル…▼"
		.string "オマエがカイセキした\n"
		.string "ザヒョウを入力させろ$"
	.endif

Text_Others_ThatSDangerous: @ 0x0838439C
	@ EN: That's...dangerous!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "That's...dangerous!$"
	.else
	.string "{WINDOW 0x40}"
		.string "そんな…キケンだわ！$"
	.endif

Text_Others_OperatorHurryUpAndPrepare: @ 0x083843A9
	@ EN: Operator. / Hurry up and prepare / for transfer.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Operator.▼"
		.string "Hurry up and prepare\n"
		.string "for transfer.$"
	.else
	.string "{WINDOW 0x04}"
		.string "オペレーター▼"
		.string "転送ジュンビいそげ$"
	.endif

Text_Others_ZeroIMNotSure: @ 0x083843BE
	@ EN: Zero, I'm not sure / about this! / I believe in you.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero, I'm not sure\n"
		.string "about this!▼"
	.string "{WINDOW 0x04}"
		.string "I believe in you.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ……自信がない！！▼"
	.string "{WINDOW 0x04}"
		.string "オレは、オマエを信じている$"
	.endif

Text_Others_Empty: @ 0x083843DF
	@ EN: ...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "...$"
	.else
	.string "{WINDOW 0x40}"
		.string "………………$"
	.endif

Text_Others_Okay: @ 0x083843E8
	@ EN: Okay... / ... / Enter...the data... / Please, transfer / him! / Understood. / Commencing transfer / preparations.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Okay...\n"
		.string "...\n"
		.string "Enter...the data...▼"
		.string "Please, transfer\n"
		.string "him!▼"
	.string "{WINDOW 0x61}"
		.string "Understood.\n"
		.string "Commencing transfer\n"
		.string "preparations.$"
	.else
	.string "{WINDOW 0x40}"
		.string "わかった……\n"
		.string "………\n"
		.string "データを…入力して………▼"
		.string "転送……おねがい！▼"
	.string "{WINDOW 0x61}"
		.string "リョウカイ\n"
		.string "転送ジュンビかいし…$"
	.endif

Text_Others_ZeroEllipsis: @ 0x08384425
	@ EN: Zero...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ………$"
	.endif

Text_Others_ZeroIMSoHappy: @ 0x0838442D
	@ EN: Zero... / I'm so happy that / you're safe... / Please...never do / anything as crazy as / that again.... / ... / I'll think about it. / By the way... / How is Harpuia?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
		.string "I'm so happy that\n"
		.string "you're safe...▼"
		.string "Please...never do\n"
		.string "anything as crazy as\n"
		.string "that again....▼"
	.string "{WINDOW 0x05}"
		.string "...\n"
		.string "I'll think about it.▼"
		.string "By the way...\n"
		.string "How is Harpuia?$"
	.else
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
	.endif

Text_Others_CerveauTookHimTo: @ 0x08384489
	@ EN: Cerveau took him to / the maintenance / room. / He wasn't hurt very / badly, but... / He'll have to rest / and recuperate for / a while. / ... / Things really have / gotten horrible... / The operators will / collect as much / info as possible. / Analyzing all of the / information will / take a while. / Try to get some rest / until then. / I'm all right.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Cerveau took him to\n"
		.string "the maintenance\n"
		.string "room.▼"
		.string "He wasn't hurt very\n"
		.string "badly, but...▼"
		.string "He'll have to rest\n"
		.string "and recuperate for\n"
		.string "a while.▼"
		.string "...▼"
		.string "Things really have\n"
		.string "gotten horrible...▼"
		.string "The operators will\n"
		.string "collect as much\n"
		.string "info as possible.▼"
		.string "Analyzing all of the\n"
		.string "information will\n"
		.string "take a while.▼"
		.string "Try to get some rest\n"
		.string "until then.▼"
	.string "{WINDOW 0x05}"
		.string "I'm all right.$"
	.else
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
	.endif

Text_Others_ThenAtLeast: @ 0x0838454C
	@ EN: Then, at least...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Then, at least...$"
	.else
	.string "{WINDOW 0x40}"
		.string "じゃあ、せめて……$"
	.endif

Text_Others_IStillDonTUnder: @ 0x08384558
	@ EN: I still don't under- / stand how Neo / Arcadia could fire a / missile into an / area where humans / live... / ...even to obtain / the Dark Elf...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "I still don't under-\n"
		.string "stand how Neo\n"
		.string "Arcadia could fire a▼"
		.string "missile into an\n"
		.string "area where humans\n"
		.string "live...▼"
		.string "...even to obtain\n"
		.string "the Dark Elf...$"
	.else
	.string "{WINDOW 0x40}"
		.string "…それにしても、\n"
		.string "ダークエルフのためとは言え…▼"
		.string "ネオ・アルカディアが\n"
		.string "人間たちのいるエリアに\n"
		.string "ミサイルを おとすなんて…$"
	.endif

Text_Others_OkayIStillDonT: @ 0x0838459A
	@ EN: Okay... / I still don't under- / stand how Neo / Arcadia could fire a / missile into an / area where humans / live... / ...even to obtain / the Dark Elf.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Okay...▼"
		.string "I still don't under-\n"
		.string "stand how Neo\n"
		.string "Arcadia could fire a▼"
		.string "missile into an\n"
		.string "area where humans\n"
		.string "live...▼"
		.string "...even to obtain\n"
		.string "the Dark Elf.$"
	.else
	.string "{WINDOW 0x40}"
		.string "そう…わかったわ……▼"
		.string "…それにしても、\n"
		.string "ダークエルフのためとは言え…▼"
		.string "ネオ・アルカディアが\n"
		.string "人間たちのいるエリアに\n"
		.string "ミサイルを おとすなんて…$"
	.endif

Text_Others_SomeoneHasBroken: @ 0x083845E7
	@ EN: Someone has broken / into our trans- / mission circuit! / It's Neo Arcadia!
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Someone has broken\n"
		.string "into our trans-\n"
		.string "mission circuit!▼"
		.string "It's Neo Arcadia!$"
	.else
	.string "{WINDOW 0x61}"
		.string "ツウシンかいせんに\n"
		.string "キョウセイわりこみ……！▼"
		.string "ネオ・アルカディアからです！$"
	.endif

Text_Others_PutThemThrough: @ 0x0838460F
	@ EN: Put them through!
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Put them through!$"
	.else
	.string "{WINDOW 0x05}"
		.string "つなげろ！$"
	.endif

Text_Others_CanYouHHHear: @ 0x08384617
	@ EN: Can you h-h-hear me? / Members of the / Resistance. / And...Dr. C-Ciel. / Copy X! / We have custody of / the D-Dark Elf. / Let us put a-a / stop to this foolish / conflict. / We ask that you / surrender t-to us.
	.if ENGLISH
	.string "{WINDOW 0x36}"
		.string "{BOTTOM}Can you h-h-hear me?\n"
		.string "Members of the\n"
		.string "Resistance.▼"
		.string "And...Dr. C-Ciel.▼"
	.string "{WINDOW 0x41}"
		.string "Copy X!▼"
	.string "{WINDOW 0x36}"
		.string "We have custody of\n"
		.string "the D-Dark Elf.▼"
		.string "Let us put a-a\n"
		.string "stop to this foolish\n"
		.string "conflict.▼"
		.string "We ask that you\n"
		.string "surrender t-to us.$"
	.else
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
	.endif

Text_Others_SurrenderHandOverTheNew: @ 0x0838469E
	@ EN: Surrender? / Hand over the new / energy you invented, / the Ciel System. / If you do this, I / guarantee the safety / of you Mavericks. / He's got to be... / As a result of our / analysis of the / Ciel System / information you so / kindly sent us... / We have determined / that by combining it / with the Dark Elf, / it may be possible / to generate enormous / amounts of energy. / This would solve the / energy crisis in / one fell swoop. / There would no / longer be a reason / for us to fight. / Ciel... / A single answer from / you will bring peace / t-to the world.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Surrender?▼"
	.string "{WINDOW 0x3B}"
		.string "Hand over the new\n"
		.string "energy you invented,\n"
		.string "the Ciel System.▼"
		.string "If you do this, I\n"
		.string "guarantee the safety\n"
		.string "of you Mavericks.▼"
	.string "{WINDOW 0x40}"
		.string "He's got to be...▼"
	.string "{WINDOW 0x3B}"
		.string "As a result of our\n"
		.string "analysis of the\n"
		.string "Ciel System▼"
		.string "information you so\n"
		.string "kindly sent us...▼"
		.string "We have determined\n"
		.string "that by combining it\n"
		.string "with the Dark Elf,▼"
		.string "it may be possible\n"
		.string "to generate enormous\n"
		.string "amounts of energy.▼"
		.string "This would solve the\n"
		.string "energy crisis in\n"
		.string "one fell swoop.▼"
		.string "There would no\n"
		.string "longer be a reason\n"
		.string "for us to fight.▼"
	.string "{WINDOW 0x37}"
		.string "Ciel...▼"
		.string "A single answer from\n"
		.string "you will bring peace\n"
		.string "t-to the world.$"
	.else
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
	.endif

Text_Others_ICanTTrustYou: @ 0x083847BB
	@ EN: ... / I can't... / trust...you. / What's th-that?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "...▼"
		.string "I can't...▼"
		.string "trust...you.▼"
	.string "{WINDOW 0x37}"
		.string "What's th-that?$"
	.else
	.string "{WINDOW 0x40}"
		.string "……………▼"
		.string "あなたたちは……▼"
		.string "信用……できません………▼"
	.string "{WINDOW 0x37}"
		.string "…なんだっテ？$"
	.endif

Text_Others_YouWerePreparedTo: @ 0x083847E5
	@ EN: You were prepared to / sacrifice humans to / obtain the Dark Elf! / I cannot trust you / after seeing that. / You cannot have the / Ciel System. / It was built so that / humans and Reploids / could live in peace!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "You were prepared to\n"
		.string "sacrifice humans to\n"
		.string "obtain the Dark Elf!▼"
		.string "I cannot trust you\n"
		.string "after seeing that.▼"
		.string "You cannot have the\n"
		.string "Ciel System.▼"
		.string "It was built so that\n"
		.string "humans and Reploids\n"
		.string "could live in peace!$"
	.else
	.string "{WINDOW 0x40}"
		.string "ダークエルフを手に入れるために\n"
		.string "人間をぎせいにするような……▼"
		.string "そんな…あなたたちは……\n"
		.string "信用できません！▼"
		.string "システマ・シエルは、わたさない▼"
		.string "これは、人とレプリロイドが\n"
		.string "平和にくらすためのものだから！$"
	.endif

Text_Others_IsThatYYour: @ 0x08384853
	@ EN: Is that...y-your / answer? / Fine. / You have a-a / monopoly on energy / resources... / And Zero, a Reploid / with terrifying / f-fighting skills... / Y-you are nothing / more than filthy / extremists! / Ciel... / I was holding-ng / back until now, / because you were / there, a human... / Now, you can face / the consequences, / along with your / Maverick friends!
	.if ENGLISH
	.string "{WINDOW 0x37}"
		.string "{BOTTOM}Is that...y-your\n"
		.string "answer?▼"
		.string "Fine.▼"
		.string "You have a-a\n"
		.string "monopoly on energy\n"
		.string "resources...▼"
		.string "And Zero, a Reploid\n"
		.string "with terrifying\n"
		.string "f-fighting skills...▼"
		.string "Y-you are nothing\n"
		.string "more than filthy\n"
		.string "extremists!▼"
		.string "Ciel...\n"
		.string "I was holding-ng\n"
		.string "back until now,▼"
		.string "because you were\n"
		.string "there, a human...▼"
		.string "Now, you can face\n"
		.string "the consequences,\n"
		.string "along with your▼"
		.string "Maverick friends!$"
	.else
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
	.endif

Text_Others_TheTransmissionWas: @ 0x083848FA
	@ EN: The transmission was / cut off.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "The transmission was\n"
		.string "cut off.$"
	.else
	.string "{WINDOW 0x61}"
		.string "ツウシンとだえました$"
	.endif

Text_Others_TheNeoArcadian: @ 0x08384907
	@ EN: The Neo Arcadian / military has begun / advancing on our / base from multiple / areas. / They've launched a / total offensive.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "The Neo Arcadian\n"
		.string "military has begun\n"
		.string "advancing on our▼"
		.string "base from multiple\n"
		.string "areas.▼"
		.string "They've launched a\n"
		.string "total offensive.$"
	.else
	.string "{WINDOW 0x62}"
		.string "ネオ・アルカディア軍が\n"
		.string "かくエリアから べースへ向けて\n"
		.string "シンコウを カイシしました▼"
		.string "ソウコウゲキを\n"
		.string "しかけてくるもようです$"
	.endif

Text_Others_ZeroIYouBelievedIn: @ 0x08384949
	@ EN: Zero...I... / You believed in / yourself, and fought / accordingly. / What comes next... / is my job. / Tell me which areas / they are in. / I will intercept. / Zero... / Displaying the Neo / Arcadian movements / on the monitor...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...I...▼"
	.string "{WINDOW 0x05}"
		.string "You believed in\n"
		.string "yourself, and fought\n"
		.string "accordingly.▼"
		.string "What comes next...\n"
		.string "is my job.▼"
		.string "Tell me which areas\n"
		.string "they are in.\n"
		.string "I will intercept.▼"
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
	.string "{WINDOW 0x61}"
		.string "Displaying the Neo\n"
		.string "Arcadian movements\n"
		.string "on the monitor...$"
	.else
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
	.endif

Text_Others_MaintenanceRoomInUse: @ 0x083849BE
	@ EN: Maintenance room in use...
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Maintenance room in use...$"
	.else
	.string "{WINDOW 0x00}"
		.string "メンテナンス・ルーム 使用中…$"
	.endif

Text_Others_SoThisIsWhatIt: @ 0x083849D3
	@ EN: So this is what it / has come to... / Dr. Weil as the / ruler of Neo / Arcadia... / Those humans haven't / been told a thing... / No, that's not it. / They haven't tried / to learn a thing...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "So this is what it\n"
		.string "has come to...▼"
		.string "Dr. Weil as the\n"
		.string "ruler of Neo\n"
		.string "Arcadia...▼"
	.string "{WINDOW 0x05}"
		.string "Those humans haven't\n"
		.string "been told a thing...▼"
		.string "No, that's not it.\n"
		.string "They haven't tried\n"
		.string "to learn a thing...$"
	.else
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
	.endif

Text_Others_LivesWithPlenty: @ 0x08384A35
	@ EN: Lives with plenty / of food and / comfort... / People have stopped / bothering to think / with their heads... / There may still be / some people who want / to do something. / If we could somehow / let those kinds of / people know what / Dr. Weil is really / thinking... / We might be able to / change Neo Arcadia. / Who is this / Dr. Weil, anyway? / What has he been / doing since he / reappeared? / If you can gather / some information... / We might be able to / analyze it to / determine where he / is presently, and / what he's been doing / until now. / Okay. / Where do I need to / Go. Just tell me...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Lives with plenty\n"
		.string "of food and\n"
		.string "comfort...▼"
		.string "People have stopped\n"
		.string "bothering to think\n"
		.string "with their heads...▼"
		.string "There may still be\n"
		.string "some people who want\n"
		.string "to do something.▼"
		.string "If we could somehow\n"
		.string "let those kinds of\n"
		.string "people know what▼"
		.string "Dr. Weil is really\n"
		.string "thinking...▼"
		.string "We might be able to\n"
		.string "change Neo Arcadia.▼"
	.string "{WINDOW 0x61}"
		.string "Who is this\n"
		.string "Dr. Weil, anyway?▼"
		.string "What has he been\n"
		.string "doing since he\n"
		.string "reappeared?▼"
	.string "{WINDOW 0x62}"
		.string "If you can gather\n"
		.string "some information...▼"
		.string "We might be able to\n"
		.string "analyze it to\n"
		.string "determine where he▼"
		.string "is presently, and\n"
		.string "what he's been doing\n"
		.string "until now.▼"
	.string "{WINDOW 0x05}"
		.string "Okay.▼"
		.string "Where do I need to\n"
		.string "Go. Just tell me...$"
	.else
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
	.endif

Text_Others_YesButFirst: @ 0x08384B81
	@ EN: Yes, but first...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Yes, but first...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ええ、でも その前に…$"
	.endif

Text_Others_WeVeIsolatedSome: @ 0x08384B90
	@ EN: We've isolated some / locations for you to / gather information.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "We've isolated some\n"
		.string "locations for you to\n"
		.string "gather information.$"
	.else
	.string "{WINDOW 0x61}"
		.string "ジョウホウが\n"
		.string "入手できそうなバショを\n"
		.string "ピックアップしてみました$"
	.endif

Text_Others_AndThereWeVeJust: @ 0x08384BB4
	@ EN: And...there. / We've just finished / inputting the data / recovered so far. / Now, to begin the / analysis.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "And...there.▼"
		.string "We've just finished\n"
		.string "inputting the data\n"
		.string "recovered so far.▼"
	.string "{WINDOW 0x62}"
		.string "Now, to begin the\n"
		.string "analysis.$"
	.else
	.string "{WINDOW 0x61}"
		.string "ゼロさんが今までカイシュウされた\n"
		.string "データの入力……▼"
		.string "今、終わりました▼"
	.string "{WINDOW 0x62}"
		.string "カイセキにうつります$"
	.endif

Text_Others_ThanksToZero: @ 0x08384BEB
	@ EN: Thanks to Zero, / we've collected / much information. / It will take time to / analyze the data, so / for now...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thanks to Zero,\n"
		.string "we've collected\n"
		.string "much information.▼"
		.string "It will take time to\n"
		.string "analyze the data, so\n"
		.string "for now...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロのおかげで、\n"
		.string "いろいろなジョウホウが\n"
		.string "集まったわ……▼"
		.string "カイセキが終わるまで\n"
		.string "少し時間がかかりそうだから\n"
		.string "今のうちに……$"
	.endif

Text_Others_OhYesThatReminds: @ 0x08384C31
	@ EN: Oh yes, that reminds / me. / Cerveau told me that / Harpuia's condition / has improved a lot. / Why don't you go / pay your respects?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Oh yes, that reminds\n"
		.string "me.▼"
		.string "Cerveau told me that\n"
		.string "Harpuia's condition\n"
		.string "has improved a lot.▼"
		.string "Why don't you go\n"
		.string "pay your respects?$"
	.else
	.string "{WINDOW 0x40}"
		.string "あっ、そうだ\n"
		.string "そういえばセルヴォが……▼"
		.string "ハルピュイアのカラダ……\n"
		.string "だいぶん よくなったって\n"
		.string "言ってたわ…▼"
		.string "おみまいに……\n"
		.string "行ってあげたら…どうかしら？$"
	.endif

Text_Others_Okay_2: @ 0x08384C81
	@ EN: Okay... / But please, don't / overdo it. / Oh yes, that reminds / me. / Cerveau told me that / Harpuia's condition / has improved a lot. / Why don't you go / pay your respects?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Okay...\n"
		.string "But please, don't\n"
		.string "overdo it.▼"
		.string "Oh yes, that reminds\n"
		.string "me.▼"
		.string "Cerveau told me that\n"
		.string "Harpuia's condition\n"
		.string "has improved a lot.▼"
		.string "Why don't you go\n"
		.string "pay your respects?$"
	.else
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
	.endif

Text_Others_CanYouStandUp: @ 0x08384CE9
	@ EN: Can you stand up / already? / Wow, Harpuia, you're / hard to keep down...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Can you stand up\n"
		.string "already?▼"
		.string "Wow, Harpuia, you're\n"
		.string "hard to keep down...$"
	.else
	.string "{WINDOW 0x04}"
		.string "もう…たてるのか▼"
		.string "さすがだな\n"
		.string "ハルピュイア……$"
	.endif

Text_Others_WhatAreYouUpTo: @ 0x08384D03
	@ EN: What are you up to? / Why did you rescue / me? / Do you expect some / favor in return? / Perhaps.
	.if ENGLISH
	.string "{WINDOW 0x2D}"
		.string "What are you up to?\n"
		.string "Why did you rescue\n"
		.string "me?▼"
		.string "Do you expect some\n"
		.string "favor in return?▼"
	.string "{WINDOW 0x04}"
		.string "Perhaps.$"
	.else
	.string "{WINDOW 0x2D}"
		.string "どういうつもりだ？\n"
		.string "なぜ助けた？▼"
		.string "かりはかえすとでも言いたいのか！？▼"
	.string "{WINDOW 0x04}"
		.string "さあな$"
	.endif

Text_Others_OhYouReAwakeHow: @ 0x08384D30
	@ EN: Oh, you're awake. / How do you feel? / Horrible. / Just the thought of / being helped by you / makes me nauseous. / Stripped of my / position, and driven / out of Neo Arcadia. / I'm used goods... / That's not true. / You just stood up / for your beliefs, / just like we do. / You've made no / mistakes. / My beliefs... / I can't sit back / any longer... / We must protect the / humans from Weil. / We have to stop him / immediately. That... / that...Weil!!!
	.if ENGLISH
	.string "{WINDOW 0x42}"
		.string "Oh, you're awake.▼"
		.string "How do you feel?▼"
	.string "{WINDOW 0x2D}"
		.string "Horrible.▼"
		.string "Just the thought of\n"
		.string "being helped by you\n"
		.string "makes me nauseous.▼"
		.string "Stripped of my\n"
		.string "position, and driven\n"
		.string "out of Neo Arcadia.▼"
		.string "I'm used goods...▼"
	.string "{WINDOW 0x42}"
		.string "That's not true.▼"
		.string "You just stood up\n"
		.string "for your beliefs,\n"
		.string "just like we do.▼"
		.string "You've made no\n"
		.string "mistakes.▼"
	.string "{WINDOW 0x2D}"
		.string "My beliefs...▼"
		.string "I can't sit back\n"
		.string "any longer...▼"
		.string "We must protect the\n"
		.string "humans from Weil.▼"
		.string "We have to stop him\n"
		.string "immediately. That...\n"
		.string "that...Weil!!!$"
	.else
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
	.endif

Text_Others_WaitYourWoundsAreNot: @ 0x08384E33
	@ EN: Wait! / Your wounds are not / fully healed yet! / I am a warrior, born / to protect humans. / I am a proud warrior / of Neo Arcadia! I / don't need any help! / Even if my body / should fall into / ruin... / I will still gladly / fight for humanity!
	.if ENGLISH
	.string "{WINDOW 0x42}"
		.string "Wait!▼"
		.string "Your wounds are not\n"
		.string "fully healed yet!▼"
	.string "{WINDOW 0x2D}"
		.string "I am a warrior, born\n"
		.string "to protect humans.▼"
		.string "I am a proud warrior\n"
		.string "of Neo Arcadia! I\n"
		.string "don't need any help!▼"
		.string "Even if my body\n"
		.string "should fall into\n"
		.string "ruin...▼"
		.string "I will still gladly\n"
		.string "fight for humanity!$"
	.else
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
	.endif

Text_Others_SoHarpuiaRefuses: @ 0x08384EC7
	@ EN: So... / Harpuia refuses / to go with us. / ...
	.if ENGLISH
	.string "{WINDOW 0x42}"
		.string "So...▼"
		.string "Harpuia refuses\n"
		.string "to go with us.▼"
	.string "{WINDOW 0x04}"
		.string "...$"
	.else
	.string "{WINDOW 0x42}"
		.string "やはり…われわれとは▼"
		.string "いっしょに\n"
		.string "行けないというのか…▼"
	.string "{WINDOW 0x04}"
		.string "………$"
	.endif

Text_Others_OperatorMrZeroComeTo: @ 0x08384EEC
	@ EN: Operator: Mr. Zero... / Come to the commander's / room immediately.
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Operator: Mr. Zero...▼"
		.string "Come to the commander's▼"
		.string "room immediately.$"
	.else
	.string "{WINDOW 0x00}"
		.string "オペレーター「ゼロさん、ゼロさん…▼"
		.string "シキュウ、シレイシツまでおこしください…$"
	.endif

Text_Others_TheySureRunYou: @ 0x08384F15
	@ EN: They sure run you / ragged, don't they, / Zero. / I'll be back later.
	.if ENGLISH
	.string "{WINDOW 0x42}"
		.string "They sure run you\n"
		.string "ragged, don't they,\n"
		.string "Zero.▼"
	.string "{WINDOW 0x04}"
		.string "I'll be back later.$"
	.else
	.string "{WINDOW 0x42}"
		.string "いきつくひまもないな…\n"
		.string "ゼロ……▼"
	.string "{WINDOW 0x04}"
		.string "…行ってくる$"
	.endif

Text_Others_ZeroHarpuiaDonTYou: @ 0x08384F32
	@ EN: Zero... / Harpuia... / Don't you dare / die...
	.if ENGLISH
	.string "{WINDOW 0x42}"
		.string "Zero...▼"
		.string "Harpuia...▼"
		.string "Don't you dare\n"
		.string "die...$"
	.else
	.string "{WINDOW 0x42}"
		.string "ゼロ……▼"
		.string "ハルピュイア……▼"
		.string "みんな…死ぬんじゃないぞ……$"
	.endif

Text_Others_WeAreAnalyzingThe: @ 0x08384F52
	@ EN: We are analyzing the / data. Please wait a / little longer.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "We are analyzing the\n"
		.string "data. Please wait a\n"
		.string "little longer.$"
	.else
	.string "{WINDOW 0x61}"
		.string "データのカイセキ中です\n"
		.string "しばらく おまちください$"
	.endif

Text_Others_InformationAnalysis: @ 0x08384F6E
	@ EN: Information analysis / is complete. / Ms. Ciel will report / on what we've found.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Information analysis\n"
		.string "is complete.▼"
		.string "Ms. Ciel will report\n"
		.string "on what we've found.$"
	.else
	.string "{WINDOW 0x61}"
		.string "ジョウホウのカイセキ…\n"
		.string "カンリョウしました▼"
		.string "シエルさんから\n"
		.string "ホウコクしていただきます……$"
	.endif

Text_Others_ZeroIMSorryYou: @ 0x08384F9D
	@ EN: Zero... I'm sorry. / You gathered a lot / of information for / us, but... / We still do not know / where Weil is. / But we have figured / out what he might / be attempting to do. / Before we talk about / Weil... / I'll open the data / file for the Elf / Wars that you found.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... I'm sorry.▼"
		.string "You gathered a lot\n"
		.string "of information for\n"
		.string "us, but...▼"
		.string "We still do not know\n"
		.string "where Weil is.▼"
		.string "But we have figured\n"
		.string "out what he might\n"
		.string "be attempting to do.▼"
		.string "Before we talk about\n"
		.string "Weil...▼"
		.string "I'll open the data\n"
		.string "file for the Elf\n"
		.string "Wars that you found.$"
	.else
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
	.endif

Text_Others_File945388: @ 0x08385043
	@ EN: File ↾945388 / == Elf Wars ==
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}File #945388\n"
		.string "== Elf Wars ==$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ファイルナンバー945388\n"
		.string "--ヨウセイ戦争--$"
	.endif

Text_Others_NearTheEndOfThe: @ 0x08385062
	@ EN: Near the end of the / Maverick Wars, many / Cyber-elves were used... / The period from this time / until the end of the / fighting was referred to as / the Elf Wars, as a result. / In particular, the use of / the gigantic elf known as / the "Dark Elf," / and copies of this / elf, known as "Baby / Elves," / to amplify the power / of Reploids... / while controlling / said Reploids at / will... / made this the worst / war in recorded / history... / While use of the Dark / Elf brought the war to / an end in four years... / Approximately 90% of / all Reploids, / and 60% of all humans, / were wiped out.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Near the end of the\n"
		.string "Maverick Wars, many\n"
		.string "Cyber-elves were used...▼"
		.string "The period from this time\n"
		.string "until the end of the\n"
		.string "fighting was referred to as▼"
		.string "the Elf Wars, as a result.▼"
		.string "In particular, the use of\n"
		.string "the gigantic elf known as\n"
		.string "the {0xE9}Dark Elf,{0xE9}▼"
		.string "and copies of this\n"
		.string "elf, known as {0xE9}Baby\n"
		.string "Elves,{0xE9}▼"
		.string "to amplify the power\n"
		.string "of Reploids...▼"
		.string "while controlling\n"
		.string "said Reploids at\n"
		.string "will...▼"
		.string "made this the worst\n"
		.string "war in recorded\n"
		.string "history...▼"
		.string "While use of the Dark\n"
		.string "Elf brought the war to\n"
		.string "an end in four years...▼"
		.string "Approximately 90% of\n"
		.string "all Reploids,▼"
		.string "and 60% of all humans,\n"
		.string "were wiped out.$"
	.else
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
	.endif

Text_Others_TheTechnologyUsed: @ 0x08385187
	@ EN: The technology used / at this time... / ...the technology of / using Baby Elves to / control Reploids. / This must be what / Weil is attempting / to use again. / I'm sure that what / Zero saw at the Dark / Elf copy factory, / was machinery / prepared for just / this purpose.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "The technology used\n"
		.string "at this time...▼"
		.string "...the technology of\n"
		.string "using Baby Elves to\n"
		.string "control Reploids.▼"
		.string "This must be what\n"
		.string "Weil is attempting\n"
		.string "to use again.▼"
		.string "I'm sure that what\n"
		.string "Zero saw at the Dark\n"
		.string "Elf copy factory,▼"
		.string "was machinery\n"
		.string "prepared for just\n"
		.string "this purpose.$"
	.else
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
	.endif

Text_Others_HeheheheExcellentDetective: @ 0x0838521D
	@ EN: ... / Hehehehe... / Excellent detective / work, Dr. Ciel.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "...▼"
		.string "Hehehehe...▼"
		.string "Excellent detective\n"
		.string "work, Dr. Ciel.$"
	.else
	.string "{WINDOW 0x62}"
		.string "………▼"
		.string "クックックック……▼"
		.string "よくしらべたな\n"
		.string "ドクター・シエル……$"
	.endif

Text_Others_WhatUnfortunatelyYouWereA: @ 0x08385240
	@ EN: What? / Unfortunately... / ...you were a little / too late.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "What?▼"
	.string "{WINDOW 0x61}"
		.string "Unfortunately...▼"
		.string "...you were a little\n"
		.string "too late.$"
	.else
	.string "{WINDOW 0x40}"
		.string "な？▼"
	.string "{WINDOW 0x61}"
		.string "だが少し………▼"
		.string "おそすぎたんじゃないかね$"
	.endif

Text_Others_IsThatDrWeil: @ 0x0838525D
	@ EN: Is that Dr. Weil?!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Is that Dr. Weil?!$"
	.else
	.string "{WINDOW 0x04}"
		.string "ドクター・バイルか！？$"
	.endif

Text_Others_HeheheThisTimeOmegaIs: @ 0x0838526B
	@ EN: Hehehe... / This time, Omega is / absolutely perfect. / I can now manipulate / all the Reploids on / the planet, / without using the / Baby Elves, / and make them do / whatever I want! / Hehehehe... / Time to start, / Omega.
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}Hehehe...▼"
		.string "This time, Omega is\n"
		.string "absolutely perfect.▼"
		.string "I can now manipulate\n"
		.string "all the Reploids on\n"
		.string "the planet,▼"
		.string "without using the\n"
		.string "Baby Elves,▼"
		.string "and make them do\n"
		.string "whatever I want!▼"
		.string "Hehehehe...\n"
		.string "Time to start,\n"
		.string "Omega.$"
	.else
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
	.endif

Text_Others_NowYouWillSee: @ 0x083852EC
	@ EN: Now you will see, / pitiful humans, / what you get for / banishing Dr. Weil!
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}Now you will see,\n"
		.string "pitiful humans,▼"
		.string "what you get for\n"
		.string "banishing Dr. Weil!$"
	.else
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}今こそ思い知れ…▼"
		.string "ワシをツイホウした\n"
		.string "人間どもよ！$"
	.endif

Text_Others_TasteTheFearFoolishReploids: @ 0x0838530E
	@ EN: Taste the fear... / Foolish Reploids, / who banished me!
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}Taste the fear...▼"
		.string "Foolish Reploids,\n"
		.string "who banished me!$"
	.else
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}キョウフしろ…▼"
		.string "ワシをツイホウした\n"
		.string "レプリロイドどもよ！$"
	.endif

Text_Others_InscribeMyName: @ 0x0838532E
	@ EN: Inscribe my name, / upon this world... / The name of your / new ruler!
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}Inscribe my name,\n"
		.string "upon this world...▼"
		.string "The name of your\n"
		.string "new ruler!$"
	.else
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}きざみこむのだ\n"
		.string "この世界に…▼"
		.string "シハイシャたるワシの名を！$"
	.endif

Text_Others_ThatNameIs: @ 0x08385351
	@ EN: That name is / Dr. Weil. / The entire world is / in my hands... / I have the power to / crush it between my / fingers at any time!
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}That name is\n"
		.string "Dr. Weil.▼"
		.string "The entire world is\n"
		.string "in my hands...▼"
		.string "I have the power to\n"
		.string "crush it between my\n"
		.string "fingers at any time!$"
	.else
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}わが名はドクター・バイル▼"
		.string "世界は、わが手の中にある…\n"
		.string "この手をにぎりしめるだけで……▼"
		.string "この世界を終わらすことが\n"
		.string "できるのだ！！$"
	.endif

Text_Others_HeheheheheeeBwahahahahah: @ 0x0838539D
	@ EN: Heheheheheee... / Bwahahahahah!
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Heheheheheee...▼"
		.string "Bwahahahahah!$"
	.else
	.string "{WINDOW 0x61}"
		.string "クーックックックッ…▼"
		.string "クヒャーッハッハッハッハッ！$"
	.endif

Text_Others_No: @ 0x083853B9
	@ EN: No!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "No!$"
	.else
	.string "{WINDOW 0x40}"
		.string "まっ、まさか！？$"
	.endif

Text_Others_RrrGrrph: @ 0x083853C4
	@ EN: Rrr...grrph...
	.if ENGLISH
	.string "{WINDOW 0x5F}"
		.string "Rrr...grrph...$"
	.else
	.string "{WINDOW 0x5F}"
		.string "う…うう…$"
	.endif

Text_Others_ThisCanTBe: @ 0x083853CC
	@ EN: This can't be / happening!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "This can't be\n"
		.string "happening!$"
	.else
	.string "{WINDOW 0x40}"
		.string "そ、そんな……！$"
	.endif

Text_Others_ANewWorld: @ 0x083853D7
	@ EN: A new world... / A new order... / History is once / again in motion...
	.if ENGLISH
	.string "{WINDOW 0x5E}"
		.string "A new world...\n"
		.string "A new order...▼"
		.string "History is once\n"
		.string "again in motion...$"
	.else
	.string "{WINDOW 0x5E}"
		.string "新たなる世界…\n"
		.string "新たなるチツジョ…▼"
		.string "とじられたレキシが…\n"
		.string "再び 動きはじめる…$"
	.endif

Text_Others_CielBack: @ 0x08385407
	@ EN: Ciel! Back!
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Ciel! Back!$"
	.else
	.string "{WINDOW 0x05}"
		.string "さがれ！ シエル！$"
	.endif

Text_Others_ZeroInscribeItUponThe: @ 0x08385413
	@ EN: Zero?! / Inscribe it upon the / world... The name of / our ruler... / Weil! Weil! Weil! / Weil! Weil! Weil! / Weil! Weil! Weil!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero?!▼"
	.string "{WINDOW 0x5E}"
		.string "Inscribe it upon the\n"
		.string "world... The name of\n"
		.string "our ruler...▼"
		.string "Weil! Weil! Weil!\n"
		.string "Weil! Weil! Weil!\n"
		.string "Weil! Weil! Weil!$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ！？▼"
	.string "{WINDOW 0x5E}"
		.string "世界にきざめ…\n"
		.string "われらのシハイシャの名は…▼"
		.string "バイル！ バイル！ バイル！\n"
		.string "バイル！ バイル！ バイル！\n"
		.string "バイル！ バイル！ バイル！$"
	.endif

Text_Others_BothOfYouFreeze: @ 0x08385462
	@ EN: Both of you, freeze!
	.if ENGLISH
	.string "{WINDOW 0x34}"
		.string "Both of you, freeze!$"
	.else
	.string "{WINDOW 0x34}"
		.string "ふたりとも、動かないで！$"
	.endif

Text_Others_ArghItSOkayThey: @ 0x08385472
	@ EN: Argh! / It's okay. They're / just unconscious. / All I did was / disable the power of / the Dark Elf. / But my current power / can only protect / those at this base.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Argh!▼"
	.string "{WINDOW 0x34}"
		.string "It's okay. They're\n"
		.string "just unconscious.▼"
		.string "All I did was\n"
		.string "disable the power of\n"
		.string "the Dark Elf.▼"
		.string "But my current power\n"
		.string "can only protect\n"
		.string "those at this base.$"
	.else
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
	.endif

Text_Others_TookYouLong: @ 0x083854D1
	@ EN: Took you long / enough, X. / Where's Weil? / In Neo Arcadia's / underground power / system... / "Sub Arcadia"! / Omega is there too, / transmitting the / power of the Dark / Elf around the / world. / Apparently... / X and I are the only / ones who can move / around freely. / X. / Tell us the / coordinates for / Sub Arcadia. / So you plan on / fighting against / Omega? / Yes... / Why? / Nothing,I'm sure / you'll be fine... / Be careful, Zero.
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Took you long\n"
		.string "enough, X.▼"
		.string "Where's Weil?▼"
	.string "{WINDOW 0x34}"
		.string "In Neo Arcadia's\n"
		.string "underground power\n"
		.string "system...▼"
		.string "{0xE9}Sub Arcadia{0xE9}!▼"
		.string "Omega is there too,\n"
		.string "transmitting the\n"
		.string "power of the Dark▼"
		.string "Elf around the\n"
		.string "world.▼"
	.string "{WINDOW 0x05}"
		.string "Apparently...▼"
		.string "X and I are the only\n"
		.string "ones who can move\n"
		.string "around freely.▼"
		.string "X.▼"
		.string "Tell us the\n"
		.string "coordinates for\n"
		.string "Sub Arcadia.▼"
	.string "{WINDOW 0x34}"
		.string "So you plan on\n"
		.string "fighting against\n"
		.string "Omega?▼"
	.string "{WINDOW 0x05}"
		.string "Yes...▼"
		.string "Why?▼"
	.string "{WINDOW 0x34}"
		.string "Nothing,I'm sure\n"
		.string "you'll be fine...▼"
		.string "Be careful, Zero.$"
	.else
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
	.endif

Text_Others_IIVeVerifiedThe: @ 0x083855B0
	@ EN: I... / I've verified the / coordinates for / Sub Arcadia on the / transfer device. / Transfer me.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "I...▼"
		.string "I've verified the\n"
		.string "coordinates for\n"
		.string "Sub Arcadia on the▼"
		.string "transfer device.▼"
	.string "{WINDOW 0x04}"
		.string "Transfer me.$"
	.else
	.string "{WINDOW 0x61}"
		.string "て…▼"
		.string "転送ソウチに…\n"
		.string "アンダー・アルカディアの\n"
		.string "ザヒョウ入力をカクニン…▼"
	.string "{WINDOW 0x04}"
		.string "転送をたのむ$"
	.endif

Text_Others_RogerAll: @ 0x083855E6
	@ EN: Roger. All / personnel, prepare / for transfer.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Roger. All\n"
		.string "personnel, prepare\n"
		.string "for transfer.$"
	.else
	.string "{WINDOW 0x61}"
		.string "リョウカイ…\n"
		.string "カクイン…転送じゅんびにかかれ$"
	.endif

Text_Others_PreparationsFor: @ 0x08385601
	@ EN: Preparations for / transfer complete.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Preparations for\n"
		.string "transfer complete.$"
	.else
	.string "{WINDOW 0x62}"
		.string "転送じゅんびカンリョウ…$"
	.endif

Text_Others_Transfer: @ 0x08385612
	@ EN: Transfer!
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Transfer!$"
	.else
	.string "{WINDOW 0x61}"
		.string "転送…$"
	.endif

Text_Others_CoordinateData: @ 0x0838561A
	@ EN: Coordinate data / obtained from / Original X... / ...has been / input completely.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Coordinate data\n"
		.string "obtained from\n"
		.string "Original X...▼"
		.string "...has been\n"
		.string "input completely.$"
	.else
	.string "{WINDOW 0x61}"
		.string "オリジナルエックスより\n"
		.string "入手しました ざひょうデータ…▼"
		.string "入力…カンリョウしました$"
	.endif

Text_Others_TheCoordinates: @ 0x08385649
	@ EN: The coordinates / lead to an abandoned / research lab. / According to our / records, this is / where Weil used to / carry out his / research. / It's right next to / the place were you / were sleeping, Zero. / Weil and Omega are / there, aren't they.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "The coordinates\n"
		.string "lead to an abandoned\n"
		.string "research lab.▼"
		.string "According to our\n"
		.string "records, this is\n"
		.string "where Weil used to▼"
		.string "carry out his\n"
		.string "research.▼"
		.string "It's right next to\n"
		.string "the place were you\n"
		.string "were sleeping, Zero.▼"
	.string "{WINDOW 0x05}"
		.string "Weil and Omega are\n"
		.string "there, aren't they.$"
	.else
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
	.endif

Text_Others_ZeroBeCarefulIWill: @ 0x083856C3
	@ EN: Zero... / Be careful... / I will. / Operator... / Is everything ready?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
		.string "Be careful...▼"
	.string "{WINDOW 0x05}"
		.string "I will.▼"
		.string "Operator...\n"
		.string "Is everything ready?$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "気をつけてね………▼"
	.string "{WINDOW 0x05}"
		.string "あぁ……▼"
		.string "オペレーター…\n"
		.string "行けるか？$"
	.endif

Text_Others_YouCanGoAtAny: @ 0x083856EB
	@ EN: You can go at any / time, Mr. Zero.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "You can go at any\n"
		.string "time, Mr. Zero.$"
	.else
	.string "{WINDOW 0x61}"
		.string "いつでも行けます$"
	.endif

.balign 4, 0
