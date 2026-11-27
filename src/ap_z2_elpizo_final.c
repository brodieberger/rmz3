#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "overworld.h"
#include "palette_animation.h"
#include "physics.h"
#include "projectile.h"
#include "random.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Zero 2's boss 19, Elpizo's last form, at the top of Yggdrasil after script 18. Hangs over the middle, calls up
  an attack in turn, each a bit in attacks its claws and fire act on, and now and then fades out and back in
  over another of three spots.
*/

#define FINAL(n) MOTION(DM217_Z2_ELPIZO_FINAL, (n))
#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define OBJ_PAL (0x200 | 4 << 5)
#define BG_PAL 0x40

enum {
  ATTACK_APPEAR = 1 << 0,
  ATTACK_TOP = 1 << 1,
  ATTACK_PILLAR = 1 << 2,
  ATTACK_CLAWS = 1 << 3,
  ATTACK_CLAWS2 = 1 << 4,
  ATTACK_CLAWS3 = 1 << 5,
  ATTACK_CLAWS4 = 1 << 6,
  ATTACK_SWEEP = 1 << 7,
  ATTACK_SWEEP2 = 1 << 8,
  ATTACK_WARP = 1 << 9,
};

struct ElpizoFinal {
  OBJECT_HDR;
  u32 attacks;  // 0xB4
  s32 baseY;    // 0xB8
  u16 timer;    // 0xBC
  u8 rests;     // 0xBE, attacks since the last warp
  u8 spot;      // 0xBF, 0..2
  s32 homeX;    // 0xC0
  s32 floorY;   // 0xC4
  u8 _c8;
  u8 bob;      // 0xC9
  u8 repeats;  // 0xCA
  u8 last;     // 0xCB
  u8 _cc[24];
};
static_assert(sizeof(struct ElpizoFinal) == sizeof(struct Boss));

extern const PlttAnimData gApZ2Yggdrasil_PlttAnim51, gApZ2Yggdrasil_PlttAnim52, gApZ2Yggdrasil_PlttAnim53,
    gApZ2Yggdrasil_PlttAnim54, gApZ2Yggdrasil_PlttAnim55, gApZ2Yggdrasil_PlttAnim56, gApZ2Yggdrasil_PlttAnim57;
extern const AnimCmd* const gApZ2Yggdrasil_PlttAnimScript51[], *const gApZ2Yggdrasil_PlttAnimScript52[],
    *const gApZ2Yggdrasil_PlttAnimScript53[], *const gApZ2Yggdrasil_PlttAnimScript54[],
    *const gApZ2Yggdrasil_PlttAnimScript55[], *const gApZ2Yggdrasil_PlttAnimScript56[],
    *const gApZ2Yggdrasil_PlttAnimScript57[];

#define START(n, ofs) \
  ApStartPaletteAnimation(PLTT_ANIM_ID(n), &gApZ2Yggdrasil_PlttAnim##n, gApZ2Yggdrasil_PlttAnimScript##n, ofs)
#define STEP(n) StepPaletteAnimation(PLTT_ANIM_ID(n))
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

static const struct PreloadEntity sPartsSheet = {AP_SHEET_Z2_ELPIZO_FINAL, 0, 512, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sFxSheet = {AP_SHEET_Z2_ELPIZO_FINAL_FX, 0, 958, 7, 0, AP_PRELOAD_SHEET, 0};

// clang-format off
// 0x0833d4b8
static const struct Collision sBody[4] = {
    {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, -0x700, 0xa00, 0xa00}},
    {DRP, FACTION_ENEMY, 2, 2, 0xff, 0xff, 0xff, 0xff, 0x05, 0, 0, 0, 0x00000000, {0x0, -0x700, 0xa00, 0xa00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, -0x700, 0xa00, 0xa00}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, -0x700, 0xa00, 0xa00}},
};
// clang-format on

static void Final_Init(struct ElpizoFinal* p);
static void Final_Update(struct ElpizoFinal* p);
static void Final_Die(struct ElpizoFinal* p);
static void Final_Disappear(struct ElpizoFinal* p);

// clang-format off
const BossRoutine gApZ2ElpizoFinalRoutine = {
    [ENTITY_INIT] =      (BossFunc)Final_Init,
    [ENTITY_UPDATE] =    (BossFunc)Final_Update,
    [ENTITY_DIE] =       (BossFunc)Final_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Final_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createBody(struct Entity* boss, u8 kind);
static struct Entity* createTentacle(struct Entity* boss, u8 side);
static struct Entity* createTop(struct Entity* boss, const Coords32* at);
static struct Entity* createRock(struct Entity* boss);
static struct Entity* createPetal(struct Entity* boss, u8 n);
static struct Entity* createOrb(struct Entity* boss, const Coords32* at, u8 n);
static struct Entity* createSeeker(struct Entity* boss, const Coords32* at);
static void createPuffs(const Coords32* at);
static struct Entity* createFlame(struct Entity* boss, const Coords32* at, u8 side);
static struct Entity* createBurst(struct Entity* boss, const Coords32* at);
static struct Entity* createBolt(struct Entity* boss, const Coords32* at, u8 side);
static struct Entity* createWall(struct Entity* boss, const Coords32* at, u8 side);

static bool8 animEnded(struct Entity* s) { return (s->motion).state == ANIM_END; }

// 0x080613cc
static void bob(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  s->coord.y = p->baseY + SIN(p->bob) * 5;
  p->bob += 3;
}

// 0x08060fe4
static void smoke(struct Entity* s, bool8 big) {
  Coords32 at;
  s32 r = RANDOM(RNG_0202f388) & 63;
  u8 a = RANDOM(RNG_0202f388);
  at.x = s->coord.x + COS(a) * r;
  at.y = s->coord.y + SIN(a) * r;
  CreateSmoke(big ? 1 : 2, &at);
}

// 0x08061084: not the same attack three times running
static bool8 again(struct ElpizoFinal* p, u8 attack) {
  if (p->last != attack) {
    p->repeats = 0;
    p->last = attack;
    return FALSE;
  }
  if (p->repeats != 0) return TRUE;
  p->repeats++;
  return FALSE;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

// 0x08061408: forms out of four petals of light, spreads its claws, then rises
static void Final_Appear(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  u8 state;
  switch (s->mode[2]) {
    case 0:
      s->flags &= ~DISPLAY;
      if (s->scriptEntity->flags & 1) s->mode[2]++;
      return;
    case 1:
      PlaySound(SE_Z2_FINAL_APPEAR);
      s->flags |= DISPLAY;
      gOverworld.work.apZ2Yggdrasil.anchor = s;
      s->work[2] = 0;
      SetMotion(s, FINAL(0));
      START(51, OBJ_PAL);
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      PlaySound(SE_Z2_FINAL_PETAL);
      s->work[3] = 32;
      createPetal(s, s->work[2]);
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      state = STEP(51);
      if (--s->work[3] == 0) {
        if (++s->work[2] != 4) s->mode[2] = 2;
      } else if (s->work[2] == 4 && state == 4) {
        s->mode[2]++;
      }
      break;
    case 4:
      p->attacks |= ATTACK_APPEAR;
      SetMotion(s, FINAL(16));
      gOverworld.state[1] = 1;
      REMOVE(51);
      START(55, BG_PAL);
      START(52, OBJ_PAL);
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      STEP(55);
      if (STEP(52) == 3) {
        s->mode[2]++;
        REMOVE(55);
        REMOVE(52);
      }
      break;
    case 6:
      PlaySound(SE_Z2_HARPUIA_EX);
      createBody(s, 0);
      SetMotion(s, FINAL(17));
      p->timer = 300;
      s->mode[2]++;
      FALLTHROUGH;
    case 7:
      bob(p);
      UpdateEntityAnim(s);
      if (p->timer != 0) {
        p->timer--;
      } else if (!(gStageRun.vm.active & VM_ACTIVE)) {
        setMode(s, 9);
      }
      if (p->timer != 270) return;
      PlaySound(SE_Z2_FINAL_CALL);
      createTentacle(s, 0);
      createTentacle(s, 1);
      createBody(s, 1);
      return;
  }
  UpdateEntityAnim(s);
}

// 0x0806160c: picks the next attack; a warp after five, or at once if Zero strays from the middle
static void Final_Decide(struct ElpizoFinal* p) {
  // 0x0833d519
  static const u8 sFarAttacks[4] = {2, 4, 5, 7};
  struct Entity* s = &p->s;
  bool8 far;
  u8 next;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sBody[0]);
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) {
    far = (u32)((pZero2->s).coord.x - p->homeX + 0xD800) > 0x1B000;
    if (++p->rests > 4 || (far && p->spot == 1)) {
      p->rests = 0;
      setMode(s, 8);
    } else {
      do {
        next = far ? sFarAttacks[RANDOM(RNG_0202f388) & 3] : RANDOM(RNG_0202f388) % 6 + 2;
      } while (again(p, next));
      setMode(s, next);
    }
  }
  bob(p);
}

// 0x08061728, 0x080617b4: the top, then the rock
static void Final_Call(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  u32 bit = s->mode[1] == 2 ? ATTACK_TOP : ATTACK_PILLAR;
  Coords32 at;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_FINAL_CALL);
    p->attacks |= bit;
    p->timer = 0;
    s->mode[2]++;
  }
  if (++p->timer == 2) p->attacks &= ~bit;
  if (bit == ATTACK_TOP) {
    if (p->timer == 110) {
      at.x = s->coord.x;
      at.y = s->coord.y + PIXEL(6);
      createTop(s, &at);
    }
    if (p->timer == 400) setMode(s, 1);
  } else {
    if (p->timer == 100) createRock(s);
    if (p->timer == 800) setMode(s, 1);
  }
  UpdateEntityAnim(s);
}

