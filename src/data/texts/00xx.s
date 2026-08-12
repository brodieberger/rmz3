.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_System:: @ 0x08376920
	.2byte (Text_System_WhoWillYouTalkWith-Start), (Text_System_WhatDoYouNeed-Start), (Text_System_SaveData-Start), (Text_System_SaveDataWhere-Start), (Text_System_OkToOverwrite-Start), (Text_System_LoadWhichData-Start), (Text_System_OkToLoad-Start), (Text_System_EraseWhichData-Start)
	.2byte (Text_System_OkToErase-Start), (Text_System_DataSaved-Start), (Text_System_DataLoaded-Start), (Text_System_DataErased-Start), (Text_System_YourOrdersPlease-Start), (Text_System_YourOrdersPlease_Alias1-Start), (Text_System_YourOrdersPlease_Alias2-Start), (Text_System_YourOrdersPlease_Alias3-Start)
	.2byte (Text_System_DisplayingThe-Start), (Text_System_AllRightLetS-Start), (Text_System_TheseAreTheOnly-Start), (Text_System_Empty-Start), (Text_System_TheNeoArcadian-Start), (Text_System_DoSomeScouting-Start), (Text_System_WeVeVerifiedA-Start), (Text_System_MissionAsk_1-Start)
	.2byte (Text_System_WeHaveDiscoveredA-Start), (Text_System_MissionAsk_2-Start), (Text_System_ThisWasAResi-Start), (Text_System_MissionAsk_3-Start), (Text_System_MissionSummary_4-Start), (Text_System_MissionAsk_4-Start), (Text_System_MissionSummary_5-Start), (Text_System_MissionAsk_5-Start)
	.2byte (Text_System_MissionSummary_6-Start), (Text_System_MissionAsk_6-Start), (Text_System_WeHaveAnalyzedThe-Start), (Text_System_MissionAsk_7-Start), (Text_System_ThisIsANeo-Start), (Text_System_MissionAsk_8-Start), (Text_System_ContainersHave-Start), (Text_System_MissionAsk_9-Start)
	.2byte (Text_System_TheRuinsOfAn-Start), (Text_System_MissionAsk_10-Start), (Text_System_NeoArcadiaHas-Start), (Text_System_MissionAsk_11-Start), (Text_System_CommencingTransfer-Start), (Text_System_AreYouReady-Start), (Text_System_WhereToTransfer-Start), (Text_System_WhereToTransfer_Alias1-Start)
	.2byte (Text_System_WhereToTransfer_Alias2-Start), (Text_System_WhereToTransfer_Alias3-Start), (Text_System_WhereToTransfer_Alias4-Start), (Text_System_DerelictSpacecraft-Start), (Text_System_AegisVolcanoBase-Start), (Text_System_OceanicHwyRuins-Start), (Text_System_WRFactory-Start), (Text_System_OldResidential-Start)
	.2byte (Text_System_MissileFactory-Start), (Text_System_TwilightDesert-Start), (Text_System_ForestOfAnatre-Start), (Text_System_FrontlineIceBase-Start), (Text_System_AreaX2-Start), (Text_System_EnergyFacility-Start), (Text_System_SnowyPlains-Start), (Text_System_SunkenLibrary-Start)
	.2byte (Text_System_GiantElevator-Start), (Text_System_SubArcadia-Start), (Text_System_MissionAssigned-Start), (Text_System_MissionAssigned_Alias1-Start), (Text_System_MissionAssigned_Alias2-Start), (Text_System_MissionAssigned_Alias3-Start), (Text_System_MissionAssigned_Alias4-Start), (Text_System_PreparationsFor-Start)
	.2byte (Text_System_Transfer-Start), (Text_System_ZeroBeCareful-Start), (Text_System_ZeroBeCareful_Alias1-Start), (Text_System_ZeroEllipsis-Start), (Text_System_ZeroComeBackSafely-Start), (Text_System_DonTDoAnything-Start), (Text_System_ZeroComeBackSafely_2-Start), (Text_System_Zerrroooo-Start)
	.2byte (Text_System_Transferring-Start), (Text_System_TransferComplete-Start), (Text_System_WhatShouldIDoWell-Start), (Text_System_WhatShouldIDoWell_Alias1-Start), (Text_System_WhatShouldIDoWell_Alias2-Start), (Text_System_WhatShouldIDoWell_Alias3-Start), (Text_System_WhatShouldIDoWell_Alias4-Start), (Text_System_WhatShouldIDoWell_Alias5-Start)
	.2byte (Text_System_WhatShouldIDoWell_Alias6-Start), (Text_System_WhatShouldIDoWell_Alias7-Start), (Text_System_ThankYouZeroWeFailed-Start), (Text_System_ZeroIMSorryYou-Start), (Text_System_ZeroThankYouThatRecycling-Start), (Text_System_ZeroThankYouTheReports-Start), (Text_System_CielGoodluck_7-Start), (Text_System_CielGoodluck_8-Start)
	.2byte (Text_System_CielGoodluck_9-Start), (Text_System_WelcomeBackZeroItAppears-Start), (Text_System_CielGoodluck_12-Start), (Text_System_CielGoodluck_13-Start), (Text_System_ThankYouZeroItLooks-Start), (Text_System_ZeroItSGreatTo-Start), (Text_System_WhatWillItBe-Start), (Text_System_BootCompleted-Start)
	.2byte (Text_System_EnterCommand-Start), (Text_System_CanTradeBattlechipsW-Start), (Text_System_BeginTransmission-Start), (Text_System_WaitingForTransmission-Start), (Text_System_CommunicatingWith-Start), (Text_System_TransmissionError-Start), (Text_System_TransmissionComplete-Start), (Text_System_TransmissionComplete_2-Start)
	.2byte (Text_System_MegaBoosterCardReceived-Start), (Text_System_MegaBoosterCardReceived_Alias1-Start), (Text_System_MegaBoosterCardReceived_Alias2-Start), (Text_System_MegaBoosterCardReceived_Alias3-Start), (Text_System_TransmissionError_2-Start), (Text_System_CardBoostReverted-Start), (Text_System_TitleBackgroundPicture-Start), (Text_System_TitleBackgroundPicture_Alias1-Start)
	.2byte (Text_System_TitleBackgroundPicture_Alias2-Start), (Text_System_TitleBackgroundPicture_Alias3-Start), (Text_System_PottedPlantAddedTo-Start), (Text_System_DesignOfElevatorIn-Start), (Text_System_ModCard_3-Start), (Text_System_PHunterEnergy-Start), (Text_System_PGuardianEnergy-Start), (Text_System_DesignOfNurseElvesHas-Start)
	.2byte (Text_System_ModCard_7-Start), (Text_System_TheDesignOfBustershot-Start), (Text_System_TheDesignOfTheZ-Start), (Text_System_TheDesignOfAlouetteS-Start), (Text_System_ModCard_11-Start), (Text_System_ZeroSDefenseIsNow-Start), (Text_System_TheDesignOfTheMessage-Start), (Text_System_TheDesignOfLifeEnergy-Start)
	.2byte (Text_System_ModCard_18-Start), (Text_System_AllBoostedItemsHave-Start), (Text_System_ThereIsALostCat-Start), (Text_System_ItIsSnowingAtThe-Start), (Text_System_TheDesignOfThe-Start), (Text_System_ModCard_23-Start), (Text_System_ModCard_24-Start), (Text_System_DesignOfComputerIn-Start)
	.2byte (Text_System_AMysteriousCyberElfHas-Start), (Text_System_ModCard_27-Start), (Text_System_APaintingHasBeenHung-Start), (Text_System_ANewDoorHasAppeared-Start), (Text_System_ModCard_30-Start), (Text_System_ModCard_31-Start), (Text_System_AFlowerHasBloomedOn-Start), (Text_System_TheDesignOfAnimalElves-Start)
	.2byte (Text_System_AndrewLooksYoungerNow-Start), (Text_System_ModCard_38-Start), (Text_System_SeagullsNowFlyInThe-Start), (Text_System_ModCard_41-Start), (Text_System_TheDesignOfSecretDisks-Start), (Text_System_ModCard_43-Start), (Text_System_SomebodyHasDrawnGraffiti-Start), (Text_System_ModCard_48-Start)
	.2byte (Text_System_ModCard_52-Start), (Text_System_ModCard_60-Start), (Text_System_ModCard_61-Start), (Text_System_ModCard_64-Start), (Text_System_ModCard_65-Start), (Text_System_TheDesignOfHackerElves-Start), (Text_System_EnergyOfCrossbyneHas-Start), (Text_System_EnergyOfPBase-Start)
	.2byte (Text_System_ModCard_69-Start), (Text_System_ItIsNowNighttimeAt-Start), (Text_System_EnergyOfPAqua-Start), (Text_System_FishNowJumpAroundThe-Start), (Text_System_ModCard_78-Start), (Text_System_ModCard_79-Start), (Text_System_ModCard_81-Start), (Text_System_ModCard_82-Start)
	.2byte (Text_System_EnergyOfPBomber-Start), (Text_System_EnergyOfAlteredP-Start), (Text_System_ModCard_90-Start), (Text_System_EnergyOfPurplenerple-Start), (Text_System_EnergyOfShellcrawler-Start), (Text_System_EnergyOfIcebonIncreased-Start), (Text_System_EnergyOfGCannon-Start), (Text_System_EnergyOfClaveker-Start)
	.2byte (Text_System_EnergyOfShotcounter-Start), (Text_System_EnergyOfGrandCannon-Start), (Text_System_EnergyOfShrimpolin-Start), (Text_System_EnergyOfBatring-Start), (Text_System_EnergyOfPCannon-Start), (Text_System_EnergyOfVolcaire-Start), (Text_System_EnergyOfSnakecord-Start), (Text_System_EnergyOfLemmingles-Start)
	.2byte (Text_System_EnergyOfLamplort-Start), (Text_System_EnergyOfTileCannon-Start), (Text_System_EnergyOfShelluno-Start), (Text_System_EnergyOfHeavyCannon-Start), (Text_System_EnergyOfMothjiro-Start), (Text_System_EnergyOfCCannon-Start), (Text_System_EnergyOfCalibeeG-Start), (Text_System_EnergyOfDeathlock-Start)
	.2byte (Text_System_EnergyOfGyroCannon-Start), (Text_System_EnergyOfSharkshielX-Start), (Text_System_EnergyOfOlwarmer-Start), (Text_System_EnergyOfBranwarmer-Start), (Text_System_EnergyOfLocomoIf-Start), (Text_System_EnergyOfBeeserver-Start), (Text_System_EnergyOfMegamilpa-Start), (Text_System_ZeroSMiniGame-Start)
	.2byte (Text_System_ZeroSMiniGame_Alias1-Start), (Text_System_ZeroSMiniGame_Alias2-Start), (Text_System_ZeroSMiniGame_Alias3-Start), (Text_System_CielSMiniGame-Start), (Text_System_CopyXSMiniGame-Start), (Text_System_HarpuiaSMiniGame-Start), (Text_System_FefnirSMiniGame-Start), (Text_System_LeviathanSMiniGame-Start)
	.2byte (Text_System_PhantomSMiniGame-Start), (Text_System_HardModeAddedPlayIn-Start), (Text_System_UltimateModeAddedPlayIn-Start)

