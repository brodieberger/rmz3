#include "global.h"
#include "vfx.h"

// コピーX関連

static void VFX52_Init(struct Entity* p);
static void VFX52_Update(struct Entity* p);
static void VFX52_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX52Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX52_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX52_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX52_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* CreateVFX52(struct Entity* e) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_052);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 0;
    p->work[1] = 0;
    p->unk_28 = e;
  }
  return p;
}

// --------------------------------------------

static void VFX52_Init(struct Entity* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitScalerotMotion1(p);
  p->taskCol = 25;
  ForceEntityPalette(p, 13);
  p->flags |= DISPLAY;
  p->work[3] = 0x80;
  VFX52_Update(p);
}

NAKED static void VFX52_Update(struct Entity* p) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	mov ip, r0\n\
	ldr r4, [r0, #0x28]\n\
	ldr r0, [r4, #0x54]\n\
	mov r1, ip\n\
	str r0, [r1, #0x54]\n\
	ldr r0, [r4, #0x58]\n\
	str r0, [r1, #0x58]\n\
	ldrb r0, [r1, #0x13]\n\
	adds r1, r0, #0\n\
	adds r1, #8\n\
	mov r2, ip\n\
	strb r1, [r2, #0x13]\n\
	ldr r1, _080C0D7C @ =gSineTable\n\
	adds r0, #0x48\n\
	lsls r0, r0, #0x18\n\
	lsrs r0, r0, #0x17\n\
	adds r0, r0, r1\n\
	movs r3, #0\n\
	ldrsh r0, [r0, r3]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #1\n\
	adds r0, r0, r2\n\
	asrs r0, r0, #3\n\
	movs r3, #8\n\
	rsbs r3, r3, #0\n\
	adds r1, r3, #0\n\
	ands r0, r1\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	adds r0, r0, r2\n\
	mov r1, ip\n\
	adds r1, #0x50\n\
	strh r0, [r1]\n\
	adds r1, #2\n\
	strh r0, [r1]\n\
	adds r0, r4, #0\n\
	adds r0, #0x48\n\
	ldrh r1, [r0]\n\
	lsls r1, r1, #0x16\n\
	mov r3, ip\n\
	adds r3, #0x48\n\
	lsrs r1, r1, #0x16\n\
	ldrh r2, [r3]\n\
	ldr r0, _080C0D80 @ =0xFFFFFC00\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strh r0, [r3]\n\
	ldr r0, [r4, #0x3c]\n\
	mov r1, ip\n\
	str r0, [r1, #0x3c]\n\
	adds r0, r4, #0\n\
	adds r0, #0x4e\n\
	ldrb r0, [r0]\n\
	adds r1, #0x4e\n\
	strb r0, [r1]\n\
	ldrb r0, [r4, #0xa]\n\
	lsrs r2, r0, #4\n\
	movs r0, #1\n\
	ands r2, r0\n\
	cmp r2, #0\n\
	beq _080C0D84\n\
	mov r3, ip\n\
	ldrb r0, [r3, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	strb r0, [r3, #0xa]\n\
	b _080C0D90\n\
	.align 2, 0\n\
_080C0D7C: .4byte gSineTable\n\
_080C0D80: .4byte 0xFFFFFC00\n\
_080C0D84:\n\
	mov r0, ip\n\
	ldrb r1, [r0, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
	mov r1, ip\n\
	strb r0, [r1, #0xa]\n\
_080C0D90:\n\
	adds r1, r2, #0\n\
	mov r0, ip\n\
	adds r0, #0x4c\n\
	strb r1, [r0]\n\
	mov r3, ip\n\
	adds r3, #0x4a\n\
	lsls r1, r1, #4\n\
	ldrb r2, [r3]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strb r0, [r3]\n\
	ldrb r0, [r4, #0xc]\n\
	cmp r0, #1\n\
	bhi _080C0DB8\n\
	mov r2, ip\n\
	ldrb r0, [r2, #0x11]\n\
	cmp r0, #0\n\
	beq _080C0DD2\n\
_080C0DB8:\n\
	ldr r1, _080C0DD8 @ =gVFXFnTable\n\
	mov r3, ip\n\
	ldrb r0, [r3, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r3, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r3, #0x14]\n\
	mov r0, ip\n\
	bl VFX52_Die\n\
_080C0DD2:\n\
	pop {r4}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080C0DD8: .4byte gVFXFnTable\n\
 .syntax divided\n");
}

static void VFX52_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}
