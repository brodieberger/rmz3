// Zero 2's PLANT2 AKA Shuttle Factory

#include "ap_import.h"
#include "gba/gba.h"
#include "collision.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "zero.h"
#include "constants/song.h"

#if AP

extern const ColorGraphic gApZ2Plant2_TileAnim[10];

#define TILESET(n) (gOverworld.terrain.tilesets[n])

// 0x0800f308
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2Plant2State* w = &gOverworld.work.apZ2Plant2;
  w->clock = 0;
  w->music = gStageRun.checkpoint == 0 ? 0 : 2;
  w->time = 0;
}

/*
  0x0800f334, 0x080193e8: x 6224 music goes, 6256 room's plays, enemies swept away
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2Plant2State* w = &gOverworld.work.apZ2Plant2;
  s32 zero = (pZero2->s).coord.x;

  if (++w->clock > 95) w->clock = 0;
  if (++w->time == 45) w->time = 0;
  if (w->music == 0 && zero > PIXEL(6223)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(6255)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (zero > PIXEL(6255) && zero <= PIXEL(6479)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && zero > PIXEL(6479)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
}

// 0x0800f374: reactor glow, then tileset 5's
static void Stage_Draw(Coords32* _ UNUSED) {
  const ColorGraphic* g;
  u8 frame = gOverworld.work.apZ2Plant2.time / 9;
  if (TILESET(0) == 3) {
    g = &gApZ2Plant2_TileAnim[frame];
    RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
    LoadPalette(&g->pal, 0);
  }
  if (TILESET(1) == 5) {
    g = &gApZ2Plant2_TileAnim[5 + frame];
    RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
    LoadPalette(&g->pal, 0);
  }
}

static void Stage_Exit(Coords32* _ UNUSED) {}

const StageFunc gApZ2Plant2_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013e8c: spawn areas
  0: the way through
  1: lower floors past x 5760
*/
u8 gApZ2Plant2_Area(Coords32* c) { return c->x > PIXEL(5760) && c->y < PIXEL(2240); }

// --------------------------------------------

// 0x0800f458
static void Back_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  if (gScreenX[l->viewportLeftTopPixel.x >> 4] > 25) {
    l->scrollPower.x = 224;
    l->scroll.x = 810;
  } else {
    l->scrollPower.y = 192;
    l->scroll.y = 400;
  }
  l->phase++;
}

// 0x0800f4b8
static void Near_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 screen;
  if (l->phase != 0) return;
  screen = gScreenX[l->viewportLeftTopPixel.x >> 4];
  if (screen <= 2) {
    l->scrollPower.x = 192;
    l->scroll.x = 60;
  } else if (screen <= 9) {
    l->scrollPower.x = 192;
    l->scroll.x = 480;
  } else if (screen <= 17) {
    l->scrollPower.x = 192;
    l->scroll.x = 720;
  } else if (screen > 25) {
    l->scrollPower.x = 192;
    l->scroll.x = 1620;
  } else {
    l->scrollPower.y = 128;
    l->scroll.y = 800;
  }
  l->phase++;
}

// clang-format off
const StageLayerRoutine gApZ2Plant2_LayerRoutines[4] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Back_Update, DrawGeneralStageLayer, NULL},
    [3] = {Near_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

// --------------------------------------------

// 0x0831ddb8: each crumbling floor cell's left edge and its patch
static const struct {
  s32 x;
  s32 y;
  s32 patch;
} sCells[19] = {
    {0x12B000, 0x93000, 0}, {0x12D000, 0x93000, 0}, {0x12F000, 0x93000, 0}, {0x135000, 0x92000, 0},
    {0x137000, 0x92000, 0}, {0x13B000, 0x91000, 0}, {0x13F000, 0x90000, 1}, {0x143000, 0x93000, 0},
    {0x145000, 0x93000, 0}, {0x149000, 0x92000, 0}, {0x14F000, 0x92000, 0}, {0x151000, 0x90000, 2},
    {0x153000, 0x90000, 3}, {0x155000, 0x90000, 4}, {0x15D000, 0x93000, 0}, {0x15F000, 0x93000, 0},
    {0x165000, 0x93000, 0}, {0x167000, 0x93000, 0}, {0x169000, 0x93000, 0},
};

// 0x0831df1c..0x0831df44
static const u16 sPatches[5][4] = {
    {2, 1, 0x403, 0x403}, {2, 1, 0x401, 0x401}, {2, 1, 0x412, 0x403}, {2, 1, 0x413, 0x401}, {2, 1, 0x405, 0x406},
};

// 0x0800f52c: floor cell under a slab gone
void ApZ2Plant2CellGone(const Coords32* at) {
  u8 i;
  for (i = 0; i < 19; i++) {
    if ((at->x >> 12) == (sCells[i].x >> 12) + 1) {
      PatchMetatileMap(sCells[i].x >> 12, sCells[i].y >> 12, sPatches[sCells[i].patch]);
      return;
    }
  }
}

#endif  // AP
