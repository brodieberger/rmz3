#include "ap.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "script.h"
#include "spawn.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"

#if AP

/*
  Zero 2 Harpuia, boss 8. Boss of the crystal cave,
  Attacks in order, every other picked randomly:
    - a dash across the arena firing a sonic wave
    - three thrown blades
    - thunder orbs circling him that fire inward
    - a dive that grabs Zero, carries him up and slams him down upside down
  Drops to the floor when taking damage, then does a three-slash combo or a lunge into a rising slash, or flies back up. 
  
  At rank A or S he uses his EX attack at 32 HP and again at 16 HP
  
  Not fully finished. He's missing some visual effects.
*/

struct Harpuia {
  OBJECT_HDR;
  u8 _b4[8];
  bool8 hitFromRight;  // 0xBC, side his last hit came from, for his knockback
  u8 exPass;           // 0xBD, EX dashes done
  u8 pattern;          // 0xBE, 0..7: even picks attack pattern / 2, odd picks are random
  u8 exUsed;           // 0xBF, 0..2: EX used at 32 HP, then at 16 HP
  u16 sound;           // 0xC0,
  u8 _c2[2];
  s32 left;            // 0xC4, arena bounds
  s32 right;           // 0xC8
  s32 hoverY;          // 0xCC
  s32 trailX;          // 0xD0, where a dash started, for its speed blur (WIP)
  s32 trailStep;       // 0xD4
  struct Zero* zero;   // 0xD8, set when he hits Zero, for the grab
  bool8 orbsDone;      // 0xDC, his thunder orbs leave once this is set
  u8 _dd[7];
};
static_assert(sizeof(struct Harpuia) == sizeof(struct Boss));

// Zero 2 sounds
#define SND_TELEPORT SE_TENSOU_BACK     // 155
#define SND_WHOOSH SE_UNK_101           // 101
#define SND_SLASH SE_HARPUIA_ATK        // 104
#define SND_HURT SE_HARPUIA_DAMAGE      // 102

#define HARPUIA(n) MOTION(DM200_Z2_HARPUIA, (n))
#define FACING_RIGHT(p) (((p)->s.flags & X_FLIP) != 0)

static const struct Collision sCollisions[30];
static const u8 sSlashCollisions[12];
static const Coords32 sElementCoord = {0, -PIXEL(24)};
#define HB_BODY (&sCollisions[1])
#define HB_DASH (&sCollisions[4])
#define HB_HOLD (&sCollisions[6])
#define HB_SLAM (&sCollisions[7])
#define HB_DIVE (&sCollisions[26])
#define HB_INTRO (&sCollisions[29])

static void Z2Harpuia_Init(struct Harpuia* p);
static void Z2Harpuia_Update(struct Harpuia* p);
static void Z2Harpuia_Die(struct Harpuia* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static void createWave(Coords32* c, u8 kind, bool8 right);
static void createThunder(struct Harpuia* p, u8 kind, u8 n);
static void createBlade(struct Harpuia* p, bool8 right);
static struct Entity* createCharge(struct Harpuia* p);

// clang-format off
const BossRoutine gApZ2HarpuiaRoutine = {
    [ENTITY_INIT] =      (BossFunc)Z2Harpuia_Init,
    [ENTITY_UPDATE] =    (BossFunc)Z2Harpuia_Update,
    [ENTITY_DIE] =       (BossFunc)Z2Harpuia_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Harpuia* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void faceZero(struct Harpuia* p) { SET_XFLIP(p, (p->s).coord.x < (pZero2->s).coord.x); }

static void turnAround(struct Harpuia* p) { SET_XFLIP(p, !FACING_RIGHT(p)); }

static bool8 zeroHeld(struct Zero* z) {
  return z != NULL && !((z->body).status & BODY_STATUS_DEAD) && (z->body).hp != 0;
}

// While grabbed, Zero hangs at his feet facing him (0x0802311c in Zero 2)
static struct Zero* carryZero(struct Harpuia* p, s32 dy, bool8 upsideDown) {
  struct Entity* s = &p->s;
  struct Zero* z;
  if (!((p->body).status & BODY_STATUS_BINDING)) return NULL;
  z = (struct Zero*)((p->body).bindPair)->parent;
  if ((z->s).kind != ENTITY_PLAYER || !zeroHeld(z)) return NULL;
  (z->s).coord.x = s->coord.x + (FACING_RIGHT(p) ? PIXEL(14) : -PIXEL(14));
  (z->s).coord.y = s->coord.y + dy;
  SET_XFLIP(z, !FACING_RIGHT(p));
  SET_YFLIP(z, upsideDown);
  return z;
}

static const struct PreloadEntity sSheets[2] = {
    {AP_SHEET_Z2_HARPUIA_SHOTS, 0, 574, 6, 0, AP_PRELOAD_SHEET, 0},
    {AP_SHEET_Z2_HARPUIA_BLADE, 0, 574 + AP_SHEET_Z2_HARPUIA_SHOTS_TILES, 7, 0, AP_PRELOAD_SHEET, 0},
};

// 0x0804a9ec
static void Z2Harpuia_Init(struct Harpuia* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sSheets[0]);
  ApLoadSheet(&sSheets[1]);
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetSpriteAnimation(p, HARPUIA(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  ResetBossBody((struct Boss*)p, HB_INTRO, 64);
  (p->body).fn = onCollision;
  p->left = s->coord.x;
  p->right = s->coord.x + PIXEL(240);
  s->coord.x = p->left + PIXEL(208);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->hoverY = s->coord.y - PIXEL(64);
  p->pattern = 0;
  s->unk_2c = NULL;
  p->zero = NULL;
  p->sound = 0xFFFF;
  p->exUsed = 0;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Z2Harpuia_Update(p);
}

static void keepInArena(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->coord.x < p->left + PIXEL(24)) s->coord.x = p->left + PIXEL(24);
  if (s->coord.x > p->right - PIXEL(24)) s->coord.x = p->right - PIXEL(24);
}

// 0x0804aea8
static void checkHit(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (!((p->body).status & BODY_STATUS_WHITE)) return;
  if (s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(13, (Object*)p, &sElementCoord);
    if (s->unk_2c == NULL && (s->mode[1] == 16 || s->mode[1] == 17 || s->mode[1] > 30)) return;
  }
  setMode(p, 16);
}

static const BossFunc sUpdates[40];

// 0x0804ab60
static void Z2Harpuia_Update(struct Harpuia* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Z2Harpuia_Die(p);
    return;
  }
  checkHit(p);
  (sUpdates[(p->s).mode[1]])((struct Boss*)p);
  keepInArena(p);
}

// 0x0804aef8
static void Z2Harpuia_Appear(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->work[0] != 0) {
      s->mode[3] = 4;
    } else {
      InitScalerotMotion1(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, HARPUIA(0));
      PaintEntityWhite(s);
      (s->spr).mag.x = 48;
      (s->spr).mag.y = 384;
      s->coord.y -= PIXEL(240);
      s->work[2] = 16;
      s->mode[3] = 0;
    }
    s->mode[2]++;
  }
  switch (s->mode[3]) {
    case 0:
      UpdateSpriteAnimation(p);
      s->coord.y += PIXEL(8);
      if (FUN_080098a4(s->coord.x, s->coord.y)) {
        PlaySound(SND_TELEPORT);
        s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
        s->mode[3]++;
      }
      break;
    case 1:
      UpdateSpriteAnimation(p);
      if ((s->spr).mag.y > 256) {
        (s->spr).mag.y -= 64;
      } else {
        s->mode[3]++;
      }
      break;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->spr).mag.x < 256) {
        (s->spr).mag.x += 64;
      } else {
        (s->spr).mag.x = 256;
        s->mode[3]++;
      }
      break;
    case 3:
      InitNonAffineMotion(s);
      s->flags |= DISPLAY | FLIPABLE;
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, HARPUIA(0));
      UpdateEntityPaletteID(s);
      s->mode[3]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      if (s->scriptEntity->flags & 1) setMode(p, 1);
      break;
  }
}

