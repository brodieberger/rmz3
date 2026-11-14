#include "anim_loader.h"
#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "gfx.h"
#include "metatile.h"
#include "motion.h"
#include "physics.h"
#include "script.h"
#include "solid.h"
#include "spawn.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/flag.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/motion/static.h"

#if AP

/*
  Zero 2's solid 12.
  work0:
    0: opens from left
    1: opens from right
    2: both, shut while FLAG_2
  work1: 1 for far side
*/

struct Door {
  OBJECT_HDR;
  struct Zero* zero;  // 0xB4
  u8 _b8[4];
  Coords32 look;      // 0xBC
};
static_assert(sizeof(struct Door) == 196);

enum { DOOR_SHUT, DOOR_RIGHT, DOOR_LEFT, DOOR_SETTLE };

#define DOOR(n) MOTION(AP_SHEET_Z2_DOOR, (n))
#define DOOR_OPEN(n) MOTION(AP_SHEET_Z2_DOOR_OPEN, (n))

static const struct Collision sCollisions[2];
static const struct Rect sSize = {0, -0x2000, 0x2000, 0x6000};

static void Door_Init(struct Door* p);
static void Door_Update(struct Door* p);
static void Door_Die(struct Door* p);

// clang-format off
const SolidRoutine gApZ2DoorRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Door_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Door_Update,
    [ENTITY_DIE] =       (SolidFunc)Door_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// Mid-slide frames are on the other sheet
static void animate(struct Door* p, u8 anim) {
  struct Entity* s = &p->s;
  u8 frame;
  bool8 sliding;
  UpdateSpriteAnimation(p);
  frame = (s->spr).spriteIdx;
  sliding = frame >= 7 && frame <= 12;
  if (sliding != (s->motionID == AP_SHEET_Z2_DOOR_OPEN)) {
    GotoMotion(s, sliding ? DOOR_OPEN(anim) : DOOR(anim), (s->motion).cmdIdx, (s->motion).duration);
  }
}

static void setSolid(struct Door* p) {
  (p->s).flags2 |= ENTI_PHYSICS;
  (p->s).size = &sSize;
  (p->s).physicsAttr = SHAPE_BLOCK;
}

// 0x080cb6f4
static void Door_Init(struct Door* p) {
  struct Entity* s = &p->s;
  struct Entity* q;
  struct PreloadEntity sheet = {AP_SHEET_Z2_DOOR, 0, 0, 0, 0, AP_PRELOAD_SHEET, 0};
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  if (s->work[1] == 0) {
    q = AllocEntityLast(gSolidHeaderPtr);
    if (q == NULL) return;
    s->coord.x += PIXEL(8);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    INIT_SOLID_ROUTINE(q, SOLID_Z2_DOOR);
    q->flags2 |= WHITE_PAINTABLE;
    q->invincibleID = q->uniqueID;
    q->work[1] = 1;
    q->unk_28 = s;
    q->coord.x = s->coord.x - PIXEL(1);
    q->coord.y = s->coord.y;
    sheet.tileBase = wStaticGraphicTilenums[SM018_DOOR_2D_BLUE];
    sheet.palID = wStaticMotionPalIDs[SM018_DOOR_2D_BLUE];
    ApLoadSheet(&sheet);
  } else {
    SetSpriteAnimation(p, DOOR(0));
    SET_XFLIP(p, TRUE);
  }
  (s->spr).oam.priority = 1;
  s->flags |= DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Door_Update(p);
}

// 0x080cb8bc
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Door* p = (struct Door*)body->parent;
  struct Entity* s = &p->s;
  struct Entity* who = body->enemy->parent;
  bool8 fromLeft = s->coord.x > who->coord.x;
  if (who->kind != 0 || s->coord.y < who->coord.y || s->coord.y - who->coord.y > PIXEL(8)) return;
  if (s->work[0] & 2) {
    if (FLAG(gCurStory.s.gameflags, FLAG_2)) return;
  } else if (fromLeft == ((s->work[0] & 1) != 0)) {
    return;
  }
  s->mode[1] = fromLeft ? DOOR_RIGHT : DOOR_LEFT;
  s->mode[2] = 0;
  ((u8*)who)[0x119] = 1;
  gStageRun.vm.unk_004 |= 1;
  p->zero = (struct Zero*)who;
}

