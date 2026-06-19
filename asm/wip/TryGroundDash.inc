	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r7, r0, #0
	mov r8, r1
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08028DD8
	mov r1, r8
	movs r2, #0
	ldrsh r0, [r1, r2]
	ldr r2, [r7, #0x54]
	subs r0, r2, r0
	ldrh r1, [r1, #4]
	b _08028DE4
_08028DD8:
	mov r3, r8
	movs r1, #0
	ldrsh r0, [r3, r1]
	ldr r2, [r7, #0x54]
	adds r0, r2, r0
	ldrh r1, [r3, #4]
_08028DE4:
	lsls r1, r1, #0x10
	asrs r1, r1, #0x11
	adds r4, r0, r1
	subs r5, r0, r1
	adds r0, r2, #0
	ldr r1, [r7, #0x58]
	adds r1, #1
	bl GetGroundMetatileAttr
	movs r1, #0xf
	ands r1, r0
	cmp r1, #1
	bne _08028E12
	mov r2, r8
	movs r3, #2
	ldrsh r0, [r2, r3]
	ldr r1, [r7, #0x58]
	adds r1, r1, r0
	ldrh r0, [r2, #6]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x11
	adds r6, r1, r0
	b _08028E1C
_08028E12:
	mov r0, r8
	movs r2, #2
	ldrsh r1, [r0, r2]
	ldr r0, [r7, #0x58]
	adds r6, r0, r1
_08028E1C:
	adds r0, r4, #0
	adds r1, r6, #0
	bl PushoutToLeft2
	cmp r0, #0
	blt _08028E36
	adds r0, r7, #0
	adds r1, r4, #0
	adds r2, r6, #0
	bl hazard_0802802c
	cmp r0, #0
	bge _08028E68
_08028E36:
	adds r0, r0, r5
	mov sb, r0
	adds r1, r6, #0
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	movs r0, #0x84
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08028E68
	movs r0, #0xf
	ands r1, r0
	cmp r1, #1
	bne _08028E58
	b _08028F58
_08028E58:
	adds r0, r7, #0
	mov r1, sb
	adds r2, r6, #0
	bl IsInHazard
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08028F58
_08028E68:
	adds r0, r5, #0
	adds r1, r6, #0
	bl PushoutToRight2
	cmp r0, #0
	bgt _08028E82
	adds r0, r7, #0
	adds r1, r5, #0
	adds r2, r6, #0
	bl hazard_0802802c
	cmp r0, #0
	ble _08028EB2
_08028E82:
	adds r0, r0, r4
	mov sb, r0
	adds r1, r6, #0
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	movs r0, #0x84
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08028EB2
	movs r0, #0xf
	ands r1, r0
	cmp r1, #1
	beq _08028F58
	adds r0, r7, #0
	mov r1, sb
	adds r2, r6, #0
	bl IsInHazard
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08028F58
_08028EB2:
	mov r3, r8
	movs r1, #2
	ldrsh r0, [r3, r1]
	ldr r1, [r7, #0x58]
	adds r1, r1, r0
	ldrh r0, [r3, #6]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x11
	subs r6, r1, r0
	adds r0, r4, #0
	adds r1, r6, #0
	bl PushoutToLeft2
	cmp r0, #0
	blt _08028EDE
	adds r0, r7, #0
	adds r1, r4, #0
	adds r2, r6, #0
	bl hazard_0802802c
	cmp r0, #0
	bge _08028F0E
_08028EDE:
	adds r0, r0, r5
	mov r8, r0
	adds r1, r6, #0
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	movs r0, #0x84
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08028F0E
	movs r0, #0xf
	ands r1, r0
	cmp r1, #1
	beq _08028F58
	adds r0, r7, #0
	mov r1, r8
	adds r2, r6, #0
	bl IsInHazard
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08028F58
_08028F0E:
	adds r0, r5, #0
	adds r1, r6, #0
	bl PushoutToRight2
	cmp r0, #0
	bgt _08028F28
	adds r0, r7, #0
	adds r1, r5, #0
	adds r2, r6, #0
	bl hazard_0802802c
	cmp r0, #0
	ble _08028F5C
_08028F28:
	adds r4, r0, r4
	adds r0, r4, #0
	adds r1, r6, #0
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	movs r0, #0x84
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08028F5C
	movs r0, #0xf
	ands r1, r0
	cmp r1, #1
	beq _08028F58
	adds r0, r7, #0
	adds r1, r4, #0
	adds r2, r6, #0
	bl IsInHazard
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08028F5C
_08028F58:
	movs r0, #0
	b _08028F5E
_08028F5C:
	movs r0, #1
_08028F5E:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
