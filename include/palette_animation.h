#ifndef __INCLUDE_PALETTE_ANIMATION_H__
#define __INCLUDE_PALETTE_ANIMATION_H__

#include "animation.h"
#include "gba/gba.h"

// 元々 Blink という名前をつけており、まだBlinkという名前が残っている部分もあるが、将来的にはすべて PaletteAnimation (or PlttAnim) に統一する予定

#define MAX_PLTT_ANIM 16

// e.g. 0x085ba244
struct PlttAnimData {
  u8 len;
  u8 start;
  u8 end;
  u8 _;
  // u16 pltt[len*n]; n = 次の PlttAnimData 構造体までの長さによって変動
};  // 4 bytes;
static_assert(sizeof(struct PlttAnimData) == 4);

// 0x02002000
typedef struct {
  struct PlttAnimData* pal;  // 0x00
  AnimCmd** cmds;            // 0x04, cmds[0] が現在のAnimCmdのコマンド列の先頭 (でも使われてなさそう)
  AnimState m;               // 0x08
  bool16 paused;             // 0x10
  u16 offsetByte;            // 0x12, PlttAnimData の示す 転送先　に加えるオフセット (バイト単位)
} PaletteAnimation;          // 20 bytes;
static_assert(sizeof(PaletteAnimation) == 20);

// アニメーションのステート更新は各自 StepPaletteAnimation を呼び出す必要がある
struct PaletteAnimationManager {
  u16 ids[MAX_PLTT_ANIM];                 // 0x00, 0: 空きエントリ, n+1: パレットアニメーションのID (n)
  PaletteAnimation anims[MAX_PLTT_ANIM];  // 0x20
};
static_assert(sizeof(struct PaletteAnimationManager) == 352);

// --------------------------------------------

extern struct PaletteAnimationManager gPaletteAnimationManager;

// --------------------------------------------

void StartPaletteAnimation(u16 id, u16 ofs);
void RemovePaletteAnimation(u16 id);
u32 StepPaletteAnimation(u16 id);
void RemoveAllPaletteAnimations(void);
void TransferAnimatedPalettesToPaletteBuffer(void);
void PauseAllPaletteAnimations(void);
void ResumeAllPaletteAnimations(void);

#endif  // __INCLUDE_PALETTE_ANIMATION_H__
