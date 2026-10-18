#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "zero.h"

#if AP

/*
  Charged Recoil Rod hit on the Zero 2 enemies.
  Only applies to enemies that could be pulled by the chainrod.
*/

static const struct Collision sFlying = {  // Same as the Pantheon Hunter's sCollisions[2].
  kind : DDP,
  faction : FACTION_NEUTRAL,
  damage : 2,
  atkType : 0x00,
  comboLv : 0x00,
  remaining : 0,
  layer : 0x00000001,
  range : {-0x0200, -0x1000, 0x1000, 0x1000},
};

bool32 ApRecoilHit(Object* p) {
  return ((p->body).status & (BODY_STATUS_RECOILED | BODY_STATUS_WHITE)) == (BODY_STATUS_RECOILED | BODY_STATUS_WHITE);
}

// Returns TRUE once it hits a wall
bool32 ApRecoilFly(Object* p) {
  struct Entity* s = &p->s;

  if (s->mode[2] == 0) {
    s32 dx = s->coord.x - (pZero2->s).coord.x;
    s32 dy = s->coord.y - PIXEL(24) - (pZero2->s).coord.y;
    s32 len = Sqrt((dx >> 8) * (dx >> 8) + (dy >> 8) * (dy >> 8));
    if (len != 0) {
      s->d.x = dx / len * 6;
      s->d.y = dy / len * 6;
    } else {
      s->d.x = ((pZero2->s).flags & X_FLIP) ? PIXEL(6) : -PIXEL(6);
      s->d.y = 0;
    }
    SET_XFLIP(p, s->d.x <= 0);
    SetDDP(&p->body, &sFlying);
    s->mode[2]++;
  }

  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  return FUN_080098a4(s->coord.x + s->d.x, s->coord.y) != 0 ||
         FUN_080098a4(s->coord.x + s->d.x, s->coord.y - PIXEL(24)) != 0;
}

#endif  // AP
