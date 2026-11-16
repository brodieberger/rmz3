#include "ap.h"
#include "ap_import.h"
#include "anim_loader.h"
#include "boss.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "projectile.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/motion/static.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's boss 23, Elpizo, at the top of Yggdrasil. Hops, guards, dashes, slashes, calls up a
  Pantheon or a Spiking, shoots from the air, and looses the Dark Elf's blast. Beaten, he kneels,
  the Dark Elf's light gathers, and he rises to the middle for script 18.
*/

struct Elpizo {
  OBJECT_HDR;
  u8 _b4[8];
  bool8 hitFromRight;      // 0xBC
  u8 attack;               // 0xBD, next in turn
  u8 _be[6];
  s32 left;                // 0xC4
  s32 right;               // 0xC8
  s32 middle;              // 0xCC
  struct Entity* summoned; // 0xD0
  struct Entity* aura;     // 0xD4, VFX 62 or 65
  u8 rest;                 // 0xD8, frames till the next summon
  u8 _d9[11];
};
static_assert(sizeof(struct Elpizo) == sizeof(struct Boss));

enum {
  ELP_WAIT,
  ELP_TAUNT,
  ELP_NOP,
  ELP_DECIDE,
  ELP_PAUSE,
  ELP_BACK,
  ELP_BACK_LAND,
  ELP_OVER,
  ELP_OVER_FALL,
  ELP_OVER_LAND,
  ELP_GUARD,
  ELP_GUARD_END,
  ELP_DASH_AIM,
  ELP_DASH,
  ELP_DASH_END,
  ELP_SUMMON_START,
  ELP_SUMMON,
  ELP_SUMMON_END,
  ELP_SLASH,
  ELP_SLASH_WAVE,
  ELP_SLASH_END,
  ELP_SHOT_JUMP,
  ELP_SHOT_AIM,
  ELP_SHOT,
  ELP_SHOT_FALL,
  ELP_SHOT_LAND,
  ELP_SHOT_WAIT,
  ELP_SHOT_END,
  ELP_BLAST,
  ELP_BLASTING,
  ELP_BLAST_END,
  ELP_STAGGER,
  ELP_STAGGER_LAND,
};

#define ELP(n) MOTION(DM216_Z2_ELPIZO_BOSS, (n))

// clang-format off
// 0x0833d760
static const struct Collision sBody[15] = {
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, METAL, 0, 2, 0x00000000, {-0xc00, -0x1200, 0x800, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
    {DDP, FACTION_NEUTRAL, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 3, 0x00000001, {-0x2400, -0x1600, 0x2a00, 0x1200}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 2, 0x00000001, {-0x2400, -0x1600, 0x2a00, 0x1200}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {-0x600, -0x1200, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {-0x600, -0x1200, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 2, 0x00000001, {0x800, -0x2e00, 0x800, 0x1600}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 2, 0x00000001, {0x500, -0x3c00, 0x800, 0x3000}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0xffffffff, {0x0, -0x1200, 0x1000, 0x2400}},
};
// clang-format on

#define GUARD_BODY (&sBody[0])
#define STAND_BODY (&sBody[1])
#define DASH_BODY (&sBody[3])
#define SLASH_BODY (&sBody[7])
#define WAVE_BODY (&sBody[10])
#define BLAST_BODY (&sBody[13])

static void Elpizo_Init(struct Elpizo* p);
static void Elpizo_Update(struct Elpizo* p);
static void Elpizo_Die(struct Elpizo* p);

// clang-format off
const BossRoutine gApZ2ElpizoBossRoutine = {
    [ENTITY_INIT] =      (BossFunc)Elpizo_Init,
    [ENTITY_UPDATE] =    (BossFunc)Elpizo_Update,
    [ENTITY_DIE] =       (BossFunc)Elpizo_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createAura(struct Entity* parent, u8 kind, u8 n);
static struct Entity* createSlashWave(struct Entity* boss);
static struct Entity* createAirShot(struct Entity* boss);
static struct Entity* createBlast(struct Entity* boss);
static struct Entity* createCircle(struct Entity* boss);
struct Entity* ApZ2CreateSpiking(s32 x, s32 y, bool8 left);
struct Entity* CreatePantheonHunter(Coords32* c, u8 r1, u8 r2);

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void faceZero(struct Entity* s) { SET_XFLIP(s, s->coord.x < (pZero2->s).coord.x); }

static bool8 countDown(struct Entity* s) { return --s->work[2] == 0xFF; }

static bool8 animEnded(struct Entity* s) { return (s->motion).state == ANIM_END; }

static bool8 fallen(struct Entity* s) {
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  return TRUE;
}

// A motion, then the next mode at its end
static void play(struct Entity* s, u8 n, u8 next) {
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(n));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, next);
}

// 0x08065528
static void onHit(struct Body* body, Coords32* _ UNUSED, Coords32* __ UNUSED) {
  struct Elpizo* p = (struct Elpizo*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) p->hitFromRight = ((body->enemy)->parent)->coord.x > (p->s).coord.x;
}

// 0x08063ec8: walls 12 px in
static void Elpizo_Init(struct Elpizo* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetMotion(s, ELP(0));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, STAND_BODY, 64);
  (p->body).fn = onHit;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->left = FUN_0800a31c(s->coord.x, s->coord.y - PIXEL(8)) + PIXEL(12);
  p->right = FUN_0800a22c(s->coord.x, s->coord.y - PIXEL(8)) - PIXEL(12);
  p->middle = p->left + (p->right - p->left) / 2;
  p->attack = 0;
  p->summoned = NULL;
  p->aura = createAura(s, 2, 0);
  p->rest = 0;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Elpizo_Update(p);
}

typedef void (*ElpizoFunc)(struct Elpizo*);
static const ElpizoFunc sStates[33];

static void keepInside(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->coord.x < p->left) s->coord.x = p->left;
  if (s->coord.x > p->right) s->coord.x = p->right;
}