// 0x0806182c: the claws, in four steps
static void Final_Claws(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_FINAL_CALL);
    p->attacks |= ATTACK_CLAWS;
    p->attacks &= ~(ATTACK_CLAWS2 | ATTACK_CLAWS3 | ATTACK_CLAWS4);
    p->timer = 0;
    s->mode[2]++;
  }
  p->timer++;
  if (p->timer == 2) p->attacks &= ~ATTACK_CLAWS;
  if (p->timer == 120) p->attacks |= ATTACK_CLAWS2;
  if (p->timer == 200) p->attacks |= ATTACK_CLAWS3;
  if (p->timer == 370) p->attacks |= ATTACK_CLAWS4;
  if (p->timer == 440) setMode(s, 1);
  UpdateEntityAnim(s);
}

// 0x080618e0, 0x08061944: the claws sweep for 300 frames
static void Final_Sweep(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  u32 bit = s->mode[1] == 5 ? ATTACK_SWEEP : ATTACK_SWEEP2;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_FINAL_CHARGE);
    p->attacks |= bit;
    p->timer = 300;
    s->mode[2]++;
  }
  if (--p->timer == 0) {
    p->attacks &= ~bit;
    setMode(s, 1);
  }
  UpdateEntityAnim(s);
}

// 0x08061be4: four orbs, one a corner in random order, twice
static void Final_Orbs(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  u8 n;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_FINAL_ORBS);
      s->work[2] = 15;
      s->work[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      p->timer = 45;
      do {
        n = RANDOM(RNG_0202f388) & 3;
      } while (!((s->work[2] >> n) & 1));
      s->work[2] &= ~(1 << n);
      PlaySound(SE_Z2_DARK_ELF_WAKE);
      createOrb(s, &s->coord, n);
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      if (--p->timer != 0) break;
      s->mode[2] = 1;
      if (s->work[2] != 0) break;
      s->work[2] = 15;
      if (++s->work[3] > 1) setMode(s, 1);
      break;
  }
  UpdateEntityAnim(s);
}

// 0x080619ac: flashes, fades out with the sky shown, and back in over another spot
static void Final_Warp(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_FINAL_FADE);
      SetDDP(&p->body, &sBody[2]);
      p->attacks |= ATTACK_WARP;
      p->timer = 30;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (--p->timer == 0) s->mode[2]++;
      break;
    case 2:
      START(56, BG_PAL);
      START(53, OBJ_PAL);
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      STEP(56);
      if (STEP(53) == 3) s->mode[2]++;
      break;
    case 4:
      s->flags &= ~DISPLAY;
      gOverworld.state[1] = 2;
      p->timer = 96;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      STEP(56);
      STEP(53);
      if (--p->timer == 32) gOverworld.state[1] = 0;
      if (p->timer == 0) s->mode[2]++;
      break;
    case 6:
      PlaySound(SE_Z2_FINAL_WARP);
      p->spot = (p->spot + 1 + (RANDOM(RNG_0202f388) & 1)) % 3;
      s->coord.x = p->homeX - PIXEL(120) + p->spot * PIXEL(120);
      gOverworld.state[1] = 3;
      p->timer = 64;
      s->mode[2]++;
      FALLTHROUGH;
    case 7:
      STEP(56);
      STEP(53);
      if (--p->timer == 0) s->mode[2]++;
      break;
    case 8:
      REMOVE(53);
      REMOVE(56);
      s->flags |= DISPLAY;
      START(57, BG_PAL);
      START(54, OBJ_PAL);
      s->mode[2]++;
      FALLTHROUGH;
    case 9:
      UpdateEntityAnim(s);
      STEP(57);
      if (STEP(54) != 3) break;
      REMOVE(54);
      REMOVE(57);
      p->attacks &= ~ATTACK_WARP;
      setMode(s, 1);
      break;
  }
}

// 0x08061cc4: rises 16 px to hang there
static void Final_Rise(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  s32 y;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sBody[0]);
    p->baseY -= PIXEL(16);
    p->bob = s->coord.y < p->baseY ? 0 : 128;
    s->mode[2]++;
  }
  y = s->coord.y - 128;
  if (y < p->baseY) y = s->coord.y + 128;
  s->coord.y = y;
  if ((u32)(p->baseY - y + 256) <= 511) {
    p->baseY = y;
    setMode(s, 1);
  }
  UpdateEntityAnim(s);
}

typedef void (*FinalFunc)(struct ElpizoFinal*);

// 0x0833d490
static const FinalFunc sStates[10] = {
    Final_Appear, Final_Decide, Final_Call, Final_Call, Final_Claws,
    Final_Sweep,  Final_Sweep,  Final_Orbs, Final_Warp, Final_Rise,
};

// 0x080610bc
static void Final_Init(struct ElpizoFinal* p) {
  // 0x0833d518
  static const u8 sModes[5] = {0, 2, 4, 5, 7};
  struct Entity* s = &p->s;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sModes[s->work[0]];
  s->flags |= FLIPABLE;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->flags |= DISPLAY;
  ResetBossBody((struct Boss*)p, sBody, 96);
  (p->body).fn = NULL;
  p->baseY = s->coord.y;
  p->bob = 0;
  p->attacks = 0;
  p->last = 0xFF;
  p->repeats = 0;
  p->rests = 0;
  p->homeX = s->coord.x;
  p->floorY = FUN_08009f6c(s->coord.x, s->coord.y);
  p->spot = 1;
  ApLoadSheet(&sFxSheet);
  ApLoadSheet(&sPartsSheet);
  Final_Update(p);
}

// 0x08061200
static void Final_Update(struct ElpizoFinal* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Final_Die(p);
    return;
  }
  sStates[(p->s).mode[1]](p);
}

// 0x0806127c: sinks out of sight in smoke
static void Final_Die(struct ElpizoFinal* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetMotion(s, FINAL(18));
      if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
        gStageRun.missionStatus &= ~MISSION_STAY;
        gStageRun.missionStatus |= MISSION_SUCCESS;
      }
      s->work[2] = 80;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[2] == 0) s->mode[1]++;
      UpdateEntityAnim(s);
      break;
    case 2:
      s->work[2] = 240;
      s->mode[1]++;
      FALLTHROUGH;
    case 3:
      if ((--s->work[2] & 7) == 0) smoke(s, FALSE);
      if (s->work[2] % 24 == 0) smoke(s, TRUE);
      if (s->work[2] % 20 == 0) PlaySound(SE_Z2_TANK_EXPLODE);
      s->coord.y += 32;
      if (s->work[2] != 0) break;
      gStageRun.vm.active |= VM_FLAG1;
      s->mode[1]++;
      break;
    case 4:
      s->coord.y += 32;
      if ((--s->work[2] & 7) == 0) smoke(s, FALSE);
      if (s->work[2] % 24 == 0) smoke(s, TRUE);
      break;
  }
}

// 0x080613ac
static void Final_Disappear(struct ElpizoFinal* p) {
  gOverworld.state[1] = 0;
  DeleteBoss(&p->s);
}

// --------------------------------------------
/*
  Zero 2's enemy 57, the last form's body over it and its claws, in its frames
  work0: 0 body, 1 claws
*/

static void Body_Init(struct Enemy* p);
static void Body_Update(struct Enemy* p);
static void Body_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2ElpizoFinalBodyRoutine = {
    [ENTITY_INIT] =      Body_Init,
    [ENTITY_UPDATE] =    Body_Update,
    [ENTITY_DIE] =       Body_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

#define CLAWS_STEP (p->buffer[2])  // 0xB6: 2 top, 4 pillars, 8 claws

#define BOSS ((struct ElpizoFinal*)s->unk_28)

// 0x080868c0, 0x08086864
static struct Entity* createBody(struct Entity* boss, u8 kind) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(&p->s, ENEMY_Z2_ELPIZO_FINAL_BODY);
    (p->s).work[0] = kind;
    (p->s).unk_28 = boss;
    CLAWS_STEP = 0;
  }
  return &p->s;
}

static void follow(struct Entity* s) { s->coord = s->unk_28->coord; }

static void show(struct Entity* s) {
  s->flags |= DISPLAY;
  s->flags2 |= 16;
  s->invincibleID = s->unk_28->invincibleID;
  ResetDynamicMotion(s);
}

// 0x08086a90: body forms
static void Body_Form(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    show(s);
    SetMotion(s, FINAL(1));
    s->mode[2]++;
  }
  follow(s);
  FUN_0801779c(s);
  if (animEnded(s)) setMode(s, 1);
}

// 0x08086af4
static void Body_Hang(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FINAL(3));
    s->mode[2]++;
  }
  follow(s);
  FUN_0801779c(s);
  if (BOSS->attacks & ATTACK_WARP) setMode(s, 9);
}

// 0x08086b44: claws spread
static void Claws_Spread(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    show(s);
    s->renderPrio = 17;
    SetMotion(s, FINAL(20));
    s->mode[2]++;
  }
  follow(s);
  FUN_0801779c(s);
  if (animEnded(s)) setMode(s, 3);
}

