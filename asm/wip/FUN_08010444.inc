	push {r4, r5, r6, lr}
	ldr r2, _080104BC @ =gOverworld
	ldr r1, _080104C0 @ =0x000007D4
	adds r0, r2, r1
	ldrh r1, [r0]
	lsrs r0, r1, #8
	cmp r0, #8
	bne _080104B6
	movs r0, #0xff
	ands r0, r1
	cmp r0, #2
	bne _080104B6
	movs r4, #0
	ldr r1, _080104C4 @ =0x0002D035
	adds r0, r2, r1
	ldr r1, _080104C8 @ =0x08340128
	ldrb r0, [r0]
	ldrb r2, [r1]
	cmp r0, r2
	bls _08010480
	adds r3, r1, #0
	adds r2, r0, #0
_08010470:
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	lsls r0, r4, #1
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r2, r0
	bhi _08010470
_08010480:
	ldr r6, _080104CC @ =gStageTilesetOffsets+(18*4)
	lsls r4, r4, #1
	adds r0, r1, #1
	adds r4, r4, r0
	ldrb r0, [r4]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r5, _080104D0 @ =0x08705150
	adds r1, r1, r5
	ldr r0, [r6]
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #7
	bl RequestGraphicTransfer
	ldrb r0, [r4]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r5
	ldr r0, [r6]
	adds r0, r0, r1
	adds r0, #0xc
	movs r1, #0
	bl LoadPalette
_080104B6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080104BC: .4byte gOverworld
_080104C0: .4byte 0x000007D4
_080104C4: .4byte 0x0002D035
_080104C8: .4byte u8_ARRAY_ARRAY_08340128
_080104CC: .4byte gStageTilesetOffsets+(18*4)
_080104D0: .4byte 0x08705150
