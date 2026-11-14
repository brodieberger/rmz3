// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Na3_Templates[42] = {
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
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_GATE, 1, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 0, 1),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 1, 1),
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 2, 1),
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 3, 1),
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 4, 1),
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 5, 1),
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 6, 1),
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 7, 1),
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 0, 0),
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 5, 0),
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 6, 0),
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 1, 0),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 2, 0),
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 3, 0),
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 4, 0),
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 0, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 1, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 2, 0),
            .attr = 0x01,
        },
    [27] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE, 0, 0),
            .attr = 0x01,
        },
    [28] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE_CARRIER, 0, 0),
            .attr = 0x01,
        },
    [29] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FLOWER, 0, 0),
            .attr = 0x01,
        },
    [30] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MOLE, 0, 0),
            .attr = 0x01,
        },
    [31] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
            .attr = 0x01,
        },
    [32] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
            .attr = 0x01,
        },
    [33] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
            .attr = 0x01,
        },
    [34] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
            .attr = 0x01,
        },
    [35] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
            .attr = 0x01,
        },
    [36] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
            .attr = 0x01,
        },
    [37] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
            .attr = 0x01,
        },
    [38] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
            .attr = 0x01,
        },
    [39] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BARRIER_SHIP, 0, 0),
            .attr = 0x01,
        },
    [40] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 227, 0),
        },
    [41] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 226, 0),
        },
};

