#ifndef GUARD_RMZ3_OW_LAYER_GFX_H
#define GUARD_RMZ3_OW_LAYER_GFX_H

#include "chunk.h"
#include "metatile.h"

// 地形レイヤのMetatileのマップデータ (ステージ全体分)
//   MetatileMap[0]:            ステージ全体の横幅(メタタイル単位)
//   MetatileMap[1]:            使われてない(Alignment?)
//   MetatileMap[2..89099]:     ステージ全体のメタタイルIDのマップデータ (89100個分, つまり横幅*縦幅分) = (metatile_id_t map[89100/width16][width16])
//   MetatileMap[89100..89101]: 使われてない(CpuFastSet のために32バイトアラインメントされる必要があるためそのパディング？)
//
// MetatileMap[2..89099] のメタタイルID のレイアウト
// 以降、 &MetatileMap[2] を map と呼ぶことにする e.g. map[N] = MetatileMap[2+N]
// 例えば、ステージが 横10チャンク、縦5チャンクだとするとステージを構成するチャンクは
//
//   chunk0   chunk1   chunk2   chunk3   chunk4   chunk5   chunk6   chunk7   chunk8   chunk9
//   chunk10  chunk11  chunk12  chunk13  chunk14  chunk15  chunk16  chunk17  chunk18  chunk19
//   chunk20  chunk21  chunk22  chunk23  chunk24  chunk25  chunk26  chunk27  chunk28  chunk29
//   ...
//   chunk40  chunk41  chunk42  chunk43  chunk44  chunk45  chunk46  chunk47  chunk48  chunk49
//
//
//   chunk0:                                         chunk1:                                  ...  chunk9:
//     map[0]     map[1]     map[2]   ...   map[14]    map[15]  map[16]  map[17] ... map[29]  ...    map[135] ... map[149]
//     map[150]   map[151]   map[152] ...   map[164]   map[165] ...
//     ...
//     map[1350]  map[1351] ...             map[1364]  map[1365] ...
//   chunk10:
//     map[1500]  map[1501] ...
//    ...
//
// 例えば、 chunk14 は chunkX: 4, chunkY: 1 なので、chunk14の左上のメタタイルIDは map[1500 + (4*15)] = map[1560] にある, CHUNK_OFFSET はこれを計算するためのマクロで、 この場合は CHUNK_OFFSET(10, 4, 1) = (1500 + (4*15)) になる
// また、   chunk14 の メタタイル座標 (2, 3) (ピクセルだと 画面左上から 16px, 24px) の部分のメタタイルID は map[(1500 + (4*15)) + (3 * 150) + 2] = map[2012] にある
typedef u16 MetatileMap[2 + 89100 + 2];

#define CHUNK_OFFSET(chunkW, chunkX, chunkY) ((((chunkW) * 15) * (chunkY) * 10) + ((chunkX) * 15))
#define TILEMAP_OFFSET(metatileW, metatileX, metatileY) (((metatileW) * (metatileY)) + (metatileX))

// StageLayer構造体のうち、BGマップへの描画に必要な情報
struct LayerGraphic {
  PixelCoords c;  // 最後に描画したときの画面左上のワールド座標(ピクセル単位), 新しい座標と比較して、描画内容を更新すべきかの判定に使われる(毎回描画し直すのは重いので)
  u16 bgofs[2];   // BGHOFS と BGVOFS にセットされる値 (0-511), 常に (.c.x & 0x1FF), (.c.y & 0x1FF) になる?
  // 以下のポインタは 全部ROMのアドレスを指す読み取り専用のもの
  Metatile* tiledata;          // 02002240, 020022c8, e.g. 086f9fec, メタタイルID を GBAのタイルマップx4 への変換テーブル (4bppデータとかではない)
  Chunk* chunks;               // chunks[ChankID] -> 15x10のメタタイルIDの配列
  const struct ChunkMap* map;  // このステージレイヤ　のチャンクマップ (ステージ全体分)
};  // 24 bytes
static_assert(sizeof(struct LayerGraphic) == 24);

struct BgOfs;
void UpdateBGOFS(struct LayerGraphic* p, struct BgOfs* bgofs);

void FUN_080050b0(struct LayerGraphic* l, PixelCoords* c, void* dst);
void FUN_08005a70(struct LayerGraphic* l, PixelCoords* c, void* dst);

void FUN_08006bb4(struct LayerGraphic* l, PixelCoords* c, u32* dst, u16* src);
void FUN_08006a10(struct LayerGraphic* l, PixelCoords* c, u32* dst, u16* src);
void FUN_08006ae0(struct LayerGraphic* l, PixelCoords* c, u32* dst, u16* src);

void ResetLayerGraphic(struct LayerGraphic* p, PixelCoords* c, void* dst UNUSED, Metatile* tiledata, Chunk* chunks, const struct ChunkMap* map);

#endif  // GUARD_RMZ3_OW_LAYER_GFX_H
