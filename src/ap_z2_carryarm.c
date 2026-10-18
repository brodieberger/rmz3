#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2 Carryarm and Spiking
*/

struct Carryarm {
  OBJECT_HDR;
  u8 bounces;              // 0xB4, Spiking's wall bounces
  u8 _b5[3];
  u8 cut;                  // 0xB8
  u8 _b9[3];
  s32 zeroSide;            // 0xBC, Zero's x minus its own at the last hit
  struct Entity* element;  // 0xC0, element effect attacking it
};
static_assert(sizeof(struct Carryarm) == sizeof(struct Enemy));

enum {
  CARRYARM_CARRY,
  SPIKING_CARRIED,
  SPIKING_ROLL,
  CARRYARM_RECOIL, 
};

enum {
  DEATH_CARRYARM,
  DEATH_CARRYARM_FALL,
  DEATH_SPIKING,
  DEATH_SPIKING_FALL,
  DEATH_GONE,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_CARRYARM, (n))
#define ANIM_CARRY ANIM(0)
#define ANIM_FLY_OFF ANIM(1)
#define ANIM_HIT ANIM(2)
#define ANIM_UPPER_HALF ANIM(3)
#define ANIM_LOWER_HALF ANIM(4)
#define ANIM_PIECE(n) ANIM(5 + (n))
#define ANIM_ROLL(n) ANIM(8 + (n))
#define ANIM_SPIKING_UPPER_HALF ANIM(11)
#define ANIM_SPIKING_LOWER_HALF ANIM(12)
#define ANIM_SPIKING_PIECE(n) ANIM(13 + (n))

#define IS_SPIKING(s) ((s)->work[0] >= 2)
#define FACES_RIGHT(s) (((s)->work[0] & 1) != 0)

#define SAVED_DY unk_coord.x  
#define LIFT unk_coord.y     

#define BOUNCE_SOUND SE_Z2_SPIKING_BOUNCE

static const struct Collision sCarryarmCollisions[2];
static const struct Collision sCarryarmHarmless[2];
static const struct Collision sSpikingCollisions[2];
static const struct Collision sSpikingHarmless[2];
static const Coords32 sCarryarmElementCoord = {0, 0};
static const Coords32 sSpikingElementCoord = {0, -PIXEL(10)};
static const s32 sSlopeDX[14];
static const s32 sSlopeDY[14];

static void Carryarm_Init(struct Carryarm* p);
static void Carryarm_Update(struct Carryarm* p);
static void Carryarm_Die(struct Carryarm* p);

// clang-format off
const EnemyRoutine gApZ2CarryarmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Carryarm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Carryarm_Update,
    [ENTITY_DIE] =       (EnemyFunc)Carryarm_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

enum {
  DEBRIS_UPPER_HALF,
  DEBRIS_PIECE,
  DEBRIS_SPIKING_UPPER_HALF,
  DEBRIS_SPIKING_PIECE,
};

static void createHalf(struct Entity* parent, u8 kind);
static void createPieces(u8 kind, bool8 facingRight, Coords32* c);

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static void disappear(struct Entity* s) {
  s->flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(s);
  SET_ENEMY_ROUTINE(s, ENTITY_DISAPPEAR);
}

static bool8 isFar(struct Entity* s) { return Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(118); }

static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Carryarm* p = (struct Carryarm*)body->parent;
  p->zeroSide = (pZero2->s).coord.x - (p->s).coord.x;
  p->cut = 0;
  if (body->status & BODY_STATUS_SLASHED) p->cut = 1;
  if (body->status & BODY_STATUS_B15) p->cut |= 2;
}

// 0x0808d8cc
static void Carryarm_Init(struct Carryarm* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->flags |= FLIPABLE;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY;
  p->cut = 0;
  if (FACES_RIGHT(s)) {
    SET_XFLIP(p, TRUE);
    s->coord.x = gStageRun.vm.camera.viewport.x - PIXEL(152);
  }
  if (IS_SPIKING(s)) {
    struct Entity* q = AllocEntityLast(gEnemyHeaderPtr);
    if (q != NULL) {
      INIT_ENEMY_ROUTINE(q, ENEMY_Z2_CARRYARM);
      q->coord.x = s->coord.x;
      q->coord.y = s->coord.y - PIXEL(22);
      q->work[0] = s->work[0] - 2;
      q->unk_28 = s;
    }
    s->unk_2c = q;
    INIT_BODY(p, sSpikingCollisions, 10, onCollision);
    SetMotion(s, ANIM_ROLL(0));
    s->mode[1] = SPIKING_CARRIED;
  } else {
    INIT_BODY(p, sCarryarmCollisions, 8, onCollision);
    SetMotion(s, ANIM_CARRY);
    s->mode[1] = CARRYARM_CARRY;
  }
  p->element = NULL;
  Carryarm_Update(p);
}

