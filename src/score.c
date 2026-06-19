#include "score.h"

#include "game.h"
#include "global.h"

// codenamePrefix
#define CODENAME_NO_PREFIX 0
#define FLAWLESS_01 1     // カンゼンシュギの
#define TRAITOR 2         // ウラギリの
#define GOD_SPEED 3       // ハヤテの
#define LIGHTNING 4       // イダテンの
#define SLUGGISH 5        // ドンソクの
#define RUTHLESS 6        // レイケツ
#define FLAWLESS_07 7     // ムキズの
#define WOUNDED 8         // キズダラケの
#define IMMORTAL 9        // フジミの
#define CODENAME_DISK 10  // ディスク
#define CODENAME_ELF 11   // エルフ

// codenameSuffix
#define WARRIOR 0         // センシ
#define HERO 1            // ユウシャ
#define VALIANT 2         // エイユウ
#define SAVIOR 3          // キュウセイシュ
#define REDEEMER 4        // ゴッド
#define GUNMAN 5          // ガンマン
#define SHOOTER 6         // シューター
#define SNIPER 7          // スナイパー
#define EDGE 8            // ケンシ
#define EDGE_BOY 9        // ケンキャク
#define EDGE_MAN 10       // ケンセイ
#define STABBER 11        // スタッバー
#define PENETRATOR 12     // ペネトレーター
#define ROD_MASTER 13     // ロッドマスター
#define RIPPER 14         // リッパー
#define SLASHER 15        // スラッシャー
#define SHIELD_MASTER 16  // シールドマスター
#define KILLER 17         // キラー
#define COLLECTOR 18      // コレクター
#define BREEDER 19        // ブリーダー

// プレイヤーのスコアに関することがメイン

// 0x080196E4
void ClearPlayInfo(struct TotalScore* p) {
  s32 i;
  p->extraLife = 2;
  p->rank = RANK_F;
  p->codenameSuffix = WARRIOR;
  p->pad_03 = 0;
  p->clearCodenameSuffix = WARRIOR;
  p->codenamePrefix = CODENAME_NO_PREFIX;
  p->pad_05 = 0;
  p->clearCodenamePrefix = CODENAME_NO_PREFIX;
  p->allElfCompleted = 0;
  p->allCyberElfBreeded = 0;
  p->allSecretDiskFound = 0;
  p->scoreSum = 0;
  p->playTime = 0;
  p->clearCount = 0, p->unusedClearCount = 0;
  p->unk_12 = 0;
  p->lastStage = 0;
  p->missionDones = 0, p->unusedMissionDones = 0;
  p->unk_1c = 0;
  p->fusionCount = 0;
  for (i = 0; i < 20; i++) p->unk_20[i] = 0;
  for (i = 0; i < 8; i++) p->suffixIdx[i] = 0;
  for (i = 0; i < 16; i++) p->unk_3a[i] = 0;
}

// 0x08019758
void ResetMissionScore(u8 stageID, struct TotalScore* total_score) {
  gScore.total = total_score;
  gScore.stageID = stageID;
  gScore.resultScore = 0;
  gScore.unk_06 = 0;
  gScore.missionPoint = 20;
  gScore.clearTime = 0;
  gScore.enemyCount = 0;
  gScore.totalDamage = 0;
  gScore.retryCount = 0;
  gScore.elfPenalty = 0;
  gScore.eachScore[0] = gScore.eachScore[1] = gScore.eachScore[2] = gScore.eachScore[3] = gScore.eachScore[4] = gScore.eachScore[5] = 0;
  gScore.weaponCount[0] = gScore.weaponCount[1] = gScore.weaponCount[2] = gScore.weaponCount[3] = 0;
}

static void unused_08019790(void) {}

// ------------------------------------------------------------------------------------------------------------------------------------

static const s32 gClearTimeTable[17] = {0, 130, 220, 220, 210, 240, 200, 200, 180, 200, 220, 340, 180, 260, 300, 250, 700};
static const s32 gEnemyCountTable[17] = {0, 20, 40, 25, 50, 40, 45, 50, 30, 45, 35, 40, 30, 25, 80, 40, 35};

// clang-format off
static const s32 sRankBorder[7] = {
    [RANK_F] = 46,
    [RANK_E] = 56,
    [RANK_D] = 66,
    [RANK_C] = 76,
    [RANK_B] = 86,
    [RANK_A] = 96,
    [RANK_S] = 65535,
};
// clang-format on

