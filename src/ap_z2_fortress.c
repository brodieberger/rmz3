#include "ap.h"
#include "ap_import.h"
#include "boss.h"
#include "collision.h"
#include "definition.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "palette_animation.h"
#include "projectile.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's boss 20, the Power Room's flying fortress. Two arms and two thrusters ride it.
  work0: side, 1 in both of its rooms
*/

struct Fortress {
  OBJECT_HDR;
  u32 signal;  // 0xB4, read by its arms and thrusters
  s32 homeX;   // 0xB8
  s32 top;     // 0xBC
  u8 low;      // 0xC0
  bool8 stop;  // 0xC1
  u8 rounds;   // 0xC2
  u8 smoke;    // 0xC3
  u8 _c4[4];
  s32 savedY;  // 0xC8
  u8 alt;      // 0xCC
  u8 _cd[23];
};
static_assert(sizeof(struct Fortress) == sizeof(struct Boss));

#define LIFT (1 << 0)
#define DIVE (1 << 1)
#define ARMS_OUT (1 << 2)
#define SLAM (1 << 3)
#define HIDE_UPPER (1 << 5)
#define HIDE_LOWER (1 << 6)
#define SPARKS_UPPER (1 << 7)
#define SPARKS_LOWER (1 << 8)
#define SWING (1 << 9)
#define THROW_UPPER (1 << 10)
#define THROW_LOWER (1 << 11)
#define HIGH (1 << 12)

#define FORT(n) MOTION(AP_SHEET_Z2_FORTRESS, (n))
#define FORTRESS(s) ((struct Fortress*)(s)->unk_28)
#define GLOW_ID (0x8000 | 58)
#define FORTRESS_PALETTE 640

extern const PlttAnimData gApZ2Plant_PlttAnim58;
extern const AnimCmd* const gApZ2Plant_PlttAnimScript58[];

enum {
  FORTRESS_START,
  FORTRESS_HOVER,
  FORTRESS_CHASE,
  FORTRESS_FIRE,
  FORTRESS_RISE,
  FORTRESS_ARMS,
  FORTRESS_DROP,
  FORTRESS_RETURN,
  FORTRESS_SWING,
  FORTRESS_WAIT,
};

static const struct Collision sBody[2];
static const struct PreloadEntity sSheet = {AP_SHEET_Z2_FORTRESS, 0, 512, 4, 0, AP_PRELOAD_SHEET, 0};

static void Fortress_Init(struct Fortress* p);
static void Fortress_Update(struct Fortress* p);
static void Fortress_Die(struct Fortress* p);
static struct Entity* createArm(struct Entity* fortress, struct Entity* pod, u8 low);
static void createJets(struct Entity* fortress, u8 low);
static void createBall(struct Entity* fortress, Coords32* at);

// clang-format off
const BossRoutine gApZ2FortressRoutine = {
    [ENTITY_INIT] =      (BossFunc)Fortress_Init,
    [ENTITY_UPDATE] =    (BossFunc)Fortress_Update,
    [ENTITY_DIE] =       (BossFunc)Fortress_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void setMode(struct Entity* s, u8 mode) {
  s->mode[1] = mode;
  s->mode[2] = 0;
}

// 0x08061d50
static void Fortress_Init(struct Fortress* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sSheet);
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  p->homeX = s->coord.x - PIXEL(94) + s->work[0] * PIXEL(188);
  p->top = s->coord.y - PIXEL(16);
  p->signal = 0;
  p->low = 0;
  p->stop = FALSE;
  p->rounds = 0;
  p->smoke = 0;
  p->alt = 0;
  SetSpriteAnimation(p, FORT(0));
  ApStartPaletteAnimation(GLOW_ID, &gApZ2Plant_PlttAnim58, gApZ2Plant_PlttAnimScript58, FORTRESS_PALETTE);
  ResetBossBody((struct Boss*)p, sBody, 80);
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  Fortress_Update(p);
}

static const BossFunc sStates[10];

// 0x08061e4c
static void Fortress_Update(struct Fortress* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  if ((p->body).hp < 40 && ++p->smoke % ((p->body).hp + 4) == 0) {
    at.x = s->coord.x - PIXEL(24) + PIXEL(RANDOM(RNG_0202f388) % 48);
    at.y = s->coord.y - PIXEL(40) + PIXEL(RANDOM(RNG_0202f388) % 80);
    CreateSmoke(3, &at);
  }
  if ((((p->body).status & BODY_STATUS_DEAD) || (p->body).hp == 0) &&
      !(gStageRun.missionStatus & MISSION_PLAYER_DEAD)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    Fortress_Die(p);
    return;
  }
  StepPaletteAnimation(GLOW_ID);
  sStates[s->mode[1]]((struct Boss*)p);
}

static void clampHeight(struct Fortress* p) {
  struct Entity* s = &p->s;
  if (s->coord.y < p->top) {
    s->coord.y = p->top;
    p->stop = TRUE;
  }
  if (s->coord.y > p->top + PIXEL(240)) {
    s->coord.y = p->top + PIXEL(240);
    p->stop = TRUE;
  }
}

