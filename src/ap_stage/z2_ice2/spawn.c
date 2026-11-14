// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Ice2_Templates[20] = {
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 2, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 3, 0),
            .attr = 0x01,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 4, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CARRYARM, 5, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_WOLF, 1, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_WOLF, 0, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SNOWBALLER, 0, 0),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SNOWBALLER, 0, 1),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_FLOOR_MINE, 0, 0),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_CRAWLER, 0, 0),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 0, 0),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 1, 0),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 130, 0),
        },
    [19] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 131, 0),
        },
};

const struct SpawnPoint gApZ2Ice2_Points[101] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(336, 1296), 18},
    [2] = {SpawnPixelCoords(880, 1040), 6},
    [3] = {SpawnPixelCoords(960, 1088), 14},
    [4] = {SpawnPixelCoords(1024, 1088), 14},
    [5] = {SpawnPixelCoords(1248, 960), 6},
    [6] = {SpawnPixelCoords(1280, 1008), 14},
    [7] = {SpawnPixelCoords(1328, 1008), 14},
    [8] = {SpawnPixelCoords(1376, 1008), 14},
    [9] = {SpawnPixelCoords(1488, 1024), 14},
    [10] = {SpawnPixelCoords(1536, 1040), 14},
    [11] = {SpawnPixelCoords(1792, 976), 6},
    [12] = {SpawnPixelCoords(1840, 1008), 14},
    [13] = {SpawnPixelCoords(1904, 1008), 14},
    [14] = {SpawnPixelCoords(1968, 1008), 14},
    [15] = {SpawnPixelCoords(2032, 1008), 14},
    [16] = {SpawnPixelCoords(2144, 1008), 10},
    [17] = {SpawnPixelCoords(2400, 976), 10},
    [18] = {SpawnPixelCoords(2608, 944), 8},
    [19] = {SpawnPixelCoords(2752, 944), 8},
    [20] = {SpawnPixelCoords(2944, 1040), 14},
    [21] = {SpawnPixelCoords(2960, 1056), 14},
    [22] = {SpawnPixelCoords(2976, 912), 6},
    [23] = {SpawnPixelCoords(2976, 1056), 14},
    [24] = {SpawnPixelCoords(2992, 1056), 14},
    [25] = {SpawnPixelCoords(3008, 1056), 14},
    [26] = {SpawnPixelCoords(3136, 1008), 10},
    [27] = {SpawnPixelCoords(3360, 1024), 10},
    [28] = {SpawnPixelCoords(3520, 1280), 15},
    [29] = {SpawnPixelCoords(3744, 1264), 10},
    [30] = {SpawnPixelCoords(3776, 1280), 15},
    [31] = {SpawnPixelCoords(4112, 1280), 15},
    [32] = {SpawnPixelCoords(4192, 1280), 10},
    [33] = {SpawnPixelCoords(4288, 1264), 2},
    [34] = {SpawnPixelCoords(4448, 1056), 12},
    [35] = {SpawnPixelCoords(4496, 1056), 14},
    [36] = {SpawnPixelCoords(4544, 1056), 14},
    [37] = {SpawnPixelCoords(4624, 992), 12},
    [38] = {SpawnPixelCoords(4832, 896), 12},
    [39] = {SpawnPixelCoords(5024, 864), 12},
    [40] = {SpawnPixelCoords(5104, 864), 17},
    [41] = {SpawnPixelCoords(5120, 912), 1},
    [42] = {SpawnPixelCoords(5392, 752), 12},
    [43] = {SpawnPixelCoords(5536, 720), 12},
    [44] = {SpawnPixelCoords(5760, 576), 12},
    [45] = {SpawnPixelCoords(5792, 400), 17},
    [46] = {SpawnPixelCoords(5792, 480), 17},
    [47] = {SpawnPixelCoords(6064, 336), 12},
    [48] = {SpawnPixelCoords(6304, 336), 12},
    [49] = {SpawnPixelCoords(6768, 400), 13},
    [50] = {SpawnPixelCoords(6992, 496), 14},
    [51] = {SpawnPixelCoords(7056, 496), 14},
    [52] = {SpawnPixelCoords(7120, 496), 14},
    [53] = {SpawnPixelCoords(7184, 1792), 3},
    [54] = {SpawnPixelCoords(7200, 768), 14},
    [55] = {SpawnPixelCoords(7200, 1056), 14},
    [56] = {SpawnPixelCoords(7200, 1344), 14},
    [57] = {SpawnPixelCoords(7200, 1632), 14},
    [58] = {SpawnPixelCoords(7200, 1792), 3},
    [59] = {SpawnPixelCoords(7216, 512), 14},
    [60] = {SpawnPixelCoords(7232, 768), 14},
    [61] = {SpawnPixelCoords(7232, 1056), 14},
    [62] = {SpawnPixelCoords(7232, 1344), 14},
    [63] = {SpawnPixelCoords(7232, 1632), 14},
    [64] = {SpawnPixelCoords(7264, 784), 14},
    [65] = {SpawnPixelCoords(7264, 1072), 14},
    [66] = {SpawnPixelCoords(7264, 1360), 14},
    [67] = {SpawnPixelCoords(7264, 1648), 14},
    [68] = {SpawnPixelCoords(7264, 1760), 16},
    [69] = {SpawnPixelCoords(7296, 640), 14},
    [70] = {SpawnPixelCoords(7296, 784), 14},
    [71] = {SpawnPixelCoords(7296, 928), 14},
    [72] = {SpawnPixelCoords(7296, 1072), 14},
    [73] = {SpawnPixelCoords(7296, 1216), 14},
    [74] = {SpawnPixelCoords(7296, 1360), 14},
    [75] = {SpawnPixelCoords(7296, 1504), 14},
    [76] = {SpawnPixelCoords(7296, 1648), 14},
    [77] = {SpawnPixelCoords(7328, 640), 14},
    [78] = {SpawnPixelCoords(7328, 928), 14},
    [79] = {SpawnPixelCoords(7328, 1216), 14},
    [80] = {SpawnPixelCoords(7328, 1504), 14},
    [81] = {SpawnPixelCoords(7360, 624), 14},
    [82] = {SpawnPixelCoords(7360, 912), 14},
    [83] = {SpawnPixelCoords(7360, 1200), 14},
    [84] = {SpawnPixelCoords(7360, 1488), 14},
    [85] = {SpawnPixelCoords(7392, 624), 14},
    [86] = {SpawnPixelCoords(7392, 912), 14},
    [87] = {SpawnPixelCoords(7392, 1200), 14},
    [88] = {SpawnPixelCoords(7392, 1488), 14},
    [89] = {SpawnPixelCoords(7408, 416), 19},
    [90] = {SpawnPixelCoords(7424, 1824), 5},
    [91] = {SpawnPixelCoords(7680, 1792), 16},
    [92] = {SpawnPixelCoords(7744, 1808), 16},
    [93] = {SpawnPixelCoords(7808, 1824), 16},
    [94] = {SpawnPixelCoords(7872, 1840), 16},
    [95] = {SpawnPixelCoords(7936, 1856), 16},
    [96] = {SpawnPixelCoords(8000, 1872), 16},
    [97] = {SpawnPixelCoords(8112, 1824), 4},
    [98] = {SpawnPixelCoords(8144, 1984), 5},
    [99] = {SpawnPixelCoords(8384, 1984), 5},
    [100] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Ice2_Preloads[7] = {
    {
        AP_SHEET_Z2_CARRYARM,
        B8(00000001),
        798,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SNOWBALLER,
        B8(00000001),
        662,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_WOLF,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FLOOR_MINE,
        B8(00000001),
        991,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRAWLER,
        B8(00000001),
        918,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM022_FLOPPER,
        B8(00000001),
        975,
        8,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