// 0x080cb95c
static void Door_Shut(struct Door* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, DOOR(0));
    INIT_BODY(p, sCollisions, 0, onCollision);
    setSolid(p);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
}

// 0x080cb9c8, 0x080cbaf8: walks Zero through, camera following spot past it
static void Door_Pass(struct Door* p) {
  struct Entity* s = &p->s;
  struct Entity* zero = &(p->zero)->s;
  bool8 right = s->mode[1] == DOOR_RIGHT;
  struct PreloadEntity sheet = {AP_SHEET_Z2_DOOR_OPEN, 0, 380, 0, 0, AP_PRELOAD_SHEET, 0};
  switch (s->mode[2]) {
    case 0:
      EXIT_BODY(p);
      s->flags2 &= ~ENTI_PHYSICS;
      sheet.palID = wStaticMotionPalIDs[SM018_DOOR_2D_BLUE];
      ApLoadSheet(&sheet);
      SetSpriteAnimation(p, DOOR(2));
      PlaySound(SE_Z2_GATE_SINK);
      p->look.x = zero->coord.x + (right ? PIXEL(56) : -PIXEL(56));
      p->look.y = zero->coord.y;
      s->work[2] = 64;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (!(s->work[0] & 2)) gCollisionManager.sweep = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      SET_XFLIP(zero, right);
      animate(p, 2);
      if (--s->work[2] != 0) break;
      s->work[2] = 56;
      s->mode[2]++;
      break;
    case 3:
      animate(p, 2);
      zero->coord.x += right ? 256 : -256;
      if (s->work[2] == 28) gStageRun.vm.camera.player = &p->look;
      if (--s->work[2] != 0) break;
      setSolid(p);
      PlaySound(SE_Z2_GATE_RISE);
      SetSpriteAnimation(p, DOOR_OPEN(3));
      s->work[2] = 32;
      s->mode[2]++;
      break;
    case 4:
      animate(p, 3);
      if (--s->work[2] != 0) break;
      if (GetGroundMetatileAttr(zero->coord.x, zero->coord.y) != 0) {
        zero->coord.y = FUN_0800a05c(zero->coord.x, zero->coord.y);
      }
      gStageRun.vm.unk_004 &= ~1;
      gStageRun.vm.camera.player = &zero->coord;
      ((u8*)zero)[0x119] = 0;
      LOAD_STATIC_GRAPHIC(SM028_ICE_EFFECT);
      s->mode[1] = DOOR_SETTLE;
      s->mode[2] = 0;
      break;
  }
}

// 0x080cbc30
static void Door_Settle(struct Door* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      animate(p, 3);
      if ((s->motion).state != ANIM_END) break;
      SetSpriteAnimation(p, DOOR(0));
      s->mode[2]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->work[0] & 2) && !FLAG(gCurStory.s.gameflags, FLAG_2)) {
        s->mode[1] = DOOR_SHUT;
        s->mode[2] = 0;
      }
      break;
  }
}

static const SolidFunc sStates[4] = {(SolidFunc)Door_Shut, (SolidFunc)Door_Pass, (SolidFunc)Door_Pass, (SolidFunc)Door_Settle};

// 0x080cb82c
static void Door_Update(struct Door* p) {
  struct Entity* s = &p->s;
  if (s->work[1] != 0) {
    struct Entity* near = s->unk_28;
    if (near->mode[0] >= ENTITY_DIE) {
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Door_Die(p);
    } else {
      (s->spr).sprites = (near->spr).sprites;
      (s->spr).spriteIdx = (near->spr).spriteIdx;
      (s->spr).oam.tileNum = (near->spr).oam.tileNum;
    }
    return;
  }
  (sStates[s->mode[1]])((struct Solid*)p);
}

// 0x080cb888
static void Door_Die(struct Door* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// clang-format off
static const struct Collision sCollisions[2] = {
    /* 0x834917c */ {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0, -0x2000, 0x2200, 0x4200}},
    /* 0x8349194 */ {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0, 0, 0, 0}},
};
// clang-format on

// --------------------------------------------
/*
  Zero 2's solid 5 work0 34, the Forest of Notus's door Elpizo opens. Opens on script's flag 1, shuts on 2.
  work1: 1 for far side
*/

