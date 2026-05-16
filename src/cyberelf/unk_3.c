#include "collision.h"
#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

// NurseB (Elf2) に従属する何か

static void Elf3_Init(Object* p);
void Elf3_Update(struct Elf* p);
void Elf3_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf3Routine = {
    [ENTITY_INIT] =      (void*)Elf3_Init,
    [ENTITY_UPDATE] =    (void*)Elf3_Update,
    [ENTITY_DIE] =       (void*)Elf3_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteElf,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Entity* CreateElf3(struct Entity* nurse_b, struct Entity* z) {
  struct Entity* p = AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    p->taskCol = 16;
    INIT_ELF_ROUTINE(p, 3);
    p->tileNum = 0, p->palID = 0;
    p->unk_28 = nurse_b;
    p->unk_2c = z;
    p->work[0] = 0, p->work[1] = nurse_b->work[1];
  }
  return p;
}

// --------------------------------------------

static const struct Collision sElf3Collisions[];
void FUN_080e2af0(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void Elf3_Init(Object* p) {
  (p->s).flags |= FLIPABLE;
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;
  (p->s).flags &= ~X_FLIP;
  INIT_BODY(p, sElf3Collisions, 1, FUN_080e2af0);
  (p->s).work[2] = 0;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  Elf3_Update((void*)p);
}

INCASM("asm/cyberelf/unk_3.inc");

// 0x08371cf0
static const struct Collision sElf3Collisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x40,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0100, -0x0E00, 0x3400, 0x3200},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {-0x0100, -0x0E00, 0x3400, 0x3200},
    },
};
