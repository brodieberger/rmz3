#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's solid 17, unseen freezing vent in the Computer Zone.
  work0:
    0: blows left
    1: blows right
    2: blows up
*/

struct Vent {
  OBJECT_HDR;
  bool8 blocked;  // 0xB4, blast meeting an attack, its frost slows
  u8 _b5[15];
};
static_assert(sizeof(struct Vent) == sizeof(struct Solid));

#define FROST(n) MOTION(AP_SHEET_Z2_FROST, (n))

static const struct Collision sOff;
static const struct Collision sBlast[3][3];
static const struct SlashedEnemy sPuff;
static const struct SlashedEnemy sWarnings[3];
static const struct SlashedEnemy sFrostGibs[3];
static const struct SlashedEnemy sCloudEnds[3];

// 0x083497a4
static const Coords32 sMouth[3] = {{-PIXEL(8), 0}, {PIXEL(8), 0}, {0, -PIXEL(8)}};

static void Vent_Init(struct Vent* p);
static void Vent_Update(struct Vent* p);
static void Vent_Disappear(struct Vent* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static void createFrost(struct Zero* zero);
static void createCloud(struct Vent* vent, Coords32* at, u8 dir, bool8 odd);

// clang-format off
const SolidRoutine gApZ2VentRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Vent_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Vent_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)Vent_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void useApSheet(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void mouth(struct Entity* s, Coords32* at) {
  at->x = s->coord.x + sMouth[s->work[0]].x;
  at->y = s->coord.y + sMouth[s->work[0]].y;
}

// 0x080cd7d4
static void Vent_Init(struct Vent* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  setMode(&p->s, 0);
  INIT_BODY(p, &sOff, 32, onCollision);
  Vent_Update(p);
}

/*
  0x080cd828
  0: 128 frames, a puff at 128 and 64
  1: 64 frames, puffs blown at 64, 32 and 24
  2: 64 frames, blast grows at 56 and 48, frost every 8
*/
static void Vent_Update(struct Vent* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  switch (s->mode[1]) {
    case 0:
      if (s->mode[2] == 0) {
        SetDDP(&p->body, &sOff);
        s->work[2] = 128;
        s->mode[2]++;
      }
      if ((s->work[2] & 63) == 0) {
        if (s->work[2] == 0) {
          setMode(s, 1);
          return;
        }
        mouth(s, &at);
        useApSheet(CreateSlashedEnemy(&at, &sPuff, 0, 0));
      }
      break;
    case 1:
      if (s->mode[2] == 0) {
        s->work[2] = 64;
        s->mode[2]++;
      }
      if (s->work[2] == 0) {
        setMode(s, 2);
        p->blocked = FALSE;
      } else if (s->work[2] == 64 || s->work[2] == 32 || s->work[2] == 24) {
        mouth(s, &at);
        useApSheet(CreateSlashedEnemy(&at, &sWarnings[s->work[0]], 0, 0));
      }
      break;
    case 2:
      if (s->mode[2] == 0) {
        SetDDP(&p->body, &sBlast[0][s->work[0]]);
        s->work[2] = 64;
        s->work[3] = 0;
        s->mode[2]++;
      }
      if (s->work[2] == 56) SetDDP(&p->body, &sBlast[1][s->work[0]]);
      if (s->work[2] == 48) SetDDP(&p->body, &sBlast[2][s->work[0]]);
      if ((s->work[2] & 7) == 0) {
        if (s->work[2] == 0) {
          s->work[2] = 128;
          setMode(s, 0);
          return;
        }
        mouth(s, &at);
        createCloud(p, &at, s->work[0], ++s->work[3] & 1);
      }
      break;
  }
  s->work[2]--;
}

// 0x080bf834
static void Vent_Disappear(struct Vent* p) {
  EXIT_BODY(p);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// 0x080cda34
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Vent* p = (struct Vent*)body->parent;
  struct Zero* zero;
  p->blocked = (body->hitboxFlags & BODY_STATUS_B8) != 0;
  if (!(body->hitboxFlags & BODY_STATUS_B2)) return;
  zero = (struct Zero*)body->enemy->parent;
  if ((zero->s).mode[1] != ZERO_BINDED) createFrost(zero);
}

// --------------------------------------------
/*
  Zero 2's projectile 48, ice Zero is frozen in. Holds him with the engine's binding
  for 300 frames, less 8 a button mashed, or until he's hit.
*/

struct Frost {
  OBJECT_HDR;
  u8 shake;  // 0xB4, 0 or 1 px left
  u8 _b5;
  u16 timer;  // 0xB6
  struct Zero* zero;  // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct Frost) == sizeof(struct Projectile));

static const struct Collision sFrost;

static void Frost_Init(struct Frost* p);
static void Frost_Update(struct Frost* p);
static void Frost_Die(struct Frost* p);

// clang-format off
const ProjectileRoutine gApZ2FrostRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Frost_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Frost_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Frost_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a8dfc
static void createFrost(struct Zero* zero) {
  struct Frost* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p == NULL) return;
  INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FROST);
  p->zero = zero;
}

