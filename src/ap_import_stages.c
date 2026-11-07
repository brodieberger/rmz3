// Every imported stage, for src/ap_import.c.
// the stages themselves are in src/ap_stage/<name>/.

#include "ap.h"
#include "ap_import.h"

#include "gba/gba.h"
#include "global.h"
#include "overworld.h"
#include "spawn.h"

#if AP

extern const struct Stage gApZ2Opening_Stage;
extern const MetatileMapSelfRelPtr gApZ2Opening_Terrain;
extern const ColorGraphic gApZ2Opening_Tilesets[];
extern const StageFunc gApZ2Opening_StageRoutines[];
u8 gApZ2Opening_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Opening_LayerRoutines[];
extern const GameCommand gApZ2Opening_Script[];
extern const GameCommand gApZ2Opening_CheckpointScript[];
extern const GameCommand gApZ2Opening_BossRestartScript[];
extern const GameCommand gApZ2Opening_BossReturnScript[];
extern const GameCommand gApZ2Opening_AgainScript[];
extern const GameCommand gApZ2Opening_ResultScript[];
extern const GameCommand gApZ2Opening_BossScript[];
extern const GameCommand gApZ2Opening_ClearScript[];
extern const GameCommand gApZ2Opening_MidBoss0Script[];
extern const GameCommand gApZ2Opening_MidBoss0ClearScript[];
extern const GameCommand gApZ2Opening_MidBoss1Script[];
extern const GameCommand gApZ2Opening_MidBoss1ClearScript[];
extern const char_t gApImportName0[];
extern const struct SpawnTemplate gApZ2Opening_Templates[];
extern const struct SpawnPoint gApZ2Opening_Points[];
extern const struct PreloadEntity gApZ2Opening_Preloads[];

static const struct ApImportMidBoss gApZ2Opening_MidBosses[2] = {
    {
      script : gApZ2Opening_MidBoss0Script,
      clearScript : gApZ2Opening_MidBoss0ClearScript,
      box : {{PIXEL(3167), PIXEL(0)}, {PIXEL(3376), PIXEL(800)}},
      lastCheckpoint : 0,
    },
    {
      script : gApZ2Opening_MidBoss1Script,
      clearScript : gApZ2Opening_MidBoss1ClearScript,
      box : {{PIXEL(4127), PIXEL(0)}, {PIXEL(4320), PIXEL(800)}},
      lastCheckpoint : 0,
    },
};

extern const struct Stage gApZ2Jungle_Stage;
extern const MetatileMapSelfRelPtr gApZ2Jungle_Terrain;
extern const ColorGraphic gApZ2Jungle_Tilesets[];
extern const StageFunc gApZ2Jungle_StageRoutines[];
u8 gApZ2Jungle_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Jungle_LayerRoutines[];
extern const GameCommand gApZ2Jungle_Script[];
extern const GameCommand gApZ2Jungle_CheckpointScript[];
extern const GameCommand gApZ2Jungle_BossRestartScript[];
extern const GameCommand gApZ2Jungle_BossReturnScript[];
extern const GameCommand gApZ2Jungle_AgainScript[];
extern const GameCommand gApZ2Jungle_ResultScript[];
extern const GameCommand gApZ2Jungle_BossScript[];
extern const GameCommand gApZ2Jungle_ClearScript[];
extern const GameCommand gApZ2Jungle_MidBoss0Script[];
extern const GameCommand gApZ2Jungle_MidBoss0ClearScript[];
extern const char_t gApImportName1[];
extern const struct SpawnTemplate gApZ2Jungle_Templates[];
extern const struct SpawnPoint gApZ2Jungle_Points[];
extern const struct PreloadEntity gApZ2Jungle_Preloads[];

static const struct ApImportMidBoss gApZ2Jungle_MidBosses[1] = {
    {
      script : gApZ2Jungle_MidBoss0Script,
      clearScript : gApZ2Jungle_MidBoss0ClearScript,
      box : {{PIXEL(4319), PIXEL(640)}, {PIXEL(4561), PIXEL(2048)}},
      lastCheckpoint : 0,
    },
};

