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
#include "physics.h"
#include "projectile.h"
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
#include "constants/song.h"

#if AP

/*
  Zero 2's boss 1, the Jungle's snake. Its body is the floor, eight blocks tail to head.
  The rider on it is the boss.
*/
struct Snake {
  OBJECT_HDR;
  Coords32 spawn;          // 0xB4
  u8 _bc;
  u8 picks;                // 0xBD
  u8 block;                // 0xBE, ours
  u8 end;                  // 0xBF, 0 tail or 7 head
  u8 order;                // 0xC0, for the blocks
  bool8 still;             // 0xC1, every block resting
  u8 wave;                 // 0xC2
  u8 lastState;            // 0xC3
  struct SnakeBlock* blocks[8];  // 0xC4
};
static_assert(sizeof(struct Snake) == sizeof(struct Boss));

/*
  Zero 2's solid 1, a block of its body.
  work0: index, 0 tail, 7 head
*/
struct SnakeBlock {
  OBJECT_HDR;
  Coords32 home;    // 0xB4
  u8 _bc;
  u8 patch;         // 0xBD
  motion_t next;    // 0xBE, set by rider
  s32 target;       // 0xC0
};
static_assert(sizeof(struct SnakeBlock) == sizeof(struct Solid));

enum { SNAKE_INTRO, SNAKE_START, SNAKE_NOP2, SNAKE_PICK, SNAKE_WAIT, SNAKE_NOP5, SNAKE_CROUCH, SNAKE_JUMP,
       SNAKE_LAND, SNAKE_CRAWL_START, SNAKE_CRAWL, SNAKE_CRAWL_END, SNAKE_RAISE, SNAKE_LASH, SNAKE_SETTLE,
       SNAKE_CALL, SNAKE_CALL2, SNAKE_CALL_WAIT, SNAKE_DIVE, SNAKE_GRAB, SNAKE_SURFACE, SNAKE_AIM, SNAKE_SHOOT,
       SNAKE_SHOT_WAIT, SNAKE_EX, SNAKE_RIDE, SNAKE_RIDE_BACK, SNAKE_HOP_CROUCH, SNAKE_HOP };

// What a block's mode does when its rider orders it
enum { BLOCK_REST, BLOCK_HEAVE_UP, BLOCK_HEAVE_UP_END, BLOCK_HEAVE_DOWN, BLOCK_HEAVE_DOWN_END, BLOCK_STAIR_UP,
       BLOCK_STAIR_DOWN, BLOCK_GATHER_4, BLOCK_GATHER_3, BLOCK_REAR_HEAD, BLOCK_REAR_HEAD2, BLOCK_REAR_HEAD3,
       BLOCK_REAR_HEAD4, BLOCK_REAR_TAIL, BLOCK_REAR_TAIL2, BLOCK_REAR_TAIL3, BLOCK_REAR_TAIL4, BLOCK_SWEEP_HEAD,
       BLOCK_SWEEP_HEAD2, BLOCK_SWEEP_UP, BLOCK_SWEEP_TAIL, BLOCK_SWEEP_TAIL2, BLOCK_SWEEP_UP2, BLOCK_SWEEP_DOWN,
       BLOCK_HOME, BLOCK_SPARK_RIGHT, BLOCK_SPARK_LEFT, BLOCK_OPEN, BLOCK_FIRE };

/*
  Zero 2's enemy 24.
  work0:
    0: arm from block work1, grabs Zero
    1: arm under rider
    2: rider's top half, cut off
*/
struct SnakeArm {
  OBJECT_HDR;
  u8 _b4[16];
};
static_assert(sizeof(struct SnakeArm) == sizeof(struct Enemy));

// Zero 2's enemy 25, a spring that hops along the body and bursts off its end
struct SnakeSpring {
  OBJECT_HDR;
  u8 _b4[16];
};
static_assert(sizeof(struct SnakeSpring) == sizeof(struct Enemy));

/*
  Zero 2's projectile 19.
  work0:
    0: spark from a block, work1 xflip
    1: bolt hopping block to block, three to a volley
*/
struct SnakeShot {
  OBJECT_HDR;
  u8 _b4[8];
  u8 half;      // 0xBC, of sOpenOrder
  u8 n;         // 0xBD, 0 bolt, 1 and 2 trail it
  u8 _be[6];
};
static_assert(sizeof(struct SnakeShot) == sizeof(struct Projectile));

#define PATCH_BODY 1
#define PATCH_END 2
#define PATCH_CLEAR 3

#define SNAKE(n) MOTION(DM206_Z2_SNAKE, (n))
#define SEGMENT(n) MOTION(AP_SHEET_Z2_SNAKE_BODY, (n))

#define GRAVITY 64
#define MAX_FALL 0x700

static void Snake_Init(struct Snake* p);
static void Snake_Update(struct Snake* p);
static void Snake_Die(struct Snake* p);
static void Block_Init(struct SnakeBlock* p);
static void Block_Update(struct SnakeBlock* p);
static void Block_Die(struct SnakeBlock* p);

static struct Entity* createPart(struct Snake* p, u8 kind, u8 block);
static struct Entity* createCaller(struct Snake* p);
static void createShot(struct Snake* p, u8 half, u8 pattern, u8 n);
static void createSpark(struct SnakeBlock* p, u8 xflip);

static const BossFunc sStates[29];
static const SolidFunc sBlockModes[29];
static const struct Collision sCollisions[23];
static const struct Collision sBlockCollisions[2];
static const struct PreloadEntity sBodySheet = {AP_SHEET_Z2_SNAKE_BODY, 0, 640, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSpringSheet = {AP_SHEET_Z2_SNAKE_SPRING, 0, 640 + AP_SHEET_Z2_SNAKE_BODY_TILES, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct Coord sElementCoord = {0, -PIXEL(20)};

// clang-format off
const BossRoutine gApZ2SnakeRoutine = {
    [ENTITY_INIT] =      (BossFunc)Snake_Init,
    [ENTITY_UPDATE] =    (BossFunc)Snake_Update,
    [ENTITY_DIE] =       (BossFunc)Snake_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};

const SolidRoutine gApZ2SnakeBlockRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Block_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Block_Update,
    [ENTITY_DIE] =       (SolidFunc)Block_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void faceZero(struct Entity* s) { SET_XFLIP(s, s->coord.x < (pZero2->s).coord.x); }

static bool8 facingRight(struct Entity* s) { return (s->flags & X_FLIP) != 0; }

static void snapToFloor(struct Entity* s) { s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y); }

// 32 px steps from spawn
static u8 blockAt(struct Snake* p, s32 x) { return (u8)((x - (p->spawn).x + PIXEL(16)) / PIXEL(32)); }

static s32 distance(s32 a, s32 b) { return a > b ? a - b : b - a; }

static u8 randomBlock(void) { return (u8)(RANDOM(RNG_0202f388) % 6 + 1); }

static void setOrder(struct Snake* p, u8 order) {
  p->order = order;
  p->wave = order;
}

static void createBlock(struct Snake* p, u8 i) {
  struct Entity* b = AllocEntityLast(gSolidHeaderPtr);
  if (b != NULL) {
    INIT_SOLID_ROUTINE(b, SOLID_Z2_SNAKE_BLOCK);
    b->unk_28 = &p->s;
    b->work[0] = i;
    b->work[1] = 0;
  }
  p->blocks[i] = (struct SnakeBlock*)b;
}

// 0x08040098
static void Snake_Init(struct Snake* p) {
  struct Entity* s = &p->s;
  u8 i;
  ApLoadSheet(&sBodySheet);
  ApLoadSheet(&sSpringSheet);
  InitNonAffineMotion(s);
  s->flags = (s->flags & ~DISPLAY) | FLIPABLE;
  ResetDynamicMotion(s);
  SET_XFLIP(s, FALSE);
  ResetBossBody((struct Boss*)p, sCollisions, 64);
  p->spawn = s->coord;
  p->picks = 0;
  p->order = 0;
  s->unk_2c = NULL;
  p->lastState = 0;
  p->still = TRUE;
  p->wave = 0;
  for (i = 0; i < 8; i++) createBlock(p, i);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = SNAKE_INTRO;
  Snake_Update(p);
}

static bool8 allResting(struct Snake* p) {
  u8 i;
  for (i = 0; i < 8; i++) {
    if ((p->blocks[i]->s).mode[1] != BLOCK_REST) return FALSE;
  }
  return TRUE;
}

// 0x080401e8
static void Snake_Update(struct Snake* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Snake_Die(p);
    return;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(8, (Object*)p, &sElementCoord);
  }
  if (s->unk_2c != NULL && isKilled(s->unk_2c)) s->unk_2c = NULL;
  if (!p->still && allResting(p)) {
    p->still = TRUE;
    p->order = 0;
  }
  (sStates[s->mode[1]])((struct Boss*)p);
}

