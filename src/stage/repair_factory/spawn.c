#include "spawn.h"

#include "global.h"

// 0x0834865c
const struct SpawnTemplate gRepairFactoryEntity[38] =
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
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [8] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [9] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SNAKECORD, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [10] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_HAMMER, 0, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_DEATHLOCK, 0, 0),
                .attr = SA_KNIGHT,
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_DEATHLOCK, 1, 0),
                .attr = SA_KNIGHT,
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_DEATHLOCK, 2, 0),
                .attr = SA_KNIGHT,
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_DEATHLOCK, 3, 0),
                .attr = SA_KNIGHT,
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_DEATHLOCK, 8, 0),
            },
        [16] =
            {
                .flag = SF_NO_CULLING,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LEMMINGLES_NEST, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [17] =
            {
                .flag = SF_NO_CULLING,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LEMMINGLES_NEST, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [18] =
            {
                .flag = SF_NO_CULLING,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LEMMINGLES_NEST, 4, 0),
                .attr = SA_KNIGHT,
            },
        [19] =
            {
                .flag = SF_NO_CULLING,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LEMMINGLES_NEST, 5, 0),
                .attr = SA_KNIGHT,
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 2, 0),
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 0, 0),
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_TOGGLE_SWITCH_RED, 0, 0),
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 84, 2),
            },
        [24] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 100, 2),
            },
        [25] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 104, 2),
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 115, 2),
            },
        [27] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 12),
            },
        [28] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 53),
            },
        [29] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [30] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [33] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 1, 0),
            },
        [34] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 2, 0),
            },
        [35] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 3, 0),
            },
        [36] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 4, 0),
            },
        [37] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

