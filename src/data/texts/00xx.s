.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOfs_System:: @ 0x08376920
	.2byte (Text0-Start), (Text1-Start), (Text2-Start), (Text3-Start), (Text4-Start), (Text5-Start), (Text6-Start), (Text7-Start)
	.2byte (Text8-Start), (Text9-Start), (Text10-Start), (Text11-Start), (Text12-Start), (Text13-Start), (Text14-Start), (Text15-Start)
	.2byte (Text16-Start), (Text17-Start), (Text18-Start), (Text19-Start), (Text20-Start), (Text21-Start), (Text22-Start), (Text23-Start)
	.2byte (Text24-Start), (Text25-Start), (Text26-Start), (Text27-Start), (Text28-Start), (Text29-Start), (Text30-Start), (Text31-Start)
	.2byte (Text32-Start), (Text33-Start), (Text34-Start), (Text35-Start), (Text36-Start), (Text37-Start), (Text38-Start), (Text39-Start)
	.2byte (Text40-Start), (Text41-Start), (Text42-Start), (Text43-Start), (Text44-Start), (Text45-Start), (Text46-Start), (Text47-Start)
	.2byte (Text48-Start), (Text49-Start), (Text50-Start), (Text51-Start), (Text52-Start), (Text53-Start), (Text54-Start), (Text55-Start)
	.2byte (Text56-Start), (Text57-Start), (Text58-Start), (Text59-Start), (Text60-Start), (Text61-Start), (Text62-Start), (Text63-Start)
	.2byte (Text64-Start), (Text65-Start), (Text66-Start), (Text67-Start), (Text68-Start), (Text69-Start), (Text70-Start), (Text71-Start)
	.2byte (Text72-Start), (Text73-Start), (Text74-Start), (Text75-Start), (Text76-Start), (Text77-Start), (Text78-Start), (Text79-Start)
	.2byte (Text80-Start), (Text81-Start), (Text82-Start), (Text83-Start), (Text84-Start), (Text85-Start), (Text86-Start), (Text87-Start)
	.2byte (Text88-Start), (Text89-Start), (Text90-Start), (Text91-Start), (Text92-Start), (Text93-Start), (Text94-Start), (Text95-Start)
	.2byte (Text96-Start), (Text97-Start), (Text98-Start), (Text99-Start), (Text100-Start), (Text101-Start), (Text102-Start), (Text103-Start)
	.2byte (Text104-Start), (Text105-Start), (Text106-Start), (Text107-Start), (Text108-Start), (Text109-Start), (Text110-Start), (Text111-Start)
	.2byte (Text112-Start), (Text113-Start), (Text114-Start), (Text115-Start), (Text116-Start), (Text117-Start), (Text118-Start), (Text119-Start)
	.2byte (Text120-Start), (Text121-Start), (Text122-Start), (Text123-Start), (Text124-Start), (Text125-Start), (Text126-Start), (Text127-Start)
	.2byte (Text128-Start), (Text129-Start), (Text130-Start), (Text131-Start), (Text132-Start), (Text133-Start), (Text134-Start), (Text135-Start)
	.2byte (Text136-Start), (Text137-Start), (Text138-Start), (Text139-Start), (Text140-Start), (Text141-Start), (Text142-Start), (Text143-Start)
	.2byte (Text144-Start), (Text145-Start), (Text146-Start), (Text147-Start), (Text148-Start), (Text149-Start), (Text150-Start), (Text151-Start)
	.2byte (Text152-Start), (Text153-Start), (Text154-Start), (Text155-Start), (Text156-Start), (Text157-Start), (Text158-Start), (Text159-Start)
	.2byte (Text160-Start), (Text161-Start), (Text162-Start), (Text163-Start), (Text164-Start), (Text165-Start), (Text166-Start), (Text167-Start)
	.2byte (Text168-Start), (Text169-Start), (Text170-Start), (Text171-Start), (Text172-Start), (Text173-Start), (Text174-Start), (Text175-Start)
	.2byte (Text176-Start), (Text177-Start), (Text178-Start), (Text179-Start), (Text180-Start), (Text181-Start), (Text182-Start), (Text183-Start)
	.2byte (Text184-Start), (Text185-Start), (Text186-Start), (Text187-Start), (Text188-Start), (Text189-Start), (Text190-Start), (Text191-Start)
	.2byte (Text192-Start), (Text193-Start), (Text194-Start), (Text195-Start), (Text196-Start), (Text197-Start), (Text198-Start), (Text199-Start)
	.2byte (Text200-Start), (Text201-Start), (Text202-Start), (Text203-Start), (Text204-Start), (Text205-Start), (Text206-Start), (Text207-Start)
	.2byte (Text208-Start), (Text209-Start), (Text210-Start), (Text211-Start), (Text212-Start), (Text213-Start), (Text214-Start), (Text215-Start)
	.2byte (Text216-Start), (Text217-Start), (Text218-Start)

