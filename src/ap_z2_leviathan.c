#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
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
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Zero 2's Leviathan, boss 17.
*/

struct Leviathan {
  OBJECT_HDR;
  s32 homeX;                 // 0xB4
  s32 hoverY;                // 0xB8
  bool8 hitFromRight;        // 0xBC
  u8 lastAttack;             // 0xBD
  u8 bob;                    // 0xBE
  u8 bubbles;                // 0xBF
  s32 left;                  // 0xC0, room's walls and floor
  s32 right;                 // 0xC4
  s32 floor;                 // 0xC8
  struct Entity* dragons[2]; // 0xCC
  struct Entity* serpents[2];// 0xD4
  u16 dieTimer;              // 0xDC
  u8 _de[6];
};
static_assert(sizeof(struct Leviathan) == sizeof(struct Boss));

enum { LEV_WAIT, LEV_SUMMON, LEV_NOP, LEV_PICK, LEV_HOVER, LEV_NOP2, LEV_LEAVE, LEV_ACROSS, LEV_BACK,
       LEV_DRAGONS_WIND, LEV_DRAGONS, LEV_WAVE_WIND, LEV_WAVE, LEV_LANCE_WIND, LEV_LANCE,
       LEV_LOW_LEAVE, LEV_LOW, LEV_LOW_BACK, LEV_SERPENTS_WIND, LEV_SERPENTS, LEV_SERPENTS_LEAVE,
       LEV_SERPENTS_ACROSS, LEV_SERPENTS_BACK };

#define LEVIATHAN(n) MOTION(DM202_Z2_LEVIATHAN, (n))
#define ARMOR(n) MOTION(DM203_Z2_LEVIATHAN_ARMOR, (n))

#define HOVER_HEIGHT PIXEL(84)
#define PAST_WALL PIXEL(80)
#define PLTT_ANIM_ID(n) (0x8000 | (n))

extern const PlttAnimData gApZ2Na2_PlttAnim140;
extern const AnimCmd* const gApZ2Na2_PlttAnimScript140[];

static const struct Collision sCollisions[24];
static const u8 sAcrossHitboxes[8];

// Above armor, whose frames run past boss window
static const struct PreloadEntity sIceSheet = {AP_SHEET_Z2_LEVIATHAN_ICE, 0, 640, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSummonSheet = {AP_SHEET_Z2_FEFNIR_SUMMON, 0, 576, 5, 0, AP_PRELOAD_SHEET, 0};

static void Leviathan_Init(struct Leviathan* p);
static void Leviathan_Update(struct Leviathan* p);
static void Leviathan_Die(struct Leviathan* p);
static void Leviathan_Disappear(struct Leviathan* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static struct Entity* createDragon(const Coords32* at, u8 kind, u8 n);
static struct Entity* createCrawler(struct Entity* boss, u8 n, u8 dir);
static void createIcicle(struct Entity* boss, u8 n);
static void createShot(struct Entity* boss, u8 kind, u8 n);
static void createPuff(const Coords32* at, u8 kind, u8 n);

// clang-format off
const BossRoutine gApZ2LeviathanRoutine = {
    [ENTITY_INIT] =      (BossFunc)Leviathan_Init,
    [ENTITY_UPDATE] =    (BossFunc)Leviathan_Update,
    [ENTITY_DIE] =       (BossFunc)Leviathan_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Leviathan_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 gone(struct Entity* e) { return e->mode[0] > ENTITY_UPDATE; }

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

// 0x0805f244
static void Leviathan_Init(struct Leviathan* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetSpriteAnimation(p, LEVIATHAN(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, 96);
  (p->body).fn = onCollision;
  p->hitFromRight = FALSE;
  p->lastAttack = 0;
  p->left = FUN_0800a31c(s->coord.x, s->coord.y);
  p->right = FUN_0800a22c(s->coord.x, s->coord.y);
  p->floor = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->hoverY = p->floor - HOVER_HEIGHT;
  p->dragons[0] = p->dragons[1] = NULL;
  s->unk_2c = NULL;
  p->bubbles = 0;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  setMode(s, LEV_WAIT);
  Leviathan_Update(p);
}

void CreateBubble(s32 x, s32 y, u8 kind);
static const BossFunc sStates[23];

// 0x0805f320
static void Leviathan_Update(struct Leviathan* p) {
  struct Entity* s = &p->s;
  u8 i;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Leviathan_Die(p);
    return;
  }
  for (i = 0; i < 2; i++) {
    if (p->dragons[i] != NULL && gone(p->dragons[i])) p->dragons[i] = NULL;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && (p->body).elemented == ELEMENT_FLAME) {
    p->bubbles = 16;
    PlaySound(SE_Z2_LEVIATHAN_HURT);
  }
  if (p->bubbles != 0) {
    p->bubbles--;
    CreateBubble(s->coord.x + PIXEL(16 - (RANDOM(RNG_0202f388) & 31)),
                 s->coord.y + PIXEL(16 - (RANDOM(RNG_0202f388) & 31)), p->bubbles & 1 ? 0 : 1);
  }
  (sStates[s->mode[1]])((struct Boss*)p);
}

// 0x0805f498: explodes, flashing slower, until clear script destroys her
static void Leviathan_Die(struct Leviathan* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    UpdateSpriteAnimation(p);
    p->dieTimer = 0;
    s->work[2] = 24;
    s->work[3] = 12;
    s->mode[2]++;
  }
  if (p->dieTimer++ > 64) {
    if ((p->dieTimer & 3) == 0) {
      at.x = s->coord.x + PIXEL(48 - (RANDOM(RNG_0202f388) & 0x7FFF) % 96);
      at.y = s->coord.y + PIXEL(32 - (RANDOM(RNG_0202f388) & 63));
      ApZ2CreateExplosion(s, &at, 2, (u8)RANDOM(RNG_0202f388));
    }
    if ((p->dieTimer & 15) == 0) PlaySound(SE_Z2_TANK_EXPLODE);
  }
  if (s->mode[1] != 0) {
    if (p->dieTimer & 1) {
      PaintEntityWhite(s);
    } else {
      UpdateEntityPaletteID(s);
    }
  } else if (--s->work[3] == 0xFF) {
    PaintEntityWhite(s);
    if (--s->work[2] == 0xFF) {
      gStageRun.vm.active |= VM_FLAG1;
      s->mode[1]++;
    }
    s->work[3] = s->work[2] >> 1;
  } else {
    UpdateEntityPaletteID(s);
  }
}

static void Leviathan_Disappear(struct Leviathan* p) { DeleteBoss(&p->s); }

// 0x0805f618: waits for script
static void Leviathan_Wait(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_LEVIATHAN_SUMMON);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) setMode(s, LEV_SUMMON);
}

