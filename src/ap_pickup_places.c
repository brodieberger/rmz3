#include "ap.h"
#include "constants/stage_id.h"

#if AP

const struct ApPickupPlace gApPickupPlaces[AP_PICKUP_PLACE_COUNT] = {
    {STAGE_OCEAN, 30, 272, 231},  /* Oceanic Highway Ruins: 1-UP */
    {STAGE_OLD_RESIDENTIAL, 27, 141, 232},  /* Old Residential: 1-UP */
    {STAGE_OLD_RESIDENTIAL, 58, 183, 233},  /* Old Residential: 1-UP */
    {STAGE_MISSILE_FACTORY, 104, 379, 234},  /* Missile Factory: 1-UP */
    {STAGE_ANATRE_FOREST, 24, 35, 235},  /* Forest of Anatre: 1-UP */
    {STAGE_E_FACILITY, 14, 625, 236},  /* Energy Facility: 1-UP */
    {STAGE_SNOWY_PLAINS, 107, 573, 237},  /* Snowy Plains: 1-UP */
    {STAGE_GIANT_ELEVATOR, 25, 72, 238},  /* Giant Elevator: 1-UP */
    {STAGE_SUB_ARCADIA, 98, 67, 239},  /* Sub Arcadia: 1-UP */
    {STAGE_BASE, 48, 26, 240},  /* Resistance Base: 1-UP */
    {STAGE_SPACE_CRAFT, 63, 215, 301},  /* Derelict Spacecraft: E-Crystal (large) */
    {STAGE_SPACE_CRAFT, 73, 251, 302},  /* Derelict Spacecraft: Life Capsule (large) */
    {STAGE_VOLCANO, 25, 319, 303},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_VOLCANO, 27, 372, 304},  /* Aegis Volcano Base: Life Capsule (large) */
    {STAGE_VOLCANO, 37, 504, 305},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_VOLCANO, 37, 505, 306},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_VOLCANO, 53, 578, 307},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_VOLCANO, 33, 583, 308},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_VOLCANO, 26, 684, 309},  /* Aegis Volcano Base: E-Crystal (large) */
    {STAGE_OCEAN, 38, 26, 310},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 38, 27, 311},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 57, 144, 312},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 57, 145, 313},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 30, 164, 314},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 30, 171, 315},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_OCEAN, 30, 245, 316},  /* Oceanic Highway Ruins: Life Capsule (large) */
    {STAGE_OCEAN, 41, 287, 317},  /* Oceanic Highway Ruins: Life Capsule (large) */
    {STAGE_OCEAN, 30, 345, 318},  /* Oceanic Highway Ruins: Life Capsule (medium) */
    {STAGE_OCEAN, 37, 511, 319},  /* Oceanic Highway Ruins: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 53, 63, 320},  /* Weapons Repair Factory: Life Capsule (medium) */
    {STAGE_REPAIR_FACTORY, 43, 117, 321},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 43, 118, 322},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 46, 176, 323},  /* Weapons Repair Factory: Life Capsule (medium) */
    {STAGE_REPAIR_FACTORY, 55, 214, 324},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 55, 215, 325},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 53, 279, 326},  /* Weapons Repair Factory: Life Capsule (medium) */
    {STAGE_REPAIR_FACTORY, 13, 357, 327},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 13, 358, 328},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_REPAIR_FACTORY, 70, 396, 329},  /* Weapons Repair Factory: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 78, 67, 330},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 73, 74, 331},  /* Old Residential: Life Capsule (medium) */
    {STAGE_OLD_RESIDENTIAL, 33, 80, 332},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 38, 80, 333},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 73, 146, 334},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 73, 147, 335},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 73, 148, 336},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 73, 216, 337},  /* Old Residential: Life Capsule (large) */
    {STAGE_OLD_RESIDENTIAL, 79, 222, 338},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 79, 223, 339},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 38, 242, 340},  /* Old Residential: Life Capsule (medium) */
    {STAGE_OLD_RESIDENTIAL, 31, 248, 341},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 21, 251, 342},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 54, 252, 343},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 54, 253, 344},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 24, 305, 345},  /* Old Residential: E-Crystal (large) */
    {STAGE_OLD_RESIDENTIAL, 43, 327, 346},  /* Old Residential: Life Capsule (medium) */
    {STAGE_OLD_RESIDENTIAL, 23, 358, 347},  /* Old Residential: Life Capsule (medium) */
    {STAGE_OLD_RESIDENTIAL, 32, 372, 348},  /* Old Residential: Life Capsule (large) */
    {STAGE_MISSILE_FACTORY, 57, 80, 349},  /* Missile Factory: E-Crystal (large) */
    {STAGE_MISSILE_FACTORY, 57, 81, 350},  /* Missile Factory: E-Crystal (large) */
    {STAGE_MISSILE_FACTORY, 103, 364, 351},  /* Missile Factory: E-Crystal (large) */
    {STAGE_MISSILE_FACTORY, 112, 364, 352},  /* Missile Factory: Life Capsule (medium) */
    {STAGE_MISSILE_FACTORY, 102, 393, 353},  /* Missile Factory: Life Capsule (large) */
    {STAGE_TWILIGHT_DESERT, 28, 340, 354},  /* Twilight Desert: Life Capsule (large) */
    {STAGE_ANATRE_FOREST, 22, 78, 355},  /* Forest of Anatre: Life Capsule (medium) */
    {STAGE_ANATRE_FOREST, 23, 328, 356},  /* Forest of Anatre: Life Capsule (medium) */
    {STAGE_ANATRE_FOREST, 27, 443, 357},  /* Forest of Anatre: Life Capsule (medium) */
    {STAGE_ICE_BASE, 38, 161, 358},  /* Frontline Ice Base: Life Capsule (medium) */
    {STAGE_ICE_BASE, 59, 186, 359},  /* Frontline Ice Base: E-Crystal (large) */
    {STAGE_ICE_BASE, 59, 187, 360},  /* Frontline Ice Base: E-Crystal (large) */
    {STAGE_ICE_BASE, 34, 392, 361},  /* Frontline Ice Base: E-Crystal (large) */
    {STAGE_AREA_X2, 153, 97, 362},  /* Area X-2: Life Capsule (medium) */
    {STAGE_AREA_X2, 159, 211, 363},  /* Area X-2: Life Capsule (large) */
    {STAGE_AREA_X2, 98, 241, 364},  /* Area X-2: Life Capsule (medium) */
    {STAGE_AREA_X2, 78, 243, 365},  /* Area X-2: Life Capsule (large) */
    {STAGE_E_FACILITY, 25, 99, 366},  /* Energy Facility: Life Capsule (medium) */
    {STAGE_E_FACILITY, 36, 193, 367},  /* Energy Facility: Life Capsule (medium) */
    {STAGE_E_FACILITY, 32, 301, 368},  /* Energy Facility: Life Capsule (medium) */
    {STAGE_E_FACILITY, 48, 312, 369},  /* Energy Facility: E-Crystal (large) */
    {STAGE_E_FACILITY, 48, 313, 370},  /* Energy Facility: E-Crystal (large) */
    {STAGE_E_FACILITY, 38, 499, 371},  /* Energy Facility: Life Capsule (medium) */
    {STAGE_SUNKEN_LIBRARY, 25, 91, 372},  /* Sunken Library: Life Capsule (medium) */
    {STAGE_SUNKEN_LIBRARY, 38, 102, 373},  /* Sunken Library: Life Capsule (medium) */
    {STAGE_SUNKEN_LIBRARY, 72, 223, 374},  /* Sunken Library: E-Crystal (large) */
    {STAGE_SUNKEN_LIBRARY, 70, 268, 375},  /* Sunken Library: Life Capsule (medium) */
    {STAGE_SUNKEN_LIBRARY, 75, 309, 376},  /* Sunken Library: E-Crystal (large) */
    {STAGE_SUNKEN_LIBRARY, 69, 311, 377},  /* Sunken Library: E-Crystal (large) */
    {STAGE_GIANT_ELEVATOR, 23, 190, 378},  /* Giant Elevator: E-Crystal (large) */
    {STAGE_GIANT_ELEVATOR, 93, 192, 379},  /* Giant Elevator: E-Crystal (large) */
    {STAGE_GIANT_ELEVATOR, 183, 287, 380},  /* Giant Elevator: Life Capsule (medium) */
    {STAGE_SUB_ARCADIA, 18, 51, 381},  /* Sub Arcadia: E-Crystal (large) */
    {STAGE_SUB_ARCADIA, 156, 166, 382},  /* Sub Arcadia: Life Capsule (medium) */
};

#endif /* AP */
