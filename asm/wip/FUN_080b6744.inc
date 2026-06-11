	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x7c]
	bl UpdateEntityAnim
	ldrb r1, [r5, #3]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080B6772
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080B676A
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080B6770
_080B676A:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080B6770:
	strb r0, [r4, #0xa]
_080B6772:
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x68]
	adds r2, r1, r0
	str r2, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r3, r0, r2
	str r3, [r4, #0x58]
	ldrb r1, [r5, #3]
	movs r0, #0x20
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _080B67F6
	adds r1, r3, #0
	cmp r2, #0
	ble _080B67A0
	adds r0, r4, #0
	adds r0, #0x76
	movs r2, #0
	ldrsh r0, [r0, r2]
	adds r1, r1, r0
	b _080B67AA
_080B67A0:
	adds r0, r4, #0
	adds r0, #0x76
	movs r1, #0
	ldrsh r0, [r0, r1]
	subs r1, r3, r0
_080B67AA:
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080B67B8
	strb r5, [r4, #0x12]
_080B67B8:
	ldr r0, [r4, #0x5c]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r1, [r4, #0x54]
	adds r1, r1, r0
	str r1, [r4, #0x54]
	adds r2, r1, #0
	cmp r0, #0
	ble _080B67D8
	adds r0, r4, #0
	adds r0, #0x74
	movs r1, #0
	ldrsh r0, [r0, r1]
	adds r2, r2, r0
	b _080B67E2
_080B67D8:
	adds r0, r4, #0
	adds r0, #0x74
	movs r2, #0
	ldrsh r0, [r0, r2]
	subs r2, r1, r0
_080B67E2:
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080B6804
	movs r0, #0
	strb r0, [r4, #0x12]
	b _080B6804
_080B67F6:
	ldr r0, [r4, #0x5c]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r1, [r4, #0x54]
	adds r1, r1, r0
	str r1, [r4, #0x54]
_080B6804:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080B682A
	ldr r1, _080B6830 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl SlashedEnemy_Die
_080B682A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B6830: .4byte gVFXFnTable
