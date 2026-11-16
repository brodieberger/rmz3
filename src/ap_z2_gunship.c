#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "projectile.h"
#include "random.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's boss 2, the Bombardment Aircraft's mid-boss: a gunship alongside the hull. Flies in from far
  off, fires its gun's rockets, bobs, and once hit backs off and passes over bombing
*/

struct Gunship {
  OBJECT_HDR;
  Coords32 home;          // 0xB4, where it spawned
  u8 _bc[4];
  struct Entity* gun;     // 0xC0
  struct Entity* engine;  // 0xC4
  s16 hpBefore;           // 0xC8, at the bob's start
  u8 _ca[10];
  bool8 firing;           // 0xD4, tells the gun
  bool8 fallen;           // 0xD5, its children go with it
  u8 _d6[2];
  motion_t engineMotion;  // 0xD8, the engine plays it
  u8 _da[10];
};
static_assert(sizeof(struct Gunship) == sizeof(struct Boss));

enum { GUN_INTRO, GUN_READY, GUN_RETURN = 5, GUN_FIRE, GUN_BOB, GUN_BACK_OFF, GUN_PASS };

#define GUNSHIP(n) MOTION(AP_SHEET_Z2_GUNSHIP, (n))
#define FAR(n) MOTION(AP_SHEET_Z2_GUNSHIP_FAR, (n))
#define FIRE(n) MOTION(AP_SHEET_Z2_GUNSHIP_FIRE, (n))

// clang-format off
// 0x0833a550, 0x0833a580
static const struct Collision sHull[3] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 8, 0x00, 0x00, 0x00, 0x00, 0x02, 0, 0, 1, 0x00000001, {-0x400, 0x600, 0x6800, 0x2c00}},
    {DRP, FACTION_ENEMY, 0, 8, 0xff, 0xff, 0xff, 0xff, 0x02, 0, 0, 0, 0x00000000, {-0x400, 0x600, 0x6800, 0x2c00}},
};
// clang-format on

static const struct PreloadEntity sGunshipSheet = {AP_SHEET_Z2_GUNSHIP, 0, 512, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sFarSheet = {AP_SHEET_Z2_GUNSHIP_FAR, 0, 727, 7, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sFireSheet = {AP_SHEET_Z2_GUNSHIP_FIRE, 0, 853, 8, 0, AP_PRELOAD_SHEET, 0};

static void Gunship_Init(struct Gunship* p);
static void Gunship_Update(struct Gunship* p);
static void Gunship_Die(struct Gunship* p);

// clang-format off
const BossRoutine gApZ2GunshipRoutine = {
    [ENTITY_INIT] =      (BossFunc)Gunship_Init,
    [ENTITY_UPDATE] =    (BossFunc)Gunship_Update,
    [ENTITY_DIE] =       (BossFunc)Gunship_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createPart(struct Entity* boss, u8 id);
static void createRocket(struct Entity* gun);
static void createBomb(struct Entity* boss);
void ApZ2CreateExplosion(struct Entity* parent, const Coords32* at, u8 kind, u8 roll);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

// 0x080418e0
static void Gunship_Init(struct Gunship* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sGunshipSheet);
  ApLoadSheet(&sFarSheet);
  ApLoadSheet(&sFireSheet);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, GUNSHIP(0));
  UpdateEntityAnim(s);
  ResetBossBody((struct Boss*)p, sHull, 64);
  p->hpBefore = (p->body).hp;
  (s->spr).oam.priority = 3;
  p->home = s->coord;
  p->fallen = FALSE;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Gunship_Update(p);
}

typedef void (*GunshipFunc)(struct Gunship*);
static const GunshipFunc sStates[10];

// 0x08041a20
static void Gunship_Update(struct Gunship* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Gunship_Die(p);
    return;
  }
  sStates[s->mode[1]](p);
}

// 0x08041a84: drifts down and away, bursting, flashing, until well below
static void Gunship_Die(struct Gunship* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    s->renderPrio = 15;
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    s->d.x = facingRight(s) ? PIXEL(2) : -PIXEL(2);
    s->d.y = PIXEL(1);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if ((++s->work[2] & 3) == 0) {
    at.x = s->coord.x + PIXEL(48 - (RANDOM(RNG_0202f388) & 0x7FFF) % 96);
    at.y = s->coord.y + PIXEL(32 - (RANDOM(RNG_0202f388) & 63));
    ApZ2CreateExplosion(s, &at, 2, RANDOM(RNG_0202f388));
  }
  if ((s->work[2] & 15) == 0) PlaySound(SE_Z2_TANK_EXPLODE);
  if (s->work[2] & 1) {
    PaintEntityWhite(s);
  } else {
    UpdateEntityPaletteID(s);
  }
  if (s->coord.y <= p->home.y + PIXEL(256)) return;
  p->fallen = TRUE;
  gStageRun.vm.active |= VM_FLAG1;
}