// 0x0804b038
static void Z2Harpuia_Pose(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(1));
    SetDDP(&p->body, HB_BODY);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] == 0 && (s->motion).cmdIdx == 4) {
    PlaySound(SND_WHOOSH);
    s->mode[3]++;
  }
  if (!(gStageRun.vm.active & VM_ACTIVE)) {
    setMode(p, 5);
    s->mode[3] = 6;
  }
}

static void Z2Harpuia_Nothing(struct Harpuia* p UNUSED) {}

// 0x0804b0ac: picks the next attack, or his EX at rank A and above
static void Z2Harpuia_Choose(struct Harpuia* p) {
  static const u8 sAttacks[5] = {7, 11, 13, 18, 26};
  struct Entity* s = &p->s;
  u8 n;
  faceZero(p);
  if (s->mode[2] == 0 && (gStageRun.vm.active & VM_ACTIVE)) {
    SetSpriteAnimation(p, HARPUIA(3));
    UpdateSpriteAnimation(p);
    return;
  }
  UpdateSpriteAnimation(p);
  if (gScore.total->rank > 4 &&
      ((p->exUsed == 0 && (p->body).hp <= 32) || (p->exUsed == 1 && (p->body).hp <= 16))) {
    setMode(p, 26);
    p->exUsed++;
    return;
  }
  n = (p->pattern & 1) ? (RANDOM(RNG_0202f388) & 3) : (p->pattern >> 1);
  if (n <= 4) s->mode[1] = sAttacks[n];
  s->mode[2] = 0;
  p->pattern = (p->pattern + 1) % 8;
}

// 0x0804b208
static void Z2Harpuia_Hover(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(3));
    SetDDP(&p->body, HB_BODY);
    faceZero(p);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(p, 3);
}

// 0x0804b2a4
static void Z2Harpuia_Flourish(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(2));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(p, s->mode[3]);
}

// 0x0804b2e0
static void Z2Harpuia_Rise(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(3));
    (s->d).y = -PIXEL(6);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  if (s->coord.y <= p->hoverY) {
    s->coord.y = p->hoverY;
    setMode(p, 3);
  }
}

// 0x0804b330
static void Z2Harpuia_DashHop(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(4));
    faceZero(p);
    (s->d).x = ((s->coord.x < (pZero2->s).coord.x ? p->right : p->left) - s->coord.x) >> 9;
    (s->d).y = -0x540;
    s->work[2] = 35;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  if (--s->work[2] == 0xFF) setMode(p, 8);
}

// 0x0804b404
static void Z2Harpuia_DashWindUp(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(5));
    (s->d).x = ((FACING_RIGHT(p) ? p->right : p->left) - s->coord.x) / 39;
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if (--s->work[2] == 0xFF) setMode(p, 9);
}

// 0x0804b47c
static void Z2Harpuia_Dash(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(6));
    createWave(&s->coord, 0, FACING_RIGHT(p));
    PlaySound(SND_SLASH);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if (s->coord.y <= p->hoverY - PIXEL(32)) setMode(p, 10);
}

// 0x0804b4ec
static void Z2Harpuia_Settle(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(3));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  faceZero(p);
  (s->d).y += 64;
  s->coord.y += (s->d).y;
  if (s->coord.y >= p->hoverY) {
    s->coord.y = p->hoverY;
    s->mode[1] = 4, s->mode[2] = 1;
    s->work[2] = 1;
  }
}
// 0x0804b694
static void throwBlades(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) {
      if (s->work[3] != 0) {
        setMode(p, 12);
        s->work[3]--;
      } else {
        setMode(p, 4);
        s->work[2] = 1;
      }
    }
  } else if (IsSpriteAnimEnd(p)) {
    createBlade(p, FACING_RIGHT(p));
    PlaySound(SE_Z2_HARPUIA_BLADES);
    s->mode[3] = 1;
    s->work[2] = 32;
  }
}