// 0x08086bb0: claws wait for a call
static void Claws_Wait(struct Enemy* p) {
  struct Entity* s = &p->s;
  u32 attacks = BOSS->attacks;
  if (s->mode[2] == 0) {
    ResetDynamicMotion(s);
    SetMotion(s, FINAL(8));
    s->mode[2]++;
  }
  follow(s);
  FUN_0801779c(s);
  if (attacks & ATTACK_TOP) {
    CLAWS_STEP = (CLAWS_STEP | 2) & ~(4 | 8);
    setMode(s, 4);
  }
  if (attacks & ATTACK_PILLAR) {
    CLAWS_STEP = (CLAWS_STEP | 4) & ~(8 | 2);
    setMode(s, 4);
  }
  if (attacks & ATTACK_CLAWS) {
    CLAWS_STEP = (CLAWS_STEP | 8) & ~(4 | 2);
    setMode(s, 4);
  }
  if (attacks & (ATTACK_SWEEP | ATTACK_SWEEP2)) setMode(s, 7);
  if (attacks & ATTACK_WARP) setMode(s, 10);
}

// 0x08086c88: raise, cast, lower
static void Claws_Cast(struct Enemy* p) {
  struct Entity* s = &p->s;
  follow(s);
  switch (s->mode[2]) {
    case 0:
      s->work[2] = (CLAWS_STEP & 8) ? 1 : 100;
      s->mode[2]++;
      break;
    case 2:
      SetMotion(s, FINAL(12));
      s->work[2] = (CLAWS_STEP & 4) ? 70 : 30;
      s->mode[2]++;
      break;
    case 4:
      SetMotion(s, FINAL(13));
      s->work[2] = 70;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      if (--s->work[2] == 0) {
        if (CLAWS_STEP & 2) s->mode[1] = 3;
        if (CLAWS_STEP & 4) s->mode[1] = 5;
        if (CLAWS_STEP & 8) s->mode[1] = 6;
        s->mode[2] = 0;
      }
      FUN_0801779c(s);
      return;
  }
  if (--s->work[2] == 0) s->mode[2]++;
  FUN_0801779c(s);
}

// 0x08086d7c: held up while the pillars stand
static void Claws_Hold(struct Enemy* p) {
  struct Entity* s = &p->s;
  follow(s);
  if (s->mode[2] == 0) {
    SetMotion(s, FINAL(14));
    s->unk_coord.x = 560;
    s->mode[2]++;
  }
  if (--s->unk_coord.x == 0) setMode(s, 3);
  FUN_0801779c(s);
}

// 0x08086dcc: the claws' own four steps
static void Claws_Strike(struct Enemy* p) {
  // 0x08086de4
  static const u8 sAnims[5] = {8, 22, 23, 8, 10};
  static const u8 sTimes[5] = {10, 70, 70, 60, 60};
  struct Entity* s = &p->s;
  u8 step = s->mode[2] >> 1;
  if ((s->mode[2] & 1) == 0) {
    SetMotion(s, FINAL(sAnims[step]));
    s->work[2] = sTimes[step];
    s->mode[2]++;
  }
  FUN_0801779c(s);
  if (--s->work[2] != 0) return;
  if (step == 4) {
    setMode(s, 3);
  } else {
    s->mode[2]++;
  }
}

// 0x08086ea8: sweep; three swings, then on ATTACK_SWEEP fire to both sides, on ATTACK_SWEEP2 pillars
static void Claws_Sweep(struct Enemy* p) {
  // 0x08341582, 0x0834158a
  static const u8 sAnims[4] = {9, 10, 9, 11};
  static const u8 sLoops[4] = {1, 8, 1, 46};
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = BOSS;
  Coords32 at;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->work[3] = 0;
      SetMotion(s, FINAL(sAnims[s->work[2]]));
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      FUN_0801779c(s);
      if ((u8)((s->motion).state - ANIM_END) > 1) break;
      if (++s->work[3] < sLoops[s->work[2]]) {
        if (!(boss->attacks & ATTACK_SWEEP2) || s->work[2] != 3 || s->work[3] <= 22) break;
      }
      if (++s->work[2] == 3) {
        if (boss->attacks & ATTACK_SWEEP) {
          at.x = s->coord.x - PIXEL(29);
          at.y = s->coord.y + PIXEL(11);
          createFlame(&boss->s, &at, 0);
          at.x = s->coord.x - PIXEL(44);
          at.y = boss->floorY;
          createBurst(&boss->s, &at);
          at.x = s->coord.x + PIXEL(29);
          at.y = s->coord.y + PIXEL(11);
          createFlame(&boss->s, &at, 1);
          at.x = s->coord.x + PIXEL(44);
          at.y = boss->floorY;
          createBurst(&boss->s, &at);
        } else {
          at.x = s->coord.x - PIXEL(29);
          at.y = s->coord.y + PIXEL(11);
          createBolt(&boss->s, &at, 0);
          at.x = s->coord.x - PIXEL(44);
          at.y = boss->floorY;
          createWall(&boss->s, &at, 0);
          at.x = s->coord.x + PIXEL(29);
          at.y = s->coord.y + PIXEL(11);
          createBolt(&boss->s, &at, 1);
          at.x = s->coord.x + PIXEL(44);
          at.y = boss->floorY;
          createWall(&boss->s, &at, 1);
        }
        PlaySound(SE_Z2_FINAL_CLAWS);
      }
      if (s->work[2] <= 3) {
        s->mode[2] = 1;
      } else if (boss->attacks & ATTACK_SWEEP2) {
        setMode(s, 8);
      } else {
        s->mode[2]++;
      }
      break;
    case 3:
      SetMotion(s, FINAL(8));
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      FUN_0801779c(s);
      if (boss->attacks & ATTACK_SWEEP) break;
      s->mode[1] = 3;
      s->mode[2] = 1;
      break;
  }
}

// 0x080870c8: ATTACK_SWEEP2's last swings
static void Claws_Sweep2(struct Enemy* p) {
  // 0x0834158e, 0x08341594
  static const u8 sAnims[3] = {8, 13, 12};
  static const u8 sLoops[3] = {1, 8, 4};
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->work[3] = 0;
      SetMotion(s, FINAL(sAnims[s->work[2]]));
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      FUN_0801779c(s);
      if ((u8)((s->motion).state - ANIM_END) > 1) break;
      if (++s->work[3] < sLoops[s->work[2]]) break;
      s->mode[2] = ++s->work[2] > 2 ? 3 : 1;
      break;
    case 3:
      SetMotion(s, FINAL(8));
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      FUN_0801779c(s);
      if (BOSS->attacks & ATTACK_SWEEP2) break;
      s->mode[1] = 3;
      s->mode[2] = 1;
      break;
  }
}

// 0x0808719c, 0x0808721c: fade with the warp, back on its end
static void Body_Warp(struct Enemy* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      ResetDynamicMotion(s);
      SetMotion(s, FINAL(s->work[0] == 0 ? 4 : 21));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      follow(s);
      FUN_0801779c(s);
      if (animEnded(s)) s->mode[2]++;
      break;
    case 2:
      s->flags &= ~DISPLAY;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (BOSS->attacks & ATTACK_WARP) break;
      setMode(s, s->work[0] == 0 ? 0 : 2);
      break;
  }
}

// 0x0834154c
static const EnemyFunc sBodyStates[11] = {
    Body_Form,  Body_Hang,   Claws_Spread, Claws_Wait,   Claws_Cast,   Claws_Hold,
    Claws_Strike, Claws_Sweep, Claws_Sweep2, Body_Warp, Body_Warp,
};

// 0x08086914
static void Body_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->work[0] == 0 ? 0 : 2;
  s->flags |= FLIPABLE | DISPLAY;
  InitNonAffineMotion(s);
  Body_Update(p);
}

// 0x0808695c
static void Body_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->unk_28->mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = s->work[0] == 0 ? 1 : 0;
    Body_Die(p);
    return;
  }
  sBodyStates[s->mode[1]](p);
}

// 0x080869e8, 0x08086a3c: falls with it
static void Body_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, FINAL(s->mode[1] == 0 ? 15 : 2));
    s->mode[2]++;
  }
  follow(s);
  if (s->mode[1] == 0) {
    FUN_0801779c(s);
  } else {
    UpdateEntityAnim(s);
  }
  if (s->unk_28->mode[0] == ENTITY_EXIT) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's projectile 45, the last form's fire
  work0: 0 a tentacle's head, 1 one of its two links, 2 flames thrown, 3 a flame, 4 the top, 5 sparks thrown,
         6 a spark, 7 a burst, 8 an orb's shot
  side: 0 left, 1 right
  links: 1 drawn in, 2 throws flames, 4 sparks, 8 reaches along the floor, 16 low
  z: depth, the tentacle turning in front of the last form or behind
*/

