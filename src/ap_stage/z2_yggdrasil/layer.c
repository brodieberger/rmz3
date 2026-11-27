// Zero 2's YGGR-DRASILL AKA Yggdrasil

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "overworld_layer_gfx.h"
#include "palette_animation.h"
#include "random.h"
#include "renderer.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"
#include "game.h"
#include "constants/ap_z2_songs.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Yggdrasil_PlttAnim65, gApZ2Yggdrasil_PlttAnim66, gApZ2Yggdrasil_PlttAnim67,
    gApZ2Yggdrasil_PlttAnim68, gApZ2Yggdrasil_PlttAnim69, gApZ2Yggdrasil_PlttAnim70, gApZ2Yggdrasil_PlttAnim71,
    gApZ2Yggdrasil_PlttAnim72, gApZ2Yggdrasil_PlttAnim73, gApZ2Yggdrasil_PlttAnim74;
extern const AnimCmd* const gApZ2Yggdrasil_PlttAnimScript65[], *const gApZ2Yggdrasil_PlttAnimScript66[],
    *const gApZ2Yggdrasil_PlttAnimScript67[], *const gApZ2Yggdrasil_PlttAnimScript68[],
    *const gApZ2Yggdrasil_PlttAnimScript69[], *const gApZ2Yggdrasil_PlttAnimScript70[],
    *const gApZ2Yggdrasil_PlttAnimScript71[], *const gApZ2Yggdrasil_PlttAnimScript72[],
    *const gApZ2Yggdrasil_PlttAnimScript73[], *const gApZ2Yggdrasil_PlttAnimScript74[];
extern const ColorGraphic gApZ2Yggdrasil_TileAnim[5];
extern const u16 gApZ2Yggdrasil_Layer3Map[], gApZ2Yggdrasil_PlatformMap[], gApZ2Yggdrasil_SkyMap[], gApZ2Yggdrasil_SkyTiles[],
    gApZ2Yggdrasil_SkyPal[], gApZ2Yggdrasil_BlastTiles[], gApZ2Yggdrasil_BlastPal[];
extern const u8 gApZ2Yggdrasil_BlastShades[9][16][16];
extern const u16 gApZ2HatchPatch[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Yggdrasil_PlttAnim##n, gApZ2Yggdrasil_PlttAnimScript##n)
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])
#define SHOW_BACKDROP (gOverworld.state[1])

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

// 0x080106ec
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  gOverworld.state[2] = 0;
  SHOW_BACKDROP = 0;
  w->farX = PIXEL(720);
  w->farY = PIXEL(384);
  w->altBackdrop = FALSE;
  w->sway = 0;
  w->anchor = NULL;
}

// 0x08010748
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  ANIMATE(TILESET(0) == 0, 65);
  ANIMATE(TILESET(0) == 0, 66);
  ANIMATE(TILESET(0) == 0, 67);
  ANIMATE(TILESET(0) == 0, 68);
  ANIMATE(TILESET(1) == 2, 70);
  ANIMATE(TILESET(0) == 3 && !w->altBackdrop, 71);
  ANIMATE(TILESET(0) == 3 && w->altBackdrop, 72);
  ANIMATE(TILESET(0) == 3 && w->altBackdrop, 73);
}

static void Stage_Exit(Coords32* _ UNUSED) {
  REMOVE(65);
  REMOVE(66);
  REMOVE(67);
  REMOVE(68);
  REMOVE(70);
  REMOVE(71);
  REMOVE(72);
  REMOVE(73);
}

static void Stage_Draw(Coords32* _ UNUSED) {}

const StageFunc gApZ2Yggdrasil_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013f54
u8 gApZ2Yggdrasil_Area(Coords32* c) {
  if (c->x > PIXEL(1440)) return 3;
  if (c->y > PIXEL(3200)) return 0;
  if (c->y <= PIXEL(1760)) return 2;
  return 1;
}

// --------------------------------------------

#define LIGHT (*(u16*)l->work.raw)

static void createBlast(s32 x, s32 y);

static void loadSky(void) {
  RequestBgMapTransfer((u16*)gApZ2Yggdrasil_SkyTiles, BG_CHAR_OFFSET(1), 13312);
  CpuCopy16(gApZ2Yggdrasil_SkyPal, &gPaletteManager.buf[2 * 16], 224);
}

