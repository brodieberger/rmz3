#ifndef GUARD_RMZ3_RENDERER_H
#define GUARD_RMZ3_RENDERER_H

#include "common.h"
#include "constants/constants.h"
#include "gba/gba.h"
#include "types.h"

// 描画に順番を設定するための描画タスク管理

#define TASK_LENGTH 128

// 任意の型のポインタ + そのポインタ+pivot で呼び出すコールバック
typedef struct Task {
  struct Task* next;  // 同じ優先度を持つ次のタスクへのポインタ
  void (*fn)(struct Task*, struct DrawPivot*);
} RenderTask;

typedef RenderTask* DrawQueue[4][32];

typedef struct Renderer {
  DrawQueue slow_buffer;  // タスク用のメモリ領域(IWRAMに余裕がない場合はここを使う)
  DrawQueue* tasks;       // 現在の DrawQueue へのポインタ
  struct Pivot* pivot;    // &camera->pivot
  void* _;                // Unused
} Renderer;
static_assert(sizeof(Renderer) == 524);

void Renderer_Init(Renderer* r);
void Renderer_SetPivot(Renderer* r, struct Pivot* pivot);
void Renderer_PrependTask(Renderer* r, struct Task* task);
void Renderer_SendTask(Renderer* r, struct Task* task, s16 prio, s16 x);
void Renderer_Clear(Renderer* r);
void Renderer_Flush(Renderer* r);

void SetTaskCallback(struct Task* t, void* cb);

#endif  // GUARD_RMZ3_RENDERER_H
