.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_EnergyFactory:: @ 0x08381364
  .2byte Text_EnergyFactory_FacilityCore-Start, Text_EnergyFactory_WhatSThis-Start, Text_EnergyFactory_TeeheeheeHeyYouWerenT-Start, Text_EnergyFactory_IAmCubitFoxtar-Start
  .2byte Text_EnergyFactory_TeeheeThatSIt-Start, Text_EnergyFactory_IfIAmDefeated-Start

Texts_EnergyFactory:: @ 0x08381370
Start:

Text_EnergyFactory_FacilityCore: @ 0x08381370
	@ EN: Operator: / The facility's core / has not yet been / activated. / We'll need to / activate the core / and reestablish / facility opera- / tions to get into / the deeper areas.
	.if ENGLISH
	.string "{WINDOW 0x64}"
		.string "Operator:\n"
		.string "The facility's core\n"
		.string "has not yet been▼"
		.string "activated.▼"
		.string "We'll need to\n"
		.string "activate the core\n"
		.string "and reestablish▼"
		.string "facility opera-\n"
		.string "tions to get into\n"
		.string "the deeper areas.$"
	.else
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「現在、シセツのロシンは\n"
		.string " キドウしてないモヨウです▼"
		.string "「おくのエリアに行くには、\n"
		.string " ロシンを動かしてシセツのキノウを\n"
		.string " とりもどすヒツヨウがあります$"
	.endif

Text_EnergyFactory_WhatSThis: @ 0x083813C9
	@ EN: What's this?
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "What's this?$"
	.else
	.string "{WINDOW 0x04}"
		.string "これは…？$"
	.endif

Text_EnergyFactory_TeeheeheeHeyYouWerenT: @ 0x083813D1
	@ EN: Teeheehee... / Hey! You weren't / supposed to see / this place. / ... / This is a Dark Elf / copy factory. / We've got copies of / the Dark Elf / sleeping here. / In other words, / Baby Elves. / We had the factory / sealed off so / nobody'd get / suspicious. Now / you've done it! / I'll have to ensure / you remain silent / about this... / ...For-e-ver!
	.if ENGLISH
	.string "{WINDOW 0x1F}"
		.string "Teeheehee...▼"
		.string "Hey! You weren't\n"
		.string "supposed to see\n"
		.string "this place.▼"
	.string "{WINDOW 0x04}"
		.string "...▼"
	.string "{WINDOW 0x1F}"
		.string "This is a Dark Elf\n"
		.string "copy factory.▼"
		.string "We've got copies of\n"
		.string "the Dark Elf\n"
		.string "sleeping here.▼"
		.string "In other words,\n"
		.string "Baby Elves.▼"
		.string "We had the factory\n"
		.string "sealed off so\n"
		.string "nobody'd get▼"
		.string "suspicious. Now\n"
		.string "you've done it!▼"
		.string "I'll have to ensure\n"
		.string "you remain silent\n"
		.string "about this...▼"
		.string "...For-e-ver!$"
	.else
	.string "{WINDOW 0x1F}"
		.string "ホホホホホッ…▼"
		.string "あらあら！\n"
		.string "見てはいけないものを\n"
		.string "見ちゃったのねぇ…▼"
	.string "{WINDOW 0x04}"
		.string "………▼"
	.string "{WINDOW 0x1F}"
		.string "ここはダークエルフのコピー工場…▼"
		.string "ここにねむっているのは、\n"
		.string "ダークエルフのコピー…\n"
		.string "つまり…ベビーエルフたちなのよ▼"
		.string "あやしまれないよう、\n"
		.string "工場をヘイサしていたのに…\n"
		.string "いけない人ねぇ▼"
		.string "見られてしまったからには\n"
		.string "だまっていてもらうわね▼"
		.string "え い え ん…に！$"
	.endif

Text_EnergyFactory_IAmCubitFoxtar: @ 0x08381483
	@ EN: I am Cubit Foxtar, / member of Weil's / Numbers! / I'll make sure you / never talk again!
	.if ENGLISH
	.string "{WINDOW 0x0F}"
		.string "I am Cubit Foxtar,\n"
		.string "member of Weil's\n"
		.string "Numbers!▼"
		.string "I'll make sure you\n"
		.string "never talk again!$"
	.else
	.string "{WINDOW 0x0F}"
		.string "わたしはバイル・ナンバーズがひとり\n"
		.string "キュービット・フォクスター！▼"
		.string "にどと 口がきけないように\n"
		.string "してやるわ！$"
	.endif

Text_EnergyFactory_TeeheeThatSIt: @ 0x083814BC
	@ EN: Teehee! That's it! / See what happens / to nosy people! / Relax! I'll show you / the way to the / afterlife.
	.if ENGLISH
	.string "{WINDOW 0x0E}"
		.string "Teehee! That's it!\n"
		.string "See what happens\n"
		.string "to nosy people!▼"
		.string "Relax! I'll show you\n"
		.string "the way to the\n"
		.string "afterlife.$"
	.else
	.string "{WINDOW 0x0E}"
		.string "ホーッホッホッ！ いいキミね！\n"
		.string "わたしたちのジャマをするから\n"
		.string "そうなるのよ！▼"
		.string "安心しなさい…！\n"
		.string "きちんとあの世へ あんない\n"
		.string "してあげるわ$"
	.endif

Text_EnergyFactory_IfIAmDefeated: @ 0x08381506
	@ EN: If I am defeated, / this room will cease / functioning, / and the copies will / all die... / There will be no / proof. Nobody will / know the truth. / And anyway... / We don't actually / need the Baby Elves. / The Dark Elf alone / will be enough to / take care of the / Reploids... / I can already see / it... The shining / future, the new / world Lord Weil is / about to create... / And I see...you, / wallowing in the / depths of despair! / Teeheeheeeeeee!
	.if ENGLISH
	.string "{WINDOW 0x0E}"
		.string "If I am defeated,\n"
		.string "this room will cease\n"
		.string "functioning,▼"
		.string "and the copies will\n"
		.string "all die...▼"
		.string "There will be no\n"
		.string "proof. Nobody will\n"
		.string "know the truth.▼"
		.string "And anyway...▼"
		.string "We don't actually\n"
		.string "need the Baby Elves.\n"
		.string "The Dark Elf alone▼"
		.string "will be enough to\n"
		.string "take care of the\n"
		.string "Reploids...▼"
		.string "I can already see\n"
		.string "it... The shining\n"
		.string "future, the new▼"
		.string "world Lord Weil is\n"
		.string "about to create...▼"
		.string "And I see...you,\n"
		.string "wallowing in the\n"
		.string "depths of despair!▼"
		.string "Teeheeheeeeeee!$"
	.else
	.string "{WINDOW 0x0E}"
		.string "わたしが たおされれば…\n"
		.string "このへやは キノウを うしなって…\n"
		.string "コピーたちも みんな死んでしまう…▼"
		.string "何も ショウコは のこらない…\n"
		.string "真実はダレにも 知られない…▼"
		.string "でもね…▼"
		.string "ベビーエルフなんかなくっても\n"
		.string "ダークエルフさえいれば\n"
		.string "レプリロイドたちを………▼"
		.string "ああ…見えますわ…\n"
		.string "バイルさまの作る…新しい世界…\n"
		.string "ひかる未来が…▼"
		.string "そして…やみの中で\n"
		.string "ブザマにもがく\n"
		.string "オマエのすがたもね！▼"
		.string "ホーッホッホッホッ！$"
	.endif

.balign 4, 0
