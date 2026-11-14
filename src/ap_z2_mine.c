#include "ap.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "metatile.h"
#include "overworld.h"
#include "quake.h"
#include "score.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/ap_z2_songs.h"
#include "constants/entity/weapon.h"
#include "constants/motion/ap_sheet.h"

#if AP

/*
  Zero 2's mine, enemy 77.
  work0:
    0: placed
    1: from spawner, blinks in
*/

struct Mine {
  OBJECT_HDR;
  u8 ring;                       // 0xB4, blast's ring, 2..4
  u8 ringPoint;                  // 0xB5
  bool8 hit;                     // 0xB6, by Zero, counts as kill
  u8 _b7;
  u16 fuse;                      // 0xB8
  u8 _ba[2];
  struct Entity* elementEffect;  // 0xBC
  u8 _c0[4];
};
static_assert(sizeof(struct Mine) == sizeof(struct Enemy));

enum {
  MINE_BLINK_IN,
  MINE_HOME,
  MINE_KNOCKED,
  MINE_ARM,
  MINE_RISE,
  MINE_FALL,
  MINE_BURN,
};

#define ANIM(n) MOTION(AP_SHEET_Z2_MINE, (n))

static const struct Collision sCollisions[2];
static const struct Collision sIntangible;
static const struct Collision sKnocked[2];
static const struct Collision sFalling[2];
static const struct Collision sBurning;
static const struct Collision sBlasts[3];
static const Coords32 sElementCoord = {0, 0};

static void Mine_Init(struct Mine* p);
static void Mine_Update(struct Mine* p);
static void Mine_Die(struct Mine* p);
static void onCollision(struct Body* body, Coords32* r1, Coords32* r2);
static void createBlast(Coords32* c);

// clang-format off
const EnemyRoutine gApZ2MineRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Mine_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Mine_Update,
    [ENTITY_DIE] =       (EnemyFunc)Mine_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void useApSheets(void* p) { ((struct Entity*)p)->texture = TEXTURE_AP_SHEET; }

static void setMode(struct Mine* p, u8 mode) {
  (p->s).mode[1] = mode;
  (p->s).mode[2] = 0;
}

static void setDisplay(struct Entity* s, bool8 on) {
  if (on) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
}

static void vanish(struct Mine* p) {
  (p->s).flags &= ~(DISPLAY | FLIPABLE);
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
}

static void explode(struct Mine* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Mine_Die(p);
}

// More than 240 x 160 px between spawn spot and Zero
static bool8 strayed(struct Mine* p) {
  struct Entity* s = &p->s;
  return (u32)(s->unk_coord.x - (pZero2->s).coord.x + PIXEL(240)) > PIXEL(480) ||
         (u32)(s->unk_coord.y - (pZero2->s).coord.y + PIXEL(160)) > PIXEL(320);
}

static u32 offCamera(struct Mine* p) { return Camera_GetDistance(&gStageRun.vm.camera, &(p->s).coord); }

// 0x0809159c
static void createMine(struct Entity* spawner, s32 x, s32 y) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_MINE);
    p->renderPrio = 24;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = spawner;
    p->coord.x = x;
    p->coord.y = y;
    p->work[0] = 1;
    p->work[1] = spawner->work[1];
  }
}

