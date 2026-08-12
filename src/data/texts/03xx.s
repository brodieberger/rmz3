.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_SpaceCraft:: @ 0x0837f00c
  .2byte (Text_SpaceCraft_ItSureIsQuietThere-Start), (Text_SpaceCraft_TheReadingIs-Start), (Text_SpaceCraft_TheSnowIsLetting-Start), (Text_SpaceCraft_WWowLookAtThat-Start), (Text_SpaceCraft_IsThatSomeKind-Start), (Text_SpaceCraft_MsCielDidThatHuge-Start), (Text_SpaceCraft_NeoArcadiaHasThe-Start), (Text_SpaceCraft_UpAheadThatSWhere-Start)
  .2byte (Text_SpaceCraft_SheKnewWhoI-Start), (Text_SpaceCraft_CielZeroAreYouThere-Start), (Text_SpaceCraft_MaintainRadio-Start), (Text_SpaceCraft_OhIIMSorry-Start), (Text_SpaceCraft_GetDown-Start), (Text_SpaceCraft_NeoArcadiansMsCielLook-Start), (Text_SpaceCraft_NeoArcadiansMsCielLook_Alias1-Start), (Text_SpaceCraft_No-Start)
  .2byte (Text_SpaceCraft_Relax-Start), (Text_SpaceCraft_ScramIDonTHave-Start), (Text_SpaceCraft_Empty-Start), (Text_SpaceCraft_CielZeroCanYouHear-Start), (Text_SpaceCraft_SeemsYouReOkayLeave-Start), (Text_SpaceCraft_CielButZero-Start), (Text_SpaceCraft_IVeHeardThat-Start), (Text_SpaceCraft_IsItCallingMe-Start)
  .2byte (Text_SpaceCraft_Aaaaaargh-Start), (Text_SpaceCraft_NowYouReAskin-Start), (Text_SpaceCraft_ILlBlastYouTo-Start), (Text_SpaceCraft_Ooph-Start), (Text_SpaceCraft_PantPantAreYouAlive-Start), (Text_SpaceCraft_ZeroWhatTheHeckAre-Start), (Text_SpaceCraft_ThatSOmega-Start), (Text_SpaceCraft_BahThat-Start)
  .2byte (Text_SpaceCraft_OmegaHuhSoYouWere-Start), (Text_SpaceCraft_Grrr-Start), (Text_SpaceCraft_YouJustDonTGive-Start), (Text_SpaceCraft_SoYouReOmegaI-Start), (Text_SpaceCraft_Gaaarrrrwl-Start), (Text_SpaceCraft_HeheheheOmegaThatWillBe-Start), (Text_SpaceCraft_FromThisDay-Start), (Text_SpaceCraft_Gaarwl-Start)
  .2byte (Text_SpaceCraft_HeheheheIAmWeilYou-Start), (Text_SpaceCraft_MMasterX-Start), (Text_SpaceCraft_HarpuiaHeheYou-Start), (Text_SpaceCraft_YouMustBe-Start), (Text_SpaceCraft_ButMasterXThink-Start), (Text_SpaceCraft_WeilYouSoZeroYou-Start), (Text_SpaceCraft_HeheheNowThings-Start), (Text_SpaceCraft_WithThatBody-Start)
  .2byte (Text_SpaceCraft_CielZeroThisIsTerrible-Start), (Text_SpaceCraft_SoYouWere-Start), (Text_SpaceCraft_CielHurryBackToBase-Start)

Text_SpaceCraft:: @ 0x0837f072
Start:

