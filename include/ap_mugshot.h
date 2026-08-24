#ifndef GUARD_RMZ3_AP_MUGSHOT_H
#define GUARD_RMZ3_AP_MUGSHOT_H

#include "gba/gba.h"
#include "motion.h"

/*
  Mission select portraits for the four stages the game has none for.
*/

#define AP_MUGSHOT_COUNT 4
#define AP_MUGSHOT_TILES 64
/*
  The tiles need this offset due to how they are stored
*/
#define AP_MUGSHOT_SHIFT 16
#define AP_MUGSHOT_TILE 740
#define AP_MUGSHOT_PAL 8

#define AP_MUGSHOT_FRAME_SLOT 1
#define AP_MUGSHOT_FRAME_INNER 15

extern const u16 gApMugshotPalette[AP_MUGSHOT_COUNT][16];
extern const u32 gApMugshotTiles[AP_MUGSHOT_COUNT * AP_MUGSHOT_TILES][8];

#endif  // GUARD_RMZ3_AP_MUGSHOT_H
