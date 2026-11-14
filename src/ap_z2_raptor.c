#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "palette_animation.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "score.h"
#include "script.h"
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
  Zero 2's boss 10, Harpuia under the Dark Elf.
  Leaps into green bubble, comes out raptor. Whole raptor and its wings are BG2 (layer.c).
*/

struct Raptor {
  OBJECT_HDR;
  s32 homeX;     // 0xB4
  s32 floor;     // 0xB8
  u8 _bc;
  u8 bob;        // 0xBD
  u8 _be;
  u8 attacks;    // 0xBF, in turn
  u8 _c0[4];
  s32 left;      // 0xC4
  s32 right;     // 0xC8
  s32 hoverY;    // 0xCC
  u16 spin;      // 0xD0, swoop's turn
  u8 swoops;     // 0xD2, odds index, 255 just swooped
  bool8 lowHp;   // 0xD3
  u16 dieTimer;  // 0xD4
  s16 loop;      // 0xD6, sound held
  u8 _d8[12];
};
static_assert(sizeof(struct Raptor) == sizeof(struct Boss));

enum {
  RAPTOR_WAIT,
  RAPTOR_LEAP,
  RAPTOR_CHANGE,
  RAPTOR_LAND,
  RAPTOR_RISE,
  RAPTOR_NOP,
  RAPTOR_PICK,
  RAPTOR_HOVER,
  RAPTOR_DRONES,
  RAPTOR_TORNADO,
  RAPTOR_DASH,
  RAPTOR_RETURN,
  RAPTOR_CLAWS,
  RAPTOR_CHARGE,
  RAPTOR_SWOOP,
  RAPTOR_VORTEX,
};

#define HARPUIA(n) MOTION(DM200_Z2_HARPUIA, (n))
#define RAPTOR(n) MOTION(AP_SHEET_Z2_RAPTOR, (n))
#define PARTS(n) MOTION(AP_SHEET_Z2_RAPTOR_PARTS, (n))
#define WIND(n) MOTION(AP_SHEET_Z2_RAPTOR_WIND, (n))
#define TRAIL(n) MOTION(AP_SHEET_Z2_RAPTOR_TRAIL, (n))
#define ORB(n) MOTION(AP_SHEET_Z2_RAPTOR_ORB, (n))

#define FACING_RIGHT(p) ((((struct Entity*)(p))->flags & X_FLIP) != 0)
#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define STAGE (gOverworld.work.apZ2WindShrine)

extern const PlttAnimData gApZ2Na3_PlttAnim8;
extern const AnimCmd* const gApZ2Na3_PlttAnimScript8[];

static const struct Collision sBody[5];
static const struct Collision sDash[6];
static const struct Collision sSwoop[1];
static const struct Collision sSwoopNear[3];
static const struct Collision sDroneBody[2];
static const struct Collision sOrbBody[2];
static const struct Collision sTornado[1];
static const struct Collision sClaw[2];
static const struct Collision sLink[2];
static const struct Coord sElementCoord = {-PIXEL(15), -PIXEL(40)};
static const u8 sSwoopOdds[3] = {3, 1, 0};

