// Zero 2's ICE AKA Computer Zone

#include "ap_import.h"
#include "gba/gba.h"
#include "collision.h"
#include "definition.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "random.h"
#include "score.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Ice_PlttAnim85, gApZ2Ice_PlttAnim86, gApZ2Ice_PlttAnim87, gApZ2Ice_PlttAnim88,
    gApZ2Ice_PlttAnim89;
extern const AnimCmd* const gApZ2Ice_PlttAnimScript85[], *const gApZ2Ice_PlttAnimScript86[],
    *const gApZ2Ice_PlttAnimScript87[], *const gApZ2Ice_PlttAnimScript88[], *const gApZ2Ice_PlttAnimScript89[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Ice_PlttAnim##n, gApZ2Ice_PlttAnimScript##n)
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])

// Bit 0 is the Golem's
#define COOLERS_DOWN gStageRun.unk_0a

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

u8 ApZ2CoolersDown(void) {
  u8 n = 0, i;
  for (i = 0; i < 4; i++) {
    if (COOLERS_DOWN & (2 << i)) n++;
  }
  return n;
}

// 0x0800bbd4
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2ComputerZoneState* w = &gOverworld.work.apZ2ComputerZone;
  w->music = gStageRun.checkpoint == 2 ? 2 : 0;
  w->swept = FALSE;
}

/*
  0x0800bc30, 0x08016bd0: x 6240 enemies swept a frame for Golem, up top x 9104 music goes,
  9136 room's plays, enemies swept until 9360
*/
static void Stage_Update(Coords32* _ UNUSED) {
  struct ApZ2ComputerZoneState* w = &gOverworld.work.apZ2ComputerZone;
  s32 x = (pZero2->s).coord.x;

  ANIMATE(TILESET(0) == 2, 86);
  ANIMATE(TILESET(0) == 2, 87);
  ANIMATE(TILESET(1) == 3, 85);
  ANIMATE(TILESET(1) == 4, 88);
  ANIMATE(TILESET(0) == 5, 89);

  if (w->swept) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
  } else if (gStageRun.checkpoint == 0 && x >= PIXEL(6240)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
    w->swept = TRUE;
  }
  if ((pZero2->s).coord.y > PIXEL(479)) return;
  if (w->music == 0 && x >= PIXEL(9104)) {
    FadeOutBGM(gStageRun.vm.bgm);
    w->music = 1;
  }
  if (w->music == 1 && x >= PIXEL(9136)) {
    PlayBGM(BGM_GUARDER_ROOM);
    gStageRun.vm.bgm = BGM_GUARDER_ROOM;
    w->music = 2;
  }
  if (x >= PIXEL(9136) && x < PIXEL(9360)) {
    gCollisionManager.sweep |= 1 << FACTION_ENEMY;
  } else if (w->music == 2 && x >= PIXEL(9360)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    w->music = 3;
  }
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x0800bdfc
static void Stage_Exit(Coords32* _ UNUSED) {
  REMOVE(85);
  REMOVE(86);
  REMOVE(87);
  REMOVE(88);
  REMOVE(89);
}

const StageFunc gApZ2Ice_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013b48: spawn areas
  0: shore, x up to 3231
  1: up to 6367
  2: Golem's room, up to 7199
  3: rest
*/
u8 gApZ2Ice_Area(Coords32* c) {
  if (c->x < PIXEL(3232)) return 0;
  if (c->x < PIXEL(6368)) return 1;
  if (c->x < PIXEL(7200)) return 2;
  return 3;
}

// --------------------------------------------

static void drawWhole(struct StageLayer* l, s16 y) {
  PixelCoords origin = {0, y};
  u16 n = (u16)l->bgIdx >> 4;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  FUN_08005a70(&l->gfx, &origin, SCREEN_ADDR(n));
  UpdateBGOFS(&l->gfx, BGOFS(n));
}

// 0x0800be34: sky, blended
static void Sky_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  drawWhole(l, 0);
  gBlendRegBuffer.bldclt = 0x3B44;
  gBlendRegBuffer.bldalpha = 0xC04;
  l->phase++;
}

// 0x0800beb0
static void Sea_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  drawWhole(l, 160);
  l->phase++;
}

// 0x0800bf18
static void Water_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase != 0) return;
  gOverworld.sea = PIXEL(1248);
  gBlendRegBuffer.bldclt = 0x3B44;
  gBlendRegBuffer.bldalpha = 0xC04;
  l->phase++;
}

// 0x0800bf44
static void Water_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) { gOverworld.sea = 0x7FFFFFFF; }

// 0x08316f6c..: room's gauge by coolers down
static const u16 sGauge[5][8] = {
    {3, 2, 0x49D, 0x49E, 0x49F, 0x4AD, 0x4AE, 0x4AF},
    {3, 2, 0x497, 0x498, 0x499, 0x4A7, 0x4A8, 0x4A9},
    {3, 2, 0x494, 0x495, 0x496, 0x4A4, 0x4A5, 0x4A6},
    {3, 2, 0x475, 0x476, 0x477, 0x485, 0x486, 0x487},
    {3, 2, 0x455, 0x456, 0x457, 0x465, 0x466, 0x467},
};

// 0x08316f40
static const u16 sCooled[22] = {20, 1, 0x21C, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E,
                                0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21E, 0x21F};

// 0x0800bf6c: bear's room
static void Room_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 n;
  if (l->phase != 0) return;
  n = ApZ2CoolersDown();
  PatchMetatileMap(593, 25, sGauge[n]);
  PatchMetatileMap(599, 25, sGauge[n]);
  if (n == 4) PatchMetatileMap(586, 29, sCooled);
  l->phase++;
}

