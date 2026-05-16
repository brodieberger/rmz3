#include "spawn.h"

#include "global.h"

// 0x0834a4d4
const struct SpawnTemplate gEnergyFacilityEntity[51] =
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 0, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 1, 0),
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 2, 0),
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 3, 0),
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 4, 0),
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LIGHT_SWITCH, 5, 0),
            },
        [16] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 4, 2),
            },
        [17] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 78, 2),
            },
        [18] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 64, 2),
            },
        [19] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 124, 2),
            },
        [20] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 56),
            },
        [21] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 82),
            },
        [22] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 95, 2),
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [24] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [26] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [27] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MOTHJIRO, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [28] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MOTHJIRO, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [29] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [35] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [36] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [37] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [38] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [39] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [40] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [41] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [42] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LAMPLORT, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [43] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LAMPLORT, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [44] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [45] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [46] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [47] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [48] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SNAKECORD, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [49] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_TOGGLE_SWITCH_YELLOW, 0, 0),
            },
        [50] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

const struct PreloadEntity gEnergyFacilityStatic[16] = {
    {
        21,
        65,
        512,
        4,
        1,
        3,
        0,
    },
    {
        223,
        1,
        544,
        5,
        3,
        3,
        1,
    },
    {
        107,
        1,
        565,
        6,
        1,
        3,
        0,
    },
    {
        126,
        1,
        613,
        7,
        1,
        3,
        0,
    },
    {
        104,
        1,
        693,
        8,
        1,
        3,
        0,
    },
    {
        222,
        2,
        512,
        4,
        3,
        3,
        1,
    },
    {
        40,
        2,
        568,
        5,
        1,
        3,
        0,
    },
    {
        210,
        2,
        656,
        6,
        3,
        3,
        1,
    },
    {
        25,
        2,
        683,
        7,
        1,
        1,
        0,
    },
    {
        22,
        2,
        839,
        8,
        1,
        1,
        0,
    },
    {
        61,
        2,
        683,
        13,
        1,
        2,
        0,
    },
    {
        62,
        2,
        712,
        7,
        1,
        2,
        0,
    },
    {
        63,
        2,
        812,
        8,
        1,
        2,
        0,
    },
    {
        67,
        0,
        937,
        9,
        3,
        3,
        0,
    },
    {
        221,
        31,
        839,
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
const struct SpawnPoint gEnergyFacilityEntityCoord[118] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x00000020, 0x0022, 28 },
    [2] = { 0x00000022, 0x002E, 28 },
    [3] = { 0x00000027, 0x0023, 28 },
    [4] = { 0x00000028, 0x0021, 27 },
    [5] = { 0x0000002A, 0x0026, 10 },
    [6] = { 0x0000002B, 0x002F, 25 },
    [7] = { 0x0000002F, 0x001C, 32 },
    [8] = { 0x0000002F, 0x0022, 27 },
    [9] = { 0x00000030, 0x002A, 27 },
    [10] = { 0x00000034, 0x0021, 33 },
    [11] = { 0x00000039, 0x0026, 32 },
    [12] = { 0x0000003A, 0x0017, 29 },
    [13] = { 0x00000044, 0x002C, 27 },
    [14] = { 0x00000048, 0x0030, 20 },
    [15] = { 0x0000004D, 0x002C, 27 },
    [16] = { 0x0000004E, 0x0030, 11 },
    [17] = { 0x00000051, 0x002A, 28 },
    [18] = { 0x00000055, 0x002E, 27 },
    [19] = { 0x00000058, 0x002D, 28 },
    [20] = { 0x0000005B, 0x0014, 40 },
    [21] = { 0x0000005B, 0x0023, 40 },
    [22] = { 0x0000005F, 0x001B, 41 },
    [23] = { 0x00000062, 0x0019, 19 },
    [24] = { 0x00000063, 0x0019, 1 },
    [25] = { 0x00000065, 0x0030, 32 },
    [26] = { 0x00000067, 0x0010, 31 },
    [27] = { 0x00000067, 0x002B, 29 },
    [28] = { 0x0000006F, 0x0012, 21 },
    [29] = { 0x0000007A, 0x000C, 27 },
    [30] = { 0x0000007A, 0x0010, 28 },
    [31] = { 0x0000007B, 0x0012, 12 },
    [32] = { 0x00000080, 0x000F, 27 },
    [33] = { 0x00000084, 0x0011, 28 },
    [34] = { 0x00000085, 0x000B, 27 },
    [35] = { 0x0000008C, 0x000F, 27 },
    [36] = { 0x00000093, 0x0012, 28 },
    [37] = { 0x00000094, 0x000E, 28 },
    [38] = { 0x0000009D, 0x0010, 32 },
    [39] = { 0x000000A8, 0x000E, 32 },
    [40] = { 0x000000B0, 0x000E, 28 },
    [41] = { 0x000000B4, 0x0011, 28 },
    [42] = { 0x000000B8, 0x0012, 13 },
    [43] = { 0x000000B9, 0x000F, 27 },
    [44] = { 0x000000BB, 0x001B, 40 },
    [45] = { 0x000000BC, 0x002B, 41 },
    [46] = { 0x000000BD, 0x0011, 27 },
    [47] = { 0x000000C1, 0x0010, 41 },
    [48] = { 0x000000C1, 0x0021, 29 },
    [49] = { 0x000000C1, 0x0024, 1 },
    [50] = { 0x000000C6, 0x0030, 26 },
    [51] = { 0x000000D1, 0x0030, 7 },
    [52] = { 0x000000E0, 0x0030, 7 },
    [53] = { 0x000000EF, 0x0030, 9 },
    [54] = { 0x000000FE, 0x0030, 7 },
    [55] = { 0x0000010E, 0x002E, 25 },
    [56] = { 0x00000116, 0x002C, 28 },
    [57] = { 0x00000120, 0x0029, 27 },
    [58] = { 0x00000120, 0x0030, 14 },
    [59] = { 0x00000121, 0x002E, 28 },
    [60] = { 0x00000128, 0x002F, 27 },
    [61] = { 0x0000012A, 0x002C, 28 },
    [62] = { 0x0000012D, 0x0020, 1 },
    [63] = { 0x00000130, 0x002E, 27 },
    [64] = { 0x00000131, 0x0017, 28 },
    [65] = { 0x00000133, 0x001C, 15 },
    [66] = { 0x00000134, 0x0028, 40 },
    [67] = { 0x00000137, 0x0018, 27 },
    [68] = { 0x00000137, 0x001C, 28 },
    [69] = { 0x00000137, 0x0023, 33 },
    [70] = { 0x00000138, 0x0030, 3 },
    [71] = { 0x00000139, 0x0030, 3 },
    [72] = { 0x0000013B, 0x001B, 27 },
    [73] = { 0x0000013D, 0x001C, 26 },
    [74] = { 0x00000149, 0x001B, 7 },
    [75] = { 0x00000158, 0x001B, 7 },
    [76] = { 0x00000167, 0x001B, 9 },
    [77] = { 0x00000176, 0x001B, 7 },
    [78] = { 0x0000018E, 0x0011, 18 },
    [79] = { 0x00000191, 0x000D, 48 },
    [80] = { 0x00000195, 0x0013, 44 },
    [81] = { 0x00000196, 0x001C, 25 },
    [82] = { 0x0000019B, 0x0010, 48 },
    [83] = { 0x0000019B, 0x001A, 49 },
    [84] = { 0x000001BB, 0x0015, 44 },
    [85] = { 0x000001CC, 0x0015, 44 },
    [86] = { 0x000001DC, 0x0018, 43 },
    [87] = { 0x000001E0, 0x001A, 49 },
    [88] = { 0x000001E3, 0x0015, 44 },
    [89] = { 0x000001E7, 0x0014, 22 },
    [90] = { 0x000001F1, 0x001C, 26 },
    [91] = { 0x000001F3, 0x0026, 1 },
    [92] = { 0x000001F7, 0x001A, 42 },
    [93] = { 0x000001FD, 0x0026, 7 },
    [94] = { 0x0000020C, 0x0026, 7 },
    [95] = { 0x0000021B, 0x0026, 9 },
    [96] = { 0x0000022A, 0x0026, 7 },
    [97] = { 0x0000022F, 0x0015, 48 },
    [98] = { 0x00000230, 0x0020, 17 },
    [99] = { 0x00000233, 0x001A, 25 },
    [100] = { 0x00000235, 0x001E, 48 },
    [101] = { 0x00000242, 0x000F, 42 },
    [102] = { 0x0000024B, 0x0010, 45 },
    [103] = { 0x00000251, 0x0011, 45 },
    [104] = { 0x00000259, 0x000F, 43 },
    [105] = { 0x0000025E, 0x0015, 45 },
    [106] = { 0x0000025E, 0x001F, 48 },
    [107] = { 0x00000265, 0x001F, 48 },
    [108] = { 0x00000271, 0x000E, 4 },
    [109] = { 0x00000272, 0x000E, 16 },
    [110] = { 0x0000027C, 0x0014, 44 },
    [111] = { 0x00000287, 0x0021, 43 },
    [112] = { 0x00000289, 0x0011, 44 },
    [113] = { 0x0000028D, 0x001F, 49 },
    [114] = { 0x000002A6, 0x0010, 26 },
    [115] = { 0x000002B1, 0x0012, 5 },
    [116] = { 0x000002C0, 0x0012, 5 },
    [117] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
