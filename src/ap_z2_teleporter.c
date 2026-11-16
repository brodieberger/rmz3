#include "ap.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's solid 23, Yggdrasil's teleporters to the refight rooms. Dark once that fight is won.
  work0: fight - 1
*/

#define TELEPORTER(n) MOTION(AP_SHEET_Z2_TELEPORTER, (n))

// clang-format off
// 0x08349a10
static const struct Collision sBody[2] = {
    {DDP, FACTION_ENEMY, CS_TELEPORTAL, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x400, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, CS_TELEPORTAL, 255, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

// 0x08326024
static const Coords32 sRooms[6] = {
    {PIXEL(1968), PIXEL(1856)}, {PIXEL(1840), PIXEL(3184)}, {PIXEL(1840), PIXEL(2528)},
    {PIXEL(1776), PIXEL(380)},  {PIXEL(2760), PIXEL(448)},  {PIXEL(1728), PIXEL(1104)},
};

// 0x080cf346
static void Teleporter_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  switch (s->mode[2]) {
    case 0:
      if (!(gStageRun.unk_0a & (1 << s->work[0]))) {
        SetMotion(s, TELEPORTER(1));
        s->flags |= COLLIDABLE;
        INIT_BODY(p, sBody, 0, NULL);
      } else {
        SetMotion(s, TELEPORTER(0));
        EXIT_BODY(p);
        s->flags &= ~COLLIDABLE;
      }
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (!gInTransport && !(gStageRun.vm.unk_004 & 1)) break;
      if (!((p->body).status & BODY_STATUS_TELEPORTAL)) break;
      gStageRun.vm.unk_004 |= 1 << 1;
      s->work[2] = 30;
      s->mode[2]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      SetMotion(s, TELEPORTER(2));
      s->work[2] = 20;
      s->mode[2]++;
      break;
    case 3:
      UpdateEntityAnim(s);
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      Camera_SetMode(&gStageRun.vm.camera, CM1);
      z->coord = sRooms[s->work[0]];
      z->spr.xflip = TRUE, z->spr.oam.xflip = TRUE;
      z->flags |= X_FLIP;
      resetSateliteElfPosition(pZero2);
      s->work[2] = 90;
      s->mode[2]++;
      break;
    case 4:
      UpdateEntityAnim(s);
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      PlaySound(SE_TENSOU_BACK);
      SetMotion(s, TELEPORTER(3));
      gStageRun.vm.transition = TRANSITION_BLACKOUT;
      s->mode[2]++;
      break;
    case 5:
      UpdateEntityAnim(s);
      if (gStageRun.vm.transition != TRANSITION_NONE) break;
      Camera_SetMode(&gStageRun.vm.camera, CM6);
      gStageRun.vm.camera.chaseMode = CHASE_MODE_B3;
      gStageRun.vm.camera.counter = 0;
      gInTransport = FALSE;
      gStageRun.vm.transition = TRANSITION_REVERSE;
      // Rides hidden with Zero so it isn't culled once camera moves
      s->unk_coord = s->coord;
      s->coord = z->coord;
      s->flags &= ~DISPLAY;
      s->work[2] = 8;
      s->mode[2]++;
      break;
    case 6:
      // Script waits for camera to snap, then spawns snake, his room's floor
      UpdateEntityAnim(s);
      gStageRun.vm.unk_004 &= ~(1 << 1);
      if (--s->work[2] != 0) break;
      // Zero lands where he is, Panter's room has no terrain. A subpixel up, out of the floor
      z->coord.y--;
      PlaySound(SE_TENSOU);
      SetMotion(z, MOTION(DM053_ZERO_TELEPORT_END, 2));
      resetSateliteElfPosition(pZero2);
      z->mode[1] = 10, z->mode[2] = 4, z->mode[3] = 1;
      s->coord = s->unk_coord;
      s->flags |= DISPLAY;
      s->mode[2] = 0;
      break;
  }
}

// 0x080cf28c
static void Teleporter_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->spr.oam.priority = 1;
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.x += PIXEL(8);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) + PIXEL(1);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = 0, s->mode[2] = s->mode[3] = 0;
  Teleporter_Update(p);
}

// 0x080cf30c
static void Teleporter_Die(struct Solid* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~(DISPLAY | COLLIDABLE);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// clang-format off
const SolidRoutine gApZ2TeleporterRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Teleporter_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Teleporter_Update,
    [ENTITY_DIE] =       (SolidFunc)Teleporter_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

#endif  // AP
