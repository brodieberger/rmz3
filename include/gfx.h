#ifndef GUARD_RMZ3_GFX_H
#define GUARD_RMZ3_GFX_H

#include "anim_loader.h"
#include "constants/constants.h"
#include "gba/gba.h"
#include "gpu_regs.h"

#define COLOR 2

// Graphic.props
#define MAP2D (1 << 0)
#define LZ77 0x0002
#define NO_PAL 0x0004
#define BPP4 0x0020
#define RLU (1 << (4 + 8))

#define PALETTE16(n) (*(u16*)(&gPaletteManager.buf[0]))

// おそらく、アセンブリで定義されたテーブルを変にCで定義してしまったせいで、アクセスする処理のコンパイル結果が変わってしまっていると思われる
#if MODERN
#define BGMAP(n) (SELF_REL_PTR(&gBgMapOffsets[n]) + sizeof(struct BgMapHeader))
#define TILESETS(id, ofs) (&((struct ColorGraphic*)SELF_REL_PTR(&gStageTilesetOffsets[id]))[ofs])
#define BG_GRAPHIC(n) ((void*)&((struct ColorGraphic*)&gGraphic_Capcom)[(n)])
#define BG_PALETTE(n) ((const struct Palette*)&(((struct ColorGraphic*)&gGraphic_Capcom)[(n)].pal))
#else
#define BGMAP(n) ((void*)(*((u32*)(0x085222a0 + (n * 4))) + (0x085222a0 + (n * 4) + sizeof(struct BgMapHeader))))
#define TILESETS(id, ofs) ((struct ColorGraphic*)(*((u32*)(0x087044b0 + (id * 4))) + (0x087044b0 + (id * 4)) + (ofs * 20)))
#define BG_GRAPHIC(n) ((void*)((const struct Graphic*)((void*)(0x08547280) + ((n) * (sizeof(struct ColorGraphic))))))
#define BG_PALETTE(n) ((const struct Palette*)((void*)(0x0854728C) + ((n) * (sizeof(struct ColorGraphic)))))
#endif

/**
 * @brief 0x080036cc の関数で src -> dst に転送が行われる (Transfer gfx data from src to dest by 0x080036cc)
 * @details
 *  Graphic構造体、Bgmapなどさまざまなグラフィックデータを転送する (gfx data is Graphic struct, Bgmap, etc...)
 */
struct GraphicTransfer {
  u32 type : 2;  // 0: struct Graphic, 1: BG map, 2: ???(0x08003a08), 3: ???
  u32 bytesize : 30;
  void* dst;
  void* src;
};

// 0x02001f00
struct GraphicTransferManager {
  s32 len;  // .tasks のうち、有効なタスク数(.tasks length)
  struct GraphicTransfer tasks[16];

  struct BG0Manager {
    u32 bytesize;  // buffer のサイズ
    void* buffer;  // BGマップのバッファ
    u32 dst;       // buffer の転送先
    u32 backdrop;  // BG0に何も描画されないときのデフォルトカラー
  } bg0;           // 0x02001fc4
};

// 0x03002ac0
struct PaletteManager {
  struct PlttData buf[512];
  u8 filter[3];  // Fadeレベル (0x0: 真っ黒, 0x20: フェードなし, 0x40: 真っ白), [0] = Red, [1] = Green, [2] = Blue
  u16 unk_404;
  u16 unk_406;
  void (*post_process)(void);  // 最終的なパレットに対して、適用される関数, このゲームでは、サイバー空間 で画面を緑っぽくする用途でのみ使われている
};  // 1036 bytes

// 0x03002ed0
struct OamManager {
  struct OamData buf[128];
  struct OamData* p;
  u32 dispcnt;
};  // 1032 bytes