// 0x080402c8: cut in two or slumps, waits for script, bursts
static void Snake_Die(struct Snake* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    s->unk_28 = NULL;
    if ((p->body).status & BODY_STATUS_SLASHED) {
      SetSpriteAnimation(p, SNAKE(0x13));
      if (facingRight(s)) {
        s->d.x = 64;
        s->unk_coord.x = -1;
      } else {
        s->d.x = -64;
        s->unk_coord.x = 1;
      }
      s->unk_28 = (struct Entity*)createPart(p, 2, 0);
      PlaySound(SE_LIGHT);
      s->mode[1] = 0;
    } else {
      SetSpriteAnimation(p, SNAKE(0x12));
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
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[1] = 1;
      break;
    case 1:
      if (s->scriptEntity->flags & 0x80) s->mode[1] = 2;
      break;
    case 2:
      if (s->mode[3] == 0) {
        at.x = facingRight(s) ? -PIXEL(4) : PIXEL(4);
        at.y = -0x2200;
        s->unk_2c = CreateBossExplosion(s, &at);
        s->mode[3]++;
      }
      if (s->unk_2c->mode[0] > ENTITY_UPDATE) gStageRun.vm.active |= VM_FLAG1;
      break;
  }
}

// 0x08040438: rises from the ground, or appears at once on a return visit (work1 1)
static void Snake_Intro(struct Snake* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    s->work[2] = 32;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      if (--s->work[2] != 0xFF) break;
      snapToFloor(s);
      if (s->work[1] != 0) {
        s->coord.x += PIXEL(192);
        s->mode[3] = 5;
      } else {
        s->coord.x += PIXEL(224);
        s->mode[3] = 1;
      }
      break;
    case 1:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, SNAKE(0x1B));
      PlaySound(SE_Z2_SNAKE_CRAWL);
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->motion).cmdIdx > 1) {
        s->coord.x -= 0x555;
        if (s->work[2]++ & 1) {
          at.x = s->coord.x + 0x2400;
          at.y = s->coord.y;
          CreateSmoke(3, &at);
        }
      }
      if ((s->motion).state == ANIM_NEXT_GOTO) s->mode[3]++;
      break;
    case 3:
      SetSpriteAnimation(p, SNAKE(5));
      s->mode[3]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[3]++;
      break;
    case 5:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, SNAKE(0));
      s->mode[3]++;
      FALLTHROUGH;
    case 6:
      UpdateSpriteAnimation(p);
      if (s->scriptEntity->flags & 1) setMode(s, SNAKE_START);
      break;
  }
}

// 0x080405a0: first heave, then picks once the script lets go
static void Snake_Start(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    setOrder(p, BLOCK_HEAVE_UP);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, SNAKE_PICK);
}

static void Snake_Nop(struct Snake* p UNUSED) {}

// Block to jump to: Zero's, or a random one when he is off the body
static void aimAtZero(struct Snake* p) {
  struct Entity* s = &p->s;
  s->work[2] = blockAt(p, (pZero2->s).coord.x);
  if (s->work[2] > 7) s->work[2] = randomBlock();
}

/*
  0x080405f8: near Zero raises the body or dives, far jumps or dives, never the same twice running.
  Every seventh pick is a set move, in turn.
*/
static void Snake_Pick(struct Snake* p) {
  struct Entity* s = &p->s;
  s32 zero = (pZero2->s).coord.x;
  bool8 near = distance(s->coord.x, zero) < PIXEL(96);
  u8 mode;
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if (p->picks <= 5) {
    p->block = blockAt(p, s->coord.x);
    s->work[3] = blockAt(p, zero);
    if (p->block == s->work[3] || s->work[3] == 0 || s->work[3] > 6 || p->block == 0 || p->block > 6) {
      if (near) {
        mode = SNAKE_RAISE;
        if (p->lastState == SNAKE_RAISE) {
          mode = SNAKE_CROUCH;
          aimAtZero(p);
        }
      } else {
        mode = SNAKE_CROUCH;
        aimAtZero(p);
        if (p->lastState == SNAKE_CROUCH) mode = SNAKE_RAISE;
      }
    } else if (near) {
      mode = (RANDOM(RNG_0202f388) & 1) ? SNAKE_RAISE : SNAKE_DIVE;
      if (mode == p->lastState) mode = (mode == SNAKE_RAISE) ? SNAKE_DIVE : SNAKE_RAISE;
    } else {
      mode = SNAKE_DIVE;
      if (RANDOM(RNG_0202f388) & 1) {
        mode = SNAKE_CROUCH;
        aimAtZero(p);
      }
      if (mode == p->lastState) mode = SNAKE_DIVE;
    }
  } else {
    switch (p->picks) {
      case 6: mode = SNAKE_CRAWL_START; break;
      case 7: mode = SNAKE_HOP_CROUCH; break;
      case 8: mode = gScore.total->rank > 4 ? SNAKE_EX : SNAKE_CALL; break;
      case 9: mode = SNAKE_CALL; break;
      case 10: mode = SNAKE_RIDE; break;
      case 11: mode = SNAKE_AIM; break;
      case 12: mode = SNAKE_RIDE_BACK; break;
      default:
        mode = SNAKE_CROUCH;
        s->work[2] = blockAt(p, zero);
        if ((u8)(s->work[2] - 1) > 5) s->work[2] = randomBlock();
        p->picks = 0xFF;
        break;
    }
  }
  if (mode != SNAKE_CALL) faceZero(s);
  p->lastState = mode;
  setMode(s, mode);
  p->picks++;
}

// 0x080409f0
static void Snake_Wait(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, SNAKE_PICK);
}

// 0x08040a34
static void Snake_Crouch(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(6));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_JUMP);
}

static s32 blockX(struct Snake* p, u8 i) { return (p->blocks[i]->s).coord.x; }

// 0x08040a70: onto block work2, heaving the body once the run is long
static void Snake_Jump(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(7));
    s->d.x = (blockX(p, s->work[2]) - s->coord.x) / 24;
    s->d.y = -0x600;
    s->mode[3] = 0;
    s->mode[2]++;
    if (p->picks > 6) setOrder(p, s->work[2] > 3 ? BLOCK_HEAVE_UP : BLOCK_HEAVE_DOWN);
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[3]) {
    case 0:
      s->d.y += GRAVITY;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->d.y < 0) break;
      faceZero(s);
      s->coord.x = blockX(p, s->work[2]);
      s->work[2] = 8;
      s->mode[3]++;
      break;
    case 1:
      if (--s->work[2] == 0xFF) s->mode[3]++;
      break;
    case 2:
      s->d.y += 256;
      if (s->d.y > MAX_FALL) s->d.y = MAX_FALL;
      s->coord.y += s->d.y;
      if (FUN_080098a4(s->coord.x, s->coord.y)) {
        snapToFloor(s);
        setMode(s, SNAKE_LAND);
      }
      break;
  }
}

static void pickOrSettle(struct Snake* p) { setMode(&p->s, p->picks <= 5 ? SNAKE_PICK : SNAKE_SETTLE); }

// 0x08040bc8
static void Snake_Land(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(8));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if ((s->motion).state == ANIM_END) pickOrSettle(p);
}

// 0x08040c1c
static void Snake_CrawlStart(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(3));
    s->mode[2]++;
    s->work[2] = 16;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_CRAWL);
}

// Hitbox by frame of the crawl
static const u8 sCrawlHitboxes[4] = {0, 15, 17, 21};

// 0x08040c5c: crawls to an end of the body, low
static void Snake_Crawl(struct Snake* p) {
  struct Entity* s = &p->s;
  s8 frame;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0x1B));
    PlaySound(SE_Z2_SNAKE_CRAWL);
    s->d.x = facingRight(s) ? 0x555 : -0x555;
    s->work[2] = 0;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  frame = (s->motion).cmdIdx;
  if (s->mode[3] == 0) {
    if (frame == 0) {
      PlaySound(SE_Z2_SNAKE_CRAWL);
      s->mode[3]++;
    }
  } else if (frame != 0) {
    s->mode[3] = 0;
  }
  if (frame > 1) {
    s->coord.x += s->d.x;
    if (s->work[2]++ & 1) {
      at.x = s->coord.x + (facingRight(s) ? -0x2400 : 0x2400);
      at.y = s->coord.y;
      CreateSmoke(3, &at);
    }
  }
  SetDDP(&p->body, &sCollisions[sCrawlHitboxes[frame]]);
  if (facingRight(s)) {
    if (s->coord.x > blockX(p, 7)) {
      s->coord.x = blockX(p, 7);
      setMode(s, SNAKE_CRAWL_END);
    }
  } else if (s->coord.x < blockX(p, 0)) {
    s->coord.x = blockX(p, 0);
    setMode(s, SNAKE_CRAWL_END);
  }
}

// 0x08040d8c
static void Snake_CrawlEnd(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(5));
    SetDDP(&p->body, &sCollisions[0]);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_PICK);
}

// Heave toward the far end from ours
static void heaveAway(struct Snake* p) {
  setOrder(p, (p->s).coord.x > blockX(p, 0) + PIXEL(112) ? BLOCK_HEAVE_UP : BLOCK_HEAVE_DOWN);
}

// 0x08040dd4
static void Snake_Raise(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(1));
    s->mode[2]++;
    if (p->order == 0) {
      heaveAway(p);
      s->work[2] = 64;
    } else {
      s->work[2] = 32;
    }
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if (--s->work[2] == 0xFF) setMode(s, SNAKE_LASH);
}

