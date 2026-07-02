080f7d94 <DiskLoop_Init>:
 80f7d94:	push	{r4, r5, r6, r7, lr}
 80f7d96:	mov	r7, r10
 80f7d98:	mov	r6, r9
 80f7d9a:	mov	r5, r8
 80f7d9c:	push	{r5, r6, r7}
 80f7d9e:	adds	r7, r0, #0
 80f7da0:	movs	r4, #0
 80f7da2:	movs	r5, #0
 80f7da4:	strh	r5, [r7, #4]
 80f7da6:	ldr	r1, [pc, #132]	@ (80f7e2c <_080F7E2C>)
 80f7da8:	adds	r0, r7, r1
 80f7daa:	strb	r4, [r0, #10]
 80f7dac:	strb	r4, [r0, #11]
 80f7dae:	strb	r4, [r0, #13]
 80f7db0:	strb	r4, [r0, #14]
 80f7db2:	strb	r4, [r0, #15]
 80f7db4:	strb	r4, [r0, #16]
 80f7db6:	strb	r4, [r0, #17]
 80f7db8:	strb	r4, [r0, #18]
 80f7dba:	adds	r0, r7, #0
 80f7dbc:	bl	80f83ac <sd_analysis_080f83ac>
 80f7dc0:	ldr	r4, [pc, #108]	@ (80f7e30 <_080F7E30>)
 80f7dc2:	ldrh	r1, [r4, #0]
 80f7dc4:	ldr	r0, [pc, #108]	@ (80f7e34 <_080F7E34>)
 80f7dc6:	ands	r0, r1
 80f7dc8:	ldr	r1, [pc, #108]	@ (80f7e38 <_080F7E38>)
 80f7dca:	ands	r0, r1
 80f7dcc:	movs	r2, #152	@ 0x98
 80f7dce:	lsls	r2, r2, #5
 80f7dd0:	adds	r1, r2, #0
 80f7dd2:	orrs	r0, r1
 80f7dd4:	strh	r0, [r4, #0]
 80f7dd6:	ldr	r1, [pc, #100]	@ (80f7e3c <_080F7E3C>)
 80f7dd8:	adds	r0, r1, #0
 80f7dda:	strh	r0, [r4, #6]
 80f7ddc:	str	r5, [r4, #16]
 80f7dde:	ldr	r1, [pc, #96]	@ (80f7e40 <_080F7E40>)
 80f7de0:	ldr	r0, [pc, #96]	@ (80f7e44 <_080F7E44>)
 80f7de2:	strh	r0, [r1, #0]
 80f7de4:	ldr	r0, [pc, #96]	@ (80f7e48 <_080F7E48>)
 80f7de6:	movs	r5, #12
 80f7de8:	movs	r1, #128	@ 0x80
 80f7dea:	lsls	r1, r1, #7
 80f7dec:	bl	80037c0 <LoadGraphic>
 80f7df0:	ldr	r0, [pc, #88]	@ (80f7e4c <_080F7E4C>)
 80f7df2:	movs	r1, #0
 80f7df4:	bl	8003c98 <LoadPalette>
 80f7df8:	ldr	r2, [pc, #84]	@ (80f7e50 <_080F7E50>)
 80f7dfa:	adds	r0, r7, r2
 80f7dfc:	ldr	r2, [pc, #84]	@ (80f7e54 <_080F7E54>)
 80f7dfe:	ldr	r1, [r2, #0]
 80f7e00:	adds	r1, r1, r2
 80f7e02:	movs	r2, #0
 80f7e04:	movs	r3, #0
 80f7e06:	bl	80f3c90 <CopyBgMap>
 80f7e0a:	ldr	r0, [pc, #76]	@ (80f7e58 <_080F7E58>)
 80f7e0c:	adds	r0, #75	@ 0x4b
 80f7e0e:	ldrb	r0, [r0, #0]
 80f7e10:	cmp	r0, #1
 80f7e12:	bne.n	80f7e64 <_080F7E64>
 80f7e14:	ldr	r0, [pc, #68]	@ (80f7e5c <_080F7E5C>)
 80f7e16:	ldrh	r2, [r4, #6]
 80f7e18:	adds	r1, r5, #0
 80f7e1a:	ands	r1, r2
 80f7e1c:	lsls	r1, r1, #12
 80f7e1e:	bl	80037c0 <LoadGraphic>
 80f7e22:	ldr	r0, [pc, #60]	@ (80f7e60 <_080F7E60>)
 80f7e24:	movs	r1, #0
 80f7e26:	bl	8003c98 <LoadPalette>
 80f7e2a:	b.n	80f7e7e <_080F7E7E>

080f7e2c <_080F7E2C>:
 80f7e2c:	.word	0x00000dcc

080f7e30 <_080F7E30>:
 80f7e30:	.word	0x02002140

080f7e34 <_080F7E34>:
 80f7e34:	.word	0x0000fff8

080f7e38 <_080F7E38>:
 80f7e38:	.word	0x0000f0ff

080f7e3c <_080F7E3C>:
 80f7e3c:	.word	0x00004206

080f7e40 <_080F7E40>:
 80f7e40:	.word	0x02002180

080f7e44 <_080F7E44>:
 80f7e44:	.word	0x00002010

080f7e48 <_080F7E48>:
 80f7e48:	.word	0x08547438

080f7e4c <_080F7E4C>:
 80f7e4c:	.word	0x08547444

080f7e50 <_080F7E50>:
 80f7e50:	.word	0x00000ed8

080f7e54 <_080F7E54>:
 80f7e54:	.word	0x08522434

080f7e58 <_080F7E58>:
 80f7e58:	.word	0x020021b0

080f7e5c <_080F7E5C>:
 80f7e5c:	.word	0x08547550

080f7e60 <_080F7E60>:
 80f7e60:	.word	0x0854755c

080f7e64 <_080F7E64>:
 80f7e64:	cmp	r0, #2
 80f7e66:	bne.n	80f7e7e <_080F7E7E>
 80f7e68:	ldr	r0, [pc, #268]	@ (80f7f78 <_080F7F78>)
 80f7e6a:	ldrh	r2, [r4, #6]
 80f7e6c:	adds	r1, r5, #0
 80f7e6e:	ands	r1, r2
 80f7e70:	lsls	r1, r1, #12
 80f7e72:	bl	80037c0 <LoadGraphic>
 80f7e76:	ldr	r0, [pc, #260]	@ (80f7f7c <_080F7F7C>)
 80f7e78:	movs	r1, #0
 80f7e7a:	bl	8003c98 <LoadPalette>

080f7e7e <_080F7E7E>:
 80f7e7e:	adds	r0, r7, #0
 80f7e80:	bl	80f845c <setSecretDiskPalette>
 80f7e84:	movs	r4, #140	@ 0x8c
 80f7e86:	lsls	r4, r4, #1
 80f7e88:	ldr	r0, [pc, #244]	@ (80f7f80 <_080F7F80>)
 80f7e8a:	mov	r8, r0
 80f7e8c:	adds	r0, r4, r0
 80f7e8e:	ldr	r6, [pc, #244]	@ (80f7f84 <_080F7F84>)
 80f7e90:	ldrh	r1, [r6, #28]
 80f7e92:	ldrh	r2, [r0, #6]
 80f7e94:	lsrs	r2, r2, #6
 80f7e96:	subs	r1, r1, r2
 80f7e98:	lsls	r1, r1, #5
 80f7e9a:	movs	r2, #128	@ 0x80
 80f7e9c:	lsls	r2, r2, #9
 80f7e9e:	adds	r1, r1, r2
 80f7ea0:	bl	80037c0 <LoadGraphic>
 80f7ea4:	ldr	r0, [pc, #224]	@ (80f7f88 <_080F7F88>)
 80f7ea6:	mov	r10, r0
 80f7ea8:	add	r4, r10
 80f7eaa:	ldr	r5, [pc, #224]	@ (80f7f8c <_080F7F8C>)
 80f7eac:	ldrh	r1, [r5, #28]
 80f7eae:	ldrb	r0, [r4, #7]
 80f7eb0:	subs	r1, r1, r0
 80f7eb2:	lsls	r1, r1, #5
 80f7eb4:	movs	r2, #128	@ 0x80
 80f7eb6:	lsls	r2, r2, #2
 80f7eb8:	mov	r9, r2
 80f7eba:	add	r1, r9
 80f7ebc:	adds	r0, r4, #0
 80f7ebe:	bl	8003c98 <LoadPalette>
 80f7ec2:	ldr	r4, [pc, #204]	@ (80f7f90 <_080F7F90>)
 80f7ec4:	add	r8, r4
 80f7ec6:	adds	r6, #166	@ 0xa6
 80f7ec8:	ldrh	r1, [r6, #0]
 80f7eca:	mov	r2, r8
 80f7ecc:	ldrh	r0, [r2, #6]
 80f7ece:	lsrs	r0, r0, #6
 80f7ed0:	subs	r1, r1, r0
 80f7ed2:	lsls	r1, r1, #5
 80f7ed4:	movs	r0, #128	@ 0x80
 80f7ed6:	lsls	r0, r0, #9
 80f7ed8:	adds	r1, r1, r0
 80f7eda:	mov	r0, r8
 80f7edc:	bl	80037c0 <LoadGraphic>
 80f7ee0:	add	r4, r10
 80f7ee2:	adds	r5, #166	@ 0xa6
 80f7ee4:	ldrh	r1, [r5, #0]
 80f7ee6:	ldrb	r0, [r4, #7]
 80f7ee8:	subs	r1, r1, r0
 80f7eea:	lsls	r1, r1, #5
 80f7eec:	add	r1, r9
 80f7eee:	adds	r0, r4, #0
 80f7ef0:	bl	8003c98 <LoadPalette>
 80f7ef4:	adds	r0, r7, #0
 80f7ef6:	movs	r1, #3
 80f7ef8:	bl	80e7564 <CreateTriangleCursor>
 80f7efc:	adds	r0, r7, #0
 80f7efe:	movs	r1, #4
 80f7f00:	bl	80e7564 <CreateTriangleCursor>
 80f7f04:	adds	r0, r7, #0
 80f7f06:	movs	r1, #0
 80f7f08:	bl	80e8204 <createSecretDiskModalBorder>
 80f7f0c:	adds	r0, r7, #0
 80f7f0e:	movs	r1, #1
 80f7f10:	bl	80e8204 <createSecretDiskModalBorder>
 80f7f14:	adds	r0, r7, #0
 80f7f16:	movs	r1, #2
 80f7f18:	bl	80e8204 <createSecretDiskModalBorder>
 80f7f1c:	adds	r0, r7, #0
 80f7f1e:	movs	r1, #3
 80f7f20:	bl	80e8204 <createSecretDiskModalBorder>
 80f7f24:	movs	r0, #64	@ 0x40
 80f7f26:	movs	r1, #0
 80f7f28:	bl	8003f2c <StartPaletteAnimation>
 80f7f2c:	movs	r2, #0
 80f7f2e:	ldr	r3, [pc, #100]	@ (80f7f94 <_080F7F94>)
 80f7f30:	adds	r4, r3, #0
 80f7f32:	subs	r4, #32

080f7f34 <_080F7F34>:
 80f7f34:	lsls	r0, r2, #1
 80f7f36:	adds	r1, r0, r3
 80f7f38:	adds	r0, r0, r4
 80f7f3a:	ldrh	r0, [r0, #0]
 80f7f3c:	strh	r0, [r1, #0]
 80f7f3e:	adds	r0, r2, #1
 80f7f40:	lsls	r0, r0, #24
 80f7f42:	lsrs	r2, r0, #24
 80f7f44:	cmp	r2, #15
 80f7f46:	bls.n	80f7f34 <_080F7F34>
 80f7f48:	ldr	r1, [pc, #76]	@ (80f7f98 <_080F7F98>)
 80f7f4a:	adds	r0, r7, r1
 80f7f4c:	ldr	r1, [pc, #76]	@ (80f7f9c <_080F7F9C>)
 80f7f4e:	ldrh	r2, [r1, #0]
 80f7f50:	movs	r1, #248	@ 0xf8
 80f7f52:	lsls	r1, r1, #5
 80f7f54:	ands	r1, r2
 80f7f56:	lsls	r1, r1, #3
 80f7f58:	movs	r2, #128	@ 0x80
 80f7f5a:	lsls	r2, r2, #5
 80f7f5c:	bl	80039ac <RequestBgMapTransfer>
 80f7f60:	movs	r0, #1
 80f7f62:	strb	r0, [r7, #1]
 80f7f64:	adds	r0, r7, #0
 80f7f66:	bl	80f7fa0 <DiskLoop_OpenScreen>
 80f7f6a:	pop	{r3, r4, r5}
 80f7f6c:	mov	r8, r3
 80f7f6e:	mov	r9, r4
 80f7f70:	mov	r10, r5
 80f7f72:	pop	{r4, r5, r6, r7}
 80f7f74:	pop	{r0}
 80f7f76:	bx	r0

080f7f78 <_080F7F78>:
 80f7f78:	.word	0x08547564

080f7f7c <_080F7F7C>:
 80f7f7c:	.word	0x08547570

080f7f80 <_080F7F80>:
 80f7f80:	.word	0x085d78f8

080f7f84 <_080F7F84>:
 80f7f84:	.word	0x0202f790

080f7f88 <_080F7F88>:
 80f7f88:	.word	0x085d7904

080f7f8c <_080F7F8C>:
 80f7f8c:	.word	0x0202f590

080f7f90 <_080F7F90>:
 80f7f90:	.word	0x0000067c

080f7f94 <_080F7F94>:
 80f7f94:	.word	0x03002be0

080f7f98 <_080F7F98>:
 80f7f98:	.word	0x00000ed8

080f7f9c <_080F7F9C>:
 80f7f9c:	.word	0x02002146

Disassembly of section lib_text:
