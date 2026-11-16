#include "ap.h"
#include "ap_import.h"
#include "collision.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "overworld.h"
#include "palette_animation.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"

#if AP

/*
  Yggdrasil's seal scene (Zero 2's script 16): Elpizo, the Dark Elf's seal he breaks, and the Dark Elf,
  which the Temple of Wind's scene shares.
*/

#define ELPIZO(n) MOTION(DM205_Z2_ELPIZO, (n))
#define BOLT(n) MOTION(AP_SHEET_Z2_SEAL_BOLT, (n))
#define SEAL(n) MOTION(AP_SHEET_Z2_SEAL, (n))
#define DARK_ELF(n) MOTION(AP_SHEET_Z2_DARK_ELF, (n))
#define FLAGS (s->scriptEntity->flags)
#define PARENT (s->scriptEntity->unk_04)
#define PLTT_ANIM_ID(n) (0x8000 | (n))

static const struct PreloadEntity sBoltSheet = {AP_SHEET_Z2_SEAL_BOLT, 0, 768, 10, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSealSheet = {AP_SHEET_Z2_SEAL, 0, 896, 8, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sDarkElfSheet = {AP_SHEET_Z2_DARK_ELF, 0, 640, 5, 0, AP_PRELOAD_SHEET, 0};

extern const PlttAnimData gApZ2Na3_PlttAnim75;
extern const AnimCmd* const gApZ2Na3_PlttAnimScript75[];

// clang-format off
#define SCENE_ROUTINE(name, init, update, disappear) \
const SolidRoutine name = { \
    [ENTITY_INIT] =      (SolidFunc)init, \
    [ENTITY_UPDATE] =    (SolidFunc)update, \
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity, \
    [ENTITY_DISAPPEAR] = (SolidFunc)disappear, \
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity, \
}
// clang-format on

static bool8 animEnded(struct Entity* s) { return (s->motion).state == ANIM_END; }

static struct Entity* createSolid(struct Entity* parent, u8 id, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    INIT_SOLID_ROUTINE(p, id);
    p->renderPrio = 30;
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

static void die(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
}

// --------------------------------------------
/*
  Zero 2's projectile 53, Elpizo's ring holding Zero still. Ends when work1 is set.
*/

#define RING(n) MOTION(AP_SHEET_Z2_DARK_RING, (n))

static const struct PreloadEntity sRingSheet = {AP_SHEET_Z2_DARK_RING, 0, 848, 7, 0, AP_PRELOAD_SHEET, 0};

// clang-format off
// 0x083455a0
static const struct Collision sRing[1] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0, 33, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
};
// clang-format on

static void Ring_Init(struct Projectile* p);
static void Ring_Update(struct Projectile* p);
static void Ring_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2DarkRingRoutine = {
    [ENTITY_INIT] =      Ring_Init,
    [ENTITY_UPDATE] =    Ring_Update,
    [ENTITY_DIE] =       Ring_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x080a9fc8
static struct Entity* createRing(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_DARK_RING);
    p->coord = *at;
    p->work[0] = p->work[1] = 0;
  }
  return p;
}

// 0x080aa020
static void Ring_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sRingSheet);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, RING(0));
  SET_XFLIP(s, FALSE);
  s->flags |= COLLIDABLE;
  INIT_BODY(p, sRing, 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = 1;
  Ring_Update(p);
}

// 0x080aa100: lands on Zero and holds
static void Ring_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 1) {
    SetMotion(s, RING(1));
    s->coord.x = (pZero2->s).coord.x;
    s->coord.y = (pZero2->s).coord.y - PIXEL(20);
    s->mode[1]++;
  }
  UpdateEntityAnim(s);
  if (s->work[1] == 0) return;
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Ring_Die(p);
}

// 0x080aa1d8
static void Ring_Die(struct Projectile* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, RING(2));
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (animEnded(s)) SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's solid 5 work0 17, Elpizo
  flags: 1 raises his hand till 1 again, 2 stands, 4 casts a ring, 8 throws the bolt, 16 steps back till 32,
         back again on 64; at once 32 shakes with power till 64, 128 then ends the ring
*/

