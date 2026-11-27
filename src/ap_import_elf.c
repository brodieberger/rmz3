#include "ap.h"

#include "ap_marker.h"
#include "camera.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "sound.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

#include "constants/entity/enemy.h"
#include "constants/motion/ap_sheet.h"
#include "constants/motion/dynamic.h"
#include "constants/song.h"
#include "constants/stage_id.h"

#if AP

/*
  Zero 2's cyber elf entity.
  work0: location, from AP_LOC_IMPORT_FIRST
  work1: type
    0: nurse
    1: animal
    2: hacker
*/

enum { NURSE, ANIMAL, HACKER };

static const struct Collision sCollision;

static void ImportElf_Init(Pickup* p);
static void ImportElf_Update(Pickup* p);

// clang-format off
const PickupRoutine gApImportElfRoutine = {
    [ENTITY_INIT] =      (PickupFunc)ImportElf_Init,
    [ENTITY_UPDATE] =    (PickupFunc)ImportElf_Update,
    [ENTITY_DIE] =       (PickupFunc)DeletePickup,
    [ENTITY_DISAPPEAR] = (PickupFunc)DeletePickup,
    [ENTITY_EXIT] =      (PickupFunc)DeleteEntity,
};
// clang-format on

#define LOCATION(p) (AP_LOC_IMPORT_FIRST + (p)->work[0])

static bool32 checked(u16 loc) {
  return ApServerChecked(loc) || (gAp.checkedLocations[loc >> 3] & (1 << (loc & 7)));
}

/*
  Elves Zero 2 gives for kills in the stage, table at 0x08333482.
*/
#define ELF_BIRFLOW 150  // Crystal Cave
#define ELF_BEEHITT 151
#define ELF_TOWERS 3  // Sand Wilderness
#define ELF_SPIKEBALLS 4
#define ELF_VULTURES 5
#define ELF_SHELLS 196  // Temple of Flame
#define ELF_CANNONS 180  // Neo Arcadia Temple
#define ELF_EYES 84  // Residential Area
#define ELF_GUARDIANS 85
#define ELF_BEES 69  // Forest of Dysis
#define ELF_CARRIERS 70
#define ELF_MOLES 71
#define ELF_SPIDERS 72
#define ELF_HUNTERS 228  // Temple of Wind
#define ELF_SHIPS 229
#define ELF_FISH 21  // Computer Zone
#define ELF_DOZERS 22
#define ELF_CRAWLERS 23
#define ELF_SPIKINGS 36  // Train
#define ELF_CRABS 37
#define ELF_MINES 55  // Power Room
#define ELF_COPTERS 56
#define ELF_GENERATOR 57
#define ELF_SIGNALOIDS 164  // Shuttle Factory
#define ELF_GUARDS 165
#define ELF_TREE_FROGS 120  // Forest of Notus
#define ELF_LEAPERS 121
#define ELF_SNOWBALLERS 132  // Computer Zone 2
#define ELF_WOLVES 133
#define ELF_FLOPPERS 134
#define ELF_FLOOR_MINES 135

EWRAM_DATA static u8 sHottalookKills = 0;
EWRAM_DATA static u8 sHopperKills = 0;
EWRAM_DATA static u8 sTowerKills = 0;
EWRAM_DATA static u8 sSpikeballKills = 0;
EWRAM_DATA static u8 sVultureKills = 0;
EWRAM_DATA static u8 sShellKills = 0;
EWRAM_DATA static u8 sCannonKills = 0;
EWRAM_DATA static u8 sEyeKills = 0;
EWRAM_DATA static u8 sGuardianKills = 0;
EWRAM_DATA static u8 sBeeKills = 0;
EWRAM_DATA static u8 sCarrierKills = 0;
EWRAM_DATA static u8 sMoleKills = 0;
EWRAM_DATA static u8 sSpiderKills = 0;
EWRAM_DATA static u8 sHunterKills = 0;
EWRAM_DATA static u8 sShipKills = 0;
EWRAM_DATA static u8 sFishKills = 0;
EWRAM_DATA static u8 sDozerKills = 0;
EWRAM_DATA static u8 sCrawlerKills = 0;
EWRAM_DATA static u8 sSpikingKills = 0;
EWRAM_DATA static u8 sCrabKills = 0;
EWRAM_DATA static u8 sMineKills = 0;
EWRAM_DATA static u8 sCopterKills = 0;
EWRAM_DATA static u8 sSignaloidKills = 0;
EWRAM_DATA static u8 sGuardKills = 0;
EWRAM_DATA static u8 sSnowballerKills = 0;
EWRAM_DATA static u8 sWolfKills = 0;
EWRAM_DATA static u8 sFlopperKills = 0;
EWRAM_DATA static u8 sFloorMineKills = 0;
EWRAM_DATA static u8 sLeaperKills = 0;
EWRAM_DATA static u8 sTreeFrogKills = 0;

