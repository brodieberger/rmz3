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
#define PROJECTILE_Z2_SPIDER_WEB 64 
#define PROJECTILE_Z2_DESERT_LINK 65  // a link between the Desert boss's stretched tail segments
#define PROJECTILE_Z2_FEFNIR_FIRE 66  // Fefnir's tank's fire, Zero 2 projectile 38
#define PROJECTILE_Z2_PYLON_HAZARD 67  // Zero 2 projectile 10
#define PROJECTILE_Z2_LEVIATHAN_SHOT 68  // Zero 2 projectile 42
#define PROJECTILE_Z2_DRAGON_TAIL 69  // Zero 2 projectile 43
#define PROJECTILE_Z2_BLOB_DROP 70  // Zero 2 projectile 26
#define PROJECTILE_Z2_BLOB_SPLAT 71  // Zero 2 projectile 27
#define PROJECTILE_Z2_GOLEM_FIRE 72  // Zero 2 projectile 51
#define PROJECTILE_Z2_GOLEM_JET 73  // Zero 2 projectile 52
#define PROJECTILE_Z2_WALL_RING 74  // Zero 2 projectile 44
#define PROJECTILE_ENTITY_COUNT (PROJECTILE_Z2_WALL_RING + 1)
#else
#define PROJECTILE_ENTITY_COUNT 48
#endif

#endif  // __INCLUDE_CONSTANTS_ENTITY_PROJECTILE_H__
