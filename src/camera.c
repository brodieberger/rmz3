#include "camera.h"

#include "global.h"
#include "overworld.h"
#include "sprite.h"

static void focus(struct Camera* camera, u8 r1);

void CalcCameraDelta(Coords32* c1, Coords32* c2);

// 0x0801a5bc
void Camera_Reset(struct Camera* cam, const struct CameraTemplate* template, Renderer* r) {
  cam->template = template;
  cam->renderer = r;
  (cam->viewport).x = 0, (cam->viewport).y = 0;
  ResetPivot(&cam->pivot, &cam->viewport, 0, 0);
  (cam->pivot).offset = &cam->quake;
  cam->chaseMode = 0;
  cam->counter = 0;
  Camera_LoadTemplate(cam, template);
  focus(cam, CHASE_MODE_B3);
}

// 0x0801a5f8
void Camera_Update(struct Camera* cam) { cam->callback(cam); }

// 0x0801a604
void Camera_Shake(struct Camera* cam) {
  CalcQuake(&cam->viewport, &cam->quake);
  quake_0801acdc(&cam->viewport);
}

// 0x0801a620
void Camera_Render(struct Camera* cam) {
  Renderer* r = cam->renderer;
  if (cam->mode != CM0_DISABLED) {
    Renderer_SetPivot(r, &cam->pivot);
    Renderer_Flush(r);
  }
}

// --------------------------------------------

static void CameraMode0Callback(struct Camera* _);
static void CameraMode1Callback_ForceScroll(struct Camera* cam);
static void CameraMode2Callback(struct Camera* cam);
static void CameraMode3Callback(struct Camera* cam);
static void CameraMode4Callback(struct Camera* cam);
static void CameraMode7Callback(struct Camera* cam);

// 0x0801a640
void Camera_SetMode(struct Camera* cam, u32 mode) {
  // clang-format off
  static const CameraFunc sUpdates[8] = {
      [CM0_DISABLED] = CameraMode0Callback,
      [CM1] = CameraMode1Callback_ForceScroll,
      [CM2] = CameraMode2Callback,
      [CM3] = CameraMode3Callback,
      [CM4] = CameraMode4Callback,
      [CM5] = CameraMode4Callback,
      [CM6] = CameraMode4Callback,
      [CM7] = CameraMode7Callback,
  };
  // clang-format on
  cam->mode = mode;
  *(u32*)&cam->isCallbackOnce = FALSE;
  cam->unk_20 = 0;
  cam->unk_1a = 0;
  cam->callback = sUpdates[mode];
}

// 0x0801a65c
void Camera_LoadTemplate(struct Camera* cam, const struct CameraTemplate* t) {
  if (t == NULL) {
    Camera_SetMode(cam, CM0_DISABLED);
    cam->player = NULL;
    cam->chaseMode = 0;
    cam->counter = 0;
    (cam->target).x = 0, (cam->target).y = 0;
    return;
  }

  Camera_SetMode(cam, t->mode);
  cam->chaseMode = t->chaseMode;
  cam->counter = 0;
  cam->player = NULL;
  if (t->mode == CM1) {
    (cam->target).x = (t->camera).x;
    (cam->target).y = (t->camera).y;
  }
  (cam->forceScrollSpeed).x = (t->forceScrollSpeed).x;
  (cam->forceScrollSpeed).y = (t->forceScrollSpeed).y;
  cam->dx = t->dx, cam->ddx = t->ddx;
  cam->dy = t->dy, cam->ddy = t->ddy;
  cam->left = t->left;
  cam->right = t->right;
  cam->top = t->top;
  cam->bottom = t->bottom;
}

