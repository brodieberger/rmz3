#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "solid.h"
#include "sound.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's solid 14 work0 0, box the Chain Rod drags.
  mode1:
    0: resting
    1: falling
    2: sliding off edge or into wall
  unk_coord: slide speed, fall speed
*/
struct Box {
  OBJECT_HDR;
  Coords32 prev;   // 0xB4
  bool8 dragging;  // 0xBC
  u8 _bd[7];
};
static_assert(sizeof(struct Box) == sizeof(struct Solid));

static void Box_Init(struct Solid* p);
static void Box_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2BoxRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Box_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Box_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x08349434
static const struct Collision sCollision = {DRP, FACTION_ENEMY, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, NO_DAMAGE | HARDNESS_B3, 0x00, 0, 0xFFFF03FF, {0, -6144, 12288, 12288}};
// 0x0834955c
static const struct Rect sSize = {0, -6400, 12288, 12288};

// 0x080cd02c
static bool8 onFloor(s32 x, s32 y) {
  u8 i;
  for (i = 0; i < 4; i++) {
    if (FUN_080098a4(x - 0x1800 + (i << 12) - (i != 0), y - 0xFF)) return TRUE;
  }
  return FALSE;
}

// 0x080ccfa4, 0x080ccfe8: box-high column at x
static bool8 wallAt(s32 x, s32 y) {
  u8 i;
  for (i = 0; i < 4; i++) {
    if (FUN_080098a4(x, y - 0x30FF + (i << 12) - (i != 0))) return TRUE;
  }
  return FALSE;
}

// 0x080cd06c
static s32 leftWallEdge(struct Entity* s) {
  s32 x = s->coord.x - 0x1800, edge = 0, y, r;
  u8 i;
  for (i = 0; i < 4; i++) {
    y = s->coord.y - 0x3100 + (i << 12) - (i != 0);
    if (!FUN_080098a4(x, y)) continue;
    r = FUN_0800a31c(x, y);
    if (r >= x && r > edge) edge = r;
  }
  return edge != 0 ? edge : x;
}

// 0x080cd0d8
static s32 rightWallEdge(struct Entity* s) {
  s32 x = s->coord.x + 0x17FF, edge = 0x7FFFFFFF, y, r;
  u8 i;
  for (i = 0; i < 4; i++) {
    y = s->coord.y - 0x3100 + (i << 12) - (i != 0);
    if (!FUN_080098a4(x, y)) continue;
    r = FUN_0800a22c(x, y);
    if (r <= x && r < edge) edge = r;
  }
  return edge != 0x7FFFFFFF ? edge : x;
}

// 0x080cd148
static s32 floorY(struct Entity* s) {
  s32 y = s->coord.y - 0x100, floor = 0x7FFFFFFF, r;
  u8 i;
  for (i = 0; i < 4; i++) {
    r = FUN_08009f6c(s->coord.x - 0x1800 + (i << 12) - (i != 0), y);
    if (r < floor) floor = r;
  }
  return (floor != 0x7FFFFFFF ? floor : y) + 0x100;
}

// 0x080cd1b0
static void dust(struct Box* b) {
  struct Entity* s = &b->s;
  Coords32 c;
  if (b->prev.x == s->coord.x) return;
  c.x = s->coord.x + (b->prev.x < s->coord.x ? -0x1400 : 0x1400);
  c.y = s->coord.y;
  CreateSmoke(3, &c);
}

// Off ledge it was moving from, falls
static void fall(struct Entity* s, s32 dir) {
  if (dir < 0) {
    s->coord.x = FUN_0800a22c(s->coord.x, s->coord.y - 0xFF) - 0x17FF;
  } else if (dir > 0) {
    s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y - 0xFF) + 0x1800;
  }
  s->mode[1] = 1;
  s->unk_coord.y = 0;
}

static void slide(struct Entity* s, s32 speed) {
  s->mode[1] = 2;
  s->unk_coord.x = speed;
}

