#include "ap.h"
#include "ap_import.h"
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
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's flame Golem, boss 22.
*/

struct FlameGolem {
  OBJECT_HDR;
  s32 homeX;       // 0xB4
  s32 homeY;       // 0xB8
  u8 _bc;
  u8 sway;         // 0xBD
  bool8 armsOut[2];// 0xBE, by arm, until each is done
  u16 dying;       // 0xC0
  u8 turn;         // 0xC2, lobbing or jets
  u8 armSway;      // 0xC3
  u8 _c4[12];
  u8 lobs;         // 0xD0
  u8 _d1[19];
};
static_assert(sizeof(struct FlameGolem) == sizeof(struct Boss));

// Zero 2's enemy 68
struct FlameArm {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  s32 homeY;  // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct FlameArm) == 196);

/*
  Zero 2's projectile 52.
  work0:
    0: nozzle on arm
    1: jet, unseen, makes flames
    2: flame turning around jet
*/
struct FlameJet {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  s32 homeY;  // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct FlameJet) == 196);

enum { FLAME_WAIT, FLAME_STIR, FLAME_NOP, FLAME_CHOOSE, FLAME_PAUSE, FLAME_OPEN, FLAME_LOB, FLAME_CLOSE, FLAME_ARMS };
enum { ARM_WAIT, ARM_SWING, ARM_BACK, ARM_SHAKE, ARM_HOME };

#define BODY(n) MOTION(AP_SHEET_Z2_FLAME_GOLEM, (n))
#define FIRE(n) MOTION(AP_SHEET_Z2_FLAME_GOLEM_FIRE, (n))

#define CAST(p) ((struct FlameGolem*)(p)->s.unk_28)

static const struct Collision sCollisions[4];
static const struct Collision sArmCollisions[2];
static const struct Collision sFireCollisions[4];
static const struct Collision sJetCollisions[2];
static const struct Coord sElementCoord = {0, -PIXEL(48)};

static const struct PreloadEntity sSheets[3] = {
    {AP_SHEET_Z2_FLAME_GOLEM, 0, 512, 4, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_FLAME_GOLEM_FIRE, 0, 512 + AP_SHEET_Z2_FLAME_GOLEM_TILES, 5, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_FLAME_GOLEM_FOOT, 0, 512 + AP_SHEET_Z2_FLAME_GOLEM_TILES + AP_SHEET_Z2_FLAME_GOLEM_FIRE_TILES, 7, 0, AP_PRELOAD_SHEET, 0},
};

static void Flame_Init(struct FlameGolem* p);
static void Flame_Update(struct FlameGolem* p);
static void Flame_Die(struct FlameGolem* p);
static void createArm(struct FlameGolem* boss, u8 side);
static void createFire(struct Entity* parent, u8 kind, u8 n);
static void createJet(struct Entity* parent, u8 kind, u8 n);

// clang-format off
const BossRoutine gApZ2FlameGolemRoutine = {
    [ENTITY_INIT] =      (BossFunc)Flame_Init,
    [ENTITY_UPDATE] =    (BossFunc)Flame_Update,
    [ENTITY_DIE] =       (BossFunc)Flame_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void useSheet(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 dying(struct Entity* e) { return e->mode[0] > ENTITY_UPDATE; }

// 0x08063870
static void Flame_Init(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  u8 i;
  for (i = 0; i < 3; i++) {
    ApLoadSheet(&sSheets[i]);
  }
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, BODY(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, s->work[1] != 0 ? 32 : 16);
  p->homeY = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  s->coord.y = p->homeY;
  p->sway = 0;
  p->armSway = 0;
  p->armsOut[0] = p->armsOut[1] = FALSE;
  p->turn = 0;
  p->lobs = 0;
  s->unk_2c = NULL;
  ApZ2CreateGolemFeet(s, 1);
  createArm(p, 0);
  createArm(p, 1);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Flame_Update(p);
}

static const BossFunc sStates[9];

// 0x08063a40
static void Flame_Update(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Flame_Die(p);
    return;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(13, (Object*)p, &sElementCoord);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  (sStates[s->mode[1]])((struct Boss*)p);
  p->sway += 2;
  p->armSway += 2;
  s->coord.y = p->homeY - SIN(p->sway) * 2;
}

// 0x08063b0c
static void Flame_Die(struct FlameGolem* p) { ApZ2GolemDie(&p->s, BODY(0)); }

// 0x08063c84
static void Flame_Wait(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) setMode(s, FLAME_STIR);
}

// 0x08063cb8
static void Flame_Stir(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, FLAME_PAUSE);
}

static void Flame_Nop(struct FlameGolem* p UNUSED) {}

// 0x08063cec
static void Flame_Choose(struct FlameGolem* p) {
  UpdateSpriteAnimation(p);
  setMode(&p->s, (p->turn++ & 1) ? FLAME_OPEN : FLAME_ARMS);
}

// 0x08063d18
static void Flame_Pause(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FLAME_CHOOSE);
}

// 0x08063d58
static void Flame_Open(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(1));
    SetDDP(&p->body, &sCollisions[2]);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) setMode(s, FLAME_LOB);
  } else if ((s->motion).state == ANIM_END) {
    s->work[2] = 48;
    s->mode[3]++;
  }
}

