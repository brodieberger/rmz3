#include "ap.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "vfx.h"

#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's spiked tower, enemy 7.
  work0:
    0: 5 sweeps before resting
    1: 3 sweeps
    2: 1 sweep
*/

struct Tower {
  OBJECT_HDR;
  Coords32 lowerArm;  // 0xB4, from tower. Upper arm is in unk_coord.
  bool8 hitFromRight;  // 0xBC
  u8 swings;           // 0xBD
  u8 side;             // 0xBE, side the arms swing out to first
  u8 maxSwings;        // 0xBF
  s32 hitHeight;       // 0xC0, its y minus attacker's
};
static_assert(sizeof(struct Tower) == sizeof(struct Enemy));

enum {
  TOWER_SWING,
  TOWER_REST,
  TOWER_FOLD,
  TOWER_AIM,
  TOWER_FIRE,
  TOWER_RECOVER,
  TOWER_RECOIL,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_TOWER, (n))

static const struct Collision sCollisions[2];
static const struct Rect sSize;
static const struct SlashedEnemy sArmGibs[2];
static const struct SlashedEnemy sBaseGib;
static const s16 sSwing[11];

static void Tower_Init(struct Tower* p);
static void Tower_Update(struct Tower* p);
static void Tower_Die(struct Tower* p);
static void createArm(struct Tower* tower, Coords32* offset);
static void createSpike(Coords32* c, bool8 right);
static void createPiece(struct Tower* tower, u8 n, u8 delay);

// clang-format off
const EnemyRoutine gApZ2TowerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Tower_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Tower_Update,
    [ENTITY_DIE] =       (EnemyFunc)Tower_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Tower* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void Tower_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Tower* p = (struct Tower*)body->parent;
    struct Entity* attacker = body->enemy->parent;
    p->hitFromRight = (attacker->coord).x > (p->s).coord.x;
    p->hitHeight = (p->s).coord.y - (attacker->coord).y;
  }
}

// 0x08069958. Solid ground, but not a wall Zero can slide down.
static void Tower_Init(struct Tower* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sCollisions, 16, Tower_OnCollision);
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sSize;
  s->physicsAttr = MTATTR_B11 | SHAPE_BLOCK;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->swings = 0;
  p->side = 0;
  p->maxSwings = s->work[0] == 0 ? 4 : s->work[0] == 1 ? 2 : 0;
  s->unk_coord.x = PIXEL(27);
  s->unk_coord.y = -PIXEL(12);
  createArm(p, &s->unk_coord);
  p->lowerArm.x = PIXEL(27);
  p->lowerArm.y = -PIXEL(44);
  createArm(p, &p->lowerArm);
  Tower_Update(p);
}

static void Tower_Recoil(struct Tower* p);
static void Tower_Swing(struct Tower* p);
static void Tower_Rest(struct Tower* p);
static void Tower_Fold(struct Tower* p);
static void Tower_Aim(struct Tower* p);
static void Tower_Fire(struct Tower* p);
static void Tower_Recover(struct Tower* p);

// 0x08069a70. Holds rest pose in stopped time.
static void Tower_Update(struct Tower* p) {
  struct Entity* s = &p->s;

  if (ApRecoilHit((Object*)p) && s->mode[1] != TOWER_RECOIL) setMode(p, TOWER_RECOIL);
  if (s->mode[1] == TOWER_RECOIL) {
    Tower_Recoil(p);
    return;
  }

  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->flags2 &= ~ENTI_PHYSICS;
    EXIT_BODY(p);
    Tower_Die(p);
    return;
  }

  if (IsFrozen(p)) setMode(p, TOWER_REST);
  switch (s->mode[1]) {
    case TOWER_SWING: Tower_Swing(p); break;
    case TOWER_REST: Tower_Rest(p); break;
    case TOWER_FOLD: Tower_Fold(p); break;
    case TOWER_AIM: Tower_Aim(p); break;
    case TOWER_FIRE: Tower_Fire(p); break;
    case TOWER_RECOVER: Tower_Recover(p); break;
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Tower_Recoil(struct Tower* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).flags2 &= ~ENTI_PHYSICS;
    EXIT_BODY(p);
    Tower_Die(p);
  }
}

static void placeArms(struct Tower* p, s32 x) {
  (p->s).unk_coord.x = x;
  p->lowerArm.x = -x;
}

// 0x08069b78: one sweep, arms going opposite ways
static void Tower_Swing(struct Tower* p) {
  struct Entity* s = &p->s;
  s32 dir;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2 + (p->swings & 1) + p->side * 2));
    if (p->swings == 0) PlaySound(SE_Z2_TOWER_SWING);
    s->work[2] = 0;
    UpdateEntityAnim(s);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  dir = (p->swings & 1) ? -1 : 1;
  if (p->side) dir = -dir;
  placeArms(p, dir * sSwing[(s->work[2] - 1) >> 1]);
  if (!IsSpriteAnimEnd(s)) return;
  if (++p->swings > p->maxSwings) {
    p->side = (p->side + 1) & 1;
    p->swings = 0;
    setMode(p, TOWER_REST);
  } else {
    setMode(p, TOWER_SWING);
  }
}

