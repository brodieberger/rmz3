// Zero 2's JUNGLE AKA Forest of Dysis

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
#include "quake.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "text_window.h"
#include "vfx.h"
#include "trig.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Jungle_PlttAnim101, gApZ2Jungle_PlttAnim102, gApZ2Jungle_PlttAnim103, gApZ2Jungle_PlttAnim104,
    gApZ2Jungle_PlttAnim105, gApZ2Jungle_PlttAnim106, gApZ2Jungle_PlttAnim107, gApZ2Jungle_PlttAnim108, gApZ2Jungle_PlttAnim109,
    gApZ2Jungle_PlttAnim110, gApZ2Jungle_PlttAnim111, gApZ2Jungle_PlttAnim112, gApZ2Jungle_PlttAnim113, gApZ2Jungle_PlttAnim114;
extern const AnimCmd* const gApZ2Jungle_PlttAnimScript101[], *const gApZ2Jungle_PlttAnimScript102[],
    *const gApZ2Jungle_PlttAnimScript103[], *const gApZ2Jungle_PlttAnimScript104[], *const gApZ2Jungle_PlttAnimScript105[],
    *const gApZ2Jungle_PlttAnimScript106[], *const gApZ2Jungle_PlttAnimScript107[], *const gApZ2Jungle_PlttAnimScript108[],
    *const gApZ2Jungle_PlttAnimScript109[], *const gApZ2Jungle_PlttAnimScript110[], *const gApZ2Jungle_PlttAnimScript111[],
    *const gApZ2Jungle_PlttAnimScript112[], *const gApZ2Jungle_PlttAnimScript113[], *const gApZ2Jungle_PlttAnimScript114[];
extern const ColorGraphic gApZ2Jungle_TileAnim[3];
extern const u16 gApZ2Jungle_Water0Map[], gApZ2Jungle_Water1Map[];
extern const TextID gApZ2Jungle_RescueTexts[5];
extern const GameCommand gApZ2Jungle_FightScript[], gApZ2Jungle_FightReturnScript[];
struct ScriptEntityTemplate;
extern struct ScriptEntityTemplate gApZ2Jungle_SnakeRider;
void CreateScriptEntity(u8 n, struct ScriptEntityTemplate* template);
struct Entity* ApZ2CreateSplash(const Coords32* at, u8 kind);

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Jungle_PlttAnim##n, gApZ2Jungle_PlttAnimScript##n)
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

// 0x0800af48
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2JungleState* w = &gOverworld.work.apZ2Jungle;
  w->timer = 0;
  w->flash = 0;
  w->music = gStageRun.checkpoint == 2 ? 2 : 0;
  w->returning = gStageRun.checkpoint == 2;
  w->fight = FALSE;
  w->burnt = FALSE;
  w->intro = FALSE;
  w->leaf = NULL;
  gOverworld.state[0] = 0;
}

