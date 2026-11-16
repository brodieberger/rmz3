// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "ap.h"
#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApZ2Yggdrasil_Templates[28] = {
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
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_HATCH, 1, 0),
        },
    [4] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 0, 0),
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 1, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 2, 0),
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 3, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 4, 0),
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_TELEPORTER, 5, 0),
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_HOPPER, 1, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 1, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_EYE, 0, 0),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 0, 0),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 1, 0),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_COPTER, 2, 0),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 5, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 2, 0),
            .attr = 0x01,
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 1, 0),
            .attr = 0x01,
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 3, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_Z2_SPIDER, 0, 0),
            .attr = 0x01,
        },
    [23] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [24] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [25] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [26] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [27] =
        {
            .flag = 0x04,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_Z2_HATCH, 3, 0),
        },
};

const struct SpawnPoint gApZ2Yggdrasil_Points[55] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(464, 2464), 23},
    [2] = {SpawnPixelCoords(480, 464), 27},
    [3] = {SpawnPixelCoords(480, 736), 21},
    [4] = {SpawnPixelCoords(496, 2736), 13},
    [5] = {SpawnPixelCoords(512, 1984), 14},
    [6] = {SpawnPixelCoords(512, 2464), 13},
    [7] = {SpawnPixelCoords(528, 848), 20},
    [8] = {SpawnPixelCoords(528, 1776), 8},
    [9] = {SpawnPixelCoords(528, 3216), 5},
    [10] = {SpawnPixelCoords(544, 4048), 10},
    [11] = {SpawnPixelCoords(576, 1648), 7},
    [12] = {SpawnPixelCoords(576, 3088), 4},
    [13] = {SpawnPixelCoords(576, 3424), 11},
    [14] = {SpawnPixelCoords(624, 1776), 9},
    [15] = {SpawnPixelCoords(624, 3216), 6},
    [16] = {SpawnPixelCoords(640, 3856), 11},
    [17] = {SpawnPixelCoords(640, 4048), 10},
    [18] = {SpawnPixelCoords(672, 768), 17},
    [19] = {SpawnPixelCoords(672, 896), 17},
    [20] = {SpawnPixelCoords(704, 608), 2},
    [21] = {SpawnPixelCoords(704, 1728), 2},
    [22] = {SpawnPixelCoords(704, 1904), 1},
    [23] = {SpawnPixelCoords(704, 3168), 2},
    [24] = {SpawnPixelCoords(704, 3344), 1},
    [25] = {SpawnPixelCoords(704, 3584), 10},
    [26] = {SpawnPixelCoords(720, 1312), 22},
    [27] = {SpawnPixelCoords(720, 2272), 15},
    [28] = {SpawnPixelCoords(720, 2480), 13},
    [29] = {SpawnPixelCoords(736, 2592), 15},
    [30] = {SpawnPixelCoords(736, 4048), 10},
    [31] = {SpawnPixelCoords(752, 2800), 13},
    [32] = {SpawnPixelCoords(752, 3616), 10},
    [33] = {SpawnPixelCoords(816, 2128), 14},
    [34] = {SpawnPixelCoords(816, 2272), 15},
    [35] = {SpawnPixelCoords(816, 3840), 10},
    [36] = {SpawnPixelCoords(848, 592), 17},
    [37] = {SpawnPixelCoords(848, 2880), 23},
    [38] = {SpawnPixelCoords(864, 896), 17},
    [39] = {SpawnPixelCoords(880, 592), 17},
    [40] = {SpawnPixelCoords(880, 3664), 11},
    [41] = {SpawnPixelCoords(896, 640), 22},
    [42] = {SpawnPixelCoords(896, 896), 23},
    [43] = {SpawnPixelCoords(896, 1040), 18},
    [44] = {SpawnPixelCoords(896, 2464), 15},
    [45] = {SpawnPixelCoords(896, 2880), 13},
    [46] = {SpawnPixelCoords(912, 1360), 17},
    [47] = {SpawnPixelCoords(928, 592), 23},
    [48] = {SpawnPixelCoords(928, 2624), 13},
    [49] = {SpawnPixelCoords(944, 1360), 26},
    [50] = {SpawnPixelCoords(944, 2048), 13},
    [51] = {SpawnPixelCoords(944, 2336), 13},
    [52] = {SpawnPixelCoords(944, 3664), 11},
    [53] = {SpawnPixelCoords(992, 4160), 11},
    [54] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApZ2Yggdrasil_Preloads[10] = {
    {
        AP_SHEET_Z2_FEFNIR_SUMMON,
        B8(00000000),
        512,
        8,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_TELEPORTER,
        B8(00000111),
        512,
        5,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_HOPPER,
        B8(00000001),
        704,
        6,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        AP_SHEET_Z2_EYE,
        B8(00000001),
        656,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000010),
        704,
        6,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_COPTER,
        B8(00000010),
        656,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00000100),
        704,
        6,
        1,
        1,
        0,
    },
    {
        AP_SHEET_Z2_SPIDER,
        B8(00000100),
        858,
        7,
        1,
        AP_PRELOAD_SHEET | 1,
        0,
    },
    {
        32,
        B8(00001000),
        637,
        5,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