// 0x08040e54: lash grows over its frames
static void Snake_Lash(struct Snake* p) {
  struct Entity* s = &p->s;
  static const s8 sFrames[5] = {2, 3, 4, 6, 7};
  static const u8 sHitboxes[5] = {2, 5, 9, 12, 0};
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(2));
    PlaySound(SE_Z2_SNAKE_LASH);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] < 5 && (s->motion).cmdIdx == sFrames[s->mode[3]]) {
    SetDDP(&p->body, &sCollisions[sHitboxes[s->mode[3]]]);
    s->mode[3]++;
  }
  snapToFloor(s);
  if ((s->motion).state == ANIM_END) pickOrSettle(p);
}

// 0x08040f68: waits out the heave it started
static void Snake_Settle(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    if (p->wave == BLOCK_HEAVE_UP) {
      p->order = BLOCK_HEAVE_UP_END;
      p->wave = 0;
    } else if (p->wave == BLOCK_HEAVE_DOWN) {
      p->order = BLOCK_HEAVE_DOWN_END;
      p->wave = 0;
    }
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if (p->order == 0) setMode(s, SNAKE_PICK);
}

// 0x08040fc8
static void Snake_Call(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0x16));
    s->unk_28 = createCaller(p);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[3]++;
      break;
    case 1:
      SetSpriteAnimation(p, SNAKE(0x18));
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) setMode(s, SNAKE_CALL2);
      break;
  }
}

// 0x0804104c
static void Snake_Call2(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0x19));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_CALL_WAIT);
}

static bool8 childDone(struct Snake* p) { return (p->s).unk_28->mode[0] > ENTITY_UPDATE; }

// 0x08041088
static void Snake_CallWait(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (childDone(p)) setMode(s, SNAKE_PICK);
}

static void showOnBlock(struct Snake* p, u8 i, motion_t m) { p->blocks[i]->next = m; }

// 0x080410c0: sinks into its block
static void Snake_Dive(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(9));
    if (p->order == 0) heaveAway(p);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] == 17) showOnBlock(p, p->block, SEGMENT(0x14));
  snapToFloor(s);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_GRAB);
}

// 0x0804115c: arms come up under Zero's block
static void Snake_Grab(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0xA));
    PlaySound(SE_Z2_SNAKE_LASH);
    showOnBlock(p, p->block, SEGMENT(0x15));
    s->work[2] = 16;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if (s->mode[3] != 0) {
    if (childDone(p)) setMode(s, SNAKE_SURFACE);
  } else if (--s->work[2] == 0xFF) {
    showOnBlock(p, s->work[3], SEGMENT(0x18));
    s->unk_28 = (struct Entity*)createPart(p, 0, s->work[3]);
    if (s->unk_28 != NULL) createPart((struct Snake*)s->unk_28, 1, s->work[3]);
    s->mode[3]++;
  }
}

// 0x08041210
static void Snake_Surface(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    showOnBlock(p, p->block, SEGMENT(0x1A));
    s->work[2] = 32;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  snapToFloor(s);
  if (s->mode[3] != 0) {
    UpdateSpriteAnimation(p);
    if ((s->motion).state == ANIM_END) pickOrSettle(p);
    return;
  }
  if (--s->work[2] == 0xFF) {
    SetSpriteAnimation(p, SNAKE(0xB));
    showOnBlock(p, p->block, SEGMENT(0x17));
    s->mode[3]++;
  }
  UpdateSpriteAnimation(p);
}

// Blocks that open in turn, by end and pattern
static const u8 sOpenOrder[2][3][6] = {
    {{5, 6, 4, 3, 2, 1}, {5, 3, 4, 1, 6, 2}, {5, 2, 1, 3, 4, 6}},
    {{2, 1, 3, 4, 5, 6}, {2, 4, 3, 6, 1, 5}, {2, 5, 6, 4, 3, 1}},
};

static const u8* openOrder(struct Snake* p) { return sOpenOrder[p->end == 7 ? 0 : 1][(p->s).work[3]]; }

static void orderBlock(struct Snake* p, u8 i, u8 mode) { setMode(&(p->blocks[i]->s), mode); }

// 0x080412bc: opens six blocks in a random order, one each 8 frames
static void Snake_Aim(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    s->work[2] = 0;
    s->work[3] = (u8)(RANDOM(RNG_0202f388) % 3);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) setMode(s, SNAKE_SHOOT);
    return;
  }
  if ((s->work[2] & 7) == 0) orderBlock(p, openOrder(p)[s->work[2] >> 3], BLOCK_OPEN);
  if ((++s->work[2] >> 3) > 5) {
    s->work[2] = 16;
    s->mode[3]++;
  }
}

// 0x08041398: first open block fires three shots
static void Snake_Shoot(struct Snake* p) {
  struct Entity* s = &p->s;
  u8 kind = p->end == 7 ? 0 : 1;
  if (s->mode[2] == 0) {
    orderBlock(p, openOrder(p)[0], BLOCK_FIRE);
    createShot(p, kind, s->work[3], 0);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
    s->mode[2]++;
    s->work[2] = 0;
  }
  UpdateSpriteAnimation(p);
  if (s->work[2] == 2) {
    createShot(p, kind, s->work[3], 1);
  } else if (s->work[2] == 4) {
    createShot(p, kind, s->work[3], 2);
  }
  if (s->work[2]++ > 7) setMode(s, SNAKE_SHOT_WAIT);
}

// 0x080414b8
static void Snake_ShotWait(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[2] = 0xFF;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(s, SNAKE_PICK);
}

// Every other block from 1 or 2
static void orderAlternate(struct Snake* p, u8 first, u8 mode) {
  orderBlock(p, first, mode);
  orderBlock(p, first + 2, mode);
  orderBlock(p, first + 4, mode);
}

// 0x080414ec: rank above 4, alternate blocks rise and fall twice
static void Snake_Ex(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    s->mode[3] = 0;
    s->work[2] = 0;
    s->work[3] = 1;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[3]) {
    case 0:
      if (p->end == 0) {
        orderAlternate(p, 2, BLOCK_SPARK_RIGHT);
      } else {
        orderAlternate(p, 1, BLOCK_SPARK_LEFT);
      }
      s->work[2] = 64;
      s->mode[3]++;
      break;
    case 1:
      if (--s->work[2] == 0xFF) s->mode[3]++;
      break;
    case 2:
      if (p->end == 0) {
        orderAlternate(p, 1, BLOCK_SPARK_RIGHT);
      } else {
        orderAlternate(p, 2, BLOCK_SPARK_LEFT);
      }
      s->work[2] = 64;
      s->mode[3]++;
      break;
    case 3:
      if (--s->work[2] == 0xFF) setMode(s, SNAKE_PICK);
      break;
  }
}

static void followEnd(struct Snake* p) {
  (p->s).coord = (p->blocks[p->end]->s).coord;
}

// 0x080415c8: rides its end as the body rears up, then back
static void Snake_Ride(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    setOrder(p, p->end == 0 ? BLOCK_GATHER_3 : BLOCK_GATHER_4);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followEnd(p);
  if (s->mode[3] != 0) {
    if (p->order == 0) setMode(s, SNAKE_PICK);
  } else if (p->order == 0) {
    setOrder(p, p->end == 0 ? BLOCK_REAR_TAIL : BLOCK_REAR_HEAD);
    s->mode[3]++;
  }
}

// 0x08041674
static void Snake_RideBack(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(0));
    p->order = p->end == 0 ? BLOCK_SWEEP_TAIL : BLOCK_SWEEP_HEAD;
    p->wave = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  followEnd(p);
  if (p->order == 0) setMode(s, SNAKE_PICK);
}

// 0x080416ec
static void Snake_HopCrouch(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(6));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  snapToFloor(s);
  if ((s->motion).state == ANIM_END) setMode(s, SNAKE_HOP);
}

// 0x08041730: to the end farther from Zero, which climbs as a stair
static void Snake_Hop(struct Snake* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, SNAKE(7));
    if ((pZero2->s).coord.x > blockX(p, 0) + PIXEL(112)) {
      p->end = 0;
      setOrder(p, BLOCK_STAIR_DOWN);
    } else {
      p->end = 7;
      setOrder(p, BLOCK_STAIR_UP);
    }
    s->d.x = (blockX(p, p->end) - s->coord.x) / 48;
    s->d.y = -0xC00;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    s->d.y += GRAVITY;
    if (s->d.y > MAX_FALL) s->d.y = MAX_FALL;
    s->coord.y += s->d.y;
    if (FUN_080098a4(s->coord.x, s->coord.y)) {
      snapToFloor(s);
      setMode(s, SNAKE_LAND);
    }
    return;
  }
  s->d.y += GRAVITY;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (s->d.y < 0) return;
  s->coord.x = blockX(p, p->end);
  SET_XFLIP(s, p->end == 0);
  s->mode[3]++;
}

