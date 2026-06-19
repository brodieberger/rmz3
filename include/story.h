#ifndef GUARD_RMZ3_STORY_H
#define GUARD_RMZ3_STORY_H

#include "common.h"
#include "gba/gba.h"
#include "types.h"

#define ENEMY_KILLCOUNT(n) (gCurStory.s.counts[29 + n])

#define IS_MISSION (!FLAG(gCurStory.s.gameflags, IS_FREERUN))
#define IS_METTAUR (FLAG(gCurStory.s.gameflags, METTAUR_ENABLED))

// --------------------------------------------

struct Story {
  u8 gameflags[8];  // 0x00, bitfields, see "include/constants/flag.h"
  /*
    0..28: 会話の進行度
    29..69: 雑魚敵の種類ごとの撃破数
    70..71: 火山のリコイルで動かす棺桶みたいなコンテナの移動量(ピクセル単位), VolcanoCoffin_Init
  */
  u8 counts[29 + 41 + 2];  // chatProgress[29] + zakoCounts[41] + volcanoCoffinX[2]
  u8 unk_54;               // 0x50, エネルギー施設の何かのbitfield
  u8 _[3];                 // padding
};  // 84 bytes
static_assert(sizeof(struct Story) == 84);

// 0202fdc0
// ラン開始時に gGameState.save.story から gCurStory にロードして、ラン終了時に gCurStory から gGameState.save.story に書き戻す
struct Story88 {
  u16 id;          // 0x00, ヘッダ的な何か?, ゲーム時にはラン開始時に stageID が入る
  u16 _;           // 0x02, padding
  struct Story s;  // 0x04
};  // 88 bytes
static_assert(sizeof(struct Story88) == 88);

// --------------------------------------------

extern struct Story88 gCurStory;

// --------------------------------------------

void LoadStoryData(u8 stageID, struct Story* src);
void StoreStoryData(struct Story* dst);
void FUN_08019678(struct Story* story);

#endif  // GUARD_RMZ3_STORY_H
