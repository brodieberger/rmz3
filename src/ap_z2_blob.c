#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "palette_animation.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Zero 2's blob, boss 11.
  work0:
    0: blob
    1: copy over Zero while held
    2: unseen, hits Zero while held
*/

struct Blob {
  OBJECT_HDR;
  s32 dx;                   // 0xB4, Zero's x from ours when last hit
  u8 _b8[4];
  s32 targetX;              // 0xBC
  u32 signals;              // 0xC0
  u8 returned;              // 0xC4, worth of drops back
  u8 _c5;
  u8 repeats;               // 0xC6
  u8 lastAttack;            // 0xC7
  struct BlobDrop* armor;   // 0xC8
  u8 colorStep;             // 0xCC
  u8 form;                  // 0xCD
  u8 oldForm;               // 0xCE
  u8 dripDelay;             // 0xCF
  s16 sound;                // 0xD0
  u8 dripSide;              // 0xD2
  u8 _d3[17];
};
static_assert(sizeof(struct Blob) == sizeof(struct Boss));

/*
  Zero 2's projectile 26.
  work0:
    1: unseen armor following blob, only splashes
    2: splash
    3: spiral around spot
    4: drop falling from ceiling
    5: unseen on ceiling, drips then drops rock
*/
struct BlobDrop {
  OBJECT_HDR;
  u8 _b4[4];
  s32 reach;       // 0xB8
  Coords32 center; // 0xBC
};
static_assert(sizeof(struct BlobDrop) == 196);