// 0x08069c58: 17 frames with arms out
static void Tower_Rest(struct Tower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(p->side));
    s->work[2] = 16;
    placeArms(p, p->side ? -PIXEL(27) : PIXEL(27));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, TOWER_FOLD);
}

// 0x08069cc4
static void Tower_Fold(struct Tower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(p->side ? 10 : 6));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(p, TOWER_AIM);
}

// 0x08069d08
static void Tower_Aim(struct Tower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(p->side ? 11 : 7));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, TOWER_FIRE);
}

static void spike(struct Tower* p, bool8 right, s32 up) {
  Coords32 c;
  c.x = (p->s).coord.x + (right ? PIXEL(13) : -PIXEL(14));
  c.y = (p->s).coord.y - up;
  createSpike(&c, right);
}

// 0x08069d58: two spikes each way, lower pair on the side the arms swung out to
static void Tower_Fire(struct Tower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    bool8 low = p->side;
    SetMotion(s, ANIM(p->side ? 12 : 8));
    PlaySound(SE_ENEMY_BOMB);
    s->work[2] = 64;
    spike(p, low, PIXEL(4));
    spike(p, low, PIXEL(20));
    spike(p, !low, PIXEL(36));
    spike(p, !low, PIXEL(52));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, TOWER_RECOVER);
}

// 0x08069e94
static void Tower_Recover(struct Tower* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(p->side ? 13 : 9));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0xFF) setMode(p, TOWER_SWING);
}

// Arm's spikes fly off where it is
static void armGibs(struct Tower* p, const Coords32* arm) {
  Coords32 c;
  const struct SlashedEnemy* gib = &sArmGibs[arm->x > 0];
  c.x = (p->s).coord.x + arm->x;
  c.y = (p->s).coord.y + arm->y - PIXEL(12);
  useApSheets(CreateSlashedEnemy(&c, gib, 0, 0));
  c.y += PIXEL(16);
  useApSheets(CreateSlashedEnemy(&c, gib, 0, 0));
}

// 0x08069ee4: four pieces burst one by one from the end that was hit
static void Tower_Die(struct Tower* p) {
  struct Entity* s = &p->s;
  switch (s->mode[3]) {
    case 0: {
      u8 n;
      bool8 low = p->hitHeight < PIXEL(32);
      SetMotion(s, ANIM(24));
      for (n = 0; n < 4; n++) createPiece(p, n, low ? n * 8 : 24 - n * 8);
      s->work[2] = low ? 24 : 0;
      armGibs(p, &s->unk_coord);
      armGibs(p, &p->lowerArm);
      s->coord.y -= PIXEL(64);
      s->mode[3]++;
      break;
    }
    case 1:
      if (--s->work[2] != 0xFF) break;
      s->d.y = -0x300;
      s->mode[3]++;
      // fallthrough
    case 2: {
      Coords32 c;
      if (s->work[2]++ & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y) == 0) break;
      c.x = s->coord.x;
      c.y = FUN_08009f6c(s->coord.x, s->coord.y);
      useApSheets(CreateSlashedEnemy(&c, &sBaseGib, 0, 0));
      useApSheets(CreateSlashedEnemy(&c, &sBaseGib, 0, 1));
      c.y -= PIXEL(4);
      CreateSmoke(1, &c);
      PlaySound(SE_ZAKO_EXPLODE);
      TryDropItem(4, (struct Coord*)&s->coord);
      if (gScore.enemyCount < 9999) gScore.enemyCount++;
      ApImportTowerKilled();
      TryDropZakoDisk((struct Enemy*)p, &s->coord);
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
    }
  }
  UpdateEntityAnim(s);
}

// --------------------------------------------
// Arm, Zero 2's projectile 3. Invisible shield with a spiked edge.

struct Arm {
  OBJECT_HDR;
  const Coords32* offset;  // 0xB4, in tower
  u8 _[12];
};
static_assert(sizeof(struct Arm) == sizeof(struct Projectile));

static const struct Collision sArm[2];

static void Arm_Init(struct Arm* p);
static void Arm_Update(struct Arm* p);

// clang-format off
const ProjectileRoutine gApZ2TowerArmRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Arm_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Arm_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x08098b24
static void createArm(struct Tower* tower, Coords32* offset) {
  struct Arm* p = (struct Arm*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_TOWER_ARM);
    (p->s).unk_28 = &tower->s;
    p->offset = offset;
  }
}

// 0x08098b7c
static void Arm_Init(struct Arm* p) {
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, sArm, 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Arm_Update(p);
}

// 0x08098bf4
static void Arm_Update(struct Arm* p) {
  struct Entity* tower = (p->s).unk_28;
  if (tower->mode[0] > ENTITY_UPDATE) {
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  (p->s).coord.x = tower->coord.x + p->offset->x;
  (p->s).coord.y = tower->coord.y + p->offset->y;
}

// --------------------------------------------
// Spike, Zero 2's projectile 4

static const struct Collision sSpike[2];

static void Spike_Init(struct Entity* p);
static void Spike_Update(struct Entity* p);
static void Spike_Die(struct Entity* p);

// clang-format off
const ProjectileRoutine gApZ2TowerSpikeRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Spike_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Spike_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Spike_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x08098c90
static void createSpike(Coords32* c, bool8 right) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_TOWER_SPIKE);
    p->coord = *c;
    p->work[0] = right;
  }
}

