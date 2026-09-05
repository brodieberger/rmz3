#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "renderer.h"

// リンクされる場所的に カプコン か インティクリエイツ で使いまわしてるライブラリの可能性がある (= ビルドフラグとか色々違う可能性がある)

extern const u8* const sSpriteSize[2];
extern const u8 sSpriteWidth[12];
extern const u8 sSpriteHeight[12];
extern const u8* const sAffineSpriteSize[2];

// The asm builds attr0|attr1 as one word. Writing bitfields one at a time into a reused
// buffer entry leaves attr1 bits 8..11 holding the previous frame's value. attr3 is not written.
struct OamRaw {
  u32 attr01;
  u16 attr2;
  u16 attr3;
};

// low byte of s->oam attr3: unused:4, xflip:1, yflip:1, size:2
#define OAM_FLIPBYTE(src) ((u32)((src)->attr3 & 0xFF) << 24)
// Subsprite bits 10..13 (xflip, yflip, size) land in attr1 bits 12..15
#define SRC(s) ((const struct OamRaw*)&(s)->oam)
#define SS_RAW(ss) (*(const u16*)(ss))
#define SS_FLIPSIZE(ss) ((u32)(SS_RAW(ss) >> 10) << 28)
#define SS_SIZESHAPE(ss) (SS_RAW(ss) >> 12)

NON_MATCH void TaskCB_DrawNoAffineSprite(struct Sprite* s, struct DrawPivot* tc) {
#if MODERN || CBODY
  Coords32* c = s->c;
  struct MetaspriteHeader* h = &s->sprites[s->spriteIdx];
  struct Subsprite* ss = (struct Subsprite*)(PTR_U32(&(s->sprites)->ofs) + h->ofs);
  s32 len = h->subspriteCount;
  struct OamRaw* oam = (struct OamRaw*)gOamManager.p;
  if ((s32)oam < (s32)(PTR_U32(&gOamManager.p) - (len * sizeof(struct OamData)))) {
    for (; len != 0; len--) {
      s32 Y = (c->y - (tc->lefttop).y) >> 8;
      if (s->yflip) {
        Y = (Y - ss->y) - sSpriteHeight[SS_SIZESHAPE(ss)];
      } else {
        Y = (Y + ss->y);
      }
      if ((u32)(Y + 64) < DISPLAY_HEIGHT + 64) {
        s32 X = (c->x - (tc->lefttop).x) >> 8;
        if (s->xflip) {
          X = (X - ss->x) - sSpriteWidth[SS_SIZESHAPE(ss)];
        } else {
          X = (X + ss->x);
        }
        if ((u32)(X + 128) < DISPLAY_WIDTH + 6 + 128) {
          oam->attr01 = (SRC(s)->attr01 | (u32)(Y & 0xFF) | ((u32)(X & 0x1FF) << 16) | SS_FLIPSIZE(ss) |
                         ((u32)(SS_RAW(ss) >> 14) << 14)) ^
                        OAM_FLIPBYTE(SRC(s));
          oam->attr2 = SRC(s)->attr2 + ss->tileNum;

          oam = &oam[1];
        }
      }
      ss = &ss[1];
    }
    gOamManager.p = (struct OamData*)oam;
  }
#else
  INCCODE("asm/wip/TaskCB_DrawNoAffineSprite.inc");
#endif
}

