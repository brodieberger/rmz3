#include "ap.h"

#undef ApInit
#undef ApUpdate
#undef ApMarkLocationChecked
#undef ApMarkExLifeCollected
#undef ApMarkNpcDialogueChecked
#undef ApMarkStageCleared
#undef ApSetRankElf
#undef ApResetMissionFlags
#undef ApOnZeroDied
#undef ApApplyStartingWeapons
#undef ApFixEquippedWeapons
#undef ApRequestMissionRerun
#undef ApTakeMissionRerun
#undef ApInMissionRerun
#undef ApUpdateStageRank
#undef ApEndRun
#undef ApHasWeaponAbility
#undef ApChargeTier
#undef ApPrintWeaponStars
#undef ApFrameHook

#include "ap_disk_stage.h"
#include "ap_icon.h"
#include "constants/armor.h"
#include "constants/entity/boss.h"
#include "constants/entity/vfx.h"
#include "constants/exskill.h"
#include "constants/game.h"
#include "constants/motion/static.h"
#include "constants/song.h"
#include "constants/stage_id.h"
#include "constants/weapon.h"
#include "entity.h"
#include "game.h"
#include "global.h"
#include "mod.h"
#include "player/zero.h"
#include "score.h"
#include "script.h"
#include "sound.h"
#include "spawn.h"
#include "stagerun.h"
#include "system.h"
#include "text.h"
#include "vfx.h"

#if AP

EWRAM_DATA struct ApState gAp = {0};

/* Mission rerun state. Both hold stageID + 1,  0 means none. */
EWRAM_DATA static u8 sApRerunRequest = 0;
EWRAM_DATA static u8 sApRerunStage = 0;

/* Weapon Stars on pause screen */
#define AP_CHAR_STAR_FULL 0xE6
#define AP_CHAR_STAR_EMPTY 0xE7
#define AP_CHAR_END 0xFF
#define AP_STARS_Y 0x12
#define AP_STARS_RIGHT_X 28
#define AP_WEAPON_CHAIN_LONGEST 7
EWRAM_DATA static char_t sApWeaponStars[AP_WEAPON_CHAIN_LONGEST + 1] = {0};

/*
  These are the settings to be overwritten per by the seed.
*/
const struct ApSeedConfig gApSeedConfig = {
    120,
    (1 << WEAPON_BUSTER) | (1 << WEAPON_SABER),
    FALSE,
};

bool32 ApInDemo(void) {
  return FLAG(gCurStory.s.gameflags, DEMO_PLAY) != 0;
}

/* Main gameplay only. */
static bool32 ApCanAcceptItems(void) {
  if (ApInDemo()) {
    return FALSE;
  }
  if (gGameState.mode[0] != MAINGAME || gGameState.mode[1] != OVERWORLD) {
    return FALSE;
  }
  /*
    Wait for the player to actually have control.
  */
  {
    u16 raw = (gGameState.z2->input).raw;

    return raw != 0 && !(raw & INPUT_DISABLED);
  }
}

// Falls back to the buster when the player owns nothing.
static u8 ApFirstUnlockedWeapon(u8 unlocked) {
  u8 weapon;

  for (weapon = 0; weapon < WEAPON_KINDS; weapon++) {
    if (unlocked & (1 << weapon)) {
      return weapon;
    }
  }
  return WEAPON_BUSTER;
}


static u8 ApFirstUnlockedWeaponExcept(u8 unlocked, u8 except) {
  u8 weapon;

  for (weapon = 0; weapon < WEAPON_KINDS; weapon++) {
    if ((unlocked & (1 << weapon)) && weapon != except) {
      return weapon;
    }
  }
  return except;
}

void ApFixEquippedWeapons(struct ZeroStatus* status) {
  u8 unlocked = status->unlockedWeapon;
  bool8 replacedMain = FALSE;

  if (!(unlocked & (1 << status->weapons[0]))) {
    status->weapons[0] = ApFirstUnlockedWeapon(unlocked);
    replacedMain = TRUE;
  }
  if (!(unlocked & (1 << status->weapons[1])) ||
      (replacedMain && status->weapons[1] == status->weapons[0])) {
    status->weapons[1] = ApFirstUnlockedWeaponExcept(unlocked, status->weapons[0]);
  }
}

void ApApplyStartingWeapons(struct ZeroStatus* status) {
  status->unlockedWeapon = gApSeedConfig.startingWeapons;
  ApFixEquippedWeapons(status);
}

/*
  Translates AP order to the Game's order
  apItemID - AP_ITEM_*_FIRST.
*/
static const u8 sApBodyChips[] = {
    BODY_CHIP_ICE,       // 197
    BODY_CHIP_THUNDER,   // 198
    BODY_CHIP_FLAME,     // 199
    BODY_CHIP_LIGHT,     // 200
    BODY_CHIP_ABSORBER,  // 201
};

static const u8 sApFootChips[] = {
    FOOT_CHIP_SPIKE,   // 202
    FOOT_CHIP_QUICK,   // 203
    FOOT_CHIP_DOUBLE,  // 204
    FOOT_CHIP_SHADOW,  // 205
};

static_assert(ARRAY_COUNT(sApBodyChips) == (AP_ITEM_BODY_CHIP_LAST - AP_ITEM_BODY_CHIP_FIRST) + 1);
static_assert(ARRAY_COUNT(sApFootChips) == (AP_ITEM_FOOT_CHIP_LAST - AP_ITEM_FOOT_CHIP_FIRST) + 1);

/*
  e-Reader modifications. Index is apItemID - AP_ITEM_EREADER_BIT_FIRST. 
  Value is the absolute bit in SystemSavedata.flags[]. 
  AP_EREADER_NO_CARD for a disk in the range carrying no card.

  There are also attack or defense cards but these are not used as they change gameplay.
  Base decoration, a few E-Crystal reploids, two NPCs, and some small visuals.
  https://tcrf.net/Mega_Man_Zero_3/e-Reader_Functions
*/
static const u8 sApEReaderModBit[] = {
     64,  69,  70,  73,  80, AP_EREADER_NO_CARD,  83,  89,  91,  92,
     94,  97,  99, 100, 102, 103, 108, 110, 115, 116,
    118, 119, 121, 124, 129, 138, 140, 146, 148, 149,
};
static_assert(ARRAY_COUNT(sApEReaderModBit) ==
              (AP_ITEM_EREADER_BIT_LAST - AP_ITEM_EREADER_BIT_FIRST) + 1);

/*
  e-Reader cosmetic cards: one SystemSavedata byte set to one value. 

  SystemSavedata.disk (0x4B) changes the visuals for the disk. Could be re implemented later,
  but I dont feel like drawing two new disk sprites. If you are reading this and feel like doing so, go ahead.
*/ 
struct ApEReaderCosmetic {
  u8 offset;
  u8 value;
};

// NONE is flags[0], meaning the disk carries no card.
#define ER(field) ((u8)((u32) & (((SystemSavedata*)0)->field)))
#define ER_NONE 0

