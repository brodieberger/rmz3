// Zero 2's TRAIN AKA Train

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "definition.h"
#include "global.h"
#include "gpu_regs.h"
#include "collision.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "quake.h"
#include "score.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "trig.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

extern const PlttAnimData gApZ2Train_PlttAnim62, gApZ2Train_PlttAnim63, gApZ2Train_PlttAnim64;
extern const AnimCmd* const gApZ2Train_PlttAnimScript62[], *const gApZ2Train_PlttAnimScript63[],
    *const gApZ2Train_PlttAnimScript64[];
extern const ColorGraphic gApZ2Train_TileAnim[4];
extern const u16 gApZ2Train_Sky0Map[], gApZ2Train_Sky1Map[], gApZ2Train_Near0Map[], gApZ2Train_Near1Map[],
    gApZ2Train_FrontCarMap[], gApZ2Train_RearCarMap[];
extern const u8 gApZ2Train_NightMap[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Train_PlttAnim##n, gApZ2Train_PlttAnimScript##n)
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])
#define ON_ROOF (TILESET(0) == 1)
#define INSIDE (TILESET(0) == 2)

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

// 0x0800d578
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2TrainState* w = &gOverworld.work.apZ2Train;
  w->time = 0;
  w->scenery = 0;
  w->rumble = 0;
  PlaySound(SE_Z2_TRAIN_RUMBLE);
}

/*
  0x0800d5b8, 0x080182d8: shakes every 48 frames on roof, camera held past x 8048
*/
static void Stage_Update(Coords32* leftTop) {
  struct ApZ2TrainState* w = &gOverworld.work.apZ2Train;
  w->time++;
  if (ON_ROOF) {
    if (++w->scenery == 72) w->scenery = 0;
    if (++w->rumble > 47) {
      w->rumble = 0;
      AppendQuake(1, leftTop);
    }
  }
  if (gStageRun.checkpoint == 1 && (pZero2->s).coord.x >= PIXEL(8048)) {
    gStageRun.vm.camera.left = PIXEL(8032);
  }
}

static const u8 sScenery[18] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 3, 2, 0, 3, 2};

// 0x0800d628: roof's passing scenery
static void Stage_Draw(Coords32* _ UNUSED) {
  const ColorGraphic* g;
  if (ON_ROOF) {
    g = &gApZ2Train_TileAnim[sScenery[gOverworld.work.apZ2Train.scenery >> 2]];
    RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
    LoadPalette(&g->pal, 0);
  }
  ANIMATE(ON_ROOF, 62);
  ANIMATE(INSIDE, 63);
  ANIMATE(INSIDE, 64);
}

// 0x0800d784
static void Stage_Exit(Coords32* _ UNUSED) {
  StopSound(SE_Z2_TRAIN_RUMBLE);
  REMOVE(62);
  REMOVE(63);
  REMOVE(64);
}

const StageFunc gApZ2Train_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013d2c: spawn areas
  0: roof
  1: inside, past x 7760
  2: boss's room, left of x 720
*/
u8 gApZ2Train_Area(Coords32* c) {
  if (c->x > PIXEL(7760)) return 1;
  if (c->x > 0x2CFFF) return 0;
  return 2;
}

// --------------------------------------------

#define SKY_SCROLL (*(s32*)l->work.raw)

static void loadMap(struct StageLayer* l, const u16* left, const u16* right) {
  u16 n = (u16)l->bgIdx >> 4;
  BGCNT16(n) = (u16)(l->prio | l->screenBase | 0x4044);
  RequestBgMapTransfer((u16*)left, (void*)((BGCNT16(n) & 0x1F00) << 3), BG_SCREEN_SIZE);
  RequestBgMapTransfer((u16*)right, (void*)(((BGCNT16(n) & 0x1F00) << 3) + BG_SCREEN_SIZE), BG_SCREEN_SIZE);
}

