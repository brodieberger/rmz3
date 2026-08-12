.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_WeaponRepairFactory:: @ 0x0837ff30
  .2byte (Text_WeaponRepairFactory_FactoryControlUnit-Start), (Text_WeaponRepairFactory_WellIfItIsnT-Start), (Text_WeaponRepairFactory_WellIfItIsnT_Alias1-Start), (Text_WeaponRepairFactory_KekekeTheFirstLessonA-Start)
  .2byte (Text_WeaponRepairFactory_KekeTheBloodOfA-Start), (Text_WeaponRepairFactory_KeKekeNoManners-Start)

Text_WeaponRepairFactory:: @ 0x0837ff3c
Start:

Text_WeaponRepairFactory_FactoryControlUnit: @ 0x0837FF3C
	@ EN: Operator: / Ahead is the factory / control unit. / Data from cameras / in the factory is / sent to this unit. / Destroy the cameras / as you proceed.
	.if ENGLISH
	.string "{WINDOW 0x64}"
		.string "Operator:\n"
		.string "Ahead is the factory\n"
		.string "control unit.▼"
		.string "Data from cameras\n"
		.string "in the factory is\n"
		.string "sent to this unit.▼"
		.string "Destroy the cameras\n"
		.string "as you proceed.$"
	.else
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「さきにすすむと工場をソウサする\n"
		.string " コントロールユニットがあります▼"
		.string "「工場内にセッチされたカメラから\n"
		.string " そのコントロールユニットへと\n"
		.string " データが転送されているようです▼"
		.string "「カメラをハカイしながら\n"
		.string " すすんでください$"
	.endif

Text_WeaponRepairFactory_WellIfItIsnT: @ 0x0837FFB6
Text_WeaponRepairFactory_WellIfItIsnT_Alias1: @ 0x0837FFB6
	@ EN: Well, if it isn't / the legendary hero. / The Mechaniloids / do all the repairs / on their own. / So I was just / trying to enjoy a / little tea break. / How dare you disturb / my peace and quiet! / Where are your / manners, sir hero? / I, Devilbat Schilt, / of Weil's Numbers, / shall educate you.
	.if ENGLISH
	.string "{WINDOW 0x1B}"
		.string "Well, if it isn't\n"
		.string "the legendary hero.▼"
		.string "The Mechaniloids\n"
		.string "do all the repairs\n"
		.string "on their own.▼"
		.string "So I was just\n"
		.string "trying to enjoy a\n"
		.string "little tea break.▼"
		.string "How dare you disturb\n"
		.string "my peace and quiet!▼"
		.string "Where are your\n"
		.string "manners, sir hero?▼"
		.string "I, Devilbat Schilt,\n"
		.string "of Weil's Numbers,\n"
		.string "shall educate you.$"
	.else
	.string "{WINDOW 0x1B}"
		.string "これはこれは\n"
		.string "伝説のエイユウさまじゃないですか▼"
		.string "ここのメカニロイドどもは\n"
		.string "ほおっておいても\n"
		.string "いくらでも再生するのでね▼"
		.string "ちょっとしたティータイムをたのしんで\n"
		.string "いたのですが…▼"
		.string "せっかくのユウガな時間を\n"
		.string "ジャマをするとは…▼"
		.string "エイユウさまも\n"
		.string "マナーがなっていませんな▼"
		.string "バイル・ナンバーズがひとり\n"
		.string "このヘルバット・シルトが\n"
		.string "キョウイクしてあげましょう$"
	.endif

Text_WeaponRepairFactory_KekekeTheFirstLessonA: @ 0x08380069
	@ EN: Kekeke! / The first lesson a / gentleman must learn / in refinement is... / Intruders are to die / without a fuss!
	.if ENGLISH
	.string "{WINDOW 0x0B}"
		.string "Kekeke!▼"
		.string "The first lesson a\n"
		.string "gentleman must learn\n"
		.string "in refinement is...▼"
		.string "Intruders are to die\n"
		.string "without a fuss!$"
	.else
	.string "{WINDOW 0x0B}"
		.string "キキキッ…！▼"
		.string "さて、まずは\n"
		.string "シンシのたしなみ、その1…▼"
		.string "ジャマ者はおとなしく\n"
		.string "死すべし！！$"
	.endif

Text_WeaponRepairFactory_KekeTheBloodOfA: @ 0x0838009B
	@ EN: Keke! / The blood of a / century-old hero has / such a lovely odor!
	.if ENGLISH
	.string "{WINDOW 0x0A}"
		.string "Keke!▼"
		.string "The blood of a\n"
		.string "century-old hero has\n"
		.string "such a lovely odor!$"
	.else
	.string "{WINDOW 0x0A}"
		.string "キキッ！▼"
		.string "100年モノのエイユウのチ\n"
		.string "実に、かぐわしい…！$"
	.endif

Text_WeaponRepairFactory_KeKekeNoManners: @ 0x083800BD
	@ EN: Ke...keke! / No manners... / No manners at all! / Trying to defy Lord / Weil, what dismal / behavior! / Ke...kekekekeeee!
	.if ENGLISH
	.string "{WINDOW 0x0A}"
		.string "Ke...keke!▼"
		.string "No manners...\n"
		.string "No manners at all!▼"
		.string "Trying to defy Lord\n"
		.string "Weil, what dismal\n"
		.string "behavior!▼"
		.string "Ke...kekekekeeee!$"
	.else
	.string "{WINDOW 0x0A}"
		.string "キッ…キキッ…！▼"
		.string "なっていない…\n"
		.string "実にマナーがなっていない…！▼"
		.string "バイルさまに…\n"
		.string "たてつこうなど…\n"
		.string "サイテイのマナーいはんですぞ…！▼"
		.string "キッ…キキキキキーーーッ！！$"
	.endif

.balign 4, 0