Text_SpaceCraft_ItSureIsQuietThere: @ 0x0837F072
	@ EN: It sure is quiet... / There haven't been / many Neo Arcadian / attacks lately. / Things are almost / too peaceful now... / Ms. Ciel completed / her research on the / new energy... / And if it solves / the energy crisis, / Neo Arcadia won't / have a reason to / fight us anymore. / Actually... / I already informed / Neo Arcadia about / this new energy, / the "Ciel System"... / But... / I haven't received / a reply yet... / Don't worry! I'm / sure their answer / will come soon! / There's no more / reason to fight. We / can live in peace! / Right?! / We're in the middle / of a mission. / So put a lid on it / and walk! / *gulp!* Sorry!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "It sure is quiet...▼"
		.string "There haven't been\n"
		.string "many Neo Arcadian\n"
		.string "attacks lately.▼"
		.string "Things are almost\n"
		.string "too peaceful now...▼"
	.string "{WINDOW 0x6D}"
		.string "Ms. Ciel completed\n"
		.string "her research on the\n"
		.string "new energy...▼"
		.string "And if it solves\n"
		.string "the energy crisis,▼"
		.string "Neo Arcadia won't\n"
		.string "have a reason to\n"
		.string "fight us anymore.▼"
	.string "{WINDOW 0x40}"
		.string "Actually...▼"
		.string "I already informed\n"
		.string "Neo Arcadia about▼"
		.string "this new energy,\n"
		.string "the {0xE9}Ciel System{0xE9}...▼"
		.string "But...▼"
		.string "I haven't received\n"
		.string "a reply yet...▼"
	.string "{WINDOW 0x6C}"
		.string "Don't worry! I'm\n"
		.string "sure their answer\n"
		.string "will come soon!▼"
		.string "There's no more\n"
		.string "reason to fight. We\n"
		.string "can live in peace!▼"
		.string "Right?!▼"
	.string "{WINDOW 0x05}"
		.string "We're in the middle\n"
		.string "of a mission.▼"
		.string "So put a lid on it\n"
		.string "and walk!▼"
	.string "{WINDOW 0x40}"
		.string "*gulp!* Sorry!$"
	.else
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
	.endif

Text_SpaceCraft_TheReadingIs: @ 0x0837F1BE
	@ EN: The reading is / getting stronger. / We're close...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "The reading is\n"
		.string "getting stronger.\n"
		.string "We're close...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ハンノウが強くなってきたわ\n"
		.string "このあたりのはずなんだけど…$"
	.endif

Text_SpaceCraft_TheSnowIsLetting: @ 0x0837F1DE
	@ EN: The snow is letting / up...
	.if ENGLISH
	.string "{WINDOW 0x6D}"
		.string "The snow is letting\n"
		.string "up...$"
	.else
	.string "{WINDOW 0x6D}"
		.string "ユキがはれてきたな…$"
	.endif

Text_SpaceCraft_WWowLookAtThat: @ 0x0837F1EB
	@ EN: W-wow! / Look at that!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "W-wow!▼"
		.string "Look at that!$"
	.else
	.string "{WINDOW 0x6C}"
		.string "お、おい…！▼"
		.string "あれを見ろ！！$"
	.endif

Text_SpaceCraft_IsThatSomeKind: @ 0x0837F1FD
	@ EN: Is that...some kind / of ship?
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Is that...some kind\n"
		.string "of ship?$"
	.else
	.string "{WINDOW 0x05}"
		.string "これは…フネ…か？$"
	.endif

Text_SpaceCraft_MsCielDidThatHuge: @ 0x0837F209
	@ EN: Ms. Ciel... / Did that...huge / thing...fall from / outer space?! / Yes...but what's / more... / It's giving out the / same energy reading / as the Dark Elf... / of which there is / only one in the / whole world... / Zero was against the / idea, but I just had / to find out... / What could possibly / be going on here?
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Ms. Ciel...▼"
		.string "Did that...huge\n"
		.string "thing...fall from\n"
		.string "outer space?!▼"
	.string "{WINDOW 0x41}"
		.string "Yes...but what's\n"
		.string "more...▼"
		.string "It's giving out the\n"
		.string "same energy reading\n"
		.string "as the Dark Elf...▼"
		.string "of which there is\n"
		.string "only one in the\n"
		.string "whole world...▼"
		.string "Zero was against the\n"
		.string "idea, but I just had\n"
		.string "to find out...▼"
		.string "What could possibly\n"
		.string "be going on here?$"
	.else
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
	.endif

Text_SpaceCraft_NeoArcadiaHasThe: @ 0x0837F2C0
	@ EN: Neo Arcadia has the / area ahead of us / cordoned off. / What?! / You guys stay here / until I make sure / it's safe. / Okay... / Be careful, Zero...
	.if ENGLISH
	.string "{WINDOW 0x05}"
		.string "Neo Arcadia has the\n"
		.string "area ahead of us\n"
		.string "cordoned off.▼"
	.string "{WINDOW 0x40}"
		.string "What?!▼"
	.string "{WINDOW 0x05}"
		.string "You guys stay here\n"
		.string "until I make sure\n"
		.string "it's safe.▼"
	.string "{WINDOW 0x40}"
		.string "Okay...\n"
		.string "Be careful, Zero...$"
	.else
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
	.endif

Text_SpaceCraft_UpAheadThatSWhere: @ 0x0837F32A
	@ EN: Up ahead... / That's where the / Dark Elf reading is / coming from.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Up ahead...▼"
		.string "That's where the\n"
		.string "Dark Elf reading is\n"
		.string "coming from.$"
	.else
	.string "{WINDOW 0x04}"
		.string "このおく……か、▼"
		.string "ダークエルフのハンノウが\n"
		.string "あったのは……$"
	.endif

Text_SpaceCraft_SheKnewWhoI: @ 0x0837F34A
	@ EN: She knew who I / was... / Why would the elf / who almost destroyed / the world know me?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}She knew who I\n"
		.string "was...▼"
		.string "Why would the elf\n"
		.string "who almost destroyed\n"
		.string "the world know me?$"
	.else
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}アイツは…\n"
		.string "オレのことを 知っていた…▼"
		.string "世界をほろぼしかけたエルフが\n"
		.string "なぜオレのことを…$"
	.endif

Text_SpaceCraft_CielZeroAreYouThere: @ 0x0837F37D
	@ EN: Ciel: Zero? Are you there?
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Zero? Are you there?$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ？ 聞こえる？$"
	.endif

Text_SpaceCraft_MaintainRadio: @ 0x0837F38E
	@ EN: Maintain radio / silence! / The enemy is near...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Maintain radio\n"
		.string "silence!▼"
		.string "The enemy is near...$"
	.else
	.string "{WINDOW 0x04}"
		.string "つうしんヘイサだ！▼"
		.string "テキが近い……$"
	.endif

Text_SpaceCraft_OhIIMSorry: @ 0x0837F3A3
	@ EN: Oh, I-I'm sorry...
	.if ENGLISH
	.string "{WINDOW 0x41}"
		.string "Oh, I-I'm sorry...$"
	.else
	.string "{WINDOW 0x41}"
		.string "えっ、ご、ごめんなさい……$"
	.endif

Text_SpaceCraft_GetDown: @ 0x0837F3B3
	@ EN: Get down!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Get down!$"
	.else
	.string "{WINDOW 0x6C}"
		.string "ふせて！！$"
	.endif

Text_SpaceCraft_NeoArcadiansMsCielLook: @ 0x0837F3BB
Text_SpaceCraft_NeoArcadiansMsCielLook_Alias1: @ 0x0837F3BB
	@ EN: Neo Arcadians! / Ms. Ciel, look out!
	.if ENGLISH
	.string "{WINDOW 0x6C}"
		.string "Neo Arcadians!▼"
	.string "{WINDOW 0x6D}"
		.string "Ms. Ciel, look out!$"
	.else
	.string "{WINDOW 0x6C}"
		.string "ネオ・アルカディアか！▼"
	.string "{WINDOW 0x6D}"
		.string "シエルさん！ さがって！$"
	.endif

Text_SpaceCraft_No: @ 0x0837F3D8
	@ EN: No!
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "No!$"
	.else
	.string "{WINDOW 0x04}"
		.string "ちっ…$"
	.endif