// 0x0804b588
static void Z2Harpuia_Blades(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(11));
    faceZero(p);
    s->work[3] = 2;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  throwBlades(p);
}

// 0x0804b610
static void Z2Harpuia_NextBlade(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(11));
    faceZero(p);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  throwBlades(p);
}

// 0x0804b6f8
static void Z2Harpuia_Summon(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(17));
    p->sound = PlaySound(SE_Z2_HARPUIA_HUM);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) setMode(p, 14);
}

// 0x0804b740
static void Z2Harpuia_Thunder(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(18));
    p->orbsDone = FALSE;
    createThunder(p, 0, 0);
    createThunder(p, 0, 1);
    createThunder(p, 0, 2);
    s->work[2] = 192;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->mode[3] != 0) {
    if (--s->work[2] == 0xFF) setMode(p, 15);
    return;
  }
  if (s->work[2] % 48 == 0) {
    createThunder(p, 1, 0);
    createThunder(p, 1, 1);
    createThunder(p, 1, 2);
    PlaySound(SE_Z2_HARPUIA_THUNDER);
  }
  if (--s->work[2] == 0xFF) {
    s->work[2] = 64;
    s->mode[3]++;
  }
}

// 0x0804b7f8
static void Z2Harpuia_EndThunder(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(19));
    StopSound(p->sound);
    p->sound = 0xFFFF;
    p->orbsDone = TRUE;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (IsSpriteAnimEnd(p)) {
    setMode(p, 4);
    s->work[2] = 32;
  }
}

// 0x0804b854
static void Z2Harpuia_Knockback(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(12));
    SetDDP(&p->body, HB_BODY);
    (s->d).x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    (s->d).y = -PIXEL(3);
    if (s->flags & Y_FLIP) {
      s->coord.y += 0x3500;
      SET_YFLIP(p, FALSE);
    }
    p->orbsDone = TRUE;
    (s->spr).oam.priority = 2;
    StopSound(p->sound);
    p->sound = 0xFFFF;
    PlaySound(SND_HURT);
    s->work[3] = (s->unk_2c != NULL) ? 3 : 2;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  if (FUN_080098a4(s->coord.x, s->coord.y)) {
    s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    setMode(p, 17);
  }
}

// 0x0804b960
static void Z2Harpuia_Down(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(13));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->unk_2c != NULL) {
    if (IsDead(s->unk_2c)) s->unk_2c = NULL;
    if (s->unk_2c != NULL) return;
  }
  if (gStageRun.vm.active & VM_ACTIVE) {
    setMode(p, 3);
    return;
  }
  if (IsSpriteAnimEnd(p)) {
    u8 n = RANDOM(RNG_0202f388) % s->work[3];
    if (n == 0) {
      s->mode[1] = 31;
    } else if (n == 1) {
      s->mode[1] = 37;
    } else {
      s->mode[1] = 5;
      s->mode[3] = 6;
    }
    s->mode[2] = 0;
  }
}

// 0x0804ba10
static void Z2Harpuia_DiveHop(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(4));
    faceZero(p);
    (s->d).x = ((pZero2->s).coord.x - s->coord.x) / 64;
    (s->d).y = -0x540;
    s->work[2] = 42;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  if (--s->work[2] == 0xFF) setMode(p, 19);
}

// 0x0804bad8
static void Z2Harpuia_Dive(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(7));
    SetDDP(&p->body, HB_DIVE);
    s->work[2] = 40;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if ((p->body).status & BODY_STATUS_BINDING) {
    SetDDP(&p->body, HB_HOLD);
    setMode(p, 21);
  } else if (--s->work[2] == 0xFF) {
    SetDDP(&p->body, HB_BODY);
    setMode(p, 20);
  }
}

// 0x0804bb70:
static void Z2Harpuia_DiveMiss(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(3));
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  if (s->coord.y <= p->hoverY) {
    s->coord.y = p->hoverY;
    setMode(p, 4);
    s->work[2] = 1;
  }
}

// 0x0804bbc4
static void Z2Harpuia_Carry(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    PlaySound(SE_Z2_HARPUIA_GRAB);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  carryZero(p, -PIXEL(8), FALSE);
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if (s->coord.y < p->hoverY - PIXEL(32)) setMode(p, 22);
}

// 0x0804bc88
static void Z2Harpuia_CarryTop(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateSpriteAnimation(p);
  s->coord.y += (s->d).y;
  (s->d).y += 64;
  carryZero(p, -PIXEL(8), FALSE);
  if ((s->d).y > 0) setMode(p, 23);
}

// 0x0804bd38
static void Z2Harpuia_CarryTurn(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateSpriteAnimation(p);
  carryZero(p, -PIXEL(8), FALSE);
  setMode(p, 24);
}

// 0x0804bdd4:
static void Z2Harpuia_Slam(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(8));
    SET_YFLIP(p, TRUE);
    s->coord.y -= 0x3500;
    s->work[2] = 0;
    PlaySound(SE_Z2_HARPUIA_SLAM);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  {
    struct Zero* z = carryZero(p, PIXEL(12), TRUE);
    if (z != NULL) p->zero = z;
  }
  if ((s->d).y < 0x380) (s->d).y += 64;
  s->coord.y += (s->d).y;
  if (FUN_080098a4(s->coord.x, s->coord.y + PIXEL(60))) {
    struct Zero* z = p->zero;
    if (zeroHeld(z)) {
      SET_YFLIP(z, FALSE);
      (z->s).coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
    }
    SetDDP(&p->body, HB_SLAM);
    setMode(p, 25);
    PlaySound(SE_Z2_HARPUIA_IMPACT);
    AppendQuake(4, &s->coord);
  }
}

// 0x0804bf40:
static void Z2Harpuia_Release(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(9));
    SetDDP(&p->body, HB_BODY);
    SET_YFLIP(p, FALSE);
    s->coord.y += 0x3500;
    s->work[2] = 24;
    (s->d).y = PIXEL(2);
    turnAround(p);
    (s->d).x = FACING_RIGHT(p) ? 0x180 : -0x180;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (s->d).y -= 64;
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  if (--s->work[2] == 0xFF) setMode(p, 20);
}

