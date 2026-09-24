// WIP Contains Zero 2 enemies not implemented

#include "spawn.h"

#include "binary_literal.h"
#include "constants/entity.h"
#include "constants/motion/static.h"
#include "global.h"

#if AP

const struct SpawnTemplate gApImp0_Templates[91] = {
    [0] = {0},
    [1] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [2] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [3] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [4] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [5] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 0, 0),
        },
    [6] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 1, 0),
        },
    [7] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 2, 0),
        },
    [8] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 67, 2, 0),
            .attr = 0x01,
        },
    [9] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 67, 3, 0),
            .attr = 0x01,
        },
    [10] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 0, 0),
            .attr = 0x01,
        },
    [11] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 1, 0),
            .attr = 0x01,
        },
    [12] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 2, 0),
            .attr = 0x01,
        },
    [13] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 3, 0),
            .attr = 0x01,
        },
    [14] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 0, 1),
            .attr = 0x01,
        },
    [15] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 1, 1),
            .attr = 0x01,
        },
    [16] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 2, 1),
            .attr = 0x01,
        },
    [17] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 78, 3, 1),
            .attr = 0x01,
        },
    [18] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [19] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 49, 0, 0),
        },
    [20] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 49, 1, 0),
        },
    [21] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 29, 1, 0),
            .attr = 0x01,
        },
    [22] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 0),
        },
    [23] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 0, 0),
            .attr = 0x01,
        },
    [24] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 1, 0),
            .attr = 0x01,
        },
    [25] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 2, 0),
            .attr = 0x01,
        },
    [26] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 28, 0),
        },
    [27] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 29, 0),
        },
    [28] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 30, 0),
        },
    [29] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 31, 0),
        },
    [30] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 0),
            .attr = 0x02,
        },
    [31] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 1),
            .attr = 0x02,
        },
    [32] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 2),
            .attr = 0x02,
        },
    [33] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 3),
            .attr = 0x02,
        },
    [34] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 4),
            .attr = 0x02,
        },
    [35] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 5),
            .attr = 0x02,
        },
    [36] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 6),
            .attr = 0x02,
        },
    [37] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 7),
            .attr = 0x02,
        },
    [38] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 8),
            .attr = 0x02,
        },
    [39] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(3, 43, 0, 9),
            .attr = 0x02,
        },
    [40] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [41] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [42] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [43] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [44] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [45] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [46] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [47] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [48] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [49] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 0, 0),
        },
    [50] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 1, 0),
        },
    [51] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 2, 0),
        },
    [52] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 3, 0),
        },
    [53] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 4, 0),
        },
    [54] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 5, 0),
        },
    [55] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 13, 6, 0),
        },
    [56] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 0, 0),
        },
    [57] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 1, 0),
        },
    [58] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 2, 0),
        },
    [59] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 3, 0),
        },
    [60] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(4, 10, 4, 0),
        },
    [61] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 1, 2),
        },
    [62] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 2, 2),
        },
    [63] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 4, 2),
        },
    [64] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(ENTITY_ITEM, ITEM_GENERAL, 5, 2),
        },
    [65] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 0, 0),
        },
    [66] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 1, 0),
        },
    [67] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(6, 12, 2, 0),
        },
    [68] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_ENEMY, ENEMY_P_HUNTER, 0, 0),
            .attr = 0x01,
        },
    [69] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 0, 0),
            .attr = 0x01,
        },
    [70] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 1, 0),
            .attr = 0x01,
        },
    [71] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 15, 2, 0),
            .attr = 0x01,
        },
    [72] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 0, 0),
            .attr = 0x01,
        },
    [73] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 1, 0),
            .attr = 0x01,
        },
    [74] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 14, 2, 0),
            .attr = 0x01,
        },
    [75] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 9, 0, 0),
            .attr = 0x01,
        },
    [76] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 9, 1, 0),
            .attr = 0x01,
        },
    [77] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 29, 1, 0),
            .attr = 0x01,
        },
    [78] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 16, 1, 0),
            .attr = 0x01,
        },
    [79] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 16, 1, 1),
            .attr = 0x01,
        },
    [80] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(3, 31, 1, 0),
            .attr = 0x01,
        },
    [81] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 0),
        },
    [82] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 7, 0),
        },
    [83] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 14, 0),
        },
    [84] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 15, 0),
        },
    [85] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 16, 0),
        },
    [86] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(7, 3, 17, 0),
        },
    [87] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_DOOR_2D_BLUE, 0, 1),
        },
    [88] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(6, 30, 0, 0),
        },
    [89] =
        {
            .flag = 0x02,
            .kind = SpawnEntity(6, 30, 1, 0),
        },
    [90] =
        {
            .flag = 0x01,
            .kind = SpawnEntity(ENTITY_SOLID, SOLID_SCRIPT_ACTOR, 0, 0),
        },
};