// Raptor and parts over boss window at the change. Trail in door window, orbs in containers' window.
static const struct PreloadEntity sRaptorSheet = {AP_SHEET_Z2_RAPTOR, 0, 512, 4, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sPartsSheet = {AP_SHEET_Z2_RAPTOR_PARTS, 0, 512 + AP_SHEET_Z2_RAPTOR_TILES, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sWindSheet = {AP_SHEET_Z2_RAPTOR_WIND, 0, 512 + AP_SHEET_Z2_RAPTOR_TILES + AP_SHEET_Z2_RAPTOR_PARTS_TILES, 6, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sTrailSheet = {AP_SHEET_Z2_RAPTOR_TRAIL, 0, 480, 7, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sOrbSheet = {AP_SHEET_Z2_RAPTOR_ORB, 0, 380, 7, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sSparkSheet = {AP_SHEET_Z2_FEFNIR_SUMMON, 0, 576, 5, 0, AP_PRELOAD_SHEET, 0};

static void Raptor_Init(struct Raptor* p);
static void Raptor_Update(struct Raptor* p);
static void Raptor_Die(struct Raptor* p);
static void Raptor_Disappear(struct Raptor* p);
static struct Entity* createDrone(struct Entity* parent, u8 kind, u8 right);
static struct Entity* createVortex(struct Entity* parent, u8 kind, u8 look, u8 angle);
static void createStreak(struct Entity* parent, u8 kind, u8 angle);
static struct Entity* createTrail(struct Entity* parent, u8 kind);
static void createTornado(struct Entity* boss, u8 n);
static struct Entity* createClaw(struct Entity* parent, u8 kind, u8 n);

// clang-format off
const BossRoutine gApZ2RaptorRoutine = {
    [ENTITY_INIT] =      (BossFunc)Raptor_Init,
    [ENTITY_UPDATE] =    (BossFunc)Raptor_Update,
    [ENTITY_DIE] =       (BossFunc)Raptor_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)Raptor_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

static bool8 gone(struct Entity* e) { return e == NULL || e->mode[0] > ENTITY_UPDATE; }

static void useApSheets(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setUp(void* p, motion_t m) {
  struct Entity* s = (struct Entity*)p;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  useApSheets(p);
  SetSpriteAnimation(p, m);
  UpdateSpriteAnimation(p);
}

static void blink(struct Entity* s, bool8 hide) { s->flags = hide ? (s->flags & ~DISPLAY) : (s->flags | DISPLAY); }

static void bob(struct Raptor* p) { (p->s).coord.y = p->hoverY + SIN(p->bob++) * 8; }

static s32 speed(struct Entity* s) { return s->d.x < 0 ? -s->d.x * 2 : s->d.x * 2; }

static bool8 pastEdge(struct Raptor* p) {
  if (FACING_RIGHT(p)) return (p->s).coord.x > p->right + PIXEL(120);
  return (p->s).coord.x < p->left - PIXEL(120);
}

// 0x0804d620
static void Raptor_Init(struct Raptor* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  ResetDynamicMotion(s);
  SetSpriteAnimation(p, HARPUIA(0));
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FALSE);
  STAGE.bg = 0;
  ResetBossBody((struct Boss*)p, sBody, 96);
  STAGE.raptor = s;
  s->coord.x += PIXEL(240);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  p->homeX = s->coord.x;
  p->floor = s->coord.y;
  p->attacks = 0;
  p->swoops = 0;
  p->lowHp = FALSE;
  s->unk_2c = NULL;
  p->left = s->coord.x - PIXEL(272);
  p->right = s->coord.x + PIXEL(128);
  p->hoverY = p->floor - PIXEL(60);
  p->loop = -1;
  ApLoadSheet(&sWindSheet);
  ApLoadSheet(&sTrailSheet);
  ApLoadSheet(&sOrbSheet);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Raptor_Update(p);
}

static const BossFunc sStates[16];

// 0x0804d7b4
static void Raptor_Update(struct Raptor* p) {
  struct Entity* s = &p->s;
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Raptor_Die(p);
    return;
  }
  if (!p->lowHp && (p->body).hp < 32) {
    PlaySound(SE_Z2_RAPTOR_CRY);
    p->lowHp = TRUE;
  }
  if (((p->body).status & BODY_STATUS_WHITE) && s->unk_2c == NULL) {
    s->unk_2c = ApplyElementEffect(13, (Object*)p, &sElementCoord);
    if (s->unk_2c != NULL) PlaySound(SE_Z2_RAPTOR_BURN);
  }
  if (s->unk_2c != NULL && IsDead(s->unk_2c)) s->unk_2c = NULL;
  (sStates[s->mode[1]])((struct Boss*)p);
  STAGE.center = s->coord;
}

// 0x0804d8a2: explodes, flashing slower, until clear script destroys it
static void Raptor_Die(struct Raptor* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if (s->mode[2] == 0) {
    SetSpriteAnimation(p, RAPTOR(7));
    STAGE.bg = FACING_RIGHT(p) ? 3 : 2;
    StopSound(p->loop);
    p->loop = -1;
    EXIT_BODY(p);
    if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
      gStageRun.missionStatus &= ~MISSION_STAY;
      gStageRun.missionStatus |= MISSION_SUCCESS;
    }
    p->dieTimer = 0;
    s->work[2] = 24;
    s->work[3] = 12;
    s->mode[2]++;
  }
  if (p->dieTimer++ > 64) {
    if ((p->dieTimer & 3) == 0) {
      at.x = s->coord.x + PIXEL(48 - (RANDOM(RNG_0202f388) & 0x7FFF) % 96);
      at.y = s->coord.y - PIXEL((RANDOM(RNG_0202f388) & 31) + 16);
      ApZ2CreateExplosion(s, &at, 2, (u8)RANDOM(RNG_0202f388));
    }
    if ((p->dieTimer & 15) == 0) PlaySound(SE_Z2_TANK_EXPLODE);
  }
  if (p->dieTimer % 10 == 0) createTrail(s, 2);
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

// 0x0804da84
static void Raptor_Disappear(struct Raptor* p) {
  STAGE.bg = 0;
  STAGE.raptor = NULL;
  DeleteBoss(&p->s);
}

// 0x0804daa0: kneels until script's flag
static void Raptor_Wait(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) s->mode[2]++;
  UpdateSpriteAnimation(p);
  if (s->scriptEntity->flags & 1) setMode(s, RAPTOR_LEAP);
}

// 0x0804dad0
static void Raptor_Leap(struct Raptor* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, HARPUIA(2));
      s->work[2] = 8;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) s->mode[2]++;
      break;
    case 2:
      SetSpriteAnimation(p, HARPUIA(3));
      s->d.y = -0x500;
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateSpriteAnimation(p);
      s->d.y += 0x40;
      s->coord.y += s->d.y;
      if (s->d.y >= 0) setMode(s, RAPTOR_CHANGE);
      break;
  }
}

// 0x0804db68: bubble, then raptor fading in from white
static void Raptor_Change(struct Raptor* p) {
  struct Entity* s = &p->s;
  struct Entity* b;
  Coords32 at;
  u8 i;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, HARPUIA(10));
      PlaySound(SE_Z2_HARPUIA_RISE);
      s->mode[3] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[2]++;
      break;
    case 2:
      at.x = s->coord.x;
      at.y = s->coord.y - PIXEL(16);
      s->unk_28 = ApZ2CreateBubble(&at, 1);
      PlaySound(SE_Z2_FEFNIR_BUBBLE);
      ApLoadSheet(&sSparkSheet);
      s->mode[2]++;
      FALLTHROUGH;
    case 3:
      b = s->unk_28;
      if (b->mode[3] == 0) {
        blink(s, !(s->work[2]++ & 1));
        if ((s->work[2] & 3) != 0) break;
        at.x = s->coord.x;
        at.y = s->coord.y - PIXEL(18);
        for (i = 0; i < 4; i++) ApZ2CreateHarpuiaSpark(&at, i);
      } else if (b->mode[3] == 1) {
        blink(s, !(s->work[2]++ & 1));
      } else if (b->mode[3] == 2) {
        s->flags &= ~DISPLAY;
        s->mode[2]++;
      }
      break;
    case 4:
      s->flags |= DISPLAY;
      ApLoadSheet(&sRaptorSheet);
      ApLoadSheet(&sPartsSheet);
      s->flags2 &= ~DYNAMIC;
      useApSheets(p);
      SetSpriteAnimation(p, RAPTOR(12));
      UpdateSpriteAnimation(p);
      ApStartPaletteAnimation(PLTT_ANIM_ID(8), &gApZ2Na3_PlttAnim8, gApZ2Na3_PlttAnimScript8, 0x280);
      StepPaletteAnimation(PLTT_ANIM_ID(8));
      s->coord.y += PIXEL(32);
      setMode(s, RAPTOR_LAND);
      break;
  }
}

