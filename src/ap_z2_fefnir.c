#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "palette_animation.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/motion/static.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's Fefnir, boss 15.
  Parts:
    39: turrets, two on top, two cannons below
    40: top turrets' lob
    42: wheels
*/

struct Fefnir {
  OBJECT_HDR;
  s32 homeX;                // 0xB4
  s32 homeY;                // 0xB8
  bool8 hitFromRight;       // 0xBC
  u8 pattern;               // 0xBD, next attack, 4 once all turrets broken
  u8 order;                 // 0xBE, for turrets
  u8 quakeTimer;            // 0xBF
  u8 delay[4];              // 0xC0, by turret, delay before order
  struct Entity* parts[4];  // 0xC4, turrets by work0
  u32 stopped;              // 0xD4, frames tank stands still
  u16 dieTimer;             // 0xD8
  u8 hurt;                  // 0xDA, frames of hurt pose
  u8 broken;                // 0xDB, turrets broken
  u8 _dc[8];
};
static_assert(sizeof(struct Fefnir) == sizeof(struct Boss));

/*
  Turret orders
  1: appear
  2: all fire in turn
  3: top turrets lob
  4: lower front cannon volleys
  5, 6: all fire at once, intact (5) or broken (6)
*/
enum { FEFNIR_WAIT, FEFNIR_SUMMON, FEFNIR_NOP, FEFNIR_PICK, FEFNIR_PAUSE, FEFNIR_ORDER2,
       FEFNIR_ORDER3, FEFNIR_ORDER4, FEFNIR_ORDER5, FEFNIR_ORDER6 };

#define FEFNIR(n) MOTION(DM201_Z2_FEFNIR, (n))
#define TANK(n) MOTION(AP_SHEET_Z2_FEFNIR_TANK, (n))

// Creeps left to here
#define TANK_END PIXEL(480)

extern const PlttAnimData gApZ2Na1_PlttAnim129, gApZ2Na1_PlttAnim130, gApZ2Na1_PlttAnim131;
extern const AnimCmd* const gApZ2Na1_PlttAnimScript129[], *const gApZ2Na1_PlttAnimScript130[],
    *const gApZ2Na1_PlttAnimScript131[];
#define PLTT_ANIM_ID(n) (0x8000 | (n))

static const struct Collision sCollisions[2];
static const struct Collision sPartCollisions[8];
static const struct Collision sWheelCollision;
static const struct Collision sNoHitbox;
static const Coords32 sElementCoord = {PIXEL(4), -PIXEL(50)};