static const BossFunc sStates[29] = {
    (BossFunc)Snake_Intro,     (BossFunc)Snake_Start,      (BossFunc)Snake_Nop,       (BossFunc)Snake_Pick,
    (BossFunc)Snake_Wait,      (BossFunc)Snake_Nop,        (BossFunc)Snake_Crouch,    (BossFunc)Snake_Jump,
    (BossFunc)Snake_Land,      (BossFunc)Snake_CrawlStart, (BossFunc)Snake_Crawl,     (BossFunc)Snake_CrawlEnd,
    (BossFunc)Snake_Raise,     (BossFunc)Snake_Lash,       (BossFunc)Snake_Settle,    (BossFunc)Snake_Call,
    (BossFunc)Snake_Call2,     (BossFunc)Snake_CallWait,   (BossFunc)Snake_Dive,      (BossFunc)Snake_Grab,
    (BossFunc)Snake_Surface,   (BossFunc)Snake_Aim,        (BossFunc)Snake_Shoot,     (BossFunc)Snake_ShotWait,
    (BossFunc)Snake_Ex,        (BossFunc)Snake_Ride,       (BossFunc)Snake_RideBack,  (BossFunc)Snake_HopCrouch,
    (BossFunc)Snake_Hop,
};

// --------------------------------------------

static const u16 sBodyPatch[2 + 4] = {2, 2, 0x128, 0x129, 0x138, 0x139};
static const u16 sEndPatch[2 + 4] = {2, 2, 0x126, 0x127, 0x136, 0x137};
static const u16 sClearPatch[2 + 4] = {2, 2, 0, 0, 0, 0};
static const struct Rect sBlockSize = {0, 0xFFF, PIXEL(32), PIXEL(32)};

#define INDEX(p) ((p)->s).work[0]
#define RIDER(p) ((struct Snake*)((p)->s).unk_28)

static bool8 isMiddle(struct SnakeBlock* p) { return (u8)(INDEX(p) - 1) <= 5; }

static struct SnakeBlock* neighbour(struct SnakeBlock* p, s8 by) { return RIDER(p)->blocks[INDEX(p) + by]; }

// 0x080bfaf4
static void Block_Init(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  struct Entity* rider = s->unk_28;
  s->coord.x = (rider->coord.x + INDEX(p) * PIXEL(32) + 1) & ~0xFF;
  s->coord.y = (rider->coord.y + 0x6001) & ~0xFF;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= FLIPABLE;
  if (INDEX(p) == 0) {
    SetSpriteAnimation(p, SEGMENT(1));
    s->flags |= DISPLAY;
    p->patch = PATCH_END;
  } else if (INDEX(p) == 7) {
    SetSpriteAnimation(p, SEGMENT(0));
    s->flags |= DISPLAY;
    p->patch = PATCH_END;
  } else {
    SetSpriteAnimation(p, SEGMENT(2));
    s->flags &= ~DISPLAY;
    p->patch = PATCH_BODY;
  }
  UpdateSpriteAnimation(p);
  INIT_BODY(p, sBlockCollisions, 1, NULL);
  SET_XFLIP(s, FALSE);
  p->next = 0;
  p->home = s->coord;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = BLOCK_REST;
  Block_Update(p);
}

static void patchAt(const Coords32* at, const u16* patch) { PatchMetatileMap((at->x >> 12) - 1, ((at->y - 1) >> 12) + 1, patch); }

// 0x080bfc0c
static void Block_Update(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  if (s->unk_28->mode[0] > ENTITY_UPDATE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Block_Die(p);
    return;
  }
  switch (p->patch) {
    case PATCH_BODY:
      patchAt(&s->coord, sBodyPatch);
      s->flags2 &= ~ENTI_PHYSICS;
      p->patch = 0;
      break;
    case PATCH_END:
      patchAt(&s->coord, sEndPatch);
      s->flags2 &= ~ENTI_PHYSICS;
      p->patch = 0;
      break;
    case PATCH_CLEAR:
      patchAt(&s->unk_coord, sClearPatch);
      p->patch = 0;
      break;
  }
  (sBlockModes[s->mode[1]])((struct Solid*)p);
}

// 0x080bfd30: shows whole until rider leaves
static void Block_Die(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (isMiddle(p)) {
      SetSpriteAnimation(p, SEGMENT(2));
      s->flags |= DISPLAY;
    }
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->unk_28->mode[0] == ENTITY_DISAPPEAR) SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
}

// Solid while it moves, terrain again once it stops
static void lift(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  s->unk_coord = s->coord;
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sBlockSize;
  s->physicsAttr = 0x2401;
  p->patch = PATCH_CLEAR;
}

static void showBody(struct SnakeBlock* p) {
  SetSpriteAnimation(p, SEGMENT(2));
  UpdateSpriteAnimation(p);
  (p->s).flags |= DISPLAY;
}

static void settle(struct SnakeBlock* p) {
  if (isMiddle(p)) {
    SetSpriteAnimation(p, SEGMENT(0x13));
    UpdateSpriteAnimation(p);
    p->patch = PATCH_BODY;
  } else {
    p->patch = PATCH_END;
  }
}

static void moveTo(struct SnakeBlock* p, s32 dx) {
  struct Entity* s = &p->s;
  s->coord.x += dx;
  if (dx > 0 ? s->coord.x > p->target : s->coord.x < p->target) s->coord.x = p->target;
}

static void heaveY(struct SnakeBlock* p) { (p->s).coord.y = (p->home).y - (SIN((p->s).work[2]) << 5); }

// 0x080bfd88: middle blocks are terrain, so their sprite goes once shown
static void Block_Rest(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  struct Snake* rider = RIDER(p);
  UpdateSpriteAnimation(p);
  if (isMiddle(p) && (s->motion).state == ANIM_END) s->flags &= ~DISPLAY;
  if (rider->still && rider->order != 0) setMode(s, rider->order);
}

// 0x080bfdd0, 0x080bff7c: travelling wave, each block a step behind the next
static void heave(struct SnakeBlock* p, u8 start) {
  struct Entity* s = &p->s;
  struct Snake* rider = RIDER(p);
  if (s->mode[2] == 0) {
    if (isMiddle(p)) {
      SetSpriteAnimation(p, SEGMENT(2));
      s->flags |= DISPLAY;
    }
    lift(p);
    s->work[2] = start;
    s->mode[3] = 0;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (isMiddle(p) && p->next != 0) {
    SetSpriteAnimation(p, p->next);
    UpdateSpriteAnimation(p);
    p->next = 0;
  }
  if (s->mode[3] != 0) {
    if ((s->work[2] & 0x7F) == 0) PlaySound(SE_Z2_SNAKE_HEAVE);
    s->work[2] += 2;
    heaveY(p);
    if (rider->order != BLOCK_HEAVE_UP) s->mode[1] = rider->order;
  } else if (--s->work[2] == 0) {
    PlaySound(SE_Z2_SNAKE_HEAVE);
    s->mode[3]++;
  }
}

static void Block_HeaveUp(struct SnakeBlock* p) { heave(p, 57 - INDEX(p) * 8); }
static void Block_HeaveDown(struct SnakeBlock* p) { heave(p, INDEX(p) * 8 + 1); }

// 0x080bfed4, 0x080c0080: comes to rest once the block toward the end it started from has
static void heaveEnd(struct SnakeBlock* p, u8 last, s8 by) {
  struct Entity* s = &p->s;
  bool8 ready;
  if (INDEX(p) == last) {
    RIDER(p)->still = FALSE;
    ready = TRUE;
  } else {
    ready = (neighbour(p, by)->s).mode[1] == BLOCK_REST;
  }
  UpdateSpriteAnimation(p);
  if (ready && (s->work[2] & 0x7F) == 0) {
    s->coord.y = (p->home).y;
    settle(p);
    setMode(s, BLOCK_REST);
  } else {
    s->work[2] += 2;
    heaveY(p);
  }
}

static void Block_HeaveUpEnd(struct SnakeBlock* p) { heaveEnd(p, 7, 1); }
static void Block_HeaveDownEnd(struct SnakeBlock* p) { heaveEnd(p, 0, -1); }

// 0x080c0128, 0x080c0264: rises to height steps after delay, in turn
static void stair(struct SnakeBlock* p, u8 steps, u8 delay) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->target = s->coord.y - steps * PIXEL(32);
    s->work[2] = delay;
    if (INDEX(p) == 7) {
      RIDER(p)->still = FALSE;
      lift(p);
      s->mode[3] = 1;
    } else {
      s->mode[3] = 0;
    }
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    s->coord.y -= PIXEL(3);
    if (s->coord.y > p->target) return;
    settle(p);
    s->coord.y = p->target;
    setMode(s, BLOCK_REST);
  } else if (--s->work[2] == 0xFF) {
    if (INDEX(p) != 0) showBody(p);
    lift(p);
    PlaySound(SE_Z2_SNAKE_HEAVE);
    s->mode[3]++;
  }
}

static void Block_StairUp(struct SnakeBlock* p) { stair(p, INDEX(p), (7 - INDEX(p)) * 10); }
static void Block_StairDown(struct SnakeBlock* p) { stair(p, 7 - INDEX(p), INDEX(p) * 10); }

