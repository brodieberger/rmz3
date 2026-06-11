#ifndef GUARD_RMZ3_CONST_METATILE_H
#define GUARD_RMZ3_CONST_METATILE_H

// metatile_attr_t (Metatileの属性)

// metatile_attr_t & 0xF, 16x16の地形の形状を表す (0..15), コメントの上り坂, 下り坂 は 左から右へ進むと考えた時のもの
#define SHAPE_EMPTY 0  // 何もない
#define SHAPE_BLOCK 1  // 全部地形(◼)

// ◢ θ=30° くらい の上り坂 (SHAPE_SLOPE2, SHAPE_SLOPE3 と繋げて1マス分の高さの上り坂になる)
#define SHAPE_SLOPE2 2  // θ=30° くらい の上り坂1(◢)
#define SHAPE_SLOPE3 3  // θ=30° くらい の上り坂2(◢)

// ◢ θ=15° くらい の上り坂 (左から SHAPE_SLOPE4, SHAPE_SLOPE5, SHAPE_SLOPE6, SHAPE_SLOPE7 と繋げて1マス分の高さの上り坂になる)
#define SHAPE_SLOPE4 4  // θ=15° くらい の上り坂1(◢)
#define SHAPE_SLOPE5 5  // θ=15° くらい の上り坂2(◢)
#define SHAPE_SLOPE6 6  // θ=15° くらい の上り坂3(◢)
#define SHAPE_SLOPE7 7  // θ=15° くらい の上り坂4(◢)

// ◢ θ=30° くらい の下り坂 (SHAPE_SLOPE8, SHAPE_SLOPE9 と繋げて1マス分の高さの下り坂になる)
#define SHAPE_SLOPE8 8  // θ=30° くらい の下り坂1(◣), SHAPE_SLOPE3 を xflip したものと同じ形
#define SHAPE_SLOPE9 9  // θ=30° くらい の下り坂2(◣), SHAPE_SLOPE2 を xflip したものと同じ形

#define SHAPE_SLOPE10 10  // θ=15° くらい の下り坂1(◣), SHAPE_SLOPE7 を xflip したものと同じ形
#define SHAPE_SLOPE11 11  // θ=15° くらい の下り坂2(◣), SHAPE_SLOPE6 を xflip したものと同じ形
#define SHAPE_SLOPE12 12  // θ=15° くらい の下り坂3(◣), SHAPE_SLOPE5 を xflip したものと同じ形
#define SHAPE_SLOPE13 13  // θ=15° くらい の下り坂4(◣), SHAPE_SLOPE4 を xflip したものと同じ形

#define SHAPE_14 14  // はじごの上の床はこの形状になっている(アナトレーの森の枝(すりぬけ床)はこの形状ではない)
#define SHAPE_15 15  // はしごのメタタイルはこの形状になっている

// ----------------------------------------------------------------------------------------

#define MTATTR_SPIKE (1 << 4)     // 0x10, 即死(トゲ、マグマ)
#define MTATTR_ICEBLOCK (1 << 5)  // 0x20, 壊れた宇宙船の氷ブロックに付与
#define MTATTR_B9 (1 << 9)        // 0x200, ???
#define MTATTR_ANTTRAP (1 << 10)  // 0x400, 徐々に沈む床(兵器再生工場のスクラップ、 夕闇の砂漠の砂地獄)
#define MTATTR_B11 (1 << 11)      // 0x800, ???
#define MTATTR_SLIP (1 << 12)     // 0x1000, 滑る(氷の前線基地の凍ったパイプ)

// X方向に動くコンベア(兵器再生工場のコンベア、夕闇の砂漠の流砂)
#define MTATTR_CONVEYOR1 (1 << 13)  // 0x2000, Terrain.conveyor[1] の速度で動く (ほとんどの場合、右に動く)
#define MTATTR_CONVEYOR0 (1 << 14)  // 0x4000, Terrain.conveyor[0] の速度で動く (ほとんどの場合、左に動く)

#define MTATTR_SOFT_PLATFORM (1 << 15)  // 0x8000, すり抜け床(アナトレーの森の枝、はしごの上の床など)

// ----------------------------------------------------------------------------------------

#define MT_LADDER (MTATTR_SOFT_PLATFORM | SHAPE_15)        // はしご
#define MT_LADDER_FLOOR (MTATTR_SOFT_PLATFORM | SHAPE_14)  // はしご床 (=はしごの上端)

#endif  // GUARD_RMZ3_CONST_METATILE_H
