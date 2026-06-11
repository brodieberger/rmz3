#ifndef __INCLUDE_PLAYER_ZERO_H__
#define __INCLUDE_PLAYER_ZERO_H__

struct Zero;

enum ZeroGround {
  GROUND_IDLE,
  GROUND_WALK,
  GROUND_DASH,
};

enum WeaponCharge {
  NO_CHARGE,
  SEMI_CHARGE,
  FULL_CHARGE,
};

void zeroNeutral2(struct Zero* z);
void zeroAir2(struct Zero* z);
void zeroWall2(struct Zero* z);
void zeroLadder2(struct Zero* z);
void zeroDamaged(struct Zero* z);
void zeroKnockBack(struct Zero* z);
void FUN_0802c010(struct Zero* z);
void zeroDoor2D(struct Zero* z);
void zeroDoor3D(struct Zero* z);
void zeroMode7(struct Zero* z);
void zeroFloat(struct Zero* z);
void zeroTalk(struct Zero* z);
void zeroTeleport(struct Zero* z);
void zeroCyberDoor(struct Zero* z);

void zeroAttack(struct Zero* z);
void zeroAirAtk(struct Zero* z);
void zeroWallAtk(struct Zero* z);
void zeroLadderAtk(struct Zero* z);

void onSaber_GroundIdle(struct Zero* z);
void charge_saber_ground(struct Zero* z);
void recoilAttack(struct Zero* z);
void shieldAttack(struct Zero* z);
void shield_throw(struct Zero* z);
void shield_0802e1c8(struct Zero* z);
void zero_shield_0802e268(struct Zero* z);

bool8 Is1000Slash(struct Zero* z);

#endif  // __INCLUDE_PLAYER_ZERO_H__
