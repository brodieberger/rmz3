	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createGoldOmega1Laser
createGoldOmega1Laser: @ 0x080AC388
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	adds r6, r2, #0
	adds r7, r3, #0
	lsls r1, r1, #0x18
	lsrs r4, r1, #0x18
	ldr r0, _080AC3E0 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080AC3D6
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080AC3E4 @ =gProjectileFnTable
	movs r1, #0x21
	strb r1, [r3, #9]
	adds r0, #0x84
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb4
	strb r4, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	str r6, [r0]
	str r7, [r3, #0x28]
_080AC3D6:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080AC3E0: .4byte gProjectileHeaderPtr
_080AC3E4: .4byte gProjectileFnTable

	thumb_func_start FUN_080ac3e8
FUN_080ac3e8: @ 0x080AC3E8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	lsls r2, r2, #0x10
	lsrs r6, r2, #0x10
	ldr r0, _080AC440 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080AC438
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080AC444 @ =gProjectileFnTable
	movs r1, #0x21
	strb r1, [r3, #9]
	adds r0, #0x84
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x11]
	adds r0, r3, #0
	adds r0, #0xbc
	str r6, [r0]
_080AC438:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080AC440: .4byte gProjectileHeaderPtr
_080AC444: .4byte gProjectileFnTable

	thumb_func_start OmegaGoldProjectile_Init
OmegaGoldProjectile_Init: @ 0x080AC448
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r5, [r6, #0x10]
	cmp r5, #0
	bne _080AC4A0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AC498 @ =0x0836C644
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r0, r6, #0
	adds r0, #0x25
	strb r5, [r0]
	ldr r1, _080AC49C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r5, [r6, #0xd]
	b _080AC4E8
	.align 2, 0
_080AC498: .4byte 0x0836C644
_080AC49C: .4byte gProjectileFnTable
_080AC4A0:
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AC4FC @ =0x0836C614
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _080AC500 @ =0xFFFFFF00
	str r0, [r6, #0x60]
	ldr r1, _080AC504 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #2
	strb r0, [r6, #0xd]
_080AC4E8:
	strb r5, [r6, #0xe]
	strb r5, [r6, #0xf]
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	bl OmegaGoldProjectile_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AC4FC: .4byte 0x0836C614
_080AC500: .4byte 0xFFFFFF00
_080AC504: .4byte gProjectileFnTable

	thumb_func_start OmegaGoldProjectile_Update
OmegaGoldProjectile_Update: @ 0x080AC508
	push {lr}
	ldr r2, _080AC51C @ =0x0836C608
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080AC51C: .4byte 0x0836C608

	thumb_func_start OmegaGoldProjectile_Die
OmegaGoldProjectile_Die: @ 0x080AC520
	adds r2, r0, #0
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0
	strb r0, [r2, #0xa]
	adds r0, r2, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080AC558 @ =gProjectileFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
	bx lr
	.align 2, 0
_080AC558: .4byte gProjectileFnTable

	thumb_func_start doGoldOmega1Laser1
doGoldOmega1Laser1: @ 0x080AC55C
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080AC58C
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080AC588 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080AC5D4
	.align 2, 0
_080AC588: .4byte gProjectileFnTable
_080AC58C:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080AC598
	cmp r0, #1
	beq _080AC5A6
	b _080AC5BA
_080AC598:
	ldr r1, _080AC5DC @ =0x00000A06
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080AC5A6:
	ldr r1, [r4, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	ldr r1, _080AC5E0 @ =0xFFFF9A00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateEntityAnim
_080AC5BA:
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	cmp r0, #0
	beq _080AC5CC
	subs r0, #1
	str r0, [r1]
	cmp r0, #0
	bne _080AC5D4
_080AC5CC:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080AC5D4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AC5DC: .4byte 0x00000A06
_080AC5E0: .4byte 0xFFFF9A00

	thumb_func_start doGoldOmega1Laser2
doGoldOmega1Laser2: @ 0x080AC5E4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bhi _080AC5FC
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AC620
_080AC5FC:
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080AC61C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080AC6EC
	.align 2, 0
_080AC61C: .4byte gProjectileFnTable
_080AC620:
	ldrb r2, [r5, #0xe]
	cmp r2, #0
	beq _080AC62C
	cmp r2, #1
	beq _080AC696
	b _080AC6EC
_080AC62C:
	adds r4, r5, #0
	adds r4, #0xb8
	ldr r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #6
	lsrs r0, r0, #8
	str r0, [r4]
	strb r2, [r5, #0x13]
	ldr r1, _080AC6F4 @ =0x00000A07
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080AC6F8 @ =0x0836C65C
	bl SetDDP
	ldr r3, _080AC6FC @ =gSineTable
	adds r2, r5, #0
	adds r2, #0xb4
	ldrb r0, [r2]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r6, #0
	ldrsh r1, [r0, r6]
	ldr r0, [r4]
	muls r0, r1, r0
	lsrs r0, r0, #8
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	ldrb r0, [r2]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r4]
	muls r0, r1, r0
	lsrs r0, r0, #8
	str r0, [r5, #0x60]
	adds r1, r5, #0
	adds r1, #0xb5
	movs r0, #1
	strb r0, [r1]
	movs r0, #0x96
	lsls r0, r0, #1
	bl PlaySound
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AC696:
	ldrb r0, [r5, #0x13]
	adds r1, r0, #1
	strb r1, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	bne _080AC6B2
	adds r0, r5, #0
	adds r0, #0x54
	movs r1, #0
	bl FUN_080c1b98
_080AC6B2:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x60]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r2, #0
	beq _080AC6E6
	adds r1, r5, #0
	adds r1, #0xb5
	ldrb r0, [r1]
	cmp r0, #0
	beq _080AC6E6
	movs r0, #0
	strb r0, [r1]
	ldr r0, [r5, #0x58]
	adds r0, r0, r2
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x60]
	rsbs r0, r0, #0
	str r0, [r5, #0x60]
_080AC6E6:
	adds r0, r5, #0
	bl UpdateEntityAnim
_080AC6EC:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AC6F4: .4byte 0x00000A07
_080AC6F8: .4byte 0x0836C65C
_080AC6FC: .4byte gSineTable

	thumb_func_start FUN_080ac700
FUN_080ac700: @ 0x080AC700
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r2, r7, #0
	adds r2, #0x8c
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080AC736
	movs r1, #0
	str r1, [r2]
	adds r0, r7, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #1
	bl CreateSmoke
	b _080AC7E2
_080AC736:
	ldrb r0, [r7, #0xe]
	cmp r0, #0
	beq _080AC742
	cmp r0, #1
	beq _080AC79C
	b _080AC7F4
_080AC742:
	ldr r2, _080AC7FC @ =0x0836C6F4
	ldrb r0, [r7, #0x11]
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r2, [r0]
	ldr r3, _080AC800 @ =RNG_0202f388
	ldr r0, [r3]
	ldr r6, _080AC804 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r6, r1
	ldr r5, _080AC808 @ =0x00269EC3
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r4, r1, #1
	str r4, [r3]
	lsrs r1, r1, #0x11
	movs r0, #0x1f
	ands r1, r0
	ldr r0, [r2, #4]
	subs r0, r0, r1
	str r0, [r7, #0x60]
	ldr r2, [r2]
	subs r2, #0x20
	adds r0, r4, #0
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	movs r1, #0x3f
	ands r0, r1
	adds r2, r2, r0
	str r2, [r7, #0x5c]
	ldr r1, _080AC80C @ =0x00000C01
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x3c
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080AC79C:
	ldrb r0, [r7, #0x12]
	cmp r0, #0x32
	bne _080AC7AC
	adds r0, r7, #0
	adds r0, #0x74
	ldr r1, _080AC810 @ =0x0836C644
	bl SetDDP
_080AC7AC:
	ldr r0, [r7, #0x60]
	adds r0, #0x20
	str r0, [r7, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080AC7BC
	str r1, [r7, #0x60]
_080AC7BC:
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	adds r0, r7, #0
	bl UpdateEntityAnim
	ldrb r0, [r7, #0x12]
	cmp r0, #0
	beq _080AC7E2
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AC7F4
_080AC7E2:
	ldr r1, _080AC814 @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r7, #0x14]
_080AC7F4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AC7FC: .4byte 0x0836C6F4
_080AC800: .4byte RNG_0202f388
_080AC804: .4byte 0x000343FD
_080AC808: .4byte 0x00269EC3
_080AC80C: .4byte 0x00000C01
_080AC810: .4byte 0x0836C644
_080AC814: .4byte gProjectileFnTable