// 0x0805f650: calls armor in bubble
static void Leviathan_Summon(struct Leviathan* p) {
  struct Entity* s = &p->s;
  struct Entity* b;
  u8 angle;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, LEVIATHAN(15));
    PlaySound(SE_Z2_LEVIATHAN_CALL);
    s->work[3] = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[3]) {
    case 0:
      if (!IsSpriteAnimEnd(p)) break;
      s->unk_28 = ApZ2CreateBubble(&s->coord, 3);
      ApLoadSheet(&sSummonSheet);
      s->work[3] = 0;
      s->work[2] = 0;
      PlaySound(SE_Z2_FEFNIR_BUBBLE);
      s->mode[3]++;
      break;
    case 1:
      b = s->unk_28;
      if (b->mode[3] == 0) {
        s->flags = (s->work[2]++ & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
        if ((s->work[2] & 3) != 0) break;
        s->work[3] += 8;
        for (angle = 0; angle < 4; angle++) {
          ApZ2CreateSpark(&s->coord, s->work[3] + (angle << 6));
          ApZ2CreateSpark(&s->coord, 0xFF - s->work[3] + (angle << 6));
        }
      } else if (b->mode[3] == 1) {
        s->flags = (s->work[2]++ & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      } else if (b->mode[3] == 2) {
        s->flags |= DISPLAY;
        ApLoadSheet(&sIceSheet);
        SetSpriteAnimation(p, ARMOR(4));
        UpdateSpriteAnimation(p);
        ApStartPaletteAnimation(PLTT_ANIM_ID(140), &gApZ2Na2_PlttAnim140, gApZ2Na2_PlttAnimScript140, 0x280);
        StepPaletteAnimation(PLTT_ANIM_ID(140));
        s->mode[3]++;
      }
      break;
    case 2:
      if (!gone(s->unk_28)) break;
      SetSpriteAnimation(p, ARMOR(5));
      UpdateSpriteAnimation(p);
      s->work[2] = 24;
      s->mode[3]++;
      break;
    case 3:
      if (--s->work[2] == 0xFF) s->mode[3]++;
      break;
    case 4:
      StepPaletteAnimation(PLTT_ANIM_ID(140));
      if ((u8)StepPaletteAnimation(PLTT_ANIM_ID(140)) != 3) break;
      RemovePaletteAnimation(PLTT_ANIM_ID(140));
      SetSpriteAnimation(p, ARMOR(0));
      UpdateSpriteAnimation(p);
      s->mode[3]++;
      break;
    case 5:
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, LEV_PICK);
      break;
  }
}

static void Leviathan_Nop(struct Leviathan* p UNUSED) {}

static void bobble(struct Leviathan* p) {
  struct Entity* s = &p->s;
  s->coord.y = p->hoverY + SIN(p->bob++) * 8;
}

// Picks by rank and Zero's distance. Never same twice running, swims round if he is behind.
static u8 pickAttack(struct Leviathan* p) {
  struct Entity* s = &p->s;
  s32 d = (pZero2->s).coord.x - s->coord.x;
  u8 hard = gScore.total->rank > 4;
  u8 roll;
  if (d < 0) d = -d;
  if (d < PIXEL(80)) {
    roll = hard ? RANDOM(RNG_0202f388) & 15 : RANDOM(RNG_0202f388) % 12;
    if (roll < 4) return LEV_WAVE_WIND;
    if (roll < 6) return LEV_DRAGONS_WIND;
    if (roll < 12) return LEV_SERPENTS_WIND;
    return LEV_LOW_LEAVE;
  }
  roll = RANDOM(RNG_0202f388) % (hard ? 14 : 12);
  if (roll < 4) return LEV_LEAVE;
  if (roll < 6) return LEV_WAVE_WIND;
  if (roll < 10) return LEV_DRAGONS_WIND;
  if (roll < 12 || !hard) return LEV_LANCE_WIND;
  return LEV_LOW_LEAVE;
}

// 0x0805f904
static void Leviathan_Pick(struct Leviathan* p) {
  struct Entity* s = &p->s;
  s32 zero;
  u8 attack;
  p->hoverY = p->floor - HOVER_HEIGHT;
  s->coord.y = p->hoverY + SIN(p->bob++) * 8;
  UpdateSpriteAnimation(p);
  zero = (pZero2->s).coord.x;
  do {
    attack = pickAttack(p);
    if (attack == LEV_DRAGONS_WIND && p->dragons[0] != NULL && p->dragons[1] != NULL) continue;
    if (p->lastAttack == LEV_WAVE_WIND && attack == LEV_SERPENTS_WIND) attack = LEV_LANCE_WIND;
    if (attack != p->lastAttack) break;
  } while (TRUE);
  if (facingRight(s) ? s->coord.x > zero : s->coord.x < zero) {
    attack = (gScore.total->rank > 4 && (RANDOM(RNG_0202f388) & 1)) ? LEV_LOW_LEAVE : LEV_LEAVE;
  }
  p->lastAttack = attack;
  setMode(s, attack);
}

// 0x0805fbf4
static void Leviathan_Hover(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (--s->work[2] == 0xFF) setMode(s, LEV_PICK);
}

static bool8 swim(struct Leviathan* p, bool8 forwards, s32 margin) {
  struct Entity* s = &p->s;
  s->coord.x += s->d.x;
  if (facingRight(s) == forwards) {
    if (s->d.x < 0x800) s->d.x += 32;
    return s->coord.x > p->right + margin;
  }
  if (s->d.x > -0x800) s->d.x -= 32;
  return s->coord.x < p->left - margin;
}

// 0x0805fc5c, 0x08060238, 0x08060624: out of room, way she faces
static void Leviathan_Leave(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    s->d.x = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (swim(p, FALSE, PAST_WALL)) setMode(s, s->mode[1] + 1);
}

// 0x0805fcf0, 0x080606b8: back across at Zero, from behind
static void Leviathan_Across(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(1));
    PlaySound(SE_Z2_LEVIATHAN_SWIM);
    if (s->mode[1] == LEV_ACROSS) {
      s->coord.y = (pZero2->s).coord.y - PIXEL(32);
    } else {
      s->coord.y += PIXEL(24);
    }
    s->d.x = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  SetDDP(&p->body, &sCollisions[sAcrossHitboxes[(s->motion).cmdIdx]]);
  if (swim(p, TRUE, PAST_WALL)) setMode(s, s->mode[1] + 1);
}

