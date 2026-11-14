// Zero 2's NA-3 AKA Temple of Wind

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "motion.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"
#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

extern const PlttAnimData gApZ2Na3_PlttAnim126, gApZ2Na3_PlttAnim127, gApZ2Na3_PlttAnim128,
    gApZ2Na3_PlttAnim146, gApZ2Na3_PlttAnim75;
extern const AnimCmd* const gApZ2Na3_PlttAnimScript126[], *const gApZ2Na3_PlttAnimScript127[],
    *const gApZ2Na3_PlttAnimScript128[], *const gApZ2Na3_PlttAnimScript146[], *const gApZ2Na3_PlttAnimScript75[];
extern const ColorGraphic gApZ2Na3_TileAnim[9];
extern const ColorGraphic gApZ2Na3_Tilesets[];
extern const u16 gApZ2Na3_RaptorMap[], gApZ2Na3_WingsMap[];
extern const GameCommand gApZ2Na3_BossScript[], gApZ2Na3_BossReturnScript[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Na3_PlttAnim##n, gApZ2Na3_PlttAnimScript##n)

#define TILESET(n) (gOverworld.terrain.tilesets[n])

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

// 0x08010000
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2WindShrineState* w = &gOverworld.work.apZ2WindShrine;
  u8 i;
  for (i = 0; i < 16; i++) w->pylons[i] = 0;
  w->beams = TRUE;
  w->music = gStageRun.checkpoint == 0 ? 0 : 2;
  w->raptor = NULL;
  w->bg = 0;
  w->angle = 0;
  w->scale = 256;
  w->center.x = PIXEL(360);
  w->center.y = PIXEL(192);
  ApStartPaletteAnimation(PLTT_ANIM_ID(146), &gApZ2Na3_PlttAnim146, gApZ2Na3_PlttAnimScript146, 0);
}

static bool8 inside(const Coords32* c, s32 left, s32 top, s32 right, s32 bottom) {
  return c->x >= PIXEL(left) && c->x < PIXEL(right) && c->y > PIXEL(top) && c->y < PIXEL(bottom);
}

// Up top: x 2144 music goes, 2176 room's plays and checkpoint, enemies swept until 2400 and fight
static void mission(void) {
  struct ApZ2WindShrineState* w = &gOverworld.work.apZ2WindShrine;
  s32 x = (pZero2->s).coord.x;

  if (gStageRun.stageEventPhase == 1 && (pZero2->s).coord.y <= PIXEL(416)) {
    if (w->music == 0 && x >= PIXEL(2144)) {
      FadeOutBGM(gStageRun.vm.bgm);
      w->music = 1;
    }
    if (x >= PIXEL(2176)) {
      gCollisionManager.sweep |= 1 << FACTION_ENEMY;
      PlayBGM(BGM_GUARDER_ROOM);
      gStageRun.vm.bgm = BGM_GUARDER_ROOM;
      w->music = 2;
      setStageCheckpoint(1);
      gStageRun.vm.camera.bottom = PIXEL(432);
      gStageRun.stageEventPhase = 2;
    }
  } else if (gStageRun.stageEventPhase == 2 && x >= PIXEL(2400)) {
    gCollisionManager.sweep &= ~(1 << FACTION_ENEMY);
    SetScript(&gStageRun.vm, gStageRun.checkpoint == 2 ? gApZ2Na3_BossReturnScript : gApZ2Na3_BossScript);
    setStageCheckpoint(2);
    gStageRun.stageEventPhase = 3;
  }
}

/*
  0x08010094, 0x0801a3cc: pylons count down, beams on while all stand and hum near the halls
*/
static void Stage_Update(Coords32* leftTop) {
  struct ApZ2WindShrineState* w = &gOverworld.work.apZ2WindShrine;
  u8 i;

  w->beams = TRUE;
  for (i = 0; i < 8; i++) {
    u8* n = &w->pylons[(i & 1) + (i >> 1) * 4];
    if (*n != 0) {
      (*n)--;
      w->beams = FALSE;
    }
  }
  ANIMATE(TILESET(0) == 2, 126);
  ANIMATE(TILESET(0) == 2, 127);
  ANIMATE(TILESET(0) == 2, 128);
  StepPaletteAnimation(PLTT_ANIM_ID(146));

  if (w->beams && (inside(leftTop, 1520, 1520, 2400, 1920) || inside(leftTop, 1200, 960, 2160, 1440))) {
    if (!isSoundPlaying(SE_Z2_BEAM_HUM)) PlaySound(SE_Z2_BEAM_HUM);
  } else if (isSoundPlaying(SE_Z2_BEAM_HUM)) {
    StopSound(SE_Z2_BEAM_HUM);
  }
  mission();
}