// 0x080620d0
static void chase(struct Fortress* p) {
  struct Entity* s = &p->s;
  s32 target = (pZero2->s).coord.y - PIXEL(48) + p->low * PIXEL(64);
  s32 ay;
  if ((u32)(target - s->coord.y + PIXEL(4)) > PIXEL(8) && !p->stop) {
    if (s->coord.y > target) {
      ay = s->coord.y < p->top + PIXEL(24) ? 32 : -16;
    } else {
      ay = s->coord.y > p->top + PIXEL(216) ? -32 : 16;
    }
    p->signal = (p->signal & ~(LIFT | DIVE)) | (ay < 0 ? LIFT : DIVE);
  } else {
    p->signal &= ~(LIFT | DIVE);
    ay = 0;
    s->d.y = s->d.y * 224 / 256;
  }
  if (ay != 0 && ((u32)(s->d.y + 0x200) <= 0x3FF || (ay < 0 ? s->d.y >= 0 : s->d.y < 0))) s->d.y += ay;
  s->coord.y += s->d.y;
  p->stop = FALSE;
  clampHeight(p);
}

// 0x08062230
static void glide(struct Fortress* p) {
  struct Entity* s = &p->s;
  p->signal &= ~(LIFT | DIVE);
  s->d.y = s->d.y * 224 / 256;
  s->coord.y += s->d.y;
  if (s->coord.y < p->top) s->coord.y = p->top;
  if (s->coord.y > p->top + PIXEL(240)) s->coord.y = p->top + PIXEL(240);
}

// 0x08062280
static void rise(struct Fortress* p) {
  struct Entity* s = &p->s;
  p->signal = (p->signal | LIFT) & ~DIVE;
  if ((u32)(s->d.y + 0x200) <= 0x3FF) s->d.y -= 6;
  s->coord.y += s->d.y;
  p->stop = FALSE;
  if (s->coord.y < p->top) {
    s->coord.y = p->top;
    p->stop = TRUE;
  }
}

// 0x080622d8
static void push(struct Fortress* p) {
  struct Entity* s = &p->s;
  p->signal |= LIFT | DIVE;
  s->d.x += s->work[0] * 32 + 16;
  s->coord.x += s->d.x;
  p->stop = FALSE;
  if (s->work[0] ? s->coord.x > p->homeX - PIXEL(36) : s->coord.x < p->homeX + PIXEL(36)) p->stop = TRUE;
}

// 0x08062340: stop set while still moving
static void back(struct Fortress* p) {
  struct Entity* s = &p->s;
  p->signal &= ~(LIFT | DIVE);
  s->coord.x += (p->homeX + PIXEL(48) - s->work[0] * PIXEL(96) - s->coord.x) * 24 / 256;
  p->stop = FALSE;
  if (s->work[0] ? s->coord.x > p->homeX - 0x2F00 : s->coord.x < p->homeX + 0x2F00) p->stop = TRUE;
}

// 0x080623bc
static void slide(struct Fortress* p) {
  struct Entity* s = &p->s;
  s32 wall = p->homeX + PIXEL(94) - s->work[0] * PIXEL(188);
  s->coord.x += s->d.x;
  p->stop = FALSE;
  if (s->work[0]) {
    s->d.x += 16;
    if (s->coord.x < wall + PIXEL(48)) p->signal |= SPARKS_UPPER | SPARKS_LOWER;
    if (s->coord.x < wall) {
      s->coord.x = wall;
      p->stop = TRUE;
    }
  } else {
    s->d.x -= 16;
    if (s->coord.x > wall - PIXEL(48)) p->signal |= SPARKS_UPPER | SPARKS_LOWER;
    if (s->coord.x > wall) {
      s->coord.x = wall;
      p->stop = TRUE;
    }
  }
}

static void bob(struct Fortress* p) {
  struct Entity* s = &p->s;
  s->work[3] += 4;
  s->coord.y = p->savedY + SIN(s->work[3]) * 640 / 256;
}

// 0x08062484
static void Fortress_Start(struct Fortress* p) {
  struct Entity* s = &p->s;
  struct Entity* pod;
  u8 low;
  switch (s->mode[2]) {
    case 0:
      s->renderPrio = 25;
      for (low = 0; low < 2; low++) {
        pod = createArm(s, NULL, low);
        createArm(s, pod, low);
        createJets(s, low);
      }
      SET_XFLIP(p, s->work[0]);
      SetSpriteAnimation(p, FORT(0));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (s->scriptEntity->flags & 1) s->mode[2]++;
      break;
    case 2:
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 3:
      if (++s->work[2] > 47) s->mode[2]++;
      break;
    case 4:
      s->mode[2]++;
      // fallthrough
    case 5:
      UpdateSpriteAnimation(p);
      if (!(gStageRun.vm.active & VM_ACTIVE)) setMode(s, FORTRESS_HOVER);
      break;
  }
}