static bool8 inPlay(void) { return (gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE); }

// 0x080a8e4c
static void Frost_Init(struct Frost* p) {
  struct Entity* s = &p->s;
  if ((p->zero->s).mode[1] == ZERO_BINDED || !inPlay()) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, FROST(1));
  s->flags |= DISPLAY | FLIPABLE;
  s->d.y = 0;
  p->timer = 300;
  s->coord = (p->zero->s).coord;
  p->shake = 0;
  s->work[2] = 0;
  INIT_BODY(p, &sFrost, 4, NULL);
  PlaySound(SE_Z2_SPIKE_GROW);
}

static void blink(struct Frost* p) {
  struct Entity* s = &p->s;
  u8 mask = p->timer < 75 ? 1 : p->timer < 150 ? 3 : 7;
  if (s->work[2] & mask) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
}

static void shatter(struct Frost* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Frost_Die(p);
}

// 0x080a8f6a
static void Frost_Update(struct Frost* p) {
  struct Entity* s = &p->s;
  struct Entity* zero = &p->zero->s;
  s32 dx;
  u8 mashed;
  if (!inPlay()) {
    shatter(p);
    return;
  }
  if (zero->coord.x != s->coord.x - PIXEL(p->shake)) s->coord.x = zero->coord.x - PIXEL(p->shake);
  if (zero->coord.y != s->coord.y) {
    s->coord.y = zero->coord.y;
    s->d.y = 0;
  }
  if (p->zero->body.status & BODY_STATUS_WHITE) {
    shatter(p);
    return;
  }
  UpdateEntityAnim(s);
  if (p->timer == 0) {
    shatter(p);
    return;
  }
  p->timer--;
  s->work[2]++;
  blink(p);
  dx = FUN_0800a40c(s->coord.x - PIXEL(8), s->coord.y + PIXEL(8));
  if (dx == 0) dx = FUN_0800a40c(s->coord.x + PIXEL(8) - 1, s->coord.y + PIXEL(8));
  s->coord.x += dx;
  if (FUN_080098a4(s->coord.x, s->coord.y + s->d.y) == 0) s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
  mashed = 8 * CountButtonMashing(p->zero);
  if (mashed != 0) {
    if (p->timer <= mashed) {
      shatter(p);
      return;
    }
    p->timer -= mashed;
    s->coord.x += p->shake ? -PIXEL(1) : PIXEL(1);
    p->shake ^= 1;
  }
  zero->coord.x = s->coord.x - PIXEL(p->shake);
  zero->coord.y = s->coord.y;
}

// 0x080a912c: shatters
static void Frost_Die(struct Frost* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i, n;
  at.x = s->coord.x;
  at.y = s->coord.y - PIXEL(16);
  n = (RANDOM(RNG_0202f388) & 1) + 5;
  for (i = 0; i < n; i++) useApSheet(CreateSlashedEnemy(&at, &sFrostGibs[i >> 1], 0, 0));
  PlaySound(SE_Z2_ICE_BREAK);
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2's VFX 52, frost a blast blows

static void Cloud_Init(struct VFX* p);
static void Cloud_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FrostCloudRoutine = {
    [ENTITY_INIT] =      Cloud_Init,
    [ENTITY_UPDATE] =    Cloud_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteEntity,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x0834715c
static const s8 sCloudDir[3][2] = {{-1, 0}, {1, 0}, {0, -1}};

// 0x080ba9b8
static void createCloud(struct Vent* vent, Coords32* at, u8 dir, bool8 odd) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_FROST_CLOUD);
  p->unk_28 = &vent->s;
  p->coord = *at;
  p->work[0] = dir;
  p->work[1] = odd;
}

