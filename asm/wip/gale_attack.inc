	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	adds r4, r6, #0
	adds r4, #0xee
	ldrb r0, [r4]
	cmp r0, #1
	beq _0802F188
	cmp r0, #1
	bgt _0802F15C
	cmp r0, #0
	beq _0802F170
	ldr r0, _0802F158 @ =0x00000129
	adds r0, r0, r6
	mov r8, r0
	b _0802F21A
	.align 2, 0
_0802F158: .4byte 0x00000129
_0802F15C:
	cmp r0, #2
	beq _0802F1BC
	cmp r0, #3
	beq _0802F1EC
	ldr r1, _0802F16C @ =0x00000129
	adds r1, r1, r6
	mov r8, r1
	b _0802F21A
	.align 2, 0
_0802F16C: .4byte 0x00000129
_0802F170:
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r6, #0
	bl SetMotion
	ldr r0, _0802F1B8 @ =0x00000129
	adds r1, r6, r0
	movs r0, #0x18
	strb r0, [r1]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
_0802F188:
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r6, #0
	bl KeepMotion
	adds r0, r6, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldr r1, _0802F1B8 @ =0x00000129
	adds r1, r1, r6
	mov r8, r1
	cmp r0, #1
	bgt _0802F21A
	adds r0, r6, #0
	movs r1, #0x12
	bl CreateWeaponSaber
	adds r1, r6, #0
	adds r1, #0xee
	ldrb r0, [r1]
	adds r0, #1
	b _0802F218
	.align 2, 0
_0802F1B8: .4byte 0x00000129
_0802F1BC:
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r6, #0
	bl KeepMotion
	ldr r0, _0802F1E4 @ =0x00000129
	adds r1, r6, r0
	ldrb r0, [r1]
	mov r8, r1
	cmp r0, #8
	bhi _0802F21A
	ldr r1, _0802F1E8 @ =0x00001801
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	b _0802F21A
	.align 2, 0
_0802F1E4: .4byte 0x00000129
_0802F1E8: .4byte 0x00001801
_0802F1EC:
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	ldr r1, _0802F264 @ =0x00000129
	adds r1, r1, r6
	mov r8, r1
	cmp r0, #3
	bne _0802F21A
	movs r0, #0x92
	lsls r0, r0, #1
	adds r2, r6, r0
	ldrb r1, [r2]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0
	strb r0, [r6, #0xd]
	strb r0, [r6, #0xe]
	strb r0, [r6, #0xf]
	adds r1, r6, #0
	adds r1, #0xec
_0802F218:
	strb r0, [r1]
_0802F21A:
	mov r7, r8
	ldrb r0, [r7]
	cmp r0, #0
	beq _0802F29E
	subs r0, #1
	strb r0, [r7]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0802F268
	adds r0, r6, #0
	bl CalcDx
	adds r5, r0, #0
	adds r0, r6, #0
	bl GetDashSpeed
	adds r4, r0, #0
	adds r0, r6, #0
	bl CalcDx
	lsls r5, r5, #0x10
	asrs r5, r5, #0x10
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	subs r4, r4, r0
	ldrb r0, [r7]
	muls r0, r4, r0
	movs r1, #0x18
	bl __divsi3
	adds r5, r5, r0
	b _0802F29C
	.align 2, 0
_0802F264: .4byte 0x00000129
_0802F268:
	adds r0, r6, #0
	bl CalcDx
	adds r5, r0, #0
	adds r0, r6, #0
	bl GetDashSpeed
	adds r4, r0, #0
	adds r0, r6, #0
	bl CalcDx
	lsls r5, r5, #0x10
	asrs r5, r5, #0x10
	rsbs r5, r5, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	subs r4, r4, r0
	mov r1, r8
	ldrb r0, [r1]
	muls r0, r4, r0
	movs r1, #0x18
	bl __divsi3
	subs r5, r5, r0
_0802F29C:
	str r5, [r6, #0x5c]
_0802F29E:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