struct Fire {
  OBJECT_HDR;
  u8 angle;  // 0xB4
  u8 side;   // 0xB5
  u8 links;  // 0xB6
  u8 _b7;
  s32 z;     // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct Fire) == sizeof(struct Projectile));

#define PARTS(n) MOTION(AP_SHEET_Z2_ELPIZO_FINAL, (n))
#define FX(n) MOTION(AP_SHEET_Z2_ELPIZO_FINAL_FX, (n))

static void Fire_Init(struct Fire* p);
static void Fire_Update(struct Fire* p);

// clang-format off
const ProjectileRoutine gApZ2ElpizoFinalFireRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Fire_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Fire_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x0834510c, 0x0834513c, 0x0834519c, 0x083451cc, 0x083451fc
static const struct Collision sFireNone[1] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
static const struct Collision sHead[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x1400, 0x1800}},
};
static const struct Collision sTop[1] = {
    {DDP, FACTION_ENEMY, 0, 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x2400, 0x2400}},
};
static const struct Collision sBurst[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0x2000, 0x2000}},
};
static const struct Collision sFlame[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xe00, 0xe00}},
};
// clang-format on

static struct Entity* createSpark(const Coords32* at, u8 kind);
static struct Entity* createGlint(const Coords32* at, u8 priority);

static struct Fire* allocFire(struct Entity* boss, const Coords32* at, u8 kind, u8 side) {
  struct Fire* p = (struct Fire*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(&p->s, PROJECTILE_Z2_ELPIZO_FINAL_FIRE);
    (p->s).coord = *at;
    (p->s).work[0] = kind;
    (p->s).unk_28 = boss;
    p->side = side;
  }
  return p;
}

// 0x080a6a78
static struct Entity* createTop(struct Entity* boss, const Coords32* at) {
  return &allocFire(boss, at, 4, 0)->s;
}

// 0x080a6b28
static struct Entity* createFlame(struct Entity* boss, const Coords32* at, u8 side) {
  return &allocFire(boss, at, 2, side)->s;
}

// 0x080a6a1c
static struct Entity* createBolt(struct Entity* boss, const Coords32* at, u8 side) {
  return &allocFire(boss, at, 5, side)->s;
}

// 0x080a6c0c, its two links 0x080a6b84
static struct Entity* createTentacle(struct Entity* boss, u8 side) {
  struct Fire* head = allocFire(boss, &boss->coord, 0, side);
  struct Fire* prev = head;
  struct Fire* q;
  u8 i;
  if (head == NULL) return NULL;
  head->z = PIXEL(64);
  (head->s).unk_coord = boss->coord;
  head->links = 0;
  (head->s).flags |= COLLIDABLE;
  INIT_BODY(head, sHead, 0, NULL);
  head->angle = 128;
  for (i = 0; i < 2; i++) {
    q = (struct Fire*)AllocEntityFirst(gProjectileHeaderPtr);
    if (q == NULL) continue;
    INIT_PROJECTILE_ROUTINE(&q->s, PROJECTILE_Z2_ELPIZO_FINAL_FIRE);
    (q->s).coord.x = boss->coord.x;
    q->z = PIXEL(64);
    (q->s).work[0] = 1;
    (q->s).work[1] = i == 1;
    (q->s).unk_28 = &prev->s;
    (q->s).unk_2c = boss;
    q->side = prev->side;
    q->links = 0;
    prev = q;
  }
  return &head->s;
}

static void fireDie(struct Fire* p) {
  struct Entity* s = &p->s;
  s->flags &= ~(DISPLAY | COLLIDABLE);
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

static bool8 bossGone(struct Entity* boss) { return boss->mode[0] > ENTITY_UPDATE; }

static void glintAndDie(struct Fire* p, u8 priority) {
  createGlint(&(p->s).coord, priority);
  fireDie(p);
}

// 0x080a6d28: the head on its circle round the last form, in front or behind
static void placeHead(struct Fire* p) {
  // 0x08345266
  static const u8 sFrames[6] = {0, 1, 2, 3, 4, 5};
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if ((s8)(p->angle - 64) >= 0) {
    s->palID = 1;
    (s->spr).oam.priority = 3;
  } else {
    s->palID = 0;
    (s->spr).oam.priority = 1;
  }
  if (p->side) {
    SetMotion(s, PARTS(sFrames[(u8)(0x115 - p->angle) / 43]));
  } else {
    SetMotion(s, PARTS(sFrames[(u8)(p->angle + 21) / 43]));
  }
  UpdateEntityAnim(s);
  s->coord.x = boss->coord.x - SIN(p->angle) * 96;
  s->coord.y = boss->coord.y + COS(p->angle) * 8;
  p->z = -COS(p->angle) * 64;
}

static void headBody(struct Fire* p) { SetDDP(&p->body, p->z > 0 ? sFireNone : sHead); }

static void faceSide(struct Fire* p, bool8 flip) {
  struct Entity* s = &p->s;
  SET_XFLIP(s, flip);
}

// 0x080a6e18: one turn round it
static void Head_Turn(struct Fire* p) {
  struct Entity* s = &p->s;
  if (bossGone(s->unk_28)) {
    glintAndDie(p, p->z < 0 ? 3 : 2);
    return;
  }
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sHead);
    s->flags |= DISPLAY;
    faceSide(p, p->side);
    p->z = PIXEL(64);
    s->mode[2]++;
  }
  p->angle -= p->side * 2 - 1;
  placeHead(p);
  headBody(p);
  if (p->angle == 128) setMode(s, 2);
}

// 0x080a6f3c: a link, held within its length of the one before
static void Link_Follow(struct Fire* p) {
  // 0x08345272
  static const u8 sFrames[6] = {6, 7, 8, 9, 10, 11};
  struct Entity* s = &p->s;
  struct Fire* prev = (struct Fire*)s->unk_28;
  struct Entity* boss = s->unk_2c;
  s32 dx, dz, len;
  u16 d;
  u8 angle, kind;
  if (bossGone(boss)) {
    glintAndDie(p, p->z < 0 ? 3 : 2);
    return;
  }
  if (s->mode[2] == 0) {
    SET_XFLIP(s, FALSE);
    s->flags |= DISPLAY;
    s->work[2] = 0;
    s->unk_coord.x = PIXEL(16);
    s->mode[2]++;
  }
  if (prev->links & 1) {
    p->links |= 1;
    s->unk_coord.x = s->unk_coord.x * 7 / 8;
    if ((u32)(s->unk_coord.x + 256) <= 0x1FF) setMode(s, 3);
  }
  dx = (prev->s).coord.x - s->coord.x;
  dz = prev->z - p->z;
  d = Sqrt(dx * dx + dz * dz);
  len = s->unk_coord.x;
  if (d > len) {
    dx = (dx << 8) / d;
    dz = (dz << 8) / d;
    s->coord.x = (prev->s).coord.x - dx * len / 256;
    p->z = prev->z - dz * len / 256;
  }
  s->coord.y = boss->coord.y - p->z / 8;
  angle = ArcTan2((s16)-dx, (s16)dz) >> 8;
  if (p->z > 0) {
    s->palID = 1;
    (s->spr).oam.priority = 3;
    kind = 3;
  } else {
    s->palID = 0;
    (s->spr).oam.priority = 1;
    kind = 1;
  }
  SetMotion(s, PARTS(sFrames[(u8)(angle + 21) / 43]));
  UpdateEntityAnim(s);
  if (s->work[1] != 0 && ++s->work[2] > 6) {
    createGlint(&s->coord, kind);
    s->work[2] = 0;
  }
}

// 0x080a7158: waits for a call
static void Head_Wait(struct Fire* p) {
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  if (bossGone(&boss->s)) {
    fireDie(p);
    return;
  }
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sFireNone);
    p->links |= 1;
    s->flags &= ~DISPLAY;
    s->mode[2]++;
  }
  if (boss->attacks & ATTACK_TOP) {
    p->links = (p->links | 2) & ~(4 | 1);
    setMode(s, 4);
  }
  if (boss->attacks & ATTACK_PILLAR) {
    p->links = (p->links | 4) & ~(2 | 1);
    setMode(s, 4);
  }
  if (boss->attacks & ATTACK_CLAWS) {
    p->links = (p->links | 8) & ~(4 | 2);
    setMode(s, 12);
  }
  s->coord.x = (boss->s).coord.x;
  p->z = PIXEL(64);
}

// 0x080a725c: a link hidden, until the head comes back out
static void Link_Wait(struct Fire* p) {
  struct Entity* s = &p->s;
  struct Fire* prev = (struct Fire*)s->unk_28;
  struct Entity* boss = s->unk_2c;
  if (bossGone(boss)) {
    fireDie(p);
    return;
  }
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    s->mode[2]++;
  }
  if (!(prev->links & 1)) {
    p->links &= ~1;
    if (prev->links & 8) {
      p->links = (prev->links & 16) ? (p->links | 16) : (p->links & ~16);
      p->links |= 8;
      s->mode[1] = 13;
    } else {
      p->links &= ~8;
      s->mode[1] = 1;
    }
    s->mode[2] = 0;
  }
  s->coord.x = boss->coord.x;
  p->z = PIXEL(64);
}

// 0x080a7328: half a turn to throw from the side, then back round
static void Head_Throw(struct Fire* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  Coords32 at;
  if (bossGone(boss)) {
    glintAndDie(p, p->z < 0 ? 3 : 2);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, sHead);
      s->flags |= DISPLAY;
      p->angle = 128;
      p->z = PIXEL(64);
      faceSide(p, p->side);
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      p->angle -= p->side * 4 - 2;
      placeHead(p);
      headBody(p);
      if (p->angle != (u8)(228 - p->side * 200)) break;
      at.x = s->coord.x - PIXEL(16 - p->side * 32);
      at.y = s->coord.y;
      PlaySound(SE_Z2_FINAL_CLAWS);
      if (p->links & 2) {
        createFlame(boss, &at, p->side);
      } else {
        createBolt(boss, &at, p->side);
      }
      s->mode[2]++;
      break;
    case 2:
      p->links |= 1;
      s->work[2] = 80;
      SetMotion(s, PARTS(0));
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (--s->work[2] == 0) {
        p->links &= ~1;
        setMode(s, 0);
      }
      UpdateEntityAnim(s);
      break;
  }
}

