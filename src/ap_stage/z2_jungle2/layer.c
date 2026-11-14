// Zero 2's JUNGLE2 AKA Forest of Notus

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "overworld_layer_gfx.h"
#include "palette_animation.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Jungle2_PlttAnim101, gApZ2Jungle2_PlttAnim102, gApZ2Jungle2_PlttAnim103,
    gApZ2Jungle2_PlttAnim104, gApZ2Jungle2_PlttAnim105, gApZ2Jungle2_PlttAnim106, gApZ2Jungle2_PlttAnim107,
    gApZ2Jungle2_PlttAnim108, gApZ2Jungle2_PlttAnim109, gApZ2Jungle2_PlttAnim110, gApZ2Jungle2_PlttAnim111,
    gApZ2Jungle2_PlttAnim112, gApZ2Jungle2_PlttAnim113, gApZ2Jungle2_PlttAnim115;
extern const AnimCmd* const gApZ2Jungle2_PlttAnimScript101[], *const gApZ2Jungle2_PlttAnimScript102[],
    *const gApZ2Jungle2_PlttAnimScript103[], *const gApZ2Jungle2_PlttAnimScript104[],
    *const gApZ2Jungle2_PlttAnimScript105[], *const gApZ2Jungle2_PlttAnimScript106[],
    *const gApZ2Jungle2_PlttAnimScript107[], *const gApZ2Jungle2_PlttAnimScript108[],
    *const gApZ2Jungle2_PlttAnimScript109[], *const gApZ2Jungle2_PlttAnimScript110[],
    *const gApZ2Jungle2_PlttAnimScript111[], *const gApZ2Jungle2_PlttAnimScript112[],
    *const gApZ2Jungle2_PlttAnimScript113[], *const gApZ2Jungle2_PlttAnimScript115[];
extern const ColorGraphic gApZ2Jungle_TileAnim[3];  // sky's flashes, the Jungle's art
extern const ColorGraphic gApZ2Jungle2_TileAnim[1];
extern const u16 gApZ2Jungle_Water0Map[], gApZ2Jungle_Water1Map[];
extern const GameCommand gApZ2Jungle2_FightScript[], gApZ2Jungle2_FightReturnScript[], gApZ2Jungle2_SceneScript[];
struct Entity* ApZ2CreateSplash(const Coords32* at, u8 kind);

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Jungle2_PlttAnim##n, gApZ2Jungle2_PlttAnimScript##n)
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

// 0x0800ded8
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2Jungle2State* w = &gOverworld.work.apZ2Jungle2;
  w->flash = 0;
  w->burnt = FALSE;
  w->music = gStageRun.checkpoint == 2 ? 2 : 0;
  w->returning = gStageRun.checkpoint == 2;
  w->fight = FALSE;
  w->scene = FALSE;
  w->leaf = NULL;
  gOverworld.state[0] = 0;
}

