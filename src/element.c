#include "element.h"

#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "vfx/element_effect.h"

// エレメントチップのエフェクト(炎, 氷, 電撃)のグラフィックデータの読み込みを管理する
// 氷のエフェクトのグラフィックは常にロードされる(エレメントチップの攻撃以外でも氷のエフェクトは使われるため)

void InitElFxManager(void) {
  gElFxManager.current = 0;
  RequestElementEffectGraphic(ELFX_NONE);
  gElFxManager.delay = 0;
  LOAD_STATIC_GRAPHIC(SM028_ICE_EFFECT);  // 氷のエフェクトのグラフィックは常にロードされる
}

void UpdateElFxManager(void) {
  u32 n;

  if (gElFxManager.delay != 0) {
    gElFxManager.delay--;
    return;
  }
  if (gElFxManager.requested != gElFxManager.current) {
    gElFxManager.current = gElFxManager.requested;
    if (gElFxManager.requested != ELFX_NONE) {
      n = 25 + gElFxManager.current;
      REQUEST_STATIC_GRAPHIC(n);
    }
  }
}

void RequestElementEffectGraphic(enum ElemFX elem_fx) {
  gElFxManager.requested = elem_fx;
  return;
}

void ReloadElementEffectGraphic(void) {
  if (gElFxManager.current != 0) {
    u32 n = 25 + gElFxManager.current;
    LOAD_STATIC_GRAPHIC(n);
  }
  if (gElFxManager.current != ELFX_ICE) {
    LOAD_STATIC_GRAPHIC(SM028_ICE_EFFECT);
  }
}

