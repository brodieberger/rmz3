// Zero 2's PLANT AKA Power Room

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"

#if AP

extern const PlttAnimData gApZ2Plant_PlttAnim59, gApZ2Plant_PlttAnim60, gApZ2Plant_PlttAnim61, gApZ2Plant_PlttAnim132;
extern const AnimCmd* const gApZ2Plant_PlttAnimScript59[], *const gApZ2Plant_PlttAnimScript60[],
    *const gApZ2Plant_PlttAnimScript61[], *const gApZ2Plant_PlttAnimScript132[];
extern const ColorGraphic gApZ2Plant_TileAnim[5];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))
#define START(n) ApStartPaletteAnimation(PLTT_ANIM_ID(n), &gApZ2Plant_PlttAnim##n, gApZ2Plant_PlttAnimScript##n, 0)
#define STEP(n) StepPaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])
#define ON_TILESET(i) (TILESET(0) == (i))

// 0x0800d110
static void Stage_Init(Coords32* _ UNUSED) {
  gOverworld.work.apZ2Plant.anims = 0;
  gOverworld.work.apZ2Plant.time = 0;
}

// 0x0800d130
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2PlantState* w = &gOverworld.work.apZ2Plant;
  if (ON_TILESET(0)) {
    if (!(w->anims & 1)) {
      START(59);
      START(60);
      w->anims |= 1;
    }
    STEP(59);
    STEP(60);
  } else if (w->anims & 1) {
    REMOVE(59);
    REMOVE(60);
    w->anims ^= 1;
  }
  if (ON_TILESET(4)) {
    if (!(w->anims & 2)) {
      START(61);
      START(132);
      w->anims |= 2;
    }
    STEP(61);
    STEP(132);
  } else if (w->anims & 2) {
    REMOVE(61);
    REMOVE(132);
    w->anims ^= 2;
  }
  if (++w->time == 45) w->time = 0;
}

// 0x0800d254: reactor rooms' glow
static void Stage_Draw(Coords32* _ UNUSED) {
  const ColorGraphic* g;
  if (!ON_TILESET(3)) return;
  g = &gApZ2Plant_TileAnim[gOverworld.work.apZ2Plant.time / 9];
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

// 0x0800d2d0
static void Stage_Exit(Coords32* _ UNUSED) {
  REMOVE(59);
  REMOVE(60);
  REMOVE(61);
  REMOVE(132);
}

const StageFunc gApZ2Plant_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013bf8: spawn areas
  0: the way through
  1: reactor rooms
  2: upper floors
  3: machine room
  5: Golem's floor
*/
u8 gApZ2Plant_Area(Coords32* c) {
  s32 x = c->x, y = c->y;
  if (y > 0x63FFF && x > 0x185FFF) return 5;
  if ((x > 0xE1000 && x < 0xFF000 && y > 0x46000 && y < 0x5A000) ||
      (x > 0x11D000 && x < 0x13B000 && y > 0x16000 && y < 0x28000) ||
      (x > 0x159000 && x < 0x177000 && y > 0x3C000 && y < 0x50000) ||
      (x > 0x195000 && x < 0x1B3000 && y > 0x16000 && y < 0x28000)) {
    return 1;
  }
  if (x > 0x177000 && x < 0x186000 && y > 0x27000 && y < 0x50000) return 3;
  if (y <= 0x16000 || x > 0x1D1000 || (x > 0x18D000 && y > 0x41000) || (x > 0x151000 && y > 0x55000) ||
      y > 0x5A000) {
    return 2;
  }
  if (y <= 0x4FFFF && x > 0xB4000 && x < 0xFF000) return 2;
  return 0;
}

// --------------------------------------------

// 0x0800d2f0
static void Far_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  l->scrollPower.x = 384;
  l->scroll.x = -240;
  l->phase++;
}

// 0x0800d310: behind terrain, by screen
static void Back_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  u32 screen;
  if (l->phase != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  screen = l->viewportLeftTopPixel.x / 240;
  l->scrollPower.x = 192;
  if (screen <= 9) {
    l->scroll.x = 420;
  } else if (screen <= 21) {
    l->scroll.x = 1080;
  } else {
    l->scroll.x = 1800;
  }
  l->phase++;
}

// 0x0800d370
static void Near_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u32 screen = l->viewportLeftTopPixel.x / 240;
  l->scrollPower.x = 128;
  if (screen <= 4) {
    l->scrollPower.x = 64;
    l->scroll.x = 180;
  } else if (screen <= 9) {
    l->scroll.x = 840;
  } else if (screen <= 21) {
    l->scroll.x = 2160;
  } else {
    l->scroll.x = 3600;
  }
}

