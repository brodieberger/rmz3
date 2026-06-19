#include "spawn.h"

#include "global.h"

// 0x083490d4
const struct SpawnTemplate gMissileFactoryEntity[35] =
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
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 30, 2),
            },
        [11] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 55, 2),
            },
        [12] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 57, 2),
            },
        [13] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 90, 2),
            },
        [14] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 21),
            },
        [15] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 117),
            },
        [16] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [17] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_MISSILE, 0, 0),
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GENERATOR_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PURPLE_NERPLE, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_SWORDY,
            },
        [26] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [27] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [28] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [29] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [34] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },

};

const struct PreloadEntity gMissileFactoryStatic[14] = {
    {
        151,
        1,
        512,
        4,
        3,
        3,
        1,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        1,
        529,
        5,
        1,
        1,
        0,
    },
    {
        113,
        1,
        683,
        6,
        1,
        1,
        0,
    },
    {
        114,
        1,
        730,
        7,
        1,
        1,
        0,
    },
    {
        SM056_HEAVY_CANNON,
        1,
        781,
        8,
        1,
        1,
        0,
    },
    {
        102,
        1,
        843,
        9,
        3,
        3,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        2,
        512,
        4,
        1,
        1,
        0,
    },
    {
        SM042_PURPLE_NERPLE,
        2,
        632,
        5,
        3,
        1,
        0,
    },
    {
        SM004_SHOTCOUNTER,
        2,
        664,
        6,
        1,
        1,
        0,
    },
    {
        61,
        127,
        529,
        13,
        1,
        2,
        0,
    },
    {
        62,
        127,
        558,
        5,
        1,
        2,
        0,
    },
    {
        63,
        127,
        658,
        6,
        1,
        2,
        0,
    },
    {
        221,
        127,
        529,
        6,
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
const struct SpawnPoint gMissileFactoryEntityCoord[82] = {
    [0] =  { -0x80000000, -0x8000, 0 },
    [1] =  { 0x00000010, 0x0073, 12 },
    [2] =  { 0x00000012, 0x006F, 23 },
    [3] =  { 0x00000019, 0x006F, 23 },
    [4] =  { 0x0000001C, 0x0074, 19 },
    [5] =  { 0x0000001F, 0x005D, 10 },
    [6] =  { 0x00000020, 0x005D, 28 },
    [7] =  { 0x00000022, 0x005D, 19 },
    [8] =  { 0x00000024, 0x0065, 23 },
    [9] =  { 0x00000025, 0x0076, 20 },
    [10] = { 0x00000026, 0x006D, 19 },
    [11] = { 0x0000002A, 0x005B, 23 },
    [12] = { 0x0000002C, 0x0079, 23 },
    [13] = { 0x00000031, 0x0062, 19 },
    [14] = { 0x00000033, 0x007D, 19 },
    [15] = { 0x00000035, 0x007D, 19 },
    [16] = { 0x00000038, 0x0060, 20 },
    [17] = { 0x00000038, 0x006F, 23 },
    [18] = { 0x0000003F, 0x005B, 23 },
    [19] = { 0x00000047, 0x0062, 20 },
    [20] = { 0x0000004E, 0x0025, 14 },
    [21] = { 0x0000004E, 0x0039, 19 },
    [22] = { 0x0000004E, 0x0049, 11 },
    [23] = { 0x00000050, 0x0039, 3 },
    [24] = { 0x00000051, 0x0039, 3 },
    [25] = { 0x00000052, 0x0060, 19 },
    [26] = { 0x00000053, 0x0036, 19 },
    [27] = { 0x00000053, 0x004B, 19 },
    [28] = { 0x00000054, 0x0022, 19 },
    [29] = { 0x00000055, 0x002D, 19 },
    [30] = { 0x00000057, 0x0034, 30 },
    [31] = { 0x00000057, 0x0048, 18 },
    [32] = { 0x00000058, 0x002D, 19 },
    [33] = { 0x0000005E, 0x005B, 23 },
    [34] = { 0x00000060, 0x0020, 23 },
    [35] = { 0x00000061, 0x0044, 15 },
    [36] = { 0x00000064, 0x0041, 30 },
    [37] = { 0x00000066, 0x002A, 20 },
    [38] = { 0x00000066, 0x0030, 23 },
    [39] = { 0x0000006C, 0x0028, 29 },
    [40] = { 0x0000006C, 0x004C, 23 },
    [41] = { 0x0000006D, 0x0049, 13 },
    [42] = { 0x00000070, 0x0056, 33 },
    [43] = { 0x00000074, 0x003C, 18 },
    [44] = { 0x00000074, 0x0055, 18 },
    [45] = { 0x00000077, 0x0026, 7 },
    [46] = { 0x0000010A, 0x0062, 24 },
    [47] = { 0x0000010C, 0x0062, 24 },
    [48] = { 0x00000115, 0x006C, 24 },
    [49] = { 0x00000116, 0x0066, 24 },
    [50] = { 0x00000119, 0x0062, 24 },
    [51] = { 0x0000011B, 0x0062, 24 },
    [52] = { 0x00000122, 0x005B, 25 },
    [53] = { 0x00000122, 0x006F, 27 },
    [54] = { 0x00000124, 0x006C, 26 },
    [55] = { 0x00000129, 0x005B, 25 },
    [56] = { 0x00000131, 0x005B, 25 },
    [57] = { 0x00000131, 0x006F, 27 },
    [58] = { 0x00000132, 0x0066, 24 },
    [59] = { 0x00000132, 0x006C, 24 },
    [60] = { 0x00000135, 0x0062, 24 },
    [61] = { 0x00000137, 0x0062, 24 },
    [62] = { 0x0000013D, 0x0066, 27 },
    [63] = { 0x0000013D, 0x006E, 27 },
    [64] = { 0x00000141, 0x006A, 26 },
    [65] = { 0x0000015E, 0x006B, 24 },
    [66] = { 0x00000161, 0x006B, 24 },
    [67] = { 0x00000162, 0x0065, 27 },
    [68] = { 0x00000162, 0x006F, 27 },
    [69] = { 0x0000016C, 0x0067, 3 },
    [70] = { 0x0000016C, 0x0070, 1 },
    [71] = { 0x0000016D, 0x006B, 24 },
    [72] = { 0x00000170, 0x0070, 24 },
    [73] = { 0x0000017B, 0x0068, 4 },
    [74] = { 0x0000017D, 0x0070, 24 },
    [75] = { 0x00000182, 0x006A, 25 },
    [76] = { 0x00000186, 0x006A, 25 },
    [77] = { 0x00000189, 0x0066, 2 },
    [78] = { 0x0000018A, 0x006A, 25 },
    [79] = { 0x00000194, 0x006B, 5 },
    [80] = { 0x000001A3, 0x006B, 5 },
    [81] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
