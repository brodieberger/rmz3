#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
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
  Zero 2's Signaloid, enemy 15:

  Attacks with Zero's element

    yellow  an electric blast that flies at Zero and splits up and down
    blue    a snowflake that splits in two and bounces off walls for two seconds
    red     a flamethrower, then a fireball
*/

struct Signaloid {
  OBJECT_HDR;
  bool8 hitFromRight;      // 0xB4
  u8 color;                // 0xB5, light it is showing
  u8 want;                 // 0xB6, light for Zero's current element
  bool8 zeroRight;         // 0xB7, direction of the attack
  u8 _b8[4];
  struct Entity* element;  // 0xBC, element effect affecting it
  u8 _c0[4];
};
static_assert(sizeof(struct Signaloid) == sizeof(struct Enemy));

enum { YELLOW, BLUE, RED };

enum {
  SIGNALOID_START,
  SIGNALOID_WATCH,
  SIGNALOID_TURN,
  SIGNALOID_WIND_UP,
  SIGNALOID_BOLT_HOLD,
  SIGNALOID_BOLT_FIRE,
  SIGNALOID_BOLT_END,
  SIGNALOID_FLAKE_HOLD,
  SIGNALOID_FLAKE_FIRE,
  SIGNALOID_FLAKE_END,
  SIGNALOID_FLAME_WIND_UP,
  SIGNALOID_FLAME,
  SIGNALOID_FLAME_PAUSE,
  SIGNALOID_FIREBALL,
  SIGNALOID_FIREBALL_END,
};

enum { DEATH_EXPLODE, DEATH_CUT };

// Animations in the sheet
#define ANIM(n) MOTION(AP_SHEET_Z2_SIGNALOID, (n))
#define ANIM_IDLE(color) ANIM(color)
#define ANIM_LOWER_HALF ANIM(40)
#define ANIM_BOLT ANIM(29)
#define ANIM_SPARK ANIM(30)
#define ANIM_FLAKE ANIM(31)
#define ANIM_FLAKES ANIM(32)
#define ANIM_TWINKLE ANIM(33)
#define ANIM_SHATTER(n) ANIM(34 + (n))
#define ANIM_FIREBALL ANIM(36)
#define ANIM_FLAME ANIM(37)
#define ANIM_FLAME_OUT ANIM(38)
#define ANIM_UPPER_HALF ANIM(39)

static const struct Collision sCollisions[2];
static const struct Collision sHarmless[1];
static const struct Collision sBoltCollision[1];
static const struct Collision sFlakeCollision[1];
static const struct Collision sFlameCollision[1];
static const struct Collision sFireballCollision[1];
static const struct SlashedEnemy sGibs[3];
static const struct SlashedEnemy sGibsA[3];
static const struct SlashedEnemy sGibsB[4];
static const struct SlashedEnemy sBaseGibs[3];
static const Coords32 sElementCoord = {0, -PIXEL(24)};

static void Signaloid_Init(struct Signaloid* p);
static void Signaloid_Update(struct Signaloid* p);
static void Signaloid_Die(struct Signaloid* p);

// clang-format off
const EnemyRoutine gApZ2SignaloidRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Signaloid_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Signaloid_Update,
    [ENTITY_DIE] =       (EnemyFunc)Signaloid_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

enum {
  EFFECT_SPARK,
  EFFECT_TWINKLE,
  EFFECT_SHATTER,
  EFFECT_UPPER_HALF,
};

// Its effects, Zero 2 VFX 23
struct Effect {
  struct Entity s;
  s32 x[2];  // 0x74, the two pieces of a twinkle or shatter
  s32 y[2];  // 0x7C, a twinkle piece with y 0 is not drawn
};
static_assert(sizeof(struct Effect) == sizeof(struct VFX));

static struct Entity* createEffect(Coords32* c, u8 kind, bool8 right);
static void createBolt(struct Entity* parent, bool8 right);
static void createFlake(struct Entity* parent, bool8 right);
static void createFire(struct Entity* parent, bool8 fireball, bool8 right);

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 zeroIsRight(struct Entity* s) { return s->coord.x < (pZero2->s).coord.x; }

