#ifndef __INCLUDE_UNK0202FE50_H__
#define __INCLUDE_UNK0202FE50_H__

#include "gba/gba.h"

// 見たところ使われていなさそう
struct Unused_0202fe50 {
  u16 unk_00;
  u16 unk_02;
  u32 unk_04;
};  // 8 bytes
static_assert(sizeof(struct Unused_0202fe50) == 8);

extern struct Unused_0202fe50 gUnk_0202fe50;

#endif  // __INCLUDE_UNK0202FE50_H__
