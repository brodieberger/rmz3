// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Na1_Templates[32] = {
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
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_H, 0, 0),
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_GATE, 0, 0),
        },
    [8] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SLAB, 2, 0),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 64, 0, 1),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 0, 1),
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 1, 1),
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_MINE_SPAWNER, 2, 1),
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIKEBALL, 0, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIKEBALL, 1, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 1, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 0, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 0, 0),
            .attr = 0x01,
        },
    [27] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 1, 0),
            .attr = 0x01,
        },
    [28] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHELL, 0, 0),
            .attr = 0x01,
        },
    [29] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHELL, 1, 0),
            .attr = 0x01,
        },
    [30] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 194, 0),
        },
    [31] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 195, 0),
        },
};

const struct SpawnPoint gApZ2Na1_Points[85] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(640, 736), 25},
    [2] = {SpawnPixelCoords(672, 736), 25},
    [3] = {SpawnPixelCoords(704, 736), 7},
    [4] = {SpawnPixelCoords(816, 576), 11},
    [5] = {SpawnPixelCoords(1024, 736), 25},
    [6] = {SpawnPixelCoords(1056, 608), 11},
    [7] = {SpawnPixelCoords(1056, 736), 25},
    [8] = {SpawnPixelCoords(1248, 608), 11},
    [9] = {SpawnPixelCoords(1280, 736), 25},
    [10] = {SpawnPixelCoords(1312, 736), 25},
    [11] = {SpawnPixelCoords(1472, 624), 11},
    [12] = {SpawnPixelCoords(1568, 592), 10},
    [13] = {SpawnPixelCoords(1600, 736), 25},
    [14] = {SpawnPixelCoords(1632, 736), 25},
    [15] = {SpawnPixelCoords(1664, 736), 7},
    [16] = {SpawnPixelCoords(1792, 704), 25},
    [17] = {SpawnPixelCoords(1824, 704), 25},
    [18] = {SpawnPixelCoords(1904, 704), 7},
    [19] = {SpawnPixelCoords(1968, 560), 11},
    [20] = {SpawnPixelCoords(2128, 576), 11},
    [21] = {SpawnPixelCoords(2256, 624), 11},
    [22] = {SpawnPixelCoords(2384, 688), 11},
    [23] = {SpawnPixelCoords(2432, 1120), 28},
    [24] = {SpawnPixelCoords(2448, 1024), 30},
    [25] = {SpawnPixelCoords(2480, 576), 10},
    [26] = {SpawnPixelCoords(2480, 976), 23},
    [27] = {SpawnPixelCoords(2544, 1200), 21},
    [28] = {SpawnPixelCoords(2592, 976), 23},
    [29] = {SpawnPixelCoords(2608, 560), 4},
    [30] = {SpawnPixelCoords(2624, 704), 7},
    [31] = {SpawnPixelCoords(2656, 1136), 24},
    [32] = {SpawnPixelCoords(2688, 1216), 8},
    [33] = {SpawnPixelCoords(2704, 704), 25},
    [34] = {SpawnPixelCoords(2704, 976), 23},
    [35] = {SpawnPixelCoords(2720, 1216), 8},
    [36] = {SpawnPixelCoords(2752, 1136), 24},
    [37] = {SpawnPixelCoords(2752, 1216), 8},
    [38] = {SpawnPixelCoords(2784, 1040), 26},
    [39] = {SpawnPixelCoords(2816, 1216), 8},
    [40] = {SpawnPixelCoords(2832, 976), 23},
    [41] = {SpawnPixelCoords(2848, 1136), 24},
    [42] = {SpawnPixelCoords(2848, 1216), 8},
    [43] = {SpawnPixelCoords(2912, 1216), 8},
    [44] = {SpawnPixelCoords(2944, 784), 28},
    [45] = {SpawnPixelCoords(2944, 1136), 24},
    [46] = {SpawnPixelCoords(2976, 1216), 8},
    [47] = {SpawnPixelCoords(3008, 1008), 21},
    [48] = {SpawnPixelCoords(3040, 592), 20},
    [49] = {SpawnPixelCoords(3040, 960), 29},
    [50] = {SpawnPixelCoords(3040, 1136), 24},
    [51] = {SpawnPixelCoords(3072, 1216), 8},
    [52] = {SpawnPixelCoords(3136, 1136), 24},
    [53] = {SpawnPixelCoords(3168, 1216), 8},
    [54] = {SpawnPixelCoords(3184, 1072), 31},
    [55] = {SpawnPixelCoords(3216, 1072), 27},
    [56] = {SpawnPixelCoords(3264, 1216), 8},
    [57] = {SpawnPixelCoords(3296, 1168), 29},
    [58] = {SpawnPixelCoords(3344, 1088), 5},
    [59] = {SpawnPixelCoords(3376, 480), 28},
    [60] = {SpawnPixelCoords(3376, 592), 8},
    [61] = {SpawnPixelCoords(3408, 592), 8},
    [62] = {SpawnPixelCoords(3408, 784), 15},
    [63] = {SpawnPixelCoords(3408, 928), 15},
    [64] = {SpawnPixelCoords(3424, 672), 8},
    [65] = {SpawnPixelCoords(3424, 768), 8},
    [66] = {SpawnPixelCoords(3440, 864), 8},
    [67] = {SpawnPixelCoords(3440, 960), 8},
    [68] = {SpawnPixelCoords(3456, 1104), 8},
    [69] = {SpawnPixelCoords(3472, 816), 8},
    [70] = {SpawnPixelCoords(3472, 960), 8},
    [71] = {SpawnPixelCoords(3488, 544), 8},
    [72] = {SpawnPixelCoords(3488, 624), 8},
    [73] = {SpawnPixelCoords(3488, 912), 8},
    [74] = {SpawnPixelCoords(3488, 1056), 8},
    [75] = {SpawnPixelCoords(3504, 720), 8},
    [76] = {SpawnPixelCoords(3520, 544), 8},
    [77] = {SpawnPixelCoords(3520, 1008), 8},
    [78] = {SpawnPixelCoords(3520, 1056), 8},
    [79] = {SpawnPixelCoords(3552, 1008), 8},
    [80] = {SpawnPixelCoords(3568, 672), 23},
    [81] = {SpawnPixelCoords(3648, 528), 27},
    [82] = {SpawnPixelCoords(3824, 528), 5},
    [83] = {SpawnPixelCoords(3856, 1264), 6},
    [84] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Na1_Preloads[10] = {
    {
        AP_SHEET_Z2_GATE,
        B8(00000001),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_MINE,
        B8(00000001),
        624,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00000001),
        704,
        6,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_SLAB,
        B8(00000011),
        560,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00000011),
        592,
        8,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_SPIKEBALL,
        B8(00000010),
        687,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHIELD_GUARD,
        B8(00000010),
        784,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_EYE,
        B8(00000010),
        512,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHELL,
        B8(00000010),
        624,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
