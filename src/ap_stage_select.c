#include "ap.h"

#include "ap_mugshot.h"
#include "constants/flag.h"
#include "constants/game.h"
#include "constants/motion/static.h"
#include "constants/song.h"
#include "constants/stage_id.h"
#include "entity.h"
#include "game.h"
#include "gfx.h"
#include "motion.h"
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
#define AP_SELECT_ART_PAGES 3
#define AP_SELECT_PAGE_COUNT (AP_SELECT_ART_PAGES + 1)
#define AP_SELECT_MISSION_COUNT (AP_SELECT_PAGE_COUNT * AP_SELECT_PAGE_SIZE)

/*
  CreateStageBossMugshots work[0]
*/
#define AP_MUGSHOT_CHILD 1

/* updateBossMugshot mode[1] after animation plays. */
#define AP_MUGSHOT_SETTLED 3
#define AP_MUGSHOT_STATIC MOTION(SM207_MISSION_DONE_MUGSHOT, 0)

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
#define ApSelectStageAt(g, slot) (sApMissionStage[((g)->unk_006 * AP_SELECT_PAGE_SIZE) + (slot)])
#define ApSelectSelectedStage(g) ApSelectStageAt(g, (g)->frames)
#define ApSelectHandle(g) ((struct Entity**)(g)->sceneState.raw)
#define ApSelectPageOf(g) ((g)->unk_006)

/* from charmap-us.txt. Letters are 'A' = 0x0B upwards. */
#define AP_CHAR_ZERO 0x01
#define AP_CHAR_SPACE 0x00
#define AP_CHAR_SLASH 0xD8
#define AP_CHAR_DASH 0xD6
#define AP_CHAR_END 0xFF

#define AP_SELECT_LABEL_X 2
#define AP_SELECT_NAME_X 9
#define AP_SELECT_DISKS_X 9
#define AP_SELECT_STATUS_X 20
#define AP_SELECT_RANK_X 16

#define AP_SELECT_NAME_Y 13
#define AP_SELECT_DISKS_Y 15
#define AP_SELECT_RANK_Y 17

/* RANK_F to RANK_S */
#define AP_SELECT_RANK_COUNT 7

extern const char_t gApSelectStageLabel[];
extern const char_t gApSelectDisksLabel[];
extern const char_t gApSelectRankLabel[];
extern const char_t gApSelectLocked[];
extern const char_t gApSelectOpen[];
extern const char_t gApSelectCleared[];
extern const char_t gApSelectRankLetters[];

/*
  PrintString pointer
*/
EWRAM_DATA static char_t sApSelectStatus[20] = {0};
EWRAM_DATA static char_t sApSelectRankLine[12] = {0};

/* Set once the current page is up. Cleared by every page increment. */
EWRAM_DATA static bool8 sApSelectBuilt = FALSE;

/*
  The slot the cursor is on.
*/
EWRAM_DATA static s16 sApSelectSlot = 0;

/* The final stage is the one with no entry in the game's own free-run name table. */
static void ApSelectPrintName(u8 stageID, u32 x, u32 y) {
  if (stageID == AP_STAGE_FINAL) {
    PrintString(gApFinalStageName, x, y);
  } else {
    PrintString(STRING(gFreeRunStageNameIdxs[stageID - 1]), x, y);
  }
}

static char_t* ApSelectPutNumber(char_t* p, u8 n) {
  if (n >= 10) {
    *p++ = (char_t)(AP_CHAR_ZERO + (n / 10));
  }
  *p++ = (char_t)(AP_CHAR_ZERO + (n % 10));
  return p;
}

/* "Disks: 6/10" and, further along the same line, LOCKED / OPEN / CLEARED. */
static void ApSelectPrintDisks(u8 stageID) {
  char_t* p = sApSelectStatus;
  const char_t* status;

  p = ApSelectPutNumber(p, ApDisksInStage(stageID));
  *p++ = AP_CHAR_SLASH;
  p = ApSelectPutNumber(p, ApDiskTotalInStage(stageID));
  *p = AP_CHAR_END;

  /* Every stage says which of the three it is. Locked, Open, and Cleared. */
  if (!ApStageUnlocked(stageID)) {
    status = gApSelectLocked;
  } else if (gMissionDones & (1 << stageID)) {
    status = gApSelectCleared;
  } else {
    status = gApSelectOpen;
  }

  PrintString(gApSelectDisksLabel, AP_SELECT_LABEL_X, AP_SELECT_DISKS_Y);
  PrintString(sApSelectStatus, AP_SELECT_DISKS_X, AP_SELECT_DISKS_Y);
  PrintString(status, AP_SELECT_STATUS_X, AP_SELECT_DISKS_Y);
}