// 0x08010960: green trail in front till the seal blows: fades, blasts, then holds the sky
static void Event_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  u16 n = (u16)l->bgIdx >> 4;
  s32 x, y;
  switch (l->phase) {
    case 0:
      BGCNT16(n) = (BGCNT16(n) & ~3) | 2;
      w->altBackdrop = FALSE;
      w->reloadSky = FALSE;
      gBlendRegBuffer.bldclt = 0x3F4C;
      gBlendRegBuffer.bldalpha = 0x1010;
      l->unk_10 = 64;
      l->phase++;
      FALLTHROUGH;
    case 1:
      if (gOverworld.state[0] == 0) break;
      if (gOverworld.state[0] != 1) {
        l->phase = 5;
        break;
      }
      l->unk_10--;
      gBlendRegBuffer.bldalpha = 0x1000 | ((l->unk_10 >> 2) & 31);
      if (l->unk_10 != 0) break;
      gVideoRegBuffer.dispcnt &= ~(1 << (8 + n));
      l->unk_10 = 128;
      l->phase++;
      break;
    case 2:
      if ((RANDOM(RNG_0202f388) & 15) == 0) {
        PlaySound(SE_Z2_TANK_EXPLODE);
        x = (RANDOM(RNG_0202f388) & 7) + 12;
        y = (RANDOM(RNG_0202f388) & 3) + 10;
        createBlast(x, y);
      }
      if (--l->unk_10 != 0) break;
      l->unk_10 = 176;
      l->phase++;
      break;
    case 3:
      if ((l->unk_10 & 3) == 0) {
        x = (RANDOM(RNG_0202f388) & 7) + 12;
        y = (RANDOM(RNG_0202f388) & 3) + 10;
        createBlast(x, y);
        if ((l->unk_10 & 7) == 0) PlaySound(SE_Z2_TANK_EXPLODE);
      } else {
        x = RANDOM(RNG_0202f388) & 63;
        y = (RANDOM(RNG_0202f388) & 31) + 2;
        createBlast(x, y);
      }
      if (--l->unk_10 != 0) break;
      l->unk_10 = 16;
      l->phase++;
      break;
    case 4:
      if (--l->unk_10 == 0) l->phase++;
      break;
    case 5:
      BGCNT16(n) = (u16)(l->screenBase | 0x4046);
      RequestBgMapTransfer((u16*)gApZ2Yggdrasil_SkyMap, (void*)(SCREEN_BASE(n) + BG_SCREEN_SIZE), BG_SCREEN_SIZE);
      RequestVRAMFill(0, (void*)SCREEN_BASE(n), BG_SCREEN_SIZE);
      loadSky();
      LoadChunk(1, 1, 142);
      LoadChunk(2, 1, 110);
      LoadChunk(3, 1, 111);
      LoadChunk(4, 1, 144);
      LoadChunk(1, 2, 143);
      LoadChunk(2, 2, 126);
      LoadChunk(3, 2, 127);
      LoadChunk(4, 2, 145);
      if (gOverworld.state[2]) PatchMetatileMap(30, 29, gApZ2HatchPatch);
      gBlendRegBuffer.bldclt = 0x3F4C;
      gBlendRegBuffer.bldalpha = 0x1000;
      w->altBackdrop = TRUE;
      l->phase++;
      FALLTHROUGH;
    case 6:
      switch (SHOW_BACKDROP) {
        case 1:
          gVideoRegBuffer.dispcnt |= 1 << (8 + n);
          gBlendRegBuffer.bldalpha = 16;
          w->fade = 0;
          break;
        case 2:
          if (w->fade > 63) {
            gBlendRegBuffer.bldalpha = 0x1000;
            break;
          }
          gBlendRegBuffer.bldalpha = 16;
          w->fade++;
          break;
        case 3:
          gVideoRegBuffer.dispcnt |= 1 << (8 + n);
          gBlendRegBuffer.bldalpha = 16;
          if (w->fade != 0) w->fade--;
          break;
        default:
          gVideoRegBuffer.dispcnt &= ~(1 << (8 + n));
          break;
      }
      break;
  }
}

// 0x08010d5c
static void Event_Draw(struct StageLayer* l, const struct Stage* stage) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  u16 n = (u16)l->bgIdx >> 4;
  if (!w->altBackdrop) {
    DrawGeneralStageLayer(l, stage);
    return;
  }
  if (w->reloadSky) {
    w->reloadSky = FALSE;
    loadSky();
  }
  if (gOverworld.terrain.reload_graphic) w->reloadSky = TRUE;
  if (w->anchor != NULL) {
    w->farX = w->anchor->coord.x;
    w->farY = w->anchor->coord.y;
  }
  BGnHOFS(n) = l->viewportLeftTopPixel.x - (w->farX >> 8) + 256;
  BGnVOFS(n) = l->viewportLeftTopPixel.y - (w->farY >> 8) + 64;
}