// 0x0804c07c
static void Z2Harpuia_ExCharge(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(10));
    SetDDP(&p->body, HB_DASH);
    SET_XFLIP(p, s->coord.x < p->left + PIXEL(120));
    s->unk_28 = createCharge(p);
    PlaySound(SE_Z2_HARPUIA_EX);
    p->exPass = 0;
    s->work[2] = 64;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.y -= 160;
  if (--s->work[2] == 0xFF) setMode(p, 27);
}

// 0x0804c144
static void Z2Harpuia_ExTurn(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(20));
    (s->d).x = (s->d).y = 0;
    SetDDP(&p->body, HB_BODY);
    if (s->unk_28 != NULL) {
      s->unk_28->work[1] = 1;
      s->unk_28 = NULL;
    }
    if (p->exPass != 0) turnAround(p);
    (s->unk_coord).x = FACING_RIGHT(p) ? 128 : -128;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (s->d).x += (s->unk_coord).x;
  (s->d).y += 128;
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  if (IsSpriteAnimEnd(p)) setMode(p, 28);
}

// 0x0804c214
static void Z2Harpuia_ExDash(struct Harpuia* p) {
  struct Entity* s = &p->s;
  Coords32 c;
  if (s->mode[2] == 0) {
    p->trailX = s->coord.x;
    SetDDP(&p->body, HB_DASH);
    (s->d).x = (p->exPass << 8) + PIXEL(8);
    if (!FACING_RIGHT(p)) (s->d).x = -(s->d).x;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->mode[3] == 0) {
    s->coord.x += (s->d).x;
    if (FACING_RIGHT(p)) {
      if (s->coord.x <= p->right - PIXEL(120)) return;
      c.x = (p->exPass == 0) ? p->left + PIXEL(120) : p->left + PIXEL(76);
    } else {
      if (s->coord.x >= p->left + PIXEL(120)) return;
      c.x = (p->exPass == 0) ? p->right - PIXEL(120) : p->right - PIXEL(76);
    }
    c.y = s->coord.y - PIXEL(8);
    createWave(&c, 5, FACING_RIGHT(p));
    PlaySound(SND_SLASH);
    s->mode[3]++;
  } else if (s->mode[3] == 1) {
    bool8 stop = FALSE;
    s->coord.x += (s->d).x;
    if (FACING_RIGHT(p)) {
      if (s->coord.x > p->right - PIXEL(32)) {
        s->coord.x = p->right - PIXEL(32);
        stop = TRUE;
      }
    } else if (s->coord.x < p->left + PIXEL(32)) {
      s->coord.x = p->left + PIXEL(32);
      stop = TRUE;
    }
    if (stop) {
      p->trailStep = (p->trailX - s->coord.x) / 8;
      s->work[2] = 7;
      s->mode[3]++;
    }
  } else {
    p->trailX -= p->trailStep;
    if (--s->work[2] == 0) setMode(p, 29);
  }
}

// 0x0804c3f4
static void Z2Harpuia_ExStop(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    InitNonAffineMotion(s);
    ResetDynamicMotion(s);
    SetSpriteAnimation(p, HARPUIA(6));
    SET_XFLIP(p, (s->d).x > 0);
    SetDDP(&p->body, HB_BODY);
    p->exPass++;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  if ((s->d).y != 0) {
    s->coord.y -= (s->d).y;
    (s->d).y -= 128;
  }
  if (IsSpriteAnimEnd(p)) {
    if (gStageRun.vm.active & VM_ACTIVE) {
      setMode(p, 3);
    } else {
      setMode(p, p->exPass < 8 ? 27 : 30);
    }
  }
}

// 0x0804c504
static void Z2Harpuia_ExEnd(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(3));
    (s->d).y = 0x4C0;
    turnAround(p);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  (s->d).y -= 64;
  s->coord.y += (s->d).y;
  if (s->coord.y > p->hoverY) {
    s->coord.y = p->hoverY;
    setMode(p, 4);
    s->work[2] = 1;
  }
}

// --------------------------------------------
// Counters from the floor

static void slash(struct Harpuia* p, u8 anim, u8 next, u8 at, u8 kind) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(anim));
    if (anim == 22) faceZero(p);
    s->work[2] = 0;
    PlaySound(anim == 24 ? SND_SLASH : SE_Z2_HARPUIA_COMBO);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (++s->work[2] == at) createWave(&s->coord, kind, FACING_RIGHT(p));
  if (IsSpriteAnimEnd(p)) setMode(p, next);
}

// 0x0804c59c, 0x0804c650, 0x0804c6b0
static void Z2Harpuia_Slash1(struct Harpuia* p) { slash(p, 22, 32, 16, 1); }
static void Z2Harpuia_Slash2(struct Harpuia* p) { slash(p, 23, 33, 12, 2); }
static void Z2Harpuia_Slash3(struct Harpuia* p) { slash(p, 24, 34, 11, 3); }

// 0x0804c710
static void Z2Harpuia_SlashEnd(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(25));
    s->work[2] = 8;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) {
    if (RANDOM(RNG_0202f388) & 1) {
      s->mode[1] = 37;
    } else {
      s->mode[1] = 35;
    }
    s->mode[2] = 0;
  }
}

// 0x0804c790
static void Z2Harpuia_Leap(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(9));
    faceZero(p);
    (s->d).x = FACING_RIGHT(p) ? PIXEL(2) : -PIXEL(2);
    (s->d).y = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if ((s->d).y < -PIXEL(4)) setMode(p, 36);
}

// 0x0804c84c
static void Z2Harpuia_LeapSlash(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(6));
    createWave(&s->coord, 4, FACING_RIGHT(p));
    PlaySound(SND_SLASH);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  (s->d).y -= 64;
  if (s->coord.y < p->hoverY) setMode(p, 10);
}