static const struct ApEReaderCosmetic sApEReaderCosmetic[] = {
    {ER(msgbox), 1},       {ER(msgbox), 2}, {ER(msgbox), 3}, {ER(msgbox), 4},  /* 141..144 */
    {ER(msgbox), 5},       {ER(msgbox), 6}, {ER(msgbox), 7}, {ER(msgbox), 8},  /* 145..148 */
    {ER(title), 1},        {ER(title), 2},  {ER(title), 3},  {ER(title), 4},   /* 149..152 */
    {ER(elevator), 1},     {ER(elevator), 2},                                  /* 153..154 */
    {ER(weather), 1},      {ER(weather), 2},                                   /* 155..156 */
    {ER(cielComputer), 1}, {ER(cielComputer), 2},                              /* 157..158 */
    {ER(cielComputer), 3}, {ER(cielComputer), 4},                              /* 159..160 */
    {ER(lifeEnergy), 1},   {ER(lifeEnergy), 2},                                /* 161..162 */
    {ER(crystal), 1},      {ER(crystal), 2},                                   /* 163..164 */
    {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0},                    /* 165..168 */
    {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0},                    /* 169..172 */
    {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0}, {ER_NONE, 0},                    /* 173..176 */
    {ER(extraLife), 1},    {ER(extraLife), 2},                                 /* 177..178 */
    {ER(bullet), 1},       {ER(bullet), 2},                                    /* 179..180 */
};
static_assert(ARRAY_COUNT(sApEReaderCosmetic) ==
              (AP_ITEM_EREADER_BYTE_LAST - AP_ITEM_EREADER_BYTE_FIRST) + 1);

bool32 ApServerChecked(u16 locationID) {
  if (locationID > AP_MAX_LOCATION_ID) {
    return FALSE;
  }
  return (gAp.serverChecked[locationID >> 3] & (1 << (locationID & 7))) != 0;
}

/* Returns TRUE when SystemSavedata changed and has to be saved. */
static bool32 ApGrantEReader(u16 apItemID) {
  if (apItemID >= AP_ITEM_EREADER_BIT_FIRST && apItemID <= AP_ITEM_EREADER_BIT_LAST) {
    u8 bit = sApEReaderModBit[apItemID - AP_ITEM_EREADER_BIT_FIRST];

    if (bit == AP_EREADER_NO_CARD) {
      return FALSE;
    }
    gSystemSavedata.flags[bit >> 3] |= (u8)(1 << (bit & 7));
    return TRUE;
  }
  if (apItemID >= AP_ITEM_EREADER_BYTE_FIRST && apItemID <= AP_ITEM_EREADER_BYTE_LAST) {
    const struct ApEReaderCosmetic* card = &sApEReaderCosmetic[apItemID - AP_ITEM_EREADER_BYTE_FIRST];

    if (card->offset == ER_NONE) {
      return FALSE;
    }
    ((u8*)&gSystemSavedata)[card->offset] = card->value;
    return TRUE;
  }
  return FALSE;
}

/*
  Give player one subtank slot. 0xFF is not owned, anything else is HP.
*/
static void ApGiveSubtankTo(u8* tank) {
  if (*tank == AP_SUBTANK_NONE) {
    *tank = 0;
  }
}

/*
  index is 0 or 1, the two in game pickup tanks AP owns. [2] and [3] come from elves(?)

  The same slot is held in three places: 
  the live player, the save, and zeroAsset (the game over rollback). Write all three.
*/
static void ApGiveSubtank(u8 index) {
  ApGiveSubtankTo(&gPlayers[0].unk_b4.status.subtankHP[index]);
  ApGiveSubtankTo(&gGameState.save.status.subtankHP[index]);
  ApGiveSubtankTo(&gGameState.save.zeroAsset.subtankHP[index]);
}

static void ApAddCrystalsTo(u16* ec, u16 amount) {
  u32 total = (u32)*ec + amount;

  *ec = (total > AP_EC_MAX) ? AP_EC_MAX : (u16)total;
}

/*
  Grant E-Crystals through the game's give crystal variable.

  Also set the save rollback crystal count in case of a game over, you still keep the added crystals.
*/
static void ApAddCrystals(u16 amount) {
  gECrystalGainAmount += amount;
  ApAddCrystalsTo(&gGameState.save.zeroAsset.EC, amount);
}

static u16 ApCountDisks(void);

/*
  Stage access.
*/
static void ApUnlockStage(u8 stageID) {
  u8* mask = &gGameState.save.unused_240[AP_UNLOCK_BYTE];
  u16 bit = (u16)(1 << (stageID - 1));

  mask[0] |= (u8)bit;
  mask[1] |= (u8)(bit >> 8);
}

/*
  The final stage has no access item.
  It opens on every other stage cleared while holding the seed's disk required amount.
*/
static bool32 ApFinalStageOpen(void) {
  if ((gGameState.save.playinfo.missionDones & AP_MISSION_DONES_ALL) != AP_MISSION_DONES_ALL) {
    return FALSE;
  }
  return ApCountDisks() >= gApSeedConfig.requiredDisks;
}

bool32 ApStageUnlocked(u8 stageID) {
  const u8* mask = &gGameState.save.unused_240[AP_UNLOCK_BYTE];

  if (stageID == AP_STAGE_FINAL) {
    return ApFinalStageOpen();
  }
  if ((stageID == STAGE_NONE) || (stageID > AP_STAGE_FINAL)) {
    return FALSE;
  }
  return (mask[(stageID - 1) >> 3] & (1 << ((stageID - 1) & 7))) != 0;
}

/*
  Per-stage best rank. A nibble each, stored as rank + 1 so an uncleared stage is not an F.
*/
static u8* ApRankByte(u8 stageID) {
  return &gGameState.save.unused_240[AP_RANK_BYTE + ((stageID - 1) >> 1)];
}

u8 ApStageBestRank(u8 stageID) {
  u8 packed;

  if ((stageID == STAGE_NONE) || (stageID > AP_STAGE_FINAL)) {
    return AP_RANK_NONE;
  }
  packed = *ApRankByte(stageID);
  return (u8)(((stageID - 1) & 1) ? (packed >> 4) : (packed & 0x0F));
}

/*
  Builds rank based on total averages of all completed levels. 
  So that the HUD displays properly and bosses use the correct attacks.
*/
static u8 ApAggregateRank(void) {
  u16 total = 0;
  u8 cleared = 0;
  u8 stageID;

  for (stageID = STAGE_SPACE_CRAFT; stageID <= AP_STAGE_FINAL; stageID++) {
    u8 packed = ApStageBestRank(stageID);

    if (packed != AP_RANK_NONE) {
      total = (u16)(total + (packed - 1));
      cleared++;
    }
  }
  if (cleared == 0) {
    return 0;
  }
  return (u8)(total / cleared);
}

