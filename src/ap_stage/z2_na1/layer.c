// Zero 2's NA-1 AKA Temple of Flame

#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "definition.h"
#include "gfx.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"

#if AP

extern const PlttAnimData gApZ2Na1_PlttAnim126, gApZ2Na1_PlttAnim127, gApZ2Na1_PlttAnim128;
extern const AnimCmd* const gApZ2Na1_PlttAnimScript126[], *const gApZ2Na1_PlttAnimScript127[],
    *const gApZ2Na1_PlttAnimScript128[];
extern const ColorGraphic gApZ2Na1_TileAnim[5];
extern const u16 gApZ2Na1_LavaMap[], gApZ2Na1_TankMap[];
extern const GameCommand gApZ2Na1_LavaScript[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

// 0x0800f728
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2LavaShrineState* w = &gOverworld.work.apZ2LavaShrine;
  w->frame = 0;
  w->lavaScript = FALSE;
  w->rise = 0;
  w->tank = FALSE;
  w->fefnir = NULL;
  w->tankX = PIXEL(360);
  w->tankY = PIXEL(192);
  ApStartPaletteAnimation(PLTT_ANIM_ID(126), &gApZ2Na1_PlttAnim126, gApZ2Na1_PlttAnimScript126, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(127), &gApZ2Na1_PlttAnim127, gApZ2Na1_PlttAnimScript127, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(128), &gApZ2Na1_PlttAnim128, gApZ2Na1_PlttAnimScript128, 0);
}

/*
  0x0800f790, 0x08019d3c: past x 3376 lava starts rising, 960 frames to top
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2LavaShrineState* w = &gOverworld.work.apZ2LavaShrine;

  if (!w->lavaScript && gStageRun.checkpoint == 0 && (pZero2->s).coord.x > PIXEL(3375) &&
      !(gStageRun.vm.active & VM_ACTIVE)) {
    SetScript(&gStageRun.vm, gApZ2Na1_LavaScript);
    w->lavaScript = TRUE;
  }
  if (++w->frame == 45) w->frame = 0;
  if (gOverworld.state[0] != 0 && w->rise < 960) w->rise++;
  StepPaletteAnimation(PLTT_ANIM_ID(126));
  StepPaletteAnimation(PLTT_ANIM_ID(127));
  StepPaletteAnimation(PLTT_ANIM_ID(128));
}

// 0x0800f7f0: lava tiles flow, a frame every 9
static void Stage_Draw(Coords32* _ UNUSED) {
  RequestGraphicTransfer(&gApZ2Na1_TileAnim[gOverworld.work.apZ2LavaShrine.frame / 9].g, BG_CHAR_OFFSET(1));
}

// 0x0800f854
static void Stage_Exit(Coords32* _ UNUSED) {
  RemovePaletteAnimation(PLTT_ANIM_ID(126));
  RemovePaletteAnimation(PLTT_ANIM_ID(127));
  RemovePaletteAnimation(PLTT_ANIM_ID(128));
}

const StageFunc gApZ2Na1_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013ebc: spawn areas
  0: lava pools
  1: climb down and up to lava shaft
  2: boss
*/
u8 gApZ2Na1_Area(Coords32* c) {
  if (c->y > PIXEL(1440) || (c->x > PIXEL(3840) && c->y > PIXEL(800))) return 2;
  if (c->x > PIXEL(2880) || c->y > PIXEL(928)) return 1;
  return 0;
}

// --------------------------------------------
/*
  Zero 2's solid 18 work0 2, slab over lava shaft
*/