/*
  0x0800af8c, 0x080166b8: x 6224 music goes, 6256 corridor's plays, 6448 snake laid out and camera holds,
  6480 fight
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2JungleState* w = &gOverworld.work.apZ2Jungle;
  s32 zero = (pZero2->s).coord.x;

  if (++w->timer == 256) w->timer = 0;

  ANIMATE(TILESET(1) == 2, 106);
  ANIMATE(TILESET(1) == 2, 107);
  ANIMATE(TILESET(1) == 2, 108);
  ANIMATE(TILESET(1) == 2, 109);
  ANIMATE(TILESET(1) == 2, 110);
  ANIMATE(TILESET(1) == 2, 111);
  ANIMATE(TILESET(0) == 3, 112);
  ANIMATE(TILESET(0) == 3, 113);
  ANIMATE(TILESET(0) == 3, 114);
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

  if (w->music == 0 && zero > PIXEL(6223)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(6255)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (gStageRun.stageEventPhase == 3 && !w->intro && zero > PIXEL(6447)) {
    CreateScriptEntity(3, &gApZ2Jungle_SnakeRider);
    Camera_SetMode(&gStageRun.vm.camera, 6);
    gStageRun.vm.camera.left = 0;
    gStageRun.vm.camera.right = PIXEL(15360);
    gStageRun.vm.camera.top = 0;
    gStageRun.vm.camera.bottom = PIXEL(480);
    w->intro = TRUE;
  }
  if (gStageRun.stageEventPhase == 3 && !w->fight && zero > PIXEL(6479)) {
    SetScript(&gStageRun.vm, w->returning ? gApZ2Jungle_FightReturnScript : gApZ2Jungle_FightScript);
    w->fight = TRUE;
  }
  if (w->leaf == NULL) w->leaf = CreateLeafBurn(1);
}

// 0x0800b258: sky flashes, three frames on timer
static void Stage_Draw(Coords32* _ UNUSED) {
  static const u8 sFlashes[6][2] = {{160, 0}, {176, 1}, {180, 2}, {184, 0}, {251, 1}, {255, 2}};
  u8 t = gOverworld.work.apZ2Jungle.flash;
  u16 i = 0;
  const ColorGraphic* g;

  if (TILESET(0) != 0) return;
  while (t > sFlashes[i][0]) i++;
  g = &gApZ2Jungle_TileAnim[sFlashes[i][1]];
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

// 0x0800b2e8
static void Stage_Exit(Coords32* _ UNUSED) {
  struct Solid* leaf = gOverworld.work.apZ2Jungle.leaf;
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
  REMOVE(114);
  if (leaf != NULL) {
    (leaf->s).flags &= ~DISPLAY;
    (leaf->s).flags &= ~FLIPABLE;
    EXIT_BODY(leaf);
    SET_SOLID_ROUTINE(leaf, ENTITY_DISAPPEAR);
  }
}

metatile_attr_t FUN_08010cd0(s32 x, s32 y);
void FUN_08010d20(s32 x, s32 y);

extern const StageFunc gApZ2Jungle2_StageRoutines[4];
metatile_attr_t ApZ2Jungle2Canopy(s32 x, s32 y);
void ApZ2Jungle2Burn(s32 x, s32 y);

static bool8 inNotus(void) { return gApImportedStages[gApImportSelected].fns == gApZ2Jungle2_StageRoutines; }

// 0x0800bb24, Anatre's own outside slot 0
metatile_attr_t ApZ2JungleCanopy(s32 x, s32 y) {
  u16* map = gOverworld.terrain.tilemap;
  if (gStageRun.id != STAGE_NONE) return FUN_08010cd0(x, y);
  if (inNotus()) return ApZ2Jungle2Canopy(x, y);
  if ((u32)x > PIXEL(3840) - 1 || y < PIXEL(640) || y > PIXEL(960) - 1) return 0;
  return map[MAP_OFFSET(map, x >> 12, (y - PIXEL(640)) >> 12)];
}

// 0x0800bb78
void ApZ2JungleBurn(s32 x, s32 y) {
  static const u16 sBurnt[3] = {1, 1, 0};
  if (gStageRun.id != STAGE_NONE) {
    FUN_08010d20(x, y);
    return;
  }
  if (inNotus()) {
    ApZ2Jungle2Burn(x, y);
    return;
  }
  if ((u32)x > PIXEL(3840) - 1 || y < PIXEL(640) || y > PIXEL(960) - 1) return;
  gOverworld.work.apZ2Jungle.burnt = TRUE;
  PatchMetatileMap(x >> 12, (y - PIXEL(640)) >> 12, sBurnt);
  gOverworld.terrain.tilemap_duty = FALSE;
}

const StageFunc gApZ2Jungle_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013aac
u8 gApZ2Jungle_Area(Coords32* c) {
  if (c->x < PIXEL(368)) return 7;
  if (c->x < PIXEL(3600)) return 0;
  if (c->x > 0x10E000 && c->x < 0x11D000 && c->y > PIXEL(640) && c->y < PIXEL(960)) return 2;
  if ((c->x < PIXEL(4080) && c->y < PIXEL(960)) || (c->x < PIXEL(5040) && c->y < PIXEL(800))) return 1;
  if (c->x >= PIXEL(6368)) return 6;
  return 3;
}

static void hideEntity(struct Entity* e) {
  e->flags &= ~(DISPLAY | FLIPABLE);
}

// 0x0800b390
static void Backdrop_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    l->scrollPower.x = l->scrollPower.y = 0x100;
    l->scroll.x = l->scroll.y = 0;
    l->phase++;
  }
}

#define LIFT0 (*(struct Entity**)&l->work.raw[0])
#define LIFT1 (*(struct Entity**)&l->work.raw[4])

static struct Entity* createLift(s32 y, u8 work0) {
  struct Entity* e = AllocEntityLast(gSolidHeaderPtr);
  if (e == NULL) return NULL;
  INIT_SOLID_ROUTINE(e, SOLID_Z2_LIFT);
  e->coord.x = PIXEL(3976);
  e->coord.y = y;
  e->work[0] = work0;
  e->work[1] = 64;
  return e;
}

// 0x0800b3b0
static void Lifts_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    LIFT0 = createLift(PIXEL(752), 0);
    LIFT1 = createLift(PIXEL(528), 1);
    l->phase++;
  }
}

static void removeLift(struct Entity* e) {
  if (e == NULL) return;
  hideEntity(e);
  SET_SOLID_ROUTINE((struct Solid*)e, ENTITY_DISAPPEAR);
}

// 0x0800b3ec
static void Lifts_Exit(struct StageLayer* l, const struct Stage* _ UNUSED) {
  removeLift(LIFT0);
  removeLift(LIFT1);
  LIFT0 = NULL;
  LIFT1 = NULL;
}

// 0x0800b478: crusher, whole layer falling every 256 frames
static void Crusher_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  static const struct Rect sSize = {0, -0x3C00, -0x1000, 0x7800};
  u16 t = gOverworld.work.apZ2Jungle.timer;
  Coords32 c;
  s32 y;

  if (t < 96) {
    y = -72;
  } else if (t < 128) {
    y = -72 - (((t - 96) * (t - 96) * 72) >> 10);
  } else if (t < 224) {
    y = -144;
  } else {
    y = (((t - 224) * 72) >> 5) - 144;
  }
  l->scroll.y = y;

  c.x = PIXEL(l->viewportLeftTopPixel.x + 120);
  c.y = PIXEL(256) - PIXEL(y);
  if (c.x > 0x171800) c.x = 0x171800;
  if (c.x < 0x143000) c.x = 0x143000;
  AppendHazard(0xE001, 15, &c, &sSize);
  if (t == 128) {
    AppendQuake(8, &c);
    PlaySound(SE_Z2_CRUSHER);
  }
}

// 0x0800b550: terrain's own map 640 px higher, canopy over forest
static void Canopy_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct LayerGraphic* g = &l->gfx;
  PixelCoords c;
  u32 dx = l->viewportLeftTopPixel.x - l->prevViewportLeftTopPixel.x + 15;
  u32 dy = l->viewportLeftTopPixel.y - l->prevViewportLeftTopPixel.y + 15;
  c.x = (l->drawPivotOffset.x >> 8) + l->viewportLeftTopPixel.x;
  c.y = (l->drawPivotOffset.y >> 8) + l->viewportLeftTopPixel.y - 640;
  if (dx >= 31 || dy >= 31 || gOverworld.work.apZ2Jungle.burnt) {
    FUN_08006ae0(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  } else {
    FUN_08006bb4(g, &c, SCREEN_ADDR(l->bgIdx >> 4), gOverworld.terrain.tilemap);
  }
  gOverworld.work.apZ2Jungle.burnt = FALSE;
  UpdateBGOFS(g, BGOFS(l->bgIdx >> 4));
}

#define WATER_TIME l->work.raw[16]
#define WATER_FALL (*(struct Entity**)&l->work.raw[0])
#define WATER_TOP (*(struct Entity**)&l->work.raw[4])
#define WATER_AT (*(Coords32*)&l->work.raw[8])

static const Coords32 sWaterFallAt = {0x10F000, 0x2B300};

static void removeSplash(struct Entity* e) {
  if (e == NULL) return;
  hideEntity(e);
  SET_VFX_ROUTINE((struct VFX*)e, ENTITY_DISAPPEAR);
}
#define SEA_LOW 0x32800

static s32 waterScroll(struct StageLayer* l) {
  s32 y = l->viewportLeftTopPixel.y - (gOverworld.sea >> 8) + 8;
  if (y < -180) y = -180;
  if (y > 0) y = 0;
  return y;
}

/*
  0x0800b62c: mid-boss's room.
  gOverworld.state[0]:
    0: water at low line
    1: boss's flood, up to y 640
    2: boss beaten, draining
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
    WATER_AT.x = 0x10F000;
    WATER_TIME = 0;
    gOverworld.sea = state == 2 ? 0x7FFFFFFF : SEA_LOW;
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
    } else if (gOverworld.sea > PIXEL(640)) {
      gOverworld.sea -= 0x100;
    }
  } else if (state == 0) {
    if (gOverworld.sea < SEA_LOW) gOverworld.sea += 0x100;
    WATER_TIME = 0;
  } else {
    gOverworld.sea = gOverworld.sea < 0x3C800 ? gOverworld.sea + 0x300 : 0x7FFFFFFF;
    WATER_TIME = 0;
  }

  WATER_AT.y = gOverworld.sea - 0x600;
  y = waterScroll(l);
  if ((u8)(WATER_TIME - 1) < 23) {
    u8 half = WATER_TIME >> 1;
    gWindowRegBuffer.winin[1] = 0xFF;
    gWindowRegBuffer.winin[2] = (gWindowRegBuffer.winin[2] | 10) & ~4;
    gWindowRegBuffer.winH.half[1] = ((half + 17) & 0xFF) | ((16 - half) << 8);
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
  BGnHOFS(n) = 0;
  BGnVOFS(n) = y;
}

// 0x0800b9b0: lines above water show nothing, by HBlank DMA
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

// 0x0800ba4c
static void Water_Exit(struct StageLayer* l, const struct Stage* _ UNUSED) {
  removeSplash(WATER_FALL);
  removeSplash(WATER_TOP);
  StopSound(SE_Z2_WATER);
  gOverworld.sea = 0x7FFFFFFF;
  gBlendRegBuffer.bldclt = 0;
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 14;
}

// 0x0800bae0: in front of terrain, 1:1
static void Front_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    u16 n = (u16)l->bgIdx >> 4;
    BGCNT16(n) = (BGCNT16(n) & ~3) | 1;
    l->scrollPower.x = l->scrollPower.y = 0x100;
    l->scroll.x = l->scroll.y = 0;
    l->phase++;
  }
}

/*
  Zero 2's layer routines for this stage
  2: backdrop, 1:1
  3: two lifts
  4: crusher
  5: canopy
  6: mid-boss's water
  7: in front, 1:1
*/
// clang-format off
const StageLayerRoutine gApZ2Jungle_LayerRoutines[8] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Backdrop_Update, DrawGeneralStageLayer, NULL},
    [3] = {Lifts_Update, DrawGeneralStageLayer, Lifts_Exit},
    [4] = {Crusher_Update, DrawGeneralStageLayer, NULL},
    [5] = {NULL, Canopy_Draw, NULL},
    [6] = {Water_Update, Water_Draw, Water_Exit},
    [7] = {Front_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

// --------------------------------------------

static void setUp(struct Solid* p, motion_t m) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, m);
}

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

