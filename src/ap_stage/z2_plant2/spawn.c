// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Plant2_Templates[40] = {
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
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0),
        },
    [7] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_SLAB, 1, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 0, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SHIELD_GUARD, 1, 0),
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 0, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 1, 0),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 2, 0),
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 1),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 0),
        },
    [27] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 16),
        },
    [28] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 32),
        },
    [29] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 48),
        },
    [30] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 64),
        },
    [31] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 0, 80),
        },
    [32] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 0),
        },
    [33] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 16),
        },
    [34] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 32),
        },
    [35] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 48),
        },
    [36] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 64),
        },
    [37] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_MAGMA_DROPPER, 1, 80),
        },
    [38] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 163, 0),
        },
    [39] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 162, 0),
        },
};

const struct SpawnPoint gApZ2Plant2_Points[89] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(224, 704), 5},
    [2] = {SpawnPixelCoords(496, 1248), 3},
    [3] = {SpawnPixelCoords(560, 976), 19},
    [4] = {SpawnPixelCoords(592, 1184), 19},
    [5] = {SpawnPixelCoords(624, 1360), 19},
    [6] = {SpawnPixelCoords(640, 1712), 10},
    [7] = {SpawnPixelCoords(656, 1344), 3},
    [8] = {SpawnPixelCoords(704, 704), 6},
    [9] = {SpawnPixelCoords(832, 1760), 36},
    [10] = {SpawnPixelCoords(992, 1776), 18},
    [11] = {SpawnPixelCoords(1104, 1872), 27},
    [12] = {SpawnPixelCoords(1232, 1776), 18},
    [13] = {SpawnPixelCoords(1360, 1760), 36},
    [14] = {SpawnPixelCoords(1552, 1840), 27},
    [15] = {SpawnPixelCoords(1728, 1824), 8},
    [16] = {SpawnPixelCoords(1872, 1760), 36},
    [17] = {SpawnPixelCoords(1968, 1872), 29},
    [18] = {SpawnPixelCoords(2016, 1872), 28},
    [19] = {SpawnPixelCoords(2112, 1760), 36},
    [20] = {SpawnPixelCoords(2160, 1760), 35},
    [21] = {SpawnPixelCoords(2208, 1760), 34},
    [22] = {SpawnPixelCoords(2432, 2000), 3},
    [23] = {SpawnPixelCoords(2432, 2064), 1},
    [24] = {SpawnPixelCoords(2448, 2128), 9},
    [25] = {SpawnPixelCoords(2464, 1792), 8},
    [26] = {SpawnPixelCoords(2480, 2064), 9},
    [27] = {SpawnPixelCoords(2496, 1904), 39},
    [28] = {SpawnPixelCoords(2512, 2000), 9},
    [29] = {SpawnPixelCoords(2640, 2288), 18},
    [30] = {SpawnPixelCoords(2848, 2384), 30},
    [31] = {SpawnPixelCoords(3008, 2272), 18},
    [32] = {SpawnPixelCoords(3216, 2320), 9},
    [33] = {SpawnPixelCoords(3264, 2384), 30},
    [34] = {SpawnPixelCoords(3552, 2336), 9},
    [35] = {SpawnPixelCoords(3648, 2384), 27},
    [36] = {SpawnPixelCoords(3792, 2240), 33},
    [37] = {SpawnPixelCoords(3936, 2384), 31},
    [38] = {SpawnPixelCoords(4272, 2272), 11},
    [39] = {SpawnPixelCoords(4368, 2288), 11},
    [40] = {SpawnPixelCoords(4464, 2304), 11},
    [41] = {SpawnPixelCoords(4512, 2256), 2},
    [42] = {SpawnPixelCoords(4528, 2256), 4},
    [43] = {SpawnPixelCoords(4656, 2240), 32},
    [44] = {SpawnPixelCoords(4720, 2272), 18},
    [45] = {SpawnPixelCoords(4784, 2352), 7},
    [46] = {SpawnPixelCoords(4816, 2352), 7},
    [47] = {SpawnPixelCoords(4848, 2352), 7},
    [48] = {SpawnPixelCoords(4944, 2336), 7},
    [49] = {SpawnPixelCoords(4976, 2336), 7},
    [50] = {SpawnPixelCoords(5040, 2320), 7},
    [51] = {SpawnPixelCoords(5104, 2304), 7},
    [52] = {SpawnPixelCoords(5168, 2352), 7},
    [53] = {SpawnPixelCoords(5200, 2352), 7},
    [54] = {SpawnPixelCoords(5264, 2336), 7},
    [55] = {SpawnPixelCoords(5312, 2384), 27},
    [56] = {SpawnPixelCoords(5360, 2336), 7},
    [57] = {SpawnPixelCoords(5392, 2304), 7},
    [58] = {SpawnPixelCoords(5424, 2304), 7},
    [59] = {SpawnPixelCoords(5456, 2304), 7},
    [60] = {SpawnPixelCoords(5584, 2352), 7},
    [61] = {SpawnPixelCoords(5616, 2352), 7},
    [62] = {SpawnPixelCoords(5664, 2384), 26},
    [63] = {SpawnPixelCoords(5712, 2352), 7},
    [64] = {SpawnPixelCoords(5744, 2352), 7},
    [65] = {SpawnPixelCoords(5776, 2352), 7},
    [66] = {SpawnPixelCoords(5792, 688), 12},
    [67] = {SpawnPixelCoords(5792, 1376), 12},
    [68] = {SpawnPixelCoords(5808, 512), 1},
    [69] = {SpawnPixelCoords(5824, 2272), 18},
    [70] = {SpawnPixelCoords(5856, 800), 13},
    [71] = {SpawnPixelCoords(5856, 992), 13},
    [72] = {SpawnPixelCoords(5872, 1456), 15},
    [73] = {SpawnPixelCoords(5872, 1728), 10},
    [74] = {SpawnPixelCoords(5872, 1888), 23},
    [75] = {SpawnPixelCoords(5872, 2048), 23},
    [76] = {SpawnPixelCoords(5904, 1088), 38},
    [77] = {SpawnPixelCoords(5920, 592), 8},
    [78] = {SpawnPixelCoords(5936, 768), 3},
    [79] = {SpawnPixelCoords(5936, 928), 24},
    [80] = {SpawnPixelCoords(5952, 1408), 24},
    [81] = {SpawnPixelCoords(5952, 1808), 21},
    [82] = {SpawnPixelCoords(5952, 2128), 1},
    [83] = {SpawnPixelCoords(5968, 768), 21},
    [84] = {SpawnPixelCoords(6064, 512), 18},
    [85] = {SpawnPixelCoords(6144, 592), 8},
    [86] = {SpawnPixelCoords(6224, 592), 5},
    [87] = {SpawnPixelCoords(6464, 592), 5},
    [88] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Plant2_Preloads[8] = {
    {
        AP_SHEET_Z2_MAGMA,
        B8(00000001),
        705,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_CRUMBLE,
        B8(00000001),
        771,
        9,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SHIELD_GUARD,
        B8(00000011),
        544,
        4,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00000011),
        512,
        5,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00000011),
        687,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_RING_CANNON,
        B8(00000010),
        705,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_SIGNALOID,
        B8(00000010),
        823,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