// 0x0800db60: skyline
static void Sky_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    loadMap(l, gApZ2Train_Sky0Map, gApZ2Train_Sky1Map);
    SKY_SCROLL = 0;
    l->phase++;
  }
  SKY_SCROLL += 10;
}

/*
  0x0800dbf0: BG2 and BG3 offsets by scanline, HBlank DMA
  BG2: top rows held, skyline at half speed, rest at full
  BG3: near city at a quarter
*/
static void Sky_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u32* t = Malloc(160 * 8);
  u16 x = l->viewportLeftTopPixel.x + SKY_SCROLL;
  u16 y = l->viewportLeftTopPixel.y;
  u16 v;
  s32 i = 0;
  if (t == NULL) return;
  gIntrManager.reservedDma0[0] = (u32)t;
  gIntrManager.reservedDma0[1] = REG_ADDR_BG2HOFS;
  gIntrManager.reservedDma0[2] = 0xA6600002;
  for (; i < 160 && (y >> 1) + i <= 143; i++) t[i * 2] = (u16)-i << 16 | (u16)(x >> 1);
  v = (y >> 1) - 144;
  for (; i < 160 && y + i <= 287; i++) t[i * 2] = v << 16 | (u16)(x >> 1);
  v = y - 224;
  for (; i < 160; i++) t[i * 2] = v << 16 | x;

  i = 0;
  v = y / 6 + 112;
  for (; i < 160 && v + i <= 175; i++) t[i * 2 + 1] = v << 16;
  v = (y >> 2) + 88;
  for (; i < 160 && v + i <= 175; i++) t[i * 2 + 1] = (u16)(175 - i) << 16;
  for (; i < 160; i++) t[i * 2 + 1] = v << 16 | (u16)(x >> 2);
}

// 0x0800dd68: near city, moved by the skyline's
static void Near_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  loadMap(l, gApZ2Train_Near0Map, gApZ2Train_Near1Map);
  l->phase++;
}

// Boss's room: two cars bobbing on sine paths, stood on through hazards
static const Coords32 sCarAt[2] = {{PIXEL(336), PIXEL(432)}, {PIXEL(496), PIXEL(432)}};
static const struct Rect sCarSize = {0, 16128, -32768, -512};

static void loadCar(struct StageLayer* l, const u16* map) {
  u16 n = (u16)l->bgIdx >> 4;
  u32 zero = 0;
  BGCNT16(n) = (u16)(l->screenBase | 0x4046);
  CpuFastSet(map, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
  CpuFastSet(&zero, (u8*)SCREEN_ADDR(n) + BG_SCREEN_SIZE, BG_SCREEN_SIZE / 4 | 1 << 24);
  gOverworld.work.apZ2Train.time = 128;
}

// Car's offset from its rest, BG and hazard moved with it
static void moveCar(struct StageLayer* l, u8 car, s32 dx, s32 dy, s16 left) {
  struct ApZ2TrainState* w = &gOverworld.work.apZ2Train;
  u16 n = (u16)l->bgIdx >> 4;
  BGnHOFS(n) = l->viewportLeftTopPixel.x + left - (dx >> 8);
  BGnVOFS(n) = l->viewportLeftTopPixel.y - 480 - (dy >> 8);
  w->cars[car].x = sCarAt[car].x + dx;
  w->cars[car].y = sCarAt[car].y + dy;
  AppendHazard(0xE001 + car, MTATTR_CONVEYOR1 | SHAPE_BLOCK, &w->cars[car], &sCarSize);
}

// 0x0800d7a4
static void FrontCar_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2TrainState* w = &gOverworld.work.apZ2Train;
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    loadCar(l, gApZ2Train_FrontCarMap);
    l->phase++;
  }
  moveCar(l, 0, SIN((u8)w->time) * 8, SIN((u8)(w->time >> 2)) * 8 + 0x800, -272);
  w->frontEdge = 128 - BGnHOFS(n);
}