static const EnemyFunc sUpdates[3];

static void killed(struct Carryarm* p, bool8 spiking) {
  struct Entity* s = &p->s;
  s->d.y = 0;
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &s->coord);
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  s->mode[1] = spiking ? DEATH_SPIKING : DEATH_CARRYARM;
  Carryarm_Die(p);
}

// 0x0808da9c
static void Carryarm_Update(struct Carryarm* p) {
  struct Entity* s = &p->s;
  bool8 spiking = IS_SPIKING(s);
  s32 feet;

  if (!spiking) {
    struct Entity* q = s->unk_28;  // The Spiking it carries
    if (q != NULL) {
      if (q->mode[0] == ENTITY_EXIT) {
        disappear(s);
        return;
      }
      if (q->mode[0] > ENTITY_UPDATE) {
        GotoMotion(s, ANIM_FLY_OFF, 5, 1);
        UpdateEntityAnim(s);
        s->unk_28 = NULL;
      }
    }
  } else if (s->unk_2c != NULL && s->unk_2c->mode[0] > ENTITY_UPDATE) {
    s->unk_2c = NULL;
  }

  if (!spiking && (s->mode[1] == CARRYARM_RECOIL || ApRecoilHit((Object*)p))) {
    if (s->mode[1] != CARRYARM_RECOIL) s->mode[1] = CARRYARM_RECOIL, s->mode[2] = 0;
    UpdateEntityAnim(s);
    if (ApRecoilFly((Object*)p)) killed(p, FALSE);
    return;
  }

  if ((p->body).status & BODY_STATUS_DEAD) {
    killed(p, spiking);
    return;
  }

  if (s->mode[3] == 0 && IsFrozen(p)) s->mode[3] = 1;
  if (s->mode[3] != 0) { 
    if (!spiking && isFar(s)) {
      disappear(s);
      return;
    }
    if (s->mode[3] == 1) {
      UpdateEntityAnim(s);
      s->mode[3] = 2;
      p->element = NULL;
      SetDDP(&p->body, spiking ? sSpikingCollisions : sCarryarmCollisions);
    }
    if (!IsFrozen(p)) s->mode[3] = 0;
    return;
  }

  if (p->element == NULL) {
    (sUpdates[s->mode[1]])((void*)p);
    if ((p->body).status & BODY_STATUS_WHITE) {
      p->element = ApplyElementEffect(0, (Object*)p, (const struct Coord*)(spiking ? &sSpikingElementCoord : &sCarryarmElementCoord));
      if (p->element != NULL) {
        SetDDP(&p->body, spiking ? sSpikingHarmless : sCarryarmHarmless);
        s->SAVED_DY = s->d.y;
        s->d.y = 0;
        if (!spiking) {
          SetMotion(s, ANIM_FLY_OFF);
          UpdateEntityAnim(s);
        }
      }
    }
    return;
  }

  if (IsDead(p->element)) {
    SetDDP(&p->body, spiking ? sSpikingCollisions : sCarryarmCollisions);
    p->element = NULL;
    s->d.y = s->SAVED_DY;
    return;
  }

  feet = spiking ? 0 : PIXEL(16);
  if (PushoutToUp1(s->coord.x - PIXEL(16), s->coord.y + feet) < 0) return;
  if (PushoutToUp1(s->coord.x + PIXEL(16), s->coord.y + feet) < 0) return;
  if (!spiking && isFar(s)) disappear(s);
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  s->coord.y += s->d.y;
  {
    s32 push = PushoutToUp1(s->coord.x - PIXEL(16), s->coord.y + feet);
    if (push < 0) s->coord.y += push;
    push = PushoutToUp1(s->coord.x + PIXEL(16), s->coord.y + feet);
    if (push < 0) s->coord.y += push;
  }
}

static void startSwoop(struct Entity* s) {
  s->d.x = -0x20A;
  if (FACES_RIGHT(s)) {
    SET_XFLIP(s, TRUE);
    s->d.x = 0x20A;
  }
  s->LIFT = 7;
  s->d.y = 0x150;
}

