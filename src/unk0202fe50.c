#include "unk0202fe50.h"

// Unused code

typedef void (*Unk0834cc60Func)(struct Unused_0202fe50*);

static bool8 FUN_08019e4c(void) { return FALSE; }

static bool8 FUN_08019e50(void) { return FALSE; }

static void unused_08019e54(void) {
  u16* tmp;
  u32* p = &gUnk_0202fe50.unk_04;
  *p = 0;
  tmp = ((u16*)(p - 1));
  tmp[1] = 0;
}

static void unused_08019e84(struct Unused_0202fe50* p);
static void nop_08019e8c(struct Unused_0202fe50* p);
static void nop_08019e90(struct Unused_0202fe50* p);

static void unused_08019e64(void) {
  static const Unk0834cc60Func PTR_ARRAY_0834cc60[3] = {
      unused_08019e84,
      nop_08019e8c,
      nop_08019e90,
  };
  PTR_ARRAY_0834cc60[(u8)gUnk_0202fe50.unk_04](&gUnk_0202fe50);
}

static void unused_08019e84(struct Unused_0202fe50* p) { p->unk_02 = 0; }
static void nop_08019e8c(struct Unused_0202fe50* _ UNUSED) { return; }
static void nop_08019e90(struct Unused_0202fe50* _ UNUSED) { return; }
