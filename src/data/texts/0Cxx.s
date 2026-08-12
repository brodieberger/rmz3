.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_AreaX2:: @ 0x08380d60
  .2byte (Text_AreaX2_Empty-Start), (Text_AreaX2_SoYouVeCome-Start), (Text_AreaX2_AhaAhahahahDidYouS-Start), (Text_AreaX2_NNoWhWhyWhy-Start)
  .2byte (Text_AreaX2_HeIsNoLongerHere-Start), (Text_AreaX2_WhoAAreYouX-Start), (Text_AreaX2_HaaaaahOhNoWeilHas-Start), (Text_AreaX2_GeeGagagaICanT-Start)
  .2byte (Text_AreaX2_WeilKnewFromThe-Start), (Text_AreaX2_HearMeCitizensOf-Start), (Text_AreaX2_DrWeil-Start), (Text_AreaX2_JustNowOurHeroMaster-Start)
  .2byte (Text_AreaX2_ThankYouAllI-Start), (Text_AreaX2_ItSAllGoing-Start), (Text_AreaX2_WhatIsItWellNever-Start), (Text_AreaX2_TheHeart-Start)

Texts_AreaX2:: @ 0x08380d80
Start:

Text_AreaX2_Empty: @ 0x08380d80
	.if ENGLISH
		.string "$"
	.else
	.string "$"
	.endif

Text_AreaX2_SoYouVeCome: @ 0x08380D81
	@ EN: So you've come, / Zero. / D-do you know what / you are doing? / Doing? / You are helping / extremists! / Why would a-a / legendary hero help / an evil army? / So you're saying / that we're an / evil army... / ...and you people / are fighting for / justice? / Exactly right. / Almost a-all / humans support our / cause. / All humans dream of / defeating th-the / extremists. / What value is there / in the justice that / complacent humans / seek? / Wh-who cares about / value? Neo Arcadia's / doing what's right. / That i-is enough / proof that what we / do is j-just!
	.if ENGLISH
	.string "{WINDOW 0x37}"
		.string "So you've come,\n"
		.string "Zero.▼"
		.string "D-do you know what\n"
		.string "you are doing?\n"
		.string "Doing?▼"
		.string "You are helping\n"
		.string "extremists!▼"
		.string "Why would a-a\n"
		.string "legendary hero help\n"
		.string "an evil army?▼"
	.string "{WINDOW 0x04}"
		.string "So you're saying\n"
		.string "that we're an\n"
		.string "evil army...▼"
		.string "...and you people\n"
		.string "are fighting for\n"
		.string "justice?▼"
	.string "{WINDOW 0x37}"
		.string "Exactly right.▼"
		.string "Almost a-all\n"
		.string "humans support our\n"
		.string "cause.▼"
		.string "All humans dream of\n"
		.string "defeating th-the\n"
		.string "extremists.▼"
	.string "{WINDOW 0x04}"
		.string "What value is there\n"
		.string "in the justice that▼"
		.string "complacent humans\n"
		.string "seek?▼"
	.string "{WINDOW 0x37}"
		.string "Wh-who cares about\n"
		.string "value? Neo Arcadia's\n"
		.string "doing what's right.▼"
		.string "That i-is enough\n"
		.string "proof that what we\n"
		.string "do is j-just!$"
	.else
	.string "{WINDOW 0x37}"
		.string "きたネ…ゼロ▼"
		.string "キミは 自分が\n"
		.string "何を シていルか\n"
		.string "ワかってイるのかい？▼"
		.string "テロリストのミカタだよ…？▼"
		.string "伝説のエイユウが\n"
		.string "悪の軍団の手助けを\n"
		.string "していルんだヨ？▼"
	.string "{WINDOW 0x04}"
		.string "オレたちが\n"
		.string "悪の軍団で…▼"
		.string "オマエたちは、\n"
		.string "セイギのみかた…\n"
		.string "ということか……▼"
	.string "{WINDOW 0x37}"
		.string "そのとオり▼"
		.string "ボクたちは、\n"
		.string "人間たちのアットウ的なシジを\n"
		.string "うけている……▼"
		.string "テロリストを たおすことは、\n"
		.string "カレら人間…みんなのユメなんだよ▼"
	.string "{WINDOW 0x04}"
		.string "かいならされた人間たちが\n"
		.string "のぞむセイギに……▼"
		.string "いったい何のカチが\n"
		.string "あるっていうんだ▼"
	.string "{WINDOW 0x37}"
		.string "カチなんて どうでもイいんダよ…\n"
		.string "ネオ・アルカディアの\n"
		.string "やっテいることは たダしい…▼"
		.string "そのセイギの ショウメイになれば\n"
		.string "それで いイのさ！$"
	.endif

