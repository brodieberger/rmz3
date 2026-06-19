#include "spawn.h"

#include "global.h"

// 0x0834b6d4
const struct SpawnTemplate gSubArcadiaEntity[36] =
    {
        [0] = {0},
        [1] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, ITEM_LIFE_M, 2),
            },
        [2] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, ITEM_LIFE_L, 2),
            },
        [3] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, ITEM_EC_L, 2),
            },
        [4] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, ITEM_EXLIFE, 2),
            },
        [5] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 0),
            },
        [6] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 1, 0),
            },
        [7] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 0, 0),
            },
        [8] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 1, 0),
            },
        [9] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 2, 0),
            },
        [10] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_SUBARCADIA, 2, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_SUBARCADIA, 0, 0),
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_SUBARCADIA, 1, 0),
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_SUBARCADIA, 3, 0),
            },
        [14] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 36, 2),
            },
        [15] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 38, 2),
            },
        [16] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 81, 2),
            },
        [17] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 180, 2),
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 8, 0),
            },
        [19] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 83),
            },
        [20] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 87),
            },
        [21] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [22] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [23] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [26] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [27] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [28] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [29] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [31] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CLAVEKER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CANNON_HOPPER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_FIST, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [35] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },

};

const struct PreloadEntity gSubArcadiaStatic[14] = {
    {
        19,
        64,
        802,
        8,
        3,
        3,
        0,
    },
    {
        108,
        1,
        512,
        4,
        3,
        3,
        1,
    },
    {
        126,
        1,
        552,
        5,
        1,
        3,
        0,
    },
    {
        104,
        1,
        632,
        6,
        1,
        3,
        0,
    },
    {
        19,
        1,
        674,
        7,
        1,
        1,
        0,
    },
    {
        102,
        1,
        794,
        8,
        3,
        3,
        0,
    },
    {
        123,
        1,
        842,
        9,
        3,
        3,
        1,
    },
    {
        117,
        2,
        512,
        4,
        1,
        3,
        0,
    },
    {
        220,
        2,
        555,
        5,
        1,
        3,
        0,
    },
    {
        212,
        2,
        611,
        7,
        1,
        1,
        0,
    },
    {
        61,
        3,
        925,
        13,
        1,
        2,
        0,
    },
    {
        62,
        3,
        674,
        7,
        1,
        2,
        0,
    },
    {
        221,
        63,
        930,
        7,
        2,
        3,
        0,
    },
    {
        255,
        255,
        4095,
        15,
        1,
        3,
        1,
    },
};

// clang-format off
const struct SpawnPoint gSubArcadiaEntityCoord[62] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x00000010, 0x0042, 15 },
    [2] = { 0x00000015, 0x0042, 18 },
    [3] = { 0x0000001D, 0x0042, 9 },
    [4] = { 0x00000022, 0x004E, 28 },
    [5] = { 0x00000026, 0x004B, 11 },
    [6] = { 0x00000027, 0x0056, 13 },
    [7] = { 0x00000028, 0x005C, 11 },
    [8] = { 0x00000029, 0x000F, 30 },
    [9] = { 0x0000002A, 0x0061, 13 },
    [10] = { 0x0000002D, 0x000B, 31 },
    [11] = { 0x0000002D, 0x0042, 11 },
    [12] = { 0x0000002E, 0x0066, 17 },
    [13] = { 0x0000002F, 0x0049, 13 },
    [14] = { 0x00000031, 0x0062, 13 },
    [15] = { 0x00000032, 0x0057, 11 },
    [16] = { 0x00000033, 0x0010, 25 },
    [17] = { 0x00000033, 0x0012, 3 },
    [18] = { 0x00000035, 0x0049, 16 },
    [19] = { 0x00000038, 0x005C, 12 },
    [20] = { 0x0000003A, 0x0042, 25 },
    [21] = { 0x0000003B, 0x003F, 30 },
    [22] = { 0x0000003D, 0x000E, 30 },
    [23] = { 0x0000003D, 0x0018, 14 },
    [24] = { 0x0000003D, 0x0024, 23 },
    [25] = { 0x0000003E, 0x003C, 30 },
    [26] = { 0x0000003F, 0x001B, 28 },
    [27] = { 0x0000003F, 0x0027, 26 },
    [28] = { 0x00000040, 0x005E, 31 },
    [29] = { 0x00000041, 0x0039, 30 },
    [30] = { 0x00000043, 0x0062, 4 },
    [31] = { 0x0000004A, 0x006B, 7 },
    [32] = { 0x00000059, 0x006B, 7 },
    [33] = { 0x00000065, 0x006B, 33 },
    [34] = { 0x0000006B, 0x006B, 34 },
    [35] = { 0x00000070, 0x006B, 20 },
    [36] = { 0x00000072, 0x0065, 32 },
    [37] = { 0x00000079, 0x006B, 34 },
    [38] = { 0x0000007D, 0x0077, 33 },
    [39] = { 0x0000007D, 0x0088, 33 },
    [40] = { 0x0000007E, 0x0092, 33 },
    [41] = { 0x00000080, 0x007D, 33 },
    [42] = { 0x00000081, 0x0074, 33 },
    [43] = { 0x00000081, 0x0085, 33 },
    [44] = { 0x0000008A, 0x0092, 34 },
    [45] = { 0x0000008F, 0x008F, 32 },
    [46] = { 0x00000096, 0x0094, 33 },
    [47] = { 0x0000009C, 0x008D, 32 },
    [48] = { 0x000000A6, 0x009C, 1 },
    [49] = { 0x000000A6, 0x00B3, 19 },
    [50] = { 0x000000AA, 0x00BA, 34 },
    [51] = { 0x000000AC, 0x00A8, 32 },
    [52] = { 0x000000AC, 0x00BF, 32 },
    [53] = { 0x000000AE, 0x00A3, 34 },
    [54] = { 0x000000AE, 0x00D0, 33 },
    [55] = { 0x000000B1, 0x00B3, 34 },
    [56] = { 0x000000B9, 0x00CE, 33 },
    [57] = { 0x000000C2, 0x00CC, 24 },
    [58] = { 0x000000C6, 0x00CC, 34 },
    [59] = { 0x000000D1, 0x00CF, 5 },
    [60] = { 0x000000E0, 0x00CF, 5 },
    [61] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