// Loaded at init and summon. Tank takes over boss window.
static const struct PreloadEntity sFireSheet = {AP_SHEET_Z2_FEFNIR_FIRE, 0, 512 + AP_SHEET_Z2_FEFNIR_TANK_TILES + AP_SHEET_Z2_FEFNIR_WHEELS_TILES, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWheelSheet = {AP_SHEET_Z2_FEFNIR_WHEELS, 0, 512 + AP_SHEET_Z2_FEFNIR_TANK_TILES, 5, 0, AP_PRELOAD_SHEET, 0};
// Doors' and containers' window, unused here
static const struct PreloadEntity sBallSheet = {AP_SHEET_Z2_FEFNIR_BALL, 0, 380, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sFlashSheet = {AP_SHEET_Z2_FEFNIR_FLASH, 0, 380 + AP_SHEET_Z2_FEFNIR_BALL_TILES, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSummonSheet = {AP_SHEET_Z2_FEFNIR_SUMMON, 0, 576, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sTankSheet = {AP_SHEET_Z2_FEFNIR_TANK, 0, 512, 4, 0, AP_PRELOAD_SHEET, 0};

static void Fefnir_Init(struct Fefnir* p);
static void Fefnir_Update(struct Fefnir* p);
static void Fefnir_Die(struct Fefnir* p);
static void Fefnir_Disappear(struct Fefnir* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static struct Entity* createPart(struct Fefnir* boss, u8 n);
static struct Entity* createWheels(struct Fefnir* boss);
struct Entity* ApZ2CreateBubble(const Coords32* at, bool8 blue);
void ApZ2CreateSpark(const Coords32* at, u8 angle);
static struct Entity* createFire(struct Entity* parent, const Coords32* ofs, u8 kind, u8 n);
static void createBall(const Coords32* at, u8 n, u8 work1);
static void createSmoke(struct Entity* parent, const Coords32* ofs, u8 kind, u8 n);
void ApZ2CreateExplosion(struct Entity* parent, const Coords32* at, u8 kind, u8 roll);

// clang-format off
const BossRoutine gApZ2FefnirRoutine = {
    [ENTITY_INIT] =      (BossFunc)Fefnir_Init,
    [ENTITY_UPDATE] =    (BossFunc)Fefnir_Update,
    [ENTITY_DIE] =       (BossFunc)Fefnir_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Fefnir_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setMode(struct Entity* p, u8 mode) {
  p->mode[1] = mode;
  p->mode[2] = 0;
}

// 0x0805cb44
static void Fefnir_Init(struct Fefnir* p) {
  struct Entity* s = &p->s;
  struct ApZ2LavaShrineState* w = &gOverworld.work.apZ2LavaShrine;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetSpriteAnimation(p, FEFNIR(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, 96);
  (p->body).fn = onCollision;
  w->fefnir = s;
  s->coord.x += PIXEL(196);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  s->unk_28 = NULL;
  w->tank = FALSE;
  p->quakeTimer = 64;
  p->hurt = 0;
  p->order = 0;
  p->stopped = 0;
  p->broken = 0;
  s->unk_2c = NULL;
  ApLoadSheet(&sFireSheet);
  ApLoadSheet(&sWheelSheet);
  ApLoadSheet(&sBallSheet);
  ApLoadSheet(&sFlashSheet);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, FEFNIR_WAIT);
  Fefnir_Update(p);
}

static const BossFunc sFefnirStates[10];

// 0x0805ccc0
static void Fefnir_Update(struct Fefnir* p) {
  struct Entity* s = &p->s;
  struct ApZ2LavaShrineState* w = &gOverworld.work.apZ2LavaShrine;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Fefnir_Die(p);
    return;
  }
  if (p->stopped != 0) p->stopped--;
  if (s->mode[1] > FEFNIR_NOP) {
    if ((p->body).status & BODY_STATUS_WHITE) {
      if (s->unk_2c != NULL || (s->unk_2c = ApplyElementEffect(22, (Object*)p, &sElementCoord)) != NULL) {
        PlaySound(SE_Z2_FEFNIR_HURT);
      }
      SetSpriteAnimation(p, TANK(54));
      p->hurt = 64;
    }
    if (p->hurt != 0) {
      if (--p->hurt == 0) {
        SetSpriteAnimation(p, TANK(53));
        p->quakeTimer = (u8)(RANDOM(RNG_0202f388) % 190 + 63);
      }
    } else if (--p->quakeTimer == 0) {
      SetSpriteAnimation(p, TANK(53));
      AppendQuake(1, &s->coord);
      p->quakeTimer = (u8)(RANDOM(RNG_0202f388) % 190 + 63);
    }
    s->d.x = (p->stopped != 0) ? 0 : -128;
    if (s->coord.x < TANK_END) s->d.x = 0;
    s->coord.x += s->d.x;
  }
  if (s->unk_2c != NULL && isKilled(s->unk_2c)) s->unk_2c = NULL;
  (sFefnirStates[s->mode[1]])((struct Boss*)p);
  w->tankX = s->coord.x;
  w->tankY = s->coord.y;
}

// 0x0805ce7c: explodes until clear script destroys him
static void Fefnir_Die(struct Fefnir* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(54));
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    PlaySound(SE_Z2_TANK_EXPLODE);
    p->dieTimer = 0;
    s->work[2] = 128;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (p->dieTimer++ > 64) {
    if ((p->dieTimer & 3) == 0) {
      at.x = s->coord.x + PIXEL(32 - (RANDOM(RNG_0202f388) & 63));
      at.y = s->coord.y + PIXEL(16 - (RANDOM(RNG_0202f388) & 63));
      ApZ2CreateExplosion(s, &at, 2, (u8)RANDOM(RNG_0202f388));
    }
    if ((p->dieTimer & 15) == 0) PlaySound(SE_Z2_TANK_EXPLODE);
  }
  if (p->dieTimer & 1) {
    PaintEntityWhite(s);
  } else {
    UpdateEntityPaletteID(s);
  }
  if (s->mode[1] == 0 && --s->work[2] == 0xFF) {
    gStageRun.vm.active |= VM_FLAG1;
    s->mode[1]++;
  }
}

// 0x0805cfe8
static void Fefnir_Disappear(struct Fefnir* p) {
  gOverworld.work.apZ2LavaShrine.tank = FALSE;
  DeleteBoss(&p->s);
}

// 0x0805d004: waits for script
static void Fefnir_Wait(struct Fefnir* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 16;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] == 0 && (s->scriptEntity->flags & 1)) setMode(s, FEFNIR_SUMMON);
}

static void fadeIn(void) {
  ApStartPaletteAnimation(PLTT_ANIM_ID(129), &gApZ2Na1_PlttAnim129, gApZ2Na1_PlttAnimScript129, 0x280);
  ApStartPaletteAnimation(PLTT_ANIM_ID(130), &gApZ2Na1_PlttAnim130, gApZ2Na1_PlttAnimScript130, 0x2A0);
  ApStartPaletteAnimation(PLTT_ANIM_ID(131), &gApZ2Na1_PlttAnim131, gApZ2Na1_PlttAnimScript131, 0x120);
}

// 0x0805d040: calls tank in bubble, fades in around him
static void Fefnir_Summon(struct Fefnir* p) {
  struct Entity* s = &p->s;
  struct Entity* b;
  Coords32 at;
  u8 i;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, FEFNIR(22));
    PlaySound(SE_Z2_FEFNIR_SUMMON);
    s->work[2] = 16;
    s->work[3] = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[3]) {
    case 0:
      if (!IsSpriteAnimEnd(p)) break;
      at.x = s->coord.x;
      at.y = s->coord.y - PIXEL(16);
      s->unk_28 = ApZ2CreateBubble(&at, FALSE);
      s->work[2] = 0;
      ApLoadSheet(&sSummonSheet);
      PlaySound(SE_Z2_FEFNIR_BUBBLE);
      s->mode[3]++;
      break;
    case 1:
      b = s->unk_28;
      if (b->mode[3] == 0) {
        if (s->work[2]++ & 1) {
          s->flags |= DISPLAY;
          break;
        }
        s->flags &= ~DISPLAY;
        at.x = s->coord.x;
        at.y = s->coord.y - PIXEL(16);
        ApZ2CreateSpark(&at, (u8)(((s->work[2] >> 1) << 6) + (RANDOM(RNG_0202f388) & 63)));
      } else if (b->mode[3] == 1) {
        s->flags = (s->work[2]++ & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
        s->work[3] = 0;
      } else if (b->mode[3] == 2) {
        s->flags |= DISPLAY;
        ApLoadSheet(&sTankSheet);
        gOverworld.work.apZ2LavaShrine.tank = TRUE;
        s->flags2 &= ~DYNAMIC;
        useApSheets(p);
        SetSpriteAnimation(p, TANK(52));
        UpdateSpriteAnimation(p);
        s->d.x = 0;
        createWheels(p);
        for (i = 0; i < 4; i++) {
          p->parts[i] = createPart(p, i);
        }
        fadeIn();
        StepPaletteAnimation(PLTT_ANIM_ID(129));
        StepPaletteAnimation(PLTT_ANIM_ID(130));
        StepPaletteAnimation(PLTT_ANIM_ID(131));
        s->mode[3]++;
      }
      break;
    case 2:
      if (s->unk_28->mode[0] > ENTITY_UPDATE) {
        p->order = 1;
        s->work[2] = 24;
        s->mode[3]++;
      }
      break;
    case 3:
      if (--s->work[2] == 0xFF) s->mode[3]++;
      break;
    case 4:
      StepPaletteAnimation(PLTT_ANIM_ID(129));
      StepPaletteAnimation(PLTT_ANIM_ID(130));
      if (StepPaletteAnimation(PLTT_ANIM_ID(131)) == 3) {
        RemovePaletteAnimation(PLTT_ANIM_ID(129));
        RemovePaletteAnimation(PLTT_ANIM_ID(130));
        RemovePaletteAnimation(PLTT_ANIM_ID(131));
        s->work[2] = 32;
        p->order = 0;
        s->mode[3]++;
      }
      break;
    case 5:
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, FEFNIR_PICK);
      break;
  }
}

static void Fefnir_Nop(struct Fefnir* p UNUSED) {}

