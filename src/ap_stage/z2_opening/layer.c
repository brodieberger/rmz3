// Zero 2's OPENING AKA Sand Wilderness

#include "ap_import.h"
#include "gba/gba.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "camera.h"
#include "definition.h"
#include "enemy.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "constants/ap_z2_songs.h"
#include "constants/metatile.h"
#include "constants/motion/static.h"
#include "constants/motion/ap_sheet.h"
#include "palette_animation.h"
#include "system.h"
#include "zero.h"
#include "trig.h"
#include "vfx.h"

#if AP

// Palette animations 0..3 by stretch of desert, 28 for sandstorm

extern const PlttAnimData gApZ2Opening_PlttAnim0, gApZ2Opening_PlttAnim1, gApZ2Opening_PlttAnim2, gApZ2Opening_PlttAnim3,
    gApZ2Opening_PlttAnim28;
extern const AnimCmd* const gApZ2Opening_PlttAnimScript0[], *const gApZ2Opening_PlttAnimScript1[],
    *const gApZ2Opening_PlttAnimScript2[], *const gApZ2Opening_PlttAnimScript3[], *const gApZ2Opening_PlttAnimScript28[];

// 32x32 maps for sky and sandstorm
extern const u16 gApZ2Opening_SkyMap[], gApZ2Opening_SandstormMap[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

/*
  0x08314fc8: by screen, bit for each palette animation 0..3
*/
static const u8 sPaletteAnimsByScreen[64 + 1] = {
    2, 2, 3, 3, 3, 2, 0, 1, 0, 1, 1, 1, 1, 4, 1, 0, 0, 8, 1, 0, 1,
};

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

static void Stage_Nop(Coords32* _ UNUSED) {}

struct Entity* CreatePantheonHunter(Coords32* c, u8 r1, u8 r2);
extern const GameCommand gApZ2Opening_WaveScript[];
struct Entity* ApZ2CreateRock(u8 kind, const Coords32* at, const Coords32* d);

// 0x0800a6ec
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2OpeningState* w = &gOverworld.work.apZ2Opening;
  s32 i;
  for (i = 0; i < 32; i++) {
    w->hunters[i] = NULL;
  }
  w->sent = w->timer = 0;
  w->sinking = w->sunk = 0;
}

/*
  0x08015e78: left of x 1568, Hunter every 30 frames, five out at most, 32 a wave. Past x 3168 rest removed.
*/
#define HUNTER_WAITING 4
#define HUNTER_WALK 6
#define HUNTER_PAUSE 9

// Zero 2's Hunter state 10, 0x08067200
static void runIn(struct Entity* h) {
  if (h->mode[0] != ENTITY_UPDATE) return;
  if (h->mode[1] >= HUNTER_WALK && h->mode[1] <= HUNTER_PAUSE) {
    h->mode[1] = HUNTER_WAITING;
    h->mode[2] = 0;
    SetMotion(h, MOTION(SM019_PANTHEON_HUNTER, 9));
    SET_XFLIP(h, TRUE);
    ((u8*)h)[0xBD] = TRUE;  // facing
  } else if (h->mode[1] != HUNTER_WAITING) {
    return;
  }
  UpdateEntityAnim(h);
  if (FUN_080098a4(h->coord.x + 0x880 + PIXEL(1), h->coord.y - PIXEL(8)) == 0) h->coord.x += PIXEL(1);
}

static void hunterWave(void) {
  static const Coords32 from = {PIXEL(1184), PIXEL(464)};
  struct ApZ2OpeningState* w = &gOverworld.work.apZ2Opening;
  s32 x = (pZero2->s).coord.x;
  s32 i, down = 0;

  if (gStageRun.vm.active & VM_ACTIVE) return;
  for (i = 0; i < w->sent; i++) {
    if (w->hunters[i] == NULL || w->hunters[i]->mode[0] > ENTITY_UPDATE) {
      w->hunters[i] = NULL;
      down++;
    } else {
      runIn(w->hunters[i]);
    }
  }
  if (x <= PIXEL(1568)) {
    if (w->sent < 32) {
      if (w->timer != 0) {
        w->timer--;
      } else if (w->sent - down <= 4) {
        w->hunters[w->sent] = CreatePantheonHunter((Coords32*)&from, 0, 0);
        if (w->hunters[w->sent] != NULL) {
          w->timer = 30;
          w->sent++;
        }
      }
    }
    if (down == 32) {
      SetScript(&gStageRun.vm, gApZ2Opening_WaveScript);
      w->sent = w->timer = 0;
    }
  }
  if (x >= PIXEL(3168)) {
    for (i = 0; i < w->sent; i++) {
      if (w->hunters[i] != NULL) {
        w->hunters[i]->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(w->hunters[i]);
        SET_ENEMY_ROUTINE(w->hunters[i], ENTITY_DISAPPEAR);
        w->hunters[i] = NULL;
      }
    }
  }
}

