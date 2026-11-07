// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Jungle_Templates[30] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0),
        },
    [2] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0),
        },
    [3] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE, 0, 0),
            .attr = 0x01,
        },
    [4] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE_CARRIER, 0, 0),
            .attr = 0x01,
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 0, 0),
            .attr = 0x01,
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 1, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FLOWER, 0, 0),
            .attr = 0x01,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MOLE, 0, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [10] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [11] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [12] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_RESCUE, 5, 0),
            .attr = 0x02,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_RESCUE, 5, 1),
            .attr = 0x02,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_RESCUE, 5, 2),
            .attr = 0x02,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_RESCUE, 5, 3),
            .attr = 0x02,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_RESCUE, 5, 4),
            .attr = 0x02,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 5, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 2, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 1, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 3, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 0, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_PAD, 0, 0),
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 7, 2),
        },
    [27] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 66, 0),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 68, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 67, 0),
        },
};

const struct SpawnPoint gApZ2Jungle_Points[84] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(688, 912), 8},
    [2] = {SpawnPixelCoords(704, 832), 3},
    [3] = {SpawnPixelCoords(784, 832), 3},
    [4] = {SpawnPixelCoords(992, 768), 3},
    [5] = {SpawnPixelCoords(1024, 800), 3},
    [6] = {SpawnPixelCoords(1152, 912), 7},
    [7] = {SpawnPixelCoords(1200, 928), 8},
    [8] = {SpawnPixelCoords(1232, 704), 27},
    [9] = {SpawnPixelCoords(1312, 880), 7},
    [10] = {SpawnPixelCoords(1392, 720), 11},
    [11] = {SpawnPixelCoords(1472, 816), 3},
    [12] = {SpawnPixelCoords(1472, 928), 8},
    [13] = {SpawnPixelCoords(1504, 880), 3},
    [14] = {SpawnPixelCoords(1536, 816), 3},
    [15] = {SpawnPixelCoords(1584, 704), 11},
    [16] = {SpawnPixelCoords(1728, 896), 8},
    [17] = {SpawnPixelCoords(1808, 784), 3},
    [18] = {SpawnPixelCoords(1968, 720), 29},
    [19] = {SpawnPixelCoords(1968, 800), 4},
    [20] = {SpawnPixelCoords(2160, 784), 3},
    [21] = {SpawnPixelCoords(2288, 912), 11},
    [22] = {SpawnPixelCoords(2336, 912), 7},
    [23] = {SpawnPixelCoords(2352, 768), 3},
    [24] = {SpawnPixelCoords(2400, 768), 3},
    [25] = {SpawnPixelCoords(2448, 768), 3},
    [26] = {SpawnPixelCoords(2592, 688), 12},
    [27] = {SpawnPixelCoords(2592, 784), 4},
    [28] = {SpawnPixelCoords(2704, 880), 6},
    [29] = {SpawnPixelCoords(2880, 688), 11},
    [30] = {SpawnPixelCoords(2896, 816), 4},
    [31] = {SpawnPixelCoords(2912, 688), 11},
    [32] = {SpawnPixelCoords(2928, 912), 6},
    [33] = {SpawnPixelCoords(2944, 688), 11},
    [34] = {SpawnPixelCoords(3200, 704), 11},
    [35] = {SpawnPixelCoords(3280, 816), 25},
    [36] = {SpawnPixelCoords(3280, 928), 8},
    [37] = {SpawnPixelCoords(3520, 816), 25},
    [38] = {SpawnPixelCoords(3744, 816), 25},
    [39] = {SpawnPixelCoords(3744, 1392), 12},
    [40] = {SpawnPixelCoords(3744, 1520), 11},
    [41] = {SpawnPixelCoords(3776, 1520), 11},
    [42] = {SpawnPixelCoords(3904, 1504), 11},
    [43] = {SpawnPixelCoords(3936, 1504), 11},
    [44] = {SpawnPixelCoords(4048, 544), 9},
    [45] = {SpawnPixelCoords(4048, 656), 6},
    [46] = {SpawnPixelCoords(4048, 768), 11},
    [47] = {SpawnPixelCoords(4048, 880), 6},
    [48] = {SpawnPixelCoords(4080, 432), 6},
    [49] = {SpawnPixelCoords(4256, 1552), 11},
    [50] = {SpawnPixelCoords(4288, 448), 5},
    [51] = {SpawnPixelCoords(4288, 1552), 11},
    [52] = {SpawnPixelCoords(4480, 480), 5},
    [53] = {SpawnPixelCoords(4544, 432), 24},
    [54] = {SpawnPixelCoords(4544, 752), 2},
    [55] = {SpawnPixelCoords(4544, 912), 1},
    [56] = {SpawnPixelCoords(4784, 768), 21},
    [57] = {SpawnPixelCoords(4896, 496), 28},
    [58] = {SpawnPixelCoords(4928, 704), 6},
    [59] = {SpawnPixelCoords(4992, 768), 9},
    [60] = {SpawnPixelCoords(5008, 672), 22},
    [61] = {SpawnPixelCoords(5136, 896), 19},
    [62] = {SpawnPixelCoords(5152, 544), 18},
    [63] = {SpawnPixelCoords(5360, 576), 19},
    [64] = {SpawnPixelCoords(5376, 896), 18},
    [65] = {SpawnPixelCoords(5392, 736), 26},
    [66] = {SpawnPixelCoords(5472, 896), 18},
    [67] = {SpawnPixelCoords(5520, 592), 18},
    [68] = {SpawnPixelCoords(5600, 896), 18},
    [69] = {SpawnPixelCoords(5616, 432), 18},
    [70] = {SpawnPixelCoords(5632, 608), 19},
    [71] = {SpawnPixelCoords(5712, 432), 16},
    [72] = {SpawnPixelCoords(5744, 896), 13},
    [73] = {SpawnPixelCoords(5840, 432), 9},
    [74] = {SpawnPixelCoords(5840, 608), 19},
    [75] = {SpawnPixelCoords(5936, 608), 15},
    [76] = {SpawnPixelCoords(5952, 432), 18},
    [77] = {SpawnPixelCoords(5968, 768), 9},
    [78] = {SpawnPixelCoords(5968, 912), 14},
    [79] = {SpawnPixelCoords(6032, 560), 17},
    [80] = {SpawnPixelCoords(6096, 432), 19},
    [81] = {SpawnPixelCoords(6224, 432), 1},
    [82] = {SpawnPixelCoords(6464, 432), 1},
    [83] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Jungle_Preloads[14] = {
    {
        AP_SHEET_Z2_BABY_ELF,
        B8(01000000),
        976,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BEE,
        B8(00000001),
        655,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BEE_CARRIER,
        B8(00000001),
        689,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_MOLE,
        B8(00000001),
        712,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FLOWER,
        B8(00000001),
        781,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_PAD,
        B8(00000011),
        811,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_LIFT,
        B8(00001010),
        840,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHIELD_GUARD,
        B8(00000011),
        512,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SPIDER,
        B8(00001010),
        871,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_RESCUE,
        B8(10001000),
        671,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00001000),
        512,
        8,
        1,
        1,
        0,
    },
    {
        SM226_CRASH_CONTAINER,
        B8(00001000),
        720,
        9,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_RESCUE_RUN,
        B8(10000000),
        720,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
