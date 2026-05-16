	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #0xc
	adds r5, r0, #0
	mov r8, r1
	mov sb, r2
	lsls r3, r3, #0x18
	lsrs r6, r3, #0x18
	adds r0, #0xb4
	ldrb r0, [r0, #0xc]
	cmp r0, #0
	bne _0803415E
	adds r0, r5, #0
	movs r1, #0
	b _08034162
_0803415E:
	adds r0, r5, #0
	movs r1, #1
_08034162:
	bl GetWeaponCharge
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #2
	beq _080341D8
	ldr r1, _080341C0 @ =0x00000225
	adds r0, r5, r1
	ldrb r1, [r0]
	adds r7, r0, #0
	cmp r1, #3
	bne _080341D8
	ldrb r0, [r5, #0xd]
	cmp r0, #3
	bne _080341D2
	ldr r0, _080341C4 @ =0x00000226
	adds r4, r5, r0
	ldrb r1, [r4]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r0, [r4]
	movs r1, #0x4a
	adds r1, r1, r5
	mov ip, r1
	adds r1, r2, #0
	ands r1, r0
	lsls r1, r1, #4
	mov r0, ip
	ldrb r3, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldrb r0, [r4]
	ands r2, r0
	cmp r2, #0
	beq _080341C8
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080341CE
	.align 2, 0
_080341C0: .4byte 0x00000225
_080341C4: .4byte 0x00000226
_080341C8:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080341CE:
	strb r0, [r5, #0xa]
	ldrb r6, [r4]
_080341D2:
	movs r4, #1
	movs r0, #0
	strb r0, [r7]
_080341D8:
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r1, [r0]
	adds r7, r0, #0
	cmp r1, #6
	bne _08034240
	ldrb r0, [r5, #0xd]
	cmp r0, #3
	bne _0803423A
	ldr r0, _0803422C @ =0x00000229
	adds r4, r5, r0
	ldrb r1, [r4]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r0, [r4]
	movs r1, #0x4a
	adds r1, r1, r5
	mov ip, r1
	adds r1, r2, #0
	ands r1, r0
	lsls r1, r1, #4
	mov r0, ip
	ldrb r3, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldrb r0, [r4]
	ands r2, r0
	cmp r2, #0
	beq _08034230
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08034236
	.align 2, 0
_0803422C: .4byte 0x00000229
_08034230:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08034236:
	strb r0, [r5, #0xa]
	ldrb r6, [r4]
_0803423A:
	movs r4, #2
	movs r0, #0
	strb r0, [r7]
_08034240:
	lsls r0, r6, #0x18
	adds r3, r0, #0
	cmp r3, #0
	beq _0803424E
	mov r1, r8
	rsbs r0, r1, #0
	b _08034250
_0803424E:
	mov r0, r8
_08034250:
	str r0, [sp, #4]
	mov r1, sb
	str r1, [sp, #8]
	adds r6, r5, #0
	adds r6, #0xb4
	cmp r4, #2
	bne _080342A0
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _080342A0
	cmp r0, #1
	bgt _0803426E
	cmp r0, #0
	beq _08034278
	b _080342A0
_0803426E:
	cmp r0, #2
	beq _08034286
	cmp r0, #3
	beq _08034294
	b _080342A0
_08034278:
	ldrh r1, [r6, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080342A0
	movs r4, #3
	b _080342A0
_08034286:
	ldrh r1, [r6, #0x12]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080342A0
	movs r4, #4
	b _080342A0
_08034294:
	ldrh r1, [r6, #0x12]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080342A0
	movs r4, #5
_080342A0:
	lsrs r7, r3, #0x18
	movs r0, #0
	str r0, [sp]
	adds r0, r5, #0
	add r1, sp, #4
	adds r2, r4, #0
	adds r3, r7, #0
	bl CreateWeaponBuster
	mov r8, r0
	ldrb r2, [r6, #0xe]
	cmp r2, #1
	bne _080342D2
	ldrh r1, [r6, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080342D2
	str r2, [sp]
	adds r0, r5, #0
	add r1, sp, #4
	adds r2, r4, #0
	adds r3, r7, #0
	bl CreateWeaponBuster
_080342D2:
	mov r0, r8
	add sp, #0xc
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
