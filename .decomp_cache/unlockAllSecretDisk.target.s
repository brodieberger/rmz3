080f8c14 <unlockAllSecretDisk>:
 80f8c14:	push	{r4, r5, r6, r7, lr}
 80f8c16:	sub	sp, #8
 80f8c18:	adds	r4, r0, #0
 80f8c1a:	ldr	r6, [pc, #88]	@ (80f8c74 <_080F8C74>)
 80f8c1c:	str	r4, [r6, #0]
 80f8c1e:	movs	r5, #0
 80f8c20:	str	r5, [sp, #0]
 80f8c22:	ldr	r2, [pc, #84]	@ (80f8c78 <_080F8C78>)
 80f8c24:	mov	r0, sp
 80f8c26:	adds	r1, r4, #0
 80f8c28:	bl	80fe538 <CpuFastSet>
 80f8c2c:	str	r5, [sp, #4]
 80f8c2e:	add	r0, sp, #4
 80f8c30:	adds	r4, #32
 80f8c32:	ldr	r2, [pc, #72]	@ (80f8c7c <_080F8C7C>)
 80f8c34:	adds	r1, r4, #0
 80f8c36:	bl	80fe53c <CpuSet>
 80f8c3a:	movs	r7, #3

080f8c3c <_080F8C3C>:
 80f8c3c:	ldr	r2, [r6, #0]
 80f8c3e:	lsrs	r4, r5, #2
 80f8c40:	adds	r2, r2, r4
 80f8c42:	adds	r3, r5, #0
 80f8c44:	ands	r3, r7
 80f8c46:	movs	r0, #1
 80f8c48:	lsls	r0, r3
 80f8c4a:	ldrb	r1, [r2, #0]
 80f8c4c:	orrs	r0, r1
 80f8c4e:	strb	r0, [r2, #0]
 80f8c50:	ldr	r2, [r6, #0]
 80f8c52:	adds	r2, r2, r4
 80f8c54:	movs	r0, #16
 80f8c56:	lsls	r0, r3
 80f8c58:	ldrb	r1, [r2, #0]
 80f8c5a:	orrs	r0, r1
 80f8c5c:	strb	r0, [r2, #0]
 80f8c5e:	adds	r0, r5, #1
 80f8c60:	lsls	r0, r0, #24
 80f8c62:	lsrs	r5, r0, #24
 80f8c64:	cmp	r5, #179	@ 0xb3
 80f8c66:	bls.n	80f8c3c <_080F8C3C>
 80f8c68:	bl	80f8c80 <clearStageDisk>
 80f8c6c:	add	sp, #8
 80f8c6e:	pop	{r4, r5, r6, r7}
 80f8c70:	pop	{r0}
 80f8c72:	bx	r0

080f8c74 <_080F8C74>:
 80f8c74:	.word	0x0203dc50

080f8c78 <_080F8C78>:
 80f8c78:	.word	0x01000008

080f8c7c <_080F8C7C>:
 80f8c7c:	.word	0x05000004

Disassembly of section lib_text:
