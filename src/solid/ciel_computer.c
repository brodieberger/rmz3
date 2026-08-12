#include "collision.h"
#include "config.h"
#include "gfx.h"
#include "global.h"
#include "solid.h"

struct CielComputerObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Entity* toucher;  // 0xB4, US only: the entity currently inside the DDP
  u8 unk_b8[12];           // 0xB8
};
static_assert(sizeof(struct CielComputerObject) == sizeof(struct Solid));

static void CielComputer_Init(struct Solid* p);
#if IS_US
static void CielComputer_OnTouch(struct Body* body, Coords32* a, Coords32* b);
#endif
static void CielComputer_Update(struct Solid* p);
static void CielComputer_Die(Object* p);

// clang-format off
const SolidRoutine gCielComputerRoutine = {
    [ENTITY_INIT] =      (void*)CielComputer_Init,
    [ENTITY_UPDATE] =    (void*)CielComputer_Update,
    [ENTITY_DIE] =       (void*)CielComputer_Die,
    [ENTITY_DISAPPEAR] = (void*)CielComputer_Die,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

// 0x08371838
static const motion_t sMotions[5] = {
    MOTION(SM144_CIEL_COMP_0, 0), MOTION(SM145_CIEL_COMP_1, 0), MOTION(SM146_CIEL_COMP_2, 0), MOTION(SM147_CIEL_COMP_3, 0), MOTION(SM148_CIEL_COMP_4, 0),
};

static void CielComputer_Init(struct Solid* p) {
  static const struct Collision sCollisions[] = {
      {
        kind : DDP,
        faction : FACTION_NEUTRAL,
        special : CHATABLE,
        damage : 0xFF,
        layer : 0x00000001,
        range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(1)},
      },
      {
        kind : DRP,
        faction : FACTION_NEUTRAL,
        special : CHATABLE,
        damage : 0xFF,
        LAYER(0xFFFFFFFF),
        remaining : 0,
        range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
      },
  };  // 0x08371844

  motion_id_t id;
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SET_XFLIP(p, FALSE);
  SetSpriteAnimation(p, sMotions[gSystemSavedata.cielComputer]);
  id = sMotions[gSystemSavedata.cielComputer] >> 8;
  LOAD_STATIC_GRAPHIC(id);
#if IS_US
  INIT_BODY(p, sCollisions, 0, CielComputer_OnTouch);
  ((struct CielComputerObject*)p)->toucher = NULL;
#else
  INIT_BODY(p, sCollisions, 0, NULL);
#endif
  (p->s).coord.x += PIXEL(8);
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) + 1;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  CielComputer_Update((void*)p);
}