// 0x08098ce4
static void Spike_Init(struct Entity* p) {
  bool8 right = p->work[0] & 1;
  InitNonAffineMotion(p);
  useApSheets(p);
  p->flags |= DISPLAY | FLIPABLE;
  SetMotion(p, ANIM(14));
  UpdateEntityAnim(p);
  SET_XFLIP(p, right);
  p->renderPrio = 31;
  p->d.x = right ? 0x300 : -0x300;
  p->d.y = 0;
  INIT_BODY(p, sSpike, 1, NULL);
  p->work[2] = 255;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Spike_Update(p);
}

// 0x08098dac
static void Spike_Update(struct Entity* p) {
  if (--p->work[2] == 0xFF || (((Object*)p)->body.status & BODY_STATUS_B2) ||
      FUN_080098a4(p->coord.x, p->coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Spike_Die(p);
    return;
  }
  p->coord.x += p->d.x;
}

// 0x08098e54
static void Spike_Die(struct Entity* p) {
  CreateSmoke(3, &p->coord);
  p->flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Tower piece, Zero 2's VFX 18. work[1] is the side hit from, work[2] the delay.

static const struct SlashedEnemy sPieceGibs[3];

static void Piece_Init(struct VFX* p);
static void Piece_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2TowerPieceRoutine = {
    [ENTITY_INIT] =      Piece_Init,
    [ENTITY_UPDATE] =    Piece_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b140c
static void createPiece(struct Tower* tower, u8 n, u8 delay) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_TOWER_PIECE);
    (p->s).coord = (tower->s).coord;
    (p->s).work[0] = n;
    (p->s).work[1] = tower->hitFromRight;
    (p->s).work[2] = delay;
  }
}

// 0x080b146c
static void Piece_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(23));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  s->coord.y -= s->work[0] << 12;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Piece_Update(p);
}

// 0x080b14e4, 0x080b1550. A CreateSlashedEnemy flag byte is (mirrored << 4) | thrown right.
static void Piece_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  u8 away;
  UpdateEntityAnim(s);
  if (--s->work[2] != 0xFF) return;
  away = (s->work[1] ? ~s->work[0] : s->work[0]) & 1;
  c = s->coord;
  useApSheets(CreateSlashedEnemy(&c, &sPieceGibs[0], 0, away));
  useApSheets(CreateSlashedEnemy(&c, &sPieceGibs[1 + (RANDOM(RNG_0202f388) & 1)], 0, (u8)~away));
  c.y -= PIXEL(4);
  CreateSmoke(1, &c);
  c.x += -PIXEL(8) + (RANDOM(RNG_0202f388) & 0xFFF);
  c.y -= RANDOM(RNG_0202f388) & 0xFFF;
  CreateSmoke(2, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x04, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, -0x2300, 0x1800, 0x4e00}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x1c00, 0x1a00, 0x4000}},
};

static const struct Rect sSize = {0x0, -0x2300, 0x1800, 0x4e00};

static const s16 sSwing[11] = {6912, 6656, 5888, 4352, 2048, 0, -2048, -4352, -5888, -6656, -6656};

static const struct Collision sArm[2] = {
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, METAL, 0, 1, 0xffffffff, {0x0, 0x0, 0x800, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x2000}},
};

static const struct Collision sSpike[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct SlashedEnemy sArmGibs[2] = {
    {MOTION(AP_SHEET_Z2_TOWER, 19), {0xff, 0x11}, {0, 0}, {0, -1024}, {0, 0}, {0, 64}, {0x400, 0x800}, {0}},
    {MOTION(AP_SHEET_Z2_TOWER, 20), {0xfe, 0x11}, {0, 0}, {0, -1024}, {0, 0}, {0, 64}, {0x400, 0x800}, {0}},
};

static const struct SlashedEnemy sBaseGib =
    {MOTION(AP_SHEET_Z2_TOWER, 22), {0xff, 0x11}, {0, 0}, {512, -768}, {255, 255}, {0, 64}, {0x400, 0x0}, {0}};

static const struct SlashedEnemy sPieceGibs[3] = {
    {MOTION(AP_SHEET_Z2_TOWER, 16), {0xff, 0x11}, {0, 0}, {256, -768}, {255, 511}, {0, 64}, {0xf00, 0x800}, {0}},
    {MOTION(AP_SHEET_Z2_TOWER, 17), {0xfe, 0x11}, {0, 0}, {-640, -1024}, {255, 511}, {0, 64}, {0x800, 0x800}, {0}},
    {MOTION(AP_SHEET_Z2_TOWER, 18), {0xfe, 0x11}, {0, 0}, {384, -1024}, {255, 511}, {0, 64}, {0x800, 0x800}, {0}},
};
// clang-format on

#endif  // AP