Text_SpaceCraft_Relax: @ 0x0837F3DE
	@ EN: Relax. / They won't come to / any harm. / Harpuia?! / I'm letting you off / the hook this time. / But you and those / Resistance fighters / must leave, now! / You're letting us / off the hook?!
	.if ENGLISH
	.string "{WINDOW 0x2D}"
		.string "Relax.\n"
		.string "They won't come to\n"
		.string "any harm.▼"
	.string "{WINDOW 0x04}"
		.string "Harpuia?!▼"
	.string "{WINDOW 0x2D}"
		.string "I'm letting you off\n"
		.string "the hook this time.▼"
		.string "But you and those\n"
		.string "Resistance fighters\n"
		.string "must leave, now!▼"
	.string "{WINDOW 0x04}"
		.string "You're letting us\n"
		.string "off the hook?!$"
	.else
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
	.endif

Text_SpaceCraft_ScramIDonTHave: @ 0x0837F434
	@ EN: Scram! / I don't have time to / mess with you now!
	.if ENGLISH
	.string "{WINDOW 0x2D}"
		.string "Scram!▼"
		.string "I don't have time to\n"
		.string "mess with you now!$"
	.else
	.string "{WINDOW 0x2D}"
		.string "さっさと消えろ▼"
		.string "今は、オマエたちに\n"
		.string "かまっているバアイじゃないんだ…$"
	.endif

Text_SpaceCraft_Empty: @ 0x0837F45B
	@ EN: ...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "...$"
	.else
	.string "{WINDOW 0x04}"
		.string "………$"
	.endif

Text_SpaceCraft_CielZeroCanYouHear: @ 0x0837F461
	@ EN: Ciel: Zero... / Can you hear me?
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Zero...▼"
		.string "Can you hear me?$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「ゼ…ゼロ▼"
		.string "聞こえる…かしら……？$"
	.endif

Text_SpaceCraft_SeemsYouReOkayLeave: @ 0x0837F479
	@ EN: Seems you're okay... / Leave the rest of / this up to me. / I want you all to / head back to the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Seems you're okay...▼"
		.string "Leave the rest of\n"
		.string "this up to me.▼"
		.string "I want you all to\n"
		.string "head back to the\n"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x04}"
		.string "無事だったようだな…▼"
		.string "ここからさきは…\n"
		.string "オレだけでやらせてもらう▼"
		.string "オマエたちは、\n"
		.string "レジスタンスベースにもどれ$"
	.endif

Text_SpaceCraft_CielButZero: @ 0x0837F4B4
	@ EN: Ciel: But, Zero...
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: But, Zero...$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「で、でも……$"
	.endif

Text_SpaceCraft_IVeHeardThat: @ 0x0837F4C1
	@ EN: I've heard that / voice somewhere / before...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "I've heard that\n"
		.string "voice somewhere\n"
		.string "before...$"
	.else
	.string "{WINDOW 0x04}"
		.string "この声…\n"
		.string "前にも どこかで………$"
	.endif

Text_SpaceCraft_IsItCallingMe: @ 0x0837F4D6
	@ EN: Is it...calling me?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}Is it...calling me?$"
	.else
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}オレを…\n"
		.string "呼んでいるのか…？$"
	.endif

Text_SpaceCraft_Aaaaaargh: @ 0x0837F4E9
	@ EN: Aaaaaargh!
	.if ENGLISH
	.string "{WINDOW 0x2F}"
		.string "Aaaaaargh!$"
	.else
	.string "{WINDOW 0x2F}"
		.string "きゃああああっ…！$"
	.endif

Text_SpaceCraft_NowYouReAskin: @ 0x0837F4F5
	@ EN: Now you're askin' / for it!
	.if ENGLISH
	.string "{WINDOW 0x31}"
		.string "Now you're askin'\n"
		.string "for it!$"
	.else
	.string "{WINDOW 0x31}"
		.string "やりやがったな！$"
	.endif

