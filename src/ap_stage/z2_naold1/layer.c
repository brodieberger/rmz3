// Zero 2's NA-OLD1 AKA Residential Area

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "collision.h"
#include "definition.h"
#include "global.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "sound.h"
#include "solid.h"
#include "stagerun.h"
#include "zero.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Naold1_PlttAnim35, gApZ2Naold1_PlttAnim36, gApZ2Naold1_PlttAnim37, gApZ2Naold1_PlttAnim38, gApZ2Naold1_PlttAnim39, gApZ2Naold1_PlttAnim40, gApZ2Naold1_PlttAnim41;
extern const AnimCmd* const gApZ2Naold1_PlttAnimScript35[], *const gApZ2Naold1_PlttAnimScript36[], *const gApZ2Naold1_PlttAnimScript37[], *const gApZ2Naold1_PlttAnimScript38[], *const gApZ2Naold1_PlttAnimScript39[], *const gApZ2Naold1_PlttAnimScript40[], *const gApZ2Naold1_PlttAnimScript41[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))

/*
  0x0831e9f0: by screen, bit for each palette animation 35..41
*/
static const u8 sPaletteAnimsByScreen[64 + 1] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 60, 60, 60, 60, 60, 60, 68,
};

static void animate(u8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

static void updatePalettes(s32 left) {
  u16 screen = (left >> 12) / 15;
  u8 here;
  here = sPaletteAnimsByScreen[screen] | sPaletteAnimsByScreen[screen + 1];
  animate(here & 1, PLTT_ANIM_ID(35), &gApZ2Naold1_PlttAnim35, gApZ2Naold1_PlttAnimScript35);
  animate(here & 2, PLTT_ANIM_ID(36), &gApZ2Naold1_PlttAnim36, gApZ2Naold1_PlttAnimScript36);
  animate(here & 4, PLTT_ANIM_ID(37), &gApZ2Naold1_PlttAnim37, gApZ2Naold1_PlttAnimScript37);
  animate(here & 8, PLTT_ANIM_ID(38), &gApZ2Naold1_PlttAnim38, gApZ2Naold1_PlttAnimScript38);
  animate(here & 16, PLTT_ANIM_ID(39), &gApZ2Naold1_PlttAnim39, gApZ2Naold1_PlttAnimScript39);
  animate(here & 32, PLTT_ANIM_ID(40), &gApZ2Naold1_PlttAnim40, gApZ2Naold1_PlttAnimScript40);
  animate(here & 64, PLTT_ANIM_ID(41), &gApZ2Naold1_PlttAnim41, gApZ2Naold1_PlttAnimScript41);
}

// 0x0800f618
static void Stage_Init(Coords32* _ UNUSED) {
  gOverworld.work.apZ2RuinedShrine.music = gStageRun.checkpoint == 0 ? 0 : 2;
}

/*
  0x0800f638, 0x080198ec: x 5504 music goes, 5536 corridor's plays, enemies swept away
*/
static void Stage_Update(Coords32* leftTop) {
  struct ApZ2CircuitShrineState* w = &gOverworld.work.apZ2RuinedShrine;
  s32 zero = (pZero2->s).coord.x;

  if (w->music == 0 && zero > PIXEL(5503)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && zero > PIXEL(5535)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (zero > PIXEL(5535) && zero <= PIXEL(5759)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && zero > PIXEL(5759)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
  if (gStageRun.stageEventPhase == 3 && zero > PIXEL(6959)) gStageRun.missionStatus |= MISSION_SUCCESS;
  updatePalettes(leftTop->x);
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x0800f6f0
static void Stage_Exit(Coords32* _ UNUSED) {
  RemovePaletteAnimation(PLTT_ANIM_ID(35));
  RemovePaletteAnimation(PLTT_ANIM_ID(36));
  RemovePaletteAnimation(PLTT_ANIM_ID(37));
  RemovePaletteAnimation(PLTT_ANIM_ID(38));
  RemovePaletteAnimation(PLTT_ANIM_ID(39));
  RemovePaletteAnimation(PLTT_ANIM_ID(40));
  RemovePaletteAnimation(PLTT_ANIM_ID(41));
}

const StageFunc gApZ2Naold1_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

// 0x08013eb4: one spawn area
u8 gApZ2Naold1_Area(Coords32* _ UNUSED) { return 0; }

// 0x0800f710: backdrop holds still
static void Backdrop_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    l->scrollPower.x = 0;
    l->phase++;
  }
}

/*
  Zero 2's layer routines for this stage
  2: backdrop, held still
*/
// clang-format off
const StageLayerRoutine gApZ2Naold1_LayerRoutines[3] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {Backdrop_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

/*
  Zero 2's solid 5 work0 0x26. work1: which soldier
*/
static void Fallen_Init(struct Solid* p);
static void Fallen_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2FallenRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Fallen_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Fallen_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c6700
static void Fallen_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FALLEN, s->work[1]));
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Fallen_Update(p);
}

static void Fallen_Update(struct Solid* p) { UpdateSpriteAnimation(p); }

/*
  Zero 2's solid 5 work0 0x2B.
  work1:
    0: Harpuia
    1: Fefnir
    2: Leviathan
*/
static void Cast_Init(struct Solid* p);
static void Cast_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2CastRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Cast_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Cast_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static const struct PreloadEntity sCastSheets[3] = {
    {AP_SHEET_Z2_CAST_HARPUIA, 0, 528, 6, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_CAST_FEFNIR, 0, 656, 7, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_CAST_LEVIATHAN, 0, 944, 8, 0, AP_PRELOAD_SHEET, 0},
};
static const motion_t sCastStand[3] = {MOTION(AP_SHEET_Z2_CAST_HARPUIA, 0), MOTION(AP_SHEET_Z2_CAST_FEFNIR, 0), MOTION(AP_SHEET_Z2_CAST_LEVIATHAN, 0)};
static const motion_t sCastFirst[3] = {MOTION(AP_SHEET_Z2_CAST_HARPUIA, 1), MOTION(AP_SHEET_Z2_CAST_FEFNIR, 1), MOTION(AP_SHEET_Z2_CAST_LEVIATHAN, 1)};
static const motion_t sCastSecond[3] = {MOTION(AP_SHEET_Z2_CAST_HARPUIA, 2), MOTION(AP_SHEET_Z2_CAST_FEFNIR, 2), MOTION(AP_SHEET_Z2_CAST_LEVIATHAN, 1)};

// 0x080c714c
static void Cast_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  ApLoadSheet(&sCastSheets[s->work[1]]);
  SetSpriteAnimation(p, sCastStand[s->work[1]]);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = 1;
  Cast_Update(p);
}

// 0x080c7190
static void Cast_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  u8 n = s->work[1];
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 1:
      if (!(s->scriptEntity->flags & 1)) break;
      s->scriptEntity->flags &= ~1;
      SetSpriteAnimation(p, sCastFirst[n]);
      s->mode[1]++;
      break;
    case 2:
      if (n == 2 && (s->motion).state == ANIM_END) SetSpriteAnimation(p, sCastStand[n]);
      if (!(s->scriptEntity->flags & 2)) break;
      s->scriptEntity->flags &= ~2;
      SetSpriteAnimation(p, sCastSecond[n]);
      s->mode[1]++;
      break;
    case 3:
      if ((s->motion).state != ANIM_END) break;
      SetSpriteAnimation(p, sCastStand[n]);
      s->mode[1] = 1;
      break;
  }
}

#endif  // AP
