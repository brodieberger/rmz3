#ifndef __INCLUDE_WIDGET_EXSKILL_ICONS_H__
#define __INCLUDE_WIDGET_EXSKILL_ICONS_H__

#include "entity/entity.h"
#include "types.h"

struct ExSkillIcons {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u8 unk_000[4];
  u8 unk_004[12];
};
static_assert(sizeof(struct ExSkillIcons) == (sizeof(struct Entity) + 16));

#endif  // __INCLUDE_WIDGET_EXSKILL_ICONS_H__