static void ScriptDoor_Init(struct Door* p);
static void ScriptDoor_Update(struct Door* p);

// clang-format off
const SolidRoutine gApZ2ScriptDoorRoutine = {
    [ENTITY_INIT] =      (SolidFunc)ScriptDoor_Init,
    [ENTITY_UPDATE] =    (SolidFunc)ScriptDoor_Update,
    [ENTITY_DIE] =       (SolidFunc)Door_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c6020
static void ScriptDoor_Init(struct Door* p) {
  struct Entity* s = &p->s;
  struct Entity* q;
  struct PreloadEntity sheet = {AP_SHEET_Z2_DOOR, 0, 0, 0, 0, AP_PRELOAD_SHEET, 0};
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->work[1] == 0) {
    q = AllocEntityLast(gSolidHeaderPtr);
    if (q != NULL) {
      INIT_SOLID_ROUTINE(q, SOLID_Z2_SCRIPT_DOOR);
      q->work[1] = 1;
      q->coord = s->coord;
      q->unk_28 = s;
    }
    sheet.tileBase = wStaticGraphicTilenums[SM018_DOOR_2D_BLUE];
    sheet.palID = wStaticMotionPalIDs[SM018_DOOR_2D_BLUE];
    ApLoadSheet(&sheet);
  } else {
    SET_XFLIP(p, TRUE);
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  ScriptDoor_Update(p);
}

// 0x080c60e0
static void ScriptDoor_Update(struct Door* p) {
  struct Entity* s = &p->s;
  struct Entity* near = s->work[1] != 0 ? s->unk_28 : s;
  struct PreloadEntity sheet = {AP_SHEET_Z2_DOOR_OPEN, 0, 380, 0, 0, AP_PRELOAD_SHEET, 0};
  if (s->work[1] != 0 && near->mode[0] > ENTITY_UPDATE) {
    s->flags &= ~DISPLAY;
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, DOOR(0));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      animate(p, 0);
      if (!(near->scriptEntity->flags & 1)) break;
      if (s->work[1] == 0) {
        sheet.palID = wStaticMotionPalIDs[SM018_DOOR_2D_BLUE];
        ApLoadSheet(&sheet);
      }
      SetSpriteAnimation(p, DOOR(2));
      PlaySound(SE_Z2_GATE_SINK);
      s->mode[1]++;
      break;
    case 2:
      animate(p, 2);
      if (!(near->scriptEntity->flags & 2)) break;
      SetSpriteAnimation(p, DOOR_OPEN(3));
      PlaySound(SE_Z2_GATE_SINK);
      s->work[2] = 32;
      s->mode[1]++;
      break;
    case 3:
      animate(p, 3);
      if (--s->work[2] != 0) break;
      PlaySound(SE_Z2_GATE_RISE);
      s->mode[1]++;
      break;
    case 4:
      animate(p, 3);
      break;
  }
}

// --------------------------------------------
/*
  Zero 2's 3D door, solid 7 work0 1, the Power Room's pair. Up takes Zero to the other.
*/

#define DOOR3D(n) MOTION(DM210_Z2_DOOR_3D, (n))
#define AT_DOOR (1 << 30)

enum { DOOR3D_IDLE, DOOR3D_ARRIVE };
enum { IDLE_SET, IDLE_WAIT, IDLE_OPEN, IDLE_WARP, IDLE_LEAVE, IDLE_SCRIPT };

static void Door3D_Init(struct Solid* p);
static void Door3D_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2Door3DRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Door3D_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Door3D_Update,
    [ENTITY_DIE] =       (SolidFunc)Door_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};