static bool8 partBroken(struct Fefnir* p, u8 n) { return p->parts[n]->work[1] != 0; }

// 0x0805d358: once all turrets idle, picks next order
static void Fefnir_Pick(struct Fefnir* p) {
  struct Entity* s = &p->s;
  u8 i, broken = 0;
  UpdateSpriteAnimation(p);
  for (i = 0; i < 4; i++) {
    if (partBroken(p, i)) broken++;
    if (p->parts[i]->mode[1] != 2) return;
  }
  if (broken == 4) p->pattern = 4;
  switch (p->pattern) {
    case 0:
      s->mode[1] = FEFNIR_ORDER2;
      p->pattern++;
      break;
    case 1:
      if (!partBroken(p, 0) || !partBroken(p, 1)) s->mode[1] = FEFNIR_ORDER3;
      p->pattern++;
      break;
    case 2:
      if (gScore.total->rank > 4 && !partBroken(p, 2)) s->mode[1] = FEFNIR_ORDER4;
      p->pattern++;
      break;
    case 3:
      s->mode[1] = FEFNIR_ORDER5;
      p->pattern = 0;
      break;
    default:
      s->mode[1] = FEFNIR_ORDER6;
      p->pattern = 0;
      break;
  }
  s->mode[2] = 0;
}

// 0x0805d408
static void Fefnir_Pause(struct Fefnir* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(52));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, FEFNIR_PICK);
}

// Order lasts a frame, turrets read it when idle
static bool8 ordered(struct Fefnir* p) {
  if ((p->s).mode[2] == 0) return FALSE;
  p->order = 0;
  setMode(&p->s, FEFNIR_PICK);
  return TRUE;
}

// 0x0805d44c: turrets fire in random order, 48 frames apart
static void Fefnir_Order2(struct Fefnir* p) {
  struct Entity* s = &p->s;
  u8 n = 0xFF;
  if (!ordered(p)) {
    p->order = 2;
    s->work[3] = 0;
    p->delay[0] = p->delay[1] = p->delay[2] = p->delay[3] = 0;
    while (!p->delay[0] || !p->delay[1] || !p->delay[2] || !p->delay[3]) {
      n = (n == 0xFF) ? (u8)RANDOM(RNG_0202f388) : n + 1;
      n &= 3;
      if (p->delay[n] != 0) continue;
      if (partBroken(p, n)) {
        p->delay[n] = 0xFF;
      } else {
        p->delay[n] = s->work[3] * 48 + 1;
        s->work[3]++;
      }
      n = 0xFF;
    }
    s->work[2] = 0xFF;
    PlaySound(SE_Z2_FEFNIR_ORDER2);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
}

// 0x0805d534
static void Fefnir_Order3(struct Fefnir* p) {
  struct Entity* s = &p->s;
  if (!ordered(p)) {
    p->order = 3;
    p->delay[0] = p->delay[1] = 0;
    s->work[2] = 0xFF;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
}

// 0x0805d574
static void Fefnir_Order4(struct Fefnir* p) {
  struct Entity* s = &p->s;
  if (!ordered(p)) {
    p->order = 4;
    s->work[2] = 0xFF;
    PlaySound(SE_Z2_FEFNIR_ORDER4);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
}

// 0x0805d5b4, 0x0805d600
static void orderAll(struct Fefnir* p, u8 order) {
  struct Entity* s = &p->s;
  if (!ordered(p)) {
    p->order = order;
    s->work[3] = 0;
    p->delay[0] = 96;
    p->delay[1] = 32;
    p->delay[2] = 64;
    p->delay[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
}

static void Fefnir_Order5(struct Fefnir* p) { orderAll(p, 5); }

static void Fefnir_Order6(struct Fefnir* p) { orderAll(p, 6); }

static const BossFunc sFefnirStates[10] = {
    (BossFunc)Fefnir_Wait,   (BossFunc)Fefnir_Summon, (BossFunc)Fefnir_Nop,
    (BossFunc)Fefnir_Pick,   (BossFunc)Fefnir_Pause,  (BossFunc)Fefnir_Order2,
    (BossFunc)Fefnir_Order3, (BossFunc)Fefnir_Order4, (BossFunc)Fefnir_Order5,
    (BossFunc)Fefnir_Order6,
};

// 0x0805d64c
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* other = body->enemy->parent;
  struct Fefnir* p = (struct Fefnir*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) p->hitFromRight = other->coord.x > (p->s).coord.x;
}

// --------------------------------------------
/*
  Zero 2's enemy 39, tank's turrets.
  work0: turret
    0, 1: on top
    2, 3: below, front and back
  work1: broken
*/

struct Part {
  OBJECT_HDR;
  u8 _b4[9];
  u8 volley;                // 0xBD, frames into lower cannon's volley
  u8 _be[2];
  struct Entity* shot;      // 0xC0
};
static_assert(sizeof(struct Part) == sizeof(struct Enemy));

enum { PART_WAIT, PART_APPEAR, PART_IDLE, PART_FIRE_DELAY, PART_FIRE, PART_LOB_DELAY, PART_LOB,
       PART_LOB_END, PART_VOLLEY_START, PART_VOLLEY, PART_VOLLEY_END, PART_ALL_DELAY, PART_ALL,
       PART_BROKEN_DELAY, PART_BROKEN_FIRE, PART_DUCK, PART_DUCKED, PART_RISE };

#define TURRET(s, intact, broken) TANK(((s)->work[1] ? (broken) : (intact)) + (s)->work[0])

static void Part_Init(struct Part* p);
static void Part_Update(struct Part* p);
static void Part_Die(struct Part* p);
static void partOnCollision(struct Body* body, Coords32* r1, Coords32* r2);

// clang-format off
const EnemyRoutine gApZ2FefnirPartRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Part_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Part_Update,
    [ENTITY_DIE] =       (EnemyFunc)Part_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x083402e0: muzzles
static const Coords32 sMuzzles[4] = {
    {-PIXEL(6), -PIXEL(68)}, {-PIXEL(20), -PIXEL(66)}, {-PIXEL(12), -PIXEL(24)}, {-PIXEL(44), -PIXEL(25)},
};
// 0x08340300: top turrets' lob origin
static const Coords32 sLobs[2] = {{PIXEL(2), -PIXEL(104)}, {-PIXEL(14), -PIXEL(104)}};
// 0x08340310, 0x08340320: smoke spots while blowing up
static const s32 sSmokeX[4] = {PIXEL(24), PIXEL(10), PIXEL(20), -PIXEL(6)};
static const s32 sSmokeY[4] = {-PIXEL(84), -PIXEL(84), -PIXEL(60), -PIXEL(60)};
// 0x08340330
static const u8 sDieDelays[4] = {0, 96, 64, 32};

static struct Fefnir* bossOf(struct Part* p) { return (struct Fefnir*)(p->s).unk_28; }

static struct Entity* createPart(struct Fefnir* boss, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FEFNIR_PART);
    p->unk_28 = &boss->s;
    p->work[0] = n;
    p->work[1] = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
  }
  return p;
}

// 0x0807b2ec
static void Part_Init(struct Part* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] & 1) s->palID = 1;
  SetSpriteAnimation(p, TANK(0x3E + s->work[0]));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sPartCollisions[s->work[0] * 2], 48, partOnCollision);
  (s->spr).oam.priority = (s->work[0] & 1) ? 3 : 2;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