// 0x08010f54
static void Event_Exit(struct StageLayer* _ UNUSED, const struct Stage* __ UNUSED) {
  gBlendRegBuffer.bldclt = 0;
}

/*
  Zero 2's VFX 61, a blast drawn on BG0: shades of white added under a 16x16 tile square for 9 frames
  coord: its top left, in tiles
*/

static void Blast_Init(struct VFX* p);
static void Blast_Update(struct VFX* p);
static void Blast_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2SealBlastRoutine = {
    [ENTITY_INIT] =      Blast_Init,
    [ENTITY_UPDATE] =    Blast_Update,
    [ENTITY_DIE] =       Blast_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bca6c
static void createBlast(s32 x, s32 y) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_SEAL_BLAST);
  p->coord.x = x - 8;
  p->coord.y = y - 8;
  p->work[0] = p->work[1] = 0;
}

// 0x080bcba8
static void drawBlast(struct Sprite* spr, struct DrawPivot* _ UNUSED) {
  struct Entity* s = (struct Entity*)spr->sprites;
  u16* bg0 = (u16*)gGameState.bg0;
  s32 r, c, row, col;
  u16* t;
  u32 shade;
  if (s->mode[0] > ENTITY_UPDATE) return;
  for (r = 0; r < 16; r++) {
    row = s->coord.y + r;
    if (row < 0) continue;
    if (row >= 20) return;
    for (c = 0; c < 16; c++) {
      col = s->coord.x + c;
      if (col < 0) continue;
      if (col >= 30) break;
      t = &bg0[row * 32 + col];
      shade = (*t & 15) + gApZ2Yggdrasil_BlastShades[s->work[3]][r][c];
      *t = 0x1200 | (shade > 15 ? 15 : shade);
    }
  }
}

static void Blast_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  CpuCopy16(gApZ2Yggdrasil_BlastTiles, (void*)(BG_VRAM + ((gVideoRegBuffer.bgcnt[0] & 12) << 12) + 512 * 32), 512);
  CpuCopy16(gApZ2Yggdrasil_BlastPal, &gPaletteManager.buf[16], 32);
  gBlendRegBuffer.bldclt = 0x3F41;
  gBlendRegBuffer.bldalpha = 0x1010;
  SetTaskCallback((void*)&s->spr, drawBlast);
  (s->spr).sprites = (struct MetaspriteHeader*)s;
  s->flags &= ~USE_COMMON_OAM_RENDERER;
  s->flags |= DISPLAY | FLIPABLE;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Blast_Update(p);
}

static void Blast_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[3] = 0;
    s->mode[2]++;
  } else {
    s->work[3]++;
  }
  if (s->work[3] <= 8) return;
  SET_VFX_ROUTINE(p, ENTITY_DIE);
  Blast_Die(p);
}

static void Blast_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x08010f60, 0x0801102c: the far wall, or once the finale opens it the sky
static void Backdrop_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (!gOverworld.work.apZ2Yggdrasil.altBackdrop) return;
  if (l->phase == 0) {
    BGCNT16(n) = (u16)(l->screenBase | 0x4046);
    RequestBgMapTransfer((u16*)gApZ2Yggdrasil_Layer3Map, (void*)SCREEN_BASE(n), BG_SCREEN_SIZE);
    RequestVRAMFill(0, (void*)(SCREEN_BASE(n) + BG_SCREEN_SIZE), BG_SCREEN_SIZE);
    l->phase++;
    l->unk_0f = 0;
  }
  if (SHOW_BACKDROP) {
    gVideoRegBuffer.dispcnt |= 1 << (8 + n);
  } else {
    gVideoRegBuffer.dispcnt &= ~(1 << (8 + n));
  }
}