/*
  Zero 2's projectile 27.
  work0:
    0: splat, bounces, pools, crawls home
    1: spray, bursts on landing, pools, crawls home
    2: drip, hits nothing
*/
struct BlobSplat {
  OBJECT_HDR;
  u8 gone;     // 0xB4, blob dying
  u8 _b5[3];
  s32 reach;   // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct BlobSplat) == 196);

enum { BLOB_INTRO, BLOB_TURN, BLOB_PICK, BLOB_HOP_WIND, BLOB_HOP, BLOB_LEAP_WIND, BLOB_NOP6, BLOB_NOP7,
       BLOB_NOP8, BLOB_NOP9, BLOB_NOP10, BLOB_REFORM, BLOB_SPRAY, BLOB_SPRAY_END, BLOB_GATHER, BLOB_LUNGE,
       BLOB_HOLD, BLOB_COPY, BLOB_HITTER, BLOB_LET_GO, BLOB_HURT, BLOB_LEAP, BLOB_STOMP };

enum { DIE_BURST, DIE_FLY, DIE_SLUMP, DIE_FLY_SMALL, DIE_SLUMP_SMALL, DIE_SPRAY_END, DIE_HOP_END, DIE_MELT };

enum { DROP_ARMOR = 4, DROP_SPLASH, DROP_SPIRAL, DROP_FALL, DROP_ROCK };
enum { SPLAT_BOUNCE, SPLAT_POOL, SPLAT_HOME, SPRAY_FLY, SPRAY_POOL, SPRAY_HOME, DRIP_FALL };

#define BLOB(n) MOTION(DM204_Z2_BLOB, (n))
#define DROP(n) MOTION(AP_SHEET_Z2_BLOB_DROP, (n))
#define SPLAT(n) MOTION(AP_SHEET_Z2_BLOB_SPLAT, (n))
#define ROCK(n) MOTION(AP_SHEET_Z2_BLOB_ROCK, (n))

#define HITBOX(n) (&sCollisions[(n)*2])
#define ARMOR_HITBOX(n) (&sDropCollisions[(n)*2])
#define SPLAT_HITBOX(n) (&sSplatCollisions[(n)*2])

#define SIGNAL_POOL 1
#define SIGNAL_HOME 2
#define SIGNAL_HOLD 4

#define GRAVITY 32
#define MAX_FALL 0x380
#define ROCK_GRAVITY 64
#define ROCK_MAX_FALL 0x700

#define COLOR_OFFSET 0x280
#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define BLOB_COLOR(n) &gApZ2Naold2_PlttAnim##n, gApZ2Naold2_PlttAnimScript##n

extern const PlttAnimData gApZ2Naold2_PlttAnim7, gApZ2Naold2_PlttAnim9, gApZ2Naold2_PlttAnim10, gApZ2Naold2_PlttAnim11,
    gApZ2Naold2_PlttAnim12, gApZ2Naold2_PlttAnim13, gApZ2Naold2_PlttAnim14, gApZ2Naold2_PlttAnim15, gApZ2Naold2_PlttAnim16;
extern const AnimCmd* const gApZ2Naold2_PlttAnimScript7[], *const gApZ2Naold2_PlttAnimScript9[],
    *const gApZ2Naold2_PlttAnimScript10[], *const gApZ2Naold2_PlttAnimScript11[], *const gApZ2Naold2_PlttAnimScript12[],
    *const gApZ2Naold2_PlttAnimScript13[], *const gApZ2Naold2_PlttAnimScript14[], *const gApZ2Naold2_PlttAnimScript15[],
    *const gApZ2Naold2_PlttAnimScript16[];

static const struct Collision sCollisions[76];
static const struct Collision sDropCollisions[46];
static const struct Collision sSplatCollisions[8];

static const struct PreloadEntity sDropSheet = {AP_SHEET_Z2_BLOB_DROP, 0, 584, 4, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSplatSheet = {AP_SHEET_Z2_BLOB_SPLAT, 0, 584 + AP_SHEET_Z2_BLOB_DROP_TILES, 4, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sRockSheet = {AP_SHEET_Z2_BLOB_ROCK, 0, 584 + AP_SHEET_Z2_BLOB_DROP_TILES + AP_SHEET_Z2_BLOB_SPLAT_TILES, 5, 0, AP_PRELOAD_SHEET, 0};

static const BossFunc sStates[23];
static const BossFunc sDeaths[8];
static const u8 sDeathOf[23] = {DIE_BURST, DIE_MELT, DIE_HOP_END, DIE_MELT, DIE_MELT, DIE_HOP_END, 0, 0,
                                DIE_FLY, DIE_FLY, DIE_FLY_SMALL, DIE_SLUMP_SMALL, DIE_HOP_END, DIE_SPRAY_END,
                                DIE_SLUMP, DIE_HOP_END, DIE_HOP_END, 0, 0, DIE_HOP_END, DIE_HOP_END, 0, DIE_HOP_END};

static void Blob_Init(struct Blob* p);
static void Blob_Update(struct Blob* p);
static void Blob_Die(struct Blob* p);
static void Blob_Disappear(struct Blob* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static struct BlobDrop* createDrop(struct Entity* boss, u8 kind, const Coords32* at, u8 xflip);
static void createSplat(struct Entity* boss, const Coords32* at, const Coords32* v, u8 kind, u8 arg);
static void createDrip(const Coords32* at, s32 reach, u8 frames, bool8 sounds);

// clang-format off
const BossRoutine gApZ2BlobRoutine = {
    [ENTITY_INIT] =      (BossFunc)Blob_Init,
    [ENTITY_UPDATE] =    (BossFunc)Blob_Update,
    [ENTITY_DIE] =       (BossFunc)Blob_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Blob_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 dying(struct Entity* e) { return e->mode[0] > ENTITY_UPDATE; }

static void faceZero(struct Blob* p) { SET_XFLIP(p, (pZero2->s).coord.x > (p->s).coord.x); }

static void setArmor(struct Blob* p, u8 n) { SetDDP(&(p->armor)->body, ARMOR_HITBOX(n)); }

// Moves out of walls, floor and ceiling. bit0: floor, bit1: wall, bit2: no floor ahead, bit3: ceiling
// 0x0804ebc4, 0x0804ec9c, 0x0804ed6c, 0x0809f784, 0x080a0460, 0x080a0524
static u8 probe(struct Entity* s, s32 side, s32 ceiling, s32 foot) {
  bool8 right = s->d.x > 0;
  s32 ahead = right ? side : -side;
  s32 y = s->coord.y - PIXEL(8);
  s32 push;
  u8 hit = 0;
  push = right ? PushoutToLeft1(s->coord.x + ahead, y) : PushoutToRight1(s->coord.x + ahead, y);
  if (right ? push < 0 : push > 0) {
    s->coord.x += push;
    hit = 2;
  }
  if (FUN_080098a4(s->coord.x + ahead, y + PIXEL(16)) == 0) hit |= 4;
  y = FUN_0800a134(s->coord.x, s->coord.y);
  if (y > s->coord.y - ceiling && s->d.y < 0) {
    s->coord.y = y + ceiling;
    hit |= 8;
  }
  y = FUN_08009f6c(s->coord.x, s->coord.y) - foot;
  if (y - s->coord.y < 0x440 && s->d.y > 0) {
    s->coord.y = y;
    hit |= 1;
  }
  return hit;
}

#define PROBE_BIG(s) probe((s), 0x1600, 0x1000, 0)
#define PROBE_BODY(s) probe((s), 0xE00, 0x800, 0x800)
#define PROBE_SMALL(s) probe((s), 0x600, 0x600, 0x600)

static void fall(struct Entity* s, s32 gravity, s32 max) {
  s->d.y += gravity;
  if (s->d.y > max) s->d.y = max;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// --------------------------------------------

static void startColor(u8 n);
static u32 stepColor(u8 n);
static void removeColor(u8 n);

// 0x0804ea84: one of four colors while form holds, fading through 13..16 and back through 9..12
static void updateColor(struct Blob* p) {
  if ((p->s).mode[1] == BLOB_INTRO) return;
  switch (p->colorStep) {
    case 0:
    start:
      startColor(0);
      p->colorStep++;
      FALLTHROUGH;
    case 1:
      stepColor(0);
      if (p->form == 0) return;
      p->oldForm = p->form - 1;
      removeColor(0);
      p->colorStep++;
      FALLTHROUGH;
    case 2:
      startColor(1 + p->oldForm);
      p->colorStep++;
      FALLTHROUGH;
    case 3:
      stepColor(1 + p->oldForm);
      if (p->form != 0) return;
      removeColor(1 + p->oldForm);
      p->colorStep++;
      FALLTHROUGH;
    case 4:
      startColor(5 + p->oldForm);
      p->colorStep++;
      FALLTHROUGH;
    case 5:
      if ((u8)stepColor(5 + p->oldForm) != 4) return;
      removeColor(5 + p->oldForm);
      p->colorStep = 0;
      goto start;
  }
}

static const u8 sColorIds[9] = {7, 13, 14, 15, 16, 9, 10, 11, 12};

static void startColor(u8 n) {
  switch (sColorIds[n]) {
    case 7: ApStartPaletteAnimation(PLTT_ANIM_ID(7), BLOB_COLOR(7), COLOR_OFFSET); break;
    case 9: ApStartPaletteAnimation(PLTT_ANIM_ID(9), BLOB_COLOR(9), COLOR_OFFSET); break;
    case 10: ApStartPaletteAnimation(PLTT_ANIM_ID(10), BLOB_COLOR(10), COLOR_OFFSET); break;
    case 11: ApStartPaletteAnimation(PLTT_ANIM_ID(11), BLOB_COLOR(11), COLOR_OFFSET); break;
    case 12: ApStartPaletteAnimation(PLTT_ANIM_ID(12), BLOB_COLOR(12), COLOR_OFFSET); break;
    case 13: ApStartPaletteAnimation(PLTT_ANIM_ID(13), BLOB_COLOR(13), COLOR_OFFSET); break;
    case 14: ApStartPaletteAnimation(PLTT_ANIM_ID(14), BLOB_COLOR(14), COLOR_OFFSET); break;
    case 15: ApStartPaletteAnimation(PLTT_ANIM_ID(15), BLOB_COLOR(15), COLOR_OFFSET); break;
    case 16: ApStartPaletteAnimation(PLTT_ANIM_ID(16), BLOB_COLOR(16), COLOR_OFFSET); break;
  }
}

static u32 stepColor(u8 n) { return StepPaletteAnimation(PLTT_ANIM_ID(sColorIds[n])); }

static void removeColor(u8 n) { RemovePaletteAnimation(PLTT_ANIM_ID(sColorIds[n])); }

// 0x0804ea2c
static void endColor(struct Blob* p) {
  switch (p->colorStep) {
    case 1: removeColor(0); break;
    case 3: removeColor(1 + p->oldForm); break;
    case 5: removeColor(5 + p->oldForm); break;
  }
}

// --------------------------------------------

// 0x0804ee6c
static void Blob_Init(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sStart[3] = {BLOB_INTRO, BLOB_COPY, BLOB_HITTER};
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sStart[s->work[0]];
  s->flags |= FLIPABLE;
  InitNonAffineMotion(s);
  if (s->work[0] != 2) {
    ResetDynamicMotion(s);
    SetSpriteAnimation(p, BLOB(0));
  }
  s->flags |= DISPLAY;
  if (s->work[0] != 1) {
    ResetBossBody((struct Boss*)p, sCollisions, 96);
    (p->body).fn = onCollision;
  }
  if (s->work[0] == 0) {
    p->armor = createDrop(s, 1, NULL, 0);
    ApLoadSheet(&sDropSheet);
    ApLoadSheet(&sSplatSheet);
    ApLoadSheet(&sRockSheet);
  }
  p->signals = 0;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->colorStep = 0;
  p->form = 0;
  p->sound = -1;
  p->returned = 0;
  p->lastAttack = 0;
  p->repeats = 0;
  Blob_Update(p);
}

static void stopSound(struct Blob* p) {
  if (p->sound != -1) {
    StopSound(p->sound);
    p->sound = -1;
  }
}

static void holdZero(struct Blob* p) {
  struct Entity* zero = (p->body).enemy->parent;
  zero->coord.x = (p->s).coord.x;
  zero->coord.y = (p->s).coord.y;
}

// 0x0804f144
static void checkHold(struct Blob* p) {
  if ((p->body).status & BODY_STATUS_BINDING) {
    holdZero(p);
    setMode(&p->s, BLOB_HOLD);
  }
}

// 0x0804effc
static void Blob_Update(struct Blob* p) {
  struct Entity* s = &p->s;
  u8 mode;
  if (s->work[0] == 0) {
    updateColor(p);
    if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
        !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
      stopSound(p);
      if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
        gStageRun.missionStatus &= ~MISSION_STAY;
        gStageRun.missionStatus |= MISSION_SUCCESS;
      }
      p->form = 0;
      mode = sDeathOf[s->mode[1]];
      SET_BOSS_ROUTINE(p, ENTITY_DIE);
      s->mode[1] = mode;
      Blob_Die(p);
      return;
    }
  }
  switch (s->mode[1]) {
    case BLOB_INTRO:
    case BLOB_TURN:
    case BLOB_HOP_WIND:
    case BLOB_HOP:
    case BLOB_LEAP_WIND:
    case BLOB_SPRAY:
    case BLOB_SPRAY_END:
    case BLOB_GATHER:
    case BLOB_LUNGE:
    case BLOB_HURT:
      checkHold(p);
      break;
    case BLOB_PICK:
      if ((p->body).status & BODY_STATUS_WHITE) setMode(s, BLOB_HURT);
      break;
    case BLOB_HOLD:
      if (!((p->body).status & BODY_STATUS_BINDING)) {
        p->signals &= ~SIGNAL_HOLD;
        setMode(s, BLOB_LET_GO);
      }
      break;
  }
  (sStates[s->mode[1]])((struct Boss*)p);
}

static void Blob_Die(struct Blob* p) { (sDeaths[(p->s).mode[1]])((struct Boss*)p); }

// 0x0804f0fc
static void Blob_Disappear(struct Blob* p) {
  stopSound(p);
  DeleteBoss(&p->s);
}

// 0x0804f12c
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Blob* p = (struct Blob*)body->parent;
  p->dx = (pZero2->s).coord.x - (p->s).coord.x;
}

// --------------------------------------------

// 0x0804f1d4: falls in drop by drop, pools, rises into shape
static void Blob_Intro(struct Blob* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 spread;
  switch (s->mode[2]) {
    case 0:
      s->flags &= ~DISPLAY;
      if (s->scriptEntity->flags & 1) s->mode[2]++;
      break;
    case 1:
      at.x = s->coord.x;
      at.y = gStageRun.vm.camera.viewport.y - PIXEL(88);
      createDrip(&at, 0, 55, TRUE);
      s->work[2] = 56;
      s->work[3] = 0;
      p->dripDelay = 8;
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 3:
      s->flags |= DISPLAY;
      s->work[3] = 0;
      SetSpriteAnimation(p, BLOB(0x19));
      s->coord.y = gStageRun.vm.camera.viewport.y - PIXEL(80);
      s->d.y = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 4: {
      s32 push;
      UpdateSpriteAnimation(p);
      s->coord.y += s->d.y;
      s->d.y += 64;
      push = PushoutToUp1(s->coord.x, s->coord.y);
      if (push < 0) {
        PlaySound(SE_Z2_BLOB_HOP);
        s->coord.y += push;
        s->mode[2]++;
      }
      break;
    }
    case 5:
      (s->spr).mag.x = 128;
      (s->spr).mag.y = 128;
      SetSpriteAnimation(p, BLOB(0x1A));
      p->dripSide = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 6:
      s->work[2]--;
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[2]++;
      break;
    case 7:
      SetSpriteAnimation(p, BLOB(0x1D));
      s->work[2] = 16;
      s->mode[2]++;
      FALLTHROUGH;
    case 8:
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 9:
      createDrop(s, 3, &s->coord, 0);
      InitRotatableMotion(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, BLOB(0x1E));
      (s->spr).mag.x = 128;
      (s->spr).mag.y = 128;
      s->mode[2]++;
      FALLTHROUGH;
    case 10:
      s->work[2]--;
      (s->spr).mag.x += 2;
      (s->spr).mag.y = (s->spr).mag.x;
      if ((s->spr).mag.x == 256) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 11:
      InitNonAffineMotion(s);
      ResetDynamicMotion(s);
      GotoMotion(s, BLOB(2), (s->motion).cmdIdx, (s->motion).duration);
      s->work[2] = 32;
      s->mode[2]++;
      FALLTHROUGH;
    case 12:
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 13:
      SetSpriteAnimation(p, BLOB(0x11));
      s->mode[2]++;
      FALLTHROUGH;
    case 14:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[2]++;
      break;
    case 15:
      SetSpriteAnimation(p, BLOB(0));
      s->mode[2]++;
      FALLTHROUGH;
    case 16:
      UpdateSpriteAnimation(p);
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, BLOB_PICK);
      break;
  }
  if (s->mode[2] < 6 || s->mode[2] > 10) return;
  if (s->work[3] != 0) {
    s->work[3]--;
    return;
  }
  spread = (s->spr).mag.x * 40;
  at.x = s->coord.x + RANDOM(RNG_0202f388) % spread - spread / 2;
  at.y = gStageRun.vm.camera.viewport.y - PIXEL(80);
  createDrip(&at, 0x400, 1, !(p->dripSide & 1));
  p->dripSide++;
  if (p->dripDelay != 0) p->dripDelay -= 2;
  s->work[3] = (RANDOM(RNG_0202f388) & 7) + p->dripDelay;
}

static void stepTable(struct Blob* p, const u8* times, const u8* hitboxes, const u8* armor) {
  struct Entity* s = &p->s;
  if (s->work[2] >= times[s->work[3]]) s->work[3]++;
  s->work[2]++;
  SetDDP(&p->body, HITBOX(hitboxes[s->work[3]]));
  setArmor(p, armor[s->work[3]]);
}

// 0x0804f514
static void Blob_Turn(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sHitboxes[4] = {6, 5, 6, 4};
  static const u8 sArmor[4] = {3, 3, 5, 4};
  static const u8 sTimes[4] = {4, 14, 15, 90};
  if (s->mode[2] == 0) {
    (s->spr).oam.priority = 2;
    faceZero(p);
    SetSpriteAnimation(p, BLOB(0x11));
    s->work[2] = 0;
    s->work[3] = 0;
    s->mode[2]++;
  }
  stepTable(p, sTimes, sHitboxes, sArmor);
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, BLOB_PICK);
}

static const u8 sNearAttacks[16] = {BLOB_HOP_WIND, BLOB_HOP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_SPRAY, BLOB_SPRAY,
                                    BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE, BLOB_LUNGE};
static const u8 sMidAttacks[16] = {BLOB_HOP_WIND, BLOB_HOP_WIND, BLOB_STOMP, BLOB_STOMP, BLOB_STOMP, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND,
                                   BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_SPRAY, BLOB_SPRAY, BLOB_SPRAY, BLOB_SPRAY, BLOB_LUNGE, BLOB_LUNGE};
static const u8 sFarAttacks[16] = {BLOB_HOP_WIND, BLOB_HOP_WIND, BLOB_STOMP, BLOB_STOMP, BLOB_STOMP, BLOB_STOMP, BLOB_STOMP, BLOB_STOMP,
                                   BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_LEAP_WIND, BLOB_SPRAY, BLOB_SPRAY};

// 0x0804ee3c
static u8 noteAttack(struct Blob* p, u8 attack) {
  if (p->lastAttack == attack) {
    p->repeats++;
  } else {
    p->lastAttack = attack;
    p->repeats = 0;
  }
  return p->repeats;
}

// 0x0804f614: never same three times running. Stomp is EX, at rank A and half health
static void Blob_Pick(struct Blob* p) {
  struct Entity* s = &p->s;
  s32 d;
  u8 r, attack, repeats;
  bool8 again;
  if (s->mode[2] == 0) {
    setArmor(p, 2);
    SetDDP(&p->body, HITBOX(0));
    (s->spr).oam.priority = 2;
    faceZero(p);
    SetSpriteAnimation(p, BLOB(0));
    s->work[2] = 32;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) {
    d = (pZero2->s).coord.x - s->coord.x;
    if (d < 0) d = -d;
    do {
      r = RANDOM(RNG_0202f388) & 15;
      if (d <= PIXEL(100)) {
        attack = sNearAttacks[r];
      } else if (d <= PIXEL(160)) {
        attack = sMidAttacks[r];
      } else {
        attack = sFarAttacks[r];
      }
      repeats = noteAttack(p, attack);
      again = attack == BLOB_STOMP ? repeats != 0 : repeats > 1;
      if ((gScore.total->rank <= 4 || (p->body).hp > 48) && attack == BLOB_STOMP) again = TRUE;
    } while (again);
    setMode(s, attack);
  }
  UpdateSpriteAnimation(p);
}

// 0x0804f798
static void Blob_HopWind(struct Blob* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    (s->spr).oam.priority = 2;
    faceZero(p);
    SetSpriteAnimation(p, BLOB(1));
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (s->work[2] <= 8) {
    setArmor(p, 4);
    SetDDP(&p->body, HITBOX(4));
  } else if (s->work[2] <= 22) {
    setArmor(p, 3);
    SetDDP(&p->body, HITBOX(5));
  } else {
    setArmor(p, 3);
    SetDDP(&p->body, HITBOX(6));
  }
  s->work[2]++;
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, BLOB_HOP);
}

