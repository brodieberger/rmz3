#include "overworld.h"
#include "zero.h"

void ClearInputHistory(struct Zero* z) {
  s32 i;
  for (i = 0; i < ARRAY_COUNT((z->input).history); i++) {
    (z->input).history[i] = 0;
  }
}

void handlePlayerInput(struct Zero* z) {
  s32 i = ARRAY_COUNT((z->input).history) - 1;
  struct StageRun* s = &gStageRun;
  KEY_INPUT* history = &(z->input).history[0];

  /*
    history[63] = history[62];
    history[62] = history[61];
    ...
    history[2] = history[1];
    history[1] = history[0];
  */
  for (; i != 0; i--) {
    history[i] = history[i - 1];
  }

  history[0] = s->input & 0x0FFF;
  (z->input).pressed = ((z->input).raw ^ s->input) & s->input;
  (z->input).raw = s->input;
}
