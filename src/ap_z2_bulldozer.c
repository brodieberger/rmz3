#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/metatile.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's bulldozer, enemy 17.
  work0:
    0: pushes stack of two blocks
    1: no blocks
*/

struct Dozer {
  OBJECT_HDR;
  bool8 airborne;                // 0xB4
  u8 lastDrive;                  // 0xB5, DOZER_PUSH or DOZER_BACK
  u8 tread;                      // 0xB6
  s8 dir;                        // 0xB7
  struct Entity* elementEffect;  // 0xB8
  u8 _bc;
  bool8 blocked;                 // 0xBD
  u8 stack;                      // 0xBE, blocks left
  u8 prevMode;                   // 0xBF
  bool8 backToZero;              // 0xC0
  u8 _c1[3];
};
static_assert(sizeof(struct Dozer) == sizeof(struct Enemy));

enum {
  DOZER_FALL,
  DOZER_IDLE,
  DOZER_PAUSE,
  DOZER_PUSH,
  DOZER_BACK,
  DOZER_ELEMENT,
  DOZER_ROLL,
  DOZER_PULLED,
};

enum {
  DOZER_DIE_BURST,
  DOZER_DIE_CUT,
  DOZER_DIE_CUT_HARD,
};

// Block, Zero 2's enemy 18
struct Block {
  OBJECT_HDR;
  u8 cracks;      // 0xB4
  u8 lastMode;    // 0xB5
  bool8 crushing; // 0xB6, falling onto Zero
  u8 _b7;
  s32 fallY;      // 0xB8
  s32 lastX;      // 0xBC
  s32 lastY;      // 0xC0
};
static_assert(sizeof(struct Block) == sizeof(struct Enemy));

enum {
  BLOCK_REST,
  BLOCK_FALL,
  BLOCK_SHATTER,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_DOZER, (n))
#define BLOCK(n) MOTION(AP_SHEET_Z2_ICE_BLOCK, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)

// Zero's hurtbox, standing
#define ZERO_LEFT ((pZero2->s).coord.x - PIXEL(9))
#define ZERO_RIGHT ((pZero2->s).coord.x + PIXEL(7))
#define ZERO_TOP ((pZero2->s).coord.y - PIXEL(29))
#define ZERO_BOTTOM ((pZero2->s).coord.y + PIXEL(1))

static const struct Collision sCollisions[6];
static const struct SlashedEnemy sPieces[3];
static const struct SlashedEnemy sCutPieces[2];
static const struct SlashedEnemy sHardCutPieces[2];
static const struct SlashedEnemy sTopPieces[3];
static const struct SlashedEnemy sHardTopPieces[3];
static const struct SlashedEnemy sChips[3];
static const struct SlashedEnemy sBits[4];
static const struct SlashedEnemy sHardBits[4];
static const struct Collision sBlock;
static const struct Collision sBlockFalling[2];
static const struct Rect sOneBlock;
static const struct Rect sTwoBlocks;
static const struct Rect sStackBoxes[3];
static const Coords32 sElementCoord = {0, -PIXEL(14)};
static const motion_t sTreadAnims[3] = {ANIM(0), ANIM(7), ANIM(8)};
static const u8 sBoxes[4] = {0, 1, 3, 4};

static u16 Dozer_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Dozer_Init(struct Dozer* p);
static void Dozer_Update(struct Dozer* p);
static void Dozer_Die(struct Dozer* p);
static void Dozer_Disappear(struct Dozer* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static struct Entity* createBlock(struct Entity* below, Coords32* c, u8 n);
static void createTop(struct Dozer* dozer, u8 kind, bool8 flip);

// clang-format off
const EnemyRoutine gApZ2DozerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Dozer_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Dozer_Update,
    [ENTITY_DIE] =       (EnemyFunc)Dozer_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)Dozer_Disappear,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Dozer* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static bool8 solid(s32 x, s32 y) { return FUN_080098a4(x, y) != 0; }

static s32 randomOffset(u8 mask, s32 base) { return ((RANDOM(RNG_0202f388) & mask) - base) * PIXEL(1); }

// 0x080708d0
static bool8 onFloor(struct Entity* s, s32 y) { return solid(s->coord.x - PIXEL(20), y) || solid(s->coord.x + PIXEL(20), y); }

// 0x0807092c
static s32 floorY(struct Entity* s, s32 y) {
  s32 left = FUN_08009f6c(s->coord.x - PIXEL(20), y);
  s32 right = FUN_08009f6c(s->coord.x + PIXEL(20), y);
  return left < right ? left : right;
}

static void treadSmoke(struct Dozer* p, s32 side) {
  Coords32 c;
  c.x = (p->s).coord.x + side * PIXEL(18);
  c.y = (p->s).coord.y - PIXEL(22);
  CreateSmoke(3, &c);
}