// 0x08041c14: far off, it swoops in and passes, then comes alongside close
static void Gunship_Intro(struct Gunship* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, FAR(1));
    SET_XFLIP(p, TRUE);
    s->coord.x = p->home.x + 0x8C00;
    s->coord.y = p->home.y + PIXEL(64);
    s->d.x = s->d.y = 0;
    s->work[2] = 64;
    for (i = 0; i < 64; i++) {
      s->d.x += 16;
      s->d.y -= 24;
      s->coord.x -= s->d.x;
      s->coord.y -= s->d.y;
    }
    s->mode[2]++;
    s->mode[3] = 0;
  }
  UpdateEntityAnim(s);
  switch (s->mode[3]) {
    case 0:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.x -= 24;
      s->d.y += 24;
      if ((s->motion).state != ANIM_NEXT_GOTO) break;
      SetMotion(s, FAR(2));
      UpdateEntityAnim(s);
      s->mode[3]++;
      break;
    case 1:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.x -= 4;
      s->d.y += 11;
      if ((s->motion).state != ANIM_NEXT_GOTO) break;
      SetMotion(s, FAR(0));
      UpdateEntityAnim(s);
      s->work[2] = 64;
      s->mode[3]++;
      break;
    case 2:
      s->d.x += 2;
      s->coord.x += s->d.x;
      s->coord.y -= s->d.x / 2;
      UpdateEntityAnim(s);
      if (s->d.x >= 0) s->mode[3] = 4;
      break;
    case 4:
      s->d.x += 96;
      s->coord.x += s->d.x;
      if (s->coord.x <= p->home.x + PIXEL(480)) break;
      SetMotion(s, GUNSHIP(0));
      UpdateEntityAnim(s);
      SetDDP(&p->body, &sHull[1]);
      (s->spr).oam.priority = 2;
      SET_XFLIP(p, FALSE);
      p->engineMotion = GUNSHIP(3);
      p->engine = createPart(s, ENEMY_Z2_GUNSHIP_ENGINE);
      p->gun = createPart(s, ENEMY_Z2_GUNSHIP_GUN);
      s->d.x = 0;
      s->coord.x = p->home.x + PIXEL(240);
      s->coord.y = p->home.y + PIXEL(80);
      s->unk_coord.x = -32;
      for (i = 0; i < 32; i++) {
        s->d.x -= 32;
        s->coord.x -= s->d.x;
      }
      s->mode[3]++;
      break;
    case 5:
      s->d.x += 32;
      s->coord.x += s->d.x;
      if (s->d.x != 0) break;
      s->coord.x = p->home.x + PIXEL(240);
      setMode(s, GUN_READY);
      break;
  }
}

// 0x08041e60
static void Gunship_Ready(struct Gunship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  setMode(s, GUN_FIRE);
}

// 0x08041e88
static void Gunship_Nop(struct Gunship* p UNUSED) {}

// 0x08041e94: comes alongside again from the side it left by
static void Gunship_Return(struct Gunship* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, GUNSHIP(0));
    p->engineMotion = GUNSHIP(3);
    s->d.x = 0;
    if (facingRight(s)) {
      SET_XFLIP(p, FALSE);
      s->coord.x = p->home.x + PIXEL(240);
      s->unk_coord.x = -32;
      for (i = 0; i < 32; i++) {
        s->d.x -= 32;
        s->coord.x -= s->d.x;
      }
    } else {
      SET_XFLIP(p, TRUE);
      s->coord.x = p->home.x;
      s->unk_coord.x = 32;
      for (i = 0; i < 32; i++) {
        s->d.x += 32;
        s->coord.x -= s->d.x;
      }
    }
    s->coord.y = p->home.y + PIXEL(80);
    p->hpBefore = (p->body).hp;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.x -= s->unk_coord.x;
  s->coord.x += s->d.x;
  if (s->d.x == 0) setMode(s, GUN_FIRE);
}

// 0x08041f8c: until its gun starts its volley
static void Gunship_Fire(struct Gunship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->engineMotion = GUNSHIP(4);
    p->firing = TRUE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->gun->mode[1] == 2) setMode(s, GUN_BOB);
}