// 0x08063fbc
static void Elpizo_Update(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Elpizo_Die(p);
    return;
  }
  // 0x08064470: knocked back by a hit that staggers, but not out of the air shot
  if ((u8)(s->mode[1] - ELP_SHOT) > 4 && ((p->body).status & BODY_STATUS_WHITE) &&
      ((p->body).status & BODY_STATUS_B15)) {
    setMode(s, ELP_STAGGER);
  }
  if (p->rest != 0) p->rest--;
  if (p->summoned != NULL && p->summoned->mode[0] > ENTITY_UPDATE) {
    p->summoned = NULL;
    p->rest = 240;
  }
  sStates[s->mode[1]](p);
  keepInside(p);
}

// After his window, Zero 2's
static const struct PreloadEntity sSummonSheet = {AP_SHEET_Z2_FEFNIR_SUMMON, 0, 512, 8, 0, AP_PRELOAD_SHEET, 0};

/*
  0x08064068: knocked back, kneels, waits for script's flags 2 and 0x80, the Dark Elf's light gathers
  round him in a bubble, and he rises to the middle for script 18
*/
static void Elpizo_Die(struct Elpizo* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x16));
    faceZero(s);
    s->d.x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    s->d.y = -PIXEL(3);
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    s->mode[2]++;
  }
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 64;
      if (FUN_080098a4(s->coord.x, s->coord.y) == 0) break;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->mode[1]++;
      break;
    case 1:
      SetMotion(s, ELP(0x18));
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if (!animEnded(s)) break;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 3:
      UpdateEntityAnim(s);
      if (countDown(s)) s->mode[1]++;
      break;
    case 4:
      SetMotion(s, ELP(0x19));
      s->mode[1]++;
      FALLTHROUGH;
    case 5:
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 2) s->mode[1]++;
      break;
    case 6:
      SetMotion(s, ELP(0x1A));
      s->mode[1]++;
      FALLTHROUGH;
    case 7:
      UpdateEntityAnim(s);
      if (s->scriptEntity->flags & 0x80) s->mode[1]++;
      break;
    case 8:
      SetMotion(s, ELP(0x1B));
      s->work[2] = 16;
      s->mode[1]++;
      FALLTHROUGH;
    case 9:
      UpdateEntityAnim(s);
      if (!countDown(s)) break;
      s->unk_28 = ApZ2CreateElpizoBubble(&s->coord);
      PlaySound(SE_Z2_FEFNIR_BUBBLE);
      ApLoadSheet(&sSummonSheet);
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 10:
      if (s->work[2]++ & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      at.x = s->coord.x;
      at.y = s->coord.y - PIXEL(16);
      ApZ2CreateElpizoSpark(&at, (s->work[2] >> 1) * 64 + (RANDOM(RNG_0202f388) & 63));
      if (s->unk_28->mode[3] == 0) break;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    case 11:
      if (s->work[2] & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (!countDown(s)) break;
      PlaySound(SE_Z2_FEFNIR_BUBBLE_GROW);
      s->flags &= ~DISPLAY;
      s->d.x = (PIXEL(720) - s->coord.x) / 64;
      s->d.y = (PIXEL(384) - s->coord.y) / 64;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    case 12:
      s->flags &= ~DISPLAY;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (!countDown(s)) break;
      s->coord.x = PIXEL(720);
      s->coord.y = PIXEL(384);
      s->mode[1]++;
      break;
    case 13:
      s->unk_28->mode[3]++;
      s->mode[1]++;
      break;
    case 14:
    case 15:
      if (s->mode[1] == 14 && s->unk_28->mode[3] > 1) {
        s->work[2] = 48;
        s->mode[1]++;
      }
      s->flags &= ~DISPLAY;
      if (!countDown(s)) break;
      gStageRun.vm.active |= VM_FLAG1;
      SET_BOSS_ROUTINE(p, ENTITY_EXIT);
      break;
  }
  keepInside(p);
}

// 0x080644a4
static void Elp_Wait(struct Elpizo* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (s->scriptEntity->flags & 1) setMode(s, ELP_TAUNT);
}

static const struct PreloadEntity sPillarSheet = {AP_SHEET_Z2_ELPIZO_PILLAR, 0, 819, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sOrbSheet = {AP_SHEET_Z2_ELPIZO_ORB, 0, 512, 7, 0, AP_PRELOAD_SHEET, 0};

// 0x080644e0
static void Elp_Taunt(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0xD));
    ApLoadSheet(&sOrbSheet);
    ApLoadSheet(&sPillarSheet);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, ELP_DECIDE);
}

static void Elp_Nop(struct Elpizo* p UNUSED) {}

static s32 wallAhead(struct Entity* s) {
  return facingRight(s) ? FUN_0800a22c(s->coord.x, s->coord.y) - s->coord.x
                        : s->coord.x - FUN_0800a31c(s->coord.x, s->coord.y);
}

static s32 wallBehind(struct Entity* s) {
  return facingRight(s) ? s->coord.x - FUN_0800a31c(s->coord.x, s->coord.y)
                        : FUN_0800a22c(s->coord.x, s->coord.y) - s->coord.x;
}

