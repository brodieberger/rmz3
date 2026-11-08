// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Naold1_Templates[17] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [2] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [3] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [4] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_BOX, 0, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 1, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 0, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 0, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 1, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 82, 0),
        },
    [13] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 83, 0),
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FALLEN, 38, 0),
            .attr = 0x02,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FALLEN, 38, 1),
            .attr = 0x02,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FALLEN, 38, 2),
            .attr = 0x02,
        },
};

const struct SpawnPoint gApZ2Naold1_Points[64] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(496, 448), 16},
    [2] = {SpawnPixelCoords(544, 448), 14},
    [3] = {SpawnPixelCoords(656, 448), 15},
    [4] = {SpawnPixelCoords(736, 336), 9},
    [5] = {SpawnPixelCoords(784, 448), 14},
    [6] = {SpawnPixelCoords(912, 416), 6},
    [7] = {SpawnPixelCoords(960, 272), 9},
    [8] = {SpawnPixelCoords(1072, 272), 9},
    [9] = {SpawnPixelCoords(1184, 272), 9},
    [10] = {SpawnPixelCoords(1296, 272), 9},
    [11] = {SpawnPixelCoords(1392, 448), 7},
    [12] = {SpawnPixelCoords(1408, 272), 9},
    [13] = {SpawnPixelCoords(1536, 464), 6},
    [14] = {SpawnPixelCoords(1584, 352), 7},
    [15] = {SpawnPixelCoords(1648, 432), 9},
    [16] = {SpawnPixelCoords(1680, 352), 12},
    [17] = {SpawnPixelCoords(1776, 432), 9},
    [18] = {SpawnPixelCoords(1904, 464), 9},
    [19] = {SpawnPixelCoords(2144, 512), 6},
    [20] = {SpawnPixelCoords(2224, 512), 6},
    [21] = {SpawnPixelCoords(2336, 512), 7},
    [22] = {SpawnPixelCoords(2560, 464), 9},
    [23] = {SpawnPixelCoords(2704, 432), 9},
    [24] = {SpawnPixelCoords(2880, 496), 6},
    [25] = {SpawnPixelCoords(2928, 608), 14},
    [26] = {SpawnPixelCoords(2976, 496), 11},
    [27] = {SpawnPixelCoords(2976, 576), 11},
    [28] = {SpawnPixelCoords(3040, 528), 3},
    [29] = {SpawnPixelCoords(3040, 608), 1},
    [30] = {SpawnPixelCoords(3168, 416), 6},
    [31] = {SpawnPixelCoords(3392, 368), 11},
    [32] = {SpawnPixelCoords(3488, 480), 15},
    [33] = {SpawnPixelCoords(3616, 272), 13},
    [34] = {SpawnPixelCoords(3664, 416), 10},
    [35] = {SpawnPixelCoords(3680, 272), 7},
    [36] = {SpawnPixelCoords(3776, 336), 6},
    [37] = {SpawnPixelCoords(3936, 176), 9},
    [38] = {SpawnPixelCoords(3936, 304), 6},
    [39] = {SpawnPixelCoords(4048, 176), 9},
    [40] = {SpawnPixelCoords(4096, 272), 16},
    [41] = {SpawnPixelCoords(4160, 176), 9},
    [42] = {SpawnPixelCoords(4272, 176), 9},
    [43] = {SpawnPixelCoords(4304, 304), 15},
    [44] = {SpawnPixelCoords(4352, 384), 7},
    [45] = {SpawnPixelCoords(4512, 416), 6},
    [46] = {SpawnPixelCoords(4544, 416), 6},
    [47] = {SpawnPixelCoords(4576, 416), 6},
    [48] = {SpawnPixelCoords(4736, 352), 9},
    [49] = {SpawnPixelCoords(4864, 336), 9},
    [50] = {SpawnPixelCoords(4880, 400), 14},
    [51] = {SpawnPixelCoords(4992, 432), 6},
    [52] = {SpawnPixelCoords(5024, 432), 6},
    [53] = {SpawnPixelCoords(5056, 432), 6},
    [54] = {SpawnPixelCoords(5152, 400), 6},
    [55] = {SpawnPixelCoords(5216, 448), 14},
    [56] = {SpawnPixelCoords(5248, 448), 15},
    [57] = {SpawnPixelCoords(5312, 448), 16},
    [58] = {SpawnPixelCoords(5408, 448), 14},
    [59] = {SpawnPixelCoords(5504, 448), 5},
    [60] = {SpawnPixelCoords(5744, 448), 5},
    [61] = {SpawnPixelCoords(6704, 448), 5},
    [62] = {SpawnPixelCoords(6944, 448), 5},
    [63] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Naold1_Preloads[6] = {
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00000001),
        512,
        4,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_BOX,
        B8(00000001),
        832,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRAB,
        B8(00000001),
        960,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_EYE,
        B8(00000001),
        666,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FALLEN,
        B8(00000001),
        714,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