extern const struct Stage gApZ2Naold1_Stage;
extern const MetatileMapSelfRelPtr gApZ2Naold1_Terrain;
extern const ColorGraphic gApZ2Naold1_Tilesets[];
extern const StageFunc gApZ2Naold1_StageRoutines[];
u8 gApZ2Naold1_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Naold1_LayerRoutines[];
extern const GameCommand gApZ2Naold1_Script[];
extern const GameCommand gApZ2Naold1_CheckpointScript[];
extern const GameCommand gApZ2Naold1_BossRestartScript[];
extern const GameCommand gApZ2Naold1_BossReturnScript[];
extern const GameCommand gApZ2Naold1_AgainScript[];
extern const GameCommand gApZ2Naold1_ResultScript[];
extern const GameCommand gApZ2Naold1_BossScript[];
extern const GameCommand gApZ2Naold1_ClearScript[];
extern const GameCommand gApZ2Naold1_MidBoss0Script[];
extern const GameCommand gApZ2Naold1_MidBoss0ClearScript[];
extern const GameCommand gApZ2Naold1_MidBoss1Script[];
extern const GameCommand gApZ2Naold1_MidBoss1ClearScript[];
extern const GameCommand gApZ2Naold1_MidBoss2Script[];
extern const GameCommand gApZ2Naold1_MidBoss2ClearScript[];
extern const char_t gApImportName2[];
extern const struct SpawnTemplate gApZ2Naold1_Templates[];
extern const struct SpawnPoint gApZ2Naold1_Points[];
extern const struct PreloadEntity gApZ2Naold1_Preloads[];

static const struct ApImportMidBoss gApZ2Naold1_MidBosses[3] = {
    {
      script : gApZ2Naold1_MidBoss0Script,
      clearScript : gApZ2Naold1_MidBoss0ClearScript,
      box : {{PIXEL(5760), PIXEL(0)}, {PIXEL(6000), PIXEL(800)}},
      lastCheckpoint : 1,
    },
    {
      script : gApZ2Naold1_MidBoss1Script,
      clearScript : gApZ2Naold1_MidBoss1ClearScript,
      box : {{PIXEL(6000), PIXEL(0)}, {PIXEL(6240), PIXEL(800)}},
      lastCheckpoint : 1,
    },
    {
      script : gApZ2Naold1_MidBoss2Script,
      clearScript : gApZ2Naold1_MidBoss2ClearScript,
      box : {{PIXEL(6240), PIXEL(0)}, {PIXEL(6960), PIXEL(800)}},
      lastCheckpoint : 1,
    },
};

extern const struct Stage gApZ2Bomber2_Stage;
extern const MetatileMapSelfRelPtr gApZ2Bomber2_Terrain;
extern const ColorGraphic gApZ2Bomber2_Tilesets[];
extern const StageFunc gApZ2Bomber2_StageRoutines[];
u8 gApZ2Bomber2_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Bomber2_LayerRoutines[];
extern const GameCommand gApZ2Bomber2_Script[];
extern const GameCommand gApZ2Bomber2_CheckpointScript[];
extern const GameCommand gApZ2Bomber2_WarningScript[];
extern const GameCommand gApZ2Bomber2_BossRestartScript[];
extern const GameCommand gApZ2Bomber2_BossReturnScript[];
extern const GameCommand gApZ2Bomber2_AgainScript[];
extern const GameCommand gApZ2Bomber2_ResultScript[];
extern const GameCommand gApZ2Bomber2_BossScript[];
extern const GameCommand gApZ2Bomber2_ClearScript[];
extern const GameCommand gApZ2Bomber2_MidBoss0Script[];
extern const GameCommand gApZ2Bomber2_MidBoss0ClearScript[];
extern const char_t gApImportName3[];
extern const struct SpawnTemplate gApZ2Bomber2_Templates[];
extern const struct SpawnPoint gApZ2Bomber2_Points[];
extern const struct PreloadEntity gApZ2Bomber2_Preloads[];

static const struct ApImportMidBoss gApZ2Bomber2_MidBosses[1] = {
    {
      script : gApZ2Bomber2_MidBoss0Script,
      clearScript : gApZ2Bomber2_MidBoss0ClearScript,
      box : {{PIXEL(944), PIXEL(2080)}, {PIXEL(1440), PIXEL(2240)}},
      lastCheckpoint : 1,
    },
};

