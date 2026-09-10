#ifndef GUARD_RMZ3_AP_MARKER_H
#define GUARD_RMZ3_AP_MARKER_H

#include "gba/gba.h"
#include "motion.h"

/*
  The Archipelago logo that floats over an unchecked pickup.

  1-UPs 16x16 sprite
  Other itemsanity 8x8 sprite
*/

#define AP_MARKER_TILE 1015
#define AP_MARKER_SMALL_TILES 1
#define AP_MARKER_BIG_TILES 4
#define AP_MARKER_TILE_COUNT (AP_MARKER_SMALL_TILES + AP_MARKER_BIG_TILES)
#define AP_MARKER_PAL 11
#define AP_MARKER_SMALL 0
#define AP_MARKER_BIG 1
#define AP_MARKER_FRAMES 2
#define AP_MARKER_BOB_PERIOD 64
#define AP_MARKER_BOB_AMPLITUDE 2
#define AP_MARKER_CENTER_Y (-24)

struct ApMarkerSprite {
  struct MetaspriteHeader hdr[AP_MARKER_FRAMES];
  struct Subsprite part[AP_MARKER_FRAMES];
};

extern const u32 gApMarkerTiles[AP_MARKER_TILE_COUNT][8];
extern const struct ApMarkerSprite gApMarkerSprite;
extern const s8 gApMarkerBob[AP_MARKER_BOB_PERIOD];

/*
  For the marker's tiles.
*/
#define AP_MARKER_STAGES 18
#define AP_MARKER_AREAS 8
extern const u16 gApMarkerTile[AP_MARKER_STAGES][AP_MARKER_AREAS];

#endif  // GUARD_RMZ3_AP_MARKER_H
