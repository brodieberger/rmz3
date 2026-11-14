#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's frog, boss 12, Burble Hekelot. Forest of Notus.
  Grows a size each time it swallows Zero or a tree frog, a hit shrinks it a size.
*/

struct Frog {
  OBJECT_HDR;
  u8 last;                 // 0xB4, state picked before
  u8 phase;                // 0xB5, 0 small, 1 grown, 2 grown twice
  u8 air;                  // 0xB6, AIRBORNE, HIDDEN
  u8 armsBack;             // 0xB7
  s32 left;                // 0xB8, arena's left wall
  s32 floor;               // 0xBC
  u8 resume;               // 0xC0, state before a guard or hit
  bool8 ateTough;          // 0xC1
  u8 tough;                // 0xC2, frogs summoned before the tough one
  u8 rolls;                // 0xC3
  struct Entity* arms[2];  // 0xC4
  u8 frogs;                // 0xCC, tree frogs it has out
  u8 summoned;             // 0xCD
  u8 spots;                // 0xCE, summon spots taken
  bool8 hungry;            // 0xCF, picks nearest tree frog into unk_coord
  bool8 ready;             // 0xD0, guards, hurts on touch
  bool8 committed;         // 0xD1, hit doesn't knock it back
  u16 reach;               // 0xD2, half width it notices tree frogs in
  u8 _d4[4];
  s8 rollX;                // 0xD8
  s8 rollY;                // 0xD9
  u8 rolled;               // 0xDA
  bool8 frogNear;          // 0xDB
  s32 distance;            // 0xDC, rolled
  s32 smoked;              // 0xE0, distance at last dust
};
static_assert(sizeof(struct Frog) == sizeof(struct Boss));

struct Tongue {
  OBJECT_HDR;
  Coords32 home;   // 0xB4, links' anchor, the tongue's hold on Zero, the eating tongue's on its frog
  u8 caught;       // 0xBC, Zero
  u8 bites;        // 0xBD, left
  u8 grip;         // 0xBE, left before Zero shakes free
  bool8 released;  // 0xBF
  u16 out;         // 0xC0, frames out
  u8 _c2[2];
};
static_assert(sizeof(struct Tongue) == sizeof(struct Enemy));

enum {
  FROG_INTRO,
  FROG_WAIT,
  FROG_IDLE,
  FROG_HOP,
  FROG_LEAP,
  FROG_CANOPY,
  FROG_GUARD,
  FROG_SUMMON,
  FROG_TONGUE,
  FROG_HIT,
  FROG_GROW,
  GROWN_IDLE,
  GROWN_HOP,
  GROWN_LEAP,
  GROWN_SPIT,
  GROWN_GUARD,
  GROWN_SUMMON,
  GROWN_TONGUE,
  GROWN_HIT,
  GROWN_GLOAT,
  GROW_AGAIN,
  BIG_IDLE,
  BIG_BUBBLES,
  BIG_ROLL,
  BIG_HIT,
  BIG_GLOAT,
  FROG_EAT,
  GROWN_EAT,
};

#define FROG(n) MOTION(DM212_Z2_FROG, (n))
#define TREE_FROG(n) MOTION(AP_SHEET_Z2_TREE_FROG, (n))
#define BUBBLE(n) MOTION(AP_SHEET_Z2_FROG_BUBBLE, (n))
#define AIRBORNE 1
#define HIDDEN 2

// clang-format off
// 0x0833c1c8
static const struct Collision sBody[28] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0x1400, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0x1400, 0x1800, 0x1800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, NO_DAMAGE, 0, 1, 0x00000001, {0x0, -0xe00, 0x2000, 0x1c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, NO_DAMAGE, 0, 0, 0x00000000, {0x0, -0xe00, 0x2000, 0x1c00}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, NO_DAMAGE, 0, 1, 0x00000001, {0x0, -0x1800, 0x2000, 0x2a00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, NO_DAMAGE, 0, 0, 0x00000000, {0x0, -0x1800, 0x2000, 0x2a00}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, NO_DAMAGE, 0, 1, 0x00000001, {0x0, -0x1200, 0x2400, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, NO_DAMAGE, 0, 0, 0x00000000, {0x0, -0x1200, 0x2400, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0x1800, 0x3000, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x0, -0x1800, 0x3000, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x200, -0x1400, 0x3600, 0x2a00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x200, -0x1400, 0x3600, 0x2a00}},
    {DDP, FACTION_NEUTRAL, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x2800, 0x2800}},
    {DRP, FACTION_NEUTRAL, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x2800, 0x2800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x0, -0xa00, 0x1800, 0x1400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x300, -0xe00, 0x1a00, 0x1c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x300, -0xe00, 0x1a00, 0x1c00}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x600, -0x1200, 0x2000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x600, -0x1200, 0x2000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x300, -0xe00, 0x1a00, 0x1c00}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0xffffffff, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0xa00, 0x1800, 0x1400}},
    {DRP, FACTION_ENEMY, 2, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x0, -0xa00, 0x1800, 0x1400}},
};
// clang-format on

#define BODY_SMALL 0
#define BODY_SMALL_AIR 2
#define BODY_GROWN 4
#define BODY_GROWN_AIR 6
#define BODY_BIG 8
#define BODY_CURL 10
#define BODY_BALL 12
#define BODY_ROLL 14
#define BODY_FULL 16
#define BODY_FULL_GROWN 18
#define BODY_SWELL 20
#define BODY_WALL 22
#define BODY_WALL_GROWN 24
#define BODY_SHRINK 26

// 0x0833c480: arena's ends in from its walls, by phase
static const u16 sMargin[3] = {0xc00, 0x1000, 0x1400};
// 0x0833c468: summoned frogs' spots from the left wall
static const s32 sSpots[6] = {0x400, 0x2c00, 0x5400, 0x7c00, 0xa400, 0xcc00};

static const struct PreloadEntity sTreeFrogSheet = {AP_SHEET_Z2_TREE_FROG, 0, 832, 9, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sBubbleSheet = {AP_SHEET_Z2_FROG_BUBBLE, 0, 699, 10, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sTintSheet = {AP_SHEET_Z2_FROG_TINT, 0, 763, 7, 0, AP_PRELOAD_SHEET, 0};

static void Frog_Init(struct Frog* p);
static void Frog_Update(struct Frog* p);
static void Frog_Die(struct Frog* p);

// clang-format off
const BossRoutine gApZ2FrogRoutine = {
    [ENTITY_INIT] =      (BossFunc)Frog_Init,
    [ENTITY_UPDATE] =    (BossFunc)Frog_Update,
    [ENTITY_DIE] =       (BossFunc)Frog_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

metatile_attr_t ApZ2Jungle2Canopy(s32 x, s32 y);
u8 makeZeroSlower(struct Zero* z, u8 val);
static struct Entity* createTreeFrog(struct Entity* boss, const Coords32* at, u8 kind, u8 n);
static struct Entity* createTongue(struct Entity* parent, const Coords32* at, u8 kind, u8 n);
static struct Entity* createSpit(struct Entity* parent, const Coords32* at, u8 kind, u8 n);
static struct Entity* createLink(struct Entity* parent, const Coords32* at, u8 kind, u8 n);
static void createLeaf(const Coords32* at);
static void createDust(const Coords32* at, u8 angle);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
  s->mode[3] = 0;
}

static void nextStep(struct Entity* s) {
  s->mode[2]++;
  s->mode[3] = 0;
}

// TRUE once, as a step starts
static bool8 entering(struct Entity* s) {
  if (s->mode[3] != 0) return FALSE;
  s->mode[3]++;
  return TRUE;
}

static bool8 animDone(struct Entity* s) { return (s->motion).state == ANIM_END; }

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void faceZero(struct Frog* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static void setBody(struct Frog* p, u8 n) { SetDDP(&p->body, &sBody[n]); }

static s32 leftEnd(struct Frog* p) { return p->left + sMargin[p->phase]; }

static s32 rightEnd(struct Frog* p) { return p->left - sMargin[p->phase] + 0xCFFF; }

static s32 endAhead(struct Frog* p) { return facingRight(&p->s) ? rightEnd(p) : leftEnd(p); }

static void enemyGone(struct Entity* e) {
  e->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(e);
  SET_ENEMY_ROUTINE(e, ENTITY_DISAPPEAR);
}

static void projectileGone(struct Entity* e) {
  e->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(e);
  SET_PROJECTILE_ROUTINE(e, ENTITY_DISAPPEAR);
}

static void gravity(struct Entity* s) {
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

// 0x08057a70
static bool8 inCanopy(struct Frog* p) { return ApZ2Jungle2Canopy((p->s).coord.x, p->floor - PIXEL(128)) != 0; }

static void leaf(s32 x, s32 y) {
  Coords32 at;
  at.x = x;
  at.y = y;
  createLeaf(&at);
}

// 0x080579b4: spot no summoned frog took, of a few tried
static u8 spot(struct Frog* p, Coords32* at) {
  u8 r = (RANDOM(RNG_0202f388) & 0x7FFF) % 6, n = p->phase == 0 ? 3 : 4, i, k = 0;
  for (i = 0; i < n; i++) {
    k = (r + i) % 6;
    if (!((p->spots >> k) & 1)) break;
  }
  at->x = p->left + sSpots[k];
  at->y = p->floor - PIXEL(160);
  return k;
}

// 0x08057938
static void onHit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = body->parent;
  struct Entity* other = (body->enemy)->parent;
  if ((body->hitboxFlags & 4) && other->kind == ENTITY_PLAYER && s->mode[1] == BIG_ROLL &&
      (s->mode[2] == 2 || s->mode[2] == 4 || s->mode[2] == 8) && !isSoundPlaying(SE_Z2_DESERT_TAIL_HIT)) {
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
  }
  if (body->hitboxFlags & 1) s->work[3] = s->coord.x < (pZero2->s).coord.x;
}

// 0x080578b0: Zero's buster shot coming at it
static bool8 shotIncoming(struct Frog* p) {
  struct Entity* s = &p->s;
  struct Entity* shot = GetNearestEntity(gWeaponHeaderPtr, &s->coord);
  s32 zx = (pZero2->s).coord.x, h;
  if (shot == NULL) return FALSE;
  if (p->phase == 0) {
    h = 0x1B00;
  } else if (p->phase == 1) {
    h = 0x1F00;
  } else {
    return FALSE;
  }
  if (shot->id != WEAPON_MOVE_Z_BUSTER) return FALSE;
  if (shot->coord.x < s->coord.x ? shot->coord.x >= zx : (s->coord.x < shot->coord.x && zx < shot->coord.x)) {
    return FALSE;
  }
  if ((u32)(shot->coord.y - (s->coord.y - h / 2) + h / 2) > (u32)h) return FALSE;
  return (u32)(shot->coord.x - s->coord.x + PIXEL(120)) <= PIXEL(240);
}

// 0x08051518
static void Frog_Init(struct Frog* p) {
  struct Entity* s = &p->s;
  bool8 right = s->coord.x < (pZero2->s).coord.x;
  ApLoadSheet(&sTreeFrogSheet);
  ApLoadSheet(&sBubbleSheet);
  ApLoadSheet(&sTintSheet);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  SET_XFLIP(p, right);
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = s->d.y = 0;
  p->last = FROG_IDLE;
  p->phase = 0;
  p->floor = FUN_08009f6c(s->coord.x, s->coord.y);
  p->left = FUN_0800a31c(s->coord.x, p->floor - PIXEL(80));
  s->coord.y = p->floor - PIXEL(128);
  p->air = HIDDEN;
  p->frogs = 0;
  p->ready = FALSE;
  p->reach = PIXEL(80);
  s->unk_2c = createLink(s, &s->coord, 1, 0);
  p->ateTough = FALSE;
  ResetBossBody((struct Boss*)p, sBody, 64);
  (p->body).fn = onHit;
  Frog_Update(p);
}

typedef void (*FrogFunc)(struct Frog*);
static const FrogFunc sStates[28];

// 0x08051728
static void Frog_Update(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 hit;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = ((p->body).status & BODY_STATUS_SLASHED) != 0;
    s->mode[2] = 0;
    Frog_Die(p);
    return;
  }
  if (p->ready && shotIncoming(p)) {
    if (p->phase == 0 && s->mode[1] != FROG_GUARD) {
      p->resume = s->mode[1];
      setMode(s, FROG_GUARD);
    } else if (p->phase == 1 && s->mode[1] != GROWN_GUARD) {
      p->resume = s->mode[1];
      setMode(s, GROWN_GUARD);
    }
  }
  if ((p->body).status & BODY_STATUS_WHITE) {
    p->hungry = FALSE;
    hit = p->phase == 0 ? FROG_HIT : p->phase == 1 ? GROWN_HIT : BIG_HIT;
    if (p->phase == 0 && s->mode[1] != FROG_HIT && !p->committed) {
      p->resume = s->mode[1];
      setMode(s, FROG_HIT);
    } else if (p->phase != 0 && s->mode[1] != hit) {
      setMode(s, hit);
    }
  }
  sStates[s->mode[1]](p);
  p->frogNear = FALSE;
}

static void dropContact(struct Frog* p) {
  struct Entity* s = &p->s;
  if (s->unk_2c != NULL) projectileGone(s->unk_2c);
  EXIT_BODY(p);
  if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
    gStageRun.missionStatus &= ~MISSION_STAY;
    gStageRun.missionStatus |= MISSION_SUCCESS;
  }
}

static void explode(struct Frog* p, s32 dx) {
  struct Entity* s = &p->s;
  Coords32 at;
  at.x = dx;
  at.y = -PIXEL(16);
  s->unk_28 = CreateBossExplosion(s, &at);
  s->mode[2]++;
}

// 0x08056d40, 0x08056e88: knocked over, or cut in two, until script's flag 7
static void Frog_Die(struct Frog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  bool8 slashed = s->mode[1] != 0;
  switch (s->mode[2]) {
    case 0:
      dropContact(p);
      if (!slashed) {
        SetMotion(s, FROG(0x10));
        s->mode[2]++;
        UpdateEntityAnim(s);
        if (animDone(s)) s->mode[2]++;
        break;
      }
      PlaySound(SE_LIGHT);
      SetMotion(s, FROG(0x12));
      at.x = s->coord.x + (facingRight(s) ? -PIXEL(2) : PIXEL(2));
      at.y = s->coord.y + PIXEL(1);
      s->unk_2c = createTongue(s, &at, 2, 0);
      s->work[2] = 0;
      s->d.x = 72;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (!slashed) {
        if (animDone(s)) s->mode[2]++;
        break;
      }
      s->coord.x += facingRight(s) ? s->d.x : -s->d.x;
      s->d.x -= 2;
      if (s->d.x <= 0) s->mode[2]++;
      break;
    case 2:
      if (!slashed) {
        SetMotion(s, FROG(0x11));
        s->mode[2]++;
        UpdateEntityAnim(s);
        if (s->scriptEntity->flags & 0x80) explode(p, 0);
        break;
      }
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 0x80) explode(p, facingRight(s) ? -PIXEL(13) : PIXEL(13));
      break;
    case 3:
      UpdateEntityAnim(s);
      if (!slashed) {
        if (s->scriptEntity->flags & 0x80) explode(p, 0);
        break;
      }
      FALLTHROUGH;
    case 4:
      if (!slashed) UpdateEntityAnim(s);
      if (s->unk_28->mode[0] <= ENTITY_UPDATE) break;
      if (slashed && s->unk_2c != NULL) enemyGone(s->unk_2c);
      s->flags &= ~DISPLAY;
      gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// --------------------------------------------

/*
  0x08057034: next move, small. A move ends here having put back what it interrupted, so
  hop, leap and the pause count as what came before them
*/
static void pickSmall(struct Frog* p) {
  struct Entity* s = &p->s;
  bool8 hit = FALSE, ate = FALSE;
  u8 m, next, r;
  switch (s->mode[1]) {
    case FROG_IDLE:
    case FROG_HOP:
    case FROG_LEAP:
      s->mode[1] = p->resume;
      break;
    case FROG_GUARD:
    case FROG_HIT:
    case GROWN_HIT:
      hit = TRUE;
      s->mode[1] = p->resume;
      break;
    case FROG_EAT:
      ate = TRUE;
      s->mode[1] = p->resume;
      break;
  }
  m = s->mode[1];
  if ((RANDOM(RNG_0202f388) & 15) <= 7 && !hit) {
    if (p->last == m && m == FROG_HOP) {
      next = FROG_LEAP;
    } else {
      next = (RANDOM(RNG_0202f388) & 15) <= 7 ? FROG_HOP : FROG_LEAP;
    }
  } else if (gScore.total->rank > 4) {
    if (p->last != m) {
      r = (RANDOM(RNG_0202f388) & 0x7FFF) % 20;
      next = r <= 1 ? FROG_IDLE : r <= 5 ? FROG_CANOPY : r <= 9 ? FROG_TONGUE : FROG_SUMMON;
    } else if (m == FROG_IDLE) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 3 ? FROG_SUMMON : r <= 7 ? FROG_TONGUE : FROG_CANOPY;
    } else if (m == FROG_CANOPY) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? FROG_IDLE : r <= 6 ? FROG_TONGUE : FROG_SUMMON;
    } else if (m == FROG_SUMMON) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? FROG_IDLE : r <= 6 ? FROG_TONGUE : FROG_CANOPY;
    } else if (m == FROG_TONGUE) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? FROG_IDLE : r <= 8 ? FROG_CANOPY : FROG_SUMMON;
    } else {
      r = (RANDOM(RNG_0202f388) & 0x7FFF) % 22;
      next = r <= 1 ? FROG_IDLE : r <= 5 ? FROG_CANOPY : r <= 9 ? FROG_SUMMON : r <= 13 ? FROG_TONGUE : FROG_EAT;
    }
  } else if (p->last == m && m == FROG_IDLE) {
    next = (RANDOM(RNG_0202f388) & 15) > 7 ? FROG_CANOPY : FROG_SUMMON;
  } else if (p->last == m && m == FROG_CANOPY) {
    next = (RANDOM(RNG_0202f388) & 7) <= 1 ? FROG_IDLE : FROG_SUMMON;
  } else if (p->last == m && m == FROG_SUMMON) {
    next = (RANDOM(RNG_0202f388) & 7) <= 1 ? FROG_IDLE : FROG_CANOPY;
  } else {
    r = (RANDOM(RNG_0202f388) & 0x7FFF) % 10;
    next = r <= 1 ? FROG_IDLE : r <= 5 ? FROG_CANOPY : FROG_SUMMON;
  }
  if (!ate && p->frogs != 0 && p->frogNear && (RANDOM(RNG_0202f388) & 3)) {
    p->resume = m;
    s->mode[1] = FROG_EAT;
  } else {
    if ((next >= FROG_IDLE && next <= FROG_LEAP) || next == FROG_GUARD) p->resume = m;
    p->last = m;
    s->mode[1] = next;
  }
  s->mode[2] = s->mode[3] = 0;
  p->frogNear = FALSE;
}

