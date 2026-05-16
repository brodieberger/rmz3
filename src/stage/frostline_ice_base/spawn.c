#include "spawn.h"

#include "global.h"

// 0x08349b74
const struct SpawnTemplate gIceBaseEntity[38] =
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_H, 1, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHARKSEAL_X, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 3,
                .virusID = VIRUS_PUFFY,
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_AQUA, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 3,
                .virusID = VIRUS_PUFFY,
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GRAND_CANNON, GRAND_CANNON_TURRET, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GYRO_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CLAVEKER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_63, 0, 0),
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_63, 1, 0),
            },
        [23] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_63, 2, 0),
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_63, 3, 0),
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_GLACIERLE_ARM, 1, 0),
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 32, 2),
            },
        [27] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 35, 2),
            },
        [28] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 66, 2),
            },
        [29] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 68, 2),
            },
        [30] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 109, 2),
            },
        [31] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 15),
            },
        [32] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 120),
            },
        [33] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [34] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [35] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [36] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [37] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

const struct PreloadEntity gIceBaseStatic[18] = {
    {
        24,
        1,
        512,
        4,
        1,
        1,
        0,
    },
    {
        23,
        1,
        602,
        8,
        1,
        1,
        0,
    },
    {
        19,
        3,
        697,
        5,
        1,
        1,
        0,
    },
    {
        7,
        3,
        817,
        6,
        1,
        1,
        0,
    },
    {
        39,
        3,
        858,
        7,
        1,
        1,
        0,
    },
    {
        88,
        2,
        512,
        9,
        3,
        3,
        0,
    },
    {
        200,
        2,
        564,
        9,
        3,
        3,
        0,
    },
    {
        56,
        4,
        512,
        4,
        1,
        1,
        0,
    },
    {
        20,
        4,
        574,
        5,
        1,
        1,
        0,
    },
    {
        117,
        4,
        945,
        8,
        1,
        3,
        0,
    },
    {
        90,
        4,
        988,
        9,
        3,
        3,
        0,
    },
    {
        61,
        127,
        604,
        13,
        1,
        2,
        0,
    },
    {
        62,
        127,
        633,
        4,
        1,
        2,
        0,
    },
    {
        63,
        127,
        733,
        5,
        1,
        2,
        0,
    },
    {
        65,
        127,
        809,
        6,
        1,
        2,
        0,
    },
    {
        66,
        127,
        839,
        7,
        1,
        2,
        0,
    },
    {
        221,
        127,
        604,
        4,
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
const struct SpawnPoint gIceBaseEntityCoord[107] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x00000026, 0x002F, 35 },
    [2] = { 0x00000033, 0x002F, 13 },
    [3] = { 0x00000035, 0x002F, 13 },
    [4] = { 0x0000003A, 0x002F, 13 },
    [5] = { 0x00000051, 0x0038, 12 },
    [6] = { 0x00000065, 0x0037, 12 },
    [7] = { 0x0000006D, 0x003A, 12 },
    [8] = { 0x00000070, 0x002F, 13 },
    [9] = { 0x0000007D, 0x002F, 13 },
    [10] = { 0x0000007F, 0x0039, 11 },
    [11] = { 0x00000081, 0x003C, 11 },
    [12] = { 0x00000082, 0x0035, 11 },
    [13] = { 0x00000083, 0x0026, 28 },
    [14] = { 0x00000086, 0x0026, 13 },
    [15] = { 0x0000008C, 0x0037, 11 },
    [16] = { 0x0000008C, 0x003C, 11 },
    [17] = { 0x00000094, 0x002A, 15 },
    [18] = { 0x0000009C, 0x0039, 11 },
    [19] = { 0x0000009C, 0x003E, 11 },
    [20] = { 0x000000A1, 0x0026, 1 },
    [21] = { 0x000000A4, 0x0026, 13 },
    [22] = { 0x000000AC, 0x0029, 15 },
    [23] = { 0x000000B4, 0x002C, 15 },
    [24] = { 0x000000B6, 0x0040, 12 },
    [25] = { 0x000000BA, 0x003B, 3 },
    [26] = { 0x000000BB, 0x003B, 3 },
    [27] = { 0x000000BF, 0x0029, 15 },
    [28] = { 0x000000C1, 0x0042, 11 },
    [29] = { 0x000000C8, 0x002C, 15 },
    [30] = { 0x000000C8, 0x003F, 11 },
    [31] = { 0x000000D1, 0x002F, 7 },
    [32] = { 0x000000D3, 0x0042, 11 },
    [33] = { 0x000000DE, 0x003F, 12 },
    [34] = { 0x000000E0, 0x002F, 7 },
    [35] = { 0x000000E6, 0x0022, 30 },
    [36] = { 0x000000E6, 0x0041, 12 },
    [37] = { 0x000000E9, 0x0025, 22 },
    [38] = { 0x000000EE, 0x002B, 14 },
    [39] = { 0x000000EF, 0x0040, 12 },
    [40] = { 0x000000F5, 0x002C, 23 },
    [41] = { 0x000000FA, 0x002C, 23 },
    [42] = { 0x000000FB, 0x0041, 12 },
    [43] = { 0x00000101, 0x002C, 23 },
    [44] = { 0x00000106, 0x0027, 24 },
    [45] = { 0x00000106, 0x0043, 12 },
    [46] = { 0x00000107, 0x002C, 14 },
    [47] = { 0x0000010A, 0x002C, 31 },
    [48] = { 0x0000010E, 0x0027, 24 },
    [49] = { 0x00000114, 0x002B, 23 },
    [50] = { 0x0000011B, 0x0027, 24 },
    [51] = { 0x0000011C, 0x0042, 7 },
    [52] = { 0x00000127, 0x002E, 14 },
    [53] = { 0x00000132, 0x0030, 13 },
    [54] = { 0x00000134, 0x0030, 13 },
    [55] = { 0x00000135, 0x003B, 10 },
    [56] = { 0x0000013C, 0x0036, 12 },
    [57] = { 0x00000140, 0x0038, 12 },
    [58] = { 0x00000144, 0x003A, 12 },
    [59] = { 0x00000158, 0x002F, 13 },
    [60] = { 0x0000015A, 0x002F, 13 },
    [61] = { 0x0000015C, 0x002F, 13 },
    [62] = { 0x00000166, 0x002C, 26 },
    [63] = { 0x00000167, 0x0039, 7 },
    [64] = { 0x00000176, 0x0039, 7 },
    [65] = { 0x00000187, 0x0022, 27 },
    [66] = { 0x00000188, 0x0022, 3 },
    [67] = { 0x00000188, 0x0030, 20 },
    [68] = { 0x00000189, 0x0033, 25 },
    [69] = { 0x0000018B, 0x0020, 25 },
    [70] = { 0x0000018B, 0x0029, 25 },
    [71] = { 0x0000018C, 0x0039, 16 },
    [72] = { 0x0000018D, 0x0030, 35 },
    [73] = { 0x0000018F, 0x0033, 25 },
    [74] = { 0x00000190, 0x0029, 25 },
    [75] = { 0x00000192, 0x0020, 25 },
    [76] = { 0x00000199, 0x0020, 25 },
    [77] = { 0x0000019D, 0x0024, 17 },
    [78] = { 0x000001A0, 0x0020, 25 },
    [79] = { 0x000001A7, 0x0020, 25 },
    [80] = { 0x000001AF, 0x0020, 25 },
    [81] = { 0x000001B6, 0x0020, 25 },
    [82] = { 0x000001BD, 0x0020, 25 },
    [83] = { 0x000001C4, 0x0020, 25 },
    [84] = { 0x000001C6, 0x002C, 25 },
    [85] = { 0x000001C9, 0x0030, 20 },
    [86] = { 0x000001CA, 0x0020, 19 },
    [87] = { 0x000001CA, 0x003A, 20 },
    [88] = { 0x000001CB, 0x002C, 25 },
    [89] = { 0x000001CB, 0x0030, 20 },
    [90] = { 0x000001CE, 0x0025, 20 },
    [91] = { 0x000001D1, 0x003A, 20 },
    [92] = { 0x000001DB, 0x0033, 19 },
    [93] = { 0x000001E8, 0x003A, 32 },
    [94] = { 0x000001EB, 0x0037, 17 },
    [95] = { 0x000001F1, 0x0025, 20 },
    [96] = { 0x000001F6, 0x0025, 20 },
    [97] = { 0x000001F9, 0x0025, 20 },
    [98] = { 0x000001FC, 0x0037, 16 },
    [99] = { 0x000001FD, 0x001B, 5 },
    [100] = { 0x000001FF, 0x0030, 29 },
    [101] = { 0x00000200, 0x0039, 36 },
    [102] = { 0x00000202, 0x0030, 20 },
    [103] = { 0x00000204, 0x001F, 19 },
    [104] = { 0x0000020A, 0x0039, 20 },
    [105] = { 0x0000020C, 0x001B, 5 },
    [106] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