const struct SpawnPoint gApZ2Na3_Points[109] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(656, 1840), 23},
    [2] = {SpawnPixelCoords(752, 1840), 23},
    [3] = {SpawnPixelCoords(1056, 1776), 27},
    [4] = {SpawnPixelCoords(1088, 1712), 27},
    [5] = {SpawnPixelCoords(1104, 1760), 27},
    [6] = {SpawnPixelCoords(1120, 1808), 27},
    [7] = {SpawnPixelCoords(1152, 1744), 27},
    [8] = {SpawnPixelCoords(1264, 736), 29},
    [9] = {SpawnPixelCoords(1312, 736), 4},
    [10] = {SpawnPixelCoords(1344, 1360), 3},
    [11] = {SpawnPixelCoords(1376, 1360), 3},
    [12] = {SpawnPixelCoords(1408, 1360), 3},
    [13] = {SpawnPixelCoords(1424, 1168), 7},
    [14] = {SpawnPixelCoords(1424, 1744), 27},
    [15] = {SpawnPixelCoords(1424, 1760), 27},
    [16] = {SpawnPixelCoords(1424, 1776), 27},
    [17] = {SpawnPixelCoords(1424, 1792), 27},
    [18] = {SpawnPixelCoords(1424, 1808), 27},
    [19] = {SpawnPixelCoords(1456, 928), 39},
    [20] = {SpawnPixelCoords(1456, 1360), 2},
    [21] = {SpawnPixelCoords(1472, 688), 39},
    [22] = {SpawnPixelCoords(1472, 1216), 23},
    [23] = {SpawnPixelCoords(1488, 1248), 21},
    [24] = {SpawnPixelCoords(1520, 480), 31},
    [25] = {SpawnPixelCoords(1536, 1136), 4},
    [26] = {SpawnPixelCoords(1536, 1248), 21},
    [27] = {SpawnPixelCoords(1552, 1376), 15},
    [28] = {SpawnPixelCoords(1552, 1872), 23},
    [29] = {SpawnPixelCoords(1584, 720), 29},
    [30] = {SpawnPixelCoords(1584, 880), 25},
    [31] = {SpawnPixelCoords(1584, 1248), 21},
    [32] = {SpawnPixelCoords(1600, 640), 39},
    [33] = {SpawnPixelCoords(1632, 1296), 23},
    [34] = {SpawnPixelCoords(1648, 816), 2},
    [35] = {SpawnPixelCoords(1648, 1296), 23},
    [36] = {SpawnPixelCoords(1664, 496), 39},
    [37] = {SpawnPixelCoords(1664, 1872), 6},
    [38] = {SpawnPixelCoords(1680, 368), 25},
    [39] = {SpawnPixelCoords(1680, 736), 29},
    [40] = {SpawnPixelCoords(1696, 1168), 14},
    [41] = {SpawnPixelCoords(1712, 640), 29},
    [42] = {SpawnPixelCoords(1712, 880), 39},
    [43] = {SpawnPixelCoords(1712, 1776), 4},
    [44] = {SpawnPixelCoords(1728, 1184), 21},
    [45] = {SpawnPixelCoords(1744, 1328), 41},
    [46] = {SpawnPixelCoords(1760, 1264), 20},
    [47] = {SpawnPixelCoords(1760, 1344), 22},
    [48] = {SpawnPixelCoords(1760, 1776), 9},
    [49] = {SpawnPixelCoords(1760, 1872), 8},
    [50] = {SpawnPixelCoords(1776, 1184), 20},
    [51] = {SpawnPixelCoords(1792, 1264), 22},
    [52] = {SpawnPixelCoords(1792, 1744), 17},
    [53] = {SpawnPixelCoords(1792, 1872), 17},
    [54] = {SpawnPixelCoords(1808, 480), 25},
    [55] = {SpawnPixelCoords(1808, 816), 29},
    [56] = {SpawnPixelCoords(1824, 416), 32},
    [57] = {SpawnPixelCoords(1824, 544), 35},
    [58] = {SpawnPixelCoords(1824, 608), 39},
    [59] = {SpawnPixelCoords(1824, 1344), 20},
    [60] = {SpawnPixelCoords(1824, 1744), 23},
    [61] = {SpawnPixelCoords(1840, 1152), 3},
    [62] = {SpawnPixelCoords(1840, 1792), 21},
    [63] = {SpawnPixelCoords(1856, 1152), 3},
    [64] = {SpawnPixelCoords(1856, 1328), 13},
    [65] = {SpawnPixelCoords(1872, 352), 39},
    [66] = {SpawnPixelCoords(1888, 880), 29},
    [67] = {SpawnPixelCoords(1920, 800), 39},
    [68] = {SpawnPixelCoords(1920, 1264), 22},
    [69] = {SpawnPixelCoords(1920, 1872), 17},
    [70] = {SpawnPixelCoords(1936, 1360), 12},
    [71] = {SpawnPixelCoords(1968, 432), 32},
    [72] = {SpawnPixelCoords(1968, 1776), 10},
    [73] = {SpawnPixelCoords(1984, 1264), 21},
    [74] = {SpawnPixelCoords(2000, 1888), 22},
    [75] = {SpawnPixelCoords(2016, 544), 25},
    [76] = {SpawnPixelCoords(2016, 1360), 23},
    [77] = {SpawnPixelCoords(2032, 960), 24},
    [78] = {SpawnPixelCoords(2064, 1248), 3},
    [79] = {SpawnPixelCoords(2064, 1648), 4},
    [80] = {SpawnPixelCoords(2064, 1888), 22},
    [81] = {SpawnPixelCoords(2080, 784), 25},
    [82] = {SpawnPixelCoords(2080, 1904), 3},
    [83] = {SpawnPixelCoords(2112, 960), 24},
    [84] = {SpawnPixelCoords(2128, 1888), 22},
    [85] = {SpawnPixelCoords(2144, 384), 5},
    [86] = {SpawnPixelCoords(2144, 1360), 7},
    [87] = {SpawnPixelCoords(2192, 1008), 3},
    [88] = {SpawnPixelCoords(2224, 1808), 21},
    [89] = {SpawnPixelCoords(2224, 1888), 22},
    [90] = {SpawnPixelCoords(2272, 1904), 3},
    [91] = {SpawnPixelCoords(2288, 1744), 23},
    [92] = {SpawnPixelCoords(2288, 1888), 21},
    [93] = {SpawnPixelCoords(2304, 1392), 23},
    [94] = {SpawnPixelCoords(2320, 1280), 28},
    [95] = {SpawnPixelCoords(2352, 1776), 11},
    [96] = {SpawnPixelCoords(2384, 384), 5},
    [97] = {SpawnPixelCoords(2384, 1872), 6},
    [98] = {SpawnPixelCoords(2432, 1376), 23},
    [99] = {SpawnPixelCoords(2640, 1360), 27},
    [100] = {SpawnPixelCoords(2688, 1824), 23},
    [101] = {SpawnPixelCoords(2816, 1776), 23},
    [102] = {SpawnPixelCoords(2928, 1440), 27},
    [103] = {SpawnPixelCoords(2928, 1680), 23},
    [104] = {SpawnPixelCoords(2960, 1600), 27},
    [105] = {SpawnPixelCoords(2992, 1872), 3},
    [106] = {SpawnPixelCoords(2992, 2032), 40},
    [107] = {SpawnPixelCoords(3008, 1872), 3},
    [108] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Na3_Preloads[12] = {
    {
        AP_SHEET_Z2_PYLON,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_LIFT,
        B8(00000001),
        704,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000001),
        768,
        6,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_BEE,
        B8(00000001),
        539,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BEE_CARRIER,
        B8(00000001),
        573,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GATE,
        B8(00000011),
        656,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00000010),
        720,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BARRIER_SHIP,
        B8(00000010),
        512,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_MOLE,
        B8(00000010),
        768,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FLOWER,
        B8(00000010),
        896,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00000010),
        960,
        8,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