// 0x0804c8b4
static void Z2Harpuia_Crouch(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(15));
    faceZero(p);
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) setMode(p, 38);
}

// 0x0804c948
static void Z2Harpuia_Lunge(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    p->trailX = s->coord.x;
    SetDDP(&p->body, HB_DASH);
    (s->d).x = FACING_RIGHT(p) ? PIXEL(8) : -PIXEL(8);
    s->work[2] = 16;
    PlaySound(SND_WHOOSH);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  if (s->mode[3] != 0) {
    p->trailX -= p->trailStep;
    if (--s->work[2] == 0) setMode(p, 39);
    return;
  }
  {
    bool8 past;
    s->coord.x += (s->d).x;
    past = FACING_RIGHT(p) ? s->coord.x > (pZero2->s).coord.x : s->coord.x < (pZero2->s).coord.x;
    if (--s->work[2] == 0xFF) past = TRUE;
    if (past) {
      p->trailStep = (p->trailX - s->coord.x) / 8;
      s->work[2] = 7;
      s->mode[3]++;
    }
  }
}

// 0x0804cac4
static void Z2Harpuia_RisingSlash(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    InitNonAffineMotion(s);
    ResetDynamicMotion(s);
    SetSpriteAnimation(p, HARPUIA(16));
    SET_XFLIP(p, (s->d).x > 0);
    s->work[2] = 17;
    s->mode[3] = 0;
    PlaySound(SND_SLASH);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  SetDDP(&p->body, &sCollisions[sSlashCollisions[(s->motion).cmdIdx]]);
  switch (s->mode[3]) {
    case 0:
      if (--s->work[2] == 0xFF) s->mode[3]++;
      break;
    case 1:
      s->coord.y -= PIXEL(6);
      s->mode[3]++;
      break;
    case 2:
      s->coord.y -= PIXEL(19);
      (s->d).y = -PIXEL(5);
      s->mode[3]++;
      break;
    case 3:
      s->coord.y += (s->d).y;
      (s->d).y += 64;
      if ((s->d).y > 0 && s->coord.y >= p->hoverY) {
        s->coord.y = p->hoverY;
        setMode(p, 4);
        s->work[2] = 1;
      }
      break;
  }
}

static const BossFunc sUpdates[40] = {
    (BossFunc)Z2Harpuia_Appear,     (BossFunc)Z2Harpuia_Pose,       (BossFunc)Z2Harpuia_Nothing,
    (BossFunc)Z2Harpuia_Choose,     (BossFunc)Z2Harpuia_Hover,      (BossFunc)Z2Harpuia_Flourish,
    (BossFunc)Z2Harpuia_Rise,       (BossFunc)Z2Harpuia_DashHop,    (BossFunc)Z2Harpuia_DashWindUp,
    (BossFunc)Z2Harpuia_Dash,       (BossFunc)Z2Harpuia_Settle,     (BossFunc)Z2Harpuia_Blades,
    (BossFunc)Z2Harpuia_NextBlade,  (BossFunc)Z2Harpuia_Summon,     (BossFunc)Z2Harpuia_Thunder,
    (BossFunc)Z2Harpuia_EndThunder, (BossFunc)Z2Harpuia_Knockback,  (BossFunc)Z2Harpuia_Down,
    (BossFunc)Z2Harpuia_DiveHop,    (BossFunc)Z2Harpuia_Dive,       (BossFunc)Z2Harpuia_DiveMiss,
    (BossFunc)Z2Harpuia_Carry,      (BossFunc)Z2Harpuia_CarryTop,   (BossFunc)Z2Harpuia_CarryTurn,
    (BossFunc)Z2Harpuia_Slam,       (BossFunc)Z2Harpuia_Release,    (BossFunc)Z2Harpuia_ExCharge,
    (BossFunc)Z2Harpuia_ExTurn,     (BossFunc)Z2Harpuia_ExDash,     (BossFunc)Z2Harpuia_ExStop,
    (BossFunc)Z2Harpuia_ExEnd,      (BossFunc)Z2Harpuia_Slash1,     (BossFunc)Z2Harpuia_Slash2,
    (BossFunc)Z2Harpuia_Slash3,     (BossFunc)Z2Harpuia_SlashEnd,   (BossFunc)Z2Harpuia_Leap,
    (BossFunc)Z2Harpuia_LeapSlash,  (BossFunc)Z2Harpuia_Crouch,     (BossFunc)Z2Harpuia_Lunge,
    (BossFunc)Z2Harpuia_RisingSlash,
};

// 0x0804abf4
static void Z2Harpuia_Die(struct Harpuia* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, HARPUIA(12));
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    s->flags &= ~COLLIDABLE;
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    s->work[2] = 0;
    if (s->flags & Y_FLIP) s->coord.y += 0x3500;
    SET_YFLIP(p, FALSE);
    (s->d).x = p->hitFromRight ? -PIXEL(1) : PIXEL(1);
    (s->d).y = -PIXEL(3);
    StopSound(p->sound);
    p->sound = 0xFFFF;
    p->orbsDone = TRUE;
    (s->spr).oam.priority = 2;
    s->mode[2]++;
  }
  switch (s->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      s->coord.x += (s->d).x;
      s->coord.y += (s->d).y;
      (s->d).y += 64;
      if (FUN_080098a4(s->coord.x, s->coord.y)) {
        s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
        s->mode[1]++;
      }
      break;
    case 1:
      SetSpriteAnimation(p, HARPUIA(14));
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[1]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if (s->scriptEntity->flags & 0x80) s->mode[1]++;
      break;
    case 4: {
      bool8 right = FACING_RIGHT(p);
      InitScalerotMotion1(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, HARPUIA(14));
      SET_XFLIP(p, right);
      PaintEntityWhite(s);
      (s->spr).mag.x = (s->spr).mag.y = 256;
      PlaySound(SND_TELEPORT);
      s->mode[1]++;
    }
      FALLTHROUGH;
    case 5:
      UpdateSpriteAnimation(p);
      (s->spr).mag.x -= 64;
      if ((s->spr).mag.x < 64) {
        (s->spr).mag.x = 4;
        s->mode[1]++;
      }
      break;
    case 6:
      UpdateSpriteAnimation(p);
      (s->spr).mag.y -= 16;
      if ((s->spr).mag.y <= 128) s->mode[1]++;
      break;
    case 7:
      UpdateSpriteAnimation(p);
      s->coord.y -= PIXEL(8);
      if ((s->spr).mag.y < 0x200) (s->spr).mag.y += 32;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > PIXEL(8)) {
        s->flags &= ~DISPLAY;
        gStageRun.vm.active |= VM_FLAG1;
      }
      break;
  }
  keepInArena(p);
}