static const EnemyFunc sPartStates[2][18];

// 0x0807b3c8
static void Part_Update(struct Part* p) {
  struct Entity* s = &p->s;
  struct Fefnir* boss = bossOf(p);
  if ((boss->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Part_Die(p);
    return;
  }
  if (s->work[1] == 0 && ((p->body).status & BODY_STATUS_DEAD)) {
    if (++boss->broken == 4) PlaySound(SE_Z2_TANK_BROKEN);
    EXIT_BODY(p);
    s->work[1] = 1;
    s->mode[2] = 0;
  }
  s->coord = (boss->s).coord;
  if (boss->stopped != 0 && s->mode[1] < PART_DUCK) setMode(s, PART_DUCK);
  (sPartStates[s->work[1]][s->mode[1]])((struct Enemy*)p);
}

// 0x0807b480: smokes, then blows up
static void Part_Die(struct Part* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x2C + s->work[0]));
    s->work[2] = sDieDelays[s->work[0]] + 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord = (bossOf(p)->s).coord;
  if (s->mode[3] != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if ((s->work[2] & 7) == 0) {
    at.x = sSmokeX[s->work[0]];
    at.y = sSmokeY[s->work[0]];
    createSmoke(s, &at, 3, (RANDOM(RNG_0202f388) & 1) + 1);
  }
  if ((s->work[2] & 15) == 0) {
    at.x = s->coord.x + sSmokeX[s->work[0]];
    at.y = s->coord.y + sSmokeY[s->work[0]];
    ApZ2CreateExplosion(s, &at, 2, (u8)RANDOM(RNG_0202f388));
  }
  if (--s->work[2] == 0xFF) s->mode[3]++;
}

// 0x0807b5b0
static void Part_Wait(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (bossOf(p)->order == 1) setMode(s, PART_APPEAR);
}

// 0x0807b5e0
static void Part_Appear(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x42 + s->work[0]));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (bossOf(p)->order == 0) setMode(s, PART_IDLE);
}

// 0x0807b620
static void Part_Idle(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TURRET(s, 0x04, 0x24));
    if (s->work[1] == 0) SetDDP(&p->body, &sPartCollisions[s->work[0] * 2]);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (bossOf(p)->order) {
    case 2:
      setMode(s, PART_FIRE_DELAY);
      break;
    case 3:
      if (s->work[0] <= 1) setMode(s, PART_LOB_DELAY);
      break;
    case 4:
      if (s->work[0] == 2) setMode(s, PART_VOLLEY_START);
      break;
    case 5:
      setMode(s, PART_ALL_DELAY);
      break;
    case 6:
      setMode(s, PART_BROKEN_DELAY);
      break;
  }
}

// 0x0807b6cc, 0x0807bae4, 0x0807bb90
static void waitDelay(struct Part* p, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = bossOf(p)->delay[s->work[0]];
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, next);
}

static void Part_FireDelay(struct Part* p) { waitDelay(p, PART_FIRE); }

// 0x0807b708: muzzle flash, then fire until burned out
static void Part_Fire(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x08 + s->work[0]));
    createSmoke(s, &sMuzzles[s->work[0]], 0, s->work[0]);
    s->work[2] = 32;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (p->shot->mode[0] > ENTITY_UPDATE) setMode(s, PART_IDLE);
  } else if (--s->work[2] == 0xFF) {
    p->shot = createFire(s, &sMuzzles[s->work[0]], 0, s->work[0]);
    PlaySound(SE_Z2_SIGNALOID_FLAME);
    s->mode[3]++;
  }
}

// 0x0807b7cc: raises lobber, unhittable
static void Part_LobDelay(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = bossOf(p)->delay[s->work[0]];
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) setMode(s, PART_LOB);
  } else if (--s->work[2] == 0xFF) {
    SetSpriteAnimation(p, s->work[1] ? TANK(0x38 + 3 * s->work[0]) : TANK(0x0C + s->work[0]));
    SetDDP(&p->body, &sNoHitbox);
    s->work[2] = 24;
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
}

// 0x0807b86c
static void Part_Lob(struct Part* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    if (s->work[1] == 0) {
      SetSpriteAnimation(p, TANK(0x10 + s->work[0]));
      createSmoke(s, &sLobs[s->work[0]], 1, 0);
      at.x = s->coord.x + sLobs[s->work[0]].x;
      at.y = s->coord.y + sLobs[s->work[0]].y;
      createBall(&at, s->work[0], 0);
      PlaySound(SE_Z2_FEFNIR_LOB);
    }
    s->work[2] = 24;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, PART_LOB_END);
}

// 0x0807b914
static void Part_LobEnd(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, s->work[1] ? TANK(0x3A + 3 * s->work[0]) : TANK(0x12 + s->work[0]));
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, PART_IDLE);
}

// 0x0807b97c
static void Part_VolleyStart(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x12 + s->work[0]));
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(s, PART_VOLLEY);
}

// 0x0807b9c0: bobs, three shots every 81 frames, nine bobs at least
static void Part_Volley(struct Part* p) {
  static const Coords32 muzzle = {-PIXEL(4), -PIXEL(25)};
  struct Entity* s = &p->s;
  Coords32 none = {0, 0};
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x14 + s->work[0]));
    createSmoke(s, &none, 2, 0);
    s->work[3] = 0;
    s->work[2] = 0;
    p->volley = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->work[2] += 4;
  if (s->work[2] == 0) s->work[3]++;
  s->coord.y = (bossOf(p)->s).coord.y + (SIN(s->work[2]) << 3);
  switch (p->volley++) {
    case 64:
    case 72:
    case 80:
      createFire(s, &muzzle, 2, 0);
      PlaySound(SE_Z2_SIGNALOID_FIREBALL);
      break;
    case 81:
      if (s->work[3] <= 8) p->volley = 0;
      break;
  }
  if (s->work[3] > 8 && p->volley == 60) setMode(s, PART_VOLLEY_END);
}

