	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	lsls r1, r1, #0x10
	lsrs r7, r1, #0x10
	movs r6, #0
	ldr r3, _08003FF4 @ =gPaletteAnimationManager
	adds r0, r4, #1
	mov r8, r0
	mov r2, r8
	adds r1, r3, #0
_08003F46:
	ldrh r0, [r1]
	cmp r0, r2
	bne _08003F4E
	b _08004050
_08003F4E:
	adds r1, #2
	adds r6, #1
	cmp r6, #0xf
	ble _08003F46
	movs r6, #0
	ldrh r0, [r3]
	cmp r0, #0
	beq _08003F6E
	adds r1, r3, #0
_08003F60:
	adds r1, #2
	adds r6, #1
	cmp r6, #0xf
	bgt _08003F6E
	ldrh r0, [r1]
	cmp r0, #0
	bne _08003F60
_08003F6E:
	cmp r6, #0x10
	beq _08004050
	lsls r0, r6, #2
	adds r0, r0, r6
	lsls r0, r0, #2
	ldr r1, _08003FF8 @ =gPaletteAnimationManager+32
	adds r5, r0, r1
	lsls r1, r4, #2
	ldr r0, _08003FFC @ =gPlttAnimDataOffsets
	adds r2, r1, r0
	ldr r0, [r2]
	adds r0, r0, r2
	str r0, [r5]
	ldr r0, _08004000 @ =gPlttAnimScriptTable
	adds r1, r1, r0
	ldr r1, [r1]
	str r1, [r5, #4]
	movs r0, #0
	strh r0, [r5, #0x10]
	strh r7, [r5, #0x12]
	adds r4, r5, #0
	adds r4, #8
	adds r0, r4, #0
	bl ResetAnimState
	adds r0, r4, #0
	movs r1, #0
	bl SetAnimSubID
	ldr r2, [r5]
	ldrb r0, [r2, #2]
	ldrb r4, [r2, #1]
	subs r0, r0, r4
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	ldrh r1, [r5, #0x12]
	ldr r0, _08004004 @ =0x000001FF
	ands r0, r1
	cmp r0, #0
	bne _08004010
	ldrb r1, [r5, #0xc]
	ldr r0, [r5, #8]
	lsls r1, r1, #2
	adds r1, r1, r0
	movs r0, #0xd
	ldrsb r0, [r5, r0]
	ldr r1, [r1]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	muls r0, r3, r0
	lsls r0, r0, #1
	adds r0, #4
	adds r0, r2, r0
	lsls r1, r4, #1
	ldrh r5, [r5, #0x12]
	adds r1, r1, r5
	ldr r2, _08004008 @ =gPaletteManager
	adds r1, r1, r2
	ldr r2, _0800400C @ =0x001FFFFF
	ands r2, r3
	bl CpuSet
	b _08004046
	.align 2, 0
_08003FF4: .4byte gPaletteAnimationManager
_08003FF8: .4byte gPaletteAnimationManager+32
_08003FFC: .4byte gPlttAnimDataOffsets
_08004000: .4byte gPlttAnimScriptTable
_08004004: .4byte 0x000001FF
_08004008: .4byte gPaletteManager
_0800400C: .4byte 0x001FFFFF
_08004010:
	ldrb r1, [r5, #0xc]
	ldr r0, [r5, #8]
	lsls r1, r1, #2
	adds r1, r1, r0
	movs r0, #0xd
	ldrsb r0, [r5, r0]
	ldr r1, [r1]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	muls r0, r3, r0
	lsls r0, r0, #1
	adds r0, #4
	adds r0, r2, r0
	lsls r1, r4, #1
	movs r2, #0x1f
	ands r1, r2
	ldrh r5, [r5, #0x12]
	adds r1, r1, r5
	ldr r2, _0800405C @ =gPaletteManager
	adds r1, r1, r2
	ldr r2, _08004060 @ =0x001FFFFF
	ands r2, r3
	bl CpuSet
_08004046:
	ldr r1, _08004064 @ =gPaletteAnimationManager
	lsls r0, r6, #1
	adds r0, r0, r1
	mov r1, r8
	strh r1, [r0]
_08004050:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800405C: .4byte gPaletteManager
_08004060: .4byte 0x001FFFFF
_08004064: .4byte gPaletteAnimationManager