static void Slab_Init(struct Solid* p);
static void Slab_Update(struct Solid* p);
static void Slab_Fall(struct Solid* p);
static void Slab_Disappear(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2SlabRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Slab_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Slab_Update,
    [ENTITY_DIE] =       (SolidFunc)Slab_Fall,
    [ENTITY_DISAPPEAR] = (SolidFunc)Slab_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08349808
static const struct Rect sSlabSize = {0, PIXEL(8), PIXEL(32), PIXEL(16)};

// 0x08349810, 0x08349830: shake offsets in pixels
static const s32 sShakeX[8] = {-1, 0, 1, 0, -1, 0, 1, 0};
static const s32 sShakeY[8] = {-1, 1, 0, -1, 1, -1, 0, 1};

// 0x080cda8c
static void Slab_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->d.x = s->d.y = 0;
  s->coord.x += PIXEL(8);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SLAB, 0));
  UpdateSpriteAnimation(p);
  s->coord.y = (s->coord.y & ~(PIXEL(16) - 1)) - 1;
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sSlabSize;
  s->physicsAttr = MTATTR_CONVEYOR1 | SHAPE_BLOCK;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Slab_Update(p);
}

static bool32 zeroTouches(struct Entity* s) {
  const Coords32* zero = &(pZero2->s).coord;
  s32 dx = zero->x - PIXEL(1) - s->coord.x;
  s32 dy = zero->y - PIXEL(14) - (s->coord.y + PIXEL(8));
  return dx > -PIXEL(25) && dx < PIXEL(25) && dy > -PIXEL(24) && dy < PIXEL(24);
}

// 0x080cdb44
static void Slab_Update(struct Solid* p) {
  if (!zeroTouches(&p->s)) return;
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  Slab_Fall(p);
}

