// Every imported stage, for src/ap_import.c.
// the stages themselves are in src/ap_stage/<name>/.

#include "ap.h"
#include "ap_import.h"

#include "gba/gba.h"
#include "global.h"
#include "overworld.h"
#include "spawn.h"

#if AP

extern const struct Stage gApImp0_Stage;
extern const MetatileMapSelfRelPtr gApImp0_Terrain;
extern const ColorGraphic gApImp0_Tilesets[];
extern const GameCommand gApImp0_Script[];
extern const char_t gApImportName0[];
extern const struct SpawnTemplate gApImp0_Templates[];
extern const struct SpawnPoint gApImp0_Points[];
extern const struct PreloadEntity gApImp0_Preloads[];

const struct ApImportedStage gApImportedStages[] = {
    {
      stage : &gApImp0_Stage,
      terrain : &gApImp0_Terrain,
      tilesets : gApImp0_Tilesets,
      tilesetCount : 13,
      script : gApImp0_Script,
      name : gApImportName0,
      templates : gApImp0_Templates,
      points : gApImp0_Points,
      preloads : gApImp0_Preloads,
    },
};

const u8 gApImportCount = 1;

#endif /* AP */
