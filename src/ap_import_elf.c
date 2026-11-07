#include "ap.h"

#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "zero.h"

#include "constants/song.h"

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

static void giveElf(u8 n) {
  struct Entity* p;

  if (n / AP_LOC_IMPORT_STRIDE != ApImportZ2Stage(gApImportSelected)) return;
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

u8 ApImportElvesFound(void) {
  u8 n = 0;
  u16 i;

  for (i = AP_LOC_IMPORT_FIRST; i <= AP_MAX_LOCATION_ID; i++) {
    if ((i - AP_LOC_IMPORT_FIRST) % AP_LOC_IMPORT_STRIDE >= 2 && checked(i)) n++;
  }
  return n;
}

static void onCollision(struct Body* body, Coords32* r1 UNUSED, Coords32* r2 UNUSED) {
  Pickup* p = (Pickup*)body->parent;
  struct Entity* q = body->enemy->parent;
  if (q->kind == ENTITY_PLAYER) p->z = (void*)q;
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
  SET_ITEM_ROUTINE(p, ENTITY_UPDATE);
  ImportElf_Update(p);
}

static void ImportElf_Update(Pickup* p) {
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
