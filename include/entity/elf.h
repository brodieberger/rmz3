#ifndef GUARD_RMZ3_ENTITY_CYBERELF_H
#define GUARD_RMZ3_ENTITY_CYBERELF_H

#include "entity/entity.h"
#include "types.h"

struct Elf {
  OBJECT_HDR;
  u8 buffer[16];  // general purpose buffer
};  // 196 bytes

typedef void (*ElfFunc)(struct Elf*);

#endif  // GUARD_RMZ3_ENTITY_CYBERELF_H