// 0x0806e93c
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Signaloid* p = (struct Signaloid*)body->parent;
    p->hitFromRight = (body->enemy->parent->coord).x > (p->s).coord.x;
  }
}

// 0x0806dc08
static void Signaloid_Init(struct Signaloid* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM_IDLE(s->work[0]));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sCollisions, 12, onCollision);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->color = p->want = s->work[0];
  p->element = NULL;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, SIGNALOID_START);
  Signaloid_Update(p);
}

static const EnemyFunc sUpdates[15];

// 0x0806dcc4
static void Signaloid_Update(struct Signaloid* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Signaloid_Die(p);
    return;
  }
  if (IsFrozen(p)) { 
    SetMotion(s, ANIM_IDLE(p->color));
    UpdateEntityAnim(s);
    SetDDP(&p->body, sCollisions);
    p->element = NULL;
    setMode(s, SIGNALOID_START);
    return;
  }
  switch ((pZero2->unk_b4).status.element) {
    case ELEMENT_THUNDER: p->want = YELLOW; break;
    case ELEMENT_FLAME: p->want = RED; break;
    case ELEMENT_ICE: p->want = BLUE; break;
    default: p->want = s->work[0]; break;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && p->element == NULL) {
    p->element = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (p->element != NULL) SetDDP(&p->body, sHarmless);
  }
  if (p->element != NULL) {
    if (IsDead(p->element)) {
      p->element = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }
  (sUpdates[s->mode[1]])((void*)p);
}

// {lays one animation, then moves on
static void playThen(struct Entity* s, motion_t anim, u8 next) {
  if (s->mode[2] == 0) {
    SetMotion(s, anim);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) setMode(s, next);
}

// Holds one animation for `frames`, then moves on
static void holdThen(struct Entity* s, motion_t anim, u8 frames, u8 next) {
  if (s->mode[2] == 0) {
    SetMotion(s, anim);
    s->work[2] = frames;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) setMode(s, next);
}

// 0x0806df3c
static void Signaloid_Start(struct Signaloid* p) {
  UpdateEntityAnim(&p->s);
  setMode(&p->s, SIGNALOID_WIND_UP);
}

// 0x0806df54: 
static void Signaloid_Watch(struct Signaloid* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_IDLE(p->color));
    s->work[2] = 60;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->color != p->want) {
    setMode(s, SIGNALOID_TURN);
  } else if (--s->work[2] == 0xFF) {
    setMode(s, SIGNALOID_START);
  }
}

// 0x0806e000: 
static void Signaloid_Turn(struct Signaloid* p) {
  static const u8 sTurns[3][3] = {{0, 3, 6}, {8, 1, 4}, {5, 7, 2}};  // [from][to], 0x0833ea0e
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(sTurns[p->color][p->want]));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) {
    p->color = p->want;
    setMode(s, SIGNALOID_WATCH);
  }
}

// 0x0806e078
static void Signaloid_WindUp(struct Signaloid* p) {
  static const u8 sWindUps[3] = {9, 15, 21};
  static const u8 sAttacks[3] = {SIGNALOID_BOLT_HOLD, SIGNALOID_FLAKE_HOLD, SIGNALOID_FLAME_WIND_UP};
  playThen(&p->s, ANIM(sWindUps[p->color]), sAttacks[p->color]);
}

// 0x0806e0e4, 0x0806e148, 0x0806e1a4
static void Signaloid_BoltHold(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) {
    p->zeroRight = zeroIsRight(&p->s);
    createBolt(&p->s, p->zeroRight);
  }
  holdThen(&p->s, ANIM(11), 32, SIGNALOID_BOLT_FIRE);
}

static void Signaloid_BoltFire(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) PlaySound(SE_Z2_SIGNALOID_THUNDER);
  playThen(&p->s, ANIM(p->zeroRight ? 13 : 12), SIGNALOID_BOLT_END);
}

static void Signaloid_BoltEnd(struct Signaloid* p) { playThen(&p->s, ANIM(14), SIGNALOID_WATCH); }

// 0x0806e1dc, 0x0806e240, 0x0806e29c
static void Signaloid_FlakeHold(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) {
    p->zeroRight = zeroIsRight(&p->s);
    createFlake(&p->s, p->zeroRight);
  }
  holdThen(&p->s, ANIM(17), 32, SIGNALOID_FLAKE_FIRE);
}

