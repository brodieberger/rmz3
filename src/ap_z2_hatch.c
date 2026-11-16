#include "anim_loader.h"
#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "overworld.h"
#include "solid.h"
#include "spawn.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"

#if AP

/*
  Zero 2's solid 22, a hatch in the floor. A plate to stand on until Zero touches it, then it walks him 64 px
  through, up or down, and shuts behind him.
  work0: bit 0 takes Zero up from below, else down from above
         bit 1 a one-way plate, gone once used, the floor patched shut, else two leaves
  work1: 1 for the second leaf
*/

struct Hatch {
  OBJECT_HDR;
  struct Zero* zero;  // 0xB4
  u8 _b8[4];
  Coords32 look;      // 0xBC
};
static_assert(sizeof(struct Hatch) == 196);

enum { HATCH_SHUT, HATCH_DOWN, HATCH_UP, HATCH_SETTLE };

#define PLATE(s) ((s)->work[0] & 2)

// 0x08320e60
const u16 gApZ2HatchPatch[2 + 4] = {4, 1, 0x414, 0x415, 0x416, 0x417};

static const struct Collision sCollisions[2];
// 0x083499e8, 0x083499f0
static const struct Rect sSizes[2] = {{0x2000, 0, 0x4000, 0x2000}, {0x2000, 0x800, 0x4000, 0x1000}};

static void Hatch_Init(struct Hatch* p);
static void Hatch_Update(struct Hatch* p);
static void Hatch_Die(struct Hatch* p);

// clang-format off
const SolidRoutine gApZ2HatchRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Hatch_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Hatch_Update,
    [ENTITY_DIE] =       (SolidFunc)Hatch_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static motion_t shut(struct Entity* s, u8 anim) {
  return PLATE(s) ? MOTION(AP_SHEET_Z2_HATCH_PLATE, anim) : MOTION(AP_SHEET_Z2_HATCH, anim);
}

// Opening frames are on the other sheet
static void animate(struct Hatch* p, u8 anim) {
  struct Entity* s = &p->s;
  u8 frame;
  bool8 open;
  UpdateEntityAnim(s);
  frame = (s->spr).spriteIdx;
  if (PLATE(s)) {
    open = frame >= 2;
  } else {
    open = frame >= 7 && frame <= 12;
  }
  if (open == (s->motionID == AP_SHEET_Z2_HATCH_OPEN || s->motionID == AP_SHEET_Z2_HATCH_PLATE_OPEN)) return;
  if (open) {
    GotoMotion(s, PLATE(s) ? MOTION(AP_SHEET_Z2_HATCH_PLATE_OPEN, anim) : MOTION(AP_SHEET_Z2_HATCH_OPEN, anim),
               (s->motion).cmdIdx, (s->motion).duration);
  } else {
    GotoMotion(s, shut(s, anim), (s->motion).cmdIdx, (s->motion).duration);
  }
}

static void setSolid(struct Entity* s, const struct Rect* size) {
  s->flags2 |= ENTI_PHYSICS;
  s->size = size;
  s->physicsAttr = SHAPE_BLOCK;
}

// 0x080ceb44
static void Hatch_Init(struct Hatch* p) {
  struct Entity* s = &p->s;
  struct Entity* q;
  struct PreloadEntity sheet = {AP_SHEET_Z2_HATCH, 0, 0, 0, 0, AP_PRELOAD_SHEET, 0};
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  if (s->work[1] == 0) {
    s->coord.x = FUN_0800a31c(s->coord.x, s->coord.y);
    if (PLATE(s)) {
      s->coord.y += PIXEL(9);
      sheet.id = AP_SHEET_Z2_HATCH_PLATE;
    } else {
      s->coord.y += PIXEL(8);
      q = AllocEntityLast(gSolidHeaderPtr);
      if (q == NULL) return;
      INIT_SOLID_ROUTINE(q, SOLID_Z2_HATCH);
      q->renderPrio = 30;
      q->flags2 |= WHITE_PAINTABLE;
      q->invincibleID = q->uniqueID;
      q->work[1] = 1;
      q->unk_28 = s;
      q->coord.x = s->coord.x - PIXEL(1);
      q->coord.y = s->coord.y;
    }
    sheet.tileBase = wStaticGraphicTilenums[SM120_DOOR_2D_GRAY_H];
    sheet.palID = wStaticMotionPalIDs[SM120_DOOR_2D_GRAY_H];
    ApLoadSheet(&sheet);
  } else {
    SetMotion(s, MOTION(AP_SHEET_Z2_HATCH, 0));
    SET_YFLIP(s, TRUE);
  }
  (s->spr).oam.priority = 1;
  s->flags |= DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->mode[2] = 0;
  Hatch_Update(p);
}