// 0x08041fd0: bobs a while, backs off if hit in its second half
static void Gunship_Bob(struct Gunship* p) {
  struct Entity* s = &p->s;
  u8 t;
  if (s->mode[2] == 0) {
    p->firing = FALSE;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  t = s->work[2]++;
  s->coord.y = COS(t) * 16 + p->home.y + PIXEL(64);
  if ((s8)s->work[2] < 0 && p->hpBefore != (p->body).hp) setMode(s, GUN_BACK_OFF);
  if (s->work[2] > 254) setMode(s, GUN_FIRE);
}

// 0x08042050: rears up and away
static void Gunship_BackOff(struct Gunship* p) {
  struct Entity* s = &p->s;
  s32 dx;
  if (s->mode[2] == 0) {
    SetMotion(s, GUNSHIP(1));
    p->engineMotion = GUNSHIP(8);
    s->d.x = 0;
    s->unk_coord.x = facingRight(s) ? -64 : 64;
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.x += s->unk_coord.x;
  s->coord.x += s->d.x;
  dx = s->d.x < 0 ? -s->d.x : s->d.x;
  s->coord.y -= dx / 2;
  if (--s->work[2] == 0xFF) setMode(s, GUN_PASS);
}

// 0x080420d8: sweeps across the hull dropping bombs
static void Gunship_Pass(struct Gunship* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->engineMotion = GUNSHIP(3);
    if (facingRight(s)) {
      s->coord.x = p->home.x - PIXEL(32);
      s->d.x = 0x500;
    } else {
      s->coord.x = p->home.x + PIXEL(272);
      s->d.x = -0x500;
    }
    s->coord.y = p->home.y;
    s->mode[3] = 1;
    s->work[2] = 0;
    PlaySound(SE_Z2_GOLEM_SLIDE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  switch (s->mode[3]) {
    case 0:
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 0;
      s->mode[3]++;
      break;
    case 1:
      if ((s->work[2] & 7) == 0) createBomb(s);
      if (s->work[2]++ <= 65) break;
      SetMotion(s, GUNSHIP(2));
      UpdateEntityAnim(s);
      s->mode[3]++;
      break;
    case 2:
      if (!IsSpriteAnimEnd(s)) break;
      s->work[2] = 48;
      s->mode[3]++;
      break;
    case 3:
      if (--s->work[2] == 0xFF) setMode(s, GUN_RETURN);
      break;
  }
}

// 0x0833a528
static const GunshipFunc sStates[10] = {
    Gunship_Intro, Gunship_Ready, Gunship_Nop,  Gunship_Nop,     Gunship_Nop,
    Gunship_Return, Gunship_Fire, Gunship_Bob, Gunship_BackOff, Gunship_Pass,
};

// --------------------------------------------
/*
  Zero 2's enemies 11 and 12: the gunship's engine, playing the motion it is told, and its gun.
  Both ride the gunship and fall with it
*/

struct Part {
  OBJECT_HDR;
  u8 _b4[12];
  motion_t shown;  // 0xC0, engine's
  u8 _c2[2];
};
static_assert(sizeof(struct Part) == sizeof(struct Enemy));

static void Part_Init(struct Part* p);
static void Part_Update(struct Part* p);
static void Part_Die(struct Part* p);

// clang-format off
const EnemyRoutine gApZ2GunshipPartRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Part_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Part_Update,
    [ENTITY_DIE] =       (EnemyFunc)Part_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x0806c90c, 0x0806cacc
static struct Entity* createPart(struct Entity* boss, u8 id) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, id);
    p->flags2 |= WHITE_PAINTABLE;
    p->unk_28 = boss;
  }
  return p;
}

static void ride(struct Entity* s) {
  struct Entity* boss = s->unk_28;
  SET_XFLIP(s, facingRight(boss));
  s->coord = boss->coord;
}

