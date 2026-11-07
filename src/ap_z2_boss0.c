#include "ap.h"
#include "ap_import.h"
#include "anim_loader.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "palette_animation.h"
#include "physics.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "spawn.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/static.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's desert mechaniloid, boss 0.
  Parts are enemies 4 (legs), 5 (tail) and 6 (jaw), attacking on its orders.
  Art is SM4 and SM5, sharing one frame table.
*/

struct DesertBoss {
  OBJECT_HDR;
  s32 homeX;               // 0xB4
  s32 homeY;               // 0xB8
  u8 lastPick;             // 0xBC, last attack rolled
  u8 prio;                 // 0xBD, OAM priority, parts too
  u8 _be[2];
  struct Entity* explosion;  // 0xC0
  u8 _c4[16];
  struct Entity* legs;     // 0xD4, enemy 4 work0 1, busy mid-step
  struct Entity* part6;    // 0xD8, enemy 6, NULL once dead
  struct Entity* part5;    // 0xDC, enemy 5
  bool8 order0;            // 0xE0, attack 0 running
  bool8 order1;            // 0xE1, attack 1 starting
  bool8 order2;            // 0xE2, attack 2 starting
  u8 stance;               // 0xE3, 2 in intro, 1 during attack 1, else 0
};
static_assert(sizeof(struct DesertBoss) == sizeof(struct Boss));

enum { DESERT_INTRO, DESERT_WAIT, DESERT_WALK, DESERT_ATTACK0, DESERT_ATTACK1, DESERT_SHOOT,
       DESERT_ATTACK2, DESERT_HURT };

// Stops here, far end of the desert
#define DESERT_END (PIXEL(14640) - PIXEL(240))
#define WALK_SPEED 192

static const struct Collision sIntroCollisions[2];
static const struct Collision sPartCollisions[4];

static void Desert_Init(struct DesertBoss* p);
static void Desert_Update(struct DesertBoss* p);
static void Desert_Die(struct DesertBoss* p);
static struct Entity* createPart(struct DesertBoss* boss, u8 kind, u8 renderPrio);
static struct Entity* createPart5(struct DesertBoss* boss);
static struct Entity* createPart6(struct DesertBoss* boss);

// clang-format off
const BossRoutine gApZ2DesertRoutine = {
    [ENTITY_INIT] =      (BossFunc)Desert_Init,
    [ENTITY_UPDATE] =    (BossFunc)Desert_Update,
    [ENTITY_DIE] =       (BossFunc)Desert_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// Loaded at init, as in Zero 2
static const struct PreloadEntity sSheets[3] = {
    {AP_SHEET_Z2_BOSS0, 0, 512, 4},
    {AP_SHEET_Z2_BOSS0_B, 0, 512 + AP_SHEET_Z2_BOSS0_TILES, 5},
    {AP_SHEET_Z2_ROCKS, 0, 992, 8},
};

static void useApSheets(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setMode(struct Entity* p, u8 mode) {
  p->mode[1] = mode;
  p->mode[2] = 0;
}

static bool8 pastEnd(struct Entity* s) { return s->coord.x + PIXEL(240) > DESERT_END; }

// 0x0803fa1c
static void Desert_Init(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sSheets[0]);
  ApLoadSheet(&sSheets[1]);
  ApLoadSheet(&sSheets[2]);
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0, 0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, sIntroCollisions, 32);
  p->prio = 3;
  (s->spr).oam.priority = 3;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(20);
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  s->d.x = s->d.y = 0;
  p->lastPick = 0;
  p->order0 = p->order1 = p->order2 = FALSE;
  p->stance = 2;
  createPart(p, 2, 25);
  p->part6 = createPart6(p);
  createPart(p, 0, 24);
  p->part5 = createPart5(p);
  createPart(p, 3, 24);
  p->legs = createPart(p, 1, 24);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Desert_Update(p);
}

static const BossFunc sDesertStates[8];

// 0x0803fbb8
static void Desert_Update(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Desert_Die(p);
    return;
  }
  (s->spr).oam.priority = p->prio & 3;
  if (p->part6 != NULL && p->part6->mode[0] > ENTITY_UPDATE) p->part6 = NULL;
  if (((p->body).status & BODY_STATUS_WHITE) && s->mode[1] == DESERT_ATTACK1) setMode(s, DESERT_HURT);

  (sDesertStates[s->mode[1]])((struct Boss*)p);

  if (pastEnd(s)) s->d.x = 0;
  s->coord.x += s->d.x;
}

// 0x0803fd10: waits for the intro script
static void Desert_Intro(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0, 0));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) {
    p->prio = 2;
    setMode(s, DESERT_WAIT);
  }
}

// 0x0803fd54
static void Desert_Wait(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0, 0));
    p->stance = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, DESERT_WALK);
}

