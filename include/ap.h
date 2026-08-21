#ifndef GUARD_RMZ3_AP_H
#define GUARD_RMZ3_AP_H

#include "gba/gba.h"
#include "types.h"

/*  
Archipelago stuff.
  The build exports gAp's location and field offsets to ap_symbols.json for the AP client.

    game -> client    checkedLocations   locations the player checked
    client -> game    itemInbox          items Archipelago sent
    client -> game    serverChecked      locations the SERVER says are checked
*/
/* Spells 'APZ3'. ApInit writes it once the mailbox is ready. */
#define AP_READY 0x335A5041u
#define AP_VERSION 19

/*
    Highest location ID the AP World defines
  Bit N of checkedLocations means location N has been checked.
*/
#define AP_MAX_LOCATION_ID 248
#define AP_CHECKED_LOCATION_BYTES ((AP_MAX_LOCATION_ID / 8) + 1)

#define AP_ITEM_INBOX_LEN 16
#define AP_ITEM_INBOX_MASK (AP_ITEM_INBOX_LEN - 1)
#define AP_ITEM_DISK_FIRST 1
#define AP_ITEM_DISK_LAST 180
#define AP_DISK_BYTES 45

#define AP_ITEM_SUBTANK_1 221
#define AP_ITEM_SUBTANK_2 222
#define AP_LOC_SUBTANK_1 221
#define AP_LOC_SUBTANK_2 222

//197 Ice     198 Thunder   199 Flame         200 Light   201 Absorber
#define AP_ITEM_BODY_CHIP_FIRST 197
#define AP_ITEM_BODY_CHIP_LAST 201

//202 Spike   203 Quick     204 Double Jump   205 Shadow Dash
#define AP_ITEM_FOOT_CHIP_FIRST 202
#define AP_ITEM_FOOT_CHIP_LAST 205

/*
  206..217 EX skills, ordered to match EXSKILL_ID_... so the ID maps straight across.

  206..220 are also the A+ rank clear locations.
*/
#define AP_ITEM_EXSKILL_FIRST 206
#define AP_ITEM_EXSKILL_LAST 217

//224 Buster   225 Z-Saber   226 Recoil Rod   227 Shield Boomerang
#define AP_ITEM_WEAPON_FIRST 224
#define AP_ITEM_WEAPON_LAST 227

/*
  Stage access items. 181 is intro stage, 195 is the final boss level
*/
#define AP_ITEM_STAGE_ACCESS_FIRST 181
#define AP_ITEM_STAGE_ACCESS_LAST 195

/*
  Story progress items.
*/
#define AP_ITEM_STORY_MID 229   // FLAG_FIRST4_DONE
#define AP_ITEM_STORY_LATE 230  // FLAG_LATER4_DONE

#define AP_LOC_ROD 226
#define AP_LOC_SHIELD 227
#define AP_LOC_EXLIFE_FIRST 231
#define AP_EXLIFE_COUNT 11

// E-Reader Modifications
#define AP_ITEM_EREADER_BIT_FIRST 111
#define AP_ITEM_EREADER_BIT_LAST 140
#define AP_ITEM_EREADER_BYTE_FIRST 141
#define AP_ITEM_EREADER_BYTE_LAST 180
#define AP_EREADER_NO_CARD 0xFF

// Filler items.
#define AP_ITEM_CRYSTAL_100 301
#define AP_CRYSTAL_100_AMOUNT 100
#define AP_EC_MAX 9999

/* ZeroStatus.subtankHP[] entry for a tank the player does not own (Doesnt render in the menu). */
#define AP_SUBTANK_NONE 0xFF
#define AP_STAGE_COUNT 18

// Weil's lab is currently the goal. This probably wont be changed.
#define AP_STAGE_FINAL STAGE_WEILS_LABO

/* gAp.killRequest states. */
#define AP_KILL_IDLE 0
#define AP_KILL_REQUESTED 1
#define AP_KILL_APPLIED 2

/*
  Pickups and other things the player has found, 
  Kept in GameSavedata.unused_240[8] so the game can save it.
*/
#define AP_TAKEN_BYTE 8
#define AP_TAKEN_SUBTANK1 (1 << 0)
#define AP_TAKEN_SUBTANK2 (1 << 1)