static void Elpizo_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      SetMotion(s, ELPIZO(8));
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (FLAGS & 1) {
        FLAGS &= ~1;
        SetMotion(s, ELPIZO(16));
        s->mode[1]++;
      }
      if (FLAGS & 2) {
        FLAGS &= ~2;
        SetMotion(s, ELPIZO(16));
      }
      if (FLAGS & 4) {
        FLAGS &= ~4;
        SetMotion(s, ELPIZO(14));
        s->mode[1] = 5;
        break;
      }
      if (FLAGS & 8) {
        FLAGS &= ~8;
        SetMotion(s, ELPIZO(19));
        s->work[2] = 15;
        s->mode[1] = 8;
        break;
      }
      if (FLAGS & 16) {
        FLAGS &= ~16;
        SetMotion(s, ELPIZO(17));
        s->mode[1] = 3;
      }
      if (FLAGS & 32) {
        FLAGS &= ~32;
        s->work[2] = 0;
        s->mode[1] = 13;
      }
      break;
    case 2:
      UpdateEntityAnim(s);
      if (!animEnded(s)) break;
      SetMotion(s, ELPIZO(17));
      s->mode[1]++;
      break;
    case 3:
      UpdateEntityAnim(s);
      if (!(FLAGS & 1)) break;
      FLAGS &= ~1;
      SetMotion(s, ELPIZO(18));
      s->mode[1]++;
      break;
    case 4:
      UpdateEntityAnim(s);
      if (animEnded(s)) s->mode[1] = 0;
      break;
    case 5:
      UpdateEntityAnim(s);
      if (!animEnded(s)) break;
      s->work[2] = 105;
      s->mode[1]++;
      break;
    case 6:
      UpdateEntityAnim(s);
      if (s->work[2] == 100) s->unk_2c = createRing(&s->coord);
      if (--s->work[2] != 0) break;
      SetMotion(s, ELPIZO(15));
      s->mode[1]++;
      break;
    case 7:
      UpdateEntityAnim(s);
      if (!animEnded(s)) break;
      SetMotion(s, ELPIZO(16));
      s->mode[1] = 1;
      break;
    case 8:
      UpdateEntityAnim(s);
      if (--s->work[2] != 0) break;
      createSolid(s, SOLID_Z2_SEAL_BOLT, 0, 0);
      s->mode[1]++;
      break;
    case 9:
      UpdateEntityAnim(s);
      if (!(FLAGS & 16)) break;
      FLAGS &= ~16;
      SetMotion(s, ELPIZO(20));
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 10:
      UpdateEntityAnim(s);
      if (s->work[2] != 0) {
        s->work[2]--;
        s->coord.x -= 0x200;
      } else if (FLAGS & 32) {
        SetMotion(s, ELPIZO(21));
        s->work[2] = 16;
        s->mode[1]++;
      }
      break;
    case 11:
      UpdateEntityAnim(s);
      if (s->work[2] != 0) {
        s->work[2]--;
        s->coord.x += 0x200;
      } else if (FLAGS & 64) {
        FLAGS &= ~(32 | 64);
        SetMotion(s, ELPIZO(22));
        s->work[2] = 15;
        s->mode[1]++;
      }
      break;
    case 12:
      UpdateEntityAnim(s);
      if (--s->work[2] != 0) break;
      SetMotion(s, ELPIZO(16));
      s->mode[1] = 1;
      break;
    case 13:
      InitScalerotMotion1(s);
      ResetDynamicMotion(s);
      SetMotion(s, ELPIZO(16));
      s->mode[1]++;
      FALLTHROUGH;
    case 14:
      UpdateEntityAnim(s);
      if ((++s->work[2] & 0x60) == 0) {
        AppendQuake(1, &s->coord);
        (s->spr).mag.x = (s->spr).mag.y = SIN(s->work[2] * 4) / 8 + 256;
      } else {
        (s->spr).mag.x = (s->spr).mag.y = 256;
      }
      if (!(FLAGS & 64)) break;
      FLAGS &= ~64;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
    case 15:
      if ((FLAGS & 128) && s->unk_2c != NULL) s->unk_2c->work[1] = 1;
      break;
  }
}