Text_System:: @ 0x08376ad6
Start:
    # シエル
Text0: @ 0x08376AD6
	.string "{WINDOW 0x02}"
		.string "だれに、話しかけますか？\n"
		.string "  オペレーター\n"
		.string "  シエル$"

Text1: @ 0x08376AF5
	.string "{WINDOW 0x40}"
		.string "なにかしら？ なんでも言ってね\n"
		.string "  データのかんり\n"
		.string "  話をする$"

Text2: @ 0x08376B1A
	.string "{WINDOW 0x40}"
		.string "  データをキロクします\n"
		.string "  データを呼び出します\n"
		.string "  データを消します$"

Text3: @ 0x08376B44
	.string "{WINDOW 0x40}"
		.string "どこにデータをキロクしますか？$"

Text4: @ 0x08376B56
	.string "{WINDOW 0x40}"
		.string " のデータを上がきしていいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text5: @ 0x08376B76
	.string "{WINDOW 0x40}"
		.string "どのデータを呼び出しますか？$"

Text6: @ 0x08376B89
	.string "{WINDOW 0x40}"
		.string " のデータを呼び出していいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text7: @ 0x08376BAA
	.string "{WINDOW 0x40}"
		.string "どのデータを消しますか？$"

Text8: @ 0x08376BBA
	.string "{WINDOW 0x40}"
		.string " のデータを消していいですか？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text9: @ 0x08376BD8
	.string "{WINDOW 0x40}"
		.string "データをキロクしました$"

Text10: @ 0x08376BE6
	.string "{WINDOW 0x40}"
		.string "データを呼び出しました$"

Text11: @ 0x08376BF6
	.string "{WINDOW 0x40}"
		.string "データを消しました$"

@ オペレータ
Text12: @ 0x08376C03
Text13: @ 0x08376C03
Text14: @ 0x08376C03
Text15: @ 0x08376C03
	.string "{WINDOW 0x62}"
		.string "{TOP}しじを おねがいします\n"
		.string "  ミッションへ行く\n"
		.string "  いちど行ったエリアへ転送$"

Text16: @ 0x08376C30
	.string "{WINDOW 0x62}"
		.string "{TOP}センタクできるミッションを\n"
		.string "ひょうじ します$"

Text17: @ 0x08376C4A
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}では、他を見てみましょう$"

Text18: @ 0x08376C5C
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}このミッションしかセンタクできません\n"
		.string "ジュンビができましたら\n"
		.string "いつでも声をおかけください…$"

Text19: @ 0x08376C8E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}$"

@ ミッション選択(序盤4)
Text20: @ 0x08376C92
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ネオ・アルカディア軍が\n"
		.string "アグニスかざんにある基地に\n"
		.string "シュウケツしつつあります▼"
		.string "カレらの目的は、\n"
		.string "現在のところ不明…$"

Text21: @ 0x08376CD8
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}テイサツをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text22: @ 0x08376CF8
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

Text23: @ 0x08376DA0
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text24: @ 0x08376DB9
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

Text25: @ 0x08376E5F
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text26: @ 0x08376E78
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

Text27: @ 0x08376F0D
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサ…おねがいできますか？\n"
		.string "  はい\n"
		.string "  いいえ$"