// clang-format off
const StageLayerRoutine gApZ2Plant_LayerRoutines[5] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Far_Update, DrawGeneralStageLayer, NULL},
    [3] = {Back_Update, DrawGeneralStageLayer, NULL},
    [4] = {Near_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

// --------------------------------------------

// 0x08318ff0: each crumbling floor cell's left edge and its patch
static const struct {
  s32 x;
  s32 y;
  s32 patch;
} sCells[35] = {
    {0xC9000, 0x38000, 0}, {0xCB000, 0x38000, 0}, {0xCD000, 0x38000, 0}, {0xD3000, 0x38000, 0},
    {0xD5000, 0x38000, 0}, {0xD7000, 0x38000, 0}, {0xD9000, 0x38000, 0}, {0xDF000, 0x38000, 1},
    {0xE1000, 0x38000, 0}, {0xE7000, 0x39000, 3}, {0xE9000, 0x39000, 4}, {0xEB000, 0x36000, 2},
    {0xED000, 0x36000, 0}, {0xF5000, 0x37000, 0}, {0xF7000, 0x37000, 0}, {0x1A8000, 0x4C000, 0},
    {0x1AA000, 0x4C000, 0}, {0x1AC000, 0x4C000, 0}, {0x1AE000, 0x4C000, 0}, {0x1B0000, 0x4C000, 0},
    {0x1B2000, 0x4C000, 0}, {0x1B4000, 0x4C000, 5}, {0x1B6000, 0x4C000, 1}, {0x1BB000, 0x4C000, 0},
    {0x1BD000, 0x4C000, 0}, {0x1BF000, 0x4C000, 0}, {0x1C1000, 0x4C000, 0}, {0x1C3000, 0x4C000, 6},
    {0x1C5000, 0x4C000, 2}, {0x1CA000, 0x4C000, 0}, {0x1CC000, 0x4C000, 0}, {0x1D1000, 0x4C000, 0},
    {0x1D3000, 0x4C000, 0}, {0x1D9000, 0x4C000, 0}, {0x1DB000, 0x4C000, 0},
};

// 0x08319214..0x08319244
static const u16 sPatches[7][4] = {
    {2, 1, 0x403, 0x403}, {2, 1, 0x404, 0x403}, {2, 1, 0x403, 0x404}, {2, 1, 0x453, 0x453},
    {2, 1, 0x453, 0x322}, {2, 1, 0x40d, 0x403}, {2, 1, 0x403, 0x402},
};

// 0x0800d460: floor cell under a slab gone
void ApZ2PlantCellGone(const Coords32* at) {
  u8 i;
  for (i = 0; i < 35; i++) {
    if ((at->x >> 12) == (sCells[i].x >> 12) + 1) {
      PatchMetatileMap(sCells[i].x >> 12, sCells[i].y >> 12, sPatches[sCells[i].patch]);
      return;
    }
  }
}

// 0x0800d4b4: reactor's chunks, broken
void ApZ2PlantBreakReactor(u8 reactor) {
  switch (reactor) {
    case 0:
      LoadChunk(15, 7, 194);
      LoadChunk(16, 7, 195);
      LoadChunk(15, 8, 192);
      LoadChunk(16, 8, 193);
      break;
    case 1:
      LoadChunk(23, 6, 194);
      LoadChunk(24, 6, 199);
      LoadChunk(23, 7, 196);
      LoadChunk(24, 7, 197);
      break;
    case 2:
      LoadChunk(27, 2, 194);
      LoadChunk(28, 2, 195);
      LoadChunk(27, 3, 200);
      LoadChunk(28, 3, 201);
      break;
    case 3:
      LoadChunk(19, 2, 194);
      LoadChunk(20, 2, 195);
      LoadChunk(19, 3, 202);
      LoadChunk(20, 3, 203);
      break;
  }
}

// --------------------------------------------
/*
  0x0801777c: Zero 2's mission update, in place of src/ap_import.c's.
  Four reactor rooms in any order, Phoenix Magnion in the last one's.

  checkpoint 0: the start
             1: the start, no line
             2..5: room of the last reactor beaten, by x
             6: Magnion beaten, clear scene skipped. Results
*/

extern const GameCommand gApZ2Plant_Script[], gApZ2Plant_AgainScript[], gApZ2Plant_CheckpointScript[],
    gApZ2Plant_ResultScript[], gApZ2Plant_ClearScript[], gApZ2Plant_MiniBoss0Script[], gApZ2Plant_MiniBoss1Script[],
    gApZ2Plant_GolemScript[], gApZ2Plant_GolemClearScript[], gApZ2Plant_Reactor0Script[], gApZ2Plant_Reactor1Script[],
    gApZ2Plant_Reactor2Script[], gApZ2Plant_Reactor3Script[], gApZ2Plant_Reactor0ClearScript[],
    gApZ2Plant_Reactor1ClearScript[], gApZ2Plant_Reactor2ClearScript[], gApZ2Plant_Reactor3ClearScript[],
    gApZ2Plant_Magnion0Script[], gApZ2Plant_Magnion1Script[], gApZ2Plant_Magnion2Script[],
    gApZ2Plant_Magnion3Script[], gApZ2Plant_Magnion0ReturnScript[], gApZ2Plant_Magnion1ReturnScript[],
    gApZ2Plant_Magnion2ReturnScript[], gApZ2Plant_Magnion3ReturnScript[], gApZ2Plant_Room0Script[],
    gApZ2Plant_Room1Script[], gApZ2Plant_Room2Script[], gApZ2Plant_Room3Script[];
struct ScriptEntityTemplate;
extern struct ScriptEntityTemplate gApZ2Plant_Generator, gApZ2Plant_MagmaDropper;
void CreateScriptEntity(u8 n, struct ScriptEntityTemplate* template);

static const GameCommand* const sReactorScripts[4] = {gApZ2Plant_Reactor0Script, gApZ2Plant_Reactor1Script,
                                                      gApZ2Plant_Reactor2Script, gApZ2Plant_Reactor3Script};
static const GameCommand* const sReactorClearScripts[4] = {
    gApZ2Plant_Reactor0ClearScript, gApZ2Plant_Reactor1ClearScript, gApZ2Plant_Reactor2ClearScript,
    gApZ2Plant_Reactor3ClearScript};
static const GameCommand* const sMagnionScripts[4] = {gApZ2Plant_Magnion0Script, gApZ2Plant_Magnion1Script,
                                                      gApZ2Plant_Magnion2Script, gApZ2Plant_Magnion3Script};
static const GameCommand* const sMagnionReturnScripts[4] = {
    gApZ2Plant_Magnion0ReturnScript, gApZ2Plant_Magnion1ReturnScript, gApZ2Plant_Magnion2ReturnScript,
    gApZ2Plant_Magnion3ReturnScript};
static const GameCommand* const sRoomScripts[4] = {gApZ2Plant_Room0Script, gApZ2Plant_Room1Script,
                                                   gApZ2Plant_Room2Script, gApZ2Plant_Room3Script};

// Rooms by x, and the reactor (Zero 2's boss 24 work0) in each
static const u8 sReactorIn[4] = {0, 3, 1, 2};

// Room's box: x and y past the first, up to the second
static const s32 sRooms[4][4] = {
    {0xE0FFF, 0xFF000, 0x4FFFF, 0x5A000},
    {0x11CFFF, 0x13B000, 0x1DFFF, 0x28000},
    {0x158FFF, 0x177000, 0x45FFF, 0x50000},
    {0x194FFF, 0x1B3000, 0x1DFFF, 0x28000},
};

#define BEATEN unk_0a  // 1, 2: the two mini-bosses, 4: Golem, 8 << n: room n's reactor
#define ROOM unk_17d
#define ALL_REACTORS 0x78
#define CLEARED_PHASE 10
#define DONE_PHASE 11

static bool8 inside(const Coords32* c, const s32* box) {
  return c->x > box[0] && c->x <= box[1] && c->y > box[2] && c->y <= box[3];
}

static bool8 inMachineRoom(const Coords32* z, s32 bottom, s32 left, s32 right) {
  return gStageRun.vm.camera.viewport.y > 0x2A000 && z->y <= bottom && z->x > left && z->x <= right;
}

static void freeCamera(void) {
  struct Camera* cam = &gStageRun.vm.camera;
  Camera_SetMode(cam, 3);
  cam->chaseMode = 4;
  cam->counter = 0;
}

static bool8 beaten(void) {
  if (!(gStageRun.missionStatus & MISSION_SUCCESS)) return FALSE;
  gStageRun.missionStatus &= ~MISSION_SUCCESS;
  gStageRun.missionStatus |= MISSION_STAY;
  return TRUE;
}

static void start(struct StageRun* p, const GameCommand* script, u8 phase) {
  SetScript(&gStageRun.vm, script);
  p->stageEventPhase = phase;
}

s16 ApZ2PlantUpdate(struct StageRun* p) {
  const Coords32* z = &(((struct Zero*)(p->vm).entities[0].entity)->s).coord;
  u8 n;

  switch (p->stageEventPhase) {
    case 0:
      gStageRun.missionStatus |= MISSION_STAY;
      if (gStageRun.checkpoint == 0) {
        SetScript(&gStageRun.vm, gApZ2Plant_Script);
        setStageCheckpoint(1);
        gStageRun.BEATEN = 0;
        p->stageEventPhase = 1;
      } else if (gStageRun.checkpoint == 1) {
        start(p, gApZ2Plant_CheckpointScript, 1);
      } else if (gStageRun.checkpoint == 6) {
        start(p, gApZ2Plant_ResultScript, CLEARED_PHASE);
      } else {
        p->ROOM = gStageRun.checkpoint - 2;
        start(p, sRoomScripts[p->ROOM], (gStageRun.BEATEN & ALL_REACTORS) == ALL_REACTORS ? 9 : 1);
      }
      for (n = 0; n < 4; n++) {
        if (gStageRun.BEATEN & (8 << n)) ApZ2PlantBreakReactor(sReactorIn[n]);
      }
      break;
    case 1:
      if (!(gStageRun.BEATEN & 1) && z->y <= 0x2F000 && z->x > 0xEFFFF && z->x <= 0xFF000) {
        start(p, gApZ2Plant_MiniBoss0Script, 2);
        gStageRun.vm.active &= ~VM_FLAG1;
        p->ROOM = 0;
      }
      if (!(gStageRun.BEATEN & 2) && z->y <= 0x43000 && z->x > 0x1D0FFF && z->x <= 0x1E0000) {
        start(p, gApZ2Plant_MiniBoss1Script, 3);
        gStageRun.vm.active &= ~VM_FLAG1;
        p->ROOM = 0;
      }
      if (inMachineRoom(z, 0x4FFFF, 0x177000, 0x185FFF)) {
        CreateScriptEntity(3, &gApZ2Plant_Generator);
        CreateScriptEntity(4, &gApZ2Plant_MagmaDropper);
        p->stageEventPhase = 4;
        break;
      }
      if (!(gStageRun.BEATEN & 4) && z->y > 0x63FFF && z->x > 0x185FFF) start(p, gApZ2Plant_GolemScript, 5);
      for (n = 0; n < 4; n++) {
        if (!(gStageRun.BEATEN & (8 << n)) && inside(z, sRooms[n])) {
          p->ROOM = n;
          start(p, sReactorScripts[n], 6);
        }
      }
      break;
    case 2:
    case 3:
      if (p->ROOM == 0 && beaten()) p->ROOM = 1;
      if (!(gStageRun.vm.active & VM_FLAG1)) break;
      DeleteScriptEntity(1);
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.BEATEN |= p->stageEventPhase == 2 ? 1 : 2;
      freeCamera();
      p->stageEventPhase = 1;
      break;
    case 4:
      if (inMachineRoom(z, 0x50000, 0x176FFF, 0x186000)) break;
      DeleteScriptEntity(3);
      DeleteScriptEntity(4);
      p->stageEventPhase = 1;
      break;
    case 5:
      if (!beaten()) break;
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.BEATEN |= 4;
      start(p, gApZ2Plant_GolemClearScript, 1);
      break;
    case 6:
      if (!beaten()) break;
      gStageRun.vm.active &= ~VM_FLAG1;
      start(p, sReactorClearScripts[p->ROOM], 7);
      setStageCheckpoint(p->ROOM + 2);
      gStageRun.BEATEN |= 8 << p->ROOM;
      break;
    case 7:
      // The last reactor's clear scene gives way to Magnion at once, as in Zero 2
      if ((gStageRun.BEATEN & ALL_REACTORS) == ALL_REACTORS) {
        start(p, sMagnionScripts[p->ROOM], 8);
      } else {
        p->stageEventPhase = 1;
      }
      break;
    case 8:
      if (!(gStageRun.missionStatus & MISSION_SUCCESS)) break;
      gCollisionManager.disabled |= COLLMAN_DISABLED;
      gCollisionManager.sweep |= (1 << FACTION_ENEMY);
      SetScript(&gStageRun.vm, gApZ2Plant_ClearScript);
      gStageRun.missionStatus &= ~MISSION_SUCCESS;
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.missionStatus |= STOP_TIME_COUNT;
      gStageRun.missionStatus |= MISSION_STAY;
      setStageCheckpoint2(6);
      p->stageEventPhase = CLEARED_PHASE;
      break;
    case 9:
      if (((z->x >> 8) % 240) >> 4 == 9) start(p, sMagnionReturnScripts[p->ROOM], 8);
      break;
    case CLEARED_PHASE:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      gCollisionManager.sweep = 0;
      gStageRun.missionStatus &= ~MISSION_STAY;
      p->stageEventPhase = DONE_PHASE;
      break;
  }
  return 0;
}

#endif  // AP