// 0x0804ddc8
static void Raptor_Land(struct Raptor* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      if (gone(s->unk_28)) s->mode[2]++;
      break;
    case 1:
      SetSpriteAnimation(p, RAPTOR(11));
      PlaySound(SE_Z2_HARPUIA_EX);
      s->work[2] = 0;
      s->mode[2]++;
      FALLTHROUGH;
    case 2:
      if (s->work[2] == 0 && (s->motion).cmdIdx == 7) {
        PlaySound(SE_Z2_HARPUIA_EX);
        s->work[2]++;
      }
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) {
        s->work[2] = 16;
        s->mode[2]++;
      }
      break;
    case 3:
      if ((u8)StepPaletteAnimation(PLTT_ANIM_ID(8)) != 3) break;
      RemovePaletteAnimation(PLTT_ANIM_ID(8));
      s->d.y = 0;
      s->mode[2]++;
      break;
    case 4:
      UpdateSpriteAnimation(p);
      s->d.y += 0x40;
      s->coord.y += s->d.y;
      if (s->coord.y <= p->floor) break;
      PlaySound(SE_Z2_DESERT_STEP);
      s->coord.y = p->floor;
      s->mode[2]++;
      break;
    case 5:
      SetSpriteAnimation(p, RAPTOR(0));
      AppendQuake(1, &s->coord);
      s->work[2] = 32;
      s->mode[2]++;
      FALLTHROUGH;
    case 6:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0xFF) setMode(s, RAPTOR_RISE);
      break;
  }
}

// 0x0804def0: rises to hover, waits for script to let go
static void Raptor_Rise(struct Raptor* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, RAPTOR(1));
      s->mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateSpriteAnimation(p);
      if (!IsSpriteAnimEnd(p)) break;
      s->work[2] = 16;
      s->mode[2]++;
      break;
    case 2:
      if (--s->work[2] == 0xFF) s->mode[2]++;
      break;
    case 3:
      SetSpriteAnimation(p, RAPTOR(3));
      s->d.y = -0x440;
      s->mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      s->d.y += 32;
      s->coord.y += s->d.y;
      if (s->coord.y >= p->hoverY - PIXEL(8)) break;
      s->coord.y = p->hoverY - PIXEL(8);
      p->bob = 192;
      s->mode[2]++;
      break;
    case 5:
      STAGE.bg = 2;
      SetSpriteAnimation(p, RAPTOR(4));
      s->mode[2]++;
      FALLTHROUGH;
    case 6:
      UpdateSpriteAnimation(p);
      s->coord.y = p->hoverY + SIN(p->bob) * 8;
      p->bob += 2;
      if (p->bob != 64) break;
      s->work[2] = 32;
      s->mode[2]++;
      break;
    case 7:
      UpdateSpriteAnimation(p);
      bob(p);
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, RAPTOR_PICK);
      break;
  }
}

static void Raptor_Nop(struct Raptor* p UNUSED) {}

// 0x0804e060: odd turns drones or charge, even ones drones, tornado, claws, vortex (rank A)
static void Raptor_Pick(struct Raptor* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  if (p->attacks & 1) {
    setMode(s, (RANDOM(RNG_0202f388) & 1) ? RAPTOR_DRONES : RAPTOR_CHARGE);
  } else {
    switch (p->attacks >> 1) {
      case 0: setMode(s, RAPTOR_DRONES); break;
      case 1: setMode(s, RAPTOR_TORNADO); break;
      case 2: setMode(s, RAPTOR_CLAWS); break;
      case 3: setMode(s, gScore.total->rank > 4 ? RAPTOR_VORTEX : RAPTOR_DRONES); break;
    }
  }
  p->attacks = (p->attacks + 1) % 8;
}

// 0x0804e0fc
static void Raptor_Hover(struct Raptor* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  bob(p);
  if (--s->work[2] == 0xFF) setMode(s, RAPTOR_PICK);
}

// 0x0804e148: hatch lets drones go
static void Raptor_Drones(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->unk_28 = createDrone(s, 0, 0);
    PlaySound(SE_Z2_RAPTOR_HATCH);
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bob(p);
  if (!gone(s->unk_28)) return;
  setMode(s, RAPTOR_HOVER);
  s->work[2] = 16;
}

// 0x0804e1b4: tornado down to floor, a segment every 6 frames
static void Raptor_Tornado(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->work[3] = s->work[2] = 0;
    p->loop = PlaySound(SE_Z2_FROST_BREATH);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bob(p);
  if (s->work[2]++ % 6 == 0) createTornado(s, s->work[3]++);
  if (s->work[3] > 8) setMode(s, RAPTOR_DASH);
}

// 0x0804e23c: carries tornado off screen
static void Raptor_Dash(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.x = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bob(p);
  if (s->d.x <= 0x1FF) s->d.x += 8;
  s->coord.x += FACING_RIGHT(p) ? s->d.x : -s->d.x;
  if (pastEdge(p)) setMode(s, RAPTOR_RETURN);
}

// 0x0804e2e4: maybe swoops, else flies back in from other side, braking
static void Raptor_Return(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    StopSound(p->loop);
    p->loop = -1;
    if (p->swoops != 0xFF) {
      if ((RANDOM(RNG_0202f388) & sSwoopOdds[p->swoops]) == 0) {
        setMode(s, RAPTOR_SWOOP);
        return;
      }
      p->swoops = (p->swoops + 1) % 3;
    } else {
      p->swoops = 0;
    }
    s->flags |= DISPLAY;
    STAGE.bg = 0;
    SetSpriteAnimation(p, RAPTOR(10));
    SetDDP(&p->body, sDash);
    s->d.y = s->d.x = 0;
    s->unk_28 = createTrail(s, 0);
    s->coord.x = FACING_RIGHT(p) ? p->right + PIXEL(80) : p->left - PIXEL(80);
    SET_XFLIP(p, !FACING_RIGHT(p));
    STAGE.scale = 256;
    STAGE.angle = 0;
    s->d.x = 0x900;
    p->bob = 64;
    PlaySound(SE_Z2_GOLEM_SLIDE);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  bob(p);
  switch (s->mode[3]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (s->d.x <= 0x1FF) s->mode[3]++;
      break;
    case 1:
      SetSpriteAnimation(p, RAPTOR(4));
      SetDDP(&p->body, sBody);
      STAGE.bg = FACING_RIGHT(p) ? 3 : 2;
      s->unk_28->work[1] = 1;
      s->mode[3]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      break;
  }
  s->d.x -= 64;
  s->coord.x += FACING_RIGHT(p) ? s->d.x : -s->d.x;
  if (s->d.x != 0) return;
  setMode(s, RAPTOR_HOVER);
  s->work[2] = 32;
}

