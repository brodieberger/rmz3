#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

struct CyberElfNurseB {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};
static_assert(sizeof(struct CyberElfNurseB) == sizeof(struct Elf));

struct Entity* CreateElf3(struct Entity* nurse_b, struct Entity* z);

void NurseB_Init(struct Elf* p);
void NurseB_Update(struct Elf* p);
void NurseB_Die(struct Elf* p);

// clang-format off
const ElfRoutine gNurseBRoutine = {
    [ENTITY_INIT] =      NurseB_Init,
    [ENTITY_UPDATE] =    NurseB_Update,
    [ENTITY_DIE] =       NurseB_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateNurseBElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfNurseB* p = (struct CyberElfNurseB*)AllocEntityLast(gElfHeaderPtr);
  if (p != NULL) {
    INIT_ELF_ROUTINE(p, 2);
    p->player = z;
    (p->s).work[0] = breed, (p->s).work[1] = availability, (p->s).work[2] = satelite_slot;
    if (satelite_slot == 0) {
      (p->s).work[3] = ((&z->unk_b4)->status).satelites[0];
    } else {
      (p->s).work[3] = ((&z->unk_b4)->status).satelites[1];
    }
  }
  return (struct Entity*)p;
}

INCASM("asm/cyberelf/nurse_b.inc");

// --------------------------------------------

void FUN_080e284c(struct Elf* p);
void FUN_080e28a8(struct Elf* p);
void FUN_080e2920(struct Elf* p);
void FUN_080e28a8(struct Elf* p);

const ElfFunc sNurseBUpdates[4] = {
    FUN_080e284c,
    FUN_080e28a8,
    FUN_080e2920,
    FUN_080e28a8,
};
