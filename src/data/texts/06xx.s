.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_WeaponRepairFactory:: @ 0x0837ff30
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start)
  .2byte (Text4-Start), (Text5-Start)

Text_WeaponRepairFactory:: @ 0x0837ff3c
Start:

Text0: @ 0x0837FF3C
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「さきにすすむと工場をソウサする\n"
		.string " コントロールユニットがあります▼"
		.string "「工場内にセッチされたカメラから\n"
		.string " そのコントロールユニットへと\n"
		.string " データが転送されているようです▼"
		.string "「カメラをハカイしながら\n"
		.string " すすんでください$"

Text1: @ 0x0837FFB6
Text2: @ 0x0837FFB6
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

Text3: @ 0x08380069
	.string "{WINDOW 0x0B}"
		.string "キキキッ…！▼"
		.string "さて、まずは\n"
		.string "シンシのたしなみ、その1…▼"
		.string "ジャマ者はおとなしく\n"
		.string "死すべし！！$"

Text4: @ 0x0838009B
	.string "{WINDOW 0x0A}"
		.string "キキッ！▼"
		.string "100年モノのエイユウのチ\n"
		.string "実に、かぐわしい…！$"

Text5: @ 0x083800BD
	.string "{WINDOW 0x0A}"
		.string "キッ…キキッ…！▼"
		.string "なっていない…\n"
		.string "実にマナーがなっていない…！▼"
		.string "バイルさまに…\n"
		.string "たてつこうなど…\n"
		.string "サイテイのマナーいはんですぞ…！▼"
		.string "キッ…キキキキキーーーッ！！$"

.balign 4, 0