// 0x0804e52c: one claw, then the other, then off screen
static void Raptor_Claws(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->unk_28 = createClaw(s, 0, 0);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
    s->work[2] = 112;
    s->d.x = FACING_RIGHT(p) ? 0x200 : -0x200;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bob(p);
  if (s->mode[3] != 0) {
    s->coord.x += s->d.x;
    if (pastEdge(p)) setMode(s, RAPTOR_RETURN);
  } else if (--s->work[2] == 0xFF) {
    s->unk_28 = createClaw(s, 0, 1);
    PlaySound(SE_Z2_SIGNALOID_THUNDER);
    s->mode[3]++;
  }
}

// 0x0804e618: dives low across room
static void Raptor_Charge(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    STAGE.bg = 0;
    SetSpriteAnimation(p, RAPTOR(10));
    SetDDP(&p->body, sDash);
    s->d.y = s->d.x = 0;
    s->unk_28 = createTrail(s, 0);
    PlaySound(SE_Z2_GOLEM_SLIDE);
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (s->d.x <= 0x5FF) s->d.x += 16;
  s->coord.y = s->coord.y < p->floor - PIXEL(16) ? s->coord.y + PIXEL(1) : p->floor - PIXEL(16);
  s->coord.x += FACING_RIGHT(p) ? s->d.x : -s->d.x;
  if (!pastEdge(p)) return;
  s->unk_28->work[1] = 1;
  setMode(s, RAPTOR_RETURN);
}

/*
  0x0804e6f8: whole raptor on BG2 sweeps over Zero growing to full size, then past screen.
  Start is first leg run backwards from Zero's x.
*/
static void Raptor_Swoop(struct Raptor* p) {
  struct Entity* s = &p->s;
  s32 v;
  u8 i;
  if (s->mode[2] == 0) {
    s->flags &= ~DISPLAY;
    SetDDP(&p->body, sSwoop);
    STAGE.bg = 1;
    STAGE.scale = 64;
    STAGE.angle = 0;
    s->d.y = s->d.x = 0;
    s->coord.x = (pZero2->s).coord.x;
    s->coord.y = p->floor - PIXEL(40);
    s->unk_coord.y = -4;
    s->unk_coord.x = FACING_RIGHT(p) ? 16 : -16;
    p->spin = 0xC00;
    for (i = 0; i < 128; i++) {
      s->d.x -= s->unk_coord.x;
      s->coord.x -= s->d.x;
      p->spin += speed(s);
    }
    p->swoops = 0xFF;
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  if (STAGE.scale == 256) {
    SetDDP(&p->body, sSwoopNear);
    PlaySound(SE_Z2_RAPTOR_SWOOP);
    PlaySound(SE_Z2_GOLEM_SLIDE);
  } else {
    SetDDP(&p->body, sSwoop);
  }
  switch (s->mode[3]) {
    case 0:
      s->coord.x += s->d.x;
      p->spin -= speed(s);
      s->d.x += s->unk_coord.x;
      if (s->d.x == 0) s->mode[3]++;
      break;
    case 1:
      STAGE.scale += 4;
      p->spin -= 48;
      s->d.y += s->unk_coord.y;
      s->coord.y += s->d.y;
      if (STAGE.scale <= 256) break;
      v = s->d.y;
      s->d.y = v * 4;
      s->unk_coord.x = FACING_RIGHT(p) ? s->unk_coord.y * 2 : -(s->unk_coord.y * 2);
      s->d.x = FACING_RIGHT(p) ? v * 8 : -(v * 8);
      s->mode[3]++;
      break;
    default:
      STAGE.scale += 4;
      p->spin -= 96;
      s->d.x += s->unk_coord.x;
      s->d.y += s->unk_coord.y;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (STAGE.scale <= 512) break;
      SET_XFLIP(p, !FACING_RIGHT(p));
      STAGE.bg = 0;
      setMode(s, RAPTOR_RETURN);
      return;
  }
  STAGE.angle = FACING_RIGHT(p) ? p->spin >> 8 : -(p->spin >> 8);
}

// 0x0804e978: glows, then vortex
static void Raptor_Vortex(struct Raptor* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->unk_28 = createTrail(s, 1);
    s->mode[3] = 0;
    s->mode[2]++;
  }
  UpdateSpriteAnimation(p);
  bob(p);
  if (!gone(s->unk_28)) return;
  if (s->mode[3] == 0) {
    s->unk_28 = createVortex(s, 2, 0, 0);
    s->mode[3]++;
  } else {
    setMode(s, RAPTOR_HOVER);
    s->work[2] = 32;
  }
}

// clang-format off
static const BossFunc sStates[16] = {
    [RAPTOR_WAIT] =    (BossFunc)Raptor_Wait,
    [RAPTOR_LEAP] =    (BossFunc)Raptor_Leap,
    [RAPTOR_CHANGE] =  (BossFunc)Raptor_Change,
    [RAPTOR_LAND] =    (BossFunc)Raptor_Land,
    [RAPTOR_RISE] =    (BossFunc)Raptor_Rise,
    [RAPTOR_NOP] =     (BossFunc)Raptor_Nop,
    [RAPTOR_PICK] =    (BossFunc)Raptor_Pick,
    [RAPTOR_HOVER] =   (BossFunc)Raptor_Hover,
    [RAPTOR_DRONES] =  (BossFunc)Raptor_Drones,
    [RAPTOR_TORNADO] = (BossFunc)Raptor_Tornado,
    [RAPTOR_DASH] =    (BossFunc)Raptor_Dash,
    [RAPTOR_RETURN] =  (BossFunc)Raptor_Return,
    [RAPTOR_CLAWS] =   (BossFunc)Raptor_Claws,
    [RAPTOR_CHARGE] =  (BossFunc)Raptor_Charge,
    [RAPTOR_SWOOP] =   (BossFunc)Raptor_Swoop,
    [RAPTOR_VORTEX] =  (BossFunc)Raptor_Vortex,
};
// clang-format on

