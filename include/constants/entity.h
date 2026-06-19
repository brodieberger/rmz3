#ifndef GUARD_RMZ3_CONST_ENTITY_H
#define GUARD_RMZ3_CONST_ENTITY_H

// --------------------------------------------
// Entity.kind ( GameState.entityHeaders の idx でもある)
// --------------------------------------------
#define ENTITY_PLAYER 0
#define ENTITY_WEAPON 1
#define ENTITY_BOSS 2
#define ENTITY_ENEMY 3
#define ENTITY_PROJECTILE 4
#define ENTITY_VFX 5
#define ENTITY_SOLID 6
#define ENTITY_ITEM 7
#define ENTITY_ELF 8
#define ENTITY_WIDGET 9

// --------------------------------------------
// Entity.flags
// --------------------------------------------

#define DISPLAY (1 << 0)
#define FLIPABLE (1 << 1)
#define COLLIDABLE (1 << 2)  // Hitboxを持つ Entity かどうか

// Entity の描画を　汎用のスプライトレンダラに任せるかどうかのフラグ
// このフラグを立てない場合は、描画処理を自前で実装して SetTaskCallback する必要がある
// NOTE: もっと短くてわかりやすい名前にしたい (あまり参照されるフラグでないので、このままでいいとは思うけど)
#define USE_COMMON_OAM_RENDERER (1 << 3)

#define X_FLIP (1 << 4)
#define Y_FLIP (1 << 5)
#define AFFINE (1 << 6)
#define SCRIPTED (1 << 7)  // ScriptedEntity か (= asm/scripts/ のスクリプトの spawnコマンド で生成された Entity かどうか)

// --------------------------------------------
// Entity.flags2
// --------------------------------------------

#define SCALEROT (1 << 0)
#define ENTITY_FLAG2_B1 (1 << 1)  // 意味のないフラグに見える(どちらにしろScalerotSpriteするので)
#define DYNAMIC (1 << 2)          // スプライトアニメーションに使うテーブル (0: Staticテーブル(SMxxx_), 1: Dynamicテーブル (DMxxx_))
#define ENTI_PHYSICS (1 << 3)     // 物理的判定を持つ Entity かどうか (コンテナや旧居住区の燃やせる木、動く足場など)
#define WHITE_PAINTABLE (1 << 4)  // (if damaged) white painted by RunDamageEffect
#define PALETTE_FORCED (1 << 5)
#define ENTITY_FLAGS2_B6 (1 << 6)
#define STOPPED (1 << 7)

// --------------------------------------------
// Entity.id
// --------------------------------------------

#include "constants/entity/boss.h"
#include "constants/entity/enemy.h"
#include "constants/entity/item.h"
#include "constants/entity/player.h"
#include "constants/entity/projectile.h"
#include "constants/entity/solid.h"
#include "constants/entity/vfx.h"
#include "constants/entity/weapon.h"

#endif  // GUARD_RMZ3_CONST_ENTITY_H
