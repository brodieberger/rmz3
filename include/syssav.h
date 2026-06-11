#ifndef GUARD_RMZ3_SYSTEM_SAVE_H
#define GUARD_RMZ3_SYSTEM_SAVE_H

#include "gba/gba.h"
#include "sram.h"
#include "types.h"

enum SramHealth {
  SRAM_NEUTRAL = 0,
  DATA_OK = 0,
  DATA_BROKEN = 0xFFFF,
};

struct SaveSlotMetadata {
  bool8 ok[SECTOR_NUM];                         // 0x0200_05f8
  u32 ALIGNED(4) playtime[SECTOR_NUM];          // 0x0200_0600
  u32 ALIGNED(4) rank[GAME_SECTOR_NUM];         // 0x0200_0618
  u8 ALIGNED(4) lap[GAME_SECTOR_NUM + 1];       // 0x0200_062c 周回数, エントリ数は GAME_SECTOR_NUM?
  u8 ALIGNED(4) gamemode[GAME_SECTOR_NUM + 1];  // 0x0200_0634, エントリ数は GAME_SECTOR_NUM?
  u32 _;
};  // 72 bytes
static_assert(sizeof(struct SaveSlotMetadata) == 72);

/**
 * @note ミニゲームなどのシステム全体で共有するデータ
 * @note SECTOR_SYSTEM には SectorHeader + SystemSavedata が保存される
 * @note 0x020021B0
 */
typedef struct {
  u8 flags[24];             // 0x00, bit0..62: カットシーン視聴済みフラグ("constants/cutscene.h"), bit63..: 改造カード("mod.h")
  u8 hardmodeLock;          // 0x18, val=0x00: Locked, val=0x31: Unlocked
  u8 ultimateModeLock;      // 0x19: val=0x00: Locked, val=0x38: Unlocked
  u8 unlockedMinigames[7];  // 0x1A
  u8 pad_21[3];
  u32 minigameHiscores[7];  // 0x24
  u32 mmbn4;                // 0x40, 0x020021f0, ロックマンエグゼ4との通信で変化
  u8 msgbox;                // 0x44, Msgbox border design, 0: Default, 1: bold, 2: blue, 3: Scream, 4: Mechanical, 5: Plant, 6: Windows, 7: ?: 8: Scream Yellow
  u8 title;                 // 0x45, 0: Default, 1..3: Zero, 4: Ciel
  u8 elevator;              // 0x46, 0: Default, 1: Wood, 2: MMX
  u8 weather;               // 0x47, 0: Default, 1: Night, 2: Snowy
  u8 cielComputer;          // 0x48, 0: Default, 1: White, 2: like Vending Machine, 3: ?, 4: ?
  u8 lifeEnergy;            // 0x49, 0: Default, 1: Blue Orbs, 2: Flashing Square
  u8 crystal;               // 0x4A, 0: Default, 1: Orbs, 2: Green
  u8 disk;                  // 0x4B, 0: Default, 1: Blue, 2: Red
  u8 extraLife;             // 0x4C, 0: Default, 1: Blue, 2: Green
  u8 bullet;                // 0x4D, 0: Default, 1: Black, 2: Realistic
  u16 _;
} SystemSavedata;  // 80 bytes
static_assert(sizeof(SystemSavedata) == 80);

extern SystemSavedata gSystemSavedata;
extern struct SaveSlotMetadata gSaveSlotMetadata;

void LoadSystemData(void);
void SaveSystemData(void);
void ToggleMods(mod_t id);

#endif  // GUARD_RMZ3_SYSTEM_SAVE_H