// Stages Archipelago has opened.
#define AP_UNLOCK_BYTE 12

// Best rank ever earned in each stage.
#define AP_RANK_BYTE 0
#define AP_RANK_NONE 0

// Every stage but the final one cleared.
#define AP_MISSION_DONES_ALL 0xFFFEu

//How many items had been granted as of the last save, u16 in unused_240[10..11].
#define AP_APPLIED_BYTE 10

/*
  Mission score that counts as an A+ clear.

  This is compared against gScore.resultScore, the score for the mission that just finished instead of the average like in base game.
*/
#define AP_RANK_A_PLUS_SCORE 85

#if AP

struct ApState {
  u32 ready;    // AP_READY once ApInit has run.
  u16 version;  // AP_VERSION. both must match.

  u16 itemInbox[AP_ITEM_INBOX_LEN];  // client -> game.

  /*
    Total items granted. The AP client watches this go backwards to spot a rewind, a
    savestate, or an older save file being loaded, and resends from there.
  */
  u16 itemsApplied;

  u8 inboxWriteIndex;  // slot the client will fill next. Client moves this.
  u8 inboxReadIndex;   // slot the game will grant next. Game moves this.
                       // Equal indices mean the inbox is empty.

  u8 checkedLocations[AP_CHECKED_LOCATION_BYTES];

  /*
    Record of what this game has checked
  */
  u8 serverChecked[AP_CHECKED_LOCATION_BYTES];

  u8 rankElfUsed;  // set by the A-rank fusion elf, cleared each mission

  // Goal reporting
  u16 disksOwned;  // AP disks held in save.savedDisk
  
  u16 deathCount;
  u8 killRequest;

  u8 canAcceptItems;
};

static_assert(sizeof(struct ApState) == 116);

extern struct ApState gAp;

struct ApSeedConfig {
  u16 requiredDisks;   // disks needed to open the final stage.
  u8 startingWeapons;  // ZeroStatus.unlockedWeapon bitfield Zero starts with
  u8 easyExSkill;      // award the EX skill location check regardless of rank
};

static_assert(sizeof(struct ApSeedConfig) == 4);

extern const struct ApSeedConfig gApSeedConfig;

struct ZeroStatus;

void ApInit(void);
void ApUpdate(void);
void ApMarkLocationChecked(u16 locationID);
void ApMarkNpcDialogueChecked(TextID textID);
void ApMarkStageCleared(void);
void ApSetRankElf(void);
void ApResetMissionFlags(void);
void ApOnZeroDied(void);
void ApApplyStartingWeapons(struct ZeroStatus* status);
void ApFixEquippedWeapons(struct ZeroStatus* status);
void ApRequestMissionRerun(u8 stageID);
bool32 ApTakeMissionRerun(u8 stageID);
bool32 ApInMissionRerun(void);
u8 ApUpdateStageRank(u8 stageID, u8 missionRank);
u8 ApStageBestRank(u8 stageID);

struct GameState;
void ApCmdRoomTalk(struct GameState* g);

/* The portrait stage select */
void ApStageSelect(struct GameState* g);

/* ap_stage_select.c */
bool32 ApStageUnlocked(u8 stageID);

bool32 ApServerChecked(u16 locationID);

bool32 ApInDemo(void);

/* Which 1-UP location a pickup is */
u16 ApExLifeLocation(u8 stageID, s32 coordX);
void ApMarkExLifeCollected(u8 stageID, s32 coordX);

struct Pickup;
void ApSpawnExLifeOrbit(struct Pickup* p);

/* Sets a story flag in gCurStory and save.story. */
void ApSetStoryFlag(u8 flag);

/* The stage list's disk readout, "found / total". Both are AP block callers too. */
u8 ApDisksInStage(u8 stageID);
u8 ApDiskTotalInStage(u8 stageID);

extern const char_t* const gApStageRevisitTexts[];
extern const char_t* const gApStageStartTexts[];
extern const char_t gApFinalStageName[];