// 0x0803fd94: walks, rolls an attack every 33 frames
static void Desert_Walk(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  u8 roll;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->d.x = WALK_SPEED;
  if (pastEnd(s)) {
    setMode(s, DESERT_SHOOT);
    return;
  }
  if (s->work[2]++ <= 32) return;
  if ((p->legs->motion).cmdIdx != 0) return;

  roll = (u8)RANDOM(RNG_0202f388) % 15;
  if (p->lastPick == 0) {
    p->lastPick = (roll <= 5) ? 2 : (roll <= 11) ? 1 : 3;
  } else if (p->lastPick == 1) {
    p->lastPick = (roll <= 5) ? 2 : (roll <= 11) ? 0 : 3;
  } else if (p->lastPick == 2) {
    p->lastPick = (roll <= 4) ? 0 : (roll <= 9) ? 1 : 3;
  } else {
    p->lastPick = (roll <= 4) ? 0 : (roll <= 9) ? 1 : 2;
  }

  if (p->lastPick == 0) {
    setMode(s, DESERT_ATTACK0);
  } else if (p->lastPick == 1 && p->part6 != NULL) {
    setMode(s, DESERT_ATTACK1);
  } else if (p->lastPick == 2 && p->part5 != NULL) {  // tail check is new
    setMode(s, DESERT_ATTACK2);
    s->d.x = 0;
  } else {
    setMode(s, DESERT_SHOOT);
  }
}

// 0x0803fecc: order 0 for 72 frames
static void Desert_Attack0(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    p->order0 = TRUE;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->d.x = WALK_SPEED;
  if (pastEnd(s)) {
    p->order0 = FALSE;
    setMode(s, DESERT_WALK);
    return;
  }
  if (++s->work[2] > 71) p->order0 = FALSE;
  if (s->work[2] > 96 && (p->legs->motion).cmdIdx == 0) setMode(s, DESERT_WALK);
}

// 0x0803ff44: order 1, until jaw is done
static void Desert_Attack1(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->order1 = TRUE;
    p->stance = 1;
    s->mode[2]++;
  } else {
    p->order1 = FALSE;
  }
  UpdateSpriteAnimation(p);
  s->d.x = WALK_SPEED;
  if ((p->part6 == NULL || p->part6->mode[1] == 0) && !p->order1) {
    p->stance = 0;
    setMode(s, DESERT_WALK);
  }
}

// 0x0803ffa0: three shots, 8 frames apart
static void Desert_Shoot(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  u8 t;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->d.x = WALK_SPEED;
  c.x = s->coord.x;
  c.y = s->coord.y + PIXEL(8);
  t = s->work[2]++;
  if (t == 0 || t == 8 || t == 16) {
    CreateLemon(&c, 0x300, 0x80);
    PlaySound(SE_ENEMY_SHOT);
  } else if (t == 64) {
    setMode(s, DESERT_WALK);
  }
}

// 0x08040014: order 2, until tail takes it
static void Desert_Attack2(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.x = 0;
    p->order2 = TRUE;
    s->mode[2]++;
  } else {
    p->order2 = FALSE;
  }
  UpdateSpriteAnimation(p);
  if (p->part5 != NULL && p->part5->mode[1] == 1 && !p->order2) {
    p->stance = 0;
    setMode(s, DESERT_WALK);
  }
}

// 0x08040064: hit during attack 1, stops for 32 frames
static void Desert_Hurt(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.x = 0;
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) s->mode[1] = DESERT_ATTACK1;
}

static const BossFunc sDesertStates[8] = {
    (BossFunc)Desert_Intro,   (BossFunc)Desert_Wait,    (BossFunc)Desert_Walk,
    (BossFunc)Desert_Attack0, (BossFunc)Desert_Attack1, (BossFunc)Desert_Shoot,
    (BossFunc)Desert_Attack2, (BossFunc)Desert_Hurt,
};

// 0x0803fc88
static void Desert_Die(struct DesertBoss* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    Coords32 still = {0, 0};
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    p->explosion = CreateBossExplosion(s, &still);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (p->explosion->mode[0] > ENTITY_UPDATE) gStageRun.vm.active |= VM_FLAG1;
}

// --------------------------------------------
/*
  Legs and fixed pieces, Zero 2's enemy 4.
  work0: piece
  work1: render priority
*/

static void Part_Init(struct Enemy* p);
static void Part_Update(struct Enemy* p);
static void Part_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2DesertPartRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Part_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Part_Update,
    [ENTITY_DIE] =       (EnemyFunc)Part_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

#define PART_LEGS 1

// 0x080ef774, by work0
static const motion_t sPartMotions[5] = {
    MOTION(AP_SHEET_Z2_BOSS0_B, 13), MOTION(AP_SHEET_Z2_BOSS0, 7), MOTION(AP_SHEET_Z2_BOSS0, 8),
    MOTION(AP_SHEET_Z2_BOSS0, 1),    MOTION(AP_SHEET_Z2_BOSS0_B, 10),
};

// 0x080689bc
static struct Entity* createPart(struct DesertBoss* boss, u8 kind, u8 renderPrio) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_DESERT_PART);
    p->unk_28 = &boss->s;
    p->work[0] = kind;
    p->work[1] = renderPrio;
  }
  return p;
}

static struct DesertBoss* bossOf(struct Enemy* p) { return (struct DesertBoss*)(p->s).unk_28; }

static void followBoss(struct Enemy* p) { (p->s).coord = (bossOf(p)->s).coord; }

// 0x08068a18: front two hurt Zero
static void Part_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, sPartMotions[s->work[0]]);
  UpdateSpriteAnimation(p);
  if (s->work[0] == 0) ForceEntityPalette(s, 4);
  SET_XFLIP(p, FALSE);
  if (s->work[0] <= PART_LEGS) {
    INIT_BODY(p, &sPartCollisions[s->work[0] * 2], 1, NULL);
  }
  (s->spr).oam.priority = 3;
  s->renderPrio = s->work[1];
  followBoss(p);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