/*
  Called from CalcMissionScore with the rank the results screen is about to print.
  Records it if it beats this stage's best, so it can be stored.
*/
u8 ApUpdateStageRank(u8 stageID, u8 missionRank) {
  u8* rankByte;
  u8 best;

  if ((stageID == STAGE_NONE) || (stageID > AP_STAGE_FINAL)) {
    return ApAggregateRank();
  }
  /* The A-rank fusion elf writes an A into the score directly, so set that as the highest levle achieved too. */
  if (gAp.rankElfUsed && (missionRank < RANK_A)) {
    missionRank = RANK_A;
  }

  best = ApStageBestRank(stageID);
  if ((u8)(missionRank + 1) > best) {
    rankByte = ApRankByte(stageID);
    if ((stageID - 1) & 1) {
      *rankByte = (u8)((*rankByte & 0x0F) | ((missionRank + 1) << 4));
    } else {
      *rankByte = (u8)((*rankByte & 0xF0) | (missionRank + 1));
    }
  }
  return ApAggregateRank();
}

/*
  Get the base script on returning from a stage.
*/
static u8 ApReturnBaseEntry(u8 clearedStage, u8 fallback) {
  u8* played = &gGameState.save.unused_240[AP_SCENE_BYTE];
  u8 bit;
  u8 entry;

  switch (clearedStage) {
    case STAGE_SPACE_CRAFT:
      bit = AP_SCENE_SPACE_CRAFT;
      entry = AP_BASE_ENTRY_SPACE_CRAFT;
      break;
    case STAGE_MISSILE_FACTORY:
      bit = AP_SCENE_MISSILE_FACTORY;
      entry = AP_BASE_ENTRY_MISSILE_FACTORY;
      break;
    case STAGE_AREA_X2:
      bit = AP_SCENE_AREA_X2;
      entry = AP_BASE_ENTRY_AREA_X2;
      break;
    default:
      return fallback;
  }

  if (*played & bit) {
    return fallback;
  }
  *played |= bit;
  return entry;
}

/*
  What to do on a level ending. Plays cutscenes or ends the game if needed.
*/
void ApEndRun(struct GameState* g) {
  bool32 missionRun = IS_MISSION && !ApInMissionRerun();
  bool32 bossDied = (gStageRun.missionStatus & MISSION_SUCCESS) != 0;
  u8 entry = missionRun ? AP_BASE_ENTRY_MISSION : AP_BASE_ENTRY_FREERUN;

  if ((gStageRun.id == STAGE_BASE) && ((gStageRun.checkpoint == AP_BASE_CHECKPOINT_LAUNCH) ||
                                       (gStageRun.checkpoint == AP_BASE_CHECKPOINT_SUBARCADIA))) {
    InitStageRun((u8)(g->save).stageID);
    SetGameMode(g, GAMEMODE(MAINGAME, PRE_OVERWORLD, 0, 0));
    return;
  }

  if (missionRun && bossDied && ((g->save).stageID == AP_STAGE_FINAL)) {
    SetGameMode(g, GAMEMODE(MAINGAME, UNLOCK_MINIGAME, 0, 0));
    return;
  }

  if (missionRun && bossDied) {
    entry = ApReturnBaseEntry((u8)(g->save).stageID, entry);
  }

  (g->save).stageID = STAGE_BASE;
  LoadStageRun(STAGE_BASE, entry);
  SetGameMode(g, GAMEMODE(MAINGAME, PRE_OVERWORLD, 0, 0));
}

void ApSetStoryFlag(u8 flag) {
  SET_FLAG(gCurStory.s.gameflags, flag);
  SET_FLAG(gGameState.save.story.gameflags, flag);
}

static void ApUnlockWeapon(u8 weapon) {
  struct ZeroStatus* live = &gPlayers[0].unk_b4.status;
  struct ZeroStatus* saved = &gGameState.save.status;

  live->unlockedWeapon |= (1 << weapon);
  saved->unlockedWeapon |= (1 << weapon);
  ApFixEquippedWeapons(live);
  ApFixEquippedWeapons(saved);
}

/*
  Longest chain each weapon has. The last three levels are e-reader attack increases
*/
static const u8 sApWeaponChainMax[WEAPON_KINDS] = {
    6,  // WEAPON_BUSTER: own, semi charge, full charge, ATK+1, ATK+2, ATK+3
    7,  // WEAPON_SABER:  own, 2nd slash, 3rd slash, charged slash, ATK+1, ATK+2, ATK+3
    5,  // WEAPON_ROD:    own, charged rod, ATK+1, ATK+2, ATK+3
    5,  // WEAPON_SHIELD: own, charged throw, ATK+1, ATK+2, ATK+3
};

// The ability given at progressive levels.
static const u8 sApWeaponAbilityMod[WEAPON_KINDS][3] = {
    {AP_MOD_BUSTER_SEMI, AP_MOD_BUSTER_FULL, AP_MOD_NONE},
    {AP_MOD_SABER_SLASH2, AP_MOD_SABER_SLASH3, AP_MOD_SABER_CHARGE},
    {AP_MOD_ROD_CHARGE, AP_MOD_NONE, AP_MOD_NONE},
    {AP_MOD_SHIELD_CHARGE, AP_MOD_NONE, AP_MOD_NONE},
};

// These are in the vanilla game.
static const u8 sApWeaponAtkMod[WEAPON_KINDS][3] = {
    {MOD_BUSTER_ATK1, MOD_BUSTER_ATK2, MOD_BUSTER_ATK3},
    {MOD_SABER_ATK1, MOD_SABER_ATK2, MOD_SABER_ATK3},
    {MOD_ROD_ATK1, MOD_ROD_ATK2, MOD_ROD_ATK3},
    {MOD_SHIELD_ATK1, MOD_SHIELD_ATK2, MOD_SHIELD_ATK3},
};
static u8 ApWeaponStepBit(u8 weapon, u8 step) {
  u8 firstAtkLevel = (u8)(sApWeaponChainMax[weapon] - 2);

  if (step < 2 || step > sApWeaponChainMax[weapon]) {
    return AP_MOD_NONE;
  }
  if (step < firstAtkLevel) {
    return sApWeaponAbilityMod[weapon][step - 2];
  }
  return sApWeaponAtkMod[weapon][step - firstAtkLevel];
}

// Returns TRUE when the bit was modified.
static bool32 ApSetModBit(u8 bit) {
  u8* slot = &gSystemSavedata.flags[bit >> 3];
  u8 mask = (u8)(1 << (bit & 7));

  if (*slot & mask) {
    return FALSE;
  }
  *slot |= mask;
  return TRUE;
}

bool32 ApHasWeaponAbility(u8 bit) {
  return (gSystemSavedata.flags[bit >> 3] & (1 << (bit & 7))) != 0;
}

u8 ApChargeTier(u8 weapon) {
  if (weapon == WEAPON_BUSTER) {
    if (ApHasWeaponAbility(AP_MOD_BUSTER_FULL)) {
      return FULL_CHARGE;
    }
    if (ApHasWeaponAbility(AP_MOD_BUSTER_SEMI)) {
      return SEMI_CHARGE;
    }
    return NO_CHARGE;
  }
  if (weapon == WEAPON_SABER) {
    return ApHasWeaponAbility(AP_MOD_SABER_CHARGE) ? FULL_CHARGE : NO_CHARGE;
  }
  if (weapon == WEAPON_ROD) {
    return ApHasWeaponAbility(AP_MOD_ROD_CHARGE) ? FULL_CHARGE : NO_CHARGE;
  }
  return ApHasWeaponAbility(AP_MOD_SHIELD_CHARGE) ? FULL_CHARGE : NO_CHARGE;
}


