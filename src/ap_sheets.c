#include "ap.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "spawn.h"

#include "constants/motion/ap_sheet.h"

#if AP

/*
  Extended sprite sheet table
*/

extern const ColorGraphic gApSheetGraphics[];

EWRAM_DATA u16 gApSheetTilenums[AP_SHEET_COUNT] = {0};
EWRAM_DATA u16 gApSheetPalIDs[AP_SHEET_COUNT] = {0};

void ApSetSheetWindow(const struct PreloadEntity* row) {
  gApSheetTilenums[row->id] = row->tileBase;
  gApSheetPalIDs[row->id] = row->palID;
}

void ApLoadSheet(const struct PreloadEntity* row) {
  const ColorGraphic* g = &gApSheetGraphics[row->id];
  ApSetSheetWindow(row);
  LoadGraphic(&g->g, (void*)((row->tileBase - (g->g).tileId) * 32 + 0x10000));
  LoadPalette(&g->pal, (row->palID - (g->pal).dst) * 32 + PLTT_SIZE / 2);
}

#endif  // AP