static void Stage_Draw(Coords32* _ UNUSED) {}

// 0x080101f8
static void Stage_Exit(Coords32* _ UNUSED) {
  StopSound(SE_Z2_BEAM_HUM);
  RemovePaletteAnimation(PLTT_ANIM_ID(126));
  RemovePaletteAnimation(PLTT_ANIM_ID(127));
  RemovePaletteAnimation(PLTT_ANIM_ID(128));
  RemovePaletteAnimation(PLTT_ANIM_ID(146));
}

const StageFunc gApZ2Na3_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013f20: spawn areas
  1: above y 1040, or above 1520 left of x 1312
  0: rest
*/
u8 gApZ2Na3_Area(Coords32* c) {
  if (c->y < PIXEL(1040)) return 1;
  return c->y < PIXEL(1520) && c->x < PIXEL(1312);
}

// --------------------------------------------

#define BG_SHOWN (l->unk_10)

/*
  0x0801021c: raptor on BG2, affine, turned and scaled about stage work's center.
  Flashes white with it. Its tiles are tilesets 0 and 1, over the room's.
*/
static void Raptor_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct ApZ2WindShrineState* w = &gOverworld.work.apZ2WindShrine;
  struct BgAffineDstData* m = &gVideoRegBuffer.bg2p;
  const ColorGraphic* g;
  u16 n = (u16)l->bgIdx >> 4;
  u16 cnt;
  s32 c, sn, dx, dy;

  if (BG_SHOWN != w->bg) l->phase = 0;
  if (l->phase == 0) {
    gVideoRegBuffer.dispcnt = (gVideoRegBuffer.dispcnt & ~DISPCNT_BGMODE_MASK) | DISPCNT_MODE_1;
    cnt = (u16)(l->prio | l->screenBase | BGCNT_256COLOR | BGCNT_AFF256x256 | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    BGCNT16(n) = cnt;
    if (w->bg == 0) {
      RequestVRAMFill(0, (void*)((cnt & 0x1F00) << 3), 0x400);
    } else {
      g = &gApZ2Na3_Tilesets[w->bg == 1 ? 0 : 1];
      RequestBgMapTransfer((u16*)(w->bg == 1 ? gApZ2Na3_RaptorMap : gApZ2Na3_WingsMap), (void*)((cnt & 0x1F00) << 3), 0x400);
      RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
      LoadPalette(&g->pal, 0);
    }
    BG_SHOWN = w->bg;
    l->phase++;
  }
  if (w->bg == 3) {
    c = (COS((u8)-w->angle) << 8) / w->scale;
    sn = (SIN((u8)-w->angle) << 8) / w->scale;
    m->pa = -c;
    m->pb = -sn;
  } else {
    c = (COS(w->angle) << 8) / w->scale;
    sn = (SIN(w->angle) << 8) / w->scale;
    m->pa = c;
    m->pb = sn;
  }
  m->pc = -sn;
  m->pd = c;
  dx = (l->viewportLeftTopPixel.x << 8) - w->center.x;
  dy = (l->viewportLeftTopPixel.y << 8) - w->center.y;
  m->dx = m->pa * dx / 256 + m->pb * dy / 256 + (w->bg == 1 ? 0x8000 : 0x2B00);
  m->dy = m->pc * dx / 256 + m->pd * dy / 256 + (w->bg == 1 ? 0x1800 : 0x4B00);
  // BG palette 2
  if (w->raptor != NULL && FLAG32(gWhitePaintFlags, w->raptor->invincibleID)) {
    gPaletteManager.unk_404 = 2 * 32;
    gPaletteManager.unk_406 = 32;
  }
  if (gOverworld.terrain.reload_graphic) l->phase = 0;
}

// 0x08010584
static void Raptor_Exit(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gVideoRegBuffer.dispcnt &= ~DISPCNT_BGMODE_MASK;
}

#define BEAM_FRAME (l->work.raw[0])