// 0x080625ac
static void Fortress_Hover(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      p->savedY = s->coord.y;
      p->stop = FALSE;
      SetSpriteAnimation(p, FORT(0));
      s->work[2] = 60;
      s->work[3] = 0;
      s->d.y = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      if (--s->work[2] == 0) {
        if (p->rounds > 1) {
          p->rounds = 0;
          p->alt = (p->alt + 1) & 1;
          setMode(s, p->alt ? FORTRESS_WAIT : FORTRESS_RISE);
        } else {
          setMode(s, FORTRESS_CHASE);
        }
      }
      bob(p);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08062658
static void Fortress_Chase(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      p->stop = FALSE;
      p->low ^= 1;
      if (p->low) {
        if (s->coord.y > p->top + PIXEL(192)) p->low = 0;
      } else if (s->coord.y < p->top + PIXEL(48)) {
        p->low = 1;
      }
      s->d.y = 0;
      s->work[2] = 120;
      s->mode[2]++;
      // fallthrough
    case 1:
      chase(p);
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      glide(p);
      UpdateSpriteAnimation(p);
      s->work[2]--;
      if ((u32)(s->d.y + 16) < 32) {
        p->signal &= ~(LIFT | DIVE);
        setMode(s, FORTRESS_FIRE);
      }
      break;
  }
}

// 0x08062ee8, as Zero 2 runs it: a frame, then the arms
static void Fortress_Wait(struct Fortress* p) {
  p->signal &= ~(LIFT | DIVE);
  setMode(&p->s, FORTRESS_ARMS);
}

// 0x0806271c
static void Fortress_Fire(struct Fortress* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_FORTRESS_SHOTS);
      s->work[2] = 32;
      p->savedY = s->coord.y;
      s->work[3] = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if ((s->work[2] & 3) == 0) {
        at.x = s->coord.x + s->work[0] * PIXEL(72) - PIXEL(38) + (RANDOM(RNG_0202f388) & 0x3FF);
        at.y = s->coord.y - PIXEL(16) + (RANDOM(RNG_0202f388) & 0x1FFF);
        createBall(s, &at);
        if (s->work[2] == 0) s->mode[2]++;
      }
      bob(p);
      s->work[2]--;
      break;
    case 2:
      s->work[2] = 50;
      s->mode[2]++;
      // fallthrough
    case 3:
      if (--s->work[2] == 0) setMode(s, ++p->rounds > 1 ? FORTRESS_HOVER : FORTRESS_CHASE);
      bob(p);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x0806287c
static void Fortress_Rise(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      p->stop = FALSE;
      s->d.y = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      rise(p);
      UpdateSpriteAnimation(p);
      if (p->stop) s->mode[2]++;
      break;
    case 2:
      p->signal &= ~(LIFT | DIVE);
      s->work[2] = 30;
      s->mode[2]++;
      // fallthrough
    case 3:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) {
        p->signal |= SLAM;
        setMode(s, FORTRESS_ARMS);
      }
      break;
  }
}