// 0x0800a720
static void Stage_Update(Coords32* c) {
  u8 screen = gScreenX[c->x >> 12];
  u8 anims = sPaletteAnimsByScreen[screen] | sPaletteAnimsByScreen[screen + 1];

  gOverworld.work.apZ2Opening.sunk = gOverworld.work.apZ2Opening.sinking;
  hunterWave();

  animate(anims & 1, PLTT_ANIM_ID(0), &gApZ2Opening_PlttAnim0, gApZ2Opening_PlttAnimScript0);
  animate(anims & 2, PLTT_ANIM_ID(1), &gApZ2Opening_PlttAnim1, gApZ2Opening_PlttAnimScript1);
  animate(anims & 4, PLTT_ANIM_ID(2), &gApZ2Opening_PlttAnim2, gApZ2Opening_PlttAnimScript2);
  animate(anims & 8, PLTT_ANIM_ID(3), &gApZ2Opening_PlttAnim3, gApZ2Opening_PlttAnimScript3);
}

// 0x0800a7ec
static void Stage_Exit(Coords32* _ UNUSED) {
  gBlendRegBuffer.bldclt = 0;
  RemovePaletteAnimation(PLTT_ANIM_ID(0));
  RemovePaletteAnimation(PLTT_ANIM_ID(1));
  RemovePaletteAnimation(PLTT_ANIM_ID(2));
  RemovePaletteAnimation(PLTT_ANIM_ID(3));
  RemovePaletteAnimation(PLTT_ANIM_ID(28));
}

const StageFunc gApZ2Opening_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Nop,
    Stage_Exit,
};

/*
  0x08013a60: spawn areas by x
  0: start
  1: first Golem
  2: between Golems
  3: second Golem
  4: rest of stage
*/
u8 gApZ2Opening_Area(Coords32* c) {
  if (c->x < PIXEL(3216)) return 0;
  if (c->x < PIXEL(3456)) return 1;
  if (c->x < PIXEL(4080)) return 2;
  if (c->x < PIXEL(4320)) return 3;
  return 4;
}

// --------------------------------------------
/*
  Sinking sand at x 5216..6816. Zero 2's solid 0 and stage code it calls.
*/

struct SandCell {
  s32 x16;
  u16 y16;
  u16 _;
  u32 level;
};

// 0x08314e10: {x16, surface y16, level}, left to right
static const struct SandCell sSandCells[26] = {
    {326, 24, 0, 0}, {327, 23, 0, 1}, {330, 23, 0, 1}, {331, 24, 0, 0},
    {336, 26, 0, 0}, {337, 24, 0, 1}, {342, 24, 0, 2}, {343, 26, 0, 1},
    {344, 26, 0, 0}, {348, 25, 0, 0}, {359, 25, 0, 0}, {364, 27, 0, 0},
    {365, 25, 0, 1}, {366, 24, 0, 2}, {372, 24, 0, 2}, {373, 25, 0, 1},
    {374, 27, 0, 0}, {393, 27, 0, 0}, {394, 27, 0, 1}, {395, 24, 0, 2},
    {403, 22, 0, 0}, {407, 22, 0, 0}, {408, 22, 0, 1}, {420, 24, 0, 0},
    {423, 24, 0, 0}, {426, 26, 0, 0},
};

// 0x08315098..0x08315218: each cell's opened column, surface down
static const u16 sSandPatch0[] = {1, 6, 0x0, 0x0, 0x0, 0x0, 0x0, 0xcf};
static const u16 sSandPatch1[] = {1, 7, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbe, 0xce};
static const u16 sSandPatch2[] = {1, 7, 0x0, 0x0, 0xbb, 0xcb, 0xdb, 0xeb, 0xf8};
static const u16 sSandPatch3[] = {1, 6, 0x0, 0xbc, 0xcc, 0xdc, 0xec, 0xf8};
static const u16 sSandPatch4[] = {1, 4, 0xcf, 0x108, 0x108, 0x108};
static const u16 sSandPatch5[] = {1, 6, 0x0, 0xbe, 0xce, 0xde, 0xee, 0xf8};
static const u16 sSandPatch6[] = {1, 6, 0x0, 0x0, 0xbb, 0xcb, 0xdb, 0xeb};
static const u16 sSandPatch7[] = {1, 4, 0xbc, 0xcc, 0xdc, 0xec};
static const u16 sSandPatch8[] = {1, 4, 0xbd, 0xcd, 0xdd, 0x108};
static const u16 sSandPatch9[] = {1, 5, 0x0, 0xbe, 0xce, 0xde, 0xee};
static const u16 sSandPatch10[] = {1, 5, 0x0, 0xbb, 0xcb, 0xdb, 0xeb};
static const u16 sSandPatch11[] = {1, 3, 0xbf, 0x108, 0x108};
static const u16 sSandPatch12[] = {1, 5, 0x0, 0x0, 0xcf, 0x108, 0x108};
static const u16 sSandPatch13[] = {1, 6, 0x0, 0x0, 0xbe, 0xce, 0xde, 0xee};
static const u16 sSandPatch14[] = {1, 6, 0x0, 0x0, 0x0, 0xbb, 0xcb, 0xdb};
static const u16 sSandPatch15[] = {1, 5, 0x0, 0x0, 0xbc, 0xcc, 0xdc};
static const u16 sSandPatch16[] = {1, 3, 0xbd, 0xcd, 0xdd};
static const u16 sSandPatch17[] = {1, 3, 0x0, 0xbf, 0x108};
static const u16 sSandPatch18[] = {1, 3, 0x0, 0xcf, 0x108};
static const u16 sSandPatch19[] = {1, 6, 0x0, 0x0, 0x0, 0xbe, 0xce, 0xde};
static const u16 sSandPatch20[] = {1, 8, 0x0, 0x0, 0x0, 0x0, 0xbb, 0xcb, 0xdb, 0xeb};
static const u16 sSandPatch21[] = {1, 8, 0x0, 0x0, 0x0, 0x0, 0x0, 0xcf, 0x108, 0x108};
static const u16 sSandPatch22[] = {1, 8, 0x0, 0x0, 0x0, 0x0, 0xbe, 0xce, 0xde, 0xee};
static const u16 sSandPatch23[] = {1, 6, 0x0, 0xbe, 0xce, 0xde, 0xee, 0xf8};
static const u16 sSandPatch24[] = {1, 6, 0x0, 0x0, 0x0, 0xbb, 0xcb, 0xdb};
static const u16 sSandPatch25[] = {1, 4, 0x0, 0xbe, 0xce, 0xde};

// 0x0831523c
static const u16* const sSandPatches[26] = {
    sSandPatch0, sSandPatch1, sSandPatch2, sSandPatch3, sSandPatch4, sSandPatch5,
    sSandPatch6, sSandPatch7, sSandPatch8, sSandPatch9, sSandPatch10, sSandPatch11,
    sSandPatch12, sSandPatch13, sSandPatch14, sSandPatch15, sSandPatch16, sSandPatch17,
    sSandPatch18, sSandPatch19, sSandPatch20, sSandPatch21, sSandPatch22, sSandPatch23,
    sSandPatch24, sSandPatch25,
};

// 0x08315218: clears 15 metatiles below cell's chunk row
static const u16 sSandClear[2 + 15] = {1, 15};

static s32 sandCellAt(s32 x) {
  s32 i;
  for (i = 0; i < 26; i++) {
    if (sSandCells[i].x16 == x >> 12) return i;
  }
  return -1;
}