// 0x080cd1e8
static u16 Box_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy UNUSED) {
  struct Box* b = (struct Box*)s;
  if (s->mode[1] != 0) return 0;
  if (dx != 0) {
    if (!b->dragging) {
      PlaySound(SE_Z2_BOX_DRAG);
      b->dragging = TRUE;
    }
    if (dx < 0 ? wallAt(s->coord.x - 0x1801, s->coord.y) : wallAt(s->coord.x + 0x1800, s->coord.y)) {
      b->dragging = FALSE;
      return 0;
    }
    s->coord.x += dx;
    if (!onFloor(s->coord.x, s->coord.y)) {
      fall(s, dx);
      b->dragging = FALSE;
      return 0;
    }
    if (dx < 0 ? wallAt(s->coord.x - 0x1801, s->coord.y) : wallAt(s->coord.x + 0x1800, s->coord.y)) {
      s->coord.x = dx < 0 ? leftWallEdge(s) + 0x1800 : rightWallEdge(s) - 0x17FF;
      b->dragging = FALSE;
      return 0;
    }
    // Wall within 16 px, slides rest of way itself
    if (dx < 0 ? wallAt(s->coord.x - 0x2801, s->coord.y) : wallAt(s->coord.x + 0x2800, s->coord.y)) {
      slide(s, dx < 0 ? -0x80 : 0x80);
      PlaySound(SE_Z2_BOX_DRAG);
      b->dragging = FALSE;
      return 0;
    }
  }
  if (pulling) return 1;
  b->dragging = FALSE;
  return 0;
}

// 0x080cc8dc
static void Box_Init(struct Solid* p) {
  struct Box* b = (struct Box*)p;
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SET_XFLIP(p, FALSE);
  s->flags |= DISPLAY | FLIPABLE | COLLIDABLE;
  s->coord.y = floorY(s);
  s->unk_coord.x = s->unk_coord.y = 0;
  b->prev = s->coord;
  s->d.x = s->d.y = 0;
  s->work[2] = 0;
  b->dragging = FALSE;
  INIT_BODY(p, &sCollision, 32, NULL);
  (p->body).unk_28 = (u32)Box_Pull;
  s->flags2 &= ~WHITE_PAINTABLE;
  s->invincibleID = s->uniqueID;
  SetMotion(s, MOTION(AP_SHEET_Z2_BOX, 0));
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sSize;
  s->physicsAttr = 0x2001;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Box_Update(p);
}

// 0x080cca10
static void Box_Update(struct Solid* p) {
  struct Box* b = (struct Box*)p;
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->work[2]--;
  switch (s->mode[1]) {
    case 0:
      if (!onFloor(s->coord.x, s->coord.y)) {
        fall(s, s->d.x);
        break;
      }
      if (s->d.x == 0) break;
      if ((s->work[2] & 3) == 0) dust(b);
      // Mostly past edge, slides off
      if (s->d.x < 0 && !FUN_080098a4(s->coord.x + 0x7FF, s->coord.y + 0x800) && !FUN_080098a4(s->coord.x - 0x1800, s->coord.y + 0x800)) {
        slide(s, -0x80);
      } else if (s->d.x > 0 && !FUN_080098a4(s->coord.x - 0x800, s->coord.y + 0x800) && !FUN_080098a4(s->coord.x + 0x17FF, s->coord.y + 0x800)) {
        slide(s, 0x80);
      }
      break;
    case 1:
      if (!onFloor(s->coord.x, s->coord.y)) {
        s->coord.y += s->unk_coord.y;
        if (!onFloor(s->coord.x, s->coord.y)) {
          s->unk_coord.y += 0x40;
          if (s->unk_coord.y > 0x700) s->unk_coord.y = 0x700;
          break;
        }
        s->coord.y = floorY(s);
        AppendQuake(1, &s->coord);
      }
      PlaySound(SE_Z2_BOX_LAND);
      s->mode[1] = 0;
      break;
    case 2:
      if (!onFloor(s->coord.x, s->coord.y)) {
        fall(s, s->d.x);
        break;
      }
      if (s->unk_coord.x < 0 ? wallAt(s->coord.x - 0x1801, s->coord.y) : wallAt(s->coord.x + 0x1800, s->coord.y)) {
        s->mode[1] = 0;
        break;
      }
      s->coord.x += s->unk_coord.x;
      if (s->unk_coord.x < 0 ? wallAt(s->coord.x - 0x1801, s->coord.y) : wallAt(s->coord.x + 0x1800, s->coord.y)) {
        s->coord.x = s->unk_coord.x < 0 ? leftWallEdge(s) + 0x1800 : rightWallEdge(s) - 0x17FF;
        s->mode[1] = 1;
        s->unk_coord.y = 0;
        break;
      }
      if ((s->work[2] & 15) == 0) dust(b);
      break;
  }
  s->d.x = s->coord.x - b->prev.x;
  s->d.y = s->coord.y - b->prev.y;
  b->prev = s->coord;
}

#endif  // AP
