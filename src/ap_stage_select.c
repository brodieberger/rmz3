#include "ap.h"

#include "constants/flag.h"
#include "constants/game.h"
#include "constants/song.h"
#include "constants/stage_id.h"
#include "entity.h"
#include "game.h"
#include "global.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "story.h"
#include "text.h"
#include "vfx.h"

#if AP

struct VFX* CreateStageBossMugshots(void* selection);
void FUN_080c5f98(struct Entity* p);

#define AP_SELECT_PAGE_SIZE 4
/*
  Pages 0, 1, and 2 are portraits. Page 3 is the four stages with no mugshot art anywhere in the ROM, and it just is a row of names instead (WIP)
*/
#define AP_SELECT_ART_PAGES 3
#define AP_SELECT_PAGE_COUNT (AP_SELECT_ART_PAGES + 1)
#define AP_SELECT_MISSION_COUNT (AP_SELECT_PAGE_COUNT * AP_SELECT_PAGE_SIZE)
#define AP_SELECT_ART_MISSIONS (AP_SELECT_ART_PAGES * AP_SELECT_PAGE_SIZE)

/* Where the name row sits, in text lines. Rows are two tiles tall. */
#define AP_SELECT_LIST_Y 3
#define AP_SELECT_LIST_X 4

/*
  Backing out ends the conversation
*/
#define AP_SELECT_EXIT_STATE 8

/* Vanilla game uses a lockout before state 7 takes input, so a held A does not fall through. */
#define AP_SELECT_OPEN_DELAY 0x3C
/*
  Frames between destroying a page and creating the next one.
*/
#define AP_SELECT_CREATE_DELAY 2

/*
  Mission index -> stage ID.
  Only the first four have any art.
*/
static const u8 sApMissionStage[AP_SELECT_MISSION_COUNT] = {
    2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 1, 6, 15, 16,
};

#define ApSelectStageOf(mission) (sApMissionStage[mission])
#define ApSelectHandle(g) ((struct Entity**)(g)->sceneState.raw)
#define ApSelectPageOf(g) ((s16)((g)->unk_006 / AP_SELECT_PAGE_SIZE))
#define ApSelectPageHasArt(g) ((g)->unk_006 < AP_SELECT_ART_MISSIONS)

/* from charmap-us.txt. Letters are 'A' = 0x0B upwards. */
#define AP_CHAR_ZERO 0x01
#define AP_CHAR_SPACE 0x00
#define AP_CHAR_SLASH 0xD8
#define AP_CHAR_END 0xFF

static const char_t sApSelectLocked[] = {0x16, 0x19, 0x0D, 0x15, 0x0F, 0x0E, AP_CHAR_END};         // LOCKED
static const char_t sApSelectCleared[] = {0x0D, 0x16, 0x0F, 0x0B, 0x1C, 0x0F, 0x0E, AP_CHAR_END};  // CLEARED

/*
  PrintString pointer
*/
EWRAM_DATA static char_t sApSelectStatus[20] = {0};

/* Set once the current page's portraits (or name row) are up. Cleared by every page increment. */
EWRAM_DATA static bool8 sApSelectBuilt = FALSE;

/* The final stage is the one with no entry in the game's own free-run name table. */
static void ApSelectPrintName(u8 stageID, u32 x, u32 y) {
  if (stageID == AP_STAGE_FINAL) {
    PrintString(gApFinalStageName, x, y);
  } else {
    PrintString(STRING(gFreeRunStageNameIdxs[stageID - 1]), x, y);
  }
}

/*
  Page 3 lists its four stages by name rather than by portrait WIP
*/
static void ApSelectPrintNameRow(struct GameState* g) {
  s16 i;

  for (i = 0; i < AP_SELECT_PAGE_SIZE; i++) {
    ApSelectPrintName(ApSelectStageOf(g->unk_006 + i), AP_SELECT_LIST_X, (u32)(AP_SELECT_LIST_Y + (i * 2)));
  }
  PrintString(STRING(0), AP_SELECT_LIST_X - 2, (u32)(AP_SELECT_LIST_Y + ((g->frames - g->unk_006) * 2)));  // the cursor
}

static char_t* ApSelectPutNumber(char_t* p, u8 n) {
  if (n >= 10) {
    *p++ = (char_t)(AP_CHAR_ZERO + (n / 10));
  }
  *p++ = (char_t)(AP_CHAR_ZERO + (n % 10));
  return p;
}

/* "6/10  LOCKED", one text line under the stage name.*/
static void ApSelectPrintStatus(u8 stageID) {
  char_t* p = sApSelectStatus;
  const char_t* word = NULL;
  u8 i;

  p = ApSelectPutNumber(p, ApDisksInStage(stageID));
  *p++ = AP_CHAR_SLASH;
  p = ApSelectPutNumber(p, ApDiskTotalInStage(stageID));
  *p++ = AP_CHAR_SPACE;
  *p++ = AP_CHAR_SPACE;

  if (!ApStageUnlocked(stageID)) {
    word = sApSelectLocked;
  } else if (gMissionDones & (1 << stageID)) {
    word = sApSelectCleared;
  }
  if (word != NULL) {
    for (i = 0; word[i] != AP_CHAR_END; i++) {
      *p++ = word[i];
    }
  }
  *p = AP_CHAR_END;

  PrintString(sApSelectStatus, 2, 15);
}

/*
  Picks which four portraits to spawn from the story tier
*/
static struct Entity* ApSelectCreatePage(struct GameState* g, s16 first) {
  u8* flags = gCurStory.s.gameflags;
  u8 saved1 = flags[1];
  u8 saved2 = flags[2];
  struct Entity* mugshots;

