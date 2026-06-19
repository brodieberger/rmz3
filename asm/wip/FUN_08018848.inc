	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x14
	lsls r0, r0, #0x18
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp, #8]
	ldr r1, _08018AF0 @ =sStagePreloadEntities
	lsrs r0, r0, #0x16
	str r0, [sp, #0xc]
	adds r0, r0, r1
	ldr r7, [r0]
	ldr r2, _08018AF4 @ =0x0202FDA1
	ldrb r0, [r2]
	cmp r0, #0xff
	beq _08018870
	b _08018A6E
_08018870:
	ldr r6, _08018AF8 @ =gStaticMotionGraphics
	ldr r0, _08018AFC @ =wStaticGraphicTilenums
	mov r8, r0
	ldrh r1, [r0]
	ldrh r0, [r6, #6]
	lsrs r0, r0, #6
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	adds r0, r6, #0
	bl LoadGraphic
	ldr r0, _08018B00 @ =gStaticMotionGraphics+12
	mov sb, r0
	ldr r2, _08018B04 @ =wStaticMotionPalIDs
	ldrh r1, [r2]
	ldrb r0, [r0, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r0, #0x80
	lsls r0, r0, #2
	adds r1, r1, r0
	mov r0, sb
	bl LoadPalette
	adds r0, r6, #0
	adds r0, #0x28
	mov r2, r8
	ldrh r1, [r2, #4]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	mov r0, sb
	adds r0, #0x28
	ldr r2, _08018B04 @ =wStaticMotionPalIDs
	ldrh r1, [r2, #4]
	ldrb r2, [r0, #7]
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	bl LoadPalette
	adds r0, r6, #0
	adds r0, #0x3c
	mov r2, r8
	ldrh r1, [r2, #6]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	mov r0, sb
	adds r0, #0x3c
	ldr r2, _08018B04 @ =wStaticMotionPalIDs
	ldrh r1, [r2, #6]
	ldrb r2, [r0, #7]
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	bl LoadPalette
	ldr r5, _08018B08 @ =0x00001054
	adds r0, r5, r6
	movs r4, #0xd1
	lsls r4, r4, #1
	mov r2, r8
	adds r1, r2, r4
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	add r5, sb
	ldr r0, _08018B04 @ =wStaticMotionPalIDs
	adds r4, r0, r4
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	ldr r0, _08018B0C @ =gSystemSavedata
	mov sl, r0
	adds r0, #0x49
	ldrb r4, [r0]
	adds r4, #0xa7
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	adds r0, r5, r6
	lsls r4, r4, #1
	mov r2, r8
	adds r1, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	add r5, sb
	ldr r0, _08018B04 @ =wStaticMotionPalIDs
	adds r4, r4, r0
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	mov r0, sl
	adds r0, #0x4a
	ldrb r4, [r0]
	adds r4, #0xaa
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	adds r0, r5, r6
	lsls r4, r4, #1
	mov r2, r8
	adds r1, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	add r5, sb
	ldr r0, _08018B04 @ =wStaticMotionPalIDs
	adds r4, r4, r0
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	mov r0, sl
	adds r0, #0x4c
	ldrb r4, [r0]
	adds r4, #0xad
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	adds r0, r5, r6
	lsls r4, r4, #1
	mov r2, r8
	adds r1, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	add r5, sb
	ldr r0, _08018B04 @ =wStaticMotionPalIDs
	adds r4, r4, r0
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	mov r0, sl
	adds r0, #0x4b
	ldrb r4, [r0]
	adds r4, #0xb0
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	adds r6, r5, r6
	lsls r4, r4, #1
	add r8, r4
	mov r0, r8
	ldrh r1, [r0]
	ldrh r0, [r6, #6]
	lsrs r0, r0, #6
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	adds r0, r6, #0
	bl LoadGraphic
	add r5, sb
	ldr r0, _08018B04 @ =wStaticMotionPalIDs
	adds r4, r4, r0
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	movs r0, #1
	rsbs r0, r0, #0
	ldr r1, _08018B10 @ =0x03002E60
	str r0, [sp]
	ldr r2, _08018B14 @ =0x01000008
	mov r0, sp
	bl CpuFastSet
	movs r0, #0xfe
	ldr r1, _08018AF4 @ =0x0202FDA1
	strb r0, [r1]
_08018A6E:
	ldr r2, _08018B18 @ =gSpawnManager
	ldr r1, _08018B1C @ =0x0000020E
	adds r0, r2, r1
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	beq _08018A82
	b _08018BDE
_08018A82:
	ldr r2, _08018AF4 @ =0x0202FDA1
	ldrb r0, [r2]
	ldr r5, [sp, #0xc]
	cmp r0, #0xfe
	bne _08018AB2
	ldrb r0, [r7]
	cmp r0, #0xff
	beq _08018AB2
	ldr r3, _08018AFC @ =wStaticGraphicTilenums
	ldr r2, _08018B04 @ =wStaticMotionPalIDs
_08018A96:
	ldrb r0, [r7]
	lsls r0, r0, #1
	adds r0, r0, r3
	ldrh r1, [r7, #2]
	strh r1, [r0]
	ldrb r0, [r7]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r1, [r7, #4]
	strh r1, [r0]
	adds r7, #8
	ldrb r0, [r7]
	cmp r0, #0xff
	bne _08018A96
_08018AB2:
	ldr r0, _08018B20 @ =0x0000022A
	adds r1, r4, r0
	movs r0, #0
	strh r0, [r1]
	ldr r2, _08018AF0 @ =sStagePreloadEntities
	adds r0, r5, r2
	ldr r7, [r0]
	ldrb r0, [r7]
	cmp r0, #0xff
	bne _08018AC8
	b _08018BD4
_08018AC8:
	movs r6, #1
	adds r3, r1, #0
	ldr r0, _08018AFC @ =wStaticGraphicTilenums
	mov sb, r0
	ldr r1, _08018B04 @ =wStaticMotionPalIDs
	mov r8, r1
_08018AD4:
	ldrb r0, [r7, #1]
	ldr r2, [sp, #8]
	asrs r0, r2
	ands r0, r6
	cmp r0, #0
	beq _08018BC8
	ldr r1, _08018B24 @ =0x00000227
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _08018B28
	ldrb r1, [r7, #5]
	movs r0, #2
	b _08018B2C
	.align 2, 0
_08018AF0: .4byte sStagePreloadEntities
_08018AF4: .4byte 0x0202FDA1
_08018AF8: .4byte gStaticMotionGraphics
_08018AFC: .4byte wStaticGraphicTilenums
_08018B00: .4byte gStaticMotionGraphics+12
_08018B04: .4byte wStaticMotionPalIDs
_08018B08: .4byte 0x00001054
_08018B0C: .4byte gSystemSavedata
_08018B10: .4byte gPaletteManager+(464*2)
_08018B14: .4byte 0x01000008
_08018B18: .4byte gSpawnManager
_08018B1C: .4byte 0x0000020E
_08018B20: .4byte 0x0000022A
_08018B24: .4byte 0x00000227
_08018B28:
	ldrb r1, [r7, #5]
	adds r0, r6, #0
_08018B2C:
	ands r0, r1
	cmp r0, #0
	beq _08018BC8
	ldr r2, _08018B44 @ =0x00000229
	adds r0, r4, r2
	ldrb r0, [r0]
	cmp r0, #0
	beq _08018B48
	ldrb r1, [r7, #6]
	movs r0, #2
	b _08018B4C
	.align 2, 0
_08018B44: .4byte 0x00000229
_08018B48:
	ldrb r1, [r7, #6]
	adds r0, r6, #0
_08018B4C:
	ands r0, r1
	cmp r0, #0
	beq _08018BC8
	ldrb r0, [r7, #7]
	cmp r0, #0
	beq _08018B64
	adds r0, r6, #0
	ldrb r1, [r7, #4]
	lsls r0, r1
	ldrh r1, [r3]
	orrs r0, r1
	b _08018B6E
_08018B64:
	adds r1, r6, #0
	ldrb r2, [r7, #4]
	lsls r1, r2
	ldrh r0, [r3]
	bics r0, r1
_08018B6E:
	strh r0, [r3]
	ldrb r0, [r7]
	lsls r0, r0, #1
	add r0, sb
	ldrh r1, [r7, #2]
	strh r1, [r0]
	ldrb r0, [r7]
	lsls r0, r0, #1
	add r0, r8
	ldrb r1, [r7, #4]
	strh r1, [r0]
	ldrb r4, [r7]
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	ldr r1, _08018BF0 @ =gStaticMotionGraphics
	adds r0, r5, r1
	lsls r4, r4, #1
	mov r2, sb
	adds r1, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	str r3, [sp, #0x10]
	bl LoadGraphic
	ldr r0, _08018BF4 @ =gStaticMotionGraphics+12
	adds r5, r5, r0
	add r4, r8
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	ldr r3, [sp, #0x10]
_08018BC8:
	adds r7, #8
	ldrb r0, [r7]
	ldr r4, _08018BF8 @ =gSpawnManager
	cmp r0, #0xff
	beq _08018BD4
	b _08018AD4
_08018BD4:
	ldr r1, _08018BFC @ =0x00000211
	adds r0, r4, r1
	mov r2, sp
	ldrb r2, [r2, #8]
	strb r2, [r0]
_08018BDE:
	add sp, #0x14
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08018BF0: .4byte gStaticMotionGraphics
_08018BF4: .4byte gStaticMotionGraphics+12
_08018BF8: .4byte gSpawnManager
_08018BFC: .4byte 0x00000211
