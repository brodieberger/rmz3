.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

TextOffsets_OpenSecretDisk:: @ 0x083789AC
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
	.2byte (Text128-Start)

Texts_OpenSecretDisk:: @ 0x08378AAE
Start:

Text0: @ 0x08378AAE
		.string "シークレットディスク{RED}{VARIABLE}{RED_END}をゲットした！$"

Text1: @ 0x08378AC3
		.string "{RED}このディスクは ここではカイセキできない{RED_END}$"

Text2: @ 0x08378ADA
		.string "サブタンクをゲットした！$"

Text3: @ 0x08378AE7
		.string "サイバーエルフがサブタンクにかわった！$"

Text4: @ 0x08378AFB
Text5: @ 0x08378AFB
Text6: @ 0x08378AFB
Text7: @ 0x08378AFB
Text8: @ 0x08378AFB
Text9: @ 0x08378AFB
Text10: @ 0x08378AFB
		.string "{RED}デスタンツ・マンティスク{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}サウザンドスラッシュ{RED_END}をゲットした！$"

Text11: @ 0x08378B2C
		.string "{RED}チルドレ・イナラビッタ{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}ザンエイダン{RED_END}をゲットした！$"

Text12: @ 0x08378B58
		.string "{RED}ブレイジン・フリザード{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}バーストショット{RED_END}をゲットした！$"

Text13: @ 0x08378B86
		.string "{RED}ヘルバット・シルト{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}ラクサイガ{RED_END}をゲットした！$"

Text14: @ 0x08378BAF
		.string "{RED}ブリザック・スタグロフR{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}ブリザードアロー{RED_END}をゲットした！$"

Text15: @ 0x08378BDE
		.string "{RED}ハヌマシーンR{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}テンレツジン{RED_END}をゲットした！$"

Text16: @ 0x08378C06
		.string "{RED}グラチャ-・レ・カクタンク{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}サーキュラシールド{RED_END}をゲットした！$"

Text17: @ 0x08378C37
		.string "{RED}コピーエックスMK2{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}リフレクトレーザー{RED_END}をゲットした！$"

Text18: @ 0x08378C65
		.string "{RED}トレテスタ・ケルベリアン{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}レップウゲキ{RED_END}をゲットした！$"

Text19: @ 0x08378C92
		.string "{RED}アヌビステップ{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}クロールシールド{RED_END}をゲットした！$"

Text20: @ 0x08378CBC
		.string "{RED}キュービット・フォクスター{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}ソウルランチャー{RED_END}をゲットした！$"

Text21: @ 0x08378CEC
		.string "{RED}ヴォルティール・ビブリーオ{RED_END}のEXワザをキャプチャーした▼"
		.string "{RED}Vショット{RED_END}をゲットした！$"

Text22: @ 0x08378D19
		.string "{RED}ライト{RED_END}のボディチップをゲットした！$"

Text23: @ 0x08378D2D
		.string "{RED}アイス{RED_END}のボディチップをゲットした！$"

Text24: @ 0x08378D41
		.string "{RED}フレイム{RED_END}のボディチップをゲットした！$"

Text25: @ 0x08378D56
		.string "{RED}サンダー{RED_END}のボディチップをゲットした！$"

Text26: @ 0x08378D6B
		.string "{RED}アブソーバ{RED_END}のボディチップをゲットした！$"

Text27: @ 0x08378D81
		.string "{RED}シャドウダッシュ{RED_END}のフットチップをゲットした！$"

Text28: @ 0x08378D9A
		.string "{RED}ダブルジャンプ{RED_END}のフットチップをゲットした！$"

Text29: @ 0x08378DB2
		.string "{RED}スパイク{RED_END}のフットチップをゲットした！$"

Text30: @ 0x08378DC7
		.string "{RED}クイック{RED_END}のフットチップをゲットした！$"

