#ifndef GUARD_RMZ3_SYSTEM_SAVE_H
#define GUARD_RMZ3_SYSTEM_SAVE_H

#include "constants/constants.h"
#include "gba/gba.h"
#include "types.h"

enum SramHealth {
  SRAM_NEUTRAL = 0,
  DATA_OK = 0,
  DATA_BROKEN = 0xFFFF,
};

struct SaveSlotInfo {
  bool8 ok[SAVE_SLOT + 1];                 // 0x0200_05f8
  u32 ALIGNED(4) playtime[SAVE_SLOT + 1];  // 0x0200_0600
  u32 ALIGNED(4) rank[SAVE_SLOT];          // 0x0200_0618
  u8 ALIGNED(4) lap[SAVE_SLOT + 1];        // 0x0200_062c 周回数
  u8 ALIGNED(4) gamemode[SAVE_SLOT + 1];   // 0x0200_0634
  u32 _;
};  // 72 bytes

struct SaveHeader {
  u32 INTI;  // マジックナンバ INTI
  u32 checksum;
  u32 size;
  u8 unk_c;  // 0x0B で固定
  u8 pad_d;
  u8 idx;  // セーブデータの番号(0..4)
  u8 unk_f;
};  // 16 bytes

/**
 * @note ミニゲームの時はここにハイスコアなどのセーブデータが保存される
 * @note 0x020021b0 (En: 0x02002430)
 */
struct SystemSavedataManager {
  u8 flags[7];  // bitfield * 7 = 56 flags
  u8 mods[16];  // 128bits (mod.h)
  u8 unk_17;

  /*
    0x00: Locked
    0x31: Unlocked
  */
  u8 hardmodeLock;
  /*
    0x00: Locked
    0x38: Unlocked
  */
  u8 ultimateModeLock;
  u8 unlockedMinigames[7];
  u8 pad_21[3];
  u32 minigameHiscores[7];
  u32 mmbn4;  // 0x020021f0, ロックマンエグゼ4との通信で変化

  // 0: Default
  u8 msgbox;        // 1..8
  u8 title;         // 1..3: Zero, 4: Ciel
  u8 elevator;      // 1: Wood, 2: MMX
  u8 weather;       // 1: Night, 2: Snowy
  u8 cielComputer;  // 1..4
  u8 lifeEnergy;    // 1: Blue Orbs, 2: Flashing Square
  u8 crystal;       // 1: Orbs, 2: Green
  u8 disk;          // 1: Blue, 2: Red
  u8 extraLife;     // 1: Blue, 2: Green
  u8 bullet;        // 1: Black, 2: Realistic

  u16 _;
};  // 80 bytes

extern struct SystemSavedataManager gSystemSavedataManager;
extern struct SaveSlotInfo gSaveSlotInfo;

void LoadSystemData(void);
void SaveSystemData(void);
void ToggleMods(mod_t id);
void PrintSaveDataRow(s32 idx, u8 rank, u32 playTime, u8 playLaps, u32 mode, u8 y);

#endif  // GUARD_RMZ3_SYSTEM_SAVE_H