// 0x08068b00: legs step only while body walks
static void Part_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct DesertBoss* boss = bossOf(p);
  if ((boss->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Part_Die(p);
    return;
  }
  (s->spr).oam.priority = boss->prio & 3;
  if (s->work[0] == PART_LEGS) {
    if (s->mode[1] == 0) {
      if ((s->motion).cmdIdx != 1) s->mode[1] = 1;
    } else if ((s->motion).cmdIdx == 1) {
      PlaySound(SE_Z2_DESERT_STEP);
      s->mode[1] = 0;
    }
  }
  if ((boss->s).d.x != 0) UpdateSpriteAnimation(p);
  followBoss(p);
}

// 0x08068b9c: harmless, gone with body
static void Part_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->mode[2]++;
  }
  if ((bossOf(p)->s).mode[0] == ENTITY_EXIT) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Tail, Zero 2's enemy 5. Five segments, each placed from the one before.
  work0:
    0: base, on the body
    1..3: middle
    4: tip
*/

struct DesertTail {
  OBJECT_HDR;
  u8 angle;            // 0xB4
  u8 _b5;
  u16 length;          // 0xB6, 256 is full length
  struct DesertBoss* boss;  // 0xB8
  s8 curl;             // 0xBC, idle curl
  u8 _bd[7];
};
static_assert(sizeof(struct DesertTail) == sizeof(struct Enemy));

enum { TAIL_NONE, TAIL_IDLE, TAIL_WIND_UP, TAIL_STRETCH, TAIL_STRIKE, TAIL_HOLD, TAIL_LIFT, TAIL_RETRACT,
       TAIL_RECOVER };

#define TAIL_TIP 4
// Body's stance while the tip is down
#define TIP_DOWN 1

static const struct Collision sTailCollisions[10];

static void Tail_Init(struct DesertTail* p);
static void Tail_Update(struct DesertTail* p);
static void Tail_Die(struct DesertTail* p);
static void createLink(struct DesertBoss* boss, Coords32* from, Coords32* to, u8 parts, u8 part);
static void crater(Coords32* c);
struct Entity* ApZ2CreateRock(u8 kind, const Coords32* at, const Coords32* d);

// clang-format off
const EnemyRoutine gApZ2DesertTailRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Tail_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Tail_Update,
    [ENTITY_DIE] =       (EnemyFunc)Tail_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08068c44, 0x08068be0
static struct Entity* createSegment(struct Entity* parent, struct DesertBoss* boss, u8 n) {
  struct DesertTail* p = (struct DesertTail*)AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_DESERT_TAIL);
    (p->s).unk_28 = parent;
    p->boss = boss;
    (p->s).work[0] = n;
    (p->s).work[1] = 0;
  }
  return (struct Entity*)p;
}

static struct Entity* createPart5(struct DesertBoss* boss) { return createSegment(&boss->s, boss, 0); }

// 0x0833e074: segment lengths, 1/256 px
static const u16 sTailLengths[5] = {PIXEL(28), PIXEL(21), PIXEL(19), PIXEL(16), PIXEL(15)};

// 0x0833e07e, by work[2]. Nothing advances it, so always 19.
static const u8 sTailWave[8] = {19, 20, 21, 22, 23, 22, 21, 20};

// 0x0833e06e: landing height of each falling segment
static const u8 sTailFloors[5] = {16, 14, 12, 10, 12};

#define TAIL_NEXT(p) ((p)->s).unk_2c

// 0x080693e4
static void placeSegment(struct DesertTail* p, u8 angle) {
  struct Entity* s = &p->s;
  s32 length = (sTailLengths[s->work[0]] * p->length) / 256;
  if (s->work[0] == 0) {
    s->coord.x = (p->boss->s).coord.x + (SIN(angle + 64) * length) / 256 - PIXEL(56);
    s->coord.y = (p->boss->s).coord.y + (SIN(angle) * length) / 256 - PIXEL(40);
    return;
  }
  s->coord.x = (s->unk_28)->coord.x + (SIN(angle + 64) * length) / 256;
  s->coord.y = (s->unk_28)->coord.y + (SIN(angle) * length) / 256;
  if (s->work[0] == TAIL_TIP) s->angle = (u8)(angle + 64);
}

// Each segment bends once more than the one before
static u8 segmentAngle(struct DesertTail* p, s32 base) { return (u8)((p->s.work[0] + 1) * base - 64); }

// 0x08068ca8
static void Tail_Init(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == TAIL_TIP) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0, (2 + s->work[0])));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, &sTailCollisions[s->work[0] * 2], 1, NULL);
  (s->spr).oam.priority = 3;
  TAIL_NEXT(p) = (s->work[0] < TAIL_TIP) ? createSegment(s, p->boss, s->work[0] + 1) : NULL;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = TAIL_IDLE;
  Tail_Update(p);
}

static const EnemyFunc sTailStates[9];