// clang-format off
const u8 gCodeNameSuffixs[6][8] = {
    /* Rank S */ [0] = { WARRIOR, HERO, HERO, VALIANT, VALIANT, SAVIOR, SAVIOR, REDEEMER },
    /* Buster */ [1] = { WARRIOR, GUNMAN, GUNMAN, SHOOTER, SHOOTER, SNIPER, SNIPER, SNIPER },
    /* Saber  */ [2] = { WARRIOR, EDGE, EDGE, EDGE_BOY, EDGE_BOY, EDGE_MAN, EDGE_MAN, EDGE_MAN },
    /* Rod    */ [3] = { WARRIOR, STABBER, STABBER, PENETRATOR, PENETRATOR, ROD_MASTER, ROD_MASTER, ROD_MASTER },
    /* Shield */ [4] = { WARRIOR, RIPPER, RIPPER, SLASHER, SLASHER, SHIELD_MASTER, SHIELD_MASTER, SHIELD_MASTER },
    /* ???    */ [5] = {},
};
// clang-format on

static void calcCodename(void);

// 0x08019794
NON_MATCH void CalcMissionScore(void) {
#if MODERN
  s32 timeover;
  s32 enemy_count;
  s32 total_damage;
  s32 retry;
  s32 elf_score;
  s32 average;
  s32 rank;

  struct MissionScore* m = &gScore;
  (m->total)->clearCount++;
  (m->total)->missionDones |= 1 << m->stageID;
  (m->total)->lastStage = m->stageID;
  m->eachScore[0] = m->missionPoint;
  (m->total)->unusedClearCount++;
  (m->total)->unusedMissionDones |= 1 << m->stageID;

  timeover = (m->clearTime / 60) - gClearTimeTable[m->stageID];
  if (timeover < 1) {
    m->eachScore[1] = 20;
  } else if (timeover < 200) {
    m->eachScore[1] = 20 - (timeover + 9) / 10;
  } else {
    m->eachScore[1] = 0;
  }

  enemy_count = m->enemyCount / (m->retryCount + 1);
  if (enemy_count == 0) {
    m->eachScore[2] = 0;
  } else {
    s32 n = (gEnemyCountTable[m->stageID] * 10) / enemy_count;
    if (n <= 10) {
      m->eachScore[2] = 15;
    } else if (n > 24) {
      m->eachScore[2] = 0;
    } else {
      m->eachScore[2] = 25 - n;
    }
  }

  total_damage = m->totalDamage;
  if (total_damage == 0) {
    m->eachScore[3] = 15;
  } else if (total_damage > 90) {
    m->eachScore[3] = 0;
  } else {
    m->eachScore[3] = 15 - ((total_damage - 1) / 6);
  }

  retry = m->retryCount;
  if (retry == 0) {
    m->eachScore[4] = 15;
  } else if (retry > 4) {
    m->eachScore[4] = 0;
  } else {
    m->eachScore[4] = 15 - (retry * 3);
  }

  // ここがコンパイル結果と合わない
  elf_score = 15 - m->elfPenalty;
  m->eachScore[5] = (elf_score < -100) ? -100 : elf_score;

  m->resultScore = m->eachScore[0] + m->eachScore[1] + m->eachScore[2] + m->eachScore[3] + m->eachScore[4] + m->eachScore[5];
  (m->total)->scoreSum += m->resultScore;

  average = (m->total)->scoreSum / (m->total)->clearCount;
  for (rank = 0; average >= sRankBorder[rank]; rank++) {
  }
  (m->total)->rank = rank;
  calcCodename();

  if ((m->weaponCount[1] != 0) || (m->weaponCount[2] != 0) || (m->weaponCount[3] != 0)) {
    CLEAR_FLAG(gCurStory.s.gameflags, FLAG_BUSTER_ONLY);
  }
  if ((m->weaponCount[0] != 0) || (m->weaponCount[2] != 0) || (m->weaponCount[3] != 0)) {
    CLEAR_FLAG(gCurStory.s.gameflags, FLAG_SABER_ONLY);
  }
#else
  INCCODE("asm/wip/CalcMissionScore.inc");
#endif
}

void AddMissionDamage(u16 damage) {
  if ((damage < 65) && (gScore.totalDamage + damage < 10000)) {
    gScore.totalDamage += damage;
  }
}