static const struct Collision sDoor3D = /* 0x8348e94 */ {DDP, FACTION_ENEMY, DOOR_3D, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x400, 0x800, 0x800}};
static const struct Collision sDoor3DShut = /* 0x8348ef4 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}};
// clang-format on

static const Coords32 sWest = {PIXEL(4176), PIXEL(608)};
static const Coords32 sEast = {PIXEL(7344), PIXEL(608)};

static bool8 zeroAt(struct Entity* s) {
  return (u32)((pZero2->s).coord.x - s->coord.x + PIXEL(32)) <= PIXEL(64) &&
         (u32)((pZero2->s).coord.y - s->coord.y + PIXEL(32)) <= PIXEL(64);
}

// 0x080c8ea4
static void Door3D_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  (s->spr).oam.priority = 3;
  s->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, &sDoor3D, 0, NULL);
  s->coord.x += PIXEL(8);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + PIXEL(1);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = zeroAt(s) ? DOOR3D_ARRIVE : DOOR3D_IDLE;
  Door3D_Update(p);
}

// 0x080c905c
static void Door3D_Idle(struct Solid* p) {
  struct Entity* s = &p->s;
  const Coords32* to;
  switch (s->mode[2]) {
    case IDLE_SET:
      SetSpriteAnimation(p, DOOR3D(3));
      UpdateSpriteAnimation(p);
      SetDDP(&p->body, &sDoor3D);
      s->mode[2]++;
      break;
    case IDLE_WAIT:
      if (s->mode[3] == 0) {
        if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= 0x3000) {
          s->texture = 0xFF;
          s->mode[3] = 1;
        }
      } else if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x3000) {
        s->mode[3] = 0;
      }
      UpdateSpriteAnimation(p);
      if (gStageRun.missionStatus & MISSION_B1) {
        SetDDP(&p->body, &sDoor3DShut);
        s->mode[2] = IDLE_SCRIPT;
        break;
      }
      if (!gIsUsingDoor3D && !(gStageRun.vm.unk_004 & 1)) break;
      if (!((pZero2->body).status & AT_DOOR)) {
        s->mode[2] = IDLE_LEAVE;
        break;
      }
      SetSpriteAnimation(p, DOOR3D(0));
      PlaySound(SE_Z2_GATE_SINK);
      s->mode[2]++;
      break;
    case IDLE_OPEN:
      UpdateSpriteAnimation(p);
      if (s->motion.state != ANIM_END) break;
      if (!((pZero2->body).status & AT_DOOR)) {
        s->mode[1] = DOOR3D_ARRIVE;
        s->mode[2] = s->mode[3] = 0;
        break;
      }
      SetSpriteAnimation(p, DOOR3D(1));
      gStageRun.vm.transition = TRANSITION_BLACKOUT;
      s->mode[2]++;
      break;
    case IDLE_WARP:
      UpdateSpriteAnimation(p);
      if (gStageRun.vm.transition != TRANSITION_NONE) break;
      gIsUsingDoor3D = FALSE;
      gStageRun.vm.transition = TRANSITION_REVERSE;
      to = s->coord.x < PIXEL(5744) ? &sEast : &sWest;
      (pZero2->s).coord = *to;
      SET_XFLIP(pZero2, (to->x >> 8) % 240 < 120);
      resetSateliteElfPosition(pZero2);
      gStageRun.vm.camera.chaseMode = CHASE_MODE_B3;
      gStageRun.vm.camera.counter = 0;
      s->mode[2] = IDLE_SET;
      break;
    case IDLE_LEAVE:
      if (gIsUsingDoor3D || (gStageRun.vm.unk_004 & 1)) break;
      s->mode[1] = zeroAt(s) ? DOOR3D_ARRIVE : DOOR3D_IDLE;
      s->mode[2] = s->mode[3] = 0;
      break;
    case IDLE_SCRIPT:
      if (gStageRun.missionStatus & MISSION_B1) break;
      SetDDP(&p->body, &sDoor3D);
      s->mode[2] = IDLE_SET;
      break;
  }
}

// 0x080c931c: shuts behind Zero
static void Door3D_Arrive(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, DOOR3D(1));
      s->work[2] = 30;
      s->mode[2]++;
    case 1:
      UpdateSpriteAnimation(p);
      if (--s->work[2] != 0) break;
      PlaySound(SE_Z2_GATE_SINK);
      SetSpriteAnimation(p, DOOR3D(2));
      s->mode[2]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (s->motion.state != ANIM_END) break;
      s->mode[1] = DOOR3D_IDLE;
      s->mode[2] = s->mode[3] = 0;
      break;
  }
}

// 0x080c8fe0
static void Door3D_Update(struct Solid* p) {
  if ((p->s).mode[1] == DOOR3D_IDLE) {
    Door3D_Idle(p);
  } else {
    Door3D_Arrive(p);
  }
}

#endif
