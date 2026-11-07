// Zero 2's NA-2 AKA Temple of Ice

#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "gfx.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Na2_PlttAnim126, gApZ2Na2_PlttAnim127, gApZ2Na2_PlttAnim128;
extern const AnimCmd* const gApZ2Na2_PlttAnimScript126[], *const gApZ2Na2_PlttAnimScript127[],
    *const gApZ2Na2_PlttAnimScript128[];
extern const u16 gApZ2Na2_WaterMap[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

#define POOL_SEA PIXEL(1248)

// 0x0800fc1c
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2IceShrineState* w = &gOverworld.work.apZ2IceShrine;
  w->rise = 0;
  w->music = gStageRun.checkpoint == 0 ? 0 : 2;
  gOverworld.state[0] = 0;
  gOverworld.sea = POOL_SEA;
  gBlendRegBuffer.bldclt = 0x3748;
  gBlendRegBuffer.bldalpha = 0xC04;
  ApStartPaletteAnimation(PLTT_ANIM_ID(126), &gApZ2Na2_PlttAnim126, gApZ2Na2_PlttAnimScript126, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(127), &gApZ2Na2_PlttAnim127, gApZ2Na2_PlttAnimScript127, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(128), &gApZ2Na2_PlttAnim128, gApZ2Na2_PlttAnimScript128, 0);
}

/*
  0x0800fc90, 0x0801a090: x 3375 starts flood, x 5264 music goes, 5296 room's plays, enemies swept away
*/
static void Stage_Update(Coords32* leftTop) {
  struct ApZ2IceShrineState* w = &gOverworld.work.apZ2IceShrine;
  s32 zero = (pZero2->s).coord.x;

  if (zero > PIXEL(3375) && !(gStageRun.vm.active & VM_ACTIVE)) gOverworld.state[0] = 1;
  if (leftTop->x > PIXEL(3376)) {
    gOverworld.state[0] = 1;
    if (w->rise < 2016) w->rise = 2016;
  }
  if (gOverworld.state[0] != 0 && w->rise < 2112) w->rise++;
  gOverworld.sea = leftTop->x < PIXEL(2880) ? POOL_SEA : PIXEL(1344) - PIXEL(w->rise >> 1);

  if (w->music == 0 && zero > PIXEL(5263)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(5295)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    gStageRun.vm.camera.bottom = PIXEL(592);
    w->music = 2;
  }
  if (zero > PIXEL(5295) && zero <= PIXEL(5519)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && zero > PIXEL(5519)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
  StepPaletteAnimation(PLTT_ANIM_ID(126));
  StepPaletteAnimation(PLTT_ANIM_ID(127));
  StepPaletteAnimation(PLTT_ANIM_ID(128));
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x0800fd3c
static void Stage_Exit(Coords32* _ UNUSED) {
  gOverworld.sea = 0x7FFFFFFF;
  gBlendRegBuffer.bldclt = 0;
  RemovePaletteAnimation(PLTT_ANIM_ID(126));
  RemovePaletteAnimation(PLTT_ANIM_ID(127));
  RemovePaletteAnimation(PLTT_ANIM_ID(128));
}

const StageFunc gApZ2Na2_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013efc: spawn areas
  1: x 2112..2991, tower
  0: rest
*/
u8 gApZ2Na2_Area(Coords32* c) { return c->x > PIXEL(2112) && c->x < PIXEL(2992); }

// --------------------------------------------
/*
  Zero 2's solid 16, ice floe.
  work0 1: rides sea, gone off camera
  work1 1: rides where placed
*/

static void Floe_Init(struct Solid* p);
static void Floe_Update(struct Solid* p);
static void Floe_Die(struct Solid* p UNUSED);

// clang-format off
const SolidRoutine gApZ2FloeRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Floe_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Floe_Update,
    [ENTITY_DIE] =       (SolidFunc)Floe_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08349594
static const struct Collision sFloeCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 255,
  hitzone : 0x00,
  remaining : 0,
  layer : 0x00000001,
  range : {0, -PIXEL(16), PIXEL(96), PIXEL(1)},
};

// 0x083495c4
static const struct Rect sFloeSize = {0, 0, PIXEL(96), PIXEL(32)};

struct Floe {
  OBJECT_HDR;
  s32 home;
  s32 tilt;
  u8 _[8];
};
static_assert(sizeof(struct Floe) == sizeof(struct Solid));

// 0x080cd5b4
static void Floe_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Floe* f = (struct Floe*)p;
  s->flags |= DISPLAY | FLIPABLE;
  InitRotatableMotion(s);
  (s->spr).c = (struct Coord*)&s->unk_coord;
  s->flags |= COLLIDABLE;
  INIT_BODY(p, &sFloeCollision, 0, NULL);
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sFloeSize;
  s->physicsAttr = 0x3C01;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FLOE, 0));
  if (s->work[1] == 0) {
    s->coord.y = gOverworld.sea - PIXEL(8);
  } else {
    s->coord.y -= PIXEL(8) + 1;
    f->home = s->coord.y;
  }
  s->unk_coord = s->coord;
  f->tilt = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Floe_Update(p);
}

