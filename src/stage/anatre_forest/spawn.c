#include "spawn.h"

#include "global.h"

// 0x08349824
const struct SpawnTemplate gAnatreForestEntity[34] =
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
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MELLNET, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [11] =
            {
                .flag = SF_NO_CULLING,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SEIMERAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GENERATOR_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TILE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [19] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, ITEM_SUBTANK2, 2),
            },
        [20] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 2, 2),
            },
        [21] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 40, 2),
            },
        [22] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 63, 2),
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 71, 2),
            },
        [24] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 108, 2),
            },
        [25] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 119, 2),
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 14),
            },
        [27] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 76, 2),
            },
        [28] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 254),
            },
        [29] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 255),
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TILE_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [33] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

const struct PreloadEntity gAnatreForestStatic[16] = {
    {
        32,
        3,
        512,
        4,
        3,
        3,
        0,
    },
    {
        71,
        1,
        574,
        5,
        1,
        3,
        0,
    },
    {
        119,
        1,
        606,
        6,
        1,
        3,
        0,
    },
    {
        113,
        1,
        669,
        7,
        1,
        1,
        0,
    },
    {
        114,
        1,
        716,
        8,
        1,
        1,
        0,
    },
    {
        61,
        1,
        669,
        13,
        1,
        2,
        0,
    },
    {
        62,
        1,
        698,
        7,
        1,
        2,
        0,
    },
    {
        47,
        2,
        574,
        5,
        1,
        3,
        1,
    },
    {
        6,
        2,
        654,
        6,
        1,
        1,
        0,
    },
    {
        126,
        2,
        751,
        7,
        1,
        3,
        0,
    },
    {
        229,
        2,
        831,
        8,
        3,
        3,
        0,
    },
    {
        112,
        130,
        973,
        9,
        3,
        3,
        1,
    },
    {
        61,
        2,
        911,
        13,
        1,
        2,
        0,
    },
    {
        63,
        2,
        654,
        6,
        1,
        2,
        0,
    },
    {
        221,
        127,
        574,
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
const struct SpawnPoint gAnatreForestEntityCoord[56] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x0000001A, 0x0017, 22 },
    [2] = { 0x00000023, 0x0018, 4 },
    [3] = { 0x00000023, 0x0020, 10 },
    [4] = { 0x00000028, 0x0023, 11 },
    [5] = { 0x0000002E, 0x001D, 10 },
    [6] = { 0x00000033, 0x0017, 10 },
    [7] = { 0x00000037, 0x0023, 11 },
    [8] = { 0x0000003A, 0x0023, 30 },
    [9] = { 0x00000046, 0x0022, 12 },
    [10] = { 0x0000004E, 0x0016, 1 },
    [11] = { 0x0000004F, 0x0024, 11 },
    [12] = { 0x00000064, 0x0018, 10 },
    [13] = { 0x00000066, 0x0016, 10 },
    [14] = { 0x00000068, 0x001B, 10 },
    [15] = { 0x0000006E, 0x0020, 28 },
    [16] = { 0x00000070, 0x0016, 10 },
    [17] = { 0x00000084, 0x0024, 12 },
    [18] = { 0x0000008E, 0x0019, 20 },
    [19] = { 0x00000095, 0x0024, 7 },
    [20] = { 0x000000A4, 0x0024, 7 },
    [21] = { 0x000000B0, 0x0023, 30 },
    [22] = { 0x000000BE, 0x001F, 32 },
    [23] = { 0x000000DB, 0x0023, 15 },
    [24] = { 0x000000ED, 0x0023, 23 },
    [25] = { 0x000000F4, 0x0017, 14 },
    [26] = { 0x000000F4, 0x0021, 13 },
    [27] = { 0x000000FD, 0x0019, 13 },
    [28] = { 0x00000103, 0x0021, 32 },
    [29] = { 0x00000106, 0x0017, 32 },
    [30] = { 0x00000117, 0x001B, 14 },
    [31] = { 0x0000012D, 0x001D, 13 },
    [32] = { 0x00000131, 0x0019, 13 },
    [33] = { 0x00000139, 0x0019, 26 },
    [34] = { 0x00000146, 0x0024, 25 },
    [35] = { 0x00000148, 0x0017, 1 },
    [36] = { 0x0000014B, 0x0020, 32 },
    [37] = { 0x00000151, 0x0024, 28 },
    [38] = { 0x00000155, 0x001B, 16 },
    [39] = { 0x00000169, 0x001F, 13 },
    [40] = { 0x00000171, 0x0010, 19 },
    [41] = { 0x00000173, 0x0010, 18 },
    [42] = { 0x00000181, 0x0024, 24 },
    [43] = { 0x00000183, 0x0017, 13 },
    [44] = { 0x00000187, 0x000D, 27 },
    [45] = { 0x00000198, 0x0018, 13 },
    [46] = { 0x000001A4, 0x0016, 31 },
    [47] = { 0x000001A5, 0x0016, 18 },
    [48] = { 0x000001AE, 0x0010, 13 },
    [49] = { 0x000001B1, 0x000E, 13 },
    [50] = { 0x000001B4, 0x000C, 13 },
    [51] = { 0x000001BB, 0x001B, 1 },
    [52] = { 0x000001BC, 0x001B, 21 },
    [53] = { 0x000001C1, 0x0012, 5 },
    [54] = { 0x000001D0, 0x0012, 5 },
    [55] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
