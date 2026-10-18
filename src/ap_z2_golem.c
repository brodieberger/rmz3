#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "projectile.h"
#include "random.h"
#include "script.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's Golem Type E, boss 9. This one specifically is the hidden boss in Crystal Caves.
*/

struct Golem {
  OBJECT_HDR;
  s32 homeX;        // 0xB4
  s32 homeY;        // 0xB8
  u8 _bc;
  u8 sway;          // 0xBD
  bool8 oddFire;    // 0xBE, side 1 arms are firing, until its shoulder is done
  bool8 evenFire;   // 0xBF, side 0 arms are firing
  u16 dying;        // 0xC0
  u8 _[34];
};
static_assert(sizeof(struct Golem) == sizeof(struct Boss));

enum { GOLEM_WAIT, GOLEM_FIGHT, GOLEM_2, GOLEM_CHOOSE, GOLEM_PAUSE, GOLEM_FIRE_ODD, GOLEM_FIRE_EVEN };

static const struct Collision sGolemCollisions[2];
static const struct Collision sGolemIntroCollisions[2];
static const struct Collision sShoulderCollisions[4];
static const struct Collision sArmCollisions[2];
static const struct Collision sLaserCollisions[2];
static const struct Collision sBeamCollisions[2];
static const Coords32 sElementCoord = {0, -PIXEL(48)};

static void Golem_Init(struct Golem* p);
static void Golem_Update(struct Golem* p);
static void Golem_Die(struct Golem* p);
static void createArm(struct Golem* golem, bool8 arm, u8 side);
static void createFeet(struct Golem* golem);

// clang-format off
const BossRoutine gApZ2GolemRoutine = {
    [ENTITY_INIT] =      (BossFunc)Golem_Init,
    [ENTITY_UPDATE] =    (BossFunc)Golem_Update,
    [ENTITY_DIE] =       (BossFunc)Golem_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* p, u8 mode) {
  p->mode[1] = mode;
  p->mode[2] = 0;
}

static bool8 dying(struct Entity* parent) { return parent->mode[0] > ENTITY_UPDATE; }

// 0x0804d028
static void Golem_Init(struct Golem* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM, 1));
  UpdateSpriteAnimation(p);
  ResetBossBody((struct Boss*)p, sGolemIntroCollisions, 16);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  p->sway = 0;
  p->oddFire = p->evenFire = FALSE;
  s->unk_2c = NULL;
  createArm(p, FALSE, 0);
  createArm(p, FALSE, 1);
  createFeet(p);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Golem_Update(p);
}

static const BossFunc sGolemUpdates[7];

// 0x0804d208
static void Golem_Update(struct Golem* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Golem_Die(p);
    return;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(13, (Object*)p, (const struct Coord*)&sElementCoord);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;

  (sGolemUpdates[s->mode[1]])((struct Boss*)p);

  p->sway += 2;
  if (s->mode[1] != GOLEM_WAIT) s->coord.x = p->homeX - SIN(p->sway * 2) * 2;
  s->coord.y = p->homeY - SIN(p->sway) * 2;
}

// 0x0804d46c
static void Golem_Wait(struct Golem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) setMode(s, GOLEM_FIGHT);
}

// 0x0804d4ec
static void Golem_Fight(struct Golem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sGolemCollisions);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!(gStageRun.vm.active & VM_ACTIVE)) {
    s->mode[1] = GOLEM_PAUSE, s->mode[2] = 1;
    s->work[2] = 16;
  }
}

static void Golem_Nothing(struct Golem* p UNUSED) {}

// 0x0804d538
static void Golem_Choose(struct Golem* p) {
  UpdateSpriteAnimation(p);
  setMode(&p->s, (RANDOM(RNG_0202f388) & 1) ? GOLEM_FIRE_ODD : GOLEM_FIRE_EVEN);
}