// 0x0800d914: window 1 splits screen between the cars
static void RearCar_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2TrainState* w = &gOverworld.work.apZ2Train;
  u16 n = (u16)l->bgIdx >> 4;
  u16 mid, x;
  if (l->phase == 0) {
    loadCar(l, gApZ2Train_RearCarMap);
    gWindowRegBuffer.dispcnt |= DISPCNT_WIN1_ON;
    gWindowRegBuffer.winin[1] = 0xF7;
    gWindowRegBuffer.winin[2] = (gWindowRegBuffer.winin[2] | 10) & ~4;
    gWindowRegBuffer.winV.half[1] = 160;
    l->phase++;
  }
  moveCar(l, 1, SIN((u8)((w->time >> 1) + 64)) * 8, SIN((u8)((w->time >> 3) + 64)) * 8 + 0x800, -384);
  w->rearEdge = 48 - BGnHOFS(n);
  mid = (w->rearEdge + w->frontEdge) >> 1;
  if (mid < 120) {
    w->split = (w->split * 15 + ((w->rearEdge - mid + 2) << 8)) / 16;
  } else {
    w->split = (w->split * 15 + ((w->frontEdge - mid - 2) << 8)) / 16;
  }
  x = mid + (w->split >> 8);
  if (x > w->rearEdge) x = w->rearEdge;
  if (x < w->frontEdge) x = w->frontEdge;
  gWindowRegBuffer.winH.half[1] = x & 0xFF;
}

// 0x0800db44
static void RearCar_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 4;
}

#define NIGHT_FRAME (l->unk_10)

// 0x0800dde4
static void Night_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    BGCNT16((u16)l->bgIdx >> 4) = (u16)(l->screenBase | 0x4047);
    NIGHT_FRAME = 0;
    l->phase++;
  }
  NIGHT_FRAME++;
}

// 0x0800de20: eight frames, two maps each
static void Night_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  const u8* map = gApZ2Train_NightMap + ((NIGHT_FRAME >> 1) & 7) * 2 * 0x808;
  RequestBgMapTransfer((u16*)map, (void*)SCREEN_BASE(n), BG_SCREEN_SIZE);
  RequestBgMapTransfer((u16*)(map + 0x808), (void*)(SCREEN_BASE(n) + BG_SCREEN_SIZE), BG_SCREEN_SIZE);
  BGnHOFS(n) = l->viewportLeftTopPixel.x - 240;
  BGnVOFS(n) = l->viewportLeftTopPixel.y - 224;
}

/*
  Zero 2's layer routines for this stage
  2, 3: boss's room's front and rear cars
  4: skyline
  5: near city
  6: boss's room's night
*/
// clang-format off
const StageLayerRoutine gApZ2Train_LayerRoutines[7] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {FrontCar_Update, NULL, NULL},
    [3] = {RearCar_Update, NULL, RearCar_Exit},
    [4] = {Sky_Update, Sky_Draw, NULL},
    [5] = {Near_Update, NULL, NULL},
    [6] = {Night_Update, Night_Draw, NULL},
};
// clang-format on

// --------------------------------------------
/*
  Zero 2's solid 20, the supplies
  work0:
    0: stack, calls carriers once flag 0 is set
    1: crate, work1 its place
*/

#define CRATE(n) MOTION(AP_SHEET_Z2_CRATE, (n))
#define STOLEN gStageRun.unk_0a  // bit 1 + crate, bit 0 is mid-boss's
#define FLAGS(s) ((s)->scriptEntity->flags)

struct Supplies {
  OBJECT_HDR;
  u32 _b4;
  bool8 called;  // 0xB8, a carrier asked for
  u8 callsLeft;  // 0xB9
  u8 busy[10];   // 0xBA, crate being carried or falling back
};
static_assert(sizeof(struct Supplies) == sizeof(struct Solid));

