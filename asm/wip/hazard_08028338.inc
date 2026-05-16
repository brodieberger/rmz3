	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r7, r0, #0
	mov sl, r1
	mov sb, r2
	movs r5, #0
	movs r1, #0xc6
	lsls r1, r1, #1
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r5, r0
	bhs _080283DA
	ldr r6, _080283BC @ =gOverworld
	mov r8, r0
_0802835A:
	movs r1, #0xae
	lsls r1, r1, #1
	adds r0, r7, r1
	adds r0, r0, r5
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r3, r0, #3
	ldr r1, _080283C0 @ =0x020023DC
	adds r0, r3, r1
	ldr r4, [r0]
	mov r0, sl
	subs r1, r0, r4
	adds r0, r3, r6
	mov ip, r0
	movs r0, #0xec
	lsls r0, r0, #1
	add r0, ip
	ldrh r0, [r0]
	adds r1, r1, r0
	lsls r0, r0, #1
	cmp r1, r0
	bhs _080283D0
	ldr r1, _080283C4 @ =0x020023E0
	adds r0, r3, r1
	ldr r2, [r0]
	mov r0, sb
	subs r1, r0, r2
	movs r0, #0xed
	lsls r0, r0, #1
	add r0, ip
	ldrh r0, [r0]
	adds r1, r1, r0
	lsls r0, r0, #1
	cmp r1, r0
	bhs _080283D0
	ldr r1, _080283C8 @ =gOverworld+484
	adds r0, r3, r1
	ldr r0, [r0]
	cmp r4, r0
	bne _080283D0
	ldr r1, _080283CC @ =gOverworld+488
	adds r0, r3, r1
	ldr r0, [r0]
	cmp r2, r0
	beq _080283D0
	movs r0, #1
	b _080283DC
	.align 2, 0
_080283BC: .4byte gOverworld
_080283C0: .4byte gOverworld+0x1DC
_080283C4: .4byte gOverworld+0x1E0
_080283C8: .4byte gOverworld+484
_080283CC: .4byte gOverworld+488
_080283D0:
	adds r0, r5, #1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, r8
	blo _0802835A
_080283DA:
	movs r0, #0
_080283DC:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