static bool8 playSteps(struct Entity* s, const u16* anims, const u8* loops, u8 last) {
  switch (s->mode[2]) {
    case 1:
      SetMotion(s, anims[s->work[2]]);
      s->work[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      UpdateEntityAnim(s);
      if ((u8)((s->motion).state - ANIM_END) > 1) break;
      if (++s->work[3] < loops[s->work[2]]) break;
      if (++s->work[2] == last) return TRUE;
      s->mode[2] = 1;
      break;
  }
  return FALSE;
}

// 0x080a74f4: flames thrown, 8 of them, 24 in a sweep, 6 frames apart
static void Flames_Throw(struct Fire* p) {
  // 0x0834527e, 0x08345284
  static const u16 sAnims[3] = {FX(2), FX(3), FX(4)};
  static const u8 sLoops[3] = {1, 3, 1};
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  if (bossGone(&boss->s)) {
    fireDie(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      (s->spr).oam.priority = 1;
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
    case 2:
      if (playSteps(s, sAnims, sLoops, 3)) s->mode[2] = 3;
      break;
    case 3:
      s->flags &= ~DISPLAY;
      s->work[2] = s->work[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      if (s->work[2] == 0) {
        s->work[2] = 6;
        allocFire(&boss->s, &s->coord, 3, p->side);
        s->work[3]++;
        if ((boss->attacks & ATTACK_SWEEP) ? s->work[3] > 23 : s->work[3] > 7) {
          fireDie(p);
          return;
        }
      }
      s->work[2]--;
      break;
  }
}

// 0x080a7680, 0x080a7af0: a flame or a spark; in a sweep it drops to the floor, else it flies 16 frames
static void Fire_Fly(struct Fire* p) {
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  bool8 spark = s->work[0] == 6;
  u32 sweep = spark ? ATTACK_SWEEP2 : ATTACK_SWEEP;
  Coords32 at;
  s32 push;
  if (s->mode[2] == 0) {
    SetMotion(s, spark ? PARTS(18) : FX(0));
    if (boss->attacks & sweep) {
      s->flags |= COLLIDABLE;
      INIT_BODY(p, sFlame, 0, NULL);
      s->d.x = -0x100 + p->side * 0x200;
      s->d.y = 0x480;
    } else {
      s->d.x = -0x380 + p->side * 0x700;
      s->d.y = 0;
    }
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (s->work[2] != 0) {
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
    if (boss->attacks & sweep) {
      push = PushoutToUp1(s->coord.x, s->coord.y);
      if (push < 0) {
        s->coord.y += push;
        if (spark) {
          at.x = s->coord.x - PIXEL(4) + (RANDOM(RNG_0202f388) & 0x7FF);
          at.y = s->coord.y;
          createSpark(&at, 6);
        }
        fireDie(p);
        return;
      }
    } else if (++s->work[2] > 15) {
      if (spark && p->side) {
        at.x = s->coord.x - PIXEL(7);
        at.y = s->coord.y;
        createSpark(&at, 2);
      }
      fireDie(p);
      return;
    }
  }
  UpdateEntityAnim(s);
  if ((!spark || s->work[2] == 0) && (s->motion).state == (spark ? ANIM_NEXT_GOTO : ANIM_END)) {
    SetMotion(s, spark ? PARTS(19) : FX(1));
    UpdateEntityAnim(s);
    s->work[2] = 1;
  }
}

// 0x080a77c0, 0x080a78d0: the top winds up, then spirals out from where it stands
static void Top_Spin(struct Fire* p) {
  // 0x08345288, 0x0834528e
  static const u16 sAnims[3] = {FX(3), FX(5), FX(6)};
  static const u8 sLoops[3] = {2, 1, 2};
  struct Entity* s = &p->s;
  if (s->mode[1] == 7) {
    if (bossGone(s->unk_28)) {
      fireDie(p);
      return;
    }
    if (s->mode[2] == 0) {
      (s->spr).oam.priority = 1;
      s->work[2] = 0;
      s->mode[2]++;
    }
    if (s->mode[2] == 1) {
      SetMotion(s, sAnims[s->work[2]]);
      s->work[3] = 0;
      s->mode[2]++;
    }
    UpdateEntityAnim(s);
    if ((u8)((s->motion).state - ANIM_END) > 1 || ++s->work[3] < sLoops[s->work[2]]) return;
    if (++s->work[2] == 2) {
      s->flags |= COLLIDABLE;
      INIT_BODY(p, sTop, 0, NULL);
    }
    if (s->work[2] == 3) {
      setMode(s, 8);
    } else {
      s->mode[2] = 1;
    }
    return;
  }
  if (s->mode[2] == 0) {
    s->unk_coord = s->coord;
    p->angle = 0;
    s->d.x = 0;
    s->mode[2]++;
  }
  s->coord.x = s->unk_coord.x + COS(p->angle) * s->d.x / 256;
  s->coord.y = s->unk_coord.y + SIN(p->angle) * s->d.x / 256;
  p->angle += 3;
  if (p->angle <= 2) PlaySound(SE_Z2_FINAL_TOP);
  s->d.x += 64;
  if (s->d.x > PIXEL(120) && Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(32)) fireDie(p);
  UpdateEntityAnim(s);
}

// 0x080a79c0: sparks thrown, 13 of them, 6 frames apart
static void Sparks_Throw(struct Fire* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (bossGone(boss)) {
    fireDie(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      (s->spr).oam.priority = 1;
      SetMotion(s, PARTS(17));
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if ((s->motion).state == ANIM_NEXT_GOTO && ++s->work[2] > 2) s->mode[2]++;
      break;
    case 2:
      s->flags &= ~DISPLAY;
      s->work[2] = s->work[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (s->work[2] == 0) {
        s->work[2] = 6;
        allocFire(boss, &s->coord, 6, p->side);
        if (++s->work[3] > 12) {
          fireDie(p);
          return;
        }
      }
      s->work[2]--;
      break;
  }
}

// 0x080a7ca8: a burst, hurting while it plays
static void Fire_Burst(struct Fire* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= COLLIDABLE;
    INIT_BODY(p, sBurst, 0, NULL);
    SetMotion(s, MOTION(SM000_BATTLE_EFFECT, 1));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((s->motion).state == ANIM_END) fireDie(p);
}

// 0x080a7d38: waits, then reaches along the floor to the far side
static void Head_Reach(struct Fire* p) {
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  bool8 stop;
  if (bossGone(&boss->s)) {
    glintAndDie(p, 3);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 50;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      p->links &= ~(1 | 16);
      s->palID = 1;
      SetDDP(&p->body, sFireNone);
      SetMotion(s, PARTS(0));
      s->d.x = 0;
      s->flags |= DISPLAY;
      p->z = 0;
      s->coord.y = (boss->s).coord.y;
      s->work[2] = 90;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      s->coord.x += s->d.x;
      if ((u32)(s->d.x + 0x500) <= 0x9FF) s->d.x += 32 - p->side * 64;
      s->work[2]--;
      if (p->side == 0) {
        stop = s->coord.x > boss->homeX + PIXEL(272) || s->work[2] == 0;
      } else {
        stop = s->coord.x < boss->homeX - PIXEL(272) || s->work[2] == 0;
      }
      if (!stop) break;
      s->flags &= ~DISPLAY;
      SetDDP(&p->body, sFireNone);
      p->links |= 1;
      s->mode[2]++;
      break;
    case 4:
      if (boss->attacks & (p->side ? ATTACK_CLAWS2 : ATTACK_CLAWS3)) setMode(s, 14);
      break;
  }
}

// 0x080a7ee8: a link lying along the floor behind the head
static void Link_Reach(struct Fire* p) {
  struct Entity* s = &p->s;
  struct Fire* prev = (struct Fire*)s->unk_28;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_2c;
  s32 dx, len;
  u16 d;
  if (bossGone(&boss->s)) {
    glintAndDie(p, p->z < 0 ? 3 : 2);
    return;
  }
  if (s->mode[2] == 0) {
    faceSide(p, p->side);
    if (p->links & 16) {
      s->palID = 0;
      SetMotion(s, PARTS(6));
      (s->spr).oam.priority = 2;
    } else {
      s->palID = 1;
      SetMotion(s, PARTS(9));
      (s->spr).oam.priority = 3;
    }
    s->coord = (prev->s).coord;
    s->flags |= DISPLAY;
    s->work[2] = s->work[3] = 0;
    s->unk_coord.x = PIXEL(16);
    s->mode[2]++;
  }
  if (prev->links & 1) {
    p->links |= 1;
    if ((p->links & 16) || (boss->attacks & ATTACK_CLAWS4)) {
      s->unk_coord.x = s->unk_coord.x * 7 / 8;
      if ((u32)(s->unk_coord.x + 256) <= 0x1FF) setMode(s, 3);
    } else {
      setMode(s, 3);
    }
  }
  dx = (prev->s).coord.x - s->coord.x;
  d = Sqrt(dx * dx);
  len = s->unk_coord.x;
  if (d > len) s->coord.x = (prev->s).coord.x - (dx << 8) / d * len / 256;
  s->coord.y = (prev->s).coord.y;
  UpdateEntityAnim(s);
  s->work[3]++;
  if (s->work[1] != 0 && ++s->work[2] > 3) {
    createGlint(&s->coord, (p->links & 16) ? 2 : 3);
    s->work[2] = 0;
  }
}

// 0x080a80d4: in from the screen's edge low along the floor, pausing over Zero once
static void Head_Sweep(struct Fire* p) {
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  struct Entity* z = &pZero2->s;
  bool8 over, past;
  if (bossGone(&boss->s)) {
    glintAndDie(p, 2);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->palID = 0;
      p->links = (p->links | 16) & ~1;
      SetDDP(&p->body, sHead);
      (s->spr).oam.priority = 2;
      SetMotion(s, PARTS(0));
      s->d.x = -0x500 + p->side * 0xA00;
      faceSide(p, p->side);
      s->flags |= DISPLAY;
      p->z = 0;
      s->work[3] = 0;
      s->coord.x = gStageRun.vm.camera.viewport.x + (p->side ? -0x7800 : 0x77FF);
      s->coord.y = boss->floorY - PIXEL(34) + p->side * PIXEL(18);
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->coord.x += s->d.x;
      if (p->side) {
        over = s->coord.x > z->coord.x - PIXEL(48) && s->coord.x < z->coord.x;
        past = s->coord.x > boss->homeX + PIXEL(272);
      } else {
        over = s->coord.x < z->coord.x + PIXEL(48) && s->coord.x > z->coord.x;
        past = s->coord.x < boss->homeX - PIXEL(272);
      }
      if (z->coord.y == boss->floorY && over && s->work[3] == 0) {
        s->work[3] = 1;
        p->links |= 1;
        s->mode[2]++;
      }
      if (past) s->mode[2] = 4;
      break;
    case 2:
      s->work[2] = 30;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (--s->work[2] == 0) {
        p->links &= ~1;
        s->mode[2] = 1;
      }
      break;
    case 4:
      SetDDP(&p->body, sFireNone);
      p->links |= 1;
      s->flags &= ~DISPLAY;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      if (boss->attacks & ATTACK_CLAWS4) setMode(s, 15);
      return;
  }
  UpdateEntityAnim(s);
}

// 0x080a838c: back in from the edge to the last form
static void Head_Return(struct Fire* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s32 edge;
  if (bossGone(boss)) {
    glintAndDie(p, 3);
    return;
  }
  if (s->mode[2] == 0) {
    s->palID = 1;
    s->coord.y = boss->coord.y;
    p->links &= ~(16 | 1);
    SetDDP(&p->body, sHead);
    (s->spr).oam.priority = 3;
    SetMotion(s, PARTS(0));
    faceSide(p, p->side ^ 1);
    s->flags |= DISPLAY;
    s->d.x = PIXEL(3) - p->side * PIXEL(6);
    if (p->side) {
      edge = gStageRun.vm.camera.viewport.x + 0x77FF;
      s->coord.x = edge < boss->coord.x ? boss->coord.x : edge;
    } else {
      edge = gStageRun.vm.camera.viewport.x - 0x7800;
      s->coord.x = edge <= boss->coord.x ? edge : boss->coord.x;
    }
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  if ((u32)(s->coord.x - boss->coord.x + PIXEL(3)) <= PIXEL(6)) {
    p->links = (p->links | 1) & ~8;
    setMode(s, 2);
  }
  UpdateEntityAnim(s);
}

// 0x080a850c: a shot from one of the orbs, at Zero
static void Fire_Shot(struct Fire* p) {
  // 0x0834522c
  static const struct Collision sShot[1] = {
      {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, 0x0, 0xa00, 0xa00}},
  };
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  struct Entity* z = &pZero2->s;
  s32 dx, dy, d;
  if ((p->body).status & 4) {
    createSpark(&s->coord, 2);
    fireDie(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->flags |= COLLIDABLE;
      INIT_BODY(p, sShot, 0, NULL);
      SetMotion(s, PARTS(18));
      s->work[2] = 20;
      dx = (z->coord.x - s->coord.x) >> 8;
      dy = (z->coord.y - (s->coord.y + PIXEL(16))) >> 8;
      d = Sqrt(dx * dx + dy * dy) << 8;
      if (d != 0) {
        s->d.x = (dx << 16) / d * 0x380 / 256;
        s->d.y = (dy << 16) / d * 0x380 / 256;
      } else {
        s->d.x = 0x380;
        s->d.y = 0;
      }
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      break;
    case 2:
      SetMotion(s, PARTS(19));
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      UpdateEntityAnim(s);
      break;
  }
  if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
  createSpark(&s->coord, s->coord.y >= boss->floorY ? 6 : 2);
  fireDie(p);
}

typedef void (*FireFunc)(struct Fire*);

// 0x083450c8
static const FireFunc sFireStates[17] = {
    Head_Turn,  Link_Follow, Head_Wait,  Link_Wait,  Head_Throw, Flames_Throw, Fire_Fly,   Top_Spin,  Top_Spin,
    Sparks_Throw, Fire_Fly,  Fire_Burst, Head_Reach, Link_Reach,   Head_Sweep, Head_Return, Fire_Shot,
};

// 0x080a6ca8
static void Fire_Init(struct Fire* p) {
  // 0x0834525c
  static const u8 sModes[9] = {0, 1, 5, 6, 7, 9, 10, 11, 16};
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sModes[s->work[0]];
  s->flags |= FLIPABLE | DISPLAY;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  p->links = 0;
  Fire_Update(p);
}

// 0x080a6cf8
static void Fire_Update(struct Fire* p) { sFireStates[(p->s).mode[1]](p); }


// --------------------------------------------
/*
  Zero 2's solid 13, the last form's rocks
  work0: 0 the rock, 1 a seeker, 2 a wall
  work2: the wall's side
*/

struct Rock {
  OBJECT_HDR;
  u8 away;  // 0xB4, the wall slides out to the screen's edge, Zero being far from the last form
  u8 _b5[15];
};
static_assert(sizeof(struct Rock) == sizeof(struct Solid));

static void Rock_Init(struct Rock* p);
static void Rock_Update(struct Rock* p);
static void Rock_Die(struct Rock* p);

// clang-format off
const SolidRoutine gApZ2ElpizoFinalRockRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Rock_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Rock_Update,
    [ENTITY_DIE] =       (SolidFunc)Rock_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};

// 0x083491ec, 0x0834921c
static const struct Collision sRockBody[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0x0, -0x900, 0x1d00, 0x1000}},
};
static const struct Collision sSeeker[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x80, 0x00, 0x05, 0, 0, 1, 0x00000001, {0x0, 0x0, 0xe00, 0xe00}},
};
// 0x0834924c, 0x0834930c: by frame as the wall rises, then 0x083492dc, 0x0834939c as it slides
static const struct Collision sWallLeft[8] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, 0x0, 0xc00, 0x800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, -0x100, 0xc00, 0xd00}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, -0xa00, 0xc00, 0x1c00}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, -0x1700, 0xc00, 0x2300}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
static const struct Collision sWallRight[6] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0xc00, 0x100, 0xc00, 0x800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x0}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0xc00, -0x700, 0xc00, 0x1600}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
static const struct Collision sSlideLeft[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {0xc00, -0x1700, 0xc00, 0x2300}},
};
static const struct Collision sSlideRight[1] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0, 0, 0, 0x00000001, {-0xc00, -0x1000, 0xc00, 0x2300}},
};
// clang-format on

