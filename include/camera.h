#ifndef GUARD_RMZ3_CAMERA_H
#define GUARD_RMZ3_CAMERA_H

#include "common.h"
#include "gba/gba.h"

struct Renderer;
struct Camera;

typedef void (*CameraFunc)(struct Camera*);

// CameraTemplate.mode, Camera.mode
typedef enum {
  CM0_DISABLED,
  CM1,
  CM2,
  CM3,
  CM4,
  CM5,
  CM6,
  CM7,
} CameraMode;

// chaseMode
#define CHASE_MODE_B3 (1 << 3)
#define CHASE_MODE_B4 (1 << 4)
#define CHASE_MODE_B5 (1 << 5)

// カメラの初期設定 08022418 で利用
struct CameraTemplate {
  u8 mode;       // -> Camera.mode
  u8 chaseMode;  // -> Camera.chaseMode
  u8 unk_02;
  u8 unk_03;
  Coords32 camera;
  Coords32 forceScrollSpeed;
  s16 dx;
  s16 ddx;
  s16 dy;
  s16 ddy;
  s32 left;
  s32 right;
  s32 top;
  s32 bottom;
};

struct Camera {
  struct Pivot pivot;
  const struct CameraTemplate* template;
  struct Renderer* renderer;
  CameraFunc callback;  // 毎フレーム呼び出される
  s8 mode;
  u8 chaseMode;  // 0x19, .target に .viewport を近づける挙動モード
  s16 unk_1a;
  bool8 isCallbackOnce;  // .mode が変わったら FALSE になって、 .callback が呼び出されると TRUE になるフラグ
  u16 ALIGNED(4) unk_20;
  s16 counter;  // Lerp用のフレームカウンタ
  u8 unk_24[4];
  Coords32 quake;             // 画面の振動
  Coords32 target;            // .viewportがあるべき位置 .flagsによって、ここに .viewport を徐々に近づけたり、一気にここに.coordがワープするよう設定する
  Coords32 viewport;          // 0x38, 現在の画面中央
  Coords32 forceScrollSpeed;  // 強制スクロールの速度
  Coords32* player;           // プレイヤーの座標

  s32 dx;
  s32 ddx;
  s32 dy;
  s32 ddy;

  s32 left;    // cameraMode 4以上の時の境界
  s32 right;   // cameraMode 4以上の時の境界
  s32 top;     // cameraMode 4以上の時の境界
  s32 bottom;  // cameraMode 4以上の時の境界
};

void Camera_Reset(struct Camera* camera, const struct CameraTemplate* template, struct Renderer* r);
void Camera_Update(struct Camera* cam);
void Camera_Render(struct Camera* cam);
void Camera_Shake(struct Camera* cam);
void Camera_SetMode(struct Camera* cam, u32 mode);
void Camera_LoadTemplate(struct Camera* cam, const struct CameraTemplate* t);
u32 Camera_GetDistance(struct Camera* cam, Coords32* c);

#endif  // GUARD_RMZ3_CAMERA_H