// 0x080705dc
// 0x08070cb8
static u16 Dozer_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy UNUSED) {
  struct Dozer* p = (struct Dozer*)s;
  if (s->mode[1] != DOZER_PULLED) setMode(p, DOZER_PULLED);
  s->coord.x += dx;
  if (pulling) {
    if (onFloor(s, s->coord.y + 1)) return 1;
    setMode(p, DOZER_FALL);
    return 0;
  }
  if (onFloor(s, s->coord.y + PIXEL(8))) {
    s->coord.y = floorY(s, s->coord.y);
    setMode(p, DOZER_ROLL);
  } else {
    setMode(p, DOZER_FALL);
  }
  return 0;
}

static void chooseNext(struct Dozer* p) {
  u8 mode = (p->s).mode[1];
  u8 r = RANDOM(RNG_0202f388) & 15;
  u8 afterDrive = p->lastDrive == DOZER_PUSH ? DOZER_BACK : DOZER_PAUSE;
  u8 next;
  if (p->prevMode == 0xFF) {
    next = DOZER_PAUSE;
  } else if (mode == DOZER_IDLE) {
    if (mode != p->prevMode && p->prevMode == DOZER_FALL) {
      next = DOZER_BACK;
    } else if (p->blocked) {
      next = afterDrive;
      p->blocked = FALSE;
    } else {
      next = r > 7 ? DOZER_BACK : DOZER_PAUSE;
    }
  } else if (mode == p->prevMode) {
    next = r > 7 ? afterDrive : DOZER_IDLE;
  } else if (mode == DOZER_PUSH || mode == DOZER_ROLL) {
    next = r > 11 ? DOZER_IDLE : DOZER_PAUSE;
  } else if (mode == DOZER_BACK) {
    next = r > 7 ? DOZER_IDLE : DOZER_PAUSE;
  } else {
    next = DOZER_IDLE;
  }
  p->prevMode = mode;
  setMode(p, next);
}

// 0x0806f428
static void Dozer_Init(struct Dozer* p) {
  struct Entity* s = &p->s;
  bool8 right = s->coord.x < (pZero2->s).coord.x;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  setMode(p, DOZER_IDLE);
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, right);
  SetMotion(s, ANIM(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  p->airborne = FALSE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  s->d.y = 0;
  p->blocked = FALSE;
  p->prevMode = 0xFF;
  p->elementEffect = NULL;
  s->unk_coord.y = right ? -PIXEL(4) : PIXEL(4);
  p->backToZero = FALSE;
  p->stack = 0;
  s->unk_2c = NULL;
  if (s->work[0] == 0) {
    Coords32 c;
    c.x = s->coord.x + (right ? PIXEL(36) : -PIXEL(36));
    c.y = s->coord.y;
    s->unk_2c = createBlock(s, &c, 0);
    if (s->unk_2c != NULL) p->stack = 2;
  }
  INIT_BODY(p, sCollisions, 8, onCollision);
  (p->body).unk_28 = (u32)Dozer_Pull;
  Dozer_Update(p);
}

static void Dozer_Fall(struct Dozer* p);
static void Dozer_Idle(struct Dozer* p);
static void Dozer_Pause(struct Dozer* p);
static void Dozer_Push(struct Dozer* p);
static void Dozer_Back(struct Dozer* p);
static void Dozer_Element(struct Dozer* p);
static void Dozer_Roll(struct Dozer* p);

// 0x08070b94: blade side only hits from the front
static void updateBoxes(struct Dozer* p) {
  struct Entity* s = &p->s;
  bool8 back = (s->coord.x < (pZero2->s).coord.x) != FACING_RIGHT(p);
  if (back != p->backToZero) {
    p->backToZero = back;
    SetDDP(&p->body, &sCollisions[sBoxes[back * 2 + (p->elementEffect != NULL)]]);
  }
}

// 0x0806f594
static void Dozer_Update(struct Dozer* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (status & BODY_STATUS_DEAD) {
    u8 kind = DOZER_DIE_BURST;
    if (status & BODY_STATUS_SLASHED) kind = (status & BODY_STATUS_B15) ? DOZER_DIE_CUT_HARD : DOZER_DIE_CUT;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = kind;
    EXIT_BODY(p);
    if (s->unk_2c != NULL) s->unk_2c->unk_28 = NULL;
    Dozer_Die(p);
    return;
  }

  updateBoxes(p);
  if (IsFrozen(p)) {
    if (p->elementEffect != NULL) {
      p->elementEffect = NULL;
      SetDDP(&p->body, sCollisions);
    }
    return;
  }

  if (p->elementEffect == NULL) {
    if (status & BODY_STATUS_WHITE) {
      p->elementEffect = ApplyElementEffect(0, (Object*)p, &sElementCoord);
      if (p->elementEffect != NULL) setMode(p, DOZER_ELEMENT);
    }
  } else if (IsDead(p->elementEffect)) {
    p->elementEffect = NULL;
  }

  switch (s->mode[1]) {
    case DOZER_FALL: Dozer_Fall(p); break;
    case DOZER_IDLE: Dozer_Idle(p); break;
    case DOZER_PAUSE: Dozer_Pause(p); break;
    case DOZER_PUSH: Dozer_Push(p); break;
    case DOZER_BACK: Dozer_Back(p); break;
    case DOZER_ELEMENT: Dozer_Element(p); break;
    case DOZER_ROLL: Dozer_Roll(p); break;
    case DOZER_PULLED:
      if (s->mode[2] == 0) {
        SetMotion(s, ANIM(0));
        s->mode[2]++;
      }
      UpdateEntityAnim(s);
      break;
  }
}

// 0x0806f714
static void Dozer_Fall(struct Dozer* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->d.y = 0;
    p->airborne = TRUE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (onFloor(s, s->coord.y)) {
    s->coord.y = floorY(s, s->coord.y);
    p->airborne = FALSE;
    chooseNext(p);
  }
}

// 0x0806f784: moves on once Zero is within 128 px
static void Dozer_Idle(struct Dozer* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->work[2] < 32) {
    s->work[2]++;
  } else if ((u32)(s->coord.x - (pZero2->s).coord.x + PIXEL(128)) <= PIXEL(256)) {
    chooseNext(p);
  }
  if (!onFloor(s, s->coord.y + 1)) setMode(p, DOZER_FALL);
}