// 0x083493e8, 0x083493f0, 0x08349410
static const struct Rect sRockSize = {0, -0x1100, 0x2000, 0x1000};
static const struct Rect sWallSizes[4] = {
    {0, 0, 0xd00, 0x800}, {0, -0x300, 0xd00, 0x1000}, {0, -0xb00, 0xd00, 0x2000}, {0, -0x1300, 0xd00, 0x2d00}};

// 0x080cbe18
static struct Entity* createRock(struct Entity* boss) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_Z2_ELPIZO_FINAL_ROCK);
    p->renderPrio = 30;
    p->coord.x = boss->coord.x;
    p->coord.y = boss->coord.y + PIXEL(16);
    p->work[0] = 0;
    p->unk_28 = boss;
  }
  return p;
}

// 0x080cbd74
static struct Entity* createSeeker(struct Entity* boss, const Coords32* at) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_Z2_ELPIZO_FINAL_ROCK);
    p->renderPrio = 30;
    p->coord = *at;
    p->work[0] = 1;
    p->unk_28 = boss;
  }
  return p;
}

// 0x080cbd10
static struct Entity* createWall(struct Entity* boss, const Coords32* at, u8 side) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, SOLID_Z2_ELPIZO_FINAL_ROCK);
    p->renderPrio = 30;
    p->coord = *at;
    p->work[0] = 2;
    p->unk_28 = boss;
    p->work[2] = side;
  }
  return p;
}

