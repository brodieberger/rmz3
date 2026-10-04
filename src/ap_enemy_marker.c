#include "ap.h"

#include "ap_marker.h"
#include "entity.h"
#include "game.h"
#include "gfx.h"
#include "global.h"
#include "constants/metatile.h"
#include "metatile.h"
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
    if (s->e == e && !((s->flag & SF_ZOMBIE) && e->mode[0] < ENTITY_DIE)) {
      return s;
    }
  }
  return NULL;
}

u8 ApDropMarkOf(const struct Entity* e) {
  const struct SpawnedEntity* s = ApSpawnOf(e);
  if (s == NULL && e->unk_28 != NULL) {
    s = ApSpawnOf(e->unk_28);
    if (s != NULL && (s->e)->id != e->id) {
      s = NULL;
    }
  }
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
  part = (const struct Subsprite*)((const u8*)(e->spr).sprites + hdr->ofs);
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
  Draw a pillar cannon's new pillar sprite.
*/
#define AP_PILLAR_SID unk_coord.x
#define AP_PILLAR_CANNON unk_28

static void ApPillarUpdate(struct Entity* m) {
  const struct Entity* e = m->AP_PILLAR_CANNON;
  const struct SpawnedEntity* s = ApSpawnOf(e);
  u16 tile;

  if (s == NULL || s->sid != m->AP_PILLAR_SID || e->mode[0] >= ENTITY_DIE) {
    DeleteEntity(m);
    return;
  }
  tile = ApPillarWindow();
  if (tile == 0) {
    m->flags &= ~DISPLAY; /* the area has no room for it */
    return;
  }
  MemCopy32(gApPillarTiles[0], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)), AP_PILLAR_TILES * 32);
  (m->spr).oam.tileNum = tile;
  (m->spr).oam.paletteNum = wStaticMotionPalIDs[SM008_PILLAR_CANNON];
  m->flags |= DISPLAY;
  m->coord = e->coord;
}

static bool32 ApCreatePillar(struct SpawnedEntity* s) {
  struct Entity* m = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);
  const Coords32* c = &(s->e)->coord;
  s32 tiles;
  metatile_attr_t shape;

  if (m == NULL) {
    return FALSE;
  }
  for (tiles = 1; tiles <= AP_PILLAR_FLOOR; tiles++) {
    shape = GetMetatileAttr(c->x, c->y + PIXEL(16 * tiles)) & 0xF;
    if (shape >= SHAPE_BLOCK && shape <= SHAPE_SLOPE13) {
      break;
    }
  }
  shape = GetMetatileAttr(c->x, c->y + PIXEL(16 * tiles)) & 0xF;
  if (shape >= SHAPE_SLOPE2 && shape <= SHAPE_SLOPE13) {
    tiles++;
  }
  m->onUpdate = (void*)ApPillarUpdate;
  m->id = 0;
  m->renderPrio = (s->e)->renderPrio + 1; /* render behind the cannon */
  m->tileNum = 0;
  m->palID = 0;
  m->AP_PILLAR_CANNON = s->e;
  m->AP_PILLAR_SID = s->sid;
  m->coord = *c;

  InitNonAffineMotion(m);
  (m->spr).sprites = (struct MetaspriteHeader*)gApPillarSprite.hdr;
  (m->spr).spriteIdx = tiles * 2 - 1;
  return TRUE;
}

/*
  Render markers above enemies heads, and the pillars under moved Pillar Cannons. Gets
  messed up in mettaur mode but who cares.
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
    if (s->e == NULL || (s->flag & SF_ZOMBIE) || (s->e)->mode[0] >= ENTITY_DIE) {
      continue;
    }
    if ((s->flag & (AP_SPAWN_PILLAR | AP_SPAWN_HAS_PILLAR)) == AP_SPAWN_PILLAR
        && ApCreatePillar(s)) {
      s->flag |= AP_SPAWN_HAS_PILLAR;
    }
    if (s->flag & AP_SPAWN_HAS_MARKER) {
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
