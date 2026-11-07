#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's propeller drone, enemy 14.
  work0:
    0: bobs 8 px
    1: bobs 16 px, slower
    2: bobs 32 px, slower again
    3: stays still
*/

struct Copter {
  OBJECT_HDR;
  u8 _b4;
  u8 gunStopped;                 // 0xB5, COPTER_FROZEN | COPTER_KNOCKED
  u8 _b6[2];
  s32 baseY;                     // 0xB8
  u16 bobHeight;                 // 0xBC
  u16 bobPhase;                  // 0xBE
  struct Entity* elementEffect;  // 0xC0
};
static_assert(sizeof(struct Copter) == sizeof(struct Enemy));

// Gun, Zero 2's projectile 11
struct Gun {
  OBJECT_HDR;
  u16 angle;       // 0xB4, 0x4000 is straight down
  u16 _b6;
  u8 target;       // 0xB8, index into sAimAngles
  u8 parentDying;  // 0xB9
  u8 paused;       // 0xBA
  u8 _[9];
};
static_assert(sizeof(struct Gun) == sizeof(struct Projectile));

// Knocked down by an element, gun never fires again
#define COPTER_FROZEN (1 << 0)
#define COPTER_PULLED (1 << 1)
#define COPTER_KNOCKED (1 << 2)

enum {
  COPTER_BOB,
  COPTER_FALL,
  COPTER_RECOIL,
};

enum {
  COPTER_EXPLODE,
  COPTER_CUT,
  COPTER_CUT_HARD,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_COPTER, n)
#define ANIM_BODY ANIM(0)
#define ANIM_HIT ANIM(4)
#define ANIM_GUN ANIM(6)
#define ANIM_GUN_FIRE ANIM(7)

#define FACING_RIGHT(p) (((p)->s.flags & X_FLIP) != 0)

static const struct Collision sCollisions[2];
static const struct Collision sHarmless[2];
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sGibsHard[3];
static const struct SlashedEnemy sCutHalf;
static const struct SlashedEnemy sCutHalfHard;
static const Coords32 sElementCoord = {0, 0};

static u16 Copter_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Copter_Init(struct Copter* p);
static void Copter_Update(struct Copter* p);
static void Copter_Die(struct Copter* p);
static struct Entity* createGun(struct Copter* parent);

// clang-format off
const EnemyRoutine gApZ2CopterRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Copter_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Copter_Update,
    [ENTITY_DIE] =       (EnemyFunc)Copter_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void Copter_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* p = body->parent;
    p->work[3] = (p->coord).x < (pZero2->s).coord.x;
  }
}

// 0x0806d2f4
static void Copter_Init(struct Copter* p) {
  struct Entity* s = &p->s;
  s->unk_2c = createGun(p);
  if (s->unk_2c == NULL) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, FALSE);
  SetSpriteAnimation(p, ANIM_BODY);
  UpdateSpriteAnimation(p);
  switch (s->work[0]) {
    case 0: p->bobHeight = PIXEL(8); break;
    case 1: p->bobHeight = PIXEL(16); break;
    case 2: p->bobHeight = PIXEL(32); break;
    default: p->bobHeight = 0; break;
  }
  INIT_BODY(p, sCollisions, 6, Copter_OnCollision);
  (p->body).unk_28 = (u32)Copter_Pull;
  s->flags |= DISPLAY | FLIPABLE;
  p->baseY = s->coord.y;
  p->bobPhase = 0;
  p->gunStopped = 0;
  s->work[2] = 0;
  p->elementEffect = NULL;
  Copter_Update(p);
}

static void Copter_Recoil(struct Copter* p);

