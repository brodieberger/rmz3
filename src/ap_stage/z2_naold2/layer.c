// Zero 2's NA-OLD2 AKA Neo Arcadia Temple

#include "ap_import.h"
#include "gba/gba.h"
#include "collision.h"
#include "definition.h"
#include "global.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Naold2_PlttAnim96, gApZ2Naold2_PlttAnim97, gApZ2Naold2_PlttAnim98, gApZ2Naold2_PlttAnim99,
    gApZ2Naold2_PlttAnim100;
extern const AnimCmd* const gApZ2Naold2_PlttAnimScript96[], *const gApZ2Naold2_PlttAnimScript97[],
    *const gApZ2Naold2_PlttAnimScript98[], *const gApZ2Naold2_PlttAnimScript99[], *const gApZ2Naold2_PlttAnimScript100[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

// 0x0800f580
static void Stage_Init(Coords32* _ UNUSED) {
  gOverworld.work.apZ2CircuitShrine.music = gStageRun.checkpoint == 0 ? 0 : 2;
  ApStartPaletteAnimation(PLTT_ANIM_ID(96), &gApZ2Naold2_PlttAnim96, gApZ2Naold2_PlttAnimScript96, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(97), &gApZ2Naold2_PlttAnim97, gApZ2Naold2_PlttAnimScript97, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(98), &gApZ2Naold2_PlttAnim98, gApZ2Naold2_PlttAnimScript98, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(99), &gApZ2Naold2_PlttAnim99, gApZ2Naold2_PlttAnimScript99, 0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(100), &gApZ2Naold2_PlttAnim100, gApZ2Naold2_PlttAnimScript100, 0);
}

/*
  0x0800f5b0, 0x08019674: x 4544 music goes, 4576 room's plays, enemies swept away
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2CircuitShrineState* w = &gOverworld.work.apZ2CircuitShrine;
  s32 zero = (pZero2->s).coord.x;

  if (w->music == 0 && zero > PIXEL(4543)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(4575)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (zero > PIXEL(4575) && zero <= PIXEL(4799)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && zero > PIXEL(4799)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
  StepPaletteAnimation(PLTT_ANIM_ID(96));
  StepPaletteAnimation(PLTT_ANIM_ID(97));
  StepPaletteAnimation(PLTT_ANIM_ID(98));
  StepPaletteAnimation(PLTT_ANIM_ID(99));
  StepPaletteAnimation(PLTT_ANIM_ID(100));
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x0800f5d8
static void Stage_Exit(Coords32* _ UNUSED) {
  RemovePaletteAnimation(PLTT_ANIM_ID(96));
  RemovePaletteAnimation(PLTT_ANIM_ID(97));
  RemovePaletteAnimation(PLTT_ANIM_ID(98));
  RemovePaletteAnimation(PLTT_ANIM_ID(99));
  RemovePaletteAnimation(PLTT_ANIM_ID(100));
}

const StageFunc gApZ2Naold2_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013eb4: one spawn area
u8 gApZ2Naold2_Area(Coords32* _ UNUSED) { return 0; }

// 0x0800f5fc: backdrop scrolls with terrain
static void Backdrop_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    l->scrollPower.x = l->scrollPower.y = 0x100;
    l->phase++;
  }
}

/*
  Zero 2's layer routines for this stage
  2: backdrop, 1:1
*/
// clang-format off
const StageLayerRoutine gApZ2Naold2_LayerRoutines[3] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Backdrop_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

#endif  // AP
