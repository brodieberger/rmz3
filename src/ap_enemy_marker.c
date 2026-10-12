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
#include "story.h"
#include "vfx.h"
#include "constants/entity/enemy.h"

#if AP

/*
  Disk drops by enemy spawn point (ap_enemy_marker.c)
  Also marks enemies with an icon.
*/
#define AP_ENEMY_MARKER_SID unk_coord.x /* the spawn point, since an enemy slot is reused */
#define AP_ENEMY_MARKER_NO_SID (-1)     /* follows the enemy itself */
#define AP_ENEMY_MARKER_ID work[0]      /* the enemy's id that needs the marker */
#define AP_ENEMY_MARKER_PHASE work[1]
#define AP_ENEMY_MARKER_REACH work[2] /* px the enemy's sprite has reached above its origin */
#define AP_ENEMY_MARKER_DISK work[3]
#define AP_ENEMY_MARKER_GAP 6        /* px between the top of the sprite and the logo's center */
#define AP_ENEMY_MARKER_SLICE 2

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

static struct SpawnedEntity* ApCreditSpawnOf(const struct Entity* e) {
  struct SpawnedEntity* s = ApSpawnOf(e);
  if (s == NULL && e->unk_28 != NULL) {
    s = ApSpawnOf(e->unk_28);
    if (s != NULL && (s->e)->id != e->id) {
      s = NULL;
    }
  }
  return s;
}

u8 ApDropMarkOf(const struct Entity* e) {
  const struct SpawnedEntity* s = ApCreditSpawnOf(e);
  return s == NULL ? AP_DROP_MARK_NONE : ApDropMarkOfSpawn(s);
}

