#ifndef __INCLUDE_CONSTANTS_ENTITY_PROJECTILE_H__
#define __INCLUDE_CONSTANTS_ENTITY_PROJECTILE_H__

// Projectile.id
#define PROJECTILE_LEMON 0
#define PROJECTILE_SHOTCOUNTER_BULLET 1
// ...
#define PROJECTILE_OMEGA_ZERO 38
// ...
#if AP
#define PROJECTILE_Z2_SIGNALOID_BOLT 48   // Zero 2 Signaloid's thunder
#define PROJECTILE_Z2_SIGNALOID_FLAKE 49  // Zero 2 Signaloid's snowflake
#define PROJECTILE_Z2_SIGNALOID_FIRE 50   // Zero 2 Signaloid's flamethrower and fireball
#define PROJECTILE_Z2_GOLEM_LASER 51      // Zero 2 Golem Type E's laser
#define PROJECTILE_Z2_HARPUIA_WAVE 52     // Zero 2 Harpuia's waves and slashes
#define PROJECTILE_Z2_HARPUIA_THUNDER 53  // Zero 2 Harpuia's thunder
#define PROJECTILE_Z2_COPTER_GUN 54       // Zero 2 propeller drone's gun
#define PROJECTILE_Z2_BARRIER_SHIP_SHOT 55  // Zero 2 barrier ship barrier and ring
#define PROJECTILE_Z2_RING_CANNON_SHOT 56  // Zero 2 ring cannon ring
#define PROJECTILE_Z2_SHIELD_GUARD_MACE 57  // Zero 2 shield guard mace and chain
#define PROJECTILE_Z2_BEE_BOMB 58
#define PROJECTILE_Z2_BEE_BLAST 59
#define PROJECTILE_Z2_MOLE_DRILL 60
#define PROJECTILE_Z2_TOWER_ARM 61
#define PROJECTILE_Z2_TOWER_SPIKE 62
#define PROJECTILE_Z2_SPIKEBALL_ROCK 63
#define PROJECTILE_Z2_SPIDER_WEB 64  // its web
#define PROJECTILE_ENTITY_COUNT (PROJECTILE_Z2_SPIDER_WEB + 1)
#else
#define PROJECTILE_ENTITY_COUNT 48
#endif

#endif  // __INCLUDE_CONSTANTS_ENTITY_PROJECTILE_H__
