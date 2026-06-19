#include "gfx.h"
#include "global.h"
#include "overworld.h"
#include "palette_animation.h"
#include "score.h"

#define STAGE (gOverworld.work.repairFactory)

#define CONVEYOR_SPEED (PIXEL(85) / 64)

static void initRepairFactory(Coords32* _ UNUSED);
static void repairFactory_0800d6b4(Coords32* c);
static void repairFactory_0800d8c0(Coords32* _ UNUSED);
static void exitRepairFactory(Coords32* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initRepairFactory,
    repairFactory_0800d6b4,
    repairFactory_0800d8c0,
    exitRepairFactory,
};

static void initRepairFactory(Coords32* _ UNUSED) {
  gOverworld.state[0] = 0;
  STAGE.unk_000 = 0;
  STAGE.unk_001 = 0;
  STAGE.unk_002 = 0;
  StartPaletteAnimation(43, 0);
  StartPaletteAnimation(44, 0);
}

// 0x0800D6B4
static void repairFactory_0800d6b4(Coords32* c) {
  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 1)) {
    if ((STAGE.unk_000 & (1 << 0)) == 0) {
      STAGE.unk_000 |= (1 << 0);
      StartPaletteAnimation(45, 0);
    }
    StepPaletteAnimation(45);

  } else if (STAGE.unk_000 & (1 << 0)) {
    STAGE.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(45);
  }

  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 4)) {
    if ((STAGE.unk_000 & (1 << 1)) == 0) {
      STAGE.unk_000 |= (1 << 1);
      StartPaletteAnimation(46, 0);
      StartPaletteAnimation(47, 0);
      StartPaletteAnimation(48, 0);
    }
    StepPaletteAnimation(46);
    StepPaletteAnimation(47);
    StepPaletteAnimation(48);

  } else if (STAGE.unk_000 & (1 << 1)) {
    STAGE.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(46);
    RemovePaletteAnimation(47);
    RemovePaletteAnimation(48);
  }

  StepPaletteAnimation(43);
  StepPaletteAnimation(44);

  // Toggle Conveyor Direction
  if (gOverworld.state[0] == 0) {
    gOverworld.terrain.conveyor[0] = -(CONVEYOR_SPEED + 1);
    gOverworld.terrain.conveyor[1] = CONVEYOR_SPEED + 1;
    STAGE.unk_001++;
    if (STAGE.unk_001 == 6) STAGE.unk_001 = 0;
  } else {
    gOverworld.terrain.conveyor[0] = CONVEYOR_SPEED + 1;
    gOverworld.terrain.conveyor[1] = -(CONVEYOR_SPEED + 1);
    STAGE.unk_001--;
    if (STAGE.unk_001 < 0) STAGE.unk_001 = 5;
  }

  STAGE.unk_002++;
  if (STAGE.unk_002 == 45) STAGE.unk_002 = 0;

  if ((c->x > PIXEL(4304) && c->x < PIXEL(5760)) || (c->x < PIXEL(480) && c->y < PIXEL(320))) {
    if (!isSoundPlaying(SE_UNK_10b)) PlaySound(SE_UNK_10b);
    SetStageNoiseVolume(SE_UNK_10b);
  } else {
    if (isSoundPlaying(SE_UNK_10b)) StopSound(SE_UNK_10b);
  }
}

static void repairFactory_0800d8c0(Coords32* _ UNUSED) {
  RequestGraphicTransfer(&(TILESETS(18, 33)[(STAGE.unk_001 << 1) / 3]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 33)[(STAGE.unk_001 << 1) / 3]).pal, 0);

  RequestGraphicTransfer(&(TILESETS(18, 37)[STAGE.unk_002 / 9]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 37)[STAGE.unk_002 / 9]).pal, 0);

  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 4)) {
    if (gMissionDones & (1 << STAGE_MISSILE_FACTORY)) {
      RequestGraphicTransfer(&(TILESETS(18, 0)[92]).g, (void*)0x4000);
      LoadPalette(&(TILESETS(18, 0)[92]).pal, 0);
    }
  }
}

static void exitRepairFactory(Coords32* _ UNUSED) {
  RemovePaletteAnimation(43);
  RemovePaletteAnimation(44);
  RemovePaletteAnimation(45);
  RemovePaletteAnimation(46);
  RemovePaletteAnimation(47);
  RemovePaletteAnimation(48);
  if (isSoundPlaying(SE_UNK_10b)) StopSound(SE_UNK_10b);
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* stage);
static void LayerUpdate_3(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[4] = {
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
    [2] = {
      [LAYER_UPDATE] = LayerUpdate_2,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [3] = {
      [LAYER_UPDATE] = LayerUpdate_3,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

// 0x0800da04
static void LayerUpdate_2(struct StageLayer* l, const struct Stage* stage) {
  s32 chunkX;

  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | BGCNT_PRIORITY(2);
    (l->scrollPower).x = 0xC0;
    (l->scrollPower).y = 0xC0;
    l->phase++;
  }

  chunkX = gScreenX[(l->viewportLeftTopPixel).x >> 4];
  if (chunkX < 6) {
    (l->scrollPower).y = 0x100;
    (l->scroll).x = 120;
  } else if (chunkX < 17) {
    (l->scroll).x = 960;
    (l->scroll).y = 200;
  } else if (chunkX < 20) {
    (l->scroll).x = 1080;
    (l->scroll).y = 140;
  } else {
    (l->scroll).x = 1752;
    (l->scroll).y = 200;
  }
}

// 0x0800da80
static void LayerUpdate_3(struct StageLayer* l, const struct Stage* stage) {
  s32 x = gScreenX[(l->viewportLeftTopPixel).x >> 4];
  if (x < 6) {
    (l->scrollPower).x = 0x40;
    (l->scrollPower).y = 0x100;
    (l->scroll).x = 360;
  } else if (x < 15) {
    (l->scroll).x = 1560;
    (l->scroll).y = 320;
  } else if (x < 17) {
    (l->scroll).x = 1920;
    (l->scroll).y = 400;
  } else if (x < 20) {
    (l->scroll).x = 2160;
    (l->scroll).y = 280;
  } else if (x < 28) {
    (l->scroll).x = 3000;
    (l->scroll).y = 400;
  } else {
    (l->scroll).x = 3504;
    (l->scroll).y = 400;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

// 0x0800DAEC
bool16 FUN_0800daec(s32 x, s32 y) {
  if (x >= PIXEL(1680) && x < PIXEL(1680 + 480)) {
    if (y >= PIXEL(640) && y < PIXEL(960)) {
      struct Overworld* ow = &gOverworld;
      if (GET_METATILE(&ow->terrain, x >> 12, y >> 12) != GET_METATILE(&ow->terrain, x >> 12, (y - PIXEL(640)) >> 12)) {
        Coords32 c = {x, y};
        if (x < PIXEL(1680 + 240)) {
          LoadChunk(7, 4, 54);
        } else {
          LoadChunk(8, 4, 55);
        }
        AppendQuake(8, &c);
        return TRUE;
      }
    }
  }
  return FALSE;
}

#undef STAGE

// ------------------------------------------------------------------------------------------------------------------------------------

#include "stage/repair_factory/layer.h"
//
#include "stage/repair_factory/landscape.h"
