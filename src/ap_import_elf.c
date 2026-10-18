#include "ap.h"

#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"

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

#define LOCATION(p) (AP_LOC_IMPORT_ELF_FIRST + (p)->work[0])

static bool32 checked(u16 loc) {
  return ApServerChecked(loc) || (gAp.checkedLocations[loc >> 3] & (1 << (loc & 7)));
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
