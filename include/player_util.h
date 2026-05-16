#ifndef __INCLUDE_PLAYER_UTIL_H__
#define __INCLUDE_PLAYER_UTIL_H__

// unk_b4 に名前をつける時に、いちいち unk_b4 にアクセスするコードを変更するのが面倒なので、一旦マクロでアクセスする

#define P_B4(player) (((Player*)player)->unk_b4)
#define P_ELEMENT(player) (((&P_B4(player))->status).element)

#define attackState8 attackState.u8

// SET_XFLIP と処理は同じだけど、こっちじゃないとコンパイル結果が一致しないときがある
#define SET_PLAYER_XFLIP(enti, value)                              \
  {                                                                \
    bool8 __xflip__;                                               \
    (((struct Entity*)enti)->spr).xflip = (value) & 1;             \
    __xflip__ = (((struct Entity*)enti)->spr).oam.xflip = (value); \
    if (__xflip__) {                                               \
      ((struct Entity*)enti)->flags |= X_FLIP;                     \
    } else {                                                       \
      ((struct Entity*)enti)->flags &= ~X_FLIP;                    \
    }                                                              \
  }

#endif  // __INCLUDE_PLAYER_UTIL_H__