Text_SpaceCraft_ILlBlastYouTo: @ 0x0837F500
	@ EN: I'll blast you to / pieces!
	.if ENGLISH
	.string "{WINDOW 0x31}"
		.string "I'll blast you to\n"
		.string "pieces!$"
	.else
	.string "{WINDOW 0x31}"
		.string "ふっとびやがれえっ！$"
	.endif

Text_SpaceCraft_Ooph: @ 0x0837F50D
	@ EN: Ooph!
	.if ENGLISH
	.string "{WINDOW 0x31}"
		.string "Ooph!$"
	.else
	.string "{WINDOW 0x31}"
		.string "グオオオオッ！$"
	.endif

Text_SpaceCraft_PantPantAreYouAlive: @ 0x0837F517
	@ EN: *pant pant* / Are you alive, / Fefnir? / What a monster... / The two of us / fighting together, / and not a scratch. / Omega, the evil / Reploid banished / from Neo Arcadia... / He's pretty tough...
	.if ENGLISH
	.string "{WINDOW 0x2F}"
		.string "{BOTTOM}*pant pant*▼"
		.string "Are you alive,\n"
		.string "Fefnir?▼"
	.string "{WINDOW 0x30}"
		.string "{BOTTOM}What a monster...▼"
		.string "The two of us\n"
		.string "fighting together,\n"
		.string "and not a scratch.▼"
	.string "{WINDOW 0x2F}"
		.string "{BOTTOM}Omega, the evil\n"
		.string "Reploid banished\n"
		.string "from Neo Arcadia...▼"
		.string "He's pretty tough...$"
	.else
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
	.endif

Text_SpaceCraft_ZeroWhatTheHeckAre: @ 0x0837F58C
	@ EN: Zero?! / What the heck are / YOU doing here?! / What is that thing?
	.if ENGLISH
	.string "{WINDOW 0x30}"
		.string "Zero?!▼"
		.string "What the heck are\n"
		.string "YOU doing here?!▼"
	.string "{WINDOW 0x05}"
		.string "What is that thing?$"
	.else
	.string "{WINDOW 0x30}"
		.string "…ゼロ！？▼"
		.string "なんでテメーがここに…！？▼"
	.string "{WINDOW 0x05}"
		.string "ヤツは何者だ？$"
	.endif

Text_SpaceCraft_ThatSOmega: @ 0x0837F5AE
	@ EN: That's Omega. / His mere existence / defies reality... / He's strong, but... / He's not as fun to / fight as you are. / Hehe... / I don't feel like / fighting him, so / he's all yours... / See you later, Zero.
	.if ENGLISH
	.string "{WINDOW 0x2E}"
		.string "That's Omega.\n"
		.string "His mere existence\n"
		.string "defies reality...▼"
		.string "He's strong, but...▼"
		.string "He's not as fun to\n"
		.string "fight as you are.\n"
		.string "Hehe...▼"
		.string "I don't feel like\n"
		.string "fighting him, so\n"
		.string "he's all yours...▼"
		.string "See you later, Zero.$"
	.else
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
	.endif

Text_SpaceCraft_BahThat: @ 0x0837F61B
	@ EN: Bah, that / Leviathan... / Grr, I can't move! / We'll have to finish / this another time! / Hey, Zero! / I'll get you and / that Omega one of / these days! / Don't you dare die / before then, Zero!
	.if ENGLISH
	.string "{WINDOW 0x30}"
		.string "Bah, that\n"
		.string "Leviathan...▼"
		.string "Grr, I can't move!\n"
		.string "We'll have to finish\n"
		.string "this another time!▼"
		.string "Hey, Zero!▼"
		.string "I'll get you and\n"
		.string "that Omega one of\n"
		.string "these days!▼"
		.string "Don't you dare die\n"
		.string "before then, Zero!$"
	.else
	.string "{WINDOW 0x30}"
		.string "ちっ、レヴィアタンめ…▼"
		.string "くそっ、体がいうことをきかねえ…\n"
		.string "今日のところは出なおしだ…！▼"
		.string "おい…ゼロ！▼"
		.string "テメエもオメガも…\n"
		.string "いつかかならず…ぶっころす！▼"
		.string "それまで死ぬんじゃねーぞ…\n"
		.string "ゼロ……！$"
	.endif