struct GraphicV2 {
  u32 src;          // 0x0: SELF_REL_PTR(&src)
  u32 size : 22;    // unit is byte.
  u32 tileId : 10;  // dst tile id in VRAM
  u16 rowsize;      // 0x8: If graphic is linear(1D), this value is unused. (LZ77 のときは違う用途っぽい)
  // 0xA, attributes
  u16 map2d : 1;     // bit0, VRAMにタイルデータを配置する時のレイアウト, 0: linear(1D), 1: non-linear(2D)
  u16 lz77 : 1;      // bit1, LZ77 compressed?
  u16 no_pal : 1;    // bit2, Graphic構造体の後ろに、使わないがPalette構造体があることを示すフラグ (ColorGraphic[] として扱いたいときのPadding), プログラム上では使われてなくて、あくまで開発者にわかりやすくするためのものと思われる?
  u16 tilesize : 8;  // bit3..10: (g->tilesize << 3) がこのグラフィックを構成するタイル1枚あたりのバイト数 (様々な bpp を想定していた?)
  u16 prop_b11 : 1;  // bit11: ???
  u16 rlu : 1;       // bit12, RLU compressed
  u16 prop_b13 : 3;  // bit13..15: ???
};

// グラフィックデータ(タイルデータ)の情報を持った構造体(ヘッダみたいなもの)
// GraphicV2 と同じ意味だけど、 LoadGraphic のコンパイル結果が GraphicV2 でないと一致しないため、GraphicV2 で全部置き換えた後に、この構造体は削除する予定
struct Graphic {
  s32 src;        // tile data starts from `(u8 *)&src + src`
  u32 size : 22;  // unit is byte.
  u32 ofs : 10;   // 転送先のVRAMのタイルID
  u16 chunkSize;  // If graphic is linear(1D), this value is unused.

  // bit0:     is 2d layout
  // bit1:     is LZ77 compressed?
  // bit2:     no_pal: Graphic構造体の後ろに、使わないがPalette構造体があることを示すフラグ (ColorGraphic[] として扱いたいときのPadding)
  //           プログラム上では使われてなくて、あくまで開発者にわかりやすくするためのものと思われる?
  // bit3..10: = props & (0xFF << 3) = ???
  //  bit5:     is 4BPP?
  //  bit6:     is 8BPP?
  // bit12:    is RLU compressed?
  // props & 0x7F8 is ofsUnit (4BPP: 32, 8BPP: 64)
  u16 props;
};

// パレットの情報を持った構造体(ヘッダみたいなもの)
struct Palette {
  u32 src;     // palette data starts from `(void *)&src + src`
  u16 size;    // unit is byte
  bool8 lz77;  // lz77 compressed?
  u8 dst;      // PaletteID (0..15)
};

struct ColorGraphic {
  struct Graphic g;
  struct Palette pal;
};

struct ColorGraphicV2 {
  struct GraphicV2 g;
  struct Palette pal;
};

// --------------------------------------------

/*
  0x02001f00
  グラフィックデータを転送するタスクデータが入っている
  毎フレーム、ここに入っているタスクが 関数 0x080036cc で実行されグラフィックデータが転送される
*/
extern struct GraphicTransferManager gGraphicTransferManager;
extern struct PaletteManager gPaletteManager;
extern struct OamManager gOamManager;

// 085d78f8 からの Graphic のpal.dstが入っている (08017aa8 参照)
extern u16 wStaticMotionPalIDs[STATIC_MOTION_COUNT + 2];

// 085d78f8 からの Graphic が配置される最初のタイル番号が入っている (08017aa8 参照)
extern u16 wStaticGraphicTilenums[STATIC_MOTION_COUNT + 2];

extern const struct ColorGraphic gStaticMotionGraphics[STATIC_MOTION_COUNT];

extern const struct Graphic gGraphic_Capcom;
extern const struct Palette gPalette_Capcom;

extern const u32 gBgMapOffsets[134];

extern const u32 gStageTilesetOffsets[19];
extern const struct ColorGraphic gMiscTilesetGraphics[177];

// --------------------------------------------

void LoadGraphic(const struct GraphicV2* g, void* dst);
void LoadPalette(const struct Palette* p, u32 r1);
s32 RequestGraphicTransfer(const struct Graphic* g, void* dst);
s32 RequestBgMapTransfer(u16* src, void* dst, s32 bytesize);
void EnableBG0(u32* buffer, u32 dst, u32 bytesize, u16 backdrop);
void DisableBG0(void);

#endif  // GUARD_RMZ3_GFX_H