Text_AreaX2_AhaAhahahahDidYouS: @ 0x08380EC8
	@ EN: Aha! Ahahahah! / Did you s-see that?! / I am the true hero!
	.if ENGLISH
	.string "{WINDOW 0x6E}"
		.string "Aha! Ahahahah!▼"
		.string "Did you s-see that?!\n"
		.string "I am the true hero!$"
	.else
	.string "{WINDOW 0x6E}"
		.string "あは！ アはハはハは！▼"
		.string "見タか！やっぱりボクは\n"
		.string "本当のエイユウなんダ！$"
	.endif

Text_AreaX2_NNoWhWhyWhy: @ 0x08380EF1
	@ EN: N-no! Wh-why-why?! / I'm a hero! I / f-fight for justice! / Weil! / Dr. Weil! / Use Omeg-Omega! / Crush him in your / h-hand!
	.if ENGLISH
	.string "{WINDOW 0x6F}"
		.string "N-no! Wh-why-why?!▼"
		.string "I'm a hero! I\n"
		.string "f-fight for justice!▼"
		.string "Weil!\n"
		.string "Dr. Weil!▼"
		.string "Use Omeg-Omega!\n"
		.string "Crush him in your\n"
		.string "h-hand!$"
	.else
	.string "{WINDOW 0x6F}"
		.string "くソっ…ナぜだ…！▼"
		.string "ボクは…ボクはセイギの\n"
		.string "エイユウなんダぞ…！▼"
		.string "バイル！\n"
		.string "ドクター・バイル！▼"
		.string "オメガを…オメガをだセ！\n"
		.string "コイツをひネりつぶセーッ！$"
	.endif

Text_AreaX2_HeIsNoLongerHere: @ 0x08380F3E
	@ EN: He is... / ...no longer here.
	.if ENGLISH
	.string "{WINDOW 0x34}"
		.string "He is...▼"
		.string "...no longer here.$"
	.else
	.string "{WINDOW 0x34}"
		.string "カレはもう…▼"
		.string "ここにはいないよ$"
	.endif

Text_AreaX2_WhoAAreYouX: @ 0x08380F50
	@ EN: Who a-are you?! / X! / X?! / Y-you are my / original form?! / Weil has moved to / another base. / With Omega... / Weil was using you / for his own purpose. / Gee...g-gee... / Everyone treats me / l-like a fool! / I-I won't stand for / it! Let me show you / my true power!
	.if ENGLISH
	.string "{WINDOW 0x6F}"
		.string "Who a-are you?!▼"
	.string "{WINDOW 0x04}"
		.string "X!▼"
	.string "{WINDOW 0x6F}"
		.string "X?!▼"
		.string "Y-you are my\n"
		.string "original form?!▼"
	.string "{WINDOW 0x34}"
		.string "Weil has moved to\n"
		.string "another base.▼"
		.string "With Omega...▼"
		.string "Weil was using you\n"
		.string "for his own purpose.▼"
	.string "{WINDOW 0x6F}"
		.string "Gee...g-gee...▼"
		.string "Everyone treats me\n"
		.string "l-like a fool!▼"
		.string "I-I won't stand for\n"
		.string "it! Let me show you\n"
		.string "my true power!$"
	.else
	.string "{WINDOW 0x6F}"
		.string "な…なンだ、オマエハ！？▼"
	.string "{WINDOW 0x04}"
		.string "エックス…！▼"
	.string "{WINDOW 0x6F}"
		.string "…エックスだと…！？▼"
		.string "オマエが…ボクのもとにナった\n"
		.string "オリジナルのエックス…！？▼"
	.string "{WINDOW 0x34}"
		.string "バイルは…\n"
		.string "この本部をすて\n"
		.string "べつのところにうつったよ▼"
		.string "オメガをつれてね……▼"
		.string "キミはバイルに\n"
		.string "利用されていただけなんだよ…▼"
	.string "{WINDOW 0x6F}"
		.string "ギ…ギギッ…▼"
		.string "どいツも…こイつも…\n"
		.string "ボクをバカにしやがッテ…！▼"
		.string "ゆるサナイ…ユルサないぞ…！\n"
		.string "ボクの…本当のチカラを…\n"
		.string "見せテやル…！$"
	.endif

Text_AreaX2_HaaaaahOhNoWeilHas: @ 0x0838101E
	@ EN: Haaaaah!!! / Oh no! / Weil has placed a / trap on your body!
	.if ENGLISH
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}Haaaaah!!!▼"
	.string "{WINDOW 0x34}"
		.string "Oh no!▼"
		.string "Weil has placed a\n"
		.string "trap on your body!$"
	.else
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}ハぁーーーーっ！！▼"
	.string "{WINDOW 0x34}"
		.string "いけない！▼"
		.string "バイルはキミのカラダに\n"
		.string "ワナを！$"
	.endif