// 0x0805fdc8, 0x080603b4, 0x08060788: turns, glides in from wall she came to
static void Leviathan_Back(struct Leviathan* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    bool8 right = !facingRight(s);
    SetSpriteAnimation(p, ARMOR(0));
    SetDDP(&p->body, sCollisions);
    SET_XFLIP(p, right);
    s->coord.x = right ? p->left - PAST_WALL : p->right + PAST_WALL;
    s->d.y = right ? 32 : -32;
    s->coord.y = p->hoverY;
    s->d.x = 0;
    for (i = 0; i < 48; i++) s->d.x += s->d.y;
    p->bob = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->d.x -= s->d.y;
  s->coord.x += s->d.x;
  if (s->d.x == 0) {
    u8 rest = s->mode[1] == LEV_LOW_BACK ? 128 : 48;
    s->mode[1] = LEV_HOVER;
    s->mode[2] = 0;
    s->work[2] = rest;
  }
}

// Windups: 0x0805febc, 0x0805ffe4, 0x080600cc, 0x080604a8
static void Leviathan_Windup(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    s->work[2] = 8;
    switch (s->mode[1]) {
      case LEV_WAVE_WIND:
        PlaySound(SE_Z2_LEVIATHAN_SHARDS);
        createShot(s, 1, facingRight(s));
        break;
      case LEV_LANCE_WIND:
        PlaySound(SE_Z2_LEVIATHAN_WAVE);
        break;
    }
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (--s->work[2] == 0xFF) setMode(s, s->mode[1] + 1);
}

static void rest(struct Leviathan* p) {
  struct Entity* s = &p->s;
  setMode(s, LEV_HOVER);
  s->work[2] = 48;
}

// 0x0805ff24
static void Leviathan_Dragons(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    if (p->dragons[0] == NULL) p->dragons[0] = createDragon(&s->coord, 0, facingRight(s) ? 2 : 0);
    if (p->dragons[1] == NULL) p->dragons[1] = createDragon(&s->coord, 0, facingRight(s) ? 3 : 1);
    s->work[2] = 96;
    PlaySound(SE_Z2_LEVIATHAN_DRAGONS);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (--s->work[2] == 0xFF) rest(p);
}

// 0x08060060
static void Leviathan_Wave(struct Leviathan* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    s->work[2] = 128;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (--s->work[2] == 0xFF) rest(p);
}

// 0x08060138: three lance shots, at 64, 48 and 32 frames left
static void Leviathan_Lance(struct Leviathan* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 dir = facingRight(s);
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    at.x = s->coord.x + (dir ? PIXEL(13) : -PIXEL(13));
    at.y = s->coord.y - PIXEL(32);
    createPuff(&at, 3, 0);
    s->work[2] = 124;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (s->work[2] == 64 || s->work[2] == 48 || s->work[2] == 32) {
    createShot(s, 0, dir | (s->work[2] == 64 ? 0 : s->work[2] == 48 ? 2 : 4));
    PlaySound(SE_Z2_LEVIATHAN_SHOT);
  }
  if (--s->work[2] == 0xFF) rest(p);
}

// 0x080602c8: low across room, five icicles trailing
static void Leviathan_Low(struct Leviathan* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(2));
    SetDDP(&p->body, &sCollisions[14]);
    s->coord.y = p->floor - PIXEL(100);
    s->d.x = 0;
    for (i = 0; i < 5; i++) createIcicle(s, i);
    PlaySound(SE_Z2_LEVIATHAN_SWIM);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (swim(p, TRUE, PIXEL(160))) setMode(s, LEV_LOW_BACK);
}

// 0x08060510: two serpents, then two crawlers along floor once first is gone
static void Leviathan_Serpents(struct Leviathan* p) {
  struct Entity* s = &p->s;
  u8 dir = facingRight(s) ? 2 : 0;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, ARMOR(0));
    p->serpents[0] = createDragon(&s->coord, 1, dir);
    p->serpents[1] = createDragon(&s->coord, 1, dir + 1);
    s->work[2] = 96;
    PlaySound(SE_Z2_LEVIATHAN_DRAGONS);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bobble(p);
  if (s->mode[3] == 0) {
    if (!gone(p->serpents[0])) return;
    p->serpents[0] = createCrawler(s, 0, facingRight(s));
    p->serpents[1] = createCrawler(s, 1, facingRight(s));
    s->mode[3]++;
    return;
  }
  if (p->serpents[0] != NULL && gone(p->serpents[0])) p->serpents[0] = NULL;
  if (p->serpents[1] != NULL && gone(p->serpents[1])) p->serpents[1] = NULL;
  if (p->serpents[0] == NULL && p->serpents[1] == NULL) setMode(s, LEV_SERPENTS_LEAVE);
}

// clang-format off
static const BossFunc sStates[23] = {
    (BossFunc)Leviathan_Wait,     (BossFunc)Leviathan_Summon,   (BossFunc)Leviathan_Nop,
    (BossFunc)Leviathan_Pick,     (BossFunc)Leviathan_Hover,    (BossFunc)Leviathan_Nop,
    (BossFunc)Leviathan_Leave,    (BossFunc)Leviathan_Across,   (BossFunc)Leviathan_Back,
    (BossFunc)Leviathan_Windup,   (BossFunc)Leviathan_Dragons,  (BossFunc)Leviathan_Windup,
    (BossFunc)Leviathan_Wave,     (BossFunc)Leviathan_Windup,   (BossFunc)Leviathan_Lance,
    (BossFunc)Leviathan_Leave,    (BossFunc)Leviathan_Low,      (BossFunc)Leviathan_Back,
    (BossFunc)Leviathan_Windup,   (BossFunc)Leviathan_Serpents, (BossFunc)Leviathan_Leave,
    (BossFunc)Leviathan_Across,   (BossFunc)Leviathan_Back,
};
// clang-format on

// 0x0806087c
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Leviathan* p = (struct Leviathan*)body->parent;
  if (body->hitboxFlags & 1) p->hitFromRight = body->enemy->parent->coord.x > (p->s).coord.x;
}

// --------------------------------------------

static void useIceSheet(struct Entity* s) { s->texture = TEXTURE_AP_SHEET; }

#define ICE(n) MOTION(AP_SHEET_Z2_LEVIATHAN_ICE, (n))

#define MOVE(s, angle, speed)                                                  do {                                                                           (s)->coord.x += (COS((u8)((angle) + 0x80)) * (speed)) / 256;                 (s)->coord.y += (SIN((u8)((angle) + 0x80)) * (speed)) / 256;               } while (0)

/*
  Zero 2's VFX 41. Odd kinds ice, even ones water.
  1: sparkle left behind something
  3: burst, breaks into 5s
     work1: only two
  5: two shards flying apart
     work1: angle, in 32nds
*/
struct Burst {
  struct Entity s;  // d and unk_coord: two spots, one drawn a frame
  s16 v[4];         // 0x74, each spot's speed
  s16 slow[4];      // 0x7C
};
static_assert(sizeof(struct Burst) == sizeof(struct VFX));
enum { BURST_SPARKLE = 1, BURST = 3, BURST_SHARD = 5 };