// 0x0804f8a0
static void Blob_Hop(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sHitboxes[7] = {1, 7, 8, 9, 10, 11, 12};
  static const u8 sArmor[7] = {5, 5, 3, 3, 3, 5, 5};
  static const u8 sTimes[7] = {6, 12, 20, 32, 38, 46, 90};
  s32 d;
  if (s->mode[2] == 0) {
    bool8 right = (pZero2->s).coord.x > s->coord.x;
    setArmor(p, 3);
    (s->spr).oam.priority = 2;
    SET_XFLIP(p, right);
    p->targetX = (pZero2->s).coord.x + (right ? PIXEL(64) : -PIXEL(64));
    s->d.x = right ? 0x2C0 : -0x2C0;
    SetSpriteAnimation(p, BLOB(3));
    SetDDP(&p->body, HITBOX(1));
    s->work[2] = 0;
    s->work[3] = 0;
    PlaySound(SE_Z2_BLOB_HOP);
    s->mode[2]++;
  }
  stepTable(p, sTimes, sHitboxes, sArmor);
  s->coord.x += s->d.x;
  d = s->coord.x - p->targetX;
  if (d < 0) d = -d;
  if (d < 0x400 || (PROBE_BIG(s) & 2)) setMode(s, BLOB_TURN);
  UpdateSpriteAnimation(p);
  if ((s->motion).state == 4) {
    s->work[2] = 0;
    s->work[3] = 0;
  }
}

// 0x0804fa24
static void Blob_LeapWind(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sHitboxes[9] = {18, 19, 20, 21, 22, 23, 24, 25, 0};
  static const u8 sArmor[9] = {10, 11, 12, 13, 14, 15, 16, 17, 0};
  static const u8 sTimes[9] = {9, 13, 17, 21, 25, 29, 33, 90, 0};
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_BLOB_LEAP);
    p->form = 4;
    (s->spr).oam.priority = 2;
    SetSpriteAnimation(p, BLOB(4));
    s->work[2] = 0;
    s->work[3] = 0;
    s->mode[2]++;
  }
  s->work[2]++;
  if (s->work[2] >= sTimes[s->work[3]]) s->work[3]++;
  SetDDP(&p->body, HITBOX(sHitboxes[s->work[3]]));
  setArmor(p, sArmor[s->work[3]]);
  if ((s->motion).state == ANIM_END) setMode(s, BLOB_LEAP);
  UpdateSpriteAnimation(p);
}