static void swoop(struct Entity* s) {
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y -= s->LIFT;
}

static void Carryarm_Carry(struct Carryarm* p) {
  struct Entity* s = &p->s;
  struct Entity* q = s->unk_28;
  if (isFar(s)) {
    disappear(s);
    return;
  }
  if (q != NULL && q->mode[0] > ENTITY_UPDATE) s->unk_28 = q = NULL;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 32;
      startSwoop(s);
      SetMotion(s, ANIM_CARRY);
      s->mode[2]++;
    case 1:
      swoop(s);
      if (--s->work[2] == 0 || q == NULL || ((struct Carryarm*)q)->element != NULL) s->mode[2]++;
      UpdateEntityAnim(s);
      break;
    case 2:
      s->unk_28 = NULL;
      SetMotion(s, ANIM_FLY_OFF);
      s->mode[2]++;
    case 3:
      swoop(s);
      UpdateEntityAnim(s);
      break;
  }
}

// 0x0808e340, 0x0808e538
static void Spiking_Carried(struct Carryarm* p) {
  struct Entity* s = &p->s;
  if (isFar(s)) {
    if (s->unk_2c != NULL) disappear(s->unk_2c);
    disappear(s);
    return;
  }
  if (s->unk_2c != NULL && s->unk_2c->mode[0] > ENTITY_UPDATE) s->unk_2c = NULL;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 28;
      startSwoop(s);
      SetMotion(s, ANIM_ROLL(0));
      s->mode[2]++;
      // fallthrough
    case 1:
      swoop(s);
      if (s->unk_2c == NULL) setMode(s, SPIKING_ROLL);
      if (--s->work[2] == 0) setMode(s, SPIKING_ROLL);
      UpdateEntityAnim(s);
      break;
  }
}

// 0x0808d814
static bool8 landAndStopAtWall(struct Entity* s) {
  s32 floor = FUN_08009f6c(s->coord.x, s->coord.y);
  s32 ahead, y;
  if (s->coord.y > floor) {
    s->coord.y = floor;
    if (s->mode[0] != ENTITY_DIE) {
      if (s->d.y > 0x100) PlaySound(BOUNCE_SOUND);
      s->d.y = -(s->d.y * 200 / 256);
    }
  }
  ahead = (s->flags & X_FLIP) ? PIXEL(16) : -PIXEL(16);
  y = s->coord.y - PIXEL(8);
  if ((u8)FUN_080098a4(s->coord.x + ahead, y) == 0) return FALSE;
  if (s->flags & X_FLIP) {
    s->coord.x = FUN_0800a22c(s->coord.x + ahead, y) - ahead;
  } else {
    s->coord.x = FUN_0800a31c(s->coord.x + ahead, y) - ahead;
  }
  return TRUE;
}

static u8 rollDelay(struct Entity* s) {
  s32 v = s->d.x >> 5;
  if (v < 0) v = -v;
  v = 21 - v;
  return (v > 0) ? v : 1;
}

// 0x0808e3e4, 0x0808e5ec
static void Spiking_Roll(struct Carryarm* p) {
  struct Entity* s = &p->s;
  u16 shape;
  if (isFar(s)) {
    disappear(s);
    return;
  }
  switch (s->mode[2]) {
    case 0:
      s->unk_2c = NULL;
      SetMotion(s, ANIM_ROLL(0));
      s->work[2] = 0;
      p->bounces = 0;
      s->work[3] = rollDelay(s);
      s->d.y = 0;
      s->mode[2]++;
    case 1:
      SetMotion(s, ANIM_ROLL(s->work[2]));
      if (--s->work[3] == 0) {
        s->work[3] = rollDelay(s);
        if (++s->work[2] > 2) s->work[2] = 0;
      }
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (landAndStopAtWall(s)) {
        if (s->d.y > 0x100) PlaySound(BOUNCE_SOUND);
        s->d.x = -s->d.x;
        s->d.y = -0x300;
        if (++p->bounces == 5) {
          p->cut = 0;
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          s->mode[1] = DEATH_SPIKING;
          return;
        }
      }
      shape = FUN_080098a4(s->coord.x, (s->coord.y & ~0xFF) + PIXEL(1)) & 15;
      if (shape == 1 && (u32)(s->d.x + 0x200) <= 0x3FF) {  // Slow on flat ground: stay there
        s32 push = PushoutToUp1(s->coord.x, (s->coord.y & ~0xFF) + PIXEL(1));
        if (push < 0) s->coord.y += push;
        shape = FUN_080098a4(s->coord.x, (s->coord.y & ~0xFF) + PIXEL(1)) & 15;
      }
      if (shape <= 13) {
        s->d.x += sSlopeDX[shape];
        s->d.y += sSlopeDY[shape];
      }
      if (shape != 0 && s->d.y <= 0xFF) s->d.y += 0x100;
      s->d.x = s->d.x * 250 / 256;
      s->d.y = s->d.y * 250 / 256;
      if ((p->body).status & BODY_STATUS_WHITE) s->d.x += (p->zeroSide > 0) ? -96 : 96;
      s->d.x += (s->d.x > 0) ? 12 : -12;
      SET_XFLIP(p, s->d.x > 0);
      UpdateEntityAnim(s);
      break;
  }
}