static void Burst_Init(struct VFX* p);
static void Burst_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2IceBurstRoutine = {
    [ENTITY_INIT] =      Burst_Init,
    [ENTITY_UPDATE] =    Burst_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b7330
void ApZ2CreateIceBurst(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_ICE_BURST);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

static void Burst_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Burst* b = (struct Burst*)p;
  u8 i, angle;
  InitNonAffineMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] & 1) {
    SetSpriteAnimation(p, ICE(s->work[0] == BURST_SPARKLE ? 10 : 12));
  } else {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_LEVIATHAN_WATER, 2 + s->work[0] / 2));
  }
  UpdateSpriteAnimation(p);
  s->coord = s->unk_28->coord;
  s->work[2] = 0;
  switch (s->work[0] | 1) {
    case BURST_SPARKLE:
      s->coord.x += PIXEL((RANDOM(RNG_0202f388) & 7) - 4);
      s->d = s->unk_coord = s->coord;
      break;
    case BURST:
      if (s->work[1] != 0) {
        ApZ2CreateIceBurst(s, (s->work[0] & 1) + 4, 1);
        ApZ2CreateIceBurst(s, (s->work[0] & 1) + 4, 3);
      } else {
        for (i = 0; i < 4; i++) ApZ2CreateIceBurst(s, (s->work[0] & 1) + 4, i);
      }
      s->work[2] = 4;
      PlaySound(SE_Z2_ICE_BREAK);
      break;
    case BURST_SHARD:
      s->d = s->unk_coord = s->coord;
      angle = s->work[1] << 5;
      b->v[0] = COS(angle) * 2;
      b->v[1] = SIN(angle) * 2;
      angle += 0x80;
      b->v[2] = COS(angle) * 2;
      b->v[3] = SIN(angle) * 2;
      for (i = 0; i < 4; i++) b->slow[i] = b->v[i] / 32;
      s->work[2] = 32;
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Burst_Update(p);
}

static void Burst_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Burst* b = (struct Burst*)p;
  u8 i;
  UpdateSpriteAnimation(p);
  switch (s->work[0] | 1) {
    case BURST_SPARKLE:
      if (s->work[2] < 7) {
        s->flags = (s->work[2] & 3) > 1 ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      } else {
        s->coord = (s->work[2] & 3) > 1 ? s->d : s->unk_coord;
      }
      if (s->work[2] == 8) s->d = s->unk_28->coord;
      if (s->work[2]++ > 40) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
    case BURST:
      s->flags = (s->work[2] & 3) > 1 ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
    case BURST_SHARD:
      s->coord = ((s->work[2] + s->work[1]) & 3) > 1 ? s->unk_coord : s->d;
      s->unk_coord.x += b->v[0];
      s->unk_coord.y += b->v[1];
      s->d.x += b->v[2];
      s->d.y += b->v[3];
      for (i = 0; i < 4; i++) b->v[i] -= b->slow[i];
      if (--s->work[2] == 0xFF) SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

/*
  Zero 2's VFX 43.
  0: wave's flash
  1: spike's sparkles
  2: falling chip of ice
  3: lance's flash, throws 4s while it holds
  4: spark flying in from 32 steps out, work1 angle
  5: lance hitting wall
*/
static const u8 sPuffAnims[6] = {7, 15, 13, 17, 19, 18};

static void Puff_Init(struct VFX* p);
static void Puff_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2IcePuffRoutine = {
    [ENTITY_INIT] =      Puff_Init,
    [ENTITY_UPDATE] =    Puff_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b7f60
static void createPuff(const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_ICE_PUFF);
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

static void Puff_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  InitNonAffineMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->d.x = s->d.y = 0;
  switch (s->work[0]) {
    case 2:
      SetSpriteAnimation(p, ICE(s->work[1] != 0 ? 13 : 12));
      s->d.x = 0x100 - ((RANDOM(RNG_0202f388) >> 8) & 0x1FF);
      s->d.y = -(((RANDOM(RNG_0202f388) & 7) + 2) << 6);
      s->work[2] = 48;
      break;
    case 3:
      SetSpriteAnimation(p, ICE(17));
      s->work[2] = 64;
      break;
    case 4:
      SetSpriteAnimation(p, ICE(19));
      s->d.x = COS(s->work[1]) * 2;
      s->d.y = SIN(s->work[1]) * 2;
      s->coord.x += COS(s->work[1]) * 32;
      s->coord.y += SIN(s->work[1]) * 32;
      s->work[2] = 16;
      break;
    default:
      SetSpriteAnimation(p, ICE(sPuffAnims[s->work[0]]));
      SET_XFLIP(p, s->work[1] & 1);
      break;
  }
  if (s->work[0] == 0) (s->spr).oam.priority = 1;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Puff_Update(p);
}

static void Puff_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  bool8 end = FALSE;
  UpdateSpriteAnimation(p);
  switch (s->work[0]) {
    case 2:
      s->d.y += 32;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->flags = (s->work[2] & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      end = --s->work[2] == 0xFF;
      break;
    case 3:
      if (s->work[2] > 16 && (s->work[2] & 1)) {
        createPuff(&s->coord, 4, (RANDOM(RNG_0202f388) & 3) << 6 | (RANDOM(RNG_0202f388) & 63));
      }
      end = --s->work[2] == 0xFF;
      break;
    case 4:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      end = --s->work[2] == 0xFF;
      break;
    default:
      end = IsSpriteAnimEnd(p);
      break;
  }
  if (end) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------
/*
  Zero 2's enemy 44, ice dragon's head. Tail is projectile 43.
  work0:
    0: curls round, homes on Zero, 16 HP
    1: flies straight for 128 frames, unbreakable
  work1: start angle
*/
struct Dragon {
  OBJECT_HDR;
  u8 ring[10];  // 0xB4, angles of last 10 frames, for tail
  u8 _[6];
};
static_assert(sizeof(struct Dragon) == sizeof(struct Enemy));

static void Dragon_Init(struct Enemy* p);
static void Dragon_Update(struct Enemy* p);
static void Dragon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2IceDragonRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Dragon_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Dragon_Update,
    [ENTITY_DIE] =       (EnemyFunc)Dragon_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sDragonCollisions[2];
static const u8 sDragonAngles[4] = {0x78, 0x88, 0x08, 0xF8};
static const s8 sDragonTurn[4] = {-2, 2, 2, -2};

static void createTail(struct Entity* parent, u8 n, u8 left);

// 0x0807d8c8
static struct Entity* createDragon(const Coords32* at, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_DRAGON);
    p->coord = *at;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x0807d990
static void Dragon_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Dragon* d = (struct Dragon*)p;
  u8 i;
  InitRotatableMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(0));
  SET_XFLIP(p, FALSE);
  SET_YFLIP(p, s->work[1] > 1);
  s->renderPrio = 25;
  s->work[3] = sDragonAngles[s->work[1]];
  INIT_BODY(p, sDragonCollisions, s->work[0] != 0 ? 255 : 16, NULL);
  s->unk_coord = s->coord;
  s->work[2] = 128;
  for (i = 0; i < 10; i++) d->ring[i] = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Dragon_Update(p);
}

