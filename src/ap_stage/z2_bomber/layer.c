// Zero 2's BOMBER AKA Bombardment Aircraft

#include "ap.h"
#include "ap_import.h"
#include "gba/gba.h"
#include "camera.h"
#include "collision.h"
#include "entity.h"
#include "entity_manager.h"
#include "enemy.h"
#include "global.h"
#include "gpu_regs.h"
#include "metatile.h"
#include "overworld.h"
#include "overworld_layer.h"
#include "palette_animation.h"
#include "quake.h"
#include "random.h"
#include "script.h"
#include "solid.h"
#include "sound.h"
#include "stagerun.h"
#include "system.h"
#include "text_window.h"
#include "zero.h"
#include "constants/ap_z2_songs.h"

#if AP

extern const PlttAnimData gApZ2Bomber_PlttAnim17, gApZ2Bomber_PlttAnim18, gApZ2Bomber_PlttAnim19, gApZ2Bomber_PlttAnim20,
    gApZ2Bomber_PlttAnim21, gApZ2Bomber_PlttAnim22, gApZ2Bomber_PlttAnim23, gApZ2Bomber_PlttAnim24,
    gApZ2Bomber_PlttAnim25, gApZ2Bomber_PlttAnim26, gApZ2Bomber_PlttAnim27;
extern const AnimCmd* const gApZ2Bomber_PlttAnimScript17[], *const gApZ2Bomber_PlttAnimScript18[],
    *const gApZ2Bomber_PlttAnimScript19[], *const gApZ2Bomber_PlttAnimScript20[], *const gApZ2Bomber_PlttAnimScript21[],
    *const gApZ2Bomber_PlttAnimScript22[], *const gApZ2Bomber_PlttAnimScript23[], *const gApZ2Bomber_PlttAnimScript24[],
    *const gApZ2Bomber_PlttAnimScript25[], *const gApZ2Bomber_PlttAnimScript26[], *const gApZ2Bomber_PlttAnimScript27[];
extern const ColorGraphic gApZ2Bomber_TileAnim[9];
extern const u16 gApZ2Bomber_Layer3Map[], gApZ2Bomber_Layer4Map[], gApZ2Bomber_Layer5Map[], gApZ2Bomber_Layer6Map[],
    gApZ2Bomber_Layer11Map[];

#define PLTT_ANIM_ID(n) (0x8000 | (n))
#define ANIMATE(here, n) animate(here, PLTT_ANIM_ID(n), &gApZ2Bomber_PlttAnim##n, gApZ2Bomber_PlttAnimScript##n)
#define REMOVE(n) RemovePaletteAnimation(PLTT_ANIM_ID(n))

#define TILESET(n) (gOverworld.terrain.tilesets[n])

static void animate(bool8 here, u16 id, const PlttAnimData* data, const AnimCmd* const* script) {
  if (here) {
    ApStartPaletteAnimation(id, data, script, 0);
    StepPaletteAnimation(id);
  } else {
    RemovePaletteAnimation(id);
  }
}

static void loop(u16 se, bool8 on) {
  if (on) {
    if (!isSoundPlaying(se)) PlaySound(se);
  } else if (isSoundPlaying(se)) {
    StopSound(se);
  }
}

// 0x083184e8
static const u16 sHatch[2 + 5 * 4] = {
    5,     4,     0x4D5, 0x4D6, 0x4D7, 0x4D8, 0x4D9, 0x4E5, 0x4E6, 0x4E7, 0x4E8,
    0x4E9, 0x4F5, 0x4F6, 0x4F7, 0x4F8, 0x4F9, 0x505, 0x506, 0x507, 0x508, 0x509,
};

// 0x0800c008
static void Stage_Init(Coords32* _ UNUSED) {
  struct ApZ2BomberState* w = &gOverworld.work.apZ2Bomber;
  u8 i;
  for (i = 0; i < 7; i++) w->pylons[i] = 0;
  w->beams = TRUE;
  w->time = 0;
  gOverworld.state[0] = 0;
  PatchMetatileMap(0xE3, 0xB7, sHatch);
}

