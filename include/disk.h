#ifndef GUARD_RMZ3_DISK_H
#define GUARD_RMZ3_DISK_H

#include "gba/gba.h"

struct SquareCursorWidget;

// GameState.sceneState のシークレットディスク解析シーン用のレイアウト
// One row of the per-disk table at 0x083864d8, indexed by disk number.
struct SecretDiskEntry {
  u16 unk_00;  // 0x00, passed to FUN_080e83d0; a zero row means "no entry"
  s8 x;        // 0x02, offset from the modal centre, used as (0x40 - x) << 8
  s8 y;        // 0x03, offset from the modal centre, used as (0x50 - y) << 8
  u8 unk_04;   // 0x04
  u8 rate0;    // 0x05, high nibble is added per frame to unk_0e; value >> 1 is the target
  u8 rate1;    // 0x06, the same for unk_0f
  u8 unk_07;   // 0x07
};
static_assert(sizeof(struct SecretDiskEntry) == 8);

struct SecretDiskState {
  u8 unk_00[4];
  struct SquareCursorWidget* cursor;  // 0x04
  u8 unk_08[2];
  u8 cursorDisk;  // 0x0A, disk under the cursor (0..0xB3); the grid is 5 wide, so x = %5, y = /5
  u8 scrollRow;   // 0x0B, topmost visible row, one row being 5 disks
  u8 redraw;      // 0x0C, set when the BG map needs repainting
  u8 unk_0d;      // 0x0D, only ever zeroed, by DiskLoop_Init
  u8 winHalfW;    // 0x0E, half-width of the analysis window: WIN0H spans 0x40 +/- this
  u8 winHalfH;    // 0x0F, half-height: WIN0V spans 0x50 +/- this
  u8 colorR;      // 0x10, backdrop colour while the window is open, packed BGR555
  u8 colorG;      // 0x11
  u8 colorB;      // 0x12
};

void clearSecretDiskData(u8* flagbits);
void clearSecretDiskDataHard(u8* flagbits);
void unlockAllSecretDisk(u8* flagbits);

#endif  // GUARD_RMZ3_DISK_H
