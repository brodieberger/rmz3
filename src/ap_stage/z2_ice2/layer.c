// Zero 2's ICE2 AKA Computer Zone 2

#include "ap_import.h"
#include "gba/gba.h"
#include "collision.h"
#include "global.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Ice2_PlttAnim83, gApZ2Ice2_PlttAnim84;
extern const AnimCmd* const gApZ2Ice2_PlttAnimScript83[], *const gApZ2Ice2_PlttAnimScript84[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

// 0x0800e9fc
static void Stage_Init(Coords32* _ UNUSED) {
  gOverworld.work.apZ2ComputerZone2.music = gStageRun.checkpoint == 0 ? 0 : 2;
  ApStartPaletteAnimation(PLTT_ANIM_ID(83), &gApZ2Ice2_PlttAnim83, gApZ2Ice2_PlttAnimScript83, 0);
}

/*
  0x0800ea0c, 0x08018bc0: x 8144 music goes, 8176 room's plays, enemies swept away until 8400
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2CircuitShrineState* w = &gOverworld.work.apZ2ComputerZone2;
  s32 zero = (pZero2->s).coord.x;

  StepPaletteAnimation(PLTT_ANIM_ID(83));
  if (w->music == 0 && zero > PIXEL(8143)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(8175)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (zero > PIXEL(8175) && zero <= PIXEL(8399)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && zero > PIXEL(8399)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x0800ea1c
static void Stage_Exit(Coords32* _ UNUSED) { RemovePaletteAnimation(PLTT_ANIM_ID(83)); }

const StageFunc gApZ2Ice2_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013dbc: one spawn area
u8 gApZ2Ice2_Area(Coords32* _ UNUSED) { return 0; }

// --------------------------------------------

// 0x0800ea28
static void Backdrop_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  PixelCoords origin = {0, 0};
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  FUN_08005a70(&l->gfx, &origin, SCREEN_ADDR(n));
  UpdateBGOFS(&l->gfx, BGOFS(n));
  l->phase++;
}

// 0x0800ea80: camera held right of x 7168 down by the water
static void Lower_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->viewportLeftTopPixel.y > 480 && l->viewportLeftTopPixel.x > 6960) {
    gStageRun.vm.camera.left = PIXEL(7168);
  } else {
    gStageRun.vm.camera.left = 0;
  }
}

// 0x0800eab8
static void Lower_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) { gStageRun.vm.camera.left = 0; }

// 0x0800eac4: water, blended, rising 256 px once state[0] is set
static void Water_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    gBlendRegBuffer.bldclt = 0x3B44;
    gBlendRegBuffer.bldalpha = 0xC04;
    gOverworld.state[0] = 0;
    l->scroll.y = -256;
    ApStartPaletteAnimation(PLTT_ANIM_ID(84), &gApZ2Ice2_PlttAnim84, gApZ2Ice2_PlttAnimScript84, 0);
    l->phase++;
  }
  if (gOverworld.state[0] != 0 && l->scroll.y != 0) l->scroll.y++;
  gOverworld.sea = PIXEL(1872) - PIXEL(l->scroll.y);
  StepPaletteAnimation(PLTT_ANIM_ID(84));
}

// 0x0800eb44
static void Water_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gOverworld.sea = 0x7FFFFFFF;
  gBlendRegBuffer.bldclt = 0;
  RemovePaletteAnimation(PLTT_ANIM_ID(84));
}

/*
  Zero 2's layer routines for this stage
  2: backdrop
  3: lower floor's camera
  4: water
*/
// clang-format off
const StageLayerRoutine gApZ2Ice2_LayerRoutines[5] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, Backdrop_Draw, NULL},
    [3] = {Lower_Update, DrawGeneralStageLayer, Lower_Exit},
    [4] = {Water_Update, DrawGeneralStageLayer, Water_Exit},
};
// clang-format on

#endif  // AP
