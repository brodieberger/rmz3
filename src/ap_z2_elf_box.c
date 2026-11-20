#include "ap.h"

#include "ap_marker.h"
#include "collision.h"
#include "definition.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "pickup.h"
#include "sound.h"
#include "vfx.h"

#include "constants/motion/ap_sheet.h"
#include "constants/song.h"

#if AP

/*
  Zero 2's elf capsule, item 3.
  work0: location, from AP_LOC_IMPORT_FIRST
  work1: its elf's type
*/

extern const ColorGraphic gApSheetGraphics[];

static const struct Collision sCollision;

static void Box_Init(Pickup* p);
static void Box_Update(Pickup* p);

// clang-format off
const PickupRoutine gApImportElfBoxRoutine = {
    [ENTITY_INIT] =      (PickupFunc)Box_Init,
    [ENTITY_UPDATE] =    (PickupFunc)Box_Update,
    [ENTITY_DIE] =       (PickupFunc)DeletePickup,
    [ENTITY_DISAPPEAR] = (PickupFunc)DeletePickup,
    [ENTITY_EXIT] =      (PickupFunc)DeleteEntity,
};
// clang-format on

// Zero 2's item colours on the pickup palette
static const u8 sColors[16] = {0, 7, 9, 10, 1, 4, 11, 5, 2, 12, 6, 8, 3, 13, 14, 15};

static void loadArt(void) {
  const ColorGraphic* g = &gApSheetGraphics[AP_SHEET_Z2_ELF_BOX];
  vu16* v = (vu16*)(VRAM + BG_VRAM_SIZE + AP_ELF_BOX_TILE * 32);
  s32 i;
  LoadGraphic(&g->g, (void*)((AP_ELF_BOX_TILE - (g->g).tileId) * 32 + 0x10000));
  for (i = 0; i < AP_SHEET_Z2_ELF_BOX_TILES * 16; i++) {
    u16 w = v[i];
    v[i] = sColors[w & 15] | (sColors[(w >> 4) & 15] << 4) | (sColors[(w >> 8) & 15] << 8) |
           (sColors[w >> 12] << 12);
  }
  gApSheetTilenums[AP_SHEET_Z2_ELF_BOX] = AP_ELF_BOX_TILE;
  gApSheetPalIDs[AP_SHEET_Z2_ELF_BOX] = AP_MARKER_PAL;
}

// 0x080d4f40
static void Box_Init(Pickup* p) {
  struct Entity* s = (struct Entity*)p;
  if (ApImportElfOut(s->work[0])) {
    s->flags &= ~(DISPLAY | FLIPABLE | COLLIDABLE);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  loadArt();
  InitNonAffineMotion(s);
  s->texture = TEXTURE_AP_SHEET;
  SetMotion(s, MOTION(AP_SHEET_Z2_ELF_BOX, 5));
  s->flags |= DISPLAY | FLIPABLE | COLLIDABLE;
  INIT_BODY(p, &sCollision, 1, NULL);
  s->d.y = 0;
  ApAttachElfMarker(s);
  SET_ITEM_ROUTINE(p, ENTITY_UPDATE);
  Box_Update(p);
}

// 0x080d5020: falls to the floor, any hit lets the elf out
static void Box_Update(Pickup* p) {
  struct Entity* s = (struct Entity*)p;
  Coords32 at;
  s32 floor;
  if ((p->body).status & BODY_STATUS_WHITE) {
    at.x = s->coord.x;
    at.y = s->coord.y - PIXEL(8);
    ApCreateImportElf(s->work[0], s->work[1], &at);
    CreateSmoke(2, &at);
    PlaySound(SE_ZAKO_EXPLODE);
    s->flags &= ~(DISPLAY | FLIPABLE | COLLIDABLE);
    EXIT_BODY(p);
    SET_ITEM_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  floor = FUN_08009f6c(s->coord.x, s->coord.y);
  if (s->coord.y >= floor) {
    s->coord.y = floor;
    s->d.y = 0;
  } else if (s->d.y <= 0x6FF) {
    s->d.y += 0x40;
  }
  s->coord.y += s->d.y;
  UpdateEntityAnim(s);
}

// 0x0834a118
static const struct Collision sCollision = {DRP, FACTION_ENEMY, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0, 0x00000000, {0, -0x600, 0x1000, 0x1000}};

#endif  // AP