void ApCreateImportElf(u8 n, u8 type, const Coords32* at) {
  struct Entity* p = AllocEntityLast(gPickupHeaderPtr);
  if (p == NULL) return;
  INIT_ITEM_ROUTINE(p, ITEM_AP_IMPORT_ELF);
  p->coord = *at;
  p->work[0] = n;
  p->work[1] = type;
}

// 0x0801de2c: rises where the last one died
static void giveElf(u8 n, u8 type, const Coords32* at) {
  if (gStageRun.id != STAGE_NONE || n / 16 != ApImportZ2Stage(gApImportSelected)) return;
  if (checked(AP_LOC_IMPORT_FIRST + n)) return;
  ApCreateImportElf(n, type, at);
}

// Checked, or out of its capsule already
bool32 ApImportElfOut(u8 n) {
  struct Entity* p;
  if (checked(AP_LOC_IMPORT_FIRST + n)) return TRUE;
  for (p = gPickupHeaderPtr->head; p != (struct Entity*)&gPickupHeaderPtr->tail; p = p->next) {
    if (p->id == ITEM_AP_IMPORT_ELF && p->work[0] == n) return TRUE;
  }
  return FALSE;
}

void ApImportResetKills(void) {
  sHottalookKills = 0;
  sHopperKills = 0;
  sTowerKills = 0;
  sSpikeballKills = 0;
  sVultureKills = 0;
  sShellKills = 0;
  sCannonKills = 0;
  sEyeKills = 0;
  sGuardianKills = 0;
  sBeeKills = 0;
  sCarrierKills = 0;
  sMoleKills = 0;
  sSpiderKills = 0;
  sHunterKills = 0;
  sShipKills = 0;
  sFishKills = 0;
  sDozerKills = 0;
  sCrawlerKills = 0;
  sSpikingKills = 0;
  sCrabKills = 0;
  sMineKills = 0;
  sCopterKills = 0;
  sSignaloidKills = 0;
  sGuardKills = 0;
  sSnowballerKills = 0;
  sWolfKills = 0;
  sFlopperKills = 0;
  sFloorMineKills = 0;
  sLeaperKills = 0;
  sTreeFrogKills = 0;
}

void ApImportHottalookKilled(const Coords32* at) {
  if (++sHottalookKills == 12) giveElf(ELF_BIRFLOW, ANIMAL, at);
}

void ApImportHopperKilled(const Coords32* at) {
  if (++sHopperKills == 3) giveElf(ELF_BEEHITT, ANIMAL, at);
}

void ApImportTowerKilled(const Coords32* at) {
  if (++sTowerKills == 3) giveElf(ELF_TOWERS, HACKER, at);
}

void ApImportSpikeballKilled(const Coords32* at) {
  if (++sSpikeballKills == 4) giveElf(ELF_SPIKEBALLS, HACKER, at);
}

// Vultures, not perches
void ApImportVultureKilled(const Coords32* at) {
  if (++sVultureKills == 5) giveElf(ELF_VULTURES, ANIMAL, at);
}

void ApImportShellKilled(const Coords32* at) {
  if (++sShellKills == 5) giveElf(ELF_SHELLS, ANIMAL, at);
}

void ApImportRingCannonKilled(const Coords32* at) {
  if (++sCannonKills == 3) giveElf(ELF_CANNONS, ANIMAL, at);
}

void ApImportEyeKilled(const Coords32* at) {
  if (++sEyeKills == 5) giveElf(ELF_EYES, ANIMAL, at);
}

void ApImportGuardianKilled(const Coords32* at) {
  if (++sGuardianKills == 8) giveElf(ELF_GUARDIANS, ANIMAL, at);
}

void ApImportBeeKilled(const Coords32* at) {
  if (++sBeeKills == 10) giveElf(ELF_BEES, ANIMAL, at);
}

void ApImportCarrierKilled(const Coords32* at) {
  if (++sCarrierKills == 3) giveElf(ELF_CARRIERS, ANIMAL, at);
}

void ApImportMoleKilled(const Coords32* at) {
  if (++sMoleKills == 4) giveElf(ELF_MOLES, HACKER, at);
}