static void rockDie(struct Rock* p) {
  struct Entity* s = &p->s;
  s->flags &= ~(DISPLAY | COLLIDABLE);
  EXIT_BODY(p);
  SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x080cbcb0: three puffs
static void puff(struct Entity* s, u8 n) {
  // 0x083493cc
  static const s8 sAt[2][3][2] = {{{-8, -32}, {0, -12}, {2, -44}}, {{8, -40}, {0, -14}, {-2, 2}}};
  Coords32 at;
  u8 i;
  PlaySound(SE_Z2_TANK_EXPLODE);
  for (i = 0; i < 3; i++) {
    at.x = s->coord.x + PIXEL(sAt[n][i][0]);
    at.y = s->coord.y + PIXEL(sAt[n][i][1]);
    CreateSmoke(1, &at);
  }
}

// 0x080a6970
static void createCrash(struct Entity* boss, const Coords32* at) { allocFire(boss, at, 7, 0); }

// 0x080cbdd0: the rock bursting on a wall
static void burst(struct Entity* s) {
  // 0x083493d8
  static const s8 sAt[6][2] = {{-16, -18}, {16, -24}, {8, -28}, {18, 10}, {10, 2}, {-10, 2}};
  Coords32 at;
  u8 i;
  PlaySound(SE_Z2_ICICLE_BREAK);
  for (i = 0; i < 6; i++) {
    at.x = s->coord.x + PIXEL(sAt[i][0]);
    at.y = s->coord.y + PIXEL(sAt[i][1]);
    createCrash(s->unk_28, &at);
  }
}

static void trail(struct Entity* s) {
  if (s->work[2] == 0) {
    s->work[2] = 7;
    createPuffs(&s->coord);
  }
  s->work[2]--;
}

// 0x080cbfac: blinks in, then forms
static void Rock_Form(struct Rock* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      (s->spr).oam.priority = 1;
      SetMotion(s, PARTS(26));
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (++s->work[2] & 2) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (s->work[2] == 25) s->mode[2]++;
      UpdateEntityAnim(s);
      break;
    case 2:
      s->flags |= DISPLAY;
      SetMotion(s, PARTS(27));
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      if (animEnded(s)) setMode(s, 1);
      break;
  }
}

static void solidOffZero(struct Entity* s) {
  const struct Rect* r = &gZeroRanges[pZero2->posture];
  s32 w = (r->w + s->size->w) / 2 + PIXEL(2);
  s32 h = (r->h + s->size->h) / 2 + PIXEL(2);
  s32 dx = (pZero2->s).coord.x + r->x - (s->coord.x + s->size->x);
  s32 dy = (pZero2->s).coord.y + r->y - (s->coord.y + s->size->y);
  if ((u32)(dx + w) < (u32)(w * 2) && dy > PIXEL(6) - h && dy < h) {
    s->flags2 &= ~ENTI_PHYSICS;
  } else {
    s->flags2 |= ENTI_PHYSICS;
  }
}

// 0x080cc060: drops, bouncing three times
static void Rock_Drop(struct Rock* p) {
  struct Entity* s = &p->s;
  s32 push;
  if (s->mode[2] == 0) {
    s->flags |= COLLIDABLE;
    INIT_BODY(p, sRockBody, 0, NULL);
    s->flags2 |= ENTI_PHYSICS;
    s->size = &sRockSize;
    s->physicsAttr = 0xA001;
    s->d.y = 0;
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->d.y > 0x700) s->d.y = 0x700;
  solidOffZero(s);
  push = PushoutToUp1(s->coord.x, s->coord.y);
  if (push >= 0) return;
  PlaySound(SE_Z2_SHIELD_GUARD_MACE_HIT);
  s->coord.y += push;
  s->d.y = -s->d.y >> 1;
  if (++s->work[2] > 3) setMode(s, 2);
}

// 0x080cc110: hangs from a point 24 px up and swings out and back twice
static void Rock_Swing(struct Rock* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetMotion(s, PARTS(29));
      s->work[2] = 28;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      trail(s);
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[2]++;
      return;
    case 2:
      s->unk_coord.x = s->coord.x;
      s->unk_coord.y = s->coord.y - PIXEL(24);
      s->work[2] = 0;
      SetMotion(s, PARTS(30));
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (++s->work[2] == 128) s->mode[2]++;
      break;
    case 4:
      s->unk_coord.y -= PIXEL(48);
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 6:
      s->unk_coord.y += PIXEL(48);
      s->work[2] = 128;
      s->mode[2]++;
      FALLTHROUGH;
    case 7:
      if (++s->work[2] == 0) setMode(s, 3);
      break;
  }
  s->d.x = s->unk_coord.x - SIN(s->work[2]) * 88 - s->coord.x;
  s->coord.x += s->d.x;
  s->d.y = s->unk_coord.y + COS(s->work[2]) * 24 - s->coord.y;
  s->coord.y += s->d.y;
  solidOffZero(s);
  UpdateEntityAnim(s);
}

// 0x080cc2c0: flies off on its last swing, bursting on a wall
static void Rock_Fly(struct Rock* p) {
  struct Entity* s = &p->s;
  s32 push;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  solidOffZero(s);
  if (s->d.x < 0) {
    push = PushoutToRight1(s->coord.x - PIXEL(40), s->coord.y);
    if (push > 0) {
      s->coord.x += push;
      burst(s);
      rockDie(p);
    }
  } else {
    push = PushoutToLeft1(s->coord.x + PIXEL(40), s->coord.y);
    if (push < 0) {
      s->coord.x += push;
      burst(s);
      rockDie(p);
    }
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(64)) rockDie(p);
  UpdateEntityAnim(s);
  trail(s);
}

// 0x080cc3c4: a seeker, homing for 255 frames then on its way; four hits break it
static void Seeker_Fly(struct Rock* p) {
  struct Entity* s = &p->s;
  struct Entity* z = &pZero2->s;
  s32 dx, dy;
  u16 d;
  if (((p->body).status & BODY_STATUS_DEAD) || bossGone(s->unk_28)) {
    createSpark(&s->coord, 5);
    rockDie(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->palID = 1;
      s->flags |= COLLIDABLE;
      INIT_BODY(p, sSeeker, 4, NULL);
      SetMotion(s, PARTS(15));
      s->work[2] = 255;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      dx = z->coord.x - s->coord.x;
      dy = z->coord.y - (s->coord.y + PIXEL(16));
      d = Sqrt(dx * dx + dy * dy);
      if (d > PIXEL(8)) {
        s->d.x = (dx << 8) / d;
        s->d.y = (dy << 8) / d;
        s->coord.x += s->d.x;
        s->coord.y += s->d.y;
      }
      UpdateEntityAnim(s);
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(32)) rockDie(p);
      UpdateEntityAnim(s);
      break;
  }
}

// 0x080cc554: a wall rising out of the floor beside the last form, a solid to stand on
static void Wall_Rise(struct Rock* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s8 frame;
  switch (s->mode[2]) {
    case 0:
      s->flags &= ~DISPLAY;
      s->work[3] = 110;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[3] == 0) s->mode[2]++;
      return;
    case 2:
      p->away = (u32)((pZero2->s).coord.x - boss->coord.x + PIXEL(44)) > 0x57FF;
      s->flags |= DISPLAY;
      s->work[3] = 60;
      SET_XFLIP(s, p->away);
      s->flags |= COLLIDABLE;
      if (s->work[2]) {
        INIT_BODY(p, sWallRight, 0, NULL);
        SetMotion(s, PARTS(24));
      } else {
        INIT_BODY(p, sWallLeft, 0, NULL);
        SetMotion(s, PARTS(22));
      }
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (--s->work[3] == 0) setMode(s, 6);
      UpdateEntityAnim(s);
      s->flags2 |= ENTI_PHYSICS;
      frame = (s->motion).cmdIdx;
      s->size = &sWallSizes[frame];
      s->physicsAttr = 1;
      SetDDP(&p->body, s->work[2] ? &sWallRight[frame * 2] : &sWallLeft[frame * 2]);
      break;
  }
}

// 0x080cc6f4: slides off to the edge or in at the last form, and breaks
static void Wall_Slide(struct Rock* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s32 push;
  if (s->mode[2] == 0) {
    s->flags2 |= ENTI_PHYSICS;
    s->size = &sWallSizes[3];
    s->physicsAttr = 0x2001;
    if (s->work[2]) {
      SetDDP(&p->body, sSlideRight);
      SetMotion(s, PARTS(25));
    } else {
      SetDDP(&p->body, sSlideLeft);
      SetMotion(s, PARTS(23));
    }
    s->d.x = 0;
    s->unk_coord.x = 32 - (p->away ^ s->work[2]) * 64;
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  if ((u32)(s->d.x + 0x400) <= 0x7FF) s->d.x += s->unk_coord.x;
  if (p->away) {
    if (s->d.x > 0) {
      push = PushoutToLeft1(s->coord.x + PIXEL(26), s->coord.y);
      if (push < 0) {
        s->coord.x += push;
        puff(s, 1);
        rockDie(p);
      }
    } else {
      push = PushoutToRight1(s->coord.x - PIXEL(26), s->coord.y);
      if (push > 0) {
        s->coord.x += push;
        puff(s, 1);
        rockDie(p);
      }
    }
  } else if (s->d.x < 0) {
    if (s->coord.x < boss->coord.x + PIXEL(8)) {
      s->coord.x = boss->coord.x + PIXEL(8);
      puff(s, 1);
      rockDie(p);
    }
  } else if (s->coord.x > boss->coord.x - PIXEL(8)) {
    s->coord.x = boss->coord.x - PIXEL(8);
    puff(s, 0);
    rockDie(p);
  }
  UpdateEntityAnim(s);
  if ((p->body).status & 36) s->flags2 &= ~ENTI_PHYSICS;
}

typedef void (*RockFunc)(struct Rock*);

// 0x083491c8
static const RockFunc sRockStates[7] = {Rock_Form, Rock_Drop, Rock_Swing, Rock_Fly, Seeker_Fly, Wall_Rise, Wall_Slide};

// 0x080cbe78
static void Rock_Init(struct Rock* p) {
  // 0x083493e4
  static const u8 sModes[3] = {0, 4, 5};
  struct Entity* s = &p->s;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sModes[s->work[0]];
  s->flags |= FLIPABLE | DISPLAY;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  Rock_Update(p);
}

// 0x080cbec0
static void Rock_Update(struct Rock* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 1 && bossGone(s->unk_28)) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Rock_Die(p);
    return;
  }
  sRockStates[s->mode[1]](p);
}