// 0x080645c8: in turn, every other one random; no summon while one is out or resting, or near a wall
static void Elp_Decide(struct Elpizo* p) {
  // 0x0833d8c8
  static const u8 sAttacks[8] = {ELP_BACK, ELP_OVER, ELP_GUARD, ELP_DASH_AIM, ELP_SUMMON_START, ELP_SLASH,
                                 ELP_SHOT_JUMP, ELP_BLAST};
  struct Entity* s = &p->s;
  u8 n;
  UpdateEntityAnim(s);
  faceZero(s);
  n = p->attack & 1 ? RANDOM(RNG_0202f388) % 7 : p->attack >> 1;
  s->mode[1] = sAttacks[n];
  if (s->mode[1] == ELP_SUMMON_START || s->mode[1] == ELP_BLAST) {
    if (p->summoned != NULL || p->rest != 0) {
      s->mode[1] = ELP_BACK;
    } else if (wallAhead(s) <= 0x3FFF) {
      setMode(s, ELP_BACK);
      return;
    }
  }
  if (s->mode[1] == ELP_BACK && wallBehind(s) <= 0x2FFF) s->mode[1] = ELP_OVER;
  p->attack = (p->attack + 1) % (gScore.total->rank > 4 ? 15 : 14);
  s->mode[2] = 0;
}

// 0x08064734
static void Elp_Pause(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0));
    SetDDP(&p->body, STAND_BODY);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, ELP_DECIDE);
}

static void guardSound(void) {
  if (!isSoundPlaying(SE_Z2_ELPIZO_GUARD)) PlaySound(SE_Z2_ELPIZO_GUARD);
}

// 0x08064780
static void Elp_Back(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(3));
    s->d.x = facingRight(s) ? -PIXEL(3) : PIXEL(3);
    s->d.y = -PIXEL(2);
    guardSound();
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (fallen(s)) setMode(s, ELP_BACK_LAND);
}

// 0x08064808
static void Elp_BackLand(struct Elpizo* p) { play(&p->s, 4, ELP_DECIDE); }

// 0x08064840: over Zero's head, 64 px past him
static void Elp_Over(struct Elpizo* p) {
  struct Entity* s = &p->s;
  s32 dx;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(5));
    dx = (pZero2->s).coord.x - s->coord.x;
    s->d.x = (dx + (s->coord.x < (pZero2->s).coord.x ? PIXEL(64) : -PIXEL(64))) / 48;
    s->d.y = -PIXEL(6);
    PlaySound(SE_Z2_ELPIZO_LAUGH);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  faceZero(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->d.y > 0) setMode(s, ELP_OVER_FALL);
}

// 0x08064914
static void Elp_OverFall(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(6));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  faceZero(s);
  if (fallen(s)) setMode(s, ELP_OVER_LAND);
}

// 0x080649c0
static void Elp_OverLand(struct Elpizo* p) { play(&p->s, 7, ELP_DECIDE); }

// 0x080649f8
static void Elp_Guard(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(1));
    SetDDP(&p->body, GUARD_BODY);
    s->work[2] = 64;
    guardSound();
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, ELP_GUARD_END);
}

// 0x08064a58
static void Elp_GuardEnd(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) SetDDP(&p->body, STAND_BODY);
  play(s, 2, ELP_DECIDE);
}

// 0x08064aa0
static void Elp_DashAim(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(8));
    faceZero(s);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0) {
    if (!animEnded(s)) return;
    s->work[2] = 16;
    s->mode[3]++;
  } else if (countDown(s)) {
    setMode(s, ELP_DASH);
  }
}

// 0x08064b50: speeds to 4 px a frame, dust behind, stopping at a side
static void Elp_Dash(struct Elpizo* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(9));
    SetDDP(&p->body, DASH_BODY);
    s->unk_coord.x = facingRight(s) ? PIXEL(1) : -PIXEL(1);
    s->d.x = 0;
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->d.x < 0 ? -s->d.x : s->d.x) <= 0x3FF) s->d.x += s->unk_coord.x;
  s->coord.x += s->d.x;
  if ((s->work[2] & 3) == 0) {
    at.x = s->coord.x - s->unk_coord.x * 12;
    at.y = s->coord.y;
    CreateSmoke(3, &at);
    PlaySound(SE_UNK_101);
  }
  if (s->d.x > 0 ? s->coord.x > p->right : s->coord.x < p->left) s->work[2] = 0;
  if (countDown(s)) setMode(s, ELP_DASH_END);
}

// 0x08064c34
static void Elp_DashEnd(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) SetDDP(&p->body, STAND_BODY);
  play(s, 0xA, ELP_DECIDE);
}

// 0x08064c7c
static void Elp_SummonStart(struct Elpizo* p) { play(&p->s, 0xB, ELP_SUMMON); }

// Summons share pillar's window, as in Zero 2. Blast reloads it
static const struct PreloadEntity sSpikingSheet = {AP_SHEET_Z2_CARRYARM, 0, 819, 6, 0, AP_PRELOAD_SHEET, 0};

// 0x08064cb8: a circle, and out of it after 49 frames a Pantheon or a Spiking
static void Elp_Summon(struct Elpizo* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    s->unk_28 = createCircle(s);
    s->work[2] = 0;
    PlaySound(SE_Z2_ELPIZO_SUMMON);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] == 49) {
    at.x = s->coord.x + (facingRight(s) ? PIXEL(32) : -PIXEL(32));
    at.y = s->coord.y;
    if (RANDOM(RNG_0202f388) & 1) {
      wStaticGraphicTilenums[SM019_PANTHEON_HUNTER] = 819;
      wStaticMotionPalIDs[SM019_PANTHEON_HUNTER] = 6;
      LOAD_STATIC_GRAPHIC(SM019_PANTHEON_HUNTER);
      p->summoned = CreatePantheonHunter(&at, 0, 0);
    } else {
      ApLoadSheet(&sSpikingSheet);
      p->summoned = ApZ2CreateSpiking(at.x, at.y, !facingRight(s));
    }
  }
  if (s->unk_28->mode[0] > ENTITY_UPDATE) setMode(s, ELP_SUMMON_END);
}

// 0x08064e04
static void Elp_SummonEnd(struct Elpizo* p) { play(&p->s, 0xC, ELP_DECIDE); }

