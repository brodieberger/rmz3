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

struct ApImportMidBoss {
  const GameCommand* script;       // Intro
  const GameCommand* clearScript;  // Defeated
  Coords32 box[2];                 // Entering it starts the fight, once per life
  u8 lastCheckpoint;               // Only fires up to this checkpoint
};

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
  const GameCommand* warningScript;       // Message played once per life after the checkpoint, or NULL
  Coords32 warningAt;                     // Going right of and below this point plays the message
  const GameCommand* bossScript;          // Boss intro
  const GameCommand* clearScript;         // Boss defeated, then the results screen
  const GameCommand* bossRestartScript;   // Stage start after dying in the boss fight
  const GameCommand* bossReturnScript;    // Boss intro after that restart
  const GameCommand* againScript;         // Stage start after a skip or a death, no opening line
  const GameCommand* resultScript;        // Results screen, after skipping the clear scene
  Coords32 bossDoor;                      // the fight starts to the right and below of the boss door
  const struct ApImportMidBoss* midBosses;
  u8 midBossCount;
  const char_t* name;
  const struct SpawnTemplate* templates;
  const struct SpawnPoint* points;
  const struct PreloadEntity* preloads;
};

extern const struct ApImportedStage gApImportedStages[];

u32 ApImportArea(Coords32* c);
// ofs moves where it paints, as StartPaletteAnimation's does
void ApStartPaletteAnimation(u16 id, const PlttAnimData* data, const AnimCmd* const* script, u16 ofs);

struct Entity* ApZ2CreateBubble(const Coords32* at, u8 kind);
void ApZ2CreateSpark(const Coords32* at, u8 angle);
void ApZ2CreateHarpuiaSpark(const Coords32* at, u8 n);
void ApZ2CreateExplosion(struct Entity* parent, const Coords32* at, u8 kind, u8 roll);
void ApZ2CreateIceBurst(struct Entity* parent, u8 kind, u8 n);
struct Entity* ApZ2CreateEx(struct Entity* boss, u8 kind);
void ApZ2PushZero(s32 dx);
void ApZ2CreateElfSparkle(const Coords32* at, u8 kind);
void ApZ2CreateGolemFeet(struct Entity* golem, u8 kind);
void ApZ2GolemDie(struct Entity* s, motion_t stand);
u8 ApZ2CoolersDown(void);
u8 ApZ2SoldiersSaved(void);
u8 ApZ2CratesStolen(void);
struct StageRun;
void ApZ2PlantCellGone(const Coords32* at);
void ApZ2PlantBreakReactor(u8 reactor);
void ApZ2Plant2CellGone(const Coords32* at);
s16 ApZ2PlantUpdate(struct StageRun* p);
s16 ApZ2BomberUpdate(struct StageRun* p);
struct Solid* ApZ2CreateCraft(const Coords32* at, u8 kind);
void ApZ2DeleteCraft(struct Solid* p);
void ApImportMissionPoint(void);

#endif  // GUARD_RMZ3_AP_IMPORT_H