// 0x0804d57c
static void Golem_Pause(struct Golem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 1;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, GOLEM_CHOOSE);
}

// 0x0804d5b0, 0x0804d5e4
static void Golem_FireOdd(struct Golem* p) {
  if ((p->s).mode[2] == 0) {
    p->oddFire = TRUE;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!p->oddFire) setMode(&p->s, GOLEM_PAUSE);
}

static void Golem_FireEven(struct Golem* p) {
  if ((p->s).mode[2] == 0) {
    p->evenFire = TRUE;
    (p->s).mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!p->evenFire) setMode(&p->s, GOLEM_PAUSE);
}

static const BossFunc sGolemUpdates[7] = {
    [GOLEM_WAIT] = (BossFunc)Golem_Wait,
    [GOLEM_FIGHT] = (BossFunc)Golem_Fight,
    [GOLEM_2] = (BossFunc)Golem_Nothing,
    [GOLEM_CHOOSE] = (BossFunc)Golem_Choose,
    [GOLEM_PAUSE] = (BossFunc)Golem_Pause,
    [GOLEM_FIRE_ODD] = (BossFunc)Golem_FireOdd,
    [GOLEM_FIRE_EVEN] = (BossFunc)Golem_FireEven,
};

static void explode(struct Golem* p, Coords32* c, u8 kind) {
  struct Entity* e = AllocEntityLast(gVFXHeaderPtr);
  if (e != NULL) {
    INIT_VFX_ROUTINE(e, VFX_BOSS_EXPLOSION);
    e->unk_28 = &p->s;
    e->coord = *c;
    e->work[0] = 2;
    e->work[1] = kind;
  }
}

static void Golem_Die(struct Golem* p) {
  struct Entity* s = &p->s;
  u16 t;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM, 0));
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    p->dying = 0;
    s->work[2] = 24;
    s->work[3] = 12;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);

  t = p->dying++;
  if (t > 64) {
    if ((p->dying & 3) == 0) {
      Coords32 c;
      c.x = s->coord.x + ((32 - (RANDOM(RNG_0202f388) & 63)) << 8);
      c.y = s->coord.y - (((RANDOM(RNG_0202f388) & 63) + 32) << 8);
      explode(p, &c, RANDOM(RNG_0202f388));
    }
    if ((p->dying & 15) == 0) PlaySound(SE_UNK_35);
  }

  if (s->mode[1] != 0) {
    if (p->dying & 1) {
      PaintEntityWhite(s);
    } else {
      UpdateEntityPaletteID(s);
    }
  } else if (--s->work[3] == 0xFF) {
    PaintEntityWhite(s);
    if (--s->work[2] == 0xFF) {
      gStageRun.vm.active |= VM_FLAG1;
      s->mode[1]++;
    }
    s->work[3] = s->work[2] >> 1;
  } else {
    UpdateEntityPaletteID(s);
  }
}

// --------------------------------------------
// Arms, Zero 2 enemy 23.

#define ARM_SIDE(e) ((e)->work[1] & 1)

static void Arm_Init(struct Enemy* p);
static void Arm_Update(struct Enemy* p);
static void Arm_Die(struct Enemy* p);
static void createLaser(struct Entity* parent, u8 side, u8 kind);

// clang-format off
const EnemyRoutine gApZ2GolemArmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Arm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Arm_Update,
    [ENTITY_DIE] =       (EnemyFunc)Arm_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

enum { ARM_WAIT, ARM_FIRE, ARM_HOLD, ARM_RETRACT };

// 0x08073a0c
static void createArm(struct Golem* golem, bool8 arm, u8 side) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_GOLEM_ARM);
    p->unk_28 = &golem->s;
    p->work[0] = arm;
    p->work[1] = side;
  }
}

static struct Golem* golemOf(struct Enemy* p) { return (struct Golem*)(p->s).unk_28; }

static void armMotion(struct Enemy* p) {
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_ARM, (ARM_SIDE(&p->s) ? 2 : 3)));
}