static void Blob_Nop(struct Blob* p UNUSED) {}

// 0x0804faf0: pools, drops come home, rises
static void Blob_Reform(struct Blob* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setArmor(p, 3);
      SetDDP(&p->body, HITBOX(17));
      (s->spr).oam.priority = 2;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      SetSpriteAnimation(p, BLOB(0x1A));
      p->signals |= SIGNAL_POOL;
      s->work[2] = 8;
      p->returned = 4;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      faceZero(p);
      if (s->work[2] == 0) {
        p->signals |= SIGNAL_HOME;
      } else {
        s->work[2]--;
      }
      if (p->returned > 7) s->mode[2]++;
      if ((s->motion).state == ANIM_END) SetSpriteAnimation(p, BLOB(0x1D));
      UpdateSpriteAnimation(p);
      break;
    case 2:
      SetDDP(&p->body, HITBOX(16));
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      SetSpriteAnimation(p, BLOB(0x17));
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      faceZero(p);
      if (p->returned == 16) s->mode[2]++;
      if ((s->motion).state == ANIM_END) SetSpriteAnimation(p, BLOB(0x1C));
      UpdateSpriteAnimation(p);
      break;
    case 4:
      setArmor(p, 5);
      SetDDP(&p->body, HITBOX(6));
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      SetSpriteAnimation(p, BLOB(2));
      s->work[2] = 30;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      faceZero(p);
      if (--s->work[2] == 0) {
        p->signals &= ~(SIGNAL_HOME | SIGNAL_POOL);
        setMode(s, BLOB_TURN);
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0804fd84: throws eight blobs, left and right by turns, each pair nearer
static void Blob_Spray(struct Blob* p) {
  struct Entity* s = &p->s;
  static const s32 sSprayX[4] = {-320, -512, -704, -832};
  static const s32 sSprayY[4] = {-320, -640, -768, -896};
  Coords32 at, v;
  u8 i, pair;
  if (s->mode[2] == 0) {
    setArmor(p, 6);
    p->form = 2;
    (s->spr).oam.priority = 2;
    SetSpriteAnimation(p, BLOB(0x0E));
    p->sound = PlaySound(SE_Z2_BLOB_SPRAY);
    s->work[2] = 32;
    s->work[3] = 0;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) {
    s->work[2] = 10;
    i = s->work[3];
    pair = 3 - (i >> 1);
    v.x = sSprayX[pair] - (i & 1) * sSprayX[pair] * 2;
    v.y = sSprayY[pair];
    at.x = s->coord.x;
    at.y = s->coord.y - PIXEL(32);
    createSplat(s, &at, &v, 1, 0);
    if (++s->work[3] == 8) setMode(s, BLOB_SPRAY_END);
  }
  UpdateSpriteAnimation(p);
}

// 0x0804fe60
static void Blob_SprayEnd(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sHitboxes[6] = {28, 29, 30, 31, 32, 33};
  static const u8 sArmor[6] = {7, 8, 9, 3, 3, 3};
  static const u8 sTimes[6] = {5, 15, 19, 25, 29, 90};
  switch (s->mode[2]) {
    case 0:
      stopSound(p);
      setArmor(p, 6);
      (s->spr).oam.priority = 2;
      SetSpriteAnimation(p, BLOB(0x0F));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) {
        p->form = 0;
        s->mode[2]++;
      }
      break;
    case 2:
      SetSpriteAnimation(p, BLOB(0x10));
      s->work[2] = 0;
      s->work[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      s->work[2]++;
      if (s->work[2] >= sTimes[s->work[3]]) s->work[3]++;
      SetDDP(&p->body, HITBOX(sHitboxes[s->work[3]]));
      setArmor(p, sArmor[s->work[3]]);
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) setMode(s, BLOB_GATHER);
      break;
  }
}

// 0x0804ff74
static void Blob_Gather(struct Blob* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      setArmor(p, 3);
      SetDDP(&p->body, HITBOX(16));
      (s->spr).oam.priority = 2;
      SetSpriteAnimation(p, BLOB(0x1C));
      p->signals |= SIGNAL_POOL;
      s->work[2] = 8;
      p->returned = 8;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      faceZero(p);
      if (s->work[2] == 0) {
        p->signals |= SIGNAL_HOME;
      } else {
        s->work[2]--;
      }
      if (p->returned == 16) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      setArmor(p, 5);
      SetDDP(&p->body, HITBOX(6));
      SetSpriteAnimation(p, BLOB(2));
      s->work[2] = 6;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      faceZero(p);
      if (--s->work[2] == 0) {
        p->signals &= ~(SIGNAL_HOME | SIGNAL_POOL);
        setMode(s, BLOB_TURN);
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0805011c: holds Zero on touch
static void Blob_Lunge(struct Blob* p) {
  struct Entity* s = &p->s;
  static const u8 sHitboxes[4] = {0, 26, 27, 0};
  static const u8 sTimes[4] = {25, 37, 41, 90};
  if (s->mode[2] == 0) {
    (s->spr).oam.priority = 2;
    SetSpriteAnimation(p, BLOB(0x12));
    PlaySound(SE_Z2_BLOB_LUNGE);
    s->d.x = (s->flags & X_FLIP) ? 0x480 : -0x480;
    s->work[2] = 0;
    s->work[3] = 0;
    s->mode[2]++;
  }
  if (s->work[2] > 24) {
    s->coord.x += s->d.x;
    s->d.x = s->d.x * 235 / 256;
  }
  PROBE_BIG(s);
  if (s->work[2] >= sTimes[s->work[3]]) s->work[3]++;
  s->work[2]++;
  SetDDP(&p->body, HITBOX(sHitboxes[s->work[3]]));
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, BLOB_PICK);
}

static struct Blob* createBoss(struct Entity* parent, u8 kind) {
  struct Blob* e = AllocEntityLast(gBossHeaderPtr);
  if (e != NULL) {
    INIT_BOSS_ROUTINE(e, BOSS_Z2_BLOB);
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).coord.x = parent->coord.x;
    (e->s).coord.y = parent->coord.y;
    (e->s).work[0] = kind;
    (e->s).unk_28 = parent;
  }
  return e;
}

// 0x080501f4: hits Zero every 32 frames until he struggles free
static void Blob_Hold(struct Blob* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->form = 1;
    (s->spr).oam.priority = 2;
    p->signals |= SIGNAL_HOLD;
    SetDDP(&p->body, HITBOX(3));
    SetSpriteAnimation(p, BLOB(7));
    createBoss(s, 1);
    PlaySound(SE_Z2_BLOB_LEAP);
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (s->work[2] == 0) createBoss(s, 2);
  if (++s->work[2] == 32) s->work[2] = 0;
  if ((p->body).status & BODY_STATUS_BINDING) holdZero(p);
  UpdateSpriteAnimation(p);
}

// 0x08050328
static void Blob_Copy(struct Blob* p) {
  struct Entity* s = &p->s;
  struct Blob* boss = (struct Blob*)s->unk_28;
  if (s->mode[2] == 0) {
    s->flags2 |= WHITE_PAINTABLE;
    s->invincibleID = (boss->s).uniqueID;
    SET_XFLIP(p, ((boss->s).flags & X_FLIP) != 0);
    (s->spr).oam.priority = 1;
    SetSpriteAnimation(p, BLOB(0x0B));
    s->mode[2]++;
  }
  if (!(boss->signals & SIGNAL_HOLD) || dying(&boss->s)) {
    s->flags &= ~DISPLAY;
    EXIT_BODY(p);
    SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  FUN_0801779c(s);
}

// 0x08050404
static void Blob_Hitter(struct Blob* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    SetDDP(&p->body, HITBOX(2));
    s->work[2] = 2;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) {
    EXIT_BODY(p);
    SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateSpriteAnimation(p);
}

// 0x08050488
static void Blob_LetGo(struct Blob* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    (s->spr).oam.priority = 1;
    SetSpriteAnimation(p, BLOB(0x0A));
    SetDDP(&p->body, HITBOX(24));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) {
    p->form = 0;
    setMode(s, BLOB_TURN);
  }
}

// 0x080504f0: slides back and picks at once
static void Blob_Hurt(struct Blob* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, BLOB(0x13));
    setArmor(p, 2);
    SetDDP(&p->body, HITBOX(0));
    s->d.x = p->dx > 0 ? -128 : 128;
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  s->d.x = s->d.x * 240 / 256;
  PROBE_BIG(s);
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) {
    s->mode[1] = BLOB_PICK;
    s->mode[2] = 1;
    faceZero(p);
    s->work[2] = 1;
    Blob_Pick(p);
  }
}

