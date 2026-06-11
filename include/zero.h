#ifndef GUARD_RMZ3_ZERO_H
#define GUARD_RMZ3_ZERO_H

#include "collision.h"
#include "common.h"
#include "entity.h"
#include "gba/gba.h"
#include "types.h"

// 後で player.h に名前変更予定

// Zero.mode[1]
enum {
  ZERO_GROUND = 0,     // 地上(棒立ち、歩き、ダッシュ、Zセイバー、etc...)
  ZERO_AIR = 1,        // 空中
  ZERO_WALL = 2,       // 壁ずり
  ZERO_LADDER = 3,     // はしご
  ZERO_DAMAGED = 4,    // 被ダメ
  ZERO_DOOR_2D = 5,    // ドア(2D, ボス部屋とか)
  ZERO_DOOR_3D = 6,    // ドア(3D, ベースのドアとか)
  ZERO_BINDED = 7,     // (レバガチャが必要な)拘束状態
  ZERO_FLOAT = 8,      // floated by Birleaf or Biraid
  ZERO_TALK = 9,       // 仁王立ち(会話時)
  ZERO_TELEPORT = 10,  // 転送
  ZERO_CYBER = 11,     // サイバー空間のドア
};

// Zero.posture (gZeroCollisions's idx)
enum ZeroPosture {
  POSTURE_IDLE = 0,
  POSTURE_DASH = 1,
  POSTURE_WALL = 2,
  POSTURE_SHADOW = 3,
  POSTURE_DOOR_2D = 4,
  POSTURE_DOOR_3D = 5,
  POSTURE_COUNT,
};

// ZeroStatus.menuZeroColor
enum MenuZeroColor {
  MZC_NORMAL,
  MZC_HARD,
  MZC_ULTIMATE,
};

typedef ZeroFunc ZeroRoutine[5];
extern const ZeroRoutine* const gPlayerFnTable[PLAYER_ENTITY_COUNT];

#define INIT_PLAYER_ROUTINE(entity, entityID) INIT_ENTITY_ROUTINE(gPlayerFnTable, entity, entityID)
#define SET_PLAYER_ROUTINE(entity, modeID) SET_ENTITY_ROUTINE(gPlayerFnTable, entity, modeID)

#define HEAD ((z->unk_b4).status.head)
#define BODY(z) (((&z->unk_b4)->status).body)
#define FOOT ((z->unk_b4).status.foot)
#define SATELITES (((&z->unk_b4)->status).satelites)
#define SATELITE_1 (((&z->unk_b4)->status).satelites[0])
#define SATELITE_2 (((&z->unk_b4)->status).satelites[1])

extern struct Entity* pZero;
extern struct Zero* pZero2;

extern const struct Collision gZeroCollisions[POSTURE_COUNT];
extern const struct Rect gZeroRanges[POSTURE_COUNT];

void ClearZeroStatus(struct ZeroStatus* p);
void ClearZeroStatusHard(struct ZeroStatus* p);
void ClearZeroStatusUltimate(struct ZeroStatus* p);
void FUN_080321d4(struct ZeroStatus* p);

void LoadZeroStatus(struct Zero* z, struct ZeroStatus* status);
void StoreZeroStatus(struct Zero* z, struct ZeroStatus* status);

u8 GetZeroColor(struct Zero* z);

u16 FUN_080101a8(void);
void InitPlayerHeader(struct EntityHeader* h, struct Zero* p, s16 len);
struct Entity* AllocPlayer(void);
struct Entity* AllocPlayer2(void);
void RemovePlayer(struct Entity* p);
void LoadZeroPalette(struct Entity* _, u32 color);
void LoadShadowDashPalette(struct Zero* _, u32 color);
bool8 UseSubtank(struct Zero* z);
bool8 IsDoubleHP(struct Zero* z);
u8 GetMaxHP(struct Zero* z);
u8 getMaxHP1x(struct Zero* z);
bool8 AddECrystal(struct Zero* z, u16 amount);
bool8 incrementSubtankHP(struct Zero* z);
u8 makeZeroFaster(struct Zero* z, u8 val);
u8 CountRodButton(struct Zero* z, bool8 isSubWeapon);
u8 CountButtonMashing(struct Zero* z);
void ResetZeroInput(struct Zero* z);
void resetSateliteElfPosition(struct Zero* z);
u16 GetDefaultMotion(struct Zero* z);
s16 CalcMaxWalkSpeed(struct Zero* z);
void FUN_080322c4(struct ZeroStatus* d);
bool8 IsButtonMashed(struct Zero* z);

// ------------------------------------------------------------------------------------------------------------------------------------

bool8 zero_08026f90(struct Zero* z, const struct Rect* p);
s16 CalcDx(struct Zero* z);
metatile_attr_t PushoutByFloor1(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t PushoutByCeiling(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t PushoutByCeilingOnLadder(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t GetWallMetatileAttr(struct Zero* z, const struct Rect* r1, bool8 _ UNUSED);
u8 ladder_08026bb0(struct Zero* z, const struct Rect* range, bool8 _);
u8 TryLadderDown(struct Zero* z, const struct Rect* p, bool8 _);
u8 TryLadderUp(struct Zero* z, const struct Rect* p, bool8 r2);
metatile_attr_t IsOnSoftPlatform(struct Zero* z, const struct Rect* p, bool8 r2);
s16 getFallAcceleration(struct Zero* z);
s16 calcMaxFallSpeed(struct Zero* z);
metatile_attr_t PushoutWallX(struct Zero* z, const struct Rect* p, bool8 r2);
u8 TryContinueLadderDown(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 PushoutByBorder(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 CanWallSlide(struct Zero* z, const struct Rect* p, bool8 _);
bool8 IsForwardPressed(struct Zero* z, const struct Rect* p, bool8 _);
bool8 IsZeroAgainstWall(struct Zero* z, const struct Rect* p, bool8 _);
u8 RecoilFromHazards(struct Zero* z, const struct Rect* range);
u8 RecoilFromFloor(struct Zero* z, const struct Rect* range);
metatile_attr_t PushoutByFloor2(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 IsElfUsed(struct Zero* z, cyberelf_t elfID);
bool8 isElfUsed_2(struct Zero* z, cyberelf_t elfID);
metatile_attr_t _pushoutHazardY(struct Zero* z, s32 x, s32 y, Coords32* c);
s16 GetDashSpeed(struct Zero* z);
bool8 IsAttackOK(struct Zero* z, weapon_t* w);
void KeepMotion(struct Zero* z, motion_t m);
void CopyPlayerMaxHPChargeOnSkipEventScene(Player* p, struct ZeroStatus* status);
void InstantlyKilling(struct Zero* z);
s16 getWallFallSpeed(struct Zero* z);
void CheckZeroHazard(struct Zero* z);
void setStageElfFlags(struct Zero* z);
void SetDisableArea(struct Zero* z, s32 left, s32 top, s32 right, s32 bottom);
void HandlePlayerInput(struct Zero* z);
u8 zero_08026970(struct Zero* z, const struct Rect* range, bool8 _);

#endif  // GUARD_RMZ3_ZERO_H