// --------------------------------------------
/*
  Zero 2's enemy 27.
  work0:
    0: hatch on raptor, lets drones go
    1: drone, drops level with Zero and flies off
  work1: drone faces right
*/

static void Drone_Init(struct Enemy* p);
static void Drone_Update(struct Enemy* p);
static void Drone_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gApZ2RaptorDroneRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Drone_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Drone_Update,
    [ENTITY_DIE] =       (EnemyFunc)Drone_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x08075060
static struct Entity* createDrone(struct Entity* parent, u8 kind, u8 right) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_RAPTOR_DRONE);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = right;
  }
  return p;
}

// 0x08075110, 0x08075168
static void Drone_Init(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 0) {
    setUp(p, RAPTOR(5));
    s->invincibleID = s->unk_28->uniqueID;
  } else {
    setUp(p, PARTS(9));
    (s->spr).oam.priority = 3;
    SET_XFLIP(p, s->work[1]);
    INIT_BODY(p, sDroneBody, 16, NULL);
    s->d.x = s->d.y = 0;
    s->work[2] = 0;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Drone_Update(p);
}

// 0x08075220: rides raptor
static void Hatch_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  SET_XFLIP(p, FACING_RIGHT(boss));
  s->coord = boss->coord;
  switch (s->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, RAPTOR(6));
      s->work[2] = 0;
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      if ((s->work[2] & 31) == 0) createDrone(boss, 1, FACING_RIGHT(p));
      if (++s->work[2] > 159) s->mode[1]++;
      break;
    case 3:
      SetSpriteAnimation(p, RAPTOR(5));
      s->mode[1]++;
      FALLTHROUGH;
    case 4:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        Drone_Die(p);
      }
      break;
  }
}

// 0x0807532c
static void Drone_Update(struct Enemy* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  s32 off;
  if (s->work[0] == 0) {
    Hatch_Update(p);
    return;
  }
  if (((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) || gone(boss)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Drone_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      off = PIXEL(13) + (s->work[2] << 9);
      s->coord.x = FACING_RIGHT(p) ? boss->coord.x - off : boss->coord.x + off;
      s->d.x = FACING_RIGHT(p) ? -0xC0 : 0xC0;
      s->coord.y = boss->coord.y - PIXEL(27);
      if (s->work[2]++ > 13) s->mode[1]++;
      break;
    case 1:
      if (s->d.y <= 0x6FF) s->d.y += 0x40;
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      if (s->coord.y <= (pZero2->s).coord.y - PIXEL(24)) break;
      SetSpriteAnimation(p, PARTS(10));
      UpdateSpriteAnimation(p);
      PlaySound(SE_Z2_DRONE_DIVE);
      s->work[2] = 255;
      s->mode[1]++;
      break;
    case 2:
      if (FACING_RIGHT(p)) {
        if (s->d.x <= 0x3FF) s->d.x += 0x80;
      } else if (s->d.x > -0x400) {
        s->d.x -= 0x80;
      }
      s->coord.x += s->d.x;
      if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}

// 0x08075480, 0x08075498
static void Drone_Die(struct Enemy* p) {
  struct Entity* s = &p->s;
  if (s->work[0] != 0) {
    CreateSmoke(1, &s->coord);
    PlaySound(SE_Z2_TANK_EXPLODE);
  }
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------
/*
  Zero 2's enemy 28.
  work0:
    0: orb, spirals into vortex
    1: orb, flung out of it
    2: vortex, flies out of raptor, opens and spins
  work1: orb's look
*/

struct Vortex {
  OBJECT_HDR;
  u8 _b4[9];
  u8 angle;   // 0xBD
  u16 scale;  // 0xBE
  s16 loop;   // 0xC0, sound held
  u8 _c2[2];
};
static_assert(sizeof(struct Vortex) == sizeof(struct Enemy));

static void Vortex_Init(struct Vortex* p);
static void Vortex_Update(struct Vortex* p);
static void Vortex_Die(struct Vortex* p);

// clang-format off
const EnemyRoutine gApZ2VortexRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Vortex_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Vortex_Update,
    [ENTITY_DIE] =       (EnemyFunc)Vortex_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x080754c8
static struct Entity* createVortex(struct Entity* parent, u8 kind, u8 look, u8 angle) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_VORTEX);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = look;
    ((struct Vortex*)p)->angle = angle;
  }
  return p;
}

// Along spiral at work3 with d.x radius, outward or back in
static void spiral(struct Entity* s, bool8 back) {
  s32 dx = COS(s->work[3]) * s->d.x / 256;
  s32 dy = SIN(s->work[3]) * s->d.x / 256;
  s->coord.x += back ? -dx : dx;
  s->coord.y += back ? -dy : dy;
}

static void randomFlips(void* p) {
  SET_XFLIP(p, RANDOM(RNG_0202f388) & 1);
  SET_YFLIP(p, RANDOM(RNG_0202f388) & 1);
}

