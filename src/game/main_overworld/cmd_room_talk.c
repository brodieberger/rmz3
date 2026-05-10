#include "game.h"
#include "global.h"
#include "mission.h"
#include "text.h"
#include "zero.h"

struct VFX* CreateStageBossMugshots(void* p);
void FUN_080c5f98(struct VFX* p);

extern u8 Unicode_CursorUp[];
extern u8 Unicode_CursorDown[];

static const u8 MissionBitfields_083861e8[MISSION_COUNT];
static const str_id_t StageNameIdxs[MISSION_COUNT];
static const TextID MissionSummaryTextIDs[MISSION_COUNT];
static const TextID MissionAskTextIDs[MISSION_COUNT];
static const u8 u8_ARRAY_0838623c[16];
static const TextID FreeRunStageTextIDs[FREE_STAGE_COUNT];
static const TextID FreeRunStageConfirmTextIDs[FREE_STAGE_COUNT];

void OverworldLoop_CmdRoomTalk(struct GameState *g) {
  s16 ans;
  struct TextWindowText* tw = &gTextWindow.text;

  switch (g->mode[3]) {
    default: {
      OverworldLoop_ManageSaveData(g);
      return;
    }

    case 0: {
      if (!(gCurStory.s.gameflags[1] & 2)) {
        g->mode[3] = 3;
        return;
      }
      PrintOptionMessage1(0);
      g->unk_008[1] = 0;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 1: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        PrintOptionMessage1(0xf);
        g->mode[3] = 5;
        return;
      }
      if (ans == -1) {
        g->mode[3] = 3;
        return;
      }
      PlaySound(3);
      g->mode[3] = 2;
      return;
    }

    case 2: {
      if (tw->mode == 0) {
        SetGameMode(g, 0x400);
        return;
      }
      tw->flag |= TEXT_FLAG_TERMINATE;
      return;
    }

    case 3:
    case 0x3f: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
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
        g->mode[3] = 0x40;
        return;
      }
      if (ans != -1) {
        PlaySound(3);
        g->mode[3] = 2;
        return;
      }
      /* ans == -1: confirmed mission mode */
      if ((gCurStory.s.gameflags[2] & 0x30) == 0x10) {
        SetScript(&gStageRun.vm, gStageScriptList[0x11][0x13]);
        setStageCheckpoint(0x13);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0x19;
        return;
      }
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
      g->mode[3] = 3;
      return;
    }

    case 5: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        if (gCurStory.s.gameflags[2] & 0x20) {
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
        /* init mission select */
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
          *(struct VFX**)&g->sceneState = NULL;
          g->mode[3]++;
          return;
        }
      }
      if (ans == -1) {
        g->mode[3] = 0xd;
        return;
      }
      PlaySound(3);
      g->mode[3] = 2;
      return;
    }

    case 6: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      if (*(struct VFX**)&g->sceneState == NULL) {
        *(struct VFX**)&g->sceneState = CreateStageBossMugshots(&g->frames);
      }
      PrintOptionMessage1(0x13);
      g->unk_008[1] = 0x3c;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 7: {
      if (g->unk_008[1] != 0) g->unk_008[1]--;
      if (g->unk_006 != g->unk_008[0]) {
        if (gJoypad[0].field3_0x6 & 0x10) {
          if (++g->frames > g->unk_008[0]) g->frames = g->unk_006;
          PlaySound(1);
        }
        if (gJoypad[0].field3_0x6 & 0x20) {
          g->frames = (g->frames == g->unk_006) ? g->unk_008[0] : g->frames - 1;
          PlaySound(1);
        }
      }
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      if (!(gMission.unk_00->missionDones & (1u << MissionBitfields_083861e8[g->frames]))) {
        PrintString(STRING(StageNameIdxs[g->frames]), 2, 0xd);
      } else {
        PrintString(STRING(75), 2, 0xd);
      }
      if (g->unk_008[1] != 0) return;
      if (gJoypad[0].pressed & 1) {
        if (gMission.unk_00->missionDones & (1u << MissionBitfields_083861e8[g->frames])) {
          PlaySound(4);
          return;
        }
        PlaySound(2);
        PrintOptionMessage2(MissionSummaryTextIDs[g->frames]);
        g->mode[3]++;
        return;
      }
      if (!(gJoypad[0].pressed & 2)) return;
      PlaySound(3);
      FUN_080c5f98(*(struct VFX**)&g->sceneState);
      g->mode[3] = 0xb;
      return;
    }

    case 8: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      g->unk_008[1] = 0;
      PrintOptionMessage1(MissionAskTextIDs[g->frames]);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 9: {
      u16 remaining;
      u32 md;

      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        FUN_080c5f98(*(struct VFX**)&g->sceneState);
        SetScript(&gStageRun.vm, gStageScriptList[0x11][6]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0xc;
        return;
      }
      /* ans <= 0, count remaining missions */
      remaining = 1;
      md = gMission.unk_00->missionDones;
      if (!(gCurStory.s.gameflags[1] & 8)) {
        remaining = (~(u16)(md >> 4) & 1) + (~(u16)(md >> 3) & 1) + (~(u16)(md >> 2) & 1);
        if (!(md & 0x20)) remaining++;
      } else if (!(gCurStory.s.gameflags[1] & 0x80)) {
        {
          s16 c = (~(md >> 8) & 1) + (~(md >> 7) & 1);
          remaining = (!(md & 0x200)) ? (u16)(c + 1) : (u16)c;
        }
      } else if (gCurStory.s.gameflags[2] & 1) {
        {
          s16 c = (~(md >> 0xd) & 1) + (~(md >> 0xc) & 1) + (~(md >> 0xb) & 1);
          remaining = (!(md & 0x4000)) ? (u16)(c + 1) : (u16)c;
        }
      }
      if (remaining < 2) {
        PrintOptionMessage2(0x12);
        g->mode[3]++;
        return;
      }
      PrintOptionMessage2(0x11);
      g->mode[3] = 6;
      return;
    }

    case 10: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      FUN_080c5f98(*(struct VFX**)&g->sceneState);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0xb: {
      if (tw->mode == 0) {
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5;
        return;
      }
      tw->flag |= TEXT_FLAG_TERMINATE;
      return;
    }

    case 0xc: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = MissionBitfields_083861e8[g->frames];
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }

    case 0xd: {
      PrintOptionMessage1(0x32);
      g->frames = 0;
      g->unk_006 = 0;
      g->unk_008[0] = 0;
      g->unk_008[1] = 0xf;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0xe: {
      s16 doneStages[16];
      s16 doneCount;
      s16 i;
      s16 j;
      u32 md;
      s16 mugshotAdj;

      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;

      /* Build list of done (unlocked for free-run) stages */
      doneCount = 0;
      md = gMission.unk_00->missionDones;
      for (i = 0; i < FREE_STAGE_COUNT; i++) {
        if (md & (1u << u8_ARRAY_0838623c[i])) {
          doneStages[doneCount++] = i;
        }
      }

      /* Cursor navigation (down) */
      if (g->frames < doneCount - 1 && (gJoypad[0].field3_0x6 & 0x80)) {
        PlaySound(1);
        g->frames++;
      }
      /* Cursor navigation (up) */
      if (g->frames > 0 && (gJoypad[0].field3_0x6 & 0x40)) {
        PlaySound(1);
        g->frames--;
      }

      /* Clamp scroll window to cursor */
      if (g->frames < g->unk_006) g->unk_006 = g->frames;
      if (g->unk_006 + 1 < g->frames) g->unk_006 = g->frames - 1;

      /* Draw visible stage entries */
      for (j = 0; j < doneCount; j++) {
        s16 row = j - g->unk_006;
        u32 rowBits = (u32)((s32)row * 0x2000000);
        if (rowBits >> 24 < 3) {
          mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
          PrintString(STRING(FreeRunStageTextIDs[doneStages[j]]),
                      10 - mugshotAdj * 7,
                      (s8)(rowBits >> 24) + 2 + tw->y);
        }
      }

      /* Draw cursor arrow */
      mugshotAdj = (tw->mugshotRight || tw->mugshot == 1) ? 1 : 0;
      PrintString(STRING(0), 8 - mugshotAdj * 7,
                  (g->frames - g->unk_006) * 2 + 2 + tw->y);

      /* Blink scroll arrows */
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

      if (g->unk_008[1] != 0) {
        g->unk_008[1]--;
        return;
      }
      if (gJoypad[0].pressed & 2) {
        PlaySound(3);
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5;
        return;
      }
      if (!(gJoypad[0].pressed & 1)) return;
      PlaySound(2);
      g->frames = doneStages[g->frames];
      g->mode[3]++;
      return;
    }

    case 0xf: {
      PrintOptionMessage1(FreeRunStageConfirmTextIDs[g->frames]);
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0x10: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        SetScript(&gStageRun.vm, gStageScriptList[0x11][8]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3]++;
        return;
      }
      g->mode[3] = 0xd;
      return;
    }

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
        *(struct VFX**)&g->sceneState = NULL;
      }
      g->mode[3] = 6;
      return;
    }

    case 0x13: {
      if (gCurStory.s.gameflags[2] & 0x40) {
        PrintOptionMessage2(0x2c);
        g->mode[3] = 0x15;
        return;
      }
      SetScript(&gStageRun.vm, gStageScriptList[0x11][20]);
      tw->flag |= TEXT_FLAG_TERMINATE;
      g->mode[3]++;
      FALLTHROUGH;
    }
    case 0x14: {
      if (gStageRun.vm.active & 1) return;
      gCurStory.s.gameflags[2] |= 0x40;
      PrintOptionMessage1(0x2d);
      g->unk_008[1] = 0;
      g->mode[3] = 0x16;
      return;
    }

    case 0x15: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      PrintOptionMessage1(0x2d);
      g->unk_008[1] = 0;
      g->mode[3]++;
      return;
    }

    case 0x16: {
      if (tw->mode != 0 && tw->mode != TEXT_MODE_OPTION) return;
      ans = (s16)handleWrapTwoChoice(g);
      if (ans == 0) return;
      if (ans > 0) {
        SetScript(&gStageRun.vm, gStageScriptList[0x11][6]);
        tw->flag |= TEXT_FLAG_TERMINATE;
        g->mode[3] = 0x17;
        return;
      }
      PrintOptionMessage1(0xf);
      g->unk_008[1] = 0;
      g->mode[3] = 5;
      return;
    }

    case 0x17: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = 0x10;
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }

    case 0x18: {
      if (tw->mode == 0 || tw->mode == TEXT_MODE_OPTION) {
        PrintOptionMessage1(0xf);
        g->unk_008[1] = 0;
        g->mode[3] = 5;
      }
      return;
    }

    case 0x19: {
      if (gStageRun.vm.active & 1) return;
      g->save.stageID = 0xf;
      saveCurStory(&g->save.story);
      CopyZeroStatus(g->z2, &g->save.status);
      InitMissionInfo(g->save.stageID, &g->save.playinfo);
      InitStageRun(g->save.stageID);
      SetGameMode(g, 0x300);
      return;
    }
  }
}

static const u8 MissionBitfields_083861e8[MISSION_COUNT] = {
    2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14,
};

/* Idx of 08372210 (StringOfsTable) */
static const str_id_t StageNameIdxs[MISSION_COUNT] = {
    63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
};

static const TextID MissionSummaryTextIDs[MISSION_COUNT] = {
    0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020, 0x0022, 0x0024, 0x0026, 0x0028, 0x002A,
};

static const TextID MissionAskTextIDs[MISSION_COUNT] = {
    0x0015, 0x0017, 0x0019, 0x001B, 0x001D, 0x001F, 0x0021, 0x0023, 0x0025, 0x0027, 0x0029, 0x002B,
};

static const u8 u8_ARRAY_0838623c[16] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
};

static const TextID FreeRunStageTextIDs[FREE_STAGE_COUNT] = {
    0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D,
};

static const TextID FreeRunStageConfirmTextIDs[FREE_STAGE_COUNT] = {
    0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040, 0x0041,
};