/*
  0x0800df0c, 0x08018604: x 7904 music goes, 7936 room's plays and enemies swept, 8160 Elpizo and
  the frog, 8400 clear scene
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2Jungle2State* w = &gOverworld.work.apZ2Jungle2;
  s32 zero = (pZero2->s).coord.x;

  ANIMATE(TILESET(1) == 2, 106);
  ANIMATE(TILESET(1) == 2, 107);
  ANIMATE(TILESET(1) == 2, 108);
  ANIMATE(TILESET(1) == 2, 109);
  ANIMATE(TILESET(1) == 2, 110);
  ANIMATE(TILESET(1) == 2, 111);
  ANIMATE(TILESET(0) == 3, 112);
  ANIMATE(TILESET(0) == 3, 113);
  ANIMATE(TILESET(0) == 3, 115);
  ANIMATE(TILESET(0) == 0, 102);
  ANIMATE(TILESET(0) == 0, 104);
  ANIMATE(TILESET(0) == 0, 105);
  if (TILESET(0) == 0) {
    if (++w->flash == 190) w->flash = 0;
  } else {
    w->flash = 0;
  }
  ANIMATE(TILESET(1) == 1, 101);
  ANIMATE(TILESET(1) == 1, 103);

  if (w->music == 0 && zero >= PIXEL(7904)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero >= PIXEL(7936)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (gStageRun.stageEventPhase == 3 && !w->fight) {
    if (zero >= PIXEL(8160)) {
      gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
      SetScript(&gStageRun.vm, w->returning ? gApZ2Jungle2_FightReturnScript : gApZ2Jungle2_FightScript);
      w->fight = TRUE;
    } else if (zero >= PIXEL(7936)) {
      gCollisionManager.sweep |= 1 << FACTION_ENEMY;
    }
  }
  if (gStageRun.stageEventPhase == 4) gStageRun.stageEventPhase = 5;
  if (gStageRun.stageEventPhase == 5 && !w->scene && !(gStageRun.vm.active & VM_ACTIVE)) {
    gCollisionManager.disabled &= ~COLLMAN_DISABLED;
    gCollisionManager.sweep = 0;
    if (zero >= PIXEL(8400)) {
      SetScript(&gStageRun.vm, gApZ2Jungle2_SceneScript);
      gStageRun.missionStatus &= ~MISSION_STAY;
      w->scene = TRUE;
    }
  }
  if (w->leaf == NULL) w->leaf = CreateLeafBurn(1);
}

// 0x0800e1bc: tileset 3's palettes, then sky flashes, three frames on timer
static void Stage_Draw(Coords32* _ UNUSED) {
  static const u8 sFlashes[6][2] = {{160, 0}, {176, 1}, {180, 2}, {184, 0}, {251, 1}, {255, 2}};
  u8 t = gOverworld.work.apZ2Jungle2.flash;
  u16 i = 0;
  const ColorGraphic* g;

  if (TILESET(0) == 3) LoadPalette(&gApZ2Jungle2_TileAnim[0].pal, 0);
  if (TILESET(0) != 0) return;
  while (t > sFlashes[i][0]) i++;
  g = &gApZ2Jungle_TileAnim[sFlashes[i][1]];
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

// 0x0800e278
static void Stage_Exit(Coords32* _ UNUSED) {
  struct Solid* leaf = gOverworld.work.apZ2Jungle2.leaf;
  REMOVE(101);
  REMOVE(102);
  REMOVE(103);
  REMOVE(104);
  REMOVE(105);
  REMOVE(106);
  REMOVE(107);
  REMOVE(108);
  REMOVE(109);
  REMOVE(110);
  REMOVE(111);
  REMOVE(112);
  REMOVE(113);
  REMOVE(115);
  if (leaf != NULL) {
    (leaf->s).flags &= ~DISPLAY;
    (leaf->s).flags &= ~FLIPABLE;
    EXIT_BODY(leaf);
    SET_SOLID_ROUTINE(leaf, ENTITY_DISAPPEAR);
  }
}

const StageFunc gApZ2Jungle2_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013d58
u8 gApZ2Jungle2_Area(Coords32* c) {
  if ((u32)(c->x - PIXEL(480)) > 0x1E8000) return 7;
  if (c->x > PIXEL(8032)) return 6;
  if (c->x < PIXEL(1792)) return 0;
  if (c->x < PIXEL(2880)) return 1;
  if ((u32)(c->x - 0x12C001) <= 0x15FFE) return 3;
  return 2;
}

// 0x0800e964: canopy over forest, terrain's own map 800 px lower
metatile_attr_t ApZ2Jungle2Canopy(s32 x, s32 y) {
  u16* map = gOverworld.terrain.tilemap;
  if ((u32)(y - PIXEL(320)) > 0x1DFFF) return 0;
  return map[MAP_OFFSET(map, x >> 12, (y + PIXEL(800)) >> 12)];
}

// 0x0800e9ac
void ApZ2Jungle2Burn(s32 x, s32 y) {
  static const u16 sBurnt[3] = {1, 1, 0};
  if ((u32)(y - PIXEL(320)) > 0x1DFFF) return;
  gOverworld.work.apZ2Jungle2.burnt = TRUE;
  PatchMetatileMap(x >> 12, (y + PIXEL(800)) >> 12, sBurnt);
  gOverworld.terrain.tilemap_duty = FALSE;
}

// --------------------------------------------

// 0x0800e320: whole layer drawn once
static void Backdrop_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  PixelCoords origin = {0, 0};
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  FUN_08005a70(&l->gfx, &origin, SCREEN_ADDR(n));
  UpdateBGOFS(&l->gfx, BGOFS(n));
  l->phase++;
}

// 0x0800e378
static void Back_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  l->phase++;
}

// 0x0800e3ac
static void Canopy_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct LayerGraphic* g = &l->gfx;
  PixelCoords c;
  u32 dx = l->viewportLeftTopPixel.x - l->prevViewportLeftTopPixel.x + 15;
  u32 dy = l->viewportLeftTopPixel.y - l->prevViewportLeftTopPixel.y + 15;
  c.x = (l->drawPivotOffset.x >> 8) + l->viewportLeftTopPixel.x;
  c.y = (l->drawPivotOffset.y >> 8) + l->viewportLeftTopPixel.y + 800;
  if (dx >= 31 || dy >= 31 || gOverworld.work.apZ2Jungle2.burnt) {
    FUN_08006ae0(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  } else {
    FUN_08006bb4(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  }
  gOverworld.work.apZ2Jungle2.burnt = FALSE;
  UpdateBGOFS(g, BGOFS(l->bgIdx >> 4));
}

// 0x0800e484: in front of terrain, 1:1
static void Front_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    u16 n = (u16)l->bgIdx >> 4;
    BGCNT16(n) = (BGCNT16(n) & ~3) | 1;
    l->scrollPower.x = l->scrollPower.y = 0x100;
    l->scroll.x = l->scroll.y = 0;
    l->phase++;
  }
}

#define WATER_TIME l->work.raw[16]
#define WATER_FALL (*(struct Entity**)&l->work.raw[0])
#define WATER_TOP (*(struct Entity**)&l->work.raw[4])
#define WATER_AT (*(Coords32*)&l->work.raw[8])
#define SEA_LOW 0x1E800

// 0x0831ab18
static const Coords32 sWaterFallAt = {PIXEL(5024), PIXEL(371)};

static void hideEntity(struct Entity* e) { e->flags &= ~(DISPLAY | FLIPABLE); }

static void removeSplash(struct Entity* e) {
  if (e == NULL) return;
  hideEntity(e);
  SET_VFX_ROUTINE((struct VFX*)e, ENTITY_DISAPPEAR);
}

static s32 waterScroll(struct StageLayer* l) {
  s32 y = l->viewportLeftTopPixel.y - (gOverworld.sea >> 8) + 8;
  if (y < -180) y = -180;
  if (y > 0) y = 0;
  return y;
}

/*
  0x0800e4c8: mid-boss's room.
  gOverworld.state[0]:
    0: water at low line
    1: mid-boss's flood, up to y 320
    2: mid-boss beaten, draining
*/
static void Water_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  u8 state = gOverworld.state[0];
  s32 y;

  if (l->phase == 0) {
    BGCNT16(n) = (u16)(l->screenBase | 0x8044);
    CpuFastSet(gApZ2Jungle_Water0Map, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
    CpuFastSet(gApZ2Jungle_Water1Map, (u8*)SCREEN_ADDR(n) + BG_SCREEN_SIZE, BG_SCREEN_SIZE / 4);
    gBlendRegBuffer.bldclt = 0x3B44;
    gBlendRegBuffer.bldalpha = 0xC0C;
    gWindowRegBuffer.dispcnt |= DISPCNT_WIN1_ON;
    gWindowRegBuffer.winin[1] = 0xFF;
    gWindowRegBuffer.winin[2] |= 14;
    WATER_FALL = NULL;
    WATER_TOP = NULL;
    WATER_AT.x = PIXEL(5024);
    WATER_TIME = 0;
    gOverworld.sea = SEA_LOW;
    gVideoRegBuffer.dispcnt |= l->bgIdx << 8;
    l->phase++;
  }

  if (state == 1) {
    if (WATER_TIME < 24) {
      if (gOverworld.sea < SEA_LOW) {
        gOverworld.sea += 0x100;
      } else {
        WATER_TIME++;
      }
    } else if (gOverworld.sea > PIXEL(320)) {
      gOverworld.sea -= 0x100;
    }
  } else if (state == 0) {
    if (gOverworld.sea < SEA_LOW) gOverworld.sea += 0x100;
    WATER_TIME = 0;
  } else {
    gOverworld.sea = gOverworld.sea < 0x28800 ? gOverworld.sea + 0x300 : 0x7FFFFFFF;
    WATER_TIME = 0;
  }

  WATER_AT.y = gOverworld.sea - 0x600;
  y = waterScroll(l);
  if ((u8)(WATER_TIME - 1) < 23) {
    u8 half = WATER_TIME >> 1;
    gWindowRegBuffer.winin[1] = 0xFF;
    gWindowRegBuffer.winin[2] = (gWindowRegBuffer.winin[2] | 10) & ~4;
    gWindowRegBuffer.winH.half[1] = ((half + 226) & 0xFF) | ((225 - half) << 8);
    gWindowRegBuffer.winV.half[1] = 0x34A0;
  } else {
    gWindowRegBuffer.winin[1] = 0xFB;
    gWindowRegBuffer.winin[2] |= 14;
    gWindowRegBuffer.winH.half[1] = 240;
  }
  if (y < -51 && state == 1) {
    if (WATER_TIME != 0) {
      if (WATER_FALL == NULL) WATER_FALL = ApZ2CreateSplash(&sWaterFallAt, 1);
      if (WATER_TOP == NULL) {
        WATER_TOP = ApZ2CreateSplash(&WATER_AT, 0);
        PlaySound(SE_Z2_WATER);
      }
    }
    if (WATER_TIME > 23) gWindowRegBuffer.winV.half[1] = 51;
    if (WATER_TIME == 0) gWindowRegBuffer.winV.half[1] = -y & 0xFF;
  } else {
    if (WATER_TOP != NULL) StopSound(SE_Z2_WATER);
    removeSplash(WATER_FALL);
    removeSplash(WATER_TOP);
    WATER_FALL = NULL;
    WATER_TOP = NULL;
    gWindowRegBuffer.winV.half[1] = -y & 0xFF;
  }
  BGnHOFS(n) = -208;
  BGnVOFS(n) = y;
}