// 0x08063dc0
static void Flame_Lob(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    createFire(s, 0, p->lobs++ & 1);
    s->work[2] = 128;
    PlaySound(SE_Z2_SIGNALOID_FIREBALL);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FLAME_CLOSE);
}

// 0x08063e14
static void Flame_Close(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(3));
    SetDDP(&p->body, sCollisions);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FLAME_CHOOSE);
}

// 0x08063e64
static void Flame_Arms(struct FlameGolem* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BODY(0));
    p->armsOut[0] = p->armsOut[1] = TRUE;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) setMode(s, FLAME_PAUSE);
  } else if (!p->armsOut[0] && !p->armsOut[1]) {
    s->work[2] = 64;
    s->mode[3]++;
  }
}

// clang-format off
static const BossFunc sStates[9] = {
    (BossFunc)Flame_Wait, (BossFunc)Flame_Stir, (BossFunc)Flame_Nop, (BossFunc)Flame_Choose, (BossFunc)Flame_Pause,
    (BossFunc)Flame_Open, (BossFunc)Flame_Lob, (BossFunc)Flame_Close, (BossFunc)Flame_Arms,
};
// clang-format on

// --------------------------------------------

static void Arm_Init(struct FlameArm* p);
static void Arm_Update(struct FlameArm* p);
static void Arm_Die(struct FlameArm* p);

// clang-format off
const EnemyRoutine gApZ2FlameArmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Arm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Arm_Update,
    [ENTITY_DIE] =       (EnemyFunc)Arm_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x0808e824
static void createArm(struct FlameGolem* boss, u8 side) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FLAME_ARM);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = &boss->s;
    p->work[0] = side;
  }
}

// 0x0808e884
static void Arm_Init(struct FlameArm* p) {
  struct Entity* s = &p->s;
  struct FlameGolem* boss = CAST(p);
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] != 0) {
    SetSpriteAnimation(p, BODY(4));
    s->renderPrio = 25;
  } else {
    SetSpriteAnimation(p, BODY(5));
    (s->spr).oam.priority = 1;
  }
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sArmCollisions, 1, NULL);
  p->homeX = (boss->s).coord.x + PIXEL(4);
  p->homeY = FUN_08009f6c((boss->s).coord.x, (boss->s).coord.y) - 0x2B00;
  createJet(s, 0, s->work[0]);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Arm_Update(p);
}

static void swing(struct FlameArm* p, u8 angle) {
  struct Entity* s = &p->s;
  s->coord.x = p->homeX + SIN((u8)(angle + 64)) * 22;
  s->coord.y = p->homeY + SIN(angle) * 40;
}