struct Crate {
  OBJECT_HDR;
  s32 baseY;               // 0xB4
  u32 _b8;
  struct Entity* carrier;  // 0xBC
  u32 _c0;
};
static_assert(sizeof(struct Crate) == sizeof(struct Solid));

struct Entity* ApZ2CreateCrateCarrier(struct Entity* crate, u8 kind, u8 from);

static const s32 sCrateX[10] = {PIXEL(-16), PIXEL(16), PIXEL(-48), PIXEL(48), PIXEL(-16),
                                PIXEL(16),  PIXEL(-48), PIXEL(48), PIXEL(-16), PIXEL(16)};
static const s32 sCrateY[10] = {PIXEL(-64), PIXEL(-64), PIXEL(-32), PIXEL(-32), PIXEL(-32), PIXEL(-32), 0, 0, 0, 0};
static const u8 sCratePrio[10] = {28, 28, 29, 29, 29, 29, 30, 30, 30, 30};
// Crate that must be gone first, and where its carrier comes from
static const u8 sCrateAfter[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 2, 3, 4, 5};
static const u8 sCarrierFrom[10] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1};
static const u16 sCrateTiles[6] = {2, 2, 0x15C, 0x15C, 0x15C, 0x15C};
static const u16 sNoCrateTiles[6] = {2, 2, 0, 0, 0, 0};
static const struct Rect sCarriedSize = {0, -PIXEL(16), PIXEL(32), PIXEL(32)};

static void Supplies_Init(struct Supplies* p);
static void Supplies_Update(struct Supplies* p);
static void Supplies_Die(struct Supplies* p);

// clang-format off
const SolidRoutine gApZ2SuppliesRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Supplies_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Supplies_Update,
    [ENTITY_DIE] =       (SolidFunc)Supplies_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static bool8 stolen(u8 crate) { return (STOLEN & (2 << crate)) != 0; }

static void patchCrate(struct Entity* s, const u16* tiles) {
  PatchMetatileMap((s->coord.x >> 12) - 1, (s->coord.y >> 12) - 2, tiles);
}

// 0x080ce0f0
static void createCrate(struct Entity* stack, u8 n) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p == NULL) return;
  INIT_SOLID_ROUTINE(p, SOLID_Z2_SUPPLIES);
  p->unk_28 = stack;
  p->work[0] = 1;
  p->work[1] = n;
}

// 0x080ce1a0, 0x080ce2f8
static void Supplies_Init(struct Supplies* p) {
  struct Entity* s = &p->s;
  struct Crate* c = (struct Crate*)p;
  u8 i;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == 0) {
    s->flags |= FLIPABLE;
    p->called = FALSE;
    p->callsLeft = 32;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + PIXEL(1);
    s->work[2] = 56;
    for (i = 0; i < 10; i++) {
      p->busy[i] = FALSE;
      STOLEN &= ~(2 << i);
      createCrate(s, i);
    }
    Supplies_Update(p);
    return;
  }
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, CRATE(0));
  SET_XFLIP(p, FALSE);
  s->renderPrio = sCratePrio[s->work[1]];
  s->coord.x = s->unk_28->coord.x + sCrateX[s->work[1]];
  s->coord.y = s->unk_28->coord.y + sCrateY[s->work[1]];
  patchCrate(s, sCrateTiles);
  c->baseY = s->coord.y;
  c->carrier = NULL;
  Supplies_Update(p);
}

// 0x080ce3c4: done once every crate is gone, or carriers are spent and none is out
static void Stack_Update(struct Supplies* p) {
  struct Entity* s = &p->s;
  u8 i, n;
  if (!(FLAGS(s) & 1)) return;
  for (i = 0; i < 10 && stolen(i); i++) {}
  if (i == 10) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    return;
  }
  if (p->callsLeft == 0) {
    for (i = n = 0; i < 10; i++) {
      if (!p->busy[i] || stolen(i)) n++;
    }
    if (n == 10) SET_SOLID_ROUTINE(p, ENTITY_DIE);
  } else if (!p->called && --s->work[2] == 0xFF) {
    s->work[2] = 56;
    p->called = TRUE;
    p->callsLeft--;
  }
}