// 0x080573fc: the same, grown
static void pickGrown(struct Frog* p) {
  struct Entity* s = &p->s;
  bool8 hit = FALSE, ate = FALSE;
  u8 m, next, r;
  switch (s->mode[1]) {
    case GROWN_IDLE:
    case GROWN_HOP:
    case GROWN_LEAP:
      s->mode[1] = p->resume;
      break;
    case GROWN_GUARD:
    case GROWN_HIT:
    case BIG_HIT:
      hit = TRUE;
      s->mode[1] = p->resume;
      break;
    case GROWN_EAT:
      ate = TRUE;
      s->mode[1] = p->resume;
      break;
  }
  m = s->mode[1];
  if ((RANDOM(RNG_0202f388) & 15) <= 7 && !hit) {
    if (p->last == m && m == GROWN_HOP) {
      next = GROWN_LEAP;
    } else {
      next = (RANDOM(RNG_0202f388) & 15) <= 7 ? GROWN_HOP : GROWN_LEAP;
    }
  } else if (gScore.total->rank > 4) {
    if (p->last != m) {
      r = (RANDOM(RNG_0202f388) & 0x7FFF) % 20;
      next = r <= 1 ? GROWN_IDLE : r <= 5 ? GROWN_SPIT : r <= 9 ? GROWN_TONGUE : GROWN_SUMMON;
    } else if (m == GROWN_IDLE) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 3 ? GROWN_SUMMON : r <= 7 ? GROWN_TONGUE : GROWN_SPIT;
    } else if (m == GROWN_SPIT) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? GROWN_IDLE : r <= 6 ? GROWN_TONGUE : GROWN_SUMMON;
    } else if (m == GROWN_SUMMON) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? GROWN_IDLE : r <= 6 ? GROWN_TONGUE : GROWN_SPIT;
    } else if (m == GROWN_TONGUE) {
      r = RANDOM(RNG_0202f388) & 15;
      next = r <= 1 ? GROWN_IDLE : r <= 8 ? GROWN_SPIT : GROWN_SUMMON;
    } else if (m == GROWN_EAT) {
      r = (RANDOM(RNG_0202f388) & 0x7FFF) % 18;
      next = r <= 1 ? GROWN_IDLE : r <= 5 ? GROWN_SUMMON : r <= 9 ? GROWN_TONGUE : GROWN_SPIT;
    } else {
      r = (RANDOM(RNG_0202f388) & 0x7FFF) % 20;
      next = r <= 1 ? GROWN_IDLE : r <= 5 ? GROWN_SPIT : r <= 9 ? GROWN_TONGUE : GROWN_SUMMON;
    }
  } else if (p->last == m && m == GROWN_IDLE) {
    next = (RANDOM(RNG_0202f388) & 15) > 7 ? GROWN_SPIT : GROWN_SUMMON;
  } else if (p->last == m && m == GROWN_SPIT) {
    next = (RANDOM(RNG_0202f388) & 7) <= 1 ? GROWN_IDLE : GROWN_SUMMON;
  } else if (p->last == m && m == GROWN_SUMMON) {
    next = (RANDOM(RNG_0202f388) & 7) <= 1 ? GROWN_IDLE : GROWN_SPIT;
  } else {
    r = (RANDOM(RNG_0202f388) & 0x7FFF) % 10;
    next = r <= 1 ? GROWN_IDLE : r <= 5 ? GROWN_SPIT : GROWN_SUMMON;
  }
  if (!ate && p->frogs != 0 && p->frogNear && (RANDOM(RNG_0202f388) & 3)) {
    p->resume = m;
    s->mode[1] = GROWN_EAT;
  } else {
    if ((next >= GROWN_IDLE && next <= GROWN_LEAP) || next == GROWN_GUARD) p->resume = m;
    p->last = m;
    s->mode[1] = next;
  }
  s->mode[2] = s->mode[3] = 0;
  p->frogNear = FALSE;
}

// 0x08057820: grown twice, bubbles or a roll
static void pickBig(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 m = s->mode[1], next;
  if (p->last != m) {
    next = (RANDOM(RNG_0202f388) & 15) > 7 ? BIG_ROLL : BIG_BUBBLES;
  } else if (m == BIG_IDLE) {
    next = (RANDOM(RNG_0202f388) & 0x7FFF) % 14 > 6 ? BIG_ROLL : BIG_BUBBLES;
  } else {
    next = m == BIG_BUBBLES ? BIG_ROLL : BIG_BUBBLES;
  }
  p->last = m;
  setMode(s, next);
}

static void pick(struct Frog* p) {
  if (p->phase == 0) {
    pickSmall(p);
  } else if (p->phase == 1) {
    pickGrown(p);
  } else {
    pickBig(p);
  }
}

// --------------------------------------------
// Steps several moves share

static void playStep(struct Frog* p, motion_t m) {
  struct Entity* s = &p->s;
  if (entering(s)) SetMotion(s, m);
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void holdStep(struct Frog* p, motion_t m, u8 frames) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, m);
    s->work[2] = frames;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) nextStep(s);
}

static void restStep(struct Frog* p, motion_t m, u8 frames) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, m);
    s->work[2] = frames;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static void landStep(struct Frog* p, motion_t m, u8 body) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_LAND);
    SetMotion(s, m);
    setBody(p, body);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

// Arc of work2 frames, then down on the floor
static void flyStep(struct Frog* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  gravity(s);
  if (--s->work[2] != 0) return;
  s->coord.y = p->floor;
  p->air &= ~AIRBORNE;
  p->ready = TRUE;
  nextStep(s);
}

static void takeOff(struct Frog* p, motion_t m, u8 body, u8 frames) {
  struct Entity* s = &p->s;
  PlaySound(SE_Z2_FROG_LAND);
  SetMotion(s, m);
  setBody(p, body);
  p->air |= AIRBORNE;
  p->ready = FALSE;
  s->work[2] = frames;
}

// Falls to a floor, d.x along
static void dropStep(struct Frog* p, bool8 along) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (along) s->coord.x += s->d.x;
  gravity(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = p->floor;
  p->air &= ~AIRBORNE;
  p->ready = TRUE;
  nextStep(s);
}

// Knocked back inside the arena, hitting its ends dead
static void knocked(struct Frog* p) {
  struct Entity* s = &p->s;
  if (!(p->air & AIRBORNE)) return;
  s->coord.x += s->d.x;
  if (s->d.x < 0 && s->coord.x < leftEnd(p)) {
    s->coord.x = leftEnd(p);
    s->d.x = 0;
  } else if (s->d.x >= 0 && s->coord.x > rightEnd(p)) {
    s->coord.x = rightEnd(p);
    s->d.x = 0;
  }
  gravity(s);
  if (s->coord.y <= p->floor) return;
  s->coord.y = p->floor;
  p->air &= ~AIRBORNE;
}

static void hopArc(struct Frog* p, motion_t m, u8 body, s32 hop, u32 lift) {
  struct Entity* s = &p->s;
  s32 to = s->coord.x + (facingRight(s) ? hop : -hop), end;
  u16 n;
  s->d.y = -(u16)Sqrt(lift);
  n = (u16)(-(s->d.y >> 5));
  if (facingRight(s)) {
    end = rightEnd(p);
    s->d.x = to > end ? (end - s->coord.x) / n : hop / n;
  } else {
    end = leftEnd(p);
    s->d.x = to < end ? (end - s->coord.x) / n : -(hop / n);
  }
  takeOff(p, m, body, n);
}

// --------------------------------------------

// 0x08051888: rustles in the canopy, drops, then waits for the script
static void Intro_Rustle(struct Frog* p) {
  struct Entity* s = &p->s;
  s32 x;
  if (entering(s)) {
    if (inCanopy(p)) PlaySound(SE_Z2_LEAVES);
    SetMotion(s, FROG(2));
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  if (s->work[2] == 4 || s->work[2] == 32 || s->work[2] == 40) {
    if (!inCanopy(p)) return;
    x = s->coord.x + PIXEL((RANDOM(RNG_0202f388) & 31) - 16);
    leaf(x, p->floor - PIXEL(120));
  } else if (s->work[2] == 48) {
    nextStep(s);
  }
}

static void Intro_Fall(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) s->d.y = 0;
  UpdateEntityAnim(s);
  gravity(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = p->floor;
  nextStep(s);
}

static void Intro_Land(struct Frog* p) { landStep(p, FROG(3), BODY_SMALL); }

static void Intro_Wait(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) SetMotion(s, FROG(0));
  UpdateEntityAnim(s);
  if (s->scriptEntity->flags & 1) setMode(s, FROG_WAIT);
}

static const FrogFunc sIntro[4] = {Intro_Rustle, Intro_Fall, Intro_Land, Intro_Wait};

// 0x08051a38: croaks while the script talks
static void Wait_Sit(struct Frog* p) { holdStep(p, FROG(0), 32); }
static void Wait_Puff(struct Frog* p) { playStep(p, FROG(0x33)); }
static void Wait_Open(struct Frog* p) { holdStep(p, FROG(10), 8); }

static void Wait_Croak(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_CROAK);
    SetMotion(s, FROG(11));
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] == 64) PlaySound(SE_Z2_FROG_CROAK);
  if (s->work[2] > 95) nextStep(s);
}