// 0x0801a6d0
// .viewport を .target に近づける
NON_MATCH static void focus(struct Camera* cam, u8 chaseMode) {
#if MODERN
  switch (chaseMode) {
    case 0: {
      (cam->viewport).x = (cam->target).x, (cam->viewport).y = (cam->target).y;
      break;
    }
    case 1: {
      {
        s32 delta = (cam->target).x - (cam->viewport).x;
        if (delta > 0) {
          (cam->viewport).x += (delta + 31) >> 5;
        } else {
          (cam->viewport).x += (delta - 31) >> 5;
        }
      }
      {
        s32 delta = (cam->target).y - (cam->viewport).y;
        if (delta > 0) {
          (cam->viewport).y += (delta + 31) >> 5;
        } else {
          (cam->viewport).y += (delta - 31) >> 5;
        }
      }
      break;
    }
    case 2: {
      if (cam->counter < 0x3FF) {
        // カウンタの値でlerp
        s32 t = ++cam->counter;
        {
          s32 x = (((cam->viewport).x >> 2) * (0x400 - t)) + (((cam->target).x >> 2) * t);
          if (x < 0) x += 0xFF;
          (cam->viewport).x = (x >> 8);
        }
        {
          s32 y = (((cam->viewport).y >> 2) * (0x400 - t)) + ((((cam->target).y >> 2) * t));
          if (y < 0) y += 0xFF;
          (cam->viewport).y = (y >> 8);
        }
        // 目標値の近くに来たら同じ位置にする(これ以上は計算の無駄)
        if ((((cam->viewport).x - (cam->target).x) >= -128) && (((cam->viewport).x - (cam->target).x) <= 128)) (cam->viewport).x = (cam->target).x;
        if ((((cam->viewport).y - (cam->target).y) >= -128) && (((cam->viewport).y - (cam->target).y) <= 128)) (cam->viewport).y = (cam->target).y;
        break;
      }
      (cam->viewport).x = (cam->target).x, (cam->viewport).y = (cam->target).y;
      break;
    }
    case 4: {
      if (cam->counter < 0xFF) {
        // カウンタの値でlerp
        s32 t = ++cam->counter;
        {
          s32 x = ((cam->viewport).x * (0x100 - t)) + ((cam->target).x * t);
          if (x < 0) x += 0xFF;
          (cam->viewport).x = (x >> 8);
        }
        {
          s32 y = ((cam->viewport).y * (0x100 - t)) + ((cam->target).y * t);
          if (y < 0) y += 0xFF;
          (cam->viewport).y = (y >> 8);
        }
        // 目標値の近くに来たら同じ位置にする(これ以上は計算の無駄)
        if ((((cam->viewport).x - (cam->target).x) >= -128) && (((cam->viewport).x - (cam->target).x) <= 128)) (cam->viewport).x = (cam->target).x;
        if ((((cam->viewport).y - (cam->target).y) >= -128) && (((cam->viewport).y - (cam->target).y) <= 128)) (cam->viewport).y = (cam->target).y;
        break;
      }
      (cam->viewport).x = (cam->target).x, (cam->viewport).y = (cam->target).y;
      break;
    }
    default: {
      cam->chaseMode &= ~CHASE_MODE_B3;
      (cam->viewport).x = (cam->target).x, (cam->viewport).y = (cam->target).y;
      break;
    }
  }
#else
  INCCODE("asm/wip/camera_0801a6d0.inc");
#endif
}

/**
 * @retval 0 c is in Camera(= inside screen)
 * @retval カメラからの距離(x方向の距離とy方向の距離の長い方)
 * @note 0x0801a810
 */
u32 Camera_GetDistance(struct Camera* cam, Coords32* c) {
  s32 dx, dy;

  dx = (cam->viewport).x - c->x;
  if (dx < 0) {
    dx = -PIXEL(DISPLAY_WIDTH / 2) - dx;
  } else {
    dx = dx - PIXEL(DISPLAY_WIDTH / 2);
  }
  if (dx < 0) dx = 0;

  dy = (cam->viewport).y - c->y;
  if (dy < 0) {
    dy = -PIXEL(DISPLAY_HEIGHT / 2) - dy;
  } else {
    dy = dy - PIXEL(DISPLAY_HEIGHT / 2);
  }
  if (dy < 0) dy = 0;

  if (dx < dy) {
    return dy;
  }
  return dx;
}

static void CameraMode0Callback(struct Camera* _) {}

static void CameraMode1Callback_ForceScroll(struct Camera* cam) {
  if (cam->isCallbackOnce == FALSE) {
    cam->counter = 0;
    cam->isCallbackOnce++;
  }
  (cam->target).x += (cam->forceScrollSpeed).x;
  (cam->target).y += (cam->forceScrollSpeed).y;
  focus(cam, cam->chaseMode);
}

// ゼロのいる位置からカメラを徐々に引き離す
static void CameraMode2Callback(struct Camera* cam) {
  if (cam->isCallbackOnce == FALSE) {
    cam->counter = 0;
    cam->isCallbackOnce++;
  }
  cam->dx += cam->ddx;
  cam->dy += cam->ddy;
  if (cam->player != NULL) {
    (cam->target).x = (cam->player)->x + cam->dx;
    (cam->target).y = (cam->player)->y + cam->dy;
  }
  focus(cam, cam->chaseMode);
}