// 0x08062910
static void Fortress_Arms(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->work[2] = 8;
      p->signal |= ARMS_OUT;
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (--s->work[2] == 0) s->mode[2]++;
      break;
    case 2:
      s->d.x = 0;
      p->stop = FALSE;
      s->mode[2]++;
      // fallthrough
    case 3:
      UpdateSpriteAnimation(p);
      push(p);
      if (p->stop) {
        p->signal &= ~ARMS_OUT;
        s->mode[2]++;
      }
      UpdateSpriteAnimation(p);
      break;
    case 4:
      back(p);
      if (!p->stop) setMode(s, (p->signal & SLAM) ? FORTRESS_DROP : FORTRESS_SWING);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x080629e4: shakes, then drops to the floor of its range
static void Fortress_Drop(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->unk_coord = s->coord;
      s->work[2] = 32;
      s->mode[2]++;
      // fallthrough
    case 1:
      if ((s->work[2] & 7) > 4) {
        p->signal |= HIDE_UPPER | HIDE_LOWER;
      } else {
        p->signal &= ~(HIDE_UPPER | HIDE_LOWER);
      }
      s->work[2]--;
      s->coord.x = s->unk_coord.x - 0x180 + RANDOM(RNG_0202f388) % 0x300;
      s->coord.y = s->unk_coord.y - 0x180 + RANDOM(RNG_0202f388) % 0x300;
      if (s->work[2] == 0) {
        s->coord = s->unk_coord;
        s->mode[2]++;
      }
      break;
    case 2:
      PlaySound(SE_Z2_RAPTOR_SWOOP);
      p->signal = (p->signal & ~(LIFT | DIVE)) | HIDE_UPPER | HIDE_LOWER;
      s->d.y = 0;
      s->work[2] = 0;
      s->mode[2]++;
      // fallthrough
    case 3:
      s->coord.y += s->d.y;
      s->d.y += 64;
      if (s->d.y > 0x700) s->d.y = 0x700;
      if (s->coord.y > p->top + PIXEL(240)) {
        s->coord.y = p->top + PIXEL(240);
        s->work[2]++;
        p->signal = (p->signal | SPARKS_LOWER | LIFT) & ~HIDE_LOWER;
        if (s->work[2] > 30) {
          p->signal = (p->signal & ~(SPARKS_LOWER | LIFT)) | HIDE_LOWER;
          setMode(s, FORTRESS_RETURN);
        }
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08062b74
static void Fortress_Return(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      s->d.x = 0;
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      push(p);
      if (p->stop) s->mode[2]++;
      UpdateSpriteAnimation(p);
      break;
    case 2:
      s->d.x = 0x300 - s->work[0] * 0x600;
      s->mode[2]++;
      // fallthrough
    case 3:
      UpdateSpriteAnimation(p);
      slide(p);
      if (p->stop) {
        p->signal &= ~(LIFT | DIVE | SPARKS_UPPER | SPARKS_LOWER | HIDE_UPPER | HIDE_LOWER | SLAM);
        setMode(s, FORTRESS_HOVER);
      }
      break;
  }
}

static void ease(struct Entity* s) {
  s->coord.x += (s->unk_coord.x - s->coord.x) / 16;
  s->coord.y += (s->unk_coord.y - s->coord.y) / 16;
}

static void swing(struct Fortress* p, u32 throw) {
  struct Entity* s = &p->s;
  ease(s);
  if (--s->work[3] == 12) p->signal |= throw;
  if (s->work[3] == 0) s->mode[2]++;
  UpdateSpriteAnimation(p);
}

// 0x08062c20: throws its arms at Zero, down the room from its half
static void Fortress_Swing(struct Fortress* p) {
  struct Entity* s = &p->s;
  bool8 high = s->work[2];
  switch (s->mode[2]) {
    case 0:
      high = s->work[2] = s->coord.y < (p->top + PIXEL(240) + p->top) >> 1;
      if (high) {
        p->signal |= HIGH;
      } else {
        p->signal &= ~HIGH;
      }
      s->mode[2]++;
      // fallthrough
    case 1:
      p->signal |= SWING;
      s->unk_coord.x = s->coord.x + PIXEL(6) - s->work[0] * PIXEL(12);
      s->unk_coord.y = s->coord.y + PIXEL(16) - high * PIXEL(32);
      s->work[3] = 25;
      s->mode[2]++;
      // fallthrough
    case 2:
      swing(p, high ? THROW_LOWER : THROW_UPPER);
      break;
    case 3:
      p->signal &= ~(THROW_UPPER | THROW_LOWER);
      s->unk_coord.x += -PIXEL(6) + s->work[0] * PIXEL(12);
      s->unk_coord.y += -PIXEL(52) + high * PIXEL(104);
      s->work[3] = 50;
      s->mode[2]++;
      // fallthrough
    case 4:
      swing(p, high ? THROW_UPPER : THROW_LOWER);
      break;
    case 5:
      p->signal &= ~(THROW_UPPER | THROW_LOWER);
      s->unk_coord.y += PIXEL(3) - high * PIXEL(6);
      s->work[3] = 25;
      s->mode[2]++;
      // fallthrough
    case 6:
      s->coord.x += (s->unk_coord.x - s->coord.x) * 24 / 256;
      s->coord.y += (s->unk_coord.y - s->coord.y) * 24 / 256;
      if (--s->work[3] == 0) {
        s->coord = s->unk_coord;
        if (high ? s->unk_coord.y > p->top + PIXEL(206) : s->unk_coord.y < p->top + PIXEL(34)) {
          s->mode[2]++;
        } else {
          s->mode[2] = 1;
        }
      }
      UpdateSpriteAnimation(p);
      break;
    case 7:
      s->work[3] = 10;
      s->mode[2]++;
      // fallthrough
    case 8:
      if (--s->work[3] == 0) {
        p->signal &= ~SWING;
        setMode(s, FORTRESS_RETURN);
      }
      UpdateSpriteAnimation(p);
      break;
  }
}

static const BossFunc sStates[10] = {
    (BossFunc)Fortress_Start, (BossFunc)Fortress_Hover, (BossFunc)Fortress_Chase, (BossFunc)Fortress_Fire,
    (BossFunc)Fortress_Rise,  (BossFunc)Fortress_Arms,  (BossFunc)Fortress_Drop,  (BossFunc)Fortress_Return,
    (BossFunc)Fortress_Swing, (BossFunc)Fortress_Wait,
};

// 0x08061f6c: sinks into the lava
static void Fortress_Die(struct Fortress* p) {
  struct Entity* s = &p->s;
  switch (s->mode[1]) {
    case 0:
      EXIT_BODY(p);
      if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & VM_ACTIVE)) {
        gStageRun.missionStatus &= ~MISSION_STAY;
        gStageRun.missionStatus |= MISSION_SUCCESS;
      }
      p->signal &= ~(LIFT | DIVE | SLAM | HIDE_UPPER | HIDE_LOWER | SPARKS_UPPER | SPARKS_LOWER | SWING);
      s->mode[1]++;
      // fallthrough
    case 1:
      if (StepPaletteAnimation(GLOW_ID) == ANIM_NEXT_GOTO) {
        RemovePaletteAnimation(GLOW_ID);
        s->mode[1]++;
      }
      break;
    case 2:
      p->signal |= HIDE_UPPER | HIDE_LOWER;
      s->work[2] = 60;
      s->mode[1]++;
      // fallthrough
    case 3:
      if (--s->work[2] == 0) s->mode[1]++;
      break;
    case 4:
      s->d.y = 0;
      s->mode[1]++;
      // fallthrough
    case 5:
      s->d.y += 16;
      s->coord.x += 0x80 - s->work[0] * 0x100;
      s->coord.y += s->d.y;
      if (s->coord.y > p->top + PIXEL(496)) {
        p->signal &= ~(HIDE_UPPER | HIDE_LOWER);
        s->mode[1]++;
        gStageRun.vm.active |= VM_FLAG1;
        PlaySound(SE_Z2_FORTRESS_SINK);
        AppendQuake(3, &s->coord);
      }
      break;
  }
}

