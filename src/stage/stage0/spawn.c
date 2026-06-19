#include "spawn.h"

#include "global.h"

const struct SpawnTemplate gStage0SpawnEntity[2] = {
    [0] = {0},
    [1] =
        {
            .flag = 0xF,
            .kind = SpawnEntity(0xF, 0xFF, 0xFF, 0xFF),
        },
};

const struct PreloadEntity sStage0StaticTemplate[1] = {
    {0xFF, 0xFF, 0xFFF, 15, 1, 3, 1},
};

const struct SpawnPoint gStage0EntityCoord[2] = {
    {0x80000000, 0x8000, 0},
    {0x7FFFFFFF, 0x7FFF, 0},
};