// 0x08050d9c: to nearest of four columns, three splats on landing
static void Blob_Leap(struct Blob* p) {
  struct Entity* s = &p->s;
  s32 x, d, best;
  u8 i, nearest;
  if (s->mode[2] == 0) {
    x = ((FUN_0800a31c(s->coord.x, s->coord.y) + FUN_0800a22c(s->coord.x, s->coord.y)) >> 1) - PIXEL(60);
    best = 0x7FFFFFFF;
    nearest = 0;
    for (i = 0; i < 4; i++) {
      d = (pZero2->s).coord.x - (x + i * PIXEL(40));
      if (d < 0) d = -d;
      if (d < best) {
        best = d;
        nearest = i;
      }
    }
    p->targetX = x + nearest * PIXEL(40);
    s->coord.y -= PIXEL(104);
    s->d.x = (p->targetX - s->coord.x) / 40;
    SET_XFLIP(p, s->d.x > 0);
    s->d.y = 0;
    setArmor(p, 18);
    (s->spr).oam.priority = 2;
    SetSpriteAnimation(p, BLOB(5));
    SetDDP(&p->body, HITBOX(13));
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += GRAVITY;
  if (s->d.y > ROCK_MAX_FALL) s->d.y = ROCK_MAX_FALL;
  if (PROBE_SMALL(s) & 1) {
    PlaySound(SE_Z2_BLOB_LAND);
    p->form = 0;
    setMode(s, BLOB_REFORM);
    s->d.x = 0x380;
    s->d.y = -0x340;
    createSplat(s, &s->coord, &s->d, 0, 1);
    s->d.x = -0x380;
    createSplat(s, &s->coord, &s->d, 0, 0);
    s->d.x = (s->flags & X_FLIP) ? 0x200 : -0x200;
    s->d.y = -0x500;
    createSplat(s, &s->coord, &s->d, 0, 0);
  }
  UpdateSpriteAnimation(p);
}

// 0x08050f90: stamps along, each stamp shakes rock loose elsewhere
static void Blob_Stomp(struct Blob* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 left, width, x, d;
  switch (s->mode[2]) {
    case 0:
      setArmor(p, 19);
      SetDDP(&p->body, HITBOX(37));
      SET_XFLIP(p, s->coord.x < (pZero2->s).coord.x);
      p->form = 3;
      (s->spr).oam.priority = 2;
      SetSpriteAnimation(p, BLOB(0x1F));
      s->work[2] = 3;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == 4 && --s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      setArmor(p, 20);
      SetSpriteAnimation(p, BLOB(0x20));
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[2]++;
      break;
    case 4:
      s->d.x = (s->flags & X_FLIP) ? 96 : -96;
      SetSpriteAnimation(p, BLOB(0x21));
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      if ((s->motion).cmdIdx == 3 || (s->motion).cmdIdx == 6) {
        if (s->work[2] == 0) {
          left = FUN_0800a31c(s->coord.x, s->coord.y);
          width = (FUN_0800a22c(s->coord.x, s->coord.y) - left) >> 8;
          do {
            x = PIXEL(RANDOM(RNG_0202f388) % width);
            d = x - p->targetX;
            if (d < 0) d = -d;
          } while (d < 0x3000);
          p->targetX = x;
          at.x = x + left;
          at.y = FUN_0800a134(s->coord.x, s->coord.y) - PIXEL(8);
          createDrop(NULL, 5, &at, 0);
          s->work[2] = 1;
          PlaySound(SE_Z2_BLOB_STOMP);
          AppendQuake(3, &s->coord);
        }
      } else {
        s->work[2] = 0;
        s->coord.x += s->d.x;
        x = s->coord.x + ((s->flags & X_FLIP) ? PIXEL(56) : -PIXEL(56));
        if (FUN_080098a4(x, s->coord.y) != 0) {
          p->form = 0;
          s->mode[2]++;
        }
      }
      UpdateSpriteAnimation(p);
      break;
    case 6:
      setArmor(p, 2);
      SetDDP(&p->body, HITBOX(0));
      faceZero(p);
      SetSpriteAnimation(p, BLOB(0));
      s->work[2] = 1;
      s->mode[2]++;
      FALLTHROUGH;
    case 7:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == 4 && --s->work[2] == 0) setMode(s, BLOB_PICK);
      break;
  }
}

// clang-format off
static const BossFunc sStates[23] = {
    (BossFunc)Blob_Intro, (BossFunc)Blob_Turn, (BossFunc)Blob_Pick, (BossFunc)Blob_HopWind,
    (BossFunc)Blob_Hop, (BossFunc)Blob_LeapWind, (BossFunc)Blob_Nop, (BossFunc)Blob_Nop,
    (BossFunc)Blob_Nop, (BossFunc)Blob_Nop, (BossFunc)Blob_Nop, (BossFunc)Blob_Reform,
    (BossFunc)Blob_Spray, (BossFunc)Blob_SprayEnd, (BossFunc)Blob_Gather, (BossFunc)Blob_Lunge,
    (BossFunc)Blob_Hold, (BossFunc)Blob_Copy, (BossFunc)Blob_Hitter, (BossFunc)Blob_LetGo,
    (BossFunc)Blob_Hurt, (BossFunc)Blob_Leap, (BossFunc)Blob_Stomp,
};
// clang-format on

// --------------------------------------------

static void smokeAround(struct Entity* s, s32 scale) {
  Coords32 at;
  u8 i;
  for (i = 0; i < 5; i++) {
    at.x = s->coord.x + (s32)(RANDOM(RNG_0202f388) & 15) * scale - (s32)(RANDOM(RNG_0202f388) & 31) * scale;
    at.y = s->coord.y + (s32)(RANDOM(RNG_0202f388) & 15) * scale - (s32)(RANDOM(RNG_0202f388) & 31) * scale;
    CreateSmoke(1, &at);
  }
}

// Each spot's speed and facing
static const s16 sLastSplats[4][3] = {{0xC0, -0x3C0, 0}, {-0x180, -0x280, 0}, {0x80, -0x320, 1}, {0x160, -0x300, 1}};
static const s16 sSomeSplats[2][3] = {{-0x110, -0x3C0, 0}, {0x160, -0x300, 1}};

static void splats(struct Entity* s, const s16 (*list)[3], u8 n, s32 up) {
  Coords32 at, v;
  u8 i;
  at.x = s->coord.x;
  at.y = s->coord.y - up;
  for (i = 0; i < n; i++) {
    v.x = list[i][0];
    v.y = list[i][1];
    createSplat(s, &at, &v, 0, (u8)list[i][2]);
  }
}

// 0x080505e8
static void Blob_DieBurst(struct Blob* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->flags &= ~DISPLAY;
      EXIT_BODY(p);
      smokeAround(s, 256);
      PlaySound(SE_Z2_TANK_EXPLODE);
      s->mode[2]++;
      break;
    case 1:
      splats(s, sLastSplats, 4, 0);
      s->mode[2]++;
      break;
    case 2:
      s->work[2] = 180;
      s->mode[2]++;
      break;
    case 3:
      if (--s->work[2] == 0) {
        gStageRun.vm.active |= VM_FLAG1;
        endColor(p);
        s->mode[2]++;
      }
      break;
  }
}

// 0x08050900, 0x08050c2c, 0x0805134c: stands a second, bursts, leaves some drops behind
static void slump(struct Blob* p, motion_t motion, s32 smoke, const s16 (*list)[3], u8 n) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      EXIT_BODY(p);
      SetSpriteAnimation(p, motion);
      s->work[2] = 60;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      smokeAround(s, smoke);
      s->flags &= ~DISPLAY;
      PlaySound(SE_Z2_TANK_EXPLODE);
      s->mode[2]++;
      break;
    case 3:
      splats(s, list, n, PIXEL(16));
      s->mode[2]++;
      break;
    case 4:
      s->work[2] = 180;
      s->mode[2]++;
      break;
    case 5:
      if (--s->work[2] == 0) {
        gStageRun.vm.active |= VM_FLAG1;
        endColor(p);
        s->mode[2]++;
      }
      break;
  }
}