// clang-format off
// 0x0833d580
static const struct Collision sBody[2] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x05, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0x3400, 0x4000}},
    {DRP, FACTION_ENEMY, 0, 4, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0, 0x00000000, {-0x1b00, 0x0, 0xa00, 0x1400}},
};
// clang-format on

// --------------------------------------------

/*
  Zero 2's enemy 60, an arm of the fortress.
  work0:
    0 spiked pod
    1 rod between it and the fortress
*/

struct Arm {
  OBJECT_HDR;
  u8 side;    // 0xB4
  u8 low;     // 0xB5
  s16 swayX;  // 0xB6
  u8 _b8[4];
  s16 swayY;  // 0xBC
  u8 _be[6];
};
static_assert(sizeof(struct Arm) == sizeof(struct Enemy));

enum { POD_IDLE, ROD, POD_OUT, POD_SHAKE, POD_WAIT, POD_HELD, POD_THROWN, POD_CAUGHT };

static void Arm_Init(struct Arm* p);
static void Arm_Update(struct Arm* p);
static void Arm_Die(struct Arm* p);

// clang-format off
const EnemyRoutine gApZ2FortressArmRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Arm_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Arm_Update,
    [ENTITY_DIE] =       (EnemyFunc)Arm_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};

// 0x08341658, every other row
static const struct Collision sArmBodies[4] = {
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0xe00, 0xe00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {-0xe00, 0x0, 0x3800, 0xe00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x1a00, 0x1b00}},
    {DDP, FACTION_ENEMY, 0, 4, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x300, 0x0, 0x1600, 0x1900}},
};
// clang-format on

// 0x0834171a, by frame of animations 10 and 11
static const u8 sOutHit[2] = {2, 3};
static const u8 sInHit[2] = {2, 1};

// 0x08087858, 0x080878c4
static struct Entity* createArm(struct Entity* fortress, struct Entity* pod, u8 low) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_FORTRESS_ARM);
    p->work[0] = pod != NULL;
    p->unk_28 = fortress;
    p->unk_2c = pod;
    ((struct Arm*)p)->side = fortress->work[0];
    ((struct Arm*)p)->low = low;
  }
  return p;
}

// 0x080879f8
static void Arm_Init(struct Arm* p) {
  struct Entity* s = &p->s;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->work[0];
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  p->swayX = 0;
  p->swayY = 0;
  Arm_Update(p);
}

static const EnemyFunc sArmModes[8];

// 0x08087a4c
static void Arm_Update(struct Arm* p) {
  struct Entity* s = &p->s;
  if ((FORTRESS(s)->s).mode[0] > ENTITY_UPDATE) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    return;
  }
  sArmModes[s->mode[1]]((struct Enemy*)p);
}

// 0x08087930
static void follow(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  if (f->signal & SWING) return;
  s->coord.x = (f->s).coord.x - PIXEL(48) + p->side * PIXEL(96) + p->swayX;
  p->swayX += (s->unk_coord.x - p->swayX) / 8;
  s->coord.y = (f->s).coord.y - PIXEL(44) + p->low * PIXEL(80) + p->swayY;
  p->swayY += (s->unk_coord.y - p->swayY) / 8;
}

// 0x080879c8
static void holdWall(struct Arm* p) {
  struct Entity* s = &p->s;
  s32 wall = FORTRESS(s)->homeX;
  if (p->side ? s->coord.x > wall : s->coord.x < wall) s->coord.x = wall;
}

// 0x08087b38
static void Pod_Idle(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  switch (s->mode[2]) {
    case 0:
      INIT_BODY(p, &sArmBodies[1], 0, NULL);
      s->invincibleID = (f->s).uniqueID;
      s->unk_coord.x = 0;
      s->unk_coord.y = 0;
      s->work[2] = p->low << 7;
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(6));
      s->mode[2]++;
      // fallthrough
    case 1:
      s->work[2] += 4;
      s->unk_coord.x = COS(s->work[2]);
      s->unk_coord.y = SIN(s->work[2]) * 640 / 256;
      follow(p);
      holdWall(p);
      UpdateSpriteAnimation(p);
      if (f->signal & ARMS_OUT) setMode(s, POD_OUT);
      if (f->signal & SWING) setMode(s, POD_HELD);
      break;
  }
}

