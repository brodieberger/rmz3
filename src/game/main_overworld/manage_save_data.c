#include "game.h"
#include "global.h"
#include "text.h"

s16 save_080f32f8(struct GameState*);
void PrintSaveDataRow(s32 idx, u8 rank, u32 playTime, u8 lap, u8 mode, u8 y8);

// DEKASUGI!!!
// 0x080f0658
NAKED void OverworldLoop_ManageSaveData(struct GameState* g) {
  asm(".syntax unified\n\
.if REGION_US\n\
	push	{r4, r5, r6, r7, lr}\n\
	mov	r7, sl\n\
	mov	r6, r9\n\
	mov	r5, r8\n\
	push	{r5, r6, r7}\n\
	sub	sp, #8\n\
	adds	r6, r0, #0\n\
	ldrb	r0, [r6, #3]\n\
	subs	r0, #63\n\
	cmp	r0, #55\n\
	bls _US_080F01CE\n\
	bl _US_080F0C2C\n\
_US_080F01CE:\n\
	lsls	r0, r0, #2\n\
	ldr	r1, _US_080F01D8\n\
	adds	r0, r0, r1\n\
	ldr	r0, [r0, #0]\n\
	mov	pc, r0\n\
	.align 2, 0\n\
_US_080F01D8: .4byte _US_080F01DC\n\
_US_080F01DC:\n\
	.4byte _US_080F02BC\n\
	.4byte _US_080F02DC\n\
	.4byte _US_080F02FC\n\
	.4byte _US_080F0350\n\
	.4byte _US_080F0368\n\
	.4byte _US_080F0408\n\
	.4byte _US_080F041A\n\
	.4byte _US_080F07E8\n\
	.4byte _US_080F07F8\n\
	.4byte _US_080F08AC\n\
	.4byte _US_080F0358\n\
	.4byte _US_080F0368\n\
	.4byte _US_080F0408\n\
	.4byte _US_080F041A\n\
	.4byte _US_080F08D8\n\
	.4byte _US_080F08E8\n\
	.4byte _US_080F096C\n\
	.4byte _US_080F09C2\n\
	.4byte _US_080F0A08\n\
	.4byte _US_080F0360\n\
	.4byte _US_080F0368\n\
	.4byte _US_080F0408\n\
	.4byte _US_080F041A\n\
	.4byte _US_080F0B6C\n\
	.4byte _US_080F0B7C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0358\n\
	.4byte _US_080F0368\n\
	.4byte _US_080F0408\n\
	.4byte _US_080F041A\n\
	.4byte _US_080F08D8\n\
	.4byte _US_080F08E8\n\
	.4byte _US_080F096C\n\
	.4byte _US_080F09C2\n\
	.4byte _US_080F0A08\n\
	.4byte _US_080F0BF6\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0C2C\n\
	.4byte _US_080F0350\n\
	.4byte _US_080F0368\n\
	.4byte _US_080F0408\n\
	.4byte _US_080F041A\n\
	.4byte _US_080F07E8\n\
	.4byte _US_080F07F8\n\
	.4byte _US_080F08AC\n\
_US_080F02BC:\n\
	ldr	r2, _US_080F02D0\n\
	ldrh	r0, [r2, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F02D4\n\
	ldrh	r1, [r2, #0]\n\
	movs	r0, #2\n\
	orrs	r0, r1\n\
	strh	r0, [r2, #0]\n\
	bl _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F02D0: .4byte gTextWindow+0x8\n\
_US_080F02D4:\n\
	movs	r1, #128\n\
	lsls	r1, r1, #3\n\
	bl _US_080F0B60\n\
_US_080F02DC:\n\
	ldr	r0, _US_080F0330\n\
	ldrh	r0, [r0, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F02EC\n\
	cmp	r0, #4\n\
	beq _US_080F02EC\n\
	bl _US_080F0C2C\n\
_US_080F02EC:\n\
	movs	r0, #2\n\
	bl PrintOptionMessage1\n\
	movs	r0, #0\n\
	strh	r0, [r6, #10]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F02FC:\n\
	ldr	r0, _US_080F0330\n\
	ldrh	r0, [r0, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F030C\n\
	cmp	r0, #4\n\
	beq _US_080F030C\n\
	bl _US_080F0C2C\n\
_US_080F030C:\n\
	adds	r0, r6, #0\n\
	bl save_080f32f8\n\
	lsls	r0, r0, #16\n\
	lsrs	r2, r0, #16\n\
	cmp	r0, #0\n\
	bne _US_080F031E\n\
	bl _US_080F0C2C\n\
_US_080F031E:\n\
	lsls	r0, r2, #16\n\
	asrs	r0, r0, #16\n\
	cmp	r0, #1\n\
	bne _US_080F0334\n\
	movs	r0, #66\n\
	strb	r0, [r6, #3]\n\
	bl _US_080F0C2C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0330: .4byte gTextWindow+0x8\n\
_US_080F0334:\n\
	cmp	r0, #2\n\
	bne _US_080F0340\n\
	movs	r0, #73\n\
	strb	r0, [r6, #3]\n\
	bl _US_080F0C2C\n\
_US_080F0340:\n\
	cmp	r0, #3\n\
	bne _US_080F0348\n\
	bl _US_080F0BF0\n\
_US_080F0348:\n\
	movs	r0, #63\n\
	strb	r0, [r6, #3]\n\
	bl _US_080F0C2C\n\
_US_080F0350:\n\
	movs	r0, #3\n\
	bl PrintOptionMessage1\n\
	b _US_080F094C\n\
_US_080F0358:\n\
	movs	r0, #5\n\
	bl PrintOptionMessage1\n\
	b _US_080F094C\n\
_US_080F0360:\n\
	movs	r0, #7\n\
	bl PrintOptionMessage1\n\
	b _US_080F094C\n\
_US_080F0368:\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0520\n\
	mov	sl, r0\n\
	ldr	r7, _US_080F0524\n\
	ldr	r1, _US_080F0528\n\
	adds	r1, r1, r7\n\
	mov	r9, r1\n\
_US_080F0376:\n\
	lsls	r4, r2, #16\n\
	asrs	r0, r4, #16\n\
	add	r0, sl\n\
	movs	r1, #0\n\
	strb	r1, [r0, #0]\n\
	lsls	r0, r2, #24\n\
	lsrs	r5, r0, #24\n\
	adds	r0, r5, #0\n\
	movs	r1, #148\n\
	lsls	r1, r1, #2\n\
	bl ValidateSector\n\
	mov	r8, r4\n\
	cmp	r0, #0\n\
	beq _US_080F03F4\n\
	adds	r0, r5, #0\n\
	ldr	r1, _US_080F052C\n\
	movs	r2, #148\n\
	lsls	r2, r2, #2\n\
	bl sram_08003378\n\
	ldr	r4, _US_080F0530\n\
_US_080F03A2:\n\
	bl UpdateSram\n\
	ldrb	r0, [r4, #0]\n\
	cmp	r0, #1\n\
	beq _US_080F03A2\n\
	movs	r2, #30\n\
	ldrsh	r0, [r4, r2]\n\
	cmp	r0, #0\n\
	beq _US_080F03A2\n\
	ldr	r1, _US_080F0530\n\
	ldrb	r0, [r1, #0]\n\
	cmp	r0, #1\n\
	beq _US_080F03F4\n\
	movs	r3, #30\n\
	ldrsh	r0, [r1, r3]\n\
	cmp	r0, #0\n\
	ble _US_080F03F4\n\
	mov	r5, r8\n\
	asrs	r3, r5, #16\n\
	mov	r0, sl\n\
	adds	r1, r3, r0\n\
	movs	r0, #1\n\
	strb	r0, [r1, #0]\n\
	ldr	r1, _US_080F0534\n\
	lsls	r2, r3, #2\n\
	adds	r1, r2, r1\n\
	ldr	r0, [r7, #12]\n\
	str	r0, [r1, #0]\n\
	ldr	r0, _US_080F0538\n\
	adds	r2, r2, r0\n\
	ldrb	r0, [r7, #1]\n\
	str	r0, [r2, #0]\n\
	ldr	r0, _US_080F053C\n\
	adds	r0, r3, r0\n\
	mov	r2, r9\n\
	ldrh	r1, [r2, #0]\n\
	strb	r1, [r0, #0]\n\
	ldr	r0, _US_080F0540\n\
	adds	r3, r3, r0\n\
	ldrh	r0, [r2, #2]\n\
	strb	r0, [r3, #0]\n\
_US_080F03F4:\n\
	movs	r0, #128\n\
	lsls	r0, r0, #9\n\
	add	r0, r8\n\
	lsrs	r2, r0, #16\n\
	asrs	r0, r0, #16\n\
	cmp	r0, #4\n\
	ble _US_080F0376\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F0408:\n\
	movs	r0, #0\n\
	strh	r0, [r6, #4]\n\
	strh	r0, [r6, #6]\n\
	strh	r0, [r6, #8]\n\
	movs	r0, #15\n\
	strh	r0, [r6, #10]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F041A:\n\
	ldr	r0, _US_080F0544\n\
	ldrh	r0, [r0, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F042A\n\
	cmp	r0, #4\n\
	beq _US_080F042A\n\
	bl _US_080F0C2C\n\
_US_080F042A:\n\
	movs	r3, #4\n\
	ldrsh	r0, [r6, r3]\n\
	cmp	r0, #3\n\
	bgt _US_080F044A\n\
	ldr	r0, _US_080F0548\n\
	ldrh	r1, [r0, #6]\n\
	movs	r0, #128\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F044A\n\
	movs	r0, #1\n\
	bl PlaySound\n\
	ldrh	r0, [r6, #4]\n\
	adds	r0, #1\n\
	strh	r0, [r6, #4]\n\
_US_080F044A:\n\
	movs	r5, #4\n\
	ldrsh	r0, [r6, r5]\n\
	cmp	r0, #0\n\
	ble _US_080F046A\n\
	ldr	r0, _US_080F0548\n\
	ldrh	r1, [r0, #6]\n\
	movs	r0, #64\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F046A\n\
	movs	r0, #1\n\
	bl PlaySound\n\
	ldrh	r0, [r6, #4]\n\
	subs	r0, #1\n\
	strh	r0, [r6, #4]\n\
_US_080F046A:\n\
	ldrh	r3, [r6, #4]\n\
	movs	r0, #4\n\
	ldrsh	r1, [r6, r0]\n\
	movs	r2, #6\n\
	ldrsh	r0, [r6, r2]\n\
	adds	r2, r3, #0\n\
	cmp	r1, r0\n\
	bge _US_080F047C\n\
	strh	r2, [r6, #6]\n\
_US_080F047C:\n\
	movs	r5, #4\n\
	ldrsh	r1, [r6, r5]\n\
	movs	r2, #6\n\
	ldrsh	r0, [r6, r2]\n\
	adds	r0, #1\n\
	cmp	r1, r0\n\
	ble _US_080F048E\n\
	subs	r0, r3, #1\n\
	strh	r0, [r6, #6]\n\
_US_080F048E:\n\
	movs	r2, #0\n\
_US_080F0490:\n\
	lsls	r0, r2, #16\n\
	asrs	r5, r0, #16\n\
	movs	r3, #6\n\
	ldrsh	r1, [r6, r3]\n\
	subs	r1, r5, r1\n\
	lsls	r1, r1, #25\n\
	lsrs	r4, r1, #24\n\
	lsls	r7, r4, #24\n\
	lsrs	r1, r7, #24\n\
	mov	r8, r0\n\
	cmp	r1, #2\n\
	bhi _US_080F0582\n\
	ldr	r0, _US_080F0520\n\
	adds	r0, r5, r0\n\
	ldrb	r0, [r0, #0]\n\
	cmp	r0, #0\n\
	bne _US_080F0554\n\
	ldr	r1, _US_080F054C\n\
	adds	r0, r5, #0\n\
	adds	r0, #31\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0550\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r1, _US_080F0544\n\
	ldrb	r0, [r1, #6]\n\
	cmp	r0, #0\n\
	bne _US_080F04D2\n\
	ldrb	r0, [r1, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F04D4\n\
_US_080F04D2:\n\
	movs	r2, #1\n\
_US_080F04D4:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #9\n\
	subs	r1, r1, r0\n\
	ldr	r5, _US_080F0544\n\
	lsls	r4, r4, #24\n\
	asrs	r2, r4, #24\n\
	adds	r2, #2\n\
	ldrb	r0, [r5, #5]\n\
	adds	r2, r2, r0\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldr	r0, _US_080F054C\n\
	ldrh	r1, [r0, #2]\n\
	ldr	r0, _US_080F0550\n\
	adds	r3, r1, r0\n\
	movs	r1, #0\n\
	ldrb	r0, [r5, #6]\n\
	cmp	r0, #0\n\
	bne _US_080F0504\n\
	ldrb	r0, [r5, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F0506\n\
_US_080F0504:\n\
	movs	r1, #1\n\
_US_080F0506:\n\
	lsls	r0, r1, #3\n\
	subs	r0, r0, r1\n\
	movs	r1, #11\n\
	subs	r1, r1, r0\n\
	ldr	r0, _US_080F0544\n\
	asrs	r2, r4, #24\n\
	adds	r2, #2\n\
	ldrb	r0, [r0, #5]\n\
	adds	r2, r2, r0\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	b _US_080F0582\n\
	.align 2, 0\n\
_US_080F0520: .4byte gSaveSlotMetadata\n\
_US_080F0524: .4byte SaveState_020003a8+0x1b4\n\
_US_080F0528: .4byte 0xFFFFFE4C\n\
_US_080F052C: .4byte SaveState_020003a8\n\
_US_080F0530: .4byte gSramState\n\
_US_080F0534: .4byte gSaveSlotMetadata+0x8\n\
_US_080F0538: .4byte gSaveSlotMetadata+0x20\n\
_US_080F053C: .4byte gSaveSlotMetadata+0x34\n\
_US_080F0540: .4byte gSaveSlotMetadata+0x3c\n\
_US_080F0544: .4byte gTextWindow+0x8\n\
_US_080F0548: .4byte gJoypad\n\
_US_080F054C: .4byte StringOfsTable\n\
_US_080F0550: .4byte gStringData\n\
_US_080F0554:\n\
	lsls	r0, r2, #24\n\
	lsrs	r0, r0, #24\n\
	ldr	r1, _US_080F065C\n\
	lsls	r3, r5, #2\n\
	adds	r1, r3, r1\n\
	ldrb	r1, [r1, #0]\n\
	ldr	r2, _US_080F0660\n\
	adds	r3, r3, r2\n\
	ldr	r2, [r3, #0]\n\
	ldr	r3, _US_080F0664\n\
	adds	r3, r5, r3\n\
	ldrb	r3, [r3, #0]\n\
	ldr	r4, _US_080F0668\n\
	adds	r4, r5, r4\n\
	ldrb	r4, [r4, #0]\n\
	str	r4, [sp, #0]\n\
	movs	r5, #128\n\
	lsls	r5, r5, #18\n\
	adds	r4, r7, r5\n\
	lsrs	r4, r4, #24\n\
	str	r4, [sp, #4]\n\
	bl PrintSaveDataRow\n\
_US_080F0582:\n\
	movs	r0, #128\n\
	lsls	r0, r0, #9\n\
	add	r0, r8\n\
	lsrs	r2, r0, #16\n\
	asrs	r0, r0, #16\n\
	cmp	r0, #4\n\
	bgt _US_080F0592\n\
	b _US_080F0490\n\
_US_080F0592:\n\
	ldr	r0, _US_080F066C\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0670\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0674\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F05AC\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F05AE\n\
_US_080F05AC:\n\
	movs	r2, #1\n\
_US_080F05AE:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #8\n\
	subs	r1, r1, r0\n\
	movs	r0, #4\n\
	ldrsh	r2, [r6, r0]\n\
	movs	r5, #6\n\
	ldrsh	r0, [r6, r5]\n\
	subs	r2, r2, r0\n\
	lsls	r2, r2, #1\n\
	adds	r2, #2\n\
	ldrb	r0, [r4, #5]\n\
	adds	r2, r2, r0\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldrh	r0, [r6, #8]\n\
	adds	r0, #1\n\
	strh	r0, [r6, #8]\n\
	movs	r1, #16\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F05DE\n\
	b _US_080F06E0\n\
_US_080F05DE:\n\
	movs	r2, #0\n\
	ldrb	r0, [r4, #6]\n\
	cmp	r0, #0\n\
	bne _US_080F05EC\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F05EE\n\
_US_080F05EC:\n\
	movs	r2, #1\n\
_US_080F05EE:\n\
	lsls	r1, r2, #3\n\
	subs	r1, r1, r2\n\
	movs	r0, #8\n\
	subs	r0, r0, r1\n\
	cmp	r0, #3\n\
	ble _US_080F0680\n\
	movs	r1, #6\n\
	ldrsh	r0, [r6, r1]\n\
	cmp	r0, #0\n\
	beq _US_080F062A\n\
	ldr	r3, _US_080F0678\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0674\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F0616\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F0618\n\
_US_080F0616:\n\
	movs	r2, #1\n\
_US_080F0618:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #28\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r2, #2\n\
	adds	r0, r3, #0\n\
	bl PrintUnicodeString\n\
_US_080F062A:\n\
	movs	r2, #6\n\
	ldrsh	r0, [r6, r2]\n\
	cmp	r0, #3\n\
	beq _US_080F06E0\n\
	ldr	r3, _US_080F067C\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0674\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F0646\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F0648\n\
_US_080F0646:\n\
	movs	r2, #1\n\
_US_080F0648:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #28\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r2, #5\n\
	adds	r0, r3, #0\n\
	bl PrintUnicodeString\n\
	b _US_080F06E0\n\
	.align 2, 0\n\
_US_080F065C: .4byte gSaveSlotMetadata+0x20\n\
_US_080F0660: .4byte gSaveSlotMetadata+0x8\n\
_US_080F0664: .4byte gSaveSlotMetadata+0x34\n\
_US_080F0668: .4byte gSaveSlotMetadata+0x3c\n\
_US_080F066C: .4byte StringOfsTable\n\
_US_080F0670: .4byte gStringData\n\
_US_080F0674: .4byte gTextWindow+0x8\n\
_US_080F0678: .4byte Unicode_CursorUp\n\
_US_080F067C: .4byte Unicode_CursorDown\n\
_US_080F0680:\n\
	movs	r3, #6\n\
	ldrsh	r0, [r6, r3]\n\
	cmp	r0, #0\n\
	beq _US_080F06B0\n\
	ldr	r3, _US_080F06F0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F06F4\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F069C\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F069E\n\
_US_080F069C:\n\
	movs	r2, #1\n\
_US_080F069E:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #7\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r2, #2\n\
	adds	r0, r3, #0\n\
	bl PrintUnicodeString\n\
_US_080F06B0:\n\
	movs	r5, #6\n\
	ldrsh	r0, [r6, r5]\n\
	cmp	r0, #3\n\
	beq _US_080F06E0\n\
	ldr	r3, _US_080F06F8\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F06F4\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F06CC\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F06CE\n\
_US_080F06CC:\n\
	movs	r2, #1\n\
_US_080F06CE:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #7\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r2, #5\n\
	adds	r0, r3, #0\n\
	bl PrintUnicodeString\n\
_US_080F06E0:\n\
	ldrh	r1, [r6, #10]\n\
	movs	r2, #10\n\
	ldrsh	r0, [r6, r2]\n\
	cmp	r0, #0\n\
	beq _US_080F06FC\n\
	subs	r0, r1, #1\n\
	strh	r0, [r6, #10]\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F06F0: .4byte Unicode_CursorUp\n\
_US_080F06F4: .4byte gTextWindow+0x8\n\
_US_080F06F8: .4byte Unicode_CursorDown\n\
_US_080F06FC:\n\
	ldr	r0, _US_080F0728\n\
	ldrh	r1, [r0, #4]\n\
	movs	r4, #2\n\
	adds	r0, r4, #0\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F073C\n\
	movs	r0, #3\n\
	bl PlaySound\n\
	ldrb	r0, [r6, #3]\n\
	cmp	r0, #99\n\
	bne _US_080F0730\n\
	ldr	r0, _US_080F072C\n\
	movs	r3, #170\n\
	lsls	r3, r3, #1\n\
	adds	r0, r0, r3\n\
	str	r4, [r0, #0]\n\
	movs	r0, #105\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0728: .4byte gJoypad\n\
_US_080F072C: .4byte gStageRun\n\
_US_080F0730:\n\
	cmp	r0, #115\n\
	beq _US_080F0736\n\
	b _US_080F0BDC\n\
_US_080F0736:\n\
	movs	r0, #124\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
_US_080F073C:\n\
	movs	r0, #1\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	bne _US_080F0746\n\
	b _US_080F0C2C\n\
_US_080F0746:\n\
	ldrb	r0, [r6, #3]\n\
	cmp	r0, #69\n\
	beq _US_080F0750\n\
	cmp	r0, #115\n\
	bne _US_080F07C6\n\
_US_080F0750:\n\
	movs	r0, #2\n\
	bl PlaySound\n\
	ldr	r0, _US_080F07A8\n\
	movs	r5, #4\n\
	ldrsh	r1, [r6, r5]\n\
	adds	r1, r1, r0\n\
	ldrb	r0, [r1, #0]\n\
	cmp	r0, #0\n\
	beq _US_080F0766\n\
	b _US_080F094C\n\
_US_080F0766:\n\
	ldr	r1, _US_080F07AC\n\
	adds	r0, r6, r1\n\
	bl StoreStoryData\n\
	ldr	r2, _US_080F07B0\n\
	adds	r0, r6, r2\n\
	ldr	r0, [r0, #0]\n\
	ldr	r3, _US_080F07B4\n\
	adds	r1, r6, r3\n\
	bl StoreZeroStatus\n\
	ldrb	r0, [r6, #4]\n\
	ldr	r1, _US_080F07B8\n\
	movs	r2, #148\n\
	lsls	r2, r2, #2\n\
	bl sram_08003330\n\
	ldr	r4, _US_080F07BC\n\
_US_080F078A:\n\
	bl UpdateSram\n\
	ldrb	r0, [r4, #0]\n\
	cmp	r0, #2\n\
	beq _US_080F078A\n\
	movs	r5, #28\n\
	ldrsh	r0, [r4, r5]\n\
	cmp	r0, #0\n\
	beq _US_080F078A\n\
	ldrb	r0, [r6, #3]\n\
	cmp	r0, #69\n\
	bne _US_080F07C0\n\
	movs	r0, #72\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F07A8: .4byte gSaveSlotMetadata\n\
_US_080F07AC: .4byte 0x00006270\n\
_US_080F07B0: .4byte 0x000064AC\n\
_US_080F07B4: .4byte 0x00006460\n\
_US_080F07B8: .4byte gGameState+0x625c\n\
_US_080F07BC: .4byte gSramState\n\
_US_080F07C0:\n\
	movs	r0, #118\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
_US_080F07C6:\n\
	ldr	r0, _US_080F07DC\n\
	movs	r2, #4\n\
	ldrsh	r1, [r6, r2]\n\
	adds	r1, r1, r0\n\
	ldrb	r0, [r1, #0]\n\
	cmp	r0, #0\n\
	bne _US_080F07E0\n\
	movs	r0, #4\n\
	bl PlaySound\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F07DC: .4byte gSaveSlotMetadata\n\
_US_080F07E0:\n\
	movs	r0, #2\n\
	bl PlaySound\n\
	b _US_080F094C\n\
_US_080F07E8:\n\
	movs	r0, #4\n\
	bl PrintOptionMessage1\n\
	movs	r0, #1\n\
	strh	r0, [r6, #10]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F07F8:\n\
	ldr	r1, _US_080F088C\n\
	movs	r3, #4\n\
	ldrsh	r0, [r6, r3]\n\
	adds	r0, #31\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0890\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0894\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F081C\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F081E\n\
_US_080F081C:\n\
	movs	r2, #1\n\
_US_080F081E:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #8\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldrh	r0, [r4, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F083A\n\
	cmp	r0, #4\n\
	beq _US_080F083A\n\
	b _US_080F0C2C\n\
_US_080F083A:\n\
	adds	r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls	r0, r0, #16\n\
	lsrs	r2, r0, #16\n\
	cmp	r0, #0\n\
	bne _US_080F084A\n\
	b _US_080F0C2C\n\
_US_080F084A:\n\
	lsls	r0, r2, #16\n\
	cmp	r0, #0\n\
	bgt _US_080F0852\n\
	b _US_080F0964\n\
_US_080F0852:\n\
	ldr	r5, _US_080F0898\n\
	adds	r0, r6, r5\n\
	bl StoreStoryData\n\
	ldr	r1, _US_080F089C\n\
	adds	r0, r6, r1\n\
	ldr	r0, [r0, #0]\n\
	ldr	r2, _US_080F08A0\n\
	adds	r1, r6, r2\n\
	bl StoreZeroStatus\n\
	ldrb	r0, [r6, #4]\n\
	ldr	r1, _US_080F08A4\n\
	movs	r2, #148\n\
	lsls	r2, r2, #2\n\
	bl sram_08003330\n\
	ldr	r4, _US_080F08A8\n\
_US_080F0876:\n\
	bl UpdateSram\n\
	ldrb	r0, [r4, #0]\n\
	cmp	r0, #2\n\
	beq _US_080F0876\n\
	movs	r3, #28\n\
	ldrsh	r0, [r4, r3]\n\
	cmp	r0, #0\n\
	beq _US_080F0876\n\
	b _US_080F094C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F088C: .4byte StringOfsTable\n\
_US_080F0890: .4byte gStringData\n\
_US_080F0894: .4byte gTextWindow+0x8\n\
_US_080F0898: .4byte 0x00006270\n\
_US_080F089C: .4byte 0x000064AC\n\
_US_080F08A0: .4byte 0x00006460\n\
_US_080F08A4: .4byte gGameState+0x625c\n\
_US_080F08A8: .4byte gSramState\n\
_US_080F08AC:\n\
	ldr	r1, _US_080F08D4\n\
	ldrb	r0, [r1, #0]\n\
	cmp	r0, #2\n\
	bne _US_080F08B6\n\
	b _US_080F0C2C\n\
_US_080F08B6:\n\
	movs	r5, #28\n\
	ldrsh	r0, [r1, r5]\n\
	cmp	r0, #0\n\
	bne _US_080F08C0\n\
	b _US_080F0C2C\n\
_US_080F08C0:\n\
	movs	r0, #9\n\
	bl PrintOptionMessage2\n\
	ldrb	r0, [r6, #3]\n\
	cmp	r0, #72\n\
	bne _US_080F08CE\n\
	b _US_080F0BDC\n\
_US_080F08CE:\n\
	movs	r0, #119\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F08D4: .4byte gSramState\n\
_US_080F08D8:\n\
	movs	r0, #6\n\
	bl PrintOptionMessage1\n\
	movs	r0, #0\n\
	strh	r0, [r6, #10]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F08E8:\n\
	ldr	r1, _US_080F0954\n\
	movs	r2, #4\n\
	ldrsh	r0, [r6, r2]\n\
	adds	r0, #31\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0958\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F095C\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F090C\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F090E\n\
_US_080F090C:\n\
	movs	r2, #1\n\
_US_080F090E:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #8\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldrh	r0, [r4, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F092A\n\
	cmp	r0, #4\n\
	beq _US_080F092A\n\
	b _US_080F0C2C\n\
_US_080F092A:\n\
	adds	r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls	r0, r0, #16\n\
	lsrs	r2, r0, #16\n\
	cmp	r0, #0\n\
	bne _US_080F093A\n\
	b _US_080F0C2C\n\
_US_080F093A:\n\
	lsls	r0, r2, #16\n\
	cmp	r0, #0\n\
	ble _US_080F0964\n\
	ldrb	r0, [r6, #4]\n\
	ldr	r1, _US_080F0960\n\
	movs	r2, #148\n\
	lsls	r2, r2, #2\n\
	bl sram_08003378\n\
_US_080F094C:\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F0954: .4byte StringOfsTable\n\
_US_080F0958: .4byte gStringData\n\
_US_080F095C: .4byte gTextWindow+0x8\n\
_US_080F0960: .4byte gGameState+0x625c\n\
_US_080F0964:\n\
	ldrb	r0, [r6, #3]\n\
	subs	r0, #5\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
_US_080F096C:\n\
	ldr	r1, _US_080F0A8C\n\
	movs	r3, #4\n\
	ldrsh	r0, [r6, r3]\n\
	adds	r0, #31\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0A90\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0A94\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F0990\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F0992\n\
_US_080F0990:\n\
	movs	r2, #1\n\
_US_080F0992:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #8\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldr	r1, _US_080F0A98\n\
	ldrb	r0, [r1, #0]\n\
	cmp	r0, #1\n\
	bne _US_080F09AC\n\
	b _US_080F0C2C\n\
_US_080F09AC:\n\
	movs	r5, #30\n\
	ldrsh	r0, [r1, r5]\n\
	cmp	r0, #0\n\
	bne _US_080F09B6\n\
	b _US_080F0C2C\n\
_US_080F09B6:\n\
	movs	r0, #10\n\
	bl PrintOptionMessage2\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F09C2:\n\
	ldr	r0, _US_080F0A94\n\
	ldrh	r0, [r0, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F09D0\n\
	cmp	r0, #4\n\
	beq _US_080F09D0\n\
	b _US_080F0C2C\n\
_US_080F09D0:\n\
	ldr	r0, _US_080F0A9C\n\
	adds	r4, r6, r0\n\
	ldrb	r0, [r4, #0]\n\
	ldr	r2, _US_080F0AA0\n\
	adds	r1, r6, r2\n\
	bl ResetMissionScore\n\
	ldr	r3, _US_080F0AA4\n\
	adds	r0, r6, r3\n\
	ldr	r0, [r0, #0]\n\
	ldr	r5, _US_080F0AA8\n\
	adds	r1, r6, r5\n\
	bl LoadZeroStatus\n\
	ldrb	r0, [r4, #0]\n\
	ldr	r2, _US_080F0AAC\n\
	adds	r1, r6, r2\n\
	bl LoadStoryData\n\
	ldr	r0, _US_080F0AB0\n\
	movs	r3, #170\n\
	lsls	r3, r3, #1\n\
	adds	r0, r0, r3\n\
	movs	r1, #2\n\
	str	r1, [r0, #0]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F0A08:\n\
	ldr	r7, _US_080F0AB0\n\
	movs	r0, #180\n\
	lsls	r0, r0, #1\n\
	adds	r5, r7, r0\n\
	ldr	r0, [r5, #0]\n\
	movs	r4, #1\n\
	negs	r4, r4\n\
	cmp	r0, r4\n\
	beq _US_080F0A24\n\
	lsls	r0, r0, #16\n\
	lsrs	r0, r0, #16\n\
	bl FadeOutBGM\n\
	str	r4, [r5, #0]\n\
_US_080F0A24:\n\
	ldr	r2, _US_080F0A94\n\
	ldrh	r1, [r2, #0]\n\
	movs	r0, #2\n\
	orrs	r0, r1\n\
	strh	r0, [r2, #0]\n\
	movs	r1, #170\n\
	lsls	r1, r1, #1\n\
	adds	r0, r7, r1\n\
	ldr	r0, [r0, #0]\n\
	cmp	r0, #0\n\
	beq _US_080F0A3C\n\
	b _US_080F0C2C\n\
_US_080F0A3C:\n\
	ldr	r0, _US_080F0AB4\n\
	ldr	r0, [r0, #0]\n\
	ldrb	r0, [r0, #16]\n\
	cmp	r0, #0\n\
	bne _US_080F0AC0\n\
	ldr	r4, _US_080F0AB8\n\
	ldrb	r2, [r4, #4]\n\
	movs	r1, #247\n\
	adds	r0, r1, #0\n\
	ands	r0, r2\n\
	strb	r0, [r4, #4]\n\
	ldr	r2, _US_080F0AAC\n\
	adds	r3, r6, r2\n\
	ldrb	r2, [r3, #0]\n\
	ands	r1, r2\n\
	strb	r1, [r3, #0]\n\
	movs	r2, #1\n\
	ands	r0, r2\n\
	cmp	r0, #0\n\
	beq _US_080F0A6A\n\
	ldr	r3, _US_080F0ABC\n\
	adds	r0, r6, r3\n\
	strh	r2, [r0, #2]\n\
_US_080F0A6A:\n\
	ldrb	r1, [r4, #4]\n\
	movs	r3, #2\n\
	adds	r0, r3, #0\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F0A7C\n\
	ldr	r5, _US_080F0ABC\n\
	adds	r0, r6, r5\n\
	strh	r3, [r0, #2]\n\
_US_080F0A7C:\n\
	ldr	r1, _US_080F0A9C\n\
	adds	r0, r6, r1\n\
	strh	r2, [r0, #0]\n\
	movs	r0, #1\n\
	bl InitStageRun\n\
	b _US_080F0B5C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0A8C: .4byte StringOfsTable\n\
_US_080F0A90: .4byte gStringData\n\
_US_080F0A94: .4byte gTextWindow+0x8\n\
_US_080F0A98: .4byte gSramState\n\
_US_080F0A9C: .4byte 0x00006260\n\
_US_080F0AA0: .4byte 0x00006410\n\
_US_080F0AA4: .4byte 0x000064AC\n\
_US_080F0AA8: .4byte 0x00006460\n\
_US_080F0AAC: .4byte 0x00006270\n\
_US_080F0AB0: .4byte gStageRun\n\
_US_080F0AB4: .4byte gScore\n\
_US_080F0AB8: .4byte gCurStory\n\
_US_080F0ABC: .4byte 0x0000625C\n\
_US_080F0AC0:\n\
	ldr	r3, _US_080F0AEC\n\
	ldrb	r2, [r3, #4]\n\
	movs	r0, #8\n\
	ands	r0, r2\n\
	cmp	r0, #0\n\
	beq _US_080F0AF8\n\
	movs	r1, #247\n\
	adds	r0, r1, #0\n\
	ands	r0, r2\n\
	strb	r0, [r3, #4]\n\
	ldr	r3, _US_080F0AF0\n\
	adds	r2, r6, r3\n\
	ldrb	r0, [r2, #0]\n\
	ands	r1, r0\n\
	strb	r1, [r2, #0]\n\
	ldr	r5, _US_080F0AF4\n\
	adds	r0, r6, r5\n\
	ldrb	r0, [r0, #0]\n\
	bl InitStageRun\n\
	b _US_080F0B5C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0AEC: .4byte gCurStory\n\
_US_080F0AF0: .4byte 0x00006270\n\
_US_080F0AF4: .4byte 0x00006260\n\
_US_080F0AF8:\n\
	ldrb	r1, [r3, #5]\n\
	movs	r0, #24\n\
	ands	r0, r1\n\
	cmp	r0, #8\n\
	bne _US_080F0B14\n\
	ldr	r1, _US_080F0B10\n\
	adds	r0, r6, r1\n\
	movs	r1, #17\n\
	strh	r1, [r0, #0]\n\
	movs	r0, #17\n\
	movs	r1, #10\n\
	b _US_080F0B58\n\
	.align 2, 0\n\
_US_080F0B10: .4byte 0x00006260\n\
_US_080F0B14:\n\
	movs	r0, #48\n\
	ands	r0, r1\n\
	cmp	r0, #16\n\
	bne _US_080F0B30\n\
	ldr	r2, _US_080F0B2C\n\
	adds	r0, r6, r2\n\
	movs	r1, #17\n\
	strh	r1, [r0, #0]\n\
	movs	r0, #17\n\
	movs	r1, #14\n\
	b _US_080F0B58\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0B2C: .4byte 0x00006260\n\
_US_080F0B30:\n\
	ldrb	r1, [r3, #6]\n\
	movs	r0, #20\n\
	ands	r0, r1\n\
	cmp	r0, #4\n\
	bne _US_080F0B4C\n\
	ldr	r3, _US_080F0B48\n\
	adds	r0, r6, r3\n\
	movs	r1, #17\n\
	strh	r1, [r0, #0]\n\
	movs	r0, #17\n\
	b _US_080F0B58\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0B48: .4byte 0x00006260\n\
_US_080F0B4C:\n\
	ldr	r5, _US_080F0B68\n\
	adds	r0, r6, r5\n\
	movs	r1, #17\n\
	strh	r1, [r0, #0]\n\
	movs	r0, #17\n\
	movs	r1, #2\n\
_US_080F0B58:\n\
	bl LoadStageRun\n\
_US_080F0B5C:\n\
	movs	r1, #192\n\
	lsls	r1, r1, #2\n\
_US_080F0B60:\n\
	adds	r0, r6, #0\n\
	bl SetGameMode\n\
	b _US_080F0C2C\n\
	.align 2, 0\n\
_US_080F0B68: .4byte 0x00006260\n\
_US_080F0B6C:\n\
	movs	r0, #8\n\
	bl PrintOptionMessage1\n\
	movs	r0, #1\n\
	strh	r0, [r6, #10]\n\
	ldrb	r0, [r6, #3]\n\
	adds	r0, #1\n\
	strb	r0, [r6, #3]\n\
_US_080F0B7C:\n\
	ldr	r1, _US_080F0BE4\n\
	movs	r2, #4\n\
	ldrsh	r0, [r6, r2]\n\
	adds	r0, #31\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r1, [r0, #0]\n\
	ldr	r0, _US_080F0BE8\n\
	adds	r3, r1, r0\n\
	movs	r2, #0\n\
	ldr	r0, _US_080F0BEC\n\
	ldrb	r1, [r0, #6]\n\
	adds	r4, r0, #0\n\
	cmp	r1, #0\n\
	bne _US_080F0BA0\n\
	ldrb	r0, [r4, #4]\n\
	cmp	r0, #1\n\
	bne _US_080F0BA2\n\
_US_080F0BA0:\n\
	movs	r2, #1\n\
_US_080F0BA2:\n\
	lsls	r0, r2, #3\n\
	subs	r0, r0, r2\n\
	movs	r1, #8\n\
	subs	r1, r1, r0\n\
	ldrb	r2, [r4, #5]\n\
	adds	r0, r3, #0\n\
	bl PrintString\n\
	ldrh	r0, [r4, #2]\n\
	cmp	r0, #0\n\
	beq _US_080F0BBC\n\
	cmp	r0, #4\n\
	bne _US_080F0C2C\n\
_US_080F0BBC:\n\
	adds	r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls	r0, r0, #16\n\
	lsrs	r2, r0, #16\n\
	cmp	r0, #0\n\
	beq _US_080F0C2C\n\
	lsls	r0, r2, #16\n\
	cmp	r0, #0\n\
	ble _US_080F0BF0\n\
	ldrb	r0, [r6, #4]\n\
	bl DeleteSector\n\
	movs	r0, #11\n\
	bl PrintOptionMessage2\n\
_US_080F0BDC:\n\
	movs	r0, #64\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F0BE4: .4byte StringOfsTable\n\
_US_080F0BE8: .4byte gStringData\n\
_US_080F0BEC: .4byte gTextWindow+0x8\n\
_US_080F0BF0:\n\
	movs	r0, #82\n\
	strb	r0, [r6, #3]\n\
	b _US_080F0C2C\n\
_US_080F0BF6:\n\
	ldr	r6, _US_080F0C3C\n\
	movs	r3, #180\n\
	lsls	r3, r3, #1\n\
	adds	r5, r6, r3\n\
	ldr	r0, [r5, #0]\n\
	movs	r4, #1\n\
	negs	r4, r4\n\
	cmp	r0, r4\n\
	beq _US_080F0C12\n\
	lsls	r0, r0, #16\n\
	lsrs	r0, r0, #16\n\
	bl FadeOutBGM\n\
	str	r4, [r5, #0]\n\
_US_080F0C12:\n\
	ldr	r2, _US_080F0C40\n\
	ldrh	r1, [r2, #0]\n\
	movs	r0, #2\n\
	orrs	r0, r1\n\
	strh	r0, [r2, #0]\n\
	movs	r5, #170\n\
	lsls	r5, r5, #1\n\
	adds	r0, r6, r5\n\
	ldr	r0, [r0, #0]\n\
	cmp	r0, #0\n\
	bne _US_080F0C2C\n\
	bl ExitProcess\n\
_US_080F0C2C:\n\
	add	sp, #8\n\
	pop	{r3, r4, r5}\n\
	mov	r8, r3\n\
	mov	r9, r4\n\
	mov	sl, r5\n\
	pop	{r4, r5, r6, r7}\n\
	pop	{r0}\n\
	bx	r0\n\
	.align 2, 0\n\
_US_080F0C3C: .4byte gStageRun\n\
_US_080F0C40: .4byte gTextWindow+0x8\n\
.else\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	sub sp, #8\n\
	adds r6, r0, #0\n\
	ldrb r0, [r6, #3]\n\
	subs r0, #0x3f\n\
	cmp r0, #0x37\n\
	bls _080F0672\n\
	bl _RETURN\n\
_080F0672:\n\
	lsls r0, r0, #2\n\
	ldr r1, _080F067C @ =_080F0680\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_080F067C: .4byte _080F0680\n\
_080F0680: @ jump table\n\
	.4byte _080F0760 @ case 0\n\
	.4byte _080F0780 @ case 1\n\
	.4byte _080F07A0 @ case 2\n\
	.4byte _080F07F4 @ case 3\n\
	.4byte _080F080C @ case 4\n\
	.4byte _080F08B0 @ case 5\n\
	.4byte _080F08C2 @ case 6\n\
	.4byte _080F0C74 @ case 7\n\
	.4byte _080F0C84 @ case 8\n\
	.4byte _080F0D20 @ case 9\n\
	.4byte _080F07FC @ case 10\n\
	.4byte _080F080C @ case 11\n\
	.4byte _080F08B0 @ case 12\n\
	.4byte _080F08C2 @ case 13\n\
	.4byte _080F0D4C @ case 14\n\
	.4byte _080F0D5C @ case 15\n\
	.4byte _080F0DE0 @ case 16\n\
	.4byte _080F0E36 @ case 17\n\
	.4byte _080F0E7C @ case 18\n\
	.4byte _080F0804 @ case 19\n\
	.4byte _080F080C @ case 20\n\
	.4byte _080F08B0 @ case 21\n\
	.4byte _080F08C2 @ case 22\n\
	.4byte _080F0FE0 @ case 23\n\
	.4byte _080F0FF0 @ case 24\n\
	.4byte _RETURN @ case 25\n\
	.4byte _RETURN @ case 26\n\
	.4byte _RETURN @ case 27\n\
	.4byte _RETURN @ case 28\n\
	.4byte _RETURN @ case 29\n\
	.4byte _RETURN @ case 30\n\
	.4byte _RETURN @ case 31\n\
	.4byte _RETURN @ case 32\n\
	.4byte _080F07FC @ case 33\n\
	.4byte _080F080C @ case 34\n\
	.4byte _080F08B0 @ case 35\n\
	.4byte _080F08C2 @ case 36\n\
	.4byte _080F0D4C @ case 37\n\
	.4byte _080F0D5C @ case 38\n\
	.4byte _080F0DE0 @ case 39\n\
	.4byte _080F0E36 @ case 40\n\
	.4byte _080F0E7C @ case 41\n\
	.4byte _080F106A @ case 42\n\
	.4byte _RETURN @ case 43\n\
	.4byte _RETURN @ case 44\n\
	.4byte _RETURN @ case 45\n\
	.4byte _RETURN @ case 46\n\
	.4byte _RETURN @ case 47\n\
	.4byte _RETURN @ case 48\n\
	.4byte _080F07F4 @ case 49\n\
	.4byte _080F080C @ case 50\n\
	.4byte _080F08B0 @ case 51\n\
	.4byte _080F08C2 @ case 52\n\
	.4byte _080F0C74 @ case 53\n\
	.4byte _080F0C84 @ case 54\n\
	.4byte _080F0D20 @ case 55\n\
_080F0760:\n\
	ldr r2, _080F0774 @ =gTextWindow+8\n\
	ldrh r0, [r2, #2]\n\
	cmp r0, #0\n\
	beq _080F0778\n\
	ldrh r1, [r2]\n\
	movs r0, #2\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	bl _RETURN\n\
	.align 2, 0\n\
_080F0774: .4byte gTextWindow+8\n\
_080F0778:\n\
	movs r1, #0x80\n\
	lsls r1, r1, #3\n\
	bl _080f0fd4\n\
_080F0780:\n\
	ldr r0, _080F07D4 @ =gTextWindow+8\n\
	ldrh r0, [r0, #2]\n\
	cmp r0, #0\n\
	beq _080F0790\n\
	cmp r0, #4\n\
	beq _080F0790\n\
	bl _RETURN\n\
_080F0790:\n\
	movs r0, #2\n\
	bl PrintOptionMessage1\n\
	movs r0, #0\n\
	strh r0, [r6, #0xa]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F07A0:\n\
	ldr r0, _080F07D4 @ =gTextWindow+8\n\
	ldrh r0, [r0, #2]\n\
	cmp r0, #0\n\
	beq _080F07B0\n\
	cmp r0, #4\n\
	beq _080F07B0\n\
	bl _RETURN\n\
_080F07B0:\n\
	adds r0, r6, #0\n\
	bl save_080f32f8\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	cmp r0, #0\n\
	bne _080F07C2\n\
	bl _RETURN\n\
_080F07C2:\n\
	lsls r0, r4, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #1\n\
	bne _080F07D8\n\
	movs r0, #0x42\n\
	strb r0, [r6, #3]\n\
	bl _RETURN\n\
	.align 2, 0\n\
_080F07D4: .4byte gTextWindow+8\n\
_080F07D8:\n\
	cmp r0, #2\n\
	bne _080F07E4\n\
	movs r0, #0x49\n\
	strb r0, [r6, #3]\n\
	bl _RETURN\n\
_080F07E4:\n\
	cmp r0, #3\n\
	bne _080F07EC\n\
	bl _080F1064\n\
_080F07EC:\n\
	movs r0, #0x3f\n\
	strb r0, [r6, #3]\n\
	bl _RETURN\n\
_080F07F4:\n\
	movs r0, #3\n\
	bl PrintOptionMessage1\n\
	b _080F0DC0\n\
_080F07FC:\n\
	movs r0, #5\n\
	bl PrintOptionMessage1\n\
	b _080F0DC0\n\
_080F0804:\n\
	movs r0, #7\n\
	bl PrintOptionMessage1\n\
	b _080F0DC0\n\
_080F080C:\n\
	movs r4, #0\n\
	ldr r0, _080F083C @ =gSaveSlotMetadata\n\
	mov sl, r0\n\
	ldr r7, _080F0840 @ =0x0200055C\n\
	ldr r1, _080F0844 @ =0xFFFFFE4C\n\
	adds r1, r1, r7\n\
	mov sb, r1\n\
_080F081A:\n\
	lsls r0, r4, #0x18\n\
	lsrs r5, r0, #0x18\n\
	adds r0, r5, #0\n\
	movs r1, #0x94\n\
	lsls r1, r1, #2\n\
	bl ValidateSector\n\
	adds r2, r0, #0\n\
	cmp r2, #0\n\
	bne _080F0848\n\
	lsls r1, r4, #0x10\n\
	asrs r0, r1, #0x10\n\
	add r0, sl\n\
	strb r2, [r0]\n\
	mov r8, r1\n\
	b _080F089C\n\
	.align 2, 0\n\
_080F083C: .4byte gSaveSlotMetadata\n\
_080F0840: .4byte 0x0200055C\n\
_080F0844: .4byte 0xFFFFFE4C\n\
_080F0848:\n\
	lsls r4, r4, #0x10\n\
	asrs r0, r4, #0x10\n\
	add r0, sl\n\
	movs r1, #1\n\
	strb r1, [r0]\n\
	adds r0, r5, #0\n\
	ldr r1, _080F09CC @ =SaveState_020003a8\n\
	movs r2, #0x94\n\
	lsls r2, r2, #2\n\
	bl sram_08003378\n\
	mov r8, r4\n\
	ldr r4, _080F09D0 @ =gSramState\n\
_080F0862:\n\
	bl UpdateSram\n\
	ldrb r0, [r4]\n\
	cmp r0, #1\n\
	beq _080F0862\n\
	movs r2, #0x1e\n\
	ldrsh r0, [r4, r2]\n\
	cmp r0, #0\n\
	beq _080F0862\n\
	ldr r1, _080F09D4 @ =0x02000600\n\
	mov r5, r8\n\
	asrs r3, r5, #0x10\n\
	lsls r2, r3, #2\n\
	adds r1, r2, r1\n\
	ldr r0, [r7, #0xc]\n\
	str r0, [r1]\n\
	ldr r0, _080F09D8 @ =0x02000618\n\
	adds r2, r2, r0\n\
	ldrb r0, [r7, #1]\n\
	str r0, [r2]\n\
	ldr r0, _080F09DC @ =0x0200062C\n\
	adds r0, r3, r0\n\
	mov r2, sb\n\
	ldrh r1, [r2]\n\
	strb r1, [r0]\n\
	ldr r0, _080F09E0 @ =0x02000634\n\
	adds r3, r3, r0\n\
	ldrh r0, [r2, #2]\n\
	strb r0, [r3]\n\
_080F089C:\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	add r0, r8\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #4\n\
	ble _080F081A\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F08B0:\n\
	movs r0, #0\n\
	strh r0, [r6, #4]\n\
	strh r0, [r6, #6]\n\
	strh r0, [r6, #8]\n\
	movs r0, #0xf\n\
	strh r0, [r6, #0xa]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F08C2:\n\
	ldr r0, _080F09E4 @ =gTextWindow+8\n\
	ldrh r0, [r0, #2]\n\
	cmp r0, #0\n\
	beq _080F08D2\n\
	cmp r0, #4\n\
	beq _080F08D2\n\
	bl _RETURN\n\
_080F08D2:\n\
	movs r5, #4\n\
	ldrsh r0, [r6, r5]\n\
	cmp r0, #3\n\
	bgt _080F08F2\n\
	ldr r0, _080F09E8 @ =gJoypad\n\
	ldrh r1, [r0, #6]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F08F2\n\
	movs r0, #1\n\
	bl PlaySound\n\
	ldrh r0, [r6, #4]\n\
	adds r0, #1\n\
	strh r0, [r6, #4]\n\
_080F08F2:\n\
	movs r1, #4\n\
	ldrsh r0, [r6, r1]\n\
	cmp r0, #0\n\
	ble _080F0912\n\
	ldr r0, _080F09E8 @ =gJoypad\n\
	ldrh r1, [r0, #6]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F0912\n\
	movs r0, #1\n\
	bl PlaySound\n\
	ldrh r0, [r6, #4]\n\
	subs r0, #1\n\
	strh r0, [r6, #4]\n\
_080F0912:\n\
	ldrh r3, [r6, #4]\n\
	movs r2, #4\n\
	ldrsh r1, [r6, r2]\n\
	movs r5, #6\n\
	ldrsh r0, [r6, r5]\n\
	adds r2, r3, #0\n\
	cmp r1, r0\n\
	bge _080F0924\n\
	strh r2, [r6, #6]\n\
_080F0924:\n\
	movs r0, #4\n\
	ldrsh r1, [r6, r0]\n\
	movs r2, #6\n\
	ldrsh r0, [r6, r2]\n\
	adds r0, #1\n\
	cmp r1, r0\n\
	ble _080F0936\n\
	subs r0, r3, #1\n\
	strh r0, [r6, #6]\n\
_080F0936:\n\
	movs r4, #0\n\
_080F0938:\n\
	lsls r0, r4, #0x10\n\
	asrs r5, r0, #0x10\n\
	movs r2, #6\n\
	ldrsh r1, [r6, r2]\n\
	subs r1, r5, r1\n\
	lsls r1, r1, #0x19\n\
	lsrs r1, r1, #0x18\n\
	mov ip, r1\n\
	lsls r7, r1, #0x18\n\
	lsrs r1, r7, #0x18\n\
	mov r8, r0\n\
	cmp r1, #2\n\
	bhi _080F0A26\n\
	ldr r0, _080F09EC @ =gSaveSlotMetadata\n\
	adds r0, r5, r0\n\
	ldrb r0, [r0]\n\
	cmp r0, #0\n\
	bne _080F09F8\n\
	ldr r1, _080F09F0 @ =StringOfsTable\n\
	adds r0, r5, #0\n\
	adds r0, #0x1f\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F09F4 @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r1, _080F09E4 @ =gTextWindow+8\n\
	ldrb r0, [r1, #6]\n\
	cmp r0, #0\n\
	bne _080F097C\n\
	ldrb r0, [r1, #4]\n\
	cmp r0, #1\n\
	bne _080F097E\n\
_080F097C:\n\
	movs r2, #1\n\
_080F097E:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #9\n\
	subs r1, r1, r0\n\
	ldr r5, _080F09E4 @ =gTextWindow+8\n\
	mov r0, ip\n\
	lsls r4, r0, #0x18\n\
	asrs r2, r4, #0x18\n\
	adds r2, #2\n\
	ldrb r0, [r5, #5]\n\
	adds r2, r2, r0\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldr r0, _080F09F0 @ =StringOfsTable\n\
	ldrh r1, [r0, #2]\n\
	ldr r0, _080F09F4 @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080F09B0\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080F09B2\n\
_080F09B0:\n\
	movs r1, #1\n\
_080F09B2:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #0xb\n\
	subs r1, r1, r0\n\
	ldr r0, _080F09E4 @ =gTextWindow+8\n\
	asrs r2, r4, #0x18\n\
	adds r2, #2\n\
	ldrb r0, [r0, #5]\n\
	adds r2, r2, r0\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	b _080F0A26\n\
	.align 2, 0\n\
_080F09CC: .4byte SaveState_020003a8\n\
_080F09D0: .4byte gSramState\n\
_080F09D4: .4byte 0x02000600\n\
_080F09D8: .4byte 0x02000618\n\
_080F09DC: .4byte 0x0200062C\n\
_080F09E0: .4byte 0x02000634\n\
_080F09E4: .4byte gTextWindow+8\n\
_080F09E8: .4byte gJoypad\n\
_080F09EC: .4byte gSaveSlotMetadata\n\
_080F09F0: .4byte StringOfsTable\n\
_080F09F4: .4byte gStringData\n\
_080F09F8:\n\
	lsls r0, r4, #0x18\n\
	lsrs r0, r0, #0x18\n\
	ldr r1, _080F0B00 @ =0x02000618\n\
	lsls r3, r5, #2\n\
	adds r1, r3, r1\n\
	ldrb r1, [r1]\n\
	ldr r2, _080F0B04 @ =0x02000600\n\
	adds r3, r3, r2\n\
	ldr r2, [r3]\n\
	ldr r3, _080F0B08 @ =0x0200062C\n\
	adds r3, r5, r3\n\
	ldrb r3, [r3]\n\
	ldr r4, _080F0B0C @ =0x02000634\n\
	adds r4, r5, r4\n\
	ldrb r4, [r4]\n\
	str r4, [sp]\n\
	movs r5, #0x80\n\
	lsls r5, r5, #0x12\n\
	adds r4, r7, r5\n\
	lsrs r4, r4, #0x18\n\
	str r4, [sp, #4]\n\
	bl PrintSaveDataRow\n\
_080F0A26:\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	add r0, r8\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #4\n\
	bgt _080F0A36\n\
	b _080F0938\n\
_080F0A36:\n\
	ldr r0, _080F0B10 @ =StringOfsTable\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F0B14 @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r0, _080F0B18 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0A50\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0A52\n\
_080F0A50:\n\
	movs r2, #1\n\
_080F0A52:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	movs r0, #4\n\
	ldrsh r2, [r6, r0]\n\
	movs r5, #6\n\
	ldrsh r0, [r6, r5]\n\
	subs r2, r2, r0\n\
	lsls r2, r2, #1\n\
	adds r2, #2\n\
	ldrb r0, [r4, #5]\n\
	adds r2, r2, r0\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldrh r0, [r6, #8]\n\
	adds r0, #1\n\
	strh r0, [r6, #8]\n\
	movs r1, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F0A82\n\
	b _080F0B84\n\
_080F0A82:\n\
	movs r2, #0\n\
	ldrb r0, [r4, #6]\n\
	cmp r0, #0\n\
	bne _080F0A90\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0A92\n\
_080F0A90:\n\
	movs r2, #1\n\
_080F0A92:\n\
	lsls r1, r2, #3\n\
	subs r1, r1, r2\n\
	movs r0, #8\n\
	subs r0, r0, r1\n\
	cmp r0, #3\n\
	ble _080F0B24\n\
	movs r1, #6\n\
	ldrsh r0, [r6, r1]\n\
	cmp r0, #0\n\
	beq _080F0ACE\n\
	ldr r3, _080F0B1C @ =Unicode_CursorUp\n\
	movs r2, #0\n\
	ldr r0, _080F0B18 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0ABA\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0ABC\n\
_080F0ABA:\n\
	movs r2, #1\n\
_080F0ABC:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #0x1c\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r2, #2\n\
	adds r0, r3, #0\n\
	bl PrintUnicodeString\n\
_080F0ACE:\n\
	movs r2, #6\n\
	ldrsh r0, [r6, r2]\n\
	cmp r0, #3\n\
	beq _080F0B84\n\
	ldr r3, _080F0B20 @ =Unicode_CursorDown\n\
	movs r2, #0\n\
	ldr r0, _080F0B18 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0AEA\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0AEC\n\
_080F0AEA:\n\
	movs r2, #1\n\
_080F0AEC:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #0x1c\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r2, #5\n\
	adds r0, r3, #0\n\
	bl PrintUnicodeString\n\
	b _080F0B84\n\
	.align 2, 0\n\
_080F0B00: .4byte 0x02000618\n\
_080F0B04: .4byte 0x02000600\n\
_080F0B08: .4byte 0x0200062C\n\
_080F0B0C: .4byte 0x02000634\n\
_080F0B10: .4byte StringOfsTable\n\
_080F0B14: .4byte gStringData\n\
_080F0B18: .4byte gTextWindow+8\n\
_080F0B1C: .4byte Unicode_CursorUp\n\
_080F0B20: .4byte Unicode_CursorDown\n\
_080F0B24:\n\
	movs r5, #6\n\
	ldrsh r0, [r6, r5]\n\
	cmp r0, #0\n\
	beq _080F0B54\n\
	ldr r3, _080F0B94 @ =Unicode_CursorUp\n\
	movs r2, #0\n\
	ldr r0, _080F0B98 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0B40\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0B42\n\
_080F0B40:\n\
	movs r2, #1\n\
_080F0B42:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #7\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r2, #2\n\
	adds r0, r3, #0\n\
	bl PrintUnicodeString\n\
_080F0B54:\n\
	movs r1, #6\n\
	ldrsh r0, [r6, r1]\n\
	cmp r0, #3\n\
	beq _080F0B84\n\
	ldr r3, _080F0B9C @ =Unicode_CursorDown\n\
	movs r2, #0\n\
	ldr r0, _080F0B98 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0B70\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0B72\n\
_080F0B70:\n\
	movs r2, #1\n\
_080F0B72:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #7\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r2, #5\n\
	adds r0, r3, #0\n\
	bl PrintUnicodeString\n\
_080F0B84:\n\
	ldrh r1, [r6, #0xa]\n\
	movs r2, #0xa\n\
	ldrsh r0, [r6, r2]\n\
	cmp r0, #0\n\
	beq _080F0BA0\n\
	subs r0, r1, #1\n\
	strh r0, [r6, #0xa]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0B94: .4byte Unicode_CursorUp\n\
_080F0B98: .4byte gTextWindow+8\n\
_080F0B9C: .4byte Unicode_CursorDown\n\
_080F0BA0:\n\
	ldr r0, _080F0BCC @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r4, #2\n\
	adds r0, r4, #0\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F0BE0\n\
	movs r0, #3\n\
	bl PlaySound\n\
	ldrb r0, [r6, #3]\n\
	cmp r0, #0x63\n\
	bne _080F0BD4\n\
	ldr r0, _080F0BD0 @ =gStageRun\n\
	movs r5, #0xaa\n\
	lsls r5, r5, #1\n\
	adds r0, r0, r5\n\
	str r4, [r0]\n\
	movs r0, #0x69\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0BCC: .4byte gJoypad\n\
_080F0BD0: .4byte gStageRun\n\
_080F0BD4:\n\
	cmp r0, #0x73\n\
	beq _080F0BDA\n\
	b _080F1050\n\
_080F0BDA:\n\
	movs r0, #0x7c\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
_080F0BE0:\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080F0BEA\n\
	b _RETURN\n\
_080F0BEA:\n\
	ldrb r0, [r6, #3]\n\
	cmp r0, #0x45\n\
	beq _080F0BF4\n\
	cmp r0, #0x73\n\
	bne _080F0C52\n\
_080F0BF4:\n\
	movs r0, #2\n\
	bl PlaySound\n\
	ldr r0, _080F0C38 @ =gSaveSlotMetadata\n\
	movs r2, #4\n\
	ldrsh r1, [r6, r2]\n\
	adds r1, r1, r0\n\
	ldrb r0, [r1]\n\
	cmp r0, #0\n\
	beq _080F0C0A\n\
	b _080F0DC0\n\
_080F0C0A:\n\
	ldr r5, _080F0C3C @ =0x00006270\n\
	adds r0, r6, r5\n\
	bl StoreStoryData\n\
	ldr r1, _080F0C40 @ =0x000064AC\n\
	adds r0, r6, r1\n\
	ldr r0, [r0]\n\
	ldr r2, _080F0C44 @ =0x00006460\n\
	adds r1, r6, r2\n\
	bl StoreZeroStatus\n\
	ldrb r0, [r6, #4]\n\
	ldr r1, _080F0C48 @ =gGameState+0x625C\n\
	movs r2, #0x94\n\
	lsls r2, r2, #2\n\
	bl sram_08003330\n\
	ldrb r0, [r6, #3]\n\
	cmp r0, #0x45\n\
	bne _080F0C4C\n\
	movs r0, #0x48\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0C38: .4byte gSaveSlotMetadata\n\
_080F0C3C: .4byte 0x00006270\n\
_080F0C40: .4byte 0x000064AC\n\
_080F0C44: .4byte 0x00006460\n\
_080F0C48: .4byte gGameState+0x625C\n\
_080F0C4C:\n\
	movs r0, #0x76\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
_080F0C52:\n\
	ldr r0, _080F0C68 @ =gSaveSlotMetadata\n\
	movs r5, #4\n\
	ldrsh r1, [r6, r5]\n\
	adds r1, r1, r0\n\
	ldrb r0, [r1]\n\
	cmp r0, #0\n\
	bne _080F0C6C\n\
	movs r0, #4\n\
	bl PlaySound\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0C68: .4byte gSaveSlotMetadata\n\
_080F0C6C:\n\
	movs r0, #2\n\
	bl PlaySound\n\
	b _080F0DC0\n\
_080F0C74:\n\
	movs r0, #4\n\
	bl PrintOptionMessage1\n\
	movs r0, #1\n\
	strh r0, [r6, #0xa]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F0C84:\n\
	ldr r1, _080F0D04 @ =StringOfsTable\n\
	movs r2, #4\n\
	ldrsh r0, [r6, r2]\n\
	adds r0, #0x1f\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F0D08 @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r0, _080F0D0C @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0CA8\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0CAA\n\
_080F0CA8:\n\
	movs r2, #1\n\
_080F0CAA:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldrh r0, [r4, #2]\n\
	cmp r0, #0\n\
	beq _080F0CC6\n\
	cmp r0, #4\n\
	beq _080F0CC6\n\
	b _RETURN\n\
_080F0CC6:\n\
	adds r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	cmp r0, #0\n\
	bne _080F0CD6\n\
	b _RETURN\n\
_080F0CD6:\n\
	lsls r0, r4, #0x10\n\
	cmp r0, #0\n\
	bgt _080F0CDE\n\
	b _080F0DD8\n\
_080F0CDE:\n\
	ldr r5, _080F0D10 @ =0x00006270\n\
	adds r0, r6, r5\n\
	bl StoreStoryData\n\
	ldr r1, _080F0D14 @ =0x000064AC\n\
	adds r0, r6, r1\n\
	ldr r0, [r0]\n\
	ldr r2, _080F0D18 @ =0x00006460\n\
	adds r1, r6, r2\n\
	bl StoreZeroStatus\n\
	ldrb r0, [r6, #4]\n\
	ldr r1, _080F0D1C @ =gGameState+0x625C\n\
	movs r2, #0x94\n\
	lsls r2, r2, #2\n\
	bl sram_08003330\n\
	b _080F0DC0\n\
	.align 2, 0\n\
_080F0D04: .4byte StringOfsTable\n\
_080F0D08: .4byte gStringData\n\
_080F0D0C: .4byte gTextWindow+8\n\
_080F0D10: .4byte 0x00006270\n\
_080F0D14: .4byte 0x000064AC\n\
_080F0D18: .4byte 0x00006460\n\
_080F0D1C: .4byte gGameState+0x625C\n\
_080F0D20:\n\
	ldr r1, _080F0D48 @ =gSramState\n\
	ldrb r0, [r1]\n\
	cmp r0, #2\n\
	bne _080F0D2A\n\
	b _RETURN\n\
_080F0D2A:\n\
	movs r5, #0x1c\n\
	ldrsh r0, [r1, r5]\n\
	cmp r0, #0\n\
	bne _080F0D34\n\
	b _RETURN\n\
_080F0D34:\n\
	movs r0, #9\n\
	bl PrintOptionMessage2\n\
	ldrb r0, [r6, #3]\n\
	cmp r0, #0x48\n\
	bne _080F0D42\n\
	b _080F1050\n\
_080F0D42:\n\
	movs r0, #0x77\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0D48: .4byte gSramState\n\
_080F0D4C:\n\
	movs r0, #6\n\
	bl PrintOptionMessage1\n\
	movs r0, #0\n\
	strh r0, [r6, #0xa]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F0D5C:\n\
	ldr r1, _080F0DC8 @ =StringOfsTable\n\
	movs r2, #4\n\
	ldrsh r0, [r6, r2]\n\
	adds r0, #0x1f\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F0DCC @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r0, _080F0DD0 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0D80\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0D82\n\
_080F0D80:\n\
	movs r2, #1\n\
_080F0D82:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldrh r0, [r4, #2]\n\
	cmp r0, #0\n\
	beq _080F0D9E\n\
	cmp r0, #4\n\
	beq _080F0D9E\n\
	b _RETURN\n\
_080F0D9E:\n\
	adds r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	cmp r0, #0\n\
	bne _080F0DAE\n\
	b _RETURN\n\
_080F0DAE:\n\
	lsls r0, r4, #0x10\n\
	cmp r0, #0\n\
	ble _080F0DD8\n\
	ldrb r0, [r6, #4]\n\
	ldr r1, _080F0DD4 @ =gGameState+0x625C\n\
	movs r2, #0x94\n\
	lsls r2, r2, #2\n\
	bl sram_08003378\n\
_080F0DC0:\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0DC8: .4byte StringOfsTable\n\
_080F0DCC: .4byte gStringData\n\
_080F0DD0: .4byte gTextWindow+8\n\
_080F0DD4: .4byte gGameState+0x625C\n\
_080F0DD8:\n\
	ldrb r0, [r6, #3]\n\
	subs r0, #5\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
_080F0DE0:\n\
	ldr r1, _080F0F00 @ =StringOfsTable\n\
	movs r5, #4\n\
	ldrsh r0, [r6, r5]\n\
	adds r0, #0x1f\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F0F04 @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r0, _080F0F08 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F0E04\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F0E06\n\
_080F0E04:\n\
	movs r2, #1\n\
_080F0E06:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldr r1, _080F0F0C @ =gSramState\n\
	ldrb r0, [r1]\n\
	cmp r0, #1\n\
	bne _080F0E20\n\
	b _RETURN\n\
_080F0E20:\n\
	movs r2, #0x1e\n\
	ldrsh r0, [r1, r2]\n\
	cmp r0, #0\n\
	bne _080F0E2A\n\
	b _RETURN\n\
_080F0E2A:\n\
	movs r0, #0xa\n\
	bl PrintOptionMessage2\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F0E36:\n\
	ldr r0, _080F0F08 @ =gTextWindow+8\n\
	ldrh r0, [r0, #2]\n\
	cmp r0, #0\n\
	beq _080F0E44\n\
	cmp r0, #4\n\
	beq _080F0E44\n\
	b _RETURN\n\
_080F0E44:\n\
	ldr r5, _080F0F10 @ =0x00006260\n\
	adds r4, r6, r5\n\
	ldrb r0, [r4]\n\
	ldr r2, _080F0F14 @ =0x00006410\n\
	adds r1, r6, r2\n\
	bl ResetMissionScore\n\
	ldr r5, _080F0F18 @ =0x000064AC\n\
	adds r0, r6, r5\n\
	ldr r0, [r0]\n\
	ldr r2, _080F0F1C @ =0x00006460\n\
	adds r1, r6, r2\n\
	bl LoadZeroStatus\n\
	ldrb r0, [r4]\n\
	ldr r5, _080F0F20 @ =0x00006270\n\
	adds r1, r6, r5\n\
	bl LoadStoryData\n\
	ldr r0, _080F0F24 @ =gStageRun\n\
	movs r1, #0xaa\n\
	lsls r1, r1, #1\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r0]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F0E7C:\n\
	ldr r7, _080F0F24 @ =gStageRun\n\
	movs r2, #0xb4\n\
	lsls r2, r2, #1\n\
	adds r5, r7, r2\n\
	ldr r0, [r5]\n\
	movs r4, #1\n\
	rsbs r4, r4, #0\n\
	cmp r0, r4\n\
	beq _080F0E98\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	bl FadeOutBGM\n\
	str r4, [r5]\n\
_080F0E98:\n\
	ldr r2, _080F0F08 @ =gTextWindow+8\n\
	ldrh r1, [r2]\n\
	movs r0, #2\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	movs r5, #0xaa\n\
	lsls r5, r5, #1\n\
	adds r0, r7, r5\n\
	ldr r0, [r0]\n\
	cmp r0, #0\n\
	beq _080F0EB0\n\
	b _RETURN\n\
_080F0EB0:\n\
	ldr r0, _080F0F28 @ =gScore\n\
	ldr r0, [r0]\n\
	ldrb r0, [r0, #0x10]\n\
	cmp r0, #0\n\
	bne _080F0F34\n\
	ldr r4, _080F0F2C @ =gCurStory\n\
	ldrb r2, [r4, #4]\n\
	movs r1, #0xf7\n\
	adds r0, r1, #0\n\
	ands r0, r2\n\
	strb r0, [r4, #4]\n\
	ldr r2, _080F0F20 @ =0x00006270\n\
	adds r3, r6, r2\n\
	ldrb r2, [r3]\n\
	ands r1, r2\n\
	strb r1, [r3]\n\
	movs r2, #1\n\
	ands r0, r2\n\
	cmp r0, #0\n\
	beq _080F0EDE\n\
	ldr r5, _080F0F30 @ =0x0000625C\n\
	adds r0, r6, r5\n\
	strh r2, [r0, #2]\n\
_080F0EDE:\n\
	ldrb r1, [r4, #4]\n\
	movs r3, #2\n\
	adds r0, r3, #0\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F0EF0\n\
	ldr r1, _080F0F30 @ =0x0000625C\n\
	adds r0, r6, r1\n\
	strh r3, [r0, #2]\n\
_080F0EF0:\n\
	ldr r5, _080F0F10 @ =0x00006260\n\
	adds r0, r6, r5\n\
	strh r2, [r0]\n\
	movs r0, #1\n\
	bl InitStageRun\n\
	b _080F0FD0\n\
	.align 2, 0\n\
_080F0F00: .4byte StringOfsTable\n\
_080F0F04: .4byte gStringData\n\
_080F0F08: .4byte gTextWindow+8\n\
_080F0F0C: .4byte gSramState\n\
_080F0F10: .4byte 0x00006260\n\
_080F0F14: .4byte 0x00006410\n\
_080F0F18: .4byte 0x000064AC\n\
_080F0F1C: .4byte 0x00006460\n\
_080F0F20: .4byte 0x00006270\n\
_080F0F24: .4byte gStageRun\n\
_080F0F28: .4byte gScore\n\
_080F0F2C: .4byte gCurStory\n\
_080F0F30: .4byte 0x0000625C\n\
_080F0F34:\n\
	ldr r3, _080F0F60 @ =gCurStory\n\
	ldrb r2, [r3, #4]\n\
	movs r0, #8\n\
	ands r0, r2\n\
	cmp r0, #0\n\
	beq _080F0F6C\n\
	movs r1, #0xf7\n\
	adds r0, r1, #0\n\
	ands r0, r2\n\
	strb r0, [r3, #4]\n\
	ldr r0, _080F0F64 @ =0x00006270\n\
	adds r2, r6, r0\n\
	ldrb r0, [r2]\n\
	ands r1, r0\n\
	strb r1, [r2]\n\
	ldr r1, _080F0F68 @ =0x00006260\n\
	adds r0, r6, r1\n\
	ldrb r0, [r0]\n\
	bl InitStageRun\n\
	b _080F0FD0\n\
	.align 2, 0\n\
_080F0F60: .4byte gCurStory\n\
_080F0F64: .4byte 0x00006270\n\
_080F0F68: .4byte 0x00006260\n\
_080F0F6C:\n\
	ldrb r1, [r3, #5]\n\
	movs r0, #0x18\n\
	ands r0, r1\n\
	cmp r0, #8\n\
	bne _080F0F88\n\
	ldr r2, _080F0F84 @ =0x00006260\n\
	adds r0, r6, r2\n\
	movs r1, #0x11\n\
	strh r1, [r0]\n\
	movs r0, #0x11\n\
	movs r1, #0xa\n\
	b _080F0FCC\n\
	.align 2, 0\n\
_080F0F84: .4byte 0x00006260\n\
_080F0F88:\n\
	movs r0, #0x30\n\
	ands r0, r1\n\
	cmp r0, #0x10\n\
	bne _080F0FA4\n\
	ldr r5, _080F0FA0 @ =0x00006260\n\
	adds r0, r6, r5\n\
	movs r1, #0x11\n\
	strh r1, [r0]\n\
	movs r0, #0x11\n\
	movs r1, #0xe\n\
	b _080F0FCC\n\
	.align 2, 0\n\
_080F0FA0: .4byte 0x00006260\n\
_080F0FA4:\n\
	ldrb r1, [r3, #6]\n\
	movs r0, #0x14\n\
	ands r0, r1\n\
	cmp r0, #4\n\
	bne _080F0FC0\n\
	ldr r1, _080F0FBC @ =0x00006260\n\
	adds r0, r6, r1\n\
	movs r1, #0x11\n\
	strh r1, [r0]\n\
	movs r0, #0x11\n\
	b _080F0FCC\n\
	.align 2, 0\n\
_080F0FBC: .4byte 0x00006260\n\
_080F0FC0:\n\
	ldr r2, _080F0FDC @ =0x00006260\n\
	adds r0, r6, r2\n\
	movs r1, #0x11\n\
	strh r1, [r0]\n\
	movs r0, #0x11\n\
	movs r1, #2\n\
_080F0FCC:\n\
	bl LoadStageRun\n\
_080F0FD0:\n\
	movs r1, #0xc0\n\
	lsls r1, r1, #2\n\
_080f0fd4: @ 0x080F0FD4\n\
	adds r0, r6, #0\n\
	bl SetGameMode\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F0FDC: .4byte 0x00006260\n\
_080F0FE0:\n\
	movs r0, #8\n\
	bl PrintOptionMessage1\n\
	movs r0, #1\n\
	strh r0, [r6, #0xa]\n\
	ldrb r0, [r6, #3]\n\
	adds r0, #1\n\
	strb r0, [r6, #3]\n\
_080F0FF0:\n\
	ldr r1, _080F1058 @ =StringOfsTable\n\
	movs r5, #4\n\
	ldrsh r0, [r6, r5]\n\
	adds r0, #0x1f\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	ldr r0, _080F105C @ =gStringData\n\
	adds r3, r1, r0\n\
	movs r2, #0\n\
	ldr r0, _080F1060 @ =gTextWindow+8\n\
	ldrb r1, [r0, #6]\n\
	adds r4, r0, #0\n\
	cmp r1, #0\n\
	bne _080F1014\n\
	ldrb r0, [r4, #4]\n\
	cmp r0, #1\n\
	bne _080F1016\n\
_080F1014:\n\
	movs r2, #1\n\
_080F1016:\n\
	lsls r0, r2, #3\n\
	subs r0, r0, r2\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r4, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
	ldrh r0, [r4, #2]\n\
	cmp r0, #0\n\
	beq _080F1030\n\
	cmp r0, #4\n\
	bne _RETURN\n\
_080F1030:\n\
	adds r0, r6, #0\n\
	bl handleWrapTwoChoice\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	cmp r0, #0\n\
	beq _RETURN\n\
	lsls r0, r4, #0x10\n\
	cmp r0, #0\n\
	ble _080F1064\n\
	ldrb r0, [r6, #4]\n\
	bl DeleteSector\n\
	movs r0, #0xb\n\
	bl PrintOptionMessage2\n\
_080F1050:\n\
	movs r0, #0x40\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
	.align 2, 0\n\
_080F1058: .4byte StringOfsTable\n\
_080F105C: .4byte gStringData\n\
_080F1060: .4byte gTextWindow+8\n\
_080F1064:\n\
	movs r0, #0x52\n\
	strb r0, [r6, #3]\n\
	b _RETURN\n\
_080F106A:\n\
	ldr r6, _080F10B0 @ =gStageRun\n\
	movs r0, #0xb4\n\
	lsls r0, r0, #1\n\
	adds r5, r6, r0\n\
	ldr r0, [r5]\n\
	movs r4, #1\n\
	rsbs r4, r4, #0\n\
	cmp r0, r4\n\
	beq _080F1086\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	bl FadeOutBGM\n\
	str r4, [r5]\n\
_080F1086:\n\
	ldr r2, _080F10B4 @ =gTextWindow+8\n\
	ldrh r1, [r2]\n\
	movs r0, #2\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	movs r1, #0xaa\n\
	lsls r1, r1, #1\n\
	adds r0, r6, r1\n\
	ldr r0, [r0]\n\
	cmp r0, #0\n\
	bne _RETURN\n\
	bl ExitProcess\n\
_RETURN:\n\
	add sp, #8\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080F10B0: .4byte gStageRun\n\
_080F10B4: .4byte gTextWindow+8\n\
.endif\n\
 .syntax divided\n");
}
