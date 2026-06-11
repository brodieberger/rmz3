#include "global.h"
#include "overworld.h"

static const Coords32 sWarpCoordsListA[37];
static const Coords32 sWarpCoordsListB[37];

/**
 * @brief 3Dドア、テレポータル による行き先を取得 (水没した図書館は除く)
 * @details sWarpCoordsListA の座標で、引数の座標から PIXEL(32) の範囲に収まるものがあれば、 (sWarpCoordsListA ではなく) sWarpCoordsListB の同じインデックスの座標を返す
 * @param c ワープ前の座標
 * @return ワープ先の座標。見つからない場合は NULL
 * @note 0x08019d20
 * @remark GetWarpDestination2 と対になっている
 */
Coords32* GetWarpDestination1(Coords32* c) {
  s32 i = 0;
  u32 id = gOverworld.terrain.id & 0x7F;
  if (id == STAGE_OLD_RESIDENTIAL) {
    i = 21;
  } else if (id == STAGE_WEILS_LABO) {
    i = 28;
  } else if (id == STAGE_SUB_ARCADIA) {
    i = 36;
  }

  for (; i < (s32)ARRAY_COUNT(sWarpCoordsListA); i++) {
    s32 ofs_x = sWarpCoordsListA[i].x - c->x;
    if ((ofs_x >= -PIXEL(32)) && (ofs_x <= PIXEL(32))) {
      s32 ofs_y = sWarpCoordsListA[i].y - c->y;
      if ((ofs_y >= -PIXEL(32)) && (ofs_y <= PIXEL(32))) {
        break;
      }
    }
  }

  if (i == ARRAY_COUNT(sWarpCoordsListA)) {
    return NULL;
  } else {
    return (Coords32*)&sWarpCoordsListB[i];
  }
}

/**
 * @brief 3Dドア、テレポータル による行き先を取得 (水没した図書館は除く)
 * @details sWarpCoordsListB の座標で、引数の座標から PIXEL(32) の範囲に収まるものがあれば、 (sWarpCoordsListB ではなく) sWarpCoordsListA の同じインデックスの座標を返す
 * @param c ワープ前の座標
 * @return ワープ先の座標。見つからない場合は NULL
 * @note 0x08019dd0
 * @remark GetWarpDestination1 と対になっている
 */
Coords32* GetWarpDestination2(Coords32* c) {
  s32 i;
  for (i = 0; i < (s32)ARRAY_COUNT(sWarpCoordsListB); i++) {
    s32 ofs_x = sWarpCoordsListB[i].x - c->x;
    if ((ofs_x >= -PIXEL(32)) && (ofs_x <= PIXEL(32))) {
      s32 ofs_y = sWarpCoordsListB[i].y - c->y;
      if ((ofs_y >= -PIXEL(32)) && (ofs_y <= PIXEL(32))) {
        break;
      }
    }
  }

  if (i == ARRAY_COUNT(sWarpCoordsListB)) {
    return NULL;
  } else {
    return (Coords32*)&sWarpCoordsListA[i];
  }
}

static const Coords32 sWarpCoordsListA[37] = {
    {PIXEL(2992), PIXEL(928)},  {PIXEL(2000), PIXEL(928)},  {PIXEL(3440), PIXEL(928)}, {PIXEL(3344), PIXEL(928)}, {PIXEL(1904), PIXEL(928)}, {PIXEL(1248), PIXEL(928)}, {PIXEL(1248), PIXEL(1088)}, {PIXEL(1184), PIXEL(1408)}, {PIXEL(1984), PIXEL(1408)}, {PIXEL(1152), PIXEL(1248)}, {PIXEL(1408), PIXEL(1248)}, {PIXEL(2000), PIXEL(1088)}, {PIXEL(2048), PIXEL(1248)}, {PIXEL(336), PIXEL(1744)}, {PIXEL(432), PIXEL(1744)}, {PIXEL(528), PIXEL(1744)}, {PIXEL(624), PIXEL(1744)}, {PIXEL(1056), PIXEL(1744)}, {PIXEL(1152), PIXEL(1744)},
    {PIXEL(1248), PIXEL(1744)}, {PIXEL(1344), PIXEL(1744)}, {PIXEL(1328), PIXEL(768)}, {PIXEL(1536), PIXEL(576)}, {PIXEL(1792), PIXEL(304)}, {PIXEL(2080), PIXEL(752)}, {PIXEL(3696), PIXEL(224)},  {PIXEL(5904), PIXEL(416)},  {PIXEL(5904), PIXEL(1248)}, {PIXEL(2912), PIXEL(480)},  {PIXEL(3056), PIXEL(480)},  {PIXEL(2928), PIXEL(640)},  {PIXEL(3040), PIXEL(640)},  {PIXEL(5792), PIXEL(320)}, {PIXEL(5936), PIXEL(320)}, {PIXEL(5808), PIXEL(480)}, {PIXEL(5920), PIXEL(480)}, {PIXEL(352), PIXEL(1056)},
};  // 0x0834ca10

static const Coords32 sWarpCoordsListB[37] = {
    {PIXEL(448), PIXEL(464)},   {PIXEL(272), PIXEL(464)},   {PIXEL(2912), PIXEL(304)}, {PIXEL(3392), PIXEL(624)}, {PIXEL(2912), PIXEL(624)}, {PIXEL(3152), PIXEL(1424)}, {PIXEL(272), PIXEL(784)},   {PIXEL(272), PIXEL(1424)}, {PIXEL(1712), PIXEL(1744)}, {PIXEL(2432), PIXEL(1744)}, {PIXEL(2848), PIXEL(1744)}, {PIXEL(272), PIXEL(1744)}, {PIXEL(992), PIXEL(1744)}, {PIXEL(272), PIXEL(2064)},  {PIXEL(752), PIXEL(2064)},  {PIXEL(1232), PIXEL(2064)}, {PIXEL(1712), PIXEL(2064)}, {PIXEL(2192), PIXEL(2064)}, {PIXEL(2672), PIXEL(2064)},
    {PIXEL(3152), PIXEL(2064)}, {PIXEL(3152), PIXEL(1744)}, {PIXEL(272), PIXEL(1264)}, {PIXEL(992), PIXEL(1264)}, {PIXEL(2672), PIXEL(784)}, {PIXEL(1712), PIXEL(1264)}, {PIXEL(2192), PIXEL(1264)}, {PIXEL(3392), PIXEL(576)}, {PIXEL(3392), PIXEL(1408)}, {PIXEL(288), PIXEL(1072)},  {PIXEL(824), PIXEL(1392)},  {PIXEL(768), PIXEL(1072)}, {PIXEL(288), PIXEL(1392)}, {PIXEL(1608), PIXEL(1072)}, {PIXEL(2208), PIXEL(1392)}, {PIXEL(1544), PIXEL(1392)}, {PIXEL(2208), PIXEL(912)},  {PIXEL(1848), PIXEL(432)},
};  // 0x0834cb38