// 0x080cdbb0
static void Slab_Fall(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  switch (s->mode[1]) {
    case 0:
      (s->spr).c = (struct Coord*)&s->unk_coord;
      PlaySound(SE_Z2_DESERT_TAIL_SLAM);
      s->work[2] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      s->unk_coord.x = s->coord.x + PIXEL(sShakeX[s->work[2] & 7]);
      s->unk_coord.y = s->coord.y + PIXEL(sShakeY[s->work[2] & 7]);
      s->work[2]++;
      if ((s->work[2] & 3) == 0) {
        at.x = s->coord.x + ((s->work[2] & 4) ? PIXEL(17) : -PIXEL(17));
        at.y = s->coord.y + PIXEL(s->work[2]);
        if (GetMetatileAttr(at.x, at.y)) CreateSmoke(3, &at);
      }
      if (s->work[2] <= 44) break;
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
static void Slab_Disappear(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's solid 28, pillar under column
*/

static void Gate_Closed(struct Solid* p);
static void Gate_Open(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2GateRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Gate_Closed,
    [ENTITY_UPDATE] =    (SolidFunc)Gate_Open,
    [ENTITY_DIE] =       (SolidFunc)Slab_Disappear,
    [ENTITY_DISAPPEAR] = (SolidFunc)Slab_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08349b50
static const struct Rect sGateSize = {0, -PIXEL(32), PIXEL(32), PIXEL(96)};

#define GATE(n) MOTION(AP_SHEET_Z2_GATE, (n))

static bool32 zeroAtGate(struct Entity* s) {
  const Coords32* zero = &(pZero2->s).coord;
  s32 dx = zero->x - PIXEL(1) - s->coord.x;
  s32 dy = zero->y - PIXEL(14) - (s->coord.y - PIXEL(32));
  return dx > -PIXEL(26) && dx < PIXEL(26) && dy > -PIXEL(48) && dy < PIXEL(48) &&
         s->coord.y >= zero->y && s->coord.y - zero->y <= PIXEL(24) && zero->x < s->coord.x;
}

// 0x080d1804, 0x080d1910
static void Gate_Closed(struct Solid* p) {
  struct Entity* s = &p->s;
  if (s->mode[0] == ENTITY_INIT) {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    (s->spr).oam.priority = 3;
    s->coord.x += PIXEL(8);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  }
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, GATE(0));
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sGateSize;
  s->physicsAttr = SHAPE_BLOCK;
  s->mode[1] = 0;
}

// 0x080d19a4
static void Gate_Open(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (!zeroAtGate(s)) break;
      SetSpriteAnimation(p, GATE(1));
      PlaySound(SE_Z2_GATE_SINK);
      s->mode[1]++;
      break;
    case 1:
      if (!IsSpriteAnimEnd(p)) break;
      s->flags2 &= ~ENTI_PHYSICS;
      s->mode[1]++;
      break;
    case 2:
      s->flags &= ~DISPLAY;
      if (s->coord.x + PIXEL(32) > (pZero2->s).coord.x) break;
      SetSpriteAnimation(p, GATE(2));
      s->flags |= DISPLAY;
      s->flags2 |= ENTI_PHYSICS;
      PlaySound(SE_Z2_GATE_RISE);
      s->mode[1]++;
      break;
    case 3:
      if (IsSpriteAnimEnd(p)) Gate_Closed(p);
      break;
  }
}

// --------------------------------------------

#define TANK_SHOWN unk_10

/*
  0x0800f874: Fefnir's tank's hull, BG2 under his sprites, hidden off screen
*/
static void Tank_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2LavaShrineState* w = &gOverworld.work.apZ2LavaShrine;
  u16 n = (u16)l->bgIdx >> 4;
  s32 x, y;

  if (l->TANK_SHOWN != w->tank) l->phase = 0;
  if (l->phase == 0) {
    BGCNT16(n) = (u16)(l->prio | l->screenBase | BGCNT_TXT512x256 | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    if (w->tank) {
      gVideoRegBuffer.dispcnt |= DISPCNT_BG0_ON << n;
      CpuFastSet(gApZ2Na1_TankMap, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
      CpuFastFill(0, (u8*)SCREEN_ADDR(n) + BG_SCREEN_SIZE, BG_SCREEN_SIZE);
    } else {
      gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
    }
    l->TANK_SHOWN = w->tank;
    l->phase++;
  }
  if (!w->tank) return;
  x = l->viewportLeftTopPixel.x - (w->tankX >> 8) + 48;
  y = l->viewportLeftTopPixel.y - (w->tankY >> 8) + 96;
  if ((u32)(x + 303) <= 382 && y <= 111 && y > -140) {
    BGnHOFS(n) = x;
    BGnVOFS(n) = y;
  } else {
    BGnVOFS(n) = 112;
  }
  // flashes white with Fefnir: BG palette 9
  if (w->fefnir != NULL && FLAG32(gWhitePaintFlags, w->fefnir->invincibleID)) {
    gPaletteManager.unk_404 = 9 * 32;
    gPaletteManager.unk_406 = 32;
  }
}

// 0x080ef6c8
static const struct Rect sLavaSize = {0, 15360, -4608, 30720};

/*
  0x0800fa38: lava rising up shaft once gOverworld.state[0] set
*/
static void Lava_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  s32 rise, y;
  Coords32 at;

  if (gOverworld.state[0] == 0) {
    gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
    return;
  }
  if (l->phase == 0) {
    BGCNT16(n) = (u16)(l->screenBase | BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    CpuFastSet(gApZ2Na1_LavaMap, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
    CpuFastFill(0, (u8*)SCREEN_ADDR(n) + BG_SCREEN_SIZE, BG_SCREEN_SIZE);
    gVideoRegBuffer.dispcnt |= DISPCNT_BG0_ON << n;
    l->phase++;
  }
  rise = gOverworld.work.apZ2LavaShrine.rise >> 1;
  y = l->viewportLeftTopPixel.y + rise - 1200;
  if (y < -180) y = -180;
  if (y > 48) y = 48;
  at.x = PIXEL(3480);
  at.y = PIXEL(1200) - PIXEL(rise);
  AppendHazard(0xE001, MTATTR_SPIKE | SHAPE_BLOCK, &at, &sLavaSize);
  BGnHOFS(n) = l->viewportLeftTopPixel.x % 240;
  BGnVOFS(n) = y;
}

/*
  Zero 2's layer routines for this stage
  2: Fefnir's tank's hull
  3: rising lava
*/
// clang-format off
const StageLayerRoutine gApZ2Na1_LayerRoutines[4] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, Tank_Draw, NULL},
    [3] = {Lava_Update, NULL, NULL},
};
// clang-format on

#endif  // AP