// 0x0806ff44
static void Dozer_Pause(struct Dozer* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if ((++s->work[2] & 7) == 0) treadSmoke(p, FACING_RIGHT(p) ? -1 : 1);
  if (s->work[2] > 31) {
    setMode(p, DOZER_ROLL);
  } else if (!onFloor(s, s->coord.y + PIXEL(8))) {
    setMode(p, DOZER_FALL);
  }
}

static void stop(struct Dozer* p) {
  p->blocked = TRUE;
  setMode(p, DOZER_IDLE);
}

// Wall or ledge ahead: stops at it
static void stopAtEdges(struct Dozer* p) {
  struct Entity* s = &p->s;
  s32 front = FACING_RIGHT(p) ? PIXEL(20) : -PIXEL(20);
  s32 x = s->coord.x + s->d.x + front;
  s32 y = s->coord.y - PIXEL(8);
  if (solid(x, y)) {
    stop(p);
    if (s->d.x < 0) {
      s->d.x = FUN_0800a31c(x, y) - (s->coord.x - PIXEL(20));
    } else if (s->d.x > 0) {
      s->d.x = FUN_0800a22c(x, y) - (s->coord.x + PIXEL(20));
    }
  }
  x = s->coord.x + s->d.x + front;
  y = s->coord.y + PIXEL(8);
  if (!solid(x, y)) {
    stop(p);
    if (s->d.x < 0) {
      s->d.x = FUN_0800a22c(x, y) - (s->coord.x - PIXEL(20));
    } else if (s->d.x > 0) {
      s->d.x = FUN_0800a31c(x, y) - (s->coord.x + PIXEL(20));
    }
  }
}

// 0x08070984: returns TRUE when wall stopped it
static bool8 pushBox(struct Entity* s, const struct Rect* r, s32 dx) {
  s32 edge, x, y;
  bool8 hit = FALSE;
  s32 i;
  if (dx == 0) return FALSE;
  edge = dx < 0 ? r->x - r->w / 2 : r->x + r->w / 2 - 1;
  x = s->coord.x + edge + dx;
  y = s->coord.y + r->y + r->h / 2 - PIXEL(1);
  for (i = 0; i <= METACOORD((u16)r->h); i++, y -= PIXEL(16)) {
    if (solid(x, y)) {
      x = dx < 0 ? FUN_0800a31c(x, y) : FUN_0800a22c(x, y);
      hit = TRUE;
    }
  }
  if (hit) {
    s->coord.x = x - edge;
  } else {
    s->coord.x += dx;
  }
  return hit;
}

// Blocks in reach, h px of them tall
static bool8 blockAhead(struct Dozer* p, s32 x, s32 h) {
  struct Entity* s = &p->s;
  struct Entity* block = s->unk_2c;
  return (u32)(block->coord.x - x + PIXEL(36)) <= PIXEL(72) &&
         (u32)(block->coord.y - h - s->coord.y + PIXEL(16) + h + 0xF00) <= (u32)(h + 0xF00) * 2;
}