// 0x08091604
static void Mine_Init(struct Mine* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  p->fuse = 3600;
  s->unk_coord = s->coord;
  p->elementEffect = NULL;
  p->hit = FALSE;
  if (s->work[0] > 1) {
    vanish(p);
    return;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  if (s->work[0] == 0) {
    setMode(p, MINE_HOME);
    s->unk_28 = NULL;
    INIT_BODY(p, sCollisions, 64, onCollision);
  } else {
    setMode(p, MINE_BLINK_IN);
    INIT_BODY(p, &sIntangible, 64, onCollision);
  }
  Mine_Update(p);
}

static void Mine_BlinkIn(struct Mine* p);
static void Mine_Home(struct Mine* p);
static void Mine_Knocked(struct Mine* p);
static void Mine_Arm(struct Mine* p);
static void Mine_Rise(struct Mine* p);
static void Mine_Fall(struct Mine* p);
static void Mine_Burn(struct Mine* p);

// 0x08091704
static void Mine_Update(struct Mine* p) {
  struct Entity* s = &p->s;
  u32 status = (p->body).status;

  if (s->unk_28 != NULL && s->unk_28->mode[0] > ENTITY_UPDATE) s->unk_28 = NULL;
  if ((gStageRun.vm.active & VM_ACTIVE) && s->unk_28 == NULL) {
    CreateSmoke(1, &s->coord);
    vanish(p);
    return;
  }
  if (p->fuse == 0) {
    explode(p);
    return;
  }
  p->fuse--;
  if (p->fuse < 60) {
    setDisplay(s, p->fuse & 1);
  } else if (p->fuse < 180) {
    setDisplay(s, (p->fuse & 3) != 0);
  }
  if ((s->mode[1] == MINE_KNOCKED && offCamera(p) > 0xEFFF) || (s->mode[1] == MINE_RISE && offCamera(p) > 0x1FFF)) {
    vanish(p);
    return;
  }
  if (status & BODY_STATUS_B2) {
    explode(p);
    return;
  }
  if ((status & BODY_STATUS_WHITE) && p->elementEffect == NULL && s->mode[1] != MINE_BURN) {
    p->elementEffect = ApplyElementEffect(0, (Object*)p, &sElementCoord);
    if (p->elementEffect != NULL) {
      setMode(p, MINE_FALL);
    } else if ((p->body).elemented == ELEMENT_FLAME) {
      setMode(p, MINE_BURN);
    }
  }
  switch (s->mode[1]) {
    case MINE_BLINK_IN: Mine_BlinkIn(p); break;
    case MINE_HOME: Mine_Home(p); break;
    case MINE_KNOCKED: Mine_Knocked(p); break;
    case MINE_ARM: Mine_Arm(p); break;
    case MINE_RISE: Mine_Rise(p); break;
    case MINE_FALL: Mine_Fall(p); break;
    case MINE_BURN: Mine_Burn(p); break;
  }
}

// 0x08091b58
static void Mine_BlinkIn(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    s->work[2] = 0;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  setDisplay(s, ++s->work[2] & 1);
  if (s->work[2] > 15 && s->motion.state == ANIM_NEXT_GOTO) {
    s->flags |= DISPLAY;
    setMode(p, MINE_ARM);
  }
}

// 0x08091bbc: drifts half a pixel a frame at point 36 px over Zero, reaims every 60
static void Mine_Home(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    u8 a;
    SetMotion(s, ANIM(0));
    UpdateEntityAnim(s);
    a = CalcAngle((pZero2->s).coord.x - s->coord.x, (pZero2->s).coord.y - PIXEL(36) - s->coord.y);
    s->d.x = COS(a) / 2;
    s->d.y = SIN(a) / 2;
    s->work[2] = 60;
    s->mode[2]++;
  }
  if ((s->work[2] & 3) == 0) UpdateEntityAnim(s);
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
  if (strayed(p) || offCamera(p) > 0x4FFF) {
    setMode(p, MINE_RISE);
    return;
  }
  if (--s->work[2] == 0) s->mode[2] = 0;
}

// 0x08091cb8: explodes on solid ground, not ladder
static void Mine_Knocked(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetMotion(s, ANIM(0));
    SetDDP(&p->body, sKnocked);
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0 && (u16)(GetMetatileAttr(s->coord.x, s->coord.y) - 14) > 1) {
    explode(p);
    return;
  }
  s->coord.x += s->d.x;
  s->coord.y += s->d.y;
}

// 0x08091d48
static void Mine_Arm(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sCollisions);
    SetMotion(s, ANIM(2));
    s->work[2] = 16;
    s->mode[2]++;
  }
  UpdateEntityAnim(s);
  if (--s->work[2] == 0) setMode(p, MINE_HOME);
}

// 0x08091d98
static void Mine_Rise(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    s->d.y = -0x80;
    s->work[2] = 0;
    s->mode[2]++;
  }
  if ((--s->work[2] & 3) == 0) UpdateEntityAnim(s);
  s->coord.y += s->d.y;
  if (!strayed(p) && offCamera(p) <= 0x1FFF) setMode(p, MINE_HOME);
}

