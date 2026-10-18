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
extern const StageFunc gApImp0_StageRoutines[];
u8 gApImp0_Area(Coords32* c);
extern const StageLayerRoutine gApImp0_LayerRoutines[];
extern const GameCommand gApImp0_Script[];
extern const GameCommand gApImp0_CheckpointScript[];
extern const GameCommand gApImp0_WarningScript[];
extern const GameCommand gApImp0_BossRestartScript[];
extern const GameCommand gApImp0_BossScript[];
extern const GameCommand gApImp0_ClearScript[];
extern const GameCommand gApImp0_MidBossScript[];
extern const GameCommand gApImp0_MidBossClearScript[];
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
      fns : gApImp0_StageRoutines,
      area : gApImp0_Area,
      layers : gApImp0_LayerRoutines,
      script : gApImp0_Script,
      checkpointScript : gApImp0_CheckpointScript,
      checkpointDoor : {PIXEL(0), PIXEL(2400)},
      warningScript : gApImp0_WarningScript,
      warningAt : {PIXEL(3600), PIXEL(0)},
      bossScript : gApImp0_BossScript,
      clearScript : gApImp0_ClearScript,
      bossRestartScript : gApImp0_BossRestartScript,
      midBossScript : gApImp0_MidBossScript,
      midBossClearScript : gApImp0_MidBossClearScript,
      midBossBox : {{PIXEL(944), PIXEL(2080)}, {PIXEL(1440), PIXEL(2240)}},
      bossDoor : {PIXEL(7320), PIXEL(0)},
      name : gApImportName0,
      templates : gApImp0_Templates,
      points : gApImp0_Points,
      preloads : gApImp0_Preloads,
    },
};

const u8 gApImportCount = 1;

#endif /* AP */