static void Blob_DieSlump(struct Blob* p) { slump(p, BLOB(0x17), 256, sSomeSplats, 2); }
static void Blob_DieSlumpSmall(struct Blob* p) { slump(p, BLOB(0x1A), 1, sSomeSplats, 0); }
static void Blob_DieMelt(struct Blob* p) { slump(p, BLOB(2), 256, sLastSplats, 4); }

// 0x08050790, 0x08050abc: flung until it lands
static void flung(struct Blob* p, motion_t motion, u8 hit, u8 next) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    SetSpriteAnimation(p, motion);
    s->mode[2]++;
  }
  if ((RANDOM(RNG_0202f388) & 3) == 0) {
    at.x = s->coord.x + PIXEL(RANDOM(RNG_0202f388) & 15) - PIXEL(RANDOM(RNG_0202f388) & 31);
    at.y = s->coord.y + PIXEL(RANDOM(RNG_0202f388) & 15) - PIXEL(RANDOM(RNG_0202f388) & 31);
    CreateSmoke(2, &at);
    PlaySound(SE_Z2_TANK_EXPLODE);
  }
  fall(s, GRAVITY, MAX_FALL);
  if (hit == 0) {
    hit = PROBE_BODY(s);
  } else {
    hit = PROBE_SMALL(s);
  }
  if (hit & 1) setMode(s, next);
  if (hit & 2) {
    s->d.x = -s->d.x;
    SET_XFLIP(p, s->d.x > 0);
  }
  if (hit & 8) s->d.y = -s->d.y;
  UpdateSpriteAnimation(p);
}

static void Blob_DieFly(struct Blob* p) { flung(p, BLOB(0x15), 0, DIE_SLUMP); }
static void Blob_DieFlySmall(struct Blob* p) { flung(p, BLOB(0x19), 1, DIE_SLUMP_SMALL); }

// 0x08051294, 0x080512ec: finishes what it was doing
static void finish(struct Blob* p, motion_t motion, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    EXIT_BODY(p);
    SetSpriteAnimation(p, motion);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, next);
}

static void Blob_DieSprayEnd(struct Blob* p) { finish(p, BLOB(0x10), DIE_SLUMP); }
static void Blob_DieHopEnd(struct Blob* p) { finish(p, BLOB(1), DIE_MELT); }

static const BossFunc sDeaths[8] = {
    (BossFunc)Blob_DieBurst, (BossFunc)Blob_DieFly, (BossFunc)Blob_DieSlump, (BossFunc)Blob_DieFlySmall,
    (BossFunc)Blob_DieSlumpSmall, (BossFunc)Blob_DieSprayEnd, (BossFunc)Blob_DieHopEnd, (BossFunc)Blob_DieMelt,
};

// --------------------------------------------

static void useSheet(struct Entity* s) { s->texture = TEXTURE_AP_SHEET; }

static void Drop_Init(struct BlobDrop* p);
static void Drop_Update(struct BlobDrop* p);

// clang-format off
const ProjectileRoutine gApZ2BlobDropRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Drop_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Drop_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809f5dc, 0x0809f644, 0x0809f698, 0x0809f6ec, 0x0809f738
static struct BlobDrop* createDrop(struct Entity* boss, u8 kind, const Coords32* at, u8 xflip) {
  struct BlobDrop* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BLOB_DROP);
    (p->s).work[0] = kind;
    (p->s).work[2] = xflip;
    (p->s).unk_28 = boss;
    if (kind == 3) {
      p->center = *at;
    } else if (at != NULL) {
      (p->s).coord = *at;
    }
  }
  return p;
}

// 0x0809f854
static void onArmorHit(struct Body* body, Coords32* at, Coords32* r2 UNUSED) {
  struct BlobDrop* p = (struct BlobDrop*)body->parent;
  if (body->hitboxFlags & 1) {
    (p->body).hp = 20;
    createDrop(NULL, 2, at, ((p->s).flags & X_FLIP) != 0);
  }
}

// 0x0809f890
static void Drop_Init(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = DROP_ARMOR + s->work[0] - 1;
  InitNonAffineMotion(s);
  useSheet(s);
  s->flags |= FLIPABLE;
  if (s->work[0] != 1) s->flags |= DISPLAY;
  INIT_BODY(p, sDropCollisions, 0, s->work[0] == 1 ? onArmorHit : NULL);
  Drop_Update(p);
}

static void dropGone(struct BlobDrop* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x0809fdec
static void Drop_Armor(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (dying(boss)) {
    dropGone(p);
    return;
  }
  if (s->mode[2] == 0) {
    SetDDP(&p->body, ARMOR_HITBOX(2));
    s->mode[2]++;
  }
  SET_XFLIP(p, (boss->flags & X_FLIP) != 0);
  s->coord.x = boss->coord.x;
  s->coord.y = boss->coord.y;
}

// 0x0809fe64
static void Drop_Splash(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    SetSpriteAnimation(p, DROP(4));
    SET_XFLIP(p, s->work[2]);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) dropGone(p);
}

// 0x0809ff0c: widening as it goes
static void Drop_Spiral(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  static const s16 sHeights[4] = {-4096, -4608, -4096, -3584};
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    SetSpriteAnimation(p, DROP(5));
    s->work[2] = 65;
    p->reach = 128;
    s->mode[2]++;
  }
  p->reach += 2;
  s->coord.x = p->center.x + -(p->reach * 512) / 256;
  s->coord.y = p->center.y + (sHeights[(s->motion).cmdIdx] * p->reach) / 256;
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0) dropGone(p);
}

// 0x0809ffe8
static void Drop_Fall(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  s32 push;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    SetSpriteAnimation(p, ROCK(2));
    s->d.y = 0;
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  s->d.y += ROCK_GRAVITY;
  if (s->d.y > ROCK_MAX_FALL) s->d.y = ROCK_MAX_FALL;
  push = PushoutToUp1(s->coord.x, s->coord.y);
  if (push < 0) {
    s->coord.y += push;
    dropGone(p);
    return;
  }
  UpdateSpriteAnimation(p);
}

// 0x080a0098: drips warning, lets go, bounces once
static void Drop_Rock(struct BlobDrop* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 push;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, ARMOR_HITBOX(22));
      s->flags &= ~DISPLAY;
      s->work[2] = 128;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      if (s->work[2] == 0) s->mode[2]++;
      if ((s->work[2] & 31) == 0) {
        at.x = s->coord.x + (RANDOM(RNG_0202f388) & 0xFFF) - PIXEL(8);
        at.y = s->coord.y;
        createDrop(NULL, 4, &at, 0);
      }
      s->work[2] -= 2;
      return;
    case 2:
      SetDDP(&p->body, ARMOR_HITBOX(21));
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, ROCK(RANDOM(RNG_0202f388) & 1));
      s->work[2] = 0;
      s->work[3] = 0;
      s->d.y = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      s->coord.y += s->d.y;
      s->d.y += ROCK_GRAVITY;
      if (s->d.y > ROCK_MAX_FALL) s->d.y = ROCK_MAX_FALL;
      if (s->work[2] == 0) {
        push = PushoutToUp1(s->coord.x, s->coord.y);
        if (push < 0) {
          EXIT_BODY(p);
          s->work[2] = 1;
          s->coord.y += push;
          s->d.y = -s->d.y >> 1;
        }
      } else {
        s->work[3]++;
        if (s->work[3] & 2) {
          s->flags |= DISPLAY;
        } else {
          s->flags &= ~DISPLAY;
        }
        if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(32)) {
          dropGone(p);
          return;
        }
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0809f924
static void Drop_Update(struct BlobDrop* p) {
  switch ((p->s).mode[1]) {
    case DROP_ARMOR: Drop_Armor(p); break;
    case DROP_SPLASH: Drop_Splash(p); break;
    case DROP_SPIRAL: Drop_Spiral(p); break;
    case DROP_FALL: Drop_Fall(p); break;
    case DROP_ROCK: Drop_Rock(p); break;
  }
}

// --------------------------------------------

static void Splat_Init(struct BlobSplat* p);
static void Splat_Update(struct BlobSplat* p);
static void Splat_Die(struct BlobSplat* p);

// clang-format off
const ProjectileRoutine gApZ2BlobSplatRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Splat_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Splat_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Splat_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a0344, 0x080a03a4
static void createSplat(struct Entity* boss, const Coords32* at, const Coords32* v, u8 kind, u8 arg) {
  struct BlobSplat* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BLOB_SPLAT);
    (p->s).work[0] = kind;
    (p->s).work[2] = arg;
    (p->s).unk_28 = boss;
    (p->s).coord = *at;
    (p->s).d = *v;
  }
}