// 0x08010598: off while a pylon is down, then flickers on
static void Beams_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    BEAM_FRAME = 15;
    l->phase++;
  }
  if (!gOverworld.work.apZ2WindShrine.beams) {
    BEAM_FRAME = 0;
  } else if (++BEAM_FRAME > 24) {
    BEAM_FRAME = 16;
  }
}

// 0x080105d0
static void Beams_Draw(struct StageLayer* l, const struct Stage* s) {
  const ColorGraphic* g = &gApZ2Na3_TileAnim[BEAM_FRAME / 3];
  DrawGeneralStageLayer(l, s);
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

static const Coords32 sLiftAt[5] = {
    {PIXEL(2672), PIXEL(1408)}, {PIXEL(2736), PIXEL(1472)}, {PIXEL(2832), PIXEL(1472)},
    {PIXEL(2832), PIXEL(1552)}, {PIXEL(2736), PIXEL(1648)},
};
static const u8 sLiftKind[5] = {1, 3, 0, 3, 1};

#define LIFTS ((struct Entity**)l->work.raw)

// 0x08010624: lifts up the east side
static void Lifts_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  struct Entity* e;
  u8 i;
  if (l->phase != 0) return;
  for (i = 0; i < 5; i++) {
    e = AllocEntityLast(gSolidHeaderPtr);
    LIFTS[i] = e;
    if (e == NULL) continue;
    INIT_SOLID_ROUTINE(e, SOLID_Z2_LIFT);
    e->coord = sLiftAt[i];
    e->work[0] = sLiftKind[i];
    e->work[1] = 64;
  }
  l->phase++;
}

// 0x08010670
static void Lifts_Exit(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 i;
  for (i = 0; i < 5; i++) {
    if (LIFTS[i] == NULL) continue;
    LIFTS[i]->flags &= ~(DISPLAY | FLIPABLE | COLLIDABLE);
    SET_SOLID_ROUTINE((struct Solid*)LIFTS[i], ENTITY_DISAPPEAR);
    LIFTS[i] = NULL;
  }
}

/*
  Zero 2's layer routines for this stage
  2: raptor
  3: beams
  4: lifts
*/
// clang-format off
const StageLayerRoutine gApZ2Na3_LayerRoutines[5] = {
    [0] = {NULL, NULL, NULL},
    [1] = {NULL, DrawGeneralStageLayer, NULL},
    [2] = {NULL, Raptor_Draw, Raptor_Exit},
    [3] = {Beams_Update, Beams_Draw, NULL},
    [4] = {Lifts_Update, DrawGeneralStageLayer, Lifts_Exit},
};
// clang-format on

// --------------------------------------------
// Elpizo's scene, Zero 2's script 3, and its clear, script 5. Tiles while no boss is loaded

#define HARPUIA(n) MOTION(DM200_Z2_HARPUIA, (n))
#define ELPIZO(n) MOTION(DM205_Z2_ELPIZO, (n))
#define BOLT(n) MOTION(AP_SHEET_Z2_DARK_BOLT, (n))
#define BABY_ELF(n) MOTION(AP_SHEET_Z2_BABY_ELF, (n))
#define DARK_ELF(n) MOTION(AP_SHEET_Z2_DARK_ELF, (n))
#define ELPIZO_TILE 608
#define FLAGS (s->scriptEntity->flags)
#define PARENT (s->scriptEntity->unk_04)