// 0x0807baa4
static void Part_VolleyEnd(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x15 + s->work[0]));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(s, PART_IDLE);
}

static void Part_AllDelay(struct Part* p) { waitDelay(p, PART_ALL); }

// 0x0807bb20, 0x0807bbcc: shot from each intact (all) or broken turret
static void fireOnce(struct Part* p, bool8 broken, u8 kind) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if ((s->work[1] != 0) == broken) {
      createFire(s, &sMuzzles[s->work[0]], kind, 1);
      PlaySound(SE_Z2_SIGNALOID_FIREBALL);
    }
    s->work[2] = 48;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, PART_IDLE);
}

static void Part_All(struct Part* p) { fireOnce(p, FALSE, 2); }

static void Part_BrokenDelay(struct Part* p) { waitDelay(p, PART_BROKEN_FIRE); }

static void Part_BrokenFire(struct Part* p) { fireOnce(p, TRUE, 3); }

// 0x0807bc3c: charged hit stops tank, turrets duck until it moves
static void Part_Duck(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TURRET(s, 0x18, 0x28));
    SetDDP(&p->body, &sNoHitbox);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(s, PART_DUCKED);
}

// 0x0807bca4
static void Part_Ducked(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TURRET(s, 0x1C, 0x2C));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (bossOf(p)->stopped == 0) setMode(s, PART_RISE);
}

// 0x0807bd00
static void Part_Rise(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TURRET(s, 0x20, 0x30));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(s, PART_IDLE);
}

// 0x0807bd5c: broken turret, order it cannot carry out
static void Part_Broken(struct Part* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, TANK(0x24 + s->work[0]));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  setMode(s, PART_IDLE);
}

// 0x08340178
static const EnemyFunc sPartStates[2][18] = {
    {
        (EnemyFunc)Part_Wait,         (EnemyFunc)Part_Appear,      (EnemyFunc)Part_Idle,
        (EnemyFunc)Part_FireDelay,    (EnemyFunc)Part_Fire,        (EnemyFunc)Part_LobDelay,
        (EnemyFunc)Part_Lob,          (EnemyFunc)Part_LobEnd,      (EnemyFunc)Part_VolleyStart,
        (EnemyFunc)Part_Volley,       (EnemyFunc)Part_VolleyEnd,   (EnemyFunc)Part_AllDelay,
        (EnemyFunc)Part_All,          (EnemyFunc)Part_BrokenDelay, (EnemyFunc)Part_BrokenFire,
        (EnemyFunc)Part_Duck,         (EnemyFunc)Part_Ducked,      (EnemyFunc)Part_Rise,
    },
    {
        (EnemyFunc)Part_Broken,       (EnemyFunc)Part_Broken,      (EnemyFunc)Part_Idle,
        (EnemyFunc)Part_Broken,       (EnemyFunc)Part_Broken,      (EnemyFunc)Part_LobDelay,
        (EnemyFunc)Part_Lob,          (EnemyFunc)Part_LobEnd,      (EnemyFunc)Part_Broken,
        (EnemyFunc)Part_Broken,       (EnemyFunc)Part_Broken,      (EnemyFunc)Part_Broken,
        (EnemyFunc)Part_Broken,       (EnemyFunc)Part_BrokenDelay, (EnemyFunc)Part_BrokenFire,
        (EnemyFunc)Part_Duck,         (EnemyFunc)Part_Ducked,      (EnemyFunc)Part_Rise,
    },
};

// 0x0807bd94: charged blow stops tank
static void partOnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Part* p = (struct Part*)body->parent;
  if ((body->hitboxFlags & BODY_STATUS_WHITE) && (p->s).mode[1] < PART_DUCK && body->unk_23 == 10) {
    bossOf(p)->stopped = 128;
  }
}

// --------------------------------------------
// Zero 2's enemy 42, tank's wheels

static void Wheels_Init(struct Enemy* p);
static void Wheels_Update(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2FefnirWheelsRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Wheels_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Wheels_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEnemy,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static struct Entity* createWheels(struct Fefnir* boss) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FEFNIR_WHEELS);
    p->unk_28 = &boss->s;
  }
  return p;
}

// 0x0807ce40
static void Wheels_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FEFNIR_WHEELS, 0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sWheelCollision, 8, NULL);
  s->flags2 |= WHITE_PAINTABLE;
  s->invincibleID = s->unk_28->uniqueID;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Wheels_Update(p);
}

// 0x0807cee8
static void Wheels_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (boss->mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    DeleteEnemy(s);
    return;
  }
  if (boss->d.x != 0) UpdateSpriteAnimation(p);
  s->coord = boss->coord;
}

// --------------------------------------------
/*
  Zero 2's VFX 22 work0 2, bubble tank appears in. Circle is Zero 3's VFX 39.
*/

struct Bubble {
  struct Entity s;
  u8 _74[12];
  s32 radius;  // 0x80
};

struct Circle {
  struct Entity s;
  u8 rgb[3];
  bool8 done;
  s32 radius;
};

struct Entity* CreateVFX39(Coords32* c, u8 r1, u8 r2);

static void Bubble_Init(struct VFX* p);
static void Bubble_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FefnirBubbleRoutine = {
    [ENTITY_INIT] =      Bubble_Init,
    [ENTITY_UPDATE] =    Bubble_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b1d74
struct Entity* ApZ2CreateBubble(const Coords32* at, bool8 blue) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_BUBBLE);
    p->coord = *at;
    p->work[0] = blue;
  }
  return p;
}

// 0x080b1e24
static void Bubble_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  s->unk_28 = CreateVFX39(&s->coord, 1, 0);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Bubble_Update(p);
}

