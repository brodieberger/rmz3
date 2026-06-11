#ifndef __INCLUDE_SCORE_H__
#define __INCLUDE_SCORE_H__

#include "constants/constants.h"
#include "gba/gba.h"

// ゲーム全体を通じた、プレイヤーの戦績 (= プレイヤーの上手さによって変わるものを管理する)
struct TotalScore {
  u8 extraLife;
  u8 rank;  // 0: F, 1: E, ... A: 5, S: 6
  u8 codenameSuffix;
  u8 pad_03;
  u8 codenamePrefix;
  u8 pad_05;
  bool8 allElfCompleted;  // エルフを全種類捕まえているか(育てているかは無関係)

  u8 allCyberElfBreeded : 4;  // 0 or 1, 1 なら 全部のエルフを育てきってる(称号エルフブリーダーの条件を満たしているか)
  u8 allSecretDiskFound : 4;  // 0 or 1, 1 なら 全てのシークレットディスクを取得している(解析の有無は問わない)

  u8 clearCodenameSuffix;  // ストーリークリア時に適用される
  u8 clearCodenamePrefix;  // ストーリークリア時に適用される

  s16 scoreSum;         // 今までクリアしたステージのスコアの合計
  u32 playTime;         // フレーム単位のプレイ時間
  u8 clearCount;        // 今までクリアしたステージの数
  u8 unusedClearCount;  // clearCountと全く同じ内容
  u8 unk_12;
  u8 lastStage;            // 最後にクリアしたステージ 根拠: 08019794
  u32 missionDones;        // クリア済みミッション を表すbitfield
  u32 unusedMissionDones;  // missionDonesと全く同じ内容
  u32 unk_1c;
  u8 unk_20[20];
  u8 suffixIdx[8];  // 0834c9e0 の2つ目のidx(0..7)
  u8 unk_3a[16];
  u8 fusionCount;  // フュージョンエルフを使った回数 リザルトのエルフ使用回数に反映されるが、減点には反映せず
};  // 80 bytes
static_assert(sizeof(struct TotalScore) == 80);

// 現在進行中のミッションの戦績 0202fe20
struct MissionScore {
  struct TotalScore* total;
  u8 stageID;      // ミッション開始時に、 ResetMissionScore でミッションのステージIDがセットされる
  s8 resultScore;  // CalcMissionScore でセットされる
  u8 unk_06;

  // ミッション中は、これらの値をリアルタイムに更新して、最後に CalcMissionScore でスコアを計算して、 resultScore, eachScore にセットする
  u8 missionPoint;  // 0~20
  u32 clearTime;    // Frame
  u16 enemyCount;
  u16 totalDamage;
  u32 elfPenalty;  // エルフの使った数じゃなくて、エルフ使用による永続的な減点
  u16 retryCount;

  u8 eachScore[6];                // ミッション中は変化しない (CalcMissionScore で計算してセットされる), 0: mission, 1: clear time, 2: enemy count, 3: total damage, 4: retry count, 5: elf
  u16 weaponCount[WEAPON_KINDS];  // Weapon use count, 武器を使うとリアルタイムに更新される (buster, saber, rod, shield)
};

extern struct MissionScore gScore;  // addr:0x0202fe20

void ClearPlayInfo(struct TotalScore* p);
void ResetMissionScore(u8 stageID, struct TotalScore* total_score);
void AddMissionDamage(u16 damage);

static inline void IncWeaponUseCount(s32 idx) {
  if (gScore.weaponCount[idx] < 0xFFFF) gScore.weaponCount[idx]++;
}

#define gMissionDones ((gScore.total)->missionDones)

#endif  // __INCLUDE_SCORE_H__