// 0x0800c070
static void Stage_Update(Coords32* leftTop) {
  struct ApZ2BomberState* w = &gOverworld.work.apZ2Bomber;
  u8 i;
  w->beams = TRUE;
  for (i = 0; i < 7; i++) {
    if (w->pylons[i] != 0) {
      w->pylons[i]--;
      w->beams = FALSE;
    }
  }
  ANIMATE(TILESET(0) == 1, 17);
  ANIMATE(TILESET(0) == 3, 18);
  ANIMATE(TILESET(0) == 3, 19);
  ANIMATE(TILESET(1) == 4, 20);
  ANIMATE(TILESET(0) == 5, 21);
  ANIMATE(TILESET(0) == 6, 22);
  ANIMATE(TILESET(1) == 7, 25);
  ANIMATE(TILESET(1) == 7, 26);
  ANIMATE(TILESET(1) == 7, 27);
  ANIMATE(TILESET(0) == 6 && gOverworld.state[0] != 2, 23);
  ANIMATE(TILESET(0) == 6 && gOverworld.state[0] == 2, 24);
  loop(SE_Z2_OUTSIDE, leftTop->x < PIXEL(2880) || leftTop->y < PIXEL(1552));
  loop(SE_Z2_BEAM_HUM, w->beams && leftTop->x >= PIXEL(2880) && leftTop->x < PIXEL(4800) &&
                           leftTop->y > 0x6F000 && leftTop->y < 0x9F000);
  w->time++;
}

// 0x0800c50c
static void Stage_Exit(Coords32* _ UNUSED) {
  StopSound(SE_Z2_OUTSIDE);
  StopSound(SE_Z2_BEAM_HUM);
  REMOVE(17);
  REMOVE(18);
  REMOVE(19);
  REMOVE(20);
  REMOVE(21);
  REMOVE(22);
  REMOVE(23);
  REMOVE(24);
  REMOVE(25);
  REMOVE(26);
  REMOVE(27);
}

static void Stage_Draw(Coords32* _ UNUSED) {}

const StageFunc gApZ2Bomber_StageRoutines[4] = {
    Stage_Init,
    Stage_Update,
    Stage_Draw,
    Stage_Exit,
};

/*
  0x08013b84: spawn areas
  0: sky and hull
  1: mid-boss's ledge
  2: shaft
  3..7: inside, by depth
*/
u8 gApZ2Bomber_Area(Coords32* c) {
  s32 x = c->x, y = c->y;
  if (y <= 0x6E000) return (x > 0xC8000 && x <= 0xCAFFF) ? 1 : 0;
  if (x <= 0xBA000) return 2;
  if (y <= 0x88000) return 3;
  if (y <= 0xA4000) return 4;
  if (y <= 0xAE000) return 6;
  if (x <= 0x132FFF) return 7;
  return 5;
}

// --------------------------------------------

#define TIME (*(u32*)l->work.raw)
#define SINK (*(s32*)l->work.raw)
#define LIGHT (*(u32*)l->work.raw)
#define CRAFTS ((struct Solid**)l->work.raw)

// 0x0800c560
static void Front_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 1;
  l->phase++;
}

static void loadMap(struct StageLayer* l, const u16* map) {
  u16 n = (u16)l->bgIdx >> 4;
  BGCNT16(n) = (u16)(l->prio | l->screenBase | BGCNT_MOSAIC | BGCNT_CHARBASE(1));
  RESET_BGOFS(n);
  TIME = 0;
  CpuFastSet(map, SCREEN_ADDR(n), BG_SCREEN_SIZE / 4);
}

// 0x0800c594
static void Far_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    loadMap(l, gApZ2Bomber_Layer3Map);
    l->phase++;
  }
  TIME++;
  BGnHOFS(n) = (l->viewportLeftTopPixel.x >> 3) + TIME;
  BGnVOFS(n) = l->viewportLeftTopPixel.y >> 3;
}

static void near(struct StageLayer* l, const u16* map) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    loadMap(l, map);
    l->phase++;
  }
  TIME++;
  BGnHOFS(n) = l->viewportLeftTopPixel.x * 2 + TIME * 16;
  BGnVOFS(n) = l->viewportLeftTopPixel.y * 2;
}

// 0x0800c624
static void Near4_Update(struct StageLayer* l, const struct Stage* s) { near(l, gApZ2Bomber_Layer4Map); }