extern const struct Stage gApZ2Naold2_Stage;
extern const MetatileMapSelfRelPtr gApZ2Naold2_Terrain;
extern const ColorGraphic gApZ2Naold2_Tilesets[];
extern const StageFunc gApZ2Naold2_StageRoutines[];
u8 gApZ2Naold2_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Naold2_LayerRoutines[];
extern const GameCommand gApZ2Naold2_Script[];
extern const GameCommand gApZ2Naold2_CheckpointScript[];
extern const GameCommand gApZ2Naold2_BossRestartScript[];
extern const GameCommand gApZ2Naold2_BossReturnScript[];
extern const GameCommand gApZ2Naold2_AgainScript[];
extern const GameCommand gApZ2Naold2_ResultScript[];
extern const GameCommand gApZ2Naold2_BossScript[];
extern const GameCommand gApZ2Naold2_ClearScript[];
extern const char_t gApImportName4[];
extern const struct SpawnTemplate gApZ2Naold2_Templates[];
extern const struct SpawnPoint gApZ2Naold2_Points[];
extern const struct PreloadEntity gApZ2Naold2_Preloads[];

static const struct ApImportMidBoss gApZ2Naold2_MidBosses[0] = {
};

extern const struct Stage gApZ2Na1_Stage;
extern const MetatileMapSelfRelPtr gApZ2Na1_Terrain;
extern const ColorGraphic gApZ2Na1_Tilesets[];
extern const StageFunc gApZ2Na1_StageRoutines[];
u8 gApZ2Na1_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Na1_LayerRoutines[];
extern const GameCommand gApZ2Na1_Script[];
extern const GameCommand gApZ2Na1_CheckpointScript[];
extern const GameCommand gApZ2Na1_BossRestartScript[];
extern const GameCommand gApZ2Na1_BossReturnScript[];
extern const GameCommand gApZ2Na1_AgainScript[];
extern const GameCommand gApZ2Na1_ResultScript[];
extern const GameCommand gApZ2Na1_BossScript[];
extern const GameCommand gApZ2Na1_ClearScript[];
extern const char_t gApImportName5[];
extern const struct SpawnTemplate gApZ2Na1_Templates[];
extern const struct SpawnPoint gApZ2Na1_Points[];
extern const struct PreloadEntity gApZ2Na1_Preloads[];

static const struct ApImportMidBoss gApZ2Na1_MidBosses[0] = {
};

extern const struct Stage gApZ2Na2_Stage;
extern const MetatileMapSelfRelPtr gApZ2Na2_Terrain;
extern const ColorGraphic gApZ2Na2_Tilesets[];
extern const StageFunc gApZ2Na2_StageRoutines[];
u8 gApZ2Na2_Area(Coords32* c);
extern const StageLayerRoutine gApZ2Na2_LayerRoutines[];
extern const GameCommand gApZ2Na2_Script[];
extern const GameCommand gApZ2Na2_CheckpointScript[];
extern const GameCommand gApZ2Na2_BossRestartScript[];
extern const GameCommand gApZ2Na2_BossReturnScript[];
extern const GameCommand gApZ2Na2_AgainScript[];
extern const GameCommand gApZ2Na2_ResultScript[];
extern const GameCommand gApZ2Na2_BossScript[];
extern const GameCommand gApZ2Na2_ClearScript[];
extern const char_t gApImportName6[];
extern const struct SpawnTemplate gApZ2Na2_Templates[];
extern const struct SpawnPoint gApZ2Na2_Points[];
extern const struct PreloadEntity gApZ2Na2_Preloads[];

static const struct ApImportMidBoss gApZ2Na2_MidBosses[0] = {
};

