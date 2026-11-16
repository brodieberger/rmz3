#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
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
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's boss 5, Kuwagust Anchus. Boss of the Bombardment Aircraft.
  Charges and lifts Zero, whirls and throws him, fires chained horn bombs, flies across leaving sparks
*/

struct Kuwagust {
  OBJECT_HDR;
  Coords32 home;              // 0xB4, where he landed
  bool8 hitFromRight;         // 0xBC
  u8 attack;                  // 0xBD, next in turn
  u8 bombSet;                 // 0xBE
  u8 count;                   // 0xBF
  struct Entity* part;        // 0xC0, enemy 33
  s32 left;                   // 0xC4
  s32 right;                  // 0xC8
  struct Entity* other;       // 0xCC, first horn bomb, or far whirlwind
  struct Entity* explosion;   // 0xD0
  s32 floor;                  // 0xD4
  struct Zero* zero;          // 0xD8, held
  u8 flyIn;                   // 0xDC
  u8 _dd;
  s16 sound;                  // 0xDE, whirlwind's
  struct Entity* element;     // 0xE0
};
static_assert(sizeof(struct Kuwagust) == sizeof(struct Boss));

enum {
  KUW_INTRO,
  KUW_TAUNT,
  KUW_NOP,
  KUW_DECIDE,
  KUW_PAUSE,
  KUW_STAGGER,
  KUW_CHARGE_DROP,
  KUW_CHARGE,
  KUW_BRAKE,
  KUW_TURN,
  KUW_LIFT,
  KUW_SQUEEZE,
  KUW_HOP_BACK,
  KUW_HOP_LAND,
  KUW_WHIRL,
  KUW_WHIRLING,
  KUW_WHIRL_TURN,
  KUW_WHIRL_END,
  KUW_SPIN,
  KUW_THROW,
  KUW_THROW_END,
  KUW_BOMB_AIM,
  KUW_BOMBS,
  KUW_BOMB_END,
  KUW_GALE,
  KUW_TAKE_OFF,
  KUW_FLY,
  KUW_DROP_IN,
  KUW_CROUCH,
  KUW_JUMP,
  KUW_LAND,
  KUW_CHARGE_CROUCH,
  KUW_CHARGE_LEAP,
};

#define KUW(n) MOTION(DM213_Z2_KUWAGUST, (n))
#define HORN(n) MOTION(AP_SHEET_Z2_KUWAGUST, (n))
#define WIND(n) MOTION(AP_SHEET_Z2_KUWAGUST_WIND, (n))

// clang-format off
// 0x0833aa94
static const struct Collision sBody[15] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x200, -0xf00, 0x1c00, 0x1e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0x200, -0xf00, 0x1c00, 0x1e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x600, -0x1500, 0x4f00, 0xd00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {-0x600, -0x1500, 0x4f00, 0xd00}},
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 2, 0x00000001, {-0x1200, -0x1000, 0x2400, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xa00, -0x1000, 0x1600, 0x2000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0xa00, -0x1000, 0x1600, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 0, 0x00000001, {0x0, -0x2200, -0x8000, -0x8000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x2200, -0x8000, -0x8000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x200, -0x1200, 0x2600, 0x2c00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0x00000000, {0x200, -0x1200, 0x2600, 0x2c00}},
    {DDP, FACTION_ENEMY, 2, 1, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 129, 0, 0x00000001, {0x0, -0x2200, -0x8000, -0x8000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 129, 2, 0x00000001, {-0x1c00, -0x1600, 0x2a00, 0x1200}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xa00, -0x1700, 0x2200, 0x1400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0xa00, -0x1700, 0x2200, 0x1400}},
};
// clang-format on

#define STAND_BODY (&sBody[0])
#define HOP_BODY (&sBody[1])
#define HORNS_BODY (&sBody[2])
#define WHIRL_BODY (&sBody[4])
#define SPIN_BODY (&sBody[7])
#define THROW_BODY (&sBody[8])
#define FLY_BODY (&sBody[9])
#define LIFT_BODY (&sBody[11])
#define CHARGE_BODY (&sBody[12])

static const Coords32 sElementCoord = {0, -PIXEL(20)};

// After his window
static const struct PreloadEntity sHornSheet = {AP_SHEET_Z2_KUWAGUST, 0, 576, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWindSheet = {AP_SHEET_Z2_KUWAGUST_WIND, 0, 713, 6, 0, AP_PRELOAD_SHEET, 0};

static void Kuwagust_Init(struct Kuwagust* p);
static void Kuwagust_Update(struct Kuwagust* p);
static void Kuwagust_Die(struct Kuwagust* p);

// clang-format off
const BossRoutine gApZ2KuwagustRoutine = {
    [ENTITY_INIT] =      (BossFunc)Kuwagust_Init,
    [ENTITY_UPDATE] =    (BossFunc)Kuwagust_Update,
    [ENTITY_DIE] =       (BossFunc)Kuwagust_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createPart(struct Entity* boss, u8 kind);
static struct Entity* createHornBomb(struct Entity* parent, u8 kind, u8 n);
static struct Entity* createWhirlwind(struct Entity* boss, u8 kind);
static void createSparkMine(const Coords32* at);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void faceZero(struct Kuwagust* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static void stopWind(struct Kuwagust* p) {
  StopSound(p->sound);
  p->sound = -1;
}

static void rest(struct Entity* s, u8 time) {
  s->mode[1] = KUW_PAUSE;
  s->mode[2] = 1;
  s->work[2] = time;
}

static bool8 countDown(struct Entity* s) { return --s->work[2] == 0xFF; }

static bool8 animEnded(struct Entity* s) { return (s->motion).state == ANIM_END; }

// Stands in for Zero 2's thrown state, 0x08022ea8
static void throwZero(struct Zero* z, s32 dx, s32 dy) {
  GotoMotion(&z->s, MOTION(DM004_ZERO_AIR, 4), 2, 1);
  (z->s).mode[1] = ZERO_AIR, (z->s).mode[2] = 2, (z->s).mode[3] = 1;
  (z->unk_b4).blownSpeed = dx;
  (z->s).d.y = dy;
}

// 0x0833ac04, 0x0833ac18
static void holdZero(struct Entity* s, struct Zero* z, s8 f) {
  static const s32 sX[5] = {-0x2600, -0x2600, -0x2200, -0x800, -0x800};
  static const s32 sY[5] = {0, 0, -0xC00, -0x2F00, -0x2F00};
  (z->s).coord.x = facingRight(s) ? s->coord.x - sX[f] : s->coord.x + sX[f];
  (z->s).coord.y = s->coord.y + sY[f];
}

static void hold(struct Kuwagust* p, s8 f) {
  if (!((p->body).status & BODY_STATUS_BINDING) || p->zero == NULL) return;
  holdZero(&p->s, p->zero, f);
}

// Slides to a stop raising dust
static void skid(struct Entity* s) {
  Coords32 at;
  if (s->d.x != 0) s->d.x -= 64;
  if ((s->work[2]++ & 3) == 0) {
    at.x = s->coord.x + (facingRight(s) ? -PIXEL(16) : PIXEL(16));
    at.y = s->coord.y;
    CreateSmoke(3, &at);
  }
  if (facingRight(s)) {
    s->coord.x += s->d.x;
  } else {
    s->coord.x -= s->d.x;
  }
}

static bool8 landed(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if ((u32)s->coord.y <= (u32)p->floor) return FALSE;
  s->coord.y = p->floor;
  return TRUE;
}

// 0x08047cbc
static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Kuwagust* p = (struct Kuwagust*)body->parent;
  struct Entity* other = (body->enemy)->parent;
  if (body->hitboxFlags & BODY_STATUS_BINDING) {
    if (other->kind == ENTITY_PLAYER) p->zero = (struct Zero*)other;
  } else if (body->hitboxFlags & BODY_STATUS_WHITE) {
    p->hitFromRight = other->coord.x > (p->s).coord.x;
  }
}

// 0x08046360
static void Kuwagust_Init(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sHornSheet);
  ApLoadSheet(&sWindSheet);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, KUW(2));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, STAND_BODY, 64);
  (p->body).fn = onHit;
  p->attack = p->bombSet = p->count = 0;
  p->flyIn = 0;
  p->element = NULL;
  p->sound = -1;
  p->part = NULL;
  p->left = s->coord.x;
  p->right = s->coord.x + PIXEL(384);
  p->floor = FUN_08009f6c(p->left + PIXEL(120), s->coord.y);
  p->zero = NULL;
  s->coord.x += PIXEL(384);
  s->coord.y = p->floor - PIXEL(120);
  s->unk_coord.x = s->unk_coord.y = 0;
  s->work[2] = 64;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Kuwagust_Update(p);
}

typedef void (*KuwagustFunc)(struct Kuwagust*);
static const KuwagustFunc sStates[33];

// 0x080464f8
static void Kuwagust_Update(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  struct Zero* z = p->zero;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Kuwagust_Die(p);
    return;
  }
  if (z != NULL && (((z->body).status & BODY_STATUS_DEAD) || (z->body).hp == 0)) p->zero = NULL;
  // 0x0804671c
  if (((p->body).status & BODY_STATUS_WHITE) &&
      (p->element != NULL || (p->element = ApplyElementEffect(13, (Object*)p, &sElementCoord)) != NULL)) {
    stopWind(p);
    setMode(s, KUW_STAGGER);
  }
  sStates[s->mode[1]](p);
}

// 0x08046590: kneels, or is cut and slides apart, then explodes on script's flag 0x80
static void Kuwagust_Die(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    stopWind(p);
    p->part = NULL;
    if ((p->body).status & BODY_STATUS_SLASHED) {
      SetMotion(s, KUW(5));
      s->d.x = facingRight(s) ? 64 : -64;
      s->unk_coord.x = facingRight(s) ? -1 : 1;
      PlaySound(SE_LIGHT);
      p->part = createPart(s, 3);
      s->mode[1] = 0;
    } else {
      SetMotion(s, KUW(4));
      s->mode[1] = 1;
      s->work[2] = 64;
    }
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x != 0) break;
      s->work[2] = 64;
      s->mode[1] = 1;
      break;
    case 1:
      if (s->scriptEntity->flags & 0x80) s->mode[1] = 2;
      break;
    case 2:
      if (s->mode[3] == 0) {
        at.x = facingRight(s) ? -PIXEL(14) : PIXEL(14);
        at.y = -PIXEL(34);
        p->explosion = CreateBossExplosion(s, &at);
        s->mode[3]++;
      }
      if (p->explosion->mode[0] > ENTITY_UPDATE) gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// 0x0804676c: drops in from the right, lands, waits for script's go
static void Kuwagust_Intro(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      UpdateEntityAnim(s);
      if (countDown(s)) s->mode[2]++;
      break;
    case 1:
      s->d.x = -PIXEL(1);
      s->d.y = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      s->d.y += 64;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y) == 0) break;
      s->coord.y = p->floor;
      p->home = s->coord;
      s->mode[2]++;
      break;
    case 3:
      SetMotion(s, KUW(3));
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 5:
      SetMotion(s, KUW(0));
      s->mode[2]++;
      FALLTHROUGH;
    case 6:
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 1) setMode(s, KUW_TAUNT);
      break;
  }
}

// 0x08046864: snaps his horns until the script lets go
static void Kuwagust_Taunt(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(16));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->mode[3] == 0 && (s->motion).cmdIdx == 4) || (s->mode[3] == 1 && (s->motion).cmdIdx == 6)) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    s->mode[3]++;
  }
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, KUW_CHARGE_CROUCH);
}

// 0x080468d8
static void Kuwagust_Nop(struct Kuwagust* p UNUSED) {}

// 0x080468dc: charge, bombs, whirl in turn, the gale now and then once hurt on A rank
static void Kuwagust_Decide(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  u8 attack;
  UpdateEntityAnim(s);
  if (gStageRun.vm.active & VM_ACTIVE) return;
  p->count = 0;
  if (s->coord.x > p->right || s->coord.x < p->left) {
    setMode(s, KUW_CROUCH);
    s->mode[3] = KUW_DECIDE;
    p->attack = (RANDOM(RNG_0202f388) & 0x7FFF) % 3;
    return;
  }
  attack = p->attack;
  if ((p->body).hp <= 31 && gScore.total->rank > 4) {
    if (p->flyIn != 0) {
      p->flyIn--;
    } else {
      p->flyIn = (RANDOM(RNG_0202f388) & 0x7FFF) % 3 + 1;
      attack = 3;
    }
  }
  switch (attack) {
    case 0:
      s->mode[1] = KUW_WHIRL;
      break;
    case 1:
      s->mode[1] = KUW_BOMB_AIM;
      break;
    case 2:
      s->mode[1] = KUW_CHARGE_CROUCH;
      break;
    case 3:
      s->mode[1] = KUW_GALE;
      break;
  }
  if (s->mode[1] == KUW_WHIRL) {
    if (s->coord.x < p->left + PIXEL(192) || s->coord.x > p->right - PIXEL(192)) {
      s->mode[3] = KUW_WHIRL;
      s->mode[1] = KUW_CROUCH;
    }
  } else if (s->mode[1] == KUW_GALE) {
    s->mode[3] = KUW_GALE;
    setMode(s, KUW_CROUCH);
    return;
  }
  s->mode[2] = 0;
  p->attack = (p->attack + 1) % 3;
}

// 0x08046a34
static void Kuwagust_Pause(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, KUW_DECIDE);
}

// 0x08046a70: knocked up and back, then held until the ice is gone
static void Kuwagust_Stagger(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(4));
    SetDDP(&p->body, STAND_BODY);
    s->d.x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    s->d.y = -PIXEL(3);
    p->count = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->element != NULL && IsDead(p->element)) p->element = NULL;
  if (s->mode[3] == 0) {
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    s->d.y += 64;
    if (s->coord.y <= p->home.y) return;
    s->mode[3]++;
    s->coord.y = p->floor;
  } else if (p->element == NULL) {
    setMode(s, KUW_PAUSE);
    s->work[2] = 16;
  }
}

// 0x08046b30: horns down out of the leap
static void Kuwagust_ChargeDrop(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(7));
    SetDDP(&p->body, HORNS_BODY);
    PlaySound(SE_Z2_DESERT_JAW_LUNGE);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, KUW_CHARGE);
}

// 0x08046b8c: across the floor until Zero is caught or the far side
static void Kuwagust_Charge(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, CHARGE_BODY);
    s->d.x = s->d.y = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((p->body).status & BODY_STATUS_BINDING) {
    SetDDP(&p->body, LIFT_BODY);
    setMode(s, KUW_LIFT);
    return;
  }
  if (s->d.x <= 0x6FF) s->d.x += 128;
  if (facingRight(s)) {
    s->coord.x += s->d.x;
    if (s->coord.x > p->right - PIXEL(108)) setMode(s, KUW_BRAKE);
  } else {
    s->coord.x -= s->d.x;
    if (s->coord.x < p->left + PIXEL(108)) setMode(s, KUW_BRAKE);
  }
}

// 0x08046c44
static void Kuwagust_Brake(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(9));
    SetDDP(&p->body, STAND_BODY);
    p->count--;
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  skid(s);
  if (s->d.x != 0) return;
  if (p->count != 0) {
    setMode(s, KUW_TURN);
  } else {
    setMode(s, KUW_PAUSE);
    s->work[2] = 16;
  }
}

// 0x08046d0c
static void Kuwagust_Turn(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(10));
    SET_XFLIP(p, !facingRight(s));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, KUW_CHARGE_CROUCH);
}

// 0x08046d88: Zero up on his horns as he skids
static void Kuwagust_Lift(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(11));
    p->part = createPart(s, 0);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  hold(p, (s->motion).cmdIdx);
  skid(s);
  if (animEnded(s)) setMode(s, KUW_SQUEEZE);
}

// 0x08046eac: until Zero mashes free
static void Kuwagust_Squeeze(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(12));
    p->part->work[1] = 1;
    p->part = createPart(s, 1);
    s->work[2] = 64;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  hold(p, 4);
  if (s->mode[3] == 0) {
    if ((s->motion).cmdIdx == 0) s->mode[3]++;
  } else if ((s->motion).cmdIdx == 1) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    s->mode[3] = 0;
  }
  if (!((p->body).status & BODY_STATUS_BINDING)) {
    SetDDP(&p->body, HOP_BODY);
    setMode(s, KUW_HOP_BACK);
  }
}

// 0x08046f44
static void Kuwagust_HopBack(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    p->part->work[1] = 1;
    s->d.x = facingRight(s) ? -0x180 : 0x180;
    s->d.y = -PIXEL(4);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (landed(p)) setMode(s, KUW_HOP_LAND);
}

// 0x08046fc0
static void Kuwagust_HopLand(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(3));
    SetDDP(&p->body, STAND_BODY);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) {
    setMode(s, KUW_PAUSE);
    s->work[2] = 16;
  }
}

// 0x0804700c: spins up a whirlwind ahead
static void Kuwagust_Whirl(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(19));
    SetDDP(&p->body, WHIRL_BODY);
    faceZero(p);
    s->unk_28 = createWhirlwind(s, 0);
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    if (p->count == 0) p->count = 255;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, KUW_WHIRLING);
}

// 0x080470c8: until Zero is drawn in, gets behind him, or time is up
static void Kuwagust_Whirling(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->count--;
  if ((p->body).status & BODY_STATUS_BINDING) {
    setMode(s, KUW_SPIN);
    s->unk_28->work[1] = 1;
    stopWind(p);
  } else if (facingRight(s) != (s->coord.x < (pZero2->s).coord.x)) {
    setMode(s, KUW_WHIRL_TURN);
  } else if (p->count == 0) {
    setMode(s, KUW_WHIRL_END);
  }
}

// 0x08047148: turns to start again while time is left
static void Kuwagust_WhirlTurn(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    s->unk_28->work[1] = 1;
    stopWind(p);
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (p->count > 64) {
    setMode(s, KUW_WHIRL);
    p->count -= 64;
  } else {
    rest(s, 16);
  }
}

// 0x080471c4
static void Kuwagust_WhirlEnd(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    SetDDP(&p->body, STAND_BODY);
    s->unk_28->work[1] = 1;
    stopWind(p);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) rest(s, 16);
}

// 0x08047230: Zero spun on his horns
static void Kuwagust_Spin(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(11));
    SetDDP(&p->body, SPIN_BODY);
    p->part = createPart(s, 0);
    s->work[2] = 96;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  hold(p, (s->motion).cmdIdx);
  if (countDown(s)) {
    SetDDP(&p->body, THROW_BODY);
    setMode(s, KUW_THROW);
  }
}

// 0x08047314: flung away in a burst
static void Kuwagust_Throw(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(30));
    p->part->work[1] = 1;
    p->part = createPart(s, 2);
    if (p->zero != NULL) {
      at.x = s->coord.x + (facingRight(s) ? PIXEL(10) : -PIXEL(10));
      at.y = s->coord.y - PIXEL(64);
      for (i = 0; i < 16; i++) ApZ2CreateExplosion(s, &at, 2, i << 4);
      throwZero(p->zero, facingRight(s) ? PIXEL(3) : -PIXEL(3), -0x380);
      AppendQuake(8, &s->coord);
    }
    PlaySound(SE_Z2_TANK_EXPLODE);
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, KUW_THROW_END);
}

// 0x08047404
static void Kuwagust_ThrowEnd(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(13));
    SetDDP(&p->body, STAND_BODY);
    p->part->work[1] = 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) rest(s, 32);
}

// 0x0804745c
static void Kuwagust_BombAim(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(33));
    faceZero(p);
    SetDDP(&p->body, STAND_BODY);
    if (p->count == 0) p->count = 3;
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, KUW_BOMBS);
}

// 0x0804750c: four horn bombs out on chains, a set not the last one
static void Kuwagust_Bombs(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  u8 last;
  if (s->mode[2] == 0) {
    s->work[2] = 16;
    last = p->bombSet;
    do {
      p->bombSet = (RANDOM(RNG_0202f388) & 0x7FFF) % 6;
    } while (last == p->bombSet);
    p->other = createHornBomb(s, 0, p->bombSet * 4);
    createHornBomb(s, 0, p->bombSet * 4 + 1);
    createHornBomb(s, 0, p->bombSet * 4 + 2);
    createHornBomb(s, 0, p->bombSet * 4 + 3);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (p->other->mode[0] > ENTITY_UPDATE) setMode(s, KUW_BOMB_END);
}

// 0x080475c4
static void Kuwagust_BombEnd(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    p->count--;
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (p->count != 0) {
    setMode(s, KUW_BOMB_AIM);
  } else {
    rest(s, 32);
  }
}

// 0x08047628: a whirlwind each side, then off
static void Kuwagust_Gale(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(18));
    faceZero(p);
    s->unk_28 = createWhirlwind(s, 1);
    p->other = createWhirlwind(s, 2);
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    if (p->count == 0) p->count = 255;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->unk_28->mode[1] == 1) setMode(s, KUW_TAKE_OFF);
}

// 0x080476f8
static void Kuwagust_TakeOff(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetMotion(s, KUW(1));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 2:
      SetMotion(s, KUW(2));
      s->d.x = facingRight(s) ? -PIXEL(2) : PIXEL(2);
      s->d.y = -PIXEL(6);
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 64;
      if (s->d.y > PIXEL(6)) setMode(s, KUW_FLY);
      break;
  }
}

// 0x080477a4: across and off the far side leaving sparks, up a little once hit four times
static void Kuwagust_Fly(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(8));
    s->d.x = facingRight(s) ? PIXEL(7) : -PIXEL(7);
    s->d.y = 0;
    SetDDP(&p->body, FLY_BODY);
    s->work[2] = s->work[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (((p->body).status & BODY_STATUS_B13) && ++s->work[3] == 4) s->d.y = -0x380;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if ((s->work[2]++ & 3) == 0) {
    at.x = s->coord.x;
    at.y = s->coord.y - PIXEL((RANDOM(RNG_0202f388) & 15) + 12);
    createSparkMine(&at);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
  }
  if (facingRight(s)) {
    if (s->coord.x > p->right + PIXEL(64)) setMode(s, KUW_DROP_IN);
  } else if (s->coord.x < p->left - PIXEL(64)) {
    setMode(s, KUW_DROP_IN);
  }
}

// 0x080478c4: back down in the middle
static void Kuwagust_DropIn(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->unk_28->work[1] = 1;
    p->other->work[1] = 1;
    stopWind(p);
    s->coord.x = p->left + PIXEL(208);
    s->coord.y = p->home.y - PIXEL(160);
    faceZero(p);
    SetDDP(&p->body, STAND_BODY);
    s->d.y = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.y += s->d.y;
  if ((u32)s->coord.y <= (u32)p->floor) return;
  s->coord.y = p->floor;
  setMode(s, KUW_LAND);
  s->mode[3] = KUW_PAUSE;
  s->work[2] = 16;
}

// 0x080479b4
static void Kuwagust_Crouch(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    faceZero(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, KUW_JUMP);
}

// 0x08047a40: to the middle, or for the gale to the side away from Zero
static void Kuwagust_Jump(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    if (s->mode[3] == KUW_GALE) {
      if ((pZero2->s).coord.x > p->left + PIXEL(208)) {
        s->d.x = (p->left + PIXEL(24) - s->coord.x) / 48;
        SET_XFLIP(p, TRUE);
      } else {
        s->d.x = (p->right - PIXEL(24) - s->coord.x) / 48;
        SET_XFLIP(p, FALSE);
      }
    } else {
      s->d.x = (p->left + PIXEL(208) - s->coord.x) / 48;
    }
    s->d.y = -PIXEL(6);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (landed(p)) setMode(s, KUW_LAND);
}

// 0x08047b38
static void Kuwagust_Land(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(3));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, s->mode[3]);
}

// 0x08047b74: away from a wall, else toward Zero
static void Kuwagust_ChargeCrouch(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    if (s->coord.x > p->right - PIXEL(108)) {
      SET_XFLIP(p, FALSE);
    } else if (s->coord.x < p->left + PIXEL(108)) {
      SET_XFLIP(p, TRUE);
    } else {
      faceZero(p);
    }
    if (p->count == 0) p->count = 3;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, KUW_CHARGE_LEAP);
}

// 0x08047c64
static void Kuwagust_ChargeLeap(struct Kuwagust* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->d.y = -0x540;
    s->work[2] = 22;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (countDown(s)) setMode(s, KUW_CHARGE_DROP);
}

// 0x0833aa10
static const KuwagustFunc sStates[33] = {
    Kuwagust_Intro,     Kuwagust_Taunt,      Kuwagust_Nop,       Kuwagust_Decide,     Kuwagust_Pause,
    Kuwagust_Stagger,   Kuwagust_ChargeDrop, Kuwagust_Charge,    Kuwagust_Brake,      Kuwagust_Turn,
    Kuwagust_Lift,      Kuwagust_Squeeze,    Kuwagust_HopBack,   Kuwagust_HopLand,    Kuwagust_Whirl,
    Kuwagust_Whirling,  Kuwagust_WhirlTurn,  Kuwagust_WhirlEnd,  Kuwagust_Spin,       Kuwagust_Throw,
    Kuwagust_ThrowEnd,  Kuwagust_BombAim,    Kuwagust_Bombs,     Kuwagust_BombEnd,    Kuwagust_Gale,
    Kuwagust_TakeOff,   Kuwagust_Fly,        Kuwagust_DropIn,    Kuwagust_Crouch,     Kuwagust_Jump,
    Kuwagust_Land,      Kuwagust_ChargeCrouch, Kuwagust_ChargeLeap,
};

// --------------------------------------------
/*
  Zero 2's enemy 33, riding Kuwagust.
  work0:
    0 grip lifting Zero
    1 grip squeezing him
    2 grip throwing him
    3 his top half once cut, sliding off
  work1: told to go
*/

static void Part_Init(struct Enemy* p);
static void Part_Update(struct Enemy* p);
static void Part_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2KuwagustPartRoutine = {
    [ENTITY_INIT] =      Part_Init,
    [ENTITY_UPDATE] =    Part_Update,
    [ENTITY_DIE] =       Part_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08079798
static struct Entity* createPart(struct Entity* boss, u8 kind) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_KUWAGUST_PART);
    p->unk_28 = boss;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

// 0x08079870..0x080799a8
static void Part_Init(struct Enemy* p) {
  static const u8 sGrips[3] = {14, 15, 32};
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 3) {
    SetMotion(s, KUW(6));
    SET_XFLIP(p, facingRight(boss));
    s->coord = boss->coord;
    s->d.x = facingRight(boss) ? -64 : 64;
    s->unk_coord.x = facingRight(boss) ? 1 : -1;
  } else {
    SetMotion(s, KUW(sGrips[s->work[0]]));
    (s->spr).oam.priority = 1;
  }
  s->flags2 |= WHITE_PAINTABLE;
  s->invincibleID = boss->uniqueID;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

// 0x08079810, 0x08079a5c..0x08079bc4: grips drawn from his texture
static void Part_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (s->work[1] != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Part_Die(p);
    return;
  }
  if (s->work[0] == 3) {
    UpdateEntityAnim(s);
    if (s->mode[1] == 0) {
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[1] = 1;
    } else if (boss->mode[0] == ENTITY_EXIT) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      Part_Die(p);
    }
    return;
  }
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == KUW_STAGGER) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Part_Die(p);
    return;
  }
  FUN_0801779c(s);
  SET_XFLIP(p, facingRight(boss));
  s->coord = boss->coord;
}

// 0x08079850
static void Part_Die(struct Enemy* p) {
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's enemy 30, a missile off a horn bomb, speeding off level. work1: right
*/

static void Missile_Init(struct Enemy* p);
static void Missile_Update(struct Enemy* p);
static void Missile_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2KuwagustMissileRoutine = {
    [ENTITY_INIT] =      Missile_Init,
    [ENTITY_UPDATE] =    Missile_Update,
    [ENTITY_DIE] =       Missile_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x0833fbe0
static const struct Collision sMissile[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, 0x0, 0x1a00, 0x800}},
};
// clang-format on

// 0x080772a0
static void createMissile(struct Entity* bomb, bool8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_KUWAGUST_MISSILE);
    p->unk_28 = bomb;
    p->work[0] = 0;
    p->work[1] = right;
  }
}

// 0x080772f8
static void Missile_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* bomb = s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, HORN(9));
  UpdateEntityAnim(s);
  SET_XFLIP(p, s->work[1]);
  INIT_BODY(p, sMissile, 1, NULL);
  s->coord = bomb->coord;
  s->d.x = 0;
  s->unk_coord.x = 32;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Missile_Update(p);
}

// 0x080773b0
static void Missile_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    if (((struct Entity*)s->unk_28)->mode[0] > ENTITY_UPDATE) {
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    UpdateEntityAnim(s);
    s->work[2] = 128;
    s->mode[1]++;
    return;
  }
  UpdateEntityAnim(s);
  if (s->d.x <= 0x6FF) s->d.x += s->unk_coord.x;
  if (facingRight(s)) {
    s->coord.x += s->d.x;
  } else {
    s->coord.x -= s->d.x;
  }
  if (countDown(s)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Missile_Die(p);
  }
}

// 0x08077450
static void Missile_Die(struct Enemy* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 22, Kuwagust's horn bombs.
  work0:
    0 horn bomb: out, flashing, fires a missile, back
    1 chain link between the bomb and where it started
  work1: which bomb of six sets of four, or which link of five
*/

struct HornBomb {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  u8 _bc[8];
};
static_assert(sizeof(struct HornBomb) == sizeof(struct Projectile));

static void HornBomb_Init(struct HornBomb* p);
static void HornBomb_Update(struct HornBomb* p);
static void HornBomb_Die(struct HornBomb* p);

// clang-format off
const ProjectileRoutine gApZ2HornBombRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)HornBomb_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)HornBomb_Update,
    [ENTITY_DIE] =       (ProjectileFunc)HornBomb_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08343c84
static const struct Collision sHornBomb[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

// 0x0809e5c4
static struct Entity* createHornBomb(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_HORN_BOMB);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x0809e664, 0x0809e7f0
static void HornBomb_Init(struct HornBomb* p) {
  // 0x08343d74, 0x08343d84, 0x08343cb4, 0x08343d14
  static const s32 sX[4] = {0x800, 0xA00, 0, 0x200};
  static const s32 sY[4] = {-0x1800, -0x1100, -0x1800, -0x1100};
  static const s32 sSlowX[24] = {0x39,  0x3D, -0x29, -0x75, -0x58, -0x74, -0x52, -0x74, -0x6E, -0x5B, -0x8A, -0x79,
                                 0x2D,  0x9B, -0xAD, -0x3F, 0x27,  0x4B,  0x36,  0x58,  0x35,  -0x40, -0x54, -0x40};
  static const s32 sSlowY[24] = {-0x79, 0x18,  -0xA3, -0x4F, 0x10, 0x1A, -0xB8, -0xAE, -0x32, -0x20, -0x78, -0x62,
                                 0xD,   0x1B,  0xD,   0x1B,   0xE,  0x1F, -0x73, -0xA5, -0x72, 0x18,  -0x92, -0x5B};
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 n = s->work[1];
  u8 i;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetMotion(s, HORN(7));
    UpdateEntityAnim(s);
    SET_XFLIP(p, facingRight(boss));
    INIT_BODY(p, sHornBomb, 1, NULL);
  } else {
    SetMotion(s, HORN(6));
    UpdateEntityAnim(s);
    SET_XFLIP(p, FALSE);
    if (n & 1) INIT_BODY(p, sHornBomb, 1, NULL);
  }
  (s->spr).oam.priority = n <= 1 ? 2 : 3;
  if (s->work[0] == 0) {
    s->d.x = s->d.y = 0;
    if (facingRight(boss)) {
      s->coord.x = boss->coord.x - sX[n & 3];
      s->unk_coord.x = -sSlowX[n];
    } else {
      s->coord.x = boss->coord.x + sX[n & 3];
      s->unk_coord.x = sSlowX[n];
    }
    s->coord.y = boss->coord.y + sY[n & 3];
    s->unk_coord.y = sSlowY[n];
    s->d.x = s->unk_coord.x * 16;
    s->d.y = s->unk_coord.y * 16;
    p->home = s->coord;
    for (i = 1; i <= 5; i++) createHornBomb(s, 1, i);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  HornBomb_Update(p);
}

static void slowAndMove(struct Entity* s) {
  s->d.x -= s->unk_coord.x;
  s->d.y -= s->unk_coord.y;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// 0x0809e9ec
static void updateLink(struct HornBomb* p) {
  struct Entity* s = &p->s;
  struct HornBomb* bomb = (struct HornBomb*)s->unk_28;
  s32 dx, dy;
  if ((bomb->s).mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateEntityAnim(s);
  dx = ((bomb->s).coord.x - bomb->home.x) / 5;
  dy = ((bomb->s).coord.y - bomb->home.y) / 5;
  s->coord.x = bomb->home.x + s->work[1] * dx;
  s->coord.y = bomb->home.y + s->work[1] * dy;
}

// 0x0809e8ac
static void HornBomb_Update(struct HornBomb* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (s->work[0] != 0) {
    updateLink(p);
    return;
  }
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == KUW_STAGGER) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      slowAndMove(s);
      if (s->d.x != 0) break;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 1:
      SetMotion(s, (s->work[2] & 3) <= 1 ? HORN(7) : HORN(8));
      UpdateEntityAnim(s);
      if (!countDown(s)) break;
      if (!(s->work[1] & 1)) PlaySound(SE_Z2_LEVIATHAN_SHOT);
      createMissile(s, facingRight(boss));
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (countDown(s)) s->mode[1]++;
      break;
    case 3:
      UpdateEntityAnim(s);
      slowAndMove(s);
      if (s->coord.x != p->home.x) break;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      HornBomb_Die(p);
      break;
  }
}

// 0x0809e64c
static void HornBomb_Die(struct HornBomb* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 23, a whirlwind growing up from the floor, drawing Zero in while he touches it.
  work0:
    0 ahead of Kuwagust
    1 the gale's, ahead
    2 the gale's, the far side, facing back
  work1: told to go
*/

static void Whirlwind_Init(struct Projectile* p);
static void Whirlwind_Update(struct Projectile* p);
static void Whirlwind_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2WhirlwindRoutine = {
    [ENTITY_INIT] =      Whirlwind_Init,
    [ENTITY_UPDATE] =    Whirlwind_Update,
    [ENTITY_DIE] =       Whirlwind_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08343da8
static const struct Collision sWhirlwind[1] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, -0x600, 0x2600}},
};
// clang-format on

static void createWhirlDust(const Coords32* at, bool8 right);

// 0x0809ea60
static struct Entity* createWhirlwind(struct Entity* boss, u8 kind) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_WHIRLWIND);
    p->unk_28 = boss;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

// 0x0809eab0
static void Whirlwind_Init(struct Projectile* p) {
  static const s32 sX[3] = {0xA200, 0x6400, 0x16400};  // 0x08343dd8
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitScalerotMotion2(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, WIND(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, s->work[0] != 0 ? !facingRight(boss) : facingRight(boss));
  s->coord.x = boss->coord.x + (facingRight(boss) ? sX[s->work[0]] : -sX[s->work[0]]);
  s->coord.y = boss->coord.y - PIXEL(24);
  s->d.x = facingRight(s) ? -PIXEL(2) : PIXEL(2);
  (s->spr).mag.x = 256;
  (s->spr).mag.y = 16;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Whirlwind_Update(p);
}

// 0x0809ebf0
static void Whirlwind_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  struct Zero* z = pZero2;
  Coords32 at;
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == KUW_STAGGER) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Whirlwind_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 0) {
    if ((s->spr).mag.y == 256) {
      INIT_BODY(p, sWhirlwind, 1, NULL);
      s->work[2] = 0;
      s->mode[1]++;
    } else {
      (s->spr).mag.y += 8;
    }
  } else {
    if ((s->work[2]++ & 3) == 0) {
      at.x = s->coord.x + PIXEL((s32)(RANDOM(RNG_0202f388) & 0xFF) - 128);
      at.y = FUN_08009f6c(at.x, s->coord.y);
      createWhirlDust(&at, !facingRight(s));
    }
    if (s->work[1] != 0) {
      (s->spr).mag.y = 256;
      EXIT_BODY(p);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Whirlwind_Die(p);
      return;
    }
  }
  if (!((p->body).status & BODY_STATUS_B2) || z == NULL || ((z->body).status & BODY_STATUS_DEAD) || (z->body).hp == 0) {
    return;
  }
  if (facingRight(s)) {
    if (s->d.x > -0x380) s->d.x -= 16;
  } else if (s->d.x <= 0x37F) {
    s->d.x += 16;
  }
  ApZ2PushZero(s->d.x);
}

// 0x0809ed64: sinks back into the floor
static void Whirlwind_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if ((s->spr).mag.y > 16) {
    (s->spr).mag.y -= 16;
    return;
  }
  s->flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's projectile 29, a spark Kuwagust leaves flying: swells, holds, blinks out
*/

static void SparkMine_Init(struct Projectile* p);
static void SparkMine_Update(struct Projectile* p);
static void SparkMine_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2SparkMineRoutine = {
    [ENTITY_INIT] =      SparkMine_Init,
    [ENTITY_UPDATE] =    SparkMine_Update,
    [ENTITY_DIE] =       SparkMine_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083445e0
static const struct Collision sSparkMine[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

// 0x080a1a18
static void createSparkMine(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_SPARK_MINE);
    p->coord = *at;
    p->work[0] = p->work[1] = 0;
  }
}

// 0x080a1a64
static void SparkMine_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  InitScalerotMotion2(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, HORN(1));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  (s->spr).mag.x = (s->spr).mag.y = 16;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  SparkMine_Update(p);
}

// 0x080a1ad8
static void SparkMine_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      (s->spr).mag.x += 16;
      (s->spr).mag.y += 16;
      if ((s->spr).mag.x <= 255) break;
      INIT_BODY(p, sSparkMine, 1, NULL);
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 1:
      if (!countDown(s)) break;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 2:
      if (s->work[2] & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (!countDown(s)) break;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      SparkMine_Die(p);
      break;
  }
}

// 0x080a1b98
static void SparkMine_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's VFX 34, dust rising off a whirlwind. work1: right
*/

static void WhirlDust_Init(struct VFX* p);
static void WhirlDust_Update(struct VFX* p);
static void WhirlDust_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2WhirlDustRoutine = {
    [ENTITY_INIT] =      WhirlDust_Init,
    [ENTITY_UPDATE] =    WhirlDust_Update,
    [ENTITY_DIE] =       WhirlDust_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b6070
static void createWhirlDust(const Coords32* at, bool8 right) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_WHIRL_DUST);
  p->coord = *at;
  p->work[0] = 0;
  p->work[1] = right;
}

// 0x080b60c4
static void WhirlDust_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, WIND(1));
  SET_XFLIP(p, s->work[1]);
  s->d.x = facingRight(s) ? PIXEL(2) : -PIXEL(2);
  s->d.y = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  WhirlDust_Update(p);
}

// 0x080b6154
static void WhirlDust_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y -= 32;
  if (animEnded(s)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    WhirlDust_Die(p);
  }
}

// 0x080b619c
static void WhirlDust_Die(struct VFX* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }


// --------------------------------------------
/*
  Zero 2's boss 6, Kuwagust again in Yggdrasil, with his brother (boss 7). Their damage is pooled:
  each takes what the other was dealt. He picks an attack for both, waits till the brother is
  ready, and the two go at once. Dies charging off the side.
*/

struct Kuwagust2 {
  OBJECT_HDR;
  struct Zero* zero;       // 0xB4, held
  s32 floor;               // 0xB8
  bool8 hitFromRight;      // 0xBC
  u8 attack;               // 0xBD, next in turn
  u8 count;                // 0xBE
  bool8 ready;             // 0xBF, for the brother
  s32 left;                // 0xC0
  s32 right;               // 0xC4
  struct Entity* brother;  // 0xC8
  struct Entity* part;     // 0xCC, enemy 33
  u8 jump;                 // 0xD0, 0 when dying
  u8 brotherNext;          // 0xD1, brother's attack, read by him
  u8 angle;                // 0xD2, round the anchor
  u8 turn;                 // 0xD3
  Coords32 centre;         // 0xD4, anchor's mark
  u16 time;                // 0xDC
  s16 sound;               // 0xDE, whirlwind's
  struct Entity* anchor;   // 0xE0
};
static_assert(sizeof(struct Kuwagust2) == sizeof(struct Boss));

enum {
  K2_INTRO,
  K2_TAUNT,
  K2_NOP,
  K2_DECIDE,
  K2_PAUSE,
  K2_NOP2,
  K2_SYNC,
  K2_WHIRL_CROUCH,
  K2_WHIRL_HOP,
  K2_WHIRL_LAND,
  K2_WHIRL,
  K2_WHIRLING,
  K2_WHIRL_TURN,
  K2_WHIRL_END,
  K2_SPIN,
  K2_THROW,
  K2_THROW_END,
  K2_HOP_CROUCH,
  K2_HOP,
  K2_HOP_LAND,
  K2_DASH_CROUCH,
  K2_DASH_JUMP,
  K2_DASH_START,
  K2_DASH,
  K2_DASH_DROP,
  K2_DASH_LAND,
  K2_SKID,
  K2_SKID_TURN,
  K2_DIVE_CROUCH,
  K2_DIVE_JUMP,
  K2_DIVE_FAR,
  K2_DIVE_AIM,
  K2_DIVE,
  K2_DIVE_FALL,
  K2_DIVE_LAND,
  K2_ANCHOR_CROUCH,
  K2_ANCHOR_JUMP,
  K2_ANCHOR_THROW,
  K2_CIRCLE,
  K2_CIRCLE_OFF,
  K2_CIRCLE_LAND,
};

// clang-format off
// 0x0833ad0c
static const struct Collision sBody2[20] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x200, -0xf00, 0x1c00, 0x1e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0x200, -0xf00, 0x1c00, 0x1e00}},
    {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x600, -0x1500, 0x4f00, 0xd00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {-0x600, -0x1500, 0x4f00, 0xd00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 2, 0x00000001, {-0x1200, -0x1000, 0x2400, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xa00, -0x1000, 0x1600, 0x2000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0xa00, -0x1000, 0x1600, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 35, 0, 0x00000001, {0x0, -0x2200, -0x8000, -0x8000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xe00, 0xc00, 0x2200, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0xe00, 0xc00, 0x2200, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, 0xc00, 0x2200, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0x0, 0xc00, 0x2200, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x600, 0xc00, 0x2200, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {-0x600, 0xc00, 0x2200, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x1000, 0xc00, 0x2200, 0x3000}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {-0x1000, 0xc00, 0x2200, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x400, -0x1600, 0x2200, 0x3800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0x400, -0x1600, 0x2200, 0x3800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x2200, -0x8000, -0x8000}},
};
// clang-format on

#define K2_STAND (&sBody2[0])
#define K2_DASH_BODY (&sBody2[2])
#define K2_WHIRL_BODY (&sBody2[4])
#define K2_SPIN_BODY (&sBody2[7])
#define K2_ANCHOR_BODY (&sBody2[16])
#define K2_FAR_BODY (&sBody2[18])
#define K2_THROWN_BODY (&sBody2[19])

static const Coords32 sElementCoord2 = {0, -PIXEL(15)};

static void Kuwagust2_Init(struct Kuwagust2* p);
static void Kuwagust2_Update(struct Kuwagust2* p);
static void Kuwagust2_Die(struct Kuwagust2* p);

// clang-format off
const BossRoutine gApZ2Kuwagust2Routine = {
    [ENTITY_INIT] =      (BossFunc)Kuwagust2_Init,
    [ENTITY_UPDATE] =    (BossFunc)Kuwagust2_Update,
    [ENTITY_DIE] =       (BossFunc)Kuwagust2_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// Zero 2 keeps it in a gameflag, 12 bit 1
static EWRAM_DATA bool8 sMarkCrackling = FALSE;

// Brother at 768, wind clear of him. Zero 2's palettes
static const struct PreloadEntity sHornSheet2 = {AP_SHEET_Z2_KUWAGUST, 0, 576, 7, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWindSheet2 = {AP_SHEET_Z2_KUWAGUST_WIND, 0, 896, 6, 0, AP_PRELOAD_SHEET, 0};

static struct Entity* createBrother(struct Entity* boss);
static u8 brotherDamage(struct Entity* brother);
static bool8 brotherReady(struct Entity* brother);
static struct Entity* createAnchor(struct Entity* parent, u8 kind, u8 brother, u8 n);
static void createAnchorPuff(const Coords32* at);

static void faceMiddle(struct Kuwagust2* p) { SET_XFLIP(p, (p->s).coord.x <= p->right - PIXEL(120)); }

// Gravity, then floor
static bool8 fell(struct Entity* s) {
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  return TRUE;
}

static void pauseAfter(struct Entity* s) {
  setMode(s, K2_PAUSE);
  s->work[2] = 16;
}

static void endWhirl(struct Kuwagust2* p) {
  SetDDP(&p->body, K2_STAND);
  (p->s).unk_28->work[1] = 1;
  StopSound(p->sound);
  p->sound = -1;
}

// 0x08049684
static void onHit2(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Kuwagust2* p = (struct Kuwagust2*)body->parent;
  struct Entity* other = (body->enemy)->parent;
  if (body->hitboxFlags & BODY_STATUS_BINDING) {
    if (other->kind == ENTITY_PLAYER) p->zero = (struct Zero*)other;
  } else if (body->hitboxFlags & BODY_STATUS_WHITE) {
    p->hitFromRight = other->coord.x > (p->s).coord.x;
  }
}

// 0x08047d08
static void Kuwagust2_Init(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sHornSheet2);
  ApLoadSheet(&sWindSheet2);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, KUW(0x23));
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, K2_STAND, 96);
  (p->body).fn = onHit2;
  p->attack = p->count = 0;
  p->left = s->coord.x;
  p->right = s->coord.x + PIXEL(240);
  s->coord.x += PIXEL(208);
  p->floor = s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->centre.x = p->left + PIXEL(120);
  p->centre.y = p->floor - PIXEL(64);
  p->brother = createBrother(s);
  sMarkCrackling = FALSE;
  p->sound = -1;
  s->work[1] = 0;
  s->work[2] = 64;
  p->zero = NULL;
  s->unk_2c = NULL;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Kuwagust2_Update(p);
}

typedef void (*Kuwagust2Func)(struct Kuwagust2*);
static const Kuwagust2Func sStates2[41];

// 0x08047e9c: hit points less the brother's damage, dying at none
static void Kuwagust2_Update(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  struct Zero* z = p->zero;
  s16 hp = (p->body).hp - brotherDamage(p->brother);
  if (hp < 0) hp = 0;
  (p->body).hp = hp;
  if (hp == 0) s->work[1] = 1;
  if (z != NULL && (((z->body).status & BODY_STATUS_DEAD) || (z->body).hp == 0)) p->zero = NULL;
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(15, (Object*)p, &sElementCoord2);
  }
  if (s->unk_2c != NULL && isKilled(s->unk_2c)) s->unk_2c = NULL;
  p->ready = FALSE;
  sStates2[s->mode[1]](p);
}

// 0x08047f48: kneels, slides, explodes on script's flag 0x80
static void Kuwagust2_Die(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(4));
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    if (facingRight(s)) {
      s->d.x = -128;
      s->unk_coord.x = 4;
    } else {
      s->d.x = 128;
      s->unk_coord.x = -4;
    }
    s->work[2] = 64;
    s->coord.y += 0x200;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      s->coord.x += s->d.x;
      if ((s->d.x < 0 ? -s->d.x : s->d.x) > 16) s->d.x += s->unk_coord.x;
      if (countDown(s)) s->mode[1]++;
      break;
    case 1:
      if (s->scriptEntity->flags & 0x80) s->mode[1] = 2;
      break;
    case 2:
      if (s->mode[3] == 0) {
        at.x = p->left - (s->coord.x - PIXEL(120));
        at.y = -PIXEL(20);
        s->unk_28 = CreateBossExplosion(s, &at);
        s->mode[3]++;
      }
      if (s->unk_28->mode[0] > ENTITY_UPDATE) gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// 0x08048098
static void K2_Intro(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  switch (s->mode[2]) {
    case 0:
      s->coord.y -= PIXEL(32);
      PlaySound(SE_Z2_HARPUIA_THUNDER);
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (!animEnded(s)) break;
      s->work[2] = 16;
      s->mode[2]++;
      break;
    case 2:
      if (s->scriptEntity->flags & 1) setMode(s, K2_TAUNT);
      break;
  }
}

// 0x08048100
static void K2_Taunt(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetMotion(s, KUW(0x24));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 2:
      SetMotion(s, KUW(0));
      s->coord.y = p->floor;
      s->work[2] = 16;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, K2_DECIDE);
      break;
  }
}

static void K2_Nop(struct Kuwagust2* p UNUSED) {}

// 0x0804818c: the next attack in turn for both, or the dash while counting down or dying
static void K2_Decide(struct Kuwagust2* p) {
  // 0x0833ac..: his attack, the brother's
  static const u8 sAttacks[4][2] = {{K2_DIVE_CROUCH, 7}, {K2_WHIRL_CROUCH, 20}, {K2_DASH_CROUCH, 12}, {K2_ANCHOR_CROUCH, 27}};
  struct Entity* s = &p->s;
  u8 n;
  UpdateEntityAnim(s);
  if (gStageRun.vm.active & VM_ACTIVE) return;
  s->mode[1] = K2_SYNC;
  if (p->count != 0 || s->work[1] != 0) {
    n = 2;
  } else {
    n = p->attack;
    p->attack = gScore.total->rank > 4 ? (n + 1) & 3 : (n + 1) % 3;
  }
  s->mode[3] = sAttacks[n][0];
  p->brotherNext = sAttacks[n][1];
}

// 0x08048234
static void K2_Pause(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, K2_DECIDE);
}

// 0x08048278
static void K2_Sync(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->ready = TRUE;
  if (brotherReady(p->brother)) setMode(s, s->mode[3]);
}

static void crouch(struct Entity* s, u8 next) {
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, next);
}

static void landing(struct Entity* s, u8 next) {
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(3));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  setMode(s, next);
  if (next == K2_PAUSE) s->work[2] = 16;
}

// 0x080482a4
static void K2_WhirlCrouch(struct Kuwagust2* p) { crouch(&p->s, K2_WHIRL_HOP); }

// 0x080482e0: to the middle
static void K2_WhirlHop(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->d.x = (p->left - (s->coord.x - PIXEL(120))) / 48;
    s->d.y = -0x600;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, K2_WHIRL_LAND);
}

// 0x0804835c
static void K2_WhirlLand(struct Kuwagust2* p) { landing(&p->s, K2_WHIRL); }

// 0x08048398
static void K2_Whirl(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0x13));
    SetDDP(&p->body, K2_WHIRL_BODY);
    SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
    s->unk_28 = createWhirlwind(s, 0);
    p->sound = PlaySound(SE_Z2_FROST_BREATH);
    if (p->count == 0) p->count = 255;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, K2_WHIRLING);
}

// 0x08048454: Zero drawn in, Zero behind, or time up
static void K2_Whirling(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->count--;
  if ((p->body).status & BODY_STATUS_BINDING) {
    setMode(s, K2_SPIN);
    s->unk_28->work[1] = 1;
    StopSound(p->sound);
    p->sound = -1;
    p->count = 0;
  } else if (facingRight(s) != (s->coord.x < (pZero2->s).coord.x)) {
    setMode(s, K2_WHIRL_TURN);
  } else if (p->count == 0) {
    setMode(s, K2_WHIRL_END);
  }
}

// 0x080484d8: again while time is left
static void K2_WhirlTurn(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    endWhirl(p);
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!countDown(s)) return;
  if (p->count > 64) {
    setMode(s, K2_WHIRL);
    p->count -= 64;
  } else {
    setMode(s, K2_HOP_CROUCH);
  }
}

// 0x08048558
static void K2_WhirlEnd(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0));
    endWhirl(p);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, K2_HOP_CROUCH);
}

// 0x080485c0: Zero spun on his horns
static void K2_Spin(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0xB));
    SetDDP(&p->body, K2_SPIN_BODY);
    p->part = createPart(s, 0);
    s->work[2] = 96;
    PlaySound(SE_Z2_FLOWER_CHOMP);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (((p->body).status & BODY_STATUS_BINDING) && p->zero != NULL) holdZero(s, p->zero, (s->motion).cmdIdx);
  if (!countDown(s)) return;
  SetDDP(&p->body, K2_THROWN_BODY);
  setMode(s, K2_THROW);
}

// 0x080486ac: flung away in a burst
static void K2_Throw(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 dx;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0x1E));
    p->part->work[1] = 1;
    p->part = createPart(s, 2);
    if (p->zero != NULL) {
      if (facingRight(s)) {
        at.x = s->coord.x + PIXEL(10);
        dx = PIXEL(3);
      } else {
        at.x = s->coord.x - PIXEL(10);
        dx = -PIXEL(3);
      }
      at.y = s->coord.y - PIXEL(64);
      for (i = 0; i < 16; i++) ApZ2CreateExplosion(s, &at, 2, i << 4);
      throwZero(p->zero, dx, -0x380);
      AppendQuake(8, &s->coord);
    }
    PlaySound(SE_Z2_TANK_EXPLODE);
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, K2_THROW_END);
}

// 0x0804879c
static void K2_ThrowEnd(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0xD));
    SetDDP(&p->body, K2_STAND);
    p->part->work[1] = 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, K2_HOP_CROUCH);
}

// 0x080487f0
static void K2_HopCrouch(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  p->count = 0;
  setMode(s, K2_HOP);
}

// 0x08048884: back the way he came, facing it
static void K2_Hop(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    SET_XFLIP(p, s->d.x < 0);
    s->d.y = -0x600;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, K2_HOP_LAND);
}

// 0x08048920
static void K2_HopLand(struct Kuwagust2* p) { landing(&p->s, K2_PAUSE); }

// 0x08048960
static void K2_DashCrouch(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    p->jump = s->work[1] != 0 ? 0 : (RANDOM(RNG_0202f388) & 1) + 1;
    faceMiddle(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, K2_DASH_JUMP);
}

// 0x08048a24
static void K2_DashJump(struct Kuwagust2* p) {
  static const s32 sUp[3] = {-0x540, -0x580, -0x640};
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->d.y = sUp[p->jump];
    s->work[2] = 22;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (countDown(s)) setMode(s, K2_DASH_START);
}

// 0x08048a98
static void K2_DashStart(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(7));
    PlaySound(SE_Z2_DESERT_JAW_LUNGE);
    SetDDP(&p->body, K2_DASH_BODY);
    faceMiddle(p);
    if (p->count == 0) p->count = RANDOM(RNG_0202f388) % 3 + 1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, K2_DASH);
}

// 0x08048b74: across in the air, dying off the far side
static void K2_Dash(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  bool8 far;
  if (s->mode[2] == 0) {
    s->d.y = s->d.x = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x <= 0x6FF) s->d.x += 128;
  if (facingRight(s)) {
    s->coord.x += s->d.x;
    far = s->coord.x > p->right - (p->jump == 0 ? PIXEL(130) : PIXEL(48));
  } else {
    s->coord.x -= s->d.x;
    far = s->coord.x < p->left + (p->jump == 0 ? PIXEL(130) : PIXEL(48));
  }
  if (!far) return;
  if (p->jump == 0) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Kuwagust2_Die(p);
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
  } else {
    setMode(s, K2_DASH_DROP);
  }
}

// 0x08048c6c
static void K2_DashDrop(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    SET_XFLIP(p, !facingRight(s));
    SetDDP(&p->body, K2_STAND);
    s->d.x &= 0xFF7F;
    p->count--;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x != 0) s->d.x -= 256;
  if (facingRight(s)) {
    s->coord.x -= s->d.x;
  } else {
    s->coord.x += s->d.x;
  }
  s->d.y += 64;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, K2_DASH_LAND);
}

// 0x08048d50
static void K2_DashLand(struct Kuwagust2* p) { landing(&p->s, K2_PAUSE); }

// 0x08048d90
static void K2_Skid(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(9));
    SetDDP(&p->body, K2_STAND);
    s->d.x &= 0xFF7F;
    p->count--;
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x != 0) s->d.x -= 256;
  if ((s->work[2]++ & 3) == 0) {
    at.x = s->coord.x + (facingRight(s) ? -PIXEL(16) : PIXEL(16));
    at.y = s->coord.y;
    CreateSmoke(3, &at);
  }
  if (facingRight(s)) {
    s->coord.x += s->d.x;
  } else {
    s->coord.x -= s->d.x;
  }
  if (s->d.x == 0) setMode(s, K2_SKID_TURN);
}

// 0x08048e54
static void K2_SkidTurn(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0xA));
    SET_XFLIP(p, !facingRight(s));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  pauseAfter(s);
}

// 0x08048ed4
static void K2_DiveCrouch(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    faceMiddle(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, K2_DIVE_JUMP);
}

// 0x08048f5c: up out of sight
static void K2_DiveJump(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->d.y = -0x900;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y == 0) setMode(s, K2_DIVE_FAR);
}

// 0x08048fa4: small, far off over one side, slowing to a stop
static void K2_DiveFar(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, K2_FAR_BODY);
    InitScalerotMotion1(s);
    ResetDynamicMotion(s);
    SetMotion(s, KUW(0x14));
    SET_XFLIP(p, s->coord.x > p->right - PIXEL(120));
    (s->spr).mag.x = (s->spr).mag.y = 128;
    s->coord.x = facingRight(s) ? p->left + PIXEL(32) : p->right - PIXEL(32);
    s->coord.y = p->floor - PIXEL(64);
    s->d.y = 0;
    for (i = 0; i < 32; i++) {
      s->coord.y -= s->d.y;
      s->d.y += 64;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y -= 64;
  if (s->d.y == 0) setMode(s, K2_DIVE_AIM);
}

// 0x080490a4
static void K2_DiveAim(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] != 0) {
    if ((s->motion).cmdIdx == 2) setMode(s, K2_DIVE);
  } else if ((s->motion).state == ANIM_NEXT_GOTO && s->work[2]++ > 1) {
    s->mode[3]++;
  }
}

// 0x08049100: out at the screen, growing
static void K2_Dive(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    at.x = s->coord.x;
    at.y = s->coord.y - PIXEL(12);
    createAnchorPuff(&at);
    s->coord.y = p->floor - PIXEL(64);
    s->d.y = 0;
    s->mode[2]++;
  }
  (s->spr).mag.x += 8;
  (s->spr).mag.y += 8;
  s->coord.y += s->d.y;
  s->d.y -= 32;
  if ((s->spr).mag.x > 255) setMode(s, K2_DIVE_FALL);
}

// 0x08049170
static void K2_DiveFall(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, K2_STAND);
    InitNonAffineMotion(s);
    ResetDynamicMotion(s);
    SetMotion(s, KUW(2));
    faceMiddle(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fell(s)) setMode(s, K2_DIVE_LAND);
}

// 0x08049228
static void K2_DiveLand(struct Kuwagust2* p) { landing(&p->s, K2_PAUSE); }

// 0x08049268
static void K2_AnchorCrouch(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(1));
    if (s->coord.x > p->right - PIXEL(120)) {
      p->angle = 0;
      SET_XFLIP(p, FALSE);
    } else {
      p->angle = 128;
      SET_XFLIP(p, TRUE);
    }
    p->turn = RANDOM(RNG_0202f388) & 3;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, K2_ANCHOR_JUMP);
}

// 0x08049324: up to the ring round the mark
static void K2_AnchorJump(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(2));
    s->d.y = -0x600;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0 && s->coord.y > p->centre.y + PIXEL(28)) {
    s->coord.y = p->centre.y + PIXEL(28);
    setMode(s, K2_ANCHOR_THROW);
  }
}

static void hand(struct Entity* s) {
  s->unk_coord.x = s->coord.x + (facingRight(s) ? PIXEL(11) : -PIXEL(11));
  s->unk_coord.y = s->coord.y - PIXEL(28);
}

// 0x08049380
static void K2_AnchorThrow(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, KUW(0x22));
    SetDDP(&p->body, K2_ANCHOR_BODY);
    p->anchor = createAnchor(s, 0, 0, 0);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  hand(s);
  if (countDown(s)) setMode(s, K2_CIRCLE);
}

// 0x0804940c: round the mark on the chain, turning back once, off at a level point after 300 frames
static void K2_Circle(struct Kuwagust2* p) {
  // 0x0833af1c, 0x0833af3c: by eighth of the circle, facing left then right
  static const u16 sMotions[16] = {0x15, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16,
                                   0x19, 0x1A, 0x1B, 0x1C, 0x15, 0x16, 0x17, 0x18};
  static const u8 sBodies[16] = {8, 10, 14, 14, 12, 10, 10, 8, 12, 14, 14, 10, 8, 8, 10, 10};
  struct Entity* s = &p->s;
  u8 n;
  motion_t m;
  if (s->mode[2] == 0) {
    p->time = 0;
    s->mode[2]++;
    s->mode[3] = p->turn;
    PlaySound(SE_Z2_DESERT_JAW_LUNGE);
  }
  p->time++;
  switch (s->mode[3]) {
    case 0:
      p->angle++;
      if (p->time > 300 && (p->angle & 127) == 0) setMode(s, K2_CIRCLE_OFF);
      break;
    case 1:
      p->angle--;
      if (p->time > 300 && (p->angle & 127) == 0) setMode(s, K2_CIRCLE_OFF);
      break;
    case 2:
    case 3:
      p->angle += s->mode[3] == 2 ? -1 : 1;
      if (p->time > 300) {
        p->time = 120;
        PlaySound(SE_Z2_DESERT_JAW_LUNGE);
        s->mode[3] -= 2;
      }
      break;
  }
  s->coord.x = p->centre.x + COS(p->angle) * 88;
  s->coord.y = p->centre.y + SIN(p->angle) * 48;
  s->unk_coord = s->coord;
  n = ((u8)(p->angle + 16) >> 5) + (facingRight(s) ? 8 : 0);
  m = KUW(sMotions[n]);
  if (((s->motionID << 8) | (s->motion).id) != m) {
    SetMotion(s, m);
    SetDDP(&p->body, &sBody2[sBodies[n]]);
  }
  UpdateEntityAnim(s);
}

// 0x08049558: off the chain once it's back
static void K2_CircleOff(struct Kuwagust2* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->mode[3] == 0) {
    s->unk_coord = s->coord;
    if (p->anchor->mode[0] > ENTITY_UPDATE) {
      SetMotion(s, KUW(2));
      SetDDP(&p->body, K2_STAND);
      faceMiddle(p);
      s->coord.x += facingRight(s) ? -PIXEL(11) : PIXEL(11);
      s->coord.y += PIXEL(28);
      s->mode[3]++;
    }
  }
  UpdateEntityAnim(s);
  if (fell(s)) setMode(s, K2_CIRCLE_LAND);
}

// 0x08049644
static void K2_CircleLand(struct Kuwagust2* p) { landing(&p->s, K2_PAUSE); }

// 0x0833ac68
static const Kuwagust2Func sStates2[41] = {
    K2_Intro,       K2_Taunt,      K2_Nop,         K2_Decide,       K2_Pause,        K2_Nop,
    K2_Sync,        K2_WhirlCrouch, K2_WhirlHop,   K2_WhirlLand,    K2_Whirl,        K2_Whirling,
    K2_WhirlTurn,   K2_WhirlEnd,   K2_Spin,        K2_Throw,        K2_ThrowEnd,     K2_HopCrouch,
    K2_Hop,         K2_HopLand,    K2_DashCrouch,  K2_DashJump,     K2_DashStart,    K2_Dash,
    K2_DashDrop,    K2_DashLand,   K2_Skid,        K2_SkidTurn,     K2_DiveCrouch,   K2_DiveJump,
    K2_DiveFar,     K2_DiveAim,    K2_Dive,        K2_DiveFall,     K2_DiveLand,     K2_AnchorCrouch,
    K2_AnchorJump,  K2_AnchorThrow, K2_Circle,     K2_CircleOff,    K2_CircleLand,
};


// --------------------------------------------
/*
  Zero 2's boss 7, Kuwagust's brother in Yggdrasil. Takes the attack Kuwagust picks for him, waits for
  him, goes with him; what he's dealt Kuwagust loses too. Dies with him, charging off the side.
*/

struct Brother {
  OBJECT_HDR;
  Coords32 home;                // 0xB4, x and floor
  bool8 hitFromRight;           // 0xBC
  u8 _bd;
  u8 count;                     // 0xBE
  bool8 ready;                  // 0xBF, for Kuwagust
  s32 left;                     // 0xC0
  s32 right;                    // 0xC4
  struct Kuwagust2* kuwagust;   // 0xC8
  u8 _cc[4];
  u8 jump;                      // 0xD0
  u8 angle;                     // 0xD1
  u8 damage;                    // 0xD2, this frame's, for Kuwagust
  u8 lastHp;                    // 0xD3
  Coords32 centre;              // 0xD4, anchor's mark
  u16 time;                     // 0xDC
  s16 sound;                    // 0xDE
  struct Entity* anchor;        // 0xE0
};
static_assert(sizeof(struct Brother) == sizeof(struct Boss));

enum {
  B_INTRO,
  B_TAUNT,
  B_NOP,
  B_WAIT,
  B_PAUSE,
  B_NOP2,
  B_SYNC,
  B_GUN_CROUCH,
  B_GUN_HOP,
  B_GUNS,
  B_GUN_FALL,
  B_GUN_LAND,
  B_DASH_CROUCH,
  B_DASH_JUMP,
  B_DASH_START,
  B_DASH,
  B_DASH_DROP,
  B_DASH_LAND,
  B_SKID,
  B_SKID_TURN,
  B_DIVE_CROUCH,
  B_DIVE_JUMP,
  B_DIVE_FAR,
  B_DIVE_AIM,
  B_DIVE,
  B_DIVE_FALL,
  B_DIVE_LAND,
  B_ANCHOR_CROUCH,
  B_ANCHOR_JUMP,
  B_ANCHOR_THROW,
  B_CIRCLE,
  B_CIRCLE_OFF,
  B_CIRCLE_LAND,
};

#define BRO(n) MOTION(DM215_Z2_ANCHUS_BROTHER, (n))

// clang-format off
// 0x0833afe4
static const struct Collision sBody7[19] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1400, 0x2000, 0x2800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0x0, -0x1400, 0x2000, 0x2800}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1a00, 0x3000, 0x1800}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0, 0, 0, 0x00000000, {0x0, -0x1a00, 0x3000, 0x1800}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x100, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0x100, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x300, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {-0x300, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0xd00, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {-0xd00, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x500, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {-0x500, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x500, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0x500, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0xb00, 0xc00, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0xb00, 0xc00, 0x2600, 0x2e00}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x100, -0x1000, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, METAL, 0, 0, 0xffffffff, {0x100, -0x1000, 0x2600, 0x2e00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

#define B_STAND (&sBody7[0])
#define B_DASH_BODY (&sBody7[2])
#define B_ANCHOR_BODY (&sBody7[16])
#define B_FAR_BODY (&sBody7[18])

static const Coords32 sElementCoord7 = {0, -PIXEL(20)};

static void Brother_Init(struct Brother* p);
static void Brother_Update(struct Brother* p);
static void Brother_Die(struct Brother* p);

// clang-format off
const BossRoutine gApZ2AnchusBrotherRoutine = {
    [ENTITY_INIT] =      (BossFunc)Brother_Init,
    [ENTITY_UPDATE] =    (BossFunc)Brother_Update,
    [ENTITY_DIE] =       (BossFunc)Brother_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createGun(struct Entity* parent, u8 kind, u8 n);

static u8 brotherDamage(struct Entity* brother) { return ((struct Brother*)brother)->damage; }

static bool8 brotherReady(struct Entity* brother) { return ((struct Brother*)brother)->ready; }

static void broFaceMiddle(struct Brother* p) { SET_XFLIP(p, (p->s).coord.x <= p->right - PIXEL(120)); }

// 0x080496c8
static struct Entity* createBrother(struct Entity* boss) {
  struct Entity* e = AllocEntityLast(gBossHeaderPtr);
  if (e != NULL) {
    INIT_BOSS_ROUTINE(e, BOSS_Z2_ANCHUS_BROTHER);
    ((struct Brother*)e)->kuwagust = (struct Kuwagust2*)boss;
    e->work[0] = e->work[1] = 0;
    ((struct Brother*)e)->jump = 0;
  }
  return e;
}

// 0x0804a9c0
static void onHit7(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Brother* p = (struct Brother*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) p->hitFromRight = ((body->enemy)->parent)->coord.x > (p->s).coord.x;
}

// 0x0804972c
static void Brother_Init(struct Brother* p) {
  struct Entity* s = &p->s;
  struct Kuwagust2* k = p->kuwagust;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, BRO(0x28));
  SET_XFLIP(p, TRUE);
  ResetBossBody((struct Boss*)p, B_STAND, 96);
  (p->body).fn = onHit7;
  p->_bd = 0;
  s->coord.y = (k->s).coord.y;
  p->left = k->left;
  p->right = k->right;
  s->coord.x = p->left + PIXEL(32);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->home = s->coord;
  p->centre.x = p->left + PIXEL(120);
  p->centre.y = p->home.y - PIXEL(64);
  p->sound = -1;
  p->lastHp = (p->body).hp;
  s->unk_2c = NULL;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Brother_Update(p);
}

typedef void (*BrotherFunc)(struct Brother*);
static const BrotherFunc sStates7[33];

// 0x08049820
static void Brother_Update(struct Brother* p) {
  struct Entity* s = &p->s;
  p->damage = p->lastHp - (u8)(p->body).hp;
  p->lastHp = (p->body).hp;
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(16, (Object*)p, &sElementCoord7);
  }
  if (s->unk_2c != NULL && isKilled(s->unk_2c)) s->unk_2c = NULL;
  p->ready = FALSE;
  sStates7[s->mode[1]](p);
}

// 0x08049894: slides on his knees, gone with Kuwagust
static void Brother_Die(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(3));
    EXIT_BODY(p);
    s->flags2 |= WHITE_PAINTABLE;
    s->invincibleID = (p->kuwagust->s).uniqueID;
    s->coord.y -= 0x200;
    if (facingRight(s)) {
      s->d.x = -128;
      s->unk_coord.x = 4;
    } else {
      s->d.x = 128;
      s->unk_coord.x = -4;
    }
    s->work[2] = 64;
    StopSound(p->sound);
    p->sound = -1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] != 0) {
    if ((p->kuwagust->s).mode[0] == ENTITY_EXIT) SET_BOSS_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  s->coord.x += s->d.x;
  if ((s->d.x < 0 ? -s->d.x : s->d.x) > 16) s->d.x += s->unk_coord.x;
  if (countDown(s)) s->mode[1]++;
}

// 0x0804998c
static void B_Intro(struct Brother* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (s->mode[2] == 0) {
    s->coord.y -= PIXEL(32);
    s->mode[2]++;
  }
  if ((p->kuwagust->s).mode[1] == K2_TAUNT) setMode(s, B_TAUNT);
}

// 0x080499cc
static void B_Taunt(struct Brother* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetMotion(s, BRO(0x29));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 2:
      SetMotion(s, BRO(0));
      s->coord.y = p->home.y;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      if ((p->kuwagust->s).mode[1] == K2_DECIDE) setMode(s, B_WAIT);
      break;
  }
}

static void B_Nop(struct Brother* p UNUSED) {}

// 0x08049a50
static void B_Wait(struct Brother* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->ready = TRUE;
  if (p->kuwagust->brotherNext == 0) return;
  s->mode[1] = B_SYNC;
  s->mode[3] = p->kuwagust->brotherNext;
}

// 0x08049a7c
static void B_Pause(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, B_WAIT);
}

// 0x08049ac0
static void B_Sync(struct Brother* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  p->ready = TRUE;
  if (!p->kuwagust->ready) return;
  p->kuwagust->brotherNext = 0;
  setMode(s, s->mode[3]);
}

static void broCrouch(struct Brother* p, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(1));
    broFaceMiddle(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, next);
}

static void broLanding(struct Entity* s) {
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0x27));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) pauseAfter(s);
}

// 0x08049af4
static void B_GunCrouch(struct Brother* p) { broCrouch(p, B_GUN_HOP); }

// 0x08049b7c: up over the middle
static void B_GunHop(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(2));
    s->d.x = (p->left - (s->coord.x - PIXEL(120))) / 22;
    s->d.y = -0x580;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->d.y == 0) setMode(s, B_GUNS);
}

// 0x08049be8: hangs there while four horn guns go out, aim and fire
static void B_Guns(struct Brother* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0x14));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] != 0) {
    if (s->unk_28->mode[0] > ENTITY_UPDATE) setMode(s, B_GUN_FALL);
  } else if ((s->motion).cmdIdx == 7) {
    p->sound = PlaySound(SE_Z2_PANTER_SPIN);
    s->unk_28 = createGun(s, 0, 0);
    for (i = 1; i < 4; i++) createGun(s, 0, i);
    s->mode[3]++;
  }
}

// 0x08049c74
static void B_GunFall(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0x15));
    StopSound(p->sound);
    p->sound = -1;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, B_GUN_LAND);
}

// 0x08049cd8
static void B_GunLand(struct Brother* p) { broLanding(&p->s); }

// 0x08049d18
static void B_DashCrouch(struct Brother* p) { broCrouch(p, B_DASH_JUMP); }

// 0x08049da0: as high as Kuwagust, by the other's height
static void B_DashJump(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(2));
    switch (p->kuwagust->jump) {
      case 0:
        s->d.y = -0x540;
        p->jump = 0;
        break;
      case 1:
        s->d.y = -0x640;
        p->jump = 2;
        break;
      default:
        s->d.y = -0x580;
        p->jump = 1;
        break;
    }
    s->work[2] = 21;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (countDown(s)) setMode(s, B_DASH_START);
}

// 0x08049e30
static void B_DashStart(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0xA));
    PlaySound(SE_Z2_GOLEM_SLIDE);
    SetDDP(&p->body, B_DASH_BODY);
    broFaceMiddle(p);
    if (p->count == 0) p->count = 3;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->d.y += 64;
  s->coord.y += s->d.y;
  if ((s->motion).state == ANIM_NEXT_GOTO) setMode(s, B_DASH);
}

// 0x08049ee4
static void B_Dash(struct Brother* p) {
  struct Entity* s = &p->s;
  bool8 far;
  if (s->mode[2] == 0) {
    s->d.y = s->d.x = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x <= 0x6FF) s->d.x += 128;
  if (facingRight(s)) {
    s->coord.x += s->d.x;
    far = s->coord.x > p->right - (p->jump == 0 ? PIXEL(130) : PIXEL(48));
  } else {
    s->coord.x -= s->d.x;
    far = s->coord.x < p->left + (p->jump == 0 ? PIXEL(130) : PIXEL(48));
  }
  if (!far) return;
  if (p->jump == 0) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Brother_Die(p);
  } else {
    setMode(s, B_DASH_DROP);
  }
}

// 0x08049fd8
static void B_DashDrop(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0xB));
    SET_XFLIP(p, !facingRight(s));
    SetDDP(&p->body, B_STAND);
    s->d.x &= 0xFF7F;
    p->count--;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x != 0) s->d.x -= 256;
  if (facingRight(s)) {
    s->coord.x -= s->d.x;
  } else {
    s->coord.x += s->d.x;
  }
  s->d.y += 64;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, B_DASH_LAND);
}

// 0x0804a0bc
static void B_DashLand(struct Brother* p) { broLanding(&p->s); }

// 0x0804a0fc
static void B_Skid(struct Brother* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0xC));
    SetDDP(&p->body, B_STAND);
    s->d.x &= 0xFF7F;
    p->count--;
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->d.x != 0) s->d.x -= 256;
  if ((s->work[2]++ & 3) == 0) {
    at.x = s->coord.x + (facingRight(s) ? -PIXEL(16) : PIXEL(16));
    at.y = s->coord.y;
    CreateSmoke(3, &at);
  }
  if (facingRight(s)) {
    s->coord.x += s->d.x;
  } else {
    s->coord.x -= s->d.x;
  }
  if (s->d.x == 0) setMode(s, B_SKID_TURN);
}

// 0x0804a1c0
static void B_SkidTurn(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0xD));
    SET_XFLIP(p, !facingRight(s));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) pauseAfter(s);
}

// 0x0804a240
static void B_DiveCrouch(struct Brother* p) { broCrouch(p, B_DIVE_JUMP); }

// 0x0804a2c8
static void B_DiveJump(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(2));
    s->d.y = -0x900;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y == 0) setMode(s, B_DIVE_FAR);
}

// 0x0804a310
static void B_DiveFar(struct Brother* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, B_FAR_BODY);
    InitScalerotMotion1(s);
    ResetDynamicMotion(s);
    SetMotion(s, BRO(0x1D));
    SET_XFLIP(p, s->coord.x > p->right - PIXEL(120));
    (s->spr).mag.x = (s->spr).mag.y = 128;
    s->coord.x = facingRight(s) ? p->left + PIXEL(32) : p->right - PIXEL(32);
    s->coord.y = p->home.y - PIXEL(64);
    s->d.y = 0;
    for (i = 0; i < 32; i++) {
      s->coord.y -= s->d.y;
      s->d.y += 64;
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y -= 64;
  if (s->d.y == 0) setMode(s, B_DIVE_AIM);
}

// 0x0804a410: dives once Kuwagust is through his throw
static void B_DiveAim(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->mode[3] = 0;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] != 0) {
    if ((s->motion).cmdIdx == 6) setMode(s, B_DIVE);
  } else if ((p->kuwagust->s).mode[1] > K2_THROW_END) {
    s->mode[3]++;
  }
}

// 0x0804a460
static void B_Dive(struct Brother* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    at.x = s->coord.x;
    at.y = s->coord.y - PIXEL(12);
    createAnchorPuff(&at);
    s->coord.y = p->home.y - PIXEL(64);
    s->d.y = 0;
    s->mode[2]++;
  }
  (s->spr).mag.x += 8;
  (s->spr).mag.y += 8;
  s->coord.y += s->d.y;
  s->d.y -= 32;
  if ((s->spr).mag.x > 255) setMode(s, B_DIVE_FALL);
}

// 0x0804a4d0
static void B_DiveFall(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, B_STAND);
    InitNonAffineMotion(s);
    ResetDynamicMotion(s);
    SetMotion(s, BRO(2));
    broFaceMiddle(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fell(s)) setMode(s, B_DIVE_LAND);
}

// 0x0804a588
static void B_DiveLand(struct Brother* p) { broLanding(&p->s); }

// 0x0804a5c8
static void B_AnchorCrouch(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(1));
    if (s->coord.x > p->right - PIXEL(120)) {
      p->angle = 0;
      SET_XFLIP(p, FALSE);
    } else {
      p->angle = 128;
      SET_XFLIP(p, TRUE);
    }
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, B_ANCHOR_JUMP);
}

// 0x0804a658
static void B_AnchorJump(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(2));
    s->d.y = -0x600;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0 && s->coord.y > p->centre.y + PIXEL(28)) {
    s->coord.y = p->centre.y + PIXEL(28);
    setMode(s, B_ANCHOR_THROW);
  }
}

// 0x0804a6b4
static void B_AnchorThrow(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, BRO(0x26));
    SetDDP(&p->body, B_ANCHOR_BODY);
    p->anchor = createAnchor(s, 0, 1, 0);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->unk_coord.x = s->coord.x + (facingRight(s) ? PIXEL(3) : -PIXEL(3));
  s->unk_coord.y = s->coord.y - PIXEL(27);
  if (countDown(s)) setMode(s, B_CIRCLE);
}

// 0x0804a740: Kuwagust's circling, turned his way
static void B_Circle(struct Brother* p) {
  // 0x0833b1b4, 0x0833b1d4
  static const u16 sMotions[16] = {0x1E, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x1F,
                                   0x22, 0x23, 0x24, 0x25, 0x1E, 0x1F, 0x20, 0x21};
  static const u8 sBodies[16] = {4, 14, 14, 12, 10, 10, 8, 6, 10, 12, 14, 14, 4, 6, 8, 10};
  struct Entity* s = &p->s;
  u8 n;
  motion_t m;
  if (s->mode[2] == 0) {
    p->time = 0;
    s->mode[2]++;
    s->mode[3] = p->kuwagust->turn;
  }
  UpdateEntityAnim(s);
  p->time++;
  switch (s->mode[3]) {
    case 0:
      p->angle++;
      if (p->time > 300 && (p->angle & 127) == 0) setMode(s, B_CIRCLE_OFF);
      break;
    case 1:
      p->angle--;
      if (p->time > 300 && (p->angle & 127) == 0) setMode(s, B_CIRCLE_OFF);
      break;
    case 2:
    case 3:
      p->angle += s->mode[3] == 2 ? -1 : 1;
      if (p->time > 300) {
        p->time = 120;
        s->mode[3] -= 2;
      }
      break;
  }
  s->coord.x = p->centre.x + COS(p->angle) * 88;
  s->coord.y = p->centre.y + SIN(p->angle) * 48;
  s->unk_coord = s->coord;
  n = ((u8)(p->angle + 16) >> 5) + (facingRight(s) ? 8 : 0);
  m = BRO(sMotions[n]);
  if (((s->motionID << 8) | (s->motion).id) != m) {
    SetMotion(s, m);
    SetDDP(&p->body, &sBody7[sBodies[n]]);
  }
  UpdateEntityAnim(s);
}

// 0x0804a88c
static void B_CircleOff(struct Brother* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->mode[3] == 0) {
    s->unk_coord = s->coord;
    if (p->anchor->mode[0] > ENTITY_UPDATE) {
      SetMotion(s, BRO(2));
      SetDDP(&p->body, B_STAND);
      broFaceMiddle(p);
      s->coord.x += facingRight(s) ? -PIXEL(11) : PIXEL(11);
      s->coord.y += PIXEL(28);
      s->mode[3]++;
    }
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  s->unk_coord = s->coord;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, B_CIRCLE_LAND);
}

// 0x0804a980
static void B_CircleLand(struct Brother* p) { broLanding(&p->s); }

// 0x0833af60
static const BrotherFunc sStates7[33] = {
    B_Intro,       B_Taunt,      B_Nop,         B_Wait,       B_Pause,       B_Nop,
    B_Sync,        B_GunCrouch,  B_GunHop,      B_Guns,       B_GunFall,     B_GunLand,
    B_DashCrouch,  B_DashJump,   B_DashStart,   B_Dash,       B_DashDrop,    B_DashLand,
    B_Skid,        B_SkidTurn,   B_DiveCrouch,  B_DiveJump,   B_DiveFar,     B_DiveAim,
    B_Dive,        B_DiveFall,   B_DiveLand,    B_AnchorCrouch, B_AnchorJump, B_AnchorThrow,
    B_Circle,      B_CircleOff,  B_CircleLand,
};

// --------------------------------------------
/*
  Zero 2's projectile 30, the brother's horn guns. Four go out on chains, turn on Zero, fire in turn
  and come back.
  work0: 0 gun, 1 link of its chain
  work1: which gun, or which of four links
*/

struct Gun {
  OBJECT_HDR;
  Coords32 home;  // 0xB4
  u8 _bc;
  u8 shown;       // 0xBD, links lit
  u8 _be[6];
};
static_assert(sizeof(struct Gun) == sizeof(struct Projectile));

static void Gun_Init(struct Gun* p);
static void Gun_Update(struct Gun* p);
static void Gun_Die(struct Gun* p);

// clang-format off
const ProjectileRoutine gApZ2AnchusGunRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Gun_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Gun_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Gun_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344624
static const struct Collision sGun[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

// 0x080a1bb0
static struct Entity* createGun(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ANCHUS_GUN);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x080a1c50, 0x080a1da8
static void Gun_Init(struct Gun* p) {
  // 0x08344674, 0x08344678, 0x08344688, 0x08344654, 0x08344664
  static const u8 sAngles[4] = {0xD0, 0x30, 0x60, 0xA0};
  static const s32 sX[4] = {0x1400, -0x1500, -0x1400, 0x1300};
  static const s32 sY[4] = {-0x2200, -0x2200, -0x1000, -0x1000};
  static const s32 sSlowX[4] = {0x78, -0x78, -0x40, 0x40};
  static const s32 sSlowY[4] = {-0x2A, -0x2A, 0x40, 0x40};
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 n = s->work[1];
  u8 i;
  s->palID = 1;
  if (s->work[0] == 0) {
    InitScalerotMotion2(s);
  } else {
    InitNonAffineMotion(s);
  }
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, HORN(s->work[0] == 0 ? 10 : 0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sGun, 1, NULL);
  if (s->work[0] == 0) {
    s->d.x = s->d.y = 0;
    s->angle = sAngles[n];
    if (facingRight(boss)) {
      s->coord.x = boss->coord.x - sX[n];
      s->unk_coord.x = -sSlowX[n];
    } else {
      s->coord.x = boss->coord.x + sX[n];
      s->unk_coord.x = sSlowX[n];
    }
    s->coord.y = boss->coord.y + sY[n];
    s->unk_coord.y = sSlowY[n];
    s->d.x = s->unk_coord.x * 16;
    s->d.y = s->unk_coord.y * 16;
    p->home = s->coord;
    p->shown = 0;
    for (i = 0; i < 4; i++) createGun(s, 1, i);
  } else {
    (s->spr).oam.priority = 3;
    p->shown = 0;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Gun_Update(p);
}

// 0x080a2000
static void gunLink(struct Gun* p) {
  struct Entity* s = &p->s;
  struct Gun* gun = (struct Gun*)s->unk_28;
  if ((gun->s).mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->mode[1] == 0) {
    if (gun->shown >= s->work[1]) {
      SetMotion(s, HORN(1));
      s->mode[1]++;
    }
  } else if (gun->shown < s->work[1]) {
    SetMotion(s, HORN(0));
    s->mode[1] = 0;
  }
  UpdateEntityAnim(s);
  s->coord.x = gun->home.x + s->work[1] * (((gun->s).coord.x - gun->home.x) / 4);
  s->coord.y = gun->home.y + s->work[1] * (((gun->s).coord.y - gun->home.y) / 4);
}

// 0x080a1e44
static void Gun_Update(struct Gun* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 to;
  s32 diff;
  if (s->work[0] != 0) {
    gunLink(p);
    return;
  }
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == 0xFF) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      slowAndMove(s);
      if (s->d.x != 0) break;
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 1:
      p->shown = ++s->work[2] >> 2;
      if (s->work[2] <= 32) break;
      s->work[2] = s->work[1] * 16 + 32;
      s->mode[1]++;
      break;
    case 2:
      to = (u16)(ArcTan2(((pZero2->s).coord.x - s->coord.x) >> 12, ((pZero2->s).coord.y - s->coord.y) >> 12) + 0x4000) >> 8;
      diff = s->angle - to;
      if (diff >= -3 && diff <= 3) {
        s->angle = to;
      } else {
        s->angle += ((s->angle - to + 256) & 255) > 128 ? 4 : -4;
      }
      if (!countDown(s)) break;
      CreateLemon(&s->coord, 0x400, (u8)(s->angle + 64));
      s->work[2] = (3 - s->work[1]) * 16 + 8;
      PlaySound(SE_ENEMY_SHOT);
      s->mode[1]++;
      break;
    case 3:
      if (--s->work[2] == 0) s->mode[1]++;
      break;
    case 4:
      slowAndMove(s);
      if (s->coord.x != p->home.x) break;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Gun_Die(p);
      break;
  }
}

// 0x080a1c38
static void Gun_Die(struct Gun* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 33, the brothers' anchor.
  work0:
    0 head, flung from the hand to the mark, hidden there, then reeled back
    1 link of its chain, work2 of six from the hand, live while the mark is
    2 puff where it strikes
  work1: 1 the brother's, which leaves no mark
*/

struct Anchor {
  OBJECT_HDR;
  Coords32 hand;        // 0xB4
  u8 _bc[4];
  struct Entity* spot;  // 0xC0, enemy 37
};
static_assert(sizeof(struct Anchor) == sizeof(struct Projectile));

static void Anchor_Init(struct Anchor* p);
static void Anchor_Update(struct Anchor* p);
static void Anchor_Die(struct Anchor* p);

// clang-format off
const ProjectileRoutine gApZ2AnchorRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Anchor_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Anchor_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Anchor_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08344830, 0x08344860
static const struct Collision sAnchorSafe[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
static const struct Collision sAnchorLive[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

static struct Entity* createMark(const Coords32* at);

// 0x080a2fcc
static struct Entity* createAnchor(struct Entity* parent, u8 kind, u8 brother, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ANCHOR);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = brother;
    p->work[2] = n;
  }
  return p;
}

// 0x080a3028
static void createAnchorPuff(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ANCHOR);
    p->coord = *at;
    p->work[0] = 2;
    p->work[1] = 0;
  }
}

// 0x080a30c0, 0x080a3174, 0x080a3204
static void Anchor_Init(struct Anchor* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->work[0] == 0) {
    InitScalerotMotion2(s);
  } else {
    InitNonAffineMotion(s);
  }
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case 0:
      SetMotion(s, HORN(s->work[1] != 0 ? 10 : 3));
      UpdateEntityAnim(s);
      SET_XFLIP(p, FALSE);
      INIT_BODY(p, sAnchorLive, 1, NULL);
      s->work[2] = 0;
      for (i = 0; i < 6; i++) createAnchor(s, 1, s->work[1], i);
      break;
    case 1:
      SetMotion(s, HORN(0));
      UpdateEntityAnim(s);
      SET_XFLIP(p, FALSE);
      INIT_BODY(p, sAnchorSafe, 1, NULL);
      s->work[3] = 0;
      break;
    case 2:
      SetMotion(s, WIND(2));
      UpdateEntityAnim(s);
      SET_XFLIP(p, FALSE);
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Anchor_Update(p);
}

static s32 between(s32 from, s32 to, u8 n) { return from + (to - from) * n / 16; }

// 0x080a326c: out over 16 frames, back over 16 once its thrower moves on
static void head(struct Anchor* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  const Coords32* mark = &((struct Kuwagust2*)boss)->centre;
  UpdateEntityAnim(s);
  (s->spr).oam.priority = boss->coord.x < mark->x ? 2 : 3;
  s->work[3] = (s->spr).oam.priority;
  switch (s->mode[1]) {
    case 0:
      s->coord.x = between(boss->unk_coord.x, mark->x, s->work[2]);
      s->coord.y = between(boss->unk_coord.y, mark->y, s->work[2]);
      if (s->work[2]++ <= 15) break;
      if (s->work[1] == 0) {
        p->spot = createMark(mark);
        createAnchorPuff(mark);
      }
      SetDDP(&p->body, sAnchorSafe);
      s->mode[1]++;
      break;
    case 1:
      s->flags &= ~DISPLAY;
      s->coord = *mark;
      if (boss->mode[1] <= (s->work[1] != 0 ? B_CIRCLE : K2_CIRCLE)) break;
      SetDDP(&p->body, sAnchorLive);
      if (s->work[1] == 0) p->spot->mode[1] = 1;
      s->mode[1]++;
      s->work[2] = 16;
      break;
    case 2:
      s->flags |= DISPLAY;
      s->coord.x = between(boss->unk_coord.x, mark->x, s->work[2]);
      s->coord.y = between(boss->unk_coord.y, mark->y, s->work[2]);
      if (countDown(s)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Anchor_Die(p);
        return;
      }
      break;
  }
  p->hand = boss->unk_coord;
  s->angle = (u16)(ArcTan2((s->coord.x - p->hand.x) >> 12, (s->coord.y - p->hand.y) >> 12) + 0x4000) >> 8;
}

// 0x080a3424: lit in a wave down the chain while the mark is
static void link(struct Anchor* p) {
  struct Entity* s = &p->s;
  struct Anchor* h = (struct Anchor*)s->unk_28;
  if ((h->s).mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Anchor_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      if (s->work[3]++ <= 15) break;
      s->work[3] = s->work[2] * 2;
      s->mode[1]++;
      break;
    case 1:
      if (s->work[3] != 0) {
        s->work[3] = sMarkCrackling ? s->work[3] - 1 : s->work[2] * 2;
        if (s->work[3] == 0) {
          SetMotion(s, HORN(1));
          SetDDP(&p->body, sAnchorLive);
        }
      } else if (!sMarkCrackling) {
        SetMotion(s, HORN(0));
        SetDDP(&p->body, sAnchorSafe);
        s->work[3] = s->work[2] * 2;
      }
      UpdateEntityAnim(s);
      UpdateEntityAnim(s);
      break;
  }
  (s->spr).oam.priority = (h->s).work[3] & 3;
  s->coord.x = h->hand.x + (h->s.coord.x - h->hand.x) / 6 * s->work[2];
  s->coord.y = h->hand.y + (h->s.coord.y - h->hand.y) / 6 * s->work[2];
}

static void Anchor_Update(struct Anchor* p) {
  struct Entity* s = &p->s;
  switch (s->work[0]) {
    case 0:
      head(p);
      break;
    case 1:
      link(p);
      break;
    case 2:
      // 0x080a3568
      UpdateEntityAnim(s);
      if (animEnded(s)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Anchor_Die(p);
      }
      break;
  }
}

// 0x080a359c
static void Anchor_Die(struct Anchor* p) {
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's enemy 37, where Kuwagust's anchor strikes. Crackles, lighting both brothers' chains;
  a hit quiets it 64 frames. Goes when told (mode1).
*/

struct Mark {
  OBJECT_HDR;
  u8 _b4[12];
  s16 sound;  // 0xC0
  u8 _c2[2];
};
static_assert(sizeof(struct Mark) == sizeof(struct Enemy));

static void Mark_Init(struct Mark* p);
static void Mark_Update(struct Mark* p);
static void Mark_Die(struct Mark* p);

// clang-format off
const EnemyRoutine gApZ2AnchorMarkRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Mark_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Mark_Update,
    [ENTITY_DIE] =       (EnemyFunc)Mark_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x083400c0, 0x083400f0
static const struct Collision sMarkBody[1] = {
    {DDP, FACTION_ENEMY, 0, 6, 0x00, 0x00, 0x00, 0x00, 0x02, 0, 0, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
static const struct Collision sMarkQuiet[1] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

// 0x0807ac48
static struct Entity* createMark(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ANCHOR_MARK);
    p->coord = *at;
    p->work[0] = p->work[1] = 0;
  }
  return p;
}

// 0x0807acac
static void Mark_Init(struct Mark* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, HORN(4));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sMarkBody, 255, NULL);
  sMarkCrackling = TRUE;
  s->work[2] = 0;
  p->sound = PlaySound(SE_Z2_PANTER_SPIN);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Mark_Update(p);
}

// 0x0807ad60
static void Mark_Update(struct Mark* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Mark_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if ((p->body).status & BODY_STATUS_WHITE) {
    StopSound(p->sound);
    p->sound = -1;
    SetDDP(&p->body, sMarkQuiet);
    sMarkCrackling = FALSE;
    s->work[2] = 64;
  }
  if (s->work[2] == 0 || --s->work[2] != 0) return;
  p->sound = PlaySound(SE_Z2_PANTER_SPIN);
  SetDDP(&p->body, sMarkBody);
  sMarkCrackling = TRUE;
}

// 0x0807ae0c
static void Mark_Die(struct Mark* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, HORN(5));
    StopSound(p->sound);
    p->sound = -1;
    EXIT_BODY(p);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}


#endif