NAKED static void calcCodename(void) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	sub sp, #0x54\n\
	ldr r0, _08019974 @ =gScore\n\
	ldr r1, [r0]\n\
	mov r8, r1\n\
	ldrb r5, [r1, #1]\n\
	ldrb r1, [r0, #0x17]\n\
	cmp r1, #0x13\n\
	bls _08019978\n\
	movs r0, #4\n\
	b _08019A06\n\
	.align 2, 0\n\
_08019974: .4byte gScore\n\
_08019978:\n\
	cmp r1, #0x11\n\
	bls _08019980\n\
	movs r0, #3\n\
	b _08019A0E\n\
_08019980:\n\
	cmp r1, #0\n\
	bne _08019988\n\
	movs r0, #5\n\
	b _080199F6\n\
_08019988:\n\
	ldr r2, _080199BC @ =gScore\n\
	ldrb r0, [r2, #0x18]\n\
	cmp r0, #0xf\n\
	bne _080199C4\n\
	ldr r1, _080199C0 @ =gEnemyCountTable\n\
	ldrb r0, [r2, #4]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	lsls r4, r0, #2\n\
	adds r4, r4, r0\n\
	lsls r4, r4, #1\n\
	ldrh r0, [r2, #0xc]\n\
	ldrh r1, [r2, #0x14]\n\
	adds r1, #1\n\
	bl __divsi3\n\
	adds r1, r0, #0\n\
	adds r0, r4, #0\n\
	bl __divsi3\n\
	cmp r0, #5\n\
	bgt _080199C4\n\
	movs r0, #6\n\
	b _08019A0E\n\
	.align 2, 0\n\
_080199BC: .4byte gScore\n\
_080199C0: .4byte gEnemyCountTable\n\
_080199C4:\n\
	ldr r1, _080199D0 @ =gScore\n\
	ldrb r0, [r1, #0x19]\n\
	cmp r0, #0xd\n\
	bls _080199D4\n\
	movs r0, #7\n\
	b _08019A06\n\
	.align 2, 0\n\
_080199D0: .4byte gScore\n\
_080199D4:\n\
	cmp r0, #5\n\
	bhi _080199DC\n\
	movs r0, #8\n\
	b _08019A0E\n\
_080199DC:\n\
	ldr r1, _080199E8 @ =gScore\n\
	ldrb r0, [r1, #0x1a]\n\
	cmp r0, #0xf\n\
	bne _080199EC\n\
	movs r0, #9\n\
	b _08019A06\n\
	.align 2, 0\n\
_080199E8: .4byte gScore\n\
_080199EC:\n\
	ldr r3, _080199FC @ =gScore\n\
	ldrb r0, [r3, #0x16]\n\
	cmp r0, #0x14\n\
	bne _08019A00\n\
	movs r0, #1\n\
_080199F6:\n\
	mov r1, r8\n\
	strb r0, [r1, #4]\n\
	b _08019A12\n\
	.align 2, 0\n\
_080199FC: .4byte gScore\n\
_08019A00:\n\
	cmp r0, #0\n\
	bne _08019A0C\n\
	movs r0, #2\n\
_08019A06:\n\
	mov r2, r8\n\
	strb r0, [r2, #4]\n\
	b _08019A12\n\
_08019A0C:\n\
	movs r0, #0\n\
_08019A0E:\n\
	mov r3, r8\n\
	strb r0, [r3, #4]\n\
_08019A12:\n\
	cmp r5, #6\n\
	bne _08019A1E\n\
	movs r4, #0\n\
	mov r0, r8\n\
	strb r4, [r0, #4]\n\
	b _08019A60\n\
_08019A1E:\n\
	ldr r1, _08019A44 @ =gScore\n\
	ldrh r4, [r1, #0x1c]\n\
	ldrh r5, [r1, #0x1e]\n\
	adds r1, r5, r4\n\
	ldr r2, _08019A44 @ =gScore\n\
	ldrh r6, [r2, #0x20]\n\
	adds r1, r1, r6\n\
	ldrh r7, [r2, #0x22]\n\
	adds r1, r1, r7\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #0xa\n\
	bl __divsi3\n\
	cmp r4, r0\n\
	blt _08019A48\n\
	movs r4, #1\n\
	b _08019A60\n\
	.align 2, 0\n\
_08019A44: .4byte gScore\n\
_08019A48:\n\
	cmp r5, r0\n\
	blt _08019A50\n\
	movs r4, #2\n\
	b _08019A60\n\
_08019A50:\n\
	cmp r6, r0\n\
	blt _08019A58\n\
	movs r4, #3\n\
	b _08019A60\n\
_08019A58:\n\
	movs r4, #5\n\
	cmp r7, r0\n\
	blt _08019A60\n\
	movs r4, #4\n\
_08019A60:\n\
	mov r3, r8\n\
	ldrb r0, [r3, #2]\n\
	strb r0, [r3, #3]\n\
	movs r3, #0\n\
	lsls r0, r4, #0x10\n\
	mov sl, r0\n\
	mov r1, r8\n\
	adds r1, #0x34\n\
	mov r2, r8\n\
	adds r2, #0x20\n\
	str r2, [sp, #0x10]\n\
	movs r0, #0x3c\n\
	add r0, r8\n\
	mov sb, r0\n\
	movs r2, #0x21\n\
	add r2, r8\n\
	mov ip, r2\n\
	mov r0, r8\n\
	adds r0, #0x22\n\
	str r0, [sp, #0x14]\n\
	mov r2, r8\n\
	adds r2, #0x23\n\
	str r2, [sp, #0x18]\n\
	adds r0, #2\n\
	str r0, [sp, #0x1c]\n\
	adds r2, #2\n\
	str r2, [sp, #0x20]\n\
	adds r0, #2\n\
	str r0, [sp, #0x24]\n\
	adds r2, #2\n\
	str r2, [sp, #0x28]\n\
	adds r0, #2\n\
	str r0, [sp, #0x2c]\n\
	adds r2, #2\n\
	str r2, [sp, #0x30]\n\
	adds r0, #2\n\
	str r0, [sp, #0x34]\n\
	adds r2, #2\n\
	str r2, [sp, #0x38]\n\
	adds r0, #2\n\
	str r0, [sp, #0x3c]\n\
	adds r2, #2\n\
	str r2, [sp, #0x40]\n\
	adds r0, #2\n\
	str r0, [sp, #0x44]\n\
	adds r2, #2\n\
	str r2, [sp, #0x48]\n\
	adds r0, #2\n\
	str r0, [sp, #0x4c]\n\
	mov r2, sp\n\
	adds r2, #8\n\
	str r2, [sp, #0x50]\n\
	mov r0, sl\n\
	asrs r6, r0, #0x10\n\
	adds r5, r1, #0\n\
	movs r7, #0\n\
_08019AD0:\n\
	lsls r0, r3, #0x10\n\
	asrs r2, r0, #0x10\n\
	adds r3, r0, #0\n\
	cmp r2, r6\n\
	beq _08019AE0\n\
	adds r0, r5, r2\n\
	strb r7, [r0]\n\
	b _08019AEC\n\
_08019AE0:\n\
	adds r2, r5, r2\n\
	ldrb r0, [r2]\n\
	cmp r0, #6\n\
	bhi _08019AEC\n\
	adds r0, #1\n\
	strb r0, [r2]\n\
_08019AEC:\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r0, r3, r2\n\
	lsrs r3, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #5\n\
	ble _08019AD0\n\
	lsls r0, r4, #0x10\n\
	asrs r0, r0, #0x10\n\
	adds r1, r1, r0\n\
	lsls r0, r0, #3\n\
	ldrb r1, [r1]\n\
	adds r0, r0, r1\n\
	ldr r3, _08019C60 @ =gCodeNameSuffixs\n\
	adds r0, r0, r3\n\
	ldrb r0, [r0]\n\
	movs r2, #0\n\
	mov r1, r8\n\
	strb r0, [r1, #2]\n\
	ldrb r1, [r1, #2]\n\
	ldr r3, [sp, #0x10]\n\
	adds r1, r3, r1\n\
	ldrb r0, [r1]\n\
	adds r0, #1\n\
	strb r0, [r1]\n\
	mov r0, r8\n\
	ldrb r1, [r0, #4]\n\
	add r1, sb\n\
	ldrb r0, [r1]\n\
	adds r0, #1\n\
	strb r0, [r1]\n\
	mov r1, r8\n\
	strb r2, [r1, #9]\n\
	movs r4, #0\n\
	mov r5, sb\n\
_08019B32:\n\
	mov r2, r8\n\
	ldrb r1, [r2, #9]\n\
	adds r1, r5, r1\n\
	lsls r0, r4, #0x10\n\
	asrs r3, r0, #0x10\n\
	adds r2, r5, r3\n\
	ldrb r0, [r1]\n\
	ldrb r2, [r2]\n\
	cmp r0, r2\n\
	bhs _08019B4A\n\
	mov r0, r8\n\
	strb r4, [r0, #9]\n\
_08019B4A:\n\
	adds r0, r3, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #9\n\
	ble _08019B32\n\
	mov r2, sp\n\
	ldr r3, [sp, #0x14]\n\
	ldrb r1, [r3]\n\
	mov r0, ip\n\
	ldrb r0, [r0]\n\
	adds r1, r1, r0\n\
	ldr r3, [sp, #0x18]\n\
	ldrb r0, [r3]\n\
	adds r0, r0, r1\n\
	ldr r1, [sp, #0x1c]\n\
	ldrb r1, [r1]\n\
	adds r0, r0, r1\n\
	strb r0, [r2]\n\
	ldr r3, [sp, #0x24]\n\
	ldrb r1, [r3]\n\
	ldr r0, [sp, #0x20]\n\
	ldrb r0, [r0]\n\
	adds r1, r1, r0\n\
	ldr r3, [sp, #0x28]\n\
	ldrb r0, [r3]\n\
	adds r0, r0, r1\n\
	strb r0, [r2, #1]\n\
	ldr r0, [sp, #0x30]\n\
	ldrb r1, [r0]\n\
	ldr r3, [sp, #0x2c]\n\
	ldrb r3, [r3]\n\
	adds r1, r1, r3\n\
	ldr r3, [sp, #0x34]\n\
	ldrb r0, [r3]\n\
	adds r0, r0, r1\n\
	strb r0, [r2, #2]\n\
	ldr r0, [sp, #0x3c]\n\
	ldrb r1, [r0]\n\
	ldr r3, [sp, #0x38]\n\
	ldrb r3, [r3]\n\
	adds r1, r1, r3\n\
	ldr r3, [sp, #0x40]\n\
	ldrb r0, [r3]\n\
	adds r0, r0, r1\n\
	strb r0, [r2, #3]\n\
	ldr r0, [sp, #0x48]\n\
	ldrb r1, [r0]\n\
	ldr r3, [sp, #0x44]\n\
	ldrb r3, [r3]\n\
	adds r1, r1, r3\n\
	ldr r3, [sp, #0x4c]\n\
	ldrb r0, [r3]\n\
	adds r0, r0, r1\n\
	strb r0, [r2, #4]\n\
	mov r1, sp\n\
	ldr r2, [sp, #0x10]\n\
	ldrb r0, [r2]\n\
	strb r0, [r1, #5]\n\
	movs r4, #0\n\
	ldr r2, [sp, #0x50]\n\
_08019BC4:\n\
	lsls r0, r4, #0x10\n\
	asrs r0, r0, #0x10\n\
	adds r1, r2, r0\n\
	strb r4, [r1]\n\
	adds r0, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #5\n\
	ble _08019BC4\n\
	movs r4, #0\n\
_08019BDA:\n\
	movs r3, #5\n\
	lsls r0, r4, #0x10\n\
	asrs r1, r0, #0x10\n\
	mov sl, r0\n\
	cmp r3, r1\n\
	ble _08019C1A\n\
	ldr r0, [sp, #0x50]\n\
	mov sb, r0\n\
	mov ip, r1\n\
	adds r7, r0, #0\n\
	add r7, ip\n\
_08019BF0:\n\
	ldrb r6, [r7]\n\
	mov r1, sp\n\
	adds r2, r1, r6\n\
	lsls r0, r3, #0x10\n\
	asrs r5, r0, #0x10\n\
	mov r3, sb\n\
	adds r4, r3, r5\n\
	ldrb r3, [r4]\n\
	adds r1, r1, r3\n\
	ldrb r0, [r2]\n\
	ldrb r1, [r1]\n\
	cmp r0, r1\n\
	bhs _08019C0E\n\
	strb r3, [r7]\n\
	strb r6, [r4]\n\
_08019C0E:\n\
	subs r0, r5, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r3, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, ip\n\
	bgt _08019BF0\n\
_08019C1A:\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	add r0, sl\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #4\n\
	ble _08019BDA\n\
	ldr r1, [sp, #0x50]\n\
	ldrb r0, [r1]\n\
	cmp r0, #0\n\
	bne _08019C64\n\
	mov r2, r8\n\
	strb r0, [r2, #9]\n\
	movs r0, #1\n\
	strb r0, [r2, #8]\n\
	movs r4, #0\n\
	ldr r5, _08019C60 @ =gCodeNameSuffixs\n\
	ldr r1, [sp, #0x10]\n\
_08019C3E:\n\
	lsls r0, r4, #0x10\n\
	asrs r3, r0, #0x10\n\
	adds r0, r3, r5\n\
	ldrb r2, [r0]\n\
	adds r0, r1, r2\n\
	ldrb r0, [r0]\n\
	cmp r0, #0\n\
	beq _08019C52\n\
	mov r0, r8\n\
	strb r2, [r0, #8]\n\
_08019C52:\n\
	adds r0, r3, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #7\n\
	ble _08019C3E\n\
	b _08019D0A\n\
	.align 2, 0\n\
_08019C60: .4byte gCodeNameSuffixs\n\
_08019C64:\n\
	ldr r1, _08019C80 @ =gScore\n\
	ldr r0, [r1]\n\
	ldrb r1, [r0, #7]\n\
	movs r0, #0xf0\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08019C84\n\
	movs r0, #0xa\n\
	mov r2, r8\n\
	strb r0, [r2, #9]\n\
	movs r0, #0x12\n\
	strb r0, [r2, #8]\n\
	b _08019D0A\n\
	.align 2, 0\n\
_08019C80: .4byte gScore\n\
_08019C84:\n\
	ldr r3, _08019CA0 @ =gScore\n\
	movs r1, #0x1b\n\
	ldrsb r1, [r3, r1]\n\
	movs r0, #0x1e\n\
	rsbs r0, r0, #0\n\
	cmp r1, r0\n\
	bge _08019CA4\n\
	movs r0, #0xb\n\
	mov r1, r8\n\
	strb r0, [r1, #9]\n\
	movs r0, #0x11\n\
	strb r0, [r1, #8]\n\
	b _08019D0A\n\
	.align 2, 0\n\
_08019CA0: .4byte gScore\n\
_08019CA4:\n\
	mov r2, r8\n\
	ldrb r1, [r2, #7]\n\
	movs r0, #0xf\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08019CBA\n\
	movs r0, #0xb\n\
	strb r0, [r2, #9]\n\
	movs r0, #0x13\n\
	strb r0, [r2, #8]\n\
	b _08019D0A\n\
_08019CBA:\n\
	mov r3, r8\n\
	ldrb r0, [r3, #6]\n\
	cmp r0, #0\n\
	beq _08019CCC\n\
	movs r0, #0xb\n\
	strb r0, [r3, #9]\n\
	movs r0, #0x12\n\
	strb r0, [r3, #8]\n\
	b _08019D0A\n\
_08019CCC:\n\
	ldr r1, [sp, #0x50]\n\
	ldrb r0, [r1]\n\
	lsls r0, r0, #3\n\
	ldr r2, _08019D1C @ =gCodeNameSuffixs\n\
	adds r0, r0, r2\n\
	ldrb r0, [r0]\n\
	mov r3, r8\n\
	strb r0, [r3, #8]\n\
	movs r4, #0\n\
	adds r6, r2, #0\n\
	ldr r5, [sp, #0x50]\n\
	ldr r1, [sp, #0x10]\n\
_08019CE4:\n\
	lsls r0, r4, #0x10\n\
	asrs r3, r0, #0x10\n\
	ldrb r0, [r5]\n\
	lsls r0, r0, #3\n\
	adds r0, r3, r0\n\
	adds r0, r0, r6\n\
	ldrb r2, [r0]\n\
	adds r0, r1, r2\n\
	ldrb r0, [r0]\n\
	cmp r0, #0\n\
	beq _08019CFE\n\
	mov r0, r8\n\
	strb r2, [r0, #8]\n\
_08019CFE:\n\
	adds r0, r3, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #7\n\
	ble _08019CE4\n\
_08019D0A:\n\
	add sp, #0x54\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08019D1C: .4byte gCodeNameSuffixs\n\
 .syntax divided\n");
}
