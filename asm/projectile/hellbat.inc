	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createBat
createBat: @ 0x080A141C
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _080A1478 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A146E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A147C @ =gProjectileFnTable
	movs r0, #0xf
	strb r0, [r3, #9]
	ldr r0, [r1, #0x3c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r4, [r0]
	adds r0, #1
	strb r5, [r0]
	ldr r0, [r6]
	ldr r1, [r6, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	str r7, [r3, #0x28]
_080A146E:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080A1478: .4byte gProjectileHeaderPtr
_080A147C: .4byte gProjectileFnTable

	thumb_func_start createEchoWave
createEchoWave: @ 0x080A1480
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A14D4 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A14CC
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A14D8 @ =gProjectileFnTable
	movs r0, #0xf
	strb r0, [r3, #9]
	ldr r0, [r1, #0x3c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r4, [r0]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	str r6, [r3, #0x28]
_080A14CC:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080A14D4: .4byte gProjectileHeaderPtr
_080A14D8: .4byte gProjectileFnTable

	thumb_func_start FUN_080a14dc
FUN_080a14dc: @ 0x080A14DC
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A1530 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A1528
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A1534 @ =gProjectileFnTable
	movs r0, #0xf
	strb r0, [r3, #9]
	ldr r0, [r1, #0x3c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r4, [r0]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	str r6, [r3, #0x28]
_080A1528:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080A1530: .4byte gProjectileHeaderPtr
_080A1534: .4byte gProjectileFnTable

	thumb_func_start FUN_080a1538
FUN_080a1538: @ 0x080A1538
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A158C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A1584
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A1590 @ =gProjectileFnTable
	movs r0, #0xf
	strb r0, [r3, #9]
	ldr r0, [r1, #0x3c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r4, [r0]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	str r6, [r3, #0x28]
_080A1584:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080A158C: .4byte gProjectileHeaderPtr
_080A1590: .4byte gProjectileFnTable

	thumb_func_start FUN_080a1594
FUN_080a1594: @ 0x080A1594
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A15E8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A15E0
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A15EC @ =gProjectileFnTable
	movs r0, #0xf
	strb r0, [r3, #9]
	ldr r0, [r1, #0x3c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #4
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r4, [r0]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	str r6, [r3, #0x28]
_080A15E0:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080A15E8: .4byte gProjectileHeaderPtr
_080A15EC: .4byte gProjectileFnTable

	thumb_func_start Projectile15_Init
Projectile15_Init: @ 0x080A15F0
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	movs r0, #0xff
	strb r0, [r6, #0x12]
	ldrb r5, [r6, #0x10]
	cmp r5, #0
	bne _080A1620
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A161C @ =0x0836B264
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	b _080A16C6
	.align 2, 0
_080A161C: .4byte 0x0836B264
_080A1620:
	cmp r5, #1
	bne _080A1660
	adds r0, r6, #0
	bl InitNonAffineMotion
	movs r5, #0
	strb r5, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0xbc
	str r5, [r0]
	adds r0, r6, #0
	bl InitNonAffineMotion
	adds r0, r6, #0
	adds r0, #0x24
	strb r5, [r0]
	adds r0, #0x2c
	movs r1, #0x80
	lsls r1, r1, #1
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A165C @ =0x0836B2DC
	b _080A16BE
	.align 2, 0
_080A165C: .4byte 0x0836B2DC
_080A1660:
	cmp r5, #2
	bne _080A1680
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A167C @ =0x0836B294
	b _080A16BE
	.align 2, 0
_080A167C: .4byte 0x0836B294
_080A1680:
	cmp r5, #3
	bne _080A16A4
	adds r0, r6, #0
	bl InitScalerotMotion1
	adds r0, r6, #0
	adds r0, #0x24
	movs r5, #0
	strb r5, [r0]
	adds r0, #0x2c
	movs r1, #0x80
	lsls r1, r1, #1
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	b _080A16B4
_080A16A4:
	cmp r5, #4
	bne _080A16CE
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
_080A16B4:
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A1708 @ =0x0836B2AC
_080A16BE:
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
_080A16C6:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
_080A16CE:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r4, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl ResetDynamicMotion
	ldr r1, _080A170C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r1, [r6, #0xd]
	strb r4, [r6, #0xe]
	strb r4, [r6, #0xf]
	adds r0, r6, #0
	bl Projectile15_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1708: .4byte 0x0836B2AC
_080A170C: .4byte gProjectileFnTable

	thumb_func_start Projectile15_Update
Projectile15_Update: @ 0x080A1710
	push {lr}
	ldr r2, _080A172C @ =0x0836B250
	ldrb r1, [r0, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldrb r2, [r0, #0xd]
	ldr r1, [r1]
	lsls r2, r2, #2
	adds r2, r2, r1
	ldr r1, [r2]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080A172C: .4byte 0x0836B250

	thumb_func_start Projectile15_Die
Projectile15_Die:
	.byte 0x02, 0x1C, 0x91, 0x7A, 0xFE, 0x20, 0x08, 0x40, 0x00, 0x21, 0x90, 0x72, 0x10, 0x1C, 0x8C, 0x30
	.byte 0x01, 0x60, 0x04, 0x30, 0x01, 0x60, 0x04, 0x30, 0x01, 0x70, 0x91, 0x7A, 0xFB, 0x20, 0x08, 0x40
	.byte 0x90, 0x72, 0x05, 0x49, 0x50, 0x7A, 0x80, 0x00, 0x40, 0x18, 0x04, 0x21, 0xD1, 0x60, 0x00, 0x68
	.byte 0x00, 0x69, 0x50, 0x61, 0x70, 0x47
	.align 2, 0
	.4byte gProjectileFnTable

	thumb_func_start FUN_080a176c
FUN_080a176c: @ 0x080A176C
	movs r2, #0
	movs r1, #1
	strb r1, [r0, #0xd]
	strb r2, [r0, #0xe]
	bx lr
	.align 2, 0

	thumb_func_start FUN_080a1778
FUN_080a1778: @ 0x080A1778
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A1792
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	b _080A180C
_080A1792:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080A1800
	ldr r2, _080A17F0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080A17F4 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _080A17F8 @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [sp]
	str r1, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	ldr r5, _080A17FC @ =0x0000AA02
	mov r0, sp
	movs r1, #0
	adds r2, r5, #0
	adds r3, r4, #0
	bl FUN_080bddcc
	mov r0, sp
	movs r1, #1
	adds r2, r5, #0
	adds r3, r4, #0
	bl FUN_080bddcc
	movs r0, #0x2a
	bl PlaySound
	b _080A180C
	.align 2, 0
_080A17F0: .4byte RNG_0202f388
_080A17F4: .4byte 0x000343FD
_080A17F8: .4byte 0x00269EC3
_080A17FC: .4byte 0x0000AA02
_080A1800:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A1824
_080A180C:
	ldr r1, _080A1820 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	b _080A1A04
	.align 2, 0
_080A1820: .4byte gProjectileFnTable
_080A1824:
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	bne _080A182C
	b _080A198C
_080A182C:
	cmp r0, #1
	bgt _080A1836
	cmp r0, #0
	beq _080A1844
	b _080A1A04
_080A1836:
	cmp r0, #2
	bne _080A183C
	b _080A19CA
_080A183C:
	cmp r0, #3
	bne _080A1842
	b _080A19D8
_080A1842:
	b _080A1A04
_080A1844:
	movs r0, #0x78
	strb r0, [r6, #0x12]
	movs r1, #0xaa
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0xb6
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	bne _080A1868
	movs r0, #0x12
	strb r0, [r6, #0x13]
	movs r0, #0x80
	lsls r0, r0, #7
	b _080A188C
_080A1868:
	cmp r1, #1
	bne _080A1876
	movs r0, #0x1a
	strb r0, [r6, #0x13]
	movs r0, #0xc0
	lsls r0, r0, #7
	b _080A188C
_080A1876:
	cmp r1, #2
	bne _080A1884
	movs r0, #0x22
	strb r0, [r6, #0x13]
	movs r0, #0x80
	lsls r0, r0, #8
	b _080A188C
_080A1884:
	movs r0, #0x2a
	strb r0, [r6, #0x13]
	movs r0, #0xa0
	lsls r0, r0, #8
_080A188C:
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x28]
	ldrb r1, [r0, #0xa]
	movs r4, #0x10
	adds r0, r4, #0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080A18C2
	ldr r1, [r6, #0x54]
	ldr r0, [r6, #0x64]
	subs r3, r1, r0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	b _080A18E6
_080A18C2:
	ldr r1, [r6, #0x54]
	ldr r0, [r6, #0x64]
	adds r3, r1, r0
	movs r2, #1
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r4
_080A18E6:
	strb r0, [r2]
	ldr r0, [r6, #0x54]
	subs r0, r3, r0
	ldrb r1, [r6, #0x13]
	bl __divsi3
	str r0, [r6, #0x5c]
	ldrb r0, [r5]
	ldrb r3, [r6, #0x13]
	cmp r0, #0
	bne _080A1900
	movs r0, #0x4c
	b _080A1912
_080A1900:
	cmp r0, #1
	bne _080A1908
	movs r0, #0x38
	b _080A1912
_080A1908:
	cmp r0, #2
	bne _080A1910
	movs r0, #0x26
	b _080A1912
_080A1910:
	movs r0, #0x14
_080A1912:
	str r0, [r6, #0x68]
	ldr r0, [r6, #0x68]
	lsls r0, r0, #8
	asrs r0, r0, #8
	adds r2, r3, #0
	adds r1, r2, #1
	asrs r1, r1, #1
	muls r1, r2, r1
	muls r0, r1, r0
	adds r1, r6, #0
	adds r1, #0xb5
	ldrb r1, [r1]
	cmp r1, #0
	bne _080A1940
	adds r1, r2, #0
	bl __divsi3
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	subs r1, r1, r0
	lsls r1, r1, #4
	b _080A197C
_080A1940:
	cmp r1, #1
	bne _080A1956
	adds r1, r2, #0
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	subs r1, r1, r0
	lsls r1, r1, #4
	b _080A197C
_080A1956:
	cmp r1, #2
	bne _080A196C
	adds r1, r2, #0
	bl __divsi3
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r0
	lsls r1, r1, #4
	b _080A197C
_080A196C:
	adds r1, r3, #0
	bl __divsi3
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	subs r1, r1, r0
	lsls r1, r1, #5
_080A197C:
	asrs r1, r1, #8
	str r1, [r6, #0x60]
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A198C:
	ldr r0, [r6, #0x68]
	rsbs r0, r0, #0
	lsls r0, r0, #8
	asrs r0, r0, #8
	ldr r2, [r6, #0x60]
	adds r2, r2, r0
	str r2, [r6, #0x60]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	adds r0, r0, r2
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080A19B2
	subs r0, #1
	strb r0, [r6, #0x13]
_080A19B2:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A1A04
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A1A04
_080A19CA:
	ldr r1, _080A1A0C @ =0x0000AA01
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A19D8:
	ldr r0, [r6, #0x68]
	rsbs r0, r0, #0
	lsls r0, r0, #8
	asrs r0, r0, #8
	ldr r2, [r6, #0x60]
	adds r2, r2, r0
	str r2, [r6, #0x60]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	adds r0, r0, r2
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080A19FE
	subs r0, #1
	strb r0, [r6, #0x13]
_080A19FE:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080A1A04:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1A0C: .4byte 0x0000AA01

	thumb_func_start FUN_080a1a10
FUN_080a1a10:
	.byte 0x00, 0x22, 0x01, 0x21, 0x41, 0x73, 0x82, 0x73, 0x70, 0x47, 0x00, 0x00

	thumb_func_start FUN_080a1a1c
FUN_080a1a1c: @ 0x080A1A1C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r4, r0, #0
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	cmp r0, #0
	ble _080A1A30
	subs r0, #1
	str r0, [r1]
_080A1A30:
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A1A50
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
_080A1A50:
	ldrb r6, [r4, #0xe]
	cmp r6, #1
	bne _080A1A58
	b _080A1C70
_080A1A58:
	cmp r6, #1
	bgt _080A1A62
	cmp r6, #0
	beq _080A1A6A
	b _080A1F04
_080A1A62:
	cmp r6, #2
	bne _080A1A68
	b _080A1ED0
_080A1A68:
	b _080A1F04
_080A1A6A:
	movs r7, #0
	strb r6, [r4, #0x12]
	strb r6, [r4, #0x13]
	str r6, [r4, #0x64]
	adds r0, r4, #0
	adds r0, #0xb5
	ldrb r5, [r0]
	cmp r5, #0
	bne _080A1AC4
	ldr r1, _080A1ABC @ =gSineTable
	movs r2, #0xca
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r2, #0x14
	ldrsh r0, [r1, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1AC0 @ =0x0000A906
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080A1B9E
	.align 2, 0
_080A1ABC: .4byte gSineTable
_080A1AC0: .4byte 0x0000A906
_080A1AC4:
	cmp r5, #1
	bne _080A1B08
	ldr r1, _080A1B00 @ =gSineTable
	movs r2, #0xb6
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r2, #0xf6
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1B04 @ =0x0000A906
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	b _080A1B8C
	.align 2, 0
_080A1B00: .4byte gSineTable
_080A1B04: .4byte 0x0000A906
_080A1B08:
	cmp r5, #2
	bne _080A1B58
	ldr r1, _080A1B50 @ =gSineTable
	adds r0, r1, #0
	adds r0, #0x94
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r2, #0x8a
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1B54 @ =0x0000A906
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080A1B9E
	.align 2, 0
_080A1B50: .4byte gSineTable
_080A1B54: .4byte 0x0000A906
_080A1B58:
	cmp r5, #3
	bne _080A1BB8
	ldr r1, _080A1BAC @ =gSineTable
	adds r0, r1, #0
	adds r0, #0x6c
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	adds r1, #0xec
	movs r2, #0
	ldrsh r0, [r1, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1BB0 @ =0x0000A906
	adds r0, r4, #0
	bl SetMotion
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
_080A1B8C:
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080A1B9E:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A1BB4 @ =0x0836B2DC
	bl SetDDP
	b _080A1C6A
	.align 2, 0
_080A1BAC: .4byte gSineTable
_080A1BB0: .4byte 0x0000A906
_080A1BB4: .4byte 0x0836B2DC
_080A1BB8:
	cmp r5, #4
	bne _080A1C1C
	ldr r1, _080A1C10 @ =gSineTable
	movs r2, #0x8a
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r2, #0xca
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1C14 @ =0x0000A90A
	adds r0, r4, #0
	bl SetMotion
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A1C18 @ =0x0836B2F4
	bl SetDDP
	b _080A1C6A
	.align 2, 0
_080A1C10: .4byte gSineTable
_080A1C14: .4byte 0x0000A90A
_080A1C18: .4byte 0x0836B2F4
_080A1C1C:
	cmp r5, #5
	bne _080A1C6A
	ldr r1, _080A1CCC @ =gSineTable
	adds r0, r1, #0
	adds r0, #0xec
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r2, #0xb6
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	ldr r1, _080A1CD0 @ =0x0000A90A
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A1CD4 @ =0x0836B2F4
	bl SetDDP
_080A1C6A:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A1C70:
	movs r6, #0
	ldr r0, [r4, #0x54]
	ldr r5, [r4, #0x5c]
	adds r2, r0, r5
	str r2, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r3, [r4, #0x60]
	adds r1, r0, r3
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb5
	ldrb r7, [r0]
	cmp r7, #3
	bgt _080A1D68
	cmp r3, #0
	bge _080A1D0C
	str r6, [sp]
	ldr r0, _080A1CD8 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r2, _080A1CDC @ =0xFFFFB000
	adds r0, r0, r2
	cmp r1, r0
	bge _080A1CA2
	movs r0, #1
	str r0, [sp]
_080A1CA2:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToLeft1
	str r0, [sp, #4]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToRight1
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	cmp r2, #0
	beq _080A1CE0
	ldr r1, [r4, #0x5c]
	cmp r1, #0
	ble _080A1CE0
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	rsbs r0, r1, #0
	b _080A1E3C
	.align 2, 0
_080A1CCC: .4byte gSineTable
_080A1CD0: .4byte 0x0000A90A
_080A1CD4: .4byte 0x0836B2F4
_080A1CD8: .4byte gStageRun+232
_080A1CDC: .4byte 0xFFFFB000
_080A1CE0:
	ldr r2, [sp, #8]
	cmp r2, #0
	beq _080A1CF6
	ldr r1, [r4, #0x5c]
	cmp r1, #0
	bge _080A1CF6
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	rsbs r0, r1, #0
	b _080A1E3C
_080A1CF6:
	ldr r1, [sp]
	cmp r1, #0
	bne _080A1CFE
	b _080A1E40
_080A1CFE:
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x60]
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	b _080A1E3E
_080A1D0C:
	adds r0, r2, #0
	bl PushoutToUp1
	str r0, [sp]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToLeft1
	str r0, [sp, #4]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToRight1
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	cmp r2, #0
	beq _080A1D3E
	ldr r1, [r4, #0x5c]
	cmp r1, #0
	ble _080A1D3E
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	rsbs r0, r1, #0
	b _080A1E3C
_080A1D3E:
	ldr r2, [sp, #8]
	cmp r2, #0
	beq _080A1D54
	ldr r1, [r4, #0x5c]
	cmp r1, #0
	bge _080A1D54
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	rsbs r0, r1, #0
	b _080A1E3C
_080A1D54:
	ldr r1, [sp]
	cmp r1, #0
	beq _080A1E40
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x60]
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	b _080A1E3E
_080A1D68:
	cmp r5, #0
	ble _080A1DCC
	adds r0, r2, #0
	bl PushoutToUp1
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, _080A1DAC @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _080A1DB0 @ =0xFFFFB000
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	cmp r1, r0
	bge _080A1D88
	movs r0, #1
	str r0, [sp, #4]
_080A1D88:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToLeft1
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	cmp r2, #0
	beq _080A1DB4
	ldr r1, [r4, #0x60]
	cmp r1, #0
	bge _080A1DB4
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	rsbs r0, r1, #0
	str r0, [r4, #0x60]
	b _080A1E3E
	.align 2, 0
_080A1DAC: .4byte gStageRun+232
_080A1DB0: .4byte 0xFFFFB000
_080A1DB4:
	ldr r2, [sp, #8]
	cmp r2, #0
	beq _080A1E2C
	ldr r1, [r4, #0x60]
	cmp r1, #0
	ble _080A1E2C
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	rsbs r0, r1, #0
	str r0, [r4, #0x60]
	b _080A1E3E
_080A1DCC:
	adds r0, r2, #0
	bl PushoutToUp1
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, _080A1E0C @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r2, _080A1E10 @ =0xFFFFB000
	adds r0, r0, r2
	ldr r1, [r4, #0x58]
	cmp r1, r0
	bge _080A1DE8
	movs r0, #1
	str r0, [sp, #4]
_080A1DE8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToRight1
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	cmp r2, #0
	beq _080A1E14
	ldr r1, [r4, #0x60]
	cmp r1, #0
	bge _080A1E14
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	rsbs r0, r1, #0
	str r0, [r4, #0x60]
	b _080A1E3E
	.align 2, 0
_080A1E0C: .4byte gStageRun+232
_080A1E10: .4byte 0xFFFFB000
_080A1E14:
	ldr r2, [sp, #8]
	cmp r2, #0
	beq _080A1E2C
	ldr r1, [r4, #0x60]
	cmp r1, #0
	ble _080A1E2C
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	rsbs r0, r1, #0
	str r0, [r4, #0x60]
	b _080A1E3E
_080A1E2C:
	ldr r1, [sp]
	cmp r1, #0
	beq _080A1E40
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
_080A1E3C:
	str r0, [r4, #0x5c]
_080A1E3E:
	movs r6, #1
_080A1E40:
	cmp r6, #1
	bne _080A1E7A
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	ldrb r2, [r4, #0xa]
	lsrs r1, r2, #4
	eors r1, r6
	ands r1, r6
	cmp r1, #0
	beq _080A1E5C
	movs r0, #0x10
	orrs r0, r2
	b _080A1E60
_080A1E5C:
	movs r0, #0xef
	ands r0, r2
_080A1E60:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
_080A1E7A:
	ldrb r0, [r4, #0x12]
	cmp r0, #1
	bls _080A1EA2
	movs r0, #0xff
	str r0, [r4, #0x64]
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A1EA2:
	ldrb r1, [r4, #0x13]
	adds r1, #1
	strb r1, [r4, #0x13]
	lsls r1, r1, #0x18
	movs r0, #0xe0
	lsls r0, r0, #0x13
	ands r0, r1
	cmp r0, #0
	bne _080A1EC8
	adds r1, r4, #0
	adds r1, #0x54
	adds r2, r7, #0
	ldrb r3, [r4, #0xa]
	lsrs r3, r3, #4
	movs r0, #1
	ands r3, r0
	adds r0, r4, #0
	bl FUN_080bde9c
_080A1EC8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080A1F04
_080A1ED0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x64]
	adds r1, r4, #0
	adds r1, #0x50
	strh r0, [r1]
	ldr r0, [r4, #0x64]
	adds r1, #2
	strh r0, [r1]
	ldr r0, [r4, #0x64]
	cmp r0, #0
	ble _080A1EEE
	subs r0, #0x20
	str r0, [r4, #0x64]
_080A1EEE:
	ldr r0, [r4, #0x64]
	cmp r0, #0x20
	bgt _080A1F04
	ldr r1, _080A1F0C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r6, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A1F04:
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1F0C: .4byte gProjectileFnTable

	thumb_func_start FUN_080a1f10
FUN_080a1f10:
	.byte 0x00, 0x22, 0x01, 0x21, 0x41, 0x73, 0x82, 0x73, 0x70, 0x47
	.align 2, 0

	thumb_func_start FUN_080a1f1c
FUN_080a1f1c: @ 0x080A1F1C
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bhi _080A1F4C
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A1F4C
	ldr r1, _080A1F48 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080A2018
	.align 2, 0
_080A1F48: .4byte gProjectileFnTable
_080A1F4C:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A1F58
	cmp r0, #1
	beq _080A1F84
	b _080A2018
_080A1F58:
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x28]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A1F6C
	movs r0, #0x12
	rsbs r0, r0, #0
	b _080A1F6E
_080A1F6C:
	movs r0, #0x12
_080A1F6E:
	str r0, [r4, #0x5c]
	movs r0, #0xc8
	strb r0, [r4, #0x12]
	movs r1, #0xa9
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A1F84:
	ldr r0, [r4, #0x64]
	ldr r3, [r4, #0x5c]
	adds r1, r0, r3
	str r1, [r4, #0x64]
	adds r2, r1, #0
	cmp r1, #0
	bge _080A1F94
	rsbs r2, r1, #0
_080A1F94:
	movs r0, #0xc0
	lsls r0, r0, #2
	cmp r2, r0
	ble _080A1FA0
	subs r0, r1, r3
	str r0, [r4, #0x64]
_080A1FA0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r2, r0, r1
	str r2, [r4, #0x54]
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A1FE4
	cmp r1, #0
	ble _080A1FBE
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToLeft1
	b _080A1FC6
_080A1FBE:
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToRight1
_080A1FC6:
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2012
	ldr r1, _080A1FE0 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080A2012
	.align 2, 0
_080A1FE0: .4byte gProjectileFnTable
_080A1FE4:
	cmp r1, #0
	ble _080A1FF2
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToLeft1
	b _080A1FFA
_080A1FF2:
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToRight1
_080A1FFA:
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2012
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
_080A2012:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A2018:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080a2020
FUN_080a2020: @ 0x080A2020
	movs r2, #0
	movs r1, #1
	strb r1, [r0, #0xd]
	strb r2, [r0, #0xe]
	bx lr
	.align 2, 0

	thumb_func_start FUN_080a202c
FUN_080a202c: @ 0x080A202C
	push {r4, r5, lr}
	sub sp, #0x10
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A2052
	adds r0, r5, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
_080A2052:
	ldrb r0, [r5, #0xe]
	cmp r0, #6
	bls _080A205A
	b _080A22DE
_080A205A:
	lsls r0, r0, #2
	ldr r1, _080A2064 @ =_080A2068
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A2064: .4byte _080A2068
_080A2068: @ jump table
	.4byte _080A2084 @ case 0
	.4byte _080A20EC @ case 1
	.4byte _080A2136 @ case 2
	.4byte _080A2162 @ case 3
	.4byte _080A21CE @ case 4
	.4byte _080A2254 @ case 5
	.4byte _080A22A8 @ case 6
_080A2084:
	adds r0, r5, #0
	adds r0, #0xb5
	ldrb r2, [r0]
	cmp r2, #1
	bne _080A209E
	ldrb r0, [r5, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r5, #0xa]
	strb r2, [r5, #0x13]
	movs r0, #3
	strb r0, [r5, #0xe]
	b _080A22DE
_080A209E:
	ldr r1, _080A20E4 @ =0x0000A903
	adds r0, r5, #0
	bl SetMotion
	movs r2, #1
	ldrb r1, [r5, #0xa]
	movs r0, #0x20
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4d
	movs r4, #0
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	movs r2, #0x20
	ldrb r1, [r3]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, _080A20E8 @ =0xFFFFFF00
	adds r0, r0, r1
	str r0, [r5, #0x54]
	movs r0, #0xe0
	lsls r0, r0, #2
	str r0, [r5, #0x60]
	str r4, [r5, #0x5c]
	b _080A2298
	.align 2, 0
_080A20E4: .4byte 0x0000A903
_080A20E8: .4byte 0xFFFFFF00
_080A20EC:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r1, r2
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bne _080A2110
	b _080A22DE
_080A2110:
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r1, [r5, #0x54]
	str r1, [sp]
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	movs r2, #0
	movs r3, #1
	bl createHellbatElectricBeam
	movs r0, #0
	strb r0, [r5, #0x13]
	movs r0, #1
	strb r0, [r5, #0x12]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	b _080A2294
_080A2136:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080A2148
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080A2148
	b _080A22DE
_080A2148:
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	add r1, sp, #8
	str r0, [r1, #4]
	ldr r0, [r5, #0x28]
	movs r2, #1
	bl FUN_080a1538
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080A2296
_080A2162:
	ldr r1, _080A21A0 @ =0x0000A905
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A21A4 @ =0x0836B2C4
	bl SetDDP
	movs r2, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4d
	strb r2, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r0, [r5, #0x13]
	cmp r0, #1
	bne _080A21A8
	movs r0, #0xc0
	lsls r0, r0, #2
	b _080A21AA
	.align 2, 0
_080A21A0: .4byte 0x0000A905
_080A21A4: .4byte 0x0836B2C4
_080A21A8:
	ldr r0, _080A2224 @ =0xFFFFFD00
_080A21AA:
	str r0, [r5, #0x5c]
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, _080A2228 @ =0xFFFFFC00
	adds r1, r1, r2
	bl FUN_08009f6c
	str r0, [r5, #0x58]
	str r4, [r5, #0x64]
	strb r4, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A21CE:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x64]
	adds r0, r0, r1
	str r0, [r5, #0x64]
	adds r1, r0, #0
	cmp r1, #0
	bge _080A21E4
	rsbs r1, r1, #0
_080A21E4:
	movs r0, #0xa0
	lsls r0, r0, #5
	cmp r1, r0
	ble _080A2206
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080A2206
	movs r0, #1
	strb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x54
	adds r0, r5, #0
	movs r2, #0
	bl FUN_080a1594
	ldr r1, [r5, #0x5c]
	str r1, [r0, #0x5c]
_080A2206:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x13]
	cmp r0, #1
	bne _080A222C
	ldr r0, [r5, #0x54]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	bl PushoutToLeft1
	b _080A2238
	.align 2, 0
_080A2224: .4byte 0xFFFFFD00
_080A2228: .4byte 0xFFFFFC00
_080A222C:
	ldr r0, [r5, #0x54]
	ldr r2, _080A224C @ =0xFFFFFC00
	adds r0, r0, r2
	ldr r1, [r5, #0x58]
	bl PushoutToRight1
_080A2238:
	adds r1, r0, #0
	cmp r1, #0
	beq _080A22DE
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, _080A2250 @ =0xFFFFFD00
	str r0, [r5, #0x60]
	b _080A2298
	.align 2, 0
_080A224C: .4byte 0xFFFFFC00
_080A2250: .4byte 0xFFFFFD00
_080A2254:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	movs r2, #0
	ldr r0, _080A22A0 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _080A22A4 @ =0xFFFFB000
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	cmp r1, r0
	bge _080A2274
	movs r2, #1
_080A2274:
	cmp r2, #0
	beq _080A22DE
	adds r0, r1, r2
	str r0, [r5, #0x58]
	movs r0, #0xff
	str r0, [r5, #0x64]
	adds r0, r5, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
_080A2294:
	ands r0, r1
_080A2296:
	strb r0, [r5, #0xa]
_080A2298:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A22DE
	.align 2, 0
_080A22A0: .4byte gStageRun+232
_080A22A4: .4byte 0xFFFFB000
_080A22A8:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x64]
	adds r1, r5, #0
	adds r1, #0x50
	strh r0, [r1]
	ldr r0, [r5, #0x64]
	adds r1, #2
	strh r0, [r1]
	ldr r0, [r5, #0x64]
	cmp r0, #0
	ble _080A22C6
	subs r0, #0x20
	str r0, [r5, #0x64]
_080A22C6:
	ldr r0, [r5, #0x64]
	cmp r0, #0x20
	bgt _080A22DE
	ldr r1, _080A22E8 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080A22DE:
	add sp, #0x10
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A22E8: .4byte gProjectileFnTable

	thumb_func_start FUN_080a22ec
FUN_080a22ec:
	.byte 0x00, 0x22, 0x01, 0x21
	.byte 0x41, 0x73, 0x82, 0x73, 0x70, 0x47, 0x00, 0x00

	thumb_func_start FUN_080a22f8
FUN_080a22f8: @ 0x080A22F8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A2334
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A2330 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080A2446
	.align 2, 0
_080A2330: .4byte gProjectileFnTable
_080A2334:
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080A23AE
	cmp r5, #1
	bgt _080A2344
	cmp r5, #0
	beq _080A234A
	b _080A2446
_080A2344:
	cmp r5, #2
	beq _080A2438
	b _080A2446
_080A234A:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A238C @ =0x0000A905
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A2390 @ =0x0836B2C4
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4d
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _080A2398
	ldr r0, [r4, #0x54]
	ldr r1, _080A2394 @ =0xFFFFEC00
	b _080A239E
	.align 2, 0
_080A238C: .4byte 0x0000A905
_080A2390: .4byte 0x0836B2C4
_080A2394: .4byte 0xFFFFEC00
_080A2398:
	ldr r0, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #5
_080A239E:
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r0, #0
	str r0, [r4, #0x64]
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A23AE:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r0, r1
	str r1, [r4, #0x64]
	adds r0, r4, #0
	adds r0, #0xb5
	ldrb r0, [r0]
	cmp r0, #0
	bne _080A23EE
	cmp r1, #0
	bge _080A23CC
	rsbs r1, r1, #0
_080A23CC:
	movs r0, #0xa0
	lsls r0, r0, #5
	cmp r1, r0
	ble _080A23EE
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A23EE
	movs r0, #1
	strb r0, [r4, #0x13]
	adds r1, r4, #0
	adds r1, #0x54
	adds r0, r4, #0
	movs r2, #1
	bl FUN_080a1594
	ldr r1, [r4, #0x5c]
	str r1, [r0, #0x5c]
_080A23EE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _080A240A
	ldr r0, [r4, #0x54]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl PushoutToLeft1
	b _080A2416
_080A240A:
	ldr r0, [r4, #0x54]
	ldr r1, _080A2430 @ =0xFFFFFC00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl PushoutToRight1
_080A2416:
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2446
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, _080A2434 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080A2446
	.align 2, 0
_080A2430: .4byte 0xFFFFFC00
_080A2434: .4byte 0xFFFFFD00
_080A2438:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A2446:
	pop {r4, r5}
	pop {r0}
	bx r0
