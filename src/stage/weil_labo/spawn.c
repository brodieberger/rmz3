#include "spawn.h"

#include "binary_literal.h"
#include "global.h"

// 0x0834ba54
const struct SpawnTemplate gWeilLaboEntity[50] =
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
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 2, 0),
            },
        [8] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 0, 0),
            },
        [9] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_GRAY_V, 1, 0),
            },
        [10] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 0, 0),
            },
        [11] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_AREAX2_WEILLABO, 0, 1),
            },
        [12] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_AREAX2_WEILLABO, 1, 1),
            },
        [13] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_AREAX2_WEILLABO, 2, 1),
            },
        [14] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PLATFORM_AREAX2_WEILLABO, 3, 1),
            },
        [15] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 0, 0),
            },
        [16] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 1, 0),
            },
        [17] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 2, 0),
            },
        [18] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 3, 0),
            },
        [19] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 4, 0),
            },
        [20] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 5, 0),
            },
        [21] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 6, 0),
            },
        [22] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_PHANTOM_TELEPORTER, 7, 0),
            },
        [23] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 177, 2),
            },
        [24] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ITEM, ITEM_DISK, 178, 2),
            },
        [25] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 20),
            },
        [26] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 11),
            },
        [27] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 19),
            },
        [28] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 97),
            },
        [29] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 151),
            },
        [30] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 164),
            },
        [31] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 179),
            },
        [32] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 254),
            },
        [33] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_SOLID, SOLID_CONTAINER, 0, 255),
            },
        [34] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [35] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MOTHJIRO, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [36] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_MOTHJIRO, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [37] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [38] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CAPSULE_CANNON, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
            },
        [39] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_GALLISNI, 0, 0),
            },
        [40] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [41] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_SHOTCOUNTER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 2,
                .virusID = VIRUS_SWORDY,
            },
        [42] =
            {
                .flag = SF_FLAG_1,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_EYE_CANNON, 0, 0),
            },
        [43] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_GUARDIAN, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [44] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_CANNON_HOPPER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [45] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 0, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [46] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [47] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_PETATRIA, 2, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
            },
        [48] =
            {
                .flag = SF_RESPAWN,
                .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 1, 0),
                .attr = SA_KNIGHT,
                .mettaurID = 1,
                .virusID = VIRUS_BEETANK,
            },
        [49] =
            {
                .flag = 0xF,
                .kind = SpawnEntity(15, 255, 255, 255),
            },

};

