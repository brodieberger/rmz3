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

extern const struct Graphic gGraphic_MiscMenu;
extern const struct Palette gPalette_MiscMenu;
extern const struct Graphic Graphic_SecretDickBlue;
extern const struct Palette Palette_SecretDickBlue;
extern const struct Graphic Graphic_SecretDickRed;
extern const struct Palette Palette_SecretDickRed;

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

static void DiskLoop_Init(struct GameState* g) {
  struct SecretDiskState* d;
  u16* pal;
  u16* src;
  u8 i;
  int cbs;
  s16 gfxOfs;
  const struct Graphic* menuGfx;

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
  gfxOfs = sizeof(ColorGraphic) * 14;
  gBlendRegBuffer.bldclt = 0x2010;

  menuGfx = &gGraphic_MiscMenu;
  cbs = 0xc;
  LoadGraphic(menuGfx, (void*)0x4000);
  LoadPalette(&gPalette_MiscMenu, 0);
  CopyBgMap(g->menuBgMap1, SELF_REL_PTR(&gBgMapOffsets[101]), 0, 0);

  if (gSystemSavedata.disk == 1) {
    LoadGraphic(&Graphic_SecretDickBlue, ((void*)((BGCNT16(1) & 0xc) << cbs)));
    LoadPalette(&Palette_SecretDickBlue, 0);
  } else if (gSystemSavedata.disk == 2) {
    LoadGraphic(&Graphic_SecretDickRed, ((void*)((BGCNT16(1) & 0xc) << cbs)));
    LoadPalette(&Palette_SecretDickRed, 0);
  }

  setSecretDiskPalette(g);
  {
    const struct Graphic* g;
    const struct Palette* pal;
    u32 ofs;
    ofs = gfxOfs;
    g = gStaticGraphic(ofs);
    LoadGraphic(g, (void*)((wStaticGraphicTilenums[14] - g->tileId) * 32 + 0x10000));
    pal = gStaticPalette(ofs);
    LoadPalette(pal, (wStaticMotionPalIDs[14] - pal->dst) * 32 + PLTT_SIZE / 2);
  }
  {
    const struct Graphic* g;
    const struct Palette* pal;
    u32 ofs;
    ofs = sizeof(ColorGraphic) * 83;
    g = gStaticGraphic(ofs);
    LoadGraphic(g, (void*)((wStaticGraphicTilenums[83] - g->tileId) * 32 + 0x10000));
    src = STATIC_PALETTES + ofs;
    pal = (const struct Palette*)src;
    LoadPalette(pal, (wStaticMotionPalIDs[83] - pal->dst) * 32 + PLTT_SIZE / 2);
  }

  CreateTriangleCursor(g, 3);
  CreateTriangleCursor(g, 4);
  createSecretDiskModalBorder(g, 0);
  createSecretDiskModalBorder(g, 1);
  createSecretDiskModalBorder(g, 2);
  createSecretDiskModalBorder(g, 3);
  StartPaletteAnimation(0x40, 0);

  i = 0;
  pal = &gPaletteManager.buf[144];
  src = pal - 16;
  for (; i <= 0xF; i++) {
    pal[i] = src[i];
  }

  RequestBgMapTransfer(g->menuBgMap1, (void*)SCREEN_BASE(1), 0x1000);
  g->mode[1] = 1;
  DiskLoop_OpenScreen(g);
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

static void DiskLoop_Run(struct GameState* g) {
  struct SecretDiskState* d;
  struct SecretDiskState* d2;
  struct SecretDiskState* d3;
  u32 diskNo;
  u8 disk;
  u16 amount;
  u16 digits;
  u32 ix;
  u8 nb;
  u8* fb;
  s16 six;

  d = &g->sceneState.disk;
  d->redraw = 0;
  PTR_ARRAY_083864ac[g->mode[2]](g);

  if (gJoypad[0].pressed & START_BUTTON) {
    g->mode[1] = 3;
  }

  PrintString(STRING(0x1DE), 0x11, 1);
  printThreeDigitNumber(d->cursorDisk + 1, 0x16, 1);

  fb = gStageDiskManager.disk;
  diskNo = (u8)(*(u16*)&d->cursorDisk);
  disk = diskNo;
  nb = disk >> 2;
  if ((((fb[nb] & 0xF) >> (diskNo & 3)) & 1) != 0) {
    if (((fb[nb] >> ((diskNo & 3) + 4)) & 1) != 0) {
      if (disk <= 5) {
        six = 0x2BC + d->cursorDisk;
        PrintString(STRING(six), 0x11, 4);
      } else if (disk <= 0x13) {
        six = 0x2BC + d->cursorDisk;
        PrintString(STRING(six), 0x11, 4);
      } else if (disk <= 0x5D) {
        nb = d->cursorDisk;
        do { ix = nb + 0x50; } while (0);
        PrintString(STRING(0x2D0), 0x11, 4);
        PrintString(STRING(ix), 0x11, 6);
        PrintString(STRING(0x2D1), getStringLength((char_t*)STRING(ix)) + 0x11, 6);
        PrintString(STRING(0x2D2), 0x11, 8);
      } else {
        if (disk <= 0x6D) {
          PrintString(STRING(0x2D3), 0x11, 4);
#if IS_US
          digits = 0;
          amount = DiskECrystalAmounts[d->cursorDisk - 0x5E];
          while (amount != 0) {
            do { amount = amount / 10; digits++; } while (0);
          }
          PrintNumber(amount = DiskECrystalAmounts[(&g->sceneState.disk)->cursorDisk - 0x5E], digits + 0x10, 4);
          PrintString(STRING(0x2D4), 0x11, 6);
#else
          ix = 0;
          amount = DiskECrystalAmounts[d->cursorDisk - 0x5E];
          while (amount != 0) {
            do { amount = amount / 10; ix = (u16)(ix + 1); } while (0);
          }
          PrintNumber(amount = DiskECrystalAmounts[(&g->sceneState.disk)->cursorDisk - 0x5E], ix + 0x11, 6);
          PrintString(STRING(0x2D4), ix + 0x12, 6);
#endif
          PrintString(STRING(0x2D5), 0x11, 8);
        } else {
          nb = d->cursorDisk;
          PrintString(STRING(0x268 + nb), 0x11, 4);
        }
      }
      PrintString(STRING(0x1DD), 1, 0x12);
    } else {
      PrintString(STRING(0x1DF), 0x11, 4);
      PrintString(STRING(0x1DC), 1, 0x12);
    }
  } else {
    PrintString(STRING(0x1DD), 1, 0x12);
  }

  d2 = &g->sceneState.disk;
  if (d2->winHalfW != 0) {
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
  d3 = &g->sceneState.disk;
  if (d3->redraw) {
    setSecretDiskPalette(g);
  }
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

static void sd_analysis_080f875c(struct GameState* g) {
  struct SecretDiskState* d;
  struct SecretDiskState* d2;
  struct SecretDiskState* d3;
  struct SecretDiskState* d4;
  const struct SecretDiskEntry* e;
  const struct SecretDiskEntry* tbl;
  u8* bits;
  u16* pal;
  u16* dst;
  u8 r;
  u32 gr, b;
  u32 tr, tg, tb;
  u16 cur;
  u16 target;
  u8 t;
  u16 i;

  if (g->mode[3] == 0) {
    bits = gStageDiskManager.disk;
    d = &g->sceneState.disk;
    if (((bits[d->cursorDisk >> 2] >> ((d->cursorDisk & 3) + 4)) & 1) != 0) {
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
    tb = 0x1F;
    b = (cur >> 10) & tb;
    tb = ((target >> 10) & 0x1F) >> 1;
    if (b > tb) b = (u8)(b - 1);
    pal[i] = (b << 10) | (gr << 5) | r;
  }

  tbl = gSecretDiskEntries;
  d4 = &g->sceneState.disk;
  if (tbl[d4->cursorDisk].unk_00 != 0) {
    t = (u8)tbl[d4->cursorDisk].rate0 >> 1;
    if (d4->winHalfW < t) {
      d4->winHalfW += tbl[d4->cursorDisk].rate0 >> 4;
      d4->winHalfH += tbl[d4->cursorDisk].rate1 >> 4;
      if (d4->winHalfW > (tbl[d4->cursorDisk].rate0 >> 1)) {
        d4->winHalfW = tbl[d4->cursorDisk].rate0 >> 1;
      }
      if (d4->winHalfH > (tbl[d4->cursorDisk].rate1 >> 1)) {
        d4->winHalfH = tbl[d4->cursorDisk].rate1 >> 1;
      }
    } else {
      d4->winHalfW = t;
      d4->winHalfH = tbl[d4->cursorDisk].rate1 >> 1;
      if (g->mode[3] == 1) {
        e = &tbl[d4->cursorDisk];
        FUN_080e83d0(g, d4->cursorDisk, e->unk_04, e->unk_00,
                     (0x40 - tbl[d4->cursorDisk].x) << 8,
                     (0x50 - tbl[d4->cursorDisk].y) << 8,
                     tbl[d4->cursorDisk].unk_07);
        g->mode[3]++;
      }
    }
  }

  if (gJoypad[0].pressed & (A_BUTTON | B_BUTTON)) {
    PlaySound(3);
    g->mode[2]++;
  }
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
