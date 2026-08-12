.if REGION_US
	push	{r4, r5, r6, r7, lr}
	mov	r7, sl
	mov	r6, r9
	mov	r5, r8
	push	{r5, r6, r7}
	sub	sp, #8
	adds	r6, r0, #0
	ldrb	r0, [r6, #2]
	cmp	r0, #9
	bls _US_080EF852
	b _US_080EFE32
_US_080EF852:
	lsls	r0, r0, #2
	ldr	r1, _US_080EF85C
	adds	r0, r0, r1
	ldr	r0, [r0, #0]
	mov	pc, r0
	.align 2, 0
_US_080EF85C: .4byte _US_080EF860
_US_080EF860:
	.4byte _US_080EF888
	.4byte _US_080EF8B4
	.4byte _US_080EF91C
	.4byte _US_080EF998
	.4byte _US_080EFA24
	.4byte _US_080EFA2E
	.4byte _US_080EFC0C
	.4byte _US_080EFD2A
	.4byte _US_080EFD42
	.4byte _US_080EFD8C
_US_080EF888:
	ldr	r1, _US_080EF8F8
	movs	r0, #0
	strh	r0, [r1, #0]
	ldr	r2, _US_080EF8FC
	ldrh	r1, [r2, #0]
	ldr	r0, _US_080EF900
	ands	r0, r1
	movs	r4, #0
	ldr	r1, _US_080EF904
	ands	r0, r1
	movs	r3, #128
	lsls	r3, r3, #1
	adds	r1, r3, #0
	orrs	r0, r1
	strh	r0, [r2, #0]
	str	r4, [r2, #12]
	bl LoadAsciiBold
	strh	r4, [r6, #6]
	ldrb	r0, [r6, #2]
	adds	r0, #1
	strb	r0, [r6, #2]
_US_080EF8B4:
	ldrh	r0, [r6, #6]
	adds	r0, #1
	adds	r1, r0, #0
	strh	r0, [r6, #6]
	ldr	r2, _US_080EF8F8
	ldr	r4, _US_080EF908
	adds	r0, r2, r4
	strb	r1, [r0, #0]
	movs	r0, #255
	ands	r0, r1
	ldr	r3, _US_080EF90C
	adds	r1, r2, r3
	strb	r0, [r1, #0]
	subs	r4, #2
	adds	r2, r2, r4
	strb	r0, [r2, #0]
	ldr	r0, _US_080EF910
	ldr	r1, _US_080EF914
	adds	r0, r0, r1
	ldrh	r0, [r0, #0]
	ldr	r1, _US_080EF918
	adds	r0, r0, r1
	movs	r1, #1
	movs	r2, #7
	bl PrintString
	movs	r2, #6
	ldrsh	r0, [r6, r2]
	cmp	r0, #31
	bgt _US_080EF8F2
	b _US_080EFE32
_US_080EF8F2:
	movs	r0, #0
	b _US_080EFD6A
	movs	r0, r0
	.align 2, 0
_US_080EF8F8: .4byte gPaletteManager
_US_080EF8FC: .4byte gVideoRegBuffer
_US_080EF900: .4byte 0x0000FFF8
_US_080EF904: .4byte 0x0000F0FF
_US_080EF908: .4byte 0x00000402
_US_080EF90C: .4byte 0x00000401
_US_080EF910: .4byte StringOfsTable
_US_080EF914: .4byte 0x00000316
_US_080EF918: .4byte gStringData
_US_080EF91C:
	ldr	r7, _US_080EF984
	ldrh	r1, [r7, #6]
	movs	r0, #192
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EF936
	movs	r0, #1
	bl PlaySound
	ldrh	r0, [r6, #4]
	movs	r1, #1
	eors	r0, r1
	strh	r0, [r6, #4]
_US_080EF936:
	ldr	r5, _US_080EF988
	ldr	r3, _US_080EF98C
	adds	r0, r5, r3
	ldrh	r0, [r0, #0]
	ldr	r4, _US_080EF990
	adds	r0, r0, r4
	movs	r1, #1
	movs	r2, #7
	bl PrintString
	ldrh	r0, [r5, #0]
	adds	r0, r0, r4
	movs	r4, #4
	ldrsh	r2, [r6, r4]
	lsls	r2, r2, #1
	adds	r2, #9
	movs	r1, #1
	bl PrintString
	ldrh	r1, [r7, #4]
	movs	r0, #1
	ands	r0, r1
	cmp	r0, #0
	bne _US_080EF968
	b _US_080EFE32
_US_080EF968:
	movs	r0, #2
	bl PlaySound
	movs	r1, #4
	ldrsh	r0, [r6, r1]
	cmp	r0, #0
	bne _US_080EF978
	b _US_080EFD6C
_US_080EF978:
	ldr	r0, _US_080EF994
	strh	r0, [r6, #4]
	movs	r0, #9
	strb	r0, [r6, #2]
	b _US_080EFE32
	movs	r0, r0
	.align 2, 0
_US_080EF984: .4byte gJoypad
_US_080EF988: .4byte StringOfsTable
_US_080EF98C: .4byte 0x00000316
_US_080EF990: .4byte gStringData
_US_080EF994: .4byte 0x0000018B
_US_080EF998:
	movs	r5, #0
	ldr	r7, _US_080EFAC0
	ldr	r2, _US_080EFAC4
	adds	r2, r2, r7
	mov	r8, r2
_US_080EF9A2:
	ldr	r0, _US_080EFAC8
	adds	r0, r5, r0
	movs	r1, #0
	strb	r1, [r0, #0]
	lsls	r0, r5, #24
	lsrs	r4, r0, #24
	adds	r0, r4, #0
	movs	r1, #148
	lsls	r1, r1, #2
	bl ValidateSector
	cmp	r0, #0
	beq _US_080EFA18
	adds	r0, r4, #0
	ldr	r1, _US_080EFACC
	movs	r2, #148
	lsls	r2, r2, #2
	bl sram_08003378
	ldr	r4, _US_080EFAD0
_US_080EF9CA:
	bl UpdateSram
	ldrb	r0, [r4, #0]
	cmp	r0, #1
	beq _US_080EF9CA
	movs	r3, #30
	ldrsh	r0, [r4, r3]
	cmp	r0, #0
	beq _US_080EF9CA
	ldr	r1, _US_080EFAD0
	ldrb	r0, [r1, #0]
	cmp	r0, #1
	beq _US_080EFA18
	movs	r4, #30
	ldrsh	r0, [r1, r4]
	cmp	r0, #0
	ble _US_080EFA18
	ldr	r0, _US_080EFAC8
	adds	r0, r5, r0
	movs	r1, #1
	strb	r1, [r0, #0]
	ldr	r1, _US_080EFAD4
	lsls	r2, r5, #2
	adds	r1, r2, r1
	ldr	r0, [r7, #12]
	str	r0, [r1, #0]
	ldr	r0, _US_080EFAD8
	adds	r2, r2, r0
	ldrb	r0, [r7, #1]
	str	r0, [r2, #0]
	ldr	r0, _US_080EFADC
	adds	r0, r5, r0
	mov	r2, r8
	ldrh	r1, [r2, #0]
	strb	r1, [r0, #0]
	ldr	r0, _US_080EFAE0
	adds	r0, r5, r0
	ldrh	r1, [r2, #2]
	strb	r1, [r0, #0]
_US_080EFA18:
	adds	r5, #1
	cmp	r5, #4
	ble _US_080EF9A2
	ldrb	r0, [r6, #2]
	adds	r0, #1
	strb	r0, [r6, #2]
_US_080EFA24:
	movs	r0, #0
	strh	r0, [r6, #4]
	ldrb	r0, [r6, #2]
	adds	r0, #1
	strb	r0, [r6, #2]
_US_080EFA2E:
	ldr	r3, _US_080EFAE4
	mov	r8, r3
	movs	r0, #198
	lsls	r0, r0, #2
	add	r0, r8
	ldrh	r0, [r0, #0]
	ldr	r7, _US_080EFAE8
	adds	r0, r0, r7
	movs	r1, #9
	movs	r2, #3
	bl PrintString
	ldr	r4, _US_080EFAEC
	ldrh	r1, [r4, #6]
	movs	r0, #128
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFA66
	movs	r0, #1
	bl PlaySound
	movs	r1, #4
	ldrsh	r0, [r6, r1]
	adds	r0, #1
	movs	r1, #5
	bl __modsi3
	strh	r0, [r6, #4]
_US_080EFA66:
	ldrh	r1, [r4, #6]
	movs	r0, #64
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFA84
	movs	r0, #1
	bl PlaySound
	movs	r2, #4
	ldrsh	r0, [r6, r2]
	adds	r0, #4
	movs	r1, #5
	bl __modsi3
	strh	r0, [r6, #4]
_US_080EFA84:
	movs	r5, #0
	mov	sl, r7
	movs	r3, #224
	lsls	r3, r3, #19
	mov	r9, r3
	movs	r7, #7
	ldr	r4, _US_080EFAE4
	adds	r4, #62
	mov	r8, r4
_US_080EFA96:
	ldr	r0, _US_080EFAC8
	adds	r0, r5, r0
	ldrb	r0, [r0, #0]
	cmp	r0, #0
	bne _US_080EFAF0
	mov	r1, r8
	ldrh	r0, [r1, #0]
	add	r0, sl
	movs	r1, #7
	adds	r2, r7, #0
	bl PrintString
	ldr	r2, _US_080EFAE4
	ldrh	r0, [r2, #2]
	add	r0, sl
	movs	r1, #9
	adds	r2, r7, #0
	bl PrintString
	b _US_080EFB1A
	movs	r0, r0
	.align 2, 0
_US_080EFAC0: .4byte SaveState_02000110+0x1b4
_US_080EFAC4: .4byte 0xFFFFFE4C
_US_080EFAC8: .4byte gSaveSlotMetadata_02000360
_US_080EFACC: .4byte SaveState_02000110
_US_080EFAD0: .4byte gSramState
_US_080EFAD4: .4byte gSaveSlotMetadata_02000360+0x8
_US_080EFAD8: .4byte gSaveSlotMetadata_02000360+0x20
_US_080EFADC: .4byte gSaveSlotMetadata_02000360+0x34
_US_080EFAE0: .4byte gSaveSlotMetadata_02000360+0x3c
_US_080EFAE4: .4byte StringOfsTable
_US_080EFAE8: .4byte gStringData
_US_080EFAEC: .4byte gJoypad
_US_080EFAF0:
	lsls	r0, r5, #24
	lsrs	r0, r0, #24
	ldr	r1, _US_080EFB60
	lsls	r3, r5, #2
	adds	r1, r3, r1
	ldrb	r1, [r1, #0]
	ldr	r2, _US_080EFB64
	adds	r3, r3, r2
	ldr	r2, [r3, #0]
	ldr	r3, _US_080EFB68
	adds	r3, r5, r3
	ldrb	r3, [r3, #0]
	ldr	r4, _US_080EFB6C
	adds	r4, r5, r4
	ldrb	r4, [r4, #0]
	str	r4, [sp, #0]
	mov	r4, r9
	lsrs	r4, r4, #24
	str	r4, [sp, #4]
	bl PrintSaveDataRowText
_US_080EFB1A:
	movs	r0, #128
	lsls	r0, r0, #18
	add	r9, r0
	adds	r7, #2
	movs	r1, #2
	add	r8, r1
	adds	r5, #1
	cmp	r5, #4
	ble _US_080EFA96
	ldr	r0, _US_080EFB70
	ldrh	r0, [r0, #0]
	ldr	r1, _US_080EFB74
	adds	r0, r0, r1
	movs	r3, #4
	ldrsh	r2, [r6, r3]
	lsls	r2, r2, #1
	adds	r2, #7
	movs	r1, #5
	bl PrintString
	ldr	r0, _US_080EFB78
	ldrh	r1, [r0, #4]
	movs	r0, #2
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFB7C
	movs	r0, #3
	bl PlaySound
	movs	r0, #0
	strh	r0, [r6, #4]
	movs	r0, #2
	strb	r0, [r6, #2]
	b _US_080EFE32
	movs	r0, r0
	.align 2, 0
_US_080EFB60: .4byte gSaveSlotMetadata_02000360+0x20
_US_080EFB64: .4byte gSaveSlotMetadata_02000360+0x8
_US_080EFB68: .4byte gSaveSlotMetadata_02000360+0x34
_US_080EFB6C: .4byte gSaveSlotMetadata_02000360+0x3c
_US_080EFB70: .4byte StringOfsTable
_US_080EFB74: .4byte gStringData
_US_080EFB78: .4byte gJoypad
_US_080EFB7C:
	movs	r4, #1
	adds	r0, r4, #0
	ands	r0, r1
	cmp	r0, #0
	bne _US_080EFB88
	b _US_080EFE32
_US_080EFB88:
	movs	r0, #2
	bl PlaySound
	ldr	r0, _US_080EFBEC
	movs	r2, #4
	ldrsh	r1, [r6, r2]
	adds	r1, r1, r0
	ldrb	r0, [r1, #0]
	cmp	r0, #0
	bne _US_080EFC08
	ldr	r3, _US_080EFBF0
	adds	r4, r6, r3
	adds	r0, r4, #0
	bl StoreStoryData
	ldr	r1, _US_080EFBF4
	adds	r0, r6, r1
	ldr	r0, [r0, #0]
	ldr	r2, _US_080EFBF8
	adds	r1, r6, r2
	bl StoreZeroStatus
	ldr	r2, _US_080EFBFC
	ldrb	r1, [r2, #4]
	movs	r0, #8
	orrs	r1, r0
	strb	r1, [r2, #4]
	ldrb	r1, [r4, #0]
	orrs	r0, r1
	strb	r0, [r4, #0]
	ldrb	r0, [r6, #4]
	ldr	r3, _US_080EFC00
	adds	r1, r6, r3
	movs	r2, #148
	lsls	r2, r2, #2
	bl sram_08003330
	ldr	r4, _US_080EFC04
_US_080EFBD4:
	bl UpdateSram
	ldrb	r0, [r4, #0]
	cmp	r0, #2
	beq _US_080EFBD4
	movs	r1, #28
	ldrsh	r0, [r4, r1]
	cmp	r0, #0
	beq _US_080EFBD4
	movs	r0, #7
	strb	r0, [r6, #2]
	b _US_080EFE32
	.align 2, 0
_US_080EFBEC: .4byte gSaveSlotMetadata_02000360
_US_080EFBF0: .4byte 0x00006270
_US_080EFBF4: .4byte 0x000064AC
_US_080EFBF8: .4byte 0x00006460
_US_080EFBFC: .4byte gCurStory
_US_080EFC00: .4byte 0x0000625C
_US_080EFC04: .4byte gSramState
_US_080EFC08:
	strh	r4, [r6, #10]
	b _US_080EFD6C
_US_080EFC0C:
	ldrb	r0, [r6, #4]
	ldr	r1, _US_080EFC8C
	movs	r2, #4
	ldrsh	r5, [r6, r2]
	lsls	r2, r5, #2
	adds	r1, r2, r1
	ldrb	r1, [r1, #0]
	ldr	r3, _US_080EFC90
	adds	r2, r2, r3
	ldr	r2, [r2, #0]
	ldr	r3, _US_080EFC94
	adds	r3, r5, r3
	ldrb	r3, [r3, #0]
	ldr	r4, _US_080EFC98
	adds	r5, r5, r4
	ldrb	r4, [r5, #0]
	str	r4, [sp, #0]
	movs	r4, #6
	str	r4, [sp, #4]
	bl PrintSaveDataRowText
	ldr	r7, _US_080EFC9C
	ldrh	r1, [r7, #6]
	movs	r0, #192
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFC50
	movs	r0, #1
	bl PlaySound
	ldrh	r0, [r6, #10]
	movs	r1, #1
	eors	r0, r1
	strh	r0, [r6, #10]
_US_080EFC50:
	ldr	r5, _US_080EFCA0
	movs	r3, #199
	lsls	r3, r3, #2
	adds	r0, r5, r3
	ldrh	r0, [r0, #0]
	ldr	r4, _US_080EFCA4
	adds	r0, r0, r4
	movs	r1, #7
	movs	r2, #9
	bl PrintString
	ldrh	r0, [r5, #0]
	adds	r0, r0, r4
	movs	r4, #10
	ldrsh	r2, [r6, r4]
	lsls	r2, r2, #1
	adds	r2, #11
	movs	r1, #7
	bl PrintString
	ldrh	r1, [r7, #4]
	movs	r0, #2
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFCA8
	movs	r0, #3
	bl PlaySound
	b _US_080EFD24
	movs	r0, r0
	.align 2, 0
_US_080EFC8C: .4byte gSaveSlotMetadata_02000360+0x20
_US_080EFC90: .4byte gSaveSlotMetadata_02000360+0x8
_US_080EFC94: .4byte gSaveSlotMetadata_02000360+0x34
_US_080EFC98: .4byte gSaveSlotMetadata_02000360+0x3c
_US_080EFC9C: .4byte gJoypad
_US_080EFCA0: .4byte StringOfsTable
_US_080EFCA4: .4byte gStringData
_US_080EFCA8:
	movs	r0, #1
	ands	r0, r1
	cmp	r0, #0
	bne _US_080EFCB2
	b _US_080EFE32
_US_080EFCB2:
	movs	r0, #2
	bl PlaySound
	movs	r1, #10
	ldrsh	r0, [r6, r1]
	cmp	r0, #0
	bne _US_080EFD24
	ldr	r2, _US_080EFD0C
	adds	r4, r6, r2
	adds	r0, r4, #0
	bl StoreStoryData
	ldr	r3, _US_080EFD10
	adds	r0, r6, r3
	ldr	r0, [r0, #0]
	ldr	r2, _US_080EFD14
	adds	r1, r6, r2
	bl StoreZeroStatus
	ldr	r2, _US_080EFD18
	ldrb	r1, [r2, #4]
	movs	r0, #8
	orrs	r1, r0
	strb	r1, [r2, #4]
	ldrb	r1, [r4, #0]
	orrs	r0, r1
	strb	r0, [r4, #0]
	ldrb	r0, [r6, #4]
	ldr	r3, _US_080EFD1C
	adds	r1, r6, r3
	movs	r2, #148
	lsls	r2, r2, #2
	bl sram_08003330
	ldr	r4, _US_080EFD20
_US_080EFCF8:
	bl UpdateSram
	ldrb	r0, [r4, #0]
	cmp	r0, #2
	beq _US_080EFCF8
	movs	r1, #28
	ldrsh	r0, [r4, r1]
	cmp	r0, #0
	beq _US_080EFCF8
	b _US_080EFD6C
	.align 2, 0
_US_080EFD0C: .4byte 0x00006270
_US_080EFD10: .4byte 0x000064AC
_US_080EFD14: .4byte 0x00006460
_US_080EFD18: .4byte gCurStory
_US_080EFD1C: .4byte 0x0000625C
_US_080EFD20: .4byte gSramState
_US_080EFD24:
	movs	r0, #5
	strb	r0, [r6, #2]
	b _US_080EFE32
_US_080EFD2A:
	ldr	r1, _US_080EFD74
	ldrb	r0, [r1, #0]
	cmp	r0, #2
	bne _US_080EFD34
	b _US_080EFE32
_US_080EFD34:
	movs	r2, #28
	ldrsh	r0, [r1, r2]
	cmp	r0, #0
	beq _US_080EFE32
	ldrb	r0, [r6, #2]
	adds	r0, #1
	strb	r0, [r6, #2]
_US_080EFD42:
	ldr	r0, _US_080EFD78
	ldr	r3, _US_080EFD7C
	adds	r0, r0, r3
	ldrh	r0, [r0, #0]
	ldr	r1, _US_080EFD80
	adds	r0, r0, r1
	movs	r1, #5
	movs	r2, #9
	bl PrintString
	ldr	r0, _US_080EFD84
	ldrh	r1, [r0, #4]
	movs	r0, #3
	ands	r0, r1
	cmp	r0, #0
	beq _US_080EFE32
	movs	r0, #2
	bl PlaySound
	ldr	r0, _US_080EFD88
_US_080EFD6A:
	strh	r0, [r6, #4]
_US_080EFD6C:
	ldrb	r0, [r6, #2]
	adds	r0, #1
	strb	r0, [r6, #2]
	b _US_080EFE32
	.align 2, 0
_US_080EFD74: .4byte gSramState
_US_080EFD78: .4byte StringOfsTable
_US_080EFD7C: .4byte 0x0000031A
_US_080EFD80: .4byte gStringData
_US_080EFD84: .4byte gJoypad
_US_080EFD88: .4byte 0x0000018D
_US_080EFD8C:
	ldrh	r0, [r6, #6]
	subs	r0, #1
	adds	r1, r0, #0
	strh	r0, [r6, #6]
	ldr	r2, _US_080EFDCC
	ldr	r4, _US_080EFDD0
	adds	r0, r2, r4
	strb	r1, [r0, #0]
	movs	r0, #255
	ands	r0, r1
	ldr	r3, _US_080EFDD4
	adds	r1, r2, r3
	strb	r0, [r1, #0]
	subs	r4, #2
	adds	r2, r2, r4
	strb	r0, [r2, #0]
	movs	r0, #4
	ldrsh	r1, [r6, r0]
	ldr	r0, _US_080EFDD8
	cmp	r1, r0
	bne _US_080EFDE8
	ldr	r0, _US_080EFDDC
	ldr	r1, _US_080EFDE0
	adds	r0, r0, r1
	ldrh	r0, [r0, #0]
	ldr	r1, _US_080EFDE4
	adds	r0, r0, r1
	movs	r1, #5
	movs	r2, #9
	bl PrintString
	b _US_080EFDFC
	.align 2, 0
_US_080EFDCC: .4byte gPaletteManager
_US_080EFDD0: .4byte 0x00000402
_US_080EFDD4: .4byte 0x00000401
_US_080EFDD8: .4byte 0x0000018D
_US_080EFDDC: .4byte StringOfsTable
_US_080EFDE0: .4byte 0x0000031A
_US_080EFDE4: .4byte gStringData
_US_080EFDE8:
	ldr	r0, _US_080EFE44
	ldr	r2, _US_080EFE48
	adds	r0, r0, r2
	ldrh	r0, [r0, #0]
	ldr	r1, _US_080EFE4C
	adds	r0, r0, r1
	movs	r1, #1
	movs	r2, #7
	bl PrintString
_US_080EFDFC:
	movs	r3, #6
	ldrsh	r0, [r6, r3]
	cmp	r0, #0
	bne _US_080EFE32
	ldr	r3, _US_080EFE50
	ldrb	r2, [r3, #4]
	movs	r1, #247
	adds	r0, r1, #0
	ands	r0, r2
	strb	r0, [r3, #4]
	ldr	r4, _US_080EFE54
	adds	r2, r6, r4
	ldrb	r0, [r2, #0]
	ands	r1, r0
	strb	r1, [r2, #0]
	ldr	r1, _US_080EFE58
	adds	r0, r6, r1
	ldrh	r0, [r0, #0]
	cmp	r0, #16
	bne _US_080EFE28
	bl ExitProcess
_US_080EFE28:
	movs	r1, #192
	lsls	r1, r1, #2
	adds	r0, r6, #0
	bl SetGameMode
_US_080EFE32:
	add	sp, #8
	pop	{r3, r4, r5}
	mov	r8, r3
	mov	r9, r4
	mov	sl, r5
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
	movs	r0, r0
	.align 2, 0
_US_080EFE44: .4byte StringOfsTable
_US_080EFE48: .4byte 0x00000316
_US_080EFE4C: .4byte gStringData
_US_080EFE50: .4byte gCurStory
_US_080EFE54: .4byte 0x00006270
_US_080EFE58: .4byte 0x00006260
.else
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	adds r6, r0, #0
	ldrb r0, [r6, #2]
	cmp r0, #9
	bls _080EFD1E
	b _080F02C6
_080EFD1E:
	lsls r0, r0, #2
	ldr r1, _080EFD28 @ =_080EFD2C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080EFD28: .4byte _080EFD2C
_080EFD2C: @ jump table
	.4byte _080EFD54 @ case 0
	.4byte _080EFD80 @ case 1
	.4byte _080EFDE8 @ case 2
	.4byte _080EFE64 @ case 3
	.4byte _080EFEF2 @ case 4
	.4byte _080EFEFC @ case 5
	.4byte _080F00B8 @ case 6
	.4byte _080F01BC @ case 7
	.4byte _080F01D4 @ case 8
	.4byte _080F0220 @ case 9
_080EFD54:
	ldr r1, _080EFDC4 @ =gPaletteManager
	movs r0, #0
	strh r0, [r1]
	ldr r2, _080EFDC8 @ =gVideoRegBuffer
	ldrh r1, [r2]
	ldr r0, _080EFDCC @ =0x0000FFF8
	ands r0, r1
	movs r4, #0
	ldr r1, _080EFDD0 @ =0x0000F0FF
	ands r0, r1
	movs r3, #0x80
	lsls r3, r3, #1
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	str r4, [r2, #0xc]
	bl LoadAsciiBold
	strh r4, [r6, #6]
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
_080EFD80:
	ldrh r0, [r6, #6]
	adds r0, #1
	adds r1, r0, #0
	strh r0, [r6, #6]
	ldr r2, _080EFDC4 @ =gPaletteManager
	ldr r4, _080EFDD4 @ =0x00000402
	adds r0, r2, r4
	strb r1, [r0]
	movs r0, #0xff
	ands r0, r1
	ldr r3, _080EFDD8 @ =0x00000401
	adds r1, r2, r3
	strb r0, [r1]
	subs r4, #2
	adds r2, r2, r4
	strb r0, [r2]
	ldr r0, _080EFDDC @ =StringOfsTable
	ldr r1, _080EFDE0 @ =0x00000316
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080EFDE4 @ =gStringData
	adds r0, r0, r1
	movs r1, #9
	movs r2, #7
	bl PrintString
	movs r2, #6
	ldrsh r0, [r6, r2]
	cmp r0, #0x1f
	bgt _080EFDBE
	b _080F02C6
_080EFDBE:
	movs r0, #0
	b _080F01FC
	.align 2, 0
_080EFDC4: .4byte gPaletteManager
_080EFDC8: .4byte gVideoRegBuffer
_080EFDCC: .4byte 0x0000FFF8
_080EFDD0: .4byte 0x0000F0FF
_080EFDD4: .4byte 0x00000402
_080EFDD8: .4byte 0x00000401
_080EFDDC: .4byte StringOfsTable
_080EFDE0: .4byte 0x00000316
_080EFDE4: .4byte gStringData
_080EFDE8:
	ldr r7, _080EFE50 @ =gJoypad
	ldrh r1, [r7, #6]
	movs r0, #0xc0
	ands r0, r1
	cmp r0, #0
	beq _080EFE02
	movs r0, #1
	bl PlaySound
	ldrh r0, [r6, #4]
	movs r1, #1
	eors r0, r1
	strh r0, [r6, #4]
_080EFE02:
	ldr r5, _080EFE54 @ =StringOfsTable
	ldr r3, _080EFE58 @ =0x00000316
	adds r0, r5, r3
	ldrh r0, [r0]
	ldr r4, _080EFE5C @ =gStringData
	adds r0, r0, r4
	movs r1, #9
	movs r2, #7
	bl PrintString
	ldrh r0, [r5]
	adds r0, r0, r4
	movs r4, #4
	ldrsh r2, [r6, r4]
	lsls r2, r2, #1
	adds r2, #9
	movs r1, #9
	bl PrintString
	ldrh r1, [r7, #4]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080EFE34
	b _080F02C6
_080EFE34:
	movs r0, #2
	bl PlaySound
	movs r1, #4
	ldrsh r0, [r6, r1]
	cmp r0, #0
	bne _080EFE44
	b _080F01FE
_080EFE44:
	ldr r0, _080EFE60 @ =0x0000018B
	strh r0, [r6, #4]
	movs r0, #9
	strb r0, [r6, #2]
	b _080F02C6
	.align 2, 0
_080EFE50: .4byte gJoypad
_080EFE54: .4byte StringOfsTable
_080EFE58: .4byte 0x00000316
_080EFE5C: .4byte gStringData
_080EFE60: .4byte 0x0000018B
_080EFE64:
	movs r5, #0
	ldr r2, _080EFE8C @ =0x020002C4
	mov r8, r2
	ldr r3, _080EFE90 @ =0xFFFFFE4C
	add r3, r8
	mov sb, r3
_080EFE70:
	lsls r0, r5, #0x18
	lsrs r4, r0, #0x18
	adds r0, r4, #0
	movs r1, #0x94
	lsls r1, r1, #2
	bl ValidateSector
	adds r1, r0, #0
	cmp r1, #0
	bne _080EFE98
	ldr r0, _080EFE94 @ =gSaveSlotMetadata_02000360
	adds r0, r5, r0
	b _080EFEE4
	.align 2, 0
_080EFE8C: .4byte 0x020002C4
_080EFE90: .4byte 0xFFFFFE4C
_080EFE94: .4byte gSaveSlotMetadata_02000360
_080EFE98:
	ldr r0, _080EFF8C @ =gSaveSlotMetadata_02000360
	adds r0, r5, r0
	movs r1, #1
	strb r1, [r0]
	adds r0, r4, #0
	ldr r1, _080EFF90 @ =SaveState_02000110
	movs r2, #0x94
	lsls r2, r2, #2
	bl sram_08003378
	lsls r7, r5, #2
	ldr r4, _080EFF94 @ =gSramState
_080EFEB0:
	bl UpdateSram
	ldrb r0, [r4]
	cmp r0, #1
	beq _080EFEB0
	movs r1, #0x1e
	ldrsh r0, [r4, r1]
	cmp r0, #0
	beq _080EFEB0
	ldr r0, _080EFF98 @ =0x02000368
	adds r0, r7, r0
	mov r2, r8
	ldr r1, [r2, #0xc]
	str r1, [r0]
	ldr r0, _080EFF9C @ =0x02000380
	adds r0, r7, r0
	ldrb r1, [r2, #1]
	str r1, [r0]
	ldr r0, _080EFFA0 @ =0x02000394
	adds r0, r5, r0
	mov r3, sb
	ldrh r1, [r3]
	strb r1, [r0]
	ldr r0, _080EFFA4 @ =0x0200039C
	adds r0, r5, r0
	ldrh r1, [r3, #2]
_080EFEE4:
	strb r1, [r0]
	adds r5, #1
	cmp r5, #4
	ble _080EFE70
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
_080EFEF2:
	movs r0, #0
	strh r0, [r6, #4]
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
_080EFEFC:
	ldr r4, _080EFFA8 @ =StringOfsTable
	mov r8, r4
	movs r0, #0xc6
	lsls r0, r0, #2
	add r0, r8
	ldrh r0, [r0]
	ldr r7, _080EFFAC @ =gStringData
	adds r0, r0, r7
	movs r1, #9
	movs r2, #3
	bl PrintString
	ldr r4, _080EFFB0 @ =gJoypad
	ldrh r1, [r4, #6]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _080EFF34
	movs r0, #1
	bl PlaySound
	movs r1, #4
	ldrsh r0, [r6, r1]
	adds r0, #1
	movs r1, #5
	bl __modsi3
	strh r0, [r6, #4]
_080EFF34:
	ldrh r1, [r4, #6]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080EFF52
	movs r0, #1
	bl PlaySound
	movs r2, #4
	ldrsh r0, [r6, r2]
	adds r0, #4
	movs r1, #5
	bl __modsi3
	strh r0, [r6, #4]
_080EFF52:
	movs r5, #0
	mov sl, r7
	movs r3, #0xe0
	lsls r3, r3, #0x13
	mov sb, r3
	movs r7, #7
	ldr r4, _080EFFA8 @ =StringOfsTable
	adds r4, #0x3e
	mov r8, r4
_080EFF64:
	ldr r0, _080EFF8C @ =gSaveSlotMetadata_02000360
	adds r0, r5, r0
	ldrb r0, [r0]
	cmp r0, #0
	bne _080EFFB4
	mov r1, r8
	ldrh r0, [r1]
	add r0, sl
	movs r1, #7
	adds r2, r7, #0
	bl PrintString
	ldr r2, _080EFFA8 @ =StringOfsTable
	ldrh r0, [r2, #2]
	add r0, sl
	movs r1, #9
	adds r2, r7, #0
	bl PrintString
	b _080EFFDE
	.align 2, 0
_080EFF8C: .4byte gSaveSlotMetadata_02000360
_080EFF90: .4byte SaveState_02000110
_080EFF94: .4byte gSramState
_080EFF98: .4byte 0x02000368
_080EFF9C: .4byte 0x02000380
_080EFFA0: .4byte 0x02000394
_080EFFA4: .4byte 0x0200039C
_080EFFA8: .4byte StringOfsTable
_080EFFAC: .4byte gStringData
_080EFFB0: .4byte gJoypad
_080EFFB4:
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _080F0024 @ =0x02000380
	lsls r3, r5, #2
	adds r1, r3, r1
	ldrb r1, [r1]
	ldr r2, _080F0028 @ =0x02000368
	adds r3, r3, r2
	ldr r2, [r3]
	ldr r3, _080F002C @ =0x02000394
	adds r3, r5, r3
	ldrb r3, [r3]
	ldr r4, _080F0030 @ =0x0200039C
	adds r4, r5, r4
	ldrb r4, [r4]
	str r4, [sp]
	mov r4, sb
	lsrs r4, r4, #0x18
	str r4, [sp, #4]
	bl PrintSaveDataRowText
_080EFFDE:
	movs r0, #0x80
	lsls r0, r0, #0x12
	add sb, r0
	adds r7, #2
	movs r1, #2
	add r8, r1
	adds r5, #1
	cmp r5, #4
	ble _080EFF64
	ldr r0, _080F0034 @ =StringOfsTable
	ldrh r0, [r0]
	ldr r1, _080F0038 @ =gStringData
	adds r0, r0, r1
	movs r3, #4
	ldrsh r2, [r6, r3]
	lsls r2, r2, #1
	adds r2, #7
	movs r1, #5
	bl PrintString
	ldr r0, _080F003C @ =gJoypad
	ldrh r1, [r0, #4]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080F0040
	movs r0, #3
	bl PlaySound
	movs r0, #0
	strh r0, [r6, #4]
	movs r0, #2
	strb r0, [r6, #2]
	b _080F02C6
	.align 2, 0
_080F0024: .4byte 0x02000380
_080F0028: .4byte 0x02000368
_080F002C: .4byte 0x02000394
_080F0030: .4byte 0x0200039C
_080F0034: .4byte StringOfsTable
_080F0038: .4byte gStringData
_080F003C: .4byte gJoypad
_080F0040:
	movs r4, #1
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _080F004C
	b _080F02C6
_080F004C:
	movs r0, #2
	bl PlaySound
	ldr r0, _080F009C @ =gSaveSlotMetadata_02000360
	movs r2, #4
	ldrsh r1, [r6, r2]
	adds r1, r1, r0
	ldrb r0, [r1]
	cmp r0, #0
	bne _080F00B4
	ldr r3, _080F00A0 @ =0x00006270
	adds r4, r6, r3
	adds r0, r4, #0
	bl StoreStoryData
	ldr r1, _080F00A4 @ =0x000064AC
	adds r0, r6, r1
	ldr r0, [r0]
	ldr r2, _080F00A8 @ =0x00006460
	adds r1, r6, r2
	bl StoreZeroStatus
	ldr r2, _080F00AC @ =gCurStory
	ldrb r1, [r2, #4]
	movs r0, #8
	orrs r1, r0
	strb r1, [r2, #4]
	ldrb r1, [r4]
	orrs r0, r1
	strb r0, [r4]
	ldrb r0, [r6, #4]
	ldr r3, _080F00B0 @ =0x0000625C
	adds r1, r6, r3
	movs r2, #0x94
	lsls r2, r2, #2
	bl sram_08003330
	movs r0, #7
	strb r0, [r6, #2]
	b _080F02C6
	.align 2, 0
_080F009C: .4byte gSaveSlotMetadata_02000360
_080F00A0: .4byte 0x00006270
_080F00A4: .4byte 0x000064AC
_080F00A8: .4byte 0x00006460
_080F00AC: .4byte gCurStory
_080F00B0: .4byte 0x0000625C
_080F00B4:
	strh r4, [r6, #0xa]
	b _080F01FE
_080F00B8:
	ldrb r0, [r6, #4]
	ldr r1, _080F0180 @ =0x02000380
	movs r4, #4
	ldrsh r5, [r6, r4]
	lsls r2, r5, #2
	adds r1, r2, r1
	ldrb r1, [r1]
	ldr r3, _080F0184 @ =0x02000368
	adds r2, r2, r3
	ldr r2, [r2]
	ldr r3, _080F0188 @ =0x02000394
	adds r3, r5, r3
	ldrb r3, [r3]
	ldr r4, _080F018C @ =0x0200039C
	adds r5, r5, r4
	ldrb r4, [r5]
	str r4, [sp]
	movs r4, #6
	str r4, [sp, #4]
	bl PrintSaveDataRowText
	ldr r7, _080F0190 @ =gJoypad
	ldrh r1, [r7, #6]
	movs r0, #0xc0
	ands r0, r1
	cmp r0, #0
	beq _080F00FC
	movs r0, #1
	bl PlaySound
	ldrh r0, [r6, #0xa]
	movs r1, #1
	eors r0, r1
	strh r0, [r6, #0xa]
_080F00FC:
	ldr r5, _080F0194 @ =StringOfsTable
	movs r1, #0xc7
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrh r0, [r0]
	ldr r4, _080F0198 @ =gStringData
	adds r0, r0, r4
	movs r1, #9
	movs r2, #9
	bl PrintString
	ldrh r0, [r5]
	adds r0, r0, r4
	movs r3, #0xa
	ldrsh r2, [r6, r3]
	lsls r2, r2, #1
	adds r2, #0xb
	movs r1, #9
	bl PrintString
	ldrh r1, [r7, #4]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _080F01B0
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080F0138
	b _080F02C6
_080F0138:
	movs r0, #2
	bl PlaySound
	movs r4, #0xa
	ldrsh r0, [r6, r4]
	cmp r0, #0
	bne _080F01B6
	ldr r0, _080F019C @ =0x00006270
	adds r4, r6, r0
	adds r0, r4, #0
	bl StoreStoryData
	ldr r1, _080F01A0 @ =0x000064AC
	adds r0, r6, r1
	ldr r0, [r0]
	ldr r2, _080F01A4 @ =0x00006460
	adds r1, r6, r2
	bl StoreZeroStatus
	ldr r2, _080F01A8 @ =gCurStory
	ldrb r1, [r2, #4]
	movs r0, #8
	orrs r1, r0
	strb r1, [r2, #4]
	ldrb r1, [r4]
	orrs r0, r1
	strb r0, [r4]
	ldrb r0, [r6, #4]
	ldr r3, _080F01AC @ =0x0000625C
	adds r1, r6, r3
	movs r2, #0x94
	lsls r2, r2, #2
	bl sram_08003330
	b _080F01FE
	.align 2, 0
_080F0180: .4byte 0x02000380
_080F0184: .4byte 0x02000368
_080F0188: .4byte 0x02000394
_080F018C: .4byte 0x0200039C
_080F0190: .4byte gJoypad
_080F0194: .4byte StringOfsTable
_080F0198: .4byte gStringData
_080F019C: .4byte 0x00006270
_080F01A0: .4byte 0x000064AC
_080F01A4: .4byte 0x00006460
_080F01A8: .4byte gCurStory
_080F01AC: .4byte 0x0000625C
_080F01B0:
	movs r0, #3
	bl PlaySound
_080F01B6:
	movs r0, #5
	strb r0, [r6, #2]
	b _080F02C6
_080F01BC:
	ldr r1, _080F0208 @ =gSramState
	ldrb r0, [r1]
	cmp r0, #2
	bne _080F01C6
	b _080F02C6
_080F01C6:
	movs r4, #0x1c
	ldrsh r0, [r1, r4]
	cmp r0, #0
	beq _080F02C6
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
_080F01D4:
	ldr r0, _080F020C @ =StringOfsTable
	ldr r1, _080F0210 @ =0x0000031A
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080F0214 @ =gStringData
	adds r0, r0, r1
	movs r1, #0xa
	movs r2, #9
	bl PrintString
	ldr r0, _080F0218 @ =gJoypad
	ldrh r1, [r0, #4]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	beq _080F02C6
	movs r0, #2
	bl PlaySound
	ldr r0, _080F021C @ =0x0000018D
_080F01FC:
	strh r0, [r6, #4]
_080F01FE:
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
	b _080F02C6
	.align 2, 0
_080F0208: .4byte gSramState
_080F020C: .4byte StringOfsTable
_080F0210: .4byte 0x0000031A
_080F0214: .4byte gStringData
_080F0218: .4byte gJoypad
_080F021C: .4byte 0x0000018D
_080F0220:
	ldrh r0, [r6, #6]
	subs r0, #1
	adds r1, r0, #0
	strh r0, [r6, #6]
	ldr r2, _080F0264 @ =gPaletteManager
	ldr r3, _080F0268 @ =0x00000402
	adds r0, r2, r3
	strb r1, [r0]
	movs r0, #0xff
	ands r0, r1
	ldr r4, _080F026C @ =0x00000401
	adds r1, r2, r4
	strb r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r2, r2, r1
	strb r0, [r2]
	movs r2, #4
	ldrsh r1, [r6, r2]
	ldr r0, _080F0270 @ =0x0000018D
	cmp r1, r0
	bne _080F027C
	ldr r0, _080F0274 @ =StringOfsTable
	subs r3, #0xe8
	adds r0, r0, r3
	ldrh r0, [r0]
	ldr r1, _080F0278 @ =gStringData
	adds r0, r0, r1
	movs r1, #0xa
	movs r2, #9
	bl PrintString
	b _080F0290
	.align 2, 0
_080F0264: .4byte gPaletteManager
_080F0268: .4byte 0x00000402
_080F026C: .4byte 0x00000401
_080F0270: .4byte 0x0000018D
_080F0274: .4byte StringOfsTable
_080F0278: .4byte gStringData
_080F027C:
	ldr r0, _080F02D8 @ =StringOfsTable
	ldr r4, _080F02DC @ =0x00000316
	adds r0, r0, r4
	ldrh r0, [r0]
	ldr r1, _080F02E0 @ =gStringData
	adds r0, r0, r1
	movs r1, #9
	movs r2, #7
	bl PrintString
_080F0290:
	movs r1, #6
	ldrsh r0, [r6, r1]
	cmp r0, #0
	bne _080F02C6
	ldr r3, _080F02E4 @ =gCurStory
	ldrb r2, [r3, #4]
	movs r1, #0xf7
	adds r0, r1, #0
	ands r0, r2
	strb r0, [r3, #4]
	ldr r3, _080F02E8 @ =0x00006270
	adds r2, r6, r3
	ldrb r0, [r2]
	ands r1, r0
	strb r1, [r2]
	ldr r4, _080F02EC @ =0x00006260
	adds r0, r6, r4
	ldrh r0, [r0]
	cmp r0, #0x10
	bne _080F02BC
	bl ExitProcess
_080F02BC:
	movs r1, #0xc0
	lsls r1, r1, #2
	adds r0, r6, #0
	bl SetGameMode
_080F02C6:
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080F02D8: .4byte StringOfsTable
_080F02DC: .4byte 0x00000316
_080F02E0: .4byte gStringData
_080F02E4: .4byte gCurStory
_080F02E8: .4byte 0x00006270
_080F02EC: .4byte 0x00006260
.endif