static void Backdrop_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  u16 n = (u16)l->bgIdx >> 4;
  PixelCoords at = {0, 0};
  if (w->altBackdrop) {
    BGnHOFS(n) = l->viewportLeftTopPixel.x - (w->farX >> 8) + 255;
    BGnVOFS(n) = l->viewportLeftTopPixel.y - (w->farY >> 8) + 64;
    return;
  }
  if (l->unk_0f != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  gVideoRegBuffer.dispcnt |= 1 << (8 + n);
  FUN_08005a70(&l->gfx, &at, SCREEN_ADDR(n));
  UpdateBGOFS(&l->gfx, BGOFS(n));
  l->unk_0f++;
  l->phase = 0;
}

// 0x0801110c
static void Wall_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  PixelCoords at = {0, 160};
  if (l->phase != 0) return;
  FUN_08005a70(&l->gfx, &at, SCREEN_ADDR(n));
  UpdateBGOFS(&l->gfx, BGOFS(n));
  l->phase++;
}

// 0x08011168
static void Lights_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    BGCNT16(n) = (BGCNT16(n) & ~3) | 2;
    LIGHT = 0;
    l->phase++;
  }
  if (++LIGHT == 45) LIGHT = 0;
}

// 0x080111bc
static void Lights_Draw(struct StageLayer* l, const struct Stage* s) {
  const ColorGraphic* g = &gApZ2Yggdrasil_TileAnim[LIGHT / 9];
  DrawGeneralStageLayer(l, s);
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

// 0x08011218, 0x0801124c
static void Glow_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    ApStartPaletteAnimation(PLTT_ANIM_ID(69), &gApZ2Yggdrasil_PlttAnim69, gApZ2Yggdrasil_PlttAnimScript69, 0);
    ApStartPaletteAnimation(PLTT_ANIM_ID(74), &gApZ2Yggdrasil_PlttAnim74, gApZ2Yggdrasil_PlttAnimScript74, 0);
    l->phase++;
  }
  StepPaletteAnimation(PLTT_ANIM_ID(69));
  StepPaletteAnimation(PLTT_ANIM_ID(74));
}

static void Glow_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  REMOVE(69);
  REMOVE(74);
}

// 0x0801144c, 0x080114c0: Panter's room, cars' clock
static void Sway_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  if (l->phase == 0) {
    ApStartPaletteAnimation(PLTT_ANIM_ID(69), &gApZ2Yggdrasil_PlttAnim69, gApZ2Yggdrasil_PlttAnimScript69, 0);
    w->sway = 128;
    l->phase++;
  }
  if (l->viewportLeftTopPixel.x <= 0x59F) w->sway = 128;
  if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) w->sway++;
  StepPaletteAnimation(PLTT_ANIM_ID(69));
}

static void Sway_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) { REMOVE(69); }

// 0x08011768: frog's canopy, terrain's own map 720 px right
metatile_attr_t ApZ2YggdrasilCanopy(s32 x, s32 y) {
  u16* map = gOverworld.terrain.tilemap;
  if ((u32)(x - PIXEL(1680)) > 0xEFFF || y < PIXEL(960) || y > 0x45FFF) return 0;
  return map[MAP_OFFSET(map, (x + PIXEL(720)) >> 12, y >> 12)];
}

// 0x080117c4
void ApZ2YggdrasilBurn(s32 x, s32 y) {
  static const u16 sBurnt[3] = {1, 1, 0};
  if ((u32)(x - PIXEL(1680)) > 0xEFFF || y < PIXEL(960) || y > 0x45FFF) return;
  gOverworld.work.apZ2Yggdrasil.burnt = TRUE;
  PatchMetatileMap((x + PIXEL(720)) >> 12, y >> 12, sBurnt);
  gOverworld.terrain.tilemap_duty = FALSE;
}

// 0x08011260: in front of terrain, its fire's solid kept while shown
static void Canopy_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    BGCNT16(n) = (BGCNT16(n) & ~3) | 1;
    w->leaf = NULL;
    w->burnt = FALSE;
    l->phase++;
  }
  if (w->leaf == NULL) w->leaf = CreateLeafBurn(1);
}

