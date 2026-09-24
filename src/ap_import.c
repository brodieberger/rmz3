#include "ap.h"
#include "ap_import.h"

#include "gba/gba.h"
#include "global.h"
#include "overworld.h"
#include "script.h"
#include "spawn.h"

#if AP

/*
  Imported stages: other Zero games' levels.
  All share Stage0 which is an unused slot
  HEAVILY WIP.
*/

EWRAM_DATA struct Stage gApSlot0Stage = {0};
EWRAM_DATA MetatileMapSelfRelPtr gApSlot0Terrain = {0};
EWRAM_DATA ColorGraphic gApSlot0Tilesets[AP_IMPORT_TILESETS_MAX] = {0};
EWRAM_DATA struct PreloadEntity gApSlot0Preloads[AP_IMPORT_PRELOADS_MAX] = {0};
EWRAM_DATA u8 gApImportSelected = 0;

static void ApImportStageNop(Coords32* _ UNUSED) { return; }

static const StageFunc sApImportStageRoutine[4] = {
    ApImportStageNop,
    ApImportStageNop,
    ApImportStageNop,
    ApImportStageNop,
};

// clang-format off
static const StageLayerRoutine sApImportLayerRoutine[2] = {
    [0] = {
      [LAYER_UPDATE] = NULL,
      [LAYER_DRAW]   = NULL,
      [LAYER_EXIT]   = NULL,
    },
    [1] = {
      [LAYER_UPDATE] = NULL,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

static void ApImportRebase(const u32* src, u32* dst) {
  *dst = (u32)((const u8*)src + *src) - (u32)dst;
}

void ApImportSelect(u8 n) {
  const struct ApImportedStage* imp;
  u8 i;

  if (n >= gApImportCount) {
    n = 0;
  }
  gApImportSelected = n;
  imp = &gApImportedStages[n];

  gApSlot0Stage = *imp->stage;
  gApSlot0Stage.fn = sApImportStageRoutine;
  gApSlot0Stage.bgFns = sApImportLayerRoutine;
  gApSlot0Stage.terrainHdr = &gApSlot0Terrain;

  ApImportRebase((const u32*)&imp->terrain->tiles, (u32*)&gApSlot0Terrain.tiles);
  ApImportRebase((const u32*)&imp->terrain->attrs, (u32*)&gApSlot0Terrain.attrs);
  ApImportRebase((const u32*)&imp->terrain->chunks, (u32*)&gApSlot0Terrain.chunks);

  for (i = 0; i < AP_IMPORT_PRELOADS_MAX; i++) {
    gApSlot0Preloads[i] = imp->preloads[i];
    if (imp->preloads[i].id == 0xFF) {
      break;
    }
  }

  for (i = 0; i < imp->tilesetCount && i < AP_IMPORT_TILESETS_MAX; i++) {
    gApSlot0Tilesets[i] = imp->tilesets[i];
    ApImportRebase(&imp->tilesets[i].g.src, &gApSlot0Tilesets[i].g.src);
    ApImportRebase(&imp->tilesets[i].pal.src, &gApSlot0Tilesets[i].pal.src);
  }
}

u8 ApImportCount(void) { return gApImportCount; }

const char_t* ApImportName(u8 n) { return gApImportedStages[n].name; }

const void* ApImportScript(void) { return gApImportedStages[gApImportSelected].script; }

const struct SpawnTemplate* ApImportTemplates(void) { return gApImportedStages[gApImportSelected].templates; }

const struct SpawnPoint* ApImportPoints(void) { return gApImportedStages[gApImportSelected].points; }

#endif /* AP */