// 0x0800ad24
static void sinkCell(s32 x) {
  struct ApZ2OpeningState* w = &gOverworld.work.apZ2Opening;
  s32 i = sandCellAt(x), j;
  if (i < 0) return;
  w->sinking |= 1 << i;
  for (j = i + 1; j < 26; j++) {
    if (sSandCells[j].x16 != sSandCells[j - 1].x16 + 1 || sSandCells[j].level >= sSandCells[j - 1].level) break;
    w->sinking |= 1 << j;
  }
  for (j = i - 1; j >= 0; j--) {
    if (sSandCells[j].x16 != sSandCells[j + 1].x16 - 1 || sSandCells[j].level >= sSandCells[j + 1].level) break;
    w->sinking |= 1 << j;
  }
}

// 0x0800adf8
static bool32 cellSunk(s32 x) {
  s32 i = sandCellAt(x);
  return i >= 0 && (gOverworld.work.apZ2Opening.sunk & (1 << i));
}

// 0x0800ae3c
static void openCell(s32 x) {
  s32 i = sandCellAt(x);
  if (i < 0) return;
  PatchMetatileMap(sSandCells[i].x16, sSandCells[i].y16, sSandPatches[i]);
  PatchMetatileMap(sSandCells[i].x16, ((sSandCells[i].y16 + 10) / 10) * 10, sSandClear);
  PlaySound(SE_Z2_DESERT_TAIL_SLAM);
}

static void SandBlock_Init(struct Solid* p);
static void SandBlock_Wait(struct Solid* p);
static void SandBlock_Sink(struct Solid* p);
static void SandBlock_Disappear(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2SandBlockRoutine = {
    [ENTITY_INIT] =      (SolidFunc)SandBlock_Init,
    [ENTITY_UPDATE] =    (SolidFunc)SandBlock_Wait,
    [ENTITY_DIE] =       (SolidFunc)SandBlock_Sink,
    [ENTITY_DISAPPEAR] = (SolidFunc)SandBlock_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08348710
static const struct Rect sSandBlockSize = {0, 32001, 4096, -1534};

// 0x08348718, 0x08348738: shake offsets in pixels
static const s32 sShakeX[8] = {-1, 0, 1, 0, -1, 0, 1, 0};
static const s32 sShakeY[8] = {-1, 1, 0, -1, 1, -1, 0, 1};

// 0x080bf878
static void SandBlock_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->d.x = s->d.y = 0;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + 1;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  SandBlock_Wait(p);
}

static bool32 zeroOnBlock(struct Entity* s) {
  static const struct Rect sensor = {0, 0x7600, 0x1000, -0x200};
  const struct Rect* z = &(gZeroCollisions[pZero2->posture].range);
  s32 x = (pZero2->s).coord.x + (((pZero2->s).flags & X_FLIP) ? -z->x : z->x) - s->coord.x;
  s32 y = (pZero2->s).coord.y + z->y - (s->coord.y + sensor.y);
  s32 w = (u16)sensor.w + z->w;
  s32 h = (u16)sensor.h + z->h;
  return x * 2 > -w && x * 2 < w && y * 2 > -h && y * 2 < h;
}

// 0x080bf8d8: hidden until cell gives way
static void SandBlock_Wait(struct Solid* p) {
  struct Entity* s = &p->s;
  if (zeroOnBlock(s)) sinkCell(s->coord.x);
  if (!cellSunk(s->coord.x)) return;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SAND_BLOCK, s->work[0]));
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  SandBlock_Sink(p);
}

// 0x080bf964
static void SandBlock_Sink(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  switch (s->mode[1]) {
    case 0:
      openCell(s->coord.x);
      s->flags2 |= ENTI_PHYSICS;
      s->size = &sSandBlockSize;
      s->physicsAttr = MTATTR_CONVEYOR1 | SHAPE_BLOCK;
      (s->spr).c = (struct Coord*)&s->unk_coord;
      s->work[2] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      s->unk_coord.x = s->coord.x + PIXEL(sShakeX[s->work[2] & 7]);
      s->unk_coord.y = s->coord.y + PIXEL(sShakeY[s->work[2] & 7]);
      s->work[2]++;
      at.x = s->coord.x + ((s->work[2] & 1) ? PIXEL(9) : -PIXEL(9));
      at.y = s->coord.y + s->work[2] * PIXEL(8);
      if (GetMetatileAttr(at.x, at.y)) CreateSmoke(3, &at);
      if (s->work[2] <= 29) break;
      s->unk_coord = s->coord;
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if (s->d.y <= 0x6FF) s->d.y += 32;
      s->coord.y += s->d.y;
      s->unk_coord.y = s->coord.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(48)) {
        s->flags &= ~DISPLAY;
        s->flags2 &= ~ENTI_PHYSICS;
        SET_SOLID_ROUTINE(p, ENTITY_EXIT);
      }
      break;
  }
}

