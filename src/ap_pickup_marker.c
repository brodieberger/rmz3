#include "ap.h"

#include "ap_marker.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "spawn.h"
#include "stagerun.h"

#if AP

/*
  The Archipelago logo floating over a pickup whose location is still unchecked.
*/
#define AP_MARKER_PLACE work[1]
#define AP_MARKER_PHASE work[2]

static bool32 ApMarkerParentAlive(const Pickup* p) {
  return ((p->flags & DISPLAY) != 0) && ApPickupIsLocation(p->work[0]);
}

static bool32 ApMarkerUnchecked(const struct Entity* e) {
  return !ApServerChecked(gApPickupPlaces[e->AP_MARKER_PLACE].loc);
}

u16 ApMarkerWindow(void) {
  if (gStageRun.id == STAGE_NONE) return AP_MARKER_LEGACY_TILE;
  if ((u32)gStageRun.id >= AP_MARKER_STAGES ||
      (u32)gSpawnManager.area >= AP_MARKER_AREAS) {
    return 0;
  }
  return gApMarkerTile[gStageRun.id][gSpawnManager.area];
}

u16 ApPillarWindow(void) {
  if ((u32)gStageRun.id >= AP_MARKER_STAGES ||
      (u32)gSpawnManager.area >= AP_MARKER_AREAS) {
    return 0;
  }
  return gApPillarTile[gStageRun.id][gSpawnManager.area];
}

// FALSE where the area has no room
static bool8 drawMarker(struct Entity* e) {
  u16 tile = ApMarkerWindow();
  if (tile == 0) return FALSE;
  MemCopy32(gApMarkerTiles[0], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)),
            AP_MARKER_SMALL_TILES * 32);
  (e->spr).oam.tileNum = tile;
  e->AP_MARKER_PHASE = (u8)((e->AP_MARKER_PHASE + 1) % AP_MARKER_BOB_PERIOD);
  e->coord = e->unk_28->coord;
  (e->coord).y += PIXEL(AP_MARKER_CENTER_Y + gApMarkerBob[e->AP_MARKER_PHASE]);
  return TRUE;
}

static void ApPickupMarkerUpdate(struct Entity* e) {
  if (!ApMarkerParentAlive((const Pickup*)e->unk_28) || !ApMarkerUnchecked(e) || !drawMarker(e)) {
    DeleteEntity(e);
  }
}

// Over a legacy stage's elf or its capsule, gone with it
static void ApElfMarkerUpdate(struct Entity* e) {
  if (!(e->unk_28->flags & DISPLAY) || !drawMarker(e)) DeleteEntity(e);
}

static struct Entity* createMarker(struct Entity* parent, void* update) {
  struct Entity* e = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);
  if (e == NULL) return NULL;
  e->onUpdate = update;
  e->id = 0;
  e->renderPrio = 1;
  e->tileNum = 0;
  e->palID = 0;
  e->unk_28 = parent;
  e->coord = parent->coord;
  e->AP_MARKER_PHASE = 0;
  InitNonAffineMotion(e);
  (e->spr).sprites = (struct MetaspriteHeader*)&gApMarkerSprite.hdr;
  (e->spr).oam.paletteNum = AP_MARKER_PAL;
  (e->spr).spriteIdx = 0;
  (e->spr).oam.tileNum = ApMarkerWindow();
  e->flags |= DISPLAY;
  return e;
}

void ApAttachElfMarker(struct Entity* parent) { createMarker(parent, ApElfMarkerUpdate); }

void ApInitPickupLocation(Pickup* p) {
  struct Entity* e;
  u8 place;

  p->AP_PICKUP_PLACE = AP_PICKUP_PLACE_NONE;
  /* Dropped pickups, not locations. */
  if (p->work[1] < 2) {
    return;
  }
  place = ApPickupPlaceIndex((gStageRun.id == STAGE_NONE) ? (AP_PICKUP_IMPORT + gApImportSelected) : gStageRun.id,
                             (p->coord).x, (p->coord).y);
  if (place == AP_PICKUP_PLACE_NONE) {
    return;
  }
  p->AP_PICKUP_PLACE = place;

  if (ApInDemo()) {
    return;
  }
  /* Don't render on mettaur mode, since it causes issues with VRAM */
  if (gSpawnManager.mettaursEnabled) {
    return;
  }
  if (ApServerChecked(gApPickupPlaces[place].loc)) {
    return;
  }
  if (ApMarkerWindow() == 0) {
    return;
  }

  e = createMarker((struct Entity*)p, ApPickupMarkerUpdate);
  if (e != NULL) e->AP_MARKER_PLACE = place;
}

#endif /* AP */