static bool32 ApEnemyLive(const struct Entity* e) {
  const struct Entity* p;

  for (p = gEnemyHeaderPtr->head; p != (struct Entity*)&gEnemyHeaderPtr->tail; p = p->next) {
    if (p == e) {
      return TRUE;
    }
  }
  return FALSE;
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

static void ApEnemyMarkerUpdate(struct Entity* m) {
  const struct Entity* e = m->unk_28;
  struct SpawnedEntity* s = NULL;
  u16 tile;
  u8 reach;

  if (m->AP_ENEMY_MARKER_SID == AP_ENEMY_MARKER_NO_SID) {
    if (!ApEnemyLive(e) || e->id != m->AP_ENEMY_MARKER_ID) {
      DeleteEntity(m);
      return;
    }
  } else {
    s = ApSpawnOf(e);
    if (s == NULL || s->sid != m->AP_ENEMY_MARKER_SID) {
      DeleteEntity(m);
      return;
    }
  }
  if (e->mode[0] >= ENTITY_DIE || ApServerChecked(m->AP_ENEMY_MARKER_DISK)) {
    /* swap marker */
    if (s != NULL) {
      s->flag &= ~AP_SPAWN_HAS_MARKER;
    }
    DeleteEntity(m);
    return;
  }

  tile = ApMarkerWindow();
  if (tile == 0 || !(e->flags & DISPLAY) || FLAG(gCurStory.s.gameflags, IN_CYBERSPACE)) {
    /* no room, an enemy not drawn (a Volcaire's spawn point), or cyberspace, where TryDropZakoDisk
       function would drop nothing */
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

static bool32 ApHasEnemyMarker(const struct Entity* e) {
  const struct Entity* m;

  for (m = gVFXHeaderPtr->head; m != (struct Entity*)&gVFXHeaderPtr->tail; m = m->next) {
    if (m->onUpdate == (void*)ApEnemyMarkerUpdate && m->unk_28 == e) {
      return TRUE;
    }
  }
  return FALSE;
}

static bool32 ApCreateEnemyMarker(struct Entity* e, s32 sid, u8 disk) {
  struct Entity* m = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);

  if (m == NULL) {
    return FALSE;
  }
  m->onUpdate = (void*)ApEnemyMarkerUpdate;
  m->id = 0;
  m->renderPrio = 1;
  m->tileNum = 0;
  m->palID = 0;
  m->unk_28 = e;
  m->coord = e->coord;
  m->AP_ENEMY_MARKER_SID = sid;
  m->AP_ENEMY_MARKER_ID = e->id;
  m->AP_ENEMY_MARKER_PHASE = 0;
  m->AP_ENEMY_MARKER_REACH = 0;
  m->AP_ENEMY_MARKER_DISK = disk;

  InitNonAffineMotion(m);
  (m->spr).sprites = (struct MetaspriteHeader*)gApMarkerSprite.hdr;
  (m->spr).oam.paletteNum = AP_MARKER_PAL;
  (m->spr).spriteIdx = AP_MARKER_SMALL;
  (m->spr).oam.tileNum = ApMarkerWindow();
  return TRUE;
}

/*
  For all enemies that are not marked through normal spawning
  Giant elevator enemies, falling trash blocks in WR Factory, and splitting volcaires.
*/
static void ApMarkCountingEnemies(void) {
  const struct EntityHeader* h = gEnemyHeaderPtr;
  const struct SpawnedEntity* s;
  struct Entity* e;
  s32 i;
  u8 mark, disk;

  for (i = 0; i < AP_ENEMY_MARKER_SLICE; i++) {
    e = (struct Entity*)((u8*)h->arr
                         + ((gStageRun.frame * AP_ENEMY_MARKER_SLICE + i) % h->length) * h->size);
    if (!ApEnemyLive(e) || e->mode[0] >= ENTITY_DIE
        || (e->flags & (DISPLAY | COLLIDABLE)) != (DISPLAY | COLLIDABLE)) {
      continue; /* also a chute, aka not an enemy */
    }
    s = ApCreditSpawnOf(e);
    mark = s == NULL ? AP_DROP_MARK_NONE : ApDropMarkOfSpawn(s);
    if (mark != AP_DROP_MARK_NONE && (s->e == e || ((s->e)->flags & DISPLAY))) {
      continue;
    }
    disk = ApDropDisk(e, mark);
    if (disk != 0 && !ApServerChecked(disk) && !ApHasEnemyMarker(e)) {
      ApCreateEnemyMarker(e, AP_ENEMY_MARKER_NO_SID, disk);
    }
  }
}

/*
  Chutes and the mousehole enemies.
*/
static s32 ApSpawnedFrom(s16 sid) {
  struct SpawnedEntity* s;
  s32 out = 0;

  for (s = gSpawnManager.list; s != NULL; s = s->next) {
    if (s->sid == sid) {
      out++;
    }
  }
  return out;
}

static void ApSpawnNamed(s16 sid, s32 x, s32 y) {
  const struct SpawnTemplate* t = &gSpawnManager.template[gSpawnManager.points[sid].idx];
  struct SpawnedEntity* s;
  struct Entity* e;

  if (gSpawnManager.remaining == 0) {
    return;
  }
  e = CreateStageEntity(t->kind, t->id);
  if (e == NULL) {
    return;
  }
  s = ApAllocStageEntity();
  e->work[0] = t->work0;
  e->work[1] = t->work1;
  (e->coord).x = x;
  (e->coord).y = y;
  s->e = e;
  s->sid = sid;
  s->flag = t->flag;
}

/*
  The chute drop for Weapon Repair Factory. Set to avoid being the junk spawn.
*/
void FUN_0808d0b0(s32 x, s32 y, u8 kind);

void ApChuteDrop(s32 x, s32 y, u8 kind) {
  if (gSpawnManager.points[0].idx == 0) {
    FUN_0808d0b0(x, y, kind);
    return;
  }
  if (ApSpawnedFrom(0) < AP_CHUTE_ENEMIES && gSpawnManager.remaining != 0
      && !gSpawnManager.mettaursEnabled && !gSpawnManager.mmbn4EnemiesEnabled) {
    ApSpawnNamed(0, x, y);
  }
}

/*
  A Lemmingles nest's mouse function.
*/
void FUN_0806e590(struct Entity* e, u8 kind1, u8 kind2, u8 kind3);

void ApNestSpawn(struct Entity* nest, u8 kind1, u8 kind2, u8 kind3) {
  s16 end = 0;

  while (gSpawnManager.points[end].x != 0x7FFFFFFF) {
    end++;
  }
  if (gSpawnManager.points[end].idx == 0 || nest->work[0] == 4 || gSpawnManager.mettaursEnabled
      || gSpawnManager.mmbn4EnemiesEnabled) {
    FUN_0806e590(nest, kind1, kind2, kind3);
    return;
  }
  ((struct Enemy*)nest)->buffer[0] &= ~(1 << kind3);
  if (ApSpawnedFrom(end) < AP_NEST_ENEMIES) {
    ApSpawnNamed(end, (nest->coord).x, (nest->coord).y);
  }
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
  Graphic as a warning for Volcaires ready to spawn under a tile.
*/
#define AP_PUFF_TIMER work[2]
#define AP_PUFF_THROWN buffer[4]

static void ApVolcairePuff(struct SpawnedEntity* s) {
  struct Enemy* e = (struct Enemy*)s->e;
  struct Entity* puff;
  Coords32 c;

  if ((e->s).kind != ENTITY_ENEMY || (e->s).id != ENEMY_VOLCAIRE || (e->s).mode[1] != 1
      || e->AP_PUFF_THROWN > 3 || ((e->s).AP_PUFF_TIMER != 32 && (e->s).AP_PUFF_TIMER != 16)) {
    s->flag &= ~AP_SPAWN_PUFFED;
    return;
  }
  if (s->flag & AP_SPAWN_PUFFED) {
    return;
  }
  s->flag |= AP_SPAWN_PUFFED;
  c.x = gSpawnManager.points[s->sid].x * PIXEL(16) + PIXEL(8);
  c.y = (gSpawnManager.points[s->sid].y + 1) * PIXEL(16);
  puff = CreateSmoke(0, &c);
  if (puff != NULL) {
    SetSpriteAnimation(puff, MOTION(SM000_BATTLE_EFFECT, 19));
  }
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
    if (s->flag & AP_SPAWN_PUFF) {
      ApVolcairePuff(s);
    }
    if ((s->flag & (AP_SPAWN_PILLAR | AP_SPAWN_HAS_PILLAR)) == AP_SPAWN_PILLAR
        && ApCreatePillar(s)) {
      s->flag |= AP_SPAWN_HAS_PILLAR;
    }
    if (!gApSeedConfig.enemyDiskMarkers || (s->flag & AP_SPAWN_HAS_MARKER)) {
      continue;
    }
    mark = ApDropMarkOfSpawn(s);
    if (mark == AP_DROP_MARK_NONE || ApServerChecked(ApDropDisk(s->e, mark))) {
      continue;
    }
    if (ApCreateEnemyMarker(s->e, s->sid, ApDropDisk(s->e, mark))) {
      s->flag |= AP_SPAWN_HAS_MARKER;
    }
  }
  if (gApSeedConfig.enemyDiskMarkers) {
    ApMarkCountingEnemies();
  }
}

#endif /* AP */
