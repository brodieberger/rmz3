#include "ap.h"

#include "ap_marker.h"
#include "entity.h"
#include "game.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "spawn.h"
#include "stagerun.h"

#if AP

/*
  Disk drops by enemy spawn point (ap_enemy_marker.c)
  Also marks enemies with an icon.
*/
#define AP_ENEMY_MARKER_SID unk_coord.x /* the spawn point, since an enemy slot is reused */
#define AP_ENEMY_MARKER_PHASE work[1]
#define AP_ENEMY_MARKER_REACH work[2] /* px the enemy's sprite has reached above its origin */
#define AP_ENEMY_MARKER_GAP 6        /* px between the top of the sprite and the logo's center */

static const u8 sApSubspriteHeight[3][4] = {{8, 16, 32, 64}, {8, 8, 16, 32}, {16, 32, 32, 64}};

static u8 ApDropMarkOfSpawn(const struct SpawnedEntity* s) {
  return gSpawnManager.template[gSpawnManager.points[s->sid].idx].attr >> AP_DROP_MARK_SHIFT;
}

static struct SpawnedEntity* ApSpawnOf(const struct Entity* e) {
  struct SpawnedEntity* s;

  for (s = gSpawnManager.list; s != NULL; s = s->next) {
    if (s->e == e) {
      return s;
    }
  }
  return NULL;
}

u8 ApDropMarkOf(const struct Entity* e) {
  const struct SpawnedEntity* s = ApSpawnOf(e);

  return s == NULL ? AP_DROP_MARK_NONE : ApDropMarkOfSpawn(s);
}

/* How far the enemy's current frame reaches above the start. */
static u8 ApSpriteReach(const struct Entity* e) {
  const struct MetaspriteHeader* hdr;
  const struct Subsprite* part;
  s32 i, top, reach = 0;

  if (!(e->flags & USE_COMMON_OAM_RENDERER) || (e->spr).sprites == NULL) {
    return 0;
  }
  hdr = &(e->spr).sprites[(e->spr).spriteIdx];
  part = (const struct Subsprite*)((const u8*)hdr + hdr->ofs);
  for (i = 0; i < hdr->subspriteCount; i++) {
    top = part[i].y;
    if ((e->spr).yflip) {
      top = -(top + sApSubspriteHeight[part[i].shape][part[i].size]);
    }
    if (-top > reach) {
      reach = -top;
    }
  }
  return reach > 0xFF ? 0xFF : reach;
}

static bool32 ApDropMarkUnchecked(u8 mark) {
  return !ApServerChecked(ApDropRowDisk(mark));
}

static void ApEnemyMarkerUpdate(struct Entity* m) {
  const struct Entity* e = m->unk_28;
  struct SpawnedEntity* s = ApSpawnOf(e);
  u16 tile;
  u8 reach;

  if (s == NULL || s->sid != m->AP_ENEMY_MARKER_SID) {
    DeleteEntity(m);
    return;
  }
  if (e->mode[0] >= ENTITY_DIE || !ApDropMarkUnchecked(ApDropMarkOfSpawn(s))) {
    /* swap marker */
    s->flag &= ~AP_SPAWN_HAS_MARKER;
    DeleteEntity(m);
    return;
  }

  tile = ApMarkerWindow();
  if (tile == 0) {
    m->flags &= ~DISPLAY;
    return;
  }
  MemCopy32(gApMarkerTiles[0], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)),
            AP_MARKER_SMALL_TILES * 32);
  (m->spr).oam.tileNum = tile;
  m->flags |= DISPLAY;

  reach = ApSpriteReach(e);
  if (reach > m->AP_ENEMY_MARKER_REACH) {
    m->AP_ENEMY_MARKER_REACH = reach;
  }
  m->AP_ENEMY_MARKER_PHASE = (u8)((m->AP_ENEMY_MARKER_PHASE + 1) % AP_MARKER_BOB_PERIOD);
  m->coord = e->coord;
  (m->coord).y -= PIXEL(m->AP_ENEMY_MARKER_REACH + AP_ENEMY_MARKER_GAP);
  (m->coord).y += PIXEL(gApMarkerBob[m->AP_ENEMY_MARKER_PHASE]);
}

static bool32 ApCreateEnemyMarker(struct SpawnedEntity* s) {
  struct Entity* m = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);

  if (m == NULL) {
    return FALSE;
  }
  m->onUpdate = (void*)ApEnemyMarkerUpdate;
  m->id = 0;
  m->renderPrio = 1;
  m->tileNum = 0;
  m->palID = 0;
  m->unk_28 = s->e;
  m->coord = (s->e)->coord;
  m->AP_ENEMY_MARKER_SID = s->sid;
  m->AP_ENEMY_MARKER_PHASE = 0;
  m->AP_ENEMY_MARKER_REACH = 0;

  InitNonAffineMotion(m);
  (m->spr).sprites = (struct MetaspriteHeader*)gApMarkerSprite.hdr;
  (m->spr).oam.paletteNum = AP_MARKER_PAL;
  (m->spr).spriteIdx = AP_MARKER_SMALL;
  (m->spr).oam.tileNum = ApMarkerWindow();
  return TRUE;
}

/*
  Render markers above enemies heads. Gets messed up in mettaur mode but who cares.
*/
void ApUpdateEnemyMarkers(void) {
  struct SpawnedEntity* s;
  u8 mark;

  if (gGameState.mode[0] != MAINGAME || gGameState.mode[1] != OVERWORLD) {
    return;
  }
  if (ApInDemo() || gSpawnManager.mettaursEnabled) {
    return;
  }
  for (s = gSpawnManager.list; s != NULL; s = s->next) {
    if (s->e == NULL || (s->flag & AP_SPAWN_HAS_MARKER) || (s->e)->mode[0] >= ENTITY_DIE) {
      continue;
    }
    mark = ApDropMarkOfSpawn(s);
    if (mark == AP_DROP_MARK_NONE || !ApDropMarkUnchecked(mark)) {
      continue;
    }
    if (ApCreateEnemyMarker(s)) {
      s->flag |= AP_SPAWN_HAS_MARKER;
    }
  }
}

#endif /* AP */
