	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	str r0, [sp]
	ldr r4, _08017D2C @ =gSpawnManager
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r0, [r0]
	str r0, [sp, #4]
	ldr r1, _08017D30 @ =gAreaCheckers
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r0, [sp]
	bl _call_via_r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov sl, r0
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r4, r2
	ldr r0, [r0]
	mov r8, r0
	movs r3, #0x86
	lsls r3, r3, #2
	adds r0, r4, r3
	ldr r0, [r0]
	mov sb, r0
	ldr r2, _08017D34 @ =gCurStory
	ldrb r1, [r2, #4]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08017CA8
	b _08017DA8
_08017CA8:
	ldrb r1, [r2, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _08017DA8
	movs r0, #0x8a
	lsls r0, r0, #2
	adds r1, r4, r0
	ldrb r0, [r1]
	cmp r0, #0
	beq _08017CC0
	b _08017EC2
_08017CC0:
	movs r0, #1
	strb r0, [r1]
	movs r2, #0
	ldr r0, _08017D38 @ =gSystemSavedata
	ldr r1, [r0, #0x40]
	ldr r0, _08017D3C @ =0x000032DA
	cmp r1, r0
	beq _08017CD6
	rsbs r0, r1, #0
	orrs r0, r1
	lsrs r2, r0, #0x1f
_08017CD6:
	ldr r1, _08017D40 @ =0x00000229
	adds r5, r4, r1
	strb r2, [r5]
	cmp r2, #0
	beq _08017CE8
	ldr r0, [sp, #4]
	mov r1, sl
	bl FUN_08018d10
_08017CE8:
	movs r2, #0x81
	lsls r2, r2, #2
	adds r0, r4, r2
	ldr r4, [r0]
	ldrb r0, [r5]
	cmp r0, #0
	bne _08017CF8
	b _08017EC2
_08017CF8:
	cmp r4, #0
	beq _08017D8A
	movs r7, #0
_08017CFE:
	ldr r6, [r4]
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _08017D7C
	movs r3, #8
	ldrsh r0, [r4, r3]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #7]
	cmp r0, #0
	beq _08017D7C
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _08017D44
	adds r0, r1, #0
	bl DeleteStageEntity
	str r7, [r4, #4]
	b _08017D7C
	.align 2, 0
_08017D2C: .4byte gSpawnManager
_08017D30: .4byte gAreaCheckers
_08017D34: .4byte gCurStory
_08017D38: .4byte gSystemSavedata
_08017D3C: .4byte 0x000032DA
_08017D40: .4byte 0x00000229
_08017D44:
	adds r0, r1, #0
	bl DeleteStageEntity
	movs r1, #8
	ldrsh r0, [r4, r1]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r1, [r0, #7]
	adds r1, #0x1d
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	movs r0, #3
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	beq _08017D7A
	strb r7, [r2, #0x10]
	strb r7, [r2, #0x11]
	ldr r0, [r4, #4]
	ldr r1, [r0, #0x54]
	str r1, [r2, #0x54]
	ldr r0, [r0, #0x58]
	str r0, [r2, #0x58]
_08017D7A:
	str r2, [r4, #4]
_08017D7C:
	adds r4, r6, #0
	ldrb r0, [r5]
	cmp r0, #0
	bne _08017D86
	b _08017EC2
_08017D86:
	cmp r4, #0
	bne _08017CFE
_08017D8A:
	ldr r0, _08017DA0 @ =gSpawnManager
	ldr r2, _08017DA4 @ =0x00000229
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #0
	bne _08017D98
	b _08017EC2
_08017D98:
	bl RemoveZ3EnemyChildEntityForSwapMMBN4Virus
	b _08017EC2
	.align 2, 0
_08017DA0: .4byte gSpawnManager
_08017DA4: .4byte 0x00000229
_08017DA8:
	ldr r0, _08017DCC @ =gSpawnManager
	movs r3, #0x8a
	lsls r3, r3, #2
	adds r2, r0, r3
	ldrb r1, [r2]
	cmp r1, #0
	bne _08017DB8
	b _08017EC2
_08017DB8:
	movs r0, #0
	strb r0, [r2]
	ldr r1, _08017DCC @ =gSpawnManager
	movs r2, #0x81
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r4, [r0]
	adds r3, #1
	adds r0, r1, r3
	b _08017E9C
	.align 2, 0
_08017DCC: .4byte gSpawnManager
_08017DD0:
	ldr r6, [r4]
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _08017E94
	movs r2, #8
	ldrsh r0, [r4, r2]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #7]
	cmp r0, #0
	beq _08017E94
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _08017DFE
	adds r0, r1, #0
	bl DeleteStageEntity
	movs r0, #0
	str r0, [r4, #4]
	b _08017E94
_08017DFE:
	adds r0, r1, #0
	bl DeleteStageEntity
	movs r3, #8
	ldrsh r0, [r4, r3]
	lsls r0, r0, #3
	add r0, sb
	ldrh r1, [r0, #6]
	lsls r1, r1, #3
	add r1, r8
	ldrb r0, [r1, #1]
	ldrb r1, [r1, #2]
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	bne _08017E28
	adds r0, r4, #0
	bl ReleaseStageEntity
	b _08017E94
_08017E28:
	movs r1, #8
	ldrsh r0, [r4, r1]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #3]
	strb r0, [r2, #0x10]
	movs r3, #8
	ldrsh r0, [r4, r3]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #4]
	strb r0, [r2, #0x11]
	ldr r0, _08017E80 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _08017E88
	movs r1, #8
	ldrsh r0, [r4, r1]
	lsls r0, r0, #3
	add r0, sb
	ldr r0, [r0]
	lsls r0, r0, #0xc
	movs r3, #0x80
	lsls r3, r3, #4
	adds r0, r0, r3
	str r0, [r2, #0x54]
	movs r1, #8
	ldrsh r0, [r4, r1]
	lsls r0, r0, #3
	add r0, sb
	movs r3, #4
	ldrsh r0, [r0, r3]
	lsls r0, r0, #0xc
	ldr r1, _08017E84 @ =0x000007FF
	adds r0, r0, r1
	b _08017E90
	.align 2, 0
_08017E80: .4byte gCurStory
_08017E84: .4byte 0x000007FF
_08017E88:
	ldr r0, [r4, #4]
	ldr r1, [r0, #0x54]
	str r1, [r2, #0x54]
	ldr r0, [r0, #0x58]
_08017E90:
	str r0, [r2, #0x58]
	str r2, [r4, #4]
_08017E94:
	adds r4, r6, #0
	ldr r0, _08017FA8 @ =gSpawnManager
	ldr r2, _08017FAC @ =0x00000229
	adds r0, r0, r2
_08017E9C:
	ldrb r0, [r0]
	cmp r0, #0
	beq _08017EC2
	cmp r4, #0
	bne _08017DD0
	ldr r0, _08017FA8 @ =gSpawnManager
	ldr r3, _08017FAC @ =0x00000229
	adds r4, r0, r3
	ldrb r0, [r4]
	cmp r0, #0
	beq _08017EC2
	bl RemoveMMBN4Entities
	movs r0, #0
	strb r0, [r4]
	ldr r0, [sp, #4]
	mov r1, sl
	bl FUN_08018848
_08017EC2:
	ldr r2, _08017FB0 @ =gCurStory
	ldrb r1, [r2, #8]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08017F4C
	ldr r1, _08017FA8 @ =gSpawnManager
	ldr r3, _08017FB4 @ =0x00000226
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08017F4C
	movs r2, #0x81
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r4, [r0]
	cmp r4, #0
	beq _08017F40
	adds r7, r1, #0
_08017EE8:
	ldr r6, [r4]
	ldr r0, [r4, #4]
	adds r5, r0, #0
	cmp r5, #0
	beq _08017F3A
	movs r3, #8
	ldrsh r0, [r4, r3]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r1, [r0, #5]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _08017F3A
	ldrh r1, [r4, #0xa]
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _08017F2E
	ldrh r1, [r4, #8]
	lsls r2, r1, #0x10
	asrs r2, r2, #0x15
	lsls r2, r2, #2
	adds r2, r2, r7
	movs r0, #0x1f
	ands r0, r1
	adds r1, r3, #0
	lsls r1, r0
	ldr r0, [r2]
	orrs r0, r1
	str r0, [r2]
_08017F2E:
	adds r0, r5, #0
	bl DeleteStageEntity
	adds r0, r4, #0
	bl ReleaseStageEntity
_08017F3A:
	adds r4, r6, #0
	cmp r4, #0
	bne _08017EE8
_08017F40:
	ldr r2, _08017FA8 @ =gSpawnManager
	ldr r0, _08017FB4 @ =0x00000226
	adds r1, r2, r0
	movs r0, #1
	strb r0, [r1]
	ldr r2, _08017FB0 @ =gCurStory
_08017F4C:
	ldrb r1, [r2, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _08018002
	ldr r1, _08017FA8 @ =gSpawnManager
	ldr r2, _08017FB8 @ =0x00000227
	adds r0, r1, r2
	ldrb r0, [r0]
	cmp r0, #0
	bne _08018002
	ldr r0, [sp, #4]
	mov r1, sl
	bl FUN_08018c00
	ldr r3, _08017FA8 @ =gSpawnManager
	movs r1, #0x81
	lsls r1, r1, #2
	adds r0, r3, r1
	ldr r4, [r0]
	cmp r4, #0
	beq _08017FF8
	movs r5, #0
_08017F7A:
	ldr r6, [r4]
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _08017FF2
	movs r2, #8
	ldrsh r0, [r4, r2]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #6]
	cmp r0, #0
	beq _08017FF2
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _08017FBC
	adds r0, r1, #0
	bl DeleteStageEntity
	str r5, [r4, #4]
	b _08017FF2
	.align 2, 0
_08017FA8: .4byte gSpawnManager
_08017FAC: .4byte 0x00000229
_08017FB0: .4byte gCurStory
_08017FB4: .4byte 0x00000226
_08017FB8: .4byte 0x00000227
_08017FBC:
	adds r0, r1, #0
	bl DeleteStageEntity
	movs r0, #3
	movs r1, #0x30
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	beq _08017FF0
	movs r3, #8
	ldrsh r0, [r4, r3]
	lsls r0, r0, #3
	add r0, sb
	ldrh r0, [r0, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #6]
	subs r0, #1
	strb r0, [r2, #0x10]
	strb r5, [r2, #0x11]
	ldr r1, [r4, #4]
	ldr r0, [r1, #0x54]
	str r0, [r2, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r2, #0x58]
_08017FF0:
	str r2, [r4, #4]
_08017FF2:
	adds r4, r6, #0
	cmp r4, #0
	bne _08017F7A
_08017FF8:
	ldr r0, _0801815C @ =gSpawnManager
	ldr r1, _08018160 @ =0x00000227
	adds r0, r0, r1
	movs r1, #1
	strb r1, [r0]
_08018002:
	ldr r4, _0801815C @ =gSpawnManager
	ldr r2, _08018164 @ =0x00000211
	adds r0, r4, r2
	ldrb r0, [r0]
	cmp r0, sl
	beq _08018016
	ldr r0, [sp, #4]
	mov r1, sl
	bl FUN_08018848
_08018016:
	ldr r3, [sp]
	ldr r0, [r3]
	asrs r0, r0, #0xc
	mov sl, r0
	ldr r0, [r3, #4]
	asrs r0, r0, #0xc
	str r0, [sp, #8]
	movs r1, #0x89
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrh r7, [r0]
	mov r1, sl
	subs r1, #0xc
	lsls r0, r7, #3
	mov r2, sb
	adds r3, r0, r2
	ldr r0, [r3]
	cmp r1, r0
	bge _08018056
	adds r4, r1, #0
	adds r2, r4, #0
	adds r1, r3, #0
_08018042:
	subs r1, #8
	subs r7, #1
	ldr r0, [r1]
	cmp r2, r0
	blt _08018042
	lsls r0, r7, #3
	add r0, sb
	ldr r0, [r0]
	cmp r4, r0
	blt _08018066
_08018056:
	adds r7, #1
	mov r0, sl
	subs r0, #0xc
	lsls r1, r7, #3
	add r1, sb
	ldr r1, [r1]
	cmp r0, r1
	bge _08018056
_08018066:
	ldr r3, _0801815C @ =gSpawnManager
	movs r1, #0x89
	lsls r1, r1, #2
	adds r0, r3, r1
	strh r7, [r0]
	ldr r2, _08018168 @ =0x0000020E
	adds r0, r3, r2
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08018080
	b _0801835A
_08018080:
	lsls r0, r7, #3
	mov r3, sb
	adds r1, r0, r3
	ldr r0, [r1]
	mov r2, sl
	adds r2, #0xc
	str r2, [sp, #0xc]
	cmp r2, r0
	bgt _08018094
	b _0801821A
_08018094:
	adds r5, r1, #0
_08018096:
	movs r3, #4
	ldrsh r4, [r5, r3]
	ldr r1, [sp, #8]
	subs r0, r4, r1
	adds r0, #0xa
	cmp r0, #0x13
	bls _080180A6
	b _0801820C
_080180A6:
	ldr r6, _0801815C @ =gSpawnManager
	asrs r3, r7, #5
	lsls r2, r3, #2
	adds r2, r2, r6
	movs r1, #0x1f
	ands r1, r7
	movs r0, #1
	mov ip, r0
	lsls r0, r1
	ldr r1, [r2]
	ands r1, r0
	mov sl, r3
	cmp r1, #0
	bne _080180C4
	b _0801820C
_080180C4:
	lsls r1, r4, #0xc
	movs r2, #0x87
	lsls r2, r2, #2
	adds r0, r6, r2
	ldr r0, [r0]
	cmp r1, r0
	bge _080180D4
	b _0801820C
_080180D4:
	movs r3, #0x88
	lsls r3, r3, #2
	adds r0, r6, r3
	ldr r0, [r0]
	cmp r1, r0
	ble _080180E2
	b _0801820C
_080180E2:
	ldr r1, _0801816C @ =0x00000226
	adds r0, r6, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _080180FE
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r1, [r0, #5]
	mov r0, ip
	ands r0, r1
	cmp r0, #0
	beq _080180FE
	b _0801820C
_080180FE:
	movs r2, #0x83
	lsls r2, r2, #2
	adds r0, r6, r2
	ldrh r0, [r0]
	cmp r0, #1
	bne _0801811A
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r1, [r0, #5]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0801820C
_0801811A:
	bl AllocStageEntity
	adds r4, r0, #0
	cmp r4, #0
	beq _0801820C
	ldr r3, _08018160 @ =0x00000227
	adds r0, r6, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08018170
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #6]
	cmp r0, #0
	beq _08018170
	movs r0, #3
	movs r1, #0x30
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	beq _080181B4
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #6]
	subs r0, #1
	movs r1, #0
	strb r0, [r2, #0x10]
	strb r1, [r2, #0x11]
	b _080181D0
	.align 2, 0
_0801815C: .4byte gSpawnManager
_08018160: .4byte 0x00000227
_08018164: .4byte 0x00000211
_08018168: .4byte 0x0000020E
_0801816C: .4byte 0x00000226
_08018170:
	ldr r1, _0801819C @ =gSpawnManager+0x229
	ldrb r0, [r1]
	cmp r0, #0
	beq _080181A0
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r1, [r0, #7]
	cmp r1, #0
	beq _080181A0
	adds r1, #0x1d
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	movs r0, #3
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	beq _080181B4
	movs r0, #0
	strb r0, [r2, #0x10]
	b _080181CE
	.align 2, 0
_0801819C: .4byte gSpawnManager+0x229 @ gSpawnManager.mmbn4EnemiesEnabled
_080181A0:
	ldrh r1, [r5, #6]
	lsls r1, r1, #3
	add r1, r8
	ldrb r0, [r1, #1]
	ldrb r1, [r1, #2]
	bl CreateStageEntity
	adds r2, r0, #0
	cmp r2, #0
	bne _080181BC
_080181B4:
	adds r0, r4, #0
	bl ReleaseStageEntity
	b _0801820C
_080181BC:
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #3]
	strb r0, [r2, #0x10]
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0, #4]
_080181CE:
	strb r0, [r2, #0x11]
_080181D0:
	ldr r0, [r5]
	lsls r0, r0, #0xc
	movs r3, #0x80
	lsls r3, r3, #4
	adds r0, r0, r3
	str r0, [r2, #0x54]
	movs r1, #4
	ldrsh r0, [r5, r1]
	lsls r0, r0, #0xc
	subs r3, #1
	adds r0, r0, r3
	str r0, [r2, #0x58]
	str r2, [r4, #4]
	strh r7, [r4, #8]
	ldrh r0, [r5, #6]
	lsls r0, r0, #3
	add r0, r8
	ldrb r0, [r0]
	strh r0, [r4, #0xa]
	mov r0, sl
	lsls r2, r0, #2
	ldr r1, _080182B4 @ =gSpawnManager
	adds r2, r2, r1
	movs r0, #0x1f
	ands r0, r7
	movs r1, #1
	lsls r1, r0
	ldr r0, [r2]
	bics r0, r1
	str r0, [r2]
_0801820C:
	adds r5, #8
	adds r7, #1
	ldr r0, [r5]
	ldr r2, [sp, #0xc]
	cmp r2, r0
	ble _0801821A
	b _08018096
_0801821A:
	ldr r3, [sp]
	ldr r3, [r3]
	mov sl, r3
	ldr r0, [sp]
	ldr r0, [r0, #4]
	str r0, [sp, #8]
	ldr r1, _080182B4 @ =gSpawnManager
	movs r2, #0x81
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r4, [r0]
	cmp r4, #0
	bne _08018236
	b _0801835A
_08018236:
	movs r3, #0x89
	lsls r3, r3, #2
	adds r1, r1, r3
	mov r8, r1
_0801823E:
	ldr r6, [r4]
	ldr r2, [r4, #4]
	cmp r2, #0
	beq _08018260
	ldrh r1, [r4, #0xa]
	movs r5, #0x10
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x10
	asrs r3, r0, #0x10
	cmp r3, #0
	beq _080182B8
	ldrb r0, [r2, #0xc]
	cmp r0, #2
	bls _08018260
	movs r0, #0
	str r0, [r4, #4]
_08018260:
	movs r1, #8
	ldrsh r0, [r4, r1]
	mov r2, r8
	ldrh r2, [r2]
	cmp r0, r2
	blt _08018284
	cmp r0, r7
	bge _08018284
	lsls r0, r0, #3
	add r0, sb
	movs r3, #4
	ldrsh r0, [r0, r3]
	ldr r2, [sp, #8]
	asrs r1, r2, #0xc
	subs r0, r0, r1
	adds r0, #0xa
	cmp r0, #0x13
	bls _08018352
_08018284:
	ldrh r1, [r4, #0xa]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080182AA
	ldrh r1, [r4, #8]
	lsls r2, r1, #0x10
	asrs r2, r2, #0x15
	lsls r2, r2, #2
	ldr r0, _080182B4 @ =gSpawnManager
	adds r2, r2, r0
	movs r0, #0x1f
	ands r0, r1
	adds r1, r3, #0
	lsls r1, r0
	ldr r0, [r2]
	orrs r0, r1
	str r0, [r2]
_080182AA:
	adds r0, r4, #0
	bl ReleaseStageEntity
	b _08018352
	.align 2, 0
_080182B4: .4byte gSpawnManager
_080182B8:
	ldrb r0, [r2, #0xc]
	cmp r0, #2
	bls _080182D6
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080182CC
	movs r0, #1
	orrs r0, r1
	strh r0, [r4, #0xa]
_080182CC:
	ldrh r0, [r4, #0xa]
	orrs r0, r5
	strh r0, [r4, #0xa]
	str r3, [r4, #4]
	b _08018352
_080182D6:
	cmp r0, #1
	bls _080182F0
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080182E8
	movs r0, #1
	orrs r0, r1
	strh r0, [r4, #0xa]
_080182E8:
	ldrh r0, [r4, #0xa]
	orrs r0, r5
	strh r0, [r4, #0xa]
	b _08018352
_080182F0:
	movs r0, #0xc
	ands r0, r1
	cmp r0, #0
	bne _08018352
	ldr r0, [r2, #0x54]
	mov r1, sl
	subs r0, r0, r1
	movs r3, #0xd0
	lsls r3, r3, #8
	adds r0, r0, r3
	ldr r1, _0801836C @ =0x00019FFF
	cmp r0, r1
	bhi _0801831C
	ldr r0, [r2, #0x58]
	ldr r1, [sp, #8]
	subs r0, r0, r1
	movs r3, #0xc0
	lsls r3, r3, #8
	adds r0, r0, r3
	ldr r1, _08018370 @ =0x00017FFF
	cmp r0, r1
	bls _08018352
_0801831C:
	movs r1, #8
	ldrsh r0, [r4, r1]
	mov r3, r8
	ldrh r3, [r3]
	cmp r0, r3
	blt _08018340
	cmp r0, r7
	bge _08018340
	lsls r0, r0, #3
	add r0, sb
	movs r1, #4
	ldrsh r0, [r0, r1]
	ldr r3, [sp, #8]
	asrs r1, r3, #0xc
	subs r0, r0, r1
	adds r0, #0xa
	cmp r0, #0x13
	bls _08018352
_08018340:
	adds r0, r2, #0
	bl DeleteStageEntity
	ldrh r0, [r4, #0xa]
	movs r1, #0x11
	orrs r0, r1
	strh r0, [r4, #0xa]
	movs r0, #0
	str r0, [r4, #4]
_08018352:
	adds r4, r6, #0
	cmp r4, #0
	beq _0801835A
	b _0801823E
_0801835A:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0801836C: .4byte 0x00019FFF
_08018370: .4byte 0x00017FFF
