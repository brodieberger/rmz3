// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Train_Templates[15] = {
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
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_GANTRY, 0, 0),
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 2, 0),
            .attr = 0x01,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 3, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 4, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 5, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 0, 1),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 1, 1),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 34, 0),
        },
    [14] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 35, 0),
        },
};

const struct SpawnPoint gApZ2Train_Points[58] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(992, 400), 13},
    [2] = {SpawnPixelCoords(1600, 224), 7},
    [3] = {SpawnPixelCoords(1840, 320), 5},
    [4] = {SpawnPixelCoords(2016, 432), 9},
    [5] = {SpawnPixelCoords(2048, 304), 6},
    [6] = {SpawnPixelCoords(2080, 304), 6},
    [7] = {SpawnPixelCoords(2112, 304), 6},
    [8] = {SpawnPixelCoords(2112, 432), 6},
    [9] = {SpawnPixelCoords(2144, 304), 6},
    [10] = {SpawnPixelCoords(2224, 432), 6},
    [11] = {SpawnPixelCoords(2464, 320), 5},
    [12] = {SpawnPixelCoords(2672, 304), 9},
    [13] = {SpawnPixelCoords(2848, 240), 7},
    [14] = {SpawnPixelCoords(2944, 304), 6},
    [15] = {SpawnPixelCoords(2976, 304), 6},
    [16] = {SpawnPixelCoords(3088, 320), 5},
    [17] = {SpawnPixelCoords(3152, 256), 8},
    [18] = {SpawnPixelCoords(3312, 432), 9},
    [19] = {SpawnPixelCoords(3424, 432), 9},
    [20] = {SpawnPixelCoords(3504, 256), 7},
    [21] = {SpawnPixelCoords(3600, 432), 1},
    [22] = {SpawnPixelCoords(3712, 320), 5},
    [23] = {SpawnPixelCoords(3824, 304), 9},
    [24] = {SpawnPixelCoords(4016, 256), 7},
    [25] = {SpawnPixelCoords(4336, 320), 5},
    [26] = {SpawnPixelCoords(4496, 432), 9},
    [27] = {SpawnPixelCoords(4592, 304), 6},
    [28] = {SpawnPixelCoords(4592, 432), 9},
    [29] = {SpawnPixelCoords(4624, 304), 6},
    [30] = {SpawnPixelCoords(4624, 432), 3},
    [31] = {SpawnPixelCoords(4656, 304), 6},
    [32] = {SpawnPixelCoords(4704, 432), 9},
    [33] = {SpawnPixelCoords(5216, 320), 5},
    [34] = {SpawnPixelCoords(5504, 256), 8},
    [35] = {SpawnPixelCoords(5712, 400), 1},
    [36] = {SpawnPixelCoords(5952, 320), 5},
    [37] = {SpawnPixelCoords(6032, 224), 7},
    [38] = {SpawnPixelCoords(6128, 304), 11},
    [39] = {SpawnPixelCoords(6528, 336), 12},
    [40] = {SpawnPixelCoords(6688, 432), 11},
    [41] = {SpawnPixelCoords(6736, 304), 6},
    [42] = {SpawnPixelCoords(6816, 304), 6},
    [43] = {SpawnPixelCoords(6864, 336), 12},
    [44] = {SpawnPixelCoords(6896, 304), 6},
    [45] = {SpawnPixelCoords(6976, 304), 6},
    [46] = {SpawnPixelCoords(7264, 224), 7},
    [47] = {SpawnPixelCoords(7456, 304), 9},
    [48] = {SpawnPixelCoords(8464, 304), 6},
    [49] = {SpawnPixelCoords(8528, 304), 6},
    [50] = {SpawnPixelCoords(8624, 304), 9},
    [51] = {SpawnPixelCoords(8720, 432), 14},
    [52] = {SpawnPixelCoords(8848, 224), 8},
    [53] = {SpawnPixelCoords(8960, 432), 9},
    [54] = {SpawnPixelCoords(9184, 432), 9},
    [55] = {SpawnPixelCoords(9296, 432), 1},
    [56] = {SpawnPixelCoords(9328, 304), 9},
    [57] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Train_Preloads[7] = {
    {
        AP_SHEET_Z2_GANTRY,
        B8(00000011),
        786,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CARRYARM,
        B8(00000011),
        666,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GANTRY_SIDE,
        B8(00000011),
        380,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00000011),
        512,
        7,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_CRAB,
        B8(00000001),
        922,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRATE,
        B8(00000010),
        922,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