static void Signaloid_FlakeFire(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) PlaySound(SE_ICE_40);
  playThen(&p->s, ANIM(p->zeroRight ? 19 : 18), SIGNALOID_FLAKE_END);
}

static void Signaloid_FlakeEnd(struct Signaloid* p) { playThen(&p->s, ANIM(20), SIGNALOID_WATCH); }

// 0x0806e2d4, 0x0806e314, 0x0806e394, 0x0806e3d4, 0x0806e438
static void Signaloid_FlameWindUp(struct Signaloid* p) {
  holdThen(&p->s, ANIM(23), 32, SIGNALOID_FLAME);
}

static void Signaloid_Flame(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) {
    p->zeroRight = zeroIsRight(&p->s);
    createFire(&p->s, FALSE, p->zeroRight);
    PlaySound(SE_Z2_SIGNALOID_FLAME);
  }
  holdThen(&p->s, ANIM(p->zeroRight ? 28 : 27), 60, SIGNALOID_FLAME_PAUSE);
}

static void Signaloid_FlamePause(struct Signaloid* p) {
  holdThen(&p->s, ANIM(22), 4, SIGNALOID_FIREBALL);
}

static void Signaloid_Fireball(struct Signaloid* p) {
  if ((p->s).mode[2] == 0) {
    createFire(&p->s, TRUE, p->zeroRight);
    PlaySound(SE_Z2_SIGNALOID_FIREBALL);
  }
  playThen(&p->s, ANIM(p->zeroRight ? 25 : 24), SIGNALOID_FIREBALL_END);
}

static void Signaloid_FireballEnd(struct Signaloid* p) { playThen(&p->s, ANIM(26), SIGNALOID_WATCH); }

static const EnemyFunc sUpdates[15] = {
    [SIGNALOID_START] = (EnemyFunc)Signaloid_Start,
    [SIGNALOID_WATCH] = (EnemyFunc)Signaloid_Watch,
    [SIGNALOID_TURN] = (EnemyFunc)Signaloid_Turn,
    [SIGNALOID_WIND_UP] = (EnemyFunc)Signaloid_WindUp,
    [SIGNALOID_BOLT_HOLD] = (EnemyFunc)Signaloid_BoltHold,
    [SIGNALOID_BOLT_FIRE] = (EnemyFunc)Signaloid_BoltFire,
    [SIGNALOID_BOLT_END] = (EnemyFunc)Signaloid_BoltEnd,
    [SIGNALOID_FLAKE_HOLD] = (EnemyFunc)Signaloid_FlakeHold,
    [SIGNALOID_FLAKE_FIRE] = (EnemyFunc)Signaloid_FlakeFire,
    [SIGNALOID_FLAKE_END] = (EnemyFunc)Signaloid_FlakeEnd,
    [SIGNALOID_FLAME_WIND_UP] = (EnemyFunc)Signaloid_FlameWindUp,
    [SIGNALOID_FLAME] = (EnemyFunc)Signaloid_Flame,
    [SIGNALOID_FLAME_PAUSE] = (EnemyFunc)Signaloid_FlamePause,
    [SIGNALOID_FIREBALL] = (EnemyFunc)Signaloid_Fireball,
    [SIGNALOID_FIREBALL_END] = (EnemyFunc)Signaloid_FireballEnd,
};

static void gib(struct Signaloid* p, const struct SlashedEnemy* g) {
  u8 flip = p->hitFromRight | (((p->s).flags & X_FLIP) ? 0x10 : 0);
  useApSheets(CreateSlashedEnemy(&(p->s).coord, g, 0, flip));
}

static void finish(struct Signaloid* p) {
  Coords32 c;
  c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(32);
  CreateSmoke(1, &c);
}

