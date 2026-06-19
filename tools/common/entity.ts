export type EntityID = {
  id: string[];
  work0?: Record<string, Record<number, string>>;
  work1?: Record<string, Record<number, string>>;
};

const EnemyID: EntityID = {
  id: [
    'ENEMY_P_GUARDIAN',
    'ENEMY_P_HUNTER',
    'ENEMY_MEGAMILPA_NODE',
    'ENEMY_SHOTCOUNTER',
    'ENEMY_BATRING',
    'ENEMY_PILLER_CANNON',
    'ENEMY_GRAND_CANNON',
    'ENEMY_SHRIMPORIN',
    'ENEMY_OMEGA1W_HAND',
    'ENEMY_FLOPPER',
    'ENEMY_LAMPLORT',
    'ENEMY_GYRO_CANNON',
    'ENEMY_LEMMINGLES_NEST',
    'ENEMY_LEMMINGLES',
    'ENEMY_TOP_GABYOALL',
    'ENEMY_SHARKSEAL_X',
    'ENEMY_VOLCANO_BOMB',
    'ENEMY_CARRY_ARM',
    'ENEMY_P_AQUA',
    'ENEMY_CHILDRE_OBJ',
    'ENEMY_SNAKECORD',
    'ENEMY_HAMMER',
    'ENEMY_PURPLE_NERPLE',
    'ENEMY_WORMER_ROCK_DRONE',
    'ENEMY_VOLCAIRE',
    'ENEMY_TILE_CANNON',
    'ENEMY_SHELLUNO',
    'ENEMY_DEATHTANZ_ROCK',
    'ENEMY_HEAVY_CANNON_BALL',
    'ENEMY_WORMER_SNOW_BALL',
    'ENEMY_BEETANK',
    'ENEMY_SWORDY',
    'ENEMY_PUFFY',
    'ENEMY_CROSSBYNE',
    'ENEMY_BURNABLE_WOOD',
    'ENEMY_MELLNET',
    'ENEMY_HELL_BOUNCER',
    'ENEMY_P_ZOMBIE',
    'ENEMY_P_AQUA_MOD_OBJ',
    'ENEMY_GLACIERLE_ARM',
    'ENEMY_OMEGA1G_HAND',
    'ENEMY_EYE_CANNON',
    'ENEMY_42',
    'ENEMY_CAPSULE_CANNON',
    'ENEMY_P_BOMBER',
    'ENEMY_HANUMACHINE_OBJ',
    'ENEMY_GALLISNI',
    'ENEMY_MOTHJIRO',
    'ENEMY_METTAUR',
    'ENEMY_P_BASE',
    'ENEMY_HANUMACHINE_NECRO',
    'ENEMY_CARRYBEE_G',
    'ENEMY_OZ_ROCK',
    'ENEMY_OMEGA1G_SWORD',
    'ENEMY_GENERATOR_CANNON',
    'ENEMY_DEATHLOCK',
    'ENEMY_CLAVEKER',
    'ENEMY_SEIMERAN',
    'ENEMY_PETATRIA',
    'ENEMY_59',
    'ENEMY_OMEGA_ZX_X',
    'ENEMY_61',
    'ENEMY_SHOTLOID',
    'ENEMY_63',
    'ENEMY_P_FIST',
    'ENEMY_SHELLCRAWLER',
    'ENEMY_CANNON_HOPPER',
    'ENEMY_CATTATANK',
    'ENEMY_LEVIATHAN_MG',
    'ENEMY_HARPUIA_MG',
    'ENEMY_CIEL_MG_1',
    'ENEMY_CIEL_MG_2',
    'ENEMY_72',
  ],
  work0: {
    'ENEMY_GRAND_CANNON': {
      0: 'GRAND_CANNON_TURRET',
      1: 'GRAND_CANNON_BATTERY',
    },
  },
};

