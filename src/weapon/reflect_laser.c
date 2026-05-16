#include "collision.h"
#include "global.h"
#include "weapon.h"

struct ReflectLaser {
  OBJECT_HDR;
  // props (56bytes, offset: 0xB4..)
  struct ReflectLaserProps {
    struct Entity* q;   // 0xB4
    struct Coord c_b8;  // 0xB8
    u8 unk_c0;          // 0xC0
    u8 unk_c1[43];      // 0xC1
  } props;
};
static_assert(sizeof(struct ReflectLaser) == sizeof(struct Weapon));

static const struct Collision sCollisions[2];
static const motion_t sMotions[8];

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 10,
      atkType : 0x00,
      comboLv : 1,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
};

void ReflectLaser_Init(struct Weapon* p);
void ReflectLaser_Update(struct Weapon* p);
static void ReflectLaser_Die(Object* p);

// clang-format off
const WeaponRoutine gReflectLaserRoutine = {
    [ENTITY_INIT] =      (void*)ReflectLaser_Init,
    [ENTITY_UPDATE] =    (void*)ReflectLaser_Update,
    [ENTITY_DIE] =       (void*)ReflectLaser_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWeapon,
    [ENTITY_EXIT] =      (void*)DeleteEntity,    
};
// clang-format on

void MenuExit_ReflectLaser(struct Weapon* p) {
  struct Zero* z = (struct Zero*)(p->s).unk_28;
  if (P_ELEMENT(z) != 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (z->unk_136 & (1 << 0)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

struct Entity* CreateReflectLaser(struct Zero* z, struct Entity* q, u8 n) {
  struct ReflectLaser* p = (struct ReflectLaser*)AllocEntityFirst(gWeaponHeaderPtr);
  if (p != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_BUSTER) {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_REFLECT_LASER);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[0], (p->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_REFLECT_LASER);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[1], (p->s).palID = gWeaponPalIDs[1];
    }
    (p->s).unk_28 = (void*)z;
    (p->props).q = q;
    (p->s).work[0] = n, (p->s).work[1] = 0;
  }
  return (void*)p;
}

NAKED static struct Weapon* unused_CreateReflectLaser(struct Zero* z, struct Entity* p, void* r2, u8 r3, u8 r4) { INCCODE("asm/unused/unused_CreateReflectLaser.inc"); }

INCASM("asm/weapon/reflect_laser.inc");

static void ReflectLaser_Die(Object* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

// clang-format off
static const motion_t sMotions[8] = {
    MOTION(DM080_SEMI_BUSTER, 0),
    MOTION(DM080_SEMI_BUSTER, 0),
    MOTION(DM080_SEMI_BUSTER, 0),
    MOTION(DM080_SEMI_BUSTER, 1),
    MOTION(DM080_SEMI_BUSTER, 1),
    MOTION(DM080_SEMI_BUSTER, 2),
    MOTION(DM080_SEMI_BUSTER, 2),
    MOTION(DM080_SEMI_BUSTER, 2),
};
// clang-format on