// 0x08011320
static void Canopy_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct LayerGraphic* g = &l->gfx;
  PixelCoords c;
  u32 dx = l->viewportLeftTopPixel.x - l->prevViewportLeftTopPixel.x + 15;
  u32 dy = l->viewportLeftTopPixel.y - l->prevViewportLeftTopPixel.y + 15;
  c.x = (l->drawPivotOffset.x >> 8) + l->viewportLeftTopPixel.x + 720;
  c.y = (l->drawPivotOffset.y >> 8) + l->viewportLeftTopPixel.y;
  if (dx >= 31 || dy >= 31 || gOverworld.work.apZ2Yggdrasil.burnt) {
    FUN_08006ae0(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  } else {
    FUN_08006bb4(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  }
  gOverworld.work.apZ2Yggdrasil.burnt = FALSE;
  UpdateBGOFS(g, BGOFS(l->bgIdx >> 4));
}

// 0x080113f8
static void Canopy_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  struct Solid* leaf = gOverworld.work.apZ2Yggdrasil.leaf;
  if (leaf == NULL) return;
  (leaf->s).flags &= ~DISPLAY;
  (leaf->s).flags &= ~FLIPABLE;
  EXIT_BODY(leaf);
  SET_SOLID_ROUTINE(leaf, ENTITY_DISAPPEAR);
  gOverworld.work.apZ2Yggdrasil.leaf = NULL;
}

// 0x080ef6d8, 0x080ef6e8, 0x080ef6e0
static const Coords32 sCarAt[2] = {{PIXEL(1776), PIXEL(432)}, {PIXEL(1936), PIXEL(432)}};
static const struct Rect sCarSize = {0, 16128, -32768, -512};

static void car(struct StageLayer* l, u8 n, s32 dx, s32 dy, s16 left) {
  struct ApZ2YggdrasilState* w = &gOverworld.work.apZ2Yggdrasil;
  u16 bg = (u16)l->bgIdx >> 4;
  u32 zero = 0;
  if (l->phase == 0) {
    BGCNT16(bg) = (u16)(l->screenBase | 0x4046);
    CpuFastSet(gApZ2Yggdrasil_PlatformMap, SCREEN_ADDR(bg), BG_SCREEN_SIZE / 4);
    CpuFastSet(&zero, (u8*)SCREEN_ADDR(bg) + BG_SCREEN_SIZE, BG_SCREEN_SIZE / 4 | 1 << 24);
    l->phase++;
  }
  BGnHOFS(bg) = l->viewportLeftTopPixel.x + left - (dx >> 8);
  BGnVOFS(bg) = l->viewportLeftTopPixel.y - 480 - (dy >> 8);
  w->cars[n].x = sCarAt[n].x + dx;
  w->cars[n].y = sCarAt[n].y + dy;
  AppendHazard(0xE001 + n, MTATTR_CONVEYOR1 | SHAPE_BLOCK, &w->cars[n], &sCarSize);
}

// 0x080114cc
static void FrontCar_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u32 t = gOverworld.work.apZ2Yggdrasil.sway;
  car(l, 0, SIN((u8)t) * 8, SIN((u8)(t >> 2)) * 8 + 0x800, -176);
}

// 0x0801160c
static void RearCar_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u32 t = gOverworld.work.apZ2Yggdrasil.sway;
  car(l, 1, SIN((u8)((t >> 1) + 64)) * 8, SIN((u8)((t >> 3) + 64)) * 8 + 0x800, -336);
}

// clang-format off
const StageLayerRoutine gApZ2Yggdrasil_LayerRoutines[11] = {
    [0] =  {NULL, NULL, NULL},
    [1] =  {NULL, DrawGeneralStageLayer, NULL},
    [2] =  {Event_Update, Event_Draw, Event_Exit},
    [3] =  {Backdrop_Update, Backdrop_Draw, NULL},
    [4] =  {NULL, Wall_Draw, NULL},
    [5] =  {Lights_Update, Lights_Draw, NULL},
    [6] =  {Glow_Update, DrawGeneralStageLayer, Glow_Exit},
    [7] =  {Canopy_Update, Canopy_Draw, Canopy_Exit},
    [8] =  {Sway_Update, DrawGeneralStageLayer, Sway_Exit},
    [9] =  {FrontCar_Update, NULL, NULL},
    [10] = {RearCar_Update, NULL, NULL},
};
// clang-format on

// --------------------------------------------
/*
  0x0801a6b4: Zero 2's mission update, in place of src/ap_import.c's.

  checkpoint 0: the bottom
             1: below hub 1
             2: past it
             3: below hub 2
             4: past it
             5: at the top
*/