Text31: @ 0x08378DDC
		.string "{RED}リコイルロッド{RED_END}を手に入れた！！$"

Text32: @ 0x08378DF0
		.string "{RED}シールドブーメラン{RED_END}を手に入れた！！$"

Text33: @ 0x08378E06
		.string "サイバーエルフ{RED}マルティナ{RED_END}が入っていた！$"

Text34: @ 0x08378E1D
		.string "サイバーエルフ{RED}ミルピィ{RED_END}が入っていた！$"

Text35: @ 0x08378E33
		.string "サイバーエルフ{RED}エルピィ{RED_END}が入っていた！$"

Text36: @ 0x08378E49
		.string "サイバーエルフ{RED}シルピィ{RED_END}が入っていた！$"

Text37: @ 0x08378E5F
		.string "サイバーエルフ{RED}レルピィ{RED_END}が入っていた！$"

Text38: @ 0x08378E75
		.string "サイバーエルフ{RED}アータン{RED_END}が入っていた！$"

Text39: @ 0x08378E8B
		.string "サイバーエルフ{RED}ジクタン{RED_END}が入っていた！$"

Text40: @ 0x08378EA1
		.string "サイバーエルフ{RED}モット{RED_END}が入っていた！$"

Text41: @ 0x08378EB6
		.string "サイバーエルフ{RED}ドット{RED_END}が入っていた！$"

Text42: @ 0x08378ECB
		.string "サイバーエルフ{RED}キュリフ{RED_END}が入っていた！$"

Text43: @ 0x08378EE1
		.string "サイバーエルフ{RED}ルルフ{RED_END}が入っていた！$"

Text44: @ 0x08378EF6
		.string "サイバーエルフ{RED}スルフ{RED_END}が入っていた！$"

Text45: @ 0x08378F0B
		.string "サイバーエルフ{RED}ティリフ{RED_END}が入っていた！$"

Text46: @ 0x08378F21
		.string "サイバーエルフ{RED}ユリフ{RED_END}が入っていた！$"

Text47: @ 0x08378F36
		.string "サイバーエルフ{RED}ベリフ{RED_END}が入っていた！$"

Text48: @ 0x08378F4B
		.string "サイバーエルフ{RED}ウィリフ{RED_END}が入っていた！$"

Text49: @ 0x08378F61
		.string "サイバーエルフ{RED}クリフ{RED_END}が入っていた！$"

Text50: @ 0x08378F76
		.string "サイバーエルフ{RED}スノック{RED_END}が入っていた！$"

Text51: @ 0x08378F8C
		.string "サイバーエルフ{RED}マティック{RED_END}が入っていた！$"

Text52: @ 0x08378FA3
		.string "サイバーエルフ{RED}ミヤック{RED_END}が入っていた！$"

Text53: @ 0x08378FB9
		.string "サイバーエルフ{RED}アジック{RED_END}が入っていた！$"

Text54: @ 0x08378FCF
		.string "サイバーエルフ{RED}トブック{RED_END}が入っていた！$"

Text55: @ 0x08378FE5
		.string "サイバーエルフ{RED}ムラック{RED_END}が入っていた！$"

Text56: @ 0x08378FFB
		.string "サイバーエルフ{RED}マイーラ{RED_END}が入っていた！$"

Text57: @ 0x08379011
		.string "サイバーエルフ{RED}ミウーラ{RED_END}が入っていた！$"

Text58: @ 0x08379027
		.string "サイバーエルフ{RED}コロップ{RED_END}が入っていた！$"

Text59: @ 0x0837903D
		.string "サイバーエルフ{RED}ソロップ{RED_END}が入っていた！$"

Text60: @ 0x08379053
		.string "サイバーエルフ{RED}プチット{RED_END}が入っていた！$"

Text61: @ 0x08379069
		.string "サイバーエルフ{RED}バレット{RED_END}が入っていた！$"