// 0x0806d438
static void Copter_Update(struct Copter* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (ApRecoilHit((Object*)p) && s->mode[1] != COPTER_RECOIL) s->mode[1] = COPTER_RECOIL, s->mode[2] = 0;
  if (s->mode[1] == COPTER_RECOIL) {
    Copter_Recoil(p);
    return;
  }

  if (status & BODY_STATUS_DEAD) {
    u8 kind = COPTER_EXPLODE;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? COPTER_CUT_HARD : COPTER_CUT;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    EXIT_BODY(p);
    Copter_Die(p);
    return;
  }

  if (IsFrozen(p)) {
    p->gunStopped |= COPTER_FROZEN;
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }
  p->gunStopped &= ~COPTER_FROZEN;
  if (p->elementEffect != NULL && IsDead(p->elementEffect)) p->elementEffect = NULL;

  if ((status & BODY_STATUS_WHITE) && p->elementEffect == NULL) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->elementEffect != NULL) {
      SetDDP(&p->body, sHarmless);
      s->mode[1] = COPTER_FALL;
      s->d.y = 0;
      p->gunStopped |= COPTER_KNOCKED;
    }
  }

  if (s->mode[1] == COPTER_BOB) {
    UpdateSpriteAnimation(p);
    if (p->gunStopped & COPTER_PULLED) return;
    p->bobPhase += 0x240 / (1 << s->work[0]);
    s->coord.y = (p->baseY + ((SIN(p->bobPhase >> 8) * p->bobHeight) >> 8)) & ~0xFF;
    return;
  }

  // Knocked down by an element, falls and bobs where it lands
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  if (p->elementEffect == NULL) {
    s->mode[1] = COPTER_BOB;
    p->baseY = s->coord.y;
    p->bobPhase = 0;
    p->gunStopped |= COPTER_KNOCKED;
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  s->mode[1] = COPTER_EXPLODE;
  EXIT_BODY(p);
  Copter_Die(p);
}

// 0x0806dbb8
static u16 Copter_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  struct Copter* p = (struct Copter*)s;
  p->gunStopped |= COPTER_PULLED;
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  p->baseY = s->coord.y;
  p->bobPhase = 0;
  p->gunStopped &= ~COPTER_PULLED;
  return 0;
}

// Same as Pantheon Hunter, 0x08064cac
static void Copter_Recoil(struct Copter* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = COPTER_EXPLODE;
    (p->s).mode[2] = 0;
    EXIT_BODY(p);
    Copter_Die(p);
  }
}

// --------------------------------------------

// Within -15..16 px
static void smokeWide(struct Copter* p, u8 kind) {
  Coords32 c;
  c.x = (p->s).coord.x + (((RANDOM(RNG_0202f388) & 31) - 15) << 8);
  c.y = (p->s).coord.y + (((RANDOM(RNG_0202f388) & 31) - 15) << 8);
  CreateSmoke(kind, &c);
}

// Within -8..7 px
static void smokeNear(struct Copter* p) {
  Coords32 c;
  c.x = (p->s).coord.x + (((RANDOM(RNG_0202f388) & 15) - 8) << 8);
  c.y = (p->s).coord.y + (((RANDOM(RNG_0202f388) & 15) - 8) << 8);
  CreateSmoke(1, &c);
}

static void burst(struct Copter* p, const struct SlashedEnemy* gibs, bool8 right) {
  s32 i;
  for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&(p->s).coord, &gibs[i], 0, right | (right << 4)));
}