static void Wait_Close(struct Frog* p) { holdStep(p, FROG(10), 4); }
static void Wait_Settle(struct Frog* p) { playStep(p, FROG(0x27)); }

static void Wait_Go(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) SetMotion(s, FROG(0));
  UpdateEntityAnim(s);
  if (!(gStageRun.vm.active & VM_ACTIVE)) pick(p);
}

static const FrogFunc sWait[7] = {Wait_Sit, Wait_Puff, Wait_Open, Wait_Croak, Wait_Close, Wait_Settle, Wait_Go};

// 0x08051c08, 0x08053c44, 0x08055b44
static void Frog_Idle(struct Frog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    faceZero(p);
    SetMotion(s, FROG(0));
    setBody(p, BODY_SMALL);
    p->ready = TRUE;
    p->committed = FALSE;
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static void Grown_Idle(struct Frog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    faceZero(p);
    SetMotion(s, FROG(0x14));
    setBody(p, BODY_GROWN);
    p->ready = TRUE;
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static void Big_Idle(struct Frog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    faceZero(p);
    SetMotion(s, FROG(0x23));
    setBody(p, BODY_BIG);
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

// --------------------------------------------
// 0x08051cbc, 0x08053cf4: hop at Zero

static void Hop_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(1));
    setBody(p, BODY_SMALL);
    p->ready = TRUE;
    p->committed = FALSE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Hop_Fly(struct Frog* p) {
  if (entering(&p->s)) hopArc(p, FROG(2), BODY_SMALL_AIR, PIXEL(64), 0x180000);
  flyStep(p);
}

static void Hop_Land(struct Frog* p) { landStep(p, FROG(3), BODY_SMALL); }
static void Hop_Rest(struct Frog* p) { restStep(p, FROG(0), 4); }

static const FrogFunc sHop[4] = {Hop_Crouch, Hop_Fly, Hop_Land, Hop_Rest};

static void GrownHop_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(0x15));
    setBody(p, BODY_GROWN);
    p->ready = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void GrownHop_Fly(struct Frog* p) {
  if (entering(&p->s)) hopArc(p, FROG(0x16), BODY_GROWN_AIR, PIXEL(56), 0x140000);
  flyStep(p);
}

static void GrownHop_Land(struct Frog* p) { landStep(p, FROG(0x17), BODY_GROWN); }
static void GrownHop_Rest(struct Frog* p) { restStep(p, FROG(0x14), 4); }

static const FrogFunc sGrownHop[4] = {GrownHop_Crouch, GrownHop_Fly, GrownHop_Land, GrownHop_Rest};

// --------------------------------------------
// 0x08051f24, 0x08053f5c: leap to the end past Zero

static void Leap_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(1));
    s->d.x = (endAhead(p) - s->coord.x) / 56;
    s->d.y = -0x700;
    setBody(p, BODY_SMALL);
    p->ready = TRUE;
    p->committed = FALSE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Leap_Fly(struct Frog* p) {
  if (entering(&p->s)) takeOff(p, FROG(2), BODY_SMALL_AIR, 56);
  flyStep(p);
}

static const FrogFunc sLeap[4] = {Leap_Crouch, Leap_Fly, Hop_Land, Hop_Rest};

static void GrownLeap_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(0x15));
    s->d.x = (endAhead(p) - s->coord.x) / 48;
    s->d.y = -0x600;
    setBody(p, BODY_GROWN);
    p->ready = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void GrownLeap_Fly(struct Frog* p) {
  if (entering(&p->s)) takeOff(p, FROG(0x16), BODY_GROWN_AIR, 48);
  flyStep(p);
}

static const FrogFunc sGrownLeap[4] = {GrownLeap_Crouch, GrownLeap_Fly, GrownHop_Land, GrownHop_Rest};

// --------------------------------------------
// 0x0805214c: up into the canopy, across to the middle, and two arms down at Zero

static void Canopy_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(1));
    s->d.x = (endAhead(p) - s->coord.x) / 56;
    s->d.y = -0x700;
    setBody(p, BODY_SMALL);
    p->ready = FALSE;
    p->committed = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Canopy_Rise(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 n;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_LAND);
    SetMotion(s, FROG(2));
    s->d.y = -0x800;
    setBody(p, BODY_SMALL_AIR);
    p->air |= AIRBORNE;
    s->work[2] = 18;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  if (--s->work[2] != 0) return;
  if (inCanopy(p)) {
    for (n = (RANDOM(RNG_0202f388) & 1) + 2; n != 0; n--) {
      s32 x = s->coord.x + PIXEL((RANDOM(RNG_0202f388) & 31) - 16);
      leaf(x, p->floor - PIXEL(136) + PIXEL(RANDOM(RNG_0202f388) & 31));
    }
  }
  nextStep(s);
}

// Out of the leaves, it drops where it is
static bool8 outOfCanopy(struct Frog* p) {
  struct Entity* s = &p->s;
  if (!(p->air & HIDDEN) || inCanopy(p)) return FALSE;
  p->air &= ~HIDDEN;
  s->mode[2] = 7;
  s->mode[3] = 0;
  return TRUE;
}

static void Canopy_Cross(struct Frog* p) {
  struct Entity* s = &p->s;
  s32 middle = p->left + PIXEL(104);
  u16 dist;
  if (entering(s)) {
    if (inCanopy(p)) PlaySound(SE_Z2_LEAVES);
    s->coord.y = p->floor - PIXEL(160);
    dist = s->coord.x >= middle ? s->coord.x - middle : middle - s->coord.x;
    s->work[2] = dist <= 0x1FF ? 1 : dist >> 9;
    s->d.x = middle < s->coord.x ? -0x200 : 0x200;
    p->arms[0] = p->arms[1] = NULL;
    if (!inCanopy(p)) p->air &= ~HIDDEN;
  }
  if (outOfCanopy(p)) return;
  UpdateEntityAnim(s);
  s->work[2]--;
  s->coord.x += s->d.x;
  if (inCanopy(p) && (s->work[2] & 31) == 0 && ((s->work[2] & 63) != 0 || (RANDOM(RNG_0202f388) & 3) == 0)) {
    leaf(s->coord.x, p->floor - PIXEL(120));
  }
  if (s->work[2] == 0) nextStep(s);
}

static void Canopy_Sink(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 n;
  if (entering(s)) {
    SetMotion(s, FROG(4));
    s->coord.x = p->left + PIXEL(104);
    if (inCanopy(p)) {
      s->d.y = p->floor - PIXEL(128);
      for (n = (RANDOM(RNG_0202f388) & 1) + 1; n != 0; n--) {
        s32 x = s->coord.x + PIXEL((RANDOM(RNG_0202f388) & 31) - 16);
        leaf(x, p->floor - PIXEL(136) + PIXEL(RANDOM(RNG_0202f388) & 31));
      }
    } else {
      s->d.y = p->floor - PIXEL(152);
    }
    s->work[2] = 0;
    UpdateEntityAnim(s);
  }
  if (outOfCanopy(p)) return;
  s->work[2] += 4;
  s->coord.y = s->d.y + SIN(s->work[2]) * 42;
  if (s->work[2] > 63) nextStep(s);
}

static void Canopy_Bob(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    if (inCanopy(p)) PlaySound(SE_Z2_LEAVES);
    p->committed = FALSE;
  }
  if (outOfCanopy(p)) return;
  s->work[2] += 2;
  UpdateEntityAnim(s);
  s->coord.y = s->d.y + SIN(s->work[2]) * 42;
  if (animDone(s) && s->work[2] > 87) nextStep(s);
}

static void Canopy_Pause(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) s->work[2] = 4;
  UpdateEntityAnim(s);
  if (outOfCanopy(p)) return;
  if (--s->work[2] == 0) nextStep(s);
}

static void Canopy_Arms(struct Frog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i;
  if (entering(s)) {
    at.x = s->coord.x - PIXEL(8);
    at.y = s->coord.y + PIXEL(3);
    p->arms[0] = createTongue(s, &at, 0, 0);
    at.x = s->coord.x + PIXEL(9);
    p->arms[1] = createTongue(s, &at, 0, 1);
    p->armsBack = 0;
    SetMotion(s, FROG(5));
  }
  if (outOfCanopy(p)) return;
  UpdateEntityAnim(s);
  for (i = 0; i < 2; i++) {
    if (p->arms[i] != NULL && p->arms[i]->mode[1] == 5) {
      p->arms[i]->mode[1]++;
      p->armsBack++;
    }
  }
  if (p->armsBack == 2) nextStep(s);
}

static void Canopy_Drop(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (entering(s)) {
    for (i = 0; i < 2; i++) {
      if (p->arms[i] != NULL) enemyGone(p->arms[i]);
    }
    faceZero(p);
    SetMotion(s, FROG(2));
    setBody(p, BODY_SMALL_AIR);
    s->d.y = 0;
  }
  dropStep(p, FALSE);
}

static const FrogFunc sCanopy[10] = {Canopy_Crouch, Canopy_Rise,  Canopy_Cross, Canopy_Sink, Canopy_Bob,
                                     Canopy_Pause,  Canopy_Arms,  Canopy_Drop,  Hop_Land,    Hop_Rest};

// --------------------------------------------
// 0x08052a30, 0x08054674: braces while Zero's shot comes

static void Guard_Brace(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    if (p->phase == 0) {
      SetMotion(s, FROG(0x33));
      setBody(p, BODY_SMALL);
      p->committed = FALSE;
    } else {
      SetMotion(s, FROG(0x34));
      setBody(p, BODY_GROWN);
    }
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Guard_Open(struct Frog* p) { holdStep(p, p->phase == 0 ? FROG(10) : FROG(0x1B), 2); }

static void Guard_Swell(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(11) : FROG(0x1C));
    s->work[2] = 32;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 15) == 0) PlaySound(p->phase == 0 ? SE_Z2_FROG_CROAK : SE_Z2_FROG_CROAK_MID);
  if ((!shotIncoming(p) && (s->motion).state == ANIM_NEXT_GOTO) || --s->work[2] == 0) nextStep(s);
}

static void Guard_Close(struct Frog* p) { playStep(p, p->phase == 0 ? FROG(10) : FROG(0x1B)); }
static void Guard_Settle(struct Frog* p) { playStep(p, p->phase == 0 ? FROG(0x27) : FROG(0x28)); }

static void Guard_End(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    s->work[2] = 1;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  p->ready = FALSE;
  pick(p);
}

static const FrogFunc sGuard[6] = {Guard_Brace, Guard_Open, Guard_Swell, Guard_Close, Guard_Settle, Guard_End};

// --------------------------------------------
// 0x08052c44, 0x08054884: jumps to a wall, croaks three tree frogs down (four grown), one tougher

static void Summon_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SET_XFLIP(p, (pZero2->s).coord.x < s->coord.x);
    if (p->phase == 0) {
      SetMotion(s, FROG(1));
      s->d.x = (endAhead(p) - s->coord.x) / 28;
      s->d.y = -0x700;
      setBody(p, BODY_WALL);
      p->committed = FALSE;
    } else {
      SetMotion(s, FROG(0x15));
      setBody(p, BODY_WALL_GROWN);
      s->d.x = (endAhead(p) - s->coord.x) / 27;
      s->d.y = -0x6C0;
    }
    p->ready = FALSE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Summon_Jump(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_LAND);
    SetMotion(s, p->phase == 0 ? FROG(2) : FROG(0x16));
    p->air |= AIRBORNE;
    s->work[2] = p->phase == 0 ? 28 : 27;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  gravity(s);
  if (--s->work[2] != 0) return;
  s->coord.x = endAhead(p);
  nextStep(s);
}

static void Summon_Cling(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0x0E) : FROG(0x1F));
    setBody(p, p->phase == 0 ? BODY_SMALL : BODY_GROWN);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Summon_Croak(struct Frog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 k, w;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0x0F) : FROG(0x20));
    p->summoned = 0;
    p->tough = p->phase == 0 ? (RANDOM(RNG_0202f388) & 0x7FFF) % 3 : RANDOM(RNG_0202f388) & 3;
    p->spots = 0;
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  w = ++s->work[2];
  if ((w & 15) == 0) PlaySound(p->phase == 0 ? SE_Z2_FROG_CROAK : SE_Z2_FROG_CROAK_MID);
  AppendQuake(p->phase == 0 ? 1 : 4, &s->coord);
  if (w == (p->phase == 0 ? 88 : 128)) {
    nextStep(s);
    return;
  }
  if (w != 2 && w != 10 && w != 42 && !(p->phase != 0 && w == 74)) return;
  if (p->summoned > (p->phase == 0 ? 2 : 3) || p->frogs > 5) return;
  k = spot(p, &at);
  if (createTreeFrog(s, &at, p->tough == 0 ? 2 : 1, 0) != NULL) {
    p->frogs++;
    p->summoned++;
  }
  p->spots |= 1 << k;
  p->tough--;
}

static void Summon_Off(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(2) : FROG(0x16));
    setBody(p, p->phase == 0 ? BODY_SMALL_AIR : BODY_GROWN_AIR);
    s->d.x = facingRight(s) ? -PIXEL(1) : PIXEL(1);
    s->d.y = 0;
  }
  dropStep(p, TRUE);
}

static const FrogFunc sSummon[7] = {Summon_Crouch, Summon_Jump, Summon_Cling, Summon_Croak, Summon_Off, Hop_Land, Hop_Rest};
static const FrogFunc sGrownSummon[7] = {Summon_Crouch, Summon_Jump, Summon_Cling,  Summon_Croak,
                                         Summon_Off,    GrownHop_Land, GrownHop_Rest};

// --------------------------------------------
// 0x080532cc, 0x08054ef4: tongue at Zero. Swallowing him grows it

static struct Tongue* tongueOut(struct Frog* p) { return (struct Tongue*)p->arms[0]; }

