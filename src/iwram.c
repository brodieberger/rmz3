#include "gba/gba.h"

struct SoundInfo;

// 0x03007A50

IWRAM_DATA u8 StackUsr[848] = {};
// 0x03007DA0: sp_sys ↑

IWRAM_DATA u8 StackIrq[512] = {};
// 0x03007FA0: sp_irq ↑

IWRAM_DATA u8 StackSvc[64] = {};
// 0x03007FE0: sp_svc ↑

// 0x03007FE0..
// BIOS によって利用される予約領域

IWRAM_DATA u8 Unk_03007fe0[16] = {};  // Debug Exception Stack
IWRAM_DATA struct SoundInfo* SOUND_INFO_PTR = NULL;
IWRAM_DATA u8 AllocatedArea_03007ff4[4] = {};
IWRAM_DATA u16 INTR_CHECK = 0;
IWRAM_DATA void* INTR_VECTOR = NULL;
