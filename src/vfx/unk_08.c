#include "entity.h"
#include "global.h"
#include "vfx.h"

// ダッシュの砂埃?

struct VFX8 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u8 angle;  // 0x74
  u8 unk_1[3];
  u16 mag;  // 0x78
  u16 unk_6;
  u8 unk_8[8];
};
static_assert(sizeof(struct VFX8) == sizeof(struct VFX));

static void Ghost8_Init(struct VFX* p);
static void Ghost8_Update(struct Entity* p);
static void Ghost8_Die(struct Entity* p);

// clang-format off
const VFXRoutine gGhost8Routine = {
    [ENTITY_INIT] =      (VFXFunc)Ghost8_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Ghost8_Update,
    [ENTITY_DIE] =       (VFXFunc)Ghost8_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void CreateGhost8(struct Coord* c, u8 n, u8 angle, u16 mag) {
  struct VFX8* p = (struct VFX8*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_008);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[1] = n;
    p->angle = angle;
    p->mag = mag;
  }
}

NAKED static void Ghost8_Init(struct VFX* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r4, r0, #0\n\
	adds r0, #0x74\n\
	ldrb r0, [r0]\n\
	lsls r0, r0, #0x18\n\
	asrs r0, r0, #0x18\n\
	cmp r0, #0\n\
	bne _080B4A1E\n\
	adds r0, r4, #0\n\
	adds r0, #0x78\n\
	movs r1, #0\n\
	ldrsh r2, [r0, r1]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #1\n\
	adds r5, r0, #0\n\
	cmp r2, r1\n\
	bne _080B4A1E\n\
	adds r0, r4, #0\n\
	bl InitNonAffineMotion\n\
	b _080B4A28\n\
_080B4A1E:\n\
	adds r0, r4, #0\n\
	bl InitScalerotMotion1\n\
	adds r5, r4, #0\n\
	adds r5, #0x78\n\
_080B4A28:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #1\n\
	movs r6, #0\n\
	orrs r0, r1\n\
	strb r0, [r4, #0xa]\n\
	adds r0, r4, #0\n\
	movs r1, #0xb\n\
	bl SetMotion\n\
	ldrb r2, [r4, #0x11]\n\
	cmp r2, #0\n\
	beq _080B4A48\n\
	ldrb r0, [r4, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	b _080B4A4E\n\
_080B4A48:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
_080B4A4E:\n\
	strb r0, [r4, #0xa]\n\
	movs r3, #1\n\
	adds r1, r3, #0\n\
	ands r1, r2\n\
	adds r0, r4, #0\n\
	adds r0, #0x4c\n\
	strb r1, [r0]\n\
	movs r0, #0x4a\n\
	adds r0, r0, r4\n\
	mov ip, r0\n\
	lsls r1, r1, #4\n\
	ldrb r2, [r0]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	mov r1, ip\n\
	strb r0, [r1]\n\
	adds r0, r4, #0\n\
	adds r0, #0x74\n\
	ldrb r1, [r0]\n\
	subs r0, #0x50\n\
	strb r1, [r0]\n\
	ldrh r1, [r5]\n\
	adds r0, #0x2c\n\
	strh r1, [r0]\n\
	ldrh r0, [r5]\n\
	adds r2, r4, #0\n\
	adds r2, #0x52\n\
	strh r0, [r2]\n\
	ldr r1, _080B4AA8 @ =gVFXFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	str r3, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r4, #0x14]\n\
	adds r0, r4, #0\n\
	bl Ghost8_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080B4AA8: .4byte gVFXFnTable\n\
 .syntax divided\n");
}

static void Ghost8_Update(struct Entity* p) {
  UpdateMotionGraphic(p);
  if ((p->motion).state == MOTION_END) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

static void Ghost8_Die(struct Entity* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }
