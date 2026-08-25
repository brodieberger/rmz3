#ifndef GUARD_RMZ3_AP_ORBIT_H
#define GUARD_RMZ3_AP_ORBIT_H

#include "gba/gba.h"
#include "motion.h"

/*
  The Archipelago logo, which orbits unchecked items
*/

#define AP_ORBIT_DOTS 6
#define AP_ORBIT_FRAMES 8

#define AP_ORBIT_STEPS (AP_ORBIT_FRAMES * AP_ORBIT_DOTS)
#define AP_ORBIT_TILE_COUNT (AP_ORBIT_DOTS * 2)

#define AP_ORBIT_STEP_FRAMES 2

#define AP_ORBIT_TILE 954
#define AP_ORBIT_PAL 2


#define AP_ORBIT_RADIUS 13
#define AP_ORBIT_CENTER_Y (-5)

struct ApOrbitSprite {
  struct MetaspriteHeader hdr[AP_ORBIT_FRAMES];
  struct Subsprite dot[AP_ORBIT_FRAMES][AP_ORBIT_DOTS];
};

extern const u16 gApOrbitPalette[16];
extern const u32 gApOrbitTiles[AP_ORBIT_TILE_COUNT][8];
extern const struct ApOrbitSprite gApOrbitSprite;

#endif  // GUARD_RMZ3_AP_ORBIT_H