// Returns TRUE when SystemSavedata changed.
static bool32 ApSetWeaponLevel(u8 weapon, u8 level) {
  bool32 changed = FALSE;
  u8 step;

  if (weapon >= WEAPON_KINDS || level == 0 || level > sApWeaponChainMax[weapon]) {
    return FALSE;
  }
  ApUnlockWeapon(weapon);

  for (step = 2; step <= level; step++) {
    u8 bit = ApWeaponStepBit(weapon, step);

    if (bit != AP_MOD_NONE && ApSetModBit(bit)) {
      changed = TRUE;
    }
  }
  return changed;
}

/*
  0 when it is not owned at all, 1 for bare ownership and so on
*/
u8 ApWeaponLevel(u8 weapon) {
  u8 step;

  if (weapon >= WEAPON_KINDS) {
    return 0;
  }
  if (!(gPlayers[0].unk_b4.status.unlockedWeapon & (1 << weapon))) {
    return 0;
  }
  for (step = sApWeaponChainMax[weapon]; step >= 2; step--) {
    u8 bit = ApWeaponStepBit(weapon, step);

    if (bit != AP_MOD_NONE && ApHasWeaponAbility(bit)) {
      return step;
    }
  }
  return 1;
}

/*
  The pause screen's weapon level row on the description line
*/
void ApPrintWeaponStars(u8 weapon) {
  u8 level;
  u8 max;
  u8 i;

  if (weapon >= WEAPON_KINDS) {
    return;
  }
  level = ApWeaponLevel(weapon);
  max = sApWeaponChainMax[weapon];

  for (i = 0; i < max; i++) {
    sApWeaponStars[i] = (char_t)((i < level) ? AP_CHAR_STAR_FULL : AP_CHAR_STAR_EMPTY);
  }
  sApWeaponStars[max] = AP_CHAR_END;

  PrintString(sApWeaponStars, (u32)(AP_STARS_RIGHT_X - max), AP_STARS_Y);
}

/* Returns TRUE when SystemSavedata changed and has to be saved. */
static bool32 ApGrantItem(u16 apItemID) {
  if (apItemID >= AP_ITEM_DISK_FIRST && apItemID <= AP_ITEM_DISK_LAST) {
    u8 diskID = (u8)(apItemID - AP_ITEM_DISK_FIRST);
    
    UNLOCK_DISK(gGameState.save.savedDisk, diskID);
    /* 111 to 180 also have an e-Reader change. */
    return ApGrantEReader(apItemID);
  }

  if (apItemID == AP_ITEM_SUBTANK_1 || apItemID == AP_ITEM_SUBTANK_2) {
    ApGiveSubtank((u8)(apItemID - AP_ITEM_SUBTANK_1));
    return FALSE;
  }

  /*
    Progressive weapons. The client sends the level.
  */
  if (apItemID >= AP_ITEM_WEAPON_LEVEL_FIRST && apItemID <= AP_ITEM_WEAPON_LEVEL_LAST) {
    u16 offset = (u16)(apItemID - AP_ITEM_WEAPON_LEVEL_FIRST);

    return ApSetWeaponLevel((u8)(offset / AP_ITEM_CODES_PER_WEAPON),
                            (u8)(offset % AP_ITEM_CODES_PER_WEAPON));
  }

  if (apItemID >= AP_ITEM_STAGE_ACCESS_FIRST && apItemID <= AP_ITEM_STAGE_ACCESS_LAST) {
    ApUnlockStage((u8)(apItemID - AP_ITEM_STAGE_ACCESS_FIRST + STAGE_SPACE_CRAFT));
    return FALSE;
  }

  if (apItemID == AP_ITEM_STORY_MID) {
    ApSetStoryFlag(FLAG_FIRST4_DONE);
    return FALSE;
  }
  if (apItemID == AP_ITEM_STORY_LATE) {
    ApSetStoryFlag(FLAG_LATER4_DONE);
    return FALSE;
  }

  if (apItemID >= AP_ITEM_BODY_CHIP_FIRST && apItemID <= AP_ITEM_BODY_CHIP_LAST) {
    u8 chip = sApBodyChips[apItemID - AP_ITEM_BODY_CHIP_FIRST];

    gPlayers[0].unk_b4.status.unlockedBody |= (1 << chip);
    gGameState.save.status.unlockedBody |= (1 << chip);
    return FALSE;
  }
  if (apItemID >= AP_ITEM_FOOT_CHIP_FIRST && apItemID <= AP_ITEM_FOOT_CHIP_LAST) {
    u8 chip = sApFootChips[apItemID - AP_ITEM_FOOT_CHIP_FIRST];

    gPlayers[0].unk_b4.status.unlockedFoot |= (1 << chip);
    gGameState.save.status.unlockedFoot |= (1 << chip);
    return FALSE;
  }
  if (apItemID >= AP_ITEM_EXSKILL_FIRST && apItemID <= AP_ITEM_EXSKILL_LAST) {
    u8 skill = (u8)(apItemID - AP_ITEM_EXSKILL_FIRST);

    gPlayers[0].unk_b4.status.unlockedExSkill |= (1 << skill);
    gGameState.save.status.unlockedExSkill |= (1 << skill);
    return FALSE;
  }

  if (apItemID == AP_ITEM_CRYSTAL_100) {
    ApAddCrystals(AP_CRYSTAL_100_AMOUNT);
    return FALSE;
  }

  return FALSE;
}

/*
  The Sunken Library's four data files, by disk number. 
  These normally get cleared by the game when you start it, since the mission's goal is to collect them.
*/
static const u8 sApSunkenDisks[AP_SUNKEN_COUNT] = {10, 16, 17, 18};

static u8 ApSunkenMask(u16 diskNo) {
  u8 i;

  for (i = 0; i < AP_SUNKEN_COUNT; i++) {
    if (sApSunkenDisks[i] == diskNo) {
      return (u8)(1 << i);
    }
  }
  return 0;
}

static bool8 ApSunkenDiskFound(u16 diskNo) {
  u8 mask = ApSunkenMask(diskNo);
  return (mask != 0) && ((gGameState.save.unused_240[AP_SUNKEN_BYTE] & mask) != 0);
}

/*
  How many AP disks the player owns. Checked through only the lower nibble of savedDisk.
*/
static u16 ApCountDisks(void) {
  const u8* disks = gGameState.save.savedDisk;
  u16 count = 0;
  u8 i;

  for (i = 0; i < AP_DISK_BYTES; i++) {
    u8 bits = (u8)(disks[i] & 0x0F);

    while (bits != 0) {
      count = (u16)(count + (bits & 1));
      bits >>= 1;
    }
  }
  return count;
}

/*
  How many of a stage's disks have been found, over how many it holds.

  The Sunken Library's four data files are counted out of AP's own record, since the stage wipes
  them from save.disk every time it is entered.
*/
u8 ApDisksInStage(u8 stageID) {
  const u8* disks = gGameState.save.disk;
  u8 count = 0;
  u16 disk;

  for (disk = 0; disk < ARRAY_COUNT(sApDiskStage); disk++) {
    if (sApDiskStage[disk] == stageID) {
      if ((disks[disk >> 2] & (1 << (disk & 3))) || ApSunkenDiskFound((u16)(disk + 1))) {
        count++;
      }
    }
  }
  return count;
}