// 0x080755e8, 0x0807575c, 0x080758a4
static void Vortex_Init(struct Vortex* p) {
  struct Entity* s = &p->s;
  struct Entity* parent = s->unk_28;
  u8 i;
  switch (s->work[0]) {
    case 0:
      setUp(p, ORB(s->work[1] ? 2 : 1));
      randomFlips(p);
      s->work[2] = 16;
      s->work[3] = p->angle;
      s->d.x = 0x500;
      s->coord = parent->coord;
      for (i = 0; i < 64; i++) {
        s->work[3]++;
        spiral(s, FALSE);
        s->d.x -= 16;
      }
      break;
    case 1:
      setUp(p, ORB(s->work[1] ? 2 : 1));
      randomFlips(p);
      INIT_BODY(p, sOrbBody, 8, NULL);
      s->work[2] = 128;
      s->work[3] = p->angle;
      s->d.x = 0x100;
      s->coord = parent->coord;
      break;
    default:
      setUp(p, PARTS(1));
      SET_XFLIP(p, FALSE);
      s->d.x = 0x300;
      if (FACING_RIGHT(parent)) {
        s->coord.x = parent->coord.x + PIXEL(20);
        s->work[2] = 16;
      } else {
        s->coord.x = parent->coord.x - PIXEL(20);
        s->work[2] = 112;
      }
      s->coord.y = parent->coord.y - PIXEL(39);
      p->loop = -1;
      break;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  Vortex_Update(p);
}

static void hitSound(struct Vortex* p) {
  if (((p->body).status & BODY_STATUS_B2) && !((p->body).prevStatus & BODY_STATUS_B2)) PlaySound(SE_Z2_BLOB_STOMP);
}

static void turn(struct Vortex* p, s8 by) {
  p->angle += by;
  (p->s).angle = p->angle;
}

static void grow(struct Vortex* p, u16 by) {
  p->scale += by;
  ((p->s).spr).mag.x = ((p->s).spr).mag.y = p->scale;
}

// 0x08075b24: draws orbs in, turns back, flings more out
static void Vortex_Spin(struct Vortex* p) {
  struct Entity* s = &p->s;
  if (gone(s->unk_28) || s->mode[1] > 8) {
    StopSound(p->loop);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->coord.x += COS(s->work[2]) * s->d.x / 256;
      s->coord.y += SIN(s->work[2]) * s->d.x / 256;
      s->d.x -= 16;
      if (!IsSpriteAnimEnd(p)) break;
      SetSpriteAnimation(p, PARTS(2));
      UpdateSpriteAnimation(p);
      s->mode[1]++;
      break;
    case 1:
      s->coord.x += COS(s->work[2]) * s->d.x / 256;
      s->coord.y += SIN(s->work[2]) * s->d.x / 256;
      s->d.x -= 16;
      if (s->d.x != 0) break;
      SetSpriteAnimation(p, PARTS(3));
      UpdateSpriteAnimation(p);
      s->mode[1]++;
      break;
    case 2:
      if (!IsSpriteAnimEnd(p)) break;
      InitRotatableMotion(s);
      SetSpriteAnimation(p, WIND(0));
      UpdateSpriteAnimation(p);
      p->angle = 0;
      p->scale = 0;
      turn(p, 0);
      grow(p, 16);
      p->loop = PlaySound(SE_Z2_FROST_BREATH);
      s->mode[1]++;
      break;
    case 3:
      turn(p, -3);
      grow(p, 8);
      if (p->scale <= 255) break;
      s->work[2] = 128;
      s->work[3] = 0;
      s->mode[1]++;
      break;
    case 4:
      turn(p, -3);
      if ((s->work[2] & 3) == 0) createStreak(s, 0, s->work[3] + (RANDOM(RNG_0202f388) & 15));
      if ((s->work[2] & 7) == 0) {
        createVortex(s, 0, RANDOM(RNG_0202f388) & 1, s->work[3]);
        s->work[3] += 66;
      }
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 128;
      s->mode[1]++;
      break;
    case 5:
      turn(p, -3);
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    case 6:
      turn(p, (32 - s->work[2]) / 11);
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 128;
      s->work[3] = 0;
      s->mode[1]++;
      break;
    case 7:
      turn(p, 3);
      if ((s->work[2] & 3) == 0) createStreak(s, 1, s->work[3] + (RANDOM(RNG_0202f388) & 15));
      if ((s->work[2] & 7) == 0) {
        createVortex(s, 1, RANDOM(RNG_0202f388) & 1, s->work[3]);
        s->work[3] -= 66;
      }
      if (--s->work[2] != 0xFF) break;
      s->work[2] = 64;
      s->mode[1]++;
      break;
    default:
      turn(p, 3);
      grow(p, 3);
      blink(s, s->work[2] & 1);
      if (--s->work[2] == 0xFF) s->mode[1]++;
      break;
  }
}

// 0x08075958, 0x08075a80
static void Vortex_Update(struct Vortex* p) {
  struct Entity* s = &p->s;
  if (s->work[0] == 2) {
    Vortex_Spin(p);
    return;
  }
  UpdateSpriteAnimation(p);
  hitSound(p);
  if (s->work[0] == 1) {
    s->work[3]++;
    spiral(s, FALSE);
    s->d.x += 16;
    if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (s->mode[1] == 0) {
    blink(s, s->work[2] & 1);
    if (--s->work[2] != 0xFF) return;
    s->flags |= DISPLAY;
    INIT_BODY(p, sOrbBody, 8, NULL);
    s->mode[1]++;
    return;
  }
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Vortex_Die(p);
    return;
  }
  s->work[3]--;
  spiral(s, TRUE);
  s->d.x += 16;
  if (s->d.x > 0x4FF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// 0x08075570: falls blinking
static void Vortex_Die(struct Vortex* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    EXIT_BODY(p);
    s->work[2] = 64;
    s->d.y = 0;
    s->mode[1]++;
  }
  s->d.y += 0x40;
  s->coord.y += s->d.y;
  blink(s, s->work[2] & 1);
  if (--s->work[2] == 0xFF) SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

// --------------------------------------------
/*
  Zero 2's VFX 30, streak along vortex's spirals.
  work0: 0 in, 1 out
*/

static void Streak_Init(struct VFX* p);
static void Streak_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2StreakRoutine = {
    [ENTITY_INIT] =      Streak_Init,
    [ENTITY_UPDATE] =    Streak_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b4edc
static void createStreak(struct Entity* parent, u8 kind, u8 angle) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_STREAK);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[3] = angle;
  }
}

// 0x080b4f80, 0x080b506c
static void Streak_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  u8 i;
  setUp(p, PARTS(4));
  SET_XFLIP(p, FALSE);
  SET_YFLIP(p, FALSE);
  s->coord = s->unk_28->coord;
  if (s->work[0] == 0) {
    s->d.x = 0x500;
    for (i = 0; i < 64; i++) {
      s->work[3]++;
      spiral(s, FALSE);
      s->d.x -= 16;
    }
  } else {
    s->d.x = 0x100;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Streak_Update(p);
}

// 0x080b510c, 0x080b51a4
static void Streak_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateSpriteAnimation(p);
  if (s->work[0] == 0) {
    s->work[3]--;
    spiral(s, TRUE);
    s->d.x += 16;
    blink(s, !(s->work[3] & 1));
    if (s->d.x > 0x4FF) SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    s->work[3]++;
    spiral(s, FALSE);
    s->d.x += 16;
    blink(s, !(s->work[3] & 1));
    if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) != 0) SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// --------------------------------------------