// Zero 2's solid 25, cap on stalk
static void Cap_Update(struct Solid* p) { UpdateSpriteAnimation(p); }

// 0x080d13dc
static void Cap_Init(struct Solid* p) {
  setUp(p, MOTION(AP_SHEET_Z2_PAD, 0));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Cap_Update(p);
}

ROUTINE(gApZ2PadRoutine, Cap_Init, Cap_Update);

/*
  Zero 2's solid 15.
  work0:
    0, 1: up and down
    2, 3: side to side
  work1: how far
*/
struct Lift {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  bool8 forward;  // 0xBC
  u8 _bd[7];
};
static_assert(sizeof(struct Lift) == sizeof(struct Solid));

static const struct Rect sLiftSize = {0, 4351, 8192, 8192};

// 0x080cd4d4, 0x080cd544
static void Lift_Update(struct Solid* p) {
  struct Lift* f = (struct Lift*)p;
  struct Entity* s = &p->s;
  bool8 vertical = s->work[0] < 2;
  s32 off = vertical ? f->home.y - s->coord.y : f->home.x - s->coord.x;
  if ((u32)(off + (s->work[1] << 8)) > (u32)(s->work[1] << 9)) {
    f->forward ^= 1;
    if (vertical) {
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_LIFT, f->forward ? 2 : 1));
    } else {
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_LIFT, f->forward ? 3 : 4));
    }
  }
  UpdateSpriteAnimation(p);
  if (vertical) {
    s->coord.y += f->forward ? 0x100 : -0x100;
  } else {
    s->coord.x += f->forward ? 0x100 : -0x100;
  }
}

