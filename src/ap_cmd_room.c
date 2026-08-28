#include "ap.h"

#undef ApCmdRoomTalk

#include "constants/flag.h"
#include "constants/game.h"
#include "constants/song.h"
#include "constants/stage_id.h"
#include "definition.h"
#include "game.h"
#include "global.h"
#include "score.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "story.h"
#include "text_window.h"
#include "zero.h"

#if AP

/* From state 15 on, g->frames holds the index, which is actually stageID - 1. */
#define ApStageOfIndex(i) ((u8)((i) + STAGE_SPACE_CRAFT))
#define ApStageCleared(i) (gMissionDones & (1 << ApStageOfIndex(i)))

enum ApStageIntroKind {
  AP_INTRO_NONE,
  AP_INTRO_SUB_ARCADIA,
  AP_INTRO_MISSILE_FACTORY
};

static u8 ApStageIntro(s16 index) {
  if (ApStageCleared(index)) {
    return AP_INTRO_NONE;
  }
  switch (ApStageOfIndex(index)) {
    case STAGE_SUB_ARCADIA:
      return AP_INTRO_SUB_ARCADIA;
    case STAGE_MISSILE_FACTORY:
      return AP_INTRO_MISSILE_FACTORY;
  }
  return AP_INTRO_NONE;
}

/*
  Cmd room conversation.
*/
void ApCmdRoomTalk(struct GameState* g) {
  TextWindowText* w = &gTextWindow.text;
  s16 ans;
  u8 intro;

  switch (g->mode[3]) {
    default: {
      CmdRoomTalk_OtherStates(g);
      return;
    }

    case 0: {
      PrintOptionMessage1(0);  // who do you want to talk to?
      g->unk_008[1] = 0;
      g->mode[3] = 1;
      return;
    }

    /*
      Skip straight the mission select screen.
    */
    case 5:
    case 19: {
      g->mode[3] = 6;
      FALLTHROUGH;
    }

    case 6:
    case 7:
    case 8: {  // 8 is the screen's own way back out, see AP_SELECT_EXIT_STATE
      ApStageSelect(g);
      return;
    }

    case 15: {
      if (ApStageCleared(g->frames)) {
        PrintOptionMessagePtr(gApStageRevisitTexts[g->frames]);  // EXPLORE / RETRY MISSION
      } else {
        PrintOptionMessagePtr(gApStageStartTexts[g->frames]);  // START MISSION / CANCEL
      }
      g->mode[3]++;
      FALLTHROUGH;
    }

    case 16: {
      if ((w->mode != 0) && (w->mode != TEXT_MODE_OPTION)) {
        return;
      }
      if ((ans = handleWrapTwoChoice(g)) == 0) {
        return;
      }
      if (ans == -2) {  // B
        g->mode[3] = 7;
        return;
      }
      if (ans < 0) {  // RETRY MISSION on a cleared stage, CANCEL otherwise
        if (!ApStageCleared(g->frames)) {
          PlaySound(SE_NO);
          g->mode[3] = 7;
          return;
        }
        ApRequestMissionRerun(ApStageOfIndex(g->frames));
      }

      intro = ApStageIntro(g->frames);
      if (intro == AP_INTRO_NONE) {
        SetScript(&gStageRun.vm, gStageScriptList[STAGE_BASE][8]);
      } else if (intro == AP_INTRO_SUB_ARCADIA) {
        (g->save).stageID = ApStageOfIndex(g->frames);
        gStageRun.missionStatus |= MISSION_B1;
        setStageCheckpoint(AP_BASE_CHECKPOINT_SUBARCADIA);
        SetScript(&gStageRun.vm, gStageScriptList[STAGE_BASE][19]);  // CS_RBASE_45
      }
      w->flag |= TEXT_FLAG_TERMINATE;
      g->mode[3]++;
      return;
    }

    case 17: {
      if (gStageRun.vm.active & VM_ACTIVE) {  // wait for the transfer cutscene
        return;
      }

      intro = ApStageIntro(g->frames);

      /* Temp needed */
      if (intro != AP_INTRO_NONE) {
        if (gTimeElfTimer != 0) {
          CLEAR_FLAG(gCurStory.s.gameflags, TIME_ELF_ENABLED);
          TurnUpBGM();
          gTimeElfTimer = 0;
        }
        StopSound(SE_TIME_ELF);
        StopSound(SE_TIME_ELF_HURRY);
      }

      (g->save).stageID = ApStageOfIndex(g->frames);
      StoreStoryData(&(g->save).story);
      StoreZeroStatus(g->z2, &(g->save).status);

      if (intro == AP_INTRO_MISSILE_FACTORY) {
        LoadStageRun(STAGE_BASE, AP_BASE_ENTRY_MISSILE_SCENE);
        SetGameMode(g, GAMEMODE(MAINGAME, PRE_OVERWORLD, 0, 0));
        return;
      }

      ResetMissionScore((u8)(g->save).stageID, &(g->save).playinfo);
      InitStageRun((u8)(g->save).stageID);
      SetGameMode(g, GAMEMODE(MAINGAME, PRE_OVERWORLD, 0, 0));
      return;
    }
  }
}

void (*const gApCmdRoomTalkFn)(struct GameState* g) = ApCmdRoomTalk;

#endif /* AP */
