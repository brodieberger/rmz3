// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Opening_Templates[16] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [2] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIKEBALL, 0, 0),
            .attr = 0x01,
        },
    [3] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_TOWER, 0, 0),
            .attr = 0x01,
        },
    [4] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIKEBALL, 1, 0),
            .attr = 0x01,
        },
    [5] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SAND_BLOCK, 0, 0),
        },
    [6] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SAND_BLOCK, 1, 0),
        },
    [7] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SAND_BLOCK, 2, 0),
        },
    [8] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_VULTURE, 0, 0),
        },
    [9] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_VULTURE, 0, 1),
        },
    [10] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_VULTURE, 1, 0),
        },
    [11] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [12] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [13] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [14] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [15] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 2, 0),
        },
};

const struct SpawnPoint gApZ2Opening_Points[50] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(1680, 400), 1},
    [2] = {SpawnPixelCoords(1792, 432), 1},
    [3] = {SpawnPixelCoords(2016, 384), 3},
    [4] = {SpawnPixelCoords(2208, 432), 3},
    [5] = {SpawnPixelCoords(2352, 400), 2},
    [6] = {SpawnPixelCoords(2560, 352), 4},
    [7] = {SpawnPixelCoords(2704, 368), 4},
    [8] = {SpawnPixelCoords(2896, 384), 4},
    [9] = {SpawnPixelCoords(3696, 432), 1},
    [10] = {SpawnPixelCoords(3904, 384), 1},
    [11] = {SpawnPixelCoords(4576, 400), 8},
    [12] = {SpawnPixelCoords(4880, 400), 9},
    [13] = {SpawnPixelCoords(5056, 384), 3},
    [14] = {SpawnPixelCoords(5216, 384), 5},
    [15] = {SpawnPixelCoords(5232, 368), 6},
    [16] = {SpawnPixelCoords(5280, 368), 7},
    [17] = {SpawnPixelCoords(5296, 384), 6},
    [18] = {SpawnPixelCoords(5376, 416), 7},
    [19] = {SpawnPixelCoords(5392, 384), 7},
    [20] = {SpawnPixelCoords(5472, 384), 6},
    [21] = {SpawnPixelCoords(5488, 416), 7},
    [22] = {SpawnPixelCoords(5504, 400), 11},
    [23] = {SpawnPixelCoords(5504, 416), 6},
    [24] = {SpawnPixelCoords(5568, 400), 6},
    [25] = {SpawnPixelCoords(5648, 400), 8},
    [26] = {SpawnPixelCoords(5744, 400), 7},
    [27] = {SpawnPixelCoords(5824, 432), 6},
    [28] = {SpawnPixelCoords(5840, 400), 6},
    [29] = {SpawnPixelCoords(5856, 384), 7},
    [30] = {SpawnPixelCoords(5904, 368), 2},
    [31] = {SpawnPixelCoords(5952, 384), 7},
    [32] = {SpawnPixelCoords(5968, 400), 5},
    [33] = {SpawnPixelCoords(5984, 432), 7},
    [34] = {SpawnPixelCoords(6128, 352), 8},
    [35] = {SpawnPixelCoords(6192, 352), 1},
    [36] = {SpawnPixelCoords(6208, 448), 14},
    [37] = {SpawnPixelCoords(6288, 432), 7},
    [38] = {SpawnPixelCoords(6304, 432), 6},
    [39] = {SpawnPixelCoords(6320, 384), 7},
    [40] = {SpawnPixelCoords(6400, 336), 10},
    [41] = {SpawnPixelCoords(6448, 352), 5},
    [42] = {SpawnPixelCoords(6512, 352), 7},
    [43] = {SpawnPixelCoords(6528, 352), 6},
    [44] = {SpawnPixelCoords(6592, 448), 15},
    [45] = {SpawnPixelCoords(6624, 336), 3},
    [46] = {SpawnPixelCoords(6720, 384), 7},
    [47] = {SpawnPixelCoords(6768, 384), 7},
    [48] = {SpawnPixelCoords(6816, 416), 7},
    [49] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Opening_Preloads[6] = {
    {
        AP_SHEET_Z2_SPIKEBALL,
        B8(11110101),
        674,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_TOWER,
        B8(11110101),
        746,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(11110101),
        904,
        9,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_SAND_BLOCK,
        B8(11110101),
        833,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_VULTURE,
        B8(11110101),
        512,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