static void dropAndCount(struct Signaloid* p) {
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(4, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0806e470
static void Signaloid_Explode(struct Signaloid* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s32 side;
  UpdateEntityAnim(s);
  gib(p, &sGibs[0]);
  gib(p, &sGibs[1]);
  gib(p, &sGibs[2]);
  gib(p, &sGibsA[RANDOM(RNG_0202f388) % 3]);
  gib(p, &sGibsB[RANDOM(RNG_0202f388) & 3]);
  gib(p, &sBaseGibs[0]);
  gib(p, &sBaseGibs[1]);
  gib(p, &sBaseGibs[2]);
  finish(p);
  side = (RANDOM(RNG_0202f388) & 1) ? 1 : -1;  // Two puffs, one on each side
  c.x = s->coord.x + side * PIXEL(RANDOM(RNG_0202f388) & 15);
  c.y = s->coord.y - PIXEL((RANDOM(RNG_0202f388) & 15) + 8);
  CreateSmoke(2, &c);
  c.x = s->coord.x - side * PIXEL(RANDOM(RNG_0202f388) & 15);
  c.y = s->coord.y - PIXEL((RANDOM(RNG_0202f388) & 15) + 24);
  CreateSmoke(2, &c);
  dropAndCount(p);
}

// 0x0806e7b0
static void Signaloid_Cut(struct Signaloid* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] == 0) {
    SetMotion(s, ANIM_LOWER_HALF);
    SET_XFLIP(p, p->hitFromRight);
    s->work[2] = 23;
    createEffect(&s->coord, EFFECT_UPPER_HALF, p->hitFromRight);
    s->mode[3]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) {
    gib(p, &sBaseGibs[0]);
    gib(p, &sBaseGibs[1]);
    gib(p, &sBaseGibs[2]);
    finish(p);
    dropAndCount(p);
  }
}

// 0x0806ddc4
static void Signaloid_Die(struct Signaloid* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[1] = ((p->body).status & BODY_STATUS_SLASHED) ? DEATH_CUT : DEATH_EXPLODE;
    EXIT_BODY(p);
    s->mode[2]++;
  }
  if (s->mode[1] == DEATH_CUT) {
    Signaloid_Cut(p);
  } else {
    Signaloid_Explode(p);
  }
}

struct Shot {
  OBJECT_HDR;
  u8 _b4[9];
  u8 spin;                 // 0xBD
  u8 heading;              // 0xBE
  u8 _bf;
  struct Entity* twinkle;  // 0xC0
};
static_assert(sizeof(struct Shot) == sizeof(struct Projectile));

#define PROBE unk_coord 

static struct Shot* allocShot(u8 id, u8 kind, u8 way) {
  struct Shot* p = (struct Shot*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, id);
    (p->s).work[0] = kind;
    (p->s).work[1] = way;
  }
  return p;
}

static void initShot(struct Shot* p, motion_t anim, const struct Collision* c, bool8 rotates) {
  struct Entity* s = &p->s;
  s->palID = 1;
  if (rotates) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, anim);
  UpdateEntityAnim(s);
  SET_XFLIP(p, s->work[1] & 1);
  INIT_BODY(p, c, 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
}

static void besideParent(struct Entity* s, struct Entity* parent) {
  s->coord.x = parent->coord.x + ((s->flags & X_FLIP) ? PIXEL(29) : -PIXEL(29));
  s->coord.y = parent->coord.y - PIXEL(20);
}

static bool8 parentGone(struct Entity* parent) { return parent->mode[0] > ENTITY_UPDATE || IsFrozen(parent); }

static bool8 isWall(s32 x, s32 y, bool8 ladderTop) {
  u16 attr = FUN_080098a4(x, y);
  return attr != 0 && attr != 0x800F && !(ladderTop && attr == 0x800E);
}

static void killShot(struct Shot* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  ((ProjectileFunc)(p->s).onUpdate)((struct Projectile*)p);
}

// Thunder bolt, 0x0809ac20 / 0x0809ac6c
enum { BOLT, BOLT_SPLIT };