Text_SpaceCraft_OmegaHuhSoYouWere: @ 0x0837F682
	@ EN: Omega, huh? / So you were the one / who called me here?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Omega, huh?▼"
		.string "So you were the one\n"
		.string "who called me here?$"
	.else
	.string "{WINDOW 0x04}"
		.string "オメガとか言ったな…▼"
		.string "オマエか…\n"
		.string "オレを呼んでいたのは…$"
	.endif

Text_SpaceCraft_Grrr: @ 0x0837F6A3
	@ EN: Grrr...
	.if ENGLISH
	.string "{WINDOW 0x3D}"
		.string "Grrr...$"
	.else
	.string "{WINDOW 0x3D}"
		.string "グ…オオ……！$"
	.endif

Text_SpaceCraft_YouJustDonTGive: @ 0x0837F6AD
	@ EN: You just don't give / up, do you...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "You just don't give\n"
		.string "up, do you...$"
	.else
	.string "{WINDOW 0x04}"
		.string "ちっ…\n"
		.string "しぶといヤツだ$"
	.endif

Text_SpaceCraft_SoYouReOmegaI: @ 0x0837F6BB
	@ EN: So you're Omega. / I'm afraid I can't / let you leave this / place, ever. / Time for your / destruction!
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "So you're Omega.▼"
		.string "I'm afraid I can't\n"
		.string "let you leave this\n"
		.string "place, ever.▼"
		.string "Time for your\n"
		.string "destruction!$"
	.else
	.string "{WINDOW 0x2C}"
		.string "オマエがオメガ…か…▼"
		.string "オマエのようなものを\n"
		.string "ここから出すわけにはいかん▼"
		.string "ここで…ハカイする！！$"
	.endif

Text_SpaceCraft_Gaaarrrrwl: @ 0x0837F6EE
	@ EN: Gaaarrrrwl!
	.if ENGLISH
	.string "{WINDOW 0x3D}"
		.string "Gaaarrrrwl!$"
	.else
	.string "{WINDOW 0x3D}"
		.string "グオオオオオッ！$"
	.endif

Text_SpaceCraft_HeheheheOmegaThatWillBe: @ 0x0837F6F9
	@ EN: Hehehehe... / Omega, that will be / quite enough.
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "Hehehehe...▼"
		.string "Omega, that will be\n"
		.string "quite enough.$"
	.else
	.string "{WINDOW 0x3B}"
		.string "クーックックックッ…▼"
		.string "オメガよ…\n"
		.string "そのくらいにしておけ$"
	.endif

Text_SpaceCraft_FromThisDay: @ 0x0837F717
	@ EN: From this day / forward... / You will fight with / this person as a / Neo Arcadian. / It's not polite, / smashing a friend / like that.
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "From this day\n"
		.string "forward...▼"
		.string "You will fight with\n"
		.string "this person as a\n"
		.string "Neo Arcadian.▼"
		.string "It's not polite,\n"
		.string "smashing a friend\n"
		.string "like that.$"
	.else
	.string "{WINDOW 0x3B}"
		.string "オマエは今日から…▼"
		.string "ネオ・アルカディアの\n"
		.string "メンバーとして\n"
		.string "この方と ともに戦うのだ…▼"
		.string "仲間になる者を\n"
		.string "ころしてしまっては、\n"
		.string "いごこちも悪かろう…$"
	.endif

Text_SpaceCraft_Gaarwl: @ 0x0837F76A
	@ EN: Gaarwl... / Lord...Weil... / A Neo Arcadian?! / Who is this guy?!
	.if ENGLISH
	.string "{WINDOW 0x3D}"
		.string "Gaarwl...\n"
		.string "Lord...Weil...▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}A Neo Arcadian?!▼"
		.string "Who is this guy?!$"
	.else
	.string "{WINDOW 0x3D}"
		.string "グ…オオ…\n"
		.string "バイル…サマ…▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}ネオ・アルカディアの…\n"
		.string "メンバーだと！？▼"
		.string "何者だ！？$"
	.endif