// 0x08073bf4, 0x08073cf4
static void Arm_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Golem* golem = golemOf(p);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_ARM, (s->work[1] ? 4 : 5)));
    if (s->work[1]) s->renderPrio = 25;
  } else {
    armMotion(p);
    if (ARM_SIDE(s)) s->renderPrio = 25;
  }
  UpdateSpriteAnimation(p);
  s->invincibleID = (golem->s).uniqueID;
  SET_XFLIP(p, ((golem->s).flags & X_FLIP) != 0);
  if (s->work[0] == 0) {
    INIT_BODY(p, &sShoulderCollisions[s->work[1] * 2], 1, NULL);
    createArm(golem, TRUE, s->work[1]);
    createArm(golem, TRUE, s->work[1] + 2);
  } else {
    s->angle = 0;
    INIT_BODY(p, sArmCollisions, 1, NULL);
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Arm_Update(p);
}

static void followGolem(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Golem* golem = golemOf(p);
  bool8 right = (s->flags & X_FLIP) != 0;
  s32 bob = SIN(golem->sway + 192) * 2;
  if (s->work[0] == 0) {
    s->coord.x = (golem->s).coord.x;
    s->coord.y = golem->homeY - bob;
    return;
  }
  if (ARM_SIDE(s)) {
    s->coord.x = (golem->s).coord.x + (right ? PIXEL(33) : -PIXEL(33));
  } else {
    s->coord.x = (golem->s).coord.x + (right ? -PIXEL(34) : PIXEL(34));
  }
  s->coord.y = golem->homeY - (bob + (s->work[1] < 2 ? PIXEL(78) : PIXEL(32)));
}

// 0x08073ef8
static void Arm_Wait(struct Enemy* p) {
  struct Golem* golem = golemOf(p);
  if (ARM_SIDE(&p->s) ? golem->oddFire : golem->evenFire) setMode(&p->s, ARM_FIRE);
}

// 0x08073f30
static void Arm_Fire(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->work[0] == 0) {
      createLaser(s, ARM_SIDE(s), 1);
      PlaySound(SE_ELECTRIC_PANTHEON);
    } else {
      InitRotatableMotion(s);
      armMotion(p);
      createLaser(s, ARM_SIDE(s), s->work[1] < 2 ? 0 : 2);
    }
    s->work[2] = 48;
    s->mode[2]++;
  }
  if (s->work[0] != 0) {
    switch (s->work[1]) {
      case 0:
        if ((u8)--s->angle < 244) s->angle = 244;
        break;
      case 1:
        if (s->angle < 14) s->angle++;
        break;
      case 2:
        if (s->angle < 12) s->angle++;
        break;
      case 3:
        if ((u8)--s->angle < 242) s->angle = 242;
        break;
    }
  }
  if (--s->work[2] == 0xFF) setMode(s, ARM_HOLD);
}

// 0x08074030
static void Arm_Hold(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 48;
    s->mode[2]++;
  }
  if (--s->work[2] == 0xFF) setMode(s, ARM_RETRACT);
}

// 0x08074060: 
static void Arm_Retract(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 48;
    s->work[3] = 0;
    s->mode[2]++;
  }
  if (s->work[0] != 0) {
    if (s->work[1] == 1 || s->work[1] == 2) {
      if (s->angle != 0) s->angle--;
    } else if (s->angle != 0) {
      s->angle++;
    }
  }
  if (s->work[3] == 0 && s->angle == 0) {
    if (s->work[0] != 0) {
      InitNonAffineMotion(s);
      armMotion(p);
    }
    s->work[3]++;
  }
  if (--s->work[2] == 0xFF) {
    if (s->work[0] == 0) {
      if (s->work[1]) {
        golemOf(p)->oddFire = FALSE;
      } else {
        golemOf(p)->evenFire = FALSE;
      }
    }
    setMode(s, ARM_WAIT);
  }
}

