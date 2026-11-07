// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Naold2_Templates[17] = {
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
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 1, 0),
            .attr = 0x01,
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 0, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_RING_CANNON, 1, 1),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 0, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 1, 0),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SIGNALOID, 2, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_DOOR, 1, 0),
        },
    [15] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 178, 0),
        },
    [16] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_AP_IMPORT_ELF, 179, 0),
        },
};

const struct SpawnPoint gApZ2Naold2_Points[43] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(752, 416), 6},
    [2] = {SpawnPixelCoords(896, 448), 6},
    [3] = {SpawnPixelCoords(992, 400), 6},
    [4] = {SpawnPixelCoords(1056, 400), 6},
    [5] = {SpawnPixelCoords(1152, 352), 6},
    [6] = {SpawnPixelCoords(1264, 352), 6},
    [7] = {SpawnPixelCoords(1360, 624), 3},
    [8] = {SpawnPixelCoords(1408, 624), 6},
    [9] = {SpawnPixelCoords(1456, 432), 7},
    [10] = {SpawnPixelCoords(1664, 400), 7},
    [11] = {SpawnPixelCoords(1744, 560), 6},
    [12] = {SpawnPixelCoords(1776, 400), 7},
    [13] = {SpawnPixelCoords(1872, 432), 15},
    [14] = {SpawnPixelCoords(1872, 624), 6},
    [15] = {SpawnPixelCoords(1872, 752), 3},
    [16] = {SpawnPixelCoords(1888, 752), 3},
    [17] = {SpawnPixelCoords(1904, 752), 3},
    [18] = {SpawnPixelCoords(1920, 752), 6},
    [19] = {SpawnPixelCoords(2048, 688), 3},
    [20] = {SpawnPixelCoords(2128, 608), 9},
    [21] = {SpawnPixelCoords(2336, 576), 6},
    [22] = {SpawnPixelCoords(2448, 656), 6},
    [23] = {SpawnPixelCoords(2496, 496), 9},
    [24] = {SpawnPixelCoords(2704, 528), 6},
    [25] = {SpawnPixelCoords(2736, 656), 4},
    [26] = {SpawnPixelCoords(2832, 496), 9},
    [27] = {SpawnPixelCoords(3136, 512), 9},
    [28] = {SpawnPixelCoords(3376, 544), 6},
    [29] = {SpawnPixelCoords(3456, 352), 16},
    [30] = {SpawnPixelCoords(3520, 480), 11},
    [31] = {SpawnPixelCoords(3568, 320), 7},
    [32] = {SpawnPixelCoords(3792, 688), 6},
    [33] = {SpawnPixelCoords(3840, 592), 12},
    [34] = {SpawnPixelCoords(3952, 320), 7},
    [35] = {SpawnPixelCoords(4080, 736), 13},
    [36] = {SpawnPixelCoords(4224, 528), 6},
    [37] = {SpawnPixelCoords(4352, 560), 6},
    [38] = {SpawnPixelCoords(4352, 704), 6},
    [39] = {SpawnPixelCoords(4544, 448), 5},
    [40] = {SpawnPixelCoords(4784, 448), 5},
    [41] = {SpawnPixelCoords(5024, 448), 14},
    [42] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Naold2_Preloads[5] = {
    {
        SM019_PANTHEON_HUNTER,
        B8(00000001),
        512,
        4,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_SIGNALOID,
        B8(00000001),
        852,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_EYE,
        B8(00000001),
        632,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_RING_CANNON,
        B8(00000001),
        680,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
