	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080aa5e8
FUN_080aa5e8: @ 0x080AA5E8
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	adds r7, r3, #0
	ldr r0, _080AA630 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080AA62A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080AA634 @ =gProjectileFnTable
	movs r0, #0x1e
	strb r0, [r3, #9]
	ldr r0, [r1, #0x78]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
	str r6, [r3, #0x5c]
	str r7, [r3, #0x60]
_080AA62A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AA630: .4byte gProjectileHeaderPtr
_080AA634: .4byte gProjectileFnTable

	thumb_func_start nop_080aa638
nop_080aa638: @ 0x080AA638
	bx lr
	.align 2, 0

	thumb_func_start Projectile30_Init
Projectile30_Init: @ 0x080AA63C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080AA69C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080AA6A0 @ =0x0836C304
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _080AA6A4 @ =0x0836C2EC
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080AA6A8 @ =nop_080aa638
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile30_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AA69C: .4byte gProjectileFnTable
_080AA6A0: .4byte 0x0836C304
_080AA6A4: .4byte 0x0836C2EC
_080AA6A8: .4byte nop_080aa638

	thumb_func_start Projectile30_Update
Projectile30_Update: @ 0x080AA6AC
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080AA6D8 @ =0x0836C2E4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080AA6DC @ =0x0836C2E8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AA6D8: .4byte 0x0836C2E4
_080AA6DC: .4byte 0x0836C2E8

	thumb_func_start Projectile30_Die
Projectile30_Die:
	.byte 0x02, 0x1C, 0x8C, 0x30, 0x00, 0x21, 0x01, 0x60, 0x04, 0x30, 0x01, 0x60, 0x04, 0x30, 0x01, 0x70
	.byte 0x91, 0x7A, 0xFB, 0x20, 0x08, 0x40, 0x90, 0x72, 0x04, 0x49, 0x50, 0x7A, 0x80, 0x00, 0x40, 0x18
	.byte 0x04, 0x21, 0xD1, 0x60, 0x00, 0x68, 0x00, 0x69, 0x50, 0x61, 0x70, 0x47, 0x0C, 0xA9, 0x36, 0x08

	thumb_func_start FUN_080aa710
FUN_080aa710:
	bx lr
	.align 2, 0

	thumb_func_start FUN_080aa714
FUN_080aa714: @ 0x080AA714
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080AA724
	cmp r0, #1
	beq _080AA728
	b _080AA798
_080AA724:
	movs r0, #1
	strb r0, [r4, #0xe]
_080AA728:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x20
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _080AA746
	str r0, [r4, #0x60]
_080AA746:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x18
	adds r0, #0x10
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x1d
	ldr r1, _080AA7A0 @ =0x0836C306
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA798
	ldr r1, _080AA7A4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080AA798:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AA7A0: .4byte 0x0836C306
_080AA7A4: .4byte gProjectileFnTable
