#ifndef __INCLUDE_RANDOM_H__
#define __INCLUDE_RANDOM_H__

#include "gba/gba.h"

#define LCG(s) (((s * 0x343FD + 0x269EC3) << 1) >> 1)

extern u32 RNG_0202f388;

#define RANDOM(rng) ((rng = LCG(rng)) >> 16)

#endif  // __INCLUDE_RANDOM_H__