// 0x0807daac
static void Dragon_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Dragon* d = (struct Dragon*)p;
  u8 i, want;
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Dragon_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0 && s->mode[2]++ > 9) {
    createTail(s, s->work[1], 6);
    s->mode[1]++;
  }
  for (i = 9; i > 0; i--) d->ring[i] = d->ring[i - 1];
  d->ring[0] = s->work[3];
  if (s->mode[3] == 0) {
    if (s->work[0] != 0) {
      if (--s->work[2] == 0xFF) {
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
    } else {
      s->work[3] += sDragonTurn[s->work[1]];
      if ((s->work[3] & 0x7F) == 0) s->mode[3]++;
    }
  } else {
    want = (u8)((ArcTan2(((pZero2->s).coord.x - s->coord.x - PIXEL(16)) >> 12,
                         ((pZero2->s).coord.y - s->coord.y) >> 12) + 0x8000) >> 8);
    if ((u8)(want - s->work[3]) < 0x80) {
      s->work[3] += 2;
    } else {
      s->work[3] -= 2;
    }
  }
  s->angle = (s->flags & Y_FLIP) ? -s->work[3] : s->work[3];
  MOVE(s, s->work[3], 0x180);
}

// 0x0807dc54
static void Dragon_Die(struct Enemy* p) {
  ApZ2CreateIceBurst(&p->s, BURST, 0);
  UpdateSpriteAnimation(p);
  (p->s).flags &= ~COLLIDABLE;
  (p->body).status = (p->body).prevStatus = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// --------------------------------------------
/*
  Zero 2's projectile 43, dragon's tail.
  work1: links still to come, 0 is tip
*/
struct Tail {
  OBJECT_HDR;
  u8 ring[10];  // 0xB4, as Dragon's
  u8 _[6];
};
static_assert(sizeof(struct Tail) == sizeof(struct Projectile));

static void Tail_Init(struct Projectile* p);
static void Tail_Update(struct Projectile* p);
static void Tail_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2DragonTailRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Tail_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Tail_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Tail_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sTailCollisions[2];

// 0x080a623c
static void createTail(struct Entity* parent, u8 n, u8 left) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_DRAGON_TAIL);
    p->unk_28 = parent;
    p->work[1] = n;
    p->work[2] = left;
  }
}

// 0x080a6294
static void Tail_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Tail* t = (struct Tail*)p;
  struct Entity* parent = s->unk_28;
  u8 i;
  if (s->work[2] != 0) {
    InitNonAffineMotion(s);
  } else {
    InitRotatableMotion(s);
  }
  useIceSheet(s);
  SetSpriteAnimation(p, ICE(s->work[2] != 0 ? 1 : 2));
  s->flags |= DISPLAY | FLIPABLE;
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sTailCollisions, 1, NULL);
  s->renderPrio = 26;
  s->coord = parent->unk_coord;
  s->unk_coord = parent->unk_coord;
  s->work[3] = ((struct Tail*)parent)->ring[9];
  for (i = 0; i < 10; i++) t->ring[i] = 0;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Tail_Update(p);
}

// 0x080a6368
static void Tail_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Tail* t = (struct Tail*)p;
  struct Entity* parent = s->unk_28;
  u8 i;
  if (parent->mode[0] > ENTITY_UPDATE) {
    if (parent->id == ENEMY_Z2_ICE_DRAGON && parent->work[0] != 0) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    } else {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Tail_Die(p);
    }
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[1] == 0 && s->mode[2]++ > 9) {
    if (s->work[2] != 0) createTail(s, s->work[1], s->work[2] - 1);
    s->mode[1]++;
  }
  for (i = 9; i > 0; i--) t->ring[i] = t->ring[i - 1];
  t->ring[0] = s->work[3];
  s->work[3] = ((struct Tail*)parent)->ring[9];
  if (s->work[2] == 0) s->angle = s->work[3];
  MOVE(s, s->work[3], 0x180);
}

// 0x080a6474: blinks, links nearest head first
static void Tail_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] != 9) {
    s->work[3] = (6 - s->work[2]) << 2;
    (p->body).status = (p->body).prevStatus = 0;
    s->flags &= ~COLLIDABLE;
    s->mode[1] = 9;
  }
  UpdateSpriteAnimation(p);
  s->flags = (s->work[3] & 1) ? (s->flags & ~DISPLAY) : (s->flags | DISPLAY);
  if (--s->work[3] == 0xFF) {
    ApZ2CreateIceBurst(s, BURST, 0);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// --------------------------------------------
/*
  Zero 2's projectile 42.
  kind 0: lance shot, grows, flies, bounces once off first wall
    n: which of three, | 1 facing right
  kind 1: wave along her side, drops snowflakes
*/
static void Shot_Init(struct Projectile* p);
static void Shot_Update(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2LeviathanShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Shot_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Shot_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sShotCollisions[2];
static const struct Collision sWaveCollisions[2];
static const u8 sShotAngles[6] = {0xD4, 0xAC, 0xE0, 0xA0, 0xEB, 0x95};

static void createSnowflake(const Coords32* at);

// 0x080a5c74
static void createShot(struct Entity* boss, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_LEVIATHAN_SHOT);
    p->unk_28 = boss;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

// 0x080a5d3c, 0x080a5e7c
static void Shot_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (s->work[0] == 0) {
    InitRotatableMotion(s);
    useIceSheet(s);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, ICE(16));
    UpdateSpriteAnimation(p);
    s->angle = sShotAngles[s->work[1]];
    (s->spr).mag.x = 192;
    (s->spr).mag.y = 0;
    INIT_BODY(p, sShotCollisions, 1, NULL);
    s->coord.x = boss->coord.x + ((s->work[1] & 1) ? PIXEL(14) : -PIXEL(14));
    s->coord.y = boss->coord.y - PIXEL(33);
    MOVE(s, s->angle, 24 * 256);
    (s->spr).oam.priority = 1;
  } else {
    InitNonAffineMotion(s);
    useIceSheet(s);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, ICE(6));
    UpdateSpriteAnimation(p);
    INIT_BODY(p, sWaveCollisions, 1, NULL);
    s->work[2] = 28;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Shot_Update(p);
}