static void Tongue_Crouch(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, p->phase == 0 ? FROG(1) : FROG(0x15));
    setBody(p, p->phase == 0 ? BODY_SMALL : BODY_GROWN);
    p->ready = FALSE;
    if (p->phase == 0) p->committed = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Tongue_Hop(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_LAND);
    SetMotion(s, p->phase == 0 ? FROG(2) : FROG(0x16));
    s->d.y = p->phase == 0 ? -0x200 : -0x180;
    setBody(p, p->phase == 0 ? BODY_SMALL_AIR : BODY_GROWN_AIR);
    p->air |= AIRBORNE;
  }
  UpdateEntityAnim(s);
  gravity(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = p->floor;
  p->air &= ~AIRBORNE;
  nextStep(s);
}

// Not facing Zero any more, it gives up
static void Tongue_Land(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_LAND);
    SetMotion(s, p->phase == 0 ? FROG(3) : FROG(0x17));
    setBody(p, p->phase == 0 ? BODY_SMALL : BODY_GROWN);
  }
  UpdateEntityAnim(s);
  if (!animDone(s)) return;
  if (facingRight(s) != (s->coord.x < (pZero2->s).coord.x)) {
    pick(p);
  } else {
    nextStep(s);
  }
}

static void Tongue_Open(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(9) : FROG(0x1A));
    if (p->phase == 0) setBody(p, BODY_SMALL);
  }
  UpdateEntityAnim(s);
  if (!animDone(s)) return;
  PlaySound(SE_Z2_FROG_MOUTH);
  nextStep(s);
}

static void Tongue_Hold(struct Frog* p) { holdStep(p, p->phase == 0 ? FROG(10) : FROG(0x1B), 4); }

static void Tongue_Shoot(struct Frog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  struct Tongue* t;
  if (entering(s)) {
    if (p->phase == 0) {
      at.x = s->coord.x + (facingRight(s) ? PIXEL(14) : -PIXEL(14));
      at.y = s->coord.y - PIXEL(16);
    } else {
      at.x = s->coord.x + (facingRight(s) ? PIXEL(18) : -PIXEL(18));
      at.y = s->coord.y - PIXEL(20);
    }
    p->arms[0] = createTongue(s, &at, 1, p->phase);
    p->ready = FALSE;
  }
  UpdateEntityAnim(s);
  t = tongueOut(p);
  if (t == NULL) {
    s->mode[2] = 10;
    s->mode[3] = 0;
  } else if (t->caught) {
    setBody(p, p->phase == 0 ? BODY_FULL : BODY_FULL_GROWN);
    if ((t->s).mode[0] > ENTITY_UPDATE) s->mode[2]++;
    nextStep(s);
  } else if ((t->s).mode[0] > ENTITY_UPDATE) {
    s->mode[2] = 10;
    s->mode[3] = 0;
  }
}

static void Tongue_Back(struct Frog* p) {
  struct Entity* s = &p->s;
  struct Tongue* t = tongueOut(p);
  if (entering(s)) SetMotion(s, p->phase == 0 ? FROG(10) : FROG(0x1B));
  UpdateEntityAnim(s);
  if (t == NULL || (t->s).mode[0] > ENTITY_UPDATE) nextStep(s);
}

static void Tongue_Close(struct Frog* p) { playStep(p, p->phase == 0 ? FROG(0x27) : FROG(0x28)); }

static void Tongue_Swallow(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    s->work[2] = 2;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (p->phase == 0) {
    p->last = FROG_TONGUE;
    setMode(s, FROG_GROW);
  } else {
    p->last = GROWN_TONGUE;
    setMode(s, GROW_AGAIN);
  }
}

static void Tongue_Rest(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    if (p->phase == 0) {
      setBody(p, BODY_SMALL);
      p->committed = FALSE;
    }
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static const FrogFunc sTongue[12] = {Tongue_Crouch, Tongue_Hop,     Tongue_Land, Tongue_Open,  Tongue_Hold,  Tongue_Shoot,
                                     Tongue_Back,   Tongue_Close,   Tongue_Swallow, Tongue_Back, Tongue_Close, Tongue_Rest};

// --------------------------------------------
// 0x080534a0: knocked back, small

static void keepFacing(struct Frog* p, bool8 scaled) {
  struct Entity* s = &p->s;
  bool8 right = facingRight(s);
  if (scaled) {
    InitScalerotMotion1(s);
  } else {
    InitNonAffineMotion(s);
  }
  ResetDynamicMotion(s);
  SET_XFLIP(p, right);
}

static void Hit_Fly(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    keepFacing(p, FALSE);
    SetMotion(s, FROG(0x10));
    (s->spr).oam.priority = 2;
    s->d.x = s->work[3] ? -0x280 : 0x280;
    s->d.y = -0x380;
    p->air |= AIRBORNE;
    setBody(p, BODY_SMALL);
    p->ready = FALSE;
    p->committed = TRUE;
  }
  UpdateEntityAnim(s);
  knocked(p);
  if (animDone(s)) nextStep(s);
}

static void Hit_Down(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x11));
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  knocked(p);
  if (s->work[2] == 0 && !(p->air & AIRBORNE)) nextStep(s);
}

static void Hit_Up(struct Frog* p) { playStep(p, FROG(0x10)); }

static const FrogFunc sHit[4] = {Hit_Fly, Hit_Down, Hit_Up, Hop_Rest};

// --------------------------------------------
// 0x08053750, 0x08055668: swells a size

static void Grow_Swell(struct Frog* p) {
  struct Entity* s = &p->s;
  u16 mag;
  if (entering(s)) {
    keepFacing(p, TRUE);
    (s->spr).mag.x = (s->spr).mag.y = 256;
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    setBody(p, p->phase == 0 ? BODY_FULL : BODY_FULL_GROWN);
    UpdateEntityAnim(s);
  }
  mag = (s->spr).mag.x + 8;
  if (mag > 0x169) {
    (s->spr).mag.x = (s->spr).mag.y = 0x16A;
    nextStep(s);
  } else {
    (s->spr).mag.x = (s->spr).mag.y = mag;
  }
}

static void Grow_Settle(struct Frog* p) {
  struct Entity* s = &p->s;
  u16 mag;
  if (entering(s)) {
    PlaySound(p->phase == 0 ? SE_Z2_FROG_CROAK_MID : SE_Z2_FROG_CROAK_BIG);
    setBody(p, p->phase == 0 ? BODY_FULL_GROWN : BODY_SWELL);
  }
  mag = (s->spr).mag.x - 1;
  if (mag > 0x155) {
    (s->spr).mag.x = (s->spr).mag.y = mag;
    return;
  }
  (s->spr).mag.x = (s->spr).mag.y = 0x155;
  p->phase++;
  nextStep(s);
}

static void Grow_Done(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    keepFacing(p, FALSE);
    if (p->phase == 1) {
      SetMotion(s, FROG(0x14));
    } else {
      SetMotion(s, FROG(0x23));
      s->coord.x += facingRight(s) ? PIXEL(2) : -PIXEL(2);
    }
    s->work[2] = 8;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (p->phase == 2) {
    if (p->last == GROWN_EAT) {
      pick(p);
    } else {
      setMode(s, BIG_GLOAT);
    }
    return;
  }
  p->reach = PIXEL(120);
  if (p->last == FROG_EAT) {
    p->last = GROWN_EAT;
    if (p->ateTough) {
      setMode(s, GROW_AGAIN);
    } else {
      pick(p);
    }
  } else {
    p->last = GROWN_EAT;
    setMode(s, GROWN_GLOAT);
  }
}

static const FrogFunc sGrow[3] = {Grow_Swell, Grow_Settle, Grow_Done};

// --------------------------------------------
// 0x08054180: grown, spits six globs that swing out and home in on Zero

static void Spit_Face(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(0x17));
    setBody(p, BODY_GROWN);
    p->ready = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Spit_Open(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_SPIKEBALL_OPEN);
    SetMotion(s, FROG(0x18));
    p->ready = FALSE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void spit(struct Frog* p, u8 kind, s32 ahead, s32 up) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 n = 16 - (RANDOM(RNG_0202f388) & 0x7FFF) % 80;
  at.x = s->coord.x + (facingRight(s) ? -ahead : ahead);
  at.y = s->coord.y - up;
  createSpit(s, &at, kind, n);
}

static void Spit_Globs(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x19));
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  switch (++s->work[2]) {
    case 2:
      PlaySound(SE_Z2_FROG_SPIT);
      spit(p, 0, PIXEL(4), PIXEL(28));
      break;
    case 10:
      spit(p, 1, -PIXEL(6), PIXEL(28));
      break;
    case 26:
      spit(p, 0, PIXEL(8), PIXEL(28));
      break;
    case 34:
      spit(p, 1, PIXEL(2), PIXEL(28));
      break;
    case 40:
      spit(p, 0, PIXEL(12), PIXEL(24));
      break;
    case 48:
      spit(p, 1, PIXEL(4), PIXEL(24));
      break;
    case 64:
      nextStep(s);
      break;
  }
}

static void Spit_Close(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x21));
    p->ready = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Spit_Rest(struct Frog* p) { restStep(p, FROG(0x14), 16); }

static const FrogFunc sSpit[5] = {Spit_Face, Spit_Open, Spit_Globs, Spit_Close, Spit_Rest};

// --------------------------------------------
// 0x080550c0, 0x08056854: a hit shrinks it a size

static void Shrink_Hit(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    keepFacing(p, FALSE);
    (s->spr).oam.priority = 2;
    SetMotion(s, p->phase == 1 ? FROG(0x21) : FROG(0x31));
    s->d.x = s->work[3] ? -0x280 : 0x280;
    s->d.y = -0x380;
    p->air |= AIRBORNE;
    setBody(p, p->phase == 1 ? BODY_GROWN : BODY_BIG);
    p->ready = FALSE;
    p->committed = TRUE;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Shrink_Squeeze(struct Frog* p) {
  struct Entity* s = &p->s;
  u16 mag;
  if (entering(s)) {
    keepFacing(p, TRUE);
    (s->spr).mag.x = (s->spr).mag.y = 256;
    SetMotion(s, p->phase == 1 ? FROG(0x22) : FROG(0x32));
    if (p->air & AIRBORNE) {
      s->d.x = s->work[3] ? -0x180 : 0x180;
      s->d.y = -0x180;
    }
    s->work[2] = 38;
  }
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  if (s->work[2] > 24) return;
  mag = (s->spr).mag.x - 7;
  knocked(p);
  if (mag > 172) {
    (s->spr).mag.x = (s->spr).mag.y = mag;
    return;
  }
  (s->spr).mag.x = (s->spr).mag.y = 172;
  nextStep(s);
}

static void Shrink_Bounce(struct Frog* p) {
  struct Entity* s = &p->s;
  u16 mag;
  if (entering(s)) setBody(p, p->phase == 1 ? BODY_SHRINK : BODY_GROWN);
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  mag = (s->spr).mag.x + 4;
  knocked(p);
  if (mag <= 193) {
    (s->spr).mag.x = (s->spr).mag.y = mag;
    return;
  }
  (s->spr).mag.x = (s->spr).mag.y = 194;
  nextStep(s);
}

static void Shrink_Land(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    keepFacing(p, FALSE);
    (s->spr).oam.priority = 2;
    if (p->phase == 1) {
      SetMotion(s, FROG(0x11));
      s->coord.x += facingRight(s) ? PIXEL(2) : -PIXEL(2);
    } else {
      SetMotion(s, FROG(0x22));
      s->coord.x -= facingRight(s) ? PIXEL(3) : -PIXEL(3);
    }
  }
  UpdateEntityAnim(s);
  if (s->work[2] != 0) s->work[2]--;
  knocked(p);
  if (s->work[2] == 0 && !(p->air & AIRBORNE)) nextStep(s);
}

static void Shrink_Up(struct Frog* p) { playStep(p, p->phase == 1 ? FROG(0x10) : FROG(0x21)); }

static void Shrink_Done(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 1 ? FROG(0) : FROG(0x14));
    s->work[2] = 2;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  p->phase--;
  p->reach = p->phase == 0 ? PIXEL(80) : PIXEL(120);
  pick(p);
}

static const FrogFunc sShrink[6] = {Shrink_Hit, Shrink_Squeeze, Shrink_Bounce, Shrink_Land, Shrink_Up, Shrink_Done};

// --------------------------------------------
// 0x080555bc, 0x080567ac: croaks over a swallowed Zero

static void Gloat_Puff(struct Frog* p) { playStep(p, p->phase == 1 ? FROG(0x2D) : FROG(0x2F)); }

static void Gloat_Croak(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 1 ? FROG(0x2E) : FROG(0x30));
    s->work[2] = 96;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 15) == 0) PlaySound(p->phase == 1 ? SE_Z2_FROG_CROAK_MID : SE_Z2_FROG_CROAK_BIG);
  if (--s->work[2] != 0) return;
  if (p->phase == 1) {
    p->ready = TRUE;
    pick(p);
  } else {
    setMode(s, BIG_ROLL);
  }
}

static const FrogFunc sGloat[2] = {Gloat_Puff, Gloat_Croak};

// --------------------------------------------
// 0x08055bec: grown twice, blows bubbles that stick to Zero and slow him

static void Bubbles_Face(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, FROG(0x24));
    setBody(p, BODY_BIG);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Bubbles_Blow(struct Frog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (entering(s)) {
    SetMotion(s, FROG(0x25));
    s->work[2] = 24;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 3) == 0) {
    at.x = s->coord.x + (facingRight(s) ? PIXEL(20) : -PIXEL(20));
    at.y = s->coord.y - PIXEL(24);
    createSpit(s, &at, 2, 0);
    if (s->work[2] == 12) PlaySound(SE_Z2_FORTRESS_SHOTS);
  }
  if (--s->work[2] == 0) nextStep(s);
}

static void Bubbles_Close(struct Frog* p) { playStep(p, FROG(0x26)); }
static void Bubbles_Rest(struct Frog* p) { restStep(p, FROG(0x23), 8); }

static const FrogFunc sBubbles[4] = {Bubbles_Face, Bubbles_Blow, Bubbles_Close, Bubbles_Rest};

// --------------------------------------------
// 0x08055d9c: grown twice, rolls along the floor and up a wall out of sight, round again from the
// other side's canopy one to three times, then drops on Zero

static void dust(struct Frog* p, s32 dx, s32 dy) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (p->distance < p->smoked + PIXEL(16)) return;
  at.x = s->coord.x + (facingRight(s) ? -dx : dx);
  at.y = s->coord.y + dy;
  CreateSmoke(3, &at);
  p->smoked = p->distance;
}

static void spin(struct Frog* p) {
  struct Entity* s = &p->s;
  s32 v = p->distance * 0x170;
  u8 a, half;
  if (v < 0) v += 255;
  a = v >> 16;
  s->angle = ~a;
  half = a << 1;
  if (half < s->work[2]) PlaySound(SE_Z2_SNOWBALL_ROLL);
  s->work[2] = half;
}

static void rollLeaves(struct Frog* p, u8 mask, u8 least, u8 spread) {
  struct Entity* s = &p->s;
  s32 x;
  u8 n;
  if (!inCanopy(p)) return;
  PlaySound(SE_Z2_LEAVES);
  for (n = (RANDOM(RNG_0202f388) & mask) + least; n != 0; n--) {
    x = s->coord.x + PIXEL((RANDOM(RNG_0202f388) & (spread * 2 - 1)) - (spread - 1));
    leaf(x, p->floor - 0x7F00 + PIXEL(RANDOM(RNG_0202f388) & 15));
  }
}

static void Roll_Curl(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    PlaySound(SE_Z2_FROG_CROAK_BIG);
    faceZero(p);
    SetMotion(s, FROG(0x29));
    setBody(p, BODY_CURL);
    p->rolled = 0;
    p->rolls = (RANDOM(RNG_0202f388) & 0x7FFF) % 3 + 1;
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Roll_Ball(struct Frog* p) {
  struct Entity* s = &p->s;
  bool8 right = facingRight(s);
  if (entering(s)) {
    InitRotatableMotion(s);
    ResetDynamicMotion(s);
    SET_XFLIP(p, right);
    (s->spr).oam.priority = 2;
    s->angle = 0;
    SetMotion(s, FROG(0x2A));
    p->rollX = right ? 1 : -1;
    p->distance = p->smoked = 0;
    s->d.x = 0;
    setBody(p, BODY_BALL);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Roll_Go(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x2B));
    setBody(p, BODY_ROLL);
    s->coord.y = p->floor - PIXEL(20);
    s->work[2] = 0;
  }
  UpdateEntityAnim(s);
  AppendQuake(1, &s->coord);
  if (s->mode[3] == 1) {
    s->coord.x += s->d.x * p->rollX;
    p->distance += s->d.x;
    s->d.x += 10;
    if (s->d.x > 0x600) s->d.x = 0x600;
    dust(p, PIXEL(20), PIXEL(20));
    if (p->rollX < 0) {
      if (s->coord.x - PIXEL(20) > p->left) {
        spin(p);
        return;
      }
      s->coord.x = p->left + PIXEL(20);
    } else {
      if (s->coord.x + PIXEL(20) < p->left + 0xCFFF) {
        spin(p);
        return;
      }
      s->coord.x = p->left + 0xBBFF;
    }
    s->d.y = p->rolled ? s->d.x : 0;
    p->rollY = -1;
    s->mode[3]++;
    spin(p);
    return;
  }
  s->coord.y += s->d.y * p->rollY;
  p->distance += s->d.y;
  s->d.y += 10;
  if (s->d.y > 0x600) s->d.y = 0x600;
  dust(p, -PIXEL(20), PIXEL(20));
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= PIXEL(64)) {
    spin(p);
    return;
  }
  rollLeaves(p, 3, 5, 32);
  nextStep(s);
}

static void Roll_Away(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) s->work[2] = ++p->rolled < p->rolls ? 128 : 72;
  if (--s->work[2] != 0) return;
  if (p->rolled >= p->rolls) {
    s->mode[2] = 8;
    s->mode[3] = 0;
  } else {
    nextStep(s);
  }
}

static void Roll_Back(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    s->coord.x = p->rollX < 0 ? p->left + 0xBBFF : p->left + PIXEL(20);
    p->distance = p->smoked = 0;
    s->work[2] = 0;
    rollLeaves(p, 3, 5, 32);
  }
  UpdateEntityAnim(s);
  AppendQuake(1, &s->coord);
  s->coord.y += s->d.y;
  p->distance += s->d.y;
  s->d.y += 10;
  if (s->d.y > 0x600) s->d.y = 0x600;
  dust(p, PIXEL(20), -PIXEL(20));
  spin(p);
  if (s->coord.y + PIXEL(20) < p->floor) return;
  s->coord.y = p->floor - PIXEL(20);
  s->mode[2] = 2;
  s->d.x = s->d.y;
  s->mode[3] = 0;
}

static void Roll_Slam(struct Frog* p) {
  struct Entity* s = &p->s;
  u8 n, i;
  s32 x;
  if (entering(s)) {
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
    keepFacing(p, FALSE);
    (s->spr).oam.priority = 2;
    SetMotion(s, FROG(0x2A));
    setBody(p, BODY_BALL);
    s->coord.y = p->floor;
    AppendQuake(8, &s->coord);
    if (inCanopy(p)) {
      for (n = (RANDOM(RNG_0202f388) & 0x7FFF) % 3 + 6; n != 0; n--) {
        x = p->left + PIXEL((RANDOM(RNG_0202f388) & 0x7FFF) % 176 + 32);
        leaf(x, p->floor - PIXEL(128) + PIXEL((RANDOM(RNG_0202f388) & 0x7FFF) % 15));
      }
    }
    for (i = 0; i < 8; i++) createDust(&s->coord, i << 5);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Roll_Uncurl(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x2C));
    setBody(p, BODY_CURL);
  }
  UpdateEntityAnim(s);
  if (animDone(s)) nextStep(s);
}

static void Roll_Rest(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, FROG(0x23));
    setBody(p, BODY_BIG);
    s->work[2] = 24;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static void Roll_Drop(struct Frog* p) {
  struct Entity* s = &p->s;
  s32 lo = p->left + PIXEL(20), hi = p->left + 0xBBFF;
  if (entering(s)) {
    s->angle = 0;
    s->coord.x = (pZero2->s).coord.x;
    if (s->coord.x < lo) {
      s->coord.x = lo;
    } else if (hi < s->coord.x) {
      s->coord.x = hi;
    }
    s->coord.y = p->floor - PIXEL(208);
    s->d.y = 0x240;
    rollLeaves(p, 1, 7, 16);
  }
  gravity(s);
  if (s->coord.y + PIXEL(20) < p->floor) return;
  s->coord.y = p->floor - PIXEL(20);
  s->mode[2] = 5;
  s->mode[3] = 0;
}

static const FrogFunc sRoll[9] = {Roll_Curl, Roll_Ball,   Roll_Go,   Roll_Away, Roll_Back,
                                  Roll_Slam, Roll_Uncurl, Roll_Rest, Roll_Drop};

// --------------------------------------------
// 0x08053948, 0x08055854: tongue at the nearest tree frog. Swallowing it grows the frog

static void Eat_Look(struct Frog* p) {
  struct Entity* s = &p->s;
  s32 reach = p->phase == 0 ? PIXEL(80) : PIXEL(120);
  if (entering(s)) {
    faceZero(p);
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    setBody(p, p->phase == 0 ? BODY_SMALL : BODY_GROWN);
    s->unk_coord.x = s->unk_coord.y = 0;
    p->hungry = TRUE;
    p->ready = FALSE;
    UpdateEntityAnim(s);
    if (p->phase == 0) p->committed = TRUE;
    return;
  }
  UpdateEntityAnim(s);
  p->hungry = FALSE;
  if ((s->unk_coord.x != 0 || s->unk_coord.y != 0) && (u32)(s->unk_coord.x - s->coord.x + reach) <= (u32)(reach << 1)) {
    nextStep(s);
  } else {
    pick(p);
  }
}

static void Eat_Open(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) SetMotion(s, p->phase == 0 ? FROG(9) : FROG(0x1A));
  UpdateEntityAnim(s);
  if (!animDone(s)) return;
  PlaySound(SE_Z2_FROG_MOUTH);
  nextStep(s);
}

static void Eat_Shoot(struct Frog* p) {
  struct Entity* s = &p->s;
  struct Entity* t;
  Coords32 at;
  if (entering(s)) {
    if (p->phase == 0) {
      at.x = s->coord.x + (facingRight(s) ? PIXEL(14) : -PIXEL(14));
      at.y = s->coord.y - PIXEL(16);
    } else {
      at.x = s->coord.x + (facingRight(s) ? PIXEL(18) : -PIXEL(18));
      at.y = s->coord.y - PIXEL(20);
      p->ready = FALSE;
    }
    p->arms[0] = createTongue(s, &at, 3, p->phase);
  }
  UpdateEntityAnim(s);
  t = p->arms[0];
  if (t != NULL && t->mode[0] <= ENTITY_UPDATE) return;
  if (t != NULL && t->unk_2c != NULL) {
    setBody(p, p->phase == 0 ? BODY_FULL : BODY_FULL_GROWN);
    nextStep(s);
  } else {
    s->mode[2] = 7;
    s->mode[3] = 0;
  }
}

static void Eat_Chew(struct Frog* p) { holdStep(p, p->phase == 0 ? FROG(10) : FROG(0x1B), 8); }

static void Eat_Swallow(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    s->work[2] = 2;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] != 0) return;
  if (p->phase == 0) {
    p->last = FROG_EAT;
    setMode(s, FROG_GROW);
  } else {
    p->last = GROWN_EAT;
    setMode(s, GROW_AGAIN);
  }
}

static void Eat_Rest(struct Frog* p) {
  struct Entity* s = &p->s;
  if (entering(s)) {
    SetMotion(s, p->phase == 0 ? FROG(0) : FROG(0x14));
    if (p->phase == 0) {
      setBody(p, BODY_SMALL);
      p->committed = FALSE;
    }
    s->work[2] = 24;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) pick(p);
}

static const FrogFunc sEat[10] = {Eat_Look,  Eat_Open, Guard_Open, Eat_Shoot, Eat_Chew,
                                  Tongue_Close, Eat_Swallow, Eat_Chew, Tongue_Close, Eat_Rest};

// --------------------------------------------

static void Frog_Intro(struct Frog* p) { sIntro[(p->s).mode[2]](p); }
static void Frog_Wait(struct Frog* p) { sWait[(p->s).mode[2]](p); }
static void Frog_Hop(struct Frog* p) { sHop[(p->s).mode[2]](p); }
static void Frog_Leap(struct Frog* p) { sLeap[(p->s).mode[2]](p); }
static void Frog_Canopy(struct Frog* p) { sCanopy[(p->s).mode[2]](p); }
static void Frog_Guard(struct Frog* p) { sGuard[(p->s).mode[2]](p); }
static void Frog_Summon(struct Frog* p) { sSummon[(p->s).mode[2]](p); }
static void Frog_Tongue(struct Frog* p) { sTongue[(p->s).mode[2]](p); }
static void Frog_Hit(struct Frog* p) { sHit[(p->s).mode[2]](p); }
static void Frog_Grow(struct Frog* p) { sGrow[(p->s).mode[2]](p); }
static void Grown_Hop(struct Frog* p) { sGrownHop[(p->s).mode[2]](p); }
static void Grown_Leap(struct Frog* p) { sGrownLeap[(p->s).mode[2]](p); }
static void Grown_Spit(struct Frog* p) { sSpit[(p->s).mode[2]](p); }
static void Grown_Summon(struct Frog* p) { sGrownSummon[(p->s).mode[2]](p); }
static void Frog_Shrink(struct Frog* p) { sShrink[(p->s).mode[2]](p); }
static void Frog_Gloat(struct Frog* p) { sGloat[(p->s).mode[2]](p); }
static void Big_Bubbles(struct Frog* p) { sBubbles[(p->s).mode[2]](p); }
static void Big_Roll(struct Frog* p) { sRoll[(p->s).mode[2]](p); }
static void Frog_Eat(struct Frog* p) { sEat[(p->s).mode[2]](p); }

// 0x0833c150
static const FrogFunc sStates[28] = {
    [FROG_INTRO] = Frog_Intro,    [FROG_WAIT] = Frog_Wait,     [FROG_IDLE] = Frog_Idle,       [FROG_HOP] = Frog_Hop,
    [FROG_LEAP] = Frog_Leap,      [FROG_CANOPY] = Frog_Canopy, [FROG_GUARD] = Frog_Guard,     [FROG_SUMMON] = Frog_Summon,
    [FROG_TONGUE] = Frog_Tongue,  [FROG_HIT] = Frog_Hit,       [FROG_GROW] = Frog_Grow,       [GROWN_IDLE] = Grown_Idle,
    [GROWN_HOP] = Grown_Hop,      [GROWN_LEAP] = Grown_Leap,   [GROWN_SPIT] = Grown_Spit,     [GROWN_GUARD] = Frog_Guard,
    [GROWN_SUMMON] = Grown_Summon, [GROWN_TONGUE] = Frog_Tongue, [GROWN_HIT] = Frog_Shrink,   [GROWN_GLOAT] = Frog_Gloat,
    [GROW_AGAIN] = Frog_Grow,     [BIG_IDLE] = Big_Idle,       [BIG_BUBBLES] = Big_Bubbles,   [BIG_ROLL] = Big_Roll,
    [BIG_HIT] = Frog_Shrink,      [BIG_GLOAT] = Frog_Gloat,    [FROG_EAT] = Frog_Eat,         [GROWN_EAT] = Frog_Eat,
};

// --------------------------------------------
/*
  Zero 2's enemy 34, tree frog
  work0:
    0: the stage's
    1: the frog's
    2: the frog's, tougher
  work1, the stage's: 0 on floor, 1 hidden in canopy
*/

struct TreeFrog {
  OBJECT_HDR;
  struct Entity* holder;  // 0xB4, tongue carrying it in mode 4
  u8 resume;              // 0xB8, mode before element hit
  u8 _b9[11];
};
static_assert(sizeof(struct TreeFrog) == sizeof(struct Enemy));

enum { TF_HIDDEN, TF_DROP, TF_HOP, TF_FALL, TF_CARRIED, TF_TURN, TF_ELEMENT };