u8 ApDiskTotalInStage(u8 stageID) {
  if (stageID >= ARRAY_COUNT(sApDiskTotal)) {
    return 0;
  }
  return sApDiskTotal[stageID];
}

static u16 ApSavedApplied(void) {
  return (u16)(gGameState.save.unused_240[AP_APPLIED_BYTE] |
               (gGameState.save.unused_240[AP_APPLIED_BYTE + 1] << 8));
}
static void ApSetSavedApplied(u16 count) {
  gGameState.save.unused_240[AP_APPLIED_BYTE] = (u8)count;
  gGameState.save.unused_240[AP_APPLIED_BYTE + 1] = (u8)(count >> 8);
}

/*
  Fix for Boss portraits (or anything else later) stealing the palette used by the AP item pop up sprites.
*/
#define AP_IN_GAMEPLAY(mode) (((mode)[0] == 0) && ((mode)[1] == 4))

EWRAM_DATA static bool8 sApWasInGameplay = FALSE;

static void ApKeepPickupPalette(void) {
  bool8 now = (bool8)AP_IN_GAMEPLAY(gGameState.mode);

  if (now && !sApWasInGameplay) {
    LOAD_STATIC_GRAPHIC(SM176_RESULT_DISK + gSystemSavedata.disk);
  }
  sApWasInGameplay = now;
}

void ApInit(void) {
  u8 i;

  gAp.inboxWriteIndex = 0;
  gAp.inboxReadIndex = 0;
  gAp.itemsApplied = 0;
  gAp.rankElfUsed = FALSE;
  gAp.disksOwned = 0;
  gAp.deathCount = 0;
  gAp.killRequest = AP_KILL_IDLE;
  gAp.canAcceptItems = FALSE;
  sApRerunRequest = 0;
  sApRerunStage = 0;

  for (i = 0; i < AP_CHECKED_LOCATION_BYTES; i++) {
    gAp.checkedLocations[i] = 0;
    gAp.serverChecked[i] = 0;
  }

  gAp.version = AP_VERSION;
  gAp.ready = AP_READY;
}

static void ApRebuildCheckedLocations(void);
static void ApCheckSubBossKilled(void);
static void ApCheckVolcanoMidBossRoom(void);

/*
  A little icon that floats over Zero's head when Archipelago hands him something.

  Uses VFX_EMOTION_BUBBLE. Early WIP
*/
#define AP_POPUP_OFFSET_Y PIXEL(-40)

/*
  Which icon an item gets
  AP_ICON_NONE subtanks and crystals since they are drawn using vanilla sprites.
*/
#define AP_ICON_NONE 0xFF

static u8 ApIconOf(u16 apItemID) {
  if (apItemID >= AP_ITEM_DISK_FIRST && apItemID <= AP_ITEM_DISK_LAST) {
    return AP_ICON_DISK;
  }
  if (apItemID >= AP_ITEM_WEAPON_LEVEL_FIRST && apItemID <= AP_ITEM_WEAPON_LEVEL_LAST) {
    return (u8)(AP_ICON_BUSTER +
                ((apItemID - AP_ITEM_WEAPON_LEVEL_FIRST) / AP_ITEM_CODES_PER_WEAPON));
  }
  if (apItemID >= AP_ITEM_BODY_CHIP_FIRST && apItemID <= AP_ITEM_BODY_CHIP_LAST) {
    return (u8)(AP_ICON_BODY_ICE + (apItemID - AP_ITEM_BODY_CHIP_FIRST));
  }
  if (apItemID >= AP_ITEM_FOOT_CHIP_FIRST && apItemID <= AP_ITEM_FOOT_CHIP_LAST) {
    return (u8)(AP_ICON_FOOT_SPIKE + (apItemID - AP_ITEM_FOOT_CHIP_FIRST));
  }
  if (apItemID >= AP_ITEM_EXSKILL_FIRST && apItemID <= AP_ITEM_EXSKILL_LAST) {
    return (u8)(AP_ICON_EXSKILL_0 + (apItemID - AP_ITEM_EXSKILL_FIRST));
  }
  if (apItemID >= AP_ITEM_STAGE_ACCESS_FIRST && apItemID <= AP_ITEM_STAGE_ACCESS_LAST) {
    return (u8)(AP_ICON_STAGE_1 + (apItemID - AP_ITEM_STAGE_ACCESS_FIRST));
  }
  if (apItemID == AP_ITEM_STORY_MID || apItemID == AP_ITEM_STORY_LATE) {
    return AP_ICON_STORY;
  }
  return AP_ICON_NONE;
}

/*
  Figure out where to place the sprite based on stage and area of that stage
*/
static u16 ApIconWindow(void) {
  if ((u32)gStageRun.id >= AP_ICON_STAGES || (u32)gSpawnManager.area >= AP_ICON_AREAS) {
    return 0;
  }
  return gApIconTile[gStageRun.id][gSpawnManager.area];
}

static void ApDrawItemIcon(struct Entity* p) {
  u16 tile = ApIconWindow();
  u8 icon = p->work[1];

  if (tile == 0) {
    return;  /* No free tiles, cant draw anything */
  }
  MemCopy32(gApIconTiles[icon], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)),
            sizeof(gApIconTiles[icon]));

  (p->spr).sprites = (struct MetaspriteHeader*)gApIconSprite.hdr;
  (p->spr).spriteIdx = 0;
  (p->spr).oam.tileNum = tile;
  (p->spr).oam.paletteNum = AP_ICON_PAL;
}

/*
  Which icon the popup shows. WIP.
*/
static motion_t ApItemPopupMotion(u16 apItemID) {
  if (apItemID == AP_ITEM_CRYSTAL_100) {
    return MOTION((SM170_ECRYSTAL + gSystemSavedata.crystal), 0);
  }
  if (apItemID == AP_ITEM_SUBTANK_1 || apItemID == AP_ITEM_SUBTANK_2) {
    /*   # TODO get a sprite for subtank since it still uses a life pickup sprite. */
    return MOTION((SM167_LIFE_ENERGY + gSystemSavedata.lifeEnergy), 0);
  }
  /* If nothing else was found. */
  return MOTION(SM003_EMOTION_BUBBLE, 0);
}

#define AP_POPUP_LIFE 96            /* frames on screen */
#define AP_POPUP_FADE 48            /* the the frame it should flciker */
#define AP_POPUP_RISE 0x60          /* sub-pixels per frame; PIXEL(1) is 0x100 */
#define AP_POPUP_RISE_MAX PIXEL(16) /* how far above zero's head to rise */