// 0x0800e834: lines above water show nothing, by HBlank DMA
static void Water_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  s32 y = waterScroll(l);
  u16* lines = Malloc(DISPLAY_HEIGHT * 2);
  s32 i = 0;

  if (lines == NULL) return;
  gIntrManager.reservedDma0[0] = (u32)lines;
  gIntrManager.reservedDma0[1] = REG_ADDR_BG2VOFS;
  gIntrManager.reservedDma0[2] = 0xA2600001;
  for (; i < -y && i < DISPLAY_HEIGHT; i++) lines[i] = 0x100;
  for (; i < DISPLAY_HEIGHT; i++) lines[i] = y;
}

// 0x0800e8d0
static void Water_Exit(struct StageLayer* l, const struct Stage* _ UNUSED) {
  removeSplash(WATER_FALL);
  removeSplash(WATER_TOP);
  StopSound(SE_Z2_WATER);
  gOverworld.sea = 0x7FFFFFFF;
  gBlendRegBuffer.bldclt = 0;
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 14;
}

/*
  Zero 2's layer routines for this stage
  2: backdrop, drawn once
  3: behind terrain
  4: canopy
  5: in front, 1:1
  6: mid-boss's water
*/
// clang-format off
const StageLayerRoutine gApZ2Jungle2_LayerRoutines[7] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, Backdrop_Draw, NULL},
    [3] = {Back_Update, DrawGeneralStageLayer, NULL},
    [4] = {NULL, Canopy_Draw, NULL},
    [5] = {Front_Update, DrawGeneralStageLayer, NULL},
    [6] = {Water_Update, Water_Draw, Water_Exit},
};
// clang-format on

