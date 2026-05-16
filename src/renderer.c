#include "renderer.h"

#include "entity.h"
#include "global.h"
#include "sprite.h"

void ResetTaskManager(struct TaskManager* tm) {
  _CpuFastFill(0, tm->slow_buffer, TASK_LENGTH * 4);
  tm->tasks = &tm->slow_buffer;
  tm->pivot = NULL;
  tm->_ = NULL;
}

void SetTaskPivot(struct TaskManager* tm, struct Pivot* pivot) { tm->pivot = pivot; }

static void unused_08004e58(struct TaskManager* tm, void* r1) { tm->_ = r1; }

void PrependTask(struct TaskManager* tm, struct Task* task) {
  task->next = (*tm->tasks)[0][0];
  (*tm->tasks)[0][0] = task;
}

static void unused_08004e74(struct TaskManager* tm, struct Task* task, s16 prio) {
  struct Task* cur = (*tm->tasks)[prio][0];
  task->next = cur;
  (*tm->tasks)[prio][0] = task;
}

void AppendTask(struct TaskManager* tm, struct Task* task, s16 prio, s16 col) {
  struct Task* cur = (*tm->tasks)[prio][col];
  task->next = cur;
  (*tm->tasks)[prio][col] = task;
}

/*
  .tasks[0][0] から .tasks[3][31] の順に描画タスクを呼び出す
  .tasks[i][j] に入っているのは、 DrawTask のリンクリストであることに注意
*/
void RunAllTasks(struct TaskManager* tm) {
  s32 i;
  struct Task** list;
  struct DrawPivot c;

  if (tm->pivot != NULL) {
    CreateDrawPivot(&c, tm->pivot, tm->_);

    list = (struct Task**)(*tm->tasks);
    for (i = 0; i < TASK_LENGTH; i++) {
      struct Task* task = list[0];  // = .tasks[i / 32][i % 32]
      list = &list[1];
      while (task != NULL) {  // task -> task->next -> task->next->next -> ... -> NULL
        (task->fn)(task, &c);
        task = task->next;
      }
    }
  }
}

// ゲーム中は毎回フレーム開始時に呼び出される
void ClearTaskBuffer(struct TaskManager* tm) {
  tm->tasks = Malloc(TASK_LENGTH * 4);
  if (tm->tasks == NULL) {  // Malloc失敗、つまり IWRAM に余裕がない場合は自前のバッファ(EWRAMなので低速)を使う
    tm->tasks = &tm->slow_buffer;
  }

  {
    const u32 fill = 0;
    void* dst = *tm->tasks;
    _CpuFastFill(fill, dst, TASK_LENGTH * 4);
  }
}