// 0x0806f7f8: slower the more blocks, stopped by Zero in front
static void Dozer_Push(struct Dozer* p) {
  struct Entity* s = &p->s;
  struct Entity* block = s->unk_2c;
  s32 x, h;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    p->dir = FACING_RIGHT(p) ? 1 : -1;
    s->unk_coord.x = s->coord.x;
    p->lastDrive = DOZER_PUSH;
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (!onFloor(s, s->coord.y + 1)) {
    setMode(p, DOZER_FALL);
    return;
  }
  if (block == NULL) {
    setMode(p, DOZER_ROLL);
    return;
  }
  if (block->mode[1] == BLOCK_FALL) {
    setMode(p, DOZER_IDLE);
    return;
  }
  s->d.x = 230 / (p->stack + 1) * p->dir;
  if (s->work[2] % (p->stack * 4 + 4) == 0) {
    if (++p->tread > 2) p->tread = 0;
    SetMotion(s, sTreadAnims[p->tread]);
    if (p->tread == 0) treadSmoke(p, -p->dir);
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  stopAtEdges(p);

  x = s->coord.x + s->d.x;
  h = p->stack * PIXEL(16);
  if (blockAhead(p, x, h)) {
    s32 cx = x + p->dir * PIXEL(36);
    s32 top = block->coord.y - h;
    s32 zx = block->coord.x >= (pZero2->s).coord.x ? ZERO_RIGHT : ZERO_LEFT;
    s32 zy = (pZero2->s).coord.y - PIXEL(14) < top ? ZERO_BOTTOM - PIXEL(1) : ZERO_TOP + PIXEL(1);
    bool8 stopped = FALSE;
    if ((u32)(zx - cx + PIXEL(16)) <= PIXEL(32) && (u32)(zy - top + h) <= (u32)h * 2) {
      block->d.x = zx - (block->coord.x + p->dir * PIXEL(16));
      if ((block->d.x < 0) != (s->d.x < 0)) block->d.x = 0;
      stopped = TRUE;
    } else {
      block->d.x = s->d.x;
    }
    if (pushBox(block, &sStackBoxes[p->stack], block->d.x)) stopped = TRUE;
    if (stopped) {
      s->coord.x = block->coord.x - p->dir * PIXEL(36);
      stop(p);
      return;
    }
  }
  if ((u32)(s->unk_coord.x - x + PIXEL(128)) > PIXEL(256) && solid(block->coord.x, block->coord.y + PIXEL(8))) {
    chooseNext(p);
  } else {
    s->coord.x = x;
  }
}

// 0x0806fb8c
static void Dozer_Back(struct Dozer* p) {
  struct Entity* s = &p->s;
  s32 x;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    p->dir = FACING_RIGHT(p) ? -1 : 1;
    s->unk_coord.x = s->coord.x;
    s->d.x = p->dir * 0x80;
    p->lastDrive = DOZER_BACK;
    s->work[2] = 0;
    s->mode[2]++;
  }
  if (s->work[2] % 6 == 0) {
    if (++p->tread > 2) p->tread = 0;
    SetMotion(s, sTreadAnims[2 - p->tread]);
    if (p->tread == 0) treadSmoke(p, p->dir);
  }
  UpdateEntityAnim(s);
  s->work[2]++;
  if (!onFloor(s, s->coord.y + PIXEL(8))) {
    setMode(p, DOZER_FALL);
    return;
  }
  x = s->coord.x + s->d.x + (FACING_RIGHT(p) ? -PIXEL(20) : PIXEL(20));
  if (solid(x, s->coord.y - PIXEL(8)) || !solid(x, s->coord.y + PIXEL(8))) {
    stop(p);
    return;
  }
  x = s->coord.x + s->d.x;
  if ((u32)(s->unk_coord.x - x + PIXEL(96)) > PIXEL(192)) {
    chooseNext(p);
  } else {
    s->coord.x = x;
  }
}

// 0x080701d0
static void Dozer_Element(struct Dozer* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, &sCollisions[1]);
    p->airborne = TRUE;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (onFloor(s, s->coord.y)) {
    s->coord.y = floorY(s, s->coord.y);
    p->airborne = FALSE;
  }
  if (p->elementEffect == NULL) {
    SetDDP(&p->body, sCollisions);
    chooseNext(p);
  }
}

// 0x0806fd04: rolls up to blocks, or at Zero without any
static void Dozer_Roll(struct Dozer* p) {
  struct Entity* s = &p->s;
  s32 x;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(6));
    p->dir = FACING_RIGHT(p) ? 1 : -1;
    s->unk_coord.x = s->coord.x;
    s->d.x = p->dir * 0x100;
    p->lastDrive = DOZER_PUSH;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (s->motion.cmdIdx == 0) treadSmoke(p, -p->dir);
  if (!onFloor(s, s->coord.y + PIXEL(8))) {
    setMode(p, DOZER_FALL);
    return;
  }
  stopAtEdges(p);
  x = s->coord.x + s->d.x;
  if (p->stack != 0 && blockAhead(p, x, p->stack * PIXEL(16))) {
    s->coord.x = s->unk_2c->coord.x - p->dir * PIXEL(36);
    setMode(p, DOZER_PUSH);
    return;
  }
  if ((u32)(s->unk_coord.x - x + PIXEL(128)) > PIXEL(256)) {
    chooseNext(p);
  } else {
    s->coord.x = x;
  }
}