// 0x080cecd4
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Hatch* p = (struct Hatch*)body->parent;
  struct Entity* s = &p->s;
  struct Entity* who = body->enemy->parent;
  if (who->kind != 0) return;
  if (s->coord.y > who->coord.y) {
    if (s->work[0] & 1) return;
    s->mode[1] = HATCH_DOWN;
  } else {
    if (!(s->work[0] & 1)) return;
    s->mode[1] = HATCH_UP;
  }
  s->mode[2] = 0;
  ((u8*)who)[0x119] = 1;
  gStageRun.vm.unk_004 |= 1;
  p->zero = (struct Zero*)who;
}

// 0x080ced2c
static void Hatch_Shut(struct Hatch* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, shut(s, 0));
    s->flags |= COLLIDABLE;
    INIT_BODY(p, sCollisions, 0, onCollision);
    setSolid(s, &sSizes[(s->work[0] & 1) == 0]);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
}

// 0x080cedcc, 0x080cefe8: walks Zero through, the camera on a spot past him
static void Hatch_Pass(struct Hatch* p) {
  struct Entity* s = &p->s;
  struct Entity* zero = &(p->zero)->s;
  s32 step = s->mode[1] == HATCH_UP ? -PIXEL(1) : PIXEL(1);
  s32 dx;
  struct PreloadEntity sheet = {AP_SHEET_Z2_HATCH_OPEN, 0, 379, 0, 0, AP_PRELOAD_SHEET, 0};
  switch (s->mode[2]) {
    case 0:
      EXIT_BODY(p);
      s->flags2 &= ~ENTI_PHYSICS;
      if (PLATE(s)) sheet.id = AP_SHEET_Z2_HATCH_PLATE_OPEN;
      sheet.palID = wStaticMotionPalIDs[SM120_DOOR_2D_GRAY_H];
      ApLoadSheet(&sheet);
      SetMotion(s, shut(s, 2));
      PlaySound(SE_Z2_GATE_SINK);
      p->look.x = s->coord.x + PIXEL(32);
      p->look.y = zero->coord.y + step * 64;
      s->work[2] = 64;
      s->mode[2]++;
      break;
    case 1:
      animate(p, 2);
      if (--s->work[2] != 0) break;
      s->work[2] = 64;
      s->mode[2]++;
      break;
    case 2:
      animate(p, 2);
      zero->coord.y += step;
      dx = p->look.x - zero->coord.x;
      if (dx > PIXEL(1)) {
        zero->coord.x += PIXEL(1);
      } else if (dx < -PIXEL(1)) {
        zero->coord.x -= PIXEL(1);
      }
      if (s->work[2] == 32) gStageRun.vm.camera.player = &p->look;
      if (--s->work[2] != 0) break;
      setSolid(s, &sSizes[0]);
      PlaySound(SE_Z2_GATE_RISE);
      SetMotion(s, shut(s, 3));
      s->work[2] = 32;
      s->mode[2]++;
      break;
    case 3:
      animate(p, 3);
      if (--s->work[2] != 0) break;
      if (PLATE(s)) {
        if ((s->motion).state != ANIM_END) break;
        gOverworld.state[2] = 1;
        PatchMetatileMap(30, 29, gApZ2HatchPatch);
      }
      gStageRun.vm.unk_004 &= ~1;
      gStageRun.vm.camera.player = &zero->coord;
      ((u8*)zero)[0x119] = 0;
      LOAD_STATIC_GRAPHIC(SM028_ICE_EFFECT);
      if (PLATE(s)) {
        s->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(p);
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      PlaySound(SE_Z2_GATE_SINK);
      s->mode[1] = HATCH_SETTLE;
      s->mode[2] = 0;
      break;
  }
}

// 0x080cf210
static void Hatch_Settle(struct Hatch* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setSolid(s, &sSizes[0]);
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      animate(p, 3);
      if ((s->motion).state != ANIM_END) break;
      SetMotion(s, shut(s, 0));
      s->mode[2]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      break;
  }
}

static const SolidFunc sStates[4] = {(SolidFunc)Hatch_Shut, (SolidFunc)Hatch_Pass, (SolidFunc)Hatch_Pass, (SolidFunc)Hatch_Settle};

// 0x080cec44
static void Hatch_Update(struct Hatch* p) {
  struct Entity* s = &p->s;
  struct Entity* first;
  if (s->work[1] == 0) {
    (sStates[s->mode[1]])((struct Solid*)p);
    return;
  }
  first = s->unk_28;
  if (first->mode[0] > ENTITY_UPDATE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Hatch_Die(p);
    return;
  }
  (s->spr).sprites = (first->spr).sprites;
  (s->spr).spriteIdx = (first->spr).spriteIdx;
  (s->spr).oam.tileNum = (first->spr).oam.tileNum;
}

// 0x080ceca0
static void Hatch_Die(struct Hatch* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// clang-format off
// 0x083499b8
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x2000, 0x100, 0x2400, 0x2400}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0, 0, 0, 0}},
};
// clang-format on

#endif