static const EnemyFunc sUpdates[3] = {
    [CARRYARM_CARRY] = (EnemyFunc)Carryarm_Carry,
    [SPIKING_CARRIED] = (EnemyFunc)Spiking_Carried,
    [SPIKING_ROLL] = (EnemyFunc)Spiking_Roll,
};

static void explode(struct Entity* s, s32 above) {
  Coords32 c;
  c.x = s->coord.x, c.y = s->coord.y - above;
  CreateSmoke(1, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  TryDropItem(4, (struct Coord*)&s->coord);
  s->mode[1] = DEATH_GONE;
}

static void Carryarm_Die(struct Carryarm* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  switch (s->mode[1]) {
    case DEATH_CARRYARM:
      if ((p->cut & 3) == 1) {
        SetMotion(s, ANIM_LOWER_HALF);
        createHalf(s, DEBRIS_UPPER_HALF);
        s->renderPrio = 25;
        s->work[2] = 24;
      } else {
        SetMotion(s, ANIM_HIT);
        s->work[2] = (p->cut & 2) ? 1 : 16;
      }
      EXIT_BODY(p);
      s->mode[1]++;
    case DEATH_CARRYARM_FALL:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
      if (--s->work[2] == 0 || FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        c.x = s->coord.x, c.y = s->coord.y - PIXEL(8);
        createPieces(DEBRIS_PIECE, (s->flags & X_FLIP) != 0, &c);
        explode(s, PIXEL(8));
      }
      UpdateEntityAnim(s);
      break;

    case DEATH_SPIKING:
      if ((p->cut & 3) == 1) {
        SetMotion(s, ANIM_SPIKING_LOWER_HALF);
        createHalf(s, DEBRIS_SPIKING_UPPER_HALF);
        s->work[2] = 24;
      } else {
        c.x = s->coord.x + PIXEL(4) - ((p->zeroSide > 0) ? PIXEL(8) : 0);
        c.y = s->coord.y - PIXEL(16);
        createPieces(DEBRIS_SPIKING_PIECE, (s->flags & X_FLIP) != 0, &c);
        s->flags &= ~DISPLAY;
        s->work[2] = 1;
      }
      EXIT_BODY(p);
      s->mode[1]++;
    case DEATH_SPIKING_FALL:
      s->coord.x += s->d.x;
      s->d.x = s->d.x * 192 / 256;
      s->coord.y += s->d.y;
      s->d.y += 0x40;
      if (s->d.y > 0x700) s->d.y = 0x700;
      landAndStopAtWall(s);
      if (--s->work[2] == 0) explode(s, PIXEL(16));
      UpdateEntityAnim(s);
      break;

    case DEATH_GONE:  // 0x0808e124
      s->flags &= ~DISPLAY;
      if (s->work[2] != 0) {
        s->work[2]--;
      } else {
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      }
      break;
  }
}

// --------------------------------------------
// Debris, Zero 2 VFX 56

static void Debris_Init(struct Entity* p);
static void Debris_Update(struct Entity* p);
static void Debris_Die(struct Entity* p);

// clang-format off
const VFXRoutine gApZ2CarryarmDebrisRoutine = {
    [ENTITY_INIT] =      (void*)Debris_Init,
    [ENTITY_UPDATE] =    (void*)Debris_Update,
    [ENTITY_DIE] =       (void*)Debris_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// 0x080bb98c, 0x080bba3c
static void createHalf(struct Entity* parent, u8 kind) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_CARRYARM_DEBRIS);
    p->work[0] = kind;
    p->work[3] = (parent->flags & X_FLIP) != 0;
    p->coord = parent->coord;
    p->d = parent->d;
  }
}

