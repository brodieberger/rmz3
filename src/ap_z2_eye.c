#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "random.h"
#include "score.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's hanging eye, enemy 79.
  work0:
    0: sweeps across
    1: hangs from ceiling, homes in on Zero
    2: rises from below, homes in on Zero
*/

struct Eye {
  OBJECT_HDR;
  struct Entity* elementEffect;  // 0xB4
  s32 travelled;                 // 0xB8
  s32 zeroDx;                    // 0xBC, Zero's x minus its own at last hit
  s32 postX;                     // 0xC0
};
static_assert(sizeof(struct Eye) == sizeof(struct Enemy));

enum {
  EYE_WAIT,
  EYE_DROP,
  EYE_SWEEP,
  EYE_HOME,
  EYE_HANG,
  EYE_RETURN,
  EYE_BOUNCE,
  EYE_RISE,
  EYE_RECOIL,
  EYE_PULLED,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_EYE, n)
#define ANIM_FLY ANIM(0)
#define ANIM_HANG ANIM(1)
#define ANIM_CUT ANIM(2)

#define FACING_RIGHT(p) (((p)->s.flags & X_FLIP) != 0)
#define frozenState mode[3]
#define gaveUp work[3]

static const struct Collision sCollisions[2];
static const struct Collision sHarmless[2];
static const u8 sFirstMode[3] = {EYE_WAIT, EYE_HANG, EYE_RISE};
static const Coords32 sElementCoord = {0, 0};

static u16 Eye_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy);
static void Eye_Init(struct Eye* p);
static void Eye_Update(struct Eye* p);
static void Eye_Die(struct Eye* p);
static void createShell(struct Eye* p);
static void createPieces(Coords32* c, bool8 right);

// clang-format off
const EnemyRoutine gApZ2EyeRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Eye_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Eye_Update,
    [ENTITY_DIE] =       (EnemyFunc)Eye_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static void setMode(struct Eye* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void Eye_OnCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Eye* p = (struct Eye*)body->parent;
  p->zeroDx = (pZero2->s).coord.x - (p->s).coord.x;
}

// 0x08092c88
static void Eye_Init(struct Eye* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->flags |= FLIPABLE;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY;
  INIT_BODY(p, sCollisions, 4, Eye_OnCollision);
  (p->body).unk_28 = (u32)Eye_Pull;
  SetMotion(s, ANIM_HANG);
  s->mode[1] = sFirstMode[s->work[0]];
  SET_XFLIP(p, (pZero2->s).coord.x - s->coord.x > 0);
  if (s->work[0] != 2) {
    s->coord.y = FUN_0800a134(s->coord.x, s->coord.y) + PIXEL(8);  // under the ceiling
    s->work[1] = FALSE;
  } else {
    s->work[1] = TRUE;
  }
  p->elementEffect = NULL;
  p->postX = s->coord.x;
  s->gaveUp = FALSE;
  Eye_Update(p);
}

static void Eye_Recoil(struct Eye* p);
static void Eye_Wait(struct Eye* p);
static void Eye_Drop(struct Eye* p);
static void Eye_Sweep(struct Eye* p);
static void Eye_Home(struct Eye* p);
static void Eye_Hang(struct Eye* p);
static void Eye_Return(struct Eye* p);
static void Eye_Bounce(struct Eye* p);
static void Eye_Rise(struct Eye* p);

// 0x08092d88
// 0x08093168
static u16 Eye_Pull(struct Entity* s, u16 pulling, s32 dx, s32 dy) {
  if (s->mode[1] != EYE_PULLED) {
    s->mode[1] = EYE_PULLED;
    s->mode[2] = 0;
  }
  s->coord.x += dx;
  s->coord.y += dy;
  if (pulling) return 1;
  s->mode[1] = s->work[0] == 0 ? EYE_SWEEP : EYE_HOME;
  s->mode[2] = 1;
  return 0;
}

