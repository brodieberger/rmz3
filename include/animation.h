#ifndef __INCLUDE_ANIMATION_H__
#define __INCLUDE_ANIMATION_H__

#include "constants/constants.h"
#include "gba/gba.h"
#include "types.h"

// AnimCmd の配列の先頭を指すポインタを AnimScript と呼ぶことにします

// AnimState.state
enum AnimStateStatus {
  MOTION_STATE_0,
  MOTION_STATE_1,
  MOTION_STATE_2,
  ANIM_END,
  ANIM_NEXT_GOTO,  // 次回の StepAnimState で AC_GOTO の AnimCmd が実行されることを示す (おそらく、無限ループするようなアニメーションを別のものに変える時に、 ループの途中でグラが変わると不自然なため、ループの終わりを検知できるようにするためのフラグ)
};

// AnimCmd.frame
#define AC_TERMINATOR -1
#define AC_GOTO -2  // AnimCmd.param にジャンプする (つまり, cmdIdx = AnimCmd.param)

typedef struct __attribute__((packed, aligned(2))) {
  u8 param;  // Spriteの場合: どのメタスプライトを使うか, PaletteAnimation の場合: どの PlttAnimData を使うか
  s8 frame;  // この AnimCmd のフレーム数, 負の数の場合は、制御コマンドとして扱う (-1: 終端, -2: goto, あとは不明), opcode に名前を変えてもいいかも？
} AnimCmd;   // 2 bytes

typedef struct {
  const AnimCmd** table;  // 0x00, 複数の AnimScript のリスト (どの AnimScript を使うかを AnimState.id で指定する)
  u8 id;                  // 0x04, AnimState.table[AnimState.id] が現在実行中の AnimScript になる
  s8 cmdIdx;              // 0x05, 現在の AnimScript のどの AnimCmd を実行しているかを指すインデックス

  s8 duration;  // 0x06, StepAnimState で 減っていき 0 になると次の AnimCmd に進む
  u8 state;     // 0x07, see AnimStateStatus
} AnimState;    // 8 bytes;
static_assert(sizeof(AnimState) == 8);

void ResetAnimState(AnimState* a, const AnimCmd* const* const table);
void SetAnimSubID(AnimState* a, u8 id);
void StepAnimState(AnimState* a);

#endif  // __INCLUDE_ANIMATION_H__