// 0x080c03a0, 0x080c04b0: all close up on block `on`
static void gather(struct SnakeBlock* p, u8 on) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->target = (RIDER(p)->blocks[on]->s).coord.x;
    if (INDEX(p) == on) {
      RIDER(p)->still = FALSE;
      setMode(s, BLOCK_REST);
      PlaySound(SE_Z2_SNAKE_HEAVE);
      return;
    }
    if (isMiddle(p)) showBody(p);
    lift(p);
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (INDEX(p) < on) {
    moveTo(p, PIXEL(3));
  } else if (INDEX(p) > on) {
    moveTo(p, -PIXEL(3));
  }
  if (s->coord.x == p->target) {
    settle(p);
    setMode(s, BLOCK_REST);
  }
}

static void Block_Gather4(struct SnakeBlock* p) { gather(p, 4); }
static void Block_Gather3(struct SnakeBlock* p) { gather(p, 3); }

/*
  0x080c05c0..0x080c09e4 rear the body toward the head, 0x080c09e4..0x080c0df8 toward the tail,
  four steps each. dx is toward the end.
*/
static void rear1(struct SnakeBlock* p, s32 dx, u8 next) {
  struct Entity* s = &p->s;
  bool8 moves = (u8)(INDEX(p) - 3) <= 1;
  if (s->mode[2] == 0) {
    if (moves) {
      showBody(p);
      lift(p);
      RIDER(p)->still = FALSE;
      p->target = s->coord.x + dx * 64;
      PlaySound(SE_Z2_SNAKE_HEAVE);
    } else {
      p->target = s->coord.x;
    }
    s->work[2] = 36;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->coord.x != p->target) moveTo(p, dx * 3);
  if (--s->work[2] == 0xFF) {
    if (moves) settle(p);
    setMode(s, next);
  }
}

static void rear2(struct SnakeBlock* p, u8 firstStill, u8 end, s32 dx, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if ((u8)(INDEX(p) - firstStill) <= 2) {
      s->mode[1] = BLOCK_REST;
      return;
    }
    if (INDEX(p) == end) {
      p->target = s->coord.x;
      PlaySound(SE_Z2_SNAKE_HEAVE);
    } else {
      p->target = s->coord.x - dx * 32;
      if (isMiddle(p)) showBody(p);
      lift(p);
    }
    s->work[2] = 26;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->coord.x != p->target) moveTo(p, -dx * 3);
  if (--s->work[2] == 0xFF) {
    if (INDEX(p) != end) settle(p);
    setMode(s, next);
  }
}

static void rear3(struct SnakeBlock* p, u8 still, s32 dx, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (INDEX(p) == still) {
      s->mode[1] = BLOCK_REST;
      return;
    }
    if (isMiddle(p)) {
      showBody(p);
      lift(p);
      p->target = s->coord.x - dx * 64;
    } else {
      p->target = s->coord.x;
      PlaySound(SE_Z2_SNAKE_HEAVE);
    }
    s->work[2] = 36;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  moveTo(p, -dx * 3);
  if (--s->work[2] == 0xFF) {
    if (isMiddle(p)) {
      SetSpriteAnimation(p, SEGMENT(0x13));
      UpdateSpriteAnimation(p);
      p->patch = PATCH_BODY;
    }
    setMode(s, next);
  }
}

// Tail half rises and head half sinks 64 px, or the other way round
static void rear4(struct SnakeBlock* p, s32 dy) {
  struct Entity* s = &p->s;
  s32 v = INDEX(p) <= 3 ? dy : -dy;
  if (s->mode[2] == 0) {
    p->target = s->coord.y + v * 64;
    if (isMiddle(p)) {
      showBody(p);
    } else {
      PlaySound(SE_Z2_SNAKE_HEAVE);
    }
    lift(p);
    s->work[2] = 20;
    s->mode[3] = 0;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) {
      settle(p);
      setMode(s, BLOCK_REST);
    }
    return;
  }
  s->coord.y += v * 3;
  if (--s->work[2] == 0) {
    s->coord.y = p->target;
    s->work[2] = 16;
    s->mode[3]++;
  }
}

static void Block_RearHead(struct SnakeBlock* p) { rear1(p, PIXEL(1), BLOCK_REAR_HEAD2); }
static void Block_RearHead2(struct SnakeBlock* p) { rear2(p, 2, 7, PIXEL(1), BLOCK_REAR_HEAD3); }
static void Block_RearHead3(struct SnakeBlock* p) { rear3(p, 5, PIXEL(1), BLOCK_REAR_HEAD4); }
static void Block_RearHead4(struct SnakeBlock* p) { rear4(p, -PIXEL(1)); }
static void Block_RearTail(struct SnakeBlock* p) { rear1(p, -PIXEL(1), BLOCK_REAR_TAIL2); }
static void Block_RearTail2(struct SnakeBlock* p) { rear2(p, 3, 0, -PIXEL(1), BLOCK_REAR_TAIL3); }
static void Block_RearTail3(struct SnakeBlock* p) { rear3(p, 2, -PIXEL(1), BLOCK_REAR_TAIL4); }
static void Block_RearTail4(struct SnakeBlock* p) { rear4(p, PIXEL(1)); }

/*
  0x080c0df8..0x080c1540 sweep the body back: ends home, two blocks apart, all up to 64 px over
  home, all down to it
*/
static void sweepEnds(struct SnakeBlock* p, u8 next) {
  struct Entity* s = &p->s;
  bool8 end = !isMiddle(p);
  if (s->mode[2] == 0) {
    if (end) {
      p->target = (p->home).x;
      RIDER(p)->still = FALSE;
      lift(p);
      PlaySound(SE_Z2_SNAKE_HEAVE);
    } else {
      p->target = s->coord.x;
    }
    s->work[2] = 46;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->coord.x != p->target) {
    if (INDEX(p) == 0) {
      moveTo(p, -PIXEL(3));
    } else if (INDEX(p) == 7) {
      moveTo(p, PIXEL(3));
    }
  }
  if (--s->work[2] == 0xFF) {
    if (end) p->patch = PATCH_END;
    setMode(s, next);
  }
}

static void sweepApart(struct SnakeBlock* p, u8 left, u8 right, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (INDEX(p) == left) {
      showBody(p);
      lift(p);
      p->target = s->coord.x - PIXEL(32);
      PlaySound(SE_Z2_SNAKE_HEAVE);
    } else if (INDEX(p) == right) {
      showBody(p);
      lift(p);
      p->target = s->coord.x + PIXEL(32);
    } else {
      p->target = s->coord.x;
    }
    s->work[2] = 26;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->coord.x != p->target) {
    if (INDEX(p) == left) {
      moveTo(p, -PIXEL(3));
    } else if (INDEX(p) == right) {
      moveTo(p, PIXEL(3));
    }
  }
  if (--s->work[2] == 0xFF) {
    if (INDEX(p) == left || INDEX(p) == right) {
      SetSpriteAnimation(p, SEGMENT(0x13));
      UpdateSpriteAnimation(p);
      p->patch = PATCH_BODY;
    }
    setMode(s, next);
  }
}

// Sinks toward height over home, snapping up to it from below
static void sweepTo(struct SnakeBlock* p, s32 height, u8 delay, u8 next) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (isMiddle(p)) {
      showBody(p);
    } else {
      PlaySound(SE_Z2_SNAKE_HEAVE);
    }
    lift(p);
    p->target = (p->home).y - height;
    s->work[2] = delay;
    s->mode[2]++;
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (s->coord.y != p->target) {
    s->coord.y += PIXEL(3);
    if (s->coord.y > p->target) s->coord.y = p->target;
  }
  if (--s->work[2] == 0xFF) {
    settle(p);
    setMode(s, next);
  }
}

static void Block_SweepHead(struct SnakeBlock* p) { sweepEnds(p, BLOCK_SWEEP_HEAD2); }
static void Block_SweepHead2(struct SnakeBlock* p) { sweepApart(p, 3, 6, BLOCK_SWEEP_UP); }
static void Block_SweepUp(struct SnakeBlock* p) { sweepTo(p, PIXEL(64), 48, BLOCK_SWEEP_DOWN); }
static void Block_SweepTail(struct SnakeBlock* p) { sweepEnds(p, BLOCK_SWEEP_TAIL2); }
static void Block_SweepTail2(struct SnakeBlock* p) { sweepApart(p, 1, 4, BLOCK_SWEEP_UP2); }
static void Block_SweepDown(struct SnakeBlock* p) { sweepTo(p, 0, 37, BLOCK_HOME); }

// 0x080c1540
static void Block_Home(struct SnakeBlock* p) {
  (p->s).coord = p->home;
  (p->s).mode[1] = BLOCK_REST;
  (p->s).mode[2] = 1;
  Block_Rest(p);
}