static void countKill(struct Dozer* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  TryDropItem(3, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void explosion(s32 x, s32 y, u8 mask, s32 xBase, s32 yBase) {
  Coords32 c;
  c.x = x + randomOffset(mask, xBase);
  c.y = y + randomOffset(mask, yBase);
  CreateSmoke(1, &c);
  c.x = x + randomOffset(mask, xBase);
  c.y = y + randomOffset(mask, yBase);
  CreateSmoke(2, &c);
}

// 0x08070270
static void Dozer_Burst(struct Dozer* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  s32 i;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(16);
  for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&c, &sPieces[i], 0, FACING_RIGHT(p) * 0x11));
  PlaySound(SE_ZAKO_EXPLODE);
  explosion(c.x, c.y, 7, 3, 3);
  countKill(p);
}

// 0x080706f8, 0x080707e4: lower half
static void burstLower(struct Dozer* p, const struct SlashedEnemy* pieces) {
  struct Entity* s = &p->s;
  Coords32 c;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(24);
  useApSheets(CreateSlashedEnemy(&c, &pieces[0], 0, FACING_RIGHT(p) * 0x11));
  useApSheets(CreateSlashedEnemy(&c, &pieces[1], 0, FACING_RIGHT(p) * 0x11));
  PlaySound(SE_ZAKO_EXPLODE);
  explosion(s->coord.x, s->coord.y, 31, 15, 39);
}

// 0x080703b0, 0x080704dc: cut in two, top half flies off, lower half shakes or sits, then blows
static void Dozer_Cut(struct Dozer* p, bool8 hard) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(2));
    if (onFloor(s, s->coord.y + PIXEL(8))) s->coord.y = floorY(s, s->coord.y + PIXEL(8));
    createTop(p, hard, FACING_RIGHT(p));
    s->d.x = PIXEL(1);
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (++s->work[2] != 255) {
    if (!onFloor(s, s->coord.y + 1)) {
      p->airborne = TRUE;
      return;
    }
    if (!p->airborne) {
      if (hard) {
        if (s->work[2] < 48) return;
      } else {
        if (s->work[2] < 24) return;
        if ((s->work[2] & 3) == 0) {
          s->coord.x += s->d.x;
          s->d.x = -s->d.x;
        }
        if (s->work[2] < 52) return;
      }
    }
  }
  burstLower(p, hard ? sHardCutPieces : sCutPieces);
  countKill(p);
}

// 0x0806f694
static void Dozer_Die(struct Dozer* p) {
  switch ((p->s).mode[1]) {
    case DOZER_DIE_BURST: Dozer_Burst(p); break;
    case DOZER_DIE_CUT: Dozer_Cut(p, FALSE); break;
    case DOZER_DIE_CUT_HARD: Dozer_Cut(p, TRUE); break;
  }
}

// 0x0806f6fc
static void Dozer_Disappear(struct Dozer* p) {
  if ((p->s).unk_2c != NULL) (p->s).unk_2c->unk_28 = NULL;
  DeleteEnemy((struct Entity*)p);
}

// 0x08070c00: knocked back on blade, unless hit from behind
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = (struct Entity*)body->parent;
  s32 x, y;
  if (!(body->hitboxFlags & BODY_STATUS_B6)) return;
  if ((s->coord.x < (pZero2->s).coord.x) != FACING_RIGHT(s)) return;
  s->coord.x += s->unk_coord.y;
  x = s->coord.x + (FACING_RIGHT(s) ? -PIXEL(20) : PIXEL(20));
  y = s->coord.y - PIXEL(8);
  if (solid(x, y)) {
    if (s->coord.x < (pZero2->s).coord.x) {
      s->coord.x = FUN_0800a31c(x, y) + PIXEL(20);
    } else {
      s->coord.x = FUN_0800a22c(x, y) - PIXEL(20);
    }
  }
}

// --------------------------------------------
// Zero 2's VFX 25, cut top half.
// work0: thrown clear
// work1: thrown right, by hit

static void Top_Init(struct VFX* p);
static void Top_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2DozerTopRoutine = {
    [ENTITY_INIT] =      Top_Init,
    [ENTITY_UPDATE] =    Top_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b37ac
static void createTop(struct Dozer* dozer, u8 kind, bool8 flip) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_DOZER_TOP);
    p->renderPrio = 1;
    p->unk_28 = &dozer->s;
    p->coord = (dozer->s).coord;
    p->work[0] = kind;
    p->work[1] = flip;
  }
}

// 0x080b3804
static void Top_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, FACING_RIGHT(s->unk_28));
  SetMotion(s, ANIM(1));
  s->flags |= DISPLAY | FLIPABLE;
  s->work[2] = 16;
  if (s->work[0] == 0) {
    s->d.x = 0;
    s->d.y = -0x240;
  } else {
    s->d.x = s->work[1] ? -0x280 : 0x280;
    s->d.y = -0x440;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Top_Update(p);
}

