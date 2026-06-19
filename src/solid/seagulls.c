#include "entity.h"
#include "global.h"
#include "mod.h"
#include "solid.h"
#include "syssav.h"

struct Seagulls {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 unk_b4_x;   // 0xB4
  u8 unk_b8[12];  // 0xB8
};
static_assert(sizeof(struct Seagulls) == sizeof(struct Solid));

static void Seagulls_Init(struct Solid* p);
static void Seagulls_Update(struct Solid* p);
static void Seagulls_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSeagullsRoutine = {
    [ENTITY_INIT] =      (void*)Seagulls_Init,
    [ENTITY_UPDATE] =    (void*)Seagulls_Update,
    [ENTITY_DIE] =       (void*)Seagulls_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Entity* CreateSeagulls(struct Entity* q, u8 t, u8 param_3) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_SEAGULLS);
    p->unk_28 = (void*)q;
    p->coord = q->coord;
    p->work[0] = t, p->work[1] = param_3;
  }
  return p;
}

static void FUN_080dcd20(struct Seagulls* p);
void FUN_080dcdac(struct Solid* p);
void FUN_080dced4(struct Solid* p);

static void Seagulls_Init(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dcd20((void*)p);
      break;
    }
    case 1: {
      FUN_080dcdac(p);
      break;
    }
    case 2: {
      FUN_080dced4(p);
      break;
    }
  }
}

void FUN_080dd02c(struct Solid* p);
void FUN_080dd11c(struct Solid* p);
void FUN_080dd364(struct Solid* p);

static void Seagulls_Update(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dd02c(p);
      break;
    }
    case 1: {
      FUN_080dd11c(p);
      break;
    }
    case 2: {
      FUN_080dd364(p);
      break;
    }
  }
}

void FUN_080dd400(struct Solid* p);
void FUN_080dd418(struct Solid* p);
void FUN_080dd430(struct Solid* p);

static void Seagulls_Die(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dd400(p);
      break;
    }
    case 1: {
      FUN_080dd418(p);
      break;
    }
    case 2: {
      FUN_080dd430(p);
      break;
    }
  }
}

// --------------------------------------------

static void FUN_080dcd20(struct Seagulls* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if (!FLAG(gSystemSavedata.flags, MOD_SEAGULLS)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (p->s).unk_2c = (void*)CreateSeagulls((void*)p, 1, 0);
  p->unk_b4_x = (p->s).coord.x;
  (p->s).work[2] = 0, (p->s).work[3] = 0;
  Seagulls_Update((void*)p);
}

INCASM("asm/solid/seagulls.inc");
