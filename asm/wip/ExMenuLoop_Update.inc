	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	ldr r1, _080F7C14 @ =0x000064AC
	adds r0, r6, r1
	ldr r0, [r0]
	mov r8, r0
	adds r0, r6, #0
	bl TrySlideMenu
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080F7B46
	b _080F7CD2
_080F7B46:
	movs r0, #0x3e
	bl StepPaletteAnimation
	movs r0, #0x3f
	bl StepPaletteAnimation
	movs r0, #0xdf
	lsls r0, r0, #4
	adds r4, r6, r0
	ldrb r7, [r4, #4]
	ldr r5, _080F7C18 @ =gJoypad
	ldrh r1, [r5, #6]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080F7B72
	adds r0, r7, #0
	adds r0, #8
	movs r1, #0xc
	bl __modsi3
	strb r0, [r4, #4]
_080F7B72:
	ldrh r5, [r5, #6]
	movs r0, #0x80
	ands r0, r5
	cmp r0, #0
	beq _080F7B88
	ldrb r0, [r4, #4]
	adds r0, #4
	movs r1, #0xc
	bl __modsi3
	strb r0, [r4, #4]
_080F7B88:
	movs r0, #0x20
	ands r0, r5
	cmp r0, #0
	beq _080F7BA4
	ldrb r1, [r4, #4]
	lsrs r0, r1, #2
	lsls r3, r0, #2
	adds r2, r1, #3
	adds r0, r2, #0
	asrs r0, r0, #2
	lsls r0, r0, #2
	subs r0, r2, r0
	adds r0, r3, r0
	strb r0, [r4, #4]
_080F7BA4:
	ldr r0, _080F7C18 @ =gJoypad
	ldrh r1, [r0, #6]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080F7BCA
	movs r1, #0xdf
	lsls r1, r1, #4
	adds r4, r6, r1
	ldrb r1, [r4, #4]
	lsrs r0, r1, #2
	lsls r3, r0, #2
	adds r2, r1, #1
	adds r0, r2, #0
	asrs r0, r0, #2
	lsls r0, r0, #2
	subs r0, r2, r0
	adds r0, r3, r0
	strb r0, [r4, #4]
_080F7BCA:
	movs r0, #0xdf
	lsls r0, r0, #4
	adds r5, r6, r0
	ldrb r1, [r5, #4]
	cmp r7, r1
	beq _080F7BDC
	movs r0, #1
	bl PlaySound
_080F7BDC:
	ldr r0, _080F7C18 @ =gJoypad
	ldrh r1, [r0, #4]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	mov r4, r8
	adds r4, #0xb4
	cmp r0, #0
	beq _080F7C2E
	ldrh r0, [r4, #0x14]
	ldrb r3, [r5, #4]
	lsls r2, r3
	ands r0, r2
	asrs r0, r3
	cmp r0, #0
	beq _080F7C28
	ldrh r1, [r4, #0x12]
	adds r0, r1, #0
	ands r0, r2
	asrs r0, r3
	cmp r0, #0
	beq _080F7C1C
	eors r1, r2
	strh r1, [r4, #0x12]
	movs r0, #3
	bl PlaySound
	b _080F7C2E
	.align 2, 0
_080F7C14: .4byte 0x000064AC
_080F7C18: .4byte gJoypad
_080F7C1C:
	orrs r1, r2
	strh r1, [r4, #0x12]
	movs r0, #2
	bl PlaySound
	b _080F7C2E
_080F7C28:
	movs r0, #4
	bl PlaySound
_080F7C2E:
	movs r0, #0xdf
	lsls r0, r0, #4
	adds r6, r6, r0
	ldr r2, [r6]
	ldrb r1, [r6, #4]
	movs r0, #3
	ands r1, r0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	movs r1, #0x8e
	lsls r1, r1, #1
	adds r0, r0, r1
	adds r2, #0x74
	strh r0, [r2]
	ldr r2, [r6]
	ldrb r1, [r6, #4]
	lsrs r1, r1, #2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r0, #0x28
	adds r2, #0x76
	strh r0, [r2]
	ldrh r1, [r4, #0x14]
	ldrb r2, [r6, #4]
	movs r0, #1
	lsls r0, r2
	ands r1, r0
	asrs r1, r2
	cmp r1, #0
	beq _080F7CAC
	ldr r5, _080F7CA0 @ =StringOfsTable
	movs r1, #0xe1
	lsls r1, r1, #1
	adds r0, r2, r1
	lsls r0, r0, #1
	adds r0, r0, r5
	ldrh r0, [r0]
	ldr r4, _080F7CA4 @ =gStringData
	adds r0, r0, r4
	movs r1, #2
	movs r2, #0xe
	bl PrintString
	ldrb r0, [r6, #4]
	ldr r1, _080F7CA8 @ =0x000001CF
	adds r0, r0, r1
	lsls r0, r0, #1
	adds r0, r0, r5
	ldrh r0, [r0]
	adds r0, r0, r4
	movs r1, #0x11
	movs r2, #1
	bl PrintString
	b _080F7CD2
	.align 2, 0
_080F7CA0: .4byte StringOfsTable
_080F7CA4: .4byte gStringData
_080F7CA8: .4byte 0x000001CF
_080F7CAC:
	ldr r4, _080F7CDC @ =StringOfsTable
	movs r1, #0xe7
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrh r0, [r0]
	ldr r5, _080F7CE0 @ =gStringData
	adds r0, r0, r5
	movs r1, #2
	movs r2, #0xe
	bl PrintString
	ldr r0, _080F7CE4 @ =0x000003B6
	adds r4, r4, r0
	ldrh r0, [r4]
	adds r0, r0, r5
	movs r1, #0x11
	movs r2, #1
	bl PrintString
_080F7CD2:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080F7CDC: .4byte StringOfsTable
_080F7CE0: .4byte gStringData
_080F7CE4: .4byte 0x000003B6