  if (first < 4) {
    CLEAR_FLAG(flags, FLAG_FIRST4_DONE);
  } else if (first < 8) {
    SET_FLAG(flags, FLAG_FIRST4_DONE);
    CLEAR_FLAG(flags, FLAG_MID3_DONE);
  } else {
    SET_FLAG(flags, FLAG_FIRST4_DONE);
    SET_FLAG(flags, FLAG_MID3_DONE);
    SET_FLAG(flags, FLAG_AREAX2_DONE);
  }

  mugshots = (struct Entity*)CreateStageBossMugshots(&g->frames);

  flags[1] = saved1;
  flags[2] = saved2;
  return mugshots;
}

static void ApSelectSpawnPortrait(struct Entity* parent, u8 mission) {
  struct Entity* e = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);

  if (e == NULL) {
    return;
  }
  e->renderPrio = 1;
  e->id = 0x47;  // VFX 71
  e->onUpdate = (*gVFXFnTable[71])[ENTITY_INIT];
  e->tileNum = 0;
  e->palID = 0;
  e->work[0] = 1;  // BOSS_MUGSHOT
  e->work[1] = mission;
  e->unk_28 = parent;
}

static void ApSelectSetPage(struct GameState* g, s16 page) {
  g->unk_006 = (s16)(page * AP_SELECT_PAGE_SIZE);
  g->unk_008[0] = (s16)(g->unk_006 + (AP_SELECT_PAGE_SIZE - 1));
  g->frames = g->unk_006;
}

static void ApSelectTearDown(struct GameState* g) {
  struct Entity** handle = ApSelectHandle(g);

  if (*handle != NULL) {
    FUN_080c5f98(*handle);
    *handle = NULL;
  }
  sApSelectBuilt = FALSE;
}

/*
  The portrait stage select
*/
void ApStageSelect(struct GameState* g) {
  struct Entity** handle = ApSelectHandle(g);
  TextWindowText* w = &gTextWindow.text;
  u8 stageID;

  switch (g->mode[3]) {
    case 6: {
      *handle = NULL;
      sApSelectBuilt = FALSE;
      ApSelectSetPage(g, 0);
      g->unk_008[1] = AP_SELECT_CREATE_DELAY;
      g->mode[3]++;
      return;
    }

    /*
      Leave the conversation.
    */
    case AP_SELECT_EXIT_STATE: {
      if (w->mode != 0) {
        w->flag |= TEXT_FLAG_TERMINATE;
      } else {
        SetGameMode(g, GAMEMODE(MAINGAME, OVERWORLD, 0, 0));
      }
      return;
    }

    case 7: {
      if ((w->mode != 0) && (w->mode != TEXT_MODE_OPTION)) {
        return;
      }

      if (!sApSelectBuilt) {
        if (g->unk_008[1] != 0) {
          g->unk_008[1]--;
          return;
        }
        g->frames = g->unk_006;
        if (ApSelectPageHasArt(g)) {
          *handle = ApSelectCreatePage(g, g->unk_006);
          if (*handle == NULL) {
            g->mode[3] = AP_SELECT_EXIT_STATE;  // out of entities: leave rather than retry forever
            return;
          }
          if (g->unk_006 == AP_SELECT_PAGE_SIZE) {
            ApSelectSpawnPortrait(*handle, 7);
          }
        }
        PrintOptionMessage1(0x13);  // Which mission?
        sApSelectBuilt = TRUE;
        g->unk_008[1] = AP_SELECT_OPEN_DELAY;
      }

      /* Left/right walk the row, L/R tab between pages. WIP will soon allow left right to also tab. */
      if (gJoypad[0].field3_0x6 & DPAD_RIGHT) {
        PlaySound(SE_CURSOR);
        g->frames = (g->frames < g->unk_008[0]) ? (s16)(g->frames + 1) : g->unk_006;
      } else if (gJoypad[0].field3_0x6 & DPAD_LEFT) {
        PlaySound(SE_CURSOR);
        g->frames = (g->frames > g->unk_006) ? (s16)(g->frames - 1) : g->unk_008[0];
      }

      if (!ApSelectPageHasArt(g)) {
        ApSelectPrintNameRow(g);
      }

      stageID = ApSelectStageOf(g->frames);
      ApSelectPrintName(stageID, 2, 13);
      ApSelectPrintStatus(stageID);

      if (g->unk_008[1] != 0) {
        g->unk_008[1]--;
        return;
      }

      if (gJoypad[0].pressed & (L_BUTTON | R_BUTTON)) {
        s16 page = ApSelectPageOf(g);

        if (gJoypad[0].pressed & R_BUTTON) {
          page = (s16)((page + 1) % AP_SELECT_PAGE_COUNT);
        } else {
          page = (s16)((page + (AP_SELECT_PAGE_COUNT - 1)) % AP_SELECT_PAGE_COUNT);
        }
        PlaySound(SE_CURSOR);
        ApSelectTearDown(g);
        ApSelectSetPage(g, page);
        g->unk_008[1] = AP_SELECT_CREATE_DELAY;
        return;
      }

      if (gJoypad[0].pressed & B_BUTTON) {
        PlaySound(SE_NO);
        ApSelectTearDown(g);
        g->mode[3] = AP_SELECT_EXIT_STATE;
        return;
      }

      if (!(gJoypad[0].pressed & A_BUTTON)) {
        return;
      }
      if (!ApStageUnlocked(stageID)) {
        PlaySound(SE_NOT_ALLOWED);
        return;
      }

      PlaySound(SE_YES);
      ApSelectTearDown(g);
      g->frames = (s16)(stageID - 1);
      g->mode[3] = 15;
      return;
    }
  }
}

#endif /* AP */
