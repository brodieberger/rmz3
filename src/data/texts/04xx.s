.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_Volcano:: @ 0x0837fb30
  .2byte (Text_Volcano_StrongEnergyReading-Start), (Text_Volcano_IAlmostGaveUpOn-Start), (Text_Volcano_IAlmostGaveUpOn_2-Start), (Text_Volcano_SsyaaaaahGetReadyFor-Start)
  .2byte (Text_Volcano_WhatIsThatAll-Start), (Text_Volcano_WhoAreYouToPut-Start)

Text_Volcano:: @ 0x0837fb3c
Start:

Text_Volcano_StrongEnergyReading: @ 0x0837FB3C
	@ EN: Operator: / A strong energy / reading detected. / They are building / a huge missile / outside the base. / The base must be / here to support the / construction. / Ciel: / Analyzing a route to / the missile factory / will take quite a / while... Zero, what / should we do?! / All right. I'll / buy us some time by / attacking the base. / Start your analysis!
	.if ENGLISH
	.string "{WINDOW 0x64}"
		.string "Operator:\n"
		.string "A strong energy\n"
		.string "reading detected.▼"
		.string "They are building\n"
		.string "a huge missile\n"
		.string "outside the base.▼"
		.string "The base must be\n"
		.string "here to support the\n"
		.string "construction.▼"
		.string "Ciel:\n"
		.string "Analyzing a route to\n"
		.string "the missile factory▼"
		.string "will take quite a\n"
		.string "while... Zero, what\n"
		.string "should we do?!▼"
	.string "{WINDOW 0x04}"
		.string "All right. I'll\n"
		.string "buy us some time by\n"
		.string "attacking the base.▼"
		.string "Start your analysis!$"
	.else
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「ただいま強力な\n"
		.string " エネルギーはんのうをカクニン▼"
		.string "「基地の近くで巨大なミサイルを\n"
		.string " ケンゾウ中のようです▼"
		.string "「この基地はミサイルのケンゾウを\n"
		.string " サポートしている基地だと\n"
		.string " 思われます▼"
		.string "シエル:\n"
		.string "「ミサイル工場への\n"
		.string " 転送ルートかいせきは▼"
		.string "「かなり時間がかかりそうなの…\n"
		.string " どうしよう…ゼロ！▼"
	.string "{WINDOW 0x04}"
		.string "わかった…\n"
		.string "この基地をコウゲキして\n"
		.string "時間をかせぐ…▼"
		.string "カイセキは まかせたぞ$"
	.endif

Text_Volcano_IAlmostGaveUpOn: @ 0x0837FC15
Text_Volcano_IAlmostGaveUpOn_2:
	@ EN: I almost gave up on / finding a foe worthy / of fighting me... / You look like you / might at least be a / minor challenge. / I'm gonna enjoy / this, Zero!
	.if ENGLISH
	.string "{WINDOW 0x17}"
		.string "I almost gave up on\n"
		.string "finding a foe worthy\n"
		.string "of fighting me...▼"
		.string "You look like you\n"
		.string "might at least be a\n"
		.string "minor challenge.▼"
		.string "I'm gonna enjoy\n"
		.string "this, Zero!$"
	.else
	.string "{WINDOW 0x17}"
		.string "たよりないザコどもを\n"
		.string "まとめるのに…しょうじき\n"
		.string "あきていたところだが…▼"
		.string "オマエなら\n"
		.string "少しは、たのしめそうだ…▼"
		.string "かんげいするぜ！\n"
		.string "ゼロォッ！$"
	.endif

Text_Volcano_SsyaaaaahGetReadyFor: @ 0x0837FC5E
	@ EN: Ssyaaaaah! / Get ready for / Blazin' Flizard, one / of Weil's Numbers! / Let's heat it up, / Zerrroooo!!!
	.if ENGLISH
	.string "{WINDOW 0x07}"
		.string "Ssyaaaaah!▼"
		.string "Get ready for\n"
		.string "Blazin' Flizard, one\n"
		.string "of Weil's Numbers!▼"
		.string "Let's heat it up,\n"
		.string "Zerrroooo!!!$"
	.else
	.string "{WINDOW 0x07}"
		.string "シャハアァァァッ！▼"
		.string "バイル・ナンバーズがひとり！\n"
		.string "オレの名は\n"
		.string "ブレイジン・フリザード！▼"
		.string "オレをあつくしてくれ！\n"
		.string "ゼェロォォォッッ！$"
	.endif

Text_Volcano_WhatIsThatAll: @ 0x0837FCA3
	@ EN: What, is that all / you got? / How...tepid. And I / was hoping to have a / little fun, too. / Ssyahahah!
	.if ENGLISH
	.string "{WINDOW 0x06}"
		.string "What, is that all\n"
		.string "you got?▼"
		.string "How...tepid. And I\n"
		.string "was hoping to have a\n"
		.string "little fun, too.▼"
		.string "Ssyahahah!$"
	.else
	.string "{WINDOW 0x06}"
		.string "もうおしまいか！？▼"
		.string "さめちまうなぁ！\n"
		.string "ひまつぶしにもならんかぁ！▼"
		.string "シャハァーッハッハッハァ！$"
	.endif

Text_Volcano_WhoAreYouToPut: @ 0x0837FCD4
	@ EN: Who are you to...put / out my flames? / Lord Weil will get / you, though... Make / no mistake... / He'll cover the / whole world in / flames, you'll see. / You can't...put out / the flames...of our / new world... / Ssyah...aaaarrgh!
	.if ENGLISH
	.string "{WINDOW 0x06}"
		.string "Who are you to...put\n"
		.string "out my flames?▼"
		.string "Lord Weil will get\n"
		.string "you, though... Make\n"
		.string "no mistake...▼"
		.string "He'll cover the\n"
		.string "whole world in\n"
		.string "flames, you'll see.▼"
		.string "You can't...put out\n"
		.string "the flames...of our\n"
		.string "new world...▼"
		.string "Ssyah...aaaarrgh!$"
	.else
	.string "{WINDOW 0x06}"
		.string "オレのホノオを…かき消すとは…！\n"
		.string "なんて…ヤツ…だっ▼"
		.string "しかし…かならず…\n"
		.string "バイルさまが…▼"
		.string "世界を…ホノオに……\n"
		.string "つつんでくださる…はずだ▼"
		.string "オマエに…\n"
		.string "われらの…新たなる世界の\n"
		.string "ホノオを消すことは…できん…▼"
		.string "シャ…ギャハアアァァァァッ！$"
	.endif

.balign 4, 0
