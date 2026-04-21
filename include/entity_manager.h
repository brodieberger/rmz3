#ifndef __INCLUDE_ENTITY_MANAGER_H__
#define __INCLUDE_ENTITY_MANAGER_H__

#include "types.h"

struct Entity;

// size is 40 bytes
struct EntityHeader {
  struct Entity* arr;   // Entityの配列の先頭(固定)
  s16 type;             // Entityの種類
  s16 size;             // .arrの各要素(Entity)のサイズ
  s16 length;           // .arrの要素数(固定)
  s16 remaining;        // .lengthを初期値として徐々に減る
  struct Entity* last;  // fnを .arr のどのEntityまで処理したか だいたいnextを指す
  struct Entity* free;  // 空きエントリ
  struct Entity* next;
  struct Entity* prev;
  u32 unk[3];
};

void InitEntityHeader(struct EntityHeader* h, s8 kind, struct Entity* arr, s16 size, s16 count);

#endif  // __INCLUDE_ENTITY_MANAGER_H__
