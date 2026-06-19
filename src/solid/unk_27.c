#include "collision.h"
#include "entity.h"
#include "global.h"
#include "solid.h"

// 水没した図書館関連の何か

static void Solid27_Init(struct Solid* p);
static void Solid27_Update(struct Solid* p);
static void Solid27_Die(void* _ UNUSED);

// clang-format off
const SolidRoutine gSolid27Routine = {
    [ENTITY_INIT] =      (void*)Solid27_Init,
    [ENTITY_UPDATE] =    (void*)Solid27_Update,
    [ENTITY_DIE] =       (void*)Solid27_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Entity* FUN_080d8f2c(void) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_UNK_027);
    p->work[0] = 0;
  }
  return p;
}

struct Entity* FUN_080d8f7c(u8 kind) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_UNK_027);
    p->work[0] = 1, p->work[1] = kind;
  }
  return p;
}

void FUN_080d8fd4(struct Entity* p) {
  if (p != NULL) p->work[3] = 1;
}

void FUN_080d8fe4(struct Entity* p) {
  if (p != NULL) p->work[3] = 0;
}

// --------------------------------------------

static const struct Collision sCollisions[];

NAKED static void Solid27_Init(struct Solid* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r5, r0, #0\n\
	movs r2, #0\n\
	movs r6, #0\n\
	strb r6, [r5, #0x13]\n\
	strb r6, [r5, #0x12]\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #2\n\
	orrs r1, r0\n\
	orrs r1, r2\n\
	strb r1, [r5, #0xa]\n\
	ldrb r0, [r5, #0x10]\n\
	cmp r0, #0\n\
	bne _080D9024\n\
	movs r0, #4\n\
	orrs r1, r0\n\
	strb r1, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _080D9020 @ =sCollisions\n\
	b _080D903A\n\
	.align 2, 0\n\
_080D9020: .4byte sCollisions\n\
_080D9024:\n\
	movs r0, #4\n\
	orrs r1, r0\n\
	strb r1, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldrb r0, [r5, #0x11]\n\
	lsls r1, r0, #1\n\
	adds r1, r1, r0\n\
	lsls r1, r1, #3\n\
	ldr r0, _080D9068 @ =0x0837110C\n\
	adds r1, r1, r0\n\
_080D903A:\n\
	adds r2, r5, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0\n\
	bl InitBody\n\
	str r5, [r4, #0x2c]\n\
	str r6, [r4, #0x24]\n\
	ldr r1, _080D906C @ =gSolidFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r5, #0x14]\n\
	adds r0, r5, #0\n\
	bl Solid27_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080D9068: .4byte sCollisions+(1*24)\n\
_080D906C: .4byte gSolidFnTable\n\
 .syntax divided\n");
}

NAKED static void Solid27_Update(struct Solid* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r5, r0, #0\n\
	ldrb r6, [r5, #0x10]\n\
	cmp r6, #0\n\
	bne _080D90E4\n\
	ldrb r0, [r5, #0x13]\n\
	adds r1, r0, #0\n\
	ldrb r2, [r5, #0x12]\n\
	cmp r1, r2\n\
	beq _080D90C6\n\
	strb r0, [r5, #0x12]\n\
	cmp r1, #0\n\
	beq _080D90B0\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _080D90AC @ =sCollisions\n\
	adds r2, r5, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0\n\
	bl InitBody\n\
	str r5, [r4, #0x2c]\n\
	str r6, [r4, #0x24]\n\
	b _080D90C6\n\
	.align 2, 0\n\
_080D90AC: .4byte sCollisions\n\
_080D90B0:\n\
	adds r0, r5, #0\n\
	adds r0, #0x8c\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	strb r1, [r0]\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r5, #0xa]\n\
_080D90C6:\n\
	ldr r0, _080D90D8 @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0x54]\n\
	str r0, [r5, #0x54]\n\
	ldr r0, _080D90DC @ =gOverworld\n\
	ldr r1, _080D90E0 @ =0x0002C00C\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	b _080D9150\n\
	.align 2, 0\n\
_080D90D8: .4byte pZero2\n\
_080D90DC: .4byte gOverworld\n\
_080D90E0: .4byte 0x0002C00C\n\
_080D90E4:\n\
	ldr r0, _080D9124 @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r2, [r0, #0x54]\n\
	str r2, [r5, #0x54]\n\
	ldr r1, [r0, #0x58]\n\
	str r1, [r5, #0x58]\n\
	ldrb r0, [r5, #0x11]\n\
	cmp r0, #0\n\
	bne _080D9130\n\
	adds r0, r2, #0\n\
	bl FUN_0800a31c\n\
	str r0, [r5, #0x54]\n\
	ldr r0, _080D9128 @ =gOverworld\n\
	movs r2, #0xe8\n\
	lsls r2, r2, #1\n\
	adds r0, r0, r2\n\
	ldrh r1, [r0]\n\
	movs r0, #0x7f\n\
	ands r0, r1\n\
	cmp r0, #0xd\n\
	bne _080D9152\n\
	ldr r1, [r5, #0x58]\n\
	movs r0, #0x97\n\
	lsls r0, r0, #0xb\n\
	cmp r1, r0\n\
	bgt _080D9150\n\
	ldr r0, _080D912C @ =0x000427FF\n\
	cmp r1, r0\n\
	bgt _080D9152\n\
	adds r0, #1\n\
	b _080D9150\n\
	.align 2, 0\n\
_080D9124: .4byte pZero2\n\
_080D9128: .4byte gOverworld\n\
_080D912C: .4byte 0x000427FF\n\
_080D9130:\n\
	cmp r0, #1\n\
	bne _080D913E\n\
	adds r0, r2, #0\n\
	bl FUN_0800a22c\n\
	str r0, [r5, #0x54]\n\
	b _080D9152\n\
_080D913E:\n\
	cmp r0, #2\n\
	bne _080D914A\n\
	adds r0, r2, #0\n\
	bl FUN_0800a134\n\
	b _080D9150\n\
_080D914A:\n\
	adds r0, r2, #0\n\
	bl FUN_08009f6c\n\
_080D9150:\n\
	str r0, [r5, #0x58]\n\
_080D9152:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}

static void Solid27_Die(void* _) {}

// --------------------------------------------

// 0x083710F4
static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x5000, 0x0800, -0x6200},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-0x0600, -0x1000, 0x1000, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0600, -0x1000, 0x1000, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, -0x0600, 0x0800, 0x1000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0600, 0x0800, 0x1000},
    },
};