// 0x08064e3c
static void Elp_Slash(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0xD));
    SetDDP(&p->body, SLASH_BODY);
    faceZero(s);
    s->mode[3] = 0;
    PlaySound(SE_Z2_ELPIZO_SLASH);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->mode[3] == 0 && (s->motion).cmdIdx > 2) {
    SetDDP(&p->body, WAVE_BODY);
    s->mode[3]++;
  }
  if (animEnded(s)) setMode(s, ELP_SLASH_WAVE);
}

// 0x08064f08
static void Elp_SlashWave(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->unk_28 = createSlashWave(s);
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, ELP_SLASH_END);
}

// 0x08064f4c
static void Elp_SlashEnd(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0xE));
    SetDDP(&p->body, STAND_BODY);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  setMode(s, ELP_PAUSE);
  s->work[2] = 64;
}

// 0x08064f98
static void Elp_ShotJump(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(5));
    s->d.x = 0;
    s->d.y = -PIXEL(6);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  faceZero(s);
  s->d.y += 64;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->d.y > 0) setMode(s, ELP_SHOT_AIM);
}

// 0x08065038
static void Elp_ShotAim(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0xF));
    faceZero(s);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) setMode(s, ELP_SHOT);
}

static void forgetGone(struct Entity* s) {
  if (s->unk_28 != NULL && s->unk_28->mode[0] > ENTITY_UPDATE) s->unk_28 = NULL;
}

// 0x080650c4
static void Elp_Shot(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x10));
    s->unk_28 = createAirShot(s);
    PlaySound(SE_Z2_ELPIZO_SHOT);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  forgetGone(s);
  if (animEnded(s)) setMode(s, ELP_SHOT_FALL);
}

// 0x08065120
static void Elp_ShotFall(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(6));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  faceZero(s);
  forgetGone(s);
  if (fallen(s)) setMode(s, ELP_SHOT_LAND);
}

// 0x080651dc: lands, then waits for the shot to do its thing
static void Elp_ShotLand(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(7));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  forgetGone(s);
  if (s->mode[3] == 0) {
    if (animEnded(s)) s->mode[3]++;
  } else if (s->unk_28 == NULL) {
    setMode(s, ELP_DECIDE);
  } else if (s->unk_28->mode[1] != 0) {
    setMode(s, ELP_SHOT_WAIT);
  }
}

// 0x08065244
static void Elp_ShotWait(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x11));
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->unk_28->mode[0] > ENTITY_UPDATE) setMode(s, ELP_SHOT_END);
}

// 0x08065280
static void Elp_ShotEnd(struct Elpizo* p) { play(&p->s, 0x12, ELP_DECIDE); }

// 0x080652b8: the aura flares and the blast goes out
static void Elp_Blast(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x13));
    SetDDP(&p->body, BLAST_BODY);
    p->aura->work[1] = 1;
    p->aura = ApZ2CreateEx(s, 3);
    s->unk_28 = createBlast(s);
    s->work[2] = 64;
    ApLoadSheet(&sPillarSheet);
    PlaySound(SE_Z2_HARPUIA_EX);
    PlaySound(SE_Z2_ELPIZO_BLAST);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (countDown(s)) setMode(s, ELP_BLASTING);
}

// 0x08065388
static void Elp_Blasting(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x14));
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->unk_28->mode[0] > ENTITY_UPDATE) setMode(s, ELP_BLAST_END);
}

// 0x080653c4
static void Elp_BlastEnd(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x15));
    p->aura->work[1] = 1;
    p->aura = createAura(s, 2, 0);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (!animEnded(s)) return;
  setMode(s, ELP_PAUSE);
  s->work[2] = 64;
}

// 0x08065418
static void Elp_Stagger(struct Elpizo* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ELP(0x16));
    SetDDP(&p->body, STAND_BODY);
    faceZero(s);
    s->d.x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    s->d.y = -PIXEL(3);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  setMode(s, ELP_STAGGER_LAND);
}

// 0x080654f0
static void Elp_StaggerLand(struct Elpizo* p) { play(&p->s, 0x17, ELP_DECIDE); }

// 0x0833d6dc
static const ElpizoFunc sStates[33] = {
    Elp_Wait,        Elp_Taunt,      Elp_Nop,       Elp_Decide,      Elp_Pause,      Elp_Back,
    Elp_BackLand,    Elp_Over,       Elp_OverFall,  Elp_OverLand,    Elp_Guard,      Elp_GuardEnd,
    Elp_DashAim,     Elp_Dash,       Elp_DashEnd,   Elp_SummonStart, Elp_Summon,     Elp_SummonEnd,
    Elp_Slash,       Elp_SlashWave,  Elp_SlashEnd,  Elp_ShotJump,    Elp_ShotAim,    Elp_Shot,
    Elp_ShotFall,    Elp_ShotLand,   Elp_ShotWait,  Elp_ShotEnd,     Elp_Blast,      Elp_Blasting,
    Elp_BlastEnd,    Elp_Stagger,    Elp_StaggerLand,
};


// --------------------------------------------
/*
  Zero 2's projectile 55, Elpizo's slash: an orb over him firing a fan of eight bolts, a bolt's flame
  spreading along the floor where it lands.
  work0: 0 orb, 1 bolt, 2 flame
  work1: bolt's angle; flame's way, 1 right
*/

#define ORB(n) MOTION(AP_SHEET_Z2_ELPIZO_ORB, (n))