static const struct PreloadEntity sBoltSheet = {AP_SHEET_Z2_DARK_BOLT, 0, 576, 8, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sDarkElfSheet = {AP_SHEET_Z2_DARK_ELF, 0, 640, 5, 0, AP_PRELOAD_SHEET, 0};
static const struct PreloadEntity sBabyElfSheet = {AP_SHEET_Z2_BABY_ELF, 0, 704, 7, 0, AP_PRELOAD_SHEET, 0};

static void standOnFloor(struct Solid* p, motion_t m) {
  struct Entity* s = &p->s;
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  s->coord.y = FUN_08009f6c(s->coord.x, s->coord.y);
  SetSpriteAnimation(p, m);
}

// clang-format off
#define SCENE_ROUTINE(name, init, update, disappear) \
const SolidRoutine name = { \
    [ENTITY_INIT] =      (SolidFunc)init, \
    [ENTITY_UPDATE] =    (SolidFunc)update, \
    [ENTITY_DIE] =       (SolidFunc)DeleteEntity, \
    [ENTITY_DISAPPEAR] = (SolidFunc)disappear, \
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity, \
}
// clang-format on

/*
  Zero 2's solid 5 work0 0x30, Harpuia kneeling before Elpizo
  flags: 1 looks up, 2 struck back, 4 looks up, 8 shakes
*/
static void Harpuia_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (!(FLAGS & 1)) break;
      SetSpriteAnimation(p, HARPUIA(27));
      s->mode[1]++;
      break;
    case 1:
      if (!(FLAGS & 2)) break;
      SetSpriteAnimation(p, HARPUIA(26));
      s->unk_coord.x = s->coord.x - PIXEL(16);
      s->work[2] = 32;
      s->mode[1]++;
      break;
    case 2:
      s->coord.x = (s->coord.x * 31 + s->unk_coord.x) / 32;
      if (s->work[2] == 0) {
        s->mode[1]++;
      } else {
        s->work[2]--;
      }
      break;
    case 3:
      if (!(FLAGS & 4)) break;
      SetSpriteAnimation(p, HARPUIA(27));
      s->mode[1]++;
      break;
    case 4:
      if (!(FLAGS & 8)) break;
      s->work[2] = 0;
      InitRotatableMotion(s);
      ResetDynamicMotion(s);
      SetSpriteAnimation(p, HARPUIA(27));
      s->mode[1]++;
      break;
    case 5:
      s->work[2]++;
      if ((s->work[2] & 0x60) == 0) {
        AppendQuake(1, &s->coord);
        (s->spr).mag.x = (s->spr).mag.y = 256 + SIN((u8)(s->work[2] * 4)) / 8;
      } else {
        (s->spr).mag.x = (s->spr).mag.y = 256;
      }
      break;
  }
}

// 0x080c7cfc
static void Harpuia_Init(struct Solid* p) {
  standOnFloor(p, HARPUIA(26));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Harpuia_Update(p);
}

SCENE_ROUTINE(gApZ2WindHarpuiaRoutine, Harpuia_Init, Harpuia_Update, DeleteEntity);

/*
  Zero 2's solid 5 work0 0x31, Elpizo
  flags: 1 laughs, 2 raises his hand until 4, 8 leaves right
*/
static void Elpizo_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (FLAGS & 1) {
        FLAGS &= ~1;
        SetSpriteAnimation(p, ELPIZO(16));
        s->mode[1] = 1;
      }
      if (FLAGS & 2) {
        FLAGS &= ~2;
        SetSpriteAnimation(p, ELPIZO(14));
        s->mode[1] = 2;
      }
      if (FLAGS & 8) {
        SetSpriteAnimation(p, ELPIZO(28));
        s->work[2] = 34;
        s->mode[1] = 3;
      }
      break;
    case 1:
      if ((s->motion).state != ANIM_END) break;
      SetSpriteAnimation(p, ELPIZO(29));
      s->mode[1] = 0;
      break;
    case 2:
      if (!(FLAGS & 4)) break;
      FLAGS &= ~4;
      SetSpriteAnimation(p, ELPIZO(15));
      s->mode[1] = 0;
      break;
    case 3:
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      s->coord.x += 0x380;
      if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) <= 0x3FFF) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// 0x080c7eec
static void Elpizo_Init(struct Solid* p) {
  wDynamicGraphicTilenums[DM205_Z2_ELPIZO] = ELPIZO_TILE;
  wDynamicMotionPalIDs[DM205_Z2_ELPIZO] = 9;
  standOnFloor(p, ELPIZO(8));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Elpizo_Update(p);
}

SCENE_ROUTINE(gApZ2ElpizoRoutine, Elpizo_Init, Elpizo_Update, DeleteEntity);

/*
  Zero 2's solid 5 work0 0x32, Elpizo's bolt holding Harpuia
*/
static void Bolt_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  s->coord.x = PARENT->coord.x;
  s->coord.y = PARENT->coord.y - PIXEL(12);
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      if (s->work[2] != 0) {
        s->work[2]--;
        break;
      }
      SetSpriteAnimation(p, BOLT(2));
      s->mode[1]++;
      break;
    case 1:
      if ((s->motion).state != ANIM_END) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
  }
}

