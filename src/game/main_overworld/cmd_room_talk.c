/*
 * OverworldLoop_CmdRoomTalk
 *
 * State machine that runs the Command Room (Ciel's room) conversation and
 * mission/free-run selection UI. It is called once per frame by the overworld
 * update loop and dispatches on g->mode[3].
 *
 * State variables (all live in GameState fields):
 *   g->mode[3]     - current sub-state (0–0x19, 0x3f)
 *   g->frames      - cursor / selected mission index
 *   g->unk_006     - scroll viewport top (min cursor index kept on screen)
 *   g->unk_008[0]  - max cursor index (highest selectable mission)
 *   g->unk_008[1]  - frame timer / input-delay counter
 *   sceneState     - first 4 bytes reused as a VFX* for boss mugshot sprites
 *
 * Rough conversation flow:
 *   0→1  : initial check / "accept mission?" two-choice
 *   2    : exit back to overworld
 *   3→4  : mission briefing / "mission or free-run?" two-choice
 *   5    : top-level "mission or free-run?" dispatch
 *   6→0c : mission selection, confirm, and launch
 *   0d→11: free-run stage list, confirm, and launch
 *   12   : re-init mission select cursor (reached from case 9)
 *   13→17: EX-mission (Weil's Lab) flow and launch
 *   18   : wait for text then return to case 5
 *   19   : EX stage 0xf (tutorial/prologue) launch
 */

#include "game.h"
#include "global.h"
#include "mission.h"
#include "text.h"
#include "zero.h"

struct VFX* CreateStageBossMugshots(void* p);
void FUN_080c5f98(struct VFX* p);

extern u8 Unicode_CursorUp[];
extern u8 Unicode_CursorDown[];

/* Bit position within PlayInfo.missionDones for each of the 12 missions. */
static const u8 MissionBitfields_083861e8[MISSION_COUNT];

/* StringOfsTable index for each mission's stage-name string. */
static const str_id_t StageNameIdxs[MISSION_COUNT];

/* TextIDs shown in the mission summary panel (even indices). */
static const TextID MissionSummaryTextIDs[MISSION_COUNT];

/* TextIDs for the "confirm mission start?" prompt (odd indices). */
static const TextID MissionAskTextIDs[MISSION_COUNT];

/* missionDones bit positions for the 15 free-run stages, in list order. */
static const u8 u8_ARRAY_0838623c[16];

/* Stage-name TextIDs displayed in the free-run stage list. */
static const TextID FreeRunStageTextIDs[FREE_STAGE_COUNT];

/* Confirm-prompt TextIDs for each free-run stage. */
static const TextID FreeRunStageConfirmTextIDs[FREE_STAGE_COUNT];

/*
 * Helper macro to get/set the boss-mugshot VFX handle, which is overlaid on
 * the first 4 bytes of sceneState (a union normally used by menu/result
 * states, but unused during this overworld sub-state machine).
 */
#define MUGSHOT_HANDLE (*(struct VFX**)&g->sceneState)

