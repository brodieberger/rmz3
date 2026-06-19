#include "gfx.h"
#include "global.h"

IWRAM_DATA ALIGNED(16) struct PaletteManager gPaletteManager = {};

void InitPaletteManager(void) {
  DmaFill32(3, 0, &gPaletteManager, PLTT_SIZE);
  DmaCopy32(3, &gPaletteManager, PLTT, PLTT_SIZE);
  gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = FILTER_NONE;
  gPaletteManager.unk_406 = 0;
  gPaletteManager.post_process = NULL;
}

static void FadeBlack(u32* src, u32* dst, u32 lv, u32* mask);
static void FadeWhite(u32* src, u32* dst, u32* fades, u32* mask);
static void FadeColor(u32* src, u32* dst, u32* fades, u32* mask);

// 0x08003b24
void FlushPalette(void) {
  u32 mask[3];
  u32 fadeval[6];  // [R1, G1, B1, R2, G2, B2]
  struct PaletteManager* pman = &gPaletteManager;

  // mask for ((RGB555 << 16) | RGB555)
  mask[0] = (0x1F << 16) | 0x1F;                  // Red
  mask[1] = ((0x1F << 5) << 16) | (0x1F << 5);    // Green
  mask[2] = ((0x1F << 10) << 16) | (0x1F << 10);  // Blue

  if (pman->filter[0] == pman->filter[1]) {  // R と G のFadeレベルが同じなら、単一フェードとして扱う
    if (pman->filter[0] == 0x20) {
      DmaCopy32(3, pman->buf, PLTT, PLTT_SIZE);
    } else if (pman->filter[0] < 0x20) {
      FadeBlack((u32*)pman->buf, (u32*)PLTT, pman->filter[0], mask);
    } else {
      fadeval[0] = 0x40 - pman->filter[0];
      fadeval[1] = (pman->filter[0] - 0x21) | ((pman->filter[0] - 0x21) << 16);
      FadeWhite((u32*)pman->buf, (u32*)PLTT, fadeval, mask);
    }
  } else {
    if (pman->filter[0] < 0x21) {
      fadeval[0] = pman->filter[0];
      fadeval[3] = 0;
    } else {
      fadeval[0] = 0x40 - pman->filter[0];
      fadeval[3] = (pman->filter[0] - 0x21) | ((pman->filter[0] - 0x21) << 16);
    }

    if (pman->filter[1] < 0x21) {
      fadeval[1] = pman->filter[1];
      fadeval[4] = 0;
    } else {
      fadeval[1] = 0x40 - pman->filter[1];
      fadeval[4] = (pman->filter[1] - 0x21) | ((pman->filter[1] - 0x21) << 16);
    }

    if (pman->filter[2] < 0x21) {
      fadeval[2] = pman->filter[2];
      fadeval[5] = 0;
    } else {
      fadeval[2] = 0x40 - pman->filter[2];
      fadeval[5] = (pman->filter[2] - 0x21) | ((pman->filter[2] - 0x21) << 16);
    }
    FadeColor((u32*)gPaletteManager.buf, (u32*)PLTT, fadeval, mask);
  }

  {
    struct PaletteManager* pman = &gPaletteManager;
    if (pman->unk_406 != 0) {
      DmaFill16(3, 0xFFFF, PLTT + pman->unk_404, pman->unk_406);
      pman->unk_406 = 0;
    }
    if (pman->post_process != NULL) {
      pman->post_process();
    }
  }
}

/**
 * @fn void LoadPalette(struct Palette* p, u32 r1)
 * @brief Palette構造体の示すパレットを gPaletteManager.buf に転送する
 * @note 0x08003c98
 */
void LoadPalette(const struct Palette* p, u32 ofs) {
  if (p->size != 0) {
    ofs += (p->dst << 5);
    if (p->lz77) {
      LZ77UnCompWram(SELF_REL_PTR(&p->src), (u8*)&gPaletteManager.buf + ofs);
    } else {
      DmaCopy32(3, SELF_REL_PTR(&p->src), (u8*)&gPaletteManager.buf + ofs, p->size);
    }
  }
}