static void TreeFrog_Init(struct TreeFrog* p);
static void TreeFrog_Update(struct TreeFrog* p);
static void TreeFrog_Die(struct TreeFrog* p);

// clang-format off
const EnemyRoutine gApZ2TreeFrogRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)TreeFrog_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)TreeFrog_Update,
    [ENTITY_DIE] =       (EnemyFunc)TreeFrog_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x0833ffc4, 0x0833fff4
static const struct Collision sTreeFrog[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, -0x200, 0xc00, 0xc00}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x400, 0x1000, 0xe00}},
};
static const struct Collision sTreeFrogHarmless = {
    DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, -0x400, 0x1000, 0xe00},
};
// clang-format on

// 0x0833ffbc
static const Coords32 sElementCoord = {0, -PIXEL(8)};

// 0x08079c14
static struct Entity* createTreeFrog(struct Entity* boss, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_TREE_FROG);
    p->unk_28 = boss;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x0807a694
static bool8 inLeaves(struct Entity* s) {
  return ApZ2Jungle2Canopy(s->coord.x - PIXEL(32), s->coord.y + PIXEL(32)) != 0;
}

static void rustle(struct Entity* s) {
  Coords32 at;
  u8 i, n;
  if (!inLeaves(s)) return;
  n = (RANDOM(RNG_0202f388) & 1) + 2;
  for (i = 0; i < n; i++) {
    at.x = s->coord.x;
    at.y = s->coord.y + PIXEL(24);
    createLeaf(&at);
  }
}

static void tint(struct TreeFrog* p) {
  if ((p->s).work[0] == 2) ForceEntityPalette(&p->s, 7);
}

// 0x08079c7c
static void TreeFrog_Init(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  struct Entity* toward = s->work[0] == 2 ? s->unk_28 : &pZero2->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  s->unk_2c = NULL;
  SET_XFLIP(p, s->coord.x < toward->coord.x);
  INIT_BODY(p, sTreeFrog, s->work[0] == 2 ? 18 : 2, NULL);
  p->holder = NULL;
  if (s->work[0] == 0 && s->work[1] == 0) {
    s->mode[1] = TF_HOP;
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    SetSpriteAnimation(p, TREE_FROG(0));
  } else {
    s->mode[1] = TF_HIDDEN;
    rustle(s);
    SetSpriteAnimation(p, TREE_FROG(1));
    tint(p);
  }
  UpdateSpriteAnimation(p);
  TreeFrog_Update(p);
}

static void die(struct TreeFrog* p) {
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  TreeFrog_Die(p);
}

// 0x0807a60c: frog's pick, nearest by x
static void offerSelf(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  struct Frog* boss = (struct Frog*)s->unk_28;
  struct Entity* b = &boss->s;
  s32 x = (s->flags & X_FLIP) ? s->coord.x : s->coord.x - PIXEL(8);
  s32 y = s->coord.y + PIXEL(5);
  u16 best;
  if (!boss->hungry || s->mode[1] <= TF_DROP) return;
  if (b->unk_coord.x == 0 && b->unk_coord.y == 0) {
    b->unk_coord.x = x;
    b->unk_coord.y = y;
    return;
  }
  best = b->unk_coord.x - b->coord.x < 0 ? b->coord.x - b->unk_coord.x : b->unk_coord.x - b->coord.x;
  if ((u32)(b->coord.x - s->coord.x + best) > (u32)(best << 1)) return;
  b->unk_coord.x = x;
  b->unk_coord.y = y;
}

static void TreeFrog_Hidden(struct TreeFrog* p);
static void TreeFrog_Drop(struct TreeFrog* p);
static void TreeFrog_Hop(struct TreeFrog* p);
static void TreeFrog_Fall(struct TreeFrog* p);
static void TreeFrog_Carried(struct TreeFrog* p);
static void TreeFrog_Turn(struct TreeFrog* p);
static void TreeFrog_Element(struct TreeFrog* p);

// 0x0833ffa0
static void (*const sTreeFrogStates[7])(struct TreeFrog*) = {
    TreeFrog_Hidden, TreeFrog_Drop, TreeFrog_Hop, TreeFrog_Fall, TreeFrog_Carried, TreeFrog_Turn, TreeFrog_Element,
};

// 0x0807a074, 0x0807a128
static void TreeFrog_Update(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  struct Frog* boss = (struct Frog*)s->unk_28;
  if (s->work[0] == 0) {
    if ((p->body).status & BODY_STATUS_DEAD) {
      die(p);
      return;
    }
    if (IsFrozen(p)) return;
  } else {
    if ((p->body).status & BODY_STATUS_DEAD || boss == NULL || (boss->s).mode[0] > ENTITY_UPDATE) {
      if (boss != NULL) boss->frogs--;
      die(p);
      return;
    }
    if ((u32)((boss->s).coord.x - s->coord.x + boss->reach) <= (u32)(boss->reach << 1) &&
        (u32)((boss->s).coord.y - s->coord.y + PIXEL(64)) <= PIXEL(128)) {
      boss->frogNear = TRUE;
    }
    offerSelf(p);
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
    if (s->unk_2c != NULL) {
      p->resume = s->mode[1];
      s->mode[1] = TF_ELEMENT;
      s->mode[2] = 0;
    }
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  sTreeFrogStates[s->mode[1]](p);
}

// 0x0807a228: rustles in canopy, then drops
static void TreeFrog_Hidden(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    if (inLeaves(s)) PlaySound(SE_Z2_LEAVES);
    s->flags &= ~DISPLAY;
    SetSpriteAnimation(p, TREE_FROG(1));
    tint(p);
    s->work[2] = 80;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2]--;
  if (inLeaves(s) && s->work[2] > 71) {
    if ((s->work[2] & 3) != 0) return;
    if ((s->work[2] & 15) == 0 && (RANDOM(RNG_0202f388) & 3) != 0) return;
    at = s->coord;
    createLeaf(&at);
    return;
  }
  if (s->work[2] != 0) return;
  s->flags |= DISPLAY;
  s->mode[1] = TF_DROP;
  s->mode[2] = 0;
}

static bool8 fall(struct Entity* s) {
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  return TRUE;
}

// 0x0807a2fc
static void TreeFrog_Drop(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TREE_FROG(1));
    tint(p);
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!fall(s)) return;
  s->mode[1] = TF_HOP;
  s->mode[2] = 0;
}

// 0x0807a368: hops along floor, turns at walls, the frog's toward Zero
static void TreeFrog_Hop(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TREE_FROG(0));
    tint(p);
    s->d.x = (s->flags & X_FLIP) ? 48 : -48;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx <= 1) return;
  s->coord.x += s->d.x;
  if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(8)) != 0) {
    s->mode[1] = TF_TURN;
    s->mode[2] = 0;
  } else if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(8)) == 0) {
    s->mode[1] = TF_FALL;
    s->mode[2] = 0;
  } else if (s->work[0] == 1 && ((s->flags & X_FLIP) != 0) != (s->coord.x < (pZero2->s).coord.x)) {
    s->mode[1] = TF_TURN;
    s->mode[2] = 0;
  } else {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  }
}

// 0x0807a434
static void TreeFrog_Fall(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = 0;
    s->mode[2]++;
  }
  if (!fall(s)) return;
  s->mode[1] = TF_HOP;
  s->mode[2] = 0;
}

// 0x0807a484: in the frog's mouth until it spits or is hit
static void TreeFrog_Carried(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  struct Tongue* h = (struct Tongue*)p->holder;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TREE_FROG(1));
    tint(p);
    s->mode[2]++;
  }
  if (boss->mode[1] == 9 || boss->mode[1] == 18) {
    s->mode[1] = TF_DROP;
    s->mode[2] = 0;
    p->holder = NULL;
    return;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = (h->s).coord.x + h->home.x;
  s->coord.y = (h->s).coord.y + h->home.y;
}

// 0x0807a4f4
static void TreeFrog_Turn(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TREE_FROG(0));
    tint(p);
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] != 0) return;
  s->mode[1] = TF_HOP;
  s->mode[2] = 0;
  SET_XFLIP(p, !(s->flags & X_FLIP));
}

// 0x0807a570: held on frame, falling, while burning or frozen
static void TreeFrog_Element(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sTreeFrogHarmless);
    s->mode[2]++;
  }
  if (s->mode[2] == 1) {
    if (FUN_080098a4(s->coord.x, s->coord.y + 1) == 0) {
      s->d.y = 0;
      s->mode[2]++;
    }
  } else if (fall(s)) {
    s->mode[2] = 1;
  }
  if (s->unk_2c != NULL) return;
  SetDDP(&p->body, sTreeFrog);
  s->mode[1] = p->resume;
  s->mode[2] = 0;
}

// 0x08079fa0
static void TreeFrog_Die(struct TreeFrog* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  PlaySound(SE_ZAKO_EXPLODE);
  c.x = s->coord.x + (((RANDOM(RNG_0202f388) & 7) - 3) << 8);
  c.y = s->coord.y + ((RANDOM(RNG_0202f388) & 7) << 8) - PIXEL(7);
  CreateSmoke(2, &c);
  TryDropItem(0, (struct Coord*)&s->coord);
  EXIT_BODY(p);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  ApImportTreeFrogKilled();
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's VFX 35 work0 1, a leaf off a tree frog's canopy, swaying down
*/

struct Leaf {
  struct Entity s;
  s32 homeX;  // 0x74
  u8 _78[6];
  u16 time;   // 0x7E
  u8 _80[4];
};
static_assert(sizeof(struct Leaf) == sizeof(struct VFX));

static void Leaf_Init(struct VFX* p);
static void Leaf_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2LeafRoutine = {
    [ENTITY_INIT] =      Leaf_Init,
    [ENTITY_UPDATE] =    Leaf_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b61b4
static void createLeaf(const Coords32* at) {
  struct Entity* p;
  if (gVFXHeaderPtr->remaining == 1) return;
  p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_LEAF);
  p->coord = *at;
}

// 0x080b6224
static void Leaf_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  struct Leaf* l = (struct Leaf*)p;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SET_XFLIP(p, RANDOM(RNG_0202f388) & 1);
  SetSpriteAnimation(p, TREE_FROG(3));
  s->work[2] = RANDOM(RNG_0202f388);
  l->homeX = s->coord.x;
  l->time = 180;
  s->flags |= DISPLAY | FLIPABLE;
  Leaf_Update(p);
}

