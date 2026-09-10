/* Auto generated marker sprites. The Archipelago logo drawn over an unchecked pickup 8x8 Sprite. */
#include "ap_marker.h"
#include "global.h"

#if AP

const u32 gApMarkerTiles[AP_MARKER_SMALL_TILES][8] = {
    {0x000FF000, 0x0FFBBFF0, 0xF33BBDDF, 0xF33FFDDF, 0xF99FF55F, 0xF99CC55F, 0x0FFCCFF0, 0x000FF000,},  /* 8x8 */
};

const struct ApMarkerSprite gApMarkerSprite = {
    hdr : {
      {ofs : 8, subspriteCount : 1, texture : 0},  /* small */
      {ofs : 12, subspriteCount : 1, texture : 0},  /* big */
    },
    part : {
      {tileNum : 0, size : 0, shape : 0, x : -4, y : -4},
      {tileNum : 0, size : 1, shape : 0, x : -8, y : -8},
    },
};

const s8 gApMarkerBob[AP_MARKER_BOB_PERIOD] = {
    0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, 0, 0,
};

#endif /* AP */
