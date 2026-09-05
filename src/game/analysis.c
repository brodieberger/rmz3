#include "disk.h"
#include "anim_loader.h"
#include "syssav.h"
#include "gpu_regs.h"
#include "input.h"
#include "widget/cursor_square.h"
#include "cyberelf.h"
#include "zero.h"
#include "definition.h"
#include "stagerun.h"
#include "game.h"
#include "global.h"
#include "palette_animation.h"
#include "text.h"
#include "widget.h"

// "シークレットディスクのカイセキ"のシーン

typedef void (*DiskLoopFunc)(struct GameState*);

void ResetPivot(struct Pivot* p, Coords32* c, u32 _, void* nullVal);

static const DiskLoopFunc sDiskLoops[5];

static void DiskLoop_Init(struct GameState* g);
static void DiskLoop_OpenScreen(struct GameState* g);
static void DiskLoop_Run(struct GameState* g);
static void DiskLoop_BlackOut(struct GameState* g);
static void DiskLoop_Exit(struct GameState* g);

static void sd_analysis_080f8408(struct GameState* g);
extern const DiskLoopFunc PTR_ARRAY_083864ac[3];
u16 OpenSecretDisk(struct GameState* g, u8 disk_no, bool8 is_result);
extern const struct SecretDiskEntry gSecretDiskEntries[DISK_COUNT];
extern const u16 DiskECrystalAmounts[16];

void MainLoop_Disk(struct GameState* g) {
  sDiskLoops[g->mode[1]](g);
  sd_analysis_080f8408(g);
  return;
}

static void sd_analysis_080f83ac(struct GameState* g);
static void setSecretDiskPalette(struct GameState* g);