Text62: @ 0x0837907F
		.string "サイバーエルフ{RED}マーヤ{RED_END}が入っていた！$"

Text63: @ 0x08379094
		.string "サイバーエルフ{RED}クワッパ{RED_END}が入っていた！$"

Text64: @ 0x083790AA
		.string "サイバーエルフ{RED}ガンブル{RED_END}が入っていた！$"

Text65: @ 0x083790C0
		.string "サイバーエルフ{RED}バーエイド{RED_END}が入っていた！$"

Text66: @ 0x083790D7
		.string "サイバーエルフ{RED}バーリーフ{RED_END}が入っていた！$"

Text67: @ 0x083790EE
		.string "サイバーエルフ{RED}ピタッパ{RED_END}が入っていた！$"

Text68: @ 0x08379104
		.string "サイバーエルフ{RED}ピタップ{RED_END}が入っていた！$"

Text69: @ 0x0837911A
		.string "サイバーエルフ{RED}ビータック{RED_END}が入っていた！$"

Text70: @ 0x08379131
		.string "サイバーエルフ{RED}ビーナイプ{RED_END}が入っていた！$"

Text71: @ 0x08379148
		.string "サイバーエルフ{RED}アーチム{RED_END}が入っていた！$"

Text72: @ 0x0837915E
		.string "サイバーエルフ{RED}アーチル{RED_END}が入っていた！$"

Text73: @ 0x08379174
		.string "サイバーエルフ{RED}バイッス{RED_END}が入っていた！$"

Text74: @ 0x0837918A
		.string "サイバーエルフ{RED}デルピーナ{RED_END}が入っていた！$"

Text75: @ 0x083791A1
		.string "サイバーエルフ{RED}リゼタス{RED_END}が入っていた！$"

Text76: @ 0x083791B7
		.string "サイバーエルフ{RED}コータス{RED_END}が入っていた！$"

Text77: @ 0x083791CD
		.string "サイバーエルフ{RED}シュータス{RED_END}が入っていた！$"

Text78: @ 0x083791E4
		.string "サイバーエルフ{RED}マルタス{RED_END}が入っていた！$"

Text79: @ 0x083791FA
		.string "サイバーエルフ{RED}イレタス{RED_END}が入っていた！$"

Text80: @ 0x08379210
		.string "サイバーエルフ{RED}エネタス{RED_END}が入っていた！$"

Text81: @ 0x08379226
		.string "サイバーエルフ{RED}バースラス{RED_END}が入っていた！$"

Text82: @ 0x0837923D
		.string "サイバーエルフ{RED}セーバラス{RED_END}が入っていた！$"

Text83: @ 0x08379254
		.string "サイバーエルフ{RED}ロードラス{RED_END}が入っていた！$"

Text84: @ 0x0837926B
		.string "サイバーエルフ{RED}ブーメラス{RED_END}が入っていた！$"

Text85: @ 0x08379282
		.string "サイバーエルフ{RED}クロクル{RED_END}が入っていた！$"

Text86: @ 0x08379298
		.string "サイバーエルフ{RED}メットラス{RED_END}が入っていた！$"

Text87: @ 0x083792AF
		.string "サイバーエルフ{RED}メットリカ{RED_END}が入っていた！$"

Text88: @ 0x083792C6
		.string "サイバーエルフ{RED}メットルフ{RED_END}が入っていた！$"

Text89: @ 0x083792DD
		.string "サイバーエルフ{RED}メットレラ{RED_END}が入っていた！$"

Text90: @ 0x083792F4
		.string "サイバーエルフ{RED}メットロム{RED_END}が入っていた！$"

Text91: @ 0x0837930B
		.string "サイバーエルフ{RED}キーナイト{RED_END}が入っていた！$"

Text92: @ 0x08379322
		.string "サイバーエルフ{RED}サーナイト{RED_END}が入っていた！$"