static void Slash_Init(struct Projectile* p);
static void Slash_Update(struct Projectile* p);
static void Slash_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2ElpizoSlashRoutine = {
    [ENTITY_INIT] =      Slash_Init,
    [ENTITY_UPDATE] =    Slash_Update,
    [ENTITY_DIE] =       Slash_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x0834567c, 0x08345694, 0x083456ac
static const struct Collision sOrb[1] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};
static const struct Collision sBolt[1] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xa00, 0x800, 0x800}},
};
static const struct Collision sFlame[5] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x400, 0x800, 0xe00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xe00, 0x800, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0xa00, 0x800, 0x1a00}},
    {DDP, FACTION_ENEMY, 0, 0, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

// 0x080aa508
static struct Entity* createSlashPart(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ELPIZO_SLASH);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

static struct Entity* createSlashWave(struct Entity* boss) { return createSlashPart(boss, 0, 0); }

// 0x080aa5a4, 0x080aa674, 0x080aa744
static void Slash_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 1) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case 0:
      SetMotion(s, ORB(0));
      SET_XFLIP(p, facingRight(parent));
      INIT_BODY(p, sOrb, 1, NULL);
      s->coord.x = parent->coord.x + (facingRight(s) ? -PIXEL(4) : PIXEL(4));
      s->coord.y = parent->coord.y - PIXEL(96);
      s->work[2] = 64;
      s->work[3] = 0;
      break;
    case 1:
      SetMotion(s, ORB(1));
      SET_XFLIP(p, FALSE);
      s->angle = s->work[1];
      INIT_BODY(p, sBolt, 1, NULL);
      s->renderPrio = 7;
      s->coord = parent->coord;
      s->d.x = SIN(s->work[1]) * 3;
      s->d.y = SIN(s->work[1] + 192) * 3;
      break;
    case 2:
      SetMotion(s, ORB(5));
      SET_XFLIP(p, FALSE);
      INIT_BODY(p, sFlame, 1, NULL);
      s->coord = parent->unk_coord;
      s->work[2] = 0;
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Slash_Update(p);
}

static void slashGone(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR); }

static void slashDone(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Slash_Die(p);
}

// 0x080aa7e8: a bolt every 8 frames, alternately up one side and the other
static void orb(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 n = s->work[3];
  bool8 up;
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == ELP_STAGGER) {
    slashGone(p);
    return;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 7) == 0) {
    up = facingRight(s) ? ((n + 1) & 1) != 0 : (n & 1) != 0;
    createSlashPart(s, 1, up ? (u8)(-40 - n * 8) : (u8)(n * 8 + 40));
    PlaySound(SE_Z2_LEVIATHAN_SHOT);
    s->work[3]++;
  }
  if (countDown(s)) slashDone(p);
}

// 0x080aa8b0: a wall ends it, the floor sets a flame its way
static void bolt(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    slashGone(p);
    return;
  }
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  s->unk_coord.x = s->coord.x;
  s->unk_coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  createSlashPart(s, 2, s->d.x > 0);
  slashDone(p);
}

// 0x080aa938: lights the next 12 px on while there's floor
static void flame(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (++s->work[2] == 9) {
    s->unk_coord.x = s->coord.x + (s->work[1] != 0 ? PIXEL(12) : -PIXEL(12));
    s->unk_coord.y = s->coord.y;
    if (FUN_080098a4(s->unk_coord.x, s->unk_coord.y) == 0) createSlashPart(s, 2, s->work[1]);
  }
  SetDDP(&p->body, &sFlame[(s->motion).cmdIdx]);
  if (animEnded(s)) slashDone(p);
}

static void Slash_Update(struct Projectile* p) {
  switch ((p->s).work[0]) {
    case 0:
      orb(p);
      break;
    case 1:
      bolt(p);
      break;
    case 2:
      flame(p);
      break;
  }
}

// 0x080aa9cc: the orb blinks out
static void Slash_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  if (countDown(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's projectile 56, Elpizo's drain. An unseen centre homes in on Zero and holds him; six orbs
  close round it. Mashing frees an orb every 8 presses, and the orbs left when time's up go back to
  heal him a point each.
  work0: 0 centre, 1 orb
  work1: orb's number
*/

struct Drain {
  OBJECT_HDR;
  u8 _b4[12];
  u16 mashed;  // 0xC0
  u16 orbs;    // 0xC2, left
};
static_assert(sizeof(struct Drain) == sizeof(struct Projectile));

static void Drain_Init(struct Drain* p);
static void Drain_Update(struct Drain* p);
static void Drain_Die(struct Drain* p);

// clang-format off
const ProjectileRoutine gApZ2ElpizoDrainRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Drain_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Drain_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Drain_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x0834575c
static const struct Collision sDrain[1] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

s32 CalcAngleBetweenPoints(s32 x1, s32 y1, s32 x2, s32 y2);
u8 FUN_080e964c(u32 r0, s32 r1, s32 r2);

// Zero 2 aims at a point of Zero's pose
static s32 zeroX(void) { return (pZero2->s).coord.x; }

static s32 zeroY(void) { return (pZero2->s).coord.y - PIXEL(16); }

// 0x080aaa70
static struct Entity* createDrainPart(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ELPIZO_DRAIN);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
    if (kind == 1) ((struct Drain*)parent)->orbs++;
  }
  return p;
}

static struct Entity* createAirShot(struct Entity* boss) { return createDrainPart(boss, 0, 0); }

// 0x080aab48, 0x080aac94
static void Drain_Init(struct Drain* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  u8 i;
  if (s->work[0] == 0) {
    SET_XFLIP(p, facingRight(parent));
    INIT_BODY(p, sDrain, 1, NULL);
    s->coord.x = parent->coord.x + (facingRight(s) ? PIXEL(26) : -PIXEL(26));
    s->coord.y = parent->coord.y - PIXEL(12);
    p->mashed = p->orbs = 0;
    s->work[2] = 128;
    s->work[3] = CalcAngleBetweenPoints(s->coord.x, s->coord.y, zeroX(), zeroY()) - 64;
    s->d.x = 0;
    for (i = 0; i < 6; i++) createDrainPart(s, 1, i);
  } else {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    SetMotion(s, ORB(2));
    UpdateEntityAnim(s);
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, sDrain, 1, NULL);
    s->work[3] = s->work[1] * 256 / 6;
    s->d.x = 0;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Drain_Update(p);
}