@ ミッション選択(中盤4)
Text28: @ 0x08376F2B
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ミナミの砂ばくをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "ヒカク的はやめのゲイゲキが\n"
		.string "ヒツヨウかと思われます$"

Text29: @ 0x08376F6A
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text30: @ 0x08376F8A
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}アナトレーのモリをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "ヒカク的はやめのゲイゲキが\n"
		.string "ヒツヨウかと思われます$"

Text31: @ 0x08376FC9
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text32: @ 0x08376FE9
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}キタのツンドラをすすむ\n"
		.string "ネオ・アルカディア軍を\n"
		.string "カクニン…▼"
		.string "テキは…\n"
		.string "ゼンセン基地を\n"
		.string "コウチクしているモヨウ…▼"
		.string "タショウの時間的ヨユウが\n"
		.string "あるものと思われます…$"

Text33: @ 0x08377044
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}ゲイゲキに向かわれますか…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text34: @ 0x08377061
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

Text35: @ 0x083770E3
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ジュンビは、よろしいでしょうか？\n"
		.string "  はい\n"
		.string "  いいえ$"

@ ミッション選択(後半4)
Text36: @ 0x08377102
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ここはネオ・アルカディアの\n"
		.string "エネルギーしせつなのですが…\n"
		.string "今は、ヘイサされています▼"
		.string "エネルギー不足にもかかわらず\n"
		.string "シセツをヘイサしてまで\n"
		.string "カレらがやりたいことは何か？▼"
		.string "ちょうどバイルが現れたあたりに\n"
		.string "ヘイサされたのが気になります$"

Text37: @ 0x0837717E
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサをおねがいしたいのですが…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text38: @ 0x0837719E
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

Text39: @ 0x08377267
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text40: @ 0x08377280
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}旧ジダイのトショカンのイセキが\n"
		.string "発見されました▼"
		.string "内部はミズびたしですが…\n"
		.string "どこかに生きてるデータが\n"
		.string "あるかもしれません▼"
		.string "バイルやオメガのデータを\n"
		.string "さがしていただきたいのですが…$"

Text41: @ 0x083772E2
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}おねがいできますか…\n"
		.string "  はい\n"
		.string "  いいえ$"

Text42: @ 0x083772FB
	.string "{WINDOW 0x61}"
		.string "{BOTTOM}ネオ・アルカディアが\n"
		.string "巨大なエレベーターを\n"
		.string "カンセイさせたようです▼"
		.string "使用目的は、不明…▼"
		.string "地下深くより\n"
		.string "何かをはこんでいるようです$"

Text43: @ 0x0837734B
	.string "{WINDOW 0x62}"
		.string "{BOTTOM}チョウサをおねがいできますか\n"
		.string "  はい\n"
		.string "  いいえ$"

Text44: @ 0x08377368
	.string "{WINDOW 0x61}"
		.string "オリジナルエックスより\n"
		.string "入手した ざひょうに転送します▼"
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "気をつけてね………$"

Text45: @ 0x0837739C
	.string "{WINDOW 0x62}"
		.string "ジュンビは、よろしいでしょうか？\n"
		.string "  はい\n"
		.string "  いいえ$"

@ フリーラン
Text46: @ 0x083773BA
Text47: @ 0x083773BA
Text48: @ 0x083773BA
Text49: @ 0x083773BA
Text50: @ 0x083773BA
	.string "{WINDOW 0x62}"
		.string "どこに転送しますか？$"