// 0x080c412c
static void Elpizo_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  wDynamicGraphicTilenums[DM205_Z2_ELPIZO] = 608;
  wDynamicMotionPalIDs[DM205_Z2_ELPIZO] = 9;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Elpizo_Update(p);
}

SCENE_ROUTINE(gApZ2YggElpizoRoutine, Elpizo_Init, Elpizo_Update, DeleteEntity);

// --------------------------------------------
/*
  Zero 2's solid 5 work0 18, Elpizo's bolt. Swells in his hand, spirals down onto the seal once he steps
  back, and waits there till he shakes.
*/

static void Bolt_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  struct Entity* elpizo = s->unk_28;
  u8 angle;
  switch (s->mode[1]) {
    case 0:
      s->coord.x = elpizo->coord.x + PIXEL(8);
      s->coord.y = elpizo->coord.y - PIXEL(40);
      SetMotion(s, BOLT(1));
      s->work[2] = s->work[3] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (s->work[2] < 64) s->work[2]++;
      (s->spr).mag.x = (s->spr).mag.y = s->work[2] * 4;
      if (elpizo->mode[1] <= 9) break;
      angle = (s8)--s->work[3] >> 1;
      s->angle = angle;
      s->coord.x -= COS(angle) * 6;
      s->coord.y -= SIN(angle) * 6;
      if (s->coord.x <= PIXEL(736) && ((s->motionID << 8) | (s->motion).id) != BOLT(2)) SetMotion(s, BOLT(2));
      if (s->coord.x > PIXEL(720)) break;
      s->coord.x = PIXEL(720);
      CreateSmoke(4, &s->coord);
      s->mode[1]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (!(elpizo->scriptEntity->flags & 32)) break;
      s->flags &= ~DISPLAY;
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x080c4560
static void Bolt_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitScalerotMotion1(s);
  s->texture = TEXTURE_AP_SHEET;
  ApLoadSheet(&sBoltSheet);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Bolt_Update(p);
}

SCENE_ROUTINE(gApZ2SealBoltRoutine, Bolt_Init, Bolt_Update, DeleteEntity);

// --------------------------------------------
/*
  Zero 2's solid 5 work0 19, the Dark Elf's seal. Bursts on flag 1, then smokes 120 frames.
*/

static void Seal_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  u8 i;
  switch (s->mode[1]) {
    case 0:
      SetMotion(s, SEAL(0));
      s->work[2] = s->work[3] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateEntityAnim(s);
      if (!(FLAGS & 1)) break;
      SetMotion(s, SEAL(1));
      createSolid(s, SOLID_Z2_SEAL_PART, 2, 0);
      for (i = 0; i < 2; i++) createSolid(s, SOLID_Z2_SEAL_PART, 0, i);
      for (i = 0; i < 8; i++) createSolid(s, SOLID_Z2_SEAL_PART, 1, i);
      s->work[2] = 120;
      s->mode[1]++;
      break;
    case 2:
      UpdateEntityAnim(s);
      if (--s->work[2] != 0) break;
      s->work[2] = 120;
      s->mode[1]++;
      FALLTHROUGH;
    case 3:
      UpdateEntityAnim(s);
      if ((s->work[2] & 15) == 0) {
        at.x = s->coord.x + (RANDOM(RNG_0202f388) & 0xFFF) - PIXEL(8);
        at.y = s->coord.y - (RANDOM(RNG_0202f388) & 0x3FFF);
        CreateSmoke(1, &at);
      }
      if (--s->work[2] == 0) s->mode[1]++;
      break;
    default:
      UpdateEntityAnim(s);
      break;
  }
}

// 0x080c4740
static void Seal_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  ApLoadSheet(&sSealSheet);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Seal_Update(p);
}

SCENE_ROUTINE(gApZ2YggSealRoutine, Seal_Init, Seal_Update, DeleteEntity);

/*
  Zero 2's solid 5 work0 20..22, the seal's pieces
  work0: 0 a half, 1 a shard, 2 the burst
  work1: which half or shard
*/