// 0x0804cc98
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Entity* other = body->enemy->parent;
  struct Harpuia* p = (struct Harpuia*)body->parent;
  if ((body->hitboxFlags & BODY_STATUS_B2) && other->kind == ENTITY_PLAYER) p->zero = (struct Zero*)other;
  if (body->hitboxFlags & BODY_STATUS_WHITE) p->hitFromRight = other->coord.x > (p->s).coord.x;
}

static struct Entity* createCharge(struct Harpuia* p UNUSED) { return NULL; }

static void useApSheets(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

#define SHOTS(n) MOTION(AP_SHEET_Z2_HARPUIA_SHOTS, (n))
#define BLADE(n) MOTION(AP_SHEET_Z2_HARPUIA_BLADE, (n))

// --------------------------------------------
// Zero 2 projectile 20:
//   0: dash wave, angled down
//   1..3: combo slashes
//   4: leap slash
//   5: EX wave, falling

static const struct Collision sWaveCollisions[6];

static void Wave_Init(struct Projectile* p);
static void Wave_Update(struct Projectile* p);
static void Wave_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2HarpuiaWaveRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Wave_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Wave_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Wave_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809da88
static void createWave(Coords32* c, u8 kind, bool8 right) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_HARPUIA_WAVE);
    p->coord = *c;
    p->work[0] = kind;
    p->work[1] = right;
  }
}

static const struct {
  u8 anim;
  s16 ahead, up, dx, dy;
} sWaves[6] = {
    {0, 0, 0x1000, 0x100, 0x380},
    {1, 0x1000, 0x1400, 0x400, 0},
    {2, 0x1000, 0x1800, 0x380, -0x100},
    {2, 0x1000, 0x1500, 0x400, 0},
    {0, 0, 0x1000, 0x400, 0x200},
    {11, 0, 0, 0, 0x200},
};

static void Wave_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  u8 kind = s->work[0];
  bool8 right = kind != 5 && s->work[1];
  if (kind == 0) {
    InitRotatableMotion(s);
  } else {
    InitNonAffineMotion(s);
  }
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetSpriteAnimation(p, SHOTS(sWaves[kind].anim));
  UpdateSpriteAnimation(p);
  INIT_BODY(p, &sWaveCollisions[kind], 1, NULL);
  SET_XFLIP(p, right);
  if (kind == 0) s->angle = 0xE2;
  s->coord.x += right ? sWaves[kind].ahead : -sWaves[kind].ahead;
  s->coord.y -= sWaves[kind].up;
  (s->d).x = right ? sWaves[kind].dx : -sWaves[kind].dx;
  (s->d).y = sWaves[kind].dy;
  s->work[2] = 128;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Wave_Update(p);
}

static void Wave_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// 0x0809daf4
static void Wave_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (s->work[2] & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
  s->coord.x += (s->d).x;
  s->coord.y += (s->d).y;
  if (--s->work[2] == 0xFF) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Wave_Die(p);
  }
}

// --------------------------------------------
// Thunder, Zero 2 projectile 21. 
//   0: the three orbs above him. Only the lowest one hurts
//   1: three markers that drop at Zero. The first one calls the bolt down where it lands
//   2: six segments of the bolt
//   3: the bolt's strike on the floor

#define THUNDER_FLOOR_Y(p) (((s32*)(p)->buffer)[1])  // Zero 2 keeps it at 0xB8

static const struct Collision sOrbCollisions[1];
static const struct Collision sStrikeCollisions[2];

static void Thunder_Init(struct Projectile* p);
static void Thunder_Update(struct Projectile* p);
static void Thunder_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gApZ2HarpuiaThunderRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Thunder_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Thunder_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Thunder_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

enum { ORB, MARKER, SEGMENT, STRIKE };

static struct Harpuia* harpuiaOf(struct Entity* s) { return (struct Harpuia*)s->unk_28; }

// 0x0809e05c, 0x0809e0ac
static void createThunderAt(struct Harpuia* parent, Coords32* c, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_HARPUIA_THUNDER);
    p->unk_28 = &parent->s;
    if (c != NULL) p->coord = *c;
    p->work[0] = kind;
    p->work[1] = n;
  }
}

static void createThunder(struct Harpuia* p, u8 kind, u8 n) { createThunderAt(p, NULL, kind, n); }

