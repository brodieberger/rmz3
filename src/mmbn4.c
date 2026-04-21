#include "mmbn4.h"

#include "global.h"

// TODO: MMBN4との通信処理と、カードeリーダー周りの処理を別ファイルに分割できるか検討

static void sio_08001748(void);
static void* mmbn4_080016c8(void* r0);
void DisableSerial(void);

// clang-format off
// 0x080006c8
const struct Unk_080006c8 UnkMmbn4Datas[5] = {
    {(void*)0x02000fb0, (void*)0x02000db0, (void*)0x02000dc0, 4},
    {(void*)0x02000fb0, (void*)0x02000db0, (void*)0x02000eb0, 0},
    {(void*)0x02000fb0, (void*)0x02000db0, (void*)0x02000dc0, 4},
    {(void*)0x02000fb0, (void*)0x02000db0, (void*)0x02000dc0, 0},
    {(void*)0x02000fb0, (void*)0x02000db0, (void*)0x02000dc0, 4},
};
// clang-format on

NAKED static void clearMemory16(void* dst, u32 bytesize) {
  asm(".syntax unified\n\
	push {r0, r1, r2, r3, lr}\n\
	ldr r2, _08000734 @ =0x01000000\n\
	lsrs r1, r1, #1\n\
	orrs r2, r1\n\
	adds r1, r0, #0\n\
	sub sp, #4\n\
	movs r0, #0\n\
	str r0, [sp]\n\
	mov r0, sp\n\
	bl CpuSet\n\
	add sp, #4\n\
	pop {r0, r1, r2, r3, pc}\n\
	.align 2, 0\n\
_08000734: .4byte 0x01000000\n\
 .syntax divided\n");
}