// 0x080cd678
static void Floe_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Floe* f = (struct Floe*)p;
  bool32 onIt = ((p->body).status & BODY_STATUS_B2) != 0;
  s32 dx = onIt ? (pZero2->s).coord.x - s->coord.x : 0;
  s32 target, tilt;
  const struct Camera* c;

  UpdateSpriteAnimation(p);
  if (s->work[1] == 0) {
    target = gOverworld.sea - (onIt ? 0 : PIXEL(8));
  } else {
    target = f->home + (onIt ? PIXEL(8) : 0);
  }
  s->coord.y = (s->coord.y * 7 + target) / 8;

  tilt = f->tilt * 7 + dx;
  f->tilt = tilt / 8;
  s->angle = tilt >> 14;
  s->unk_coord.y = s->coord.y - ((SIN((f->tilt >> 11) & 0xFF) * f->tilt) / 256 + PIXEL(16));

  if (s->work[0] != 0) {
    c = &gStageRun.vm.camera;
    if (c->viewport.x - PIXEL(240) > s->coord.x || c->viewport.x + PIXEL(240) <= s->coord.x) {
      s->flags &= ~(DISPLAY | FLIPABLE | COLLIDABLE);
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

static void Floe_Die(struct Solid* p UNUSED) {}

// --------------------------------------------

// 0x0800ffe0: backdrop scrolls with terrain
static void Backdrop_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    l->scrollPower.x = l->scrollPower.y = 0x100;
    l->scroll.x = l->scroll.y = 0;
    l->phase++;
  }
}

/*
  0x0800fee4: flood in shaft and past it, BG3 in front, blended
*/
static void Water_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  s32 y;

  if (gOverworld.state[0] == 0) {
    gVideoRegBuffer.dispcnt &= ~(DISPCNT_BG0_ON << n);
    return;
  }
  if (l->phase == 0) {
    BGCNT16(n) = (u16)(l->screenBase | BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    CpuFastSet(gApZ2Na2_WaterMap, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
    CpuFastFill(0, (u8*)SCREEN_ADDR(n) + BG_SCREEN_SIZE, BG_SCREEN_SIZE);
    gVideoRegBuffer.dispcnt |= DISPCNT_BG0_ON << n;
    l->phase++;
  }
  y = l->viewportLeftTopPixel.y + (gOverworld.work.apZ2IceShrine.rise >> 1) - 1336;
  if (y < -180) y = -180;
  if (y > 48) y = 48;
  BGnHOFS(n) = l->viewportLeftTopPixel.x;
  BGnVOFS(n) = y;
}

/*
  Zero 2's layer routines for this stage
  3: flood
  4: backdrop, 1:1
*/
// clang-format off
const StageLayerRoutine gApZ2Na2_LayerRoutines[5] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, NULL, NULL},
    [3] = {NULL, Water_Draw, NULL},
    [4] = {Backdrop_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

#endif  // AP