static void updateLance(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[2]) {
    case 0:
      (s->spr).mag.y += 24;
      if ((s->spr).mag.y > 191) s->mode[2]++;
      break;
    case 1:
      MOVE(s, s->angle, 4 * 256);
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        createPuff(&s->coord, 5, 0);
        s->work[2] = 96;
        s->mode[2]++;
      }
      break;
    case 2:
      SetSpriteAnimation(p, ICE(20));
      SetDDP(&p->body, sShotCollisions);
      s->angle = -s->angle;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      MOVE(s, s->angle, 4 * 256);
      if (s->work[2] < 32) s->flags = (s->work[2] & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      if (--s->work[2] == 0xFF) SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

static void updateWave(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  UpdateSpriteAnimation(p);
  if (s->mode[2] <= 2) {
    SET_XFLIP(p, (boss->flags & X_FLIP) != 0);
    s->coord.x = boss->coord.x + ((boss->flags & X_FLIP) ? PIXEL(13) : -PIXEL(13));
    s->coord.y = boss->coord.y - PIXEL(33);
  }
  switch (s->mode[2]) {
    case 0:
      if (--s->work[2] == 0xFF) s->mode[2]++;
      break;
    case 1:
      SetSpriteAnimation(p, ICE(8));
      createPuff(&s->coord, 0, (s->flags & X_FLIP) != 0);
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      if ((s->motion).cmdIdx == 0) break;
      s->d.x = (s->flags & X_FLIP) ? PIXEL(8) : -PIXEL(8);
      s->work[2] = 64;
      PlaySound(SE_Z2_LEVIATHAN_SHOT);
      s->mode[2]++;
      break;
    case 3:
      s->coord.x += s->d.x;
      if (s->work[2] % 6 == 0) createSnowflake(&s->coord);
      if (--s->work[2] == 0xFF) SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x080a5cdc
static void Shot_Update(struct Projectile* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if ((p->s).work[0] == 0) {
    updateLance(p);
  } else {
    updateWave(p);
  }
}

// --------------------------------------------
/*
  Zero 2's enemy 46, snowflake.
*/
struct Snowflake {
  OBJECT_HDR;
  s32 homeX;
  s32 homeY;
  u8 _4;
  u8 death;
  u8 _[6];
};
static_assert(sizeof(struct Snowflake) == sizeof(struct Enemy));

static void Snow_Init(struct Enemy* p);
static void Snow_Update(struct Enemy* p);
static void Snow_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2SnowflakeRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Snow_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Snow_Update,
    [ENTITY_DIE] =       (EnemyFunc)Snow_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sSnowCollisions[2];
static const struct Collision sSpikeCollision[1];
static const struct Collision sSpikeRiseCollisions[2];

// 0x0807e060
static void createSnowflake(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_SNOWFLAKE);
    p->coord = *at;
  }
}

// 0x0807e0c4
static void Snow_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Snowflake* f = (struct Snowflake*)p;
  InitNonAffineMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(9));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sSnowCollisions, 8, NULL);
  f->homeX = s->coord.x;
  f->homeY = s->coord.y;
  f->death = 0;
  s->work[2] = 0;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Snow_Update(p);
}

// 0x0807e188
static void Snow_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Snowflake* f = (struct Snowflake*)p;
  Coords32 at;
  if ((p->body).status & BODY_STATUS_DEAD) {
    f->death = s->mode[1] == 0 ? 1 : 2;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Snow_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->coord.y += PIXEL(1);
      s->coord.x = f->homeX + SIN(s->work[2]) * 4;
      s->work[2] += 4;
      if ((s->work[3]++ & 15) == 0) ApZ2CreateIceBurst(s, BURST_SPARKLE, 0);
      if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        s->mode[1] = 1;
        s->mode[2] = 0;
      }
      break;
    case 1:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, ICE(14));
        SetDDP(&p->body, sSpikeCollision);
        s->work[2] = 0;
        PlaySound(SE_Z2_SPIKE_GROW);
        s->mode[2]++;
      }
      s->work[2]++;
      if (s->work[2] < 16 && (s->work[2] & 3) == 0) {
        at.x = s->coord.x + PIXEL(16 - (RANDOM(RNG_0202f388) & 31));
        at.y = s->coord.y - (s->work[2] << 9);
        createPuff(&at, 1, RANDOM(RNG_0202f388) & 1);
      }
      if (s->work[2] > 48) {
        s->mode[1] = 2;
        s->mode[2] = 0;
      }
      break;
    case 2:
      if (s->mode[2] == 0) {
        SetDDP(&p->body, sSpikeRiseCollisions);
        s->d.y = -PIXEL(1);
        s->work[2] = 128;
        s->mode[2]++;
      }
      s->coord.y += s->d.y;
      if (s->work[2] < 32) s->flags = (s->work[2] & 1) ? (s->flags | DISPLAY) : (s->flags & ~DISPLAY);
      if (--s->work[2] == 0xFF) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        Snow_Die(p);
      }
      break;
  }
}

// 0x0807e1e8
static void Snow_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Snowflake* f = (struct Snowflake*)p;
  Coords32 at = s->coord;
  u8 i;
  if (f->death == 1) {
    ApZ2CreateIceBurst(s, BURST, 0);
  } else if (f->death == 2) {
    for (i = 0; i < 4; i++) {
      at.y -= PIXEL(8);
      createPuff(&at, 2, RANDOM(RNG_0202f388) & 1);
    }
    PlaySound(SE_Z2_ICE_BREAK);
  }
  s->flags &= ~COLLIDABLE;
  (p->body).status = (p->body).prevStatus = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// --------------------------------------------
/*
  Zero 2's enemy 47, icicle from low swim.
  work1: place in row
*/
static void Icicle_Init(struct Enemy* p);
static void Icicle_Update(struct Enemy* p);
static void Icicle_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2IcicleRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Icicle_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Icicle_Update,
    [ENTITY_DIE] =       (EnemyFunc)Icicle_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sIcicleCollisions[2];

#define ICICLE_GAP(s) (PIXEL(128) + ((s)->work[1] << 14))

// 0x0807e4a4
static void createIcicle(struct Entity* boss, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICICLE);
    p->unk_28 = boss;
    p->work[1] = n;
  }
}

// 0x0807e500
static void Icicle_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  bool8 right = (boss->flags & X_FLIP) != 0;
  InitNonAffineMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(3));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, right);
  INIT_BODY(p, sIcicleCollisions, 8, NULL);
  s->coord.x = boss->coord.x + (right ? -ICICLE_GAP(s) : ICICLE_GAP(s));
  s->coord.y = boss->coord.y;
  s->d.x = 0;
  s->unk_coord.x = ((struct Leviathan*)boss)->left + PIXEL(240);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Icicle_Update(p);
}

static bool8 movingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