static void finish(struct Copter* p) {
  TryDropItem(1, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0806d6b0
static void Copter_Explode(struct Copter* p) {
  burst(p, sGibs, FACING_RIGHT(p));
  smokeWide(p, 1);
  smokeWide(p, 2);
  PlaySound(SE_ZAKO_EXPLODE);
  finish(p);
}

static void fall(struct Entity* s) {
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

// 0x0806d7d0
static void Copter_Cut(struct Copter* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3];
  if (s->mode[2] == 0) {
    ((struct Gun*)s->unk_2c)->parentDying = TRUE;  // gun waits for this half to land
    SET_XFLIP(p, right);
    (s->spr).oam.priority = 1;
    SetSpriteAnimation(p, ANIM_HIT);
    useApSheets(CreateSlashedEnemy(&s->coord, &sCutHalf, 0, right | (right << 4)));
    s->coord.x += right ? PIXEL(2) : -PIXEL(2);
    s->coord.y += PIXEL(1);
    s->d.x = right ? 0xC0 : -0xC0;
    s->d.y = PIXEL(1);
    s->work[2] = 128;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]--;
  if (s->work[2] > 114) return;
  if (s->work[2] > 104) {
    s->coord.x += s->d.x;
    s->coord.y += 0x80;
    return;
  }
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0 && s->work[2] != 0) {
    fall(s);
    return;
  }
  burst(p, sGibs, right);
  smokeNear(p);
  PlaySound(SE_ZAKO_EXPLODE);
  finish(p);
}

// 0x0806d934
static void Copter_CutHard(struct Copter* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3];
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ANIM_HIT);
    useApSheets(CreateSlashedEnemy(&s->coord, &sCutHalfHard, 0, right | (right << 4)));
    s->d.x = right ? (RANDOM(RNG_0202f388) & 0xFF) - 0x37F : (RANDOM(RNG_0202f388) & 0xFF) + 0x281;
    s->d.y = -0x380;
    s->work[2] = 128;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]--;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0 && s->work[2] != 0) {
    fall(s);
    return;
  }
  burst(p, sGibsHard, right);
  smokeNear(p);
  PlaySound(SE_ZAKO_EXPLODE);
  finish(p);
}

// 0x0806d648
static void Copter_Die(struct Copter* p) {
  switch ((p->s).mode[1]) {
    case COPTER_EXPLODE: Copter_Explode(p); break;
    case COPTER_CUT: Copter_Cut(p); break;
    case COPTER_CUT_HARD: Copter_CutHard(p); break;
  }
}

// --------------------------------------------
// Gun

enum {
  GUN_IDLE,
  GUN_AIM,
  GUN_FIRE,
  GUN_COOL,
};

static const u8 sAimAngles[9] = {21, 30, 42, 53, 64, 74, 85, 94, 106};
static const u8 sShotAngles[9] = {21, 32, 42, 53, 64, 74, 85, 96, 106};

static void Gun_Init(struct Gun* p);
static void Gun_Update(struct Gun* p);
static void Gun_Die(struct Gun* p);

// clang-format off
const ProjectileRoutine gApZ2CopterGunRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Gun_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Gun_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Gun_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809a618
static struct Entity* createGun(struct Copter* parent) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_COPTER_GUN);
    p->unk_28 = (struct Entity*)parent;
    p->coord = (parent->s).coord;
  }
  return p;
}

// 0x0809ac10
static void pointGun(struct Gun* p) { (p->s).angle = (p->angle >> 8) + 128; }

// 0x0809a668
static void Gun_Init(struct Gun* p) {
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitRotatableMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY;
  s->renderPrio = 25;
  SET_XFLIP(p, (s->unk_28->flags & X_FLIP) != 0);
  p->angle = 0x4000;
  pointGun(p);
  s->flags |= FLIPABLE;
  s->coord.y += PIXEL(6);
  p->parentDying = FALSE;
  p->paused = FALSE;
  SetMotion(s, ANIM_GUN);
  UpdateEntityAnim(s);
  Gun_Update(p);
}

static void setGunMode(struct Gun* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

// 0x0809abb4: nearest of nine angles to Zero's chest
static void pickTarget(struct Gun* p) {
  u8 a = CalcAngle((p->s).coord.x - (pZero2->s).coord.x, (p->s).coord.y - ((pZero2->s).coord.y - PIXEL(16))) + 0x82;
  if (a < sAimAngles[0]) a = sAimAngles[0];
  if (a > sAimAngles[8]) a = sAimAngles[8];
  p->target = (a - 21) / 10;
}

// 0x0809a8ec: hangs straight down until Zero is below, within 96 px
static void Gun_Idle(struct Gun* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_GUN);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((u32)((pZero2->s).coord.x - s->coord.x + PIXEL(96)) <= PIXEL(192) &&
      s->coord.y - ((pZero2->s).coord.y - PIXEL(16)) <= 0) {
    pickTarget(p);
    setGunMode(p, GUN_AIM);
    return;
  }
  if (p->angle < 0x4000) {
    p->angle += 0x180;
    if (p->angle > 0x4000) p->angle = 0x4000;
  } else if (p->angle > 0x4000) {
    p->angle -= 0x180;
    if (p->angle < 0x4000) p->angle = 0x4000;
  }
  pointGun(p);
}

