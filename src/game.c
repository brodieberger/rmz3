#include "game.h"

#include "global.h"
#include "system.h"

void MainLoop_Game(struct GameState* g);
void MainLoop_Menu(struct GameState* g);
void MainLoop_Disk(struct GameState* g);
void MainLoop_Minigame(struct GameState* g);

void Process_Game(struct Process* p) {
  static const GameLoopFunc scenes[4] = {
      MainLoop_Game,  // MainGame
      MainLoop_Menu,  // スタートメニュー
      MainLoop_Disk,  // "シークレットディスクのカイセキ"のシーン
      MainLoop_Minigame,
  };

  FUN_08002428(p);
  do {
    scenes[gGameState.mode[0]](&gGameState);
    SwitchProcess(TRUE);
  } while (TRUE);
}

void SetGameMode(struct GameState* g, u32 mode) {
  *((u32*)g->mode) = mode;
  *((u32*)&g->frames) = 0;
  *(u32*)g->unk_008 = 0;
};
