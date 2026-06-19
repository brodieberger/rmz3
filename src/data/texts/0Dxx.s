.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_EnergyFactory:: @ 0x08381364
  .2byte Text0-Start, Text1-Start, Text2-Start, Text3-Start
  .2byte Text4-Start, Text5-Start

Texts_EnergyFactory:: @ 0x08381370
Start:

Text0: @ 0x08381370
	.string "{WINDOW 0x64}"
		.string "オペレーター:\n"
		.string "「現在、シセツのロシンは\n"
		.string " キドウしてないモヨウです▼"
		.string "「おくのエリアに行くには、\n"
		.string " ロシンを動かしてシセツのキノウを\n"
		.string " とりもどすヒツヨウがあります$"

Text1: @ 0x083813C9
	.string "{WINDOW 0x04}"
		.string "これは…？$"

Text2: @ 0x083813D1
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

Text3: @ 0x08381483
	.string "{WINDOW 0x0F}"
		.string "わたしはバイル・ナンバーズがひとり\n"
		.string "キュービット・フォクスター！▼"
		.string "にどと 口がきけないように\n"
		.string "してやるわ！$"

Text4: @ 0x083814BC
	.string "{WINDOW 0x0E}"
		.string "ホーッホッホッ！ いいキミね！\n"
		.string "わたしたちのジャマをするから\n"
		.string "そうなるのよ！▼"
		.string "安心しなさい…！\n"
		.string "きちんとあの世へ あんない\n"
		.string "してあげるわ$"

Text5: @ 0x08381506
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

.balign 4, 0
