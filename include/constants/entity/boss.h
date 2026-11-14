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
#define BOSS_Z2_DESERT 27  // Zero 2 boss 0, the Desert's mechaniloid
#define BOSS_Z2_FEFNIR 28  // Zero 2 Fefnir, boss 15, and his tank. Boss of the Temple of Flame
#define BOSS_Z2_LEVIATHAN 29  // Zero 2 Leviathan, boss 17. Boss of the Temple of Ice
#define BOSS_Z2_BLOB 30  // Zero 2 boss 11. Boss of the Neo Arcadia Temple
#define BOSS_Z2_FLAME_GOLEM 31  // Zero 2 boss 22. Second fight of the Residential Area
#define BOSS_Z2_FROST_GOLEM 32  // Zero 2 boss 21. Last fight of the Residential Area
#define BOSS_Z2_WALL 33  // Zero 2 boss 18. The Jungle's mid-boss, a machine in the wall
#define BOSS_Z2_SNAKE 34  // Zero 2 boss 1. The Jungle's boss
#define BOSS_Z2_RAPTOR 35  // Zero 2 boss 10, Harpuia under the Dark Elf. Boss of the Temple of Wind
#define BOSS_Z2_BEAR 36  // Zero 2 boss 4, boss of the Computer Zone
#define BOSS_Z2_PANTER 37  // Zero 2 boss 3, Panter Flauclaws. Boss of the Train
#define BOSS_Z2_REACTOR 38  // Zero 2 boss 24, the Power Room's reactor cores
#define BOSS_Z2_FORTRESS 39  // Zero 2 boss 20, the Power Room's two mini-bosses
#define BOSS_Z2_MAGNION 40  // Zero 2 boss 13, Phoenix Magnion. Boss of the Power Room
#define BOSS_Z2_FEFNIR_FOOT 41  // Zero 2 boss 14, Fefnir on foot. Boss of the Shuttle Factory
#define BOSS_Z2_LEVIATHAN_FIRST 42  // Zero 2 boss 16, Leviathan's first fight. Boss of Computer Zone 2
#define BOSS_Z2_FROG 43  // Zero 2 boss 12, Burble Hekelot. Boss of the Forest of Notus
#define BOSS_ENTITY_COUNT (BOSS_Z2_FROG + 1)
#else
#define BOSS_ENTITY_COUNT 25
#endif

#endif  // GUARD_RMZ3_CONST_BOSS_H
