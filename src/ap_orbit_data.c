/* Six dots and their orbit, for the marker on an unchecked item in itemsanity. */
#include "ap_orbit.h"
#include "global.h"

#if AP

const u32 gApOrbitTiles[AP_ORBIT_TILE_COUNT][8] = {
    {0x00000000, 0x000AA000, 0x00ACCA00, 0x0ACCCCA0, 0x0ACCCCA0, 0x00ACCA00, 0x000AA000, 0x00000000,},
    {0x00000000, 0x00044000, 0x00455400, 0x04555540, 0x04555540, 0x00455400, 0x00044000, 0x00000000,},
    {0x00000000, 0x000DD000, 0x00DEED00, 0x0DEEEED0, 0x0DEEEED0, 0x00DEED00, 0x000DD000, 0x00000000,},
    {0x00000000, 0x000AA000, 0x00ABBA00, 0x0ABBBBA0, 0x0ABBBBA0, 0x00ABBA00, 0x000AA000, 0x00000000,},
    {0x00000000, 0x00022000, 0x00233200, 0x02333320, 0x02333320, 0x00233200, 0x00022000, 0x00000000,},
    {0x00000000, 0x00077000, 0x00799700, 0x07999970, 0x07999970, 0x00799700, 0x00077000, 0x00000000,},
    {0x00000000, 0x000AA000, 0x00ACCA00, 0x0ACCCCA0, 0x0ACCCCA0, 0x00ACCA00, 0x000AA000, 0x00000000,},
    {0x00000000, 0x00044000, 0x00455400, 0x04555540, 0x04555540, 0x00455400, 0x00044000, 0x00000000,},
    {0x00000000, 0x000DD000, 0x00DEED00, 0x0DEEEED0, 0x0DEEEED0, 0x00DEED00, 0x000DD000, 0x00000000,},
    {0x00000000, 0x000AA000, 0x00ABBA00, 0x0ABBBBA0, 0x0ABBBBA0, 0x00ABBA00, 0x000AA000, 0x00000000,},
    {0x00000000, 0x00022000, 0x00233200, 0x02333320, 0x02333320, 0x00233200, 0x00022000, 0x00000000,},
    {0x00000000, 0x00077000, 0x00799700, 0x07999970, 0x07999970, 0x00799700, 0x00077000, 0x00000000,},
};

const struct ApOrbitSprite gApOrbitSprite = {
    hdr : {
      {ofs : 32, subspriteCount : 6, texture : 0},
      {ofs : 56, subspriteCount : 6, texture : 0},
      {ofs : 80, subspriteCount : 6, texture : 0},
      {ofs : 104, subspriteCount : 6, texture : 0},
      {ofs : 128, subspriteCount : 6, texture : 0},
      {ofs : 152, subspriteCount : 6, texture : 0},
      {ofs : 176, subspriteCount : 6, texture : 0},
      {ofs : 200, subspriteCount : 6, texture : 0},
    },
    dot : {
      {{tileNum : 0, x : 9, y : -9}, {tileNum : 1, x : 3, y : 2}, {tileNum : 2, x : -10, y : 2}, {tileNum : 3, x : -17, y : -9}, {tileNum : 4, x : -11, y : -20}, {tileNum : 5, x : 3, y : -20}},
      {{tileNum : 0, x : 9, y : -7}, {tileNum : 1, x : 1, y : 3}, {tileNum : 2, x : -12, y : 1}, {tileNum : 3, x : -17, y : -11}, {tileNum : 4, x : -9, y : -21}, {tileNum : 5, x : 4, y : -19}},
      {{tileNum : 0, x : 9, y : -6}, {tileNum : 1, x : -1, y : 4}, {tileNum : 2, x : -13, y : 0}, {tileNum : 3, x : -17, y : -12}, {tileNum : 4, x : -7, y : -22}, {tileNum : 5, x : 5, y : -18}},
      {{tileNum : 0, x : 8, y : -4}, {tileNum : 1, x : -2, y : 4}, {tileNum : 2, x : -14, y : -1}, {tileNum : 3, x : -16, y : -14}, {tileNum : 4, x : -6, y : -22}, {tileNum : 5, x : 6, y : -17}},
      {{tileNum : 0, x : 7, y : -3}, {tileNum : 1, x : -4, y : 4}, {tileNum : 2, x : -15, y : -3}, {tileNum : 3, x : -15, y : -16}, {tileNum : 4, x : -4, y : -22}, {tileNum : 5, x : 7, y : -16}},
      {{tileNum : 0, x : 6, y : -1}, {tileNum : 1, x : -6, y : 4}, {tileNum : 2, x : -16, y : -4}, {tileNum : 3, x : -14, y : -17}, {tileNum : 4, x : -2, y : -22}, {tileNum : 5, x : 8, y : -14}},
      {{tileNum : 0, x : 5, y : 0}, {tileNum : 1, x : -7, y : 4}, {tileNum : 2, x : -17, y : -6}, {tileNum : 3, x : -13, y : -18}, {tileNum : 4, x : -1, y : -22}, {tileNum : 5, x : 9, y : -12}},
      {{tileNum : 0, x : 4, y : 1}, {tileNum : 1, x : -9, y : 3}, {tileNum : 2, x : -17, y : -7}, {tileNum : 3, x : -12, y : -19}, {tileNum : 4, x : 1, y : -21}, {tileNum : 5, x : 9, y : -11}},
    },
};

#endif /* AP */