// 0x0800c940
static void Near6_Update(struct StageLayer* l, const struct Stage* s) { near(l, gApZ2Bomber_Layer6Map); }

static void timeMap(struct StageLayer* l, const u16* map) {
  if (l->phase == 0) {
    loadMap(l, map);
    l->phase++;
  }
  TIME++;
}

// 0x0800c6b4, 0x0800cb20
static void Clouds_Update(struct StageLayer* l, const struct Stage* _ UNUSED) { timeMap(l, gApZ2Bomber_Layer5Map); }

// 0x0800cdac
static void Clouds11_Update(struct StageLayer* l, const struct Stage* _ UNUSED) { timeMap(l, gApZ2Bomber_Layer11Map); }

/*
  0x0800c720, 0x0800cb8c, 0x0800ce18: BG3 offsets by scanline, HBlank DMA.
  Seven bands of cloud, farther ones slower.
*/
static void clouds(struct StageLayer* l, s32 above) {
  static const u8 sEnds[7] = {40, 56, 64, 96, 104, 120, DISPLAY_HEIGHT};
  static const u8 sShifts[7] = {0, 1, 2, 3, 2, 1, 0};
  u32* lines = Malloc(DISPLAY_HEIGHT * 4);
  s16 x = (u16)(l->viewportLeftTopPixel.x >> 3);
  s8 v = (l->viewportLeftTopPixel.y >> 3) + above;
  s32 y = 0, band, end;

  if (lines == NULL) return;
  gIntrManager.reservedDma0[0] = (u32)lines;
  gIntrManager.reservedDma0[1] = REG_ADDR_BG3HOFS;
  gIntrManager.reservedDma0[2] = 0xA6600001;
  for (band = 0; band < 7; band++) {
    end = sEnds[band] - v;
    if (end > DISPLAY_HEIGHT || band == 6) end = DISPLAY_HEIGHT;
    for (; y < end; y++) {
      lines[y] = ((u32)(u16)v << 16) | (u16)((x >> sShifts[band]) + (TIME >> sShifts[band]));
    }
  }
}

static void Clouds_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) { clouds(l, 64); }

static void LowClouds_Draw(struct StageLayer* l, const struct Stage* _ UNUSED) { clouds(l, 32); }

// 0x0800c9d0: hull behind, sinks with quakes once the ship is hit
static void Sinking_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase == 0) {
    BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
    SINK = gOverworld.state[0] != 0 ? -0x6000 : 0;
    l->scroll.y = 0;
    l->scrollPower.x = 256;
    l->scrollPower.y = 256;
    l->phase++;
  }
  if (gOverworld.state[0] == 1) {
    if (SINK == 0) AppendQuake(3, (Coords32*)&l->viewportLeftTopPixel);
    if (SINK > -0x6000) {
      SINK -= 32;
      if (SINK <= -0x6000) AppendQuake(3, (Coords32*)&l->viewportLeftTopPixel);
    }
  }
  l->scroll.x = SINK >> 8;
}

// 0x0800ca68, 0x0800d0d4
static void Back_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = (u16)l->bgIdx >> 4;
  if (l->phase != 0) return;
  BGCNT16(n) = (BGCNT16(n) & ~3) | 3;
  l->phase++;
}

static void Back13_Update(struct StageLayer* l, const struct Stage* s) {
  if (l->phase == 0) {
    l->scrollPower.x = 256;
    l->scrollPower.y = 256;
  }
  Back_Update(l, s);
}

// 0x0800ca9c: lights, cycling while the beams are up
static void Lights_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    LIGHT = 15;
    l->phase++;
  }
  if (!gOverworld.work.apZ2Bomber.beams) {
    LIGHT = 0;
  } else if (++LIGHT > 24) {
    LIGHT -= 9;
  }
}

// 0x0800cad4
static void Lights_Draw(struct StageLayer* l, const struct Stage* s) {
  const ColorGraphic* g = &gApZ2Bomber_TileAnim[LIGHT / 3];
  DrawGeneralStageLayer(l, s);
  RequestGraphicTransfer(&g->g, BG_CHAR_OFFSET(1));
  LoadPalette(&g->pal, 0);
}

