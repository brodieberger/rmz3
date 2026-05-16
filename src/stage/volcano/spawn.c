#include "spawn.h"

#include "binary_literal.h"
#include "global.h"

const struct SpawnTemplate gVolcanoEntity[51] =
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 2, 0),
            },
        [9] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GYRO_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [10] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 0, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 1, 0),
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 2, 0),
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 3, 0),
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 4, 0),
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 5, 0),
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 6, 0),
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 7, 0),
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 8, 0),
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 9, 0),
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 10, 0),
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_LAVA_GEYSER, 11, 0),
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [23] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_SWORDY,
            },
        [24] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_VOLCAIRE, 0, 0),
                .attr = SA_KNIGHT,
            },
        [25] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [26] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [27] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_HEAVY_CANNON, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [28] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LAMPLORT, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [29] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_LAMPLORT, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [30] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [31] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [32] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [33] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 0, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [35] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 1, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [36] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 2, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [37] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_TOP_GABYOALL, 3, 1),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [38] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 26, 2),
            },
        [39] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 47, 2),
            },
        [40] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 73, 2),
            },
        [41] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 114, 2),
            },
        [42] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 8),
            },
        [43] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 72),
            },
        [44] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 102),
            },
        [45] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 254),
            },
        [46] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 1, 255),
            },
        [47] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 0, 0),
            },
        [48] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CYBERSPACE_DOOR, 1, 0),
            },
        [49] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [50] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },
};

