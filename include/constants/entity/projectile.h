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
#define PROJECTILE_Z2_SNAKE_SHOT 75  // Zero 2 projectile 19, the Jungle snake's bolts and sparks
#define PROJECTILE_Z2_TORNADO 76  // Zero 2 projectile 24, the raptor's
#define PROJECTILE_Z2_RAPTOR_CLAW 77  // Zero 2 projectile 25, claw and chain
#define PROJECTILE_Z2_FROST 78  // Zero 2 projectile 48, ice a vent freezes Zero in
#define PROJECTILE_Z2_ICE_BALL 79  // Zero 2 projectile 18 work0 0, the bear's ice ball
#define PROJECTILE_Z2_PANTER_CLAW 80  // Zero 2 projectile 16, Panter's thrown claws
#define PROJECTILE_Z2_PANTER_SLASH 81  // Zero 2 projectile 17, Panter's slashes
#define PROJECTILE_Z2_ENERGY_BALL 82  // Zero 2 projectile 63, the reactors' bouncing shots
#define PROJECTILE_Z2_FORTRESS_BALL 83  // Zero 2 projectile 47, the fortress's shots
#define PROJECTILE_Z2_MAGNION_SHOT 84  // Zero 2 projectile 28, Magnion's attacks
#define PROJECTILE_Z2_DRONE_SHOT 85  // Zero 2 projectile 50, the machine room's drones' shot
#define PROJECTILE_Z2_FEFNIR_SHOT 86  // Zero 2 projectile 34, Fefnir's shots in the Shuttle Factory
#define PROJECTILE_Z2_FEFNIR_WAVE 87  // Zero 2 projectile 35, his punch's flames along the floor
#define PROJECTILE_Z2_FEFNIR_JUMP_FIRE 88  // Zero 2 projectile 36, fire around him as he jumps
#define PROJECTILE_Z2_FEFNIR_PILLAR 89  // Zero 2 projectile 37, his EX's pillars
#define PROJECTILE_Z2_FLOOR_MINE 90  // Zero 2 projectile 54, Computer Zone 2's floor mines
#define PROJECTILE_Z2_LEVIATHAN_LANCE 91  // Zero 2 projectile 40, Leviathan's lance shots and ice lances
#define PROJECTILE_Z2_ICE_MINE 92  // Zero 2 projectile 41, her ice mines and whirl
#define PROJECTILE_Z2_FROG_SPIT 93  // Zero 2 projectile 31, the frog's globs, bubbles and swallowed tree frogs
#define PROJECTILE_Z2_FROG_LINK 94  // Zero 2 projectile 32, its arms' links and its touch
#define PROJECTILE_ENTITY_COUNT (PROJECTILE_Z2_FROG_LINK + 1)
#else
#define PROJECTILE_ENTITY_COUNT 48
#endif

#endif  // __INCLUDE_CONSTANTS_ENTITY_PROJECTILE_H__
