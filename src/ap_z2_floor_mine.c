#include "ap.h"
#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "sound.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"

#if AP

/*
  Zero 2's projectile 54, a mine on the floor. Set off by a hit, anything but Zero touching it,
  or Zero standing on it.
  work0: 0 the mine, 1 its blast
*/

struct Mine {
  OBJECT_HDR;
  bool8 touched;  // 0xB4
  u8 _b5[15];
};
static_assert(sizeof(struct Mine) == sizeof(struct Projectile));

static void Mine_Init(struct Mine* p);
static void Mine_Update(struct Mine* p);
static void Mine_Die(struct Mine* p);

// clang-format off
const ProjectileRoutine gApZ2FloorMineRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Mine_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Mine_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Mine_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083455e4, 0x08345614
static const struct Collision sMine[2] = {
    {DDP, FACTION_NEUTRAL, 0, 255, 0x00, 0x00, 0x00, 0x00, 0xff, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_NEUTRAL, 0, 255, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};
static const struct Collision sBlast[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

#define MINE(n) MOTION(AP_SHEET_Z2_FLOOR_MINE, (n))

// 0x080aa220
static void createBlast(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FLOOR_MINE);
    p->coord = *at;
    p->work[0] = 1;
    p->work[1] = 0;
  }
}

// 0x080aa4d0
static void onTouch(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Entity* other = (body->enemy)->parent;
  if (!(body->hitboxFlags & BODY_STATUS_B2)) return;
  if (other->kind != ENTITY_PLAYER || other->mode[1] == ZERO_GROUND) ((struct Mine*)body->parent)->touched = TRUE;
}

// 0x080aa278
static void Mine_Init(struct Mine* p) {
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  if (s->work[0] == 0) {
    s->texture = TEXTURE_AP_SHEET;
    SET_XFLIP(p, FALSE);
    SetSpriteAnimation(p, MINE(0));
    s->flags |= DISPLAY;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    p->touched = FALSE;
    INIT_BODY(p, sMine, 64, onTouch);
  } else {
    s->palID = 0;
    SetSpriteAnimation(p, MOTION(SM000_BATTLE_EFFECT, 1));
    s->flags |= DISPLAY;
    INIT_BODY(p, sBlast, 64, NULL);
    PlaySound(SE_Z2_TANK_EXPLODE);
  }
  s->flags |= FLIPABLE;
  Mine_Update(p);
}

// 0x080aa358: blinks six frames once set off
static void Mine_Update(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 1) {
    UpdateSpriteAnimation(p);
    if (!IsSpriteAnimEnd(s)) return;
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->mode[1] == 0) {
    UpdateSpriteAnimation(p);
    if (p->touched || ((p->body).status & BODY_STATUS_WHITE)) {
      EXIT_BODY(p);
      s->mode[1]++;
      s->mode[2] = 0;
    }
    return;
  }
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MINE(1));
    s->work[2] = 6;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] != 0) return;
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Mine_Die(p);
}

// 0x080aa464
static void Mine_Die(struct Mine* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  at.x = s->coord.x;
  at.y = s->coord.y - PIXEL(8);
  createBlast(&at);
  ApImportFloorMineKilled();
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

#endif  // AP