Text_SpaceCraft_HeheheheIAmWeilYou: @ 0x0837F79A
	@ EN: Hehehehe... / I am Weil. You may / call me Dr. Weil. / You must know my / name, Harpuia of the / Four Guardians? / And you...the / legendary hero. / Zero... / Dr. Weil?! / You're kidding me! / It can't be! Why / are you, who were / banished from Neo / Arcadia a century / ago, with Omega?! / That's simple. / I-I brought him.
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}Hehehehe...▼"
		.string "I am Weil. You may\n"
		.string "call me Dr. Weil.▼"
		.string "You must know my\n"
		.string "name, Harpuia of the\n"
		.string "Four Guardians?▼"
		.string "And you...the\n"
		.string "legendary hero.▼"
		.string "Zero...▼"
	.string "{WINDOW 0x2C}"
		.string "{BOTTOM}Dr. Weil?!▼"
		.string "You're kidding me!\n"
		.string "It can't be! Why\n"
		.string "are you, who were▼"
		.string "banished from Neo\n"
		.string "Arcadia a century\n"
		.string "ago, with Omega?!▼"
	.string "{WINDOW 0x37}"
		.string "{BOTTOM}That's simple.▼"
		.string "I-I brought him.$"
	.else
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
	.endif

Text_SpaceCraft_MMasterX: @ 0x0837F847
	@ EN: M...Master X?! / Is that you?!
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "M...Master X?!\n"
		.string "Is that you?!$"
	.else
	.string "{WINDOW 0x2C}"
		.string "エ…\n"
		.string "エックス…さま！？$"
	.endif

Text_SpaceCraft_HarpuiaHeheYou: @ 0x0837F856
	@ EN: Harpuia! Hehe, you / haven't ch-changed! / And th-then / there's... / I missed y-you, / Zero...
	.if ENGLISH
	.string "{WINDOW 0x37}"
		.string "Harpuia! Hehe, you\n"
		.string "haven't ch-changed!▼"
		.string "And th-then\n"
		.string "there's...▼"
		.string "I missed y-you,\n"
		.string "Zero...$"
	.else
	.string "{WINDOW 0x37}"
		.string "ギギッ…ハルピュイアか\n"
		.string "フフ…かわりない…な▼"
		.string "そしテ……▼"
		.string "会いタかッたよ……ゼロ$"
	.endif

Text_SpaceCraft_YouMustBe: @ 0x0837F882
	@ EN: You must be... / You're a copy, / aren't you? / Hehehe! / I brought back / Master X, whom you / defeated long ago! / To protect humanity / from the chaos of / this world! / Weil saved my life. / I owe h-him, see... / I'll take Omega / back, thank y-you. / Harpuia, you k-keep / searching for the / Dark Elf. / Omega and the Dark / Elf... / We'll need them / both for what's to / c-come...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "You must be...\n"
		.string "You're a copy,\n"
		.string "aren't you?▼"
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}Hehehe!▼"
		.string "I brought back\n"
		.string "Master X, whom you\n"
		.string "defeated long ago!▼"
		.string "To protect humanity\n"
		.string "from the chaos of\n"
		.string "this world!▼"
	.string "{WINDOW 0x37}"
		.string "{TOP}Weil saved my life.\n"
		.string "I owe h-him, see...▼"
		.string "I'll take Omega\n"
		.string "back, thank y-you.▼"
		.string "Harpuia, you k-keep\n"
		.string "searching for the\n"
		.string "Dark Elf.▼"
		.string "Omega and the Dark\n"
		.string "Elf... ▼"
		.string "We'll need them\n"
		.string "both for what's to\n"
		.string "c-come...$"
	.else
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
	.endif