static void Bolt_Init(struct Shot* p);
static void Bolt_Update(struct Shot* p);
static void Bolt_Die(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2SignaloidBoltRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Bolt_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Bolt_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Bolt_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static void createBolt(struct Entity* parent, bool8 right) {
  struct Shot* p = allocShot(PROJECTILE_Z2_SIGNALOID_BOLT, BOLT, right);
  if (p != NULL) (p->s).unk_28 = parent;
}

static void createSplit(Coords32* c, bool8 right, bool8 down) {
  struct Shot* p = allocShot(PROJECTILE_Z2_SIGNALOID_BOLT, BOLT_SPLIT, right | (down << 4));
  if (p != NULL) (p->s).coord = *c;
}

// 0x0809ad90, 0x0809ae88
static void Bolt_Init(struct Shot* p) {
  struct Entity* s = &p->s;
  initShot(p, ANIM_BOLT, sBoltCollision, FALSE);
  if (s->work[0] == BOLT) {
    besideParent(s, s->unk_28);
    s->d.x = (s->flags & X_FLIP) ? 0x400 : -0x400;
    s->PROBE.x = (s->flags & X_FLIP) ? PIXEL(8) : -PIXEL(8);
  } else {
    bool8 down = s->work[1] >> 4;
    SET_YFLIP(p, down);
    s->d.y = down ? 0x200 : -0x200;
    s->PROBE.y = down ? PIXEL(8) : -PIXEL(8);
    s->work[2] = 128;
  }
  Bolt_Update(p);
}

static void Bolt_Fly(struct Shot* p) {
  struct Entity* s = &p->s;
  bool8 left = !(s->flags & X_FLIP);
  if (s->mode[2] == 0) {
    struct Entity* parent = s->unk_28;
    if (parentGone(parent)) {
      killShot(p);
      return;
    }
    if (parent->mode[1] != SIGNALOID_BOLT_FIRE) {
      UpdateEntityAnim(s);
      return;
    }
    if (left != (s->coord.x > (pZero2->s).coord.x)) s->mode[3] = TRUE;  // Zero is behind it
    createEffect(&s->coord, EFFECT_SPARK, !left);
    s->work[2] = 128;
    s->mode[2]++;
    UpdateEntityAnim(s);
    return;
  }
  s->coord.x += s->d.x;
  if (isWall(s->coord.x + s->PROBE.x, s->coord.y, TRUE) || ((p->body).status & BODY_STATUS_B2) ||
      --s->work[2] == 0xFF) {
    killShot(p);
    return;
  }
  if (!s->mode[3] && left != (s->coord.x + s->PROBE.x > (pZero2->s).coord.x)) {
    killShot(p);
    return;
  }
  UpdateEntityAnim(s);
}

// 0x0809b088
static void Bolt_Split(struct Shot* p) {
  struct Entity* s = &p->s;
  s->coord.y += s->d.y;
  if (isWall(s->coord.x, s->coord.y + s->PROBE.y, TRUE) || ((p->body).status & BODY_STATUS_B2) ||
      --s->work[2] == 0xFF) {
    killShot(p);
    return;
  }
  UpdateEntityAnim(s);
}

static void Bolt_Update(struct Shot* p) {
  if ((p->s).work[0] == BOLT) {
    Bolt_Fly(p);
  } else {
    Bolt_Split(p);
  }
}

// 0x0809b0fc, 0x0809b178: sparks out. The bolt splits up and down as it goes
static void Bolt_Die(struct Shot* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_SPARK);
    EXIT_BODY(p);
    if (s->work[0] == BOLT) {
      bool8 right = (s->flags & X_FLIP) != 0;
      createSplit(&s->coord, right, FALSE);
      createSplit(&s->coord, right, TRUE);
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (IsSpriteAnimEnd(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// Snowflake, 0x0809b1d4
enum { FLAKE, FLAKE_HALF };

static void Flake_Init(struct Shot* p);
static void Flake_Update(struct Shot* p);
static void Shot_Exit(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2SignaloidFlakeRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Flake_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Flake_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Shot_Exit,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static void createFlake(struct Entity* parent, bool8 right) {
  struct Shot* p = allocShot(PROJECTILE_Z2_SIGNALOID_FLAKE, FLAKE, right);
  if (p != NULL) (p->s).unk_28 = parent;
}

static void createFlakeHalf(Coords32* c, bool8 right, bool8 down) {
  struct Shot* p = allocShot(PROJECTILE_Z2_SIGNALOID_FLAKE, FLAKE_HALF, right | (down << 4));
  if (p != NULL) (p->s).coord = *c;
}

// 0x0809b2ec, 0x0809b3cc
static void Flake_Init(struct Shot* p) {
  static const u8 sHeadings[2][2] = {{144, 240}, {112, 16}};  // [down][right], 0x08343770
  struct Entity* s = &p->s;
  initShot(p, (s->work[0] == FLAKE) ? ANIM_FLAKE : ANIM_FLAKES, sFlakeCollision, TRUE);
  p->spin = 0;
  if (s->work[0] == FLAKE) {
    besideParent(s, s->unk_28);
  } else {
    p->heading = sHeadings[s->work[1] >> 4][s->work[1] & 1];
    s->d.x = COS(p->heading) * 4;
    s->d.y = SIN(p->heading) * 4;
    s->work[2] = 0;
  }
  Flake_Update(p);
}

static void spin(struct Shot* p) {
  p->spin -= 7;
  (p->s).angle = p->spin;
}

static void shatter(struct Shot* p) {
  createEffect(&(p->s).coord, EFFECT_SHATTER, ((p->s).flags & X_FLIP) != 0);
  killShot(p);
}

// 0x0809b4d8:
static void Flake_Wait(struct Shot* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  spin(p);
  if (parentGone(parent)) {
    shatter(p);
  } else if (parent->mode[1] == SIGNALOID_FLAKE_FIRE) {
    createFlakeHalf(&s->coord, s->work[1], FALSE);
    createFlakeHalf(&s->coord, s->work[1], TRUE);
    s->flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    UpdateEntityAnim(s);
  }
}

// 0x0809b578: 
static void Flake_Bounce(struct Shot* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  spin(p);
  switch (s->work[2] & 15) {
    case 0:
      p->twinkle = createEffect(&s->coord, EFFECT_TWINKLE, FALSE);
      break;
    case 8:
      if (p->twinkle != NULL) {
        ((struct Effect*)p->twinkle)->x[1] = s->coord.x;
        ((struct Effect*)p->twinkle)->y[1] = s->coord.y;
      }
      break;
  }
  if (isWall(s->coord.x + s->d.x, s->coord.y, FALSE)) {
    SET_XFLIP(p, !(s->flags & X_FLIP));
    s->d.x = -s->d.x;
  }
  s->coord.x += s->d.x;
  if (isWall(s->coord.x, s->coord.y + s->d.y, FALSE)) s->d.y = -s->d.y;
  s->coord.y += s->d.y;
  if (s->work[2]++ > 120) shatter(p);
}

static void Flake_Update(struct Shot* p) {
  if ((p->s).work[0] == FLAKE) {
    Flake_Wait(p);
  } else {
    Flake_Bounce(p);
  }
}

static void Shot_Exit(struct Shot* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// Flamethrower and fireball, 0x0809b6bc
enum { FLAMETHROWER, FIREBALL };

static void Fire_Init(struct Shot* p);
static void Fire_Update(struct Shot* p);

// clang-format off
const ProjectileRoutine gApZ2SignaloidFireRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Fire_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Fire_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Shot_Exit,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static void createFire(struct Entity* parent, bool8 fireball, bool8 right) {
  struct Shot* p = allocShot(PROJECTILE_Z2_SIGNALOID_FIRE, fireball ? FIREBALL : FLAMETHROWER, right);
  if (p != NULL) (p->s).unk_28 = parent;
}

// 0x0809b7d4, 0x0809b894
static void Fire_Init(struct Shot* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == FLAMETHROWER) {
    initShot(p, ANIM_FLAME, sFlameCollision, FALSE);
    s->coord = (s->unk_28)->coord;
  } else {
    initShot(p, ANIM_FIREBALL, sFireballCollision, FALSE);
    besideParent(s, s->unk_28);
    s->d.x = (s->flags & X_FLIP) ? 0x2C0 : -0x2C0;
    s->work[2] = 128;
  }
  Fire_Update(p);
}

// 0x0809b980:
static void Fire_Flame(struct Shot* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (parentGone(parent)) {
    s->flags &= ~DISPLAY;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->mode[2] == 0) {
    if (parent->mode[1] != SIGNALOID_FLAME) {
      SetMotion(s, ANIM_FLAME_OUT);
      s->mode[2]++;
    }
  } else if (IsSpriteAnimEnd(s)) {
    killShot(p);
  }
  UpdateEntityAnim(s);
}

// 0x0809ba24:
static void Fire_Ball(struct Shot* p) {
  struct Entity* s = &p->s;
  bool8 wall;
  s->coord.x += s->d.x;
  wall = isWall(s->coord.x + s->d.x, s->coord.y, FALSE);
  if (--s->work[2] == 0xFF || ((p->body).status & BODY_STATUS_B2) || wall) {
    killShot(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->work[2] < 32) s->flags = ((s->work[2] & 3) <= 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
}

static void Fire_Update(struct Shot* p) {
  if ((p->s).work[0] == FLAMETHROWER) {
    Fire_Flame(p);
  } else {
    Fire_Ball(p);
  }
}

#define FALL unk_coord  // Fall speed of the two pieces, or the top half's slowdown

static void Effect_Init(struct Effect* p);
static void Effect_Update(struct Effect* p);
static void Effect_Die(struct Effect* p);

// clang-format off
const VFXRoutine gApZ2SignaloidEffectRoutine = {
    [ENTITY_INIT] =      (void*)Effect_Init,
    [ENTITY_UPDATE] =    (void*)Effect_Update,
    [ENTITY_DIE] =       (void*)Effect_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// 0x080b2a10
static struct Entity* createEffect(Coords32* c, u8 kind, bool8 right) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_SIGNALOID);
    p->coord = *c;
    p->work[0] = kind;
    p->work[1] = right;
  }
  return p;
}

static void randomFlips(struct Entity* s) {
  bool8 x = RANDOM(RNG_0202f388) & 1, y = RANDOM(RNG_0202f388) & 1;
  SET_XFLIP(s, x);
  SET_YFLIP(s, y);
}

// 0x080b2ae8, 0x080b2b70, 0x080b2c78, 0x080b2e0c
static void Effect_Init(struct Effect* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[1];
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case EFFECT_SPARK:
      s->palID = 1;
      SetMotion(s, ANIM_SPARK);
      UpdateEntityAnim(s);
      SET_XFLIP(p, right);
      break;
    case EFFECT_TWINKLE:
      s->palID = 1;
      SetMotion(s, ANIM_TWINKLE);
      UpdateEntityAnim(s);
      randomFlips(s);
      p->x[0] = s->coord.x, p->y[0] = s->coord.y;
      p->x[1] = p->y[1] = 0;
      s->FALL.x = s->FALL.y = 0;
      break;
    case EFFECT_SHATTER:
      s->palID = 1;
      SetMotion(s, ANIM_SHATTER((RANDOM(RNG_0202f388) & 1) ? 0 : 1));
      UpdateEntityAnim(s);
      randomFlips(s);
      p->x[0] = p->x[1] = s->coord.x;
      p->y[0] = p->y[1] = s->coord.y;
      s->d.x = right ? 0x2A0 : -0x2A0;  // Horizontal speed of the two pieces
      s->d.y = right ? 0x300 : -0x300;
      s->FALL.x = -(((RANDOM(RNG_0202f388) & 15) + 8) << 6);
      s->FALL.y = -(((RANDOM(RNG_0202f388) & 15) + 12) << 6);
      s->work[2] = 32;
      break;
    case EFFECT_UPPER_HALF:
      SetMotion(s, ANIM_UPPER_HALF);
      UpdateEntityAnim(s);
      SET_XFLIP(p, right);
      s->d.x = right ? -0xF0 : 0xF0;  // Away from the hit
      s->FALL.x = right ? 10 : -10;
      s->work[2] = 23;
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Effect_Update(p);
}

// 0x080b2ed0:
static void Effect_Twinkle(struct Effect* p) {
  struct Entity* s = &p->s;
  u8 k = s->mode[1];
  if (p->y[0] != 0) {
    s->FALL.x += 0x40;
    p->y[0] += s->FALL.x;
  }
  if (p->y[1] != 0) {
    s->FALL.y += 0x40;
    p->y[1] += s->FALL.y;
  }
  if (p->y[k] != 0) {
    s->flags |= DISPLAY;
    s->coord.x = p->x[k], s->coord.y = p->y[k];
    if ((k ? s->FALL.y : s->FALL.x) > 0x600) {
      if (k != 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
        Effect_Die(p);
        return;
      }
      p->y[0] = 0;
    }
  } else {
    s->flags &= ~DISPLAY;
  }
  UpdateEntityAnim(s);
  s->mode[1] = (s->mode[1] + 1) & 1;
}

// 0x080b2f84:
static void Effect_Shatter(struct Effect* p) {
  struct Entity* s = &p->s;
  u8 k = s->work[2] & 1;
  UpdateEntityAnim(s);
  p->x[0] += s->d.x;
  p->x[1] += s->d.y;
  p->y[0] += s->FALL.x;
  p->y[1] += s->FALL.y;
  s->FALL.x += 0x40;
  s->FALL.y += 0x40;
  s->coord.x = p->x[k], s->coord.y = p->y[k];
  if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// 0x080b3008: 
static void Effect_UpperHalf(struct Effect* p) {
  struct Entity* s = &p->s;
  u8 flip = s->work[1] | ((s->flags & X_FLIP) ? 0x10 : 0);
  UpdateEntityAnim(s);
  if (s->mode[1] == 0) {
    s->coord.x += s->d.x;
    s->d.x += s->FALL.x;
    if (--s->work[2] == 0xFF) {
      s->d.x = s->work[1] ? -0x1C0 : 0x1C0;
      s->d.y = -0x600;
      s->work[2] = 20;
      s->mode[1]++;
    }
    return;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (--s->work[2] == 0xFF || FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[0], 0, flip));
    useApSheets(CreateSlashedEnemy(&s->coord, &sGibs[1], 0, flip));
    useApSheets(CreateSlashedEnemy(&s->coord, &sGibsA[RANDOM(RNG_0202f388) % 3], 0, flip));
    useApSheets(CreateSlashedEnemy(&s->coord, &sGibsB[RANDOM(RNG_0202f388) & 3], 0, flip));
    CreateSmoke(1, &s->coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

static void Effect_Update(struct Effect* p) {
  struct Entity* s = &p->s;
  switch (s->work[0]) {
    case EFFECT_SPARK:  // 0x080b2ea4
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    case EFFECT_TWINKLE: Effect_Twinkle(p); break;
    case EFFECT_SHATTER: Effect_Shatter(p); break;
    case EFFECT_UPPER_HALF: Effect_UpperHalf(p); break;
  }
}

// 0x080b31b8
static void Effect_Die(struct Effect* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
// Zero 2 data.

// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 1, 0x00000001, {0x0, -0x1200, 0x1d00, 0x1d00}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0x1200, 0x2400, 0x1d00}},
};

static const struct Collision sHarmless[1] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0x1200, 0x2400, 0x1d00}},
};

static const struct Collision sBoltCollision[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};

static const struct Collision sFlakeCollision[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};

static const struct Collision sFlameCollision[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x3900, -0x1600, 0x3e00, 0x800}},
};

static const struct Collision sFireballCollision[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x100, 0x0, 0x800, 0x800}},
};

// 0x0833e89c: always
static const struct SlashedEnemy sGibs[3] = {
    {ANIM(41), {0xff, 0x11}, {0, -9472}, {0, -1280}, {0, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(42), {0xfe, 0x11}, {1, -6656}, {256, -1280}, {127, 127}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(44), {0x20, 0x24}, {0, -1024}, {0, 0}, {0, 0}, {0, 0}, {0x800, 0x200}, {0}},
};

// 0x0833e8f0 and 0x0833e944: one of each, chosen at random
static const struct SlashedEnemy sGibsA[3] = {
    {ANIM(43), {0xfe, 0x11}, {0, 0}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(45), {0xff, 0x11}, {0, 1024}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(46), {0xfe, 0x11}, {0, -1024}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

static const struct SlashedEnemy sGibsB[4] = {
    {ANIM(47), {0xff, 0x11}, {0, -1024}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(48), {0xfe, 0x11}, {-5376, -5120}, {512, -1152}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(49), {0xff, 0x11}, {-5376, -5120}, {512, -1152}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(50), {0xfe, 0x11}, {-5376, -5120}, {512, -1152}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x0833e9b4: base
static const struct SlashedEnemy sBaseGibs[3] = {
    {ANIM(51), {0xff, 0x11}, {1, -3072}, {128, -1152}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(52), {0xfe, 0x11}, {0, -3072}, {512, -512}, {511, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {ANIM(53), {0xff, 0x11}, {0, -3328}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
