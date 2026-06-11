	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r7, r0, #0
	ldrb r0, [r7, #0x1c]
	adds r1, r0, #0
	cmp r1, #0
	bne _0801A9F4
	strh r1, [r7, #0x22]
	adds r0, #1
	strb r0, [r7, #0x1c]
_0801A9F4:
	ldr r2, [r7, #0x48]
	ldr r1, [r2]
	ldr r0, [r7, #0x4c]
	adds r5, r1, r0
	ldr r1, [r2, #4]
	ldr r0, [r7, #0x54]
	adds r6, r1, r0
	ldr r0, [r7, #0x30]
	str r0, [sp]
	ldr r1, [r7, #0x34]
	str r1, [sp, #4]
	subs r2, r0, r5
	cmp r2, #0
	ble _0801AA14
	subs r0, r0, r2
	str r0, [sp]
_0801AA14:
	cmp r2, #0
	bge _0801AA1E
	ldr r0, [sp]
	subs r0, r0, r2
	str r0, [sp]
_0801AA1E:
	subs r1, r1, r6
	ldr r0, _0801AA58 @ =0xFFFFF000
	cmp r1, r0
	ble _0801AA30
	ldr r0, [sp, #4]
	ldr r2, _0801AA58 @ =0xFFFFF000
	adds r0, r0, r2
	subs r0, r0, r1
	str r0, [sp, #4]
_0801AA30:
	ldr r0, _0801AA5C @ =0xFFFFE800
	cmp r1, r0
	bge _0801AA40
	ldr r0, [sp, #4]
	ldr r2, _0801AA5C @ =0xFFFFE800
	adds r0, r0, r2
	subs r0, r0, r1
	str r0, [sp, #4]
_0801AA40:
	add r4, sp, #8
	mov r0, sp
	adds r1, r4, #0
	bl CalcCameraDelta
	ldrb r1, [r7, #0x19]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0801AA60
	ldr r5, [sp]
	b _0801AA66
	.align 2, 0
_0801AA58: .4byte 0xFFFFF000
_0801AA5C: .4byte 0xFFFFE800
_0801AA60:
	ldr r1, [sp]
	ldr r0, [sp, #8]
	adds r5, r1, r0
_0801AA66:
	ldr r0, [sp, #4]
	ldr r1, [r4, #4]
	adds r6, r0, r1
	ldr r1, _0801AABC @ =0xFFFF8800
	adds r0, r5, r1
	ldr r1, [r7, #0x5c]
	cmp r0, r1
	bge _0801AA7C
	movs r2, #0xf0
	lsls r2, r2, #7
	adds r5, r1, r2
_0801AA7C:
	movs r1, #0xf0
	lsls r1, r1, #7
	adds r0, r5, r1
	ldr r1, [r7, #0x60]
	cmp r0, r1
	ble _0801AA8C
	ldr r2, _0801AABC @ =0xFFFF8800
	adds r5, r1, r2
_0801AA8C:
	ldr r1, _0801AAC0 @ =0xFFFFB000
	adds r0, r6, r1
	ldr r1, [r7, #0x64]
	cmp r0, r1
	bge _0801AA9C
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r6, r1, r2
_0801AA9C:
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r6, r1
	ldr r1, [r7, #0x68]
	cmp r0, r1
	ble _0801AAAC
	ldr r2, _0801AAC0 @ =0xFFFFB000
	adds r6, r1, r2
_0801AAAC:
	ldrb r1, [r7, #0x19]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0801AAC4
	str r6, [r7, #0x34]
	str r5, [r7, #0x30]
	b _0801AAFE
	.align 2, 0
_0801AABC: .4byte 0xFFFF8800
_0801AAC0: .4byte 0xFFFFB000
_0801AAC4:
	ldr r1, [r7, #0x30]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r0, r1, r2
	cmp r0, r5
	blt _0801AAD8
	ldr r2, _0801AADC @ =0xFFFFFC00
	adds r0, r1, r2
	cmp r0, r5
	ble _0801AAE0
_0801AAD8:
	str r0, [r7, #0x30]
	b _0801AAE2
	.align 2, 0
_0801AADC: .4byte 0xFFFFFC00
_0801AAE0:
	str r5, [r7, #0x30]
_0801AAE2:
	ldr r1, [r7, #0x34]
	subs r0, r1, r6
	cmp r0, #0
	blt _0801AAF2
	lsls r0, r1, #3
	subs r0, r0, r1
	adds r0, r0, r6
	b _0801AAFA
_0801AAF2:
	lsls r0, r1, #3
	subs r0, r0, r1
	adds r0, r0, r6
	adds r0, #7
_0801AAFA:
	asrs r0, r0, #3
	str r0, [r7, #0x34]
_0801AAFE:
	ldrb r1, [r7, #0x19]
	adds r0, r7, #0
	bl focus
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
