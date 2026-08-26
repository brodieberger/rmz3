#include "ap.h"

#undef ApSpawnExLifeOrbit

#include "ap_orbit.h"
#include "constants/entity/item.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "spawn.h"
#include "stagerun.h"

#if AP

// The archipelago logo that rotates around an unchecked item in itemsanity.

#define AP_ORBIT_TIMER work[2]
#define AP_ORBIT_STEP work[3]

static bool32 ApOrbitParentAlive(const Pickup* p) {
  return ((p->flags & DISPLAY) != 0) && (p->work[0] == ITEM_EXLIFE);
}

// The client may only tell us the location is checked after the pickup has already spawned.
static bool32 ApOrbitStillUnchecked(const Pickup* p) {
  return !ApServerChecked(ApExLifeLocation(gStageRun.id, (p->coord).x));
}

static void ApExLifeOrbitUpdate(struct Entity* e) {
  const Pickup* p = (const Pickup*)e->unk_28;

  if (!ApOrbitParentAlive(p) || !ApOrbitStillUnchecked(p)) {
    DeleteEntity(e);
    return;
  }

  MemCopy32(gApOrbitTiles, (void*)(VRAM + BG_VRAM_SIZE + (AP_ORBIT_TILE * 32)), sizeof(gApOrbitTiles));

  e->coord = p->coord;
  e->AP_ORBIT_TIMER++;
  if (e->AP_ORBIT_TIMER >= AP_ORBIT_STEP_FRAMES) {
    u8 lap;
    e->AP_ORBIT_TIMER = 0;
    e->AP_ORBIT_STEP = (u8)((e->AP_ORBIT_STEP + 1) % AP_ORBIT_STEPS);

    lap = (u8)(e->AP_ORBIT_STEP / AP_ORBIT_FRAMES);
    (e->spr).oam.tileNum = (u16)(AP_ORBIT_TILE + ((AP_ORBIT_DOTS - lap) % AP_ORBIT_DOTS));
  }
  (e->spr).spriteIdx = (u8)(e->AP_ORBIT_STEP % AP_ORBIT_FRAMES);
}

void ApSpawnExLifeOrbit(Pickup* p) {
  struct Entity* e;

  // Dropped 1-UPs, which are not locations.
  if (p->work[1] < 2) {
    return;
  }
  if (ApInDemo()) {
    return;
  }
  // Don't render on mettaur mode, since it causes issues with VRAM
  if (gSpawnManager.mettaursEnabled) {
    return;
  }
  if (!ApOrbitStillUnchecked(p)) {
    return;
  }

  e = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);
  if (e == NULL) {
    return;
  }

  e->onUpdate = (void*)ApExLifeOrbitUpdate;
  e->id = 0;
  e->renderPrio = 1;
  e->tileNum = 0;
  e->palID = 0;
  e->unk_28 = (struct Entity*)p;
  e->coord = p->coord;
  e->AP_ORBIT_TIMER = 0;
  e->AP_ORBIT_STEP = 0;

  InitNonAffineMotion(e);
  (e->spr).sprites = (struct MetaspriteHeader*)gApOrbitSprite.hdr;
  (e->spr).oam.tileNum = AP_ORBIT_TILE;
  (e->spr).oam.paletteNum = AP_ORBIT_PAL;
  (e->spr).spriteIdx = 0;
  e->flags |= DISPLAY;
}

void (*const gApSpawnExLifeOrbitFn)(Pickup* p) = ApSpawnExLifeOrbit;

#endif /* AP */