static void ApItemPopupUpdate(struct Entity* p) {
  u8 left;

  if (p->work[1] == AP_ICON_NONE) {
    UpdateSpriteAnimation(p);
  } else {
    ApDrawItemIcon(p);
  }

  if (p->work[3] < (AP_POPUP_RISE_MAX / AP_POPUP_RISE)) {
    p->work[3]++;
  }
  if (gGameState.z2 != NULL) {
    (p->coord).x = (gGameState.z2->s).coord.x;
    (p->coord).y = (gGameState.z2->s).coord.y + AP_POPUP_OFFSET_Y - (p->work[3] * AP_POPUP_RISE);
  }

  left = --p->work[2];
  if (left == 0) {
    p->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);  /* VFX_EMOTION_BUBBLE's slot is DeleteVFX */
    return;
  }
  if (left < AP_POPUP_FADE) {
    if ((left & 3) < ((left * 4) / AP_POPUP_FADE)) {
      p->flags |= DISPLAY;
    } else {
      p->flags &= ~DISPLAY;
    }
  }
}

static void ApShowItemPopup(u16 apItemID) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);

  if (p == NULL) {
    return;  // the VFX pool is full
  }
  INIT_VFX_ROUTINE(p, VFX_EMOTION_BUBBLE);
  (p->coord).x = (gGameState.z2->s).coord.x;
  (p->coord).y = (gGameState.z2->s).coord.y + AP_POPUP_OFFSET_Y;
  p->work[0] = 0;
  p->work[1] = ApIconWindow() ? ApIconOf(apItemID) : AP_ICON_NONE;
  p->work[3] = 0;  /* how far it has risen above his head */
  InitNonAffineMotion(p);
  if (p->work[1] == AP_ICON_NONE) {
    SetSpriteAnimation(p, ApItemPopupMotion(apItemID));
  } else {
    ApDrawItemIcon(p);
  }
  p->flags |= DISPLAY;
  (p->spr).oam.priority = 0;
  p->work[2] = AP_POPUP_LIFE;
  p->onUpdate = (void*)ApItemPopupUpdate;

  PlaySound(SE_NOTIFICATION);
}

/*
  SELECT cycles the sub weapon. WIP this will soon be a weapon wheel!

  Skips whatever is in the main weapon slot
*/
static void ApCycleSubWeapon(void) {
  struct ZeroStatus* status;
  u8 unlocked;
  u8 main;
  u8 i;

  if (ApInDemo()) {
    return;
  }
  if (gGameState.mode[0] != MAINGAME || gGameState.mode[1] != OVERWORLD) {
    return;
  }
  if (!(gJoypad[0].pressed & SELECT_BUTTON)) {
    return;
  }
  /* SELECT+START+A+B does a soft reset, so skip out of this if the player is also pressing start.
  Who even knew this was a mechanic? */
  if (gJoypad[0].input & START_BUTTON) {
    return;
  }
  /* For cutscenes and other stuff. */
  if ((gGameState.z2->input).raw & INPUT_DISABLED) {
    return;
  }

  status = &(&gGameState.z2->unk_b4)->status;
  unlocked = status->unlockedWeapon;
  main = status->weapons[0];

  for (i = 1; i < WEAPON_KINDS; i++) {
    u8 next = (u8)((status->weapons[1] + i) & 3);

    if ((unlocked & (1 << next)) && (next != main)) {
      status->weapons[1] = next;
      PlaySound(SE_CURSOR);
      return;
    }
  }
}

/*
  Simplfies the requirements for Harpuias scene in the maintenence bay so it loads easier in
  Archipelago's conditions.
*/
static void ApSetHarpuiaScene(void) {
  if (gStageRun.id != STAGE_BASE) {
    return;
  }
  if (gStageRun.stageEventPhase != AP_BASE_EVENT_IDLE) {
    return;
  }
  if (gStageRun.vm.active & VM_ACTIVE) {
    return;
  }
  if (!FLAG(gCurStory.s.gameflags, FLAG_LATER4_DONE)) {
    return;
  }
  if (FLAG(gCurStory.s.gameflags, FLAG_BRAIN_CONTROL)) {
    return;
  }
  gStageRun.stageEventPhase = AP_BASE_EVENT_HARPUIA;
}

/*
  Called once per frame from Process_Game.
*/
void ApUpdate(void) {
  bool32 needSaveSystemData = FALSE;
  bool32 canAcceptItems;
  bool32 granted = FALSE;
  u16 lastGranted = 0;

  if (gAp.ready != AP_READY) {
    ApInit();
  }
  ApKeepPickupPalette();
  canAcceptItems = ApCanAcceptItems();
  gAp.canAcceptItems = (u8)(canAcceptItems != 0);
  ApCycleSubWeapon();

  /*
    How many items have been applied.
    gAp.itemsApplied and unused_240 are written together,
    They only desync when theres a a savestate, a soft reset, a game over, or an older save file.
  */
  gAp.itemsApplied = ApSavedApplied();
  gAp.disksOwned = ApCountDisks();
  ApRebuildCheckedLocations();
  ApCheckSubBossKilled();
  ApCheckVolcanoMidBossRoom();
  ApSetHarpuiaScene();

  if (!canAcceptItems) {
    return;
  }

  if (gAp.killRequest == AP_KILL_REQUESTED) {
    gGameState.z2->body.hp = 0;
    gAp.killRequest = AP_KILL_APPLIED;
  }

  while (gAp.inboxReadIndex != (u8)(gAp.inboxWriteIndex & AP_ITEM_INBOX_MASK)) {
    lastGranted = gAp.itemInbox[gAp.inboxReadIndex & AP_ITEM_INBOX_MASK];
    if (ApGrantItem(lastGranted)) {
      needSaveSystemData = TRUE;
    }
    granted = TRUE;
    gAp.inboxReadIndex = (gAp.inboxReadIndex + 1) & AP_ITEM_INBOX_MASK;
    gAp.itemsApplied++;
    ApSetSavedApplied(gAp.itemsApplied);
  }
  
  if (granted) {
    ApShowItemPopup(lastGranted);
  }

  if (needSaveSystemData) {
    SaveSystemData();
  }
}

static_assert(AP_STAGE_COUNT == STAGE_COUNT);

/*
  Every static 1-UP, in location order

  x is the spawn point's tile x, 
  basically its coordinates so the game can send the correct check based on where the life pickup is.
*/
struct ApExLifePlace {
  u8 stageID;
  u16 x;
};

static const struct ApExLifePlace sApExLifePlaces[AP_EXLIFE_COUNT] = {
    {STAGE_OCEAN, 272},           /* 231 */
    {STAGE_OLD_RESIDENTIAL, 141}, /* 232 */
    {STAGE_OLD_RESIDENTIAL, 183}, /* 233 */
    {STAGE_MISSILE_FACTORY, 379}, /* 234 */
    {STAGE_ANATRE_FOREST, 35},    /* 235 */
    {STAGE_E_FACILITY, 625},      /* 236 */
    {STAGE_SNOWY_PLAINS, 573},    /* 237 */
    {STAGE_GIANT_ELEVATOR, 72},   /* 238 */
    {STAGE_SUB_ARCADIA, 67},      /* 239 */
    {STAGE_BASE, 26},             /* 240 */
};

