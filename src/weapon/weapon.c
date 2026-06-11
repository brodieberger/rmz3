#include "weapon.h"

#include "collision.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "renderer.h"
#include "zero.h"

#define SLOT_4BPP 16

static const struct PlttData gWeaponPalettes[5][SLOT_4BPP];

void InitWeaponHeader(struct EntityHeader* h, struct Weapon* w, s16 len) {
  s16 i;
  u16 j;

  InitEntityHeader(h, ENTITY_WEAPON, &w->s, sizeof(struct Weapon), len);
  for (i = 0; i < len; i++) {
    w[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gWeaponHeaderPtr = h;
  for (j = 0; j < 4; j++) {
    gLastWeaponElements[j] = gWeaponElements[j] = 0xFFFF;
  }
}

void DrawWeapon(Renderer* r) {
  u16 i;
  for (i = 0; i < 4; i++) {
    if (gLastWeaponElements[i] != gWeaponElements[i]) {
      gLastWeaponElements[i] = gWeaponElements[i];
      CpuFastCopy(gWeaponPalettes[gLastWeaponElements[i]], &gPaletteManager.buf[gWeaponPalIDs[i] * SLOT_4BPP + 256], 32);
    }
  }
  DrawEntity(gWeaponHeaderPtr, r);
}

void DeleteWeapon(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

/*
  Buster(0): Element effected
  Saber(1):  Element effected
  Rod(2):    No effected
  Shield(3): No effected
*/
void SetWeaponElement(u16 weaponKind, u16 element) {
  gWeaponElements[weaponKind & 0xFFFE] = element;
  return;
}

// run kill(p) for all weapon entities (mainly clean up all weapons)
void KillAllWeapons(WeaponFunc kill) {
  struct EntityHeader* h = gWeaponHeaderPtr;
  struct Entity* p = GetEntityList(h);
  while (p != (struct Entity*)&h->tail) {
    kill((struct Weapon*)p);
    p = GetNextEntity(h);
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

const u16 gWeaponTileNum[4] = {
    0,
    48,
    512 + 48,
    512 + 96,
};

const u8 gWeaponPalIDs[4] = {1, 1, 5, 5};

// clang-format off
static const ALIGNED(4) struct PlttData gWeaponPalettes[5][SLOT_4BPP] = {
  [WEAPON_COLOR_NORMAL]  = { PLTTDATA(0x0000), PLTTDATA(0xB4A0), PLTTDATA(0xC588), PLTTDATA(0x6AD2), PLTTDATA(0xFBDE), PLTTDATA(0x82DC), PLTTDATA(0x939F), PLTTDATA(0xD3FF), PLTTDATA(0x8388), PLTTDATA(0xBFF2), PLTTDATA(0xFBF5), PLTTDATA(0x8388), PLTTDATA(0x43F2), PLTTDATA(0xFBF5), PLTTDATA(0xFFBF), PLTTDATA(0xFFFF) },
  [WEAPON_COLOR_THUNDER] = { PLTTDATA(0x0000), PLTTDATA(0xB4A0), PLTTDATA(0xC588), PLTTDATA(0x6AD2), PLTTDATA(0xFBDE), PLTTDATA(0x82DC), PLTTDATA(0x939F), PLTTDATA(0xD3FF), PLTTDATA(0x8388), PLTTDATA(0xBFF2), PLTTDATA(0xFBF5), PLTTDATA(0xDBF2), PLTTDATA(0xD3FF), PLTTDATA(0xEFFF), PLTTDATA(0xDBFF), PLTTDATA(0xFFFF) },
  [WEAPON_COLOR_FLAME]   = { PLTTDATA(0x0000), PLTTDATA(0xB4A0), PLTTDATA(0xC588), PLTTDATA(0x6AD2), PLTTDATA(0xFBDE), PLTTDATA(0x82DC), PLTTDATA(0x939F), PLTTDATA(0xD3FF), PLTTDATA(0x8388), PLTTDATA(0xBFF2), PLTTDATA(0xFBF5), PLTTDATA(0x825F), PLTTDATA(0x031F), PLTTDATA(0xAFFF), PLTTDATA(0xFF9F), PLTTDATA(0xFFFF) },
  [WEAPON_COLOR_ICE]     = { PLTTDATA(0x0000), PLTTDATA(0xB4A0), PLTTDATA(0xC588), PLTTDATA(0x6AD2), PLTTDATA(0xFBDE), PLTTDATA(0x82DC), PLTTDATA(0x939F), PLTTDATA(0xD3FF), PLTTDATA(0x8388), PLTTDATA(0xBFF2), PLTTDATA(0xFBF5), PLTTDATA(0x7F07), PLTTDATA(0xFF90), PLTTDATA(0x7FD5), PLTTDATA(0xFFFC), PLTTDATA(0xFFFF) },
  [WEAPON_COLOR_OMEGA]   = { PLTTDATA(0x0000), PLTTDATA(0xB4A0), PLTTDATA(0xC588), PLTTDATA(0x6AD2), PLTTDATA(0xFBDE), PLTTDATA(0x82DC), PLTTDATA(0x939F), PLTTDATA(0xD3FF), PLTTDATA(0xE8BF), PLTTDATA(0x7DFF), PLTTDATA(0x7EDF), PLTTDATA(0x441F), PLTTDATA(0xE8BF), PLTTDATA(0x7DFF), PLTTDATA(0x7EDF), PLTTDATA(0xFFBF) },
};

extern const WeaponRoutine gBusterRoutine;
extern const WeaponRoutine gSaberRoutine;
extern const WeaponRoutine gShieldGuardRoutine;
extern const WeaponRoutine gRodRoutine;
extern const WeaponRoutine gShieldFlyRoutine;
extern const WeaponRoutine gSaberWaveRoutine;
extern const WeaponRoutine gWeapon6Routine;
extern const WeaponRoutine gReflectLaserRoutine;
extern const WeaponRoutine gSoulLauncherRoutine;
extern const WeaponRoutine gBurstShotRoutine;
extern const WeaponRoutine gBlizzardArrowRoutine;
extern const WeaponRoutine gThrowBladeRoutine;
extern const WeaponRoutine gShieldSweepRoutine;
extern const WeaponRoutine gWeapon13Routine;
extern const WeaponRoutine gSmashElecRoutine;
extern const WeaponRoutine gElecShieldSweepRoutine;
extern const WeaponRoutine gMinigameRodRoutine;

const WeaponRoutine* const gWeaponFnTable[WEAPON_MOVE_COUNT] = {
    [WEAPON_MOVE_Z_BUSTER] =          &gBusterRoutine,
    [WEAPON_MOVE_Z_SABER] =           &gSaberRoutine,
    [WEAPON_MOVE_SHIELD_GUARD] =      &gShieldGuardRoutine,
    [WEAPON_MOVE_RECOIL_ROD] =        &gRodRoutine,
    [WEAPON_MOVE_SHIELD_FLY] =        &gShieldFlyRoutine,
    [WEAPON_MOVE_SABER_WAVE] =        &gSaberWaveRoutine,
    [WEAPON_MOVE_06] =                &gWeapon6Routine,
    [WEAPON_MOVE_REFLECT_LASER] =     &gReflectLaserRoutine,
    [WEAPON_MOVE_SOUL_LANCHER] =      &gSoulLauncherRoutine,
    [WEAPON_MOVE_BURST_SHOT] =        &gBurstShotRoutine,
    [WEAPON_MOVE_BLIZZARD_ARROW] =    &gBlizzardArrowRoutine,
    [WEAPON_MOVE_ZANEIDAN] =          &gThrowBladeRoutine,
    [WEAPON_MOVE_SHIELD_SWEEP] =      &gShieldSweepRoutine,
    [WEAPON_MOVE_13] =                &gWeapon13Routine,
    [WEAPON_MOVE_RAKUSAIGA] =         &gSmashElecRoutine,
    [WEAPON_MOVE_SHIELD_SWEEP_ELEC] = &gElecShieldSweepRoutine,
    [WEAPON_MOVE_MINIGAME_ROD] =      &gMinigameRodRoutine,
};
// clang-format on
