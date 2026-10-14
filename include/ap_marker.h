#ifndef GUARD_RMZ3_AP_MARKER_H
#define GUARD_RMZ3_AP_MARKER_H

#include "constants/motion/static.h"
#include "gba/gba.h"
#include "motion.h"

/*
  The Archipelago logo that floats over an unchecked pickup.

  1-UPs 16x16 sprite
  Other itemsanity 8x8 sprite
*/

#define AP_MARKER_SMALL_TILES 1
#define AP_MARKER_BIG_MOTION SM176_RESULT_DISK
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

extern const u32 gApMarkerTiles[AP_MARKER_SMALL_TILES][8];
extern const struct ApMarkerSprite gApMarkerSprite;
extern const s8 gApMarkerBob[AP_MARKER_BOB_PERIOD];

/*
  The column a randomized Pillar Cannon is connected to.
*/
#define AP_PILLAR_TILES 2
#define AP_PILLAR_FLOOR 4 /* the most tiles that a Pillar Cannon is put above the floor */
#define AP_PILLAR_MAX ((AP_PILLAR_FLOOR + 2) * 2)

struct ApPillarSprite {
  struct MetaspriteHeader hdr[AP_PILLAR_MAX];
  struct Subsprite part[AP_PILLAR_MAX * (AP_PILLAR_MAX + 1) / 2];
};

extern const u32 gApPillarTiles[AP_PILLAR_TILES][8];
extern const struct ApPillarSprite gApPillarSprite;
#define AP_MARKER_STAGES 18
#define AP_MARKER_AREAS 8
extern const u16 gApMarkerTile[AP_MARKER_STAGES][AP_MARKER_AREAS];
extern const u16 gApPillarTile[AP_MARKER_STAGES][AP_MARKER_AREAS];
u16 ApMarkerWindow(void);
u16 ApPillarWindow(void);

#endif  // GUARD_RMZ3_AP_MARKER_H