// 0x080c80ac
static void Bolt_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sBoltSheet);
  s->flags |= DISPLAY | FLIPABLE;
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, BOLT(1));
  s->renderPrio = 1;
  s->work[2] = 128;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Bolt_Update(p);
}

SCENE_ROUTINE(gApZ2DarkBoltRoutine, Bolt_Init, Bolt_Update, DeleteEntity);

/*
  Zero 2's solid 5 work0 0x33, a Baby Elf
  work1: 0 left, 1 right
  flags: 1 circles into its parent and fades, 0x80 from the start circles out of it and away
  Drawn trailing at unk_coord.
*/
static void orbit(struct Entity* s) {
  s32 r = s->d.y + 2;
  s32 sn = SIN(s->mode[2]);
  s->coord.x = PARENT->coord.x + (s->work[1] == 0 ? -sn * r : r * sn) / 256;
  s->coord.y = PARENT->coord.y - s->d.y - PIXEL(30);
}

static void sparkle(struct Entity* s) {
  Coords32 at;
  if ((s->work[2] & 31) != 0) return;
  at.x = s->unk_coord.x;
  at.y = s->unk_coord.y + PIXEL(8);
  ApZ2CreateElfSparkle(&at, 4);
}

static void BabyElf_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  s32 tx, ty;
  UpdateSpriteAnimation(p);
  switch (s->mode[1]) {
    case 0:
      s->work[2] = s->work[1] << 6;
      s->work[3] = 16;
      if (FLAGS & 0x80) {
        s->unk_coord.x = s->coord.x = PARENT->coord.x;
        s->unk_coord.y = s->coord.y = PARENT->coord.y - PIXEL(30);
        s->d.y = 0;
        s->mode[2] = 0;
        s->mode[1] = 5;
        break;
      }
      s->unk_coord.x = s->coord.x = PARENT->coord.x + (s->work[1] ? PIXEL(20) : -PIXEL(20));
      s->unk_coord.y = s->coord.y = PARENT->coord.y - PIXEL(48);
      s->mode[1]++;
      break;
    case 1:
      tx = PARENT->coord.x + (s->work[1] ? PIXEL(20) : -PIXEL(20));
      ty = PARENT->coord.y - PIXEL(48);
      if (s->coord.x < tx) {
        s->coord.x += 0x80;
      } else if (s->coord.x > tx) {
        s->coord.x -= 0x80;
      }
      if (s->coord.y < ty) {
        s->coord.y += 0x80;
      } else if (s->coord.y > ty) {
        s->coord.y -= 0x80;
      }
      sparkle(s);
      if (!(FLAGS & 1)) break;
      s->d.y = 0x1200;
      s->mode[2] = 0;
      s->mode[1]++;
      break;
    case 2:
      orbit(s);
      s->mode[2] += (0x4000 - s->d.y) >> 10;
      s->d.y += 64;
      s->work[3] = s->d.y / 768;
      if (s->d.y > 0x3FFF) s->mode[1]++;
      sparkle(s);
      break;
    case 3:
      orbit(s);
      s->mode[2] += (0x4000 - s->d.y) >> 10;
      s->d.y -= 128;
      s->work[3] = s->d.y / 768;
      if (s->d.y > 0) break;
      s->flags &= ~DISPLAY;
      s->mode[1]++;
      break;
    case 5:
      orbit(s);
      s->mode[2] += (0x4000 - (s->d.y >> 1)) >> 10;
      s->d.y += 128;
      s->work[3] = s->d.y / 768;
      if (s->d.y > 0x7FFF) {
        s->flags &= ~DISPLAY;
        s->mode[1]++;
      }
      sparkle(s);
      break;
  }
  s->work[2]++;
  s->unk_coord.x = (s->unk_coord.x * 7 + s->coord.x + SIN((u8)(s->work[2] + 64)) * (s->work[3] >> 1)) / 8;
  s->unk_coord.y = (s->unk_coord.y * 7 + s->coord.y - SIN((u8)(s->work[2] * 2)) * (s->work[3] >> 2)) / 8;
}

// 0x080c81d0
static void BabyElf_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sBabyElfSheet);
  s->flags |= DISPLAY | FLIPABLE;
  InitRotatableMotion(s);
  (s->spr).c = (struct Coord*)&s->unk_coord;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, BABY_ELF(0));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  BabyElf_Update(p);
}