// 0x080b214e: white, then bigger red, whitening as it holds
static void drawCircle(struct Bubble* b) {
  struct Entity* s = &b->s;
  struct Circle* c = (struct Circle*)s->unk_28;
  u8 g = (s->work[3] >> 1 > 31) ? 31 : s->work[3] >> 1;
  if (c == NULL) return;
  if (s->work[2]++ & 1) {
    c->radius = b->radius;
    c->rgb[0] = c->rgb[1] = c->rgb[2] = 31;
  } else {
    c->radius = b->radius + PIXEL(4);
    c->rgb[0] = s->work[0] ? g : 31;
    c->rgb[1] = g;
    c->rgb[2] = s->work[0] ? 31 : g;
  }
}

// 0x080b2094
static void Bubble_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Bubble* b = (struct Bubble*)p;
  if (s->mode[2] == 0) {
    s->work[2] = s->work[3] = 0;
    b->radius = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      b->radius += 128;
      if (b->radius > (s->work[0] ? 0x4FFF : 0x3FFF)) {
        s->work[3] = 0;
        s->mode[3]++;
      }
      if (b->radius == PIXEL(24)) PlaySound(SE_Z2_FEFNIR_BUBBLE_GROW);
      break;
    case 1:
      if (s->work[3]++ > 64) s->mode[3]++;
      break;
    default:
      b->radius -= 0x180;
      if (b->radius <= 0) {
        if (s->unk_28 != NULL) ((struct Circle*)s->unk_28)->done = TRUE;
        SET_VFX_ROUTINE(p, ENTITY_DIE);
        return;
      }
      break;
  }
  drawCircle(b);
}

// --------------------------------------------
/*
  Zero 2's projectile 38, tank's fire.
  work0:
    0: flame, swells and shrinks eight times
    2: shot, slides left
    3: broken turret's smaller shot
  work1: slower shot
*/

static void Fire_Init(struct Projectile* p);
static void Fire_Update(struct Projectile* p);
static void Fire_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2FefnirFireRoutine = {
    [ENTITY_INIT] =      Fire_Init,
    [ENTITY_UPDATE] =    Fire_Update,
    [ENTITY_DIE] =       Fire_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sFireCollisions[16];
// 0x08344d78: flame hitbox by magnification / 16
static const u8 sFlameSizes[34] = {2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8,
                                   8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13};

#define FIRE(n) MOTION(AP_SHEET_Z2_FEFNIR_FIRE, (n))

// 0x080a4558
static struct Entity* createFire(struct Entity* parent, const Coords32* ofs, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FEFNIR_FIRE);
    p->unk_28 = parent;
    p->unk_coord = *ofs;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x080a462c, 0x080a4796, 0x080a4842
static void Fire_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 1 || s->work[0] == 2) {
    InitNonAffineMotion(s);
  } else {
    InitScalerotMotion1(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, FIRE(s->work[0] <= 1 ? s->work[0] : 2));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  switch (s->work[0]) {
    case 0:
      INIT_BODY(p, &sFireCollisions[0], 1, NULL);
      (s->spr).oam.priority = (s->work[1] & 1) ? 3 : 2;
      (s->spr).mag.x = (s->spr).mag.y = 16;
      s->work[3] = s->work[2] = 0;
      break;
    case 1:
      INIT_BODY(p, &sFireCollisions[0], 1, NULL);
      s->coord = s->unk_coord;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      break;
    case 2:
      INIT_BODY(p, &sFireCollisions[1], 1, NULL);
      s->coord.y = s->unk_28->coord.y + s->unk_coord.y;
      s->d.x = 0;
      s->work[2] = 0xFF;
      break;
    default:
      INIT_BODY(p, &sFireCollisions[15], 1, NULL);
      (s->spr).mag.x = (s->spr).mag.y = 128;
      s->coord.y = s->unk_28->coord.y + s->unk_coord.y;
      s->d.x = 0;
      s->work[2] = 0xFF;
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Fire_Update(p);
}

// 0x080a48f4: flame dies with turret ducking
static void flame(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  if (parent->mode[1] >= PART_DUCK) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = parent->coord.x + s->unk_coord.x;
  s->coord.y = parent->coord.y + s->unk_coord.y + PIXEL(s->work[3] & 1);
  s->work[3]++;
  switch (s->mode[1]) {
    case 0:
      (s->spr).mag.x += 16;
      (s->spr).mag.y += 16;
      if ((s->spr).mag.x > 0x1FF) s->mode[1] = (s->work[2]++ > 7) ? 2 : 1;
      break;
    case 1:
      (s->spr).mag.x -= 16;
      (s->spr).mag.y -= 16;
      if ((s->spr).mag.x > 0x17F) s->mode[1] = 0;
      break;
    case 2:
      (s->spr).mag.x -= 64;
      (s->spr).mag.y -= 64;
      if ((s->spr).mag.x <= 64) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        Fire_Die(p);
        return;
      }
      break;
  }
  SetDDP(&p->body, &sFireCollisions[sFlameSizes[(s->spr).mag.x >> 4]]);
}

// 0x080a4a50, 0x080a4af4: slides left from muzzle, blinks out
static void shot(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0 && IsSpriteAnimEnd(p)) {
    SetSpriteAnimation(p, FIRE(s->work[0] == 2 ? 4 : 3));
    s->mode[1]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = s->unk_28->coord.x + s->unk_coord.x + s->d.x;
  s->d.x += s->work[1] ? -0x200 : -0x380;
  if (s->work[2] <= 31) {
    s->flags = (s->work[2] & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
  }
  if (--s->work[2] == 0xFF) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Fire_Die(p);
  }
}

// 0x080a4a1c: burns out
static void groundFlame(struct Projectile* p) {
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Fire_Die(p);
  }
}

// 0x080a45cc: dies with tank, ground flame on its own
static void Fire_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 1) {
    groundFlame(p);
  } else if (s->unk_28->mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Fire_Die(p);
  } else if (s->work[0] == 0) {
    flame(p);
  } else {
    shot(p);
  }
}

// 0x080a4614
static void Fire_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
// Zero 2's VFX 67 work0 0, summon's sparks

static void Spark_Init(struct VFX* p);
static void Spark_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FefnirSparkRoutine = {
    [ENTITY_INIT] =      Spark_Init,
    [ENTITY_UPDATE] =    Spark_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bdae4
void ApZ2CreateSpark(const Coords32* at, u8 angle) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_SPARK);
    p->coord = *at;
    p->work[1] = angle;
  }
}