// 0x08068d80
static void Tail_Update(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if ((p->boss->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Tail_Die(p);
    return;
  }
  (s->spr).oam.priority = p->boss->prio & 3;
  (sTailStates[s->mode[1]])((struct Enemy*)p);
}

static void Tail_None(struct DesertTail* p UNUSED) {}

// 0x08068eb8: idle, curled during intro and while jaw is out
static void Tail_Idle(struct DesertTail* p) {
  struct Entity* s = &p->s;
  u8 angle;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    p->length = 256;
    p->curl = 0;
    s->mode[2]++;
    s->mode[3] = 0;
  }
  if (p->boss->stance == 2) {
    p->length = 32;
    p->curl = -8;
  } else if (p->boss->stance == 1) {
    p->length -= 8;
    if (p->length < 128) p->length = 128;
    if (--p->curl < -8) p->curl = -8;
  } else {
    p->length += 8;
    if (p->length > 256) p->length = 256;
    if (++p->curl > 0) p->curl = 0;
  }
  angle = segmentAngle(p, p->curl + sTailWave[(s->work[2] >> 3) & 7]);
  p->angle = angle;
  placeSegment(p, angle);
  if (p->boss->order2) setMode(s, TAIL_WIND_UP);
}

// 0x08068fd0: folds up
static void Tail_WindUp(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    p->angle = 19;
    p->length = 256;
    s->mode[2]++;
    s->mode[3] = 0;
  }
  placeSegment(p, segmentAngle(p, p->angle));
  p->angle--;
  p->length -= 16;
  if (p->length <= 16) setMode(s, TAIL_STRETCH);
}

// 0x08069050: stretches to twice its length
static void Tail_Stretch(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    if (s->work[0] == 0) {
      s->unk_coord.x = (p->boss->s).coord.x - PIXEL(56);
      s->unk_coord.y = (p->boss->s).coord.y - PIXEL(40);
      createLink(p->boss, &s->coord, &s->unk_coord, 8, 3);
      createLink(p->boss, &s->coord, &s->unk_coord, 8, 5);
    } else if (s->work[0] != TAIL_TIP) {
      createLink(p->boss, &s->coord, &TAIL_NEXT(p)->coord, 4, 1);
      createLink(p->boss, &s->coord, &TAIL_NEXT(p)->coord, 4, 2);
      createLink(p->boss, &s->coord, &TAIL_NEXT(p)->coord, 4, 3);
    }
    PlaySound(SE_Z2_DESERT_TAIL_STRETCH);
    s->mode[2]++;
    s->mode[3] = 0;
  }
  placeSegment(p, segmentAngle(p, p->angle));
  p->length += 16;
  if (p->length > 0x1FF) setMode(s, TAIL_STRIKE);
}

// 0x08069150: column 120 px ahead, tip drops to the ground
static void Tail_Strike(struct DesertTail* p) {
  struct Entity* s = &p->s;
  struct DesertBoss* boss = p->boss;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    if (s->work[0] != 0) {
      s->coord.x = ((boss->s).coord.x + PIXEL(120)) & ~0xFFF;
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(200);
      s->d.y = 0x700;
      if (s->work[0] == TAIL_TIP) s->angle = 128;
    }
    boss->stance = 0;
    s->mode[2]++;
  }
  if (((p->body).status & BODY_STATUS_B2) && !((p->body).prevStatus & BODY_STATUS_B2)) {
    PlaySound(SE_Z2_DESERT_TAIL_HIT);
  }
  if (boss->stance != 0) {
    setMode(s, TAIL_HOLD);
  } else if (s->work[0] == TAIL_TIP) {
    s->coord.y += s->d.y;
    if (s->coord.y > (boss->s).coord.y - PIXEL(64) && FUN_080098a4(s->coord.x, s->coord.y + PIXEL(20))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y + PIXEL(20)) - PIXEL(20);
      boss->stance = TIP_DOWN;
      AppendQuake(1, &s->coord);
      crater(&s->coord);
      PlaySound(SE_Z2_DESERT_TAIL_SLAM);
    }
  } else if (s->work[0] > 1) {
    s->coord.y = TAIL_NEXT(p)->coord.y - PIXEL(48);
  }
}

// 0x08069258
static void Tail_Hold(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    s->d.y = 0;
    if (s->work[0] > 1) s->coord.y -= PIXEL(4);
    s->mode[2]++;
  }
  if (s->work[2]++ > 32) setMode(s, TAIL_LIFT);
}

// 0x08069298: tip rises past the body
static void Tail_Lift(struct DesertTail* p) {
  struct Entity* s = &p->s;
  struct DesertBoss* boss = p->boss;
  if (s->mode[2] == 0) {
    s->work[2] = 0;
    if (s->work[0] != 0) s->d.y = -0x700;
    s->mode[2]++;
  }
  if (boss->stance == 0) {
    setMode(s, TAIL_RETRACT);
  } else if (s->work[0] == TAIL_TIP) {
    s->coord.y += s->d.y;
    if (s->coord.y < (boss->s).coord.y - PIXEL(240)) boss->stance = 0;
  } else if (s->work[0] > 1) {
    s->coord.y = TAIL_NEXT(p)->coord.y - PIXEL(48);
  }
}

// 0x0806930c: shrinks away
static void Tail_Retract(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  placeSegment(p, segmentAngle(p, p->angle));
  p->length -= 16;
  if (p->length <= 16) setMode(s, TAIL_RECOVER);
}

// 0x08069370: back to resting shape
static void Tail_Recover(struct DesertTail* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  placeSegment(p, segmentAngle(p, p->angle));
  if (++p->angle > 19) p->angle = 19;
  p->length += 16;
  if (p->length > 255) setMode(s, TAIL_IDLE);
}