// 0x08091e28
static void Mine_Fall(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, sFalling);
    s->d.y = 0;
    s->mode[2]++;
  }
  s->coord.y += s->d.y;
  s->d.y += 0x40;
  if (s->d.y > 0x700) s->d.y = 0x700;
  if (FUN_080098a4(s->coord.x, s->coord.y) != 0) explode(p);
}

// 0x08091e98
static void Mine_Burn(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[2] == 0) {
    SetDDP(&p->body, &sBurning);
    s->work[2] = 64;
    s->mode[2]++;
  }
  if (--s->work[2] == 0) explode(p);
}

// 0x08091ef8: shots knock it level, blades away from Zero
static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  struct Mine* p = (struct Mine*)body->parent;
  struct Entity* s = &p->s;
  struct Entity* by = body->enemy->parent;
  u8 a;
  if (!(body->hitboxFlags & BODY_STATUS_WHITE) || p->hit) return;
  p->hit = TRUE;
  if (by->kind == ENTITY_PROJECTILE) return;
  if (by->kind != ENTITY_WEAPON) {
    explode(p);
    return;
  }
  switch (by->id) {
    case WEAPON_MOVE_Z_BUSTER:
    case WEAPON_MOVE_SOUL_LANCHER:
    case WEAPON_MOVE_BURST_SHOT:
    case WEAPON_MOVE_BLIZZARD_ARROW:
    case WEAPON_MOVE_REFLECT_LASER:
      s->d.x = s->coord.x < (pZero2->s).coord.x ? -PIXEL(4) : PIXEL(4);
      s->d.y = 0;
      break;
    default:
      a = CalcAngle(s->coord.x - (pZero2->s).coord.x, s->coord.y - (pZero2->s).coord.y + PIXEL(14));
      s->d.x = COS(a) * 4;
      s->d.y = SIN(a) * 4;
      break;
  }
  setMode(p, MINE_KNOCKED);
}

// 0x0800fb84: rock in screen rows 3 and 4 breaks to metatile 8 screens below
static void breakRock(const Coords32* c) {
  u16* map = gOverworld.terrain.tilemap;
  s32 x = METACOORD(c->x + 0x7FF);
  s32 y = METACOORD(c->y + 0x7FF);
  u16 patch[3];
  if (y / 10 != 3 && y / 10 != 4) return;
  patch[0] = patch[1] = 1;
  patch[2] = map[MAP_OFFSET(map, x, y + 80)];
  if (map[MAP_OFFSET(map, x, y)] == patch[2]) return;
  PatchMetatileMap(x, y, patch);
  if (!isSoundPlaying(SE_Z2_DESERT_TAIL_SLAM)) PlaySound(SE_Z2_DESERT_TAIL_SLAM);
}

static void blast(s32 x, s32 y) {
  Coords32 c;
  c.x = x;
  c.y = y;
  createBlast(&c);
  breakRock(&c);
}

// 0x080918c8: grows in rings, four blasts every other frame, quake each
static void Mine_Die(struct Mine* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    PlaySound(SE_Z2_TANK_EXPLODE);
    s->renderPrio = 1;
    SetDDP(&p->body, &sBlasts[0]);
    p->ring = 2;
    p->ringPoint = 1;
    s->work[2] = 0;
    s->mode[1]++;
  }
  if (s->work[2] == 8) SetDDP(&p->body, &sBlasts[1]);
  if (s->work[2] == 16) SetDDP(&p->body, &sBlasts[2]);
  if (s->work[2] == 24) {
    if (p->hit) {
      if (gScore.enemyCount < 9999) gScore.enemyCount++;
      TryDropZakoDisk((struct Enemy*)p, &s->coord);
      ApImportMineKilled();
    }
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    return;
  }
  if (p->ring <= 4) {
    setDisplay(s, s->work[2] & 1);
    if (!(s->work[2] & 1)) {
      s32 along = PIXEL(8) * (p->ring / 2) - PIXEL(16) * (p->ringPoint - 1) - PIXEL(8);
      s32 out = PIXEL(8) * (p->ring - 1);
      blast(s->coord.x - along, s->coord.y - out);
      blast(s->coord.x + out, s->coord.y - along);
      blast(s->coord.x + along, s->coord.y + out);
      blast(s->coord.x - out, s->coord.y + along);
      AppendQuake(4, &s->coord);
      if (++p->ringPoint == p->ring) {
        if (p->ring == 4) {
          TryDropItem(p->fuse == 0 ? 7 : 0, (struct Coord*)&s->coord);
          s->flags &= ~DISPLAY;
        }
        p->ring++;
        p->ringPoint = 1;
      }
    }
  }
  s->work[2]++;
}

