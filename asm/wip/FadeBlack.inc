	push {r4, r5, r6, r7, lr}
	movs r4, #0xff
_08003CF4:
	mov lr, r1
	ldr r1, [r0]
	ldr r5, [r3]
	ands r5, r1
	muls r5, r2, r5
	lsrs r5, r5, #5
	ldr r6, [r3]
	ands r6, r5
	ldr r5, [r3, #4]
	ands r5, r1
	muls r5, r2, r5
	lsrs r5, r5, #5
	ldr r7, [r3, #4]
	ands r7, r5
	orrs r6, r7
	ldr r5, [r3, #8]
	ands r5, r1
	lsrs r5, r5, #5
	muls r5, r2, r5
	ldr r7, [r3, #8]
	ands r7, r5
	orrs r6, r7
	mov r1, lr
	str r6, [r1]
	adds r0, #4
	adds r1, #4
	subs r4, #1
	bpl _08003CF4
	pop {r4, r5, r6, r7}
	pop {r0}
	mov lr, r0
	bx lr