// 0x080cd3d8
static void Lift_Init(struct Solid* p) {
  static const u8 sAnim[4] = {1, 2, 4, 3};
  struct Lift* f = (struct Lift*)p;
  struct Entity* s = &p->s;
  setUp(p, MOTION(AP_SHEET_Z2_LIFT, sAnim[s->work[0]]));
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sLiftSize;
  s->physicsAttr = 0x2401;
  f->home = s->coord;
  f->forward = s->work[0] & 1;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Lift_Update(p);
}

ROUTINE(gApZ2LiftRoutine, Lift_Init, Lift_Update);

/*
  Zero 2's solid 8 work0 5, lost soldier.
  work1: which, 0..4
*/
#define SOLDIERS_SAVED gStageRun.unk_0a  // bit 0 is the mid-boss's

// 0x08348fa4: talk box 32 px ahead
static const struct Collision sRescueCollisions[2] = {
    {DDP, FACTION_NEUTRAL, CHATABLE, 255, 0, 0, 0, 0, 0, 0, 0, 1, 0x00000001, {-0x2000, 0, 0x1000, 0x100}},
    {DRP, FACTION_NEUTRAL, CHATABLE, 255, 0xff, 0xff, 0xff, 0xff, 0, 0, 0, 0, 0x00000000, {0, 0, 0, 0}},
};