// 0x080aad3c: speeds in turning on Zero, holds him once it touches
static void centre(struct Drain* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      s->d.x += 32;
      s->work[3] = FUN_080e964c(CalcAngleBetweenPoints(s->coord.x, s->coord.y, zeroX(), zeroY()), s->work[3], 1);
      s->coord.x += COS(s->work[3]) * s->d.x / 256;
      s->coord.y += SIN(s->work[3]) * s->d.x / 256;
      if (countDown(s)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      if ((p->body).status & BODY_STATUS_B2) s->mode[1]++;
      break;
    case 1:
      s->coord.x = zeroX();
      s->coord.y = zeroY();
      p->mashed += CountButtonMashing(pZero2);
      if (p->orbs == 0) SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

static void orbAround(struct Drain* p, struct Entity* c) {
  struct Entity* s = &p->s;
  s->work[3] += facingRight(s) ? 2 : -2;
  s->renderPrio = s->work[3] > 128 ? 24 : 8;
  s->coord.x = c->coord.x + COS(s->work[3]) * s->d.x / 256;
  s->coord.y = c->coord.y + SIN(s->work[3]) * (s->mode[1] == 0 ? s->d.x : s->d.y) / 256;
}

static void orbGone(struct Drain* p, struct Drain* c) {
  c->orbs--;
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x080aae60: closes in round the centre, squashes round Zero, then back to heal Elpizo
static void drainOrb(struct Drain* p) {
  struct Entity* s = &p->s;
  struct Drain* c = (struct Drain*)s->unk_28;
  struct Boss* boss = (struct Boss*)(c->s).unk_28;
  if ((c->s).mode[0] > ENTITY_UPDATE) {
    orbGone(p, c);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      orbAround(p, &c->s);
      if (s->d.x <= 0xFFF) s->d.x += 128;
      if ((c->s).mode[1] == 0) break;
      s->d.x = s->d.y = PIXEL(16);
      s->work[2] = s->work[1] * 16 + 64;
      s->mode[1]++;
      break;
    case 1:
      orbAround(p, &c->s);
      if (s->d.y > PIXEL(4)) s->d.y -= PIXEL(1);
      if ((s->work[1] + 1) * 8 < c->mashed) {
        c->orbs--;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Drain_Die(p);
        return;
      }
      if (countDown(s)) s->mode[1]++;
      break;
    case 2:
      s->d.x = ((boss->s).coord.x - s->coord.x) / 32;
      s->d.y = ((boss->s).coord.y - (s->coord.y + PIXEL(18))) / 32;
      s->work[2] = 32;
      s->mode[1]++;
      FALLTHROUGH;
    case 3:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (!countDown(s)) break;
      if (((!((boss->body).status & BODY_STATUS_DEAD) && (boss->body).hp != 0) ||
           (gStageRun.missionStatus & MISSION_PLAYER_DEAD)) &&
          (boss->body).hp <= 63) {
        (boss->body).hp++;
      }
      orbGone(p, c);
      break;
  }
}

static void Drain_Update(struct Drain* p) {
  if ((p->s).work[0] == 0) {
    centre(p);
  } else {
    drainOrb(p);
  }
}

// 0x080ab0ac, 0x080ab0c4: a freed orb drops and blinks out
static void Drain_Die(struct Drain* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += PIXEL(1);
  if (s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  if (countDown(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's projectile 57, the Dark Elf blast. An orb tossed up toward Zero, it drops when Elpizo looses
  it, and where it lands a pillar bursts up throwing rocks for 250 frames; then the orb goes back to him.
  work0: 0 orb, 1 pillar
*/

#define PILLAR(n) MOTION(AP_SHEET_Z2_ELPIZO_PILLAR, (n))

static void Blast_Init(struct Projectile* p);
static void Blast_Update(struct Projectile* p);
static void Blast_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2ElpizoBlastRoutine = {
    [ENTITY_INIT] =      Blast_Init,
    [ENTITY_UPDATE] =    Blast_Update,
    [ENTITY_DIE] =       Blast_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x083457c4, 0x083457f4
static const struct Collision sBlastOrb[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 1, 0x00000001, {0x0, -0xc00, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0xc00, 0x800, 0x800}},
};
static const struct Collision sPillar[1] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x7e00, 0x2600, -0x100}},
};
// clang-format on

static void createRock(const Coords32* at, bool8 right);

// 0x080ab1a4
static struct Entity* createBlastPart(struct Entity* parent, u8 kind) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ELPIZO_BLAST);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

static struct Entity* createBlast(struct Entity* boss) { return createBlastPart(boss, 0); }

// 0x080ab270, 0x080ab388
static void Blast_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  InitRotatableMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetMotion(s, ORB(3));
    UpdateEntityAnim(s);
    SET_XFLIP(p, facingRight(parent));
    INIT_BODY(p, sBlastOrb, 1, NULL);
    s->coord.x = parent->coord.x + (facingRight(s) ? PIXEL(22) : -PIXEL(22));
    s->d.x = ((pZero2->s).coord.x - s->coord.x) / 32;
    if (facingRight(s)) {
      if (s->d.x <= 255) s->d.x = PIXEL(1);
    } else if (s->d.x > -PIXEL(1)) {
      s->d.x = -PIXEL(1);
    }
    s->coord.y = parent->coord.y - PIXEL(40);
    s->d.y = -PIXEL(4);
    s->unk_coord.y = 32;
  } else {
    SetMotion(s, PILLAR(0));
    UpdateEntityAnim(s);
    SET_XFLIP(p, FALSE);
    s->renderPrio = 17;
    s->coord.x = parent->coord.x;
    s->coord.y = FUN_08009f6c(parent->coord.x, parent->coord.y);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Blast_Update(p);
}

static void spinOrb(struct Entity* s) {
  s->work[3] += 20;
  s->angle = s->work[3];
}

// 0x080ab408: up, dropped once he looses it, a pillar where it lands, then home to him
static void blastOrb(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      spinOrb(s);
      if (s->d.y < 0) {
        s->coord.x += s->d.x;
        s->coord.y += s->d.y;
        s->d.y += s->unk_coord.y;
      }
      if (boss->mode[1] == ELP_BLASTING) s->mode[1]++;
      break;
    case 1:
      InitNonAffineMotion(s);
      SetMotion(s, ORB(3));
      SET_XFLIP(p, !facingRight(s));
      (s->spr).yflip = TRUE;
      s->flags |= Y_FLIP;
      s->d.y = PIXEL(2);
      s->mode[1]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (s->d.y <= 0x7FF) s->d.y += 128;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(16)) == 0) break;
      PlaySound(SE_Z2_ELPIZO_PILLAR);
      s->unk_2c = createBlastPart(s, 1);
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 3:
      if (countDown(s)) {
        s->work[3] = 128;
        s->mode[1]++;
      }
      break;
    case 4:
      s->work[3] += 2;
      s->coord.y += SIN(s->work[3]);
      if (s->work[3] > 192) s->mode[1]++;
      break;
    case 5:
      s->work[3] += 2;
      s->coord.y += SIN(s->work[3]) / 2;
      if (s->unk_2c->mode[0] > ENTITY_UPDATE) s->mode[1]++;
      break;
    case 6:
      InitRotatableMotion(s);
      SetMotion(s, ORB(3));
      SET_XFLIP(p, facingRight(boss));
      (s->spr).yflip = FALSE;
      s->flags &= ~Y_FLIP;
      s->d.x = (boss->coord.x - (s->coord.x + (facingRight(boss) ? -PIXEL(8) : PIXEL(8)))) / 32;
      s->d.y = (boss->coord.y - (s->coord.y + PIXEL(18))) / 32;
      s->work[2] = 32;
      s->mode[1]++;
      FALLTHROUGH;
    case 7:
      UpdateEntityAnim(s);
      spinOrb(s);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (countDown(s)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Blast_Die(p);
      }
      break;
  }
}