// --------------------------------------------

#define ELPIZO(n) MOTION(DM205_Z2_ELPIZO, (n))
#define ELPIZO_TILE 912
#define FLAGS (s->scriptEntity->flags)

static const struct PreloadEntity sXSheet = {AP_SHEET_Z2_X, 0, 784, 8, 0, AP_PRELOAD_SHEET, 0};

// clang-format off
#define ROUTINE(name, init, update) \
const SolidRoutine name = { \
    [ENTITY_INIT] =      (SolidFunc)init, \
    [ENTITY_UPDATE] =    (SolidFunc)update, \
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity, \
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity, \
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity, \
}
// clang-format on

static void placeElpizo(struct Entity* s) {
  wDynamicGraphicTilenums[DM205_Z2_ELPIZO] = ELPIZO_TILE;
  wDynamicMotionPalIDs[DM205_Z2_ELPIZO] = 9;
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
}

/*
  Zero 2's solid 5 work0 33, Elpizo after the Dark Elf's key
  flags: 1 turns, 2 laughs, 4 runs off right
*/
static void ForestElpizo_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, ELPIZO(12));
      SET_XFLIP(p, TRUE);
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (FLAGS & 1) s->mode[1]++;
      break;
    case 2:
      SetSpriteAnimation(p, ELPIZO(9));
      SET_XFLIP(p, FALSE);
      s->work[2] = 8;
      s->mode[1]++;
      FALLTHROUGH;
    case 3:
      UpdateSpriteAnimation(p);
      if (--s->work[2] != 0) break;
      SetSpriteAnimation(p, ELPIZO(8));
      s->mode[1]++;
      break;
    case 4:
      UpdateSpriteAnimation(p);
      if (FLAGS & 2) {
        FLAGS &= ~2;
        SetSpriteAnimation(p, ELPIZO(16));
      }
      if (!(FLAGS & 4)) break;
      SetSpriteAnimation(p, ELPIZO(28));
      s->work[2] = 34;
      s->mode[1]++;
      break;
    case 5:
      UpdateSpriteAnimation(p);
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      s->coord.x += 0x380;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= 0x3FFF) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// 0x080c5e78
static void ForestElpizo_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  placeElpizo(s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  ForestElpizo_Update(p);
}

