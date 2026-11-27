// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Bomber_Templates[43] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 0, 0),
        },
    [2] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 1, 0),
        },
    [3] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 2, 0),
        },
    [4] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 3, 0),
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 4, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 5, 0),
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_PYLON, 6, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 0, 0),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 1, 0),
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 2, 0),
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 3, 0),
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_PROJECTILE, PROJECTILE_Z2_PYLON_HAZARD, 4, 0),
        },
    [13] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [14] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [15] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [16] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 0, 0),
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0),
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 2, 0),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 0, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 1, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 2, 0),
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 0, 0),
            .attr = 0x01,
        },
    [28] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 1, 0),
            .attr = 0x01,
        },
    [29] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HOPPER, 1, 0),
            .attr = 0x01,
        },
    [30] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 0),
            .attr = 0x01,
        },
    [31] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 1),
            .attr = 0x01,
        },
    [32] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 31, 1, 0),
            .attr = 0x01,
        },
    [33] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_CRAFT, 0, 0),
        },
    [34] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_CRAFT, 7, 0),
        },
    [35] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF_BOX, 98, 0),
        },
    [36] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF_BOX, 101, 0),
        },
    [37] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF_BOX, 99, 2),
        },
    [38] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF_BOX, 100, 2),
        },
    [39] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_CRAFT, 0, 1),
        },
    [40] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_CARGO, 0, 0),
        },
    [41] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_CARGO, 1, 0),
        },
    [42] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_HATCH, 0, 0),
        },
};