Text_AreaX2_GeeGagagaICanT: @ 0x08381044
	@ EN: Gee...gagaga?! / I...can't... / can't move... / Gagagaaa... / Aaaaaaarggh!
	.if ENGLISH
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}Gee...gagaga?!▼"
		.string "I...can't...\n"
		.string "can't move...▼"
		.string "Gagagaaa...\n"
		.string "Aaaaaaarggh!$"
	.else
	.string "{WINDOW 0x6F}"
		.string "{BOTTOM}ギ…ガガ…！？▼"
		.string "カ…カラダが…しびれ…▼"
		.string "グガガッ…\n"
		.string "アアアアアアーーーッ！$"
	.endif

Text_AreaX2_WeilKnewFromThe: @ 0x0838106D
	@ EN: ?! / Weil knew from the / start how things / would turn out, / so he must have / rigged a trap on / him... / To fulfill his / true ambition...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "?!▼"
	.string "{WINDOW 0x35}"
		.string "Weil knew from the\n"
		.string "start how things\n"
		.string "would turn out,▼"
		.string "so he must have\n"
		.string "rigged a trap on\n"
		.string "him...▼"
		.string "To fulfill his\n"
		.string "true ambition...$"
	.else
	.string "{WINDOW 0x04}"
		.string "………！？▼"
	.string "{WINDOW 0x35}"
		.string "バイルは はじめから\n"
		.string "こうなることを 知っていて…\n"
		.string "カレにワナをしかけていたんだ▼"
		.string "カレの…本当のヤボウを\n"
		.string "かなえるために……$"
	.endif

Text_AreaX2_HearMeCitizensOf: @ 0x083810B9
	@ EN: Hear me, citizens of / the great land of / Neo Arcadia... / I must inform you of / sorrowful news.
	.if ENGLISH
	.string "{WINDOW 0x52}"
		.string "Hear me, citizens of\n"
		.string "the great land of\n"
		.string "Neo Arcadia...▼"
		.string "I must inform you of\n"
		.string "sorrowful news.$"
	.else
	.string "{WINDOW 0x52}"
		.string "…ネオ・アルカディアの\n"
		.string "すべてのゼンリョウなるシミンの\n"
		.string "みなさんに……▼"
		.string "かなしいお知らせをしなければ\n"
		.string "なりません……$"
	.endif

Text_AreaX2_DrWeil: @ 0x083810F7
	@ EN: Dr. Weil...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "Dr. Weil...$"
	.else
	.string "{WINDOW 0x04}"
		.string "ドクター・バイル……$"
	.endif

Text_AreaX2_JustNowOurHeroMaster: @ 0x08381104
	@ EN: Just now... / Our hero Master X / was taken by blood- / thirsty extremists, / and he has sadly / passed away... / So, in accordance / with Ordinance ↾8, / I, Dr. Weil, will / become your new / leader... / It is time to put / a stop to these / extremists!
	.if ENGLISH
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}Just now...▼"
		.string "Our hero Master X\n"
		.string "was taken by blood-\n"
		.string "thirsty extremists,▼"
		.string "and he has sadly\n"
		.string "passed away...▼"
		.string "So, in accordance\n"
		.string "with Ordinance #8,▼"
		.string "I, Dr. Weil, will\n"
		.string "become your new\n"
		.string "leader...▼"
		.string "It is time to put\n"
		.string "a stop to these\n"
		.string "extremists!$"
	.else
	.string "{WINDOW 0x3A}"
		.string "{BOTTOM}たった今…▼"
		.string "チにうえたテロリストの手にかかり\n"
		.string "ワレラがエイユウ…\n"
		.string "エックスさまが…………▼"
		.string "おナクなりに…\n"
		.string "なりました………▼"
		.string "今からジョウレイ8コウの\n"
		.string "テキヨウにより…▼"
		.string "フショウこのドクター・バイルが\n"
		.string "みなさんのシドウシャとなり…▼"
		.string "テロリストちんあつのシキを\n"
		.string "とりおこなうことになりました…$"
	.endif