Text_SpaceCraft_ButMasterXThink: @ 0x0837F955
	@ EN: But Master X! Think / how many humans died / because of the Dark / Elf and Omega, both / built by this man... / How can you justify / exposing humanity to / such a grave danger, / especially now with / the energy crisis / almost solved?! / What's this? Are you / trying to tell / Master X what to do? / When did you grow so / bold, Harpuia?
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "But Master X! Think\n"
		.string "how many humans died▼"
		.string "because of the Dark\n"
		.string "Elf and Omega, both\n"
		.string "built by this man...▼"
		.string "How can you justify\n"
		.string "exposing humanity to\n"
		.string "such a grave danger,▼"
		.string "especially now with\n"
		.string "the energy crisis\n"
		.string "almost solved?!▼"
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}What's this? Are you\n"
		.string "trying to tell\n"
		.string "Master X what to do?▼"
		.string "When did you grow so\n"
		.string "bold, Harpuia?$"
	.else
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
	.endif

Text_SpaceCraft_WeilYouSoZeroYou: @ 0x0837FA09
	@ EN: Weil...you... / So, Zero. / You g-guys are / also searching for / the Dark Elf, right? / Let's m-make a / contest out of it! / I'll sh-show you / who the real hero / i-is!
	.if ENGLISH
	.string "{WINDOW 0x2C}"
		.string "{TOP}Weil...you...▼"
	.string "{WINDOW 0x37}"
		.string "So, Zero.▼"
		.string "You g-guys are\n"
		.string "also searching for\n"
		.string "the Dark Elf, right?▼"
		.string "Let's m-make a\n"
		.string "contest out of it!▼"
		.string "I'll sh-show you\n"
		.string "who the real hero\n"
		.string "i-is!$"
	.else
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
	.endif

Text_SpaceCraft_HeheheNowThings: @ 0x0837FA77
	@ EN: Hehehe... Now things / are getting / interesting, Zero! / Let's see how far / you get with that / body! Hehehe...
	.if ENGLISH
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}Hehehe... Now things\n"
		.string "are getting\n"
		.string "interesting, Zero!▼"
		.string "Let's see how far\n"
		.string "you get with that\n"
		.string "body! Hehehe...$"
	.else
	.string "{WINDOW 0x3B}"
		.string "{BOTTOM}クーックックックッ…\n"
		.string "たのしくなってきたな、ゼロ！▼"
		.string "そのカラダでどこまでできるか…\n"
		.string "見せてもらうとしよう！\n"
		.string "クックックッ…$"
	.endif

Text_SpaceCraft_WithThatBody: @ 0x0837FAB9
	@ EN: "With that body"...? / ...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "{0xE9}With that body{0xE9}...?▼"
		.string "...$"
	.else
	.string "{WINDOW 0x04}"
		.string "そのカラダ…だと…？▼"
		.string "………$"
	.endif

Text_SpaceCraft_CielZeroThisIsTerrible: @ 0x0837FACA
	@ EN: Ciel: Zero... / This is terrible...
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Zero... ▼"
		.string "This is terrible...$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「ゼロ……▼"
		.string "タイヘンなことになったわね……$"
	.endif

Text_SpaceCraft_SoYouWere: @ 0x0837FAE5
	@ EN: So you were / monitoring the whole / thing?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "So you were\n"
		.string "monitoring the whole\n"
		.string "thing?$"
	.else
	.string "{WINDOW 0x04}"
		.string "モニターしていたのか……$"
	.endif

Text_SpaceCraft_CielHurryBackToBase: @ 0x0837FAF4
	@ EN: Ciel: Hurry back to base. / Operator? / Operator: Commencing trans.
	.if ENGLISH
	.string "{WINDOW 0x00}"
		.string "Ciel: Hurry back to base.▼"
		.string "Operator?▼"
	.string "{WINDOW 0x00}"
		.string "Operator: Commencing trans.$"
	.else
	.string "{WINDOW 0x00}"
		.string "シエル「すぐにベースへもどってきて……▼"
		.string "オペレーターさん…おねがい▼"
	.string "{WINDOW 0x00}"
		.string "オペレーター「転送をカイシします$"
	.endif

.balign 4, 0