// 0x08347f64
const struct PreloadEntity gVolcanoStatic[20] = {
    {
        SM023_GYRO_CANNON,
        B8(00001111),
        512,
        4,
        1,
        1,
        0,
    },
    {
        SM056_HEAVY_CANNON,
        B8(00001111),
        607,
        5,
        1,
        1,
        0,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00001111),
        669,
        6,
        1,
        1,
        0,
    },
    {
        SM061_UNK,
        B8(00001111),
        512,
        13,
        1,
        2,
        0,
    },
    {
        SM062_BEETANK,
        B8(00001111),
        541,
        5,
        1,
        2,
        0,
    },
    {
        SM063_SWORDY,
        B8(00001111),
        641,
        6,
        1,
        2,
        0,
    },
    {
        SM031_VOLCANO_BOMB,
        B8(00000001),
        849,
        8,
        3,
        3,
        0,
    },
    {
        SM046_VOLCAIRE,
        B8(00000010),
        849,
        8,
        3,
        3,
        0,
    },
    {
        SM057_GEYSER,
        B8(00000100),
        849,
        8,
        3,
        3,
        1,
    },
    {
        SM058_VOLCANO_RISING_PLATFORM,
        B8(00000100),
        994,
        9,
        3,
        3,
        1,
    },
    {
        SM059_LAVA_PLATFORM,
        B8(00011000),
        849,
        8,
        3,
        3,
        1,
    },
    {
        SM025_LAMPLORT,
        B8(00010000),
        512,
        4,
        1,
        1,
        0,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00010000),
        668,
        5,
        1,
        1,
        0,
    },
    {
        SM021_TOP_GABYOALL,
        B8(00010000),
        873,
        6,
        1,
        3,
        0,
    },
    {
        SM153_VOLCANO_COFFIN,
        B8(00010000),
        905,
        9,
        3,
        3,
        1,
    },
    {
        SM061_UNK,
        B8(00010000),
        512,
        13,
        1,
        2,
        0,
    },
    {
        SM062_BEETANK,
        B8(00010000),
        541,
        5,
        1,
        2,
        0,
    },
    {
        SM063_SWORDY,
        B8(00010000),
        641,
        7,
        1,
        2,
        0,
    },
    {
        SM221_METTAUR,
        B8(01111111),
        669,
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

// 0x08348004
// clang-format off
const struct SpawnPoint gVolcanoSpawnPoints[69] = {
	[0]  = { -0x80000000, -0x8000, 0 },
	[1]  = { SpawnPixelCoords(736, 592), 25 },
	[2]  = { SpawnPixelCoords(1152, 592), 26 },
	[3]  = { SpawnPixelCoords(1712, 592), 25 },
	[4]  = { SpawnPixelCoords(2112, 592), 27 },
	[5]  = { SpawnPixelCoords(2336, 560), 47 },
	[6]  = { SpawnPixelCoords(2400, 560), 22 },
	[7]  = { SpawnPixelCoords(2704, 560), 22 },
	[8]  = { SpawnPixelCoords(2736, 560), 22 },
	[9]  = { SpawnPixelCoords(2896, 560), 22 },
	[10] = { SpawnPixelCoords(3056, 560), 22 },
	[11] = { SpawnPixelCoords(3088, 560), 22 },
	[12] = { SpawnPixelCoords(3568, 624), 24 },
	[13] = { SpawnPixelCoords(3856, 528), 22 },
	[14] = { SpawnPixelCoords(4048, 624), 24 },
	[15] = { SpawnPixelCoords(4144, 528), 22 },
	[16] = { SpawnPixelCoords(4336, 624), 24 },
	[17] = { SpawnPixelCoords(4432, 528), 22 },
	[18] = { SpawnPixelCoords(4752, 608), 18 },
	[19] = { SpawnPixelCoords(4848, 576), 49 },
	[20] = { SpawnPixelCoords(4848, 608), 19 },
	[21] = { SpawnPixelCoords(4976, 608), 12 },
	[22] = { SpawnPixelCoords(5088, 608), 18 },
	[23] = { SpawnPixelCoords(5104, 400), 3 },
	[24] = { SpawnPixelCoords(5120, 400), 22 },
	[25] = { SpawnPixelCoords(5152, 400), 39 },
	[26] = { SpawnPixelCoords(5216, 608), 12 },
	[27] = { SpawnPixelCoords(5600, 592), 44 },
	[28] = { SpawnPixelCoords(5632, 592), 27 },
	[29] = { SpawnPixelCoords(5776, 528), 9 },
	[30] = { SpawnPixelCoords(5936, 432), 38 },
	[31] = { SpawnPixelCoords(5952, 432), 2 },
	[32] = { SpawnPixelCoords(6032, 528), 9 },
	[33] = { SpawnPixelCoords(6144, 592), 25 },
	[34] = { SpawnPixelCoords(7264, 448), 48 },
	[35] = { SpawnPixelCoords(7424, 448), 7 },
	[36] = { SpawnPixelCoords(7664, 448), 7 },
	[37] = { SpawnPixelCoords(8048, 592), 41 },
	[38] = { SpawnPixelCoords(8064, 592), 3 },
	[39] = { SpawnPixelCoords(8080, 592), 3 },
	[40] = { SpawnPixelCoords(8256, 432), 28 },
	[41] = { SpawnPixelCoords(8256, 688), 23 },
	[42] = { SpawnPixelCoords(8272, 768), 23 },
	[43] = { SpawnPixelCoords(8384, 928), 7 },
	[44] = { SpawnPixelCoords(8496, 368), 40 },
	[45] = { SpawnPixelCoords(8624, 928), 7 },
	[46] = { SpawnPixelCoords(8672, 576), 28 },
	[47] = { SpawnPixelCoords(8688, 448), 23 },
	[48] = { SpawnPixelCoords(8704, 608), 43 },
	[49] = { SpawnPixelCoords(8832, 416), 29 },
	[50] = { SpawnPixelCoords(8864, 608), 23 },
	[51] = { SpawnPixelCoords(8864, 928), 8 },
	[52] = { SpawnPixelCoords(9008, 608), 23 },
	[53] = { SpawnPixelCoords(9040, 448), 42 },
	[54] = { SpawnPixelCoords(9120, 448), 30 },
	[55] = { SpawnPixelCoords(9152, 720), 23 },
	[56] = { SpawnPixelCoords(9200, 656), 31 },
	[57] = { SpawnPixelCoords(9232, 848), 47 },
	[58] = { SpawnPixelCoords(9248, 848), 3 },
	[59] = { SpawnPixelCoords(9248, 928), 23 },
	[60] = { SpawnPixelCoords(9264, 400), 29 },
	[61] = { SpawnPixelCoords(9328, 528), 3 },
	[62] = { SpawnPixelCoords(9328, 624), 33 },
	[63] = { SpawnPixelCoords(10880, 416), 28 },
	[64] = { SpawnPixelCoords(10944, 416), 3 },
	[65] = { SpawnPixelCoords(11040, 416), 48 },
	[66] = { SpawnPixelCoords(11264, 448), 5 },
	[67] = { SpawnPixelCoords(11504, 448), 5 },
	[68] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
