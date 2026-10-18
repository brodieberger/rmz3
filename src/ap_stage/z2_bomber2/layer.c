// Zero 2's BOMBER2 AKA Crystal Cave: stage and layer routines

#include "ap_import.h"
#include "gba/gba.h"
#include "gfx.h"
#include "global.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "overworld_layer_gfx.h"
#include "overworld_terrain.h"
#include "palette_animation.h"

#if AP

/*
  Palette animation for each tileset
  133 for most of the cave, 134 for the crystal corridors, 
  135 for the purple building, and 138 for the lightning in the outdoor sky.
*/

extern const PlttAnimData gApImp0_PlttAnim133, gApImp0_PlttAnim134, gApImp0_PlttAnim135,
    gApImp0_PlttAnim138;
extern const AnimCmd* const gApImp0_PlttAnimScript133[], *const gApImp0_PlttAnimScript134[],
    *const gApImp0_PlttAnimScript135[], *const gApImp0_PlttAnimScript138[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

static void Stage_Nop(Coords32* _ UNUSED) {}

// 0x0800ebe0
static void Stage_Update(Coords32* _ UNUSED) {
  animate(TILESET_IDX(1) == 9, PLTT_ANIM_ID(133), &gApImp0_PlttAnim133, gApImp0_PlttAnimScript133);
  animate(TILESET_IDX(1) == 10, PLTT_ANIM_ID(134), &gApImp0_PlttAnim134, gApImp0_PlttAnimScript134);
  animate(TILESET_IDX(1) == 4, PLTT_ANIM_ID(135), &gApImp0_PlttAnim135, gApImp0_PlttAnimScript135);
  animate(TILESET_IDX(0) == 11, PLTT_ANIM_ID(138), &gApImp0_PlttAnim138, gApImp0_PlttAnimScript138);
}

// 0x0800ef6c
static void Stage_Exit(Coords32* _ UNUSED) {
  RemovePaletteAnimation(PLTT_ANIM_ID(133));
  RemovePaletteAnimation(PLTT_ANIM_ID(134));
  RemovePaletteAnimation(PLTT_ANIM_ID(135));
  RemovePaletteAnimation(PLTT_ANIM_ID(138));
}

const StageFunc gApImp0_StageRoutines[4] = {
    Stage_Nop,
    Stage_Update,
    Stage_Nop,
    Stage_Exit,
};

/*
  0x08013dc0: the stage's spawn areas,
  0: top of the cave
  1: middle of the cave
  2: lower corridor
  3: purple building, outdoor strip and the rest
  4: room at the bottom of the cave
  5, 6, 7: lower half of the building and the plant underneath.
*/
u8 gApImp0_Area(Coords32* c) {
  s32 x = c->x, y = c->y;
  if (x > PIXEL(960) && x < PIXEL(1440) && y > PIXEL(2080) && y < PIXEL(2240)) return 4;
  if (x < PIXEL(3120)) {
    if (y < PIXEL(960)) return 0;
    if (y < PIXEL(2240)) return 1;
  }
  if (x < PIXEL(3600) && y >= PIXEL(2240)) return 2;
  if (x <= PIXEL(3840) || x >= PIXEL(6000) || y <= PIXEL(1280)) return 3;
  if (x > PIXEL(4080) && x <= PIXEL(4336) && y < PIXEL(1440)) return 7;
  return (y > PIXEL(2240)) ? 6 : 5;
}

/*
  The red and blue crystal pillars. Glows red and blue based on if they are lit by Hottalook enemies.
*/

static const u16 sCrystalColors[2][16] = {
    // 0x0831d120 (red) and 0x0831d140 (blue)
    {0x0000, 0x808A, 0x88AE, 0x94D1, 0x9CF5, 0x9CF9, 0xA117, 0xA959,
     0xA53C, 0xA97C, 0xB19E, 0xB9DF, 0xC21F, 0xCE7F, 0xDAFF, 0xEF7F},
    {0x0000, 0xAC80, 0xB8A2, 0xC4C4, 0xD0E7, 0xD507, 0xDD28, 0xE529,
     0xE94A, 0xF16A, 0xF98B, 0xF9EE, 0xFA51, 0xFEB4, 0xFF18, 0xFF7B},
};

static_assert((u32) & ((struct StageLayer*)0)->bgIdx == 0x5C);
static_assert((u32) & ((struct StageLayer*)0)->viewportLeftTopPixel == 0x34);
static_assert((u32) & ((struct StageLayer*)0)->scrollPower == 0x44);

#define LEVEL_RED unk_10
#define LEVEL_BLUE unk_12

static void fade(u16* level, bool8 lit) {
  if (lit) {
    if (*level < 64) (*level)++;
  } else if (*level != 0) {
    (*level)--;
  }
}

// 0x0800ef98
static void Crystals_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2Bomber2State* w = &gOverworld.work.apZ2Bomber2;
  if (l->phase == 0) {
    gBlendRegBuffer.bldclt = (u16)l->bgIdx | 0x3F40;
    gBlendRegBuffer.bldalpha = 0x1010;
    l->LEVEL_RED = l->LEVEL_BLUE = 0;
    w->lit[0] = w->lit[1] = FALSE;
    l->phase++;
  }
  fade(&l->LEVEL_RED, w->lit[0]);
  fade(&l->LEVEL_BLUE, w->lit[1]);
  w->lit[0] = w->lit[1] = FALSE;
}

