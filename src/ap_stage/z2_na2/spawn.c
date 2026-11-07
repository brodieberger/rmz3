// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Na2_Templates[32] = {
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
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_GATE, 0, 0),
        },
    [7] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FLOE, 1, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FLOE, 0, 1),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 0, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAB, 1, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH, 0, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH, 0, 1),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH, 1, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH, 1, 1),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH_SPAWNER, 0, 0),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FISH_SPAWNER, 0, 0),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_WOLF, 1, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_WOLF, 0, 0),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
            .attr = 0x01,
        },
    [27] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
            .attr = 0x01,
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 210, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 211, 0),
        },
    [30] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 212, 0),
        },
    [31] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0),
        },
};

const struct SpawnPoint gApZ2Na2_Points[45] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(704, 1200), 6},
    [2] = {SpawnPixelCoords(864, 1360), 12},
    [3] = {SpawnPixelCoords(1040, 1248), 8},
    [4] = {SpawnPixelCoords(1072, 1376), 9},
    [5] = {SpawnPixelCoords(1168, 1056), 1},
    [6] = {SpawnPixelCoords(1280, 1328), 12},
    [7] = {SpawnPixelCoords(1488, 1248), 8},
    [8] = {SpawnPixelCoords(1520, 1360), 11},
    [9] = {SpawnPixelCoords(1616, 1056), 28},
    [10] = {SpawnPixelCoords(1616, 1264), 9},
    [11] = {SpawnPixelCoords(1792, 1344), 11},
    [12] = {SpawnPixelCoords(1904, 1200), 6},
    [13] = {SpawnPixelCoords(2288, 1248), 1},
    [14] = {SpawnPixelCoords(2384, 1216), 6},
    [15] = {SpawnPixelCoords(2464, 1104), 18},
    [16] = {SpawnPixelCoords(2480, 992), 18},
    [17] = {SpawnPixelCoords(2512, 1216), 18},
    [18] = {SpawnPixelCoords(2640, 1056), 17},
    [19] = {SpawnPixelCoords(2656, 960), 29},
    [20] = {SpawnPixelCoords(2720, 1136), 17},
    [21] = {SpawnPixelCoords(2832, 896), 4},
    [22] = {SpawnPixelCoords(2864, 1216), 5},
    [23] = {SpawnPixelCoords(3344, 1216), 5},
    [24] = {SpawnPixelCoords(3376, 352), 9},
    [25] = {SpawnPixelCoords(3376, 528), 30},
    [26] = {SpawnPixelCoords(3392, 528), 9},
    [27] = {SpawnPixelCoords(3472, 1232), 7},
    [28] = {SpawnPixelCoords(3472, 1312), 15},
    [29] = {SpawnPixelCoords(3568, 528), 9},
    [30] = {SpawnPixelCoords(3568, 960), 9},
    [31] = {SpawnPixelCoords(3584, 256), 5},
    [32] = {SpawnPixelCoords(3888, 256), 1},
    [33] = {SpawnPixelCoords(3888, 288), 8},
    [34] = {SpawnPixelCoords(3920, 208), 10},
    [35] = {SpawnPixelCoords(4256, 352), 11},
    [36] = {SpawnPixelCoords(4496, 368), 11},
    [37] = {SpawnPixelCoords(4688, 416), 11},
    [38] = {SpawnPixelCoords(4752, 352), 4},
    [39] = {SpawnPixelCoords(4912, 288), 10},
    [40] = {SpawnPixelCoords(5072, 320), 11},
    [41] = {SpawnPixelCoords(5136, 448), 9},
    [42] = {SpawnPixelCoords(5264, 560), 5},
    [43] = {SpawnPixelCoords(5504, 560), 31},
    [44] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Na2_Preloads[8] = {
    {
        AP_SHEET_Z2_FLOE,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRAB,
        B8(00000001),
        640,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FISH,
        B8(00000001),
        704,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GATE,
        B8(00000011),
        928,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000010),
        512,
        4,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_WOLF,
        B8(00000010),
        632,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00000010),
        816,
        6,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