ROUTINE(gApZ2ForestElpizoRoutine, ForestElpizo_Init, ForestElpizo_Update);

/*
  Zero 2's solid 5 work0 35, Elpizo with the seal broken
  flags: 1 laughs, 2 flashes and beams out
*/
static void SealElpizo_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, ELPIZO(15));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (!(FLAGS & 1)) break;
      SetSpriteAnimation(p, ELPIZO(16));
      s->mode[1]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (!(FLAGS & 2)) break;
      s->work[2] = 30;
      s->mode[1]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if (s->work[2] & 1) {
        PaintEntityWhite(s);
      } else {
        UpdateEntityPaletteID(s);
      }
      if (--s->work[2] != 0) break;
      PlaySound(SE_TENSOU_BACK);
      s->work[2] = 8;
      s->mode[1]++;
      break;
    case 4:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = 288 - s->work[2] * 4;
      (s->spr).mag.y = s->work[2] * 4 + 224;
      if (--s->work[2] != 0) break;
      s->work[2] = 4;
      s->mode[1]++;
      break;
    case 5:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = s->work[2] * 64 + 32;
      (s->spr).mag.y = 352 - s->work[2] * 32;
      if (--s->work[2] != 0) break;
      s->d.y = -0xC00;
      s->mode[1]++;
      break;
    case 6:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = 32;
      s->d.y -= 64;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= 0x3000) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// 0x080c61b0
static void SealElpizo_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  InitScalerotMotion1(s);
  placeElpizo(s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  SealElpizo_Update(p);
}

ROUTINE(gApZ2SealElpizoRoutine, SealElpizo_Init, SealElpizo_Update);

/*
  Zero 2's solid 5 work0 36, X as a cyber elf, circling his spot. Drawn at unk_coord
  flags: 1 rises off floor, 2 leaves upward
*/
static void XGlow_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_X, 0));
      s->work[2] = 0;
      s->work[3] = 4;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (!(FLAGS & 1)) break;
      s->coord.y -= 64;
      if (s->work[3] < 16) s->work[3]++;
      if (s->coord.y < FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(40)) s->mode[1]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (s->work[3] < 16) s->work[3]++;
      if (!(FLAGS & 2)) break;
      s->coord.y -= 192;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= 0xFFF) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
  s->work[2]++;
  if (s->work[3] < 7) s->work[2] += 31;
  s->unk_coord.x = s->coord.x + COS(s->work[2]) * (s->work[3] >> 1);
  s->unk_coord.y = s->coord.y - SIN(s->work[2] * 2) * (s->work[3] >> 2);
}

// 0x080c6380
static void XGlow_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  (s->spr).c = (struct Coord*)&s->unk_coord;
  ApLoadSheet(&sXSheet);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  XGlow_Update(p);
}

ROUTINE(gApZ2XGlowRoutine, XGlow_Init, XGlow_Update);

#endif  // AP
