/* Auto generated marker sprites. The Archipelago logo drawn over an unchecked pickup, 8x8 and 16x16 sprites. */
#include "ap_marker.h"
#include "global.h"

#if AP

const u32 gApMarkerTiles[AP_MARKER_TILE_COUNT][8] = {
    {0x000FF000, 0x0FFBBFF0, 0xF33BBDDF, 0xF33FFDDF, 0xF99FF55F, 0xF99CC55F, 0x0FFCCFF0, 0x000FF000,},  /* 8x8 */
    {0xF0000000, 0xBF000000, 0xBBF00000, 0xBBFFFF00, 0xBFFFDDF0, 0xFFFDDDDF, 0x0FFDDDDF, 0x00FFFFF0,},  /* 16x16 quadrant 0 */
    {0x0000000F, 0x000000FB, 0x00000FBB, 0x00FFFFBB, 0x0F33FFFB, 0xF3333FFF, 0xF3333FF0, 0x0FFFFF00,},  /* 16x16 quadrant 1 */
    {0x00FF55F0, 0x0FF5555F, 0xFFF5555F, 0xCFFF55F0, 0xCCFFFF00, 0xCCF00000, 0xCF000000, 0xF0000000,},  /* 16x16 quadrant 2 */
    {0x0F99FF00, 0xF9999FF0, 0xF9999FFF, 0x0F99FFFC, 0x00FFFFCC, 0x00000FCC, 0x000000FC, 0x0000000F,},  /* 16x16 quadrant 3 */
};

const struct ApMarkerSprite gApMarkerSprite = {
    hdr : {
      {ofs : 8, subspriteCount : 1, texture : 0},  /* small */
      {ofs : 12, subspriteCount : 1, texture : 0},  /* big */
    },
    part : {
      {tileNum : 0, size : 0, shape : 0, x : -4, y : -4},
      {tileNum : 1, size : 1, shape : 0, x : -8, y : -8},
    },
};

const s8 gApMarkerBob[AP_MARKER_BOB_PERIOD] = {
    0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, 0, 0,
};

#endif /* AP */