// --------------------------------------------
/*
  Zero 2's solid 6, cooling system.
  work1: its bit of COOLERS_DOWN, less 1
*/

static void Cooler_Init(struct Solid* p);
static void Cooler_Update(struct Solid* p);
static void Cooler_Die(struct Solid* p);
static void Cooler_Disappear(struct Solid* p);

// clang-format off
const SolidRoutine gApZ2CoolerRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Cooler_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Cooler_Update,
    [ENTITY_DIE] =       (SolidFunc)Cooler_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)Cooler_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

#define COOLER(n) MOTION(AP_SHEET_Z2_COOLER, (n))

// 0x08348e1c, 0x08348e6c
static const struct Collision sCoolerCollision =
    {DRP, FACTION_ENEMY, 0, 0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0, 0x00000000, {0, -0x1e00, 0x2a00, 0x3c00}};
static const struct Rect sCoolerSize = {0, -0x1e00, 0x2a00, 0x3c00};

// 0x08348e34
static const struct SlashedEnemy sCoolerGibs[2] = {
    {COOLER(1), {0xff, 0x54}, {0, 0}, {-384, -1024}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
    {COOLER(2), {0xff, 0x52}, {0, 0}, {320, -1280}, {255, 255}, {0, 64}, {0x200, 0x200}, {0}},
};

static void useApSheet(void* p) {
  if (p != NULL) ((struct Entity*)p)->texture = TEXTURE_AP_SHEET;
}

static bool8 coolerUnderwater(struct Entity* s) {
  return GetMetatileAttr(s->coord.x, s->coord.y) == 0x8000 || s->coord.y > gOverworld.sea;
}

// 0x080c8e80
static void coolerBang(struct Entity* s) { PlaySound(coolerUnderwater(s) ? SE_Z2_FISH_BURST : SE_ZAKO_EXPLODE); }

// Up to 8 px either way, or 15 if wide
static void coolerSmoke(struct Entity* s, u8 kind, bool8 wide, s32 up) {
  Coords32 at;
  if (wide) {
    at.x = s->coord.x + PIXEL((s32)(RANDOM(RNG_0202f388) & 31) - 15);
    at.y = s->coord.y + PIXEL((s32)(RANDOM(RNG_0202f388) & 31) - 15) - up;
  } else {
    at.x = s->coord.x + PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8);
    at.y = s->coord.y + PIXEL((s32)(RANDOM(RNG_0202f388) & 15) - 8) - up;
  }
  CreateSmoke(kind, &at);
}

// 0x080c89dc
static void Cooler_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  if (COOLERS_DOWN & (2 << s->work[1])) {
    s->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, COOLER(0));
  s->flags |= DISPLAY | FLIPABLE;
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  INIT_BODY(p, &sCoolerCollision, 8, NULL);
  s->flags2 |= ENTI_PHYSICS;
  s->size = &sCoolerSize;
  s->physicsAttr = 0x401;
  Cooler_Update(p);
}

// 0x080c8ae8
static void Cooler_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    UpdateEntityAnim(s);
    return;
  }
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  Cooler_Die(p);
}

// 0x080c8b48: bursts for 32 frames
static void Cooler_Die(struct Solid* p) {
  struct Entity* s = &p->s;
  if (s->mode[1] == 0) {
    u8 flip = (s->flags & X_FLIP) ? 1 : 0;
    s32 sign = flip * 2 - 1;
    Coords32 at;
    coolerBang(s);
    SetSpriteAnimation(p, COOLER(3));
    at.x = s->coord.x + sign * PIXEL(14);
    at.y = s->coord.y - PIXEL(46);
    useApSheet(CreateSlashedEnemy(&at, &sCoolerGibs[0], 0, flip << 4));
    at.x = s->coord.x - sign * PIXEL(4);
    useApSheet(CreateSlashedEnemy(&at, &sCoolerGibs[1], 0, flip << 4));
    coolerSmoke(s, 1, FALSE, PIXEL(46));
    coolerSmoke(s, 2, FALSE, PIXEL(46));
    COOLERS_DOWN |= 2 << s->work[1];
    s->work[2] = 32;
    s->mode[1]++;
  }
  UpdateEntityAnim(s);
  if ((s->work[2] & 3) == 0) {
    coolerBang(s);
    coolerSmoke(s, 2, TRUE, PIXEL(7));
  }
  if (--s->work[2] != 0) return;
  coolerBang(s);
  coolerSmoke(s, 1, TRUE, PIXEL(24));
  coolerSmoke(s, 2, TRUE, PIXEL(24));
  coolerSmoke(s, 2, TRUE, PIXEL(24));
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  TryDropItem(0, (struct Coord*)&s->coord);
  if (gScore.enemyCount < 9999) gScore.enemyCount++;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// 0x080bf834
static void Cooler_Disappear(struct Solid* p) {
  struct Entity* s = &p->s;
  s->flags &= ~DISPLAY;
  EXIT_BODY(p);
  s->flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

/*
  Zero 2's layer routines for this stage
  2: sky
  3: sea
  4: water line
  5: bear's room
*/
// clang-format off
const StageLayerRoutine gApZ2Ice_LayerRoutines[6] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, Sky_Draw, NULL},
    [3] = {NULL, Sea_Draw, NULL},
    [4] = {Water_Update, DrawGeneralStageLayer, Water_Exit},
    [5] = {Room_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

#endif  // AP