static void Part_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  u32 n;
  if (s->mode[1] == 0) {
    if (s->work[0] == 0) {
      SetMotion(s, SEAL(s->work[1] == 0 ? 4 : 5));
      s->d.x = s->work[1] == 0 ? 0x200 : -0x400;
      s->d.y = s->work[1] == 0 ? -0x3C0 : -0xC0;
      s->work[2] = 64;
    } else if (s->work[0] == 1) {
      SetMotion(s, SEAL(2));
      s->d.x = SIN(s->work[1] * 32);
      s->d.y = COS(s->work[1] * 32);
      s->work[2] = 255;
    } else {
      SetMotion(s, SEAL(3));
    }
    s->mode[1]++;
  }
  UpdateEntityAnim(s);
  if (s->work[0] == 2) {
    if (animEnded(s)) die(p);
    return;
  }
  s->coord.x += s->d.x;
  if (s->work[0] == 0) {
    s->d.y += 64;
    s->coord.y += s->d.y;
  } else {
    s->coord.y += s->d.y;
    s->d.x = s->d.x * 31 / 32;
    s->d.y = s->d.y * 31 / 32 + 1;
    n = s->work[1] + s->work[2];
    if ((n & 1) && (s->work[2] > 63 || !(n & 2))) {
      s->flags |= DISPLAY;
    } else {
      s->flags &= ~DISPLAY;
    }
    SET_XFLIP(s, (n >> 2) & 1);
    SET_YFLIP(s, (n >> 3) & 1);
  }
  if (--s->work[2] == 0) die(p);
}

// 0x080c49d8
static void Part_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  s->coord.x = s->unk_28->coord.x;
  s->coord.y = s->unk_28->coord.y - PIXEL(30);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Part_Update(p);
}

SCENE_ROUTINE(gApZ2SealPartRoutine, Part_Init, Part_Update, DeleteEntity);

// --------------------------------------------
/*
  Zero 2's solid 24 work0 0, the Dark Elf, over Elpizo
  flags: 1 spreads its wings, 2 rises, slides over him, shakes and dives into him, 4 stops flickering
*/

static const s32 sSparkleX[5] = {PIXEL(-8), PIXEL(4), PIXEL(-4), PIXEL(0), PIXEL(8)};

struct DarkElf {
  OBJECT_HDR;
  u8 bob;    // 0xB4
  u8 _b5;
  u8 timer;  // 0xB6
  u8 _b7[13];
};
static_assert(sizeof(struct DarkElf) == sizeof(struct Solid));