// 0x080b6444: blinks out
static void Leaf_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  struct Leaf* l = (struct Leaf*)p;
  if (--l->time == 0) {
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (l->time < 24) {
    s->flags = (l->time & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  } else if (l->time < 64) {
    s->flags = (l->time & 3) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  }
  UpdateSpriteAnimation(p);
  s->work[2] += 4;
  s->coord.x = l->homeX + COS(s->work[2]) * 4;
  s->coord.y += SIN(s->work[2] & 127) * 288 / 256;
}


// --------------------------------------------
/*
  Zero 2's enemy 32, the frog's arms, tongues and cut half
  work0:
    0 arm from the canopy, work1 its side
    1 tongue at Zero, work1 the frog's phase
    2 upper half when cut
    3 tongue at a tree frog, work1 the frog's phase
    4 arm's middle link
    6, 7 tongue's segments, small and grown
    8, 9 eating tongue's segments
  Segments and links sit work1 sevenths of the way out
*/

enum { ARM, TONGUE, HALF, EAT, ARM_LINK, TONGUE_SEG = 6, EAT_SEG = 8 };

static void Tongue_Init(struct Tongue* p);
static void Tongue_Update(struct Tongue* p);

// clang-format off
const EnemyRoutine gApZ2FrogTongueRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Tongue_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Tongue_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEnemy,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x0833fe00
static const struct Collision sTongueBody[13] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0x200, 0x200, 0xa00, 0xa00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 33, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 33, 0, 0x00000001, {0x0, 0x0, 0xc00, 0x800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 0, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 35, 0, 0x00000001, {0x0, 0x0, 0x4000, 0x4000}},
    {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x01, 0x00, 0, 35, 0, 0x00000001, {0x0, 0x0, 0x4000, 0x4000}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xc00, 0x800}},
    {DDP, FACTION_NEUTRAL, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_NEUTRAL, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xc00, 0x800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

#define BODY_ARM 0
#define BODY_LINK 1
#define BODY_TONGUE 2
#define BODY_SEG 4
#define BODY_GULP 5
#define BODY_HOLD 6
#define BODY_BITE 7
#define BODY_TONGUE_BACK 8
#define BODY_EAT 10
#define BODY_EAT_SEG 12

// 0x08077fb0, 0x08078018
static struct Entity* createTongue(struct Entity* parent, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FROG_TONGUE);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = parent;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x08079654: at Zero's middle, 16..112, down either side
static u8 aimDown(const Coords32* from) {
  struct Zero* z = pZero2;
  u8 a = CalcAngle((z->s).coord.x - from->x, (z->s).coord.y - gZeroRanges[z->posture].h / 2 - from->y);
  if ((u8)(a - 16) > 176) return 16;
  return a > 112 ? 112 : a;
}

// 0x080796b0: reaches out at Zero, slowing
static void aimArm(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Entity* frog = s->unk_28;
  s32 zx = (pZero2->s).coord.x, ax, ay;
  u8 a = aimDown(&frog->coord);
  if (a == 64) a = 65;
  s->d.x = COS(a) * 2;
  s->d.y = SIN(a) * 2;
  ax = COS(a) * 80;
  ay = SIN(a) * 80;
  s->unk_coord.x = (ax < 0 ? ax + 255 : ax) >> 8;
  s->unk_coord.y = (ay < 0 ? ay + 255 : ay) >> 8;
  if (s->work[1] == 0 ? frog->coord.x < zx : zx < frog->coord.x) {
    s->d.x = -s->d.x;
    s->unk_coord.x = -s->unk_coord.x;
  }
}

static void sevenths(struct Entity* s, const struct Entity* to, bool8 alsoY) {
  struct Tongue* p = (struct Tongue*)s;
  s->coord.x = p->home.x + (to->coord.x - p->home.x) / 7 * s->work[1];
  if (alsoY) s->coord.y = p->home.y + (to->coord.y - p->home.y) / 7 * s->work[1];
}

// 0x08079748: grabs a tree frog it touches
s32 CalcAngleBetweenPoints(s32 x1, s32 y1, s32 x2, s32 y2);

static void onLick(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Tongue* p = (struct Tongue*)body->parent;
  struct Entity* s = &p->s;
  struct Entity* frog = (body->enemy)->parent;
  if (!(body->hitboxFlags & 4) || frog->kind != ENTITY_ENEMY || frog->id != ENEMY_Z2_TREE_FROG) return;
  if (s->unk_2c != NULL) return;
  s->unk_2c = frog;
  s->mode[1] = 1;
  s->work[3] = 16;
  p->home.x = frog->coord.x - s->coord.x;
  p->home.y = frog->coord.y - s->coord.y;
  frog->mode[1] = 4;
  frog->mode[2] = 0;
  ((struct TreeFrog*)frog)->holder = s;
}

// 0x080780d8, 0x080782bc, 0x08078620, 0x080786f0, 0x08078204, 0x08078468, 0x08078544, 0x08078938, 0x080789fc
static void Tongue_Init(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  struct Entity* frog = parent;
  Coords32 at;
  u8 kind = s->work[0], n, a;
  s32 dx, dy;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  if (kind == HALF && parent == NULL) {
    enemyGone(s);
    return;
  }
  if (kind == ARM_LINK || kind >= TONGUE_SEG) frog = parent->unk_28;
  if (kind == TONGUE || kind == TONGUE_SEG || kind == TONGUE_SEG + 1) {
    InitScalerotMotion1(s);
    (s->spr).mag.x = (s->spr).mag.y = 256;
  } else {
    InitNonAffineMotion(s);
  }
  if (kind == TONGUE) s->renderPrio = 8;
  if (kind == EAT) s->renderPrio = 22;
  if (kind >= TONGUE_SEG) s->renderPrio = kind >= EAT_SEG ? 24 : 12;
  if (kind == ARM || kind == ARM_LINK) (s->spr).oam.priority = 3;
  ResetDynamicMotion(s);
  SET_XFLIP(p, kind == ARM ? s->work[1] : kind == ARM_LINK ? FALSE : facingRight(parent));
  s->flags |= DISPLAY | FLIPABLE;
  s->invincibleID = frog->uniqueID;
  p->home = s->coord;
  switch (kind) {
    case ARM:
      SetMotion(s, FROG(8));
      aimArm(p);
      p->out = 0;
      INIT_BODY(p, &sTongueBody[BODY_ARM], 4, NULL);
      at.x = s->coord.x;
      at.y = frog->coord.y - PIXEL(4);
      createLink(s, &at, 0, 6);
      createLink(s, &at, 0, 5);
      createTongue(s, &at, ARM_LINK, 4);
      createLink(s, &at, 0, 3);
      createLink(s, &at, 0, 2);
      createLink(s, &at, 0, 1);
      PlaySound(SE_Z2_FROG_LAND);
      break;
    case TONGUE:
      s->work[2] = 0;
      p->out = 0;
      p->bites = 8;
      p->released = FALSE;
      p->caught = 0;
      SetMotion(s, s->work[1] == 0 ? FROG(0x0C) : FROG(0x1D));
      s->d.x = facingRight(s) ? PIXEL(8) : -PIXEL(8);
      p->grip = s->work[1] == 0 ? 32 : 48;
      INIT_BODY(p, &sTongueBody[BODY_TONGUE + s->work[1]], 4, NULL);
      for (n = 6; n != 0; n--) {
        struct Entity* seg = createTongue(s, &s->coord, TONGUE_SEG + s->work[1], n);
        if (n == 6) s->unk_2c = seg;
      }
      break;
    case HALF:
      SetMotion(s, FROG(0x13));
      s->d.x = 112;
      break;
    case EAT:
      s->unk_2c = NULL;
      s->work[2] = 0;
      a = CalcAngleBetweenPoints(s->coord.x, s->coord.y, parent->unk_coord.x, parent->unk_coord.y);
      SetMotion(s, s->work[1] == 0 ? FROG(0x0C) : FROG(0x1D));
      s->d.x = COS(a) * 8;
      s->d.y = SIN(a) * 8;
      dx = s->d.x == 0 ? 0 : (s->coord.x - parent->unk_coord.x) / s->d.x;
      dy = s->d.y == 0 ? 0 : (s->coord.y - parent->unk_coord.y) / s->d.y;
      dx = (u8)((dx < 0 ? -dx : dx) + 1 + s->work[1]);
      dy = (u8)((dy < 0 ? -dy : dy) + 1 + s->work[1]);
      s->work[3] = dx > dy ? dx : dy;
      INIT_BODY(p, &sTongueBody[BODY_EAT + s->work[1]], 4, onLick);
      for (n = 6; n != 0; n--) createTongue(s, &s->coord, EAT_SEG + s->work[1], n);
      SET_XFLIP(p, s->d.x >= 0);
      break;
    case ARM_LINK:
      SetMotion(s, FROG(7));
      INIT_BODY(p, &sTongueBody[BODY_LINK], 4, NULL);
      break;
    default:
      SetMotion(s, (kind & 1) ? FROG(0x1E) : FROG(0x0D));
      if (kind < EAT_SEG) p->bites = 8;
      INIT_BODY(p, &sTongueBody[kind < EAT_SEG ? BODY_SEG : BODY_EAT_SEG], 4, NULL);
      break;
  }
  Tongue_Update(p);
}

// Zero held where the tongue caught him, mashing to get loose
static void holdZero(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  u8 n;
  if (z == NULL) {
    p->released = TRUE;
    return;
  }
  (z->s).coord.x = s->coord.x + p->home.x;
  (z->s).coord.y = s->coord.y + p->home.y;
  n = CountButtonMashing(z);
  p->grip = p->grip > n ? p->grip - n : 0;
}

// 0x08078d3c
static void Tongue_Out(struct Tongue* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  p->out++;
  UpdateEntityAnim(s);
  if ((p->body).status & BODY_STATUS_B2) {
    if (pZero2 == NULL) {
      s->mode[1] = 4;
      return;
    }
    SetDDP(&p->body, &sTongueBody[BODY_HOLD]);
    p->home.x = (pZero2->s).coord.x - s->coord.x;
    p->home.y = (pZero2->s).coord.y - s->coord.y;
    p->caught = 1;
    s->mode[1] = 2;
    s->mode[2] = 0;
    return;
  }
  s->coord.x += s->d.x;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->mode[1]++;
  SetDDP(&p->body, &sTongueBody[BODY_TONGUE_BACK + s->work[1]]);
}

// 0x08078de8
static void Tongue_In(struct Tongue* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->coord.x -= s->d.x;
  if (--p->out == 0) enemyGone(s);
}

// 0x08078e4c: swells, a gulp running down the segments
static void Tongue_Chew(struct Tongue* p) {
  struct Entity* s = &p->s;
  s16 mag;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_FROG_CHEW);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  holdZero(p);
  s->work[2] += 2;
  mag = SIN(s->work[2]) + 256;
  if (mag <= 255) mag = 256;
  (s->spr).mag.x = (s->spr).mag.y = mag;
  if (mag != 256) return;
  SetDDP(&p->body, &sTongueBody[BODY_BITE]);
  p->bites--;
  s->mode[1]++;
  s->mode[2] = 0;
}

// 0x08078f20: the gulp reaching the tip heals the frog a point, then another bite while Zero is held
static void Tongue_Bite(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Tongue* tip = (struct Tongue*)s->unk_2c;
  struct Boss* frog = (struct Boss*)s->unk_28;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_FROG_CHEW);
    SetDDP(&p->body, &sTongueBody[BODY_HOLD]);
    if (!((p->body).status & BODY_STATUS_B2) || (gStageRun.vm.active & VM_ACTIVE)) p->released = TRUE;
    s->mode[2]++;
  }
  holdZero(p);
  if (p->bites != tip->bites) return;
  if ((frog->body).hp < 64) (frog->body).hp++;
  if (p->bites != 0 && !p->released && p->grip != 0) {
    s->mode[1] = 2;
    s->mode[2] = 0;
  } else {
    s->mode[1]++;
  }
  s->work[2] = 0;
}

// 0x0807901c
static void Tongue_Let(struct Tongue* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (++s->work[2] == 16) s->mode[1] = 1;
}

static void (*const sTongueStates[5])(struct Tongue*) = {Tongue_Out, Tongue_In, Tongue_Chew, Tongue_Bite, Tongue_Let};

// 0x08078ac0: reaches down at Zero twice, back up into the canopy
static void updateArm(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Entity* frog = s->unk_28;
  if (frog->mode[0] > ENTITY_UPDATE || frog->mode[1] == FROG_HIT) {
    enemyGone(s);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
    case 3:
      p->out++;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.x += s->unk_coord.x;
      s->d.y += s->unk_coord.y;
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) s->mode[1]++;
      break;
    case 1:
    case 4:
      p->out--;
      s->coord.x -= s->d.x;
      s->coord.y -= s->d.y;
      s->d.x -= s->unk_coord.x;
      s->d.y -= s->unk_coord.y;
      if (p->out != 0) break;
      if (s->mode[1] == 1) {
        s->work[2] = 8;
      } else {
        s->coord.x = frog->coord.x + PIXEL(16) * s->work[1] - PIXEL(8);
        s->coord.y = frog->coord.y - PIXEL(3);
      }
      s->mode[1]++;
      break;
    case 2:
      if (--s->work[2] != 0) break;
      PlaySound(SE_Z2_FROG_LAND);
      aimArm(p);
      s->mode[1]++;
      break;
  }
}

// 0x080792d4: out until it hits something or runs its course, back with what it caught
static void updateEat(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Frog* frog = (struct Frog*)s->unk_28;
  struct Entity* caught = s->unk_2c;
  if ((frog->s).mode[0] > ENTITY_UPDATE || (frog->s).mode[1] == FROG_HIT || (frog->s).mode[1] == GROWN_HIT) {
    enemyGone(s);
    return;
  }
  if (caught != NULL && caught->mode[0] > ENTITY_UPDATE) s->unk_2c = caught = NULL;
  UpdateEntityAnim(s);
  if (s->mode[1] == 0) {
    s->work[2]++;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y - PIXEL(8)) != 0 || --s->work[3] == 0) s->mode[1] += 2;
    return;
  }
  if (s->mode[1] == 1) {
    if (--s->work[3] == 0) s->mode[1]++;
    return;
  }
  s->work[2]--;
  s->coord.x -= s->d.x;
  s->coord.y -= s->d.y;
  if (s->work[2] != 0) return;
  if (caught != NULL) {
    frog->ateTough = caught->work[0] == 2;
    createSpit(caught, &s->coord, (frog->ateTough ? 5 : 3) + s->work[1], !facingRight(&frog->s));
    enemyGone(caught);
    frog->frogs--;
  }
  enemyGone(s);
}

// 0x0807903c, 0x0807916c: a gulp passes each in turn
static void updateSegment(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Tongue* t = (struct Tongue*)s->unk_28;
  s32 base;
  s16 mag;
  if ((t->s).mode[0] > ENTITY_UPDATE) {
    enemyGone(s);
    return;
  }
  UpdateEntityAnim(s);
  base = (t->s).coord.x - (facingRight(s) ? 1 : -1) * (s->work[0] & 1 ? 0x600 : 0x400);
  s->coord.x = base + (p->home.x - base) / 7 * s->work[1];
  switch (s->mode[1]) {
    case 0:
      if (p->bites <= t->bites) break;
      SetDDP(&p->body, &sTongueBody[BODY_GULP]);
      s->work[2] = s->work[1] * 2 + s->work[1] * s->work[1] / 4;
      s->mode[1]++;
      break;
    case 1:
      if (--s->work[2] == 0) s->mode[1]++;
      break;
    case 2:
      s->work[2] += 4;
      mag = SIN(s->work[2]) * 7 / 4 + 256;
      if (mag <= 255) mag = 256;
      (s->spr).mag.x = (s->spr).mag.y = mag;
      if (mag != 256) break;
      s->mode[1] = --p->bites == 0 ? 3 : 0;
      break;
  }
}

// 0x08079450, 0x080794e4
static void updateEatSegment(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Entity* t = s->unk_28;
  s32 baseX, baseY;
  if (t->mode[0] > ENTITY_UPDATE) {
    enemyGone(s);
    return;
  }
  UpdateEntityAnim(s);
  baseX = t->coord.x - (facingRight(s) ? 1 : -1) * (s->work[0] & 1 ? 0x600 : 0x400);
  baseY = t->coord.y;
  s->coord.x = baseX + (p->home.x - baseX) / 7 * s->work[1];
  s->coord.y = baseY + (p->home.y - baseY) / 7 * s->work[1];
}

static void Tongue_Update(struct Tongue* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  switch (s->work[0]) {
    case ARM:
      updateArm(p);
      break;
    case TONGUE:
      if (parent->mode[0] > ENTITY_UPDATE || parent->mode[1] == FROG_HIT || parent->mode[1] == GROWN_HIT) {
        enemyGone(s);
        return;
      }
      sTongueStates[s->mode[1]](p);
      break;
    case HALF:
      UpdateEntityAnim(s);
      s->coord.x += facingRight(s) ? -s->d.x : s->d.x;
      s->d.x -= 3;
      if (s->d.x < 0) s->d.x = 0;
      break;
    case EAT:
      updateEat(p);
      break;
    case ARM_LINK:
      if (parent->mode[0] > ENTITY_UPDATE) {
        enemyGone(s);
        return;
      }
      UpdateEntityAnim(s);
      sevenths(s, parent, TRUE);
      break;
    case TONGUE_SEG:
    case TONGUE_SEG + 1:
      updateSegment(p);
      break;
    case EAT_SEG:
    case EAT_SEG + 1:
      updateEatSegment(p);
      break;
  }
}