u8 ApZ2SoldiersSaved(void) {
  u8 n = 0, i;
  for (i = 0; i < 5; i++) {
    if (SOLDIERS_SAVED & (2 << i)) n++;
  }
  return n;
}

static void Rescue_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (!((p->body).status & BODY_STATUS_CHAT)) {
        SET_XFLIP(p, (pZero2->s).coord.x > s->coord.x);
        break;
      }
      if (!gInChat || gCollisionManager.talkTo != &p->body) break;
      PrintNormalMessage(gApZ2Jungle_RescueTexts[s->work[1]]);
      s->mode[1]++;
      break;
    case 1:
      if ((&gTextWindow.text)->mode != 0) break;
      gInChat = FALSE;
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      s->flags &= ~COLLIDABLE;
      SOLDIERS_SAVED |= 2 << s->work[1];
      s->work[2] = 30;
      s->mode[1]++;
      break;
    case 2:
      if (s->work[2] & 1) {
        PaintEntityWhite(s);
      } else {
        UpdateEntityPaletteID(s);
      }
      if (--s->work[2] != 0) break;
      InitRotatableMotion(s);
      s->texture = TEXTURE_AP_SHEET;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_RESCUE, 2));
      PlaySound(SE_TENSOU_BACK);
      s->work[2] = 8;
      s->mode[1]++;
      break;
    case 3:
      PaintEntityWhite(s);
      (s->spr).mag.x = 288 - s->work[2] * 4;
      (s->spr).mag.y = s->work[2] * 4 + 224;
      if (--s->work[2] != 0) break;
      s->work[2] = 4;
      s->mode[1]++;
      break;
    case 4:
      PaintEntityWhite(s);
      (s->spr).mag.x = s->work[2] * 64 + 32;
      (s->spr).mag.y = 352 - s->work[2] * 32;
      if (--s->work[2] != 0) break;
      s->d.y = -0xC00;
      s->mode[1]++;
      break;
    case 5:
      PaintEntityWhite(s);
      (s->spr).mag.x = 32;
      s->d.y -= 64;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= PIXEL(48)) break;
      s->flags &= ~DISPLAY;
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x080ca3b0
static void Rescue_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  if (SOLDIERS_SAVED & (2 << s->work[1])) {
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  setUp(p, MOTION(AP_SHEET_Z2_RESCUE, 2));
  s->flags |= COLLIDABLE;
  INIT_BODY(p, sRescueCollisions, 0, NULL);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Rescue_Update(p);
}

