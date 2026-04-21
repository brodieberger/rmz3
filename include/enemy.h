#ifndef GUARD_RMZ3_ENEMY_H
#define GUARD_RMZ3_ENEMY_H

#include "constants/constants.h"
#include "entity.h"
#include "types.h"

typedef EnemyFunc EnemyRoutine[5];
extern const EnemyRoutine* const gEnemyFnTable[ENEMY_COUNT];

#define INIT_ENEMY_ROUTINE(entity, entityID) INIT_ENTITY_ROUTINE(gEnemyFnTable, entity, entityID)
#define SET_ENEMY_ROUTINE(entity, modeID) SET_ENTITY_ROUTINE(gEnemyFnTable, entity, modeID)

// --------------------------------------------

void DeleteEnemy(struct Entity* p);
bool32 IsFrozen(struct Entity* p);

#endif  // GUARD_RMZ3_ENEMY_H