Text51: @ 0x083773C9
	.string "{WINDOW 0x62}"
		.string "{RED}こわれたウチュウセン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text52: @ 0x083773E7
	.string "{WINDOW 0x62}"
		.string "{RED}アグニスかざんの基地{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text53: @ 0x08377407
	.string "{WINDOW 0x62}"
		.string "{RED}カイジョウのハイウェイあとち{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text54: @ 0x08377429
	.string "{WINDOW 0x62}"
		.string "{RED}ヘイキ再生工場{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text55: @ 0x08377447
	.string "{WINDOW 0x62}"
		.string "{RED}旧きょじゅうく{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text56: @ 0x08377463
	.string "{WINDOW 0x62}"
		.string "{RED}ミサイル工場{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text57: @ 0x0837747E
	.string "{WINDOW 0x62}"
		.string "{RED}ゆうやみの砂ばく{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text58: @ 0x0837749B
	.string "{WINDOW 0x62}"
		.string "{RED}アナトレーのモリ{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text59: @ 0x083774B7
	.string "{WINDOW 0x62}"
		.string "{RED}コオリのゼンセン基地{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text60: @ 0x083774D7
	.string "{WINDOW 0x62}"
		.string "{RED}エリアX-2{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text61: @ 0x083774F1
	.string "{WINDOW 0x62}"
		.string "{RED}エネルギーしせつ{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text62: @ 0x0837750D
	.string "{WINDOW 0x62}"
		.string "{RED}セツゲン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text63: @ 0x08377525
	.string "{WINDOW 0x62}"
		.string "{RED}すいぼつしたトショカン{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text64: @ 0x08377544
	.string "{WINDOW 0x62}"
		.string "{RED}巨大エレベーター{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text65: @ 0x08377562
	.string "{WINDOW 0x62}"
		.string "{RED}アンダー・アルカディア{RED_END}ですね？\n"
		.string "  はい\n"
		.string "  いいえ$"

@ 転送
Text66: @ 0x08377581
Text67: @ 0x08377581
Text68: @ 0x08377581
Text69: @ 0x08377581
Text70: @ 0x08377581
	.string "{WINDOW 0x61}"
		.string "ミッションはつれい…\n"
		.string "かくいん、転送じゅんびにかかれ$"

Text71: @ 0x083775A0
	.string "{WINDOW 0x62}"
		.string "転送じゅんびカンリョウ…$"

Text72: @ 0x083775B1
	.string "{WINDOW 0x61}"
		.string "転送！$"

@ シエルの見送りメッセージ
Text73: @ 0x083775B9
Text74: @ 0x083775B9
	.string "{WINDOW 0x40}"
		.string "ゼロ…気をつけて……$"
Text75: @ 0x083775C7
	.string "{WINDOW 0x40}"
		.string "ゼロ……$"

Text76: @ 0x083775CE
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "かならず…\n"
		.string "かえってきて…ね…$"

Text77: @ 0x083775E5
	.string "{WINDOW 0x40}"
		.string "無理しないでね…ゼロ$"

Text78: @ 0x083775F4
	.string "{WINDOW 0x40}"
		.string "ゼロ……▼"
		.string "かえって…きてね……$"

Text79: @ 0x08377606
	.string "{WINDOW 0x40}"
		.string "ゼローーーーーー！$"

@ ミッション終了後
Text80: @ 0x08377612
	.string "{WINDOW 0x62}"
		.string "転送カンリョウまで…     \n"
		.string "2…     \n"
		.string "1…$"

Text81: @ 0x08377631
	.string "{WINDOW 0x61}"
		.string "おつかれさまでした$"

Text82: @ 0x0837763D
Text83: @ 0x0837763D
Text84: @ 0x0837763D
Text85: @ 0x0837763D
Text86: @ 0x0837763D
Text87: @ 0x0837763D
Text88: @ 0x0837763D
Text89: @ 0x0837763D
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

Text90: @ 0x083776DA
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

Text91: @ 0x0837774D
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

Text92: @ 0x083777FD
	.string "{WINDOW 0x40}"
		.string "ゼロ…ありがとう▼"
		.string "これで再生工場は、\n"
		.string "しばらく動かないと思うわ…▼"
		.string "本当に…ありがとう…$"

Text93: @ 0x08377832
	.string "{WINDOW 0x40}"
		.string "ゼロ、ありがとう…▼"
		.string "ホウコクにあった\n"
		.string "ダークエルフって…▼"
		.string "ベビーエルフたちのこと\n"
		.string "だったのね…▼"
		.string "ネオ・アルカディアは…\n"
		.string "あのコたちを使って\n"
		.string "何をするつもりなのかしら……$"

Text94: @ 0x0837788B
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"

Text95: @ 0x083778CB
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"