ROUTINE(gApZ2RescueRoutine, Rescue_Init, Rescue_Update);

/*
  Zero 2's solid 5 work0 27, soldier in opening
*/
static void Scout_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (!(s->scriptEntity->flags & 1)) break;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_RESCUE, 3));
      s->mode[1]++;
      break;
    case 1:
      if (!(s->scriptEntity->flags & 2)) break;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_RESCUE_RUN, 0));
      s->mode[1]++;
      break;
    case 2:
      s->coord.x -= 0x140;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) >= 0x1000) s->mode[1]++;
      break;
  }
}

// 0x080c52a0
static void Scout_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  setUp(p, MOTION(AP_SHEET_Z2_RESCUE, 2));
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Scout_Update(p);
}

ROUTINE(gApZ2ScoutRoutine, Scout_Init, Scout_Update);

/*
  Zero 2's solid 5 work0 30, soldier who took Baby Elf
*/
static const struct PreloadEntity sThiefSheet = {AP_SHEET_Z2_RESCUE, 0, 870, 8, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sThiefRunSheet = {AP_SHEET_Z2_RESCUE_RUN, 0, 224, 9, 0, AP_PRELOAD_SHEET, 0};

static void Thief_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (!(s->scriptEntity->flags & 1)) break;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_RESCUE, 1));
      s->mode[1]++;
      break;
    case 1:
      if (!(s->scriptEntity->flags & 2)) break;
      ApLoadSheet(&sThiefRunSheet);
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_RESCUE_RUN, 0));
      s->mode[1]++;
      break;
    case 2:
      s->coord.x -= 0x140;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) >= 0x1000) s->mode[1]++;
      break;
  }
}

// 0x080c5700
static void Thief_Init(struct Solid* p) {
  ApLoadSheet(&sThiefSheet);
  setUp(p, MOTION(AP_SHEET_Z2_RESCUE, 0));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Thief_Update(p);
}

ROUTINE(gApZ2ThiefRoutine, Thief_Init, Thief_Update);

/*
  Zero 2's solid 5 work0 31, Baby Elf, beside whoever the script linked it to
  work1: 0 one side, 1 the other
  flags: 0x80 closer and lower, 1 beams out
*/
static const struct PreloadEntity sElfSheet = {AP_SHEET_Z2_BABY_ELF, 0, 976, 7, 0, AP_PRELOAD_SHEET, 0};

