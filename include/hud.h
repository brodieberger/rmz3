#ifndef GUARD_RMZ3_HEALTH_H
#define GUARD_RMZ3_HEALTH_H

#include "common.h"
#include "gba/gba.h"

struct Zero;
struct Entity;

// state about BG0(Health Layer)
struct HUD {
  u16* bg0;               // 0x00, -> 0x02030b70
  u16 offset_y;           // 0x04
  struct Zero* z;         // 0x08
  struct Entity* unk_0c;  // 0x0C
  s32* timeLeft;          // 0x10, e.g. Left time in Volcano Mid-boss room(Kill 25 Crossbynes)
};  // 20 bytes
static_assert(sizeof(struct HUD) == 20);

extern struct HUD gHUD;

void ResetHUD(u16* bg0);
void DrawStatus(void);
void DrawLeftTime(void);

#endif  // GUARD_RMZ3_OW_BG0_H
