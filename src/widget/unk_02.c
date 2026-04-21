#include "game.h"
#include "global.h"
#include "motion.h"
#include "widget.h"

struct Widget2 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u16 px;
  u16 py;
  u8 unk_78[12];
};
static_assert(sizeof(struct Widget2) == sizeof(struct Widget));

static void MenuComp2_Init(struct Widget2* w);
static void MenuComp2_Update(struct Widget2* w);
static void MenuComp2_Die(struct Entity* p);

// clang-format off
const WidgetRoutine gMenuComp2Routine = {
    [ENTITY_INIT] =      (void*)MenuComp2_Init,
    [ENTITY_UPDATE] =    (void*)MenuComp2_Update,
    [ENTITY_DIE] =       (void*)MenuComp2_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWidget,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* CreateMenuComp2(struct GameState* g, u8 kind, u8 r2) {
  struct Entity* w = AllocEntityFirst(gWidgetHeaderPtr);
  if (w != NULL) {
    w->taskCol = 16;
    INIT_WIDGET_ROUTINE(w, 2);
    w->tileNum = 0, w->palID = 0;
    w->unk_28 = (void*)g;
    w->work[0] = kind, w->work[1] = r2;
  }
  return w;
}

// --------------------------------------------

static void MenuComp2_Init(struct Widget2* w) {
  static const motion_t sMotions[2] = {
      MOTION(SM014_CHIPICON, 11),
      MOTION(SM014_CHIPICON, 24),
  };  // 0x08372044

  SET_WIDGET_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  (w->s).flags |= DISPLAY;
  (w->s).flags |= FLIPABLE;
  SetMotion(&w->s, sMotions[(w->s).work[0]]);
  (w->s).spr.xflip = FALSE;
  (w->s).spr.oam.xflip = FALSE;
  (w->s).flags &= ~X_FLIP;
  (w->s).spr.oam.priority = 0;
  w->unk_78[0] = 0;
  MenuComp2_Update((void*)w);
}

static void MenuComp2_Update(struct Widget2* w) {
  UpdateMotionGraphic(&w->s);
  if (w->unk_78[0]) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    SET_WIDGET_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }

  (w->s).coord.x = w->px * PIXEL(1);
  (w->s).coord.y = w->py * PIXEL(1);
  if ((w->s).work[0] == 0) {
    const u16* bg1ofs = gVideoRegBuffer.bgofs[1];
    if (bg1ofs[0] > 0x100) {
      (w->s).coord.x += PIXEL(512);
    }
  }
}

static void MenuComp2_Die(struct Entity* p) { SET_WIDGET_ROUTINE(p, ENTITY_EXIT); }