// 0x080c4c90
static void follow(struct Entity* s) {
  struct Entity* leader = s->scriptEntity->unk_04;
  s32 lag, x, y;
  if (s->d.x != 0) s->d.x--;
  lag = (s->d.x * 5 << 11) >> 5;
  x = ((leader->flags & X_FLIP) != 0) == (s->work[1] == 0) ? PIXEL(20) - lag : lag - PIXEL(20);
  if (s->scriptEntity->flags & 0x80) {
    x = leader->coord.x + x / 3;
    y = leader->coord.y - PIXEL(16);
  } else {
    x += leader->coord.x;
    y = leader->coord.y - PIXEL(48);
  }
  s->work[3]++;
  y -= SIN(s->work[3] * 2) * 8;
  x += COS(s->work[3]) * 16;
  y -= (x - s->coord.x < 0 ? s->coord.x - x : x - s->coord.x) >> 1;
  s->coord.x = (s->coord.x * 31 + x) >> 5;
  s->coord.y = (s->coord.y * 31 + y) >> 5;
}

// 0x080c5954
static void BabyElf_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BABY_ELF, 0));
      s->d.x = 0;
      s->work[3] = s->work[1] << 6;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      follow(s);
      if ((s->work[3] & 31) == 0) {
        at.x = s->coord.x;
        at.y = s->coord.y + PIXEL(8);
        ApZ2CreateElfSparkle(&at, 4);
      }
      if (!(s->scriptEntity->flags & 1)) break;
      s->work[2] = 30;
      s->mode[1]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      follow(s);
      if (s->work[2] & 1) {
        PaintEntityWhite(s);
      } else {
        UpdateEntityPaletteID(s);
      }
      if (--s->work[2] != 0) break;
      s->work[2] = 8;
      s->mode[1]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      follow(s);
      PaintEntityWhite(s);
      (s->spr).mag.x = 288 - s->work[2] * 4;
      (s->spr).mag.y = s->work[2] * 4 + 224;
      if (--s->work[2] != 0) break;
      s->work[2] = 4;
      s->mode[1]++;
      break;
    case 4:
      UpdateSpriteAnimation(p);
      follow(s);
      PaintEntityWhite(s);
      (s->spr).mag.x = s->work[2] * 64 + 32;
      (s->spr).mag.y = 352 - s->work[2] * 32;
      if (--s->work[2] != 0) break;
      s->d.y = -0xC00;
      s->mode[1]++;
      break;
    case 5:
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

// 0x080c58c8
static void BabyElf_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitScalerotMotion1(s);
  s->texture = TEXTURE_AP_SHEET;
  ApLoadSheet(&sElfSheet);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  BabyElf_Update(p);
}

ROUTINE(gApZ2BabyElfRoutine, BabyElf_Init, BabyElf_Update);

/*
  Zero 2's solid 5 work0 32, X
*/
static const struct PreloadEntity sXSheet = {AP_SHEET_Z2_X, 0, 784, 8, 0, AP_PRELOAD_SHEET, 0};

static void X_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->coord.y += s->d.y;
      s->d.y -= 16;
      if (s->d.y != 0) break;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_X, 1));
      s->mode[1]++;
      break;
    case 1:
      if ((s->motion).state != ANIM_END) break;
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_X, 2));
      s->mode[1]++;
      break;
    case 2:
      if (!(s->scriptEntity->flags & 2)) break;
      s->d.y = 0;
      PlaySound(SE_TENSOU_BACK);
      s->mode[1]++;
      break;
    case 3:
      s->d.y -= 16;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= PIXEL(96)) break;
      s->flags &= ~DISPLAY;
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x080c5af4
static void X_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  u8 i;
  ApLoadSheet(&sXSheet);
  setUp(p, MOTION(AP_SHEET_Z2_X, 0));
  s->d.y = 0;
  for (i = 0; i < 96; i++) {
    s->d.y += 16;
    s->coord.y -= s->d.y;
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  X_Update(p);
}

ROUTINE(gApZ2XRoutine, X_Init, X_Update);

#endif  // AP
