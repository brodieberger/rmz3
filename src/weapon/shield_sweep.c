#include "global.h"
#include "weapon.h"

void ShieldSweep_Init(struct Weapon* p);
void ShieldSweep_Update(struct Weapon* p);
void ShieldSweep_Die(struct Weapon* p);

// clang-format off
const WeaponRoutine gShieldSweepRoutine = {
    [ENTITY_INIT] =      (void*)ShieldSweep_Init,
    [ENTITY_UPDATE] =    (void*)ShieldSweep_Update,
    [ENTITY_DIE] =       (void*)ShieldSweep_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWeapon,
    [ENTITY_EXIT] =      (void*)DeleteEntity,    
};
// clang-format on

void MenuExit_ShieldSweep(struct WeaponCommon* p) {
  if ((p->props).z->unk_136 & (1 << 3)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

struct Entity* CreateShieldSweep(struct Zero* z, struct Entity* q, u8 n) {
  u8 element;
  struct WeaponCommon* p = (struct WeaponCommon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (p != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_SHIELD) {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_SHIELD_SWEEP);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[0], (p->s).palID = gWeaponPalIDs[0];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(0, element);
    } else {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_SHIELD_SWEEP);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[1], (p->s).palID = gWeaponPalIDs[1];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(1, element);
    }
    (p->props).z = z;
    (p->s).unk_28 = q;
    (p->s).work[0] = n, (p->s).work[1] = 0;
  }
  return (void*)p;
}

INCASM("asm/weapon/shield_sweep.inc");
