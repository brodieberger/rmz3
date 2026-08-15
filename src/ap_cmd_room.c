#include "ap.h"

#undef ApCmdRoomTalk

#include "constants/game.h"
#include "constants/song.h"
#include "constants/stage_id.h"
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

/*
  Cmd room conversation.
*/
void ApCmdRoomTalk(struct GameState* g) {
  TextWindowText* w = &gTextWindow.text;
  s16 ans;

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
      SetScript(&gStageRun.vm, gStageScriptList[STAGE_BASE][8]);  // Script_FreeRunTransport
      w->flag |= TEXT_FLAG_TERMINATE;
      g->mode[3]++;
      return;
    }

    case 17: {
      if (gStageRun.vm.active & VM_ACTIVE) {  // wait for the transfer cutscene
        return;
      }
      (g->save).stageID = ApStageOfIndex(g->frames);
      StoreStoryData(&(g->save).story);
      StoreZeroStatus(g->z2, &(g->save).status);
      ResetMissionScore((u8)(g->save).stageID, &(g->save).playinfo);
      InitStageRun((u8)(g->save).stageID);
      SetGameMode(g, GAMEMODE(MAINGAME, PRE_OVERWORLD, 0, 0));
      return;
    }
  }
}

void (*const gApCmdRoomTalkFn)(struct GameState* g) = ApCmdRoomTalk;

#endif /* AP */
