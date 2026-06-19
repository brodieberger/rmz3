#include "story.h"

#include "game.h"
#include "global.h"

/**
 * @brief gCurStory に src の内容をコピーして、いくつかのフラグをリセットする
 * @param src story data to load, gGameState.save.story or gGameState.save.savedStory (only GameOver)
 * @note 0x080195F4
 */
void LoadStoryData(u8 stageID, struct Story* src) {
  s16 i;
  gCurStory.id = stageID;
  MemCopy32(src, &gCurStory.s, sizeof(struct Story));
  CLEAR_FLAG(gCurStory.s.gameflags, IN_CYBERSPACE);
  CLEAR_FLAG(gCurStory.s.gameflags, ARMOR_ELF_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, GIANT_ELF_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, TIME_ELF_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, ELF_B4_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, DYLPHINA_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, METTAUR_ENABLED);
  CLEAR_FLAG(gCurStory.s.gameflags, FLAG_49);
  for (i = 29; i < 70; i++) {
    ENEMY_KILLCOUNT(i - 29) = 0;
  }
  gCurStory.s.unk_54 = 0;
}

/**
 * @brief 引数で渡した Story の内容をクリアする (gCurStory とは無関係)
 * @param story クリア対象の Story (常に　&gGameState.save.story　っぽい)
 * @note 0x08019678
 */
void FUN_08019678(struct Story* story) {
  MemFill32(0, story, sizeof(struct Story));
  SET_FLAG(story->gameflags, FLAG_BUSTER_ONLY);
  SET_FLAG(story->gameflags, FLAG_SABER_ONLY);
}

/**
 * @brief gCurStory.s の内容を dst にコピーする
 * @note 0x080196b8
 */
void StoreStoryData(struct Story* dst) { MemCopy32(&gCurStory.s, dst, sizeof(struct Story)); }