static void Thunder_Die(struct Projectile* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

static void killThunder(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  Thunder_Die(p);
}

// 0x0809e14c, 0x0809e1e0, 0x0809e27c, 0x0809e2fc
static void Thunder_Init(struct Projectile* p) {
  struct Entity* s = &p->s;
  u8 n = s->work[1];
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  switch (s->work[0]) {
    case ORB:
      SetSpriteAnimation(p, SHOTS(4));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      if (n == 0) INIT_BODY(p, sOrbCollisions, 1, NULL);
      s->work[2] = 0;
      break;
    case MARKER:
      SetSpriteAnimation(p, SHOTS(10));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, n & 1);
      s->coord = (pZero2->s).coord;
      THUNDER_FLOOR_Y(p) = FUN_08009f6c(s->coord.x, s->coord.y);
      s->work[2] = 24;
      break;
    case SEGMENT:
      SetSpriteAnimation(p, SHOTS(4));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      s->coord.y += PIXEL(16) - (n << 13);
      s->work[2] = 32;
      break;
    case STRIKE:
      SetSpriteAnimation(p, SHOTS(8));
      UpdateSpriteAnimation(p);
      SET_XFLIP(p, FALSE);
      INIT_BODY(p, sStrikeCollisions, 1, NULL);
      s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
      s->work[2] = 32;
      break;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Thunder_Update(p);
}

// 0x0809e398, 0x0809e424, 0x0809e520, 0x0809e580
static void Thunder_Update(struct Projectile* p) {
  struct Entity* s = &p->s;
  struct Harpuia* h = harpuiaOf(s);
  u8 n = s->work[1];
  switch (s->work[0]) {
    case ORB:
      if (h->orbsDone) {
        killThunder(p);
        return;
      }
      SetSpriteAnimation(p, SHOTS(4 + s->work[2]));
      UpdateSpriteAnimation(p);
      s->coord.x = (h->s).coord.x + (FACING_RIGHT(h) ? -PIXEL(5) : PIXEL(5));
      s->coord.y = (h->s).coord.y - ((n << 13) + 0x5600);
      s->work[2] = (s->work[2] + 1) & 3;
      break;
    case MARKER:
      if (h->orbsDone) {
        killThunder(p);
        return;
      }
      UpdateSpriteAnimation(p);
      if (s->work[2] & 1) {
        s->flags |= DISPLAY;
      } else {
        s->flags &= ~DISPLAY;
      }
      if (s->mode[1] != 0) {
        if (--s->work[2] != 0xFF) return;
        if (n == 0) {
          u8 i;
          for (i = 0; i < 6; i++) createThunderAt(h, &s->coord, SEGMENT, i);
          createThunderAt(h, &s->coord, STRIKE, 0);
        }
        killThunder(p);
        return;
      }
      s->coord.y = THUNDER_FLOOR_Y(p) - ((n << 14) + PIXEL(32)) - s->work[2] * 0xC00;
      if (--s->work[2] == 0xFF) {
        s->work[2] = 4;
        s->mode[1]++;
      }
      break;
    case SEGMENT:
      SetSpriteAnimation(p, SHOTS(4 + ((s->work[2] + SEGMENT) & 3)));
      UpdateSpriteAnimation(p);
      if (h->orbsDone || --s->work[2] == 0xFF) killThunder(p);
      break;
    case STRIKE:
      UpdateSpriteAnimation(p);
      if (h->orbsDone || --s->work[2] == 0xFF) killThunder(p);
      break;
  }
}

// --------------------------------------------
// Blades, Zero 2 enemy 26

static const struct Collision sBladeCollisions[2];
static const struct Collision sBladeStopCollisions[2];
static const struct Collision sSparkCollisions[1];

static void Blade_Init(struct Enemy* p);
static void Blade_Update(struct Enemy* p);
static void Blade_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2HarpuiaBladeRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Blade_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Blade_Update,
    [ENTITY_DIE] =       (EnemyFunc)Blade_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

#define BLADE_ANGLE(s) ((s)->work[3])
#define BLADE_SPEED(s) ((s)->d.x)
#define BLADE_FLIGHTS(s) ((s)->d.y)

// 0x080749fc
static void createBladeOf(struct Entity* parent, u8 kind, bool8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_HARPUIA_BLADE);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = right;
  }
}

static void createBlade(struct Harpuia* p, bool8 right) { createBladeOf(&p->s, 0, right); }

// 0x08074aac, 0x08074b6c
static void Blade_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    struct Entity* h = s->unk_28;
    InitRotatableMotion(s);
    useApSheets(p);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, BLADE(0));
    UpdateSpriteAnimation(p);
    SET_XFLIP(p, FALSE);
    s->coord.x = h->coord.x;
    s->coord.y = h->coord.y - PIXEL(30);
    BLADE_FLIGHTS(s) = 2;
    BLADE_ANGLE(s) = s->work[1] ? 212 : 44;
    INIT_BODY(p, sBladeCollisions, 8, NULL);
    s->angle = BLADE_ANGLE(s);
    BLADE_SPEED(s) = PIXEL(2);
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
    s->mode[2] = 1;
  } else {
    InitScalerotMotion2(s);
    useApSheets(p);
    s->flags |= DISPLAY | FLIPABLE;
    SetSpriteAnimation(p, SHOTS(9));
    UpdateSpriteAnimation(p);
    SET_XFLIP(p, FALSE);
    s->angle = 0;
    (s->spr).mag.x = (s->spr).mag.y = 1;
    s->work[2] = 8;
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  }
  Blade_Update(p);
}

// 0x08074db4, 0x08074dfc
static void Blade_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    CreateSmoke(1, &s->coord);
    PlaySound(SE_ZAKO_EXPLODE);
  } else {
    s->flags &= ~DISPLAY;
  }
  (p->body).status = (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  s->flags &= ~COLLIDABLE;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static void killBlade(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Blade_Die(p);
}

static void fly(struct Entity* s) {
  s->coord.x += Sin(BLADE_ANGLE(s) + 128, BLADE_SPEED(s));
  s->coord.y += Sin(BLADE_ANGLE(s) + 64, BLADE_SPEED(s));
}

// 0x08074e38
static void Blade_Fly(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s32 dx = ((pZero2->s).coord.x - s->coord.x) >> 12;
    s32 dy = ((pZero2->s).coord.y - s->coord.y - PIXEL(16)) >> 12;
    BLADE_ANGLE(s) = (u16)(ArcTan2(dx, dy) + 0xC000) >> 8;
    s->angle = BLADE_ANGLE(s);
    BLADE_SPEED(s) = PIXEL(3);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  fly(s);
  BLADE_SPEED(s) -= 16;
  if (BLADE_SPEED(s) <= 0) {
    s->mode[1]++;
    s->mode[2] = 0;
  }
}

// 0x08074ef4
static void Blade_Stop(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    createBladeOf(s, 1, FALSE);
    SetDDP(&p->body, sBladeStopCollisions);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (--s->work[2] == 0xFF) {
    s->mode[1]++;
    s->mode[2] = 0;
  }
}

// 0x08074f44
static void Blade_Again(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sBladeCollisions);
    s->work[2] = 32;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->mode[1] = (BLADE_FLIGHTS(s)-- == 0) ? s->mode[1] + 1 : 0;
  s->mode[2] = 0;
}