// 0x0808eb88
static void Arm_Wait(struct FlameArm* p) {
  struct Entity* s = &p->s;
  struct FlameGolem* boss = CAST(p);
  u8 bob = boss->armSway + 128;
  UpdateSpriteAnimation(p);
  s->coord.x = (boss->s).coord.x + (s->work[0] != 0 ? -PIXEL(18) : PIXEL(26));
  if (boss->armsOut[s->work[0] != 0 ? 0 : 1] && (bob & 127) == 0) {
    s->mode[1] = ARM_SWING;
    s->mode[2] = 0;
  }
  s->coord.y = (boss->s).coord.y - SIN(bob) * 2 - 0x2B00;
}

// 0x0808ec0c
static void Arm_Swing(struct FlameArm* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[3] = s->work[0] != 0 ? 128 : 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  swing(p, s->work[3]);
  s->work[3] += 2;
  if (s->work[3] == (s->work[0] != 0 ? 192 : 64)) {
    s->mode[1] = ARM_BACK;
    s->mode[2] = 0;
  }
}

// 0x0808eca0
static void Arm_Back(struct FlameArm* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->work[0] == 0) createJet(s, 1, 0);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  swing(p, s->work[3]);
  s->work[3] -= 2;
  if (s->work[3] == (s->work[0] != 0 ? 64 : 192)) {
    s->mode[1] = ARM_SHAKE;
    s->mode[2] = 0;
  }
}

// 0x0808ed34
static void Arm_Shake(struct FlameArm* p) {
  struct Entity* s = &p->s;
  u8 t;
  if (s->mode[2] == 0) {
    s->work[2] = 2;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  t = s->work[2]++;
  if (t == 16 || t == 17) {
    s->coord.x += 256;
  } else if (t == 18 || t == 19) {
    s->coord.x -= 256;
  } else if (t == 32) {
    s->mode[1] = ARM_HOME;
    s->mode[2] = 0;
  }
}

// 0x0808edd8
static void Arm_Home(struct FlameArm* p) {
  struct Entity* s = &p->s;
  struct FlameGolem* boss = CAST(p);
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  swing(p, s->work[3]);
  if (s->mode[3] != 0) {
    boss->armsOut[s->work[0] != 0 ? 0 : 1] = FALSE;
    boss->armSway = 0;
    s->mode[1] = ARM_WAIT;
    s->mode[2] = 0;
  } else {
    s->work[3] += 2;
    if ((s->work[3] & 127) == 0) s->mode[3]++;
  }
}

static const EnemyFunc sArmStates[5] = {
    (EnemyFunc)Arm_Wait, (EnemyFunc)Arm_Swing, (EnemyFunc)Arm_Back, (EnemyFunc)Arm_Shake, (EnemyFunc)Arm_Home,
};

// 0x0808e970
static void Arm_Update(struct FlameArm* p) {
  if (dying((p->s).unk_28)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Arm_Die(p);
    return;
  }
  (sArmStates[(p->s).mode[1]])((struct Enemy*)p);
}

static void smoke(struct Entity* s, u8 kind, s32 x, s32 up) {
  Coords32 at;
  at.x = s->coord.x + x;
  at.y = s->coord.y - ((RANDOM(RNG_0202f388) & 0x3FF) + up);
  CreateSmoke(kind, &at);
}

// 0x0808e9b4: shakes, drops, bursts on floor
static void Arm_Die(struct FlameArm* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = s->work[0] != 0 ? 32 : 0;
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0) {
    s->coord.y += (s->work[2] & 3) == 0 ? 128 : -128;
    if (--s->work[2] == 0xFF) s->mode[1]++;
    return;
  }
  s->d.y += 64;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(16)) == 0) return;
  smoke(s, 1, -PIXEL(18), -PIXEL(5));
  smoke(s, 1, PIXEL(4), PIXEL(2));
  smoke(s, 1, PIXEL(22), -PIXEL(5));
  smoke(s, 2, -PIXEL(8), PIXEL(5));
  smoke(s, 2, -PIXEL(8), PIXEL(9));
  PlaySound(SE_Z2_ICICLE_BREAK);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's projectile 51.
// work0:
//   0: fireball lobbed over
//   1: pillar where it lands, next one spreading on

