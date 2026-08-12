#include "ap.h"

#undef ApCmdRoomTalk

#include "constants/game.h"
#include "constants/song.h"
#include "constants/stage_id.h"
#include "game.h"
#include "global.h"
#include "input.h"
#include "score.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "story.h"
#include "text.h"
#include "zero.h"

#if AP

extern const char_t Unicode_CursorUp[];
extern const char_t Unicode_CursorDown[];

#define FREE_RUN_VISIBLE_ROWS 2
#define FREE_RUN_OPEN_DELAY 15

/*
  Cmd room Transfer back option
  Pick a cleared area, then ask user to retry or revisit.
  Lets player re attempt a stage for a chance at an A+ rank after completing it initially.
*/
void ApCmdRoomTalk(struct GameState* g) {
  TextWindowText* w = &gTextWindow.text;
  s16 ans;

  switch (g->mode[3]) {
    default: {
      CmdRoomTalk_OtherStates(g);
      return;
    }

    case 13: {
      PrintOptionMessage1(0x32);  // Where to transfer?
      g->frames = 0;
      g->unk_006 = 0;
      g->unk_008[0] = 0;
      g->unk_008[1] = FREE_RUN_OPEN_DELAY;
      g->mode[3]++;
      FALLTHROUGH;
    }

    case 14: {
      s16 available[FREE_STAGE_COUNT];
      s16 count = 0;
      s16 i;
      s32 noLeftMugshot;

      if ((w->mode != 0) && (w->mode != TEXT_MODE_OPTION)) {
        return;
      }

      for (i = 0; i < FREE_STAGE_COUNT; i++) {
        if (gMissionDones & (1 << gFreeRunStageIDs[i])) {
          available[count] = i;
          count++;
        }
      }

      if ((g->frames < count - 1) && (gJoypad[0].field3_0x6 & DPAD_DOWN)) {
        PlaySound(SE_CURSOR);
        g->frames++;
      }
      if ((g->frames > 0) && (gJoypad[0].field3_0x6 & DPAD_UP)) {
        PlaySound(SE_CURSOR);
        g->frames--;
      }

      if (g->frames < g->unk_006) g->unk_006 = g->frames;
      if (g->frames > g->unk_006 + (FREE_RUN_VISIBLE_ROWS - 1)) g->unk_006 = g->frames - (FREE_RUN_VISIBLE_ROWS - 1);

      noLeftMugshot = (w->mugshotRight || (w->mugshot == NO_MUGSHOT)) ? 1 : 0;

      for (i = 0; i < count; i++) {
        u8 row = (u8)((i - g->unk_006) * 2);
        if (row <= (FREE_RUN_VISIBLE_ROWS - 1) * 2) {
          PrintString(STRING(gFreeRunStageNameIdxs[available[i]]), 10 - (noLeftMugshot * 7), (s8)row + 2 + w->y8);
        }
      }
      PrintString(STRING(0), 8 - (noLeftMugshot * 7), ((g->frames - g->unk_006) * 2) + 2 + w->y8);  // ▷

      g->unk_008[0]++;
      if (!(g->unk_008[0] & 0x10)) {  // blink?
        if (g->unk_006 != 0) {
          PrintUnicodeString(Unicode_CursorUp, 28 - (noLeftMugshot * 7), w->y8 + 2);
        }
        if (g->unk_006 < count - FREE_RUN_VISIBLE_ROWS) {
          PrintUnicodeString(Unicode_CursorDown, 28 - (noLeftMugshot * 7), w->y8 + 5);
        }
      }

      if (g->unk_008[1] != 0) {
        g->unk_008[1]--;
        return;
      }

      if (gJoypad[0].pressed & B_BUTTON) {
        PlaySound(SE_NO);
        PrintOptionMessage1(0x0F);  // Your orders, please.
        g->unk_008[1] = 0;
        g->mode[3] = 5;
        return;
      }
      if (!(gJoypad[0].pressed & A_BUTTON) || (count == 0)) {
        return;
      }
      PlaySound(SE_YES);
      g->frames = available[g->frames];
      g->mode[3]++;
      return;
    }

    case 15: {
      PrintOptionMessagePtr(gApFreeRunConfirmTexts[g->frames]);
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
        g->mode[3] = 13;
        return;
      }
      if (ans < 0) {  // RETRY MISSION
        ApRequestMissionRerun(gFreeRunStageIDs[g->frames]);
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
      (g->save).stageID = gFreeRunStageIDs[g->frames];
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