const SolidID: EntityID = {
  id: [
    'SOLID_ICEBON',
    'SOLID_ICEBON_ICE',
    'SOLID_DOOR_2D_BLUE',
    'SOLID_BURNING_FLAME',
    'SOLID_UNK_004',
    'SOLID_HEAVY_CANNON',
    'SOLID_LAVA_GEYSER_PLATFORM',
    'SOLID_LAVA_GEYSER',
    'SOLID_LAVA_RIVER_PLATFORM',
    'SOLID_DOOR_3D',
    'SOLID_UNK_010',
    'SOLID_UNK_011',
    'SOLID_ANUBIS_COFFIN',
    'SOLID_UNK_013',
    'SOLID_LOCOMOIF_PLATFORM',
    'SOLID_GLACIERLE_ARM',
    'SOLID_UNK_016',
    'SOLID_PLATFORM_SUBARCADIA',
    'SOLID_SNOWBOARD',
    'SOLID_BASE_ELEVATOR',
    'SOLID_DOOR_2D_GRAY_V',
    'SOLID_SCRIPT_ACTOR',
    'SOLID_DOOR_2D_GRAY_H',
    'SOLID_TURTLOID_S',
    'SOLID_PHANTOM_TELEPORTER',
    'SOLID_PLATFORM_AREAX2_WEILLABO',
    'SOLID_ICE_BLOCK',
    'SOLID_UNK_027',
    'SOLID_MG_NINJASTAR',
    'SOLID_MOB_NPC',
    'SOLID_MAIN_NPC',
    'SOLID_CYBERSPACE_DOOR',
    'SOLID_LIGHT_SWITCH',
    'SOLID_PLATFORM_33',
    'SOLID_TOGGLE_SWITCH_RED',
    'SOLID_CONTAINER',
    'SOLID_PLATFORM_MISSILE',
    'SOLID_FLYING_FISH',
    'SOLID_SEAGULLS',
    'SOLID_CAT',
    'SOLID_MOD_PLANT',
    'SOLID_VOLCANO_COFFIN',
    'SOLID_UNK_042',
    'SOLID_UNK_043',
    'SOLID_UNK_044',
    'SOLID_GE_PIER',
    'SOLID_GE_PLATFORM',
    'SOLID_ANATRE_CUBE',
    'SOLID_CIEL_COMPUTER',
    'SOLID_GRAFFITI',
    'SOLID_STRUCTURAL_STEEL',
    'SOLID_MOD_ELF',
    'SOLID_TOGGLE_SWITCH_YELLOW',
    'SOLID_OCEAN_ROD_WALL',
    'SOLID_SEA_LV_BTN',
    'SOLID_CHILDRE_SHIP',
  ],
};

const PickupID: EntityID = {
  id: ['ITEM_GENERAL', 'ITEM_DISK'],
  work0: {
    'ITEM_GENERAL': {
      0: 'ITEM_LIFE_S',
      1: 'ITEM_LIFE_M',
      2: 'ITEM_LIFE_L',
      3: 'ITEM_EC_S',
      4: 'ITEM_EC_L',
      5: 'ITEM_EXLIFE',
      6: 'ITEM_SD',
      7: 'ITEM_SUBTANK1',
      8: 'ITEM_SUBTANK2',
    },
    'ITEM_DISK': [],
  },
};

export const Entity = {
  kind: ['ENTITY_PLAYER', 'ENTITY_WEAPON', 'ENTITY_BOSS', 'ENTITY_ENEMY', 'ENTITY_PROJECTILE', 'ENTITY_VFX', 'ENTITY_SOLID', 'ENTITY_ITEM', 'ENTITY_ELF', 'ENTITY_WIDGET'],
  id: {
    'ENTITY_ENEMY': EnemyID,
    'ENTITY_SOLID': SolidID,
    'ENTITY_ITEM': PickupID,
  } as Record<string, EntityID>,
};

export const getEntityKind = (kind: number, id: number, work0: number, work1: number): string[] => {
  const kindName = Entity.kind[kind];
  if (!kindName) {
    return [`${kind}`, `${id}`, `${work0}`, `${work1}`];
  }

  const table = Entity.id[kindName];
  if (!table) {
    return [kindName, `${id}`, `${work0}`, `${work1}`];
  }

  const idName = table.id[id];
  if (!idName) {
    return [kindName, `${id}`, `${work0}`, `${work1}`];
  }
  const work0Name = table.work0?.[idName]?.[work0];
  if (work0Name === undefined) {
    return [kindName, idName, `${work0}`, `${work1}`];
  }
  const work1Name = table.work1?.[idName]?.[work1];
  if (work1Name === undefined) {
    return [kindName, idName, work0Name, `${work1}`];
  }
  return [kindName, idName, work0Name, work1Name];
};
