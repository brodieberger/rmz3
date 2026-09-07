#include "ap.h"

#undef ApDiskMenuUpdate
#undef ApDiskShopUpdate

#include "disk.h"
#include "entity/player.h"
#include "game.h"
#include "global.h"
#include "gfx.h"
#include "gpu_regs.h"
#include "input.h"
#include "constants/song.h"
#include "sound.h"
#include "stagerun.h"
#include "text.h"
#include "widget/cursor_square.h"

#if AP

/*
  Cerveau's secret disk analysis screen. Modifications here include pressing select to
  analyze all disks, as well as the whole shop menu implementation.

  Still writes into the AP inventory.
*/

#define DISK_BITS(disks, i) ((disks)[(i) >> 2] >> ((i) & 3))
#define DISK_FOUND(bits) ((bits) & 1)
#define DISK_ANALYSED(bits) ((bits) & 0x10)
#define SHOP_STATE(g) ((g)->sceneState.disk.unk_0d)
#define SHOP_OPEN(g) (SHOP_STATE(g) != 0)
#define SHOP_SLOT(g) ((u8)(SHOP_STATE(g) - 1))
#define PANEL_X 0x11
#define PANEL_NUM_X (PANEL_X + 8)
#define HEADER_NUM_X 0x16
#define PROMPT_Y 0x12

/*
  The slot's icon is BG tilemap entries in menuBgMap1

    for sale   found but unread disks, which is the Archipelago pickup icon
    sold       temp: shows analysed disk, what the screen uses for one already read
    clear      0x2193, the panel's background, so empty
*/
#define PANEL_FILL_TILE 0x2193

#define GRID_TX 3
#define GRID_TY 3
#define GRID_W 10
#define GRID_H 12
#define GRID_EMPTY_TILE 0x31A2

static const u16 sIconForSale[4] = {0x80EB, 0x80EC, 0x810B, 0x810C};
static const u16 sIconSold[4] = {0x80ED, 0x80EE, 0x810D, 0x810E};
static const u16 sIconDim[4] = {0x816B, 0x816C, 0x816D, 0x816E};
static const u16 sIconAbsent[4] = {GRID_EMPTY_TILE, GRID_EMPTY_TILE,
                                   GRID_EMPTY_TILE, GRID_EMPTY_TILE};

#define LOGO_TILE 0x174
#define OWN_TILE 0x178 // temp
#define LOGO_PAL_DIM (AP_SHOP_PAL_FIRST + 3)

static void cellArt(u16* out, u16 tile, u8 bank) {
  u8 i;

  for (i = 0; i < 4; i++) {
    out[i] = (u16)((bank << 12) | (tile + i));
  }
}

static void loadShopPalettes(void) {
  u8 bank;
  u8 i;

  for (bank = 0; bank < AP_SHOP_PAL_COUNT; bank++) {
    for (i = 0; i < 16; i++) {
      gPaletteManager.buf[(AP_SHOP_PAL_FIRST + bank) * 16 + i] = gApShopPalettes[bank][i];
    }
  }
}

#define SHOP_SCROLL(g) ((g)->sceneState.disk.unk_08[1])
#define SGRID_COLS 5
#define SGRID_ROWS 6
#define SGRID_CELLS (SGRID_COLS * SGRID_ROWS)

/*
  Slide animation content, ripped from the pause menu
*/
#define SHOP_PAGE_X 256
#define SLIDE_STEP 16
#define SHOP_CLOSING 0xFF
#define BG1_X (BGOFS(1)->x & 0x1FF)
#define SHOP_DIR(g) ((g)->sceneState.disk.unk_08[0])
#define DIR_RIGHT 0
#define DIR_LEFT 1


/*
  The "Secret Disk" banner. Displays the word "Shop" when viewing the shop.
*/
#define BANNER_TX 1
#define BANNER_TY 1
#define BANNER_W 12
#define BANNER_SHOP_TILE 0x15F
#define BANNER_PALETTE 0x3000

