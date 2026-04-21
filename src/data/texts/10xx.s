.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

.global TextOfs_GiantElevator
TextOfs_GiantElevator: @ 0x08382008
  .2byte (Text0 - Start), (Text1 - Start), (Text2 - Start), (Text3 - Start)

Texts_GiantElevator:: @ 0x08382010
Start:

Text0: @ 0x08382010
  .string "$"

Text1: @ 0x08382011
	.string "{WINDOW 0x15}"
		.string "ゴルルルゥ…テメエがゼロかぁ…？▼"
		.string "小さすぎてぇ\n"
		.string "ふんづけちまうところだったぜぇ…！▼"
		.string "オレの名はバイル・ナンバーズ\n"
		.string "トレテスタ・ケルベリアン▼"
		.string "そのほそいくび…\n"
		.string "ひとくちでぇ\n"
		.string "かみちぎってやるぜぇ！▼"
		.string "ゴルルルルルルァ！$"

Text2: @ 0x08382081
	.string "{WINDOW 0x14}"
		.string "ああーん？▼"
		.string "いつのまにかぁ\n"
		.string "ふみつぶしちまったかぁ？▼"
		.string "小さすぎて気づかなかったぜぇ！$"

Text3: @ 0x083820b0
	.string "{WINDOW 0x14}"
		.string "あ…れぇ…？\n"
		.string "ゼロォ…どこ行きやがったぁ…？\n"
		.string "見えねえぞぉ…？▼"
		.string "それに…カラダもいてえ…\n"
		.string "いてえ…いてえぞおおおっ！▼"
		.string "ゴアアアアアアッ！$"

.balign 4, 0
