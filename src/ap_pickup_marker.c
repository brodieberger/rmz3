#include "ap.h"

#undef ApSpawnPickupMarker

#include "ap_marker.h"
#include "constants/entity/item.h"
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

static u16 ApMarkerWindow(void) {
  if ((u32)gStageRun.id >= AP_MARKER_STAGES ||
      (u32)gSpawnManager.area >= AP_MARKER_AREAS) {
    return 0;
  }
  return gApMarkerTile[gStageRun.id][gSpawnManager.area];
}

static void ApPickupMarkerUpdate(struct Entity* e) {
  const Pickup* p = (const Pickup*)e->unk_28;
  u16 tile;

  if (!ApMarkerParentAlive(p) || !ApMarkerUnchecked(e)) {
    DeleteEntity(e);
    return;
  }

  if ((e->spr).spriteIdx == AP_MARKER_BIG) {
    (e->spr).oam.tileNum = wStaticGraphicTilenums[AP_MARKER_BIG_MOTION];
  } else {
    tile = ApMarkerWindow();
    if (tile == 0) {
      DeleteEntity(e);
      return;
    }
    MemCopy32(gApMarkerTiles[0], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)),
              AP_MARKER_SMALL_TILES * 32);
    (e->spr).oam.tileNum = tile;
  }

  e->AP_MARKER_PHASE = (u8)((e->AP_MARKER_PHASE + 1) % AP_MARKER_BOB_PERIOD);
  e->coord = p->coord;
  (e->coord).y += PIXEL(AP_MARKER_CENTER_Y + gApMarkerBob[e->AP_MARKER_PHASE]);
}

void ApSpawnPickupMarker(Pickup* p) {
  struct Entity* e;
  u8 place;

  /* Dropped pickups, not locations. */
  if (p->work[1] < 2) {
    return;
  }
  if (ApInDemo()) {
    return;
  }
  /* Don't render on mettaur mode, since it causes issues with VRAM */
  if (gSpawnManager.mettaursEnabled) {
    return;
  }
  place = ApPickupPlaceIndex(gStageRun.id, (p->coord).x, (p->coord).y);
  if (place == AP_PICKUP_PLACE_NONE) {
    return;
  }
  if (ApServerChecked(gApPickupPlaces[place].loc)) {
    return;
  }
  if (p->work[0] != ITEM_EXLIFE && ApMarkerWindow() == 0) {
    return;
  }

  e = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);
  if (e == NULL) {
    return;
  }

  e->onUpdate = (void*)ApPickupMarkerUpdate;
  e->id = 0;
  e->renderPrio = 1;
  e->tileNum = 0;
  e->palID = 0;
  e->unk_28 = (struct Entity*)p;
  e->coord = p->coord;
  e->AP_MARKER_PLACE = place;
  e->AP_MARKER_PHASE = 0;

  InitNonAffineMotion(e);
  (e->spr).sprites = (struct MetaspriteHeader*)gApMarkerSprite.hdr;
  (e->spr).oam.paletteNum = AP_MARKER_PAL;
  /*
    Full size logo for one ups
  */
  (e->spr).spriteIdx = p->work[0] == ITEM_EXLIFE ? AP_MARKER_BIG : AP_MARKER_SMALL;
  (e->spr).oam.tileNum = (e->spr).spriteIdx == AP_MARKER_BIG
                             ? wStaticGraphicTilenums[AP_MARKER_BIG_MOTION]
                             : ApMarkerWindow();
  e->flags |= DISPLAY;
}

void (*const gApSpawnPickupMarkerFn)(Pickup* p) = ApSpawnPickupMarker;

#endif /* AP */