static const EnemyFunc sArmUpdates[4] = {
    [ARM_WAIT] = (EnemyFunc)Arm_Wait,
    [ARM_FIRE] = (EnemyFunc)Arm_Fire,
    [ARM_HOLD] = (EnemyFunc)Arm_Hold,
    [ARM_RETRACT] = (EnemyFunc)Arm_Retract,
};

// 0x08073a84
static void Arm_Update(struct Enemy* p) {
  if (dying(&golemOf(p)->s)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Arm_Die(p);
    return;
  }
  followGolem(p);
  (sArmUpdates[(p->s).mode[1]])(p);
  UpdateSpriteAnimation(p);
}

// 0x08073afc
static void Arm_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    if (s->work[0] == 0) {
      s->work[2] = 16;
    } else {
      s->work[2] = s->work[1] < 2 ? 0 : 32;
    }
    if (s->work[1] != 0) s->work[2] += 8;
    s->d.y = 0;
    s->mode[2]++;
  }
  if (s->mode[1] == 0) {
    s->coord.y += (s->work[2] & 3) ? -0x80 : 0x80;
    if (--s->work[2] == 0xFF) s->mode[1]++;
    return;
  }
  s->d.y += 0x40;
  s->coord.y += s->d.y;
  if (s->work[0] == 0) {
    Coords32 c;
    c.x = s->coord.x, c.y = s->coord.y - PIXEL(48);
    if (FUN_080098a4(c.x, c.y) == 0) return;
    CreateSmoke(1, &c);
  } else {
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    CreateSmoke(1, &s->coord);
  }
  PlaySound(SE_ZAKO_EXPLODE);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Feet, Zero 2 VFX 28

static void Foot_Init(struct Entity* p);
static void Foot_Update(struct Entity* p);
static void Foot_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2GolemFootRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Foot_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Foot_Update,
    [ENTITY_DIE] =       (VFXFunc)Foot_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b48c8
static void createFeet(struct Golem* golem) {
  u8 i;
  if (gVFXHeaderPtr->remaining <= 1) return;
  for (i = 0; i < 2; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    INIT_VFX_ROUTINE(p, VFX_Z2_GOLEM_FOOT);
    p->work[0] = i;
    p->unk_28 = &golem->s;
  }
}

// 0x080b4960
static void Foot_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  useApSheets(p);
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_FOOT, (p->work[0] ? 0 : 1)));
  p->flags |= DISPLAY;
  p->renderPrio = 24;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Foot_Update(p);
}

// 0x080b49b4
static void Foot_Update(struct Entity* p) {
  struct Entity* golem = p->unk_28;
  bool8 right = (golem->flags & X_FLIP) != 0;
  if (dying(golem)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Foot_Die(p);
    return;
  }
  if (p->work[0]) {
    (p->coord).x = (golem->coord).x + (right ? -PIXEL(16) : PIXEL(16));
  } else {
    (p->coord).x = (golem->coord).x + (right ? PIXEL(13) : -PIXEL(13));
  }
  (p->coord).y = FUN_08009f6c((p->coord).x, (golem->coord).y);
  UpdateSpriteAnimation(p);
}

static void Foot_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Laser, Zero 2 projectile 46

static void Laser_Init(struct Projectile* p);
static void Laser_Update(struct Projectile* p);
static void Laser_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2GolemLaserRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Laser_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Laser_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Laser_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

enum { LASER_SPARK, LASER_CHARGE, LASER_CHARGING, LASER_FLASH, LASER_FLASHING, LASER_FIRE, LASER_FLY };

#define LASER_KIND(s) ((s)->work[1])
#define SHOULDER_LASER 1
#define LOWER_LASER 2

// 0x080a86cc
static void createLaser(struct Entity* parent, u8 side, u8 kind) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_GOLEM_LASER);
    p->unk_28 = parent;
    p->work[0] = side;
    p->work[1] = kind;
  }
}