// 0x0807e5ec
static void Icicle_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  s32 x = s->coord.x, was = s->d.x, by;
  bool8 done = FALSE;
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Icicle_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->coord.x = s->unk_28->coord.x + (movingRight(s) ? -ICICLE_GAP(s) : ICICLE_GAP(s));
      if (movingRight(s) ? s->coord.x > s->unk_coord.x : s->coord.x < s->unk_coord.x) done = TRUE;
      s->d.x = s->coord.x - x;
      if (abs(was) > abs(s->d.x)) done = TRUE;
      if (done) {
        s->mode[1] = 2;
        s->mode[2] = 0;
      }
      break;
    case 1:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, ICE(3));
        s->mode[2]++;
      }
      s->d.x += movingRight(s) ? 32 : -32;
      by = (pZero2->s).coord.x;
      if ((movingRight(s) ? x < by : x > by) && s->coord.y > (pZero2->s).coord.y - PIXEL(32)) done = TRUE;
      s->coord.x = x + s->d.x;
      if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(32)) != 0) done = TRUE;
      if (done) {
        s->mode[1] = 4;
        s->mode[2] = 0;
      } else if (abs(s->d.x) > 0x500) {
        s->mode[1] = 2;
        s->mode[2] = 0;
      }
      break;
    case 2:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, ICE(4));
        s->mode[2]++;
      }
      s->d.x += movingRight(s) ? -64 : 64;
      s->coord.x += s->d.x;
      s->coord.y += PIXEL(1);
      if (movingRight(s) ? s->d.x < 0 : s->d.x > 0) {
        s->mode[1] = 3;
        s->mode[2] = 0;
      }
      break;
    case 3:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, ICE(5));
        SET_XFLIP(p, !movingRight(s));
        s->mode[2]++;
      }
      s->d.x += movingRight(s) ? 32 : -32;
      s->coord.x += s->d.x;
      s->coord.y += PIXEL(1);
      if (IsSpriteAnimEnd(p)) {
        s->mode[1] = 1;
        s->mode[2] = 0;
      }
      break;
    case 4:
      if (s->mode[2] == 0) {
        s->work[2] = 255;
        s->mode[2]++;
      }
      if (movingRight(s)) {
        if (s->d.x < 0x700) s->d.x += 32;
      } else if (s->d.x > -0x700) {
        s->d.x -= 32;
      }
      s->coord.x += s->d.x;
      if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x0807e634
static void Icicle_Die(struct Enemy* p) {
  PlaySound(SE_Z2_ICICLE_BREAK);
  CreateSmoke(1, &(p->s).coord);
  (p->s).flags &= ~COLLIDABLE;
  (p->body).status = (p->body).prevStatus = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// --------------------------------------------
/*
  Zero 2's enemy 45, crawling dragon's head.
  work0:
    0: upper row, turns down
    1: lower row, turns up
  work1: heading right
*/
struct Crawler {
  OBJECT_HDR;
  s32 ahead;  // 0xB4, where to look for wall
  u8 _[12];
};
static_assert(sizeof(struct Crawler) == sizeof(struct Enemy));

static void Crawler_Init(struct Enemy* p);
static void Crawler_Update(struct Enemy* p);
static void Crawler_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2IceCrawlerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Crawler_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Crawler_Update,
    [ENTITY_DIE] =       (EnemyFunc)Crawler_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCrawlerCollisions[2];
static const struct Rect sCrawlerSize = {0, 0, PIXEL(32), PIXEL(16)};

static void createIceCell(struct Entity* boss, const Coords32* at, u8 right);

// 0x0807dc9c
static struct Entity* createCrawler(struct Entity* boss, u8 n, u8 dir) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_CRAWLER);
    p->unk_28 = boss;
    p->work[0] = n;
    p->work[1] = dir;
  }
  return p;
}

// 0x0807dcfc
static void Crawler_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Leviathan* boss = (struct Leviathan*)s->unk_28;
  InitRotatableMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, s->work[1]);
  INIT_BODY(p, sCrawlerCollisions, 8, NULL);
  s->angle = 0;
  s->renderPrio = 25;
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sCrawlerSize;
  s->physicsAttr = 0x2E01;
  if (s->work[1] != 0) {
    s->coord.x = boss->left - PIXEL(24);
    s->d.x = 0x400;
  } else {
    s->coord.x = boss->right + PIXEL(24);
    s->d.x = -0x400;
  }
  s->coord.y = boss->hoverY + (s->work[0] != 0 ? PIXEL(64) : -PIXEL(32));
  s->coord.x = (s->coord.x & ~0xFFF) + PIXEL(8);
  s->coord.y = (s->coord.y & ~0xFFF) + PIXEL(8);
  s->work[2] = 32;
  s->work[3] = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Crawler_Update(p);
}

// 0x0807de58
static void Crawler_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Crawler* c = (struct Crawler*)p;
  s32 zero = (pZero2->s).coord.x;
  u8 keep;
  Coords32 at;
  bool8 die = ((p->body).status & BODY_STATUS_DEAD) != 0;

  if (!die) {
    at.x = (s->coord.x & ~0xFFF) + PIXEL(8);
    at.y = (s->coord.y & ~0xFFF) + PIXEL(8);
    if (FUN_080098a4(at.x, at.y) == 0) {
      if (gSolidHeaderPtr->remaining > 2 || gEnemyHeaderPtr->remaining != 0) {
        createIceCell(s->unk_28, &at, s->flags & X_FLIP ? TRUE : FALSE);
        s->work[3]++;
      } else {
        die = TRUE;
      }
    }
  }
  if (die) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Crawler_Die(p);
    return;
  }
  if (s->mode[1] == 0) {
    s->coord.x += s->d.x;
    if ((s->coord.x & 0xFFF) != 0x800) return;
    keep = s->d.x > 0 ? 6 + (s->work[0] & 1) : 8 - (s->work[0] & 1);
    if (gEnemyHeaderPtr->remaining <= keep || s->work[3] > 10 ||
        (s->d.x > 0 ? s->coord.x > zero + PIXEL(64) : s->coord.x < zero - PIXEL(64))) {
      s->mode[1]++;
      if (s->work[0] != 0) {
        c->ahead = -PIXEL(16);
        s->d.y = -0x400;
        s->work[2] = 64;
      } else {
        c->ahead = PIXEL(16);
        s->d.y = 0x400;
        s->work[2] = 192;
      }
    }
    return;
  }
  s->angle = s->work[2];
  s->coord.y += s->d.y;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0 && FUN_080098a4(s->coord.x, s->coord.y + c->ahead) != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Crawler_Die(p);
  }
}