// 0x08318594, 0x083185c4
static const Coords32 sCraftAt[6] = {
    {PIXEL(592), PIXEL(1632)},  {PIXEL(1056), PIXEL(1624)}, {PIXEL(1872), PIXEL(1720)},
    {PIXEL(2016), PIXEL(1504)}, {PIXEL(2344), PIXEL(1664)}, {PIXEL(2528), PIXEL(1472)},
};

// 0x0800d020: flying craft past the first
static void Crafts_Update(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 i;
  if (l->phase != 0) return;
  for (i = 0; i < 6; i++) CRAFTS[i] = ApZ2CreateCraft(&sCraftAt[i], i + 1);
  l->phase++;
}

// 0x0800d06c
static void Crafts_Exit(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 i;
  for (i = 0; i < 6; i++) {
    if (CRAFTS[i] != NULL) {
      ApZ2DeleteCraft(CRAFTS[i]);
      CRAFTS[i] = NULL;
    }
  }
}

// clang-format off
const StageLayerRoutine gApZ2Bomber_LayerRoutines[14] = {
    [0] =  {NULL, NULL, NULL},
    [1] =  {NULL, DrawGeneralStageLayer, NULL},
    [2] =  {Front_Update, DrawGeneralStageLayer, NULL},
    [3] =  {Far_Update, NULL, NULL},
    [4] =  {Near4_Update, NULL, NULL},
    [5] =  {Clouds_Update, Clouds_Draw, NULL},
    [6] =  {Near6_Update, NULL, NULL},
    [7] =  {Sinking_Update, DrawGeneralStageLayer, NULL},
    [8] =  {Back_Update, DrawGeneralStageLayer, NULL},
    [9] =  {Lights_Update, Lights_Draw, NULL},
    [10] = {Clouds_Update, LowClouds_Draw, NULL},
    [11] = {Clouds11_Update, LowClouds_Draw, NULL},
    [12] = {Crafts_Update, DrawGeneralStageLayer, Crafts_Exit},
    [13] = {Back13_Update, DrawGeneralStageLayer, NULL},
};
// clang-format on

// --------------------------------------------
/*
  0x0801706c: Zero 2's mission update, in place of src/ap_import.c's.

  checkpoint 0: the drop from the transport
             1: on the first craft
             2: past the mid-boss
             3: at the defence
             4: after it
             5: at the boss
             6: boss beaten, clear scene skipped. Results
*/

extern const GameCommand gApZ2Bomber_OpeningScript[], gApZ2Bomber_CraftScript[], gApZ2Bomber_MidBossScript[],
    gApZ2Bomber_MidBossClearScript[], gApZ2Bomber_MidBossRestartScript[], gApZ2Bomber_GolemScript[],
    gApZ2Bomber_GolemClearScript[], gApZ2Bomber_DefenceRestartScript[], gApZ2Bomber_DefenceScript[],
    gApZ2Bomber_DefenceClearScript[], gApZ2Bomber_DescentRestartScript[], gApZ2Bomber_DescentScript[],
    gApZ2Bomber_FightRestartScript[], gApZ2Bomber_FightScript[], gApZ2Bomber_ClearScript[],
    gApZ2Bomber_ResultScript[];
extern const TextID gApZ2Bomber_Texts[4];
struct ScriptEntityTemplate;
extern struct ScriptEntityTemplate gApZ2Bomber_Doors0, gApZ2Bomber_Doors1;
void CreateScriptEntity(u8 n, struct ScriptEntityTemplate* template);

#define GOLEM_BEATEN unk_0a
#define CLEARED_PHASE 14
#define DONE_PHASE 15

// 0x083262e8, 0x083262f0
static const Coords32 sHopperAt = {PIXEL(4848), PIXEL(2736)};
static const Coords32 sRaiderAt[5] = {
    {PIXEL(4928), PIXEL(2768)}, {PIXEL(4992), PIXEL(2800)}, {PIXEL(5040), PIXEL(2768)},
    {PIXEL(5104), PIXEL(2800)}, {PIXEL(5168), PIXEL(2768)},
};

static struct Entity* createHopper(const Coords32* at) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    INIT_ENEMY_ROUTINE(p, ENEMY_Z2_HOPPER);
    p->unk_28 = gStageRun.vm.entities[1].entity;
    p->coord = *at;
  }
  return p;
}