extern const GameCommand gApZ2Yggdrasil_OpeningScript[], gApZ2Yggdrasil_StartRestartScript[],
    gApZ2Yggdrasil_SnakeScript[], gApZ2Yggdrasil_BearScript[], gApZ2Yggdrasil_MagnionScript[],
    gApZ2Yggdrasil_Hub1ClearScript[], gApZ2Yggdrasil_Hub1DoneScript[], gApZ2Yggdrasil_Hub1RestartScript[],
    gApZ2Yggdrasil_Hub2RestartScript[], gApZ2Yggdrasil_PanterScript[], gApZ2Yggdrasil_KuwagustScript[],
    gApZ2Yggdrasil_FrogScript[], gApZ2Yggdrasil_Hub2ClearScript[], gApZ2Yggdrasil_Hub2DoneScript[],
    gApZ2Yggdrasil_ClimbRestartScript[], gApZ2Yggdrasil_TopRestartScript[], gApZ2Yggdrasil_BossScript[],
    gApZ2Yggdrasil_BossReturnScript[], gApZ2Yggdrasil_ElpizoDownScript[], gApZ2Yggdrasil_FinalDownScript[];

#define BEATEN unk_0a
#define FIGHT unk_17d
#define BACK 10

static void start(struct StageRun* p, const GameCommand* script, u8 phase) {
  SetScript(&gStageRun.vm, script);
  p->stageEventPhase = phase;
}

static void sweep(bool8 on) {
  if (on) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else {
    gCollisionManager.sweep = 0;
  }
}

static bool8 within(s32 y, s32 top) { return (u32)(y - top) < PIXEL(160); }

// A refight's end: the hub's three beaten opens the way on
static void hub(struct StageRun* p, const GameCommand* clear, const GameCommand* done, u8 first, u8 next) {
  u8 all = 7 << first;
  if (gStageRun.missionStatus & MISSION_SUCCESS) {
    gCollisionManager.disabled |= COLLMAN_DISABLED;
    sweep(TRUE);
    gStageRun.missionStatus &= ~(MISSION_B1 | MISSION_SUCCESS);
    gStageRun.vm.active &= ~VM_FLAG1;
    gStageRun.missionStatus |= MISSION_STAY;
    gStageRun.BEATEN |= 1 << (p->FIGHT - 1);
    ApMarkLocationChecked(AP_LOC_IMPORT_REFIGHT_FIRST + p->FIGHT - 1);
    p->FIGHT = BACK;
    if ((gStageRun.BEATEN & all) == all) {
      start(p, done, next);
    } else {
      SetScript(&gStageRun.vm, clear);
    }
    return;
  }
  if (p->FIGHT != BACK) return;
  gCollisionManager.disabled &= ~COLLMAN_DISABLED;
  sweep(FALSE);
  setStageCheckpoint(first == 0 ? 1 : 3);
  p->FIGHT = 0;
}

static void enter(struct StageRun* p, const GameCommand* script, u8 fight) {
  SetScript(&gStageRun.vm, script);
  p->FIGHT = fight;
}