// --------------------------------------------
// Zero 2's enemy 36, unseen, makes mine every 240 frames on camera
// work0: how many may be out, less one

struct Spawner {
  OBJECT_HDR;
  s32 wait;  // 0xB4
  u8 _b8[12];
};
static_assert(sizeof(struct Spawner) == sizeof(struct Enemy));

static void Spawner_Init(struct Spawner* p);
static void Spawner_Update(struct Spawner* p);

// clang-format off
const EnemyRoutine gApZ2MineSpawnerRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Spawner_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Spawner_Update,
    [ENTITY_DIE] =       (EnemyFunc)DeleteEnemy,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x0807aaf8
static void Spawner_Init(struct Spawner* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  p->wait = 0;
  Spawner_Update(p);
}

// 0x0807ab4c
static void Spawner_Update(struct Spawner* p) {
  struct Entity* s = &p->s;
  if (gStageRun.vm.active & VM_ACTIVE) return;
  if (p->wait != 0) {
    p->wait--;
    return;
  }
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) != 0) return;
  if (countSpecificEntities1(gEnemyHeaderPtr, ENEMY_Z2_MINE) > s->work[0]) return;
  createMine(s, s->coord.x + PIXEL(8), s->coord.y + PIXEL(8));
  p->wait = 240;
}

// --------------------------------------------
// Zero 2's VFX 37, mine's blast

static void Blast_Init(struct VFX* p);
static void Blast_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2MineBlastRoutine = {
    [ENTITY_INIT] =      Blast_Init,
    [ENTITY_UPDATE] =    Blast_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteVFX,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080b666c
static void createBlast(Coords32* c) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    INIT_VFX_ROUTINE(p, VFX_Z2_MINE_BLAST);
    p->renderPrio = 1;
    p->coord = *c;
  }
}

// 0x080b66b8
static void Blast_Init(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  InitNonAffineMotion(s);
  useApSheets(p);
  s->flags |= DISPLAY | FLIPABLE;
  SetMotion(s, ANIM(1));
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Blast_Update(p);
}

// 0x080b672c
static void Blast_Update(struct VFX* p) {
  struct Entity* s = (struct Entity*)p;
  UpdateEntityAnim(s);
  if (s->motion.state == ANIM_END) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

// -------------------------------------------
// clang-format off
static const struct Collision sCollisions[2] = {
    {DDP, FACTION_ENEMY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 1, 0x00000001, {0x100, 0x0, 0x1300, 0x1400}},
    {DRP, FACTION_ENEMY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x03, 0x02, 0x00, 0, 0x00000000, {0x100, 0x0, 0x1300, 0x1400}},
};

static const struct Collision sIntangible =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0, 0x00000000, {0x0, 0x0, 0x0, 0x0}};

static const struct Collision sKnocked[2] = {
    {DDP, FACTION_NEUTRAL, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 1, 0x00000001, {0x100, 0x0, 0x1300, 0x1400}},
    {DRP, FACTION_NEUTRAL, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x03, 0x02, 0x00, 0, 0x00000000, {0x100, 0x0, 0x1300, 0x1400}},
};

static const struct Collision sFalling[2] = {
    {DDP, FACTION_ALLY, 0, 255, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 1, 0x00000001, {0x100, 0x0, 0x1300, 0x1400}},
    {DRP, FACTION_ALLY, 0, 255, 0xff, 0xff, 0xff, 0xff, 0x03, 0x02, 0x00, 0, 0x00000000, {0x100, 0x0, 0x1300, 0x1400}},
};

static const struct Collision sBurning =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x02, 0x00, 0, 0x00000000, {0x100, 0x0, 0x1300, 0x1400}};

static const struct Collision sBlasts[3] = {
    {DDP, FACTION_NEUTRAL, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x2000, 0x2000}},
    {DDP, FACTION_NEUTRAL, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x3000, 0x3000}},
    {DDP, FACTION_NEUTRAL, 0, 2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0x00000001, {0x0, 0x0, 0x4000, 0x4000}},
};
// clang-format on

#endif  // AP
