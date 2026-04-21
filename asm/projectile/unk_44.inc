	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b1698
FUN_080b1698: @ 0x080B1698
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r7, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	ldr r0, _080B16E8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B16E0
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B16EC @ =gProjectileFnTable
	movs r1, #0x2c
	strb r1, [r3, #9]
	adds r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
	strb r5, [r3, #0x12]
	strb r4, [r3, #0x13]
_080B16E0:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080B16E8: .4byte gProjectileHeaderPtr
_080B16EC: .4byte gProjectileFnTable
_080B16F0:
	.byte 0x70, 0x47, 0x00, 0x00

	thumb_func_start FUN_080b16f4
FUN_080b16f4: @ 0x080B16F4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080B1754 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080B1758 @ =0x0836D7B4
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
	ldr r1, _080B175C @ =0x0836D79C
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080B1760 @ =0x080B16F1
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl FUN_080b1764
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B1754: .4byte gProjectileFnTable
_080B1758: .4byte 0x0836D7B4
_080B175C: .4byte 0x0836D79C
_080B1760: .4byte 0x080B16F1

	thumb_func_start FUN_080b1764
FUN_080b1764: @ 0x080B1764
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080B1790 @ =0x0836D794
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080B1794 @ =0x0836D798
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
_080B1790: .4byte 0x0836D794
_080B1794: .4byte 0x0836D798

	thumb_func_start FUN_080b1798
FUN_080b1798: @ 0x080B1798
	push {r4, lr}
	adds r4, r0, #0
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
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080B17D4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B17D4: .4byte gProjectileFnTable

	thumb_func_start FUN_080b17d8
FUN_080b17d8:
  bx lr
	.align 2, 0

	thumb_func_start FUN_080b17dc
FUN_080b17dc: @ 0x080B17DC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B17EC
	cmp r0, #1
	beq _080B1834
	b _080B18C2
_080B17EC:
	movs r0, #0x40
	str r0, [r4, #0x64]
	movs r0, #0xa0
	lsls r0, r0, #3
	bl Sqrt
	ldr r1, [r4, #0x64]
	rsbs r1, r1, #0
	lsls r0, r0, #0x10
	asrs r3, r0, #0x10
	adds r2, r1, #0
	muls r2, r3, r2
	str r2, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080B1812
	str r1, [r4, #0x64]
	rsbs r0, r2, #0
	str r0, [r4, #0x5c]
_080B1812:
	lsls r0, r3, #1
	str r0, [r4, #0x68]
	movs r2, #0xa0
	ldrb r1, [r4, #0x13]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #6
	subs r2, r2, r0
	str r2, [r4, #0x60]
	movs r1, #0xd7
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B1834:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x68]
	cmp r0, #0
	beq _080B184C
	subs r0, #1
	str r0, [r4, #0x68]
	ldr r0, [r4, #0x64]
	adds r0, r1, r0
	str r0, [r4, #0x5c]
_080B184C:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _080B1880
	ldr r0, _080B1878 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080B187C @ =0xFFFF2800
	adds r0, r0, r1
	ldr r1, [r4, #0x54]
	cmp r1, r0
	bge _080B18C2
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	b _080B1894
	.align 2, 0
_080B1878: .4byte gStageRun+232
_080B187C: .4byte 0xFFFF2800
_080B1880:
	ldr r0, _080B18C8 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080B18CC @ =0x0000D7FF
	adds r0, r0, r1
	ldr r1, [r4, #0x54]
	cmp r1, r0
	ble _080B18C2
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080B1894:
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080B18D0 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080B18C2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B18C8: .4byte gStageRun+232
_080B18CC: .4byte 0x0000D7FF
_080B18D0: .4byte gProjectileFnTable