Text96: @ 0x0837790B
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "リーダーをうしなって\n"
		.string "このエリアのネオ・アルカディアは\n"
		.string "タイキャクしたみたい…▼"
		.string "本当にありがとう…$"

Text97: @ 0x0837794B
	.string "{WINDOW 0x40}"
		.string "おかえりなさい…ゼロ…▼"
		.string "バイルは、あの工場で\n"
		.string "ベビーエルフをタイリョウに\n"
		.string "作ろうとしてたみたい…▼"
		.string "でも いったい……▼"
		.string "ベビーエルフをあんなに作って…\n"
		.string "バイルは何するつもりだったのかしら$"

Text98: @ 0x083779AE
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

Text99: @ 0x08377A21
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

Text100: @ 0x08377A95
	.string "{WINDOW 0x40}"
		.string "ありがとう…ゼロ…▼"
		.string "あのエレベーターは、\n"
		.string "Eクリスタルをたいりょうに\n"
		.string "はこんでいたみたい…▼"
		.string "でも、いったい……▼"
		.string "あんなにエネルギーを集めて…\n"
		.string "バイルは何するつもりだったのかしら$"

Text101: @ 0x08377AF2
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

@ セルヴォ
Text102: @ 0x08377B60
	.string "{WINDOW 0x43}"
		.string "なんのようかな？\n"
		.string "  シークレットディスクのカイセキ\n"
		.string "  話をする$"

@ コンピュータ
Text103: @ 0x08377B85
	.string "{WINDOW 0x02}"
		.string "キドウシマシタ$"

Text104: @ 0x08377B8F
	.string "{WINDOW 0x02}"
		.string "コマンド ヲ センタク シテ クダサイ\n"
		.string "  何かをしらべる\n"
		.string "  通信する$"

Text105: @ 0x08377BB9
	.string "{WINDOW 0x02}"
		.string "「ロックマンエグゼ4 レッドサン」\n"
		.string "「ロックマンエグゼ4 ブルームーン」 ト\n"
		.string "バトルチップ トレード ガ デキマス▼"
		.string "「ロックマンゼロ3」 ニ バトルチップ ヲ オクル ト\n"
		.string "サイバークウカン ノ テキ ガ ヘンカ シマス▼"
		.string "「ロックマンエグゼ4」 デ PETガメン ニ ハイリ\n"
		.string "「つうしん」 ノ 「トレード」 カラ\n"
		.string "「バトルチップ」 ヲ センタク シテ 通信シテクダサイ$"

Text106: @ 0x08377C75
	.string "{WINDOW 0x02}"
		.string "通信ヲ カイシ シマスカ？\n"
		.string "  はい\n"
		.string "  いいえ$"

Text107: @ 0x08377C92
	.string "{WINDOW 0x02}"
		.string "通信タイキ中デス\n"
		.string "\n"
		.string "(Bボタン デ キャンセル デキマス)$"

Text108: @ 0x08377CB5
	.string "{WINDOW 0x02}"
		.string "ロックマンエグゼ4 ト 通信中デス\n"
		.string "ロックマンエグゼ4 ガワ デ ソウサ シテ クダサイ$"

Text109: @ 0x08377CE7
	.string "{WINDOW 0x02}"
		.string "通信エラー デス\n"
		.string "通信ヲ シュウリョウ シマス$"

Text110: @ 0x08377D05
	.string "{WINDOW 0x02}"
		.string "通信カンリョウ\n"
		.string "サイバークウカン ガ ヘンカ シマシタ！$"

Text111: @ 0x08377D26
	.string "{WINDOW 0x02}"
		.string "通信カンリョウ$"

@ 改造カード
Text112: @ 0x08377D32
Text113: @ 0x08377D32
Text114: @ 0x08377D32
Text115: @ 0x08377D32
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}改造カードをじゅしんしました\n"
		.string "  改造じっこう\n"
		.string "  やめておく$"

Text116: @ 0x08377D59
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}通信エラーです$"

Text117: @ 0x08377D66
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}カード{VARIABLE}の改造を もとにもどしました$"

Text118: @ 0x08377D7E
Text119: @ 0x08377D7E
Text120: @ 0x08377D7E
Text121: @ 0x08377D7E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}タイトルバックのえが\n"
		.string "ちがうものに かわりました$"

