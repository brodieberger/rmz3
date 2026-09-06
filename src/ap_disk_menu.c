#include "ap.h"

#undef ApDiskMenuUpdate

#include "disk.h"
#include "game.h"
#include "global.h"
#include "input.h"
#include "sound.h"
#include "stagerun.h"
#include "text.h"

#if AP

#define DISK_BITS(disks, i) ((disks)[(i) >> 2] >> ((i) & 3))
#define DISK_FOUND(bits) ((bits) & 1)
#define DISK_ANALYSED(bits) ((bits) & 0x10)

static bool32 anyUnread(void) {
  const u8* disks = gStageDiskManager.disk;
  u16 i;

  for (i = 0; i < DISK_COUNT; i++) {
    u8 bits = DISK_BITS(disks, i);
    if (DISK_FOUND(bits) && !DISK_ANALYSED(bits)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*
  For opening every disk
*/
void ApDiskMenuUpdate(struct GameState* g) {
  u8 cursorBits;
  u16 i;

  // mode[2] is the sub-loop: 0 is the grid, 1 and 2 are the window opening and closing.
  if (g->mode[2] != 0 || !anyUnread()) {
    return;
  }

  cursorBits = DISK_BITS(gStageDiskManager.disk, (g->sceneState).disk.cursorDisk);
  if (!DISK_FOUND(cursorBits) || DISK_ANALYSED(cursorBits)) {
    PrintString(gApDiskOpenAllText, 1, 0x12);
  }

  if (!(gJoypad[0].pressed & SELECT_BUTTON)) {
    return;
  }

  for (i = 0; i < DISK_COUNT; i++) {
    if (DISK_FOUND(DISK_BITS(gStageDiskManager.disk, i))) {
      OpenSecretDisk(g, (u8)i, FALSE);
    }
  }

  PlaySound(14);
  (g->sceneState).disk.redraw = 1;
}

void (*const gApDiskMenuUpdateFn)(struct GameState* g) = ApDiskMenuUpdate;

#endif /* AP */