// 0x080bdb84: starts 24 steps out
static void Spark_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  s32 i;
  InitRotatableMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FEFNIR_SUMMON, 0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  s->d.x = s->d.y = 0;
  if (s->work[1] & 1) {
    s->unk_coord.x = COS(s->work[1]) / 6;
    s->unk_coord.y = SIN(s->work[1]) / 6;
  } else {
    s->unk_coord.x = COS(s->work[1]) / 4;
    s->unk_coord.y = SIN(s->work[1]) / 4;
  }
  s->work[2] = 8;
  for (i = 0; i < 24; i++) {
    s->d.x += s->unk_coord.x;
    s->d.y += s->unk_coord.y;
    s->coord.x += s->d.x;
    s->coord.y += s->d.y;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Spark_Update(p);
}

// 0x080bdefc: blinks, retraces way in, shrinking
static void Spark_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0) {
    (s->spr).mag.x = (s->spr).mag.y = 224;
    s->flags = (s->work[2] & 1) ? (s->flags & ~DISPLAY) : (s->flags | DISPLAY);
    if (--s->work[2] == 0xFF) {
      s->work[2] = 28;
      s->mode[1]++;
    }
    return;
  }
  (s->spr).mag.x = (s->spr).mag.y = s->work[2] * 8;
  s->coord.x -= s->d.x;
  s->coord.y -= s->d.y;
  s->d.x -= s->unk_coord.x;
  s->d.y -= s->unk_coord.y;
  if (--s->work[2] == 0) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------
/*
  Zero 2's VFX 39, tank's smoke.
  work0:
    0: muzzle smoke, drifts up
    1: lob's flash
    2: cannon's flash through volley
    3: broken turret's debris
  work1:
    0, 1: behind
    3: which piece
*/

static void Smoke_Init(struct VFX* p);
static void Smoke_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FefnirSmokeRoutine = {
    [ENTITY_INIT] =      Smoke_Init,
    [ENTITY_UPDATE] =    Smoke_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b6910
static void createSmoke(struct Entity* parent, const Coords32* ofs, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_SMOKE);
    p->unk_28 = parent;
    p->unk_coord = *ofs;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080b69b4, 0x080b6a5c, 0x080b6b0c, 0x080b6b94
static void Smoke_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Entity* parent = s->unk_28;
  if (s->work[0] <= 1) {
    InitScalerotMotion1(s);
  } else {
    InitNonAffineMotion(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case 0:
    case 1:
      SetSpriteAnimation(p, FIRE(3));
      (s->spr).mag.x = (s->spr).mag.y = 96;
      if (s->work[0] == 1) s->angle = 32;
      (s->spr).oam.priority = (s->work[1] & 1) ? 3 : 2;
      s->d.x = s->d.y = 0;
      s->work[2] = 32;
      break;
    case 2:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FEFNIR_FLASH, 5));
      (s->spr).oam.priority = 2;
      s->renderPrio = 23;
      s->work[2] = 64;
      break;
    default:
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FEFNIR_BALL, (s->work[1] + 3)));
      s->d.x = PIXEL(2) - (RANDOM(RNG_0202f388) & 0x3FF);
      s->d.y = -(((RANDOM(RNG_0202f388) & 7) + 12) << 6);
      s->work[2] = 64;
      s->coord.x = parent->coord.x + s->unk_coord.x;
      s->coord.y = parent->coord.y + s->unk_coord.y;
      break;
  }
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Smoke_Update(p);
}

static void blink(struct Entity* s, bool8 shown) { s->flags = shown ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY); }

// 0x080b6c68, 0x080b6cf8, 0x080b6d88, 0x080b6dec
static void Smoke_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Entity* parent = s->unk_28;
  if (s->work[0] == 2 && parent->mode[1] >= PART_DUCK) {
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->work[0]) {
    case 0:
      s->coord.x = parent->coord.x + s->unk_coord.x + s->d.x;
      s->coord.y = parent->coord.y + s->unk_coord.y + s->d.y;
      if ((s->spr).mag.x <= 0xFF) {
        (s->spr).mag.x += 8;
        (s->spr).mag.y += 8;
      }
      s->d.x -= 96;
      s->d.y -= 32;
      blink(s, (s->work[2] & 3) <= 1);
      if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
    case 1:
      s->coord.x = parent->coord.x + s->unk_coord.x + s->d.x;
      s->coord.y = parent->coord.y + s->unk_coord.y + s->d.y;
      (s->spr).mag.x += 32;
      (s->spr).mag.y += 32;
      s->d.x -= 64;
      s->d.y -= 64;
      blink(s, (++s->work[2] & 3) <= 1);
      if ((s->spr).mag.x > 384) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
    case 2:
      s->coord = parent->coord;
      if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
    default:
      blink(s, s->work[2] & 1);
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 64;
      if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// --------------------------------------------
// Zero 2's VFX 45 work0 2, explosion drifting off, Zero 3's SM0

static void Explosion_Init(struct VFX* p);
static void Explosion_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2FefnirExplosionRoutine = {
    [ENTITY_INIT] =      Explosion_Init,
    [ENTITY_UPDATE] =    Explosion_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b87e0
void ApZ2CreateExplosion(struct Entity* parent, const Coords32* at, u8 kind UNUSED, u8 roll) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_FEFNIR_EXPLOSION);
    p->unk_28 = parent;
    p->coord = *at;
    p->work[1] = roll;
  }
}

// 0x080b8a0c
static void Explosion_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(SM000_BATTLE_EFFECT, 1));
  UpdateSpriteAnimation(p);
  s->d.x = COS(s->work[1]);
  s->d.y = SIN(s->work[1]);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Explosion_Update(p);
}

// 0x080b8dec
static void Explosion_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateSpriteAnimation(p);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (IsSpriteAnimEnd(p)) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------
/*
  Zero 2's enemy 40, burning ball top turrets lob.
  work0: turret
*/

struct Ball {
  OBJECT_HDR;
  u8 _b4[9];
  bool8 destroyed;  // 0xBD
  u8 _be[2];
  s32 groundY;      // 0xC0
};
static_assert(sizeof(struct Ball) == sizeof(struct Enemy));

static void Ball_Init(struct Ball* p);
static void Ball_Update(struct Ball* p);
static void Ball_Die(struct Ball* p);

// clang-format off
const EnemyRoutine gApZ2FefnirBallRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Ball_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Ball_Update,
    [ENTITY_DIE] =       (EnemyFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sBallCollision;

// 0x0807bddc
static void createBall(const Coords32* at, u8 n, u8 work1) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FEFNIR_BALL);
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *at;
    p->work[0] = n;
    p->work[1] = work1;
  }
}

