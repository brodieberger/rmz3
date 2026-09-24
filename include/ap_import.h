#ifndef GUARD_RMZ3_AP_IMPORT_H
#define GUARD_RMZ3_AP_IMPORT_H

/*
  One imported custom stage stage
*/

#include "gfx.h"
#include "overworld.h"
#include "script.h"
#include "spawn.h"

struct ApImportedStage {
  const struct Stage* stage;              // template: maps, tables and layer numbers; code pointers NULL
  const MetatileMapSelfRelPtr* terrain;
  const ColorGraphic* tilesets;
  u32 tilesetCount;
  const GameCommand* script;              // Currently just spawnpoint, BGM, READY, release
  const char_t* name;
  const struct SpawnTemplate* templates;
  const struct SpawnPoint* points;
  const struct PreloadEntity* preloads;
};

extern const struct ApImportedStage gApImportedStages[];
extern const u8 gApImportCount;

#endif  // GUARD_RMZ3_AP_IMPORT_H
