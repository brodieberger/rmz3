#include "ap.h"

#include "game.h"
#include "global.h"
#include "sram.h"

#if AP

/*
  AP save data, written into each game sector after GameSavedata.
*/

struct ApGameSector {
  GameSavedata game;
  struct ApSavedata ap;
};
// ValidateSectorWithChecksum stops at SECTOR_DATA_MAX
static_assert(sizeof(struct ApGameSector) <= SECTOR_DATA_MAX);

EWRAM_DATA struct ApSavedata gApSavedata = {0};
EWRAM_DATA static struct ApGameSector sApSector = {0};

// Destination of the load in progress, or NULL
EWRAM_DATA static GameSavedata* sApLoadTo = NULL;

void ApClearSavedata(void) {
  u8* p = (u8*)&gApSavedata;
  u32 i;

  for (i = 0; i < sizeof(gApSavedata); i++) {
    p[i] = 0;
  }
}

bool32 ApIsGameSector(u8 sector) { return sector < GAME_SECTOR_NUM; }

u32 ApGameSectorSize(void) { return sizeof(struct ApGameSector); }

void* ApStageSave(const void* game) {
  sApSector.game = *(const GameSavedata*)game;
  sApSector.ap = gApSavedata;
  return &sApSector;
}

void* ApStageLoad(void* game) {
  sApLoadTo = game;
  return &sApSector;
}

// After load. Only load into live save copies AP's part.
void ApFinishLoad(void) {
  if (sApLoadTo == NULL) {
    return;
  }
  *sApLoadTo = sApSector.game;
  if (sApLoadTo == &gGameState.save) {
    gApSavedata = sApSector.ap;
  }
  sApLoadTo = NULL;
}

#endif /* AP */