static void Fire_Init(struct Projectile* p);
static void Fire_Update(struct Projectile* p);
static void Fire_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2GolemFireRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Fire_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Fire_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Fire_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a9734
static void createFire(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_GOLEM_FIRE);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080a97cc, 0x080a9858
static void Fire_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 0) {
    InitNonAffineMotion(s);
    useSheet(s);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, FIRE(2));
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, sFireCollisions, 1, NULL);
  } else {
    InitRotatableMotion(s);
    useSheet(s);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, FIRE(4));
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, sFireCollisions, 1, NULL);
    s->coord.x = parent->coord.x + (s->work[1] == 0 ? 0 : s->work[1] == 1 ? -PIXEL(12) : PIXEL(12));
    s->coord.y = FUN_08009f6c(s->coord.x, parent->coord.y);
    s->work[2] = 0;
    PlaySound(SE_Z2_SIGNALOID_FIREBALL);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Fire_Update(p);
}

// 0x080a9914
static void updateBall(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  switch (s->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      s->coord.x = parent->coord.x - PIXEL(20);
      s->coord.y = parent->coord.y - PIXEL(94);
      if ((s->motion).state != ANIM_END) break;
      s->unk_coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, FIRE(3));
      s->d.x = s->work[1] != 0 ? -0x300 : -0x100;
      s->d.y = s->work[1] != 0 ? -0x400 : 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      s->d.y += 64;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->coord.y > s->unk_coord.y) {
        createFire(s, 1, s->work[1] + 1);
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// 0x080a99f8
static void updatePillar(struct Projectile* p) {
  struct Entity* s = &p->s;
  u8 t = s->work[2] < 18 ? s->work[2] : 36 - s->work[2];
  s32 x;
  UpdateSpriteAnimation(p);
  (s->spr).mag.y = t * 14 + 256;
  s->work[2]++;
  switch (s->mode[1]) {
    case 0:
      if ((s->motion).cmdIdx == 1) s->mode[1]++;
      break;
    case 1:
      if ((s->motion).cmdIdx != 2) break;
      if (s->work[1] != 0) {
        x = s->coord.x + (s->work[1] == 1 ? -PIXEL(12) : PIXEL(12));
        if (FUN_080098a4(x, s->coord.y) == 0) createFire(s, 1, s->work[1]);
      } else {
        createFire(s, 1, 1);
      }
      SetDDP(&p->body, &sFireCollisions[2]);
      s->mode[1]++;
      break;
    case 2:
      if ((s->motion).cmdIdx != 5) break;
      EXIT_BODY(p);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

static void Fire_Update(struct Projectile* p) {
  if ((p->s).work[0] == 0) {
    updateBall(p);
  } else {
    updatePillar(p);
  }
}

// 0x080a9b00, 0x080a9b18
static void Fire_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 0) {
    UpdateSpriteAnimation(p);
    if ((s->motion).state != 4) return;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void Jet_Init(struct FlameJet* p);
static void Jet_Update(struct FlameJet* p);

// clang-format off
const ProjectileRoutine gApZ2GolemJetRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Jet_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Jet_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a9b44
static void createJet(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_GOLEM_JET);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080a9bdc, 0x080a9c60, 0x080a9cd0
static void Jet_Init(struct FlameJet* p) {
  struct Entity* s = &p->s;
  struct FlameJet* parent = (struct FlameJet*)s->unk_28;
  switch (s->work[0]) {
    case 0:
      InitNonAffineMotion(s);
      useSheet(s);
      s->flags |= DISPLAY | FLIPABLE;
      if (s->work[1] != 0) {
        SetSpriteAnimation(p, FIRE(8));
        s->renderPrio = 25;
      } else {
        SetSpriteAnimation(p, FIRE(6));
      }
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      break;
    case 1:
      s->flags |= FLIPABLE;
      INIT_BODY(p, sJetCollisions, 1, NULL);
      s->coord.x = parent->homeX;
      s->coord.y = parent->homeY;
      p->homeX = s->coord.x;
      p->homeY = s->coord.y;
      s->work[2] = 0;
      s->work[3] = 0;
      break;
    case 2:
      InitNonAffineMotion(s);
      useSheet(s);
      s->flags |= DISPLAY | FLIPABLE;
      SetSpriteAnimation(p, FIRE(0));
      UpdateSpriteAnimation(p);
      s->coord.x = parent->homeX;
      s->coord.y = parent->homeY;
      p->homeX = s->coord.x;
      p->homeY = s->coord.y;
      s->work[2] = 0;
      s->work[3] = 0;
      if ((u8)(s->work[1] - 65) <= 126) {
        s->palID = 1;
        s->renderPrio = 23;
      } else {
        s->palID = 0;
        s->renderPrio = 8;
      }
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Jet_Update(p);
}

// 0x080a9d60
static void updateNozzle(struct FlameJet* p) {
  struct Entity* s = &p->s;
  struct Entity* arm = s->unk_28;
  if (s->mode[1] != 0) {
    if (arm->mode[1] != ARM_BACK) {
      SetSpriteAnimation(p, s->work[1] != 0 ? FIRE(8) : FIRE(6));
      s->mode[1] = 0;
    }
  } else if (arm->mode[1] == ARM_BACK) {
    SetSpriteAnimation(p, FIRE(10));
    s->mode[1]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = arm->coord.x;
  s->coord.y = arm->coord.y;
}

// 0x080a9de8
static void updateJet(struct FlameJet* p) {
  struct Entity* s = &p->s;
  struct Entity* arm = s->unk_28;
  u8 t = s->work[3]++;
  if ((t & 7) == 0) PlaySound(SE_Z2_SIGNALOID_FLAME);
  switch (s->mode[1]) {
    case 0:
      if ((s->work[3] & 7) == 0) {
        createJet(s, 2, arm->work[3]);
        createJet(s, 2, arm->work[3] + 128);
      }
      if (arm->mode[1] == ARM_SHAKE) s->mode[1]++;
      break;
    case 1:
      if (arm->work[2] > 15) {
        s->work[3] = 0;
        s->mode[1]++;
      }
      break;
    case 2:
      s->work[2] -= 4;
      s->coord.x -= PIXEL(2);
      if (s->work[3] > 96) SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// 0x080a9eb8
static void updateFlame(struct FlameJet* p) {
  struct Entity* s = &p->s;
  struct Entity* jet = s->unk_28;
  u8 a = (jet->work[2] & 15) + s->work[1];
  s->coord.x = jet->coord.x + SIN((u8)(a + 64)) * 22 - PIXEL(53);
  s->coord.y = jet->coord.y + SIN(a) * 40;
  switch (s->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (s->work[2]++ > 4) s->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, FIRE(1));
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x080a9bc4
static void Jet_Update(struct FlameJet* p) {
  struct Entity* s = &p->s;
  if (dying(s->unk_28)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch (s->work[0]) {
    case 0: updateNozzle(p); break;
    case 1: updateJet(p); break;
    case 2: updateFlame(p); break;
  }
}

// --------------------------------------------

// clang-format off
static const struct Collision sCollisions[4] = {
    /* 0x833d660 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x400, -0x2600, 0x3a00, 0x3000}},
    /* 0x833d678 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x600, -0x5000, 0x3400, 0x2400}},
    /* 0x833d690 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x400, -0x2600, 0x3a00, 0x3000}},
    /* 0x833d6a8 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x600, -0x5600, 0x3400, 0x3200}},
};

static const struct Collision sArmCollisions[2] = {
    /* 0x83420a0 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x3e00, 0x1000}},
    /* 0x83420b8 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sFireCollisions[4] = {
    /* 0x83454c4 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0xe00, 0xe00}},
    /* 0x83454dc */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    /* 0x83454f4 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0xa00, 0x1000, 0x1400}},
    /* 0x834550c */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sJetCollisions[2] = {
    /* 0x834555c */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x3500, 0x2800, 0x1000, 0x1000}},
    /* 0x8345574 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x3500, -0x2800, 0x1000, 0x1000}},
};
// clang-format on

#endif