// 0x08074f90
static void Blade_Leave(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    (s->d).y = PIXEL(3);
    s->angle = 128;
    s->work[2] = 255;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.y -= (s->d).y;
  if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x08074fec
static void Blade_FlyOff(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    if (s->coord.x < s->unk_28->coord.x) {
      (s->d).x = -PIXEL(3);
      s->angle = 64;
    } else {
      (s->d).x = PIXEL(3);
      s->angle = 192;
    }
    s->work[2] = 255;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  s->coord.x += (s->d).x;
  if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

static const EnemyFunc sBladeUpdates[5] = {
    (EnemyFunc)Blade_Fly, (EnemyFunc)Blade_Stop, (EnemyFunc)Blade_Again, (EnemyFunc)Blade_Leave, (EnemyFunc)Blade_FlyOff,
};

// 0x08074c48
static void Spark_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* blade = s->unk_28;
  if (blade->mode[0] > ENTITY_UPDATE) {
    killBlade(p);
    return;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = blade->coord.x + (SIN(BLADE_ANGLE(blade) + 128) << 3);
  s->coord.y = blade->coord.y + (SIN(BLADE_ANGLE(blade) + 64) << 3);
  if (blade->mode[1] == 4) s->mode[1] = 2;
  switch (s->mode[1]) {
    case 0:
      (s->spr).mag.x = (s->spr).mag.y = 256 - s->work[2] * 16;
      if (--s->work[2] == 0xFF) {
        INIT_BODY(p, sSparkCollisions, 1, NULL);
        s->mode[1]++;
        s->work[2] = 16;
      }
      break;
    case 1:
      (s->spr).mag.x = (s->spr).mag.y = 256;
      if (--s->work[2] == 0xFF) {
        (p->body).status = (p->body).prevStatus = 0;
        (p->body).invincibleTime = 0;
        s->flags &= ~COLLIDABLE;
        s->work[2] = 8;
        s->mode[1]++;
      }
      break;
    case 2:
      (s->spr).mag.x = (s->spr).mag.y = s->work[2] * 16 + 128;
      if (--s->work[2] == 0xFF) killBlade(p);
      break;
  }
}

// 0x08074be8
static void Blade_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 0) {
    Spark_Update(p);
    return;
  }
  if ((p->body).status & BODY_STATUS_DEAD) {
    killBlade(p);
    return;
  }
  if (s->mode[1] <= 3 && s->unk_28->mode[1] == 21) s->mode[1] = 4, s->mode[2] = 0;  // He has grabbed Zero
  (sBladeUpdates[s->mode[1]])(p);
}

// --------------------------------------------
// Zero 2 data.

// clang-format off
static const struct Collision sCollisions[30] = {
    /* 0x833b298 */ {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x23, 2, 0x00000001, {-0x800, -0x1800, 0x1200, 0x2c00}},
    /* 0x833b2b0, HB_BODY */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b2c8 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b2e0 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b2f8, HB_DASH */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b310 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0xffffffff, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b328, HB_HOLD */ {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0, 0x00000001, {0x0, 0x0, -0x8000, -0x8000}},
    /* 0x833b340, HB_SLAM */ {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, -0x8000, -0x8000}},
    /* 0x833b358 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x2200, -0x600, 0x2400, 0x1800}},
    /* 0x833b370 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b388 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b3a0 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1c00, -0x600, 0x1400, 0x1200}},
    /* 0x833b3b8 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b3d0 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b3e8 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1c00, -0xc00, 0x1400, 0x1e00}},
    /* 0x833b400 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b418 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x400, -0x1000, 0x2000, 0x2000}},
    /* 0x833b430 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1400, -0x1a00, 0x1000, 0x3c00}},
    /* 0x833b448 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b460 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b478 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1400, -0x1000, 0x1000, 0x5400}},
    /* 0x833b490 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b4a8 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b4c0 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {-0x1400, -0x800, 0x1000, 0x6000}},
    /* 0x833b4d8 */ {DDP, FACTION_ENEMY, 2, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b4f0 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {-0x200, -0x1800, 0x1400, 0x2800}},
    /* 0x833b508, HB_DIVE */ {DDP, FACTION_ENEMY, 2, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 1, 0x00000001, {-0x800, -0x1800, 0x1200, 0x2c00}},
    /* 0x833b520 */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
    /* 0x833b538, HB_INTRO: cannot be hurt */ {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, -0x1200, 0x1000, 0x2400}},
};
// clang-format on

// 0x0833b5fc: rising slash hitboxes, by animation step
static const u8 sSlashCollisions[12] = {8, 9, 11, 14, 17, 20, 23, 17, 16, 16, 16, 16};

// 0x08343b5c..0x08343bd4: waves, by kind
static const struct Collision sWaveCollisions[6] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x4000, 0x2000}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1800, 0xa00}},
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x200, 0x200, 0xe00, 0x1200}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x400, 0x0, 0x1200, 0x1a00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x2000, 0x4000}},
    {DDP, FACTION_ENEMY, 0, 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x400, -0x8000, 0x800}},
};

// 0x08343c28: the bolt, 128 px tall, starting 48 px above the lowest orb
static const struct Collision sOrbCollisions[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x3000, 0x1000, -0x8000}},
};

// 0x08343c40: the strike, on the floor and up the bolt
static const struct Collision sStrikeCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x2000, 0x800}},
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, -0x7d00, 0x800, -0x600}},
};

// 0x0833f904, 0x0833f934, 0x0833f964: blade, stopped blade, spark
static const struct Collision sBladeCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};
static const struct Collision sBladeStopCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x800, 0x800}},
};
static const struct Collision sSparkCollisions[1] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
};

#endif  // AP