// 0x080a871c
static void Laser_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_LASER, 5));
  UpdateSpriteAnimation(p);
  if (s->work[0]) s->palID = 1;  // Takes effect from its next animation, like in Zero 2
  SET_XFLIP(p, (s->unk_28->flags & X_FLIP) != 0);
  INIT_BODY(p, sLaserCollisions, 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Laser_Update(p);
}

static void Laser_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

static void killLaser(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Laser_Die(p);
}

// 0x080a87d0
static void followArm(struct Entity* s, struct Entity* arm) {
  bool8 right = (s->flags & X_FLIP) != 0;
  if (LASER_KIND(s) == SHOULDER_LASER) {
    if (s->work[0]) {
      s->coord.x = (arm->coord).x + (right ? PIXEL(56) : -PIXEL(56));
    } else {
      s->coord.x = (arm->coord).x + (right ? -PIXEL(26) : PIXEL(26));
    }
    s->coord.y = (arm->coord).y - PIXEL(55);
  } else {
    s32 out = COS(arm->angle) * 12;
    s->coord.x = (arm->coord).x + (right ? out : -out);
    s->coord.y = (arm->coord).y - SIN(arm->angle) * 12;
  }
}

static void Laser_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* arm = s->unk_28;
  if (dying(arm)) {
    s->flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->mode[1] <= LASER_FIRE) followArm(s, arm);

  switch (s->mode[1]) {
    case LASER_SPARK:
    case LASER_FLASHING:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[1]++;
      break;

    case LASER_CHARGE:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_LASER, (LASER_KIND(s))));
      s->work[2] = 32;
      s->mode[1]++;
      // fallthrough
    case LASER_CHARGING:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;

    case LASER_FLASH:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_LASER, 3));
      s->mode[1]++;
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[1]++;
      break;

    case LASER_FIRE:
      if (LASER_KIND(s) != SHOULDER_LASER) {
        InitRotatableMotion(s);
        s->angle = arm->angle;
      }
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_GOLEM_LASER, 4));
      SetDDP(&p->body, sBeamCollisions);
      PlaySound(SE_REFLECT_LASER);
      s->work[2] = 64;
      s->mode[1]++;
      // fallthrough
    case LASER_FLY:
      UpdateSpriteAnimation(p);
      if (LASER_KIND(s) != SHOULDER_LASER) {
        s32 dx = COS(s->angle) * 4;
        s->coord.x += (s->flags & X_FLIP) ? dx : -dx;
        s->coord.y -= SIN(s->angle) * 4;
      } else {
        s->coord.x += (s->flags & X_FLIP) ? PIXEL(4) : -PIXEL(4);
      }
      if (LASER_KIND(s) == LOWER_LASER &&
          FUN_080098a4(s->coord.x - COS(s->angle) * 26, s->coord.y - SIN(s->angle) * 26) != 0) {
        killLaser(p);
        return;
      }
      if (--s->work[2] == 0xFF) killLaser(p);
      break;
  }
}

// --------------------------------------------
// Zero 2 data.

// clang-format off
static const struct Collision sGolemCollisions[2] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x06, 0x00, 0, 1, 0x00000001, {0x400, -0x2600, 0x3a00, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0, 0, 0x00000000, {0x600, -0x5000, 0x3400, 0x2400}},
};

// While its script runs: hurts to touch and cannot be hurt
static const struct Collision sGolemIntroCollisions[2] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x400, -0x2600, 0x3a00, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x600, -0x5000, 0x3400, 0x2400}},
};

// By side: hurt to touch and cannot be hurt
static const struct Collision sShoulderCollisions[4] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x2000, -0x3600, 0x1c00, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x1e00, -0x3600, 0x1c00, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sArmCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x1c00, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sLaserCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sBeamCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x1600, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

#endif  // AP
