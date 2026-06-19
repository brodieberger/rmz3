#ifndef __INCLUDE_ENTITY_MANAGER_H__
#define __INCLUDE_ENTITY_MANAGER_H__

#include "types.h"

struct Entity;

// e.g. 0x02031460 (Solid)
struct EntityHeader {
  struct Entity* arr;   // Entityの配列の先頭(固定)
  s16 type;             // 0x04, Entityの種類 (= Entity.kind)
  s16 size;             // 0x06, .arrの各要素(Entity)のサイズ
  s16 length;           // 0x08, .arrの要素数(固定)
  s16 remaining;        // 0x0A, .lengthを初期値として徐々に減る
  struct Entity* cur;   // 0x0C, fnを .arr のどのEntityまで処理したか
  struct Entity* free;  // 0x10, 空きエントリ
  struct Entity* tail;  // 0x14, リンクリストの末尾
  struct Entity* head;  // 0x18, リンクリストの先頭 (ループではこのEntityから処理していく)
  u32 unk[3];           // 0x1C
};  // 40 bytes

void InitEntityHeader(struct EntityHeader* h, s8 kind, struct Entity* arr, s16 size, s16 count);

#endif  // __INCLUDE_ENTITY_MANAGER_H__