// 0x080a0400
static void createDrip(const Coords32* at, s32 reach, u8 frames, bool8 sounds) {
  struct BlobSplat* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_BLOB_SPLAT);
    (p->s).work[0] = 2;
    (p->s).work[2] = frames;
    (p->s).work[3] = sounds;
    (p->s).coord = *at;
    p->reach = reach;
  }
}

// 0x080a05f4
static void Splat_Init(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  static const u8 sStart[3] = {SPLAT_BOUNCE, SPRAY_FLY, DRIP_FALL};
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = sStart[s->work[0]];
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] != 2) INIT_BODY(p, sSplatCollisions, 0, NULL);
  p->gone = FALSE;
  Splat_Update(p);
}

static void splatGone(struct BlobSplat* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

static void shrink(struct BlobSplat* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_DIE); }

static void towardBoss(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  bool8 right = ((struct Entity*)s->unk_28)->coord.x > s->coord.x;
  s->d.x = right ? 0x180 : -0x180;
  SET_XFLIP(p, right);
}

static void reachBoss(struct BlobSplat* p, s32 near, u8 worth) {
  struct Entity* s = &p->s;
  struct Blob* boss = (struct Blob*)s->unk_28;
  s32 d;
  s->coord.x += s->d.x;
  d = (boss->s).coord.x - s->coord.x;
  if (d < 0) d = -d;
  if (d < near) {
    PlaySound(SE_Z2_BLOB_HOP);
    boss->returned += worth;
    splatGone(p);
    return;
  }
  UpdateSpriteAnimation(p);
}

static void prepare(struct Entity* s, motion_t motion) {
  InitNonAffineMotion(s);
  useSheet(s);
  (s->spr).oam.priority = 3;
  SetSpriteAnimation(s, motion);
}

// 0x080a06dc
static void Splat_Bounce(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  struct Blob* boss = (struct Blob*)s->unk_28;
  u8 hit;
  if (s->mode[2] == 0) {
    prepare(s, SPLAT(0));
    SET_XFLIP(p, s->work[2]);
    SetDDP(&p->body, SPLAT_HITBOX(0));
    s->work[2] = 0;
    s->mode[2]++;
  }
  fall(s, GRAVITY, MAX_FALL);
  hit = probe(s, PIXEL(8), PIXEL(8), PIXEL(8));
  if (hit & 1) {
    PlaySound(SE_Z2_BLOB_BOUNCE);
    s->d.y = -0x400;
    if (++s->work[2] == 2 || (boss->signals & SIGNAL_POOL)) {
      s->mode[1] = SPLAT_POOL;
      s->mode[2] = 0;
    }
    if (p->gone) {
      shrink(p);
      return;
    }
  }
  if (hit & 2) s->d.x = -s->d.x;
  if (hit & 8) s->d.y = -s->d.y;
  UpdateSpriteAnimation(p);
}

// 0x080a0804
static void Splat_Pool(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, SPLAT_HITBOX(1));
    SetSpriteAnimation(p, SPLAT(1));
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    s->mode[2]++;
  }
  if (((struct Blob*)s->unk_28)->signals & SIGNAL_HOME) {
    s->mode[1] = SPLAT_HOME;
    s->mode[2] = 0;
  }
  UpdateSpriteAnimation(p);
  if (p->gone) shrink(p);
}

// 0x080a0884
static void Splat_Home(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if (p->gone) {
    shrink(p);
    return;
  }
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SPLAT(2));
    towardBoss(p);
    SetDDP(&p->body, SPLAT_HITBOX(1));
    s->mode[2]++;
  }
  reachBoss(p, PIXEL(8), 4);
}

// 0x080a09a8
static void Spray_Fly(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    prepare(s, SPLAT(3));
    SET_XFLIP(p, s->d.x > 0);
    SetDDP(&p->body, SPLAT_HITBOX(2));
    s->mode[2]++;
  }
  fall(s, GRAVITY, MAX_FALL);
  if (probe(s, PIXEL(4), PIXEL(4), PIXEL(2)) & 3) {
    PlaySound(SE_Z2_TANK_EXPLODE);
    CreateSmoke(1, &s->coord);
    s->mode[1] = SPRAY_POOL;
    s->mode[2] = 0;
  }
  UpdateSpriteAnimation(p);
}

// 0x080a0a80
static void Spray_Pool(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 8;
    s->mode[2]++;
  }
  if (s->work[2] != 0) {
    SetDDP(&p->body, SPLAT_HITBOX(3));
    s->work[2]--;
  } else {
    SetDDP(&p->body, SPLAT_HITBOX(2));
  }
  if (((struct Blob*)s->unk_28)->signals & SIGNAL_HOME) {
    s->mode[1] = SPRAY_HOME;
    s->mode[2] = 0;
  }
  UpdateSpriteAnimation(p);
  if (p->gone) shrink(p);
}

// 0x080a0b0c
static void Spray_Home(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if (p->gone) {
    shrink(p);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, SPLAT_HITBOX(2));
      s->d.y = 0x180;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->coord.y += s->d.y;
      if (probe(s, PIXEL(4), PIXEL(4), PIXEL(2)) & 1) s->mode[2]++;
      break;
    case 2:
      towardBoss(p);
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      reachBoss(p, PIXEL(16), 1);
      break;
  }
}

// 0x080a0c60
static void Drip_Fall(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  s32 push;
  switch (s->mode[2]) {
    case 0:
      prepare(s, SPLAT(3));
      s->d.y = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->coord.y += s->d.y;
      s->d.y += ROCK_GRAVITY;
      push = PushoutToUp1(s->coord.x, s->coord.y + p->reach);
      if (push < 0) {
        if (s->work[3] != 0) PlaySound(SE_Z2_BLOB_HOP);
        s->coord.y += push;
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) splatGone(p);
      break;
  }
}

// 0x080a0668
static void Splat_Update(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & BODY_STATUS_WHITE) (p->body).hp = 20;
  if (!p->gone && s->work[0] != 2 && dying((struct Entity*)s->unk_28)) {
    p->gone = TRUE;
    EXIT_BODY(p);
  }
  switch (s->mode[1]) {
    case SPLAT_BOUNCE: Splat_Bounce(p); break;
    case SPLAT_POOL: Splat_Pool(p); break;
    case SPLAT_HOME: Splat_Home(p); break;
    case SPRAY_FLY: Spray_Fly(p); break;
    case SPRAY_POOL: Spray_Pool(p); break;
    case SPRAY_HOME: Spray_Home(p); break;
    case DRIP_FALL: Drip_Fall(p); break;
  }
}