static const EnemyFunc sTailStates[9] = {
    (EnemyFunc)Tail_None,  (EnemyFunc)Tail_Idle, (EnemyFunc)Tail_WindUp,  (EnemyFunc)Tail_Stretch,
    (EnemyFunc)Tail_Strike, (EnemyFunc)Tail_Hold, (EnemyFunc)Tail_Lift,   (EnemyFunc)Tail_Retract,
    (EnemyFunc)Tail_Recover,
};

// 0x08068de4: body gone, segments drop tip first
static void Tail_Die(struct DesertTail* p) {
  struct Entity* s = &p->s;
  u8 floor;
  if (s->mode[2] == 0) {
    EXIT_BODY(p);
    s->work[2] = (TAIL_TIP - s->work[0]) * 16;
    s->work[3] = sTailFloors[s->work[0]];
    s->d.x = s->d.y = 0;
    s->mode[2]++;
  }
  floor = s->work[3];
  if (s->mode[3] == 0) {
    if (s->work[2] != 0) {
      s->work[2]--;
    } else {
      s->mode[3] = 1;
    }
  } else if (s->mode[3] == 1) {
    s->d.y += 64;
    if (s->d.y > 0x700) s->d.y = 0x700;
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(floor))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y + PIXEL(floor)) - PIXEL(floor);
      CreateSmoke(1, &s->coord);
      PlaySound(SE_Z2_DESERT_JAW_BREAK);
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    }
  }
}

// 0x0800aea4, stage code. Crater where the tip lands, rocks and smoke around it.
static const u16 sCraterPatch[38];
static const Coords32 sCraterSmoke[8];

static void crater(Coords32* c) {
  s32 x16 = c->x >> 12;
  Coords32 at;
  s32 i;
  PatchMetatileMap(x16 - 2, 28, sCraterPatch);
  PatchMetatileMap(x16 - 1, 27, &sCraterPatch[34]);
  for (i = 0; i < 8; i++) {
    Coords32 d;
    at.x = (x16 << 12) + (sCraterSmoke[i].x >> 1);
    at.y = PIXEL(464) + sCraterSmoke[i].y;
    d.x = sCraterSmoke[i].x >> 3;
    d.y = (sCraterSmoke[i].y >> 3) - PIXEL(4);
    ApZ2CreateRock(i % 3, &at, &d);
    at.x = (x16 << 12) + sCraterSmoke[i].x;
    CreateSmoke(3, &at);
  }
}

// --------------------------------------------
// Rocks, Zero 2's VFX 36. One bounce, then blink away.

static void Rock_Init(struct VFX* p);
static void Rock_Update(struct VFX* p);
static void Rock_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2RockRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Rock_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Rock_Update,
    [ENTITY_DIE] =       (VFXFunc)Rock_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

#define ROCK_BOUNCE work[2]
#define ROCK_BLINK work[3]

// 0x080b6508: kind 0..3, SM62 animations
struct Entity* ApZ2CreateRock(u8 kind, const Coords32* at, const Coords32* d) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_ROCK);
    p->coord = *at;
    p->d = *d;
    InitNonAffineMotion(p);
    useApSheets(p);
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_ROCKS, kind));
  }
  return p;
}

// 0x080b657c
static void Rock_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  s->flags |= DISPLAY;
  s->ROCK_BOUNCE = 60;
  s->ROCK_BLINK = 30;
  SET_VFX_ROUTINE(s, ENTITY_UPDATE);
  Rock_Update(p);
}

// 0x080b65ac: falls, bounces once in the first 60 frames
static void Rock_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateSpriteAnimation(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 64;
  if (s->ROCK_BOUNCE != 0) {
    s->ROCK_BOUNCE--;
    if (PushoutToUp1(s->coord.x, s->coord.y + PIXEL(4))) {
      s->d.y = -(s->d.y >> 2);
      s->d.x >>= 1;
      s->ROCK_BOUNCE = 0;
    }
    return;
  }
  if (s->ROCK_BLINK == 0 || Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 8) SET_VFX_ROUTINE(s, ENTITY_DIE);
  if (s->ROCK_BLINK & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  s->ROCK_BLINK--;
}

// 0x080b664c
static void Rock_Die(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  s->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(s, ENTITY_EXIT);
}

// --------------------------------------------
// Links between stretched tail segments, Zero 2's projectile 1

static void Link_Init(struct Projectile* p);
static void Link_Update(struct Projectile* p);
static void Link_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2DesertLinkRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Link_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Link_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Link_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

struct DesertLink {
  OBJECT_HDR;
  Coords32* from;  // 0xB4
  Coords32* to;    // 0xB8
  u8 _bc[8];
};
static_assert(sizeof(struct DesertLink) == sizeof(struct Projectile));

#define LINK_PARTS work[0]
#define LINK_PART work[1]

// 0x0809876c
static void createLink(struct DesertBoss* boss, Coords32* from, Coords32* to, u8 parts, u8 part) {
  struct DesertLink* p = (struct DesertLink*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_DESERT_LINK);
    (p->s).unk_28 = &boss->s;
    p->from = from;
    p->to = to;
    (p->s).LINK_PARTS = parts;
    (p->s).LINK_PART = part;
  }
}

// 0x080987d8
static void Link_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0, 14));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  (s->spr).oam.priority = 3;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Link_Update(p);
}