// 0x0807e010
static void Crawler_Die(struct Enemy* p) {
  ApZ2CreateIceBurst(&p->s, BURST, 0);
  UpdateSpriteAnimation(p);
  (p->s).flags &= ~COLLIDABLE;
  (p->s).flags2 &= ~ENTI_PHYSICS;
  (p->body).status = (p->body).prevStatus = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// --------------------------------------------
/*
  Zero 2's solid 31, enemy 85 when solids run out. Cell of crawler's row.
*/
static void Cell_Init(Object* p);
static void Cell_Update(Object* p);
static void Cell_Die(Object* p);

// clang-format off
const SolidRoutine gApZ2IceCellRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Cell_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Cell_Update,
    [ENTITY_DIE] =       (SolidFunc)Cell_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
const EnemyRoutine gApZ2IceCellEnemyRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Cell_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Cell_Update,
    [ENTITY_DIE] =       (EnemyFunc)Cell_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCellCollision;
static const u16 sCellIce[] = {1, 1, 0x1F};    // 0x0831fbd4
static const u16 sCellEmpty[] = {1, 1, 0x00};  // 0x0831fbcc

static void cellRoutine(Object* p, u8 n) {
  if ((p->s).kind == ENTITY_SOLID) {
    SET_SOLID_ROUTINE(p, n);
  } else {
    SET_ENEMY_ROUTINE(p, n);
  }
}

// 0x080d26c0, 0x08096d98
static void createIceCell(struct Entity* boss, const Coords32* at, u8 right) {
  struct Entity* p;
  if (gSolidHeaderPtr->remaining > 2) {
    p = AllocEntityLast(gSolidHeaderPtr);
    if (p == NULL) return;
    INIT_SOLID_ROUTINE(p, SOLID_Z2_ICE_CELL);
  } else {
    p = AllocEntityLast(gEnemyHeaderPtr);
    if (p == NULL) return;
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_CELL);
  }
  p->unk_28 = boss;
  p->coord = *at;
  p->work[1] = right;
}

// 0x080d2724
static void Cell_Init(Object* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useIceSheet(s);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, ICE(1));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sCellCollision, 16, NULL);
  PatchMetatileMap(s->coord.x >> 12, s->coord.y >> 12, sCellIce);
  cellRoutine(p, ENTITY_UPDATE);
  Cell_Update(p);
}

// 0x080d27c8
static void Cell_Update(Object* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  if (((p->body).status & BODY_STATUS_DEAD) ||
      (boss->mode[1] == LEV_SERPENTS_ACROSS &&
       (s->work[1] != 0 ? s->coord.x < boss->coord.x : s->coord.x > boss->coord.x))) {
    cellRoutine(p, ENTITY_DIE);
    Cell_Die(p);
    return;
  }
  if (s->mode[1] != 0) {
    s->flags &= ~DISPLAY;
    s->mode[1] = 0;
  } else if ((p->body).status & BODY_STATUS_WHITE) {
    s->flags |= DISPLAY;
    s->mode[1]++;
  } else {
    s->flags &= ~DISPLAY;
  }
}

// 0x080d2848
static void Cell_Die(Object* p) {
  struct Entity* s = &p->s;
  PatchMetatileMap(s->coord.x >> 12, s->coord.y >> 12, sCellEmpty);
  ApZ2CreateIceBurst(s, BURST, 1);
  (p->body).status = (p->body).prevStatus = 0;
  s->flags &= ~COLLIDABLE;
  cellRoutine(p, ENTITY_DISAPPEAR);
}

static const u8 sAcrossHitboxes[8] = {9, 9, 14, 9, 9, 9, 19, 9};

// clang-format off
static const struct Collision sCollisions[24] = {
    /* 0x833d13c */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 8, 0x00000000, {-0xa00, -0x1b00, 0x1000, 0x1000}},
    /* 0x833d154 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 7, 0x00000001, {-0x200, -0x400, 0x2600, 0x2600}},
    /* 0x833d16c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 6, 0x00000001, {-0x200, -0x1c00, 0xa00, 0xa00}},
    /* 0x833d184 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {-0xa00, -0x2200, 0xa00, 0x800}},
    /* 0x833d19c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 4, 0x00000001, {0x1800, 0x1400, 0x1200, 0x3400}},
    /* 0x833d1b4 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x1c00, 0x3200, 0xc00, 0xa00}},
    /* 0x833d1cc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x2200, 0x3e00, 0x800, 0x1000}},
    /* 0x833d1e4 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x2800, 0x4c00, 0x800, 0xc00}},
    /* 0x833d1fc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x2600, 0xc00, 0xc00, 0x1400}},
    /* 0x833d214 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 4, 0x00000000, {-0x2000, 0x0, 0x800, 0x800}},
    /* 0x833d22c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x1800, 0x0, 0x1400, 0x5600}},
    /* 0x833d244 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x2000, 0x0, 0x7a00, 0x800}},
    /* 0x833d25c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x200, 0x0, 0x1800, 0x3e00}},
    /* 0x833d274 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xe00, 0x0, 0xc00, 0x2c00}},
    /* 0x833d28c */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 4, 0x00000000, {-0x2000, 0x400, 0x800, 0x800}},
    /* 0x833d2a4 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x1b00, -0x400, 0x8000, 0xa00}},
    /* 0x833d2bc */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0xe00, -0x1400, 0x1a00, 0x1600}},
    /* 0x833d2d4 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x1400, 0x1000, 0xa00, 0x1a00}},
    /* 0x833d2ec */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xc00, -0x200, 0x1c00, 0x1800}},
    /* 0x833d304 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 4, 0x00000000, {-0x2000, -0x600, 0x800, 0x800}},
    /* 0x833d31c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x1b00, 0x400, 0x8000, 0xa00}},
    /* 0x833d334 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0xe00, 0x1200, 0x1a00, 0x1600}},
    /* 0x833d34c */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x1400, -0x1000, 0xa00, 0x1a00}},
    /* 0x833d364 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xc00, 0x0, 0x1c00, 0x1800}},
};
// clang-format on

// clang-format off
static const struct Collision sDragonCollisions[2] = {
    /* 0x8340758 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x8340770 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sCrawlerCollisions[2] = {
    /* 0x83407a0 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x2000, 0x1000}},
    /* 0x83407b8 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sSnowCollisions[2] = {
    /* 0x83407f8 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x8340810 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sSpikeCollision[1] = {
    /* 0x8340828 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sSpikeRiseCollisions[2] = {
    /* 0x8340858 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, -0xe00, 0xa00, 0x2400}},
    /* 0x8340870 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, -0xe00, 0xa00, 0x2400}},
};

static const struct Collision sIcicleCollisions[2] = {
    /* 0x83408b0 */ {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1a00, 0x800}},
    /* 0x83408c8 */ {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1a00, 0x800}},
};

static const struct Collision sShotCollisions[2] = {
    /* 0x8344f8c */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    /* 0x8344fa4 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};

static const struct Collision sWaveCollisions[2] = {
    /* 0x8344fec */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x8345004 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sTailCollisions[2] = {
    /* 0x8345038 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    /* 0x8345050 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

static const struct Collision sCellCollision =
    /* 0x8349e84 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}};

#endif  // AP
