#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "physics.h"
#include "pickup.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "story.h"
#include "text_window.h"
#include "zero.h"

static const struct Collision sCollision;
extern const motion_t gMapItemMotions[9];
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED);

static void MapItem_Init(Pickup* p);
static void MapItem_Update(Pickup* p);
static void MapItem_Die(struct Entity* p);

// clang-format off
const PickupRoutine gPickupItemRoutine = {
    [ENTITY_INIT] =      (PickupFunc)MapItem_Init,
    [ENTITY_UPDATE] =    (PickupFunc)MapItem_Update,
    [ENTITY_DIE] =       (PickupFunc)MapItem_Die,
    [ENTITY_DISAPPEAR] = (PickupFunc)DeletePickup,
    [ENTITY_EXIT] =      (PickupFunc)DeleteEntity,
};
// clang-format on

NAKED struct Entity* CreatePickupItem(u8 itemID, Coords32* c, u8 param_3) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	lsls r0, r0, #0x18\n\
	lsrs r0, r0, #0x18\n\
	mov sl, r0\n\
	lsls r2, r2, #0x18\n\
	lsrs r2, r2, #0x18\n\
	mov sb, r2\n\
	ldr r5, [r1]\n\
	ldr r1, [r1, #4]\n\
	mov r8, r1\n\
	mov r7, r8\n\
	ldr r0, _080E09EC @ =gPickupHeaderPtr\n\
	ldr r1, [r0]\n\
	movs r2, #0xa\n\
	ldrsh r0, [r1, r2]\n\
	cmp r0, #2\n\
	bgt _080E09F0\n\
	movs r0, #0\n\
	b _080E0A76\n\
	.align 2, 0\n\
_080E09EC: .4byte gPickupHeaderPtr\n\
_080E09F0:\n\
	adds r0, r1, #0\n\
	bl AllocEntityLast\n\
	adds r4, r0, #0\n\
	cmp r4, #0\n\
	beq _080E0A74\n\
	adds r2, r4, #0\n\
	adds r2, #0x25\n\
	movs r1, #0\n\
	movs r0, #1\n\
	strb r0, [r2]\n\
	ldr r0, _080E0A38 @ =gPickupFnTable\n\
	strb r1, [r4, #9]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0]\n\
	str r0, [r4, #0x14]\n\
	movs r0, #0\n\
	strh r1, [r4, #0x20]\n\
	adds r1, r4, #0\n\
	adds r1, #0x22\n\
	strb r0, [r1]\n\
	ldrb r1, [r4, #0xb]\n\
	movs r0, #0x10\n\
	orrs r0, r1\n\
	strb r0, [r4, #0xb]\n\
	ldrb r0, [r4, #0x1c]\n\
	strb r0, [r4, #0x1d]\n\
	ldrb r0, [r4, #0x11]\n\
	cmp r0, #1\n\
	bls _080E0A3C\n\
	str r5, [r4, #0x54]\n\
	adds r0, r5, #0\n\
	mov r1, r8\n\
	bl FUN_08009f6c\n\
	b _080E0A6A\n\
	.align 2, 0\n\
_080E0A38: .4byte gPickupFnTable\n\
_080E0A3C:\n\
	adds r0, r5, #0\n\
	mov r1, r8\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _080E0A66\n\
	adds r0, r5, #0\n\
	mov r1, r8\n\
	bl FUN_08009f6c\n\
	str r0, [r4, #0x58]\n\
	cmp r0, r7\n\
	ble _080E0A62\n\
	adds r0, r5, #0\n\
	mov r1, r8\n\
	bl FUN_0800a134\n\
	str r0, [r4, #0x58]\n\
_080E0A62:\n\
	str r5, [r4, #0x54]\n\
	b _080E0A6C\n\
_080E0A66:\n\
	str r5, [r4, #0x54]\n\
	mov r0, r8\n\
_080E0A6A:\n\
	str r0, [r4, #0x58]\n\
_080E0A6C:\n\
	mov r2, sl\n\
	strb r2, [r4, #0x10]\n\
	mov r0, sb\n\
	strb r0, [r4, #0x11]\n\
_080E0A74:\n\
	adds r0, r4, #0\n\
_080E0A76:\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r1}\n\
	bx r1\n\
 .syntax divided\n");
}

NON_MATCH_AP static void MapItem_Init(Pickup* p) {
#if MODERN || AP
  motion_t m;

  if ((u8)(p->work[0] - ITEM_SUBTANK1) <= 1) {
    const ColorGraphic* cg;
    s32 n = 0;
    if (p->work[0] == ITEM_SUBTANK2) {
      n = 1;
    }
#if AP
    // The taken flag stops the pickup coming back when you re enter the stage
    if (gGameState.save.unused_240[AP_TAKEN_BYTE] & (AP_TAKEN_SUBTANK1 << n)) {
#else
    if (pZero2->unk_b4.status.subtankHP[n] != 0xFF) {
#endif
      p->flags &= ~DISPLAY;
      p->flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    cg = &gStaticMotionGraphics[SM229_SUBTANK];
    LoadGraphic(&cg->g, (void*)(BG_VRAM_SIZE + ((wStaticGraphicTilenums[SM229_SUBTANK] - cg->g.tileId) << 5)));
    LoadPalette(&cg->pal, 0x200 + ((wStaticMotionPalIDs[SM229_SUBTANK] - cg->pal.dst) << 5));
  }

  m = gMapItemMotions[p->work[0]];
  if (p->work[0] <= ITEM_LIFE_L) {
    m += gSystemSavedata.lifeEnergy << 8;
  } else if (p->work[0] <= ITEM_EC_L) {
    m += gSystemSavedata.crystal << 8;
  } else if (p->work[0] == ITEM_EXLIFE) {
    m += gSystemSavedata.extraLife << 8;
  }

  InitNonAffineMotion((void*)p);
  SetSpriteAnimation(p, m);
  p->flags |= DISPLAY;
  p->flags |= FLIPABLE;
  INIT_BODY(p, &sCollision, 64, onCollision);
  p->y = (p->coord).y;
  p->z = NULL;

  if (p->work[1] >= 2) {
    (p->d).y = PIXEL(0);
  } else {
    (p->d).y = -PIXEL(4);
  }
  p->work[2] = 240;
#if AP
  /* Marks the pickup as an unchecked Archipelago location (orbiting logo). */
  if (p->work[0] == ITEM_EXLIFE) {
    ApSpawnExLifeOrbit(p);
  }
#endif
  SET_ITEM_ROUTINE(p, ENTITY_UPDATE);
  MapItem_Update(p);
#else
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldrb r1, [r6, #0x10]\n\
	subs r0, r1, #7\n\
	lsls r0, r0, #0x18\n\
	lsrs r0, r0, #0x18\n\
	cmp r0, #1\n\
	bhi _080E0B2A\n\
	ldr r0, _080E0AE4 @ =pZero2\n\
	ldr r0, [r0]\n\
	movs r2, #0\n\
	cmp r1, #8\n\
	bne _080E0AA0\n\
	movs r2, #1\n\
_080E0AA0:\n\
	adds r0, #0xbc\n\
	adds r0, r0, r2\n\
	ldrb r0, [r0]\n\
	cmp r0, #0xff\n\
	beq _080E0AEC\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	ldr r1, _080E0AE8 @ =gPickupFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r6, #0x14]\n\
	b _080E0BFC\n\
	.align 2, 0\n\
_080E0AE4: .4byte pZero2\n\
_080E0AE8: .4byte gPickupFnTable\n\
_080E0AEC:\n\
	ldr r4, _080E0B40 @ =0x000011E4\n\
	ldr r1, _080E0B44 @ =gStaticMotionGraphics\n\
	adds r0, r4, r1\n\
	ldr r1, _080E0B48 @ =wStaticGraphicTilenums\n\
	movs r5, #0xe5\n\
	lsls r5, r5, #1\n\
	adds r1, r1, r5\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl LoadGraphic\n\
	ldr r0, _080E0B4C @ =gStaticMotionGraphics+12\n\
	adds r4, r4, r0\n\
	ldr r0, _080E0B50 @ =wStaticMotionPalIDs\n\
	adds r0, r0, r5\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
_080E0B2A:\n\
	ldr r2, _080E0B54 @ =gMapItemMotions\n\
	ldrb r1, [r6, #0x10]\n\
	lsls r0, r1, #1\n\
	adds r0, r0, r2\n\
	ldrh r4, [r0]\n\
	cmp r1, #2\n\
	bhi _080E0B5C\n\
	ldr r0, _080E0B58 @ =gSystemSavedata\n\
	adds r0, #0x49\n\
	b _080E0B74\n\
	.align 2, 0\n\
_080E0B40: .4byte 0x000011E4\n\
_080E0B44: .4byte gStaticMotionGraphics\n\
_080E0B48: .4byte wStaticGraphicTilenums\n\
_080E0B4C: .4byte gStaticMotionGraphics+12\n\
_080E0B50: .4byte wStaticMotionPalIDs\n\
_080E0B54: .4byte gMapItemMotions\n\
_080E0B58: .4byte gSystemSavedata\n\
_080E0B5C:\n\
	cmp r1, #4\n\
	bhi _080E0B6C\n\
	ldr r0, _080E0B68 @ =gSystemSavedata\n\
	adds r0, #0x4a\n\
	b _080E0B74\n\
	.align 2, 0\n\
_080E0B68: .4byte gSystemSavedata\n\
_080E0B6C:\n\
	cmp r1, #5\n\
	bne _080E0B7E\n\
	ldr r0, _080E0BD0 @ =gSystemSavedata\n\
	adds r0, #0x4c\n\
_080E0B74:\n\
	ldrb r0, [r0]\n\
	lsls r0, r0, #8\n\
	adds r0, r4, r0\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
_080E0B7E:\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	adds r0, r6, #0\n\
	adds r1, r4, #0\n\
	bl SetMotion\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _080E0BD4 @ =sCollision\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0x40\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	ldr r0, _080E0BD8 @ =onCollision\n\
	str r0, [r4, #0x24]\n\
	adds r1, r6, #0\n\
	adds r1, #0xb4\n\
	ldr r0, [r6, #0x58]\n\
	str r0, [r1]\n\
	adds r0, r6, #0\n\
	adds r0, #0xb8\n\
	str r5, [r0]\n\
	ldrb r0, [r6, #0x11]\n\
	cmp r0, #1\n\
	bls _080E0BDC\n\
	str r5, [r6, #0x60]\n\
	b _080E0BE0\n\
	.align 2, 0\n\
_080E0BD0: .4byte gSystemSavedata\n\
_080E0BD4: .4byte sCollision\n\
_080E0BD8: .4byte onCollision\n\
_080E0BDC:\n\
	ldr r0, _080E0C04 @ =0xFFFFFC00\n\
	str r0, [r6, #0x60]\n\
_080E0BE0:\n\
	movs r0, #0xf0\n\
	strb r0, [r6, #0x12]\n\
	ldr r1, _080E0C08 @ =gPickupFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	adds r0, r6, #0\n\
	bl MapItem_Update\n\
_080E0BFC:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080E0C04: .4byte 0xFFFFFC00\n\
_080E0C08: .4byte gPickupFnTable\n\
 .syntax divided\n");
#endif
}

NON_MATCH_AP static void MapItem_Update(Pickup* p) {
#if MODERN || AP
  UpdateSpriteAnimation(p);

  // 消滅間際は点滅させる
  if (p->work[1] == 0) {
    u8 t = --p->work[2];
    if (t <= 0x3b) {
      if (t & 2) {
        p->flags |= DISPLAY;
      } else {
        p->flags &= ~DISPLAY;
      }
    }
  }

  if (((p->body).status & BODY_STATUS_B2) && (p->z != NULL)) {
    // ゼロが拾った (バイッスが有効なら取得量2倍)
    if (p->work[0] == ITEM_LIFE_S) {
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) gLifeRecoverAmount += 0x10;
      gLifeRecoverAmount += 0x10;
    } else if (p->work[0] == ITEM_LIFE_M) {
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) gLifeRecoverAmount += 0x20;
      gLifeRecoverAmount += 0x20;
    } else if (p->work[0] == ITEM_LIFE_L) {
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) gLifeRecoverAmount += 0x100;
      gLifeRecoverAmount += 0x100;
    } else if (p->work[0] == ITEM_EC_S) {
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) gECrystalGainAmount += 4;
      gECrystalGainAmount += 4;
    } else if (p->work[0] == ITEM_EC_L) {
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) gECrystalGainAmount += 0x10;
      gECrystalGainAmount += 0x10;
    } else if (p->work[0] == ITEM_EXLIFE) {
#if AP
      // One location per stage. Dropped 1-UPs carry work[1] = 0 and are not locations.
      if (p->work[1] >= 2) {
        ApMarkLocationChecked((u16)(AP_LOC_EXLIFE_FIRST + gStageRun.id));
      }
#endif
      if (FLAG(gCurStory.s.gameflags, BYSE_ENABLED)) {
        if ((gScore.total)->extraLife <= 8) (gScore.total)->extraLife++;
      }
      if ((gScore.total)->extraLife <= 8) (gScore.total)->extraLife++;
      PlaySound(SE_NOTIFICATION);
    } else if (p->work[0] == ITEM_SUBTANK1) {
#if AP
      ApMarkLocationChecked(AP_LOC_SUBTANK_1);
      gGameState.save.unused_240[AP_TAKEN_BYTE] |= AP_TAKEN_SUBTANK1;
#else
      ((&pZero2->unk_b4)->status).subtankHP[0] = 0;
      PrintTextWindow(0x102, 0x5A);
#endif
    } else if (p->work[0] == ITEM_SUBTANK2) {
#if AP
      ApMarkLocationChecked(AP_LOC_SUBTANK_2);
      gGameState.save.unused_240[AP_TAKEN_BYTE] |= AP_TAKEN_SUBTANK2;
#else
      ((&pZero2->unk_b4)->status).subtankHP[1] = 0;
      PrintTextWindow(0x102, 0x5A);
#endif
    }

    p->flags &= ~DISPLAY;
    p->flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    // 寿命切れ or 画面から離れすぎたら消す
    if ((p->work[2] == 0) || (Camera_GetDistance(&gStageRun.vm.camera, &p->coord) > PIXEL(128))) {
      SET_ITEM_ROUTINE(p, ENTITY_DIE);
    }

    if (p->mode[1] == 0) {
      // 落下中
      if ((p->coord.y >= p->y) && (FUN_080098a4(p->coord.x, p->coord.y) != 0)) {
        p->coord.y = FUN_08009f6c(p->coord.x, p->coord.y);
        p->d.y = 0;
        p->mode[1]++;
      } else if (FUN_080098a4(p->coord.x, p->y) != 0) {
        if (FUN_08009f6c(p->coord.x, p->y) < p->coord.y - PIXEL(7)) {
          p->y = FUN_0800a134(p->coord.x, p->y);
        }
      }
      p->coord.y += p->d.y;
      if (p->d.y < PIXEL(7)) p->d.y += 0x40;
    } else {
      // 着地後、地形に沿って移動する
      s32 y = FUN_08009f6c(p->coord.x, p->coord.y);
      s32 dx;
      if (y < p->coord.y) {
        p->coord.y = y;
        p->d.y = 0;
      } else if (y > p->coord.y) {
        if (p->d.y == 0) {
          if (y > p->coord.y + PIXEL(7)) {
            p->d.y = 0x40;
            p->coord.y += 0x40;
          } else {
            p->coord.y = y;
          }
        } else {
          if (p->d.y < PIXEL(7)) p->d.y += 0x40;
          p->coord.y += p->d.y;
        }
      }

      dx = FUN_0800a40c(p->coord.x, p->coord.y + PIXEL(4));
      if (dx != 0) {
        if (FUN_080098a4(p->coord.x + dx, p->coord.y - PIXEL(4)) == 0) {
          p->coord.x += dx;
        }
      }
    }
  }
#else
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r4, r0, #0\n\
	bl UpdateEntityAnim\n\
	ldrb r0, [r4, #0x11]\n\
	cmp r0, #0\n\
	bne _080E0C40\n\
	ldrb r0, [r4, #0x12]\n\
	subs r1, r0, #1\n\
	strb r1, [r4, #0x12]\n\
	lsls r0, r1, #0x18\n\
	lsrs r0, r0, #0x18\n\
	cmp r0, #0x3b\n\
	bhi _080E0C40\n\
	movs r0, #2\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	beq _080E0C38\n\
	ldrb r0, [r4, #0xa]\n\
	movs r1, #1\n\
	orrs r0, r1\n\
	b _080E0C3E\n\
_080E0C38:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
_080E0C3E:\n\
	strb r0, [r4, #0xa]\n\
_080E0C40:\n\
	adds r0, r4, #0\n\
	adds r0, #0x8c\n\
	ldr r1, [r0]\n\
	movs r2, #4\n\
	ands r1, r2\n\
	adds r5, r0, #0\n\
	cmp r1, #0\n\
	bne _080E0C52\n\
	b _080E0DD4\n\
_080E0C52:\n\
	adds r0, #0x2c\n\
	ldr r0, [r0]\n\
	cmp r0, #0\n\
	bne _080E0C5C\n\
	b _080E0DD4\n\
_080E0C5C:\n\
	ldrb r0, [r4, #0x10]\n\
	cmp r0, #0\n\
	bne _080E0C78\n\
	ldr r0, _080E0C70 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r1, _080E0C74 @ =gLifeRecoverAmount\n\
	b _080E0D06\n\
	.align 2, 0\n\
_080E0C70: .4byte gCurStory\n\
_080E0C74: .4byte gLifeRecoverAmount\n\
_080E0C78:\n\
	cmp r0, #1\n\
	bne _080E0CA0\n\
	ldr r0, _080E0C98 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r1, _080E0C9C @ =gLifeRecoverAmount\n\
	cmp r0, #0\n\
	beq _080E0C90\n\
	ldr r0, [r1]\n\
	adds r0, #0x20\n\
	str r0, [r1]\n\
_080E0C90:\n\
	ldr r0, [r1]\n\
	adds r0, #0x20\n\
	str r0, [r1]\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0C98: .4byte gCurStory\n\
_080E0C9C: .4byte gLifeRecoverAmount\n\
_080E0CA0:\n\
	cmp r0, #2\n\
	bne _080E0CD0\n\
	ldr r0, _080E0CC8 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r1, _080E0CCC @ =gLifeRecoverAmount\n\
	cmp r0, #0\n\
	beq _080E0CBC\n\
	ldr r0, [r1]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #1\n\
	adds r0, r0, r2\n\
	str r0, [r1]\n\
_080E0CBC:\n\
	ldr r0, [r1]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #1\n\
	adds r0, r0, r2\n\
	str r0, [r1]\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0CC8: .4byte gCurStory\n\
_080E0CCC: .4byte gLifeRecoverAmount\n\
_080E0CD0:\n\
	cmp r0, #3\n\
	bne _080E0CF8\n\
	ldr r0, _080E0CF0 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r1, _080E0CF4 @ =gECrystalGainAmount\n\
	cmp r0, #0\n\
	beq _080E0CE8\n\
	ldr r0, [r1]\n\
	adds r0, #4\n\
	str r0, [r1]\n\
_080E0CE8:\n\
	ldr r0, [r1]\n\
	adds r0, #4\n\
	str r0, [r1]\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0CF0: .4byte gCurStory\n\
_080E0CF4: .4byte gECrystalGainAmount\n\
_080E0CF8:\n\
	cmp r0, #4\n\
	bne _080E0D20\n\
	ldr r0, _080E0D18 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r1, _080E0D1C @ =gECrystalGainAmount\n\
_080E0D06:\n\
	cmp r0, #0\n\
	beq _080E0D10\n\
	ldr r0, [r1]\n\
	adds r0, #0x10\n\
	str r0, [r1]\n\
_080E0D10:\n\
	ldr r0, [r1]\n\
	adds r0, #0x10\n\
	str r0, [r1]\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0D18: .4byte gCurStory\n\
_080E0D1C: .4byte gECrystalGainAmount\n\
_080E0D20:\n\
	cmp r0, #5\n\
	bne _080E0D5C\n\
	ldr r0, _080E0D54 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	ldr r2, _080E0D58 @ =gScore\n\
	cmp r0, #0\n\
	beq _080E0D3E\n\
	ldr r1, [r2]\n\
	ldrb r0, [r1]\n\
	cmp r0, #8\n\
	bhi _080E0D4A\n\
	adds r0, #1\n\
	strb r0, [r1]\n\
_080E0D3E:\n\
	ldr r1, [r2]\n\
	ldrb r0, [r1]\n\
	cmp r0, #8\n\
	bhi _080E0D4A\n\
	adds r0, #1\n\
	strb r0, [r1]\n\
_080E0D4A:\n\
	movs r0, #6\n\
	bl PlaySound\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0D54: .4byte gCurStory\n\
_080E0D58: .4byte gScore\n\
_080E0D5C:\n\
	cmp r0, #7\n\
	bne _080E0D7C\n\
	ldr r0, _080E0D78 @ =pZero2\n\
	ldr r0, [r0]\n\
	adds r0, #0xb4\n\
	movs r1, #0\n\
	strb r1, [r0, #8]\n\
	movs r0, #0x81\n\
	lsls r0, r0, #1\n\
	movs r1, #0x5a\n\
	bl PrintTextWindow\n\
	b _080E0D94\n\
	.align 2, 0\n\
_080E0D78: .4byte pZero2\n\
_080E0D7C:\n\
	cmp r0, #8\n\
	bne _080E0D94\n\
	ldr r0, _080E0DCC @ =pZero2\n\
	ldr r0, [r0]\n\
	adds r0, #0xb4\n\
	movs r1, #0\n\
	strb r1, [r0, #9]\n\
	movs r0, #0x81\n\
	lsls r0, r0, #1\n\
	movs r1, #0x5a\n\
	bl PrintTextWindow\n\
_080E0D94:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
	str r2, [r5]\n\
	adds r0, r4, #0\n\
	adds r0, #0x90\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
	ldr r1, _080E0DD0 @ =gPickupFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r4, #0x14]\n\
	b _080E0F08\n\
	.align 2, 0\n\
_080E0DCC: .4byte pZero2\n\
_080E0DD0: .4byte gPickupFnTable\n\
_080E0DD4:\n\
	ldrb r0, [r4, #0x12]\n\
	cmp r0, #0\n\
	beq _080E0DEC\n\
	ldr r0, _080E0E38 @ =gStageRun+232\n\
	adds r1, r4, #0\n\
	adds r1, #0x54\n\
	bl Camera_GetDistance\n\
	movs r1, #0x80\n\
	lsls r1, r1, #8\n\
	cmp r0, r1\n\
	bls _080E0DFE\n\
_080E0DEC:\n\
	ldr r1, _080E0E3C @ =gPickupFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r4, #0x14]\n\
_080E0DFE:\n\
	ldrb r6, [r4, #0xd]\n\
	cmp r6, #0\n\
	bne _080E0E8C\n\
	adds r0, r4, #0\n\
	adds r0, #0xb4\n\
	ldr r2, [r4, #0x58]\n\
	ldr r1, [r0]\n\
	adds r5, r0, #0\n\
	cmp r2, r1\n\
	blt _080E0E40\n\
	ldr r0, [r4, #0x54]\n\
	adds r1, r2, #0\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _080E0E40\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	bl FUN_08009f6c\n\
	adds r1, r0, #0\n\
	str r1, [r4, #0x58]\n\
	str r6, [r4, #0x60]\n\
	ldrb r0, [r4, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xd]\n\
	b _080E0E6C\n\
	.align 2, 0\n\
_080E0E38: .4byte gStageRun+232\n\
_080E0E3C: .4byte gPickupFnTable\n\
_080E0E40:\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r5]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _080E0E6C\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r5]\n\
	bl FUN_08009f6c\n\
	adds r1, r0, #0\n\
	ldr r0, [r4, #0x58]\n\
	ldr r2, _080E0E84 @ =0xFFFFF900\n\
	adds r0, r0, r2\n\
	cmp r1, r0\n\
	bge _080E0E6C\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r5]\n\
	bl FUN_0800a134\n\
	str r0, [r5]\n\
_080E0E6C:\n\
	ldr r0, [r4, #0x58]\n\
	ldr r1, [r4, #0x60]\n\
	adds r0, r0, r1\n\
	str r0, [r4, #0x58]\n\
	ldr r0, _080E0E88 @ =0x000006FF\n\
	cmp r1, r0\n\
	bgt _080E0F08\n\
	adds r0, r1, #0\n\
	adds r0, #0x40\n\
	str r0, [r4, #0x60]\n\
	b _080E0F08\n\
	.align 2, 0\n\
_080E0E84: .4byte 0xFFFFF900\n\
_080E0E88: .4byte 0x000006FF\n\
_080E0E8C:\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	bl FUN_08009f6c\n\
	adds r2, r0, #0\n\
	ldr r3, [r4, #0x58]\n\
	cmp r2, r3\n\
	bge _080E0EA4\n\
	str r2, [r4, #0x58]\n\
	movs r0, #0\n\
	str r0, [r4, #0x60]\n\
	b _080E0EDA\n\
_080E0EA4:\n\
	cmp r2, r3\n\
	ble _080E0EDA\n\
	ldr r1, [r4, #0x60]\n\
	cmp r1, #0\n\
	bne _080E0EC6\n\
	movs r1, #0xe0\n\
	lsls r1, r1, #3\n\
	adds r0, r3, r1\n\
	cmp r2, r0\n\
	ble _080E0EC2\n\
	movs r0, #0x40\n\
	str r0, [r4, #0x60]\n\
	adds r0, r3, #0\n\
	adds r0, #0x40\n\
	b _080E0ED8\n\
_080E0EC2:\n\
	str r2, [r4, #0x58]\n\
	b _080E0EDA\n\
_080E0EC6:\n\
	ldr r0, _080E0F10 @ =0x000006FF\n\
	cmp r1, r0\n\
	bgt _080E0ED2\n\
	adds r0, r1, #0\n\
	adds r0, #0x40\n\
	str r0, [r4, #0x60]\n\
_080E0ED2:\n\
	ldr r0, [r4, #0x58]\n\
	ldr r1, [r4, #0x60]\n\
	adds r0, r0, r1\n\
_080E0ED8:\n\
	str r0, [r4, #0x58]\n\
_080E0EDA:\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #3\n\
	adds r1, r1, r2\n\
	bl FUN_0800a40c\n\
	adds r5, r0, #0\n\
	cmp r5, #0\n\
	beq _080E0F08\n\
	ldr r0, [r4, #0x54]\n\
	adds r0, r0, r5\n\
	ldr r1, [r4, #0x58]\n\
	ldr r2, _080E0F14 @ =0xFFFFFC00\n\
	adds r1, r1, r2\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	bne _080E0F08\n\
	ldr r0, [r4, #0x54]\n\
	adds r0, r0, r5\n\
	str r0, [r4, #0x54]\n\
_080E0F08:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080E0F10: .4byte 0x000006FF\n\
_080E0F14: .4byte 0xFFFFFC00\n\
 .syntax divided\n");
#endif
}

static void MapItem_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_ITEM_ROUTINE(p, ENTITY_EXIT);
}

static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  Pickup* p = (Pickup*)body->parent;
  struct Entity* q = body->enemy->parent;
  if (q->kind == ENTITY_PLAYER) {
    p->z = (void*)q;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

// clang-format off
const motion_t gMapItemMotions[9] = {
    MOTION(SM167_LIFE_ENERGY, 0),
    MOTION(SM167_LIFE_ENERGY, 1),
    MOTION(SM167_LIFE_ENERGY, 2),
    MOTION(SM170_ECRYSTAL, 3),
    MOTION(SM170_ECRYSTAL, 4),
    MOTION(SM173_EXLIFE, 9),
    MOTION(SM176_RESULT_DISK, 11),
    MOTION(SM229_SUBTANK, 0),
    MOTION(SM229_SUBTANK, 0),
};
// clang-format on

static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 255,
  layer : 0x00000001,
  range : {PIXEL(0), -PIXEL(6), PIXEL(12), PIXEL(12)},
};
