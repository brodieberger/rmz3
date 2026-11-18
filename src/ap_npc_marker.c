#include "ap.h"

#include "ap_marker.h"
#include "constants/entity/solid.h"
#include "constants/flag.h"
#include "constants/stage_id.h"
#include "definition.h"
#include "entity.h"
#include "game.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "spawn.h"
#include "stagerun.h"
#include "story.h"
#include "vfx.h"

#if AP

/*
  The Archipelago logo over a base NPC who has a location check.
  work1: bobbing up and down
  work2: px the NPC's sprite has reached above its origin
*/
#define AP_NPC_MARKER_SID unk_coord.x
#define AP_NPC_MARKER_PHASE work[1]
#define AP_NPC_MARKER_REACH work[2]
#define AP_NPC_MARKER_GAP 6

static bool32 checked(u16 loc) {
  return ApServerChecked(loc) || (gAp.checkedLocations[loc >> 3] & (1 << (loc & 7)));
}

/* The location the NPC still gives, 0 for none. */
static u16 heldLocation(const struct Entity* npc) {
  u16 loc;

  if (npc->id == SOLID_MAIN_NPC) {
    if (npc->work[0] != MAIN_NPC_CERVEAU || ApCerveauAway()) {
      return 0;
    }
    if (!checked(AP_LOC_ROD)) {
      return AP_LOC_ROD;
    }
    if (!checked(AP_LOC_SHIELD)) {
      return AP_LOC_SHIELD;
    }
    return checked(92) ? 0 : 92;  // disk 91
  }
  switch (npc->work[0]) {
    case MOB_ANDREW: loc = 107; break;
    case MOB_ALOUETTE: loc = 116; break;
    case MOB_HIBOU: loc = 169; break;
    case MOB_MENART: loc = 175; break;
    case MOB_ROCINOLLE: loc = checked(167) ? 44 : 167; break;
    case MOB_HIRONDELLE: loc = 173; break;
    case MOB_08: loc = 174; break;  // Doigt
    case MOB_11: loc = 58; break;   // soldier in right tower
    case MOB_24: loc = 23; break;   // soldier in room 02D
    default: return 0;
  }
  return checked(loc) ? 0 : loc;
}

static bool32 opened(u16 loc) {
  switch (loc) {
    case 175:
    case 167:
    case 58:
    case AP_LOC_ROD:
    case AP_LOC_SHIELD:
    case 92:
      return TRUE;
    case 44:
      return FLAG(gCurStory.s.gameflags, FLAG_AREAX2_DONE) || FLAG(gCurStory.s.gameflags, FLAG_LATER4_DONE);
  }
  return FLAG(gCurStory.s.gameflags, FLAG_FIRST4_DONE);
}

static void ApNpcMarkerUpdate(struct Entity* m) {
  const struct Entity* npc = m->unk_28;
  const struct SpawnedEntity* s = ApSpawnOf(npc);
  u16 loc, tile;
  u8 reach;

  if (s == NULL || s->sid != m->AP_NPC_MARKER_SID) {
    DeleteEntity(m);
    return;
  }
  loc = heldLocation(npc);
  if (loc == 0) {
    DeleteEntity(m);
    return;
  }
  tile = ApMarkerWindow();
  if (tile == 0 || !(npc->flags & DISPLAY)) {
    m->flags &= ~DISPLAY;
    return;
  }
  if (opened(loc)) {
    MemCopy32(gApMarkerTiles[0], (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)), 32);
  } else {
    tile++;
    MemCopy32(gApMarkerLockedTile, (void*)(VRAM + BG_VRAM_SIZE + (tile * 32)), 32);
  }
  (m->spr).oam.tileNum = tile;
  m->flags |= DISPLAY;

  reach = ApSpriteReach(npc);
  if (reach > m->AP_NPC_MARKER_REACH) {
    m->AP_NPC_MARKER_REACH = reach;
  }
  m->AP_NPC_MARKER_PHASE = (u8)((m->AP_NPC_MARKER_PHASE + 1) % AP_MARKER_BOB_PERIOD);
  m->coord = npc->coord;
  (m->coord).y -= PIXEL(m->AP_NPC_MARKER_REACH + AP_NPC_MARKER_GAP);
  (m->coord).y += PIXEL(gApMarkerBob[m->AP_NPC_MARKER_PHASE]);
}

static bool32 ApCreateNpcMarker(const struct SpawnedEntity* s) {
  struct Entity* m = (struct Entity*)AllocEntityLast(gVFXHeaderPtr);

  if (m == NULL) {
    return FALSE;
  }
  m->onUpdate = (void*)ApNpcMarkerUpdate;
  m->id = 0;
  m->renderPrio = 1;
  m->tileNum = 0;
  m->palID = 0;
  m->unk_28 = s->e;
  m->coord = (s->e)->coord;
  m->AP_NPC_MARKER_SID = s->sid;
  m->AP_NPC_MARKER_PHASE = 0;
  m->AP_NPC_MARKER_REACH = 0;

  InitNonAffineMotion(m);
  (m->spr).sprites = (struct MetaspriteHeader*)gApMarkerSprite.hdr;
  (m->spr).oam.paletteNum = AP_MARKER_PAL;
  (m->spr).spriteIdx = AP_MARKER_SMALL;
  return TRUE;
}

void ApUpdateNpcMarkers(void) {
  struct SpawnedEntity* s;

  if (gStageRun.id != STAGE_BASE || gGameState.mode[0] != MAINGAME || gGameState.mode[1] != OVERWORLD
      || ApInDemo()) {
    return;
  }
  for (s = gSpawnManager.list; s != NULL; s = s->next) {
    if (s->e == NULL || (s->flag & (SF_ZOMBIE | AP_SPAWN_HAS_MARKER))) {
      continue;
    }
    if ((s->e)->kind != ENTITY_SOLID || ((s->e)->id != SOLID_MOB_NPC && (s->e)->id != SOLID_MAIN_NPC)
        || heldLocation(s->e) == 0) {
      continue;
    }
    if (ApCreateNpcMarker(s)) {
      s->flag |= AP_SPAWN_HAS_MARKER;
    }
  }
}

#endif /* AP */