void ApImportSpiderKilled(const Coords32* at) {
  if (++sSpiderKills == 3) giveElf(ELF_SPIDERS, ANIMAL, at);
}

void ApImportHunterKilled(const Coords32* at) {
  if (++sHunterKills == 8) giveElf(ELF_HUNTERS, ANIMAL, at);
}

void ApImportBarrierShipKilled(const Coords32* at) {
  if (++sShipKills == 5) giveElf(ELF_SHIPS, ANIMAL, at);
}

void ApImportFishKilled(const Coords32* at) {
  if (++sFishKills == 5) giveElf(ELF_FISH, ANIMAL, at);
}

void ApImportDozerKilled(const Coords32* at) {
  if (++sDozerKills == 4) giveElf(ELF_DOZERS, ANIMAL, at);
}

void ApImportCrawlerKilled(const Coords32* at) {
  if (++sCrawlerKills == 4) giveElf(ELF_CRAWLERS, ANIMAL, at);
}

void ApImportSpikingKilled(const Coords32* at) {
  if (++sSpikingKills == 10) giveElf(ELF_SPIKINGS, ANIMAL, at);
}

void ApImportCrabKilled(const Coords32* at) {
  if (++sCrabKills == 4) giveElf(ELF_CRABS, HACKER, at);
}

void ApImportMineKilled(const Coords32* at) {
  if (++sMineKills == 4) giveElf(ELF_MINES, ANIMAL, at);
}

void ApImportCopterKilled(const Coords32* at) {
  if (++sCopterKills == 7) giveElf(ELF_COPTERS, ANIMAL, at);
}

void ApImportGeneratorKilled(const Coords32* at) { giveElf(ELF_GENERATOR, HACKER, at); }

void ApImportSignaloidKilled(const Coords32* at) {
  if (++sSignaloidKills == 3) giveElf(ELF_SIGNALOIDS, HACKER, at);
}

void ApImportShieldGuardKilled(const Coords32* at) {
  if (++sGuardKills == 3) giveElf(ELF_GUARDS, ANIMAL, at);
}

void ApImportSnowballerKilled(const Coords32* at) {
  if (++sSnowballerKills == 5) giveElf(ELF_SNOWBALLERS, ANIMAL, at);
}

void ApImportWolfKilled(const Coords32* at) {
  if (++sWolfKills == 4) giveElf(ELF_WOLVES, ANIMAL, at);
}

void ApImportFlopperKilled(const Coords32* at) {
  if (++sFlopperKills == 3) giveElf(ELF_FLOPPERS, ANIMAL, at);
}

void ApImportFloorMineKilled(const Coords32* at) {
  if (++sFloorMineKills == 20) giveElf(ELF_FLOOR_MINES, ANIMAL, at);
}

void ApImportLeaperKilled(const Coords32* at) {
  if (++sLeaperKills == 6) giveElf(ELF_LEAPERS, ANIMAL, at);
}

void ApImportTreeFrogKilled(const Coords32* at) {
  if (++sTreeFrogKills == 5) giveElf(ELF_TREE_FROGS, ANIMAL, at);
}