Text_AreaX2_ThankYouAllI: @ 0x0838119B
	@ EN: ... / Thank you all. I / have just confirmed / your approval. / I will have to ask / you all to do a / number of things... / Neo Arcadia cannot / know true peace, / until the extremists / are eradicated! / Let us all fight / together, until they / are wiped out! / He... / Hehehehe... / Heheheheheee... / Bwahahahahah!
	.if ENGLISH
	.string "{WINDOW 0x52}"
		.string "...▼"
		.string "Thank you all. I\n"
		.string "have just confirmed\n"
		.string "your approval.▼"
		.string "I will have to ask\n"
		.string "you all to do a\n"
		.string "number of things...▼"
		.string "Neo Arcadia cannot\n"
		.string "know true peace,\n"
		.string "until the extremists▼"
		.string "are eradicated!▼"
		.string "Let us all fight\n"
		.string "together, until they\n"
		.string "are wiped out!▼"
		.string "He...▼"
		.string "Hehehehe...▼"
		.string "Heheheheheee...\n"
		.string "Bwahahahahah!$"
	.else
	.string "{WINDOW 0x52}"
		.string "………▼"
		.string "ありがとうございます\n"
		.string "今、みなさんのごショウニンを\n"
		.string "カクニンいたしました▼"
		.string "これから、みなさんにイロイロな\n"
		.string "オネガイをすることになるかも\n"
		.string "しれませんが……▼"
		.string "テロリストぼくめつまで……\n"
		.string "ネオ・アルカディアに\n"
		.string "真の平和は、おとずれません！▼"
		.string "ともにテロリストをねだやしに\n"
		.string "するまで、戦おうでは\n"
		.string "ありませんか！！▼"
		.string "……クッ………▼"
		.string "クックックッ……▼"
		.string "クーックックックッ…\n"
		.string "クヒャーッハッハッハッハッ！$"
	.endif

Text_AreaX2_ItSAllGoing: @ 0x08381269
	@ EN: ... / It's all going / according to his / plans. / Dr. Weil... / Will he try to / repeat the tragedy / of the Elf Wars, / that ended a / century ago... / I'll look for Weil. / I need you to help. / Okay. / I'll look for him, / too... / I wanted to say / something. About / Omega... / ...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "...▼"
		.string "It's all going\n"
		.string "according to his\n"
		.string "plans.▼"
	.string "{WINDOW 0x35}"
		.string "Dr. Weil...▼"
		.string "Will he try to\n"
		.string "repeat the tragedy\n"
		.string "of the Elf Wars,▼"
		.string "that ended a\n"
		.string "century ago...▼"
	.string "{WINDOW 0x04}"
		.string "I'll look for Weil.▼"
		.string "I need you to help.▼"
	.string "{WINDOW 0x35}"
		.string "Okay.▼"
		.string "I'll look for him,\n"
		.string "too...▼"
		.string "I wanted to say\n"
		.string "something. About\n"
		.string "Omega...▼"
		.string "...$"
	.else
	.string "{WINDOW 0x04}"
		.string "…………▼"
		.string "すべてヤツの\n"
		.string "スジガキどおり……か▼"
	.string "{WINDOW 0x35}"
		.string "ドクター・バイル……▼"
		.string "あなたは また\n"
		.string "100年前の戦争を…▼"
		.string "ヨウセイ戦争の ヒゲキを\n"
		.string "くりかえす つもりなのか…▼"
	.string "{WINDOW 0x04}"
		.string "オレはバイルの行方をおう▼"
		.string "チカラをかしてくれ▼"
	.string "{WINDOW 0x35}"
		.string "わかった……▼"
		.string "ボクもカレのイバショを\n"
		.string "さがそう……▼"
		.string "ところで……\n"
		.string "オメガのことなんだが……▼"
		.string "…………$"
	.endif

Text_AreaX2_WhatIsItWellNever: @ 0x08381313
	@ EN: What is it? / Well...never mind. / I'll bring it up / again when the time / comes. / The heart is what / counts. Not the / body...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "What is it?▼"
	.string "{WINDOW 0x35}"
		.string "Well...never mind.▼"
		.string "I'll bring it up\n"
		.string "again when the time\n"
		.string "comes.▼"
		.string "The heart is what\n"
		.string "counts. Not the\n"
		.string "body...$"
	.else
	.string "{WINDOW 0x04}"
		.string "なんだ……？▼"
	.string "{WINDOW 0x35}"
		.string "いや……▼"
		.string "その時になったら\n"
		.string "あらためて言うよ……▼"
		.string "大事なのは、カラダではなく\n"
		.string "心なのだと……$"
	.endif

Text_AreaX2_TheHeart: @ 0x08381352
	@ EN: The heart? / ...
	.if ENGLISH
	.string "{WINDOW 0x04}"
		.string "The heart?▼"
		.string "...$"
	.else
	.string "{WINDOW 0x04}"
		.string "心……だと？▼"
		.string "…………$"
	.endif

.balign 4, 0
