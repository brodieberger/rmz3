#include "global.h"
#include "mission.h"
#include "weapon.h"

// ラクサイガ雷が地面につくる電撃

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

// 0x083616e0
static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      element : ELEMENT_THUNDER,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000004,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
};

void SmashElec_Init(struct Weapon* w);
void SmashElec_Update(struct Weapon* w);
void SmashElec_Die(struct Weapon* w);
void SmashElec_Disappear(struct Weapon* w);

// clang-format off
const WeaponRoutine gSmashElecRoutine = {
    [ENTITY_INIT] =      SmashElec_Init,
    [ENTITY_UPDATE] =    SmashElec_Update,
    [ENTITY_DIE] =       SmashElec_Die,
    [ENTITY_DISAPPEAR] = SmashElec_Disappear,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_SaberSmash(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_THUNDER || (z->unk_136 & (1 << 1))) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

INCASM("asm/weapon/saber_smash_elec.inc");

// 0x0803cb64
static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct Entity* self = (struct Entity*)body->parent;
    if (gMission.weaponCount[WEAPON_SABER] < 0xFFFF) {
      gMission.weaponCount[WEAPON_SABER]++;
    }
    self->work[1] = 1;
  }
}
