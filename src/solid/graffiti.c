#include "collision.h"
#include "global.h"
#include "solid.h"

// 改造カードでベースに出現する 絵 と 落書き

enum Graffiti {
  GRAFFITI_MMBN = 0,  // MMBNのロックマンの絵
  GRAFFITI_ZERO1,     // ゼロの落書き
  GRAFFITI_CIEL1,     // シエルの落書き
  GRAFFITI_ZERO2,     // ゼロの落書き (ZERO1 と酷似した落書き + "ぜろ"という文字が入っている)
  GRAFFITI_CIEL2,     // シエルの絵(かわいい)
};

static void Graffiti_Init(Object* p);
static void Graffiti_Update(struct Entity* p);
static void Graffiti_Die(struct Entity* p);

// clang-format off
const SolidRoutine gGraffitiRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Graffiti_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Graffiti_Update,
    [ENTITY_DIE] =       (SolidFunc)Graffiti_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Graffiti_Init(Object* p) {
  static const motion_t sMotions[5] = {
      MOTION(SM162_PAINTING_MMBN, 0), MOTION(SM163_GRAFFITI_ZERO1, 0), MOTION(SM164_GRAFFITI_CIEL, 0), MOTION(SM165_GRAFFITI_ZERO2, 0), MOTION(SM166_PAINTING_CIEL, 0),
  };  // 0x08371888

  // clang-format off
  static const u16 sFlags[] = {
      [GRAFFITI_MMBN] = 91,
      [GRAFFITI_ZERO1] = 108,
      [GRAFFITI_CIEL1] = 108,
      [GRAFFITI_ZERO2] = 108,
      [GRAFFITI_CIEL2] = 91,
  };  // 0x08371892
  // clang-format on

  if (!FLAG(gSystemSavedataManager.flags, sFlags[(p->s).work[0]])) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, sMotions[(p->s).work[0]]);
  SET_XFLIP(p, FALSE);
  (p->s).taskCol = 31;
  if ((p->s).work[0] == GRAFFITI_CIEL2) {
    (p->s).coord.x -= PIXEL(4);
    (p->s).coord.y -= PIXEL(4);
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Graffiti_Update((void*)p);
}

static void Graffiti_Update(struct Entity* p) { UpdateMotionGraphic(p); }

static void Graffiti_Die(struct Entity* p) { SET_SOLID_ROUTINE(p, ENTITY_EXIT); }