// gUnk02000d50 に対して送受信バッファサイズ・通信速度・コールバックテーブルポインタなどをまとめてセットし、受信カードIDスロットを 0xFFFF でクリアするSIOコアの初期化関数です。
NAKED static void mmbn4_08000738(u32 r0, u32 r1, u32 r2, u32 r3) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	ldr r7, _08000794 @ =gUnk02000d50 TODO: この関数の外にあるラベルなのでこの関数あたりはCでは書かれてないと思われる \n\
	str r0, [r7, #0x20]\n\
	str r0, [r7, #0x24]\n\
	strb r2, [r7, #3]\n\
	strb r3, [r7, #2]\n\
	ldr r0, _08000770 @ =UnkMmbn4Datas\n\
	lsls r1, r1, #4\n\
	adds r0, r0, r1\n\
	ldr r1, [r0]\n\
	str r1, [r7, #0x34]\n\
	ldr r1, [r0, #4]\n\
	str r1, [r7, #0x38]\n\
	ldr r1, [r0, #8]\n\
	str r1, [r7, #0x3c]\n\
	ldrb r1, [r0, #0xc]\n\
	strb r1, [r7]\n\
	strb r1, [r7, #1]\n\
	movs r1, #0\n\
	strb r1, [r7, #5]\n\
	strb r1, [r7, #8]\n\
	strh r1, [r7, #0x18]\n\
	mvns r1, r1\n\
	strh r1, [r7, #0x10]\n\
	strh r1, [r7, #0x12]\n\
	strh r1, [r7, #0x14]\n\
	strh r1, [r7, #0x16]\n\
	pop {r4, r5, r6, r7, pc}\n\
	.align 2, 0\n\
_08000770: .4byte UnkMmbn4Datas\n\
 .syntax divided\n");
}

// gUnk02000d50 の +0x1c（送信バッファアドレス）、+0x0a（送信長）、+0x0e（フラグ）を設定するだけのセッター。
NAKED static void SioLink_SetTransmitParams(u32 r0, u16 r1, u16 r2) {
  asm(".syntax unified\n\
	push {r7, lr}\n\
	ldr r7, _08000780 @ =gUnk02000d50\n\
	str r0, [r7, #0x1c]\n\
	strh r1, [r7, #0xa]\n\
	strh r2, [r7, #0xe]\n\
	pop {r7, pc}\n\
	.align 2, 0\n\
_08000780: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

// 自分のプレイヤー番号（0〜3）を返すだけのゲッター
// 0x08000784
NAKED u32 SioLink_GetLocalPlayerId(void) {
  asm(".syntax unified\n\
	push {r7, lr}\n\
	ldr r7, _08000794 @ =gUnk02000d50\n\
	ldr r0, [r7, #0x48]\n\
	movs r1, #3\n\
	ands r0, r1\n\
	movs r0, r0\n\
	tst r0, r0\n\
	pop {r7, pc}\n\
	.align 2, 0\n\
_08000794: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

INCASM("asm/mmbn4.inc");

// SIO送信フラグの読み取り
// bool8: CPSR.Z
// 0x08001498
NAKED bool8 SioLink_GetTransmitFlags(void) {
  asm(".syntax unified\n\
	push {lr}\n\
	ldr r1, _080014A4 @ =gUnk02000d50\n\
	ldrh r0, [r1, #0xe]\n\
	tst r0, r0\n\
	pop {pc}\n\
	.align 2, 0\n\
_080014A4: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

// 受信バッファへの逐次コピー
// 0x080014A8
NAKED void EReader_CopyReceivedChunk(void) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	ldr r6, _080014E8 @ =gUnk02000d50\n\
	ldrb r0, [r6, #1]\n\
	cmp r0, #4\n\
	bne _080014DE\n\
	ldr r1, [r6, #0x2c]\n\
	ldr r0, [r6, #0x20]\n\
	cmp r1, r0\n\
	blt _080014C2\n\
	adds r0, r6, #0\n\
	bl SioLink_ResetSession\n\
	b _080014DE\n\
_080014C2:\n\
	ldr r1, [r6, #0x30]\n\
	movs r2, #0\n\
	ldr r7, _080014E0 @ =0x02000FB0\n\
	ldr r5, _080014E4 @ =0x020010C0\n\
_080014CA:\n\
	ldrh r0, [r5, r1]\n\
	strh r0, [r7, r2]\n\
	adds r1, #2\n\
	adds r2, #2\n\
	cmp r2, #0x10\n\
	blt _080014CA\n\
	movs r0, #0xe\n\
	ldr r1, [r6, #0x2c]\n\
	adds r1, r1, r0\n\
	str r1, [r6, #0x2c]\n\
_080014DE:\n\
	pop {r4, r5, r6, r7, pc}\n\
	.align 2, 0\n\
_080014E0: .4byte 0x02000FB0\n\
_080014E4: .4byte 0x020010C0\n\
_080014E8: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

// カード読み取りシーケンスの第2段階を開始する
// 0x080014EC
NAKED void EReader_SioBeginCardRead(void) {
  asm(".syntax unified\n\
	push {lr}\n\
	ldr r0, _08001504 @ =0x425A334A\n\
	ldr r1, _08001508 @ =0x08001510\n\
	ldrh r1, [r1]\n\
	movs r2, #0\n\
	bl SioLink_SetTransmitParams\n\
	ldr r0, _0800150C @ =0x020014C0\n\
	movs r1, #4\n\
	strb r1, [r0, #1]\n\
	pop {pc}\n\
	.align 2, 0\n\
_08001504: .4byte 0x425A334A\n\
_08001508: .4byte _08001510\n\
_0800150C: .4byte 0x020014C0\n\
_08001510:\n\
	.byte 0x10, 0x10, 0x00, 0x00\n\
 .syntax divided\n");
}

// 受信バッファからカードIDコードを取り出して返す
// 0x08001514
NAKED u16 EReader_SioGetCardId(void) {
  asm(".syntax unified\n\
	push {r4, r6, lr}\n\
	ldr r4, _08001530 @ =0x020014C0\n\
	movs r1, #0x38\n\
	ldrb r0, [r4]\n\
	tst r0, r0\n\
	beq _08001522\n\
	movs r1, #0x3c\n\
_08001522:\n\
	ldr r6, _08001534 @ =gUnk02000d50\n\
	ldr r2, [r6, r1]\n\
	ldrh r0, [r2]\n\
	ldrh r0, [r2, r0]\n\
	movs r1, #0xff\n\
	ands r0, r1\n\
	pop {r4, r6, pc}\n\
	.align 2, 0\n\
_08001530: .4byte 0x020014C0\n\
_08001534: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

// カードデータ本体の受信セッションを開始する
// 0x08001538
NAKED void EReader_SioInitDataReceive(void) {
  asm(".syntax unified\n\
	push {lr}\n\
	ldr r0, _0800156C @ =0x020014C0\n\
	movs r1, #0x20\n\
	bl clearMemory16\n\
	bl SioLink_ClearAllBuffers\n\
	movs r0, #0x10\n\
	movs r1, #2\n\
	movs r2, #4\n\
	movs r3, #0\n\
	bl mmbn4_08000738\n\
	movs r0, #0\n\
	movs r1, #0\n\
	ldr r2, _08001564 @ =0x00004000\n\
	bl FUN_0800165c\n\
	ldr r0, _08001568 @ =gUnk02000d50\n\
	movs r1, #0x3c\n\
	strh r1, [r0, #0xc]\n\
	pop {pc}\n\
	.align 2, 0\n\
_08001564: .4byte 0x00004000\n\
_08001568: .4byte gUnk02000d50\n\
_0800156C: .4byte 0x020014C0\n\
 .syntax divided\n");
}

// 受信データのチェックサム照合・保存データとの整合性検証
// 0x08001570
NAKED u8 EReader_SioVerifyCardData(void) {
  asm(".syntax unified\n\
	push {r5, r6, r7, lr}\n\
	movs r6, #2\n\
	bl EReader_SioCheckAllPlayersConnected\n\
	bne _0800159C\n\
	bl SioLink_LoadSendCmds\n\
	beq _0800159C\n\
	bl EReader_ValidateAndStoreCardId\n\
	bne _080015A0\n\
	ldr r5, _080015A4 @ =0x020014C0\n\
	ldrh r0, [r5, #0x10]\n\
	movs r1, #0\n\
	movs r2, #0xa\n\
	movs r3, #4\n\
	ldrh r0, [r5, #0x12]\n\
	movs r1, #0\n\
	movs r2, #0xb\n\
	movs r3, #4\n\
	movs r6, #0\n\
	b _080015A0\n\
_0800159C:\n\
	movs r6, #1\n\
	mov r8, r8\n\
_080015A0:\n\
	adds r0, r6, #0\n\
	pop {r5, r6, r7, pc}\n\
	.align 2, 0\n\
_080015A4: .4byte 0x020014C0\n\
 .syntax divided\n");
}

// 送信コマンドバッファの読み出し
// 0x080015a8
NAKED bool8 SioLink_LoadSendCmds(void) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	bl SioLink_ReadSendCmdSlots\n\
	ldr r4, _080015C0 @ =0x0000A380\n\
	cmp r0, r4\n\
	beq _080015BE\n\
	cmp r1, r4\n\
	beq _080015BE\n\
	cmp r2, r4\n\
	beq _080015BE\n\
	cmp r3, r4\n\
_080015BE:\n\
	pop {r4, pc}\n\
	.align 2, 0\n\
_080015C0: .4byte 0x0000A380\n\
 .syntax divided\n");
}

// bool8: CPSR.Z
NAKED bool8 EReader_ValidateAndStoreCardId(void) {
  asm(".syntax unified\n\
	push {r5, lr}\n\
	ldr r5, _080015E4 @ =0x020014C0\n\
	movs r0, #4\n\
	bl FUN_08000ed4\n\
	tst r1, r1\n\
	bne _080015D8\n\
	strh r2, [r5, #0x10]\n\
	strh r0, [r5, #0x12]\n\
	pop {r5, pc}\n\
_080015D8:\n\
	movs r0, #0\n\
	mvns r0, r0\n\
	strh r0, [r5, #0x12]\n\
	strh r0, [r5, #0x10]\n\
	pop {r5, pc}\n\
	.align 2, 0\n\
_080015E4: .4byte 0x020014C0\n\
 .syntax divided\n");
}

// 接続プレイヤー状態の集計
// 4プレイヤー分の SioLink_GetPlayerStatus を呼び出してステータスを配列に記録し、SIO制御ブロック（gUnk02000d50+0x48）から期待接続数を取得して一致するか確認します。「eカードリーダー側（プレイヤー1/2）が接続済みか」を判定しているのがポイントです。
// 0x080015e8
NAKED u8 EReader_SioCheckAllPlayersConnected(void) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	movs r6, #2\n\
	bl SioLink_PollAndDispatch\n\
	cmp r0, #2\n\
	beq _080015FA\n\
	cmp r0, #4\n\
	beq _0800164A\n\
	b _0800164C\n\
_080015FA:\n\
	movs r0, #0\n\
	bl FUN_08001690\n\
	cmp r0, #0xff\n\
	beq _0800164C\n\
	ldr r4, _08001654 @ =0x020014C0\n\
	movs r3, #0xc\n\
	movs r7, #0\n\
	movs r5, #0\n\
_0800160C:\n\
	adds r0, r7, #0\n\
	bl SioLink_GetPlayerStatus\n\
	strb r0, [r4, r3]\n\
	cmp r0, #2\n\
	bne _08001626\n\
	cmp r7, #1\n\
	beq _08001620\n\
	cmp r7, #2\n\
	bne _08001634\n\
_08001620:\n\
	adds r5, #1\n\
	movs r6, #0\n\
	b _08001634\n\
_08001626:\n\
	cmp r0, #1\n\
	bne _08001634\n\
	cmp r7, #0\n\
	beq _08001632\n\
	cmp r7, #3\n\
	bne _08001634\n\
_08001632:\n\
	adds r5, #1\n\
_08001634:\n\
	adds r3, #1\n\
	adds r7, #1\n\
	cmp r7, #4\n\
	blt _0800160C\n\
	ldr r1, _08001658 @ =gUnk02000d50\n\
	ldr r0, [r1, #0x48]\n\
	movs r1, #0x1c\n\
	ands r0, r1\n\
	lsrs r0, r0, #2\n\
	cmp r5, r0\n\
	beq _0800164C\n\
_0800164A:\n\
	movs r6, #1\n\
_0800164C:\n\
	adds r0, r6, #0\n\
	tst r6, r6\n\
	pop {r4, r5, r6, r7, pc}\n\
	.align 2, 0\n\
_08001654: .4byte 0x020014C0\n\
_08001658: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

NAKED void FUN_0800165c(u16 param_1, u16 param_2, u16 param_3) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	ldr r4, _08001688 @ =0x02000FB0\n\
	strh r0, [r4, #8]\n\
	strh r1, [r4, #6]\n\
	strh r2, [r4, #4]\n\
	ldr r0, _0800168C @ =0x4234574A\n\
	str r0, [r4]\n\
	movs r0, #0x3c\n\
	strh r0, [r4, #0xa]\n\
	pop {r4, pc}\n\
 .syntax divided\n");
}

NAKED void FUN_08001670(u16 param_1, u16 param_2, u16 param_3) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	bl FUN_0800165c\n\
	ldr r4, _08001688 @ =0x02000FB0\n\
	bl GetLastSendQueueCount\n\
	strh r0, [r4, #0xc]\n\
	bl GetLastRecvQueueCount\n\
	strh r0, [r4, #0xe]\n\
	pop {r4, pc}\n\
	.align 2, 0\n\
_08001688: .4byte 0x02000FB0\n\
_0800168C: .4byte 0x4234574A\n\
 .syntax divided\n");
}

NAKED void* FUN_08001690(u32 r0) {
  asm(".syntax unified\n\
	push {r4, r6, r7, lr}\n\
	lsls r0, r0, #2\n\
	adds r7, r0, #0\n\
	bl SioLink_GetLocalPlayerId\n\
	beq _0800169E\n\
	movs r0, #1\n\
_0800169E:\n\
	ldr r4, _08001728 @ =0x020014C0\n\
	strb r0, [r4]\n\
	ldr r1, _0800172C @ =0x08001730\n\
	ldr r6, [r1, #4]\n\
	tst r0, r0\n\
	beq _080016AC\n\
	ldr r6, [r1]\n\
_080016AC:\n\
	ldr r0, [r6]\n\
	ldr r1, _08001738 @ =0x4234574A\n\
	cmp r0, r1\n\
	bne _080016C2\n\
	ldrh r0, [r6, #4]\n\
	ldr r1, _0800173C @ =0x08001740\n\
	ldr r1, [r1, r7]\n\
	cmp r0, r1\n\
	bne _080016C2\n\
	adds r0, r6, #0\n\
	b _080016C4\n\
_080016C2:\n\
	movs r0, #0xff\n\
_080016C4:\n\
	pop {r4, r6, r7, pc}\n\
	.align 2, 0\n\
 .syntax divided\n");
}

NAKED static void* mmbn4_080016c8(void* r0) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	lsls r0, r0, #2\n\
	adds r7, r0, #0\n\
	bl SioLink_GetLocalPlayerId\n\
	beq _080016D6\n\
	movs r0, #1\n\
_080016D6:\n\
	ldr r4, _08001728 @ =0x020014C0\n\
	strb r0, [r4]\n\
	movs r5, #0\n\
_080016DC:\n\
	ldr r1, _0800172C @ =0x08001730\n\
	ldr r6, [r1, #4]\n\
	tst r5, r5\n\
	bne _080016E6\n\
	ldr r6, [r1]\n\
_080016E6:\n\
	ldr r0, [r6]\n\
	ldr r1, _08001738 @ =0x4234574A\n\
	cmp r0, r1\n\
	bne _080016FC\n\
	ldrh r0, [r6, #4]\n\
	ldr r1, _0800173C @ =0x08001740\n\
	ldr r1, [r1, r7]\n\
	cmp r0, r1\n\
	bne _080016FC\n\
	bl sio_08001748\n\
_080016FC:\n\
	adds r5, #1\n\
	cmp r5, #2\n\
	blt _080016DC\n\
	ldr r1, _0800172C @ =0x08001730\n\
	ldr r6, [r1, #4]\n\
	ldrb r5, [r4]\n\
	tst r5, r5\n\
	beq _0800170E\n\
	ldr r6, [r1]\n\
_0800170E:\n\
	ldr r0, [r6]\n\
	ldr r1, _08001738 @ =0x4234574A\n\
	cmp r0, r1\n\
	bne _08001724\n\
	ldrh r0, [r6, #4]\n\
	ldr r1, _0800173C @ =0x08001740\n\
	ldr r1, [r1, r7]\n\
	cmp r0, r1\n\
	bne _08001724\n\
	adds r0, r6, #0\n\
	b _08001726\n\
_08001724:\n\
	movs r0, #0xff\n\
_08001726:\n\
	pop {r4, r5, r6, r7, pc}\n\
	.align 2, 0\n\
_08001728: .4byte 0x020014C0\n\
_0800172C: .4byte _08001730\n\
_08001730: .4byte Unk02000db0, Unk02000dc0\n\
_08001738: .4byte 0x4234574A\n\
_0800173C: .4byte _08001740\n\
_08001740:\n\
	.byte 0x00, 0x40, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00\n\
 .syntax divided\n");
}

NAKED static void sio_08001748(void) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	ldrb r1, [r6, #0xc]\n\
	cmp r1, #5\n\
	bgt _08001756\n\
	ldrb r1, [r6, #0xe]\n\
	cmp r1, #5\n\
	ble _08001770\n\
_08001756:\n\
	ldr r4, _08001774 @ =gUnk02000d50\n\
	adds r0, r1, #0\n\
	cmp r1, r2\n\
	bge _08001760\n\
	adds r0, r2, #0\n\
_08001760:\n\
	adds r0, #8\n\
	ldr r1, [r4, #0x54]\n\
	cmp r0, r1\n\
	bge _0800176A\n\
	adds r0, r1, #0\n\
_0800176A:\n\
	str r0, [r4, #0x54]\n\
	movs r0, #0xc\n\
	strb r0, [r4]\n\
_08001770:\n\
	pop {r4, pc}\n\
	.align 2, 0\n\
_08001774: .4byte gUnk02000d50\n\
 .syntax divided\n");
}

void EReader_SioAbortSession(void) {
  DisableSerial();
  return;
}