static void Eye_Update(struct Eye* p) {
  struct Entity* s = &p->s;

  if (ApRecoilHit((Object*)p) && s->mode[1] != EYE_RECOIL) setMode(p, EYE_RECOIL);
  if (s->mode[1] == EYE_RECOIL) {
    Eye_Recoil(p);
    return;
  }

  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    s->mode[1] = 0;
    Eye_Die(p);
    return;
  }

  if (s->frozenState == 0 && IsFrozen(p)) s->frozenState = 1;
  if (s->frozenState != 0) {
    if (s->frozenState == 1) {
      UpdateEntityAnim(s);
      s->frozenState = 2;
      p->elementEffect = NULL;
      SetDDP(&p->body, sCollisions);
    }
    if (!IsFrozen(p)) s->frozenState = 0;
    return;
  }

  if (p->elementEffect == NULL) {
    switch (s->mode[1]) {
      case EYE_WAIT: Eye_Wait(p); break;
      case EYE_DROP: Eye_Drop(p); break;
      case EYE_SWEEP: Eye_Sweep(p); break;
      case EYE_HOME: Eye_Home(p); break;
      case EYE_HANG: Eye_Hang(p); break;
      case EYE_RETURN: Eye_Return(p); break;
      case EYE_BOUNCE: Eye_Bounce(p); break;
      case EYE_RISE: Eye_Rise(p); break;
    }
    if ((p->body).status & BODY_STATUS_WHITE) {
      p->elementEffect = ApplyElementEffect(0, (Object*)p, (const struct Coord*)&sElementCoord);
      if (p->elementEffect != NULL) {
        SetDDP(&p->body, sHarmless);
        s->unk_coord.y = s->d.y;
        s->d.y = 0;
      }
    }
  } else if (IsDead(p->elementEffect)) {
    SetDDP(&p->body, sCollisions);
    p->elementEffect = NULL;
    s->d.y = s->unk_coord.y;
  } else if (PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y + PIXEL(8)) >= 0 &&
             PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y + PIXEL(8)) >= 0) {
    // Burning or frozen, falls and settles on ground
    s32 push;
    s->d.y += 0x40;
    if (s->d.y > 0x700) s->d.y = 0x700;
    s->coord.y += s->d.y;
    push = PushoutToUp1(s->coord.x - PIXEL(8), s->coord.y + PIXEL(8));
    if (push < 0) s->coord.y += push;
    push = PushoutToUp1(s->coord.x + PIXEL(8), s->coord.y + PIXEL(8));
    if (push < 0) s->coord.y += push;
  }

  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(128)) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// Same as Pantheon Hunter, 0x08064cac
static void Eye_Recoil(struct Eye* p) {
  if (ApRecoilFly((Object*)p)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    EXIT_BODY(p);
    Eye_Die(p);
  }
}

// 0x080931b4
static void Eye_Wait(struct Eye* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_HANG);
    s->work[2] = 32;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) setMode(p, EYE_DROP);
  UpdateEntityAnim(s);
}

// 0x080931fc: falls 48 px from ceiling
static void Eye_Drop(struct Eye* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_HANG);
    p->travelled = 0;
    s->d.y = 0;
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  p->travelled += s->d.y;
  if (p->travelled > PIXEL(48)) setMode(p, s->work[0] == 0 ? EYE_SWEEP : EYE_HOME);
  s->d.y += 0x20;
  if (s->d.y > 0x700) s->d.y = 0x700;
  UpdateEntityAnim(s);
}

static void giveUp(struct Eye* p) {
  (p->s).gaveUp = TRUE;
  setMode(p, EYE_RETURN);
}

static s32 fromPost(struct Eye* p) {
  s32 d = p->postX - (p->s).coord.x;
  return d < 0 ? -d : d;
}

// 0x08093270: 448 px out at most
static void Eye_Sweep(struct Eye* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    p->travelled = 0;
    s->work[2] = 0;
    s->d.x = FACING_RIGHT(p) ? PIXEL(1) : -PIXEL(1);
    s->mode[2]++;
  }
  s->d.y = COS(s->work[2]) << 1;
  s->work[2] += 2;
  s->coord.y += s->d.y;
  s->coord.x += s->d.x;
  p->travelled += PIXEL(1);
  if (fromPost(p) > PIXEL(448)) giveUp(p);
  UpdateEntityAnim(s);
}