// 0x080c1564: opens, sparks along the floor, closes
static void Block_Spark(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  bool8 right = s->mode[1] == BLOCK_SPARK_RIGHT;
  switch (s->mode[2]) {
    case 0:
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, SEGMENT(5));
      if (right) {
        SET_XFLIP(s, TRUE);
        s->coord.x -= PIXEL(1);
      }
      RIDER(p)->still = FALSE;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) {
        createSpark(p, facingRight(s));
        PlaySound(SE_Z2_LEVIATHAN_SHOT);
        s->mode[2]++;
      }
      break;
    case 2:
      SetSpriteAnimation(p, SEGMENT(7));
      s->work[2] = 32;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) s->mode[2]++;
      break;
    case 4:
      SetSpriteAnimation(p, SEGMENT(8));
      s->mode[2]++;
      FALLTHROUGH;
    case 5:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[2]++;
      break;
    case 6:
      s->flags &= ~DISPLAY;
      if (right) {
        SET_XFLIP(s, FALSE);
        s->coord.x += PIXEL(1);
      }
      setMode(s, BLOCK_REST);
      break;
  }
}

// 0x080c16b8
static void Block_Open(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= DISPLAY;
    SetSpriteAnimation(p, SEGMENT(4));
    RIDER(p)->still = FALSE;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if ((s->motion).state == ANIM_NEXT_GOTO) {
    s->flags &= ~DISPLAY;
    setMode(s, BLOCK_REST);
  }
}

static const struct Collision sFireCollisions[2];

// 0x080c1708: flares, hurting, as the bolt passes
static void Block_Fire(struct SnakeBlock* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->flags |= DISPLAY;
    SetSpriteAnimation(p, SEGMENT(3));
    SetDDP(&p->body, sFireCollisions);
    s->work[2] = 32;
    RIDER(p)->still = FALSE;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) {
    SetDDP(&p->body, sBlockCollisions);
    s->flags &= ~DISPLAY;
    setMode(s, BLOCK_REST);
  }
}

static const SolidFunc sBlockModes[29] = {
    (SolidFunc)Block_Rest,       (SolidFunc)Block_HeaveUp,    (SolidFunc)Block_HeaveUpEnd, (SolidFunc)Block_HeaveDown,
    (SolidFunc)Block_HeaveDownEnd, (SolidFunc)Block_StairUp,  (SolidFunc)Block_StairDown,  (SolidFunc)Block_Gather4,
    (SolidFunc)Block_Gather3,    (SolidFunc)Block_RearHead,   (SolidFunc)Block_RearHead2,  (SolidFunc)Block_RearHead3,
    (SolidFunc)Block_RearHead4,  (SolidFunc)Block_RearTail,   (SolidFunc)Block_RearTail2,  (SolidFunc)Block_RearTail3,
    (SolidFunc)Block_RearTail4,  (SolidFunc)Block_SweepHead,  (SolidFunc)Block_SweepHead2, (SolidFunc)Block_SweepUp,
    (SolidFunc)Block_SweepTail,  (SolidFunc)Block_SweepTail2, (SolidFunc)Block_SweepUp,    (SolidFunc)Block_SweepDown,
    (SolidFunc)Block_Home,       (SolidFunc)Block_Spark,      (SolidFunc)Block_Spark,      (SolidFunc)Block_Open,
    (SolidFunc)Block_Fire,
};

// --------------------------------------------

static void Arm_Init(struct SnakeArm* p);
static void Arm_Update(struct SnakeArm* p);
static void Spring_Init(struct SnakeSpring* p);
static void Spring_Update(struct SnakeSpring* p);
static void Spring_Die(struct SnakeSpring* p);
static void Shot_Init(struct SnakeShot* p);
static void Shot_Update(struct SnakeShot* p);

static const struct Collision sArmCollision;
static const struct Collision sSpringCollisions[44];
static const struct Collision sShotCollisions[6];
static const u8 sSpringHitboxes[20];

// clang-format off
const EnemyRoutine gApZ2SnakeArmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Arm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Arm_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEnemy,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

const EnemyRoutine gApZ2SnakeSpringRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Spring_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Spring_Update,
    [ENTITY_DIE] =       (EnemyFunc)Spring_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

const ProjectileRoutine gApZ2SnakeShotRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Shot_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Shot_Update,
    [ENTITY_DIE] =       (ProjectileFunc)DeleteProjectile,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0807414c
static struct Entity* createPart(struct Snake* p, u8 kind, u8 block) {
  struct Entity* e = AllocEntityLast(gEnemyHeaderPtr);
  if (e != NULL) {
    INIT_ENEMY_ROUTINE(e, ENEMY_Z2_SNAKE_ARM);
    e->flags2 |= WHITE_PAINTABLE;
    e->invincibleID = e->uniqueID;
    e->unk_28 = &p->s;
    e->work[0] = kind;
    e->work[1] = block;
  }
  return e;
}

// 0x08074510
static struct Entity* createCaller(struct Snake* p) {
  struct Entity* e = AllocEntityLast(gEnemyHeaderPtr);
  if (e != NULL) {
    INIT_ENEMY_ROUTINE(e, ENEMY_Z2_SNAKE_SPRING);
    e->flags2 |= WHITE_PAINTABLE;
    e->invincibleID = e->uniqueID;
    e->unk_28 = &p->s;
    e->work[0] = 0;
    e->work[1] = 0;
  }
  return e;
}

// 0x0809d4c4
static void createShot(struct Snake* p, u8 half, u8 pattern, u8 n) {
  struct SnakeShot* e = (struct SnakeShot*)AllocEntityLast(gProjectileHeaderPtr);
  if (e != NULL) {
    INIT_PROJECTILE_ROUTINE(&e->s, PROJECTILE_Z2_SNAKE_SHOT);
    (e->s).unk_28 = &p->s;
    (e->s).work[0] = 1;
    (e->s).work[1] = pattern;
    e->half = half;
    e->n = n;
  }
}

// 0x0809d474
static void createSpark(struct SnakeBlock* p, u8 xflip) {
  struct Entity* e = AllocEntityLast(gProjectileHeaderPtr);
  if (e != NULL) {
    INIT_PROJECTILE_ROUTINE(e, PROJECTILE_Z2_SNAKE_SHOT);
    e->unk_28 = &p->s;
    e->work[0] = 0;
    e->work[1] = xflip;
  }
}

// 0x080741a8
static void Arm_Init(struct SnakeArm* p) {
  struct Entity* s = &p->s;
  struct Entity* rider = s->unk_28;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  switch (s->work[0]) {
    case 0:
      SetSpriteAnimation(p, SNAKE(0xC));
      (s->spr).oam.priority = 1;
      SET_XFLIP(s, FALSE);
      s->work[2] = 0;
      s->flags2 |= WHITE_PAINTABLE;
      s->invincibleID = s->uniqueID;
      break;
    case 1:
      SetSpriteAnimation(p, SNAKE(0xF));
      (s->spr).oam.priority = 3;
      SET_XFLIP(s, FALSE);
      s->work[2] = 0;
      s->flags2 |= WHITE_PAINTABLE;
      s->invincibleID = rider->unk_28->uniqueID;
      break;
    case 2:
      SetSpriteAnimation(p, SNAKE(0x14));
      SET_XFLIP(s, facingRight(rider));
      s->coord = rider->coord;
      if (facingRight(rider)) {
        s->d.x = -64;
        s->unk_coord.x = 1;
      } else {
        s->d.x = 64;
        s->unk_coord.x = -1;
      }
      s->flags2 |= WHITE_PAINTABLE;
      s->invincibleID = rider->uniqueID;
      break;
  }
  UpdateSpriteAnimation(p);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Arm_Update(p);
}