/*
  Third line: the best rank ever earned here, or a dash for a stage that hasn't been cleared.
*/
static void ApSelectPrintRank(u8 stageID) {
  u8 packedRank = ApStageBestRank(stageID);

  if ((packedRank == AP_RANK_NONE) || (packedRank > AP_SELECT_RANK_COUNT)) {
    sApSelectRankLine[0] = AP_CHAR_DASH;
  } else {
    sApSelectRankLine[0] = gApSelectRankLetters[packedRank - 1];
  }
  sApSelectRankLine[1] = AP_CHAR_END;

  PrintString(gApSelectRankLabel, AP_SELECT_LABEL_X, AP_SELECT_RANK_Y);
  PrintString(sApSelectRankLine, AP_SELECT_RANK_X, AP_SELECT_RANK_Y);
}

/*
  Picks which four portraits to spawn from the story tier.
  Should probably be replaced so that you go to the most recent page you were looking at.
*/
static struct Entity* ApSelectCreatePage(struct GameState* g) {
  u8* flags = gCurStory.s.gameflags;
  u8 saved1 = flags[1];
  u8 saved2 = flags[2];
  struct Entity* mugshots;

  CLEAR_FLAG(flags, FLAG_FIRST4_DONE);
  mugshots = (struct Entity*)CreateStageBossMugshots(&g->frames);

  flags[1] = saved1;
  flags[2] = saved2;
  return mugshots;
}

static const u16 sApSelectPageSheet[AP_SELECT_ART_PAGES] = {
    SM205_MISSION_MUGSHOT,
    SM206_MISSION_MUGSHOT,
    SM208_MISSION_MUGSHOT,
};

/*
  Page 3's four portraits (Ones with no mission art)
*/
static void ApSelectLoadNamelessArt(void) {
  u8 i;

  MemCopy32(gApMugshotTiles, (void*)(VRAM + BG_VRAM_SIZE + (AP_MUGSHOT_TILE * 32)),
            sizeof(gApMugshotTiles));
  for (i = 0; i < AP_MUGSHOT_COUNT; i++) {
    MemCopy32(gApMugshotPalette[i], &gPaletteManager.buf[(16 + AP_MUGSHOT_PAL + i) * 16],
              sizeof(gApMugshotPalette[i]));
  }
}

static void ApSelectLoadPageArt(s16 page) {
  if (page >= AP_SELECT_ART_PAGES) {
    ApSelectLoadNamelessArt();
    return;
  }
  LOAD_STATIC_GRAPHIC(sApSelectPageSheet[page]);
}

/*
  Jitter animation for a stage that is locked.
*/
static void ApSelectShakeStatic(struct Entity* p) {
  u8 xflip, yflip;

  p->work[3]++;
  xflip = (u8)((p->work[3] >> 2) & 1);
  yflip = (u8)((p->work[3] >> 3) & 1);

  p->flags = (u8)((p->flags & ~(X_FLIP | Y_FLIP)) | (xflip ? X_FLIP : 0) | (yflip ? Y_FLIP : 0));
  (p->spr).xflip = xflip;
  (p->spr).yflip = yflip;
  (p->spr).oam.xflip = xflip;
  (p->spr).oam.yflip = yflip;

  (p->unk_coord).x = (p->coord).x - (xflip << 8);
  (p->unk_coord).y = (p->coord).y - (yflip << 8);
  (p->spr).c = &p->unk_coord;
}

static void ApSelectStylePortrait(struct Entity* p, u8 slot, u8 stageID) {
  bool32 open = ApStageUnlocked(stageID);
  motion_t want = open ? MOTION(SM205_MISSION_MUGSHOT, slot) : AP_MUGSHOT_STATIC;

  if (p->motionID != (motion_id_t)(want >> 8)) {
    p->palID = (u8)(open ? slot : 0);
    SetMotion(p, want);
  }
  (p->d).x = (s32)want;

  if (!open && (p->mode[1] == AP_MUGSHOT_SETTLED)) {
    ApSelectShakeStatic(p);
    return;
  }

  p->flags &= ~(X_FLIP | Y_FLIP);
  (p->spr).xflip = FALSE;
  (p->spr).yflip = FALSE;
  (p->spr).oam.xflip = FALSE;
  (p->spr).oam.yflip = FALSE;
  (p->spr).c = &p->coord;
}

