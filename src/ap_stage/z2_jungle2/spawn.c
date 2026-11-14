// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Jungle2_Templates[34] = {
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE, 0, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_BEE_CARRIER, 0, 0),
            .attr = 0x01,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_FLOWER, 0, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MOLE, 0, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_PAD, 0, 0),
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_TREE_FROG, 0, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_TREE_FROG, 0, 1),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_LEAPER, 0, 1),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_LEAPER, 0, 0),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 5, 0),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 2, 0),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 1, 0),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 3, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 0, 0),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 0, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 1, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_BOX, 0, 0),
        },
    [23] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_BOX, 1, 0),
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
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 8, 2),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 114, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 115, 0),
        },
    [30] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 116, 0),
        },
    [31] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 117, 0),
        },
    [32] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 118, 0),
        },
    [33] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 119, 0),
        },
};

const struct SpawnPoint gApZ2Jungle2_Points[130] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(368, 560), 28},
    [2] = {SpawnPixelCoords(608, 528), 3},
    [3] = {SpawnPixelCoords(704, 688), 6},
    [4] = {SpawnPixelCoords(768, 464), 12},
    [5] = {SpawnPixelCoords(784, 672), 11},
    [6] = {SpawnPixelCoords(880, 656), 11},
    [7] = {SpawnPixelCoords(1024, 816), 14},
    [8] = {SpawnPixelCoords(1152, 736), 9},
    [9] = {SpawnPixelCoords(1232, 560), 3},
    [10] = {SpawnPixelCoords(1248, 640), 6},
    [11] = {SpawnPixelCoords(1280, 816), 13},
    [12] = {SpawnPixelCoords(1360, 752), 9},
    [13] = {SpawnPixelCoords(1424, 816), 13},
    [14] = {SpawnPixelCoords(1440, 576), 3},
    [15] = {SpawnPixelCoords(1456, 464), 12},
    [16] = {SpawnPixelCoords(1488, 544), 1},
    [17] = {SpawnPixelCoords(1520, 464), 12},
    [18] = {SpawnPixelCoords(1552, 816), 13},
    [19] = {SpawnPixelCoords(1712, 624), 11},
    [20] = {SpawnPixelCoords(1776, 816), 13},
    [21] = {SpawnPixelCoords(1808, 816), 13},
    [22] = {SpawnPixelCoords(1920, 384), 29},
    [23] = {SpawnPixelCoords(1920, 400), 10},
    [24] = {SpawnPixelCoords(1984, 320), 10},
    [25] = {SpawnPixelCoords(2096, 512), 10},
    [26] = {SpawnPixelCoords(2128, 320), 10},
    [27] = {SpawnPixelCoords(2144, 928), 21},
    [28] = {SpawnPixelCoords(2240, 512), 10},
    [29] = {SpawnPixelCoords(2256, 336), 10},
    [30] = {SpawnPixelCoords(2320, 928), 21},
    [31] = {SpawnPixelCoords(2352, 784), 4},
    [32] = {SpawnPixelCoords(2368, 352), 10},
    [33] = {SpawnPixelCoords(2368, 496), 10},
    [34] = {SpawnPixelCoords(2496, 480), 10},
    [35] = {SpawnPixelCoords(2512, 608), 10},
    [36] = {SpawnPixelCoords(2896, 176), 4},
    [37] = {SpawnPixelCoords(2912, 224), 3},
    [38] = {SpawnPixelCoords(2928, 224), 3},
    [39] = {SpawnPixelCoords(3072, 416), 3},
    [40] = {SpawnPixelCoords(3088, 416), 3},
    [41] = {SpawnPixelCoords(3136, 416), 21},
    [42] = {SpawnPixelCoords(3168, 768), 30},
    [43] = {SpawnPixelCoords(3184, 448), 23},
    [44] = {SpawnPixelCoords(3184, 560), 23},
    [45] = {SpawnPixelCoords(3232, 448), 23},
    [46] = {SpawnPixelCoords(3232, 560), 23},
    [47] = {SpawnPixelCoords(3376, 464), 19},
    [48] = {SpawnPixelCoords(3664, 544), 23},
    [49] = {SpawnPixelCoords(3696, 416), 15},
    [50] = {SpawnPixelCoords(3776, 256), 3},
    [51] = {SpawnPixelCoords(3792, 256), 3},
    [52] = {SpawnPixelCoords(3808, 736), 20},
    [53] = {SpawnPixelCoords(3824, 560), 3},
    [54] = {SpawnPixelCoords(3840, 560), 3},
    [55] = {SpawnPixelCoords(3888, 512), 23},
    [56] = {SpawnPixelCoords(3888, 752), 23},
    [57] = {SpawnPixelCoords(3952, 224), 23},
    [58] = {SpawnPixelCoords(4032, 336), 31},
    [59] = {SpawnPixelCoords(4064, 624), 3},
    [60] = {SpawnPixelCoords(4080, 624), 3},
    [61] = {SpawnPixelCoords(4096, 352), 23},
    [62] = {SpawnPixelCoords(4128, 560), 22},
    [63] = {SpawnPixelCoords(4128, 656), 23},
    [64] = {SpawnPixelCoords(4128, 736), 20},
    [65] = {SpawnPixelCoords(4240, 400), 32},
    [66] = {SpawnPixelCoords(4416, 464), 21},
    [67] = {SpawnPixelCoords(4448, 672), 23},
    [68] = {SpawnPixelCoords(4496, 672), 23},
    [69] = {SpawnPixelCoords(4560, 688), 3},
    [70] = {SpawnPixelCoords(4576, 688), 3},
    [71] = {SpawnPixelCoords(4592, 576), 23},
    [72] = {SpawnPixelCoords(4592, 688), 3},
    [73] = {SpawnPixelCoords(4624, 592), 3},
    [74] = {SpawnPixelCoords(4672, 512), 16},
    [75] = {SpawnPixelCoords(4688, 512), 1},
    [76] = {SpawnPixelCoords(4784, 432), 5},
    [77] = {SpawnPixelCoords(5024, 592), 5},
    [78] = {SpawnPixelCoords(5264, 592), 5},
    [79] = {SpawnPixelCoords(5312, 320), 1},
    [80] = {SpawnPixelCoords(5344, 464), 21},
    [81] = {SpawnPixelCoords(5504, 560), 23},
    [82] = {SpawnPixelCoords(5552, 576), 3},
    [83] = {SpawnPixelCoords(5568, 576), 3},
    [84] = {SpawnPixelCoords(5616, 368), 21},
    [85] = {SpawnPixelCoords(5744, 480), 23},
    [86] = {SpawnPixelCoords(5792, 448), 23},
    [87] = {SpawnPixelCoords(5808, 496), 23},
    [88] = {SpawnPixelCoords(5840, 352), 20},
    [89] = {SpawnPixelCoords(5856, 496), 22},
    [90] = {SpawnPixelCoords(5904, 544), 27},
    [91] = {SpawnPixelCoords(5936, 256), 22},
    [92] = {SpawnPixelCoords(5984, 576), 1},
    [93] = {SpawnPixelCoords(6048, 240), 3},
    [94] = {SpawnPixelCoords(6064, 240), 3},
    [95] = {SpawnPixelCoords(6064, 336), 3},
    [96] = {SpawnPixelCoords(6080, 336), 3},
    [97] = {SpawnPixelCoords(6096, 336), 3},
    [98] = {SpawnPixelCoords(6128, 464), 24},
    [99] = {SpawnPixelCoords(6128, 544), 24},
    [100] = {SpawnPixelCoords(6144, 368), 23},
    [101] = {SpawnPixelCoords(6192, 368), 17},
    [102] = {SpawnPixelCoords(6256, 560), 22},
    [103] = {SpawnPixelCoords(6304, 368), 18},
    [104] = {SpawnPixelCoords(6400, 400), 3},
    [105] = {SpawnPixelCoords(6400, 528), 25},
    [106] = {SpawnPixelCoords(6416, 400), 3},
    [107] = {SpawnPixelCoords(6512, 592), 16},
    [108] = {SpawnPixelCoords(6576, 512), 23},
    [109] = {SpawnPixelCoords(6624, 512), 23},
    [110] = {SpawnPixelCoords(6688, 560), 23},
    [111] = {SpawnPixelCoords(6688, 608), 23},
    [112] = {SpawnPixelCoords(6816, 560), 22},
    [113] = {SpawnPixelCoords(6880, 240), 3},
    [114] = {SpawnPixelCoords(6896, 240), 3},
    [115] = {SpawnPixelCoords(6896, 704), 33},
    [116] = {SpawnPixelCoords(6912, 448), 2},
    [117] = {SpawnPixelCoords(6976, 400), 20},
    [118] = {SpawnPixelCoords(7088, 240), 3},
    [119] = {SpawnPixelCoords(7104, 240), 3},
    [120] = {SpawnPixelCoords(7120, 240), 3},
    [121] = {SpawnPixelCoords(7136, 240), 3},
    [122] = {SpawnPixelCoords(7168, 448), 16},
    [123] = {SpawnPixelCoords(7296, 400), 19},
    [124] = {SpawnPixelCoords(7424, 448), 16},
    [125] = {SpawnPixelCoords(7552, 400), 19},
    [126] = {SpawnPixelCoords(7680, 448), 16},
    [127] = {SpawnPixelCoords(7904, 448), 5},
    [128] = {SpawnPixelCoords(8144, 448), 5},
    [129] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Jungle2_Preloads[16] = {
    {
        AP_SHEET_Z2_BABY_ELF,
        B8(10000000),
        699,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_X,
        B8(10000000),
        784,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        32,
        B8(00000011),
        637,
        5,
        1,
        1,
        0,
    },
    {
        32,
        B8(11000000),
        637,
        5,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_BEE,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BEE_CARRIER,
        B8(00000001),
        576,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_MOLE,
        B8(00000011),
        699,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_FLOWER,
        B8(00000001),
        546,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_TREE_FROG,
        B8(00000011),
        832,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_LEAPER,
        B8(00000011),
        599,
        10,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_PAD,
        B8(00000010),
        786,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_BOX,
        B8(00000100),
        785,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00000100),
        821,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHIELD_GUARD,
        B8(00000110),
        879,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SPIDER,
        B8(00000100),
        655,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