void OverworldLoop_CmdRoomTalk(struct GameState* g) {
  s16 ans;
  struct TextWindowText* tw = &gTextWindow.text;

  /*
   * How the switch works:
   *   This function is called every frame. g->mode[3] is the "program counter"
   *   of the conversation. Each case either:
   *     - returns early (waiting for text or input this frame), or
   *     - sets g->mode[3] to the next state and returns so the new state runs
   *       on the following frame.
   *   FALLTHROUGH is used when two consecutive states share an entry point in
   *   the original assembly (case N sets up state then immediately runs case N+1
   *   on the same frame).
   */
  switch (g->mode[3]) {
    /* Any state > 0x3f falls here — treated as "done, hand off to save manager". */
    default: {
      OverworldLoop_ManageSaveData(g);
      return;
    }

      /* --- Initial contact / accept-mission prompt --- */

    case 0: {
      /* Skip straight to the briefing if missions aren't unlocked yet. */
      if (!(gCurStory.s.gameflags[1] & 2)) {
        g->mode[3] = 3;
        return;
      }
      /* Print "I have a mission for you" opener and ask yes/no. */
      PrintOptionMessage1(0);
      g->unk_008[1] = 0;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 1: {
      /* Wait for text window to finish scrolling or reach option prompt. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return; /* still waiting for player input */
      if (ans > 0) {
        /* YES — "I'm ready!" — skip briefing, go to mission/freerun menu. */
        PrintOptionMessage1(0xf);
        g->mode[3] = 5;
        return;
      }
      if (ans == -1) {
        /* NO — "Not now." — go to briefing loop. */
        g->mode[3] = 3;
        return;
      }
      /* Cancelled (neither clear yes nor no) — close dialog. */
      PlaySound(3);
      g->mode[3] = 2;
      return;
    }

      /* --- Exit dialog, return to overworld --- */

    case 2: {
      if (tw->mode == 0) {
        /* Text window closed — switch game mode back to normal overworld. */
        SetGameMode(g, 0x400);
        return;
      }
      /* Text still open — force it to close, will be caught next frame. */
      tw->flag |= TEXT_FLAG_TERMINATE;
      return;
    }

    /* --- Mission briefing / "mission or free-run?" prompt --- */

    /* case 0x3f is the same entry as case 3 in the original jump table. */
    case 3:
    case 0x3f: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      /* Print the "mission or free-run?" two-choice question. */
      PrintOptionMessage1(1);
      g->unk_008[1] = 0;
      g->mode[3] = 4;
      FALLTHROUGH;
    }
    case 4: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        /* Top option chosen (leave / not mission) — hand off to save manager. */
        g->mode[3] = 0x40;
        return;
      }
      if (ans != -1) {
        /* Unexpected value — cancel with sound. */
        PlaySound(3);
        g->mode[3] = 2;
        return;
      }
      /* Bottom option (ans == -1): mission confirmed — show Ciel's briefing. */
      if ((gCurStory.s.gameflags[2] & 0x30) == 0x10) {
        /* Special condition: start the EX-stage intro script directly. */
        SetScript(&gStageRun.vm, gStageScriptList[0x11][0x13]);
        setStageCheckpoint(0x13);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0x19;
        return;
      }
      /*
       * Print a mission-status message appropriate to story progress.
       * counts[0] tracks which message variant has already been shown so
       * Ciel doesn't repeat the same line on every visit.
       */
      if (!(gCurStory.s.gameflags[1] & 2)) {
        PrintOptionMessage2(0x1305);
      } else if (!(gCurStory.s.gameflags[1] & 8)) {
        if (gCurStory.s.counts[0] == 0) {
          PrintOptionMessage2(0x200);
          gCurStory.s.counts[0] = 1;
        } else {
          PrintOptionMessage2(0x201);
        }
      } else if (!(gCurStory.s.gameflags[2] & 1)) {
        if (gCurStory.s.counts[0] < 2) {
          PrintOptionMessage2(0x202);
          gCurStory.s.counts[0] = 2;
        } else {
          PrintOptionMessage2(0x203);
        }
      } else if (gCurStory.s.counts[0] < 3) {
        PrintOptionMessage2(0x204);
        gCurStory.s.counts[0] = 3;
      } else if (gCurStory.s.counts[0] < 4) {
        PrintOptionMessage2(0x205);
        gCurStory.s.counts[0] = 4;
      } else {
        PrintOptionMessage2(0x206);
      }
      /* Loop back to re-show the question after the briefing message. */
      g->mode[3] = 3;
      return;
    }

      /* --- Top-level "mission or free-run?" dispatch --- */

    case 5: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        /* YES = go to missions. Check story flags to see which flow applies. */
        if (gCurStory.s.gameflags[2] & 0x20) {
          /* EX mission available — go to the EX mission entry prompt. */
          g->mode[3] = 0x13;
          return;
        }
        if ((gCurStory.s.gameflags[2] & 0x14) == 4) {
          PrintOptionMessage2(0x1344);
          g->mode[3] = 0x18;
          return;
        }
        if ((gCurStory.s.gameflags[2] & 0x14) == 0x14) {
          PrintOptionMessage2(0x1345);
          g->mode[3] = 0x18;
          return;
        }
        /* Normal mission select — compute starting cursor and max index. */
        PrintOptionMessage2(0x10);
        {
          u16 base;
          s16 top, max;
          /*
           * base = starting mission index based on story stage:
           *   bit 3 of gameflags[1] (8 missions done): base 4, else 0
           *   bit 0 of gameflags[2] adds 1 (or 3+1 if gameflags[1] bit 7 set)
           */
          base = ((u16)(-(s16)(gCurStory.s.gameflags[1] & 8)) >> 12) & 4;
          if (!(gCurStory.s.gameflags[1] & 0x80)) {
            base |= (u16)(gCurStory.s.gameflags[2] & 1);
          } else {
            base += (u16)(gCurStory.s.gameflags[2] & 1) + 3;
          }
          g->unk_006 = (s16)base; /* min selectable index */
          g->frames = (s16)base;  /* start cursor here */
          top = 3;
          if (gCurStory.s.gameflags[1] & 8) top = 6;
          max = (s16)((gCurStory.s.gameflags[2] & 1) * 4);
          if (gCurStory.s.gameflags[1] & 0x80) max++;
          g->unk_008[0] = top + max; /* max selectable index */
          MUGSHOT_HANDLE = NULL;
          g->mode[3]++;
          return;
        }
      }
      if (ans == -1) {
        /* NO = free run — go to free-run stage list. */
        g->mode[3] = 0xd;
        return;
      }
      PlaySound(3);
      g->mode[3] = 2;
      return;
    }

      /* --- Mission selection UI --- */

    case 6: {
      /* One-time setup: spawn boss mugshots, print header, start delay timer. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      if (MUGSHOT_HANDLE == NULL) {
        /* Pass &g->frames so the VFX can read the cursor position each frame. */
        MUGSHOT_HANDLE = CreateStageBossMugshots(&g->frames);
      }
      PrintOptionMessage1(0x13);
      g->unk_008[1] = 0x3c; /* 60-frame input delay before player can confirm */
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 7: {
      /* Per-frame mission cursor update and display. */
      if (g->unk_008[1] != 0) g->unk_008[1]--;

      /* D-pad left/right scrolls through missions (wraps). */
      if (g->unk_006 != g->unk_008[0]) {
        if (gJoypad[0].field3_0x6 & 0x10) { /* right */
          if (++g->frames > g->unk_008[0]) g->frames = g->unk_006;
          PlaySound(1);
        }
        if (gJoypad[0].field3_0x6 & 0x20) { /* left */
          g->frames = (g->frames == g->unk_006) ? g->unk_008[0] : g->frames - 1;
          PlaySound(1);
        }
      }

      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;

      /* Print stage name, or a "cleared" placeholder if mission already done. */
      if (!(gMission.unk_00->missionDones & (1u << MissionBitfields_083861e8[g->frames]))) {
        PrintString(STRING(StageNameIdxs[g->frames]), 2, 0xd);
      } else {
        PrintString(STRING(75), 2, 0xd); /* string index 75 = "CLEAR" or similar */
      }

      if (g->unk_008[1] != 0) return; /* still in initial delay */

      if (gJoypad[0].pressed & 1) { /* A button */
        if (gMission.unk_00->missionDones & (1u << MissionBitfields_083861e8[g->frames])) {
          /* Mission already cleared — reject selection with error sound. */
          PlaySound(4);
          return;
        }
        /* Valid selection — show summary and advance to confirm prompt. */
        PlaySound(2);
        PrintOptionMessage2(MissionSummaryTextIDs[g->frames]);
        g->mode[3]++;
        return;
      }
      if (!(gJoypad[0].pressed & 2)) return; /* no B button */
      /* B button — cancel, destroy mugshots, return to main menu. */
      PlaySound(3);
      FUN_080c5f98(MUGSHOT_HANDLE);
      g->mode[3] = 0xb;
      return;
    }

    case 8: {
      /* Show "Are you sure you want to start this mission?" prompt. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      g->unk_008[1] = 0;
      PrintOptionMessage1(MissionAskTextIDs[g->frames]);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 9: {
      /* Wait for YES/NO on the mission confirm prompt. */
      u16 remaining;
      u32 md;

      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        /* YES — start the mission transport script. */
        FUN_080c5f98(MUGSHOT_HANDLE);
        SetScript(&gStageRun.vm, gStageScriptList[0x11][6]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0xc;
        return;
      }
      /*
       * NO — count how many missions are still available.
       * remaining = number of missions not yet cleared, capped per story tier.
       * If only 1 left this time, skip back to mission select (show "only one
       * mission remains" message). Otherwise let the player pick again.
       */
      remaining = 1;
      md = gMission.unk_00->missionDones;
      if (!(gCurStory.s.gameflags[1] & 8)) {
        /* Early tier: up to 4 missions (bits 2-5). */
        remaining = (~(u16)(md >> 4) & 1) + (~(u16)(md >> 3) & 1) + (~(u16)(md >> 2) & 1);
        if (!(md & 0x20)) remaining++;
      } else if (!(gCurStory.s.gameflags[1] & 0x80)) {
        /* Mid tier: up to 2 missions (bits 7-9). */
        {
          s16 c = (~(md >> 8) & 1) + (~(md >> 7) & 1);
          remaining = (!(md & 0x200)) ? (u16)(c + 1) : (u16)c;
        }
      } else if (gCurStory.s.gameflags[2] & 1) {
        /* Late tier: up to 3 missions (bits 11-14). */
        {
          s16 c = (~(md >> 0xd) & 1) + (~(md >> 0xc) & 1) + (~(md >> 0xb) & 1);
          remaining = (!(md & 0x4000)) ? (u16)(c + 1) : (u16)c;
        }
      }
      if (remaining < 2) {
        /* Only one mission left — print "just one mission" message, advance. */
        PrintOptionMessage2(0x12);
        g->mode[3]++; /* → case 10 */
        return;
      }
      /* More than one left — go back to mission select cursor. */
      PrintOptionMessage2(0x11);
      g->mode[3] = 6;
      return;
    }

    case 10: {
      /* Destroy mugshots before returning to the top-level menu. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      FUN_080c5f98(MUGSHOT_HANDLE);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0xb: {
      /* Wait for any pending text then print the "farewell" line and exit. */
      if (tw->mode == 0) {
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5; /* back to mission/freerun top menu */
        return;
      }
      tw->flag |= TEXT_FLAG_TERMINATE;
      return;
    }

      /* --- Mission launch (wait for transport script to finish) --- */

    case 0xc: {
      /* Spin until the VM script (transport animation) finishes. */
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = MissionBitfields_083861e8[g->frames];
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }

      /* --- Free-run stage list --- */

    case 0xd: {
      /* One-time init: print header, reset cursor and timer. */
      PrintOptionMessage1(0x32);
      g->frames = 0;
      g->unk_006 = 0;
      g->unk_008[0] = 0;
      g->unk_008[1] = 0xf; /* 15-frame initial input delay */
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0xe: {
      /*
       * Free-run stage list: build the list of cleared stages, handle
       * scrolling cursor, draw visible entries, and wait for player input.
       */
      s16 doneStages[16]; /* indices into u8_ARRAY_0838623c of cleared stages */
      s16 doneCount;
      s16 i;
      s16 j;
      u32 md;
      s16 mugshotAdj; /* x-offset when a mugshot portrait is visible */

      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;

      /* Build list of stages available for free-run (cleared in any run). */
      doneCount = 0;
      md = gMission.unk_00->missionDones;
      for (i = 0; i < FREE_STAGE_COUNT; i++) {
        if (md & (1u << u8_ARRAY_0838623c[i])) {
          doneStages[doneCount++] = i;
        }
      }

      /* D-pad down: move cursor down the list. */
      if (g->frames < doneCount - 1 && (gJoypad[0].field3_0x6 & 0x80)) {
        PlaySound(1);
        g->frames++;
      }
      /* D-pad up: move cursor up the list. */
      if (g->frames > 0 && (gJoypad[0].field3_0x6 & 0x40)) {
        PlaySound(1);
        g->frames--;
      }

      /*
       * Clamp viewport so the cursor is always visible.
       * The visible window shows 2 entries (rows 0 and 1 relative to unk_006).
       */
      if (g->frames < g->unk_006) g->unk_006 = g->frames;
      if (g->unk_006 + 1 < g->frames) g->unk_006 = g->frames - 1;

      /*
       * Draw each visible stage name.
       * rowBits trick: multiplying row by 0x2000000 then shifting right by 24
       * converts a signed row to a small unsigned value (0, 2, 4, …) that is
       * < 3 only for rows 0 and 1 (negative rows produce large values).
       */
      for (j = 0; j < doneCount; j++) {
        s16 row = j - g->unk_006;
        u32 rowBits = (u32)((s32)row * 0x2000000);
        if (rowBits >> 24 < 3) {
          mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
          PrintString(STRING(FreeRunStageTextIDs[doneStages[j]]), 10 - mugshotAdj * 7, (s8)(rowBits >> 24) + 2 + tw->y);
        }
      }

      /* Draw the selection arrow at the cursor's row within the viewport. */
      mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
      PrintString(STRING(0), /* STRING(0) is the cursor glyph */
                  8 - mugshotAdj * 7, (g->frames - g->unk_006) * 2 + 2 + tw->y);

      /*
       * Blink the up/down scroll arrows every 16 frames (bit 4 of the counter).
       * Only show the arrow if there are entries above/below the viewport.
       */
      g->unk_008[0]++;
      if (!(g->unk_008[0] & 0x10)) {
        if (g->unk_006 != 0) {
          mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
          PrintUnicodeString(Unicode_CursorUp, 0x1c - mugshotAdj * 7, tw->y + 2);
        }
        if (g->unk_006 < doneCount - 2) {
          mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
          PrintUnicodeString(Unicode_CursorDown, 0x1c - mugshotAdj * 7, tw->y + 5);
        }
      }

      /* Initial input delay (prevents accidental immediate confirmation). */
      if (g->unk_008[1] != 0) {
        g->unk_008[1]--;
        return;
      }
      if (gJoypad[0].pressed & 2) { /* B — cancel, back to mission/freerun menu */
        PlaySound(3);
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5;
        return;
      }
      if (!(gJoypad[0].pressed & 1)) return; /* wait for A */
      /* A — confirm: resolve cursor position to actual stage ID and advance. */
      PlaySound(2);
      g->frames = doneStages[g->frames];
      g->mode[3]++;
      return;
    }

    case 0xf: {
      /* Print the stage-specific "are you sure?" confirmation message. */
      PrintOptionMessage1(FreeRunStageConfirmTextIDs[g->frames]);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0x10: {
      /* Wait for YES/NO on free-run confirm. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        /* YES — start the free-run transport script. */
        SetScript(&gStageRun.vm, gStageScriptList[0x11][8]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3]++; /* → 0x11 */
        return;
      }
      /* NO — go back to the stage list. */
      g->mode[3] = 0xd;
      return;
    }

      /* --- Free-run launch (wait for transport script to finish) --- */

    case 0x11: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = u8_ARRAY_0838623c[g->frames];
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }

    /*
     * Re-initialize the mission-select cursor (jumped to from case 9 when
     * player has more than one mission still available).
     */
    case 0x12: {
      PrintOptionMessage2(0x10);
      {
        u16 base;
        s16 top, max;
        base = ((u16)(-(s16)(gCurStory.s.gameflags[1] & 8)) >> 12) & 4;
        if (!(gCurStory.s.gameflags[1] & 0x80)) {
          base |= (u16)(gCurStory.s.gameflags[2] & 1);
        } else {
          base += (u16)(gCurStory.s.gameflags[2] & 1) + 3;
        }
        g->unk_006 = (s16)base;
        g->frames = (s16)base;
        top = 3;
        if (gCurStory.s.gameflags[1] & 8) top = 6;
        max = (s16)((gCurStory.s.gameflags[2] & 1) * 4);
        if (gCurStory.s.gameflags[1] & 0x80) max++;
        g->unk_008[0] = top + max;
        MUGSHOT_HANDLE = NULL;
      }
      g->mode[3] = 6;
      return;
    }

      /* --- EX mission (Weil's Lab) flow --- */

    case 0x13: {
      if (gCurStory.s.gameflags[2] & 0x40) {
        /* EX mission already briefed — skip briefing, go to confirm prompt. */
        PrintOptionMessage2(0x2c);
        g->mode[3] = 0x15;
        return;
      }
      /* First time: run the EX-mission briefing script. */
      SetScript(&gStageRun.vm, gStageScriptList[0x11][20]);
      tw->flag |= TEXT_FLAG_TERMINATE;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0x14: {
      /* Wait for briefing script to complete, then show confirm prompt. */
      if (gStageRun.vm.active & 1) return;
      gCurStory.s.gameflags[2] |= 0x40; /* mark EX mission as briefed */
      PrintOptionMessage1(0x2d);
      g->unk_008[1] = 0;
      g->mode[3] = 0x16;
      return;
    }

    case 0x15: {
      /* (Repeated-visit path) Re-show the EX confirm prompt. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      PrintOptionMessage1(0x2d);
      g->unk_008[1] = 0;
      g->mode[3]++;
      return;
    }

    case 0x16: {
      /* Wait for YES/NO on EX-mission confirm. */
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        /* YES — start EX transport script (same script as mission transport). */
        SetScript(&gStageRun.vm, gStageScriptList[0x11][6]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0x17;
        return;
      }
      /* NO — go back to mission/freerun top menu. */
      PrintOptionMessage1(0xf);
      g->unk_008[1] = 0;
      g->mode[3] = 5;
      return;
    }

      /* --- EX mission launch (Weil's Lab, stage ID 0x10) --- */

    case 0x17: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = 0x10; /* Weil's Lab stage ID */
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }

    /* Wait for the current text to close, then return to the top menu. */
    case 0x18: {
      if (tw->mode == 0 || tw->mode == TEXT_MODE_OPTION) {
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5;
      }
      return;
    }

      /* --- EX stage 0xf (prologue / tutorial) launch --- */

    case 0x19: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = 0xf; /* stage ID for the intro stage */
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }
  }
}