// 0x08098848
static void Link_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct DesertLink* link = (struct DesertLink*)p;
  struct Entity* boss = s->unk_28;
  if (boss->mode[0] > ENTITY_UPDATE) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Link_Die(p);
    return;
  }
  if (boss->mode[1] == DESERT_WALK) {
    s->flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  s->coord.x = link->from->x + ((link->to->x - link->from->x) / s->LINK_PARTS) * s->LINK_PART;
  s->coord.y = link->from->y + ((link->to->y - link->from->y) / s->LINK_PARTS) * s->LINK_PART;
}

// 0x080988fc
static void Link_Die(struct Projectile* p) {
  CreateSmoke(2, &(p->s).coord);
  PlaySound(SE_ZAKO_EXPLODE);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Jaw, Zero 2's enemy 6. 24 HP of its own.
  Bites on order 0, lunges 200 px on order 1. Flashes with stage palette animation 4.
*/

struct DesertJaw {
  OBJECT_HDR;
  s32 homeX;     // 0xB4
  s32 homeY;     // 0xB8
  u8 flashing;   // 0xBC, running palette animation or 0
  u8 _bd[7];
};
static_assert(sizeof(struct DesertJaw) == sizeof(struct Enemy));

enum { JAW_IDLE, JAW_BITE, JAW_CLOSE, JAW_OPEN, JAW_LUNGE, JAW_SNAP, JAW_RETURN };

extern const PlttAnimData gApZ2Opening_PlttAnim4, gApZ2Opening_PlttAnim5;
extern const AnimCmd* const gApZ2Opening_PlttAnimScript4[];

#define JAW_PALETTE (PLTT_SIZE / 2 + 5 * 32)   // OBJ palette 5
#define JAW_FLASH 4
#define JAW_FLASH_ID (0x8000 | JAW_FLASH)

static const struct Collision sJawIdleCollisions[1];
static const struct Collision sJawBiteCollisions[3];
static const struct Collision sJawOpenCollisions[2];

static void Jaw_Init(struct DesertJaw* p);
static void Jaw_Update(struct DesertJaw* p);
static void Jaw_Die(struct DesertJaw* p);

// clang-format off
const EnemyRoutine gApZ2DesertJawRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Jaw_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Jaw_Update,
    [ENTITY_DIE] =       (EnemyFunc)Jaw_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080694ac
static struct Entity* createPart6(struct DesertBoss* boss) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_DESERT_JAW);
    p->unk_28 = &boss->s;
    p->coord = (boss->s).coord;
    p->work[0] = p->work[1] = 0;
  }
  return p;
}

static struct DesertBoss* jawBoss(struct DesertJaw* p) { return (struct DesertBoss*)(p->s).unk_28; }

// Palette animation 5 started and removed at once, leaving the jaw's resting colors
static void restColors(void) {
  const PlttAnimData* a = &gApZ2Opening_PlttAnim5;
  CpuCopy16(a + 1, (u8*)gPaletteManager.buf + JAW_PALETTE + ((a->start << 1) & 0x1F),
            (a->end - a->start + 1) * 2);
}

// 0x08069510
static void Jaw_Init(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 9));
  UpdateSpriteAnimation(p);
  restColors();
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sJawIdleCollisions, 24, NULL);
  (s->spr).oam.priority = 3;
  s->renderPrio = 25;
  p->flashing = 0;
  p->homeX = s->coord.x;
  p->homeY = s->coord.y;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Jaw_Update(p);
}

static const EnemyFunc sJawStates[7];

// 0x080695d0
static void Jaw_Update(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  struct DesertBoss* boss = jawBoss(p);
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    (s->spr).oam.priority = boss->prio & 3;
    if ((boss->s).mode[0] <= ENTITY_UPDATE) {
      (sJawStates[s->mode[1]])((struct Enemy*)p);
      return;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Jaw_Die(p);
}

static void followJawBoss(struct DesertJaw* p) { (p->s).coord = (jawBoss(p)->s).coord; }

// 0x080696b4: rest until an order
static void Jaw_Idle(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  struct DesertBoss* boss = jawBoss(p);
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 9));
    SetDDP(&p->body, sJawIdleCollisions);
    restColors();
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followJawBoss(p);
  if (boss->order0) {
    setMode(s, JAW_BITE);
  } else if (boss->order1) {
    setMode(s, JAW_OPEN);
  }
}

// 0x08069728: bites during order 0
static void Jaw_Bite(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 11));
    SetDDP(&p->body, sJawBiteCollisions);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followJawBoss(p);
  if (!jawBoss(p)->order0) setMode(s, JAW_CLOSE);
}

// 0x08069778
static void Jaw_Close(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 12));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followJawBoss(p);
  if (IsSpriteAnimEnd(p)) setMode(s, JAW_IDLE);
}

// 0x080697bc: two chomps, then lunge
static void Jaw_Open(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 10));
    SetDDP(&p->body, sJawOpenCollisions);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followJawBoss(p);
  if ((s->motion).state == ANIM_NEXT_GOTO) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    s->work[2]++;
  }
  if (s->work[2] > 1) setMode(s, JAW_LUNGE);
}

