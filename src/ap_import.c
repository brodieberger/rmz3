#include "ap.h"
#include "ap_import.h"

#include "gba/gba.h"
#include "global.h"
#include "overworld.h"
#include "score.h"
#include "script.h"
#include "spawn.h"
#include "stagerun.h"

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
EWRAM_DATA static bool8 sStarted = FALSE;  // opening line played

static void ApImportRebase(const u32* src, u32* dst) {
  *dst = (u32)((const u8*)src + *src) - (u32)dst;
}

void ApImportSelect(u8 n) {
  const struct ApImportedStage* imp;
  u8 i;

  if (n >= AP_IMPORT_COUNT) {
    n = 0;
  }
  gApImportSelected = n;
  sStarted = FALSE;
  imp = &gApImportedStages[n];
  ApImportResetKills();

  gApSlot0Stage = *imp->stage;
  gApSlot0Stage.fn = imp->fns;
  gApSlot0Stage.bgFns = imp->layers;
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

// 0 unless the legacy stage option is enabled.
u8 ApImportCount(void) { return gApSeedConfig.legacyStages ? AP_IMPORT_COUNT : 0; }

const char_t* ApImportName(u8 n) { return gApImportedStages[n].name; }

/*
  Update for imported stages, based on Area X-2's. 
  Dying will restart the stage at gStageRun.checkpoint, and phase 0 gets the start script.

  checkpoint 0: the start
             1: past checkpointDoor
             2: past bossDoor, the boss fight
             3: boss beaten, clear scene skipped. Results
*/
#define MID_BOSS_PHASE 6
#define WARNED_PHASE 7
#define MID_BOSSES_BEATEN unk_0a  // bit by mid-boss

EWRAM_DATA static u8 sMidBoss = 0;  // the one being fought

// Phases before the boss fight, when the mid-boss and the boss door can start
static bool8 isExploring(u8 phase) { return phase == 1 || phase == 2 || phase == WARNED_PHASE; }

static bool8 isPast(struct Zero* z, const Coords32* door) {
  return (z->s).coord.x >= door->x && (z->s).coord.y >= door->y;
}

static bool8 isInside(struct Zero* z, const Coords32* box) {
  return (z->s).coord.x > box[0].x && (z->s).coord.x < box[1].x && (z->s).coord.y > box[0].y &&
         (z->s).coord.y < box[1].y;
}

// Mid-boss whose box Zero is in and not beaten this life, or midBossCount
static u8 midBossAt(const struct ApImportedStage* imp, struct Zero* z) {
  u8 i;
  for (i = 0; i < imp->midBossCount; i++) {
    const struct ApImportMidBoss* m = &imp->midBosses[i];
    if (!(gStageRun.MID_BOSSES_BEATEN & (1 << i)) && gStageRun.checkpoint <= m->lastCheckpoint &&
        isInside(z, m->box)) {
      break;
    }
  }
  return i;
}

extern const StageFunc gApZ2Ice_StageRoutines[4], gApZ2Jungle_StageRoutines[4], gApZ2Train_StageRoutines[4],
    gApZ2Plant_StageRoutines[4], gApZ2Bomber_StageRoutines[4];

s16 ApImportUpdate(struct StageRun* p) {
  const struct ApImportedStage* imp = &gApImportedStages[gApImportSelected];
  struct Zero* z = (struct Zero*)(p->vm).entities[0].entity;
  u8 midBoss;

  if (imp->fns == gApZ2Plant_StageRoutines) return ApZ2PlantUpdate(p);
  if (imp->fns == gApZ2Bomber_StageRoutines) return ApZ2BomberUpdate(p);

  if (p->stageEventPhase == 0) {
    gStageRun.MID_BOSSES_BEATEN &= ~((1 << imp->midBossCount) - 1);
    gStageRun.missionStatus |= MISSION_STAY;
    if (gStageRun.checkpoint == 0) {
      SetScript(&gStageRun.vm, sStarted ? imp->againScript : imp->script);
      sStarted = TRUE;
      p->stageEventPhase = 1;
    } else if (gStageRun.checkpoint == 3) {
      SetScript(&gStageRun.vm, imp->resultScript);
      p->stageEventPhase = 4;
    } else if (gStageRun.checkpoint == 1) {
      SetScript(&gStageRun.vm, imp->checkpointScript);
      p->stageEventPhase = 2;
    } else {
      SetScript(&gStageRun.vm, imp->bossRestartScript);
      p->stageEventPhase = 2;
    }

  } else if (isExploring(p->stageEventPhase) && (midBoss = midBossAt(imp, z)) < imp->midBossCount) {
    sMidBoss = midBoss;
    SetScript(&gStageRun.vm, imp->midBosses[midBoss].script);
    p->stageEventPhase = MID_BOSS_PHASE;

  } else if (p->stageEventPhase == MID_BOSS_PHASE && (gStageRun.missionStatus & MISSION_SUCCESS)) {
    SetScript(&gStageRun.vm, imp->midBosses[sMidBoss].clearScript);
    gStageRun.missionStatus &= ~MISSION_SUCCESS;
    gStageRun.vm.active &= ~VM_FLAG1;
    gStageRun.missionStatus |= MISSION_STAY;
    gStageRun.MID_BOSSES_BEATEN |= 1 << sMidBoss;
    p->stageEventPhase = 1;

  } else if (p->stageEventPhase == 1 && isPast(z, &imp->checkpointDoor)) {
    setStageCheckpoint(1);
    p->stageEventPhase = 2;

  } else if (p->stageEventPhase == 2 && imp->warningScript != NULL && gStageRun.checkpoint == 1 &&
             isPast(z, &imp->warningAt)) {
    SetScript(&gStageRun.vm, imp->warningScript);
    p->stageEventPhase = WARNED_PHASE;

  } else if (isExploring(p->stageEventPhase) && isPast(z, &imp->bossDoor)) {
    SetScript(&gStageRun.vm, (gStageRun.checkpoint == 2) ? imp->bossReturnScript : imp->bossScript);
    setStageCheckpoint(2);
    p->stageEventPhase = 3;

  } else if (p->stageEventPhase == 3 && (gStageRun.missionStatus & MISSION_SUCCESS)) {
    gCollisionManager.disabled |= COLLMAN_DISABLED;
    gCollisionManager.sweep |= (1 << FACTION_ENEMY);
    SetScript(&gStageRun.vm, imp->clearScript);
    gStageRun.vm.active &= ~VM_FLAG1;
    gStageRun.missionStatus |= STOP_TIME_COUNT;
    gStageRun.missionStatus |= MISSION_STAY;
    setStageCheckpoint2(3);
    p->stageEventPhase = 4;

  } else if (p->stageEventPhase == 4) {
    gCollisionManager.disabled &= ~COLLMAN_DISABLED;
    gCollisionManager.sweep = 0;
    gStageRun.missionStatus &= ~MISSION_STAY;
    p->stageEventPhase = 5;
  }
  return 0;
}

u32 ApImportArea(Coords32* c) { return gApImportedStages[gApImportSelected].area(c); }

const struct SpawnTemplate* ApImportTemplates(void) { return gApImportedStages[gApImportSelected].templates; }

const struct SpawnPoint* ApImportPoints(void) { return gApImportedStages[gApImportSelected].points; }

// 0x0801cefc: in Zero 2 two stages' mission points are what Zero did there
void ApImportMissionPoint(void) {
  const StageFunc* fns = gApImportedStages[gApImportSelected].fns;
  if (gScore.stageID != STAGE_NONE) return;
  if (fns == gApZ2Ice_StageRoutines) gScore.missionPoint = 5 * ApZ2CoolersDown();
  if (fns == gApZ2Jungle_StageRoutines) gScore.missionPoint = 4 * ApZ2SoldiersSaved();
  if (fns == gApZ2Train_StageRoutines) gScore.missionPoint = 20 - 2 * ApZ2CratesStolen();
}

#endif /* AP */
