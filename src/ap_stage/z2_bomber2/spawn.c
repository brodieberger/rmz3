// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApImp0_Templates[91] = {
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
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 1, 0),
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 2, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 2, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 3, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HIVE, 0, 0),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HIVE, 1, 0),
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HOPPER, 1, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 0),
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 0, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 1, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 2, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 1, 0),
        },
    [27] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 3, 0),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 2, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 0, 0),
        },
    [30] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 0),
            .attr = 0x02,
        },
    [31] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 1),
            .attr = 0x02,
        },
    [32] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 2),
            .attr = 0x02,
        },
    [33] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 3),
            .attr = 0x02,
        },
    [34] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 4),
            .attr = 0x02,
        },
    [35] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 5),
            .attr = 0x02,
        },
    [36] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 6),
            .attr = 0x02,
        },
    [37] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 7),
            .attr = 0x02,
        },
    [38] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 8),
            .attr = 0x02,
        },
    [39] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SOLDIER, 0, 9),
            .attr = 0x02,
        },
    [40] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [41] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [42] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [43] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [44] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [45] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [46] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [47] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [48] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [49] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 0, 0),
        },
    [50] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 1, 0),
        },
    [51] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 2, 0),
        },
    [52] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 3, 0),
        },
    [53] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 4, 0),
        },
    [54] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 5, 0),
        },
    [55] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 6, 0),
        },
    [56] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 0, 0),
        },
    [57] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 1, 0),
        },
    [58] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 2, 0),
        },
    [59] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 3, 0),
        },
    [60] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 4, 0),
        },
    [61] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [62] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [63] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [64] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [65] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 0),
        },
    [66] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 1, 0),
        },
    [67] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 2, 0),
        },
    [68] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [69] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 0, 0),
            .attr = 0x01,
        },
    [70] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 1, 0),
            .attr = 0x01,
        },
    [71] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 2, 0),
            .attr = 0x01,
        },
    [72] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 0, 0),
            .attr = 0x01,
        },
    [73] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 1, 0),
            .attr = 0x01,
        },
    [74] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 2, 0),
            .attr = 0x01,
        },
    [75] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 9, 0, 0),
            .attr = 0x01,
        },
    [76] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 9, 1, 0),
            .attr = 0x01,
        },
    [77] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HOPPER, 1, 0),
            .attr = 0x01,
        },
    [78] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 16, 1, 0),
            .attr = 0x01,
        },
    [79] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 16, 1, 1),
            .attr = 0x01,
        },
    [80] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 31, 1, 0),
            .attr = 0x01,
        },
    [81] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 0),
        },
    [82] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 7, 0),
        },
    [83] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 4, 0),
        },
    [84] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 7, 0),
        },
    [85] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 5, 0),
        },
    [86] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 6, 0),
        },
    [87] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 1),
        },
    [88] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(6, 30, 0, 0),
        },
    [89] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(6, 30, 1, 0),
        },
    [90] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_H, 0, 0),
        },
};