// Location of kill elf enemy counts toward, 0 if none
u16 ApImportKillElf(const struct Entity* e) {
  u8 n;
  if (gStageRun.id != STAGE_NONE) return 0;
  if (e->kind == ENTITY_PROJECTILE) {
    n = ELF_FLOOR_MINES;
  } else switch (e->id) {
    case ENEMY_Z2_HOTTALOOK: n = ELF_BIRFLOW; break;
    case ENEMY_Z2_HOPPER: n = ELF_BEEHITT; break;
    case ENEMY_Z2_TOWER: n = ELF_TOWERS; break;
    case ENEMY_Z2_SPIKEBALL: n = ELF_SPIKEBALLS; break;
    case ENEMY_Z2_VULTURE: n = ELF_VULTURES; break;
    case ENEMY_Z2_SHELL: n = ELF_SHELLS; break;
    case ENEMY_Z2_RING_CANNON: n = ELF_CANNONS; break;
    case ENEMY_Z2_EYE: n = ELF_EYES; break;
    case ENEMY_P_GUARDIAN: n = ELF_GUARDIANS; break;
    case ENEMY_Z2_BEE: n = ELF_BEES; break;
    case ENEMY_Z2_BEE_CARRIER: n = ELF_CARRIERS; break;
    case ENEMY_Z2_MOLE: n = ELF_MOLES; break;
    case ENEMY_Z2_SPIDER: n = ELF_SPIDERS; break;
    case ENEMY_P_HUNTER: n = ELF_HUNTERS; break;
    case ENEMY_Z2_BARRIER_SHIP: n = ELF_SHIPS; break;
    case ENEMY_Z2_FISH: n = ELF_FISH; break;
    case ENEMY_Z2_DOZER: n = ELF_DOZERS; break;
    case ENEMY_Z2_CRAWLER: n = ELF_CRAWLERS; break;
    case ENEMY_Z2_CARRYARM: n = ELF_SPIKINGS; break;
    case ENEMY_Z2_CRAB: n = ELF_CRABS; break;
    case ENEMY_Z2_MINE: n = ELF_MINES; break;
    case ENEMY_Z2_COPTER: n = ELF_COPTERS; break;
    case ENEMY_Z2_GENERATOR: n = ELF_GENERATOR; break;
    case ENEMY_Z2_SIGNALOID: n = ELF_SIGNALOIDS; break;
    case ENEMY_Z2_SHIELD_GUARD: n = ELF_GUARDS; break;
    case ENEMY_Z2_SNOWBALLER:
      if (e->work[0] != 0) return 0;
      n = ELF_SNOWBALLERS;
      break;
    case ENEMY_Z2_WOLF: n = ELF_WOLVES; break;
    case ENEMY_FLOPPER: n = ELF_FLOPPERS; break;
    case ENEMY_Z2_LEAPER: n = ELF_LEAPERS; break;
    case ENEMY_Z2_TREE_FROG: n = ELF_TREE_FROGS; break;
    default: return 0;
  }
  if (n / 16 != ApImportZ2Stage(gApImportSelected)) return 0;
  return AP_LOC_IMPORT_FIRST + n;
}

// By import, placed and kill elves, from block's third id on
static const u8 sElves[AP_IMPORT_COUNT] = {5, 7, 4, 8, 8, 4, 4, 8, 6, 6, 4, 3, 3, 3, 4, 0};

u8 ApImportElfTotal(u8 import) { return sElves[import]; }

u8 ApImportElvesFound(u8 import) {
  u16 first = AP_LOC_IMPORT_FIRST + ApImportZ2Stage(import) * 16 + 2;
  u8 n = 0, i;
  for (i = 0; i < sElves[import]; i++) {
    if (checked(first + i)) n++;
  }
  return n;
}

static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  Pickup* p = (Pickup*)body->parent;
  struct Entity* q = body->enemy->parent;
  if (q->kind == ENTITY_PLAYER) p->z = (void*)q;
}

// 0x080d68b8: bobs about home, home's y creeps to Zero's chest outside scripts
static void drift(Pickup* p) {
  s32 dy = (pZero2->s).coord.y - PIXEL(21) - (p->unk_coord).y;
  if (!(gStageRun.vm.active & VM_ACTIVE)) {
    if (dy >= -32 && dy <= 32) {
      (p->unk_coord).y += dy;
    } else {
      (p->unk_coord).y += dy > 0 ? 32 : -32;
    }
  }
  if (++p->work[2] == 160) p->work[2] = 0;
  (p->coord).x = (p->unk_coord).x + SIN(p->work[2] * 256 / 160) * 12;
  (p->coord).y = (p->unk_coord).y - SIN((p->work[2] % 80) * 256 / 80) * 4;
}

// Zero 3's own nurse, animal and hacker, which are Zero 2's floating ones
static const struct {
  struct MetaspriteHeader hdr;
  struct Subsprite part;
} sSprite = {
  hdr : {ofs : 4, subspriteCount : 1, texture : 0},
  part : {tileNum : 0, size : 1, shape : 0, x : -8, y : -8},
};

// 0x080d6804
static void ImportElf_Init(Pickup* p) {
  const ColorGraphic* g = SELF_REL_PTR(&gDynamicMotionGraphicOffsets[DM144_CYBERELF_NURSE + p->work[1]]);
  u16 tile = AP_ELF_TILE + p->work[1] * 4;
  if (checked(LOCATION(p))) {
    p->flags &= ~(DISPLAY | FLIPABLE);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  LoadGraphic(&g->g, (void*)((tile - (g->g).tileId) * 32 + 0x10000));
  LoadPalette(&g->pal, PLTT_SIZE / 2);
  InitNonAffineMotion((void*)p);
  (p->spr).sprites = (struct MetaspriteHeader*)&sSprite.hdr;
  (p->spr).spriteIdx = 0;
  (p->spr).oam.tileNum = tile;
  p->savedPalID = (g->pal).dst;
  p->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, &sCollision, 64, onCollision);
  p->z = NULL;
  p->work[3] = 0;
  p->unk_coord = p->coord;
  ApAttachElfMarker((struct Entity*)p);
  SET_ITEM_ROUTINE(p, ENTITY_UPDATE);
  ImportElf_Update(p);
}