const struct PreloadEntity gRepairFactoryStatic[13] = {
    {
        SM020_PANTHEON_GUARDIAN,
        3,
        512,
        4,
        1,
        1,
        0,
    },
    {
        SM040_SNAKECORD,
        3,
        666,
        5,
        1,
        3,
    },
    {
        SM029_LEMMINGLES,
        3,
        754,
        6,
        1,
        3,
        0,
    },
    {
        SM030_LEMMINGLES_NEST,
        3,
        834,
        7,
        1,
        3,
        0,
    },
    {
        SM061_UNK,
        3,
        512,
        13,
        1,
        2,
        0,
    },
    {
        SM062_BEETANK,
        3,
        541,
        4,
        1,
        2,
        0,
    },
    {
        SM041_HAMMER,
        1,
        855,
        8,
        1,
        3,
        0,
    },
    {
        SM102_EYE_CANNON,
        1,
        872,
        9,
        3,
        3,
        0,
    },
    {
        SM224_RUBBLE,
        1,
        920,
        10,
        1,
        3,
        1,
    },
    {
        SM116_DEATHLOCK,
        2,
        855,
        7,
        3,
        3,
        0,
    },
    {
        SM118_LEVER_SWITCH_RED,
        2,
        950,
        8,
        3,
        3,
        1,
    },
    {
        SM221_METTAUR,
        127,
        512,
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

// 0x083487f4
// clang-format off
const struct SpawnPoint gRepairFactoryEntityCoord[73] = {
	[0]  = { -0x80000000, -0x8000, 0 },
	[1]  = { SpawnPixelCoords(512, 1088), 7 },
	[2]  = { SpawnPixelCoords(560, 816), 33 },
	[3]  = { SpawnPixelCoords(576, 1232), 7 },
	[4]  = { SpawnPixelCoords(624, 1232), 7 },
	[5]  = { SpawnPixelCoords(720, 832), 10 },
	[6]  = { SpawnPixelCoords(720, 1008), 10 },
	[7]  = { SpawnPixelCoords(752, 1168), 34 },
	[8]  = { SpawnPixelCoords(800, 1088), 7 },
	[9]  = { SpawnPixelCoords(944, 1232), 18 },
	[10] = { SpawnPixelCoords(992, 848), 31 },
	[11] = { SpawnPixelCoords(1008, 848), 1 },
	[12] = { SpawnPixelCoords(1056, 816), 35 },
	[13] = { SpawnPixelCoords(1120, 928), 18 },
	[14] = { SpawnPixelCoords(1344, 880), 7 },
	[15] = { SpawnPixelCoords(1456, 768), 7 },
	[16] = { SpawnPixelCoords(1536, 704), 7 },
	[17] = { SpawnPixelCoords(1664, 928), 18 },
	[18] = { SpawnPixelCoords(1712, 656), 9 },
	[19] = { SpawnPixelCoords(1872, 688), 3 },
	[20] = { SpawnPixelCoords(1888, 688), 3 },
	[21] = { SpawnPixelCoords(1952, 736), 10 },
	[22] = { SpawnPixelCoords(1984, 688), 26 },
	[23] = { SpawnPixelCoords(2048, 848), 27 },
	[24] = { SpawnPixelCoords(2176, 656), 36 },
	[25] = { SpawnPixelCoords(2304, 784), 18 },
	[26] = { SpawnPixelCoords(2560, 656), 9 },
	[27] = { SpawnPixelCoords(2688, 720), 7 },
	[28] = { SpawnPixelCoords(2816, 736), 1 },
	[29] = { SpawnPixelCoords(2880, 720), 7 },
	[30] = { SpawnPixelCoords(2944, 656), 9 },
	[31] = { SpawnPixelCoords(3104, 720), 7 },
	[32] = { SpawnPixelCoords(3152, 720), 32 },
	[33] = { SpawnPixelCoords(3312, 720), 7 },
	[34] = { SpawnPixelCoords(3376, 768), 29 },
	[35] = { SpawnPixelCoords(3424, 880), 3 },
	[36] = { SpawnPixelCoords(3440, 880), 3 },
	[37] = { SpawnPixelCoords(3472, 688), 10 },
	[38] = { SpawnPixelCoords(3568, 720), 25 },
	[39] = { SpawnPixelCoords(3584, 928), 21 },
	[40] = { SpawnPixelCoords(3824, 928), 21 },
	[41] = { SpawnPixelCoords(4064, 928), 20 },
	[42] = { SpawnPixelCoords(4304, 928), 21 },
	[43] = { SpawnPixelCoords(4352, 352), 15 },
	[44] = { SpawnPixelCoords(4384, 176), 9 },
	[45] = { SpawnPixelCoords(4448, 848), 31 },
	[46] = { SpawnPixelCoords(4464, 848), 1 },
	[47] = { SpawnPixelCoords(4880, 208), 15 },
	[48] = { SpawnPixelCoords(4992, 176), 22 },
	[49] = { SpawnPixelCoords(5152, 176), 9 },
	[50] = { SpawnPixelCoords(5312, 208), 16 },
	[51] = { SpawnPixelCoords(5328, 208), 24 },
	[52] = { SpawnPixelCoords(5536, 768), 23 },
	[53] = { SpawnPixelCoords(5552, 192), 15 },
	[54] = { SpawnPixelCoords(5552, 800), 22 },
	[55] = { SpawnPixelCoords(5600, 736), 9 },
	[56] = { SpawnPixelCoords(5632, 176), 9 },
	[57] = { SpawnPixelCoords(5648, 384), 15 },
	[58] = { SpawnPixelCoords(5712, 208), 3 },
	[59] = { SpawnPixelCoords(5728, 208), 3 },
	[60] = { SpawnPixelCoords(5824, 896), 16 },
	[61] = { SpawnPixelCoords(6016, 816), 9 },
	[62] = { SpawnPixelCoords(6192, 896), 11 },
	[63] = { SpawnPixelCoords(6224, 896), 32 },
	[64] = { SpawnPixelCoords(6256, 1232), 28 },
	[65] = { SpawnPixelCoords(6304, 1040), 17 },
	[66] = { SpawnPixelCoords(6336, 1120), 3 },
	[67] = { SpawnPixelCoords(6400, 816), 9 },
	[68] = { SpawnPixelCoords(6560, 1104), 12 },
	[69] = { SpawnPixelCoords(6560, 1152), 9 },
	[70] = { SpawnPixelCoords(6704, 928), 5 },
	[71] = { SpawnPixelCoords(6944, 928), 5 },
	[72] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