// 0x08069820: out 200 px, flashing
static void Jaw_Lunge(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 9));
    s->d.x = PIXEL(2);
    ApStartPaletteAnimation(JAW_FLASH_ID, &gApZ2Opening_PlttAnim4, gApZ2Opening_PlttAnimScript4, JAW_PALETTE);
    p->flashing = JAW_FLASH;
    s->mode[3] = 0;
    PlaySound(SE_Z2_DESERT_JAW_LUNGE);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  StepPaletteAnimation(JAW_FLASH_ID);
  s->coord.x += s->d.x;
  if (s->mode[3] == 0) {
    if (s->coord.x - (jawBoss(p)->s).coord.x > PIXEL(200)) {
      s->d.x = 0;
      s->work[2] = 0;
      s->mode[3]++;
    }
  } else if (s->work[2]++ > 24) {
    setMode(s, JAW_SNAP);
  }
}

// 0x080698ac: two chomps
static void Jaw_Snap(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 10));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  StepPaletteAnimation(JAW_FLASH_ID);
  if ((s->motion).state == ANIM_NEXT_GOTO) {
    PlaySound(SE_Z2_FLOWER_CHOMP);
    s->work[2]++;
  }
  if (s->work[2] > 1) setMode(s, JAW_RETURN);
}

// 0x08069900: returns
static void Jaw_Return(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 9));
    s->d.x = -PIXEL(2);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  StepPaletteAnimation(JAW_FLASH_ID);
  s->coord.x += s->d.x;
  if (s->coord.x < (jawBoss(p)->s).coord.x) {
    RemovePaletteAnimation(JAW_FLASH_ID);
    p->flashing = 0;
    setMode(s, JAW_IDLE);
  }
}

static const EnemyFunc sJawStates[7] = {
    (EnemyFunc)Jaw_Idle,  (EnemyFunc)Jaw_Bite, (EnemyFunc)Jaw_Close,  (EnemyFunc)Jaw_Open,
    (EnemyFunc)Jaw_Lunge, (EnemyFunc)Jaw_Snap, (EnemyFunc)Jaw_Return,
};

// 0x08069648: breaks off in smoke
static void Jaw_Die(struct DesertJaw* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    EXIT_BODY(p);
    if (p->flashing != 0) RemovePaletteAnimation(0x8000 | p->flashing);
    s->mode[2]++;
  }
  CreateSmoke(1, &s->coord);
  PlaySound(SE_Z2_DESERT_JAW_BREAK);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  First visit's intro, Zero 2's script 9. Both are Zero 2's solid 5.
  work0 3: Pantheon Hunter
  work0 0x36: boss's jaw
*/

static void IntroHunter_Init(struct Solid* p);
static void IntroHunter_Update(struct Solid* p);
static void IntroJaw_Init(struct Solid* p);
static void IntroJaw_Update(struct Solid* p);
static void IntroSolid_Die(struct Solid* p);
static const struct Collision sIntroHunterCollision;
static const struct Collision sIntroJawCollisions[2];
static const struct SlashedEnemy sIntroHunterGibs[3];

// clang-format off
const SolidRoutine gApZ2IntroHunterRoutine = {
    [ENTITY_INIT] =      (SolidFunc)IntroHunter_Init,
    [ENTITY_UPDATE] =    (SolidFunc)IntroHunter_Update,
    [ENTITY_DIE] =       (SolidFunc)IntroSolid_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)IntroSolid_Die,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};

const SolidRoutine gApZ2IntroJawRoutine = {
    [ENTITY_INIT] =      (SolidFunc)IntroJaw_Init,
    [ENTITY_UPDATE] =    (SolidFunc)IntroJaw_Update,
    [ENTITY_DIE] =       (SolidFunc)IntroSolid_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)IntroSolid_Die,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 0x080c2528
static void IntroHunter_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  IntroHunter_Update(p);
}

// 0x080c256c: walks in, stands, falls apart when the jaw hits. Sheet at tile 512, palette 7.
static void IntroHunter_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  s32 i;
  switch (s->mode[1]) {
    case 0:
      wStaticGraphicTilenums[SM019_PANTHEON_HUNTER] = 512;
      wStaticMotionPalIDs[SM019_PANTHEON_HUNTER] = 7;
      LOAD_STATIC_GRAPHIC(SM019_PANTHEON_HUNTER);
      SetSpriteAnimation(p, MOTION(SM019_PANTHEON_HUNTER, 9));
      INIT_BODY(p, &sIntroHunterCollision, 0, NULL);
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      s->coord.x -= 128;
      if (s->scriptEntity->flags & 1) {
        SetSpriteAnimation(p, MOTION(SM019_PANTHEON_HUNTER, 0));
        s->work[2] = 15;
        s->mode[1]++;
      }
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) {
        SetSpriteAnimation(p, MOTION(SM019_PANTHEON_HUNTER, 1));
        s->mode[1]++;
      }
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if ((p->body).status & BODY_STATUS_DEAD) {
        SetSpriteAnimation(p, MOTION(SM019_PANTHEON_HUNTER, 3));
        s->mode[1]++;
      }
      break;
    case 4:
      UpdateSpriteAnimation(p);
      if (!IsSpriteAnimEnd(p)) break;
      at.x = s->coord.x;
      at.y = s->coord.y - PIXEL(24);
      for (i = 0; i < 3; i++) {
        CreateSlashedEnemy(&at, &sIntroHunterGibs[i], 0, s->flags & X_FLIP);
      }
      at.y = s->coord.y - PIXEL(16);
      CreateSmoke(1, &at);
      for (i = 0; i < 2; i++) {
        at.x = s->coord.x + PIXEL(16 - (RANDOM(RNG_0202f388) & 31));
        at.y = s->coord.y - PIXEL(RANDOM(RNG_0202f388) & 31);
        CreateSmoke(2, &at);
      }
      PlaySound(SE_ZAKO_EXPLODE);
      s->flags &= ~DISPLAY;
      EXIT_BODY(p);
      s->mode[1]++;
      break;
  }
}