/*
  Shop page reuses most graphics from the normal secret disk analysis screen, just with
  the grid not drawn.
*/
static void buildShopPage(struct GameState* g) {
  u16* src = g->menuBgMap1;
  u16* dst = g->menuBgMap2;
  u16 i;
  u8 tx;
  u8 ty;

  for (i = 0; i < 1024; i++) {
    dst[i] = src[i];
  }
  for (ty = GRID_TY; ty < GRID_TY + GRID_H; ty++) {
    for (tx = GRID_TX; tx < GRID_TX + GRID_W; tx++) {
      dst[ty * 32 + tx] = GRID_EMPTY_TILE;
    }
  }
  for (tx = 0; tx < BANNER_W; tx++) {
    dst[BANNER_TY * 32 + BANNER_TX + tx] = (u16)(BANNER_PALETTE | (BANNER_SHOP_TILE + tx));
  }
  (g->sceneState).disk.redraw = 1;
}

/* Slides BG1 either left or right. TRUE while the page is still moving. */
static bool32 slidePage(struct GameState* g, u16 target) {
  u16 x = BG1_X;

  if (x == target) {
    return FALSE;
  }
  x = (u16)((SHOP_DIR(g) == DIR_LEFT) ? (x - SLIDE_STEP) : (x + SLIDE_STEP));
  BGOFS(1)->x = x & 0x1FF;
  return TRUE;
}

static u8 shopSlots(void);
static u16 shopPrice(u8 slot);
static bool32 shopSold(u8 slot);

static bool32 paintCell(u16* map, u16 at, const u16* art) {
  if (map[at] == art[0]) {
    return FALSE;
  }
  map[at] = art[0];
  map[at + 1] = art[1];
  map[at + 32] = art[2];
  map[at + 33] = art[3];
  return TRUE;
}

/*
  The left panel, laid out exactly as the disk grid is on the other vanilla page
*/
static void paintSlotGrid(struct GameState* g) {
  u16* map = g->menuBgMap2;
  u8 slots = shopSlots();
  u16 ec = (g->z2->unk_b4).status.EC;
  bool32 changed = FALSE;
  u16 logo[4];
  u8 i;

  for (i = 0; i < SGRID_CELLS; i++) {
    u8 slot = (u8)(SHOP_SCROLL(g) * SGRID_COLS + i);
    const u16* art;
    u16 at = (u16)((GRID_TY + (i / SGRID_COLS) * 2) * 32 + GRID_TX + (i % SGRID_COLS) * 2);

    if (slot >= slots) {
      art = sIconAbsent;
    } else if (shopSold(slot)) {
      art = sIconSold;
    } else {
      u8 kind = gApShopItems[slot].kind;
      bool32 poor = shopPrice(slot) > ec;

      if (kind & AP_SHOP_IS_DISK) {
        art = poor ? sIconDim : sIconForSale;
      } else {
        cellArt(logo, (kind & AP_SHOP_OWN_WORLD) ? OWN_TILE : LOGO_TILE,
                (u8)(poor ? LOGO_PAL_DIM
                          : (AP_SHOP_PAL_FIRST + (kind & AP_SHOP_KIND_MASK))));
        art = logo;
      }
    }
    if (paintCell(map, at, art)) {
      changed = TRUE;
    }
  }
  if (changed) {
    (g->sceneState).disk.redraw = 1;
  }
}

/* Highlight cursor, same as vanilla. */
static void placeCursor(struct GameState* g) {
  struct SecretDiskState* d = &(g->sceneState).disk;
  u8 slot = SHOP_SLOT(g);

  if (d->cursor == NULL) {
    return;
  }
  d->cursor->px = (u16)(SHOP_PAGE_X + ((slot % SGRID_COLS) << 4) + 0x18);
  d->cursor->py = (u16)((((slot / SGRID_COLS) - SHOP_SCROLL(g)) << 4) + 0x18);
}

static u8 shopSlots(void) {
  u8 n;

  for (n = 0; n < AP_SHOP_SLOTS_MAX; n++) {
    if (gApShopPrices[n] == 0) {
      break;
    }
  }
  return n;
}