// 0x08087c50: halfway between the fortress and its pod
static void Rod(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Entity* f = s->unk_28;
  struct Entity* pod = s->unk_2c;
  s32 x, y;
  switch (s->mode[2]) {
    case 0:
      INIT_BODY(p, &sArmBodies[0], 0, NULL);
      s->invincibleID = f->uniqueID;
      s->renderPrio = 25;
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(5));
      s->mode[2]++;
      // fallthrough
    case 1:
      x = (f->coord.x >> 8) - 25 + p->side * 50 + (pod->coord.x >> 8) + 10 - p->side * 20;
      y = (f->coord.y >> 8) - 33 + p->low * 66 + (pod->coord.y >> 8);
      s->coord.x = PIXEL(x >> 1);
      s->coord.y = PIXEL(y >> 1);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08087d58
static void Pod_Out(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  switch (s->mode[2]) {
    case 0:
      s->unk_coord.x = PIXEL(4) - p->side * PIXEL(8);
      s->unk_coord.y = -PIXEL(4) + p->low * PIXEL(8);
      SetSpriteAnimation(p, FORT(10));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      if (s->motion.state == ANIM_END) s->mode[2]++;
      SetDDP(&p->body, &sArmBodies[sOutHit[s->motion.cmdIdx]]);
      break;
    case 2:
      SetSpriteAnimation(p, FORT(8));
      s->mode[2]++;
      // fallthrough
    case 3:
      UpdateSpriteAnimation(p);
      if (!(f->signal & ARMS_OUT)) s->mode[2]++;
      break;
    case 4:
      PlaySound(SE_Z2_FORTRESS_CLANG);
      SetSpriteAnimation(p, FORT(11));
      s->mode[2]++;
      // fallthrough
    case 5:
      UpdateSpriteAnimation(p);
      if (s->motion.state == ANIM_END) setMode(s, (f->signal & SLAM) ? POD_SHAKE : POD_IDLE);
      SetDDP(&p->body, &sArmBodies[sInHit[s->motion.cmdIdx]]);
      break;
  }
  follow(p);
  holdWall(p);
}

// 0x08087eb8
static void Pod_Shake(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, &sArmBodies[1]);
      s->work[2] = 30;
      SetSpriteAnimation(p, FORT(9));
      s->mode[2]++;
      // fallthrough
    case 1:
      follow(p);
      holdWall(p);
      s->work[2]--;
      UpdateSpriteAnimation(p);
      if (s->work[2] == 0) setMode(s, (f->signal & SLAM) ? POD_WAIT : POD_IDLE);
      break;
  }
}

// 0x08087f30
static void Pod_Wait(struct Arm* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetDDP(&p->body, &sArmBodies[1]);
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(6));
      s->mode[2]++;
      // fallthrough
    case 1:
      follow(p);
      holdWall(p);
      UpdateSpriteAnimation(p);
      if (!(FORTRESS(s)->signal & SLAM)) setMode(s, POD_IDLE);
      break;
  }
}

// 0x08087fc4
static void Pod_Held(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  switch (s->mode[2]) {
    case 0:
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(6));
      s->mode[2]++;
      // fallthrough
    case 1:
      if (f->signal & (p->low ? THROW_LOWER : THROW_UPPER)) setMode(s, POD_THROWN);
      if (!(f->signal & SWING)) setMode(s, POD_IDLE);
      UpdateSpriteAnimation(p);
      break;
  }
}

// 0x08088078: flies out and back to the fortress's wall
static void Pod_Thrown(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Fortress* f = FORTRESS(s);
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, FORT(10));
      s->d.y = (f->signal & HIGH) ? 0x100 : -0x100;
      s->d.x = 0x300 - p->side * 0x600;
      s->unk_coord.x = -48 + p->side * 96;
      s->mode[2]++;
      // fallthrough
    case 1:
      s->coord.x += s->d.x;
      s->d.x += s->unk_coord.x;
      s->coord.y += s->d.y;
      if (p->side ? s->d.x > 0 && s->coord.x > f->homeX : s->d.x < 0 && s->coord.x < f->homeX) {
        PlaySound(SE_Z2_FORTRESS_CLANG);
        s->coord.x = f->homeX;
        setMode(s, POD_CAUGHT);
      }
      UpdateSpriteAnimation(p);
      SetDDP(&p->body, &sArmBodies[sOutHit[s->motion.cmdIdx]]);
      break;
  }
}

// 0x08088178
static void Pod_Caught(struct Arm* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      SetSpriteAnimation(p, FORT(11));
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      SetDDP(&p->body, &sArmBodies[sInHit[s->motion.cmdIdx]]);
      if (s->motion.state == ANIM_END) s->mode[2]++;
      break;
    case 2:
      SetSpriteAnimation(p, FORT(9));
      s->work[2] = 20;
      s->mode[2]++;
      // fallthrough
    case 3:
      if (--s->work[2] == 0) setMode(s, POD_HELD);
      UpdateSpriteAnimation(p);
      break;
  }
}

