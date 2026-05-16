	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x24
	adds r5, r1, #0
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	movs r0, #0
	mov sl, r0
	ldr r0, [r2]
	str r0, [sp]
	ldr r0, [r2, #4]
	str r0, [sp, #4]
	movs r1, #0
	str r1, [sp, #0x20]
	adds r0, r5, #0
	adds r0, #0x97
	ldrb r0, [r0]
	movs r1, #0xf0
	ands r1, r0
	cmp r1, #0x10
	bne _08025286
	movs r2, #1
	str r2, [sp, #0x20]
	b _08025298
_08025286:
	cmp r1, #0x20
	bne _08025290
	movs r0, #2
	str r0, [sp, #0x20]
	b _08025298
_08025290:
	cmp r1, #0x30
	bne _08025298
	movs r1, #3
	str r1, [sp, #0x20]
_08025298:
	ldr r0, _080252C4 @ =sWeakElements
	lsls r1, r3, #2
	ldr r2, [sp, #0x20]
	adds r1, r2, r1
	adds r1, r1, r0
	ldrb r0, [r1]
	cmp r0, #0
	bne _080252AA
	b _080255FA
_080252AA:
	cmp r3, #6
	bls _080252B0
	b _080253D4
_080252B0:
	ldr r0, [sp, #0x20]
	cmp r0, #1
	bne _080252C8
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateThunderEffect
	mov sl, r0
	b _080255AE
	.align 2, 0
_080252C4: .4byte sWeakElements
_080252C8:
	ldr r1, [sp, #0x20]
	cmp r1, #2
	bne _0802534C
	ldr r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #3
	adds r0, r0, r4
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, _08025340 @ =0xFFFFF400
	adds r0, r0, r2
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateFlameEffect
	mov sl, r0
	ldr r0, [sp]
	ldr r1, _08025344 @ =0xFFFFF200
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	adds r0, r0, r4
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateFlameEffect
	ldr r0, [sp]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateFlameEffect
	ldr r0, [sp]
	ldr r2, _08025348 @ =0xFFFFF600
	adds r0, r0, r2
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateFlameEffect
	b _080255AE
	.align 2, 0
_08025340: .4byte 0xFFFFF400
_08025344: .4byte 0xFFFFF200
_08025348: .4byte 0xFFFFF600
_0802534C:
	ldr r2, [sp, #0x20]
	cmp r2, #3
	beq _08025354
	b _080255AE
_08025354:
	ldr r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #3
	adds r0, r0, r4
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r1, _080253C8 @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateIceEffect
	mov sl, r0
	ldr r0, [sp]
	ldr r2, _080253CC @ =0xFFFFF200
	adds r0, r0, r2
	str r0, [sp]
	ldr r0, [sp, #4]
	adds r0, r0, r4
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateIceEffect
	ldr r0, [sp]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateIceEffect
	ldr r0, [sp]
	ldr r1, _080253D0 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r0, r2
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0x5a
	bl CreateIceEffect
	b _080255AE
	.align 2, 0
_080253C8: .4byte 0xFFFFF400
_080253CC: .4byte 0xFFFFF200
_080253D0: .4byte 0xFFFFF600
_080253D4:
	movs r7, #0x1e
	ldr r0, [sp, #0x20]
	cmp r0, #1
	bne _08025426
	add r4, sp, #8
	ldr r6, _08025408 @ =Coord_ARRAY_0835e01c
	movs r1, #6
	mov r8, r1
_080253E4:
	ldr r0, [sp]
	ldr r1, [r6]
	adds r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	ldr r1, [r6, #4]
	adds r0, r0, r1
	str r0, [r4, #4]
	mov r2, sl
	cmp r2, #0
	bne _0802540C
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateThunderEffect
	mov sl, r0
	b _08025416
	.align 2, 0
_08025408: .4byte Coord_ARRAY_0835e01c
_0802540C:
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateThunderEffect
_08025416:
	adds r6, #8
	movs r0, #1
	rsbs r0, r0, #0
	add r8, r0
	mov r1, r8
	cmp r1, #0
	bge _080253E4
	b _080255AE
_08025426:
	ldr r2, [sp, #0x20]
	cmp r2, #2
	bne _080254F0
	add r0, sp, #0x10
	mov sb, r0
	mov r4, sb
	ldr r6, _08025470 @ =Coord_ARRAY_0835e054
	movs r1, #3
	mov r8, r1
_08025438:
	ldr r0, [sp]
	ldr r1, [r6]
	adds r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	ldr r1, [r6, #4]
	adds r0, r0, r1
	str r0, [r4, #4]
	ldr r0, [sp, #0x10]
	movs r2, #0xc0
	lsls r2, r2, #3
	adds r0, r0, r2
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	ldr r1, _08025474 @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [r4, #4]
	mov r2, sl
	cmp r2, #0
	bne _08025478
	adds r0, r5, #0
	mov r1, sb
	adds r2, r7, #0
	bl CreateFlameEffect
	mov sl, r0
	b _08025482
	.align 2, 0
_08025470: .4byte Coord_ARRAY_0835e054
_08025474: .4byte 0xFFFFF400
_08025478:
	adds r0, r5, #0
	mov r1, sb
	adds r2, r7, #0
	bl CreateFlameEffect
_08025482:
	ldr r0, [sp, #0x10]
	ldr r1, _080254E8 @ =0xFFFFF200
	adds r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	movs r2, #0xc0
	lsls r2, r2, #3
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateFlameEffect
	ldr r0, [sp, #0x10]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateFlameEffect
	ldr r0, [sp, #0x10]
	ldr r1, _080254EC @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateFlameEffect
	adds r6, #8
	movs r0, #1
	rsbs r0, r0, #0
	add r8, r0
	mov r1, r8
	cmp r1, #0
	bge _08025438
	b _080255AE
	.align 2, 0
_080254E8: .4byte 0xFFFFF200
_080254EC: .4byte 0xFFFFF600
_080254F0:
	ldr r2, [sp, #0x20]
	cmp r2, #3
	bne _080255AE
	add r0, sp, #0x18
	mov sb, r0
	mov r4, sb
	ldr r6, _08025538 @ =Coord_ARRAY_0835e054
	movs r1, #3
	mov r8, r1
_08025502:
	ldr r0, [sp]
	ldr r1, [r6]
	adds r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [sp, #4]
	ldr r1, [r6, #4]
	adds r0, r0, r1
	str r0, [r4, #4]
	ldr r0, [sp, #0x18]
	movs r2, #0xc0
	lsls r2, r2, #3
	adds r0, r0, r2
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	ldr r1, _0802553C @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [r4, #4]
	mov r2, sl
	cmp r2, #0
	bne _08025540
	adds r0, r5, #0
	mov r1, sb
	adds r2, r7, #0
	bl CreateIceEffect
	mov sl, r0
	b _0802554A
	.align 2, 0
_08025538: .4byte Coord_ARRAY_0835e054
_0802553C: .4byte 0xFFFFF400
_08025540:
	adds r0, r5, #0
	mov r1, sb
	adds r2, r7, #0
	bl CreateIceEffect
_0802554A:
	ldr r0, [sp, #0x18]
	ldr r1, _080255DC @ =0xFFFFF200
	adds r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	movs r2, #0xc0
	lsls r2, r2, #3
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateIceEffect
	ldr r0, [sp, #0x18]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateIceEffect
	ldr r0, [sp, #0x18]
	ldr r1, _080255E0 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r0, r2
	str r0, [r4, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	adds r2, r7, #0
	bl CreateIceEffect
	adds r6, #8
	movs r0, #1
	rsbs r0, r0, #0
	add r8, r0
	mov r1, r8
	cmp r1, #0
	bge _08025502
_080255AE:
	mov r2, sl
	cmp r2, #0
	beq _080255FA
	ldr r0, [sp, #0x20]
	cmp r0, #1
	bne _080255CA
	movs r0, #0x3c
	bl PlaySound
	adds r1, r5, #0
	adds r1, #0x94
	ldrb r0, [r1]
	adds r0, #0x1e
	strb r0, [r1]
_080255CA:
	ldr r1, [sp, #0x20]
	cmp r1, #2
	bne _080255E4
	movs r0, #0x3d
	bl PlaySound
	movs r0, #0
	b _080255FC
	.align 2, 0
_080255DC: .4byte 0xFFFFF200
_080255E0: .4byte 0xFFFFF600
_080255E4:
	ldr r2, [sp, #0x20]
	cmp r2, #3
	bne _080255FA
	movs r0, #0x40
	bl PlaySound
	adds r1, r5, #0
	adds r1, #0x94
	ldrb r0, [r1]
	adds r0, #0x1e
	strb r0, [r1]
_080255FA:
	mov r0, sl
_080255FC:
	add sp, #0x24
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