Text_System:: @ 0x08376ad6
Start:
    # シエル
Text_System_WhoWillYouTalkWith: @ 0x08376AD6
	@ EN: Who will you talk with? / Operator / Ciel
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Who will you talk with?\n"
		.string "  Operator\n"
		.string "  Ciel$"
	.else
	.string "{WINDOW 0x02}"
		.string "だれに、話しかけますか？\n"
		.string "  オペレーター\n"
		.string "  シエル$"
	.endif

Text_System_WhatDoYouNeed: @ 0x08376AF5
	@ EN: What do you need? / Manage data / Talk
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "What do you need?\n"
		.string "  Manage data\n"
		.string "  Talk$"
	.else
	.string "{WINDOW 0x40}"
		.string "なにかしら？ なんでも言ってね\n"
		.string "  データのかんり\n"
		.string "  話をする$"
	.endif

Text_System_SaveData: @ 0x08376B1A
	@ EN: Save data / Load data / Erase data
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "  Save data\n"
		.string "  Load data\n"
		.string "  Erase data$"
	.else
	.string "{WINDOW 0x40}"
		.string "  データをキロクします\n"
		.string "  データを呼び出します\n"
		.string "  データを消します$"
	.endif

Text_System_SaveDataWhere: @ 0x08376B44
	@ EN: Save data where?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Save data where?$"
	.else
	.string "{WINDOW 0x40}"
		.string "どこにデータをキロクしますか？$"
	.endif

Text_System_OkToOverwrite: @ 0x08376B56
	@ EN: : OK to overwrite? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string " : OK to overwrite?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x40}"
		.string " のデータを上がきしていいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_LoadWhichData: @ 0x08376B76
	@ EN: Load which data?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Load which data?$"
	.else
	.string "{WINDOW 0x40}"
		.string "どのデータを呼び出しますか？$"
	.endif

Text_System_OkToLoad: @ 0x08376B89
	@ EN: : OK to load? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string " : OK to load?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x40}"
		.string " のデータを呼び出していいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_EraseWhichData: @ 0x08376BAA
	@ EN: Erase which data?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Erase which data?$"
	.else
	.string "{WINDOW 0x40}"
		.string "どのデータを消しますか？$"
	.endif

Text_System_OkToErase: @ 0x08376BBA
	@ EN: : OK to erase? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string " : OK to erase?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x40}"
		.string " のデータを消していいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_DataSaved: @ 0x08376BD8
	@ EN: Data saved.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Data saved.$"
	.else
	.string "{WINDOW 0x40}"
		.string "データをキロクしました$"
	.endif

Text_System_DataLoaded: @ 0x08376BE6
	@ EN: Data loaded.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Data loaded.$"
	.else
	.string "{WINDOW 0x40}"
		.string "データを呼び出しました$"
	.endif

Text_System_DataErased: @ 0x08376BF6
	@ EN: Data erased.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Data erased.$"
	.else
	.string "{WINDOW 0x40}"
		.string "データを消しました$"
	.endif

@ オペレータ
Text_System_YourOrdersPlease: @ 0x08376C03
Text_System_YourOrdersPlease_Alias1: @ 0x08376C03
Text_System_YourOrdersPlease_Alias2: @ 0x08376C03
Text_System_YourOrdersPlease_Alias3: @ 0x08376C03
	@ EN: Your orders, please. / Select mission / Transfer back
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{TOP}Your orders, please.\n"
		.string "  Select mission\n"
		.string "  Transfer back$"
	.else
	.string "{WINDOW 0x62}"
		.string "{TOP}しじを おねがいします\n"
		.string "  ミッションへ行く\n"
		.string "  いちど行ったエリアへ転送$"
	.endif

Text_System_DisplayingThe: @ 0x08376C30
	@ EN: Displaying the / available missions:
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{TOP}Displaying the\n"
		.string "available missions:$"
	.else
	.string "{WINDOW 0x62}"
		.string "{TOP}センタクできるミッションを\n"
		.string "ひょうじ します$"
	.endif

Text_System_AllRightLetS: @ 0x08376C4A
	@ EN: All right, let's / look at something / else.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}All right, let's\n"
		.string "look at something\n"
		.string "else.$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}では、他を見てみましょう$"
	.endif

Text_System_TheseAreTheOnly: @ 0x08376C5C
	@ EN: These are the only / available missions. / Return when ready.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}These are the only\n"
		.string "available missions.\n"
		.string "Return when ready.$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}このミッションしかセンタクできません\n"
		.string "ジュンビができましたら\n"
		.string "いつでも声をおかけください…$"
	.endif

Text_System_Empty: @ 0x08376C8E
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}$"
	.endif

@ ミッション選択(序盤4)
Text_System_TheNeoArcadian: @ 0x08376C92
	@ EN: The Neo Arcadian / army is building up / at the base in Aegis / Volcano. / We do not know what / their intention is.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}The Neo Arcadian\n"
		.string "army is building up\n"
		.string "at the base in Aegis▼"
		.string "Volcano.▼"
		.string "We do not know what\n"
		.string "their intention is.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ネオ・アルカディア軍が\n"
		.string "アグニスかざんにある基地に\n"
		.string "シュウケツしつつあります▼"
		.string "カレらの目的は、\n"
		.string "現在のところ不明…$"
	.endif

Text_System_DoSomeScouting: @ 0x08376CD8
	@ EN: Do some scouting? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Do some scouting?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}テイサツをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_WeVeVerifiedA: @ 0x08376CF8
	@ EN: We've verified a / reading similar to / the Dark Elf on the / ruins of an inter- / continental oceanic / highway... / We have verified / that Neo Arcadia / is pursuing this. / We believe it will / take some time for / them to reach the / source of this / reading. / If possible, you / should verify / this signal, / and if it is indeed / the Dark Elf, / protect it.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We've verified a\n"
		.string "reading similar to\n"
		.string "the Dark Elf on the▼"
		.string "ruins of an inter-\n"
		.string "continental oceanic\n"
		.string "highway...▼"
		.string "We have verified\n"
		.string "that Neo Arcadia\n"
		.string "is pursuing this.▼"
		.string "We believe it will\n"
		.string "take some time for\n"
		.string "them to reach the▼"
		.string "source of this\n"
		.string "reading.▼"
		.string "If possible, you\n"
		.string "should verify\n"
		.string "this signal,▼"
		.string "and if it is indeed\n"
		.string "the Dark Elf,\n"
		.string "protect it.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}カイジョウをはしる\n"
		.string "タイリク間ハイウェイあとちにて\n"
		.string "ダークエルフらしきハンノウと…▼"
		.string "それをツイセキする\n"
		.string "ネオ・アルカディアを…\n"
		.string "カクニンしました▼"
		.string "カレらがこのハンノウを\n"
		.string "ホソクするまで\n"
		.string "まだじかんがかかりそうですが…▼"
		.string "できれば、はやめに\n"
		.string "このハンノウをカクニンし…▼"
		.string "ダークエルフであった場合、\n"
		.string "ホゴしていただきたいのですが…$"
	.endif

