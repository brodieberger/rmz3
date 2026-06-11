#ifndef GUARD_RMZ3_SOLID_H
#define GUARD_RMZ3_SOLID_H

#include "collision.h"
#include "constants/constants.h"
#include "entity.h"
#include "types.h"

typedef void (*SolidFunc)(struct Solid*);
typedef SolidFunc SolidRoutine[5];
extern const SolidRoutine* const gSolidFnTable[SOLID_ENTITY_COUNT];

#define INIT_SOLID_ROUTINE(entity, entityID) INIT_OBJECT_ENTITY(30, gSolidFnTable, entity, entityID)
#define SET_SOLID_ROUTINE(entity, modeID) SET_ENTITY_ROUTINE(gSolidFnTable, entity, modeID)

void DeleteSolid(Object* p);
u16 FUN_080d0934(struct Entity* p, motion_t m, u8 r2);
struct Solid* CreateLeafBurn(u8 id);
struct Solid* CreateResistanceBaseElevator(u8 floor);

#endif  // GUARD_RMZ3_SOLID_H
