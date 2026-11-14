#include "boss.h"

#include "collision.h"
#include "global.h"

extern const BossRoutine gMegamilpaRoutine;
extern const BossRoutine gOmegaWhiteRoutine;
extern const BossRoutine gBlazinRoutine;
extern const BossRoutine gChildreRoutine;
extern const BossRoutine gWormerRoutine;
extern const BossRoutine gVolteelRoutine;
extern const BossRoutine gBabyElfRoutine;
extern const BossRoutine gDeathtanzRoutine;
extern const BossRoutine gHellbatRoutine;
extern const BossRoutine gBeeServerRoutine;
extern const BossRoutine gTretistaRoutine;
extern const BossRoutine gAnubisRoutine;
extern const BossRoutine gPantheonAquaModRoutine;
extern const BossRoutine gCubitRoutine;
extern const BossRoutine gLocomoIFRoutine;
extern const BossRoutine gCopyXRoutine;
extern const BossRoutine gGlacierleRoutine;
extern const BossRoutine gBlizzackRoutine;
extern const BossRoutine gOmegaGoldRoutine;
extern const BossRoutine gHanumachineRoutine;
extern const BossRoutine gOmegaZeroRoutine;
extern const BossRoutine gPhantomBossRoutine;
extern const BossRoutine gOmegaZXRoutine;
extern const BossRoutine gReactorCoreRoutine;
extern const BossRoutine gSpearookRoutine;
#if AP
extern const BossRoutine gApZ2GolemRoutine;
extern const BossRoutine gApZ2HarpuiaRoutine;
extern const BossRoutine gApZ2DesertRoutine;
extern const BossRoutine gApZ2FefnirRoutine;
extern const BossRoutine gApZ2LeviathanRoutine;
extern const BossRoutine gApZ2BlobRoutine;
extern const BossRoutine gApZ2FlameGolemRoutine;
extern const BossRoutine gApZ2FrostGolemRoutine;
extern const BossRoutine gApZ2WallRoutine;
extern const BossRoutine gApZ2SnakeRoutine;
extern const BossRoutine gApZ2RaptorRoutine, gApZ2BearRoutine, gApZ2PanterRoutine, gApZ2ReactorRoutine;
extern const BossRoutine gApZ2FortressRoutine, gApZ2MagnionRoutine, gApZ2FefnirFootRoutine, gApZ2LeviathanFirstRoutine,
    gApZ2FrogRoutine;
#endif

// clang-format off
const BossRoutine* const gBossFnTable[BOSS_ENTITY_COUNT] = {
    [BOSS_MEGAMILPA] =          &gMegamilpaRoutine,
    [BOSS_OMEGA_WHITE] =        &gOmegaWhiteRoutine,
    [BOSS_BLAZIN] =             &gBlazinRoutine,
    [BOSS_CHILDRE] =            &gChildreRoutine,
    [BOSS_WORMER] =             &gWormerRoutine,
    [BOSS_VOLTEEL] =            &gVolteelRoutine,
    [BOSS_BABY_ELF] =           &gBabyElfRoutine,
    [BOSS_DEATHTANZ] =          &gDeathtanzRoutine,
    [BOSS_HELLBAT] =            &gHellbatRoutine,
    [BOSS_BEE_SERVER] =         &gBeeServerRoutine,
    [BOSS_TRETISTA] =           &gTretistaRoutine,
    [BOSS_ANUBIS] =             &gAnubisRoutine,
    [BOSS_PANTHEON_AQUA_MOD] =  &gPantheonAquaModRoutine,
    [BOSS_CUBIT] =              &gCubitRoutine,
    [BOSS_LOCOMO_IF] =          &gLocomoIFRoutine,
    [BOSS_COPY_X] =             &gCopyXRoutine,
    [BOSS_GLACIERLE] =          &gGlacierleRoutine,
    [BOSS_BLIZZACK] =           &gBlizzackRoutine,
    [BOSS_OMEGA_GOLD] =         &gOmegaGoldRoutine,
    [BOSS_HANUMACHINE] =        &gHanumachineRoutine,
    [BOSS_OMEGA_ZERO] =         &gOmegaZeroRoutine,
    [BOSS_PHANTOM] =            &gPhantomBossRoutine,
    [BOSS_OMEGA_ZX] =           &gOmegaZXRoutine,
    [BOSS_REACTOR_CORE] =       &gReactorCoreRoutine,
    [BOSS_SPEAROOK] =           &gSpearookRoutine,
#if AP
    [BOSS_Z2_GOLEM] =           &gApZ2GolemRoutine,
    [BOSS_Z2_HARPUIA] =         &gApZ2HarpuiaRoutine,
    [BOSS_Z2_DESERT] =          &gApZ2DesertRoutine,
    [BOSS_Z2_FEFNIR] =          &gApZ2FefnirRoutine,
    [BOSS_Z2_LEVIATHAN] =       &gApZ2LeviathanRoutine,
    [BOSS_Z2_BLOB] =            &gApZ2BlobRoutine,
    [BOSS_Z2_FLAME_GOLEM] =     &gApZ2FlameGolemRoutine,
    [BOSS_Z2_FROST_GOLEM] =     &gApZ2FrostGolemRoutine,
    [BOSS_Z2_WALL] =            &gApZ2WallRoutine,
    [BOSS_Z2_SNAKE] =           &gApZ2SnakeRoutine,
    [BOSS_Z2_RAPTOR] =          &gApZ2RaptorRoutine,
    [BOSS_Z2_BEAR] =            &gApZ2BearRoutine,
    [BOSS_Z2_PANTER] =          &gApZ2PanterRoutine,
    [BOSS_Z2_REACTOR] =         &gApZ2ReactorRoutine,
    [BOSS_Z2_FORTRESS] =        &gApZ2FortressRoutine,
    [BOSS_Z2_MAGNION] =         &gApZ2MagnionRoutine,
    [BOSS_Z2_FEFNIR_FOOT] =     &gApZ2FefnirFootRoutine,
    [BOSS_Z2_LEVIATHAN_FIRST] = &gApZ2LeviathanFirstRoutine,
    [BOSS_Z2_FROG] = &gApZ2FrogRoutine,
#endif
};
// clang-format on

void InitBossHeader(struct EntityHeader* h, struct Boss* p, s16 len) {
  s16 i;

  InitEntityHeader(h, ENTITY_BOSS, &p->s, sizeof(struct Boss), len);
  for (i = 0; i < len; i++) {
    p[i].s.uniqueID = gEntityIDGenerator + i;
  }
  gEntityIDGenerator += len;
  gBossHeaderPtr = h;
}

void DeleteBoss(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_BOSS_ROUTINE(p, ENTITY_EXIT);
}

static struct Entity* unused_0803d120(struct Entity* p) {
  struct Entity* w = GetNearestEntity(gWeaponHeaderPtr, &p->coord);
  if (w == NULL) return NULL;
  return w;
}

static Coords32* unused_0803d13c(struct Entity* p) {
  struct Entity* w = GetNearestEntity(gWeaponHeaderPtr, &p->coord);
  if (w != NULL) return &w->coord;
  return NULL;
}

void ResetBossBody(struct Boss* p, const struct Collision* collisions, s16 hp) { INIT_BODY(p, &collisions[0], hp, NULL); }