static void DarkElf_Update(struct DarkElf* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  StepPaletteAnimation(PLTT_ANIM_ID(75));
  UpdateEntityAnim(s);
  if (s->mode[1] <= 1) {
    s->coord.x = PARENT->coord.x + PIXEL(32);
    s->coord.y = PARENT->coord.y - PIXEL(64) + SIN(p->bob) * 8;
    p->bob += 2;
  }
  if (s->mode[1] <= 3 && (s->work[2]++ & 15) == 0) {
    at.x = s->coord.x + sSparkleX[s->work[3]];
    at.y = s->coord.y + PIXEL(8);
    ApZ2CreateElfSparkle(&at, (RANDOM(RNG_0202f388) & 0x7FFF) % 3 + 1);
    s->work[3] = (s->work[3] + 1) % 5;
  }
  if ((FLAGS & 4) || (s->mode[3]++ & 1)) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  switch (s->mode[1]) {
    case 0:
      if (!(FLAGS & 1)) break;
      createSolid(s, SOLID_Z2_DARK_WING, 3, 1);
      createSolid(s, SOLID_Z2_DARK_WING, 3, 0);
      s->mode[1]++;
      break;
    case 1:
      if (!(FLAGS & 2)) break;
      p->timer = 192;
      s->unk_coord.x = 0;
      s->mode[1]++;
      break;
    case 2:
      // Waits, rises over him, waits, slides till above him
      switch (s->unk_coord.x) {
        case 1:
          s->coord.y -= 64;
          if (s->coord.y >= PARENT->coord.y - PIXEL(112)) break;
          s->coord.y = PARENT->coord.y - PIXEL(112);
          p->timer = 16;
          s->unk_coord.x++;
          break;
        case 0:
        case 2:
          if (--p->timer == 0xFF) s->unk_coord.x++;
          break;
        default:
          s->coord.x -= 64;
          if (s->coord.x >= PARENT->coord.x) break;
          s->coord.x = PARENT->coord.x;
          p->timer = 128;
          s->mode[1]++;
          break;
      }
      break;
    case 3:
      if (--p->timer == 0xFF) s->mode[1]++;
      FALLTHROUGH;
    case 4:
      if (--p->timer != 0xFF) break;
      p->timer = 128;
      s->mode[1]++;
      break;
    case 5:
      if (--p->timer != 0xFF) break;
      p->timer = 64;
      s->mode[1]++;
      break;
    case 6:
      s->coord.x += (p->timer & 1) ? 0x100 : -0x100;
      if (--p->timer != 0xFF) break;
      p->timer = 32;
      s->d.y = 0x300;
      s->unk_coord.y = 12;
      s->mode[1]++;
      break;
    case 7:
      (s->spr).mag.x -= 6;
      (s->spr).mag.y -= 6;
      s->d.y -= s->unk_coord.y;
      s->coord.y += s->d.y;
      if (s->coord.y > PARENT->coord.y - PIXEL(34)) s->mode[1]++;
      break;
    case 8:
      if ((s->spr).mag.x > 6) {
        (s->spr).mag.x -= 6;
        (s->spr).mag.y -= 6;
        break;
      }
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// 0x080cf62c
static void DarkElf_Init(struct DarkElf* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sDarkElfSheet);
  InitRotatableMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, DARK_ELF(0));
  ApStartPaletteAnimation(PLTT_ANIM_ID(75), &gApZ2Na3_PlttAnim75, gApZ2Na3_PlttAnimScript75, 0x200 | 5 << 5);
  SET_XFLIP(s, FALSE);
  s->renderPrio = 23;
  p->bob = 0;
  s->work[2] = s->work[3] = 0;
  (s->spr).mag.x = (s->spr).mag.y = 256;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  DarkElf_Update(p);
}

// 0x080cf610
static void DarkElf_Disappear(struct DarkElf* p) {
  RemovePaletteAnimation(PLTT_ANIM_ID(75));
  DeleteEntity(&p->s);
}

SCENE_ROUTINE(gApZ2DarkElfRoutine, DarkElf_Init, DarkElf_Update, DarkElf_Disappear);

/*
  Zero 2's solid 24 work0 3 and 4, the Dark Elf's wings: each a segment off the elf, its tip a second
  segment off its end, unfolding, beating, then folding away as it dives
  work1: 1 the left one, mirrored
*/

struct Wing {
  OBJECT_HDR;
  u8 _b4[7];
  u8 tipAngle;  // 0xBB
  u16 scaleX;   // 0xBC
  u16 scaleY;   // 0xBE
  u8 _c0[4];
};
static_assert(sizeof(struct Wing) == sizeof(struct Solid));

static void grow(struct Wing* p) {
  p->scaleX += 2;
  p->scaleY += 1;
}

