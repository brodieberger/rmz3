#include "spawn.h"

#include "global.h"

// 0x0834aa9c
const struct SpawnTemplate gSnowyPlainsEntity[27] =
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
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 25, 2),
            },
        [8] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 29, 2),
            },
        [9] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 86, 2),
            },
        [10] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 2, 3),
            },
        [11] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 2, 103),
            },
        [12] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 2, 123),
            },
        [13] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 2, 254),
            },
        [14] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 2, 255),
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_044, 0, 0),
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_SNOWBOARD, 0, 0),
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_SNOWBOARD, 1, 0),
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHRIMPORIN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHRIMPORIN, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GYRO_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHELLCRAWLER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GENERATOR_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [23] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MELLNET, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [26] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

const struct PreloadEntity gSnowyPlainsStatic[13] = {
    {
        109,
        3,
        512,
        4,
        3,
        3,
        0,
    },
    {
        13,
        3,
        607,
        5,
        1,
        3,
        0,
    },
    {
        61,
        3,
        995,
        13,
        1,
        2,
        0,
    },
    {
        157,
        1,
        735,
        6,
        3,
        3,
        1,
    },
    {
        219,
        1,
        767,
        7,
        1,
        3,
        0,
    },
    {
        23,
        1,
        894,
        8,
        1,
        1,
        0,
    },
    {
        63,
        1,
        894,
        8,
        1,
        2,
        0,
    },
    {
        71,
        2,
        735,
        6,
        1,
        3,
        0,
    },
    {
        113,
        2,
        767,
        7,
        1,
        1,
        0,
    },
    {
        114,
        2,
        814,
        8,
        1,
        1,
        0,
    },
    {
        62,
        2,
        767,
        7,
        1,
        2,
        0,
    },
    {
        221,
        127,
        607,
        5,
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
const struct SpawnPoint gSnowyPlainsEntityCoord[78] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x0000003A, 0x0016, 18 },
    [2] = { 0x0000003D, 0x0015, 24 },
    [3] = { 0x00000043, 0x0016, 19 },
    [4] = { 0x00000055, 0x0010, 20 },
    [5] = { 0x00000068, 0x0015, 18 },
    [6] = { 0x00000076, 0x0014, 16 },
    [7] = { 0x0000008E, 0x001E, 17 },
    [8] = { 0x00000091, 0x0022, 18 },
    [9] = { 0x000000A4, 0x002A, 18 },
    [10] = { 0x000000BD, 0x0020, 20 },
    [11] = { 0x000000C7, 0x0025, 21 },
    [12] = { 0x000000D5, 0x0025, 16 },
    [13] = { 0x000000E3, 0x002B, 20 },
    [14] = { 0x000000F2, 0x0034, 13 },
    [15] = { 0x00000100, 0x0039, 21 },
    [16] = { 0x00000118, 0x0046, 10 },
    [17] = { 0x00000120, 0x0044, 16 },
    [18] = { 0x0000012D, 0x004B, 18 },
    [19] = { 0x00000146, 0x0042, 20 },
    [20] = { 0x00000151, 0x0049, 17 },
    [21] = { 0x0000015C, 0x004B, 8 },
    [22] = { 0x00000164, 0x0055, 13 },
    [23] = { 0x0000016D, 0x004E, 20 },
    [24] = { 0x00000174, 0x004D, 17 },
    [25] = { 0x0000018B, 0x005F, 15 },
    [26] = { 0x0000018D, 0x005F, 15 },
    [27] = { 0x0000018F, 0x005F, 15 },
    [28] = { 0x00000191, 0x005F, 15 },
    [29] = { 0x00000193, 0x005F, 15 },
    [30] = { 0x00000195, 0x005F, 15 },
    [31] = { 0x00000199, 0x005A, 20 },
    [32] = { 0x0000019C, 0x0054, 7 },
    [33] = { 0x000001A0, 0x0061, 18 },
    [34] = { 0x000001A6, 0x006A, 11 },
    [35] = { 0x000001A9, 0x0064, 15 },
    [36] = { 0x000001AB, 0x0060, 20 },
    [37] = { 0x000001AB, 0x0064, 15 },
    [38] = { 0x000001AD, 0x0064, 15 },
    [39] = { 0x000001B7, 0x0066, 15 },
    [40] = { 0x000001B9, 0x0066, 15 },
    [41] = { 0x000001C2, 0x0067, 15 },
    [42] = { 0x000001C4, 0x0067, 15 },
    [43] = { 0x000001CE, 0x0065, 21 },
    [44] = { 0x000001D6, 0x0063, 20 },
    [45] = { 0x000001DD, 0x0061, 25 },
    [46] = { 0x000001E3, 0x005C, 20 },
    [47] = { 0x000001E8, 0x005E, 20 },
    [48] = { 0x00000227, 0x005F, 24 },
    [49] = { 0x00000230, 0x0063, 18 },
    [50] = { 0x0000023D, 0x006B, 4 },
    [51] = { 0x00000255, 0x006A, 12 },
    [52] = { 0x00000260, 0x0065, 16 },
    [53] = { 0x00000269, 0x0067, 23 },
    [54] = { 0x0000026F, 0x0069, 23 },
    [55] = { 0x0000027C, 0x006D, 23 },
    [56] = { 0x00000287, 0x006F, 23 },
    [57] = { 0x0000028C, 0x0071, 13 },
    [58] = { 0x00000294, 0x006F, 23 },
    [59] = { 0x0000029E, 0x0072, 23 },
    [60] = { 0x000002A6, 0x007B, 13 },
    [61] = { 0x000002AB, 0x0075, 22 },
    [62] = { 0x000002BC, 0x0078, 23 },
    [63] = { 0x000002C1, 0x0077, 9 },
    [64] = { 0x000002CA, 0x0076, 23 },
    [65] = { 0x000002D1, 0x007B, 23 },
    [66] = { 0x000002D8, 0x007D, 23 },
    [67] = { 0x000002DB, 0x007F, 23 },
    [68] = { 0x000002DE, 0x0080, 23 },
    [69] = { 0x000002E2, 0x0087, 22 },
    [70] = { 0x000002F8, 0x008A, 23 },
    [71] = { 0x000002FF, 0x008E, 23 },
    [72] = { 0x00000300, 0x0090, 13 },
    [73] = { 0x0000030F, 0x0091, 22 },
    [74] = { 0x0000031C, 0x0094, 25 },
    [75] = { 0x00000338, 0x0094, 5 },
    [76] = { 0x00000347, 0x0094, 5 },
    [77] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
