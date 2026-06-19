#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"

// ファントムの出すオブジェクト?

void FUN_080c4c2c(s32 x, s32 y, s32 amplitude, u8 theta);
void CreateGhost18(Coords32* c, u8 kind, bool8 xflip, u8 r3);

void Enemy59_Init(struct Enemy* p);
void Enemy59_Update(struct Enemy* p);
void Enemy59_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEnemy59Routine = {
    [ENTITY_INIT] =      Enemy59_Init,
    [ENTITY_UPDATE] =    Enemy59_Update,
    [ENTITY_DIE] =       Enemy59_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_08091280(struct Entity* p) {
  s32 x, y, amplitude;
  u8 theta;
  x = (p->coord).x + PIXEL((RANDOM(RNG_0202f388) & 0x1F) - 16);
  y = (p->coord).y - PIXEL(-RANDOM(RNG_0202f388) % 48);
  amplitude = 0x100;
  theta = 0x80 | (RANDOM(RNG_0202f388) & 0x7F);
  FUN_080c4c2c(x, y, amplitude, theta);
}

void FUN_0809130c(struct Entity* e, u8 idx) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_59);
    (p->coord).x = (e->coord).x, (p->coord).y = (e->coord).y;
    if (idx < 4) {
      s32 x = (idx - 2) * PIXEL(48) + PIXEL(24);
      (p->unk_coord).x = (e->coord).x + x;
    }
    if (idx > 4) {
      s32 x = (idx - 7) * PIXEL(48) + PIXEL(24);
      (p->coord).x = (e->coord).x + x;
    }
    p->unk_28 = e;
    InitNonAffineMotion(p);
    ResetDynamicMotion(p);
    (p->spr).sprites = (*(void**)&e->kind);
    {
      u8 palID = *((u8*)e + 0x15);
      (p->spr).oam.paletteNum = palID >> 4;
    }
    p->work[0] = idx;
  }
}

INCASM("asm/enemy/unk_59.inc");

// 0x083697F4
static const struct SlashedEnemy sSlashedEnemies[4] = {
    {
      m : 0x1306,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0080, -0x0500},
      unk_coord_0c : {0x00FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1307,
      unk_02 : {254, 17},
      c : {0x0000, 0x0000},
      d : {0x0080, -0x0200},
      unk_coord_0c : {0x007F, 0x007F},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1308,
      unk_02 : {254, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0300},
      unk_coord_0c : {0x01FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1304,
      unk_02 : {16, 4},
      c : {0x0800, -0x1800},
      d : {-0x0080, -0x0100},
      unk_coord_0c : {0x0000, 0x0000},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
};

// 0x08369864
static const struct Collision sCollisions[14] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 3,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 2,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : 8,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : 8,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
};

// --------------------------------------------

void FUN_08091810(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
};
// clang-format on

void FUN_08091814(struct Enemy* p);
void FUN_080918ec(struct Enemy* p);
void FUN_08091980(struct Enemy* p);
void FUN_08091ab0(struct Enemy* p);
void FUN_08091b60(struct Enemy* p);
void FUN_08091c54(struct Enemy* p);
void FUN_08091d0c(struct Enemy* p);
void FUN_08091da4(struct Enemy* p);
void FUN_08091e58(struct Enemy* p);
void FUN_08091f00(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_08091814,
    FUN_080918ec,
    FUN_08091980,
    FUN_08091ab0,
    FUN_08091b60,
    FUN_08091c54,
    FUN_08091d0c,
    FUN_08091da4,
    FUN_08091e58,
    FUN_08091f00,
};
// clang-format on

// --------------------------------------------

void FUN_08091fa8(struct Enemy* p);
void FUN_080921c8(struct Enemy* p);
static void FUN_080922e0(struct Entity* p);
static void FUN_080923ec(Object* p);

static const EnemyFunc sDeads[4] = {
    (void*)FUN_08091fa8,
    (void*)FUN_080921c8,
    (void*)FUN_080922e0,
    (void*)FUN_080923ec,
};

NON_MATCH static void FUN_080922e0(struct Entity* p) {
#if MODERN
  switch (p->mode[2]) {
    case 0: {
      InitNonAffineMotion(p);
      SET_XFLIP(p, p->work[3]);
      SetSpriteAnimation(p, MOTION(SM019_PANTHEON_HUNTER, 3));  // 分身のハズレ枠
      p->work[2] = 18;
      p->mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateSpriteAnimation(p);
      p->work[2]--;
      if ((p->work[2] & 3) == 0) FUN_08091280(p);
      if (p->work[2] == 0) p->mode[2]++;
      break;
    }

    case 2: {
      p->work[2] = 0;
      p->mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      UpdateSpriteAnimation(p);
      if (p->work[2] == 0) PlaySound(SE_ZAKO_EXPLODE);
      p->work[2]++;
      {
        register Coords32* c asm("r4") = &p->coord;
        CreateGhost18(c, 0, (p->flags & X_FLIP) != 0, p->work[3]);
        {
          register const struct SlashedEnemy* tmp asm("r6") = &sSlashedEnemies[3];
          u8 work3 = p->work[3];
          if (p->flags & X_FLIP) work3 |= p->flags & X_FLIP;
          CreateSlashedEnemy(c, tmp, 0, work3);
        }
      }
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
    }
    default: {
      break;
    }
  }
#else
  INCCODE("asm/wip/FUN_080922e0.inc");
#endif
}

static void FUN_080923ec(Object* p) {
  Coords32 c;
  EXIT_BODY(p);
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(8);
  CreateSmoke(1, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

// 0x08369a14
static const u8 u8_ARRAY_08369a14[16] = {
    1, 1, 1, 1, 2, 5, 5, 5, 5, 0, 1, 2, 6, 0, 0, 0,
};
