#include "ap.h"
#include "constants/armor.h"
#include "constants/game.h"
#include "constants/song.h"
#include "entity.h"
#include "game.h"
#include "global.h"
#include "gpu_regs.h"
#include "player/zero.h"
#include "quake.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "text_window.h"
#include "zero.h"

#if AP

/*
  Traps. Each implemented effect is just a timer that applies a visual effect each frame it is active.
*/

#define AP_QUAKE_FRAMES (10 * 60)
#define AP_QUAKE_POWER 3  // Pantheon Aqua mod's rubble fall

#define AP_MOSAIC_FRAMES (16 * 60)
#define AP_MOSAIC_SIZE 5    // matches cyber elf usage blur
#define AP_MOSAIC_RAMP 32   // frames to fade in, and to fade out

#define AP_SLIP_FRAMES (20 * 60)

EWRAM_DATA static u16 sApQuakeFrames = 0;
EWRAM_DATA static u16 sApMosaicFrames = 0;
EWRAM_DATA static u16 sApSlipFrames = 0;

extern const char_t gApTrapQuakeText[];
extern const char_t gApTrapMosaicText[];
extern const char_t gApTrapSlipText[];

void ApClearTraps(void) {
  sApQuakeFrames = 0;
  sApMosaicFrames = 0;
  sApSlipFrames = 0;
}

bool32 ApSlipperyFloor(void) {
  u8 foot = gPlayers[0].unk_b4.status.foot;

  return sApSlipFrames != 0 && foot != FOOT_CHIP_SPIKE && foot != FOOT_CHIP_ULTIMA;
}

/* Returns TRUE if apItemID is a trap. */
bool32 ApStartTrap(u16 apItemID) {
  if (apItemID == AP_ITEM_TRAP_EARTHQUAKE) {
    sApQuakeFrames = AP_QUAKE_FRAMES;
    PlaySound(SE_UNK_10d);
    PrintTextWindowPtr(gApTrapQuakeText, AP_CAPTION_FRAMES);
    return TRUE;
  }
  if (apItemID == AP_ITEM_TRAP_PIXELATE) {
    sApMosaicFrames = AP_MOSAIC_FRAMES;
    PrintTextWindowPtr(gApTrapMosaicText, AP_CAPTION_FRAMES);
    return TRUE;
  }
  if (apItemID == AP_ITEM_TRAP_SLIPPERY) {
    sApSlipFrames = AP_SLIP_FRAMES;
    PrintTextWindowPtr(gApTrapSlipText, AP_CAPTION_FRAMES);
    return TRUE;
  }
  return FALSE;
}

/*
  So that traps effects are only in game.
*/
static bool32 ApTrapsRun(void) {
  if (ApInDemo() || gPause) {
    return FALSE;
  }
  if (*(u32*)gGameState.mode != GAMEMODE(MAINGAME, OVERWORLD, 0, 0)) {
    return FALSE;
  }
  if (gStageRun.vm.active & VM_ACTIVE) {
    return FALSE;
  }
  return !((gGameState.z2->input).raw & INPUT_DISABLED);
}

/*
  The mosaic's effect strength.
*/
static u16 ApMosaicValue(u16 left) {
  u16 ramp = AP_MOSAIC_FRAMES - left;
  u16 size;

  if (left < ramp) {
    ramp = left;
  }
  if (ramp > AP_MOSAIC_RAMP) {
    ramp = AP_MOSAIC_RAMP;
  }
  size = (u16)((ramp * AP_MOSAIC_SIZE) / AP_MOSAIC_RAMP);
  return (u16)(size | (size << 4) | (size << 8) | (size << 12));
}

void ApTrapUpdate(void) {
  if (!ApTrapsRun()) {
    if (sApMosaicFrames != 0) {
      wMOSAIC = 0;
    }
    return;
  }

  if (sApQuakeFrames != 0) {
    AppendQuake(AP_QUAKE_POWER, &(gGameState.z2->s).coord);
    sApQuakeFrames--;
  }

  if (sApMosaicFrames != 0) {
    sApMosaicFrames--;
    wMOSAIC = ApMosaicValue(sApMosaicFrames);
  }

  if (sApSlipFrames != 0) {
    sApSlipFrames--;
  }
}

#endif /* AP */