const struct PreloadEntity gWeilLaboStatic[13] = {
    {
      id : SM123_TELEPORTAL,
      areas : B8(01000000),
      tileBase : 903,
      palID : 8,
      unk_05 : 3,
      unk_06 : 3,
      cyberColor : TRUE,
    },
    {
        SM019_PANTHEON_HUNTER,
        B8(00000101),
        512,
        4,
        1,
        1,
    },
    {
      // Solid, 33
      id : SM125_WEILLABO_PLATFORM,
      areas : B8(00000001),
      tileBase : 632,
      palID : 5,
      unk_05 : 3,
      unk_06 : 3,
      cyberColor : TRUE,
    },
    {
      // Enemy, 47
      id : SM107_MOTHJIRO,
      areas : B8(00000001),
      tileBase : 692,
      palID : 6,
      unk_05 : 1,
      unk_06 : 3,
    },
    {
      // Enemy, 43
      id : SM104_CAPSULE_CANNON,
      areas : B8(00000001),
      tileBase : 740,
      palID : 7,
      unk_05 : 1,
      unk_06 : 3,
    },
    {
        SM020_PANTHEON_GUARDIAN,
        B8(00000010),
        512,
        4,
        1,
        1,
        0,
    },
    {
        SM103_GALLISNI,
        B8(00000010),
        666,
        5,
        3,
        3,
        0,
    },
    {
        SM004_SHOTCOUNTER,
        B8(00000010),
        799,
        6,
        1,
        1,
        0,
    },
    {
        SM102_EYE_CANNON,
        B8(00000010),
        855,
        7,
        3,
        3,
        0,
    },
    {
        SM220_CANNON_HOPPER,
        B8(00000100),
        632,
        5,
        1,
        3,
        0,
    },
    {
        SM126_PETATRIA,
        B8(00000100),
        688,
        6,
        1,
        3,
        0,
    },
    {
        SM221_METTAUR,
        B8(00111111),
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

// clang-format off
const struct SpawnPoint gWeilLaboEntityCoord[68] = {
    [0] = { -0x80000000, -0x8000, 0 },
    [1] = { 0x0000002C, 0x001B, 34 },
    [2] = { 0x00000037, 0x001A, 34 },
    [3] = { 0x0000003A, 0x001A, 28 },
    [4] = { 0x00000040, 0x0018, 34 },
    [5] = { 0x0000004C, 0x0015, 35 },
    [6] = { 0x00000052, 0x0013, 35 },
    [7] = { 0x0000005A, 0x0016, 11 },
    [8] = { 0x00000060, 0x0019, 13 },
    [9] = { 0x00000067, 0x001C, 11 },
    [10] = { 0x00000070, 0x001D, 13 },
    [11] = { 0x00000071, 0x001C, 48 },
    [12] = { 0x00000079, 0x001D, 11 },
    [13] = { 0x00000082, 0x001D, 13 },
    [14] = { 0x0000008A, 0x0013, 23 },
    [15] = { 0x0000008B, 0x001D, 11 },
    [16] = { 0x00000092, 0x0013, 38 },
    [17] = { 0x00000095, 0x001F, 34 },
    [18] = { 0x0000009B, 0x001B, 38 },
    [19] = { 0x000000A4, 0x0023, 5 },
    [20] = { 0x000000B3, 0x0023, 5 },
    [21] = { 0x000000B6, 0x001E, 15 },
    [22] = { 0x000000B7, 0x0028, 17 },
    [23] = { 0x000000BE, 0x0028, 18 },
    [24] = { 0x000000BF, 0x001E, 16 },
    [25] = { 0x000000C2, 0x0023, 7 },
    [26] = { 0x000000D1, 0x0023, 5 },
    [27] = { 0x000000D4, 0x001A, 43 },
    [28] = { 0x000000D8, 0x0019, 39 },
    [29] = { 0x000000DA, 0x000B, 42 },
    [30] = { 0x000000DA, 0x0010, 29 },
    [31] = { 0x000000DA, 0x0021, 39 },
    [32] = { 0x000000E6, 0x000C, 39 },
    [33] = { 0x000000F5, 0x000C, 39 },
    [34] = { 0x00000104, 0x000C, 39 },
    [35] = { 0x00000111, 0x000C, 39 },
    [36] = { 0x00000116, 0x0010, 43 },
    [37] = { 0x00000118, 0x0012, 27 },
    [38] = { 0x00000120, 0x0010, 39 },
    [39] = { 0x00000128, 0x0010, 43 },
    [40] = { 0x00000130, 0x000C, 39 },
    [41] = { 0x00000132, 0x000C, 41 },
    [42] = { 0x00000132, 0x0017, 41 },
    [43] = { 0x00000133, 0x001D, 25 },
    [44] = { 0x00000133, 0x0023, 39 },
    [45] = { 0x00000136, 0x0024, 24 },
    [46] = { 0x00000137, 0x002E, 40 },
    [47] = { 0x00000138, 0x000F, 40 },
    [48] = { 0x0000013D, 0x002F, 41 },
    [49] = { 0x00000147, 0x002B, 42 },
    [50] = { 0x0000014E, 0x0022, 41 },
    [51] = { 0x0000014F, 0x0030, 30 },
    [52] = { 0x00000153, 0x002E, 43 },
    [53] = { 0x00000158, 0x0019, 5 },
    [54] = { 0x00000167, 0x0019, 5 },
    [55] = { 0x0000016A, 0x0014, 19 },
    [56] = { 0x0000016B, 0x001E, 21 },
    [57] = { 0x00000172, 0x001E, 22 },
    [58] = { 0x00000173, 0x0014, 20 },
    [59] = { 0x00000176, 0x0019, 7 },
    [60] = { 0x00000185, 0x001B, 34 },
    [61] = { 0x00000194, 0x001B, 34 },
    [62] = { 0x00000198, 0x001B, 44 },
    [63] = { 0x0000019C, 0x001B, 31 },
    [64] = { 0x000001AF, 0x0025, 26 },
    [65] = { 0x000001B2, 0x0058, 5 },
    [66] = { 0x000001C1, 0x0058, 5 },
    [67] = { 0x7FFFFFFF, 0x7FFF, 0 },
};
// clang-format on