SCENE_ROUTINE(gApZ2BabyElvesRoutine, BabyElf_Init, BabyElf_Update, DeleteEntity);

/*
  Zero 2's solid 24 work0 0, the Dark Elf, over Elpizo
  Flickers and sheds sparkles. Its scene never sets a flag, so its other states are not ported.
*/
static const s32 sSparkleX[5] = {PIXEL(-8), PIXEL(4), PIXEL(-4), PIXEL(0), PIXEL(8)};

#define BOB (p->buffer[4])

static void DarkElf_Update(struct Solid* p) {
  struct Entity* s = &p->s;
  Coords32 at;
  StepPaletteAnimation(PLTT_ANIM_ID(75));
  UpdateSpriteAnimation(p);
  s->coord.x = PARENT->coord.x + PIXEL(32);
  s->coord.y = PARENT->coord.y - PIXEL(64) + SIN(BOB) * 8;
  BOB += 2;
  if ((s->work[2]++ & 15) == 0) {
    at.x = s->coord.x + sSparkleX[s->work[3]];
    at.y = s->coord.y + PIXEL(8);
    ApZ2CreateElfSparkle(&at, (RANDOM(RNG_0202f388) & 0x7FFF) % 3 + 1);
    s->work[3] = (s->work[3] + 1) % 5;
  }
  if (s->mode[3]++ & 1) {
    s->flags |= DISPLAY;
  } else {
    s->flags &= ~DISPLAY;
  }
}

// 0x080cf62c
static void DarkElf_Init(struct Solid* p) {
  struct Entity* s = &p->s;
  ApLoadSheet(&sDarkElfSheet);
  InitRotatableMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, DARK_ELF(0));
  ApStartPaletteAnimation(PLTT_ANIM_ID(75), &gApZ2Na3_PlttAnim75, gApZ2Na3_PlttAnimScript75, 0x200 | 5 << 5);
  SET_XFLIP(p, FALSE);
  s->renderPrio = 23;
  BOB = 0;
  s->work[2] = s->work[3] = 0;
  (s->spr).mag.x = (s->spr).mag.y = 256;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  DarkElf_Update(p);
}

// 0x080cf610
static void DarkElf_Disappear(struct Solid* p) {
  RemovePaletteAnimation(PLTT_ANIM_ID(75));
  DeleteEntity(&p->s);
}

SCENE_ROUTINE(gApZ2DarkElfRoutine, DarkElf_Init, DarkElf_Update, DarkElf_Disappear);

/*
  Zero 2's VFX 60, a sparkle falling off an elf
  work1: 1..3 the Dark Elf's, 4 a Baby Elf's, blinking
*/
static void Sparkle_Init(struct VFX* p);
static void Sparkle_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2ElfSparkleRoutine = {
    [ENTITY_INIT] =      Sparkle_Init,
    [ENTITY_UPDATE] =    Sparkle_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x080bc790
void ApZ2CreateElfSparkle(const Coords32* at, u8 kind) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p == NULL) return;
  INIT_VFX_ROUTINE(p, VFX_Z2_ELF_SPARKLE);
  p->coord = *at;
  p->work[1] = kind;
}

// 0x080bc830
static void Sparkle_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  s->flags |= DISPLAY | FLIPABLE;
  s->texture = TEXTURE_AP_SHEET;
  SetSpriteAnimation(p, s->work[1] == 4 ? BABY_ELF(1) : DARK_ELF(s->work[1] + 2));
  UpdateSpriteAnimation(p);
  s->renderPrio = 31;
  SET_XFLIP(p, RANDOM(RNG_0202f388) & 1);
  SET_YFLIP(p, RANDOM(RNG_0202f388) & 1);
  s->work[3] = 48;
  s->work[2] = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Sparkle_Update(p);
}

// 0x080bc93c
static void Sparkle_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  UpdateSpriteAnimation(p);
  s->coord.y += PIXEL(1);
  if (s->work[1] == 4) {
    if (s->work[2]++ & 1) {
      s->flags |= DISPLAY;
    } else {
      s->flags &= ~DISPLAY;
    }
  }
  if (--s->work[3] == 0xFF || FUN_080098a4(s->coord.x, s->coord.y) != 0) SET_VFX_ROUTINE(p, ENTITY_DIE);
}

#endif  // AP