// 0x08074330: holds Zero over its block while he is grabbed
static void armFromBlock(struct SnakeArm* p) {
  struct Entity* s = &p->s;
  struct Entity* zero;
  s->coord = (((struct Snake*)s->unk_28)->blocks[s->work[1]]->s).coord;
  switch (s->mode[2]) {
    case 0:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) {
        INIT_BODY(p, &sArmCollision, 1, NULL);
        s->mode[2]++;
      }
      break;
    case 1:
      UpdateSpriteAnimation(p);
      if (!((p->body).status & BODY_STATUS_BINDING)) {
        EXIT_BODY(p);
        s->mode[2]++;
        break;
      }
      zero = (p->body).bindPair->parent;
      if (zero->kind == ENTITY_PLAYER && !((((Object*)zero)->body).status & BODY_STATUS_DEAD) &&
          (((Object*)zero)->body).hp != 0) {
        zero->coord.x = s->coord.x;
        zero->coord.y = s->coord.y - PIXEL(6);
      }
      break;
    case 2:
      SetSpriteAnimation(p, SNAKE(0xE));
      UpdateSpriteAnimation(p);
      s->mode[2]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x08074454: follows the rider by its phase, not its own
static void armUnderRider(struct SnakeArm* p) {
  struct Entity* s = &p->s;
  struct Entity* rider = s->unk_28;
  s->coord = rider->coord;
  switch (rider->mode[2]) {
    case 0:
    case 1:
      UpdateSpriteAnimation(p);
      FALLTHROUGH;
    case 2:
      SetSpriteAnimation(p, SNAKE(0x11));
      UpdateSpriteAnimation(p);
      s->mode[2]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x080744c4: slides to a stop, gone with the rider
static void topHalf(struct SnakeArm* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    s->coord.x += s->d.x;
    s->d.x += s->unk_coord.x;
    if (s->d.x == 0) s->mode[1] = 1;
  } else if (s->unk_28->mode[0] == ENTITY_DISAPPEAR) {
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// 0x080742f8
static void Arm_Update(struct SnakeArm* p) {
  switch ((p->s).work[0]) {
    case 0: armFromBlock(p); break;
    case 1: armUnderRider(p); break;
    case 2: topHalf(p); break;
  }
}

static const struct Collision* springHitbox(struct SnakeSpring* p) { return &sSpringCollisions[sSpringHitboxes[(p->s).motion.cmdIdx]]; }

// 0x08074564
static void Spring_Init(struct SnakeSpring* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SET_XFLIP(s, FALSE);
  INIT_BODY(p, NULL, 6, NULL);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Spring_Update(p);
}

static s32 hopDx(struct Entity* s) { return facingRight(s) ? PIXEL(32) : -PIXEL(32); }

// 0x080745dc: springs out of rider, hops while there is floor ahead, bursts off the end
static void Spring_Update(struct SnakeSpring* p) {
  struct Entity* s = &p->s;
  struct Entity* rider = s->unk_28;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Spring_Die(p);
    return;
  }
  switch (s->mode[1]) {
    case 0:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SNAKE_SPRING, 2));
        SET_XFLIP(s, facingRight(rider));
        s->coord = rider->coord;
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) setMode(s, 1);
      break;
    case 1:
    case 2:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SNAKE_SPRING, s->mode[1] == 1 ? 4 : 5));
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) setMode(s, s->mode[1] + 1);
      break;
    case 3:
      if (s->mode[2] == 0) {
        SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SNAKE_SPRING, 6));
        SetDDP(&p->body, &sSpringCollisions[6]);
        s->coord.x += hopDx(s);
        snapToFloor(s);
        PlaySound(SE_Z2_CRAB_LAND);
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) {
        setMode(s, 4);
        s->mode[3] = 0;
      }
      break;
    case 4:
      if (s->mode[2] == 0) {
        if (s->mode[3] != 0) s->coord.x += hopDx(s);
        snapToFloor(s);
        if (FUN_080098a4(s->coord.x + hopDx(s), s->coord.y + PIXEL(48))) {
          SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SNAKE_SPRING, 0));
          s->mode[3] = 0;
        } else {
          SetSpriteAnimation(p, MOTION(AP_SHEET_Z2_SNAKE_SPRING, 7));
          s->mode[3] = 1;
        }
        PlaySound(SE_Z2_CRAB_LAND);
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      SetDDP(&p->body, springHitbox(p));
      if (s->mode[3] != 0) {
        if ((s->motion).state == ANIM_END) SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      } else if ((s->motion).state == ANIM_NEXT_GOTO) {
        s->mode[3] = 1;
        s->mode[2] = 0;
      }
      break;
  }
}

// 0x08074624: smoke over each of the frame's hitboxes
static void Spring_Die(struct SnakeSpring* p) {
  struct Entity* s = &p->s;
  const struct Collision* c;
  Coords32 at;
  u8 i, n;
  UpdateSpriteAnimation(p);
  if ((s->motion).cmdIdx > 19) {
    CreateSmoke(2, &s->coord);
  } else {
    c = springHitbox(p);
    n = c->remaining + 1;
    for (i = 0; i < n; i++, c++) {
      at.x = facingRight(s) ? s->coord.x - (c->range).x : s->coord.x + (c->range).x;
      at.y = s->coord.y + (c->range).y;
      CreateSmoke((RANDOM(RNG_0202f388) & 1) ? 2 : 1, &at);
    }
  }
  PlaySound(SE_Z2_ICICLE_BREAK);
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

static const Coords32* blockCoord(struct Snake* rider, u8 i) { return &(rider->blocks[i]->s).coord; }

// Bolt starts over hop's block, aimed to arrive at next one in 16 frames
static void aimBolt(struct SnakeShot* p) {
  struct Entity* s = &p->s;
  struct Snake* rider = (struct Snake*)s->unk_28;
  const u8* order = sOpenOrder[p->half][s->work[1]];
  const Coords32* from = blockCoord(rider, order[s->work[2]]);
  const Coords32* to = blockCoord(rider, order[s->work[2] + 1]);
  s->coord.x = from->x;
  s->coord.y = from->y + PIXEL(20);
  s->d.x = (to->x - from->x) / 16;
  s->d.y = (to->y - from->y) / 16;
}

// 0x0809d56c, 0x0809d610
static void Shot_Init(struct SnakeShot* p) {
  struct Entity* s = &p->s;
  static const u8 sTrails[3] = {0xE, 0x11, 0x12};
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  if (s->work[0] == 0) {
    SetSpriteAnimation(p, SEGMENT(9));
    UpdateSpriteAnimation(p);
    INIT_BODY(p, &sShotCollisions[0], 0, NULL);
    SET_XFLIP(s, s->work[1]);
    s->d.x = 0;
  } else {
    SetSpriteAnimation(p, SEGMENT(sTrails[p->n]));
    if (p->n != 0) s->mode[1] = 1;
    UpdateSpriteAnimation(p);
    INIT_BODY(p, &sShotCollisions[4], 0, NULL);
    SET_XFLIP(s, p->half);
    s->work[2] = 0;
    s->work[3] = 15;
    aimBolt(p);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Shot_Update(p);
}

// 0x0809d754: winds up beside its block, then runs along the floor
static void spark(struct SnakeShot* p) {
  struct Entity* s = &p->s;
  struct Entity* block = s->unk_28;
  if (s->d.x == 0) {
    s->coord.x = block->coord.x + (facingRight(s) ? 0x1600 : -0x1700);
    s->coord.y = block->coord.y + 0x1200;
  }
  switch (s->mode[1]) {
    case 1:
      SetSpriteAnimation(p, SEGMENT(0xA));
      s->work[2] = 16;
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;
    case 3:
      SetSpriteAnimation(p, SEGMENT(0xC));
      s->mode[1]++;
      FALLTHROUGH;
    case 0:
    case 4:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) s->mode[1]++;
      break;
    case 5:
      SetSpriteAnimation(p, SEGMENT(0xD));
      s->d.x = facingRight(s) ? PIXEL(4) : -PIXEL(4);
      s->work[2] = 0xFF;
      SetDDP(&p->body, &sShotCollisions[2]);
      s->mode[1]++;
      FALLTHROUGH;
    case 6:
      UpdateSpriteAnimation(p);
      s->coord.x += s->d.x;
      if (--s->work[2] == 0xFF) SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x0809d884: each block it reaches flares. Trailing two show only in flight
static void bolt(struct SnakeShot* p) {
  struct Entity* s = &p->s;
  struct Snake* rider = (struct Snake*)s->unk_28;
  const u8* order = sOpenOrder[p->half][s->work[1]];
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if ((s->motion).state == ANIM_END) {
        SetSpriteAnimation(p, SEGMENT(0xF));
        UpdateSpriteAnimation(p);
        s->mode[1]++;
      }
      FALLTHROUGH;
    case 1:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (--s->work[3] != 0xFF) break;
      if (p->n == 0) {
        SetSpriteAnimation(p, SEGMENT(0x10));
      } else {
        s->flags &= ~DISPLAY;
        s->mode[1]++;
      }
      s->work[3] = 15;
      setMode(&(rider->blocks[order[s->work[2] + 1]]->s), BLOCK_FIRE);
      if (s->work[2] <= 3) {
        s->mode[1]++;
      } else {
        s->mode[1] = 4;
      }
      break;
    case 2:
      if ((s->motion).state == ANIM_END) {
        s->flags &= ~DISPLAY;
        s->mode[1]++;
      }
      FALLTHROUGH;
    case 3:
      if (--s->work[3] != 0xFF) break;
      s->flags |= DISPLAY;
      s->work[2]++;
      s->work[3] = 15;
      aimBolt(p);
      if (p->n == 0) {
        SetSpriteAnimation(p, SEGMENT(0xE));
        UpdateSpriteAnimation(p);
        PlaySound(SE_Z2_SIGNALOID_THUNDER);
        s->mode[1] = 0;
      } else {
        s->mode[1] = 1;
      }
      break;
    case 4:
      EXIT_BODY(p);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

static void Shot_Update(struct SnakeShot* p) {
  if ((p->s).work[0] == 0) {
    spark(p);
  } else {
    bolt(p);
  }
}

// --------------------------------------------

/*
  Zero 2's solid 5 work0 28 and 29: the snake lying across the corridor's end before the fight,
  rider and nine pieces of body. Script entity 3. On its flag the rider leaps off and the
  pieces drop away in turn, Zero with them, to the fight below.
*/
static void Rider_Init(struct Solid* p);
static void Rider_Update(struct Solid* p);
static void Piece_Init(struct Solid* p);
static void Piece_Update(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2SnakeRiderRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Rider_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Rider_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};

const SolidRoutine gApZ2SnakePieceRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Piece_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Piece_Update,
    [ENTITY_DIE] =       (SolidFunc)DeleteSolid,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static const struct Rect sPieceSize = {-0x7800, 0x1000, 0xF000, 0x2000};
static const u8 sDropDelays[9] = {0, 48, 24, 16, 64, 40, 32, 72, 8};

// 0x080c53b4
static void Rider_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Entity* e;
  u8 i;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  ApLoadSheet(&sBodySheet);
  for (i = 0; i < 9; i++) {
    e = AllocEntityLast(gSolidHeaderPtr);
    if (e == NULL) continue;
    INIT_SOLID_ROUTINE(e, SOLID_Z2_SNAKE_PIECE);
    e->flags2 |= WHITE_PAINTABLE;
    e->invincibleID = e->uniqueID;
    e->work[0] = 29;
    e->work[1] = i;
    e->coord.x = FUN_0800a31c(s->coord.x, s->coord.y);
    e->coord.y = s->coord.y - 1;
    e->unk_28 = s;
  }
  s->coord.y--;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Rider_Update(p);
}

// 0x080c54a0: crouches on its flag and leaps off the screen
static void Rider_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, SNAKE(1));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (s->scriptEntity->flags & 1) {
        SetSpriteAnimation(p, SNAKE(6));
        s->mode[1]++;
      }
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->motion).state == ANIM_END) {
        s->d.y = -PIXEL(4);
        SetSpriteAnimation(p, SNAKE(7));
        s->mode[1]++;
      }
      break;
    case 3:
      UpdateSpriteAnimation(p);
      s->coord.y += s->d.y;
      s->d.y += GRAVITY;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x1FFF) {
        s->flags &= ~DISPLAY;
        s->mode[1]++;
      }
      break;
  }
}