/* 0 when the stage places no 1-UP. */
u16 ApExLifeLocation(u8 stageID, s32 coordX) {
  u16 px = (u16)(coordX >> 12);
  u8 nearestPlace = AP_EXLIFE_COUNT;  // AP_EXLIFE_COUNT means the stage places no 1-UP
  u16 nearestDist = 0xFFFF;
  u8 i;

  for (i = 0; i < AP_EXLIFE_COUNT; i++) {
    u16 dist;

    if (sApExLifePlaces[i].stageID != stageID) {
      continue;
    }
    dist = (u16)(px > sApExLifePlaces[i].x ? px - sApExLifePlaces[i].x : sApExLifePlaces[i].x - px);
    if (dist < nearestDist) {
      nearestDist = dist;
      nearestPlace = i;
    }
  }

  if (nearestPlace == AP_EXLIFE_COUNT) {
    return 0;
  }
  return (u16)(AP_LOC_EXLIFE_FIRST + nearestPlace);
}

void ApMarkExLifeCollected(u8 stageID, s32 coordX) {
  u16 loc = ApExLifeLocation(stageID, coordX);

  if (loc != 0) {
    ApMarkLocationChecked(loc);
  }
}

/*
  Sub-bosses. To be used as location checks.

  x is the spawn's x coordinate, used for the two reactor cores in the energy facility.
*/
struct ApSubBossPlace {
  u8 stageID;
  u8 bossID;
  u16 x;
};

static const struct ApSubBossPlace sApSubBossPlaces[AP_SUBBOSS_COUNT] = {
    {STAGE_REPAIR_FACTORY, BOSS_BEE_SERVER, 247},         /* 242 */
    {STAGE_OCEAN, BOSS_PANTHEON_AQUA_MOD, 427},           /* 243 */
    {STAGE_OLD_RESIDENTIAL, BOSS_MEGAMILPA, 292},         /* 244 */
    {STAGE_TWILIGHT_DESERT, BOSS_WORMER, 283},            /* 245 */
    {STAGE_SNOWY_PLAINS, BOSS_WORMER, 517},               /* 246 */
    {STAGE_E_FACILITY, BOSS_LOCOMO_IF, 352},              /* 247 */
    {STAGE_E_FACILITY, BOSS_REACTOR_CORE, 232},           /* 248 */
    {STAGE_E_FACILITY, BOSS_REACTOR_CORE, 532},           /* 249 */
    {STAGE_GIANT_ELEVATOR, BOSS_SPEAROOK, 244},           /* 250 */
    {STAGE_SUB_ARCADIA, BOSS_PHANTOM, 124},               /* 251 */
};

u16 ApSubBossLocation(u8 stageID, u8 bossID, s32 coordX) {
  u16 px = (u16)(coordX >> 12);
  u8 nearest = AP_SUBBOSS_COUNT;
  u16 nearestDist = 0xFFFF;
  u8 i;

  for (i = 0; i < AP_SUBBOSS_COUNT; i++) {
    u16 dist;

    if (sApSubBossPlaces[i].stageID != stageID || sApSubBossPlaces[i].bossID != bossID) {
      continue;
    }
    dist = (u16)(px > sApSubBossPlaces[i].x ? px - sApSubBossPlaces[i].x : sApSubBossPlaces[i].x - px);
    if (dist < nearestDist) {
      nearestDist = dist;
      nearest = i;
    }
  }

  if (nearest == AP_SUBBOSS_COUNT) {
    return 0;
  }
  return (u16)(AP_LOC_SUBBOSS_FIRST + nearest);
}

static void ApCheckSubBossKilled(void) {
  const struct Entity* boss = gStageRun.vm.entities[1].entity;

  if (boss == NULL || boss->kind != ENTITY_BOSS) {
    return;
  }
  if (!isKilled((struct Entity*)boss)) {
    return;
  }
  ApMarkLocationChecked(ApSubBossLocation(gStageRun.id, boss->id, boss->coord.x));
}

/*
  Use checkpoints to send the location for clearing the midboss on this stage.
  For some reason, this stage's boss is not treated as a midboss in the code.
*/
static void ApCheckVolcanoMidBossRoom(void) {
  if (gStageRun.id != STAGE_VOLCANO) {
    return;
  }
  if (gStageRun.checkpoint < AP_VOLCANO_ROOM_CLEARED_CHECKPOINT) {
    return;
  }
  ApMarkLocationChecked(AP_LOC_VOLCANO_MIDBOSS_ROOM);
}

/*
  Called wherever the game already knows a check happened
  getDiskInStageRun(), the subtank pickup, mission complete, an NPC reward.
*/
void ApMarkLocationChecked(u16 locationID) {
  if (ApInDemo()) {
    return;
  }
  if (locationID > AP_MAX_LOCATION_ID) {
    return;
  }
  gAp.checkedLocations[locationID >> 3] |= (1 << (locationID & 7));
  gGameState.save.unused_240[AP_SUNKEN_BYTE] |= ApSunkenMask(locationID);
}

/*
  What clearing a stage should give you: 
  the completion check, (currently an AP loc but will probably be removed later) 
  the chip that stage used to award (AP Loc),
  the A+ rank check (AP Loc). 
  0 means the stage has none of that one.
*/
struct ApStageClear {
  u16 clear;
  u16 chip;
  u16 rank;
};

static const struct ApStageClear sApStageClears[AP_STAGE_COUNT] = {
    [STAGE_SPACE_CRAFT] = {181, 0, 206},
    [STAGE_VOLCANO] = {182, 199, 207},
    [STAGE_OCEAN] = {183, 197, 208},
    [STAGE_REPAIR_FACTORY] = {184, 198, 209},
    [STAGE_OLD_RESIDENTIAL] = {185, 200, 210},
    [STAGE_MISSILE_FACTORY] = {186, 0, 211},
    [STAGE_TWILIGHT_DESERT] = {187, 0, 212},
    [STAGE_ANATRE_FOREST] = {188, 0, 213},
    [STAGE_ICE_BASE] = {189, 0, 214},
    [STAGE_AREA_X2] = {190, 203, 215},
    [STAGE_E_FACILITY] = {191, 204, 216},
    [STAGE_SNOWY_PLAINS] = {192, 202, 217},
    [STAGE_SUNKEN_LIBRARY] = {193, 205, 218},
    [STAGE_GIANT_ELEVATOR] = {194, 201, 219},
    [STAGE_SUB_ARCADIA] = {195, 0, 220},
    [STAGE_WEILS_LABO] = {196, 0, 0},
};

