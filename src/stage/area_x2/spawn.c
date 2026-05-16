#include "spawn.h"

#include "global.h"

// 0x0834a08c
const struct SpawnTemplate gAreaX2Entity[36] =
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_H, 1, 0),
            },
        [7] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_025, 0, 0),
            },
        [8] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_025, 1, 0),
            },
        [9] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_025, 2, 0),
            },
        [10] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_UNK_025, 3, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GALLISNI, 0, 0),
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [13] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CLAVEKER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_FLOPPER, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [21] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 61, 2),
            },
        [22] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 62, 2),
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 69, 2),
            },
        [24] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 70, 2),
            },
        [25] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 77, 2),
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 110, 2),
            },
        [27] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 34),
            },
        [28] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 42),
            },
        [29] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 121),
            },
        [30] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [31] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 1, 0),
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

const struct PreloadEntity gAreaX2Static[13] = {
    {
        124,
        3,
        512,
        4,
        3,
        3,
        1,
    },
    {
        103,
        1,
        547,
        5,
        3,
        3,
        0,
    },
    {
        19,
        1,
        680,
        6,
        1,
        1,
        0,
    },
    {
        102,
        1,
        800,
        7,
        3,
        3,
        0,
    },
    {
        61,
        1,
        848,
        13,
        1,
        2,
        0,
    },
    {
        62,
        1,
        680,
        6,
        1,
        2,
        0,
    },
    {
        117,
        2,
        547,
        5,
        1,
        3,
        0,
    },
    {
        104,
        2,
        590,
        6,
        1,
        3,
        0,
    },
    {
        22,
        2,
        632,
        7,
        1,
        1,
        0,
    },
    {
        61,
        2,
        632,
        13,
        1,
        2,
        0,
    },
    {
        63,
        2,
        661,
        7,
        1,
        2,
        0,
    },
    {
        221,
        127,
        680,
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
const struct SpawnPoint gAreaX2EntityCoord[88] = {
  [0] = { -0x80000000, -0x8000, 0 },
  [1] = { 0x0000002C, 0x009E, 12 },
  [2] = { 0x00000034, 0x0097, 13 },
  [3] = { 0x0000003D, 0x009C, 12 },
  [4] = { 0x00000043, 0x009A, 34 },
  [5] = { 0x00000045, 0x009A, 32 },
  [6] = { 0x00000049, 0x0093, 13 },
  [7] = { 0x0000004F, 0x009C, 12 },
  [8] = { 0x0000005B, 0x0096, 13 },
  [9] = { 0x0000005E, 0x00A7, 29 },
  [10] = { 0x00000060, 0x0099, 26 },
  [11] = { 0x00000061, 0x0099, 1 },
  [12] = { 0x00000062, 0x009F, 13 },
  [13] = { 0x00000066, 0x00A2, 7 },
  [14] = { 0x0000006C, 0x00A2, 8 },
  [15] = { 0x00000072, 0x00A2, 9 },
  [16] = { 0x00000078, 0x00A2, 10 },
  [17] = { 0x00000079, 0x00A0, 34 },
  [18] = { 0x0000007D, 0x009B, 22 },
  [19] = { 0x0000007E, 0x00A2, 7 },
  [20] = { 0x00000086, 0x00A6, 12 },
  [21] = { 0x0000008A, 0x00A6, 11 },
  [22] = { 0x00000095, 0x00A8, 11 },
  [23] = { 0x0000009E, 0x00A2, 13 },
  [24] = { 0x000000A4, 0x00A5, 11 },
  [25] = { 0x000000B3, 0x00A7, 11 },
  [26] = { 0x000000BA, 0x00A7, 11 },
  [27] = { 0x000000C1, 0x00A1, 13 },
  [28] = { 0x000000C7, 0x00A4, 11 },
  [29] = { 0x000000D2, 0x00A8, 11 },
  [30] = { 0x000000D3, 0x0017, 21 },
  [31] = { 0x000000D3, 0x001E, 7 },
  [32] = { 0x000000D3, 0x0026, 23 },
  [33] = { 0x000000D3, 0x009F, 2 },
  [34] = { 0x000000D4, 0x009F, 12 },
  [35] = { 0x000000D6, 0x0020, 9 },
  [36] = { 0x000000D8, 0x0092, 27 },
  [37] = { 0x000000D8, 0x0099, 11 },
  [38] = { 0x000000D8, 0x009F, 11 },
  [39] = { 0x000000D9, 0x001E, 7 },
  [40] = { 0x000000DC, 0x0020, 9 },
  [41] = { 0x000000DC, 0x008D, 13 },
  [42] = { 0x000000DD, 0x00A8, 12 },
  [43] = { 0x000000DE, 0x00A0, 13 },
  [44] = { 0x000000DF, 0x001E, 7 },
  [45] = { 0x000000E2, 0x0092, 11 },
  [46] = { 0x000000E4, 0x0023, 17 },
  [47] = { 0x000000E9, 0x0090, 12 },
  [48] = { 0x000000EA, 0x001F, 14 },
  [49] = { 0x000000ED, 0x0090, 11 },
  [50] = { 0x000000EF, 0x001C, 5 },
  [51] = { 0x000000F1, 0x0023, 17 },
  [52] = { 0x000000F1, 0x005E, 15 },
  [53] = { 0x000000F1, 0x0062, 1 },
  [54] = { 0x000000F2, 0x003C, 7 },
  [55] = { 0x000000F2, 0x0062, 32 },
  [56] = { 0x000000F2, 0x007B, 28 },
  [57] = { 0x000000F3, 0x004B, 15 },
  [58] = { 0x000000F3, 0x004E, 2 },
  [59] = { 0x000000F3, 0x0062, 24 },
  [60] = { 0x000000F4, 0x0074, 8 },
  [61] = { 0x000000F5, 0x004E, 25 },
  [62] = { 0x000000F6, 0x0032, 8 },
  [63] = { 0x000000F6, 0x003B, 16 },
  [64] = { 0x000000F6, 0x005B, 8 },
  [65] = { 0x000000F6, 0x0069, 10 },
  [66] = { 0x000000F7, 0x0022, 33 },
  [67] = { 0x000000F8, 0x0078, 10 },
  [68] = { 0x000000F8, 0x0093, 12 },
  [69] = { 0x000000F9, 0x0051, 9 },
  [70] = { 0x000000F9, 0x0081, 6 },
  [71] = { 0x000000F9, 0x008B, 6 },
  [72] = { 0x000000FA, 0x002C, 18 },
  [73] = { 0x000000FA, 0x0032, 16 },
  [74] = { 0x000000FA, 0x0061, 7 },
  [75] = { 0x000000FA, 0x006F, 9 },
  [76] = { 0x000000FA, 0x0093, 30 },
  [77] = { 0x000000FD, 0x0021, 16 },
  [78] = { 0x000000FE, 0x001C, 5 },
  [79] = { 0x000000FF, 0x004D, 10 },
  [80] = { 0x00000106, 0x004E, 7 },
  [81] = { 0x0000010A, 0x003D, 14 },
  [82] = { 0x0000010D, 0x004B, 8 },
  [83] = { 0x0000010E, 0x0040, 17 },
  [84] = { 0x00000114, 0x004B, 9 },
  [85] = { 0x0000011A, 0x0047, 10 },
  [86] = { 0x0000011B, 0x0040, 16 },
  [87] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