static void Wing_Update(struct Wing* p) {
  struct Entity* s = &p->s;
  struct Entity* elf = s->unk_28;
  struct Entity* tip = s->unk_2c;
  u8 a;
  if (elf->mode[0] > ENTITY_UPDATE) {
    die((struct Solid*)p);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      s->work[3] = 8;
      p->scaleY += 16;
      s->d.x += s->work[1] != 0 ? 0x100 : 0x180;
      if (p->scaleY > 127) s->mode[1]++;
      break;
    case 1:
      p->scaleX += 8;
      if (p->scaleX <= 63) break;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    case 2:
      if (--s->work[2] != 0xFF) break;
      s->unk_2c = createSolid(s, SOLID_Z2_DARK_WING_TIP, 4, s->work[1]);
      s->mode[1]++;
      break;
    case 3:
      if (tip->mode[1] <= 2) break;
      s->work[2] = 16;
      s->mode[1]++;
      break;
    // Beats: swings out, slows, swings back, slows
    case 4:
      s->work[2] += 4;
      s->work[3] += s->work[2] >> 4;
      grow(p);
      if (s->work[3] > 64) s->mode[1]++;
      break;
    case 5:
      s->work[2] -= 8;
      s->work[3] += s->work[2] >> 4;
      grow(p);
      if (s->work[2] <= 15) s->mode[1]++;
      break;
    case 6:
      s->work[2] += 3;
      s->work[3] -= s->work[2] >> 4;
      grow(p);
      if (s->work[3] <= 63) s->mode[1]++;
      break;
    case 7:
      s->work[2] -= 3;
      s->work[3] -= s->work[2] >> 4;
      grow(p);
      if (s->work[3] <= 47) s->mode[1]++;
      break;
    case 8:
      if (tip->mode[1] <= 5) break;
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 9:
      s->work[3] = SIN(s->work[2]) / 20 + 48;
      s->work[2] += 2;
      if (elf->work[0] != 0 || elf->mode[1] <= 4) break;
      s->work[2] = 32;
      s->mode[1]++;
      break;
    case 10:
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 48;
      s->mode[1]++;
      break;
    case 11:
      s->work[2]--;
      s->work[3] -= s->work[2] >> 4;
      if (p->scaleX > 16) {
        p->scaleX -= 8;
        break;
      }
      s->work[2] = 16;
      p->scaleX = 16;
      s->mode[1]++;
      break;
    case 12:
      s->mode[1]++;
      break;
    case 13:
      if (p->scaleY > 64) {
        p->scaleY -= 64;
        break;
      }
      die((struct Solid*)p);
      break;
  }
  s->angle = s->work[3];
  a = (s->flags & X_FLIP) ? -s->work[3] : s->work[3];
  s->coord.x = elf->coord.x + SIN(a) * s->d.x / 256;
  s->coord.y = elf->coord.y - COS(a) * s->d.x / 256;
  (s->spr).mag.x = p->scaleX;
  (s->spr).mag.y = p->scaleY;
}

// 0x080cf978
static void Wing_Init(struct Wing* p) {
  struct Entity* s = &p->s;
  InitScalerotMotion2(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, DARK_ELF(1));
  SET_XFLIP(s, s->work[1] & 1);
  s->renderPrio = (s->work[1] & 1) ? 25 : 23;
  s->d.x = s->d.y = 0;
  p->scaleX = p->scaleY = 16;
  s->work[2] = 1;
  s->work[3] = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Wing_Update(p);
}

SCENE_ROUTINE(gApZ2DarkWingRoutine, Wing_Init, Wing_Update, DeleteEntity);

static void Tip_Update(struct Wing* p) {
  struct Entity* s = &p->s;
  struct Entity* wing = s->unk_28;
  struct Entity* elf = s->unk_2c;
  u8 a;
  if (elf->mode[0] > ENTITY_UPDATE) {
    die((struct Solid*)p);
    return;
  }
  UpdateEntityAnim(s);
  switch (s->mode[1]) {
    case 0:
      p->tipAngle = 8;
      p->scaleY += 32;
      if (p->scaleY > 383) s->mode[1]++;
      break;
    case 1:
      p->scaleX += 8;
      if (p->scaleX <= 63) break;
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 2:
      if (s->work[2]++ <= 24) break;
      s->work[2] = 12;
      s->mode[1]++;
      break;
    case 3:
      s->work[2]++;
      p->tipAngle += s->work[2] >> 4;
      p->scaleX += 2;
      p->scaleY += s->work[1] != 0 ? -1 : 1;
      if (wing->mode[1] > 4) s->mode[1]++;
      break;
    case 4:
      s->work[2] += 8;
      p->tipAngle += s->work[2] >> 4;
      p->scaleX += s->work[1] != 0 ? 3 : 5;
      p->scaleY += s->work[1] != 0 ? -2 : 2;
      if (p->tipAngle <= 131) break;
      s->work[2] = 96;
      s->mode[1]++;
      break;
    case 5:
      p->scaleX++;
      s->work[2] -= 3;
      p->tipAngle -= s->work[2] >> 4;
      if (p->tipAngle > 55) break;
      s->work[2] = 0;
      s->mode[1]++;
      break;
    case 6:
      s->work[3] = SIN(s->work[2]) / 32 + 56;
      s->work[2] += 2;
      if (elf->mode[1] <= 4) break;
      s->work[2] = 32;
      s->mode[1]++;
      break;
    case 7:
      if (p->tipAngle > wing->work[3]) {
        p->tipAngle--;
      } else if (p->tipAngle < wing->work[3]) {
        p->tipAngle++;
      }
      if (--s->work[2] != 0xFF) break;
      p->tipAngle = wing->work[3];
      s->mode[1]++;
      break;
    case 8:
      p->tipAngle = wing->work[3];
      if (p->scaleX > 16) {
        p->scaleX -= 16;
        break;
      }
      s->work[2] = 16;
      p->scaleX = 16;
      s->mode[1]++;
      break;
    case 9:
      p->tipAngle = wing->work[3];
      s->mode[1]++;
      break;
    case 10:
      if (p->scaleY > 64) {
        p->scaleY -= 64;
        break;
      }
      die((struct Solid*)p);
      break;
  }
  s->angle = p->tipAngle;
  a = (s->flags & X_FLIP) ? -wing->angle : wing->angle;
  s->coord.x = wing->coord.x + SIN(a) * 20 * (wing->spr).mag.y / 256;
  s->coord.y = wing->coord.y - COS(a) * 20 * (wing->spr).mag.y / 256;
  (s->spr).mag.x = p->scaleX;
  (s->spr).mag.y = p->scaleY;
}