static void scale(u16* dst, const u16* src, u16 level) {
  s16 i;
  for (i = 0; i < 16; i++) {
    u16 c = src[i];
    dst[i] = (((c & 31) * level) >> 6) | ((((c >> 5) & 31) * level >> 6) << 5) |
             ((((c >> 10) & 31) * level >> 6) << 10);
  }
}

// 0x0800f050
static void Crystals_Draw(struct StageLayer* l, const struct Stage* stage) {
  scale(&gPaletteManager.buf[11 * 16], sCrystalColors[0], l->LEVEL_RED);
  scale(&gPaletteManager.buf[12 * 16], sCrystalColors[1], l->LEVEL_BLUE);
  DrawGeneralStageLayer(l, stage);
}

// 0x0800f11c
static void Crystals_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gBlendRegBuffer.bldclt = 0;
}

/*
  0x0800f218: cave's background.
*/
static void CaveBackground_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 cx, cy;
  if (l->phase != 0) return;
  cx = gScreenX[l->viewportLeftTopPixel.x >> 4];
  cy = gScreenY[l->viewportLeftTopPixel.y >> 4];
  if (cy <= 4) {
    l->scrollPower.x = l->scrollPower.y = 128;
    l->scroll.x = 120, l->scroll.y = 320;
  } else if (cx <= 13) {
    l->scrollPower.x = 192;
    l->scroll.x = 240;
  } else if (cx > 16 && cy >= 8 && cy <= 9) {
    l->scrollPower.x = 192;
    l->scroll.x = 1200;
  } else if (cx > 15 && cy >= 11 && cy <= 12) {
    l->scrollPower.x = 192;
    l->scroll.x = 1080;
  } else {
    l->scrollPower.x = l->scrollPower.y = 128;
    l->scroll.x = 1680, l->scroll.y = 960;
  }
  l->phase++;
}

// 0x0800f128: outdoor sky.
static void Sky_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  PixelCoords origin = {0, 0};
  if (l->phase != 0) return;
  FUN_08005a70(&l->gfx, &origin, SCREEN_ADDR(l->bgIdx >> 4));
  UpdateBGOFS(&l->gfx, BGOFS(l->bgIdx >> 4));
  l->phase++;
}

// 0x0800f184
static void Clear_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  RequestVRAMFill(0, (void*)SCREEN_BASE(l->bgIdx >> 4), BG_SCREEN_SIZE * 2);
  l->phase++;
}

// 0x0800f1d8 and 0x0800f1f8: purple building
static void Chunk178_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  LoadChunk(16, 8, 178);
  l->phase++;
}

static void Chunk131_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  LoadChunk(16, 8, 131);
  l->phase++;
}

// 0x0800f2ac: turns the layer off on the outdoor strip
static void Off_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  const u16 n = l->bgIdx >> 4;
  if (l->phase != 0) return;
  BGCNT16(n) = l->screenBase | BGCNT_MOSAIC | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(2);
  RESET_BGOFS(n);
  RequestVRAMFill(0x41DC41DC, (void*)SCREEN_BASE(n), BG_SCREEN_SIZE);
  gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
  l->phase++;
}

/*
  Zero 2's layer routines for this stage, 
  2: crystals
  3: outdoor sky
  7: cave background
*/
// clang-format off
const StageLayerRoutine gApImp0_LayerRoutines[9] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Crystals_Update, Crystals_Draw, Crystals_Exit},
    [3] = {NULL, Sky_Draw, NULL},
    [4] = {Clear_Update, DrawGeneralStageLayer, NULL},
    [5] = {Chunk178_Update, DrawGeneralStageLayer, NULL},
    [6] = {Chunk131_Update, DrawGeneralStageLayer, NULL},
    [7] = {CaveBackground_Update, DrawGeneralStageLayer, NULL},
    [8] = {Off_Update, NULL, NULL},
};
// clang-format on

#endif  // AP