Text_System_MissionAsk_1: @ 0x08376DA0
	@ EN: Do you accept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Do you accept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_WeHaveDiscoveredA: @ 0x08376DB9
	@ EN: We have discovered a / Neo Arcadian weapons / factory. / They are fixing and / refitting broken / weaponry. / It seems this is / more efficient than / making new ones. / They have doubled / weapon production / recently. / Destroy this factory / to cut Neo Arcadia's / military power.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We have discovered a\n"
		.string "Neo Arcadian weapons\n"
		.string "factory.▼"
		.string "They are fixing and\n"
		.string "refitting broken\n"
		.string "weaponry.▼"
		.string "It seems this is\n"
		.string "more efficient than\n"
		.string "making new ones.▼"
		.string "They have doubled\n"
		.string "weapon production\n"
		.string "recently.▼"
		.string "Destroy this factory\n"
		.string "to cut Neo Arcadia's\n"
		.string "military power.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ネオ・アルカディアの\n"
		.string "ヘイキ再生工場を発見しました▼"
		.string "こわれたヘイキをシュウリし\n"
		.string "再利用しているようなのですが…▼"
		.string "イチからセイサンするより\n"
		.string "コウリツがいいらしく▼"
		.string "ここ最近、\n"
		.string "ヘイキのセイサンリョウが\n"
		.string "2倍になっています▼"
		.string "この工場をハカイし\n"
		.string "ネオ・アルカディアの戦力を\n"
		.string "弱体化させたいのですが…$"
	.endif

Text_System_MissionAsk_2: @ 0x08376E5F
	@ EN: Do you accept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Do you accept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_ThisWasAResi: @ 0x08376E78
	@ EN: This was a resi- / dential area where / humans once lived. / We sent some people / to investigate... / And received news / that Dark Elf may / have been seen. / For some reason, we / are unable to scan / this area. / We would like you to / go there to investi- / gate first-hand.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}This was a resi-\n"
		.string "dential area where\n"
		.string "humans once lived.▼"
		.string "We sent some people\n"
		.string "to investigate...▼"
		.string "And received news\n"
		.string "that Dark Elf may\n"
		.string "have been seen.▼"
		.string "For some reason, we\n"
		.string "are unable to scan\n"
		.string "this area.▼"
		.string "We would like you to\n"
		.string "go there to investi-\n"
		.string "gate first-hand.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ここは かつて人間がすんでいた\n"
		.string "きょじゅうくのあとちです▼"
		.string "チョウサに行った仲間たちから…▼"
		.string "ダークエルフらしきものを\n"
		.string "見たというホウコクが\n"
		.string "とどいています▼"
		.string "このエリアにたいしては\n"
		.string "なぜかスキャンが使用できません▼"
		.string "ゼロさんにチョクセツ\n"
		.string "チョウサに行って\n"
		.string "いただきたいのですが…$"
	.endif

Text_System_MissionAsk_3: @ 0x08376F0D
	@ EN: Can you investigate? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you investigate?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサ…おねがいできますか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

@ ミッション選択(中盤4)
Text_System_MissionSummary_4: @ 0x08376F2B
	@ EN: We have detected / Neo Arcadian units / moving through the / southern desert. / These forces must be / intercepted as / soon as possible.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We have detected\n"
		.string "Neo Arcadian units\n"
		.string "moving through the▼"
		.string "southern desert.▼"
		.string "These forces must be\n"
		.string "intercepted as\n"
		.string "soon as possible.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ミナミの砂ばくをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "ヒカク的はやめのゲイゲキが\n"
		.string "ヒツヨウかと思われます$"
	.endif

Text_System_MissionAsk_4: @ 0x08376F6A
	@ EN: Can you intercept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you intercept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_MissionSummary_5: @ 0x08376F8A
	@ EN: We have detected / Neo Arcadian units / moving through the / Forest of Anatre... / These forces must be / intercepted as / soon as possible.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We have detected\n"
		.string "Neo Arcadian units\n"
		.string "moving through the▼"
		.string "Forest of Anatre...▼"
		.string "These forces must be\n"
		.string "intercepted as\n"
		.string "soon as possible.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}アナトレーのモリをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "ヒカク的はやめのゲイゲキが\n"
		.string "ヒツヨウかと思われます$"
	.endif

Text_System_MissionAsk_5: @ 0x08376FC9
	@ EN: Can you intercept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you intercept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_MissionSummary_6: @ 0x08376FE9
	@ EN: We have detected / Neo Arcadian units / moving through the / northern tundra... / The enemy is / constructing a / frontline base. / There seems to be a / reasonable amount of / time left to act.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We have detected\n"
		.string "Neo Arcadian units\n"
		.string "moving through the▼"
		.string "northern tundra...▼"
		.string "The enemy is\n"
		.string "constructing a\n"
		.string "frontline base.▼"
		.string "There seems to be a\n"
		.string "reasonable amount of\n"
		.string "time left to act.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}キタのツンドラをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "テキは…\n"
		.string "ゼンセン基地を\n"
		.string "コウチクしているモヨウ…▼"
		.string "タショウの時間的ヨユウが\n"
		.string "あるものと思われます…$"
	.endif

Text_System_MissionAsk_6: @ 0x08377044
	@ EN: Can you intercept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you intercept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキに向かわれますか…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_WeHaveAnalyzedThe: @ 0x08377061
	@ EN: We have analyzed the / enemy's movements... / As a result, we have / succeeded in / determining the / location of the Neo / Arcadian HQ. / It seems that Copy X / and Weil are / commanding the / entire army from / this base. / If you strike here, / you may be able to / stop Neo Arcadia.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}We have analyzed the\n"
		.string "enemy's movements...▼"
		.string "As a result, we have\n"
		.string "succeeded in\n"
		.string "determining the▼"
		.string "location of the Neo\n"
		.string "Arcadian HQ.▼"
		.string "It seems that Copy X\n"
		.string "and Weil are\n"
		.string "commanding the▼"
		.string "entire army from\n"
		.string "this base.▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}If you strike here,\n"
		.string "you may be able to\n"
		.string "stop Neo Arcadia.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}テキのしんこうルートを\n"
		.string "カイセキし…▼"
		.string "ネオ・アルカディア本部の\n"
		.string "イチのトクテイに\n"
		.string "セイコウしました…▼"
		.string "コピーエックスとバイルは、\n"
		.string "ここより全軍のシキを\n"
		.string "とっているモヨウ…▼"
	.string "{WINDOW 0x04}"
		.string "{BOTTOM}ここをたたけば…\n"
		.string "ネオ・アルカディアを\n"
		.string "止めることができる…か…$"
	.endif

Text_System_MissionAsk_7: @ 0x083770E3
	@ EN: Are you ready? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}Are you ready?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ジュンビは、よろしいでしょうか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

@ ミッション選択(後半4)
Text_System_ThisIsANeo: @ 0x08377102
	@ EN: This is a Neo / Arcadian energy / plant. It is / currently shut. / What is so important / that they had to / shut down the plant / in the middle of an / energy crisis? / The place was shut / down around the time / Weil appeared, so it / bears investigation.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}This is a Neo\n"
		.string "Arcadian energy\n"
		.string "plant. It is▼"
		.string "currently shut.▼"
		.string "What is so important\n"
		.string "that they had to\n"
		.string "shut down the plant▼"
		.string "in the middle of an\n"
		.string "energy crisis?▼"
		.string "The place was shut\n"
		.string "down around the time\n"
		.string "Weil appeared, so it▼"
		.string "bears investigation.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ここはネオ・アルカディアの\n"
		.string "エネルギーしせつなのですが…\n"
		.string "今は、ヘイサされています▼"
		.string "エネルギー不足にもかかわらず\n"
		.string "シセツをヘイサしてまで\n"
		.string "カレらがやりたいことは何か？▼"
		.string "ちょうどバイルが現れたあたりに\n"
		.string "ヘイサされたのが気になります$"
	.endif

Text_System_MissionAsk_8: @ 0x0837717E
	@ EN: Can you investigate? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you investigate?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_ContainersHave: @ 0x0837719E
	@ EN: Containers have / fallen out of a / space ship, / which fell onto / snowy plains. / It is possible that / they contain data / about Omega or Weil. / We sent a scouting / party, but the / Neo Arcadian forces / are too strong, and / they cannot pass. / We would like you to / reinforce them, and / retrieve the data.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}Containers have\n"
		.string "fallen out of a\n"
		.string "space ship,▼"
		.string "which fell onto\n"
		.string "snowy plains.▼"
		.string "It is possible that\n"
		.string "they contain data\n"
		.string "about Omega or Weil.▼"
		.string "We sent a scouting\n"
		.string "party, but the\n"
		.string "Neo Arcadian forces▼"
		.string "are too strong, and\n"
		.string "they cannot pass.▼"
		.string "We would like you to\n"
		.string "reinforce them, and\n"
		.string "retrieve the data.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ウチュウセンがおちてきた\n"
		.string "あのセツゲンに…▼"
		.string "おそらくウチュウセンに\n"
		.string "つまれていたのだろうと思われる\n"
		.string "コンテナがちらばっています▼"
		.string "もしかしたら、\n"
		.string "オメガやバイルにかんするデータが\n"
		.string "のこっているカノウセイがあります▼"
		.string "テイサツ部隊を\n"
		.string "ハケンしていますが…▼"
		.string "ネオ・アルカディアの\n"
		.string "テイコウが強く…\n"
		.string "なかなかさきにすすめません▼"
		.string "仲間をエンゴし、\n"
		.string "データをカイシュウして\n"
		.string "いただきたいのですが…$"
	.endif

