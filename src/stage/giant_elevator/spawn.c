#include "spawn.h"

#include "global.h"

// 0x0834b2ec
const struct SpawnTemplate gGiantElevatorEntity[41] =
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
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 41, 2),
            },
        [11] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 45, 2),
            },
        [12] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 54, 2),
            },
        [13] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 27),
            },
        [14] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 80),
            },
        [15] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 122),
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_043, 0, 0),
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [23] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
            },
        [27] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [28] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [29] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [35] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [36] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_BATRING, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [37] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_GE_PIER, 0, 0),
            },
        [38] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [39] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [40] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },

};

const struct PreloadEntity gGiantElevatorStatic[19] = {
    {
        156,
        3,
        512,
        4,
        3,
        3,
        1,
    },
    {
        4,
        3,
        524,
        5,
        1,
        1,
        0,
    },
    {
        20,
        3,
        580,
        6,
        1,
        1,
        0,
    },
    {
        22,
        3,
        734,
        7,
        1,
        1,
        0,
    },
    {
        102,
        3,
        750,
        8,
        3,
        3,
        0,
    },
    {
        61,
        63,
        524,
        13,
        1,
        2,
        0,
    },
    {
        62,
        63,
        553,
        5,
        1,
        2,
        0,
    },
    {
        63,
        63,
        653,
        6,
        1,
        2,
        0,
    },
    {
        6,
        1,
        798,
        9,
        1,
        1,
        0,
    },
    {
        21,
        2,
        798,
        9,
        1,
        3,
        0,
    },
    {
        154,
        64,
        512,
        5,
        3,
        3,
        1,
    },
    {
        155,
        0,
        536,
        5,
        3,
        3,
        1,
    },
    {
        213,
        64,
        568,
        6,
        3,
        3,
        0,
    },
    {
        142,
        64,
        643,
        7,
        3,
        3,
        0,
    },
    {
        212,
        64,
        685,
        8,
        3,
        3,
        0,
    },
    {
        214,
        0,
        817,
        9,
        3,
        3,
        0,
    },
    {
        215,
        0,
        982,
        4,
        3,
        3,
        0,
    },
    {
        221,
        63,
        580,
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
const struct SpawnPoint gGiantElevatorEntityCoord[65] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x00000011, 0x0016, 11 },
    [2] = { 0x00000021, 0x0017, 10 },
    [3] = { 0x00000023, 0x001A, 35 },
    [4] = { 0x00000026, 0x0024, 21 },
    [5] = { 0x00000031, 0x0023, 21 },
    [6] = { 0x00000038, 0x001B, 26 },
    [7] = { 0x00000038, 0x0023, 21 },
    [8] = { 0x0000003E, 0x0017, 19 },
    [9] = { 0x0000003E, 0x0023, 38 },
    [10] = { 0x0000003F, 0x001B, 26 },
    [11] = { 0x00000048, 0x0019, 4 },
    [12] = { 0x0000004E, 0x001D, 20 },
    [13] = { 0x00000054, 0x0020, 19 },
    [14] = { 0x0000005E, 0x001D, 26 },
    [15] = { 0x00000061, 0x001B, 21 },
    [16] = { 0x00000065, 0x0022, 16 },
    [17] = { 0x00000068, 0x001B, 21 },
    [18] = { 0x0000006C, 0x001D, 26 },
    [19] = { 0x0000007D, 0x0023, 16 },
    [20] = { 0x0000008A, 0x001B, 21 },
    [21] = { 0x0000008E, 0x001B, 21 },
    [22] = { 0x0000008F, 0x0016, 14 },
    [23] = { 0x0000009F, 0x0024, 21 },
    [24] = { 0x000000A5, 0x0024, 21 },
    [25] = { 0x000000A8, 0x0024, 17 },
    [26] = { 0x000000A8, 0x0075, 16 },
    [27] = { 0x000000AB, 0x0075, 16 },
    [28] = { 0x000000AE, 0x0018, 19 },
    [29] = { 0x000000AE, 0x0075, 13 },
    [30] = { 0x000000B4, 0x0073, 18 },
    [31] = { 0x000000B6, 0x0053, 16 },
    [32] = { 0x000000B9, 0x0059, 21 },
    [33] = { 0x000000BA, 0x0023, 21 },
    [34] = { 0x000000BA, 0x0041, 22 },
    [35] = { 0x000000BA, 0x0062, 21 },
    [36] = { 0x000000BB, 0x004B, 22 },
    [37] = { 0x000000BC, 0x0037, 22 },
    [38] = { 0x000000BC, 0x006F, 26 },
    [39] = { 0x000000BE, 0x0017, 3 },
    [40] = { 0x000000BE, 0x004C, 22 },
    [41] = { 0x000000BE, 0x0064, 22 },
    [42] = { 0x000000C0, 0x0017, 12 },
    [43] = { 0x000000C0, 0x0049, 15 },
    [44] = { 0x000000C0, 0x005D, 3 },
    [45] = { 0x000000C2, 0x0075, 7 },
    [46] = { 0x000000D1, 0x0075, 7 },
    [47] = { 0x000000DD, 0x0074, 39 },
    [48] = { 0x000000E5, 0x0075, 37 },
    [49] = { 0x000000FE, 0x0074, 7 },
    [50] = { 0x0000010D, 0x0074, 7 },
    [51] = { 0x0000011F, 0x00B7, 1 },
    [52] = { 0x00000120, 0x0074, 21 },
    [53] = { 0x00000121, 0x007F, 23 },
    [54] = { 0x00000121, 0x00A5, 22 },
    [55] = { 0x00000124, 0x00A5, 22 },
    [56] = { 0x00000125, 0x0074, 21 },
    [57] = { 0x00000125, 0x0097, 26 },
    [58] = { 0x00000125, 0x00BF, 26 },
    [59] = { 0x00000127, 0x0089, 23 },
    [60] = { 0x00000128, 0x00AB, 26 },
    [61] = { 0x00000128, 0x00BB, 21 },
    [62] = { 0x0000012B, 0x00C5, 5 },
    [63] = { 0x0000013A, 0x00C6, 5 },
    [64] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