/* Bit position within PlayInfo.missionDones for each mission (12 total). */
static const u8 MissionBitfields_083861e8[MISSION_COUNT] = {
    2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14,
};

/* StringOfsTable index for each mission's stage name. */
static const str_id_t StageNameIdxs[MISSION_COUNT] = {
    63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
};

static const TextID MissionSummaryTextIDs[MISSION_COUNT] = {
    0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020, 0x0022, 0x0024, 0x0026, 0x0028, 0x002A,
};

static const TextID MissionAskTextIDs[MISSION_COUNT] = {
    0x0015, 0x0017, 0x0019, 0x001B, 0x001D, 0x001F, 0x0021, 0x0023, 0x0025, 0x0027, 0x0029, 0x002B,
};

/*
 * missionDones bit positions for the 15 free-run stages in list order.
 * Index 15 (value 0) is a sentinel that wraps back to stage 0 in the
 * original 16-entry table but is never reached by the FREE_STAGE_COUNT loop.
 */
static const u8 u8_ARRAY_0838623c[16] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
};

static const TextID FreeRunStageTextIDs[FREE_STAGE_COUNT] = {
    0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D,
};

static const TextID FreeRunStageConfirmTextIDs[FREE_STAGE_COUNT] = {
    0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040, 0x0041,
};