// 0x0807be40
static void Ball_Init(struct Ball* p) {
  struct Entity* s = &p->s;
  InitRotatableMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_FEFNIR_BALL, 6));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sBallCollision, 2, NULL);
  p->destroyed = FALSE;
  s->angle = 32;
  if (s->work[0] == 0) {
    s->d.x = -0x440;
    s->d.y = -0x400;
  } else {
    s->d.x = -0x200;
    s->d.y = -0x500;
  }
  p->groundY = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Ball_Update(p);
}

// 0x0807bf04
static void Ball_Update(struct Ball* p) {
  struct Entity* s = &p->s;
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    p->destroyed = TRUE;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Ball_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  s->angle -= 7;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->coord.y > p->groundY) {
    s->coord.y = p->groundY;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Ball_Die(p);
  }
}

// 0x0807bf94
static void Ball_Die(struct Ball* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    if (p->destroyed) {
      CreateSmoke(1, &s->coord);
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      return;
    }
    s->work[2] = 64;
    s->flags &= ~DISPLAY;
    s->mode[2]++;
  }
  if ((s->work[2] & 7) == 0) {
    at.x = s->coord.x + PIXEL(12 - (s32)(RANDOM(RNG_0202f388) % 24));
    at.y = s->coord.y - PIXEL(RANDOM(RNG_0202f388) % 12);
    createFire(s, &at, 1, 0);
  }
  if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's solid 5 work0 37, work1 0, Fefnir beaten in clear scene
*/

static void Beaten_Init(struct Solid* p);
static void Beaten_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2BeatenFefnirRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Beaten_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Beaten_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteEntity,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c6518
static void Beaten_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitScalerotMotion1(s);
  ResetDynamicMotion(s);
  if (s->work[1] != 1) s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Beaten_Update(p);
}

// 0x080c6568
static void Beaten_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, s->work[1] == 2 ? MOTION(DM205_Z2_CAPTIVE, 25) : s->work[1] != 0 ? MOTION(DM202_Z2_LEVIATHAN, 17) : FEFNIR(0));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (!(s->scriptEntity->flags & 1)) break;
      if (s->work[1] == 2) {
        s->work[2] = 30;
        s->mode[1] = 3;
        break;
      }
      SetSpriteAnimation(p, s->work[1] != 0 ? MOTION(DM202_Z2_LEVIATHAN, 18) : FEFNIR(23));
      s->mode[1]++;
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (!(s->scriptEntity->flags & 2)) break;
      s->work[2] = 30;
      s->mode[1]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if (s->work[2] & 1) {
        PaintEntityWhite(s);
      } else {
        UpdateEntityPaletteID(s);
      }
      if (--s->work[2] != 0) break;
      s->work[2] = 8;
      s->mode[1]++;
      break;
    case 4:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = 288 - s->work[2] * 4;
      (s->spr).mag.y = s->work[2] * 4 + 224;
      if (--s->work[2] != 0) break;
      PlaySound(SE_TENSOU_BACK);
      s->work[2] = 4;
      s->mode[1]++;
      break;
    case 5:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = s->work[2] * 64 + 32;
      (s->spr).mag.y = 352 - s->work[2] * 32;
      if (--s->work[2] != 0) break;
      s->d.y = -0xC00;
      s->mode[1]++;
      break;
    case 6:
      UpdateSpriteAnimation(p);
      PaintEntityWhite(s);
      (s->spr).mag.x = 32;
      s->d.y -= 64;
      s->coord.y += s->d.y;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= PIXEL(48)) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// --------------------------------------------

// clang-format off
static const struct Collision sCollisions[2] = {
    /* 0x833ce1c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 1, 0x00000001, {0x400, -0x3200, 0x1000, 0x1000}},
    /* 0x833ce34 */ {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0, 0x00000000, {0x400, -0x3200, 0x1000, 0x1000}},
};

static const struct Collision sPartCollisions[8] = {
    /* 0x8340208 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0xc00, -0x4400, 0x2400, 0x1a00}},
    /* 0x8340220 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {0xc00, -0x4400, 0x2400, 0x1a00}},
    /* 0x8340238 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x200, -0x4400, 0x2400, 0x1a00}},
    /* 0x8340250 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x4400, 0x2400, 0x1a00}},
    /* 0x8340268 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x800, -0x1a00, 0x2400, 0x1a00}},
    /* 0x8340280 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {0x800, -0x1a00, 0x2400, 0x1a00}},
    /* 0x8340298 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1a00, -0x1b00, 0x2400, 0x1a00}},
    /* 0x83402b0 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0, 0x00000000, {-0x1a00, -0x1b00, 0x2400, 0x1a00}},
};

/* 0x83402c8 */
static const struct Collision sNoHitbox = {DDP, FACTION_ENEMY, 2, 0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x0, 0x0}};

static const struct Collision sFireCollisions[16] = {
    /* 0x8344bf8 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x8344c10 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x1a00}},
    /* 0x8344c28 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x400, 0x0, 0x800, 0x800}},
    /* 0x8344c40 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x800, 0x0, 0x1000, 0x800}},
    /* 0x8344c58 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xc00, 0x0, 0x1800, 0x800}},
    /* 0x8344c70 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x1000, 0x0, 0x2000, 0x800}},
    /* 0x8344c88 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x1400, 0x0, 0x2a00, 0xe00}},
    /* 0x8344ca0 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x1a00, -0x400, 0x3000, 0x1200}},
    /* 0x8344cb8 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x1e00, -0x600, 0x3e00, 0x1600}},
    /* 0x8344cd0 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x2400, -0x600, 0x4800, 0x1c00}},
    /* 0x8344ce8 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x2a00, -0x600, 0x5400, 0x2000}},
    /* 0x8344d00 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x3100, -0x700, 0x6200, 0x2700}},
    /* 0x8344d18 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x3500, -0x700, 0x6a00, 0x2b00}},
    /* 0x8344d30 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x3500, 0x700, 0x6a00, 0x1700}},
    /* 0x8344d48 */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0x5800, -0x1400, 0x3c00, 0x1400}},
    /* 0x8344d60 */ {DDP, FACTION_ENEMY, 2, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0xc00}},
};

/* 0x8340348 */
static const struct Collision sBallCollision = {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}};

/* 0x8340614 */
static const struct Collision sWheelCollision = {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x800, -0x1000, 0x4c00, 0x2400}};
// clang-format on

#endif  // AP
