#include "global.h"
#include "vfx.h"

// メットールのなにか

static void VFX62_Init(struct Entity* p);
static void VFX62_Update(struct Entity* p);
static void VFX62_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX62Routine = {
    [ENTITY_INIT] =      (void*)VFX62_Init,
    [ENTITY_UPDATE] =    (void*)VFX62_Update,
    [ENTITY_DIE] =       (void*)VFX62_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void CreateVFX62(struct Entity* e, Coords32* c) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_UNK_062);
      p->work[0] = 0, p->work[1] = i;
      p->unk_28 = e;
      (p->coord).x = c->x, (p->coord).y = c->y;
    }
  }
}

// --------------------------------------------

static void _VFX62_Init(struct Entity* p);

static void VFX62_Init(struct Entity* p) {
  static const EntityFunc sInitializers[1] = {
      _VFX62_Init,
  };
  (sInitializers[p->work[0]])(p);
}

static void _VFX62_Update(struct Entity* p);

static void VFX62_Update(struct Entity* p) {
  static const EntityFunc sUpdates[1] = {
      _VFX62_Update,
  };
  (sUpdates[p->work[0]])(p);
}

static void VFX62_Die(struct Entity* p) {
  (p->flags) &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

// 0x0836F4B8
static const motion_t sMotions[3] = {
    MOTION(SM221_METTAUR, 16),
    MOTION(SM221_METTAUR, 16),
    MOTION(SM221_METTAUR, 17),
};

/**
 * @note 0x080c3574
 */
NAKED static void _VFX62_Init(struct Entity* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	adds r7, r0, #0\n\
	ldr r0, [r7, #0x28]\n\
	ldrb r0, [r0, #0xa]\n\
	lsrs r5, r0, #4\n\
	movs r0, #1\n\
	ands r5, r0\n\
	ldrb r4, [r7, #0x11]\n\
	ldrb r1, [r7, #0xa]\n\
	movs r6, #0\n\
	orrs r0, r1\n\
	strb r0, [r7, #0xa]\n\
	adds r0, r7, #0\n\
	bl InitNonAffineMotion\n\
	adds r2, r5, #0\n\
	cmp r5, #0\n\
	beq _080C35A4\n\
	ldrb r0, [r7, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	b _080C35AA\n\
_080C35A4:\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
_080C35AA:\n\
	strb r0, [r7, #0xa]\n\
	movs r0, #1\n\
	mov r8, r0\n\
	ands r0, r2\n\
	adds r6, r7, #0\n\
	adds r6, #0x4c\n\
	strb r0, [r6]\n\
	adds r3, r7, #0\n\
	adds r3, #0x4a\n\
	lsls r0, r0, #4\n\
	ldrb r2, [r3]\n\
	movs r1, #0x11\n\
	rsbs r1, r1, #0\n\
	mov ip, r1\n\
	ands r1, r2\n\
	orrs r1, r0\n\
	strb r1, [r3]\n\
	cmp r4, #1\n\
	bne _080C35E6\n\
	ldrb r0, [r7, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	strb r0, [r7, #0xa]\n\
	strb r4, [r6]\n\
	movs r2, #0x10\n\
	ldrb r1, [r3]\n\
	mov r0, ip\n\
	ands r0, r1\n\
	orrs r0, r2\n\
	strb r0, [r3]\n\
_080C35E6:\n\
	ldr r0, _080C3658 @ =sMotions\n\
	lsls r1, r4, #1\n\
	adds r1, r1, r0\n\
	ldrh r1, [r1]\n\
	adds r0, r7, #0\n\
	bl SetMotion\n\
	cmp r5, #0\n\
	beq _080C35FC\n\
	movs r0, #2\n\
	subs r4, r0, r4\n\
_080C35FC:\n\
	subs r1, r4, #1\n\
	lsls r1, r1, #7\n\
	ldr r6, _080C365C @ =RNG_0202f388\n\
	ldr r0, [r6]\n\
	ldr r5, _080C3660 @ =0x000343FD\n\
	muls r0, r5, r0\n\
	ldr r3, _080C3664 @ =0x00269EC3\n\
	adds r0, r0, r3\n\
	lsls r0, r0, #1\n\
	lsrs r2, r0, #1\n\
	lsrs r0, r0, #0x11\n\
	ldr r4, _080C3668 @ =0x000001FF\n\
	ands r0, r4\n\
	adds r1, r1, r0\n\
	ldr r0, _080C366C @ =0xFFFFFF00\n\
	adds r1, r1, r0\n\
	str r1, [r7, #0x5c]\n\
	adds r0, r2, #0\n\
	muls r0, r5, r0\n\
	adds r0, r0, r3\n\
	lsls r0, r0, #1\n\
	lsrs r1, r0, #1\n\
	str r1, [r6]\n\
	lsrs r0, r0, #0x11\n\
	ands r0, r4\n\
	ldr r1, _080C3670 @ =0xFFFFFE00\n\
	subs r1, r1, r0\n\
	str r1, [r7, #0x60]\n\
	ldr r1, _080C3674 @ =gVFXFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	mov r1, r8\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r7, #0x14]\n\
	adds r0, r7, #0\n\
	bl VFX62_Update\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080C3658: .4byte sMotions\n\
_080C365C: .4byte RNG_0202f388\n\
_080C3660: .4byte 0x000343FD\n\
_080C3664: .4byte 0x00269EC3\n\
_080C3668: .4byte 0x000001FF\n\
_080C366C: .4byte 0xFFFFFF00\n\
_080C3670: .4byte 0xFFFFFE00\n\
_080C3674: .4byte gVFXFnTable\n\
 .syntax divided\n");
}

/**
 * @note 0x080c3678
 */
NAKED void _VFX62_Update(struct Entity* p) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	adds r4, r0, #0\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x5c]\n\
	adds r0, r0, r1\n\
	str r0, [r4, #0x54]\n\
	ldr r0, [r4, #0x58]\n\
	ldr r1, [r4, #0x60]\n\
	adds r0, r0, r1\n\
	str r0, [r4, #0x58]\n\
	adds r1, #0x40\n\
	str r1, [r4, #0x60]\n\
	adds r0, r4, #0\n\
	bl UpdateEntityAnim\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _080C36C0\n\
	adds r1, r4, #0\n\
	adds r1, #0x54\n\
	movs r0, #3\n\
	bl CreateSmoke\n\
	ldr r1, _080C36C8 @ =gVFXFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r4, #0x14]\n\
_080C36C0:\n\
	pop {r4}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080C36C8: .4byte gVFXFnTable\n\
 .syntax divided\n");
}