Text_System_MissionAsk_9: @ 0x08377267
	@ EN: Do you accept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Do you accept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_TheRuinsOfAn: @ 0x08377280
	@ EN: The ruins of an / ancient library have / been found. / It's completely / soaked inside, but / there may still be / some data around. / We'd like you to / search for data on / Weil or Omega.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}The ruins of an\n"
		.string "ancient library have\n"
		.string "been found.▼"
		.string "It's completely\n"
		.string "soaked inside, but\n"
		.string "there may still be▼"
		.string "some data around.▼"
		.string "We'd like you to\n"
		.string "search for data on\n"
		.string "Weil or Omega.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}旧ジダイのトショカンのイセキが\n"
		.string "発見されました▼"
		.string "内部はミズびたしですが…\n"
		.string "どこかに生きてるデータが\n"
		.string "あるかもしれません▼"
		.string "バイルやオメガのデータを\n"
		.string "さがしていただきたいのですが…$"
	.endif

Text_System_MissionAsk_10: @ 0x083772E2
	@ EN: Do you accept? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Do you accept?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_NeoArcadiaHas: @ 0x083772FB
	@ EN: Neo Arcadia has / completed a giant / elevator. / We do not know its / purpose. / They are bringing / something up from / deep underground.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}Neo Arcadia has\n"
		.string "completed a giant\n"
		.string "elevator.▼"
		.string "We do not know its\n"
		.string "purpose.▼"
		.string "They are bringing\n"
		.string "something up from\n"
		.string "deep underground.$"
	.else
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ネオ・アルカディアが\n"
		.string "巨大なエレベーターを\n"
		.string "カンセイさせたようです▼"
		.string "使用目的は、不明…▼"
		.string "地下深くより\n"
		.string "何かをはこんでいるようです$"
	.endif

Text_System_MissionAsk_11: @ 0x0837734B
	@ EN: Can you investigate? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}Can you investigate?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサをおねがいできますか\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_CommencingTransfer: @ 0x08377368
	@ EN: Commencing transfer / to the coordinates / obtained from / Original X. / Zero... / Please be careful.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Commencing transfer\n"
		.string "to the coordinates\n"
		.string "obtained from▼"
		.string "Original X.▼"
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
		.string "Please be careful.$"
	.else
	.string "{WINDOW 0x61}"
		.string "オリジナルエックスより\n"
		.string "入手した ざひょうに転送します▼"
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "気をつけてね………$"
	.endif

Text_System_AreYouReady: @ 0x0837739C
	@ EN: Are you ready? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Are you ready?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "ジュンビは、よろしいでしょうか？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

@ フリーラン
Text_System_WhereToTransfer: @ 0x083773BA
Text_System_WhereToTransfer_Alias1: @ 0x083773BA
Text_System_WhereToTransfer_Alias2: @ 0x083773BA
Text_System_WhereToTransfer_Alias3: @ 0x083773BA
Text_System_WhereToTransfer_Alias4: @ 0x083773BA
	@ EN: Where to transfer?
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Where to transfer?$"
	.else
	.string "{WINDOW 0x62}"
		.string "どこに転送しますか？$"
	.endif

Text_System_DerelictSpacecraft: @ 0x083773C9
	@ EN: DERELICT SPACECRAFT? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}DERELICT SPACECRAFT{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}こわれたウチュウセン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_AegisVolcanoBase: @ 0x083773E7
	@ EN: AEGIS VOLCANO BASE? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}AEGIS VOLCANO BASE{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}アグニスかざんの基地{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_OceanicHwyRuins: @ 0x08377407
	@ EN: OCEANIC HWY RUINS? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}OCEANIC HWY RUINS{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}カイジョウのハイウェイあとち{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_WRFactory: @ 0x08377429
	@ EN: W.R. FACTORY? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}W.R. FACTORY{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}ヘイキ再生工場{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_OldResidential: @ 0x08377447
	@ EN: OLD RESIDENTIAL? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}OLD RESIDENTIAL{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}旧きょじゅうく{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_MissileFactory: @ 0x08377463
	@ EN: MISSILE FACTORY? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}MISSILE FACTORY{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}ミサイル工場{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_TwilightDesert: @ 0x0837747E
	@ EN: TWILIGHT DESERT? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}TWILIGHT DESERT{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}ゆうやみの砂ばく{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_ForestOfAnatre: @ 0x0837749B
	@ EN: FOREST OF ANATRE? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}FOREST OF ANATRE{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}アナトレーのモリ{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_FrontlineIceBase: @ 0x083774B7
	@ EN: FRONTLINE ICE BASE? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}FRONTLINE ICE BASE{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}コオリのゼンセン基地{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_AreaX2: @ 0x083774D7
	@ EN: AREA X-2? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}AREA X-2{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}エリアX-2{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_EnergyFacility: @ 0x083774F1
	@ EN: ENERGY FACILITY? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}ENERGY FACILITY{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}エネルギーしせつ{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_SnowyPlains: @ 0x0837750D
	@ EN: SNOWY PLAINS? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}SNOWY PLAINS{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}セツゲン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_SunkenLibrary: @ 0x08377525
	@ EN: SUNKEN LIBRARY? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}SUNKEN LIBRARY{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}すいぼつしたトショカン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_GiantElevator: @ 0x08377544
	@ EN: GIANT ELEVATOR? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}GIANT ELEVATOR{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}巨大エレベーター{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_SubArcadia: @ 0x08377562
	@ EN: SUB ARCADIA? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "{RED}SUB ARCADIA{RED_END}?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x62}"
		.string "{RED}アンダー・アルカディア{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

@ 転送
Text_System_MissionAssigned: @ 0x08377581
Text_System_MissionAssigned_Alias1: @ 0x08377581
Text_System_MissionAssigned_Alias2: @ 0x08377581
Text_System_MissionAssigned_Alias3: @ 0x08377581
Text_System_MissionAssigned_Alias4: @ 0x08377581
	@ EN: Mission assigned... / All personnel, / prepare to transfer.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Mission assigned...\n"
		.string "All personnel,\n"
		.string "prepare to transfer.$"
	.else
	.string "{WINDOW 0x61}"
		.string "ミッションはつれい…\n"
		.string "かくいん、転送じゅんびにかかれ$"
	.endif

Text_System_PreparationsFor: @ 0x083775A0
	@ EN: Preparations for / transfer complete.
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Preparations for\n"
		.string "transfer complete.$"
	.else
	.string "{WINDOW 0x62}"
		.string "転送じゅんびカンリョウ…$"
	.endif

Text_System_Transfer: @ 0x083775B1
	@ EN: Transfer!
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Transfer!$"
	.else
	.string "{WINDOW 0x61}"
		.string "転送！$"
	.endif

@ シエルの見送りメッセージ
Text_System_ZeroBeCareful: @ 0x083775B9
Text_System_ZeroBeCareful_Alias1: @ 0x083775B9
	@ EN: Zero... Be careful.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... Be careful.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…気をつけて……$"
	.endif
Text_System_ZeroEllipsis: @ 0x083775C7
	@ EN: Zero...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ……$"
	.endif

Text_System_ZeroComeBackSafely: @ 0x083775CE
	@ EN: Zero... / Come back safely... / Okay?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
		.string "Come back safely...\n"
		.string "Okay?$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "かならず…\n"
		.string "かえってきて…ね…$"
	.endif

Text_System_DonTDoAnything: @ 0x083775E5
	@ EN: Don't do anything / dangerous, Zero...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Don't do anything\n"
		.string "dangerous, Zero...$"
	.else
	.string "{WINDOW 0x40}"
		.string "無理しないでね…ゼロ$"
	.endif

Text_System_ZeroComeBackSafely_2: @ 0x083775F4
	@ EN: Zero... / Come back safely...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero...▼"
		.string "Come back safely...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "かえって…きてね……$"
	.endif

Text_System_Zerrroooo: @ 0x08377606
	@ EN: Zerrroooo!
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zerrroooo!$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼローーーーーー！$"
	.endif

@ ミッション終了後
Text_System_Transferring: @ 0x08377612
	@ EN: Transferring... / Two... / One...
	.if ENGLISH
	.string "{WINDOW 0x62}"
		.string "Transferring...\n"
		.string "Two...\n"
		.string "One...$"
	.else
	.string "{WINDOW 0x62}"
		.string "転送カンリョウまで…     \n"
		.string "2…     \n"
		.string "1…$"
	.endif

Text_System_TransferComplete: @ 0x08377631
	@ EN: Transfer complete.
	.if ENGLISH
	.string "{WINDOW 0x61}"
		.string "Transfer complete.$"
	.else
	.string "{WINDOW 0x61}"
		.string "おつかれさまでした$"
	.endif

Text_System_WhatShouldIDoWell: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias1: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias2: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias3: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias4: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias5: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias6: @ 0x0837763D
Text_System_WhatShouldIDoWell_Alias7: @ 0x0837763D
	@ EN: What should I do? / Well, for now... / Not letting Neo / Arcadia have the / Dark Elf... / That would be / priority number one. / I will calculate / our best course of / action, giving / priority to the / search for the / Dark Elf. / I will report to / Ms. Ciel as soon as / the results are in.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "What should I do?▼"
	.string "{WINDOW 0x05}"
		.string "Well, for now...▼"
		.string "Not letting Neo\n"
		.string "Arcadia have the\n"
		.string "Dark Elf...▼"
		.string "That would be\n"
		.string "priority number one.▼"
	.string "{WINDOW 0x62}"
		.string "I will calculate\n"
		.string "our best course of\n"
		.string "action, giving▼"
		.string "priority to the\n"
		.string "search for the\n"
		.string "Dark Elf.▼"
		.string "I will report to\n"
		.string "Ms. Ciel as soon as\n"
		.string "the results are in.$"
	.else
	.string "{WINDOW 0x40}"
		.string "どうしたらいいんだろう……\n"
		.string "わたし………▼"
	.string "{WINDOW 0x05}"
		.string "とりあえず……▼"
		.string "ダークエルフを\n"
		.string "ネオ・アルカディアに\n"
		.string "わたさないことが……▼"
		.string "サイユウセン……だな▼"
	.string "{WINDOW 0x62}"
		.string "ダークエルフそうさくを\n"
		.string "サイユウセンとして……▼"
		.string "今後ワレワレがとるべき行動を\n"
		.string "シミュレートしてみます▼"
		.string "ケッカがわかりしだい\n"
		.string "シエルさんにホウコクしますね$"
	.endif

Text_System_ThankYouZeroWeFailed: @ 0x083776DA
	@ EN: Thank you, Zero. / We failed to destroy / the missile, / but I believe we / succeeded in / delaying its / construction. / I will analyze the / route to the missile / factory as quickly / as possible. / Please wait a bit / longer, okay?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thank you, Zero.▼"
		.string "We failed to destroy\n"
		.string "the missile,▼"
		.string "but I believe we\n"
		.string "succeeded in\n"
		.string "delaying its▼"
		.string "construction.▼"
		.string "I will analyze the\n"
		.string "route to the missile\n"
		.string "factory as quickly▼"
		.string "as possible.▼"
		.string "Please wait a bit\n"
		.string "longer, okay?$"
	.else
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ▼"
		.string "ミサイルは、\n"
		.string "ハカイできなかったけど……▼"
		.string "これでミサイルのケンゾウを\n"
		.string "おくらせることができたはず……▼"
		.string "ミサイル工場へのルートは、\n"
		.string "できるだけ\n"
		.string "いそいでカイセキするわ▼"
		.string "もうしばらく\n"
		.string "時間をちょうだい…ね$"
	.endif

Text_System_ZeroIMSorryYou: @ 0x0837774D
	@ EN: Zero, I'm sorry. / You risked your life / to go after the Dark / Elf... / But the Dark Elf was / too fast, and we / lost sight of it. / I scanned that area / again, / but there's no / reading anywhere / in the vicinity. / I know an apology is / not enough, but I am / truly sorry, Zero.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero, I'm sorry.▼"
		.string "You risked your life\n"
		.string "to go after the Dark\n"
		.string "Elf...▼"
		.string "But the Dark Elf was\n"
		.string "too fast, and we\n"
		.string "lost sight of it.▼"
		.string "I scanned that area\n"
		.string "again,▼"
		.string "but there's no\n"
		.string "reading anywhere\n"
		.string "in the vicinity.▼"
		.string "I know an apology is\n"
		.string "not enough, but I am\n"
		.string "truly sorry, Zero.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…ごめんなさい……▼"
		.string "せっかくゼロがいのちがけで\n"
		.string "ダークエルフを\n"
		.string "おいかけてくれたのに……▼"
		.string "ダークエルフのスピードが\n"
		.string "はやすぎて\n"
		.string "見うしなってしまったの……▼"
		.string "もういちど\n"
		.string "さっきのエリアを\n"
		.string "スキャンしなおしたんだけど……▼"
		.string "やっぱり…もう…\n"
		.string "あのあたりにハンノウは\n"
		.string "ないみたい……▼"
		.string "あやまってすむことじゃないけど……\n"
		.string "本当にごめんなさい…ゼロ$"
	.endif

Text_System_ZeroThankYouThatRecycling: @ 0x083777FD
	@ EN: Zero... Thank you. / That recycling plant / will be out of / operation for some / time, I think. / Thank you so much...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... Thank you.▼"
		.string "That recycling plant\n"
		.string "will be out of\n"
		.string "operation for some▼"
		.string "time, I think.▼"
		.string "Thank you so much...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…ありがとう▼"
		.string "これで再生工場は、\n"
		.string "しばらく動かないと思うわ…▼"
		.string "本当に…ありがとう…$"
	.endif

Text_System_ZeroThankYouTheReports: @ 0x08377832
	@ EN: Zero... Thank you. / The reports of the / Dark Elf... / They were really / Baby Elf sitings... / I wonder what Neo / Arcadia is planning / on doing with them.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... Thank you.▼"
		.string "The reports of the\n"
		.string "Dark Elf...▼"
		.string "They were really\n"
		.string "Baby Elf sitings...▼"
		.string "I wonder what Neo\n"
		.string "Arcadia is planning\n"
		.string "on doing with them.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ、ありがとう…▼"
		.string "ホウコクにあった\n"
		.string "ダークエルフって…▼"
		.string "ベビーエルフたちのこと\n"
		.string "だったのね…▼"
		.string "ネオ・アルカディアは…\n"
		.string "あのコたちを使って\n"
		.string "何をするつもりなのかしら……$"
	.endif

Text_System_CielGoodluck_7: @ 0x0837788B
	@ EN: Thank you, Zero. / Now that they are / without a leader, / the Neo Arcadians in / that area have / retreated. / Thank you so much...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thank you, Zero.▼"
		.string "Now that they are\n"
		.string "without a leader,\n"
		.string "the Neo Arcadians in▼"
		.string "that area have\n"
		.string "retreated.▼"
		.string "Thank you so much...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"
	.endif

Text_System_CielGoodluck_8: @ 0x083778CB
	@ EN: Thank you, Zero. / Now that they are / without a leader, / the Neo Arcadians in / that area have / retreated. / Thank you so much...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thank you, Zero.▼"
		.string "Now that they are\n"
		.string "without a leader,\n"
		.string "the Neo Arcadians in▼"
		.string "that area have\n"
		.string "retreated.▼"
		.string "Thank you so much...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"
	.endif

Text_System_CielGoodluck_9: @ 0x0837790B
	@ EN: Thank you, Zero. / Now that they are / without a leader, / the Neo Arcadians in / that area have / retreated. / Thank you so much...
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thank you, Zero.▼"
		.string "Now that they are\n"
		.string "without a leader,\n"
		.string "the Neo Arcadians in▼"
		.string "that area have\n"
		.string "retreated.▼"
		.string "Thank you so much...$"
	.else
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"
	.endif

Text_System_WelcomeBackZeroItAppears: @ 0x0837794B
	@ EN: Welcome back, Zero. / It appears that Weil / was attempting to / mass-produce Baby / Elves at that / factory. / But I wonder... / What was he planning / on doing with all / those Baby Elves?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Welcome back, Zero.▼"
		.string "It appears that Weil\n"
		.string "was attempting to\n"
		.string "mass-produce Baby▼"
		.string "Elves at that\n"
		.string "factory.▼"
		.string "But I wonder...▼"
		.string "What was he planning\n"
		.string "on doing with all\n"
		.string "those Baby Elves?$"
	.else
	.string "{WINDOW 0x40}"
		.string "おかえりなさい…ゼロ…▼"
		.string "バイルは、あの工場で\n"
		.string "ベビーエルフをタイリョウに\n"
		.string "作ろうとしてたみたい…▼"
		.string "でも いったい……▼"
		.string "ベビーエルフをあんなに作って…\n"
		.string "バイルは何するつもりだったのかしら$"
	.endif

Text_System_CielGoodluck_12: @ 0x083779AE
	@ EN: Zero... Thank you. / I'm analyzing all of / the data you / recovered for us. / We may be able to / figure out what Weil / is attempting to do, / by analyzing past / data. / I'll do my best.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... Thank you.▼"
		.string "I'm analyzing all of\n"
		.string "the data you\n"
		.string "recovered for us.▼"
		.string "We may be able to\n"
		.string "figure out what Weil\n"
		.string "is attempting to do,▼"
		.string "by analyzing past\n"
		.string "data.▼"
		.string "I'll do my best.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…ありがとう…▼"
		.string "カイシュウしてくれたデータは\n"
		.string "今、全力で\n"
		.string "ブンセキをしているわ…▼"
		.string "過去のデータを\n"
		.string "ブンセキすることで…▼"
		.string "バイルが今、\n"
		.string "何をしようとしているか…\n"
		.string "わかるかもしれない▼"
		.string "わたしも…がんばるから…ね$"
	.endif

Text_System_CielGoodluck_13: @ 0x08377A21
	@ EN: Zero... Thank you. / I'm analyzing all of / the data you / recovered for us. / We may be able to / figure out what Weil / is attempting to do, / by analyzing past / data. / I'll do my best.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero... Thank you.▼"
		.string "I'm analyzing all of\n"
		.string "the data you\n"
		.string "recovered for us.▼"
		.string "We may be able to\n"
		.string "figure out what Weil\n"
		.string "is attempting to do,▼"
		.string "by analyzing past\n"
		.string "data.▼"
		.string "I'll do my best.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…ありがとう…▼"
		.string "カイシュウしてくれたデータは\n"
		.string "今、全力で\n"
		.string "ブンセキにかけてるわ…▼"
		.string "過去のデータを\n"
		.string "ブンセキすることで…▼"
		.string "バイルが今、\n"
		.string "何をしようとしているか…\n"
		.string "わかるかもしれない▼"
		.string "わたしも…がんばるから…ね…$"
	.endif

Text_System_ThankYouZeroItLooks: @ 0x08377A95
	@ EN: Thank you, Zero. / It looks like that / elevator was being / used to carry mass / amounts of / E-Crystals. / But, I wonder... / What was Weil up to / with all that / energy?
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Thank you, Zero.▼"
		.string "It looks like that\n"
		.string "elevator was being\n"
		.string "used to carry mass▼"
		.string "amounts of\n"
		.string "E-Crystals.▼"
		.string "But, I wonder...▼"
		.string "What was Weil up to\n"
		.string "with all that\n"
		.string "energy?$"
	.else
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "あのエレベーターは、\n"
		.string "Eクリスタルをたいりょうに\n"
		.string "はこんでいたみたい…▼"
		.string "でも、いったい……▼"
		.string "あんなにエネルギーを集めて…\n"
		.string "バイルは何するつもりだったのかしら$"
	.endif

Text_System_ZeroItSGreatTo: @ 0x08377AF2
	@ EN: Zero, it's great to / see you back safe. / X just sent us some / new coordinates. / Apparently, they / indicate where / Weil and Omega are. / This may be the last / battle... / Come talk to me when / you are ready.
	.if ENGLISH
	.string "{WINDOW 0x40}"
		.string "Zero, it's great to\n"
		.string "see you back safe.▼"
		.string "X just sent us some\n"
		.string "new coordinates.▼"
		.string "Apparently, they\n"
		.string "indicate where\n"
		.string "Weil and Omega are.▼"
		.string "This may be the last\n"
		.string "battle...▼"
		.string "Come talk to me when\n"
		.string "you are ready.$"
	.else
	.string "{WINDOW 0x40}"
		.string "ゼロ…無事でよかった…▼"
		.string "さっきエックスから\n"
		.string "新しいザヒョウがおくられてきたの▼"
		.string "どうやらそこに\n"
		.string "バイルとオメガがいるみたい…▼"
		.string "これが最後の戦いに\n"
		.string "なるかもしれない……▼"
		.string "ジュンビができたら\n"
		.string "声をかけてね…$"
	.endif

@ セルヴォ
Text_System_WhatWillItBe: @ 0x08377B60
	@ EN: What will it be? / Secret Disk / Talk
	.if ENGLISH
	.string "{WINDOW 0x43}"
		.string "What will it be?\n"
		.string "  Secret Disk\n"
		.string "  Talk$"
	.else
	.string "{WINDOW 0x43}"
		.string "なんのようかな？\n"
		.string "  シークレットディスクのカイセキ\n"
		.string "  話をする$"
	.endif

@ コンピュータ
Text_System_BootCompleted: @ 0x08377B85
	@ EN: Boot completed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Boot completed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "キドウシマシタ$"
	.endif

Text_System_EnterCommand: @ 0x08377B8F
	@ EN: Enter command. / Look something up / Transmission
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Enter command.\n"
		.string "  Look something up\n"
		.string "  Transmission$"
	.else
	.string "{WINDOW 0x02}"
		.string "コマンド ヲ センタク シテ クダサイ\n"
		.string "  何かをしらべる\n"
		.string "  通信する$"
	.endif

Text_System_CanTradeBattlechipsW: @ 0x08377BB9
	@ EN: Can trade BattleChips w /  / "MMBN 4 Red Sun" and / "MMBN 4 Blue Moon." / Send BattleChips to / "MMZ 3" to change / enemies in Cyberspace. / Begin transmission by / selecting "BattleChips" from / "Trade" in "Comm." / on the PET screen of "Mega / Man Battle Network 4."
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Can trade BattleChips w/\n"
		.string "{0xE9}MMBN 4  Red Sun{0xE9} and\n"
		.string "{0xE9}MMBN 4  Blue Moon.{0xE9}▼"
		.string "Send BattleChips to\n"
		.string "{0xE9}MMZ 3{0xE9} to change\n"
		.string "enemies in Cyberspace.▼"
		.string "Begin transmission by\n"
		.string "selecting {0xE9}BattleChips{0xE9} from\n"
		.string "{0xE9}Trade{0xE9} in {0xE9}Comm.{0xE9}▼"
		.string "on the PET screen of {0xE9}Mega\n"
		.string "Man Battle Network 4.{0xE9}$"
	.else
	.string "{WINDOW 0x02}"
		.string "「ロックマンエグゼ4 レッドサン」\n"
		.string "「ロックマンエグゼ4 ブルームーン」 ト\n"
		.string "バトルチップ トレード ガ デキマス▼"
		.string "「ロックマンゼロ3」 ニ バトルチップ ヲ オクル ト\n"
		.string "サイバークウカン ノ テキ ガ ヘンカ シマス▼"
		.string "「ロックマンエグゼ4」 デ PETガメン ニ ハイリ\n"
		.string "「つうしん」 ノ 「トレード」 カラ\n"
		.string "「バトルチップ」 ヲ センタク シテ 通信シテクダサイ$"
	.endif

Text_System_BeginTransmission: @ 0x08377C75
	@ EN: Begin transmission? / YES / NO
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Begin transmission?\n"
		.string "  YES\n"
		.string "  NO$"
	.else
	.string "{WINDOW 0x02}"
		.string "通信ヲ カイシ シマスカ？\n"
		.string "  はい\n"
		.string "  いいえ$"
	.endif

Text_System_WaitingForTransmission: @ 0x08377C92
	@ EN: Waiting for transmission. /  / (Cancel with the B BUTTON)
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Waiting for transmission.\n"
		.string "\n"
		.string "(Cancel with the B BUTTON)$"
	.else
	.string "{WINDOW 0x02}"
		.string "通信タイキ中デス\n"
		.string "\n"
		.string "(Bボタン デ キャンセル デキマス)$"
	.endif

Text_System_CommunicatingWith: @ 0x08377CB5
	@ EN: Communicating with / MMBN 4. Enter / commands from MMBN 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Communicating with\n"
		.string "MMBN 4. Enter\n"
		.string "commands from MMBN 4.$"
	.else
	.string "{WINDOW 0x02}"
		.string "ロックマンエグゼ4 ト 通信中デス\n"
		.string "ロックマンエグゼ4 ガワ デ ソウサ シテ クダサイ$"
	.endif

Text_System_TransmissionError: @ 0x08377CE7
	@ EN: Transmission error. / Ending transmission.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Transmission error.\n"
		.string "Ending transmission.$"
	.else
	.string "{WINDOW 0x02}"
		.string "通信エラー デス\n"
		.string "通信ヲ シュウリョウ シマス$"
	.endif

Text_System_TransmissionComplete: @ 0x08377D05
	@ EN: Transmission complete. / Cyberspace has changed!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Transmission complete.\n"
		.string "Cyberspace has changed!$"
	.else
	.string "{WINDOW 0x02}"
		.string "通信カンリョウ\n"
		.string "サイバークウカン ガ ヘンカ シマシタ！$"
	.endif

Text_System_TransmissionComplete_2: @ 0x08377D26
	@ EN: Transmission complete.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "Transmission complete.$"
	.else
	.string "{WINDOW 0x02}"
		.string "通信カンリョウ$"
	.endif

@ 改造カード
Text_System_MegaBoosterCardReceived: @ 0x08377D32
Text_System_MegaBoosterCardReceived_Alias1: @ 0x08377D32
Text_System_MegaBoosterCardReceived_Alias2: @ 0x08377D32
Text_System_MegaBoosterCardReceived_Alias3: @ 0x08377D32
	@ EN: Mega Booster Card received. / BOOST UP / CANCEL
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Mega Booster Card received.\n"
		.string "  BOOST UP\n"
		.string "  CANCEL$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}改造カードをじゅしんしました\n"
		.string "  改造じっこう\n"
		.string "  やめておく$"
	.endif

Text_System_TransmissionError_2: @ 0x08377D59
	@ EN: Transmission error.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Transmission error.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}通信エラーです$"
	.endif

Text_System_CardBoostReverted: @ 0x08377D66
	@ EN: Card boost reverted / to previous state.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Card{VARIABLE} boost reverted\n"
		.string "to previous state.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}カード{VARIABLE}の改造を もとにもどしました$"
	.endif

Text_System_TitleBackgroundPicture: @ 0x08377D7E
Text_System_TitleBackgroundPicture_Alias1: @ 0x08377D7E
Text_System_TitleBackgroundPicture_Alias2: @ 0x08377D7E
Text_System_TitleBackgroundPicture_Alias3: @ 0x08377D7E
	@ EN: Title background picture / has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Title background picture\n"
		.string "has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}タイトルバックのえが\n"
		.string "ちがうものに かわりました$"
	.endif

Text_System_PottedPlantAddedTo: @ 0x08377D9A
	@ EN: Potted plant added to / Resistance Base, somewhere.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Potted plant added to\n"
		.string "Resistance Base, somewhere.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "はちうえが おかれました$"
	.endif

Text_System_DesignOfElevatorIn: @ 0x08377DB9
	@ EN: Design of elevator in / Resistance Base changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Design of elevator in\n"
		.string "Resistance Base changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのエレベーターの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_3: @ 0x08377DDB
	@ EN: Attack of Z Saber increased / by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Z Saber increased\n"
		.string "by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_PHunterEnergy: @ 0x08377E01
	@ EN: P. Hunter energy / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}P. Hunter energy\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ハンターの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_PGuardianEnergy: @ 0x08377E1E
	@ EN: P. Guardian energy / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}P. Guardian energy\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ガーディアンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_DesignOfNurseElvesHas: @ 0x08377E3D
	@ EN: Design of Nurse elves has / changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Design of Nurse elves has\n"
		.string "changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ナース系エルフの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_7: @ 0x08377E57
	@ EN: You have a new friend some- / where on the second floor / of the Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}You have a new friend some-\n"
		.string "where on the second floor\n"
		.string "of the Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの2かいの\n"
		.string "どこかに 仲間が ふえました$"
	.endif