// 0x0806c968, 0x0806cb28
static void Part_Init(struct Part* p) {
  struct Entity* s = &p->s;
  struct Gunship* boss = (struct Gunship*)s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  p->shown = s->id == ENEMY_Z2_GUNSHIP_ENGINE ? boss->engineMotion : GUNSHIP(10);
  SetMotion(s, p->shown);
  UpdateEntityAnim(s);
  s->invincibleID = (boss->s).uniqueID;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

// 0x0806cc84..0x0806cd80: idles until told to fire, opens, three rockets, closes
static void updateGun(struct Part* p) {
  struct Entity* s = &p->s;
  struct Gunship* boss = (struct Gunship*)s->unk_28;
  switch (s->mode[1]) {
    case 0:
      if (s->mode[2] == 0) {
        SetMotion(s, GUNSHIP(10));
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      if (boss->firing) setMode(s, 1);
      break;
    case 1:
      if (s->mode[2] == 0) {
        SetMotion(s, GUNSHIP(11));
        PlaySound(SE_Z2_SPIKEBALL_OPEN);
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, 2);
      break;
    case 2:
      if (s->mode[2] == 0) {
        s->work[2] = 0;
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      switch (s->work[2]++) {
        case 32:
        case 64:
        case 96:
          PlaySound(SE_Z2_LAUNCH);
          createRocket(s);
          break;
        case 127:
          setMode(s, 3);
          break;
      }
      break;
    case 3:
      if (s->mode[2] == 0) {
        SetMotion(s, GUNSHIP(12));
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      if (IsSpriteAnimEnd(s)) setMode(s, 0);
      break;
  }
}

// 0x0806c9c8, 0x0806cb88
static void Part_Update(struct Part* p) {
  struct Entity* s = &p->s;
  struct Gunship* boss = (struct Gunship*)s->unk_28;
  if ((boss->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Part_Die(p);
    return;
  }
  if (s->id == ENEMY_Z2_GUNSHIP_GUN) {
    ride(s);
    updateGun(p);
    return;
  }
  if (p->shown != boss->engineMotion) {
    SetMotion(s, boss->engineMotion);
    p->shown = boss->engineMotion;
  }
  UpdateEntityAnim(s);
  ride(s);
}

// 0x0806ca58, 0x0806cc10: rides the fall out of sight
static void Part_Die(struct Part* p) {
  struct Entity* s = &p->s;
  struct Gunship* boss = (struct Gunship*)s->unk_28;
  if (s->id == ENEMY_Z2_GUNSHIP_ENGINE) UpdateEntityAnim(s);
  s->renderPrio = 15;
  ride(s);
  if (boss->fallen) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 8. work0: 0 the gun's rocket, arcing up and over then speeding off; it bursts
  into seven puffs of 1, fire, work1 their angle
*/

struct Rocket {
  OBJECT_HDR;
  s32 launchX;  // 0xB4
  u8 _b8[6];
  s16 speed;    // 0xBE
  u8 _c0[4];
};
static_assert(sizeof(struct Rocket) == sizeof(struct Projectile));

static void Rocket_Init(struct Rocket* p);
static void Rocket_Update(struct Rocket* p);
static void Rocket_Die(struct Rocket* p);

// clang-format off
const ProjectileRoutine gApZ2RocketRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Rocket_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Rocket_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Rocket_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083433e0, 0x08343410
static const struct Collision sRocket[3] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x02, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x02, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xc00, 0xc00}},
};
// clang-format on

static struct Entity* createProjectile(struct Entity* parent, u8 id, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, id);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x08099aa0
static void createRocket(struct Entity* gun) { createProjectile(gun, PROJECTILE_Z2_ROCKET, 0, 0); }

static s32 scaleDown(s32 v) { return (v < 0 ? v + 255 : v) >> 8; }

// 0x08099b80, 0x08099c58
static void Rocket_Init(struct Rocket* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 0) {
    InitRotatableMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    SetMotion(s, GUNSHIP(13));
    UpdateEntityAnim(s);
    SET_XFLIP(p, facingRight(parent));
    INIT_BODY(p, sRocket, 6, NULL);
    s->coord.x = parent->coord.x + (facingRight(s) ? PIXEL(36) : -PIXEL(36));
    s->coord.y = parent->coord.y + PIXEL(24);
    p->launchX = s->coord.x;
  } else {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    SetMotion(s, FIRE(2));
    UpdateEntityAnim(s);
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, &sRocket[2], 6, NULL);
    (s->spr).oam.priority = 1;
    s->coord = parent->coord;
    s->d.x = scaleDown(COS(s->work[1]) * 448);
    s->d.y = scaleDown(SIN(s->work[1]) * 448);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Rocket_Update(p);
}

// 0x08099d48: up, over, then off along its turn, gone 240 px from launch
static void Rocket_Fly(struct Rocket* p) {
  struct Entity* s = &p->s;
  s32 off;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->d.x = facingRight(s) ? -PIXEL(1) : PIXEL(1);
    s->d.y = 0;
    p->speed = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Rocket_Die(p);
    return;
  }
  switch (s->mode[3]) {
    case 0:
      s->d.y += 64;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->angle = s->work[2] * 2;
      if (s->work[2]++ <= 8) break;
      SetMotion(s, GUNSHIP(14));
      UpdateEntityAnim(s);
      s->work[3] = 5;
      s->mode[3]++;
      break;
    case 1:
      s->d.y -= 64;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->angle = s->work[2] * 2;
      if (s->work[2]++ > 15) s->mode[3] = 3;
      break;
    case 3:
      p->speed += 32;
      s->d.x = scaleDown(COS(s->work[2]) * p->speed);
      s->d.y = scaleDown(SIN(s->work[2]) * p->speed);
      s->coord.x += facingRight(s) ? s->d.x : -s->d.x;
      s->coord.y -= s->d.y;
      s->angle = s->work[2] * 2;
      if (s->work[2] != 0) s->work[2]--;
      off = p->launchX - s->coord.x;
      if ((off < 0 ? -off : off) > PIXEL(240)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
      break;
  }
}

// 0x08099f08
static void Fire_Update(struct Rocket* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (!IsSpriteAnimEnd(s)) return;
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Rocket_Die(p);
}

static void Rocket_Update(struct Rocket* p) {
  if ((p->s).work[0] == 0) {
    Rocket_Fly(p);
  } else {
    Fire_Update(p);
  }
}

// 0x08099f48: a fan of fire, one puff a frame; 0x08099fd8
static void Rocket_Die(struct Rocket* p) {
  struct Entity* s = &p->s;
  u8 angle;
  if (s->work[0] != 0) {
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    CreateSmoke(1, &s->coord);
    s->work[2] = 0;
    PlaySound(SE_Z2_TANK_EXPLODE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  angle = facingRight(s) ? ~(s->work[2] << 5) : s->work[2] << 5;
  createProjectile(s, PROJECTILE_Z2_ROCKET, 1, angle);
  if (s->work[2]++ > 6) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 9. work0: 0 the gunship's bomb, falling ahead of it; 1 the fire where it lands
*/

static void Bomb_Init(struct Projectile* p);
static void Bomb_Update(struct Projectile* p);
static void Bomb_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2BombRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Bomb_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Bomb_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Bomb_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x0834346c..0x0834355c: the bomb, then the fire as it grows and dies down
static const struct Collision sBomb[6] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x200, 0xe00, 0xc00}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x700, 0xe00, 0x1400}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x1400, 0xe00, 0x3000}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x1400, 0xa00, 0x3000}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x600, 0x800, 0x1200}},
};
// clang-format on