// 0x080baa14: 32 frames at 2.5 px a frame, slowing
static void Cloud_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  const s8* dir = sCloudDir[s->work[0]];
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, FROST(0));
  s->flags |= DISPLAY | FLIPABLE;
  s->work[2] = 32;
  s->d.x = dir[0] * 640;
  s->d.y = dir[1] * 640;
  s->unk_coord.x = -dir[0] * 8;
  s->unk_coord.y = -dir[1] * 8;
  Cloud_Update(p);
}

// 0x080baad8
static void Cloud_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) {
    if (s->work[1]) useApSheet(CreateSlashedEnemy(&s->coord, &sCloudEnds[s->work[0]], 0, 0));
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (((struct Vent*)s->unk_28)->blocked) {
    s->coord.x += s->d.x / 3 * 2;
    s->coord.y += s->d.y / 3 * 2;
  } else {
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
  }
  s->d.x += s->unk_coord.x;
  s->d.y += s->unk_coord.y;
}

// --------------------------------------------
// clang-format off
// 0x083495e0
static const struct Collision sOff =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0, 0, 0, 0}};

// 0x083495f8, 0x08349658, 0x083496b8: by work0, growing. Damage 255 is none.
static const struct Collision sBlast[3][3] = {
    {
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {-0x1000, 0, 0x1000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0x1000, 0, 0x1000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0, -0x1000, 0x1000, 0x1000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {-0x1800, 0, 0x2000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0x1800, 0, 0x2000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0, -0x1800, 0x1000, 0x2000}},
    },
    {
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {-0x2800, 0, 0x4000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0x2800, 0, 0x4000, 0x1000}},
        {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0x00000001, {0, -0x2800, 0x1000, 0x4000}},
    },
};

// 0x083453a4: unk_0a 0x23 binds while ice's unk_21 holds
static const struct Collision sFrost =
    {DDP, FACTION_ENEMY, 0, 255, 0, 0, 0, 0, 0, 0, 0x23, 0, 0x00000001, {0, -0x2000, 0x4000, 0x4000}};

// 0x08349718
static const struct SlashedEnemy sPuff = {FROST(5), {12, 112}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0}};

// 0x08349734
static const struct SlashedEnemy sWarnings[3] = {
    {FROST(5), {12, 112}, {0, 0}, {-256, 0}, {0, 0}, {0, 0}, {0, 0}, {0}},
    {FROST(5), {12, 112}, {0, 0}, {256, 0}, {0, 0}, {0, 0}, {0, 0}, {0}},
    {FROST(5), {12, 112}, {0, 0}, {0, -256}, {0, 0}, {0, 0}, {0, 0}, {0}},
};

// 0x08347164
static const struct SlashedEnemy sCloudEnds[3] = {
    {FROST(5), {12, 112}, {0, 0}, {-256, 0}, {0, 0}, {8, 0}, {0, 0}, {0}},
    {FROST(5), {12, 112}, {0, 0}, {256, 0}, {0, 0}, {-8, 0}, {0, 0}, {0}},
    {FROST(5), {12, 112}, {0, 0}, {0, -256}, {0, 0}, {0, 8}, {0, 0}, {0}},
};

// 0x083453bc
static const struct SlashedEnemy sFrostGibs[3] = {
    {FROST(2), {0xff, 0x51}, {0, 0}, {-256, -1664}, {511, 1023}, {0, 64}, {0x200, 0x200}, {0}},
    {FROST(3), {0xff, 0x51}, {0, 0}, {-256, -1664}, {511, 1023}, {0, 64}, {0x200, 0x200}, {0}},
    {FROST(4), {0xff, 0x51}, {0, 0}, {-256, -1664}, {511, 1023}, {0, 64}, {0x200, 0x200}, {0}},
};
// clang-format on

#endif  // AP
