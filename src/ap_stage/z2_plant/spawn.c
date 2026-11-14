// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Plant_Templates[31] = {
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
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SLAB, 0, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 64, 0, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 0, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 1, 0),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 2, 0),
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 0, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 1, 0),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 2, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HOPPER, 1, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 0, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 1, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 2, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 2, 0),
        },
    [27] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 51, 0),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 52, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 50, 0),
        },
    [30] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR_3D, 1, 0),
        },
};

const struct SpawnPoint gApZ2Plant_Points[150] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(768, 1040), 21},
    [2] = {SpawnPixelCoords(1024, 1040), 21},
    [3] = {SpawnPixelCoords(1120, 1040), 21},
    [4] = {SpawnPixelCoords(1168, 1040), 21},
    [5] = {SpawnPixelCoords(1376, 992), 21},
    [6] = {SpawnPixelCoords(1488, 1072), 29},
    [7] = {SpawnPixelCoords(1600, 976), 8},
    [8] = {SpawnPixelCoords(1712, 1056), 21},
    [9] = {SpawnPixelCoords(1808, 976), 8},
    [10] = {SpawnPixelCoords(1920, 1040), 21},
    [11] = {SpawnPixelCoords(2016, 1152), 8},
    [12] = {SpawnPixelCoords(2112, 1376), 22},
    [13] = {SpawnPixelCoords(2176, 1328), 8},
    [14] = {SpawnPixelCoords(2384, 1376), 22},
    [15] = {SpawnPixelCoords(2416, 1312), 8},
    [16] = {SpawnPixelCoords(2528, 1312), 8},
    [17] = {SpawnPixelCoords(2544, 1376), 22},
    [18] = {SpawnPixelCoords(2720, 1360), 8},
    [19] = {SpawnPixelCoords(2816, 1296), 8},
    [20] = {SpawnPixelCoords(2880, 1376), 22},
    [21] = {SpawnPixelCoords(2960, 1360), 8},
    [22] = {SpawnPixelCoords(3040, 1008), 27},
    [23] = {SpawnPixelCoords(3040, 1072), 3},
    [24] = {SpawnPixelCoords(3184, 1296), 8},
    [25] = {SpawnPixelCoords(3216, 896), 5},
    [26] = {SpawnPixelCoords(3248, 896), 5},
    [27] = {SpawnPixelCoords(3264, 816), 23},
    [28] = {SpawnPixelCoords(3264, 1408), 20},
    [29] = {SpawnPixelCoords(3280, 896), 5},
    [30] = {SpawnPixelCoords(3344, 1296), 8},
    [31] = {SpawnPixelCoords(3376, 896), 5},
    [32] = {SpawnPixelCoords(3408, 896), 5},
    [33] = {SpawnPixelCoords(3424, 1408), 20},
    [34] = {SpawnPixelCoords(3440, 896), 5},
    [35] = {SpawnPixelCoords(3472, 896), 5},
    [36] = {SpawnPixelCoords(3488, 1296), 8},
    [37] = {SpawnPixelCoords(3520, 1408), 1},
    [38] = {SpawnPixelCoords(3568, 896), 5},
    [39] = {SpawnPixelCoords(3584, 1344), 26},
    [40] = {SpawnPixelCoords(3600, 896), 5},
    [41] = {SpawnPixelCoords(3648, 816), 23},
    [42] = {SpawnPixelCoords(3696, 912), 5},
    [43] = {SpawnPixelCoords(3728, 912), 5},
    [44] = {SpawnPixelCoords(3760, 864), 5},
    [45] = {SpawnPixelCoords(3792, 864), 5},
    [46] = {SpawnPixelCoords(3888, 432), 3},
    [47] = {SpawnPixelCoords(3920, 880), 5},
    [48] = {SpawnPixelCoords(3952, 880), 5},
    [49] = {SpawnPixelCoords(3968, 400), 10},
    [50] = {SpawnPixelCoords(4016, 176), 23},
    [51] = {SpawnPixelCoords(4064, 1344), 26},
    [52] = {SpawnPixelCoords(4128, 176), 23},
    [53] = {SpawnPixelCoords(4128, 1184), 4},
    [54] = {SpawnPixelCoords(4144, 1184), 2},
    [55] = {SpawnPixelCoords(4160, 592), 30},
    [56] = {SpawnPixelCoords(4192, 1280), 8},
    [57] = {SpawnPixelCoords(4224, 1200), 8},
    [58] = {SpawnPixelCoords(4336, 1312), 8},
    [59] = {SpawnPixelCoords(4464, 1280), 20},
    [60] = {SpawnPixelCoords(4544, 544), 26},
    [61] = {SpawnPixelCoords(4544, 1200), 8},
    [62] = {SpawnPixelCoords(4688, 1152), 8},
    [63] = {SpawnPixelCoords(4848, 1264), 20},
    [64] = {SpawnPixelCoords(4944, 1296), 8},
    [65] = {SpawnPixelCoords(5024, 544), 26},
    [66] = {SpawnPixelCoords(5072, 1152), 8},
    [67] = {SpawnPixelCoords(5152, 608), 10},
    [68] = {SpawnPixelCoords(5200, 1152), 8},
    [69] = {SpawnPixelCoords(5264, 592), 2},
    [70] = {SpawnPixelCoords(5280, 528), 22},
    [71] = {SpawnPixelCoords(5344, 528), 22},
    [72] = {SpawnPixelCoords(5360, 592), 3},
    [73] = {SpawnPixelCoords(5360, 1632), 9},
    [74] = {SpawnPixelCoords(5376, 1264), 21},
    [75] = {SpawnPixelCoords(5456, 1552), 3},
    [76] = {SpawnPixelCoords(5472, 608), 10},
    [77] = {SpawnPixelCoords(5472, 1552), 3},
    [78] = {SpawnPixelCoords(5472, 1616), 9},
    [79] = {SpawnPixelCoords(5472, 1680), 10},
    [80] = {SpawnPixelCoords(5488, 1552), 3},
    [81] = {SpawnPixelCoords(5504, 1184), 26},
    [82] = {SpawnPixelCoords(5504, 1552), 3},
    [83] = {SpawnPixelCoords(5584, 1552), 10},
    [84] = {SpawnPixelCoords(5584, 1600), 9},
    [85] = {SpawnPixelCoords(5600, 592), 3},
    [86] = {SpawnPixelCoords(5616, 528), 22},
    [87] = {SpawnPixelCoords(5680, 528), 22},
    [88] = {SpawnPixelCoords(5696, 592), 3},
    [89] = {SpawnPixelCoords(5696, 1472), 8},
    [90] = {SpawnPixelCoords(5696, 1552), 3},
    [91] = {SpawnPixelCoords(5696, 1600), 8},
    [92] = {SpawnPixelCoords(5712, 1552), 3},
    [93] = {SpawnPixelCoords(5712, 1680), 10},
    [94] = {SpawnPixelCoords(5808, 1520), 8},
    [95] = {SpawnPixelCoords(5824, 608), 10},
    [96] = {SpawnPixelCoords(5888, 1680), 28},
    [97] = {SpawnPixelCoords(5936, 592), 3},
    [98] = {SpawnPixelCoords(5952, 528), 22},
    [99] = {SpawnPixelCoords(5984, 1184), 26},
    [100] = {SpawnPixelCoords(6160, 1712), 1},
    [101] = {SpawnPixelCoords(6208, 496), 8},
    [102] = {SpawnPixelCoords(6224, 1712), 26},
    [103] = {SpawnPixelCoords(6272, 512), 8},
    [104] = {SpawnPixelCoords(6352, 1472), 9},
    [105] = {SpawnPixelCoords(6352, 1520), 9},
    [106] = {SpawnPixelCoords(6464, 544), 26},
    [107] = {SpawnPixelCoords(6464, 1472), 9},
    [108] = {SpawnPixelCoords(6464, 1520), 9},
    [109] = {SpawnPixelCoords(6464, 1712), 26},
    [110] = {SpawnPixelCoords(6528, 1376), 1},
    [111] = {SpawnPixelCoords(6544, 1712), 3},
    [112] = {SpawnPixelCoords(6560, 1712), 3},
    [113] = {SpawnPixelCoords(6576, 1472), 9},
    [114] = {SpawnPixelCoords(6576, 1520), 9},
    [115] = {SpawnPixelCoords(6592, 1712), 4},
    [116] = {SpawnPixelCoords(6624, 1712), 3},
    [117] = {SpawnPixelCoords(6640, 1712), 3},
    [118] = {SpawnPixelCoords(6672, 1136), 23},
    [119] = {SpawnPixelCoords(6672, 1328), 3},
    [120] = {SpawnPixelCoords(6784, 1216), 5},
    [121] = {SpawnPixelCoords(6816, 1216), 5},
    [122] = {SpawnPixelCoords(6848, 1216), 5},
    [123] = {SpawnPixelCoords(6880, 1216), 5},
    [124] = {SpawnPixelCoords(6912, 1216), 5},
    [125] = {SpawnPixelCoords(6944, 544), 26},
    [126] = {SpawnPixelCoords(6944, 1216), 5},
    [127] = {SpawnPixelCoords(6976, 1216), 5},
    [128] = {SpawnPixelCoords(7008, 1216), 5},
    [129] = {SpawnPixelCoords(7056, 1152), 23},
    [130] = {SpawnPixelCoords(7088, 1216), 5},
    [131] = {SpawnPixelCoords(7120, 1216), 5},
    [132] = {SpawnPixelCoords(7152, 1216), 5},
    [133] = {SpawnPixelCoords(7184, 1216), 5},
    [134] = {SpawnPixelCoords(7216, 1216), 5},
    [135] = {SpawnPixelCoords(7248, 1216), 5},
    [136] = {SpawnPixelCoords(7264, 176), 23},
    [137] = {SpawnPixelCoords(7328, 592), 30},
    [138] = {SpawnPixelCoords(7328, 1216), 5},
    [139] = {SpawnPixelCoords(7360, 1216), 5},
    [140] = {SpawnPixelCoords(7440, 1216), 5},
    [141] = {SpawnPixelCoords(7456, 176), 23},
    [142] = {SpawnPixelCoords(7472, 1216), 5},
    [143] = {SpawnPixelCoords(7552, 400), 3},
    [144] = {SpawnPixelCoords(7552, 736), 10},
    [145] = {SpawnPixelCoords(7568, 1216), 5},
    [146] = {SpawnPixelCoords(7584, 336), 10},
    [147] = {SpawnPixelCoords(7600, 1216), 5},
    [148] = {SpawnPixelCoords(7632, 416), 1},
    [149] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Plant_Preloads[12] = {
    {
        AP_SHEET_Z2_SIGNALOID,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000001),
        904,
        6,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_HOPPER,
        B8(00000001),
        684,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00000101),
        766,
        8,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_MINE,
        B8(00000101),
        798,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRUMBLE,
        B8(00000100),
        944,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00000100),
        867,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FORTRESS,
        B8(00000100),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_MAGMA,
        B8(00001000),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_DRONE,
        B8(00001000),
        640,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GENERATOR,
        B8(00001000),
        704,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
