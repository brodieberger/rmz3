#ifndef GUARD_RMZ3_STAGE_SCRIPT_H
#define GUARD_RMZ3_STAGE_SCRIPT_H

#include "camera.h"
#include "common.h"
#include "gba/types.h"

#define SCRIPT_ENTITY_COUNT 12

// vm.transition
#define TRANSITION_NONE 0
#define TRANSITION_REVERSE (1 << 0)
#define TRANSITION_BLACKOUT (1 << 1)
#define TRANSITION_WHITEOUT (1 << 2)
#define TRANSITION_Z (1 << 3)  // wipe by Z

// vm.emergency
#define EMERGENCY_TEMPORARY (1 << 14)
#define EMERGENCY_ENABLED (1 << 15)

struct Entity;
struct VFX;

/**
 * @brief Script Command
 * @see gScriptCommands
 */
struct Command {
  u8 cmd;     // 0x0, コマンドID (e.g. spawn => 11)
  u8 status;  // 0x1
  s16 val2;   // 0x2
  u32 work;   // 0x4, コマンドハンドラ用の汎用データ コマンドによって用途が異なる
};  // 8 bytes

struct ScriptEntity {
  struct Entity* entity;
  struct Entity* unk_04;
  u8 unk_08;
  u8 flags;  // Actorによって各bitの意味が異なる
  u16 unk_0A[3];
};

// フィールドスクリプト実行VM
struct VM {
  u8 unk_000;
  u8 unk_001;
  bool8 active;
  u8 unk_003;
  u16 unk_004;
  u16 unk_006;
  struct Command* start;  // コマンド列の開始地点
  struct Command* pc;     // コマンド列の現在地点
  struct ScriptEntity entities[SCRIPT_ENTITY_COUNT];
  u32 time;              // Frame count from ClearVM
  u32 wait;              // waitコマンドで設定する待機時間
  struct Camera camera;  // 0xD8
  u32 transition;        // bit0..15: transition flags, bit16..31: transition parameter
  KEY_INPUT forcedKey;
  u16 unk_14a;
  u16 emergency;  // 緊急事態に画面が赤くなるエフェクト (bit0..7: intensity, bit8..13: unused?, bit14: temporary, bit15: enabled)
  u16 magnitude;  // 0xFFにするほど揺れが強い
  union {
    u32 raw;
    s16 n;  // strings.s
    u8 x;
    u8 y;
  } string;               // ((string_id << 16) | (y << 8) | x)
  struct VFX* indicator;  // ステージへオペレータに転送されたとき(もしくはミッション開始時に)右下に出てくる "Z x 9" や `MISSION START`などのオーバーレイ
  SoundID32 bgm;
  TextID zeroDeathTextIDs[2];  // ゼロがボス戦で死んだ時にボスが喋るメッセージのテキストID配列
  struct Coord forceCoord;     // 0xFFFFFFFF以外に設定するとそこにゼロが瞬間移動 & 座標固定される(侵入可能エリアなら死)
};  // 360 bytes

// ------------------------------------------------------------------------------------------------------------------------------------

typedef bool32 (*CommandHandler)(struct VM*);

extern const CommandHandler gScriptCommands[38];

void SetScript(struct VM* vm, const struct Command* script);
bool32 RunVM(struct VM* vm);
void ClearVM(struct VM* vm, u32 stageID);
void FUN_08021cb4(struct VM* vm, const struct Command* script, struct Entity* e);
void DeleteScriptEntity(u8 n);

#endif  // GUARD_RMZ3_STAGE_SCRIPT_H
