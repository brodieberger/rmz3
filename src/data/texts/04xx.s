.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_Volcano:: @ 0x0837fb30
  .2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start)
  .2byte (Text4-Start), (Text5-Start)

Text_Volcano:: @ 0x0837fb3c
Start:

Text0: @ 0x0837FB3C
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

Text1: @ 0x0837FC15
Text2:
	.string "{WINDOW 0x17}"
		.string "たよりないザコどもを\n"
		.string "まとめるのに…しょうじき\n"
		.string "あきていたところだが…▼"
		.string "オマエなら\n"
		.string "少しは、たのしめそうだ…▼"
		.string "かんげいするぜ！\n"
		.string "ゼロォッ！$"

Text3: @ 0x0837FC5E
	.string "{WINDOW 0x07}"
		.string "シャハアァァァッ！▼"
		.string "バイル・ナンバーズがひとり！\n"
		.string "オレの名は\n"
		.string "ブレイジン・フリザード！▼"
		.string "オレをあつくしてくれ！\n"
		.string "ゼェロォォォッッ！$"

Text4: @ 0x0837FCA3
	.string "{WINDOW 0x06}"
		.string "もうおしまいか！？▼"
		.string "さめちまうなぁ！\n"
		.string "ひまつぶしにもならんかぁ！▼"
		.string "シャハァーッハッハッハァ！$"

Text5: @ 0x0837FCD4
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

.balign 4, 0
