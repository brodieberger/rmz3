#include "ap.h"

#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "stagerun.h"
#include "trig.h"
#include "zero.h"

#include "constants/song.h"
#include "constants/stage_id.h"

#if AP

/*
  A cyber elf pickup in a Zero 2 level. Temporary implemenattion. Just spawns as an archipelago logo for now.
*/

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
  Elves themselves aren't actually implemented.
  They are just given to Zero immediately.
*/
#define ELF_BIRFLOW 150  // Crystal Cave
#define ELF_BEEHITT 151
#define ELF_TOWERS 3  // Sand Wilderness
#define ELF_SPIKEBALLS 4
#define ELF_VULTURES 5
#define ELF_SHELLS 196  // Temple of Flame
#define ELF_CANNONS 180  // Neo Arcadia Temple
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

static void giveElf(u8 n) {
  struct Entity* p;

  if (gStageRun.id != STAGE_NONE || n / 16 != ApImportZ2Stage(gApImportSelected)) return;
  if (checked(AP_LOC_IMPORT_FIRST + n)) return;
  p = AllocEntityLast(gPickupHeaderPtr);
  if (p == NULL) return;
  INIT_ITEM_ROUTINE(p, ITEM_AP_IMPORT_ELF);
  (p->coord).x = (pZero2->s).coord.x;
  (p->coord).y = (pZero2->s).coord.y - PIXEL(16);
  p->work[0] = n;
}

void ApImportResetKills(void) {
  sHottalookKills = 0;
  sHopperKills = 0;
  sTowerKills = 0;
  sSpikeballKills = 0;
  sVultureKills = 0;
  sShellKills = 0;
  sCannonKills = 0;
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

void ApImportHottalookKilled(void) {
  if (++sHottalookKills == 12) giveElf(ELF_BIRFLOW);
}

void ApImportHopperKilled(void) {
  if (++sHopperKills == 3) giveElf(ELF_BEEHITT);
}

void ApImportTowerKilled(void) {
  if (++sTowerKills == 3) giveElf(ELF_TOWERS);
}

void ApImportSpikeballKilled(void) {
  if (++sSpikeballKills == 4) giveElf(ELF_SPIKEBALLS);
}

// Vultures, not perches
void ApImportVultureKilled(void) {
  if (++sVultureKills == 5) giveElf(ELF_VULTURES);
}

void ApImportShellKilled(void) {
  if (++sShellKills == 5) giveElf(ELF_SHELLS);
}

void ApImportRingCannonKilled(void) {
  if (++sCannonKills == 3) giveElf(ELF_CANNONS);
}

void ApImportBeeKilled(void) {
  if (++sBeeKills == 10) giveElf(ELF_BEES);
}

void ApImportCarrierKilled(void) {
  if (++sCarrierKills == 3) giveElf(ELF_CARRIERS);
}

void ApImportMoleKilled(void) {
  if (++sMoleKills == 4) giveElf(ELF_MOLES);
}

void ApImportSpiderKilled(void) {
  if (++sSpiderKills == 3) giveElf(ELF_SPIDERS);
}

void ApImportHunterKilled(void) {
  if (++sHunterKills == 8) giveElf(ELF_HUNTERS);
}

void ApImportBarrierShipKilled(void) {
  if (++sShipKills == 5) giveElf(ELF_SHIPS);
}

void ApImportFishKilled(void) {
  if (++sFishKills == 5) giveElf(ELF_FISH);
}

void ApImportDozerKilled(void) {
  if (++sDozerKills == 4) giveElf(ELF_DOZERS);
}

void ApImportCrawlerKilled(void) {
  if (++sCrawlerKills == 4) giveElf(ELF_CRAWLERS);
}

void ApImportSpikingKilled(void) {
  if (++sSpikingKills == 10) giveElf(ELF_SPIKINGS);
}

void ApImportCrabKilled(void) {
  if (++sCrabKills == 4) giveElf(ELF_CRABS);
}

void ApImportMineKilled(void) {
  if (++sMineKills == 4) giveElf(ELF_MINES);
}

void ApImportCopterKilled(void) {
  if (++sCopterKills == 7) giveElf(ELF_COPTERS);
}

void ApImportGeneratorKilled(void) { giveElf(ELF_GENERATOR); }

void ApImportSignaloidKilled(void) {
  if (++sSignaloidKills == 3) giveElf(ELF_SIGNALOIDS);
}

void ApImportShieldGuardKilled(void) {
  if (++sGuardKills == 3) giveElf(ELF_GUARDS);
}

void ApImportSnowballerKilled(void) {
  if (++sSnowballerKills == 5) giveElf(ELF_SNOWBALLERS);
}

void ApImportWolfKilled(void) {
  if (++sWolfKills == 4) giveElf(ELF_WOLVES);
}

void ApImportFlopperKilled(void) {
  if (++sFlopperKills == 3) giveElf(ELF_FLOPPERS);
}

void ApImportFloorMineKilled(void) {
  if (++sFloorMineKills == 20) giveElf(ELF_FLOOR_MINES);
}

void ApImportLeaperKilled(void) {
  if (++sLeaperKills == 6) giveElf(ELF_LEAPERS);
}

void ApImportTreeFrogKilled(void) {
  if (++sTreeFrogKills == 5) giveElf(ELF_TREE_FROGS);
}

// By import, placed and kill elves, from block's third id on
static const u8 sElves[AP_IMPORT_COUNT] = {4, 6, 4, 8, 8, 2, 4, 8, 6, 6, 4, 3, 3, 3, 4};

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

// 0x080d68b8: bobs about home, home's y creeps to Zero's
static void drift(Pickup* p) {
  s32 dy = (pZero2->s).coord.y - (p->unk_coord).y;
  if (dy >= -32 && dy <= 32) {
    (p->unk_coord).y += dy;
  } else {
    (p->unk_coord).y += dy > 0 ? 32 : -32;
  }
  if (++p->work[2] == 160) p->work[2] = 0;
  (p->coord).x = (p->unk_coord).x + SIN(p->work[2] * 256 / 160) * 12;
  (p->coord).y = (p->unk_coord).y - SIN((p->work[2] % 80) * 256 / 80) * 4;
}

static void ImportElf_Init(Pickup* p) {
  if (checked(LOCATION(p))) {
    p->flags &= ~(DISPLAY | FLIPABLE);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  InitNonAffineMotion((void*)p);
  SetSpriteAnimation(p, MOTION(SM176_RESULT_DISK, 11));
  p->flags |= DISPLAY | FLIPABLE;
  INIT_BODY(p, &sCollision, 64, onCollision);
  p->z = NULL;
  p->unk_coord = p->coord;
  SET_ITEM_ROUTINE(p, ENTITY_UPDATE);
  ImportElf_Update(p);
}

static void ImportElf_Update(Pickup* p) {
  if (p->work[1] != 0) drift(p);
  UpdateSpriteAnimation(p);
  if (((p->body).status & BODY_STATUS_B2) && p->z != NULL) {
    ApMarkLocationChecked(LOCATION(p));
    PlaySound(SE_NOTIFICATION);
    p->flags &= ~(DISPLAY | FLIPABLE);
    EXIT_BODY(p);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// Same as the secret disk's (pickup/disk.c)
static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 255,
  layer : 0x00000001,
  range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
};

#endif  // AP
