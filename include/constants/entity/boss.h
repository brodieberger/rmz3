#ifndef GUARD_RMZ3_CONST_BOSS_H
#define GUARD_RMZ3_CONST_BOSS_H

// Boss.id
#define BOSS_MEGAMILPA 0
#define BOSS_OMEGA_WHITE 1
#define BOSS_BLAZIN 2
#define BOSS_CHILDRE 3
#define BOSS_WORMER 4
#define BOSS_VOLTEEL 5
#define BOSS_BABY_ELF 6
#define BOSS_DEATHTANZ 7
#define BOSS_HELLBAT 8
#define BOSS_BEE_SERVER 9
#define BOSS_TRETISTA 10
#define BOSS_ANUBIS 11
#define BOSS_PANTHEON_AQUA_MOD 12
#define BOSS_CUBIT 13
#define BOSS_LOCOMO_IF 14
#define BOSS_COPY_X 15
#define BOSS_GLACIERLE 16
#define BOSS_BLIZZACK 17
#define BOSS_OMEGA_GOLD 18
#define BOSS_HANUMACHINE 19
#define BOSS_OMEGA_ZERO 20
#define BOSS_PHANTOM 21
#define BOSS_OMEGA_ZX 22
#define BOSS_REACTOR_CORE 23  // エネルギー再生施設の炉心(スイッチ押し込み部屋)
#define BOSS_SPEAROOK 24

#if AP
#define BOSS_Z2_GOLEM 25  // Zero 2 Golem Type E. Hidden mid-boss in the crystal cave
#define BOSS_Z2_HARPUIA 26  // Zero 2 Harpuia. Boss of the crystal cave
#define BOSS_ENTITY_COUNT (BOSS_Z2_HARPUIA + 1)
#else
#define BOSS_ENTITY_COUNT 25
#endif

#endif  // GUARD_RMZ3_CONST_BOSS_H