// 0x0809332c: steers for 24 px above Zero's feet
static void Eye_Home(struct Eye* p) {
  struct Entity* s = &p->s;
  s32 dx, dy, len;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    (s->spr).oam.priority = 2;
    s->d.x = s->d.y = 0;
    s->work[2] = 0;
    s->mode[2]++;
  }
  dx = (pZero2->s).coord.x - s->coord.x;
  SET_XFLIP(p, dx > 0);
  dy = (pZero2->s).coord.y - s->coord.y - PIXEL(24);
  len = Sqrt((dx >> 8) * (dx >> 8) + (dy >> 8) * (dy >> 8)) << 8;
  dx = ((dx << 8) / len) * 384 / 256;
  dy = ((dy << 8) / len) * 384 / 256;
  s->d.x = s->d.x * 240 / 256 + dx * 15 / 256;
  s->d.y = s->d.y * 240 / 256 + dy * 15 / 256;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  p->travelled--;
  if (fromPost(p) > PIXEL(384)) giveUp(p);
  if ((p->body).status & BODY_STATUS_B2) setMode(p, EYE_BOUNCE);
  UpdateEntityAnim(s);
}

// 0x080934b4: waits until Zero is within 112 px across
static void Eye_Hang(struct Eye* p) {
  struct Entity* s = &p->s;
  s32 dx;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_HANG);
    s->work[2] = 90;
    s->mode[2]++;
  }
  if (s->work[2] != 0) {
    s->work[2]--;
  } else {
    dx = s->coord.x - (pZero2->s).coord.x;
    if (dx < 0) dx = -dx;
    if (dx <= 0x6FFF) setMode(p, EYE_DROP);
  }
  UpdateEntityAnim(s);
}

// 0x08093528: back to ceiling, or off top of screen once it gives up
static void Eye_Return(struct Eye* p) {
  struct Entity* s = &p->s;
  s32 perch, d;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    s->work[2] = s->gaveUp ? 1 : 0;
    s->mode[2]++;
  }
  s->coord.x += s->d.x;
  s->d.x = s->d.x * 250 / 256;
  perch = FUN_0800a134(s->coord.x, s->coord.y) + PIXEL(8);
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) {
    d = s->coord.y - perch;
    if (d < 0) d = -d;
    if (d > PIXEL(16)) s->work[2] = 1;
  }
  if (s->work[2] != 0) {
    s->coord.y -= PIXEL(1);
  } else {
    s->coord.y += (s->coord.y > perch) ? -PIXEL(1) : PIXEL(1);
    d = s->coord.y - perch;
    if (d < 0) d = -d;
    if (d <= 0x3FF) setMode(p, s->work[0] == 0 ? EYE_WAIT : EYE_HANG);
  }
  UpdateEntityAnim(s);
}

// 0x08093610
static void Eye_Bounce(struct Eye* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 16;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      s->coord.x += (p->zeroDx > 0) ? -PIXEL(2) : PIXEL(2);
      s->coord.y -= PIXEL(2);
      if (--s->work[2] == 0) s->mode[2]++;
      UpdateEntityAnim(s);
      return;
    case 2:
      s->work[2] = 20;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      if (--s->work[2] == 0) {
        s->mode[1] = EYE_HOME;
        s->mode[2] = 1;
      }
      UpdateEntityAnim(s);
      return;
  }
}

// 0x080936a4: pops 64 px out of floor
static void Eye_Rise(struct Eye* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM_FLY);
    (s->spr).oam.priority = 3;
    p->travelled = PIXEL(64);
    s->d.y = -PIXEL(5);
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  p->travelled -= (s->d.y < 0) ? -s->d.y : s->d.y;
  if (p->travelled < 0) {
    setMode(p, EYE_HOME);
    s->work[0] = 1;
  }
  s->d.y += 0x30;
  UpdateEntityAnim(s);
}

// --------------------------------------------

