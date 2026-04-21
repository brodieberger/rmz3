#ifndef GUARD_RMZ3_VFX_H
#define GUARD_RMZ3_VFX_H

#include "constants/constants.h"
#include "entity.h"
#include "types.h"

// For VFX 16
// e.g. u8_ARRAY_08365c14
struct SlashedEnemy {
  motion_t m;
  u8 unk_02[2];
  struct Coord16 c;
  struct Coord16 d;
  struct Coord16 unk_coord_0c;
  struct Coord16 unk_10;
  u16 unk_14[2];
  u8 _[4];
};  // 28 bytes

typedef void (*VFXFunc)(struct VFX*);
typedef VFXFunc VFXRoutine[5];
extern const VFXRoutine* const gVFXFnTable[85];

#define INIT_VFX_ROUTINE(entity, entityID) INIT_ENTITY_ROUTINE(gVFXFnTable, entity, entityID)
#define SET_VFX_ROUTINE(entity, modeID) SET_ENTITY_ROUTINE(gVFXFnTable, entity, modeID)

void DeleteVFX(struct Entity* p);

struct Entity* CreateSmoke(u8 kind, struct Coord* c);
struct VFX* CreateChargeEffect(struct Zero* z, struct VFX* v, u8 r2);
void CreateParticle(struct Coord* c, u8 action, bool8 isRight);
void oz_080b3820(struct Coord* omegaCoord, bool8 isRight);
void CreateWallDust(struct Coord* c, bool8 isRight);
struct VFX* CreateRipple(struct Zero* z, bool8 outOfSea);
struct VFX* CreateEmotionBubble(u8 kind, struct Coord* target, struct Coord* c);
struct VFX* CreateCopyXIcon(struct Zero* z, struct Coord* c, u8 n);
struct VFX* CreateExlifeIndicator(u8 extraLife);
struct VFX* CreateMissionAlert(u8 kind);
struct VFX* CreateSlashedEnemy(struct Coord* c, const struct SlashedEnemy* data, u8 r2, u8 r3);
struct VFX* FUN_080bfce8(struct Coord* c, u8 r1);
struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);
void CreateVFX31_1(s32 x, s32 y);
void CreateVFX31_2(s32 x, s32 y);
void FUN_080b81a0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);

#endif  // GUARD_RMZ3_VFX_H
