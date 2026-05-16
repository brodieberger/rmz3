#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"
#include "zero.h"

static void Solid44_Init(struct Solid* p);
static void Solid44_Update(struct Solid* p);
static void Solid44_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid44Routine = {
    [ENTITY_INIT] =      (void*)Solid44_Init,
    [ENTITY_UPDATE] =    (void*)Solid44_Update,
    [ENTITY_DIE] =       (void*)Solid44_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

static void Solid44_Init(struct Solid* p) {
  static const struct Collision sCollisions[2] = {
      {
        kind : DDP,
        faction : FACTION_ENEMY,
        damage : 255,
        remaining : 0,
        layer : 0x00000001,
        range : {PIXEL(0), PIXEL(8), PIXEL(34), PIXEL(18)},
      },
      {
        kind : DRP,
        faction : FACTION_ENEMY,
        damage : 255,
        LAYER(0xFFFFFFFF),
        hitzone : 0x00,
        remaining : 0,
        range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
      },
  };

  if ((p->s).work[0] == 0) {
    metatile_attr_t attr = GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
    if (attr == 0) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    } else {
      INIT_BODY(p, sCollisions, 0, NULL);
      (p->s).coord.x += PIXEL(8);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
      Solid44_Update(p);
    }
  } else {
    (p->s).flags |= FLIPABLE;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid44_Die(p);
  }
}

static void Solid44_Update(struct Solid* p) {
  // clang-format off
  if (
    (((p->body).status & BODY_STATUS_B2) && (BODY(pZero2) != BODY_CHIP_LIGHT)) || 
    (GetMetatileAttr((p->s).coord.x + PIXEL(17), (p->s).coord.y + 1) == 0) || 
    (GetMetatileAttr((p->s).coord.x - PIXEL(17), (p->s).coord.y + 1) == 0)
  ) {
    // clang-format on
    struct Entity* q = AllocEntityFirst(gSolidHeaderPtr);
    if (q != NULL) {
      q->taskCol = 30;
      INIT_SOLID_ROUTINE(q, SOLID_UNK_044);
      q->tileNum = 0, q->palID = 0;
      q->flags2 |= WHITE_PAINTABLE;
      q->invincibleID = q->uniqueID;
      q->work[0] = 1, q->work[1] = 0;
      q->coord.x = (p->s).coord.x + PIXEL(8);
      q->coord.y = (p->s).coord.y;
    }
    (p->s).coord.x -= PIXEL(8);
    EXIT_BODY(p);
    (p->s).flags |= FLIPABLE;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid44_Die(p);
  }
}