// 0x080ce4cc
static void Crate_Update(struct Crate* p) {
  struct Entity* s = &p->s;
  struct Supplies* stack = (struct Supplies*)s->unk_28;
  u8 n = s->work[1];
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (s->coord.y != p->baseY) {
      s->d.y += 64;
      s->coord.y += s->d.y;
      if (s->coord.y > p->baseY) s->coord.y = p->baseY;
    }
    if (s->coord.x < (pZero2->s).coord.x - PIXEL(240)) SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if ((stack->s).mode[0] > ENTITY_UPDATE) {
    s->mode[3]++;
    return;
  }
  if (s->mode[2] == 0) {
    if (FLAGS(&stack->s) & 1) s->mode[2]++;
    return;
  }
  if (p->carrier != NULL && (p->carrier->mode[0] > ENTITY_UPDATE || p->carrier->mode[1] > 4)) {
    p->carrier = NULL;
    s->d.y = 0;
    s->mode[1] = 3;
    return;
  }
  switch (s->mode[1]) {
    case 0:
      if (!stack->called) break;
      if (sCrateAfter[n] != 0xFF && !stolen(sCrateAfter[n])) break;
      stack->called = FALSE;
      stack->busy[n] = TRUE;
      p->carrier = ApZ2CreateCrateCarrier(s, 0, sCarrierFrom[n]);
      s->mode[1]++;
      break;
    case 1:
      if (p->carrier->mode[1] != 4) break;
      s->flags2 |= ENTI_PHYSICS;
      s->size = &sCarriedSize;
      s->physicsAttr = 0x801;
      patchCrate(s, sNoCrateTiles);
      s->mode[1]++;
      break;
    case 2:
      s->coord.y -= PIXEL(1);
      if (s->coord.y >= p->baseY - PIXEL(80)) break;
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Supplies_Die((struct Supplies*)p);
      break;
    case 3:
      s->d.y += 64;
      s->coord.y += s->d.y;
      if (s->coord.y <= p->baseY) break;
      stack->busy[n] = FALSE;
      s->coord.y = p->baseY;
      patchCrate(s, sCrateTiles);
      s->flags2 &= ~ENTI_PHYSICS;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    case 4:
      if (--s->work[2] == 0xFF) s->mode[1] = 0;
      break;
  }
}

static void Supplies_Update(struct Supplies* p) {
  if ((p->s).work[0] == 0) {
    Stack_Update(p);
  } else {
    Crate_Update((struct Crate*)p);
  }
}

// 0x080ce70c, 0x080ce768: stack done after 8 frames, a crate carried off
static void Supplies_Die(struct Supplies* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 1) {
    STOLEN |= 2 << s->work[1];
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    s->work[2] = 8;
    s->mode[2]++;
  }
  if (--s->work[2] != 0xFF) return;
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  gStageRun.missionStatus |= MISSION_SUCCESS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

u8 ApZ2CratesStolen(void) {
  u8 n = 0, i;
  for (i = 0; i < 10; i++) {
    if (stolen(i)) n++;
  }
  return n;
}

// --------------------------------------------
/*
  Zero 2's solid 21, gantry over the roof
  work0:
    0: unseen, sends its pieces past
    1: piece, work1 which
*/

#define GANTRY(n) MOTION(AP_SHEET_Z2_GANTRY, (n))
#define SIDE(n) MOTION(AP_SHEET_Z2_GANTRY_SIDE, (n))

static const motion_t sGantryPieces[12] = {GANTRY(0), GANTRY(1), SIDE(0), SIDE(1), SIDE(2), SIDE(3),
                                           GANTRY(0), GANTRY(1), SIDE(0), SIDE(1), SIDE(2), SIDE(3)};
