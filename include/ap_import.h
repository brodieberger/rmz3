#ifndef GUARD_RMZ3_AP_IMPORT_H
#define GUARD_RMZ3_AP_IMPORT_H

/*
  One imported custom stage stage
*/

#include "gfx.h"
#include "overworld.h"
#include "palette_animation.h"
#include "script.h"
#include "spawn.h"

struct ApImportedStage {
  const struct Stage* stage;              // Template. Its code pointers come from fns and layers
  const MetatileMapSelfRelPtr* terrain;
  const ColorGraphic* tilesets;
  u32 tilesetCount;
  const StageFunc* fns;                   // Stage routines: init, update, draw, exit
  AreaChecker area;                       // Which spawn area a position is in
  const StageLayerRoutine* layers;        // Background layer routines
  const GameCommand* script;              // Stage start
  const GameCommand* checkpointScript;    // Stage start from the checkpoint
  Coords32 checkpointDoor;                // Going right of and below this point sets the checkpoint
  const GameCommand* warningScript;       // Message played once per life after the checkpoint
  Coords32 warningAt;                     // Going right of and below this point plays the message
  const GameCommand* bossScript;          // Boss intro
  const GameCommand* clearScript;         // Boss defeated, then the results screen
  const GameCommand* bossRestartScript;   // Stage start after dying in the boss fight
  Coords32 bossDoor;                      // the fight starts to the right and below of the boss door
  const GameCommand* midBossScript;       // Mid-boss intro
  const GameCommand* midBossClearScript;  // Mid-boss defeated
  Coords32 midBossBox[2];                 // Entering it starts the mid-boss, once per run
  const char_t* name;
  const struct SpawnTemplate* templates;
  const struct SpawnPoint* points;
  const struct PreloadEntity* preloads;
};

extern const struct ApImportedStage gApImportedStages[];

u32 ApImportArea(Coords32* c);
void ApStartPaletteAnimation(u16 id, const PlttAnimData* data, const AnimCmd* const* script);
extern const u8 gApImportCount;

#endif  // GUARD_RMZ3_AP_IMPORT_H