// 0x080bb9d4, 0x080bba88
static void createPieces(u8 kind, bool8 facingRight, Coords32* c) {
  u8 i;
  for (i = 0; i < 3; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_CARRYARM_DEBRIS);
      p->work[0] = kind;
      p->work[1] = i;
      p->work[3] = facingRight;
      p->coord = *c;
    }
  }
}

// 0x080bbb74, 0x080bbca4, 0x080bbdfc, 0x080bbf20
static void Debris_Init(struct Entity* p) {
  u8 n;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  p->flags |= DISPLAY;
  InitNonAffineMotion(p);
  useApSheets(p);
  SET_XFLIP(p, p->work[3]);
  switch (p->work[0]) {
    case DEBRIS_UPPER_HALF:
    case DEBRIS_SPIKING_UPPER_HALF:
      SetMotion(p, (p->work[0] == DEBRIS_UPPER_HALF) ? ANIM_UPPER_HALF : ANIM_SPIKING_UPPER_HALF);
      p->work[2] = 24;
      break;
    default: 
      n = p->work[1];
      SetMotion(p, (p->work[0] == DEBRIS_PIECE) ? ANIM_PIECE(n) : ANIM_SPIKING_PIECE(n));
      if (p->work[3]) n = 2 - n;
      p->d.x = PIXEL(n - 1) + (RANDOM(RNG_0202f388) & 0x1FF) - 0x100;
      p->d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x1FF);
      p->work[2] = 0;
      break;
  }
  Debris_Update(p);
}

static void Debris_Update(struct Entity* p) {
  switch (p->work[0]) {
    case DEBRIS_UPPER_HALF:  // 0x080bbc14
      p->coord.x += p->d.x;
      p->d.x = p->d.x * 192 / 256;
      p->coord.y += p->d.y;
      p->d.y += 0x40;
      UpdateEntityAnim(p);
      p->work[2]--;
      if (FUN_080098a4(p->coord.x, p->coord.y + PIXEL(8)) != 0) p->work[2] = 0;
      if (p->work[2] == 0 || FUN_080098a4(p->coord.x, p->coord.y) != 0) {
        createPieces(DEBRIS_PIECE, p->work[3], &p->coord);
        CreateSmoke(1, &p->coord);
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;

    case DEBRIS_SPIKING_UPPER_HALF:  // 0x080bbe9c
      p->coord.x += p->d.x;
      p->d.x = p->d.x * 232 / 256;
      p->coord.y += p->d.y;
      p->d.y += 0x20;
      if (p->d.y > 0x700) p->d.y = 0x700;
      {
        s32 floor = FUN_08009f6c(p->coord.x, p->coord.y);
        if (p->coord.y > floor) p->coord.y = floor;
      }
      UpdateEntityAnim(p);
      if (--p->work[2] == 0) {
        createPieces(DEBRIS_SPIKING_PIECE, p->work[3], &p->coord);
        CreateSmoke(1, &p->coord);
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;

    default:  // 0x080bbd8c, 0x080bc008: pieces
      p->flags = (++p->work[2] & 1) ? (p->flags | DISPLAY) : (p->flags & ~DISPLAY);
      p->coord.x += p->d.x;
      p->coord.y += p->d.y;
      p->d.y += 0x40;
      UpdateEntityAnim(p);
      if (FUN_080098a4(p->coord.x, p->coord.y) != 0) {
        CreateSmoke(3, &p->coord);
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// 0x080bbb54
static void Debris_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
// Zero 2 data. 

// clang-format off
static const struct Collision sCarryarmCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0x800, 0x1800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0x800, 0x1800, 0x1000}},
};

static const struct Collision sCarryarmHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0x800, 0x1800, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0x800, 0x1800, 0x1000}},
};

static const struct Collision sSpikingCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, -0xa00, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1800}},
};

static const struct Collision sSpikingHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1800}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0, 0, 0x00000000, {0x0, -0xa00, 0x1800, 0x1800}},
};
// clang-format on

static const s32 sSlopeDX[14] = {0, 0, -19, -19, -14, -14, -14, -14, 19, 19, 14, 14, 14, 14};
static const s32 sSlopeDY[14] = {64, 0, 9, 9, 3, 3, 3, 3, 9, 9, 3, 3, 3, 3};

#endif  // AP
