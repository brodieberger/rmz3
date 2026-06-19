#ifndef GUARD_RMZ3_SOUND_H
#define GUARD_RMZ3_SOUND_H

#include "types.h"

// Sound API

void StopAllMusics(void);
void TurnDownBGM(void);
void TurnUpBGM(void);
void PlayBGM(SoundID n);
void FadeOutBGM(SoundID n);
bool32 _isSoundPlaying(SoundID n);
s16 PlaySound(SoundID id);
void StopSound(s16 n);
void FadeOutSound(s16 r0, u16 r1);
bool32 isSoundPlaying(SoundID n);
void SetStageNoiseVolume(SoundID n);

#endif  // GUARD_RMZ3_SOUND_H