Text_System_TheDesignOfBustershot: @ 0x08377E7A
	@ EN: The design of BusterShot / bullets has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of BusterShot\n"
		.string "bullets has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのタマの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_TheDesignOfTheZ: @ 0x08377E97
	@ EN: The design of the Z Panels / in the game has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of the Z Panels\n"
		.string "in the game has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゲーム中に出現するZパネルの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_TheDesignOfAlouetteS: @ 0x08377EB9
	@ EN: The design of Alouette's / clothing has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of Alouette's\n"
		.string "clothing has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アルエットのきている ふくの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_11: @ 0x08377ED8
	@ EN: Attack of Animal elves / Archim and Archil have / increased by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Archim and Archil have\n"
		.string "increased by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_ZeroSDefenseIsNow: @ 0x08377F0B
	@ EN: Zero's Defense is now / doubled.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Zero's Defense is now\n"
		.string "doubled.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼロのボウギョりょくが\n"
		.string "つうじょう時の2倍になりました$"
	.endif

Text_System_TheDesignOfTheMessage: @ 0x08377F2C
	@ EN: The design of the message / window has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of the message\n"
		.string "window has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}メッセージウィンドウの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_TheDesignOfLifeEnergy: @ 0x08377F48
	@ EN: The design of Life Energy / has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of Life Energy\n"
		.string "has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ライフエネルギーの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_18: @ 0x08377F62
	@ EN: Attack of Recoil Rod has / increased by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Recoil Rod has\n"
		.string "increased by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_AllBoostedItemsHave: @ 0x08377F88
	@ EN: All boosted items have / been reset to default.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}All boosted items have\n"
		.string "been reset to default.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}これまで改造したものを\n"
		.string "すべて リセットしました$"
	.endif

Text_System_ThereIsALostCat: @ 0x08377FA6
	@ EN: There is a lost cat / somewhere in the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}There is a lost cat\n"
		.string "somewhere in the\n"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "ネコが まよいこみました$"
	.endif

Text_System_ItIsSnowingAtThe: @ 0x08377FC5
	@ EN: It is snowing at the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}It is snowing at the\n"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースに\n"
		.string "ユキが ふってきました$"
	.endif

Text_System_TheDesignOfThe: @ 0x08377FDF
	@ EN: The design of the / E-Crystals in the / game has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of the\n"
		.string "E-Crystals in the\n"
		.string "game has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゲーム中に出現する\n"
		.string "Eクリスタルの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_23: @ 0x08378004
	@ EN: Attack of S.Boomerang / has increased by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of S.Boomerang\n"
		.string "has increased by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_ModCard_24: @ 0x0837802D
	@ EN: Attack of Animal elves / Beetack and Beenipe have / increased by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Beetack and Beenipe have\n"
		.string "increased by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_DesignOfComputerIn: @ 0x08378062
	@ EN: Design of computer in / Ciel's room has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Design of computer in\n"
		.string "Ciel's room has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シエルのへやのコンピューターの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_AMysteriousCyberElfHas: @ 0x08378082
	@ EN: A mysterious Cyber-elf has / appeared somewhere in the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}A mysterious Cyber-elf has\n"
		.string "appeared somewhere in the\n"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "なぞのサイバーエルフが現れました$"
	.endif

Text_System_ModCard_27: @ 0x083780A6
	@ EN: The Attack of BusterShots / has increased by 1.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The Attack of BusterShots\n"
		.string "has increased by {RED}1{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"
	.endif

Text_System_APaintingHasBeenHung: @ 0x083780CD
	@ EN: A painting has been hung / from the Resistance Base / wall.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}A painting has been hung\n"
		.string "from the Resistance Base\n"
		.string "wall.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのかべに\n"
		.string "カイガが かけられました$"
	.endif

Text_System_ANewDoorHasAppeared: @ 0x083780EB
	@ EN: A new door has appeared / somewhere in the Resistance / Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}A new door has appeared\n"
		.string "somewhere in the Resistance\n"
		.string "Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "新しくトビラが出現しました$"
	.endif

Text_System_ModCard_30: @ 0x0837810E
	@ EN: The Attack of BusterShots / has increased by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The Attack of BusterShots\n"
		.string "has increased by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_ModCard_31: @ 0x08378135
	@ EN: You have a new friend some- / where on the first floor / of the Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}You have a new friend some-\n"
		.string "where on the first floor\n"
		.string "of the Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの1かいの\n"
		.string "どこかに 仲間が ふえました$"
	.endif

Text_System_AFlowerHasBloomedOn: @ 0x08378158
	@ EN: A flower has bloomed on the / Resistance Base roof.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}A flower has bloomed on the\n"
		.string "Resistance Base roof.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのおくじょうに\n"
		.string "はなが さきました$"
	.endif

Text_System_TheDesignOfAnimalElves: @ 0x08378176
	@ EN: The design of Animal elves / has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of Animal elves\n"
		.string "has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_AndrewLooksYoungerNow: @ 0x08378191
	@ EN: Andrew looks younger now.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Andrew looks younger now.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アンドリューのすがたが\n"
		.string "わかがえりました$"
	.endif

Text_System_ModCard_38: @ 0x083781A9
	@ EN: Attack of Animal elves / Archim and Archil have / increased by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Archim and Archil have\n"
		.string "increased by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_SeagullsNowFlyInThe: @ 0x083781DC
	@ EN: Seagulls now fly in the sky / above the Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Seagulls now fly in the sky\n"
		.string "above the Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのそらに\n"
		.string "カモメが やってきました$"
	.endif

Text_System_ModCard_41: @ 0x083781FA
	@ EN: Attack of Animal elves / Beetack and Beenipe have / increased by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Beetack and Beenipe have\n"
		.string "increased by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_TheDesignOfSecretDisks: @ 0x0837822F
	@ EN: The design of Secret Disks / has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of Secret Disks\n"
		.string "has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シークレットディスクの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_ModCard_43: @ 0x0837824B
	@ EN: Attack of S.Boomerang / has increased by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of S.Boomerang\n"
		.string "has increased by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_SomebodyHasDrawnGraffiti: @ 0x08378274
	@ EN: Somebody has drawn graffiti / on the Resistance Base / wall.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Somebody has drawn graffiti\n"
		.string "on the Resistance Base\n"
		.string "wall.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのかべに\n"
		.string "だれかが ラクガキしました$"
	.endif

Text_System_ModCard_48: @ 0x08378293
	@ EN: Attack of Recoil Rod has / increased by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Recoil Rod has\n"
		.string "increased by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_ModCard_52: @ 0x083782B9
	@ EN: The conversation with the / Resistance fighter in the / watchtower at the right / side of the base has / changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The conversation with the\n"
		.string "Resistance fighter in the\n"
		.string "watchtower at the right▼"
		.string "side of the base has\n"
		.string "changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの右の\n"
		.string "カンシトウにいるレジスタンスの\n"
		.string "会話のナイヨウが かわりました$"
	.endif

Text_System_ModCard_60: @ 0x083782EC
	@ EN: Attack of S.Boomerang / has increased by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of S.Boomerang\n"
		.string "has increased by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_ModCard_61: @ 0x08378315
	@ EN: The conversation with the / Resistance fighter in the / watchtower at the left / side of the base has / changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The conversation with the\n"
		.string "Resistance fighter in the\n"
		.string "watchtower at the left▼"
		.string "side of the base has\n"
		.string "changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの左の\n"
		.string "カンシトウにいるレジスタンスの\n"
		.string "会話のナイヨウが かわりました$"
	.endif

