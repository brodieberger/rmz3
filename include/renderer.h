#ifndef GUARD_RMZ3_RENDERER_H
#define GUARD_RMZ3_RENDERER_H

#include "common.h"
#include "constants/constants.h"
#include "gba/gba.h"
#include "types.h"

// TODO: 後で Renderer に名前を変える予定
// 描画に順番を設定するための描画タスク管理

#define TASK_LENGTH 128

// 任意の型のポインタ + そのポインタ+pivot で呼び出すコールバック
typedef struct Task {
  struct Task* next;  // 同じ優先度を持つ次のタスクへのポインタ
  void (*fn)(struct Task*, struct DrawPivot*);
} DrawTask;

typedef DrawTask* DrawQueue[4][32];

struct TaskManager {
  DrawQueue slow_buffer;  // タスク用のメモリ領域(IWRAMに余裕がない場合はここを使う)
  DrawQueue* tasks;       // 現在の DrawQueue へのポインタ
  struct Pivot* pivot;    // &camera->pivot
  void* _;                // Unused
};
static_assert(sizeof(struct TaskManager) == 524);

void ResetTaskManager(struct TaskManager* tm);
void SetTaskPivot(struct TaskManager* tm, struct Pivot* pivot);
void PrependTask(struct TaskManager* tm, struct Task* task);
void AppendTask(struct TaskManager* tm, struct Task* task, s16 prio, s16 x);
void ClearTaskBuffer(struct TaskManager* tm);
void RunAllTasks(struct TaskManager* tm);

void SetTaskCallback(struct Task* t, void* cb);

#endif  // GUARD_RMZ3_RENDERER_H