s16 ApZ2YggdrasilUpdate(struct StageRun* p) {
  const Coords32* z = &(((struct Zero*)(p->vm).entities[0].entity)->s).coord;
  bool8 idle = !(gStageRun.vm.active & VM_ACTIVE);

  switch (p->stageEventPhase) {
    case 0:
      gStageRun.missionStatus |= MISSION_STAY;
      switch (gStageRun.checkpoint) {
        case 0:
          gStageRun.BEATEN = 0;
          start(p, gApZ2Yggdrasil_OpeningScript, 1);
          break;
        case 1:
          start(p, gApZ2Yggdrasil_StartRestartScript, 2);
          break;
        case 2:
          start(p, gApZ2Yggdrasil_Hub1RestartScript, 6);
          break;
        case 3:
          start(p, gApZ2Yggdrasil_Hub2RestartScript, 7);
          break;
        case 4:
          start(p, gApZ2Yggdrasil_ClimbRestartScript, 11);
          break;
        case 5:
          start(p, gApZ2Yggdrasil_TopRestartScript, 13);
          gOverworld.state[0] = 2;
          break;
      }
      return 0;
    case 1:
      if (z->y <= 0xD1FFF && z->x > 0x2CFFF) {
        sweep(TRUE);
        setStageCheckpoint(1);
        p->stageEventPhase = 2;
      }
      break;
    case 2:
      if (z->y <= 0xC7FFF && z->x <= PIXEL(720) && idle) {
        sweep(FALSE);
        gStageRun.vm.camera.bottom = 0xCB000;
        p->FIGHT = 0;
        p->stageEventPhase = 3;
      }
      break;
    case 3:
      hub(p, gApZ2Yggdrasil_Hub1ClearScript, gApZ2Yggdrasil_Hub1DoneScript, 0, 4);
      if (p->stageEventPhase != 3 || p->FIGHT != 0 || z->x <= PIXEL(1680)) break;
      if (within(z->y, PIXEL(1760))) {
        enter(p, gApZ2Yggdrasil_SnakeScript, 1);
      } else if (within(z->y, PIXEL(3040))) {
        enter(p, gApZ2Yggdrasil_BearScript, 2);
      } else if (within(z->y, PIXEL(2400))) {
        enter(p, gApZ2Yggdrasil_MagnionScript, 3);
      }
      break;
    case 4:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      sweep(FALSE);
      setStageCheckpoint(1);
      p->stageEventPhase = 5;
      break;
    case 5:
      if (z->y <= 0xBDFFF) {
        setStageCheckpoint(2);
        p->stageEventPhase = 6;
      }
      break;
    case 6:
      if (z->y <= 0x77FFF && z->x > 0x2CFFF) {
        sweep(TRUE);
        setStageCheckpoint(3);
        p->stageEventPhase = 7;
      }
      break;
    case 7:
      if (z->y <= 0x6DFFF && z->x <= PIXEL(720) && idle) {
        sweep(FALSE);
        gStageRun.vm.camera.bottom = 0x71000;
        p->FIGHT = 0;
        p->stageEventPhase = 8;
      }
      break;
    case 8:
      hub(p, gApZ2Yggdrasil_Hub2ClearScript, gApZ2Yggdrasil_Hub2DoneScript, 3, 9);
      if (p->stageEventPhase != 8 || p->FIGHT != 0) break;
      if (z->x > PIXEL(2400) && within(z->y, PIXEL(320))) {
        enter(p, gApZ2Yggdrasil_KuwagustScript, 5);
      } else if (z->x > PIXEL(1680) && within(z->y, PIXEL(320))) {
        enter(p, gApZ2Yggdrasil_PanterScript, 4);
      } else if (z->x > PIXEL(1680) && within(z->y, PIXEL(960))) {
        enter(p, gApZ2Yggdrasil_FrogScript, 6);
      }
      break;
    case 9:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      sweep(FALSE);
      setStageCheckpoint(3);
      p->stageEventPhase = 10;
      break;
    case 10:
      if (z->y <= 0xBDFFF) {
        setStageCheckpoint(4);
        p->stageEventPhase = 11;
      }
      break;
    case 11:
      if (z->y <= 0x27FFF && z->x <= PIXEL(720)) {
        sweep(TRUE);
        if (gStageRun.vm.bgm != BGM_GUARDER_ROOM) {
          if (gStageRun.vm.bgm != (SoundID32)-1) FadeOutBGM(gStageRun.vm.bgm);
          PlayBGM(BGM_GUARDER_ROOM);
          gStageRun.vm.bgm = BGM_GUARDER_ROOM;
        }
        gOverworld.state[0] = 0;
        setStageCheckpoint(5);
        p->stageEventPhase = 12;
      }
      break;
    case 12:
    case 13:
      if (z->y <= 0x1CFFF && idle) {
        sweep(FALSE);
        p->FIGHT = 0;
        start(p, p->stageEventPhase == 12 ? gApZ2Yggdrasil_BossScript : gApZ2Yggdrasil_BossReturnScript, 14);
      }
      break;
    case 14:
      if (!(gStageRun.missionStatus & MISSION_SUCCESS)) break;
      gCollisionManager.disabled |= COLLMAN_DISABLED;
      sweep(TRUE);
      gStageRun.missionStatus &= ~MISSION_SUCCESS;
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.missionStatus |= MISSION_STAY;
      start(p, gApZ2Yggdrasil_ElpizoDownScript, 15);
      break;
    case 15:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      sweep(FALSE);
      p->stageEventPhase = 16;
      break;
    case 16:
      if (!(gStageRun.missionStatus & MISSION_SUCCESS)) break;
      gCollisionManager.disabled |= COLLMAN_DISABLED;
      sweep(TRUE);
      gStageRun.missionStatus &= ~MISSION_SUCCESS;
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.missionStatus |= MISSION_STAY;
      start(p, gApZ2Yggdrasil_FinalDownScript, 17);
      break;
    case 17:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      sweep(FALSE);
      gStageRun.missionStatus &= ~MISSION_STAY;
      p->stageEventPhase = 18;
      break;
  }
  return 0;
}

#endif  // AP