// 0x080b38b0
static void Top_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  s->coord.x += s->d.x;
  if (solid(s->coord.x, s->coord.y - PIXEL(12)) || --s->work[2] == 0) {
    Coords32 c;
    const struct SlashedEnemy* pieces = s->work[0] ? sHardTopPieces : sTopPieces;
    u8 flip = (FACING_RIGHT(s) << 4) | s->work[1];
    s32 i;
    c.x = s->coord.x;
    c.y = s->coord.y - (s->work[0] ? PIXEL(12) : PIXEL(24));
    for (i = 0; i < 3; i++) useApSheets(CreateSlashedEnemy(&c, &pieces[i], 0, flip));
    c.x += randomOffset(31, 15);
    c.y += randomOffset(31, 15);
    CreateSmoke(1, &c);
    s->flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
}

// --------------------------------------------
/*
  Zero 2's ice block, enemy 18.
  work0:
    0: bottom
    1: on top, unk_28 block below
*/

static void Block_Init(struct Block* p);
static void Block_Update(struct Block* p);
static void Block_Die(struct Block* p);
static void Block_Hit(struct Body* body, Coords32* r1, Coords32* r2);

// clang-format off
const EnemyRoutine gApZ2IceBlockRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Block_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Block_Update,
    [ENTITY_DIE] =       (EnemyFunc)Block_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080713c4
static void setSolid(struct Entity* s, const struct Rect* size) {
  s->flags2 |= ENTI_PHYSICS;
  s->size = size;
  s->physicsAttr = SHAPE_BLOCK;
}

// 0x08070d3c
static struct Entity* createBlock(struct Entity* below, Coords32* c, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_ICE_BLOCK);
    p->renderPrio = 24;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = below;
    p->coord = *c;
    p->work[0] = n;
  }
  return p;
}