static const EnemyFunc sArmModes[8] = {
    (EnemyFunc)Pod_Idle,  (EnemyFunc)Rod,      (EnemyFunc)Pod_Out,    (EnemyFunc)Pod_Shake,
    (EnemyFunc)Pod_Wait,  (EnemyFunc)Pod_Held, (EnemyFunc)Pod_Thrown, (EnemyFunc)Pod_Caught,
};

// 0x08087aa4: rides the sinking fortress
static void Arm_Die(struct Arm* p) {
  struct Entity* s = &p->s;
  struct Entity* f = s->unk_28;
  switch (s->mode[2]) {
    case 0:
      if (s->work[0] == 0) SetSpriteAnimation(p, FORT(8));
      s->unk_coord.x = s->coord.x - f->coord.x;
      s->unk_coord.y = s->coord.y - f->coord.y;
      EXIT_BODY(p);
      s->mode[2]++;
      // fallthrough
    case 1:
      UpdateSpriteAnimation(p);
      s->coord.x = f->coord.x + s->unk_coord.x;
      s->coord.y = f->coord.y + s->unk_coord.y;
      if (f->mode[0] == ENTITY_EXIT) SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
  }
}

// --------------------------------------------

/*
  Zero 2's VFX 50, the fortress's thrusters.
  work0:
    0 jet
    1 sparks off the wall
*/

struct Jet {
  struct Entity s;
  u8 side;  // 0x74
  u8 low;   // 0x75
  u8 _76[14];
};
static_assert(sizeof(struct Jet) == sizeof(struct VFX));

enum { JET_IDLE, JET_FIRE, JET_HIDDEN, SPARKS_ON, SPARKS_OFF };

static void Jet_Init(struct Jet* p);
static void Jet_Update(struct Jet* p);

// clang-format off
const VFXRoutine gApZ2FortressJetRoutine = {
    [ENTITY_INIT] =      (VFXFunc)Jet_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Jet_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080ba2f0
static void createJets(struct Entity* fortress, u8 low) {
  u8 kind;
  struct Entity* p;
  for (kind = 0; kind < 2; kind++) {
    p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      INIT_VFX_ROUTINE(p, VFX_Z2_FORTRESS_JET);
      p->work[0] = kind;
      p->unk_28 = fortress;
      ((struct Jet*)p)->side = fortress->work[0];
      ((struct Jet*)p)->low = low;
    }
  }
}

// 0x080ba39c
static void Jet_Init(struct Jet* p) {
  struct Entity* s = &p->s;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  s->mode[1] = s->work[0] ? SPARKS_OFF : JET_IDLE;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  Jet_Update(p);
}

static const VFXFunc sJetModes[5];

// 0x080ba3e4
static void Jet_Update(struct Jet* p) {
  struct Entity* s = &p->s;
  if ((FORTRESS(s)->s).mode[0] > ENTITY_UPDATE) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  sJetModes[s->mode[1]]((struct VFX*)p);
}

static void ride(struct Jet* p) {
  struct Entity* s = &p->s;
  s->coord = (FORTRESS(s)->s).coord;
  UpdateSpriteAnimation(p);
}

// 0x080ba4d4
static void Jet_Idle(struct Jet* p) {
  struct Entity* s = &p->s;
  u32 signal = FORTRESS(s)->signal;
  switch (s->mode[2]) {
    case 0:
      s->flags |= DISPLAY;
      s->renderPrio = 26;
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(p->low ? 3 : 1));
      s->mode[2]++;
      // fallthrough
    case 1:
      if (signal & (p->low ? HIDE_LOWER : HIDE_UPPER)) setMode(s, JET_HIDDEN);
      if (signal & (p->low ? LIFT : DIVE)) setMode(s, JET_FIRE);
      ride(p);
      break;
  }
}

// 0x080ba5c0
static void Jet_Fire(struct Jet* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_GOLEM_SLIDE);
      s->flags |= DISPLAY;
      SetSpriteAnimation(p, FORT(p->low ? 4 : 2));
      s->mode[2]++;
      // fallthrough
    case 1:
      if (!(FORTRESS(s)->signal & (p->low ? LIFT : DIVE))) setMode(s, JET_IDLE);
      ride(p);
      break;
  }
}

// 0x080ba648
static void Jet_Hidden(struct Jet* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  if (!(FORTRESS(s)->signal & (p->low ? HIDE_LOWER : HIDE_UPPER))) setMode(s, JET_IDLE);
}

// 0x080ba680
static void Sparks_On(struct Jet* p) {
  struct Entity* s = &p->s;
  switch (s->mode[2]) {
    case 0:
      PlaySound(SE_Z2_GOLEM_SLIDE);
      s->flags |= DISPLAY;
      SET_XFLIP(p, p->side);
      SetSpriteAnimation(p, FORT(p->low ? 16 : 15));
      s->mode[2]++;
      // fallthrough
    case 1:
      if (!(FORTRESS(s)->signal & (p->low ? SPARKS_LOWER : SPARKS_UPPER))) setMode(s, SPARKS_OFF);
      ride(p);
      break;
  }
}

