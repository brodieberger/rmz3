	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	adds r6, r0, #0
	ldrh r0, [r6, #4]
	movs r2, #4
	ldrsh r1, [r6, r2]
	cmp r1, #0x1f
	bgt _080F8F90
	adds r0, #1
	adds r1, r0, #0
	strh r0, [r6, #4]
	ldr r2, _080F8F88 @ =gPaletteManager
	ldr r3, _080F8F8C @ =0x00000402
	adds r0, r2, r3
	strb r1, [r0]
	movs r0, #0xff
	b _080F8FA4
	.align 2, 0
_080F8F88: .4byte gPaletteManager
_080F8F8C: .4byte 0x00000402
_080F8F90:
	cmp r1, #0x20
	ble _080F8FB4
	subs r0, #1
	strh r0, [r6, #4]
	ldr r2, _080F9170 @ =gPaletteManager
	subs r0, #0x20
	ldr r3, _080F9174 @ =0x00000402
	adds r1, r2, r3
	strb r0, [r1]
	movs r1, #0xff
_080F8FA4:
	ands r0, r1
	subs r3, #1
	adds r1, r2, r3
	strb r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r2, r2, r1
	strb r0, [r2]
_080F8FB4:
	ldr r2, _080F9178 @ =0x00001ED8
	adds r1, r6, r2
	ldr r0, [r1]
	adds r0, #1
	str r0, [r1]
	movs r3, #0x9a
	lsls r3, r3, #4
	adds r0, r6, r3
	bl ClearTaskBuffer
	ldr r1, _080F917C @ =0x0202F354
	movs r0, #0
	strb r0, [r1]
	ldr r1, _080F9180 @ =gWhitePaintFlags
	movs r0, #0
	str r0, [sp]
	ldr r2, _080F9184 @ =0x001FFFFF
	mov sl, r2
	ldr r2, _080F9188 @ =0x01000008
	mov r0, sp
	bl CpuFastSet
	ldr r1, _080F918C @ =sEachMinigameLoops
	ldrb r0, [r6, #1]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	cmp r0, #0
	bne _080F8FFA
	ldrb r0, [r6, #2]
	adds r0, #1
	strb r0, [r6, #2]
_080F8FFA:
	ldrb r0, [r6, #1]
	cmp r0, #1
	beq _080F9058
	ldr r7, _080F9190 @ =0x020023D4
	movs r3, #0xc0
	lsls r3, r3, #2
	adds r3, r3, r7
	mov sb, r3
	subs r0, r7, #2
	mov r8, r0
	ldrb r0, [r0]
	lsls r4, r0, #1
	adds r4, r4, r0
	lsls r4, r4, #3
	adds r5, r4, #0
	movs r0, #0x20
	rsbs r0, r0, #0
	ands r5, r0
	lsrs r2, r5, #2
	mov r1, sl
	ands r2, r1
	adds r0, r7, #0
	mov r1, sb
	bl CpuFastSet
	movs r0, #0x1f
	ands r4, r0
	cmp r4, #0
	beq _080F904A
	adds r0, r5, r7
	mov r2, sb
	adds r1, r5, r2
	lsrs r2, r4, #2
	mov r3, sl
	ands r2, r3
	movs r3, #0x80
	lsls r3, r3, #0x13
	orrs r2, r3
	bl CpuSet
_080F904A:
	mov r0, r8
	ldrb r1, [r0]
	subs r0, r7, #1
	strb r1, [r0]
	movs r2, #0
	mov r1, r8
	strb r2, [r1]
_080F9058:
	ldr r5, _080F9194 @ =gSolidHeaderPtr
	ldr r0, [r5]
	bl UpdateHazardEntities
	ldr r7, _080F9198 @ =gEnemyHeaderPtr
	ldr r0, [r7]
	bl UpdateHazardEntities
	ldr r3, _080F919C @ =0x0203029C
	mov r8, r3
	ldr r0, [r3]
	bl UpdateEntities
	bl UpdateProjectiles
	ldr r4, _080F91A0 @ =gWeaponHeaderPtr
	ldr r0, [r4]
	bl UpdateEntities
	ldr r0, _080F91A4 @ =gPickupHeaderPtr
	mov sb, r0
	ldr r0, [r0]
	bl UpdateEntities
	bl UpdateVFXs
	bl ClearAllHitboxes
	ldr r0, [r5]
	bl RegisterHitboxes
	ldr r0, [r7]
	bl RegisterHitboxes
	mov r1, r8
	ldr r0, [r1]
	bl RegisterHitboxes
	ldr r2, _080F91A8 @ =gProjectileHeaderPtr
	mov sl, r2
	ldr r0, [r2]
	bl RegisterHitboxes
	ldr r0, [r4]
	bl RegisterHitboxes
	mov r3, sb
	ldr r0, [r3]
	bl RegisterHitboxes
	ldrb r0, [r6, #1]
	cmp r0, #1
	beq _080F90CA
	ldr r1, _080F91AC @ =0x00000DC4
	adds r0, r6, r1
	bl UpdateStageLandscape
_080F90CA:
	bl CheckCollision
	ldr r0, [r5]
	bl RunDamageEffect
	ldr r0, [r7]
	bl RunDamageEffect
	mov r2, r8
	ldr r0, [r2]
	bl RunDamageEffect
	mov r3, sb
	ldr r0, [r3]
	bl RunDamageEffect
	ldr r0, [r5]
	movs r1, #0x9a
	lsls r1, r1, #4
	adds r4, r6, r1
	adds r1, r4, #0
	bl DrawCollidableEntity
	ldr r0, [r7]
	adds r1, r4, #0
	bl DrawCollidableEntity
	mov r2, r8
	ldr r0, [r2]
	adds r1, r4, #0
	bl DrawCollidableEntity
	adds r0, r4, #0
	bl DrawWeapon
	mov r3, sl
	ldr r0, [r3]
	adds r1, r4, #0
	bl DrawEntity
	ldr r0, _080F91B0 @ =gVFXHeaderPtr
	ldr r0, [r0]
	adds r1, r4, #0
	bl DrawEntity
	mov r1, sb
	ldr r0, [r1]
	adds r1, r4, #0
	bl DrawCollidableEntity
	ldrb r0, [r6, #1]
	cmp r0, #1
	beq _080F913A
	adds r0, r4, #0
	bl DrawOverworld
_080F913A:
	adds r0, r4, #0
	bl RunAllTasks
	ldr r0, _080F91B4 @ =0x0202F330
	ldrb r0, [r0]
	cmp r0, #0
	beq _080F915A
	ldr r0, _080F91B8 @ =gCollisionManager
	ldrb r1, [r0, #1]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _080F915A
	movs r0, #0x29
	bl PlaySound
_080F915A:
	ldr r1, _080F91B4 @ =0x0202F330
	movs r0, #0
	strb r0, [r1]
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080F9170: .4byte gPaletteManager
_080F9174: .4byte 0x00000402
_080F9178: .4byte 0x00001ED8
_080F917C: .4byte 0x0202F354
_080F9180: .4byte gWhitePaintFlags
_080F9184: .4byte 0x001FFFFF
_080F9188: .4byte 0x01000008
_080F918C: .4byte sEachMinigameLoops
_080F9190: .4byte 0x020023D4
_080F9194: .4byte gSolidHeaderPtr
_080F9198: .4byte gEnemyHeaderPtr
_080F919C: .4byte 0x0203029C
_080F91A0: .4byte gWeaponHeaderPtr
_080F91A4: .4byte gPickupHeaderPtr
_080F91A8: .4byte gProjectileHeaderPtr
_080F91AC: .4byte 0x00000DC4
_080F91B0: .4byte gVFXHeaderPtr
_080F91B4: .4byte 0x0202F330
_080F91B8: .4byte gCollisionManager