static void ApSelectStyleRow(struct GameState* g) {
  struct EntityHeader* h = gVFXHeaderPtr;
  struct Entity* p = h->head;

  while (p != (struct Entity*)&h->tail) {
    if ((p->id == VFX_MISSION_INFO) && (p->work[0] == AP_MUGSHOT_CHILD) &&
        (p->work[1] < AP_SELECT_PAGE_SIZE)) {
      if (p->mode[1] != 0) {
        ApSelectStylePortrait(p, p->work[1], ApSelectStageAt(g, p->work[1]));
      }
    }
    p = p->next;
  }
}

static void ApSelectSetPage(struct GameState* g, s16 page) {
  g->unk_006 = page;
  g->unk_008[0] = AP_SELECT_PAGE_SIZE - 1;
  g->frames = sApSelectSlot = 0;
}

/*
  Fix for Boss portraits stealing the palette used by the AP item pop up sprites.
*/
static void ApSelectRestorePickupPalette(void) {
  LOAD_STATIC_GRAPHIC(SM176_RESULT_DISK + gSystemSavedata.disk);
}

static void ApSelectTearDown(struct GameState* g) {
  struct Entity** handle = ApSelectHandle(g);

  if (*handle != NULL) {
    FUN_080c5f98(*handle);
    *handle = NULL;
  }
  ApSelectRestorePickupPalette();
  sApSelectBuilt = FALSE;
}

/*
  Turn to the next or previous page, wrap to the start or end
*/
static void ApSelectTurnPage(struct GameState* g, s16 step) {
  s16 page = (s16)((ApSelectPageOf(g) + step + AP_SELECT_PAGE_COUNT) % AP_SELECT_PAGE_COUNT);

  PlaySound(SE_CURSOR);
  ApSelectTearDown(g);
  ApSelectSetPage(g, page);
  if (step < 0) {
    g->frames = sApSelectSlot = g->unk_008[0];
  }
  g->unk_008[1] = AP_SELECT_CREATE_DELAY;
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
      /*
        Advances the flag where Cerveau tells you to talk to Ciel in the intro.
      */
      ApSetStoryFlag(FLAG_10);
      ApSetStoryFlag(FLAG_8);

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
      if (sApSelectBuilt) {
        ApSelectStyleRow(g);
      }

      if ((w->mode != 0) && (w->mode != TEXT_MODE_OPTION)) {
        return;
      }

      if (!sApSelectBuilt) {
        if (g->unk_008[1] != 0) {
          g->unk_008[1]--;
          return;
        }
        if ((sApSelectSlot < 0) || (sApSelectSlot > g->unk_008[0])) {
          sApSelectSlot = 0;
        }
        g->frames = sApSelectSlot;
        *handle = ApSelectCreatePage(g);
        if (*handle == NULL) {
          g->mode[3] = AP_SELECT_EXIT_STATE;  // out of entities: leave rather than retry forever
          return;
        }
        ApSelectLoadPageArt(ApSelectPageOf(g));
        PrintOptionMessage1(0x13);  // Which mission?
        sApSelectBuilt = TRUE;
        g->unk_008[1] = AP_SELECT_OPEN_DELAY;
      }

      if (gJoypad[0].pressed & R_BUTTON) {
        ApSelectTurnPage(g, 1);
        return;
      }
      if (gJoypad[0].pressed & L_BUTTON) {
        ApSelectTurnPage(g, -1);
        return;
      }
      if (gJoypad[0].field3_0x6 & DPAD_RIGHT) {
        if (g->frames >= g->unk_008[0]) {
          ApSelectTurnPage(g, 1);
          return;
        }
        PlaySound(SE_CURSOR);
        g->frames++;
      } else if (gJoypad[0].field3_0x6 & DPAD_LEFT) {
        if (g->frames <= 0) {
          ApSelectTurnPage(g, -1);
          return;
        }
        PlaySound(SE_CURSOR);
        g->frames--;
      }

      sApSelectSlot = g->frames;
      stageID = ApSelectSelectedStage(g);
      PrintString(gApSelectStageLabel, AP_SELECT_LABEL_X, AP_SELECT_NAME_Y);
      ApSelectPrintName(stageID, AP_SELECT_NAME_X, AP_SELECT_NAME_Y);
      ApSelectPrintDisks(stageID);
      ApSelectPrintRank(stageID);

      if (g->unk_008[1] != 0) {
        g->unk_008[1]--;
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