// 0x080bf834
static void SandBlock_Disappear(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// Copies 32x32 map into layer's screen, unscrolled
static void LoadLayerMap(struct StageLayer* l, const u16* map) {
  u16 n = (u16)l->bgIdx >> 4;

  BGCNT16(n) = (u16)(l->prio | l->screenBase | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
  RESET_BGOFS(n);
  CpuFastSet(map, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
}

#define SHIMMER unk_10

// 0x0800a818: sky, BG3
static void Sky_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    LoadLayerMap(l, gApZ2Opening_SkyMap);
    l->SHIMMER = 0;
    l->phase++;
  }
  l->SHIMMER += 4;
}

/*
  0x0800a888: BG3 offsets per line by HBlank DMA
*/
static void Sky_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u32* lines = Malloc(DISPLAY_HEIGHT * 4);
  s32 y, horizon;

  if (lines == NULL) return;
  gIntrManager.reservedDma0[0] = (u32)lines;
  gIntrManager.reservedDma0[1] = REG_ADDR_BG3HOFS;
  gIntrManager.reservedDma0[2] = 0xA6600001;  // one word every HBlank

  for (y = 0; y < 82; y++) {
    lines[y] = 0;
  }
  for (y = 82; y <= 104; y++) {
    lines[y] = ((u32)(SIN(l->SHIMMER - y * 16) >> 8) << 16) | (u16)(SIN(l->SHIMMER * 8 - y * 32) >> 6);
  }
  horizon = ((320 - l->viewportLeftTopPixel.y) >> 3) + 117;
  if (horizon > DISPLAY_HEIGHT) horizon = DISPLAY_HEIGHT;
  for (y = 105; y <= 115; y++) {
    lines[y] = 0;
  }
  for (y = 116; y < horizon; y++) {
    lines[y] = (u32)(116 - y) << 16;
  }
  for (y = horizon; y < DISPLAY_HEIGHT; y++) {
    lines[y] = ((u32)(117 - horizon) << 16) | (l->viewportLeftTopPixel.x >> 2);
  }
}

// 0x0800a998: far dunes, by which third of desert camera is in
static void FarBackground_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 screen;

  if (l->phase != 0) return;
  screen = gScreenX[l->viewportLeftTopPixel.x >> 4];
  l->scrollPower.x = 352;
  if (screen <= 11) {
    l->scrollPower.y = 256;
    l->scroll.x = -720, l->scroll.y = -160;
  } else if (screen <= 21) {
    l->scrollPower.y = 256;
    l->scroll.x = -1536, l->scroll.y = -160;
  } else {
    l->scrollPower.y = 352;
    l->scroll.x = -2576, l->scroll.y = -128;
  }
  l->phase++;
}

#define STORM_ON unk_10
#define STORM_LEVEL unk_12

/*
  0x0800aa08: sandstorm, BG2 blended over everything.
  gOverworld.state[0]:
    0: dies down
    1: full strength
    2: builds up
    3: builds past full
*/
static void Sandstorm_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  u8 storm = gOverworld.state[0];

  if (l->phase == 0) {
    LoadLayerMap(l, gApZ2Opening_SandstormMap);
    gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
    l->STORM_ON = FALSE;
    l->STORM_LEVEL = 0;
    l->phase++;
  }

  if (storm != 0 && !l->STORM_ON) {
    l->STORM_LEVEL = (storm == 1) ? 256 : 0;
    gVideoRegBuffer.dispcnt |= DISPCNT_BG0_ON << n;
    gBlendRegBuffer.bldclt = 0x3B44;  // BG2 over everything
    ApStartPaletteAnimation(PLTT_ANIM_ID(28), &gApZ2Opening_PlttAnim28, gApZ2Opening_PlttAnimScript28, 0);
    l->STORM_ON = TRUE;
  } else if (storm == 0) {
    l->STORM_ON = FALSE;
  }

  if (l->STORM_ON) {
    if (l->STORM_LEVEL < ((storm == 3) ? 384 : 256)) l->STORM_LEVEL++;
  } else if (l->STORM_LEVEL != 0 && --l->STORM_LEVEL == 0) {
    gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
    gBlendRegBuffer.bldclt = 0;
    RemovePaletteAnimation(PLTT_ANIM_ID(28));
  }

  // Only written during a storm so other blends are kept
  if (l->STORM_LEVEL == 0) {
  } else if (l->STORM_LEVEL < 256) {
    gBlendRegBuffer.bldalpha = (l->STORM_LEVEL >> 5) | ((16 - (l->STORM_LEVEL >> 5)) << 8);
  } else {
    gBlendRegBuffer.bldalpha = (8 - ((l->STORM_LEVEL - 256) >> 6)) | ((8 - ((l->STORM_LEVEL - 256) >> 5)) << 8);
  }
  BGnHOFS(n) += 12;
  BGnVOFS(n) -= 2;
  StepPaletteAnimation(PLTT_ANIM_ID(28));
}