Text93: @ 0x08379339
		.string "サイバーエルフ{RED}テーナイト{RED_END}が入っていた！$"

Text94: @ 0x08379350
		.string "サイバーエルフ{RED}ストパーラ{RED_END}が入っていた！$"

Text95: @ 0x08379367
		.string "サイバーエルフ{RED}ストピーナ{RED_END}が入っていた！$"

Text96: @ 0x0837937E
		.string "サイバーエルフ{RED}ストプール{RED_END}が入っていた！$"

Text97: @ 0x08379395
		.string "サイバーエルフ{RED}ストペータ{RED_END}が入っていた！$"

Text98: @ 0x083793AC
		.string "サイバーエルフ{RED}ストポーサ{RED_END}が入っていた！$"

Text99: @ 0x083793C3
		.string "サイバーエルフ{RED}ハンマーガ{RED_END}が入っていた！$"

Text100: @ 0x083793DA
		.string "サイバーエルフ{RED}ハンマージ{RED_END}が入っていた！$"

Text101: @ 0x083793F1
		.string "サイバーエルフ{RED}ハンマーボ{RED_END}が入っていた！$"

Text102: @ 0x08379408
		.string "サイバーエルフ{RED}エイーナ{RED_END}が入っていた！$"

Text103: @ 0x0837941E
		.string "サイバーエルフ{RED}エコーイ{RED_END}が入っていた！$"

Text104: @ 0x08379434
		.string "サイバーエルフ{RED}エチューン{RED_END}が入っていた！$"

Text105: @ 0x0837944B
		.string "サイバーエルフ{RED}エナータ{RED_END}が入っていた！$"

Text106: @ 0x08379461
		.string "サイバーエルフ{RED}エワーネ{RED_END}が入っていた！$"

Text107: @ 0x08379477
		.string "エネルゲンすいしょう{RED}80EC{RED_END}ゲットした！$"

Text108: @ 0x0837948E
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text109: @ 0x083794A6
		.string "エネルゲンすいしょう{RED}200EC{RED_END}ゲットした！$"

Text110: @ 0x083794BE
		.string "エネルゲンすいしょう{RED}150EC{RED_END}ゲットした！$"

Text111: @ 0x083794D6
		.string "エネルゲンすいしょう{RED}40EC{RED_END}ゲットした！$"

Text112: @ 0x083794ED
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text113: @ 0x08379505
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text114: @ 0x0837951D
		.string "エネルゲンすいしょう{RED}50EC{RED_END}ゲットした！$"

Text115: @ 0x08379534
		.string "エネルゲンすいしょう{RED}80EC{RED_END}ゲットした！$"

Text116: @ 0x0837954B
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text117: @ 0x08379563
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text118: @ 0x0837957B
		.string "エネルゲンすいしょう{RED}40EC{RED_END}ゲットした！$"

Text119: @ 0x08379592
		.string "エネルゲンすいしょう{RED}500EC{RED_END}ゲットした！$"

Text120: @ 0x083795AA
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text121: @ 0x083795C2
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text122: @ 0x083795DA
		.string "エネルゲンすいしょう{RED}100EC{RED_END}ゲットした！$"

Text123: @ 0x083795F2
		.string "ヘッドチップ{RED}オートチャージ{RED_END}をゲットした！$"

Text124: @ 0x08379609
		.string "ヘッドチップ{RED}オートリカバリー{RED_END}をゲットした！$"

Text125: @ 0x08379621
		.string "ヘッドチップ{RED}クイックチャージ{RED_END}をゲットした！$"

Text126: @ 0x08379639
		.string "フットチップ{RED}フロッグ{RED_END}をゲットした！$"

Text127: @ 0x0837964D
		.string "フットチップ{RED}スプラッシュジャンプ{RED_END}をゲットした！$"

Text128: @ 0x08379667
		.string "フットチップ{RED}アルティメットフット{RED_END}をゲットした！$"

.balign 4, 0