Text_System_ModCard_64: @ 0x08378348
	@ EN: Attack of Animal elves / Beetack and Beenipe have / increased by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Beetack and Beenipe have\n"
		.string "increased by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_ModCard_65: @ 0x0837837D
	@ EN: Attack of Animal elves / Archim and Archil have / increased by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Archim and Archil have\n"
		.string "increased by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_TheDesignOfHackerElves: @ 0x083783B0
	@ EN: The design of Hacker elves / has changed.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The design of Hacker elves\n"
		.string "has changed.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ハッカー系エルフの\n"
		.string "デザインが かわりました$"
	.endif

Text_System_EnergyOfCrossbyneHas: @ 0x083783CB
	@ EN: Energy of Crossbyne has / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Crossbyne has\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}クロスバインの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfPBase: @ 0x083783E4
	@ EN: Energy of P. Base / has increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of P. Base\n"
		.string "has increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ベースの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_ModCard_69: @ 0x08378400
	@ EN: The Attack of BusterShots / has increased by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}The Attack of BusterShots\n"
		.string "has increased by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_ItIsNowNighttimeAt: @ 0x08378427
	@ EN: It is now nighttime at the / Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}It is now nighttime at the\n"
		.string "Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースが\n"
		.string "よるに なりました$"
	.endif

Text_System_EnergyOfPAqua: @ 0x0837843F
	@ EN: Energy of P. Aqua / has increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of P. Aqua\n"
		.string "has increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・アクアの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_FishNowJumpAroundThe: @ 0x0837845B
	@ EN: Fish now jump around the / Resistance Base harbor.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Fish now jump around the\n"
		.string "Resistance Base harbor.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのミナトで\n"
		.string "サカナが はねるようになりました$"
	.endif

Text_System_ModCard_78: @ 0x0837847E
	@ EN: Attack of Recoil Rod has / increased by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Recoil Rod has\n"
		.string "increased by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_ModCard_79: @ 0x083784A4
	@ EN: You have a new friend some- / where on the third floor / of the Resistance Base.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}You have a new friend some-\n"
		.string "where on the third floor\n"
		.string "of the Resistance Base.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの3かいの\n"
		.string "どこかに 仲間が ふえました$"
	.endif

Text_System_ModCard_81: @ 0x083784C7
	@ EN: Attack of Animal elves / Archim and Archil have / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Animal elves\n"
		.string "Archim and Archil have\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}4{RED_END}ふえました$"
	.endif

Text_System_ModCard_82: @ 0x083784FA
	@ EN: Attack of Z Saber increased / by 2.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Z Saber increased\n"
		.string "by {RED}2{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"
	.endif

Text_System_EnergyOfPBomber: @ 0x08378520
	@ EN: Energy of P. Bomber / has increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of P. Bomber\n"
		.string "has increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ボマーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfAlteredP: @ 0x0837853C
	@ EN: Energy of altered P. / Aqua has increased by / 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of altered P.\n"
		.string "Aqua has increased by\n"
		.string "{RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}かいぞうパンテオン・アクアの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_ModCard_90: @ 0x0837855D
	@ EN: Attack of Z Saber increased / by 3.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Attack of Z Saber increased\n"
		.string "by {RED}3{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"
	.endif

Text_System_EnergyOfPurplenerple: @ 0x08378583
	@ EN: Energy of PurpleNerple / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of PurpleNerple\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パープルナープルの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfShellcrawler: @ 0x0837859E
	@ EN: Energy of Shellcrawler / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Shellcrawler\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シェルクローラーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfIcebonIncreased: @ 0x083785B9
	@ EN: Energy of Icebon increased / by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Icebon increased\n"
		.string "by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アイスボンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfGCannon: @ 0x083785D1
	@ EN: Energy of G. Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of G. Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ジェネレーターキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfClaveker: @ 0x083785EF
	@ EN: Energy of Claveker / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Claveker\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}クラベッガーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfShotcounter: @ 0x08378608
	@ EN: Energy of Shotcounter / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Shotcounter\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シャットカウンターの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfGrandCannon: @ 0x08378624
	@ EN: Energy of Grand Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Grand Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}グランドキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfShrimpolin: @ 0x0837863F
	@ EN: Energy of Shrimpolin / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Shrimpolin\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シュリンポリンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfBatring: @ 0x08378659
	@ EN: Energy of Batring / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Batring\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バットンリングの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfPCannon: @ 0x08378673
	@ EN: Energy of P. Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of P. Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ピラーキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfVolcaire: @ 0x0837868D
	@ EN: Energy of Volcaire / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Volcaire\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ヴォルケールの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfSnakecord: @ 0x083786A6
	@ EN: Energy of Snakecord / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Snakecord\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}スネーケーブルの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfLemmingles: @ 0x083786C0
	@ EN: Energy of Lemmingles / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Lemmingles\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レミングルスの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfLamplort: @ 0x083786D9
	@ EN: Energy of Lamplort / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Lamplort\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ランプロートの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfTileCannon: @ 0x083786F2
	@ EN: Energy of Tile Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Tile Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}タイルキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfShelluno: @ 0x0837870C
	@ EN: Energy of Shelluno / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Shelluno\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シェルーノーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfHeavyCannon: @ 0x08378725
	@ EN: Energy of Heavy Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Heavy Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ヘビーキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfMothjiro: @ 0x0837873F
	@ EN: Energy of Mothjiro / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Mothjiro\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}モスジーロの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfCCannon: @ 0x08378757
	@ EN: Energy of C. Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of C. Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}カプセルキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfCalibeeG: @ 0x08378772
	@ EN: Energy of Calibee G / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Calibee G\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}キャリビーGの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_EnergyOfDeathlock: @ 0x0837878C
	@ EN: Energy of Deathlock / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Deathlock\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ダスロックの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfGyroCannon: @ 0x083787A4
	@ EN: Energy of Gyro Cannon / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Gyro Cannon\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ジャイロキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfSharkshielX: @ 0x083787BF
	@ EN: Energy of Sharkshiel X / increased by 4.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Sharkshiel X\n"
		.string "increased by {RED}4{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シャークシールXの体力が\n"
		.string "{RED}4{RED_END}ふえました$"
	.endif

Text_System_EnergyOfOlwarmer: @ 0x083787DA
	@ EN: Energy of Olwarmer / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Olwarmer\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}オールワーマーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_EnergyOfBranwarmer: @ 0x083787F5
	@ EN: Energy of Branwarmer / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Branwarmer\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ブランワーマーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_EnergyOfLocomoIf: @ 0x08378810
	@ EN: Energy of Locomo IF / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Locomo IF\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ロコモIFの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_EnergyOfBeeserver: @ 0x08378829
	@ EN: Energy of Beeserver / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Beeserver\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ビーサーバーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_EnergyOfMegamilpa: @ 0x08378843
	@ EN: Energy of Megamilpa / increased by 16.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}Energy of Megamilpa\n"
		.string "increased by {RED}16{RED_END}.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}メガミルパの体力が\n"
		.string "{RED}16{RED_END}ふえました$"
	.endif

Text_System_ZeroSMiniGame: @ 0x0837885C
Text_System_ZeroSMiniGame_Alias1: @ 0x0837885C
Text_System_ZeroSMiniGame_Alias2: @ 0x0837885C
Text_System_ZeroSMiniGame_Alias3: @ 0x0837885C
	@ EN: Zero's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Zero's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ゼロ{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_CielSMiniGame: @ 0x08378874
	@ EN: Ciel's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Ciel's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}シエル{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_CopyXSMiniGame: @ 0x0837888D
	@ EN: Copy X's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Copy X's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}コピーエックス{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_HarpuiaSMiniGame: @ 0x083788AA
	@ EN: Harpuia's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Harpuia's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ハルピュイア{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_FefnirSMiniGame: @ 0x083788C6
	@ EN: Fefnir's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Fefnir's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ファーブニル{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_LeviathanSMiniGame: @ 0x083788E2
	@ EN: Leviathan's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Leviathan's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}レヴィアタン{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_PhantomSMiniGame: @ 0x083788FE
	@ EN: Phantom's mini game / added!
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Phantom's{RED_END} mini game\n"
		.string "added!$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ファントム{RED_END}のミニゲームが ツイカされました$"
	.endif

Text_System_HardModeAddedPlayIn: @ 0x08378919
	@ EN: Hard Mode added! / Play in Hard Mode by / holding the L BUTTON down / while selecting NEW GAME.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Hard Mode{RED_END} added!▼"
		.string "Play in Hard Mode by\n"
		.string "holding the L BUTTON down\n"
		.string "while selecting NEW GAME.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ハードモード{RED_END}が ツイカされました▼"
		.string "Lボタンをおしながら\n"
		.string "「はじめから」をせんたくすると\n"
		.string "ハードモードでプレイすることができます$"
	.endif

Text_System_UltimateModeAddedPlayIn: @ 0x0837895E
	@ EN: Ultimate Mode added! / Play in Ultimate Mode by / holding the R BUTTON down / while selecting NEW GAME.
	.if ENGLISH
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}Ultimate Mode{RED_END} added!▼"
		.string "Play in Ultimate Mode by\n"
		.string "holding the R BUTTON down\n"
		.string "while selecting NEW GAME.$"
	.else
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}アルティメットモード{RED_END}が ツイカされました▼"
		.string "Rボタンをおしながら\n"
		.string "「はじめから」をせんたくすると\n"
		.string "アルティメットモードでプレイすることができます$"
	.endif

.balign 4, 0