static const ALIGNED(4) u8 sWeakElements[34][4] = {
    {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
};

// 0x0835e01c
static const Coords32 Coord_ARRAY_0835e01c[7] = {
    {0x00000000, 0x00000000}, {-0x00001C00, 0x00000000}, {0x00001C00, 0x00000000}, {-0x00000E00, -0x00001C00}, {0x00000E00, -0x00001C00}, {-0x00000E00, 0x00001C00}, {0x00000E00, 0x00001C00},
};

// 0x0835e054
static const Coords32 Coord_ARRAY_0835e054[4] = {{-PIXEL(14), -PIXEL(14)}, {PIXEL(14), -PIXEL(14)}, {-PIXEL(14), PIXEL(14)}, {PIXEL(14), PIXEL(14)}};

struct ElementEffect* CreateThunderEffect(struct Entity* e, Coords32* c, u8 r2);
struct ElementEffect* CreateFlameEffect(struct Entity* e, Coords32* c, u8 r2);
struct ElementEffect* CreateIceEffect(struct Entity* e, Coords32* c, u8 r2);

// Entityに属性攻撃のエフェクト(氷や電撃)をつける関数
NON_MATCH struct Entity* ApplyElementEffect(u8 idx, Object* p, const Coords32* base) {
#if MODERN
  struct ElementEffect* fx = NULL;
  Coords32 c = {
      .x = base->x,
      .y = base->y,
  };

  u8 elfx = ELFX_NONE;
  if ((p->body).elemented == 1) {
    elfx = ELFX_THUNDER;
  } else if ((p->body).elemented == 2) {
    elfx = ELFX_FIRE;
  } else if ((p->body).elemented == 3) {
    elfx = ELFX_ICE;
  }

  if (sWeakElements[idx][elfx] != 0) {
    if (idx < 7) {
      if (elfx == ELFX_THUNDER) {
        fx = CreateThunderEffect((void*)p, &c, 90);
      } else if (elfx == ELFX_FIRE) {
        c.x += PIXEL(6), c.y -= PIXEL(12);
        fx = CreateFlameEffect((void*)p, &c, 90);
        c.x -= PIXEL(14), c.y += PIXEL(6), CreateFlameEffect((void*)p, &c, 90);
        c.x += PIXEL(16), c.y += PIXEL(8), CreateFlameEffect((void*)p, &c, 90);
        c.x -= PIXEL(10), c.y += PIXEL(2), CreateFlameEffect((void*)p, &c, 90);
      } else if (elfx == ELFX_ICE) {
        c.x += PIXEL(6), c.y -= PIXEL(12);
        fx = CreateIceEffect((void*)p, &c, 90);
        c.x -= PIXEL(14), c.y += PIXEL(6), CreateIceEffect((void*)p, &c, 90);
        c.x += PIXEL(16), c.y += PIXEL(8), CreateIceEffect((void*)p, &c, 90);
        c.x -= PIXEL(10), c.y += PIXEL(2), CreateIceEffect((void*)p, &c, 90);
      }
    } else {
      u8 lifetime = 30;

      if (elfx == ELFX_THUNDER) {
        Coords32 _c;
        s32 i;
        for (i = 0; i < (s32)ARRAY_COUNT(Coord_ARRAY_0835e01c); i++) {
          _c.x = c.x + (Coord_ARRAY_0835e01c[i]).x;
          _c.y = c.y + (Coord_ARRAY_0835e01c[i]).y;
          if (fx == NULL) {
            fx = CreateThunderEffect((void*)p, &_c, lifetime);
          } else {
            CreateThunderEffect((void*)p, &_c, lifetime);
          }
        }
      } else if (elfx == ELFX_FIRE) {
        Coords32 _c;
        s32 i;
        for (i = 0; i < (s32)ARRAY_COUNT(Coord_ARRAY_0835e054); i++) {
          _c.x = c.x + (Coord_ARRAY_0835e054[i]).x;
          _c.y = c.y + (Coord_ARRAY_0835e054[i]).y;
          _c.x += PIXEL(6), _c.y -= PIXEL(12);
          if (fx == NULL) {
            fx = CreateFlameEffect((void*)p, &_c, lifetime);
          } else {
            CreateFlameEffect((void*)p, &_c, lifetime);
          }
          _c.x -= PIXEL(14), _c.y += PIXEL(6), CreateFlameEffect((void*)p, &_c, lifetime);
          _c.x += PIXEL(16), _c.y += PIXEL(8), CreateFlameEffect((void*)p, &_c, lifetime);
          _c.x -= PIXEL(10), _c.y += PIXEL(2), CreateFlameEffect((void*)p, &_c, lifetime);
        }
      } else if (elfx == ELFX_ICE) {
        Coords32 _c;
        s32 i;
        for (i = 0; i < (s32)ARRAY_COUNT(Coord_ARRAY_0835e054); i++) {
          _c.x = c.x + (Coord_ARRAY_0835e054[i]).x;
          _c.y = c.y + (Coord_ARRAY_0835e054[i]).y;
          _c.x += PIXEL(6), _c.y -= PIXEL(12);
          if (fx == NULL) {
            fx = CreateIceEffect((void*)p, &_c, lifetime);
          } else {
            CreateIceEffect((void*)p, &_c, lifetime);
          }
          _c.x -= PIXEL(14), _c.y += PIXEL(6), CreateIceEffect((void*)p, &_c, lifetime);
          _c.x += PIXEL(16), _c.y += PIXEL(8), CreateIceEffect((void*)p, &_c, lifetime);
          _c.x -= PIXEL(10), _c.y += PIXEL(2), CreateIceEffect((void*)p, &_c, lifetime);
        }
      }
    }

    if (fx != NULL) {
      if (elfx == ELFX_THUNDER) {
        PlaySound(SE_ELECTRIC);
        (p->body).invincibleTime += 30;
      }
      if (elfx == ELFX_FIRE) {
        PlaySound(SE_FLAME);
        return NULL;
      }
      if (elfx == ELFX_ICE) {
        PlaySound(SE_ICE_40);
        (p->body).invincibleTime += 30;
      }
    }
  }

  return (void*)fx;
#else
  INCCODE("asm/wip/ApplyElementEffect.inc");
#endif
}

bool32 isKilled(struct Entity* p) {
  if (p != NULL) {
    return 1 < p->mode[0];
  }
  return TRUE;
}