// 0x080c5568
static void Piece_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->unk_coord.x = s->coord.x + PIXEL(16);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Piece_Update(p);
}

// 0x080c55ac: a floor that keeps up with the camera, solid left of its centre
static void Piece_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Camera* cam = &gStageRun.vm.camera;
  switch (s->mode[1]) {
    case 0:
      SetSpriteAnimation(p, SEGMENT(2));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (s->unk_28->scriptEntity->flags & 1) {
        s->work[2] = 0;
        s->mode[1]++;
      }
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if (++s->work[2] >= sDropDelays[s->work[1]]) {
        s->d.y = 0;
        PlaySound(SE_Z2_SNAKE_HEAVE);
        s->mode[1]++;
      }
      break;
    case 3:
      UpdateSpriteAnimation(p);
      s->coord.y += s->d.y;
      s->d.y += GRAVITY;
      if (s->d.y > MAX_FALL) s->d.y = MAX_FALL;
      if (Camera_GetDistance(cam, &s->coord) > 0x2FFF) {
        s->flags2 &= ~ENTI_PHYSICS;
        s->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(p);
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      break;
  }
  s->coord.x = s->unk_coord.x + s->work[1] * PIXEL(32);
  while (s->coord.x < (cam->viewport).x - 0x8800) s->coord.x += PIXEL(288);
  if (s->coord.x < (cam->viewport).x) {
    s->flags2 |= ENTI_PHYSICS;
    s->size = &sPieceSize;
    s->physicsAttr = SHAPE_BLOCK;
  } else {
    s->flags2 &= ~ENTI_PHYSICS;
  }
}

// --------------------------------------------

// clang-format off
static const struct Collision sCollisions[23] = {
    /* 0x833a2b0 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a2c8 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a2e0 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a2f8 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1a00, -0x2c00, 0x6400, 0x800}},
    /* 0x833a310 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a328 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a340 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1a00, -0x2200, 0x6400, 0x800}},
    /* 0x833a358 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x4600, -0x2800, 0x1600, 0x800}},
    /* 0x833a370 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1400, 0x1000, 0x2800}},
    /* 0x833a388 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, -0x1900, 0x1400, 0x3200}},
    /* 0x833a3a0 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1e00, -0x1e00, 0x6c00, 0x800}},
    /* 0x833a3b8 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1900, 0x1400, 0x3200}},
    /* 0x833a3d0 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, -0x1600, 0x1400, 0x2c00}},
    /* 0x833a3e8 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1600, -0x1e00, 0x4e00, 0x800}},
    /* 0x833a400 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1600, 0x1400, 0x2c00}},
    /* 0x833a418 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x600, -0xe00, 0x1200, 0x2200}},
    /* 0x833a430 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x600, -0xe00, 0x1200, 0x2200}},
    /* 0x833a448 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0xa00, -0xc00, 0x1800, 0x1000}},
    /* 0x833a460 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 2, 0x00000000, {-0xa00, -0xc00, 0x1800, 0x1000}},
    /* 0x833a478 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x1a00, -0x400, 0x3400, 0xa00}},
    /* 0x833a490 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {0x1a00, -0x400, 0x3400, 0xa00}},
    /* 0x833a4a8 */ {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x600, -0x1000, 0x1800, 0x1000}},
    /* 0x833a4c0 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 2, 0x00000000, {-0x600, -0x1000, 0x1800, 0x1000}},
};

static const struct Collision sBlockCollisions[2] = {
    /* 0x83487e0 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    /* 0x83487f8 */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sFireCollisions[2] = {
    /* 0x8348810 */ {DDP, FACTION_ENEMY, 0, 1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x1000, 0x2800, 0x2800}},
    /* 0x8348828 */ {DRP, FACTION_ENEMY, 0, 1, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};

static const struct Collision sArmCollision = {DDP, FACTION_ENEMY, 2, 1, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x81, 0, 0x00000001, {-0x100, -0xb00, 0x1400, 0x2c00}};

static const struct Collision sSpringCollisions[44] = {
    /* 0x833f494 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0xd00, 0x800, 0x2000}},
    /* 0x833f4ac */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, -0xd00, 0x800, 0x2000}},
    /* 0x833f4c4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0xa00, 0x800, 0x1a00}},
    /* 0x833f4dc */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, -0xa00, 0x800, 0x1a00}},
    /* 0x833f4f4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f50c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f524 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0x300, 0x800, 0xf00}},
    /* 0x833f53c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, -0x300, 0x800, 0xf00}},
    /* 0x833f554 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f56c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 4, 0x00000000, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f584 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x600, -0x1400, 0x800, 0x800}},
    /* 0x833f59c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 2, 0x00000000, {-0x600, -0x1400, 0x800, 0x800}},
    /* 0x833f5b4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0xc00, -0x1a00, 0x800, 0x800}},
    /* 0x833f5cc */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {-0xc00, -0x1a00, 0x800, 0x800}},
    /* 0x833f5e4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f5fc */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 4, 0x00000000, {0x0, -0x600, 0x800, 0x1500}},
    /* 0x833f614 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x800, -0x1200, 0x800, 0x800}},
    /* 0x833f62c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 2, 0x00000000, {-0x800, -0x1200, 0x800, 0x800}},
    /* 0x833f644 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1300, -0x1700, 0x1000, 0x800}},
    /* 0x833f65c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {-0x1300, -0x1700, 0x1000, 0x800}},
    /* 0x833f674 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 7, 0x00000001, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f68c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 6, 0x00000000, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f6a4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f6bc */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 4, 0x00000000, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f6d4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x1100, -0xf00, 0x1000, 0x800}},
    /* 0x833f6ec */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 2, 0x00000000, {-0x1100, -0xf00, 0x1000, 0x800}},
    /* 0x833f704 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x1e00, -0x600, 0xa00, 0xc00}},
    /* 0x833f71c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {-0x1e00, -0x600, 0xa00, 0xc00}},
    /* 0x833f734 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 7, 0x00000001, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f74c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 6, 0x00000000, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f764 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f77c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 4, 0x00000000, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f794 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x1300, -0xd00, 0x1200, 0x800}},
    /* 0x833f7ac */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 2, 0x00000000, {-0x1300, -0xd00, 0x1200, 0x800}},
    /* 0x833f7c4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x2000, 0x400, 0x800, 0x1e00}},
    /* 0x833f7dc */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {-0x2000, 0x400, 0x800, 0x1e00}},
    /* 0x833f7f4 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 7, 0x00000001, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f80c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 6, 0x00000000, {0x0, -0x200, 0x800, 0x800}},
    /* 0x833f824 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 0x00000001, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f83c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 4, 0x00000000, {-0x600, -0xa00, 0x800, 0x800}},
    /* 0x833f854 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {-0x1300, -0xd00, 0x1200, 0x800}},
    /* 0x833f86c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 2, 0x00000000, {-0x1300, -0xd00, 0x1200, 0x800}},
    /* 0x833f884 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x2000, 0xd00, 0x800, 0x2e00}},
    /* 0x833f89c */ {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {-0x2000, 0xd00, 0x800, 0x2e00}},
};

static const struct Collision sShotCollisions[6] = {
    /* 0x8343aa0 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    /* 0x8343ab8 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    /* 0x8343ad0 */ {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xd00, 0x0, 0x1c00, 0x800}},
    /* 0x8343ae8 */ {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
    /* 0x8343b00 */ {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    /* 0x8343b18 */ {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
// clang-format on

// Hitbox by frame, alive or bursting
static const u8 sSpringHitboxes[20] = {0, 2, 4, 6, 4, 2, 0, 8, 13, 20, 28, 36, 36, 36, 36, 36, 38, 40, 42, 42};

#endif