// 0x0809a008
static void createBomb(struct Entity* boss) { createProjectile(boss, PROJECTILE_Z2_BOMB, 0, 0); }

// 0x0809a120, 0x0809a224
static void Bomb_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetMotion(s, FIRE(0));
    UpdateEntityAnim(s);
    INIT_BODY(p, sBomb, 1, NULL);
    (s->spr).oam.priority = 3;
    if (facingRight(boss)) {
      s->coord.x = boss->coord.x + PIXEL(66);
      s->d.x = PIXEL(1);
      SET_XFLIP(p, FALSE);
    } else {
      s->coord.x = boss->coord.x - PIXEL(67);
      s->d.x = -PIXEL(1);
      SET_XFLIP(p, TRUE);
    }
    s->coord.y = boss->coord.y + PIXEL(27);
    s->d.y = 0;
  } else {
    SetMotion(s, FIRE(1));
    INIT_BODY(p, &sBomb[1], 1, NULL);
    SET_XFLIP(p, FALSE);
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    s->work[2] = 0;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Bomb_Update(p);
}

static void boom(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Bomb_Die(p);
}

// 0x0809a0c0, 0x0809a2b4, 0x0809a310
static void Bomb_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    boom(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->work[0] == 0) {
    s->d.y += 64;
    if (s->d.y > 0x700) s->d.y = 0x700;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    PlaySound(SE_Z2_SIGNALOID_FLAME);
    boom(p);
    return;
  }
  switch (s->work[2]++) {
    case 2:
      SetDDP(&p->body, &sBomb[2]);
      break;
    case 5:
      SetDDP(&p->body, &sBomb[3]);
      break;
    case 8:
      SetDDP(&p->body, &sBomb[4]);
      break;
    case 12:
      SetDDP(&p->body, &sBomb[5]);
      break;
  }
  if (IsSpriteAnimEnd(s)) boom(p);
}

// 0x0809a3a8, 0x0809a3e8
static void Bomb_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  EXIT_BODY(p);
  if (s->work[0] == 0) {
    struct Entity* fire = createProjectile(s, PROJECTILE_Z2_BOMB, 1, 0);
    if (fire != NULL) fire->coord = s->coord;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

#endif  // AP