#if IS_US
NAKED static void CielComputer_OnTouch(struct Body* body, Coords32* a, Coords32* b) {
  asm(".syntax unified\n\
	push {lr}\n\
	ldr r2, [r0, #0x2c]\n\
	ldr r0, [r0, #0xc]\n\
	ldr r1, [r0, #0x2c]\n\
	movs r0, #8\n\
	ldrsb r0, [r1, r0]\n\
	cmp r0, #0\n\
	bne _080DED6E\n\
	adds r0, r2, #0\n\
	adds r0, #0xb4\n\
	str r1, [r0]\n\
_080DED6E:\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}
#endif

NAKED static void CielComputer_Update(struct Solid* p) {
  asm(".syntax unified\n\
.if REGION_US\n\
	@ US keeps &p->toucher live in r9, requires a toucher before opening the\n\
	@ chat, and clears it on every exit path.\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r9\n\
	mov r6, r8\n\
	push {r6, r7}\n\
	adds r6, r0, #0\n\
	bl UpdateEntityAnim\n\
	ldrb r0, [r6, #0xd]\n\
	cmp r0, #0\n\
	beq _US_080DED92\n\
	cmp r0, #1\n\
	beq _US_080DEE64\n\
	adds r6, #0xb4\n\
	mov r9, r6\n\
	b _US_080DEEFC\n\
_US_080DED92:\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	ldr r0, [r0]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #0x16\n\
	ands r0, r1\n\
	movs r1, #0xb4\n\
	adds r1, r1, r6\n\
	mov r9, r1\n\
	cmp r0, #0\n\
	bne _US_080DEDAA\n\
	b _US_080DEEFC\n\
_US_080DEDAA:\n\
	ldr r0, _US_080DEE4C @ =gInChat\n\
	ldrb r0, [r0]\n\
	cmp r0, #0\n\
	bne _US_080DEDB4\n\
	b _US_080DEEFC\n\
_US_080DEDB4:\n\
	ldr r0, _US_080DEE50 @ =gCollisionManager\n\
	movs r2, #0xc5\n\
	lsls r2, r2, #3\n\
	adds r0, r0, r2\n\
	adds r1, r6, #0\n\
	adds r1, #0x74\n\
	ldr r0, [r0]\n\
	cmp r0, r1\n\
	beq _US_080DEDC8\n\
	b _US_080DEEFC\n\
_US_080DEDC8:\n\
	mov r1, r9\n\
	ldr r0, [r1]\n\
	cmp r0, #0\n\
	bne _US_080DEDD2\n\
	b _US_080DEEFC\n\
_US_080DEDD2:\n\
	ldr r0, _US_080DEE54 @ =gSystemSavedata\n\
	adds r4, r0, #0\n\
	adds r4, #0x48\n\
	ldrb r0, [r4]\n\
	cmp r0, #3\n\
	bhi _US_080DEE10\n\
	ldr r1, _US_080DEE58 @ =sMotions\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r0, [r0]\n\
	movs r1, #1\n\
	orrs r1, r0\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldrb r0, [r4]\n\
	cmp r0, #3\n\
	bne _US_080DEE10\n\
	adds r0, r6, #0\n\
	bl GetEntityPalID\n\
	adds r1, r0, #0\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x13\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	movs r0, #0xf1\n\
	bl StartPaletteAnimation\n\
_US_080DEE10:\n\
	ldr r0, _US_080DEE54 @ =gSystemSavedata\n\
	adds r0, #0x48\n\
	ldrb r0, [r0]\n\
	cmp r0, #4\n\
	bne _US_080DEE34\n\
	adds r0, r6, #0\n\
	bl GetEntityPalID\n\
	adds r1, r0, #0\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x13\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	movs r0, #0xf2\n\
	bl StartPaletteAnimation\n\
_US_080DEE34:\n\
	movs r0, #0x95\n\
	lsls r0, r0, #1\n\
	bl PlaySound\n\
	ldr r0, _US_080DEE5C @ =gGameState\n\
	ldr r1, _US_080DEE60 @ =0x00060400\n\
	bl SetGameMode\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
	b _US_080DEEFC\n\
	.align 2, 0\n\
_US_080DEE4C: .4byte gInChat\n\
_US_080DEE50: .4byte gCollisionManager\n\
_US_080DEE54: .4byte gSystemSavedata\n\
_US_080DEE58: .4byte sMotions\n\
_US_080DEE5C: .4byte gGameState\n\
_US_080DEE60: .4byte 0x00060400\n\
_US_080DEE64:\n\
	movs r0, #0xf1\n\
	bl StepPaletteAnimation\n\
	movs r0, #0xf2\n\
	bl StepPaletteAnimation\n\
	ldr r0, _US_080DEF10 @ =gGameState\n\
	ldrb r7, [r0, #2]\n\
	movs r0, #0xb4\n\
	adds r0, r0, r6\n\
	mov r9, r0\n\
	cmp r7, #0\n\
	bne _US_080DEEFC\n\
	movs r0, #0xf1\n\
	bl RemovePaletteAnimation\n\
	movs r0, #0xf2\n\
	bl RemovePaletteAnimation\n\
	ldr r0, _US_080DEF14 @ =gSystemSavedata\n\
	adds r0, #0x48\n\
	mov r8, r0\n\
	ldrb r0, [r0]\n\
	cmp r0, #2\n\
	bls _US_080DEEE4\n\
	ldr r1, _US_080DEF18 @ =sMotions\n\
	mov r2, r8\n\
	ldrb r0, [r2]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r4, [r0]\n\
	lsrs r4, r4, #8\n\
	lsls r5, r4, #2\n\
	adds r5, r5, r4\n\
	lsls r5, r5, #2\n\
	ldr r1, _US_080DEF1C @ =gStaticMotionGraphics\n\
	adds r0, r5, r1\n\
	ldr r1, _US_080DEF20 @ =wStaticGraphicTilenums\n\
	lsls r4, r4, #1\n\
	adds r1, r4, r1\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl RequestGraphicTransfer\n\
	ldr r0, _US_080DEF24 @ =gStaticMotionGraphics+12\n\
	adds r5, r5, r0\n\
	ldr r0, _US_080DEF28 @ =wStaticMotionPalIDs\n\
	adds r4, r4, r0\n\
	ldrh r1, [r4]\n\
	ldrb r0, [r5, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r5, #0\n\
	bl LoadPalette\n\
_US_080DEEE4:\n\
	ldr r1, _US_080DEF18 @ =sMotions\n\
	mov r2, r8\n\
	ldrb r0, [r2]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldr r0, _US_080DEF2C @ =gInChat\n\
	strb r7, [r0]\n\
	strb r7, [r6, #0xd]\n\
_US_080DEEFC:\n\
	movs r0, #0\n\
	mov r1, r9\n\
	str r0, [r1]\n\
	pop {r3, r4}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_US_080DEF10: .4byte gGameState\n\
_US_080DEF14: .4byte gSystemSavedata\n\
_US_080DEF18: .4byte sMotions\n\
_US_080DEF1C: .4byte gStaticMotionGraphics\n\
_US_080DEF20: .4byte wStaticGraphicTilenums\n\
_US_080DEF24: .4byte gStaticMotionGraphics+12\n\
_US_080DEF28: .4byte wStaticMotionPalIDs\n\
_US_080DEF2C: .4byte gInChat\n\
.else\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	adds r6, r0, #0\n\
	bl UpdateEntityAnim\n\
	ldrb r0, [r6, #0xd]\n\
	cmp r0, #0\n\
	beq _080DF294\n\
	cmp r0, #1\n\
	beq _080DF358\n\
	b _080DF3EA\n\
_080DF294:\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	ldr r0, [r0]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #0x16\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080DF2A6\n\
	b _080DF3EA\n\
_080DF2A6:\n\
	ldr r0, _080DF340 @ =gInChat\n\
	ldrb r0, [r0]\n\
	cmp r0, #0\n\
	bne _080DF2B0\n\
	b _080DF3EA\n\
_080DF2B0:\n\
	ldr r0, _080DF344 @ =gCollisionManager\n\
	movs r1, #0xc5\n\
	lsls r1, r1, #3\n\
	adds r0, r0, r1\n\
	adds r1, r6, #0\n\
	adds r1, #0x74\n\
	ldr r0, [r0]\n\
	cmp r0, r1\n\
	beq _080DF2C4\n\
	b _080DF3EA\n\
_080DF2C4:\n\
	ldr r0, _080DF348 @ =gSystemSavedata\n\
	adds r4, r0, #0\n\
	adds r4, #0x48\n\
	ldrb r0, [r4]\n\
	cmp r0, #3\n\
	bhi _080DF302\n\
	ldr r1, _080DF34C @ =sMotions\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r0, [r0]\n\
	movs r1, #1\n\
	orrs r1, r0\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldrb r0, [r4]\n\
	cmp r0, #3\n\
	bne _080DF302\n\
	adds r0, r6, #0\n\
	bl GetEntityPalID\n\
	adds r1, r0, #0\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x13\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	movs r0, #0xf1\n\
	bl StartPaletteAnimation\n\
_080DF302:\n\
	ldr r0, _080DF348 @ =gSystemSavedata\n\
	adds r0, #0x48\n\
	ldrb r0, [r0]\n\
	cmp r0, #4\n\
	bne _080DF326\n\
	adds r0, r6, #0\n\
	bl GetEntityPalID\n\
	adds r1, r0, #0\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x13\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	movs r0, #0xf2\n\
	bl StartPaletteAnimation\n\
_080DF326:\n\
	movs r0, #0x95\n\
	lsls r0, r0, #1\n\
	bl PlaySound\n\
	ldr r0, _080DF350 @ =gGameState\n\
	ldr r1, _080DF354 @ =0x00060400\n\
	bl SetGameMode\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
	b _080DF3EA\n\
	.align 2, 0\n\
_080DF340: .4byte gInChat\n\
_080DF344: .4byte gCollisionManager\n\
_080DF348: .4byte gSystemSavedata\n\
_080DF34C: .4byte sMotions\n\
_080DF350: .4byte gGameState\n\
_080DF354: .4byte 0x00060400\n\
_080DF358:\n\
	movs r0, #0xf1\n\
	bl StepPaletteAnimation\n\
	movs r0, #0xf2\n\
	bl StepPaletteAnimation\n\
	ldr r0, _080DF3F4 @ =gGameState\n\
	ldrb r7, [r0, #2]\n\
	cmp r7, #0\n\
	bne _080DF3EA\n\
	movs r0, #0xf1\n\
	bl RemovePaletteAnimation\n\
	movs r0, #0xf2\n\
	bl RemovePaletteAnimation\n\
	ldr r0, _080DF3F8 @ =gSystemSavedata\n\
	adds r0, #0x48\n\
	mov r8, r0\n\
	ldrb r0, [r0]\n\
	cmp r0, #2\n\
	bls _080DF3D2\n\
	ldr r1, _080DF3FC @ =sMotions\n\
	mov r2, r8\n\
	ldrb r0, [r2]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r4, [r0]\n\
	lsrs r4, r4, #8\n\
	lsls r5, r4, #2\n\
	adds r5, r5, r4\n\
	lsls r5, r5, #2\n\
	ldr r1, _080DF400 @ =gStaticMotionGraphics\n\
	adds r0, r5, r1\n\
	ldr r1, _080DF404 @ =wStaticGraphicTilenums\n\
	lsls r4, r4, #1\n\
	adds r1, r4, r1\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl RequestGraphicTransfer\n\
	ldr r0, _080DF408 @ =gStaticMotionGraphics+12\n\
	adds r5, r5, r0\n\
	ldr r0, _080DF40C @ =wStaticMotionPalIDs\n\
	adds r4, r4, r0\n\
	ldrh r1, [r4]\n\
	ldrb r0, [r5, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r5, #0\n\
	bl LoadPalette\n\
_080DF3D2:\n\
	ldr r1, _080DF3FC @ =sMotions\n\
	mov r2, r8\n\
	ldrb r0, [r2]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r1, [r0]\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldr r0, _080DF410 @ =gInChat\n\
	strb r7, [r0]\n\
	strb r7, [r6, #0xd]\n\
_080DF3EA:\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080DF3F4: .4byte gGameState\n\
_080DF3F8: .4byte gSystemSavedata\n\
_080DF3FC: .4byte sMotions\n\
_080DF400: .4byte gStaticMotionGraphics\n\
_080DF404: .4byte wStaticGraphicTilenums\n\
_080DF408: .4byte gStaticMotionGraphics+12\n\
_080DF40C: .4byte wStaticMotionPalIDs\n\
_080DF410: .4byte gInChat\n\
.endif\n\
 .syntax divided\n");
}

static void CielComputer_Die(Object* p) { DeleteSolid((void*)p); }