// 0x08070d9c
static void Block_Init(struct Block* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = BLOCK_REST;
  InitNonAffineMotion(s);
  useApSheets(p);
  SetMotion(s, BLOCK(0));
  UpdateEntityAnim(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  s->unk_coord.x = s->unk_coord.y = 0;
  p->cracks = 0;
  p->lastMode = 0xFF;
  p->crushing = FALSE;
  p->lastX = s->coord.x;
  p->lastY = s->coord.y;
  INIT_BODY(p, &sBlock, 24, Block_Hit);
  s->unk_2c = NULL;
  if (s->work[0] == 0) {
    s->unk_2c = createBlock(s, &s->coord, 1);
    if (s->unk_2c == NULL) {
      if (s->unk_28 != NULL) ((struct Dozer*)s->unk_28)->stack--;
      setSolid(s, &sOneBlock);
    }
  } else {
    setSolid(s, &sTwoBlocks);
  }
  Block_Update(p);
}

static void chips(struct Entity* s) {
  Coords32 c;
  bool8 right = (pZero2->s).coord.x > s->coord.x;
  u8 flip = (FACING_RIGHT(s) << 4) | right;
  s32 n = (RANDOM(RNG_0202f388) & 1) + 1;
  s32 i;
  c.x = s->coord.x + (right ? PIXEL(16) : -PIXEL(16));
  c.y = s->coord.y - PIXEL(16);
  for (i = 0; i < n; i++) useApSheets(CreateSlashedEnemy(&c, &sChips[i], 0, flip));
}

static void bits(struct Entity* s, s32 n, const struct SlashedEnemy* table) {
  Coords32 c;
  bool8 right = (pZero2->s).coord.x > s->coord.x;
  u8 flip = (FACING_RIGHT(s) << 4) | (n == 8 ? s->work[3] : right);
  s32 i;
  c.x = s->coord.x;
  c.y = s->coord.y - PIXEL(16);
  for (i = 0; i < n; i++) useApSheets(CreateSlashedEnemy(&c, &table[i & 3], 0, flip));
}

// 0x08071574 and on: chips, cracks at 12 HP left and at 6
static void takeHit(struct Block* p) {
  struct Entity* s = &p->s;
  chips(s);
  if (p->cracks > 1 || (p->body).hp > (p->cracks == 0 ? 12 : 6)) return;
  SetMotion(s, BLOCK(p->cracks + 1));
  bits(s, (RANDOM(RNG_0202f388) & 1) + 2, sBits);
  p->cracks++;
}

// 0x08071448: falling on Zero's head hurts him
static void watchZero(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* above = s->unk_2c;
  s32 zx = s->coord.x >= (pZero2->s).coord.x ? ZERO_RIGHT - PIXEL(1) : ZERO_LEFT + PIXEL(1);
  bool8 over = (u32)(zx - s->coord.x + PIXEL(16)) <= PIXEL(32) && s->coord.y - PIXEL(8) < ZERO_TOP + PIXEL(1);
  if (p->crushing) {
    if (s->mode[1] == BLOCK_FALL && over) {
      if (!((p->body).status & BODY_STATUS_B2)) return;
      bits(s, 8, sBits);
      s->work[2] = 0;
      EXIT_BODY(p);
      s->mode[1] = BLOCK_SHATTER;
    } else {
      SetDDP(&p->body, &sBlock);
      if (above != NULL) {
        setSolid(above, &sTwoBlocks);
      } else {
        setSolid(s, &sOneBlock);
      }
      p->crushing = FALSE;
    }
  } else if (s->mode[1] == BLOCK_FALL && over) {
    SetDDP(&p->body, sBlockFalling);
    (above != NULL ? above : s)->flags2 &= ~ENTI_PHYSICS;
    p->crushing = TRUE;
  }
}

static bool8 floorUnder(struct Entity* s) {
  s32 y = s->coord.y;
  bool8 hit = FALSE;
  s32 i;
  for (i = 0; i <= 2; i++) {
    s32 x = s->coord.x - PIXEL(16) + i * PIXEL(16) - (i != 0);
    if (solid(x, y)) {
      y = FUN_08009f6c(x, y);
      hit = TRUE;
    }
  }
  if (hit) s->coord.y = y;
  return hit;
}

// 0x08071744
static bool8 land(struct Entity* s) {
  s32 l = s->coord.x - PIXEL(16);
  s32 r = s->coord.x + PIXEL(16) - 1;
  s32 y = s->coord.y;
  if (s->unk_coord.y == 0) {
    if (solid(r, y + PIXEL(1)) || solid(l, y + PIXEL(1))) return TRUE;
    if (solid(r, y + PIXEL(8)) || solid(l, y + PIXEL(8))) {
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      return TRUE;
    }
  }
  if (floorUnder(s)) {
    s->unk_coord.y = 0;
    return TRUE;
  }
  s->unk_coord.y += 0x40;
  if (s->unk_coord.y > 0x700) s->unk_coord.y = 0x700;
  return FALSE;
}

// 0x080710e4
static void Block_Bottom(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* above = s->unk_2c;
  if (s->unk_28 != NULL && s->unk_28->mode[0] > ENTITY_UPDATE) s->unk_28 = NULL;
  if (s->unk_28 == NULL && Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(96)) {
    if (above != NULL) DeleteEnemy(above);
    DeleteEnemy(s);
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) takeHit(p);
  switch (s->mode[1]) {
    case BLOCK_REST:
      watchZero(p);
      s->coord.y += s->unk_coord.y;
      if (!land(s)) {
        p->fallY = s->coord.y;
        s->mode[1] = BLOCK_FALL;
      }
      break;
    case BLOCK_FALL:
      watchZero(p);
      if (s->mode[1] != BLOCK_FALL) break;
      s->coord.y += s->unk_coord.y;
      if (land(s)) {
        if (s->coord.y - p->fallY > PIXEL(40)) {
          bits(s, 8, sBits);
          s->work[2] = 0;
          EXIT_BODY(p);
          s->flags2 &= ~ENTI_PHYSICS;
          s->mode[1] = BLOCK_SHATTER;
        } else {
          useApSheets(CreateSlashedEnemy(&s->coord, &sChips[0], 0, 0));
          useApSheets(CreateSlashedEnemy(&s->coord, &sChips[1], 0, 0x11));
          useApSheets(CreateSlashedEnemy(&s->coord, &sChips[2], 0, 0));
          s->mode[1] = BLOCK_REST;
        }
      }
      break;
    case BLOCK_SHATTER:
      land(s);
      if (++s->work[2] & 1) return;
      if (p->cracks < 2) {
        SetMotion(s, BLOCK(p->cracks + 1));
        p->cracks++;
      } else {
        bits(s, 8, sBits);
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        Block_Die(p);
        return;
      }
      break;
  }
  p->lastMode = s->mode[1];
}

// 0x0807132c: bottom gone, becomes it
static void Block_Top(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* below = s->unk_28;
  if (below == NULL) {
    s->work[0] = 0;
    setSolid(s, &sOneBlock);
    return;
  }
  if ((p->body).status & BODY_STATUS_WHITE) takeHit(p);
  s->coord.x = below->coord.x;
  s->coord.y = below->coord.y - PIXEL(32);
}

// 0x08070ed8
static void Block_Update(struct Block* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;
  if (status & BODY_STATUS_DEAD) {
    bits(s, 8, (status & BODY_STATUS_B15) ? sHardBits : sBits);
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    EXIT_BODY(p);
    Block_Die(p);
    return;
  }
  UpdateEntityAnim(s);
  if (s->work[0] == 0) {
    Block_Bottom(p);
  } else {
    Block_Top(p);
  }
  s->d.x = s->coord.x - p->lastX;
  s->d.y = s->coord.y - p->lastY;
  p->lastX = s->coord.x;
  p->lastY = s->coord.y;
}

// 0x08070fc4: top one moves down to dozer
static void Block_Die(struct Block* p) {
  struct Entity* s = &p->s;
  struct Entity* below = s->unk_28;
  struct Entity* above = s->unk_2c;
  if (s->work[0] == 0) {
    if (above != NULL) {
      above->work[0] = 0;
      setSolid(above, &sOneBlock);
      if (p->lastMode == BLOCK_SHATTER) {
        above->mode[1] = BLOCK_FALL;
        ((struct Block*)above)->fallY = p->fallY;
      }
      if (below != NULL) {
        ((struct Dozer*)below)->stack--;
        below->unk_2c = above;
      }
      above->unk_28 = below;
    } else {
      if (below != NULL) {
        ((struct Dozer*)below)->stack--;
        below->unk_2c = NULL;
      }
      s->flags2 &= ~ENTI_PHYSICS;
    }
  } else {
    if (below->unk_28 != NULL) ((struct Dozer*)below->unk_28)->stack--;
    if (below->mode[0] <= ENTITY_UPDATE) {
      below->unk_2c = NULL;
      setSolid(below, &sOneBlock);
    }
    s->flags2 &= ~ENTI_PHYSICS;
  }
  PlaySound(SE_Z2_ICE_BREAK);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x08071890
static void Block_Hit(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* s = (struct Entity*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_WHITE) s->work[3] = s->coord.x < (pZero2->s).coord.x;
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[6] = {
    {DDP,  FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x600, -0xe00, 0x2400, 0x2000}},
    {DRP,  FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 1, 0x00000000, {0x400, -0xe00, 0x1000, 0x2000}},
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0xffffffff, {-0xe00, -0xe00, 0x1400, 0x2000}},
    {DDP,  FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x600, -0xe00, 0x2400, 0x2000}},
    {DRP,  FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, HARDNESS_B3, 0x00, 1, 0x00000000, {0x400, -0xe00, 0x1000, 0x2000}},
    {DRP2, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0xffffffff, {-0xe00, -0xe00, 0x1400, 0x2000}},
};

