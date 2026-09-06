#include "ap.h"

#undef ApDiskMenuUpdate
#undef ApDiskShopUpdate

#include "disk.h"
#include "entity/player.h"
#include "game.h"
#include "global.h"
#include "input.h"
#include "sound.h"
#include "stagerun.h"
#include "text.h"

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
#define PROMPT_Y 0x12

static u8 shopSlots(void) {
  u8 n = gApSeedConfig.shopSlots;

  return (n > AP_SHOP_SLOTS_MAX) ? AP_SHOP_SLOTS_MAX : n;
}

/*
  Slot n costs shopPriceBase * (n + 1) eCrystals. Set by player via options.
*/
static u16 shopPrice(u8 slot) {
  return (u16)(gApSeedConfig.shopPriceBase * (slot + 1));
}

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

  if (slots == 0) {
    return FALSE;
  }

  if (!SHOP_OPEN(g)) {
    // Only from the grid itself, not from the window opening or closing over it.
    if (g->mode[2] == 0 && (pressed & (L_BUTTON | R_BUTTON))) {
      SHOP_STATE(g) = 1;
      PlaySound(1);
      return TRUE;
    }
    return FALSE;
  }

  if (pressed & B_BUTTON) {
    SHOP_STATE(g) = 0;
    PlaySound(3);
    return TRUE;
  }

  if (pressed & R_BUTTON) {
    SHOP_STATE(g) = (u8)((SHOP_SLOT(g) + 1) % slots + 1);
    PlaySound(1);
  } else if (pressed & L_BUTTON) {
    SHOP_STATE(g) = (u8)((SHOP_SLOT(g) + slots - 1) % slots + 1);
    PlaySound(1);
  } else if (pressed & A_BUTTON) {
    buy(g, SHOP_SLOT(g));
  }
  return TRUE;
}

static void drawShop(struct GameState* g) {
  u8 slot = SHOP_SLOT(g);

  PrintString(gApShopTitleText, PANEL_X, 1);
  PrintString(gApShopSlotText, PANEL_X, 4);
  PrintNumber((u16)(slot + 1), PANEL_NUM_X, 4);
  PrintString(gApShopCostText, PANEL_X, 6);
  PrintNumber(shopPrice(slot), PANEL_NUM_X, 6);
  PrintString(gApShopHaveText, PANEL_X, 8);
  PrintNumber((g->z2->unk_b4).status.EC, PANEL_NUM_X, 8);

  if (shopSold(slot)) {
    PrintString(gApShopSoldText, PANEL_X, 10);
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
    drawShop(g);
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
