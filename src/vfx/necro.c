#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

/*
  雑魚敵が死んだあと、爆散始まるまでの状態
  雑魚敵が切断死した際の、切断された方の片方
*/
struct NecroVFX {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  motion_t* motions;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06[10];
};
static_assert(sizeof(struct NecroVFX) == sizeof(struct VFX));

static const VFXFunc sUpdates[5];
static const u8 sInitModes[5];

static void Necro_Init(struct VFX* p);
static void Necro_Update(struct NecroVFX* p);
static void Necro_Die(struct VFX* p);

// clang-format off
const VFXRoutine gNecroRoutine = {
    [ENTITY_INIT] =      (void*)Necro_Init,
    [ENTITY_UPDATE] =    (void*)Necro_Update,
    [ENTITY_DIE] =       (void*)Necro_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

void FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 0, (p->s).work[1] = i;
      (p->s).unk_28 = e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 1, p->unk_05 = 0;
    }
  }
}

void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 0, (p->s).work[1] = i;
      (p->s).unk_28 = e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 0, p->unk_05 = 0;
    }
  }
}

void FUN_080b8080(struct Enemy* e, struct Coord* c, motion_t* motions, u8 len, u8 r4) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 0, (p->s).work[1] = i;
      (p->s).unk_28 = (void*)e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      (p->s).palID = r4;
      p->unk_04 = 1, p->unk_05 = 0;
    }
  }
}

static void Unused_080b8114(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 1, (p->s).work[1] = i;
      (p->s).unk_28 = e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 1, p->unk_05 = 0;
    }
  }
}

void FUN_080b81a0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 1, (p->s).work[1] = i;
      (p->s).unk_28 = e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 0, p->unk_05 = 0;
    }
  }
}

void FUN_080b822c(struct Enemy* e, struct Coord* c, motion_t* motions, u8 len, u8 r4) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 1, (p->s).work[1] = i;
      (p->s).unk_28 = (void*)e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 1, p->unk_05 = 1;
      (p->s).palID = r4;
    }
  }
}

void FUN_080b82c0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_NECRO);
      (p->s).tileNum = 0, (p->s).palID = 0;
      (p->s).work[0] = 2, (p->s).work[1] = i;
      (p->s).unk_28 = e;
      p->motions = motions;
      (p->s).coord.x = c->x, (p->s).coord.y = c->y;
      p->unk_04 = 1, p->unk_05 = 0;
    }
  }
}

void FUN_080b834c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x;
    (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    p->unk_04 = 1, p->unk_05 = 0;
  }
}

void FUN_080b83d4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x;
    (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    p->unk_04 = 0, p->unk_05 = 0;
  }
}

void FUN_080b8454(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x;
    (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    (p->s).taskCol = taskCol;
    p->unk_04 = 1, p->unk_05 = 0;
  }
}

void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x;
    (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    p->unk_04 = 1, p->unk_05 = 0;
  }
}

void FUN_080b857c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x;
    (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    p->unk_04 = 0, p->unk_05 = 0;
  }
}

void FUN_080b85fc(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x, (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    (p->s).taskCol = taskCol;
    p->unk_04 = 1, p->unk_05 = 0;
  }
}

void FUN_080b869c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol, u8 palID) {
  struct NecroVFX* p = (struct NecroVFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).unk_28 = e;
    p->motions = motions;
    (p->s).coord.x = c->x, (p->s).coord.y = c->y;
    (p->s).d.x = dc->x, (p->s).d.y = dc->y;
    (p->s).unk_coord.y = y;
    (p->s).work[2] = frame;
    (p->s).taskCol = taskCol;
    (p->s).palID = palID;
    p->unk_04 = 1, p->unk_05 = 0;
  }
}

// --------------------------------------------

static void Necro_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  Necro_Update((void*)p);
}

// --------------------------------------------

void FUN_080b8804(struct VFX* p);
void FUN_080b8984(struct VFX* p);
void FUN_080b8af8(struct VFX* p);
void FUN_080b8c74(struct VFX* p);
void FUN_080b8d4c(struct VFX* p);

static void Necro_Update(struct NecroVFX* p) {
  // clang-format off
  static const VFXFunc sUpdates[5] = {
      (void*)FUN_080b8804,
      (void*)FUN_080b8984,
      (void*)FUN_080b8af8,
      (void*)FUN_080b8c74,
      (void*)FUN_080b8d4c,
  };
  // clang-format on

  if (IS_METTAUR && p->unk_04 != 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).mode[1]])((void*)p);
}

// --------------------------------------------

static void Necro_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
  return;
}

// --------------------------------------------

INCASM("asm/vfx/necro.inc");

static const u8 sInitModes[5] = {0, 1, 2, 3, 4};