extern void (*const gApInitFn)(void);
extern void (*const gApUpdateFn)(void);
extern void (*const gApMarkLocationCheckedFn)(u16 locationID);
extern void (*const gApMarkExLifeCollectedFn)(u8 stageID, s32 coordX);
extern void (*const gApMarkNpcDialogueCheckedFn)(TextID textID);
extern void (*const gApMarkStageClearedFn)(void);
extern void (*const gApSetRankElfFn)(void);
extern void (*const gApResetMissionFlagsFn)(void);
extern void (*const gApOnZeroDiedFn)(void);
extern void (*const gApApplyStartingWeaponsFn)(struct ZeroStatus* status);
extern void (*const gApFixEquippedWeaponsFn)(struct ZeroStatus* status);
extern void (*const gApCmdRoomTalkFn)(struct GameState* g);
extern void (*const gApRequestMissionRerunFn)(u8 stageID);
extern bool32 (*const gApTakeMissionRerunFn)(u8 stageID);
extern bool32 (*const gApInMissionRerunFn)(void);
extern u8 (*const gApUpdateStageRankFn)(u8 stageID, u8 missionRank);
extern void (*const gApSpawnExLifeOrbitFn)(struct Pickup* p);

#define ApInit() gApInitFn()
#define ApUpdate() gApUpdateFn()
#define ApMarkLocationChecked(locationID) gApMarkLocationCheckedFn(locationID)
#define ApMarkExLifeCollected(stageID, coordX) gApMarkExLifeCollectedFn(stageID, coordX)
#define ApMarkNpcDialogueChecked(textID) gApMarkNpcDialogueCheckedFn(textID)
#define ApMarkStageCleared() gApMarkStageClearedFn()
#define ApSetRankElf() gApSetRankElfFn()
#define ApResetMissionFlags() gApResetMissionFlagsFn()
#define ApOnZeroDied() gApOnZeroDiedFn()
#define ApApplyStartingWeapons(status) gApApplyStartingWeaponsFn(status)
#define ApFixEquippedWeapons(status) gApFixEquippedWeaponsFn(status)
#define ApCmdRoomTalk(g) gApCmdRoomTalkFn(g)
#define ApRequestMissionRerun(stageID) gApRequestMissionRerunFn(stageID)
#define ApTakeMissionRerun(stageID) gApTakeMissionRerunFn(stageID)
#define ApInMissionRerun() gApInMissionRerunFn()
#define ApUpdateStageRank(stageID, missionRank) gApUpdateStageRankFn(stageID, missionRank)
#define ApSpawnExLifeOrbit(p) gApSpawnExLifeOrbitFn(p)

/*
  Point gStageDiskManager.disk at AP's inventory, or back at the game's.
  Used for when you are in game collecting disks and switches when talking to cerveau.

  AP's inventory is save.savedDisk. Which was used for game over backups in the vanilla game.
*/
#define ApUseApDiskInventory(g) (gStageDiskManager.disk = (g)->save.savedDisk)
#define ApUseGameDiskInventory(g) (gStageDiskManager.disk = (g)->save.disk)

/*
  Process_Game calls this instead of SwitchProcess()

  Trampoline in link.c, a direct BL can't reach ApUpdate.
  Runs ApUpdate() and then calls SwitchProcess() back.
*/
void ApFrameHook(bool32 b);
extern void (*const gApFrameHookFn)(bool32 b);

#else /* !AP */

#define ApInit() ((void)0)
#define ApUpdate() ((void)0)
#define ApMarkLocationChecked(locationID) ((void)0)
#define ApMarkNpcDialogueChecked(textID) ((void)0)
#define ApMarkStageCleared() ((void)0)
#define ApSetRankElf() ((void)0)
#define ApResetMissionFlags() ((void)0)
#define ApOnZeroDied() ((void)0)
#define ApApplyStartingWeapons(status) ((void)0)
#define ApFixEquippedWeapons(status) ((void)0)
#define ApRequestMissionRerun(stageID) ((void)0)
#define ApTakeMissionRerun(stageID) (0)
#define ApInMissionRerun() (0)
#define ApFrameHook(b) SwitchProcess(b)
#define ApUseApDiskInventory(g) ((void)0)
#define ApUseGameDiskInventory(g) ((void)0)

#endif /* AP */

#endif /* GUARD_RMZ3_AP_H */