static const struct Collision sBlock =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, -0xe00, 0x2000, 0x2000}};

static const struct Collision sBlockFalling[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 1, 0x00000001, {0x0, -0xe00, 0x2000, 0x2000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0, 0x00000000, {0x0, -0xe00, 0x2000, 0x2000}},
};

static const struct Rect sOneBlock = {0, -4096, 8192, 8192};
static const struct Rect sTwoBlocks = {0, 0, 8192, 16384};
static const struct Rect sStackBoxes[3] = {{512, 512, 0, 0}, {0, -4096, 8192, 8192}, {0, -8192, 8192, 16384}};

static const struct SlashedEnemy sPieces[3] = {
    {ANIM(3), {0xff, 0x11}, {0, 0}, {256, -1280}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(4), {0xff, 0x11}, {0, 0}, {-256, -1280}, {63, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {32, -1152}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sCutPieces[2] = {
    {ANIM(5), {0xff, 0x11}, {0, 0}, {64, -1280}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {128, -1024}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sHardCutPieces[2] = {
    {ANIM(5), {0xff, 0x11}, {0, 0}, {512, -1664}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {192, -1792}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sTopPieces[3] = {
    {ANIM(3), {0xff, 0x11}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(4), {0xff, 0x11}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sHardTopPieces[3] = {
    {ANIM(3), {0xff, 0x11}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(4), {0xff, 0x11}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {ANIM(5), {0xff, 0x11}, {0, 0}, {192, -768}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sChips[3] = {
    {BLOCK(4), {0x40, 0x30}, {0, 0}, {32, -1280}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(5), {0x40, 0x30}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(6), {0x40, 0x30}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sBits[4] = {
    {BLOCK(3), {0x40, 0x30}, {0, 0}, {-128, -1280}, {255, 511}, {0, 64}, {512, 512}, {0}},
    {BLOCK(4), {0x40, 0x30}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(5), {0x40, 0x30}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(6), {0x40, 0x30}, {0, 0}, {128, -512}, {255, 255}, {0, 64}, {512, 512}, {0}},
};

static const struct SlashedEnemy sHardBits[4] = {
    {BLOCK(3), {0x40, 0x30}, {0, 0}, {48, -1920}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(4), {0x40, 0x30}, {0, 0}, {-576, -1536}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(5), {0x40, 0x30}, {0, 0}, {192, -768}, {255, 255}, {0, 64}, {512, 512}, {0}},
    {BLOCK(6), {0x40, 0x30}, {0, 0}, {192, -768}, {255, 255}, {0, 64}, {512, 512}, {0}},
};
// clang-format on

#endif  // AP