static void finish(struct Eye* p) {
  (p->s).flags &= ~DISPLAY;
  TryDropItem(4, (struct Coord*)&(p->s).coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  TryDropZakoDisk((struct Enemy*)p, &(p->s).coord);
}

// 0x08092f60
static void Eye_Die(struct Eye* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  switch (s->mode[1]) {
    case 0:
      if (s->d.x > 0) s->d.x = 0;
      if (s->d.x < -0x300) s->d.x = -0x300;
      s->d.y = 0;
      if ((p->body).status & BODY_STATUS_SLASHED) {
        // Shell falls off, eye drops after it
        s->work[2] = 32;
        createShell(p);
        SetMotion(s, ANIM_CUT);
        EXIT_BODY(p);
        s->mode[1]++;
        return;
      }
      s->work[2] = 8;
      createPieces(&s->coord, FACING_RIGHT(p));
      CreateSmoke(1, &s->coord);
      PlaySound(SE_ZAKO_EXPLODE);
      finish(p);
      EXIT_BODY(p);
      s->mode[1] = 2;
      return;

    case 1:
      s->work[2]--;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->d.y += 0x20;
      if (s->work[2] == 0 || FUN_080098a4(s->coord.x, s->coord.y) != 0) {
        c.x = s->coord.x;
        c.y = s->coord.y - PIXEL(12);
        CreateSmoke(1, &c);
        PlaySound(SE_ZAKO_EXPLODE);
        s->mode[1]++;
        finish(p);
      }
      UpdateEntityAnim(s);
      return;

    case 2:
      if (s->work[2] != 0) {
        s->work[2]--;
      } else {
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      }
      return;
  }
}

// --------------------------------------------
// Pieces, Zero 2's VFX 63

enum {
  SHELL,
  PIECE,
};

static const motion_t sPieces[3] = {ANIM(4), ANIM(5), ANIM(6)};

static void Debris_Init(struct VFX* p);
static void Debris_Update(struct VFX* p);
static void Debris_Die(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2EyeDebrisRoutine = {
    [ENTITY_INIT] =      Debris_Init,
    [ENTITY_UPDATE] =    Debris_Update,
    [ENTITY_DIE] =       Debris_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bd160. Facing passed in work[3].
static void createShell(struct Eye* eye) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_EYE_DEBRIS);
    (p->s).work[0] = SHELL;
    (p->s).work[3] = FACING_RIGHT(eye);
    (p->s).coord = (eye->s).coord;
    (p->s).d.x = (eye->s).d.x / 4;
  }
}

// 0x080bd1a8
static void createPieces(Coords32* c, bool8 right) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_EYE_DEBRIS);
      (p->s).work[0] = PIECE;
      (p->s).work[1] = i;
      (p->s).work[3] = right;
      (p->s).coord = *c;
    }
  }
}

// 0x080bd29c / 0x080bd3c0
static void Debris_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  bool8 right = s->work[3];
  s->flags |= DISPLAY;
  InitNonAffineMotion(s);
  useApSheets(p);
  SET_XFLIP(p, right);
  if (s->work[0] == SHELL) {
    SetMotion(s, ANIM(3));
    s->d.y = 0;
    s->work[2] = 24;
  } else {
    u8 n = s->work[1];
    SetMotion(s, sPieces[n]);
    if (right) n = 2 - n;
    s->d.x = ((n - 1) << 8) + (RANDOM(RNG_0202f388) & 0x1FF) - PIXEL(1);
    s->d.y = -PIXEL(2) - (RANDOM(RNG_0202f388) & 0x1FF);
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Debris_Update(p);
}

// 0x080bd33c / 0x080bd4a0
static void Debris_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  UpdateEntityAnim(s);
  if (s->work[0] == SHELL) {
    s->work[2]--;
    if (GetMetatileAttr(s->coord.x, s->coord.y + PIXEL(16)) != 0) s->work[2] = 0;
    if (s->work[2] != 0 && FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    createPieces(&s->coord, s->work[3]);
    CreateSmoke(1, &s->coord);
  } else {
    if (FUN_080098a4(s->coord.x, s->coord.y) == 0) return;
    CreateSmoke(3, &s->coord);
  }
  SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// 0x080bd278
static void Debris_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, HARDNESS_B3, 0, 1, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, HARDNESS_B3, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};

static const struct Collision sHarmless[2] = {
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0, 0, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

#endif  // AP