// 0x080cbf4c, 0x080cbf7c
static void Rock_Die(struct Rock* p) {
  puff(&p->s, 0);
  puff(&p->s, 1);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}


// --------------------------------------------
/*
  Zero 2's VFX 46, the last form's light
  work0: 0 a petal as it forms, 1..3 sparks, 4 the seekers' burst, 5 a seeker breaking, 6 a spark on the floor,
         7 an orb at a corner: a flash on the last form (work1 0) and the orb out there (1), which shoots
  work2: the petal or the corner, a glint's layer
*/

static void Light_Init(struct VFX* p);
static void Light_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2ElpizoFinalLightRoutine = {
    [ENTITY_INIT] =      Light_Init,
    [ENTITY_UPDATE] =    Light_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

static struct VFX* allocLight(const Coords32* at, u8 kind) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(&p->s, VFX_Z2_ELPIZO_FINAL_LIGHT);
    if (at != NULL) (p->s).coord = *at;
    (p->s).work[0] = kind;
  }
  return p;
}

// 0x080b9010, 0x080b914c, 0x080b8fc0
static struct Entity* createSpark(const Coords32* at, u8 kind) { return &allocLight(at, kind)->s; }

// 0x080b919c
static struct Entity* createGlint(const Coords32* at, u8 priority) {
  struct VFX* p = allocLight(at, 1);
  if (p == NULL) return NULL;
  (p->s).work[2] = priority;
  return &p->s;
}

// 0x080b90b4: a pair, out to either side
static void createPuffs(const Coords32* at) {
  struct VFX* p = allocLight(at, 3);
  if (p != NULL) (p->s).d.x = -0x200;
  p = allocLight(at, 3);
  if (p != NULL) (p->s).d.x = 0x200;
}

// 0x080b91ec
static struct Entity* createPetal(struct Entity* boss, u8 n) {
  struct VFX* p = allocLight(NULL, 0);
  if (p == NULL) return NULL;
  (p->s).work[1] = n;
  (p->s).unk_28 = boss;
  return &p->s;
}

// 0x080b9060
static struct Entity* createBurst(struct Entity* boss, const Coords32* at) {
  struct VFX* p = allocLight(at, 4);
  if (p == NULL) return NULL;
  (p->s).unk_28 = boss;
  return &p->s;
}

// 0x080b8f50: the flash, and with it the orb
static struct Entity* orbPart(struct Entity* boss, const Coords32* at, u8 n, u8 out) {
  struct VFX* p = allocLight(at, 7);
  if (p == NULL) return NULL;
  (p->s).unk_28 = boss;
  (p->s).work[1] = out;
  (p->s).work[2] = n;
  return &p->s;
}

static struct Entity* createOrb(struct Entity* boss, const Coords32* at, u8 n) {
  struct Entity* p = orbPart(boss, at, n, 0);
  orbPart(boss, at, n, 1);
  return p;
}

static void lightDie(struct Entity* s) {
  s->flags &= ~(DISPLAY | COLLIDABLE);
  SET_VFX_ROUTINE(s, ENTITY_DISAPPEAR);
}

static void flip(struct Entity* s, u8 n) {
  SET_XFLIP(s, n & 1);
  SET_YFLIP(s, (n & 1) ^ ((n >> 1) & 1));
}

// 0x080b92b0, 0x080b937c: a petal on the last form, until it appears
static void Light_Petal(struct VFX* p) {
  struct Entity* s = &p->s;
  struct ElpizoFinal* boss = (struct ElpizoFinal*)s->unk_28;
  u8 n = s->work[1];
  if (s->mode[2] == 0) {
    ResetDynamicMotion(s);
    SetMotion(s, FINAL(s->mode[1] == 0 ? 5 : 6));
    if (s->mode[1] == 0) {
      s->renderPrio = 25;
      SET_XFLIP(s, ((n >> 1) ^ n) & 1);
      SET_YFLIP(s, n & 1);
    }
    s->mode[2]++;
  }
  s->coord.x = (boss->s).coord.x;
  s->coord.y = (boss->s).coord.y - (n & 1) * 256;
  if (s->mode[1] == 1 && (boss->attacks & ATTACK_APPEAR)) {
    lightDie(s);
    return;
  }
  FUN_0801779c(s);
  if (s->mode[1] == 0 && animEnded(s)) setMode(s, 1);
}

// 0x080b93f4, 0x080b947c, 0x080b9564..0x080b9700: sparks and puffs, gone when played
static void Light_Spark(struct VFX* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    switch (s->work[0]) {
      case 1:
        (s->spr).oam.priority = s->work[2] & 3;
        s->palID = s->work[2] == 3;
        s->renderPrio = 9;
        SetMotion(s, PARTS(14));
        break;
      case 2:
        SetMotion(s, PARTS(21));
        break;
      case 3:
        (s->spr).oam.priority = 1;
        s->texture = 0;
        SetMotion(s, MOTION(SM000_BATTLE_EFFECT, 3));
        s->work[2] = 0;
        break;
      case 5:
        SetMotion(s, FX(10));
        break;
      default:
        SetMotion(s, PARTS(20));
        break;
    }
    s->mode[2]++;
  }
  if (s->work[0] == 3) {
    if (s->work[2]++ & 1) {
      s->flags |= DISPLAY;
    } else {
      s->flags &= ~DISPLAY;
    }
    s->coord.x += s->d.x;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) lightDie(s);
}

// 0x080b9564: waits, then flares three times, letting a seeker out every fourth frame of the second
static void Light_Burst(struct VFX* p) {
  // 0x08347064, 0x0834706a
  static const u16 sAnims[3] = {FX(7), FX(8), FX(9)};
  static const u8 sLoops[3] = {1, 13, 1};
  struct Entity* s = &p->s;
  if (bossGone(s->unk_28)) {
    lightDie(s);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->flags &= ~DISPLAY;
      (s->spr).oam.priority = 1;
      s->work[2] = 58;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      s->flags |= DISPLAY;
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      s->work[3] = 0;
      SetMotion(s, sAnims[s->work[2]]);
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateEntityAnim(s);
      if ((u8)((s->motion).state - ANIM_END) > 1) break;
      s->work[3]++;
      if (s->work[2] == 1 && (s->work[3] & 3) == 0) createSeeker(s->unk_28, &s->coord);
      if (s->work[3] < sLoops[s->work[2]]) break;
      if (++s->work[2] > 2) {
        lightDie(s);
      } else {
        s->mode[2] = 3;
      }
      break;
  }
}

// 0x080b9758: an orb's flash on the last form, or the orb at the corner shooting after 20 frames
static void Light_Orb(struct VFX* p) {
  // 0x0834706d
  static const s8 sCorners[4][2] = {{64, -60}, {-64, 60}, {64, 60}, {-64, -60}};
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 n = s->work[2];
  if (bossGone(boss)) {
    lightDie(s);
    return;
  }
  if (s->mode[2] == 0) {
    if (s->work[1] != 0) {
      s->coord.x += PIXEL(sCorners[n][0]);
      s->coord.y += PIXEL(sCorners[n][1]);
      s->texture = TEXTURE_AP_SHEET;
      SetMotion(s, PARTS(17));
    } else {
      ResetDynamicMotion(s);
      SetMotion(s, FINAL(19));
    }
    flip(s, n);
    s->work[3] = 20;
    s->mode[2]++;
  }
  if (s->work[1] != 0) {
    UpdateEntityAnim(s);
  } else {
    s->coord.y = boss->coord.y - (((n & 1) ^ ((n >> 1) & 1)) << 8);
    FUN_0801779c(s);
  }
  if (--s->work[3] != 0) return;
  if (s->work[1] != 0) allocFire(boss, &s->coord, 8, 0);
  lightDie(s);
}

typedef void (*LightFunc)(struct VFX*);

// 0x08347038
static const LightFunc sLightStates[9] = {
    Light_Petal, Light_Petal, Light_Spark, Light_Spark, Light_Spark, Light_Burst, Light_Spark, Light_Spark, Light_Orb,
};

// 0x080b9238
static void Light_Init(struct VFX* p) {
  // 0x0834705c
  static const u8 sModes[9] = {0, 2, 3, 4, 5, 6, 7, 8, 7};
  struct Entity* s = &p->s;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sModes[s->work[0]];
  s->flags |= FLIPABLE | DISPLAY;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  Light_Update(p);
}

static void Light_Update(struct VFX* p) { sLightStates[(p->s).mode[1]](p); }

#endif  // AP