// 0x080ab6c4: bursts up, sparks rising, a rock every 16 frames alternately each way
static void pillar(struct Projectile* p) {
  // 0x0834580c
  static const u8 sSparks[4] = {0, 2, 1, 3};
  struct Entity* s = &p->s;
  u8 i;
  switch (s->mode[1]) {
    case 0:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[1]++;
      break;
    case 1:
      SetMotion(s, PILLAR(1));
      INIT_BODY(p, sPillar, 1, NULL);
      for (i = 0; i <= 12; i++) createAura(s, 0, i);
      s->work[2] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if ((s->work[2] & 15) == 0) {
        createAura(s, 1, sSparks[(s->work[2] >> 4) & 3]);
        createRock(&s->coord, (s->work[2] >> 4) & 1);
      }
      if (s->work[2]++ > 249) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Blast_Die(p);
      }
      break;
  }
}

static void Blast_Update(struct Projectile* p) {
  if ((p->s).work[0] == 0) {
    blastOrb(p);
  } else {
    pillar(p);
  }
}

// 0x080ab7bc, 0x080ab7d4
static void Blast_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (s->mode[2] == 0) {
    SetMotion(s, PILLAR(8));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's enemy 76, a rock the pillar throws, breaking on the floor or under a few hits.
  work0: 1 right
*/

static void Rock_Init(struct Enemy* p);
static void Rock_Update(struct Enemy* p);
static void Rock_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2ElpizoRockRoutine = {
    [ENTITY_INIT] =      Rock_Init,
    [ENTITY_UPDATE] =    Rock_Update,
    [ENTITY_DIE] =       Rock_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x083425dc
static const struct Collision sRock[1] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

// 0x08091380
static void createRock(const Coords32* at, bool8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ELPIZO_ROCK);
    p->coord = *at;
    p->work[0] = right;
    p->work[1] = 0;
  }
}

// 0x080913e4
static void Rock_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, PILLAR(6));
  UpdateEntityAnim(s);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sRock, 8, NULL);
  if (s->work[0] != 0) {
    s->d.x = (RANDOM(RNG_0202f388) & 511) + 128;
  } else {
    s->d.x = -128 - (RANDOM(RNG_0202f388) & 511);
  }
  s->d.y = -(((RANDOM(RNG_0202f388) & 7) + 24) << 6);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Rock_Update(p);
}

// 0x080914e4
static void Rock_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Rock_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->d.y <= 0x6FF) s->d.y += 64;
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Rock_Die(p);
}

// 0x0809156c
static void Rock_Die(struct Enemy* p) {
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's projectile 58, the portal at Elpizo's side he calls a Pantheon or a Spiking out of. Blinks
  in, stays 64 frames, blinks out.
*/

static void Portal_Init(struct Projectile* p);
static void Portal_Update(struct Projectile* p);
static void Portal_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2ElpizoPortalRoutine = {
    [ENTITY_INIT] =      Portal_Init,
    [ENTITY_UPDATE] =    Portal_Update,
    [ENTITY_DIE] =       Portal_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x08345824
static const struct Collision sPortal[1] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1400, 0x2a00}},
};
// clang-format on

// 0x080ab834
static struct Entity* createCircle(struct Entity* boss) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_ELPIZO_PORTAL);
    p->unk_28 = boss;
    p->work[0] = p->work[1] = 0;
  }
  return p;
}

