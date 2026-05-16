#include "collision.h"
#include "global.h"
#include "mission.h"
#include "sound.h"
#include "weapon.h"

static const u8 sElements[4];
static const motion_t sShieldFlyMotions[3][4];
static const WeaponFunc sShieldFlyUpdates[5];

bool32 shield_0803a5fc(struct WeaponCommon* w);
static void onHit(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void ShieldFly_Init(struct WeaponCommon* p);
static void ShieldFly_Update(struct WeaponCommon* p);
static void ShieldFly_Die(struct Entity* p);

// 0x080399fc
void DeleteFlyingShield(Object* p) {
  if ((p->s).id == WEAPON_MOVE_SHIELD_FLY) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

NAKED void MenuExit_ShieldFly(struct Weapon* w) { INCCODE("asm/todo/MenuExit_ShieldFly.inc"); }

struct Entity* CreateWeaponShieldFly(struct Zero* z, u8 r1) {
  struct WeaponCommon* p;

  KillAllWeapons(DeleteSaber);
  p = (struct WeaponCommon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (p != NULL) {
    u8 element;

    if ((z->unk_b4).mainCopy == WEAPON_SHIELD) {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_SHIELD_FLY);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[0], (p->s).palID = gWeaponPalIDs[0];
      element = sElements[((&z->unk_b4)->status).element];
      SetWeaponElement(0, element);

    } else {
      INIT_WEAPON_ROUTINE(p, WEAPON_MOVE_SHIELD_FLY);
      (p->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (p->s).taskCol = 16;
      (p->s).tileNum = gWeaponTileNum[1], (p->s).palID = gWeaponPalIDs[1];
      element = sElements[((&z->unk_b4)->status).element];
      SetWeaponElement(1, element);
    }

    (p->props).z = z;
    (p->s).work[0] = z->unk_127, (p->s).work[1] = r1;
    (&p->props)->props[1][1] = ((&z->unk_b4)->status).element;
  }
  return (void*)p;
}

static void ShieldFly_Init(struct WeaponCommon* p) {
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, sShieldFlyMotions[(p->s).work[1]][(p->s).work[0]]);
  PlaySound(SE_CHARGE_SHIELD_VOICE);
  (&p->props)->props[1][2] = 1;
  ShieldFly_Update(p);
}

static void ShieldFly_Update(struct WeaponCommon* p) {
  struct WeaponCommonProps* b4 = &p->props;
  struct Zero* z = (p->props).z;
  if (z->elfMotion != 0) {
    SET_WEAPON_ROUTINE(p, ENTITY_DIE);
    return;
  }
  if (((z->body).status & BODY_STATUS_DEAD) || ((z->body).hp == 0)) {
    SET_WEAPON_ROUTINE(p, ENTITY_DIE);
    return;
  }
  if ((b4->props[1][2] != 0) && ((p->body).status & BODY_STATUS_BLOCKED)) {
    PlaySound(SE_BLOCKED);
    b4->props[1][2] = 0;
  }

  {
    struct Zero_b4* b4 = &z->unk_b4;
    if ((b4->status).weapons[0] == WEAPON_SHIELD) {
      (z->restriction).mainCharge = TRUE;
    } else {
      (z->restriction).subCharge = TRUE;
    }
  }
  (sShieldFlyUpdates[(p->s).mode[1]])((void*)p);
  UpdateMotionGraphic(&p->s);

  if (((p->s).mode[1] == 2) && shield_0803a5fc(p)) {
    SET_WEAPON_ROUTINE(p, ENTITY_DIE);
  }
}

static void ShieldFly_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

static void onHit(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if ((body->hitboxFlags & BODY_STATUS_B2) && (gMission.weaponCount[WEAPON_SHIELD] < 0xFFFF)) {
    gMission.weaponCount[WEAPON_SHIELD]++;
  }
}

INCASM("asm/weapon/shield_fly.inc");

static const motion_t sShieldFlyMotions[3][4] = {
    {
        MOTION(0x6D, 0x00),
        MOTION(0x70, 0x00),
        MOTION(0x72, 0x00),
        MOTION(0x74, 0x00),
    },
    {
        MOTION(0x6D, 0x03),
        MOTION(0x70, 0x01),
        MOTION(0x72, 0x01),
        MOTION(0x74, 0x01),
    },
    {
        MOTION(0x6D, 0x03),
        MOTION(0x70, 0x01),
        MOTION(0x72, 0x01),
        MOTION(0x74, 0x01),
    },
};

static const u8 sElements[4] = {0, 1, 2, 3};
const u8 u8_ARRAY_08361288[4] = {5, 8, 11, 0};

const s16 s16_ARRAY_0836128c[8] = {
    0x1C00, -0x1300, 0x1A00, -0x1500, 0x1800, -0x1400, 0x1A00, -0x1000,
};

const s16 s16_ARRAY_0836129c[8] = {
    0x1C00, -0x1200, 0x1C00, -0x1500, 0x1600, -0x1400, 0x1B00, -0x0F00,
};

const struct Collision Collision_ARRAY_083612ac[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_UNK3,
      nature : (BODY_NATURE_CUT | ELEMENT_ENCHANTABLE),
      comboLv : 1,
      remaining : 1,
      layer : 0x00010000,
      range : {PIXEL(0), PIXEL(0), PIXEL(38), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(38), PIXEL(16)},
    },
};

const struct Collision Collision_ARRAY_083612dc[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_UNK3,
      nature : (BODY_NATURE_CUT | ELEMENT_ENCHANTABLE),
      comboLv : 1,
      remaining : 1,
      layer : 0x00010000,
      range : {PIXEL(0), PIXEL(0), PIXEL(34), PIXEL(34)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(34), PIXEL(34)},
    },
};

// --------------------------------------------

void shield_08039d3c(struct Weapon* w);
void shield_08039e28(struct Weapon* w);
void shield_08039ffc(struct Weapon* w);
void shield_0803a108(struct Weapon* w);
void shield_0803a3b4(struct Weapon* w);

// clang-format off
static const WeaponFunc sShieldFlyUpdates[5] = {
    shield_08039d3c,
    shield_08039e28,
    shield_08039ffc,
    shield_0803a108,
    shield_0803a3b4,
};
// clang-format on

// --------------------------------------------

// clang-format off
const WeaponRoutine gShieldFlyRoutine = {
    [ENTITY_INIT] =      (void*)ShieldFly_Init,
    [ENTITY_UPDATE] =    (void*)ShieldFly_Update,
    [ENTITY_DIE] =       (void*)ShieldFly_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWeapon,
    [ENTITY_EXIT] =      (void*)DeleteEntity,    
};
// clang-format on

const u8 u8_ARRAY_08361334[4] = {1, 3, 4, 0};