static const struct Collision sGantryCollision = {
    DDP, FACTION_NEUTRAL, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0x200, -0x7000, 0x2600, 0x1000}};

static void Gantry_Init(struct Solid* p);
static void Gantry_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2GantryRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Gantry_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Gantry_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080ce7cc
static void createPiece(struct Entity* gantry, u8 n) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p == NULL) return;
  INIT_SOLID_ROUTINE(p, SOLID_Z2_GANTRY);
  p->renderPrio = 30;
  p->unk_28 = gantry;
  p->work[0] = 1;
  p->work[1] = n;
}

// 0x080ce870, 0x080ce8b4
static void Gantry_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  u8 n = s->work[1];
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == 0) {
    s->flags |= FLIPABLE;
    s->unk_coord = s->coord;
    s->coord.y -= PIXEL(64);
    Gantry_Update(p);
    return;
  }
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, sGantryPieces[n]);
  SET_XFLIP(p, FALSE);
  if (n % 6 == 0) {
    s->flags |= COLLIDABLE;
    INIT_BODY(p, &sGantryCollision, 1, NULL);
  }
  (s->spr).oam.priority = (n & 1) ? 3 : 1;
  s->coord.x = gStageRun.vm.camera.viewport.x + (n > 7 ? 0xB7FF : n > 5 ? 0xBFFF : 0xA7FF);
  s->coord.y = s->unk_28->unk_coord.y + PIXEL(88);
  Gantry_Update(p);
}

// 0x080ce9cc: four sets 60 frames apart, the beam last
static void Gantry_Send(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
    case 2:
      createPiece(s, 2);
      createPiece(s, 3);
      createPiece(s, 8);
      createPiece(s, 9);
      s->work[2] = 60;
      s->mode[1]++;
      break;
    case 4:
      createPiece(s, 4);
      createPiece(s, 5);
      createPiece(s, 10);
      createPiece(s, 11);
      s->work[2] = 60;
      s->mode[1]++;
      break;
    case 6:
      createPiece(s, 6);
      createPiece(s, 7);
      createPiece(s, 0);
      createPiece(s, 1);
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      break;
    default:
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;
  }
}

// 0x080ceab4
static void Gantry_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  u8 n = s->work[1];
  if (s->work[0] == 0) {
    Gantry_Send(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[2] == 0 && n <= 5 && s->coord.x < gStageRun.vm.camera.viewport.x + 0x77FF) {
    if (n == 1) {
      PlaySound(SE_Z2_GANTRY);
    } else if (n & 1) {
      PlaySound(SE_Z2_GANTRY_SIDE);
    }
    s->mode[2]++;
  }
  s->coord.x -= PIXEL(8);
  if (s->coord.x < (pZero2->s).coord.x - PIXEL(240)) SET_SOLID_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------
/*
  Zero 2's solid 5 work0 55, front of a boss room car over its BG
  work1: which car
*/

static const struct PreloadEntity sCarSheet = {AP_SHEET_Z2_TRAIN_CAR, 0, 864, 9, 0, AP_PRELOAD_SHEET, 0};

static void CarFront_Init(struct Solid* p);
static void CarFront_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2CarFrontRoutine = {
    [ENTITY_INIT] =      (SolidFunc)CarFront_Init,
    [ENTITY_UPDATE] =    (SolidFunc)CarFront_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c88f4
static void CarFront_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  CarFront_Update(p);
}

// 0x080c892c
static void CarFront_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  s->coord = gOverworld.work.apZ2Train.cars[s->work[1]];
  if (s->mode[1] == 0) {
    ApLoadSheet(&sCarSheet);
    s->texture = TEXTURE_AP_SHEET;
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_TRAIN_CAR, s->work[1]));
    s->renderPrio = 1;
    s->mode[1]++;
  }
  UpdateSpriteAnimation(p);
}

#endif  // AP