static void ApRebuildCheckedLocations(void) {
  const u8* disks = gGameState.save.disk;
  u32 missionDones = gGameState.save.playinfo.missionDones;
  u8 taken = gGameState.save.unused_240[AP_TAKEN_BYTE];
  u8 i;

  for (i = 0; i < AP_DISK_BYTES; i++) {
    u8 found = (u8)(disks[i] & 0x0F);
    u8 n;

    for (n = 0; n < 4; n++) {
      if (found & (1 << n)) {
        ApMarkLocationChecked((u16)((i * 4) + n + 1));
      }
    }
  }

  for (i = 0; i < AP_STAGE_COUNT; i++) {
    if (missionDones & (1 << i)) {
      if (sApStageClears[i].clear != 0) {
        ApMarkLocationChecked(sApStageClears[i].clear);
      }
      if (sApStageClears[i].chip != 0) {
        ApMarkLocationChecked(sApStageClears[i].chip);
      }
    }
  }

  for (i = 0; i < AP_SUNKEN_COUNT; i++) {
    if (gGameState.save.unused_240[AP_SUNKEN_BYTE] & (1 << i)) {
      ApMarkLocationChecked(sApSunkenDisks[i]);
    }
  }

  if (taken & AP_TAKEN_SUBTANK1) {
    ApMarkLocationChecked(AP_LOC_SUBTANK_1);
  }
  if (taken & AP_TAKEN_SUBTANK2) {
    ApMarkLocationChecked(AP_LOC_SUBTANK_2);
  }
}

void ApRequestMissionRerun(u8 stageID) {
  sApRerunRequest = (u8)(stageID + 1);
}

bool32 ApTakeMissionRerun(u8 stageID) {
  u8 want = (u8)(stageID + 1);

  if (sApRerunRequest == want) {
    sApRerunStage = want;
  } else if (sApRerunStage != want) {
    sApRerunStage = 0;
  }
  sApRerunRequest = 0;
  return sApRerunStage != 0;
}

bool32 ApInMissionRerun(void) {
  return sApRerunStage != 0;
}

/*
  The A rank fusion elf writes gScore.total->rank which isn't what AP checks, this is written instead.
*/
void ApSetRankElf(void) {
  gAp.rankElfUsed = TRUE;
}

// Called from ResetMissionScore
void ApResetMissionFlags(void) {
  gAp.rankElfUsed = FALSE;
  if (gAp.killRequest == AP_KILL_APPLIED) {
    gAp.killRequest = AP_KILL_IDLE;
  }
}

void ApOnZeroDied(void) {
  if (ApInDemo()) {
    return;
  }
  if (gAp.killRequest == AP_KILL_APPLIED) {
    gAp.killRequest = AP_KILL_IDLE;
    return;
  }
  gAp.deathCount++;
}

void ApMarkStageCleared(void) {
  const struct ApStageClear* stage;

  if (ApInDemo() || (u32)gStageRun.id >= AP_STAGE_COUNT) {
    return;
  }

  stage = &sApStageClears[gStageRun.id];
  if (stage->clear == 0) {
    return;
  }

  ApMarkLocationChecked(stage->clear);
  if (stage->chip != 0) {
    ApMarkLocationChecked(stage->chip);
  }
  if ((stage->rank != 0) &&
      (gApSeedConfig.easyExSkill || gAp.rankElfUsed ||
       (gScore.resultScore > AP_RANK_A_PLUS_SCORE))) {
    ApMarkLocationChecked(stage->rank);
  }
  gAp.rankElfUsed = FALSE;
}

/*
  Which AP location an NPC conversation counts as, based on the text just shown.

  Every text a mapped NPC can say after that point counts as the check.

*/
struct ApNpcDialogue {
  u16 textID;
  u16 locationID;
};

/*
  WIP This will eventually be replaced when I can make all NPCs say their dialogue in order.
*/
static const struct ApNpcDialogue sApNpcDialogues[] = {
    {0x241, 107}, {0x242, 107}, {0x243, 107}, {0x2D3, 107},                // Andrew
    {0x247, 116}, {0x248, 116}, {0x249, 116}, {0x24A, 116},                // Alouette
    {0x24E, 169}, {0x24F, 169}, {0x250, 169}, {0x251, 169},                // Hibou
    {0x253, 175}, {0x254, 175}, {0x255, 175}, {0x256, 175}, {0x257, 175},
    {0x258, 175},                                                          // Menart
    {0x259, 167}, {0x25A, 167}, {0x25B, 167}, {0x25C, 167}, {0x25E, 167},  // Rocinolle
    {0x25D, 44},                                                           // Rocinolle, elf disk
    {0x26E, 173}, {0x26F, 173}, {0x270, 173}, {0x271, 173}, {0x272, 173},  // Hirondelle
    {0x281, 174}, {0x282, 174}, {0x283, 174}, {0x284, 174}, {0x285, 174},  // Doigt
    {0x2A6, 58},  {0x2A7, 58},  {0x2A9, 58},  {0x2AB, 58},                 // Soldier in right tower
    {0x2B1, 23},  {0x2B2, 23},  {0x2B3, 23},                               // Soldier in room 02D
    {0x2CF, 107}, {0x2D0, 107}, {0x2D1, 107}, {0x2D2, 107},                // Andrew, young (from ereader)
};

/*
  Called once per finished conversation, from FUN_080d98e8. 
*/
void ApMarkNpcDialogueChecked(TextID textID) {
  u32 i;
  for (i = 0; i < ARRAY_COUNT(sApNpcDialogues); i++) {
    if (sApNpcDialogues[i].textID == textID) {
      ApMarkLocationChecked(sApNpcDialogues[i].locationID);
      return;
    }
  }
}
static void (*const pSwitchProcess)(bool32 b) = SwitchProcess;

static void ApFrameHookImpl(bool32 b) {
  ApUpdate();
  pSwitchProcess(b);
}

/*
  Needed due to ROM expansion
*/
void (*const gApInitFn)(void) = ApInit;
void (*const gApUpdateFn)(void) = ApUpdate;
void (*const gApMarkLocationCheckedFn)(u16 locationID) = ApMarkLocationChecked;
void (*const gApMarkExLifeCollectedFn)(u8 stageID, s32 coordX) = ApMarkExLifeCollected;
void (*const gApMarkNpcDialogueCheckedFn)(TextID textID) = ApMarkNpcDialogueChecked;
void (*const gApMarkStageClearedFn)(void) = ApMarkStageCleared;
void (*const gApSetRankElfFn)(void) = ApSetRankElf;
void (*const gApResetMissionFlagsFn)(void) = ApResetMissionFlags;
void (*const gApOnZeroDiedFn)(void) = ApOnZeroDied;
void (*const gApApplyStartingWeaponsFn)(struct ZeroStatus* status) = ApApplyStartingWeapons;
void (*const gApFixEquippedWeaponsFn)(struct ZeroStatus* status) = ApFixEquippedWeapons;
void (*const gApRequestMissionRerunFn)(u8 stageID) = ApRequestMissionRerun;
bool32 (*const gApTakeMissionRerunFn)(u8 stageID) = ApTakeMissionRerun;
bool32 (*const gApInMissionRerunFn)(void) = ApInMissionRerun;
u8 (*const gApUpdateStageRankFn)(u8 stageID, u8 missionRank) = ApUpdateStageRank;
void (*const gApEndRunFn)(struct GameState* g) = ApEndRun;
bool32 (*const gApHasWeaponAbilityFn)(u8 bit) = ApHasWeaponAbility;
u8 (*const gApChargeTierFn)(u8 weapon) = ApChargeTier;
void (*const gApPrintWeaponStarsFn)(u8 weapon) = ApPrintWeaponStars;
void (*const gApFrameHookFn)(bool32 b) = ApFrameHookImpl;

#endif /* AP */