// 0x080a0d34: lingers, then shrinks away
static void Splat_Die(struct BlobSplat* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      InitRotatableMotion(s);
      useSheet(s);
      (s->spr).oam.priority = 3;
      if (s->work[0] == 0) {
        s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
        SetSpriteAnimation(p, SPLAT(1));
      } else {
        SetSpriteAnimation(p, SPLAT(3));
      }
      s->work[2] = 60;
      EXIT_BODY(p);
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      if (--s->work[2] == 0) s->mode[1]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      s->work[2] = 254;
      s->mode[1]++;
      FALLTHROUGH;
    case 3:
      (s->spr).mag.x = s->work[2];
      (s->spr).mag.y = s->work[2];
      s->work[2] -= 2;
      if (s->work[2] == 0) {
        s->flags &= ~DISPLAY;
        SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// --------------------------------------------

// clang-format off
static const struct Collision sCollisions[76] = {
    /* 0x833b87c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1800, 0x2000, 0x3000}},
    /* 0x833b894 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
    /* 0x833b8ac */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {-0xc00, -0x800, 0x2000, 0x1000}},
    /* 0x833b8c4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x1c00, -0x1400, 0xa00, 0xa00}},
    /* 0x833b8dc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x1000, 0x2000, 0x2000}},
    /* 0x833b8f4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x2000}},
    /* 0x833b90c */ {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x1000, 0x2000, 0x2000}},
    /* 0x833b924 */ {DRP, FACTION_ENEMY, 2, 255, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {0x0, -0x1000, 0x2000, 0x2000}},
    /* 0x833b93c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x2600, 0x1c00, 0x4c00}},
    /* 0x833b954 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x4200, 0xa00, 0xa00}},
    /* 0x833b96c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x800, 0x4000, 0x1000}},
    /* 0x833b984 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x800, 0xa00, 0xa00}},
    /* 0x833b99c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0xc00, 0x3000, 0x1800}},
    /* 0x833b9b4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x1400, 0xa00, 0xa00}},
    /* 0x833b9cc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {-0xc00, -0x800, 0x2000, 0x1000}},
    /* 0x833b9e4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x2600, -0x1400, 0xa00, 0xa00}},
    /* 0x833b9fc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x700, 0x2000, 0xe00}},
    /* 0x833ba14 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x1e00, -0xf00, 0xa00, 0xa00}},
    /* 0x833ba2c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x700, 0x2000, 0xe00}},
    /* 0x833ba44 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x1200, -0xb00, 0xa00, 0xa00}},
    /* 0x833ba5c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x700, 0x2000, 0xe00}},
    /* 0x833ba74 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x600, -0xb00, 0xa00, 0xa00}},
    /* 0x833ba8c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x700, 0x2000, 0xe00}},
    /* 0x833baa4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {0x200, -0x1100, 0xa00, 0xa00}},
    /* 0x833babc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 1, 0x00000001, {0x0, -0x700, 0x2000, 0xe00}},
    /* 0x833bad4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x21, 0, 0x00000000, {-0x300, -0x1400, 0xa00, 0xa00}},
    /* 0x833baec */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x1800}},
    /* 0x833bb04 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xa00, -0x600, 0xa00, 0xa00}},
    /* 0x833bb1c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1400, 0x1400}},
    /* 0x833bb34 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xa00, 0xa00}},
    /* 0x833bb4c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x833bb64 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xa00, 0xa00}},
    /* 0x833bb7c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x800, 0x2000, 0x1000}},
    /* 0x833bb94 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x400, -0xd00, 0xa00, 0xa00}},
    /* 0x833bbac */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x600, 0x1800, 0xc00}},
    /* 0x833bbc4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x600, 0xa00, 0xa00}},
    /* 0x833bbdc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0xc00, 0x3000, 0x1800}},
    /* 0x833bbf4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x400, -0x1c00, 0xa00, 0xa00}},
    /* 0x833bc0c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1300, 0x1c00, 0x2600}},
    /* 0x833bc24 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2400, 0xa00, 0xa00}},
    /* 0x833bc3c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1b00, 0x1c00, 0x3600}},
    /* 0x833bc54 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x900, -0x3900, 0xa00, 0xa00}},
    /* 0x833bc6c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x2000, 0x1c00, 0x4000}},
    /* 0x833bc84 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xa00, -0x4000, 0xa00, 0xa00}},
    /* 0x833bc9c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x2800, 0x1c00, 0x5000}},
    /* 0x833bcb4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x800, -0x4e00, 0xa00, 0xa00}},
    /* 0x833bccc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x3800, 0x1c00, 0x7000}},
    /* 0x833bce4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0xd00, -0x6a00, 0xa00, 0xa00}},
    /* 0x833bcfc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x5400, 0x1c00, 0x3800}},
    /* 0x833bd14 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x200, -0x6c00, 0xa00, 0xa00}},
    /* 0x833bd2c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x6600, 0x2000, 0x1800}},
    /* 0x833bd44 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xa00, -0x6a00, 0xa00, 0xa00}},
    /* 0x833bd5c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x80, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {-0x1a00, -0x1400, 0x5800, 0x2800}},
    /* 0x833bd74 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xa00, -0x2b00, 0xa00, 0xa00}},
    /* 0x833bd8c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x80, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {-0xe00, -0x1400, 0x3c00, 0x2800}},
    /* 0x833bda4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xe00, -0x2b00, 0xa00, 0xa00}},
    /* 0x833bdbc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0xc00, 0x1800, 0x1800}},
    /* 0x833bdd4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xb00, -0x1e00, 0xa00, 0xa00}},
    /* 0x833bdec */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1900, 0x800, 0x3200}},
    /* 0x833be04 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x200, -0x3700, 0xa00, 0xa00}},
    /* 0x833be1c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0xe00, 0x1000, 0x1c00}},
    /* 0x833be34 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x100, -0x2200, 0xa00, 0xa00}},
    /* 0x833be4c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x600, 0x1c00, 0xc00}},
    /* 0x833be64 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x500, 0xa00, 0xa00}},
    /* 0x833be7c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x600, 0x1c00, 0xc00}},
    /* 0x833be94 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0xd00, 0xa00, 0xa00}},
    /* 0x833beac */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, -0x600, 0x1c00, 0xc00}},
    /* 0x833bec4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0xb00, 0xa00, 0xa00}},
    /* 0x833bedc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2800, 0x1400}},
    /* 0x833bef4 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x1400, 0x0, 0xa00, 0xa00}},
    /* 0x833bf0c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x1000}},
    /* 0x833bf24 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0xc00, 0x0, 0xa00, 0xa00}},
    /* 0x833bf3c */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
    /* 0x833bf54 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
    /* 0x833bf6c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x1800, 0x2000, 0x3000}},
    /* 0x833bf84 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x2b00, 0xa00, 0xa00}},
};

static const struct Collision sDropCollisions[46] = {
    /* 0x8343f10 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1400, 0x1400}},
    /* 0x8343f28 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1400, 0x1400}},
    /* 0x8343f40 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x600, 0x1800, 0xc00}},
    /* 0x8343f58 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x600, 0x1800, 0xc00}},
    /* 0x8343f70 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0xe00, 0x2000}},
    /* 0x8343f88 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0xe00, 0x2000}},
    /* 0x8343fa0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x800, 0x800}},
    /* 0x8343fb8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x800, 0x800}},
    /* 0x8343fd0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2300, 0x800, 0x3200}},
    /* 0x8343fe8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2300, 0x800, 0x3200}},
    /* 0x8344000 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x500, 0x800, 0xa00}},
    /* 0x8344018 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x500, 0x800, 0xa00}},
    /* 0x8344030 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x800, 0x1c00}},
    /* 0x8344048 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x800, 0x1c00}},
    /* 0x8344060 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x800, 0x1400}},
    /* 0x8344078 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x800, 0x1400}},
    /* 0x8344090 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2200, 0x800, 0x1c00}},
    /* 0x83440a8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2200, 0x800, 0x1c00}},
    /* 0x83440c0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0x800, 0x1a00}},
    /* 0x83440d8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0x800, 0x1a00}},
    /* 0x83440f0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0xb00, 0xe00, 0x1600}},
    /* 0x8344108 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0xb00, 0xe00, 0x1600}},
    /* 0x8344120 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0xe00, 0x2000}},
    /* 0x8344138 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1000, 0xe00, 0x2000}},
    /* 0x8344150 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1800, 0xe00, 0x3000}},
    /* 0x8344168 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1800, 0xe00, 0x3000}},
    /* 0x8344180 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1e00, 0xe00, 0x3c00}},
    /* 0x8344198 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1e00, 0xe00, 0x3c00}},
    /* 0x83441b0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2300, 0xe00, 0x4600}},
    /* 0x83441c8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x2300, 0xe00, 0x4600}},
    /* 0x83441e0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x3200, 0xe00, 0x6400}},
    /* 0x83441f8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x3200, 0xe00, 0x6400}},
    /* 0x8344210 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x5200, 0xe00, 0x2800}},
    /* 0x8344228 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x5200, 0xe00, 0x2800}},
    /* 0x8344240 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x6000, 0xe00, 0xa00}},
    /* 0x8344258 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x6000, 0xe00, 0xa00}},
    /* 0x8344270 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xe00, 0x1000}},
    /* 0x8344288 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xe00, 0x1000}},
    /* 0x83442a0 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x700, -0x2200, 0xd00, 0x4200}},
    /* 0x83442b8 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xe00, 0x1000}},
    /* 0x83442d0 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x400, -0x1800, 0xd00, 0x2b00}},
    /* 0x83442e8 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xe00, 0x1000}},
    /* 0x8344300 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x800, 0x1000, 0x1000}},
    /* 0x8344318 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x600, 0x1800, 0xc00}},
    /* 0x8344330 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x600, 0x1800, 0xc00}},
    /* 0x8344348 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x600, 0x1800, 0xc00}},
};

static const struct Collision sSplatCollisions[8] = {
    /* 0x83443bc */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x83443d4 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x83443ec */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x400, 0x1000, 0x800}},
    /* 0x8344404 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x400, 0x1000, 0x800}},
    /* 0x834441c */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    /* 0x8344434 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
    /* 0x834444c */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    /* 0x8344464 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

#endif