// Zero 2's four colourings, Zero 3's elf sheets 0..3, at Zero 3's elf pace
static void glow(Pickup* p) {
  const ColorGraphic* g = SELF_REL_PTR(&gDynamicMotionGraphicOffsets[DM144_CYBERELF_NURSE + p->work[1]]);
  u16 tile = AP_ELF_TILE + p->work[1] * 4;
  if (p->work[2] % 5 != 0) return;
  g += (p->work[2] / 5) & 3;
  LoadGraphic(&g->g, (void*)((tile - (g->g).tileId) * 32 + 0x10000));
}

// 0x080bed50
static void sparkle(Pickup* p) {
  struct Entity* q;
  if (p->work[3] != 0 && --p->work[3] != 0) return;
  if (Camera_GetDistance(&gStageRun.vm.camera, &p->coord) > 0x1FFF) return;
  q = AllocEntityLast(gVFXHeaderPtr);
  if (q != NULL) {
    INIT_VFX_ROUTINE(q, VFX_Z2_ELF_TRAIL);
    q->coord = p->coord;
  }
  p->work[3] = 14 + ((RANDOM(RNG_0202f388) & 7) + 1) / 2;
}

static void ImportElf_Update(Pickup* p) {
  drift(p);
  glow(p);
  sparkle(p);
  if (((p->body).status & BODY_STATUS_B2) && p->z != NULL) {
    ApMarkLocationChecked(LOCATION(p));
    PlaySound(SE_NOTIFICATION);
    p->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

/*
  Zero 2's VFX 70 work0 0, three sparkles falling off a floating elf, on Zero 3's elf particle art
  mode1: 0 shown, 1 and 2 blinking
*/
static void Trail_Init(struct VFX* p);
static void Trail_Update(struct VFX* p);

// clang-format off
const VFXRoutine gApZ2ElfTrailRoutine = {
    [ENTITY_INIT] =      Trail_Init,
    [ENTITY_UPDATE] =    Trail_Update,
    [ENTITY_DIE] =       (VFXFunc)DeleteEntity,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// 0x083485a8: loops of each mode
static const u8 sLoops[3] = {3, 2, 2};

// 0x080be9c8
static void Trail_Init(struct VFX* p) {
  struct Entity* s = &p->s;
  InitNonAffineMotion(s);
  ResetDynamicMotion(s);
  SET_XFLIP(p, RANDOM(RNG_0202f388) & 1);
  SET_YFLIP(p, RANDOM(RNG_0202f388) & 1);
  SetMotion(s, MOTION(DM147_CYBERELF_PARTICLE, 0));
  (s->spr).oam.priority = 2;
  s->flags |= DISPLAY;
  s->d.y = 0;
  s->unk_coord.x = s->coord.x;
  s->work[2] = (RANDOM(RNG_0202f388) & 1) * 32;
  s->work[3] = sLoops[0];
  s->mode[1] = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Trail_Update(p);
}

// 0x080beb5c
static void Trail_Update(struct VFX* p) {
  struct Entity* s = &p->s;
  if ((s->motion).state == ANIM_NEXT_GOTO) {
    while (--s->work[3] == 0) {
      if (++s->mode[1] == 3) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
        return;
      }
      s->work[3] = sLoops[s->mode[1]];
    }
  }
  if (s->mode[1] == 1) {
    s->flags = (s->flags & ~DISPLAY) | ((s->motion).duration & 1 ? DISPLAY : 0);
  } else if (s->mode[1] == 2) {
    s->flags = (s->flags & ~DISPLAY) | ((s->motion).duration == 1 ? DISPLAY : 0);
  }
  s->coord.x = s->unk_coord.x + SIN(s->work[2] * 4) * 2;
  s->work[2] = (s->work[2] + 1) % 64;
  s->coord.y += s->d.y++;
  if (Camera_GetDistance(&gStageRun.vm.camera, &s->coord) > 0x1FFF) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  UpdateEntityAnim(s);
}

// 0x0834b2cc
static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 255,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
};

#endif  // AP