// 0x080cfa24
static void Tip_Init(struct Wing* p) {
  struct Entity* s = &p->s;
  InitScalerotMotion1(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, DARK_ELF(1));
  SET_XFLIP(s, s->work[1] & 1);
  s->renderPrio = (s->work[1] & 1) ? 26 : 21;
  s->d.x = s->d.y = 0;
  p->scaleX = p->scaleY = 16;
  s->work[2] = 1;
  s->work[3] = 0;
  s->unk_2c = s->unk_28->unk_28;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Tip_Update(p);
}

SCENE_ROUTINE(gApZ2DarkWingTipRoutine, Tip_Init, Tip_Update, DeleteEntity);

/*
  Zero 2's solid 24 work0 6, the Dark Elf freed from the seal. Bobs, sinks on flag 1, and on 2 glides to the
  other and stays on it.
*/

static void Twin_Update(struct DarkElf* p) {
  struct Entity* s = &p->s;
  UpdateEntityAnim(s);
  if (s->mode[3]++ & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  switch (s->mode[1]) {
    case 0:
    case 2:
      s->coord.x = s->unk_coord.x;
      s->coord.y = s->unk_coord.y + SIN(p->bob) * 8;
      p->bob += 2;
      if (s->mode[1] == 0) {
        if (FLAGS & 1) s->mode[1]++;
        break;
      }
      if (!(FLAGS & 2)) break;
      s->work[2] = 192;
      s->d.x = (PARENT->coord.x - s->coord.x) / 192;
      s->d.y = (PARENT->coord.y - s->coord.y) / 192;
      s->mode[1]++;
      break;
    case 1:
      s->coord.y += 128;
      if (s->coord.y <= PARENT->coord.y) break;
      s->unk_coord = s->coord;
      p->bob = 0;
      s->mode[1]++;
      break;
    case 3:
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->coord.y - PARENT->coord.y < 2 * s->d.y && PARENT->coord.y - s->coord.y < 2 * s->d.y) {
        s->coord.y = PARENT->coord.y;
      }
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;
    case 4:
      s->coord = PARENT->coord;
      break;
  }
}

// 0x080cfb74
static void Twin_Init(struct DarkElf* p) {
  struct Entity* s = &p->s;
  InitScalerotMotion1(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, DARK_ELF(0));
  SET_XFLIP(s, FALSE);
  s->renderPrio = 23;
  p->bob = 0;
  s->work[2] = s->work[3] = 0;
  (s->spr).mag.x = (s->spr).mag.y = 256;
  s->unk_coord = s->coord;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  s->mode[3] = 1;
  Twin_Update(p);
}

SCENE_ROUTINE(gApZ2DarkElfTwinRoutine, Twin_Init, Twin_Update, DeleteEntity);

#endif  // AP