const struct SpawnPoint gApZ2Bomber_Points[102] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(368, 1632), 33},
    [2] = {SpawnPixelCoords(832, 1600), 39},
    [3] = {SpawnPixelCoords(1280, 1568), 33},
    [4] = {SpawnPixelCoords(1472, 1536), 33},
    [5] = {SpawnPixelCoords(1632, 1680), 39},
    [6] = {SpawnPixelCoords(1664, 1488), 39},
    [7] = {SpawnPixelCoords(2112, 1680), 39},
    [8] = {SpawnPixelCoords(2336, 1488), 39},
    [9] = {SpawnPixelCoords(2640, 1680), 13},
    [10] = {SpawnPixelCoords(2752, 2080), 34},
    [11] = {SpawnPixelCoords(2752, 2224), 34},
    [12] = {SpawnPixelCoords(2752, 2368), 34},
    [13] = {SpawnPixelCoords(2768, 1872), 35},
    [14] = {SpawnPixelCoords(2800, 1872), 15},
    [15] = {SpawnPixelCoords(2816, 2496), 13},
    [16] = {SpawnPixelCoords(2864, 1872), 19},
    [17] = {SpawnPixelCoords(2864, 2496), 17},
    [18] = {SpawnPixelCoords(2912, 2336), 11},
    [19] = {SpawnPixelCoords(2912, 2368), 11},
    [20] = {SpawnPixelCoords(2976, 2032), 21},
    [21] = {SpawnPixelCoords(3040, 2320), 37},
    [22] = {SpawnPixelCoords(3056, 2128), 3},
    [23] = {SpawnPixelCoords(3104, 1872), 18},
    [24] = {SpawnPixelCoords(3104, 2032), 18},
    [25] = {SpawnPixelCoords(3216, 2432), 4},
    [26] = {SpawnPixelCoords(3232, 1984), 12},
    [27] = {SpawnPixelCoords(3296, 1984), 12},
    [28] = {SpawnPixelCoords(3312, 1808), 16},
    [29] = {SpawnPixelCoords(3360, 1984), 12},
    [30] = {SpawnPixelCoords(3392, 2528), 21},
    [31] = {SpawnPixelCoords(3424, 1984), 12},
    [32] = {SpawnPixelCoords(3440, 2448), 12},
    [33] = {SpawnPixelCoords(3488, 1984), 12},
    [34] = {SpawnPixelCoords(3536, 2432), 28},
    [35] = {SpawnPixelCoords(3552, 1984), 12},
    [36] = {SpawnPixelCoords(3568, 1952), 24},
    [37] = {SpawnPixelCoords(3568, 2480), 12},
    [38] = {SpawnPixelCoords(3616, 1984), 9},
    [39] = {SpawnPixelCoords(3632, 2480), 10},
    [40] = {SpawnPixelCoords(3664, 1984), 12},
    [41] = {SpawnPixelCoords(3664, 2752), 38},
    [42] = {SpawnPixelCoords(3680, 2752), 40},
    [43] = {SpawnPixelCoords(3696, 2832), 41},
    [44] = {SpawnPixelCoords(3728, 1952), 24},
    [45] = {SpawnPixelCoords(3728, 1984), 12},
    [46] = {SpawnPixelCoords(3728, 2480), 12},
    [47] = {SpawnPixelCoords(3792, 1952), 24},
    [48] = {SpawnPixelCoords(3792, 1984), 12},
    [49] = {SpawnPixelCoords(3792, 2784), 40},
    [50] = {SpawnPixelCoords(3824, 1520), 20},
    [51] = {SpawnPixelCoords(3824, 2448), 21},
    [52] = {SpawnPixelCoords(3824, 2528), 5},
    [53] = {SpawnPixelCoords(3840, 2784), 40},
    [54] = {SpawnPixelCoords(3856, 1984), 11},
    [55] = {SpawnPixelCoords(3856, 2464), 12},
    [56] = {SpawnPixelCoords(3904, 1536), 20},
    [57] = {SpawnPixelCoords(3920, 1952), 2},
    [58] = {SpawnPixelCoords(3936, 2992), 40},
    [59] = {SpawnPixelCoords(3968, 2800), 28},
    [60] = {SpawnPixelCoords(3984, 2992), 40},
    [61] = {SpawnPixelCoords(4032, 2992), 40},
    [62] = {SpawnPixelCoords(4048, 1952), 21},
    [63] = {SpawnPixelCoords(4064, 1520), 20},
    [64] = {SpawnPixelCoords(4064, 2512), 8},
    [65] = {SpawnPixelCoords(4080, 2032), 12},
    [66] = {SpawnPixelCoords(4080, 2832), 41},
    [67] = {SpawnPixelCoords(4112, 2048), 13},
    [68] = {SpawnPixelCoords(4128, 2992), 40},
    [69] = {SpawnPixelCoords(4144, 2032), 10},
    [70] = {SpawnPixelCoords(4160, 2528), 28},
    [71] = {SpawnPixelCoords(4176, 2992), 40},
    [72] = {SpawnPixelCoords(4192, 2512), 8},
    [73] = {SpawnPixelCoords(4192, 2816), 28},
    [74] = {SpawnPixelCoords(4224, 1536), 20},
    [75] = {SpawnPixelCoords(4224, 2992), 40},
    [76] = {SpawnPixelCoords(4240, 2032), 12},
    [77] = {SpawnPixelCoords(4256, 2048), 15},
    [78] = {SpawnPixelCoords(4256, 2816), 40},
    [79] = {SpawnPixelCoords(4288, 2528), 6},
    [80] = {SpawnPixelCoords(4288, 2992), 27},
    [81] = {SpawnPixelCoords(4304, 2832), 40},
    [82] = {SpawnPixelCoords(4352, 2832), 40},
    [83] = {SpawnPixelCoords(4368, 1536), 20},
    [84] = {SpawnPixelCoords(4368, 2032), 12},
    [85] = {SpawnPixelCoords(4384, 2048), 15},
    [86] = {SpawnPixelCoords(4432, 2448), 12},
    [87] = {SpawnPixelCoords(4432, 2480), 12},
    [88] = {SpawnPixelCoords(4432, 2512), 12},
    [89] = {SpawnPixelCoords(4448, 2016), 1},
    [90] = {SpawnPixelCoords(4496, 2512), 12},
    [91] = {SpawnPixelCoords(4560, 2512), 12},
    [92] = {SpawnPixelCoords(4592, 1680), 15},
    [93] = {SpawnPixelCoords(4592, 2704), 42},
    [94] = {SpawnPixelCoords(4608, 1680), 15},
    [95] = {SpawnPixelCoords(4608, 2608), 13},
    [96] = {SpawnPixelCoords(4624, 2512), 12},
    [97] = {SpawnPixelCoords(4688, 2512), 12},
    [98] = {SpawnPixelCoords(4736, 2416), 7},
    [99] = {SpawnPixelCoords(4752, 2416), 36},
    [100] = {SpawnPixelCoords(4752, 2512), 9},
    [101] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Bomber_Preloads[14] = {
    {
        AP_SHEET_Z2_GUNSHIP,
        B8(00000000),
        512,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GUNSHIP_FAR,
        B8(00000000),
        528,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_GUNSHIP_FIRE,
        B8(00000000),
        784,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000001),
        768,
        5,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_CRAFT,
        B8(00000101),
        512,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00001000),
        854,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_PYLON,
        B8(01011000),
        655,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SIGNALOID,
        B8(00011000),
        682,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HOPPER,
        B8(00100000),
        736,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_RAIDER,
        B8(00100000),
        896,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HATCH,
        B8(11000000),
        768,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHIELD_GUARD,
        B8(11010000),
        512,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CARGO,
        B8(11000000),
        800,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