NAKED static void Solid44_Die(struct Solid* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	sub sp, #8\n\
	adds r6, r0, #0\n\
	ldrb r0, [r6, #0xd]\n\
	cmp r0, #1\n\
	beq _080DE43C\n\
	cmp r0, #1\n\
	bgt _080DE3CE\n\
	cmp r0, #0\n\
	beq _080DE3D6\n\
	b _080DE5C2\n\
_080DE3CE:\n\
	cmp r0, #2\n\
	bne _080DE3D4\n\
	b _080DE558\n\
_080DE3D4:\n\
	b _080DE5C2\n\
_080DE3D6:\n\
	str r0, [r6, #0x60]\n\
	str r0, [r6, #0x5c]\n\
	ldrb r0, [r6, #0x11]\n\
	cmp r0, #0\n\
	beq _080DE434\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	adds r2, r6, #0\n\
	adds r2, #0x49\n\
	ldrb r0, [r2]\n\
	movs r1, #0xc\n\
	orrs r0, r1\n\
	strb r0, [r2]\n\
	ldr r2, _080DE428 @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _080DE42C @ =0x000343FD\n\
	muls r1, r0, r1\n\
	ldr r0, _080DE430 @ =0x00269EC3\n\
	adds r1, r1, r0\n\
	lsls r1, r1, #1\n\
	lsrs r0, r1, #1\n\
	str r0, [r2]\n\
	lsrs r1, r1, #0x11\n\
	movs r0, #1\n\
	ands r1, r0\n\
	adds r1, #1\n\
	movs r2, #0x9d\n\
	lsls r2, r2, #8\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	movs r0, #2\n\
	strb r0, [r6, #0xd]\n\
	b _080DE5C2\n\
	.align 2, 0\n\
_080DE428: .4byte RNG_0202f388\n\
_080DE42C: .4byte 0x000343FD\n\
_080DE430: .4byte 0x00269EC3\n\
_080DE434:\n\
	strb r0, [r6, #0x12]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080DE43C:\n\
	ldrb r0, [r6, #0x12]\n\
	adds r3, r0, #1\n\
	strb r3, [r6, #0x12]\n\
	movs r0, #7\n\
	ands r0, r3\n\
	cmp r0, #0\n\
	bne _080DE526\n\
	ldr r2, _080DE47C @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _080DE480 @ =0x000343FD\n\
	muls r0, r1, r0\n\
	ldr r1, _080DE484 @ =0x00269EC3\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	lsrs r1, r0, #1\n\
	str r1, [r2]\n\
	lsls r0, r0, #3\n\
	lsrs r0, r0, #0x14\n\
	ldr r1, [r6, #0x58]\n\
	adds r1, r1, r0\n\
	str r1, [sp, #4]\n\
	movs r0, #8\n\
	ands r3, r0\n\
	adds r7, r2, #0\n\
	cmp r3, #0\n\
	beq _080DE488\n\
	ldr r0, [r6, #0x54]\n\
	movs r2, #0x90\n\
	lsls r2, r2, #4\n\
	adds r0, r0, r2\n\
	b _080DE48E\n\
	.align 2, 0\n\
_080DE47C: .4byte RNG_0202f388\n\
_080DE480: .4byte 0x000343FD\n\
_080DE484: .4byte 0x00269EC3\n\
_080DE488:\n\
	ldr r0, [r6, #0x54]\n\
	ldr r1, _080DE5CC @ =0xFFFFF700\n\
	adds r0, r0, r1\n\
_080DE48E:\n\
	str r0, [sp]\n\
	ldr r1, [sp]\n\
	ldr r2, _080DE5D0 @ =0xFFFFFC00\n\
	adds r1, r1, r2\n\
	ldr r0, [r7]\n\
	ldr r3, _080DE5D4 @ =0x000343FD\n\
	muls r0, r3, r0\n\
	ldr r4, _080DE5D8 @ =0x00269EC3\n\
	adds r0, r0, r4\n\
	lsls r0, r0, #1\n\
	lsrs r2, r0, #1\n\
	lsls r0, r0, #4\n\
	lsrs r0, r0, #0x15\n\
	adds r1, r1, r0\n\
	str r1, [sp]\n\
	ldr r0, _080DE5DC @ =0x00009D03\n\
	muls r2, r3, r2\n\
	adds r2, r2, r4\n\
	lsls r2, r2, #1\n\
	lsrs r1, r2, #1\n\
	lsrs r2, r2, #0x11\n\
	movs r5, #1\n\
	ands r2, r5\n\
	muls r3, r1, r3\n\
	adds r3, r3, r4\n\
	lsls r3, r3, #1\n\
	lsrs r1, r3, #1\n\
	str r1, [r7]\n\
	lsrs r3, r3, #0x11\n\
	ands r3, r5\n\
	mov r1, sp\n\
	bl FUN_080b2c28\n\
	ldr r0, _080DE5E0 @ =gSolidHeaderPtr\n\
	ldr r1, [r0]\n\
	movs r2, #0xa\n\
	ldrsh r0, [r1, r2]\n\
	cmp r0, #8\n\
	ble _080DE526\n\
	adds r0, r1, #0\n\
	bl AllocEntityFirst\n\
	adds r3, r0, #0\n\
	cmp r3, #0\n\
	beq _080DE526\n\
	adds r1, r3, #0\n\
	adds r1, #0x25\n\
	movs r2, #0\n\
	movs r0, #0x1e\n\
	strb r0, [r1]\n\
	ldr r0, _080DE5E4 @ =gSolidFnTable\n\
	movs r1, #0x2c\n\
	strb r1, [r3, #9]\n\
	adds r0, #0xb0\n\
	ldr r0, [r0]\n\
	ldr r0, [r0]\n\
	str r0, [r3, #0x14]\n\
	movs r0, #0\n\
	strh r2, [r3, #0x20]\n\
	adds r1, r3, #0\n\
	adds r1, #0x22\n\
	strb r0, [r1]\n\
	ldrb r1, [r3, #0xb]\n\
	movs r0, #0x10\n\
	orrs r0, r1\n\
	strb r0, [r3, #0xb]\n\
	ldrb r0, [r3, #0x1c]\n\
	strb r0, [r3, #0x1d]\n\
	movs r0, #1\n\
	strb r0, [r3, #0x10]\n\
	strb r0, [r3, #0x11]\n\
	ldr r0, [sp]\n\
	str r0, [r3, #0x54]\n\
	ldr r0, [r6, #0x58]\n\
	str r0, [sp, #4]\n\
	str r0, [r3, #0x58]\n\
_080DE526:\n\
	ldrb r0, [r6, #0x12]\n\
	cmp r0, #0x3b\n\
	bls _080DE5C2\n\
	ldrb r0, [r6, #0x10]\n\
	cmp r0, #0\n\
	bne _080DE53A\n\
	adds r0, r6, #0\n\
	adds r0, #0x54\n\
	bl FUN_080133e8\n\
_080DE53A:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	movs r1, #0x9d\n\
	lsls r1, r1, #8\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080DE558:\n\
	adds r0, r6, #0\n\
	bl UpdateMotionGraphic\n\
	ldr r1, [r6, #0x60]\n\
	ldr r0, _080DE5E8 @ =0x000006FF\n\
	cmp r1, r0\n\
	bgt _080DE56C\n\
	adds r0, r1, #0\n\
	adds r0, #0x20\n\
	str r0, [r6, #0x60]\n\
_080DE56C:\n\
	ldr r0, [r6, #0x58]\n\
	ldr r1, [r6, #0x60]\n\
	adds r0, r0, r1\n\
	str r0, [r6, #0x58]\n\
	str r0, [r6, #0x68]\n\
	ldr r0, _080DE5EC @ =gStageRun+232\n\
	adds r1, r6, #0\n\
	adds r1, #0x54\n\
	bl CalcFromCamera\n\
	movs r1, #0xa0\n\
	lsls r1, r1, #4\n\
	cmp r0, r1\n\
	bls _080DE5C2\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r1, #0\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	strb r1, [r0]\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	ldrb r1, [r6, #0xb]\n\
	movs r0, #0xf7\n\
	ands r0, r1\n\
	strb r0, [r6, #0xb]\n\
	ldr r1, _080DE5E4 @ =gSolidFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #4\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0x10]\n\
	str r0, [r6, #0x14]\n\
_080DE5C2:\n\
	add sp, #8\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080DE5CC: .4byte 0xFFFFF700\n\
_080DE5D0: .4byte 0xFFFFFC00\n\
_080DE5D4: .4byte 0x000343FD\n\
_080DE5D8: .4byte 0x00269EC3\n\
_080DE5DC: .4byte 0x00009D03\n\
_080DE5E0: .4byte gSolidHeaderPtr\n\
_080DE5E4: .4byte gSolidFnTable\n\
_080DE5E8: .4byte 0x000006FF\n\
_080DE5EC: .4byte gStageRun+232\n\
 .syntax divided\n");
}