const u16 gApShopPrices[AP_SHOP_SLOTS_MAX] = {
    100, 150, 200, 250, 300, 100, 400, 200, 500, 150, 700, 300,
    100, 250, 200, 400, 300, 150, 500, 100, 200, 700, 250, 300,
    150, 400, 100, 200, 300, 500, 250, 150, 700, 100, 400, 200,
    300, 250, 150, 500, 200, 100, 400, 300, 700, 150, 250, 200,
};

static u16 shopPrice(u8 slot) {
  return gApShopPrices[slot];
}

/*
  Empty until the archipelago Rom.py patches them in.
*/
#define EMPTY_ITEM {{{AP_SHOP_TEXT_END}, {AP_SHOP_TEXT_END}, {AP_SHOP_TEXT_END}}, \
                    {{AP_SHOP_TEXT_END}, {AP_SHOP_TEXT_END}}, 0, {0}}

const struct ApShopItem gApShopItems[AP_SHOP_SLOTS_MAX] = {
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
    EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM, EMPTY_ITEM,
};

static bool32 shopSold(u8 slot) {
  u16 loc = (u16)(AP_SHOP_LOCATION_FIRST + slot);

  if (gAp.checkedLocations[loc >> 3] & (1 << (loc & 7))) {
    return TRUE;
  }
  return ApServerChecked(loc);
}

