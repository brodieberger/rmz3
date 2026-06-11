#ifndef GUARD_RMZ3_SRAM_H
#define GUARD_RMZ3_SRAM_H

#include "gba/gba.h"
#include "types.h"

#define SRAM_SIZE (32 * 1024)

// 2730 * 12 = 32760
#define SECTOR_SIZE 2730

#define GAME_SECTOR_NUM 5                  // ゲームのセーブスロット
#define SECTOR_NUM (GAME_SECTOR_NUM + 1)   // ゲームのセーブスロット5つ + システムデータ用のセーブスロット1つ
#define TOTAL_SECTOR_NUM (SECTOR_NUM * 2)  // メインのセーブデータとバックアップのセーブデータを合わせた数

enum SectorID {
  SECTOR_GAME_0,  // ゲームのセーブスロット1
  SECTOR_GAME_1,  // ゲームのセーブスロット2
  SECTOR_GAME_2,  // ゲームのセーブスロット3
  SECTOR_GAME_3,  // ゲームのセーブスロット4
  SECTOR_GAME_4,  // ゲームのセーブスロット5
  SECTOR_SYSTEM,  // システムデータ用のセクタ (ゲームのプレイヤーからは見れない)
};

// 各セクタのヘッダ
typedef struct {
  u32 INTI;  // マジックナンバ INTI (INTI　出ない場合はセーブデータがないと判断する)
  u32 checksum;
  u32 size;  // セクタのデータ部分のサイズ(つまり、 sector0..4: sizeof(GameSavedata), sector5: sizeof(SystemSavedata))
  u8 unk_c;  // 0x0B で固定
  u8 pad_d;
  u8 sector;  // セクタ
  u8 unk_f;
} SectorHeader;  // 16 bytes
static_assert(sizeof(SectorHeader) == 16);

struct SramState {
  u8 unk_00;
  u8 sector;
  u8 status;
  u8 busStatus;
  s16 retryCount;
  u16 useBackup;  // +0x3ffc 版を使う 080033d8 でセットされる
  u8* start;      // 例: 0x02036dbc ここからメインのセーブデータ
  u8* wramAddr;   // wramStartから始まって処理と共に増える
  u8* sramAddr;   // セーブデータのある場所
  s32 length;     // SRAMの全体サイズ
  u32 remaining;  // lengthから始まってセーブが進むにつれて減っていく
  s16 unk_1c;
  u16 health;
};  // 32 bytes
static_assert(sizeof(struct SramState) == 32);

typedef void (*saveFunc)(struct SramState* s);

extern struct SramState gSramState;
extern const saveFunc gSramRoutine[3];

void UpdateSram(void);
bool32 ValidateSector(u8 sector, s32 length);
s32 DeleteSector(u8 sector);
s32 sram_08003330(u8 sector, void* data, u32 bytesize);
s32 sram_08003378(u8 sector, void* data, u32 bytesize);

void nop_080033d4(struct SramState* _);
void saveSram(struct SramState* s);
void loadSram(struct SramState* s);

// --------------------------------------------

// セクタ および SRAM のレイアウト

typedef struct PACKED {
  SectorHeader h;
  u8 data[592];  // 592 = sizeof(GameSavedata);
  u8 padding[SECTOR_SIZE - (16 + 592)];
} GameSaveSector;
static_assert(sizeof(GameSaveSector) == SECTOR_SIZE);

typedef struct PACKED {
  SectorHeader h;
  u8 data[80];  // 80 = sizeof(SystemSavedata);
  u8 padding[SECTOR_SIZE - (16 + 80)];
} SystemSaveSector;
static_assert(sizeof(SystemSaveSector) == SECTOR_SIZE);

// これが 0x0E000000 や .sav のレイアウト
struct SRAM {
  GameSaveSector game[GAME_SECTOR_NUM];
  SystemSaveSector system;
  GameSaveSector game_backup[GAME_SECTOR_NUM];  // .game のバックアップセクタ
  SystemSaveSector system_backup;               // .system のバックアップセクタ
  u8 _[8];
};
static_assert(sizeof(struct SRAM) == SRAM_SIZE);

#endif  // GUARD_RMZ3_SRAM_H