// 0x0800abcc
static void BlendOff_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  gBlendRegBuffer.bldclt = 0;
  l->phase++;
}

#define CAVE_IN unk_10
#define CAVE_IN_ROWS unk_12

// 0x08315008: cave-in metatiles from (436, 22). 0 keeps cell.
static const u16 sCaveIn[6][12] = {
    {0x000, 0x380, 0x381, 0x382, 0x383, 0x000, 0x000, 0x384, 0x385, 0x386, 0x387, 0x000},
    {0x000, 0x388, 0x389, 0x38a, 0x38b, 0x000, 0x38c, 0x38d, 0x38e, 0x38f, 0x390, 0x000},
    {0x000, 0x391, 0x392, 0x393, 0x394, 0x000, 0x395, 0x396, 0x397, 0x398, 0x399, 0x000},
    {0x000, 0x39a, 0x39b, 0x39c, 0x39d, 0x000, 0x39e, 0x39f, 0x3a0, 0x3a1, 0x3a2, 0x000},
    {0x000, 0x3a3, 0x3a4, 0x3a5, 0x3a6, 0x000, 0x3a7, 0x3a8, 0x3a9, 0x3aa, 0x3ab, 0x000},
    {0x000, 0x3ac, 0x3ad, 0x3ae, 0x3af, 0x3b0, 0x3b1, 0x3b2, 0x3b3, 0x3b4, 0x3b5, 0x000},
};

/*
  0x0800abe8: ground breaks open where boss rises, once gOverworld.state[1] set
*/
static void CaveIn_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 patch[4] = {2, 1, 0, 0};
  s16 row, col;
  Coords32 at, d;

  if (l->phase == 0) {
    l->CAVE_IN = l->CAVE_IN_ROWS = 0;
    l->phase++;
  }
  if (gOverworld.state[1] != 0 && l->CAVE_IN < 160) l->CAVE_IN++;
  if ((l->CAVE_IN >> 3) == l->CAVE_IN_ROWS) return;

  for (row = 0; row <= l->CAVE_IN_ROWS; row++) {
    col = row - (l->CAVE_IN_ROWS - 10);
    if (col < 0 || row > 5) continue;
    patch[2] = sCaveIn[row][col];
    PatchMetatileMap(col + 436, row + 22, patch);
    at.x = PIXEL(16) * col + PIXEL(7000);
    at.y = PIXEL(16) * row + PIXEL(370);
    d.x = ((2 * col + row) % 5 - 2) * 64;
    d.y = -((col * row * 2) % 3) * PIXEL(1);
    ApZ2CreateRock((col + row) % 2 + 2, &at, &d);
    CreateSmoke(3, &at);
  }
  l->CAVE_IN_ROWS = l->CAVE_IN >> 3;
}

/*
  Zero 2's layer routines for this stage
  2: sky with heat shimmer
  3: far background
  4: sandstorm
  5: blending off
  6: cave-in for boss
*/
// clang-format off
const StageLayerRoutine gApZ2Opening_LayerRoutines[7] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Sky_Update, Sky_Draw, NULL},
    [3] = {FarBackground_Update, DrawGeneralStageLayer, NULL},
    [4] = {Sandstorm_Update, NULL, NULL},
    [5] = {BlendOff_Update, DrawGeneralStageLayer, NULL},
    [6] = {CaveIn_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

#endif  // AP