/*
  Zero 2's VFX 31, on raptor.
  work0:
    0: jet trail until work1 set
    1: glow, six loops
    2: debris as it dies
*/

static void Trail_Init(struct VFX* p);
static void Trail_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2RaptorTrailRoutine = {
    [ENTITY_INIT] =      Trail_Init,
    [ENTITY_UPDATE] =    Trail_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b5244
static struct Entity* createTrail(struct Entity* parent, u8 kind) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_RAPTOR_TRAIL);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = 0;
  }
  return p;
}

// 0x080b52dc, 0x080b5324, 0x080b5376
static void Trail_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  switch (s->work[0]) {
    case 0:
      setUp(p, TRAIL(0));
      break;
    case 1:
      setUp(p, PARTS(0));
      s->work[2] = 6;
      break;
    default:
      setUp(p, PARTS(8));
      randomFlips(p);
      s->unk_coord.x = PIXEL(48 - (RANDOM(RNG_0202f388) & 0x7FFF) % 96);
      s->unk_coord.y = -PIXEL((RANDOM(RNG_0202f388) & 0x7FFF) % 56 + 8);
      break;
  }
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Trail_Update(p);
}

// 0x080b54b0, 0x080b5528, 0x080b55b0
static void Trail_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  struct Entity* boss = s->unk_28;
  if (s->work[0] == 2) {
    UpdateSpriteAnimation(p);
    s->coord.x = boss->coord.x + s->unk_coord.x;
    s->coord.y = boss->coord.y + s->unk_coord.y;
    if ((s->motion).state == ANIM_NEXT_GOTO) SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  if (gone(boss) || (s->work[0] == 0 ? s->work[1] != 0 : s->work[2] == 0)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  UpdateSpriteAnimation(p);
  SET_XFLIP(p, FACING_RIGHT(boss));
  s->coord = boss->coord;
  if (s->work[0] == 1 && (s->motion).state == ANIM_NEXT_GOTO) s->work[2]--;
}

// --------------------------------------------
/*
  Zero 2's projectile 24, tornado segment.
  work0: 0 top .. 8 floor
  Pushes Zero sideways. Breaks up top down once raptor is past floor's end.
*/

struct Tornado {
  OBJECT_HDR;
  u8 _b4[12];
  s32 floor;  // 0xC0
};
static_assert(sizeof(struct Tornado) == sizeof(struct Projectile));

static void Tornado_Init(struct Tornado* p);
static void Tornado_Update(struct Tornado* p);
static void Tornado_Die(struct Tornado* p);

// clang-format off
const ProjectileRoutine gApZ2TornadoRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Tornado_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Tornado_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Tornado_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809eda4
static void createTornado(struct Entity* boss, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_TORNADO);
    p->unk_28 = boss;
    p->work[0] = n;
  }
}

// Top, middle or floor segment's animation
static motion_t segment(struct Entity* s, u8 top, u8 middle, u8 floor) {
  return WIND(s->work[0] == 0 ? top : s->work[0] == 8 ? floor : middle);
}

// 0x0809edf8
static void Tornado_Init(struct Tornado* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  setUp(p, segment(s, 7, 1, 4));
  SET_XFLIP(p, FALSE);
  INIT_BODY(p, sTornado, 1, NULL);
  p->floor = FUN_08009f6c(boss->coord.x, boss->coord.y);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Tornado_Update(p);
}

// Zero 2 moves him in these states only (0x08335f64)
void ApZ2PushZero(s32 dx) {
  struct Zero* z = pZero2;
  const struct Rect* range = &gZeroRanges[z->posture];
  u8 state = (z->s).mode[1];
  if (state != ZERO_GROUND && state != ZERO_AIR && state != ZERO_WALL && state != ZERO_DAMAGED &&
      state != ZERO_BINDED) {
    return;
  }
  (z->s).coord.x += dx;
  PushoutWallX(z, range, 0);
  PushoutWallX(z, range, 1);
}

// 0x0809eeb8
static void Tornado_Update(struct Tornado* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  struct Zero* z = pZero2;
  u8 n = s->work[0];
  if (gone(boss)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  UpdateSpriteAnimation(p);
  if (((p->body).status & BODY_STATUS_B2) && z != NULL && !((z->body).status & BODY_STATUS_DEAD) &&
      (z->body).hp != 0) {
    s->d.x = s->coord.x < (z->s).coord.x ? 0x180 : -0x180;
    ApZ2PushZero(s->d.x);
  }
  s->coord.x = boss->coord.x + (FACING_RIGHT(p) ? -0x300 : 0x300);
  if (n == 0) {
    s->coord.y = boss->coord.y - PIXEL(41);
  } else if (n == 8) {
    s->coord.y = p->floor;
  } else {
    s->coord.y = boss->coord.y - PIXEL(41) + n * ((p->floor + PIXEL(41) - boss->coord.y) / 8);
  }
  if (s->mode[1] == 0) {
    SetSpriteAnimation(p, segment(s, 8, 2, 5));
    UpdateSpriteAnimation(p);
    s->mode[1]++;
  }
  switch (s->mode[1]) {
    case 1:
      if (FUN_080098a4(s->coord.x, p->floor + PIXEL(1)) != 0) break;
      s->work[2] = (8 - n) * 4;
      s->mode[1]++;
      break;
    case 2:
      if (--s->work[2] != 0xFF) break;
      SetSpriteAnimation(p, segment(s, 9, 3, 6));
      UpdateSpriteAnimation(p);
      s->mode[1]++;
      break;
    case 3:
      if (!IsSpriteAnimEnd(p)) break;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      Tornado_Die(p);
      break;
  }
}

// 0x0809f084
static void Tornado_Die(struct Tornado* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
/*
  Zero 2's projectile 25.
  work0:
    0: claw, hangs under raptor and swings
    1: chain link, work1 twelfths of way to claw
  work1: second claw, further back
*/

struct Claw {
  OBJECT_HDR;
  Coords32 pivot;  // 0xB4
  u8 angle;        // 0xBC
  u8 from;         // 0xBD
  bool8 back;      // 0xBE
  bool8 out;       // 0xBF
  s32 reach;       // 0xC0
};
static_assert(sizeof(struct Claw) == sizeof(struct Projectile));

static void Claw_Init(struct Claw* p);
static void Claw_Update(struct Claw* p);
static void Claw_Die(struct Claw* p);

// clang-format off
const ProjectileRoutine gApZ2RaptorClawRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Claw_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Claw_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Claw_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// 0x0809f09c
static struct Entity* createClaw(struct Entity* parent, u8 kind, u8 n) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_RAPTOR_CLAW);
    p->unk_28 = parent;
    p->work[0] = kind;
    p->work[1] = n;
  }
  return p;
}