// 0x080ba73c
static void Sparks_Off(struct Jet* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  if (FORTRESS(s)->signal & (p->low ? SPARKS_LOWER : SPARKS_UPPER)) setMode(s, SPARKS_ON);
}

static const VFXFunc sJetModes[5] = {
    (VFXFunc)Jet_Idle, (VFXFunc)Jet_Fire, (VFXFunc)Jet_Hidden, (VFXFunc)Sparks_On, (VFXFunc)Sparks_Off,
};

// --------------------------------------------

/*
  Zero 2's projectile 47, the fortress's shot. Charges, then flies at Zero.
*/

enum { BALL_APPEAR, BALL_CHARGE, BALL_FLY, BALL_BURST };

static void Ball_Init(struct Entity* s);
static void Ball_Update(struct Entity* s);
static void Ball_Die(struct Entity* s);

// clang-format off
const ProjectileRoutine gApZ2FortressBallRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Ball_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Ball_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Ball_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};

// 0x0834535c, 0x0834532c
static const struct Collision sBall[2] = {
    {DDP, FACTION_ENEMY, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 1, 0x00000001, {0x0, 0x0, 0xc00, 0xc00}},
    {DRP, FACTION_ENEMY, 0, 2, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0xc00, 0xc00}},
};
static const struct Collision sBurst = {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x1000, 0x1000}};
// clang-format on

// 0x080a8b08
static void createBall(struct Entity* fortress, Coords32* at) {
  struct Entity* p = AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    INIT_PROJECTILE_ROUTINE(p, PROJECTILE_Z2_FORTRESS_BALL);
    p->coord = *at;
    p->work[0] = 0;
    p->unk_28 = fortress;
  }
}

// 0x080a8b58
static void Ball_Init(struct Entity* s) {
  SET_PROJECTILE_ROUTINE(s, ENTITY_UPDATE);
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  Ball_Update(s);
}

// 0x080a8bb8
static void Ball_Die(struct Entity* s) { SET_PROJECTILE_ROUTINE(s, ENTITY_EXIT); }

static bool8 burst(struct Entity* s) {
  if (!(((Object*)s)->body.status & BODY_STATUS_WHITE)) return FALSE;
  setMode(s, BALL_BURST);
  return TRUE;
}

// 0x080a8ba0
static void Ball_Update(struct Entity* s) {
  Object* p = (Object*)s;
  struct Zero* z = pZero2;
  s32 dx, dy;
  u32 len;
  u16 at;
  switch (s->mode[1]) {
    case BALL_APPEAR:  // 0x080a8bd0
      if (s->mode[2] == 0) {
        SetSpriteAnimation(s, FORT(12));
        s->mode[2]++;
      }
      UpdateSpriteAnimation(s);
      if (s->motion.state == ANIM_END) setMode(s, BALL_CHARGE);
      break;
    case BALL_CHARGE:  // 0x080a8c10
      if (burst(s)) break;
      if (s->mode[2] == 0) {
        INIT_BODY(s, sBall, 1, NULL);
        s->work[2] = 32;
        SetSpriteAnimation(s, FORT(13));
        s->mode[2]++;
      }
      if (--s->work[2] == 0) setMode(s, BALL_FLY);
      UpdateSpriteAnimation(s);
      break;
    case BALL_FLY:  // 0x080a8c90
      if (burst(s)) break;
      if (s->mode[2] == 0) {
        dx = ((z->s).coord.x - s->coord.x) >> 8;
        dy = ((z->s).coord.y - (s->coord.y + PIXEL(16))) >> 8;
        len = (u16)Sqrt(dx * dx + dy * dy) << 8;
        if (len != 0) {
          s->d.x = (dx << 16) / (s32)len * 2;
          s->d.y = (dy << 16) / (s32)len * 2;
        } else {
          s->d.x = 0x200;
          s->d.y = 0;
        }
        s->work[2] = 192;
        SetSpriteAnimation(s, FORT(13));
        s->mode[2]++;
      }
      s->coord.x += s->d.x;
      s->coord.y += s->d.y;
      s->work[2]--;
      at = FUN_080098a4(s->coord.x, s->coord.y);
      if (((p->body).status & BODY_STATUS_B2) || (at != 0 && at != 0x800F) || s->work[2] == 0) setMode(s, BALL_BURST);
      UpdateSpriteAnimation(s);
      break;
    case BALL_BURST:  // 0x080a8d7c
      if (s->mode[2] == 0) {
        SetDDP(&p->body, &sBurst);
        SetSpriteAnimation(s, FORT(14));
        s->mode[2]++;
      }
      UpdateSpriteAnimation(s);
      if (s->motion.state == ANIM_END) {
        s->flags &= ~(DISPLAY | FLIPABLE);
        EXIT_BODY(s);
        SET_PROJECTILE_ROUTINE(s, ENTITY_DISAPPEAR);
      }
      break;
  }
}

#endif
