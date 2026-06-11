#include "animation.h"

#include "global.h"

// State Machine for animation
// AnimCmd の実行とその状態遷移　のみを担当 (グラフィックには何も関与しない)

// clear AnimState
void ResetAnimState(AnimState* a, const AnimCmd* const* const table) {
  a->table = (const AnimCmd**)table;  // table is overwritten later
  a->id = 0, a->cmdIdx = 0;
  a->duration = (*table)->frame + 1;
  a->state = MOTION_STATE_0;
}

void SetAnimSubID(AnimState* a, u8 id) {
  s8 frame2ndCmd;

  a->id = id, a->cmdIdx = 0;
  a->duration = a->table[id][0].frame + 1;

  // コマンド列の2個目のAnimCmdの frame は　負の数の場合は、制御命令として扱う (-1: 終端, -2: goto, あとは不明)
  frame2ndCmd = a->table[a->id][1].frame;
  if (frame2ndCmd < 0) {
    if (a->duration == 2) {
      a->state = MOTION_STATE_2;

    } else if (a->duration == 1) {
      if (frame2ndCmd == AC_TERMINATOR) {
        a->state = ANIM_END;
      } else {
        a->state = ANIM_NEXT_GOTO;  // 負のときは AC_TERMINATOR でなかったら　必ず　 AC_GOTO?
      }
    } else {
      a->state = MOTION_STATE_1;
    }
    return;
  }

  a->state = MOTION_STATE_0;
}

// 0x08004fa8
void StepAnimState(AnimState* a) {
  a->duration--;
  if (a->duration == 0) {
    u8 prev = a->cmdIdx;
    a->cmdIdx++;

    if (a->table[a->id][a->cmdIdx].frame == AC_TERMINATOR) {
      a->cmdIdx = prev, a->duration = 1;  // 直前のグラフィックを表示し続ける
      a->state = ANIM_END;
      return;
    }
    if (a->table[a->id][a->cmdIdx].frame == AC_GOTO) {
      a->cmdIdx = a->table[a->id][a->cmdIdx].param;
      a->state = MOTION_STATE_0;
    }

    a->duration = a->table[a->id][a->cmdIdx].frame;

    // SetAnimSubID と同様に、次のAnimCmdの frame を確認して、負の数の場合は制御命令として扱う
    a->cmdIdx++;
    if (a->table[a->id][a->cmdIdx].frame < 0) {
      if (a->duration == 2) {
        a->state = MOTION_STATE_2;
      } else if (a->duration == 1) {
        if (a->table[a->id][a->cmdIdx].frame == AC_TERMINATOR) {
          a->state = ANIM_END;
        } else {
          a->state = ANIM_NEXT_GOTO;  // 負のときは AC_TERMINATOR でなかったら　必ず　 AC_GOTO?
        }
      } else {
        a->state = MOTION_STATE_1;
      }
    }
    a->cmdIdx--;
    return;
  }

  if (a->state != MOTION_STATE_0) {
    if (a->duration == 2) {
      a->state = MOTION_STATE_2;
    } else if (a->duration == 1) {
      if (a->table[a->id][a->cmdIdx + 1].frame == AC_TERMINATOR) {
        a->state = ANIM_END;
      } else {
        a->state = ANIM_NEXT_GOTO;  // 負のときは AC_TERMINATOR でなかったら　必ず　 AC_GOTO?
      }
    }
  }
}