// 0x0809a9a0
static void Gun_Aim(struct Gun* p) {
  struct Entity* s = &p->s;
  u16 goal = sAimAngles[p->target] << 8;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_GUN);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->angle < goal) {
    p->angle += 0x240;
    if (p->angle < goal) {
      pointGun(p);
      return;
    }
  } else if (p->angle > goal) {
    p->angle -= 0x240;
    if (p->angle > goal) {
      pointGun(p);
      return;
    }
  }
  p->angle = goal;
  pointGun(p);
  setGunMode(p, GUN_FIRE);
}

// 0x0809aa2c
static void Gun_Fire(struct Gun* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->mode[2]++;
  }
  switch (s->work[2]) {
    case 0:
    case 10:
    case 20: {
      u8 a = sAimAngles[p->target];
      Coords32 c;
      SetMotion(s, ANIM_GUN_FIRE);
      c.x = s->coord.x + COS(a) * 12;
      c.y = s->coord.y + SIN(a) * 12;
      CreateLemon(&c, 0x200, sShotAngles[p->target] + 128);
      PlaySound(SE_ENEMY_SHOT);
      break;
    }
    case 4:
    case 14:
    case 24:
      SetMotion(s, ANIM_GUN);
      break;
    case 30:
      setGunMode(p, GUN_COOL);
      return;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
}

// 0x0809ab78
static void Gun_Cool(struct Gun* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_GUN);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] > 89) setGunMode(p, GUN_IDLE);
}

// 0x0809a720
static void Gun_Update(struct Gun* p) {
  struct Entity* s = &p->s;
  struct Copter* parent = (struct Copter*)s->unk_28;

  if (parent == NULL || (parent->s).mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = 0;
    Gun_Die(p);
    return;
  }
  s->coord.x = (parent->s).coord.x;
  s->coord.y = (parent->s).coord.y + PIXEL(6);
  if (parent->gunStopped != 0) {
    p->paused = TRUE;
    return;
  }
  if (p->paused) {
    p->paused = FALSE;
    setGunMode(p, GUN_COOL);
  }
  switch (s->mode[1]) {
    case GUN_IDLE: Gun_Idle(p); break;
    case GUN_AIM: Gun_Aim(p); break;
    case GUN_FIRE: Gun_Fire(p); break;
    case GUN_COOL: Gun_Cool(p); break;
  }
}

// 0x0809a7fc: bursts, or 36 frames later if drone was cut in half
static void Gun_Die(struct Gun* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (s->mode[1] == 0) {
    SetMotion(s, ANIM_GUN);
    s->work[2] = 0;
    s->mode[1]++;
  }
  if (p->parentDying && ++s->work[2] <= 35) return;
  c.x = s->coord.x + (COS(p->angle >> 8) << 3);
  c.y = s->coord.y + (SIN(p->angle >> 8) << 3);
  CreateSmoke(2, &c);
  s->flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct SlashedEnemy sGibs[3] = {
    {ANIM(1), {0xff, 0x11}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(2), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(3), {0xff, 0x11}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sGibsHard[3] = {
    {ANIM(1), {0xff, 0x11}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(2), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(3), {0xff, 0x01}, {0, 0}, {192, -768}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sCutHalf = {ANIM(5), {0x1c, 0x04}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0x200, 0x200}, {0}};
static const struct SlashedEnemy sCutHalfHard = {ANIM(5), {0xff, 0x04}, {0, 0}, {64, 0}, {15, 0}, {0, 64}, {0x200, 0x200}, {0}};
// clang-format on

#endif  // AP
