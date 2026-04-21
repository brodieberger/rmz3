	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	asrs r3, r5, #0xc
	asrs r2, r6, #0xc
	movs r0, #0xee
	lsls r0, r0, #3
	cmp r3, r0
	bhi _0800A4AA
	ldr r0, _0800A470 @ =0x000004F5
	cmp r2, r0
	bhi _0800A4AA
	ldr r7, _0800A474 @ =gOverworld+440
	movs r0, #0xc5
	lsls r0, r0, #3
	adds r1, r7, r0
	ldrh r0, [r1]
	muls r0, r2, r0
	adds r0, r0, r3
	adds r0, #2
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, [r7]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r4, [r0]
	ldr r0, _0800A478 @ =gShapeCheckerUp
	movs r2, #0xf
	ands r2, r4
	lsls r2, r2, #2
	adds r2, r2, r0
	ldr r3, _0800A47C @ =0x00000FFF
	adds r0, r5, #0
	ands r0, r3
	adds r1, r6, #0
	ands r1, r3
	ldr r2, [r2]
	bl _call_via_r2
	cmp r0, #0
	beq _0800A498
	movs r0, #0x80
	lsls r0, r0, #6
	ands r0, r4
	cmp r0, #0
	beq _0800A484
	ldr r1, _0800A480 @ =0x0002BE50
	adds r0, r7, r1
	b _0800A4B0
	.align 2, 0
_0800A470: .4byte 0x000004F5
_0800A474: .4byte gOverworld+440
_0800A478: .4byte gShapeCheckerUp
_0800A47C: .4byte 0x00000FFF
_0800A480: .4byte 0x0002BE50
_0800A484:
	movs r0, #0x80
	lsls r0, r0, #7
	ands r4, r0
	cmp r4, #0
	beq _0800A498
	ldr r1, _0800A494 @ =0x0002BE4C
	adds r0, r7, r1
	b _0800A4B0
	.align 2, 0
_0800A494: .4byte 0x0002BE4C
_0800A498:
	adds r0, r5, #0
	adds r1, r6, #0
	bl GetHazardMetatileAttr
	movs r1, #0x80
	lsls r1, r1, #6
	ands r1, r0
	cmp r1, #0
	bne _0800A4AE
_0800A4AA:
	movs r0, #0
	b _0800A4B2
_0800A4AE:
	ldr r0, _0800A4B8 @ =gConveyor
_0800A4B0:
	ldr r0, [r0]
_0800A4B2:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0800A4B8: .4byte gConveyor