// --------------------------------------------
/*
  Zero 2's projectile 31
  work0:
    0, 1 glob, behind and in front of the frog, work1 its sway
    2 bubble that sticks to Zero and slows him
    3, 4 tree frog going down the small and grown frog's throat, work1 which way
    5, 6 the same, a tough one
*/

struct Spit {
  OBJECT_HDR;
  s32 homeX;  // 0xB4
  u16 swing;  // 0xB8
  u16 turn;   // 0xBA
  u16 spin;   // 0xBC
  u16 time;   // 0xBE
  s8 dir;     // 0xC0
  u8 _c1[3];
};
static_assert(sizeof(struct Spit) == sizeof(struct Projectile));

struct Bubble {
  OBJECT_HDR;
  Coords32 stuck;    // 0xB4, from Zero
  u16 slowed;        // 0xBC
  u16 time;          // 0xBE
  bool8 zeroRight;   // 0xC0
  u8 _c1[3];
};
static_assert(sizeof(struct Bubble) == sizeof(struct Projectile));

static void Spit_Init(struct Spit* p);
static void Spit_Update(struct Spit* p);
static void Spit_Die(struct Spit* p);

// clang-format off
const ProjectileRoutine gApZ2FrogSpitRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Spit_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Spit_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Spit_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083446c8
static const struct Collision sSpitBody[6] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x600, 0x600}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x600, 0x600}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

// 0x080a20a4
static struct Entity* createSpit(struct Entity* parent, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FROG_SPIT);
    p->unk_28 = parent;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

static bool8 offScreen(struct Entity* s) { return Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64); }

// 0x080a2158
static void Spit_Init(struct Spit* p) {
  struct Entity* s = &p->s;
  struct Bubble* b = (struct Bubble*)p;
  bool8 right = facingRight(s->unk_28);
  s32 v;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->texture = TEXTURE_AP_SHEET;
  switch (s->work[0]) {
    case 0:
    case 1:
      InitRotatableMotion(s);
      s->angle = 0;
      SET_XFLIP(p, right);
      (s->spr).oam.priority = s->work[0] == 0 ? 2 : 3;
      SetMotion(s, TREE_FROG(2));
      INIT_BODY(p, &sSpitBody[0], 2, NULL);
      p->homeX = s->coord.x;
      p->swing = right ? 0 : 0x8000;
      p->turn = 0x200;
      p->spin = 0x8000;
      p->time = 64;
      v = SIN(s->work[1]) * 52;
      s->d.y = (v < 0 ? v + 63 : v) >> 6;
      p->dir = right ? 1 : -1;
      break;
    case 2:
      InitScalerotMotion2(s);
      (s->spr).mag.x = (s->spr).mag.y = 64;
      SET_XFLIP(p, right);
      SetMotion(s, BUBBLE(0));
      INIT_BODY(p, &sSpitBody[2], 2, NULL);
      s->d.x = (right ? 1 : -1) * (RANDOM(RNG_0202f388) & 0x3FF);
      s->d.y = 0x200;
      s->work[2] = 0;
      b->time = 360;
      b->slowed = 0;
      break;
    default:
      InitScalerotMotion2(s);
      (s->spr).mag.x = (s->spr).mag.y = 256;
      SET_XFLIP(p, right);
      SetMotion(s, TREE_FROG(1));
      if (s->work[0] >= 5) ForceEntityPalette(s, 7);
      s->d.x = (s->work[0] & 1) ? s->work[1] * 320 - 160 : s->work[1] * 512 - 256;
      s->work[2] = 0;
      break;
  }
  s->flags |= DISPLAY | FLIPABLE;
  Spit_Update(p);
}

// 0x080a2664: swings out in a half circle
static void Glob_Swing(struct Spit* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->spin -= p->turn;
  s->angle = p->spin >> 8;
  p->swing -= p->turn;
  s->coord.x = p->homeX + SIN(p->swing >> 8) * 52;
  s->coord.y += s->d.y;
  if (--p->time != 0) return;
  s->d.x = 0x300;
  s->mode[1]++;
  s->mode[2] = 0;
}

// 0x080a26dc: speeds ahead, drifting to Zero's height
static void Glob_Fly(struct Spit* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  bool8 right = facingRight(s);
  s32 zy;
  if (s->mode[2] == 0) {
    InitNonAffineMotion(s);
    SET_XFLIP(p, right);
    SetMotion(s, TREE_FROG(2));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (offScreen(s)) {
    projectileGone(s);
    return;
  }
  s->coord.x += s->d.x * p->dir;
  s->d.x += 24;
  if (s->d.x > 0x600) s->d.x = 0x600;
  if (z == NULL) return;
  zy = (z->s).coord.y - gZeroRanges[z->posture].h / 2;
  if (zy < s->coord.y) {
    s->coord.y -= 96;
  } else if (zy > s->coord.y) {
    s->coord.y += 96;
  }
}

static void rise(struct Entity* s) {
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y -= 32;
  if (s->d.y < -0x1C0) s->d.y = -0x1C0;
}

static void touchZero(struct Entity* s) {
  if (((struct Projectile*)s)->body.status & BODY_STATUS_B2 && pZero2 != NULL) {
    s->mode[1] = 2;
    s->mode[2] = 0;
  }
}

// 0x080a2860: grows as it floats up
static void Bubble_Grow(struct Bubble* p) {
  struct Entity* s = &p->s;
  u16 mag;
  if (offScreen(s)) {
    projectileGone(s);
    return;
  }
  UpdateEntityAnim(s);
  rise(s);
  mag = (s->spr).mag.x + 8;
  if (mag > 255) {
    mag = 256;
    s->mode[1]++;
    s->mode[2] = 0;
  }
  (s->spr).mag.x = (s->spr).mag.y = mag;
  touchZero(s);
}

// 0x080a292c
static void Bubble_Float(struct Bubble* p) {
  struct Entity* s = &p->s;
  bool8 right = facingRight(s);
  if (s->mode[2] == 0) {
    InitNonAffineMotion(s);
    SET_XFLIP(p, right);
    SetMotion(s, BUBBLE(0));
    SetDDP(&p->body, &sSpitBody[4]);
    s->mode[2]++;
  }
  if (offScreen(s)) {
    projectileGone(s);
    return;
  }
  UpdateEntityAnim(s);
  rise(s);
  touchZero(s);
}

// 0x080230fc: Zero's slowness taken off, what it could take
static u8 unslow(struct Zero* z, u8 n) {
  u8 was = z->slow;
  makeZeroFaster(z, n);
  return was - z->slow;
}

// 0x080a2a30: on Zero, slowing him until the time is up or he shakes it off
static void Bubble_Stuck(struct Bubble* p) {
  struct Entity* s = &p->s;
  struct Zero* z = pZero2;
  u8 was, n;
  if (z == NULL || !(gStageRun.missionStatus & MISSION_STAY) || (gStageRun.vm.active & VM_ACTIVE)) {
    projectileGone(s);
    return;
  }
  if (s->mode[2] == 0) {
    was = z->slow;
    makeZeroSlower(z, 24);
    if (z->slow == was) {
      projectileGone(s);
      return;
    }
    p->slowed = z->slow - was;
    p->stuck.x = s->coord.x - (z->s).coord.x;
    p->stuck.y = s->coord.y - (z->s).coord.y;
    p->zeroRight = facingRight(&z->s);
    EXIT_BODY(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->time == 0 || --p->time == 0) {
    unslow(z, p->slowed);
    projectileGone(s);
    return;
  }
  if (p->time <= 89 || p->slowed <= 8) {
    if (++s->work[2] & 1) {
      s->flags |= DISPLAY;
    } else {
      s->flags &= ~DISPLAY;
    }
    UpdateEntityAnim(s);
  }
  n = unslow(z, CountButtonMashing(z));
  p->slowed = p->slowed > n ? p->slowed - n : 0;
  if (p->slowed == 0) {
    projectileGone(s);
    return;
  }
  s->coord.x = facingRight(&z->s) == p->zeroRight ? (z->s).coord.x + p->stuck.x : (z->s).coord.x - p->stuck.x;
  s->coord.y = (z->s).coord.y + p->stuck.y;
}

// 0x080a2bf4: shrinks away, blinking
static void Swallowed_Update(struct Spit* p) {
  struct Entity* s = &p->s;
  u8 t;
  UpdateEntityAnim(s);
  t = s->work[2] -= 16;
  (s->spr).mag.x = (s->spr).mag.y = t;
  s->coord.x += s->d.x;
  if (t == 0) {
    projectileGone(s);
  } else if (t <= 63) {
    s->flags = (t & 31) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  } else if (t < 128) {
    s->flags = (t & 63) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  }
}

// 0x080a252c, 0x080a25d0, 0x080a27e0
static void Spit_Update(struct Spit* p) {
  struct Entity* s = &p->s;
  struct Entity* owner = s->unk_28;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Spit_Die(p);
    return;
  }
  switch (s->work[0]) {
    case 0:
    case 1:
      if (owner == NULL) {
        projectileGone(s);
      } else if (owner->mode[0] > ENTITY_UPDATE || ((p->body).status & BODY_STATUS_B2)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Spit_Die(p);
      } else if (s->mode[1] == 0) {
        Glob_Swing(p);
      } else {
        Glob_Fly(p);
      }
      break;
    case 2:
      if (owner == NULL || owner->mode[0] > ENTITY_UPDATE) {
        if (pZero2 != NULL) unslow(pZero2, ((struct Bubble*)p)->slowed);
        projectileGone(s);
      } else if (s->mode[1] == 0) {
        Bubble_Grow((struct Bubble*)p);
      } else if (s->mode[1] == 1) {
        Bubble_Float((struct Bubble*)p);
      } else {
        Bubble_Stuck((struct Bubble*)p);
      }
      break;
    default:
      Swallowed_Update(p);
      break;
  }
}

// 0x080a2578: pops
static void Spit_Die(struct Spit* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 2) {
    PlaySound(SE_Z2_TANK_EXPLODE);
    CreateSmoke(2, &s->coord);
  }
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 32
  work0: 0 arm's link, work1 its seventh. 1 the frog's touch, by its size
*/

struct Link {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  u8 _bc[8];
};
static_assert(sizeof(struct Link) == sizeof(struct Projectile));

static void Link_Init(struct Link* p);
static void Link_Update(struct Link* p);

// clang-format off
const ProjectileRoutine gApZ2FrogLinkRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Link_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Link_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344780
static const struct Collision sLinkBody[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};

// 0x083447b0: none, small, grown
static const struct Collision sTouch[3] = {
    {DDP, FACTION_ENEMY, 0, 0, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0x1000, -0xf00, 0x1000, 0x1e00}},
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0x1200, -0x1200, 0x1000, 0x2400}},
};
// clang-format on

// 0x080a2cf8
static struct Entity* createLink(struct Entity* parent, const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FROG_LINK);
    p->unk_28 = parent;
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x080a2d54
static void Link_Init(struct Link* p) {
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == 0) {
    InitNonAffineMotion(s);
    (s->spr).oam.priority = 3;
    ResetDynamicMotion(s);
    SET_XFLIP(p, FALSE);
    SetMotion(s, FROG(6));
    s->flags |= DISPLAY | FLIPABLE;
    p->home = s->coord;
    INIT_BODY(p, sLinkBody, 64, NULL);
  } else {
    s->flags |= FLIPABLE;
    s->work[2] = 0;
    INIT_BODY(p, sTouch, 64, NULL);
  }
  Link_Update(p);
}

// 0x080a2e50
static void Link_Update(struct Link* p) {
  struct Entity* s = &p->s;
  struct Entity* owner = s->unk_28;
  struct Frog* frog = (struct Frog*)owner;
  u8 touch;
  if (owner->mode[0] > ENTITY_UPDATE) {
    projectileGone(s);
    return;
  }
  if (s->work[0] == 0) {
    UpdateEntityAnim(s);
    sevenths(s, owner, TRUE);
    return;
  }
  s->coord = owner->coord;
  SET_XFLIP(p, facingRight(owner));
  touch = frog->ready && frog->phase < 2 ? frog->phase + 1 : 0;
  if (touch == s->work[2]) return;
  s->work[2] = touch;
  SetDDP(&p->body, &sTouch[touch]);
}

// --------------------------------------------
/*
  Zero 2's VFX 35 work0 0, a puff of the ring of dust round the frog's landing
*/

struct Dust {
  struct Entity s;
  Coords32 home;  // 0x74
  u16 radius;     // 0x7C
  u8 _7e[6];
};
static_assert(sizeof(struct Dust) == sizeof(struct VFX));

static void Dust_Init(struct VFX* p);
static void Dust_Update(struct VFX* p);
static void Dust_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FrogDustRoutine = {
    [ENTITY_INIT] =      Dust_Init,
    [ENTITY_UPDATE] =    Dust_Update,
    [ENTITY_DIE] =       Dust_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b61b4
static void createDust(const Coords32* at, u8 angle) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_FROG_DUST);
  p->coord = *at;
  p->work[1] = angle;
}

// 0x080b6224
static void Dust_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  struct Dust* d = (struct Dust*)p;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  SET_XFLIP(p, FALSE);
  SetMotion(s, MOTION(SM000_BATTLE_EFFECT, 3));
  d->home = s->coord;
  d->radius = 0x200;
  s->work[2] = 0;
  s->flags |= DISPLAY | FLIPABLE;
  Dust_Update(p);
}

// 0x080b6374: out round the landing, behind the frog for the far half
static void Dust_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  struct Dust* d = (struct Dust*)p;
  s32 v;
  UpdateEntityAnim(s);
  s->work[1] += 6;
  d->radius += 0x180;
  v = COS(s->work[1]) * d->radius;
  s->coord.x = d->home.x + ((v < 0 ? v + 255 : v) >> 8);
  v = SIN(s->work[1]) * d->radius;
  s->coord.y = d->home.y + ((v < 0 ? v + 0x7FF : v) >> 11);
  (s->spr).oam.priority = s->work[1] <= 128 ? 2 : 3;
  if (!animDone(s)) return;
  if (++s->work[2] > 1) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  SetMotion(s, MOTION(SM000_BATTLE_EFFECT, 3));
}

// 0x080b6354
static void Dust_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

#endif  // AP