static bool8 beaten(void) {
  if (!(gStageRun.missionStatus & MISSION_SUCCESS)) return FALSE;
  gStageRun.missionStatus &= ~MISSION_SUCCESS;
  gStageRun.missionStatus |= MISSION_STAY;
  gStageRun.vm.active &= ~VM_FLAG1;
  return TRUE;
}

static void start(struct StageRun* p, const GameCommand* script, u8 phase) {
  SetScript(&gStageRun.vm, script);
  p->stageEventPhase = phase;
}

static void defend(struct StageRun* p) {
  struct ApZ2BomberState* w = &gOverworld.work.apZ2Bomber;
  u8 i;
  if (p->remainingTimeFrame == 0) {
    if (gEnemyHeaderPtr->remaining != gEnemyHeaderPtr->length) return;
    gCollisionManager.disabled |= COLLMAN_DISABLED;
    start(p, gApZ2Bomber_DefenceClearScript, 9);
    p->remainingTimeFrame = -1;
    return;
  }
  if ((p->remainingTimeFrame & 63) == 0) {
    for (i = 0; i < 6; i++) {
      if (w->defenders[i] == NULL) {
        w->defenders[i] = createHopper((i & 1) ? &sHopperAt : &sRaiderAt[RANDOM(RNG_0202f388) % 5]);
        break;
      }
    }
  }
  for (i = 0; i < 6; i++) {
    if (w->defenders[i] != NULL && w->defenders[i]->mode[0] > 1) w->defenders[i] = NULL;
  }
  switch (--p->remainingTimeFrame) {
    case 2700:
      PrintTextWindow(gApZ2Bomber_Texts[1], 60);
      break;
    case 600:
      PrintTextWindow(gApZ2Bomber_Texts[2], 60);
      break;
    case 0:
      PrintTextWindow(gApZ2Bomber_Texts[3], 60);
      gOverworld.state[0] = 2;
      break;
  }
}

