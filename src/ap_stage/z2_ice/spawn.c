// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Ice_Templates[29] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0),
        },
    [2] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_DOZER, 0, 0),
            .attr = 0x01,
        },
    [3] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAWLER, 0, 0),
            .attr = 0x01,
        },
    [4] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_COOLER, 0, 0),
            .attr = 0x02,
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_COOLER, 0, 1),
            .attr = 0x02,
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_COOLER, 0, 2),
            .attr = 0x02,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_COOLER, 0, 3),
            .attr = 0x02,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 0, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 1, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 2, 0),
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
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_FLOE, 0, 1),
        },
    [16] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [17] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [18] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [19] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_VENT, 0, 0),
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_VENT, 1, 0),
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_VENT, 2, 0),
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_VENT, 3, 0),
        },
    [25] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_DOZER, 1, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 19, 0),
        },
    [27] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 18, 0),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 20, 0),
        },
};

const struct SpawnPoint gApZ2Ice_Points[102] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(768, 1264), 14},
    [2] = {SpawnPixelCoords(832, 1248), 15},
    [3] = {SpawnPixelCoords(928, 1280), 14},
    [4] = {SpawnPixelCoords(992, 1248), 15},
    [5] = {SpawnPixelCoords(1040, 1360), 12},
    [6] = {SpawnPixelCoords(1136, 1264), 14},
    [7] = {SpawnPixelCoords(1200, 1216), 27},
    [8] = {SpawnPixelCoords(1200, 1248), 15},
    [9] = {SpawnPixelCoords(1232, 1328), 11},
    [10] = {SpawnPixelCoords(1264, 1280), 13},
    [11] = {SpawnPixelCoords(1488, 1136), 9},
    [12] = {SpawnPixelCoords(1536, 1136), 9},
    [13] = {SpawnPixelCoords(1648, 1280), 14},
    [14] = {SpawnPixelCoords(1712, 1248), 15},
    [15] = {SpawnPixelCoords(1712, 1328), 12},
    [16] = {SpawnPixelCoords(1776, 1264), 13},
    [17] = {SpawnPixelCoords(1840, 1264), 14},
    [18] = {SpawnPixelCoords(1904, 1248), 15},
    [19] = {SpawnPixelCoords(1984, 1280), 13},
    [20] = {SpawnPixelCoords(2016, 1360), 11},
    [21] = {SpawnPixelCoords(2048, 1280), 14},
    [22] = {SpawnPixelCoords(2112, 1136), 9},
    [23] = {SpawnPixelCoords(2112, 1248), 15},
    [24] = {SpawnPixelCoords(2160, 1328), 12},
    [25] = {SpawnPixelCoords(2176, 1264), 13},
    [26] = {SpawnPixelCoords(2272, 1360), 11},
    [27] = {SpawnPixelCoords(2304, 1264), 14},
    [28] = {SpawnPixelCoords(2352, 1216), 19},
    [29] = {SpawnPixelCoords(2352, 1248), 15},
    [30] = {SpawnPixelCoords(2432, 1280), 13},
    [31] = {SpawnPixelCoords(2704, 1152), 8},
    [32] = {SpawnPixelCoords(2784, 1136), 10},
    [33] = {SpawnPixelCoords(2960, 960), 8},
    [34] = {SpawnPixelCoords(3040, 1136), 9},
    [35] = {SpawnPixelCoords(3328, 1104), 18},
    [36] = {SpawnPixelCoords(3456, 1008), 22},
    [37] = {SpawnPixelCoords(3456, 1040), 22},
    [38] = {SpawnPixelCoords(3456, 1072), 22},
    [39] = {SpawnPixelCoords(3696, 1200), 23},
    [40] = {SpawnPixelCoords(3776, 1200), 23},
    [41] = {SpawnPixelCoords(3808, 1184), 25},
    [42] = {SpawnPixelCoords(3920, 1104), 21},
    [43] = {SpawnPixelCoords(4176, 1136), 25},
    [44] = {SpawnPixelCoords(4224, 1120), 21},
    [45] = {SpawnPixelCoords(4256, 1104), 23},
    [46] = {SpawnPixelCoords(4496, 1040), 2},
    [47] = {SpawnPixelCoords(4624, 1088), 22},
    [48] = {SpawnPixelCoords(4784, 1152), 23},
    [49] = {SpawnPixelCoords(4848, 1152), 3},
    [50] = {SpawnPixelCoords(4976, 1120), 23},
    [51] = {SpawnPixelCoords(5136, 1120), 3},
    [52] = {SpawnPixelCoords(5152, 1136), 22},
    [53] = {SpawnPixelCoords(5280, 1232), 25},
    [54] = {SpawnPixelCoords(5344, 1232), 4},
    [55] = {SpawnPixelCoords(5408, 1072), 2},
    [56] = {SpawnPixelCoords(5472, 1088), 23},
    [57] = {SpawnPixelCoords(5552, 1392), 5},
    [58] = {SpawnPixelCoords(5632, 1152), 3},
    [59] = {SpawnPixelCoords(5648, 1152), 23},
    [60] = {SpawnPixelCoords(5664, 1312), 11},
    [61] = {SpawnPixelCoords(5664, 1360), 12},
    [62] = {SpawnPixelCoords(5680, 1168), 22},
    [63] = {SpawnPixelCoords(5888, 1120), 23},
    [64] = {SpawnPixelCoords(5920, 1136), 22},
    [65] = {SpawnPixelCoords(6048, 1136), 25},
    [66] = {SpawnPixelCoords(6160, 1088), 21},
    [67] = {SpawnPixelCoords(6208, 1040), 17},
    [68] = {SpawnPixelCoords(6224, 1248), 1},
    [69] = {SpawnPixelCoords(7168, 1232), 26},
    [70] = {SpawnPixelCoords(7184, 1360), 1},
    [71] = {SpawnPixelCoords(7264, 992), 6},
    [72] = {SpawnPixelCoords(7296, 1232), 20},
    [73] = {SpawnPixelCoords(7312, 944), 8},
    [74] = {SpawnPixelCoords(7344, 1104), 20},
    [75] = {SpawnPixelCoords(7360, 944), 8},
    [76] = {SpawnPixelCoords(7456, 1072), 20},
    [77] = {SpawnPixelCoords(7616, 1168), 20},
    [78] = {SpawnPixelCoords(7664, 1040), 20},
    [79] = {SpawnPixelCoords(7712, 1312), 20},
    [80] = {SpawnPixelCoords(7760, 976), 10},
    [81] = {SpawnPixelCoords(7808, 1360), 18},
    [82] = {SpawnPixelCoords(7840, 1120), 20},
    [83] = {SpawnPixelCoords(7872, 960), 28},
    [84] = {SpawnPixelCoords(7952, 1296), 20},
    [85] = {SpawnPixelCoords(8000, 1120), 8},
    [86] = {SpawnPixelCoords(8080, 880), 7},
    [87] = {SpawnPixelCoords(8080, 1024), 9},
    [88] = {SpawnPixelCoords(8112, 880), 19},
    [89] = {SpawnPixelCoords(8224, 1024), 20},
    [90] = {SpawnPixelCoords(8384, 976), 20},
    [91] = {SpawnPixelCoords(8752, 944), 20},
    [92] = {SpawnPixelCoords(8800, 944), 20},
    [93] = {SpawnPixelCoords(8944, 512), 20},
    [94] = {SpawnPixelCoords(9008, 320), 20},
    [95] = {SpawnPixelCoords(9088, 320), 16},
    [96] = {SpawnPixelCoords(9104, 400), 1},
    [97] = {SpawnPixelCoords(9104, 736), 20},
    [98] = {SpawnPixelCoords(9168, 736), 20},
    [99] = {SpawnPixelCoords(9248, 848), 9},
    [100] = {SpawnPixelCoords(9344, 448), 1},
    [101] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Ice_Preloads[10] = {
    {
        AP_SHEET_Z2_FLOE,
        B8(00000001),
        544,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FISH,
        B8(00000011),
        659,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00001001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FROST,
        B8(00000010),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_DOZER,
        B8(00000010),
        770,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_ICE_BLOCK,
        B8(00000010),
        839,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRAWLER,
        B8(00000010),
        602,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COOLER,
        B8(00001010),
        903,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00001000),
        544,
        5,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
