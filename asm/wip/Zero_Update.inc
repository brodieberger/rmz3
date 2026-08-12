.if REGION_US
	push	{r4, r5, r6, r7, lr}
	mov	r7, sl
	mov	r6, r9
	mov	r5, r8
	push	{r5, r6, r7}
	sub	sp, #32
	adds	r6, r0, #0
	ldr	r0, [r6, #84]
	ldr	r1, [r6, #88]
	str	r0, [sp, #0]
	str	r1, [sp, #4]
	ldrb	r1, [r6, #10]
	movs	r0, #1
	ands	r0, r1
	cmp	r0, #0
	bne _US_080294E2
	adds	r0, r6, #0
	bl resetSateliteElfPosition
_US_080294E2:
	ldr	r2, _US_08029500
	adds	r1, r6, r2
	ldrb	r0, [r1, #0]
	cmp	r0, #0
	beq _US_08029504
	subs	r0, #1
	strb	r0, [r1, #0]
	lsls	r0, r0, #24
	cmp	r0, #0
	beq _US_080294F8
	b _US_08029C2E
_US_080294F8:
	movs	r0, #33
	bl PlaySound
	b _US_08029C2E
	.align 2, 0
_US_08029500: .4byte 0x00000233
_US_08029504:
	adds	r4, r6, #0
	adds	r4, #250
	movs	r3, #0
	ldrsh	r1, [r4, r3]
	movs	r0, #1
	negs	r0, r0
	cmp	r1, r0
	bne _US_08029540
	ldrb	r0, [r6, #13]
	cmp	r0, #11
	beq _US_0802955A
	ldr	r0, _US_08029534
	ldr	r1, _US_08029538
	adds	r0, r0, r1
	ldr	r1, [r6, #88]
	ldr	r2, _US_0802953C
	adds	r1, r1, r2
	ldr	r0, [r0, #0]
	cmp	r0, r1
	bge _US_0802955A
	movs	r0, #50
	bl PlaySound
	b _US_08029558
	.align 2, 0
_US_08029534: .4byte gOverworld
_US_08029538: .4byte 0x0002C00C
_US_0802953C: .4byte 0xFFFFE200
_US_08029540:
	.2byte 0x481D
	ldr	r3, _US_080295BC
	adds	r0, r0, r3
	ldr	r1, [r0, #0]
	ldr	r0, [r6, #88]
	cmp	r1, r0
	ble _US_0802955A
	movs	r1, #0
	ldrsh	r0, [r4, r1]
	bl StopSound
	ldr	r0, _US_080295C0
_US_08029558:
	strh	r0, [r4, #0]
_US_0802955A:
	ldrb	r0, [r6, #13]
	adds	r5, r6, #0
	adds	r5, #232
	strb	r0, [r5, #0]
	ldrb	r0, [r6, #14]
	adds	r4, r6, #0
	adds	r4, #233
	strb	r0, [r4, #0]
	adds	r0, r6, #0
	bl HandlePlayerInput
	adds	r1, r6, #0
	adds	r1, #140
	ldr	r7, [r1, #0]
	movs	r0, #128
	lsls	r0, r0, #2
	ands	r7, r0
	str	r5, [sp, #16]
	str	r4, [sp, #20]
	str	r1, [sp, #8]
	ldr	r2, _US_080295C4
	adds	r2, r2, r6
	mov	r8, r2
	cmp	r7, #0
	bne _US_08029648
	adds	r0, r6, #0
	adds	r0, #164
	movs	r3, #0
	ldrsh	r1, [r0, r3]
	adds	r5, r0, #0
	cmp	r1, #0
	beq _US_080295EA
	ldrb	r1, [r2, #0]
	lsls	r1, r1, #3
	ldr	r0, _US_080295C8
	adds	r1, r1, r0
	adds	r0, r6, #0
	bl RecoilFromFloor
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #1
	bne _US_080295CC
	adds	r0, r6, #0
	bl InstantlyKilling
	b _US_080295EA
	movs	r4, #128
	lsls	r0, r0, #8
	.align 2, 0
_US_080295BC: .4byte 0x0002C00C
_US_080295C0: .4byte 0x0000FFFF
_US_080295C4: .4byte 0x00000147
_US_080295C8: .4byte gZeroRanges
_US_080295CC:
	cmp	r0, #2
	bne _US_080295EA
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r4, #140
	lsls	r4, r4, #1
	adds	r1, r6, r4
	strb	r0, [r1, #0]
	movs	r1, #0
	strh	r7, [r5, #0]
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
_US_080295EA:
	ldr	r0, [sp, #8]
	ldr	r4, [r0, #0]
	movs	r0, #128
	lsls	r0, r0, #2
	ands	r4, r0
	cmp	r4, #0
	bne _US_08029648
	movs	r1, #0
	ldrsh	r0, [r5, r1]
	cmp	r0, #0
	beq _US_08029648
	mov	r2, r8
	ldrb	r1, [r2, #0]
	lsls	r1, r1, #3
	ldr	r0, _US_08029634
	adds	r1, r1, r0
	adds	r0, r6, #0
	bl RecoilFromHazards
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #1
	bne _US_08029638
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r3, #140
	lsls	r3, r3, #1
	adds	r1, r6, r3
	strb	r0, [r1, #0]
	movs	r1, #0
	strh	r4, [r5, #0]
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
	b _US_08029642
	.align 2, 0
_US_08029634: .4byte gZeroRanges
_US_08029638:
	cmp	r0, #2
	bne _US_08029642
	adds	r0, r6, #0
	bl InstantlyKilling
_US_08029642:
	adds	r0, r6, #0
	bl CheckZeroHazard
_US_08029648:
	ldrb	r0, [r6, #13]
	adds	r4, r6, #0
	adds	r4, #180
	str	r4, [sp, #12]
	cmp	r0, #1
	beq _US_0802965C
	cmp	r0, #4
	beq _US_0802965C
	movs	r0, #0
	str	r0, [r4, #84]
_US_0802965C:
	movs	r0, #141
	lsls	r0, r0, #2
	adds	r4, r6, r0
	ldrb	r0, [r4, #0]
	cmp	r0, #0
	beq _US_0802966C
	subs	r0, #1
	b _US_0802968A
_US_0802966C:
	ldr	r0, _US_080297A4
	movs	r1, #232
	lsls	r1, r1, #1
	adds	r0, r0, r1
	ldrh	r1, [r0, #0]
	movs	r0, #127
	ands	r0, r1
	cmp	r0, #7
	bne _US_0802968C
	bl FUN_080101a8
	lsls	r0, r0, #16
	cmp	r0, #0
	beq _US_0802968C
	movs	r0, #16
_US_0802968A:
	strb	r0, [r4, #0]
_US_0802968C:
	movs	r3, #128
	lsls	r3, r3, #1
	adds	r2, r6, r3
	ldr	r0, [r6, #84]
	ldr	r1, [r6, #88]
	str	r0, [r2, #0]
	str	r1, [r2, #4]
	ldrb	r0, [r6, #30]
	lsls	r0, r0, #8
	adds	r1, r6, #0
	adds	r1, #112
	ldrb	r1, [r1, #0]
	orrs	r1, r0
	movs	r4, #159
	lsls	r4, r4, #1
	adds	r0, r6, r4
	movs	r2, #0
	mov	sl, r2
	strh	r1, [r0, #0]
	adds	r0, r6, #0
	adds	r0, #113
	ldrb	r1, [r0, #0]
	adds	r3, #64
	adds	r0, r6, r3
	strb	r1, [r0, #0]
	adds	r0, r6, #0
	adds	r0, #114
	ldrb	r0, [r0, #0]
	adds	r4, #3
	adds	r1, r6, r4
	strb	r0, [r1, #0]
	mov	r1, r8
	ldrb	r0, [r1, #0]
	adds	r3, #8
	adds	r2, r6, r3
	strb	r0, [r2, #0]
	mov	r4, sl
	strb	r4, [r1, #0]
	ldr	r1, [r6, #12]
	ldr	r0, _US_080297A8
	ands	r1, r0
	str	r2, [sp, #28]
	movs	r0, #128
	lsls	r0, r0, #3
	cmp	r1, r0
	beq _US_080296EE
	ldr	r1, _US_080297AC
	adds	r0, r6, r1
	strb	r4, [r0, #0]
_US_080296EE:
	movs	r2, #161
	lsls	r2, r2, #1
	adds	r1, r6, r2
	mov	r3, sl
	strb	r3, [r1, #0]
	ldr	r4, [sp, #8]
	ldr	r7, [r4, #0]
	movs	r0, #128
	lsls	r0, r0, #2
	ands	r7, r0
	str	r1, [sp, #24]
	cmp	r7, #0
	bne _US_080297F8
	adds	r4, r6, #0
	adds	r4, #164
	movs	r1, #0
	ldrsh	r0, [r4, r1]
	cmp	r0, #0
	beq _US_080297F8
	ldrb	r1, [r6, #13]
	subs	r0, r1, #5
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #1
	bls _US_080297F8
	cmp	r1, #10
	beq _US_080297F8
	ldr	r2, _US_080297B0
	mov	r9, r2
	mov	r3, r8
	ldrb	r0, [r3, #0]
	lsls	r0, r0, #3
	add	r0, r9
	movs	r2, #6
	ldrsh	r1, [r0, r2]
	ldr	r2, [r6, #88]
	subs	r1, r2, r1
	ldr	r5, _US_080297B4
	adds	r1, r1, r5
	movs	r3, #172
	lsls	r3, r3, #1
	adds	r0, r6, r3
	ldr	r0, [r0, #0]
	cmp	r1, r0
	bgt _US_08029774
	ldr	r0, [r6, #84]
	adds	r1, r2, #0
	bl IsVoidSpace
	lsls	r0, r0, #24
	cmp	r0, #0
	beq _US_080297F8
	ldr	r0, [r6, #84]
	mov	r2, r8
	ldrb	r1, [r2, #0]
	lsls	r1, r1, #3
	add	r1, r9
	movs	r3, #6
	ldrsh	r2, [r1, r3]
	ldr	r1, [r6, #88]
	subs	r1, r1, r2
	adds	r1, r1, r5
	bl IsVoidSpace
	lsls	r0, r0, #24
	cmp	r0, #0
	beq _US_080297F8
_US_08029774:
	ldr	r0, [r6, #84]
	ldr	r1, [r6, #88]
	ldr	r2, _US_080297B8
	adds	r1, r1, r2
	bl GetGroundMetatileAttr
	movs	r1, #128
	lsls	r1, r1, #3
	ands	r1, r0
	lsls	r1, r1, #16
	lsrs	r2, r1, #16
	cmp	r2, #0
	beq _US_080297BC
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r3, #140
	lsls	r3, r3, #1
	adds	r1, r6, r3
	strb	r0, [r1, #0]
	strh	r7, [r4, #0]
	b _US_080297F0
	movs	r0, r0
	.align 2, 0
_US_080297A4: .4byte gOverworld
_US_080297A8: .4byte 0x00FFFF00
_US_080297AC: .4byte 0x0000018D
_US_080297B0: .4byte gZeroRanges
_US_080297B4: .4byte 0xFFFFF800
_US_080297B8: .4byte 0xFFFFE200
_US_080297BC:
	.2byte 0x9903
	ldrb	r0, [r1, #0]
	subs	r0, #32
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #1
	bls _US_080297D4
	ldrb	r0, [r1, #1]
	cmp	r0, #32
	beq _US_080297D4
	cmp	r0, #33
	bne _US_080297DE
_US_080297D4:
	movs	r1, #0
	movs	r0, #8
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
	b _US_080297F8
_US_080297DE:
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r3, #140
	lsls	r3, r3, #1
	adds	r1, r6, r3
	strb	r0, [r1, #0]
	strh	r2, [r4, #0]
_US_080297F0:
	movs	r0, #4
	strb	r0, [r6, #13]
	mov	r4, sl
	strb	r4, [r6, #14]
_US_080297F8:
	movs	r0, #155
	lsls	r0, r0, #1
	adds	r2, r6, r0
	ldrb	r1, [r2, #0]
	cmp	r1, #0
	beq _US_08029816
	movs	r0, #128
	ands	r0, r1
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #0
	beq _US_08029814
	movs	r0, #128
	eors	r0, r1
_US_08029814:
	strb	r0, [r2, #0]
_US_08029816:
	ldr	r1, _US_08029900
	ldrb	r0, [r6, #13]
	lsls	r0, r0, #2
	adds	r0, r0, r1
	ldr	r1, [r0, #0]
	adds	r0, r6, #0
	bl _call_via_r1
	ldr	r1, _US_08029904
	adds	r0, r6, r1
	ldrb	r1, [r0, #0]
	adds	r4, r0, #0
	cmp	r1, #0
	beq _US_08029884
	ldr	r2, [sp, #12]
	ldr	r0, [r2, #96]
	ldr	r1, [r6, #88]
	cmp	r0, r1
	bcs _US_08029872
	ldr	r0, [r6, #84]
	bl GetGroundMetatileAttr
	movs	r1, #128
	lsls	r1, r1, #8
	ands	r1, r0
	cmp	r1, #0
	beq _US_0802986E
	ldr	r0, [r6, #84]
	ldr	r1, [r6, #88]
	bl GetGroundMetatileAttr
	movs	r7, #15
	adds	r1, r7, #0
	ands	r1, r0
	cmp	r1, #0
	beq _US_0802986E
	ldr	r0, [r6, #84]
	ldr	r1, [r6, #88]
	bl GetGroundMetatileAttr
	adds	r1, r7, #0
	ands	r1, r0
	cmp	r1, #14
	bls _US_08029872
_US_0802986E:
	movs	r0, #0
	strb	r0, [r4, #0]
_US_08029872:
	ldr	r3, [sp, #12]
	ldr	r0, [r3, #96]
	ldr	r1, _US_08029908
	adds	r0, r0, r1
	ldr	r1, [r6, #88]
	cmp	r0, r1
	bls _US_08029884
	movs	r0, #0
	strb	r0, [r4, #0]
_US_08029884:
	ldrb	r0, [r6, #13]
	cmp	r0, #7
	beq _US_08029892
	ldr	r2, _US_0802990C
	adds	r1, r6, r2
	movs	r0, #0
	strb	r0, [r1, #0]
_US_08029892:
	ldrb	r0, [r6, #13]
	cmp	r0, #4
	beq _US_080298BA
	ldr	r3, [sp, #8]
	ldr	r0, [r3, #0]
	movs	r1, #128
	lsls	r1, r1, #2
	ands	r0, r1
	cmp	r0, #0
	bne _US_080298B2
	adds	r0, r6, #0
	adds	r0, #164
	movs	r4, #0
	ldrsh	r0, [r0, r4]
	cmp	r0, #0
	bne _US_080298BA
_US_080298B2:
	movs	r1, #0
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
_US_080298BA:
	ldr	r1, _US_08029910
	ldrb	r0, [r6, #13]
	lsls	r0, r0, #2
	adds	r0, r0, r1
	ldr	r1, [r0, #0]
	adds	r0, r6, #0
	bl _call_via_r1
	movs	r0, #151
	lsls	r0, r0, #1
	adds	r1, r6, r0
	movs	r0, #255
	strb	r0, [r1, #0]
	movs	r3, #0
	movs	r1, #146
	lsls	r1, r1, #1
	adds	r2, r6, r1
	ldrb	r1, [r2, #0]
	movs	r0, #4
	ands	r0, r1
	adds	r7, r2, #0
	ldr	r4, _US_08029914
	adds	r2, r6, r4
	cmp	r0, #0
	beq _US_08029936
	ldrb	r0, [r6, #13]
	ldr	r1, [sp, #16]
	ldrb	r1, [r1, #0]
	cmp	r0, r1
	beq _US_08029918
	ldrb	r0, [r2, #0]
	cmp	r0, #0
	bne _US_0802992C
	b _US_08029930
	movs	r0, r0
	.align 2, 0
_US_08029900: .4byte sHandlePlayerInputs
_US_08029904: .4byte 0x00000113
_US_08029908: .4byte 0xFFFFE000
_US_0802990C: .4byte 0x00000143
_US_08029910: .4byte sZeroUpdates
_US_08029914: .4byte 0x00000125
_US_08029918:
	cmp	r0, #0
	bne _US_08029936
	ldrb	r0, [r6, #14]
	ldr	r4, [sp, #20]
	ldrb	r4, [r4, #0]
	cmp	r0, r4
	beq _US_08029936
	ldrb	r0, [r2, #0]
	cmp	r0, #0
	beq _US_08029930
_US_0802992C:
	movs	r3, #1
	b _US_08029936
_US_08029930:
	adds	r0, r6, #0
	adds	r0, #236
	strb	r3, [r0, #0]
_US_08029936:
	ldrb	r1, [r7, #0]
	movs	r0, #2
	negs	r0, r0
	ands	r0, r1
	movs	r1, #3
_US_08029940:
	negs	r1, r1
	ands	r0, r1
	subs	r1, #2
	ands	r0, r1
	subs	r1, #4
	ands	r0, r1
	strb	r0, [r7, #0]
	movs	r0, #0
	strb	r0, [r2, #0]
	lsls	r2, r3, #6
	ldrb	r1, [r7, #0]
	subs	r0, #65
	ands	r0, r1
	orrs	r0, r2
	strb	r0, [r7, #0]
	movs	r0, #147
	lsls	r0, r0, #1
	adds	r1, r6, r0
	movs	r0, #255
	strb	r0, [r1, #0]
	ldr	r2, _US_080299F8
	adds	r1, r6, r2
	movs	r0, #1
	negs	r0, r0
	strb	r0, [r1, #0]
	ldr	r3, _US_080299FC
	adds	r1, r6, r3
	ldrb	r0, [r1, #0]
	cmp	r0, #0
	beq _US_08029980
	subs	r0, #1
	strb	r0, [r1, #0]
_US_08029980:
	mov	r4, r8
	ldrb	r0, [r4, #0]
	ldr	r1, _US_08029A00
	adds	r5, r6, r1
	cmp	r0, #1
	bne _US_080299B0
	ldrh	r1, [r5, #0]
	movs	r0, #128
	lsls	r0, r0, #8
	ands	r0, r1
	cmp	r0, #0
	bne _US_080299B0
	ldr	r2, [sp, #12]
	ldrb	r0, [r2, #17]
	cmp	r0, #3
	beq _US_080299A4
	cmp	r0, #7
	bne _US_080299B0
_US_080299A4:
	ldr	r3, [sp, #28]
	ldrb	r0, [r3, #0]
	cmp	r0, #3
	bne _US_080299B0
	mov	r4, r8
	strb	r0, [r4, #0]
_US_080299B0:
	ldrb	r0, [r6, #13]
	cmp	r0, #3
	bhi _US_08029A0C
	ldr	r0, _US_08029A04
	ldrb	r1, [r6, #13]
	lsls	r1, r1, #2
	adds	r1, r1, r0
	ldr	r1, [r1, #0]
	adds	r0, r6, #0
	bl _call_via_r1
	ldr	r0, _US_08029A08
	adds	r1, r6, r0
	ldrb	r0, [r1, #0]
	cmp	r0, #0
	beq _US_08029A14
	subs	r0, #1
	strb	r0, [r1, #0]
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #0
	bne _US_08029A14
	strb	r0, [r1, #0]
	ldr	r2, [sp, #12]
	ldrb	r1, [r2, #0]
	adds	r0, r6, #0
	movs	r2, #0
	bl CreateSateliteElf
	ldr	r3, [sp, #12]
	ldrb	r1, [r3, #1]
	adds	r0, r6, #0
	movs	r2, #1
	bl CreateSateliteElf
	b _US_08029A14
	.align 2, 0
_US_080299F8: .4byte 0x00000127
_US_080299FC: .4byte 0x0000013B
_US_08029A00: .4byte 0x00000216
_US_08029A04: .4byte sZeroAttacks
_US_08029A08: .4byte 0x00000232
_US_08029A0C:
	adds	r1, r6, #0
	adds	r1, #236
	movs	r0, #0
	strb	r0, [r1, #0]
_US_08029A14:
	ldrb	r1, [r7, #0]
	movs	r0, #17
	negs	r0, r0
	ands	r0, r1
	movs	r1, #33
	negs	r1, r1
	ands	r0, r1
	strb	r0, [r7, #0]
	ldr	r4, [sp, #28]
	ldrb	r0, [r4, #0]
	mov	r1, r8
	ldrb	r1, [r1, #0]
	cmp	r0, r1
	beq _US_08029A7A
	adds	r0, r6, #0
	adds	r0, #116
	mov	r3, r8
	ldrb	r2, [r3, #0]
	lsls	r1, r2, #1
	adds	r1, r1, r2
	lsls	r1, r1, #3
	ldr	r2, _US_08029A64
	adds	r1, r1, r2
	bl SetDDP
	mov	r4, r8
	ldrb	r0, [r4, #0]
	cmp	r0, #3
	bne _US_08029A68
	adds	r0, r6, #0
	bl GetZeroColor
	adds	r1, r0, #0
	lsls	r1, r1, #24
	lsrs	r1, r1, #24
	adds	r0, r6, #0
	bl LoadShadowDashPalette
	b _US_08029A7A
	movs	r0, r0
	.align 2, 0
_US_08029A64: .4byte gZeroCollisions
_US_08029A68:
	adds	r0, r6, #0
	bl GetZeroColor
	adds	r1, r0, #0
	lsls	r1, r1, #24
	lsrs	r1, r1, #24
	adds	r0, r6, #0
	bl LoadZeroPalette
_US_08029A7A:
	ldrb	r1, [r6, #13]
	subs	r0, r1, #5
	lsls	r0, r0, #24
	lsrs	r0, r0, #24
	cmp	r0, #1
	bls _US_08029ACA
	cmp	r1, #10
	beq _US_08029ACA
	mov	r0, r8
	ldrb	r1, [r0, #0]
	lsls	r1, r1, #3
	ldr	r0, _US_08029B08
	adds	r1, r1, r0
	adds	r0, r6, #0
	movs	r2, #1
	bl PushoutByBorder
	lsls	r0, r0, #24
	cmp	r0, #0
	beq _US_08029ACA
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r2, #140
	lsls	r2, r2, #1
	adds	r1, r6, r2
	movs	r2, #0
	strb	r0, [r1, #0]
	adds	r0, r6, #0
	adds	r0, #164
	movs	r1, #0
	strh	r2, [r0, #0]
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
	ldr	r3, [sp, #0]
	ldr	r4, [sp, #4]
	str	r3, [r6, #84]
	str	r4, [r6, #88]
_US_08029ACA:
	ldr	r4, _US_08029B0C
	adds	r0, r6, r4
	ldrb	r0, [r0, #0]
	cmp	r0, #0
	bne _US_08029B24
	ldr	r1, _US_08029B08
	mov	r2, r8
	ldrb	r0, [r2, #0]
	lsls	r0, r0, #3
	adds	r4, r0, r1
	ldrh	r0, [r4, #6]
	lsls	r0, r0, #16
	asrs	r0, r0, #17
	ldr	r3, [r6, #88]
	subs	r2, r3, r0
	ldr	r0, _US_08029B10
	ldr	r1, _US_08029B14
	adds	r0, r0, r1
	ldr	r1, [r0, #0]
	cmp	r2, r1
	ble _US_08029B18
	movs	r2, #6
	ldrsh	r0, [r4, r2]
	subs	r2, r3, r0
	cmp	r2, r1
	bge _US_08029B24
	adds	r0, r6, #0
	movs	r1, #1
	bl CreateRipple
	b _US_08029B24
	.align 2, 0
_US_08029B08: .4byte gZeroRanges
_US_08029B0C: .4byte 0x0000011B
_US_08029B10: .4byte gOverworld
_US_08029B14: .4byte 0x0002C00C
_US_08029B18:
	cmp	r3, r1
	ble _US_08029B24
	adds	r0, r6, #0
	movs	r1, #0
	bl CreateRipple
_US_08029B24:
	movs	r3, #142
	lsls	r3, r3, #1
	adds	r1, r6, r3
	movs	r0, #0
	strb	r0, [r1, #0]
	ldrh	r1, [r5, #0]
	movs	r0, #128
	lsls	r0, r0, #8
	ands	r0, r1
	cmp	r0, #0
	bne _US_08029B9A
	ldr	r4, [sp, #8]
	ldr	r0, [r4, #0]
	movs	r1, #128
	lsls	r1, r1, #2
	ands	r0, r1
	cmp	r0, #0
	bne _US_08029B9A
	adds	r0, r6, #0
	adds	r0, #164
	movs	r2, #0
	ldrsh	r1, [r0, r2]
	adds	r5, r0, #0
	cmp	r1, #0
	beq _US_08029B9A
	ldr	r1, [r6, #84]
	ldr	r3, [sp, #0]
	subs	r2, r3, r1
	cmp	r2, #0
	blt _US_08029B6A
	movs	r0, #128
	lsls	r0, r0, #5
	cmp	r2, r0
	bgt _US_08029B76
	b _US_08029B9A
_US_08029B6A:
	ldr	r4, [sp, #0]
	subs	r1, r1, r4
	movs	r0, #128
	lsls	r0, r0, #5
	cmp	r1, r0
	ble _US_08029B9A
_US_08029B76:
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r2, #140
	lsls	r2, r2, #1
	adds	r1, r6, r2
	movs	r2, #0
	strb	r0, [r1, #0]
	movs	r1, #0
	strh	r2, [r5, #0]
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
	ldr	r3, [sp, #0]
	ldr	r4, [sp, #4]
	str	r3, [r6, #84]
	str	r4, [r6, #88]
_US_08029B9A:
	ldr	r4, _US_08029BD4
	adds	r0, r6, r4
	ldrb	r0, [r0, #0]
	cmp	r0, #0
	beq _US_08029C08
	ldr	r1, [sp, #8]
	ldr	r0, [r1, #0]
	movs	r1, #128
	lsls	r1, r1, #2
	ands	r0, r1
	cmp	r0, #0
	bne _US_08029C08
	adds	r0, r6, #0
	adds	r0, #164
	movs	r2, #0
	ldrsh	r1, [r0, r2]
	adds	r5, r0, #0
_US_08029BBC:
	cmp	r1, #0
	beq _US_08029C08
	ldr	r1, [r6, #88]
	ldr	r3, [sp, #4]
	subs	r2, r3, r1
	cmp	r2, #0
	blt _US_08029BD8
	movs	r0, #128
	lsls	r0, r0, #5
	cmp	r2, r0
	bgt _US_08029BE4
	b _US_08029C08
	.align 2, 0
_US_08029BD4: .4byte 0x0000018F
_US_08029BD8:
	ldr	r4, [sp, #4]
	subs	r1, r1, r4
	movs	r0, #128
	lsls	r0, r0, #5
	cmp	r1, r0
	ble _US_08029C08
_US_08029BE4:
	ldrb	r0, [r6, #10]
	lsrs	r0, r0, #4
	movs	r1, #1
	ands	r0, r1
	movs	r2, #140
	lsls	r2, r2, #1
	adds	r1, r6, r2
	movs	r2, #0
	strb	r0, [r1, #0]
	movs	r1, #0
	strh	r2, [r5, #0]
	movs	r0, #4
	strb	r0, [r6, #13]
	strb	r1, [r6, #14]
	ldr	r3, [sp, #0]
	ldr	r4, [sp, #4]
	str	r3, [r6, #84]
	str	r4, [r6, #88]
_US_08029C08:
	ldr	r4, [sp, #24]
	ldrb	r0, [r4, #0]
	cmp	r0, #0
	bne _US_08029C16
	adds	r0, r6, #0
	bl UpdateEntityAnim
_US_08029C16:
	adds	r0, r6, #0
	bl setStageElfFlags
	ldr	r0, _US_08029C40
	adds	r1, r6, r0
	movs	r0, #0
	strb	r0, [r1, #0]
	ldr	r0, [r6, #84]
	ldr	r1, [sp, #0]
	subs	r0, r0, r1
	ldr	r2, [sp, #12]
	str	r0, [r2, #88]
_US_08029C2E:
	add	sp, #32
	pop	{r3, r4, r5}
	mov	r8, r3
	mov	r9, r4
	mov	sl, r5
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
	movs	r0, r0
	.align 2, 0
_US_08029C40: .4byte 0x00000149
.else
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x18
	adds r6, r0, #0
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [sp]
	str r1, [sp, #4]
	ldrb r1, [r6, #0xa]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080292E6
	adds r0, r6, #0
	bl resetSateliteElfPosition
_080292E6:
	ldr r2, _08029304 @ =0x00000233
	adds r1, r6, r2
	ldrb r0, [r1]
	cmp r0, #0
	beq _08029308
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080292FC
	b _080299C8
_080292FC:
	movs r0, #0x21
	bl PlaySound
	b _080299C8
	.align 2, 0
_08029304: .4byte 0x00000233
_08029308:
	adds r4, r6, #0
	adds r4, #0xfa
	movs r3, #0
	ldrsh r1, [r4, r3]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	bne _08029344
	ldrb r0, [r6, #0xd]
	cmp r0, #0xb
	beq _0802935E
	ldr r0, _08029338 @ =gOverworld
	ldr r7, _0802933C @ =0x0002C00C
	adds r0, r0, r7
	ldr r1, [r6, #0x58]
	ldr r2, _08029340 @ =0xFFFFE200
	adds r1, r1, r2
	ldr r0, [r0]
	cmp r0, r1
	bge _0802935E
	movs r0, #0x32
	bl PlaySound
	b _0802935C
	.align 2, 0
_08029338: .4byte gOverworld
_0802933C: .4byte 0x0002C00C
_08029340: .4byte 0xFFFFE200
_08029344:
	ldr r0, _080293A8 @ =gOverworld
	ldr r3, _080293AC @ =0x0002C00C
	adds r0, r0, r3
	ldr r1, [r0]
	ldr r0, [r6, #0x58]
	cmp r1, r0
	ble _0802935E
	movs r7, #0
	ldrsh r0, [r4, r7]
	bl StopSound
	ldr r0, _080293B0 @ =0x0000FFFF
_0802935C:
	strh r0, [r4]
_0802935E:
	ldrb r0, [r6, #0xd]
	adds r5, r6, #0
	adds r5, #0xe8
	strb r0, [r5]
	ldrb r0, [r6, #0xe]
	adds r4, r6, #0
	adds r4, #0xe9
	strb r0, [r4]
	adds r0, r6, #0
	bl HandlePlayerInput
	adds r0, r6, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r1, [r0, r2]
	str r5, [sp, #8]
	str r4, [sp, #0xc]
	mov r8, r0
	ldr r3, _080293B4 @ =0x00000147
	adds r5, r6, r3
	cmp r1, #0
	beq _08029434
	ldrb r1, [r5]
	lsls r1, r1, #3
	ldr r0, _080293B8 @ =gZeroRanges
	adds r1, r1, r0
	adds r0, r6, #0
	bl RecoilFromFloor
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _080293BC
	adds r0, r6, #0
	bl InstantlyKilling
	b _080293DE
	.align 2, 0
_080293A8: .4byte gOverworld
_080293AC: .4byte 0x0002C00C
_080293B0: .4byte 0x0000FFFF
_080293B4: .4byte 0x00000147
_080293B8: .4byte gZeroRanges
_080293BC:
	cmp r0, #2
	bne _080293DE
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r7, #0x8c
	lsls r7, r7, #1
	adds r1, r6, r7
	strb r0, [r1]
	movs r1, #0
	movs r0, #0
	mov r2, r8
	strh r0, [r2]
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_080293DE:
	mov r3, r8
	movs r7, #0
	ldrsh r0, [r3, r7]
	cmp r0, #0
	beq _08029434
	ldrb r1, [r5]
	lsls r1, r1, #3
	ldr r0, _08029420 @ =gZeroRanges
	adds r1, r1, r0
	adds r0, r6, #0
	bl RecoilFromHazards
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _08029424
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r2, #0x8c
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r2, #0
	strb r0, [r1]
	movs r1, #0
	mov r3, r8
	strh r2, [r3]
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	b _0802942E
	.align 2, 0
_08029420: .4byte gZeroRanges
_08029424:
	cmp r0, #2
	bne _0802942E
	adds r0, r6, #0
	bl InstantlyKilling
_0802942E:
	adds r0, r6, #0
	bl CheckZeroHazard
_08029434:
	ldrb r0, [r6, #0xd]
	movs r7, #0xb4
	adds r7, r7, r6
	mov sl, r7
	cmp r0, #1
	beq _08029448
	cmp r0, #4
	beq _08029448
	movs r0, #0
	str r0, [r7, #0x54]
_08029448:
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r4, r6, r0
	ldrb r0, [r4]
	cmp r0, #0
	beq _08029458
	subs r0, #1
	b _08029476
_08029458:
	ldr r0, _0802957C @ =gOverworld
	movs r1, #0xe8
	lsls r1, r1, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	movs r0, #0x7f
	ands r0, r1
	cmp r0, #7
	bne _08029478
	bl FUN_080101a8
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08029478
	movs r0, #0x10
_08029476:
	strb r0, [r4]
_08029478:
	movs r3, #0x80
	lsls r3, r3, #1
	adds r2, r6, r3
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [r2]
	str r1, [r2, #4]
	ldrb r0, [r6, #0x1e]
	lsls r0, r0, #8
	adds r1, r6, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r1, r0
	movs r7, #0x9f
	lsls r7, r7, #1
	adds r0, r6, r7
	movs r2, #0
	mov sb, r2
	strh r1, [r0]
	adds r0, r6, #0
	adds r0, #0x71
	ldrb r1, [r0]
	adds r3, #0x40
	adds r0, r6, r3
	strb r1, [r0]
	adds r0, r6, #0
	adds r0, #0x72
	ldrb r0, [r0]
	adds r7, #3
	adds r1, r6, r7
	strb r0, [r1]
	ldrb r0, [r5]
	movs r1, #0xa4
	lsls r1, r1, #1
	adds r2, r6, r1
	strb r0, [r2]
	mov r3, sb
	strb r3, [r5]
	ldr r1, [r6, #0xc]
	ldr r0, _08029580 @ =0x00FFFF00
	ands r1, r0
	str r2, [sp, #0x14]
	movs r7, #0x80
	lsls r7, r7, #3
	cmp r1, r7
	beq _080294DA
	ldr r1, _08029584 @ =0x0000018D
	adds r0, r6, r1
	strb r3, [r0]
_080294DA:
	movs r2, #0xa1
	lsls r2, r2, #1
	adds r0, r6, r2
	mov r3, sb
	strb r3, [r0]
	mov r7, r8
	movs r2, #0
	ldrsh r1, [r7, r2]
	str r0, [sp, #0x10]
	cmp r1, #0
	beq _080295D2
	ldrb r1, [r6, #0xd]
	subs r0, r1, #5
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _080295D2
	cmp r1, #0xa
	beq _080295D2
	ldr r7, _08029588 @ =gZeroRanges
	ldrb r0, [r5]
	lsls r0, r0, #3
	adds r0, r0, r7
	movs r3, #6
	ldrsh r1, [r0, r3]
	ldr r2, [r6, #0x58]
	subs r1, r2, r1
	ldr r4, _0802958C @ =0xFFFFF800
	adds r1, r1, r4
	movs r3, #0xac
	lsls r3, r3, #1
	adds r0, r6, r3
	ldr r0, [r0]
	cmp r1, r0
	bgt _0802954A
	ldr r0, [r6, #0x54]
	adds r1, r2, #0
	bl IsVoidSpace
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080295D2
	ldr r0, [r6, #0x54]
	ldrb r1, [r5]
	lsls r1, r1, #3
	adds r1, r1, r7
	movs r7, #6
	ldrsh r2, [r1, r7]
	ldr r1, [r6, #0x58]
	subs r1, r1, r2
	adds r1, r1, r4
	bl IsVoidSpace
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080295D2
_0802954A:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	ldr r2, _08029590 @ =0xFFFFE200
	adds r1, r1, r2
	bl GetGroundMetatileAttr
	movs r1, #0x80
	lsls r1, r1, #3
	ands r1, r0
	lsls r1, r1, #0x10
	lsrs r2, r1, #0x10
	cmp r2, #0
	beq _08029594
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r3, #0x8c
	lsls r3, r3, #1
	adds r1, r6, r3
	strb r0, [r1]
	movs r0, #0
	mov r7, r8
	strh r0, [r7]
	b _080295CA
	.align 2, 0
_0802957C: .4byte gOverworld
_08029580: .4byte 0x00FFFF00
_08029584: .4byte 0x0000018D
_08029588: .4byte gZeroRanges
_0802958C: .4byte 0xFFFFF800
_08029590: .4byte 0xFFFFE200
_08029594:
	mov r1, sl
	ldrb r0, [r1]
	subs r0, #0x20
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _080295AC
	ldrb r0, [r1, #1]
	cmp r0, #0x20
	beq _080295AC
	cmp r0, #0x21
	bne _080295B6
_080295AC:
	movs r1, #0
	movs r0, #8
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	b _080295D2
_080295B6:
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r3, #0x8c
	lsls r3, r3, #1
	adds r1, r6, r3
	strb r0, [r1]
	mov r7, r8
	strh r2, [r7]
_080295CA:
	movs r0, #4
	strb r0, [r6, #0xd]
	mov r0, sb
	strb r0, [r6, #0xe]
_080295D2:
	movs r1, #0x9b
	lsls r1, r1, #1
	adds r2, r6, r1
	ldrb r1, [r2]
	cmp r1, #0
	beq _080295F0
	movs r0, #0x80
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	beq _080295EE
	movs r0, #0x80
	eors r0, r1
_080295EE:
	strb r0, [r2]
_080295F0:
	ldr r1, _080296C8 @ =sHandlePlayerInputs
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	ldr r2, _080296CC @ =0x00000113
	adds r0, r6, r2
	ldrb r1, [r0]
	adds r7, r0, #0
	cmp r1, #0
	beq _0802965E
	mov r3, sl
	ldr r0, [r3, #0x60]
	ldr r1, [r6, #0x58]
	cmp r0, r1
	bhs _0802964C
	ldr r0, [r6, #0x54]
	bl GetGroundMetatileAttr
	movs r1, #0x80
	lsls r1, r1, #8
	ands r1, r0
	cmp r1, #0
	beq _08029648
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl GetGroundMetatileAttr
	movs r4, #0xf
	adds r1, r4, #0
	ands r1, r0
	cmp r1, #0
	beq _08029648
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl GetGroundMetatileAttr
	adds r1, r4, #0
	ands r1, r0
	cmp r1, #0xe
	bls _0802964C
_08029648:
	movs r0, #0
	strb r0, [r7]
_0802964C:
	mov r1, sl
	ldr r0, [r1, #0x60]
	ldr r2, _080296D0 @ =0xFFFFE000
	adds r0, r0, r2
	ldr r1, [r6, #0x58]
	cmp r0, r1
	bls _0802965E
	movs r0, #0
	strb r0, [r7]
_0802965E:
	ldrb r0, [r6, #0xd]
	cmp r0, #7
	beq _0802966C
	ldr r3, _080296D4 @ =0x00000143
	adds r1, r6, r3
	movs r0, #0
	strb r0, [r1]
_0802966C:
	ldrb r0, [r6, #0xd]
	cmp r0, #4
	beq _08029682
	mov r7, r8
	movs r0, #0
	ldrsh r1, [r7, r0]
	cmp r1, #0
	bne _08029682
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_08029682:
	ldr r1, _080296D8 @ =sZeroUpdates
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	movs r2, #0x97
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r0, #0xff
	strb r0, [r1]
	movs r3, #0
	movs r7, #0x92
	lsls r7, r7, #1
	adds r2, r6, r7
	ldrb r1, [r2]
	movs r0, #4
	ands r0, r1
	adds r4, r2, #0
	ldr r1, _080296DC @ =0x00000125
	adds r2, r6, r1
	cmp r0, #0
	beq _080296FE
	ldrb r0, [r6, #0xd]
	ldr r7, [sp, #8]
	ldrb r7, [r7]
	cmp r0, r7
	beq _080296E0
	ldrb r0, [r2]
	cmp r0, #0
	bne _080296F4
	b _080296F8
	.align 2, 0
_080296C8: .4byte sHandlePlayerInputs
_080296CC: .4byte 0x00000113
_080296D0: .4byte 0xFFFFE000
_080296D4: .4byte 0x00000143
_080296D8: .4byte sZeroUpdates
_080296DC: .4byte 0x00000125
_080296E0:
	cmp r0, #0
	bne _080296FE
	ldrb r0, [r6, #0xe]
	ldr r1, [sp, #0xc]
	ldrb r1, [r1]
	cmp r0, r1
	beq _080296FE
	ldrb r0, [r2]
	cmp r0, #0
	beq _080296F8
_080296F4:
	movs r3, #1
	b _080296FE
_080296F8:
	adds r0, r6, #0
	adds r0, #0xec
	strb r3, [r0]
_080296FE:
	ldrb r1, [r4]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
	subs r1, #2
	ands r0, r1
	subs r1, #4
	ands r0, r1
	strb r0, [r4]
	movs r0, #0
	strb r0, [r2]
	lsls r2, r3, #6
	ldrb r1, [r4]
	subs r0, #0x41
	ands r0, r1
	orrs r0, r2
	strb r0, [r4]
	movs r2, #0x93
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r0, #0xff
	strb r0, [r1]
	ldr r3, _080297BC @ =0x00000127
	adds r1, r6, r3
	movs r0, #1
	rsbs r0, r0, #0
	strb r0, [r1]
	ldr r7, _080297C0 @ =0x0000013B
	adds r1, r6, r7
	ldrb r0, [r1]
	cmp r0, #0
	beq _08029748
	subs r0, #1
	strb r0, [r1]
_08029748:
	ldrb r0, [r5]
	ldr r1, _080297C4 @ =0x00000216
	adds r7, r6, r1
	cmp r0, #1
	bne _08029774
	ldrh r1, [r7]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08029774
	mov r2, sl
	ldrb r0, [r2, #0x11]
	cmp r0, #3
	beq _0802976A
	cmp r0, #7
	bne _08029774
_0802976A:
	ldr r3, [sp, #0x14]
	ldrb r0, [r3]
	cmp r0, #3
	bne _08029774
	strb r0, [r5]
_08029774:
	ldrb r0, [r6, #0xd]
	cmp r0, #3
	bhi _080297D0
	ldr r0, _080297C8 @ =sZeroAttacks
	ldrb r1, [r6, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r6, #0
	bl _call_via_r1
	ldr r0, _080297CC @ =0x00000232
	adds r1, r6, r0
	ldrb r0, [r1]
	cmp r0, #0
	beq _080297D8
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _080297D8
	strb r0, [r1]
	mov r2, sl
	ldrb r1, [r2]
	adds r0, r6, #0
	movs r2, #0
	bl CreateSateliteElf
	mov r3, sl
	ldrb r1, [r3, #1]
	adds r0, r6, #0
	movs r2, #1
	bl CreateSateliteElf
	b _080297D8
	.align 2, 0
_080297BC: .4byte 0x00000127
_080297C0: .4byte 0x0000013B
_080297C4: .4byte 0x00000216
_080297C8: .4byte sZeroAttacks
_080297CC: .4byte 0x00000232
_080297D0:
	adds r1, r6, #0
	adds r1, #0xec
	movs r0, #0
	strb r0, [r1]
_080297D8:
	ldrb r1, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #0x21
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r4]
	ldr r1, [sp, #0x14]
	ldrb r0, [r1]
	ldrb r2, [r5]
	cmp r0, r2
	beq _08029836
	adds r0, r6, #0
	adds r0, #0x74
	ldrb r2, [r5]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08029820 @ =gZeroCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r5]
	cmp r0, #3
	bne _08029824
	adds r0, r6, #0
	bl GetZeroColor
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r6, #0
	bl LoadShadowDashPalette
	b _08029836
	.align 2, 0
_08029820: .4byte gZeroCollisions
_08029824:
	adds r0, r6, #0
	bl GetZeroColor
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r6, #0
	bl LoadZeroPalette
_08029836:
	ldrb r1, [r6, #0xd]
	subs r0, r1, #5
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _08029882
	cmp r1, #0xa
	beq _08029882
	ldrb r1, [r5]
	lsls r1, r1, #3
	ldr r0, _080298C0 @ =gZeroRanges
	adds r1, r1, r0
	adds r0, r6, #0
	movs r2, #1
	bl PushoutByBorder
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08029882
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r3, #0x8c
	lsls r3, r3, #1
	adds r1, r6, r3
	movs r2, #0
	strb r0, [r1]
	movs r1, #0
	mov r0, r8
	strh r2, [r0]
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	ldr r1, [sp]
	ldr r2, [sp, #4]
	str r1, [r6, #0x54]
	str r2, [r6, #0x58]
_08029882:
	ldr r2, _080298C4 @ =0x0000011B
	adds r0, r6, r2
	ldrb r0, [r0]
	cmp r0, #0
	bne _080298DC
	ldr r1, _080298C0 @ =gZeroRanges
	ldrb r0, [r5]
	lsls r0, r0, #3
	adds r4, r0, r1
	ldrh r0, [r4, #6]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x11
	ldr r3, [r6, #0x58]
	subs r2, r3, r0
	ldr r0, _080298C8 @ =gOverworld
	ldr r1, _080298CC @ =0x0002C00C
	adds r0, r0, r1
	ldr r1, [r0]
	cmp r2, r1
	ble _080298D0
	movs r2, #6
	ldrsh r0, [r4, r2]
	subs r2, r3, r0
	cmp r2, r1
	bge _080298DC
	adds r0, r6, #0
	movs r1, #1
	bl CreateRipple
	b _080298DC
	.align 2, 0
_080298C0: .4byte gZeroRanges
_080298C4: .4byte 0x0000011B
_080298C8: .4byte gOverworld
_080298CC: .4byte 0x0002C00C
_080298D0:
	cmp r3, r1
	ble _080298DC
	adds r0, r6, #0
	movs r1, #0
	bl CreateRipple
_080298DC:
	movs r3, #0x8e
	lsls r3, r3, #1
	adds r1, r6, r3
	movs r0, #0
	strb r0, [r1]
	ldrh r1, [r7]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08029942
	mov r7, r8
	movs r1, #0
	ldrsh r0, [r7, r1]
	cmp r0, #0
	beq _08029942
	ldr r1, [r6, #0x54]
	ldr r3, [sp]
	subs r2, r3, r1
	cmp r2, #0
	blt _08029910
	movs r0, #0x80
	lsls r0, r0, #5
	cmp r2, r0
	bgt _0802991C
	b _08029942
_08029910:
	ldr r7, [sp]
	subs r1, r1, r7
	movs r0, #0x80
	lsls r0, r0, #5
	cmp r1, r0
	ble _08029942
_0802991C:
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r2, #0x8c
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r2, #0
	strb r0, [r1]
	movs r1, #0
	mov r3, r8
	strh r2, [r3]
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
_08029942:
	ldr r1, _0802996C @ =0x0000018F
	adds r0, r6, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _080299A2
	mov r2, r8
	movs r3, #0
	ldrsh r0, [r2, r3]
	cmp r0, #0
	beq _080299A2
	ldr r1, [r6, #0x58]
	ldr r7, [sp, #4]
	subs r2, r7, r1
	cmp r2, #0
	blt _08029970
	movs r0, #0x80
	lsls r0, r0, #5
	cmp r2, r0
	bgt _0802997C
	b _080299A2
	.align 2, 0
_0802996C: .4byte 0x0000018F
_08029970:
	ldr r0, [sp, #4]
	subs r1, r1, r0
	movs r0, #0x80
	lsls r0, r0, #5
	cmp r1, r0
	ble _080299A2
_0802997C:
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	movs r2, #0x8c
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r2, #0
	strb r0, [r1]
	movs r1, #0
	mov r3, r8
	strh r2, [r3]
	movs r0, #4
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
_080299A2:
	ldr r1, [sp, #0x10]
	ldrb r0, [r1]
	cmp r0, #0
	bne _080299B0
	adds r0, r6, #0
	bl UpdateEntityAnim
_080299B0:
	adds r0, r6, #0
	bl setStageElfFlags
	ldr r2, _080299D8 @ =0x00000149
	adds r1, r6, r2
	movs r0, #0
	strb r0, [r1]
	ldr r0, [r6, #0x54]
	ldr r3, [sp]
	subs r0, r0, r3
	mov r7, sl
	str r0, [r7, #0x58]
_080299C8:
	add sp, #0x18
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080299D8: .4byte 0x00000149
.endif