NON_MATCH static void DiskLoop_Init(struct GameState* g) {
#if MODERN || CBODY
  struct SecretDiskState* d;
  u16* pal;
  u16* src;
  u8 i;

  g->frames = 0;
  d = &g->sceneState.disk;
  d->cursorDisk = 0;
  d->scrollRow = 0;
  d->unk_0d = 0;
  d->winHalfW = 0;
  d->winHalfH = 0;
  d->colorR = 0;
  d->colorG = 0;
  d->colorB = 0;
  sd_analysis_080f83ac(g);

  gVideoRegBuffer.dispcnt &= ~DISPCNT_BGMODE_MASK;
  gVideoRegBuffer.dispcnt &= ~DISPCNT_BG_ALL_ON;
  gVideoRegBuffer.dispcnt |= (DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON);
  BGCNT16(1) = 0x4206;
  RESET_BGOFS(1);
  gBlendRegBuffer.bldclt = 0x2010;

  LoadGraphic(BG_GRAPHIC(22), (void*)0x4000);
  LoadPalette(BG_PALETTE(22), 0);
  CopyBgMap(g->menuBgMap1, SELF_REL_PTR(&gBgMapOffsets[101]), 0, 0);

  if (gSystemSavedata.disk == 1) {
    LoadGraphic(BG_GRAPHIC(36), CHAR_BASE(1));
    LoadPalette(BG_PALETTE(36), 0);
  } else if (gSystemSavedata.disk == 2) {
    LoadGraphic(BG_GRAPHIC(37), CHAR_BASE(1));
    LoadPalette(BG_PALETTE(37), 0);
  }

  setSecretDiskPalette(g);
  LOAD_STATIC_GRAPHIC(14);
  LOAD_STATIC_GRAPHIC(83);

  CreateTriangleCursor(g, 3);
  CreateTriangleCursor(g, 4);
  createSecretDiskModalBorder(g, 0);
  createSecretDiskModalBorder(g, 1);
  createSecretDiskModalBorder(g, 2);
  createSecretDiskModalBorder(g, 3);
  StartPaletteAnimation(0x40, 0);

  pal = &gPaletteManager.buf[144];
  src = pal - 16;
  for (i = 0; i <= 0xF; i++) {
    pal[i] = src[i];
  }

  RequestBgMapTransfer(g->menuBgMap1, (void*)SCREEN_BASE(1), 0x1000);
  g->mode[1] = 1;
  DiskLoop_OpenScreen(g);
#else
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	adds r7, r0, #0\n\
	movs r4, #0\n\
	movs r5, #0\n\
	strh r5, [r7, #4]\n\
	ldr r1, _080F7E2C @ =0x00000DCC\n\
	adds r0, r7, r1\n\
	strb r4, [r0, #0xa]\n\
	strb r4, [r0, #0xb]\n\
	strb r4, [r0, #0xd]\n\
	strb r4, [r0, #0xe]\n\
	strb r4, [r0, #0xf]\n\
	strb r4, [r0, #0x10]\n\
	strb r4, [r0, #0x11]\n\
	strb r4, [r0, #0x12]\n\
	adds r0, r7, #0\n\
	bl sd_analysis_080f83ac\n\
	ldr r4, _080F7E30 @ =gVideoRegBuffer\n\
	ldrh r1, [r4]\n\
	ldr r0, _080F7E34 @ =0x0000FFF8\n\
	ands r0, r1\n\
	ldr r1, _080F7E38 @ =0x0000F0FF\n\
	ands r0, r1\n\
	movs r2, #0x98\n\
	lsls r2, r2, #5\n\
	adds r1, r2, #0\n\
	orrs r0, r1\n\
	strh r0, [r4]\n\
	ldr r1, _080F7E3C @ =0x00004206\n\
	adds r0, r1, #0\n\
	strh r0, [r4, #6]\n\
	str r5, [r4, #0x10]\n\
	ldr r1, _080F7E40 @ =gBlendRegBuffer\n\
	ldr r0, _080F7E44 @ =0x00002010\n\
	strh r0, [r1]\n\
	ldr r0, _080F7E48 @ =gGraphic_Capcom+(22*20)\n\
	movs r5, #0xc\n\
	movs r1, #0x80\n\
	lsls r1, r1, #7\n\
	bl LoadGraphic\n\
	ldr r0, _080F7E4C @ =gGraphic_Capcom+(22*20)+12\n\
	movs r1, #0\n\
	bl LoadPalette\n\
	ldr r2, _080F7E50 @ =0x00000ED8\n\
	adds r0, r7, r2\n\
	ldr r2, _080F7E54 @ =gBgMapOffsets+(101*4)\n\
	ldr r1, [r2]\n\
	adds r1, r1, r2\n\
	movs r2, #0\n\
	movs r3, #0\n\
	bl CopyBgMap\n\
	ldr r0, _080F7E58 @ =gSystemSavedata\n\
	adds r0, #0x4b\n\
	ldrb r0, [r0]\n\
	cmp r0, #1\n\
	bne _080F7E64\n\
	ldr r0, _080F7E5C @ =gGraphic_Capcom+(36*20)\n\
	ldrh r2, [r4, #6]\n\
	adds r1, r5, #0\n\
	ands r1, r2\n\
	lsls r1, r1, #0xc\n\
	bl LoadGraphic\n\
	ldr r0, _080F7E60 @ =gGraphic_Capcom+(36*20)+12\n\
	movs r1, #0\n\
	bl LoadPalette\n\
	b _080F7E7E\n\
	.align 2, 0\n\
_080F7E2C: .4byte 0x00000DCC\n\
_080F7E30: .4byte gVideoRegBuffer\n\
_080F7E34: .4byte 0x0000FFF8\n\
_080F7E38: .4byte 0x0000F0FF\n\
_080F7E3C: .4byte 0x00004206\n\
_080F7E40: .4byte gBlendRegBuffer\n\
_080F7E44: .4byte 0x00002010\n\
_080F7E48: .4byte gGraphic_Capcom+(22*20)\n\
_080F7E4C: .4byte gGraphic_Capcom+(22*20)+12\n\
_080F7E50: .4byte 0x00000ED8\n\
_080F7E54: .4byte gBgMapOffsets+(101*4)\n\
_080F7E58: .4byte gSystemSavedata\n\
_080F7E5C: .4byte gGraphic_Capcom+(36*20)\n\
_080F7E60: .4byte gGraphic_Capcom+(36*20)+12\n\
_080F7E64:\n\
	cmp r0, #2\n\
	bne _080F7E7E\n\
	ldr r0, _080F7F78 @ =gGraphic_Capcom+(36*20)+20\n\
	ldrh r2, [r4, #6]\n\
	adds r1, r5, #0\n\
	ands r1, r2\n\
	lsls r1, r1, #0xc\n\
	bl LoadGraphic\n\
	ldr r0, _080F7F7C @ =gGraphic_Capcom+(36*20)+32\n\
	movs r1, #0\n\
	bl LoadPalette\n\
_080F7E7E:\n\
	adds r0, r7, #0\n\
	bl setSecretDiskPalette\n\
	movs r4, #0x8c\n\
	lsls r4, r4, #1\n\
	ldr r0, _080F7F80 @ =gStaticMotionGraphics\n\
	mov r8, r0\n\
	adds r0, r4, r0\n\
	ldr r6, _080F7F84 @ =wStaticGraphicTilenums\n\
	ldrh r1, [r6, #0x1c]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl LoadGraphic\n\
	ldr r0, _080F7F88 @ =gStaticMotionGraphics+12\n\
	mov sl, r0\n\
	add r4, sl\n\
	ldr r5, _080F7F8C @ =wStaticMotionPalIDs\n\
	ldrh r1, [r5, #0x1c]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	mov sb, r2\n\
	add r1, sb\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r4, _080F7F90 @ =0x0000067C\n\
	add r8, r4\n\
	adds r6, #0xa6\n\
	ldrh r1, [r6]\n\
	mov r2, r8\n\
	ldrh r0, [r2, #6]\n\
	lsrs r0, r0, #6\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	adds r1, r1, r0\n\
	mov r0, r8\n\
	bl LoadGraphic\n\
	add r4, sl\n\
	adds r5, #0xa6\n\
	ldrh r1, [r5]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	add r1, sb\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	adds r0, r7, #0\n\
	movs r1, #3\n\
	bl CreateTriangleCursor\n\
	adds r0, r7, #0\n\
	movs r1, #4\n\
	bl CreateTriangleCursor\n\
	adds r0, r7, #0\n\
	movs r1, #0\n\
	bl createSecretDiskModalBorder\n\
	adds r0, r7, #0\n\
	movs r1, #1\n\
	bl createSecretDiskModalBorder\n\
	adds r0, r7, #0\n\
	movs r1, #2\n\
	bl createSecretDiskModalBorder\n\
	adds r0, r7, #0\n\
	movs r1, #3\n\
	bl createSecretDiskModalBorder\n\
	movs r0, #0x40\n\
	movs r1, #0\n\
	bl StartPaletteAnimation\n\
	movs r2, #0\n\
	ldr r3, _080F7F94 @ =0x03002BE0\n\
	adds r4, r3, #0\n\
	subs r4, #0x20\n\
_080F7F34:\n\
	lsls r0, r2, #1\n\
	adds r1, r0, r3\n\
	adds r0, r0, r4\n\
	ldrh r0, [r0]\n\
	strh r0, [r1]\n\
	adds r0, r2, #1\n\
	lsls r0, r0, #0x18\n\
	lsrs r2, r0, #0x18\n\
	cmp r2, #0xf\n\
	bls _080F7F34\n\
	ldr r1, _080F7F98 @ =0x00000ED8\n\
	adds r0, r7, r1\n\
	ldr r1, _080F7F9C @ =gVideoRegBuffer+6\n\
	ldrh r2, [r1]\n\
	movs r1, #0xf8\n\
	lsls r1, r1, #5\n\
	ands r1, r2\n\
	lsls r1, r1, #3\n\
	movs r2, #0x80\n\
	lsls r2, r2, #5\n\
	bl RequestBgMapTransfer\n\
	movs r0, #1\n\
	strb r0, [r7, #1]\n\
	adds r0, r7, #0\n\
	bl DiskLoop_OpenScreen\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080F7F78: .4byte gGraphic_Capcom+(36*20)+20\n\
_080F7F7C: .4byte gGraphic_Capcom+(36*20)+32\n\
_080F7F80: .4byte gStaticMotionGraphics\n\
_080F7F84: .4byte wStaticGraphicTilenums\n\
_080F7F88: .4byte gStaticMotionGraphics+12\n\
_080F7F8C: .4byte wStaticMotionPalIDs\n\
_080F7F90: .4byte 0x0000067C\n\
_080F7F94: .4byte gPaletteManager+(144*2)\n\
_080F7F98: .4byte 0x00000ED8\n\
_080F7F9C: .4byte gVideoRegBuffer+6\n\
 .syntax divided\n");
#endif
}

static void DiskLoop_OpenScreen(struct GameState* g) {
  g->frames++;
  if (g->frames >= 16) {
    gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = FILTER_NONE;
    g->mode[1] = 2;
    DiskLoop_Run(g);
  } else {
    gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = g->frames;
  }
}

static void printThreeDigitNumber(u16 n, u8 x, u8 y);

NON_MATCH static void DiskLoop_Run(struct GameState* g) {
#if MODERN || CBODY
  struct SecretDiskState* d;
  struct SecretDiskState* d2;
  u8 disk;
  u16 amount;
  u16 digits;

  d = &g->sceneState.disk;
  d->redraw = 0;
  PTR_ARRAY_083864ac[g->mode[2]](g);

  if (gJoypad[0].pressed & START_BUTTON) {
    g->mode[1] = 3;
  }

  PrintString(STRING(0x1DE), 0x11, 1);
  printThreeDigitNumber(d->cursorDisk + 1, 0x16, 1);

  disk = g->sceneState.disk.cursorDisk;
  if ((((gStageDiskManager.disk[disk >> 2] & 0xF) >> (disk & 3)) & 1) == 0) {
    PrintString(STRING(0x1DD), 1, 0x12);
  } else if (((gStageDiskManager.disk[disk >> 2] >> ((disk & 3) + 4)) & 1) == 0) {
    PrintString(STRING(0x1DF), 0x11, 4);
    PrintString(STRING(0x1DC), 1, 0x12);
  } else {
    if (disk <= 5) {
      PrintString(STRING(0x2BC + d->cursorDisk), 0x11, 4);
    } else if (disk <= 0x13) {
      PrintString(STRING(0x2BC + d->cursorDisk), 0x11, 4);
    } else if (disk <= 0x5D) {
      PrintString(STRING(0x2D0), 0x11, 4);
      PrintString(STRING(d->cursorDisk + 0x50), 0x11, 6);
      PrintString(STRING(0x2D1), getStringLength((char_t*)STRING(d->cursorDisk + 0x50)) + 0x11, 6);
      PrintString(STRING(0x2D2), 0x11, 8);
    } else if (disk <= 0x6D) {
      PrintString(STRING(0x2D3), 0x11, 4);
      digits = 0;
      amount = DiskECrystalAmounts[d->cursorDisk - 0x5E];
      while (amount != 0) {
        amount = amount / 10;
        digits++;
      }
      PrintNumber(DiskECrystalAmounts[d->cursorDisk - 0x5E], digits + 0x11, 6);
      PrintString(STRING(0x2D4), digits + 0x12, 6);
      PrintString(STRING(0x2D5), 0x11, 8);
    } else {
      PrintString(STRING(0x268 + d->cursorDisk), 0x11, 4);
    }
    PrintString(STRING(0x1DD), 1, 0x12);
  }

  d2 = &g->sceneState.disk;
  if (g->sceneState.disk.winHalfW != 0) {
    gPaletteManager.buf[0] = (d2->colorB << 10) | (d2->colorG << 5) | d2->colorR;
    gWindowRegBuffer.dispcnt |= DISPCNT_WIN0_ON;
    gWindowRegBuffer.winin[0] = 0x10;
    gWindowRegBuffer.winin[2] |= 3;
    gWindowRegBuffer.winH.half[0] =
        ((d2->winHalfW + 0x40) & 0xFF) | ((0x40 - d2->winHalfW) << 8);
    gWindowRegBuffer.winV.half[0] =
        ((d2->winHalfH + 0x50) & 0xFF) | ((0x50 - d2->winHalfH) << 8);
  } else {
    gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN0_ON;
    d2->colorR = 0;
    d2->colorG = 0;
    d2->colorB = 0;
  }

  StepPaletteAnimation(0x40);
  if (g->sceneState.disk.redraw) {
    setSecretDiskPalette(g);
  }
#else
  asm(".syntax unified\n\
.if REGION_US\n\
	push	{r4, r5, r6, r7, lr}\n\
	mov	r7, r8\n\
	push	{r7}\n\
	mov	r8, r0\n\
	ldr	r5, _US_080F7C84\n\
	add	r5, r8\n\
	movs	r0, #0\n\
	strb	r0, [r5, #12]\n\
	ldr	r1, _US_080F7C88\n\
	mov	r2, r8\n\
	ldrb	r0, [r2, #2]\n\
	lsls	r0, r0, #2\n\
	adds	r0, r0, r1\n\
	ldr	r1, [r0, #0]\n\
	mov	r0, r8\n\
	bl _call_via_r1\n\
	ldr	r0, _US_080F7C8C\n\
	ldrh	r1, [r0, #4]\n\
	movs	r0, #8\n\
	ands	r0, r1\n\
	cmp	r0, #0\n\
	beq _US_080F7C24\n\
	movs	r0, #3\n\
	mov	r3, r8\n\
	strb	r0, [r3, #1]\n\
_US_080F7C24:\n\
	ldr	r6, _US_080F7C90\n\
	movs	r1, #239\n\
	lsls	r1, r1, #2\n\
	adds	r0, r6, r1\n\
	ldrh	r0, [r0, #0]\n\
	ldr	r7, _US_080F7C94\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #1\n\
	bl PrintString\n\
	ldrb	r0, [r5, #10]\n\
	adds	r0, #1\n\
	movs	r1, #22\n\
	movs	r2, #1\n\
	bl printThreeDigitNumber\n\
	ldr	r0, _US_080F7C98\n\
	ldr	r1, [r0, #0]\n\
	ldrb	r2, [r5, #10]\n\
	lsls	r0, r2, #24\n\
	lsrs	r3, r0, #24\n\
	lsrs	r0, r0, #26\n\
	adds	r4, r1, r0\n\
	ldrb	r1, [r4, #0]\n\
	movs	r0, #15\n\
	ands	r0, r1\n\
	movs	r1, #3\n\
	ands	r1, r2\n\
	asrs	r0, r1\n\
	movs	r2, #1\n\
	ands	r0, r2\n\
	cmp	r0, #0\n\
	bne _US_080F7C6A\n\
	b _US_080F7E14\n\
_US_080F7C6A:\n\
	ldrb	r0, [r4, #0]\n\
	adds	r1, #4\n\
	asrs	r0, r1\n\
	ands	r0, r2\n\
	cmp	r0, #0\n\
	bne _US_080F7C78\n\
	b _US_080F7DEC\n\
_US_080F7C78:\n\
	cmp	r3, #5\n\
	bhi _US_080F7C9C\n\
	movs	r2, #175\n\
	lsls	r2, r2, #2\n\
	adds	r0, r2, #0\n\
	b _US_080F7CA6\n\
	.align 2, 0\n\
_US_080F7C84: .4byte 0x00000DCC\n\
_US_080F7C88: .4byte PTR_ARRAY_083864ac\n\
_US_080F7C8C: .4byte gJoypad\n\
_US_080F7C90: .4byte StringOfsTable\n\
_US_080F7C94: .4byte gStringData\n\
_US_080F7C98: .4byte gStageDiskManager\n\
_US_080F7C9C:\n\
	cmp	r3, #19\n\
	bhi _US_080F7CBC\n\
	movs	r3, #175\n\
	lsls	r3, r3, #2\n\
	adds	r0, r3, #0\n\
_US_080F7CA6:\n\
	ldrb	r5, [r5, #10]\n\
	adds	r0, r0, r5\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r6\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #4\n\
	bl PrintString\n\
	b _US_080F7DD0\n\
_US_080F7CBC:\n\
	cmp	r3, #93\n\
	bhi _US_080F7D1C\n\
	ldrb	r0, [r5, #10]\n\
	adds	r4, r0, #0\n\
	adds	r4, #80\n\
	movs	r1, #180\n\
	lsls	r1, r1, #3\n\
	adds	r0, r6, r1\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #4\n\
	bl PrintString\n\
	lsls	r4, r4, #1\n\
	adds	r4, r4, r6\n\
	ldrh	r0, [r4, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #6\n\
	bl PrintString\n\
	ldr	r2, _US_080F7D14\n\
	adds	r0, r6, r2\n\
	ldrh	r5, [r0, #0]\n\
	adds	r5, r5, r7\n\
	ldrh	r0, [r4, #0]\n\
	adds	r0, r0, r7\n\
	bl getStringLength\n\
	adds	r1, r0, #0\n\
	lsls	r1, r1, #16\n\
	asrs	r1, r1, #16\n\
	adds	r1, #17\n\
	adds	r0, r5, #0\n\
	movs	r2, #6\n\
	bl PrintString\n\
	ldr	r3, _US_080F7D18\n\
	adds	r0, r6, r3\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	b _US_080F7D96\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F7D14: .4byte 0x000005A2\n\
_US_080F7D18: .4byte 0x000005A4\n\
_US_080F7D1C:\n\
	cmp	r3, #109\n\
	bhi _US_080F7DB8\n\
	ldr	r1, _US_080F7DA0\n\
	adds	r0, r6, r1\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #4\n\
	bl PrintString\n\
	movs	r4, #0\n\
	ldr	r1, _US_080F7DA4\n\
	ldrb	r0, [r5, #10]\n\
	subs	r0, #94\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r2, [r0, #0]\n\
	cmp	r2, #0\n\
	beq _US_080F7D58\n\
_US_080F7D42:\n\
	adds	r0, r2, #0\n\
	movs	r1, #10\n\
	bl __udivsi3\n\
	lsls	r0, r0, #16\n\
	lsrs	r2, r0, #16\n\
	adds	r0, r4, #1\n\
	lsls	r0, r0, #16\n\
	lsrs	r4, r0, #16\n\
	cmp	r2, #0\n\
	bne _US_080F7D42\n\
_US_080F7D58:\n\
	ldr	r1, _US_080F7DA4\n\
	ldr	r0, _US_080F7DA8\n\
	add	r0, r8\n\
	ldrb	r0, [r0, #10]\n\
	subs	r0, #94\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r1\n\
	ldrh	r2, [r0, #0]\n\
	adds	r1, r4, #0\n\
	adds	r1, #16\n\
	lsls	r1, r1, #24\n\
	lsrs	r1, r1, #24\n\
	adds	r0, r2, #0\n\
	movs	r2, #4\n\
	bl PrintNumber\n\
	ldr	r4, _US_080F7DAC\n\
	movs	r2, #181\n\
	lsls	r2, r2, #3\n\
	adds	r0, r4, r2\n\
	ldrh	r0, [r0, #0]\n\
	ldr	r5, _US_080F7DB0\n\
	adds	r0, r0, r5\n\
	movs	r1, #17\n\
	movs	r2, #6\n\
	bl PrintString\n\
	ldr	r3, _US_080F7DB4\n\
	adds	r4, r4, r3\n\
	ldrh	r0, [r4, #0]\n\
	adds	r0, r0, r5\n\
_US_080F7D96:\n\
	movs	r1, #17\n\
	movs	r2, #8\n\
	bl PrintString\n\
	b _US_080F7DD0\n\
	.align 2, 0\n\
_US_080F7DA0: .4byte 0x000005A6\n\
_US_080F7DA4: .4byte DiskECrystalAmounts\n\
_US_080F7DA8: .4byte 0x00000DCC\n\
_US_080F7DAC: .4byte StringOfsTable\n\
_US_080F7DB0: .4byte gStringData\n\
_US_080F7DB4: .4byte 0x000005AA\n\
_US_080F7DB8:\n\
	ldrb	r0, [r5, #10]\n\
	movs	r1, #154\n\
	lsls	r1, r1, #2\n\
	adds	r0, r0, r1\n\
	lsls	r0, r0, #1\n\
	adds	r0, r0, r6\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #4\n\
	bl PrintString\n\
_US_080F7DD0:\n\
	ldr	r0, _US_080F7DE0\n\
	ldr	r2, _US_080F7DE4\n\
	adds	r0, r0, r2\n\
	ldrh	r0, [r0, #0]\n\
	ldr	r1, _US_080F7DE8\n\
	adds	r0, r0, r1\n\
	b _US_080F7E06\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F7DE0: .4byte StringOfsTable\n\
_US_080F7DE4: .4byte 0x000003BA\n\
_US_080F7DE8: .4byte gStringData\n\
_US_080F7DEC:\n\
	ldr	r3, _US_080F7E10\n\
	adds	r0, r6, r3\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #17\n\
	movs	r2, #4\n\
	bl PrintString\n\
	movs	r1, #238\n\
	lsls	r1, r1, #2\n\
	adds	r0, r6, r1\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
_US_080F7E06:\n\
	movs	r1, #1\n\
	movs	r2, #18\n\
	bl PrintString\n\
	b _US_080F7E24\n\
	.align 2, 0\n\
_US_080F7E10: .4byte 0x000003BE\n\
_US_080F7E14:\n\
	ldr	r2, _US_080F7E84\n\
	adds	r0, r6, r2\n\
	ldrh	r0, [r0, #0]\n\
	adds	r0, r0, r7\n\
	movs	r1, #1\n\
	movs	r2, #18\n\
	bl PrintString\n\
_US_080F7E24:\n\
	ldr	r5, _US_080F7E88\n\
	add	r5, r8\n\
	ldrb	r0, [r5, #14]\n\
	cmp	r0, #0\n\
	beq _US_080F7E94\n\
	ldr	r2, _US_080F7E8C\n\
	ldrb	r1, [r5, #18]\n\
	lsls	r1, r1, #10\n\
	ldrb	r0, [r5, #17]\n\
	lsls	r0, r0, #5\n\
	orrs	r1, r0\n\
	ldrb	r0, [r5, #16]\n\
	orrs	r0, r1\n\
	strh	r0, [r2, #0]\n\
	ldr	r2, _US_080F7E90\n\
	ldrh	r1, [r2, #0]\n\
	movs	r3, #128\n\
	lsls	r3, r3, #6\n\
	adds	r0, r3, #0\n\
	orrs	r0, r1\n\
	strh	r0, [r2, #0]\n\
	movs	r0, #16\n\
	strb	r0, [r2, #12]\n\
	ldrb	r1, [r2, #14]\n\
	movs	r0, #3\n\
	orrs	r0, r1\n\
	strb	r0, [r2, #14]\n\
	ldrb	r3, [r5, #14]\n\
	adds	r1, r3, #0\n\
	adds	r1, #64\n\
	movs	r4, #255\n\
	ands	r1, r4\n\
	movs	r0, #64\n\
	subs	r0, r0, r3\n\
	lsls	r0, r0, #8\n\
	orrs	r1, r0\n\
	strh	r1, [r2, #4]\n\
	ldrb	r3, [r5, #15]\n\
	adds	r1, r3, #0\n\
	adds	r1, #80\n\
	ands	r1, r4\n\
	movs	r0, #80\n\
	subs	r0, r0, r3\n\
	lsls	r0, r0, #8\n\
	orrs	r1, r0\n\
	strh	r1, [r2, #8]\n\
	b _US_080F7EA6\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F7E84: .4byte 0x000003BA\n\
_US_080F7E88: .4byte 0x00000DCC\n\
_US_080F7E8C: .4byte gPaletteManager\n\
_US_080F7E90: .4byte gWindowRegBuffer\n\
_US_080F7E94:\n\
	ldr	r2, _US_080F7EC8\n\
	ldrh	r1, [r2, #0]\n\
	ldr	r0, _US_080F7ECC\n\
	ands	r0, r1\n\
	movs	r1, #0\n\
	strh	r0, [r2, #0]\n\
	strb	r1, [r5, #16]\n\
	strb	r1, [r5, #17]\n\
	strb	r1, [r5, #18]\n\
_US_080F7EA6:\n\
	movs	r0, #64\n\
	bl StepPaletteAnimation\n\
	ldr	r0, _US_080F7ED0\n\
	add	r0, r8\n\
	ldrb	r0, [r0, #12]\n\
	cmp	r0, #0\n\
	beq _US_080F7EBC\n\
	mov	r0, r8\n\
	bl setSecretDiskPalette\n\
_US_080F7EBC:\n\
	pop	{r3}\n\
	mov	r8, r3\n\
	pop	{r4, r5, r6, r7}\n\
	pop	{r0}\n\
	bx	r0\n\
	movs	r0, r0\n\
	.align 2, 0\n\
_US_080F7EC8: .4byte gWindowRegBuffer\n\
_US_080F7ECC: .4byte 0x0000DFFF\n\
_US_080F7ED0: .4byte 0x00000DCC\n\
.else\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sb\n\
	mov r6, r8\n\
	push {r6, r7}\n\
	mov sb, r0\n\
	ldr r4, _080F80A8 @ =0x00000DCC\n\
	add r4, sb\n\
	movs r0, #0\n\
	strb r0, [r4, #0xc]\n\
	ldr r1, _080F80AC @ =PTR_ARRAY_083864ac\n\
	mov r2, sb\n\
	ldrb r0, [r2, #2]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	ldr r1, [r0]\n\
	mov r0, sb\n\
	bl _call_via_r1\n\
	ldr r0, _080F80B0 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F8046\n\
	movs r0, #3\n\
	mov r3, sb\n\
	strb r0, [r3, #1]\n\
_080F8046:\n\
	ldr r7, _080F80B4 @ =StringOfsTable\n\
	movs r1, #0xef\n\
	lsls r1, r1, #2\n\
	adds r0, r7, r1\n\
	ldrh r0, [r0]\n\
	ldr r2, _080F80B8 @ =gStringData\n\
	mov r8, r2\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #1\n\
	bl PrintString\n\
	ldrb r0, [r4, #0xa]\n\
	adds r0, #1\n\
	movs r1, #0x16\n\
	movs r2, #1\n\
	bl printThreeDigitNumber\n\
	ldr r0, _080F80BC @ =gStageDiskManager\n\
	ldr r1, [r0]\n\
	ldrb r2, [r4, #0xa]\n\
	lsls r0, r2, #0x18\n\
	lsrs r3, r0, #0x18\n\
	lsrs r0, r0, #0x1a\n\
	adds r5, r1, r0\n\
	ldrb r1, [r5]\n\
	movs r0, #0xf\n\
	ands r0, r1\n\
	movs r1, #3\n\
	ands r1, r2\n\
	asrs r0, r1\n\
	movs r2, #1\n\
	ands r0, r2\n\
	cmp r0, #0\n\
	bne _080F808E\n\
	b _080F823C\n\
_080F808E:\n\
	ldrb r0, [r5]\n\
	adds r1, #4\n\
	asrs r0, r1\n\
	ands r0, r2\n\
	cmp r0, #0\n\
	bne _080F809C\n\
	b _080F8214\n\
_080F809C:\n\
	cmp r3, #5\n\
	bhi _080F80C0\n\
	movs r3, #0xaf\n\
	lsls r3, r3, #2\n\
	adds r0, r3, #0\n\
	b _080F80CA\n\
	.align 2, 0\n\
_080F80A8: .4byte 0x00000DCC\n\
_080F80AC: .4byte PTR_ARRAY_083864ac\n\
_080F80B0: .4byte gJoypad\n\
_080F80B4: .4byte StringOfsTable\n\
_080F80B8: .4byte gStringData\n\
_080F80BC: .4byte gStageDiskManager\n\
_080F80C0:\n\
	cmp r3, #0x13\n\
	bhi _080F80E0\n\
	movs r1, #0xaf\n\
	lsls r1, r1, #2\n\
	adds r0, r1, #0\n\
_080F80CA:\n\
	ldrb r4, [r4, #0xa]\n\
	adds r0, r0, r4\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r7\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #4\n\
	bl PrintString\n\
	b _080F81F8\n\
_080F80E0:\n\
	cmp r3, #0x5d\n\
	bhi _080F8140\n\
	ldrb r0, [r4, #0xa]\n\
	adds r6, r0, #0\n\
	adds r6, #0x50\n\
	movs r2, #0xb4\n\
	lsls r2, r2, #3\n\
	adds r0, r7, r2\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #4\n\
	bl PrintString\n\
	lsls r4, r6, #1\n\
	adds r4, r4, r7\n\
	ldrh r0, [r4]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #6\n\
	bl PrintString\n\
	ldr r3, _080F8138 @ =0x000005A2\n\
	adds r0, r7, r3\n\
	ldrh r5, [r0]\n\
	add r5, r8\n\
	ldrh r0, [r4]\n\
	add r0, r8\n\
	bl getStringLength\n\
	adds r1, r0, #0\n\
	lsls r1, r1, #0x10\n\
	asrs r1, r1, #0x10\n\
	adds r1, #0x11\n\
	adds r0, r5, #0\n\
	movs r2, #6\n\
	bl PrintString\n\
	ldr r1, _080F813C @ =0x000005A4\n\
	adds r0, r7, r1\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	b _080F81BC\n\
	.align 2, 0\n\
_080F8138: .4byte 0x000005A2\n\
_080F813C: .4byte 0x000005A4\n\
_080F8140:\n\
	cmp r3, #0x6d\n\
	bhi _080F81E0\n\
	ldr r2, _080F81C8 @ =0x000005A6\n\
	adds r0, r7, r2\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #4\n\
	bl PrintString\n\
	movs r6, #0\n\
	ldr r1, _080F81CC @ =DiskECrystalAmounts\n\
	ldrb r0, [r4, #0xa]\n\
	subs r0, #0x5e\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r2, [r0]\n\
	cmp r2, #0\n\
	beq _080F817C\n\
_080F8166:\n\
	adds r0, r2, #0\n\
	movs r1, #0xa\n\
	bl __udivsi3\n\
	lsls r0, r0, #0x10\n\
	lsrs r2, r0, #0x10\n\
	adds r0, r6, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r6, r0, #0x10\n\
	cmp r2, #0\n\
	bne _080F8166\n\
_080F817C:\n\
	ldr r1, _080F81CC @ =DiskECrystalAmounts\n\
	ldr r0, _080F81D0 @ =0x00000DCC\n\
	add r0, sb\n\
	ldrb r0, [r0, #0xa]\n\
	subs r0, #0x5e\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrh r2, [r0]\n\
	adds r1, r6, #0\n\
	adds r1, #0x11\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x18\n\
	adds r0, r2, #0\n\
	movs r2, #6\n\
	bl PrintNumber\n\
	ldr r4, _080F81D4 @ =StringOfsTable\n\
	movs r3, #0xb5\n\
	lsls r3, r3, #3\n\
	adds r0, r4, r3\n\
	ldrh r0, [r0]\n\
	ldr r5, _080F81D8 @ =gStringData\n\
	adds r0, r0, r5\n\
	adds r1, r6, #0\n\
	adds r1, #0x12\n\
	movs r2, #6\n\
	bl PrintString\n\
	ldr r0, _080F81DC @ =0x000005AA\n\
	adds r4, r4, r0\n\
	ldrh r0, [r4]\n\
	adds r0, r0, r5\n\
_080F81BC:\n\
	movs r1, #0x11\n\
	movs r2, #8\n\
	bl PrintString\n\
	b _080F81F8\n\
	.align 2, 0\n\
_080F81C8: .4byte 0x000005A6\n\
_080F81CC: .4byte DiskECrystalAmounts\n\
_080F81D0: .4byte 0x00000DCC\n\
_080F81D4: .4byte StringOfsTable\n\
_080F81D8: .4byte gStringData\n\
_080F81DC: .4byte 0x000005AA\n\
_080F81E0:\n\
	ldrb r0, [r4, #0xa]\n\
	movs r1, #0x9a\n\
	lsls r1, r1, #2\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r7\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #4\n\
	bl PrintString\n\
_080F81F8:\n\
	ldr r0, _080F8208 @ =StringOfsTable\n\
	ldr r2, _080F820C @ =0x000003BA\n\
	adds r0, r0, r2\n\
	ldrh r0, [r0]\n\
	ldr r1, _080F8210 @ =gStringData\n\
	adds r0, r0, r1\n\
	b _080F822E\n\
	.align 2, 0\n\
_080F8208: .4byte StringOfsTable\n\
_080F820C: .4byte 0x000003BA\n\
_080F8210: .4byte gStringData\n\
_080F8214:\n\
	ldr r3, _080F8238 @ =0x000003BE\n\
	adds r0, r7, r3\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #0x11\n\
	movs r2, #4\n\
	bl PrintString\n\
	movs r1, #0xee\n\
	lsls r1, r1, #2\n\
	adds r0, r7, r1\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
_080F822E:\n\
	movs r1, #1\n\
	movs r2, #0x12\n\
	bl PrintString\n\
	b _080F824C\n\
	.align 2, 0\n\
_080F8238: .4byte 0x000003BE\n\
_080F823C:\n\
	ldr r2, _080F82AC @ =0x000003BA\n\
	adds r0, r7, r2\n\
	ldrh r0, [r0]\n\
	add r0, r8\n\
	movs r1, #1\n\
	movs r2, #0x12\n\
	bl PrintString\n\
_080F824C:\n\
	ldr r5, _080F82B0 @ =0x00000DCC\n\
	add r5, sb\n\
	ldrb r0, [r5, #0xe]\n\
	cmp r0, #0\n\
	beq _080F82BC\n\
	ldr r2, _080F82B4 @ =gPaletteManager\n\
	ldrb r1, [r5, #0x12]\n\
	lsls r1, r1, #0xa\n\
	ldrb r0, [r5, #0x11]\n\
	lsls r0, r0, #5\n\
	orrs r1, r0\n\
	ldrb r0, [r5, #0x10]\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	ldr r2, _080F82B8 @ =gWindowRegBuffer\n\
	ldrh r1, [r2]\n\
	movs r3, #0x80\n\
	lsls r3, r3, #6\n\
	adds r0, r3, #0\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	movs r0, #0x10\n\
	strb r0, [r2, #0xc]\n\
	ldrb r1, [r2, #0xe]\n\
	movs r0, #3\n\
	orrs r0, r1\n\
	strb r0, [r2, #0xe]\n\
	ldrb r3, [r5, #0xe]\n\
	adds r1, r3, #0\n\
	adds r1, #0x40\n\
	movs r4, #0xff\n\
	ands r1, r4\n\
	movs r0, #0x40\n\
	subs r0, r0, r3\n\
	lsls r0, r0, #8\n\
	orrs r1, r0\n\
	strh r1, [r2, #4]\n\
	ldrb r3, [r5, #0xf]\n\
	adds r1, r3, #0\n\
	adds r1, #0x50\n\
	ands r1, r4\n\
	movs r0, #0x50\n\
	subs r0, r0, r3\n\
	lsls r0, r0, #8\n\
	orrs r1, r0\n\
	strh r1, [r2, #8]\n\
	b _080F82CE\n\
	.align 2, 0\n\
_080F82AC: .4byte 0x000003BA\n\
_080F82B0: .4byte 0x00000DCC\n\
_080F82B4: .4byte gPaletteManager\n\
_080F82B8: .4byte gWindowRegBuffer\n\
_080F82BC:\n\
	ldr r2, _080F82F0 @ =gWindowRegBuffer\n\
	ldrh r1, [r2]\n\
	ldr r0, _080F82F4 @ =0x0000DFFF\n\
	ands r0, r1\n\
	movs r1, #0\n\
	strh r0, [r2]\n\
	strb r1, [r5, #0x10]\n\
	strb r1, [r5, #0x11]\n\
	strb r1, [r5, #0x12]\n\
_080F82CE:\n\
	movs r0, #0x40\n\
	bl StepPaletteAnimation\n\
	ldr r0, _080F82F8 @ =0x00000DCC\n\
	add r0, sb\n\
	ldrb r0, [r0, #0xc]\n\
	cmp r0, #0\n\
	beq _080F82E4\n\
	mov r0, sb\n\
	bl setSecretDiskPalette\n\
_080F82E4:\n\
	pop {r3, r4}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080F82F0: .4byte gWindowRegBuffer\n\
_080F82F4: .4byte 0x0000DFFF\n\
_080F82F8: .4byte 0x00000DCC\n\
.endif\n\
 .syntax divided\n");
#endif
}

static void DiskLoop_BlackOut(struct GameState* g) {
  g->frames--;
  if (g->frames == 0) {
    gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = FILTER_BLACK;
    g->mode[1] = 4;
    DiskLoop_Exit(g);
  } else {
    gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = g->frames;
  }
}

static void DiskLoop_Exit(struct GameState* g) {
  u8* s;
  RemovePaletteAnimation(64);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN0_ON;
  gPaletteManager.buf[0] = 0;
  s = (u8*)&(g->sceneState).menu;
  s[13] = 1;
  SetGameMode(g, GAMEMODE(MAINGAME, OVERWORLD, 3, 5));
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void sd_analysis_080f83ac(struct GameState* g) {
  Coords32* c = &g->unk_0dc4;
  c->x = PIXEL(120), c->y = PIXEL(80);
  ResetPivot(&g->unk_0db8, c, 0, 0);
  Renderer_Init(&g->rendererUI);
  Renderer_SetPivot(&g->rendererUI, &g->unk_0db8);
  InitWidgetHeader(&g->entityHeaders[ENTITY_WIDGET], gWidgets, 64);
}

static void sd_analysis_080f8408(struct GameState* g) {
  Coords32* c = &g->unk_0dc4;
  const BgOfs* bg1ofs = (const BgOfs*)gVideoRegBuffer.bgofs[1];
  c->x = PIXEL(bg1ofs->x & 0x1FF) + PIXEL(120);
  Renderer_Clear(&g->rendererUI);
  UpdateEntities(gWidgetHeaderPtr);
  DrawEntity(gWidgetHeaderPtr, &g->rendererUI);
  Renderer_Flush(&g->rendererUI);
}

static void setSecretDiskPalette(struct GameState* g) {
  struct SecretDiskState* d;
  u16* map;
  u16* p;
  u8* disk;
  u8* q;
  u8* q2;
  s32 n;
  u8 i;
  u8 row;
  u8 col;

  map = g->menuBgMap1;
  for (i = 0; i <= 0x1D; i++) {
    disk = gStageDiskManager.disk;
    d = &g->sceneState.disk;
    n = d->scrollRow * 5 + i;
    q = &disk[n >> 2];
    if (((*q & 0xF) >> (n & 3)) & 1) {
      q2 = q;
      if ((*q2 >> ((n & 3) + 4)) & 1) {
        row = i / 5;
        col = i % 5;
        (&map[(row << 6) + (col << 1)])[99] = 0x80ED;
        (&map[(row << 6) + (col << 1)])[100] = 0x80EE;
        (&map[(row << 6) + (col << 1)])[131] = 0x810D;
        (&map[(row << 6) + (col << 1)])[132] = 0x810E;
      } else {
        row = (col = i / 5);
        col = i % 5;
        (&map[(row << 6) + (col << 1)])[99] = 0x80EB;
        (&map[(row << 6) + (col << 1)])[100] = 0x80EC;
        (&map[(row << 6) + (col << 1)])[131] = 0x810B;
        (&map[(row << 6) + (col << 1)])[132] = 0x810C;
      }
    } else {
      row = 5;
      row = i / row;
      col = i % 5;
      (&map[(((u8)(i / 5)) << 6) + (col << 1)])[99] = 0x31A2;
      (&map[(((u8)(i / 5)) << 6) + (col << 1)])[100] = 0x31A2;
      (&map[(((u8)(i / 5)) << 6) + (col << 1)])[131] = 0x31A2;
      (&map[(((u8)(i / 5)) << 6) + (col << 1)])[132] = 0x31A2;
    }
  }
  RequestBgMapTransfer(g->menuBgMap1, (void*)SCREEN_BASE(1), 0x1000);
}

static void sd_analysis_080f85e0(struct GameState* g) {
  struct SecretDiskState* d;
  struct SecretDiskState* d2;
  struct SecretDiskState* d3;
  u8 old;
  u32 q;
  u8* disk;
  u32 five;

  if (g->mode[3] == 0) {
    d = &g->sceneState.disk;
    d->redraw = 1;
    d->cursor = (struct SquareCursorWidget*)CreateSquareCursor(g, FALSE, 0);
    d->cursor->px = ((u8)(d->cursorDisk % 5) << 4) + 0x18;
    d->cursor->py = (((u8)(d->cursorDisk / 5) - d->scrollRow) << 4) + 0x18;
    g->mode[3]++;
    return;
  }

  d3 = &g->sceneState.disk;
  old = d3->cursorDisk;
  if (gJoypad[0].field3_0x6 & DPAD_LEFT) {
    if (old != 0) d3->cursorDisk = old - 1;
  } else if (gJoypad[0].field3_0x6 & DPAD_RIGHT) {
    if (old <= 0xB2) d3->cursorDisk = old + 1;
  } else if (gJoypad[0].field3_0x6 & DPAD_UP) {
    if (old > 4) d3->cursorDisk = old - 5;
  } else if (gJoypad[0].field3_0x6 & DPAD_DOWN) {
    if (old <= 0xAE) d3->cursorDisk = old + 5;
  }

  d2 = &g->sceneState.disk;
  if (old != d2->cursorDisk) PlaySound(1);

  five = 5;
  q = d2->cursorDisk / five;
  if (d2->scrollRow > (u8)q) {
    d2->scrollRow = q;
    d2->redraw = 1;
  } else if (d2->scrollRow < (s32)((u8)q - five)) {
    d2->scrollRow = q - five;
    d2->redraw = 1;
  }

  d = &g->sceneState.disk;
  d->cursor->px = ((u8)(d->cursorDisk % 5) << 4) + 0x18;
  d->cursor->py = (((u8)(d->cursorDisk / 5) - d->scrollRow) << 4) + 0x18;

  if (gJoypad[0].pressed & A_BUTTON) {
    disk = gStageDiskManager.disk;
    if ((((disk[d->cursorDisk >> 2] & 0xF) >> (d->cursorDisk & 3)) & 1) != 0) {
      d->cursor->dead = TRUE;
      g->mode[2] = 1;
      g->mode[3] = 0;
    } else {
      PlaySound(4);
    }
  } else if (gJoypad[0].pressed & B_BUTTON) {
    g->mode[1] = 3;
  }
}

NON_MATCH static void sd_analysis_080f875c(struct GameState* g) {
#if MODERN || CBODY
  struct SecretDiskState* d;
  struct SecretDiskState* d2;
  struct SecretDiskState* d3;
  struct SecretDiskState* d4;
  const struct SecretDiskEntry* e;
  u16* pal;
  u16* dst;
  u8 r;
  u32 gr, b;
  u32 tr, tg, tb;
  u16 cur;
  u16 target;
  u8 t;
  u16 i;

  d = &g->sceneState.disk;

  if (g->mode[3] == 0) {
    if (((gStageDiskManager.disk[d->cursorDisk >> 2] >> ((d->cursorDisk & 3) + 4)) & 1) != 0) {
      PlaySound(2);
    } else {
      PlaySound(14);
    }
    d2 = &g->sceneState.disk;
    OpenSecretDisk(g, d2->cursorDisk, FALSE);

    // The three bytes are a palette-animation triple, chosen by which range of
    // disk numbers the opened disk falls in.
    if (d2->cursorDisk <= 0x13) {
      d2->colorB = 0;
      d2->colorG = 0;
      d2->colorR = 0;
    } else if (d2->cursorDisk <= 0x2E) {
      d2->colorR = 0x13;
      d2->colorG = 2;
      d2->colorB = 9;
    } else if (d2->cursorDisk <= 0x3B) {
      d2->colorR = 2;
      d2->colorG = 0x11;
      d2->colorB = 7;
    } else if (d2->cursorDisk <= 0x5D) {
      d2->colorR = 8;
      d2->colorG = 0xB;
      d2->colorB = 0x16;
    } else {
      d2->colorB = 0;
      d2->colorG = 0;
      d2->colorR = 0;
    }

    d3 = &g->sceneState.disk;
    d3->redraw = 1;
    g->mode[3]++;
  }

  // Fade entries 130..143 toward half the brightness of 146..159, one step per
  // channel per frame.
  for (i = 2; i <= 0xF; i++) {
    pal = &gPaletteManager.buf[128];
    dst = &gPaletteManager.buf[144];
    cur = pal[i];
    target = dst[i];
    r = cur & 0x1F;
    tr = (target & 0x1F) >> 1;
    if (r > tr) r = (u8)(r - 1);
    gr = cur >> 5;
    gr = gr & 0x1F;
    tg = ((target >> 5) & 0x1F) >> 1;
    if (gr > tg) gr = (u8)(gr - 1);
    b = (cur >> 10) & 0x1F;
    tb = 0x1F;
    tb = ((target >> 10) & tb) >> 1;
    if (b > tb) b = (u8)(b - 1);
    pal[i] = (b << 10) | (gr << 5) | r;
  }

  d4 = &g->sceneState.disk;
  if (gSecretDiskEntries[d4->cursorDisk].unk_00 != 0) {
    t = (u8)gSecretDiskEntries[d4->cursorDisk].rate0 >> 1;
    if (d4->winHalfW < t) {
      d4->winHalfW += gSecretDiskEntries[d4->cursorDisk].rate0 >> 4;
      d4->winHalfH += gSecretDiskEntries[d4->cursorDisk].rate1 >> 4;
      if (d4->winHalfW > (gSecretDiskEntries[d4->cursorDisk].rate0 >> 1)) {
        d4->winHalfW = gSecretDiskEntries[d4->cursorDisk].rate0 >> 1;
      }
      if (d4->winHalfH > (gSecretDiskEntries[d4->cursorDisk].rate1 >> 1)) {
        d4->winHalfH = gSecretDiskEntries[d4->cursorDisk].rate1 >> 1;
      }
    } else {
      d4->winHalfW = t;
      d4->winHalfH = gSecretDiskEntries[d4->cursorDisk].rate1 >> 1;
      if (g->mode[3] == 1) {
        e = &gSecretDiskEntries[d4->cursorDisk];
        FUN_080e83d0(g, d4->cursorDisk, e->unk_04, e->unk_00,
                     (0x40 - gSecretDiskEntries[d4->cursorDisk].x) << 8,
                     (0x50 - gSecretDiskEntries[d4->cursorDisk].y) << 8,
                     gSecretDiskEntries[d4->cursorDisk].unk_07);
        g->mode[3]++;
      }
    }
  }

  if (gJoypad[0].pressed & (A_BUTTON | B_BUTTON)) {
    PlaySound(3);
    g->mode[2]++;
  }
#else
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	sub sp, #0x10\n\
	mov r8, r0\n\
	ldrb r0, [r0, #3]\n\
	cmp r0, #0\n\
	bne _080F880C\n\
	ldr r0, _080F8798 @ =gStageDiskManager\n\
	ldr r1, [r0]\n\
	ldr r0, _080F879C @ =0x00000DCC\n\
	add r0, r8\n\
	ldrb r2, [r0, #0xa]\n\
	lsrs r0, r2, #2\n\
	adds r1, r1, r0\n\
	ldrb r1, [r1]\n\
	movs r0, #3\n\
	ands r0, r2\n\
	adds r0, #4\n\
	asrs r1, r0\n\
	movs r0, #1\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	beq _080F87A0\n\
	movs r0, #2\n\
	bl PlaySound\n\
	b _080F87A6\n\
	.align 2, 0\n\
_080F8798: .4byte gStageDiskManager\n\
_080F879C: .4byte 0x00000DCC\n\
_080F87A0:\n\
	movs r0, #0xe\n\
	bl PlaySound\n\
_080F87A6:\n\
	ldr r4, _080F87CC @ =0x00000DCC\n\
	add r4, r8\n\
	ldrb r1, [r4, #0xa]\n\
	mov r0, r8\n\
	movs r2, #0\n\
	bl OpenSecretDisk\n\
	ldrb r0, [r4, #0xa]\n\
	cmp r0, #0x13\n\
	bls _080F87F4\n\
	cmp r0, #0x2e\n\
	bhi _080F87D0\n\
	movs r0, #0x13\n\
	strb r0, [r4, #0x10]\n\
	movs r0, #2\n\
	strb r0, [r4, #0x11]\n\
	movs r0, #9\n\
	strb r0, [r4, #0x12]\n\
	b _080F87FC\n\
	.align 2, 0\n\
_080F87CC: .4byte 0x00000DCC\n\
_080F87D0:\n\
	cmp r0, #0x3b\n\
	bhi _080F87E2\n\
	movs r0, #2\n\
	strb r0, [r4, #0x10]\n\
	movs r0, #0x11\n\
	strb r0, [r4, #0x11]\n\
	movs r0, #7\n\
	strb r0, [r4, #0x12]\n\
	b _080F87FC\n\
_080F87E2:\n\
	cmp r0, #0x5d\n\
	bhi _080F87F4\n\
	movs r0, #8\n\
	strb r0, [r4, #0x10]\n\
	movs r0, #0xb\n\
	strb r0, [r4, #0x11]\n\
	movs r0, #0x16\n\
	strb r0, [r4, #0x12]\n\
	b _080F87FC\n\
_080F87F4:\n\
	movs r0, #0\n\
	strb r0, [r4, #0x12]\n\
	strb r0, [r4, #0x11]\n\
	strb r0, [r4, #0x10]\n\
_080F87FC:\n\
	ldr r1, _080F88E0 @ =0x00000DCC\n\
	add r1, r8\n\
	movs r0, #1\n\
	strb r0, [r1, #0xc]\n\
	mov r1, r8\n\
	ldrb r0, [r1, #3]\n\
	adds r0, #1\n\
	strb r0, [r1, #3]\n\
_080F880C:\n\
	movs r7, #2\n\
	ldr r2, _080F88E4 @ =0x03002BC0\n\
	mov sl, r2\n\
	movs r4, #0x1f\n\
	mov sb, r4\n\
	movs r5, #0x1f\n\
	mov ip, r5\n\
_080F881A:\n\
	lsls r0, r7, #1\n\
	mov r1, sl\n\
	adds r6, r0, r1\n\
	ldrh r1, [r6]\n\
	adds r4, r1, #0\n\
	ldr r2, _080F88E8 @ =0x03002BE0\n\
	adds r0, r0, r2\n\
	ldrh r2, [r0]\n\
	str r2, [sp, #0xc]\n\
	movs r0, #0x1f\n\
	adds r3, r1, #0\n\
	ands r3, r0\n\
	adds r0, r2, #0\n\
	mov r5, ip\n\
	ands r0, r5\n\
	lsrs r0, r0, #1\n\
	cmp r3, r0\n\
	bls _080F8844\n\
	subs r0, r3, #1\n\
	lsls r0, r0, #0x18\n\
	lsrs r3, r0, #0x18\n\
_080F8844:\n\
	lsrs r1, r1, #5\n\
	mov r0, ip\n\
	ands r1, r0\n\
	lsrs r0, r2, #5\n\
	mov r2, sb\n\
	ands r0, r2\n\
	lsrs r0, r0, #1\n\
	cmp r1, r0\n\
	bls _080F885C\n\
	subs r0, r1, #1\n\
	lsls r0, r0, #0x18\n\
	lsrs r1, r0, #0x18\n\
_080F885C:\n\
	lsrs r2, r4, #0xa\n\
	mov r4, ip\n\
	ands r2, r4\n\
	ldr r5, [sp, #0xc]\n\
	lsrs r0, r5, #0xa\n\
	mov r4, sb\n\
	ands r0, r4\n\
	lsrs r0, r0, #1\n\
	cmp r2, r0\n\
	bls _080F8876\n\
	subs r0, r2, #1\n\
	lsls r0, r0, #0x18\n\
	lsrs r2, r0, #0x18\n\
_080F8876:\n\
	lsls r0, r2, #0xa\n\
	lsls r1, r1, #5\n\
	orrs r0, r1\n\
	orrs r0, r3\n\
	strh r0, [r6]\n\
	adds r0, r7, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r7, r0, #0x10\n\
	cmp r7, #0xf\n\
	bls _080F881A\n\
	ldr r5, _080F88EC @ =gSecretDiskEntries\n\
	ldr r4, _080F88E0 @ =0x00000DCC\n\
	add r4, r8\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	adds r1, r0, r5\n\
	ldrh r0, [r1]\n\
	cmp r0, #0\n\
	beq _080F8950\n\
	ldrb r0, [r1, #5]\n\
	lsls r0, r0, #0x18\n\
	lsrs r2, r0, #0x19\n\
	ldrb r3, [r4, #0xe]\n\
	cmp r3, r2\n\
	bhs _080F88F0\n\
	lsrs r1, r0, #0x1c\n\
	adds r1, r3, r1\n\
	strb r1, [r4, #0xe]\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	adds r0, r0, r5\n\
	ldrb r0, [r0, #6]\n\
	lsrs r0, r0, #4\n\
	ldrb r2, [r4, #0xf]\n\
	adds r0, r0, r2\n\
	strb r0, [r4, #0xf]\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	adds r2, r0, r5\n\
	ldrb r0, [r2, #5]\n\
	lsrs r0, r0, #1\n\
	lsls r1, r1, #0x18\n\
	lsrs r1, r1, #0x18\n\
	cmp r1, r0\n\
	bls _080F88D2\n\
	strb r0, [r4, #0xe]\n\
_080F88D2:\n\
	ldrb r0, [r2, #6]\n\
	lsrs r1, r0, #1\n\
	ldrb r0, [r4, #0xf]\n\
	cmp r0, r1\n\
	bls _080F8950\n\
	strb r1, [r4, #0xf]\n\
	b _080F8950\n\
	.align 2, 0\n\
_080F88E0: .4byte 0x00000DCC\n\
_080F88E4: .4byte gPaletteManager+(128*2)\n\
_080F88E8: .4byte gPaletteManager+(144*2)\n\
_080F88EC: .4byte gSecretDiskEntries\n\
_080F88F0:\n\
	strb r2, [r4, #0xe]\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	ldr r5, _080F897C @ =gSecretDiskEntries\n\
	adds r0, r0, r5\n\
	ldrb r0, [r0, #6]\n\
	lsrs r0, r0, #1\n\
	strb r0, [r4, #0xf]\n\
	mov r1, r8\n\
	ldrb r0, [r1, #3]\n\
	ldrb r5, [r4, #0xa]\n\
	cmp r0, #1\n\
	bne _080F8950\n\
	lsls r0, r5, #3\n\
	ldr r2, _080F897C @ =gSecretDiskEntries\n\
	adds r0, r0, r2\n\
	ldrb r2, [r0, #4]\n\
	ldrh r3, [r0]\n\
	movs r1, #2\n\
	ldrsb r1, [r0, r1]\n\
	movs r0, #0x40\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #8\n\
	str r0, [sp]\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	ldr r1, _080F897C @ =gSecretDiskEntries\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	ldrsb r1, [r0, r1]\n\
	movs r0, #0x50\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #8\n\
	str r0, [sp, #4]\n\
	ldrb r0, [r4, #0xa]\n\
	lsls r0, r0, #3\n\
	ldr r4, _080F897C @ =gSecretDiskEntries\n\
	adds r0, r0, r4\n\
	ldrb r0, [r0, #7]\n\
	str r0, [sp, #8]\n\
	mov r0, r8\n\
	adds r1, r5, #0\n\
	bl FUN_080e83d0\n\
	mov r5, r8\n\
	ldrb r0, [r5, #3]\n\
	adds r0, #1\n\
	strb r0, [r5, #3]\n\
_080F8950:\n\
	ldr r0, _080F8980 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F896A\n\
	movs r0, #3\n\
	bl PlaySound\n\
	mov r1, r8\n\
	ldrb r0, [r1, #2]\n\
	adds r0, #1\n\
	strb r0, [r1, #2]\n\
_080F896A:\n\
	add sp, #0x10\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080F897C: .4byte gSecretDiskEntries\n\
_080F8980: .4byte gJoypad\n\
 .syntax divided\n");
#endif
}

static void sd_analysis_080f8984(struct GameState* g) {
  struct SecretDiskState* d = &g->sceneState.disk;
  const struct SecretDiskEntry* e;
  const struct SecretDiskEntry* table;
  int t;
  u16* pal;
  u16* src;
  u8 i;
  const struct SecretDiskEntry* row;

  if (d->winHalfW != 0) {
    t = d->winHalfW;
    table = gSecretDiskEntries;
    row = &table[d->cursorDisk];
    e = row;
    if ((t - (e->rate0 >> 4)) > 0) {
      d->winHalfW = t - (e->rate0 >> 4);
      if ((d->winHalfH - (e->rate1 >> 4)) > 0) {
        d->winHalfH = d->winHalfH - (e->rate1 >> 4);
      } else {
        d->winHalfH = 0;
      }
      return;
    }
    d->winHalfW = 0;
    d->winHalfH = 0;
    g->mode[2] = 0;
    g->mode[3] = 0;
    i = 2;
    pal = &gPaletteManager.buf[128];
    src = pal + 16;
    for (; i <= 0xF; i++) {
      pal[i] = src[i];
    }
    return;
  }

    d->winHalfW = 0;
    d->winHalfH = 0;
    g->mode[2] = 0;
    g->mode[3] = 0;
    i = 2;
    pal = &gPaletteManager.buf[128];
    src = pal + 16;
    for (; i <= 0xF; i++) {
      pal[i] = src[i];
    }
}

static void printThreeDigitNumber(u16 n, u8 x, u8 y) {
  u8 i;
  for (i = 0; i < 3; i++) {
    u32 digit = n % 10;
    PrintString(STRING(digit + 30), x - i, y);
    n /= 10;
  }
}

/**
 * @brief シークレットディスクを開ける処理
 * @param disk_no ディスク番号
 * @param is_result 1(リザルト画面) or 0(セルヴォの解析)
 * @note 0x080f8a84
 */
u16 OpenSecretDisk(struct GameState* g, u8 disk_no, bool8 is_result) {
  struct Zero* z = g->z2;
  u8* p;
  u8 bit;
  u8 flags;
  u8* disk;
  struct ZeroStatus* st;

  if (is_result) {
    if ((u8)(disk_no - 6) <= 0xD) return 0;
    if (disk_no > 0x6D) return 0;
  }

  disk = gStageDiskManager.disk;
  p = &disk[disk_no >> 2];
  flags = *p;
  bit = disk_no & 3;
  if ((flags >> (bit + 4)) & 1) return 0;
  *p = flags | (0x10 << bit);

  if (disk_no <= 5) {
    switch (disk_no) {
      case 0: st = &z->unk_b4.status; st->unlockedHead |= 4; break;
      case 1: st = &z->unk_b4.status; st->unlockedHead |= 2; break;
      case 2: st = &z->unk_b4.status; st->unlockedHead |= 8; break;
      case 3: st = &z->unk_b4.status; st->unlockedFoot |= 0x40; break;
      case 4: st = &z->unk_b4.status; st->unlockedFoot |= 2; break;
      case 5: st = &z->unk_b4.status; st->unlockedFoot |= 0x80; break;
    }
    return disk_no + 0x17B;
  }
  if (disk_no <= 0x13) return 0;
  if (disk_no <= 0x5D) {
    gElfAvailability[disk_no - 0x14] |= 1;
    return disk_no + 0x10D;
  }
  if (disk_no <= 0x6D) {
    AddECrystal(z, DiskECrystalAmounts[disk_no - 0x5E]);
    return disk_no + 0x10D;
  }
  return 0;
}

/**
 * @param flagbits &GameSavedata.disk[0] (addr: 0x02036e78)
 * @note 0x080f8b94
 */
void clearSecretDiskData(u8* flagbits) {
  gStageDiskManager.disk = flagbits;
  MemFill32(0, flagbits, 48);
  clearStageDisk();
}

/**
 * @brief clearSecretDiskData のハードモード版
 * @note 0x080f8bd4, 処理は clearSecretDiskData と完全に同じ
 */
void clearSecretDiskDataHard(u8* flagbits) {
  gStageDiskManager.disk = flagbits;
  MemFill32(0, flagbits, 48);
  clearStageDisk();
}

/**
 * @brief clearSecretDiskData のアルティメットモード版
 * @note 0x080f8c14
 */
void unlockAllSecretDisk(u8* flagbits) {
  u8* disk;
  u8 i;
  gStageDiskManager.disk = flagbits;
  CpuFastFill(0, flagbits, 32);
  CpuFill32(0, flagbits + 0x20, 16);
  // Two bits per disk in each byte: found in the low nibble, analysed in the high.
  for (i = 0; i <= 0xB3; i++) {
    disk = gStageDiskManager.disk;
    gStageDiskManager.disk[i >> 2] = disk[i >> 2] | (1 << (i & 3));
    gStageDiskManager.disk[i >> 2] |= 0x10 << (i & 3);
  }
  clearStageDisk();
}

void clearStageDisk(void) {
  u8 i;
  for (i = 0; i < 10; i++) {
    gStageDiskManager.stageDiskIDs[i] = 0xFF;
  }
  gStageDiskManager.stageDiskCount = 0;
}

void getDiskInStageRun(u8 disk_id) {
  u8* flagbits = gStageDiskManager.disk;
  UNLOCK_DISK(flagbits, disk_id);
  gStageDiskManager.stageDiskIDs[gStageDiskManager.stageDiskCount] = disk_id;
  gStageDiskManager.stageDiskCount++;
}

bool8 allSecretDiskFound(void) {
  u8 i;
  for (i = 0; i < DISK_COUNT; i++) {
    if ((IS_DISK_UNLOCKED(gStageDiskManager.disk, i) & 1) == 0) {
      return FALSE;
    }
  }
  return TRUE;
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void sd_analysis_080f85e0(struct GameState* g);
static void sd_analysis_080f875c(struct GameState* g);
static void sd_analysis_080f8984(struct GameState* g);

const DiskLoopFunc PTR_ARRAY_083864ac[3] = {
    sd_analysis_080f85e0,
    sd_analysis_080f875c,
    sd_analysis_080f8984,
};

const u16 DiskECrystalAmounts[16] = {
    80, 100, 200, 150, 40, 100, 100, 50, 80, 100, 100, 40, 500, 100, 100, 100,
};

const struct SecretDiskEntry gSecretDiskEntries[DISK_COUNT] = {
    {0x0E1C, 15, 15, 0x00, 0x30, 0x30, 0x01}, {0x0E1E, 15, 15, 0x00, 0x30, 0x30, 0x01}, {0x0E1D, 15, 15, 0x00, 0x30, 0x30, 0x01}, {0x0E2B, 15, 15, 0x00, 0x30, 0x30, 0x01},
    {0x0E26, 15, 15, 0x00, 0x30, 0x30, 0x01}, {0x0E2C, 15, 15, 0x00, 0x30, 0x30, 0x01}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00},
    {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00},
    {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00},
    {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00}, {0xB00A, 0, -10, 0x00, 0x48, 0x48, 0x00},
    {0x9100, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9500, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9500, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xBE00, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xBE00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0x9300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9500, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0x9500, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9B00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9B00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0x9E00, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xA000, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA200, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA400, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA600, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xA700, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA700, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA800, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA800, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xA900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xA900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xAA00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xAA00, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xAD00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xAE00, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB000, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB100, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB100, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB100, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB100, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB200, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB300, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB300, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB500, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB500, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB500, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB600, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB600, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB600, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB600, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB600, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB800, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB800, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB800, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB900, 0, 0, 0x00, 0x30, 0x30, 0x00},
    {0xB900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xB900, 0, 0, 0x00, 0x30, 0x30, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00},
    {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00},
    {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00},
    {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00},
    {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xAA04, 0, -6, 0x00, 0x24, 0x24, 0x00}, {0xE100, 8, 4, 0x00, 0x78, 0x96, 0x00}, {0xA706, -3, -33, 0x01, 0x58, 0x58, 0x00},
    {0xA41E, 5, -23, 0x01, 0x50, 0x50, 0x00}, {0xA200, 2, -20, 0x01, 0x50, 0x50, 0x00}, {0xA804, 2, -37, 0x01, 0x58, 0x58, 0x00}, {0x3100, 0, 0, 0x00, 0x48, 0x48, 0x00},
    {0x3100, 0, 0, 0x00, 0x48, 0x48, 0x00}, {0xAF01, 0, 0, 0x01, 0x38, 0x50, 0x00}, {0xB510, 15, -18, 0x01, 0x52, 0x52, 0x00}, {0xB401, 0, -34, 0x01, 0x58, 0x58, 0x00},
    {0xB31E, 0, -20, 0x01, 0x48, 0x48, 0x00}, {0xAB09, -6, -42, 0x01, 0x7E, 0x6C, 0x00}, {0xB200, 0, -29, 0x01, 0x52, 0x52, 0x00}, {0xB002, 0, -24, 0x01, 0x46, 0x4A, 0x00},
    {0xA500, 8, -24, 0x01, 0x60, 0x50, 0x00}, {0x1309, -2, -15, 0x00, 0x40, 0x40, 0x00}, {0x1401, -1, -15, 0x00, 0x40, 0x40, 0x00}, {0x2700, 0, -21, 0x00, 0x40, 0x40, 0x00},
    {0xD402, 0, -13, 0x00, 0x40, 0x40, 0x00}, {0x6D00, 14, -35, 0x00, 0x62, 0x5E, 0x00}, {0x7402, 0, -16, 0x00, 0x40, 0x40, 0x00}, {0x170F, 0, -4, 0x00, 0x40, 0x40, 0x00},
    {0x0709, 0, -10, 0x00, 0x40, 0x40, 0x00}, {0x2F00, 0, 0, 0x00, 0x40, 0x40, 0x00}, {0x0808, -6, 0, 0x00, 0x40, 0x40, 0x00}, {0x3809, 0, -6, 0x00, 0x48, 0x48, 0x00},
    {0x6806, -7, 0, 0x00, 0x40, 0x40, 0x00}, {0x7107, 0, -26, 0x00, 0x66, 0x4A, 0x00}, {0x6601, -14, 18, 0x00, 0x4E, 0x40, 0x00}, {0x0D03, 0, 6, 0x00, 0x40, 0x40, 0x00},
    {0x2E06, 0, -10, 0x00, 0x40, 0x40, 0x00}, {0x7501, 0, 17, 0x00, 0x40, 0x2E, 0x00}, {0x7E1D, 0, -16, 0x00, 0x40, 0x40, 0x00}, {0x8E12, 1, -10, 0x00, 0x40, 0x40, 0x00},
    {0x770C, 1, -18, 0x00, 0x40, 0x40, 0x00}, {0x190F, 0, -15, 0x00, 0x48, 0x48, 0x00}, {0x1D03, 3, -8, 0x00, 0x40, 0x40, 0x00}, {0xD501, 0, -20, 0x00, 0x40, 0x40, 0x00},
    {0x1500, 0, -7, 0x00, 0x40, 0x40, 0x00}, {0x280C, 11, -16, 0x00, 0x40, 0x40, 0x00}, {0x6703, 2, 2, 0x00, 0x40, 0x40, 0x00}, {0x4318, 0, 0, 0x00, 0x40, 0x40, 0x00},
    {0x1601, 0, 0, 0x00, 0x40, 0x40, 0x00}, {0x2A02, 0, -9, 0x00, 0x40, 0x40, 0x00}, {0x6B00, 0, -6, 0x00, 0x40, 0x40, 0x00}, {0x0600, 0, 0, 0x00, 0x40, 0x40, 0x00},
    {0x4703, 0, 0, 0x00, 0x40, 0x40, 0x00}, {0x0400, 0, 0, 0x00, 0x40, 0x40, 0x00}, {0x1800, 3, 0, 0x00, 0x40, 0x40, 0x00}, {0x350B, 1, -10, 0x00, 0x40, 0x40, 0x00},
    {0x1000, 0, -14, 0x00, 0x40, 0x40, 0x00}, {0xDB00, 0, -8, 0x00, 0x40, 0x40, 0x00}, {0xDC03, 0, -8, 0x00, 0x40, 0x40, 0x00}, {0xC505, 0, -32, 0x01, 0x46, 0x46, 0x00},
    {0xC20E, 0, -14, 0x01, 0x38, 0x38, 0x00}, {0xC203, 0, -17, 0x00, 0x38, 0x38, 0x00}, {0xC401, 0, -13, 0x00, 0x38, 0x38, 0x00}, {0xBB01, 0, -13, 0x00, 0x38, 0x38, 0x00},
    {0xC301, 0, -19, 0x00, 0x38, 0x38, 0x00}, {0xC000, 0, -17, 0x00, 0x38, 0x38, 0x00}, {0xC601, 0, -11, 0x00, 0x38, 0x38, 0x00}, {0xBF00, 0, -19, 0x00, 0x38, 0x38, 0x00},
    {0xBE00, 0, -17, 0x00, 0x38, 0x38, 0x00}, {0xC100, 0, -17, 0x00, 0x38, 0x38, 0x00}, {0xC500, 0, -14, 0x00, 0x38, 0x38, 0x00}, {0xC700, 0, -16, 0x00, 0x38, 0x38, 0x00},
    {0xBE00, -4, -42, 0x01, 0x64, 0x64, 0x00}, {0xA100, -26, -40, 0x01, 0x64, 0x64, 0x00}, {0xBD02, -16, -13, 0x01, 0x64, 0x64, 0x00}, {0xBC00, 0, -32, 0x01, 0x64, 0x64, 0x00},
};

// clang-format off
static const DiskLoopFunc sDiskLoops[5] = {
    DiskLoop_Init, 
    DiskLoop_OpenScreen, 
    DiskLoop_Run, 
    DiskLoop_BlackOut, 
    DiskLoop_Exit,
};
// clang-format on