// 0x080c879c: starts 168 px left of screen center
static void IntroJaw_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y) - PIXEL(20);
  s->coord.x = gStageRun.vm.camera.viewport.x - PIXEL(168);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  IntroJaw_Update(p);
}

// 0x080c87f8: crosses at 3 px a frame
static void IntroJaw_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      ApLoadSheet(&sSheets[1]);
      useApSheets(p);
      SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_BOSS0_B, 9));
      ApStartPaletteAnimation(JAW_FLASH_ID, &gApZ2Opening_PlttAnim4, gApZ2Opening_PlttAnimScript4, JAW_PALETTE);
      PlaySound(SE_Z2_DESERT_JAW_LUNGE);
      SET_XFLIP(p, FALSE);
      s->renderPrio = 31;
      INIT_BODY(p, sIntroJawCollisions, 0, NULL);
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      StepPaletteAnimation(JAW_FLASH_ID);
      s->coord.x += PIXEL(3);
      if (s->coord.x > gStageRun.vm.camera.viewport.x + 0x97FF) {
        s->flags &= ~DISPLAY;
        RemovePaletteAnimation(JAW_FLASH_ID);
        s->mode[1]++;
      }
      break;
  }
}

// 0x080c2358
static void IntroSolid_Die(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// 0x08348c48: neutral, so the jaw can hit it
static const struct Collision sIntroHunterCollision = {
    DRP, FACTION_NEUTRAL, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0x1000, 0x1000, 0x2000},
};

// 0x08348d40
static const struct Collision sIntroJawCollisions[2] = {
    {DDP, FACTION_ALLY, 0, 40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0, 1, 0x00000001, {0xa00, -0x400, 0x2200, 0x2400}},
    {DRP, FACTION_ALLY, 0, 40, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

// 0x08348c78, Zero 2's SM9 is Zero 3's SM19
static const struct SlashedEnemy sIntroHunterGibs[3] = {
    {MOTION(SM019_PANTHEON_HUNTER, 6), {0xff, 0x11}, {0, 0}, {128, -1280}, {255, 511}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(SM019_PANTHEON_HUNTER, 7), {0xfe, 0x11}, {0, 0}, {128, -512}, {127, 127}, {0, 64}, {0x200, 0x200}, {0}},
    {MOTION(SM019_PANTHEON_HUNTER, 8), {0xfe, 0x11}, {0, 0}, {256, -768}, {511, 511}, {0, 64}, {0x200, 0x200}, {0}},
};

// 0x0833a1d0: hurts to touch, invulnerable until the fight
static const struct Collision sIntroCollisions[2] = {
    {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1800}},
    {DRP, FACTION_ENEMY, 2, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1800}},
};

// 0x0833df74: by segment, hurts to touch
static const struct Collision sTailCollisions[10] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x1400, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0xc00, 0xc00}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

// 0x083152a4: 4x9 metatiles from x - 2, row 28
// 0x083152e8: 2x1 from x - 1, row 27, its last four ids
static const u16 sCraterPatch[38] = {
    4, 9,
    0xf1, 0xbd, 0xbe, 0xf0,
    0x101, 0xcd, 0xce, 0x100,
    0xf3, 0xcd, 0xce, 0xf2,
    0x103, 0xcd, 0xce, 0x102,
    0x103, 0xcd, 0xce, 0x102,
    0x103, 0xcd, 0xce, 0x102,
    0x103, 0xcd, 0xce, 0x102,
    0x103, 0xcd, 0xce, 0x102,
    2, 1, 0, 0,
};

// 0x083152f0
static const Coords32 sCraterSmoke[8] = {
    {-3072, 0}, {-2048, -2048}, {0, 1024}, {3072, -1024}, {1536, -3072}, {-512, 3584}, {-4096, 4608}, {2304, 2560},
};

// 0x0833e158: resting, can be hurt
static const struct Collision sJawIdleCollisions[1] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

// 0x0833e0e0: biting
static const struct Collision sJawBiteCollisions[3] = {
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 2, 0x00000000, {0x600, -0x600, 0x1200, 0x3200}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 1, 0x00000001, {0x1800, -0x600, 0x1400, 0x3200}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x1800, -0x600, 0x1400, 0x3200}},
};

// 0x0833e128: open, lunging
static const struct Collision sJawOpenCollisions[2] = {
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 1, 0x00000001, {0xa00, -0x400, 0x2200, 0x2400}},
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {-0x600, -0x200, 0x1600, 0x1000}},
};

// 0x0833dedc: by work0, front piece and legs
static const struct Collision sPartCollisions[4] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x2800, -0x400, 0x4000, 0x2800}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0xffffffff, {0x0, 0x0, 0x0, 0x0}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0, 0, 0x00000001, {-0x3800, -0x2800, 0x2000, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

#endif  // AP