const struct SpawnPoint gApImp0_Points[39] = {
    [0] = {-0x80000000, -0x8000, 0},
    [1] = {SpawnPixelCoords(720, 1680), 1},
    [2] = {SpawnPixelCoords(1280, 2176), 3},
    [3] = {SpawnPixelCoords(1296, 1344), 3},
    [4] = {SpawnPixelCoords(1312, 2176), 3},
    [5] = {SpawnPixelCoords(1344, 2176), 3},
    [6] = {SpawnPixelCoords(1776, 704), 18},
    [7] = {SpawnPixelCoords(1840, 672), 18},
    [8] = {SpawnPixelCoords(1936, 608), 18},
    [9] = {SpawnPixelCoords(1952, 720), 3},
    [10] = {SpawnPixelCoords(2160, 528), 18},
    [11] = {SpawnPixelCoords(2176, 1376), 3},
    [12] = {SpawnPixelCoords(2304, 1360), 3},
    [13] = {SpawnPixelCoords(2336, 752), 4},
    [14] = {SpawnPixelCoords(2416, 1312), 3},
    [15] = {SpawnPixelCoords(2448, 1312), 18},
    [16] = {SpawnPixelCoords(2752, 1376), 18},
    [17] = {SpawnPixelCoords(2848, 768), 18},
    [18] = {SpawnPixelCoords(2976, 736), 18},
    [19] = {SpawnPixelCoords(3056, 1072), 18},
    [20] = {SpawnPixelCoords(3376, 2128), 3},
    [21] = {SpawnPixelCoords(3392, 2128), 18},
    [22] = {SpawnPixelCoords(3472, 2320), 18},
    [23] = {SpawnPixelCoords(3776, 1536), 3},
    [24] = {SpawnPixelCoords(3792, 1424), 3},
    [25] = {SpawnPixelCoords(3856, 1200), 2},
    [26] = {SpawnPixelCoords(4000, 1392), 63},
    [27] = {SpawnPixelCoords(4016, 2016), 61},
    [28] = {SpawnPixelCoords(4512, 1328), 64},
    [29] = {SpawnPixelCoords(5312, 1568), 61},
    [30] = {SpawnPixelCoords(5456, 1568), 63},
    [31] = {SpawnPixelCoords(5584, 1568), 63},
    [32] = {SpawnPixelCoords(5792, 1200), 63},
    [33] = {SpawnPixelCoords(5792, 2224), 90},
    [34] = {SpawnPixelCoords(5808, 1200), 63},
    [35] = {SpawnPixelCoords(5808, 2128), 61},
    [36] = {SpawnPixelCoords(6960, 1552), 3},
    [37] = {SpawnPixelCoords(6976, 1552), 3},
    [38] = {0x7FFFFFFF, 0x7FFF, 0},
};

const struct PreloadEntity gApImp0_Preloads[2] = {
    {
        SM019_PANTHEON_HUNTER,
        B8(11111111),
        512,
        4,
        1,
        1,
        0,
    },
    {0xFF},  // terminator
};

#endif /* AP */
