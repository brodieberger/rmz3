#ifndef __INCLUDE_VFX_UNK_COMMON_H__
#define __INCLUDE_VFX_UNK_COMMON_H__

#include "entity/entity.h"
#include "gba/gba.h"

// このレイアウトのVFXが複数存在する
struct VFXUnkCommon {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  motion_t m_74;
  u32 unk_78;
  u8 unk_7c;
  u8 pad_7d[3];
  u16 unk_80;
};  // 132 bytes
static_assert(sizeof(struct VFXUnkCommon) == sizeof(struct VFX));

#endif  // __INCLUDE_VFX_UNK_COMMON_H__