Text122: @ 0x08377D9A
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "はちうえが おかれました$"

Text123: @ 0x08377DB9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのエレベーターの\n"
		.string "デザインが かわりました$"

Text124: @ 0x08377DDB
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text125: @ 0x08377E01
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ハンターの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text126: @ 0x08377E1E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ガーディアンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text127: @ 0x08377E3D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ナース系エルフの\n"
		.string "デザインが かわりました$"

Text128: @ 0x08377E57
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの2かいの\n"
		.string "どこかに 仲間が ふえました$"

Text129: @ 0x08377E7A
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのタマの\n"
		.string "デザインが かわりました$"

Text130: @ 0x08377E97
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゲーム中に出現するZパネルの\n"
		.string "デザインが かわりました$"

Text131: @ 0x08377EB9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アルエットのきている ふくの\n"
		.string "デザインが かわりました$"

Text132: @ 0x08377ED8
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text133: @ 0x08377F0B
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼロのボウギョりょくが\n"
		.string "つうじょう時の2倍になりました$"

Text134: @ 0x08377F2C
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}メッセージウィンドウの\n"
		.string "デザインが かわりました$"

Text135: @ 0x08377F48
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ライフエネルギーの\n"
		.string "デザインが かわりました$"

Text136: @ 0x08377F62
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text137: @ 0x08377F88
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}これまで改造したものを\n"
		.string "すべて リセットしました$"

Text138: @ 0x08377FA6
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "ネコが まよいこみました$"

Text139: @ 0x08377FC5
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースに\n"
		.string "ユキが ふってきました$"

Text140: @ 0x08377FDF
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゲーム中に出現する\n"
		.string "Eクリスタルの\n"
		.string "デザインが かわりました$"

Text141: @ 0x08378004
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text142: @ 0x0837802D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text143: @ 0x08378062
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シエルのへやのコンピューターの\n"
		.string "デザインが かわりました$"

Text144: @ 0x08378082
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "なぞのサイバーエルフが現れました$"

Text145: @ 0x083780A6
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}1{RED_END}ふえました$"

Text146: @ 0x083780CD
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのかべに\n"
		.string "カイガが かけられました$"

Text147: @ 0x083780EB
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのどこかに\n"
		.string "新しくトビラが出現しました$"

Text148: @ 0x0837810E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text149: @ 0x08378135
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの1かいの\n"
		.string "どこかに 仲間が ふえました$"

Text150: @ 0x08378158
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのおくじょうに\n"
		.string "はなが さきました$"

Text151: @ 0x08378176
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフの\n"
		.string "デザインが かわりました$"

Text152: @ 0x08378191
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アンドリューのすがたが\n"
		.string "わかがえりました$"

Text153: @ 0x083781A9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text154: @ 0x083781DC
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのそらに\n"
		.string "カモメが やってきました$"

Text155: @ 0x083781FA
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text156: @ 0x0837822F
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シークレットディスクの\n"
		.string "デザインが かわりました$"

Text157: @ 0x0837824B
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text158: @ 0x08378274
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのかべに\n"
		.string "だれかが ラクガキしました$"

Text159: @ 0x08378293
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text160: @ 0x083782B9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの右の\n"
		.string "カンシトウにいるレジスタンスの\n"
		.string "会話のナイヨウが かわりました$"

Text161: @ 0x083782EC
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シールドブーメランの\n"
		.string "コウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text162: @ 0x08378315
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの左の\n"
		.string "カンシトウにいるレジスタンスの\n"
		.string "会話のナイヨウが かわりました$"

Text163: @ 0x08378348
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのビータックと\n"
		.string "ビーナイプのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text164: @ 0x0837837D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text165: @ 0x083783B0
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ハッカー系エルフの\n"
		.string "デザインが かわりました$"

Text166: @ 0x083783CB
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}クロスバインの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text167: @ 0x083783E4
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ベースの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text168: @ 0x08378400
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バスターショットのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text169: @ 0x08378427
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースが\n"
		.string "よるに なりました$"