// レジスタンスベース、 バイル研究所 の　ボスラッシュ部屋のうち横幅が画面1枚に収まる部屋(ブレイジンフリザード、チルドレイナラビッタ、デスタンツマンティスク、キュービットフォクスター戦) で使用
NON_MATCH static void CameraMode3Callback(struct Camera* cam) {
#if MODERN
  s32 zx, zy, tmp;
  Coords32 c, d, target;
  if (cam->isCallbackOnce == 0) {
    cam->counter = 0;
    cam->isCallbackOnce++;
  }
  zx = (cam->player)->x + cam->dx;
  zy = (cam->player)->y + cam->dy;

  c.x = (cam->target).x;
  c.y = (cam->target).y;

  tmp = (cam->target).x - zx;
  if (tmp > 0) c.x -= tmp;
  if (tmp < 0) c.x -= tmp;

  tmp = (cam->target).y - zy;
  if (tmp > -PIXEL(16)) c.y -= (PIXEL(16) + tmp);
  if (tmp < -PIXEL(24)) c.y -= (PIXEL(24) + tmp);

  CalcCameraDelta(&c, &d);
  if (cam->chaseMode & CHASE_MODE_B4) {
    target.x = c.x;
  } else {
    target.x = c.x + d.x;
  }
  if (cam->chaseMode & CHASE_MODE_B5) {
    target.y = c.y;
  } else {
    target.y = c.y + d.y;
  }

  if (cam->chaseMode & CHASE_MODE_B3) {
    (cam->target).y = target.y;
    (cam->target).x = target.x;
  } else {
    // 最大でも動くのは 4px
    if ((cam->target).x + PIXEL(4) < target.x) {
      (cam->target).x = (cam->target).x + PIXEL(4);
    } else if ((cam->target).x - PIXEL(4) > target.x) {
      (cam->target).x = (cam->target).x - PIXEL(4);
    } else {
      (cam->target).x = target.x;
    }

    // 7 : 1 の割合
    if ((cam->target).y - target.y >= 0) {
      (cam->target).y = ((cam->target).y * 7 + target.y) >> 3;
    } else {
      (cam->target).y = ((cam->target).y * 7 + target.y + 7) >> 3;
    }
  }
  focus(cam, cam->chaseMode);
#else
  INCCODE("asm/wip/CameraMode3Callback.inc");
#endif
}

// 0x0801a9e0
WIP static void CameraMode4Callback(struct Camera* cam) {
#ifdef ALWAYS_FALSE
  s32 zx, zy, tmp;
  Coords32 c, d, target;
  if (cam->isCallbackOnce == 0) {
    cam->counter = 0;
    cam->isCallbackOnce++;
  }
  zx = (cam->player)->x + cam->dx;
  zy = (cam->player)->y + cam->dy;

  c.x = (cam->target).x;
  c.y = (cam->target).y;

  tmp = (cam->target).x - zx;
  if (tmp > 0) c.x -= tmp;
  if (tmp < 0) c.x -= tmp;

  tmp = (cam->target).y - zy;
  if (tmp > -PIXEL(16)) c.y -= (PIXEL(16) + tmp);
  if (tmp < -PIXEL(24)) c.y -= (PIXEL(24) + tmp);

  CalcCameraDelta(&c, &d);
  if (cam->chaseMode & CHASE_MODE_B4) {
    target.x = c.x;
  } else {
    target.x = c.x + d.x;
  }
  target.y = c.y + d.y;

  if (target.x < cam->left + PIXEL(120)) target.x = cam->left + PIXEL(120);
  if (target.x > cam->right - PIXEL(120)) target.x = cam->right - PIXEL(120);
  if (target.y < cam->top + PIXEL(80)) target.y = cam->top + PIXEL(80);
  if (target.y > cam->bottom - PIXEL(80)) target.y = cam->bottom - PIXEL(80);

  if (cam->chaseMode & CHASE_MODE_B3) {
    (cam->target).y = target.y;
    (cam->target).x = target.x;
  } else {
    // 最大でも動くのは 4px
    if ((cam->target).x + PIXEL(4) < target.x) {
      (cam->target).x = (cam->target).x + PIXEL(4);
    } else if ((cam->target).x - PIXEL(4) > target.x) {
      (cam->target).x = (cam->target).x - PIXEL(4);
    } else {
      (cam->target).x = target.x;
    }

    // 7 : 1 の割合
    if ((cam->target).y - target.y >= 0) {
      (cam->target).y = ((cam->target).y * 7 + target.y) >> 3;
    } else {
      (cam->target).y = ((cam->target).y * 7 + target.y + 7) >> 3;
    }
  }
  focus(cam, cam->chaseMode);
#else
  INCCODE("asm/wip/CameraMode4Callback.inc");
#endif
}

static void CameraMode7Callback(struct Camera* _) {}