static bool32 anyUnread(void) {
  const u8* disks = gStageDiskManager.disk;
  u16 i;

  for (i = 0; i < DISK_COUNT; i++) {
    u8 bits = DISK_BITS(disks, i);
    if (DISK_FOUND(bits) && !DISK_ANALYSED(bits)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*
  Read all found disks.
*/
static void readAll(struct GameState* g) {
  u16 i;

  for (i = 0; i < DISK_COUNT; i++) {
    if (DISK_FOUND(DISK_BITS(gStageDiskManager.disk, i))) {
      OpenSecretDisk(g, (u8)i, FALSE);
    }
  }

  PlaySound(14);
  (g->sceneState).disk.redraw = 1;
}

static void buy(struct GameState* g, u8 slot) {
  struct ZeroStatus* st = &(g->z2->unk_b4).status;
  u16 price = shopPrice(slot);

  if (shopSold(slot) || st->EC < price) {
    PlaySound(4);
    return;
  }

  st->EC -= price;
  ApMarkLocationChecked((u16)(AP_SHOP_LOCATION_FIRST + slot));
  PlaySound(14);
}

/*
  Runs before the grid sub-loop, and returning TRUE is what stops that sub-loop running.
  WIP: while the shop is up it takes over the d-pad and the A and B buttons. This is temporary.
*/
bool32 ApDiskShopUpdate(struct GameState* g) {
  u8 slots = shopSlots();
  u16 pressed = gJoypad[0].pressed;
  u8 slot;
  u8 moved;
  u8 row;

  if (slots == 0) {
    return FALSE;
  }

  /* Stop anything else from happening while the page is turning. */
  if (slidePage(g, SHOP_STATE(g) == SHOP_CLOSING ? 0 : (SHOP_OPEN(g) ? SHOP_PAGE_X : 0))) {
    return TRUE;
  }
  if (SHOP_STATE(g) == SHOP_CLOSING) {
    SHOP_STATE(g) = 0;
    return TRUE;
  }

  if (!SHOP_OPEN(g)) {
    // Only from the grid itself, not from the window opening or closing over it.
    if (g->mode[2] == 0 && (pressed & (L_BUTTON | R_BUTTON))) {
      buildShopPage(g);
      loadShopPalettes();
      SHOP_DIR(g) = (pressed & L_BUTTON) ? DIR_LEFT : DIR_RIGHT;
      SHOP_SCROLL(g) = 0;
      SHOP_STATE(g) = 1;
      PlaySound(SE_MENU_SLIDE);
      return TRUE;
    }
    return FALSE;
  }

  // L and R tab to and from the screen.
  if (pressed & (L_BUTTON | R_BUTTON)) {
    SHOP_DIR(g) = (pressed & L_BUTTON) ? DIR_LEFT : DIR_RIGHT;
    SHOP_STATE(g) = SHOP_CLOSING;
    PlaySound(SE_MENU_SLIDE);
    return TRUE;
  }

  // B leaves the whole screen.
  if (pressed & B_BUTTON) {
    g->mode[1] = 3;
    return TRUE;
  }

  slot = SHOP_SLOT(g);
  moved = slot;
  if ((pressed & DPAD_RIGHT) && slot + 1 < slots) {
    moved = (u8)(slot + 1);
  } else if ((pressed & DPAD_LEFT) && slot > 0) {
    moved = (u8)(slot - 1);
  } else if ((pressed & DPAD_DOWN) && slot + SGRID_COLS < slots) {
    moved = (u8)(slot + SGRID_COLS);
  } else if ((pressed & DPAD_UP) && slot >= SGRID_COLS) {
    moved = (u8)(slot - SGRID_COLS);
  } else if (pressed & A_BUTTON) {
    buy(g, slot);
  }

  if (moved != slot) {
    SHOP_STATE(g) = (u8)(moved + 1);
    PlaySound(1);
    row = (u8)(moved / SGRID_COLS);
    if (row < SHOP_SCROLL(g)) {
      SHOP_SCROLL(g) = row;
    } else if (row >= SHOP_SCROLL(g) + SGRID_ROWS) {
      SHOP_SCROLL(g) = (u8)(row - SGRID_ROWS + 1);
    }
  }
  return TRUE;
}

/*
  Right side information panel.
*/
static void drawShop(struct GameState* g) {
  const struct ApShopItem* item;
  u8 slot = SHOP_SLOT(g);
  u8 i;

  // The header box labels the number below it, also says SOLD.
  PrintString(shopSold(slot) ? gApShopSoldText : gApShopCostText, PANEL_X, 1);

  // like 300/5000: what it costs against what you are holding.
  PrintNumber(shopPrice(slot), PANEL_X + 3, 4);
  PrintString(gApShopSlashText, PANEL_X + 4, 4);
  PrintNumber((g->z2->unk_b4).status.EC, PANEL_X + 8, 4);

  item = &gApShopItems[slot];
  for (i = 0; i < AP_SHOP_NAME_LINES; i++) {
    PrintString(item->name[i], PANEL_X, (u8)(6 + i * 2));
  }
  // Blank for your own items.
  for (i = 0; i < AP_SHOP_PLAYER_LINES; i++) {
    PrintString(item->player[i], PANEL_X, (u8)(12 + i * 2));
  }

  PrintString(gApShopPromptText, 1, PROMPT_Y);
}

/*
  Draws over diskloop run
*/
void ApDiskMenuUpdate(struct GameState* g) {
  const char_t* hint;
  u8 cursorBits;
  bool32 unread;

  if (SHOP_OPEN(g)) {
    // todo, the text wouldnt render right when its sliding.
    if (SHOP_STATE(g) != SHOP_CLOSING && BG1_X == SHOP_PAGE_X) {
      paintSlotGrid(g);
      placeCursor(g);
      drawShop(g);
    }
    return;
  }

  // mode[2] is the sub-loop: 0 is the grid, 1 and 2 are the window opening and closing.
  if (g->mode[2] != 0) {
    return;
  }

  unread = anyUnread();
  if (unread) {
    hint = shopSlots() ? gApDiskOpenAllShopText : gApDiskOpenAllText;
  } else if (shopSlots()) {
    hint = gApDiskShopHintText;
  } else {
    return;
  }

  cursorBits = DISK_BITS(gStageDiskManager.disk, (g->sceneState).disk.cursorDisk);
  if (!DISK_FOUND(cursorBits) || DISK_ANALYSED(cursorBits)) {
    PrintString(hint, 1, PROMPT_Y);
  }

  if (unread && (gJoypad[0].pressed & SELECT_BUTTON)) {
    readAll(g);
  }
}

void (*const gApDiskMenuUpdateFn)(struct GameState* g) = ApDiskMenuUpdate;
bool32 (*const gApDiskShopUpdateFn)(struct GameState* g) = ApDiskShopUpdate;

#endif /* AP */