NON_MATCH void TaskCB_DrawRotatableSprite(struct Sprite* s, struct DrawPivot* tc) {
#if MODERN || CBODY
  Coords32* c = s->c;
  struct MetaspriteHeader* h = &s->sprites[s->spriteIdx];
  struct Subsprite* ss = (struct Subsprite*)(PTR_U32(&(s->sprites)->ofs) + h->ofs);
  s32 len = h->subspriteCount;
  struct OamRaw* oam = (struct OamRaw*)gOamManager.p;
  if ((s32)oam < (s32)(PTR_U32(&gOamManager.p) - (len * sizeof(struct OamData)))) {
    u8 angle = s->angle;
    s16 sin, cos;
    if (s->xflip != s->yflip) {
      angle = -angle;
    }

    sin = SIN(angle);
    cos = COS(angle);

    for (; len != 0; len--) {
      s32 X, Y;

      const u32 shape = SS_SIZESHAPE(ss);
      const s32 W = sAffineSpriteSize[0][shape];
      const s32 H = sAffineSpriteSize[1][shape];

      s32 x = sin * (ss->x + W);
      s32 y;
      if (s->xflip) {
        x = -x;
      }
      y = cos * (ss->y + H);
      if (s->yflip) {
        y = -y;
      }
      Y = ((x + y) >> 8) - (H * 2) + ((c->y - (tc->lefttop).y) >> 8);

      if ((u32)(Y + 64) < DISPLAY_HEIGHT + 64) {
        s32 x2 = cos * (ss->x + W);
        s32 y2;
        if (s->xflip) {
          x2 = -x2;
        }
        y2 = sin * (ss->y + H);
        // X = cos*x - sin*y; yflip cancels the minus
        if (!s->yflip) {
          y2 = -y2;
        }
        X = ((x2 + y2) >> 8) - (W * 2) + ((c->x - (tc->lefttop).x) >> 8);

        if ((u32)(X + 128) < DISPLAY_WIDTH + 6 + 128) {
          oam->attr01 = SRC(s)->attr01 | (u32)(Y & 0xFF) | ((u32)(X & 0x1FF) << 16) | SS_FLIPSIZE(ss) |
                        ((u32)(SS_RAW(ss) >> 14) << 14);
          oam->attr2 = SRC(s)->attr2 + ss->tileNum;

          oam = &oam[1];
        }
      }
      ss = &ss[1];
    }
    gOamManager.p = (struct OamData*)oam;
  }
#else
  INCCODE("asm/wip/TaskCB_DrawRotatableSprite.inc");
#endif
}

NON_MATCH void RotateSprite(struct Sprite* s, s32 angle) {
#if MODERN || CBODY
  struct OamData* oam = &gOamManager.buf[s->oam.matrixNum * 4];
  s->angle = angle;
  if (s->xflip != s->yflip) {
    angle = (-angle) & 0xFF;
  }

  oam[0].affineParam = COS(angle);
  oam[1].affineParam = SIN(angle);
  if (s->xflip) {
    oam[0].affineParam = -COS(angle);
    oam[1].affineParam = -SIN(angle);
  }

  oam[2].affineParam = -SIN(angle);
  oam[3].affineParam = COS(angle);
  if (s->yflip) {
    oam[2].affineParam = SIN(angle);
    oam[3].affineParam = -COS(angle);
  }
#else
  INCCODE("asm/wip/RotateSprite.inc");
#endif
}

NON_MATCH void ScalerotSprite(struct Sprite* s, s32 angle) {
#if MODERN || CBODY
  u8 angle1, angle2;
  struct OamData* oam = &gOamManager.buf[s->oam.matrixNum * 4];
  s->angle = angle;
  if (s->xflip != s->yflip) {
    angle = (u8)(-angle);
  }

  if (s->xflip) {
    oam[0].affineParam = -((COS(angle) << 8) / (s->mag.x + 22));
    oam[1].affineParam = -((SIN(angle) << 8) / (s->mag.x + 22));
  } else {
    oam[0].affineParam = ((COS(angle) << 8) / (s->mag.x + 22));
    oam[1].affineParam = ((SIN(angle) << 8) / (s->mag.x + 22));
  }

  if (s->yflip) {
    oam[2].affineParam = ((SIN(angle) << 8) / (s->mag.y + 22));
    oam[3].affineParam = -((COS(angle) << 8) / (s->mag.y + 22));
  } else {
    oam[2].affineParam = -((SIN(angle) << 8) / (s->mag.y + 22));
    oam[3].affineParam = ((COS(angle) << 8) / (s->mag.y + 22));
  }
#else
  INCCODE("asm/wip/ScalerotSprite.inc");
#endif
}

const u8 sSpriteWidth[12] = {
    0x07, 0x0F, 0x1F, 0x3F, 0x0F, 0x1F, 0x1F, 0x3F, 0x07, 0x07, 0x0F, 0x1F,
};

const u8 sSpriteHeight[12] = {
    0x07, 0x0F, 0x1F, 0x3F, 0x07, 0x07, 0x0F, 0x1F, 0x0F, 0x1F, 0x1F, 0x3F,
};

// 0x080006a0
const u8* const sSpriteSize[2] = {
    sSpriteWidth,
    sSpriteHeight,
};

const u8 sSpriteAffineWidth[12] = {
    0x04, 0x08, 0x10, 0x20, 0x08, 0x10, 0x10, 0x20, 0x04, 0x04, 0x08, 0x10,
};

const u8 sSpriteAffineHeight[12] = {
    0x04, 0x08, 0x10, 0x20, 0x04, 0x04, 0x08, 0x10, 0x08, 0x10, 0x10, 0x20,
};

const u8* const sAffineSpriteSize[2] = {
    sSpriteAffineWidth,
    sSpriteAffineHeight,
};