/**
 * @note 0x08003cf0
 */
WIP static void FadeBlack(u32* src, u32* dst, u32 lv, u32* mask) {
#ifdef ALWAYS_FALSE
  // 画面が黄色くなるので、コードがおかしい
  s32 i;
  for (i = 0; i < 256; i++) {
    u32 c = *src;
    u32 r = (((c & mask[0]) * lv) >> 5) & mask[0];
    u32 g = (((c & mask[1]) * lv) >> 5) & mask[1];
    u32 b = (((c & mask[2]) * lv) >> 5) & mask[2];
    *dst = r | g | b;
    src++;
    dst++;
  }
#else
  INCCODE("asm/wip/FadeBlack.inc");
#endif
}

NAKED static void FadeWhite(u32* src, u32* dst, u32* fades, u32* mask) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7}\n\
	ldr r4, [r2]\n\
	movs r7, #0xff\n\
_08003D3A:\n\
	push {r0, r1, r7}\n\
	ldr r1, [r0]\n\
	ldr r5, [r2, #4]\n\
	ldr r0, [r3]\n\
	ands r0, r1\n\
	muls r0, r4, r0\n\
	lsrs r0, r0, #5\n\
	adds r0, r0, r5\n\
	ldr r6, [r3]\n\
	ands r6, r0\n\
	lsls r5, r5, #5\n\
	ldr r0, [r3, #4]\n\
	ands r0, r1\n\
	muls r0, r4, r0\n\
	lsrs r0, r0, #5\n\
	adds r0, r0, r5\n\
	ldr r7, [r3, #4]\n\
	ands r7, r0\n\
	orrs r6, r7\n\
	lsls r5, r5, #5\n\
	ldr r0, [r3, #8]\n\
	ands r0, r1\n\
	lsrs r0, r0, #5\n\
	muls r0, r4, r0\n\
	ldr r7, [r3, #8]\n\
	adds r0, r0, r5\n\
	ands r7, r0\n\
	orrs r6, r7\n\
	pop {r0, r1, r7}\n\
	str r6, [r1]\n\
	adds r0, #4\n\
	adds r1, #4\n\
	subs r7, #1\n\
	bpl _08003D3A\n\
	pop {r4, r5, r6, r7}\n\
	bx lr\n\
	.align 2, 0\n\
 .syntax divided\n");
}

// 0x08003d84
NAKED static void FadeColor(u32* src, u32* dst, u32* fades, u32* mask) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7}\n\
	movs r7, #0xff\n\
_08003D88:\n\
	push {r0, r1, r7}\n\
	ldr r1, [r0]\n\
	ldr r4, [r2]\n\
	ldr r5, [r2, #0xc]\n\
	ldr r0, [r3]\n\
	ands r0, r1\n\
	muls r0, r4, r0\n\
	lsrs r0, r0, #5\n\
	adds r0, r0, r5\n\
	ldr r6, [r3]\n\
	ands r6, r0\n\
	ldr r4, [r2, #4]\n\
	ldr r5, [r2, #0x10]\n\
	ldr r0, [r3, #4]\n\
	ands r0, r1\n\
	muls r0, r4, r0\n\
	lsrs r0, r0, #5\n\
	adds r0, r0, r5\n\
	ldr r7, [r3, #4]\n\
	ands r7, r0\n\
	orrs r6, r7\n\
	ldr r4, [r2, #8]\n\
	ldr r5, [r2, #0x14]\n\
	ldr r0, [r3, #8]\n\
	ands r0, r1\n\
	lsrs r0, r0, #5\n\
	muls r0, r4, r0\n\
	ldr r7, [r3, #8]\n\
	adds r0, r0, r5\n\
	ands r7, r0\n\
	orrs r6, r7\n\
	pop {r0, r1, r7}\n\
	str r6, [r1]\n\
	adds r0, #4\n\
	adds r1, #4\n\
	subs r7, #1\n\
	bpl _08003D88\n\
	pop {r4, r5, r6, r7}\n\
	bx lr\n\
	.align 2, 0\n\
	 .syntax divided\n");
}