static void blink(struct Entity* s) {
  if (s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
}

// 0x080ab888
static void Portal_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ORB(4));
  UpdateEntityAnim(s);
  SET_XFLIP(p, facingRight(boss));
  INIT_BODY(p, sPortal, 1, NULL);
  (s->spr).oam.priority = 1;
  s->coord.x = boss->coord.x + (facingRight(s) ? PIXEL(41) : -PIXEL(41));
  s->coord.y = boss->coord.y - PIXEL(20);
  s->work[2] = 32;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Portal_Update(p);
}

// 0x080ab97c
static void Portal_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (boss->mode[0] > ENTITY_UPDATE || boss->mode[1] == ELP_STAGGER) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Portal_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->mode[1] == 0) {
    blink(s);
    if (!countDown(s)) return;
    s->flags |= DISPLAY;
    s->work[2] = 64;
    s->mode[1]++;
  } else if (countDown(s)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Portal_Die(p);
  }
}

// 0x080aba24
static void Portal_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  blink(s);
  if (countDown(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's VFX 62. Kinds 0 and 1 ride the blast's pillar, 2 is Elpizo's aura: his own frame behind
  him, two frames late, pulsing, all one color.
  work0: 0 pillar's column, 1 spark rising up it, 2 aura
  work1: 0 column's segment or spark's lane, 1 aura ends
*/

struct Aura {
  struct Entity s;
  Coords32 last;  // 0x74, his coord a frame ago
  Coords32 prev;  // 0x7C, two frames ago
};
static_assert(sizeof(struct Aura) == sizeof(struct VFX));

static void Aura_Init(struct Aura* p);
static void Aura_Update(struct Aura* p);
static void Aura_Die(struct Aura* p);

// clang-format off
const VFXRoutine gApZ2ElpizoAuraRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Aura_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Aura_Update,
    [ENTITY_DIE] =       (VFXFunc)Aura_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

extern const PlttAnimData gApZ2Yggdrasil_PlttAnim139;
extern const AnimCmd* const gApZ2Yggdrasil_PlttAnimScript139[];

// 0x080bcc7c
static struct Entity* createAura(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_ELPIZO_AURA);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x080bcd18, 0x080bcd98, 0x080bce8c
static void Aura_Init(struct Aura* p) {
  static const motion_t sSparks[3] = {PILLAR(2), PILLAR(3), PILLAR(4)};
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 2) {
    InitScalerotMotion1(s);
    s->renderPrio = 25;
    ForceEntityPalette(s, 9);
    s->flags |= DISPLAY;
    ApStartPaletteAnimation(0x8000 | 139, &gApZ2Yggdrasil_PlttAnim139, gApZ2Yggdrasil_PlttAnimScript139, 0x320);
    s->work[3] = 0;
    p->last = p->prev = parent->coord;
  } else {
    InitNonAffineMotion(s);
    s->texture = TEXTURE_AP_SHEET;
    s->flags |= DISPLAY | FLIPABLE;
    if (s->work[0] == 0) {
      SetMotion(s, PILLAR(7));
      SET_XFLIP(s, FALSE);
      s->renderPrio = 17;
      s->coord.x = parent->coord.x;
      s->coord.y = parent->coord.y - PIXEL(19) - PIXEL(16) * s->work[1];
    } else {
      SetMotion(s, sSparks[RANDOM(RNG_0202f388) % 3]);
      SET_XFLIP(s, FALSE);
      s->renderPrio = 17;
      s->coord.x = parent->coord.x - PIXEL(8) + PIXEL(4) * s->work[1] + PIXEL(RANDOM(RNG_0202f388) & 3);
      s->coord.y = parent->coord.y - PIXEL(10);
      s->work[2] = 32;
    }
  }
  SET_VFX_ROUTINE(s, ENTITY_UPDATE);
  Aura_Update(p);
}

// 0x080bcef4, 0x080bcf28, 0x080bcfd4
static void Aura_Update(struct Aura* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 2) {
    s->coord = p->prev;
    p->prev = p->last;
    p->last = parent->coord;
    s->work[3] += 2;
    (s->spr).mag.x = (s->spr).mag.y = (SIN(s->work[3]) + 256) / 14 + 256;
    (s->spr).oam.tileNum = (parent->spr).oam.tileNum;
    (s->spr).sprites = (parent->spr).sprites;
    (s->spr).spriteIdx = (parent->spr).spriteIdx;
    SET_XFLIP(s, facingRight(parent));
    if (parent->mode[0] > ENTITY_UPDATE || s->work[1] != 0) {
      SET_VFX_ROUTINE(s, ENTITY_DIE);
      Aura_Die(p);
    }
    return;
  }
  if (s->work[0] == 0) UpdateEntityAnim(s);
  if (parent->mode[0] > ENTITY_UPDATE) {
    SET_VFX_ROUTINE(s, ENTITY_DIE);
    Aura_Die(p);
    return;
  }
  if (s->work[0] == 0) return;
  UpdateEntityAnim(s);
  s->coord.y -= 0x2C0;
  if (s->mode[1] == 0) {
    if (s->work[2] & 1) {
      s->flags &= ~DISPLAY;
    } else {
      s->flags |= DISPLAY;
    }
    if (countDown(s)) s->mode[1]++;
  } else if (FUN_080098a4(s->coord.x, s->coord.y - 0xAC0)) {
    SET_VFX_ROUTINE(s, ENTITY_DISAPPEAR);
  }
}

// 0x080bd0b4, 0x080bd0cc, 0x080bd148: spark falls, blinking, till it lands
static void Aura_Die(struct Aura* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 1) {
    SET_VFX_ROUTINE(s, ENTITY_EXIT);
    return;
  }
  UpdateEntityAnim(s);
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  blink(s);
  if (countDown(s) || FUN_080098a4(s->coord.x, s->coord.y)) SET_VFX_ROUTINE(s, ENTITY_EXIT);
}

#endif  // AP