Text170: @ 0x0837843F
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・アクアの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text171: @ 0x0837845B
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースのミナトで\n"
		.string "サカナが はねるようになりました$"

Text172: @ 0x0837847E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}リコイルロッドのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text173: @ 0x083784A4
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レジスタンスベースの3かいの\n"
		.string "どこかに 仲間が ふえました$"

Text174: @ 0x083784C7
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アニマル系エルフのアーチムと\n"
		.string "アーチルのコウゲキりょくが\n"
		.string "つうじょう時より{RED}4{RED_END}ふえました$"

Text175: @ 0x083784FA
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}2{RED_END}ふえました$"

Text176: @ 0x08378520
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パンテオン・ボマーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text177: @ 0x0837853C
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}かいぞうパンテオン・アクアの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text178: @ 0x0837855D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ゼットセイバーのコウゲキりょくが\n"
		.string "つうじょう時より{RED}3{RED_END}ふえました$"

Text179: @ 0x08378583
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}パープルナープルの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text180: @ 0x0837859E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シェルクローラーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text181: @ 0x083785B9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}アイスボンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text182: @ 0x083785D1
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ジェネレーターキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text183: @ 0x083785EF
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}クラベッガーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text184: @ 0x08378608
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シャットカウンターの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text185: @ 0x08378624
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}グランドキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text186: @ 0x0837863F
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シュリンポリンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text187: @ 0x08378659
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}バットンリングの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text188: @ 0x08378673
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ピラーキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text189: @ 0x0837868D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ヴォルケールの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text190: @ 0x083786A6
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}スネーケーブルの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text191: @ 0x083786C0
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}レミングルスの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text192: @ 0x083786D9
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ランプロートの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text193: @ 0x083786F2
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}タイルキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text194: @ 0x0837870C
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シェルーノーの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text195: @ 0x08378725
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ヘビーキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text196: @ 0x0837873F
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}モスジーロの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text197: @ 0x08378757
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}カプセルキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text198: @ 0x08378772
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}キャリビーGの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text199: @ 0x0837878C
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ダスロックの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text200: @ 0x083787A4
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ジャイロキャノンの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text201: @ 0x083787BF
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}シャークシールXの体力が\n"
		.string "{RED}4{RED_END}ふえました$"

Text202: @ 0x083787DA
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}オールワーマーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text203: @ 0x083787F5
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ブランワーマーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text204: @ 0x08378810
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ロコモIFの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text205: @ 0x08378829
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}ビーサーバーの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text206: @ 0x08378843
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}メガミルパの体力が\n"
		.string "{RED}16{RED_END}ふえました$"

Text207: @ 0x0837885C
Text208: @ 0x0837885C
Text209: @ 0x0837885C
Text210: @ 0x0837885C
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ゼロ{RED_END}のミニゲームが ツイカされました$"

Text211: @ 0x08378874
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}シエル{RED_END}のミニゲームが ツイカされました$"

Text212: @ 0x0837888D
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}コピーエックス{RED_END}のミニゲームが ツイカされました$"

Text213: @ 0x083788AA
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ハルピュイア{RED_END}のミニゲームが ツイカされました$"

Text214: @ 0x083788C6
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ファーブニル{RED_END}のミニゲームが ツイカされました$"

Text215: @ 0x083788E2
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}レヴィアタン{RED_END}のミニゲームが ツイカされました$"

Text216: @ 0x083788FE
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ファントム{RED_END}のミニゲームが ツイカされました$"

Text217: @ 0x08378919
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}ハードモード{RED_END}が ツイカされました▼"
		.string "Lボタンをおしながら\n"
		.string "「はじめから」をせんたくすると\n"
		.string "ハードモードでプレイすることができます$"

Text218: @ 0x0837895E
	.string "{WINDOW 0x02}"
		.string "{BOTTOM}{RED}アルティメットモード{RED_END}が ツイカされました▼"
		.string "Rボタンをおしながら\n"
		.string "「はじめから」をせんたくすると\n"
		.string "アルティメットモードでプレイすることができます$"

.balign 4, 0