s16 ApZ2BomberUpdate(struct StageRun* p) {
  struct ApZ2BomberState* w = &gOverworld.work.apZ2Bomber;
  const Coords32* z = &(((struct Zero*)(p->vm).entities[0].entity)->s).coord;
  struct Camera* cam = &gStageRun.vm.camera;
  u8 i;

  switch (p->stageEventPhase) {
    case 0:
      gStageRun.missionStatus |= MISSION_STAY;
      gStageRun.vm.zeroDeathTextIDs[1] = gApZ2Bomber_Texts[0];
      CLEAR_FLAG(gCurStory.s.gameflags, FLAG_2);
      switch (gStageRun.checkpoint) {
        case 0:
          start(p, gApZ2Bomber_OpeningScript, 1);
          setStageCheckpoint(1);
          gStageRun.GOLEM_BEATEN = 0;
          break;
        case 1:
          start(p, gApZ2Bomber_CraftScript, 1);
          break;
        case 2:
          start(p, gApZ2Bomber_MidBossRestartScript, 5);
          break;
        case 3:
          start(p, gApZ2Bomber_DefenceRestartScript, 6);
          break;
        case 4:
          start(p, gApZ2Bomber_DescentRestartScript, 10);
          break;
        case 5:
          start(p, gApZ2Bomber_FightRestartScript, 12);
          break;
        case 6:
          start(p, gApZ2Bomber_ResultScript, CLEARED_PHASE);
          break;
      }
      return 0;
    case 1:
      if (z->x > PIXEL(2640) && cam->dx != 0) {
        Camera_SetMode(cam, 6);
        cam->chaseMode = 4;
        cam->counter = 0;
        cam->dx = 0;
      }
      if (z->x > 0xC9FFF) {
        gCollisionManager.sweep |= 1 << FACTION_ENEMY;
        p->stageEventPhase = 2;
        return 0;
      }
      break;
    case 2:
      gCollisionManager.sweep = 0;
      start(p, gApZ2Bomber_MidBossScript, 3);
      return 0;
    case 3:
      if (!beaten()) break;
      gCollisionManager.disabled |= COLLMAN_DISABLED;
      gCollisionManager.sweep |= 1 << FACTION_ENEMY;
      start(p, gApZ2Bomber_MidBossClearScript, 4);
      setStageCheckpoint(2);
      return 0;
    case 4:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      gCollisionManager.sweep = 0;
      p->stageEventPhase = 5;
      return 0;
  }

  if (p->stageEventPhase != 10 && !(gStageRun.GOLEM_BEATEN & 1) && z->x > PIXEL(2880) && z->x <= PIXEL(3136) &&
      z->y > PIXEL(1760) && z->y <= 0x77FFF) {
    start(p, gApZ2Bomber_GolemScript, 10);
  }
  if (p->stageEventPhase == 10 && beaten()) {
    start(p, gApZ2Bomber_GolemClearScript, 5);
    gStageRun.GOLEM_BEATEN |= 1;
    return 0;
  }

  switch (p->stageEventPhase) {
    case 5:
      if (z->y > 0x45FFF) {
        CreateScriptEntity(3, &gApZ2Bomber_Doors0);
        CreateScriptEntity(4, &gApZ2Bomber_Doors1);
        p->stageEventPhase = 6;
      }
      break;
    case 6:
      if (z->x > 0x12BFFF) {
        start(p, gApZ2Bomber_DefenceScript, 7);
        setStageCheckpoint(3);
      }
      break;
    case 7:
      for (i = 0; i < 6; i++) w->defenders[i] = NULL;
      p->remainingTimeFrame = 5400;
      w->defenders[0] = gStageRun.vm.entities[6].entity;
      gOverworld.state[0] = 1;
      p->stageEventPhase = 8;
      break;
    case 8:
      defend(p);
      break;
    case 9:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      gCollisionManager.sweep = 0;
      setStageCheckpoint(4);
      p->stageEventPhase = 10;
      break;
    case 10:
      if (z->y > 0xB3FFF && z->x <= PIXEL(3728)) start(p, gApZ2Bomber_DescentScript, 11);
      break;
    case 11:
      if (z->y > 0xC2FFF) {
        if (gStageRun.vm.bgm != (SoundID32)-1) {
          FadeOutBGM(gStageRun.vm.bgm);
          gStageRun.vm.bgm = -1;
        }
        gOverworld.range.left = PIXEL(3600);
        gOverworld.range.right = PIXEL(3728);
        gStageRun.vm.magnitude = 0;
      }
      if (z->y > 0xF9FFF) {
        gOverworld.range.left = 0;
        gOverworld.range.right = MAX_X;
        gCollisionManager.sweep |= 1 << FACTION_ENEMY;
        if (gStageRun.vm.bgm != BGM_GUARDER_ROOM) {
          if (gStageRun.vm.bgm != (SoundID32)-1) FadeOutBGM(gStageRun.vm.bgm);
          PlayBGM(BGM_GUARDER_ROOM);
          gStageRun.vm.bgm = BGM_GUARDER_ROOM;
        }
        p->stageEventPhase = 12;
      }
      break;
    case 12:
      if (z->y > 0xF9FFF && z->x > 0xEDFFF) {
        gCollisionManager.sweep = 0;
        start(p, gApZ2Bomber_FightScript, 13);
        setStageCheckpoint(5);
      }
      break;
    case 13:
      if (!(gStageRun.missionStatus & MISSION_SUCCESS)) break;
      gCollisionManager.disabled |= COLLMAN_DISABLED;
      gCollisionManager.sweep |= 1 << FACTION_ENEMY;
      SetScript(&gStageRun.vm, gApZ2Bomber_ClearScript);
      gStageRun.missionStatus &= ~MISSION_SUCCESS;
      gStageRun.vm.active &= ~VM_FLAG1;
      gStageRun.missionStatus |= STOP_TIME_COUNT;
      gStageRun.missionStatus |= MISSION_STAY;
      setStageCheckpoint2(6);
      p->stageEventPhase = CLEARED_PHASE;
      break;
    case CLEARED_PHASE:
      gCollisionManager.disabled &= ~COLLMAN_DISABLED;
      gCollisionManager.sweep = 0;
      gStageRun.missionStatus &= ~MISSION_STAY;
      p->stageEventPhase = DONE_PHASE;
      break;
  }
  return 0;
}

#endif  // AP