const struct ApImportedStage gApImportedStages[] = {
    {
      stage : &gApZ2Opening_Stage,
      terrain : &gApZ2Opening_Terrain,
      tilesets : gApZ2Opening_Tilesets,
      tilesetCount : 6,
      fns : gApZ2Opening_StageRoutines,
      area : gApZ2Opening_Area,
      layers : gApZ2Opening_LayerRoutines,
      script : gApZ2Opening_Script,
      checkpointScript : gApZ2Opening_CheckpointScript,
      checkpointDoor : {PIXEL(4320), PIXEL(0)},
      warningScript : NULL,
      bossScript : gApZ2Opening_BossScript,
      clearScript : gApZ2Opening_ClearScript,
      bossRestartScript : gApZ2Opening_BossRestartScript,
      bossReturnScript : gApZ2Opening_BossReturnScript,
      againScript : gApZ2Opening_AgainScript,
      resultScript : gApZ2Opening_ResultScript,
      midBosses : gApZ2Opening_MidBosses,
      midBossCount : 2,
      bossDoor : {PIXEL(7232), PIXEL(0)},
      name : gApImportName0,
      templates : gApZ2Opening_Templates,
      points : gApZ2Opening_Points,
      preloads : gApZ2Opening_Preloads,
    },
    {
      stage : &gApZ2Jungle_Stage,
      terrain : &gApZ2Jungle_Terrain,
      tilesets : gApZ2Jungle_Tilesets,
      tilesetCount : 5,
      fns : gApZ2Jungle_StageRoutines,
      area : gApZ2Jungle_Area,
      layers : gApZ2Jungle_LayerRoutines,
      script : gApZ2Jungle_Script,
      checkpointScript : gApZ2Jungle_CheckpointScript,
      checkpointDoor : {PIXEL(4560), PIXEL(880)},
      warningScript : NULL,
      bossScript : gApZ2Jungle_BossScript,
      clearScript : gApZ2Jungle_ClearScript,
      bossRestartScript : gApZ2Jungle_BossRestartScript,
      bossReturnScript : gApZ2Jungle_BossReturnScript,
      againScript : gApZ2Jungle_AgainScript,
      resultScript : gApZ2Jungle_ResultScript,
      midBosses : gApZ2Jungle_MidBosses,
      midBossCount : 1,
      bossDoor : {PIXEL(6256), PIXEL(0)},
      name : gApImportName1,
      templates : gApZ2Jungle_Templates,
      points : gApZ2Jungle_Points,
      preloads : gApZ2Jungle_Preloads,
    },
    {
      stage : &gApZ2Naold1_Stage,
      terrain : &gApZ2Naold1_Terrain,
      tilesets : gApZ2Naold1_Tilesets,
      tilesetCount : 4,
      fns : gApZ2Naold1_StageRoutines,
      area : gApZ2Naold1_Area,
      layers : gApZ2Naold1_LayerRoutines,
      script : gApZ2Naold1_Script,
      checkpointScript : gApZ2Naold1_CheckpointScript,
      checkpointDoor : {PIXEL(5536), PIXEL(0)},
      warningScript : NULL,
      bossScript : gApZ2Naold1_BossScript,
      clearScript : gApZ2Naold1_ClearScript,
      bossRestartScript : gApZ2Naold1_BossRestartScript,
      bossReturnScript : gApZ2Naold1_BossReturnScript,
      againScript : gApZ2Naold1_AgainScript,
      resultScript : gApZ2Naold1_ResultScript,
      midBosses : gApZ2Naold1_MidBosses,
      midBossCount : 3,
      bossDoor : {PIXEL(6960), PIXEL(0)},
      name : gApImportName2,
      templates : gApZ2Naold1_Templates,
      points : gApZ2Naold1_Points,
      preloads : gApZ2Naold1_Preloads,
    },
    {
      stage : &gApZ2Bomber2_Stage,
      terrain : &gApZ2Bomber2_Terrain,
      tilesets : gApZ2Bomber2_Tilesets,
      tilesetCount : 13,
      fns : gApZ2Bomber2_StageRoutines,
      area : gApZ2Bomber2_Area,
      layers : gApZ2Bomber2_LayerRoutines,
      script : gApZ2Bomber2_Script,
      checkpointScript : gApZ2Bomber2_CheckpointScript,
      checkpointDoor : {PIXEL(0), PIXEL(2400)},
      warningScript : gApZ2Bomber2_WarningScript,
      warningAt : {PIXEL(3600), PIXEL(0)},
      bossScript : gApZ2Bomber2_BossScript,
      clearScript : gApZ2Bomber2_ClearScript,
      bossRestartScript : gApZ2Bomber2_BossRestartScript,
      bossReturnScript : gApZ2Bomber2_BossReturnScript,
      againScript : gApZ2Bomber2_AgainScript,
      resultScript : gApZ2Bomber2_ResultScript,
      midBosses : gApZ2Bomber2_MidBosses,
      midBossCount : 1,
      bossDoor : {PIXEL(7320), PIXEL(0)},
      name : gApImportName3,
      templates : gApZ2Bomber2_Templates,
      points : gApZ2Bomber2_Points,
      preloads : gApZ2Bomber2_Preloads,
    },
    {
      stage : &gApZ2Naold2_Stage,
      terrain : &gApZ2Naold2_Terrain,
      tilesets : gApZ2Naold2_Tilesets,
      tilesetCount : 2,
      fns : gApZ2Naold2_StageRoutines,
      area : gApZ2Naold2_Area,
      layers : gApZ2Naold2_LayerRoutines,
      script : gApZ2Naold2_Script,
      checkpointScript : gApZ2Naold2_CheckpointScript,
      checkpointDoor : {PIXEL(4576), PIXEL(0)},
      warningScript : NULL,
      bossScript : gApZ2Naold2_BossScript,
      clearScript : gApZ2Naold2_ClearScript,
      bossRestartScript : gApZ2Naold2_BossRestartScript,
      bossReturnScript : gApZ2Naold2_BossReturnScript,
      againScript : gApZ2Naold2_AgainScript,
      resultScript : gApZ2Naold2_ResultScript,
      midBosses : gApZ2Naold2_MidBosses,
      midBossCount : 0,
      bossDoor : {PIXEL(4800), PIXEL(0)},
      name : gApImportName4,
      templates : gApZ2Naold2_Templates,
      points : gApZ2Naold2_Points,
      preloads : gApZ2Naold2_Preloads,
    },
    {
      stage : &gApZ2Na1_Stage,
      terrain : &gApZ2Na1_Terrain,
      tilesets : gApZ2Na1_Tilesets,
      tilesetCount : 5,
      fns : gApZ2Na1_StageRoutines,
      area : gApZ2Na1_Area,
      layers : gApZ2Na1_LayerRoutines,
      script : gApZ2Na1_Script,
      checkpointScript : gApZ2Na1_CheckpointScript,
      checkpointDoor : {PIXEL(3856), PIXEL(0)},
      warningScript : NULL,
      bossScript : gApZ2Na1_BossScript,
      clearScript : gApZ2Na1_ClearScript,
      bossRestartScript : gApZ2Na1_BossRestartScript,
      bossReturnScript : gApZ2Na1_BossReturnScript,
      againScript : gApZ2Na1_AgainScript,
      resultScript : gApZ2Na1_ResultScript,
      midBosses : gApZ2Na1_MidBosses,
      midBossCount : 0,
      bossDoor : {PIXEL(3856), PIXEL(1280)},
      name : gApImportName5,
      templates : gApZ2Na1_Templates,
      points : gApZ2Na1_Points,
      preloads : gApZ2Na1_Preloads,
    },
    {
      stage : &gApZ2Na2_Stage,
      terrain : &gApZ2Na2_Terrain,
      tilesets : gApZ2Na2_Tilesets,
      tilesetCount : 6,
      fns : gApZ2Na2_StageRoutines,
      area : gApZ2Na2_Area,
      layers : gApZ2Na2_LayerRoutines,
      script : gApZ2Na2_Script,
      checkpointScript : gApZ2Na2_CheckpointScript,
      checkpointDoor : {PIXEL(5296), PIXEL(0)},
      warningScript : NULL,
      bossScript : gApZ2Na2_BossScript,
      clearScript : gApZ2Na2_ClearScript,
      bossRestartScript : gApZ2Na2_BossRestartScript,
      bossReturnScript : gApZ2Na2_BossReturnScript,
      againScript : gApZ2Na2_AgainScript,
      resultScript : gApZ2Na2_ResultScript,
      midBosses : gApZ2Na2_MidBosses,
      midBossCount : 0,
      bossDoor : {PIXEL(5520), PIXEL(0)},
      name : gApImportName6,
      templates : gApZ2Na2_Templates,
      points : gApZ2Na2_Points,
      preloads : gApZ2Na2_Preloads,
    },
};

#endif /* AP */