// 0x0809f168, 0x0809f26c
static void Claw_Init(struct Claw* p) {
  struct Entity* s = &p->s;
  u8 i;
  if (s->work[0] == 0) {
    setUp(p, PARTS(5));
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, sClaw, 1, NULL);
    (s->spr).oam.priority = 1;
    s->unk_coord.x = s->work[1] ? PIXEL(10) : PIXEL(5);
    s->unk_coord.y = s->work[1] ? PIXEL(11) : PIXEL(14);
    if (FACING_RIGHT(s->unk_28)) {
      p->back = TRUE;
      p->angle = 0;
      p->from = 0;
    } else {
      p->back = FALSE;
      p->angle = 128;
      p->from = 16;
    }
    p->out = FALSE;
    p->reach = 0;
  } else {
    setUp(p, PARTS(8));
    for (i = 0; i < 6 - s->work[1]; i++) {
      UpdateSpriteAnimation(p);
      UpdateSpriteAnimation(p);
    }
    SET_XFLIP(p, FALSE);
    INIT_BODY(p, sLink, 1, NULL);
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Claw_Update(p);
}

// 0x0809f4d8
static void Link_Update(struct Claw* p) {
  struct Entity* s = &p->s;
  struct Claw* claw = (struct Claw*)s->unk_28;
  if (gone(&claw->s)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Claw_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  s->coord.x = claw->pivot.x + s->work[1] * (((claw->s).coord.x - claw->pivot.x) / 12);
  s->coord.y = claw->pivot.y + s->work[1] * (((claw->s).coord.y - claw->pivot.y) / 12);
}

// 0x0809f320: reaches out to 64 px, swings 112 steps of angle back and forth
static void Claw_Update(struct Claw* p) {
  struct Entity* s = &p->s;
  struct Entity* boss = s->unk_28;
  u8 i;
  if (s->work[0] != 0) {
    Link_Update(p);
    return;
  }
  if (gone(boss) || boss->mode[1] == RAPTOR_RETURN) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Claw_Die(p);
    return;
  }
  UpdateSpriteAnimation(p);
  p->pivot.x = FACING_RIGHT(boss) ? boss->coord.x + s->unk_coord.x : boss->coord.x - s->unk_coord.x;
  p->pivot.y = boss->coord.y - s->unk_coord.y;
  s->coord.x = p->pivot.x + COS(p->angle) * p->reach / 256;
  s->coord.y = p->pivot.y + SIN(p->angle) * p->reach / 256;
  switch (s->mode[1]) {
    case 0:
      UpdateSpriteAnimation(p);
      if (IsSpriteAnimEnd(p)) s->mode[1]++;
      break;
    case 1:
      SetSpriteAnimation(p, PARTS(6));
      for (i = 1; i < 10; i += 2) createClaw(s, 1, i);
      s->mode[1]++;
      FALLTHROUGH;
    case 2:
      UpdateSpriteAnimation(p);
      p->reach += 0x200;
      if (p->reach <= PIXEL(64)) break;
      p->out = TRUE;
      s->mode[1]++;
      break;
    case 3:
      UpdateSpriteAnimation(p);
      if (p->back) {
        if (++p->angle > p->from + 112) p->back = FALSE;
      } else if (--p->angle < p->from) {
        p->back = TRUE;
      }
      break;
  }
}

static void Claw_Die(struct Claw* p) { SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------
// clang-format off
static const struct Collision sBody[5] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 4, 0x00000000, {-0xf00, -0x2800, 0x1000, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x2200, -0x2a00, 0x5a00, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, -0x1200, 0x2200, 0x2000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x800, -0x3800, 0x2c00, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x1a00, -0x4600, 0x1600, 0x800}},
};
static const struct Collision sDash[6] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 5, 0x00000000, {-0xf00, -0x2800, 0x800, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 4, 0x00000001, {0x2200, -0x2a00, 0x5a00, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 3, 0x00000001, {0x0, -0x2000, 0x2200, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x800, -0x3800, 0x2c00, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {0x1a00, -0x4600, 0x1600, 0x800}},
    {DDP, FACTION_ENEMY, 2, 3, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x1400, -0x1200, 0x2200, 0x1000}},
};
static const struct Collision sSwoop[1] = {
    {DRP, FACTION_ENEMY, 2, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}},
};
static const struct Collision sSwoopNear[3] = {
    {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 2, 0x00000001, {0x0, 0x1000, 0x3200, 0x4800}},
    {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 1, 0x00000001, {-0x4800, 0x200, 0x6400, 0x1000}},
    {DDP, FACTION_ENEMY, 2, 5, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x4800, 0x200, 0x6400, 0x1000}},
};
static const struct Collision sDroneBody[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {-0x200, 0x0, 0x1600, 0xa00}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {-0x200, 0x0, 0x1600, 0xa00}},
};
static const struct Collision sOrbBody[2] = {
    {DDP, FACTION_ENEMY, 0, 3, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x1a00, 0x1a00}},
    {DRP, FACTION_ENEMY, 0, 3, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1a00, 0x1a00}},
};
static const struct Collision sTornado[1] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1e00, 0x1000}},
};
static const struct Collision sClaw[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1000, 0x1000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
static const struct Collision sLink[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x800, 0x800}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}},
};
// clang-format on

#endif  // AP