const struct SpawnPoint gApImp0_Points[89] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(720, 1680), 1},
    [2] = {SpawnPixelCoords(800, 576), 8},
    [3] = {SpawnPixelCoords(864, 1328), 10},
    [4] = {SpawnPixelCoords(928, 512), 8},
    [5] = {SpawnPixelCoords(944, 2176), 7},
    [6] = {SpawnPixelCoords(1040, 2512), 21},
    [7] = {SpawnPixelCoords(1072, 496), 8},
    [8] = {SpawnPixelCoords(1168, 2512), 21},
    [9] = {SpawnPixelCoords(1184, 2176), 7},
    [10] = {SpawnPixelCoords(1248, 496), 9},
    [11] = {SpawnPixelCoords(1280, 2176), 3},
    [12] = {SpawnPixelCoords(1296, 1344), 3},
    [13] = {SpawnPixelCoords(1312, 2176), 3},
    [14] = {SpawnPixelCoords(1312, 2416), 20},
    [15] = {SpawnPixelCoords(1344, 2176), 3},
    [16] = {SpawnPixelCoords(1376, 2176), 29},
    [17] = {SpawnPixelCoords(1776, 704), 18},
    [18] = {SpawnPixelCoords(1808, 592), 9},
    [19] = {SpawnPixelCoords(1808, 2464), 21},
    [20] = {SpawnPixelCoords(1840, 672), 18},
    [21] = {SpawnPixelCoords(1936, 608), 18},
    [22] = {SpawnPixelCoords(1952, 720), 3},
    [23] = {SpawnPixelCoords(2160, 528), 18},
    [24] = {SpawnPixelCoords(2176, 1376), 3},
    [25] = {SpawnPixelCoords(2304, 752), 26},
    [26] = {SpawnPixelCoords(2304, 1360), 3},
    [27] = {SpawnPixelCoords(2336, 752), 4},
    [28] = {SpawnPixelCoords(2368, 1296), 19},
    [29] = {SpawnPixelCoords(2368, 2448), 21},
    [30] = {SpawnPixelCoords(2416, 1312), 3},
    [31] = {SpawnPixelCoords(2448, 1312), 18},
    [32] = {SpawnPixelCoords(2480, 496), 9},
    [33] = {SpawnPixelCoords(2592, 2432), 21},
    [34] = {SpawnPixelCoords(2752, 1376), 18},
    [35] = {SpawnPixelCoords(2848, 768), 18},
    [36] = {SpawnPixelCoords(2912, 1200), 28},
    [37] = {SpawnPixelCoords(2960, 608), 14},
    [38] = {SpawnPixelCoords(2976, 736), 18},
    [39] = {SpawnPixelCoords(3008, 224), 27},
    [40] = {SpawnPixelCoords(3056, 1072), 18},
    [41] = {SpawnPixelCoords(3376, 2128), 3},
    [42] = {SpawnPixelCoords(3392, 2128), 18},
    [43] = {SpawnPixelCoords(3472, 2320), 18},
    [44] = {SpawnPixelCoords(3696, 1760), 30},
    [45] = {SpawnPixelCoords(3728, 1536), 31},
    [46] = {SpawnPixelCoords(3744, 1424), 32},
    [47] = {SpawnPixelCoords(3776, 1312), 33},
    [48] = {SpawnPixelCoords(3776, 1536), 3},
    [49] = {SpawnPixelCoords(3792, 1424), 3},
    [50] = {SpawnPixelCoords(3808, 1200), 34},
    [51] = {SpawnPixelCoords(3856, 1200), 2},
    [52] = {SpawnPixelCoords(3952, 1008), 23},
    [53] = {SpawnPixelCoords(3968, 1392), 83},
    [54] = {SpawnPixelCoords(4000, 1392), 63},
    [55] = {SpawnPixelCoords(4016, 2016), 61},
    [56] = {SpawnPixelCoords(4064, 1392), 67},
    [57] = {SpawnPixelCoords(4064, 2016), 65},
    [58] = {SpawnPixelCoords(4176, 1552), 69},
    [59] = {SpawnPixelCoords(4240, 1840), 85},
    [60] = {SpawnPixelCoords(4304, 1072), 35},
    [61] = {SpawnPixelCoords(4304, 1392), 66},
    [62] = {SpawnPixelCoords(4304, 1552), 66},
    [63] = {SpawnPixelCoords(4512, 1328), 64},
    [64] = {SpawnPixelCoords(4592, 2048), 69},
    [65] = {SpawnPixelCoords(4784, 1040), 23},
    [66] = {SpawnPixelCoords(4864, 2272), 86},
    [67] = {SpawnPixelCoords(4880, 1056), 36},
    [68] = {SpawnPixelCoords(5024, 1040), 23},
    [69] = {SpawnPixelCoords(5024, 1968), 69},
    [70] = {SpawnPixelCoords(5248, 1472), 69},
    [71] = {SpawnPixelCoords(5280, 1040), 37},
    [72] = {SpawnPixelCoords(5312, 1568), 61},
    [73] = {SpawnPixelCoords(5456, 1568), 63},
    [74] = {SpawnPixelCoords(5504, 1040), 38},
    [75] = {SpawnPixelCoords(5584, 1568), 63},
    [76] = {SpawnPixelCoords(5712, 992), 39},
    [77] = {SpawnPixelCoords(5744, 2352), 66},
    [78] = {SpawnPixelCoords(5792, 1200), 63},
    [79] = {SpawnPixelCoords(5792, 2224), 90},
    [80] = {SpawnPixelCoords(5808, 1200), 63},
    [81] = {SpawnPixelCoords(5808, 2128), 61},
    [82] = {SpawnPixelCoords(5952, 1936), 84},
    [83] = {SpawnPixelCoords(5984, 2352), 66},
    [84] = {SpawnPixelCoords(6320, 960), 9},
    [85] = {SpawnPixelCoords(6544, 992), 8},
    [86] = {SpawnPixelCoords(6960, 1552), 3},
    [87] = {SpawnPixelCoords(6976, 1552), 3},
    [88] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApImp0_Preloads[13] = {
    {
        SM021_TOP_GABYOALL,
        B8(00000111),
        834,
        9,
        1,
        1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000111),
        512,
        4,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_CARRYARM,
        B8(00001001),
        901,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HIVE,
        B8(00000110),
        632,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HOTTALOOK,
        B8(00000110),
        696,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HOPPER,
        B8(00000100),
        752,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SOLDIER,
        B8(00001000),
        834,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SIGNALOID,
        B8(00101000),
        552,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GOLEM,
        B8(00010000),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GOLEM_ARM,
        B8(00010000),
        692,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GOLEM_LASER,
        B8(00010000),
        916,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GOLEM_FOOT,
        B8(00010000),
        976,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
